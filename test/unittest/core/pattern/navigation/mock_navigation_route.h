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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_NAVIGATION_ROUTE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_NAVIGATION_ROUTE_H

#include "frameworks/core/components_ng/pattern/navigation/navigation_route.h"

namespace OHOS::Ace {
class MockNavigationRoute : public OHOS::Ace::NG::NavigationRoute {
    DECLARE_ACE_TYPE(MockNavigationRoute, OHOS::Ace::NG::NavigationRoute);

public:
    explicit MockNavigationRoute(const std::string& bundleName) {}

    ~MockNavigationRoute() = default;

    int32_t LoadPage(const std::string& name) override
    {
        if (std::find(names_.begin(), names_.end(), name) != names_.end()) {
            return 0;
        }
        if (name == "error") {
            return -1;
        }
        names_.push_back(name);
        return 0;
    }

    std::vector<std::string> GetPageNames() const
    {
        return names_;
    }

private:
    std::vector<std::string> names_;
};
} // namespace OHOS::Ace
#endif
