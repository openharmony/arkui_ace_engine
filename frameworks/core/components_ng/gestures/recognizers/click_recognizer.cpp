/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/gestures/recognizers/click_recognizer.h"

#include "base/ressched/ressched_report.h"
#include "core/common/recorder/event_definition.h"
#include "core/common/recorder/event_recorder.h"

namespace OHOS::Ace::NG {
namespace {

int32_t MULTI_FINGER_TIMEOUT = 300;
constexpr int32_t MULTI_FINGER_TIMEOUT_TOUCH = 300;
constexpr int32_t MULTI_FINGER_TIMEOUT_MOUSE = 300;
int32_t MULTI_TAP_TIMEOUT = 300;
constexpr int32_t MULTI_TAP_TIMEOUT_TOUCH = 300;
constexpr int32_t MULTI_TAP_TIMEOUT_MOUSE = 300;
constexpr int32_t MAX_THRESHOLD_MANYTAP = 60;
constexpr int32_t MAX_TAP_FINGERS = 10;
constexpr double MAX_THRESHOLD = 20.0;
constexpr int32_t DEFAULT_TAP_FINGERS = 1;
constexpr int32_t DEFAULT_LONGPRESS_DURATION = 800000000;

} // namespace

void ClickRecognizer::ForceCleanRecognizer()
{
    MultiFingersRecognizer::ForceCleanRecognizer();
    tappedCount_ = 0;
    equalsToFingers_ = false;
    focusPoint_ = {};
    fingerDeadlineTimer_.Cancel();
    tapDeadlineTimer_.Cancel();
    currentTouchPointsNum_ = 0;
    responseRegionBuffer_.clear();
    paintRect_ = RectF();
}

bool ClickRecognizer::IsPointInRegion(const TouchEvent& event)
{
    if (distanceThreshold_ < std::numeric_limits<double>::infinity()) {
        Offset offset = event.GetScreenOffset() - touchPoints_[event.id].GetScreenOffset();
        if (offset.GetDistance() > distanceThreshold_) {
            TAG_LOGI(AceLogTag::ACE_GESTURE, "Click move distance is larger than distanceThreshold_, "
            "distanceThreshold_ is %{public}f", distanceThreshold_);
            extraInfo_ += "move distance out of distanceThreshold.";
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
            return false;
        } else {
            return true;
        }
    }
    PointF localPoint(event.x, event.y);
    auto frameNode = GetAttachedNode();
    if (!frameNode.Invalid()) {
        auto host = frameNode.Upgrade();
        CHECK_NULL_RETURN(host, false);
        NGGestureRecognizer::Transform(localPoint, frameNode, false, isPostEventResult_, event.postEventNodeId);
        localPoint = localPoint + paintRect_.GetOffset();
        if (!host->InResponseRegionList(localPoint, responseRegionBuffer_)) {
            TAG_LOGI(AceLogTag::ACE_GESTURE,
                "InputTracking id:%{public}d, this MOVE/UP event is out of region, try to reject click gesture",
                event.touchEventId);
            extraInfo_ += "move/up event out of region.";
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
            return false;
        }
    }
    return true;
}

ClickRecognizer::ClickRecognizer(int32_t fingers, int32_t count, double distanceThreshold, bool isLimitFingerCount)
    : MultiFingersRecognizer(fingers, isLimitFingerCount), count_(count), distanceThreshold_(distanceThreshold)
{
    if (fingers_ > MAX_TAP_FINGERS || fingers_ < DEFAULT_TAP_FINGERS) {
        fingers_ = DEFAULT_TAP_FINGERS;
    }
    if (distanceThreshold_ <= 0) {
        distanceThreshold_ = std::numeric_limits<double>::infinity();
    }
    
    SetOnAccessibility(GetOnAccessibilityEventFunc());
}

void ClickRecognizer::InitGlobalValue(SourceType sourceType)
{
    switch (sourceType) {
        case SourceType::TOUCH:
            MULTI_FINGER_TIMEOUT = MULTI_FINGER_TIMEOUT_TOUCH;
            MULTI_TAP_TIMEOUT = MULTI_TAP_TIMEOUT_TOUCH;
            break;
        case SourceType::MOUSE:
        case SourceType::TOUCH_PAD:
            MULTI_FINGER_TIMEOUT = MULTI_FINGER_TIMEOUT_MOUSE;
            MULTI_TAP_TIMEOUT = MULTI_TAP_TIMEOUT_MOUSE;
            break;
        default:
            break;
    }
}

ClickInfo ClickRecognizer::GetClickInfo()
{
    TouchEvent touchPoint = {};
    if (!touchPoints_.empty()) {
        touchPoint = touchPoints_.begin()->second;
    }
    ClickInfo info(touchPoint.id);
    PointF localPoint(touchPoint.GetOffset().GetX(), touchPoint.GetOffset().GetY());
    NGGestureRecognizer::Transform(localPoint, GetAttachedNode(), false,
        isPostEventResult_, touchPoint.postEventNodeId);
    Offset localOffset(localPoint.GetX(), localPoint.GetY());
    info.SetTimeStamp(touchPoint.time);
    info.SetScreenLocation(touchPoint.GetScreenOffset());
    info.SetGlobalLocation(touchPoint.GetOffset()).SetLocalLocation(localOffset);
    info.SetSourceDevice(deviceType_);
    info.SetDeviceId(deviceId_);
    info.SetTarget(GetEventTarget().value_or(EventTarget()));
    info.SetForce(touchPoint.force);
    auto frameNode = GetAttachedNode().Upgrade();
    std::string patternName = "";
    if (frameNode) {
        patternName = frameNode->GetTag();
    }
    info.SetPatternName(patternName.c_str());
    if (touchPoint.tiltX.has_value()) {
        info.SetTiltX(touchPoint.tiltX.value());
    }
    if (touchPoint.tiltY.has_value()) {
        info.SetTiltY(touchPoint.tiltY.value());
    }
    if (touchPoint.rollAngle.has_value()) {
        info.SetRollAngle(touchPoint.rollAngle.value());
    }
    info.SetSourceTool(touchPoint.sourceTool);
    return info;
}

void ClickRecognizer::OnAccepted()
{
    int64_t acceptTime = GetSysTimestamp();
    int64_t inputTime = acceptTime;
    if (firstInputTime_.has_value()) {
        inputTime = static_cast<int64_t>(firstInputTime_.value().time_since_epoch().count());
    }
    if (SystemProperties::GetTraceInputEventEnabled()) {
        ACE_SCOPED_TRACE("UserEvent InputTime:%lld AcceptTime:%lld InputType:ClickGesture",
            static_cast<long long>(inputTime), static_cast<long long>(acceptTime));
    }
    firstInputTime_.reset();

    auto node = GetAttachedNode().Upgrade();
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "Click accepted, tag: %{public}s",
        node ? node->GetTag().c_str() : "null");
    auto lastRefereeState = refereeState_;
    refereeState_ = RefereeState::SUCCEED;
    ResSchedReport::GetInstance().ResSchedDataReport("click");
    if (backupTouchPointsForSucceedBlock_.has_value()) {
        touchPoints_ = backupTouchPointsForSucceedBlock_.value();
        backupTouchPointsForSucceedBlock_.reset();
    }
    TouchEvent touchPoint = {};
    if (!touchPoints_.empty()) {
        touchPoint = touchPoints_.begin()->second;
    }
    PointF localPoint(touchPoint.GetOffset().GetX(), touchPoint.GetOffset().GetY());
    NGGestureRecognizer::Transform(localPoint, GetAttachedNode(), false,
        isPostEventResult_, touchPoint.postEventNodeId);
    Offset localOffset(localPoint.GetX(), localPoint.GetY());
    if (onClick_) {
        ClickInfo info = GetClickInfo();
        onClick_(info);
    }

    if (remoteMessage_) {
        ClickInfo info = GetClickInfo();
        info.SetTimeStamp(touchPoint.time);
        info.SetGlobalLocation(touchPoint.GetOffset()).SetLocalLocation(localOffset);
        remoteMessage_(info);
    }
    UpdateFingerListInfo();
    SendCallbackMsg(onAction_);

    int64_t overTime = GetSysTimestamp();
    if (SystemProperties::GetTraceInputEventEnabled()) {
        ACE_SCOPED_TRACE("UserEvent InputTime:%lld OverTime:%lld InputType:ClickGesture",
            static_cast<long long>(inputTime), static_cast<long long>(overTime));
    }
    firstInputTime_.reset();

    // already send Event in onClick
    if (onAccessibilityEventFunc_ && !onClick_) {
        onAccessibilityEventFunc_(AccessibilityEventType::CLICK);
    }
    if (lastRefereeState != RefereeState::SUCCEED_BLOCKED) {
        ResetStateVoluntarily();
    }
}

void ClickRecognizer::OnRejected()
{
    SendRejectMsg();
    refereeState_ = RefereeState::FAIL;
    firstInputTime_.reset();
    backupTouchPointsForSucceedBlock_.reset();
}

void ClickRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    extraInfo_ = "ETF: " + std::to_string(equalsToFingers_) + " CFP: " + std::to_string(currentTouchPointsNum_);
    if (!firstInputTime_.has_value()) {
        firstInputTime_ = event.time;
    }

    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    if (pipeline && pipeline->IsFormRenderExceptDynamicComponent()) {
        touchDownTime_ = event.time;
    }
    if (IsRefereeFinished()) {
        auto node = GetAttachedNode().Upgrade();
        TAG_LOGI(AceLogTag::ACE_GESTURE,
            "Click recognizer handle touch down event refereeState is %{public}d, node tag = %{public}s, id = "
            SEC_PLD(%{public}s) ".",
            refereeState_, node ? node->GetTag().c_str() : "null",
            SEC_PARAM(node ? std::to_string(node->GetId()).c_str() : "invalid"));
        return;
    }
    InitGlobalValue(event.sourceType);
    UpdateInfoWithDownEvent(event);
}

void ClickRecognizer::UpdateInfoWithDownEvent(const TouchEvent& event)
{
    // The last recognition sequence has been completed, reset the timer.
    if (tappedCount_ > 0 && currentTouchPointsNum_ == 0) {
        responseRegionBuffer_.clear();
        paintRect_ = RectF();
        tapDeadlineTimer_.Cancel();
    }
    if (currentTouchPointsNum_ == 0) {
        auto frameNode = GetAttachedNode();
        if (!frameNode.Invalid()) {
            auto host = frameNode.Upgrade();
            responseRegionBuffer_ = host->GetResponseRegionListForRecognizer(static_cast<int32_t>(event.sourceType));
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            paintRect_ = renderContext->GetPaintRectWithoutTransform();
        }
    }
    if (fingersId_.find(event.id) == fingersId_.end()) {
        fingersId_.insert(event.id);
        ++currentTouchPointsNum_;
        touchPoints_[event.id] = event;
    }
    UpdateFingerListInfo();
    if (fingers_ > currentTouchPointsNum_) {
        // waiting for multi-finger press
        DeadlineTimer(fingerDeadlineTimer_, MULTI_FINGER_TIMEOUT);
    } else {
        // Turn off the multi-finger press deadline timer
        fingerDeadlineTimer_.Cancel();
        equalsToFingers_ = true;
        if (ExceedSlop()) {
            TAG_LOGW(AceLogTag::ACE_GESTURE, "Fail to detect multi finger tap due to offset is out of slop");
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
    }
    if (currentTouchPointsNum_ == fingers_) {
        focusPoint_ = ComputeFocusPoint();
    }
}

bool ClickRecognizer::IsFormRenderClickRejected(const TouchEvent& event)
{
    Offset offset = event.GetScreenOffset() - touchPoints_[event.id].GetScreenOffset();
    if (event.time.time_since_epoch().count() - touchDownTime_.time_since_epoch().count() >
        DEFAULT_LONGPRESS_DURATION || offset.GetDistance() > MAX_THRESHOLD) {
        TAG_LOGI(AceLogTag::ACE_GESTURE, "reject click when up, offset is %{public}f",
            static_cast<float>(offset.GetDistance()));
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return true;
    }
    return false;
}

void ClickRecognizer::TriggerClickAccepted(const TouchEvent& event)
{
    TAG_LOGI(AceLogTag::ACE_GESTURE, "Click try accept");
    time_ = event.time;
    if (!useCatchMode_) {
        OnAccepted();
        return;
    }
    auto onGestureJudgeBeginResult = TriggerGestureJudgeCallback();
    if (onGestureJudgeBeginResult == GestureJudgeResult::REJECT) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        TAG_LOGI(AceLogTag::ACE_GESTURE, "Click gesture judge reject");
        return;
    }
    if (CheckLimitFinger()) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }
    Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
}

void ClickRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    if (fingersId_.find(event.id) != fingersId_.end()) {
        fingersId_.erase(event.id);
        --currentTouchPointsNum_;
    }
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    // In a card scenario, determine the interval between finger pressing and finger lifting. Delete this section of
    // logic when the formal scenario is complete.
    if (pipeline && pipeline->IsFormRenderExceptDynamicComponent() && IsFormRenderClickRejected(event)) {
        return;
    }
    if (IsRefereeFinished()) {
        return;
    }
    InitGlobalValue(event.sourceType);
    touchPoints_[event.id] = event;
    UpdateFingerListInfo();
    auto isUpInRegion = IsPointInRegion(event);
    if (currentTouchPointsNum_ == 0) {
        responseRegionBuffer_.clear();
        paintRect_ = RectF();
    }
    bool fingersNumberSatisfied = equalsToFingers_;
    // Check whether multi-finger taps are completed in count_ times
    if (equalsToFingers_ && (currentTouchPointsNum_ == 0) && isUpInRegion) {
        // Turn off the multi-finger lift deadline timer
        fingerDeadlineTimer_.Cancel();
        tappedCount_++;
        if (CheckLimitFinger()) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
        if (tappedCount_ == count_) {
            TriggerClickAccepted(event);
            return;
        }
        equalsToFingers_ = false;
        // waiting for multi-finger lift
        DeadlineTimer(tapDeadlineTimer_, MULTI_TAP_TIMEOUT);
    }
    if (refereeState_ != RefereeState::PENDING && refereeState_ != RefereeState::FAIL) {
        if (fingersNumberSatisfied) {
            Adjudicate(AceType::Claim(this), GestureDisposal::PENDING);
            AboutToAddToPendingRecognizers(event);
        } else {
            extraInfo_ += "finger number not satisfied.";
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
    }
    if (currentTouchPointsNum_ < fingers_ && equalsToFingers_) {
        DeadlineTimer(fingerDeadlineTimer_, MULTI_FINGER_TIMEOUT);
    }
}

void ClickRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    if (currentFingers_ < fingers_) {
        return;
    }
    if (IsRefereeFinished()) {
        return;
    }
    InitGlobalValue(event.sourceType);
    // In form scenario, if move more than 20vp, reject click gesture.
    // Remove form scenario when formal solution is completed.
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    if (pipeline && pipeline->IsFormRenderExceptDynamicComponent()) {
        Offset offset = event.GetScreenOffset() - touchPoints_[event.id].GetScreenOffset();
        if (offset.GetDistance() > MAX_THRESHOLD) {
            TAG_LOGI(AceLogTag::ACE_GESTURE, "This gesture is out of offset, try to reject it");
            extraInfo_ += "offset is out of region.";
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
    }
    IsPointInRegion(event);
    UpdateFingerListInfo();
}

void ClickRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    extraInfo_ += "receive cancel event.";
    if (IsRefereeFinished()) {
        return;
    }
    InitGlobalValue(event.sourceType);
    Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
}

void ClickRecognizer::HandleOverdueDeadline()
{
    if (currentTouchPointsNum_ < fingers_ || tappedCount_ < count_) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
    }
}

void ClickRecognizer::DeadlineTimer(CancelableCallback<void()>& deadlineTimer, int32_t time)
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);

    auto&& callback = [weakPtr = AceType::WeakClaim(this)]() {
        auto refPtr = weakPtr.Upgrade();
        if (refPtr) {
            refPtr->HandleOverdueDeadline();
        }
    };

    deadlineTimer.Reset(callback);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    taskExecutor.PostDelayedTask(deadlineTimer, time, "ArkUIGestureClickDeadlineTimer");
}

Offset ClickRecognizer::ComputeFocusPoint()
{
    Offset sumOfPoints;
    int32_t count = 0;
    for (auto& element : touchPoints_) {
        if (count >= fingers_) {
            break;
        }
        sumOfPoints = sumOfPoints + element.second.GetOffset();
        count++;
    }
    Offset focusPoint = sumOfPoints / count;
    return focusPoint;
}

bool ClickRecognizer::ExceedSlop()
{
    if (tappedCount_ > 0 && tappedCount_ < count_) {
        Offset currentFocusPoint = ComputeFocusPoint();
        Offset slop = currentFocusPoint - focusPoint_;
        if (GreatOrEqual(PipelineBase::Px2VpWithCurrentDensity(slop.GetDistance()), MAX_THRESHOLD_MANYTAP)) {
            return true;
        }
    }
    return false;
}

GestureEvent ClickRecognizer::GetGestureEventInfo()
{
    GestureEvent info;
    info.SetTimeStamp(time_);
    info.SetFingerList(fingerList_);
    TouchEvent touchPoint = {};
    for (const auto& pointKeyVal : touchPoints_) {
        auto pointVal = pointKeyVal.second;
        if (pointVal.sourceType != SourceType::NONE) {
            touchPoint = pointVal;
            break;
        }
    }
    PointF localPoint(touchPoint.GetOffset().GetX(), touchPoint.GetOffset().GetY());
    NGGestureRecognizer::Transform(localPoint, GetAttachedNode(), false,
        isPostEventResult_, touchPoint.postEventNodeId);
    info.SetTimeStamp(touchPoint.time);
    info.SetScreenLocation(touchPoint.GetScreenOffset());
    info.SetGlobalLocation(touchPoint.GetOffset()).SetLocalLocation(Offset(localPoint.GetX(), localPoint.GetY()));
    info.SetSourceDevice(deviceType_);
    info.SetDeviceId(deviceId_);
    info.SetTarget(GetEventTarget().value_or(EventTarget()));
    info.SetForce(touchPoint.force);
    auto frameNode = GetAttachedNode().Upgrade();
    std::string patternName = "";
    if (frameNode) {
        patternName = frameNode->GetTag();
    }
    info.SetPatternName(patternName.c_str());
    
    if (touchPoint.tiltX.has_value()) {
        info.SetTiltX(touchPoint.tiltX.value());
    }
    if (touchPoint.tiltY.has_value()) {
        info.SetTiltY(touchPoint.tiltY.value());
    }
    if (touchPoint.rollAngle.has_value()) {
        info.SetRollAngle(touchPoint.rollAngle.value());
    }
    info.SetSourceTool(touchPoint.sourceTool);
#ifdef SECURITY_COMPONENT_ENABLE
    info.SetDisplayX(touchPoint.screenX);
    info.SetDisplayY(touchPoint.screenY);
#endif
    info.SetPointerEvent(lastPointEvent_);
    info.SetPressedKeyCodes(touchPoint.pressedKeyCodes_);
    info.SetInputEventType(inputEventType_);
    return info;
}

void ClickRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& onAction)
{
    if (gestureInfo_ && gestureInfo_->GetDisposeTag()) {
        return;
    }
    if (onAction && *onAction) {
        GestureEvent info = GetGestureEventInfo();
        // onAction may be overwritten in its invoke so we copy it first
        auto onActionFunction = *onAction;
        onActionFunction(info);
        RecordClickEventIfNeed(info);
    }
}

void ClickRecognizer::RecordClickEventIfNeed(const GestureEvent& info) const
{
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        auto host = GetAttachedNode().Upgrade();
        CHECK_NULL_VOID(host);
        auto accessibilityProperty = host->GetAccessibilityProperty<NG::AccessibilityProperty>();
        CHECK_NULL_VOID(accessibilityProperty);
        Recorder::EventParamsBuilder builder;
        builder.SetEventType(Recorder::EventType::CLICK)
            .SetId(host->GetInspectorId().value_or(""))
            .SetType(host->GetTag())
            .SetText(accessibilityProperty->GetGroupText(true))
            .SetDescription(host->GetAutoEventParamValue(""))
            .SetHost(host);
        auto pointSwitch = Recorder::EventRecorder::Get().IsRecordEnable(Recorder::EventCategory::CATEGORY_POINT);
        if (pointSwitch) {
            static const int32_t precision = 2;
            std::stringstream ss;
            ss << std::fixed << std::setprecision(precision) << info.GetGlobalPoint().GetX() << ","
               << info.GetGlobalPoint().GetY();
            builder.SetExtra(Recorder::KEY_POINT, ss.str());
        }
        Recorder::EventRecorder::Get().OnClick(std::move(builder));
    }
}

GestureJudgeResult ClickRecognizer::TriggerGestureJudgeCallback()
{
    auto targetComponent = GetTargetComponent();
    CHECK_NULL_RETURN(targetComponent, GestureJudgeResult::CONTINUE);
    auto gestureRecognizerJudgeFunc = targetComponent->GetOnGestureRecognizerJudgeBegin();
    auto callback = targetComponent->GetOnGestureJudgeBeginCallback();
    if (!callback && !sysJudge_ && !gestureRecognizerJudgeFunc) {
        return GestureJudgeResult::CONTINUE;
    }
    auto info = std::make_shared<TapGestureEvent>();
    info->SetTimeStamp(time_);
    info->SetDeviceId(deviceId_);
    info->SetFingerList(fingerList_);
    TouchEvent touchPoint = {};
    if (!touchPoints_.empty()) {
        touchPoint = touchPoints_.begin()->second;
    }
    info->SetSourceDevice(deviceType_);
    info->SetTarget(GetEventTarget().value_or(EventTarget()));
    info->SetForce(touchPoint.force);
    if (gestureInfo_) {
        gestureInfo_->SetInputEventType(inputEventType_);
    }
    if (touchPoint.tiltX.has_value()) {
        info->SetTiltX(touchPoint.tiltX.value());
    }
    if (touchPoint.tiltY.has_value()) {
        info->SetTiltY(touchPoint.tiltY.value());
    }
    if (touchPoint.rollAngle.has_value()) {
        info->SetRollAngle(touchPoint.rollAngle.value());
    }
    info->SetSourceTool(touchPoint.sourceTool);
    if (sysJudge_) {
        return sysJudge_(gestureInfo_, info);
    }
    if (gestureRecognizerJudgeFunc) {
        return gestureRecognizerJudgeFunc(info, Claim(this), responseLinkRecognizer_);
    }
    return callback(gestureInfo_, info);
}

bool ClickRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    RefPtr<ClickRecognizer> curr = AceType::DynamicCast<ClickRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (curr->count_ != count_ || curr->fingers_ != fingers_ || curr->priorityMask_ != priorityMask_ ||
        curr->distanceThreshold_ != distanceThreshold_) {
        ResetStatus();
        return false;
    }

    onAction_ = std::move(curr->onAction_);
    ReconcileGestureInfoFrom(recognizer);
    return true;
}

RefPtr<GestureSnapshot> ClickRecognizer::Dump() const
{
    RefPtr<GestureSnapshot> info = NGGestureRecognizer::Dump();
    std::stringstream oss;
    oss << "count: " << count_ << ", "
        << "fingers: " << fingers_ << ", "
        << DumpGestureInfo();
    info->customInfo = oss.str();
    return info;
}

RefPtr<Gesture> ClickRecognizer::CreateGestureFromRecognizer() const
{
    return AceType::MakeRefPtr<TapGesture>(count_, fingers_, distanceThreshold_, isLimitFingerCount_);
}

void ClickRecognizer::CleanRecognizerState()
{
    if ((refereeState_ == RefereeState::SUCCEED ||
        refereeState_ == RefereeState::FAIL ||
        refereeState_ == RefereeState::DETECTING) &&
        currentFingers_ == 0) {
        tappedCount_ = 0;
        refereeState_ = RefereeState::READY;
        disposal_ = GestureDisposal::NONE;
    }
}

OnAccessibilityEventFunc ClickRecognizer::GetOnAccessibilityEventFunc()
{
    auto callback = [weak = WeakClaim(this)](AccessibilityEventType eventType) {
        auto recognizer = weak.Upgrade();
        CHECK_NULL_VOID(recognizer);
        auto node = recognizer->GetAttachedNode().Upgrade();
        CHECK_NULL_VOID(node);
        node->OnAccessibilityEvent(eventType);
    };
    return callback;
}

void ClickRecognizer::AboutToAddToPendingRecognizers(const TouchEvent& event)
{
    if (event.sourceType == SourceType::MOUSE &&
        (refereeState_ == RefereeState::PENDING || refereeState_ == RefereeState::PENDING_BLOCKED)) {
        auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto eventManager = pipeline->GetEventManager();
        CHECK_NULL_VOID(eventManager);
        eventManager->AddToMousePendingRecognizers(AceType::WeakClaim(this));
    }
}
} // namespace OHOS::Ace::NG
