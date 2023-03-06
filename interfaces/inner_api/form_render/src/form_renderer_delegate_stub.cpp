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

namespace OHOS {
namespace Ace {
FormRendererDelegateStub::FormRendererDelegateStub()
{
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_CREATE)] =
        &FormRendererDelegateStub::HandleOnSurfaceCreate;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_ACTION_CREATE)] =
        &FormRendererDelegateStub::HandleOnActionEvent;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDelegate::Message::ON_ERROR)] =
        &FormRendererDelegateStub::HandleOnError;
}

FormRendererDelegateStub::~FormRendererDelegateStub()
{
    memberFuncMap_.clear();
}

int FormRendererDelegateStub::OnRemoteRequest(
    uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    HILOG_DEBUG("FormRendererDelegateStub::OnReceived, code = %{public}u, flags= %{public}d.",
        code, option.GetFlags());
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

int FormRendererDelegateStub::HandleOnSurfaceCreate(MessageParcel &data, MessageParcel &reply)
{
    std::shared_ptr<Rosen::RSSurfaceNode> surfaceNode = Rosen::RSSurfaceNode::Unmarshalling(data);
    if (surfaceNode == nullptr) {
        HILOG_ERROR("surfaceNode is nullptr");
        return ERR_INVALID_VALUE;
    }

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

int FormRendererDelegateStub::HandleOnActionEvent(MessageParcel &data, MessageParcel &reply)
{
    std::string action = data.ReadString();
    int32_t errCode = OnActionEvent(action);
    reply.WriteInt32(errCode);
    return ERR_OK;
}

int32_t FormRendererDelegateStub::HandleOnError(MessageParcel &data, MessageParcel &reply)
{
    std::string code = data.ReadString();
    std::string msg = data.ReadString();
    int32_t errCode = OnError(code, msg);
    reply.WriteInt32(errCode);
    return ERR_OK;
}
}  // namespace Ace
}  // namespace OHOS