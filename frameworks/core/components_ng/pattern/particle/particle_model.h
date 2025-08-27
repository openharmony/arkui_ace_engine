/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PATTERNS_PARTICLE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PATTERNS_PARTICLE_MODEL_H
#include <functional>
#include <list>
#include <memory>
#include <mutex>

#include "base/geometry/ng/vector.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/particle_property.h"
namespace OHOS::Ace {

enum class ParticleDisturbanceShapeType :uint32_t { RECT, CIRCLE, ELLIPSE };
const CalcDimension DEFAULT_CENTER_VALUE = CalcDimension(0.5, DimensionUnit::PERCENT);
constexpr float DEFAULT_RADIUS_VALUE = 0.0f;
constexpr float DEFAULT_START_ANGLE_VALUE = 0.0f;
constexpr float DEFAULT_END_ANGLE_VALUE = 360.0f;

struct ParticleDisturbance {
    float strength = 0.0f;
    ParticleDisturbanceShapeType shape = ParticleDisturbanceShapeType::RECT;
    int  size[2] = {0, 0};
    int  position[2] = {0, 0};
    int feather = 0;
    float noiseScale = 1.0f;
    float noiseFrequency = 1.0f;
    float noiseAmplitude = 1.0f;

    bool operator!=(const ParticleDisturbance& data) const
    {
        return !(NearEqual(strength, data.strength) && shape == data.shape && size[0] == data.size[0] &&
                 size[1] == data.size[1] && position[0] == data.position[0] && position[1] == data.position[1] &&
                 feather == data.feather && NearEqual(noiseScale, data.noiseScale) &&
                 NearEqual(noiseFrequency, data.noiseFrequency) && NearEqual(noiseAmplitude, data.noiseAmplitude));
    }
};

struct EmitterProperty {
    uint32_t index = 0;
    std::optional<NG::VectorF> position;
    std::optional<NG::VectorF> size;
    std::optional<uint32_t> emitRate;
    std::optional<NG::ParticleAnnulusRegion> annulusRegion;
};

class ACE_FORCE_EXPORT ParticleModel {
public:
    static ParticleModel* GetInstance();
    virtual ~ParticleModel() = default;
    virtual void Create(std::list<NG::ParticleOption>& arrayValue) = 0;
    virtual void DisturbanceField(const std::vector<ParticleDisturbance>& disturbanceArray) = 0;
    virtual void updateEmitter(std::vector<EmitterProperty>& property) = 0;

private:
    static std::unique_ptr<ParticleModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif