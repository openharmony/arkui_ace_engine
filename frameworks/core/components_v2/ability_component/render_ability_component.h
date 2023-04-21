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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_ABILITY_COMPONENT_RENDER_ABILITY_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_ABILITY_COMPONENT_RENDER_ABILITY_COMPONENT_H

#include <string>

#include "base/geometry/rect.h"
#include "core/common/window/window_extension_connection_proxy.h"
#include "core/components_v2/ability_component/ability_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::V2 {
class RenderAbilityComponent : public RenderNode {
    DECLARE_ACE_TYPE(V2::RenderAbilityComponent, RenderNode);

public:
    ~RenderAbilityComponent() override;

    static RefPtr<RenderNode> Create();
    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void Paint(RenderContext &context, const Offset &offset) override;
    void OnAppShow() override
    {
        if (adapter_) {
            adapter_->Show();
        }
    }

    void OnAppHide() override
    {
        if (adapter_) {
            adapter_->Hide();
        }
    }

    void FireConnect()
    {
        if (adapter_) {
            adapter_->UpdateRect(currentRect_);
        }
        hasConnectionToAbility_ = true;
        if (component_) {
            component_->FireOnConnected();
        } else {
            LOGI("ability component fire event fail");
        }
    }

    void FireDisconnect()
    {
        hasConnectionToAbility_ = false;
        if (component_) {
            component_->FireOnDisconnected();
        } else {
            LOGI("ability component fire event fail");
        }
    }

    void ConnectOrUpdateExtension();

    void OnPaintFinish() override;

private:
    Rect currentRect_;
    bool needLayout_ = false;
    bool hasConnectionToAbility_ = false;
    int32_t callbackId_ = 0;
    Dimension width_;
    Dimension height_;
    Offset globalOffsetExternal_;

    RefPtr<WindowExtensionConnectionAdapter> adapter_;
    RefPtr<V2::AbilityComponent> component_;
};
} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_ABILITY_COMPONENT_RENDER_ABILITY_COMPONENT_H
