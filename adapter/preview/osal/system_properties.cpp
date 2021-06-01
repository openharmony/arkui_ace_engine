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

#include "base/log/log.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t ORIENTATION_PORTRAIT = 0;
constexpr int32_t ORIENTATION_LANDSCAPE = 1;
const char PROPERTY_DEVICE_TYPE_PHONE[] = "phone";
const char PROPERTY_DEVICE_TYPE_TV[] = "tv";
const char PROPERTY_DEVICE_TYPE_TABLET[] = "tablet";
const char PROPERTY_DEVICE_TYPE_WEARABLE[] = "wearable";
const char PROPERTY_DEVICE_TYPE_CAR[] = "car";

static constexpr char UNDEFINED_PARAM[] = "undefined parameter";

void Swap(int32_t& deviceWidth, int32_t& deviceHeight)
{
    int32_t temp = deviceWidth;
    deviceWidth = deviceHeight;
    deviceHeight = temp;
}

} // namespace

void SystemProperties::InitDeviceType(DeviceType type)
{
    // Properties: "phone", "tv", "tablet", "watch", "car"
    if (type == DeviceType::TV) {
        deviceType_ = DeviceType::TV;
        paramDeviceType_ = PROPERTY_DEVICE_TYPE_TV;
    } else if (type == DeviceType::WATCH) {
        deviceType_ = DeviceType::WATCH;
        paramDeviceType_ = PROPERTY_DEVICE_TYPE_WEARABLE;
    } else if (type == DeviceType::CAR) {
        deviceType_ = DeviceType::CAR;
        paramDeviceType_ = PROPERTY_DEVICE_TYPE_CAR;
    } else if (type == DeviceType::TABLET) {
        deviceType_ = DeviceType::PHONE;
        paramDeviceType_ = PROPERTY_DEVICE_TYPE_TABLET;
    } else {
        deviceType_ = DeviceType::PHONE;
        paramDeviceType_ = PROPERTY_DEVICE_TYPE_PHONE;
    }
}

bool SystemProperties::traceEnabled_ = false;
bool SystemProperties::isRound_ = false;
int32_t SystemProperties::width_ = 0;
int32_t SystemProperties::height_ = 0;
int32_t SystemProperties::deviceWidth_ = 0;
int32_t SystemProperties::deviceHeight_ = 0;
double SystemProperties::resolution_ = 1.0;
DeviceType SystemProperties::deviceType_ { DeviceType::PHONE };
DeviceOrientation SystemProperties::orientation_ { DeviceOrientation::PORTRAIT };
std::string SystemProperties::brand_ = UNDEFINED_PARAM;
std::string SystemProperties::manufacturer_ = UNDEFINED_PARAM;
std::string SystemProperties::model_ = UNDEFINED_PARAM;
std::string SystemProperties::product_ = UNDEFINED_PARAM;
std::string SystemProperties::apiVersion_ = UNDEFINED_PARAM;
std::string SystemProperties::releaseType_ = UNDEFINED_PARAM;
std::string SystemProperties::paramDeviceType_ = UNDEFINED_PARAM;
int32_t SystemProperties::mcc_ = MCC_UNDEFINED;
int32_t SystemProperties::mnc_ = MNC_UNDEFINED;
ColorMode SystemProperties::colorMode_ = ColorMode::LIGHT;

void SystemProperties::UpdateSurfaceStatus(int32_t width, int32_t height)
{
    width_ = width;
    height_ = height;
}

DeviceType SystemProperties::GetDeviceType()
{
    return deviceType_;
}

void SystemProperties::InitDeviceTypeBySystemProperty()
{
    deviceType_ = DeviceType::PHONE;
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
    // To avoid the deviceinfor api failure due to surface width and height equal 0 in previewer.
    width_ = deviceWidth_;
    height_ = deviceHeight_;
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
    return 1.0f;
}

void SystemProperties::InitMccMnc(int32_t mcc, int32_t mnc)
{
    mcc_ = mcc;
    mnc_ = mnc;
}

} // namespace OHOS::Ace
