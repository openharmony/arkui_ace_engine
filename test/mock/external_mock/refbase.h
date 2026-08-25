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

namespace OHOS {
#ifndef ACE_MOCK_REFBASE_SPTR_DEFINED
#define ACE_MOCK_REFBASE_SPTR_DEFINED
template <typename T>
class sptr {
private:
    T* ptr;
public:
    sptr()
    {
        ptr = nullptr;
    }
    sptr(T* p) : ptr(p) {}
    ~sptr()
    {
        delete ptr;
    }

    sptr(const sptr&) = delete;
    sptr& operator=(const sptr&) = delete;

    T& operator*()
    {
        return *ptr;
    }

    T* operator->()
    {
        return ptr;
    }

    bool operator==(std::nullptr_t) const
    {
        return ptr == nullptr;
    }

    bool operator!=(std::nullptr_t) const
    {
        return ptr != nullptr;
    }
};
#endif // ACE_MOCK_REFBASE_SPTR_DEFINED

#ifndef ACE_MOCK_REFBASE_WPTR_DEFINED
#define ACE_MOCK_REFBASE_WPTR_DEFINED
template <typename T>
class wptr {
private:
    T* ptr;
public:
    wptr() : ptr(nullptr) {}
    wptr(T* p) : ptr(p) {}
    wptr(const sptr<T>& s) : ptr(s.operator->()) {}
    T* operator->() const { return ptr; }
    operator bool() const { return ptr != nullptr; }
};
#endif // ACE_MOCK_REFBASE_WPTR_DEFINED
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_EXTERNAL_MOCK_MOCK_REBASE_H
