/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_CONTENT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_CONTENT_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/custom_safe_area_expander.h"

namespace OHOS::Ace::NG {
class NavDestinationContentPattern : public LinearLayoutPattern, public CustomSafeAreaExpander {
    DECLARE_ACE_TYPE(NavDestinationContentPattern, LinearLayoutPattern, CustomSafeAreaExpander);

public:
    explicit NavDestinationContentPattern(bool isVertical) : LinearLayoutPattern(isVertical) {}
    ~NavDestinationContentPattern() override = default;

private:
    bool CustomizeExpandSafeArea() override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        return RunCustomizeExpandIfNeeded(host);
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_CONTENT_PATTERN_H
