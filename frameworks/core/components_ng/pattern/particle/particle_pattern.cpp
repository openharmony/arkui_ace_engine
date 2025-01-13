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
namespace {
std::unordered_map<ParticleDisturbanceShapeType, std::string> shapes = {
    { ParticleDisturbanceShapeType::RECT, "RECT" },
    { ParticleDisturbanceShapeType::CIRCLE, "CIRCLE" },
    { ParticleDisturbanceShapeType::ELLIPSE, "ELLIPSE" } };
std::string ShapeTypeToString(ParticleDisturbanceShapeType type)
{
    auto it = shapes.find(type);
    if (it != shapes.end()) {
        return it->second;
    }
    return "Unknown";
}
} // namespace
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

std::unique_ptr<JsonValue> ParticlePattern::ParseEmitterParticleJson(const ParticleOption& particleOption) const
{
    auto emitterOptionOpt = particleOption.GetEmitterOption();
    auto objectParticleJson = JsonUtil::Create(true);
    auto particle = emitterOptionOpt.GetParticle();
    auto particleType = particle.GetParticleType();
    auto particleConfig = particle.GetConfig();
    if (particleType == ParticleType::POINT) {
        auto objectConfigJson = JsonUtil::Create(true);
        objectParticleJson->Put("type", "ParticleType.POINT");
        auto pointParameter = particleConfig.GetPointParticleParameter();
        auto radius = pointParameter.GetRadius();
        objectConfigJson->Put("radius", std::to_string(radius).c_str());
        objectParticleJson->Put("config", objectConfigJson);
    } else {
        objectParticleJson->Put("type", "ParticleType.IMAGE");
        auto objectConfigJson = JsonUtil::Create(true);
        auto imageParameter = particleConfig.GetImageParticleParameter();
        auto imageSource = imageParameter.GetImageSource();
        auto imageSize = imageParameter.GetSize();
        auto imageWidth = imageSize.first.ToString();
        auto imageHeight = imageSize.second.ToString();
        objectConfigJson->Put("src", imageSource.c_str());
        auto dimension = "[" + imageWidth + "," + imageHeight + "]";
        objectConfigJson->Put("size", dimension.c_str());
        auto objectFit = imageParameter.GetImageFit();
        static const char* OBJECTFITVALUE[] = { "ImageFit.Fill", "ImageFit.Contain", "ImageFit.Cover", "ImageFit.Auto",
            "ImageFit.FitHeight", "ImageFit.None", "ImageFit.ScaleDown", "ImageFit.TOP_START", "ImageFit.TOP",
            "ImageFit.TOP_END", "ImageFit.START", "ImageFit.CENTER", "ImageFit.END", "ImageFit.BOTTOM_START",
            "ImageFit.BOTTOM", "ImageFit.BOTTOM_END" };
        if (objectFit.has_value()) {
            auto objectFitValue = static_cast<int32_t>(objectFit.value());
            if (objectFitValue < sizeof(OBJECTFITVALUE) / sizeof(char*)) {
                objectConfigJson->Put("objectFit", OBJECTFITVALUE[objectFitValue]);
            }
        }
        objectParticleJson->Put("config", objectConfigJson);
    }
    auto particleCount = particle.GetCount();
    objectParticleJson->Put("count", std::to_string(particleCount).c_str());
    auto lifeTimeOpt = particle.GetLifeTime();
    if (lifeTimeOpt.has_value()) {
        objectParticleJson->Put("lifetime", std::to_string(lifeTimeOpt.value()).c_str());
    }
    auto lifeTimeRangeOpt = particle.GetLifeTimeRange();
    if (lifeTimeRangeOpt.has_value()) {
        objectParticleJson->Put("lifetimeRange", std::to_string(lifeTimeRangeOpt.value()).c_str());
    }
    return objectParticleJson;
}

void ParticlePattern::GetEmitterJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
    const ParticleOption& particleOption) const
{
    auto objectEmitterJson = JsonUtil::Create(true);
    auto objectParticleJson = ParseEmitterParticleJson(particleOption);
    objectEmitterJson->Put("particle", objectParticleJson);

    auto emitterOptionOpt = particleOption.GetEmitterOption();
    auto emitterRateOpt = emitterOptionOpt.GetEmitterRate();
    if (emitterRateOpt.has_value()) {
        objectEmitterJson->Put("emitRate", std::to_string(emitterRateOpt.value()).c_str());
    }
    auto shapeOpt = emitterOptionOpt.GetShape();
    if (shapeOpt.has_value()) {
        auto shapeInt = static_cast<int32_t>(shapeOpt.value());
        if (shapeInt == ParticleEmitterShape::CIRCLE) {
            objectEmitterJson->Put("shape", "ParticleEmitterShape.CIRCLE");
        } else if (shapeInt == ParticleEmitterShape::ELLIPSE) {
            objectEmitterJson->Put("shape", "ParticleEmitterShape.ELLIPSE");
        } else {
            objectEmitterJson->Put("shape", "ParticleEmitterShape.RECTANGLE");
        }
    }
    auto pointOpt = emitterOptionOpt.GetPosition();
    if (pointOpt.has_value()) {
        auto position = "[" + pointOpt.value().first.ToString() + "," + pointOpt.value().second.ToString() + "]";
        objectEmitterJson->Put("position", position.c_str());
    }
    auto sizeOpt = emitterOptionOpt.GetSize();
    if (sizeOpt.has_value()) {
        auto position = "[" + sizeOpt.value().first.ToString() + "," + sizeOpt.value().second.ToString() + "]";
        objectEmitterJson->Put("size", position.c_str());
    }
    objectParticlesJson->Put("emitter", objectEmitterJson);
}

std::unique_ptr<JsonValue> ParticlePattern::ParseColorUpdater(ParticleColorPropertyUpdater& updater) const
{
    auto updateType = updater.GetUpdateType();
    auto config = updater.GetConfig();
    auto objectUpdaterJson = JsonUtil::Create(true);
    if (updateType == UpdaterType::RANDOM) {
        objectUpdaterJson->Put("type", "ParticleUpdater.RANDOM");
        auto randomConfig = config.GetRandomConfig();
        auto redRandom = randomConfig.GetRedRandom();
        auto greenRandom = randomConfig.GetGreenRandom();
        auto blueRandom = randomConfig.GetBlueRandom();
        auto alphaRandom = randomConfig.GetAlphaRandom();
        auto configJson = JsonUtil::Create(true);
        auto rString = "[" + std::to_string(redRandom.first) + "," +
            std::to_string(redRandom.second) + "]";
        configJson->Put("r", rString.c_str());
        auto gString = "[" + std::to_string(greenRandom.first) + "," +
            std::to_string(greenRandom.second) + "]";
        configJson->Put("g", gString.c_str());
        auto bString = "[" + std::to_string(blueRandom.first) + "," +
            std::to_string(blueRandom.second) + "]";
        configJson->Put("b", bString.c_str());
        auto aString = "[" + std::to_string(alphaRandom.first) +  "," +
            std::to_string(alphaRandom.second) + "]";
        configJson->Put("a", aString.c_str());
        objectUpdaterJson->Put("config", configJson);
    } else if (updateType == UpdaterType::CURVE) {
        objectUpdaterJson->Put("type", "ParticleUpdater.CURVE");
        auto configArrayJson = JsonUtil::CreateArray(true);
        auto& curveConfig = config.GetAnimationArray();
        for (const auto& colorAnimationConfig : curveConfig) {
            auto fromColor = colorAnimationConfig.GetFrom().ToString();
            auto toColor = colorAnimationConfig.GetTo().ToString();
            auto startMills = colorAnimationConfig.GetStartMills();
            auto endMills = colorAnimationConfig.GetEndMills();
            auto curve = colorAnimationConfig.GetCurve();
            auto configJson = JsonUtil::Create(true);
            configJson->Put("from", fromColor.c_str());
            configJson->Put("to", toColor.c_str());
            configJson->Put("startMillis", std::to_string(startMills).c_str());
            configJson->Put("endMillis", std::to_string(endMills).c_str());
            configJson->Put("curve", curve->ToString().c_str());
            configArrayJson->Put(configJson);
        }
        objectUpdaterJson->Put("config", configArrayJson);
    } else {
        objectUpdaterJson->Put("type", "ParticleUpdater.NONE");
        objectUpdaterJson->Put("config", "");
    }
    return objectUpdaterJson;
}

void ParticlePattern::GetColorJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
    const ParticleOption& particleOption) const
{
    auto colorOptionOpt = particleOption.GetParticleColorOption();
    if (!colorOptionOpt.has_value()) {
        return;
    }
    auto objectColorJson = JsonUtil::Create(true);
    auto colorOption = colorOptionOpt.value();
    auto initRange = colorOption.GetRange();
    auto colorDist = colorOption.GetDistribution();
    objectColorJson->Put("range", ("[" + initRange.first.ToString() + "," +
        initRange.second.ToString() +"]").c_str());
    auto colorDistInt = colorDist.value_or(DistributionType::UNIFORM);
    if (colorDistInt == DistributionType::UNIFORM) {
        objectColorJson->Put("distributionType", "DistributionType::UNIFORM");
    } else {
        objectColorJson->Put("distributionType", "DistributionType::GAUSSIAN");
    }
    auto updaterOpt = colorOption.GetUpdater();
    if (!updaterOpt.has_value()) {
        objectParticlesJson->Put("color", objectColorJson);
        return;
    }
    auto updater = updaterOpt.value();
    auto objectUpdaterJson = ParseColorUpdater(updater);
    objectColorJson->Put("updater", objectUpdaterJson);
    objectParticlesJson->Put("color", objectColorJson);
}

void ParticlePattern::GetOpacityJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
    const ParticleOption& particleOption) const
{
    auto opacityOptionOpt = particleOption.GetParticleOpacityOption();
    if (!opacityOptionOpt.has_value()) {
        return;
    }
    objectParticlesJson->Put("opacity", ParseFloatObjectJson(opacityOptionOpt.value()));
}

void ParticlePattern::GetScaleJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
    const ParticleOption& particleOption) const
{
    auto scaleOptionOpt = particleOption.GetParticleScaleOption();
    if (!scaleOptionOpt.has_value()) {
        return;
    }
    objectParticlesJson->Put("scale", ParseFloatObjectJson(scaleOptionOpt.value()));
}

void ParticlePattern::GetVelocityJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
    const ParticleOption& particleOption) const
{
    auto velocityOptionOpt = particleOption.GetParticleVelocityOption();
    if (!velocityOptionOpt.has_value()) {
        return;
    }
    auto objectVelocityJson = JsonUtil::Create(true);
    auto velocityValue = velocityOptionOpt.value();
    auto speed = velocityValue.GetSpeedRange();
    auto angle = velocityValue.GetAngleRange();
    auto speedString = "[" + std::to_string(speed.first) + "," +
            std::to_string(speed.second) + "]";
    objectVelocityJson->Put("speed", speedString.c_str());
    auto angleString = "[" + std::to_string(angle.first) + "," +
            std::to_string(angle.second) + "]";
    objectVelocityJson->Put("angle", angleString.c_str());
    objectParticlesJson->Put("velocity", objectVelocityJson);
}

void ParticlePattern::GetAccelerationJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
    const ParticleOption& particleOption) const
{
    auto accelerationOpt = particleOption.GetParticleAccelerationOption();
    if (!accelerationOpt.has_value()) {
        return;
    }
    auto objectAccelerationJson = JsonUtil::Create(true);
    auto acceleration = accelerationOpt.value();
    auto speedOpt = acceleration.GetSpeed();
    auto angleOpt = acceleration.GetAngle();
    if (speedOpt.has_value()) {
        objectAccelerationJson->Put("speed", ParseFloatObjectJson(speedOpt.value()));
    }
    if (angleOpt.has_value()) {
        objectAccelerationJson->Put("angle", ParseFloatObjectJson(angleOpt.value()));
    }
    objectParticlesJson->Put("acceleration", objectAccelerationJson);
}

void ParticlePattern::GetSpinJson(const std::unique_ptr<JsonValue>& objectParticlesJson,
    const ParticleOption& particleOption) const
{
    auto spinOptionOpt = particleOption.GetParticleSpinOption();
    auto objectSpinJson = JsonUtil::Create(true);
    if (!spinOptionOpt.has_value()) {
        return;
    }
    objectParticlesJson->Put("spin", ParseFloatObjectJson(spinOptionOpt.value()));
}

std::unique_ptr<JsonValue> ParticlePattern::ParseFloatObjectJson(const ParticleFloatPropertyOption& floatObject) const
{
    auto objectJson = JsonUtil::Create(true);
    auto initRange = floatObject.GetRange();
    objectJson->Put("range", ("[" + std::to_string(initRange.first) + "," +
        std::to_string(initRange.second) + "]").c_str());

    auto updaterOpt = floatObject.GetUpdater();
    if (!updaterOpt.has_value()) {
        return objectJson;
    }
    auto objectUpdaterJson = JsonUtil::Create(true);
    auto updater = updaterOpt.value();
    auto updateType = updater.GetUpdaterType();
    auto config = updater.GetConfig();
    if (updateType == UpdaterType::RANDOM) {
        objectUpdaterJson->Put("type", "ParticleUpdater.RANDOM");
        auto randomConfig = config.GetRandomConfig();
        auto configString = "[" + std::to_string(randomConfig.first) + "," +
            std::to_string(randomConfig.second) + "]";
        objectUpdaterJson->Put("config", configString.c_str());
    } else if (updateType == UpdaterType::CURVE) {
        objectUpdaterJson->Put("type", "ParticleUpdater.CURVE");
        auto configArrayJson = JsonUtil::CreateArray(true);
        auto& curveConfig = config.GetAnimations();
        for (const auto& animationConfig : curveConfig) {
            auto fromColor = animationConfig.GetFrom();
            auto toColor = animationConfig.GetTo();
            auto startMills = animationConfig.GetStartMills();
            auto endMills = animationConfig.GetEndMills();
            auto curve = animationConfig.GetCurve();
            auto configJson = JsonUtil::Create(true);
            configJson->Put("from", std::to_string(fromColor).c_str());
            configJson->Put("to", std::to_string(toColor).c_str());
            configJson->Put("startMillis", std::to_string(startMills).c_str());
            configJson->Put("endMillis", std::to_string(endMills).c_str());
            configJson->Put("curve", curve->ToString().c_str());
            configArrayJson->Put(configJson);
        }
        objectUpdaterJson->Put("config", configArrayJson);
    } else if (updateType == UpdaterType::NONE_UPDATER) {
        objectUpdaterJson->Put("type", "ParticleUpdater.NONE");
        objectUpdaterJson->Put("config", "");
    }
    objectJson->Put("updater", objectUpdaterJson);
    return objectJson;
}

void ParticlePattern::ParseParticleObject(std::unique_ptr<JsonValue>& json,
    const InspectorFilter& filter) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (!context->GetParticleOptionArray().has_value()) {
        return;
    }
    auto particleArray = context->GetParticleOptionArray().value();
    auto objectParticlesArrayJson = JsonUtil::CreateArray(true);
    for (auto& particle : particleArray) {
        auto objectParticlesJson = JsonUtil::Create(true);
        GetEmitterJson(objectParticlesJson, particle);
        GetColorJson(objectParticlesJson, particle);
        GetOpacityJson(objectParticlesJson, particle);
        GetScaleJson(objectParticlesJson, particle);
        GetVelocityJson(objectParticlesJson, particle);
        GetAccelerationJson(objectParticlesJson, particle);
        GetSpinJson(objectParticlesJson, particle);
        objectParticlesArrayJson->Put(objectParticlesJson);
    }
    json->PutExtAttr("particles", objectParticlesArrayJson, filter);
}

void ParticlePattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    auto props = GetEmitterProperty();
    if (props.size() > 0) {
        auto array = JsonUtil::CreateArray(true);
        for (size_t i = 0; i < props.size(); i++) {
            auto object = JsonUtil::Create(true);
            object->Put("index", std::to_string(props[i].index).c_str());
            if (props[i].emitRate.has_value()) {
                object->Put("emitRate", std::to_string(*props[i].emitRate).c_str());
            }
            if (props[i].position.has_value()) {
                auto positionObj = JsonUtil::Create(true);
                positionObj->Put("x", std::to_string(props[i].position->x).c_str());
                positionObj->Put("y", std::to_string(props[i].position->y).c_str());
                object->Put("position", positionObj);
            }
            if (props[i].size.has_value()) {
                auto sizeObj = JsonUtil::Create(true);
                sizeObj->Put("x", std::to_string(props[i].size->x).c_str());
                sizeObj->Put("y", std::to_string(props[i].size->y).c_str());
                object->Put("size", sizeObj);
            }
            array->Put(std::to_string(i).c_str(), object);
        }
        json->Put("emitter", array);
    }
    auto disturbance = GetDisturbance();
    if (disturbance.size() > 0) {
        auto disturbanceFieldsArray = JsonUtil::CreateArray(true);
        for (size_t i = 0; i < disturbance.size(); i++) {
            auto object = JsonUtil::Create(true);
            object->Put("strength", disturbance[i].strength);
            object->Put("shape", ShapeTypeToString(disturbance[i].shape).c_str());
            auto size = JsonUtil::Create(true);
            size->Put("width", disturbance[i].size[0]);
            size->Put("height", disturbance[i].size[1]);
            object->Put("size", size);
            auto position = JsonUtil::Create(true);
            size->Put("x", disturbance[i].position[0]);
            size->Put("y", disturbance[i].position[1]);
            object->Put("feather", disturbance[i].feather);
            object->Put("noiseScale", disturbance[i].noiseScale);
            object->Put("noiseFrequency", disturbance[i].noiseFrequency);
            object->Put("noiseAmplitude", disturbance[i].noiseAmplitude);
            disturbanceFieldsArray->Put(std::to_string(i).c_str(), object);
        }
        json->Put("disturbanceFields", disturbanceFieldsArray);
    }
    ParseParticleObject(json, filter);
}

void ParticlePattern::UpdateDisturbance(const std::vector<ParticleDisturbance>& disturbanceArray)
{
    if (disturbanceArray.size() == 0) {
        return;
    }
    const std::vector<ParticleDisturbance>& disturbance = GetDisturbance();
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

void ParticlePattern::updateEmitterPosition(std::vector<EmitterProperty>& props)
{
    auto frameNode = GetHost();
    for (EmitterProperty& prop : props) {
        prop.index = prop.index >= GetEmitterCount() ? 0 : prop.index;
    }
    SetEmitterProperty(props);
    RosenRenderParticle::updateEmitterPosition(frameNode, props);
}
} // namespace OHOS::Ace::NG