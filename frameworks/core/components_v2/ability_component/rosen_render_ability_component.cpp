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

#include "core/components_v2/ability_component/rosen_render_ability_component.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_surface_node.h"
#endif

namespace OHOS::Ace::V2 {

RosenRenderAbilityComponent::RosenRenderAbilityComponent() = default;
RosenRenderAbilityComponent::~RosenRenderAbilityComponent() = default;

void RosenRenderAbilityComponent::Paint(RenderContext& context, const Offset& offset)
{
    SyncGeometryProperties();
    V2::RenderAbilityComponent::Paint(context, offset);
}

void RosenRenderAbilityComponent::SyncGeometryProperties()
{
    if (!IsTailRenderNode()) {
        return;
    }
    auto rsNode = GetRSNode();
    if (!rsNode) {
        return;
    }

    auto size = GetLayoutSize();
    rsNode->SetBounds(0.0, 0.0, size.Width(), size.Height());
}

} // namespace OHOS::Ace::V2
