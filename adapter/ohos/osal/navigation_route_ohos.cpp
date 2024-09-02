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
#include "adapter/ohos/osal/navigation_route_ohos.h"
#include "base/error/error_code.h"

#include "iservice_registry.h"
#include "system_ability_definition.h"

namespace OHOS::Ace {

sptr<AppExecFwk::IBundleMgr> NavigationRouteOhos::GetBundleManager()
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityMgr) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "get system ability failed");
        return nullptr;
    }
    auto bundleObj = systemAbilityMgr->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    if (!bundleObj) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "get bundle service failed");
        return nullptr;
    }
    return iface_cast<AppExecFwk::IBundleMgr>(bundleObj);
}

void NavigationRouteOhos::InitRouteMap()
{
    auto bundleManager = GetBundleManager();
    if (!bundleManager) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "get bundle manager failed");
        return;
    }
    AppExecFwk::BundleInfo bundleInfo;
    if (bundleManager->GetBundleInfoForSelf(
        static_cast<int32_t>(AppExecFwk::GetBundleInfoFlag::GET_BUNDLE_INFO_WITH_HAP_MODULE) +
        static_cast<int32_t>(AppExecFwk::GetBundleInfoFlag::GET_BUNDLE_INFO_WITH_ROUTER_MAP),
        bundleInfo) != 0) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "get bundle info failed");
        return;
    }
    allRouteItems_ = bundleInfo.routerArray;
}

void NavigationRouteOhos::OnPackageChange()
{
    InitRouteMap();
}

bool NavigationRouteOhos::GetRouteItem(const std::string& name, NG::RouteItem& info)
{
    AppExecFwk::RouterItem routeItem;
    if (!GetRouteItemFromBundle(name, routeItem)) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "get route info %{public}s failed", name.c_str());
        return false;
    }
    info.name = routeItem.name;
    info.bundleName = routeItem.bundleName;
    info.moduleName = routeItem.moduleName;
    info.pageSourceFile = routeItem.pageSourceFile;
    info.data = routeItem.data;
    return true;
}

bool NavigationRouteOhos::GetRouteItemFromBundle(const std::string& name, AppExecFwk::RouterItem& routeItem)
{
    for (auto moduleIter = allRouteItems_.begin(); moduleIter != allRouteItems_.end(); moduleIter++) {
        if (moduleIter->name == name) {
            routeItem = *moduleIter;
            return true;
        }
    }
    TAG_LOGE(AceLogTag::ACE_NAVIGATION, "can't find name in config file: %{public}s", name.c_str());
    return false;
}

int32_t NavigationRouteOhos::LoadPage(const std::string& name)
{
    AppExecFwk::RouterItem item;
    if (!GetRouteItemFromBundle(name, item)) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "get route name failed");
        return ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED;
    }
    if (callback_ == nullptr) {
        return -1;
    }
    int32_t res = callback_(item.bundleName, item.moduleName, item.ohmurl, false);
    if (res == 0) {
        names_.emplace_back(name);
    }
    return res;
}

bool NavigationRouteOhos::IsNavigationItemExits(const std::string& name)
{
    if (HasLoaded(name)) {
        return true;
    }
    AppExecFwk::RouterItem item;
    if (GetRouteItemFromBundle(name, item)) {
        return true;
    }
    return false;
}
} // namespace OHOS::Ace