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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_SURFACE_CONFIG_CLIENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_SURFACE_CONFIG_CLIENT_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_surface_config_interface.h"

namespace OHOS::Ace::NG {
class XComponentSurfaceConfigClient : public XComponentSurfaceConfigInterface {
public:
    explicit XComponentSurfaceConfigClient(const WeakPtr<XComponentPatternV2>& pattern)
        : weakXComponentPatternV2_(pattern)
    {}
    ~XComponentSurfaceConfigClient() override = default;
    int32_t SetSurfaceIsOpaque(bool isOpaque) override
    {
        auto xComponentPatternV2 = weakXComponentPatternV2_.Upgrade();
        CHECK_NULL_RETURN(xComponentPatternV2, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
        xComponentPatternV2->SetSurfaceIsOpaque(isOpaque);
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
private:
    WeakPtr<XComponentPatternV2> weakXComponentPatternV2_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_SURFACE_CONFIG_CLIENT_H
