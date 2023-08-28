/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/gestures/recognizers/recognizer_group.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace::NG {

void RecognizerGroup::OnBeginGestureReferee(int32_t touchId, bool needUpdateChild)
{
    MultiFingersRecognizer::OnBeginGestureReferee(touchId);
    if (!needUpdateChild) {
        return;
    }
    for (const auto& child : recognizers_) {
        if (child) {
            child->BeginReferee(touchId, needUpdateChild);
        }
    }
}

void RecognizerGroup::OnFinishGestureReferee(int32_t touchId, bool isBlocked)
{
    for (const auto& child : recognizers_) {
        if (child) {
            child->FinishReferee(touchId, isBlocked);
        }
    }
    MultiFingersRecognizer::OnFinishGestureReferee(touchId, isBlocked);
}

const std::list<RefPtr<NGGestureRecognizer>>& RecognizerGroup::GetGroupRecognizer()
{
    return recognizers_;
}

void RecognizerGroup::AddChildren(const std::list<RefPtr<NGGestureRecognizer>>& recognizers)
{
    // TODO: add state adjustment.
    for (const auto& child : recognizers) {
        if (child && !Existed(child)) {
            recognizers_.emplace_back(child);
            child->SetGestureGroup(AceType::WeakClaim(this));
        }
    }
}

RefereeState RecognizerGroup::CheckStates(size_t touchId)
{
    int count = 0;
    for (auto& recognizer : recognizers_) {
        if (AceType::InstanceOf<MultiFingersRecognizer>(recognizer) && !recognizer->CheckTouchId(touchId)) {
            continue;
        }
        if (!AceType::InstanceOf<RecognizerGroup>(recognizer)) {
            if (recognizer->GetRefereeState() != RefereeState::SUCCEED_BLOCKED &&
                recognizer->GetRefereeState() != RefereeState::SUCCEED &&
                recognizer->GetRefereeState() != RefereeState::FAIL &&
                recognizer->GetRefereeState() != RefereeState::READY) {
                count++;
                break;
            }
            continue;
        }
        auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
        if (group) {
            auto state = group->CheckStates(touchId);
            if (state == RefereeState::PENDING) {
                count++;
                break;
            }
        }
    }
    if (count > 0) {
        return RefereeState::PENDING;
    } else {
        return RefereeState::READY;
    }
}

void RecognizerGroup::ForceReject()
{
    for (auto& recognizer : recognizers_) {
        if (!AceType::InstanceOf<RecognizerGroup>(recognizer)) {
            if (recognizer->GetRefereeState() != RefereeState::SUCCEED_BLOCKED &&
                recognizer->GetRefereeState() != RefereeState::SUCCEED &&
                recognizer->GetRefereeState() != RefereeState::FAIL) {
                recognizer->OnRejected();
            }
            continue;
        }
        auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
        if (group) {
            group->ForceReject();
        }
    }
    if (GetRefereeState() != RefereeState::FAIL) {
        OnRejected();
    }
}

bool RecognizerGroup::Existed(const RefPtr<NGGestureRecognizer>& recognizer)
{
    CHECK_NULL_RETURN(recognizer, false);

    if (recognizers_.empty()) {
        return false;
    }
    auto result = std::find(recognizers_.cbegin(), recognizers_.cend(), recognizer);
    return result != recognizers_.cend();
}

void RecognizerGroup::OnFlushTouchEventsBegin()
{
    for (const auto& recognizer : recognizers_) {
        if (recognizer) {
            recognizer->OnFlushTouchEventsBegin();
        }
    }
}

void RecognizerGroup::OnFlushTouchEventsEnd()
{
    for (const auto& recognizer : recognizers_) {
        if (recognizer) {
            recognizer->OnFlushTouchEventsEnd();
        }
    }
}

void RecognizerGroup::OnResetStatus()
{
    MultiFingersRecognizer::OnResetStatus();
    if (!remainChildOnResetStatus_) {
        for (const auto& child : recognizers_) {
            if (child) {
                child->SetGestureGroup(nullptr);
            }
        }
        recognizers_.clear();
    }
}

bool RecognizerGroup::CheckAllFailed()
{
    auto notFailMember =
        std::find_if(std::begin(recognizers_), std::end(recognizers_), [](const RefPtr<NGGestureRecognizer>& member) {
            return member && member->GetRefereeState() != RefereeState::FAIL;
        });

    return notFailMember == recognizers_.end();
}

void RecognizerGroup::GroupAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
{
    disposal_ = disposal;
    NGGestureRecognizer::BatchAdjudicate(recognizer, disposal);
}

} // namespace OHOS::Ace::NG
