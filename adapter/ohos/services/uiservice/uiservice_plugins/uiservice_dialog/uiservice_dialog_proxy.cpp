/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "uiservice_dialog_proxy.h"

#include <iremote_object.h>

#include "base/log/log.h"
#include "message_parcel.h"
#include "string_ex.h"

namespace OHOS::Ace {
UiServiceDialogProxy::UiServiceDialogProxy(const sptr<IRemoteObject>& impl) : IRemoteProxy<IUiServiceDialog>(impl) {}
UiServiceDialogProxy::~UiServiceDialogProxy() = default;

bool UiServiceDialogProxy::WriteInterfaceToken(MessageParcel& data)
{
    if (!data.WriteInterfaceToken(IUiServiceDialog::GetDescriptor())) {
        LOGE("write interface token failed");
        return false;
    }
    return true;
}

int32_t UiServiceDialogProxy::ShowDialog(
    const std::string& name,
    const std::string& params,
    uint32_t windowType,
    int x,
    int y,
    int width,
    int height,
    int32_t dialogId)
{
    LOGI("UiServiceDialogProxy Show Dialog Begin");
    MessageParcel dataParcel;
    MessageParcel reply;
    MessageOption option;

    if (!WriteInterfaceToken(dataParcel)) {
        return -1;
    }

    if (!dataParcel.WriteString(name)) {
        LOGE("fail to WriteString name");
        return INVALID_DATA;
    }

    if (!dataParcel.WriteString(params)) {
        LOGE("fail to WriteString params");
        return INVALID_DATA;
    }

    if (!dataParcel.WriteUint32(windowType)) {
        LOGE("fail to WriteUInt32 windowType");
        return INVALID_DATA;
    }

    if (!dataParcel.WriteInt32(x)) {
        LOGE("fail to WriteInt32 x");
        return INVALID_DATA;
    }

    if (!dataParcel.WriteInt32(y)) {
        LOGE("fail to WriteInt32 y");
        return INVALID_DATA;
    }
    if (!dataParcel.WriteInt32(width)) {
        LOGE("fail to WriteInt32 width");
        return INVALID_DATA;
    }

    if (!dataParcel.WriteInt32(height)) {
        LOGE("fail to WriteInt32 height");
        return INVALID_DATA;
    }

    if (!dataParcel.WriteInt32(dialogId)) {
        LOGE("fail to WriteInt32 height");
        return INVALID_DATA;
    }

    int error = Remote()->SendRequest(IUiServiceDialog::SHOW_DIALOG, dataParcel, reply, option);
    if (error != 0) {
        LOGE("Request fail, error: %{public}d", error);
        return error;
    }

    return reply.ReadInt32();
}

int32_t UiServiceDialogProxy::UpdateDialog(int32_t dialogId, const std::string& data)
{
    MessageParcel dataParcel;
    MessageParcel reply;
    MessageOption option;

    if (!WriteInterfaceToken(dataParcel)) {
        return -1;
    }

    if (!dataParcel.WriteInt32(dialogId)) {
        LOGE("fail to WriteString id");
        return -1;
    }

    if (!dataParcel.WriteString(data)) {
        LOGE("fail to WriteString data");
        return -1;
    }
    int error = Remote()->SendRequest(IUiServiceDialog::UPDATE_DIALOG, dataParcel, reply, option);
    if (error != 0) {
        LOGE("Request fail, error: %{public}d", error);
        return error;
    }
    return reply.ReadInt32();
}

int32_t UiServiceDialogProxy::CancelDialog(int32_t dialogId)
{
    MessageParcel dataParcel;
    MessageParcel reply;
    MessageOption option;

    if (!WriteInterfaceToken(dataParcel)) {
        return -1;
    }

    if (!dataParcel.WriteInt32(dialogId)) {
        LOGE("fail to WriteString id");
        return -1;
    }
    int error = Remote()->SendRequest(IUiServiceDialog::CANCEL_DIALOG, dataParcel, reply, option);
    if (error != 0) {
        LOGE("Request fail, error: %{public}d", error);
        return error;
    }
    return reply.ReadInt32();
}
}