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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FREE_SCROLL_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FREE_SCROLL_CONTROLLER_H

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
class AxisAnimator;

enum class State { IDLE, DRAG, FLING, WHEEL };

using TextFreeScrollCallback = std::function<void(float, int32_t, bool)>;
using TextFreeEndScrollCallback = std::function<void(bool)>;
using CheckCrashEdgeCallback = std::function<bool()>;

class TextFreeScrollController final : public AceType {
    DECLARE_ACE_TYPE(TextFreeScrollController, AceType);
    ACE_DISALLOW_COPY_AND_MOVE(TextFreeScrollController);

public:
    explicit TextFreeScrollController(const WeakPtr<ScrollablePattern>& pattern);
    ~TextFreeScrollController() final;

    RefPtr<NGGestureRecognizer> GetGestureRecognizer() const
    {
        return recognizer_;
    }

    void SetOnScrollCallback(TextFreeScrollCallback&& callback)
    {
        freeScrollCallback_ = std::move(callback);
    }

    void SetOnScrollEndCallback(TextFreeEndScrollCallback&& callback)
    {
        freeEndScrollCallback_ = std::move(callback);
    }

    void UpdateCurrentOffset(const OffsetF& offset)
    {
        currentOffset_ = offset;
    }
    void Fling(float velocity, bool isVertical);
    void StopScrollAnimation(bool isVertical);
    void StopAllScrollAnimation();

private:
    void InitializePanRecognizer();
    void InitializeTouchEvent();

    RefPtr<PanRecognizer> CreatePanRecognizer(uint32_t direction);
    void HandlePanStart(const GestureEvent& event, bool isVertical);
    void HandlePanUpdate(const GestureEvent& event, bool isVertical);
    void HandlePanEndOrCancel(const GestureEvent& event, bool isVertical);
    void HandleTouchDown();
    void HandleOffsetUpdate(float currentValue, bool isVertical);
    void HandleAnimationEnd(bool isVertical);
    void FireOnScrollUpdate(float offset, int32_t source, bool isVertical);
    void FireOnScrollEnd(bool isVertical) const;
    void TriggerMouseAnimation(float delta, bool isVertical);
    void HandleMouseAnimationFrame(float newOffset);
    void UpdateState(bool isVertical, State newState)
    {
        if (isVertical) {
            verticalState_ = newState;
        } else {
            horizontalState_ = newState;
        }
    }

    bool IsEqualState(bool isVertical, State state)
    {
        return isVertical ? verticalState_ == state : horizontalState_ == state;
    }

    WeakPtr<ScrollablePattern> pattern_;
    WeakPtr<FrameNode> weakHost_;
    WeakPtr<PipelineContext> context_;
    RefPtr<NodeAnimatablePropertyFloat> offsetX_;
    RefPtr<NodeAnimatablePropertyFloat> offsetY_;
    OffsetF currentOffset_;
    RefPtr<NGGestureRecognizer> recognizer_;
    RefPtr<TouchEventImpl> freeTouch_;
    RefPtr<AxisAnimator> wheelAnimator_;
    bool mouseWheelScrollIsVertical_ = true;
    TextFreeScrollCallback freeScrollCallback_;
    TextFreeEndScrollCallback freeEndScrollCallback_;
    State verticalState_ = State::IDLE;
    State horizontalState_ = State::IDLE;
    float flingFinalPos_ = 0.0f;
    uint64_t lastVsyncTime_ = 0;
    float lastPosition_ = 0.0f;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FREE_SCROLL_CONTROLLER_H
