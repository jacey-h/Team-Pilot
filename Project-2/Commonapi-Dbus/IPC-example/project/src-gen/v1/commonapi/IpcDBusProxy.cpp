/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.12.v201907221221.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/commonapi/IpcDBusProxy.hpp>

namespace v1 {
namespace commonapi {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createIpcDBusProxy(
    const CommonAPI::DBus::DBusAddress &_address,
    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection) {
    return std::make_shared< IpcDBusProxy>(_address, _connection);
}

void initializeIpcDBusProxy() {
     CommonAPI::DBus::Factory::get()->registerProxyCreateMethod(
        Ipc::getInterface(),
        &createIpcDBusProxy);
}

INITIALIZER(registerIpcDBusProxy) {
    CommonAPI::DBus::Factory::get()->registerInterface(initializeIpcDBusProxy);
}

IpcDBusProxy::IpcDBusProxy(
    const CommonAPI::DBus::DBusAddress &_address,
    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection)
    :   CommonAPI::DBus::DBusProxy(_address, _connection)
{
}



    void IpcDBusProxy::structInMethod(const Ipc::IpcStruct &_structParameter, CommonAPI::CallStatus &_internalCallStatus, int32_t &_output, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable< Ipc::IpcStruct, ::v1::commonapi::Ipc_::IpcStructDeployment_t> deploy_structParameter(_structParameter, static_cast< ::v1::commonapi::Ipc_::IpcStructDeployment_t* >(nullptr));
        CommonAPI::Deployable< int32_t, CommonAPI::DBus::IntegerDeployment> deploy_output(static_cast< CommonAPI::DBus::IntegerDeployment* >(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable< Ipc::IpcStruct, ::v1::commonapi::Ipc_::IpcStructDeployment_t >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable< int32_t,CommonAPI::DBus::IntegerDeployment>
            >
            >::callMethodWithReply(
        *this,
        "structInMethod",
        "(iiiii)",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
deploy_structParameter,
_internalCallStatus,
deploy_output);
_output = deploy_output.getValue();
}
    std::future<CommonAPI::CallStatus> IpcDBusProxy::structInMethodAsync(const Ipc::IpcStruct &_structParameter, StructInMethodAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable< Ipc::IpcStruct, ::v1::commonapi::Ipc_::IpcStructDeployment_t> deploy_structParameter(_structParameter, static_cast< ::v1::commonapi::Ipc_::IpcStructDeployment_t* >(nullptr));
        CommonAPI::Deployable< int32_t, CommonAPI::DBus::IntegerDeployment> deploy_output(static_cast< CommonAPI::DBus::IntegerDeployment* >(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable< Ipc::IpcStruct, ::v1::commonapi::Ipc_::IpcStructDeployment_t >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable< int32_t,CommonAPI::DBus::IntegerDeployment>
            >
            >::callMethodAsync(
        *this,
        "structInMethod",
        "(iiiii)",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        deploy_structParameter,
        [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable< int32_t, CommonAPI::DBus::IntegerDeployment > _output) {
            if (_callback)
                _callback(_internalCallStatus, _output.getValue());
        },
        std::make_tuple(deploy_output));
    }


void IpcDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
          ownVersionMajor = 1;
          ownVersionMinor = 0;
      }

      } // namespace commonapi
      } // namespace v1