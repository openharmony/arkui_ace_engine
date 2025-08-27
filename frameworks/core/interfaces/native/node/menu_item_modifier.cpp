/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/menu_item_modifier.h"

#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
const char DELIMITER = '|';
constexpr int32_t SIZE_OF_FONT_INFO = 3;
static const char* ERR_CODE = "-1";
const std::string DEFAULT_FONT_WEIGHT = "normal";
const std::string DEFAULT_FONT_FAMILY = "HarmonyOS Sans";
const Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
void SetMenuItemSelected(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetSelected(frameNode, value);
}

void ResetMenuItemSelected(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetSelected(frameNode, false);
}

void SetLabelFontColor(ArkUINodeHandle node, const uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetLabelFontColor(frameNode, Color(color));
}

void SetLabelFontColorWithResource(ArkUINodeHandle node, const uint32_t color, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetLabelFontColor(frameNode, Color(color));
    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        MenuItemModelNG::CreateWithColorResourceObj(frameNode, colorResObj, MenuItemFontColorType::LABEL_FONT_COLOR);
    }
}

void ResetLabelFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> color = std::nullopt;
    MenuItemModelNG::SetLabelFontColor(frameNode, color);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> nullResObj = nullptr;
        MenuItemModelNG::CreateWithColorResourceObj(frameNode, nullResObj, MenuItemFontColorType::LABEL_FONT_COLOR);
    }
}

void SetContentFontColor(ArkUINodeHandle node, const uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetFontColor(frameNode, Color(color));
}

void SetContentFontColorWithResource(ArkUINodeHandle node, const uint32_t color, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetFontColor(frameNode, Color(color));
    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        MenuItemModelNG::CreateWithColorResourceObj(frameNode, colorResObj, MenuItemFontColorType::FONT_COLOR);
    }
}

void ResetContentFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> color = std::nullopt;
    MenuItemModelNG::SetFontColor(frameNode, color);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> nullResObj = nullptr;
        MenuItemModelNG::CreateWithColorResourceObj(frameNode, nullResObj, MenuItemFontColorType::FONT_COLOR);
    }
}

void SetLabelFont(ArkUINodeHandle node, const char* fontInfo, int32_t styleVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DELIMITER, res);
    if (res.empty() || res.size() != SIZE_OF_FONT_INFO) {
        return;
    }
    CalcDimension fontSize;
    if (res[0] != ERR_CODE) { // 0: position of font size data
        fontSize = StringUtils::StringToCalcDimension(res[0], false, DimensionUnit::FP);
    }
    MenuItemModelNG::SetLabelFontSize(frameNode, fontSize);

    if (res[1] != ERR_CODE) { // 1: position of font weight data
        MenuItemModelNG::SetLabelFontWeight(frameNode, Framework::ConvertStrToFontWeight(res[1]));
    } else {
        MenuItemModelNG::SetLabelFontWeight(frameNode, FontWeight::NORMAL);
    }

    if (styleVal >= 0 && styleVal < static_cast<int32_t>(FONT_STYLES.size())) {
        MenuItemModelNG::SetLabelFontStyle(frameNode, FONT_STYLES[styleVal]);
    } else {
        MenuItemModelNG::SetLabelFontStyle(frameNode, DEFAULT_FONT_STYLE);
    }

    if (res[2] != ERR_CODE) { // 2: position of font family data
        MenuItemModelNG::SetLabelFontFamily(frameNode, Framework::ConvertStrToFontFamilies(res[2]));
    } else {
        MenuItemModelNG::SetLabelFontFamily(frameNode, Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY));
    }
}

void SetLabelFontWithResource(ArkUINodeHandle node, const char* fontInfo, int32_t styleVal, void* fontSizeRawPtr,
    void* fontFamilyRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DELIMITER, res);
    if (res.empty() || res.size() != SIZE_OF_FONT_INFO) {
        return;
    }
    CalcDimension fontSize;
    if (res[0] != ERR_CODE) { // 0: position of font size data
        fontSize = StringUtils::StringToCalcDimension(res[0], false, DimensionUnit::FP);
    }
    MenuItemModelNG::SetLabelFontSize(frameNode, fontSize);
    if (SystemProperties::ConfigChangePerform() && fontSizeRawPtr) {
        auto* fontSizePtr = reinterpret_cast<ResourceObject*>(fontSizeRawPtr);
        auto fontSizeResObj = AceType::Claim(fontSizePtr);
        MenuItemModelNG::CreateWithDimensionFpResourceObj(
            frameNode, fontSizeResObj, MenuItemFontSizeType::LABEL_FONT_SIZE);
    }

    if (res[1] != ERR_CODE) { // 1: position of font weight data
        MenuItemModelNG::SetLabelFontWeight(frameNode, Framework::ConvertStrToFontWeight(res[1]));
    } else {
        MenuItemModelNG::SetLabelFontWeight(frameNode, FontWeight::NORMAL);
    }

    if (styleVal >= 0 && styleVal < static_cast<int32_t>(FONT_STYLES.size())) {
        MenuItemModelNG::SetLabelFontStyle(frameNode, FONT_STYLES[styleVal]);
    } else {
        MenuItemModelNG::SetLabelFontStyle(frameNode, DEFAULT_FONT_STYLE);
    }

    if (res[2] != ERR_CODE) { // 2: position of font family data
        MenuItemModelNG::SetLabelFontFamily(frameNode, Framework::ConvertStrToFontFamilies(res[2]));
        if (SystemProperties::ConfigChangePerform() && fontFamilyRawPtr) {
            auto* fontFamilyPtr = reinterpret_cast<ResourceObject*>(fontFamilyRawPtr);
            auto fontFamilyResObj = AceType::Claim(fontFamilyPtr);
            MenuItemModelNG::CreateWithFontFamilyResourceObj(
                frameNode, fontFamilyResObj, MenuItemFontFamilyType::LABEL_FONT_FAMILY);
        }
    } else {
        MenuItemModelNG::SetLabelFontFamily(frameNode, Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY));
    }
}

void ResetLabelFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension fontSize;
    FontWeight fontWeight = StringUtils::StringToFontWeight(DEFAULT_FONT_WEIGHT);
    MenuItemModelNG::SetLabelFontSize(frameNode, fontSize);
    MenuItemModelNG::SetLabelFontWeight(frameNode, fontWeight);
    MenuItemModelNG::SetLabelFontFamily(frameNode, Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY));
    MenuItemModelNG::SetLabelFontStyle(frameNode, DEFAULT_FONT_STYLE);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> nullResObj = nullptr;
        MenuItemModelNG::CreateWithDimensionFpResourceObj(
            frameNode, nullResObj, MenuItemFontSizeType::LABEL_FONT_SIZE);
        MenuItemModelNG::CreateWithFontFamilyResourceObj(
            frameNode, nullResObj, MenuItemFontFamilyType::LABEL_FONT_FAMILY);
    }
}

void SetContentFont(ArkUINodeHandle node, const char* fontInfo, int32_t styleVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DELIMITER, res);
    if (res.empty() || res.size() != SIZE_OF_FONT_INFO) {
        return;
    }

    CalcDimension fontSize;
    if (res[0] != ERR_CODE) { // 0: position of font size data
        fontSize = StringUtils::StringToCalcDimension(res[0], false, DimensionUnit::FP);
    }
    MenuItemModelNG::SetFontSize(frameNode, fontSize);
    if (res[1] != ERR_CODE) { // 1: position of font weight data
        MenuItemModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(res[1]));
    } else {
        MenuItemModelNG::SetFontWeight(frameNode, FontWeight::NORMAL);
    }

    if (styleVal >= 0 && styleVal < static_cast<int32_t>(FONT_STYLES.size())) {
        MenuItemModelNG::SetFontStyle(frameNode, FONT_STYLES[styleVal]);
    } else {
        MenuItemModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
    }

    if (res[2] != ERR_CODE) { // 2: position of font family data
        MenuItemModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(res[2]));
    } else {
        MenuItemModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY));
    }
}

void SetContentFontWithResource(
    ArkUINodeHandle node, const char* fontInfo, int32_t styleVal, void* fontSizeRawPtr, void* fontFamilyRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DELIMITER, res);
    if (res.empty() || res.size() != SIZE_OF_FONT_INFO) {
        return;
    }

    CalcDimension fontSize;
    if (res[0] != ERR_CODE) { // 0: position of font size data
        fontSize = StringUtils::StringToCalcDimension(res[0], false, DimensionUnit::FP);
    }
    MenuItemModelNG::SetFontSize(frameNode, fontSize);
    if (SystemProperties::ConfigChangePerform() && fontSizeRawPtr) {
        auto* fontSizePtr = reinterpret_cast<ResourceObject*>(fontSizeRawPtr);
        auto fontSizeResObj = AceType::Claim(fontSizePtr);
        MenuItemModelNG::CreateWithDimensionFpResourceObj(frameNode, fontSizeResObj, MenuItemFontSizeType::FONT_SIZE);
    }

    if (res[1] != ERR_CODE) { // 1: position of font weight data
        MenuItemModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(res[1]));
    } else {
        MenuItemModelNG::SetFontWeight(frameNode, FontWeight::NORMAL);
    }

    if (styleVal >= 0 && styleVal < static_cast<int32_t>(FONT_STYLES.size())) {
        MenuItemModelNG::SetFontStyle(frameNode, FONT_STYLES[styleVal]);
    } else {
        MenuItemModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
    }

    if (res[2] != ERR_CODE) { // 2: position of font family data
        MenuItemModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(res[2]));
        if (SystemProperties::ConfigChangePerform() && fontFamilyRawPtr) {
            auto* fontFamilyPtr = reinterpret_cast<ResourceObject*>(fontFamilyRawPtr);
            auto fontFamilyResObj = AceType::Claim(fontFamilyPtr);
            MenuItemModelNG::CreateWithFontFamilyResourceObj(
                frameNode, fontFamilyResObj, MenuItemFontFamilyType::FONT_FAMILY);
        }
    } else {
        MenuItemModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY));
    }
}

void ResetContentFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension fontSize;
    FontWeight fontWeight = StringUtils::StringToFontWeight(DEFAULT_FONT_WEIGHT);
    MenuItemModelNG::SetFontSize(frameNode, fontSize);
    MenuItemModelNG::SetFontWeight(frameNode, fontWeight);
    MenuItemModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY));
    MenuItemModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> nullResObj = nullptr;
        MenuItemModelNG::CreateWithFontFamilyResourceObj(frameNode, nullResObj, MenuItemFontFamilyType::FONT_FAMILY);
        MenuItemModelNG::CreateWithDimensionFpResourceObj(frameNode, nullResObj, MenuItemFontSizeType::FONT_SIZE);
    }
}

void SetSelectIcon(ArkUINodeHandle node, ArkUI_Bool showIcon)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetSelectIcon(frameNode, showIcon);
}

void ResetSelectIcon(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetSelectIcon(frameNode, false);
}

void SetSelectIconSrc(ArkUINodeHandle node, const char* iconSrc)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string iconPathStr;
    if (iconSrc != nullptr) {
        iconPathStr = iconSrc;
    }
    MenuItemModelNG::SetSelectIconSrc(frameNode, iconPathStr);
}

void SetSelectIconSrcWithResource(ArkUINodeHandle node, const char* iconSrc, void* iconRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SetSelectIconSrc(node, iconSrc);
    if (SystemProperties::ConfigChangePerform() && iconRawPtr) {
        auto* icon = reinterpret_cast<ResourceObject*>(iconRawPtr);
        auto iconResObj = AceType::Claim(icon);
        MenuItemModelNG::CreateWithStringResourceObj(frameNode, iconResObj, MenuItemStringType::SELECT_ICON);
    }
}

void ResetSelectIconSrc(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string iconPathStr;
    MenuItemModelNG::SetSelectIconSrc(frameNode, iconPathStr);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> nullResObj = nullptr;
        MenuItemModelNG::CreateWithStringResourceObj(frameNode, nullResObj, MenuItemStringType::SELECT_ICON);
    }
}

void SetSelectIconSymbol(ArkUINodeHandle node, void* symbolFunction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (symbolFunction) {
        auto symbolCallback = reinterpret_cast<std::function<void(WeakPtr<NG::FrameNode>)>*>(symbolFunction);
        MenuItemModelNG::SetSelectIconSymbol(frameNode, std::move(*symbolCallback));
    } else {
        MenuItemModelNG::SetSelectIconSymbol(frameNode, nullptr);
    }
}

void ResetSelectIconSymbol(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string iconPathStr;
    MenuItemModelNG::SetSelectIconSymbol(frameNode, nullptr);
}

void SetMenuItemOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        MenuItemModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        MenuItemModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetMenuItemOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string iconPathStr;
    MenuItemModelNG::SetOnChange(frameNode, nullptr);
}

namespace NodeModifier {
const ArkUIMenuItemModifier* GetMenuItemModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIMenuItemModifier modifier = {
        .setMenuItemSelected = SetMenuItemSelected,
        .resetMenuItemSelected = ResetMenuItemSelected,
        .setLabelFontColor = SetLabelFontColorWithResource,
        .resetLabelFontColor = ResetLabelFontColor,
        .setContentFontColor = SetContentFontColorWithResource,
        .resetContentFontColor = ResetContentFontColor,
        .setLabelFont = SetLabelFontWithResource,
        .resetLabelFont = ResetLabelFont,
        .setContentFont = SetContentFontWithResource,
        .resetContentFont = ResetContentFont,
        .setSelectIcon = SetSelectIcon,
        .resetSelectIcon = ResetSelectIcon,
        .setSelectIconSrc = SetSelectIconSrcWithResource,
        .resetSelectIconSrc = ResetSelectIconSrc,
        .setSelectIconSymbol = SetSelectIconSymbol,
        .resetSelectIconSymbol = ResetSelectIconSymbol,
        .setOnChange = SetMenuItemOnChange,
        .resetOnChange = ResetMenuItemOnChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIMenuItemModifier* GetCJUIMenuItemModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIMenuItemModifier modifier = {
        .setMenuItemSelected = SetMenuItemSelected,
        .resetMenuItemSelected = ResetMenuItemSelected,
        .setLabelFontColor = SetLabelFontColor,
        .resetLabelFontColor = ResetLabelFontColor,
        .setContentFontColor = SetContentFontColor,
        .resetContentFontColor = ResetContentFontColor,
        .setLabelFont = SetLabelFont,
        .resetLabelFont = ResetLabelFont,
        .setContentFont = SetContentFont,
        .resetContentFont = ResetContentFont,
        .setSelectIcon = SetSelectIcon,
        .resetSelectIcon = ResetSelectIcon,
        .setSelectIconSrc = SetSelectIconSrc,
        .resetSelectIconSrc = ResetSelectIconSrc,
        .setSelectIconSymbol = SetSelectIconSymbol,
        .resetSelectIconSymbol = ResetSelectIconSymbol,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
