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

#include "base/utils/system_properties.h"

#include "base/log/log.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t ORIENTATION_PORTRAIT = 0;
constexpr int32_t ORIENTATION_LANDSCAPE = 1;
constexpr char PROPERTY_DEVICE_TYPE_PHONE[] = "phone";
constexpr char PROPERTY_DEVICE_TYPE_TV[] = "tv";
constexpr char PROPERTY_DEVICE_TYPE_TABLET[] = "tablet";
constexpr char PROPERTY_DEVICE_TYPE_TWO_IN_ONE[] = "2in1";
constexpr char PROPERTY_DEVICE_TYPE_WEARABLE[] = "wearable";
constexpr char PROPERTY_DEVICE_TYPE_CAR[] = "car";

static constexpr char UNDEFINED_PARAM[] = "undefined parameter";

void Swap(int32_t& deviceWidth, int32_t& deviceHeight)
{
    int32_t temp = deviceWidth;
    deviceWidth = deviceHeight;
    deviceHeight = temp;
}
} // namespace

bool SystemProperties::svgTraceEnable_ = false;
bool SystemProperties::developerModeOn_ = false;
std::atomic<bool> SystemProperties::layoutTraceEnable_(false);
std::atomic<bool> SystemProperties::traceInputEventEnable_(false);
std::atomic<bool> SystemProperties::stateManagerEnable_(false);
bool SystemProperties::buildTraceEnable_ = false;
bool SystemProperties::syncDebugTraceEnable_ = false;
bool SystemProperties::measureDebugTraceEnable_ = false;
bool SystemProperties::safeAreaDebugTraceEnable_ = false;
bool SystemProperties::pixelRoundEnable_ = true;
bool SystemProperties::textTraceEnable_ = false;
bool SystemProperties::syntaxTraceEnable_ = false;
bool SystemProperties::accessTraceEnable_ = false;
bool SystemProperties::vsyncModeTraceEnable_ = false;
bool SystemProperties::accessibilityEnabled_ = false;
bool SystemProperties::isRound_ = false;
bool SystemProperties::isDeviceAccess_ = false;
int32_t SystemProperties::deviceWidth_ = 0;
int32_t SystemProperties::deviceHeight_ = 0;
int32_t SystemProperties::devicePhysicalWidth_ = 0;
int32_t SystemProperties::devicePhysicalHeight_ = 0;
double SystemProperties::resolution_ = 1.0;
DeviceType SystemProperties::deviceType_ { DeviceType::PHONE };
DeviceOrientation SystemProperties::orientation_ { DeviceOrientation::PORTRAIT };
std::string SystemProperties::brand_ = UNDEFINED_PARAM;
std::string SystemProperties::manufacturer_ = UNDEFINED_PARAM;
std::string SystemProperties::model_ = UNDEFINED_PARAM;
std::string SystemProperties::product_ = UNDEFINED_PARAM;
std::string SystemProperties::apiVersion_ = "9";
std::string SystemProperties::releaseType_ = UNDEFINED_PARAM;
std::string SystemProperties::paramDeviceType_ = UNDEFINED_PARAM;
int32_t SystemProperties::mcc_ = MCC_UNDEFINED;
int32_t SystemProperties::mnc_ = MNC_UNDEFINED;
ColorMode SystemProperties::colorMode_ = ColorMode::LIGHT;
ScreenShape SystemProperties::screenShape_ { ScreenShape::NOT_ROUND };
LongScreenType SystemProperties::LongScreen_ { LongScreenType::NOT_LONG };
bool SystemProperties::unZipHap_ = true;
bool SystemProperties::windowAnimationEnabled_ = false;
std::atomic<bool> SystemProperties::debugBoundaryEnabled_(false);
bool SystemProperties::debugAutoUIEnabled_ = false;
bool SystemProperties::debugOffsetLogEnabled_ = false;
bool SystemProperties::downloadByNetworkEnabled_ = false;
bool SystemProperties::recycleImageEnabled_ = false;
bool SystemProperties::gpuUploadEnabled_ = false;
bool SystemProperties::isHookModeEnabled_ = false;
bool SystemProperties::astcEnabled_ = false;
int SystemProperties::astcMax_ = 0;
int SystemProperties::astcPsnr_ = 0;
bool SystemProperties::imageFileCacheConvertAstc_ = false;
int32_t SystemProperties::imageFileCacheConvertAstcThreshold_ = 2;
bool SystemProperties::extSurfaceEnabled_ = false;
uint32_t SystemProperties::dumpFrameCount_ = 0;
bool SystemProperties::resourceDecoupling_ = true;
#ifndef ENABLE_ROSEN_BACKEND
bool SystemProperties::rosenBackendEnabled_ = false;
#else
bool SystemProperties::rosenBackendEnabled_ = true;
#endif
bool SystemProperties::enableScrollableItemPool_ = false;
bool SystemProperties::navigationBlurEnabled_ = true;
bool SystemProperties::gridCacheEnabled_ = false;
bool SystemProperties::sideBarContainerBlurEnable_ = false;
std::atomic<bool> SystemProperties::acePerformanceMonitorEnable_(false);
std::atomic<bool> SystemProperties::asyncInitializeEnabled_(true);
std::atomic<bool> SystemProperties::focusCanBeActive_(true);
bool SystemProperties::aceCommercialLogEnable_ = false;
std::pair<float, float> SystemProperties::brightUpPercent_ = {};
bool SystemProperties::faultInjectEnabled_ = false;
bool SystemProperties::imageFrameworkEnable_ = false;
float SystemProperties::pageCount_ = 1.0f;
float SystemProperties::dragStartDampingRatio_ = 0.2f;
float SystemProperties::dragStartPanDisThreshold_ = 10.0f;
uint32_t SystemProperties::canvasDebugMode_ = 0;
double SystemProperties::scrollableDistance_ = 0.0;
bool SystemProperties::taskPriorityAdjustmentEnable_ = false;
int32_t SystemProperties::dragDropFrameworkStatus_ = 0;

bool SystemProperties::IsOpIncEnable()
{
    return false;
}

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
        deviceType_ = DeviceType::TABLET;
        paramDeviceType_ = PROPERTY_DEVICE_TYPE_TABLET;
    } else if (type == DeviceType::TWO_IN_ONE) {
        deviceType_ = DeviceType::TWO_IN_ONE;
        paramDeviceType_ = PROPERTY_DEVICE_TYPE_TWO_IN_ONE;
    } else {
        deviceType_ = DeviceType::PHONE;
        paramDeviceType_ = PROPERTY_DEVICE_TYPE_PHONE;
    }
}

DeviceType SystemProperties::GetDeviceType()
{
    return deviceType_;
}

bool SystemProperties::IsSyscapExist(const char* cap)
{
    return false;
}

void SystemProperties::InitDeviceTypeBySystemProperty()
{
    deviceType_ = DeviceType::PHONE;
}

void SystemProperties::InitDeviceInfo(
    int32_t deviceWidth, int32_t deviceHeight, int32_t orientation, double resolution, bool isRound)
{
    // SetDeviceOrientation should be eralier than deviceWidth/deviceHeight init.
    if (orientation == ORIENTATION_PORTRAIT) {
        orientation_ = DeviceOrientation::PORTRAIT;
    } else if (orientation == ORIENTATION_LANDSCAPE) {
        orientation_ = DeviceOrientation::LANDSCAPE;
    } else {
        LOGW("SetDeviceOrientation, undefined orientation");
    }

    isRound_ = isRound;
    resolution_ = resolution;
    deviceWidth_ = deviceWidth;
    deviceHeight_ = deviceHeight;
    if (isRound_) {
        screenShape_ = ScreenShape::ROUND;
    } else {
        screenShape_ = ScreenShape::NOT_ROUND;
    }
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
        LOGI("SetDeviceOrientation, no change info: %{public}d", orientation);
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

bool SystemProperties::IsScoringEnabled(const std::string& name)
{
    return false;
}

bool SystemProperties::GetDebugEnabled()
{
    return false;
}

bool SystemProperties::GetLayoutDetectEnabled()
{
    return false;
}

std::string SystemProperties::GetLanguage()
{
    return UNDEFINED_PARAM;
}

std::string SystemProperties::GetRegion()
{
    return UNDEFINED_PARAM;
}

std::string SystemProperties::GetPartialUpdatePkg()
{
    return {};
}

std::string SystemProperties::GetNewPipePkg()
{
    return {};
}

int32_t SystemProperties::GetSvgMode()
{
    return 1;
}

bool SystemProperties::GetIsUseMemoryMonitor()
{
    return false;
}

bool SystemProperties::IsFormAnimationLimited()
{
    return true;
}

bool SystemProperties::GetDebugPixelMapSaveEnabled()
{
    return false;
}

bool SystemProperties::GetResourceDecoupling()
{
    return true;
}

bool SystemProperties::GetTitleStyleEnabled()
{
    return false;
}

int32_t SystemProperties::GetJankFrameThreshold()
{
    return 0;
}

std::string SystemProperties::GetCustomTitleFilePath()
{
    return UNDEFINED_PARAM;
}

bool SystemProperties::Is24HourClock()
{
    return false;
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
    return false;
}

bool SystemProperties::WaterFlowUseSegmentedLayout()
{
    return false;
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
    return UNDEFINED_PARAM;
}

float SystemProperties::GetDragStartDampingRatio()
{
    return dragStartDampingRatio_;
}

float SystemProperties::GetDragStartPanDistanceThreshold()
{
    return dragStartPanDisThreshold_;
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
    return UNDEFINED_PARAM;
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
    return scrollableDistance_;
}

bool SystemProperties::IsNeedResampleTouchPoints()
{
    return true;
}

bool SystemProperties::IsNeedSymbol()
{
    return true;
}

int32_t SystemProperties::GetDragDropFrameworkStatus()
{
    return dragDropFrameworkStatus_;
}

bool SystemProperties::GetContainerDeleteFlag()
{
    return false;
}

bool SystemProperties::IsSuperFoldDisplayDevice()
{
    return false;
}
} // namespace OHOS::Ace
