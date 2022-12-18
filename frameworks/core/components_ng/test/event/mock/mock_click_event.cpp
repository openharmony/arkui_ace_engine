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

#include "core/components_ng/event/click_event.h"

namespace OHOS::Ace::NG {
ClickEventActuator::ClickEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub)
    : gestureEventHub_(gestureEventHub)
{}

void ClickEventActuator::OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result)
{}

GestureEventFunc ClickEventActuator::GetClickEvent()
{
    auto callback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        for (const auto& callback : actuator->clickEvents_) {
            if (callback) {
                (*callback)(info);
            }
        }
        if (actuator->userCallback_) {
            (*actuator->userCallback_)(info);
        }
        if (actuator->onAccessibilityEventFunc_) {
            actuator->onAccessibilityEventFunc_(AccessibilityEventType::CLICK);
        }
    };
    return callback;
}
} // namespace OHOS::Ace::NG
