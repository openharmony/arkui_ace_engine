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

#include "core/gestures/parallel_recognizer.h"

namespace OHOS::Ace {

void ParallelRecognizer::OnAccepted(size_t touchId)
{
    if (refereePointers_.find(touchId) == refereePointers_.end()) {
        return;
    }
    refereePointers_.erase(touchId);

    for (auto& recognizer : recognizers_) {
        if (recognizer->GetDetectState() == DetectState::DETECTED) {
            recognizer->SetCoordinateOffset(coordinateOffset_);
            recognizer->OnAccepted(touchId);
            recognizer->SetRefereeState(RefereeState::SUCCEED);
        }
    }
}

void ParallelRecognizer::OnRejected(size_t touchId)
{
    if (refereePointers_.find(touchId) == refereePointers_.end()) {
        return;
    }
    refereePointers_.erase(touchId);

    for (auto& recognizer : recognizers_) {
        recognizer->OnRejected(touchId);
        if (recognizer->GetDetectState() == DetectState::READY) {
            recognizer->SetRefereeState(RefereeState::FAIL);
        }
    }
}

void ParallelRecognizer::OnPending(size_t touchId)
{
    if (refereePointers_.find(touchId) == refereePointers_.end()) {
        return;
    }

    for (auto& recognizer : recognizers_) {
        if (recognizer->GetRefereeState() == RefereeState::PENDING) {
            recognizer->OnPending(touchId);
        }
    }
}

bool ParallelRecognizer::HandleEvent(const TouchEvent& point)
{
    if (point.type == TouchType::UNKNOWN) {
        LOGW("unknown touch type");
        return true;
    }

    if (point.type == TouchType::DOWN) {
        bool allRecognizeEnd = true;
        for (auto& recognizer : recognizers_) {
            if (!IsRecognizeEnd(recognizer)) {
                allRecognizeEnd = false;
                break;
            }
        }

        if (allRecognizeEnd) {
            Reset();
        }
    }

    for (auto& recognizer : recognizers_) {
        if (recognizer->GetRefereeState() != RefereeState::FAIL) {
            recognizer->HandleEvent(point);
        }
    }

    return true;
}

void ParallelRecognizer::OnFlushTouchEventsBegin()
{
    for (auto& recognizer : recognizers_) {
        recognizer->OnFlushTouchEventsBegin();
    }
}

void ParallelRecognizer::OnFlushTouchEventsEnd()
{
    for (auto& recognizer : recognizers_) {
        recognizer->OnFlushTouchEventsEnd();
    }
}

bool ParallelRecognizer::IsRecognizeEnd(const RefPtr<GestureRecognizer>& recognizer)
{
    DetectState currState = recognizer->GetDetectState();
    RefereeState refereeState = recognizer->GetRefereeState();
    return (refereeState == RefereeState::SUCCEED && currState != DetectState::DETECTED) ||
           (refereeState == RefereeState::FAIL);
}

void ParallelRecognizer::BatchAdjudicate(
    const std::set<size_t>& touchIds, const RefPtr<GestureRecognizer>& recognizer, GestureDisposal disposal)
{
    if (disposal == GestureDisposal::ACCEPT) {
        if (state_ == DetectState::DETECTING) {
            state_ = DetectState::DETECTED;
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        } else if (refereeState_ == RefereeState::SUCCEED) {
            for (auto touchId : touchIds) {
                recognizer->OnAccepted(touchId);
            }
            recognizer->SetRefereeState(RefereeState::SUCCEED);
        }
    } else if (disposal == GestureDisposal::REJECT) {
        for (auto touchId : touchIds) {
            recognizer->OnRejected(touchId);
        }
        recognizer->SetRefereeState(RefereeState::FAIL);

        bool needReject = true;
        for (auto& tmpRecognizer : recognizers_) {
            if (tmpRecognizer->GetRefereeState() != RefereeState::FAIL) {
                needReject = false;
                break;
            }
        }

        if (needReject) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
    } else {
        if (state_ == DetectState::DETECTING) {
            recognizer->SetRefereeState(RefereeState::PENDING);
            Adjudicate(AceType::Claim(this), GestureDisposal::PENDING);
        }
    }
}

void ParallelRecognizer::AddToReferee(size_t touchId, const RefPtr<GestureRecognizer>& recognizer)
{
    recognizer->SetRefereeState(RefereeState::DETECTING);
    if (state_ == DetectState::READY) {
        state_ = DetectState::DETECTING;
    }

    if (state_ == DetectState::DETECTING) {
        MultiFingersRecognizer::AddToReferee(touchId, AceType::Claim(this));
    }
}

void ParallelRecognizer::Reset()
{
    state_ = DetectState::READY;
    for (auto& recognizer : recognizers_) {
        recognizer->SetRefereeState(RefereeState::DETECTING);
    }
}

bool ParallelRecognizer::ReconcileFrom(const RefPtr<GestureRecognizer>& recognizer)
{
    RefPtr<ParallelRecognizer> curr = AceType::DynamicCast<ParallelRecognizer>(recognizer);
    if (!curr) {
        Reset();
        return false;
    }

    if (recognizers_.size() != curr->recognizers_.size() || curr->priorityMask_ != priorityMask_) {
        Reset();
        return false;
    }

    auto currIter = curr->recognizers_.begin();

    for (auto iter = recognizers_.begin(); iter != recognizers_.end(); iter++, currIter++) {
        if (!(*iter)->ReconcileFrom(*currIter)) {
            Reset();
            return false;
        }
    }

    return true;
}

} // namespace OHOS::Ace
