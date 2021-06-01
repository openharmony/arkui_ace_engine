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

#include "core/components/theme/resource_adapter_preview.h"

#include <fstream>
#include <regex>
#include <unistd.h>

#include "frameworks/base/json/json_util.h"

namespace OHOS::Ace {
namespace {

constexpr uint32_t SYSTEM_RES_ID_BASE = 0x7000000;
const std::string FLOAT_REFERENCE_PREFIX = "$float:";
const std::string STRING_REFERENCE_PREFIX = "$string:";
const std::string PATTERN_REFERENCE_PREFIX = "$pattern:";
const std::string COLOR_REFERENCE_PREFIX = "$color:";
const std::string THEME_DYNAMIC_REFERENCE_PREFIX = "?theme:";
// the length of dimension unit(vp/fp) is 2.
constexpr int32_t DIMENSION_UNIT_LENGTH = 2;
const std::regex COLOR_REGEX("#[0-9A-Fa-f]{6,8}");
// end with fp/vp
const std::regex DIMENSION_UNIT_REGEX("[fsvd]p$");
// non negative float or int number
const std::regex NON_NEGATIVE_FLOAT_OR_INT_REGEX("^(\\d+)(\\.?)(\\d*)$");
#if defined(WINDOWS_PLATFORM)
const std::string SYSTEM_RESOURCE_BASE_ELEMENT_DIR_SUFFIX = "\\base\\element\\";
const std::string SYSTEM_RESOURCE_DARK_ELEMENT_DIR_SUFFIX = "\\dark\\element\\";
#else
// for MAC platform
const std::string SYSTEM_RESOURCE_BASE_ELEMENT_DIR_SUFFIX = "/base/element/";
const std::string SYSTEM_RESOURCE_DARK_ELEMENT_DIR_SUFFIX = "/dark/element/";
#endif
const std::string BASE_FLOAT_JSON_FILE_SUFFIX = SYSTEM_RESOURCE_BASE_ELEMENT_DIR_SUFFIX + "float.json";
const std::string DARK_FLOAT_JSON_FILE_SUFFIX = SYSTEM_RESOURCE_DARK_ELEMENT_DIR_SUFFIX + "float.json";
const std::string BASE_STRINGS_JSON_FILE_SUFFIX = SYSTEM_RESOURCE_BASE_ELEMENT_DIR_SUFFIX + "strings.json";
const std::string BASE_COLORS_JSON_FILE_SUFFIX = SYSTEM_RESOURCE_BASE_ELEMENT_DIR_SUFFIX + "colors.json";
const std::string DARK_COLORS_JSON_FILE_SUFFIX = SYSTEM_RESOURCE_DARK_ELEMENT_DIR_SUFFIX + "colors.json";
const std::string BASE_DARK_COLORS_JSON_FILE_SUFFIX = SYSTEM_RESOURCE_BASE_ELEMENT_DIR_SUFFIX + "colors_dark.json";
const std::string BASE_PATTENS_LIGHT_JSON_FILE_SUFFIX = SYSTEM_RESOURCE_BASE_ELEMENT_DIR_SUFFIX + "patterns_light.json";
const std::string BASE_PATTENS_DARK_JSON_FILE_SUFFIX = SYSTEM_RESOURCE_BASE_ELEMENT_DIR_SUFFIX + "patterns_dark.json";
const std::string BASE_THEME_LIGHT_JSON_FILE_SUFFIX = SYSTEM_RESOURCE_BASE_ELEMENT_DIR_SUFFIX + "theme_light.json";
const std::string BASE_THEME_DARK_JSON_FILE_SUFFIX = SYSTEM_RESOURCE_BASE_ELEMENT_DIR_SUFFIX + "theme_dark.json";
const std::string BASE_RECORD_JSON_FILE_SUFFIX = SYSTEM_RESOURCE_BASE_ELEMENT_DIR_SUFFIX + "id_defined.json";

} // namespace

RefPtr<ResourceAdapter> ResourceAdapter::Create()
{
    return AceType::MakeRefPtr<ResourceAdapterPreview>();
}

bool ResourceAdapterPreview::ReadFileToString(const std::string& filePath, std::string& fileContent)
{
    std::ifstream inFile(filePath.c_str());
    if (inFile.fail()) {
        LOGE("open file(%{public}s) failed", filePath.c_str());
        inFile.close();
        return false;
    }

    fileContent.clear();
    inFile.seekg(0, std::ios::end);
    fileContent.reserve(static_cast<std::string::size_type>(inFile.tellg()));
    inFile.seekg(0, std::ios::beg);
    fileContent.assign(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>());
    inFile.close();

    return true;
}

bool ResourceAdapterPreview::ConvertFloatValToResValueWrapper(const std::string& floatVal,
    ResValueWrapper& resValWrapper)
{
    std::string dimensionUnit;
    std::string doubleVal;
    if (std::regex_search(floatVal, DIMENSION_UNIT_REGEX)) {
        dimensionUnit = floatVal.substr(floatVal.size() - DIMENSION_UNIT_LENGTH);
        doubleVal = floatVal.substr(0, floatVal.size() - DIMENSION_UNIT_LENGTH);
    } else if (strncmp(floatVal.c_str(), FLOAT_REFERENCE_PREFIX.c_str(), FLOAT_REFERENCE_PREFIX.length()) == 0) {
        auto iter = sysResFloat_.find(floatVal.substr(strlen(FLOAT_REFERENCE_PREFIX.c_str())));
        resValWrapper = iter->second;
        return true;
    } else {
        doubleVal = floatVal;
    }

    if (std::regex_match(doubleVal, NON_NEGATIVE_FLOAT_OR_INT_REGEX)) {
        if (dimensionUnit.empty()) {
            resValWrapper = { .type = ThemeConstantsType::DOUBLE, .value = std::stod(doubleVal) };
            return true;
        }
        if (dimensionUnit == "fp") {
            resValWrapper = { .type = ThemeConstantsType::DIMENSION,
                .value = Dimension(std::stod(doubleVal), DimensionUnit::FP) };
            return true;
        }
        if (dimensionUnit == "vp") {
            resValWrapper = { .type = ThemeConstantsType::DIMENSION,
                .value = Dimension(std::stod(doubleVal), DimensionUnit::VP) };
            return true;
        }
    }
    return false;
}

bool ResourceAdapterPreview::ParseFloatJsonFile(const std::string& jsonFile)
{
    std::string fileContent;
    if (!ReadFileToString(jsonFile, fileContent)) {
        return false;
    }
    auto rootJson = JsonUtil::ParseJsonString(fileContent);
    auto floatVal = rootJson->GetValue("float");
    if (floatVal->IsNull()) {
        LOGE("float not found.");
        return false;
    }

    auto child = floatVal->GetChild();
    while (child && !child->IsNull()) {
        const auto& key = child->GetString("name");
        const auto& value = child->GetString("value");
        child = child->GetNext();
        ResValueWrapper resValWrapper;
        if (!ConvertFloatValToResValueWrapper(value, resValWrapper)) {
            LOGE("convert FloatVal(%{public}s) to ResValueWrapper failed!", value.c_str());
            continue;
        }
        sysResFloat_[key] = resValWrapper;
    }

    return true;
}

bool ResourceAdapterPreview::ParseStringJsonFile(const std::string& jsonFile)
{
    std::string fileContent;
    if (!ReadFileToString(jsonFile, fileContent)) {
        return false;
    }
    auto rootJson = JsonUtil::ParseJsonString(fileContent);
    auto strVal = rootJson->GetValue("string");
    if (strVal->IsNull()) {
        LOGE("ParseStringJsonFile, 'string' not found.");
        return false;
    }

    auto child = strVal->GetChild();
    while (child && !child->IsNull()) {
        const auto& key = child->GetString("name");
        const auto& value = child->GetString("value");
        child = child->GetNext();
        sysResString_[key] = { .type = ThemeConstantsType::STRING, .value = value };
    }

    return true;
}

bool ResourceAdapterPreview::ConvertColorValToResValueWrapper(const std::string& colorVal,
    ResValueWrapper& resValWrapper)
{
    if (std::regex_match(colorVal, COLOR_REGEX)) {
        resValWrapper = { .type = ThemeConstantsType::COLOR, .value = Color::FromString(colorVal) };
        return true;
    }
    if (strncmp(colorVal.c_str(), COLOR_REFERENCE_PREFIX.c_str(), COLOR_REFERENCE_PREFIX.length()) == 0) {
        auto iter = sysResColor_.find(colorVal.substr(strlen(COLOR_REFERENCE_PREFIX.c_str())));
        if (iter != sysResColor_.end()) {
            resValWrapper = iter->second;
            return true;
        }
    }
    return false;
}

bool ResourceAdapterPreview::ParseColorJsonFile(const std::string& jsonFile)
{
    std::string fileContent;
    if (!ReadFileToString(jsonFile, fileContent)) {
        return false;
    }
    auto rootJson = JsonUtil::ParseJsonString(fileContent);
    auto colorsVal = rootJson->GetValue("color");
    if (colorsVal->IsNull()) {
        LOGE("ParseColorJsonFile, 'color' not found.");
        return false;
    }

    auto child = colorsVal->GetChild();
    while (child && !child->IsNull()) {
        const auto& key = child->GetString("name");
        const auto& value = child->GetString("value");
        child = child->GetNext();
        ResValueWrapper resValWrapper;
        if (!ConvertColorValToResValueWrapper(value, resValWrapper)) {
            LOGE("convert ColorVal(%{public}s) to ResValueWrapper failed!", value.c_str());
            continue;
        }
        sysResColor_[key] = resValWrapper;
    }

    return true;
}

bool ResourceAdapterPreview::ConvertStringValToResValueWrapper(const std::string& stringVal,
    ResValueWrapper& resValWrapper)
{
    if (strncmp(stringVal.c_str(), STRING_REFERENCE_PREFIX.c_str(), STRING_REFERENCE_PREFIX.length()) == 0) {
        auto iter = sysResString_.find(stringVal.substr(strlen(STRING_REFERENCE_PREFIX.c_str())));
        if (iter != sysResString_.end()) {
            resValWrapper = iter->second;
            return true;
        }
    }
    return false;
}

bool ResourceAdapterPreview::ParsePatternJsonFile(const std::string& jsonFile)
{
    std::string fileContent;
    if (!ReadFileToString(jsonFile, fileContent)) {
        return false;
    }
    auto rootJson = JsonUtil::ParseJsonString(fileContent);
    auto patternVal = rootJson->GetValue("pattern");
    if (patternVal->IsNull()) {
        LOGE("ParsePatternJsonFile, 'pattern' not found.");
        return false;
    }

    auto child = patternVal->GetChild();
    while (child && !child->IsNull()) {
        const auto& key = child->GetString("name");
        const auto& parentValue = child->GetString("parent");
        auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
        if (!parentValue.empty()) {
            auto patternIter =  sysResPattern_.find(parentValue);
            if (patternIter != sysResPattern_.end()) {
                themeStyle = (patternIter->second.GetValue<RefPtr<ThemeStyle>>(nullptr)).second;
            }
        }
        themeStyle->SetName(key);
        const auto& value = child->GetValue("value");
        child = child->GetNext();
        auto item = value->GetChild();
        while (item && !item->IsNull()) {
            const auto& itemKey = item->GetString("name");
            const auto& itemValue = item->GetString("value");
            item = item->GetNext();
            ResValueWrapper resValWrapper;
            if (ConvertColorValToResValueWrapper(itemValue, resValWrapper)) {
                themeStyle->SetAttr(itemKey, resValWrapper);
                continue;
            }
            if (ConvertFloatValToResValueWrapper(itemValue, resValWrapper)) {
                themeStyle->SetAttr(itemKey, resValWrapper);
                continue;
            }
            if (strncmp(itemValue.c_str(), THEME_DYNAMIC_REFERENCE_PREFIX.c_str(),
                THEME_DYNAMIC_REFERENCE_PREFIX.length()) == 0) {
                resValWrapper = { .type = ThemeConstantsType::REFERENCE_ATTR, .value = itemValue };
                themeStyle->SetAttr(itemKey, resValWrapper);
                continue;
            }
            if (ConvertStringValToResValueWrapper(itemValue, resValWrapper)) {
                themeStyle->SetAttr(itemKey, resValWrapper);
                continue;
            }
        }
        sysResPattern_[key] = { .type = ThemeConstantsType::PATTERN, .value = std::move(themeStyle) };
    }

    return true;
}

bool ResourceAdapterPreview::ConvertThemeValToResValueWrapper(const std::string& themeVal,
    ResValueWrapper& resValWrapper)
{
    if (ConvertColorValToResValueWrapper(themeVal, resValWrapper)) {
        return true;
    }
    if (ConvertFloatValToResValueWrapper(themeVal, resValWrapper)) {
        return true;
    }
    if (ConvertStringValToResValueWrapper(themeVal, resValWrapper)) {
        return true;
    }
    if (strncmp(themeVal.c_str(), PATTERN_REFERENCE_PREFIX.c_str(), PATTERN_REFERENCE_PREFIX.length()) == 0) {
        auto iter = sysResPattern_.find(themeVal.substr(strlen(PATTERN_REFERENCE_PREFIX.c_str())));
        if (iter != sysResPattern_.end()) {
            resValWrapper = iter->second;
            return true;
        }
    }
    return false;
}

bool ResourceAdapterPreview::ParseThemeJsonFile(const std::string& jsonFile)
{
    std::string fileContent;
    if (!ReadFileToString(jsonFile, fileContent)) {
        return false;
    }
    auto rootJson = JsonUtil::ParseJsonString(fileContent);
    auto themeVal = rootJson->GetValue("theme");
    if (themeVal->IsNull()) {
        LOGE("ParseThemeJsonFile, 'theme' not found.");
        return false;
    }

    auto child = themeVal->GetChild();
    while (child && !child->IsNull()) {
        const auto& key = child->GetString("name");
        const auto& parentValue = child->GetString("parent");
        auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
        if (!parentValue.empty()) {
            auto themeIter =  sysResTheme_.find(parentValue);
            if (themeIter != sysResTheme_.end()) {
                themeStyle = (themeIter->second.GetValue<RefPtr<ThemeStyle>>(nullptr)).second;
            }
        }
        themeStyle->SetName(key);
        const auto& value = child->GetValue("value");
        child = child->GetNext();
        auto item = value->GetChild();
        while (item && !item->IsNull()) {
            const auto& itemKey = item->GetString("name");
            const auto& itemValue = item->GetString("value");
            item = item->GetNext();
            ResValueWrapper resValWrapper;
            if (!ConvertThemeValToResValueWrapper(itemValue, resValWrapper)) {
                LOGW("convert themeval(=%{public}s) to ResValueWrapper failed", itemValue.c_str());
                continue;
            }
            themeStyle->SetAttr(itemKey, resValWrapper);
        }
        sysResTheme_[key] = { .type = ThemeConstantsType::THEME, .value = std::move(themeStyle) };
    }
    return true;
}

bool ResourceAdapterPreview::PostprocessSystemResources()
{
    // After all json files have been loaded, resolve references to theme element in pattern element.
    for (auto themeIter = sysResTheme_.begin(); themeIter != sysResTheme_.end(); ++themeIter) {
        auto themeStyle = (themeIter->second.GetValue<RefPtr<ThemeStyle>>(nullptr)).second;
        if (!themeStyle) {
            LOGW("PostprocessSystemResources invalid theme(%{public}s)", themeIter->first.c_str());
            continue;
        }
        auto themeAttrs = themeStyle->GetAttributes();
        for (auto themeAttrIter = themeAttrs.begin(); themeAttrIter != themeAttrs.end(); ++themeAttrIter) {
            // There are four types of themeAttr: string/color/float/pattern
            // Only element in pattern that reference to theme(for example, "?theme:xxx") need to be resolved by
            // current theme attributes.
            if (themeAttrIter->second.type != ThemeConstantsType::PATTERN) {
                continue;
            }
            auto pattern = (themeAttrIter->second.GetValue<RefPtr<ThemeStyle>>(nullptr)).second;
            if (!pattern) {
                continue;
            }
            // make a copy of pattern with all references are resolved.
            auto resolvedPattern = AceType::MakeRefPtr<ThemeStyle>();
            resolvedPattern->SetName(pattern->GetName());
            auto patternAttrs = pattern->GetAttributes();
            for (auto patternAttrIter = patternAttrs.begin(); patternAttrIter != patternAttrs.end();
                ++patternAttrIter) {
                // There are four types of patternAttr: string/color/float and reference to theme.
                if (patternAttrIter->second.type != ThemeConstantsType::REFERENCE_ATTR) {
                    resolvedPattern->SetAttr(patternAttrIter->first, patternAttrIter->second);
                    continue;
                }
                auto refToTheme = (patternAttrIter->second.GetValue<std::string>("")).second;
                if (strncmp(refToTheme.c_str(), THEME_DYNAMIC_REFERENCE_PREFIX.c_str(),
                    THEME_DYNAMIC_REFERENCE_PREFIX.length()) != 0) {
                    continue;
                }
                auto valueFromTheme = themeAttrs.find(refToTheme.substr(THEME_DYNAMIC_REFERENCE_PREFIX.size()));
                if (valueFromTheme == themeAttrs.end()) {
                    LOGW("can't find pattern(%{public}s) element(%{public}s) in theme(%{public}s)",
                        patternAttrIter->first.c_str(), refToTheme.c_str(), themeIter->first.c_str());
                    continue;
                }
                resolvedPattern->SetAttr(patternAttrIter->first, valueFromTheme->second);
            }
            // update pattern value in theme attributes.
            themeStyle->SetAttr(themeAttrIter->first, {
                .type = ThemeConstantsType::PATTERN,
                .value = std::move(resolvedPattern)
            });
        }
    }
    return true;
}

bool ResourceAdapterPreview::ParseRecordJsonFile(const std::string& jsonFile)
{
    std::string fileContent;
    if (!ReadFileToString(jsonFile, fileContent)) {
        return false;
    }
    auto rootJson = JsonUtil::ParseJsonString(fileContent);
    auto strVal = rootJson->GetValue("record");
    if (strVal->IsNull()) {
        LOGE("ParseStringJsonFile, 'string' not found.");
        return false;
    }

    auto child = strVal->GetChild();
    while (child && !child->IsNull()) {
        const auto& name = child->GetString("name");
        const auto& type = child->GetString("type");
        uint32_t resId = child->GetUInt("order") + SYSTEM_RES_ID_BASE;
        child = child->GetNext();
        sysResRecord_[resId] = std::make_pair(name, type);
    }

    return true;
}

bool ResourceAdapterPreview::LoadSystemResources(const std::string& sysResDir, const int32_t& themeId,
                                                 const ColorMode& colorMode)
{
    LOGI("loading system resources from %{private}s", sysResDir.c_str());
    if (access(sysResDir.c_str(), F_OK) != 0) {
        LOGE("load system resources failed, %{public}s does not exist!", sysResDir.c_str());
        return false;
    }
    // The float/string/color json files are parsed first, then the pattern json files, finally the theme json files.
    ParseFloatJsonFile(sysResDir + BASE_FLOAT_JSON_FILE_SUFFIX);
    ParseStringJsonFile(sysResDir + BASE_STRINGS_JSON_FILE_SUFFIX);
    ParseColorJsonFile(sysResDir + BASE_COLORS_JSON_FILE_SUFFIX);

    // If dark color mode, parse the colors.json and float.json in dark directory.
    if (colorMode == ColorMode::DARK) {
        ParseFloatJsonFile(sysResDir + DARK_FLOAT_JSON_FILE_SUFFIX);
        ParseColorJsonFile(sysResDir + DARK_COLORS_JSON_FILE_SUFFIX);
    }

    ParsePatternJsonFile(sysResDir + BASE_PATTENS_LIGHT_JSON_FILE_SUFFIX);
    ParseThemeJsonFile(sysResDir + BASE_THEME_LIGHT_JSON_FILE_SUFFIX);

    // If dark theme, parse colors_dark.json, patterns_dark.json, theme_dark.json.
    if (themeId == 1) {
        ParseColorJsonFile(sysResDir + BASE_DARK_COLORS_JSON_FILE_SUFFIX);
        ParsePatternJsonFile(sysResDir + BASE_PATTENS_DARK_JSON_FILE_SUFFIX);
        ParseThemeJsonFile(sysResDir + BASE_THEME_DARK_JSON_FILE_SUFFIX);
    }

    PostprocessSystemResources();
    // get the mapping relationship between system resources id and name.
    ParseRecordJsonFile(sysResDir + BASE_RECORD_JSON_FILE_SUFFIX);
    LOGI("load system resources from json, float size = %{public}zu, string size = %{public}zu, "
        "color size = %{public}zu, pattern size = %{public}zu, theme size = %{public}zu, record size = %{public}zu",
        sysResFloat_.size(), sysResString_.size(), sysResColor_.size(), sysResPattern_.size(), sysResTheme_.size(),
        sysResRecord_.size());
    return true;
}

void ResourceAdapterPreview::Init(const DeviceResourceInfo& resourceInfo)
{
    LoadSystemResources(resourceInfo.packagePath, resourceInfo.themeId, resourceInfo.deviceConfig.colorMode);
}

void ResourceAdapterPreview::UpdateConfig(const DeviceConfig& config)
{
    // dynamic theme modification is not supported in PC Preview mode!
    LOGE("ResourceAdapterPreview::UpdateConfig is not implemented yet");
}

RefPtr<ThemeStyle> ResourceAdapterPreview::GetTheme(int32_t themeId)
{
    if (themeId == 1) {
        LOGD("ResourceAdapterPreview::GetTheme(themeId=%{public}d), theme style = theme_dark", themeId);
        auto iter = sysResTheme_.find("theme_dark");
        if (iter == sysResTheme_.end()) {
            LOGE("ResourceAdapterPreview::GetTheme failed, can't find theme.");
            return nullptr;
        }
        auto themeStyle = iter->second.GetValue<RefPtr<ThemeStyle>>(nullptr);
        if (!themeStyle.first) {
            LOGE("ResourceAdapterPreview::GetTheme failed, invalid theme style.");
        }
        return themeStyle.second;
    }

    LOGD("ResourceAdapterPreview::GetTheme(themeId=%{public}d), theme style = theme_light", themeId);
    auto iter = sysResTheme_.find("theme_light");
    if (iter == sysResTheme_.end()) {
        LOGE("ResourceAdapterPreview::GetTheme failed, can't find theme.");
        return nullptr;
    }
    auto themeStyle = iter->second.GetValue<RefPtr<ThemeStyle>>(nullptr);
    if (!themeStyle.first) {
        LOGE("ResourceAdapterPreview::GetTheme failed, invalid theme style.");
    }
    return themeStyle.second;
}

Color ResourceAdapterPreview::GetColor(uint32_t resId)
{
    auto recordIter = sysResRecord_.find(resId);
    if (recordIter == sysResRecord_.end()) {
        LOGW("GetColor can't find resource(id=%{public}u)", resId);
        return Color(0);
    }
    auto resIter = sysResColor_.find(recordIter->second.first);
    if (resIter == sysResColor_.end()) {
        LOGW("GetColor can't find resource(name=%{public}s)", recordIter->second.first.c_str());
        return Color(0);
    }
    auto resVal = resIter->second.GetValue<Color>(Color(0));
    if (!resVal.first) {
        LOGW("GetColor get color value from ResValueWrapper failed");
    }
    return resVal.second;
}

Dimension ResourceAdapterPreview::GetDimension(uint32_t resId)
{
    auto recordIter = sysResRecord_.find(resId);
    if (recordIter == sysResRecord_.end()) {
        LOGW("GetDimension can't find resource(id=%{public}u)", resId);
        return 0.0_vp;
    }
    auto resIter = sysResFloat_.find(recordIter->second.first);
    if (resIter == sysResFloat_.end()) {
        LOGW("GetDimension can't find resource(name=%{public}s)", recordIter->second.first.c_str());
        return 0.0_vp;
    }
    auto resVal = resIter->second.GetValue<Dimension>(0.0_vp);
    if (!resVal.first) {
        LOGW("GetDimension get dimension value from ResValueWrapper failed");
    }
    return resVal.second;
}

std::string ResourceAdapterPreview::GetString(uint32_t resId)
{
    auto recordIter = sysResRecord_.find(resId);
    if (recordIter == sysResRecord_.end()) {
        LOGW("GetString can't find resource(id=%{public}u)", resId);
        return "";
    }
    auto resIter = sysResString_.find(recordIter->second.first);
    if (resIter == sysResString_.end()) {
        LOGW("GetString can't find resource(name=%{public}s)", recordIter->second.first.c_str());
        return "";
    }
    auto resVal = resIter->second.GetValue<std::string>("");
    if (!resVal.first) {
        LOGW("GetString get string value from ResValueWrapper failed");
    }
    return resVal.second;
}

double ResourceAdapterPreview::GetDouble(uint32_t resId)
{
    auto recordIter = sysResRecord_.find(resId);
    if (recordIter == sysResRecord_.end()) {
        LOGW("GetDouble can't find resource(id=%{public}u)", resId);
        return 0.0;
    }
    auto resIter = sysResFloat_.find(recordIter->second.first);
    if (resIter == sysResFloat_.end()) {
        LOGW("GetDouble can't find resource(name=%{public}s)", recordIter->second.first.c_str());
        return 0.0;
    }
    auto resVal = resIter->second.GetValue<double>(0.0);
    if (!resVal.first) {
        LOGW("GetDouble get double value from ResValueWrapper failed");
    }
    return resVal.second;
}

int32_t ResourceAdapterPreview::GetInt(uint32_t resId)
{
    LOGE("ResourceAdapterPreview::GetInt is not implemented yet");
    return 0;
}

} // namespace OHOS::Ace
