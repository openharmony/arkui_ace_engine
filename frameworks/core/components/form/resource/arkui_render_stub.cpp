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
#include "arkui_render_stub.h"

#include "appexecfwk_errors.h"
#include "hilog_wrapper.h"
#include "errors.h"
#include "ipc_skeleton.h"
#include "ipc_types.h"
#include "iremote_object.h"
#include "pointer_event.h"

namespace OHOS {
namespace Ace {
ArkUIRenderStub::ArkUIRenderStub()
{
    memberFuncMap_[static_cast<uint32_t>(IArkUIRender::Message::FORM_RENDER_DISPATCH_FORM_EVENT)] =
        &ArkUIRenderStub::HandleDispatchFormEvent;
}

ArkUIRenderStub::~ArkUIRenderStub()
{
    memberFuncMap_.clear();
}

int ArkUIRenderStub::OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    HILOG_ERROR("ArkUIRenderStub::OnReceived, code = %{public}u, flags= %{public}d.", code, option.GetFlags());
    std::u16string descriptor = ArkUIRenderStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (descriptor != remoteDescriptor) {
        HILOG_ERROR("%{public}s failed, local descriptor is not equal to remote", __func__);
        return -1;
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

int ArkUIRenderStub::HandleDispatchFormEvent(MessageParcel &data, MessageParcel &reply)
{
    HILOG_ERROR("HandleDispatchFormEvent");
    std::shared_ptr<MMI::PointerEvent> pointerEvent = MMI::PointerEvent::Create();
    if (pointerEvent == nullptr) {
        HILOG_ERROR("%{public}s, Create Pointer Event failed.", __func__);
        return -1;
    }

    int64_t formId = data.ReadInt64();
    if (!pointerEvent->ReadFromParcel(data)) {
        HILOG_ERROR("%{public}s, Read Pointer Event failed.", __func__);
        return -1;
    }

    DispatchFormEvent(formId, pointerEvent);
    reply.WriteInt32(ERR_OK);
    return ERR_OK;
}
}  // namespace Ace
}  // namespace OHOS