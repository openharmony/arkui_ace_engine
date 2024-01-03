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
#include "form_renderer_dispatcher_stub.h"

#include "appexecfwk_errors.h"
#include "errors.h"
#include "form_renderer_hilog.h"
#include "ipc_skeleton.h"

namespace OHOS {
namespace Ace {
FormRendererDispatcherStub::FormRendererDispatcherStub()
{
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::DISPATCH_POINTER_EVENT)] =
        &FormRendererDispatcherStub::HandleDispatchPointerEvent;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_ALLOW_UPDATE)] =
        &FormRendererDispatcherStub::HandleSetAllowUpdate;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::DISPATCH_SURFACE_CHANGE_EVENT)] =
        &FormRendererDispatcherStub::HandleDispatchSurfaceChangeEvent;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_VISIBLE_CHANGE)] =
        &FormRendererDispatcherStub::HandleSetVisibleChange;
}

FormRendererDispatcherStub::~FormRendererDispatcherStub()
{
    memberFuncMap_.clear();
}

int32_t FormRendererDispatcherStub::OnRemoteRequest(
    uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    HILOG_DEBUG("FormRendererDispatcherStub::OnReceived, code = %{public}u, flags= %{public}d.",
        code, option.GetFlags());
    std::u16string descriptor = FormRendererDispatcherStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (descriptor != remoteDescriptor) {
        HILOG_ERROR("%{public}s failed, local descriptor is not equal to remote", __func__);
        return ERR_INVALID_VALUE;
    }

    auto itFunc = memberFuncMap_.find(code);
    if (itFunc != memberFuncMap_.end()) {
        auto memberFunc = itFunc->second;
        if (memberFunc != nullptr) {
            return (this->*memberFunc)(data, reply);
        }
    }

    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

int32_t FormRendererDispatcherStub::HandleDispatchPointerEvent(MessageParcel &data, MessageParcel &reply)
{
    std::shared_ptr<MMI::PointerEvent> pointerEvent = MMI::PointerEvent::Create();
    if (pointerEvent == nullptr) {
        HILOG_ERROR("%{public}s, Create Pointer Event failed.", __func__);
        return ERR_INVALID_VALUE;
    }

    if (!pointerEvent->ReadFromParcel(data)) {
        HILOG_ERROR("%{public}s, Read Pointer Event failed.", __func__);
        return ERR_INVALID_VALUE;
    }
    SerializedGesture serializedGesture;
    DispatchPointerEvent(pointerEvent, serializedGesture);
    reply.WriteInt32(serializedGesture.data.size());
    reply.WriteRawData(serializedGesture.data.data(), serializedGesture.data.size());
    return ERR_OK;
}

int32_t FormRendererDispatcherStub::HandleSetAllowUpdate(MessageParcel &data, MessageParcel &reply)
{
    bool allowUpdate = data.ReadBool();
    SetAllowUpdate(allowUpdate);
    reply.WriteInt32(ERR_OK);
    return ERR_OK;
}

int32_t FormRendererDispatcherStub::HandleDispatchSurfaceChangeEvent(MessageParcel& data, MessageParcel& reply)
{
    float width = data.ReadFloat();
    float height = data.ReadFloat();
    DispatchSurfaceChangeEvent(width, height);
    reply.WriteInt32(ERR_OK);
    return ERR_OK;
}

int32_t FormRendererDispatcherStub::HandleSetVisibleChange(MessageParcel &data, MessageParcel &reply)
{
    bool isVisible = data.ReadBool();
    SetVisibleChange(isVisible);
    reply.WriteInt32(ERR_OK);
    return ERR_OK;
}
}  // namespace Ace
}  // namespace OHOS