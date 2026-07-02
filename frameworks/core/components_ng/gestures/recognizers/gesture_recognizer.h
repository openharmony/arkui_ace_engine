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

#include <functional>
#include <memory>
#include <unordered_set>

#include "base/memory/referenced.h"
#include "core/components_ng/event/gesture_types.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/event/axis_event.h"
#include "core/event/touch_event.h"
#include "frameworks/base/geometry/ng/point_t.h"

// Forward declarations and type aliases from gesture_event.h
namespace OHOS::Ace {
class GestureEvent;
struct AxisEvent;
using GestureEventFunc = std::function<void(GestureEvent& info)>;
using GestureEventNoParameter = std::function<void()>;
}

namespace OHOS::Ace::NG {
enum class GestureListenerType;
enum class GestureActionPhase;
class Gesture;
class GestureInfo;

struct DelayedTask {
    WeakPtr<NGGestureRecognizer> recognizer;
    int64_t timeStamp = 0;
    int32_t time = 0;
    std::function<void()> task;
};

enum class RefereeState { READY, DETECTING, PENDING, PENDING_BLOCKED, SUCCEED_BLOCKED, SUCCEED, FAIL };

enum class CurrentCallbackState { READY, START, UPDATE, END, CANCEL };

enum class StateChangeReason {
    UNKNOWN,
    ACCEPTED_BY_REFEREE,
    REJECTED_BY_REFEREE,
    PENDING_WAITING,
    BLOCKED_BY_OTHER,
    DETECTING_STARTED,
    READY_RESET,
    CLICK_SINGLE_TAP,
    CLICK_DOUBLE_TAP_FIRST,
    CLICK_DOUBLE_TAP_SECOND,
    CLICK_TIMEOUT,
    CLICK_MOVE_OUT_REGION,
    CLICK_FINGER_COUNT_NOT_MATCH,
    LONG_PRESS_TIME_REACHED,
    LONG_PRESS_FINGER_UP,
    LONG_PRESS_MOVE_EXCEED,
    PAN_DISTANCE_EXCEED,
    PAN_DIRECTION_MATCH,
    PAN_FINGER_UP,
    PAN_BRIDGE_MODE,
    PINCH_DISTANCE_REACHED,
    PINCH_CONTINUOUS_ACCEPT,
    PINCH_DISTANCE_CHANGE,
    PINCH_FINGER_COUNT_NOT_MATCH,
    ROTATION_ANGLE_REACHED,
    ROTATION_ANGLE_CHANGE,
    ROTATION_FINGER_COUNT_NOT_MATCH,
    SWIPE_SPEED_REACHED,
    SWIPE_SPEED_EXCEED,
    SWIPE_DIRECTION_NOT_MATCH,
    EXCLUSIVE_ACTIVE_WIN,
    EXCLUSIVE_OTHER_FAIL,
    PARALLEL_ACCEPT,
    PARALLEL_REJECT,
    SEQUENCED_STEP_COMPLETE,
    FORCE_CLEAN,
    USER_CANCEL,
    SYSTEM_CANCEL
};

inline std::string TransRefereeState(RefereeState state)
{
    const char *str[] = { "READY", "DETECTING", "PENDING", "PENDING_BLOCKED", "SUCCEED_BLOCKED", "SUCCEED", "FAIL" };
    if (state >= RefereeState::READY && state <= RefereeState::FAIL) {
        return str[static_cast<int32_t>(state)];
    }
    return std::string("State:").append(std::to_string(static_cast<int32_t>(state)));
}

std::string TransStateChangeReason(StateChangeReason reason);

class FrameNode;
using GestureEventWithRefereeState = std::function<void(RefereeState state)>;

class ACE_FORCE_EXPORT NGGestureRecognizer : public TouchEventTarget {
    DECLARE_ACE_TYPE(NGGestureRecognizer, TouchEventTarget);

public:
    // IsRealTime is true when using real-time layouts.
    static void Transform(PointF& localPointF, const WeakPtr<FrameNode>& node, bool isRealTime = false,
        bool isPostEventResult = false, int32_t postEventNodeId = -1);

    static std::vector<Matrix4> GetTransformMatrix(const WeakPtr<FrameNode>& node, bool isRealTime = false,
        bool isPostEventResult = false, int32_t postEventNodeId = -1);

    // Triggered when the gesture referee finishes collecting gestures and begin a gesture referee.
    void BeginReferee(int32_t touchId, int32_t originalId, bool needUpdateChild = false)
    {
        OnBeginGestureReferee(touchId, originalId, needUpdateChild);
    }

    virtual RefPtr<Gesture> CreateGestureFromRecognizer() const;

    // Triggered when the Gesture referee ends a gesture referee.
    void FinishReferee(int32_t touchId, bool isBlocked = false)
    {
        OnFinishGestureReferee(touchId, isBlocked);
    }

    virtual void AboutToAccept();

    // Called when request of handling gesture sequence is accepted by gesture referee.
    virtual void OnAccepted() = 0;

    // Called when request of handling gesture sequence is rejected by gesture referee.
    virtual void OnRejected() = 0;

    void OnRejectBridgeObj();

    // Called when request of handling gesture sequence is pending by gesture referee.
    virtual void OnPending();
    virtual void OnBlocked();

    // Reconcile the state from the given recognizer into this. The
    // implementation must check that the given recognizer type matches the
    // current one. The return value should be false if the reconciliation fails
    // and true if it succeeds
    virtual bool ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
    {
        return true;
    }

    virtual void SetInnerFlag(bool value) {
        fromCardOrUIExtension_ = value;
    }

    bool GetInnerFlag() {
        return fromCardOrUIExtension_;
    }

    bool DispatchEvent(const TouchEvent& point) override
    {
        return true;
    }
    bool HandleEvent(const TouchEvent& point) override;
    bool HandleEvent(const AxisEvent& event) override;

    void HandleBridgeModeEvent(const TouchEvent& point);
    void HandleEventToBridgeObjList(
        const TouchEvent& point, const std::list<WeakPtr<NGGestureRecognizer>>& bridgeObjList);
    void HandleBridgeModeEvent(const AxisEvent& event);

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

    ACE_FORCE_EXPORT bool SetGestureGroup(const WeakPtr<NGGestureRecognizer>& gestureGroup);

    void SetEventImportGestureGroup(const WeakPtr<NGGestureRecognizer>& gestureGroup);

    void ResetEventImportGestureGroup()
    {
        eventImportGestureGroup_.Reset();
    }

    const WeakPtr<NGGestureRecognizer>& GetGestureGroup() const
    {
        return gestureGroup_;
    }

    void SetOnAction(const GestureEventFunc& onAction)
    {
        onAction_ = std::make_unique<GestureEventFunc>(onAction);
    }

    void SetOnActionStart(const GestureEventFunc& onActionStart)
    {
        onActionStart_ = std::make_unique<GestureEventFunc>(onActionStart);
    }

    void SetOnActionExtUpdate(const GestureEventFunc& onActionExtUpdate)
    {
        onActionExtUpdate_ = std::make_unique<GestureEventFunc>(onActionExtUpdate);
    }

    void SetOnActionUpdate(const GestureEventFunc& onActionUpdate)
    {
        onActionUpdate_ = std::make_unique<GestureEventFunc>(onActionUpdate);
    }

    void SetOnActionEnd(const GestureEventFunc& onActionEnd)
    {
        onActionEnd_ = std::make_unique<GestureEventFunc>(onActionEnd);
    }

    void SetOnActionCancel(const GestureEventFunc& onActionCancel)
    {
        onActionCancel_ = std::make_unique<GestureEventFunc>(onActionCancel);
    }

    void SetOnReject(const GestureEventNoParameter& onReject)
    {
        onReject_ = std::make_unique<GestureEventNoParameter>(onReject);
    }

    inline void SendRejectMsg()
    {
        if (onReject_ && *onReject_) {
            (*onReject_)();
        }
    }

    void SetOnPending(const GestureEventWithRefereeState& onPending)
    {
        onPending_ = std::make_unique<GestureEventWithRefereeState>(onPending);
    }

    inline void SendPendingMsg()
    {
        if (onPending_ && *onPending_) {
            (*onPending_)(refereeState_);
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
    virtual void ResetStatusOnFinish(bool isBlocked = false)
    {
        if (isBlocked && refereeState_ == RefereeState::SUCCEED) {
            OnSucceedCancel();
        }
        lastRefereeState_ = RefereeState::READY;
        refereeState_ = RefereeState::READY;
        disposal_ = GestureDisposal::NONE;
        currentFingers_ = 0;
        SetBridgeMode(false);
        ClearBridgeObjList();
        responseLinkRecognizer_.clear();
        enabled_ = true;
        OnResetStatus();
        ResetEscapeMode();
    }

    // called to reset status manually without rejected callback.
    void ResetStatus()
    {
        lastRefereeState_ = RefereeState::READY;
        refereeState_ = RefereeState::READY;
        OnResetStatus();
        SetBridgeMode(false);
        ClearBridgeObjList();
        responseLinkRecognizer_.clear();
        enabled_ = true;
        ResetEscapeMode();
    }
    virtual bool CheckTouchId(int32_t touchId) = 0;

    virtual std::map<int32_t, TouchEvent> GetTouchPoints() = 0;

    SourceType getDeviceType()
    {
        return deviceType_;
    }

    void SetTransInfo(int id);

    virtual RefPtr<GestureSnapshot> Dump() const override;

    // for recognizer
    void AddGestureProcedure(const std::string& procedure) const;
    // for recognizer group
    void AddGestureProcedure(const TouchEvent& point, const RefPtr<NGGestureRecognizer>& recognizer) const;
    void AddGestureProcedure(const AxisEvent& event, const RefPtr<NGGestureRecognizer>& recognizer) const;

    bool IsSystemGesture() const;

    GestureTypeName GetRecognizerType() const;

    void SetRecognizerType(GestureTypeName trueType);

    virtual void ForceCleanRecognizer() {};

    virtual void ForceCleanRecognizerWithGroup() {
        ForceCleanRecognizer();
    };

    void SetGestureInfo(const RefPtr<GestureInfo>& gestureInfo);

    RefPtr<GestureInfo> GetGestureInfo();

    RefPtr<GestureInfo> GetOrCreateGestureInfo();

    void SetSysGestureJudge(const GestureJudgeFunc& sysJudge)
    {
        sysJudge_ = sysJudge;
    }

    void SetIsSystemGesture(bool isSystemGesture);

    virtual void CleanRecognizerState() {};

    bool AboutToAddCurrentFingers(const TouchEvent& event);

    bool AboutToMinusCurrentFingers(int32_t touchId);

    bool IsInAttachedNode(const TouchEvent& event, bool isRealTime = true);


    void SetUserData(void* userData);

    virtual bool IsReady()
    {
        return refereeState_ == RefereeState::READY;
    }

    void SetDisposeNotifyCallback(std::function<void(void*)>&& callback);

    void SetBridgeMode(bool bridgeMode)
    {
        bridgeMode_ = bridgeMode;
    }

    bool IsBridgeMode() const
    {
        return bridgeMode_;
    }

    void AddBridgeObj(const WeakPtr<NGGestureRecognizer>& bridgeObj)
    {
        bridgeObjList_.emplace_back(bridgeObj);
    }

    std::list<WeakPtr<NGGestureRecognizer>> GetBridgeObj() const
    {
        return bridgeObjList_;
    }

    void ClearBridgeObjList()
    {
        bridgeObjList_.clear();
    }

    void SetEnabled(bool enabled)
    {
        enabled_ = enabled;
    }

    bool IsEnabled() const
    {
        return enabled_;
    }

    RefereeState GetGestureState() const
    {
        return refereeState_;
    }

    void SetResponseLinkRecognizers(const ResponseLinkResult& responseLinkResult);

    bool IsInResponseLinkRecognizers();

    bool IsAllowedType(SourceTool type);

    std::string GetExtraInfo() const
    {
        return extraInfo_;
    }

    WeakPtr<NG::GestureReferee> GetRefereeWithStrategy() const
    {
        return referee_;
    }

    virtual void CleanRecognizerStateVoluntarily() {}

    void ResetStateVoluntarily();

    void SetIsNeedResetRecognizer(bool isNeedResetRecognizerState);

    bool IsNeedResetRecognizerState();

    void CheckPendingRecognizerIsInAttachedNode(const TouchEvent& event);

    void TransformForRecognizer(PointF& localPointF, const WeakPtr<FrameNode>& node, bool isRealTime = false,
        bool isPostEventResult = false, int32_t postEventNodeId = -1);

    void SetPreventBegin(bool preventBegin);

    std::string GetCallbackName(const std::unique_ptr<GestureEventFunc>& callback);

    void ResetResponseLinkRecognizer();

    void LogStateChange(RefereeState oldState, RefereeState newState, StateChangeReason reason);

    CurrentCallbackState GetCurrentCallbackState() const
    {
        return currentCallbackState_;
    }

    virtual void CheckCurrentFingers() const = 0;

    virtual void UpdateGestureReferee(const WeakPtr<NG::GestureReferee>& gestureReferee);

    void NotifyManagerStateChange(RefereeState newState);

    // ===================== Pan-gesture-escape API ============================
    // The "escape" mechanism lets a recognizer that has just won the arena
    // for a finger (typically a multi-selection PanRecognizer) push that
    // finger out of every parallel recognizer (typically a system scroll Pan)
    // *without* rejecting them. Newly-arriving fingers are still routed to
    // those parallel recognizers normally, so the user can scroll with a
    // second finger while the first one keeps driving multi-selection.
    //
    // Subclasses that hold per-finger state (touchPoints_, velocity, ...)
    // should override OnFingerEscaped() to drop that state.
    void SetEscapeMode(const std::unordered_set<int32_t>& existingFingers)
    {
        escapedFingerIds_.insert(existingFingers.begin(), existingFingers.end());
    }

    bool IsFingerEscaped(int32_t fingerId) const
    {
        return escapedFingerIds_.find(fingerId) != escapedFingerIds_.end();
    }

    void ResetEscapeMode()
    {
        escapedFingerIds_.clear();
    }

    // Hook: subclasses with per-finger state must override and clean it up.
    virtual void OnFingerEscaped(int32_t /*fingerId*/) {}

protected:
    void Adjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
    {
        disposal_ = disposal;
        BatchAdjudicate(recognizer, disposal);
    }
    virtual void BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal);

    virtual void OnBeginGestureReferee(int32_t touchId, int32_t originalId, bool needUpdateChild = false) {}
    virtual void OnFinishGestureReferee(int32_t touchId, bool isBlocked = false) {}

    virtual void HandleTouchDownEvent(const TouchEvent& event) = 0;
    virtual void HandleTouchUpEvent(const TouchEvent& event) = 0;
    virtual void HandleTouchMoveEvent(const TouchEvent& event) = 0;
    virtual void HandleTouchCancelEvent(const TouchEvent& event) = 0;
    virtual void HandleReports(const GestureEvent& info, GestureCallbackType type) {};
    virtual void HandleTouchDownEvent(const AxisEvent& event) {}
    virtual void HandleTouchUpEvent(const AxisEvent& event) {}
    virtual void HandleTouchMoveEvent(const AxisEvent& event) {}
    virtual void HandleTouchCancelEvent(const AxisEvent& event) {}

    virtual void OnResetStatus() = 0;

    virtual void OnSucceedCancel() {}
    virtual void RemoveUnsupportEvent(int32_t touchId) {}
    bool ShouldResponse() override;
    bool IsPreventBegin() const;
    bool CheckoutDownFingers(int32_t fingerId) const;

    void HandleWillAccept();
    void HandleDidAccept();

    void ReconcileGestureInfoFrom(const RefPtr<NGGestureRecognizer>& recognizer);
    bool ProcessTouchEvent(const TouchEvent& point);
    void HandleTouchDown(const TouchEvent& point);
    void HandleTouchUp(const TouchEvent& point);
    void HandleTouchCancel(const TouchEvent& point);
    void HandleGestureAccept(const GestureEvent& info, GestureCallbackType type, GestureListenerType listenerType);
    void ReportToGestureDebugManager(GestureCallbackType type, GestureListenerType listenerType);
    void SetGestureEventCurrentLocalLocation(GestureEvent& info, const TouchEvent& touchPoint);
    virtual bool CheckReconcileFromProperties(const RefPtr<NGGestureRecognizer>& recognizer)
    {
        return false;
    }
    virtual std::string GetGestureInfoString() const;

    RefereeState refereeState_ = RefereeState::READY;

    RefereeState lastRefereeState_ = RefereeState::READY;

    GestureDisposal disposal_ = GestureDisposal::NONE;

    GesturePriority priority_ = GesturePriority::Low;

    GestureMask priorityMask_ = GestureMask::Normal;

    CurrentCallbackState currentCallbackState_ = CurrentCallbackState::READY;

    bool isExternalGesture_ = false;
    bool fromCardOrUIExtension_ = false;
    std::unique_ptr<GestureEventFunc> onAction_;
    std::unique_ptr<GestureEventFunc> onActionStart_;
    std::unique_ptr<GestureEventFunc> onActionUpdate_;
    std::unique_ptr<GestureEventFunc> onActionExtUpdate_;
    std::unique_ptr<GestureEventFunc> onActionEnd_;
    std::unique_ptr<GestureEventFunc> onActionCancel_;
    // triggered when the recongnizer is rejected
    std::unique_ptr<GestureEventNoParameter> onReject_;
    std::unique_ptr<GestureEventWithRefereeState> onPending_;

    int64_t deviceId_ = 0;
    SourceType deviceType_ = SourceType::NONE;
    SourceTool deviceTool_ = SourceTool::UNKNOWN;
    InputEventType inputEventType_ = InputEventType::TOUCH_SCREEN;
    int32_t transId_ = 0;

    int32_t currentFingers_ = 0;
    std::set<int32_t> fingersId_;
    RefPtr<GestureInfo> gestureInfo_;
    GestureJudgeFunc sysJudge_ = nullptr;
    bool isTouchEventFinished_ = false;
    bool bridgeMode_ = false;
    std::list<WeakPtr<NGGestureRecognizer>> bridgeObjList_;
    bool enabled_ = true;
    ResponseLinkResult responseLinkRecognizer_;
    std::string extraInfo_;
    // This flag is set when the current recognition of the recognizer ends. Used when all fingers on the recognizer are
    // raised.
    bool isNeedResetVoluntarily_ = false;
    bool isNeedResetRecognizerState_ = false;
    std::vector<Matrix4> localMatrix_ = {};
    bool preventBegin_ = false;
    WeakPtr<NG::GestureReferee> referee_;

    std::unordered_set<int32_t> escapedFingerIds_;
private:
    WeakPtr<NGGestureRecognizer> gestureGroup_;
    WeakPtr<NGGestureRecognizer> eventImportGestureGroup_;
    GestureActionPhase GetActionPhase(GestureCallbackType callbackType, GestureListenerType listenerType) const;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_GESTURE_RECOGNIZER_H
