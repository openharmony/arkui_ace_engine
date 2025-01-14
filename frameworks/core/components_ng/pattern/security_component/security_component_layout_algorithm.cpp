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

#include "core/components_ng/pattern/security_component/security_component_layout_algorithm.h"

#include "core/components/common/properties/alignment.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/security_component/security_component_log.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "unicode/uchar.h"

namespace {
constexpr float HALF = 2.0f;
constexpr float TEXT_OUT_OF_RANGE_PERCENT = 0.3f; // 30%
constexpr float TEXT_OUT_OF_WIDTH_PERCENT = 0.1f; // 10%
constexpr float RANGE_RATIO = 1.414f;
}

namespace OHOS::Ace::NG {
RefPtr<LayoutWrapper> SecurityComponentLayoutAlgorithm::GetChildWrapper(LayoutWrapper* layoutWrapper,
    const std::string& tag)
{
    int32_t count = layoutWrapper->GetTotalChildCount();
    for (int32_t i = 0; i < count; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        if (childWrapper == nullptr) {
            continue;
        }
        if (childWrapper->GetHostTag() == tag) {
            return childWrapper;
        }
    }
    return nullptr;
}

void SecurityComponentLayoutAlgorithm::UpdateChildPosition(LayoutWrapper* layoutWrapper, const std::string& tag,
    OffsetF& offset)
{
    auto childWrapper = GetChildWrapper(layoutWrapper, tag);
    CHECK_NULL_VOID(childWrapper);
    auto childNode = childWrapper->GetHostNode();
    CHECK_NULL_VOID(childNode);
    auto geometryNode = childNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetMarginFrameOffset(
        OffsetF(std::round(offset.GetX()), std::round(offset.GetY())));
}

static LayoutConstraintF CreateDefaultChildConstraint(
    RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty)
{
    auto constraint = securityComponentProperty->CreateChildConstraint();
    SizeT<float> maxSize { Infinity<float>(), Infinity<float>() };
    constraint.maxSize = maxSize;
    return constraint;
}

void SecurityComponentLayoutAlgorithm::MeasureButton(LayoutWrapper* layoutWrapper,
    RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty)
{
    auto buttonWrapper = GetChildWrapper(layoutWrapper, V2::BUTTON_ETS_TAG);
    CHECK_NULL_VOID(buttonWrapper);
    auto buttonLayoutProperty = DynamicCast<ButtonLayoutProperty>(buttonWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto buttonConstraint = CreateDefaultChildConstraint(securityComponentProperty);
    if (securityComponentProperty->GetBackgroundType() == static_cast<int32_t>(ButtonType::CIRCLE)) {
        buttonConstraint.selfIdealSize.SetSize(SizeF(std::min(componentWidth_, componentHeight_),
            std::min(componentWidth_, componentHeight_)));
        if (GreatNotEqual(componentWidth_, componentHeight_)) {
            left_.ShrinkWidth((componentWidth_ / HALF) - (componentHeight_ / HALF));
        } else if (GreatNotEqual(componentHeight_, componentWidth_)) {
            top_.ShrinkHeight((componentHeight_ / HALF) - (componentWidth_ / HALF));
        }
        componentWidth_ = componentHeight_ = std::min(componentWidth_, componentHeight_);
    } else {
        buttonConstraint.selfIdealSize.SetSize(SizeF(componentWidth_, componentHeight_));
    }

    buttonWrapper->Measure(std::optional<LayoutConstraintF>(buttonConstraint));
    auto geometryNode = buttonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(SizeF(componentWidth_, componentHeight_));
}

void SecurityComponentLayoutAlgorithm::InitPadding(RefPtr<SecurityComponentLayoutProperty>& property)
{
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);

    double borderWidth = property->GetBackgroundBorderWidth().value_or(Dimension(0.0)).ConvertToPx();
    double size = property->GetBackgroundLeftPadding().value_or(theme->GetBackgroundLeftPadding()).ConvertToPx() +
        borderWidth;
    left_.Init(false,
        property->GetBackgroundLeftPadding().has_value(), size, borderWidth);

    size = property->GetBackgroundTopPadding().value_or(theme->GetBackgroundTopPadding()).ConvertToPx() +
        borderWidth;
    top_.Init(true,
        property->GetBackgroundTopPadding().has_value(), size, borderWidth);

    size = property->GetBackgroundRightPadding().value_or(theme->GetBackgroundRightPadding()).ConvertToPx() +
        borderWidth;
    right_.Init(false,
        property->GetBackgroundRightPadding().has_value(), size, borderWidth);

    size = property->GetBackgroundBottomPadding().value_or(theme->GetBackgroundBottomPadding()).ConvertToPx() +
        borderWidth;
    bottom_.Init(true,
        property->GetBackgroundBottomPadding().has_value(), size, borderWidth);

    size = property->GetTextIconSpace().value_or(theme->GetTextIconSpace()).ConvertToPx();
    middle_.Init(isVertical_, property->GetTextIconSpace().has_value(), size, 0.0);
}

void SecurityComponentLayoutAlgorithm::UpdateTextSize()
{
    auto minWidth = std::min(maxWidth_, componentWidth_);
    if (!NearEqual(idealWidth_, 0.0)) {
        minWidth = std::min(minWidth, idealWidth_);
    }
    float leftSpace;
    if (isVertical_) {
        leftSpace = left_.width_ + icon_.width_ + right_.width_;
    } else {
        leftSpace = left_.width_ + middle_.width_ + icon_.width_ + right_.width_;
    }
    text_.DoMeasure(isVertical_, minWidth, leftSpace);
}

double SecurityComponentLayoutAlgorithm::ShrinkWidth(double diff)
{
    // first shrink left and right padding
    double remain = left_.ShrinkWidth(diff / HALF);
    remain = right_.ShrinkWidth(remain + (diff / HALF));
    remain = left_.ShrinkWidth(remain);
    if (NearEqual(remain, 0.0)) {
        MeasureIntegralSize();
        return componentWidth_;
    }

    // if horizontal shrink IconTextSpace
    remain = middle_.ShrinkWidth(remain);
    if (NearEqual(remain, 0.0)) {
        MeasureIntegralSize();
        return componentWidth_;
    }

    double iconWidth = icon_.width_;
    double textWidth = text_.width_;
    if (isVertical_) {
        // Shrink max width, then shrink another proportionally if vertical
        if (GreatNotEqual(textWidth, iconWidth)) {
            double textRemain = text_.ShrinkWidth(remain);
            double iconRemain = (remain - textRemain) * iconWidth / textWidth;
            icon_.ShrinkWidth(iconRemain);
        } else {
            double iconRemain = icon_.ShrinkWidth(remain);
            double textRemain = (remain - iconRemain) * textWidth / iconWidth;
            text_.ShrinkWidth(textRemain);
        }
    } else {
        // Shrink proportional text and icon if horizontal
        double iconRemain = iconWidth * remain / (iconWidth + textWidth);
        double textRemain = textWidth * remain / (iconWidth + textWidth);
        double resIcon = icon_.ShrinkWidth(iconRemain);
        double resText = text_.ShrinkWidth(textRemain);
        if (!NearEqual(resIcon, 0.0)) {
            text_.ShrinkWidth(resIcon);
        } else if (!NearEqual(resText, 0.0)) {
            icon_.ShrinkWidth(resText);
        }
    }
    UpdateTextSize();
    MeasureIntegralSize();
    return componentWidth_;
}

double SecurityComponentLayoutAlgorithm::EnlargeWidth(double diff)
{
    double remain = left_.EnlargeWidth(diff / HALF);
    remain = right_.EnlargeWidth(remain + (diff / HALF));
    remain = left_.EnlargeWidth(remain);
    if (GreatNotEqual(remain, 0.0) && !isVertical_) {
        middle_.EnlargeWidth(remain);
    }
    MeasureIntegralSize();
    return componentWidth_;
}

double SecurityComponentLayoutAlgorithm::ShrinkHeight(double diff)
{
    // first shrink left and right padding
    double remain = top_.ShrinkHeight(diff / HALF);
    remain = bottom_.ShrinkHeight(remain + (diff / HALF));
    remain = top_.ShrinkHeight(remain);
    if (NearEqual(remain, 0.0)) {
        MeasureIntegralSize();
        return componentHeight_;
    }

    // if vertical shrink IconTextSpace
    remain = middle_.ShrinkHeight(remain);
    if (NearEqual(remain, 0.0)) {
        MeasureIntegralSize();
        return componentHeight_;
    }

    double iconHeight = icon_.height_;
    double textHeight = text_.height_;
    if (!isVertical_) {
         // Shrink max width, then shrink another proportionally if horizontal
        if (GreatNotEqual(textHeight, iconHeight)) {
            double textRemain = text_.ShrinkHeight(remain);
            double iconRemain = (remain - textRemain) * iconHeight / textHeight;
            icon_.ShrinkHeight(iconRemain);
        } else {
            double iconRemain = icon_.ShrinkHeight(remain);
            double textRemain = (remain - iconRemain) * textHeight / iconHeight;
            text_.ShrinkHeight(textRemain);
        }
    } else {
        double iconRemain = iconHeight * remain / (iconHeight + textHeight);
        double textRemain = textHeight * remain / (iconHeight + textHeight);
        double resIcon = icon_.ShrinkHeight(iconRemain);
        double resText = text_.ShrinkHeight(textRemain);
        if (!NearEqual(resIcon, 0.0)) {
            text_.ShrinkHeight(resIcon);
        } else if (!NearEqual(resText, 0.0)) {
            icon_.ShrinkHeight(resText);
        }
    }
    isNeedReadaptWidth_ = true;
    MeasureIntegralSize();
    return componentHeight_;
}

double SecurityComponentLayoutAlgorithm::EnlargeHeight(double diff)
{
    double remain = top_.EnlargeHeight(diff / HALF);
    remain = bottom_.EnlargeHeight(remain + (diff / HALF));
    remain = top_.EnlargeHeight(remain);
    if (GreatNotEqual(remain, 0.0) && isVertical_) {
        middle_.EnlargeHeight(remain);
    }
    MeasureIntegralSize();
    return componentHeight_;
}

void SecurityComponentLayoutAlgorithm::AdaptWidth()
{
    if (idealWidth_ != 0.0) {
        if (componentWidth_ > idealWidth_) {
            ShrinkWidth(componentWidth_ - idealWidth_);
        } else if (componentWidth_ < idealWidth_) {
            EnlargeWidth(idealWidth_ - componentWidth_);
        }
        return;
    }

    if (componentWidth_ > maxWidth_) {
        ShrinkWidth(componentWidth_ - maxWidth_);
    } else if (componentWidth_ < minWidth_) {
        EnlargeWidth(minWidth_ - componentWidth_);
    }
}

void SecurityComponentLayoutAlgorithm::AdaptHeight()
{
    if (idealHeight_ != 0.0) {
        if (componentHeight_ > idealHeight_) {
            ShrinkHeight(componentHeight_ - idealHeight_);
        } else if (componentHeight_ < idealHeight_) {
            EnlargeHeight(idealHeight_ - componentHeight_);
        }
        return;
    }
    if (componentHeight_ > maxHeight_) {
        ShrinkHeight(componentHeight_ - maxHeight_);
    } else if (componentHeight_ < minHeight_) {
        EnlargeHeight(minHeight_ - componentHeight_);
    }
}

void SecurityComponentLayoutAlgorithm::MeasureIntegralSize()
{
    if (isVertical_) {
        double contextWidth = std::max(text_.width_, icon_.width_);
        componentHeight_ = top_.height_ + text_.height_ +
            middle_.height_ + icon_.height_ + bottom_.height_;
        componentWidth_ = left_.width_ + contextWidth + right_.width_;
    } else {
        double contextHeight = std::max(text_.height_, icon_.height_);
        componentHeight_ = top_.height_ + contextHeight + bottom_.height_;
        componentWidth_ = left_.width_ + icon_.width_ +
            middle_.width_ + text_.width_ + right_.width_;
    }
}

void SecurityComponentLayoutAlgorithm::UpdateVerticalOffset(OffsetF& offsetIcon,
    OffsetF& offsetText, SizeF& childSize)
{
    offsetText = offsetIcon + OffsetF(0.0, icon_.height_ + middle_.height_);
    if (icon_.width_ > text_.width_) {
        offsetText += OffsetF((icon_.width_ - text_.width_) / HALF, 0.0);
        childSize += SizeF(icon_.width_, 0.0);
    } else {
        offsetIcon += OffsetF((text_.width_ - icon_.width_) / HALF, 0.0);
        childSize += SizeF(text_.width_, 0.0);
    }
    childSize += SizeF(0.0, icon_.height_ + middle_.height_ + text_.height_);
}

void SecurityComponentLayoutAlgorithm::UpdateHorizontalOffset(LayoutWrapper* layoutWrapper,
    OffsetF& offsetIcon, OffsetF& offsetText, SizeF& childSize)
{
    if (GetTextDirection(layoutWrapper) == TextDirection::RTL) {
        offsetIcon = offsetText +
            OffsetF(text_.width_ + middle_.width_, 0.0);
    } else {
        offsetText = offsetIcon +
            OffsetF(icon_.width_ + middle_.width_, 0.0);
    }
    if (icon_.height_ > text_.height_) {
        offsetText +=
            OffsetF(0.0, (icon_.height_ - text_.height_) / HALF);
        childSize += SizeF(0.0, icon_.height_);
    } else {
        offsetIcon +=
            OffsetF(0.0, (text_.height_ - icon_.height_) / HALF);
        childSize += SizeF(0.0, text_.height_);
    }
    childSize += SizeF(icon_.width_ + middle_.width_ + text_.width_, 0.0);
}

Alignment SecurityComponentLayoutAlgorithm::ParseAlignmentRTL(LayoutWrapper* layoutWrapper, Alignment align)
{
    if (GetTextDirection(layoutWrapper) != TextDirection::RTL) {
        return align;
    }
    if (align == Alignment::TOP_LEFT) {
        return Alignment::TOP_RIGHT;
    }
    if (align == Alignment::CENTER_LEFT) {
        return Alignment::CENTER_RIGHT;
    }
    if (align == Alignment::BOTTOM_LEFT) {
        return Alignment::BOTTOM_RIGHT;
    }
    if (align == Alignment::TOP_RIGHT) {
        return Alignment::TOP_LEFT;
    }
    if (align == Alignment::CENTER_RIGHT) {
        return Alignment::CENTER_LEFT;
    }
    if (align == Alignment::BOTTOM_RIGHT) {
        return Alignment::BOTTOM_LEFT;
    }
    return align;
}

void SecurityComponentLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    OffsetF offsetIcon = OffsetF(0.0, 0.0);
    OffsetF offsetText = OffsetF(0.0, 0.0);
    SizeF childSize = SizeF(0.0, 0.0);
    if (isVertical_) {
        UpdateVerticalOffset(offsetIcon, offsetText, childSize);
    } else {
        UpdateHorizontalOffset(layoutWrapper, offsetIcon, offsetText, childSize);
    }
    auto property = AceType::DynamicCast<SecurityComponentLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(property);
    if (property->GetAlignment().has_value()) {
        auto left = LessNotEqual(left_.width_, left_.defaultWidth_) ? left_.width_ : left_.defaultWidth_;
        auto right = LessNotEqual(right_.width_, right_.defaultWidth_) ? right_.width_ : right_.defaultWidth_;
        auto top = LessNotEqual(top_.height_, top_.defaultHeight_) ? top_.height_ : top_.defaultHeight_;
        auto bottom = LessNotEqual(bottom_.height_, bottom_.defaultHeight_) ? bottom_.height_ : bottom_.defaultHeight_;
        offsetIcon += OffsetF(left, top);
        offsetText += OffsetF(left, top);
        auto geometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto frameSize = geometryNode->GetFrameSize();
        frameSize -= SizeF(left + right, top + bottom);
        auto alignment = ParseAlignmentRTL(layoutWrapper, property->GetAlignment().value());
        auto translate = Alignment::GetAlignPosition(frameSize, childSize, alignment);
        offsetIcon += translate;
        offsetText += translate;
    } else {
        offsetIcon += OffsetF(left_.width_, top_.height_);
        offsetText += OffsetF(left_.width_, top_.height_);
    }

    UpdateChildPosition(layoutWrapper, V2::IMAGE_ETS_TAG, offsetIcon);
    UpdateChildPosition(layoutWrapper, V2::SYMBOL_ETS_TAG, offsetIcon);
    UpdateChildPosition(layoutWrapper, V2::TEXT_ETS_TAG, offsetText);

    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Layout();
    }
}

void SecurityComponentLayoutAlgorithm::UpdateCircleButtonConstraint()
{
    double circleIdealSize = std::max(componentWidth_, componentHeight_);
    if ((idealWidth_ != 0.0) && (idealHeight_ != 0.0)) {
        circleIdealSize = std::min(idealWidth_, idealHeight_);
    } else if (idealWidth_ != 0.0) {
        circleIdealSize = idealWidth_;
    } else if (idealHeight_ != 0.0) {
        circleIdealSize = idealHeight_;
    } else {
        if ((componentWidth_ < minWidth_) || (componentHeight_ < minHeight_)) {
            circleIdealSize = std::max(minWidth_, minHeight_);
        } else if ((componentWidth_ > maxWidth_) || (componentHeight_ > maxHeight_)) {
            circleIdealSize = std::min(maxWidth_, maxHeight_);
        }
    }
    idealWidth_ = idealHeight_ = circleIdealSize;
}

void SecurityComponentLayoutAlgorithm::FillBlank()
{
    if (isNobg_) {
        return;
    }
    if (GreatNotEqual(idealWidth_, componentWidth_)) {
        left_.width_ += ((idealWidth_ - componentWidth_) / HALF);
        right_.width_ += ((idealWidth_ - componentWidth_) / HALF);
    } else if (GreatNotEqual(minWidth_, componentWidth_)) {
        left_.width_ += ((minWidth_ - componentWidth_) / HALF);
        right_.width_ += ((minWidth_ - componentWidth_) / HALF);
    }
    if (GreatNotEqual(idealHeight_, componentHeight_)) {
        top_.height_ += ((idealHeight_ - componentHeight_) / HALF);
        bottom_.height_ += ((idealHeight_ - componentHeight_) / HALF);
    } else if (GreatNotEqual(minHeight_, componentHeight_)) {
        top_.height_ += ((minHeight_ - componentHeight_) / HALF);
        bottom_.height_ += ((minHeight_ - componentHeight_) / HALF);
    }
    MeasureIntegralSize();
}

RefPtr<FrameNode> SecurityComponentLayoutAlgorithm::GetSecCompChildNode(RefPtr<FrameNode>& parent,
    const std::string& tag)
{
    for (const auto& child : parent->GetChildren()) {
        auto node = AceType::DynamicCast<FrameNode, UINode>(child);
        CHECK_NULL_RETURN(node, nullptr);
        if (node->GetTag() == tag) {
            return node;
        }
    }
    return nullptr;
}

void SecurityComponentLayoutAlgorithm::UpdateTextRectPoint()
{
    if (isVertical_) {
        if (icon_.width_ > text_.width_) {
            textLeftTopPoint_ = SizeF(left_.width_ + icon_.width_ / HALF - text_.width_ / HALF,
                top_.height_ + icon_.height_ + middle_.height_);
            textRightTopPoint_ = SizeF(left_.width_ + icon_.width_ / HALF + text_.width_ / HALF,
                top_.height_ + icon_.height_ + middle_.height_);
            textLeftBottomPoint_ = SizeF(left_.width_ + icon_.width_ / HALF - text_.width_ / HALF,
                top_.height_ + icon_.height_ + middle_.height_ + text_.height_);
            textRightBottomPoint_ = SizeF(left_.width_ + icon_.width_ / HALF + text_.width_ / HALF,
                top_.height_ + icon_.height_ + middle_.height_ + text_.height_);
        } else {
            textLeftTopPoint_ = SizeF(left_.width_, top_.height_ + icon_.height_ + middle_.height_);
            textRightTopPoint_ = SizeF(left_.width_ + text_.width_, top_.height_ + icon_.height_ + middle_.height_);
            textLeftBottomPoint_ = SizeF(left_.width_, top_.height_ + icon_.height_ + middle_.height_ + text_.height_);
            textRightBottomPoint_ = SizeF(left_.width_ + text_.width_,
                top_.height_ + icon_.height_ + middle_.height_ + text_.height_);
        }
    } else {
        if (icon_.height_ > text_.height_) {
            textLeftTopPoint_ = SizeF(left_.width_ + icon_.width_ + middle_.width_,
                top_.height_ + icon_.height_ / HALF - text_.height_ / HALF);
            textRightTopPoint_ = SizeF(left_.width_ + icon_.width_ + middle_.width_ + text_.width_,
                top_.height_ + icon_.height_ / HALF - text_.height_ / HALF);
            textLeftBottomPoint_ = SizeF(left_.width_ + icon_.width_ + middle_.width_,
                top_.height_ + icon_.height_ / HALF + text_.height_ / HALF);
            textRightBottomPoint_ = SizeF(left_.width_ + icon_.width_ + middle_.width_ + text_.width_,
                top_.height_ + icon_.height_ / HALF + text_.height_ / HALF);
        } else {
            textLeftTopPoint_ = SizeF(left_.width_ + icon_.width_ + middle_.width_, top_.height_);
            textRightTopPoint_ = SizeF(left_.width_ + icon_.width_ + middle_.width_ + text_.width_, top_.height_);
            textLeftBottomPoint_ = SizeF(left_.width_ + icon_.width_ + middle_.width_, top_.height_ + text_.height_);
            textRightBottomPoint_ = SizeF(left_.width_ + icon_.width_ + middle_.width_ + text_.width_,
                top_.height_ + text_.height_);
        }
    }
}

bool SecurityComponentLayoutAlgorithm::IsTextAdaptOutOfRange(SizeF& leftPoint, SizeF& rightPoint, SizeF& circlePoint,
    float maxDistance)
{
    if (LessOrEqual(rightPoint.Width(), circlePoint.Width())) {
        return true;
    }

    auto pointDistance = rightPoint.Width() - circlePoint.Width();
    auto maxSpaceToShrink = rightPoint.Width() - leftPoint.Width();
    maxSpaceToShrink = GreatNotEqual(maxSpaceToShrink, pointDistance) ? pointDistance : maxSpaceToShrink;
    auto threshold = currentFontSize_.ConvertToPx() * (1.0 - TEXT_OUT_OF_WIDTH_PERCENT);
    auto res = text_.TryShrinkTextWidth(rightPoint, circlePoint, maxSpaceToShrink, maxDistance, threshold);
    if (res) {
        UpdateTextRectPoint();
        return false;
    }
    return true;
}

bool SecurityComponentLayoutAlgorithm::IsTextOutOfRangeInCircle()
{
    auto circlePoint = SizeF(componentWidth_ / HALF, componentHeight_ / HALF);
    auto threshold = TEXT_OUT_OF_RANGE_PERCENT * RANGE_RATIO * currentFontSize_.ConvertToPx();
    auto maxDistance = pow(circlePoint.Width() + threshold);
    auto leftTopDistance = pow(textLeftTopPoint_.Width() - circlePoint.Width()) +
        pow(textLeftTopPoint_.Height() - circlePoint.Height());
    if (GreatNotEqual(leftTopDistance, maxDistance)) {
        return true;
    }
    auto leftBottomDistance = pow(textLeftBottomPoint_.Width() - circlePoint.Width()) +
        pow(textLeftBottomPoint_.Height() - circlePoint.Height());
    if (GreatNotEqual(leftBottomDistance, maxDistance)) {
        return true;
    }
    auto rightTopDistance = pow(textRightTopPoint_.Width() - circlePoint.Width()) +
        pow(textRightTopPoint_.Height() - circlePoint.Height());
    if (GreatNotEqual(rightTopDistance, maxDistance) && IsTextAdaptOutOfRange(textLeftTopPoint_,
        textRightTopPoint_, circlePoint, maxDistance)) {
        return true;
    }
    auto rightBottomDistance = pow(textRightBottomPoint_.Width() - circlePoint.Width()) +
        pow(textRightBottomPoint_.Height() - circlePoint.Height());
    if (GreatNotEqual(rightBottomDistance, maxDistance) && IsTextAdaptOutOfRange(textLeftBottomPoint_,
        textRightBottomPoint_, circlePoint, maxDistance)) {
        return true;
    }
    return false;
}

bool SecurityComponentLayoutAlgorithm::CompareDistance(SizeF& point, SizeF& circlePoint, float maxDistance)
{
    auto distance = pow(point.Width() - circlePoint.Width()) + pow(point.Height() - circlePoint.Height());
    if (GreatNotEqual(distance, maxDistance)) {
        return true;
    }
    return false;
}

bool SecurityComponentLayoutAlgorithm::IsOutOfRangeInHoriCapsule(SizeF& leftCirclePoint, SizeF& rightCirclePoint,
    float maxDistance)
{
    if (GreatNotEqual(textRightTopPoint_.Width(), rightCirclePoint.Width()) &&
        LessNotEqual(textRightTopPoint_.Height(), rightCirclePoint.Height())) {
        if (CompareDistance(textRightTopPoint_, rightCirclePoint, maxDistance) &&
            IsTextAdaptOutOfRange(textLeftTopPoint_, textRightTopPoint_, rightCirclePoint, maxDistance)) {
            return true;
        }
    }
    if (LessNotEqual(textLeftBottomPoint_.Width(), leftCirclePoint.Width()) &&
        GreatNotEqual(textLeftBottomPoint_.Height(), leftCirclePoint.Height())) {
        if (CompareDistance(textLeftBottomPoint_, leftCirclePoint, maxDistance)) {
            return true;
        }
    }
    return false;
}

bool SecurityComponentLayoutAlgorithm::IsOutOfRangeInVertiCapsule(SizeF& topCirclePoint, SizeF& bottomCirclePoint,
    float maxDistance)
{
    if (GreatNotEqual(textRightTopPoint_.Width(), topCirclePoint.Width()) &&
        LessNotEqual(textRightTopPoint_.Height(), topCirclePoint.Height())) {
        if (CompareDistance(textRightTopPoint_, topCirclePoint, maxDistance) &&
            IsTextAdaptOutOfRange(textLeftTopPoint_, textRightTopPoint_, topCirclePoint, maxDistance)) {
            return true;
        }
    }
    if (LessNotEqual(textLeftBottomPoint_.Width(), bottomCirclePoint.Width()) &&
        GreatNotEqual(textLeftBottomPoint_.Height(), bottomCirclePoint.Height())) {
        if (CompareDistance(textLeftBottomPoint_, bottomCirclePoint, maxDistance)) {
            return true;
        }
    }
    return false;
}

bool SecurityComponentLayoutAlgorithm::IsTextOutOfRangeInCapsule()
{
    SizeF rightBottomCirclePoint;
    auto capsuleRadius = std::min(componentWidth_, componentHeight_) / HALF;
    auto maxDistance = pow(capsuleRadius + TEXT_OUT_OF_RANGE_PERCENT * RANGE_RATIO * currentFontSize_.ConvertToPx());
    auto leftTopCirclePoint = SizeF(capsuleRadius, capsuleRadius);
    if (LessNotEqual(textLeftTopPoint_.Width(), leftTopCirclePoint.Width()) &&
        LessNotEqual(textLeftTopPoint_.Height(), leftTopCirclePoint.Height())) {
        if (CompareDistance(textLeftTopPoint_, leftTopCirclePoint, maxDistance)) {
            return true;
        }
    }
    if (GreatOrEqual(componentWidth_, componentHeight_)) {
        rightBottomCirclePoint = SizeF(componentWidth_ - capsuleRadius, capsuleRadius);
        auto res = IsOutOfRangeInHoriCapsule(leftTopCirclePoint, rightBottomCirclePoint, maxDistance);
        if (res) {
            return res;
        }
    } else {
        rightBottomCirclePoint = SizeF(capsuleRadius, componentHeight_ - capsuleRadius);
        auto res = IsOutOfRangeInVertiCapsule(leftTopCirclePoint, rightBottomCirclePoint, maxDistance);
        if (res) {
            return res;
        }
    }
    if (GreatNotEqual(textRightBottomPoint_.Width(), rightBottomCirclePoint.Width()) &&
        GreatNotEqual(textRightBottomPoint_.Height(), rightBottomCirclePoint.Height())) {
        if (CompareDistance(textRightBottomPoint_, rightBottomCirclePoint, maxDistance) &&
            IsTextAdaptOutOfRange(textLeftBottomPoint_, textRightBottomPoint_, rightBottomCirclePoint, maxDistance)) {
            return true;
        }
    }
    return false;
}

bool SecurityComponentLayoutAlgorithm::TopLeftCompDistance(float obtainedRadius, float maxRadius, float threshold)
{
    auto radius = GreatNotEqual(obtainedRadius, maxRadius) ? maxRadius : obtainedRadius;
    auto circlePoint = SizeF(radius, radius);
    if (LessNotEqual(textLeftTopPoint_.Width(), circlePoint.Width()) &&
        LessNotEqual(textLeftTopPoint_.Height(), circlePoint.Height())) {
        auto distance = pow(textLeftTopPoint_.Width() - circlePoint.Width()) +
            pow(textLeftTopPoint_.Height() - circlePoint.Height());
        auto maxDistance = pow(radius + threshold);
        if (GreatNotEqual(distance, maxDistance)) {
            return true;
        }
    }
    return false;
}

bool SecurityComponentLayoutAlgorithm::BottomLeftCompDistance(float obtainedRadius, float maxRadius, float threshold)
{
    auto radius = GreatNotEqual(obtainedRadius, maxRadius) ? maxRadius : obtainedRadius;
    auto circlePoint = SizeF(radius, componentHeight_ - radius);
    if (LessNotEqual(textLeftBottomPoint_.Width(), circlePoint.Width()) &&
        GreatNotEqual(textLeftBottomPoint_.Height(), circlePoint.Height())) {
        auto distance = pow(textLeftBottomPoint_.Width() - circlePoint.Width()) +
            pow(textLeftBottomPoint_.Height() - circlePoint.Height());
        auto maxDistance = pow(radius + threshold);
        if (GreatNotEqual(distance, maxDistance)) {
            return true;
        }
    }
    return false;
}

bool SecurityComponentLayoutAlgorithm::TopRightCompDistance(float obtainedRadius, float maxRadius, float threshold)
{
    auto radius = GreatNotEqual(obtainedRadius, maxRadius) ? maxRadius : obtainedRadius;
    auto circlePoint = SizeF(componentWidth_ - radius, radius);
    if (GreatNotEqual(textRightTopPoint_.Width(), circlePoint.Width()) &&
        LessNotEqual(textRightTopPoint_.Height(), circlePoint.Height())) {
        auto distance = pow(textRightTopPoint_.Width() - circlePoint.Width()) +
            pow(textRightTopPoint_.Height() - circlePoint.Height());
        auto maxDistance = pow(radius + threshold);
        if (GreatNotEqual(distance, maxDistance) && IsTextAdaptOutOfRange(textLeftTopPoint_,
            textRightTopPoint_, circlePoint, maxDistance)) {
            return true;
        }
    }
    return false;
}

bool SecurityComponentLayoutAlgorithm::BottomRightCompDistance(float obtainedRadius, float maxRadius, float threshold)
{
    auto radius = GreatNotEqual(obtainedRadius, maxRadius) ? maxRadius : obtainedRadius;
    auto circlePoint = SizeF(componentWidth_ - radius, componentHeight_ - radius);
    if (GreatNotEqual(textRightBottomPoint_.Width(), circlePoint.Width()) &&
        GreatNotEqual(textRightBottomPoint_.Height(), circlePoint.Height())) {
        auto distance = pow(textRightBottomPoint_.Width() - circlePoint.Width()) +
            pow(textRightBottomPoint_.Height() - circlePoint.Height());
        auto maxDistance = pow(radius + threshold);
        if (GreatNotEqual(distance, maxDistance) && IsTextAdaptOutOfRange(textLeftBottomPoint_,
            textRightBottomPoint_, circlePoint, maxDistance)) {
            return true;
        }
    }
    return false;
}

bool SecurityComponentLayoutAlgorithm::IsTextOutOfRangeInNormal()
{
    auto borderRadius = buttonLayoutProperty_->GetBorderRadius();
    if (!borderRadius.has_value()) {
        return false;
    }
    auto maxRadius = std::min(componentWidth_, componentHeight_) / HALF;
    auto threshold = TEXT_OUT_OF_RANGE_PERCENT * RANGE_RATIO * currentFontSize_.ConvertToPx();
    if (borderRadius->radiusTopLeft.has_value() &&
        GreatNotEqual(borderRadius->radiusTopLeft.value().ConvertToPx(), currentFontSize_.ConvertToPx())) {
        if (TopLeftCompDistance(borderRadius->radiusTopLeft.value().ConvertToPx(), maxRadius, threshold)) {
            return true;
        }
    }
    if (borderRadius->radiusBottomLeft.has_value() &&
        GreatNotEqual(borderRadius->radiusBottomLeft.value().ConvertToPx(), currentFontSize_.ConvertToPx())) {
        if (BottomLeftCompDistance(borderRadius->radiusBottomLeft.value().ConvertToPx(), maxRadius, threshold)) {
            return true;
        }
    }
    if (borderRadius->radiusTopRight.has_value() &&
        GreatNotEqual(borderRadius->radiusTopRight.value().ConvertToPx(), currentFontSize_.ConvertToPx())) {
        if (TopRightCompDistance(borderRadius->radiusTopRight.value().ConvertToPx(), maxRadius, threshold)) {
            return true;
        }
    }
    if (borderRadius->radiusBottomRight.has_value() &&
        GreatNotEqual(borderRadius->radiusBottomRight.value().ConvertToPx(), currentFontSize_.ConvertToPx())) {
        if (BottomRightCompDistance(borderRadius->radiusBottomRight.value().ConvertToPx(), maxRadius, threshold)) {
            return true;
        }
    }
    return false;
}

bool SecurityComponentLayoutAlgorithm::IsTextOutOfOneColumn(RefPtr<FrameNode>& frameNode, float threshold)
{
    auto textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    CHECK_NULL_RETURN(textNode, false);
    auto textPattern = textNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    auto realWidth = textPattern->GetLineMetrics(0).width;
    auto allowWidth = text_.width_ + threshold;
    if (LessNotEqual(allowWidth, realWidth)) {
        return true;
    }

    return false;
}

bool SecurityComponentLayoutAlgorithm::GetMaxLineLimitExceededFlag(std::optional<SizeF>& currentTextSize)
{
    auto res = text_.DidExceedMaxLines(currentTextSize);
    if (res) {
        SC_LOG_INFO("MaxLine limit exceeded.");
        return true;
    }
    return false;
}

bool SecurityComponentLayoutAlgorithm::GetTextLimitExceededFlag(RefPtr<SecurityComponentLayoutProperty>& property,
    LayoutWrapper* layoutWrapper, std::optional<SizeF>& currentTextSize)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto buttonNode = GetSecCompChildNode(frameNode, V2::BUTTON_ETS_TAG);
    CHECK_NULL_RETURN(buttonNode, false);
    buttonLayoutProperty_ = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty_, false);

    auto res = text_.GetCurrentTextSize(currentTextSize, currentFontSize_);
    if (!res) {
        return false;
    }

    UpdateTextRectPoint();

    auto isCircle = (property->GetBackgroundType() == static_cast<int32_t>(ButtonType::CIRCLE));
    auto isCapsule = (property->GetBackgroundType() == static_cast<int32_t>(ButtonType::CAPSULE));
    if (isCircle) {
        res = IsTextOutOfRangeInCircle();
    } else if (isCapsule) {
        res = IsTextOutOfRangeInCapsule();
    } else {
        res = IsTextOutOfRangeInNormal();
    }

    if (!res) {
        auto threshold = currentFontSize_.ConvertToPx() * TEXT_OUT_OF_WIDTH_PERCENT;
        res = IsTextOutOfOneColumn(frameNode, threshold);
    }

    return res;
}

void SecurityComponentLayoutAlgorithm::UpdateTextFlags(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto securityComponentLayoutProperty =
        AceType::DynamicCast<SecurityComponentLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(securityComponentLayoutProperty);
    std::optional<SizeF> currentTextSize;
    securityComponentLayoutProperty->UpdateIsTextLimitExceeded(GetTextLimitExceededFlag(securityComponentLayoutProperty,
        layoutWrapper, currentTextSize));
    securityComponentLayoutProperty->UpdateIsMaxLineLimitExceeded(GetMaxLineLimitExceededFlag(currentTextSize));
}

void SecurityComponentLayoutAlgorithm::InitLayoutWrapper(LayoutWrapper* layoutWrapper,
    const RefPtr<SecurityComponentLayoutProperty>& securityComponentLayoutProperty)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto iconWrapper = GetChildWrapper(layoutWrapper, V2::IMAGE_ETS_TAG);
    iconWrapper = iconWrapper ? iconWrapper : GetChildWrapper(layoutWrapper, V2::SYMBOL_ETS_TAG);
    icon_.Init(securityComponentLayoutProperty, iconWrapper);

    auto textWrapper = GetChildWrapper(layoutWrapper, V2::TEXT_ETS_TAG);
    text_.Init(securityComponentLayoutProperty, textWrapper);
}

void SecurityComponentLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto securityComponentLayoutProperty =
        AceType::DynamicCast<SecurityComponentLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(securityComponentLayoutProperty);
    InitLayoutWrapper(layoutWrapper, securityComponentLayoutProperty);

    constraint_ = securityComponentLayoutProperty->GetContentLayoutConstraint();
    CHECK_NULL_VOID(constraint_);

    // has value and less equal 0.0
    if (LessOrEqual(constraint_->selfIdealSize.Width().value_or(1.0), 0.0) &&
        LessOrEqual(constraint_->selfIdealSize.Height().value_or(1.0), 0.0)) {
        return;
    }

    isVertical_ = (securityComponentLayoutProperty->GetTextIconLayoutDirection().value_or(
        SecurityComponentLayoutDirection::HORIZONTAL) == SecurityComponentLayoutDirection::VERTICAL);
    isNobg_ = (securityComponentLayoutProperty->GetBackgroundType().value_or(
        static_cast<int32_t>(ButtonType::CAPSULE)) == BUTTON_TYPE_NULL);
    idealWidth_ = constraint_->selfIdealSize.Width().value_or(0.0);
    idealHeight_ = constraint_->selfIdealSize.Height().value_or(0.0);
    minWidth_ = constraint_->minSize.Width();
    minHeight_ = constraint_->minSize.Height();
    maxWidth_ = constraint_->maxSize.Width();
    maxHeight_ = constraint_->maxSize.Height();
    InitPadding(securityComponentLayoutProperty);
    if (GetTextDirection(layoutWrapper) == TextDirection::RTL) {
        PaddingLayoutElement temp = left_;
        left_ = right_;
        right_ = temp;
    }

    MeasureIntegralSize();

    if (securityComponentLayoutProperty->GetBackgroundType() == static_cast<int32_t>(ButtonType::CIRCLE)) {
        UpdateCircleButtonConstraint();
    }
    AdaptWidth();
    AdaptHeight();
    if (isNeedReadaptWidth_) {
        AdaptWidth();
    }
    // fill blank when all paddings can not be enlarged because it has been set
    FillBlank();
    icon_.DoMeasure();
    MeasureButton(layoutWrapper, securityComponentLayoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(SizeF(componentWidth_, componentHeight_));
    UpdateTextFlags(layoutWrapper);
}

TextDirection SecurityComponentLayoutAlgorithm::GetTextDirection(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    // default return LTR
    CHECK_NULL_RETURN(frameNode, TextDirection::LTR);
    std::u16string text = u"";
    // get button string
    for (const auto& child : frameNode->GetChildren()) {
        auto node = AceType::DynamicCast<FrameNode, UINode>(child);
        if (node == nullptr) {
            continue;
        }
        if (node->GetTag() == V2::TEXT_ETS_TAG) {
            auto textLayoutProperty = node->GetLayoutProperty<TextLayoutProperty>();
            if (textLayoutProperty == nullptr) {
                continue;
            }
            text = textLayoutProperty->GetContentValue(text);
            break;
        }
    }
    if (text.empty()) {
        return TextDirection::LTR;
    }
    for (const auto& charInStr : text) {
        auto direction = u_charDirection(charInStr);
        if (direction == UCharDirection::U_LEFT_TO_RIGHT) {
            return TextDirection::LTR;
        }
        if (direction == UCharDirection::U_RIGHT_TO_LEFT || direction == UCharDirection::U_RIGHT_TO_LEFT_ARABIC) {
            return TextDirection::RTL;
        }
    }
    return TextDirection::LTR;
}
} // namespace OHOS::Ace::NG
