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

#include "core/components_ng/pattern/slider/slider_content_modifier.h"

#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/path_painter.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5f;
constexpr float SPRING_MOTION_RESPONSE = 0.314f;
constexpr float SPRING_MOTION_DAMPING_FRACTION = 0.95f;
constexpr double DEFAULT_SCALE_VALUE = 1.0;
} // namespace
SliderContentModifier::SliderContentModifier(const Parameters& parameters,
    std::function<void(float)> updateImageCenterX, std::function<void(float)> updateImageCenterY)
    : updateImageCenterX_(std::move(updateImageCenterX)), updateImageCenterY_(std::move(updateImageCenterY)),
      boardColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT)))
{
    // animatable property
    selectStart_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(parameters.selectStart - PointF());
    selectEnd_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(parameters.selectEnd - PointF());
    backStart_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(parameters.backStart - PointF());
    backEnd_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(parameters.backEnd - PointF());
    blockCenterX_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(parameters.circleCenter.GetX());
    blockCenterY_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(parameters.circleCenter.GetY());
    trackThickness_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(parameters.trackThickness);
    trackBackgroundColor_ =
        AceType::MakeRefPtr<AnimatablePropertyVectorColor>(GradientArithmetic(parameters.trackBackgroundColor));
    selectGradientColor_ =
        AceType::MakeRefPtr<AnimatablePropertyVectorColor>(GradientArithmetic(parameters.selectGradientColor));
    blockColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(parameters.blockColor));
    trackBorderRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(parameters.trackThickness * HALF);
    selectedBorderRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(trackBorderRadius_->Get());
    stepSize_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(1);
    blockBorderWidth_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0);
    stepColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::TRANSPARENT);
    blockBorderColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(parameters.blockColor));
    blockSize_ = AceType::MakeRefPtr<AnimatablePropertySizeF>(parameters.blockSize);
    // non-animatable property
    stepRatio_ = AceType::MakeRefPtr<PropertyFloat>(parameters.stepRatio);
    sliderMode_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    directionAxis_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(Axis::HORIZONTAL));
    isShowStep_ = AceType::MakeRefPtr<PropertyBool>(false);
    sliderInteractionMode_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int>(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK));
    minResponse_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    blockType_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(SliderModelNG::BlockStyleType::DEFAULT));
    useContentModifier_ = AceType::MakeRefPtr<PropertyBool>(false);
    isHovered_ = AceType::MakeRefPtr<PropertyBool>(false);
    isPressed_ = AceType::MakeRefPtr<PropertyBool>(false);
    isFocused_ = AceType::MakeRefPtr<PropertyBool>(false);
    // others
    UpdateData(parameters);
    UpdateThemeColor();

    AttachProperty(selectStart_);
    AttachProperty(selectEnd_);
    AttachProperty(backStart_);
    AttachProperty(backEnd_);
    AttachProperty(blockCenterX_);
    AttachProperty(blockCenterY_);
    AttachProperty(trackThickness_);
    AttachProperty(trackBackgroundColor_);
    AttachProperty(selectGradientColor_);
    AttachProperty(blockColor_);
    AttachProperty(boardColor_);
    AttachProperty(trackBorderRadius_);
    AttachProperty(selectedBorderRadius_);
    AttachProperty(stepSize_);
    AttachProperty(blockBorderWidth_);
    AttachProperty(stepColor_);
    AttachProperty(blockBorderColor_);
    AttachProperty(blockSize_);
    AttachProperty(stepRatio_);
    AttachProperty(sliderMode_);
    AttachProperty(directionAxis_);
    AttachProperty(isShowStep_);
    AttachProperty(sliderInteractionMode_);
    AttachProperty(minResponse_);
    AttachProperty(blockType_);
    AttachProperty(isHovered_);
    AttachProperty(isPressed_);
    AttachProperty(isFocused_);

    InitializeShapeProperty();
}

void SliderContentModifier::InitializeShapeProperty()
{
    shapeWidth_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    shapeHeight_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    circleRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    ellipseRadiusX_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    ellipseRadiusY_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    rectTopLeftRadiusX_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    rectTopLeftRadiusY_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    rectTopRightRadiusX_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    rectTopRightRadiusY_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    rectBottomLeftRadiusX_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    rectBottomLeftRadiusY_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    rectBottomRightRadiusX_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    rectBottomRightRadiusY_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f);
    AttachProperty(shapeWidth_);
    AttachProperty(shapeHeight_);
    AttachProperty(circleRadius_);
    AttachProperty(ellipseRadiusX_);
    AttachProperty(ellipseRadiusY_);
    AttachProperty(rectTopLeftRadiusX_);
    AttachProperty(rectTopLeftRadiusY_);
    AttachProperty(rectTopRightRadiusX_);
    AttachProperty(rectTopRightRadiusY_);
    AttachProperty(rectBottomLeftRadiusX_);
    AttachProperty(rectBottomLeftRadiusY_);
    AttachProperty(rectBottomRightRadiusX_);
    AttachProperty(rectBottomRightRadiusY_);
}

void SliderContentModifier::onDraw(DrawingContext& context)
{
    if (useContentModifier_->Get()) {
        return;
    }
    DrawBackground(context);
    DrawStep(context);
    DrawSelect(context);
    DrawShadow(context);
    DrawBlock(context);
    DrawHoverOrPress(context);
}

void SetStartEndPointLocation(Axis& direction, RSRect& trackRect, RSPoint& startPoint, RSPoint& endPoint)
{
    if (direction == Axis::HORIZONTAL) {
        startPoint.SetX(trackRect.GetLeft());
        startPoint.SetY(trackRect.GetTop());
        endPoint.SetX(trackRect.GetRight());
        endPoint.SetY(trackRect.GetTop());
    } else {
        startPoint.SetX(trackRect.GetLeft());
        startPoint.SetY(trackRect.GetTop());
        endPoint.SetX(trackRect.GetLeft());
        endPoint.SetY(trackRect.GetBottom());
    }
}

void SliderContentModifier::DrawBackground(DrawingContext& context)
{
    auto& canvas = context.canvas;
    auto trackBorderRadius = trackBorderRadius_->Get();
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    scaleValue_ = theme->GetFocusedScaleValue();
    std::vector<GradientColor> gradientColors = GetTrackBackgroundColor();
    std::vector<RSColorQuad> colors;
    std::vector<float> pos;
    for (size_t i = 0; i < gradientColors.size(); i++) {
        colors.emplace_back(gradientColors[i].GetLinearColor().GetValue());
        pos.emplace_back(gradientColors[i].GetDimension().Value());
    }
    if (sliderMode_->Get() != static_cast<int32_t>(SliderModel::SliderMode::INSET)) {
        isEnlarge_ = isPressed_->Get() || isHovered_->Get() || isFocused_->Get();
    }
    RSRect trackRect = GetTrackRect();
    auto direction = static_cast<Axis>(directionAxis_->Get());
    RSPoint startPoint;
    RSPoint endPoint;
    SetStartEndPointLocation(direction, trackRect, startPoint, endPoint);
    RSBrush brush;
    brush.SetAntiAlias(true);
    if (reverse_) {
#ifndef USE_ROSEN_DRAWING
        brush.SetShaderEffect(
            RSShaderEffect::CreateLinearGradient(endPoint, startPoint, colors, pos, RSTileMode::CLAMP));
#else
        brush.SetShaderEffect(
            RSRecordingShaderEffect::CreateLinearGradient(endPoint, startPoint, colors, pos, RSTileMode::CLAMP));
#endif
    } else {
#ifndef USE_ROSEN_DRAWING
        brush.SetShaderEffect(
            RSShaderEffect::CreateLinearGradient(startPoint, endPoint, colors, pos, RSTileMode::CLAMP));
#else
        brush.SetShaderEffect(
            RSRecordingShaderEffect::CreateLinearGradient(startPoint, endPoint, colors, pos, RSTileMode::CLAMP));
#endif
    }
    canvas.AttachBrush(brush);
    auto trackRadius = isEnlarge_ ? trackBorderRadius * scaleValue_ : trackBorderRadius;
    RSRoundRect roundRect(trackRect, trackRadius, trackRadius);
    canvas.DrawRoundRect(roundRect);
    canvas.DetachBrush();
    canvas.Save();
    canvas.ClipRoundRect(roundRect, RSClipOp::INTERSECT, true);
}

void SliderContentModifier::AddStepPoint(float startX, float startY, float endX, float endY, RSCanvas& canvas)
{
    auto stepRatio = stepRatio_->Get();
    if (NearEqual(stepRatio, .0f)) {
        return;
    }

    auto stepsLengthX = (endX - startX) * stepRatio;
    auto stepsLengthY = (endY - startY) * stepRatio;
    auto stepSize = stepSize_->Get();
    auto trackThickness = trackThickness_->Get();
    if (GreatNotEqual(stepSize, trackThickness)) {
        stepSize = trackThickness;
    }

    if (reverse_) {
        while (GreatOrEqual(endX, startX) && GreatOrEqual(endY, startY)) {
            canvas.DrawCircle(RSPoint(endX, endY), isEnlarge_ ? stepSize * HALF * scaleValue_ : stepSize * HALF);
            stepPointVec_.emplace_back(PointF(endX, endY));
            endX -= stepsLengthX;
            endY -= stepsLengthY;
        }
        endX += stepsLengthX;
        endY += stepsLengthY;
        if (!NearEqual(endX, startX) || !NearEqual(endY, startY)) {
            stepPointVec_.emplace_back(PointF(startX, startY));
        }
    } else {
        while (LessOrEqual(startX, endX) && LessOrEqual(startY, endY)) {
            canvas.DrawCircle(RSPoint(startX, startY), isEnlarge_ ? stepSize * HALF * scaleValue_ : stepSize * HALF);
            stepPointVec_.emplace_back(PointF(startX, startY));
            startX += stepsLengthX;
            startY += stepsLengthY;
        }
        startX -= stepsLengthX;
        startY -= stepsLengthY;
        if (!NearEqual(startX, endX) || !NearEqual(startY, endY)) {
            stepPointVec_.emplace_back(PointF(endX, endY));
        }
    }
}

void SliderContentModifier::DrawStep(DrawingContext& context)
{
    if (!isShowStep_->Get()) {
        return;
    }
    auto& canvas = context.canvas;
    auto stepColor = stepColor_->Get();
    auto backStart = backStart_->Get();
    auto backEnd = backEnd_->Get();
    auto stepRatio = stepRatio_->Get();
    if (NearEqual(stepRatio, .0f)) {
        return;
    }
    float startX = backStart.GetX();
    float endX = backEnd.GetX();
    float startY = backStart.GetY();
    float endY = backEnd.GetY();
    if (NearEqual(startX, endX) && NearEqual(startY, endY)) {
        return;
    }

    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(stepColor));
    canvas.AttachBrush(brush);
    stepPointVec_.clear();
    AddStepPoint(startX, startY, endX, endY, canvas);
    canvas.DetachBrush();
}

void SliderContentModifier::DrawSelect(DrawingContext& context)
{
    auto& canvas = context.canvas;
    if (!NearEqual(selectStart_->Get().GetX(), selectEnd_->Get().GetX(), HALF) ||
        !NearEqual(selectStart_->Get().GetY(), selectEnd_->Get().GetY(), HALF)) {
        auto selectedBorderRadius = selectedBorderRadius_->Get();
        auto direction = static_cast<Axis>(directionAxis_->Get());
        auto blockCenter = GetBlockCenter();
        auto trackThickness = trackThickness_->Get();
        auto sliderMode = static_cast<SliderModelNG::SliderMode>(sliderMode_->Get());
        auto rect = GetTrackRect();
        auto insetOffset = .0f;
        if (sliderMode == SliderModelNG::SliderMode::INSET) {
            insetOffset = std::max(selectedBorderRadius, trackThickness * HALF);
        }
        if (!reverse_) {
            if (direction == Axis::HORIZONTAL) {
                rect.SetRight(blockCenter.GetX() + insetOffset);
            } else {
                rect.SetBottom(blockCenter.GetY() + insetOffset);
            }
        } else {
            if (direction == Axis::HORIZONTAL) {
                rect.SetLeft(blockCenter.GetX() - insetOffset);
            } else {
                rect.SetTop(blockCenter.GetY() - insetOffset);
            }
        }

        RSBrush brush;
        DrawSelectColor(brush, rect);
        canvas.AttachBrush(brush);
        canvas.DrawRoundRect(RSRoundRect(rect, selectedBorderRadius, selectedBorderRadius));
        canvas.DetachBrush();
    }
    canvas.Restore();
}

void SliderContentModifier::DrawDefaultBlock(DrawingContext& context)
{
    auto& canvas = context.canvas;
    auto borderWidth = blockBorderWidth_->Get();
    auto blockSize = blockSize_->Get();
    auto blockCenter = GetBlockCenter();
    float blockRadius = std::min(blockSize.Width(), blockSize.Height()) * HALF;
    float radius = blockRadius;
    RSBrush brush;
    brush.SetAntiAlias(true);
    if (GreatOrEqual(borderWidth * HALF, radius)) {
        brush.SetColor(ToRSColor(blockBorderColor_->Get()));
    } else {
        radius = std::min(blockSize.Width(), blockSize.Height()) * HALF - borderWidth * HALF;
        brush.SetColor(ToRSColor(blockColor_->Get()));
    }
    canvas.AttachBrush(brush);
    RSPen pen;
    if (!NearEqual(borderWidth, .0f) && LessNotEqual(borderWidth * HALF, blockRadius)) {
        pen.SetAntiAlias(true);
        pen.SetWidth(borderWidth);
        pen.SetColor(ToRSColor(blockBorderColor_->Get()));
        canvas.AttachPen(pen);
    }
    canvas.DrawCircle(
        ToRSPoint(PointF(blockCenter.GetX(), blockCenter.GetY())), isEnlarge_ ? radius * scaleValue_ : radius);
    canvas.DetachBrush();
    if (!NearEqual(borderWidth, .0f) && LessNotEqual(borderWidth * HALF, blockRadius)) {
        canvas.DetachPen();
    }
}

void SliderContentModifier::DrawHoverOrPress(DrawingContext& context)
{
    auto sliderMode = static_cast<SliderModelNG::SliderMode>(sliderMode_->Get());
    if (static_cast<SliderModelNG::BlockStyleType>(blockType_->Get()) != SliderModelNG::BlockStyleType::DEFAULT ||
        sliderMode == SliderModelNG::SliderMode::NONE) {
        return;
    }

    auto& canvas = context.canvas;
    RSPen circleStatePen;
    circleStatePen.SetAntiAlias(true);
    // add animate color
    circleStatePen.SetColor(ToRSColor(boardColor_->Get()));
    circleStatePen.SetWidth(isEnlarge_ ? hotCircleShadowWidth_ * scaleValue_ : hotCircleShadowWidth_);
    canvas.AttachPen(circleStatePen);
    auto blockSize = blockSize_->Get();
    float diameter = std::min(blockSize.Width(), blockSize.Height());
    auto penRadius = (diameter + hotCircleShadowWidth_) * HALF;
    auto blockCenter = GetBlockCenter();
    canvas.DrawCircle(ToRSPoint(blockCenter), isEnlarge_ ? penRadius * scaleValue_ : penRadius);
    canvas.DetachPen();
}

void SliderContentModifier::DrawShadow(DrawingContext& context)
{
    auto sliderMode = static_cast<SliderModelNG::SliderMode>(sliderMode_->Get());
    if (static_cast<SliderModelNG::BlockStyleType>(blockType_->Get()) != SliderModelNG::BlockStyleType::DEFAULT ||
        sliderMode == SliderModelNG::SliderMode::NONE) {
        return;
    }

    if (!mouseHoverFlag_ && !mousePressedFlag_) {
        auto& canvas = context.canvas;
        auto blockSize = blockSize_->Get();
        auto blockCenter = GetBlockCenter();
        float radius = std::min(blockSize.Width(), blockSize.Height()) * HALF;
        canvas.Save();
        RSBrush shadowBrush;
        shadowBrush.SetAntiAlias(true);
        shadowBrush.SetColor(ToRSColor(blockShadowColor_));
        RSFilter filter;
        filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(
            RSBlurType::NORMAL, RSDrawing::ConvertRadiusToSigma(hotCircleShadowWidth_)));
        shadowBrush.SetFilter(filter);

        canvas.AttachBrush(shadowBrush);
        RSPath path;
        path.AddCircle(ToRSPoint(blockCenter).GetX(), ToRSPoint(blockCenter).GetY(), radius);
        canvas.DrawPath(path);
        canvas.DetachBrush();
        canvas.Restore();
    }
}

void SliderContentModifier::SetBoardColor()
{
    CHECK_NULL_VOID(boardColor_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    Color shadowColor = Color::TRANSPARENT;
    shadowColor = mouseHoverFlag_ ? theme->GetBlockHoverColor() : shadowColor;
    shadowColor = mousePressedFlag_ ? theme->GetBlockPressedColor() : shadowColor;
    auto duration = mousePressedFlag_ ? static_cast<int32_t>(theme->GetPressAnimationDuration())
                                      : static_cast<int32_t>(theme->GetHoverAnimationDuration());
    auto curve = mousePressedFlag_ ? Curves::SHARP : Curves::FRICTION;
    AnimationOption option = AnimationOption();
    option.SetDuration(duration);
    option.SetCurve(curve);
    AnimationUtils::Animate(option, [&]() { boardColor_->Set(LinearColor(shadowColor)); });
}

void SliderContentModifier::UpdateData(const Parameters& parameters)
{
    mouseHoverFlag_ = parameters.mouseHoverFlag_;
    mousePressedFlag_ = parameters.mousePressedFlag_;
    hotCircleShadowWidth_ = parameters.hotCircleShadowWidth;
    SetIsHovered(mouseHoverFlag_);
}

void SliderContentModifier::JudgeNeedAnimate(bool reverse)
{
    // when reverse is changed, slider block position changes do not animated.
    if (reverse_ != reverse) {
        SetAnimatorStatus(SliderStatus::DEFAULT);
        reverse_ = reverse;
    }
}

void SliderContentModifier::StopSelectAnimation()
{
    AnimationOption option = AnimationOption();
    option.SetCurve(Curves::LINEAR);
    AnimationUtils::Animate(option, [this]() {
        selectEnd_->Set(selectEnd_->Get());
        if (animatorStatus_ == SliderStatus::MOVE) {
            selectEnd_->Set(targetSelectEnd_);
        }
    });
}

void SliderContentModifier::SetSelectSize(const PointF& start, const PointF& end)
{
    if (selectStart_) {
        selectStart_->Set(start - PointF());
    }
    CHECK_NULL_VOID(selectEnd_);
    auto currentEnd = end - PointF();
    if (targetSelectEnd_ == currentEnd) {
        return;
    }
    if (animatorStatus_ != SliderStatus::DEFAULT && isVisible_) {
        StopSelectAnimation();
        AnimationOption option = AnimationOption();
        auto motion =
            AceType::MakeRefPtr<ResponsiveSpringMotion>(SPRING_MOTION_RESPONSE, SPRING_MOTION_DAMPING_FRACTION);
        option.SetCurve(motion);
        AnimationUtils::Animate(option, [&]() { selectEnd_->Set(end - PointF()); });
    } else {
        selectEnd_->Set(end - PointF());
    }
    targetSelectEnd_ = end - PointF();
}

void SliderContentModifier::StopCircleCenterAnimation()
{
    AnimationOption option = AnimationOption();
    option.SetCurve(Curves::LINEAR);
    AnimationUtils::Animate(option, [this]() {
        if (static_cast<Axis>(directionAxis_->Get()) == Axis::HORIZONTAL) {
            blockCenterX_->Set(blockCenterX_->Get());
        } else {
            blockCenterY_->Set(blockCenterY_->Get());
        }
        if (animatorStatus_ == SliderStatus::MOVE) {
            if (static_cast<Axis>(directionAxis_->Get()) == Axis::HORIZONTAL) {
                blockCenterX_->Set(targetCenter_.GetX());
            } else {
                blockCenterY_->Set(targetCenter_.GetY());
            }
        }
    });
}

void SliderContentModifier::SetCircleCenter(const PointF& center)
{
    if (center == targetCenter_) {
        return;
    }

    CHECK_NULL_VOID(blockCenterX_);
    CHECK_NULL_VOID(blockCenterY_);
    if (animatorStatus_ != SliderStatus::DEFAULT && isVisible_) {
        StopCircleCenterAnimation();
        AnimationOption option = AnimationOption();
        auto motion =
            AceType::MakeRefPtr<ResponsiveSpringMotion>(SPRING_MOTION_RESPONSE, SPRING_MOTION_DAMPING_FRACTION);
        option.SetCurve(motion);
        AnimationUtils::Animate(option, [this, center]() {
            if (static_cast<Axis>(directionAxis_->Get()) == Axis::HORIZONTAL) {
                blockCenterX_->Set(center.GetX());
            } else {
                blockCenterY_->Set(center.GetY());
            }
        });
        if (static_cast<Axis>(directionAxis_->Get()) == Axis::HORIZONTAL) {
            blockCenterY_->Set(center.GetY());
        } else {
            blockCenterX_->Set(center.GetX());
        }
    } else {
        blockCenterX_->Set(center.GetX());
        blockCenterY_->Set(center.GetY());
    }
    targetCenter_ = center;
}

RSRect SliderContentModifier::GetTrackRect()
{
    auto backStart = backStart_->Get();
    auto backEnd = backEnd_->Get();
    auto trackThickness = trackThickness_->Get();
    auto direction = static_cast<Axis>(directionAxis_->Get());
    auto stepSize = stepSize_->Get();
    if (GreatNotEqual(stepSize, trackThickness)) {
        stepSize = trackThickness;
    }
    RSRect rect;
    auto calculatedThickness = isEnlarge_ ? trackThickness * HALF * scaleValue_ : trackThickness * HALF;
    if (direction == Axis::HORIZONTAL) {
        if (sliderMode_->Get() == static_cast<int32_t>(SliderModel::SliderMode::OUTSET)) {
            rect.SetLeft(backStart.GetX() - stepSize * HALF);
            rect.SetRight(backEnd.GetX() + stepSize * HALF);
        } else if (sliderMode_->Get() == static_cast<int32_t>(SliderModel::SliderMode::INSET)) {
            rect.SetLeft(backStart.GetX() - trackThickness * HALF);
            rect.SetRight(backEnd.GetX() + trackThickness * HALF);
        } else {
            rect.SetLeft(backStart.GetX());
            rect.SetRight(backEnd.GetX());
        }
        rect.SetTop(backStart.GetY() - calculatedThickness);
        rect.SetBottom(backEnd.GetY() + calculatedThickness);
    } else {
        rect.SetLeft(backStart.GetX() - calculatedThickness);
        rect.SetRight(backEnd.GetX() + calculatedThickness);
        if (sliderMode_->Get() == static_cast<int32_t>(SliderModel::SliderMode::OUTSET)) {
            rect.SetTop(backStart.GetY() - stepSize * HALF);
            rect.SetBottom(backEnd.GetY() + stepSize * HALF);
        } else if (sliderMode_->Get() == static_cast<int32_t>(SliderModel::SliderMode::INSET)) {
            rect.SetTop(backStart.GetY() - trackThickness * HALF);
            rect.SetBottom(backEnd.GetY() + trackThickness * HALF);
        } else {
            rect.SetTop(backStart.GetY());
            rect.SetBottom(backEnd.GetY());
        }
    }
    return rect;
}

void SliderContentModifier::DrawBlock(DrawingContext& context)
{
    auto sliderMode = static_cast<SliderModelNG::SliderMode>(sliderMode_->Get());
    if (sliderMode != SliderModelNG::SliderMode::NONE) {
        auto blockType = static_cast<SliderModelNG::BlockStyleType>(blockType_->Get());
        if (blockType == SliderModelNG::BlockStyleType::DEFAULT) {
            DrawDefaultBlock(context);
        } else if (blockType == SliderModelNG::BlockStyleType::SHAPE) {
            DrawBlockShape(context);
        } else if (blockType == SliderModelNG::BlockStyleType::IMAGE) {
            auto blockCenter = GetBlockCenter();
            if (updateImageCenterX_) {
                updateImageCenterX_(blockCenter.GetX());
            }
            if (updateImageCenterY_) {
                updateImageCenterY_(blockCenter.GetY());
            }
        }
    }
}

void SliderContentModifier::DrawBlockShape(DrawingContext& context)
{
    if (shape_ == nullptr) {
        return;
    }

    switch (shape_->GetBasicShapeType()) {
        case BasicShapeType::CIRCLE: {
            auto circle = DynamicCast<Circle>(shape_);
            CHECK_NULL_VOID(circle);
            DrawBlockShapeCircle(context, circle);
            break;
        }
        case BasicShapeType::ELLIPSE: {
            auto ellipse = DynamicCast<Ellipse>(shape_);
            CHECK_NULL_VOID(ellipse);
            DrawBlockShapeEllipse(context, ellipse);
            break;
        }
        case BasicShapeType::PATH: {
            auto path = DynamicCast<Path>(shape_);
            CHECK_NULL_VOID(path);
            DrawBlockShapePath(context, path);
            break;
        }
        case BasicShapeType::RECT: {
            auto rect = DynamicCast<ShapeRect>(shape_);
            CHECK_NULL_VOID(rect);
            DrawBlockShapeRect(context, rect);
            break;
        }
        default:
            break;
    }
}

void SliderContentModifier::DrawBlockShapeCircle(DrawingContext& context, RefPtr<Circle>& circle)
{
    auto blockSize = blockSize_->Get();
    auto shapeWidth = shapeWidth_->Get();
    auto shapeHeight = shapeHeight_->Get();
    auto blockBorderWidth = blockBorderWidth_->Get();
    if (NearZero(shapeWidth) || NearZero(shapeHeight)) {
        return;
    }

    auto blockCenter = GetBlockCenter();
    float scale = std::max(blockSize.Width() / shapeWidth, blockSize.Height() / shapeHeight);
    if (NearZero(scale)) {
        return;
    }
    float blockBorderWidthUnscale = blockBorderWidth / scale;

    auto& canvas = context.canvas;
    canvas.Save();
    SetBlockClip(context);
    canvas.Translate(blockCenter.GetX(), blockCenter.GetY());
    canvas.Scale(scale, scale);
    canvas.Translate(-blockCenter.GetX(), -blockCenter.GetY());

    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(blockBorderWidthUnscale);
    pen.SetColor(ToRSColor(blockBorderColor_->Get()));
    canvas.AttachPen(pen);
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(blockColor_->Get()));
    canvas.AttachBrush(brush);

    float radius = std::min(shapeWidth, shapeHeight) * HALF;
    float drawRadius = radius - blockBorderWidthUnscale * HALF;
    PointF drawCenter(
        blockCenter.GetX() - shapeWidth * HALF + radius, blockCenter.GetY() - shapeHeight * HALF + radius);
    canvas.DrawCircle(ToRSPoint(drawCenter), drawRadius);

    canvas.DetachBrush();
    canvas.DetachPen();
    canvas.Restore();
}

void SliderContentModifier::DrawBlockShapeEllipse(DrawingContext& context, RefPtr<Ellipse>& ellipse)
{
    auto blockSize = blockSize_->Get();
    auto shapeWidth = shapeWidth_->Get();
    auto shapeHeight = shapeHeight_->Get();
    auto blockBorderWidth = blockBorderWidth_->Get();
    if (NearZero(shapeWidth) || NearZero(shapeHeight)) {
        return;
    }

    auto blockCenter = GetBlockCenter();
    float scale = std::max(blockSize.Width() / shapeWidth, blockSize.Height() / shapeHeight);
    if (NearZero(scale)) {
        return;
    }
    float blockBorderWidthUnscale = blockBorderWidth / scale;

    auto& canvas = context.canvas;
    canvas.Save();
    SetBlockClip(context);
    canvas.Translate(blockCenter.GetX(), blockCenter.GetY());
    canvas.Scale(scale, scale);
    canvas.Translate(-blockCenter.GetX(), -blockCenter.GetY());

    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(blockBorderWidth);
    pen.SetColor(ToRSColor(blockBorderColor_->Get()));
    canvas.AttachPen(pen);
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(blockColor_->Get()));
    canvas.AttachBrush(brush);

    RectF drawRect(blockCenter.GetX() - shapeWidth * HALF + blockBorderWidthUnscale * HALF,
        blockCenter.GetY() - shapeHeight * HALF + blockBorderWidthUnscale * HALF, shapeWidth - blockBorderWidthUnscale,
        shapeHeight - blockBorderWidthUnscale);
    canvas.DrawOval(ToRSRect(drawRect));

    canvas.DetachBrush();
    canvas.DetachPen();
    canvas.Restore();
}

void SliderContentModifier::DrawBlockShapePath(DrawingContext& context, RefPtr<Path>& path)
{
    auto blockSize = blockSize_->Get();
    auto blockBorderWidth = blockBorderWidth_->Get();

    auto blockCenter = GetBlockCenter();
    SizeF shapeSize = PathPainter::GetPathSize(path->GetValue());
    if (NearZero(shapeSize.Width()) || NearZero(shapeSize.Height())) {
        return;
    }
    float scale = std::max(blockSize.Width() / (shapeSize.Width() + blockBorderWidth),
        blockSize.Height() / (shapeSize.Height() + blockBorderWidth));
    if (NearZero(scale)) {
        return;
    }

    auto& canvas = context.canvas;
    canvas.Save();
    SetBlockClip(context);
    canvas.Translate(blockCenter.GetX(), blockCenter.GetY());
    canvas.Scale(scale, scale);
    canvas.Translate(-blockCenter.GetX(), -blockCenter.GetY());

    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(blockBorderWidth);
    pen.SetColor(ToRSColor(blockBorderColor_->Get()));
    canvas.AttachPen(pen);
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(blockColor_->Get()));
    canvas.AttachBrush(brush);

    OffsetF offset(blockCenter.GetX() - shapeSize.Width() * HALF, blockCenter.GetY() - shapeSize.Height() * HALF);
    PathPainter::DrawPath(canvas, path->GetValue(), offset);
    canvas.DetachBrush();
    canvas.DetachPen();
    canvas.Restore();
}

void SliderContentModifier::SetShapeRectRadius(RSRoundRect& roundRect, float borderWidth)
{
    float radiusX = rectTopLeftRadiusX_->Get() - borderWidth * HALF;
    float radiusY = rectTopLeftRadiusY_->Get() - borderWidth * HALF;
    roundRect.SetCornerRadius(RSRoundRect::TOP_LEFT_POS, radiusX, radiusY);

    radiusX = rectTopRightRadiusX_->Get() - borderWidth * HALF;
    radiusY = rectTopRightRadiusY_->Get() - borderWidth * HALF;
    roundRect.SetCornerRadius(RSRoundRect::TOP_RIGHT_POS, radiusX, radiusY);

    radiusX = rectBottomLeftRadiusX_->Get() - borderWidth * HALF;
    radiusY = rectBottomLeftRadiusY_->Get() - borderWidth * HALF;
    roundRect.SetCornerRadius(RSRoundRect::BOTTOM_LEFT_POS, radiusX, radiusY);

    radiusX = rectBottomRightRadiusX_->Get() - borderWidth * HALF;
    radiusY = rectBottomRightRadiusY_->Get() - borderWidth * HALF;
    roundRect.SetCornerRadius(RSRoundRect::BOTTOM_RIGHT_POS, radiusX, radiusY);
}

void SliderContentModifier::DrawBlockShapeRect(DrawingContext& context, RefPtr<ShapeRect>& rect)
{
    auto shapeWidth = shapeWidth_->Get();
    auto shapeHeight = shapeHeight_->Get();
    if (NearZero(shapeWidth) || NearZero(shapeHeight)) {
        return;
    }
    auto blockSize = blockSize_->Get();
    float scale = std::max(blockSize.Width() / shapeWidth, blockSize.Height() / shapeHeight);
    if (NearZero(scale)) {
        return;
    }
    auto blockBorderWidth = blockBorderWidth_->Get();
    float blockBorderWidthUnscale = blockBorderWidth / scale;
    auto blockCenter = GetBlockCenter();

    auto& canvas = context.canvas;
    canvas.Save();
    SetBlockClip(context);
    canvas.Translate(blockCenter.GetX(), blockCenter.GetY());
    canvas.Scale(scale, scale);
    canvas.Translate(-blockCenter.GetX(), -blockCenter.GetY());

    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(blockBorderWidth_->Get());
    pen.SetColor(ToRSColor(blockBorderColor_->Get()));
    canvas.AttachPen(pen);
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(blockColor_->Get()));
    canvas.AttachBrush(brush);

    RSRoundRect roundRect;
    RSRect rsRect;
    rsRect.SetLeft(blockCenter.GetX() - shapeWidth * HALF + blockBorderWidthUnscale * HALF);
    rsRect.SetRight(blockCenter.GetX() + shapeWidth * HALF - blockBorderWidthUnscale);
    rsRect.SetTop(blockCenter.GetY() - shapeHeight * HALF + blockBorderWidthUnscale * HALF);
    rsRect.SetBottom(blockCenter.GetY() + shapeHeight * HALF - blockBorderWidthUnscale);
    roundRect.SetRect(rsRect);
    SetShapeRectRadius(roundRect, blockBorderWidthUnscale);

    canvas.DrawRoundRect(roundRect);
    canvas.DetachBrush();
    canvas.DetachPen();
    canvas.Restore();
}

void SliderContentModifier::SetBlockShape(const RefPtr<BasicShape>& shape)
{
    shape_ = shape;
    CHECK_NULL_VOID(shape_);
    shapeWidth_->Set(shape_->GetWidth().ConvertToPx());
    shapeHeight_->Set(shape_->GetHeight().ConvertToPx());
    if (shape->GetBasicShapeType() == BasicShapeType::CIRCLE) {
        auto circle = DynamicCast<Circle>(shape_);
        CHECK_NULL_VOID(circle);
        if (circle->GetRadius().IsValid()) {
            circleRadius_->Set(circle->GetRadius().ConvertToPx());
        } else {
            circleRadius_->Set(std::min(shape_->GetWidth().ConvertToPx(), shape_->GetHeight().ConvertToPx()) * HALF);
        }
    } else if (shape->GetBasicShapeType() == BasicShapeType::ELLIPSE) {
        auto ellipse = DynamicCast<Ellipse>(shape_);
        CHECK_NULL_VOID(ellipse);
        if (ellipse->GetRadiusX().IsValid() && ellipse->GetRadiusY().IsValid()) {
            ellipseRadiusX_->Set(ellipse->GetRadiusX().ConvertToPx());
            ellipseRadiusY_->Set(ellipse->GetRadiusY().ConvertToPx());
        } else {
            ellipseRadiusX_->Set(shape_->GetWidth().ConvertToPx() * HALF);
            ellipseRadiusY_->Set(shape_->GetHeight().ConvertToPx() * HALF);
        }
    } else if (shape->GetBasicShapeType() == BasicShapeType::RECT) {
        auto rect = DynamicCast<ShapeRect>(shape_);
        CHECK_NULL_VOID(rect);
        rectTopLeftRadiusX_->Set(rect->GetTopLeftRadius().GetX().ConvertToPx());
        rectTopLeftRadiusY_->Set(rect->GetTopLeftRadius().GetY().ConvertToPx());
        rectTopRightRadiusX_->Set(rect->GetTopRightRadius().GetX().ConvertToPx());
        rectTopRightRadiusY_->Set(rect->GetTopRightRadius().GetY().ConvertToPx());
        rectBottomLeftRadiusX_->Set(rect->GetBottomLeftRadius().GetX().ConvertToPx());
        rectBottomLeftRadiusY_->Set(rect->GetBottomLeftRadius().GetY().ConvertToPx());
        rectBottomRightRadiusX_->Set(rect->GetBottomRightRadius().GetX().ConvertToPx());
        rectBottomRightRadiusY_->Set(rect->GetBottomRightRadius().GetY().ConvertToPx());
    }
}

void SliderContentModifier::UpdateContentDirtyRect(const SizeF& frameSize)
{
    if (useContentModifier_->Get()) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto hotShadowWidth = sliderMode_->Get() == static_cast<int32_t>(SliderModel::SliderMode::OUTSET)
                              ? theme->GetOutsetHotBlockShadowWidth().ConvertToPx()
                              : theme->GetInsetHotBlockShadowWidth().ConvertToPx();
    auto circleSize =
        SizeF(blockSize_->Get().Width() + hotShadowWidth / HALF, blockSize_->Get().Height() + hotShadowWidth / HALF);
    if (GreatNotEqual(scaleValue_, DEFAULT_SCALE_VALUE)) {
        circleSize = circleSize * scaleValue_;
    }
    RectF rect;
    if (directionAxis_->Get() == static_cast<int32_t>(Axis::HORIZONTAL)) {
        auto maxWidth = std::max(circleSize.Height(), frameSize.Height()) * HALF;
        rect.SetOffset(OffsetF(-circleSize.Width(), blockCenterY_->Get() - maxWidth));
        rect.SetSize(SizeF(circleSize.Width() / HALF + frameSize.Width(), maxWidth / HALF));
    } else {
        auto maxWidth = std::max(circleSize.Width(), frameSize.Width()) * HALF;
        rect.SetOffset(OffsetF(blockCenterX_->Get() - maxWidth, -circleSize.Height()));
        rect.SetSize(SizeF(maxWidth / HALF, circleSize.Height() / HALF + frameSize.Height()));
    }

    SetBoundsRect(rect);
}

void SliderContentModifier::SetBlockClip(DrawingContext& context)
{
    auto& canvas = context.canvas;
    auto blockCenter = GetBlockCenter();
    auto blockSize = blockSize_->Get();
    RectF rect(blockCenter.GetX() - blockSize.Width() * HALF, blockCenter.GetY() - blockSize.Height() * HALF,
        blockSize.Width(), blockSize.Height());
    canvas.ClipRect(ToRSRect(rect), RSClipOp::INTERSECT);
}

std::vector<GradientColor> SliderContentModifier::GetTrackBackgroundColor() const
{
    Gradient gradient = SortGradientColorsByOffset(trackBackgroundColor_->Get().GetGradient());
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    // Fault protection processing, if gradientColors is empty, set to default colors.

    if (gradientColors.empty()) {
        auto host = host_.Upgrade();
        CHECK_NULL_RETURN(host, gradientColors);
        auto pipeline = host->GetContext();
        CHECK_NULL_RETURN(pipeline, gradientColors);
        auto theme = pipeline->GetTheme<SliderTheme>(host->GetThemeScopeId());
        CHECK_NULL_RETURN(theme, gradientColors);
        gradientColors = SliderModelNG::CreateSolidGradient(theme->GetTrackBgColor()).GetColors();
    }
    return gradientColors;
}

Gradient SliderContentModifier::SortGradientColorsByOffset(const Gradient& gradient) const
{
    auto srcGradientColors = gradient.GetColors();
    std::sort(
        srcGradientColors.begin(), srcGradientColors.end(), [](const GradientColor& left, const GradientColor& right) {
            return left.GetDimension().Value() < right.GetDimension().Value();
        });

    Gradient sortedGradient;
    for (const auto& item : srcGradientColors) {
        sortedGradient.AddColor(item);
    }

    return sortedGradient;
}

void SliderContentModifier::DrawSelectColor(RSBrush& brush, RSRect& rect)
{
    Gradient gradient = SortGradientColorsByOffset(selectGradientColor_->Get().GetGradient());
    std::vector<GradientColor> gradientColors = gradient.GetColors();

    if (gradientColors.empty()) {
        auto pipeline = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SliderTheme>();
        CHECK_NULL_VOID(theme);
        gradientColors = SliderModelNG::CreateSolidGradient(theme->GetTrackSelectedColor()).GetColors();
    }

    std::vector<RSColorQuad> colors;
    std::vector<float> pos;
    for (size_t i = 0; i < gradientColors.size(); i++) {
        colors.emplace_back(gradientColors[i].GetLinearColor().GetValue());
        pos.emplace_back(gradientColors[i].GetDimension().Value());
    }
    RSPoint startPoint;
    RSPoint endPoint;
    auto direction = static_cast<Axis>(directionAxis_->Get());
    SetStartEndPointLocation(direction, rect, startPoint, endPoint);

    brush.SetAntiAlias(true);
    if (reverse_) {
#ifndef USE_ROSEN_DRAWING
        brush.SetShaderEffect(
            RSShaderEffect::CreateLinearGradient(endPoint, startPoint, colors, pos, RSTileMode::CLAMP));
#else
        brush.SetShaderEffect(
            RSRecordingShaderEffect::CreateLinearGradient(endPoint, startPoint, colors, pos, RSTileMode::CLAMP));
#endif
    } else {
#ifndef USE_ROSEN_DRAWING
        brush.SetShaderEffect(
            RSShaderEffect::CreateLinearGradient(startPoint, endPoint, colors, pos, RSTileMode::CLAMP));
#else
        brush.SetShaderEffect(
            RSRecordingShaderEffect::CreateLinearGradient(startPoint, endPoint, colors, pos, RSTileMode::CLAMP));
#endif
    }
}
} // namespace OHOS::Ace::NG
