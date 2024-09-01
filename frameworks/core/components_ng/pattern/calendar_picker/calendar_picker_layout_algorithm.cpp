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

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CHILDREN_SIZE = 5;
} // namespace
void CalendarPickerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CalendarPickerContentMeasure(layoutWrapper);
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

    auto defaultTopMargin = theme->GetEntryDateTopBottomMargin();
    auto defaultLeftMargin = theme->GetEntryDateLeftRightMargin();
    PaddingProperty currentPadding;
    if (contentLayoutProperty->GetPaddingProperty() != nullptr) {
        currentPadding = *(contentLayoutProperty->GetPaddingProperty());
    }

    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
    }
    float widthTotal = 0.0f;
    float height = 0.0f;
    for (int32_t i = 0; i < CHILDREN_SIZE; i++) {
        auto textWrapper = contentWrapper->GetOrCreateChildByIndex(i);
        CHECK_NULL_VOID(textWrapper);
        contentLayoutProperty->UpdateContentConstraint();
        textWrapper->Measure(std::nullopt);
        auto textGeometryNode = textWrapper->GetGeometryNode();
        CHECK_NULL_VOID(textGeometryNode);
        widthTotal += textGeometryNode->GetFrameSize().Width();
        height = std::max(height, textGeometryNode->GetFrameSize().Height());
    }
    widthTotal += currentPadding.left.value_or(CalcLength(defaultLeftMargin)).GetDimension().ConvertToPx();
    widthTotal += currentPadding.right.value_or(CalcLength(defaultLeftMargin)).GetDimension().ConvertToPx();
    height += currentPadding.top.value_or(CalcLength(defaultTopMargin)).GetDimension().ConvertToPx();
    height += currentPadding.bottom.value_or(CalcLength(defaultTopMargin)).GetDimension().ConvertToPx();

    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(contentLayoutProperty);
    CHECK_NULL_VOID(linearLayoutProperty);

    auto Idealwidth = constraint->selfIdealSize.Width().value_or(0);
    if (widthTotal < Idealwidth - theme->GetEntryButtonWidth().ConvertToPx()) {
        widthTotal = Idealwidth - theme->GetEntryButtonWidth().ConvertToPx();
        linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    } else {
        linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    }
    height = std::max(height, constraint->selfIdealSize.Height().value_or(0));

    contentMeasure_ = SizeF(widthTotal, height);
    contentGeometryNode->SetFrameSize(contentMeasure_);
}

void CalendarPickerLayoutAlgorithm::SelfMeasure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<CalendarPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    BorderWidthProperty currentBorderWidth;
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        currentBorderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        currentBorderWidth.SetBorderWidth(theme->GetEntryBorderWidth());
    }

    auto width = contentMeasure_.Width() + theme->GetEntryButtonWidth().ConvertToPx();
    width += currentBorderWidth.topDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    width += currentBorderWidth.bottomDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    auto height = contentMeasure_.Height();

    if (layoutProperty->HasAspectRatio() && layoutProperty->GetAspectRatio() != 0) {
        height = width / layoutProperty->GetAspectRatio();
    } else {
        height += currentBorderWidth.leftDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
        height += currentBorderWidth.rightDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    }
    SizeF idealSize(width, height);
    geometryNode->SetFrameSize(idealSize);

    auto flexWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(flexWrapper);
    auto flexLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(flexWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(flexLayoutProperty);
    auto flexGeometryNode = flexWrapper->GetGeometryNode();
    CHECK_NULL_VOID(flexGeometryNode);

    auto flexHeight = height - currentBorderWidth.leftDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    flexHeight -= currentBorderWidth.rightDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    CalcSize flexCalcSize((CalcLength(theme->GetEntryButtonWidth().ConvertToPx())), CalcLength(flexHeight));
    flexLayoutProperty->UpdateUserDefinedIdealSize(flexCalcSize);
    auto flexLayoutConstraint = layoutProperty->CreateChildConstraint();
    flexWrapper->Measure(flexLayoutConstraint);
    flexMeasure_ = SizeF(theme->GetEntryButtonWidth().ConvertToPx(), flexHeight);
    flexGeometryNode->SetFrameSize(flexMeasure_);

    for (int32_t i = 0; i < flexWrapper->GetTotalChildCount(); i++) {
        auto child = flexWrapper->GetChildByIndex(i);
        CHECK_NULL_VOID(child);
        auto childGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(childGeometryNode);
        SizeF childMeasure = SizeF(theme->GetEntryButtonWidth().ConvertToPx(), flexHeight / 2);
        childGeometryNode->SetFrameSize(childMeasure);
    }
}
} // namespace OHOS::Ace::NG
