/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ABILITY_COMPONENT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ABILITY_COMPONENT_PATTERN_H

#include "base/memory/referenced.h"
#include "core/common/window/window_extension_connection_proxy.h"
#include "core/components_ng/pattern/ability_component/ability_component_event_hub.h"
#include "core/components_ng/pattern/ability_component/ability_component_render_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT AbilityComponentPattern : public Pattern {
    DECLARE_ACE_TYPE(AbilityComponentPattern, Pattern);

public:
    AbilityComponentPattern() = default;
    ~AbilityComponentPattern() override
    {
        adapter_->RemoveExtension();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<AbilityComponentRenderProperty>();
    }
    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<AbilityComponentEventHub>();
    }
    // Called on main thread to check if need rerender of the content.
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void OnModifyDone() override;
    void FireConnect();
    void FireDisConnect();

private:
    void OnActive() override
    {
        if (adapter_) {
            adapter_->Show();
        }
        isActive_ = true;
    }

    void OnInActive() override
    {
        if (adapter_) {
            adapter_->Hide();
        }
        isActive_ = false;
    }

    bool isActive_ = false;
    bool hasConnectionToAbility_ = false;
    RefPtr<WindowExtensionConnectionAdapter> adapter_;
    ACE_DISALLOW_COPY_AND_MOVE(AbilityComponentPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ABILITY_COMPONENT_PATTERN_H
