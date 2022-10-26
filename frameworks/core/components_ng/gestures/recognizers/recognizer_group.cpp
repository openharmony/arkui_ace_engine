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

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace::NG {

void RecognizerGroup::OnBeginGestureReferee(int32_t touchId)
{
    MultiFingersRecognizer::OnBeginGestureReferee(touchId);
    for (const auto& child : recognizers_) {
        if (child) {
            child->BeginReferee(touchId);
        }
    }
}

void RecognizerGroup::OnFinishGestureReferee(int32_t touchId)
{
    for (const auto& child : recognizers_) {
        if (child) {
            child->FinishReferee(touchId);
        }
    }
    MultiFingersRecognizer::OnFinishGestureReferee(touchId);
}

void RecognizerGroup::AddChildren(const std::list<RefPtr<GestureRecognizer>>& recognizers)
{
    // TODO: add state adjustment.
    for (const auto& child : recognizers) {
        if (child && !Existed(child)) {
            recognizers_.emplace_back(child);
            child->SetGestureGroup(AceType::WeakClaim(this));
        }
    }
}

bool RecognizerGroup::Existed(const RefPtr<GestureRecognizer>& recognizer)
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
        recognizers_.clear();
    }
}

bool RecognizerGroup::CheckAllFailed()
{
    auto notFailMember =
        std::find_if(std::begin(recognizers_), std::end(recognizers_), [](const RefPtr<GestureRecognizer>& member) {
            return member && member->GetRefereeState() != RefereeState::FAIL;
        });

    return notFailMember == recognizers_.end();
}

void RecognizerGroup::GroupAdjudicate(const RefPtr<GestureRecognizer>& recognizer, GestureDisposal disposal)
{
    disposal_ = disposal;
    GestureRecognizer::BatchAdjudicate(recognizer, disposal);
}

} // namespace OHOS::Ace::NG
