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

#include "adapter/ohos/entrance/ui_session/test/mock_ui_sa_service.h"

#include "hilog/log.h"
#include "iremote_object.h"
#include "string_ex.h"
#include "ui_content_proxy.h"
#include "ui_content_service_interface.h"
#include "window_manager.h"
namespace OHOS::Ace {

const bool REGISTER_RESULT = SystemAbility::MakeAndRegisterAbility(&MockSaService::GetInstance());

MockSaService::MockSaService() : SystemAbility(SA_ID, true) {}

MockSaService& MockSaService::GetInstance()
{
    static MockSaService instance;
    return instance;
}
std::string MockSaService::ExecuteMethod()
{
    return "";
}
void MockSaService::OnStart()
{
    Publish(this);
}
void MockSaService::OnStop() {}
int32_t MockSaService::Dump(int32_t fd, const std::vector<std::u16string>& args)
{
    if (fd < 0) {
        return ERR_INVALID_DATA;
    }
    std::string message;
    std::vector<std::string> str8Args;
    for (const auto& arg : args) {
        const auto str = Str16ToStr8(arg);
        message.append(str);
        message.append(" ");
        str8Args.emplace_back(str);
    }
    OHOS::Rosen::FocusChangeInfo focusedWindowInfo;
    OHOS::Rosen::WindowManager::GetInstance().GetFocusWindowInfo(focusedWindowInfo);
    int32_t focusedWindowId = focusedWindowInfo.windowId_;
    sptr<Ace::IUiContentService> service = nullptr;
    sptr<IRemoteObject> tmpRemoteObj = nullptr;
    OHOS::Rosen::WindowManager::GetInstance().GetUIContentRemoteObj(focusedWindowId, tmpRemoteObj);
    if (tmpRemoteObj == nullptr) {
        dprintf(fd, "tmpRemoteObj is null");
        return ERR_OK;
    }
    service = iface_cast<Ace::IUiContentService>(tmpRemoteObj);
    if (service == nullptr) {
        dprintf(fd, "cast service failed");
        return ERR_OK;
    }
    auto cb = [fd](std::string res) { dprintf(fd, "connect success , foucs window info:[%s]", res.c_str()); };
    service->Connect(cb);
    if (!args.empty()) {
        message.pop_back();
    }
    return ERR_NONE;
}

} // namespace OHOS::Ace