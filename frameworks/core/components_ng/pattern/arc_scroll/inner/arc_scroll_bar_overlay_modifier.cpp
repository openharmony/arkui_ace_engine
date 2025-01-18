/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double FULL_ALPHA = 255.0;
constexpr int32_t BAR_GROW_DURATION = 150;       // 150ms, scroll bar width expands from 4dp to 8dp
constexpr int32_t BAR_SHRINK_DURATION = 250;     // 250ms, scroll bar width shrinks from 8dp to 4dp
} // namespace

ArcScrollBarOverlayModifier::ArcScrollBarOverlayModifier(
    const OffsetF& barOffset, const SizeF& barSize) : ScrollBarOverlayModifier(barOffset, barSize)
{
    strokeWidth_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    AttachProperty(strokeWidth_);
    curveRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    AttachProperty(curveRadius_);
    curveCenter_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
    AttachProperty(curveCenter_);
    startAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    AttachProperty(startAngle_);
    sweepAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    AttachProperty(sweepAngle_);
    backgroundStartAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    AttachProperty(backgroundStartAngle_);
    backgroundSweepAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    AttachProperty(backgroundSweepAngle_);
    backgroundStrokeWidth_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    AttachProperty(backgroundStrokeWidth_);
    backgroundCurveRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    AttachProperty(backgroundCurveRadius_);
    backgroundBarColor_ = AceType::MakeRefPtr<PropertyColor>(Color());
    AttachProperty(backgroundBarColor_);
}

void ArcScrollBarOverlayModifier::StartArcBarAnimation(HoverAnimationType hoverAnimationType,
    OpacityAnimationType opacityAnimationType, bool needAdaptAnimation, const ArcRound& arcBarRect,
    const ArcRound& backgroundArcBarRect)
{
    if (hoverAnimationType == HoverAnimationType::NONE && !needAdaptAnimation) {
        SetArcRect(arcBarRect);
        SetBackgroundArcRect(backgroundArcBarRect);
    } else {
        StartHoverAnimation(arcBarRect, backgroundArcBarRect, hoverAnimationType);
    }
    if (opacityAnimationType != OpacityAnimationType::NONE && GetScrollable()) {
        StartOpacityAnimation(opacityAnimationType);
    }
}

void ArcScrollBarOverlayModifier::SetBackgroundArcRect(const ArcRound& backgroundArcBarRect)
{
    backgroundStrokeWidth_->Set(backgroundArcBarRect.GetWidth());
    backgroundCurveRadius_->Set(backgroundArcBarRect.GetRadius());
    backgroundStartAngle_->Set(backgroundArcBarRect.GetStartAngle());
    backgroundSweepAngle_->Set(backgroundArcBarRect.GetSweepAngle());
}

void ArcScrollBarOverlayModifier::SetArcRect(const ArcRound& arcBarRect)
{
    strokeWidth_->Set(arcBarRect.GetWidth());
    curveRadius_->Set(arcBarRect.GetRadius());
    SetCurveCenter(arcBarRect.GetCenterPoint());
    startAngle_->Set(arcBarRect.GetStartAngle());
    sweepAngle_->Set(arcBarRect.GetSweepAngle());
}

void ArcScrollBarOverlayModifier::SetBackgroundBarColor(Color backgroundBarColor)
{
    CHECK_NULL_VOID(backgroundBarColor_);
    backgroundBarColor_->Set(backgroundBarColor);
}

void ArcScrollBarOverlayModifier::SetCurveCenter(Point curveCenter)
{
    CHECK_NULL_VOID(curveCenter_);
    float x = curveCenter.GetX();
    float y = curveCenter.GetY();
    OffsetF temp(x, y);
    curveCenter_->Set(temp);
}

void ArcScrollBarOverlayModifier::StartHoverAnimation(const ArcRound& arcBarRect,
    const ArcRound& backgroundArcBarRect, HoverAnimationType hoverAnimationType)
{
    if (hoverAnimationType == HoverAnimationType::NONE) {
        SetArcRect(arcBarRect);
        SetBackgroundArcRect(backgroundArcBarRect);
        return;
    }
    if (hoverAnimationType != GetHoverAnimatingType()) {
        StopHoverAnimation();
    }

    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    if (hoverAnimationType == HoverAnimationType::GROW) {
        option.SetDuration(BAR_GROW_DURATION);
    } else if (hoverAnimationType == HoverAnimationType::SHRINK) {
        option.SetDuration(BAR_SHRINK_DURATION);
    }

    SetHoverAnimatingType(hoverAnimationType);
    hoverAnimation_ = AnimationUtils::StartAnimation(
        option,
        [&]() {
            SetArcRect(arcBarRect);
            SetBackgroundArcRect(backgroundArcBarRect);
        },
        [weak = WeakClaim(this)]() {
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            modifier->SetHoverAnimatingType(HoverAnimationType::NONE);
        });
}

void ArcScrollBarOverlayModifier::onDraw(DrawingContext& drawingContext)
{
    CHECK_NULL_VOID(strokeWidth_);
    CHECK_NULL_VOID(curveCenter_);
    CHECK_NULL_VOID(startAngle_);
    CHECK_NULL_VOID(sweepAngle_);
    CHECK_NULL_VOID(curveRadius_);

    CHECK_NULL_VOID(backgroundStartAngle_);
    CHECK_NULL_VOID(backgroundSweepAngle_);
    CHECK_NULL_VOID(backgroundStrokeWidth_);
    CHECK_NULL_VOID(backgroundCurveRadius_);
    CHECK_NULL_VOID(backgroundBarColor_);
    DrawBackgroundArc(drawingContext);
    DrawArc(drawingContext);
}

void ArcScrollBarOverlayModifier::DrawArc(DrawingContext& context)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto strokeWidth = strokeWidth_->Get();
    auto& canvas = context.canvas;
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(strokeWidth);
    pen.SetCapStyle(ToRSCapStyle(LineCap::ROUND));
    auto barOpacity = GetOpacity() / FULL_ALPHA;
    pen.SetColor(ToRSColor(GetBarColor()->Get().BlendOpacity(barOpacity)));
    canvas.AttachPen(pen);
    auto center = curveCenter_->Get();
    auto radius = curveRadius_->Get();
    auto startAngle = startAngle_->Get();
    auto sweepAngle = sweepAngle_->Get();
    canvas.DrawArc(
        { center.GetX() - radius, center.GetY() - radius, center.GetX() + radius, center.GetY() + radius },
        startAngle, sweepAngle);
    canvas.DetachPen();
}

void ArcScrollBarOverlayModifier::DrawBackgroundArc(DrawingContext& context)
{
    CHECK_NULL_VOID(backgroundBarColor_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto& canvas = context.canvas;
    auto strokeWidth = backgroundStrokeWidth_->Get();
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(strokeWidth);
    pen.SetCapStyle(ToRSCapStyle(LineCap::ROUND));
    auto barOpacity = GetOpacity() / FULL_ALPHA;
    pen.SetColor(ToRSColor(backgroundBarColor_->Get().BlendOpacity(barOpacity)));

    canvas.AttachPen(pen);
    auto center = curveCenter_->Get();
    auto radius = backgroundCurveRadius_->Get();
    auto startAngle = backgroundStartAngle_->Get();
    auto sweepAngle = backgroundSweepAngle_->Get();

    canvas.DrawArc(
        { center.GetX() - radius, center.GetY() - radius, center.GetX() + radius, center.GetY() + radius },
        startAngle, sweepAngle);
    canvas.DetachPen();
}
} // namespace OHOS::Ace::NG