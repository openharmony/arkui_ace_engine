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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_SCROLL_INNER_ARC_SCROLL_BAR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_SCROLL_INNER_ARC_SCROLL_BAR_H

#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "base/geometry/arc_round.h"

namespace OHOS::Ace::NG {
class ArcScrollBar : public ScrollBar {
    DECLARE_ACE_TYPE(ArcScrollBar, ScrollBar);
public:
    ArcScrollBar() : ScrollBar(DisplayMode::AUTO, ShapeMode::ROUND, PositionMode::RIGHT) {}
    ~ArcScrollBar() override = default;
    
    const ArcRound& GetArcActiveRect() const
    {
        return arcActiveRect_;
    }
    const ArcRound& GetArcBarRect() const
    {
        return arcAarRect_;
    }
    virtual bool InBarTouchRegion(const Point& point) const override;
    virtual bool InBarHoverRegion(const Point& point) const override;
    virtual bool InBarRectRegion(const Point& point) const override;
    virtual void SetBarRegion(const Offset& offset, const Size& size) override;
    virtual void SetRoundTrickRegion(const Offset& offset, const Size& size, const Offset& lastOffset,
        double mainScrollExtent) override;
    virtual float CalcPatternOffset(float scrollBarOffset) const override;

    void ScheduleShrinkDelayTask();

private:
    void SetRoundTrickRegion(double estimatedHeight, double barRegionSize, double activeSize,
        double activeMainOffset, double normalWidth, const Size& size);
    void CalcReservedHeight() override;

private:
    ArcRound arcHoverRegion_;
    ArcRound arcAarRect_;
    ArcRound arcActiveRect_;
    ArcRound arcHotZoneRect_;
    double trickStartAngle_ = 0.0;
    double trickSweepAngle_ = 0.0;
    double width_ = 0.0;
    double centerDeviation_ = 0.0;
    CancelableCallback<void()> shrinkDelayTask_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_INNER_ARC_SCROLL_BAR_H