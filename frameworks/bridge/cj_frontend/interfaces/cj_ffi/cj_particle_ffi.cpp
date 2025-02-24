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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_particle_ffi.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/components/chart/chart_component.h"
#include "core/components_ng/pattern/particle/particle_model.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

constexpr int32_t DEAFULT_LIFE_TIME = 1000;
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

extern "C" {
VectorParticleOptionsHandle FFICJCreateVectorParticleOptions(int64_t size)
{
    LOGI("Create ParticleOptions Vector");
    return new std::vector<ParticleOptions>(size);
}

void FFICJVectorParticleOptionsSetElement(
    VectorParticleOptionsHandle vec, int64_t index, ParticleOptions particleOptions)
{
    LOGI("ParticleOptions Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<ParticleOptions>*>(vec);
    (*actualVec)[index] = particleOptions;
    LOGI("ParticleOptions Vector Set Element Success");
}

void FFICJVectorParticleOptionsDelete(VectorParticleOptionsHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<ParticleOptions>*>(vec);
    delete actualVec;
}

VectorParticlePropertyAnimationHandle FFICJCreateVectorParticlePropertyAnimation(int64_t size)
{
    LOGI("Create ParticlePropertyAnimation Vector");
    return new std::vector<ParticlePropertyAnimation>(size);
}

void FFICJVectorParticlePropertyAnimationSetElement(
    VectorParticlePropertyAnimationHandle vec, int64_t index, ParticlePropertyAnimation particlePropertyAnimation)
{
    LOGI("ParticlePropertyAnimation Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<ParticlePropertyAnimation>*>(vec);
    (*actualVec)[index] = particlePropertyAnimation;
    LOGI("ParticlePropertyAnimation Vector Set Element Success");
}

void FFICJVectorParticlePropertyAnimationDelete(VectorParticlePropertyAnimationHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<ParticlePropertyAnimation>*>(vec);
    delete actualVec;
}

void ParseFloatPropertyAnimation(ParticlePropertyAnimation animation,
    NG::ParticlePropertyAnimation<float>& floatPropertyAnimation, float defaultValue, float minValue, float maxValue)
{
    float from = defaultValue;
    float to = defaultValue;
    if (GreatNotEqual(animation.fromFloat, minValue) && GreatNotEqual(maxValue, animation.fromFloat)) {
        from = animation.fromFloat;
    }
    if (GreatNotEqual(animation.toFloat, minValue) && GreatNotEqual(maxValue, animation.toFloat)) {
        to = animation.toFloat;
    }
    floatPropertyAnimation.SetFrom(animation.fromFloat);
    floatPropertyAnimation.SetTo(animation.toFloat);
    floatPropertyAnimation.SetStartMills(animation.startMillis);
    floatPropertyAnimation.SetEndMills(animation.endMillis);
    RefPtr<Curve> curve_;
    std::string src(animation.curve);
    curve_ = CreateCurve(src);
    if (!curve_) {
        curve_ = AceType::MakeRefPtr<LinearCurve>();
    }
    floatPropertyAnimation.SetCurve(curve_);
}

void ParseFloatCurveUpdater(ParticlePropertyUpdaterConfigs config,
    OHOS::Ace::NG::ParticleFloatPropertyUpdater& updater_, float defaultValue, float minValue, float maxValue)
{
    std::list<NG::ParticlePropertyAnimation<float>> particleAnimationFloatArray;
    NG::ParticleFloatPropertyUpdaterConfig randomUpdaterConfig;
    auto curValue = *reinterpret_cast<std::vector<ParticlePropertyAnimation>*>(config.cur);
    for (size_t i = 0; i < curValue.size(); ++i) {
        NG::ParticlePropertyAnimation<float> floatPropertyAnimation;
        ParseFloatPropertyAnimation(curValue[i], floatPropertyAnimation, defaultValue, minValue, maxValue);
        particleAnimationFloatArray.emplace_back(floatPropertyAnimation);
    }
    randomUpdaterConfig.SetAnimations(particleAnimationFloatArray);
    updater_.SetConfig(randomUpdaterConfig);
}

void ParseParticleUpdaterOptions(ParticleUpdaterOptions updater, OHOS::Ace::NG::ParticleFloatPropertyUpdater& updater_,
    float defaultValue, float minValue, float maxValue)
{
    auto type_ = static_cast<NG::UpdaterType>(updater.type);
    updater_.SetUpdaterType(type_);
    if (type_ == NG::UpdaterType::RANDOM) {
        auto randomRangePair = std::pair<float, float>(updater.config.from, updater.config.to);
        NG::ParticleFloatPropertyUpdaterConfig randomUpdaterConfig;
        randomUpdaterConfig.SetRandomConfig(randomRangePair);
        updater_.SetConfig(randomUpdaterConfig);
    } else if (type_ == NG::UpdaterType::CURVE) {
        ParseFloatCurveUpdater(updater.config, updater_, defaultValue, minValue, maxValue);
    }
}

void ParseParticlePropertyOptions(ParticlePropertyOptions options,
    OHOS::Ace::NG::ParticleFloatPropertyOption& floatOption, float defaultValue, float minValue, float maxValue)
{
    float from = defaultValue;
    float to = defaultValue;
    if (GreatNotEqual(options.rangeFrom, minValue) && GreatNotEqual(maxValue, options.rangeFrom)) {
        from = options.rangeFrom;
    }
    if (GreatNotEqual(options.rangeTo, minValue) && GreatNotEqual(maxValue, options.rangeTo)) {
        to = options.rangeTo;
    }
    auto range = std::pair<float, float>(from, to);
    floatOption.SetRange(range);

    NG::ParticleFloatPropertyUpdater updater_;
    ParseParticleUpdaterOptions(options.updater, updater_, defaultValue, minValue, maxValue);
    floatOption.SetUpdater(updater_);
}

void ParseAccelerationOptions(AccelerationOptions acceleration, OHOS::Ace::NG::AccelerationProperty& acceleration_)
{
    OHOS::Ace::NG::ParticleFloatPropertyOption speedOption;
    ParseParticlePropertyOptions(acceleration.speed, speedOption, DEFAULT_SPEED, MIN_SPEED, MAX_SPEED);
    acceleration_.SetSpeed(speedOption);
    OHOS::Ace::NG::ParticleFloatPropertyOption angleOption;
    ParseParticlePropertyOptions(acceleration.angle, angleOption, DEFAULT_ANGLE, MIN_ANGLE, MAX_ANGLE);
    acceleration_.SetAngle(angleOption);
}

void ParseVelocityOptions(VelocityOptions velocity, OHOS::Ace::NG::VelocityProperty& velocity_)
{
    auto speedPair = std::pair<float, float>(velocity.speedFrom, velocity.speedTo);
    auto anglePair = std::pair<float, float>(velocity.angleFrom, velocity.angleTo);
    velocity_.SetSpeedRange(speedPair);
    velocity_.SetAngleRange(anglePair);
}

void ParseColorRandomUpdater(
    ParticleColorPropertyUpdaterConfigs config, OHOS::Ace::NG::ParticleColorPropertyUpdater& updater_)
{
    NG::ParticleColorPropertyUpdaterConfig randomUpdaterConfig;
    NG::ColorParticleRandomUpdateConfig colorRandomConfig;
    auto rRangeValue = std::pair<float, float>(static_cast<float>(config.rFrom), static_cast<float>(config.rTo));
    auto gRangeValue = std::pair<float, float>(static_cast<float>(config.gFrom), static_cast<float>(config.gTo));
    auto bRangeValue = std::pair<float, float>(static_cast<float>(config.bFrom), static_cast<float>(config.bTo));
    auto aRangeValue = std::pair<float, float>(static_cast<float>(config.aFrom), static_cast<float>(config.aTo));
    colorRandomConfig.SetRedRandom(rRangeValue);
    colorRandomConfig.SetGreenRandom(gRangeValue);
    colorRandomConfig.SetBlueRandom(bRangeValue);
    colorRandomConfig.SetAlphaRandom(aRangeValue);
    randomUpdaterConfig.SetRandomConfig(colorRandomConfig);
    updater_.SetConfig(randomUpdaterConfig);
}

void ParseColorPropertyAnimation(
    ParticlePropertyAnimation animation, NG::ParticlePropertyAnimation<Color>& colorPropertyAnimation)
{
    Color from = Color(animation.fromColor);
    Color to = Color(animation.toColor);
    colorPropertyAnimation.SetFrom(from);
    colorPropertyAnimation.SetTo(to);
    colorPropertyAnimation.SetStartMills(animation.startMillis);
    colorPropertyAnimation.SetEndMills(animation.endMillis);
    RefPtr<Curve> curve_;
    std::string src(animation.curve);
    curve_ = CreateCurve(src);
    if (!curve_) {
        curve_ = AceType::MakeRefPtr<LinearCurve>();
    }
    colorPropertyAnimation.SetCurve(curve_);
}

void ParseColorCurveUpdater(
    ParticleColorPropertyUpdaterConfigs config, OHOS::Ace::NG::ParticleColorPropertyUpdater& updater_)
{
    std::list<NG::ParticlePropertyAnimation<Color>> particleAnimationColorArray;
    NG::ParticleColorPropertyUpdaterConfig randomUpdaterConfig;
    auto curValue = *reinterpret_cast<std::vector<ParticlePropertyAnimation>*>(config.cur);
    for (size_t i = 0; i < curValue.size(); ++i) {
        NG::ParticlePropertyAnimation<Color> colorPropertyAnimation;
        ParseColorPropertyAnimation(curValue[i], colorPropertyAnimation);
        particleAnimationColorArray.emplace_back(colorPropertyAnimation);
    }
    randomUpdaterConfig.SetAnimationArray(particleAnimationColorArray);
    updater_.SetConfig(randomUpdaterConfig);
}

void ParseParticleColorUpdaterOptions(
    ParticleColorUpdaterOptions& updater, OHOS::Ace::NG::ParticleColorPropertyUpdater& updater_)
{
    auto type_ = static_cast<NG::UpdaterType>(updater.type);
    updater_.SetUpdateType(type_);
    if (type_ == NG::UpdaterType::RANDOM) {
        ParseColorRandomUpdater(updater.config, updater_);
    } else if (type_ == NG::UpdaterType::CURVE) {
        ParseColorCurveUpdater(updater.config, updater_);
    }
}

void ParseParticleColorPropertyOptions(
    ParticleColorPropertyOptions& colorPropertyOptions, OHOS::Ace::NG::ParticleColorPropertyOption& colorOption)
{
    auto range = std::pair<Color, Color>(Color(colorPropertyOptions.colorFrom), Color(colorPropertyOptions.colorTo));
    colorOption.SetRange(range);
    auto colorDist = static_cast<OHOS::Ace::NG::DistributionType>(colorPropertyOptions.distributionType);
    colorOption.SetDistribution(colorDist);
    NG::ParticleColorPropertyUpdater updater_;
    ParseParticleColorUpdaterOptions(colorPropertyOptions.updater, updater_);
    colorOption.SetUpdater(updater_);
}

void ParseEmitterParticleOptions(EmitterParticleOptions& emitterParticle, OHOS::Ace::NG::Particle& particle)
{
    auto typeValue = static_cast<NG::ParticleType>(emitterParticle.type);
    particle.SetParticleType(typeValue);
    ParticleConfigs config = emitterParticle.config;
    if (typeValue == NG::ParticleType::POINT) {
        CalcDimension radius = CalcDimension(config.radius, DimensionUnit::VP);
        NG::PointParticleParameter pointParameter;
        pointParameter.SetRadius(!radius.IsNonPositive() ? radius.ConvertToPx() : 0.0f);
        NG::ParticleConfig particleConfig;
        particleConfig.SetPointParticleParameter(pointParameter);
        particle.SetConfig(particleConfig);
    } else {
        NG::ImageParticleParameter imageParameter;
        std::string src(config.src);
        imageParameter.SetImageSource(src);

        auto width = CalcDimension(config.sizeWidthValue, static_cast<DimensionUnit>(config.sizeWidthUnit));
        auto height = CalcDimension(config.sizeHeightValue, static_cast<DimensionUnit>(config.sizeHeightUnit));
        auto sizeValue = std::pair<Dimension, Dimension>(width, height);
        imageParameter.SetSize(sizeValue);

        auto fit = static_cast<ImageFit>(config.objectFit);
        imageParameter.SetImageFit(fit);
        NG::ParticleConfig particleConfig;
        particleConfig.SetImageParticleParameter(imageParameter);
        particle.SetConfig(particleConfig);
    }
    particle.SetCount(emitterParticle.count >= -1 ? emitterParticle.count : 0);
    particle.SetLifeTime(emitterParticle.lifetime >= -1 ? emitterParticle.lifetime : DEAFULT_LIFE_TIME);
    particle.SetLifeTimeRange(emitterParticle.lifeTimeRange >= 0 ? emitterParticle.lifeTimeRange : 0);
}

void ParseEmitterOptions(EmitterOptions& emitter, OHOS::Ace::NG::EmitterOption& emitterOption)
{
    OHOS::Ace::NG::Particle particle;
    ParseEmitterParticleOptions(emitter.particle, particle);
    emitterOption.SetParticle(particle);
    emitterOption.SetEmitterRate(emitter.emitRate);
    auto emitShape = static_cast<OHOS::Ace::NG::ParticleEmitterShape>(emitter.shape);
    emitterOption.SetShape(emitShape);

    CalcDimension xValue = CalcDimension(emitter.positionXValue, static_cast<DimensionUnit>(emitter.positionXUnit));
    CalcDimension yValue = CalcDimension(emitter.positionYValue, static_cast<DimensionUnit>(emitter.positionYUnit));
    auto positionValue = std::pair<Dimension, Dimension>(xValue, yValue);
    emitterOption.SetPosition(positionValue);

    CalcDimension width = CalcDimension(emitter.sizeWidthValue, static_cast<DimensionUnit>(emitter.sizeWidthUnit));
    CalcDimension height = CalcDimension(emitter.sizeHeightValue, static_cast<DimensionUnit>(emitter.sizeHeightUnit));
    auto sizeValue = std::pair<Dimension, Dimension>(width, height);
    emitterOption.SetSize(sizeValue);
}

void ParseParticleOptions(ParticleOptions& particle, OHOS::Ace::NG::ParticleOption& particleOption)
{
    // emitter
    OHOS::Ace::NG::EmitterOption emitterOption;
    ParseEmitterOptions(particle.emitter, emitterOption);
    particleOption.SetEmitterOption(emitterOption);

    // color
    OHOS::Ace::NG::ParticleColorPropertyOption colorOption;
    ParseParticleColorPropertyOptions(particle.color, colorOption);
    particleOption.SetParticleColorOption(colorOption);

    // opacity
    OHOS::Ace::NG::ParticleFloatPropertyOption opacityOption;
    ParseParticlePropertyOptions(particle.opacity, opacityOption, DEFAULT_OPACITY, MIN_OPACITY, MAX_OPACITY);
    particleOption.SetParticleOpacityOption(opacityOption);

    // scale
    OHOS::Ace::NG::ParticleFloatPropertyOption scaleOption;
    ParseParticlePropertyOptions(particle.scale, scaleOption, DEFAULT_SCALE, MIN_SCALE, MAX_SCALE);
    particleOption.SetParticleScaleOption(scaleOption);

    // velocity
    OHOS::Ace::NG::VelocityProperty velocity_;
    ParseVelocityOptions(particle.velocity, velocity_);
    particleOption.SetParticleVelocityOption(velocity_);

    // acceleration
    OHOS::Ace::NG::AccelerationProperty acceleration_;
    ParseAccelerationOptions(particle.acceleration, acceleration_);
    particleOption.SetParticleAccelerationOption(acceleration_);

    // spin
    OHOS::Ace::NG::ParticleFloatPropertyOption spinOption;
    ParseParticlePropertyOptions(particle.spin, spinOption, DEFAULT_SPIN, MIN_SPIN, MAX_SPIN);
    particleOption.SetParticleSpinOption(spinOption);
}

void FfiOHOSAceFrameworkParticleCreate(VectorParticleOptionsHandle particles)
{
    std::list<OHOS::Ace::NG::ParticleOption> arrayValue;
    auto particlesValue = *reinterpret_cast<std::vector<ParticleOptions>*>(particles);
    for (size_t i = 0; i < particlesValue.size(); ++i) {
        OHOS::Ace::NG::ParticleOption option;
        ParseParticleOptions(particlesValue[i], option);
        arrayValue.emplace_back(option);
    }
    ParticleModel::GetInstance()->Create(arrayValue);
}

VectorNativeDisturbanceFieldOptionsHandle FFICJCreateVectorNativeDisturbanceFieldOptions(int64_t size)
{
    LOGI("Create NativeDisturbanceFieldOptions Vector");
    return new std::vector<NativeDisturbanceFieldOptions>(size);
}

void FFICJVectorNativeDisturbanceFieldOptionsSetElement(VectorNativeDisturbanceFieldOptionsHandle vec,
    int64_t index, NativeDisturbanceFieldOptions options)
{
    LOGI("NativeDisturbanceFieldOptions Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<NativeDisturbanceFieldOptions>*>(vec);
    (*actualVec)[index] = options;
    LOGI("NativeDisturbanceFieldOptions Vector Set Element Success");
}

void FFICJVectorNativeDisturbanceFieldOptionsDelete(VectorNativeDisturbanceFieldOptionsHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeDisturbanceFieldOptions>*>(vec);
    delete actualVec;
}

void FfiOHOSAceFrameworkDataPanelSetDisturbanceFields(VectorNativeDisturbanceFieldOptionsHandle value)
{
    auto nativeDisturbanceFieldOptionsVec = *reinterpret_cast<std::vector<NativeDisturbanceFieldOptions>*>(value);
    std::vector<ParticleDisturbance> dataArray;
    for (size_t i = 0; i < nativeDisturbanceFieldOptionsVec.size(); ++i) {
        ParticleDisturbance tmp;
        tmp.strength = nativeDisturbanceFieldOptionsVec[i].strength;
        tmp.shape = static_cast<ParticleDisturbanceShapeType>(nativeDisturbanceFieldOptionsVec[i].shape);
        tmp.size[0] = nativeDisturbanceFieldOptionsVec[i].size_width;
        tmp.size[1] = nativeDisturbanceFieldOptionsVec[i].size_height;
        tmp.position[0] = nativeDisturbanceFieldOptionsVec[i].position_x;
        tmp.position[1] = nativeDisturbanceFieldOptionsVec[i].position_y;
        tmp.feather = nativeDisturbanceFieldOptionsVec[i].feather;
        tmp.noiseScale = nativeDisturbanceFieldOptionsVec[i].noiseScale;
        tmp.noiseFrequency = nativeDisturbanceFieldOptionsVec[i].noiseFrequency;
        tmp.noiseAmplitude = nativeDisturbanceFieldOptionsVec[i].noiseAmplitude;
        dataArray.push_back(tmp);
    }
    ParticleModel::GetInstance()->DisturbanceField(dataArray);
}

VectorNativeEmitterPropertyHandle FFICJCreateVectorNativeEmitterProperty(int64_t size)
{
    LOGI("Create NativeEmitterProperty Vector");
    return new std::vector<NativeEmitterProperty>(size);
}

void FFICJVectorNativeEmitterPropertySetElement(VectorNativeEmitterPropertyHandle vec,
    int64_t index, NativeEmitterProperty value)
{
    LOGI("NativeEmitterProperty Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<NativeEmitterProperty>*>(vec);
    (*actualVec)[index] = value;
    LOGI("NativeEmitterProperty Vector Set Element Success");
}

void FFICJVectorNativeEmitterPropertyDelete(VectorNativeEmitterPropertyHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeEmitterProperty>*>(vec);
    delete actualVec;
}

void FfiOHOSAceFrameworkSetEmitterProperties(VectorNativeEmitterPropertyHandle value)
{
    auto nativeEmitterPropertiesVec = *reinterpret_cast<std::vector<NativeEmitterProperty>*>(value);
    std::vector<EmitterProperty> dataArray;
    for (size_t i = 0; i < nativeEmitterPropertiesVec.size(); ++i) {
        EmitterProperty tmp;
        tmp.index = nativeEmitterPropertiesVec[i].index;
        if (nativeEmitterPropertiesVec[i].is_mitRate_set) {
            tmp.emitRate = nativeEmitterPropertiesVec[i].emitRate;
        } else {
            tmp.emitRate.reset();
        }
        if (nativeEmitterPropertiesVec[i].is_position_set) {
            tmp.position->x = nativeEmitterPropertiesVec[i].position_x;
            tmp.position->y = nativeEmitterPropertiesVec[i].position_y;
        } else {
            tmp.position.reset();
        }
        if (nativeEmitterPropertiesVec[i].is_size_set) {
            tmp.size->x = nativeEmitterPropertiesVec[i].size_width;
            tmp.size->y = nativeEmitterPropertiesVec[i].size_height;
        } else {
            tmp.size.reset();
        }

        dataArray.push_back(tmp);
    }
    ParticleModel::GetInstance()->updateEmitter(dataArray);
}
}
