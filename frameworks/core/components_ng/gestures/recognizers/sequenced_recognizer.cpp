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

#include <iterator>
#include <vector>

#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "base/utils/utils.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/components_ng/gestures/recognizers/recognizer_group.h"
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
            activeRecognizer->OnAccepted();
            UpdateCurrentIndex();
        }
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
            recognizer->OnRejected();
        }
        ++iter;
    }

    if (currentIndex_ != -1) {
        SendCancelMsg();
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
            activeRecognizer->OnAccepted();
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

bool SequencedRecognizer::HandleEvent(const TouchEvent& point)
{
    auto iter = recognizers_.begin();
    std::advance(iter, currentIndex_);
    RefPtr<NGGestureRecognizer> curRecognizer = *iter;
    if (!curRecognizer) {
        LOGE("curRecognizer is nullptr");
        GroupAdjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return true;
    }
    touchPoints_[point.id] = point;
    if (currentIndex_ > 0) {
        auto prevState = curRecognizer->GetRefereeState();
        if (prevState == RefereeState::READY) {
            // the prevState is ready, need to pase down event to the new coming recognizer.
            for (auto& item : touchPoints_) {
                item.second.type = TouchType::DOWN;
                curRecognizer->HandleEvent(item.second);
            }
        }
    }
    switch (point.type) {
        case TouchType::DOWN:
            if (touchPoints_.size() == 1) {
                deadlineTimer_.Cancel();
            }
            [[fallthrough]];
        case TouchType::MOVE:
        case TouchType::UP:
        case TouchType::CANCEL:
            curRecognizer->HandleEvent(point);
            break;
        default:
            LOGW("unknown touch type");
            break;
    }

    if ((point.type == TouchType::UP) && (refereeState_ == RefereeState::PENDING)) {
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
        LOGD("the sub recognizer %{public}s ask for accept", AceType::TypeName(recognizer));
        if (currentIndex_ == static_cast<int32_t>((recognizers_.size() - 1))) {
            GroupAdjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        } else {
            if (refereeState_ == RefereeState::PENDING) {
                UpdateCurrentIndex();
                recognizer->OnAccepted();
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
}

void SequencedRecognizer::OnResetStatus()
{
    RecognizerGroup::OnResetStatus();
    currentIndex_ = 0;
    deadlineTimer_.Cancel();
}

void SequencedRecognizer::DeadlineTimer()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    auto callback = [weakPtr = AceType::WeakClaim(this)]() {
        auto refPtr = weakPtr.Upgrade();
        if (refPtr) {
            refPtr->HandleOverdueDeadline();
        } else {
            LOGE("fail to handle overdue deadline due to context is nullptr");
        }
    };

    deadlineTimer_.Reset(callback);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    taskExecutor.PostDelayedTask(deadlineTimer_, SEQUENCE_GESTURE_TIMEOUT);
}

void SequencedRecognizer::HandleOverdueDeadline()
{
    LOGI("sequence gesture recognizer does not receive touch down in time");
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

} // namespace OHOS::Ace::NG
