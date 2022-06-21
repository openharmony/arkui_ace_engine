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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_ACTUATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_ACTUATOR_H

#include <list>

#include "base/memory/referenced.h"
#include "core/components/scroll/scrollable.h"

namespace OHOS::Ace::NG {

class GestureEventActuator : public Referenced {
public:
    GestureEventActuator() = default;
    ~GestureEventActuator() override = default;

    virtual void OnCollectTouchTarget(
        const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
    {}
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_ACTUATOR_H