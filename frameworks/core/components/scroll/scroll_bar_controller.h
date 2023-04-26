/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_BAR_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_BAR_CONTROLLER_H

#include <functional>

#include "core/animation/animator.h"
#include "core/animation/friction_motion.h"
#include "core/animation/scroll_motion.h"
#include "core/common/vibrator/vibrator.h"
#include "core/event/touch_event.h"
#include "core/gestures/drag_recognizer.h"
#include "core/gestures/pan_recognizer.h"
#include "core/gestures/raw_recognizer.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

using ScrollBarPositionCallback = std::function<bool(double, int32_t source)>;
using ScrollBarEndCallback = std::function<void(int32_t)>;
using ScrollBarEventCallback = std::function<void()>;
using ScrollBarTouchEventCallback = std::function<void(double)>;

class ScrollBarController : public TouchEventTarget {
    DECLARE_ACE_TYPE(ScrollBarController, TouchEventTarget);

public:
    ScrollBarController() = default;
    ~ScrollBarController() override = default;

    void Initialize(const WeakPtr<PipelineContext>& context, bool isVertical);
    void HandleScrollBarEnd();
    void HandleTouchDown();
    void HandleTouchUp();
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd(const GestureEvent& info);
    virtual void MarkScrollRender();
    void Reset();

    bool DispatchEvent(const TouchEvent& point) override
    {
        return true;
    }
    bool HandleEvent(const TouchEvent& event) override
    {
        if (panRecognizer_) {
            panRecognizer_->HandleEvent(event);
        }
        if (rawRecognizer_) {
            return rawRecognizer_->HandleEvent(event);
        }
        return true;
    }
    bool HandleEvent(const AxisEvent& event) override
    {
        if (panRecognizer_) {
            return panRecognizer_->HandleEvent(event);
        }
        return false;
    }

    void SetCallback(const ScrollBarPositionCallback& callback)
    {
        callback_ = callback;
    }

    void SetBarEndCallback(const ScrollBarEndCallback& barEndCallback)
    {
        barEndCallback_ = barEndCallback;
    }

    void SetCoordinateOffset(const Offset& offset) const
    {
        if (panRecognizer_) {
            panRecognizer_->SetCoordinateOffset(offset);
        }
        if (rawRecognizer_) {
            rawRecognizer_->SetCoordinateOffset(offset);
        }
    }

    void SetScrollEndCallback(const ScrollBarEventCallback& scrollEndCallback)
    {
        scrollEndCallback_ = scrollEndCallback;
    }

    void SetTouchUpCallback(const ScrollBarTouchEventCallback& touchUpCallback)
    {
        touchUpCallback_ = touchUpCallback;
    }

    void SetTouchDownCallback(const ScrollBarTouchEventCallback& touchDownCallback)
    {
        touchDownCallback_ = touchDownCallback;
    }

    void SetScrollNode(const WeakPtr<RenderNode>& scroll)
    {
        scroll_ = scroll;
    }

    bool IsActive() const
    {
        return isActive_;
    }

    void SetActive(bool isActive)
    {
        isActive_ = isActive;
    }

    void SetInactiveWidth(const Dimension& inactiveWidth)
    {
        inactiveWidth_ = inactiveWidth;
    }

    void SetActiveWidth(const Dimension& activeWidth)
    {
        activeWidth_ = activeWidth;
    }

    const Dimension& GetInactiveWidth() const
    {
        return inactiveWidth_;
    }

    const Dimension& GetActiveWidth() const
    {
        return activeWidth_;
    }

    bool IsPressed() const
    {
        return isPressed_;
    }

    void SetIsHover(bool isInBarRegion);

    void StopScrollEndAnimator()
    {
        if (scrollEndAnimator_ && !scrollEndAnimator_->IsStopped()) {
            scrollEndAnimator_->Stop();
        }
    }
    void OnFlushTouchEventsBegin() override;
    void OnFlushTouchEventsEnd() override;

protected:
    virtual bool UpdateScrollPosition(double offset, int32_t source);

    virtual void ProcessScrollMotion(double position);

    virtual bool CheckScroll();

    // Play grow when hover or pressed, from inactive with to active width.
    void PlayGrowAnimation();
    // Play shrink animation when lost hover or pressed state, from active with to inactive width.
    void PlayShrinkAnimation();

    void InitBarEndAnimation(const WeakPtr<PipelineContext>& context);

    WeakPtr<RenderNode> scroll_;
    ScrollBarPositionCallback callback_;
    ScrollBarEventCallback scrollEndCallback_;
    ScrollBarEndCallback barEndCallback_;
    ScrollBarTouchEventCallback touchUpCallback_;
    ScrollBarTouchEventCallback touchDownCallback_;

    RefPtr<PanRecognizer> panRecognizer_;
    RefPtr<RawRecognizer> rawRecognizer_;

    RefPtr<Animator> scrollEndAnimator_;
    RefPtr<Animator> touchAnimator_;
    RefPtr<Animator> dragEndAnimator_;
    RefPtr<FrictionMotion> dragEndMotion_;
    RefPtr<Vibrator> vibrator_;
    WeakPtr<PipelineContext> context_;

    bool isVertical_ = true;
    bool isActive_ = false;
    // Whether scroll bar is pressed, use different style when pressed.
    bool isPressed_ = false;
    // Whether scroll bar is hover.
    bool isHover_ = false;
    // Whether event is in scroll bar region.
    bool isInBar_ = false;
    double currentPos_ = 0.0;
    Dimension activeWidth_;
    Dimension inactiveWidth_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_BAR_CONTROLLER_H
