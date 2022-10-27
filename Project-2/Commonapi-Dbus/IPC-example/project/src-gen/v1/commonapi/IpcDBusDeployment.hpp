/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.12.v201907221221.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/

#ifndef V1_COMMONAPI_Ipc_DBUS_DEPLOYMENT_HPP_
#define V1_COMMONAPI_Ipc_DBUS_DEPLOYMENT_HPP_

#include <v1/commonapi/IpcDBusDeployment.hpp>


#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/DBus/DBusDeployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace commonapi {
namespace Ipc_ {

// Interface-specific deployment types
typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::DBus::IntegerDeployment,
    CommonAPI::DBus::IntegerDeployment,
    CommonAPI::DBus::IntegerDeployment,
    CommonAPI::DBus::IntegerDeployment,
    CommonAPI::DBus::IntegerDeployment
> IpcStructDeployment_t;


// Type-specific deployments

// Attribute-specific deployments

// Argument-specific deployments

// Broadcast-specific deployments


} // namespace Ipc_
} // namespace commonapi
} // namespace v1

#endif // V1_COMMONAPI_Ipc_DBUS_DEPLOYMENT_HPP_