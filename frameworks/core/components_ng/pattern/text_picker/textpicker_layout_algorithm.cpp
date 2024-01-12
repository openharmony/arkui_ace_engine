/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_picker/textpicker_layout_algorithm.h"

#include "core/components/dialog/dialog_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
const int32_t DIVIDER_SIZE = 2;
const int32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const float PICKER_HEIGHT_HALF = 3.5f;
const float ITEM_HEIGHT_HALF = 2.0f;
const int32_t MAX_HALF_DISPLAY_COUNT = 2;
const int32_t BUFFER_NODE_NUMBER = 2;
constexpr double PERCENT_100 = 100.0;

GradientColor CreatePercentGradientColor(float percent, Color color)
{
    NG::GradientColor gredient = GradientColor(color);
    gredient.SetDimension(CalcDimension(percent * PERCENT_100, DimensionUnit::PERCENT));
    return gredient;
}
} // namespace
void TextPickerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    SizeF frameSize = { -1.0f, -1.0f };

    float pickerHeight = 0.0f;
    auto columnNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(columnNode);
    auto stackNode = DynamicCast<FrameNode>(columnNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto pickerNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(pickerNode);
    auto layoutProperty = pickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    isDefaultPickerItemHeight_ = layoutProperty->HasDefaultPickerItemHeight();
    if (isDefaultPickerItemHeight_) {
        auto defaultPickerItemHeightValue = layoutProperty->GetDefaultPickerItemHeightValue();
        if (LessOrEqual(defaultPickerItemHeightValue.Value(), 0.0)) {
            isDefaultPickerItemHeight_ = false;
        }
    }

    uint32_t showCount_ = pickerTheme->GetShowOptionCount();
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE &&
        SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount_ = OPTION_COUNT_PHONE_LANDSCAPE;
    }

    if (isDefaultPickerItemHeight_) {
        pickerHeight = static_cast<float>(defaultPickerItemHeight_ * showCount_);
    } else {
        pickerHeight = static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx() * (showCount_ - 1) +
                                          pickerTheme->GetDividerSpacing().ConvertToPx());
    }

    auto layoutConstraint = pickerNode->GetLayoutProperty()->GetLayoutConstraint();
    float pickerWidth = static_cast<float>((pickerTheme->GetDividerSpacing() * DIVIDER_SIZE).ConvertToPx());

    auto textPickerPattern = pickerNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    if (textPickerPattern->GetIsShowInDialog() && isDefaultPickerItemHeight_) {
        float dialogButtonHeight =
            static_cast<float>((pickerTheme->GetButtonHeight() + dialogTheme->GetDividerHeight() +
                                dialogTheme->GetDividerPadding().Bottom() + pickerTheme->GetContentMarginVertical() * 2)
                                .ConvertToPx());
        pickerHeight = std::min(pickerHeight, layoutConstraint->maxSize.Height() - dialogButtonHeight);
        if (!NearZero(showCount_)) {
            defaultPickerItemHeight_ = pickerHeight / showCount_;
        }
        textPickerPattern->SetResizePickerItemHeight(defaultPickerItemHeight_);
        textPickerPattern->SetResizeFlag(true);
    }

    frameSize.SetWidth(pickerWidth);
    frameSize.SetHeight(pickerHeight);
    textPickerPattern->CheckAndUpdateColumnSize(frameSize);
    pickerItemHeight_ = frameSize.Height();
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
    auto layoutChildConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutChildConstraint);
    }
    MeasureText(layoutWrapper, frameSize);
    auto gradientPercent = static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx()) / frameSize.Height();
    InitGradient(gradientPercent, stackNode, columnNode);
}

void TextPickerLayoutAlgorithm::InitGradient(const float& gradientPercent, const RefPtr<FrameNode> stackNode,
    const RefPtr<FrameNode> columnNode)
{
    auto stackRenderContext = stackNode->GetRenderContext();
    auto columnRenderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(stackRenderContext);
    CHECK_NULL_VOID(columnRenderContext);
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    gradient.AddColor(CreatePercentGradientColor(0, Color::TRANSPARENT));
    gradient.AddColor(CreatePercentGradientColor(gradientPercent, Color::WHITE));
    gradient.AddColor(CreatePercentGradientColor(1 - gradientPercent, Color::WHITE));
    gradient.AddColor(CreatePercentGradientColor(1, Color::TRANSPARENT));

    columnRenderContext->UpdateBackBlendMode(BlendMode::SRC_IN);
    columnRenderContext->UpdateBackBlendApplyType(BlendApplyType::OFFSCREEN);
    stackRenderContext->UpdateLinearGradient(gradient);
    stackRenderContext->UpdateBackBlendMode(BlendMode::SRC_OVER);
    stackRenderContext->UpdateBackBlendApplyType(BlendApplyType::OFFSCREEN);
}

void TextPickerLayoutAlgorithm::MeasureText(LayoutWrapper* layoutWrapper, const SizeF& size)
{
    auto totalChild = layoutWrapper->GetTotalChildCount();
    for (int32_t index = 0; index < totalChild; index++) {
        auto child = layoutWrapper->GetOrCreateChildByIndex(index);
        ChangeTextStyle(index, totalChild, size, child, layoutWrapper);
    }
}

void TextPickerLayoutAlgorithm::ChangeTextStyle(uint32_t index, uint32_t showOptionCount, const SizeF& size,
    const RefPtr<LayoutWrapper>& childLayoutWrapper, LayoutWrapper* layoutWrapper)
{
    SizeF frameSize = { -1.0f, -1.0f };
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    frameSize.SetWidth(size.Width());
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.
    auto layoutChildConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    if (isDefaultPickerItemHeight_) {
        frameSize.SetHeight(static_cast<float>(defaultPickerItemHeight_));
    } else {
        if (index == selectedIndex) {
            frameSize.SetHeight(static_cast<float>(pickerTheme->GetDividerSpacing().ConvertToPx()));
        } else {
            frameSize.SetHeight(static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx()));
        }
    }
    layoutChildConstraint.selfIdealSize = { frameSize.Width(), frameSize.Height() };
    childLayoutWrapper->Measure(layoutChildConstraint);
}

void TextPickerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
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
    float childStartCoordinate = 0.0f;

    if (isDefaultPickerItemHeight_) {
        childStartCoordinate +=
            static_cast<float>(size.Height() / ITEM_HEIGHT_HALF - defaultPickerItemHeight_ * PICKER_HEIGHT_HALF);
        halfDisplayCounts_ =
            std::clamp(static_cast<int32_t>(
                           std::ceil((size.Height() / ITEM_HEIGHT_HALF - defaultPickerItemHeight_ / ITEM_HEIGHT_HALF) /
                                     defaultPickerItemHeight_)),
                0, MAX_HALF_DISPLAY_COUNT);
    } else {
        childStartCoordinate += static_cast<float>(pickerItemHeight_ / ITEM_HEIGHT_HALF -
                                    pickerTheme->GetGradientHeight().ConvertToPx() * (ITEM_HEIGHT_HALF + 1) -
                                    pickerTheme->GetDividerSpacing().ConvertToPx() / ITEM_HEIGHT_HALF);
        halfDisplayCounts_ = std::clamp(
            static_cast<int32_t>(std::ceil((pickerItemHeight_ / ITEM_HEIGHT_HALF -
                                               pickerTheme->GetDividerSpacing().ConvertToPx() / ITEM_HEIGHT_HALF) /
                                           pickerTheme->GetGradientHeight().ConvertToPx())),
            0, MAX_HALF_DISPLAY_COUNT);
    }
    int32_t i = 0;
    int32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    for (const auto& child : children) {
        if (i >= showCount) {
            break;
        }
        auto childGeometryNode = child->GetGeometryNode();
        auto childSize = childGeometryNode->GetMarginFrameSize();
        auto childOffset =
            OffsetF(0.0, childStartCoordinate + static_cast<float>(currentOffset_[i++]) + padding.Offset().GetY());
        childGeometryNode->SetMarginFrameOffset(childOffset);
        child->Layout();
        childStartCoordinate += childSize.Height();
    }
}

} // namespace OHOS::Ace::NG
