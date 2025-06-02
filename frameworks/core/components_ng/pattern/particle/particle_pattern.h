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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PARTICLE_PARTICLE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PARTICLE_PARTICLE_PATTERN_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/particle/particle_model.h"

namespace OHOS::Ace::NG {
  
class ACE_EXPORT ParticlePattern : public Pattern {
    DECLARE_ACE_TYPE(ParticlePattern, Pattern);

public:
    ParticlePattern(uint32_t emitterCount) : emitterCount_(emitterCount) {};
    ~ParticlePattern() override = default;

    void OnVisibleChange(bool isVisible) override;
    void OnAttachToMainTree() override;
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void UpdateDisturbance(const std::vector<ParticleDisturbance>& disturbance);
    void updateEmitterPosition(std::vector<EmitterProperty>& property);

    bool HaveUnVisibleParent() const
    {
        return haveUnVisibleParent_;
    }

    void SetHaveUnVisibleParent(bool haveUnVisibleParent)
    {
        haveUnVisibleParent_ = haveUnVisibleParent;
    }

    const std::vector<ParticleDisturbance>& GetDisturbance() const
    {
        return disturbance_;
    }

    void SetDisturbance(std::vector<ParticleDisturbance> disturbance)
    {
        disturbance_ = disturbance;
    }

    const std::vector<EmitterProperty>& GetEmitterProperty() const
    {
        return emitterProperty_;
    }

    void SetEmitterProperty(std::vector<EmitterProperty> emitterProperty)
    {
        emitterProperty_ = emitterProperty;
    }

    uint32_t GetEmitterCount() const
    {
        return emitterCount_;
    }

private:
    void GetEmitterJson(const std::unique_ptr<JsonValue>& objectParticlesJson, const ParticleOption& item) const;
    void GetColorJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
        const ParticleOption& particleOption) const;
    void GetOpacityJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
        const ParticleOption& particleOption) const;
    void GetScaleJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
        const ParticleOption& particleOption) const;
    void GetVelocityJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
        const ParticleOption& particleOption) const;
    void GetAccelerationJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
        const ParticleOption& particleOption) const;
    void GetSpinJson(const std::unique_ptr<JsonValue>& objectParticlesJson, const ParticleOption& particleOption) const;

    std::unique_ptr<JsonValue> ParseEmitterParticleJson(const ParticleOption& particleOption) const;
    std::unique_ptr<JsonValue> ParseAnnulusRegionJson(const ParticleOption& particleOption,
        const ParticleAnnulusRegion& annulusRegion) const;
    std::unique_ptr<JsonValue> ParseColorUpdater(ParticleColorPropertyUpdater& updater) const;
    std::unique_ptr<JsonValue> ParseFloatObjectJson(const ParticleFloatPropertyOption& updaterObject) const;
    void ParseParticleObject(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    bool haveUnVisibleParent_ = false;
    std::vector<ParticleDisturbance> disturbance_;
    std::vector<EmitterProperty> emitterProperty_;
    uint32_t emitterCount_ = 0;
};
} // namespace OHOS::Ace

#endif