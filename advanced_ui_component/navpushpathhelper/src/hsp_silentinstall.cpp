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
#include "advanced_ui_component/navpushpathhelper/include/hsp_silentinstall.h"
#include "advanced_ui_component/navpushpathhelper/include/silent_install_callback.h"

#include "iservice_registry.h"
#include "system_ability_definition.h"
#include "ability_runtime/context/context.h"
#include "want.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "core/components_ng/pattern/image/image_pattern.h"

namespace OHOS::NavPushPathHelper {

OHOS::sptr<OHOS::AppExecFwk::IBundleMgr> HspSilentInstall::GetBundleManager()
{
    auto systemAbilityMgr = OHOS::SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityMgr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "get system ability failed");
        return nullptr;
    }
    auto bundleObj = systemAbilityMgr->GetSystemAbility(OHOS::BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    if (!bundleObj) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "get bundle service failed");
        return nullptr;
    }
    return OHOS::iface_cast<OHOS::AppExecFwk::IBundleMgr>(bundleObj);
}

int32_t HspSilentInstall::SilentInstall(const std::string& moduleName, const std::function<void()>& callback,
    const std::function<void(int32_t, const std::string&)>& silentInstallErrorCallBack)
{
    auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, -1);
    
    auto runtimeContext = OHOS::Ace::Platform::AceContainer::GetRuntimeContext(pipeline->GetInstanceId());
    CHECK_NULL_RETURN(runtimeContext, -1);
    
    auto bundleName = runtimeContext->GetBundleName();
    if (bundleName.empty()) {
        return -1;
    }

    auto appInfo = runtimeContext->GetApplicationInfo();
    if (!appInfo) {
        return -1;
    }
    auto bms = GetBundleManager();
    CHECK_NULL_RETURN(bms, -1);

    OHOS::AAFwk::Want want;
    want.SetBundle(bundleName);
    want.SetModuleName(moduleName);
    OHOS::sptr<AtomicServiceStatusCallback> routerCallback = new AtomicServiceStatusCallback();
    routerCallback->SetActionEventHandler(callback);
    routerCallback->SetErrorEventHandler(silentInstallErrorCallBack);
    if (bms->SilentInstall(want, appInfo->uid / OHOS::AppExecFwk::Constants::BASE_USER_RANGE, routerCallback)) {
        TAG_LOGI(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "Begin to silent install");
        return 0;
    }
    return -1;
}

bool HspSilentInstall::IsHspExist(const std::string &moduleName, const std::string &pathName)
{
    auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, false);
    auto container = OHOS::Ace::Container::CurrentSafely();
    CHECK_NULL_RETURN(container, false);
    auto navigationRoute = container->GetNavigationRoute();
    CHECK_NULL_RETURN(navigationRoute, false);
    if (navigationRoute->IsNavigationItemExits(pathName)) {
        return true;
    }

    auto runtimeContext = OHOS::Ace::Platform::AceContainer::GetRuntimeContext(pipeline->GetInstanceId());
    CHECK_NULL_RETURN(runtimeContext, false);

    auto appInfo = runtimeContext->GetApplicationInfo();
    if (!appInfo) {
        return false;
    }
    std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
    auto res = std::any_of(moduleList.begin(), moduleList.end(), [moduleName](const auto &module) {
        return module.moduleName == moduleName;
    });
    if (res) {
        return true;
    }
    return false;
}
} // namespace OHOS::NavPushPathHelper