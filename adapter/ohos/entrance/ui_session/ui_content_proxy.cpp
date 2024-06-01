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

#include "interfaces/inner_api/ui_session/ui_content_proxy.h"

#include "adapter/ohos/entrance/ui_session/include/ui_service_hilog.h"

namespace OHOS::Ace {

int32_t UIContentServiceProxy::OnGetInspectorTree()
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("OnGetInspectorTree write interface token failed");
        return FAILED;
    }
    if (Remote()->SendRequest(UI_CONTENT_SERVICE_GET_TREE, data, reply, option) != ERR_NONE) {
        LOGW("OnGetInspectorTree send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::OnReportUnfocusEvent()
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("OnReportUnfocusEvent write interface token failed");
        return FAILED;
    }
    if (Remote()->SendRequest(UI_CONTENT_SERVICE_REPORT_EVENT, data, reply, option) != ERR_NONE) {
        LOGW("OnReportUnfocusEvent send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::RegisterRemoteObject(sptr<IRemoteObject> remoteObject)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("RegisterRemoteObject write interface token failed");
        return FAILED;
    }
    if (!data.WriteRemoteObject(remoteObject)) {
        LOGW("RegisterRemoteObject write remoteObject failed");
        return FAILED;
    }
    if (Remote()->SendRequest(UI_CONTENT_SERVICE_REGISTER, data, reply, option) != ERR_NONE) {
        LOGW("RegisterRemoteObject send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}
} // namespace OHOS::Ace