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
#include "core/interfaces/native/node/menu_modifier.h"

#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/property/border_property.h"

namespace OHOS::Ace::NG {
const char DELIMITER = '|';
constexpr int32_t SIZE_OF_FONT_INFO = 3;
constexpr int COUNT_PROP = 4;
static const char* ERR_CODE = "-1";
constexpr int SUB_MENU_EXPANDING_MODE_SIDE = 0;
constexpr int SUB_MENU_EXPANDING_MODE_EMBEDDED = 1;
constexpr int SUB_MENU_EXPANDING_MODE_STACK = 2;
const std::string DEFAULT_FONT_WEIGHT = "normal";
const std::string DEFAULT_FONT_FAMILY = "HarmonyOS Sans";
const Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };

SubMenuExpandingMode ParseSubMenuExpandingMode(int32_t subMenuExpandingMode)
{
    SubMenuExpandingMode mode = SubMenuExpandingMode::SIDE;
    switch (subMenuExpandingMode) {
        case SUB_MENU_EXPANDING_MODE_SIDE:
            mode = SubMenuExpandingMode::SIDE;
            break;
        case SUB_MENU_EXPANDING_MODE_EMBEDDED:
            mode = SubMenuExpandingMode::EMBEDDED;
            break;
        case SUB_MENU_EXPANDING_MODE_STACK:
            mode = SubMenuExpandingMode::STACK;
            break;
        default:
            break;
    }
    return mode;
}

void SetMenuDivider(ArkUINodeHandle node, ArkUIMenuDividerOptions* dividerInfo, void* colorRawPtr, bool isGroupDivider)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    V2::ItemDivider divider;
    divider.strokeWidth = Dimension(dividerInfo->strokeWidth.value,
        static_cast<OHOS::Ace::DimensionUnit>(dividerInfo->strokeWidth.units));
    divider.color = Color(dividerInfo->color);
    divider.startMargin = Dimension(dividerInfo->startMargin.value,
        static_cast<OHOS::Ace::DimensionUnit>(dividerInfo->startMargin.units));
    divider.endMargin = Dimension(dividerInfo->endMargin.value,
        static_cast<OHOS::Ace::DimensionUnit>(dividerInfo->endMargin.units));
    DividerMode mode = dividerInfo->mode == 1 ? DividerMode::EMBEDDED_IN_MENU: DividerMode::FLOATING_ABOVE_MENU;
    if (isGroupDivider) {
        MenuModelNG::SetItemGroupDivider(frameNode, divider, mode);
    } else {
        MenuModelNG::SetItemDivider(frameNode, divider, mode);
    }
    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        MenuModelNG::CreateWithColorResourceObj(frameNode, colorResObj,
            isGroupDivider ? MenuColorType::GROUP_DIVIDER_COLOR : MenuColorType::DIVIDER_COLOR);
    }
}

void ResetMenuDivider(ArkUINodeHandle node, bool isGroupDivider)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    V2::ItemDivider divider;
    divider.strokeWidth = Dimension(0.0);
    divider.color = Color::TRANSPARENT;
    divider.startMargin = Dimension(0.0);
    divider.endMargin = Dimension(0.0);
    if (isGroupDivider) {
        MenuModelNG::SetItemGroupDivider(frameNode, divider, DividerMode::FLOATING_ABOVE_MENU);
    } else {
        MenuModelNG::SetItemDivider(frameNode, divider, DividerMode::FLOATING_ABOVE_MENU);
    }
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> nullResObj = nullptr;
        MenuModelNG::CreateWithColorResourceObj(frameNode, nullResObj,
            isGroupDivider ? MenuColorType::GROUP_DIVIDER_COLOR : MenuColorType::DIVIDER_COLOR);
    }
}

void SetMenuFontColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelNG::SetFontColor(frameNode, Color(color));
}

void SetMenuFontColorWithResource(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelNG::SetFontColor(frameNode, Color(color));
    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        MenuModelNG::CreateWithColorResourceObj(frameNode, colorResObj, MenuColorType::FONT_COLOR);
    }
}

void ResetMenuFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> color = std::nullopt;
    MenuModelNG::SetFontColor(frameNode, color);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> nullResObj = nullptr;
        MenuModelNG::CreateWithColorResourceObj(frameNode, nullResObj, MenuColorType::FONT_COLOR);
    }
}

void SetMenuFont(ArkUINodeHandle node, const char* fontInfo, int32_t styleVal)
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
    if (res[0] != ERR_CODE) { // 0: index of font size data
        fontSize = StringUtils::StringToCalcDimension(res[0], false, DimensionUnit::FP);
    }
    MenuModelNG::SetFontSize(frameNode, fontSize);
    if (res[1] != ERR_CODE) { // 1: index of font weight data
        MenuModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(res[1]));
    } else {
        MenuModelNG::SetFontWeight(frameNode, FontWeight::NORMAL);
    }

    if (styleVal >= 0 && styleVal < static_cast<int32_t>(FONT_STYLES.size())) {
        MenuModelNG::SetFontStyle(frameNode, FONT_STYLES[styleVal]);
    } else {
        MenuModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
    }

    if (res[2] != ERR_CODE) { // 2: index of font family data
        MenuModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(res[2]));
    } else {
        MenuModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY));
    }
}

void SetMenuFontWithResource(
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
    if (res[0] != ERR_CODE) { // 0: index of font size data
        fontSize = StringUtils::StringToCalcDimension(res[0], false, DimensionUnit::FP);
    }
    MenuModelNG::SetFontSize(frameNode, fontSize);
    if (SystemProperties::ConfigChangePerform() && fontSizeRawPtr) {
        auto* fontSizePtr = reinterpret_cast<ResourceObject*>(fontSizeRawPtr);
        auto fontSizeResObj = AceType::Claim(fontSizePtr);
        MenuModelNG::CreateWithDimensionResourceObj(frameNode, fontSizeResObj, MenuDimensionType::FONT_SIZE);
    }

    if (res[1] != ERR_CODE) { // 1: index of font weight data
        MenuModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(res[1]));
    } else {
        MenuModelNG::SetFontWeight(frameNode, FontWeight::NORMAL);
    }

    if (styleVal >= 0 && styleVal < static_cast<int32_t>(FONT_STYLES.size())) {
        MenuModelNG::SetFontStyle(frameNode, FONT_STYLES[styleVal]);
    } else {
        MenuModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
    }

    if (res[2] != ERR_CODE) { // 2: index of font family data
        MenuModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(res[2]));
        if (SystemProperties::ConfigChangePerform() && fontFamilyRawPtr) {
            auto* fontFamilyPtr = reinterpret_cast<ResourceObject*>(fontFamilyRawPtr);
            auto fontFamilyResObj = AceType::Claim(fontFamilyPtr);
            MenuModelNG::CreateWithFontFamilyResourceObj(frameNode, fontFamilyResObj, MenuFamilyType::FONT_FAMILY);
        }
    } else {
        MenuModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY));
    }
}

void ResetMenuFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension fontSize;
    FontWeight fontWeight = StringUtils::StringToFontWeight(DEFAULT_FONT_WEIGHT);
    MenuModelNG::SetFontSize(frameNode, fontSize);
    MenuModelNG::SetFontWeight(frameNode, fontWeight);
    MenuModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
    MenuModelNG::SetFontFamily(frameNode, Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY));
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> nullResObj = nullptr;
        MenuModelNG::CreateWithDimensionResourceObj(frameNode, nullResObj, MenuDimensionType::FONT_SIZE);
        MenuModelNG::CreateWithFontFamilyResourceObj(frameNode, nullResObj, MenuFamilyType::FONT_FAMILY);
    }
}

void ResetRadius(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelNG::ResetBorderRadius(frameNode);
}

void SetRadius(
    ArkUINodeHandle node, const ArkUI_Float32* values, const int32_t* units)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto topLeft = Dimension(values[0], static_cast<OHOS::Ace::DimensionUnit>(units[0])); // 0: index of top left value
    auto topRight =
        Dimension(values[1], static_cast<OHOS::Ace::DimensionUnit>(units[1])); // 1: index of top right value
    auto bottomLeft =
        Dimension(values[2], static_cast<OHOS::Ace::DimensionUnit>(units[2])); // 2: index of bottom left value
    auto bottomRight =
        Dimension(values[3], static_cast<OHOS::Ace::DimensionUnit>(units[3])); // 3: index of bottom right value
    if (topLeft.IsNegative() || topRight.IsNegative() || bottomLeft.IsNegative() || bottomRight.IsNegative()) {
        ResetRadius(node);
    }
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = topLeft;
    borderRadius.radiusTopRight = topRight;
    borderRadius.radiusBottomLeft = bottomLeft;
    borderRadius.radiusBottomRight = bottomRight;
    borderRadius.multiValued = true;
    MenuModelNG::SetBorderRadius(frameNode, borderRadius);
}

#define ADD_RADIUS_RESOURCE(resObjPtr, radiusProp, propName, dimensionMember) \
    auto propName##Update = [](const RefPtr<ResourceObject>& obj, BorderRadiusProperty& prop) { \
        CalcDimension dim; \
        ResourceParseUtils::ParseResDimensionVp(obj, dim); \
        prop.dimensionMember = dim; \
    }; \
    propName##ResObj->DecRefCount(); \
    const std::string resourceKey = std::string("borderRadius.") + #dimensionMember; \
    (radiusProp).AddResource(resourceKey, propName##ResObj, std::move(propName##Update))

void AddRadiusResource(BorderRadiusProperty& borderRadius, void** resObjs)
{
    auto* topLeftResPtr = reinterpret_cast<ResourceObject*>(resObjs[0]);
    auto topLeftResObj = AceType::Claim(topLeftResPtr);
    auto* topRightResPtr = reinterpret_cast<ResourceObject*>(resObjs[1]);
    auto topRightResObj = AceType::Claim(topRightResPtr);
    auto* bottomLeftResPtr = reinterpret_cast<ResourceObject*>(resObjs[2]);
    auto bottomLeftResObj = AceType::Claim(bottomLeftResPtr);
    auto* bottomRightResPtr = reinterpret_cast<ResourceObject*>(resObjs[3]);
    auto bottomRightResObj = AceType::Claim(bottomRightResPtr);
    if (topLeftResObj) {
        ADD_RADIUS_RESOURCE(resObjs[0], borderRadius, topLeft, radiusTopLeft);
    }
    if (topRightResObj) {
        ADD_RADIUS_RESOURCE(resObjs[1], borderRadius, topRight, radiusTopRight);
    }
    if (bottomLeftResObj) {
        ADD_RADIUS_RESOURCE(resObjs[2], borderRadius, bottomLeft, radiusBottomLeft);
    }
    if (bottomRightResObj) {
        ADD_RADIUS_RESOURCE(resObjs[3], borderRadius, bottomRight, radiusBottomRight);
    }
}

void SetRadiusWithResource(
    ArkUINodeHandle node, const ArkUI_Float32* values, const int32_t* units, void** resObjs, size_t unitSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!values || !units || !resObjs || unitSize < COUNT_PROP) {
        return;
    }
    auto topLeft =
        Dimension(values[0], static_cast<OHOS::Ace::DimensionUnit>(units[0])); // 0: index of top left value
    auto topRight =
        Dimension(values[1], static_cast<OHOS::Ace::DimensionUnit>(units[1])); // 1: index of top right value
    auto bottomLeft =
        Dimension(values[2], static_cast<OHOS::Ace::DimensionUnit>(units[2])); // 2: index of bottom left value
    auto bottomRight =
        Dimension(values[3], static_cast<OHOS::Ace::DimensionUnit>(units[3])); // 3: index of bottom right value
    if (topLeft.IsNegative() || topRight.IsNegative() || bottomLeft.IsNegative() || bottomRight.IsNegative()) {
        ResetRadius(node);
    }
    BorderRadiusProperty borderRadius;
    AddRadiusResource(borderRadius, resObjs);
    borderRadius.radiusTopLeft = topLeft;
    borderRadius.radiusTopRight = topRight;
    borderRadius.radiusBottomLeft = bottomLeft;
    borderRadius.radiusBottomRight = bottomRight;
    borderRadius.multiValued = true;
    MenuModelNG::SetBorderRadius(frameNode, borderRadius);
}

void SetMenuWidth(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    MenuModelNG::SetWidth(frameNode, width);
}

void ResetMenuWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::CalcDimension reset;
    MenuModelNG::SetWidth(frameNode, reset);
}

void SetMenuItemDivider(ArkUINodeHandle node, ArkUIMenuDividerOptions* menuItemDividerInfo)
{
    SetMenuDivider(node, menuItemDividerInfo, nullptr, false);
}

void SetMenuItemDividerWithResource(ArkUINodeHandle node, ArkUIMenuDividerOptions* menuItemDividerInfo,
    void* colorRawPtr)
{
    SetMenuDivider(node, menuItemDividerInfo, colorRawPtr, false);
}

void ResetMenuItemDivider(ArkUINodeHandle node)
{
    ResetMenuDivider(node, false);
}

void SetMenuItemGroupDivider(
    ArkUINodeHandle node, ArkUIMenuDividerOptions* menuItemGroupDividerInfo)
{
    SetMenuDivider(node, menuItemGroupDividerInfo, nullptr, true);
}

void SetMenuItemGroupDividerWithResource(
    ArkUINodeHandle node, ArkUIMenuDividerOptions* menuItemGroupDividerInfo, void* colorRawPtr)
{
    SetMenuDivider(node, menuItemGroupDividerInfo, colorRawPtr, true);
}

void ResetMenuItemGroupDivider(ArkUINodeHandle node)
{
    ResetMenuDivider(node, true);
}

void SetSubMenuExpandingMode(ArkUINodeHandle node, ArkUI_Int32 modeParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    SubMenuExpandingMode subMenuExpandingMode = ParseSubMenuExpandingMode(modeParam);
    MenuModelNG::SetExpandingMode(frameNode, subMenuExpandingMode);
}

void ResetSubMenuExpandingMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelNG::SetExpandingMode(frameNode, SubMenuExpandingMode::SIDE);
}

void SetSubMenuExpandSymbol(ArkUINodeHandle node, void* symbolFunction)
{
    CHECK_NULL_VOID(symbolFunction);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto symbolCallback = reinterpret_cast<std::function<void(WeakPtr<NG::FrameNode>)>*>(symbolFunction);
    MenuModelNG::SetExpandSymbol(frameNode, std::move(*symbolCallback));
}

void ResetSubMenuExpandSymbol(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelNG::SetExpandSymbol(frameNode, nullptr);
}

void SetMenuFontSize(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit, void* fontSizeRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension fontSize = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    MenuModelNG::SetFontSize(frameNode, fontSize);
    if (SystemProperties::ConfigChangePerform() && fontSizeRawPtr) {
        auto* fontSizePtr = reinterpret_cast<ResourceObject*>(fontSizeRawPtr);
        auto fontSizeResObj = AceType::Claim(fontSizePtr);
        MenuModelNG::CreateWithDimensionResourceObj(frameNode, fontSizeResObj, MenuDimensionType::FONT_SIZE);
    }
}

void ResetMenuFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::CalcDimension reset;
    MenuModelNG::SetFontSize(frameNode, reset);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> nullResObj = nullptr;
        MenuModelNG::CreateWithDimensionResourceObj(frameNode, nullResObj, MenuDimensionType::FONT_SIZE);
    }
}

namespace NodeModifier {
const ArkUIMenuModifier* GetMenuModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIMenuModifier modifier = {
        .setMenuFontColor = SetMenuFontColorWithResource,
        .resetMenuFontColor = ResetMenuFontColor,
        .setFont = SetMenuFontWithResource,
        .resetFont = ResetMenuFont,
        .setRadius = SetRadiusWithResource,
        .resetRadius = ResetRadius,
        .setMenuWidth = SetMenuWidth,
        .resetMenuWidth = ResetMenuWidth,
        .setMenuItemDivider = SetMenuItemDivider,
        .setMenuItemDividerWithResource = SetMenuItemDividerWithResource,
        .resetMenuItemDivider = ResetMenuItemDivider,
        .setMenuItemGroupDivider = SetMenuItemGroupDivider,
        .setMenuItemGroupDividerWithResource = SetMenuItemGroupDividerWithResource,
        .resetMenuItemGroupDivider = ResetMenuItemGroupDivider,
        .setSubMenuExpandingMode = SetSubMenuExpandingMode,
        .resetSubMenuExpandingMode = ResetSubMenuExpandingMode,
        .setSubMenuExpandSymbol = SetSubMenuExpandSymbol,
        .resetSubMenuExpandSymbol = ResetSubMenuExpandSymbol,
        .setMenuFontSize = SetMenuFontSize,
        .resetMenuFontSize = ResetMenuFontSize,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIMenuModifier* GetCJUIMenuModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIMenuModifier modifier = {
        .setMenuFontColor = SetMenuFontColor,
        .resetMenuFontColor = ResetMenuFontColor,
        .setFont = SetMenuFont,
        .resetFont = ResetMenuFont,
        .setRadius = SetRadius,
        .resetRadius = ResetRadius,
        .setMenuWidth = SetMenuWidth,
        .resetMenuWidth = ResetMenuWidth,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
