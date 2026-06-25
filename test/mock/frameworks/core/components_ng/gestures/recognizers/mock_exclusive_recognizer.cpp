/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"

namespace OHOS::Ace::NG {
void ExclusiveRecognizer::OnAccepted()
{
    refereeState_ = RefereeState::SUCCEED;
}

void ExclusiveRecognizer::OnRejected()
{
    refereeState_ = RefereeState::FAIL;
}

void ExclusiveRecognizer::OnPending()
{
    refereeState_ = RefereeState::PENDING;
}

void ExclusiveRecognizer::OnBlocked()
{
    refereeState_ = RefereeState::PENDING_BLOCKED;
}

bool ExclusiveRecognizer::HandleEvent(const TouchEvent& point)
{
    (void)point;
    return false;
}

bool ExclusiveRecognizer::HandleEvent(const AxisEvent& event)
{
    (void)event;
    return false;
}

void ExclusiveRecognizer::CleanRecognizerState()
{
    activeRecognizer_.Reset();
}

void ExclusiveRecognizer::ForceCleanRecognizer()
{
    activeRecognizer_.Reset();
}

void ExclusiveRecognizer::CheckAndSetRecognizerCleanFlag(const RefPtr<NGGestureRecognizer>& recognizer)
{
    (void)recognizer;
}

void ExclusiveRecognizer::CleanRecognizerStateVoluntarily()
{
    activeRecognizer_.Reset();
}

void ExclusiveRecognizer::BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
{
    (void)recognizer;
    (void)disposal;
}

bool ExclusiveRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    (void)recognizer;
    return false;
}

void ExclusiveRecognizer::OnResetStatus()
{
    activeRecognizer_.Reset();
}
} // namespace OHOS::Ace::NG
