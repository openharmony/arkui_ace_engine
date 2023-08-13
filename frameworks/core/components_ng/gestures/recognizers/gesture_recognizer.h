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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_GESTURE_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_GESTURE_RECOGNIZER_H

#include <memory>

#include "base/memory/referenced.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/event/axis_event.h"
#include "core/event/touch_event.h"
#include "frameworks/base/geometry/ng/point_t.h"

namespace OHOS::Ace::NG {

enum class RefereeState { READY, DETECTING, PENDING, PENDING_BLOCKED, SUCCEED_BLOCKED, SUCCEED, FAIL };

class ACE_EXPORT NGGestureRecognizer : public TouchEventTarget {
    DECLARE_ACE_TYPE(NGGestureRecognizer, TouchEventTarget)

public:
    static std::unordered_map<int, TransformConfig>& GetGlobalTransCfg();

    static std::unordered_map<int, AncestorNodeInfo>& GetGlobalTransIds();

    static void ResetGlobalTransCfg();

    // Triggered when the gesture referee finishes collecting gestures and begin a gesture referee.
    void BeginReferee(int32_t touchId, bool needUpdateChild = false)
    {
        OnBeginGestureReferee(touchId, needUpdateChild);
    }

    // Triggered when the Gesture referee ends a gesture referee.
    void FinishReferee(int32_t touchId)
    {
        OnFinishGestureReferee(touchId);
    }

    // Called when request of handling gesture sequence is accepted by gesture referee.
    virtual void OnAccepted() = 0;

    // Called when request of handling gesture sequence is rejected by gesture referee.
    virtual void OnRejected() = 0;

    // Called when request of handling gesture sequence is pending by gesture referee.
    virtual void OnPending()
    {
        refereeState_ = RefereeState::PENDING;
    }

    // Called when request of handling gesture sequence is blocked by gesture referee.
    virtual void OnBlocked()
    {
        if (disposal_ == GestureDisposal::ACCEPT) {
            refereeState_ = RefereeState::SUCCEED_BLOCKED;
        }
        if (disposal_ == GestureDisposal::PENDING) {
            refereeState_ = RefereeState::PENDING_BLOCKED;
        }
    }

    // Reconcile the state from the given recognizer into this. The
    // implementation must check that the given recognizer type matches the
    // current one. The return value should be false if the reconciliation fails
    // and true if it succeeds
    virtual bool ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
    {
        return true;
    }

    bool DispatchEvent(const TouchEvent& point) override
    {
        return true;
    }
    bool HandleEvent(const TouchEvent& point) override;
    bool HandleEvent(const AxisEvent& event) override;

    GesturePriority GetPriority() const
    {
        return priority_;
    }

    void SetPriority(GesturePriority priority)
    {
        priority_ = priority;
    }

    GestureMask GetPriorityMask() const
    {
        return priorityMask_;
    }

    void SetPriorityMask(GestureMask priorityMask)
    {
        priorityMask_ = priorityMask;
    }

    GestureDisposal GetGestureDisposal() const
    {
        return disposal_;
    }

    RefereeState GetRefereeState() const
    {
        return refereeState_;
    }

    void SetGestureGroup(const WeakPtr<NGGestureRecognizer>& gestureGroup)
    {
        gestureGroup_ = gestureGroup;
    }

    void SetOnAction(const GestureEventFunc& onAction)
    {
        onAction_ = std::make_unique<GestureEventFunc>(onAction);
    }

    void SetOnActionStart(const GestureEventFunc& onActionStart)
    {
        onActionStart_ = std::make_unique<GestureEventFunc>(onActionStart);
    }

    void SetOnActionUpdate(const GestureEventFunc& onActionUpdate)
    {
        onActionUpdate_ = std::make_unique<GestureEventFunc>(onActionUpdate);
    }

    void SetOnActionEnd(const GestureEventFunc& onActionEnd)
    {
        onActionEnd_ = std::make_unique<GestureEventFunc>(onActionEnd);
    }

    void SetOnActionCancel(const GestureEventNoParameter& onActionCancel)
    {
        onActionCancel_ = std::make_unique<GestureEventNoParameter>(onActionCancel);
    }

    inline void SendCancelMsg()
    {
        if (onActionCancel_ && *onActionCancel_) {
            (*onActionCancel_)();
        }
    }

    void SetIsExternalGesture(bool isExternalGesture)
    {
        isExternalGesture_ = isExternalGesture;
    }

    bool GetIsExternalGesture() const
    {
        return isExternalGesture_;
    }

    bool IsPending() const
    {
        return (refereeState_ == RefereeState::PENDING) || (refereeState_ == RefereeState::PENDING_BLOCKED);
    }

    bool IsRefereeFinished() const
    {
        return (refereeState_ == RefereeState::SUCCEED) || (refereeState_ == RefereeState::FAIL) ||
               (refereeState_ == RefereeState::SUCCEED_BLOCKED);
    }

    // called when gesture scope is closed.
    void ResetStatusOnFinish()
    {
        refereeState_ = RefereeState::READY;
        OnResetStatus();
    }

    // called to reset status manually without rejected callback.
    void ResetStatus()
    {
        refereeState_ = RefereeState::READY;
        OnResetStatus();
    }
    virtual bool CheckTouchId(int32_t touchId) = 0;

    SourceType getDeviceType()
    {
        return deviceType_;
    }

    void SetSize(std::optional<double> recognizerTargetAreaHeight, std::optional<double> recognizerTargetAreaWidth)
    {
        EventTarget recognizerTarget;
        recognizerTarget.area.SetHeight(Dimension(recognizerTargetAreaHeight.value()));
        recognizerTarget.area.SetWidth(Dimension(recognizerTargetAreaWidth.value()));
        recognizerTarget_ = recognizerTarget;
    }

    void SetTransInfo(int id);
    void Transform(PointF& windowPointF, PointF& originPointF);
protected:
    void Adjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
    {
        disposal_ = disposal;
        BatchAdjudicate(recognizer, disposal);
    }
    virtual void BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal);

    virtual void OnBeginGestureReferee(int32_t touchId, bool needUpdateChild = false) {}
    virtual void OnFinishGestureReferee(int32_t touchId) {}

    virtual void HandleTouchDownEvent(const TouchEvent& event) = 0;
    virtual void HandleTouchUpEvent(const TouchEvent& event) = 0;
    virtual void HandleTouchMoveEvent(const TouchEvent& event) = 0;
    virtual void HandleTouchCancelEvent(const TouchEvent& event) = 0;
    virtual void HandleTouchDownEvent(const AxisEvent& event) {}
    virtual void HandleTouchUpEvent(const AxisEvent& event) {}
    virtual void HandleTouchMoveEvent(const AxisEvent& event) {}
    virtual void HandleTouchCancelEvent(const AxisEvent& event) {}

    virtual void OnResetStatus() = 0;

    RefereeState refereeState_ = RefereeState::READY;

    GestureDisposal disposal_ = GestureDisposal::NONE;

    GesturePriority priority_ = GesturePriority::Low;

    GestureMask priorityMask_ = GestureMask::Normal;

    bool isExternalGesture_ = false;

    std::unique_ptr<GestureEventFunc> onAction_;
    std::unique_ptr<GestureEventFunc> onActionStart_;
    std::unique_ptr<GestureEventFunc> onActionUpdate_;
    std::unique_ptr<GestureEventFunc> onActionEnd_;
    std::unique_ptr<GestureEventNoParameter> onActionCancel_;

    int64_t deviceId_ = 0;
    SourceType deviceType_ = SourceType::NONE;
    // size of recognizer target.
    std::optional<EventTarget> recognizerTarget_ = std::nullopt;
    int transId_;

    int32_t currentFingers_ = 0;
private:
    WeakPtr<NGGestureRecognizer> gestureGroup_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_GESTURE_RECOGNIZER_H
