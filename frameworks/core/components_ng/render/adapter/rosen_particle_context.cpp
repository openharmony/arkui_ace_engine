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

#include "frameworks/core/components_ng/render/adapter/rosen_particle_context.h"

#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
class RosenRenderContext;
void RosenRenderParticle::UpdateDisturbance(
    const RefPtr<FrameNode>& frameNode, const std::vector<ParticleDisturbance>& disturbanceArray)
{
    // auto renderContext = AceType::DynamicCast<NG::RosenRenderContext>(frameNode->GetRenderContext());
    // auto rsNode = renderContext->GetRSNode();
    // std::shared_ptr<Rosen::ParticleNoiseFields> fields = std::make_shared<Rosen::ParticleNoiseFields>();
    // for (auto field : disturbanceArray) {
    //     Rosen::Vector2f size = { field.size[0], field.size[1] };
    //     Rosen::Vector2f position = { field.position[0], field.position[1] };
    //     Rosen::ParticleNoiseField rsField = Rosen::ParticleNoiseField(field.strength, field.shape, size, position,
    //         field.feather, field.noiseScale, field.noiseFrequency, field.noiseAmplitude);
    //     fields->AddFiled(rsField);
    // }
    // rsNode->SetParticleNoiseField();
}
} // namespace OHOS::Ace::NG