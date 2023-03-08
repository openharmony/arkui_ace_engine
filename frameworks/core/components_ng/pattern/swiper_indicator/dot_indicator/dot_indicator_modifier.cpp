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

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_modifier.h"

#include "base/utils/utils.h"
#include "core/animation/spring_curve.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5f;
constexpr float DOUBLE = 2.0f;
constexpr Dimension INDICATOR_ITEM_SPACE = 8.0_vp;
constexpr Dimension INDICATOR_PADDING_DEFAULT = 13.0_vp;
constexpr Dimension INDICATOR_PADDING_HOVER = 12.0_vp;
constexpr float INDICATOR_ZOOM_IN_SCALE = 1.33f;
constexpr int32_t POINT_HOVER_ANIMATION_DURATION = 100;
constexpr int32_t COMPONENT_DILATE_ANIMATION_DURATION = 250;
constexpr int32_t COMPONENT_SHRINK_ANIMATION_DURATION = 300;
constexpr int32_t MOUSE_PRESS_ANIMATION_DURATION = 250;
constexpr int32_t POINT_ANIMATION_DURATION = 400;

constexpr float BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY = 0.4f;
constexpr float LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY = 0.2f;
constexpr float LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY = 1.0f;
constexpr float CENTER_BEZIER_CURVE_MASS = 0.0f;
constexpr float CENTER_BEZIER_CURVE_STIFFNESS = 1.0f;
constexpr float CENTER_BEZIER_CURVE_DAMPING = 1.0f;
} // namespace

void DotIndicatorModifier::onDraw(DrawingContext& context)
{
    ContentProperty contentProperty;
    contentProperty.backgroundColor = backgroundColor_->Get();
    contentProperty.vectorBlackPointCenterX = vectorBlackPointCenterX_->Get();
    contentProperty.longPointLeftCenterX = longPointLeftCenterX_->Get();
    contentProperty.longPointRightCenterX = longPointRightCenterX_->Get();
    contentProperty.normalToHoverPointDilateRatio = normalToHoverPointDilateRatio_->Get();
    contentProperty.hoverToNormalPointDilateRatio = hoverToNormalPointDilateRatio_->Get();
    contentProperty.longPointDilateRatio = longPointDilateRatio_->Get();
    contentProperty.indicatorPadding = indicatorPadding_->Get();
    contentProperty.indicatorMargin = indicatorMargin_->Get();
    contentProperty.itemHalfSizes = itemHalfSizes_->Get();
    PaintBackground(context, contentProperty);
    if (indicatorMask_) {
        PaintMask(context);
    }
    PaintContent(context, contentProperty);
}

void DotIndicatorModifier::PaintBackground(DrawingContext& context, const ContentProperty& contentProperty)
{
    CHECK_NULL_VOID_NOLOG(contentProperty.backgroundColor.GetAlpha());
    auto itemWidth = contentProperty.itemHalfSizes[0] * DOUBLE;
    auto itemHeight = contentProperty.itemHalfSizes[1] * DOUBLE;
    auto selectedItemWidth = contentProperty.itemHalfSizes[2] * DOUBLE;
    auto selectedItemHeight = contentProperty.itemHalfSizes[3] * DOUBLE;
    auto pointNumber = static_cast<float>(contentProperty.vectorBlackPointCenterX.size());
    float allPointDiameterSum = itemWidth * (pointNumber + 1);
    if ((contentProperty.itemHalfSizes[0] != contentProperty.itemHalfSizes[2]) ||
        (contentProperty.itemHalfSizes[1] != contentProperty.itemHalfSizes[3])) {
        allPointDiameterSum = itemWidth * static_cast<float>(pointNumber - 1) + selectedItemWidth;
    }
    float allPointSpaceSum = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()) * (pointNumber - 1);

    // Background necessary property
    float rectWidth =
        contentProperty.indicatorPadding + allPointDiameterSum + allPointSpaceSum + contentProperty.indicatorPadding;
    float rectHeight = contentProperty.indicatorPadding + itemHeight + contentProperty.indicatorPadding;
    if (selectedItemHeight > itemHeight) {
        rectHeight = contentProperty.indicatorPadding + selectedItemHeight + contentProperty.indicatorPadding;
    }

    // Property to get the rectangle offset
    float rectLeft =
        axis_ == Axis::HORIZONTAL ? contentProperty.indicatorMargin.GetX() : contentProperty.indicatorMargin.GetY();
    float rectTop =
        axis_ == Axis::HORIZONTAL ? contentProperty.indicatorMargin.GetY() : contentProperty.indicatorMargin.GetX();
    // Adapter circle and rect
    float rectRight = rectLeft + (axis_ == Axis::HORIZONTAL ? rectWidth : rectHeight);
    float rectBottom = rectTop + (axis_ == Axis::HORIZONTAL ? rectHeight : rectWidth);
    // Paint background
    RSCanvas canvas = context.canvas;
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(contentProperty.backgroundColor));
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect({ { rectLeft, rectTop, rectRight, rectBottom }, rectHeight * HALF, rectHeight * HALF });
}

void DotIndicatorModifier::PaintContent(DrawingContext& context, ContentProperty& contentProperty)
{
    RSCanvas canvas = context.canvas;
    for (size_t i = 0; i < contentProperty.vectorBlackPointCenterX.size(); ++i) {
        LinearVector<float> itemHalfSizes = GetItemHalfSizes(i, contentProperty);
        OffsetF center = { contentProperty.vectorBlackPointCenterX[i], centerY_ };
        PaintUnselectedIndicator(canvas, center, itemHalfSizes);
    }
    OffsetF leftCenter = { contentProperty.longPointLeftCenterX, centerY_ };
    OffsetF rightCenter = { contentProperty.longPointRightCenterX, centerY_ };
    OffsetF centerDistance = rightCenter - leftCenter;
    OffsetF centerDilateDistance = centerDistance * contentProperty.longPointDilateRatio;
    leftCenter -= (centerDilateDistance - centerDistance) * HALF;
    rightCenter += (centerDilateDistance - centerDistance) * HALF;
    PaintSelectedIndicator(
        canvas, leftCenter, rightCenter, contentProperty.itemHalfSizes * contentProperty.longPointDilateRatio);
}

LinearVector<float> DotIndicatorModifier::GetItemHalfSizes(size_t index, ContentProperty& contentProperty)
{
    if (normalToHoverIndex_.has_value() && normalToHoverIndex_ == index) {
        contentProperty.itemHalfSizes[0] *= contentProperty.normalToHoverPointDilateRatio;
        contentProperty.itemHalfSizes[1] *= contentProperty.normalToHoverPointDilateRatio;
        contentProperty.itemHalfSizes[2] *= contentProperty.normalToHoverPointDilateRatio;
        contentProperty.itemHalfSizes[3] *= contentProperty.normalToHoverPointDilateRatio;
        return contentProperty.itemHalfSizes;
    }
    if (hoverToNormalIndex_.has_value() && hoverToNormalIndex_ == index) {
        contentProperty.itemHalfSizes[0] *= contentProperty.hoverToNormalPointDilateRatio;
        contentProperty.itemHalfSizes[1] *= contentProperty.hoverToNormalPointDilateRatio;
        contentProperty.itemHalfSizes[2] *= contentProperty.hoverToNormalPointDilateRatio;
        contentProperty.itemHalfSizes[3] *= contentProperty.hoverToNormalPointDilateRatio;
        return contentProperty.itemHalfSizes;
    }
    return contentProperty.itemHalfSizes;
}

void DotIndicatorModifier::PaintUnselectedIndicator(
    RSCanvas& canvas, const OffsetF& center, const LinearVector<float>& itemHalfSizes)
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(unselectedColor_));
    canvas.AttachBrush(brush);
    if ((itemHalfSizes[0] != itemHalfSizes[2]) || (itemHalfSizes[1] != itemHalfSizes[3])) {
        float rectLeft = (axis_ == Axis::HORIZONTAL ? center.GetX() : center.GetY()) - itemHalfSizes[0];
        float rectTop = (axis_ == Axis::HORIZONTAL ? center.GetY() : center.GetX()) - itemHalfSizes[1];
        float rectRight = (axis_ == Axis::HORIZONTAL ? center.GetX() : center.GetY()) + itemHalfSizes[0];
        float rectBottom = (axis_ == Axis::HORIZONTAL ? center.GetY() : center.GetX()) + itemHalfSizes[1];
        canvas.DrawRoundRect({ { rectLeft, rectTop, rectRight, rectBottom }, itemHalfSizes[1], itemHalfSizes[1] });
    } else {
        float pointX = axis_ == Axis::HORIZONTAL ? center.GetX() : center.GetY();
        float pointY = axis_ == Axis::HORIZONTAL ? center.GetY() : center.GetX();
        canvas.DrawCircle({ pointX, pointY }, itemHalfSizes[1]);
    }
}

void DotIndicatorModifier::PaintSelectedIndicator(
    RSCanvas& canvas, const OffsetF& leftCenter, const OffsetF& rightCenter, const LinearVector<float>& itemHalfSizes)
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(selectedColor_));
    canvas.AttachBrush(brush);
    // TODO: the center distance should also be enlarged
    float rectLeft = (axis_ == Axis::HORIZONTAL ? leftCenter.GetX() : leftCenter.GetY()) - itemHalfSizes[2];
    float rectTop = (axis_ == Axis::HORIZONTAL ? leftCenter.GetY() : leftCenter.GetX()) - itemHalfSizes[3];
    float rectRight = (axis_ == Axis::HORIZONTAL ? rightCenter.GetX() : rightCenter.GetY()) + itemHalfSizes[2];
    float rectBottom = (axis_ == Axis::HORIZONTAL ? rightCenter.GetY() : rightCenter.GetX()) + itemHalfSizes[3];
    canvas.DrawRoundRect({ { rectLeft, rectTop, rectRight, rectBottom }, itemHalfSizes[3], itemHalfSizes[3] });
}

void DotIndicatorModifier::PaintMask(DrawingContext& context)
{
    RSCanvas canvas = context.canvas;

    RSBrush brush;
    brush.SetAntiAlias(true);
    canvas.Save();

    std::vector<RSColorQuad> colors;
    colors.push_back(0x00000000);
    colors.push_back(0xff000000);
    colors.push_back(0xff000000);

    RSPoint startPt = { offset_.GetX(), offset_.GetY() };
    RSPoint endPt = { offset_.GetX(), offset_.GetY() };
    startPt -= axis_ == Axis::HORIZONTAL ? RSPoint(0, (9.0_vp).ConvertToPx()) : RSPoint((9.0_vp).ConvertToPx(), 0);
    endPt += axis_ == Axis::HORIZONTAL ? RSPoint(0, (15.0_vp).ConvertToPx()) : RSPoint((15.0_vp).ConvertToPx(), 0);

    std::vector<float> pos = { 0.0f, 0.75f, 1.0f };

    brush.SetShaderEffect(RSShaderEffect::CreateLinearGradient(startPt, endPt, colors, pos, RSTileMode::CLAMP));
    canvas.DrawRect({ startPt.GetX(), startPt.GetY(), endPt.GetX(), endPt.GetY() });
}

void DotIndicatorModifier::UpdateShrinkPaintProperty(
    const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
    const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX)
{
    indicatorMargin_->Set(margin);
    indicatorPadding_->Set(static_cast<float>(INDICATOR_PADDING_DEFAULT.ConvertToPx()));

    vectorBlackPointCenterX_->Set(vectorBlackPointCenterX);
    longPointLeftCenterX_->Set(longPointCenterX.first);
    longPointRightCenterX_->Set(longPointCenterX.second);
    itemHalfSizes_->Set(normalItemHalfSizes);
    normalToHoverPointDilateRatio_->Set(1.0f);
    hoverToNormalPointDilateRatio_->Set(1.0f);
    longPointDilateRatio_->Set(1.0f);
}

void DotIndicatorModifier::UpdateDilatePaintProperty(
    const LinearVector<float>& hoverItemHalfSizes, const LinearVector<float>& vectorBlackPointCenterX,
    const std::pair<float, float>& longPointCenterX)
{
    indicatorMargin_->Set({ 0, 0 });
    indicatorPadding_->Set(static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx()));

    vectorBlackPointCenterX_->Set(vectorBlackPointCenterX);
    longPointLeftCenterX_->Set(longPointCenterX.first);
    longPointRightCenterX_->Set(longPointCenterX.second);
    itemHalfSizes_->Set(hoverItemHalfSizes);
}

void DotIndicatorModifier::UpdateBackgroundColor(const Color& backgroundColor)
{
    backgroundColor_->Set(LinearColor(backgroundColor));
}

void DotIndicatorModifier::UpdateNormalPaintProperty(
    const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
    const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX)
{
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    auto backgroundColor = swiperTheme->GetHoverColor().ChangeOpacity(0);
    UpdateShrinkPaintProperty(margin, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    UpdateBackgroundColor(backgroundColor);
}

void DotIndicatorModifier::UpdateHoverPaintProperty(
    const LinearVector<float>& hoverItemHalfSizes,
    const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX)
{
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    auto backgroundColor = swiperTheme->GetHoverColor();
    UpdateDilatePaintProperty(hoverItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    UpdateBackgroundColor(backgroundColor);
}

void DotIndicatorModifier::UpdatePressPaintProperty(
    const LinearVector<float>& hoverItemHalfSizes,
    const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX)
{
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    auto backgroundColor = swiperTheme->GetPressedColor();
    UpdateDilatePaintProperty(hoverItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    UpdateBackgroundColor(backgroundColor);
}

void DotIndicatorModifier::UpdateNormalToHoverPaintProperty(
    const LinearVector<float>& hoverItemHalfSizes, const LinearVector<float>& vectorBlackPointCenterX,
    const std::pair<float, float>& longPointCenterX)
{
    AnimationOption option;
    option.SetDuration(COMPONENT_DILATE_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(
        option, [&]() { this->UpdateHoverPaintProperty(hoverItemHalfSizes, vectorBlackPointCenterX, longPointCenterX); });
}

void DotIndicatorModifier::UpdateHoverToNormalPaintProperty(
    const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
    const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX)
{
    AnimationOption option;
    option.SetDuration(COMPONENT_SHRINK_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [&]() {
        this->UpdateNormalPaintProperty(margin, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    });
}

void DotIndicatorModifier::UpdateNormalToPressPaintProperty(
    const LinearVector<float>& hoverItemHalfSizes, const LinearVector<float>& vectorBlackPointCenterX,
    const std::pair<float, float>& longPointCenterX)
{
    AnimationOption option;
    option.SetDuration(COMPONENT_DILATE_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(
        option, [&]() { this->UpdatePressPaintProperty(hoverItemHalfSizes, vectorBlackPointCenterX, longPointCenterX); });
}

void DotIndicatorModifier::UpdatePressToNormalPaintProperty(
    const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
    const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX)
{
    AnimationOption option;
    option.SetDuration(COMPONENT_SHRINK_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [&]() {
        this->UpdateNormalPaintProperty(margin, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    });
}

void DotIndicatorModifier::UpdateHoverAndPressConversionPaintProperty()
{
    auto swiperTheme = GetSwiperIndicatorTheme();
    CHECK_NULL_VOID(swiperTheme);
    Color backgroundColor = isPressed_ ? swiperTheme->GetPressedColor() : swiperTheme->GetHoverColor();
    AnimationOption option;
    option.SetDuration(MOUSE_PRESS_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [&]() { this->UpdateBackgroundColor(backgroundColor); });
}

void DotIndicatorModifier::UpdateNormalToHoverPointDilateRatio()
{
    normalToHoverPointDilateRatio_->Set(1.0f);
    AnimationOption option;
    option.SetDuration(POINT_HOVER_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [&]() { normalToHoverPointDilateRatio_->Set(INDICATOR_ZOOM_IN_SCALE); });
}

void DotIndicatorModifier::UpdateHoverToNormalPointDilateRatio()
{
    hoverToNormalPointDilateRatio_->Set(normalToHoverPointDilateRatio_->Get());
    AnimationOption option;
    option.SetDuration(POINT_HOVER_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [&]() { hoverToNormalPointDilateRatio_->Set(1.0f); });
}

void DotIndicatorModifier::UpdateLongPointDilateRatio()
{
    AnimationOption option;
    option.SetDuration(POINT_HOVER_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    if (longPointIsHover_) {
        AnimationUtils::Animate(option, [&]() { longPointDilateRatio_->Set(INDICATOR_ZOOM_IN_SCALE); });
    } else {
        AnimationUtils::Animate(option, [&]() { longPointDilateRatio_->Set(1.0f); });
    }
}

void DotIndicatorModifier::UpdateAllPointCenterXAnimation(
    bool isForward, const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX)
{
    AnimationOption blackPointOption;
    blackPointOption.SetDuration(POINT_ANIMATION_DURATION);
    blackPointOption.SetCurve(AceType::MakeRefPtr<CubicCurve>(BLACK_POINT_CENTER_BEZIER_CURVE_VELOCITY,
        CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING));
    AnimationUtils::Animate(blackPointOption, [&]() { vectorBlackPointCenterX_->Set(vectorBlackPointCenterX); });

    AnimationOption longPointLeftOption;
    longPointLeftOption.SetDuration(POINT_ANIMATION_DURATION);
    longPointLeftOption.SetCurve(AceType::MakeRefPtr<CubicCurve>(
        isForward ? LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY : LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY,
        CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING));
    AnimationUtils::Animate(longPointLeftOption, [&]() { longPointLeftCenterX_->Set(longPointCenterX.first); });

    AnimationOption longPointRightOption;
    longPointRightOption.SetDuration(POINT_ANIMATION_DURATION);
    longPointRightOption.SetCurve(AceType::MakeRefPtr<CubicCurve>(
        isForward ? LONG_POINT_LEFT_CENTER_BEZIER_CURVE_VELOCITY : LONG_POINT_RIGHT_CENTER_BEZIER_CURVE_VELOCITY,
        CENTER_BEZIER_CURVE_MASS, CENTER_BEZIER_CURVE_STIFFNESS, CENTER_BEZIER_CURVE_DAMPING));
    AnimationUtils::Animate(longPointRightOption, [&]() { longPointRightCenterX_->Set(longPointCenterX.second); });
}
} // namespace OHOS::Ace::NG
