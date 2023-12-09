/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
#include "ui_service_stub.h"

namespace OHOS {
namespace Ace {
UIServiceStub::UIServiceStub()
{
    requestFuncMap_[UI_SERVICE_PUSH_CALL_BACK] = &UIServiceStub::OnPushCallBackInner;
    requestFuncMap_[UI_SERVICE_REQUEST_CALL_BACK] = &UIServiceStub::OnRequestCallBackInner;
    requestFuncMap_[UI_SERVICE_RETURN_REQUEST] = &UIServiceStub::OnReturnRequestInner;
}

UIServiceStub::~UIServiceStub()
{
    requestFuncMap_.clear();
}

int32_t UIServiceStub::OnRemoteRequest(
    uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    std::u16string descriptor = UIServiceStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (descriptor != remoteDescriptor) {
        return ERR_INVALID_STATE;
    }

    auto itFunc = requestFuncMap_.find(code);
    if (itFunc != requestFuncMap_.end()) {
        auto requestFunc = itFunc->second;
        if (requestFunc != nullptr) {
            return (this->*requestFunc)(data, reply);
        }
    }
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

int32_t UIServiceStub::OnPushCallBackInner(MessageParcel& data, MessageParcel& reply)
{
    std::shared_ptr<AAFwk::Want> want(data.ReadParcelable<AAFwk::Want>());
    if (want == nullptr) {
        return ERR_INVALID_VALUE;
    }
    const std::string& name = data.ReadString();
    const std::string& jsonPath = data.ReadString();
    const std::string& dataStr = data.ReadString();
    const std::string& extraData = data.ReadString();
    OnPushCallBack(*want, name, jsonPath, dataStr, extraData);
    return ERR_NONE;
}

int32_t UIServiceStub::OnReturnRequestInner(MessageParcel& data, MessageParcel& reply)
{
    std::shared_ptr<AAFwk::Want> want(data.ReadParcelable<AAFwk::Want>());
    if (want == nullptr) {
        return ERR_INVALID_VALUE;
    }
    const std::string& source = data.ReadString();
    const std::string& dataStr = data.ReadString();
    const std::string& extraData = data.ReadString();
    OnReturnRequest(*want, source, dataStr, extraData);
    return ERR_NONE;
}

int32_t UIServiceStub::OnRequestCallBackInner(MessageParcel& data, MessageParcel& reply)
{
    std::shared_ptr<AAFwk::Want> want(data.ReadParcelable<AAFwk::Want>());
    if (want == nullptr) {
        return ERR_INVALID_VALUE;
    }
    const std::string& name = data.ReadString();
    const std::string& dataStr = data.ReadString();
    OnRequestCallBack(*want, name, dataStr);
    return ERR_NONE;
}

void UIServiceCallbackRecipient::OnRemoteDied(const wptr<IRemoteObject>& remote)
{
    if (handler_) {
        handler_(remote);
    }
}

UIServiceCallbackRecipient::UIServiceCallbackRecipient(RemoteDiedHandler handler) : handler_(handler) {}

UIServiceCallbackRecipient::~UIServiceCallbackRecipient() = default;
}  // namespace Ace
}  // namespace OHOS
