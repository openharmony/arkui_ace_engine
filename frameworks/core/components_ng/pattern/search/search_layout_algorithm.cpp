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

#include "core/components_ng/pattern/search/search_layout_algorithm.h"

#include "core/components/search/search_theme.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t IMAGE_INDEX = 1;
constexpr int32_t CANCEL_IMAGE_INDEX = 2;
constexpr int32_t CANCEL_BUTTON_INDEX = 3;
constexpr int32_t BUTTON_INDEX = 4;
constexpr int32_t BUTTON_TEXT_INDEX = 0;
} // namespace

void SearchLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.empty()) {
        LOGW("Search has no child node.");
        return;
    }
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto constraint = layoutProperty->GetLayoutConstraint();

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    auto iconHeight = searchTheme->GetIconHeight().ConvertToPx();

    if (!constraint->selfIdealSize.Height().has_value()) {
        auto height = searchTheme->GetHeight().ConvertToPx();
        constraint->selfIdealSize.SetHeight(height);
    }

    auto idealSize = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
    if (GreaterOrEqualToInfinity(idealSize.Width()) || GreaterOrEqualToInfinity(idealSize.Height())) {
        LOGW("Size is infinity.");
        geometryNode->SetFrameSize(SizeF());
        return;
    }
    geometryNode->SetFrameSize(idealSize);
    geometryNode->SetContentSize(idealSize);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = OptionalSizeF(idealSize);

    // First measure the Button for TextField needs to determine its size based on the size of the Button
    auto buttonWrapper = layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
    CHECK_NULL_VOID(buttonWrapper);
    auto textWrapper = buttonWrapper->GetOrCreateChildByIndex(BUTTON_TEXT_INDEX);
    CHECK_NULL_VOID(textWrapper);

    auto searchButton = layoutProperty->GetSearchButton();
    if (searchButton.has_value() && !searchButton.value()->empty()) {
        auto textLayoutProperty = DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(searchButton->value());
        textLayoutProperty->UpdateMaxLines(1);
        PaddingProperty padding;
        padding.left = CalcLength(searchTheme->GetSearchButtonTextPadding());
        padding.right = CalcLength(searchTheme->GetSearchButtonTextPadding());
        textLayoutProperty->UpdatePadding(padding);
        auto buttonLayoutConstraint = childLayoutConstraint;
        auto buttonHeight =
            searchTheme->GetHeight().ConvertToPx() - 2 * searchTheme->GetSearchButtonSpace().ConvertToPx();
        auto buttonLayoutProperty = DynamicCast<ButtonLayoutProperty>(buttonWrapper->GetLayoutProperty());
        CalcSize buttonCalcSize;
        buttonCalcSize.SetHeight(CalcLength(buttonHeight));
        buttonLayoutProperty->UpdateUserDefinedIdealSize(buttonCalcSize);
        buttonWrapper->Measure(buttonLayoutConstraint);
    } else {
        auto buttonLayoutProperty = DynamicCast<ButtonLayoutProperty>(buttonWrapper->GetLayoutProperty());
        CalcSize buttonCalcSize(CalcLength(0.0), CalcLength(0.0));
        buttonLayoutProperty->UpdateUserDefinedIdealSize(buttonCalcSize);
        auto buttonLayoutConstraint = childLayoutConstraint;
        buttonWrapper->Measure(buttonLayoutConstraint);
    }

    // Measure Image
    auto imageLayoutConstraint = childLayoutConstraint;
    auto imageWrapper = layoutWrapper->GetOrCreateChildByIndex(IMAGE_INDEX);
    CHECK_NULL_VOID(imageWrapper);
    imageWrapper->Measure(imageLayoutConstraint);

    // Measure CancelButton and CancelImage
    auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textFieldWrapper);
    auto textLayoutProperty = DynamicCast<TextFieldLayoutProperty>(textFieldWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto cancelButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButtonWrapper);
    auto cancelImageWrapper = layoutWrapper->GetOrCreateChildByIndex(CANCEL_IMAGE_INDEX);
    CHECK_NULL_VOID(cancelImageWrapper);
    if (textLayoutProperty->HasValue() && !textLayoutProperty->GetValue()->empty()) {
        auto cancelButtonHeight =
            searchTheme->GetHeight().ConvertToPx() - 2 * searchTheme->GetSearchButtonSpace().ConvertToPx();
        auto cancelButtonLayoutProperty = DynamicCast<ButtonLayoutProperty>(cancelButtonWrapper->GetLayoutProperty());
        CalcSize cancelButtonCalcSize((CalcLength(cancelButtonHeight)), CalcLength(cancelButtonHeight));
        cancelButtonLayoutProperty->UpdateUserDefinedIdealSize(cancelButtonCalcSize);
    } else {
        auto cancelButtonLayoutProperty = DynamicCast<ButtonLayoutProperty>(cancelButtonWrapper->GetLayoutProperty());
        CalcSize cancelButtonCalcSize(CalcLength(0.0), CalcLength(0.0));
        cancelButtonLayoutProperty->UpdateUserDefinedIdealSize(cancelButtonCalcSize);

        auto cancelImageLayoutProperty = DynamicCast<ImageLayoutProperty>(cancelImageWrapper->GetLayoutProperty());
        CalcSize cancelImageCalcSize(CalcLength(0.0), CalcLength(0.0));
        cancelImageLayoutProperty->UpdateUserDefinedIdealSize(cancelImageCalcSize);
    }
    auto cancelButtonLayoutConstraint = childLayoutConstraint;
    cancelButtonWrapper->Measure(cancelButtonLayoutConstraint);
    auto cancelImageLayoutConstraint = childLayoutConstraint;
    cancelImageWrapper->Measure(cancelImageLayoutConstraint);

    // Measure TextField
    auto textFieldLayoutConstraint = childLayoutConstraint;
    auto buttonWidth = buttonWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto cancelButtonWidth = cancelButtonWrapper->GetGeometryNode()->GetFrameSize().Width();
    float textFieldWidth = 0.0f;
    if (searchButton.has_value() && !searchButton.value()->empty()) {
        textFieldWidth = idealSize.Width() - searchTheme->GetSearchIconLeftSpace().ConvertToPx() - iconHeight -
                         searchTheme->GetSearchIconRightSpace().ConvertToPx() - cancelButtonWidth - buttonWidth -
                         searchTheme->GetSearchDividerWidth().ConvertToPx() -
                         2 * searchTheme->GetDividerSideSpace().ConvertToPx();
    } else {
        textFieldWidth = idealSize.Width() - searchTheme->GetSearchIconLeftSpace().ConvertToPx() - iconHeight -
                         searchTheme->GetSearchIconRightSpace().ConvertToPx() - cancelButtonWidth - buttonWidth;
    }
    auto textFieldHeight = idealSize.Height();
    textFieldLayoutConstraint.selfIdealSize = OptionalSizeF(textFieldWidth, textFieldHeight);
    textFieldWrapper->Measure(textFieldLayoutConstraint);
}

void SearchLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.empty()) {
        LOGW("Search has no child node.");
        return;
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto layoutProperty = DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    auto iconHeight = searchTheme->GetIconHeight().ConvertToPx();
    // Layout TextField
    auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textFieldWrapper);
    auto textFieldGeometryNode = textFieldWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);
    float textFieldHorizontalOffset = searchTheme->GetSearchIconLeftSpace().ConvertToPx() + iconHeight +
                                      searchTheme->GetSearchIconRightSpace().ConvertToPx();
    textFieldGeometryNode->SetMarginFrameOffset(OffsetF(textFieldHorizontalOffset, 0.0f));
    textFieldWrapper->Layout();

    // Layout Image
    auto searchSize = geometryNode->GetFrameSize();
    float imageHorizontalOffset = searchTheme->GetSearchIconLeftSpace().ConvertToPx();
    float imageVerticalOffset = (searchSize.Height() - iconHeight) / 2.0;
    OffsetF imageOffset(imageHorizontalOffset, imageVerticalOffset);
    auto imageWrapper = layoutWrapper->GetOrCreateChildByIndex(IMAGE_INDEX);
    CHECK_NULL_VOID(imageWrapper);
    auto imageGeometryNode = imageWrapper->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    imageGeometryNode->SetMarginFrameOffset(imageOffset);
    imageWrapper->Layout();

    // If SearchButton is set, layout SearchButton
    auto cancelButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButtonWrapper);
    auto cancelButtonGeometryNode = cancelButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(cancelButtonGeometryNode);
    auto cancelButtonFrameSize = cancelButtonGeometryNode->GetFrameSize();

    auto cancelImageWrapper = layoutWrapper->GetOrCreateChildByIndex(CANCEL_IMAGE_INDEX);
    CHECK_NULL_VOID(cancelImageWrapper);
    auto cancelImageGeometryNode = cancelImageWrapper->GetGeometryNode();
    CHECK_NULL_VOID(cancelImageGeometryNode);

    auto searchButton = layoutProperty->GetSearchButton();
    if (searchButton.has_value() && !searchButton.value()->empty()) {
        auto buttonWrapper = layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
        CHECK_NULL_VOID(buttonWrapper);
        auto buttonGeometryNode = buttonWrapper->GetGeometryNode();
        CHECK_NULL_VOID(buttonGeometryNode);
        auto buttonFrameSize = buttonGeometryNode->GetFrameSize();
        float buttonVerticalOffset = (searchSize.Height() - buttonFrameSize.Height()) / 2.0;
        float buttonHorizontalOffset =
            searchSize.Width() - buttonFrameSize.Width() - searchTheme->GetSearchButtonSpace().ConvertToPx();
        OffsetF buttonOffset;
        buttonOffset = OffsetF(buttonHorizontalOffset, buttonVerticalOffset);
        buttonGeometryNode->SetMarginFrameOffset(buttonOffset);
        buttonWrapper->Layout();
        // Layout CancelButton
        float cancelButtonVerticalOffset = (searchSize.Height() - cancelButtonFrameSize.Height()) / 2.0;
        auto cancelButtonOffsetToSearchButton = cancelButtonFrameSize.Width() +
                                                2 * searchTheme->GetDividerSideSpace().ConvertToPx() +
                                                searchTheme->GetSearchDividerWidth().ConvertToPx();
        OffsetF cancelButtonOffset = OffsetF(buttonOffset.GetX() - cancelButtonOffsetToSearchButton, 0.0);
        cancelButtonOffset += OffsetF(0.0, cancelButtonVerticalOffset);
        cancelButtonGeometryNode->SetMarginFrameOffset(cancelButtonOffset);
        cancelButtonWrapper->Layout();
        // Layout CancelImage
        float cancelImageVerticalOffset = (searchSize.Height() - iconHeight) / 2.0;
        auto cancelImageOffsetToSearchButton = iconHeight + 2 * searchTheme->GetDividerSideSpace().ConvertToPx() +
                                               searchTheme->GetSearchDividerWidth().ConvertToPx();
        auto cancelButtonImageCenterOffset = (cancelButtonFrameSize.Height() - iconHeight) / 2.0;
        OffsetF cancelImageOffset =
            OffsetF(buttonOffset.GetX() - cancelImageOffsetToSearchButton - cancelButtonImageCenterOffset, 0.0);
        cancelImageOffset += OffsetF(0.0, cancelImageVerticalOffset);
        cancelImageGeometryNode->SetMarginFrameOffset(cancelImageOffset);
        cancelImageWrapper->Layout();
    } else {
        // Layout CancelButton
        float cancelButtonVerticalOffset = (searchSize.Height() - cancelButtonFrameSize.Height()) / 2.0;
        float cancelButtonHorizontalOffset =
            searchSize.Width() - cancelButtonFrameSize.Width() - searchTheme->GetSearchButtonSpace().ConvertToPx();
        auto cancelButtonImageCenterOffset = (cancelButtonFrameSize.Height() - iconHeight) / 2.0;
        OffsetF cancelButtonOffset = OffsetF(cancelButtonHorizontalOffset, cancelButtonVerticalOffset);
        cancelButtonGeometryNode->SetMarginFrameOffset(cancelButtonOffset);
        cancelButtonWrapper->Layout();
        // Layout CancelImage
        float cancelImageVerticalOffset = (searchSize.Height() - iconHeight) / 2.0;
        float cancelImageHorizontalOffset = cancelButtonHorizontalOffset + cancelButtonImageCenterOffset;
        OffsetF cancelImageOffset = OffsetF(cancelImageHorizontalOffset, cancelImageVerticalOffset);
        cancelImageGeometryNode->SetMarginFrameOffset(cancelImageOffset);
        cancelImageWrapper->Layout();
    }
}

} // namespace OHOS::Ace::NG
