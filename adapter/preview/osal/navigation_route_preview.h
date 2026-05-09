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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_NAVIGATION_ROUTE_PREVIEW_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_NAVIGATION_ROUTE_PREVIEW_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <optional>

#include "foundation/ability/ability_runtime/frameworks/simulator/common/include/hap_module_info.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_route.h"


namespace OHOS::Ace {

/**
 * @class NavigationRoutePreview
 * @brief Preview implementation of NavigationRoute for previewer environment.
 *
 * This class provides a simplified implementation of NavigationRoute for the
 * previewer (DevEco Studio Preview). Unlike the OHOS implementation, it doesn't
 * have access to BundleManager and other system services, so it provides basic
 * stub/mock functionality for navigation routing in preview mode.
 */
class ACE_EXPORT NavigationRoutePreview : public NG::NavigationRoute {
    DECLARE_ACE_TYPE(NavigationRoutePreview, NG::NavigationRoute);

public:
    explicit NavigationRoutePreview(const std::string& bundleName);

    ~NavigationRoutePreview() override = default;

    /**
     * @brief Get route item by name.
     * @param name The route name.
     * @param info The route item to be filled.
     * @return true if found, false otherwise.
     */
    bool GetRouteItem(const std::string& name, NG::RouteItem& info) override;

    /**
     * @brief Check if a page has been loaded.
     * @param name The route name.
     * @return true if loaded, false otherwise.
     */
    bool HasLoaded(const std::string& name) override;

    /**
     * @brief Load a page by route name.
     * @param name The route name.
     * @return 0 on success, error code on failure.
     */
    int32_t LoadPage(const std::string& name) override;

    /**
     * @brief Init Navigation Route info from preview
     */
    void InitRouteInfo(const std::vector<OHOS::AppExecFwk::RouterItem>& routeItems);

    bool IsNavigationItemExits(const std::string& name) override;

private:
    /**
     * @brief Check if the route is from a plugin HSP.
     * NOTE: In preview mode, always returns false as HSP plugins are not supported.
     * @param bundleName The bundle name.
     * @param moduleName The module name.
     * @return true if it's a plugin route, false otherwise.
     */
    bool IsPluginRouteInfo(const std::string& bundleName, const std::string& moduleName);

    /**
     * @brief Load page from HAP module.
     * NOTE: In preview mode, routes are loaded from manually added route items.
     * @param name The route name.
     * @return 0 on success, error code on failure.
     */
    int32_t LoadPageFromHapModule(const std::string& name);

    /**
     * @brief Get route item from bundle.
     * @param name The route name.
     * @param routeItem The route item to be filled.
     * @return true if found, false otherwise.
     */
    bool GetRouteItemFromBundle(const std::string& name, AppExecFwk::RouterItem& routeItem);

    std::string bundleName_;
    std::unordered_set<std::string> loadedNames_;
    std::vector<OHOS::AppExecFwk::RouterItem> routeItems_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_NAVIGATION_ROUTE_PREVIEW_H
