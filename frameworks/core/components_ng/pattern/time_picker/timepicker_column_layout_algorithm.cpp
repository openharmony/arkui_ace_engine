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

#include "core/components_ng/pattern/time_picker/timepicker_column_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DIVIDER_SIZE = 2;
constexpr float ITEM_HEIGHT_HALF = 2.0f;
constexpr int32_t BUFFER_NODE_NUMBER = 2;
constexpr int32_t HIDENODE = 3;
constexpr double PERCENT_100 = 100.0f;
constexpr double PERCENT_120 = 1.2f;
constexpr double SPACE_CALC_TIME = 2.0;
constexpr Dimension LUNARSWITCH_HEIGHT = 48.0_vp;
constexpr float DEFAULT_FONT_SCALE = 1.f;

GradientColor CreatePercentGradientColor(float percent, Color color)
{
    NG::GradientColor gredient = GradientColor(color);
    gredient.SetDimension(CalcDimension(percent * PERCENT_100, DimensionUnit::PERCENT));
    return gredient;
}
} // namespace

void TimePickerColumnLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto columnNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(columnNode);
    auto blendNode = DynamicCast<FrameNode>(columnNode->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto pickerNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(pickerNode);
    auto timePickerPattern = pickerNode->GetPattern<TimePickerRowPattern>();
    SizeF frameSize = { -1.0f, -1.0f };

    uint32_t showCount = pickerTheme->GetShowCountPortrait() + BUFFER_NODE_NUMBER;
    if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount = pickerTheme->GetShowCountLandscape() + BUFFER_NODE_NUMBER;
    }

    if (timePickerPattern->GetIsUserSetDividerSpacingFont()) {
        dividerSpacingFontScale_ = ReCalcItemHeightScale(timePickerPattern->GetDividerSpacing());
    }

    if (timePickerPattern->GetIsUserSetGradientFont()) {
        gradientFontScale_ = ReCalcItemHeightScale(timePickerPattern->GetGradientHeight(), false);
    }
    auto height = static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx() * gradientFontScale_ *
        (showCount - HIDENODE) + pickerTheme->GetDividerSpacing().ConvertToPx() * dividerSpacingFontScale_);
    timePickerPattern->SetPaintDividerSpacing(dividerSpacingFontScale_);
    auto layoutConstraint = blendNode->GetLayoutProperty()->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto width = layoutConstraint->parentIdealSize.Width();
    auto pickerMaxHeight = GetPickerMaxHeight(layoutConstraint, pickerNode);
    float pickerWidth = static_cast<float>((pickerTheme->GetDividerSpacing() * DIVIDER_SIZE).ConvertToPx());
    if (width.has_value()) {
        pickerWidth = width.value();
    }

    pickerItemHeight_ = std::min(height, pickerMaxHeight);
    frameSize.SetWidth(pickerWidth);
    frameSize.SetHeight(std::min(height, pickerMaxHeight));
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
    MeasureText(layoutWrapper, pickerTheme, frameSize);
    auto gradientPercent = static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx() *
        gradientFontScale_) / frameSize.Height();
    InitGradient(gradientPercent, blendNode, columnNode);
}

float TimePickerColumnLayoutAlgorithm::GetPickerMaxHeight(
    const std::optional<LayoutConstraintF>& layoutConstraint, const RefPtr<FrameNode>& pickerNode)
{
    auto pickerMaxHeight = layoutConstraint->maxSize.Height();
    
    auto pipeline = pickerNode->GetContext();
    CHECK_NULL_RETURN(pipeline, pickerMaxHeight);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, pickerMaxHeight);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, pickerMaxHeight);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_RETURN(buttonTheme, pickerMaxHeight);

    auto timePickerPattern = pickerNode->GetPattern<TimePickerRowPattern>();
    if (timePickerPattern->GetIsShowInDialog()) {
        float dialogTitleHeight = static_cast<float>(
            (buttonTheme->GetHeight() + dialogTheme->GetButtonSpacingVertical() * SPACE_CALC_TIME).ConvertToPx());
        float dialogButtonHeight = static_cast<float>(
            (buttonTheme->GetHeight() + dialogTheme->GetButtonPaddingBottom() * SPACE_CALC_TIME).ConvertToPx());
        pickerMaxHeight -= (dialogTitleHeight + dialogButtonHeight);
        if (timePickerPattern->GetShowLunarSwitch()) {
            pickerMaxHeight -= static_cast<float>(LUNARSWITCH_HEIGHT.ConvertToPx());
        }
    }
    return pickerMaxHeight;
}

void TimePickerColumnLayoutAlgorithm::InitGradient(const float& gradientPercent, const RefPtr<FrameNode> blendNode,
    const RefPtr<FrameNode> columnNode)
{
    auto blendRenderContext = blendNode->GetRenderContext();
    auto columnRenderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(blendRenderContext);
    CHECK_NULL_VOID(columnRenderContext);

    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    gradient.AddColor(CreatePercentGradientColor(0, Color::TRANSPARENT));
    gradient.AddColor(CreatePercentGradientColor(gradientPercent, Color::WHITE));
    gradient.AddColor(CreatePercentGradientColor(1 - gradientPercent, Color::WHITE));
    gradient.AddColor(CreatePercentGradientColor(1, Color::TRANSPARENT));

    columnRenderContext->UpdateBackBlendMode(BlendMode::SRC_IN);
    columnRenderContext->UpdateBackBlendApplyType(BlendApplyType::OFFSCREEN);
    blendRenderContext->UpdateLinearGradient(gradient);
    blendRenderContext->UpdateBackBlendMode(BlendMode::SRC_OVER);
    blendRenderContext->UpdateBackBlendApplyType(BlendApplyType::OFFSCREEN);
}

void TimePickerColumnLayoutAlgorithm::MeasureText(LayoutWrapper* layoutWrapper, const SizeF& size)
{
    auto totalChild = layoutWrapper->GetTotalChildCount();
    for (int32_t index = 0; index < totalChild; index++) {
        auto child = layoutWrapper->GetOrCreateChildByIndex(index);
        ChangeAmPmTextStyle(index, totalChild, size, child, layoutWrapper);
    }
}

void TimePickerColumnLayoutAlgorithm::ChangeAmPmTextStyle(uint32_t index, uint32_t showOptionCount, const SizeF& size,
    const RefPtr<LayoutWrapper>& childLayoutWrapper, LayoutWrapper* layoutWrapper)
{
    SizeF frameSize = { -1.0f, -1.0f };
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    frameSize.SetWidth(size.Width());
    auto layoutChildConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.
    if (index == selectedIndex) {
        frameSize.SetHeight(
            static_cast<float>(pickerTheme->GetDividerSpacing().ConvertToPx() * dividerSpacingFontScale_));
    } else {
        frameSize.SetHeight(static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx() * gradientFontScale_));
    }
    layoutChildConstraint.selfIdealSize = { frameSize.Width(), frameSize.Height() };
    childLayoutWrapper->Measure(layoutChildConstraint);
}

void TimePickerColumnLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto layoutProperty = AceType::DynamicCast<LinearLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto size = geometryNode->GetFrameSize();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    uint32_t halfCount = static_cast<uint32_t>(layoutWrapper->GetTotalChildCount() / 2);
    float childStartCoordinate = static_cast<float>(
        pickerItemHeight_ / ITEM_HEIGHT_HALF -
        pickerTheme->GetGradientHeight().ConvertToPx() * gradientFontScale_ * halfCount -
        pickerTheme->GetDividerSpacing().ConvertToPx() * dividerSpacingFontScale_ / ITEM_HEIGHT_HALF);
    uint32_t i = 0;
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    for (const auto& child : children) {
        if (i >= showCount || i >= currentOffset_.size()) {
            break;
        }
        auto childGeometryNode = child->GetGeometryNode();
        auto childSize = childGeometryNode->GetMarginFrameSize();
        auto childOffset =
            OffsetF(0.0f, childStartCoordinate + static_cast<float>(currentOffset_[i++]) + padding.Offset().GetY());
        childGeometryNode->SetMarginFrameOffset(childOffset);
        child->Layout();
        childStartCoordinate += childSize.Height();
    }
}

bool TimePickerColumnLayoutAlgorithm::NeedAdaptForAging()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);

    return GreatOrEqual(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale());
}

const Dimension TimePickerColumnLayoutAlgorithm::AdjustFontSizeScale(const Dimension& fontSizeValue, double fontScale)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);

    double adjustedScale = std::clamp(fontScale, pickerTheme->GetNormalFontScale(), pickerTheme->GetMaxTwoFontScale());
    auto result = 0.0_vp;
    if (!NearZero(fontScale)) {
        result =  fontSizeValue / fontScale * adjustedScale;
    }
    return result;
}

float TimePickerColumnLayoutAlgorithm::ReCalcItemHeightScale(const Dimension& userSetHeight, bool isDividerSpacing)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, DEFAULT_FONT_SCALE);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, DEFAULT_FONT_SCALE);

    auto systemFontScale = static_cast<double>(pipeline->GetFontScale());
    auto themePadding = pickerTheme->GetPickerDialogFontPadding();
    auto userSetHeightValue = AdjustFontSizeScale(userSetHeight, systemFontScale).ConvertToPx();
    double adjustedScale =
        std::clamp(systemFontScale, pickerTheme->GetNormalFontScale(), pickerTheme->GetMaxTwoFontScale());
    if (NearZero(adjustedScale)) {
        return DEFAULT_FONT_SCALE;
    }
    userSetHeightValue = userSetHeightValue / adjustedScale * PERCENT_120 + (themePadding.ConvertToPx() * DIVIDER_SIZE);
    auto themeHeightLimit =
        isDividerSpacing ? pickerTheme->GetDividerSpacingLimit() : pickerTheme->GetGradientHeightLimit();
    auto themeHeight = isDividerSpacing ? pickerTheme->GetDividerSpacing() : pickerTheme->GetGradientHeight();
    if (GreatOrEqualCustomPrecision(userSetHeightValue, themeHeightLimit.ConvertToPx())) {
        userSetHeightValue = themeHeightLimit.ConvertToPx();
    } else {
        userSetHeightValue = std::max(userSetHeightValue, themeHeight.ConvertToPx());
    }

    if (NearZero(themeHeight.ConvertToPx())) {
        return DEFAULT_FONT_SCALE;
    }

    return std::max(static_cast<float>(userSetHeightValue / themeHeight.ConvertToPx()), DEFAULT_FONT_SCALE);
}

void TimePickerColumnLayoutAlgorithm::MeasureText(LayoutWrapper* layoutWrapper, const RefPtr<PickerTheme>& pickerTheme,
    const SizeF& size)
{
    auto totalChild = layoutWrapper->GetTotalChildCount();
    CHECK_EQUAL_VOID(totalChild, 0);

    auto selectedIndex = totalChild / 2;
    auto layoutChildConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    const float dividerHeight = static_cast<float>(pickerTheme->GetDividerSpacing().ConvertToPx() * \
        dividerSpacingFontScale_);
    const float gradientHeight = static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx() * \
        gradientFontScale_);

    for (auto index = 0; index < totalChild; index++) {
        auto child = layoutWrapper->GetOrCreateChildByIndex(index);
        SizeF frameSize = { size.Width(), -1.0f };
        if (index == selectedIndex) {
            frameSize.SetHeight(dividerHeight);
        } else {
            frameSize.SetHeight(gradientHeight);
        }
        layoutChildConstraint.selfIdealSize = { frameSize.Width(), frameSize.Height() };
        child->Measure(layoutChildConstraint);
    }
}

} // namespace OHOS::Ace::NG
