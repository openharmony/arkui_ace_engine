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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_REF_COUNTER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_REF_COUNTER_H

#include <atomic>

#include "ui/base/macros.h"
#include "ui/base/noncopyable.h"

namespace OHOS::Ace {

// Define thread-safe counter using 'std::atomic' to implement Increase/Decrease count.
class ThreadSafeCounter final {
public:
    explicit ThreadSafeCounter(int32_t count) : count_(count) {}
    ~ThreadSafeCounter() = default;

    void Increase()
    {
        count_.fetch_add(1, std::memory_order_relaxed);
    }
    int32_t Decrease()
    {
        int32_t count = count_.fetch_sub(1, std::memory_order_release);
        ACE_DCHECK(count > 0);
        return count - 1;
    }
    int32_t CurrentCount() const
    {
        return count_.load(std::memory_order_relaxed);
    }

    // Try to increase reference count while current value is not zero.
    bool TryIncrease()
    {
        int32_t count = CurrentCount();
        do {
            if (count == 0) {
                return false;
            }
            ACE_DCHECK(count > 0);
        } while (!count_.compare_exchange_weak(count, count + 1, std::memory_order_relaxed));
        return true;
    }

private:
    std::atomic<int32_t> count_ { 0 };

    ACE_DISALLOW_COPY_AND_MOVE(ThreadSafeCounter);
};

class RefCounter final {
public:
    static RefCounter* Create()
    {
        return new RefCounter();
    }

    void IncStrongRef()
    {
        strongRef_.Increase();
    }
    int32_t DecStrongRef()
    {
        return strongRef_.Decrease();
    }
    bool TryIncStrongRef()
    {
        return strongRef_.TryIncrease();
    }
    int32_t StrongRefCount() const
    {
        return strongRef_.CurrentCount();
    }

    void IncWeakRef()
    {
        weakRef_.Increase();
    }
    void DecWeakRef()
    {
        int32_t refCount = weakRef_.Decrease();
        if (refCount == 0) {
            // Release this reference counter, while its weak reference have reduced to zero.
            delete this;
        }
    }

protected:
    ~RefCounter() = default;

private:
    ThreadSafeCounter strongRef_ { 0 };
    // Weak reference count should start with 1,
    // because instance MUST hold the reference counter for itself.
    ThreadSafeCounter weakRef_ { 1 };
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_REF_COUNTER_H
