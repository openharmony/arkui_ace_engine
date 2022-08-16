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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_ABILITY_COMPONENT_ABILITY_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_ABILITY_COMPONENT_ABILITY_COMPONENT_H

#include <string>

#include "core/components_v2/common/common_def.h"
#include "core/pipeline/base/render_component.h"

namespace OHOS::Ace::V2 {
class ACE_EXPORT AbilityComponent : public RenderComponent {
    DECLARE_ACE_TYPE(V2::AbilityComponent, RenderComponent);

public:
    AbilityComponent() = default;
    ~AbilityComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    ACE_DEFINE_COMPONENT_PROP(Want, std::string, "");
    ACE_DEFINE_COMPONENT_PROP(Width, Dimension, 0.0_px);
    ACE_DEFINE_COMPONENT_PROP(Height, Dimension, 0.0_px);

    ACE_DEFINE_COMPONENT_EVENT(OnConnected, void());
    ACE_DEFINE_COMPONENT_EVENT(OnDisconnected, void());

    void FireOnConnected()
    {
        if (eventOnConnected_) {
            (*eventOnConnected_)();
        }
    }

    void FireOnDisconnected()
    {
        if (eventOnDisconnected_) {
            (*eventOnDisconnected_)();
        }
    }
};
} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_ABILITY_COMPONENT_ABILITY_COMPONENT_H
