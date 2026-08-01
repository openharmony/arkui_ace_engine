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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_LIFECYCLE_OBSERVABLE_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_LIFECYCLE_OBSERVABLE_H

#include <set>

#include "ui/base/macros.h"

namespace OHOS::Ace {
class LifeCycleObserver;

// NOTICE: NOT multi-thread safe
class ACE_FORCE_EXPORT LifeCycleObservable {
public:
    void Subscrible(LifeCycleObserver* observer)
    {
        observers_.insert(observer);
    }
    void Unsubscrible(LifeCycleObserver* observer)
    {
        observers_.erase(observer);
    }
protected:
    ~LifeCycleObservable();
private:
    std::set<LifeCycleObserver*> observers_;
};

// NOTICE: NOT multi-thread safe
class ACE_FORCE_EXPORT LifeCycleObserver final {
public:
    LifeCycleObserver(LifeCycleObservable* observable) : observable_(observable)
    {
        observable_->Subscrible(this);
    }
    ~LifeCycleObserver()
    {
        if (observable_) {
            observable_->Unsubscrible(this);
        }
    }
    void Notify()
    {
        observable_ = nullptr;
    }
    template<typename T = LifeCycleObservable>
    T* Get() const
    {
        return reinterpret_cast<T*>(observable_);
    }
private:
    LifeCycleObservable* observable_;
};

LifeCycleObservable::~LifeCycleObservable()
{
    // notify all observers
    for (auto& observer : observers_) {
        observer->Notify();
    }
}

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_LIFECYCLE_OBSERVABLE_H
