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

void CalculateContentSize(const RefPtr<CalendarTheme>& theme, const RefPtr<LayoutWrapper>& contentWrapper,
    SizeF& contentSize)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(contentWrapper);
    auto contentLayoutProperty = contentWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty);

    float contentWidth = 0.0f;
    float contentHeight = 0.0f;
    for (int32_t i = 0; i < CHILDREN_SIZE; i++) {
        auto textWrapper = contentWrapper->GetOrCreateChildByIndex(i);
        CHECK_NULL_VOID(textWrapper);
        contentLayoutProperty->UpdateContentConstraint();
        textWrapper->Measure(std::nullopt);
        auto textGeometryNode = textWrapper->GetGeometryNode();
        CHECK_NULL_VOID(textGeometryNode);
        contentWidth += textGeometryNode->GetFrameSize().Width();
        contentHeight = std::max(contentHeight, textGeometryNode->GetFrameSize().Height());
    }

    if (contentLayoutProperty->GetPaddingProperty() != nullptr) {
        auto defaultTopMargin = theme->GetEntryDateTopBottomMargin();
        auto defaultLeftMargin = theme->GetEntryDateLeftRightMargin();
        PaddingProperty currentPadding = *(contentLayoutProperty->GetPaddingProperty());
        contentWidth += currentPadding.left.value_or(CalcLength(defaultLeftMargin)).GetDimension().ConvertToPx();
        contentWidth += currentPadding.right.value_or(CalcLength(defaultLeftMargin)).GetDimension().ConvertToPx();
        contentHeight += currentPadding.top.value_or(CalcLength(defaultTopMargin)).GetDimension().ConvertToPx();
        contentHeight += currentPadding.bottom.value_or(CalcLength(defaultTopMargin)).GetDimension().ConvertToPx();
    }
    contentSize = SizeF(contentWidth, contentHeight);
}

void UpdateContentSizeWithLayoutPolicy(const RefPtr<CalendarTheme>& theme, LayoutWrapper* layoutWrapper,
    SizeF& contentSize)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<CalendarPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value());
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint.has_value());

    BorderWidthProperty currentBorderWidth;
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        currentBorderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        currentBorderWidth.SetBorderWidth(theme->GetEntryBorderWidth());
    }

    if (layoutPolicy->IsWidthMatch()) {
        auto contentWidth = layoutConstraint->parentIdealSize.Width().value_or(0) -
            theme->GetEntryButtonWidth().ConvertToPx() -
            currentBorderWidth.topDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx() -
            currentBorderWidth.bottomDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
        contentSize.SetWidth(contentWidth);
    } else if (layoutPolicy->IsWidthWrap() || layoutPolicy->IsWidthFix()) {
        const auto& calcConstraint = layoutProperty->GetCalcLayoutConstraint();
        if (calcConstraint && calcConstraint->maxSize->Width().has_value()) {
            float contentWidth = contentSize.Width();
            float maxWidth = layoutConstraint->maxSize.Width() - theme->GetEntryButtonWidth().ConvertToPx() -
                currentBorderWidth.topDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx() -
                currentBorderWidth.bottomDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
            contentSize.SetWidth(std::min(contentWidth, maxWidth));
        }
    }

    if (layoutPolicy->IsHeightMatch()) {
        auto contentHeight = layoutConstraint->parentIdealSize.Height().value_or(0) -
            currentBorderWidth.leftDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx() -
            currentBorderWidth.rightDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
        contentSize.SetHeight(contentHeight);
    } else if (layoutPolicy->IsHeightWrap() || layoutPolicy->IsHeightFix()) {
        const auto& calcConstraint = layoutProperty->GetCalcLayoutConstraint();
        if (calcConstraint && calcConstraint->maxSize->Height().has_value()) {
            float contentHeight = contentSize.Height();
            float maxHeight = layoutConstraint->maxSize.Height() -
                currentBorderWidth.leftDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx() -
                currentBorderWidth.rightDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
            contentSize.SetHeight(std::min(contentHeight, maxHeight));
        }
    }
}

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
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
    }

    SizeF contentSize = SizeF(0.0f, 0.0f);
    CalculateContentSize(theme, contentWrapper, contentSize);

    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(contentLayoutProperty);
    CHECK_NULL_VOID(linearLayoutProperty);

    SizeF policySize = {constraint->selfIdealSize.Width().value_or(0), constraint->selfIdealSize.Height().value_or(0)};
    UpdateFrameSizeWithLayoutPolicy(layoutWrapper, policySize);
    if (LessNotEqual(contentSize.Width(), policySize.Width() - theme->GetEntryButtonWidth().ConvertToPx())) {
        contentSize.SetWidth(policySize.Width() - theme->GetEntryButtonWidth().ConvertToPx());
        linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    } else {
        linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    }

    if (LessNotEqual(contentSize.Height(), policySize.Height())) {
        contentSize.SetHeight(policySize.Height());
    }

    contentMeasure_ = contentSize;
    UpdateContentSizeWithLayoutPolicy(theme, layoutWrapper, contentMeasure_);
    contentGeometryNode->SetFrameSize(contentMeasure_);
}

void CalendarPickerLayoutAlgorithm::SelfMeasure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<CalendarPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    BorderWidthProperty currentBorderWidth;
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        currentBorderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        currentBorderWidth.SetBorderWidth(theme->GetEntryBorderWidth());
    }

    auto totalWidth = contentMeasure_.Width() + theme->GetEntryButtonWidth().ConvertToPx();
    totalWidth += currentBorderWidth.topDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    totalWidth += currentBorderWidth.bottomDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    auto totalHeight = contentMeasure_.Height();

    if (layoutProperty->HasAspectRatio() && layoutProperty->GetAspectRatio() != 0) {
        totalHeight = totalWidth / layoutProperty->GetAspectRatio();
    } else {
        totalHeight += currentBorderWidth.leftDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
        totalHeight += currentBorderWidth.rightDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    }

    geometryNode->SetFrameSize(SizeF(totalWidth, totalHeight));

    auto flexWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(flexWrapper);
    auto flexLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(flexWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(flexLayoutProperty);
    auto flexGeometryNode = flexWrapper->GetGeometryNode();
    CHECK_NULL_VOID(flexGeometryNode);

    auto flexHeight = totalHeight - currentBorderWidth.leftDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    flexHeight -= currentBorderWidth.rightDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    CalcSize flexCalcSize(CalcLength(theme->GetEntryButtonWidth().ConvertToPx()), CalcLength(flexHeight));
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

void CalendarPickerLayoutAlgorithm::UpdateFrameSizeWithLayoutPolicy(LayoutWrapper* layoutWrapper, SizeF& frameSize)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<CalendarPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value());
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint.has_value());

    if (layoutPolicy->IsWidthMatch()) {
        auto width = layoutConstraint->parentIdealSize.Width().value_or(0);
        frameSize.SetWidth(width);
    }

    if (layoutPolicy->IsHeightMatch()) {
        auto height = layoutConstraint->parentIdealSize.Height().value_or(0);
        frameSize.SetHeight(height);
    }
}

} // namespace OHOS::Ace::NG
