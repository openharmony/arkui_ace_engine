/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "frameworks/base/geometry/rect.h"
#include "frameworks/base/memory/referenced.h"
#include "frameworks/core/common/window_ng/window_extension_connection_proxy_ng.h"
#include "frameworks/core/components_ng/pattern/ability_component/ability_component_event_hub.h"
#include "frameworks/core/components_ng/pattern/ability_component/ability_component_layout_algorithm.h"
#include "frameworks/core/components_ng/pattern/ability_component/ability_component_render_property.h"
#include "frameworks/core/components_ng/pattern/pattern.h"
#include "frameworks/core/components_ng/pattern/ui_extension/ui_extension_pattern.h"
#include "frameworks/core/components_ng/property/property.h"
#include "frameworks/core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT AbilityComponentPattern : public UIExtensionPattern {
    DECLARE_ACE_TYPE(AbilityComponentPattern, UIExtensionPattern);

public:
    AbilityComponentPattern(const std::string& bundleName, const std::string& abilityName)
        : UIExtensionPattern(Ace::WantWrap::CreateWantWrap("AbilityComp", abilityName))
    {
        bundleName_ = bundleName;
        abilityName_ = abilityName;
    }

    ~AbilityComponentPattern() override
    {
        if (adapter_) {
            adapter_->RemoveExtension();
        }
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<AbilityComponentRenderProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<AbilityComponentEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<AbilityComponentLayoutAlgorithm>();
    }

    void FireConnect();
    void FireDisConnect();
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAreaChangedInner() override;

private:
    void OnModifyDone() override;

    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleTouchEvent(const TouchEventInfo& info);

    void OnActive() override
    {
        if (!isActive_) {
            if (adapter_) {
                adapter_->Show();
            }
            isActive_ = true;
        }
    }

    void OnInActive() override
    {
        if (isActive_) {
            if (adapter_) {
                adapter_->Hide();
            }
            isActive_ = false;
        }
    }

    void OnWindowShow() override
    {
        if (!isActive_) {
            if (adapter_) {
                adapter_->Show();
            }
            isActive_ = true;
        }
    }

    void OnWindowHide() override
    {
        if (isActive_) {
            if (adapter_) {
                adapter_->Hide();
            }
            isActive_ = false;
        }
    }

    void UpdateWindowRect();

    bool isActive_ = false;
    bool hasConnectionToAbility_ = false;
    Rect lastRect_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<WindowExtensionConnectionAdapterNG> adapter_;
    std::string bundleName_;
    std::string abilityName_;
    ACE_DISALLOW_COPY_AND_MOVE(AbilityComponentPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ABILITY_COMPONENT_PATTERN_H
