/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"

#include "parameters.h"

#include "base/log/log.h"

namespace OHOS::Ace {
namespace {

const char PROPERTY_DEVICE_TYPE[] = "ro.build.characteristics";
const char PROPERTY_DEVICE_TYPE_DEFAULT[] = "default";
const char PROPERTY_DEVICE_TYPE_TV[] = "tv";
const char PROPERTY_DEVICE_TYPE_WATCH[] = "watch";
const char PROPERTY_DEVICE_TYPE_CAR[] = "car";

constexpr int32_t ORIENTATION_PORTRAIT = 0;
constexpr int32_t ORIENTATION_LANDSCAPE = 1;

void Swap(int32_t& deviceWidth, int32_t& deviceHeight)
{
    int32_t temp = deviceWidth;
    deviceWidth = deviceHeight;
    deviceHeight = temp;
}

} // namespace

void SystemProperties::InitDeviceType(DeviceType)
{
    // Do nothing, no need to store type here, use system property at 'GetDeviceType' instead.
}

bool SystemProperties::traceEnabled_ = system::GetParameter("persist.ace.trace.enabled", "0") == "1";
bool SystemProperties::isRound_ = false;
int32_t SystemProperties::width_ = 0;
int32_t SystemProperties::height_ = 0;
int32_t SystemProperties::deviceWidth_ = 0;
int32_t SystemProperties::deviceHeight_ = 0;
double SystemProperties::resolution_ = 1.0;
DeviceType SystemProperties::deviceType_ { DeviceType::UNKNOWN };
DeviceOrientation SystemProperties::orientation_ { DeviceOrientation::PORTRAIT };
std::string SystemProperties::brand_ = INVALID_PARAM;
std::string SystemProperties::manufacturer_ = INVALID_PARAM;
std::string SystemProperties::model_ = INVALID_PARAM;
std::string SystemProperties::product_ = INVALID_PARAM;
std::string SystemProperties::apiVersion_ = INVALID_PARAM;
std::string SystemProperties::releaseType_ = INVALID_PARAM;
std::string SystemProperties::paramDeviceType_ = INVALID_PARAM;
int32_t SystemProperties::mcc_ = MCC_UNDEFINED;
int32_t SystemProperties::mnc_ = MNC_UNDEFINED;
ColorMode SystemProperties::colorMode_ { ColorMode::LIGHT };

void SystemProperties::UpdateSurfaceStatus(int32_t width, int32_t height)
{
    width_ = width;
    height_ = height;
}

DeviceType SystemProperties::GetDeviceType()
{
    InitDeviceTypeBySystemProperty();
    return deviceType_;
}

void SystemProperties::InitDeviceTypeBySystemProperty()
{
    if (deviceType_ != DeviceType::UNKNOWN) {
        return;
    }

    auto deviceProp = system::GetParameter(PROPERTY_DEVICE_TYPE, PROPERTY_DEVICE_TYPE_DEFAULT);
    // Properties: "default", "tv", "tablet", "watch", "car"
    LOGD("GetDeviceType, deviceProp=%{private}s.", deviceProp.c_str());
    if (deviceProp == PROPERTY_DEVICE_TYPE_TV) {
        deviceType_ = DeviceType::TV;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_CAR) {
        deviceType_ = DeviceType::CAR;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_WATCH) {
        deviceType_ = DeviceType::WATCH;
    } else {
        deviceType_ = DeviceType::PHONE;
    }
}

void SystemProperties::InitDeviceInfo(int32_t deviceWidth, int32_t deviceHeight, int32_t orientation,
    double resolution, bool isRound)
{
    // SetDeviceOrientation should be eralier than deviceWidth/deviceHeight init.
    SetDeviceOrientation(orientation);

    isRound_ = isRound;
    resolution_ = resolution;
    deviceWidth_ = deviceWidth;
    deviceHeight_ = deviceHeight;
    brand_ = system::GetParameter("ro.product.brand", INVALID_PARAM);
    manufacturer_ = system::GetParameter("ro.product.manufacturer", INVALID_PARAM);
    model_ = system::GetParameter("ro.product.model", INVALID_PARAM);
    product_ = system::GetParameter("ro.product.name", INVALID_PARAM);
    apiVersion_ = system::GetParameter("hw_sc.build.os.apiversion", INVALID_PARAM);
    releaseType_ = system::GetParameter("hw_sc.build.os.releasetype", INVALID_PARAM);
    paramDeviceType_ = system::GetParameter("hw_sc.build.os.devicetype", INVALID_PARAM);

    InitDeviceTypeBySystemProperty();
}

void SystemProperties::SetDeviceOrientation(int32_t orientation)
{
    if (orientation == ORIENTATION_PORTRAIT && orientation_ != DeviceOrientation::PORTRAIT) {
        Swap(deviceWidth_, deviceHeight_);
        orientation_ = DeviceOrientation::PORTRAIT;
    } else if (orientation == ORIENTATION_LANDSCAPE && orientation_ != DeviceOrientation::LANDSCAPE) {
        Swap(deviceWidth_, deviceHeight_);
        orientation_ = DeviceOrientation::LANDSCAPE;
    } else {
        LOGW("SetDeviceOrientation, undefined orientation");
    }
}

float SystemProperties::GetFontWeightScale()
{
    // Default value of font weight scale is 1.0.
    std::string prop =
        "persist.sys.font_wght_scale_for_user" + std::to_string(AceApplicationInfo::GetInstance().GetUserId());
    return std::stof(system::GetParameter(prop, "1.0"));
}

void SystemProperties::InitMccMnc(int32_t mcc, int32_t mnc)
{
    mcc_ = mcc;
    mnc_ = mnc;
}

} // namespace OHOS::Ace
