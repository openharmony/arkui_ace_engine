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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_EVENT_MANAGER_MOCK_TOUCH_EVENT_TARGET_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_EVENT_MANAGER_MOCK_TOUCH_EVENT_TARGET_H

#include "core/event/touch_event.h"

namespace OHOS::Ace {
class MockTouchEventTarget : public TouchEventTarget {
public:
    MockTouchEventTarget() = default;

    // if return false means need to stop event dispatch.
    bool DispatchEvent(const TouchEvent& point) override
    {
        return true;
    }
    // if return false means need to stop event bubbling.
    bool HandleEvent(const TouchEvent& point) override
    {
        return true;
    };
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_EVENT_MANAGER_MOCK_TOUCH_EVENT_TARGET_H