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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_LIFECYCLE_CHECKABLE_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_LIFECYCLE_CHECKABLE_H

#include <atomic>
#include <cstdlib>

#include "ui/base/macros.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT LifeCycleCheckable {
public:
    template<class T>
    class PtrHolder {
    public:
        PtrHolder(T* ptr) : ptr_(ptr)
        {
            ptr_->lastStack_ = &ptr;
            ++ptr_->usingCount_;
        }
        ~PtrHolder()
        {
            --ptr_->usingCount_;
        }
        T* operator->() const
        {
            return ptr_;
        }

        void* operator new(size_t) = delete;
    private:
        T* ptr_;
    };

protected:
    ~LifeCycleCheckable()
    {
        if (usingCount_) {
            OnDetectedObjDestroyInUse();
        }
    }

    void OnDetectedObjDestroyInUse();

private:
    std::atomic_int usingCount_ = 0;
    std::atomic<void*> lastStack_ = nullptr;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_LIFECYCLE_CHECKABLE_H
