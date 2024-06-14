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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_MOCK_I_REMOTE_OBJECT_FORM_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_MOCK_I_REMOTE_OBJECT_FORM_H

#include "gmock/gmock.h"

#include "iremote_broker.h"
#include "iremote_object.h"

namespace OHOS {
namespace AppExecFwk {
class MockFormIRemoteObject : public IRemoteObject {
public:
    MockFormIRemoteObject() : IRemoteObject(u"mock_i_remote_object") {}

    ~MockFormIRemoteObject() {}

    int32_t GetObjectRefCount() override
    {
        return 0;
    }

    MOCK_METHOD(int, SendRequest, (uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option));

    bool IsProxyObject() const override
    {
        return true;
    }

    bool CheckObjectLegality() const override
    {
        return true;
    }

    bool AddDeathRecipient(const sptr<DeathRecipient> &recipient) override
    {
        return true;
    }

    bool RemoveDeathRecipient(const sptr<DeathRecipient> &recipient) override
    {
        return true;
    }

    bool Marshalling(Parcel &parcel) const override
    {
        return true;
    }

    sptr<IRemoteBroker> AsInterface() override
    {
        return nullptr;
    }

    int Dump(int fd, const std::vector<std::u16string> &args) override
    {
        return 0;
    }

    std::u16string GetObjectDescriptor() const
    {
        std::u16string descriptor = std::u16string();
        return descriptor;
    }
};
} // namespace Notification
} // namespace OHOS
#endif
