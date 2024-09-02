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

#include "core/components_ng/event/long_press_event.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

LongPressEventActuator::LongPressEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub)
    : gestureEventHub_(gestureEventHub)
{}

void LongPressEventActuator::OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, ResponseLinkResult& responseLinkResult)
{
    CHECK_NULL_VOID(longPressEvent_);
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);

    if (!longPressRecognizer_) {
        longPressRecognizer_ = MakeRefPtr<LongPressRecognizer>(isForDrag_, isDisableMouseLeft_);
    }

    longPressRecognizer_->SetIsSystemGesture(true);
    longPressRecognizer_->SetRecognizerType(GestureTypeName::LONG_PRESS_GESTURE);
    longPressRecognizer_->SetOnAction(GetGestureEventFunc());
    longPressRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    longPressRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    result.emplace_back(longPressRecognizer_);
    responseLinkResult.emplace_back(longPressRecognizer_);
}

GestureEventFunc LongPressEventActuator::GetGestureEventFunc()
{
    auto callback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        if (actuator->longPressEvent_) {
            (*actuator->longPressEvent_)(info);
        }
        if (actuator->onAccessibilityEventFunc_) {
            actuator->onAccessibilityEventFunc_(AccessibilityEventType::LONG_PRESS);
        }
    };
    return callback;
}

} // namespace OHOS::Ace::NG
