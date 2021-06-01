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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_SYSTEM_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_SYSTEM_PROPERTIES_H

#include <string>

#include "base/utils/device_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {

enum class DeviceOrientation : int32_t {
    PORTRAIT,
    LANDSCAPE,
    ORIENTATION_UNDEFINED,
};

enum class ColorMode : int32_t {
    LIGHT = 0,
    DARK,
    COLOR_MODE_UNDEFINED,
};

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

class ACE_EXPORT SystemProperties final {
public:
    /*
     * Init device type for Ace.
     */
    static void InitDeviceType(DeviceType deviceType);

    /*
     * Init device info for Ace.
     */
    static void InitDeviceInfo(int32_t deviceWidth, int32_t deviceHeight, int32_t orientation,
        double resolution, bool isRound);

    /*
     * Init device type according to system property.
     */
    static void InitDeviceTypeBySystemProperty();

    /*
     * Update view's width and height information.
     */
    static void UpdateSurfaceStatus(int32_t width, int32_t height);

    /*
     * Get width of view.
     */
    static int32_t GetWidth()
    {
        return width_;
    }

    /*
     * Get height of view.
     */
    static int32_t GetHeight()
    {
        return height_;
    }

    /*
     * Get type of current device.
     */
    static DeviceType GetDeviceType();

    /*
     * Get current orientation of device.
     */
    static DeviceOrientation GetDevcieOrientation()
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

    static bool GetTraceEnabled()
    {
        return traceEnabled_;
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
        colorMode_ = colorMode;
    }

    static ColorMode GetColorMode()
    {
        return colorMode_;
    }

    static void InitMccMnc(int32_t mcc, int32_t mnc);

private:
    static bool traceEnabled_;
    static bool isRound_;
    static int32_t width_;
    static int32_t height_;
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
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_SYSTEM_PROPERTIES_H
