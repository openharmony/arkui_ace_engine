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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_STATUSBAR_EVENT_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_STATUSBAR_EVENT_PROXY_H

#include <memory>
#include <mutex>
#include <set>

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/event/statusbar/statusbar_click_listener.h"

namespace OHOS::Ace {
/**
 * @class StatusBarEventProxy
 * @brief The StatusBarEventProxy class is responsible for managing statusbar event subscriptions and notifying
 * subscribers. It provides a singleton instance and allows subscribers to register for statusbar events.
 */
class StatusBarEventProxy {
public:
    virtual ~StatusBarEventProxy() = default;

    /**
     * @brief Get the singleton instance of StatusBarEventProxy.
     * @return The singleton instance of StatusBarEventProxy.
     */
    static StatusBarEventProxy* GetInstance();

    /**
     * @brief Register a statusbar event listener.
     * @param listener The statusbar event listener to register.
     */
    virtual void Register(const WeakPtr<StatusBarClickListener>& listener) = 0;
    virtual void UnRegister(const WeakPtr<StatusBarClickListener>& listener) = 0;
    virtual void OnStatusBarClick() = 0;
    virtual std::set<std::pair<WeakPtr<StatusBarClickListener>, int32_t>> GetStatusBarClickListener();

protected:
    StatusBarEventProxy() = default;

private:
    static std::unique_ptr<StatusBarEventProxy> instance_; /**< The singleton instance of StatusBarEventProxy. */
    static std::mutex mutex_; /**< Mutex for thread-safe creation of the singleton instance. */

    ACE_DISALLOW_COPY_AND_MOVE(StatusBarEventProxy);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_STATUSBAR_EVENT_PROXY_H
