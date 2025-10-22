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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_IREMOTE_BROKER_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_IREMOTE_BROKER_H

#include "refbase.h"
namespace OHOS {
#define DECLARE_INTERFACE_DESCRIPTOR(DESCRIPTOR)                         \
    static constexpr const char16_t *metaDescriptor_ = DESCRIPTOR;       \
    static inline const std::u16string GetDescriptor()                  \
    {                                                                    \
        return metaDescriptor_;                                          \
    }

class IRemoteBroker {
public:
    IRemoteBroker() = default;
    virtual ~IRemoteBroker() = default;
};

template <typename T>
class BrokerDelegator {
public:
    BrokerDelegator();
    ~BrokerDelegator();

private:
    BrokerDelegator(const BrokerDelegator &) = delete;
    BrokerDelegator(BrokerDelegator &&) = delete;
    BrokerDelegator &operator = (const BrokerDelegator &) = delete;
    BrokerDelegator &operator = (BrokerDelegator &&) = delete;
};

template <typename T>
BrokerDelegator<T>::BrokerDelegator()
{
}

template <typename T> BrokerDelegator<T>::~BrokerDelegator()
{
}
}

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_IREMOTE_BROKER_H
