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

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

void ParallelRecognizer::OnAccepted()
{
    refereeState_ = RefereeState::SUCCEED;
    if (currentBatchRecognizer_) {
        currentBatchRecognizer_->AboutToAccept();
        currentBatchRecognizer_.Reset();
    }
    for (auto& recognizer : succeedBlockRecognizers_) {
        if (recognizer && recognizer->GetGestureState() == RefereeState::SUCCEED_BLOCKED) {
            recognizer->AboutToAccept();
        }
    }
    if (!succeedBlockRecognizers_.empty()) {
        succeedBlockRecognizers_.clear();
    }
}

void ParallelRecognizer::OnRejected()
{
    if (refereeState_ == RefereeState::SUCCEED) {
        return;
    }
    refereeState_ = RefereeState::FAIL;
    for (const auto& recognizer : recognizers_) {
        if (!recognizer) {
            continue;
        }
        if (AceType::InstanceOf<RecognizerGroup>(recognizer)) {
            auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
            group->ForceReject();
        } else {
            if (recognizer->IsBridgeMode()) {
                continue;
            }
            recognizer->OnRejected();
            recognizer->OnRejectBridgeObj();
        }
    }
    succeedBlockRecognizers_.clear();
}

void ParallelRecognizer::OnPending()
{
    refereeState_ = RefereeState::PENDING;
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
            if (currentBatchRecognizer_->GetGestureState() == RefereeState::SUCCEED_BLOCKED) {
                AddSucceedBlockRecognizer(currentBatchRecognizer_);
            }
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
            auto saveRecognizer = recognizer;
            recognizer->HandleEvent(point);
            AddGestureProcedure(point, saveRecognizer);
            if (recognizers_.size() < size) {
                break;
            }
        } else if (!recognizer) {
            if (point.type == TouchType::DOWN) {
                TAG_LOGI(AceLogTag::ACE_GESTURE, "ParallelRecognizer receive down event recognizer is invalid");
            }
        } else {
            if (point.type == TouchType::DOWN) {
                auto node = recognizer->GetAttachedNode().Upgrade();
                TAG_LOGI(AceLogTag::ACE_GESTURE,
                    "ParallelRecognizer receive down event has no activeRecognizer recognizer is not in id: "
                    "%{public}d touchTestResult, node tag = %{public}s",
                    point.id, node ? node->GetTag().c_str() : "null");
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
            AddGestureProcedure(event, recognizer);
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
            recognizer->AboutToAccept();
        } else if ((refereeState_ == RefereeState::PENDING_BLOCKED) ||
                   (refereeState_ == RefereeState::SUCCEED_BLOCKED)) {
            if (refereeState_ == RefereeState::SUCCEED_BLOCKED) {
                AddSucceedBlockRecognizer(recognizer);
            }
            recognizer->OnBlocked();
        } else {
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
            recognizer->OnPending();
        } else if ((refereeState_ == RefereeState::PENDING_BLOCKED) ||
                   (refereeState_ == RefereeState::SUCCEED_BLOCKED)) {
            recognizer->OnBlocked();
        } else {
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

void ParallelRecognizer::CleanRecognizerState()
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
    currentBatchRecognizer_ = nullptr;
    succeedBlockRecognizers_.clear();
}

void ParallelRecognizer::ForceCleanRecognizer()
{
    for (const auto& child : recognizers_) {
        if (child) {
            child->ForceCleanRecognizer();
        }
    }
    MultiFingersRecognizer::ForceCleanRecognizer();
    currentBatchRecognizer_ = nullptr;
    succeedBlockRecognizers_.clear();
}

void ParallelRecognizer::CleanRecognizerStateVoluntarily()
{
    for (const auto& child : recognizers_) {
        if (child && AceType::InstanceOf<RecognizerGroup>(child)) {
            child->CleanRecognizerStateVoluntarily();
        }
    }
}
} // namespace OHOS::Ace::NG
