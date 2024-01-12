/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include <string>

#include "base/utils/system_properties.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t ORIENTATION_PORTRAIT = 0;
constexpr int32_t ORIENTATION_LANDSCAPE = 1;

void Swap(int32_t& deviceWidth, int32_t& deviceHeight)
{
    int32_t temp = deviceWidth;
    deviceWidth = deviceHeight;
    deviceHeight = temp;
}
} // namespace

DeviceType SystemProperties::deviceType_ = DeviceType::PHONE;
DeviceOrientation SystemProperties::orientation_ { DeviceOrientation::PORTRAIT };
bool SystemProperties::isHookModeEnabled_ = false;
bool SystemProperties::rosenBackendEnabled_ = true;
bool SystemProperties::windowAnimationEnabled_ = true;
bool SystemProperties::buildTraceEnable_ = false;
double SystemProperties::resolution_ = 0.0;
constexpr float defaultAnimationScale = 1.0f;
bool SystemProperties::extSurfaceEnabled_ = false;
uint32_t SystemProperties::dumpFrameCount_ = 0;
bool SystemProperties::debugEnabled_ = false;
ColorMode SystemProperties::colorMode_ { ColorMode::LIGHT };
int32_t SystemProperties::deviceWidth_ = 720;
int32_t SystemProperties::deviceHeight_ = 1280;
bool SystemProperties::downloadByNetworkEnabled_ = false;
bool SystemProperties::traceEnabled_ = false;
int32_t SystemProperties::devicePhysicalWidth_ = 0;
int32_t SystemProperties::devicePhysicalHeight_ = 0;
bool SystemProperties::enableScrollableItemPool_ = false;
bool SystemProperties::navigationBlurEnabled_ = false;
bool SystemProperties::gridCacheEnabled_ = false;

float SystemProperties::GetFontWeightScale()
{
    // Default value of font weight scale is 1.0.
    return 1.0f;
}

DeviceType SystemProperties::GetDeviceType()
{
    return deviceType_;
}

bool SystemProperties::GetDebugEnabled()
{
    return false;
}

float SystemProperties::GetAnimationScale()
{
    return defaultAnimationScale;
}

bool SystemProperties::GetIsUseMemoryMonitor()
{
    return false;
}

void SystemProperties::SetDeviceOrientation(int32_t orientation)
{
    if (orientation == ORIENTATION_PORTRAIT && orientation_ != DeviceOrientation::PORTRAIT) {
        Swap(deviceWidth_, deviceHeight_);
        orientation_ = DeviceOrientation::PORTRAIT;
    } else if (orientation == ORIENTATION_LANDSCAPE && orientation_ != DeviceOrientation::LANDSCAPE) {
        Swap(deviceWidth_, deviceHeight_);
        orientation_ = DeviceOrientation::LANDSCAPE;
    }
}

bool SystemProperties::Is24HourClock()
{
    return false;
}

bool SystemProperties::GetImageFrameworkEnabled()
{
    return true;
}

bool SystemProperties::GetTitleStyleEnabled()
{
    return false;
}

std::string SystemProperties::GetCustomTitleFilePath()
{
    return {};
}

bool SystemProperties::GetDisplaySyncSkipEnabled()
{
    return true;
}

bool SystemProperties::GetNavigationBlurEnabled()
{
    return navigationBlurEnabled_;
}

bool SystemProperties::GetLayoutTraceEnabled()
{
    return false;
}

bool SystemProperties::GetGridCacheEnabled()
{
    return gridCacheEnabled_;
}
} // namespace OHOS::Ace
