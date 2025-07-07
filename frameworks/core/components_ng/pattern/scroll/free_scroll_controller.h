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
        if (!enableScroll_) {
            return MakeRefPtr<PanRecognizer>(0, PanDirection {}, 1.0); // dummy recognizer
        }
        return freePanGesture_;
    }

    /**
     * @brief Allow other modules to modify offset. Calling this function automatically stops scroll animations.
     * @attention doesn't allow over-scroll
     */
    void UpdateOffset(const OffsetF& delta);

    void OnLayoutFinished(const OffsetF& adjustedOffset, const SizeF& scrollableArea);

    OffsetF GetOffset() const;

private:
    void InitializePanRecognizer();
    void InitializeTouchEvent();

    void HandlePanStart(const GestureEvent& event);
    void HandlePanUpdate(const GestureEvent& event);
    void HandlePanEndOrCancel(const GestureEvent& event);

    void HandleTouchDown();
    void HandleTouchUpOrCancel();

    /**
     * @brief Start the scroll animation if possible with the given velocity and offset_.
     */
    void TryScrollAnimation(const OffsetF& velocity);
    void StopScrollAnimation();
    void HandleAnimationUpdate(const OffsetF& currentValue);

    /**
     * @brief clamp position to be within the scrollable area.
     */
    void ClampPosition(OffsetF& finalPos) const;

    /**
     * @brief triggers onWillScroll user callback
     * @return user-modified delta
     */
    OffsetF FireOnWillScroll(const OffsetF& delta, ScrollState state, ScrollSource source) const;
    void FireOnDidScroll(const OffsetF& delta, ScrollState state) const;

    ScrollPattern& pattern_;
    RefPtr<NodeAnimatablePropertyOffsetF> offset_;
    OffsetF prevOffset_;
    RefPtr<PanRecognizer> freePanGesture_;
    RefPtr<TouchEventImpl> freeTouch_;
    float friction_ = 0.0f;
    ScrollState state_ = ScrollState::IDLE;
    bool enableScroll_ = true;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_FREE_GESTURE_CONTROLLER_H
