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

#include "core/components_ng/pattern/particle/particle_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/particle/particle_pattern.h"
namespace OHOS::Ace::NG {
namespace {
void ReloadParticleResources(const ParticleOption& particleOption,
    std::list<ParticleOption>& updatedArrayValue)
{
    // reloadResources EmitterOptions: position、size.
    auto emitterOptionOpt = particleOption.GetEmitterOption();
    emitterOptionOpt.ReloadResources();

    std::optional<ParticleColorPropertyUpdater> updater;
    ParticleColorPropertyUpdaterConfig updaterConfig;
    std::list<ParticlePropertyAnimation<Color>> animationArrayValue;

    // reloadResources ParticleColorPropertyOptions: range.
    auto particleColorOpt = particleOption.GetParticleColorOption();
    if (particleColorOpt.has_value()) {
        particleColorOpt->ReloadResources();

        // reloadResources ParticleUpdater.CURVE: from、to.
        updater = particleColorOpt.value().GetUpdater();
        if (updater.has_value()) {
            updaterConfig = updater.value().GetConfig();
            auto animationArray = updaterConfig.GetAnimationArray();
            for (auto& fromTo : animationArray) {
                fromTo.ReloadResources();
                animationArrayValue.push_back(fromTo);
            }
        }
    }

    // reloadResources ImageParticleParameters: src、size.
    auto particle = emitterOptionOpt.GetParticle();
    auto particleConfig = particle.GetConfig();
    auto imageParameter = particleConfig.GetImageParticleParameter();
    imageParameter.ReloadResources();

    auto annulusRegion = emitterOptionOpt.GetAnnulusRegion();
    if (annulusRegion.has_value()) {
        annulusRegion->ReloadResources();
    }

    ParticleOption updatedParticleOption = particleOption;
    
    // set src and size after reloadResources.
    particleConfig.SetImageParticleParameter(imageParameter);
    particle.SetConfig(particleConfig);
    emitterOptionOpt.SetParticle(particle);
    if (annulusRegion.has_value()) {
        emitterOptionOpt.SetAnnulusRegion(annulusRegion.value());
    }

    // set position and size after reloadResources.
    updatedParticleOption.SetEmitterOption(emitterOptionOpt);

    // set range and from-to after reloadResources.
    if (particleColorOpt.has_value() && updater.has_value()) {
        updaterConfig.SetAnimationArray(animationArrayValue);
        updater.value().SetConfig(updaterConfig);
        particleColorOpt.value().SetUpdater(updater.value());
        updatedParticleOption.SetParticleColorOption(particleColorOpt.value());
    }
    updatedArrayValue.push_back(updatedParticleOption);
}

void CreateParticleResObj(std::list<ParticleOption>& arrayValue,
    const RefPtr<FrameNode> frameNode)
{
    if (!SystemProperties::ConfigChangePerform() || !frameNode) {
        return;
    }
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    auto updateFunc = [arrayValue, weakNode = WeakPtr<FrameNode>(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        std::list<ParticleOption> updatedArrayValue;
        for (auto& particleOption : arrayValue) {
            ReloadParticleResources(particleOption, updatedArrayValue);
        }
        auto context = frameNode->GetRenderContext();
        context->UpdateParticleOptionArray(updatedArrayValue);
    };
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("particle.Create", resObj, std::move(updateFunc));
}
}
void ParticleModelNG::Create(std::list<ParticleOption>& arrayValue)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::PARTICLE_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::PARTICLE_ETS_TAG, nodeId,
        [count = arrayValue.size()]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    stack->Push(frameNode);
    ACE_UPDATE_RENDER_CONTEXT(ParticleOptionArray, arrayValue);
    CreateParticleResObj(arrayValue, frameNode);
}

void ParticleModelNG::DisturbanceField(const std::vector<ParticleDisturbance>& disturbanceArray, FrameNode* frameNode)
{
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->UpdateDisturbance(disturbanceArray);
}

void ParticleModelNG::DisturbanceField(const std::vector<ParticleDisturbance>& disturbanceArray)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->UpdateDisturbance(disturbanceArray);
}

void ParticleModelNG::updateEmitter(std::vector<EmitterProperty>& property, FrameNode* frameNode)
{
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->updateEmitterPosition(property);
}

void ParticleModelNG::updateEmitter(std::vector<EmitterProperty>& property)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->updateEmitterPosition(property);
}
} // namespace OHOS::Ace::NG