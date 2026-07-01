/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_UI_SESSION_REQUEST_GUARD_H
#define FOUNDATION_ACE_INTERFACE_UI_SESSION_REQUEST_GUARD_H

#include <atomic>

namespace OHOS::Ace {
// Guards synchronous get-style IPC calls that allow only one pending request in a proxy instance.
class SyncRequestGuard final {
public:
    explicit SyncRequestGuard(std::atomic_bool& pending) : pending_(pending)
    {
        bool expected = false;
        acquired_ = pending_.compare_exchange_strong(expected, true);
    }

    ~SyncRequestGuard()
    {
        if (acquired_) {
            pending_.store(false);
        }
    }

    SyncRequestGuard(const SyncRequestGuard&) = delete;
    SyncRequestGuard& operator=(const SyncRequestGuard&) = delete;

    bool IsAcquired() const
    {
        return acquired_;
    }

private:
    std::atomic_bool& pending_;
    bool acquired_ = false;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACE_UI_SESSION_REQUEST_GUARD_H
