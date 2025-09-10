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

#include "core/components_ng/pattern/scroll/inner/scroll_bar_overlay_modifier.h"

#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double FULL_ALPHA = 255.0;
constexpr float HALF = 0.5f;
constexpr float SPRING_MOTION_RESPONSE = 0.314f;
constexpr float SPRING_MOTION_DAMPING_FRACTION = 0.95f;
constexpr int32_t BAR_DISAPPEAR_DURATION = 300;  // 300ms
constexpr int32_t BAR_APPEAR_DURATION = 100;     // 100ms
constexpr int32_t BAR_GROW_DURATION = 150;       // 150ms, scroll bar width expands from 4dp to 8dp
constexpr int32_t BAR_SHRINK_DURATION = 250;     // 250ms, scroll bar width shrinks from 8dp to 4dp
constexpr int32_t BAR_DISAPPEAR_FRAME_RATE = 15; // 15fps, the expected frame rate of opacity animation
constexpr int32_t BAR_DISAPPEAR_MIN_FRAME_RATE = 0;
constexpr int32_t BAR_DISAPPEAR_MAX_FRAME_RATE = 90;
constexpr float ADAPT_ACCURACY = 0.5f;
} // namespace

ScrollBarOverlayModifier::ScrollBarOverlayModifier(const OffsetF& barOffset, const SizeF& barSize)
{
    barX_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(barOffset.GetX());
    AttachProperty(barX_);
    barY_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(barOffset.GetY());
    AttachProperty(barY_);
    barWidth_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(barSize.Width());
    AttachProperty(barWidth_);
    barHeight_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(barSize.Height());
    AttachProperty(barHeight_);
    opacity_ = AceType::MakeRefPtr<AnimatablePropertyUint8>(UINT8_MAX);
    AttachProperty(opacity_);
    barColor_ = AceType::MakeRefPtr<PropertyColor>(Color());
    AttachProperty(barColor_);
}

void ScrollBarOverlayModifier::onDraw(DrawingContext& drawingContext)
{
    CHECK_NULL_VOID(opacity_);
    CHECK_NULL_VOID(barColor_);
    CHECK_NULL_VOID(barWidth_);
    CHECK_NULL_VOID(barHeight_);
    CHECK_NULL_VOID(barX_);
    CHECK_NULL_VOID(barY_);
    CheckMainModeNearEqual();
    auto barWidth = barWidth_->Get();
    auto barHeight = barHeight_->Get();
    auto barX = barX_->Get();
    auto barY = barY_->Get();
    if (!NearZero(barWidth) && !NearZero(barHeight)) {
        auto& canvas = drawingContext.canvas;
        RSBrush brush;
        brush.SetBlendMode(RSBlendMode::SRC_OVER);
        brush.SetAntiAlias(true);
        RSRect fgRect(barX, barY, barX + barWidth, barY + barHeight);
        double filletRadius = barWidth * HALF;
        RSColor barColor = ToRSColor(barColor_->Get().BlendOpacity(opacity_->Get() / FULL_ALPHA));
        brush.SetColor(barColor);
        canvas.AttachBrush(brush);
        canvas.DrawRoundRect({ fgRect, filletRadius, filletRadius });
        canvas.DetachBrush();
        SetBoundsRect(RectF { barX, barY, barWidth, barHeight });
    }
}

void ScrollBarOverlayModifier::SetOffset(const OffsetF& barOffset)
{
    CHECK_NULL_VOID(barX_);
    CHECK_NULL_VOID(barY_);
    barX_->Set(barOffset.GetX());
    barY_->Set(barOffset.GetY());
}

void ScrollBarOverlayModifier::SetSize(const SizeF& barSize)
{
    CHECK_NULL_VOID(barWidth_);
    CHECK_NULL_VOID(barHeight_);
    barWidth_->Set(barSize.Width());
    barHeight_->Set(barSize.Height());
}

void ScrollBarOverlayModifier::SetRect(const Rect& fgRect)
{
    SetOffset(OffsetF(fgRect.Left(), fgRect.Top()));
    SetSize(SizeF(fgRect.Width(), fgRect.Height()));
}

void ScrollBarOverlayModifier::SetMainModeSize(const Size& size)
{
    if (positionMode_ == PositionMode::BOTTOM) {
        CHECK_NULL_VOID(barWidth_);
        barWidth_->Set(size.Width());
    } else {
        CHECK_NULL_VOID(barHeight_);
        barHeight_->Set(size.Height());
    }
}

void ScrollBarOverlayModifier::SetCrossModeSize(const Size& size)
{
    if (positionMode_ == PositionMode::BOTTOM) {
        CHECK_NULL_VOID(barHeight_);
        barHeight_->Set(size.Height());
    } else {
        CHECK_NULL_VOID(barWidth_);
        barWidth_->Set(size.Width());
    }
}

void ScrollBarOverlayModifier::SetMainModeOffset(const Offset& offset)
{
    if (positionMode_ == PositionMode::BOTTOM) {
        CHECK_NULL_VOID(barX_);
        barX_->Set(offset.GetX());
    } else {
        CHECK_NULL_VOID(barY_);
        barY_->Set(offset.GetY());
    }
}

void ScrollBarOverlayModifier::SetCrossModeOffset(const Offset& offset)
{
    if (positionMode_ == PositionMode::BOTTOM) {
        CHECK_NULL_VOID(barY_);
        barY_->Set(offset.GetY());
    } else {
        CHECK_NULL_VOID(barX_);
        barX_->Set(offset.GetX());
    }
}

void ScrollBarOverlayModifier::StartBarAnimation(HoverAnimationType hoverAnimationType,
    OpacityAnimationType opacityAnimationType, bool needAdaptAnimation, const Rect& fgRect)
{
    CHECK_NULL_VOID(barX_);
    CHECK_NULL_VOID(barY_);
    CHECK_NULL_VOID(barWidth_);
    CHECK_NULL_VOID(barHeight_);
    if (opacityAnimationType == OpacityAnimationType::NONE && GetOpacity() == 0) {
        AnimationUtils::ExecuteWithoutAnimation([weak = AceType::WeakClaim(this), fgRect]() {
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            modifier->SetRect(fgRect);
        });
    } else if (hoverAnimationType == HoverAnimationType::NONE && !needAdaptAnimation) {
        SetRect(fgRect);
    } else {
        StartHoverAnimation(fgRect, hoverAnimationType);
        StartAdaptAnimation(fgRect, needAdaptAnimation);
    }
    if (opacityAnimationType != OpacityAnimationType::NONE && isScrollable_) {
        StartOpacityAnimation(opacityAnimationType);
    }
}

void ScrollBarOverlayModifier::StartAdaptAnimation(const Rect& fgRect, bool needAdaptAnimation)
{
    CHECK_NULL_VOID(needAdaptAnimation);
    AnimationOption option;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(SPRING_MOTION_RESPONSE, SPRING_MOTION_DAMPING_FRACTION);
    option.SetCurve(motion);
    isAdaptAnimationStop_ = false;
    adaptAnimation_ = AnimationUtils::StartAnimation(option, [weak = WeakClaim(this), fgRect]() {
        auto modifier = weak.Upgrade();
        CHECK_NULL_VOID(modifier);
        modifier->SetMainModeSize(fgRect.GetSize());
        modifier->SetMainModeOffset(fgRect.GetOffset());
    });
}

void ScrollBarOverlayModifier::StopAdaptAnimation()
{
    if (adaptAnimation_) {
        isAdaptAnimationStop_ = true;
        AnimationUtils::StopAnimation(adaptAnimation_);
    }
}

void ScrollBarOverlayModifier::StartHoverAnimation(const Rect& fgRect, HoverAnimationType hoverAnimationType)
{
    // Only the cross axis offset is updated, the main axis offset will be updated by adaptAnimation.
    if (hoverAnimationType == HoverAnimationType::NONE) {
        SetCrossModeSize(fgRect.GetSize());
        SetCrossModeOffset(fgRect.GetOffset());
        return;
    }
    if (hoverAnimationType != hoverAnimatingType_) {
        StopHoverAnimation();
    }
    // In order to only play the offset of the hover part in the animation, update the cross axis offset in advance
    SetCrossModeOffset(fgRect.GetOffset() + GetHoverOffset(fgRect.GetSize()));
    hoverAnimatingType_ = hoverAnimationType;
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    if (hoverAnimatingType_ == HoverAnimationType::GROW) {
        option.SetDuration(BAR_GROW_DURATION);
    } else if (hoverAnimatingType_ == HoverAnimationType::SHRINK) {
        option.SetDuration(BAR_SHRINK_DURATION);
    }
    hoverAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak = WeakClaim(this), fgRect]() {
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            modifier->SetCrossModeSize(fgRect.GetSize());
            modifier->SetCrossModeOffset(fgRect.GetOffset());
        },
        [weak = WeakClaim(this)]() {
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            modifier->SetHoverAnimatingType(HoverAnimationType::NONE);
        });
}

void ScrollBarOverlayModifier::StopHoverAnimation()
{
    if (hoverAnimation_) {
        AnimationUtils::StopAnimation(hoverAnimation_);
    }
}

void ScrollBarOverlayModifier::StopOpacityAnimation()
{
    if (opacityAnimation_) {
        AnimationUtils::StopAnimation(opacityAnimation_);
    }
}

void ScrollBarOverlayModifier::StartOpacityAnimation(OpacityAnimationType opacityAnimationType)
{
    CHECK_NULL_VOID(opacity_);
    if (opacityAnimationType != opacityAnimatingType_) {
        StopOpacityAnimation();
    } else {
        return;
    }
    if (opacityAnimationType == OpacityAnimationType::APPEAR_WITHOUT_ANIMATION) {
        opacityAnimatingType_ = OpacityAnimationType::NONE;
        opacity_->Set(UINT8_MAX);
        return;
    }
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    if (opacityAnimationType == OpacityAnimationType::DISAPPEAR) {
        if (!isNavDestinationShow_) {
            opacityAnimatingType_ = OpacityAnimationType::NONE;
            opacity_->Set(0);
            return;
        }
        option.SetFrameRateRange(AceType::MakeRefPtr<FrameRateRange>(
            BAR_DISAPPEAR_MIN_FRAME_RATE, BAR_DISAPPEAR_MAX_FRAME_RATE, BAR_DISAPPEAR_FRAME_RATE));
        option.SetDuration(BAR_DISAPPEAR_DURATION);
    } else if (opacityAnimationType == OpacityAnimationType::APPEAR) {
        option.SetDuration(BAR_APPEAR_DURATION);
    }
    opacityAnimatingType_ = opacityAnimationType;
    opacityAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak = WeakClaim(this)]() {
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            if (modifier->opacityAnimatingType_ == OpacityAnimationType::DISAPPEAR) {
                modifier->opacity_->Set(0);
            } else if (modifier->opacityAnimatingType_ == OpacityAnimationType::APPEAR) {
                modifier->opacity_->Set(UINT8_MAX);
            }
        },
        [weak = WeakClaim(this)]() {
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            modifier->SetOpacityAnimatingType(OpacityAnimationType::NONE);
        });
}

void ScrollBarOverlayModifier::SetBarColor(Color barColor)
{
    CHECK_NULL_VOID(barColor_);
    barColor_->Set(barColor);
}

Offset ScrollBarOverlayModifier::GetHoverOffset(const Size& size) const
{
    if (positionMode_ == PositionMode::RIGHT) {
        return Offset(size.Width() - barWidth_->Get(), 0.f);
    } else if (positionMode_ == PositionMode::BOTTOM) {
        return Offset(0.f, size.Height() - barHeight_->Get());
    }
    return Offset::Zero();
}

void ScrollBarOverlayModifier::CheckMainModeNearEqual()
{
    if (isAdaptAnimationStop_) {
        return;
    }
    float MainModeHeight = 0.f;
    float MainModeOffset = 0.f;
    if (positionMode_ == PositionMode::BOTTOM) {
        MainModeHeight = barWidth_->Get();
        MainModeOffset = barX_->Get();
    } else {
        MainModeHeight = barHeight_->Get();
        MainModeOffset = barY_->Get();
    }
    if (NearEqual(lastMainModeHeight_, MainModeHeight, ADAPT_ACCURACY) &&
        NearEqual(lastMainModeOffset_, MainModeOffset, ADAPT_ACCURACY)) {
        StopAdaptAnimation();
    }
    lastMainModeHeight_ = MainModeHeight;
    lastMainModeOffset_ = MainModeOffset;
}
} // namespace OHOS::Ace::NG
