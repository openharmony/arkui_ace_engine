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

#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {
GestureEventHub::GestureEventHub(const WeakPtr<EventHub>& eventHub) : eventHub_(eventHub) {}

bool GestureEventHub::ProcessTouchTestHit(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    TouchTestResult& innerTargets, TouchTestResult& finalResult, int32_t touchId, const PointF& localPoint)
{
    return false;
}

void GestureEventHub::CombineIntoExclusiveRecognizer(
    const PointF& globalPoint, const PointF& localPoint, TouchTestResult& result, int32_t touchId)
{}

void GestureEventHub::OnModifyDone() {}
void GestureEventHub::AddClickEvent(const RefPtr<ClickEvent>& clickEvent) {}
void GestureEventHub::SetUserOnClick(GestureEventFunc&& clickEvent) {}
void GestureEventHub::BindMenu(GestureEventFunc&& showMenu) {}

std::string GestureEventHub::GetHitTestModeStr() const
{
    return "HitTestMode.Default";
}
} // namespace OHOS::Ace::NG
