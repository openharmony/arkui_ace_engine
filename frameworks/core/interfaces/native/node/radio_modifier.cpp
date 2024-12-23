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
#include "core/interfaces/native/node/radio_modifier.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr bool DEFAULT_CHECKED = false;
const int32_t ERROR_INT_CODE = -1;
std::string g_radioStrValue;

void SetRadioChecked(ArkUINodeHandle node, ArkUI_Bool isCheck)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetChecked(frameNode, isCheck);
}

void ResetRadioChecked(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetChecked(frameNode, DEFAULT_CHECKED);
}

void SetRadioStyle(ArkUINodeHandle node, ArkUI_Uint32 checkedBackgroundColor, ArkUI_Uint32 uncheckedBorderColor,
    ArkUI_Uint32 indicatorColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    RadioModelNG::SetCheckedBackgroundColor(frameNode, Color(checkedBackgroundColor));
    RadioModelNG::SetUncheckedBorderColor(frameNode, Color(uncheckedBorderColor));
    RadioModelNG::SetIndicatorColor(frameNode, Color(indicatorColor));
}

void ResetRadioStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(theme);

    RadioModelNG::SetCheckedBackgroundColor(frameNode, theme->GetActiveColor());
    RadioModelNG::SetUncheckedBorderColor(frameNode, theme->GetInactiveColor());
    RadioModelNG::SetIndicatorColor(frameNode, theme->GetPointColor());
}

void SetRadioWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        ViewAbstract::SetWidth(frameNode, CalcLength(CalcLength(std::string(calcValue))));
    } else {
        ViewAbstract::SetWidth(frameNode, CalcLength(value, unitEnum));
    }
}

void ResetRadioWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
}

void SetRadioHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        ViewAbstract::SetHeight(frameNode, CalcLength(CalcLength(std::string(calcValue))));
    } else {
        ViewAbstract::SetHeight(frameNode, CalcLength(value, unitEnum));
    }
}

void ResetRadioHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}

void SetRadioSize(ArkUINodeHandle node, ArkUI_Float32 widthValue, ArkUI_Int32 widthUnit, ArkUI_Float32 heightValue,
    ArkUI_Int32 heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetWidth(frameNode, Dimension(widthValue, static_cast<OHOS::Ace::DimensionUnit>(widthUnit)));
    RadioModelNG::SetHeight(frameNode, Dimension(heightValue, static_cast<OHOS::Ace::DimensionUnit>(heightUnit)));
}

void ResetRadioSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    auto defaultWidth = radioTheme->GetDefaultWidth();
    auto horizontalPadding = radioTheme->GetHotZoneHorizontalPadding();
    auto width = defaultWidth - horizontalPadding * 2; //2 is Calculate the parameters of the formula

    auto defaultHeight = radioTheme->GetDefaultHeight();
    auto verticalPadding = radioTheme->GetHotZoneVerticalPadding();
    auto height = defaultHeight - verticalPadding * 2; //2 is Calculate the parameters of the formula
    RadioModelNG::SetWidth(frameNode, width);
    RadioModelNG::SetHeight(frameNode, height);
}

void SetRadioHoverEffect(ArkUINodeHandle node, ArkUI_Int32 hoverEffectValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::HoverEffectType hoverEffect = OHOS::Ace::HoverEffectType::AUTO;
    hoverEffect = static_cast<OHOS::Ace::HoverEffectType>(hoverEffectValue);
    RadioModelNG::SetHoverEffect(frameNode, hoverEffect);
}

void ResetRadioHoverEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetHoverEffect(frameNode, OHOS::Ace::HoverEffectType::AUTO);
}

void SetRadioPadding(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
    const struct ArkUISizeType* bottom, const struct ArkUISizeType* left)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcLength topDimen;
    CalcLength rightDimen;
    CalcLength bottomDimen;
    CalcLength leftDimen;
    if (top->string != nullptr) {
        topDimen = CalcLength(top->string);
    } else {
        topDimen = CalcLength(top->value, static_cast<DimensionUnit>(top->unit));
    }
    if (right->string != nullptr) {
        rightDimen = CalcLength(right->string);
    } else {
        rightDimen = CalcLength(right->value, static_cast<DimensionUnit>(right->unit));
    }
    if (bottom->string != nullptr) {
        bottomDimen = CalcLength(bottom->string);
    } else {
        bottomDimen = CalcLength(bottom->value, static_cast<DimensionUnit>(bottom->unit));
    }
    if (left->string != nullptr) {
        leftDimen = CalcLength(left->string);
    } else {
        leftDimen = CalcLength(left->value, static_cast<DimensionUnit>(left->unit));
    }
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(topDimen);
    paddings.bottom = std::optional<CalcLength>(bottomDimen);
    paddings.left = std::optional<CalcLength>(leftDimen);
    paddings.right = std::optional<CalcLength>(rightDimen);
    RadioModelNG::SetPadding(frameNode, paddings);
}

void ResetRadioPadding(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.bottom = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.left = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.right = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    RadioModelNG::SetPadding(frameNode, paddings);
}

void SetRadioResponseRegion(
    ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Uint32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    for (uint32_t i = 0; i < length / 4; i++) { //4 is 4 different parameters
        CalcDimension xDimen =
            CalcDimension(values[i * 4 + 0], static_cast<DimensionUnit>(units[i * 4 + 0])); //4：parameters
        CalcDimension yDimen =
            CalcDimension(values[i * 4 + 1], static_cast<DimensionUnit>(units[i * 4 + 1])); //4：parameters
        CalcDimension widthDimen =
            CalcDimension(values[i * 4 + 2], static_cast<DimensionUnit>(units[i * 4 + 2])); //4：parameters, 2：width
        CalcDimension heightDimen =
            CalcDimension(values[i * 4 + 3], static_cast<DimensionUnit>(units[i * 4 + 3])); //4：parameters, 3：height
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    RadioModelNG::SetResponseRegion(frameNode, region);
}

void ResetRadioResponseRegion(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
    region.emplace_back(dimenRect);
    RadioModelNG::SetResponseRegion(frameNode, region);
}

ArkUI_Bool GetRadioChecked(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(RadioModelNG::GetChecked(frameNode));
}

void GetRadioStyle(ArkUINodeHandle node, ArkUIRadioStyleOption* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    options->checkedBackgroundColor = RadioModelNG::GetCheckedBackgroundColor(frameNode).GetValue();
    options->uncheckedBorderColor = RadioModelNG::GetUncheckedBorderColor(frameNode).GetValue();
    options->indicatorColor = RadioModelNG::GetIndicatorColor(frameNode).GetValue();
}

void SetRadioValue(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetRadioValue(frameNode, std::string(value));
}

void ResetRadioValue(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetRadioValue(frameNode, "");
}

ArkUI_CharPtr GetSetRadioValue(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_radioStrValue = RadioModelNG::GetRadioValue(frameNode);
    return g_radioStrValue.c_str();
}

void SetRadioGroup(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetRadioGroup(frameNode, std::string(value));
}

void ResetRadioGroup(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetRadioGroup(frameNode, "");
}

ArkUI_CharPtr GetRadioGroup(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_radioStrValue = RadioModelNG::GetRadioGroup(frameNode);
    return g_radioStrValue.c_str();
}

void SetRadioOptions(ArkUINodeHandle node, ArkUI_CharPtr value, ArkUI_CharPtr group, ArkUI_Uint32 indicatorType)
{
    if (value == nullptr || group == nullptr) {
        return;
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (static_cast<RadioIndicatorType>(indicatorType) != RadioIndicatorType::TICK &&
        static_cast<RadioIndicatorType>(indicatorType) != RadioIndicatorType::DOT &&
        static_cast<RadioIndicatorType>(indicatorType) != RadioIndicatorType::CUSTOM) {
            indicatorType = static_cast<ArkUI_Uint32>(RadioIndicatorType::TICK);
    }
    RadioModelNG::SetRadioOptions(frameNode, std::string(value), std::string(group), indicatorType);
}
} // namespace

namespace NodeModifier {
const ArkUIRadioModifier* GetRadioModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIRadioModifier modifier = {
        SetRadioChecked,
        ResetRadioChecked,
        SetRadioStyle,
        ResetRadioStyle,
        SetRadioWidth,
        ResetRadioWidth,
        SetRadioHeight,
        ResetRadioHeight,
        SetRadioSize,
        ResetRadioSize,
        SetRadioHoverEffect,
        ResetRadioHoverEffect,
        SetRadioPadding,
        ResetRadioPadding,
        SetRadioResponseRegion,
        ResetRadioResponseRegion,
        GetRadioChecked,
        GetRadioStyle,
        SetRadioValue,
        ResetRadioValue,
        GetSetRadioValue,
        SetRadioGroup,
        ResetRadioGroup,
        GetRadioGroup,
        SetRadioOptions,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}

const CJUIRadioModifier* GetCJUIRadioModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIRadioModifier modifier = {
        SetRadioChecked,
        ResetRadioChecked,
        SetRadioStyle,
        ResetRadioStyle,
        SetRadioWidth,
        ResetRadioWidth,
        SetRadioHeight,
        ResetRadioHeight,
        SetRadioSize,
        ResetRadioSize,
        SetRadioHoverEffect,
        ResetRadioHoverEffect,
        SetRadioPadding,
        ResetRadioPadding,
        SetRadioResponseRegion,
        ResetRadioResponseRegion,
        GetRadioChecked,
        GetRadioStyle,
        SetRadioValue,
        ResetRadioValue,
        GetSetRadioValue,
        SetRadioGroup,
        ResetRadioGroup,
        GetRadioGroup,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}

void SetOnRadioChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [node, extraParam](const bool value) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_RADIO_CHANGE;
        event.componentAsyncEvent.data[0].i32 = static_cast<int>(value);
        SendArkUISyncEvent(&event);
    };
    RadioModelNG::SetOnChange(frameNode, std::move(onChange));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
