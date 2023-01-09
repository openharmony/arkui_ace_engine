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

#include "form_surface_proxy.h"
#include "hilog_wrapper.h"
#include "ipc_types.h"

namespace OHOS::Ace {
int32_t FormSurfaceServiceProxy::ProcessAddSurface(const AAFwk::Want& want, 
    const OHOS::AppExecFwk::FormJsInfo& formJsInfo, const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;

    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return ERR_INVALID_VALUE;
    }

    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("register callback fail, want error");
        return ERR_INVALID_VALUE;
    }
    if (!data.WriteParcelable(&formJsInfo)) {
        HILOG_ERROR("%{public}s fail, write formJsInfo error", __func__);
        return ERR_INVALID_VALUE;
    }
    if (surfaceNode == nullptr || !surfaceNode->Marshalling(data)) {
        HILOG_ERROR("%{public}s fail, write surfaceNode error", __func__);
        return ERR_INVALID_VALUE;
    }
    int32_t error = Remote()->SendRequest(
        static_cast<uint32_t>(FormSurfaceServiceMessage::PROCESS_ADD_SURFACE), data, reply, option);
    if (error != NO_ERROR) {
        HILOG_ERROR("register callback fail, error: %d", error);
        return error;
    }
    return reply.ReadInt32();
}

bool  FormSurfaceServiceProxy::WriteInterfaceToken(MessageParcel &data)
{
    if (!data.WriteInterfaceToken(FormSurfaceServiceProxy::GetDescriptor())) {
        HILOG_ERROR("%{public}s, failed to write interface token", __func__);
        return false;
    }
    return true;
}
} // namespace OHOS::Ace
