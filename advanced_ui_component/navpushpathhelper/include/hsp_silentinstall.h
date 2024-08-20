/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef ADVANCED_UI_COMPONENT_NAVPUSHPATHHELPER_INCLUDE_HSP_SILENTINSTALL_H
#define ADVANCED_UI_COMPONENT_NAVPUSHPATHHELPER_INCLUDE_HSP_SILENTINSTALL_H

#include "bundlemgr/bundle_mgr_interface.h"
#include "interfaces/inner_api/ace/ui_content.h"
namespace OHOS::NavPushPathHelper {

class HspSilentInstall {
public:
    HspSilentInstall() = default;
    ~HspSilentInstall() = default;

    static int32_t SilentInstall(const std::string& moduleName, const std::function<void()>& callback,
        const std::function<void(int32_t, const std::string&)>& silentInstallErrorCallBack);
    static bool IsHspExist(const std::string& moduleName, const std::string& pathName);

private:
    static OHOS::sptr<OHOS::AppExecFwk::IBundleMgr> GetBundleManager();
};
} // namespace OHOS::NavPushPathHelper
#endif