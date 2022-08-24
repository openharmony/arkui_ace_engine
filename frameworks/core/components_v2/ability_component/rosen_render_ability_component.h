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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_ABILITY_COMPONENT_ROSEN_RENDER_ABILITY_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_ABILITY_COMPONENT_ROSEN_RENDER_ABILITY_COMPONENT_H

#include "core/components_v2/ability_component/render_ability_component.h"

namespace OHOS::Ace::V2 {

class RosenRenderAbilityComponent final : public RenderAbilityComponent {
    DECLARE_ACE_TYPE(RosenRenderAbilityComponent, V2::RenderAbilityComponent);

public:
    RosenRenderAbilityComponent();
    ~RosenRenderAbilityComponent() override;

    void Paint(RenderContext& context, const Offset& offset) override;
    void SyncGeometryProperties() override;
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_ABILITY_COMPONENT_ROSEN_RENDER_ABILITY_COMPONENT_H
