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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_IREMOTE_OBJECT_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_IREMOTE_OBJECT_H

namespace OHOS {
class IRemoteObject {
public:
    explicit IRemoteObject(const std::u16string &descriptor = nullptr);
    virtual ~IRemoteObject() = default;
};
template <typename T>
class sptr {
private:
    T* ptr;
public:
    sptr(T* p) : ptr(p) {}
    ~sptr()
    {
        delete ptr;
    }

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
}

#endif //FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_IREMOTE_OBJECT_H