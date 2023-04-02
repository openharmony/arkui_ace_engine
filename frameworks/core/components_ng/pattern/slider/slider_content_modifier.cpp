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
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5f;
constexpr Dimension CIRCLE_SHADOW_WIDTH = 1.0_vp;
constexpr float SPRING_MOTION_RESPONSE = 0.314f;
constexpr float SPRING_MOTION_DAMPING_FRACTION = 0.95f;
} // namespace
SliderContentModifier::SliderContentModifier(const Parameters& parameters)
    : boardColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT)))
{
    // animatable property
    selectStart_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(parameters.selectStart - PointF());
    selectEnd_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(parameters.selectEnd - PointF());
    backStart_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(parameters.backStart - PointF());
    backEnd_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(parameters.backEnd - PointF());
    circleCenter_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(parameters.circleCenter - PointF());
    trackThickness_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(parameters.trackThickness);
    trackBackgroundColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(parameters.trackBackgroundColor));
    selectColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(parameters.selectColor));
    blockColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(parameters.blockColor));
    // non-animatable property
    blockDiameter_ = AceType::MakeRefPtr<PropertyFloat>(parameters.blockDiameter);
    stepRatio_ = AceType::MakeRefPtr<PropertyFloat>(parameters.stepRatio);
    isShowStep_ = AceType::MakeRefPtr<PropertyBool>(false);
    // others
    UpdateData(parameters);
    UpdateThemeColor();

    AttachProperty(selectStart_);
    AttachProperty(selectEnd_);
    AttachProperty(backStart_);
    AttachProperty(backEnd_);
    AttachProperty(circleCenter_);
    AttachProperty(trackThickness_);
    AttachProperty(trackBackgroundColor_);
    AttachProperty(selectColor_);
    AttachProperty(blockColor_);
    AttachProperty(boardColor_);
    AttachProperty(blockDiameter_);
    AttachProperty(stepRatio_);
    AttachProperty(isShowStep_);
}

void SliderContentModifier::onDraw(DrawingContext& context)
{
    DrawBackground(context);
    DrawStep(context);
    DrawSelect(context);
    DrawDefaultBlock(context);
    DrawShadow(context);
    DrawHoverOrPress(context);
}

void SliderContentModifier::DrawBackground(DrawingContext& context)
{
    auto& canvas = context.canvas;
    RSPen backgroundPen;
    backgroundPen.SetAntiAlias(true);
    backgroundPen.SetWidth(trackThickness_->Get());
    backgroundPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    backgroundPen.SetColor(ToRSColor(trackBackgroundColor_->Get()));
    canvas.AttachPen(backgroundPen);
    canvas.DrawLine(RSPoint(backStart_->Get().GetX(), backStart_->Get().GetY()),
        RSPoint(backEnd_->Get().GetX(), backEnd_->Get().GetY()));
    canvas.DetachPen();
}

void SliderContentModifier::DrawStep(DrawingContext& context)
{
    if (!isShowStep_->Get()) {
        return;
    }
    auto& canvas = context.canvas;
    auto stepSize = stepSize_;
    auto stepColor = stepColor_;
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
    auto centerWidth = directionAxis_ == Axis::HORIZONTAL ? context.height : context.width;
    centerWidth *= HALF;
    if (directionAxis_ == Axis::HORIZONTAL) {
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
        RSPen selectPen;
        selectPen.SetAntiAlias(true);
        selectPen.SetWidth(trackThickness_->Get());
        selectPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
        selectPen.SetColor(ToRSColor(selectColor_->Get()));
        canvas.AttachPen(selectPen);
        canvas.DrawLine(RSPoint(selectStart_->Get().GetX(), selectStart_->Get().GetY()),
            RSPoint(selectEnd_->Get().GetX(), selectEnd_->Get().GetY()));
    }
}

void SliderContentModifier::DrawDefaultBlock(DrawingContext& context)
{
    auto& canvas = context.canvas;
    RSPen circlePen;
    circlePen.SetAntiAlias(true);
    circlePen.SetColor(ToRSColor(blockColor_->Get()));
    circlePen.SetWidth(blockDiameter_->Get() * HALF);
    canvas.AttachPen(circlePen);
    auto penRadius = blockDiameter_->Get() * HALF * HALF;
    canvas.DrawCircle(RSPoint(circleCenter_->Get().GetX(), circleCenter_->Get().GetY()), penRadius);
    canvas.DetachPen();
}

void SliderContentModifier::DrawHoverOrPress(DrawingContext& context)
{
    auto& canvas = context.canvas;
    RSPen circleStatePen;
    circleStatePen.SetAntiAlias(true);
    // add animate color
    circleStatePen.SetColor(ToRSColor(boardColor_->Get()));
    circleStatePen.SetWidth(hotCircleShadowWidth_);
    canvas.AttachPen(circleStatePen);
    auto penRadius = (blockDiameter_->Get() + hotCircleShadowWidth_) * HALF;
    canvas.DrawCircle(RSPoint(circleCenter_->Get().GetX(), circleCenter_->Get().GetY()), penRadius);
    canvas.DetachPen();
}

void SliderContentModifier::DrawShadow(DrawingContext& context)
{
    auto& canvas = context.canvas;
    if (!mouseHoverFlag_ && !mousePressedFlag_) {
        RSPen circleShadowPen;
        circleShadowPen.SetAntiAlias(true);
        circleShadowPen.SetColor(ToRSColor(blockOuterEdgeColor_));
        circleShadowPen.SetWidth(static_cast<float>(CIRCLE_SHADOW_WIDTH.ConvertToPx()));
        canvas.AttachPen(circleShadowPen);
        auto penRadius = (blockDiameter_->Get() + static_cast<float>(CIRCLE_SHADOW_WIDTH.ConvertToPx())) * HALF;
        canvas.DrawCircle(
            RSPoint(circleCenter_->Get().GetX(), circleCenter_->Get().GetY()), penRadius);
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
    if (needAnimate_) {
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
    CHECK_NULL_VOID(circleCenter_);
    if (needAnimate_) {
        AnimationOption option = AnimationOption();
        auto motion =
            AceType::MakeRefPtr<ResponsiveSpringMotion>(SPRING_MOTION_RESPONSE, SPRING_MOTION_DAMPING_FRACTION);
        option.SetCurve(motion);
        AnimationUtils::Animate(option, [&]() { circleCenter_->Set(center - PointF()); });
    } else {
        circleCenter_->Set(center - PointF());
    }
}
} // namespace OHOS::Ace::NG
