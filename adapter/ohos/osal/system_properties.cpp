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

#include <regex>

#include "display_info.h"
#include "display_manager.h"
#include "locale_config.h"
#include "parameter.h"
#include "parameters.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/window_utils.h"
#include "core/common/ace_application_info.h"

#ifdef OHOS_STANDARD_SYSTEM
#include "systemcapability.h"
#endif

namespace OHOS::Ace {
namespace {
constexpr char PROPERTY_DEVICE_TYPE[] = "const.product.devicetype";
constexpr char PROPERTY_NEED_AVOID_WINDOW[] = "const.window.need_avoid_window";
constexpr char PROPERTY_DEVICE_TYPE_DEFAULT[] = "default";
constexpr char PROPERTY_DEVICE_TYPE_TV[] = "tv";
constexpr char PROPERTY_DEVICE_TYPE_TABLET[] = "tablet";
constexpr char PROPERTY_DEVICE_TYPE_TWOINONE[] = "2in1";
constexpr char PROPERTY_DEVICE_TYPE_WATCH[] = "watch";
constexpr char PROPERTY_DEVICE_TYPE_CAR[] = "car";
constexpr char PROPERTY_DEVICE_TYPE_WEARABLE[] = "wearable";
constexpr char PROPERTY_FOLD_TYPE[] = "const.window.foldscreen.type";
constexpr char ENABLE_DEBUG_AUTOUI_KEY[] = "persist.ace.debug.autoui.enabled";
constexpr char ENABLE_DEBUG_BOUNDARY_KEY[] = "persist.ace.debug.boundary.enabled";
constexpr char ENABLE_DOWNLOAD_BY_NETSTACK_KEY[] = "persist.ace.download.netstack.enabled";
constexpr char ENABLE_RECYCLE_IMAGE_KEY[] = "persist.ace.recycle.image.enabled";
constexpr char ENABLE_DEBUG_OFFSET_LOG_KEY[] = "persist.ace.scrollable.log.enabled";
constexpr char ANIMATION_SCALE_KEY[] = "persist.sys.arkui.animationscale";
constexpr char CUSTOM_TITLE_KEY[] = "persist.sys.arkui.customtitle";
constexpr char DISTRIBUTE_ENGINE_BUNDLE_NAME[] = "atomic.service.distribute.engine.bundle.name";
constexpr char IS_OPINC_ENABLE[] = "persist.ddgr.opinctype";
constexpr int32_t ORIENTATION_PORTRAIT = 0;
constexpr int32_t ORIENTATION_LANDSCAPE = 1;
constexpr int DEFAULT_THRESHOLD_JANK = 15;
constexpr float DEFAULT_ANIMATION_SCALE = 1.0f;
float animationScale_ = DEFAULT_ANIMATION_SCALE;
constexpr int32_t DEFAULT_DRAG_START_DAMPING_RATIO = 20;
constexpr int32_t DEFAULT_DRAG_START_PAN_DISTANCE_THRESHOLD_IN_VP = 10;
std::shared_mutex mutex_;
const std::regex FOLD_TYPE_REGEX("^(\\d+)(,\\d+){3,}$");
#ifdef ENABLE_ROSEN_BACKEND
constexpr char DISABLE_ROSEN_FILE_PATH[] = "/etc/disablerosen";
constexpr char DISABLE_WINDOW_ANIMATION_PATH[] = "/etc/disable_window_size_animation";
#endif
constexpr int32_t CONVERT_ASTC_THRESHOLD = 2;
constexpr int32_t FOLD_TYPE_TWO = 2;
constexpr int32_t FOLD_TYPE_FOUR = 4;

bool IsOpIncEnabled()
{
    return (system::GetParameter(IS_OPINC_ENABLE, "2") == "2");
}

void Swap(int32_t& deviceWidth, int32_t& deviceHeight)
{
    int32_t temp = deviceWidth;
    deviceWidth = deviceHeight;
    deviceHeight = temp;
}

bool IsDebugAutoUIEnabled()
{
    return (system::GetParameter(ENABLE_DEBUG_AUTOUI_KEY, "false") == "true");
}

bool IsDebugOffsetLogEnabled()
{
    return (system::GetParameter(ENABLE_DEBUG_OFFSET_LOG_KEY, "false") == "true");
}

bool IsDebugBoundaryEnabled()
{
    return system::GetParameter(ENABLE_DEBUG_BOUNDARY_KEY, "false") == "true";
}

bool IsDownloadByNetworkDisabled()
{
    return system::GetParameter(ENABLE_DOWNLOAD_BY_NETSTACK_KEY, "true") == "true";
}

bool IsRecycleImageEnabled()
{
    return system::GetParameter(ENABLE_RECYCLE_IMAGE_KEY, "true") == "true";
}

bool IsSvgTraceEnabled()
{
    return (system::GetParameter("persist.ace.trace.svg.enabled", "0") == "1");
}

bool IsLayoutTraceEnabled()
{
    return (system::GetParameter("persist.ace.trace.layout.enabled", "false") == "true");
}

bool IsTextTraceEnabled()
{
    return (system::GetParameter("persist.ace.trace.text.enabled", "false") == "true");
}

bool IsSyntaxTraceEnabled()
{
    return (system::GetParameter("persist.ace.trace.syntax.enabled", "false") == "true");
}

bool IsAccessTraceEnabled()
{
    return (system::GetParameter("persist.ace.trace.access.enabled", "false") == "true");
}

bool IsTraceInputEventEnabled()
{
    return (system::GetParameter("persist.ace.trace.inputevent.enabled", "false") == "true");
}

bool IsStateManagerEnable()
{
    return (system::GetParameter("persist.ace.debug.statemgr.enabled", "false") == "true");
}

bool IsBuildTraceEnabled()
{
    return (system::GetParameter("persist.ace.trace.build.enabled", "false") == "true");
}

bool IsSyncDebugTraceEnabled()
{
    return (system::GetParameter("persist.ace.trace.sync.debug.enabled", "false") == "true");
}

bool IsMeasureDebugTraceEnabled()
{
    return (system::GetParameter("persist.ace.trace.measure.debug.enabled", "false") == "true");
}

bool IsSafeAreaDebugTraceEnabled()
{
    return (system::GetParameter("persist.ace.trace.safeArea.debug.enabled", "false") == "true");
}

bool IsVsyncModeDebugTraceEnabled()
{
    return system::GetBoolParameter("persist.ace.trace.vsyncMode.debug.enabled", false);
}

bool IsDeveloperModeOn()
{
    return (system::GetParameter("const.security.developermode.state", "false") == "true");
}

bool IsWindowRectResizeEnabled()
{
    return (system::GetParameter("persist.ace.windowresize.enabled", "true") == "true");
}

bool IsFocusCanBeActive()
{
    return system::GetParameter("persist.gesture.smart_gesture_enable", "1") != "0";
}

bool IsCacheNavigationNodeEnable()
{
    return system::GetParameter("persist.ace.navigation.groupnode.cached", "false") == "true";
}

bool IsHookModeEnabled()
{
#ifdef PREVIEW
    return false;
#endif
    const int bufferLen = 128;
    char paramOutBuf[bufferLen] = { 0 };
    constexpr char hook_mode[] = "startup:";
    int ret = GetParameter("persist.libc.hook_mode", "", paramOutBuf, bufferLen);
    if (ret <= 0 || strncmp(paramOutBuf, hook_mode, strlen(hook_mode)) != 0) {
        return false;
    }
    return true;
}

bool IsRosenBackendEnabled()
{
#ifdef PREVIEW
    return false;
#endif
#ifdef ENABLE_ROSEN_BACKEND
    if (system::GetParameter("persist.ace.rosen.backend.enabled", "0") == "1") {
        return true;
    }
    if (system::GetParameter("persist.ace.rosen.backend.enabled", "0") == "2") {
        return false;
    }
    if (access(DISABLE_ROSEN_FILE_PATH, F_OK) == 0) {
        return false;
    }
    return true;
#else
    return false;
#endif
}

bool IsWindowAnimationEnabled()
{
#ifdef PREVIEW
    return false;
#endif
#ifdef ENABLE_ROSEN_BACKEND
    if (access(DISABLE_WINDOW_ANIMATION_PATH, F_OK) == 0) {
        return false;
    }
    return true;
#else
    return false;
#endif
}

bool IsAccessibilityEnabled()
{
    return (system::GetParameter("persist.ace.testmode.enabled", "0") == "1" ||
            system::GetParameter("debug.ace.testmode.enabled", "0") == "1");
}

bool IsDebugEnabled()
{
    return (system::GetParameter("persist.ace.debug.enabled", "0") == "1");
}

int64_t GetDebugFlags()
{
    return system::GetIntParameter<int64_t>("persist.ace.debug.flags", 0);
}

bool IsContainerDeleteFlag()
{
    return (system::GetParameter("persist.container.delete", "true") == "true");
}

bool IsLayoutDetectEnabled()
{
    return (system::GetParameter("persist.ace.layoutdetect.enabled", "0") == "1");
}

bool IsNavigationBlurEnabled()
{
    return (system::GetParameter("persist.ace.navigation.blur.enabled", "0") == "1");
}

bool IsGridCacheEnabled()
{
    return (system::GetParameter("persist.ace.grid.cache.enabled", "1") == "1");
}

bool IsSideBarContainerBlurEnable()
{
    return (system::GetParameter("persist.ace.sidebar.blur.enabled", "0") == "1");
}

bool IsGpuUploadEnabled()
{
    return (system::GetParameter("persist.ace.gpuupload.enabled", "0") == "1" ||
            system::GetParameter("debug.ace.gpuupload.enabled", "0") == "1");
}

bool IsImageFrameworkEnabled()
{
    return system::GetBoolParameter("persist.ace.image.framework.enabled", true);
}

void OnAnimationScaleChanged(const char* key, const char* value, void* context)
{
    CHECK_NULL_VOID(key);
    if (strcmp(key, ANIMATION_SCALE_KEY) != 0) {
        LOGE("AnimationScale key not matched. key: %{public}s", key);
        return;
    }
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (value == nullptr) {
        LOGW("AnimationScale changes with null value, use default. key: %{public}s", key);
        animationScale_ = DEFAULT_ANIMATION_SCALE;
        return;
    }
    auto animationScale = std::atof(value);
    if (animationScale < 0.0f) {
        LOGE("AnimationScale changes with invalid value: %{public}s. ignore", value);
        return;
    }
    LOGI("AnimationScale: %{public}f -> %{public}f", animationScale_, animationScale);
    animationScale_ = animationScale;
}

uint32_t GetSysDumpFrameCount()
{
    return system::GetUintParameter<uint32_t>(
        "persist.ace.framedumpcount", 10); // 10: Pipeline dump of the last 10 frames' task.
}

bool GetAstcEnabled()
{
    return system::GetParameter("persist.astc.enable", "true") == "true";
}

int32_t GetAstcMaxErrorProp()
{
    return system::GetIntParameter<int>("persist.astc.max", 50000); // 50000: Anomaly threshold of astc.
}

int32_t GetAstcPsnrProp()
{
    return system::GetIntParameter<int>("persist.astc.psnr", 0);
}

bool GetImageFileCacheConvertToAstcEnabled()
{
    return system::GetParameter("persist.image.filecache.astc.enable", "false") == "true";
}

int32_t GetImageFileCacheConvertAstcThresholdProp()
{
    return system::GetIntParameter<int>("persist.image.filecache.astc.threshold", CONVERT_ASTC_THRESHOLD);
}

bool IsUseMemoryMonitor()
{
    return (system::GetParameter("persist.ace.memorymonitor.enabled", "0") == "1");
}

bool IsExtSurfaceEnabled()
{
#ifdef EXT_SURFACE_ENABLE
    return true;
#else
    return false;
#endif
}

bool IsEnableScrollableItemPool()
{
    return system::GetBoolParameter("persist.ace.scrollablepool.enabled", false);
}

bool IsResourceDecoupling()
{
    return system::GetBoolParameter("persist.sys.arkui.resource.decoupling", true);
}

bool IsAcePerformanceMonitorEnabled()
{
    return system::GetBoolParameter("persist.ace.performance.monitor.enabled", false);
}

bool IsAceCommercialLogEnable()
{
    return system::GetParameter("const.logsystem.versiontype", "commercial") == "commercial";
}
} // namespace

float ReadDragStartDampingRatio()
{
    return system::GetIntParameter("debug.ace.drag.damping.ratio", DEFAULT_DRAG_START_DAMPING_RATIO) / 100.0f;
}

float ReadDragStartPanDistanceThreshold()
{
    return system::GetIntParameter("debug.ace.drag.pan.threshold",
        DEFAULT_DRAG_START_PAN_DISTANCE_THRESHOLD_IN_VP) * 1.0f;
}

uint32_t ReadCanvasDebugMode()
{
    return system::GetUintParameter("persist.ace.canvas.debug.mode", 0u);
}

bool IsFaultInjectEnabled()
{
    return (system::GetParameter("persist.ace.fault.inject.enabled", "false") == "true");
}

double ReadScrollableDistance()
{
    auto ret = system::GetParameter("persist.scrollable.distance", "");
    return StringUtils::StringToDouble(ret);
}

std::pair<float, float> GetPercent()
{
    std::vector<double> result;
    StringUtils::StringSplitter(
        system::GetParameter("const.ace.darkModeAppBGColorBrightness", "0.10,0.05"), ',', result);
    std::pair<float, float> percent(result.front(), result.back());
    return percent;
}

int32_t GetPageCountProp()
{
    float pageCount = std::atof(system::GetParameter("persist.ace.cachedcount.page_count", "1.0").c_str());
    return pageCount > 0.0f ? pageCount : 0.0f;
}

bool IsTaskPriorityAdjustmentEnable()
{
    int32_t appVsyncPriority = system::GetIntParameter("const.graphic.app_vsync_priority", -1);
    bool isArkUIEnable = system::GetBoolParameter("persist.sys.arkui.task_priority.enabled", false);
    return appVsyncPriority != -1 && isArkUIEnable;
}

int32_t ReadDragDropFrameworkStatus()
{
    return system::GetIntParameter("debug.ace.drag.drop.framework.status", 0);
}

bool IsAsyncInitializeEnabled()
{
    return system::GetBoolParameter("persist.ace.async.initialize", true);
}

std::atomic<bool> SystemProperties::asyncInitializeEnabled_(IsAsyncInitializeEnabled()); 
bool SystemProperties::svgTraceEnable_ = IsSvgTraceEnabled();
bool SystemProperties::developerModeOn_ = IsDeveloperModeOn();
std::atomic<bool> SystemProperties::layoutTraceEnable_(IsLayoutTraceEnabled() && developerModeOn_);
bool SystemProperties::imageFrameworkEnable_ = IsImageFrameworkEnabled();
std::atomic<bool> SystemProperties::traceInputEventEnable_(IsTraceInputEventEnabled() && developerModeOn_);
std::atomic<bool> SystemProperties::stateManagerEnable_(IsStateManagerEnable());
bool SystemProperties::buildTraceEnable_ = IsBuildTraceEnabled() && developerModeOn_;
bool SystemProperties::cacheNavigationNodeEnable_ = IsCacheNavigationNodeEnable();
bool SystemProperties::syncDebugTraceEnable_ = IsSyncDebugTraceEnabled();
bool SystemProperties::measureDebugTraceEnable_ = IsMeasureDebugTraceEnabled();
bool SystemProperties::safeAreaDebugTraceEnable_ = IsSafeAreaDebugTraceEnabled();
bool SystemProperties::pixelRoundEnable_ = IsPixelRoundEnabled();
bool SystemProperties::textTraceEnable_ = IsTextTraceEnabled();
bool SystemProperties::syntaxTraceEnable_ = IsSyntaxTraceEnabled();
bool SystemProperties::accessTraceEnable_ = IsAccessTraceEnabled();
bool SystemProperties::vsyncModeTraceEnable_ = IsVsyncModeDebugTraceEnabled();
bool SystemProperties::accessibilityEnabled_ = IsAccessibilityEnabled();
bool SystemProperties::isRound_ = false;
bool SystemProperties::isDeviceAccess_ = false;
ACE_WEAK_SYM int32_t SystemProperties::deviceWidth_ = 0;
ACE_WEAK_SYM int32_t SystemProperties::deviceHeight_ = 0;
ACE_WEAK_SYM int32_t SystemProperties::devicePhysicalWidth_ = 0;
ACE_WEAK_SYM int32_t SystemProperties::devicePhysicalHeight_ = 0;
ACE_WEAK_SYM double SystemProperties::resolution_ = 1.0;
ACE_WEAK_SYM DeviceType SystemProperties::deviceType_ { DeviceType::UNKNOWN };
ACE_WEAK_SYM FoldScreenType SystemProperties::foldScreenType_ { FoldScreenType::UNKNOWN };
ACE_WEAK_SYM bool SystemProperties::needAvoidWindow_ { false };
ACE_WEAK_SYM DeviceOrientation SystemProperties::orientation_ { DeviceOrientation::PORTRAIT };
std::string SystemProperties::brand_ = INVALID_PARAM;
std::string SystemProperties::manufacturer_ = INVALID_PARAM;
std::string SystemProperties::model_ = INVALID_PARAM;
std::string SystemProperties::product_ = INVALID_PARAM;
std::string SystemProperties::apiVersion_ = INVALID_PARAM;
std::string SystemProperties::releaseType_ = INVALID_PARAM;
std::string SystemProperties::paramDeviceType_ = INVALID_PARAM;
int32_t SystemProperties::mcc_ = MCC_UNDEFINED;
int32_t SystemProperties::mnc_ = MNC_UNDEFINED;
ACE_WEAK_SYM ColorMode SystemProperties::colorMode_ { ColorMode::LIGHT };
ScreenShape SystemProperties::screenShape_ { ScreenShape::NOT_ROUND };
LongScreenType SystemProperties::LongScreen_ { LongScreenType::NOT_LONG };
bool SystemProperties::unZipHap_ = true;
ACE_WEAK_SYM bool SystemProperties::rosenBackendEnabled_ = IsRosenBackendEnabled();
ACE_WEAK_SYM bool SystemProperties::isHookModeEnabled_ = IsHookModeEnabled();
std::atomic<bool> SystemProperties::debugBoundaryEnabled_(IsDebugBoundaryEnabled() && developerModeOn_);
bool SystemProperties::debugAutoUIEnabled_ = IsDebugAutoUIEnabled();
bool SystemProperties::downloadByNetworkEnabled_ = IsDownloadByNetworkDisabled();
bool SystemProperties::recycleImageEnabled_ = IsRecycleImageEnabled();
bool SystemProperties::debugOffsetLogEnabled_ = IsDebugOffsetLogEnabled();
ACE_WEAK_SYM bool SystemProperties::windowAnimationEnabled_ = IsWindowAnimationEnabled();
ACE_WEAK_SYM bool SystemProperties::debugEnabled_ = IsDebugEnabled();
ACE_WEAK_SYM DebugFlags SystemProperties::debugFlags_ = GetDebugFlags();
ACE_WEAK_SYM bool SystemProperties::containerDeleteFlag_ = IsContainerDeleteFlag();
ACE_WEAK_SYM bool SystemProperties::layoutDetectEnabled_ = IsLayoutDetectEnabled();
bool SystemProperties::gpuUploadEnabled_ = IsGpuUploadEnabled();
bool SystemProperties::astcEnabled_ = GetAstcEnabled();
int32_t SystemProperties::astcMax_ = GetAstcMaxErrorProp();
int32_t SystemProperties::astcPsnr_ = GetAstcPsnrProp();
bool SystemProperties::imageFileCacheConvertAstc_ = GetImageFileCacheConvertToAstcEnabled();
int32_t SystemProperties::imageFileCacheConvertAstcThreshold_ = GetImageFileCacheConvertAstcThresholdProp();
ACE_WEAK_SYM bool SystemProperties::extSurfaceEnabled_ = IsExtSurfaceEnabled();
ACE_WEAK_SYM uint32_t SystemProperties::dumpFrameCount_ = GetSysDumpFrameCount();
ACE_WEAK_SYM bool SystemProperties::windowRectResizeEnabled_ = IsWindowRectResizeEnabled();
bool SystemProperties::enableScrollableItemPool_ = IsEnableScrollableItemPool();
bool SystemProperties::resourceDecoupling_ = IsResourceDecoupling();
bool SystemProperties::navigationBlurEnabled_ = IsNavigationBlurEnabled();
bool SystemProperties::gridCacheEnabled_ = IsGridCacheEnabled();
std::pair<float, float> SystemProperties::brightUpPercent_ = GetPercent();
float SystemProperties::pageCount_ = GetPageCountProp();
bool SystemProperties::sideBarContainerBlurEnable_ = IsSideBarContainerBlurEnable();
std::atomic<bool> SystemProperties::acePerformanceMonitorEnable_(IsAcePerformanceMonitorEnabled());
std::atomic<bool> SystemProperties::focusCanBeActive_(IsFocusCanBeActive());
bool SystemProperties::aceCommercialLogEnable_ = IsAceCommercialLogEnable();
bool SystemProperties::faultInjectEnabled_  = IsFaultInjectEnabled();
bool SystemProperties::opincEnabled_ = IsOpIncEnabled();
float SystemProperties::dragStartDampingRatio_ = ReadDragStartDampingRatio();
float SystemProperties::dragStartPanDisThreshold_ = ReadDragStartPanDistanceThreshold();
uint32_t SystemProperties::canvasDebugMode_ = ReadCanvasDebugMode();
float SystemProperties::fontScale_ = 1.0;
float SystemProperties::fontWeightScale_ = 1.0;
double SystemProperties::scrollableDistance_ = ReadScrollableDistance();
bool SystemProperties::taskPriorityAdjustmentEnable_ = IsTaskPriorityAdjustmentEnable();
int32_t SystemProperties::dragDropFrameworkStatus_ = ReadDragDropFrameworkStatus();
bool SystemProperties::IsOpIncEnable()
{
    return opincEnabled_;
}

bool SystemProperties::IsSyscapExist(const char* cap)
{
#ifdef OHOS_STANDARD_SYSTEM
    return HasSystemCapability(cap);
#else
    return false;
#endif
}

void SystemProperties::InitDeviceType(DeviceType)
{
    // Do nothing, no need to store type here, use system property at 'GetDeviceType' instead.
}

int SystemProperties::GetArkProperties()
{
    return system::GetIntParameter<int>("persist.ark.properties", -1);
}

std::string SystemProperties::GetMemConfigProperty()
{
    return system::GetParameter("persist.ark.mem_config_property", "");
}

std::string SystemProperties::GetArkBundleName()
{
    return system::GetParameter("persist.ark.arkbundlename", "");
}

size_t SystemProperties::GetGcThreadNum()
{
    size_t defaultGcThreadNums = 7;
    return system::GetUintParameter<size_t>("persist.ark.gcthreads", defaultGcThreadNums);
}

size_t SystemProperties::GetLongPauseTime()
{
    size_t defaultLongPauseTime = 40; // 40ms
    return system::GetUintParameter<size_t>("persist.ark.longpausetime", defaultLongPauseTime);
}

bool SystemProperties::GetAsmInterpreterEnabled()
{
    return system::GetParameter("persist.ark.asminterpreter", "true") == "true";
}

std::string SystemProperties::GetAsmOpcodeDisableRange()
{
    return system::GetParameter("persist.ark.asmopcodedisablerange", "");
}

bool SystemProperties::IsScoringEnabled(const std::string& name)
{
    if (name.empty()) {
        return false;
    }
    std::string filePath = "/etc/" + name;
    if (access(filePath.c_str(), F_OK) == 0) {
        return true;
    }
    std::string prop = system::GetParameter("persist.ace.trace.scoringtool", "");
    return prop == name;
}

ACE_WEAK_SYM DeviceType SystemProperties::GetDeviceType()
{
    InitDeviceTypeBySystemProperty();
    return deviceType_;
}

ACE_WEAK_SYM bool SystemProperties::GetNeedAvoidWindow()
{
    return needAvoidWindow_;
}

void SystemProperties::InitDeviceTypeBySystemProperty()
{
    if (deviceType_ != DeviceType::UNKNOWN) {
        return;
    }

    auto deviceProp = system::GetParameter(PROPERTY_DEVICE_TYPE, PROPERTY_DEVICE_TYPE_DEFAULT);
    // Properties: "default", "tv", "tablet", "watch", "car"
    if (deviceProp == PROPERTY_DEVICE_TYPE_TV) {
        deviceType_ = DeviceType::TV;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_CAR) {
        deviceType_ = DeviceType::CAR;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_WATCH) {
        deviceType_ = DeviceType::WATCH;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_TABLET) {
        deviceType_ = DeviceType::TABLET;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_TWOINONE) {
        deviceType_ = DeviceType::TWO_IN_ONE;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_WEARABLE) {
        deviceType_ = DeviceType::WEARABLE;
    } else {
        deviceType_ = DeviceType::PHONE;
    }
}

void SystemProperties::InitDeviceInfo(
    int32_t deviceWidth, int32_t deviceHeight, int32_t orientation, double resolution, bool isRound)
{
    // SetDeviceOrientation should be earlier than deviceWidth/deviceHeight init.
    SetDeviceOrientation(orientation);
    isRound_ = isRound;
    resolution_ = resolution;
    deviceWidth_ = deviceWidth;
    deviceHeight_ = deviceHeight;
    brand_ = ::GetBrand();
    manufacturer_ = ::GetManufacture();
    model_ = ::GetProductModel();
    product_ = ::GetMarketName();
    apiVersion_ = std::to_string(::GetSdkApiVersion());
    releaseType_ = ::GetOsReleaseType();
    paramDeviceType_ = ::GetDeviceType();
    needAvoidWindow_ = system::GetBoolParameter(PROPERTY_NEED_AVOID_WINDOW, false);
    debugEnabled_ = IsDebugEnabled();
    debugFlags_ = GetDebugFlags();
    layoutDetectEnabled_ = IsLayoutDetectEnabled();
    svgTraceEnable_ = IsSvgTraceEnabled();
    layoutTraceEnable_.store(IsLayoutTraceEnabled() && developerModeOn_);
    traceInputEventEnable_.store(IsTraceInputEventEnabled() && developerModeOn_);
    stateManagerEnable_.store(IsStateManagerEnable());
    buildTraceEnable_ = IsBuildTraceEnabled() && developerModeOn_;
    syncDebugTraceEnable_ = IsSyncDebugTraceEnabled();
    measureDebugTraceEnable_ = IsMeasureDebugTraceEnabled();
    safeAreaDebugTraceEnable_ = IsSafeAreaDebugTraceEnabled();
    vsyncModeTraceEnable_ = IsVsyncModeDebugTraceEnabled();
    pixelRoundEnable_ = IsPixelRoundEnabled();
    accessibilityEnabled_ = IsAccessibilityEnabled();
    canvasDebugMode_ = ReadCanvasDebugMode();
    isHookModeEnabled_ = IsHookModeEnabled();
    debugAutoUIEnabled_ = system::GetParameter(ENABLE_DEBUG_AUTOUI_KEY, "false") == "true";
    debugOffsetLogEnabled_ = system::GetParameter(ENABLE_DEBUG_OFFSET_LOG_KEY, "false") == "true";
    downloadByNetworkEnabled_ = system::GetParameter(ENABLE_DOWNLOAD_BY_NETSTACK_KEY, "true") == "true";
    recycleImageEnabled_ = system::GetParameter(ENABLE_RECYCLE_IMAGE_KEY, "true") == "true";
    animationScale_ = std::atof(system::GetParameter(ANIMATION_SCALE_KEY, "1").c_str());
    WatchParameter(ANIMATION_SCALE_KEY, OnAnimationScaleChanged, nullptr);
    resourceDecoupling_ = IsResourceDecoupling();
    navigationBlurEnabled_ = IsNavigationBlurEnabled();
    gridCacheEnabled_ = IsGridCacheEnabled();
    sideBarContainerBlurEnable_ = IsSideBarContainerBlurEnable();
    acePerformanceMonitorEnable_.store(IsAcePerformanceMonitorEnabled());
    asyncInitializeEnabled_.store(IsAsyncInitializeEnabled());
    focusCanBeActive_.store(IsFocusCanBeActive());
    faultInjectEnabled_  = IsFaultInjectEnabled();
    windowRectResizeEnabled_ = IsWindowRectResizeEnabled();
    taskPriorityAdjustmentEnable_ = IsTaskPriorityAdjustmentEnable();
    if (isRound_) {
        screenShape_ = ScreenShape::ROUND;
    } else {
        screenShape_ = ScreenShape::NOT_ROUND;
    }
    InitDeviceTypeBySystemProperty();
}

ACE_WEAK_SYM void SystemProperties::SetDeviceOrientation(int32_t orientation)
{
    auto newOrientation = static_cast<int32_t>(WindowUtils::GetDeviceOrientation(orientation));
    if (newOrientation == ORIENTATION_PORTRAIT && orientation_ != DeviceOrientation::PORTRAIT) {
        Swap(deviceWidth_, deviceHeight_);
        orientation_ = DeviceOrientation::PORTRAIT;
    } else if (newOrientation == ORIENTATION_LANDSCAPE && orientation_ != DeviceOrientation::LANDSCAPE) {
        Swap(deviceWidth_, deviceHeight_);
        orientation_ = DeviceOrientation::LANDSCAPE;
    }
}

ACE_WEAK_SYM float SystemProperties::GetFontWeightScale()
{
    // Default value of font weight scale is 1.0.
    return fontWeightScale_;
}

ACE_WEAK_SYM float SystemProperties::GetFontScale()
{
    // Default value of font size scale is 1.0.
    return fontScale_;
}

bool SystemProperties::GetContainerDeleteFlag()
{
    return containerDeleteFlag_;
}

void SystemProperties::InitMccMnc(int32_t mcc, int32_t mnc)
{
    mcc_ = mcc;
    mnc_ = mnc;
}

ACE_WEAK_SYM bool SystemProperties::GetDebugEnabled()
{
    return debugEnabled_;
}

ACE_WEAK_SYM bool SystemProperties::GetLayoutDetectEnabled()
{
    return layoutDetectEnabled_;
}

std::string SystemProperties::GetLanguage()
{
    return system::GetParameter("const.global.language", INVALID_PARAM);
}

std::string SystemProperties::GetRegion()
{
    return system::GetParameter("const.global.region", INVALID_PARAM);
}

std::string SystemProperties::GetNewPipePkg()
{
    return system::GetParameter("persist.ace.newpipe.pkgname", "");
}

ACE_WEAK_SYM float SystemProperties::GetAnimationScale()
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return animationScale_;
}

std::string SystemProperties::GetPartialUpdatePkg()
{
    return system::GetParameter("persist.ace.partial.pkgname", "");
}

int32_t SystemProperties::GetSvgMode()
{
#ifdef NG_BUILD
    // disable ace svg before updated to new pipeline
    return system::GetIntParameter<int>("persist.ace.svg.mode", 0);
#else
    return system::GetIntParameter<int>("persist.ace.svg.mode", 1);
#endif
}

bool SystemProperties::GetAllowWindowOpenMethodEnabled()
{
    return system::GetBoolParameter("persist.web.allowWindowOpenMethod.enabled", false);
}

bool SystemProperties::GetDebugPixelMapSaveEnabled()
{
    return system::GetBoolParameter("persist.ace.save.pixelmap.enabled", false);
}

bool SystemProperties::IsPixelRoundEnabled()
{
    return system::GetBoolParameter("ace.debug.pixelround.enabled", true);
}

ACE_WEAK_SYM bool SystemProperties::GetIsUseMemoryMonitor()
{
    static bool isUseMemoryMonitor = IsUseMemoryMonitor();
    return isUseMemoryMonitor;
}

bool SystemProperties::IsFormAnimationLimited()
{
    return system::GetBoolParameter("persist.sys.arkui.formAnimationLimit", true);
}

bool SystemProperties::GetResourceDecoupling()
{
    return resourceDecoupling_;
}

bool SystemProperties::GetTitleStyleEnabled()
{
    return system::GetBoolParameter("persist.ace.title.style.enabled", false);
}

int32_t SystemProperties::GetJankFrameThreshold()
{
    return system::GetIntParameter<int>("persist.sys.arkui.perf.threshold", DEFAULT_THRESHOLD_JANK);
}

ACE_WEAK_SYM std::string SystemProperties::GetCustomTitleFilePath()
{
    return system::GetParameter(CUSTOM_TITLE_KEY, "");
}

ACE_WEAK_SYM bool SystemProperties::Is24HourClock()
{
    return Global::I18n::LocaleConfig::Is24HourClock();
}

std::optional<bool> SystemProperties::GetRtlEnabled()
{
    const std::string emptyParam("none");
    auto ret = system::GetParameter("debug.ace.rtl.enabled", emptyParam);
    if (ret == emptyParam) {
        return std::nullopt;
    } else {
        return (ret == "true") ? true : false;
    }
}

bool SystemProperties::GetDisplaySyncSkipEnabled()
{
    return system::GetBoolParameter("debug.ace.displaySyncSkip.enabled", true);
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
    return system::GetBoolParameter("persist.ace.grid.irregular.enabled", false);
}

bool SystemProperties::WaterFlowUseSegmentedLayout()
{
    return system::GetBoolParameter("persist.ace.water.flow.segmented", false);
}

bool SystemProperties::GetSideBarContainerBlurEnable()
{
    return sideBarContainerBlurEnable_;
}

void SystemProperties::AddWatchSystemParameter(const char* key, void* context, EnableSystemParameterCallback callback)
{
    WatchParameter(key, callback, context);
}

ACE_WEAK_SYM bool SystemProperties::GetWindowRectResizeEnabled()
{
    return windowRectResizeEnabled_;
}

void SystemProperties::RemoveWatchSystemParameter(
    const char* key, void* context, EnableSystemParameterCallback callback)
{
    RemoveParameterWatcher(key, callback, context);
}

void SystemProperties::EnableSystemParameterTraceLayoutCallback(const char* key, const char* value, void* context)
{
    if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0) {
        SetLayoutTraceEnabled(strcmp(value, "true") == 0);
    }
}

void SystemProperties::EnableSystemParameterTraceInputEventCallback(const char* key, const char* value, void* context)
{
    if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0) {
        SetInputEventTraceEnabled(strcmp(value, "true") == 0);
    }
}

void SystemProperties::EnableSystemParameterSecurityDevelopermodeCallback(
    const char* key, const char* value, void* context)
{
    if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0) {
        SetSecurityDevelopermodeLayoutTraceEnabled(strcmp(value, "true") == 0);
    }
}

void SystemProperties::EnableSystemParameterDebugStatemgrCallback(const char* key, const char* value, void* context)
{
    if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0) {
        SetStateManagerEnabled(strcmp(value, "true") == 0);
    }
}

void SystemProperties::EnableSystemParameterDebugBoundaryCallback(const char* key, const char* value, void* context)
{
    bool isDebugBoundary = strcmp(value, "true") == 0;
    SetDebugBoundaryEnabled(isDebugBoundary);
    auto container = reinterpret_cast<Platform::AceContainer*>(context);
    CHECK_NULL_VOID(container);
    container->RenderLayoutBoundary(isDebugBoundary);
}

void SystemProperties::EnableSystemParameterPerformanceMonitorCallback(const char* key, const char* value,
    void* context)
{
    if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0) {
        SetPerformanceMonitorEnabled(strcmp(value, "true") == 0);
    }
}

void SystemProperties::OnFocusActiveChanged(const char* key, const char* value, void* context)
{
    bool focusCanBeActive = true;
    if (value && strcmp(value, "0") == 0) {
        focusCanBeActive = false;
    }
    if (focusCanBeActive != focusCanBeActive_) {
        SetFocusCanBeActive(focusCanBeActive);
        if (!focusCanBeActive) {
            auto container = reinterpret_cast<Platform::AceContainer*>(context);
            CHECK_NULL_VOID(container);
            container->SetIsFocusActive(focusCanBeActive);
        }
        LOGI("focusCanBeActive turns to %{public}d", focusCanBeActive);
    }
    return;
}

float SystemProperties::GetDefaultResolution()
{
    // always return density of main screen, don't use this interface unless you need density when no window exists
    float density = 1.0f;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    CHECK_NULL_RETURN(defaultDisplay, density);
    auto displayInfo = defaultDisplay->GetDisplayInfoWithCache();
    CHECK_NULL_RETURN(displayInfo, density);
    density = displayInfo->GetVirtualPixelRatio();
    return density;
}

void SystemProperties::SetLayoutTraceEnabled(bool layoutTraceEnable)
{
    layoutTraceEnable_.store(layoutTraceEnable && developerModeOn_);
}

void SystemProperties::SetInputEventTraceEnabled(bool inputEventTraceEnable)
{
    traceInputEventEnable_.store(inputEventTraceEnable && developerModeOn_);
}

void SystemProperties::SetSecurityDevelopermodeLayoutTraceEnabled(bool layoutTraceEnable)
{
    layoutTraceEnable_.store(layoutTraceEnable && IsLayoutTraceEnabled());
}

void SystemProperties::SetDebugBoundaryEnabled(bool debugBoundaryEnabled)
{
    debugBoundaryEnabled_.store(debugBoundaryEnabled && developerModeOn_);
}

void SystemProperties::SetPerformanceMonitorEnabled(bool performanceMonitorEnable)
{
    acePerformanceMonitorEnable_.store(performanceMonitorEnable);
}

void SystemProperties::SetFocusCanBeActive(bool focusCanBeActive)
{
    focusCanBeActive_.store(focusCanBeActive);
}

std::string SystemProperties::GetAtomicServiceBundleName()
{
    return system::GetParameter(DISTRIBUTE_ENGINE_BUNDLE_NAME, "");
}

float SystemProperties::GetDragStartDampingRatio()
{
    return dragStartDampingRatio_;
}

float SystemProperties::GetDragStartPanDistanceThreshold()
{
    return dragStartPanDisThreshold_;
}

ACE_WEAK_SYM bool SystemProperties::IsSmallFoldProduct()
{
    InitFoldScreenTypeBySystemProperty();
    return foldScreenType_ == FoldScreenType::SMALL_FOLDER;
}

ACE_WEAK_SYM bool SystemProperties::IsBigFoldProduct()
{
    InitFoldScreenTypeBySystemProperty();
    return foldScreenType_ == FoldScreenType::BIG_FOLDER;
}

void SystemProperties::InitFoldScreenTypeBySystemProperty()
{
    if (foldScreenType_ != FoldScreenType::UNKNOWN) {
        return;
    }

    auto foldTypeProp = system::GetParameter(PROPERTY_FOLD_TYPE, "0,0,0,0");
    if (std::regex_match(foldTypeProp, FOLD_TYPE_REGEX)) {
        auto index = foldTypeProp.find_first_of(',');
        auto foldScreenTypeStr = foldTypeProp.substr(0, index);
        auto type = StringUtils::StringToInt(foldScreenTypeStr);
        if (type == FOLD_TYPE_FOUR) {
            type = FOLD_TYPE_TWO;
        }
        foldScreenType_ = static_cast<FoldScreenType>(type);
    }
}

std::string SystemProperties::GetWebDebugRenderMode()
{
    return OHOS::system::GetParameter("web.debug.renderMode", "");
}

std::string SystemProperties::GetDebugInspectorId()
{
    return system::GetParameter("ace.debug.inspectorId", INVALID_PARAM);
}

double SystemProperties::GetSrollableVelocityScale()
{
    auto ret = system::GetParameter("persist.scrollable.velocityScale", "");
    return StringUtils::StringToDouble(ret);
}

double SystemProperties::GetSrollableFriction()
{
    auto ret = system::GetParameter("persist.scrollable.friction", "");
    return StringUtils::StringToDouble(ret);
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

bool SystemProperties::IsSuperFoldDisplayDevice()
{
    InitFoldScreenTypeBySystemProperty();
    return foldScreenType_ == FoldScreenType::SUPER_FOLDER;
}
} // namespace OHOS::Ace
