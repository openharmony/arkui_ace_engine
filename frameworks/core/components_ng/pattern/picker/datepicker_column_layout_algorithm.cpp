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
const int32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const float ITEM_HEIGHT_HALF = 2.0f;
} // namespace
void DatePickerColumnLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    SizeF frameSize = { -1.0f, -1.0f };

    uint32_t showCount_ = pickerTheme->GetShowOptionCount();
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE &&
        SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount_ = OPTION_COUNT_PHONE_LANDSCAPE;
    }
    auto height = static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx() * (showCount_ - 1) +
                                     pickerTheme->GetDividerSpacing().ConvertToPx());
    auto columnNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(columnNode);
    auto stackNode = DynamicCast<FrameNode>(columnNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto pickerNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(pickerNode);
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
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
    auto pickerMaxHeight = layoutConstraint->maxSize.Height();
    if (datePickerPattern->GetIsShowInDialog()) {
        float dialogTitleHeight =
            static_cast<float>((pickerTheme->GetTitleStyle().GetFontSize() + dialogTheme->GetDividerHeight() +
                                pickerTheme->GetContentMarginVertical() * 2)
                                   .ConvertToPx());
        float dialogButtonHeight =
            static_cast<float>((pickerTheme->GetButtonHeight() + dialogTheme->GetDividerHeight() +
                                dialogTheme->GetDividerPadding().Bottom() + pickerTheme->GetContentMarginVertical() * 2)
                                   .ConvertToPx());
        pickerMaxHeight -= (dialogTitleHeight + dialogButtonHeight);
        auto gradientHeight = pickerTheme->GetGradientHeight().ConvertToPx();
        auto dividerSpacingHeight = pickerTheme->GetDividerSpacing().ConvertToPx();
        auto columnHeight = gradientHeight * (showCount_ - 1) + dividerSpacingHeight;
        datePickerPattern->SetResizePickerItemHeight(
            dividerSpacingHeight / columnHeight * std::min(height, pickerMaxHeight));
        datePickerPattern->SetResizeFlag(true);
    }

    pickerItemHeight_ = std::min(height, pickerMaxHeight);
    frameSize.SetWidth(pickerWidth);
    frameSize.SetHeight(std::min(height, pickerMaxHeight));
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
    auto layoutChildConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutChildConstraint);
    }
    MeasureText(layoutWrapper, frameSize);
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
        frameSize.SetHeight(static_cast<float>(pickerTheme->GetDividerSpacing().ConvertToPx()));
    } else {
        frameSize.SetHeight(static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx()));
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
    uint32_t halfCount = layoutWrapper->GetTotalChildCount() / 2;
    float childStartCoordinate = static_cast<float>(pickerItemHeight_ / ITEM_HEIGHT_HALF -
                                                    pickerTheme->GetGradientHeight().ConvertToPx() * halfCount -
                                                    pickerTheme->GetDividerSpacing().ConvertToPx() / ITEM_HEIGHT_HALF);
    uint32_t i = 0;
    uint32_t showCount = pickerTheme->GetShowOptionCount();
    for (const auto& child : children) {
        if (i >= showCount) {
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

} // namespace OHOS::Ace::NG
