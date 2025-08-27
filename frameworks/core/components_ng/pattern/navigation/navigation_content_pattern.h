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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_CONTENT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_CONTENT_PATTERN_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/navigation/custom_safe_area_expander.h"
#include "core/components_ng/pattern/navigation/navigation_content_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
// NavigationContentPattern is the content container for navigation destination
class ACE_EXPORT NavigationContentPattern : public Pattern, public CustomSafeAreaExpander {
    DECLARE_ACE_TYPE(NavigationContentPattern, Pattern, CustomSafeAreaExpander);

public:
    NavigationContentPattern() = default;
    ~NavigationContentPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<NavigationContentLayoutAlgorithm>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    void OnAttachToFrameNode() override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->GetRenderContext()->SetClipToBounds(true);
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
                .edges = SAFE_AREA_EDGE_ALL };
            host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
        }
    }

    bool CustomizeExpandSafeArea() override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        return RunCustomizeExpandIfNeeded(host);
    }

    bool IsEnableMatchParent() override
    {
        return true;
    }

    bool IsEnableFix() override
    {
        return true;
    }

    bool IsEnableChildrenMatchParent() override
    {
        return true;
    }

    ACE_DISALLOW_COPY_AND_MOVE(NavigationContentPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_CONTENT_PATTERN_H
