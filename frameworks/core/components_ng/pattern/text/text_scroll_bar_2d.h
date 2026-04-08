/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_SCROLL_BAR_2D_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_SCROLL_BAR_2D_H

#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
struct ScrollBarProperty;

struct UpdateScrollBarData {
    float offset;
    float estimatedHeight;
    Size viewPort;
    Offset viewOffset;
};
using ScrollBarScrollCallback = std::function<void(float offset, int32_t source, bool isVertical)>;
using ScrollBarEndScrollCallback = std::function<void(bool isVertical)>;

class TextScrollBar2D final : public AceType {
    DECLARE_ACE_TYPE(TextScrollBar2D, AceType);
    ACE_DISALLOW_COPY_AND_MOVE(TextScrollBar2D);

public:
    explicit TextScrollBar2D(const WeakPtr<ScrollablePattern>& pattern);
    ~TextScrollBar2D() final;

    void Update(const std::unique_ptr<ScrollBarProperty>& props);
    void UpdateVerticalBar(float offset, float estimatedHeight, const Size& viewPort, Offset viewOffset);
    void UpdateHorizontalBar(float offset, float estimatedHeight, const Size& viewPort, Offset viewOffset);
    void UpdateBorderRadius(bool isVertical);
    void OnDraw(DrawingContext& context) const;

    void SetScrollBarScrollCallback(ScrollBarScrollCallback&& callback)
    {
        scrollCallback_ = std::move(callback);
    }

    void SetScrollBarEndCallback(ScrollBarEndScrollCallback&& callback)
    {
        endScrollCallback_ = std::move(callback);
    }

    void SetDisplayMode(DisplayMode mode)
    {
        if (verticalBar_) {
            verticalBar_->SetDisplayMode(mode);
        }
        if (horizontalBar_) {
            horizontalBar_->SetDisplayMode(mode);
        }
    }

    DisplayMode GetDisplayMode() const
    {
        return displayMode_;
    }

    bool IsScrollable() const
    {
        return true;
    }

    void SetOpacity(uint8_t opacity)
    {
        if (verticalModifier_) {
            verticalModifier_->SetOpacity(opacity);
        }
        if (horizontalModifier_) {
            horizontalModifier_->SetOpacity(opacity);
        }
    }

    void PlayAppearAnimation(bool isVertical)
    {
        if (isVertical) {
            CHECK_NULL_VOID(verticalBar_);
            if (verticalBar_->GetOpacityAnimationType() != OpacityAnimationType::APPEAR) {
                verticalBar_->PlayScrollBarAppearAnimation();
            }
        } else {
            CHECK_NULL_VOID(horizontalBar_);
            if (horizontalBar_->GetOpacityAnimationType() != OpacityAnimationType::APPEAR) {
                horizontalBar_->PlayScrollBarAppearAnimation();
            }
        }
    }

    void ScheduleDisappearDelayTask()
    {
        ScheduleDisappearDelayTask(true);
        ScheduleDisappearDelayTask(false);
    }

    void ScheduleDisappearDelayTask(bool isVertical)
    {
        auto scrollBar = isVertical ? verticalBar_ : horizontalBar_;
        if (scrollBar) {
            scrollBar->ScheduleDisappearDelayTask();
        }
    }

    void SetPositionMode(PositionMode mode)
    {
        if (verticalBar_) {
            verticalBar_->SetPositionMode(mode);
        }
        if (verticalModifier_) {
            verticalModifier_->SetPositionMode(mode);
        }
    }

    RefPtr<NG::ScrollBar> GetVerticalBar() const
    {
        return verticalBar_;
    }

    RefPtr<NG::ScrollBar> GetHorizontalBar() const
    {
        return horizontalBar_;
    }

    RefPtr<ScrollBarOverlayModifier> GetVerticalModifier() const
    {
        return verticalModifier_;
    }

    RefPtr<ScrollBarOverlayModifier> GetHorizontalModifier() const
    {
        return horizontalModifier_;
    }

private:
    void InitNGScrollBar(NG::ScrollBar& bar, bool isVertical);
    void AddScrollableEvent();
    void SetInBarRegionCallback(const RefPtr<ScrollableEvent>& event);
    void SetInBarRectRegionCallback(const RefPtr<ScrollableEvent>& event);
    void SetBarCollectTouchTargetCallback(const RefPtr<ScrollableEvent>& event);
    void SetBarCollectClickAndLongPressTargetCallback(const RefPtr<ScrollableEvent>& event);
    void RemoveGestures(NG::ScrollBar& bar);
    void UpdateScrollBar(const UpdateScrollBarData& data, bool isVertical);
    bool HandleScrollPositionCallback(double offset, int32_t source, bool isMouseWheelScroll, bool isVertical);
    void HandleScrollEndCallback(bool isVertical);

    DisplayMode displayMode_ = DisplayMode::AUTO;
    WeakPtr<ScrollablePattern> pattern_;
    RefPtr<NG::ScrollBar> verticalBar_;
    RefPtr<NG::ScrollBar> horizontalBar_;
    RefPtr<ScrollBarOverlayModifier> verticalModifier_;
    RefPtr<ScrollBarOverlayModifier> horizontalModifier_;
    RefPtr<ScrollableEvent> scrollableEvent_;
    ScrollBarScrollCallback scrollCallback_;
    ScrollBarEndScrollCallback endScrollCallback_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_SCROLL_BAR_2D_H
