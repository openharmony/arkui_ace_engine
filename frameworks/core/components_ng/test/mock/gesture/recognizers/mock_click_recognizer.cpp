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

#include "core/components_ng/gestures/recognizers/click_recognizer.h"

namespace OHOS::Ace::NG {
ClickRecognizer::ClickRecognizer(int32_t fingers, int32_t count) {}

void ClickRecognizer::OnAccepted() {}

void ClickRecognizer::OnRejected() {}

void ClickRecognizer::HandleTouchDownEvent(const TouchEvent& event) {}

void ClickRecognizer::HandleTouchUpEvent(const TouchEvent& event) {}

void ClickRecognizer::HandleTouchMoveEvent(const TouchEvent& event) {}

void ClickRecognizer::HandleTouchCancelEvent(const TouchEvent& event) {}

void ClickRecognizer::HandleOverdueDeadline() {}

bool ClickRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& /* recognizer */)
{
    return true;
}
} // namespace OHOS::Ace::NG
