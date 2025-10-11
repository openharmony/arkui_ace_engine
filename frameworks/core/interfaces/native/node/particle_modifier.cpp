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
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_CENTER_VALUE = 0.5f;
constexpr float DEFAULT_START_ANGLE_VALUE = 0.0f;
constexpr float DEFAULT_END_ANGLE_VALUE = 360.0f;

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

void SetRippleField(ArkUINodeHandle node, const ArkRippleFieldOptions* values, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ParticleRippleField> dataArray;
    for (ArkUI_Int32 i = 0; i < length; i++) {
        ParticleRippleField rippleField;
        if (values[i].isSetAmplitude == 1) {
            rippleField.amplitude = values[i].amplitude;
        }
        if (values[i].isSetWaveLength == 1) {
            rippleField.wavelength = values[i].wavelength;
        }
        if (values[i].isSetWaveSpeed == 1) {
            rippleField.waveSpeed = values[i].waveSpeed;
        }
        if (values[i].isSetAttenuation == 1) {
            rippleField.attenuation = values[i].attenuation;
        }
        if (values[i].isSetCenter == 1) {
            rippleField.center.first = static_cast<CalcDimension>(values[i].centerX);
            rippleField.center.second = static_cast<CalcDimension>(values[i].centerY);
        }
        if (values[i].isSetRegion == 1) {
            if (values[i].region.isSetShape == 1) {
                auto shapeValue = values[i].region.shape;
                rippleField.region.shape = shapeValue >= 0 && shapeValue < static_cast<int>(ParticleDisturbanceShapeType::MAX)
                    ? static_cast<ParticleDisturbanceShapeType>(shapeValue)
                    : ParticleDisturbanceShapeType::RECT;
            }
            if (values[i].region.isSetPosition == 1) {
                rippleField.region.position.first =
                    static_cast<CalcDimension>(values[i].region.positionX);
                rippleField.region.position.second =
                    static_cast<CalcDimension>(values[i].region.positionY);
            }
            if (values[i].region.isSetSize == 1) {
                rippleField.region.size.first =
                    static_cast<CalcDimension>(values[i].region.sizeWidth);
                rippleField.region.size.second =
                    static_cast<CalcDimension>(values[i].region.sizeHeight);
            }
        }
        dataArray.push_back(rippleField);
    }
    ParticleModelNG::RippleFields(dataArray, frameNode);
}

void ResetRippleField(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ParticleRippleField> dataArray;
    ParticleModelNG::RippleFields(dataArray, frameNode);
}

void SetVelocityField(ArkUINodeHandle node, const ArkVelocityFieldOptions* values, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ParticleVelocityField> dataArray;
    for (ArkUI_Int32 i = 0; i < length; i++) {
        ParticleVelocityField velocityField;
        if (values[i].isSetVelocity == 1) {
            velocityField.velocity.first = values[i].velocityX;
            velocityField.velocity.second = values[i].velocityY;
        }
        if (values[i].isSetRegion == 1) {
            velocityField.velocity.first = values[i].velocityX;
            velocityField.velocity.second = values[i].velocityY;
            if (values[i].region.isSetShape == 1) {
                velocityField.region.shape = static_cast<ParticleDisturbanceShapeType>(values[i].region.shape);
            }
            if (values[i].region.isSetPosition == 1) {
                velocityField.region.position.first =
                    Dimension(values[i].region.positionX, DimensionUnit::VP);
                velocityField.region.position.second =
                    Dimension(values[i].region.positionY, DimensionUnit::VP);
            }
            if (values[i].region.isSetSize == 1) {
                velocityField.region.size.first =
                    Dimension(values[i].region.sizeWidth, DimensionUnit::VP);
                velocityField.region.size.second =
                    Dimension(values[i].region.sizeHeight, DimensionUnit::VP);
            }
        }
        dataArray.push_back(velocityField);
    }
    ParticleModelNG::VelocityFields(dataArray, frameNode);
}

void ResetVelocityField(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ParticleVelocityField> dataArray;
    ParticleModelNG::VelocityFields(dataArray, frameNode);
}

void setEmitter(ArkUINodeHandle node, const ArkEmitterPropertyOptions* values, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<EmitterProperty> emitterProperties;
    for (ArkUI_Int32 i = 0; i < length; i++) {
        EmitterProperty prop;
        prop.index = values[i].index;
        if (values[i].isSetEmitRate == 1) {
            prop.emitRate = values[i].emitRate;
        }
        if (values[i].isSetPosition == 1) {
            prop.position = VectorF(values[i].positionX, values[i].positionY);
        }
        if (values[i].isSetSize == 1) {
            prop.size = VectorF(values[i].sizeWidth, values[i].sizeHeight);
        }

        if (values[i].isSetAnnulusRegion == 1) {
            std::pair<CalcDimension, CalcDimension> center = {
                CalcDimension(DEFAULT_CENTER_VALUE, DimensionUnit::PERCENT),
                CalcDimension(DEFAULT_CENTER_VALUE, DimensionUnit::PERCENT)};
            CalcDimension innerRadius;
            CalcDimension outerRadius;
            float startAngle = DEFAULT_START_ANGLE_VALUE;
            float endAngle = DEFAULT_END_ANGLE_VALUE;

            if (values[i].isSetCenter == 1) {
                center.first = CalcDimension(values[i].centerX.value,
                    static_cast<DimensionUnit>(values[i].centerX.units));
                center.second = CalcDimension(values[i].centerY.value,
                    static_cast<DimensionUnit>(values[i].centerY.units));
            }

            if (values[i].isSetInnerRadius == 1) {
                innerRadius = CalcDimension(values[i].innerRadius.value,
                    static_cast<DimensionUnit>(values[i].innerRadius.units));
            }
            if (values[i].isSetOuterRadius == 1) {
                outerRadius = CalcDimension(values[i].outerRadius.value,
                    static_cast<DimensionUnit>(values[i].outerRadius.units));
            }

            if (values[i].isSetStartAngle == 1) {
                startAngle = values[i].startAngle;
            }
            if (values[i].isSetEndAngle == 1) {
                endAngle = values[i].endAngle;
            }
            prop.annulusRegion = {center, innerRadius, outerRadius, startAngle, endAngle};
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
        .SetRippleField = SetRippleField,
        .ResetRippleField = ResetRippleField,
        .SetVelocityField = SetVelocityField,
        .ResetVelocityField = ResetVelocityField,
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
