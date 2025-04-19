/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_ADAPTER_OHOS_SERVICES_UISERVICE_UI_MGR_SERVICE_IDL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_ADAPTER_OHOS_SERVICES_UISERVICE_UI_MGR_SERVICE_IDL_H

#include <memory>
#include <singleton.h>
#include <thread_ex.h>
#include <unordered_map>

#include "element_name.h"
#include "event_handler.h"
#include "event_runner.h"
#include "iremote_object.h"

#include "system_ability.h"
#include "ui_service_mgr_new_stub.h"

namespace OHOS {
namespace Ace {
using EventRunner = OHOS::AppExecFwk::EventRunner;
using EventHandler = OHOS::AppExecFwk::EventHandler;
enum class UIServiceRunningState { STATE_NOT_START, STATE_RUNNING };

class UIMgrServiceIdl : public SystemAbility,
                        public UIServiceMgrNewStub,
                        public std::enable_shared_from_this<UIMgrServiceIdl> {
    DECLARE_DELAYED_SINGLETON(UIMgrServiceIdl)
    DECLEAR_SYSTEM_ABILITY(UIMgrService)
public:
    void OnStart() override;
    void OnStop() override;
    UIServiceRunningState QueryServiceState() const;

    int32_t RegisterCallBack(const AAFwk::Want& want, const sptr<IUIServiceNew>& uiService) override;
    int32_t UnregisterCallBack(const AAFwk::Want& want) override;
    int32_t Push(const AAFwk::Want& want, const std::string& name, const std::string& jsonPath,
        const std::string& data, const std::string& extraData) override;

    int32_t Request(const AAFwk::Want& want, const std::string& name, const std::string& data) override;
    int32_t ReturnRequest(const AAFwk::Want& want, const std::string& source, const std::string& data,
        const std::string& extraData) override;

    int32_t Dump(int32_t fd, const std::vector<std::u16string>& args) override;

    int32_t OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option) override;

private:
    const char* IpcCodeToString(uint32_t code);
    bool IsSystemApp();
    bool Init();
    bool CheckCallBackFromMap(const std::string& key);
    int32_t HandleRegister(const AAFwk::Want& want,  const sptr<IUIServiceNew>& uiService);
    int32_t HandleUnregister(const AAFwk::Want& want);

    std::string GetCallBackKeyStr(const AAFwk::Want& want);
    std::shared_ptr<EventRunner> eventLoop_;
    std::shared_ptr<EventHandler> handler_;
    UIServiceRunningState state_;

    std::map<std::string, sptr<IUIServiceNew>> callbackMap_;
    std::recursive_mutex uiMutex_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ARKUI_ACE_ENGINE_ADAPTER_OHOS_SERVICES_UISERVICE_UI_MGR_SERVICE_IDL_H