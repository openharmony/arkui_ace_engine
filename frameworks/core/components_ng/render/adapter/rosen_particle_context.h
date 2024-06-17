/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_PARTICLE_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_PARTICLE_CONTEXT_H

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/particle/particle_model.h"

namespace OHOS::Ace::NG {
class RosenRenderParticle : public AceType {
public:
    static void UpdateDisturbance(
        const RefPtr<FrameNode>& frameNode, const std::vector<ParticleDisturbance>& disturbanceArray);
    static void updateEmitterPosition(const RefPtr<FrameNode>& frameNode,
        std::vector<EmitterProperty>& props);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_PARTICLE_CONTEXT_H