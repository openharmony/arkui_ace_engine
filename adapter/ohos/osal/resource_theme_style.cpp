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

#include <regex>
#include <unordered_set>

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

const std::regex DIMENSION_REGEX(R"(^([+-]?\d+(\.\d+)?)(px|fp|lpx|vp|%)?)");
constexpr int32_t WAIT_FOR_TIME = 50;
static const std::unordered_set<std::string> stringAttrs = {
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
    "description_download_file",
    "description_save",
    "description_save_image",
    "description_save_file",
    "description_download_and_share",
    "description_receive",
    "description_continue_to_receive",
    "description_save_to_gallery",
    "description_export_to_gallery",
    "description_quick_save_to_gallery",
    "description_quick_resave_to_gallery",
    "description_save_all",
    "draggable",
    "divider_shadow_enable",
    "camera_input",
    "menu_bg_blur_effect_enable",
    "menu_double_border_enable",
    "section_unfocus_effect_enable",
    "section_unfocus_color",
    "sheet_type",
    "sheet_close",
    "multiple_dialog_display",
    "menu_expand_display",
    "popup_double_border_enable",
    "tips_double_border_enable",
    "dialog_expand_display",
    "show_password_directly",
    "textfield_show_handle",
    "dialog_radius_level10",
    "dialog_icon_primary",
    "dialog_font_primary",
    "menu_has_filter",
    "navigation_general_more",
    "navigation_back",
    "calendar_picker_dialog_button_transparent",
    "calendar_picker_dialog_divider_transparent",
    "textfield_accessibility_property_clear",
    "textfield_accessibility_show_password",
    "textfield_accessibility_hide_password",
    "rich_editor_show_handle",
    "text_show_handle",
    "list_fadeout_enable",
    "text_fadeout_enable",
    "textfield_show_password_button",
    "textfield_hide_password_button",
    "textfield_has_showed_password",
    "textfield_has_hidden_password",
    "calendar_picker_mon",
    "calendar_picker_tue",
    "calendar_picker_wed",
    "calendar_picker_thu",
    "calendar_picker_fri",
    "calendar_picker_sat",
    "calendar_picker_sun",
    "general_today",
    "picker_dialog_lunar_switch",
    "picker_dialog_previous_button",
    "picker_dialog_next_button",
    "filter_accessibility_expand",
    "filter_accessibility_collapse",
    "filter_accessibility_collapsed",
    "filter_accessibility_expanded",
    "slider_accessibility_selected",
    "slider_accessibility_unselected",
    "slider_accessibility_unselectedDesc",
    "slider_accessibility_disabledDesc",
    "stepper_back",
    "stepper_skip",
    "stepper_start",
    "stepper_next",
    "textfield_writting_bundle_name",
    "textfield_writting_ability_name",
    "rich_editor_writting_bundle_name",
    "rich_editor_writting_ability_name",
    "textfield_writting_is_support",
    "rich_editor_writting_is_support",
    "ai_write_menu_name",
    "menu_translate_is_support",
    "text_menu_search_is_support",
    "textfield_menu_search_is_support",
    "richeditor_menu_search_is_support",
    "textfield_accessibility_clear",
    "pass_point",
    "side_length",
    "general_next_year",
    "general_next_month",
    "general_pre_year",
    "general_pre_month",
    "prev_arrow_accessibility_text",
    "next_arrow_accessibility_text",
    "menu_haptic_feedback",
    "text_overlay_menu_cut_label",
    "text_overlay_menu_copy_label",
    "text_overlay_menu_paste_label",
    "text_overlay_menu_select_all_label",
    "text_overlay_menu_translate_label",
    "text_overlay_menu_share_label",
    "text_overlay_menu_search_label",
    "switch_on_text",
    "switch_off_text",
    "common_cancel_text",
    "common_ok_text",
    "textoverlay_paste",
};

void ParseNumberUnit(const std::string& value, std::string& number, std::string& unit)
{
    std::smatch results;
    if (std::regex_search(value, results, DIMENSION_REGEX)) {
        number = results[1];
        // The unit is in the 3rd sub-match. If the value doesn't have unit,
        // the 3rd match result is empty.
        unit = results[3];
    }
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
    for (const auto& [attrName, attrValue] : rawAttrs_) {
        if (attrName.empty() || attrValue.empty()) {
            continue;
        }
        if (stringAttrs.find(attrName) != stringAttrs.end()) {
            // string
            attributes_[attrName] = { .type = ThemeConstantsType::STRING, .value = attrValue };
            continue;
        }
        if (attrValue.front() == '#' || attrValue.find(COLOR_VALUE_PREFIX) != std::string::npos) {
            // color
            attributes_[attrName] = { .type = ThemeConstantsType::COLOR, .value = Color::FromString(attrValue) };
        } else if (attrValue.find(MEDIA_VALUE_PREFIX) != std::string::npos) {
            OnParseResourceMedia(attrName, attrValue);
        } else if (attrValue.find(REF_ATTR_VALUE_KEY_WORD) != std::string::npos) {
            attributes_[attrName] = { .type = ThemeConstantsType::REFERENCE_ATTR, .value = attrValue };
        } else {
            // int & double & dimension
            std::string number;
            std::string unit;
            ParseNumberUnit(attrValue, number, unit);
            if (number.empty()) {
                continue;
            } else if (!unit.empty()) {
                attributes_[attrName] = { .type = ThemeConstantsType::DIMENSION,
                    .value = Dimension(std::atof(number.c_str()), ParseDimensionUnit(unit)) };
            } else if (number.find(".") == std::string::npos) {
                attributes_[attrName] = { .type = ThemeConstantsType::INT, .value = std::atoi(number.c_str()) };
            } else {
                attributes_[attrName] = { .type = ThemeConstantsType::DOUBLE, .value = std::atof(number.c_str()) };
            }
        }
    }
    OnParseStyle();
}

void ResourceThemeStyle::OnParseStyle()
{
    for (const auto& [patternName, patternMap]: patternAttrs_) {
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
#ifdef PREVIEW
        auto pos = attrValue.find(MEDIA_VALUE_PREFIX);
        if (pos == std::string::npos) {
            return;
        }
        mediaPath += attrValue.substr(pos + 1);
#else
        mediaPath += attrValue;
#endif
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

void ResourceThemeStyle::CheckThemeStyleLoaded(const std::string& patternName)
{
    if (!CheckThemeStyle(patternName)) {
        return;
    }
    if (future_.valid()) {
        future_.wait_until(std::chrono::system_clock::now() + std::chrono::milliseconds(WAIT_FOR_TIME));
    }
}
} // namespace OHOS::Ace
