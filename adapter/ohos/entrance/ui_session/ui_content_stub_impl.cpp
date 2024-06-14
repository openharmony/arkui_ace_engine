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

#include "interfaces/inner_api/ui_session/ui_content_stub_impl.h"

#include "adapter/ohos/entrance/ui_session/include/ui_service_hilog.h"

namespace OHOS::Ace {

int32_t UIContentServiceStubImpl::OnGetInspectorTreeInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::OnReportUnfocusEventInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterRemoteObjectInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    sptr<IRemoteObject> SAObject = data.ReadRemoteObject();
    if (SAObject == nullptr) {
        LOGW("RemoteObject is null,register remote object failed");
        return FAILED;
    }
    SAObject_ = SAObject;
    return NO_ERROR;
}
} // namespace OHOS::Ace