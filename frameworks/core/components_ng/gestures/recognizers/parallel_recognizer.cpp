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

#include "core/components_ng/gestures/recognizers/parallel_recognizer.h"

#include <vector>

#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace::NG {

void ParallelRecognizer::OnAccepted()
{
    refereeState_ = RefereeState::SUCCEED;
    if (currentBatchRecognizer_) {
        currentBatchRecognizer_->OnAccepted();
        currentBatchRecognizer_.Reset();
    }
}

void ParallelRecognizer::OnRejected()
{
    refereeState_ = RefereeState::FAIL;
    for (const auto& recognizer : recognizers_) {
        if (!recognizer) {
            continue;
        }
        if (recognizer->GetRefereeState() == RefereeState::FAIL) {
            LOGE("the %{public}s gesture recognizer already failed", AceType::TypeName(recognizer));
        }
        if (AceType::InstanceOf<RecognizerGroup>(recognizer)) {
            auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
            group->ForceReject();
        } else {
            recognizer->OnRejected();
        }
    }
}

void ParallelRecognizer::OnPending()
{
    refereeState_ = RefereeState::PENDING;
    LOGD("the parallel gesture recognizer is pending!");
    if (currentBatchRecognizer_) {
        currentBatchRecognizer_->OnPending();
        currentBatchRecognizer_.Reset();
    }
}

void ParallelRecognizer::OnBlocked()
{
    if (disposal_ == GestureDisposal::ACCEPT) {
        refereeState_ = RefereeState::SUCCEED_BLOCKED;
        if (currentBatchRecognizer_) {
            currentBatchRecognizer_->OnBlocked();
            currentBatchRecognizer_.Reset();
        }
        return;
    }
    if (disposal_ == GestureDisposal::PENDING) {
        refereeState_ = RefereeState::PENDING_BLOCKED;
        if (currentBatchRecognizer_) {
            currentBatchRecognizer_->OnBlocked();
            currentBatchRecognizer_.Reset();
        }
    }
}

bool ParallelRecognizer::HandleEvent(const TouchEvent& point)
{
    if (refereeState_ == RefereeState::READY) {
        refereeState_ = RefereeState::DETECTING;
    }
    auto size = recognizers_.size();
    for (const auto& recognizer : recognizers_) {
        if (recognizer && recognizer->CheckTouchId(point.id)) {
            recognizer->HandleEvent(point);
            if (recognizers_.size() < size) {
                LOGD("remove recognizer while handle event!");
                break;
            }
        }
    }
    return true;
}

bool ParallelRecognizer::HandleEvent(const AxisEvent& event)
{
    if (refereeState_ == RefereeState::READY) {
        refereeState_ = RefereeState::DETECTING;
    }
    for (const auto& recognizer : recognizers_) {
        if (recognizer) {
            recognizer->HandleEvent(event);
        }
    }
    return true;
}

void ParallelRecognizer::BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
{
    CHECK_NULL_VOID(recognizer);
    if (disposal == GestureDisposal::ACCEPT) {
        if (recognizer->GetRefereeState() == RefereeState::SUCCEED) {
            return;
        }

        if (refereeState_ == RefereeState::SUCCEED) {
            LOGD("the sub gesture recognizer %{public}s is accepted because referee succeed",
                AceType::TypeName(recognizer));
            recognizer->OnAccepted();
        } else if ((refereeState_ == RefereeState::PENDING_BLOCKED) ||
                   (refereeState_ == RefereeState::SUCCEED_BLOCKED)) {
            recognizer->OnBlocked();
        } else {
            LOGD("the sub gesture recognizer %{public}s ask for accept", AceType::TypeName(recognizer));
            currentBatchRecognizer_ = recognizer;
            GroupAdjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        }
        return;
    }
    if (disposal == GestureDisposal::REJECT) {
        if (recognizer->GetRefereeState() == RefereeState::FAIL) {
            return;
        }
        recognizer->OnRejected();
        if (CheckAllFailed()) {
            GroupAdjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
        return;
    }
    if (disposal == GestureDisposal::PENDING) {
        if (recognizer->GetRefereeState() == RefereeState::PENDING) {
            return;
        }

        if ((refereeState_ == RefereeState::SUCCEED) || (refereeState_ == RefereeState::PENDING)) {
            LOGD("the sub gesture recognizer %{public}s is pending because referee is in current state",
                AceType::TypeName(recognizer));
            recognizer->OnPending();
        } else if ((refereeState_ == RefereeState::PENDING_BLOCKED) ||
                   (refereeState_ == RefereeState::SUCCEED_BLOCKED)) {
            recognizer->OnBlocked();
        } else {
            LOGD("the sub gesture recognizer %{public}s ask for pending", AceType::TypeName(recognizer));
            currentBatchRecognizer_ = recognizer;
            GroupAdjudicate(AceType::Claim(this), GestureDisposal::PENDING);
        }
    }
}

bool ParallelRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    RefPtr<ParallelRecognizer> curr = AceType::DynamicCast<ParallelRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (recognizers_.size() != curr->recognizers_.size() || curr->priorityMask_ != priorityMask_) {
        ResetStatus();
        return false;
    }

    auto currIter = curr->recognizers_.begin();

    for (auto iter = recognizers_.begin(); iter != recognizers_.end(); iter++, currIter++) {
        auto child = *iter;
        auto newChild = *currIter;
        if (!child || !child->ReconcileFrom(newChild)) {
            ResetStatus();
            return false;
        }
    }

    return true;
}

} // namespace OHOS::Ace::NG
