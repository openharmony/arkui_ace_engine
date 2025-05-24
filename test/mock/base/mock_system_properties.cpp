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
namespace MockSystemProperties {
bool g_isSuperFoldDisplayDevice = false;
}
namespace {
constexpr int32_t ORIENTATION_PORTRAIT = 0;
constexpr int32_t ORIENTATION_LANDSCAPE = 1;
constexpr int32_t DEFAULT_FORM_SHARED_IMAGE_CACHE_THRESHOLD = 20;

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
bool SystemProperties::measureDebugTraceEnable_ = false;
bool SystemProperties::safeAreaDebugTraceEnable_ = false;
bool SystemProperties::pixelRoundEnable_ = true;
bool SystemProperties::textTraceEnable_ = false;
bool SystemProperties::vsyncModeTraceEnable_ = false;
bool SystemProperties::syntaxTraceEnable_ = false;
double SystemProperties::resolution_ = 0.0;
constexpr float defaultAnimationScale = 1.0f;
bool SystemProperties::extSurfaceEnabled_ = false;
uint32_t SystemProperties::dumpFrameCount_ = 0;
bool SystemProperties::debugEnabled_ = false;
DebugFlags SystemProperties::debugFlags_ = 0;
bool SystemProperties::containerDeleteFlag_ = false;
bool SystemProperties::layoutDetectEnabled_ = false;
int32_t SystemProperties::deviceWidth_ = 720;
int32_t SystemProperties::deviceHeight_ = 1280;
bool SystemProperties::debugOffsetLogEnabled_ = false;
bool SystemProperties::downloadByNetworkEnabled_ = false;
bool SystemProperties::recycleImageEnabled_ = false;
int32_t SystemProperties::devicePhysicalWidth_ = 0;
int32_t SystemProperties::devicePhysicalHeight_ = 0;
bool SystemProperties::enableScrollableItemPool_ = false;
bool SystemProperties::navigationBlurEnabled_ = false;
bool SystemProperties::cacheNavigationNodeEnable_ = false;
bool SystemProperties::gridCacheEnabled_ = true;
bool SystemProperties::sideBarContainerBlurEnable_ = false;
std::atomic<bool> SystemProperties::stateManagerEnable_(false);
std::atomic<bool> SystemProperties::acePerformanceMonitorEnable_(false);
std::atomic<bool> SystemProperties::focusCanBeActive_(true);
bool SystemProperties::aceCommercialLogEnable_ = false;
std::atomic<bool> SystemProperties::debugBoundaryEnabled_(false);
bool SystemProperties::developerModeOn_ = false;
bool SystemProperties::faultInjectEnabled_ = false;
bool SystemProperties::imageFileCacheConvertAstc_ = true;
bool SystemProperties::imageFrameworkEnable_ = true;
bool SystemProperties::debugAutoUIEnabled_ = false;
float SystemProperties::dragStartDampingRatio_ = 0.2f;
float SystemProperties::dragStartPanDisThreshold_ = 10.0f;
float SystemProperties::pageCount_ = 0.0f;
std::pair<float, float> SystemProperties::brightUpPercent_ = {};
int32_t SystemProperties::imageFileCacheConvertAstcThreshold_ = 3;
bool SystemProperties::taskPriorityAdjustmentEnable_ = false;
int32_t SystemProperties::dragDropFrameworkStatus_ = 0;
bool SystemProperties::multiInstanceEnabled_ = false;
bool SystemProperties::pageTransitionFrzEnabled_ = false;
bool SystemProperties::formSkeletonBlurEnabled_ = true;
int32_t SystemProperties::formSharedImageCacheThreshold_ = DEFAULT_FORM_SHARED_IMAGE_CACHE_THRESHOLD;

bool g_irregularGrid = true;
bool g_segmentedWaterflow = true;
bool g_isNeedSymbol = true;

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

bool SystemProperties::GetMultiInstanceEnabled()
{
    return multiInstanceEnabled_;
}

void SystemProperties::SetMultiInstanceEnabled(bool enabled)
{
    multiInstanceEnabled_ = enabled;
}

bool SystemProperties::IsSyscapExist(const char* cap)
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

bool SystemProperties::GetCacheNavigationNodeEnable()
{
    return cacheNavigationNodeEnable_;
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

bool SystemProperties::IsBigFoldProduct()
{
    return false;
}

std::string SystemProperties::GetDebugInspectorId()
{
    return "N/A";
}

double SystemProperties::GetSrollableVelocityScale()
{
    return 0.0;
}

double SystemProperties::GetSrollableFriction()
{
    return 0.0;
}

double SystemProperties::GetScrollableDistance()
{
    return 0.0;
}

bool SystemProperties::GetWebDebugMaximizeResizeOptimize()
{
    return true;
}

bool SystemProperties::IsNeedResampleTouchPoints()
{
    return true;
}

bool SystemProperties::IsNeedSymbol()
{
    return g_isNeedSymbol;
}

bool SystemProperties::GetResourceDecoupling()
{
    return true;
}

bool SystemProperties::ConfigChangePerform()
{
    return false;
}

int32_t SystemProperties::GetDragDropFrameworkStatus()
{
    return dragDropFrameworkStatus_;
}

bool SystemProperties::GetContainerDeleteFlag()
{
    return containerDeleteFlag_;
}

bool SystemProperties::IsSuperFoldDisplayDevice()
{
    return MockSystemProperties::g_isSuperFoldDisplayDevice;
}

bool SystemProperties::IsPageTransitionFreeze()
{
    return pageTransitionFrzEnabled_;
}

bool SystemProperties::IsFormSkeletonBlurEnabled()
{
    return formSkeletonBlurEnabled_;
}

int32_t SystemProperties::getFormSharedImageCacheThreshold()
{
    return formSharedImageCacheThreshold_;
}
} // namespace OHOS::Ace
