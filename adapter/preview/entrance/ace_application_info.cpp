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

#include "adapter/preview/entrance/ace_application_info.h"

#include "unicode/locid.h"

#ifdef WINDOWS_PLATFORM
#include <windows.h>
#else
#include <dirent.h>
#include <sys/types.h>
#endif

#include "base/i18n/localization.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/resource/ace_res_config.h"
#include "base/resource/ace_res_data_struct.h"
#include "core/common/ace_engine.h"

namespace OHOS::Ace::Platform {

void AceApplicationInfoImpl::ChangeLocale(const std::string& language, const std::string& countryOrRegion) {}

std::vector<std::string> AceApplicationInfoImpl::GetLocaleFallback(const std::vector<std::string>& localeList) const
{
    std::vector<std::string> fileList;
    AceResConfig::MatchAndSortI18nConfigs(localeList, localeTag_, fileList);
    return fileList;
}

std::vector<std::string> AceApplicationInfoImpl::GetResourceFallback(const std::vector<std::string>& resourceList) const
{
    std::vector<std::string> fileList;
    std::string deviceConfigTag = GetCurrentDeviceResTag();
    AceResConfig::MatchAndSortResConfigs(resourceList, deviceConfigTag, fileList);
    return fileList;
}

std::vector<std::string> AceApplicationInfoImpl::GetStyleResourceFallback(
    const std::vector<std::string>& resourceList) const
{
    std::vector<std::string> fileList;
    std::string deviceConfigTag = GetCurrentDeviceResTag();
    AceResConfig::MatchAndSortStyleResConfigs(resourceList, deviceConfigTag, fileList);
    return fileList;
}

std::vector<std::string> AceApplicationInfoImpl::GetDeclarativeResourceFallback(
    const std::set<std::string>& resourceFolderList) const
{
    std::string deviceConfigTag = GetCurrentDeviceDeclarativeResTag();
    std::vector<std::string> folderList;
    AceResConfig::MatchAndSortDeclarativeResConfigs(resourceFolderList, deviceConfigTag, folderList);
    return folderList;
}

std::string AceApplicationInfoImpl::GetCurrentDeviceResTag() const
{
    ResolutionType resolutionType = AceResConfig::GetResolutionType(SystemProperties::GetResolution());
    AceResConfig deviceResConfig = AceResConfig(SystemProperties::GetMcc(), SystemProperties::GetMnc(),
        SystemProperties::GetDevcieOrientation(), SystemProperties::GetColorMode(),
        SystemProperties::GetParamDeviceType() == "tablet" ? DeviceType::TABLET : SystemProperties::GetDeviceType(),
        resolutionType);
    return AceResConfig::ConvertResConfigToTag(deviceResConfig, false);
}

std::string AceApplicationInfoImpl::GetCurrentDeviceDeclarativeResTag() const
{
    UErrorCode status = U_ZERO_ERROR;
    icu::Locale locale = icu::Locale::forLanguageTag(icu::StringPiece(localeTag_), status);
    ResolutionType resolutionType = AceResConfig::GetResolutionType(SystemProperties::GetResolution());
    LongScreenType longScreenType = AceResConfig::GetLongScreenType(SystemProperties::GetResolution());
    AceResConfig deviceResConfig;
    if (status != U_ZERO_ERROR) {
        LOGE("This localeTag is not valid.");
        deviceResConfig = AceResConfig("", "", "", longScreenType, SystemProperties::GetScreenShape(),
            SystemProperties::GetDevcieOrientation(), SystemProperties::GetColorMode(),
            SystemProperties::GetParamDeviceType() == "tablet" ? DeviceType::TABLET : SystemProperties::GetDeviceType(),
            resolutionType);
    } else {
        deviceResConfig = AceResConfig(locale.getLanguage(), locale.getScript(), locale.getCountry(),
            longScreenType, SystemProperties::GetScreenShape(), SystemProperties::GetDevcieOrientation(),
            SystemProperties::GetColorMode(), SystemProperties::GetParamDeviceType() == "tablet" ? DeviceType::TABLET :
            SystemProperties::GetDeviceType(), resolutionType);
    }

    return AceResConfig::ConvertDeclarativeResConfigToTag(deviceResConfig);
}

double AceApplicationInfoImpl::GetTargetMediaScaleRatio(const std::string& targetResTag) const
{
    std::string deviceConfigTag = GetCurrentDeviceDeclarativeResTag();
    auto deviceConfig = AceResConfig::ConvertDeclarativeResTagToConfig(deviceConfigTag);
    ResolutionType deviceResolution = (deviceConfig.resolution_ != ResolutionType::RESOLUTION_NONE) ?
        deviceConfig.resolution_ : ResolutionType::RESOLUTION_MDPI;

    ResolutionType targetResolution;
    if (targetResTag == "default") {
        targetResolution = ResolutionType::RESOLUTION_MDPI;
    } else {
        AceResConfig targetConfig = AceResConfig::ConvertDeclarativeResTagToConfig(targetResTag);
        targetResolution = (targetConfig.resolution_ != ResolutionType::RESOLUTION_NONE) ?
            targetConfig.resolution_ : ResolutionType::RESOLUTION_MDPI;
    }

    return static_cast<double>(deviceResolution) / static_cast<double>(targetResolution);
}

void AceApplicationInfoImpl::SetLocale(const std::string& language, const std::string& countryOrRegion,
    const std::string& script, const std::string& keywordsAndValues)
{
    language_ = language;
    countryOrRegion_ = countryOrRegion;
    script_ = script;
    keywordsAndValues_ = keywordsAndValues;

    localeTag_ = language;
    if (!script_.empty()) {
        localeTag_.append("-" + script_);
    }
    localeTag_.append("-" + countryOrRegion_);

    icu::Locale locale(language_.c_str(), countryOrRegion.c_str());
    isRightToLeft_ = locale.isRightToLeft();

    auto languageList = Localization::GetLanguageList(language_);
    Localization::SetLocale(
        language_, countryOrRegion_, script, languageList.front(), keywordsAndValues_);
}

bool AceApplicationInfoImpl::GetFiles(const std::string& filePath, std::vector<std::string>& fileList) const
{
    const auto& assetBasePathSet = AceEngine::Get().GetAssetBasePath();
    if (assetBasePathSet.empty()) {
        LOGE("the assetBasePathSet is empty");
        return false;
    }
    std::vector<std::string> assetPaths;
#ifdef WINDOWS_PLATFORM
    for (const auto& assetBasePath : assetBasePathSet) {
        assetPaths.emplace_back(assetBasePath + "\\" + filePath);
    }
    for (const auto& path : assetPaths) {
        std::string filePath(path);
        WIN32_FIND_DATA fileInfo;
        HANDLE hFind;
        if ((hFind = FindFirstFile(filePath.append("\\*").c_str(), &fileInfo)) != INVALID_HANDLE_VALUE) {
            do {
                if (strcmp(fileInfo.cFileName, ".") != 0 && strcmp(fileInfo.cFileName, "..") != 0) {
                    fileList.push_back(fileInfo.cFileName);
                }
            } while (FindNextFile(hFind, &fileInfo) != 0);
            FindClose(hFind);
        }
    }
#elif defined(MAC_PLATFORM)
    for (const auto& assetBasePath : assetBasePathSet) {
        assetPaths.emplace_back(assetBasePath + "/" + filePath);
    }
    for (const auto& assetPath : assetPaths) {
        DIR* dp = nullptr;
        if (nullptr == (dp = opendir(assetPath.c_str()))) {
            continue;
        }
        struct dirent* dptr = nullptr;
        while ((dptr = readdir(dp)) != nullptr) {
            if (strcmp(dptr->d_name, ".") != 0 && strcmp(dptr->d_name, "..") != 0) {
                fileList.push_back(dptr->d_name);
            }
        }
        closedir(dp);
    }
#endif
    return true;
}

bool AceApplicationInfoImpl::GetFiles(
    int32_t instanceId, const std::string& filePath, std::vector<std::string>& fileList) const
{
    return GetFiles(filePath, fileList);
}

bool AceApplicationInfoImpl::GetBundleInfo(const std::string& packageName, AceBundleInfo& bundleInfo)
{
    return false;
}

double AceApplicationInfoImpl::GetLifeTime() const
{
    return 0;
}

std::string AceApplicationInfoImpl::GetJsEngineParam(const std::string& key) const
{
    return "";
}

AceApplicationInfoImpl& AceApplicationInfoImpl::GetInstance()
{
    static AceApplicationInfoImpl instance;
    return instance;
}

} // namespace OHOS::Ace::Platform

namespace OHOS::Ace {

AceApplicationInfo& AceApplicationInfo::GetInstance()
{
    return Platform::AceApplicationInfoImpl::GetInstance();
}

} // namespace OHOS::Ace
