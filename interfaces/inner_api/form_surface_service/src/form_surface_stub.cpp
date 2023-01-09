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

#include "form_surface_stub.h"
#include "form_surface_interface.h"
#include "hilog_wrapper.h"
#include "ipc_types.h"

namespace OHOS::Ace {

int32_t FormSurfaceServiceStub::OnRemoteRequest(
    uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    HILOG_DEBUG("UIServiceMgrStub::OnRemoteRequest, cmd = %d, flags= %d", code, option.GetFlags());
    std::u16string descriptor = FormSurfaceServiceStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (descriptor != remoteDescriptor) {
        HILOG_INFO("local descriptor is not equal to remote");
        return ERR_INVALID_STATE;
    }
    auto msgId = static_cast<FormSurfaceServiceMessage>(code);
    switch (msgId) {
        case FormSurfaceServiceMessage::PROCESS_ADD_SURFACE: {
            std::shared_ptr<AAFwk::Want> want(data.ReadParcelable<AAFwk::Want>());
            if (want == nullptr) {
                HILOG_ERROR("RegisterCallBackInner want is nullptr");
                return ERR_INVALID_VALUE;
            }
            std::unique_ptr<AppExecFwk::FormJsInfo> formJsInfo(data.ReadParcelable<AppExecFwk::FormJsInfo>());
            std::shared_ptr<Rosen::RSSurfaceNode> surfaceNode = Rosen::RSSurfaceNode::Unmarshalling(data);
            int32_t errCode = ProcessAddSurface(*want, *formJsInfo, surfaceNode);
            reply.WriteInt32(errCode);
            break;
        }
        default:
            HILOG_WARN("unknown transaction code %{public}d", code);
            return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
    }
    return 0;
};
} // namespace OHOS::Ace
