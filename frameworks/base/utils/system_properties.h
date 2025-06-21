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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_SYSTEM_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_SYSTEM_PROPERTIES_H

#include <atomic>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>

#include "base/utils/device_config.h"
#include "base/utils/device_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {

enum class ResolutionType : int32_t {
    RESOLUTION_NONE = -2,
    RESOLUTION_ANY = -1,
    RESOLUTION_LDPI = 120,
    RESOLUTION_MDPI = 160,
    RESOLUTION_HDPI = 240,
    RESOLUTION_XHDPI = 320,
    RESOLUTION_XXHDPI = 480,
    RESOLUTION_XXXHDPI = 640,
};

enum class FoldScreenType: int32_t {
    UNKNOWN = 0,
    BIG_FOLDER = 1,
    SMALL_FOLDER = 2,
    OUTER_FOLDER = 3,
    SUPER_FOLDER = 5,
};

constexpr int32_t MCC_UNDEFINED = 0;
constexpr int32_t MNC_UNDEFINED = 0;
extern const char ENABLE_DEBUG_BOUNDARY_KEY[];
extern const char ENABLE_TRACE_LAYOUT_KEY[];
extern const char ENABLE_TRACE_INPUTEVENT_KEY[];
extern const char ENABLE_SECURITY_DEVELOPERMODE_KEY[];
extern const char ENABLE_DEBUG_STATEMGR_KEY[];

enum class LongScreenType : int32_t {
    LONG = 0,
    NOT_LONG,
    LONG_SCREEN_UNDEFINED,
};

enum class ScreenShape : int32_t {
    ROUND = 0,
    NOT_ROUND,
    SCREEN_SHAPE_UNDEFINED,
};

union DebugFlags {
    DebugFlags(int64_t flag = 0) : flag_(flag) {}
    int64_t flag_;
    struct {
        bool containerMultiThread_ : 1;
        bool getHostOnDetach_ : 1;
        bool claimDeathObj_ : 1;
        bool aceObjTypeCvt_ : 1;
        bool jsObjTypeCvt_ : 1;
        bool objDestroyInUse_ : 1;
        bool useInvalidIter_ : 1;
    } bits_;
};

struct WidthLayoutBreakPoint {
    double widthVPXS_ = 320.0;
    double widthVPSM_ = 600.0;
    double widthVPMD_ = 840.0;
    double widthVPLG_ = 1440.0;
    WidthLayoutBreakPoint() = default;
    WidthLayoutBreakPoint(double widthVPXS, double widthVPSM, double widthVPMD, double widthVPLG)
        : widthVPXS_(widthVPXS), widthVPSM_(widthVPSM), widthVPMD_(widthVPMD), widthVPLG_(widthVPLG) {}
};

struct HeightLayoutBreakPoint {
    double heightVPRATIOSM_ = 0.8;
    double heightVPRATIOMD_ = 1.2;
    HeightLayoutBreakPoint() = default;
    HeightLayoutBreakPoint(double heightVPRATIOSM, double heightVPRATIOMD)
        : heightVPRATIOSM_(heightVPRATIOSM), heightVPRATIOMD_(heightVPRATIOMD) {}
};

class ACE_FORCE_EXPORT SystemProperties final {
public:
    /*
     * Init device type for Ace.
     */
    static void InitDeviceType(DeviceType deviceType);

    /*
     * Init device info for Ace.
     */
    static void InitDeviceInfo(
        int32_t deviceWidth, int32_t deviceHeight, int32_t orientation, double resolution, bool isRound);

    /*
     * Init device type according to system property.
     */
    static void InitDeviceTypeBySystemProperty();

    /**
     * Init fold screen type according to system property.
     */
    static void InitFoldScreenTypeBySystemProperty();

    /*
     * Get type of current device.
     */
    static DeviceType GetDeviceType();

    /*
     * Get if current device need avoid window.
     */
    static bool GetNeedAvoidWindow();

    /*
     * check SystemCapability.
     */
    static bool IsSyscapExist(const char* cap);
    /*
     * check ApiVersion.
     */
    static bool IsApiVersionGreaterOrEqual(int majorVersion, int minorVersion, int patchVersion);

    /**
     * Set type of current device.
     * @param deviceType
     */
    static void SetDeviceType(DeviceType deviceType)
    {
        deviceType_ = deviceType;
    }

    /*
     * Get current orientation of device.
     */
    static DeviceOrientation GetDeviceOrientation()
    {
        return orientation_;
    }

    /*
     * Get width of device.
     */
    static int32_t GetDeviceWidth()
    {
        return deviceWidth_;
    }

    /*
     * Get height of device.
     */
    static int32_t GetDeviceHeight()
    {
        return deviceHeight_;
    }

    /*
     * Set physical width of device.
     */
    static void SetDevicePhysicalWidth(int32_t devicePhysicalWidth)
    {
        devicePhysicalWidth_ = devicePhysicalWidth;
    }

    /*
     * Set physical height of device.
     */
    static void SetDevicePhysicalHeight(int32_t devicePhysicalHeight)
    {
        devicePhysicalHeight_ = devicePhysicalHeight;
    }

    /*
     * Get physical width of device.
     */
    static int32_t GetDevicePhysicalWidth()
    {
        return devicePhysicalWidth_;
    }

    /*
     * Get physical height of device.
     */
    static int32_t GetDevicePhysicalHeight()
    {
        return devicePhysicalHeight_;
    }

    /*
     * Get wght scale of device.
     */
    static float GetFontWeightScale();

    static void SetFontWeightScale(const float fontWeightScale)
    {
        if (fontWeightScale_ != fontWeightScale) {
            fontWeightScale_ = fontWeightScale;
        }
    }

    /*
     * Get size scale of device.
     */
    static float GetFontScale();

    static void SetFontScale(const float fontScale)
    {
        if (fontScale != fontScale_) {
            fontScale_ = fontScale;
        }
    }

    /*
     * Get density of default display.
     */
    static double GetResolution()
    {
        return resolution_;
    }

    /*
     * Set resolution of device.
     */
    static void SetResolution(double resolution)
    {
        resolution_ = resolution;
    }

    static bool GetIsScreenRound()
    {
        return isRound_;
    }

    static const std::string& GetBrand()
    {
        return brand_;
    }

    static const std::string& GetManufacturer()
    {
        return manufacturer_;
    }

    static const std::string& GetModel()
    {
        return model_;
    }

    static const std::string& GetProduct()
    {
        return product_;
    }

    static const std::string& GetApiVersion()
    {
        return apiVersion_;
    }

    static const std::string& GetReleaseType()
    {
        return releaseType_;
    }

    static const std::string& GetParamDeviceType()
    {
        return paramDeviceType_;
    }

    static std::string GetLanguage();

    static bool GetContainerDeleteFlag();

    static std::string GetRegion();

    static std::string GetNewPipePkg();

    static float GetAnimationScale();

    static std::string GetPartialUpdatePkg();

    static int32_t GetSvgMode();

    static bool GetDebugPixelMapSaveEnabled();

    static bool IsPixelRoundEnabled();

    static bool GetRosenBackendEnabled()
    {
        return rosenBackendEnabled_;
    }

    static bool GetHookModeEnabled()
    {
        return isHookModeEnabled_;
    }

    static bool GetDeveloperModeOn()
    {
        return developerModeOn_;
    }

    static bool GetDebugBoundaryEnabled()
    {
        return debugBoundaryEnabled_.load();
    }

    static bool GetDebugOffsetLogEnabled()
    {
        return debugOffsetLogEnabled_;
    }

    static bool GetDebugAutoUIEnabled()
    {
        return debugAutoUIEnabled_;
    }

    static bool GetDownloadByNetworkEnabled()
    {
        return downloadByNetworkEnabled_;
    }

    static bool GetRecycleImageEnabled()
    {
        return recycleImageEnabled_;
    }

    static bool GetSvgTraceEnabled()
    {
        return svgTraceEnable_;
    }

    static bool GetLayoutTraceEnabled()
    {
        return layoutTraceEnable_.load();
    }

    static bool GetSyncDebugTraceEnabled()
    {
        return syncDebugTraceEnable_;
    }

    static bool GetPixelRoundEnabled()
    {
        return pixelRoundEnable_;
    }

    static bool GetTextTraceEnabled()
    {
        return textTraceEnable_;
    }

    static bool GetSyntaxTraceEnabled()
    {
        return syntaxTraceEnable_;
    }

    static bool GetAccessTraceEnabled()
    {
        return accessTraceEnable_;
    }

    static bool GetVsyncModeTraceEnabled()
    {
        return vsyncModeTraceEnable_;
    }

    static bool GetTraceInputEventEnabled()
    {
        return traceInputEventEnable_.load();
    }

    static bool GetStateManagerEnabled()
    {
        return stateManagerEnable_.load();
    }

    static void SetStateManagerEnabled(bool stateManagerEnable)
    {
        stateManagerEnable_.store(stateManagerEnable);
    }

    static void SetFaultInjectEnabled(bool faultInjectEnable)
    {
        faultInjectEnabled_ = faultInjectEnable;
    }

    static bool GetFaultInjectEnabled()
    {
        return faultInjectEnabled_;
    }

    static bool GetBuildTraceEnabled()
    {
        return buildTraceEnable_;
    }

    static bool GetDynamicDetectionTraceEnabled()
    {
        return dynamicDetectionTraceEnable_;
    }

    static bool GetCacheNavigationNodeEnable();

    static bool GetAccessibilityEnabled()
    {
        return accessibilityEnabled_;
    }

    static uint32_t GetCanvasDebugMode()
    {
        return canvasDebugMode_;
    }

    static bool GetDebugEnabled();

    static bool DetectContainerMultiThread()
    {
        return debugEnabled_ && debugFlags_.bits_.containerMultiThread_;
    }

    static bool DetectGetHostOnDetach()
    {
        return debugEnabled_ && debugFlags_.bits_.getHostOnDetach_;
    }

    static bool DetectClaimDeathObj()
    {
        return debugEnabled_ && debugFlags_.bits_.claimDeathObj_;
    }

    static bool DetectAceObjTypeConvertion()
    {
        return debugEnabled_ && debugFlags_.bits_.aceObjTypeCvt_;
    }

    static bool DetectJsObjTypeConvertion()
    {
        return debugEnabled_ && debugFlags_.bits_.jsObjTypeCvt_;
    }

    static bool DetectObjDestroyInUse()
    {
        return debugEnabled_ && debugFlags_.bits_.objDestroyInUse_;
    }

    static bool DetectUseInvalidIterator()
    {
        return debugEnabled_ && debugFlags_.bits_.useInvalidIter_;
    }

    static bool GetMeasureDebugTraceEnabled()
    {
        return measureDebugTraceEnable_;
    }

    static bool GetSafeAreaDebugTraceEnabled()
    {
        return safeAreaDebugTraceEnable_;
    }

    static bool GetLayoutDetectEnabled();

    static bool GetGpuUploadEnabled()
    {
        return gpuUploadEnabled_;
    }

    static bool GetImageFrameworkEnabled()
    {
        return imageFrameworkEnable_;
    }

    /*
     * Set device orientation.
     */
    static void SetDeviceOrientation(int32_t orientation);

    static constexpr char INVALID_PARAM[] = "N/A";

    static int32_t GetMcc()
    {
        return mcc_;
    }

    static int32_t GetMnc()
    {
        return mnc_;
    }

    static void SetDeviceAccess(bool isDeviceAccess)
    {
        isDeviceAccess_ = isDeviceAccess;
    }

    static bool GetDeviceAccess()
    {
        return isDeviceAccess_;
    }

    static void SetConfigDeviceType(const std::string& type)
    {
        configDeviceType_ = type;
    }

    static const std::string& GetConfigDeviceType()
    {
        return configDeviceType_;
    }

    static float GetScrollCoefficients();

    static bool GetTransformEnabled();

    static void InitMccMnc(int32_t mcc, int32_t mnc);

    static ScreenShape GetScreenShape()
    {
        return screenShape_;
    }

    static int GetArkProperties();

    static std::string GetMemConfigProperty();

    static std::string GetArkBundleName();

    static size_t GetGcThreadNum();

    static size_t GetLongPauseTime();

    static void SetUnZipHap(bool unZipHap = true)
    {
        unZipHap_ = unZipHap;
    }

    static bool GetUnZipHap()
    {
        return unZipHap_;
    }

    static bool GetAsmInterpreterEnabled();

    static std::string GetAsmOpcodeDisableRange();

    static bool IsScoringEnabled(const std::string& name);

    static bool IsWindowSizeAnimationEnabled()
    {
        return windowAnimationEnabled_;
    }

    static bool IsAstcEnabled()
    {
        return astcEnabled_;
    }

    static bool GetWindowRectResizeEnabled();

    static int32_t GetAstcMaxError()
    {
        return astcMax_;
    }

    static int32_t GetAstcPsnr()
    {
        return astcPsnr_;
    }

    static bool IsImageFileCacheConvertAstcEnabled()
    {
        return imageFileCacheConvertAstc_;
    }

    static int32_t GetImageFileCacheConvertAstcThreshold()
    {
        return imageFileCacheConvertAstcThreshold_;
    }

    static void SetExtSurfaceEnabled(bool extSurfaceEnabled)
    {
        extSurfaceEnabled_ = extSurfaceEnabled;
    }

    static bool GetExtSurfaceEnabled()
    {
        return extSurfaceEnabled_;
    }

    static bool GetAllowWindowOpenMethodEnabled();

    static uint32_t GetDumpFrameCount()
    {
        return dumpFrameCount_;
    }

    static bool GetIsUseMemoryMonitor();

    static bool IsFormAnimationLimited();

    static bool GetResourceDecoupling();

    static bool ConfigChangePerform();

    static void SetConfigChangePerform();

    static int32_t GetJankFrameThreshold();

    static bool GetTitleStyleEnabled();

    static std::string GetCustomTitleFilePath();

    static bool Is24HourClock();

    static std::optional<bool> GetRtlEnabled();

    static bool GetEnableScrollableItemPool()
    {
        return enableScrollableItemPool_;
    }

    static bool GetDisplaySyncSkipEnabled();

    static bool GetNavigationBlurEnabled();

    static bool GetGridCacheEnabled();

    static bool GetGridIrregularLayoutEnabled();

    static bool WaterFlowUseSegmentedLayout();

    static bool GetSideBarContainerBlurEnable();

    using EnableSystemParameterCallback = void (*)(const char* key, const char* value, void* context);

    static void AddWatchSystemParameter(const char* key, void* context, EnableSystemParameterCallback callback);

    static void RemoveWatchSystemParameter(const char* key, void* context, EnableSystemParameterCallback callback);
    static void EnableSystemParameterTraceLayoutCallback(const char* key, const char* value, void* context);
    static void EnableSystemParameterTraceInputEventCallback(const char* key, const char* value, void* context);
    static void EnableSystemParameterSecurityDevelopermodeCallback(const char* key, const char* value, void* context);
    static void EnableSystemParameterDebugStatemgrCallback(const char* key, const char* value, void* context);
    static void EnableSystemParameterDebugBoundaryCallback(const char* key, const char* value, void* context);
    static void EnableSystemParameterPerformanceMonitorCallback(const char* key, const char* value, void* context);
    static void OnFocusActiveChanged(const char* key, const char* value, void* context);
    static float GetDefaultResolution();

    static void SetLayoutTraceEnabled(bool layoutTraceEnable);

    static void SetInputEventTraceEnabled(bool inputEventTraceEnable);

    static void SetSecurityDevelopermodeLayoutTraceEnabled(bool layoutTraceEnable);

    static void SetDebugBoundaryEnabled(bool debugBoundaryEnabled);

    static void SetPerformanceMonitorEnabled(bool performanceMonitorEnable);

    static void SetFocusCanBeActive(bool focusCanBeActive);

    static bool GetAcePerformanceMonitorEnabled()
    {
        return acePerformanceMonitorEnable_.load();
    }

    static bool GetFocusCanBeActive()
    {
        return focusCanBeActive_.load();
    }

    static bool GetAceCommercialLogEnabled()
    {
        return aceCommercialLogEnable_;
    }

    static std::string GetAtomicServiceBundleName();

    static std::pair<float, float> GetDarkModeBrightnessPercent()
    {
        return brightUpPercent_;
    }

    static float GetPageCount()
    {
        return pageCount_;
    }

    static bool IsOpIncEnable();

    static float GetDragStartDampingRatio();

    static float GetDragStartPanDistanceThreshold();

    static bool IsSmallFoldProduct();

    static bool IsBigFoldProduct();

    static std::string GetWebDebugRenderMode();

    static std::string GetDebugInspectorId();

    static double GetSrollableVelocityScale();

    static double GetSrollableFriction();

    static double GetScrollableDistance();

    static bool GetWebDebugMaximizeResizeOptimize();

    static bool IsNeedResampleTouchPoints();

    static bool IsNeedSymbol();

    static bool GetMultiInstanceEnabled();

    static void SetMultiInstanceEnabled(bool enabled);

    static bool GetTaskPriorityAdjustmentEnable()
    {
        return taskPriorityAdjustmentEnable_;
    }

    static int32_t GetDragDropFrameworkStatus();
    static int32_t GetTouchAccelarate();

    static bool IsSuperFoldDisplayDevice();

    static bool IsPageTransitionFreeze();

    static bool IsSoftPageTransition();

    static bool IsFormSkeletonBlurEnabled();

    static int32_t getFormSharedImageCacheThreshold();

    static bool IsWhiteBlockEnabled();
    static bool IsWhiteBlockIdleChange();
    static int32_t GetWhiteBlockIndexValue();
    static int32_t GetWhiteBlockCacheCountValue();

    static WidthLayoutBreakPoint GetWidthLayoutBreakpoints()
    {
        return widthLayoutBreakpoints_;
    }

    static HeightLayoutBreakPoint GetHeightLayoutBreakpoints()
    {
        return heightLayoutBreakpoints_;
    }

    static bool IsSyncLoadEnabled()
    {
        return syncLoadEnabled_;
    }

    static std::string GetMapSearchPrefix();

    static bool GetDebugThreadSafeNodeEnabled()
    {
        return debugThreadSafeNodeEnable_;
    }

private:
    static bool opincEnabled_;
    static bool developerModeOn_;
    static bool svgTraceEnable_;
    static std::atomic<bool> layoutTraceEnable_;
    static std::atomic<bool> traceInputEventEnable_;
    static bool buildTraceEnable_;
    static bool dynamicDetectionTraceEnable_;
    static bool cacheNavigationNodeEnable_;
    static bool syncDebugTraceEnable_;
    static bool measureDebugTraceEnable_;
    static bool safeAreaDebugTraceEnable_;
    static bool pixelRoundEnable_;
    static bool textTraceEnable_;
    static bool syntaxTraceEnable_;
    static bool accessTraceEnable_;
    static bool vsyncModeTraceEnable_;
    static bool accessibilityEnabled_;
    static uint32_t canvasDebugMode_;
    static bool isRound_;
    static bool isDeviceAccess_;
    static int32_t deviceWidth_;
    static int32_t deviceHeight_;
    static int32_t devicePhysicalWidth_;
    static int32_t devicePhysicalHeight_;
    static double resolution_; // density of the default display
    static DeviceType deviceType_;
    static bool needAvoidWindow_;
    static DeviceOrientation orientation_;
    static std::string brand_;
    static std::string manufacturer_;
    static std::string model_;
    static std::string product_;
    static std::string apiVersion_;
    static std::string releaseType_;
    static std::string paramDeviceType_;
    static int32_t mcc_;
    static int32_t mnc_;
    static ScreenShape screenShape_;
    static LongScreenType LongScreen_;
    static bool unZipHap_;
    static bool rosenBackendEnabled_;
    static bool windowAnimationEnabled_;
    static bool debugEnabled_;
    static std::string configDeviceType_;
    static bool transformEnabled_;
    static float scrollCoefficients_;
    static DebugFlags debugFlags_;
    static bool containerDeleteFlag_;
    static bool layoutDetectEnabled_;
    static std::atomic<bool> debugBoundaryEnabled_;
    static bool debugAutoUIEnabled_; // for AutoUI Test
    static bool debugOffsetLogEnabled_;
    static bool downloadByNetworkEnabled_;
    static bool recycleImageEnabled_;
    static bool gpuUploadEnabled_;
    static bool isHookModeEnabled_;
    static bool astcEnabled_;
    static int32_t astcMax_;
    static int32_t astcPsnr_;
    static bool imageFileCacheConvertAstc_;
    static int32_t imageFileCacheConvertAstcThreshold_;
    static bool extSurfaceEnabled_;
    static uint32_t dumpFrameCount_;
    static bool resourceDecoupling_;
    static bool configChangePerform_;
    static bool enableScrollableItemPool_;
    static bool navigationBlurEnabled_;
    static bool gridCacheEnabled_;
    static bool gridIrregularLayoutEnable_;
    static bool sideBarContainerBlurEnable_;
    static std::atomic<bool> stateManagerEnable_;
    static std::atomic<bool> acePerformanceMonitorEnable_;
    static std::atomic<bool> focusCanBeActive_;
    static bool aceCommercialLogEnable_;
    static bool faultInjectEnabled_;
    static bool imageFrameworkEnable_;
    static float pageCount_;
    static std::pair<float, float> brightUpPercent_;
    static float dragStartDampingRatio_;
    static float dragStartPanDisThreshold_;
    static float fontScale_;
    static float fontWeightScale_;
    static bool windowRectResizeEnabled_;
    static FoldScreenType foldScreenType_;
    static double scrollableDistance_;
    static bool taskPriorityAdjustmentEnable_;
    static bool multiInstanceEnabled_;
    static int32_t dragDropFrameworkStatus_;
    static int32_t touchAccelarate_;
    static bool pageTransitionFrzEnabled_;
    static bool softPagetransition_;
    static bool formSkeletonBlurEnabled_;
    static int32_t formSharedImageCacheThreshold_;
    static WidthLayoutBreakPoint widthLayoutBreakpoints_;
    static HeightLayoutBreakPoint heightLayoutBreakpoints_;
    static bool syncLoadEnabled_;
    static bool whiteBlockEnabled_;
    static std::string mapSearchPrefix_;
    static bool debugThreadSafeNodeEnable_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_SYSTEM_PROPERTIES_H
