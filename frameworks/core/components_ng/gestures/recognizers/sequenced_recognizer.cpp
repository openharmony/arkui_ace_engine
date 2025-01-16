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

#include "core/components_ng/gestures/recognizers/sequenced_recognizer.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t SEQUENCE_GESTURE_TIMEOUT = 300;
} // namespace

void SequencedRecognizer::OnAccepted()
{
    refereeState_ = RefereeState::SUCCEED;

    auto iter = recognizers_.begin();
    std::advance(iter, currentIndex_);
    if (iter != recognizers_.end()) {
        auto activeRecognizer = *iter;
        if (activeRecognizer) {
            activeRecognizer->AboutToAccept();
            UpdateCurrentIndex();
        }
    }
}

void SequencedRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback)
{
    if (callback && *callback) {
        GestureEvent info;
        (*callback)(info);
    }
}

void SequencedRecognizer::OnRejected()
{
    refereeState_ = RefereeState::FAIL;

    auto iter = recognizers_.begin();
    std::advance(iter, currentIndex_);

    while (iter != recognizers_.end()) {
        auto recognizer = *iter;
        if (recognizer) {
            if (recognizer->IsBridgeMode()) {
                continue;
            }
            recognizer->OnRejected();
            recognizer->OnRejectBridgeObj();
        }
        ++iter;
    }

    if (currentIndex_ != -1) {
        SendCallbackMsg(onActionCancel_);
    }
}

void SequencedRecognizer::OnPending()
{
    refereeState_ = RefereeState::PENDING;
    auto iter = recognizers_.begin();
    std::advance(iter, currentIndex_);
    if (iter != recognizers_.end()) {
        auto activeRecognizer = *iter;
        CHECK_NULL_VOID(activeRecognizer);
        if (activeRecognizer->GetGestureDisposal() == GestureDisposal::ACCEPT) {
            activeRecognizer->AboutToAccept();
            UpdateCurrentIndex();
        }
        if (activeRecognizer->GetGestureDisposal() == GestureDisposal::PENDING) {
            activeRecognizer->OnPending();
        }
    }
}

void SequencedRecognizer::OnBlocked()
{
    RefPtr<NGGestureRecognizer> activeRecognizer;
    auto iter = recognizers_.begin();
    std::advance(iter, currentIndex_);
    if (iter != recognizers_.end()) {
        activeRecognizer = *iter;
    }
    if (disposal_ == GestureDisposal::ACCEPT) {
        refereeState_ = RefereeState::SUCCEED_BLOCKED;
        if (activeRecognizer) {
            activeRecognizer->OnBlocked();
        }
        return;
    }
    if (disposal_ == GestureDisposal::PENDING) {
        refereeState_ = RefereeState::PENDING_BLOCKED;
        if (activeRecognizer) {
            activeRecognizer->OnBlocked();
        }
    }
}

RefPtr<NGGestureRecognizer> SequencedRecognizer::GetCurrentRecognizer()
{
    auto iter = recognizers_.begin();
    std::advance(iter, currentIndex_);
    RefPtr<NGGestureRecognizer> curRecognizer = *iter;
    return curRecognizer;
}

bool SequencedRecognizer::CheckGroupState()
{
    if (currentIndex_ < 0 || refereeState_ != RefereeState::PENDING) {
        return false;
    }
    auto curRecognizer = GetCurrentRecognizer();
    if (!AceType::InstanceOf<RecognizerGroup>(curRecognizer)) {
        return curRecognizer->GetRefereeState() != RefereeState::SUCCEED_BLOCKED &&
               curRecognizer->GetRefereeState() != RefereeState::SUCCEED &&
               curRecognizer->GetRefereeState() != RefereeState::FAIL;
    }
    auto group = AceType::DynamicCast<RecognizerGroup>(curRecognizer);
    return group && group->CheckGroupState();
}

RefereeState SequencedRecognizer::CheckStates(size_t touchId)
{
    int count = 0;
    if (currentIndex_ < 0 || refereeState_ != RefereeState::PENDING) {
        return RefereeState::READY;
    }
    auto curRecognizer = GetCurrentRecognizer();
    if (!AceType::InstanceOf<RecognizerGroup>(curRecognizer)) {
        if (curRecognizer->GetRefereeState() != RefereeState::SUCCEED_BLOCKED &&
            curRecognizer->GetRefereeState() != RefereeState::SUCCEED &&
            curRecognizer->GetRefereeState() != RefereeState::FAIL) {
            count++;
        }
    } else {
        auto group = AceType::DynamicCast<RecognizerGroup>(curRecognizer);
        if (group) {
            auto state = group->CheckStates(touchId);
            if (state == RefereeState::PENDING) {
                count++;
            }
        }
    }
    if (count > 0) {
        return RefereeState::PENDING;
    } else {
        return RefereeState::READY;
    }
}

bool SequencedRecognizer::NeedStartDeadlineTimerInner(
    const RefPtr<NGGestureRecognizer> curRecognizer, SourceTool sourceTool)
{
    if (currentIndex_ <= 0) {
        return curRecognizer->IsAllowedType(sourceTool);
    }
    auto iter = recognizers_.begin();
    std::advance(iter, currentIndex_ - 1);
    RefPtr<NGGestureRecognizer> lastRecognizer = *iter;
    return (lastRecognizer->GetRefereeState() == RefereeState::SUCCEED && lastRecognizer->IsAllowedType(sourceTool)) ||
           curRecognizer->IsAllowedType(sourceTool);
}

bool SequencedRecognizer::HandleEvent(const TouchEvent& point)
{
    if (point.type == TouchType::DOWN || point.type == TouchType::UP) {
        inputEventType_ = point.sourceType == SourceType::TOUCH ? InputEventType::TOUCH_SCREEN :
            InputEventType::MOUSE_BUTTON;
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, sequenced %{public}d type: %{public}d",
            point.touchEventId, point.id, static_cast<int32_t>(point.type));
    }
    auto iter = recognizers_.begin();
    std::advance(iter, currentIndex_);
    RefPtr<NGGestureRecognizer> curRecognizer = *iter;
    if (!curRecognizer) {
        if (point.type == TouchType::DOWN) {
            TAG_LOGI(AceLogTag::ACE_GESTURE, "SequencedRecognizer curRecognizer is invalid");
        }
        GroupAdjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return true;
    }
    if (point.type == TouchType::DOWN && !point.childTouchTestList.empty()) {
        childTouchTestList_ = point.childTouchTestList;
    }
    touchPoints_[point.id] = point;
    // the prevState is ready, need to pase down event to the new coming recognizer.
    if (currentIndex_ > 0 && curRecognizer->GetRefereeState() == RefereeState::READY) {
        if (inputEventType_ != InputEventType::MOUSE_BUTTON || !CheckBetweenTwoLongPressRecognizer(currentIndex_)) {
            SendTouchEventToNextRecognizer(curRecognizer);
        }
    }
    switch (point.type) {
        case TouchType::DOWN:
            if (touchPoints_.size() == 1 && curRecognizer->IsAllowedType(point.sourceTool)) {
                deadlineTimer_.Cancel();
            }
            [[fallthrough]];
        case TouchType::MOVE:
        case TouchType::UP:
        case TouchType::CANCEL:
            curRecognizer->HandleEvent(point);
            AddGestureProcedure(point, curRecognizer);
            break;
        default:
            break;
    }

    if ((point.type == TouchType::UP) && (refereeState_ == RefereeState::PENDING) &&
        NeedStartDeadlineTimerInner(curRecognizer, point.sourceTool)) {
        DeadlineTimer();
    }
    return true;
}

bool SequencedRecognizer::HandleEvent(const AxisEvent& point)
{
    if (point.action == AxisAction::BEGIN) {
        inputEventType_ = InputEventType::AXIS;
    }
    auto iter = recognizers_.begin();
    std::advance(iter, currentIndex_);
    RefPtr<NGGestureRecognizer> curRecognizer = *iter;
    if (!curRecognizer) {
        GroupAdjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return true;
    }
    lastAxisEvent_ = point;
    if (currentIndex_ > 0) {
        auto prevState = curRecognizer->GetRefereeState();
        if (prevState == RefereeState::READY) {
            // the prevState is ready, need to pass axis-begin event to the new coming recognizer.
            SendTouchEventToNextRecognizer(curRecognizer);
        }
    }
    if (point.action != AxisAction::NONE) {
        curRecognizer->HandleEvent(point);
    }

    if ((point.action == AxisAction::END) && (refereeState_ == RefereeState::PENDING) &&
        NeedStartDeadlineTimerInner(curRecognizer, point.sourceTool)) {
        DeadlineTimer();
    }
    return true;
}

void SequencedRecognizer::BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
{
    if (disposal == GestureDisposal::ACCEPT) {
        if (recognizer->GetRefereeState() == RefereeState::SUCCEED) {
            return;
        }
        if (currentIndex_ == static_cast<int32_t>((recognizers_.size() - 1))) {
            GroupAdjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        } else {
            if (refereeState_ == RefereeState::PENDING) {
                UpdateCurrentIndex();
                recognizer->AboutToAccept();
            } else {
                GroupAdjudicate(AceType::Claim(this), GestureDisposal::PENDING);
            }
        }
        return;
    }
    if (disposal == GestureDisposal::REJECT) {
        if (recognizer->GetRefereeState() == RefereeState::FAIL) {
            return;
        }
        if (refereeState_ == RefereeState::FAIL) {
            recognizer->OnRejected();
        } else {
            GroupAdjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
        return;
    }

    if (recognizer->GetRefereeState() == RefereeState::PENDING) {
        return;
    }

    if (refereeState_ == RefereeState::PENDING) {
        recognizer->OnPending();
    } else {
        GroupAdjudicate(AceType::Claim(this), GestureDisposal::PENDING);
    }
}

void SequencedRecognizer::UpdateCurrentIndex()
{
    if (currentIndex_ == static_cast<int32_t>((recognizers_.size() - 1))) {
        // the last one.
        return;
    }
    currentIndex_++;
    // if the sequence recognizer between long press recognizer, auto send to next event.
    if (isEventHandoverNeeded_ ||
        (inputEventType_ == InputEventType::MOUSE_BUTTON && CheckBetweenTwoLongPressRecognizer(currentIndex_))) {
        auto duration = 0;
        auto iter = recognizers_.begin();
        std::advance(iter, currentIndex_ - 1);
        RefPtr<NGGestureRecognizer> curRecognizer = *iter;
        RefPtr<LongPressRecognizer> recognizer = AceType::DynamicCast<LongPressRecognizer>(curRecognizer);
        if (recognizer) {
            duration = recognizer->GetDuration();
        }
        std::advance(iter, 1);
        curRecognizer = *iter;
        SendTouchEventToNextRecognizer(curRecognizer, duration);
    }
}

bool SequencedRecognizer::CheckBetweenTwoLongPressRecognizer(int32_t currentIndex)
{
    if (currentIndex <= 0 || currentIndex_ > static_cast<int32_t>(recognizers_.size()) - 1) {
        return false;
    }
    auto iterBefore = recognizers_.begin();
    std::advance(iterBefore, currentIndex - 1);
    auto iterAfter = recognizers_.begin();
    std::advance(iterAfter, currentIndex);
    return AceType::InstanceOf<LongPressRecognizer>(*iterBefore) &&
           AceType::InstanceOf<LongPressRecognizer>(*iterAfter);
}

void SequencedRecognizer::SendTouchEventToNextRecognizer(
    const RefPtr<NGGestureRecognizer> curRecognizer, int64_t beforeDuration)
{
    if (inputEventType_ == InputEventType::AXIS) {
        auto event = lastAxisEvent_;
        event.action = AxisAction::BEGIN;
        curRecognizer->HandleEvent(event);
        return;
    }
    for (auto& item : touchPoints_) {
        item.second.type = TouchType::DOWN;
        if (beforeDuration > 0) {
            std::chrono::microseconds microseconds(
                static_cast<int64_t>(item.second.time.time_since_epoch().count()) + beforeDuration);
            TimeStamp time(microseconds);
            item.second.time = time;
        }
        if (!childTouchTestList_.empty()) {
            item.second.childTouchTestList = childTouchTestList_;
        }
        curRecognizer->HandleEvent(item.second);
        AddGestureProcedure(item.second, curRecognizer);
    }
}

void SequencedRecognizer::OnResetStatus()
{
    RecognizerGroup::OnResetStatus();
    currentIndex_ = 0;
    deadlineTimer_.Cancel();
    childTouchTestList_.clear();
}

void SequencedRecognizer::DeadlineTimer()
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);

    auto callback = [weakPtr = AceType::WeakClaim(this)]() {
        auto refPtr = weakPtr.Upgrade();
        if (refPtr) {
            refPtr->HandleOverdueDeadline();
        }
    };

    deadlineTimer_.Reset(callback);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    taskExecutor.PostDelayedTask(deadlineTimer_, SEQUENCE_GESTURE_TIMEOUT, "ArkUIGestureSequencedDeadlineTimer");
}

void SequencedRecognizer::HandleOverdueDeadline()
{
    if (refereeState_ == RefereeState::PENDING) {
        GroupAdjudicate(AceType::Claim(this), GestureDisposal::REJECT);
    }
}

bool SequencedRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    RefPtr<SequencedRecognizer> curr = AceType::DynamicCast<SequencedRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (recognizers_.size() != curr->recognizers_.size() || priorityMask_ != curr->priorityMask_) {
        ResetStatus();
        return false;
    }

    auto iter = recognizers_.begin();
    auto currIter = curr->recognizers_.begin();
    for (size_t i = 0; i < recognizers_.size(); i++) {
        auto child = *iter;
        auto newChild = *currIter;
        if (!child || !child->ReconcileFrom(newChild)) {
            ResetStatus();
            return false;
        }
        ++iter;
        ++currIter;
    }

    onActionCancel_ = std::move(curr->onActionCancel_);

    return true;
}

void SequencedRecognizer::CleanRecognizerState()
{
    for (const auto& child : recognizers_) {
        auto childRecognizer = AceType::DynamicCast<MultiFingersRecognizer>(child);
        if (childRecognizer && childRecognizer->GetTouchPointsSize() <= 1) {
            childRecognizer->CleanRecognizerState();
        }
    }
    if ((refereeState_ == RefereeState::SUCCEED ||
        refereeState_ == RefereeState::FAIL ||
        refereeState_ == RefereeState::DETECTING) &&
        currentFingers_ == 0) {
        refereeState_ = RefereeState::READY;
        disposal_ = GestureDisposal::NONE;
    }
    currentIndex_ = 0;
    childTouchTestList_.clear();
}

void SequencedRecognizer::ForceCleanRecognizer()
{
    for (const auto& child : recognizers_) {
        if (child) {
            child->ForceCleanRecognizer();
        }
    }
    MultiFingersRecognizer::ForceCleanRecognizer();
    currentIndex_ = 0;
    childTouchTestList_.clear();
}
} // namespace OHOS::Ace::NG
