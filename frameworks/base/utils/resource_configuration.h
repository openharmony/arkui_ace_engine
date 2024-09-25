/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_RESOURCE_CONFIGURATION_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_RESOURCE_CONFIGURATION_H

#include <string>
#include <vector>

#include "base/json/json_util.h"
#include "base/utils/device_type.h"
#include "base/utils/device_config.h"

namespace OHOS::Ace {

class ResourceConfiguration {
public:
    static constexpr uint32_t COLOR_MODE_UPDATED_FLAG = 0x00000001;
    static constexpr uint32_t FONT_RATIO_UPDATED_FLAG = 0x00000002;
    static bool TestFlag(uint32_t flags, uint32_t flag)
    {
        return (flags & flag);
    }

public:
    void SetDeviceType(const DeviceType& deviceType)
    {
        deviceType_ = deviceType;
    }

    DeviceType GetDeviceType() const
    {
        return deviceType_;
    }

    void SetOrientation(const DeviceOrientation& orientation)
    {
        orientation_ = orientation;
    }

    DeviceOrientation GetOrientation() const
    {
        return orientation_;
    }

    void SetDensity(const double& density)
    {
        density_ = density;
    }

    double GetDensity() const
    {
        return density_;
    }

    void SetFontRatio(double fontRatio)
    {
        fontRatio_ = fontRatio;
    }

    double GetFontRatio() const
    {
        return fontRatio_;
    }

    void SetColorMode(const ColorMode& colorMode)
    {
        colorMode_ = colorMode;
    }

    ColorMode GetColorMode() const
    {
        return colorMode_;
    }

    void SetDeviceAccess(bool isDeviceAccess)
    {
        isDeviceAccess_ = isDeviceAccess;
    }

    bool GetDeviceAccess() const
    {
        return isDeviceAccess_;
    }

    bool UpdateFromJsonString(const std::string jsonStr, uint32_t& updateFlags);

    void SetColorModeIsSetByApp(bool colorModeIsSetByApp)
    {
        colorModeIsSetByApp_ = colorModeIsSetByApp;
    }

    bool GetColorModeIsSetByApp() const
    {
        return colorModeIsSetByApp_;
    }

    void SetMcc(uint32_t mcc)
    {
        mcc_ = mcc;
    }

    uint32_t GetMcc() const
    {
        return mcc_;
    }

    void SetMnc(uint32_t mnc)
    {
        mnc_ = mnc;
    }

    uint32_t GetMnc() const
    {
        return mnc_;
    }

    void SetAppHasDarkRes(bool hasDarkRes)
    {
        appHasDarkRes_ = hasDarkRes;
    }

    bool GetAppHasDarkRes() const
    {
        return appHasDarkRes_;
    }

    void SetPreferredLanguage(const std::string& preferredLanguage)
    {
        preferredLanguage_ = preferredLanguage;
    }

    const std::string& GetPreferredLanguage() const
    {
        return preferredLanguage_;
    }

private:
    bool ParseJsonColorMode(const std::unique_ptr<JsonValue>& jsonConfig, uint32_t& updateFlags);
    bool ParseJsonFontRatio(const std::unique_ptr<JsonValue>& jsonConfig, uint32_t& updateFlags);

private:
    DeviceType deviceType_ = DeviceType::PHONE;
    DeviceOrientation orientation_ = DeviceOrientation::PORTRAIT;
    double density_ = 1.0;
    double fontRatio_ = 1.0;
    bool isDeviceAccess_ = false;
    ColorMode colorMode_ = ColorMode::LIGHT;
    bool colorModeIsSetByApp_ = false;
    bool appHasDarkRes_ = false;
    uint32_t mcc_ = 0;
    uint32_t mnc_ = 0;
    std::string preferredLanguage_;
};

class ResourceInfo {
public:
    void SetResourceConfiguration(const ResourceConfiguration& resourceConfiguration)
    {
        resourceConfiguration_ = resourceConfiguration;
    }

    ResourceConfiguration GetResourceConfiguration() const
    {
        return resourceConfiguration_;
    }

    void SetResourceHandlers(const std::vector<int64_t>& resourcehandlers)
    {
        resourcehandlers_ = resourcehandlers;
    }

    std::vector<int64_t> GetResourceHandlers() const
    {
        return resourcehandlers_;
    }

    void SetHapPath(const std::string& hapPath)
    {
        hapPath_ = hapPath;
    }

    std::string GetHapPath() const
    {
        return hapPath_;
    }

    void SetPackagePath(const std::string& packagePath)
    {
        packagePath_ = packagePath;
    }

    std::string GetPackagePath() const
    {
        return packagePath_;
    }

#if defined(PREVIEW)
    void SetSystemPackagePath(const std::string& systemPackagePath)
    {
        systemPackagePath_ = systemPackagePath;
    }

    std::string GetSystemPackagePath() const
    {
        return systemPackagePath_;
    }

    void SetHmsPackagePath(const std::string& hmsPackagePath)
    {
        hmsPackagePath_ = hmsPackagePath;
    }

    const std::string& GetHmsPackagePath() const
    {
        return hmsPackagePath_;
    }
#endif

    void SetThemeId(uint32_t themeId)
    {
        themeId_ = static_cast<int32_t>(themeId);
    }

    int32_t GetThemeId() const
    {
        return themeId_;
    }

private:
    ResourceConfiguration resourceConfiguration_;
    std::vector<int64_t> resourcehandlers_;
    std::string hapPath_;
    std::string packagePath_;
#if defined(PREVIEW)
    std::string systemPackagePath_;
    std::string hmsPackagePath_;
#endif
    int32_t themeId_ = -1;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_RESOURCE_CONFIGURATION_H
