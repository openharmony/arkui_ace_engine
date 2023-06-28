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

#include "core/components_ng/pattern/counter/counter_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components/counter/counter_theme.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SUB_BUTTON = 0;
constexpr int32_t CONTENT = 1;
constexpr int32_t ADD_BUTTON = 2;
constexpr int32_t SUB_TEXT = 0;
constexpr int32_t ADD_TEXT = 0;
} // namespace

void CounterLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // counter measure
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto frameWidthMax = ((constraint->selfIdealSize.Width().has_value())
                              ? std::min(constraint->selfIdealSize.Width().value(), constraint->maxSize.Width())
                              : std::min(constraint->percentReference.Width(), constraint->maxSize.Width()));
    frameSize.SetWidth(frameWidthMax);
    frameSize.SetHeight(constraint->selfIdealSize.Height().value_or(constraint->maxSize.Height()));
    geometryNode->SetFrameSize(frameSize);
    const auto& padding = layoutProperty->CreatePaddingWithoutBorder();
    auto widthMax = ((constraint->selfIdealSize.Width().has_value())
                            ? std::min(constraint->selfIdealSize.Width().value(), constraint->maxSize.Width())
                            : std::min(constraint->percentReference.Width(), constraint->maxSize.Width())) -
                    padding.left.value_or(0) - padding.right.value_or(0);
    auto heightMax = ((constraint->selfIdealSize.Height().has_value())
                             ? std::min(constraint->selfIdealSize.Height().value(), constraint->maxSize.Height())
                             : std::min(constraint->percentReference.Height(), constraint->maxSize.Height())) -
                     padding.top.value_or(0) - padding.bottom.value_or(0);
    geometryNode->SetContentSize(SizeF(widthMax, heightMax));
    // sub button measure
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto counterTheme = pipeline->GetTheme<CounterTheme>();
    CHECK_NULL_VOID(counterTheme);
    auto buttonWidth = counterTheme->GetControlWidth().ConvertToPx();
    auto subButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(SUB_BUTTON);
    CHECK_NULL_VOID(subButtonWrapper);
    auto subButtonGeometryNode = subButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(subButtonGeometryNode);
    auto subButtonLayoutProperty = subButtonWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(subButtonLayoutProperty);
    CalcSize subButtonSize;
    subButtonSize.SetWidth(CalcLength(buttonWidth));
    subButtonSize.SetHeight(CalcLength(heightMax));
    subButtonLayoutProperty->UpdateUserDefinedIdealSize(subButtonSize);
    auto subButtonTextWrapper = subButtonWrapper->GetOrCreateChildByIndex(SUB_TEXT);
    CHECK_NULL_VOID(subButtonTextWrapper);
    auto subButtonTextLayoutProperty = subButtonTextWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(subButtonTextLayoutProperty);
    subButtonTextLayoutProperty->UpdateUserDefinedIdealSize(subButtonSize);
    auto layoutConstraint = layoutProperty->CreateChildConstraint();
    subButtonWrapper->Measure(layoutConstraint);

    // content measure
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(CONTENT);
    CHECK_NULL_VOID(contentWrapper);
    auto contentGeometryNode = contentWrapper->GetGeometryNode();
    CHECK_NULL_VOID(contentGeometryNode);
    auto contentLayoutProperty = contentWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty);
    CalcSize contentSize;
    contentSize.SetWidth(CalcLength(widthMax - 2 * buttonWidth));
    contentSize.SetHeight(CalcLength(heightMax));
    contentLayoutProperty->UpdateUserDefinedIdealSize(contentSize);
    contentWrapper->Measure(layoutConstraint);

    // add button measure
    auto addButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(ADD_BUTTON);
    CHECK_NULL_VOID(addButtonWrapper);
    auto addButtonGeometryNode = addButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(addButtonGeometryNode);
    auto addButtonLayoutProperty = addButtonWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(addButtonLayoutProperty);
    CalcSize addButtonSize;
    addButtonSize.SetWidth(CalcLength(buttonWidth));
    addButtonSize.SetHeight(CalcLength(heightMax));
    auto addButtonTextWrapper = addButtonWrapper->GetOrCreateChildByIndex(ADD_TEXT);
    CHECK_NULL_VOID(addButtonTextWrapper);
    auto addButtonTextLayoutProperty = addButtonTextWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(addButtonTextLayoutProperty);
    addButtonTextLayoutProperty->UpdateUserDefinedIdealSize(addButtonSize);
    addButtonLayoutProperty->UpdateUserDefinedIdealSize(addButtonSize);
    addButtonWrapper->Measure(layoutConstraint);
}

void CounterLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    // layout sub button
    auto subButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(SUB_BUTTON);
    CHECK_NULL_VOID(subButtonWrapper);
    auto subButtonGeometryNode = subButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(subButtonGeometryNode);
    auto subButtonSize = subButtonGeometryNode->GetFrameSize();
    auto subButtonFrameWidth = subButtonSize.Width();
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& padding = layoutProperty->CreatePaddingWithoutBorder();
    OffsetF subButtonOffset(padding.left.value_or(0), padding.top.value_or(0));
    subButtonGeometryNode->SetMarginFrameOffset(subButtonOffset);
    subButtonWrapper->Layout();

    // layout content
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(CONTENT);
    CHECK_NULL_VOID(contentWrapper);
    auto contentGeometryNode = contentWrapper->GetGeometryNode();
    CHECK_NULL_VOID(contentGeometryNode);
    auto contentSize = contentGeometryNode->GetFrameSize();
    auto contentFrameWidth = contentSize.Width();
    auto contentHorizontalOffset = subButtonGeometryNode->GetFrameOffset().GetX() + subButtonFrameWidth;
    auto contentVerticalOffset = subButtonGeometryNode->GetFrameOffset().GetY();
    OffsetF contentOffset(contentHorizontalOffset, contentVerticalOffset);
    contentGeometryNode->SetMarginFrameOffset(contentOffset);
    contentWrapper->Layout();

    // layout add button
    auto addButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(ADD_BUTTON);
    CHECK_NULL_VOID(addButtonWrapper);
    auto addButtonGeometryNode = addButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(addButtonGeometryNode);
    auto addButtonHorizontalOffset =
        subButtonGeometryNode->GetFrameOffset().GetX() + subButtonFrameWidth + contentFrameWidth;
    auto addButtonVerticalOffset = subButtonGeometryNode->GetFrameOffset().GetY();
    OffsetF addButtonOffset(addButtonHorizontalOffset, addButtonVerticalOffset);
    addButtonGeometryNode->SetMarginFrameOffset(addButtonOffset);
    addButtonWrapper->Layout();
}
} // namespace OHOS::Ace::NG
