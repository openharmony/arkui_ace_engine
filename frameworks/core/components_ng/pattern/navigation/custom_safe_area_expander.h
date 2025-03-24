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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_CUSTOM_SAFE_AREA_EXPANDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_CUSTOM_SAFE_AREA_EXPANDER_H

#include "base/memory/referenced.h"
#include "core/common/page_viewport_config.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class CustomSafeAreaExpander : public virtual AceType {
    DECLARE_ACE_TYPE(CustomSafeAreaExpander, AceType);

public:
    CustomSafeAreaExpander() = default;
    ~CustomSafeAreaExpander() override = default;

    bool RunCustomizeExpandIfNeeded(const RefPtr<FrameNode>& hostNode);
    virtual void SetPageViewportConfig(const RefPtr<PageViewportConfig>& config)
    {
        viewportConfig_ = config;
    }
    const RefPtr<PageViewportConfig>& GetPageViewportConfig() const
    {
        return viewportConfig_;
    }

protected:
    RefPtr<PageViewportConfig> viewportConfig_;
    bool isCustomExpandRunning_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_CUSTOM_SAFE_AREA_EXPANDER_H
