/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/search/search_pattern.h"

#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t IMAGE_INDEX = 1;
constexpr int32_t CANCEL_IMAGE_INDEX = 2;
constexpr int32_t CANCEL_BUTTON_INDEX = 3;
constexpr int32_t BUTTON_INDEX = 4;
constexpr int32_t DIVIDER_INDEX = 5;
constexpr int32_t MULTIPLE_2 = 2;
constexpr float MAX_SEARCH_BUTTON_RATE = 0.4f;
constexpr float AGING_MIN_SCALE = 1.75f;
constexpr float MAX_FONT_SCALE = 2.0f;
constexpr int TWO = 2;
constexpr Dimension DEFAULT_DIVIDER_HEIGHT = 12.0_vp;
} // namespace

bool SearchLayoutAlgorithm::IsFixedHeightMode(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);

    auto constraint = layoutProperty->GetLayoutConstraint();
    return constraint->selfIdealSize.Height().has_value();
}

float SearchLayoutAlgorithm::CalculateMaxFontScale(LayoutWrapper* layoutWrapper)
{
    auto searchHost = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(searchHost, MAX_FONT_SCALE);
    auto pipeline = searchHost->GetContext();
    CHECK_NULL_RETURN(pipeline, MAX_FONT_SCALE);
    auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_RETURN(textFieldWrapper, MAX_FONT_SCALE);
    auto textFieldLayoutProperty = AceType::DynamicCast<TextFieldLayoutProperty>(textFieldWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textFieldLayoutProperty, MAX_FONT_SCALE);
    auto maxScale = MAX_FONT_SCALE;
    if (textFieldLayoutProperty->HasMaxFontScale()) {
        maxScale = std::min(textFieldLayoutProperty->GetMaxFontScale().value(), maxScale);
    } else {
        maxScale = std::min(pipeline->GetMaxAppFontScale(), maxScale);
    }
    return maxScale;
}

float SearchLayoutAlgorithm::CalculateMinFontScale(LayoutWrapper* layoutWrapper)
{
    auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_RETURN(textFieldWrapper, 0.0f);
    auto textFieldLayoutProperty = AceType::DynamicCast<TextFieldLayoutProperty>(textFieldWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textFieldLayoutProperty, 0.0f);
    auto minScale = 0.0f;
    if (textFieldLayoutProperty->HasMinFontScale()) {
        minScale = textFieldLayoutProperty->GetMinFontScale().value();
    }
    return minScale;
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
    auto searchHost = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(searchHost);
    auto pipeline = searchHost->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>(searchHost->GetThemeScopeId());
    CHECK_NULL_VOID(searchTheme);
    auto defaultImageHeight = static_cast<float>(searchTheme->GetIconSize().ConvertToPxDistribute(
        minFontScale_, maxFontScale_));
    auto imageHeight = static_cast<float>(std::min(layoutProperty->HasCancelButtonUDSize() ?
        layoutProperty->GetCancelButtonUDSizeValue().ConvertToPxDistribute(
            minFontScale_, maxFontScale_) : defaultImageHeight,
        searchHeight_));
    if (cancelImageWrapper->GetHostTag() == V2::SYMBOL_ETS_TAG) {
        imageHeight = CalcSymbolIconHeight(layoutWrapper, CANCEL_IMAGE_INDEX, defaultImageHeight);
    }
    CalcSize imageCalcSize;
    imageCalcSize.SetWidth(CalcLength(imageHeight));
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
    auto searchHost = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(searchHost);
    auto pipeline = searchHost->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>(searchHost->GetThemeScopeId());
    CHECK_NULL_VOID(searchTheme);

    // calculate theme space from cancel button to cancel image
    auto spaceHeight = searchTheme->GetHeight().ConvertToPx() - 2 * searchTheme->GetSearchButtonSpace().ConvertToPx() -
                       searchTheme->GetIconHeight().ConvertToPx();

    // calculate cancel button height
    auto cancelButtonHeight =
        layoutProperty->GetCancelButtonUDSizeValue(Dimension(cancelIconSizeMeasure_.Height())).ConvertToPx() +
        spaceHeight;

    // cancel button height should be less than searchHeight
    cancelButtonHeight = std::min(cancelButtonHeight, searchHeight_);

    CalcSize cancelButtonCalcSize((CalcLength(cancelButtonHeight)), CalcLength(cancelButtonHeight));
    cancelButtonLayoutProperty->UpdateUserDefinedIdealSize(cancelButtonCalcSize);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    cancelButtonWrapper->Measure(childLayoutConstraint);
    cancelBtnSizeMeasure_ = cancelButtonGeometryNode->GetFrameSize();
}

void SearchLayoutAlgorithm::TextFieldMeasure(LayoutWrapper* layoutWrapper)
{
    auto searchHost = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(searchHost);
    auto pipeline = searchHost->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>(searchHost->GetThemeScopeId());
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textFieldWrapper);

    UpdateFontFeature(layoutWrapper);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto searchWidthMax = CalcSearchWidth(constraint.value(), layoutWrapper);

    auto textFieldWidth = CalculateTextFieldWidth(layoutWrapper, searchWidthMax, searchTheme);
    auto textFieldHeight = searchHeight_;
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize.SetWidth(textFieldWidth);
    if (LessNotEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        SetTextFieldLayoutConstraintHeight(childLayoutConstraint, textFieldHeight, layoutWrapper);
    }
    textFieldWrapper->Measure(childLayoutConstraint);
    UpdateTextFieldSize(layoutWrapper);
}

float SearchLayoutAlgorithm::CalculateTextFieldWidth(
    LayoutWrapper* layoutWrapper, float searchWidthMax, const RefPtr<SearchTheme>& searchTheme)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    auto buttonWidth = searchButtonSizeMeasure_.Width();
    auto cancelButtonWidth = cancelBtnSizeMeasure_.Width();
    auto iconRenderWidth =
        layoutProperty->GetSearchIconUDSizeValue(Dimension(searchIconSizeMeasure_.Width())).ConvertToPx();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    float leftPadding = padding.left.value_or(0.0f);
    float rightPadding = padding.right.value_or(0.0f);
    auto textFieldWidth = searchWidthMax - searchTheme->GetSearchIconLeftSpace().ConvertToPx() - iconRenderWidth -
                          searchTheme->GetSearchIconRightSpace().ConvertToPx() - leftPadding - rightPadding;
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TEN)) {
        textFieldWidth = searchWidthMax - searchTheme->GetSearchIconLeftSpace().ConvertToPx() - iconRenderWidth -
                         searchTheme->GetSearchIconRightSpace().ConvertToPx();
    }

    auto searchWrapper = layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
    auto searchButtonNode = searchWrapper->GetHostNode();
    auto searchButtonEvent = searchButtonNode->GetEventHub<ButtonEventHub>();
    auto searchButtonLayoutProperty = searchButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(searchButtonLayoutProperty, 0.0f);
    auto needToDisable = searchButtonLayoutProperty->GetAutoDisable().value_or(false);
    if (searchButtonEvent->IsEnabled() || needToDisable) {
        textFieldWidth = textFieldWidth - buttonWidth - searchTheme->GetSearchDividerWidth().ConvertToPx() -
                         MULTIPLE_2 * searchTheme->GetDividerSideSpace().ConvertToPx();
    }

    auto style = layoutProperty->GetCancelButtonStyle().value_or(CancelButtonStyle::INPUT);
    if (style != CancelButtonStyle::INVISIBLE) {
        textFieldWidth = textFieldWidth - cancelButtonWidth;
    }
    if (style == CancelButtonStyle::INVISIBLE && !searchButtonEvent->IsEnabled()) {
        // right padding without cancel button and search button
        auto rightPadding = searchTheme->GetRightPaddingWithoutButton();
        textFieldWidth = textFieldWidth - rightPadding.ConvertToPx();
    }

    return textFieldWidth;
}

void SearchLayoutAlgorithm::UpdateFontFeature(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textFieldWrapper);

    auto textFieldLayoutProperty = AceType::DynamicCast<TextFieldLayoutProperty>(textFieldWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (layoutProperty->HasFontFeature()) {
        textFieldLayoutProperty->UpdateFontFeature(layoutProperty->GetFontFeature().value());
    }
}

void SearchLayoutAlgorithm::UpdateTextFieldSize(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textFieldWrapper);

    auto textFieldGeometryNode = textFieldWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);
    textFieldSizeMeasure_ = textFieldGeometryNode->GetFrameSize();
}

void SearchLayoutAlgorithm::SetTextFieldLayoutConstraintHeight(LayoutConstraintF& contentConstraint,
    double textFieldHeight, LayoutWrapper* layoutWrapper)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto textFieldWrapper = layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
        auto textFieldLayoutProperty =
            AceType::DynamicCast<TextFieldLayoutProperty>(textFieldWrapper->GetLayoutProperty());
        if ((textFieldLayoutProperty == nullptr) || (!textFieldLayoutProperty->HasLineHeight())) {
            contentConstraint.selfIdealSize.SetHeight(textFieldHeight);
        }
        return;
    }
    contentConstraint.selfIdealSize.SetHeight(textFieldHeight);
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
    auto searchHost = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(searchHost);
    auto pipeline = searchHost->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>(searchHost->GetThemeScopeId());
    CHECK_NULL_VOID(searchTheme);
    auto defaultImageHeight = searchTheme->GetIconSize().ConvertToPx();
    auto imageHeight = static_cast<float>(std::min(layoutProperty->HasSearchIconUDSize() ?
        layoutProperty->GetSearchIconUDSizeValue().ConvertToPx() : defaultImageHeight,
        searchHeight_));
    if (imageWrapper->GetHostTag() == V2::SYMBOL_ETS_TAG) {
        imageHeight = CalcSymbolIconHeight(layoutWrapper, IMAGE_INDEX, defaultImageHeight);
    }
    CalcSize imageCalcSize;
    imageCalcSize.SetWidth(CalcLength(imageHeight));
    imageCalcSize.SetHeight(CalcLength(imageHeight));
    imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    imageWrapper->Measure(childLayoutConstraint);
    searchIconSizeMeasure_ = imageGeometryNode->GetFrameSize();
}

CalcSize SearchLayoutAlgorithm::searchButtonCalcSize(const RefPtr<SearchTheme>& searchTheme,
    RefPtr<SearchLayoutProperty> layoutProperty, LayoutWrapper* layoutWrapper, float maxFontScale, float minFontScale)
{
    // calculate theme space from search button to font
    auto spaceHeight = searchTheme->GetHeight().ConvertToPx() - 2 * searchTheme->GetSearchButtonSpace().ConvertToPx() -
                       searchTheme->GetButtonFontSize().ConvertToPxDistribute(minFontScale, maxFontScale);
    // calculate search button height
    auto defaultButtonHeight =
        searchTheme->GetHeight().ConvertToPx() - 2 * searchTheme->GetSearchButtonSpace().ConvertToPx();
    auto searchButtonHeight = std::max(defaultButtonHeight,
        layoutProperty->GetSearchButtonFontSizeValue(searchTheme->GetButtonFontSize()).ConvertToPxDistribute(
            minFontScale, maxFontScale) + spaceHeight);
    searchButtonHeight = std::min(searchButtonHeight, searchHeight_);
    CalcSize searchButtonCalcSize;
    searchButtonCalcSize.SetHeight(CalcLength(searchButtonHeight));
    return searchButtonCalcSize;
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
    auto searchHost = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(searchHost);
    auto pipeline = searchHost->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>(searchHost->GetThemeScopeId());
    CHECK_NULL_VOID(searchTheme);
    buttonLayoutProperty->UpdateUserDefinedIdealSize(searchButtonCalcSize(searchTheme, layoutProperty, layoutWrapper,
        maxFontScale_, minFontScale_));
    auto textWrapper = buttonWrapper->GetChildByIndex(0);
    if (textWrapper) {
        auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateMaxFontScale(maxFontScale_);
        textLayoutProperty->UpdateMinFontScale(minFontScale_);
    }
    if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        buttonLayoutProperty->ClearUserDefinedIdealSize(false, true);
    }

    // searchButton Measure
    auto buttonLayoutConstraint = layoutProperty->CreateChildConstraint();
    buttonWrapper->Measure(buttonLayoutConstraint);

    // deal with pixel round
    auto pixelRound = static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP) |
                        static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
    buttonLayoutProperty->UpdatePixelRound(pixelRound);

    // compute searchButton width
    auto searchWidthMax = CalcSearchWidth(layoutProperty->GetLayoutConstraint().value(), layoutWrapper);
    double searchButtonWidth = searchWidthMax * MAX_SEARCH_BUTTON_RATE;
    double curSearchButtonWidth = buttonGeometryNode->GetFrameSize().Width();
    searchButtonWidth = std::min(searchButtonWidth, curSearchButtonWidth);
    buttonLayoutConstraint.selfIdealSize.SetWidth(searchButtonWidth);
    buttonWrapper->Measure(buttonLayoutConstraint);
    searchButtonSizeMeasure_ = buttonGeometryNode->GetFrameSize();
}

void SearchLayoutAlgorithm::DividerMeasure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(DIVIDER_INDEX);
    CHECK_NULL_VOID(dividerWrapper);
    auto dividerGeometryNode = dividerWrapper->GetGeometryNode();
    CHECK_NULL_VOID(dividerGeometryNode);
    auto dividerLayoutProperty = dividerWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(dividerLayoutProperty);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(searchTheme);

    auto iconHeight = searchTheme->GetIconHeight().ConvertToPx();
    auto dividerHeight = std::min(static_cast<float>(searchHeight_), static_cast<float>(iconHeight));
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        auto defaultDividerHeight = DEFAULT_DIVIDER_HEIGHT.ConvertToPx();
        dividerHeight = std::min(static_cast<float>(searchHeight_), static_cast<float>(defaultDividerHeight));
    }
    auto dividerWidth = searchTheme->GetSearchDividerWidth();

    CalcSize dividerSize;
    dividerSize.SetWidth(CalcLength(dividerWidth));
    dividerSize.SetHeight(CalcLength(dividerHeight));
    dividerLayoutProperty->UpdateUserDefinedIdealSize(dividerSize);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    dividerWrapper->Measure(childLayoutConstraint);
    dividerSizeMeasure_ = dividerGeometryNode->GetFrameSize();
}

double SearchLayoutAlgorithm::CalcSearchAdaptHeight(LayoutWrapper* layoutWrapper)
{
    double searchHeightAdapt = 0;
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, 0);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, 0);
    auto searchTheme = pipeline->GetTheme<SearchTheme>(host->GetThemeScopeId());
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
    auto searchButtonHeight = searchButtonSizeMeasure_.Height() + 2 *
        searchTheme->GetSearchButtonSpace().ConvertToPxDistribute(minFontScale_, maxFontScale_);
    searchButtonHeight = (!searchButtonEvent->IsEnabled()) ? 0.0f : searchButtonHeight;
    // search icon height
    auto searchIconFrameHight = searchIconSizeMeasure_.Height();
    auto searchIconHeight = layoutProperty->GetSearchIconUDSizeValue(
        Dimension(searchIconFrameHight)).ConvertToPxDistribute(minFontScale_, maxFontScale_);
    searchIconHeight += searchTheme->GetHeight().ConvertToPxDistribute(minFontScale_, maxFontScale_) -
    searchTheme->GetIconHeight().ConvertToPxDistribute(minFontScale_, maxFontScale_);
    // cancel button height
    auto cancelButtonNode = cancelBtnLayoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(cancelButtonNode, 0);
    auto cancelButtonEvent = cancelButtonNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(cancelButtonEvent, 0);
    auto cancelBtnHight = cancelBtnSizeMeasure_.Height() + 2 *
        searchTheme->GetSearchButtonSpace().ConvertToPxDistribute(minFontScale_, maxFontScale_);
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
    auto searchHeight = CalcSearchHeight(constraint.value(), layoutWrapper);
    UpdateClipBounds(layoutWrapper, searchHeight);
    // update search height
    constraint->selfIdealSize.SetHeight(searchHeight);
    auto searchWidth = CalcSearchWidth(constraint.value(), layoutWrapper);
    SizeF idealSize(searchWidth, searchHeight);
    if (GreaterOrEqualToInfinity(idealSize.Width()) || GreaterOrEqualToInfinity(idealSize.Height())) {
        geometryNode->SetFrameSize(SizeF());
        return;
    }

    // update search height
    geometryNode->SetFrameSize(idealSize);
    geometryNode->SetContentSize(idealSize);
}

double SearchLayoutAlgorithm::CalcSearchWidth(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto searchConstraint = contentConstraint;
    auto idealWidth = contentConstraint.selfIdealSize.Width().value_or(contentConstraint.maxSize.Width());
    auto idealHeight = contentConstraint.selfIdealSize.Height().value_or(contentConstraint.maxSize.Height());
    auto maxIdealSize = SizeF { idealWidth, idealHeight };
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        auto frameIdealSize = maxIdealSize;
        auto finalSize = UpdateOptionSizeByCalcLayoutConstraint(static_cast<OptionalSize<float>>(frameIdealSize),
            layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
            layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
        finalSize.SetWidth(finalSize.Width().value_or(frameIdealSize.Width()));
        finalSize.SetHeight(finalSize.Height().value_or(frameIdealSize.Height()));
        maxIdealSize.UpdateSizeWhenSmaller(finalSize.ConvertToSizeT());
    }
    searchConstraint.maxSize = maxIdealSize;
    auto searchWidth = (searchConstraint.selfIdealSize.Width().has_value())
                ? std::min(searchConstraint.selfIdealSize.Width().value(), searchConstraint.maxSize.Width())
                : std::min(searchConstraint.percentReference.Width(), searchConstraint.maxSize.Width());

    const auto& calcLayoutConstraint = layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(calcLayoutConstraint, searchWidth);
    auto hasMinSize = calcLayoutConstraint->minSize->Width().has_value();
    auto hasMaxSize = calcLayoutConstraint->maxSize->Width().has_value();
    auto hasWidth = calcLayoutConstraint->selfIdealSize->Width().has_value();
    if (hasMinSize && ((hasMaxSize && searchConstraint.minSize.Width() >= searchConstraint.maxSize.Width())
        || (!hasMaxSize && !hasWidth))) {
        return searchConstraint.minSize.Width();
    }
    if (hasMinSize) {
        searchWidth = std::max(searchConstraint.minSize.Width(), static_cast<float>(searchWidth));
    }
    if (hasMaxSize) {
        searchWidth = std::min(searchConstraint.maxSize.Width(), static_cast<float>(searchWidth));
    }
    return searchWidth;
}

double SearchLayoutAlgorithm::CalcSearchHeight(
    const LayoutConstraintF& constraint, LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, 0.0);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, 0.0);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, 0.0);
    auto searchTheme = pipeline->GetTheme<SearchTheme>(host->GetThemeScopeId());
    CHECK_NULL_RETURN(searchTheme, 0.0);
    auto themeHeight = searchTheme->GetHeight().ConvertToPx();
    auto searchHeight =
        (constraint.selfIdealSize.Height().has_value()) ? constraint.selfIdealSize.Height().value() : themeHeight;
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto verticalPadding = padding.top.value_or(0.0f) + padding.bottom.value_or(0.0f);
    searchHeight = std::max(verticalPadding, static_cast<float>(searchHeight));
    auto searchHeightAdapt = searchHeight;
    if (!IsFixedHeightMode(layoutWrapper)) {
        searchHeightAdapt = std::max(searchHeightAdapt, CalcSearchAdaptHeight(layoutWrapper));
        renderContext->SetClipToBounds(false);
    } else {
        renderContext->SetClipToBounds(true);
    }

    const auto& calcLayoutConstraint = layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(calcLayoutConstraint, searchHeightAdapt);
    auto hasMinSize = calcLayoutConstraint->minSize.has_value() &&
        calcLayoutConstraint->minSize->Height().has_value();
    auto hasMaxSize = calcLayoutConstraint->maxSize.has_value() &&
        calcLayoutConstraint->maxSize->Height().has_value();
    auto hasHeight = calcLayoutConstraint->selfIdealSize.has_value() &&
        calcLayoutConstraint->selfIdealSize->Height().has_value();
    if (hasMinSize && ((hasMaxSize && constraint.minSize.Height() >= constraint.maxSize.Height())
        || (!hasMaxSize && !hasHeight))) {
        return constraint.minSize.Height();
    }
    if (hasMinSize) {
        searchHeightAdapt = std::max(constraint.minSize.Height(),
            static_cast<float>(searchHeightAdapt));
    }
    if (hasMaxSize) {
        searchHeightAdapt = std::min(constraint.maxSize.Height(),
            static_cast<float>(searchHeightAdapt));
    }
    return searchHeightAdapt;
}

void SearchLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.empty()) {
        return;
    }

    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto constraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    searchHeight_ = CalcSearchHeight(constraint.value(), layoutWrapper);
    maxFontScale_ = CalculateMaxFontScale(layoutWrapper);
    minFontScale_ = CalculateMinFontScale(layoutWrapper);

    SearchButtonMeasure(layoutWrapper);
    DividerMeasure(layoutWrapper);
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

    auto pipeline = searchButtonFrameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>(searchButtonFrameNode->GetThemeScopeId());
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
        return;
    }

    auto layoutProperty = DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    

    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>(host->GetThemeScopeId());

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto searchSize = geometryNode->GetFrameSize();
    auto searchFrameWidth = searchSize.Width();
    auto searchFrameHeight = searchSize.Height();

    LayoutSearchParams params = {
        .layoutWrapper = layoutWrapper,
        .layoutProperty = layoutProperty,
        .searchTheme = searchTheme,
        .searchFrameWidth = searchFrameWidth,
        .searchFrameHeight = searchFrameHeight,
        .isRTL = isRTL
    };

    LayoutSearchIcon(params);
    LayoutSearchButton(params);
    LayoutDivider(params);
    LayoutCancelButton(params);
    LayoutCancelImage(params);
    LayoutTextField(params);

    CalcChildrenHotZone(layoutWrapper);
}

void SearchLayoutAlgorithm::LayoutSearchIcon(const LayoutSearchParams& params)
{
    auto searchIconLeftSpace = params.searchTheme->GetSearchIconLeftSpace().ConvertToPx();
    auto imageWrapper = params.layoutWrapper->GetOrCreateChildByIndex(IMAGE_INDEX);
    CHECK_NULL_VOID(imageWrapper);
    auto imageGeometryNode = imageWrapper->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    auto iconFrameWidth = searchIconSizeMeasure_.Width();
    auto iconFrameHeight = searchIconSizeMeasure_.Height();
    auto layoutProperty = params.layoutProperty;
    auto iconRenderWidth = layoutProperty->GetSearchIconUDSizeValue(Dimension(iconFrameWidth)).ConvertToPx();

    auto padding = layoutProperty->CreatePaddingAndBorder();
    float topPadding = padding.top.value_or(0.0f);
    auto bottomPadding = padding.bottom.value_or(0.0f);
    auto leftOffset = padding.left.value_or(0.0f);
    auto rightOffset = padding.right.value_or(0.0f);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        leftOffset = 0.0f;
    }
    float iconHorizontalOffset = params.isRTL ?
        params.searchFrameWidth - searchIconLeftSpace - iconRenderWidth - rightOffset :
        leftOffset + searchIconLeftSpace + (iconRenderWidth - iconFrameWidth) / 2.0f;

    auto searchIconConstraint = imageWrapper->GetLayoutProperty()->GetLayoutConstraint();
    auto iconUserHeight =
        searchIconConstraint->selfIdealSize.Height().value_or(params.searchTheme->GetIconHeight().ConvertToPx());
    float imageVerticalOffset = topPadding;
    if (NearEqual(iconUserHeight, iconFrameHeight)) {
        float iconInterval = (params.searchFrameHeight - iconUserHeight) / 2;
        if (topPadding <= iconInterval && bottomPadding <= iconInterval) {
            imageVerticalOffset = iconInterval;
        } else if (topPadding <= iconInterval && bottomPadding > iconInterval) {
            imageVerticalOffset = params.searchFrameHeight - (bottomPadding + iconFrameHeight);
        }
    }
    OffsetF imageOffset(iconHorizontalOffset, imageVerticalOffset);
    imageGeometryNode->SetMarginFrameOffset(imageOffset);
    imageWrapper->Layout();
}

void SearchLayoutAlgorithm::LayoutSearchButton(const LayoutSearchParams& params)
{
    auto searchButtonSpace = params.searchTheme->GetSearchButtonSpace().ConvertToPx();

    auto searchButtonWrapper = params.layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
    CHECK_NULL_VOID(searchButtonWrapper);
    auto searchButtonGeometryNode = searchButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(searchButtonGeometryNode);
    auto searchButtonFrameSize = searchButtonGeometryNode->GetFrameSize();
    float searchButtonVerticalOffset = (params.searchFrameHeight - searchButtonFrameSize.Height()) / TWO;

    auto padding = params.layoutProperty->CreatePaddingAndBorder();
    auto leftOffset = padding.left.value_or(0.0f);
    auto rightOffset = padding.right.value_or(0.0f);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        rightOffset = 0.0f;
    }
    float searchButtonHorizontalOffset = 0.0f;
    if (params.isRTL) {
        searchButtonHorizontalOffset = leftOffset + searchButtonSpace;
    } else {
        searchButtonHorizontalOffset =
            params.searchFrameWidth - searchButtonFrameSize.Width() - searchButtonSpace - rightOffset;
        searchButtonHorizontalOffset = std::max(searchButtonHorizontalOffset, 0.0f);
    }
    auto searchButtonOffset = OffsetF(searchButtonHorizontalOffset, searchButtonVerticalOffset);
    searchButtonGeometryNode->SetMarginFrameOffset(searchButtonOffset);
    searchButtonWrapper->Layout();
}

void SearchLayoutAlgorithm::LayoutDivider(const LayoutSearchParams& params)
{
    auto searchButtonSpace = params.searchTheme->GetSearchButtonSpace().ConvertToPx();
    auto dividerSpace = params.searchTheme->GetDividerSideSpace().ConvertToPx();

    auto dividerWrapper = params.layoutWrapper->GetOrCreateChildByIndex(DIVIDER_INDEX);
    CHECK_NULL_VOID(dividerWrapper);
    auto dividerGeometryNode = dividerWrapper->GetGeometryNode();
    CHECK_NULL_VOID(dividerGeometryNode);
    auto dividerFrameSize = dividerGeometryNode->GetFrameSize();

    auto padding = params.layoutProperty->CreatePaddingAndBorder();
    auto leftOffset = padding.left.value_or(0.0f);
    auto rightOffset = padding.right.value_or(0.0f);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        rightOffset = 0.0f;
    }
    auto buttonWidth = searchButtonSizeMeasure_.Width();

    float dividerHorizontalOffset = 0.0f;
    if (params.isRTL) {
        dividerHorizontalOffset =
            leftOffset + buttonWidth + dividerSpace + searchButtonSpace + dividerFrameSize.Width() / 2.0f;
    } else {
        dividerHorizontalOffset = params.searchFrameWidth - buttonWidth - dividerSpace - searchButtonSpace -
                                  dividerFrameSize.Width() / 2.0f - rightOffset;
    }
    dividerHorizontalOffset = std::max(dividerHorizontalOffset, 0.0f);
    auto dividerVerticalOffset = (params.searchFrameHeight - dividerFrameSize.Height()) / 2.0f;
    auto dividerOffset = OffsetF(dividerHorizontalOffset, dividerVerticalOffset);
    dividerGeometryNode->SetMarginFrameOffset(dividerOffset);
    dividerWrapper->Layout();
}


void SearchLayoutAlgorithm::LayoutCancelButton(const LayoutSearchParams& params)
{
    auto searchTheme = params.searchTheme;
    CHECK_NULL_VOID(searchTheme);
    auto dividerSideSpace = searchTheme->GetDividerSideSpace().ConvertToPx();
    auto dividerWidth = searchTheme->GetSearchDividerWidth().ConvertToPx();
    auto borderWidth = searchTheme->GetBorderWidth().ConvertToPx();

    auto cancelButtonWrapper = params.layoutWrapper->GetOrCreateChildByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButtonWrapper);
    auto cancelButtonGeometryNode = cancelButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(cancelButtonGeometryNode);
    auto cancelButtonFrameSize = cancelButtonGeometryNode->GetFrameSize();
    auto cancelButtonFrameWidth = cancelButtonFrameSize.Width();
    auto cancelButtonFrameHeight = cancelButtonFrameSize.Height();

    auto searchButtonWrapper = params.layoutWrapper->GetOrCreateChildByIndex(BUTTON_INDEX);
    CHECK_NULL_VOID(searchButtonWrapper);
    auto searchButtonGeometryNode = searchButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(searchButtonGeometryNode);
    auto searchButtonFrameSize = searchButtonGeometryNode->GetFrameSize();
    auto searchButtonHorizontalOffset = searchButtonGeometryNode->GetMarginFrameOffset().GetX();

    auto cancelButtonHorizontalOffset = 0;
    auto cancelButtonVerticalOffset = (params.searchFrameHeight - cancelButtonFrameHeight) / 2;
    auto searchButtonNode = searchButtonWrapper->GetHostNode();
    auto searchButtonEvent = searchButtonNode->GetEventHub<ButtonEventHub>();
    auto buttonSpace = params.searchTheme->GetSearchButtonSpace().ConvertToPx();
    auto searchButtonLayoutProperty = searchButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(searchButtonLayoutProperty);
    auto needToDisable = searchButtonLayoutProperty->GetAutoDisable().value_or(false);
    if (params.isRTL) {
        if (searchButtonEvent->IsEnabled() || needToDisable) {
            cancelButtonHorizontalOffset =
                searchButtonHorizontalOffset + (searchButtonFrameSize.Width() + TWO * dividerSideSpace + dividerWidth);
        } else {
            cancelButtonHorizontalOffset = searchButtonHorizontalOffset;
        }
    } else {
        if (searchButtonEvent->IsEnabled() || needToDisable) {
            auto cancelButtonOffsetToSearchButton = cancelButtonFrameWidth + 2 * dividerSideSpace + dividerWidth;
            cancelButtonHorizontalOffset =
                std::max(searchButtonHorizontalOffset - cancelButtonOffsetToSearchButton, 0.0);
        } else {
            cancelButtonHorizontalOffset = params.searchFrameWidth - cancelButtonFrameWidth - buttonSpace - borderWidth;
        }
    }
    auto cancelButtonOffset = OffsetF(cancelButtonHorizontalOffset, cancelButtonVerticalOffset);
    cancelButtonGeometryNode->SetMarginFrameOffset(cancelButtonOffset);
    cancelButtonWrapper->Layout();
}

void SearchLayoutAlgorithm::LayoutCancelImage(const LayoutSearchParams& params)
{
    auto cancelImageWrapper = params.layoutWrapper->GetOrCreateChildByIndex(CANCEL_IMAGE_INDEX);
    CHECK_NULL_VOID(cancelImageWrapper);
    auto cancelImageGeometryNode = cancelImageWrapper->GetGeometryNode();
    CHECK_NULL_VOID(cancelImageGeometryNode);
    auto cancelImageFrameSize = cancelImageGeometryNode->GetFrameSize();
    auto cancelImageFrameWidth = cancelImageFrameSize.Width();
    auto cancelImageFrameHeight = cancelImageFrameSize.Height();

    auto cancelButtonWrapper = params.layoutWrapper->GetOrCreateChildByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_VOID(cancelButtonWrapper);
    auto cancelButtonGeometryNode = cancelButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(cancelButtonGeometryNode);
    auto cancelButtonHorizontalOffset = cancelButtonGeometryNode->GetMarginFrameOffset().GetX();
    auto cancelButtonFrameWidth = cancelButtonGeometryNode->GetFrameSize().Width();

    auto cancelImageVerticalOffset = (params.searchFrameHeight - cancelImageFrameHeight) / 2;
    auto cancelButtonImageCenterOffset = (cancelButtonFrameWidth - cancelImageFrameWidth) / 2;
    auto cancelImageHorizontalOffset = cancelButtonHorizontalOffset + cancelButtonImageCenterOffset;
    auto cancelImageOffset = OffsetF(cancelImageHorizontalOffset, cancelImageVerticalOffset);
    cancelImageGeometryNode->SetMarginFrameOffset(cancelImageOffset);
    cancelImageWrapper->Layout();
}

void SearchLayoutAlgorithm::LayoutTextField(const LayoutSearchParams& params)
{
    auto searchIconLeftSpace = params.searchTheme->GetSearchIconLeftSpace().ConvertToPx();
    auto searchIconRightSpace = params.searchTheme->GetSearchIconRightSpace().ConvertToPx();
    auto searchIconWidth = searchIconSizeMeasure_.Width();
    auto layoutProperty = DynamicCast<SearchLayoutProperty>(params.layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();

    auto textFieldWrapper = params.layoutWrapper->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_VOID(textFieldWrapper);
    auto textFieldGeometryNode = textFieldWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);

    auto hostGeometryNode = params.layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(hostGeometryNode);

    auto textFieldHorizontalOffset = 0;
    if (params.isRTL) {
        auto rightOffset = searchIconWidth + searchIconLeftSpace
            + searchIconRightSpace + padding.right.value_or(0.0f);
        textFieldHorizontalOffset = hostGeometryNode->GetFrameSize().Width()
            - rightOffset - textFieldGeometryNode->GetFrameSize().Width();
    } else {
        textFieldHorizontalOffset = searchIconWidth + searchIconLeftSpace
            + searchIconRightSpace + padding.left.value_or(0.0f);
    }

    auto textFieldVerticalOffset = (params.searchFrameHeight - textFieldGeometryNode->GetFrameSize().Height()) / 2;
    textFieldGeometryNode->SetMarginFrameOffset(OffsetF(textFieldHorizontalOffset, textFieldVerticalOffset));
    textFieldWrapper->Layout();
}

void SearchLayoutAlgorithm::UpdateClipBounds(LayoutWrapper* layoutWrapper, float height)
{
    if (!IsFixedHeightMode(layoutWrapper)) {
        return;
    }
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = AceType::DynamicCast<SearchLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->HasSearchIconUDSize() && !layoutProperty->HasCancelButtonUDSize()) {
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto searchTheme = pipeline->GetTheme<SearchTheme>(host->GetThemeScopeId());
        CHECK_NULL_VOID(searchTheme);
        auto defaultImageHeight = searchTheme->GetIconSize().ConvertToPx();
        auto isClip = LessNotEqual(height, defaultImageHeight);
        renderContext->SetClipToBounds(isClip);
        return;
    }
    auto isClip = false;
    if (layoutProperty->HasSearchIconUDSize()) {
        isClip = isClip || LessNotEqual(height, layoutProperty->GetSearchIconUDSizeValue().ConvertToPx());
    }
    if (layoutProperty->HasCancelButtonUDSize()) {
        isClip = isClip || LessNotEqual(height, layoutProperty->GetCancelButtonUDSizeValue().ConvertToPx());
    }
    renderContext->SetClipToBounds(isClip);
}
double SearchLayoutAlgorithm::CalcSymbolIconHeight(
    LayoutWrapper* layoutWrapper, int32_t index, double defaultImageHeight)
{
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(hostNode, defaultImageHeight);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_RETURN(pipeline, defaultImageHeight);
    auto searchPattern = hostNode->GetPattern<SearchPattern>();
    CHECK_NULL_RETURN(searchPattern, defaultImageHeight);
    auto searchNode = searchPattern->GetSearchNode();
    CHECK_NULL_RETURN(searchNode, defaultImageHeight);

    auto iconNode = AceType::DynamicCast<FrameNode>(hostNode->GetChildAtIndex(index));
    CHECK_NULL_RETURN(iconNode, defaultImageHeight);
    auto symbolLayoutProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(symbolLayoutProperty, defaultImageHeight);
    symbolLayoutProperty->UpdateMaxFontScale(maxFontScale_);
    symbolLayoutProperty->UpdateMinFontScale(minFontScale_);
    auto defaultSymbolIconSize =
        (index == IMAGE_INDEX ? searchNode->GetSearchSymbolIconSize() : searchNode->GetCancelSymbolIconSize());
    auto iconSize = symbolLayoutProperty->GetFontSize().value_or(defaultSymbolIconSize);

    return iconSize.ConvertToPxDistribute(minFontScale_, maxFontScale_);
}
} // namespace OHOS::Ace::NG
