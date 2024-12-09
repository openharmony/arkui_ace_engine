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

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
namespace OHOS::Ace::NG {
namespace {
// for indicator
constexpr Dimension INDICATOR_ITEM_SPACE = 8.0_vp;
constexpr Dimension INDICATOR_PADDING_DEFAULT = 12.0_vp;
constexpr Dimension INDICATOR_PADDING_HOVER = 12.0_vp;
constexpr float INDICATOR_ZOOM_IN_SCALE = 1.33f;

constexpr float BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY = 0.4f;
constexpr float LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY = 0.2f;
constexpr float LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY = 1.0f;
constexpr float CENTER_BEZIER_CURVE_MASS = 0.0f;
constexpr float CENTER_BEZIER_CURVE_STIFFNESS = 1.0f;
constexpr float CENTER_BEZIER_CURVE_DAMPING = 1.0f;
constexpr uint32_t ITEM_HALF_WIDTH = 0;
constexpr uint32_t ITEM_HALF_HEIGHT = 1;
constexpr uint32_t SELECTED_ITEM_HALF_WIDTH = 2;
constexpr uint32_t SELECTED_ITEM_HALF_HEIGHT = 3;
constexpr float TOUCH_BOTTOM_BACKGROUND_WIDTH_MULTIPLE = 1.225f;
constexpr float TOUCH_BOTTOM_DOT_WIDTH_MULTIPLE = 0.0125f;
constexpr float LONG_POINT_TAIL_RATIO = 0.5f;
constexpr float HALF_SELECTED_WIDTH = 2.0f;
constexpr int TWOFOLD = 2;
} // namespace

void DotIndicatorPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    CHECK_NULL_VOID(paintWrapper);

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperTheme);

    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    if (isHorizontalAndRightToLeft_) {
        currentIndex_ = itemCount_ - 1 - currentIndex_;
    }
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    IsCustomSizeValue_ = paintProperty->GetIsCustomSizeValue(false);
    dotIndicatorModifier_->SetAxis(axis_);
    dotIndicatorModifier_->SetCurrentIndex(currentIndex_);
    dotIndicatorModifier_->SetCurrentIndexActual(currentIndexActual_);
    dotIndicatorModifier_->SetUnselectedColor(paintProperty->GetColorValue(swiperTheme->GetColor()));
    dotIndicatorModifier_->SetSelectedColor(paintProperty->GetSelectedColorValue(swiperTheme->GetSelectedColor()));
    dotIndicatorModifier_->SetIndicatorMask(paintProperty->GetIndicatorMaskValue(false));
    dotIndicatorModifier_->SetIsIndicatorCustomSize(IsCustomSizeValue_);
    dotIndicatorModifier_->SetOffset(geometryNode->GetContentOffset());
    SizeF contentSize = geometryNode->GetFrameSize();
    centerY_ = (axis_ == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width()) * 0.5;
    dotIndicatorModifier_->SetCenterY(centerY_);
    if (touchBottomType_ != TouchBottomType::NONE) {
        if (!dotIndicatorModifier_->GetIsPressed()) {
            PaintPressIndicator(paintWrapper);
            dotIndicatorModifier_->SetIsPressed(true);
        }
        UpdateBackground(paintWrapper);
    } else if (isPressed_) {
        PaintPressIndicator(paintWrapper);
        dotIndicatorModifier_->SetIsPressed(true);
    } else if (isHover_) {
        PaintHoverIndicator(paintWrapper);
        dotIndicatorModifier_->SetIsHover(true);
    } else {
        PaintNormalIndicator(paintWrapper);
        dotIndicatorModifier_->SetIsHover(false);
        dotIndicatorModifier_->SetIsPressed(false);
    }
}

void DotIndicatorPaintMethod::GetLongPointAnimationStateSecondCenter(
    const PaintWrapper* paintWrapper, std::vector<std::pair<float, float>>& pointCenterX)
{
    bool leftBottom = (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT &&
                       touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
    bool rightBottom = (gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT &&
                        touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);

    if (leftBottom || rightBottom) {
        pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
        auto [longPointCenterX, _] = CalculateLongPointCenterX(paintWrapper);
        pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
        pointCenterX.push_back(longPointCenterX);
    }
}

void DotIndicatorPaintMethod::UpdateNormalIndicator(
    LinearVector<float>& itemHalfSizes, const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        std::vector<std::pair<float, float>> pointCenterX({ longPointCenterX_ });
        GetLongPointAnimationStateSecondCenter(paintWrapper, pointCenterX);
        dotIndicatorModifier_->PlayIndicatorAnimation(
            vectorBlackPointCenterX_, pointCenterX, gestureState_, touchBottomTypeLoop_);
    } else {
        dotIndicatorModifier_->UpdateNormalPaintProperty(
            normalMargin_, itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    }
}

void DotIndicatorPaintMethod::PaintNormalIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    auto [longPointCenterX, itemHalfSizes] = CalculateLongPointCenterX(paintWrapper);
    longPointCenterX_ = longPointCenterX;

    if (dotIndicatorModifier_->GetIsHover()) {
        dotIndicatorModifier_->UpdateHoverToNormalPaintProperty(
            normalMargin_, itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    } else if (dotIndicatorModifier_->GetIsPressed()) {
        dotIndicatorModifier_->UpdatePressToNormalPaintProperty(
            normalMargin_, itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    } else {
        UpdateNormalIndicator(itemHalfSizes, paintWrapper);
    }
}

void DotIndicatorPaintMethod::PaintHoverIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight =
        static_cast<float>(paintProperty->GetSelectedItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    // use radius calculation
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(itemWidth * 0.5 * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(itemHeight * 0.5 * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(selectedItemWidth * 0.5 * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(selectedItemHeight * 0.5 * INDICATOR_ZOOM_IN_SCALE);
    longPointCenterX_ =
        CalculatePointCenterX(itemHalfSizes, 0, static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()),
            static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);

    if (dotIndicatorModifier_->GetIsPressed()) {
        dotIndicatorModifier_->SetIsPressed(false);
        dotIndicatorModifier_->UpdateHoverAndPressConversionPaintProperty();
    } else if (dotIndicatorModifier_->GetIsHover()) {
        if (!mouseClickIndex_.has_value()) {
            dotIndicatorModifier_->UpdateHoverPaintProperty(itemHalfSizes,
                vectorBlackPointCenterX_, longPointCenterX_);
        }
    } else {
        dotIndicatorModifier_->UpdateNormalToHoverPaintProperty(
            itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    }

    CalculateHoverIndex(itemHalfSizes);
    if (dotIndicatorModifier_->GetNormalToHoverIndex() != hoverIndex_) {
        dotIndicatorModifier_->SetHoverToNormalIndex(dotIndicatorModifier_->GetNormalToHoverIndex());
        dotIndicatorModifier_->UpdateHoverToNormalPointDilateRatio();
        dotIndicatorModifier_->SetNormalToHoverIndex(hoverIndex_);
        dotIndicatorModifier_->UpdateNormalToHoverPointDilateRatio();
    }

    PaintHoverIndicator(itemHalfSizes, INDICATOR_PADDING_HOVER);
}

void DotIndicatorPaintMethod::PaintHoverIndicator(LinearVector<float>& itemHalfSizes, const Dimension paddingSide)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    if (mouseClickIndex_) {
        if (currentIndex_ == itemCount_ - displayCount_ && !isLoop_ && mouseClickIndex_ > currentIndex_ &&
            mouseClickIndex_ < itemCount_) {
            longPointCenterX_ = CalculatePointCenterX(itemHalfSizes, 0, static_cast<float>(paddingSide.ConvertToPx()),
                static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);
        } else {
            auto mouseClickIndex = mouseClickIndex_.value();
            if (isHorizontalAndRightToLeft_) {
                mouseClickIndex = itemCount_ - 1 - mouseClickIndex_.value();
            }
            longPointCenterX_ = CalculatePointCenterX(itemHalfSizes, 0, static_cast<float>(paddingSide.ConvertToPx()),
                static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), mouseClickIndex);
        }
        dotIndicatorModifier_->UpdateAllPointCenterXAnimation(
            gestureState_, vectorBlackPointCenterX_, longPointCenterX_);
        mouseClickIndex_ = std::nullopt;
    }
    if (dotIndicatorModifier_->GetLongPointIsHover() != longPointIsHover_) {
        dotIndicatorModifier_->SetLongPointIsHover(longPointIsHover_);
        dotIndicatorModifier_->UpdateLongPointDilateRatio();
    }
}

void DotIndicatorPaintMethod::PaintPressIndicator(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight =
        static_cast<float>(paintProperty->GetSelectedItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    // use radius calculation
    auto itemHalfWidth = itemWidth * 0.5 * INDICATOR_ZOOM_IN_SCALE;
    auto itemHalfHeight = itemHeight * 0.5 * INDICATOR_ZOOM_IN_SCALE;
    auto selectedItemHalfWidth = selectedItemWidth * 0.5 * INDICATOR_ZOOM_IN_SCALE;
    auto selectedItemHalfHeight = selectedItemHeight * 0.5 * INDICATOR_ZOOM_IN_SCALE;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(itemHalfWidth);
    itemHalfSizes.emplace_back(itemHalfHeight);
    itemHalfSizes.emplace_back(selectedItemHalfWidth);
    itemHalfSizes.emplace_back(selectedItemHalfHeight);
    longPointCenterX_ =
        CalculatePointCenterX(itemHalfSizes, 0, static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()),
            static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);
    if (dotIndicatorModifier_->GetIsPressed()) {
        dotIndicatorModifier_->UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    } else if (dotIndicatorModifier_->GetIsHover()) {
        dotIndicatorModifier_->SetIsPressed(true);
        dotIndicatorModifier_->UpdateHoverAndPressConversionPaintProperty();
    } else {
        dotIndicatorModifier_->UpdateNormalToPressPaintProperty(
            itemHalfSizes, vectorBlackPointCenterX_, longPointCenterX_);
    }
}

void DotIndicatorPaintMethod::CalculateNormalMargin(const LinearVector<float>& itemHalfSizes,
    const SizeF& frameSize, const int32_t displayCount)
{
    // diameter calculation
    auto itemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * 2;
    auto itemHeight = itemHalfSizes[ITEM_HALF_HEIGHT] * 2;
    auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * 2;
    auto selectedItemHeight = itemHalfSizes[SELECTED_ITEM_HALF_HEIGHT] * 2;
    auto allPointDiameterSum = itemWidth * static_cast<float>(displayCount + 1);
    if (IsCustomSizeValue_) {
        allPointDiameterSum = itemWidth * static_cast<float>(displayCount - 1) + selectedItemWidth;
    }
    auto allPointSpaceSum = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()) * (displayCount - 1);
    auto indicatorPadding = static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx());
    auto contentWidth = indicatorPadding + allPointDiameterSum + allPointSpaceSum + indicatorPadding;
    auto contentHeight = indicatorPadding + itemHeight + indicatorPadding;
    if (selectedItemHeight > itemHeight) {
        contentHeight = indicatorPadding + selectedItemHeight + indicatorPadding;
    }
    float marginX = ((axis_ == Axis::HORIZONTAL ? frameSize.Width() : frameSize.Height()) - contentWidth) * 0.5;
    float marginY = ((axis_ == Axis::HORIZONTAL ? frameSize.Height() : frameSize.Width()) - contentHeight) * 0.5;
    normalMargin_.SetX(marginX);
    normalMargin_.SetY(marginY);
}

std::pair<float, float> DotIndicatorPaintMethod::CalculatePointCenterX(
    const LinearVector<float>& itemHalfSizes, float margin, float padding, float space, int32_t index)
{
    if (itemCount_ == 0) {
        return { 0, 0 };
    }
    float startCenterX = margin + padding;
    float endCenterX = margin + padding;
    if (Positive(turnPageRate_)) {
        auto itemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * TWOFOLD;
        auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * TWOFOLD;
        float allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ + 1);
        if (IsCustomSizeValue_) {
            allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ - 1) + selectedItemWidth;
        }
        auto allPointSpaceSum = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx() * (itemCount_ - 1));
        float rectWidth = padding + allPointDiameterSum + allPointSpaceSum + padding;
        startCenterX = rectWidth - startCenterX;
        endCenterX = rectWidth - endCenterX;
        return BackwardCalculation(itemHalfSizes, startCenterX, endCenterX, space, index);
    }
    return ForwardCalculation(itemHalfSizes, startCenterX, endCenterX, space, index);
}

std::tuple<std::pair<float, float>, LinearVector<float>> DotIndicatorPaintMethod::CalculateLongPointCenterX(
    const PaintWrapper* paintWrapper)
{
    std::tuple<std::pair<float, float>, LinearVector<float>> tmp;
    CHECK_NULL_RETURN(paintWrapper, tmp);
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, tmp);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, tmp);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_RETURN(swiperTheme, tmp);
    SizeF frameSize = geometryNode->GetFrameSize();
    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight =
        static_cast<float>(paintProperty->GetSelectedItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    // use radius calculation
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(itemWidth * 0.5);
    itemHalfSizes.emplace_back(itemHeight * 0.5);
    itemHalfSizes.emplace_back(selectedItemWidth * 0.5);
    itemHalfSizes.emplace_back(selectedItemHeight * 0.5);
    CalculateNormalMargin(itemHalfSizes, frameSize, itemCount_);
    auto longPointCenterX = CalculatePointCenterX(itemHalfSizes, normalMargin_.GetX(),
        static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx()),
        static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()), currentIndex_);
    return { longPointCenterX, itemHalfSizes };
}

std::tuple<float, float, float> DotIndicatorPaintMethod::GetMoveRate()
{
    float blackPointCenterMoveRate = CubicCurve(BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY, CENTER_BEZIER_CURVE_MASS,
        CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING).MoveInternal(std::abs(turnPageRate_));
    float longPointLeftCenterMoveRate = 0.0f;
    float longPointRightCenterMoveRate = 0.0f;
    if (isPressed_ && touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE) {
        longPointLeftCenterMoveRate = CubicCurve(turnPageRate_ > 0 ? LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY :
            LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY, CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS,
            CENTER_BEZIER_CURVE_DAMPING).MoveInternal(std::abs(turnPageRate_));
        longPointRightCenterMoveRate = CubicCurve(turnPageRate_ > 0 ? LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY :
            LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY, CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS,
            CENTER_BEZIER_CURVE_DAMPING).MoveInternal(std::abs(turnPageRate_));
    } else if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
               gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        blackPointCenterMoveRate = 1;
        longPointLeftCenterMoveRate = 1;
        longPointRightCenterMoveRate = 1;
    } else if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT) {
        auto rateAbs = 1.0f - std::abs(turnPageRate_);
        // x0:0.33, y0:0, x1:0.67, y1:1
        longPointLeftCenterMoveRate = longPointRightCenterMoveRate = CubicCurve(0.33, 0, 0.67, 1).MoveInternal(rateAbs);
    } else if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT) {
        auto rateAbs = std::abs(turnPageRate_);
        // x0:0.33, y0:0, x1:0.67, y1:1
        longPointLeftCenterMoveRate = longPointRightCenterMoveRate = CubicCurve(0.33, 0, 0.67, 1).MoveInternal(rateAbs);
    } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
        longPointLeftCenterMoveRate =std::abs(turnPageRate_);
        longPointRightCenterMoveRate = std::abs(turnPageRate_) +
                                       ((1 - longPointLeftCenterMoveRate) * LONG_POINT_TAIL_RATIO);
    } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        longPointRightCenterMoveRate = std::abs(turnPageRate_);
        longPointLeftCenterMoveRate = std::abs(turnPageRate_) * LONG_POINT_TAIL_RATIO;
    }
    return { blackPointCenterMoveRate, longPointLeftCenterMoveRate, longPointRightCenterMoveRate };
}

std::pair<float, float> DotIndicatorPaintMethod::CalculatePointCenterX(
    const StarAndEndPointCenter& starAndEndPointCenter, const LinearVector<float>& startVectorBlackPointCenterX,
    const LinearVector<float>& endVectorBlackPointCenterX)
{
    const auto [blackPointCenterMoveRate, longPointLeftCenterMoveRate, longPointRightCenterMoveRate] = GetMoveRate();

    vectorBlackPointCenterX_.resize(itemCount_);
    for (int32_t i = 0; i < itemCount_; ++i) {
        vectorBlackPointCenterX_[i] = startVectorBlackPointCenterX[i] +
        (endVectorBlackPointCenterX[i] - startVectorBlackPointCenterX[i]) * blackPointCenterMoveRate;
    }

    std::pair<float, float> longPointCenterX;
    longPointCenterX.first = starAndEndPointCenter.startLongPointLeftCenterX +
        (starAndEndPointCenter.endLongPointLeftCenterX - starAndEndPointCenter.startLongPointLeftCenterX) *
            longPointLeftCenterMoveRate;
    longPointCenterX.second = starAndEndPointCenter.startLongPointRightCenterX +
        (starAndEndPointCenter.endLongPointRightCenterX - starAndEndPointCenter.startLongPointRightCenterX) *
            longPointRightCenterMoveRate;
    if (isHorizontalAndRightToLeft_) {
        longPointCenterX.first = starAndEndPointCenter.startLongPointLeftCenterX +
        (starAndEndPointCenter.endLongPointLeftCenterX - starAndEndPointCenter.startLongPointLeftCenterX) *
            longPointLeftCenterMoveRate;
        longPointCenterX.second = starAndEndPointCenter.startLongPointRightCenterX +
            (starAndEndPointCenter.endLongPointRightCenterX - starAndEndPointCenter.startLongPointRightCenterX) *
                longPointRightCenterMoveRate;
    }
    return longPointCenterX;
}

void DotIndicatorPaintMethod::CalculateHoverIndex(const LinearVector<float>& itemHalfSizes)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    if (!isHover_) {
        hoverIndex_ = std::nullopt;
        longPointIsHover_ = false;
        return;
    }
    for (size_t i = 0; i < vectorBlackPointCenterX_.size(); ++i) {
        OffsetF center = { vectorBlackPointCenterX_[i], centerY_ };
        if (isHoverPoint(hoverPoint_, center, center, itemHalfSizes)) {
            hoverIndex_ = i;
            break;
        }
    }
    auto longPointCenterX = dotIndicatorModifier_->GetLongPointCenterX();

    OffsetF leftCenter = { longPointCenterX.first, centerY_ };
    OffsetF rightCenter = { longPointCenterX.second, centerY_ };
    longPointIsHover_ = isHoverPoint(hoverPoint_, leftCenter, rightCenter, itemHalfSizes);
}

bool DotIndicatorPaintMethod::isHoverPoint(
    const PointF& hoverPoint, const OffsetF& leftCenter,
    const OffsetF& rightCenter, const LinearVector<float>& itemHalfSizes)
{
    float tempLeftCenterX = axis_ == Axis::HORIZONTAL ? leftCenter.GetX() : leftCenter.GetY();
    float tempLeftCenterY = axis_ == Axis::HORIZONTAL ? leftCenter.GetY() : leftCenter.GetX();
    float tempRightCenterX = axis_ == Axis::HORIZONTAL ? rightCenter.GetX() : rightCenter.GetY();
    float tempRightCenterY = axis_ == Axis::HORIZONTAL ? rightCenter.GetY() : rightCenter.GetX();
    float itemHalfWidth = itemHalfSizes[ITEM_HALF_WIDTH];
    float itemHalfHeight = itemHalfSizes[ITEM_HALF_HEIGHT];
    if (hoverIndex_ == currentIndex_) {
        itemHalfWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
        itemHalfHeight = itemHalfSizes[SELECTED_ITEM_HALF_HEIGHT];
    }
    return hoverPoint.GetX() >= (tempLeftCenterX - itemHalfWidth) && (hoverPoint.GetX() <=
                (tempRightCenterX + itemHalfWidth)) && (hoverPoint.GetY() >= (tempLeftCenterY - itemHalfHeight)) &&
                (hoverPoint.GetY() <= (tempRightCenterY + itemHalfHeight));
}

void DotIndicatorPaintMethod::UpdateBackground(const PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<DotIndicatorPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);

    // diameter calculation
    auto itemWidth = static_cast<float>(paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto itemHeight = static_cast<float>(paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemWidth =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    auto selectedItemHeight =
        static_cast<float>(paintProperty->GetSelectedItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    // use radius calculation
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(itemWidth * 0.5f * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(itemHeight * 0.5f * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(selectedItemWidth * 0.5f * INDICATOR_ZOOM_IN_SCALE);
    itemHalfSizes.emplace_back(selectedItemHeight * 0.5f * INDICATOR_ZOOM_IN_SCALE);
    if (touchBottomType_ != TouchBottomType::NONE) {
        float allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ + 1);
        if (IsCustomSizeValue_) {
            allPointDiameterSum = itemWidth * static_cast<float>(itemCount_ - 1) + selectedItemWidth;
        }
        float allPointSpaceSum = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()) * (itemCount_ - 1);
        float padding = static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx());
        float rectWidth = padding + allPointDiameterSum + allPointSpaceSum + padding;
        float newRectWidth =
            rectWidth * (TOUCH_BOTTOM_BACKGROUND_WIDTH_MULTIPLE - TOUCH_BOTTOM_DOT_WIDTH_MULTIPLE * itemCount_);
        auto changeValue = (newRectWidth - rectWidth) * touchBottomRate_;

        float space = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx());
        if (itemCount_ > 1) {
            space = (rectWidth + changeValue - padding * 2 - allPointDiameterSum) / (itemCount_ - 1);
        }
        longPointCenterX_ = CalculatePointCenterX(itemHalfSizes, 0, padding, space, currentIndex_);
        if (touchBottomType_ == TouchBottomType::START) {
            for (size_t index = 0; index < vectorBlackPointCenterX_.size(); index++) {
                vectorBlackPointCenterX_[index] = vectorBlackPointCenterX_[index] - changeValue;
            }
            longPointCenterX_.first = longPointCenterX_.first - changeValue;
            longPointCenterX_.second = longPointCenterX_.second - changeValue;
        }
    }
    dotIndicatorModifier_->UpdateTouchBottomAnimation(
        touchBottomType_, vectorBlackPointCenterX_, longPointCenterX_, touchBottomRate_);
}

std::pair<int32_t, int32_t> DotIndicatorPaintMethod::GetIndexOnRTL(int32_t index)
{
    int32_t startCurrentIndex = index;
    auto isInvalid = NearEqual(turnPageRate_, 0.0f) || LessOrEqualCustomPrecision(turnPageRate_, -1.0f) ||
                     GreatOrEqualCustomPrecision(turnPageRate_, 1.0f);
    if (!isInvalid) {
        startCurrentIndex = LessNotEqualCustomPrecision(turnPageRate_, 0.0f) ? index - 1 : index + 1;
    }

    if (startCurrentIndex == -1) {
        startCurrentIndex = itemCount_ - 1;
    }

    return { startCurrentIndex, index };
}

std::pair<int32_t, int32_t> DotIndicatorPaintMethod::GetIndex(int32_t index)
{
    if (mouseClickIndex_ || gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT ||
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT) {
        turnPageRate_ = 0;
    }

    if (isHorizontalAndRightToLeft_) {
        return GetIndexOnRTL(index);
    }

    // item may be invalid in auto linear scene
    if (nextValidIndex_ >= 0) {
        int32_t startCurrentIndex = index;
        int32_t endCurrentIndex = NearEqual(turnPageRate_, 0.0f) || LessOrEqualCustomPrecision(turnPageRate_, -1.0f) ||
                                          GreatOrEqualCustomPrecision(turnPageRate_, 1.0f)
                                      ? index
                                      : nextValidIndex_;
        // reach edge scene
        if (startCurrentIndex > endCurrentIndex) {
            startCurrentIndex = currentIndexActual_;
            endCurrentIndex = currentIndexActual_;
        }
        return { startCurrentIndex, endCurrentIndex };
    }

    int32_t startCurrentIndex = index;
    int32_t endCurrentIndex = NearEqual(turnPageRate_, 0.0f) || LessOrEqualCustomPrecision(turnPageRate_, -1.0f) ||
                                      GreatOrEqualCustomPrecision(turnPageRate_, 1.0f)
                                  ? endCurrentIndex = index
                                  : (LessNotEqualCustomPrecision(turnPageRate_, 0.0f) ? index + 1 : index - 1);
    if (endCurrentIndex == -1) {
        endCurrentIndex = itemCount_ - 1;
    } else if (endCurrentIndex == itemCount_) {
        endCurrentIndex = 0;
    }

    return { startCurrentIndex, endCurrentIndex };
}

std::pair<int32_t, int32_t> DotIndicatorPaintMethod::GetStartAndEndIndex(int32_t index)
{
    auto [startCurrentIndex, endCurrentIndex] = GetIndex(index);

    if (pointAnimationStage_ == PointAnimationStage::STATE_EXPAND_TO_LONG_POINT &&
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT &&
        touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT) {
        endCurrentIndex = startCurrentIndex;
        return { startCurrentIndex, endCurrentIndex };
    } else if (pointAnimationStage_ == PointAnimationStage::STATE_EXPAND_TO_LONG_POINT &&
               gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT &&
               touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT) {
        endCurrentIndex = startCurrentIndex = 0;
        return { startCurrentIndex, endCurrentIndex };
    }

    if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT &&
        !(endCurrentIndex == startCurrentIndex && startCurrentIndex != 0)) {
        startCurrentIndex = endCurrentIndex = 0;
    } else if (gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT &&
               touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT) {
        endCurrentIndex = startCurrentIndex = itemCount_ - 1;
    } else if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT) {
        endCurrentIndex = startCurrentIndex;
    }

    return { startCurrentIndex, endCurrentIndex };
}

void DotIndicatorPaintMethod::AdjustPointCenterXForTouchBottom(StarAndEndPointCenter& pointCenter,
    LinearVector<float>& endVectorBlackPointCenterX, int32_t startCurrentIndex, int32_t endCurrentIndex,
    float selectedItemWidth, int32_t index)
{
    auto [startIndex, endIndex] = GetIndex(index);
    if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT &&
        pointAnimationStage_ != PointAnimationStage::STATE_EXPAND_TO_LONG_POINT &&
        (!(endIndex == startIndex && startIndex != 0) ||
            (gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT ||
                gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT))) {
        pointCenter.endLongPointRightCenterX = pointCenter.endLongPointLeftCenterX = endVectorBlackPointCenterX[0];
    } else if (touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT &&
               pointAnimationStage_ != PointAnimationStage::STATE_EXPAND_TO_LONG_POINT) {
        pointCenter.endLongPointRightCenterX = pointCenter.endLongPointLeftCenterX =
            endVectorBlackPointCenterX[startCurrentIndex];
    }

    if (IsCustomSizeValue_) {
        selectedItemWidth = 0;
    }

    if (pointAnimationStage_ == PointAnimationStage::STATE_EXPAND_TO_LONG_POINT &&
        gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT &&
        touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT) {
        pointCenter.startLongPointRightCenterX = endVectorBlackPointCenterX[endCurrentIndex];
        pointCenter.endLongPointLeftCenterX =
            endVectorBlackPointCenterX[endCurrentIndex] - (selectedItemWidth / HALF_SELECTED_WIDTH);
    } else if (pointAnimationStage_ == PointAnimationStage::STATE_EXPAND_TO_LONG_POINT &&
               gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT &&
               touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT) {
        pointCenter.startLongPointRightCenterX = endVectorBlackPointCenterX[0];
        pointCenter.endLongPointLeftCenterX = endVectorBlackPointCenterX[0] - (selectedItemWidth / HALF_SELECTED_WIDTH);
    }
}

std::pair<float, float> DotIndicatorPaintMethod::ForwardCalculation(
    const LinearVector<float>& itemHalfSizes, float startCenterX, float endCenterX, float space, int32_t index)
{
    auto itemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * TWOFOLD;
    auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * TWOFOLD;
    StarAndEndPointCenter pointCenter;
    // Calculate the data required for the current pages
    LinearVector<float> startVectorBlackPointCenterX(itemCount_);
    // Calculate the data required for subsequent pages
    LinearVector<float> endVectorBlackPointCenterX(itemCount_);

    auto [startCurrentIndex, endCurrentIndex] = GetStartAndEndIndex(index);
    for (int32_t i = 0; i < itemCount_; ++i) {
        if (i != startCurrentIndex) {
            startVectorBlackPointCenterX[i] = startCenterX + itemHalfSizes[ITEM_HALF_WIDTH];
            startCenterX += itemWidth;
        } else {
            if (IsCustomSizeValue_) {
                startVectorBlackPointCenterX[i] = startCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.startLongPointLeftCenterX = startCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.startLongPointRightCenterX = pointCenter.startLongPointLeftCenterX;
                startCenterX += selectedItemWidth;
            } else {
                startVectorBlackPointCenterX[i] = startCenterX + selectedItemWidth;
                pointCenter.startLongPointLeftCenterX = startCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.startLongPointRightCenterX = pointCenter.startLongPointLeftCenterX + selectedItemWidth;
                startCenterX += selectedItemWidth * TWOFOLD;
            }
        }
        if (i != endCurrentIndex) {
            endVectorBlackPointCenterX[i] = endCenterX + itemHalfSizes[ITEM_HALF_WIDTH];
            endCenterX += itemWidth;
        } else {
            if (IsCustomSizeValue_) {
                endVectorBlackPointCenterX[i] = endCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.endLongPointLeftCenterX = endCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.endLongPointRightCenterX = pointCenter.endLongPointLeftCenterX;
                endCenterX += selectedItemWidth;
            } else {
                endVectorBlackPointCenterX[i] = endCenterX + selectedItemWidth;
                pointCenter.endLongPointLeftCenterX = endCenterX + itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.endLongPointRightCenterX = pointCenter.endLongPointLeftCenterX + selectedItemWidth;
                endCenterX += selectedItemWidth * TWOFOLD;
            }
        }
        startCenterX += space;
        endCenterX += space;
    }
    AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, index);
    return CalculatePointCenterX(pointCenter, startVectorBlackPointCenterX, endVectorBlackPointCenterX);
}

std::pair<float, float> DotIndicatorPaintMethod::BackwardCalculation(
    const LinearVector<float>& itemHalfSizes, float startCenterX, float endCenterX, float space, int32_t index)
{
    int32_t startCurrentIndex = index;
    auto itemWidth = itemHalfSizes[ITEM_HALF_WIDTH] * TWOFOLD;
    auto selectedItemWidth = itemHalfSizes[SELECTED_ITEM_HALF_WIDTH] * TWOFOLD;
    StarAndEndPointCenter pointCenter;
    // Calculate the data required for the current pages
    LinearVector<float> startVectorBlackPointCenterX(itemCount_);
    // Calculate the data required for subsequent pages
    LinearVector<float> endVectorBlackPointCenterX(itemCount_);
    int32_t endCurrentIndex = NearEqual(turnPageRate_, 0.0f) || turnPageRate_ <= -1.0f || turnPageRate_ >= 1.0f
        ? endCurrentIndex = index : (turnPageRate_ < 0.0f ? index + 1 : index - 1);
    if (endCurrentIndex == -1) {
        endCurrentIndex = itemCount_ - 1;
    } else if (endCurrentIndex == itemCount_) {
        endCurrentIndex = 0;
    }
    for (int32_t i = itemCount_ - 1; i >= 0; --i) {
        if (i != startCurrentIndex) {
            startVectorBlackPointCenterX[i] = startCenterX - itemHalfSizes[ITEM_HALF_WIDTH];
            startCenterX -= itemWidth;
        } else {
            if (IsCustomSizeValue_) {
                startVectorBlackPointCenterX[i] = startCenterX - itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.startLongPointLeftCenterX = startCenterX - itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.startLongPointRightCenterX = pointCenter.startLongPointLeftCenterX;
                startCenterX -= selectedItemWidth;
            } else {
                startVectorBlackPointCenterX[i] = startCenterX - itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.startLongPointRightCenterX = startCenterX - itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.startLongPointLeftCenterX = pointCenter.startLongPointRightCenterX - selectedItemWidth;
                startCenterX -= selectedItemWidth * TWOFOLD;
            }
        }
        if (i != endCurrentIndex) {
            endVectorBlackPointCenterX[i] = endCenterX - itemHalfSizes[ITEM_HALF_WIDTH];
            endCenterX -= itemWidth;
        } else {
            if (IsCustomSizeValue_) {
                endVectorBlackPointCenterX[i] = endCenterX - itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.endLongPointLeftCenterX = endCenterX - itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.endLongPointRightCenterX = pointCenter.endLongPointLeftCenterX;
                endCenterX -= selectedItemWidth;
            } else {
                endVectorBlackPointCenterX[i] = endCenterX - itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.endLongPointRightCenterX = endCenterX - itemHalfSizes[SELECTED_ITEM_HALF_WIDTH];
                pointCenter.endLongPointLeftCenterX = pointCenter.endLongPointRightCenterX - selectedItemWidth;
                endCenterX -= selectedItemWidth * TWOFOLD;
            }
        }
        startCenterX -= space;
        endCenterX -= space;
    }
    return CalculatePointCenterX(pointCenter, startVectorBlackPointCenterX, endVectorBlackPointCenterX);
}
} // namespace OHOS::Ace::NG
