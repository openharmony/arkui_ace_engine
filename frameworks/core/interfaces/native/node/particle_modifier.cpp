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
#include "particle_modifier.h"

#include "core/components_ng/pattern/particle/particle_model_ng.h"
#include "base/geometry/dimension.h"

namespace OHOS::Ace::NG {
namespace {
void SetDisturbanceField(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ParticleDisturbance> dataArray;
    for (ArkUI_Int32 i = 0; i < length / 10; i++) {
        ParticleDisturbance disturbanceField;
        disturbanceField.strength = values[i*10].f32;
        disturbanceField.shape = static_cast<ParticleDisturbanceShapeType>(values[i*10+1].i32);
        disturbanceField.size[0] = values[i*10+2].i32, disturbanceField.size[1] = values[i*10+3].i32,
        disturbanceField.position[0] = values[i*10+4].i32, disturbanceField.position[1] = values[i*10+5].i32,
        disturbanceField.feather = values[i*10+6].i32;
        disturbanceField.noiseScale = values[i*10+7].f32;
        disturbanceField.noiseFrequency = values[i*10+8].f32;
        disturbanceField.noiseAmplitude = values[i*10+9].f32;
        dataArray.push_back(disturbanceField);
    }
    ParticleModelNG::DisturbanceField(dataArray, frameNode);
}

void ResetDisturbanceField(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ParticleDisturbance> dataArray;
    ParticleModelNG::DisturbanceField(dataArray, frameNode);
}

} // namespace

namespace NodeModifier {
const ArkUIParticleModifier* GetParticleModifier()
{
    static const ArkUIParticleModifier modifier = { SetDisturbanceField, ResetDisturbanceField };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG