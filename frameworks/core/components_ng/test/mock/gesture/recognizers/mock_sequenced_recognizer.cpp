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

namespace OHOS::Ace::NG {
void SequencedRecognizer::OnAccepted() {}

void SequencedRecognizer::OnRejected() {}

void SequencedRecognizer::OnPending() {}

void SequencedRecognizer::OnBlocked() {}

bool SequencedRecognizer::HandleEvent(const TouchEvent&  /* point */)
{
    return true;
}

void SequencedRecognizer::BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal) {}

void SequencedRecognizer::OnResetStatus() {}

bool SequencedRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>&  /* recognizer */)
{
    return true;
}
} // namespace OHOS::Ace::NG
