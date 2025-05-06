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

#include "adapter/ohos/entrance/ui_session/test/mock_ui_sa_stub.h"

namespace OHOS::Ace {
int MockSaStub::OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    if (data.ReadInterfaceToken() != GetDescriptor()) {
        return ERR_INVALID_DATA;
    }
    int32_t resultCode = 0;
    switch (code) {
        case MessageCode::EXECUTE_METHOD: {
            resultCode = Test(data, reply);
            break;
        }
        default: {
            resultCode = ERR_INVALID_DATA;
            break;
        }
    }
    return resultCode;
}
int32_t MockSaStub::Test(MessageParcel& data, MessageParcel& reply)
{
    std::string somebody = data.ReadString();
    std::string result = ExecuteMethod();
    reply.WriteNoException();
    reply.WriteString(result);
    return ERR_NONE;
}

} // namespace OHOS::Ace