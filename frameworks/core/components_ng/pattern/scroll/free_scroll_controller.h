/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_FREE_GESTURE_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_FREE_GESTURE_CONTROLLER_H

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {
class ScrollPattern;
class AxisAnimator;
enum class ScrollEdge;

/**
 * @brief Controller for free scrolling behavior. It manages related gestures and animations.
 *
 */
class FreeScrollController final : public AceType {
    DECLARE_ACE_TYPE(FreeScrollController, AceType);
    ACE_DISALLOW_COPY_AND_MOVE(FreeScrollController);

public:
    explicit FreeScrollController(ScrollPattern& pattern);
    ~FreeScrollController() final;

    RefPtr<PanRecognizer> GetFreePanGesture() const
    {
        freePanGesture_->SetEnabled(enableScroll_); // workaround gesture's internal reset
        return freePanGesture_;
    }

    /**
     * @brief Allow other modules to modify offset. Calling this function automatically stops scroll animations.
     */
    void SetOffset(OffsetF newPos, bool allowOverScroll = false);
    inline void UpdateOffset(const OffsetF& delta)
    {
        SetOffset(offset_->Get() + delta);
    }

    void OnLayoutFinished(const OffsetF& adjustedOffset, const SizeF& scrollableArea);

    OffsetF GetOffset() const;
    const OffsetF& GetLayoutOffset() const
    {
        return actualOffset_;
    }

    /**
     * @brief Start a scroll animation to the final position.
     */
    void ScrollTo(OffsetF finalPos, const std::optional<float>& velocity,
        std::optional<int32_t> duration = std::nullopt, RefPtr<Curve> curve = nullptr, bool allowOverScroll = false);

private:
    void InitializePanRecognizer();
    void InitializeTouchEvent();

    void HandlePanStart(const GestureEvent& event);
    void HandlePanUpdate(const GestureEvent& event);
    void HandlePanEndOrCancel(const GestureEvent& event);

    void HandleTouchDown();
    void HandleTouchUpOrCancel();

    /**
     * @brief update callback of AnimatableProperty @c offset_.
     */
    void HandleOffsetUpdate(const OffsetF& currentValue);

    /**
     * @brief Start the scroll animation if possible with the given velocity and offset_.
     */
    void Fling(const OffsetF& velocity);
    void StopScrollAnimation();
    void HandleAnimationEnd();

    /**
     * @brief clamp position to be within the scrollable area.
     */
    OffsetF ClampPosition(const OffsetF& finalPos) const;

    /**
     * @brief Check if the new offset would reach any edges. If so, fire corresponding user callbacks.
     * @return true if any edge is reached, false otherwise.
     */
    bool CheckCrashEdge(const OffsetF& newOffset, const SizeF& scrollableArea) const;

    /**
     * @brief triggers onWillScroll user callback
     * @return user-modified delta
     */
    OffsetF FireOnWillScroll(const OffsetF& delta, ScrollState state, ScrollSource source) const;
    void FireOnDidScroll(const OffsetF& delta, ScrollState state) const;
    void FireOnScrollStart() const;
    void FireOnScrollEnd() const;
    void FireOnScrollEdge(const std::vector<ScrollEdge>& edges) const;

    void AnimateOnMouseScroll(const OffsetF& delta);
    void HandleAxisAnimationFrame(float newOffset);

    ScrollPattern& pattern_;
    RefPtr<NodeAnimatablePropertyOffsetF> offset_;
    OffsetF actualOffset_; // actual displayed offset, adjusted by LayoutAlgorithm
    RefPtr<PanRecognizer> freePanGesture_;
    RefPtr<TouchEventImpl> freeTouch_;
    RefPtr<AxisAnimator> axisAnimator_; // to smooth out mouse wheel scrolls

public:
    enum class State {
        IDLE,
        DRAG,
        FLING,
        EXTERNAL_FLING, // used for external animations like scroller animation
        BOUNCE,         // used for bounce animation transitioned from FLING when reaching edge
    };

private:
    State state_ = State::IDLE;
    bool enableScroll_ = true;
    bool mouseWheelScrollIsVertical_ = true;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_FREE_GESTURE_CONTROLLER_H
