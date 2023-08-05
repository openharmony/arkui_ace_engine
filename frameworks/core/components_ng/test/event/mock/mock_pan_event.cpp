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

#include "core/components_ng/event/pan_event.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"

namespace OHOS::Ace::NG {
PanEventActuator::PanEventActuator(
    const WeakPtr<GestureEventHub>& gestureEventHub, PanDirection direction, int32_t fingers, float distance)
    : gestureEventHub_(gestureEventHub), direction_(direction), fingers_(fingers), distance_(distance)
{
    if (fingers_ < DEFAULT_PAN_FINGER) {
        fingers_ = DEFAULT_PAN_FINGER;
    }
    if (LessOrEqual(distance_, DEFAULT_PAN_DISTANCE.ConvertToPx())) {
        distance_ = DEFAULT_PAN_DISTANCE.ConvertToPx();
    }
}

void PanEventActuator::OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result)
{}
} // namespace OHOS::Ace::NG
