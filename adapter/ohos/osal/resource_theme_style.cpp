/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "adapter/ohos/osal/resource_theme_style.h"

#include <set>

namespace OHOS::Ace {
namespace {
constexpr char COLOR_VALUE_PREFIX[] = "$color:";
constexpr char MEDIA_VALUE_PREFIX[] = "/";
constexpr char REF_ATTR_VALUE_KEY_WORD[] = "?theme:";

constexpr char RES_TAG[] = "resource:///";
// resource manager hap for system resource
constexpr char RES_HAP_PREFIX[] = "ohos.global.systemres";
#ifdef PREVIEW
constexpr char RES_PATH_TAG[] = "file://";
// resource manager hap absolute path, as resource manager api don't return
constexpr char RES_HAP_PATH[] = "../resources/";
#else
constexpr char RES_PATH_TAG[] = "file:///";
// resource manager hap absolute path, as resource manager api don't return
constexpr char RES_HAP_PATH[] = "/data/storage/el1/bundle/ohos.global.systemres/ohos.global.systemres/assets/";
#endif

static const std::set<std::string> stringAttrs = {
    "attribute_text_font_family_regular",
    "attribute_text_font_family_medium",
    "description_current_location",
    "description_add_location",
    "description_select_location",
    "description_share_location",
    "description_send_location",
    "description_locating",
    "description_location",
    "description_send_current_location",
    "description_relocation",
    "description_punch_in",
    "description_current_position",
    "description_paste",
    "description_download",
    "description_download_files",
    "description_save",
    "description_save_images",
    "description_save_files",
    "description_download_and_share",
    "description_receive",
    "description_continue_to_receive",
    "draggable",
};

double ParseDoubleUnit(const std::string& value, std::string& unit)
{
    for (size_t i = 0; i < value.length(); i++) {
        if (i == 0 && (value[i] == '-' || value[i] == '+')) {
            continue;
        }
        if (value[i] != '.' && (value[i] < '0' || value[i] > '9')) {
            unit = value.substr(i);
            return std::atof(value.substr(0, i).c_str());
        }
    }
    return std::atof(value.c_str());
}

DimensionUnit ParseDimensionUnit(const std::string& unit)
{
    if (unit == "px") {
        return DimensionUnit::PX;
    } else if (unit == "fp") {
        return DimensionUnit::FP;
    } else if (unit == "lpx") {
        return DimensionUnit::LPX;
    } else if (unit == "%") {
        return DimensionUnit::PERCENT;
    } else {
        return DimensionUnit::VP;
    }
}
}

void ResourceThemeStyle::ParseContent()
{
    for (auto& [attrName, attrValue] : rawAttrs_) {
        if (attrName.empty() || attrValue.empty()) {
            LOGD("theme attr name:%{public}s or value:%{public}s is empty", attrName.c_str(), attrValue.c_str());
            continue;
        }
        if (attrValue.front() == '#' || attrValue.find(COLOR_VALUE_PREFIX) != std::string::npos) {
            // color
            attributes_[attrName] = { .type = ThemeConstantsType::COLOR, .value = Color::FromString(attrValue) };
        } else if (attrValue.find(MEDIA_VALUE_PREFIX) != std::string::npos) {
            OnParseResourceMedia(attrName, attrValue);
        } else if (stringAttrs.find(attrName) != stringAttrs.end()) {
            // string
            attributes_[attrName] = { .type = ThemeConstantsType::STRING, .value = attrValue };
        } else if (attrValue.find(REF_ATTR_VALUE_KEY_WORD) != std::string::npos) {
            attributes_[attrName] = { .type = ThemeConstantsType::REFERENCE_ATTR, .value = attrValue };
        } else {
            // double & dimension
            std::string unit = "";
            auto doubleValue = ParseDoubleUnit(attrValue, unit);
            if (unit.empty()) {
                attributes_[attrName] = { .type = ThemeConstantsType::DOUBLE, .value = doubleValue };
            } else {
                attributes_[attrName] = { .type = ThemeConstantsType::DIMENSION,
                    .value = Dimension(doubleValue, ParseDimensionUnit(unit)) };
            }
        }
    }
    LOGD("theme attribute size:%{public}zu", attributes_.size());
    OnParseStyle();
}

void ResourceThemeStyle::OnParseStyle()
{
    for (auto& [patternName, patternMap]: patternAttrs_) {
        auto patternStyle = AceType::MakeRefPtr<ResourceThemeStyle>(resAdapter_);
        patternStyle->SetName(patternName);
        patternStyle->parentStyle_ = AceType::WeakClaim(this);
        patternStyle->rawAttrs_ = patternMap;
        patternStyle->ParseContent();
        attributes_[patternName] = { .type = ThemeConstantsType::PATTERN,
            .value = RefPtr<ThemeStyle>(std::move(patternStyle)) };
    }
}

void ResourceThemeStyle::OnParseResourceMedia(const std::string& attrName, const std::string& attrValue)
{
    std::string mediaPath;
    if (SystemProperties::GetUnZipHap()) {
        mediaPath = RES_PATH_TAG;
        if (attrValue.find(RES_HAP_PREFIX) == std::string::npos) {
            mediaPath.append(RES_HAP_PATH);
        }
        mediaPath += attrValue;
    } else {
        // hap is not unzip, should use resource name to read file
        auto pos = attrValue.find_last_of(MEDIA_VALUE_PREFIX);
        if (pos == std::string::npos) {
            LOGW("resource media invalid:[%{public}s, %{public}s]", attrName.c_str(), attrValue.c_str());
            return;
        }
        mediaPath = std::string(RES_TAG) + attrValue.substr(pos + 1);
    }
    attributes_[attrName] = { .type = ThemeConstantsType::STRING, .value = mediaPath };
}
} // namespace OHOS::Ace
