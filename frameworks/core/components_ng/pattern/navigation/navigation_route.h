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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_ROUTE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_ROUTE_H

#include <map>
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/event/package/package_change_listener.h"

namespace OHOS::Ace::NG {
using NavigationLoadPageCallback = std::function<int32_t(
    const std::string& bundleName, const std::string& moduleName, const std::string& pageName, bool isSingleton)>;
// navigation map info
struct RouteItem {
    std::optional<std::string> name;
    std::optional<std::string> bundleName;
    std::optional<std::string> moduleName;
    std::optional<std::string> buildFunction;
    std::optional<std::string> pageSourceFile;
    std::map<std::string, std::string> data;
};

class ACE_EXPORT NavigationRoute : public PackageChangeListener {
    DECLARE_ACE_TYPE(NavigationRoute, PackageChangeListener);
public:
    NavigationRoute() = default;
    ~NavigationRoute() = default;

    virtual bool GetRouteItem(const std::string& name, RouteItem& info)
    {
        return false;
    }

    virtual bool HasLoaded(const std::string& name)
    {
        return false;
    }

    virtual int32_t LoadPage(const std::string& name)
    {
        return 0;
    }

    void SetLoadPageCallback(NavigationLoadPageCallback callback)
    {
        callback_ = std::move(callback);
    }

    virtual bool IsNavigationItemExits(const std::string& name)
    {
        return false;
    }

    void OnPackageChange() override {}

protected:
    NavigationLoadPageCallback callback_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_PAGE_URL_CHECKER_H