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

#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_utils.h"
#include "core/components_ng/pattern/picker/datepicker_layout_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t DIVIDER_SIZE = 2;
} // namespace
void DatePickerColumnLayoutAlgorithm::Measure(FrameNode* frameNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    SizeF frameSize = { -1.0f, -1.0f };

    auto height = static_cast<float>(
        pickerTheme->GetGradientHeight().ConvertToPx() * 4 + pickerTheme->GetDividerSpacing().ConvertToPx());

    auto layoutConstraint = frameNode->GetLayoutProperty()->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto width = layoutConstraint->parentIdealSize.Width();
    float pickerWidth = 0.0f;
    if (width.has_value()) {
        pickerWidth = width.value();
    } else {
        pickerWidth = static_cast<float>((pickerTheme->GetDividerSpacing() * DIVIDER_SIZE).ConvertToPx());
    }
    frameSize.SetWidth(pickerWidth);
    frameSize.SetHeight(height);
    frameNode->GetGeometryNode()->SetFrameSize(frameSize);
    auto layoutChildConstraint = frameNode->GetLayoutProperty()->CreateChildConstraint();
    for (auto&& child : frameNode->GetAllFrameNodeChildren()) {
        child->Measure(layoutChildConstraint);
    }
    MeasureText(frameNode, frameSize);
}

void DatePickerColumnLayoutAlgorithm::MeasureText(FrameNode* frameNode, const SizeF& size)
{
    auto totalChild = frameNode->TotalChildCount();
    for (int32_t index = 0; index < totalChild; index++) {
        auto child = frameNode->GetFrameNodeByIndex(index);
        ChangeTextStyle(index, totalChild, size, child, frameNode);
    }
}

void DatePickerColumnLayoutAlgorithm::ChangeTextStyle(uint32_t index, uint32_t showOptionCount, const SizeF& size,
    const RefPtr<FrameNode>& child, FrameNode* frameNode)
{
    SizeF frameSize = { -1.0f, -1.0f };
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    frameSize.SetWidth(size.Width());
    auto layoutChildConstraint = frameNode->GetLayoutProperty()->CreateChildConstraint();
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.
    if (index == selectedIndex) {
        frameSize.SetHeight(static_cast<float>(pickerTheme->GetDividerSpacing().ConvertToPx()));
    } else {
        frameSize.SetHeight(static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx()));
    }
    layoutChildConstraint.selfIdealSize = { frameSize.Width(), frameSize.Height() };
    frameNode->Measure(layoutChildConstraint);
}

void DatePickerColumnLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    auto layoutProperty = AceType::DynamicCast<DataPickerLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto size = geometryNode->GetFrameSize();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);

    auto children = frameNode->GetAllFrameNodeChildren();

    float childStartCoordinate = 0.0;
    for (const auto& child : children) {
        auto childGeometryNode = child->GetGeometryNode();
        auto childSize = childGeometryNode->GetMarginFrameSize();
        auto childOffset =
            OffsetF(0.0f, childStartCoordinate + static_cast<float>(currentOffset_) + padding.Offset().GetY());
        childGeometryNode->SetMarginFrameOffset(childOffset);
        child->Layout();
        childStartCoordinate += childSize.Height();
    }
}

} // namespace OHOS::Ace::NG
