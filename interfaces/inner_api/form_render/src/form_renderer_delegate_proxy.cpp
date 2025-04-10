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
#include "form_renderer_delegate_proxy.h"

#include "form_renderer_hilog.h"
#include "core/accessibility/accessibility_manager.h"

namespace OHOS {
namespace Ace {
FormRendererDelegateProxy::FormRendererDelegateProxy(const sptr<IRemoteObject>& impl)
    : IRemoteProxy<IFormRendererDelegate>(impl)
{}

int32_t FormRendererDelegateProxy::OnSurfaceCreate(const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
    const OHOS::AppExecFwk::FormJsInfo& formJsInfo, const AAFwk::Want& want)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return ERR_INVALID_VALUE;
    }
    if (surfaceNode == nullptr) {
        HILOG_ERROR("%{public}s fail, surfaceNode is nullptr", __func__);
        return ERR_INVALID_VALUE;
    }
    if (!surfaceNode->Marshalling(data)) {
        HILOG_ERROR("%{public}s fail, write surfaceNode error", __func__);
        return ERR_INVALID_VALUE;
    }
    if (!data.WriteParcelable(&formJsInfo)) {
        HILOG_ERROR("%{public}s fail, write formJsInfo error", __func__);
        return ERR_INVALID_VALUE;
    }
    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("%{public}s fail, write want error", __func__);
        return ERR_INVALID_VALUE;
    }
    HILOG_INFO("Proxy create surfaceNode:%{public}s", std::to_string(surfaceNode->GetId()).c_str());

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_CREATE), data, reply, option);
    if (error != NO_ERROR) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
        return error;
    }

    return reply.ReadInt32();
}

int32_t FormRendererDelegateProxy::OnSurfaceReuse(
    uint64_t surfaceId, const OHOS::AppExecFwk::FormJsInfo& formJsInfo, const AAFwk::Want& want)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return ERR_INVALID_VALUE;
    }
    data.WriteUint64(surfaceId);
    if (!data.WriteParcelable(&formJsInfo)) {
        HILOG_ERROR("%{public}s fail, write formJsInfo error", __func__);
        return ERR_INVALID_VALUE;
    }
    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("%{public}s fail, write want error", __func__);
        return ERR_INVALID_VALUE;
    }
    HILOG_INFO("Proxy reuse surfaceNode:%{public}s", std::to_string(surfaceId).c_str());

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_REUSE), data, reply, option);
    if (error != NO_ERROR) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
        return error;
    }

    return reply.ReadInt32();
}

int32_t FormRendererDelegateProxy::OnSurfaceDetach(uint64_t surfaceId)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return ERR_INVALID_VALUE;
    }
    data.WriteUint64(surfaceId);
    HILOG_INFO("Proxy detach surfaceNode:%{public}s", std::to_string(surfaceId).c_str());

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDelegate::Message::ON_FORMSURFACE_DETACH), data, reply, option);
    if (error != NO_ERROR) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
        return error;
    }

    return reply.ReadInt32();
}

int32_t FormRendererDelegateProxy::OnSurfaceRelease(uint64_t surfaceId)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return ERR_INVALID_VALUE;
    }
    data.WriteUint64(surfaceId);
    HILOG_INFO("Proxy release surfaceNode:%{public}s", std::to_string(surfaceId).c_str());

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_RELEASE), data, reply, option);
    if (error != NO_ERROR) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
        return error;
    }

    return reply.ReadInt32();
}

int32_t FormRendererDelegateProxy::OnActionEvent(const std::string& action)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return ERR_INVALID_VALUE;
    }

    if (!data.WriteString(action)) {
        HILOG_ERROR("%{public}s, write action error", __func__);
        return ERR_INVALID_VALUE;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDelegate::Message::ON_ACTION_CREATE), data, reply, option);
    if (error != NO_ERROR) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
        return error;
    }

    return reply.ReadInt32();
}

int32_t FormRendererDelegateProxy::OnError(const std::string& code, const std::string& msg)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return ERR_INVALID_VALUE;
    }

    if (!data.WriteString(code)) {
        HILOG_ERROR("%{public}s, write code error", __func__);
        return ERR_INVALID_VALUE;
    }

    if (!data.WriteString(msg)) {
        HILOG_ERROR("%{public}s, write msg error", __func__);
        return ERR_INVALID_VALUE;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(static_cast<uint32_t>(IFormRendererDelegate::Message::ON_ERROR), data, reply, option);
    if (error != NO_ERROR) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
        return error;
    }

    return reply.ReadInt32();
}

int32_t FormRendererDelegateProxy::OnSurfaceChange(float width, float height, float borderWidth)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return ERR_INVALID_VALUE;
    }

    if (!data.WriteFloat(width)) {
        HILOG_ERROR("write width fail, action error");
        return ERR_INVALID_VALUE;
    }

    if (!data.WriteFloat(height)) {
        HILOG_ERROR("write height fail, action error");
        return ERR_INVALID_VALUE;
    }

    if (!data.WriteFloat(borderWidth)) {
        HILOG_ERROR("write borderWidth fail, action error");
        return ERR_INVALID_VALUE;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_CHANGE), data, reply, option);
    if (error != NO_ERROR) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
    }
    return reply.ReadInt32();
}

int32_t FormRendererDelegateProxy::OnFormLinkInfoUpdate(const std::vector<std::string>& formLinkInfos)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return ERR_INVALID_VALUE;
    }

    if (!data.WriteStringVector(formLinkInfos)) {
        HILOG_ERROR("%{public}s, write formLinkInfos error", __func__);
        return ERR_INVALID_VALUE;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDelegate::Message::ON_FORM_LINK_INFO_UPDATE), data, reply, option);
    if (error != NO_ERROR) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
        return error;
    }

    return reply.ReadInt32();
}

int32_t FormRendererDelegateProxy::OnGetRectRelativeToWindow(AccessibilityParentRectInfo& parentRectInfo)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("failed to write interface token");
        return ERR_INVALID_VALUE;
    }

    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDelegate::Message::ON_GET_RECT_RELATIVE_TO_WINDOW), data, reply, option);
    if (error != NO_ERROR) {
        HILOG_ERROR("failed to SendRequest: %{public}d", error);
        return error;
    }

    int32_t errCode = reply.ReadInt32();
    if (errCode != ERR_OK) {
        HILOG_ERROR("return errCode: %{public}d", errCode);
        return errCode;
    }
    reply.ReadInt32(parentRectInfo.top);
    reply.ReadInt32(parentRectInfo.left);
    reply.ReadFloat(parentRectInfo.scaleX);
    reply.ReadFloat(parentRectInfo.scaleY);
    return ERR_OK;
}

bool FormRendererDelegateProxy::WriteInterfaceToken(MessageParcel& data)
{
    if (!data.WriteInterfaceToken(FormRendererDelegateProxy::GetDescriptor())) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return false;
    }
    return true;
}

int32_t FormRendererDelegateProxy::OnCheckManagerDelegate(bool &checkFlag)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("failed to write interface token");
        return ERR_INVALID_VALUE;
    }
    MessageParcel reply;
    MessageOption option;
    int32_t error = SendRequest(
        static_cast<uint32_t>(IFormRendererDelegate::Message::ON_CHECK_MANAGER_DELEGATE), data, reply, option);
    if (error != NO_ERROR) {
        HILOG_ERROR("failed to SendRequest: %{public}d", error);
        return error;
    }

    int32_t errCode = reply.ReadInt32();
    if (errCode != ERR_OK) {
        HILOG_ERROR("return errCode: %{public}d", errCode);
        return errCode;
    }
    reply.ReadBool(checkFlag);
    return ERR_OK;
}

int32_t FormRendererDelegateProxy::SendRequest(uint32_t code, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        HILOG_ERROR("remote is null");
        return IPC_PROXY_ERR;
    }
    return remote->SendRequest(code, data, reply, option);
}
} // namespace Ace
} // namespace OHOS
