/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/particle/particle_model_ng.h"
#include "core/components_ng/pattern/particle/particle_pattern.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {

namespace {
constexpr Color DEFAULT_COLOR { 0xffffffff };
constexpr float MIN_BOUNDARY = -100.0f;
constexpr float MAX_BOUNDARY = 100.0f;
constexpr float MIN_LIMIT = -10000.0f;
constexpr float MAX_LIMIT = 10000.0f;
constexpr float DEFAULT_OPACITY = 1.0f;
constexpr float DEFAULT_SCALE = 1.0f;
constexpr float DEFAULT_SPIN = 0.0f;
constexpr float DEFAULT_SPEED = 0.0f;
constexpr float DEFAULT_ANGLE = 0.0f;
constexpr float MIN_OPACITY = 0.0f;
constexpr float MIN_SCALE = 0.0f;
constexpr float MIN_SPIN = MIN_LIMIT;
constexpr float MIN_SPEED = 0.0f;
constexpr float MIN_ANGLE = MIN_LIMIT;
constexpr float MAX_OPACITY = 1.0f;
constexpr float MAX_SCALE = MAX_LIMIT;
constexpr float MAX_SPIN = MAX_LIMIT;
constexpr float MAX_SPEED = MAX_LIMIT;
constexpr float MAX_ANGLE = MAX_LIMIT;
constexpr int32_t PARTICLE_DEFAULT_EMITTER_RATE = 5;

void ParseSize(std::pair<Dimension, Dimension>& size, const Ark_Tuple_Dimension_Dimension& value)
{
    auto dimPair = Converter::Convert<std::pair<Dimension, Dimension>>(value);
    auto width = dimPair.first;
    auto height = dimPair.second;
    if (GreatOrEqual(width.Value(), 0.0)) {
        size.first = width;
    }
    if (GreatOrEqual(height.Value(), 0.0)) {
        size.second = height;
    }
}
int32_t ParseEmitRate(const Opt_Number& value)
{
    int32_t emitRate = PARTICLE_DEFAULT_EMITTER_RATE;
    std::optional<int32_t> emitRateOpt = Converter::OptConvert<int32_t>(value);
    if (emitRateOpt && *emitRateOpt >= 0) {
        emitRate = *emitRateOpt;
    }
    return emitRate;
}
std::pair<float, float> ParseParticleRange(const Ark_Tuple_Number_Number& src, float defaultValue)
{
    auto from = Converter::Convert<float>(src.value0);
    auto to = Converter::Convert<float>(src.value1);
    if (GreatNotEqual(from, to)) {
        return std::pair<float, float>(defaultValue, defaultValue);
    }
    return std::pair<float, float>(from, to);
}
std::pair<Color, Color> ParseParticleColor(const Ark_Tuple_ResourceColor_ResourceColor& src)
{
    std::pair<Color, Color> result(DEFAULT_COLOR, DEFAULT_COLOR);
    std::optional<Color> color;
    color = Converter::OptConvert<Color>(src.value0);
    if (color) {
        result.first = *color;
    }
    color = Converter::OptConvert<Color>(src.value1);
    if (color) {
        result.second = *color;
    }
    return result;
}
void SetNoneColorUpdater(ParticleColorPropertyUpdater& updater)
{
    updater.SetUpdateType(UpdaterType::NONE_UPDATER);
    ParticleColorPropertyUpdaterConfig noneUpdaterConfig;
    noneUpdaterConfig.SetInValid(0);
    updater.SetConfig(noneUpdaterConfig);
}
void ParseFloatInitRange(const Ark_Tuple_Number_Number& arkRange, ParticleFloatPropertyOption& floatOption,
    float defaultValue, float minValue, float maxValue)
{
    float from = Converter::Convert<float>(arkRange.value0);
    float to = Converter::Convert<float>(arkRange.value1);
    if (GreatNotEqual(minValue, MIN_BOUNDARY) && LessNotEqual(from, minValue)) {
        from = defaultValue;
    }
    if (LessNotEqual(maxValue, MAX_BOUNDARY) && GreatNotEqual(from, maxValue)) {
        from = defaultValue;
    }
    if (GreatNotEqual(minValue, MIN_BOUNDARY) && LessNotEqual(to, minValue)) {
        to = defaultValue;
    }
    if (LessNotEqual(maxValue, MAX_BOUNDARY) && GreatNotEqual(to, maxValue)) {
        to = defaultValue;
    }
    if (GreatNotEqual(from, to)) {
        from = defaultValue;
        to = defaultValue;
    }
    auto range = std::pair<float, float>(from, to);
    floatOption.SetRange(range);
}

RefPtr<Curve> ParseCurve(const Opt_Union_curves_Curve_curves_ICurve arkCurve)
{
    std::optional<RefPtr<Curve>> curveOpt = Converter::OptConvert<RefPtr<Curve>>(arkCurve);
    if (curveOpt && *curveOpt) {
        return *curveOpt;
    }
    return Curves::LINEAR;
}

bool ParseFloatRandomConfig(const Opt_Union_Tuple_Number_Number_Array_ParticlePropertyAnimationNumberInner& arkObject,
    ParticleFloatPropertyUpdater& updater)
{
    if (arkObject.tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return false;
    }
    constexpr int RANDOM_INDEX = 0;
    if (arkObject.value.selector != RANDOM_INDEX) {
        return false;
    }
    auto randomRangePair = ParseParticleRange(arkObject.value.value0, 0.0f);
    ParticleFloatPropertyUpdaterConfig randomUpdaterConfig;
    randomUpdaterConfig.SetRandomConfig(randomRangePair);
    updater.SetConfig(randomUpdaterConfig);
    return true;
}
std::list<NG::ParticlePropertyAnimation<float>> ParseAnimationFloatArray(
    const Array_ParticlePropertyAnimationNumberInner& arkArray, float defaultValue, float minValue, float maxValue)
{
    std::list<NG::ParticlePropertyAnimation<float>> particleAnimationFloatArray;
    for (int i = 0; i < arkArray.length; ++i) {
        NG::ParticlePropertyAnimation<float> floatPropertyAnimation;
        const auto& arkItem = arkArray.array[i];
        float from = Converter::Convert<float>(arkItem.from);
        if (GreatNotEqual(minValue, MIN_BOUNDARY) && LessNotEqual(from, minValue)) {
            from = defaultValue;
        }
        if (LessNotEqual(maxValue, MAX_BOUNDARY) && GreatNotEqual(from, maxValue)) {
            from = defaultValue;
        }
        floatPropertyAnimation.SetFrom(from);
        float to = Converter::Convert<float>(arkItem.to);
        if (GreatNotEqual(minValue, MIN_BOUNDARY) && LessNotEqual(to, minValue)) {
            to = defaultValue;
        }
        if (LessNotEqual(maxValue, MAX_BOUNDARY) && GreatNotEqual(to, maxValue)) {
            to = defaultValue;
        }
        floatPropertyAnimation.SetTo(to);
        int32_t startMillis = Converter::Convert<int32_t>(arkItem.startMillis);
        if (startMillis < 0) {
            startMillis = 0;
        }
        floatPropertyAnimation.SetStartMills(startMillis);
        int32_t endMillis = Converter::Convert<int32_t>(arkItem.endMillis);
        if (endMillis < 0) {
            endMillis = 0;
        }
        floatPropertyAnimation.SetEndMills(endMillis);
        RefPtr<Curve> curve = ParseCurve(arkItem.curve);
        floatPropertyAnimation.SetCurve(curve);
        particleAnimationFloatArray.emplace_back(floatPropertyAnimation);
    }
    return particleAnimationFloatArray;
}
bool ParseFloatCurveConfig(const Opt_Union_Tuple_Number_Number_Array_ParticlePropertyAnimationNumberInner& arkObject,
    ParticleFloatPropertyUpdater& updater, float defaultValue, float minValue, float maxValue)
{
    if (arkObject.tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return false;
    }
    constexpr int ANIMATION_INDEX = 1;
    if (arkObject.value.selector != ANIMATION_INDEX) {
        return false;
    }
    auto particleAnimationFloatArray =
        ParseAnimationFloatArray(arkObject.value.value1, defaultValue, minValue, maxValue);
    NG::ParticleFloatPropertyUpdaterConfig updateConfig;
    updateConfig.SetAnimations(particleAnimationFloatArray);
    updater.SetConfig(updateConfig);
    return true;
}
bool ParseFloatUpdater(const Ark_ParticleUpdaterOptionsInner& arkObject, ParticleFloatPropertyUpdater& updater,
    float defaultValue, float minValue, float maxValue)
{
    std::optional<UpdaterType> typeOpt = Converter::OptConvert<UpdaterType>(arkObject.type);
    UpdaterType type = UpdaterType::NONE_UPDATER;
    if (typeOpt) {
        type = *typeOpt;
    }
    updater.SetUpdaterType(type);
    if (type == UpdaterType::RANDOM) {
        if (!ParseFloatRandomConfig(arkObject.config, updater)) {
            auto randomRangePair = std::pair<float, float>(0.0f, 0.0f);
            NG::ParticleFloatPropertyUpdaterConfig randomUpdaterConfig;
            randomUpdaterConfig.SetRandomConfig(randomRangePair);
            updater.SetConfig(randomUpdaterConfig);
        }
        return true;
    } else if (type == NG::UpdaterType::CURVE) {
        if (!ParseFloatCurveConfig(arkObject.config, updater, defaultValue, minValue, maxValue)) {
            std::list<NG::ParticlePropertyAnimation<float>> particleAnimationFloatArray;
            NG::ParticleFloatPropertyUpdaterConfig updateConfig;
            updateConfig.SetAnimations(particleAnimationFloatArray);
            updater.SetConfig(updateConfig);
        }
        return true;
    }
    return false;
}
void ParseFloatOption(const Ark_ParticlePropertyOptionsInner& arkObject, ParticleFloatPropertyOption& floatOption,
    float defaultValue, float minValue, float maxValue)
{
    ParseFloatInitRange(arkObject.range, floatOption, defaultValue, minValue, maxValue);
    NG::ParticleFloatPropertyUpdater updater;
    if (arkObject.updater.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        if (ParseFloatUpdater(arkObject.updater.value, updater, defaultValue, minValue, maxValue)) {
            floatOption.SetUpdater(updater);
            return;
        }
    }
    updater.SetUpdaterType(UpdaterType::NONE_UPDATER);
    NG::ParticleFloatPropertyUpdaterConfig updateConfig;
    updateConfig.SetNullStr("");
    updater.SetConfig(updateConfig);
    floatOption.SetUpdater(updater);
}
void ParseParticleVelocity(const Opt_VelocityOptions& optVelocity, NG::VelocityProperty& velocity)
{
    auto defaultPair = std::pair<float, float>(0.0f, 0.0f);
    if (optVelocity.tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        velocity.SetSpeedRange(defaultPair);
        velocity.SetAngleRange(defaultPair);
        return;
    }
    auto speedPair = ParseParticleRange(optVelocity.value.speed, 0.0f);
    velocity.SetSpeedRange(speedPair);
    auto anglePair = ParseParticleRange(optVelocity.value.angle, 0.0f);
    velocity.SetAngleRange(anglePair);
}
void ParseParticleAcceleration(
    const Opt_AccelerationOptionsInner& optAcceleration, NG::AccelerationProperty& acceleration)
{
    if (optAcceleration.tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    const auto& arkAcceleration = optAcceleration.value;
    if (arkAcceleration.speed.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        NG::ParticleFloatPropertyOption speedOption;
        ParseFloatOption(arkAcceleration.speed.value, speedOption, DEFAULT_SPEED, MIN_SPEED, MAX_SPEED);
        acceleration.SetSpeed(speedOption);
    }
    if (arkAcceleration.angle.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        NG::ParticleFloatPropertyOption angleOption;
        ParseFloatOption(arkAcceleration.angle.value, angleOption, DEFAULT_ANGLE, MIN_ANGLE, MAX_ANGLE);
        acceleration.SetAngle(angleOption);
    }
}
void ParseEmitterProperty(std::vector<EmitterProperty>& data, const Ark_EmitterPropertyInner& arkEmitter)
{
    EmitterProperty emitterProperty;
    uint32_t index = Converter::Convert<uint32_t>(arkEmitter.index);
    emitterProperty.index = index;

    std::optional<int32_t> emitRateOpt = Converter::OptConvert<int32_t>(arkEmitter.emitRate);
    if (emitRateOpt) {
        emitterProperty.emitRate = *emitRateOpt >= 0 ? *emitRateOpt : PARTICLE_DEFAULT_EMITTER_RATE;
    }

    if (arkEmitter.position.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        const auto& arkPosition = arkEmitter.position.value;
        auto positionXValue = Converter::Convert<float>(arkPosition.x);
        auto positionYValue = Converter::Convert<float>(arkPosition.y);
        emitterProperty.position = { positionXValue, positionYValue };
    }

    if (arkEmitter.size.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        const auto& arkSize = arkEmitter.size.value;
        auto sizeXValue = Converter::Convert<float>(arkSize.width);
        auto sizeYValue = Converter::Convert<float>(arkSize.height);
        if (sizeXValue > 0 && sizeYValue > 0) {
            emitterProperty.size = { sizeXValue, sizeYValue };
        }
    }

    data.push_back(emitterProperty);
}
void GetSizeAndPositionValues(const Ark_DisturbanceFieldOptionsInner& arkDisturbance, std::pair<int32_t, int32_t>& size,
    std::pair<int32_t, int32_t>& position)
{
    if (arkDisturbance.size.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        size.first = Converter::Convert<int32_t>(arkDisturbance.size.value.width);
        size.second = Converter::Convert<int32_t>(arkDisturbance.size.value.height);
    }
    if (arkDisturbance.position.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        position.first = Converter::Convert<int32_t>(arkDisturbance.position.value.x);
        position.second = Converter::Convert<int32_t>(arkDisturbance.position.value.y);
    }
}
void AddDisturbance(std::vector<ParticleDisturbance>& dataArray, const Ark_DisturbanceFieldOptionsInner& arkDisturbance)
{
    float strength = Converter::ConvertOrDefault<float>(arkDisturbance.strength, 0.0f);
    ParticleDisturbanceShapeType shape = Converter::ConvertOrDefault<ParticleDisturbanceShapeType>(
        arkDisturbance.shape, ParticleDisturbanceShapeType::RECT);
    std::pair<int32_t, int32_t> size(0, 0);
    std::pair<int32_t, int32_t> position(0, 0);
    GetSizeAndPositionValues(arkDisturbance, size, position);
    std::optional<int32_t> featherOpt = Converter::OptConvert<int32_t>(arkDisturbance.feather);
    int32_t feather = 0;
    if (featherOpt) {
        constexpr int32_t maxFeather = 100;
        feather = std::clamp(*featherOpt, 0, maxFeather);
    }
    float noiseScale = 1.0f;
    if (arkDisturbance.noiseScale.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        noiseScale = Converter::Convert<float>(arkDisturbance.noiseScale.value);
        if (noiseScale < 0.0f) {
            noiseScale = 1.0f;
        }
    }
    float noiseFrequency = 1.0f;
    if (arkDisturbance.noiseFrequency.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        noiseFrequency = Converter::Convert<float>(arkDisturbance.noiseFrequency.value);
        if (noiseFrequency < 0.0f) {
            noiseFrequency = 1.0f;
        }
    }
    float noiseAmplitude = 1.0f;
    if (arkDisturbance.noiseAmplitude.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        noiseAmplitude = Converter::Convert<float>(arkDisturbance.noiseAmplitude.value);
        if (noiseAmplitude < 0.0f) {
            noiseAmplitude = 1.0f;
        }
    }
    ParticleDisturbance disturbanceField;
    disturbanceField.strength = strength;
    disturbanceField.shape = shape;
    disturbanceField.size[0] = size.first;
    disturbanceField.size[1] = size.second;
    disturbanceField.position[0] = position.first;
    disturbanceField.position[1] = position.second;
    disturbanceField.feather = feather;
    disturbanceField.noiseScale = noiseScale;
    disturbanceField.noiseFrequency = noiseFrequency;
    disturbanceField.noiseAmplitude = noiseAmplitude;
    dataArray.push_back(disturbanceField);
}

bool ParseParticleConfig(const ParticleType& type, const Ark_ParticleConfigs& arkConfig, ParticleConfig& result)
{
    if (type == ParticleType::IMAGE) {
        if (arkConfig.selector != 1) { // 1 is image selector
            return false;
        }
        const Ark_ImageParticleParameters& imageConfig = arkConfig.value1;
        ImageParticleParameter imageParameter;
        std::optional<std::string> srcString = Converter::OptConvert<std::string>(imageConfig.src);
        if (!srcString) {
            return false;
        }
        imageParameter.SetImageSource(*srcString);
        auto size = std::pair<Dimension, Dimension>(Dimension(0.0), Dimension(0.0));
        ParseSize(size, imageConfig.size);
        imageParameter.SetSize(size);
        std::optional<ImageFit> imageFitOpt = Converter::OptConvert<ImageFit>(imageConfig.objectFit);
        imageParameter.SetImageFit(imageFitOpt.value_or(ImageFit::COVER));
        result.SetImageParticleParameter(imageParameter);
    } else {
        CalcDimension radius;
        if (arkConfig.selector == 0) { // 0 is point selector
            const Ark_PointParticleParameters& pointConfig = arkConfig.value0;
            std::optional<CalcDimension> radiusOpt = Converter::OptConvert<CalcDimension>(pointConfig.radius);
            if (radiusOpt) {
                radius = *radiusOpt;
            }
        }
        NG::PointParticleParameter pointParameter;
        pointParameter.SetRadius(!radius.IsNonPositive() ? radius.ConvertToPx() : 0.0f);
        result.SetPointParticleParameter(pointParameter);
    }
    return true;
}

bool ParseParticleObject(const Ark_EmitterParticleOptions& src, Particle& result)
{
    std::optional<ParticleType> typeOpt = Converter::OptConvert<ParticleType>(src.type);
    auto type = typeOpt.value_or(ParticleType::POINT);
    result.SetParticleType(type);
    ParticleConfig particleConfig;
    if (!ParseParticleConfig(type, src.config, particleConfig)) {
        return false;
    }
    result.SetConfig(particleConfig);
    auto count = 0;
    int32_t countIntValue = Converter::Convert<int32_t>(src.count);
    if (countIntValue >= -1) {
        count = countIntValue;
    }
    result.SetCount(count);
    int64_t lifeTime = 1000;
    auto lifeTimeIntValue = Converter::OptConvert<int32_t>(src.lifetime);
    if (lifeTimeIntValue && *lifeTimeIntValue >= -1) {
        lifeTime = *lifeTimeIntValue;
    }
    result.SetLifeTime(lifeTime);
    int64_t lifeTimeRange = 0;
    auto lifeTimeRangeIntValue = Converter::OptConvert<int32_t>(src.lifetimeRange);
    if (lifeTimeRangeIntValue && *lifeTimeRangeIntValue >= 0) {
        lifeTimeRange = *lifeTimeRangeIntValue;
    }
    result.SetLifeTimeRange(lifeTimeRange);
    return true;
}

bool ParseEmitterOption(const Ark_EmitterOptionsInner& src, EmitterOption& result)
{
    Particle particle;
    if (!ParseParticleObject(src.particle, particle)) {
        return false;
    }
    result.SetParticle(particle);
    auto emitRate = ParseEmitRate(src.emitRate);
    result.SetEmitterRate(emitRate);
    auto shapeOpt = Converter::OptConvert<ParticleEmitterShape>(src.shape);
    result.SetShape(shapeOpt.value_or(ParticleEmitterShape::RECTANGLE));
    auto positionValue = Converter::OptConvert<std::pair<Dimension, Dimension>>(src.position);
    if (positionValue) {
        result.SetPosition(*positionValue);
    } else {
        result.SetPosition(std::pair<Dimension, Dimension>(Dimension(0.0f), Dimension(0.0f)));
    }
    auto width = Dimension(1.0, DimensionUnit::PERCENT);
    auto height = Dimension(1.0, DimensionUnit::PERCENT);
    auto sizeValue = std::pair<Dimension, Dimension>(width, height);
    if (src.size.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        ParseSize(sizeValue, src.size.value);
    }
    result.SetSize(sizeValue);
    return true;
}

void ParseColorRandomUpdater(const Opt_Union_ParticleColorOptions_Array_ParticlePropertyAnimationColorInner& config,
    ParticleColorPropertyUpdater& result)
{
    NG::ParticleColorPropertyUpdaterConfig randomUpdaterConfig;
    NG::ColorParticleRandomUpdateConfig colorRandomConfig;
    if (config.tag != InteropTag::INTEROP_TAG_UNDEFINED && config.value.selector == 0) {
        const auto& arkColorOption = config.value.value0;
        auto r = ParseParticleRange(arkColorOption.r, 0.0f);
        auto g = ParseParticleRange(arkColorOption.g, 0.0f);
        auto b = ParseParticleRange(arkColorOption.b, 0.0f);
        auto a = ParseParticleRange(arkColorOption.a, 0.0f);
        colorRandomConfig.SetRedRandom(r);
        colorRandomConfig.SetGreenRandom(g);
        colorRandomConfig.SetBlueRandom(b);
        colorRandomConfig.SetAlphaRandom(a);
        randomUpdaterConfig.SetRandomConfig(colorRandomConfig);
        result.SetConfig(randomUpdaterConfig);
        return;
    }
    auto defaultPair = std::pair<float, float>(0.0f, 0.0f);
    colorRandomConfig.SetRedRandom(defaultPair);
    colorRandomConfig.SetGreenRandom(defaultPair);
    colorRandomConfig.SetBlueRandom(defaultPair);
    colorRandomConfig.SetAlphaRandom(defaultPair);
    randomUpdaterConfig.SetRandomConfig(colorRandomConfig);
    result.SetConfig(randomUpdaterConfig);
}

void ParseColorCurveUpdater(const Opt_Union_ParticleColorOptions_Array_ParticlePropertyAnimationColorInner& config,
    ParticleColorPropertyUpdater& result)
{
    std::list<NG::ParticlePropertyAnimation<Color>> particleAnimationColorArray;
    NG::ParticleColorPropertyUpdaterConfig animationUpdaterConfig;
    if (config.tag != InteropTag::INTEROP_TAG_UNDEFINED && config.value.selector == 1) {
        const auto& arkArray = config.value.value1;
        for (int32_t i = 0; i < arkArray.length; ++i) {
            ParticlePropertyAnimation<Color> colorPropertyAnimation;
            const auto& animationItem = arkArray.array[i];
            std::optional<Color> from = Converter::OptConvert<Color>(animationItem.from);
            colorPropertyAnimation.SetFrom(from.value_or(DEFAULT_COLOR));
            std::optional<Color> to = Converter::OptConvert<Color>(animationItem.to);
            colorPropertyAnimation.SetTo(to.value_or(DEFAULT_COLOR));
            int32_t startMillis = Converter::Convert<int32_t>(animationItem.startMillis);
            if (startMillis < 0) {
                startMillis = 0;
            }
            colorPropertyAnimation.SetStartMills(startMillis);
            int endMillis = Converter::Convert<int32_t>(animationItem.endMillis);
            if (endMillis < 0) {
                endMillis = 0;
            }
            colorPropertyAnimation.SetEndMills(endMillis);
            auto curve = ParseCurve(animationItem.curve);
            colorPropertyAnimation.SetCurve(curve);
            particleAnimationColorArray.emplace_back(colorPropertyAnimation);
        }
        animationUpdaterConfig.SetAnimationArray(particleAnimationColorArray);
        result.SetConfig(animationUpdaterConfig);
        return;
    }
    animationUpdaterConfig.SetAnimationArray(particleAnimationColorArray);
    result.SetConfig(animationUpdaterConfig);
}

bool ParseColorUpdater(const Ark_ParticleColorUpdaterOptionsInner& src, ParticleColorPropertyUpdater& updater)
{
    std::optional<UpdaterType> type = Converter::OptConvert<UpdaterType>(src.type);
    if (type) {
        updater.SetUpdateType(*type);
        if (type == NG::UpdaterType::RANDOM) {
            ParseColorRandomUpdater(src.config, updater);
            return true;
        } else if (type == NG::UpdaterType::CURVE) {
            ParseColorCurveUpdater(src.config, updater);
            return true;
        }
    }
    return false;
}

void ParseColorOption(const Ark_ParticleColorPropertyOptionsInner& src, ParticleColorPropertyOption& result)
{
    std::pair<Color, Color> colorRange = ParseParticleColor(src.range);
    result.SetRange(colorRange);
    std::optional<DistributionType> colorDist = Converter::OptConvert<DistributionType>(src.distributionType);
    result.SetDistribution(colorDist.value_or(DistributionType::UNIFORM));
    ParticleColorPropertyUpdater updater;
    if (src.updater.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        if (ParseColorUpdater(src.updater.value, updater)) {
            result.SetUpdater(updater);
            return;
        }
    }
    SetNoneColorUpdater(updater);
    result.SetUpdater(updater);
}

bool ParseParticleOption(const Ark_ParticleOptionsInner& src, ParticleOption& result)
{
    EmitterOption emitterOption;
    if (!ParseEmitterOption(src.emitter, emitterOption)) {
        return false;
    }
    result.SetEmitterOption(emitterOption);
    if (src.color.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        ParticleColorPropertyOption colorOption;
        ParseColorOption(src.color.value, colorOption);
        result.SetParticleColorOption(colorOption);
    }
    if (src.opacity.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        NG::ParticleFloatPropertyOption opacityOption;
        ParseFloatOption(src.opacity.value, opacityOption, DEFAULT_OPACITY, MIN_OPACITY, MAX_OPACITY);
        result.SetParticleOpacityOption(opacityOption);
    }
    if (src.scale.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        NG::ParticleFloatPropertyOption scaleOption;
        ParseFloatOption(src.scale.value, scaleOption, DEFAULT_SCALE, MIN_SCALE, MAX_SCALE);
        result.SetParticleScaleOption(scaleOption);
    }
    NG::VelocityProperty velocity;
    ParseParticleVelocity(src.velocity, velocity);
    result.SetParticleVelocityOption(velocity);

    NG::AccelerationProperty acceleration;
    ParseParticleAcceleration(src.acceleration, acceleration);
    result.SetParticleAccelerationOption(acceleration);

    if (src.spin.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        NG::ParticleFloatPropertyOption spinOption;
        ParseFloatOption(src.spin.value, spinOption, DEFAULT_SPIN, MIN_SPIN, MAX_SPIN);
        result.SetParticleSpinOption(spinOption);
    }
    return true;
}

void ParseParticleArray(const Ark_ParticlesInner& src, std::list<ParticleOption>& result)
{
    for (int32_t i = 0; i != src.particles.length; ++i) {
        ParticleOption option;
        if (!ParseParticleOption(src.particles.array[i], option)) {
            continue;
        }
        result.emplace_back(option);
    }
}
} // namespace
namespace ParticleHelperAccessor {
void SetDisturbanceFieldsImpl(Ark_NativePointer node,
                              const Opt_Array_DisturbanceFieldOptionsInner* disturbanceFields)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(disturbanceFields);
    if (disturbanceFields->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    std::vector<ParticleDisturbance> dataArray;
    const auto& arkDisturbanceFieldOptions = disturbanceFields->value;
    for (int32_t i = 0; i < arkDisturbanceFieldOptions.length; i++) {
        AddDisturbance(dataArray, arkDisturbanceFieldOptions.array[i]);
    }
    ParticleModelNG::DisturbanceField(dataArray, frameNode);
}
void SetEmitterPropertyImpl(Ark_NativePointer node,
                            const Opt_Array_EmitterPropertyInner* emitter)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(emitter);
    if (emitter->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    std::vector<EmitterProperty> dataArray;
    const auto& arkEmitter = emitter->value;
    for (int32_t i = 0; i < arkEmitter.length; ++i) {
        ParseEmitterProperty(dataArray, arkEmitter.array[i]);
    }
    ParticleModelNG::updateEmitter(dataArray, frameNode);
}
Ark_NativePointer ParticleConstructImpl(Ark_Int32 id,
                                        Ark_Int32 flags)
{
    auto frameNode =
        FrameNode::CreateFrameNode(V2::PARTICLE_ETS_TAG, id, AceType::MakeRefPtr<ParticlePattern>(0));
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
void SetParticleOptionsImpl(Ark_NativePointer node,
                            const Ark_ParticlesInner* particles)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(particles);
    std::list<ParticleOption> options;
    ParseParticleArray(*particles, options);
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateParticleOptionArray(options);
}
} // ParticleHelperAccessor
const GENERATED_ArkUIParticleHelperAccessor* GetParticleHelperAccessor()
{
    static const GENERATED_ArkUIParticleHelperAccessor ParticleHelperAccessorImpl {
        ParticleHelperAccessor::SetDisturbanceFieldsImpl,
        ParticleHelperAccessor::SetEmitterPropertyImpl,
        ParticleHelperAccessor::ParticleConstructImpl,
        ParticleHelperAccessor::SetParticleOptionsImpl,
    };
    return &ParticleHelperAccessorImpl;
}

}
