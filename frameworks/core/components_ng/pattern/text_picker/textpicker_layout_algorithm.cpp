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

#include "core/components_ng/pattern/text_picker/textpicker_layout_algorithm.h"

#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

namespace {
const int32_t DIVIDER_SIZE = 2;
const float PICKER_HEIGHT_HALF = 3.5f;
const float ITEM_HEIGHT_HALF = 2.0f;
const int32_t MAX_HALF_DISPLAY_COUNT = 2;
const int32_t BUFFER_NODE_NUMBER = 2;
const float DOUBLE_VALUE = 2.0f;
constexpr double PERCENT_100 = 100.0;
constexpr double PERCENT_120 = 1.2f;

GradientColor CreatePercentGradientColor(float percent, Color color)
{
    NG::GradientColor gredient = GradientColor(color);
    gredient.SetDimension(CalcDimension(percent * PERCENT_100, DimensionUnit::PERCENT));
    return gredient;
}
} // namespace
void TextPickerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    SizeF frameSize = { -1.0f, -1.0f };

    auto columnNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(columnNode);
    auto blendNode = DynamicCast<FrameNode>(columnNode->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto pickerNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(pickerNode);
    auto layoutProperty = pickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto textPickerPattern = pickerNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);

    GetColumnSize(layoutProperty, pickerTheme, dialogTheme, frameSize, pickerNode);

    textPickerPattern->CheckAndUpdateColumnSize(frameSize, columnNode, NeedAdaptForAging());
    pickerItemHeight_ = frameSize.Height();
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
    auto layoutChildConstraint = blendNode->GetLayoutProperty()->CreateChildConstraint();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutChildConstraint);
    }
    MeasureText(layoutWrapper, frameSize);
    float gradientPercent = GetGradientPercent(layoutProperty, textPickerPattern, frameSize, pickerTheme);
    InitGradient(gradientPercent, blendNode, columnNode);
}

float TextPickerLayoutAlgorithm::GetGradientPercent(const RefPtr<TextPickerLayoutProperty>& layoutProperty,
    const RefPtr<TextPickerPattern>& textPickerPattern, SizeF& frameSize, const RefPtr<PickerTheme>& pickerTheme)
{
    float gradientPercent = 0.0f;
    bool isGradientHeight = layoutProperty->HasGradientHeight();
    if (LessNotEqual(textPickerPattern->GetGradientHeight().ConvertToPx(), 0.0)) {
        isGradientHeight = false;
    }
    if (isGradientHeight) {
        auto gradientheight = textPickerPattern->GetGradientHeight();
        float gradientheightValue = 0.0f;
        if (gradientheight.Unit() == DimensionUnit::PERCENT) {
            gradientheightValue = frameSize.Height() * gradientheight.Value() / DOUBLE_VALUE;
        } else {
            gradientheightValue = gradientheight.ConvertToPx();
        }
        if ((frameSize.Height() / DOUBLE_VALUE) < gradientheightValue) {
            gradientPercent = static_cast<float>
                (pickerTheme->GetGradientHeight().ConvertToPx()) * gradientFontScale_ / frameSize.Height();
        } else {
            gradientPercent = gradientheightValue / frameSize.Height();
        }
    } else {
        gradientPercent = static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx()) * gradientFontScale_ /
                          frameSize.Height();
    }
    return gradientPercent;
}

void TextPickerLayoutAlgorithm::GetColumnSize(const RefPtr<TextPickerLayoutProperty>& layoutProperty,
    const RefPtr<PickerTheme>& pickerTheme, const RefPtr<DialogTheme>& dialogTheme, SizeF& frameSize,
    const RefPtr<FrameNode>& pickerNode)
{
    float pickerHeight = 0.0f;
    isDefaultPickerItemHeight_ = layoutProperty->HasDefaultPickerItemHeight();
    if (isDefaultPickerItemHeight_) {
        auto defaultPickerItemHeightValue = layoutProperty->GetDefaultPickerItemHeightValue();
        if (LessOrEqual(defaultPickerItemHeightValue.Value(), 0.0)) {
            isDefaultPickerItemHeight_ = false;
        } else {
            UpdateDefaultPickerItemHeightLPX(pickerNode, defaultPickerItemHeightValue);
        }
    }

    uint32_t showCount_ = pickerTheme->GetShowCountPortrait();
    if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount_ = pickerTheme->GetShowCountLandscape();
    }
    auto textPickerPattern = pickerNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    auto isUserSetDividerSpacingFont = textPickerPattern->GetIsUserSetDividerSpacingFont();
    auto isUserSetGradientFont = textPickerPattern->GetIsUserSetGradientFont();
    if (isUserSetDividerSpacingFont) {
        dividerSpacingFontScale_ = ReCalcItemHeightScale(textPickerPattern->GetDividerSpacing());
        textPickerPattern->SetPaintDividerSpacing(dividerSpacingFontScale_);
    }

    if (isUserSetGradientFont) {
        gradientFontScale_ = ReCalcItemHeightScale(textPickerPattern->GetGradientHeight(), false);
    }

    if (isDefaultPickerItemHeight_) {
        pickerHeight = static_cast<float>(defaultPickerItemHeight_ * showCount_);
    } else {
        pickerHeight = static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx() *
                                              (static_cast<int32_t>(showCount_) - 1) * gradientFontScale_ +
                                          pickerTheme->GetDividerSpacing().ConvertToPx() * dividerSpacingFontScale_);
    }

    auto layoutConstraint = pickerNode->GetLayoutProperty()->GetLayoutConstraint();
    float pickerWidth = static_cast<float>((pickerTheme->GetDividerSpacing() * DIVIDER_SIZE).ConvertToPx());

    if (textPickerPattern->GetIsShowInDialog()) {
        float dialogButtonHeight =
            static_cast<float>((pickerTheme->GetButtonHeight() + dialogTheme->GetDividerHeight() +
                                dialogTheme->GetDividerPadding().Bottom() + pickerTheme->GetContentMarginVertical() * 2)
                                .ConvertToPx());
        pickerHeight = std::min(pickerHeight, layoutConstraint->maxSize.Height() - dialogButtonHeight);
        if (isDefaultPickerItemHeight_) {
            defaultPickerItemHeight_ = NearZero(showCount_) ? defaultPickerItemHeight_ : pickerHeight / showCount_;
            textPickerPattern->SetResizePickerItemHeight(defaultPickerItemHeight_);
            textPickerPattern->SetResizeFlag(true);
        }
    }

    frameSize.SetWidth(pickerWidth);
    frameSize.SetHeight(pickerHeight);
}

void TextPickerLayoutAlgorithm::UpdateDefaultPickerItemHeightLPX(
    const RefPtr<FrameNode>& pickerNode, const Dimension& defaultPickerItemHeightValue)
{
    if (defaultPickerItemHeight_ != defaultPickerItemHeightValue.Value() &&
        defaultPickerItemHeightValue.Unit() == DimensionUnit::LPX) {
        CHECK_NULL_VOID(pickerNode);
        auto context = pickerNode->GetContext();
        CHECK_NULL_VOID(context);
        defaultPickerItemHeight_ = context->NormalizeToPx(defaultPickerItemHeightValue);
    }
}

void TextPickerLayoutAlgorithm::InitGradient(const float& gradientPercent, const RefPtr<FrameNode> blendNode,
    const RefPtr<FrameNode> columnNode)
{
    auto blendRenderContext = blendNode->GetRenderContext();
    auto columnRenderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(blendRenderContext);
    CHECK_NULL_VOID(columnRenderContext);
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    gradient.AddColor(CreatePercentGradientColor(0, Color::TRANSPARENT));
    gradient.AddColor(CreatePercentGradientColor(gradientPercent, Color::WHITE));
    gradient.AddColor(CreatePercentGradientColor(1 - gradientPercent, Color::WHITE));
    gradient.AddColor(CreatePercentGradientColor(1, Color::TRANSPARENT));

    columnRenderContext->UpdateBackBlendMode(BlendMode::SRC_IN);
    columnRenderContext->UpdateBackBlendApplyType(BlendApplyType::OFFSCREEN);
    blendRenderContext->UpdateLinearGradient(gradient);
    blendRenderContext->UpdateBackBlendMode(BlendMode::SRC_OVER);
    blendRenderContext->UpdateBackBlendApplyType(BlendApplyType::OFFSCREEN);
}

void TextPickerLayoutAlgorithm::MeasureText(LayoutWrapper* layoutWrapper, const SizeF& size)
{
    auto totalChild = layoutWrapper->GetTotalChildCount();
    for (int32_t index = 0; index < totalChild; index++) {
        auto child = layoutWrapper->GetOrCreateChildByIndex(index);
        ChangeTextStyle(index, totalChild, size, child, layoutWrapper);
    }
}

void TextPickerLayoutAlgorithm::ChangeTextStyle(uint32_t index, uint32_t showOptionCount, const SizeF& size,
    const RefPtr<LayoutWrapper>& childLayoutWrapper, LayoutWrapper* layoutWrapper)
{
    SizeF frameSize = { -1.0f, -1.0f };
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    frameSize.SetWidth(size.Width());
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.
    auto layoutChildConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    if (isDefaultPickerItemHeight_) {
        frameSize.SetHeight(static_cast<float>(defaultPickerItemHeight_));
    } else {
        if (index == selectedIndex) {
            frameSize.SetHeight(
                static_cast<float>(pickerTheme->GetDividerSpacing().ConvertToPx() * dividerSpacingFontScale_));
        } else {
            frameSize.SetHeight(
                static_cast<float>(pickerTheme->GetGradientHeight().ConvertToPx() * gradientFontScale_));
        }
    }
    layoutChildConstraint.selfIdealSize = { frameSize.Width(), frameSize.Height() };
    childLayoutWrapper->Measure(layoutChildConstraint);
    UpdateContentSize(frameSize, childLayoutWrapper);
}

void TextPickerLayoutAlgorithm::UpdateContentSize(const SizeF& size, const RefPtr<LayoutWrapper> layoutWrapper)
{
    SizeF frameSize = size;
    CHECK_NULL_VOID(layoutWrapper->GetLayoutProperty());
    auto contentWrapper = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    CHECK_NULL_VOID(!children.empty());
    for (const auto& child : children) {
        if (child == children.back()) {
            auto frameNode  = child->GetHostNode();
            CHECK_NULL_VOID(frameNode);
            auto overlayNode = frameNode ->GetOverlayNode();
            CHECK_NULL_VOID(overlayNode);
            auto geometryNode = frameNode->GetGeometryNode();
            CHECK_NULL_VOID(geometryNode);
            auto overlayGeometryNode = overlayNode->GetGeometryNode();
            CHECK_NULL_VOID(overlayGeometryNode);
            auto textRect = geometryNode->GetFrameRect();
            contentWrapper.selfIdealSize = { frameSize.Width() - textRect.Left(), textRect.Height() };
            child->Measure(contentWrapper);
            auto textFrameSize_ = geometryNode->GetMarginFrameSize();
            overlayGeometryNode->SetFrameSize(textFrameSize_);
            overlayNode->Layout();
        }
    }
}

void TextPickerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto layoutProperty = AceType::DynamicCast<LinearLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto size = geometryNode->GetFrameSize();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    float childStartCoordinate = 0.0f;

    if (isDefaultPickerItemHeight_) {
        childStartCoordinate +=
            static_cast<float>(size.Height() / ITEM_HEIGHT_HALF - defaultPickerItemHeight_ * PICKER_HEIGHT_HALF);
        halfDisplayCounts_ =
            std::clamp(static_cast<int32_t>(
                           std::ceil((size.Height() / ITEM_HEIGHT_HALF - defaultPickerItemHeight_ / ITEM_HEIGHT_HALF) /
                                     defaultPickerItemHeight_)),
                0, MAX_HALF_DISPLAY_COUNT);
    } else {
        childStartCoordinate += static_cast<float>(pickerItemHeight_ / ITEM_HEIGHT_HALF -
            pickerTheme->GetGradientHeight().ConvertToPx() * gradientFontScale_* (ITEM_HEIGHT_HALF + 1) -
            pickerTheme->GetDividerSpacing().ConvertToPx() * dividerSpacingFontScale_ / ITEM_HEIGHT_HALF);
        halfDisplayCounts_ = std::clamp(
            static_cast<int32_t>(std::ceil((pickerItemHeight_ / ITEM_HEIGHT_HALF -
                                               pickerTheme->GetDividerSpacing().ConvertToPx() / ITEM_HEIGHT_HALF) /
                                           pickerTheme->GetGradientHeight().ConvertToPx())),
            0, MAX_HALF_DISPLAY_COUNT);
    }
    int32_t i = 0;
    int32_t showCount = static_cast<int32_t>(pickerTheme->GetShowOptionCount()) + BUFFER_NODE_NUMBER;
    for (const auto& child : children) {
        if (i >= showCount || i >= static_cast<int32_t>(currentOffset_.size())) {
            break;
        }
        auto childGeometryNode = child->GetGeometryNode();
        auto childSize = childGeometryNode->GetMarginFrameSize();
        auto childOffset =
            OffsetF(0.0, childStartCoordinate + static_cast<float>(currentOffset_[i++]) + padding.Offset().GetY());
        childGeometryNode->SetMarginFrameOffset(childOffset);
        child->Layout();
        childStartCoordinate += childSize.Height();
    }
}

bool TextPickerLayoutAlgorithm::NeedAdaptForAging()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);

    if (GreatOrEqual(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale())) {
        return true;
    }
    return false;
}

const Dimension TextPickerLayoutAlgorithm::AdjustFontSizeScale(const Dimension& fontSizeValue, double fontScale)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);

    double adjustedScale = std::clamp(fontScale, pickerTheme->GetNormalFontScale(),
        pickerTheme->GetMaxTwoFontScale());
    auto result = 0.0_vp;
    if (!NearZero(fontScale)) {
        result =  fontSizeValue / fontScale * adjustedScale;
    }
    return result;
}

float TextPickerLayoutAlgorithm::ReCalcItemHeightScale(const Dimension& userSetHeight, bool isDividerSpacing)
{
    auto fontScale = 1.0f;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontScale);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontScale);
    auto systemFontScale = static_cast<double>(pipeline->GetFontScale());
    auto themePadding = pickerTheme->GetPickerDialogFontPadding();
    auto userSetHeightValue = AdjustFontSizeScale(userSetHeight, systemFontScale).ConvertToPx();
    double adjustedScale =
        std::clamp(systemFontScale, pickerTheme->GetNormalFontScale(), pickerTheme->GetMaxTwoFontScale());
    if (NearZero(adjustedScale)) {
        return fontScale;
    }
    userSetHeightValue = userSetHeightValue / adjustedScale * PERCENT_120 + (themePadding.ConvertToPx() * DIVIDER_SIZE);
    auto themeHeightLimit =
        isDividerSpacing ? pickerTheme->GetDividerSpacingLimit() : pickerTheme->GetGradientHeightLimit();
    auto themeHeight = isDividerSpacing ? pickerTheme->GetDividerSpacing() : pickerTheme->GetGradientHeight();
    if (GreatOrEqualCustomPrecision(userSetHeightValue, themeHeightLimit.ConvertToPx())) {
        userSetHeightValue = themeHeightLimit.ConvertToPx();
    } else {
        userSetHeightValue = std::max(userSetHeightValue, themeHeight.ConvertToPx());
    }

    if (NearZero(themeHeight.ConvertToPx())) {
        return fontScale;
    }

    fontScale = std::max(static_cast<float>(userSetHeightValue / themeHeight.ConvertToPx()), fontScale);
    return fontScale;
}

} // namespace OHOS::Ace::NG
