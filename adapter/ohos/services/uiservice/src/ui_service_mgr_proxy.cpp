/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "ui_service_mgr_proxy.h"

#include "ui_service_hilog.h"
#include "ui_service_mgr_errors.h"

namespace OHOS::Ace {
bool UIServiceMgrProxy::WriteInterfaceToken(MessageParcel& data)
{
    if (!data.WriteInterfaceToken(UIServiceMgrProxy::GetDescriptor())) {
        return false;
    }
    return true;
}

int32_t UIServiceMgrProxy::RegisterCallBack(const AAFwk::Want& want, const sptr<IUIService>& uiService)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!WriteInterfaceToken(data)) {
        return UI_SERVICE_PROXY_INNER_ERR;
    }
    if (!data.WriteParcelable(&want)) {
        return ERR_INVALID_VALUE;
    }
    if (uiService == nullptr) {
        return ERR_INVALID_VALUE;
    }
    if (!data.WriteRemoteObject(uiService->AsObject())) {
        return ERR_INVALID_VALUE;
    }
    int32_t error = Remote()->SendRequest(IUIServiceMgr::REGISTER_CALLBACK, data, reply, option);
    if (error != NO_ERROR) {
        LOGW("register callback fail, error: %d", error);
        return error;
    }
    return reply.ReadInt32();
}

int32_t UIServiceMgrProxy::UnregisterCallBack(const AAFwk::Want& want)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(data)) {
        return UI_SERVICE_PROXY_INNER_ERR;
    }
    data.WriteParcelable(&want);
    int32_t error = Remote()->SendRequest(IUIServiceMgr::UNREGISTER_CALLBACK, data, reply, option);
    if (error != NO_ERROR) {
        LOGW("unregister callback fail, error: %d", error);
        return error;
    }
    return reply.ReadInt32();
}

int32_t UIServiceMgrProxy::Push(const AAFwk::Want& want, const std::string& name, const std::string& jsonPath,
    const std::string& data, const std::string& extraData)
{
    MessageParcel dataParcel;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!WriteInterfaceToken(dataParcel)) {
        return UI_SERVICE_PROXY_INNER_ERR;
    }
    dataParcel.WriteParcelable(&want);
    if (!dataParcel.WriteString(name)) {
        return INVALID_DATA;
    }
    if (!dataParcel.WriteString(jsonPath)) {
        return INVALID_DATA;
    }
    if (!dataParcel.WriteString(data)) {
        return INVALID_DATA;
    }
    if (!dataParcel.WriteString(extraData)) {
        return INVALID_DATA;
    }
    int32_t error = Remote()->SendRequest(IUIServiceMgr::PUSH, dataParcel, reply, option);
    if (error != NO_ERROR) {
        return error;
    }
    return reply.ReadInt32();
}

int32_t UIServiceMgrProxy::Request(const AAFwk::Want& want, const std::string& name, const std::string& data)
{
    MessageParcel dataParcel;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(dataParcel)) {
        return UI_SERVICE_PROXY_INNER_ERR;
    }
    dataParcel.WriteParcelable(&want);

    if (!dataParcel.WriteString(name)) {
        return INVALID_DATA;
    }

    if (!dataParcel.WriteString(data)) {
        return INVALID_DATA;
    }

    int32_t error = Remote()->SendRequest(IUIServiceMgr::REQUEST, dataParcel, reply, option);
    if (error != NO_ERROR) {
        return error;
    }
    return reply.ReadInt32();
}

int32_t UIServiceMgrProxy::ReturnRequest(
    const AAFwk::Want& want, const std::string& source, const std::string& data, const std::string& extraData)
{
    MessageParcel dataParcel;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(dataParcel)) {
        return UI_SERVICE_PROXY_INNER_ERR;
    }
    dataParcel.WriteParcelable(&want);

    if (!dataParcel.WriteString(source)) {
        return INVALID_DATA;
    }

    if (!dataParcel.WriteString(data)) {
        return INVALID_DATA;
    }
    if (!dataParcel.WriteString(extraData)) {
        return INVALID_DATA;
    }
    int32_t error = Remote()->SendRequest(IUIServiceMgr::RETURN_REQUEST, dataParcel, reply, option);
    if (error != NO_ERROR) {
        return error;
    }
    return reply.ReadInt32();
}
} // namespace OHOS::Ace
