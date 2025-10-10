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

#include "iservice_registry.h"
#include "system_ability_definition.h"

#include "base/error/error_code.h"
#include "base/log/log.h"

namespace OHOS::Ace {
NavigationRouteOhos::NavigationRouteOhos(const std::string& bundleName)
{
    InitRouteMap();
    RegisteHspUpdateCallback();
}

NavigationRouteOhos::~NavigationRouteOhos()
{
    auto bundleManager = GetBundleManager();
    if (bundleManager && navigationBundleEventCallback_) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "unregiste plugin change callback");
        bundleManager->UnregisterPluginEventCallback(navigationBundleEventCallback_);
    }
}

void NavigationRouteOhos::RegisteHspUpdateCallback()
{
    auto bundleManager = GetBundleManager();
    if (!bundleManager) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "[%{public}s] get bundle manager failed", __func__);
        return;
    }
    navigationBundleEventCallback_ = new NavigationBundleEventCallback(WeakClaim(this));
    bundleManager->RegisterPluginEventCallback(navigationBundleEventCallback_);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "subscribe hsp Update successfully");
}

void NavigationBundleEventCallback::OnReceiveEvent(const EventFwk::CommonEventData eventData)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "on receive bundle change event");
    auto navigationRoute = navigationRoute_.Upgrade();
    if (!navigationRoute) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "update route map failed cause invalid navigaiton route");
        return;
    }
    navigationRoute->InitRouteMap();
}

bool NavigationRouteOhos::IsPluginRouteInfo(const std::string& bundleName, const std::string& moduleName)
{
    for (auto pluginHspInfo: pluginHspInfos_) {
        if (bundleName == pluginHspInfo.bundleName && moduleName == pluginHspInfo.moduleName) {
            return true;
        }
    }
    return false;
}

void NavigationRouteOhos::UpdatePluginHspInfos(sptr<AppExecFwk::IBundleMgr> bundleManager)
{
    if (!bundleManager) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "[%{public}s] get bundle manager failed", __func__);
        return;
    }
    pluginHspInfos_.clear();
    std::vector<AppExecFwk::PluginBundleInfo> infos;
    bundleManager->GetPluginInfosForSelf(infos);
    if (infos.empty()) {
        return;
    }
    for (auto pluginBundleInfo: infos) {
        if (pluginBundleInfo.pluginModuleInfos.empty()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION,
                "current plugin bundle has no module: %{public}s", pluginBundleInfo.pluginBundleName.c_str());
            continue;
        }
        for (auto pluginModuleInfo: pluginBundleInfo.pluginModuleInfos) {
            pluginHspInfos_.push_back(PluginHspInfo(pluginBundleInfo.pluginBundleName, pluginModuleInfo.moduleName));
        }
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "update plugin hsp info success, size: %{public}zu", pluginHspInfos_.size());
}

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
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "[%{public}s] get bundle manager failed", __func__);
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
    moduleInfos_ = bundleInfo.hapModuleInfos;
    UpdatePluginHspInfos(bundleManager);
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
    if (IsPluginRouteInfo(item.bundleName, item.moduleName)) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION,
            "load navdestination from plugin hsp, bundleName: %{public}s, moduleName: %{public}s",
            item.bundleName.c_str(), item.moduleName.c_str());
        // pass its real bundleName means navigate between two applications.
        int32_t errorCode = callback_(item.bundleName, item.moduleName, item.ohmurl, false);
        if (errorCode == 0) {
            names_.emplace_back(name);
        }
        return errorCode;
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "load navdestination, bundleName: %{public}s, moduleName: %{public}s",
        item.bundleName.c_str(), item.moduleName.c_str());
    // pass emptry string as bundleName means navigate inside current application.
    int32_t errorCode = callback_("", item.moduleName, item.ohmurl, false);
    if (errorCode == 0) {
        names_.emplace_back(name);
    }
    return LoadPageFromHapModule(name);
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

int32_t NavigationRouteOhos::LoadPageFromHapModule(const std::string& name)
{
    int32_t errorCode = -1;
    if (!callback_) {
        return errorCode;
    }
    for (auto hapIter = moduleInfos_.begin(); hapIter != moduleInfos_.end(); hapIter++) {
        auto routerInfo = hapIter->routerArray;
        for (auto routerIter = routerInfo.begin(); routerIter != routerInfo.end(); routerIter++) {
            if (routerIter->name != name) {
                continue;
            }
            // pass bundleName as emptry string means navigate inside current application.
            errorCode = callback_("", routerIter->moduleName, routerIter->ohmurl, false);
            TAG_LOGD(AceLogTag::ACE_NAVIGATION, "load current destination name: %{public}s, ohmurl: %{public}s",
                name.c_str(), routerIter->ohmurl.c_str());
            if (errorCode == 0) {
                return 0;
            }
            break;
        }
    }
    return errorCode;
}
} // namespace OHOS::Ace