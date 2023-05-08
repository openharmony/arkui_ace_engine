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

#include <algorithm>

#include "core/components_ng/pattern/search/search_layout_algorithm.h"

#include "core/components/search/search_theme.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
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
constexpr int32_t MULTIPLE_2 = 2;

} // namespace

bool SearchLayoutAlgorithm::IsFixedHeightMode(FrameNode* frameNode)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);

    auto constraint = layoutProperty->GetLayoutConstraint();
    return constraint->selfIdealSize.Height().has_value();
}

void SearchLayoutAlgorithm::CancelImageMeasure(FrameNode* frameNode)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto cancelImage = frameNode->GetFrameNodeByIndex(CANCEL_IMAGE_INDEX);
    CHECK_NULL_VOID(cancelImage);
    auto cancelImageGeometryNode = cancelImage->GetGeometryNode();
    CHECK_NULL_VOID(cancelImageGeometryNode);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    cancelImage->Measure(childLayoutConstraint);
    cancelIconSizeMeasure_ = cancelImageGeometryNode->GetFrameSize();
}

void SearchLayoutAlgorithm::CancelButtonMeasure(FrameNode* frameNode)
{
    auto cancelButton = frameNode->GetFrameNodeByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButton);
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto cancelButtonLayoutProperty =
        AceType::DynamicCast<ButtonLayoutProperty>(cancelButton->GetLayoutProperty());
    CHECK_NULL_VOID(cancelButtonLayoutProperty);
    auto cancelButtonGeometryNode = cancelButton->GetGeometryNode();
    CHECK_NULL_VOID(cancelButtonGeometryNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);

    // calculate theme space from cancel button to cancel image
    auto spaceHeight = searchTheme->GetHeight().ConvertToPx() - 2 * searchTheme->GetSearchButtonSpace().ConvertToPx() -
        searchTheme->GetIconHeight().ConvertToPx();

    // calculate cancel button height
    auto cancelButtonHeight =
        layoutProperty->GetCancelButtonUDSizeValue(Dimension(cancelIconSizeMeasure_.Height())).ConvertToPx() +
        spaceHeight;

    CalcSize cancelButtonCalcSize((CalcLength(cancelButtonHeight)), CalcLength(cancelButtonHeight));
    cancelButtonLayoutProperty->UpdateUserDefinedIdealSize(cancelButtonCalcSize);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    cancelButton->Measure(childLayoutConstraint);
    cancelBtnSizeMeasure_ = cancelButtonGeometryNode->GetFrameSize();
}

void SearchLayoutAlgorithm::TextFieldMeasure(FrameNode* frameNode)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto textField = frameNode->GetFrameNodeByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textField);
    auto textFieldGeometryNode = textField->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);

    auto buttonWidth = searchButtonSizeMeasure_.Width();
    auto cancelButtonWidth = cancelBtnSizeMeasure_.Width();
    auto iconRenderWidth =
        layoutProperty->GetSearchIconUDSizeValue(Dimension(searchIconSizeMeasure_.Width())).ConvertToPx();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto searchWidthMax = (constraint->selfIdealSize.Width().has_value()) ?
        constraint->selfIdealSize.Width().value() : constraint->maxSize.Width();

    auto cancelButton = frameNode->GetFrameNodeByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButton);
    auto search = frameNode->GetFrameNodeByIndex(BUTTON_INDEX);
    CHECK_NULL_VOID(search);
    auto searchButtonEvent = search->GetEventHub<ButtonEventHub>();
    auto cancelButtonEvent = cancelButton->GetEventHub<ButtonEventHub>();

    auto textFieldWidth = searchWidthMax - searchTheme->GetSearchIconLeftSpace().ConvertToPx() - iconRenderWidth -
                           searchTheme->GetSearchIconRightSpace().ConvertToPx();
    if (searchButtonEvent->IsEnabled()) {
        textFieldWidth = textFieldWidth - buttonWidth - searchTheme->GetSearchDividerWidth().ConvertToPx() -
                         MULTIPLE_2 * searchTheme->GetDividerSideSpace().ConvertToPx();
    }

    if (cancelButtonEvent->IsEnabled()) {
        textFieldWidth = textFieldWidth - cancelButtonWidth;
    }

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize.SetWidth(textFieldWidth);
    textField->Measure(childLayoutConstraint);
    textFieldSizeMeasure_ = textFieldGeometryNode->GetFrameSize();
}

void SearchLayoutAlgorithm::ImageMeasure(FrameNode* frameNode)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto image = frameNode->GetFrameNodeByIndex(IMAGE_INDEX);
    CHECK_NULL_VOID(image);
    auto imageGeometryNode = image->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    image->Measure(childLayoutConstraint);
    searchIconSizeMeasure_ = imageGeometryNode->GetFrameSize();
}

void SearchLayoutAlgorithm::SearchButtonMeasure(FrameNode* frameNode)
{
    auto button = frameNode->GetFrameNodeByIndex(BUTTON_INDEX);
    CHECK_NULL_VOID(button);
    auto buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(button->GetLayoutProperty());
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto buttonGeometryNode = button->GetGeometryNode();
    CHECK_NULL_VOID(buttonGeometryNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);

    // calculate theme space from search button to font
    auto spaceHeight = searchTheme->GetHeight().ConvertToPx() - 2 * searchTheme->GetSearchButtonSpace().ConvertToPx() -
        searchTheme->GetFontSize().ConvertToPx();

    // calculate search button height
    auto searchButtonHeight =
        layoutProperty->GetSearchButtonFontSizeValue(searchTheme->GetFontSize()).ConvertToPx() + spaceHeight;
    CalcSize searchButtonCalcSize;
    searchButtonCalcSize.SetHeight(CalcLength(searchButtonHeight));
    buttonLayoutProperty->UpdateUserDefinedIdealSize(searchButtonCalcSize);

    // searchButton Measure
    auto buttonLayoutConstraint = layoutProperty->CreateChildConstraint();
    button->Measure(buttonLayoutConstraint);
    searchButtonSizeMeasure_ = buttonGeometryNode->GetFrameSize();
}

double SearchLayoutAlgorithm::CalcSearchAdaptHeight(FrameNode* frameNode)
{
    double searchHeightAdapt = 0;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, 0);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(searchTheme, 0);
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, 0);
    auto searchBtn = frameNode->GetFrameNodeByIndex(BUTTON_INDEX);
    CHECK_NULL_RETURN(searchBtn, 0);
    auto cancelBtn = frameNode->GetFrameNodeByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_RETURN(cancelBtn, 0);

    // search button height
    auto searchButtonEvent = searchBtn->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(searchButtonEvent, true);
    auto searchButtonHeight = searchButtonSizeMeasure_.Height() + 2 * searchTheme->GetSearchButtonSpace().ConvertToPx();
    searchButtonHeight = (!searchButtonEvent->IsEnabled()) ? 0.0f : searchButtonHeight;

    // search icon height
    auto searchIconFrameHight = searchIconSizeMeasure_.Height();
    auto searchIconHeight = layoutProperty->GetSearchIconUDSizeValue(Dimension(searchIconFrameHight)).ConvertToPx();
    searchIconHeight += searchTheme->GetHeight().ConvertToPx() - searchTheme->GetIconHeight().ConvertToPx();

    // cancel button height
    auto cancelButtonEvent = cancelBtn->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(cancelButtonEvent, 0);
    auto cancelBtnHight = cancelBtnSizeMeasure_.Height() + 2 * searchTheme->GetSearchButtonSpace().ConvertToPx();
    cancelBtnHight = (!cancelButtonEvent->IsEnabled()) ? 0.0f : cancelBtnHight;

    // textfield height
    auto textfieldHeight = textFieldSizeMeasure_.Height();

    // calculate the highest
    searchHeightAdapt = std::max(searchIconHeight, searchButtonHeight);
    searchHeightAdapt = std::max(searchHeightAdapt, cancelBtnHight);
    searchHeightAdapt = std::max(searchHeightAdapt, static_cast<double>(textfieldHeight));

    return searchHeightAdapt;
}

void SearchLayoutAlgorithm::SelfMeasure(FrameNode* frameNode)
{
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);

    // theme height
    auto themeHeight = searchTheme->GetHeight().ConvertToPx();

    // self height
    auto searchHeight =
        (constraint->selfIdealSize.Height().has_value()) ? constraint->selfIdealSize.Height().value() : themeHeight;
    auto searchHeightAdapt = searchHeight;

    if (!IsFixedHeightMode(frameNode)) {
        searchHeightAdapt = CalcSearchAdaptHeight(frameNode);
        renderContext->SetClipToBounds(false);
    } else {
        renderContext->SetClipToBounds(true);
    }

    // update search height
    constraint->selfIdealSize.SetHeight(searchHeightAdapt);

    auto idealSize = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
    if (GreaterOrEqualToInfinity(idealSize.Width()) || GreaterOrEqualToInfinity(idealSize.Height())) {
        LOGW("Size is infinity.");
        geometryNode->SetFrameSize(SizeF());
        return;
    }

    // update search height
    geometryNode->SetFrameSize(idealSize);
    geometryNode->SetContentSize(idealSize);
}

void SearchLayoutAlgorithm::Measure(FrameNode* frameNode)
{
    auto children = frameNode->GetChildren();
    if (children.empty()) {
        LOGW("Search has no child node.");
        return;
    }

    SearchButtonMeasure(frameNode);
    ImageMeasure(frameNode);
    CancelImageMeasure(frameNode);
    CancelButtonMeasure(frameNode);
    TextFieldMeasure(frameNode);
    SelfMeasure(frameNode);

    if (IsFixedHeightMode(frameNode)) {
        CalcChildrenHotZone(frameNode);
    }
}

void SearchLayoutAlgorithm::CalcChildrenHotZone(FrameNode* frameNode)
{
    // search info
    auto searchGeometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(searchGeometryNode);
    auto searchHeight = searchGeometryNode->GetFrameSize().Height();

    // cancel button info
    auto cancelButton = frameNode->GetFrameNodeByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButton);
    auto cancelButtonGeometryNode = cancelButton->GetGeometryNode();
    CHECK_NULL_VOID(cancelButtonGeometryNode);
    auto cancelButtonFrameSize = cancelButtonGeometryNode->GetFrameSize();
    auto cancelButtonWidth = cancelButtonFrameSize.Width();
    auto cancelButtonHeight = cancelButtonFrameSize.Height();

    // search button info
    auto searchButton = frameNode->GetFrameNodeByIndex(BUTTON_INDEX);
    CHECK_NULL_VOID(searchButton);
    auto searchButtonGeometryNode = searchButton->GetGeometryNode();
    CHECK_NULL_VOID(searchButtonGeometryNode);
    auto searchButtonFrameSize = searchButtonGeometryNode->GetFrameSize();
    auto searchButtonWidth = searchButtonFrameSize.Width();
    auto searchButtonHeight = searchButtonFrameSize.Height();

    // calculate cancel button hot zone
    cancelButton->RemoveLastHotZoneRect();
    DimensionRect cancelButtonHotZone;
    if (cancelButtonHeight > searchHeight) {
        cancelButtonHotZone.SetSize(DimensionSize(Dimension(cancelButtonWidth), Dimension(searchHeight)));
        double hotZoneOffsetY = (cancelButtonHeight - searchHeight) / 2;
        cancelButtonHotZone.SetOffset(DimensionOffset(Dimension(0), Dimension(hotZoneOffsetY)));
    } else {
        cancelButtonHotZone.SetSize(DimensionSize(Dimension(cancelButtonWidth), Dimension(cancelButtonHeight)));
        cancelButtonHotZone.SetOffset(DimensionOffset(Dimension(0), Dimension(0)));
    }
    cancelButton->AddHotZoneRect(cancelButtonHotZone);

    // calculate search button hot zone
    searchButton->RemoveLastHotZoneRect();
    DimensionRect searchButtonHotZone;
    if (searchButtonHeight > searchHeight) {
        searchButtonHotZone.SetSize(DimensionSize(Dimension(searchButtonWidth), Dimension(searchHeight)));
        double hotZoneOffsetY = (searchButtonHeight - searchHeight) / 2;
        searchButtonHotZone.SetOffset(DimensionOffset(Dimension(0), Dimension(hotZoneOffsetY)));
    } else {
        searchButtonHotZone.SetSize(DimensionSize(Dimension(searchButtonWidth), Dimension(searchButtonHeight)));
        searchButtonHotZone.SetOffset(DimensionOffset(Dimension(0), Dimension(0)));
    }
    searchButton->AddHotZoneRect(searchButtonHotZone);
}

void SearchLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    auto children = frameNode->GetChildren();
    if (children.empty()) {
        LOGW("Search has no child node.");
        return;
    }

    auto layoutProperty = DynamicCast<SearchLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    // search theme
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    auto searchIconLeftSpace = searchTheme->GetSearchIconLeftSpace().ConvertToPx();
    auto searchIconRightSpace = searchTheme->GetSearchIconRightSpace().ConvertToPx();
    auto searchButtonSpace = searchTheme->GetSearchButtonSpace().ConvertToPx();
    auto dividerSideSpace = searchTheme->GetDividerSideSpace().ConvertToPx();
    auto dividerWidth = searchTheme->GetSearchDividerWidth().ConvertToPx();

    // search size
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto searchSize = geometryNode->GetFrameSize();
    auto searchFrameWidth = searchSize.Width();
    auto searchFrameHeight = searchSize.Height();

    // search icon size
    auto image = frameNode->GetFrameNodeByIndex(IMAGE_INDEX);
    CHECK_NULL_VOID(image);
    auto imageGeometryNode = image->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    auto iconFrameWidth = searchIconSizeMeasure_.Width();
    auto iconFrameHeight = searchIconSizeMeasure_.Height();
    auto iconRenderWidth = layoutProperty->GetSearchIconUDSizeValue(Dimension(iconFrameWidth)).ConvertToPx();

    // layout search icon
    float iconHorizontalOffset = searchIconLeftSpace + (iconRenderWidth - iconFrameWidth) / 2.0;
    float imageVerticalOffset = (searchFrameHeight - iconFrameHeight) / 2.0;
    OffsetF imageOffset(iconHorizontalOffset, imageVerticalOffset);
    imageGeometryNode->SetMarginFrameOffset(imageOffset);
    image->Layout();

    // layout textfield
    auto textField = frameNode->GetFrameNodeByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textField);
    auto textFieldGeometryNode = textField->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);
    float textFieldHorizontalOffset = searchIconLeftSpace + iconRenderWidth + searchIconRightSpace;
    float textFieldVerticalOffset = (searchFrameHeight - textFieldGeometryNode->GetFrameSize().Height()) / 2.0;
    textFieldGeometryNode->SetMarginFrameOffset(OffsetF(textFieldHorizontalOffset, textFieldVerticalOffset));
    textField->Layout();

    // cancel button size
    auto cancelButton = frameNode->GetFrameNodeByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButton);
    auto cancelButtonGeometryNode = cancelButton->GetGeometryNode();
    CHECK_NULL_VOID(cancelButtonGeometryNode);
    auto cancelButtonFrameSize = cancelButtonGeometryNode->GetFrameSize();
    auto cancelButtonFrameWidth = cancelButtonFrameSize.Width();
    auto cancelButtonFrameHeight = cancelButtonFrameSize.Height();

    // cancel image size
    auto cancelImage = frameNode->GetFrameNodeByIndex(CANCEL_IMAGE_INDEX);
    CHECK_NULL_VOID(cancelImage);
    auto cancelImageGeometryNode = cancelImage->GetGeometryNode();
    CHECK_NULL_VOID(cancelImageGeometryNode);
    auto cancelImageFrameSize = cancelImageGeometryNode->GetFrameSize();
    auto cancelImageFrameWidth = cancelImageFrameSize.Width();
    auto cancelImageFrameHeight = cancelImageFrameSize.Height();

    // layout search button
    auto searchButton = frameNode->GetFrameNodeByIndex(BUTTON_INDEX);
    CHECK_NULL_VOID(searchButton);
    auto searchButtonGeometryNode = searchButton->GetGeometryNode();
    CHECK_NULL_VOID(searchButtonGeometryNode);
    auto searchButtonFrameSize = searchButtonGeometryNode->GetFrameSize();
    float searchButtonVerticalOffset = (searchFrameHeight - searchButtonFrameSize.Height()) / 2.0;
    float searchButtonHorizontalOffset = searchFrameWidth - searchButtonFrameSize.Width() - searchButtonSpace;
    searchButtonHorizontalOffset = std::max(searchButtonHorizontalOffset, 0.0f);
    OffsetF searchButtonOffset = OffsetF(searchButtonHorizontalOffset, searchButtonVerticalOffset);
    searchButtonGeometryNode->SetMarginFrameOffset(searchButtonOffset);
    searchButton->Layout();

    // layout cancel button
    float cancelButtonHorizontalOffset = 0;
    float cancelButtonVerticalOffset = (searchFrameHeight - cancelButtonFrameHeight) / 2;
    auto searchButtonEvent = searchButton->GetEventHub<ButtonEventHub>();
    if (searchButtonEvent->IsEnabled()) {
        auto cancelButtonOffsetToSearchButton = cancelButtonFrameWidth + 2 * dividerSideSpace + dividerWidth;
        cancelButtonHorizontalOffset = std::max(searchButtonOffset.GetX() - cancelButtonOffsetToSearchButton, 0.0);
    } else {
        cancelButtonHorizontalOffset = searchFrameWidth - cancelButtonFrameWidth - searchButtonSpace;
    }
    OffsetF cancelButtonOffset = OffsetF(cancelButtonHorizontalOffset, cancelButtonVerticalOffset);
    cancelButtonGeometryNode->SetMarginFrameOffset(cancelButtonOffset);
    cancelButton->Layout();

    // layout cancel image
    float cancelImageVerticalOffset = (searchFrameHeight - cancelImageFrameHeight) / 2;
    float cancelButtonImageCenterOffset = (cancelButtonFrameWidth - cancelImageFrameWidth) / 2;
    float cancelImageHorizontalOffset = cancelButtonHorizontalOffset + cancelButtonImageCenterOffset;
    OffsetF cancelImageOffset = OffsetF(cancelImageHorizontalOffset, cancelImageVerticalOffset);
    cancelImageGeometryNode->SetMarginFrameOffset(cancelImageOffset);
    cancelImage->Layout();
}

} // namespace OHOS::Ace::NG
