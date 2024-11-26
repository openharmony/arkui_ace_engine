/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_FORM_EVENT_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_FORM_EVENT_MANAGER_H

#include <functional>
#include <unordered_map>
#include <memory>

#include "base/memory/ace_type.h"
#include "core/event/touch_event.h"
#include "core/event/axis_event.h"
#include "interfaces/inner_api/ace/serialized_gesture.h"


namespace OHOS::Ace {
using EtsCardTouchEventCallback = std::function<void(const TouchEvent&, SerializedGesture& serializedGesture)>;
using EtsCardAxisEventCallback = std::function<void(const AxisEvent&, SerializedGesture& serializedGesture)>;

namespace NG {
class FormEventManager : public virtual AceType {
    DECLARE_ACE_TYPE(FormEventManager, AceType);
public:
    FormEventManager() = default;

    ~FormEventManager() override = default;

    void AddEtsCardTouchEventCallback(int32_t ponitId, EtsCardTouchEventCallback&& callback);

    void AddEtsCardAxisEventCallback(int32_t pointId, EtsCardAxisEventCallback&& callback);

    void HandleEtsCardTouchEvent(const TouchEvent &point, SerializedGesture& serializedGesture);

    void HandleEtsCardAxisEvent(const AxisEvent &point, SerializedGesture& serializedGesture);

    void RemoveEtsCardTouchEventCallback(int32_t ponitId);

    void RemoveEtsCardAxisEventCallback(int32_t pointId);

    void ClearEtsCardTouchEventCallback();

    void ClearEtsCardAxisEventCallback();

private:
    std::unordered_map<int32_t, EtsCardTouchEventCallback> etsCardTouchEventCallback_;
    std::unordered_map<int32_t, EtsCardAxisEventCallback> etsCardAxisEventCallback_;
};
} // namespace OHOS::Ace
} // namespace OHOS::Ace::NG
#endif //FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_FORM_EVENT_MANAGER_H
