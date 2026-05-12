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

#include "adapter/preview/osal/navigation_route_preview.h"

#include "base/error/error_code.h"
#include "base/log/log.h"
#include <algorithm>

namespace OHOS::Ace {

NavigationRoutePreview::NavigationRoutePreview(const std::string& bundleName) : bundleName_(bundleName) {}

bool NavigationRoutePreview::GetRouteItem(const std::string& name, NG::RouteItem& info)
{
    AppExecFwk::RouterItem routeItem;
    if (!GetRouteItemFromBundle(name, routeItem)) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "GetRouteItem failed: %{public}s", name.c_str());
        return false;
    }
    info.name = routeItem.name;
    info.bundleName = routeItem.bundleName;
    info.moduleName = routeItem.moduleName;
    info.pageSourceFile = routeItem.pageSourceFile;
    info.data = routeItem.data;
    return true;
}

bool NavigationRoutePreview::HasLoaded(const std::string& name)
{
    return std::find(loadedNames_.begin(), loadedNames_.end(), name) != loadedNames_.end();
}

int32_t NavigationRoutePreview::LoadPage(const std::string& name)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "LoadPage: %{public}s (preview mode)", name.c_str());

    // Check if already loaded
    if (HasLoaded(name)) {
        TAG_LOGD(AceLogTag::ACE_NAVIGATION, "LoadPage: already loaded - %{public}s", name.c_str());
        return 0;
    }

    AppExecFwk::RouterItem item;
    if (!GetRouteItemFromBundle(name, item)) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "LoadPage failed: get route item failed - %{public}s", name.c_str());
        return ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED;
    }

    // Check if it's a plugin route (always false in preview mode)
    if (IsPluginRouteInfo(item.bundleName, item.moduleName)) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION,
            "load navdestination from plugin hsp, bundleName: %{public}s, moduleName: %{public}s",
            item.bundleName.c_str(), item.moduleName.c_str());
        if (callback_) {
            int32_t errorCode = callback_(item.bundleName, item.moduleName,
                item.ohmurl, false);
            if (errorCode == 0) {
                loadedNames_.insert(name);
            }
            return errorCode;
        }
    }

    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "load navdestination, bundleName: %{public}s, moduleName: %{public}s",
        item.bundleName.c_str(), item.moduleName.c_str());

    // Load from HAP module
    int32_t errorCode = LoadPageFromHapModule(name);
    if (errorCode == 0) {
        loadedNames_.insert(name);
    }
    return errorCode;
}

bool NavigationRoutePreview::IsNavigationItemExits(const std::string& name)
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

bool NavigationRoutePreview::IsPluginRouteInfo(const std::string& bundleName, const std::string& moduleName)
{
    TAG_LOGD(AceLogTag::ACE_NAVIGATION,
        "IsPluginRouteInfo: preview mode, always returns false (HSP plugins not supported)");
    // In preview mode, HSP plugins are not supported
    return false;
}

int32_t NavigationRoutePreview::LoadPageFromHapModule(const std::string& name)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "LoadPageFromHapModule: %{public}s (preview mode)", name.c_str());
    if (!callback_) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "LoadPageFromHapModule failed: no callback");
        return -1;
    }

    AppExecFwk::RouterItem routeItem;
    if (!GetRouteItemFromBundle(name, routeItem)) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "LoadPageFromHapModule failed: route not found - %{public}s", name.c_str());
        return ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED;
    }

    // In preview mode, pass empty bundleName to indicate internal navigation
    int32_t errorCode = callback_("", routeItem.moduleName,
        routeItem.ohmurl, false);
    if (errorCode == 0) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "LoadPageFromHapModule success: %{public}s", name.c_str());
    }
    return errorCode;
}

bool NavigationRoutePreview::GetRouteItemFromBundle(const std::string& name, AppExecFwk::RouterItem& routeItem)
{
    for (auto moduleIter = routeItems_.begin(); moduleIter != routeItems_.end(); moduleIter++) {
        if (moduleIter->name == name) {
            routeItem = *moduleIter;
            return true;
        }
    }
    TAG_LOGE(AceLogTag::ACE_NAVIGATION, "GetRouteItemFromBundle not found: %{public}s", name.c_str());
    return false;
}

void NavigationRoutePreview::InitRouteInfo(const std::vector<AppExecFwk::RouterItem>& routeItems)
{
    routeItems_ = routeItems;
}
} // namespace OHOS::Ace
