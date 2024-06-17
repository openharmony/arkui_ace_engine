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

#ifndef OHOS_ACE_UI_SERVICE_MANAGER_STUB_H
#define OHOS_ACE_UI_SERVICE_MANAGER_STUB_H

#include "ui_service_mgr_interface.h"

#include <iremote_object.h>
#include <iremote_stub.h>
#include <map>


namespace OHOS {
namespace Ace {
/**
 * @class UIServiceMgrStub
 * UIServiceMgrStub
 */
class UIServiceMgrStub : public IRemoteStub<IUIServiceMgr> {
public:
    UIServiceMgrStub();
    ~UIServiceMgrStub() override;
    int32_t OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option) override;

private:
    bool IsSystemApp();
    int32_t RegisterCallBackInner(MessageParcel& data, MessageParcel& reply);
    int32_t UnregisterCallBackInner(MessageParcel& data, MessageParcel& reply);
    int32_t PushInner(MessageParcel& data, MessageParcel& reply);
    int32_t RequestInner(MessageParcel& data, MessageParcel& reply);
    int32_t ReturnRequestInner(MessageParcel& data, MessageParcel& reply);

    using RequestFuncType = int32_t (UIServiceMgrStub ::*)(MessageParcel& data, MessageParcel& reply);
    std::map<uint32_t, RequestFuncType> requestFuncMap_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // OHOS_AAFWK_UI_SERVICE_MANAGER_STUB_H
