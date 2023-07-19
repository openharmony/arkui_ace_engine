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

#include "core/components_ng/render/animation_utils.h"

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
const float EPSLION = 1e-5;
const float DEFAULT_MAXVALUE = 100.0f;
} // namespace

void MoonProgressModifier::Draw(RSDrawingContext& context) const
{
    CHECK_NULL_VOID(maskColor_);
    CHECK_NULL_VOID(value_);
    CHECK_NULL_VOID(maxValue_);
    CHECK_NULL_VOID(ratio_);
#ifndef USE_ROSEN_DRAWING
    std::shared_ptr<SkCanvas> skCanvas { context.canvas, [](SkCanvas* /* unused */) {} };
    RSCanvas rsCanvas(&skCanvas);
    CHECK_NULL_VOID(&rsCanvas);
    SizeF contentSize(context.width, context.height);

    PaintSquareMoon(rsCanvas, contentSize);
#else
    CHECK_NULL_VOID(context.canvas);
    SizeF contentSize(context.width, context.height);

    PaintSquareMoon(*context.canvas, contentSize);
#endif
}

void MoonProgressModifier::SetMaskColor(LinearColor color)
{
    if (maskColor_ == nullptr) {
        maskColor_ = std::make_shared<Rosen::RSAnimatableProperty<LinearColor>>(color);
        AttachProperty(maskColor_);
    } else {
        maskColor_->Set(color);
    }
}

void MoonProgressModifier::SetValue(float value)
{
    if (value_ == nullptr) {
        value_ = std::make_shared<Rosen::RSProperty<float>>(value);
        AttachProperty(value_);
    } else {
        value_->Set(value);
    }
    CHECK_NULL_VOID(maxValue_);
    if (value_->Get() < maxValue_->Get() &&
        std::abs(maxValue_->Get() - value_->Get()) > EPSLION &&
        std::abs(ratio_->Get() - INITIAL_RATIO) > EPSLION) {
        if (ratio_) {
            ratio_->Set(INITIAL_RATIO);
        }
    }
}

void MoonProgressModifier::SetMaxValue(float value)
{
    if (maxValue_ == nullptr) {
        maxValue_ = std::make_shared<Rosen::RSProperty<float>>(value);
        AttachProperty(maxValue_);
    } else {
        maxValue_->Set(value);
    }
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
    if (ratio_ == nullptr) {
        ratio_ = std::make_shared<Rosen::RSAnimatableProperty<float>>(INITIAL_RATIO);
        AttachProperty(ratio_);
        ratio_->Set(INITIAL_RATIO);
    }
}

void MoonProgressModifier::SetMoonAnimate(float value) const
{
    if (ratio_) {
        AnimationOption option = AnimationOption();
        option.SetDuration(DIFFUSE_DURATION);
        option.SetDelay(0);
        option.SetCurve(Curves::SHARP);
        AnimationUtils::Animate(option, [&]() { ratio_->Set(value); });
    }
}

void MoonProgressModifier::PaintSquareMoon(RSCanvas& canvas, const SizeF& frameSize) const
{
    static int32_t totalDegree = 1;
    PointF centerPt = PointF(frameSize.Width() / INT32_TWO, frameSize.Height() / INT32_TWO);
    double radius = (std::min(frameSize.Width() / INT32_TWO, frameSize.Height() / INT32_TWO));
    double smallRadius = radius * INITIAL_RATIO * FLOAT_ZERO_SEVEN;
    double bigRadius = std::sqrt(std::pow(frameSize.Width() / INT32_TWO, 2) +
        std::pow(frameSize.Height() / INT32_TWO, 2));
    RSBrush brush;
    double angle = (value_->Get() / maxValue_->Get()) * totalDegree;
    RSPath path;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor((maskColor_->Get())));
    canvas.AttachBrush(brush);
#ifndef USE_ROSEN_DRAWING
    path.SetFillStyle(RSPathFillType::EVENTODD);
#else
    path.SetFillStyle(RSPathFillType::EVENTODD);
#endif
    path.AddCircle(centerPt.GetX(), centerPt.GetY(), bigRadius, RSPathDirection::CW_DIRECTION);
    if (angle < FLOAT_ONE_ZERO) {
        path.AddArc(
            { centerPt.GetX() - smallRadius, centerPt.GetY() - smallRadius,
            centerPt.GetX() + smallRadius, centerPt.GetY() + smallRadius }, ANGLE_90, ANGLE_180);
        if (angle <= FLOAT_ZERO_FIVE) {
            double progressOffset = smallRadius - smallRadius * angle / FLOAT_ZERO_FIVE;
            path.MoveTo(centerPt.GetX(), centerPt.GetY() - smallRadius);
            // startAngle:270  sweepAngle:-180
            path.AddArc(
                { centerPt.GetX() - progressOffset, centerPt.GetY() - smallRadius,
                centerPt.GetX() + progressOffset, centerPt.GetY() + smallRadius }, ANGLE_270, -ANGLE_180);
            canvas.DrawPath(path);
        } else {
            double progressOffset = smallRadius * (angle - FLOAT_ZERO_FIVE) / FLOAT_ZERO_FIVE;
            path.MoveTo(centerPt.GetX(), centerPt.GetY() - smallRadius);
            // startAngle:270  sweepAngle:180
            path.AddArc(
                { centerPt.GetX() - progressOffset, centerPt.GetY() - smallRadius,
                centerPt.GetX() + progressOffset, centerPt.GetY() + smallRadius }, ANGLE_270, ANGLE_180);
            canvas.DrawPath(path);
        }
    } else {
        if (std::abs(ratio_->Get() - INITIAL_RATIO) < EPSLION) {
            SetMoonAnimate(bigRadius/smallRadius);
        }
        path.MoveTo(centerPt.GetX(), centerPt.GetY() -  smallRadius * ratio_->Get());
        path.AddCircle(centerPt.GetX(), centerPt.GetY(), smallRadius * ratio_->Get(),
            RSPathDirection::CW_DIRECTION);
        canvas.DrawPath(path);
    }
}
} // namespace OHOS::Ace::NG