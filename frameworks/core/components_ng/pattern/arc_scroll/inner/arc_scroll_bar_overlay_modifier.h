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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_SCROLL_INNER_ARC_SCROLL_BAR_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_SCROLL_INNER_ARC_SCROLL_BAR_OVERLAY_MODIFIER_H

#include "core/components_ng/pattern/scroll/inner/scroll_bar_overlay_modifier.h"
#include "base/geometry/arc_round.h"

namespace OHOS::Ace::NG {
class ArcScrollBarOverlayModifier : public ScrollBarOverlayModifier {
    DECLARE_ACE_TYPE(ArcScrollBarOverlayModifier, ScrollBarOverlayModifier);
public:
    ArcScrollBarOverlayModifier(const OffsetF& barOffset = OffsetF(), const SizeF& barSize = SizeF());
    ~ArcScrollBarOverlayModifier() override = default;

    void StartArcBarAnimation(HoverAnimationType hoverAnimationType, OpacityAnimationType opacityAnimationType,
        bool needAdaptAnimation, const ArcRound& arcBarRect, const ArcRound& backgroundArcBarRect);
    void SetBackgroundArcRect(const ArcRound& backgroundArcBarRect);
    void SetArcRect(const ArcRound& arcBarRect);
    void SetBackgroundBarColor(Color backgroundBarColor);
    void SetCurveCenter(Point curveCenter);
    void StartHoverAnimation(const ArcRound& barRect, const ArcRound& backgroundArcBarRect,
        HoverAnimationType hoverAnimationType);

    void DrawArc(DrawingContext& context);
    void DrawBackgroundArc(DrawingContext& context);
    virtual void onDraw(DrawingContext& drawingContext) override;
    void SetStrokeWidth(float strokeWidth)
    {
        strokeWidth_->Set(strokeWidth);
    }
    void SetStartAngle(float startAngle)
    {
        startAngle_->Set(startAngle);
    }
    void SetSweepAngle(float sweepAngle)
    {
        sweepAngle_->Set(sweepAngle);
    }
    void SetCurveRadius(float curveRadius)
    {
        curveRadius_->Set(curveRadius);
    }

private:
    RefPtr<AnimatablePropertyOffsetF> curveCenter_;
    RefPtr<AnimatablePropertyFloat> startAngle_;
    RefPtr<AnimatablePropertyFloat> sweepAngle_;
    RefPtr<AnimatablePropertyFloat> strokeWidth_;
    RefPtr<AnimatablePropertyFloat> curveRadius_;
    RefPtr<AnimatablePropertyFloat> backgroundStartAngle_;
    RefPtr<AnimatablePropertyFloat> backgroundSweepAngle_;
    RefPtr<AnimatablePropertyFloat> backgroundStrokeWidth_;
    RefPtr<AnimatablePropertyFloat> backgroundCurveRadius_;
    RefPtr<PropertyColor> backgroundBarColor_;
    ACE_DISALLOW_COPY_AND_MOVE(ArcScrollBarOverlayModifier);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_INNER_ARC_SCROLL_BAR_OVERLAY_MODIFIER_H