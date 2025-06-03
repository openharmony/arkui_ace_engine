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
#include "form_renderer_dispatcher_proxy.h"

#include "form_renderer_hilog.h"
#include "core/accessibility/accessibility_manager.h"

namespace OHOS {
namespace Ace {
FormRendererDispatcherProxy::FormRendererDispatcherProxy(const sptr<IRemoteObject>& impl)
    : IRemoteProxy<IFormRendererDispatcher>(impl) {}

void FormRendererDispatcherProxy::DispatchPointerEvent(
    const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent,
    SerializedGesture& serializedGesture)
{
    if (pointerEvent == nullptr) {
        HILOG_ERROR("%{public}s, pointerEvent is null", __func__);
        return;
    }

    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return;
    }

    if (!pointerEvent->WriteToParcel(data)) {
        HILOG_ERROR("Failed to write pointer event");
        return;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::DISPATCH_POINTER_EVENT),
        data, reply, option);

    int32_t size = 0;
    reply.ReadInt32(size);
    if (size < 0) {
        HILOG_ERROR("Serialized gesture size is not valid!");
    } else {
        auto buffer = static_cast<const char*>(reply.ReadRawData(size));
        if (buffer == nullptr) {
            return;
        }
        serializedGesture.data = std::vector<char>(buffer, buffer + size);
    }

    if (error != ERR_OK) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
    }
}

void FormRendererDispatcherProxy::SetAllowUpdate(bool allowUpdate)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return;
    }

    if (!data.WriteBool(allowUpdate)) {
        HILOG_ERROR("write allowUpdate fail, action error");
        return;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_ALLOW_UPDATE),
        data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
    }
}

void FormRendererDispatcherProxy::DispatchSurfaceChangeEvent(float width, float height, uint32_t reason,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, float borderWidth)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return;
    }

    if (!data.WriteFloat(width)) {
        HILOG_ERROR("write width fail, action error");
        return;
    }

    if (!data.WriteFloat(height)) {
        HILOG_ERROR("write height fail, action error");
        return;
    }

    if (!data.WriteUint32(static_cast<uint32_t>(reason))) {
        HILOG_ERROR("Write SessionSizeChangeReason failed");
        return;
    }

    bool hasRSTransaction = rsTransaction != nullptr;
    if (!data.WriteBool(hasRSTransaction)) {
        HILOG_ERROR("Write has transaction failed");
        return;
    }
    if (hasRSTransaction) {
        auto pid = rsTransaction->GetParentPid();
        rsTransaction->SetParentPid(getprocpid());
        if (!data.WriteParcelable(rsTransaction.get())) {
            HILOG_ERROR("Write transaction sync Id failed");
            return;
        }
        rsTransaction->SetParentPid(pid);
    }

    if (!data.WriteFloat(borderWidth)) {
        HILOG_ERROR("write borderWidth fail, action error");
        return;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::DISPATCH_SURFACE_CHANGE_EVENT), data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
    }
}

bool FormRendererDispatcherProxy::WriteInterfaceToken(MessageParcel &data)
{
    if (!data.WriteInterfaceToken(FormRendererDispatcherProxy::GetDescriptor())) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return false;
    }
    return true;
}

void FormRendererDispatcherProxy::SetObscured(bool isObscured)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("failed to write interface token");
        return;
    }

    if (!data.WriteBool(isObscured)) {
        HILOG_ERROR("write isObscured fail, action error");
        return;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_OBSCURED),
        data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("failed to SendRequest: %{public}d", error);
    }
}

void FormRendererDispatcherProxy::OnAccessibilityChildTreeRegister(
    uint32_t windowId, int32_t treeId, int64_t accessibilityId)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("failed to write interface token");
        return;
    }
    if (!data.WriteUint32(windowId)) {
        HILOG_ERROR("write windowId fail, action error");
        return;
    }
    if (!data.WriteInt32(treeId)) {
        HILOG_ERROR("write treeId fail, action error");
        return;
    }
    if (!data.WriteInt64(accessibilityId)) {
        HILOG_ERROR("write accessibilityId fail, action error");
        return;
    }

    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_CHILD_TREE_REGISTER),
        data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("failed to SendRequest: %{public}d", error);
    }
}

void FormRendererDispatcherProxy::OnAccessibilityChildTreeDeregister()
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("failed to write interface token");
        return;
    }

    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_CHILD_TREE_DEREGISTER),
        data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("failed to SendRequest: %{public}d", error);
    }
}

void FormRendererDispatcherProxy::OnAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("failed to write interface token");
        return;
    }
    if (!data.WriteStringVector(params)) {
        HILOG_ERROR("failed to write params");
        return;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_DUMP_CHILD_INFO),
        data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("failed to SendRequest: %{public}d", error);
        return;
    }
    if (!reply.ReadStringVector(&info)) {
        HILOG_ERROR("%{public}s, Read reply info failed.", __func__);
    }
}

void FormRendererDispatcherProxy::OnAccessibilityTransferHoverEvent(float pointX, float pointY, int32_t sourceType,
    int32_t eventType, int64_t timeMs)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("failed to write interface token");
        return;
    }
    if (!data.WriteFloat(pointX) ||
        !data.WriteFloat(pointY) ||
        !data.WriteInt32(sourceType) ||
        !data.WriteInt32(eventType) ||
        !data.WriteInt64(timeMs)) {
        HILOG_ERROR("Write TransferAccessibilityHoverEvent data failed");
        return;
    }

    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_TRANSFER_HOVER_EVENT),
        data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("failed to SendRequest: %{public}d", error);
    }
}

void FormRendererDispatcherProxy::OnNotifyDumpInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("failed to write interface token");
        return;
    }
    if (!data.WriteStringVector(params)) {
        HILOG_ERROR("failed to write params");
        return;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::NOTIFY_DUMP_INFO),
        data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("failed to SendRequest: %{public}d", error);
        return;
    }
    if (!reply.ReadStringVector(&info)) {
        HILOG_ERROR("%{public}s, Read reply info failed.", __func__);
    }
}

int32_t FormRendererDispatcherProxy::SendRequest(uint32_t code, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        HILOG_ERROR("remote is null");
        return IPC_PROXY_ERR;
    }
    return remote->SendRequest(code, data, reply, option);
}

void FormRendererDispatcherProxy::SetMultiInstanceEnabled(bool isMultiInstanceEnabled)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return;
    }
 
    if (!data.WriteBool(isMultiInstanceEnabled)) {
        HILOG_ERROR("write multi instance enabled flag fail, action error");
        return;
    }
 
    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_MULTI_INSTANCE_ENABLED),
        data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
    }
}
} // namespace Ace
} // namespace OHOS
