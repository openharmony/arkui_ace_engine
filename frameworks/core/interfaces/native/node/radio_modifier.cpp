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

#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/common/layout/constants.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"

namespace OHOS::Ace::NG {
constexpr bool DEFAULT_CHECKED = false;
void SetRadioChecked(NodeHandle node, bool isCheck)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetChecked(frameNode, isCheck);
}

void ResetRadioChecked(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetChecked(frameNode, DEFAULT_CHECKED);
}

void SetRadioStyle(NodeHandle node,
    uint32_t checkedBackgroundColor, uint32_t uncheckedBorderColor, uint32_t indicatorColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    RadioModelNG::SetCheckedBackgroundColor(frameNode, Color(checkedBackgroundColor));
    RadioModelNG::SetUncheckedBorderColor(frameNode, Color(uncheckedBorderColor));
    RadioModelNG::SetIndicatorColor(frameNode, Color(indicatorColor));
}

void ResetRadioStyle(NodeHandle node)
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

void SetRadioWidth(NodeHandle node, double value, uint32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    RadioModelNG::SetWidth(frameNode, width);
}

void ResetRadioWidth(NodeHandle node)
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
    RadioModelNG::SetWidth(frameNode, width);
}

void SetRadioHeight(NodeHandle node, double value, uint32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension height = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    RadioModelNG::SetHeight(frameNode, height);
}

void ResetRadioHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    auto defaultHeight = radioTheme->GetDefaultHeight();
    auto verticalPadding = radioTheme->GetHotZoneVerticalPadding();
    auto height = defaultHeight - verticalPadding * 2; //2 is Calculate the parameters of the formula
    RadioModelNG::SetHeight(frameNode, height);
}

void SetRadioSize(NodeHandle node, double widthValue, int32_t widthUnit, double heightValue, int32_t heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetWidth(
        frameNode, Dimension(widthValue, static_cast<OHOS::Ace::DimensionUnit>(widthUnit)));
    RadioModelNG::SetHeight(
        frameNode, Dimension(heightValue, static_cast<OHOS::Ace::DimensionUnit>(heightUnit)));
}

void ResetRadioSize(NodeHandle node)
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

void SetRadioHoverEffect(NodeHandle node, int32_t hoverEffectValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::HoverEffectType hoverEffect = OHOS::Ace::HoverEffectType::AUTO;
    hoverEffect = static_cast<OHOS::Ace::HoverEffectType>(hoverEffectValue);
    RadioModelNG::SetHoverEffect(frameNode, hoverEffect);
}

void ResetRadioHoverEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RadioModelNG::SetHoverEffect(frameNode, OHOS::Ace::HoverEffectType::AUTO);
}

void SetRadioPadding(NodeHandle node, const struct ArkUISizeType *top, const struct ArkUISizeType *right,
    const struct ArkUISizeType *bottom, const struct ArkUISizeType *left)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
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

void ResetRadioPadding(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.bottom = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.left = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.right = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    RadioModelNG::SetPadding(frameNode, paddings);
}

void SetRadioResponseRegion(NodeHandle node, const double* values, const int32_t* units, uint32_t length)
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

void ResetRadioResponseRegion(NodeHandle node)
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

ArkUIRadioModifierAPI GetRadioModifier()
{
    static const ArkUIRadioModifierAPI modifier = {SetRadioChecked, ResetRadioChecked, SetRadioStyle, ResetRadioStyle,
        SetRadioWidth, ResetRadioWidth, SetRadioHeight, ResetRadioHeight, SetRadioSize, ResetRadioSize,
        SetRadioHoverEffect, ResetRadioHoverEffect, SetRadioPadding, ResetRadioPadding, SetRadioResponseRegion,
        ResetRadioResponseRegion};

    return modifier;
}
}