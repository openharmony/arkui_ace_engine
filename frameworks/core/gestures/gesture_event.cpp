/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/gestures/gesture_event.h"

#include "base/input_manager/input_manager.h"

namespace OHOS::Ace {

size_t GestureEvent::GetApproximateSize() const
{
    constexpr size_t FINGER_COUNT = 5;
    constexpr size_t LIST_NODE = sizeof(void*) * 2;
    constexpr size_t fingerListSize = FINGER_COUNT * (sizeof(FingerInfo) + LIST_NODE);
    constexpr size_t pointerEventCount = 2; // pointerEvent_ and clickPointerEvent_

#ifdef SECURITY_COMPONENT_ENABLE
    constexpr size_t secCompSize = sizeof(JsonValue);
#else
    constexpr size_t secCompSize = 0;
#endif

    return sizeof(*this) + GetApproximateBaseEventSize() + secCompSize + fingerListSize +
           (InputManager::GetApproximatePointerEventSize() * pointerEventCount);
}

} // namespace OHOS::Ace
