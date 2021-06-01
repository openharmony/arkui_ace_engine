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

#include "adapter/common/cpp/ace_res_config.h"

#include <unordered_map>

#include "unicode/locid.h"

#include "adapter/common/cpp/ace_res_key_parser.h"
#include "base/json/json_util.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace {
namespace {

const std::unordered_map<std::string, std::string> LOCALE_PARENTS {
    { "ar-DZ", "ar-015" },
    { "ar-EH", "ar-015" },
    { "ar-LY", "ar-015" },
    { "ar-MA", "ar-015" },
    { "ar-TN", "ar-015" },
    { "zh-MO", "zh-HK" },
    { "en-150", "en-001" },
    { "en-AG", "en-001" },
    { "en-AI", "en-001" },
    { "en-AU", "en-001" },
    { "en-BB", "en-001" },
    { "en-BE", "en-001" },
    { "en-BM", "en-001" },
    { "en-BS", "en-001" },
    { "en-BZ", "en-001" },
    { "en-CC", "en-001" },
    { "en-CK", "en-001" },
    { "en-CX", "en-001" },
    { "en-DG", "en-001" },
    { "en-ER", "en-001" },
    { "en-FK", "en-001" },
    { "en-FM", "en-001" },
    { "en-GB", "en-001" },
    { "en-GD", "en-001" },
    { "en-GG", "en-001" },
    { "en-GI", "en-001" },
    { "en-GY", "en-001" },
    { "en-HK", "en-001" },
    { "en-IE", "en-001" },
    { "en-IM", "en-001" },
    { "en-IN", "en-001" },
    { "en-IO", "en-001" },
    { "en-JE", "en-001" },
    { "en-KI", "en-001" },
    { "en-KN", "en-001" },
    { "en-KY", "en-001" },
    { "en-LC", "en-001" },
    { "en-LR", "en-001" },
    { "en-LS", "en-001" },
    { "en-MM", "en-001" },
    { "en-MO", "en-001" },
    { "en-MS", "en-001" },
    { "en-MT", "en-001" },
    { "en-MY", "en-001" },
    { "en-NF", "en-001" },
    { "en-NR", "en-001" },
    { "en-NU", "en-001" },
    { "en-NZ", "en-001" },
    { "en-PG", "en-001" },
    { "en-PK", "en-001" },
    { "en-PN", "en-001" },
    { "en-PW", "en-001" },
    { "en-SB", "en-001" },
    { "en-SC", "en-001" },
    { "en-SD", "en-001" },
    { "en-SG", "en-001" },
    { "en-SH", "en-001" },
    { "en-SL", "en-001" },
    { "en-SS", "en-001" },
    { "en-SX", "en-001" },
    { "en-SZ", "en-001" },
    { "en-TC", "en-001" },
    { "en-TK", "en-001" },
    { "en-TT", "en-001" },
    { "en-TV", "en-001" },
    { "en-VC", "en-001" },
    { "en-VG", "en-001" },
    { "en-WS", "en-001" },
    { "en-ZG", "en-001" },
    { "es-AR", "es-419" },
    { "es-BO", "es-419" },
    { "es-BR", "es-419" },
    { "es-BZ", "es-419" },
    { "es-CL", "es-419" },
    { "es-CO", "es-419" },
    { "es-CR", "es-419" },
    { "es-CU", "es-419" },
    { "es-DO", "es-419" },
    { "es-EC", "es-419" },
    { "es-GT", "es-419" },
    { "es-HN", "es-419" },
    { "es-MX", "es-419" },
    { "es-NI", "es-419" },
    { "es-PA", "es-419" },
    { "es-PE", "es-419" },
    { "es-PR", "es-419" },
    { "es-PY", "es-419" },
    { "es-SV", "es-419" },
    { "es-US", "es-419" },
    { "es-UY", "es-419" },
    { "es-VE", "es-419" },
    { "pt-AO", "pt-PT" },
    { "pt-CH", "pt-PT" },
    { "pt-CV", "pt-PT" },
    { "pt-GQ", "pt-PT" },
    { "pt-GW", "pt-PT" },
    { "pt-LU", "pt-PT" },
    { "pt-MO", "pt-PT" },
    { "pt-MZ", "pt-PT" },
    { "pt-ST", "pt-PT" },
    { "pt-TL", "pt-PT" },
};

const std::unordered_map<std::string, std::string> DEFAULT_LANG {
    { "es-419", "es-US" },
    { "en-Qaag", "en-GB" },
    { "en-001", "en-GB" },
};

const std::unordered_map<std::string, std::string> LANGUAGE_CODE_MAP {
    { "iw", "he" },
    { "tl", "fil" },
    { "in", "id" },
};

std::string ComputeScript(const AceResConfig& resConfig)
{
    icu::Locale locale(resConfig.language_.c_str(), resConfig.region_.c_str());
    UErrorCode status = U_ZERO_ERROR;
    locale.addLikelySubtags(status);
    if (status != U_ZERO_ERROR) {
        return std::string();
    }
    return locale.getScript();
}

AceResConfig ConvertLocaleTagToConfig(const std::string& localeTag)
{
    UErrorCode status = U_ZERO_ERROR;
    icu::Locale locale = icu::Locale::forLanguageTag(icu::StringPiece(localeTag), status);
    if (status != U_ZERO_ERROR) {
        LOGE("This localeTag is not valid.");
        return AceResConfig("", "", "");
    }
    return AceResConfig(locale.getLanguage(), locale.getScript(), locale.getCountry());
}

std::string ConvertLocaleConfigToTag(const AceResConfig& localeConfig)
{
    std::string localeTag = localeConfig.language_;
    if (!localeConfig.script_.empty()) {
        localeTag += ('-' + localeConfig.script_);
    }
    if (!localeConfig.region_.empty()) {
        localeTag += ('-' + localeConfig.region_);
    }
    return localeTag;
}

bool IsPseudoLocale(const AceResConfig& resConfig)
{
    return (resConfig.language_ == "en" && resConfig.region_ == "XA") ||
           (resConfig.language_ == "ar" && resConfig.region_ == "XB");
}

void MatchLocaleConfig(const std::vector<AceResConfig>& candidatesLocaleConfig, const AceResConfig& deviceLocaleConfig,
    std::vector<AceResConfig>& matchedLocaleConfigs)
{
    std::string deviceLanguage = deviceLocaleConfig.language_;
    std::string deviceScript = deviceLocaleConfig.script_;
    auto iter = LANGUAGE_CODE_MAP.find(deviceLanguage);
    if (iter != LANGUAGE_CODE_MAP.end()) {
        deviceLanguage = iter->second;
    }
    for (auto& candidate : candidatesLocaleConfig) {
        std::string candidateLanguage = candidate.language_;
        // Languages codes need to be specially handled.
        auto candidateIter = LANGUAGE_CODE_MAP.find(candidateLanguage);
        if (candidateIter != LANGUAGE_CODE_MAP.end()) {
            candidateLanguage = candidateIter->second;
        }
        if (candidateLanguage != deviceLanguage) {
            continue;
        }
        if (IsPseudoLocale(candidate)) {
            if (IsPseudoLocale(deviceLocaleConfig)) {
                matchedLocaleConfigs.emplace_back(candidate);
            }
            continue;
        }
        if (deviceLanguage == "en" && deviceScript == "Qaag") {
            deviceScript = "Latn";
        }
        // Compute Script when it is not provided.
        std::string candidateScript = candidate.script_.empty() ? ComputeScript(candidate) : candidate.script_;
        if (deviceScript != candidateScript) {
            continue;
        }
        matchedLocaleConfigs.emplace_back(candidate);
    }
}

void FindBacktrackPath(
    const AceResConfig& localeConfig, std::vector<std::string>& backtrackPath, const std::string& localeTag)
{
    if (LOCALE_PARENTS.find(localeTag) != LOCALE_PARENTS.end()) {
        std::string curTag = LOCALE_PARENTS.find(localeTag)->second;
        backtrackPath.emplace_back(curTag);
        FindBacktrackPath(localeConfig, backtrackPath, curTag);
    } else {
        backtrackPath.emplace_back(localeConfig.language_);
    }
}

bool IsOnBacktrackingPath(const std::string& bestConfigTag, const std::string& candidateConfigTag,
    const AceResConfig& bestLocaleConfig, const AceResConfig& candidateLocaleConfig,
    std::vector<std::string> backtrackPath)
{
    std::vector<std::string> bestConfigBacktrackPaths;
    FindBacktrackPath(bestLocaleConfig, bestConfigBacktrackPaths, bestConfigTag);
    std::vector<std::string> candidateConfigBacktrackPaths;
    FindBacktrackPath(candidateLocaleConfig, candidateConfigBacktrackPaths, candidateConfigTag);
    int32_t bestConfigIndex = -1;
    int32_t candidateConfigIndex = -1;
    for (std::size_t i = 0; i < backtrackPath.size(); i++) {
        for (const auto& bestConfigPath : bestConfigBacktrackPaths) {
            if (bestConfigPath == backtrackPath[i] && bestConfigIndex == -1) {
                bestConfigIndex = i;
            }
        }
        for (const auto& candidateConfigPath : candidateConfigBacktrackPaths) {
            if (candidateConfigPath == backtrackPath[i] && candidateConfigIndex == -1) {
                candidateConfigIndex = i;
            }
        }
    }
    if (bestConfigIndex < candidateConfigIndex) {
        return (bestConfigIndex == -1);
    } else if (candidateConfigIndex < bestConfigIndex) {
        return (candidateConfigIndex != -1);
    }
    // Check if candidate and best are on the default area of device's backtracking path.
    for (auto& path : backtrackPath) {
        if (DEFAULT_LANG.find(path) != DEFAULT_LANG.end()) {
            std::string curTag = DEFAULT_LANG.find(path)->second;
            if (bestConfigTag == curTag) {
                return false;
            } else if (candidateConfigTag == curTag) {
                return true;
            }
        }
    }

    // Compute the default region code through the device language code.
    UErrorCode status = U_ZERO_ERROR;
    icu::Locale locale = icu::Locale::forLanguageTag(icu::StringPiece(backtrackPath[backtrackPath.size() - 1]), status);
    locale.addLikelySubtags(status);
    if (status == U_ZERO_ERROR) {
        if (bestLocaleConfig.region_ == locale.getCountry()) {
            return false;
        }
        if (candidateLocaleConfig.region_ == locale.getCountry()) {
            return true;
        }
    }

    // If configs did not meet all the conditions above, sort the config region with dictionary order.
    return strcmp(bestLocaleConfig.region_.c_str(), candidateLocaleConfig.region_.c_str()) >= 0;
}

bool IsLocaleConfigMoreSpecified(const AceResConfig& bestLocaleConfig, const AceResConfig& deviceLocaleConfig,
    const AceResConfig& candidateLocaleConfig)
{
    // Candidates' language and script are equal with the device's after being filtered MatchLocaleConfig().
    std::string deviceRegion = deviceLocaleConfig.region_;
    if (bestLocaleConfig.region_ == deviceRegion) {
        return false;
    }
    if (candidateLocaleConfig.region_ == deviceRegion) {
        return true;
    }
    std::string deviceTag = deviceLocaleConfig.language_ + '-' + deviceLocaleConfig.region_;
    std::vector<std::string> deviceBacktrackPath;
    FindBacktrackPath(deviceLocaleConfig, deviceBacktrackPath, deviceTag);
    std::string bestConfigTag = bestLocaleConfig.language_;
    if (!bestLocaleConfig.region_.empty()) {
        bestConfigTag += '-' + bestLocaleConfig.region_;
    }
    std::string candidateConfigTag = candidateLocaleConfig.language_;
    if (!candidateLocaleConfig.region_.empty()) {
        candidateConfigTag += '-' + candidateLocaleConfig.region_;
    }
    int32_t bestConfigIndex = -1;
    int32_t candidateConfigIndex = -1;
    for (std::size_t i = 0; i < deviceBacktrackPath.size(); i++) {
        if (deviceBacktrackPath[i] == bestConfigTag) {
            bestConfigIndex = i;
        }
        if (deviceBacktrackPath[i] == candidateConfigTag) {
            candidateConfigIndex = i;
        }
    }
    if (bestConfigIndex < candidateConfigIndex) {
        return (bestConfigIndex == -1);
    } else if (candidateConfigIndex < bestConfigIndex) {
        return (candidateConfigIndex != -1);
    }
    // Neither best nor candidate on the device's backtracking path, check if they are the default locale of the device.
    if (candidateConfigIndex == bestConfigIndex && candidateConfigIndex == -1) {
        std::string deviceTagWithScript = deviceLocaleConfig.language_ + "-" + deviceLocaleConfig.script_;
        if (DEFAULT_LANG.find(deviceTagWithScript) != DEFAULT_LANG.end()) {
            std::string defaultTag = DEFAULT_LANG.find(deviceTagWithScript)->second;
            std::string defaultRegion = defaultTag.substr(defaultTag.find('-') + 1);
            if (candidateLocaleConfig.region_ == defaultRegion) {
                return true;
            }
            if (bestLocaleConfig.region_ == defaultRegion) {
                return false;
            }
        }
        // If they are not on the default area, continue to check the candidates' backtacking path.
        return IsOnBacktrackingPath(
            bestConfigTag, candidateConfigTag, bestLocaleConfig, candidateLocaleConfig, deviceBacktrackPath);
    }
    // Both best and candidate on the device's backtracking path with same index.
    return false;
}

void SortLocaleConfigs(std::vector<AceResConfig>& candidatesLocaleConfig, const AceResConfig& deviceLocaleConfig,
    int32_t left, int32_t right)
{
    if (left < right) {
        AceResConfig bestLocaleConfig = candidatesLocaleConfig[left];
        int32_t i = left;
        int32_t j = right;
        while (i < j) {
            while (i < j &&
                   !IsLocaleConfigMoreSpecified(bestLocaleConfig, deviceLocaleConfig, candidatesLocaleConfig[j])) {
                j--;
            }
            candidatesLocaleConfig[i] = candidatesLocaleConfig[j];
            while (
                i < j && IsLocaleConfigMoreSpecified(bestLocaleConfig, deviceLocaleConfig, candidatesLocaleConfig[i])) {
                i++;
            }
            candidatesLocaleConfig[j] = candidatesLocaleConfig[i];
        }
        candidatesLocaleConfig[i] = bestLocaleConfig;
        SortLocaleConfigs(candidatesLocaleConfig, deviceLocaleConfig, left, i - 1);
        SortLocaleConfigs(candidatesLocaleConfig, deviceLocaleConfig, i + 1, right);
    }
}

bool IsLowerResolutionPreferred(int32_t high, int32_t low, int32_t request)
{
    if (request <= low) {
        return true;
    }

    if (request >= high) {
        return false;
    }

    return ((2 * low) - request) * high > request * request; // scaling down is 2x better than up
}

bool IsCandidateResolutionPreferred(
    const AceResConfig& deviceConfig, const AceResConfig& bestConfig, const AceResConfig& candidateConfig)
{
    if (bestConfig.resolution_ == candidateConfig.resolution_) {
        return false;
    }

    const ResolutionType bestRes = bestConfig.resolution_ != ResolutionType::RESOLUTION_NONE
                                       ? bestConfig.resolution_
                                       : ResolutionType::RESOLUTION_MDPI;
    const ResolutionType candidateRes = candidateConfig.resolution_ != ResolutionType::RESOLUTION_NONE
                                            ? candidateConfig.resolution_
                                            : ResolutionType::RESOLUTION_MDPI;

    if (bestRes == ResolutionType::RESOLUTION_ANY) {
        return false;
    } else if (candidateRes == ResolutionType::RESOLUTION_ANY) {
        return true;
    }

    ResolutionType deviceRes = deviceConfig.resolution_;
    if (deviceConfig.resolution_ == ResolutionType::RESOLUTION_NONE ||
        deviceConfig.resolution_ == ResolutionType::RESOLUTION_ANY) {
        deviceRes = ResolutionType::RESOLUTION_MDPI;
    }

    if (bestRes > candidateRes) {
        return IsLowerResolutionPreferred(
            static_cast<int32_t>(bestRes), static_cast<int32_t>(candidateRes), static_cast<int32_t>(deviceRes));
    }

    if (bestRes < candidateRes) {
        return !IsLowerResolutionPreferred(
            static_cast<int32_t>(candidateRes), static_cast<int32_t>(bestRes), static_cast<int32_t>(deviceRes));
    }

    return false;
}

bool IsCandidateResConfigPreferred(
    const AceResConfig& deviceConfig, const AceResConfig& bestConfig, const AceResConfig& candidateConfig)
{
    if ((candidateConfig.mcc_ != bestConfig.mcc_) && deviceConfig.mcc_) {
        return candidateConfig.mcc_;
    }
    if ((candidateConfig.mnc_ != bestConfig.mnc_) && deviceConfig.mnc_) {
        return candidateConfig.mnc_;
    }

    if (bestConfig.orientation_ != candidateConfig.orientation_ &&
        deviceConfig.orientation_ != DeviceOrientation::ORIENTATION_UNDEFINED) {
        return candidateConfig.orientation_ != DeviceOrientation::ORIENTATION_UNDEFINED;
    }

    if (bestConfig.deviceType_ != DeviceType::UNKNOWN || candidateConfig.deviceType_ != DeviceType::UNKNOWN) {
        if (bestConfig.deviceType_ != candidateConfig.deviceType_) {
            return candidateConfig.deviceType_ != DeviceType::UNKNOWN;
        }
    }

    if (bestConfig.colorMode_ != candidateConfig.colorMode_) {
        return candidateConfig.colorMode_ == deviceConfig.colorMode_;
    }

    return IsCandidateResolutionPreferred(deviceConfig, bestConfig, candidateConfig);
}

void SortResConfigs(
    const AceResConfig& desiredConfig, std::vector<AceResConfig>& candidateConfigs, int32_t left, int32_t right)
{
    if (left < right) {
        AceResConfig bestConfig = candidateConfigs[left];
        int32_t i = left;
        int32_t j = right;
        while (i < j) {
            while (i < j && !IsCandidateResConfigPreferred(desiredConfig, bestConfig, candidateConfigs[j])) {
                j--;
            }
            candidateConfigs[i] = candidateConfigs[j];
            while (i < j && IsCandidateResConfigPreferred(desiredConfig, bestConfig, candidateConfigs[i])) {
                i++;
            }
            candidateConfigs[j] = candidateConfigs[i];
        }
        candidateConfigs[i] = bestConfig;
        SortResConfigs(desiredConfig, candidateConfigs, left, i - 1);
        SortResConfigs(desiredConfig, candidateConfigs, i + 1, right);
    }
}

bool IsOrientationMatch(const AceResConfig& desired, const AceResConfig& supported)
{
    return supported.orientation_ == DeviceOrientation::ORIENTATION_UNDEFINED ||
           supported.orientation_ == desired.orientation_;
}

bool IsDeviceTypeMatch(const AceResConfig& desired, const AceResConfig& supported)
{
    return supported.deviceType_ == DeviceType::UNKNOWN || supported.deviceType_ == desired.deviceType_;
}

bool IsColorModeMatch(const AceResConfig& desired, const AceResConfig& supported)
{
    return supported.colorMode_ == ColorMode::COLOR_MODE_UNDEFINED || supported.colorMode_ == desired.colorMode_;
}

bool IsMccMncMatch(const AceResConfig& desired, const AceResConfig& supported)
{
    if (supported.mcc_ != 0 && supported.mcc_ != desired.mcc_) {
        return false;
    }
    return !(supported.mnc_ != 0 && supported.mnc_ != desired.mnc_);
}

bool IsResolutionMatch(const AceResConfig& desired, const AceResConfig& supported)
{
    return supported.resolution_ == ResolutionType::RESOLUTION_NONE || supported.resolution_ == desired.resolution_;
}

bool MatchResConfig(const AceResConfig& desired, const AceResConfig& supported)
{
    return !(!IsOrientationMatch(desired, supported) || !IsDeviceTypeMatch(desired, supported) ||
             !IsColorModeMatch(desired, supported) || !IsMccMncMatch(desired, supported) ||
             !IsResolutionMatch(desired, supported));
}

} // namespace

bool AceResConfig::operator==(const AceResConfig& other) const
{
    return language_ == other.language_ && script_ == other.script_ && region_ == other.region_ && mcc_ == other.mcc_ &&
           mnc_ == other.mnc_ && orientation_ == other.orientation_ && colorMode_ == other.colorMode_ &&
           deviceType_ == other.deviceType_ && resolution_ == other.resolution_;
}

void AceResConfig::MatchAndSortI18nConfigs(const std::vector<std::string>& candidatesFiles,
    const std::string& devicesLocaleTag, std::vector<std::string>& fileList)
{
    std::vector<AceResConfig> candidateLocaleConfigs;
    for (auto& file : candidatesFiles) {
        AceResConfig LocaleConfig = ConvertLocaleTagToConfig(file);
        if (file == ConvertLocaleConfigToTag(LocaleConfig)) {
            candidateLocaleConfigs.emplace_back(LocaleConfig);
        }
    }
    AceResConfig deviceLocaleConfig = ConvertLocaleTagToConfig(devicesLocaleTag);
    // Compute Script when it is not provided.
    if (deviceLocaleConfig.script_.empty()) {
        deviceLocaleConfig.script_ = ComputeScript(deviceLocaleConfig);
    }
    std::vector<AceResConfig> matchedLocaleConfigs;
    MatchLocaleConfig(candidateLocaleConfigs, deviceLocaleConfig, matchedLocaleConfigs);
    int32_t left = 0;
    int32_t right = matchedLocaleConfigs.size() - 1;
    SortLocaleConfigs(matchedLocaleConfigs, deviceLocaleConfig, left, right);
    bool existDefault = false;
    for (const auto& matchedLocaleConfig : matchedLocaleConfigs) {
        std::string localeConfigTag = ConvertLocaleConfigToTag(matchedLocaleConfig);
        if (localeConfigTag == "en-US") {
            existDefault = true;
        }
        fileList.emplace_back(localeConfigTag);
    }

    if (!existDefault) {
        fileList.emplace_back("en-US");
    }
}

void AceResConfig::MatchAndSortResConfigs(const std::vector<std::string>& candidateFiles,
    const std::string& deviceResTag, std::vector<std::string>& matchedFileList)
{
    std::vector<AceResConfig> candidateResConfigs;
    for (auto& file : candidateFiles) {
        AceResConfig ResConfig = ConvertResTagToConfig(file);
        if (file == ConvertResConfigToTag(ResConfig)) {
            candidateResConfigs.emplace_back(ResConfig);
        }
    }

    AceResConfig deviceResConfig = ConvertResTagToConfig(deviceResTag);
    int32_t candidateConfigSize = candidateResConfigs.size();
    std::vector<AceResConfig> matchedResConfigs;
    for (auto i = 0; i < candidateConfigSize; i++) {
        if (!MatchResConfig(deviceResConfig, candidateResConfigs[i])) {
            continue;
        } else {
            matchedResConfigs.emplace_back(candidateResConfigs[i]);
        }
    }
    int32_t left = 0;
    int32_t right = matchedResConfigs.size() - 1;
    SortResConfigs(deviceResConfig, matchedResConfigs, left, right);
    for (const auto& matchedConfig : matchedResConfigs) {
        matchedFileList.emplace_back(ConvertResConfigToTag(matchedConfig));
    }
    matchedFileList.emplace_back("res-defaults");
}

void AceResConfig::GetConfigString(KeyType type, int32_t value, std::string& buf)
{
    std::string appending;
    if (!buf.empty()) {
        appending = "-";
    }

    switch (type) {
        case KeyType::ORIENTATION:
            appending.append(
                AceResKeyParser::GetInstance().GetOrientationByType(static_cast<DeviceOrientation>(value)));
            break;
        case KeyType::DEVICETYPE:
            appending.append(AceResKeyParser::GetInstance().GetDeviceByType(static_cast<DeviceType>(value)));
            break;
        case KeyType::RESOLUTION:
            appending.append(AceResKeyParser::GetInstance().GetResolutionByType(static_cast<ResolutionType>(value)));
            break;
        case KeyType::COLOR_MODE:
            appending.append(AceResKeyParser::GetInstance().GetColorModeByType(static_cast<ColorMode>(value)));
            break;
        case KeyType::MCC:
            appending.append(AceResKeyParser::GetInstance().GetMccByValue(value));
            break;
        case KeyType::MNC_SHORT_LEN:
            appending.append(AceResKeyParser::GetInstance().GetMncShortLenByValue(value));
            break;
        case KeyType::MNC:
            appending.append(AceResKeyParser::GetInstance().GetMncByValue(value));
            break;
        default:
            break;
    }
    buf.append(appending);
}

bool AceResConfig::ParseConfig(const std::vector<KeyParam>& keyParams)
{
    for (auto keyParam : keyParams) {
        switch (keyParam.keyType) {
            case KeyType::RESOLUTION:
                resolution_ = static_cast<ResolutionType>(keyParam.value);
                break;
            case KeyType::ORIENTATION:
                orientation_ = static_cast<DeviceOrientation>(keyParam.value);
                break;
            case KeyType::DEVICETYPE:
                deviceType_ = static_cast<DeviceType>(keyParam.value);
                break;
            case KeyType::COLOR_MODE:
                colorMode_ = static_cast<ColorMode>(keyParam.value);
                break;
            case KeyType::MCC:
                mcc_ = keyParam.value;
                break;
            case KeyType::MNC:
                mnc_ = keyParam.value;
                break;
            case KeyType::MNC_SHORT_LEN:
                mnc_ = keyParam.value;
                mncShortLen_ = true;
                break;
            default:
                LOGE("unknown KeyType:%{public}d", keyParam.keyType);
                break;
        }
    }
    return true;
}

ResolutionType AceResConfig::GetResolutionType(double resolution)
{
    static const LinearEnumMapNode<ResolutionType, bool (*)(double)> resolutionMap[] = {
        { ResolutionType::RESOLUTION_LDPI,
            [](double resolution) { return GreatNotEqual(resolution, 0.0) && LessNotEqual(resolution, 0.875); } },
        { ResolutionType::RESOLUTION_MDPI,
            [](double resolution) { return GreatOrEqual(resolution, 0.875) && LessNotEqual(resolution, 1.25); } },
        { ResolutionType::RESOLUTION_HDPI,
            [](double resolution) { return GreatOrEqual(resolution, 1.25) && LessNotEqual(resolution, 1.75); } },
        { ResolutionType::RESOLUTION_XHDPI,
            [](double resolution) { return GreatOrEqual(resolution, 1.75) && LessNotEqual(resolution, 2.5); } },
        { ResolutionType::RESOLUTION_XXHDPI,
            [](double resolution) { return GreatOrEqual(resolution, 2.5) && LessNotEqual(resolution, 3.5); } },
        { ResolutionType::RESOLUTION_XXXHDPI, [](double resolution) { return GreatOrEqual(resolution, 3.5); } },
    };

    for (const auto& idx : resolutionMap) {
        if (idx.value(resolution)) {
            return idx.key;
        }
    }
    return ResolutionType::RESOLUTION_MDPI;
}

AceResConfig AceResConfig::ConvertResTagToConfig(const std::string& deviceResConfigTag)
{
    AceResConfig resConfig;
    std::vector<KeyParam> keyParams;
    bool parseSucceed = AceResKeyParser::GetInstance().Parse(deviceResConfigTag, keyParams);
    if (parseSucceed) {
        resConfig.ParseConfig(keyParams);
    }
    return resConfig;
}

std::string AceResConfig::ConvertResConfigToTag(const AceResConfig& resConfig)
{
    std::string resTag = "res";
    if (resConfig.mcc_ != MCC_UNDEFINED && resConfig.mnc_ != MNC_UNDEFINED) {
        GetConfigString(KeyType::MCC, resConfig.mcc_, resTag);
        if (resConfig.mncShortLen_) {
            GetConfigString(KeyType::MNC_SHORT_LEN, resConfig.mnc_, resTag);
        } else {
            GetConfigString(KeyType::MNC, resConfig.mnc_, resTag);
        }
    }

    if (resConfig.orientation_ != DeviceOrientation::ORIENTATION_UNDEFINED) {
        GetConfigString(KeyType::ORIENTATION, static_cast<int32_t>(resConfig.orientation_), resTag);
    }

    if (resConfig.colorMode_ != ColorMode::COLOR_MODE_UNDEFINED) {
        GetConfigString(KeyType::COLOR_MODE, static_cast<int32_t>(resConfig.colorMode_), resTag);
    }

    if (resConfig.deviceType_ != DeviceType::UNKNOWN) {
        GetConfigString(KeyType::DEVICETYPE, static_cast<int32_t>(resConfig.deviceType_), resTag);
    }

    if (resConfig.resolution_ != ResolutionType::RESOLUTION_NONE) {
        GetConfigString(KeyType::RESOLUTION, static_cast<int32_t>(resConfig.resolution_), resTag);
    }
    return resTag;
}

} // namespace OHOS::Ace