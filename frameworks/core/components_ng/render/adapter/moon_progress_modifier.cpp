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

#include "core/components_ng/render/adapter/moon_progress_modifier.h"

#include <cmath>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DIFFUSE_DURATION = 300;
constexpr float INITIAL_RATIO = 1.0f;
constexpr int32_t INT32_TWO = 2;
constexpr int32_t ANGLE_90 = 90;
constexpr int32_t ANGLE_180 = 180;
constexpr int32_t ANGLE_270 = 270;
constexpr float FLOAT_ZERO_FIVE = 0.5f;
constexpr float FLOAT_ZERO_SEVEN = 0.7f;
constexpr float FLOAT_ONE_ZERO = 1.0f;
constexpr float SPRING_MOTION_RESPONSE = 0.314f;
constexpr float SPRING_MOTION_DAMPING_FRACTION = 0.95f;
const float EPSLION = 1e-5;
const float DEFAULT_MAXVALUE = 100.0f;
} // namespace

MoonProgressModifier::MoonProgressModifier()
    : maskColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT))),
      ratio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(INITIAL_RATIO)),
      value_(AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f)),
      maxValue_(AceType::MakeRefPtr<PropertyFloat>(DEFAULT_MAXVALUE))
{
    AttachProperty(maskColor_);
    AttachProperty(ratio_);
    AttachProperty(value_);
    AttachProperty(maxValue_);
}

void MoonProgressModifier::onDraw(DrawingContext& context)
{
    SizeF frameSize(context.width, context.height);
    SetBigRadius(frameSize);
    PaintSquareMoon(context.canvas, frameSize);
}

void MoonProgressModifier::SetMaskColor(LinearColor color)
{
    maskColor_->Set(color);
}

void MoonProgressModifier::SetValue(float value)
{
    auto finishCallback = [weak = AceType::WeakClaim(this), bigRadius = bigRadius_, smallRadius = smallRadius_,
                              id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto task = [weak, bigRadius, smallRadius]() {
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            double angle = (modifier->value_->Get() / modifier->maxValue_->Get()) * 1;
            if (NearEqual(std::abs(angle - FLOAT_ONE_ZERO), EPSLION)) {
                modifier->SetMoonAnimate(bigRadius / smallRadius);
            }
        };
        pipeline->PostSyncEvent(task);
        pipeline->RequestFrame();
    };

    AnimationOption option;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(SPRING_MOTION_RESPONSE, SPRING_MOTION_DAMPING_FRACTION);
    option.SetCurve(motion);
    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(AceType::RawPtr(value_)), valueTo = value]() {
            auto value = weak.Upgrade();
            CHECK_NULL_VOID(value);
            value->Set(valueTo);
        },
        finishCallback);

    CHECK_NULL_VOID(maxValue_);
    if (value < maxValue_->Get() && std::abs(maxValue_->Get() - value) > EPSLION &&
        std::abs(ratio_->Get() - INITIAL_RATIO) > EPSLION) {
        InitRatio();
    }
}

void MoonProgressModifier::SetMaxValue(float value)
{
    maxValue_->Set(value);
}

float MoonProgressModifier::GetMaxValue()
{
    if (maxValue_) {
        return maxValue_->Get();
    } else {
        return DEFAULT_MAXVALUE;
    }
}

void MoonProgressModifier::InitRatio()
{
    ratio_->Set(INITIAL_RATIO);
}

void MoonProgressModifier::SetMoonAnimate(float value) const
{
    if (ratio_) {
        AnimationOption option;
        option.SetDuration(DIFFUSE_DURATION);
        option.SetDelay(0);
        option.SetCurve(Curves::SHARP);
        AnimationUtils::Animate(option, [weak = AceType::WeakClaim(AceType::RawPtr(ratio_)), value]() {
            auto ratio = weak.Upgrade();
            CHECK_NULL_VOID(ratio);
            ratio->Set(value);
        });
    }
}

void MoonProgressModifier::SetBigRadius(const SizeF& frameSize)
{
    bigRadius_ = std::sqrt(std::pow(frameSize.Width() / INT32_TWO, 2) + std::pow(frameSize.Height() / INT32_TWO, 2));
    double radius = (std::min(frameSize.Width() / INT32_TWO, frameSize.Height() / INT32_TWO));
    smallRadius_ = radius * INITIAL_RATIO * FLOAT_ZERO_SEVEN;
}

void MoonProgressModifier::PaintSquareMoon(RSCanvas& canvas, const SizeF& frameSize) const
{
    static int32_t totalDegree = 1;
    PointF centerPt = PointF(frameSize.Width() / INT32_TWO, frameSize.Height() / INT32_TWO);
    RSBrush brush;
    double angle = (value_->Get() / maxValue_->Get()) * totalDegree;
    RSPath path;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor((maskColor_->Get())));
    canvas.AttachBrush(brush);
#ifndef USE_ROSEN_DRAWING
    path.SetFillStyle(RSPathFillType::EVENTODD);
#else
    path.SetFillStyle(RSPathFillType::EVEN_ODD);
#endif
    path.AddCircle(centerPt.GetX(), centerPt.GetY(), bigRadius_, RSPathDirection::CW_DIRECTION);
    if (NearZero(std::abs(ratio_->Get() - INITIAL_RATIO), EPSLION)) {
        path.AddArc(
            { centerPt.GetX() - smallRadius_, centerPt.GetY() - smallRadius_,
            centerPt.GetX() + smallRadius_, centerPt.GetY() + smallRadius_ }, ANGLE_90, ANGLE_180);
        if (angle <= FLOAT_ZERO_FIVE) {
            double progressOffset = smallRadius_ - smallRadius_ * angle / FLOAT_ZERO_FIVE;
            path.MoveTo(centerPt.GetX(), centerPt.GetY() - smallRadius_);
            // startAngle:270  sweepAngle:-180
            path.AddArc(
                { centerPt.GetX() - progressOffset, centerPt.GetY() - smallRadius_,
                centerPt.GetX() + progressOffset, centerPt.GetY() + smallRadius_ }, ANGLE_270, -ANGLE_180);
            canvas.DrawPath(path);
        } else {
            double progressOffset = smallRadius_ * (angle - FLOAT_ZERO_FIVE) / FLOAT_ZERO_FIVE;
            path.MoveTo(centerPt.GetX(), centerPt.GetY() - smallRadius_);
            // startAngle:270  sweepAngle:180
            path.AddArc(
                { centerPt.GetX() - progressOffset, centerPt.GetY() - smallRadius_,
                centerPt.GetX() + progressOffset, centerPt.GetY() + smallRadius_ }, ANGLE_270, ANGLE_180);
            canvas.DrawPath(path);
        }
    } else {
        path.MoveTo(centerPt.GetX(), centerPt.GetY() -  smallRadius_ * ratio_->Get());
        path.AddCircle(centerPt.GetX(), centerPt.GetY(), smallRadius_ * ratio_->Get(),
            RSPathDirection::CW_DIRECTION);
        canvas.DrawPath(path);
    }
}
} // namespace OHOS::Ace::NG
