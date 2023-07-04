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

#include <optional>
#include <utility>

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/animation/curves.h"
#include "core/components/common/properties/color.h"
#include "core/components/slider/slider_theme.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/path_painter.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5f;
constexpr Dimension CIRCLE_SHADOW_WIDTH = 1.0_vp;
constexpr float SPRING_MOTION_RESPONSE = 0.314f;
constexpr float SPRING_MOTION_DAMPING_FRACTION = 0.95f;
} // namespace
SliderContentModifier::SliderContentModifier(const Parameters& parameters, std::function<void()> updateImageFunc)
    : updateImageFunc_(std::move(updateImageFunc)),
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
    trackBackgroundColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(parameters.trackBackgroundColor));
    selectColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(parameters.selectColor));
    blockColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(parameters.blockColor));
    trackBorderRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(parameters.trackThickness * HALF);
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
    blockType_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(SliderModelNG::BlockStyleType::DEFAULT));
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
    AttachProperty(selectColor_);
    AttachProperty(blockColor_);
    AttachProperty(boardColor_);
    AttachProperty(trackBorderRadius_);
    AttachProperty(stepSize_);
    AttachProperty(blockBorderWidth_);
    AttachProperty(stepColor_);
    AttachProperty(blockBorderColor_);
    AttachProperty(blockSize_);
    AttachProperty(stepRatio_);
    AttachProperty(sliderMode_);
    AttachProperty(directionAxis_);
    AttachProperty(isShowStep_);
    AttachProperty(blockType_);

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
    DrawBackground(context);
    DrawStep(context);
    DrawSelect(context);
    DrawBlock(context);
    DrawShadow(context);
    DrawHoverOrPress(context);
}

void SliderContentModifier::DrawBackground(DrawingContext& context)
{
    auto& canvas = context.canvas;
    auto trackBorderRadius = trackBorderRadius_->Get();

    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(trackBackgroundColor_->Get()));

    canvas.AttachBrush(brush);
    RSRoundRect roundRect(GetTrackRect(), trackBorderRadius, trackBorderRadius);
    canvas.DrawRoundRect(roundRect);
    canvas.DetachBrush();
}

void SliderContentModifier::DrawStep(DrawingContext& context)
{
    if (!isShowStep_->Get()) {
        return;
    }
    auto& canvas = context.canvas;
    auto stepSize = stepSize_->Get();
    auto stepColor = stepColor_->Get();
    auto direction = static_cast<Axis>(directionAxis_->Get());
    auto backStart = backStart_->Get();
    auto backEnd = backEnd_->Get();
    auto stepRatio = stepRatio_->Get();
    if (NearEqual(stepRatio, .0f)) {
        return;
    }

    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(stepColor));

    canvas.AttachBrush(brush);
    // Distance between slide track and Content boundary
    auto centerWidth = direction == Axis::HORIZONTAL ? context.height : context.width;
    centerWidth *= HALF;
    if (direction == Axis::HORIZONTAL) {
        auto stepsLength = (backEnd.GetX() - backStart.GetX()) * stepRatio;
        float dyOffset = backEnd.GetY();
        float start = backStart.GetX();
        float end = backEnd.GetX();
        float current = start;
        while (LessOrEqual(current, end)) {
            float dxOffset = std::clamp(current, start, end);
            canvas.DrawCircle(RSPoint(dxOffset, dyOffset), stepSize * HALF);
            current += stepsLength;
        }
    } else {
        auto stepsLength = (backEnd.GetY() - backStart.GetY()) * stepRatio;
        float dxOffset = backEnd.GetX();
        float start = backStart.GetY();
        float end = backEnd.GetY();
        float current = start;
        while (LessOrEqual(current, end)) {
            float dyOffset = std::clamp(current, start, end);
            canvas.DrawCircle(RSPoint(dxOffset, dyOffset), stepSize * HALF);
            current += stepsLength;
        }
    }

    canvas.DetachBrush();
}

void SliderContentModifier::DrawSelect(DrawingContext& context)
{
    auto& canvas = context.canvas;
    if (selectStart_->Get() != selectEnd_->Get()) {
        auto trackBorderRadius = trackBorderRadius_->Get();
        auto direction = static_cast<Axis>(directionAxis_->Get());
        auto blockCenter = PointF(blockCenterX_->Get(), blockCenterY_->Get());
        auto trackThickness = trackThickness_->Get();
        auto sliderMode = static_cast<SliderModelNG::SliderMode>(sliderMode_->Get());
        auto rect = GetTrackRect();
        auto insetOffset = .0f;
        if (sliderMode == SliderModelNG::SliderMode::INSET) {
            insetOffset = trackThickness * HALF;
        }
        if (!reverse_) {
            if (direction == Axis::HORIZONTAL) {
                rect.SetRight(blockCenter.GetX() + std::max(trackBorderRadius, insetOffset));
            } else {
                rect.SetBottom(blockCenter.GetY() + std::max(trackBorderRadius, insetOffset));
            }
        } else {
            if (direction == Axis::HORIZONTAL) {
                rect.SetLeft(blockCenter.GetX() - std::max(trackBorderRadius, insetOffset));
            } else {
                rect.SetTop(blockCenter.GetY() - std::max(trackBorderRadius, insetOffset));
            }
        }

        RSBrush brush;
        brush.SetAntiAlias(true);
        brush.SetColor(ToRSColor(selectColor_->Get()));

        canvas.AttachBrush(brush);
        canvas.DrawRoundRect(RSRoundRect(rect, trackBorderRadius, trackBorderRadius));
        canvas.DetachBrush();
    }
}

void SliderContentModifier::DrawDefaultBlock(DrawingContext& context)
{
    auto& canvas = context.canvas;
    auto borderWidth = blockBorderWidth_->Get();

    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(borderWidth);
    pen.SetColor(ToRSColor(blockBorderColor_->Get()));
    if (!NearEqual(borderWidth, .0f)) {
        canvas.AttachPen(pen);
    }
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(blockColor_->Get()));
    canvas.AttachBrush(brush);

    auto blockSize = blockSize_->Get();
    auto blockCenter = PointF(blockCenterX_->Get(), blockCenterY_->Get());
    float radius = std::min(blockSize.Width(), blockSize.Height()) * HALF - borderWidth * HALF;
    canvas.DrawCircle(ToRSPoint(blockCenter), radius);
    canvas.DetachBrush();
    if (!NearEqual(borderWidth, .0f)) {
        canvas.DetachPen();
    }
}

void SliderContentModifier::DrawHoverOrPress(DrawingContext& context)
{
    if (static_cast<SliderModelNG::BlockStyleType>(blockType_->Get()) != SliderModelNG::BlockStyleType::DEFAULT) {
        return;
    }

    auto& canvas = context.canvas;
    RSPen circleStatePen;
    circleStatePen.SetAntiAlias(true);
    // add animate color
    circleStatePen.SetColor(ToRSColor(boardColor_->Get()));
    circleStatePen.SetWidth(hotCircleShadowWidth_);
    canvas.AttachPen(circleStatePen);
    auto blockSize = blockSize_->Get();
    float diameter = std::min(blockSize.Width(), blockSize.Height());
    auto penRadius = (diameter + hotCircleShadowWidth_) * HALF;
    auto blockCenter = PointF(blockCenterX_->Get(), blockCenterY_->Get());
    canvas.DrawCircle(ToRSPoint(blockCenter), penRadius);
    canvas.DetachPen();
}

void SliderContentModifier::DrawShadow(DrawingContext& context)
{
    if (static_cast<SliderModelNG::BlockStyleType>(blockType_->Get()) != SliderModelNG::BlockStyleType::DEFAULT) {
        return;
    }

    auto& canvas = context.canvas;
    if (!mouseHoverFlag_ && !mousePressedFlag_) {
        RSPen circleShadowPen;
        circleShadowPen.SetAntiAlias(true);
        circleShadowPen.SetColor(ToRSColor(blockOuterEdgeColor_));
        circleShadowPen.SetWidth(static_cast<float>(CIRCLE_SHADOW_WIDTH.ConvertToPx()));
        canvas.AttachPen(circleShadowPen);
        auto blockSize = blockSize_->Get();
        float diameter = std::min(blockSize.Width(), blockSize.Height());
        auto penRadius = (diameter + static_cast<float>(CIRCLE_SHADOW_WIDTH.ConvertToPx())) * HALF;
        auto blockCenter = PointF(blockCenterX_->Get(), blockCenterY_->Get());
        canvas.DrawCircle(ToRSPoint(blockCenter), penRadius);
        canvas.DetachPen();
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
}

void SliderContentModifier::JudgeNeedAimate(const RefPtr<SliderPaintProperty>& property)
{
    auto reverse = property->GetReverseValue(false);
    // when reverse is changed, slider block position changes do not animated.
    if (reverse_ != reverse) {
        SetNotAnimated();
        reverse_ = reverse;
    }
}

void SliderContentModifier::SetSelectSize(const PointF& start, const PointF& end)
{
    if (selectStart_) {
        selectStart_->Set(start - PointF());
    }
    CHECK_NULL_VOID(selectEnd_);
    if (needAnimate_ && isVisible_) {
        AnimationOption option = AnimationOption();
        auto motion =
            AceType::MakeRefPtr<ResponsiveSpringMotion>(SPRING_MOTION_RESPONSE, SPRING_MOTION_DAMPING_FRACTION);
        option.SetCurve(motion);
        AnimationUtils::Animate(option, [&]() { selectEnd_->Set(end - PointF()); });
    } else {
        selectEnd_->Set(end - PointF());
    }
}

void SliderContentModifier::SetCircleCenter(const PointF& center)
{
    CHECK_NULL_VOID(blockCenterX_);
    CHECK_NULL_VOID(blockCenterY_);
    if (needAnimate_ && isVisible_) {
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
}

RSRect SliderContentModifier::GetTrackRect()
{
    auto backStart = backStart_->Get();
    auto backEnd = backEnd_->Get();
    auto trackThickness = trackThickness_->Get();

    RSRect rect;
    rect.SetLeft(backStart.GetX() - trackThickness * HALF);
    rect.SetRight(backEnd.GetX() + trackThickness * HALF);
    rect.SetTop(backStart.GetY() - trackThickness * HALF);
    rect.SetBottom(backEnd.GetY() + trackThickness * HALF);

    return rect;
}

void SliderContentModifier::DrawBlock(DrawingContext& context)
{
    auto blockType = static_cast<SliderModelNG::BlockStyleType>(blockType_->Get());
    if (blockType == SliderModelNG::BlockStyleType::DEFAULT) {
        DrawDefaultBlock(context);
    } else if (blockType == SliderModelNG::BlockStyleType::SHAPE) {
        DrawBlockShape(context);
    } else if (blockType == SliderModelNG::BlockStyleType::IMAGE) {
        if (updateImageFunc_ != nullptr) {
            updateImageFunc_();
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
            LOGW("Invalid shape type [%{public}d]", static_cast<int>(shape_->GetBasicShapeType()));
            break;
    }
}

void SliderContentModifier::DrawBlockShapeCircle(DrawingContext& context, RefPtr<Circle>& circle)
{
    auto blockSize = blockSize_->Get();
    auto shapeWidth = shapeWidth_->Get();
    auto shapeHeight = shapeHeight_->Get();

    auto& canvas = context.canvas;
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(blockBorderWidth_->Get());
    pen.SetColor(ToRSColor(blockBorderColor_->Get()));
    canvas.AttachPen(pen);
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(blockColor_->Get()));
    canvas.AttachBrush(brush);

    float width = std::min(shapeWidth, blockSize.Width());
    float height = std::min(shapeHeight, blockSize.Height());
    float radius = std::min(width, height) * HALF;
    if (circle->GetRadius().IsValid()) {
        radius = circleRadius_->Get();
    }

    auto blockCenter = PointF(blockCenterX_->Get(), blockCenterY_->Get());
    canvas.DrawCircle(ToRSPoint(blockCenter), radius);
    canvas.DetachBrush();
    canvas.DetachPen();
}

void SliderContentModifier::DrawBlockShapeEllipse(DrawingContext& context, RefPtr<Ellipse>& ellipse)
{
    auto blockSize = blockSize_->Get();
    auto shapeWidth = shapeWidth_->Get();
    auto shapeHeight = shapeHeight_->Get();

    auto& canvas = context.canvas;
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(blockBorderWidth_->Get());
    pen.SetColor(ToRSColor(blockBorderColor_->Get()));
    canvas.AttachPen(pen);
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(blockColor_->Get()));
    canvas.AttachBrush(brush);

    auto blockCenter = PointF(blockCenterX_->Get(), blockCenterY_->Get());
    float width = std::min(shapeWidth, blockSize.Width());
    float height = std::min(shapeHeight, blockSize.Height());
    float x = blockCenter.GetX() - width * HALF;
    float y = blockCenter.GetY() - height * HALF;
    if (ellipse->GetRadiusX().IsValid() && ellipse->GetRadiusY().IsValid()) {
        float radiusX = ellipseRadiusX_->Get();
        float radiusY = ellipseRadiusY_->Get();
        x = blockCenter.GetX() - radiusX;
        y = blockCenter.GetY() - radiusY;
        width = radiusX / HALF;
        height = radiusY / HALF;
    }
    canvas.DrawOval(ToRSRect(RectF(x, y, width, height)));
    canvas.DetachBrush();
    canvas.DetachPen();
}

void SliderContentModifier::DrawBlockShapePath(DrawingContext& context, RefPtr<Path>& path)
{
    auto& canvas = context.canvas;
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(blockBorderWidth_->Get());
    pen.SetColor(ToRSColor(blockBorderColor_->Get()));
    canvas.AttachPen(pen);
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(blockColor_->Get()));
    canvas.AttachBrush(brush);

    auto blockSize = blockSize_->Get();
    auto blockCenter = PointF(blockCenterX_->Get(), blockCenterY_->Get());
    OffsetF offset(blockCenter.GetX() - blockSize.Width() * HALF, blockCenter.GetY() - blockSize.Height() * HALF);
    PathPainter::DrawPath(canvas, path->GetValue(), offset);
    canvas.DetachBrush();
    canvas.DetachPen();
}

void SliderContentModifier::DrawBlockShapeRect(DrawingContext& context, RefPtr<ShapeRect>& rect)
{
    auto blockSize = blockSize_->Get();
    auto shapeWidth = shapeWidth_->Get();
    auto shapeHeight = shapeHeight_->Get();

    auto& canvas = context.canvas;
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(blockBorderWidth_->Get());
    pen.SetColor(ToRSColor(blockBorderColor_->Get()));
    canvas.AttachPen(pen);
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(blockColor_->Get()));
    canvas.AttachBrush(brush);

    auto blockCenter = PointF(blockCenterX_->Get(), blockCenterY_->Get());
    float width = std::min(shapeWidth, blockSize.Width());
    float height = std::min(shapeHeight, blockSize.Height());

    RSRoundRect roundRect;
    RSRect rsRect;
    rsRect.SetLeft(blockCenter.GetX() - width * HALF);
    rsRect.SetRight(blockCenter.GetX() + width * HALF);
    rsRect.SetTop(blockCenter.GetY() - height * HALF);
    rsRect.SetBottom(blockCenter.GetY() + height * HALF);
    roundRect.SetRect(rsRect);

    float radiusX = rectTopLeftRadiusX_->Get();
    float radiusY = rectTopLeftRadiusY_->Get();
    roundRect.SetCornerRadius(RSRoundRect::TOP_LEFT_POS, radiusX, radiusY);

    radiusX = rectTopRightRadiusX_->Get();
    radiusY = rectTopRightRadiusY_->Get();
    roundRect.SetCornerRadius(RSRoundRect::TOP_RIGHT_POS, radiusX, radiusY);

    radiusX = rectBottomLeftRadiusX_->Get();
    radiusY = rectBottomLeftRadiusY_->Get();
    roundRect.SetCornerRadius(RSRoundRect::BOTTOM_LEFT_POS, radiusX, radiusY);

    radiusX = rectBottomRightRadiusX_->Get();
    radiusY = rectBottomRightRadiusY_->Get();
    roundRect.SetCornerRadius(RSRoundRect::BOTTOM_RIGHT_POS, radiusX, radiusY);

    canvas.DrawRoundRect(roundRect);
    canvas.DetachBrush();
    canvas.DetachPen();
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto hotShadowWidth = sliderMode_->Get() == static_cast<int32_t>(SliderModel::SliderMode::OUTSET)
                              ? theme->GetOutsetHotBlockShadowWidth().ConvertToPx()
                              : theme->GetInsetHotBlockShadowWidth().ConvertToPx();
    auto circleSize =
        SizeF(blockSize_->Get().Width() + hotShadowWidth / HALF, blockSize_->Get().Height() + hotShadowWidth / HALF);
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
} // namespace OHOS::Ace::NG
