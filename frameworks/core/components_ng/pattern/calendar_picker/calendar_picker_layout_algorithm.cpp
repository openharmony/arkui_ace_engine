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

#include "core/components_ng/pattern/calendar_picker/calendar_picker_layout_algorithm.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CHILDREN_SIZE = 5;
constexpr int32_t DOUBLE = 2;
} // namespace
void CalendarPickerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CalendarPickerContentMeasure(layoutWrapper);
    CalendarPickerFlexMeasure(layoutWrapper);

    SelfMeasure(layoutWrapper);
}

void CalendarPickerLayoutAlgorithm::CalendarPickerContentMeasure(LayoutWrapper* layoutWrapper)
{
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(contentWrapper);
    auto contentLayoutProperty = contentWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty);
    auto layoutProperty = AceType::DynamicCast<CalendarPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto constraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto contentGeometryNode = contentWrapper->GetGeometryNode();
    CHECK_NULL_VOID(contentGeometryNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    auto topMargin = theme->GetEntryDateTopBottomMargin();
    topMargin += theme->GetEntryBorderWidth() * DOUBLE;
    auto leftMargin = theme->GetEntryDateLeftRightMargin();
    float widthTotal = 0.0f;
    float height = 0.0f;
    for (int32_t i = 0; i < CHILDREN_SIZE; i++) {
        auto textWrapper = contentWrapper->GetOrCreateChildByIndex(i);
        CHECK_NULL_VOID(textWrapper);
        contentLayoutProperty->UpdateContentConstraint();
        auto textLayoutConstraint = contentLayoutProperty->CreateChildConstraint();
        textWrapper->Measure(textLayoutConstraint);
        auto textGeometryNode = textWrapper->GetGeometryNode();
        CHECK_NULL_VOID(textGeometryNode);
        widthTotal += textGeometryNode->GetFrameSize().Width();
        height = std::max(height, textGeometryNode->GetFrameSize().Height());
    }
    widthTotal += leftMargin.ConvertToPx() * 2;
    height += topMargin.ConvertToPx() * 2;

    auto Idealwidth = constraint->selfIdealSize.Width().value_or(0);
    auto idealHeight = constraint->selfIdealSize.Height().value_or(0);
    if (widthTotal < Idealwidth - theme->GetEntryButtonWidth().ConvertToPx()) {
        widthTotal = Idealwidth - theme->GetEntryButtonWidth().ConvertToPx();
    }
    if (height < idealHeight) {
        height = idealHeight;
    }

    auto contentLayoutConstraint = layoutProperty->CreateChildConstraint();
    CalcSize cancelButtonCalcSize((CalcLength(widthTotal)), CalcLength(height));
    contentLayoutProperty->UpdateUserDefinedIdealSize(cancelButtonCalcSize);
    contentWrapper->Measure(contentLayoutConstraint);
    contentMeasure_ = SizeF(widthTotal, height);
    contentGeometryNode->SetFrameSize(contentMeasure_);
    contentGeometryNode->SetContentSize(contentMeasure_);
}

void CalendarPickerLayoutAlgorithm::CalendarPickerFlexMeasure(LayoutWrapper* layoutWrapper)
{
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(contentWrapper);
    auto layoutProperty = AceType::DynamicCast<CalendarPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto flexLayoutProperty = AceType::DynamicCast<FlexLayoutProperty>(contentWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(flexLayoutProperty);
    auto contentGeometryNode = contentWrapper->GetGeometryNode();
    CHECK_NULL_VOID(contentGeometryNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    flexLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(theme->GetEntryButtonWidth()), CalcLength(contentMeasure_.Height())));

    auto contentLayoutConstraint = layoutProperty->CreateChildConstraint();
    contentWrapper->Measure(contentLayoutConstraint);
    flexMeasure_ = contentGeometryNode->GetFrameSize();
}

void CalendarPickerLayoutAlgorithm::SelfMeasure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<CalendarPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    SizeF idealSize(contentMeasure_.Width() + flexMeasure_.Width(), flexMeasure_.Height());
    geometryNode->SetFrameSize(idealSize);
    geometryNode->SetContentSize(idealSize);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(idealSize.Width()), CalcLength(idealSize.Height())));
}
} // namespace OHOS::Ace::NG
