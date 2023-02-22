/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.2.0.v202012010857.
* Used org.franca.core 0.13.1.201807231814.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/commonapi/Ipc.hpp>
#include <v1/commonapi/IpcDBusStubAdapter.hpp>

namespace v1 {
namespace commonapi {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createIpcDBusStubAdapter(
                   const CommonAPI::DBus::DBusAddress &_address,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared< IpcDBusStubAdapter<::v1::commonapi::IpcStub>>(_address, _connection, std::dynamic_pointer_cast<::v1::commonapi::IpcStub>(_stub));
}

void initializeIpcDBusStubAdapter() {
    CommonAPI::DBus::Factory::get()->registerStubAdapterCreateMethod(
        Ipc::getInterface(), &createIpcDBusStubAdapter);
}

INITIALIZER(registerIpcDBusStubAdapter) {
    CommonAPI::DBus::Factory::get()->registerInterface(initializeIpcDBusStubAdapter);
}

} // namespace commonapi
} // namespace v1