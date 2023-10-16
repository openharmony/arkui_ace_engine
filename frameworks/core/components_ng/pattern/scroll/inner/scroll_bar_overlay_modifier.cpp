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

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double FULL_ALPHA = 255.0;
constexpr float HALF = 0.5f;
constexpr float SPRING_MOTION_RESPONSE = 0.314f;
constexpr float SPRING_MOTION_DAMPING_FRACTION = 0.95f;
constexpr int32_t BAR_DISAPPEAR_DURATION = 400; // 400ms
constexpr int32_t BAR_APPEAR_DURATION = 100;    // 100ms
constexpr int32_t BAR_GROW_DURATION = 150;      // 150ms, scroll bar width expands from 4dp to 8dp
constexpr int32_t BAR_SHRINK_DURATION = 250;    // 250ms, scroll bar width shrinks from 8dp to 4dp
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
    TAG_LOGD(AceLogTag::ACE_INNER_SCROLL_BAR, "startBarAnimation hoverAnimationType:%{public}d, "
         "opacityAnimationType:%{public}d, needAdaptAnimation:%{public}u, fgRect:%{public}s",
        hoverAnimationType, opacityAnimationType, needAdaptAnimation, fgRect.ToString().c_str());
    CHECK_NULL_VOID(barX_);
    CHECK_NULL_VOID(barY_);
    CHECK_NULL_VOID(barWidth_);
    CHECK_NULL_VOID(barHeight_);
    if (hoverAnimationType == HoverAnimationType::NONE && !needAdaptAnimation) {
        SetRect(fgRect);
    } else {
        StartHoverAnimation(fgRect, hoverAnimationType);
        StartAdaptAnimation(fgRect, needAdaptAnimation);
    }
    if (opacityAnimationType != OpacityAnimationType::NONE) {
        StartOpacityAnimation(opacityAnimationType);
    }
}

void ScrollBarOverlayModifier::StartAdaptAnimation(const Rect& fgRect, bool needAdaptAnimation)
{
    CHECK_NULL_VOID(needAdaptAnimation);
    AnimationOption option;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(SPRING_MOTION_RESPONSE, SPRING_MOTION_DAMPING_FRACTION);
    option.SetCurve(motion);
    adaptAnimation_ = AnimationUtils::StartAnimation(option, [&]() {
        SetMainModeSize(fgRect.GetSize());
        SetMainModeOffset(fgRect.GetOffset());
    });
}

void ScrollBarOverlayModifier::StopAdaptAnimation()
{
    if (adaptAnimation_) {
        AnimationOption option;
        option.SetCurve(Curves::FRICTION);
        option.SetDuration(0);
        adaptAnimation_ = AnimationUtils::StartAnimation(option, [&]() {
            SetMainModeSize(Size(barWidth_->Get(), barHeight_->Get()));
            SetMainModeOffset(Offset(barX_->Get(), barY_->Get()));
        });
    }
}

void ScrollBarOverlayModifier::StartHoverAnimation(const Rect& fgRect, HoverAnimationType hoverAnimationType)
{
    CHECK_NULL_VOID(hoverAnimationType != HoverAnimationType::NONE);
    if (hoverAnimationType != hoverAnimatingType_) {
        StopHoverAnimation();
    }
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
        [&]() {
            SetCrossModeSize(fgRect.GetSize());
            SetCrossModeOffset(fgRect.GetOffset());
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
        AnimationOption option;
        option.SetCurve(Curves::SHARP);
        option.SetDuration(0);
        hoverAnimation_ = AnimationUtils::StartAnimation(option, [&]() {
            SetCrossModeSize(Size(barWidth_->Get(), barHeight_->Get()));
            SetCrossModeOffset(Offset(barX_->Get(), barY_->Get()));
        });
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
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    if (opacityAnimationType == OpacityAnimationType::DISAPPEAR) {
        option.SetDuration(BAR_DISAPPEAR_DURATION);
    } else if (opacityAnimationType == OpacityAnimationType::APPEAR) {
        option.SetDuration(BAR_APPEAR_DURATION);
    }
    opacityAnimatingType_ = opacityAnimationType;
    opacityAnimation_ = AnimationUtils::StartAnimation(
        option,
        [&]() {
            if (opacityAnimatingType_ == OpacityAnimationType::DISAPPEAR) {
                opacity_->Set(0);
            } else if (opacityAnimatingType_ == OpacityAnimationType::APPEAR) {
                opacity_->Set(UINT8_MAX);
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
} // namespace OHOS::Ace::NG
