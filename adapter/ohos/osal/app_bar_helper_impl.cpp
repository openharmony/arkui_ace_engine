/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/common/app_bar_helper.h"

#include "bundlemgr/bundle_mgr_interface.h"
#include "iservice_registry.h"
#include "system_ability_definition.h"

namespace OHOS::Ace {

std::string AppBarHelper::QueryAppGalleryBundleName()
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    CHECK_NULL_RETURN(systemAbilityMgr, "");

    auto bundleObj = systemAbilityMgr->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    CHECK_NULL_RETURN(bundleObj, "");

    auto bundleMgr = iface_cast<AppExecFwk::IBundleMgr>(bundleObj);
    CHECK_NULL_RETURN(bundleMgr, "");

    std::string bundleName = "";
    auto result = bundleMgr->QueryAppGalleryBundleName(bundleName);
    if (!result) {
        LOGE("Query BundleName fail!");
    } else {
        LOGI("BundleName: %{public}s", bundleName.c_str());
    }
    return bundleName;
}

} // namespace OHOS::Ace