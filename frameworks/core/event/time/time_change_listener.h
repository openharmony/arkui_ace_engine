/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TIME_CHANGE_LISTENER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TIME_CHANGE_LISTENER_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {
/**
 * @brief an interface for time change listeners. Listeners need to register to TimeEventProxy to receive time change
 */
class TimeChangeListener : public AceType {
public:
    TimeChangeListener() = default;
    ~TimeChangeListener() override = default;

    /**
     * @brief This function is called when the system time changes.
     *
     * Subclasses should override this function to perform specific actions when the time changes.
     */
    virtual void OnTimeChange() = 0;

    ACE_DISALLOW_COPY_AND_MOVE(TimeChangeListener);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TIME_CHANGE_LISTENER_H
