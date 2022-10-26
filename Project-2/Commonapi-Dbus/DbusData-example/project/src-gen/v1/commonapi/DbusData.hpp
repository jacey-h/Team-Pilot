/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v201907221047.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_COMMONAPI_DBUS_DATA_HPP_
#define V1_COMMONAPI_DBUS_DATA_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <CommonAPI/Types.hpp>
#include <cstdint>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace commonapi {

class DbusData {
public:
    virtual ~DbusData() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
    struct dataStruct : CommonAPI::Struct< int32_t, int32_t, int32_t, int32_t, int32_t> {
    
        dataStruct()
        {
            std::get< 0>(values_) = 0;
            std::get< 1>(values_) = 0;
            std::get< 2>(values_) = 0;
            std::get< 3>(values_) = 0;
            std::get< 4>(values_) = 0;
        }
        dataStruct(const int32_t &_TMP, const int32_t &_HUM, const int32_t &_RPM, const int32_t &_SPD, const int32_t &_BAT)
        {
            std::get< 0>(values_) = _TMP;
            std::get< 1>(values_) = _HUM;
            std::get< 2>(values_) = _RPM;
            std::get< 3>(values_) = _SPD;
            std::get< 4>(values_) = _BAT;
        }
        inline const int32_t &getTMP() const { return std::get< 0>(values_); }
        inline void setTMP(const int32_t &_value) { std::get< 0>(values_) = _value; }
        inline const int32_t &getHUM() const { return std::get< 1>(values_); }
        inline void setHUM(const int32_t &_value) { std::get< 1>(values_) = _value; }
        inline const int32_t &getRPM() const { return std::get< 2>(values_); }
        inline void setRPM(const int32_t &_value) { std::get< 2>(values_) = _value; }
        inline const int32_t &getSPD() const { return std::get< 3>(values_); }
        inline void setSPD(const int32_t &_value) { std::get< 3>(values_) = _value; }
        inline const int32_t &getBAT() const { return std::get< 4>(values_); }
        inline void setBAT(const int32_t &_value) { std::get< 4>(values_) = _value; }
        inline bool operator==(const dataStruct& _other) const {
        return (getTMP() == _other.getTMP() && getHUM() == _other.getHUM() && getRPM() == _other.getRPM() && getSPD() == _other.getSPD() && getBAT() == _other.getBAT());
        }
        inline bool operator!=(const dataStruct &_other) const {
            return !((*this) == _other);
        }
    
    };
};

const char* DbusData::getInterface() {
    return ("commonapi.DbusData:v1_0");
}

CommonAPI::Version DbusData::getInterfaceVersion() {
    return CommonAPI::Version(1, 0);
}


} // namespace commonapi
} // namespace v1

namespace CommonAPI {
}


// Compatibility
namespace v1_0 = v1;

#endif // V1_COMMONAPI_DBUS_DATA_HPP_