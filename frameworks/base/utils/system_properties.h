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

#include <memory>
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

constexpr int32_t MCC_UNDEFINED = 0;
constexpr int32_t MNC_UNDEFINED = 0;

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

    /*
     * Get type of current device.
     */
    static DeviceType GetDeviceType();

    /*
     * check SystemCapability.
     */
    static bool IsSyscapExist(const char* cap);

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
     * Get wght scale of device.
     */
    static float GetFontWeightScale();

    /*
     * Get resolution of device.
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

    static std::string GetRegion();

    static std::string GetNewPipePkg();

    static float GetAnimationScale();

    static std::string GetPartialUpdatePkg();

    static int32_t GetSvgMode();

    static bool GetImageFrameworkEnabled();

    static bool GetRosenBackendEnabled()
    {
        return rosenBackendEnabled_;
    }

    static bool GetHookModeEnabled()
    {
        return isHookModeEnabled_;
    }

    static bool GetDebugBoundaryEnabled()
    {
        return debugBoundaryEnabled_;
    }

    static bool GetTraceEnabled()
    {
        return traceEnabled_;
    }

    static bool GetSvgTraceEnabled()
    {
        return svgTraceEnable_;
    }

    static bool GetAccessibilityEnabled()
    {
        return accessibilityEnabled_;
    }

    static bool GetDebugEnabled();

    static bool GetGpuUploadEnabled()
    {
        return gpuUploadEnabled_;
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

    static void SetColorMode(ColorMode colorMode)
    {
        if (colorMode_ != colorMode) {
            colorMode_ = colorMode;
        }
    }

    static ColorMode GetColorMode()
    {
        return colorMode_;
    }

    static void SetDeviceAccess(bool isDeviceAccess)
    {
        isDeviceAccess_ = isDeviceAccess;
    }

    static bool GetDeviceAccess()
    {
        return isDeviceAccess_;
    }

    static void InitMccMnc(int32_t mcc, int32_t mnc);

    static ScreenShape GetScreenShape()
    {
        return screenShape_;
    }

    /*
     * Change px to vp
     */
    static double Px2Vp(double pxNum)
    {
        return pxNum / resolution_;
    }

    static double Vp2Px(double pxNum)
    {
        return pxNum * resolution_;
    }

    static int GetArkProperties();

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

    static int32_t GetAstcMaxError()
    {
        return astcMax_;
    }

    static int32_t GetAstcPsnr()
    {
        return astcPsnr_;
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

    static bool IsSceneBoardEnabled();

private:
    static bool traceEnabled_;
    static bool svgTraceEnable_;
    static bool accessibilityEnabled_;
    static bool isRound_;
    static bool isDeviceAccess_;
    static int32_t deviceWidth_;
    static int32_t deviceHeight_;
    static double resolution_;
    static DeviceType deviceType_;
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
    static ColorMode colorMode_;
    static ScreenShape screenShape_;
    static LongScreenType LongScreen_;
    static bool unZipHap_;
    static bool rosenBackendEnabled_;
    static bool windowAnimationEnabled_;
    static bool debugEnabled_;
    static bool debugBoundaryEnabled_;
    static bool gpuUploadEnabled_;
    static bool isHookModeEnabled_;
    static bool astcEnabled_;
    static int32_t astcMax_;
    static int32_t astcPsnr_;
    static bool extSurfaceEnabled_;
    static uint32_t dumpFrameCount_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_SYSTEM_PROPERTIES_H
