/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.12.v201907221221.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/commonapi/HelloWorldDBusProxy.hpp>

namespace v1 {
namespace commonapi {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createHelloWorldDBusProxy(
    const CommonAPI::DBus::DBusAddress &_address,
    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection) {
    return std::make_shared< HelloWorldDBusProxy>(_address, _connection);
}

void initializeHelloWorldDBusProxy() {
     CommonAPI::DBus::Factory::get()->registerProxyCreateMethod(
        HelloWorld::getInterface(),
        &createHelloWorldDBusProxy);
}

INITIALIZER(registerHelloWorldDBusProxy) {
    CommonAPI::DBus::Factory::get()->registerInterface(initializeHelloWorldDBusProxy);
}

HelloWorldDBusProxy::HelloWorldDBusProxy(
    const CommonAPI::DBus::DBusAddress &_address,
    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection)
    :   CommonAPI::DBus::DBusProxy(_address, _connection)
{
}



    void HelloWorldDBusProxy::sayHello(const std::string &_name, CommonAPI::CallStatus &_internalCallStatus, std::string &_message, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable< std::string, CommonAPI::DBus::StringDeployment> deploy_name(_name, static_cast< CommonAPI::DBus::StringDeployment* >(nullptr));
        CommonAPI::Deployable< std::string, CommonAPI::DBus::StringDeployment> deploy_message(static_cast< CommonAPI::DBus::StringDeployment* >(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable< std::string, CommonAPI::DBus::StringDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable< std::string,CommonAPI::DBus::StringDeployment>
            >
            >::callMethodWithReply(
        *this,
        "sayHello",
        "s",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
deploy_name,
_internalCallStatus,
deploy_message);
_message = deploy_message.getValue();
}
    std::future<CommonAPI::CallStatus> HelloWorldDBusProxy::sayHelloAsync(const std::string &_name, SayHelloAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable< std::string, CommonAPI::DBus::StringDeployment> deploy_name(_name, static_cast< CommonAPI::DBus::StringDeployment* >(nullptr));
        CommonAPI::Deployable< std::string, CommonAPI::DBus::StringDeployment> deploy_message(static_cast< CommonAPI::DBus::StringDeployment* >(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable< std::string, CommonAPI::DBus::StringDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable< std::string,CommonAPI::DBus::StringDeployment>
            >
            >::callMethodAsync(
        *this,
        "sayHello",
        "s",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        deploy_name,
        [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable< std::string, CommonAPI::DBus::StringDeployment > _message) {
            if (_callback)
                _callback(_internalCallStatus, _message.getValue());
        },
        std::make_tuple(deploy_message));
    }


void HelloWorldDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
          ownVersionMajor = 1;
          ownVersionMinor = 0;
      }

      } // namespace commonapi
      } // namespace v1
