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

#include "core/components_ng/pattern/picker/datepicker_column_layout_algorithm.h"
#include <cstdint>

#include "core/components/dialog/dialog_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_utils.h"
#include "core/components_ng/pattern/picker/datepicker_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t DIVIDER_SIZE = 2;
const float ITEM_HEIGHT_HALF = 2.0f;
const int32_t BUFFER_NODE_NUMBER = 2;
const int32_t HIDENODE = 3;
constexpr double PERCENT_100 = 100.0;
constexpr double PERCENT_120 = 1.2f;
constexpr double SPACE_CALC_TIME = 2.0;
constexpr Dimension LUNARSWITCH_HEIGHT = 48.0_vp;
GradientColor CreatePercentGradientColor(float percent, Color color)
{
    NG::GradientColor gredient = GradientColor(color);
    gredient.SetDimension(CalcDimension(percent * PERCENT_100, DimensionUnit::PERCENT));
    return gredient;
}
} // namespace
void DatePickerColumnLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    SizeF frameSize = { -1.0f, -1.0f };

    uint32_t showCount_ = pickerTheme->GetShowCountPortrait() + BUFFER_NODE_NUMBER;
    if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount_ = pickerTheme->GetShowCountLandscape() + BUFFER_NODE_NUMBER;
    }

    auto columnNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(columnNode);
    auto blendNode = DynamicCast<FrameNode>(columnNode->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto pickerNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(pickerNode);
    auto layoutConstraint = blendNode->GetLayoutProperty()->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto width = layoutConstraint->parentIdealSize.Width();
    float pickerWidth = 0.0f;
    if (width.has_value()) {
        pickerWidth = width.value();
    } else {
        pickerWidth = static_cast<float>((pickerTheme->GetDividerSpacing() * DIVIDER_SIZE).ConvertToPx());
    }
    auto datePickerPattern = pickerNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    if (datePickerPattern->GetIsUserSetDividerSpacingFont()) {
        dividerSpacingFontScale_ = ReCalcItemHeightScale(datePickerPattern->GetDividerSpacing());
    }

    if (datePickerPattern->GetIsUserSetGradientFont()) {
        gradientFontScale_ = ReCalcItemHeightScale(datePickerPattern->GetGradientHeight(), false);
    }
    auto height = static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx() * gradientFontScale_ *
         (showCount_ - HIDENODE) + pickerTheme->GetDividerSpacing().ConvertToPx() * dividerSpacingFontScale_);

    auto pickerMaxHeight = layoutConstraint->maxSize.Height();
    if (datePickerPattern->GetIsShowInDialog()) {
        float dialogTitleHeight = static_cast<float>(
            (buttonTheme->GetHeight() + dialogTheme->GetButtonSpacingVertical() * SPACE_CALC_TIME).ConvertToPx());
        float dialogButtonHeight = static_cast<float>(
            (buttonTheme->GetHeight() + dialogTheme->GetButtonPaddingBottom() * SPACE_CALC_TIME).ConvertToPx());
        pickerMaxHeight -= (dialogTitleHeight + dialogButtonHeight);
        if (datePickerPattern->GetShowLunarSwitch()) {
            pickerMaxHeight -= static_cast<float>(LUNARSWITCH_HEIGHT.ConvertToPx());
        }
        auto gradientHeight = pickerTheme->GetGradientHeight().ConvertToPx() * gradientFontScale_;
        auto dividerSpacingHeight = pickerTheme->GetDividerSpacing().ConvertToPx() * dividerSpacingFontScale_;
        datePickerPattern->SetPaintDividerSpacing(dividerSpacingFontScale_);
        auto columnHeight = gradientHeight * (showCount_ - 1) + dividerSpacingHeight;
        datePickerPattern->SetResizePickerItemHeight(
            dividerSpacingHeight / columnHeight * std::min(height, pickerMaxHeight));
        datePickerPattern->SetResizeFlag(true);
    }

    pickerItemHeight_ = std::min(height, pickerMaxHeight);
    frameSize.SetWidth(pickerWidth);
    frameSize.SetHeight(std::min(height, pickerMaxHeight));
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
    auto layoutChildConstraint = blendNode->GetLayoutProperty()->CreateChildConstraint();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutChildConstraint);
    }
    MeasureText(layoutWrapper, frameSize);
    auto gradientPercent = static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx()) *
        gradientFontScale_ / frameSize.Height();
    InitGradient(gradientPercent, blendNode, columnNode);
}

void DatePickerColumnLayoutAlgorithm::InitGradient(const float& gradientPercent, const RefPtr<FrameNode> blendNode,
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

void DatePickerColumnLayoutAlgorithm::MeasureText(LayoutWrapper* layoutWrapper, const SizeF& size)
{
    auto totalChild = layoutWrapper->GetTotalChildCount();
    for (int32_t index = 0; index < totalChild; index++) {
        auto child = layoutWrapper->GetOrCreateChildByIndex(index);
        ChangeTextStyle(index, totalChild, size, child, layoutWrapper);
    }
}

void DatePickerColumnLayoutAlgorithm::ChangeTextStyle(uint32_t index, uint32_t showOptionCount, const SizeF& size,
    const RefPtr<LayoutWrapper>& childLayoutWrapper, LayoutWrapper* layoutWrapper)
{
    SizeF frameSize = { -1.0f, -1.0f };
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    frameSize.SetWidth(size.Width());
    auto layoutChildConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.
    if (index == selectedIndex) {
        frameSize.SetHeight(static_cast<float>(pickerTheme->GetDividerSpacing().ConvertToPx() *
            dividerSpacingFontScale_));
    } else {
        frameSize.SetHeight(static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx() *
            gradientFontScale_));
    }
    layoutChildConstraint.selfIdealSize = { frameSize.Width(), frameSize.Height() };
    childLayoutWrapper->Measure(layoutChildConstraint);
}

void DatePickerColumnLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto layoutProperty = AceType::DynamicCast<DataPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto size = geometryNode->GetFrameSize();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);

    auto children = layoutWrapper->GetAllChildrenWithBuild();
    int32_t halfCount = layoutWrapper->GetTotalChildCount() / 2;
    float childStartCoordinate = static_cast<float>(pickerItemHeight_ / ITEM_HEIGHT_HALF -
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

bool DatePickerColumnLayoutAlgorithm::NeedAdaptForAging()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);

    if (GreatOrEqual(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale())) {
        return true;
    }
    return false;
}

const Dimension DatePickerColumnLayoutAlgorithm::AdjustFontSizeScale(const Dimension& fontSizeValue, double fontScale)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);

    double adjustedScale = std::clamp(fontScale, pickerTheme->GetNormalFontScale(),
        pickerTheme->GetMaxTwoFontScale());
    Dimension result = 0.0_vp;
    if (!NearZero(fontScale)) {
        result = fontSizeValue / fontScale * adjustedScale;
    }
    return result;
}

float DatePickerColumnLayoutAlgorithm::ReCalcItemHeightScale(const Dimension& userSetHeight, bool isDividerSpacing)
{
    auto fontScale = 1.0f;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontScale);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontScale);
    auto systemFontScale = static_cast<double>(pipeline->GetFontScale());
    auto themePadding = pickerTheme->GetPickerDialogFontPadding();
    auto userSetHeightValue = AdjustFontSizeScale(userSetHeight, systemFontScale).ConvertToPx();
    double adjustedScale =
        std::clamp(systemFontScale, pickerTheme->GetNormalFontScale(), pickerTheme->GetMaxTwoFontScale());
    if (NearZero(adjustedScale)) {
        return fontScale;
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
        return fontScale;
    }

    fontScale = std::max(static_cast<float>(userSetHeightValue / themeHeight.ConvertToPx()), fontScale);
    return fontScale;
}

} // namespace OHOS::Ace::NG
