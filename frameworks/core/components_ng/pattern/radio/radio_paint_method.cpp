/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/radio/radio_modifier.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint8_t ENABLED_ALPHA = 255;
constexpr uint8_t DISABLED_ALPHA = 102;
constexpr float CALC_RADIUS = 2.0f;
constexpr float DEFAULT_POINT_SCALE = 0.5f;
constexpr float DEFAULT_TOTAL_SCALE = 1.0f;
constexpr float DEFAULT_SHRINK_SCALE = 0.9f;
constexpr float DEFAULT_SHRINK_SCALE_VER_TWELVE = 0.95f;
constexpr int32_t DEFAULT_RADIO_ANIMATION_DURATION = 300;
constexpr float DEFAULT_OPACITY_SCALE = 1.0f;
constexpr float DEFAULT_OPACITY_BORDER_SCALE = 0.0f;
constexpr float DEFAULT_INTERPOLATINGSPRING_VELOCITY = 0.0f;
constexpr float DEFAULT_INTERPOLATINGSPRING_MASS = 1.0f;
constexpr float DEFAULT_INTERPOLATINGSPRING_STIFFNESS = 728.0f;
constexpr float DEFAULT_INTERPOLATINGSPRING_DAMPING = 46.0f;
constexpr int32_t DEFAULT_INDICATOR_ANIMATION_DURATION = 150;
} // namespace

RadioModifier::RadioModifier()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    pointColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(radioTheme->GetPointColor()));
    AttachProperty(pointColor_);

    activeColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(radioTheme->GetActiveColor()));
    AttachProperty(activeColor_);

    inactiveColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(radioTheme->GetInactiveColor()));
    AttachProperty(inactiveColor_);
    isOnAnimationFlag_ = AceType::MakeRefPtr<PropertyBool>(false);
    enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    isCheck_ = AceType::MakeRefPtr<PropertyBool>(false);
    isFocused_ = AceType::MakeRefPtr<PropertyBool>(false);
    uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
    offset_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
    size_ = AceType::MakeRefPtr<AnimatablePropertySizeF>(SizeF());
    totalScale_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(DEFAULT_TOTAL_SCALE);
    opacityScale_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(DEFAULT_OPACITY_SCALE);
    borderOpacityScale_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(DEFAULT_OPACITY_BORDER_SCALE);
    pointScale_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(DEFAULT_POINT_SCALE);
    ringPointScale_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0f);
    animateTouchHoverColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    useContentModifier_ = AceType::MakeRefPtr<PropertyBool>(false);

    AttachProperty(enabled_);
    AttachProperty(isCheck_);
    AttachProperty(isFocused_);
    AttachProperty(uiStatus_);
    AttachProperty(offset_);
    AttachProperty(size_);
    AttachProperty(totalScale_);
    AttachProperty(opacityScale_);
    AttachProperty(borderOpacityScale_);
    AttachProperty(pointScale_);
    AttachProperty(ringPointScale_);
    AttachProperty(animateTouchHoverColor_);

    InitializeParam();
}

void RadioModifier::InitializeParam()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    shadowWidth_ = radioTheme->GetShadowWidth().ConvertToPx();
    borderWidth_ = radioTheme->GetBorderWidth().ConvertToPx();
    inactivePointColor_ = radioTheme->GetInactivePointColor();
    shadowColor_ = radioTheme->GetShadowColor();
    clickEffectColor_ = radioTheme->GetClickEffectColor();
    hoverColor_ = radioTheme->GetHoverColor();
    hotZoneHorizontalPadding_ = radioTheme->GetHotZoneHorizontalPadding();
    hoverDuration_ = radioTheme->GetHoverDuration();
    hoverToTouchDuration_ = radioTheme->GetHoverToTouchDuration();
    touchDuration_ = radioTheme->GetTouchDuration();
    focusedBgUnchecked_ = radioTheme->GetFocusedBgUnchecked();
    focusedRingUnchecked_ = radioTheme->GetFocusedRingUnchecked();
    focusedBgColor_ = radioTheme->GetFocusedBgColor();
    sizeFocused_ = radioTheme->GetSizeFocusBg();
    sizeHover_ = radioTheme->GetSizeHoverBg();
}

void RadioModifier::UpdateAnimatableProperty()
{
    switch (touchHoverType_) {
        case TouchHoverAnimationType::HOVER:
            SetBoardColor(LinearColor(hoverColor_), hoverDuration_, Curves::FRICTION);
            break;
        case TouchHoverAnimationType::PRESS_TO_HOVER:
            SetBoardColor(LinearColor(hoverColor_), hoverToTouchDuration_, Curves::SHARP);
            break;
        case TouchHoverAnimationType::NONE:
            SetBoardColor(LinearColor(hoverColor_.BlendOpacity(0)), hoverDuration_, Curves::FRICTION);
            break;
        case TouchHoverAnimationType::HOVER_TO_PRESS:
            SetBoardColor(LinearColor(clickEffectColor_), hoverToTouchDuration_, Curves::SHARP);
            break;
        case TouchHoverAnimationType::PRESS:
            SetBoardColor(LinearColor(clickEffectColor_), hoverDuration_, Curves::FRICTION);
            break;
        default:
            break;
    }
}
void RadioModifier::UpdateTotalScaleOnAnimatable(
    bool isCheck, const AnimationOption& delayOption, const AnimationOption& halfDurationOption)
{
    totalScale_->Set(DEFAULT_TOTAL_SCALE);
    AnimationUtils::Animate(halfDurationOption, [&]() { totalScale_->Set(DEFAULT_SHRINK_SCALE_VER_TWELVE); });
    totalScale_->Set(DEFAULT_SHRINK_SCALE_VER_TWELVE);
    AnimationUtils::Animate(delayOption, [&]() { totalScale_->Set(DEFAULT_TOTAL_SCALE); });
}

void RadioModifier::UpdateIsOnAnimatableProperty(bool isCheck)
{
    AnimationOption delayOption;
    delayOption.SetDelay(DEFAULT_RADIO_ANIMATION_DURATION / 2);
    delayOption.SetDuration(DEFAULT_RADIO_ANIMATION_DURATION / 2);
    delayOption.SetCurve(Curves::FRICTION);

    AnimationOption halfDurationOption;
    halfDurationOption.SetDuration(DEFAULT_RADIO_ANIMATION_DURATION / 2);
    halfDurationOption.SetCurve(Curves::FRICTION);

    if (isOnAnimationFlag_->Get()) {
        pointScale_->Set(0);
        AnimationUtils::Animate(delayOption, [&]() { pointScale_->Set(DEFAULT_POINT_SCALE); });
        ringPointScale_->Set(1);
        AnimationUtils::Animate(halfDurationOption, [&]() { ringPointScale_->Set(0); });
    } else {
        pointScale_->Set(DEFAULT_POINT_SCALE);
        AnimationUtils::Animate(halfDurationOption, [&]() { pointScale_->Set(0); });
        ringPointScale_->Set(0);
        AnimationUtils::Animate(delayOption, [&]() { ringPointScale_->Set(1); });
    }

    totalScale_->Set(DEFAULT_TOTAL_SCALE);
    AnimationUtils::Animate(halfDurationOption, [&]() { totalScale_->Set(DEFAULT_SHRINK_SCALE); });
    totalScale_->Set(DEFAULT_SHRINK_SCALE);
    AnimationUtils::Animate(
        delayOption, [&]() { totalScale_->Set(1); },
        [isCheck, weakUiStatus = AceType::WeakClaim(AceType::RawPtr(uiStatus_))]() {
            auto uiStatus = weakUiStatus.Upgrade();
            if (uiStatus) {
                uiStatus->Set(static_cast<int32_t>(isCheck ? UIStatus::SELECTED : UIStatus::UNSELECTED));
            }
            auto context = PipelineBase::GetCurrentContext();
            if (context) {
                context->RequestFrame();
            }
        });
}

void RadioModifier::UpdateIndicatorAnimation(bool isCheck)
{
    auto springCurve = AceType::MakeRefPtr<InterpolatingSpring>(DEFAULT_INTERPOLATINGSPRING_VELOCITY,
        DEFAULT_INTERPOLATINGSPRING_MASS, DEFAULT_INTERPOLATINGSPRING_STIFFNESS, DEFAULT_INTERPOLATINGSPRING_DAMPING);
    AnimationOption halfDurationOption;
    halfDurationOption.SetCurve(Curves::FRICTION);
    halfDurationOption.SetDuration(DEFAULT_INDICATOR_ANIMATION_DURATION);
    AnimationOption delayOption;
    delayOption.SetCurve(springCurve);
    delayOption.SetDelay(DEFAULT_INDICATOR_ANIMATION_DURATION);
    delayOption.SetDuration(DEFAULT_INDICATOR_ANIMATION_DURATION);
    if (isCheck) {
        AnimationUtils::Animate(
            delayOption,
            [&]() {
                opacityScale_->Set(1);
                borderOpacityScale_->Set(0);
            },
            nullptr);
    } else {
        AnimationUtils::Animate(
            halfDurationOption,
            [&]() {
                opacityScale_->Set(0);
                borderOpacityScale_->Set(1);
            },
            nullptr);
    }
    UpdateTotalScaleOnAnimatable(isCheck, delayOption, halfDurationOption);
}

void RadioModifier::SetBoardColor(LinearColor color, int32_t duratuion, const RefPtr<CubicCurve>& curve)
{
    if (animateTouchHoverColor_) {
        AnimationOption option = AnimationOption();
        option.SetDuration(duratuion);
        option.SetCurve(curve);
        AnimationUtils::Animate(option, [&]() { animateTouchHoverColor_->Set(color); });
    }
}

void RadioModifier::PaintRadio(
    RSCanvas& canvas, bool /* checked */, const SizeF& contentSize, const OffsetF& contentOffset) const
{
    DrawFocusBoard(canvas, contentSize, contentOffset);
    DrawTouchAndHoverBoard(canvas, contentSize, contentOffset);
    float outCircleRadius = contentSize.Width() / CALC_RADIUS;
    float centerX = contentOffset.GetX() + outCircleRadius;
    float centerY = contentOffset.GetY() + outCircleRadius;
    RSPen pen;
    RSPen outPen;
    RSBrush brush;
    RSBrush shadowBrush;
    pen.SetAntiAlias(true);
    pen.SetWidth(borderWidth_);
    outPen.SetAntiAlias(true);
    brush.SetAntiAlias(true);
    shadowBrush.SetAntiAlias(true);
    shadowBrush.SetColor(ToRSColor(shadowColor_));
    if (uiStatus_->Get() == static_cast<int32_t>(UIStatus::SELECTED)) {
        if (!enabled_->Get()) {
            brush.SetColor(
                ToRSColor(pointColor_->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        } else {
            brush.SetColor(ToRSColor(pointColor_->Get()));
        }
        if (!NearZero(pointScale_->Get())) {
            // draw shadow
            canvas.AttachBrush(shadowBrush);
            canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * pointScale_->Get() + shadowWidth_);
            canvas.DetachBrush();
            // draw inner circle
            canvas.AttachBrush(brush);
            canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * pointScale_->Get());
            canvas.DetachBrush();
        }
        // draw ring circle
        if (!enabled_->Get()) {
            brush.SetColor(
                ToRSColor(inactivePointColor_.BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        } else {
            brush.SetColor(ToRSColor(inactivePointColor_));
        }
        if (!NearZero(ringPointScale_->Get())) {
            canvas.AttachBrush(brush);
            canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * ringPointScale_->Get());
            canvas.DetachBrush();
        }
        // draw out circular ring
        if (!enabled_->Get()) {
            outPen.SetColor(
                ToRSColor(activeColor_->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        } else {
            outPen.SetColor(ToRSColor(activeColor_->Get()));
        }
        auto outWidth = outCircleRadius * (totalScale_->Get() - pointScale_->Get() - ringPointScale_->Get());
        if (outWidth < borderWidth_) {
            outWidth = borderWidth_;
        }
        outPen.SetWidth(outWidth);
        canvas.AttachPen(outPen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * totalScale_->Get() - outWidth / CALC_RADIUS);
        canvas.DetachPen();
    } else if (uiStatus_->Get() == static_cast<int32_t>(UIStatus::UNSELECTED)) {
        auto alphaCalculate = static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA;
        if (!enabled_->Get()) {
            if (isFocused_->Get()) {
                brush.SetColor(ToRSColor(focusedBgUnchecked_.BlendOpacity(alphaCalculate)));
                pen.SetColor(ToRSColor(focusedRingUnchecked_.BlendOpacity(alphaCalculate)));
            } else {
                brush.SetColor(ToRSColor(inactivePointColor_.BlendOpacity(alphaCalculate)));
                pen.SetColor(ToRSColor(inactiveColor_->Get().BlendOpacity(alphaCalculate)));
            }
        } else {
            if (isFocused_->Get()) {
                brush.SetColor(ToRSColor(focusedBgUnchecked_));
                pen.SetColor(ToRSColor(focusedRingUnchecked_));
            } else {
                brush.SetColor(ToRSColor(inactivePointColor_));
                pen.SetColor(ToRSColor(inactiveColor_->Get()));
            }
        }
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius - borderWidth_);
        canvas.DetachBrush();
        // draw border with unselected color
        canvas.AttachPen(pen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius - borderWidth_ / CALC_RADIUS);
        canvas.DetachPen();
    }
}

void RadioModifier::PaintUnselectedIndicator(
    RSCanvas& canvas, float outCircleRadius, float centerX, float centerY) const
{
    RSPen pen;
    RSBrush brush;
    pen.SetAntiAlias(true);
    pen.SetWidth(borderWidth_);
    brush.SetAntiAlias(true);
    auto alphaCalculate = static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    if (!enabled_->Get()) {
        brush.SetColor(ToRSColor(inactivePointColor_.BlendOpacity(alphaCalculate)));
        pen.SetColor(ToRSColor(inactiveColor_->Get().BlendOpacity(alphaCalculate)));
    } else {
        brush.SetColor(ToRSColor(inactivePointColor_));
        pen.SetColor(ToRSColor(inactiveColor_->Get()));
    }
    canvas.AttachBrush(brush);
    canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius - borderWidth_);
    canvas.DetachBrush();
    // draw border with unselected color
    canvas.AttachPen(pen);
    canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * totalScale_->Get() - borderWidth_ / CALC_RADIUS);
    canvas.DetachPen();
}

void RadioModifier::PaintIndicator(
    RSCanvas& canvas, bool /* checked */, const SizeF& contentSize, const OffsetF& contentOffset) const
{
    DrawFocusBoard(canvas, contentSize, contentOffset);
    DrawTouchAndHoverBoard(canvas, contentSize, contentOffset);
    float outCircleRadius = contentSize.Width() / CALC_RADIUS;
    float centerX = contentOffset.GetX() + outCircleRadius;
    float centerY = contentOffset.GetY() + outCircleRadius;
    RSPen pen;
    RSPen outPen;
    RSBrush brush;
    pen.SetAntiAlias(true);
    auto borderOpacityScale = borderOpacityScale_->Get();
    pen.SetWidth(borderWidth_ * borderOpacityScale);
    outPen.SetAntiAlias(true);
    brush.SetAntiAlias(true);
    auto alphaCalculate = static_cast<float>(enabled_->Get() ? ENABLED_ALPHA : DISABLED_ALPHA) / ENABLED_ALPHA;
    outPen.SetColor(ToRSColor(activeColor_->Get().BlendOpacity(opacityScale_->Get()).BlendOpacity(alphaCalculate)));
    if (isFocused_->Get()) {
        brush.SetColor(ToRSColor(focusedBgUnchecked_.BlendOpacity(borderOpacityScale).BlendOpacity(alphaCalculate)));
    } else {
        brush.SetColor(ToRSColor(inactivePointColor_.BlendOpacity(borderOpacityScale).BlendOpacity(alphaCalculate)));
    }
    pen.SetColor(ToRSColor(inactiveColor_->Get().BlendOpacity(borderOpacityScale).BlendOpacity(alphaCalculate)));
    auto outWidth = outCircleRadius * totalScale_->Get();
    if (outWidth < borderWidth_) {
        outWidth = borderWidth_;
    }
    canvas.AttachPen(pen);
    canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * totalScale_->Get() - borderWidth_ / CALC_RADIUS);
    canvas.DetachPen();

    canvas.AttachBrush(brush);
    canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * totalScale_->Get() - borderWidth_);
    canvas.DetachBrush();

    outPen.SetWidth(outWidth);
    canvas.AttachPen(outPen);
    canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * totalScale_->Get() - outWidth / CALC_RADIUS);
    canvas.DetachPen();
}

void RadioModifier::DrawTouchAndHoverBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const
{
    CHECK_NULL_VOID(showHoverEffect_);
    float outCircleRadius = contentSize.Width() / CALC_RADIUS;
    float centerX = outCircleRadius + offset.GetX();
    float centerY = outCircleRadius + offset.GetY();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        outCircleRadius += sizeHover_.ConvertToPx();
    } else {
        outCircleRadius += hotZoneHorizontalPadding_.ConvertToPx();
    }
    RSBrush brush;
    brush.SetColor(ToRSColor(animateTouchHoverColor_->Get()));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius);
    canvas.DetachBrush();
}

void RadioModifier::DrawFocusBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const
{
    float outCircleRadius = contentSize.Width() / CALC_RADIUS;
    float centerX = outCircleRadius + offset.GetX();
    float centerY = outCircleRadius + offset.GetY();
    RSBrush brush;
    if (isFocused_->Get()) {
        brush.SetColor(ToRSColor(focusedBgColor_));
    } else {
        brush.SetColor(ToRSColor(Color::TRANSPARENT));
    }
    brush.SetAntiAlias(true);
    outCircleRadius += sizeFocused_.ConvertToPx();
    canvas.AttachBrush(brush);
    canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius);
    canvas.DetachBrush();
}
} // namespace OHOS::Ace::NG
