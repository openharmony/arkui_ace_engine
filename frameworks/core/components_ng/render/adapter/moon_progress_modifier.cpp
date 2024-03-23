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
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/image/image_source_info.h"
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
constexpr int32_t PICTURE_DURATION = 1500;
} // namespace

MoonProgressModifier::MoonProgressModifier()
    : maskColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT))),
      ratio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(INITIAL_RATIO)),
      value_(AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f)),
      opacity_(AceType::MakeRefPtr<AnimatablePropertyFloat>(INITIAL_OPACITY)),
      maxValue_(AceType::MakeRefPtr<PropertyFloat>(DEFAULT_MAXVALUE)),
      enableBreathe_(AceType::MakeRefPtr<PropertyBool>(DEFAULT_ENABLE_BREATHE))
{
    AttachProperty(maskColor_);
    AttachProperty(ratio_);
    AttachProperty(value_);
    AttachProperty(opacity_);
    AttachProperty(maxValue_);
    AttachProperty(enableBreathe_);
}

void MoonProgressModifier::onDraw(DrawingContext& context)
{
    frameSize_.SetWidth(context.width);
    frameSize_.SetHeight(context.height);
    if (!canvasImage_ && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        InitImage();
    }
    SetBigRadius();
    PaintSquareMoon(context.canvas);
}

void MoonProgressModifier::SetMaskColor(LinearColor color)
{
    maskColor_->Set(color);
}

void MoonProgressModifier::SetValue(float value)
{
    auto finishCallback = [weak = AceType::WeakClaim(this), bigRadius = bigRadius_, smallRadius = smallRadius_,
                              animationEnd = animationEnd_, id = Container::CurrentId()]() {
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
        if (modifier->enableBreathe_->Get() && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE) &&
            !animationEnd) {
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
    AnimationOption option;
    option.SetDuration(PICTURE_DURATION);
    option.SetDelay(0);
    option.SetCurve(Curves::SHARP);
    option.SetIteration(-1);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(AceType::RawPtr(opacity_))]() {
        auto opacity = weak.Upgrade();
        CHECK_NULL_VOID(opacity);
        opacity->Set(2.0f);
    });
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

void MoonProgressModifier::PaintSquareMoon(RSCanvas& canvas) const
{
    static int32_t totalDegree = 1;
    PointF centerPt = PointF(frameSize_.Width() / INT32_TWO, frameSize_.Height() / INT32_TWO);
    RSBrush brush;
    double angle = (value_->Get() / maxValue_->Get()) * totalDegree;
#ifndef USE_ROSEN_DRAWING
    RSPath path;
#else
    RSRecordingPath path;
#endif
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor((maskColor_->Get())));
    canvas.AttachBrush(brush);
    path.SetFillStyle(RSPathFillType::EVENTODD);
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
    canvas.DetachBrush();
    if (GreatOrEqual(angle, 1.0f)) {
        canvas.Restore();
        PaintSquareMoonShadow(canvas, brush);
    }
}

void MoonProgressModifier::PaintSquareMoonShadow(RSCanvas& canvas, RSBrush& brush) const
{
    CHECK_NULL_VOID(canvasImage_);

    float opacity = 0.0f;
    if (GreatNotEqual(opacity_->Get(), 1.0f)) {
        opacity = 2.0f - opacity_->Get();
    } else {
        opacity = opacity_->Get();
    }
    brush.SetAlphaF(opacity);
    canvas.AttachBrush(brush);

    auto config = canvasImage_->GetPaintConfig();
    auto shortLength = (std::min(frameSize_.Width(), frameSize_.Height()));
    auto longLength = (std::max(frameSize_.Width(), frameSize_.Height()));
    if (NonPositive(longLength)) {
        return;
    }
    auto scale = shortLength / longLength;
    config.scaleX_ = scale;
    config.scaleY_ = scale;
    canvasImage_->SetPaintConfig(config);
    OffsetF offset = OffsetF((longLength - shortLength) * FLOAT_ZERO_FIVE * (frameSize_.Width() / longLength),
        (longLength - shortLength) * FLOAT_ZERO_FIVE * (frameSize_.Height() / longLength));
    canvas.Save();
    canvas.Translate(offset.GetX(), offset.GetY());
    canvasImage_->DrawToRSCanvasWithBrush(canvas, brush, ToRSRect(config.srcRect_), ToRSRect(config.dstRect_));
    canvas.Restore();
}

void MoonProgressModifier::InitImage()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto iconPath =
        pipeline->GetTheme<IconTheme>()->GetIconPath(InternalResource::ResourceId::MOON_PROGRESS_FG_CIRCLE_SHADOW);
    ImageSourceInfo sourceInfo;
    sourceInfo.SetSrc(iconPath);
    auto dataReadyCallback = [moonProgressModifier = this](const ImageSourceInfo& sourceInfo) {
        CHECK_NULL_VOID(moonProgressModifier);
        moonProgressModifier->OnImageDataReady();
    };
    auto loadSuccessCallback = [moonProgressModifier = this](const ImageSourceInfo& sourceInfo) {
        CHECK_NULL_VOID(moonProgressModifier);
        moonProgressModifier->OnImageLoadSuccess();
    };
    auto loadFailCallback = [moonProgressModifier = this](
                                const ImageSourceInfo& sourceInfo, const std::string& errorMsg) {
        CHECK_NULL_VOID(moonProgressModifier);
        moonProgressModifier->OnImageLoadFail(errorMsg);
    };
    LoadNotifier loadNotifier(dataReadyCallback, loadSuccessCallback, loadFailCallback);
    loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier), true);
    loadingCtx_->LoadImageData();
}

void MoonProgressModifier::OnImageDataReady()
{
    CHECK_NULL_VOID(loadingCtx_);
    loadingCtx_->MakeCanvasImageIfNeed(loadingCtx_->GetImageSize(), true, ImageFit::NONE);
}

void MoonProgressModifier::OnImageLoadSuccess()
{
    CHECK_NULL_VOID(loadingCtx_);
    ImagePaintConfig config;
    config.srcRect_ = loadingCtx_->GetSrcRect();
    config.dstRect_ = loadingCtx_->GetDstRect();
    canvasImage_ = DynamicCast<PixelMapImage>(loadingCtx_->MoveCanvasImage());
    canvasImage_->SetPaintConfig(config);
}

void MoonProgressModifier::OnImageLoadFail(const std::string& errorMsg)
{
    canvasImage_ = nullptr;
}
} // namespace OHOS::Ace::NG
