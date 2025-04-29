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

#include "session/host/include/extension_session.h"
#include "test/unittest/core/pattern/ui_extension/mock/mock_data_handler.h"

namespace OHOS::Rosen {
void WindowEventChannelListener::SetTransferKeyEventForConsumedParams(int32_t keyEventId, bool isPreImeEvent,
    const std::shared_ptr<std::promise<bool>>& isConsumedPromise, const std::shared_ptr<WSError>& retCode)
{}

void WindowEventChannelListener::ResetTransferKeyEventForConsumedParams(bool isConsumed, WSError retCode) {}

void WindowEventChannelListener::OnTransferKeyEventForConsumed(
    int32_t keyEventId, bool isPreImeEvent, bool isConsumed, WSError retCode)
{}

int32_t WindowEventChannelListener::OnRemoteRequest(
    uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    return 1;
}

void ChannelDeathRecipient::OnRemoteDied(const wptr<IRemoteObject>& wptrDeath) {}

ExtensionSession::ExtensionSession(const SessionInfo& info) : Session(info) {}

ExtensionSession::~ExtensionSession()
{
    channelListener_ = nullptr;
    channelDeath_ = nullptr;
}

std::shared_ptr<IDataHandler> ExtensionSession::GetExtensionDataHandler() const
{
    return std::make_shared<OHOS::Rosen::MockDataHandler>();
}

sptr<ExtensionSession::ExtensionSessionEventCallback> ExtensionSession::GetExtensionSessionEventCallback()
{
    if (extSessionEventCallback_ == nullptr) {
        extSessionEventCallback_ = sptr<ExtensionSessionEventCallback>::MakeSptr();
    }
    return extSessionEventCallback_;
}

WSError ExtensionSession::TransferKeyEventForConsumed(
    const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool& isConsumed, bool& isTimeout, bool isPreImeEvent)
{
    isTimeout = isPreImeEvent;
    return WSError::WS_ERROR_NULLPTR;
}
} // namespace OHOS::Rosen
