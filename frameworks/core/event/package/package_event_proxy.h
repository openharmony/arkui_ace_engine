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
 
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_PACKAGE_EVENT_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_PACKAGE_EVENT_PROXY_H
 
#include <mutex>
#include <set>
 
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/event/package/package_change_listener.h"
 
namespace OHOS::Ace {
/**
 * @class PackageEventProxy
 * @brief The PackageEventProxy class is responsible for managing package event subscriptions and notifying subscribers
 *        It provides a singleton instance and allows subscribers to register for package events.
 */
class ACE_EXPORT PackageEventProxy {
public:
    virtual ~PackageEventProxy() = default;
 
    /**
     * @brief Get the singleton instance of PackageEventProxy.
     * @return The singleton instance of PackageEventProxy.
     */
    static PackageEventProxy* GetInstance();
 
    /**
     * @brief Register a package event listener.
     * @param listener The package event listener to register.
     */
    virtual void Register(const WeakPtr<PackageChangeListener>& listener) = 0;
 
    virtual void OnPackageChange() = 0;
 
protected:
    PackageEventProxy() = default;
 
private:
 
    static std::unique_ptr<PackageEventProxy> instance_; /**< The singleton instance of PackageEventProxy. */
    static std::mutex mutex_;  /**< Mutex for thread-safe creation of the singleton instance. */
 
    ACE_DISALLOW_COPY_AND_MOVE(PackageEventProxy);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_PACKAGE_EVENT_PROXY_H