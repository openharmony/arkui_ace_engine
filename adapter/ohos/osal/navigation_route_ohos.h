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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_NAVIGATION_ROUTE_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_NAVIGATION_ROUTE_OHOS_H
#include <cstdint>

#include "bundlemgr/bundle_mgr_interface.h"

#include "frameworks/core/components_ng/pattern/navigation/navigation_route.h"

namespace OHOS::Ace {

class ACE_EXPORT NavigationRouteOhos : public NG::NavigationRoute {
    DECLARE_ACE_TYPE(NavigationRouteOhos, NG::NavigationRoute);

public:
    explicit NavigationRouteOhos(const std::string& bundleName)
    {
        InitRouteMap();
    }
    ~NavigationRouteOhos() = default;

    bool GetRouteItem(const std::string& name, NG::RouteItem& info) override;

    bool HasLoaded(const std::string& name) override
    {
        return std::find(names_.begin(), names_.end(), name) != names_.end();
    }

    int32_t LoadPage(const std::string& name) override;

    bool IsNavigationItemExits(const std::string& name) override;
 
    void OnPackageChange() override;

private:
    bool GetRouteItemFromBundle(const std::string& name, AppExecFwk::RouterItem& routeItem);
    void InitRouteMap();
    sptr<AppExecFwk::IBundleMgr> GetBundleManager();
    AppExecFwk::RouterItem GetRouteItem(const std::string name);
    std::vector<AppExecFwk::RouterItem> allRouteItems_;
    std::vector<std::string> names_;
};
} // namespace OHOS::Ace
#endif