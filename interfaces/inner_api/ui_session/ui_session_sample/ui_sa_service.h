/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef UI_SA_SERVICE_H
#define UI_SA_SERVICE_H

#include "ui_sa_stub.h"
#include "system_ability.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {
class IUiContentService;
class UiSaService final : public SystemAbility, public UiSaStub {
public:
    static UiSaService& GetInstance();

    ~UiSaService() override = default;

    void OnStart() override;

    void OnStop() override;

    int32_t Dump(int32_t fd, const std::vector<std::u16string>& args) override;

    sptr<Ace::IUiContentService> getArkUIService(int32_t windowId);

    void HandleConnect(sptr<IUiContentService> service, std::vector<std::string> params);
    void HandleGetVisibleInspectorTree(sptr<IUiContentService> service, std::vector<std::string> params);
    void HandleGetCurrentPageName(sptr<IUiContentService> service, std::vector<std::string> params);
    void HandleSendCommand(sptr<IUiContentService> service, std::vector<std::string> params);
    void HandleSendCommandAsync(sptr<IUiContentService> service, std::vector<std::string> params);
    void HandleRegisterContentChangeCallback(sptr<IUiContentService> service, std::vector<std::string> params);
    void HandleUnregisterContentChangeCallback(sptr<IUiContentService> service, std::vector<std::string> params);
    void HandleGetCurrentImagesShowing(sptr<IUiContentService> service, std::vector<std::string> params);
    void HandleGetImagesById(sptr<IUiContentService> service, std::vector<std::string> params);

private:
    DECLEAR_SYSTEM_ABILITY(UiSaService);

    UiSaService();

    using DumpHandler = void(UiSaService::*)(sptr<IUiContentService>, std::vector<std::string>);
    static const std::map<std::string, DumpHandler> DUMP_MAP;

    std::mutex uiContentRemoteObjMapMtx_;
    std::map<int32_t, std::pair<sptr<IRemoteObject>, sptr<Ace::IUiContentService>>> uiContentRemoteObjMap_;
    std::string visibleInspectorTreeInfo_ = "";
};
} // namespace OHOS::Ace
#endif // UI_SA_SERVICE_H
