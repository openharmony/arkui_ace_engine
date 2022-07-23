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

#ifndef OHOS_ACE_UI_SERVICE_DIALOG_IMPL_H
#define OHOS_ACE_UI_SERVICE_DIALOG_IMPL_H

#include <memory>
#include <unordered_map>
#include <iremote_object.h>
#include <iremote_stub.h>

#include "event_handler.h"
#include "event_runner.h"

#include "nocopyable.h"

#include "base/utils/macros.h"
#include "uiservice_dialog_interface.h"
#include "ui_dialog_base.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT UiServiceDialogImpl : public IRemoteStub<IUiServiceDialog> {
public:
    UiServiceDialogImpl();
    ~UiServiceDialogImpl() override;

    int OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option) override;
    static void InitAceDialog();

    int32_t ShowDialog(
        const std::string& name,
        const std::string& params,
        uint32_t windowType,
        int x,
        int y,
        int width,
        int height,
        int32_t dialogId) override;

    int32_t UpdateDialog(int32_t id, const std::string& data) override;
    int32_t CancelDialog(int32_t id) override;

private:
    static void* OpenSharedLib(const char* libName);
    static void* GetFunc(void* libHandel, const char* funName);

    void Init();
    bool InitSharedLib();
    bool ClearSharedLib();
    void RemoteDialogCallback(int32_t id, const std::string& event, const std::string& params);

    int32_t OnShowDialogRequest(MessageParcel& data, MessageParcel& reply);
    int32_t OnUpdateDialogRequest(MessageParcel& data, MessageParcel& reply);
    int32_t OnCancelDialogRequest(MessageParcel& data, MessageParcel& reply);

    using RequestFuncType = int32_t (UiServiceDialogImpl ::*)(MessageParcel& data, MessageParcel& reply);
    std::unordered_map<uint32_t, RequestFuncType> requestFuncMap_;

    std::shared_ptr<OHOS::AppExecFwk::EventRunner> eventRunner_;
    std::shared_ptr<OHOS::AppExecFwk::EventHandler> eventHandler_;

    void* libHandle_ = nullptr;
    UIDialogBase* uidialog_ = nullptr;

    static sptr<UiServiceDialogImpl> nowDialog_;
};
}

#endif