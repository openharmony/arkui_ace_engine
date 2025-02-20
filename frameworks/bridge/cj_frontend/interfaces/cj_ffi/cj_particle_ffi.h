/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_FRAMEWORK_CJ_PARTICLE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_PARTICLE_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorParticleOptionsHandle = void*;
using VectorParticlePropertyAnimationHandle = void*;
using VectorNativeDisturbanceFieldOptionsHandle = void*;
using VectorNativeEmitterPropertyHandle = void*;

extern "C" {
struct ParticlePropertyUpdaterConfigs {
    float from;
    float to;
    VectorParticlePropertyAnimationHandle cur;
};

struct ParticleUpdaterOptions {
    int32_t type;
    ParticlePropertyUpdaterConfigs config;
};

struct ParticlePropertyOptions {
    float rangeFrom;
    float rangeTo;
    ParticleUpdaterOptions updater;
};

struct AccelerationOptions {
    ParticlePropertyOptions speed;
    ParticlePropertyOptions angle;
};

struct VelocityOptions {
    float speedFrom;
    float speedTo;
    float angleFrom;
    float angleTo;
};

struct ParticlePropertyAnimation {
    float fromFloat;
    float toFloat;
    uint32_t fromColor;
    uint32_t toColor;
    int32_t startMillis;
    int32_t endMillis;
    char* curve;
};

struct ParticleColorPropertyUpdaterConfigs {
    uint32_t rFrom;
    uint32_t rTo;
    uint32_t gFrom;
    uint32_t gTo;
    uint32_t bFrom;
    uint32_t bTo;
    uint32_t aFrom;
    uint32_t aTo;
    VectorParticlePropertyAnimationHandle cur;
};

struct ParticleColorUpdaterOptions {
    int32_t type;
    ParticleColorPropertyUpdaterConfigs config;
};

struct ParticleColorPropertyOptions {
    uint32_t colorFrom;
    uint32_t colorTo;
    int32_t distributionType;
    ParticleColorUpdaterOptions updater;
};

struct ParticleConfigs {
    double radius;
    char* src;
    double sizeWidthValue;
    int32_t sizeWidthUnit;
    double sizeHeightValue;
    int32_t sizeHeightUnit;
    int32_t objectFit;
};

struct EmitterParticleOptions {
    int32_t type;
    ParticleConfigs config;
    int32_t count;
    int64_t lifetime;
    int64_t lifeTimeRange;
};

struct EmitterOptions {
    EmitterParticleOptions particle;
    int32_t emitRate;
    int32_t shape;
    double positionXValue;
    int32_t positionXUnit;
    double positionYValue;
    int32_t positionYUnit;
    double sizeWidthValue;
    int32_t sizeWidthUnit;
    double sizeHeightValue;
    int32_t sizeHeightUnit;
};

struct ParticleOptions {
    EmitterOptions emitter;
    ParticleColorPropertyOptions color;
    ParticlePropertyOptions opacity;
    ParticlePropertyOptions scale;
    VelocityOptions velocity;
    AccelerationOptions acceleration;
    ParticlePropertyOptions spin;
};

struct NativeDisturbanceFieldOptions {
    double strength;
    int32_t shape;
    int32_t size_width;
    int32_t size_height;
    int32_t position_x;
    int32_t position_y;
    int32_t feather;
    double noiseScale;
    double noiseFrequency;
    double noiseAmplitude;
};

struct NativeEmitterProperty {
    int32_t index;
    bool is_mitRate_set;
    int32_t emitRate;
    bool is_position_set;
    int32_t position_x;
    int32_t position_y;
    bool is_size_set;
    int32_t size_width;
    int32_t size_height;
};

CJ_EXPORT VectorParticleOptionsHandle FFICJCreateVectorParticleOptions(int64_t size);
CJ_EXPORT void FFICJVectorParticleOptionsSetElement(
    VectorParticleOptionsHandle vec, int64_t index, ParticleOptions particleOptions);
CJ_EXPORT void FFICJVectorParticleOptionsDelete(VectorParticleOptionsHandle vec);

CJ_EXPORT VectorParticlePropertyAnimationHandle FFICJCreateVectorParticlePropertyAnimation(int64_t size);
CJ_EXPORT void FFICJVectorParticlePropertyAnimationSetElement(
    VectorParticlePropertyAnimationHandle vec, int64_t index, ParticlePropertyAnimation particlePropertyAnimation);
CJ_EXPORT void FFICJVectorParticlePropertyAnimationDelete(VectorParticlePropertyAnimationHandle vec);

CJ_EXPORT void FfiOHOSAceFrameworkParticleCreate(VectorParticleOptionsHandle particles);

CJ_EXPORT VectorNativeDisturbanceFieldOptionsHandle FFICJCreateVectorNativeDisturbanceFieldOptions(int64_t size);
CJ_EXPORT void FFICJVectorNativeDisturbanceFieldOptionsSetElement(VectorNativeDisturbanceFieldOptionsHandle vec,
    int64_t index, NativeDisturbanceFieldOptions options);
CJ_EXPORT void FFICJVectorNativeDisturbanceFieldOptionsDelete(VectorNativeDisturbanceFieldOptionsHandle vec);
CJ_EXPORT void FfiOHOSAceFrameworkDataPanelSetDisturbanceFields(VectorNativeDisturbanceFieldOptionsHandle value);
CJ_EXPORT VectorNativeEmitterPropertyHandle FFICJCreateVectorNativeEmitterProperty(int64_t size);
CJ_EXPORT void FFICJVectorNativeEmitterPropertySetElement(VectorNativeEmitterPropertyHandle vec, int64_t index,
    NativeEmitterProperty value);
CJ_EXPORT void FFICJVectorNativeEmitterPropertyDelete(VectorNativeEmitterPropertyHandle vec);
CJ_EXPORT void FfiOHOSAceFrameworkSetEmitterProperties(VectorNativeEmitterPropertyHandle value);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_PARTICLE_FFI_H
