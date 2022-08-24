
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

#ifndef MOCK_FOUNDATION_AAFWK_MOCK_UI_MGR_SERVICE_H
#define MOCK_FOUNDATION_AAFWK_MOCK_UI_MGR_SERVICE_H

#include <gmock/gmock.h>
#define protected public
#define private public
#include "ui_mgr_service.h"
#include "ui_service_mgr_stub.h"
#include "event_handler.h"
#include "event_runner.h"

namespace OHOS {
namespace Ace {
class MockUIMgrService : public UIServiceMgrStub {
public:
    MockUIMgrService() = default;
    virtual ~MockUIMgrService() = default;

    MOCK_METHOD2(RegisterCallBackCall, int(const AAFwk::Want& want, const sptr<IUIService>& uiService));
    MOCK_METHOD1(UnregisterCallBackCall, int(const AAFwk::Want& want));
    MOCK_METHOD5(PushCall, int(const AAFwk::Want& want, const std::string& name,
        const std::string& jsonPath, const std::string& data, const std::string& extraData));
    MOCK_METHOD3(RequestCall, int(const AAFwk::Want& want, const std::string& name,
        const std::string& data));
    MOCK_METHOD4(ReturnRequestCall, void(const AAFwk::Want& want, const std::string& source,
        const std::string& data,  const std::string& extraData));

    MOCK_METHOD9(ShowDialog, int(const std::string& name,
        const std::string& params,
        uint32_t windowType,
        int x,
        int y,
        int width,
        int height,
        const sptr<OHOS::Ace::IDialogCallback>& dialogCallback,
        int* id));

    MOCK_METHOD1(CancelDialog, int(int id));

    MOCK_METHOD2(UpdateDialog, int(int id, const std::string& data));

    MOCK_METHOD2(AttachToUiService, int32_t(const sptr<IRemoteObject>& dialog, int32_t pid));

    MOCK_METHOD3(RemoteDialogCallback, int32_t(int32_t id, const std::string& event, const std::string& params));

    int RegisterCallBack(const AAFwk::Want& want,  const sptr<IUIService>& uiService)
    {
        RegisterCallBackCall(want, uiService);
        return 1;
    }
    int UnregisterCallBack(const AAFwk::Want& want)
    {
        UnregisterCallBackCall(want);
        return 1;
    }
    int Push(const AAFwk::Want& want, const std::string& name, const std::string& jsonPath, const std::string& data,
            const std::string& extraData)
    {
        PushCall(want, name, jsonPath, data, extraData);
        return 1;
    }
    int Request(const AAFwk::Want& want, const std::string& name, const std::string& data)
    {
        RequestCall(want, name, data);
        return 1;
    }
    int ReturnRequest(const AAFwk::Want& want, const std::string& source,  const std::string& data,
                    const std::string& extraData)
    {
        ReturnRequestCall(want, source, data, extraData);
        return 1;
    }
    void OnStart()
    {
        if (state_ == UIServiceRunningState::STATE_RUNNING) {
            HILOG_INFO("UIService Manager  has already started.");
            return;
        }
        HILOG_INFO("UIService Manager  started.");
        if (!Init()) {
            HILOG_ERROR("failed to init service.");
            return;
        }
        state_ = UIServiceRunningState::STATE_RUNNING;
        eventLoop_->Run();

        HILOG_INFO("UIService Manager  start success.");
    }
    void OnStop()
    {
        HILOG_INFO("stop service");
        eventLoop_.reset();
        handler_.reset();
        state_ = UIServiceRunningState::STATE_NOT_START;
    }
    /**
     * GetEventHandler, get the dataobs manager service's handler.
     * @return Returns EventHandler ptr.
     */
    std::shared_ptr<AppExecFwk::EventHandler> GetEventHandler()
    {
        return handler_;
    }

private:
    bool Init()
    {
        eventLoop_ = AppExecFwk::EventRunner::Create("UIMgrService");
        if (eventLoop_ == nullptr) {
            return false;
        }

        handler_ = std::make_shared<AppExecFwk::EventHandler>(eventLoop_);
        if (handler_ == nullptr) {
            return false;
        }

        HILOG_INFO("init success");
        return true;
    }

    std::shared_ptr<AppExecFwk::EventRunner> eventLoop_;
    std::shared_ptr<AppExecFwk::EventHandler> handler_;
    UIServiceRunningState state_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // MOCK_FOUNDATION_AAFWK_MOCK_UI_MGR_SERVICE_H
