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

#include "appexecfwk_errors.h"
#include "errors.h"
#include "form_renderer_hilog.h"

#include "core/event/touch_event.h"

namespace OHOS {
namespace Ace {
FormRendererDispatcherProxy::FormRendererDispatcherProxy(const sptr<IRemoteObject>& impl)
    : IRemoteProxy<IFormRendererDispatcher>(impl) {}

void FormRendererDispatcherProxy::DispatchPointerEvent(
    const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent, SerializedGesture& serializedGesture)
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
    int error = Remote()->SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::DISPATCH_POINTER_EVENT),
        data, reply, option);

    int32_t result;
    reply.ReadInt32(result);
    reply.ReadInt32(serializedGesture.size);
    auto buffer = static_cast<const char*>(reply.ReadRawData(serializedGesture.size));
    serializedGesture.data = std::vector<char>(buffer, buffer + serializedGesture.size);

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
    int error = Remote()->SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_ALLOW_UPDATE),
        data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
    }
}

void FormRendererDispatcherProxy::DispatchSurfaceChangeEvent(float width, float height)
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

    MessageParcel reply;
    MessageOption option;
    int error = Remote()->SendRequest(
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

void FormRendererDispatcherProxy::SetVisibleChange(bool isVisible)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return;
    }

    if (!data.WriteBool(isVisible)) {
        HILOG_ERROR("write isVisible fail, action error");
        return;
    }

    MessageParcel reply;
    MessageOption option;
    int error = Remote()->SendRequest(
        static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_VISIBLE_CHANGE),
        data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
    }
}
} // namespace Ace
} // namespace OHOS
