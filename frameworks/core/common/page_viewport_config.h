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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PAGE_VIEWPORT_CONFIG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PAGE_VIEWPORT_CONFIG_H

#include <string>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/display_info.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace {
class PageViewportConfig : public AceType {
    DECLARE_ACE_TYPE(PageViewportConfig, AceType);
public:
    PageViewportConfig() = default;
    ~PageViewportConfig() = default;

    virtual RefPtr<PageViewportConfig> Clone() const
    {
        return nullptr;
    }

    virtual int32_t GetWidth() const
    {
        return -1;
    }
    virtual DisplayOrientation GetOrientation() const
    {
        return DisplayOrientation::PORTRAIT;
    }
    virtual NG::LayoutConstraintF CreateRootLayoutConstraint() const
    {
        return NG::LayoutConstraintF();
    }
    virtual NG::SafeAreaInsets GetSafeArea() const
    {
        return NG::SafeAreaInsets();
    }
    virtual void ApplySafeArea() {}
    virtual void RestoreSafeArea() {}
};

class ScopePageViewportConfig {
public:
    ScopePageViewportConfig(const RefPtr<PageViewportConfig>& config) : config_(config)
    {
        if (config_) {
            config_->ApplySafeArea();
        }
    }
    ~ScopePageViewportConfig()
    {
        if (config_) {
            config_->RestoreSafeArea();
        }
    }

    ScopePageViewportConfig(const ScopePageViewportConfig&) = delete;
    ScopePageViewportConfig& operator= (const ScopePageViewportConfig&) = delete;
    ScopePageViewportConfig(ScopePageViewportConfig&&) = delete;
    ScopePageViewportConfig& operator= (ScopePageViewportConfig&&) = delete;

private:
    RefPtr<PageViewportConfig> config_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PAGE_VIEWPORT_CONFIG_H
