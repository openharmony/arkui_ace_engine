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

#include "test/mock/base/mock_system_properties.h"

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
std::atomic<bool> SystemProperties::layoutTraceEnable_(false);
std::atomic<bool> SystemProperties::traceInputEventEnable_(false);
bool SystemProperties::buildTraceEnable_ = false;
bool SystemProperties::syncDebugTraceEnable_ = false;
bool SystemProperties::pixelRoundEnable_ = true;
bool SystemProperties::textTraceEnable_ = false;
bool SystemProperties::syntaxTraceEnable_ = false;
double SystemProperties::resolution_ = 0.0;
constexpr float defaultAnimationScale = 1.0f;
bool SystemProperties::extSurfaceEnabled_ = false;
uint32_t SystemProperties::dumpFrameCount_ = 0;
bool SystemProperties::debugEnabled_ = false;
bool SystemProperties::layoutDetectEnabled_ = false;
ColorMode SystemProperties::colorMode_ { ColorMode::LIGHT };
int32_t SystemProperties::deviceWidth_ = 720;
int32_t SystemProperties::deviceHeight_ = 1280;
bool SystemProperties::debugOffsetLogEnabled_ = false;
bool SystemProperties::downloadByNetworkEnabled_ = false;
int32_t SystemProperties::devicePhysicalWidth_ = 0;
int32_t SystemProperties::devicePhysicalHeight_ = 0;
bool SystemProperties::enableScrollableItemPool_ = false;
bool SystemProperties::navigationBlurEnabled_ = false;
bool SystemProperties::gridCacheEnabled_ = true;
bool SystemProperties::sideBarContainerBlurEnable_ = false;
std::atomic<bool> SystemProperties::stateManagerEnable_(false);
std::atomic<bool> SystemProperties::acePerformanceMonitorEnable_(false);
bool SystemProperties::aceCommercialLogEnable_ = false;
std::atomic<bool> SystemProperties::debugBoundaryEnabled_(false);
bool SystemProperties::developerModeOn_ = false;
bool SystemProperties::faultInjectEnabled_ = false;
bool SystemProperties::imageFileCacheConvertAstc_ = true;
bool SystemProperties::imageFrameworkEnable_ = true;
bool SystemProperties::debugAutoUIEnabled_ = false;
float SystemProperties::dragStartDampingRatio_ = 0.2f;
float SystemProperties::dragStartPanDisThreshold_ = 10.0f;
std::pair<float, float> SystemProperties::brightUpPercent_ = {};
int32_t SystemProperties::imageFileCacheConvertAstcThreshold_ = 3;

bool g_irregularGrid = true;
bool g_segmentedWaterflow = true;

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
    return debugEnabled_;
}

bool SystemProperties::GetLayoutDetectEnabled()
{
    return layoutDetectEnabled_;
}

float SystemProperties::GetAnimationScale()
{
    return defaultAnimationScale;
}

bool SystemProperties::GetIsUseMemoryMonitor()
{
    return false;
}

bool SystemProperties::IsOpIncEnable()
{
    return true;
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

bool SystemProperties::GetGridCacheEnabled()
{
    return gridCacheEnabled_;
}

bool SystemProperties::GetGridIrregularLayoutEnabled()
{
    return g_irregularGrid;
}

bool SystemProperties::WaterFlowUseSegmentedLayout()
{
    return g_segmentedWaterflow;
}

bool SystemProperties::GetSideBarContainerBlurEnable()
{
    return sideBarContainerBlurEnable_;
}

float SystemProperties::GetDefaultResolution()
{
    return 1.0f;
}

std::string SystemProperties::GetAtomicServiceBundleName()
{
    return {};
}

float SystemProperties::GetDragStartDampingRatio()
{
    return dragStartDampingRatio_;
}

float SystemProperties::GetDragStartPanDistanceThreshold()
{
    return dragStartPanDisThreshold_;
}

bool SystemProperties::GetAllowWindowOpenMethodEnabled()
{
    return false;
}

bool SystemProperties::IsSmallFoldProduct()
{
    return false;
}

std::string SystemProperties::GetDebugInspectorId()
{
    return "N/A";
}
} // namespace OHOS::Ace
