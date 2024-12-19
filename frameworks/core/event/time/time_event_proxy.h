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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TIME_EVENT_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TIME_EVENT_PROXY_H

#include <mutex>
#include <set>

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/event/time/time_change_listener.h"

namespace OHOS::Ace {
/**
 * @class TimeEventProxy
 * @brief The TimeEventProxy class is responsible for managing time event subscriptions and notifying subscribers.
 *        It provides a singleton instance and allows subscribers to register for time events.
 */
class TimeEventProxy {
public:
    virtual ~TimeEventProxy() = default;

    /**
     * @brief Get the singleton instance of TimeEventProxy.
     * @return The singleton instance of TimeEventProxy.
     */
    static TimeEventProxy* GetInstance();

    /**
     * @brief Register a time event listener.
     * @param listener The time event listener to register.
     */
    virtual void Register(const WeakPtr<TimeChangeListener>& listener) = 0;

    virtual void OnTimeChange() = 0;

protected:
    TimeEventProxy() = default;

private:

    static std::unique_ptr<TimeEventProxy> instance_; /**< The singleton instance of TimeEventProxy. */
    static std::mutex mutex_;                         /**< Mutex for thread-safe creation of the singleton instance. */

    ACE_DISALLOW_COPY_AND_MOVE(TimeEventProxy);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TIME_EVENT_PROXY_H
