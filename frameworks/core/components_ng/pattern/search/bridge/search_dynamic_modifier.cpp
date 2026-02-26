/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "ui/base/geometry/calc_dimension.h"
#include "ui/properties/color.h"

#include "base/utils/utf_helper.h"
#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/common/layout/common_text_constants.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components/search/search_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/search/bridge/search_custom_modifier.h"
#include "core/components_ng/pattern/search/search_model.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_model_static.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/node/search_modifier.h"

namespace OHOS::Ace {
const std::vector<TextDirection> TEXT_DIRECTIONS = { TextDirection::LTR, TextDirection::RTL, TextDirection::INHERIT,
    TextDirection::AUTO };
}

namespace OHOS::Ace::NG {
namespace {

constexpr Dimension DEFAULT_FONT_SIZE = 16.0_fp;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const bool DEFAULT_SELECTION_MENU_HIDDEN = false;
constexpr CancelButtonStyle DEFAULT_CANCEL_BUTTON_STYLE = CancelButtonStyle::INPUT;
constexpr Dimension THEME_SEARCH_FONT_SIZE = Dimension(16.0, DimensionUnit::FP);
constexpr TextDecoration DEFAULT_TEXT_DECORATION = TextDecoration::NONE;
constexpr Color DEFAULT_DECORATION_COLOR = Color(0xff000000);
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr int16_t DEFAULT_ALPHA = 255;
constexpr double DEFAULT_OPACITY = 0.2;
constexpr float DEFAULT_MIN_FONT_SCALE = 0.0f;
constexpr float DEFAULT_MAX_FONT_SCALE = static_cast<float>(INT32_MAX);
constexpr bool DEFAULT_ENABLE_PREVIEW_TEXT_VALUE = true;
constexpr int32_t DEFAULT_CARET_POSITION = 0;
constexpr bool DEFAULT_ENABLE_HAPTIC_FEEDBACK_VALUE = true;
constexpr bool DEFAULT_LEADING_PUNCTUATION = false;
const int32_t ERROR_INT_CODE = -1;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

SearchModel* GetInstance()
{
#ifdef NG_BUILD
    static NG::SearchModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::SearchModelNG instance;
        return &instance;
    } else {
        static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("search");
        static SearchModel* instance = loader ? reinterpret_cast<SearchModel*>(loader->CreateModel()) : nullptr;
        return instance;
    }
#endif
}

#ifndef CROSS_PLATFORM
SearchModel* GetSearchModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("search");
    static SearchModel* instance = loader ? reinterpret_cast<SearchModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
#endif

void FillColorValueAndPlaceholder(Color& result, ArkUI_Int32 colorValue, ArkUI_Int32 colorPlaceholder)
{
    result.SetValue(colorValue);
    if (colorPlaceholder > static_cast<ArkUI_Int32>(ColorPlaceholder::NONE) &&
        colorPlaceholder <= static_cast<ArkUI_Int32>(ColorPlaceholder::MAX)) {
        // no need to set ColorPlaceholder::NONE
        result.SetPlaceholder(static_cast<ColorPlaceholder>(colorPlaceholder));
    }
}

void SetSearchTextFont(ArkUINodeHandle node, const struct ArkUIFontStruct* value, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = Dimension(value->fontSizeNumber, static_cast<DimensionUnit>(value->fontSizeUnit));
    font.fontWeight = static_cast<FontWeight>(value->fontWeight);
    font.fontFamilies.assign(value->fontFamilies, value->fontFamilies + value->familyLength);
    font.fontStyle = static_cast<OHOS::Ace::FontStyle>(value->fontStyle);

    SearchModelNG::SetTextFont(frameNode, font);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<CalcDimension>(
            "fontSize", resObj, Dimension(value->fontSizeNumber, static_cast<DimensionUnit>(value->fontSizeUnit)));
    } else {
        pattern->UnRegisterResource("fontSize");
    }
}

void ResetSearchTextFont(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = DEFAULT_FONT_SIZE;
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    SearchModelNG::SetTextFont(frameNode, font);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("fontSize");
    }
}

void SetSearchPlaceholderColor(ArkUINodeHandle node, const ArkUI_InnerColor* color, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    const auto* colorPtr = reinterpret_cast<const Color*>(color);
    CHECK_NULL_VOID(colorPtr);
    SearchModelNG::SetPlaceholderColor(frameNode, *colorPtr);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<Color>("placeholderColor", resObj, *colorPtr, true);
    } else {
        pattern->UnRegisterResource("placeholderColor");
    }
}

void ResetSearchPlaceholderColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::ResetPlaceholderColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("placeholderColor");
    }
}

void SetSearchSelectionMenuHidden(ArkUINodeHandle node, ArkUI_Uint32 selectionMenuHidden)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSelectionMenuHidden(frameNode, static_cast<bool>(selectionMenuHidden));
}

void ResetSearchSelectionMenuHidden(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSelectionMenuHidden(frameNode, DEFAULT_SELECTION_MENU_HIDDEN);
}

void SetSearchCaretStyle(ArkUINodeHandle node, const ArkUI_Float32 number, ArkUI_Int32 unit,
    const ArkUI_InnerColor* caretColor, void* widthRawPtr, void* colorRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    const auto* caretColorPtr = reinterpret_cast<const Color*>(caretColor);
    SearchModelNG::SetCaretWidth(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    SearchModelNG::SetCaretColor(frameNode, *caretColorPtr);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && widthRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(widthRawPtr));
        pattern->RegisterResource<CalcDimension>(
            "caretWidth", resObj, Dimension(number, static_cast<DimensionUnit>(unit)));
    } else {
        pattern->UnRegisterResource("caretWidth");
    }
    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        pattern->RegisterResource<Color>("caretColor", resObj, *caretColorPtr, true);
    } else {
        pattern->UnRegisterResource("caretColor");
    }
}

void ResetSearchCaretStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto textFieldTheme = GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    CalcDimension caretWidth = textFieldTheme->GetCursorWidth();
    SearchModelNG::SetCaretWidth(frameNode, Dimension(caretWidth.Value(), caretWidth.Unit()));
    SearchModelNG::ResetCaretColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("caretWidth");
        pattern->UnRegisterResource("caretColor");
    }
}

void SetSearchTextAlign(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextAlign value_textAlign = static_cast<TextAlign>(value);
    SearchModelNG::SetTextAlign(frameNode, value_textAlign);
}

void ResetSearchTextAlign(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextAlign(frameNode, TextAlign::START);
}

void SetSearchDirection(ArkUINodeHandle node, ArkUI_Uint32 textDirection)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (textDirection < 0 || textDirection >= TEXT_DIRECTIONS.size()) {
        SearchModelNG::ResetTextDirection(frameNode);
        return;
    }
    SearchModelNG::SetTextDirection(frameNode, TEXT_DIRECTIONS[textDirection]);
}

int32_t GetSearchDirection(ArkUINodeHandle node)
{
    auto defaultTextDirection = static_cast<int32_t>(OHOS::Ace::TextDirection::INHERIT);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, defaultTextDirection);
    return static_cast<int32_t>(SearchModelNG::GetTextDirection(frameNode));
}

void ResetSearchDirection(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::ResetTextDirection(frameNode);
}

void RegisterSearchCancelButtonResources(const RefPtr<Pattern>& pattern, const struct ArkUIIconOptionsStruct* value,
    ArkUIImageIconRes* imageIconRes, const Color& iconColor)
{
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->sizeObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->sizeObj));
        pattern->RegisterResource<CalcDimension>(
            "cancelButtonIconSize", resObj, Dimension(value->value, static_cast<DimensionUnit>(value->unit)));
    } else {
        pattern->UnRegisterResource("cancelButtonIconSize");
    }
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->colorObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->colorObj));
        pattern->RegisterResource<Color>("cancelButtonIconColor", resObj, iconColor, true);
    } else {
        pattern->UnRegisterResource("cancelButtonIconColor");
    }
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->srcObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->srcObj));
        pattern->RegisterResource<std::string>("cancelButtonIconSrc", resObj, std::string(value->src));
    } else {
        pattern->UnRegisterResource("cancelButtonIconSrc");
    }
}

void SetJsSearchCancelButton(ArkUI_Int32 style, const struct ArkUIIconOptionsStruct* value,
    ArkUIImageIconRes* imageIconRes, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCancelButtonStyle(frameNode, static_cast<CancelButtonStyle>(style));
    CHECK_NULL_VOID(value);
    Color iconColor;
    NG::IconOptions cancelIconOptions;
    std::string bundleNameStr(bundleName);
    std::string moduleNameStr(moduleName);
    if (value->color != INVALID_COLOR_VALUE) {
        FillColorValueAndPlaceholder(iconColor, value->color, value->colorPlaceholder);
        cancelIconOptions =
            NG::IconOptions(iconColor, Dimension(value->value, static_cast<DimensionUnit>(value->unit)),
                std::string(value->src), bundleNameStr, moduleNameStr);
    } else {
        cancelIconOptions = NG::IconOptions(Dimension(value->value, static_cast<DimensionUnit>(value->unit)),
            std::string(value->src), bundleNameStr, moduleNameStr);
    }
    SearchModelNG::SetCancelImageIcon(frameNode, cancelIconOptions);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    RegisterSearchCancelButtonResources(pattern, value, imageIconRes, iconColor);
}

void SetJsSearchDefaultCancelButton(ArkUI_Int32 style)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCancelButtonStyle(frameNode, static_cast<CancelButtonStyle>(style));
    SearchModelNG::SetCancelDefaultIcon(frameNode);
}

void SetSearchCancelButton(ArkUINodeHandle node, ArkUI_Int32 style, const struct ArkUISizeType* size,
    const ArkUI_InnerColor* color, ArkUI_CharPtr src, ArkUIImageIconRes* imageIconRes)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCancelButtonStyle(frameNode, static_cast<CancelButtonStyle>(style));
    const auto* colorPtr = reinterpret_cast<const Color*>(color);
    NG::IconOptions cancelIconOptions = NG::IconOptions(
        *colorPtr, Dimension(size->value, static_cast<DimensionUnit>(size->unit)), std::string(src), "", "");
    SearchModelNG::SetCancelImageIcon(frameNode, cancelIconOptions);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    struct ArkUIIconOptionsStruct value = { size->value, size->unit, static_cast<ArkUI_Int32>(colorPtr->GetValue()),
        static_cast<ArkUI_Int32>(colorPtr->GetPlaceholder()), src };
    RegisterSearchCancelButtonResources(pattern, &value, imageIconRes, *colorPtr);
}

void ResetSearchCancelButton(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCancelButtonStyle(frameNode, DEFAULT_CANCEL_BUTTON_STYLE);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("cancelButtonIconSize");
        pattern->UnRegisterResource("cancelButtonIconColor");
        pattern->UnRegisterResource("cancelButtonIconSrc");
    }
}

void SetSearchEnableKeyboardOnFocus(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::RequestKeyboardOnFocus(frameNode, static_cast<bool>(value));
}

void ResetSearchEnableKeyboardOnFocus(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::RequestKeyboardOnFocus(frameNode, true);
}

void SetSearchPlaceholderFont(ArkUINodeHandle node, const struct ArkUIFontStruct* value, void* resRawPtr, bool isJsView)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = Dimension(value->fontSizeNumber, static_cast<DimensionUnit>(value->fontSizeUnit));
    font.fontWeight = static_cast<FontWeight>(value->fontWeight);
    font.fontFamilies.assign(value->fontFamilies, value->fontFamilies + value->familyLength);
    if (isJsView) {
        if (value->fontStyle != INVALID_FONT_STYLE) {
            font.fontStyle = static_cast<OHOS::Ace::FontStyle>(value->fontStyle);
        }
    } else {
        font.fontStyle = static_cast<OHOS::Ace::FontStyle>(value->fontStyle);
    }
    SearchModelNG::SetPlaceholderFont(frameNode, font);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<CalcDimension>("placeholderFontSize", resObj,
            Dimension(value->fontSizeNumber, static_cast<DimensionUnit>(value->fontSizeUnit)));
    } else {
        pattern->UnRegisterResource("placeholderFontSize");
    }
}

void ResetSearchPlaceholderFont(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = THEME_SEARCH_FONT_SIZE;
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    SearchModelNG::SetPlaceholderFont(frameNode, font);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("placeholderFontSize");
    }
}

void RegisterSearchIconResources(const RefPtr<Pattern>& pattern, const struct ArkUIIconOptionsStruct* value,
    ArkUIImageIconRes* imageIconRes, const Color& iconColor, bool isJsView)
{
    CHECK_NULL_VOID(pattern);
    std::string resourceName = isJsView ? "searchButtonIconSrc" : "searchIconSrc";
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->sizeObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->sizeObj));
        pattern->RegisterResource<CalcDimension>(
            "searchIconSize", resObj, Dimension(value->value, static_cast<DimensionUnit>(value->unit)));
    } else {
        pattern->UnRegisterResource("searchIconSize");
    }
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->colorObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->colorObj));
        pattern->RegisterResource<Color>("searchIconColor", resObj, iconColor, true);
    } else {
        pattern->UnRegisterResource("searchIconColor");
    }
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->srcObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->srcObj));
        pattern->RegisterResource<std::string>(resourceName, resObj, std::string(value->src));
    } else {
        pattern->UnRegisterResource(resourceName);
    }
}

void SetSearchSearchIcon(
    ArkUINodeHandle node, const struct ArkUIIconOptionsStruct* value, ArkUIImageIconRes* imageIconRes)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color iconColor;
    if (value->color != INVALID_COLOR_VALUE) {
        FillColorValueAndPlaceholder(iconColor, value->color, value->colorPlaceholder);
    }

    NG::IconOptions cancelInconOptions = NG::IconOptions(
        iconColor, Dimension(value->value, static_cast<DimensionUnit>(value->unit)), std::string(value->src), "", "");
    SearchModelNG::SetSearchImageIcon(frameNode, cancelInconOptions);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    RegisterSearchIconResources(pattern, value, imageIconRes, iconColor, false);
}

void SetJsSearchSearchIcon(ArkUINodeHandle node, const struct ArkUIIconOptionsStruct* value,
    ArkUIImageIconRes* imageIconRes, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("searchIconSize");
        pattern->UnRegisterResource("searchButtonIconSrc");
        pattern->UnRegisterResource("searchIconColor");
    }
    CHECK_NULL_VOID(value);
    Color iconColor;
    NG::IconOptions searchIconOptions;
    std::string bundleNameStr(bundleName);
    std::string moduleNameStr(moduleName);
    if (value->color != INVALID_COLOR_VALUE) {
        FillColorValueAndPlaceholder(iconColor, value->color, value->colorPlaceholder);
        searchIconOptions =
            NG::IconOptions(iconColor, Dimension(value->value, static_cast<DimensionUnit>(value->unit)),
                std::string(value->src), bundleNameStr, moduleNameStr);
    } else {
        searchIconOptions = NG::IconOptions(Dimension(value->value, static_cast<DimensionUnit>(value->unit)),
            std::string(value->src), bundleNameStr, moduleNameStr);
    }

    SearchModelNG::SetSearchImageIcon(frameNode, searchIconOptions);
    RegisterSearchIconResources(pattern, value, imageIconRes, iconColor, true);
}

void SetSearchDefaultIcon(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("searchIconSize");
        pattern->UnRegisterResource("searchButtonIconSrc");
        pattern->UnRegisterResource("searchIconColor");
    }
    SearchModelNG::SetSearchDefaultIcon(frameNode);
}

void ResetSearchSearchIcon(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchSrcPath(frameNode, "");
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("searchIconSize");
        pattern->UnRegisterResource("searchIconColor");
        pattern->UnRegisterResource("searchIconSrc");
    }
}

void ParseSearchButtonRegisterResource(FrameNode* frameNode, const struct ArkUISearchButtonOptionsStruct* value,
    ArkUIImageIconRes* imageIconRes)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("searchButtonFontSize");
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->sizeObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->sizeObj));
        pattern->RegisterResource<CalcDimension>("searchButtonFontSize", resObj,
        CalcDimension(value->sizeValue, static_cast<DimensionUnit>(value->sizeUnit)));
    }
    pattern->UnRegisterResource("searchButtonFontColor");
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->colorObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->colorObj));
        pattern->RegisterResource<Color>("searchButtonFontColor", resObj, Color(value->fontColor));
    }
    pattern->UnRegisterResource("searchButtonValue");
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->srcObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->srcObj));
        pattern->RegisterResource<std::string>("searchButtonValue", resObj, value->value);
    }
}

void SetSearchSearchButton(ArkUINodeHandle node, const struct ArkUISearchButtonOptionsStruct* value,
    ArkUIImageIconRes* imageIconRes, bool isThemeColor, bool isJsView)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchButton(frameNode, value->value, isJsView);
    SearchModelNG::SetSearchButtonFontSize(
        frameNode, CalcDimension(value->sizeValue, static_cast<DimensionUnit>(value->sizeUnit)));
    SearchModelNG::SetSearchButtonFontColor(frameNode, Color(value->fontColor), isThemeColor);
    SearchModelNG::SetSearchButtonAutoDisable(frameNode, value->autoDisable);
    if (isJsView) {
        ParseSearchButtonRegisterResource(frameNode, value, imageIconRes);
        return;
    }
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->sizeObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->sizeObj));
        pattern->RegisterResource<CalcDimension>("searchButtonFontSize", resObj,
            CalcDimension(value->sizeValue, static_cast<DimensionUnit>(value->sizeUnit)));
    } else {
        pattern->UnRegisterResource("searchButtonFontSize");
    }
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->colorObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->colorObj));
        pattern->RegisterResource<Color>("searchButtonFontColor", resObj, Color(value->fontColor));
    } else {
        pattern->UnRegisterResource("searchButtonFontColor");
    }
    if (SystemProperties::ConfigChangePerform() && imageIconRes && imageIconRes->srcObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(imageIconRes->srcObj));
        pattern->RegisterResource<std::string>("searchButtonValue", resObj, value->value);
    } else {
        pattern->UnRegisterResource("searchButtonValue");
    }
}

void ResetSearchSearchButton(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchButton(frameNode, "");
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("searchButtonFontSize");
        pattern->UnRegisterResource("searchButtonFontColor");
        pattern->UnRegisterResource("searchButtonValue");
    }
}

void SetSearchFontColor(ArkUINodeHandle node, const ArkUI_InnerColor* value, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    const auto* colorPtr = reinterpret_cast<const Color*>(value);
    CHECK_NULL_VOID(colorPtr);
    SearchModelNG::SetTextColor(frameNode, *colorPtr);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<Color>("fontColor", resObj, *colorPtr, true);
    } else {
        pattern->UnRegisterResource("fontColor");
    }
}

void ResetSearchFontColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::ResetTextColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("fontColor");
    }
}

void SetSearchCopyOption(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto copyOptions = CopyOptions::Local;
    copyOptions = static_cast<CopyOptions>(value);
    SearchModelNG::SetCopyOption(frameNode, copyOptions);
}

void ResetSearchCopyOption(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto copyOptions = CopyOptions::Local;
    SearchModelNG::SetCopyOption(frameNode, copyOptions);
}

void SetSearchEnterKeyType(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchEnterKeyType(frameNode, CastToTextInputAction(value));
}

void ResetSearchEnterKeyType(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchEnterKeyType(frameNode, TextInputAction::SEARCH);
}

void SetSearchHeight(ArkUINodeHandle node, ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetHeight(frameNode, CalcDimension(heightValue, (DimensionUnit)heightUnit));
}

void ResetSearchHeight(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}

void SetSearchFontFeature(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string strValue = value;
    SearchModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void ResetSearchFontFeature(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string strValue = "";
    SearchModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void SetSearchInspectorId(ArkUINodeHandle node, ArkUI_CharPtr key)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetId(frameNode, key);
}

void ResetSearchInspectorId(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetId(frameNode, "");
}

void SetSearchDividerColor(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Uint32 colorSpace, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(color, static_cast<ColorSpace>(colorSpace));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (!resRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(
                resObj, result, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        }
        if (resObj) {
            pattern->RegisterResource<Color>("dividerColor", resObj, result);
        } else {
            pattern->UnRegisterResource("dividerColor");
        }
    }
    SearchModelNG::SetDividerColor(frameNode, result);
}

void ResetSearchDividerColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::ResetDividerColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("dividerColor");
    }
}

void SetSearchDecoration(
    ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Int32 style, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextDecoration(frameNode, static_cast<TextDecoration>(decoration));
    SearchModelNG::SetTextDecorationColor(frameNode, Color(color));
    SearchModelNG::SetTextDecorationStyle(frameNode, static_cast<TextDecorationStyle>(style));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<Color>("decorationColor", resObj, Color(color));
    } else {
        pattern->UnRegisterResource("decorationColor");
    }
}

void ResetSearchDecoration(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextDecoration(frameNode, DEFAULT_TEXT_DECORATION);
    SearchModelNG::SetTextDecorationColor(frameNode, DEFAULT_DECORATION_COLOR);
    SearchModelNG::SetTextDecorationStyle(frameNode, DEFAULT_DECORATION_STYLE);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("decorationColor");
    }
}

void SetSearchLetterSpacing(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetLetterSpacing(frameNode, CalcDimension(value, (DimensionUnit)unit));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<CalcDimension>("letterSpacing", resObj, CalcDimension(value, (DimensionUnit)unit));
    } else {
        pattern->UnRegisterResource("letterSpacing");
    }
}

void ResetSearchLetterSpacing(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value;
    value.Reset();
    SearchModelNG::SetLetterSpacing(frameNode, value);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("letterSpacing");
    }
}
void SetSearchLineHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetLineHeight(frameNode, CalcDimension(value, (DimensionUnit)unit));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<CalcDimension>("lineHeight", resObj, CalcDimension(value, (DimensionUnit)unit));
    } else {
        pattern->UnRegisterResource("lineHeight");
    }
}
void ResetSearchLineHeight(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value;
    value.Reset();
    SearchModelNG::SetLineHeight(frameNode, value);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("lineHeight");
    }
}

void SetSearchHalfLeading(ArkUINodeHandle node, ArkUI_Uint32 halfLeading)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetHalfLeading(frameNode, static_cast<bool>(halfLeading));
}

void ResetSearchHalfLeading(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    bool value = false;
    SearchModelNG::SetHalfLeading(frameNode, value);
}

void SetSearchAdaptMinFontSize(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetAdaptMinFontSize(frameNode, CalcDimension(value, (DimensionUnit)unit));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<CalcDimension>("minFontSize", resObj, CalcDimension(value, (DimensionUnit)unit));
    } else {
        pattern->UnRegisterResource("minFontSize");
    }
}

void ResetSearchAdaptMinFontSize(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension minFontSize = theme->GetTextStyle().GetAdaptMinFontSize();
    SearchModelNG::SetAdaptMinFontSize(frameNode, minFontSize);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("minFontSize");
    }
}

void SetSearchAdaptMaxFontSize(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetAdaptMaxFontSize(frameNode, CalcDimension(value, (DimensionUnit)unit));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<CalcDimension>("maxFontSize", resObj, CalcDimension(value, (DimensionUnit)unit));
    } else {
        pattern->UnRegisterResource("maxFontSize");
    }
}

void ResetSearchAdaptMaxFontSize(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
    SearchModelNG::SetAdaptMaxFontSize(frameNode, maxFontSize);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("maxFontSize");
    }
}

void SetSearchSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color selectedColor = Color(color);
    if (selectedColor.GetAlpha() == DEFAULT_ALPHA) {
        // Default setting of 20% opacity
        selectedColor = selectedColor.ChangeOpacity(DEFAULT_OPACITY);
    }
    SearchModelNG::SetSelectedBackgroundColor(frameNode, selectedColor);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<Color>("selectedBackgroundColor", resObj, selectedColor);
    } else {
        pattern->UnRegisterResource("selectedBackgroundColor");
    }
}

void ResetSearchSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::ResetSelectedBackgroundColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("selectedBackgroundColor");
    }
}

void SetSelectDetectorEnable(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSelectDetectEnable(frameNode, static_cast<bool>(value));
}

ArkUI_Int32 GetSelectDetectorEnable(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SearchModelNG::GetSelectDetectEnable(frameNode));
}

void ResetSelectDetectorEnable(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::ResetSelectDetectEnable(frameNode);
}

void SetSearchTextIndent(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextIndent(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<CalcDimension>(
            "textIndent", resObj, Dimension(number, static_cast<DimensionUnit>(unit)));
    } else {
        pattern->UnRegisterResource("textIndent");
    }
}

void ResetSearchTextIndent(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextIndent(frameNode, CalcDimension(0, DimensionUnit::VP));
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("textIndent");
    }
}

void SetSearchMaxLength(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetMaxLength(frameNode, value);
}

void ResetSearchMaxLength(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::ResetMaxLength(frameNode);
}

void SetSearchType(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetType(frameNode, CastToTextInputType(value));
}

void ResetSearchType(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetType(frameNode, Ace::TextInputType::TEXT);
}

void SetSearchOnEditChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEditChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        SearchModelNG::SetOnEditChange(frameNode, std::move(*onEditChange));
    } else {
        SearchModelNG::SetOnEditChange(frameNode, nullptr);
    }
}

void ResetSearchOnEditChange(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnEditChange(frameNode, nullptr);
}

void SetSearchOnSubmitWithEvent(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSubmit =
            reinterpret_cast<std::function<void(const std::u16string&, NG::TextFieldCommonEvent&)>*>(callback);
        SearchModelNG::SetOnSubmit(frameNode, std::move(*onSubmit));
    } else {
        SearchModelNG::SetOnSubmit(frameNode, nullptr);
    }
}

void ResetSearchOnSubmitWithEvent(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnSubmit(frameNode, nullptr);
}

void SetSearchOnCopy(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCopy = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
        SearchModelNG::SetOnCopy(frameNode, std::move(*onCopy));
    } else {
        SearchModelNG::SetOnCopy(frameNode, nullptr);
    }
}

void ResetSearchOnCopy(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnCopy(frameNode, nullptr);
}

void SetSearchOnCut(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCut = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
        SearchModelNG::SetOnCut(frameNode, std::move(*onCut));
    } else {
        SearchModelNG::SetOnCut(frameNode, nullptr);
    }
}

void ResetSearchOnCut(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnCut(frameNode, nullptr);
}

void SetSearchOnPaste(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onPasteWithEvent =
            reinterpret_cast<std::function<void(const std::u16string&, NG::TextCommonEvent&)>*>(callback);
        SearchModelNG::SetOnPasteWithEvent(frameNode, std::move(*onPasteWithEvent));
    } else {
        SearchModelNG::SetOnPasteWithEvent(frameNode, nullptr);
    }
}

void ResetSearchOnPaste(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnPasteWithEvent(frameNode, nullptr);
}

void SetSearchOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSubmit = reinterpret_cast<std::function<void(const ChangeValueInfo&)>*>(callback);
        SearchModelNG::SetOnChange(frameNode, std::move(*onSubmit));
    } else {
        SearchModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetSearchOnChange(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnChange(frameNode, nullptr);
}

void SetSearchOnTextSelectionChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(int32_t, int32_t)>*>(callback);
        SearchModelNG::SetOnTextSelectionChange(frameNode, std::move(*onChange));
    } else {
        SearchModelNG::SetOnTextSelectionChange(frameNode, nullptr);
    }
}

void ResetSearchOnTextSelectionChange(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnTextSelectionChange(frameNode, nullptr);
}

void SetSearchOnContentScroll(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onScroll = reinterpret_cast<std::function<void(float, float)>*>(callback);
        SearchModelNG::SetOnContentScroll(frameNode, std::move(*onScroll));
    } else {
        SearchModelNG::SetOnContentScroll(frameNode, nullptr);
    }
}

void ResetSearchOnContentScroll(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnContentScroll(frameNode, nullptr);
}

void SetSearchShowCounterOptions(
    ArkUINodeHandle node, ArkUI_Bool open, ArkUI_Int32 thresholdPercentage, ArkUI_Bool highlightBorder)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetShowCounter(frameNode, open);
    SearchModelNG::SetCounterType(frameNode, thresholdPercentage);
    SearchModelNG::SetShowCounterBorder(frameNode, highlightBorder);
}

void ResetSearchShowCounterOptions(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetShowCounter(frameNode, false);
    SearchModelNG::SetCounterType(frameNode, -1);
    SearchModelNG::SetShowCounterBorder(frameNode, true);
}

ArkUINodeHandle GetSearchController(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = SearchModelNG::GetSearchController(frameNode);
    CHECK_NULL_RETURN(controller, nullptr);
    auto nodecontroller = reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(controller));
    return nodecontroller;
}

void SetSearchValue(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> valueNG = value;
    SearchModelNG::SetTextValue(frameNode, valueNG);
}

void ResetSearchValue(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextValue(frameNode, "");
}

void SetSearchPlaceholder(ArkUINodeHandle node, ArkUI_CharPtr placeholder)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> placeholderNG = placeholder;

    SearchModelNG::SetPlaceholder(frameNode, placeholderNG);
}

void ResetSearchPlaceholder(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetPlaceholder(frameNode, "");
}

void SetSearchIcon(ArkUINodeHandle node, ArkUI_CharPtr icon)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> iconNG = icon;

    SearchModelNG::SetIcon(frameNode, iconNG);
}

void ResetSearchIcon(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetIcon(frameNode, "");
}

void SetSearchOnWillChange(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillChange = reinterpret_cast<std::function<bool(const ChangeValueInfo&)>*>(callback);
        SearchModelNG::SetOnWillChangeEvent(frameNode, std::move(*onWillChange));
    } else {
        SearchModelNG::SetOnWillChangeEvent(frameNode, nullptr);
    }
}

void ResetSearchOnWillChange(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnWillChangeEvent(frameNode, nullptr);
}

void SetSearchOnWillInsert(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillInsert = reinterpret_cast<std::function<bool(const InsertValueInfo&)>*>(callback);
        SearchModelNG::SetOnWillInsertValueEvent(frameNode, std::move(*onWillInsert));
    } else {
        SearchModelNG::SetOnWillInsertValueEvent(frameNode, nullptr);
    }
}

void ResetSearchOnWillInsert(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnWillInsertValueEvent(frameNode, nullptr);
}

void SetSearchOnDidInsert(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDidInsert = reinterpret_cast<std::function<void(const InsertValueInfo&)>*>(callback);
        SearchModelNG::SetOnDidInsertValueEvent(frameNode, std::move(*onDidInsert));
    } else {
        SearchModelNG::SetOnDidInsertValueEvent(frameNode, nullptr);
    }
}

void ResetSearchOnDidInsert(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnDidInsertValueEvent(frameNode, nullptr);
}

void SetSearchOnWillDelete(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillDelete = reinterpret_cast<std::function<bool(const DeleteValueInfo&)>*>(callback);
        SearchModelNG::SetOnWillDeleteEvent(frameNode, std::move(*onWillDelete));
    } else {
        SearchModelNG::SetOnWillDeleteEvent(frameNode, nullptr);
    }
}

void ResetSearchOnWillDelete(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnWillDeleteEvent(frameNode, nullptr);
}

void SetSearchOnDidDelete(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDidDelete = reinterpret_cast<std::function<void(const DeleteValueInfo&)>*>(callback);
        SearchModelNG::SetOnDidDeleteEvent(frameNode, std::move(*onDidDelete));
    } else {
        SearchModelNG::SetOnDidDeleteEvent(frameNode, nullptr);
    }
}

void ResetSearchOnDidDelete(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnDidDeleteEvent(frameNode, nullptr);
}

void SetSearchEnablePreviewText(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnablePreviewText(frameNode, static_cast<bool>(value));
}

void ResetSearchEnablePreviewText(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnablePreviewText(frameNode, DEFAULT_ENABLE_PREVIEW_TEXT_VALUE);
}

void SetSearchCaretPosition(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);

    SearchModelNG::SetCaretPosition(frameNode, value);
}

void ResetSearchCaretPosition(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);

    SearchModelNG::SetCaretPosition(frameNode, DEFAULT_CARET_POSITION);
}

void SetSearchSelectionMenuOptions(
    ArkUINodeHandle node, void* onCreateMenuCallback, void* onMenuItemClickCallback, void* onPrepareMenuCallback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (onCreateMenuCallback) {
        NG::OnCreateMenuCallback onCreateMenu = *(reinterpret_cast<NG::OnCreateMenuCallback*>(onCreateMenuCallback));
        SearchModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(onCreateMenu));
    } else {
        SearchModelNG::OnCreateMenuCallbackUpdate(frameNode, nullptr);
    }
    if (onMenuItemClickCallback) {
        NG::OnMenuItemClickCallback onMenuItemClick =
            *(reinterpret_cast<NG::OnMenuItemClickCallback*>(onMenuItemClickCallback));
        SearchModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(onMenuItemClick));
    } else {
        SearchModelNG::OnMenuItemClickCallbackUpdate(frameNode, nullptr);
    }
    if (onPrepareMenuCallback) {
        NG::OnPrepareMenuCallback onPrepareMenu =
            *(reinterpret_cast<NG::OnPrepareMenuCallback*>(onPrepareMenuCallback));
        SearchModelNG::OnPrepareMenuCallbackUpdate(frameNode, std::move(onPrepareMenu));
    } else {
        SearchModelNG::OnPrepareMenuCallbackUpdate(frameNode, nullptr);
    }
}

void ResetSearchSelectionMenuOptions(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    SearchModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(onCreateMenuCallback));
    SearchModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(onMenuItemClick));
    SearchModelNG::OnPrepareMenuCallbackUpdate(frameNode, std::move(onPrepareMenuCallback));
}

void SetSearchMinFontScale(ArkUINodeHandle node, ArkUI_Float32 number, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetMinFontScale(frameNode, number);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<float>("minFontScale", resObj, number);
    } else {
        pattern->UnRegisterResource("minFontScale");
    }
}

void ResetSearchMinFontScale(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetMinFontScale(frameNode, DEFAULT_MIN_FONT_SCALE);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("minFontScale");
    }
}

void SetSearchMaxFontScale(ArkUINodeHandle node, ArkUI_Float32 number, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetMaxFontScale(frameNode, number);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<float>("maxFontScale", resObj, number);
    } else {
        pattern->UnRegisterResource("maxFontScale");
    }
}

void ResetSearchMaxFontScale(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetMaxFontScale(frameNode, DEFAULT_MAX_FONT_SCALE);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("maxFontScale");
    }
}

void SetSearchEnableHapticFeedback(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnableHapticFeedback(frameNode, static_cast<bool>(value));
}

void ResetSearchEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnableHapticFeedback(frameNode, DEFAULT_ENABLE_HAPTIC_FEEDBACK_VALUE);
}

void SetSearchAutoCapitalizationMode(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetAutoCapitalizationMode(frameNode, CastToAutoCapitalizationMode(value));
}

void ResetSearchAutoCapitalizationMode(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetAutoCapitalizationMode(frameNode, AutoCapitalizationMode::NONE);
}

void SetStopBackPress(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetStopBackPress(frameNode, static_cast<bool>(value));
}

void ResetStopBackPress(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetStopBackPress(frameNode, true);
}

void SetSearchStrokeWidth(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetStrokeWidth(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetSearchStrokeWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetStrokeWidth(frameNode, 0.0_px);
}

void SetSearchStrokeColor(ArkUINodeHandle node, ArkUI_Uint32 value, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetStrokeColor(frameNode, Color(value));
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        if (resRawPtr) {
            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
            pattern->RegisterResource<Color>("strokeColor", resObj, Color(value));
        } else {
            pattern->UnRegisterResource("strokeColor");
        }
    }
}

void ResetSearchStrokeColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::ResetStrokeColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("strokeColor");
    }
}

void SetEnableAutoSpacing(ArkUINodeHandle node, ArkUI_Bool enableAutoSpacing)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnableAutoSpacing(frameNode, static_cast<bool>(enableAutoSpacing));
}

void ResetEnableAutoSpacing(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnableAutoSpacing(frameNode, false);
}

void SetSearchMargin(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetUserMargin(frameNode);
}

void ResetSearchMargin(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetUserMargin(frameNode);
}

void SetSearchCustomKeyboard(ArkUINodeHandle node, ArkUINodeHandle contentNode, ArkUI_Bool supportAvoidance)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCustomKeyboardWithNode(frameNode, reinterpret_cast<FrameNode*>(contentNode), supportAvoidance);
}

void ResetSearchCustomKeyboard(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCustomKeyboardWithNode(frameNode, nullptr);
}

void SetSearchOnWillAttachIME(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillAttachIMECallback = reinterpret_cast<IMEAttachCallback*>(callback);
        SearchModelNG::SetOnWillAttachIME(frameNode, std::move(*onWillAttachIMECallback));
    } else {
        SearchModelNG::SetOnWillAttachIME(frameNode, nullptr);
    }
}

void ResetSearchOnWillAttachIME(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnWillAttachIME(frameNode, nullptr);
}

void SetSearchCompressLeadingPunctuation(ArkUINodeHandle node, ArkUI_Bool enable)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCompressLeadingPunctuation(frameNode, enable);
}

ArkUI_Int32 GetSearchCompressLeadingPunctuation(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Int32>(SearchModelNG::GetCompressLeadingPunctuation(frameNode));
}

void ResetSearchCompressLeadingPunctuation(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCompressLeadingPunctuation(frameNode, DEFAULT_LEADING_PUNCTUATION);
}

void SetIncludeFontPadding(ArkUINodeHandle node, ArkUI_Bool includeFontPadding)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetIncludeFontPadding(frameNode, static_cast<bool>(includeFontPadding));
}

void ResetIncludeFontPadding(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetIncludeFontPadding(frameNode, false);
}

void SetFallbackLineSpacing(ArkUINodeHandle node, ArkUI_Bool includeFontPadding)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetFallbackLineSpacing(frameNode, static_cast<bool>(includeFontPadding));
}

void ResetFallbackLineSpacing(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetFallbackLineSpacing(frameNode, false);
}

void SetSearchSelectedDragPreviewStyle(ArkUINodeHandle node, ArkUI_Uint32 color, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(color);
    auto pattern = frameNode->GetPattern();
    SearchModelNG::SetSelectedDragPreviewStyle(frameNode, result);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<Color>("selectedDragPreviewStyleColor", resObj, result);
    } else {
        pattern->UnRegisterResource("selectedDragPreviewStyleColor");
    }
}

void ResetSearchSelectedDragPreviewStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::ResetSelectedDragPreviewStyle(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("selectedDragPreviewStyle");
    }
}

ArkUI_Uint32 GetSearchSelectedDragPreviewStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return SearchModelNG::GetSelectedDragPreviewStyle(frameNode).GetValue();
}

void SetSearchBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetBorderRadius(frameNode);
}

void SetOnSearchSubmitExtraParam(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const std::u16string& text, NG::TextFieldCommonEvent& commonEvent) {
        ArkUINodeEvent event;
        std::string utf8Text = UtfUtils::Str16DebugToStr8(text);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_SEARCH_SUBMIT;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Text.c_str());
        SendArkUISyncEvent(&event);
    };
    SearchModelNG::SetOnSubmit(frameNode, std::move(onEvent));
}

void SetOnSearchChangeExtraParam(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const ChangeValueInfo& info) {
        ArkUINodeEvent event;
        std::string utf8Text = UtfUtils::Str16DebugToStr8(info.value);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_SEARCH_CHANGE;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Text.c_str());
        SendArkUISyncEvent(&event);
    };
    SearchModelNG::SetOnChange(frameNode, std::move(onEvent));
}

void SetOnSearchCopyExtraParam(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const std::u16string& text) {
        ArkUINodeEvent event;
        std::string utf8Text = UtfUtils::Str16DebugToStr8(text);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_SEARCH_COPY;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Text.c_str());
        SendArkUISyncEvent(&event);
    };
    SearchModelNG::SetOnCopy(frameNode, std::move(onEvent));
}

void SetOnSearchCutExtraParam(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const std::u16string& text) {
        ArkUINodeEvent event;
        std::string utf8Text = UtfUtils::Str16DebugToStr8(text);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_SEARCH_CUT;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Text.c_str());
        SendArkUISyncEvent(&event);
    };
    SearchModelNG::SetOnCut(frameNode, std::move(onEvent));
}

void SetOnSearchPasteExtraParam(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const std::u16string& text, NG::TextCommonEvent& textEvent) {
        ArkUINodeEvent event;
        std::string utf8Text = UtfUtils::Str16DebugToStr8(text);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_SEARCH_PASTE;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Text.c_str());
        SendArkUISyncEvent(&event);
    };
    SearchModelNG::SetOnPasteWithEvent(frameNode, std::move(onEvent));
}

void SetSearchBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetBackgroundColor(frameNode, Color(color));
}

void RetSetSearchBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::ResetBackgroundColorStatic();
}

void SetSearchSymbolIcon(ArkUINodeHandle node, std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchSymbolIcon(frameNode, iconSymbol);
}

void SetSearchCancelSymbolIcon(
    ArkUINodeHandle node, std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol, ArkUI_Int32 style)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCancelButtonStyle(frameNode, static_cast<CancelButtonStyle>(style));
    SearchModelNG::SetCancelSymbolIcon(frameNode, iconSymbol);
}

void SetDragPreviewOptions(ArkUINodeHandle node, const NG::DragPreviewOption option)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetDragPreviewOptions(frameNode, option);
}

void SetSearchInputFilter(ArkUI_CharPtr value, void* callback, void* resRawPtr)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    std::string inputFilter(value);
    if (callback) {
        auto onError = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
        SearchModelNG::SetInputFilter(frameNode, inputFilter, std::move(*onError));
    } else {
        SearchModelNG::SetInputFilter(frameNode, inputFilter, nullptr);
    }
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<std::string>("inputFilter", resObj, inputFilter);
    } else {
        pattern->UnRegisterResource("inputFilter");
    }
}

void ResetSearchInputFilter()
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    std::string inputFilter;
    SearchModelNG::SetInputFilter(frameNode, inputFilter, nullptr);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("inputFilter");
    }
}

void SetSearchCustomKeyboardWithBuilder(void* builder, ArkUI_Bool supportAvoidance)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto builderFunc = reinterpret_cast<std::function<void()>*>(builder);
    SearchModelNG::SetCustomKeyboard(frameNode, std::move(*builderFunc), supportAvoidance);
}

void ResetSearchCustomKeyboardWithBuilder()
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCustomKeyboard(frameNode, nullptr);
}

void ResetSearchCaretColor(const ArkUI_Float32 number, ArkUI_Int32 unit, void* widthRawPtr)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCaretWidth(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    SearchModelNG::ResetCaretColor(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && widthRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(widthRawPtr));
        pattern->RegisterResource<CalcDimension>(
            "caretWidth", resObj, Dimension(number, static_cast<DimensionUnit>(unit)));
    } else {
        pattern->UnRegisterResource("caretWidth");
    }
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("caretColor");
    }
}

void SetBackBorder(ArkUINodeHandle node)
{
    return;
}

#ifndef CROSS_PLATFORM
void SetSearchPlaceholderColorImpl(ArkUINodeHandle node, const ArkUI_InnerColor* color, void* resRawPtr)
{
    const auto* colorPtr = reinterpret_cast<const Color*>(color);
    CHECK_NULL_VOID(colorPtr);
    GetSearchModelImpl()->SetPlaceholderColor(*colorPtr);
}

void SetSearchTextFontImpl(ArkUINodeHandle node, const struct ArkUIFontStruct* value, void* resRawPtr)
{
    Font font;
    font.fontSize = Dimension(value->fontSizeNumber, static_cast<DimensionUnit>(value->fontSizeUnit));
    font.fontWeight = static_cast<FontWeight>(value->fontWeight);
    font.fontFamilies.assign(value->fontFamilies, value->fontFamilies + value->familyLength);
    font.fontStyle = static_cast<OHOS::Ace::FontStyle>(value->fontStyle);
    GetSearchModelImpl()->SetTextFont(font);
}

void SetSearchTextAlignImpl(ArkUINodeHandle node, ArkUI_Int32 value)
{
    TextAlign value_textAlign = static_cast<TextAlign>(value);
    GetSearchModelImpl()->SetTextAlign(value_textAlign);
}

void SetSearchPlaceholderFontImpl(
    ArkUINodeHandle node, const struct ArkUIFontStruct* value, void* resRawPtr, bool isJsView)
{
    Font font;
    font.fontSize = Dimension(value->fontSizeNumber, static_cast<DimensionUnit>(value->fontSizeUnit));
    font.fontWeight = static_cast<FontWeight>(value->fontWeight);
    font.fontFamilies.assign(value->fontFamilies, value->fontFamilies + value->familyLength);
    font.fontStyle = static_cast<OHOS::Ace::FontStyle>(value->fontStyle);

    GetSearchModelImpl()->SetPlaceholderFont(font);
}

void SetSearchSearchButtonImpl(ArkUINodeHandle node, const struct ArkUISearchButtonOptionsStruct* value,
    ArkUIImageIconRes* imageIconRes, bool isThemeColor, bool isJsView)
{
    GetSearchModelImpl()->SetSearchButton(value->value);
}

void SetSearchCopyOptionImpl(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto copyOptions = CopyOptions::Local;
    copyOptions = static_cast<CopyOptions>(value);
    GetSearchModelImpl()->SetCopyOption(copyOptions);
}

void SetSearchHeightImpl(ArkUINodeHandle node, ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit)
{
    GetSearchModelImpl()->SetHeight(CalcDimension(heightValue, (DimensionUnit)heightUnit));
}

void SetSearchOnSubmitWithEventImpl(ArkUINodeHandle node, void* callback)
{
    auto onSubmit = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
    GetSearchModelImpl()->SetOnSubmit(std::move(*onSubmit));
}

void SetSearchOnCopyImpl(ArkUINodeHandle node, void* callback)
{
    auto onCopy = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
    GetSearchModelImpl()->SetOnCopy(std::move(*onCopy));
}

void SetSearchOnCutImpl(ArkUINodeHandle node, void* callback)
{
    auto onCut = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
    GetSearchModelImpl()->SetOnCut(std::move(*onCut));
}

void SetSearchOnPasteImpl(ArkUINodeHandle node, void* callback)
{
    auto onPasteWithEvent =
        reinterpret_cast<std::function<void(const std::u16string&, NG::TextCommonEvent&)>*>(callback);
    GetSearchModelImpl()->SetOnPasteWithEvent(std::move(*onPasteWithEvent));
}

void SetBackBorderImpl(ArkUINodeHandle node)
{
    GetSearchModelImpl()->SetBackBorder();
}
#endif

ArkUINodeHandle CreateSearchFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = SearchModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void SetKeyboardAppearanceConfig(FrameNode* frameNode, KeyboardAppearanceConfig config)
{
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetKeyboardAppearanceConfig(frameNode, config);
}

void SetTextValue(FrameNode* frameNode, const std::optional<std::string>& value)
{
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextValue(frameNode, value);
}

void SetOnChangeEvent(FrameNode* frameNode, std::function<void(const std::u16string&)>&& onChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetOnChangeEvent(frameNode, std::move(onChangeEvent));
}

void CreateNormalSearch(std::optional<std::u16string>& stringValue, std::optional<std::u16string>& placeholder,
    std::optional<std::string>& iconSrc, const ArkUISearchCreateResourceParams* resParams)
{
    static SearchModelNG model;
    model.Create(stringValue, placeholder, iconSrc);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        if (resParams && resParams->parseValueResult && resParams->stringValueRawPtr) {
            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resParams->stringValueRawPtr));
            pattern->RegisterResource<std::u16string>("text", resObj, stringValue.value());
        } else {
            pattern->UnRegisterResource("text");
        }
    }
    if (SystemProperties::ConfigChangePerform()) {
        if (resParams && resParams->parsePlaceholderResult && resParams->placeholderRawPtr) {
            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resParams->placeholderRawPtr));
            pattern->RegisterResource<std::u16string>("placeholder", resObj, placeholder.value());
        } else {
            pattern->UnRegisterResource("placeholder");
        }
    }
}

void SetSearchOnChangeEvent(void* callback)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto onChangeEvent = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
    SearchModelNG::SetOnChangeEvent(frameNode, std::move(*onChangeEvent));
}
} // namespace
namespace NodeModifier {
const ArkUISearchModifier* GetSearchDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUISearchModifier modifier = {
            .setSelectDetectorEnable = nullptr,
            .getSelectDetectorEnable = nullptr,
            .resetSelectDetectorEnable = nullptr,
            .setSearchPlaceholderColor = SetSearchPlaceholderColorImpl,
            .resetSearchPlaceholderColor = nullptr,
            .setSearchTextFont = SetSearchTextFontImpl,
            .resetSearchTextFont = nullptr,
            .setSearchSelectionMenuHidden = nullptr,
            .resetSearchSelectionMenuHidden = nullptr,
            .setSearchCaretStyle = nullptr,
            .resetSearchCaretStyle = nullptr,
            .setSearchTextAlign = SetSearchTextAlignImpl,
            .resetSearchTextAlign = nullptr,
            .setSearchCancelButton = nullptr,
            .resetSearchCancelButton = nullptr,
            .setSearchEnableKeyboardOnFocus = nullptr,
            .resetSearchEnableKeyboardOnFocus = nullptr,
            .setSearchPlaceholderFont = SetSearchPlaceholderFontImpl,
            .resetSearchPlaceholderFont = nullptr,
            .setSearchSearchIcon = nullptr,
            .setJsSearchSearchIcon = nullptr,
            .setSearchDefaultIcon = nullptr,
            .resetSearchSearchIcon = nullptr,
            .setSearchSearchButton = SetSearchSearchButtonImpl,
            .resetSearchSearchButton = nullptr,
            .setSearchFontColor = nullptr,
            .resetSearchFontColor = nullptr,
            .setSearchCopyOption = SetSearchCopyOptionImpl,
            .resetSearchCopyOption = nullptr,
            .setSearchEnterKeyType = nullptr,
            .resetSearchEnterKeyType = nullptr,
            .setSearchHeight = SetSearchHeightImpl,
            .resetSearchHeight = nullptr,
            .setSearchInspectorId = nullptr,
            .resetSearchInspectorId = nullptr,
            .setSearchDecoration = nullptr,
            .resetSearchDecoration = nullptr,
            .setSearchLetterSpacing = nullptr,
            .resetSearchLetterSpacing = nullptr,
            .setSearchLineHeight = nullptr,
            .resetSearchLineHeight = nullptr,
            .setSearchHalfLeading = nullptr,
            .resetSearchHalfLeading = nullptr,
            .setSearchFontFeature = nullptr,
            .resetSearchFontFeature = nullptr,
            .setSearchDividerColor = nullptr,
            .resetSearchDividerColor = nullptr,
            .setSearchAdaptMinFontSize = nullptr,
            .resetSearchAdaptMinFontSize = nullptr,
            .setSearchAdaptMaxFontSize = nullptr,
            .resetSearchAdaptMaxFontSize = nullptr,
            .setSearchSelectedBackgroundColor = nullptr,
            .resetSearchSelectedBackgroundColor = nullptr,
            .setSearchTextIndent = nullptr,
            .resetSearchTextIndent = nullptr,
            .setSearchValue = nullptr,
            .resetSearchValue = nullptr,
            .setSearchPlaceholder = nullptr,
            .resetSearchPlaceholder = nullptr,
            .setSearchIcon = nullptr,
            .resetSearchIcon = nullptr,
            .setSearchCaretPosition = nullptr,
            .resetSearchCaretPosition = nullptr,
            .setSearchMaxLength = nullptr,
            .resetSearchMaxLength = nullptr,
            .setSearchType = nullptr,
            .resetSearchType = nullptr,
            .setSearchOnEditChange = nullptr,
            .resetSearchOnEditChange = nullptr,
            .setSearchOnSubmitWithEvent = SetSearchOnSubmitWithEventImpl,
            .resetSearchOnSubmitWithEvent = nullptr,
            .setSearchOnCopy = SetSearchOnCopyImpl,
            .resetSearchOnCopy = nullptr,
            .setSearchOnCut = SetSearchOnCutImpl,
            .resetSearchOnCut = nullptr,
            .setSearchOnPaste = SetSearchOnPasteImpl,
            .resetSearchOnPaste = nullptr,
            .setSearchOnChange = nullptr,
            .resetSearchOnChange = nullptr,
            .setSearchOnTextSelectionChange = nullptr,
            .resetSearchOnTextSelectionChange = nullptr,
            .setSearchOnContentScroll = nullptr,
            .resetSearchOnContentScroll = nullptr,
            .setSearchShowCounter = nullptr,
            .resetSearchShowCounter = nullptr,
            .getSearchController = nullptr,
            .setSearchOnWillChange = nullptr,
            .resetSearchOnWillChange = nullptr,
            .setSearchOnWillInsert = nullptr,
            .resetSearchOnWillInsert = nullptr,
            .setSearchOnDidInsert = nullptr,
            .resetSearchOnDidInsert = nullptr,
            .setSearchOnWillDelete = nullptr,
            .resetSearchOnWillDelete = nullptr,
            .setSearchOnDidDelete = nullptr,
            .resetSearchOnDidDelete = nullptr,
            .setSearchEnablePreviewText = nullptr,
            .resetSearchEnablePreviewText = nullptr,
            .setSearchSelectionMenuOptions = nullptr,
            .resetSearchSelectionMenuOptions = nullptr,
            .setSearchEnableHapticFeedback = nullptr,
            .resetSearchEnableHapticFeedback = nullptr,
            .setSearchAutoCapitalizationMode = nullptr,
            .resetSearchAutoCapitalizationMode = nullptr,
            .setSearchMinFontScale = nullptr,
            .resetSearchMinFontScale = nullptr,
            .setSearchMaxFontScale = nullptr,
            .resetSearchMaxFontScale = nullptr,
            .setStopBackPress = nullptr,
            .resetStopBackPress = nullptr,
            .setSearchKeyboardAppearance = nullptr,
            .resetSearchKeyboardAppearance = nullptr,
            .setSearchStrokeWidth = nullptr,
            .resetSearchStrokeWidth = nullptr,
            .setSearchStrokeColor = nullptr,
            .resetSearchStrokeColor = nullptr,
            .setEnableAutoSpacing = nullptr,
            .resetEnableAutoSpacing = nullptr,
            .setSearchMargin = nullptr,
            .resetSearchMargin = nullptr,
            .setSearchCustomKeyboard = nullptr,
            .resetSearchCustomKeyboard = nullptr,
            .setSearchOnWillAttachIME = nullptr,
            .resetSearchOnWillAttachIME = nullptr,
            .setSearchCompressLeadingPunctuation = nullptr,
            .getSearchCompressLeadingPunctuation = nullptr,
            .resetSearchCompressLeadingPunctuation = nullptr,
            .setSearchDirection = nullptr,
            .getSearchDirection = nullptr,
            .resetSearchDirection = nullptr,
            .setIncludeFontPadding = nullptr,
            .resetIncludeFontPadding = nullptr,
            .setFallbackLineSpacing = nullptr,
            .resetFallbackLineSpacing = nullptr,
            .setSearchSelectedDragPreviewStyle = nullptr,
            .resetSearchSelectedDragPreviewStyle = nullptr,
            .getSearchSelectedDragPreviewStyle = nullptr,
            .setOnSearchSubmitExtraParam = nullptr,
            .setOnSearchChangeExtraParam = nullptr,
            .setOnSearchCopyExtraParam = nullptr,
            .setOnSearchCutExtraParam = nullptr,
            .setOnSearchPasteExtraParam = nullptr,
            .createSearchFrameNode = CreateSearchFrameNode,
            .setSearchInputFilter = nullptr,
            .resetSearchInputFilter = nullptr,
            .setSearchCustomKeyboardWithBuilder = nullptr,
            .resetSearchCustomKeyboardWithBuilder = nullptr,
            .resetSearchCaretColor = nullptr,
            .setSearchBorderRadius = nullptr,
            .setSearchBackgroundColor = nullptr,
            .resetSearchBackgroundColor = nullptr,
            .setBackBorder = SetBackBorderImpl,
            .setJsSearchCancelButton = nullptr,
            .setJsSearchDefaultCancelButton = nullptr,
            .setSearchOnChangeEvent = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISearchModifier modifier = {
        .setSelectDetectorEnable = SetSelectDetectorEnable,
        .getSelectDetectorEnable = GetSelectDetectorEnable,
        .resetSelectDetectorEnable = ResetSelectDetectorEnable,
        .setSearchPlaceholderColor = SetSearchPlaceholderColor,
        .resetSearchPlaceholderColor = ResetSearchPlaceholderColor,
        .setSearchTextFont = SetSearchTextFont,
        .resetSearchTextFont = ResetSearchTextFont,
        .setSearchSelectionMenuHidden = SetSearchSelectionMenuHidden,
        .resetSearchSelectionMenuHidden = ResetSearchSelectionMenuHidden,
        .setSearchCaretStyle = SetSearchCaretStyle,
        .resetSearchCaretStyle = ResetSearchCaretStyle,
        .setSearchTextAlign = SetSearchTextAlign,
        .resetSearchTextAlign = ResetSearchTextAlign,
        .setSearchCancelButton = SetSearchCancelButton,
        .resetSearchCancelButton = ResetSearchCancelButton,
        .setSearchEnableKeyboardOnFocus = SetSearchEnableKeyboardOnFocus,
        .resetSearchEnableKeyboardOnFocus = ResetSearchEnableKeyboardOnFocus,
        .setSearchPlaceholderFont = SetSearchPlaceholderFont,
        .resetSearchPlaceholderFont = ResetSearchPlaceholderFont,
        .setSearchSearchIcon = SetSearchSearchIcon,
        .setJsSearchSearchIcon = SetJsSearchSearchIcon,
        .setSearchDefaultIcon = SetSearchDefaultIcon,
        .resetSearchSearchIcon = ResetSearchSearchIcon,
        .setSearchSearchButton = SetSearchSearchButton,
        .resetSearchSearchButton = ResetSearchSearchButton,
        .setSearchFontColor = SetSearchFontColor,
        .resetSearchFontColor = ResetSearchFontColor,
        .setSearchCopyOption = SetSearchCopyOption,
        .resetSearchCopyOption = ResetSearchCopyOption,
        .setSearchEnterKeyType = SetSearchEnterKeyType,
        .resetSearchEnterKeyType = ResetSearchEnterKeyType,
        .setSearchHeight = SetSearchHeight,
        .resetSearchHeight = ResetSearchHeight,
        .setSearchInspectorId = SetSearchInspectorId,
        .resetSearchInspectorId = ResetSearchInspectorId,
        .setSearchDecoration = SetSearchDecoration,
        .resetSearchDecoration = ResetSearchDecoration,
        .setSearchLetterSpacing = SetSearchLetterSpacing,
        .resetSearchLetterSpacing = ResetSearchLetterSpacing,
        .setSearchLineHeight = SetSearchLineHeight,
        .resetSearchLineHeight = ResetSearchLineHeight,
        .setSearchHalfLeading = SetSearchHalfLeading,
        .resetSearchHalfLeading = ResetSearchHalfLeading,
        .setSearchFontFeature = SetSearchFontFeature,
        .resetSearchFontFeature = ResetSearchFontFeature,
        .setSearchDividerColor = SetSearchDividerColor,
        .resetSearchDividerColor = ResetSearchDividerColor,
        .setSearchAdaptMinFontSize = SetSearchAdaptMinFontSize,
        .resetSearchAdaptMinFontSize = ResetSearchAdaptMinFontSize,
        .setSearchAdaptMaxFontSize = SetSearchAdaptMaxFontSize,
        .resetSearchAdaptMaxFontSize = ResetSearchAdaptMaxFontSize,
        .setSearchSelectedBackgroundColor = SetSearchSelectedBackgroundColor,
        .resetSearchSelectedBackgroundColor = ResetSearchSelectedBackgroundColor,
        .setSearchTextIndent = SetSearchTextIndent,
        .resetSearchTextIndent = ResetSearchTextIndent,
        .setSearchValue = SetSearchValue,
        .resetSearchValue = ResetSearchValue,
        .setSearchPlaceholder = SetSearchPlaceholder,
        .resetSearchPlaceholder = ResetSearchPlaceholder,
        .setSearchIcon = SetSearchIcon,
        .resetSearchIcon = ResetSearchIcon,
        .setSearchCaretPosition = SetSearchCaretPosition,
        .resetSearchCaretPosition = ResetSearchCaretPosition,
        .setSearchMaxLength = SetSearchMaxLength,
        .resetSearchMaxLength = ResetSearchMaxLength,
        .setSearchType = SetSearchType,
        .resetSearchType = ResetSearchType,
        .setSearchOnEditChange = SetSearchOnEditChange,
        .resetSearchOnEditChange = ResetSearchOnEditChange,
        .setSearchOnSubmitWithEvent = SetSearchOnSubmitWithEvent,
        .resetSearchOnSubmitWithEvent = ResetSearchOnSubmitWithEvent,
        .setSearchOnCopy = SetSearchOnCopy,
        .resetSearchOnCopy = ResetSearchOnCopy,
        .setSearchOnCut = SetSearchOnCut,
        .resetSearchOnCut = ResetSearchOnCut,
        .setSearchOnPaste = SetSearchOnPaste,
        .resetSearchOnPaste = ResetSearchOnPaste,
        .setSearchOnChange = SetSearchOnChange,
        .resetSearchOnChange = ResetSearchOnChange,
        .setSearchOnTextSelectionChange = SetSearchOnTextSelectionChange,
        .resetSearchOnTextSelectionChange = ResetSearchOnTextSelectionChange,
        .setSearchOnContentScroll = SetSearchOnContentScroll,
        .resetSearchOnContentScroll = ResetSearchOnContentScroll,
        .setSearchShowCounter = SetSearchShowCounterOptions,
        .resetSearchShowCounter = ResetSearchShowCounterOptions,
        .getSearchController = GetSearchController,
        .setSearchOnWillChange = SetSearchOnWillChange,
        .resetSearchOnWillChange = ResetSearchOnWillChange,
        .setSearchOnWillInsert = SetSearchOnWillInsert,
        .resetSearchOnWillInsert = ResetSearchOnWillInsert,
        .setSearchOnDidInsert = SetSearchOnDidInsert,
        .resetSearchOnDidInsert = ResetSearchOnDidInsert,
        .setSearchOnWillDelete = SetSearchOnWillDelete,
        .resetSearchOnWillDelete = ResetSearchOnWillDelete,
        .setSearchOnDidDelete = SetSearchOnDidDelete,
        .resetSearchOnDidDelete = ResetSearchOnDidDelete,
        .setSearchEnablePreviewText = SetSearchEnablePreviewText,
        .resetSearchEnablePreviewText = ResetSearchEnablePreviewText,
        .setSearchSelectionMenuOptions = SetSearchSelectionMenuOptions,
        .resetSearchSelectionMenuOptions = ResetSearchSelectionMenuOptions,
        .setSearchEnableHapticFeedback = SetSearchEnableHapticFeedback,
        .resetSearchEnableHapticFeedback = ResetSearchEnableHapticFeedback,
        .setSearchAutoCapitalizationMode = SetSearchAutoCapitalizationMode,
        .resetSearchAutoCapitalizationMode = ResetSearchAutoCapitalizationMode,
        .setSearchMinFontScale = SetSearchMinFontScale,
        .resetSearchMinFontScale = ResetSearchMinFontScale,
        .setSearchMaxFontScale = SetSearchMaxFontScale,
        .resetSearchMaxFontScale = ResetSearchMaxFontScale,
        .setStopBackPress = SetStopBackPress,
        .resetStopBackPress = ResetStopBackPress,
        .setSearchKeyboardAppearance = SetSearchKeyboardAppearance,
        .resetSearchKeyboardAppearance = ResetSearchKeyboardAppearance,
        .setSearchStrokeWidth = SetSearchStrokeWidth,
        .resetSearchStrokeWidth = ResetSearchStrokeWidth,
        .setSearchStrokeColor = SetSearchStrokeColor,
        .resetSearchStrokeColor = ResetSearchStrokeColor,
        .setEnableAutoSpacing = SetEnableAutoSpacing,
        .resetEnableAutoSpacing = ResetEnableAutoSpacing,
        .setSearchMargin = SetSearchMargin,
        .resetSearchMargin = ResetSearchMargin,
        .setSearchCustomKeyboard = SetSearchCustomKeyboard,
        .resetSearchCustomKeyboard = ResetSearchCustomKeyboard,
        .setSearchOnWillAttachIME = SetSearchOnWillAttachIME,
        .resetSearchOnWillAttachIME = ResetSearchOnWillAttachIME,
        .setSearchCompressLeadingPunctuation = SetSearchCompressLeadingPunctuation,
        .getSearchCompressLeadingPunctuation = GetSearchCompressLeadingPunctuation,
        .resetSearchCompressLeadingPunctuation = ResetSearchCompressLeadingPunctuation,
        .setSearchDirection = SetSearchDirection,
        .getSearchDirection = GetSearchDirection,
        .resetSearchDirection = ResetSearchDirection,
        .setIncludeFontPadding = SetIncludeFontPadding,
        .resetIncludeFontPadding = ResetIncludeFontPadding,
        .setFallbackLineSpacing = SetFallbackLineSpacing,
        .resetFallbackLineSpacing = ResetFallbackLineSpacing,
        .setSearchSelectedDragPreviewStyle = SetSearchSelectedDragPreviewStyle,
        .resetSearchSelectedDragPreviewStyle = ResetSearchSelectedDragPreviewStyle,
        .getSearchSelectedDragPreviewStyle = GetSearchSelectedDragPreviewStyle,
        .setOnSearchSubmitExtraParam = SetOnSearchSubmitExtraParam,
        .setOnSearchChangeExtraParam = SetOnSearchChangeExtraParam,
        .setOnSearchCopyExtraParam = SetOnSearchCopyExtraParam,
        .setOnSearchCutExtraParam = SetOnSearchCutExtraParam,
        .setOnSearchPasteExtraParam = SetOnSearchPasteExtraParam,
        .createSearchFrameNode = CreateSearchFrameNode,
        .setSearchInputFilter = SetSearchInputFilter,
        .resetSearchInputFilter = ResetSearchInputFilter,
        .setSearchCustomKeyboardWithBuilder = SetSearchCustomKeyboardWithBuilder,
        .resetSearchCustomKeyboardWithBuilder = ResetSearchCustomKeyboardWithBuilder,
        .resetSearchCaretColor = ResetSearchCaretColor,
        .setSearchBorderRadius = SetSearchBorderRadius,
        .setSearchBackgroundColor = SetSearchBackgroundColor,
        .resetSearchBackgroundColor = RetSetSearchBackgroundColor,
        .setBackBorder = SetBackBorder,
        .setJsSearchCancelButton = SetJsSearchCancelButton,
        .setJsSearchDefaultCancelButton = SetJsSearchDefaultCancelButton,
        .setSearchOnChangeEvent = SetSearchOnChangeEvent,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUISearchModifier* GetCJUISearchModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUISearchModifier modifier = {
        .setSelectDetectorEnable = SetSelectDetectorEnable,
        .getSelectDetectorEnable = GetSelectDetectorEnable,
        .resetSelectDetectorEnable = ResetSelectDetectorEnable,
        .setSearchPlaceholderColor = SetSearchPlaceholderColor,
        .resetSearchPlaceholderColor = ResetSearchPlaceholderColor,
        .setSearchTextFont = SetSearchTextFont,
        .resetSearchTextFont = ResetSearchTextFont,
        .setSearchSelectionMenuHidden = SetSearchSelectionMenuHidden,
        .resetSearchSelectionMenuHidden = ResetSearchSelectionMenuHidden,
        .setSearchCaretStyle = SetSearchCaretStyle,
        .resetSearchCaretStyle = ResetSearchCaretStyle,
        .setSearchTextAlign = SetSearchTextAlign,
        .resetSearchTextAlign = ResetSearchTextAlign,
        .setSearchCancelButton = SetSearchCancelButton,
        .resetSearchCancelButton = ResetSearchCancelButton,
        .setSearchEnableKeyboardOnFocus = SetSearchEnableKeyboardOnFocus,
        .resetSearchEnableKeyboardOnFocus = ResetSearchEnableKeyboardOnFocus,
        .setSearchPlaceholderFont = SetSearchPlaceholderFont,
        .resetSearchPlaceholderFont = ResetSearchPlaceholderFont,
        .setSearchSearchIcon = SetSearchSearchIcon,
        .resetSearchSearchIcon = ResetSearchSearchIcon,
        .setSearchSearchButton = SetSearchSearchButton,
        .resetSearchSearchButton = ResetSearchSearchButton,
        .setSearchFontColor = SetSearchFontColor,
        .resetSearchFontColor = ResetSearchFontColor,
        .setSearchCopyOption = SetSearchCopyOption,
        .resetSearchCopyOption = ResetSearchCopyOption,
        .setSearchEnterKeyType = SetSearchEnterKeyType,
        .resetSearchEnterKeyType = ResetSearchEnterKeyType,
        .setSearchHeight = SetSearchHeight,
        .resetSearchHeight = ResetSearchHeight,
        .setSearchFontFeature = SetSearchFontFeature,
        .resetSearchFontFeature = ResetSearchFontFeature,
        .setSearchDecoration = SetSearchDecoration,
        .resetSearchDecoration = ResetSearchDecoration,
        .setSearchLetterSpacing = SetSearchLetterSpacing,
        .resetSearchLetterSpacing = ResetSearchLetterSpacing,
        .setSearchLineHeight = SetSearchLineHeight,
        .resetSearchLineHeight = ResetSearchLineHeight,
        .setSearchDividerColor = SetSearchDividerColor,
        .resetSearchDividerColor = ResetSearchDividerColor,
        .setSearchAdaptMinFontSize = SetSearchAdaptMinFontSize,
        .resetSearchAdaptMinFontSize = ResetSearchAdaptMinFontSize,
        .setSearchAdaptMaxFontSize = SetSearchAdaptMaxFontSize,
        .resetSearchAdaptMaxFontSize = ResetSearchAdaptMaxFontSize,
        .setSearchSelectedBackgroundColor = SetSearchSelectedBackgroundColor,
        .resetSearchSelectedBackgroundColor = ResetSearchSelectedBackgroundColor,
        .setSearchTextIndent = SetSearchTextIndent,
        .resetSearchTextIndent = ResetSearchTextIndent,
        .setSearchMaxLength = SetSearchMaxLength,
        .resetSearchMaxLength = ResetSearchMaxLength,
        .setSearchType = SetSearchType,
        .resetSearchType = ResetSearchType,
        .setSearchOnEditChange = SetSearchOnEditChange,
        .resetSearchOnEditChange = ResetSearchOnEditChange,
        .setSearchOnSubmitWithEvent = SetSearchOnSubmitWithEvent,
        .resetSearchOnSubmitWithEvent = ResetSearchOnSubmitWithEvent,
        .setSearchOnCopy = SetSearchOnCopy,
        .resetSearchOnCopy = ResetSearchOnCopy,
        .setSearchOnCut = SetSearchOnCut,
        .resetSearchOnCut = ResetSearchOnCut,
        .setSearchOnPaste = SetSearchOnPaste,
        .resetSearchOnPaste = ResetSearchOnPaste,
        .setSearchOnChange = SetSearchOnChange,
        .resetSearchOnChange = ResetSearchOnChange,
        .setSearchOnTextSelectionChange = SetSearchOnTextSelectionChange,
        .resetSearchOnTextSelectionChange = ResetSearchOnTextSelectionChange,
        .setSearchOnContentScroll = SetSearchOnContentScroll,
        .resetSearchOnContentScroll = ResetSearchOnContentScroll,
        .setSearchShowCounter = SetSearchShowCounterOptions,
        .resetSearchShowCounter = ResetSearchShowCounterOptions,
        .getSearchController = GetSearchController,
        .setSearchValue = SetSearchValue,
        .resetSearchValue = ResetSearchValue,
        .setSearchPlaceholder = SetSearchPlaceholder,
        .resetSearchPlaceholder = ResetSearchPlaceholder,
        .setSearchIcon = SetSearchIcon,
        .resetSearchIcon = ResetSearchIcon,
        .setSearchOnWillInsert = SetSearchOnWillInsert,
        .resetSearchOnWillInsert = ResetSearchOnWillInsert,
        .setSearchOnDidInsert = SetSearchOnDidInsert,
        .resetSearchOnDidInsert = ResetSearchOnDidInsert,
        .setSearchOnWillDelete = SetSearchOnWillDelete,
        .resetSearchOnWillDelete = ResetSearchOnWillDelete,
        .setSearchOnDidDelete = SetSearchOnDidDelete,
        .resetSearchOnDidDelete = ResetSearchOnDidDelete,
        .setSearchEnablePreviewText = SetSearchEnablePreviewText,
        .resetSearchEnablePreviewText = ResetSearchEnablePreviewText,
        .setSearchCaretPosition = SetSearchCaretPosition,
        .resetSearchCaretPosition = ResetSearchCaretPosition,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUISearchCustomModifier* GetSearchCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISearchCustomModifier modifier = {
        .setKeyboardAppearanceConfig = SetKeyboardAppearanceConfig,
        .setTextValue = SetTextValue,
        .setOnChangeEvent = SetOnChangeEvent,
        .createNormalSearch = CreateNormalSearch,
        .setSearchSymbolIcon = SetSearchSymbolIcon,
        .setSearchCancelSymbolIcon = SetSearchCancelSymbolIcon,
        .setDragPreviewOptions = SetDragPreviewOptions,
        .getInstance = GetInstance,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

void SetSearchKeyboardAppearance(ArkUINodeHandle node, ArkUI_Uint32 keyboardAppearance)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto value = static_cast<KeyboardAppearance>(keyboardAppearance);
    SearchModelNG::SetKeyboardAppearance(frameNode, value);
}

void ResetSearchKeyboardAppearance(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto value = KeyboardAppearance::NONE_IMMERSIVE;
    SearchModelNG::SetKeyboardAppearance(frameNode, value);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
