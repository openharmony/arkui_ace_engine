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

#include "core/components_ng/gestures/recognizers/pan_recognizer.h"

namespace OHOS::Ace::NG {
void PanRecognizer::OnAccepted() {}

void PanRecognizer::OnRejected() {}

void PanRecognizer::HandleTouchDownEvent(const TouchEvent& event) {}

void PanRecognizer::HandleTouchDownEvent(const AxisEvent& event) {}

void PanRecognizer::HandleTouchUpEvent(const TouchEvent& event) {}

void PanRecognizer::HandleTouchUpEvent(const AxisEvent& event) {}

void PanRecognizer::HandleTouchMoveEvent(const TouchEvent& event) {}

void PanRecognizer::OnFlushTouchEventsBegin() {}

void PanRecognizer::OnFlushTouchEventsEnd() {}

void PanRecognizer::HandleTouchMoveEvent(const AxisEvent& event) {}

void PanRecognizer::HandleTouchCancelEvent(const TouchEvent& /* event */) {}

void PanRecognizer::HandleTouchCancelEvent(const AxisEvent& /* event */) {}

void PanRecognizer::OnResetStatus() {}

void PanRecognizer::SetDirection(OHOS::Ace::PanDirection const& direction) {}

bool PanRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>&  /* recognizer */)
{
    return true;
}
} // namespace OHOS::Ace::NG
