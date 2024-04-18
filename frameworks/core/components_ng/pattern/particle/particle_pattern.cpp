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

#include "core/components_ng/pattern/particle/particle_pattern.h"

#include "core/components_ng/render/adapter/rosen_particle_context.h"

namespace OHOS::Ace::NG {
class RosenRenderParticle;
void ParticlePattern::OnVisibleChange(bool isVisible)
{
    if (HaveUnVisibleParent() == !isVisible) {
        return;
    }
    SetHaveUnVisibleParent(!isVisible);
    if (isVisible) {
        auto host = GetHost();
        auto context = host->GetRenderContext();
        context->OnParticleOptionArrayUpdate(context->GetParticleOptionArray().value());
    }
}

void ParticlePattern::OnAttachToMainTree()
{
    auto host = GetHost();
    auto parent = host->GetParent();
    while (parent) {
        if (InstanceOf<FrameNode>(parent)) {
            auto frameNode = DynamicCast<FrameNode>(parent);
            if (!frameNode->IsVisible()) {
                SetHaveUnVisibleParent(true);
                return;
            }
        }
        parent = parent->GetParent();
    }
}

void ParticlePattern::UpdateDisturbance(const std::vector<ParticleDisturbance>& disturbanceArray)
{
    if (disturbanceArray.size() == 0) {
        return;
    }
    LOGW("wjh SIZE IS %{public}d", static_cast<int>(disturbanceArray.size()));
    for (auto d : disturbanceArray) {
        LOGW("wjh strength: %{public}f, size[0]:%{public}d, size[1]:%{public}d, position[0]:%{public}d, "
             "position[1]:%{public}d",
            d.strength, d.size[0], d.size[1], d.position[0], d.position[1]);
        LOGW("wjh feature: %{public}d, noiseScale:%{public}f, noiseFrequency:%{public}f, noiseAmplitude:%{public}f, "
             "shape is %{public}d",
            d.feather, d.noiseScale, d.noiseFrequency, d.noiseAmplitude, static_cast<int>(d.shape));
    }
    const std::vector<ParticleDisturbance>& disturbance = GetPDisturbance();
    if (disturbance.size() != disturbanceArray.size()) {
        SetDisturbance(disturbanceArray);
        auto frameNode = GetHost();
        RosenRenderParticle::UpdateDisturbance(frameNode, disturbanceArray);
        return;
    }
    bool equal = true;
    for (size_t i = 0; i < disturbance.size(); i++) {
        ParticleDisturbance src = disturbance[i];
        ParticleDisturbance dst = disturbanceArray[i];
        if (src != dst) {
            equal = false;
            break;
        }
    }
    if (equal) {
        return;
    }
    SetDisturbance(disturbanceArray);
    auto frameNode = GetHost();
    RosenRenderParticle::UpdateDisturbance(frameNode, disturbanceArray);
}
} // namespace OHOS::Ace::NG