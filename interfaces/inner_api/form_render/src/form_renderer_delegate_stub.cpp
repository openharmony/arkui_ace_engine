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
#include "form_renderer_delegate_stub.h"

#include "form_renderer_hilog.h"
#include "core/accessibility/accessibility_manager.h"

namespace OHOS {
namespace Ace {
static std::mutex g_surfaceNodeMutex_;
static std::map<uint64_t, std::shared_ptr<Rosen::RSSurfaceNode>> g_surfaceNodeMap_;

FormRendererDelegateStub::FormRendererDelegateStub()
{
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_CREATE)] =
        &FormRendererDelegateStub::HandleOnSurfaceCreate;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_REUSE)] =
        &FormRendererDelegateStub::HandleOnSurfaceReuse;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_RELEASE)] =
        &FormRendererDelegateStub::HandleOnSurfaceRelease;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_ACTION_CREATE)] =
        &FormRendererDelegateStub::HandleOnActionEvent;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_ERROR)] =
        &FormRendererDelegateStub::HandleOnError;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_CHANGE)] =
        &FormRendererDelegateStub::HandleOnSurfaceChange;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_FORM_LINK_INFO_UPDATE)] =
        &FormRendererDelegateStub::HandleOnFormLinkInfoUpdate;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_FORMSURFACE_DETACH)] =
        &FormRendererDelegateStub::HandleOnSurfaceDetach;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_GET_RECT_RELATIVE_TO_WINDOW)] =
        &FormRendererDelegateStub::HandleOnGetRectRelativeToWindow;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_CHECK_MANAGER_DELEGATE)] =
        &FormRendererDelegateStub::HandleOnCheckManagerDelegate;
}

FormRendererDelegateStub::~FormRendererDelegateStub()
{
    memberFuncMap_.clear();
}

int FormRendererDelegateStub::OnRemoteRequest(
    uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    HILOG_DEBUG("FormRendererDelegateStub::OnReceived, code = %{public}u, flags= %{public}d.", code, option.GetFlags());
    std::u16string descriptor = FormRendererDelegateStub::GetDescriptor();
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

int FormRendererDelegateStub::HandleOnSurfaceCreate(MessageParcel& data, MessageParcel& reply)
{
    auto surfaceNode = Rosen::RSSurfaceNode::Unmarshalling(data);
    if (surfaceNode == nullptr) {
        HILOG_ERROR("surfaceNode is nullptr");
        return ERR_INVALID_VALUE;
    }
    {
        std::lock_guard<std::mutex> lock(g_surfaceNodeMutex_);
        g_surfaceNodeMap_[surfaceNode->GetId()] = surfaceNode;
    }
    HILOG_INFO("Stub create surfaceNode:%{public}s", std::to_string(surfaceNode->GetId()).c_str());
    std::unique_ptr<AppExecFwk::FormJsInfo> formJsInfo(data.ReadParcelable<AppExecFwk::FormJsInfo>());
    if (formJsInfo == nullptr) {
        HILOG_ERROR("formJsInfo is nullptr");
        return ERR_INVALID_VALUE;
    }

    std::shared_ptr<AAFwk::Want> want(data.ReadParcelable<AAFwk::Want>());
    if (want == nullptr) {
        HILOG_ERROR("want is nullptr");
        return ERR_INVALID_VALUE;
    }

    int32_t errCode = OnSurfaceCreate(surfaceNode, *formJsInfo, *want);
    reply.WriteInt32(errCode);
    return ERR_OK;
}

int32_t FormRendererDelegateStub::HandleOnSurfaceReuse(MessageParcel& data, MessageParcel& reply)
{
    uint64_t id = UINT64_MAX;
    data.ReadUint64(id);
    std::shared_ptr<Rosen::RSSurfaceNode> surfaceNode;
    {
        std::lock_guard<std::mutex> lock(g_surfaceNodeMutex_);
        auto iter = g_surfaceNodeMap_.find(id);
        if (iter != g_surfaceNodeMap_.end()) {
            surfaceNode = iter->second;
        }
    }
    if (surfaceNode == nullptr) {
        HILOG_ERROR("surfaceNode:%{public}s is nullptr", std::to_string(id).c_str());
        return ERR_INVALID_VALUE;
    }

    HILOG_INFO("Stub reuse surfaceNode:%{public}s", std::to_string(id).c_str());
    std::unique_ptr<AppExecFwk::FormJsInfo> formJsInfo(data.ReadParcelable<AppExecFwk::FormJsInfo>());
    if (formJsInfo == nullptr) {
        HILOG_ERROR("formJsInfo is nullptr");
        return ERR_INVALID_VALUE;
    }

    std::shared_ptr<AAFwk::Want> want(data.ReadParcelable<AAFwk::Want>());
    if (want == nullptr) {
        HILOG_ERROR("want is nullptr");
        return ERR_INVALID_VALUE;
    }

    int32_t errCode = OnSurfaceCreate(surfaceNode, *formJsInfo, *want);
    reply.WriteInt32(errCode);
    return ERR_OK;
}

int32_t FormRendererDelegateStub::HandleOnSurfaceDetach(MessageParcel& data, MessageParcel& reply)
{
    uint64_t id = UINT64_MAX;
    data.ReadUint64(id);

    HILOG_INFO("Stub detach surfaceNode:%{public}s", std::to_string(id).c_str());

    int32_t errCode = OnSurfaceDetach(id);
    reply.WriteInt32(errCode);
    return ERR_OK;
}

int32_t FormRendererDelegateStub::HandleOnSurfaceRelease(MessageParcel& data, MessageParcel& reply)
{
    uint64_t id = UINT64_MAX;
    data.ReadUint64(id);
    HILOG_INFO("Stub release surfaceNode:%{public}s start", std::to_string(id).c_str());
    {
        std::lock_guard<std::mutex> lock(g_surfaceNodeMutex_);
        auto iter = g_surfaceNodeMap_.find(id);
        if (iter != g_surfaceNodeMap_.end()) {
            HILOG_INFO("Stub release surfaceNode:%{public}s finish", std::to_string(id).c_str());
            g_surfaceNodeMap_.erase(iter);
        }
    }
    reply.WriteInt32(ERR_OK);
    return ERR_OK;
}

int FormRendererDelegateStub::HandleOnActionEvent(MessageParcel& data, MessageParcel& reply)
{
    std::string action = data.ReadString();
    int32_t errCode = OnActionEvent(action);
    reply.WriteInt32(errCode);
    return ERR_OK;
}

int32_t FormRendererDelegateStub::HandleOnError(MessageParcel& data, MessageParcel& reply)
{
    std::string code = data.ReadString();
    std::string msg = data.ReadString();
    int32_t errCode = OnError(code, msg);
    reply.WriteInt32(errCode);
    return ERR_OK;
}

int32_t FormRendererDelegateStub::HandleOnSurfaceChange(MessageParcel& data, MessageParcel& reply)
{
    float width = data.ReadFloat();
    float height = data.ReadFloat();
    float borderWidth = data.ReadFloat();

    OnSurfaceChange(width, height, borderWidth);
    reply.WriteInt32(ERR_OK);
    return ERR_OK;
}

int32_t FormRendererDelegateStub::HandleOnFormLinkInfoUpdate(MessageParcel& data, MessageParcel& reply)
{
    std::vector<std::string> formLinkInfos;
    data.ReadStringVector(&formLinkInfos);
    int32_t errCode = OnFormLinkInfoUpdate(formLinkInfos);
    reply.WriteInt32(errCode);
    return ERR_OK;
}

int32_t FormRendererDelegateStub::HandleOnGetRectRelativeToWindow(MessageParcel& data, MessageParcel& reply)
{
    AccessibilityParentRectInfo parentRectInfo;
    int32_t errCode = OnGetRectRelativeToWindow(parentRectInfo);
    reply.WriteInt32(errCode);
    reply.WriteInt32(parentRectInfo.top);
    reply.WriteInt32(parentRectInfo.left);
    reply.WriteFloat(parentRectInfo.scaleX);
    reply.WriteFloat(parentRectInfo.scaleY);
    return ERR_OK;
}

int32_t FormRendererDelegateStub::HandleOnCheckManagerDelegate(MessageParcel& data, MessageParcel& reply)
{
    bool checkFlag = true;
    int32_t errCode = OnCheckManagerDelegate(checkFlag);
    reply.WriteInt32(errCode);
    reply.WriteBool(checkFlag);
    return ERR_OK;
}
} // namespace Ace
} // namespace OHOS
