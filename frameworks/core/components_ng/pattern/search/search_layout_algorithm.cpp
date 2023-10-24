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

#include "core/components_ng/pattern/search/search_layout_algorithm.h"

#include <algorithm>

#include "base/utils/utils.h"
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

bool SearchLayoutAlgorithm::IsFixedHeightMode(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);

    auto constraint = layoutProperty->GetLayoutConstraint();
    return constraint->selfIdealSize.Height().has_value();
}

void SearchLayoutAlgorithm::CancelImageMeasure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto cancelImageWrapper = layoutWrapper->GetOrCreateChildByIndex(CANCEL_IMAGE_INDEX);
    CHECK_NULL_VOID(cancelImageWrapper);
    auto cancelImageGeometryNode = cancelImageWrapper->GetGeometryNode();
    CHECK_NULL_VOID(cancelImageGeometryNode);
    auto imageLayoutProperty = cancelImageWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);
    auto themeHeight = searchTheme->GetHeight().ConvertToPx();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto imageConstraint = imageLayoutProperty->GetLayoutConstraint();
    auto searchHeight =
        (constraint->selfIdealSize.Height().has_value()) ? constraint->selfIdealSize.Height().value() : themeHeight;
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto defaultImageHeight =
        imageConstraint->selfIdealSize.Height().value_or(searchTheme->GetIconSize().ConvertToPx());
    auto imageHeightAdaptPadding =
        static_cast<float>(searchHeight - padding.top.value_or(0.0f) - padding.bottom.value_or(0.0f));
    auto imageHeight = std::min(defaultImageHeight, imageHeightAdaptPadding);
    CalcSize imageCalcSize;
    imageCalcSize.SetHeight(CalcLength(imageHeight));
    imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    cancelImageWrapper->Measure(childLayoutConstraint);
    cancelIconSizeMeasure_ = cancelImageGeometryNode->GetFrameSize();
}

void SearchLayoutAlgorithm::CancelButtonMeasure(LayoutWrapper* layoutWrapper)
{
    auto cancelButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButtonWrapper);
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto cancelButtonLayoutProperty =
        AceType::DynamicCast<ButtonLayoutProperty>(cancelButtonWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(cancelButtonLayoutProperty);
    auto cancelButtonGeometryNode = cancelButtonWrapper->GetGeometryNode();
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
    auto themeHeight = searchTheme->GetHeight().ConvertToPx();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto searchHeight =
        (constraint->selfIdealSize.Height().has_value()) ? constraint->selfIdealSize.Height().value() : themeHeight;
    auto padding = layoutProperty->CreatePaddingAndBorder();
    cancelButtonHeight =
        std::min(cancelButtonHeight, searchHeight - padding.top.value_or(0.0f) - padding.bottom.value_or(0.0f));
    CalcSize cancelButtonCalcSize((CalcLength(cancelButtonHeight)), CalcLength(cancelButtonHeight));
    cancelButtonLayoutProperty->UpdateUserDefinedIdealSize(cancelButtonCalcSize);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    cancelButtonWrapper->Measure(childLayoutConstraint);
    cancelBtnSizeMeasure_ = cancelButtonGeometryNode->GetFrameSize();
}

void SearchLayoutAlgorithm::TextFieldMeasure(LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textFieldWrapper);
    auto cancelButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButtonWrapper);
    auto textFieldGeometryNode = textFieldWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);

    auto buttonWidth = searchButtonSizeMeasure_.Width();
    auto cancelButtonWidth = cancelBtnSizeMeasure_.Width();
    auto iconRenderWidth =
        layoutProperty->GetSearchIconUDSizeValue(Dimension(searchIconSizeMeasure_.Width())).ConvertToPx();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto searchWidthMax = (constraint->selfIdealSize.Width().has_value())
                              ? std::min(constraint->selfIdealSize.Width().value(), constraint->maxSize.Width())
                              : std::min(constraint->percentReference.Width(), constraint->maxSize.Width());

    auto searchWrapper = layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
    auto searchButtonNode = searchWrapper->GetHostNode();
    auto searchButtonEvent = searchButtonNode->GetEventHub<ButtonEventHub>();
    auto cancelButtonNode = cancelButtonWrapper->GetHostNode();
    auto cancelButtonEvent = cancelButtonNode->GetEventHub<ButtonEventHub>();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    float leftPadding = padding.left.value_or(0.0f);
    float rightPadding = padding.right.value_or(0.0f);
    auto textFieldWidth = searchWidthMax - searchTheme->GetSearchIconLeftSpace().ConvertToPx() - iconRenderWidth -
                          searchTheme->GetSearchIconRightSpace().ConvertToPx() - leftPadding - rightPadding;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        textFieldWidth = searchWidthMax - searchTheme->GetSearchIconLeftSpace().ConvertToPx() - iconRenderWidth -
                         searchTheme->GetSearchIconRightSpace().ConvertToPx();
    }
    if (searchButtonEvent->IsEnabled()) {
        textFieldWidth = textFieldWidth - buttonWidth - searchTheme->GetSearchDividerWidth().ConvertToPx() -
                         MULTIPLE_2 * searchTheme->GetDividerSideSpace().ConvertToPx();
    }

    if (cancelButtonEvent->IsEnabled()) {
        textFieldWidth = textFieldWidth - cancelButtonWidth;
    }
    auto themeHeight = searchTheme->GetHeight().ConvertToPx();
    auto searchHeight =
        (constraint->selfIdealSize.Height().has_value()) ? constraint->selfIdealSize.Height().value() : themeHeight;
    auto textFieldHeight =
        std::min(themeHeight, searchHeight - padding.top.value_or(0.0f) - padding.bottom.value_or(0.0f));
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize.SetWidth(textFieldWidth);
    childLayoutConstraint.selfIdealSize.SetHeight(textFieldHeight);
    textFieldWrapper->Measure(childLayoutConstraint);
    textFieldSizeMeasure_ = textFieldGeometryNode->GetFrameSize();
}

void SearchLayoutAlgorithm::ImageMeasure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto imageWrapper = layoutWrapper->GetOrCreateChildByIndex(IMAGE_INDEX);
    CHECK_NULL_VOID(imageWrapper);
    auto imageGeometryNode = imageWrapper->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    auto imageLayoutProperty = imageWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);
    auto themeHeight = searchTheme->GetHeight().ConvertToPx();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto imageConstraint = imageLayoutProperty->GetLayoutConstraint();
    auto searchHeight =
        (constraint->selfIdealSize.Height().has_value()) ? constraint->selfIdealSize.Height().value() : themeHeight;
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto defaultImageHeight =
        imageConstraint->selfIdealSize.Height().value_or(searchTheme->GetIconSize().ConvertToPx());
    auto imageHeightAdaptPadding =
        static_cast<float>(searchHeight - padding.top.value_or(0.0f) - padding.bottom.value_or(0.0f));
    auto imageHeight = std::min(defaultImageHeight, imageHeightAdaptPadding);
    CalcSize imageCalcSize;
    imageCalcSize.SetHeight(CalcLength(imageHeight));
    imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    imageWrapper->Measure(childLayoutConstraint);
    searchIconSizeMeasure_ = imageGeometryNode->GetFrameSize();
}

void SearchLayoutAlgorithm::SearchButtonMeasure(LayoutWrapper* layoutWrapper)
{
    auto buttonWrapper = layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
    CHECK_NULL_VOID(buttonWrapper);
    auto buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(buttonWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto buttonGeometryNode = buttonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(buttonGeometryNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);

    // calculate theme space from search button to font
    auto spaceHeight = searchTheme->GetHeight().ConvertToPx() - 2 * searchTheme->GetSearchButtonSpace().ConvertToPx() -
                       searchTheme->GetFontSize().ConvertToPx();

    // calculate search button height
    auto defaultButtonHeight =
        searchTheme->GetHeight().ConvertToPx() - 2 * searchTheme->GetSearchButtonSpace().ConvertToPx();
    auto searchButtonHeight = std::max(defaultButtonHeight,
        layoutProperty->GetSearchButtonFontSizeValue(searchTheme->GetFontSize()).ConvertToPx() + spaceHeight);
    auto themeHeight = searchTheme->GetHeight().ConvertToPx();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto searchHeight =
        (constraint->selfIdealSize.Height().has_value()) ? constraint->selfIdealSize.Height().value() : themeHeight;
    auto padding = layoutProperty->CreatePaddingAndBorder();
    searchButtonHeight =
        std::min(searchButtonHeight, searchHeight - padding.top.value_or(0.0f) - padding.bottom.value_or(0.0f));
    CalcSize searchButtonCalcSize;
    searchButtonCalcSize.SetHeight(CalcLength(searchButtonHeight));
    buttonLayoutProperty->UpdateUserDefinedIdealSize(searchButtonCalcSize);

    // searchButton Measure
    auto buttonLayoutConstraint = layoutProperty->CreateChildConstraint();
    buttonWrapper->Measure(buttonLayoutConstraint);
    searchButtonSizeMeasure_ = buttonGeometryNode->GetFrameSize();
}

double SearchLayoutAlgorithm::CalcSearchAdaptHeight(LayoutWrapper* layoutWrapper)
{
    double searchHeightAdapt = 0;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, 0);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(searchTheme, 0);
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, 0);
    auto searchBtnWrapper = layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
    CHECK_NULL_RETURN(searchBtnWrapper, 0);
    auto cancelBtnLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_RETURN(cancelBtnLayoutWrapper, 0);

    // search button height
    auto buttonNode = searchBtnWrapper->GetHostNode();
    CHECK_NULL_RETURN(buttonNode, true);
    auto searchButtonEvent = buttonNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(searchButtonEvent, true);
    auto searchButtonHeight = searchButtonSizeMeasure_.Height() + 2 * searchTheme->GetSearchButtonSpace().ConvertToPx();
    searchButtonHeight = (!searchButtonEvent->IsEnabled()) ? 0.0f : searchButtonHeight;

    // search icon height
    auto searchIconFrameHight = searchIconSizeMeasure_.Height();
    auto searchIconHeight = layoutProperty->GetSearchIconUDSizeValue(Dimension(searchIconFrameHight)).ConvertToPx();
    searchIconHeight += searchTheme->GetHeight().ConvertToPx() - searchTheme->GetIconHeight().ConvertToPx();

    // cancel button height
    auto cancelButtonNode = cancelBtnLayoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(cancelButtonNode, 0);
    auto cancelButtonEvent = cancelButtonNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(cancelButtonEvent, 0);
    auto cancelBtnHight = cancelBtnSizeMeasure_.Height() + 2 * searchTheme->GetSearchButtonSpace().ConvertToPx();
    cancelBtnHight = (!cancelButtonEvent->IsEnabled()) ? 0.0f : cancelBtnHight;

    // textfield height
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto verticalPadding = padding.top.value_or(0.0f) + padding.bottom.value_or(0.0f);
    auto textfieldHeight = textFieldSizeMeasure_.Height() + verticalPadding;

    // calculate the highest
    searchHeightAdapt = std::max(searchIconHeight, searchButtonHeight);
    searchHeightAdapt = std::max(searchHeightAdapt, cancelBtnHight);
    searchHeightAdapt = std::max(searchHeightAdapt, static_cast<double>(textfieldHeight));

    return searchHeightAdapt;
}

void SearchLayoutAlgorithm::SelfMeasure(LayoutWrapper* layoutWrapper)
{
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);

    // theme height
    auto themeHeight = searchTheme->GetHeight().ConvertToPx();

    // self height
    auto searchHeight =
        (constraint->selfIdealSize.Height().has_value()) ? constraint->selfIdealSize.Height().value() : themeHeight;
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto verticalPadding = padding.top.value_or(0.0f) + padding.bottom.value_or(0.0f);
    searchHeight = std::max(verticalPadding, static_cast<float>(searchHeight));
    auto searchHeightAdapt = searchHeight;
    if (!IsFixedHeightMode(layoutWrapper)) {
        searchHeightAdapt = CalcSearchAdaptHeight(layoutWrapper);
        renderContext->SetClipToBounds(false);
    } else {
        renderContext->SetClipToBounds(true);
    }

    // update search height
    constraint->selfIdealSize.SetHeight(searchHeightAdapt);
    auto searchWidth = (constraint->selfIdealSize.Width().has_value())
                           ? std::min(constraint->selfIdealSize.Width().value(), constraint->maxSize.Width())
                           : std::min(constraint->percentReference.Width(), constraint->maxSize.Width());
    SizeF idealSize(searchWidth, searchHeightAdapt);
    if (GreaterOrEqualToInfinity(idealSize.Width()) || GreaterOrEqualToInfinity(idealSize.Height())) {
        LOGW("Size is infinity.");
        geometryNode->SetFrameSize(SizeF());
        return;
    }

    // update search height
    geometryNode->SetFrameSize(idealSize);
    geometryNode->SetContentSize(idealSize);
}

void SearchLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.empty()) {
        LOGW("Search has no child node.");
        return;
    }

    SearchButtonMeasure(layoutWrapper);
    ImageMeasure(layoutWrapper);
    CancelImageMeasure(layoutWrapper);
    CancelButtonMeasure(layoutWrapper);
    TextFieldMeasure(layoutWrapper);
    SelfMeasure(layoutWrapper);
}

void SearchLayoutAlgorithm::CalcChildrenHotZone(LayoutWrapper* layoutWrapper)
{
    // search info
    auto searchGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(searchGeometryNode);
    auto searchHeight = searchGeometryNode->GetFrameSize().Height();

    // cancel button info
    auto cancelButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButtonWrapper);
    auto cancelButtonFrameNode = cancelButtonWrapper->GetHostNode();
    CHECK_NULL_VOID(cancelButtonFrameNode);
    auto cancelButtonGeometryNode = cancelButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(cancelButtonGeometryNode);
    auto cancelButtonFrameSize = cancelButtonGeometryNode->GetFrameSize();
    auto cancelButtonWidth = cancelButtonFrameSize.Width();
    auto cancelButtonHeight = cancelButtonFrameSize.Height();

    // search button info
    auto searchButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
    CHECK_NULL_VOID(searchButtonWrapper);
    auto searchButtonFrameNode = searchButtonWrapper->GetHostNode();
    CHECK_NULL_VOID(searchButtonFrameNode);
    auto searchButtonGeometryNode = searchButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(searchButtonGeometryNode);
    auto searchButtonFrameSize = searchButtonGeometryNode->GetFrameSize();
    auto searchButtonWidth = searchButtonFrameSize.Width();
    auto searchButtonHeight = searchButtonFrameSize.Height();

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    auto buttonSpace = searchTheme->GetSearchButtonSpace().ConvertToPx();
    // calculate cancel button hot zone
    cancelButtonFrameNode->RemoveLastHotZoneRect();
    DimensionRect cancelButtonHotZone;
    if (cancelButtonHeight > searchHeight) {
        cancelButtonHotZone.SetSize(DimensionSize(Dimension(cancelButtonWidth), Dimension(searchHeight)));
        double hotZoneOffsetY = (cancelButtonHeight - searchHeight) / 2;
        cancelButtonHotZone.SetOffset(DimensionOffset(Dimension(0), Dimension(hotZoneOffsetY)));
    } else {
        cancelButtonHotZone.SetSize(DimensionSize(
            Dimension(cancelButtonWidth + 2 * buttonSpace), Dimension(cancelButtonHeight + 2 * buttonSpace)));
        cancelButtonHotZone.SetOffset(
            DimensionOffset(Offset(static_cast<float>(-buttonSpace), static_cast<float>(-buttonSpace))));
    }
    cancelButtonFrameNode->AddHotZoneRect(cancelButtonHotZone);

    // calculate search button hot zone
    searchButtonFrameNode->RemoveLastHotZoneRect();
    DimensionRect searchButtonHotZone;
    if (searchButtonHeight > searchHeight) {
        searchButtonHotZone.SetSize(DimensionSize(Dimension(searchButtonWidth), Dimension(searchHeight)));
        double hotZoneOffsetY = (searchButtonHeight - searchHeight) / 2;
        searchButtonHotZone.SetOffset(DimensionOffset(Dimension(0), Dimension(hotZoneOffsetY)));
    } else {
        searchButtonHotZone.SetSize(DimensionSize(
            Dimension(searchButtonWidth + 2 * buttonSpace), Dimension(searchButtonHeight + 2 * buttonSpace)));
        searchButtonHotZone.SetOffset(
            DimensionOffset(Offset(static_cast<float>(-buttonSpace), static_cast<float>(-buttonSpace))));
    }
    searchButtonFrameNode->AddHotZoneRect(searchButtonHotZone);
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

    auto layoutProperty = DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
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
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto searchSize = geometryNode->GetFrameSize();
    auto searchFrameWidth = searchSize.Width();
    auto searchFrameHeight = searchSize.Height();
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    auto searchUserHeight = layoutConstraint->selfIdealSize.Height().value_or(searchTheme->GetHeight().ConvertToPx());

    // search icon size
    auto imageWrapper = layoutWrapper->GetOrCreateChildByIndex(IMAGE_INDEX);
    CHECK_NULL_VOID(imageWrapper);
    auto imageGeometryNode = imageWrapper->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    auto iconFrameWidth = searchIconSizeMeasure_.Width();
    auto iconFrameHeight = searchIconSizeMeasure_.Height();
    auto iconRenderWidth = layoutProperty->GetSearchIconUDSizeValue(Dimension(iconFrameWidth)).ConvertToPx();

    // layout search icon
    auto padding = layoutProperty->CreatePaddingAndBorder();
    float topPadding = padding.top.value_or(0.0f);
    float bottomPadding = padding.bottom.value_or(0.0f);
    float leftOffset = padding.left.value_or(0.0f);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        leftOffset = 0.0f;
    }
    float iconHorizontalOffset = leftOffset + searchIconLeftSpace + (iconRenderWidth - iconFrameWidth) / 2;
    auto searchIconConstraint = imageWrapper->GetLayoutProperty()->GetLayoutConstraint();
    auto iconUserHeight =
        searchIconConstraint->selfIdealSize.Height().value_or(searchTheme->GetIconHeight().ConvertToPx());
    float imageVerticalOffset = topPadding;
    if (NearEqual(iconUserHeight, iconFrameHeight)) {
        auto iconInterval = (searchUserHeight - iconUserHeight) / 2;
        if (topPadding <= iconInterval && bottomPadding <= iconInterval) {
            imageVerticalOffset = iconInterval;
        } else if (topPadding <= iconInterval && bottomPadding > iconInterval) {
            imageVerticalOffset = searchFrameHeight - (bottomPadding + iconFrameHeight);
        }
    }
    auto centerVerticalOffset = imageVerticalOffset + iconFrameHeight / 2;
    OffsetF imageOffset(iconHorizontalOffset, imageVerticalOffset);
    imageGeometryNode->SetMarginFrameOffset(imageOffset);
    imageWrapper->Layout();

    // layout textfield
    auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textFieldWrapper);
    auto textFieldGeometryNode = textFieldWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);
    float textFieldHorizontalOffset = leftOffset + searchIconLeftSpace + iconRenderWidth + searchIconRightSpace;
    float textFieldVerticalOffset = centerVerticalOffset - textFieldGeometryNode->GetFrameSize().Height() / 2;
    textFieldGeometryNode->SetMarginFrameOffset(OffsetF(textFieldHorizontalOffset, textFieldVerticalOffset));
    textFieldWrapper->Layout();

    // cancel button size
    auto cancelButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButtonWrapper);
    auto cancelButtonGeometryNode = cancelButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(cancelButtonGeometryNode);
    auto cancelButtonFrameSize = cancelButtonGeometryNode->GetFrameSize();
    auto cancelButtonFrameWidth = cancelButtonFrameSize.Width();
    auto cancelButtonFrameHeight = cancelButtonFrameSize.Height();

    // cancel image size
    auto cancelImageWrapper = layoutWrapper->GetOrCreateChildByIndex(CANCEL_IMAGE_INDEX);
    CHECK_NULL_VOID(cancelImageWrapper);
    auto cancelImageGeometryNode = cancelImageWrapper->GetGeometryNode();
    CHECK_NULL_VOID(cancelImageGeometryNode);
    auto cancelImageFrameSize = cancelImageGeometryNode->GetFrameSize();
    auto cancelImageFrameWidth = cancelImageFrameSize.Width();
    auto cancelImageFrameHeight = cancelImageFrameSize.Height();

    // layout search button
    auto searchButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
    CHECK_NULL_VOID(searchButtonWrapper);
    auto searchButtonGeometryNode = searchButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(searchButtonGeometryNode);
    auto searchButtonFrameSize = searchButtonGeometryNode->GetFrameSize();
    float searchButtonVerticalOffset = centerVerticalOffset - searchButtonFrameSize.Height() / 2;
    float rightOffset = padding.right.value_or(0.0f);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        rightOffset = 0.0f;
    }
    float searchButtonHorizontalOffset =
        searchFrameWidth - searchButtonFrameSize.Width() - searchButtonSpace - rightOffset;
    searchButtonHorizontalOffset = std::max(searchButtonHorizontalOffset, 0.0f);
    OffsetF searchButtonOffset = OffsetF(searchButtonHorizontalOffset, searchButtonVerticalOffset);
    searchButtonGeometryNode->SetMarginFrameOffset(searchButtonOffset);
    searchButtonWrapper->Layout();

    // layout cancel button
    float cancelButtonHorizontalOffset = 0;
    float cancelButtonVerticalOffset = centerVerticalOffset - cancelButtonFrameHeight / 2;
    auto searchButtonNode = searchButtonWrapper->GetHostNode();
    auto searchButtonEvent = searchButtonNode->GetEventHub<ButtonEventHub>();
    if (searchButtonEvent->IsEnabled()) {
        auto cancelButtonOffsetToSearchButton = cancelButtonFrameWidth + 2 * dividerSideSpace + dividerWidth;
        cancelButtonHorizontalOffset = std::max(searchButtonOffset.GetX() - cancelButtonOffsetToSearchButton, 0.0);
    } else {
        cancelButtonHorizontalOffset = searchFrameWidth - cancelButtonFrameWidth - searchButtonSpace - rightOffset;
    }
    OffsetF cancelButtonOffset = OffsetF(cancelButtonHorizontalOffset, cancelButtonVerticalOffset);
    cancelButtonGeometryNode->SetMarginFrameOffset(cancelButtonOffset);
    cancelButtonWrapper->Layout();

    // layout cancel image
    float cancelImageVerticalOffset = centerVerticalOffset - cancelImageFrameHeight / 2;
    float cancelButtonImageCenterOffset = (cancelButtonFrameWidth - cancelImageFrameWidth) / 2;
    float cancelImageHorizontalOffset = cancelButtonHorizontalOffset + cancelButtonImageCenterOffset;
    OffsetF cancelImageOffset = OffsetF(cancelImageHorizontalOffset, cancelImageVerticalOffset);
    cancelImageGeometryNode->SetMarginFrameOffset(cancelImageOffset);
    cancelImageWrapper->Layout();
    CalcChildrenHotZone(layoutWrapper);
}

} // namespace OHOS::Ace::NG
