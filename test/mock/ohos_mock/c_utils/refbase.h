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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_EXTERNAL_MOCK_MOCK_REBASE_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_EXTERNAL_MOCK_MOCK_REBASE_H

#include <memory>
namespace OHOS {
template <typename T>
class sptr {
private:
    std::shared_ptr<T> ptr_;
public:
    sptr(T* p)
    {
        ptr_ = std::shared_ptr<T>(p);
    }

    sptr(const sptr& other)
    {
        ptr_ = other.ptr_;
    }

    sptr(const std::shared_ptr<T>& p): ptr_(p) {}

    ~sptr() = default;

    T& operator*()
    {
        return *ptr_;
    }

    const T* operator->() const
    {
        return ptr_.operator->();
    }

    T* operator->()
    {
        return ptr_.operator->();
    }

    bool operator==(std::nullptr_t) const
    {
        return ptr_ == nullptr;
    }

    bool operator!=(std::nullptr_t) const
    {
        return ptr_ != nullptr;
    }

    sptr& operator=(const sptr& other)
    {
        ptr_ = other.ptr_;
        return *this;
    }

    operator bool() const
    {
        return ptr_ != nullptr;
    }
};

template <typename T>
class wptr {
private:
    std::weak_ptr<T> ptr_;
public:
    wptr(T* p)
    {
        ptr_ = std::shared_ptr<T>(p);
    }

    wptr(const wptr& other)
    {
        ptr_ = other.ptr_;
    }

    wptr(const sptr<T>& other)
    {
        ptr_ = other.ptr_;
    }

    wptr(const std::weak_ptr<T>& p): ptr_(p) {}

    ~wptr() = default;

    T& operator*()
    {
        return *ptr_;
    }

    bool operator==(std::nullptr_t) const
    {
        return ptr_ == nullptr;
    }

    bool operator!=(std::nullptr_t) const
    {
        return ptr_ != nullptr;
    }

    wptr& operator=(const wptr& other)
    {
        ptr_ = other.ptr_;
        return *this;
    }

    const sptr<T> promote() const
    {
        return sptr<T>(ptr_.lock());
    }
};
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_EXTERNAL_MOCK_MOCK_REBASE_H
