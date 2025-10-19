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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_IREMOTE_STUB_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_IREMOTE_STUB_H

#include "message_parcel.h"
#include "message_option.h"
#include "iremote_object.h"

namespace OHOS {
class IPCObjectStub : public IRemoteObject {
public:
    IPCObjectStub() = default;
    virtual ~IPCObjectStub() = default;

    virtual int32_t OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option)
    {
        return 0;
    }
};

template <typename T>
class IRemoteStub : public IPCObjectStub, public T {
public:
    IRemoteStub() = default;
    virtual ~IRemoteStub() override = default;

    int32_t OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option) override
    {
        return 0;
    }
};
}
#endif
