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
const bool DEFAULT_ENABLE_BREATHE = true;
constexpr float INITIAL_OPACITY = 0.0f;
constexpr int32_t PICTURE_DURATION = 750;
} // namespace

MoonProgressModifier::MoonProgressModifier(const WeakPtr<FrameNode>& maskNode)
    : maskColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT))),
      ratio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(INITIAL_RATIO)),
      value_(AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f)),
      opacity_(AceType::MakeRefPtr<AnimatablePropertyFloat>(INITIAL_OPACITY)),
      maxValue_(AceType::MakeRefPtr<PropertyFloat>(DEFAULT_MAXVALUE)),
      enableBreathe_(AceType::MakeRefPtr<PropertyBool>(DEFAULT_ENABLE_BREATHE))
{
    maskNode_ = maskNode;
    AttachProperty(maskColor_);
    AttachProperty(ratio_);
    AttachProperty(value_);
    AttachProperty(opacity_);
    AttachProperty(maxValue_);
    AttachProperty(enableBreathe_);
}

void MoonProgressModifier::onDraw(DrawingContext& context)
{
    auto node = maskNode_.Upgrade();
    CHECK_NULL_VOID(node);
    auto geometryNode = node->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto contentSize = geometryNode->GetFrameSize();
    frameSize_.SetWidth(contentSize.Width());
    frameSize_.SetHeight(contentSize.Height());
    SetBigRadius();
    if (GreatOrEqual(ratio_->Get(), bigRadius_ / smallRadius_)) {
        hideMask_ = true;
        return;
    }
    PaintSquareMoon(context.canvas);
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
        auto modifier = weak.Upgrade();
        CHECK_NULL_VOID(modifier);
        double angle = (modifier->value_->Get() / modifier->maxValue_->Get()) * 1;
        if (GreatNotEqual(std::abs(angle - FLOAT_ONE_ZERO), EPSLION)) {
            modifier->StopPictureAnimate();
            return;
        }
        if (modifier->enableBreathe_->Get() && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            modifier->StartPictureAnimate();
        } else {
            modifier->StopPictureAnimate();
            modifier->SetMoonAnimate(bigRadius / smallRadius);
        }
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

void MoonProgressModifier::SetEnableBreathe(bool enableBreathe)
{
    enableBreathe_->Set(enableBreathe);
}

void MoonProgressModifier::InitRatio()
{
    ratio_->Set(INITIAL_RATIO);
    animationEnd_ = false;
    hideMask_ = false;
    RemoveVisibleChange();
}

void MoonProgressModifier::SetMoonAnimate(float value)
{
    if (ratio_) {
        animationEnd_ = true;
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

void MoonProgressModifier::StartPictureAnimate() const
{
    if (GreatOrEqual(value_->Get(), maxValue_->Get()) && !animationEnd_) {
        AnimationOption option;
        option.SetDuration(PICTURE_DURATION);
        option.SetDelay(0);
        option.SetCurve(Curves::SHARP);
        option.SetIteration(-1);
        option.SetAnimationDirection(AnimationDirection::ALTERNATE);
        AnimationUtils::Animate(option, [weak = AceType::WeakClaim(AceType::RawPtr(opacity_))]() {
            auto opacity = weak.Upgrade();
            CHECK_NULL_VOID(opacity);
            opacity->Set(1.0f);
        });
    }
}

void MoonProgressModifier::StopPictureAnimate() const
{
    AnimationOption option;
    option.SetDuration(0);
    AnimationUtils::Animate(option, [&]() { opacity_->Set(0.0f); });
}

void MoonProgressModifier::SetBigRadius()
{
    bigRadius_ = std::sqrt(
        std::pow(frameSize_.Width() / INT32_TWO, INT32_TWO) + std::pow(frameSize_.Height() / INT32_TWO, INT32_TWO));
    double radius = (std::min(frameSize_.Width() / INT32_TWO, frameSize_.Height() / INT32_TWO));
    smallRadius_ = radius * INITIAL_RATIO * FLOAT_ZERO_SEVEN;
}
void MoonProgressModifier::CalculateSquareMoonPath(RSPath& path, const PointF& centerPt, const double& angle)
{
    path.AddArc({ centerPt.GetX() - smallRadius_, centerPt.GetY() - smallRadius_, centerPt.GetX() + smallRadius_,
                    centerPt.GetY() + smallRadius_ },
        ANGLE_90, ANGLE_180);
    if (LessOrEqual(angle, FLOAT_ZERO_FIVE)) {
        double progressOffset = smallRadius_ - smallRadius_ * angle / FLOAT_ZERO_FIVE;
        path.MoveTo(centerPt.GetX(), centerPt.GetY() - smallRadius_);
        // startAngle:270  sweepAngle:-180
        path.AddArc({ centerPt.GetX() - progressOffset, centerPt.GetY() - smallRadius_,
                        centerPt.GetX() + progressOffset, centerPt.GetY() + smallRadius_ },
            ANGLE_270, -ANGLE_180);
    } else {
        double progressOffset = smallRadius_ * (angle - FLOAT_ZERO_FIVE) / FLOAT_ZERO_FIVE;
        path.MoveTo(centerPt.GetX(), centerPt.GetY() - smallRadius_);
        // startAngle:270  sweepAngle:180
        path.AddArc({ centerPt.GetX() - progressOffset, centerPt.GetY() - smallRadius_,
                        centerPt.GetX() + progressOffset, centerPt.GetY() + smallRadius_ },
            ANGLE_270, ANGLE_180);
    }
}
void MoonProgressModifier::PaintSquareMoon(RSCanvas& canvas)
{
    PointF centerPt = PointF(frameSize_.Width() / INT32_TWO, frameSize_.Height() / INT32_TWO);
    RSBrush brush;
    double angle = value_->Get() / maxValue_->Get();
#ifndef USE_ROSEN_DRAWING
    RSPath path;
    RSPath clipPath;
#else
    RSRecordingPath path;
    RSRecordingPath clipPath;
#endif
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor((maskColor_->Get())));
    canvas.AttachBrush(brush);
    path.SetFillStyle(RSPathFillType::EVENTODD);
    path.AddCircle(centerPt.GetX(), centerPt.GetY(), bigRadius_, RSPathDirection::CW_DIRECTION);
    if (NearZero(std::abs(ratio_->Get() - INITIAL_RATIO), EPSLION)) {
        if (NearZero(angle, EPSLION)) {
            canvas.DrawPath(path);
            canvas.DetachBrush();
            canvas.Restore();
            return;
        }
        if (LessOrEqual(angle, FLOAT_ONE_ZERO)) {
            CalculateSquareMoonPath(path, centerPt, angle);
        } else {
            clipPath.AddCircle(centerPt.GetX(), centerPt.GetY(), smallRadius_, RSPathDirection::CW_DIRECTION);
            canvas.ClipPath(clipPath, RSClipOp::DIFFERENCE, true);
        }
        canvas.DrawPath(path);
    } else {
        path.MoveTo(centerPt.GetX(), centerPt.GetY() - smallRadius_ * ratio_->Get());
        path.AddCircle(centerPt.GetX(), centerPt.GetY(), smallRadius_ * ratio_->Get(), RSPathDirection::CW_DIRECTION);
        canvas.DrawPath(path);
    }
    canvas.DetachBrush();
    canvas.Restore();
    if (GreatOrEqual(angle, 1.0f)) {
        PaintSquareMoonShadow(canvas, brush);
    }
}

void MoonProgressModifier::PaintSquareMoonShadow(RSCanvas& canvas, RSBrush& brush)
{
    RegisterVisibleChange();
    Color color = Color::WHITE.ChangeOpacity(opacity_->Get());
    brush.SetColor(ToRSColor(color));
    auto radius = (std::min(frameSize_.Width() / INT32_TWO, frameSize_.Height() / INT32_TWO));
    RSFilter filter;
#ifndef USE_ROSEN_DRAWING
    RSPath path;
    filter.SetImageFilter(
        RSImageFilter::CreateBlurImageFilter(radius - smallRadius_, radius - smallRadius_, RSTileMode::DECAL, nullptr));
#else
    RSRecordingPath path;
    filter.SetImageFilter(RSRecordingImageFilter::CreateBlurImageFilter(
        radius - smallRadius_, radius - smallRadius_, RSTileMode::DECAL, nullptr));
#endif
    brush.SetFilter(filter);
    canvas.AttachBrush(brush);
    PointF centerPt = PointF(frameSize_.Width() / INT32_TWO, frameSize_.Height() / INT32_TWO);
    path.AddCircle(centerPt.GetX(), centerPt.GetY(), smallRadius_, RSPathDirection::CW_DIRECTION);
    canvas.ClipPath(path, RSClipOp::DIFFERENCE, true);
    canvas.DrawPath(path);
    canvas.DetachBrush();
    canvas.Restore();
}

void MoonProgressModifier::RegisterVisibleChange()
{
    if (hasVisibleChangeRegister_) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto modifier = weak.Upgrade();
        CHECK_NULL_VOID(modifier);
        if (visible) {
            modifier->StartPictureAnimate();
        } else {
            modifier->StopPictureAnimate();
        }
    };
    std::vector<double> ratioList = { 0.0 };
    auto node = maskNode_.Upgrade();
    CHECK_NULL_VOID(node);
    pipeline->AddVisibleAreaChangeNode(node, ratioList, callback, false);
    pipeline->AddWindowStateChangedCallback(node->GetId());
    hasVisibleChangeRegister_ = true;
}

void MoonProgressModifier::RemoveVisibleChange()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto node = maskNode_.Upgrade();
    CHECK_NULL_VOID(node);
    pipeline->RemoveVisibleAreaChangeNode(node->GetId());
    pipeline->RemoveWindowStateChangedCallback(node->GetId());
    hasVisibleChangeRegister_ = false;
}
} // namespace OHOS::Ace::NG
