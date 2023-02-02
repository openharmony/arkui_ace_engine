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
#include "arkui_render_proxy.h"

#include "appexecfwk_errors.h"
#include "hilog_wrapper.h"
#include "pointer_event.h"
#include "string_ex.h"

namespace OHOS {
namespace Ace {
void ArkUIRenderProxy::DispatchFormEvent(
    int64_t formId, const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
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

    if (!data.WriteInt64(formId)) {
        HILOG_ERROR("Failed to write pointer event");
        return;
    }

    if (!pointerEvent->WriteToParcel(data)) {
        HILOG_ERROR("Failed to write pointer event");
        return;
    }

    MessageParcel reply;
    MessageOption option;
    int error = Remote()->SendRequest(
        static_cast<uint32_t>(IArkUIRender::Message::FORM_RENDER_DISPATCH_FORM_EVENT),
        data, reply, option);
    if (error != ERR_OK) {
        HILOG_ERROR("%{public}s, failed to SendRequest: %{public}d", __func__, error);
    }
}

bool ArkUIRenderProxy::WriteInterfaceToken(MessageParcel &data)
{
    if (!data.WriteInterfaceToken(ArkUIRenderProxy::GetDescriptor())) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return false;
    }
    return true;
}
} // namespace Ace
} // namespace OHOS
