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

void setEmitter(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<EmitterProperty> emitterProperties;
    for (ArkUI_Int32 i = 0; i < length / 9; i++) {
        EmitterProperty prop;

        //The numbers 0-9 represent each attribute in the object, corresponding to index，hasEmitRate，emitRate,
        //hasPosition，positionX，positionY，hasSize，sizeX，sizeY. Among them, index 1, 3, and 6 are marker values,
        // indicating whether the attributes following the markers exist.
        prop.index = values[i * 9].i32;
        if (values[i * 9 + 1].i32 == 1) {
            prop.emitRate = values[i * 9 + 2].i32;
        }
        if (values[i * 9 + 3].i32 == 1) {
            prop.position = VectorF(values[i * 9 + 4].f32, values[i * 9 + 5].f32);
        }
        if (values[i * 9 + 6].i32 == 1) {
            prop.size = VectorF(values[i * 9 + 7].f32, values[i * 9 + 8].f32);
        }
        emitterProperties.push_back(prop);
    }
    ParticleModelNG::updateEmitter(emitterProperties, frameNode);
}

void resetEmitter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<EmitterProperty> dataArray;
    ParticleModelNG::updateEmitter(dataArray, frameNode);
}
} // namespace

namespace NodeModifier {
const ArkUIParticleModifier* GetParticleModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIParticleModifier modifier = {
        .SetDisturbanceField = SetDisturbanceField,
        .ResetDisturbanceField = ResetDisturbanceField,
        .SetEmitter = setEmitter,
        .ResetEmitter = resetEmitter,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIParticleModifier* GetCJUIParticleModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIParticleModifier modifier = {
        .SetDisturbanceField = SetDisturbanceField,
        .ResetDisturbanceField = ResetDisturbanceField,
        .SetEmitter = setEmitter,
        .ResetEmitter = resetEmitter,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
