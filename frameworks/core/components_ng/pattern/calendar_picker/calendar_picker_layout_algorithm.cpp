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

bool IsMatchParent(const RefPtr<CalendarPickerLayoutProperty>& layoutProperty, const bool isWidth)
{
    CHECK_NULL_RETURN(layoutProperty, false);
    auto layoutPolicyProperty = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_RETURN(layoutPolicyProperty.has_value(), false);
    LayoutCalPolicy layoutPolicy = isWidth ?
        layoutPolicyProperty.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH) :
        layoutPolicyProperty.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
    return layoutPolicy == LayoutCalPolicy::MATCH_PARENT;
}

void CalculateTotalSize(const RefPtr<CalendarTheme>& theme, const RefPtr<LayoutWrapper>& contentWrapper,
    const RefPtr<CalendarPickerLayoutProperty>& layoutProperty, SizeF& totalSize)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(contentWrapper);
    CHECK_NULL_VOID(layoutProperty);
    auto contentLayoutProperty = contentWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty);

    float totalWidth = 0.0f;
    float totalHeight = 0.0f;
    for (int32_t i = 0; i < CHILDREN_SIZE; i++) {
        auto textWrapper = contentWrapper->GetOrCreateChildByIndex(i);
        CHECK_NULL_VOID(textWrapper);
        contentLayoutProperty->UpdateContentConstraint();
        textWrapper->Measure(std::nullopt);
        auto textGeometryNode = textWrapper->GetGeometryNode();
        CHECK_NULL_VOID(textGeometryNode);
        totalWidth += textGeometryNode->GetFrameSize().Width();
        totalHeight = std::max(totalHeight, textGeometryNode->GetFrameSize().Height());
    }

    if (contentLayoutProperty->GetPaddingProperty() != nullptr) {
        auto defaultTopMargin = theme->GetEntryDateTopBottomMargin();
        auto defaultLeftMargin = theme->GetEntryDateLeftRightMargin();
        PaddingProperty currentPadding = *(contentLayoutProperty->GetPaddingProperty());
        totalWidth += currentPadding.left.value_or(CalcLength(defaultLeftMargin)).GetDimension().ConvertToPx();
        totalWidth += currentPadding.right.value_or(CalcLength(defaultLeftMargin)).GetDimension().ConvertToPx();
        totalHeight += currentPadding.top.value_or(CalcLength(defaultTopMargin)).GetDimension().ConvertToPx();
        totalHeight += currentPadding.bottom.value_or(CalcLength(defaultTopMargin)).GetDimension().ConvertToPx();
    }

    BorderWidthProperty currentBorderWidth;
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        currentBorderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        currentBorderWidth.SetBorderWidth(theme->GetEntryBorderWidth());
    }
    totalWidth = totalWidth + currentBorderWidth.leftDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx() +
        currentBorderWidth.rightDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    totalHeight = totalHeight + currentBorderWidth.topDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx() +
        currentBorderWidth.bottomDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();

    totalWidth += theme->GetEntryButtonWidth().ConvertToPx();
    totalSize = SizeF(totalWidth, totalHeight);
}

void CalculateContentSize(const RefPtr<CalendarTheme>& theme,
    const RefPtr<CalendarPickerLayoutProperty>& layoutProperty, const SizeF& totalSize, SizeF& contentMeasure)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(layoutProperty);

    BorderWidthProperty currentBorderWidth;
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        currentBorderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        currentBorderWidth.SetBorderWidth(theme->GetEntryBorderWidth());
    }
    auto contentWidth = totalSize.Width() - theme->GetEntryButtonWidth().ConvertToPx() -
        currentBorderWidth.leftDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx() -
        currentBorderWidth.rightDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();
    auto contentHeight = totalSize.Height() -
        currentBorderWidth.topDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx() -
        currentBorderWidth.bottomDimen.value_or(theme->GetEntryBorderWidth()).ConvertToPx();

    contentMeasure = SizeF(contentWidth, contentHeight);
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

    SizeF totalSize = SizeF(0.0f, 0.0f);
    CalculateTotalSize(theme, contentWrapper, layoutProperty, totalSize);

    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(contentLayoutProperty);
    CHECK_NULL_VOID(linearLayoutProperty);

    SizeF policySize = {constraint->selfIdealSize.Width().value_or(0), constraint->selfIdealSize.Height().value_or(0)};
    UpdateFrameSizeWithLayoutPolicy(layoutWrapper, policySize);

    if (LessNotEqual(totalSize.Width(), policySize.Width()) || IsMatchParent(layoutProperty, true)) {
        totalSize.SetWidth(policySize.Width());
        linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    } else {
        linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    }

    if (LessNotEqual(totalSize.Height(), policySize.Height()) || IsMatchParent(layoutProperty, false)) {
        totalSize.SetHeight(policySize.Height());
    }

    CalculateContentSize(theme, layoutProperty, totalSize, contentMeasure_);
    contentGeometryNode->SetFrameSize(contentMeasure_);

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(SizeF(totalSize.Width(), totalSize.Height()));
}

void CalendarPickerLayoutAlgorithm::SelfMeasure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<CalendarPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);

    auto flexWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(flexWrapper);
    auto flexLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(flexWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(flexLayoutProperty);
    auto flexGeometryNode = flexWrapper->GetGeometryNode();
    CHECK_NULL_VOID(flexGeometryNode);

    auto flexHeight = contentMeasure_.Height();
    auto flexWidth = theme->GetEntryButtonWidth().ConvertToPx();
    flexLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(flexWidth), CalcLength(flexHeight)));
    auto flexLayoutConstraint = layoutProperty->CreateChildConstraint();
    flexWrapper->Measure(flexLayoutConstraint);
    flexMeasure_ = SizeF(flexWidth, flexHeight);
    flexGeometryNode->SetFrameSize(flexMeasure_);

    for (int32_t i = 0; i < flexWrapper->GetTotalChildCount(); i++) {
        auto child = flexWrapper->GetChildByIndex(i);
        CHECK_NULL_VOID(child);
        auto childGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(childGeometryNode);
        SizeF childMeasure = SizeF(flexWidth, flexHeight / 2);
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

    LayoutCalPolicy widthLayoutPolicy =
        layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
    LayoutCalPolicy heightLayoutPolicy =
        layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
    if (widthLayoutPolicy == LayoutCalPolicy::MATCH_PARENT) {
        auto width = layoutConstraint->parentIdealSize.Width().value_or(0);
        frameSize.SetWidth(width);
    }

    if (heightLayoutPolicy == LayoutCalPolicy::MATCH_PARENT) {
        auto height = layoutConstraint->parentIdealSize.Height().value_or(0);
        frameSize.SetHeight(height);
    }
}

} // namespace OHOS::Ace::NG
