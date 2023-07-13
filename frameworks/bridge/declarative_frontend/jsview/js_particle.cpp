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
#include "bridge/declarative_frontend/jsview/js_particle.h"

#include <array>
#include <utility>

#include "core/components_ng/pattern/particle/particle_model_ng.h"
#include "core/components_ng/property/particle_property.h"
#include "core/components_ng/property/particle_property_animation.h"
namespace OHOS::Ace {
std::unique_ptr<ParticleModel> ParticleModel::instance_ = nullptr;
std::mutex ParticleModel::mutex_;
ParticleModel* ParticleModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ParticleModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ParticleModelNG());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t ARRAY_SIZE = 2;
constexpr int32_t PARTICLE_DEFAULT_EMITTER_RATE = 5;
void ParsSize(std::pair<Dimension, Dimension>& size, JSRef<JSVal>& sizeJsValue)
{
    if (sizeJsValue->IsArray()) {
        auto sizeJsArray = JSRef<JSArray>::Cast(sizeJsValue);
        if (static_cast<int32_t>(sizeJsArray->Length()) == ARRAY_SIZE) {
            CalcDimension xValue;
            CalcDimension yValue;
            if (JSParticle::ParseJsDimensionVp(sizeJsArray->GetValueAt(0), xValue)) {
                size.first = xValue;
            }
            if (JSParticle::ParseJsDimensionVp(sizeJsArray->GetValueAt(1), yValue)) {
                size.second = yValue;
            }
        }
    }
}

template<class T>
std::optional<std::pair<T, T>> ParseParticleRange(JSRef<JSVal>& jsValue)
{
    std::optional<std::pair<T, T>> rangeOpt;
    if (!jsValue->IsArray()) {
        return rangeOpt;
    }
    auto jsArray = JSRef<JSArray>::Cast(jsValue);
    if (jsArray->Length() == ARRAY_SIZE && jsArray->GetValueAt(0)->IsNumber() && jsArray->GetValueAt(1)->IsNumber()) {
        auto from = jsArray->GetValueAt(0)->ToNumber<T>();
        auto to = jsArray->GetValueAt(1)->ToNumber<T>();
        if (from <= to) {
            rangeOpt = std::pair<T, T>(from, to);
        }
    }
    return rangeOpt;
}

RefPtr<Curve> ParseCurve(JSRef<JSVal>& curveJsValue)
{
    RefPtr<Curve> curve;
    if (curveJsValue->IsString()) {
        std::string src;
        if (JSParticle::ParseJsString(curveJsValue, src)) {
            curve = CreateCurve(src);
        }
    }
    if (!curve) {
        curve = AceType::MakeRefPtr<LinearCurve>();
    }
    return curve;
}

void ParseAnimationFloatArray(
    JSRef<JSArray>& curveConfigJsArray, std::list<NG::ParticlePropertyAnimation<float>>& particleAnimationFloatArray)
{
    auto arraySize = static_cast<int32_t>(curveConfigJsArray->Length());
    for (int i = 0; i < arraySize; i++) {
        auto arrayItemJsValue = curveConfigJsArray->GetValueAt(i);
        NG::ParticlePropertyAnimation<float> floatPropertyAnimation;
        if (!arrayItemJsValue->IsObject()) {
            continue;
        }
        auto arrayItemJsObject = JSRef<JSObject>::Cast(arrayItemJsValue);
        auto fromJsValue = arrayItemJsObject->GetProperty("from");
        float from;
        if (fromJsValue->IsNumber() && OHOS::Ace::GreatOrEqual(fromJsValue->ToNumber<float>(), 0.0f)) {
            from = fromJsValue->ToNumber<float>();
            continue;
        }
        floatPropertyAnimation.SetFrom(from);
        auto toJsValue = arrayItemJsObject->GetProperty("to");
        float to;
        if (toJsValue->IsNumber() && OHOS::Ace::GreatNotEqual(toJsValue->ToNumber<float>(), 0.0f)) {
            to = toJsValue->ToNumber<float>();
            continue;
        }
        floatPropertyAnimation.SetTo(to);
        auto startMillisJsValue = arrayItemJsObject->GetProperty("startMillis");
        auto startMillis = static_cast<int32_t>(0);
        if (!JSParticle::ParseJsInt32(startMillisJsValue, startMillis) || startMillis < 0) {
            continue;
        }
        floatPropertyAnimation.SetStartMills(startMillis);
        auto endMillisJsValue = arrayItemJsObject->GetProperty("endMillis");
        auto endMillis = static_cast<int32_t>(0);
        if (!JSParticle::ParseJsInt32(endMillisJsValue, endMillis) || endMillis < 0) {
            continue;
        }
        floatPropertyAnimation.SetEndMills(endMillis);
        auto curveJsValue = arrayItemJsObject->GetProperty("curve");
        auto curve = ParseCurve(curveJsValue);
        if (curve) {
            floatPropertyAnimation.SetCurve(curve);
        }
        particleAnimationFloatArray.emplace_back(floatPropertyAnimation);
    }
}

bool ParseFloatUpdater(JSRef<JSObject>& updaterJsObject, OHOS::Ace::NG::ParticleFloatPropertyUpdater& updater)
{
    auto typeJsValue = updaterJsObject->GetProperty("type");
    if (typeJsValue->IsNumber()) {
        auto typeIntValue = typeJsValue->ToNumber<int32_t>();
        if (typeIntValue < NG::UpdaterType::NONE_UPDATER || typeIntValue > NG::UpdaterType::CURVE) {
            return false;
        }
        auto type = static_cast<NG::UpdaterType>(typeIntValue);
        updater.SetUpdaterType(type);
        auto configJsValue = updaterJsObject->GetProperty("config");
        if (type == NG::UpdaterType::RANDOM) {
            if (!configJsValue->IsArray()) {
                return false;
            }
            auto randomConfigJsArray = JSRef<JSArray>::Cast(configJsValue);
            auto randomArraySize = static_cast<int32_t>(randomConfigJsArray->Length());
            if (randomArraySize != ARRAY_SIZE) {
                return false;
            }
            auto randomRangePair = ParseParticleRange<float>(configJsValue);
            if (!randomRangePair.has_value() || GreatNotEqual(randomRangePair->first, randomRangePair->second)) {
                return false;
            }
            NG::ParticleFloatPropertyUpdaterConfig randomUpdaterConfig;
            randomUpdaterConfig.SetRandomConfig(randomRangePair.value());
            updater.SetConfig(randomUpdaterConfig);
        } else if (type == NG::UpdaterType::CURVE) {
            if (!configJsValue->IsArray()) {
                return false;
            }
            auto curveConfigJsArray = JSRef<JSArray>::Cast(configJsValue);
            std::list<NG::ParticlePropertyAnimation<float>> particleAnimationFloatArray;
            ParseAnimationFloatArray(curveConfigJsArray, particleAnimationFloatArray);
            NG::ParticleFloatPropertyUpdaterConfig updateConfig;
            updateConfig.SetAnimations(particleAnimationFloatArray);
            updater.SetConfig(updateConfig);
        }
    }
    return true;
}

bool ParseFloatOption(JSRef<JSObject>& floatJsObject, OHOS::Ace::NG::ParticleFloatPropertyOption& floatOption)
{
    auto floatRangeJsValue = floatJsObject->GetProperty("range");
    if (!floatRangeJsValue->IsArray()) {
        return false;
    }
    auto floatRangeJsArray = JSRef<JSArray>::Cast(floatRangeJsValue);
    if (floatRangeJsArray->Length() != ARRAY_SIZE) {
        return false;
    }
    auto fromJsValue = floatRangeJsArray->GetValueAt(0);
    if (!fromJsValue->IsNumber()) {
        return false;
    }
    auto from = fromJsValue->ToNumber<float>();
    auto toJsValue = floatRangeJsArray->GetValueAt(1);
    if (!toJsValue->IsNumber()) {
        return false;
    }
    auto to = toJsValue->ToNumber<float>();
    if (OHOS::Ace::LessOrEqual(from, 0.0f) || OHOS::Ace::LessNotEqual(to, 0.0f) || GreatOrEqual(from, to)) {
        return false;
    }
    auto range = std::pair<float, float>(from, to);
    floatOption.SetRange(range);
    auto updaterJsValue = floatJsObject->GetProperty("updater");
    if (updaterJsValue->IsObject()) {
        auto updaterJsObject = JSRef<JSObject>::Cast(updaterJsValue);
        NG::ParticleFloatPropertyUpdater updater;
        ParseFloatUpdater(updaterJsObject, updater);
        floatOption.SetUpdater(updater);
    }
    return true;
}

bool ParseParticleObject(JSRef<JSObject>& particleJsObject, OHOS::Ace::NG::Particle& particle)
{
    auto typeJsValue = particleJsObject->GetProperty("type");
    auto typeValue = NG::ParticleType::POINT;
    if (typeJsValue->IsNumber()) {
        auto typeIntValue = typeJsValue->ToNumber<int32_t>();
        if (typeIntValue >= static_cast<int32_t>(NG::ParticleType::POINT) &&
            typeIntValue <= static_cast<int32_t>(NG::ParticleType::IMAGE)) {
            typeValue = static_cast<NG::ParticleType>(typeIntValue);
        }
    }
    particle.SetParticleType(typeValue);

    auto configJsValue = particleJsObject->GetProperty("config");
    if (!configJsValue->IsObject()) {
        return false;
    }
    auto configJsObject = JSRef<JSObject>::Cast(configJsValue);
    if (typeValue == NG::ParticleType::IMAGE) {
        auto srcJsValue = configJsObject->GetProperty("src");
        auto sizeJsValue = configJsObject->GetProperty("size");
        auto objectFitJsValue = configJsObject->GetProperty("objectFit");
        NG::ImageParticleParameter imageParameter;
        std::string src;
        if (!JSParticle::ParseJsMedia(srcJsValue, src)) {
            return false;
        }
        imageParameter.SetImageSource(src);
        auto width = Dimension(0.0);
        auto height = Dimension(0.0);
        auto sizeValue = std::pair<Dimension, Dimension>(width, height);
        ParsSize(sizeValue, sizeJsValue);
        imageParameter.SetSize(sizeValue);
        auto fit = ImageFit::COVER;
        if (objectFitJsValue->IsNumber()) {
            auto fitIntValue = objectFitJsValue->ToNumber<int32_t>();
            if (fitIntValue >= static_cast<int32_t>(ImageFit::SCALE_DOWN) &&
                fitIntValue <= static_cast<int32_t>(ImageFit::FILL)) {
                fit = static_cast<ImageFit>(fitIntValue);
            }
        }
        imageParameter.SetImageFit(fit);
        NG::ParticleConfig particleConfig;
        particleConfig.SetImageParticleParameter(imageParameter);
        particle.SetConfig(particleConfig);
    } else {
        auto radiusJsValue = configJsObject->GetProperty("radius");
        CalcDimension radius;
        JSParticle::ParseJsDimensionVp(radiusJsValue, radius);
        NG::PointParticleParameter pointParameter;
        pointParameter.SetRadius(radius.ConvertToPx());
        NG::ParticleConfig particleConfig;
        particleConfig.SetPointParticleParameter(pointParameter);
        particle.SetConfig(particleConfig);
    }

    auto count = 0;
    auto countJsValue = particleJsObject->GetProperty("count");
    if (countJsValue->IsNumber()) {
        auto countIntValue = countJsValue->ToNumber<int32_t>();
        if (countIntValue >= 0) {
            count = countIntValue;
        }
    }
    particle.SetCount(count);

    auto lifeTime = 1000;
    auto lifeTimeJsValue = particleJsObject->GetProperty("lifetime");
    if (lifeTimeJsValue->IsNumber()) {
        auto lifeTimeIntValue = lifeTimeJsValue->ToNumber<int64_t>();
        if (lifeTimeIntValue >= 0) {
            lifeTime = lifeTimeIntValue;
        }
    }
    particle.SetLifeTime(lifeTime);
    return true;
}

bool ParseEmitterOption(JSRef<JSObject>& emitterJsObject, OHOS::Ace::NG::EmitterOption& emitterOption)
{
    auto particleJsValue = emitterJsObject->GetProperty("particle");
    if (!particleJsValue->IsObject()) {
        return false;
    }
    auto particleJsObject = JSRef<JSObject>::Cast(particleJsValue);
    OHOS::Ace::NG::Particle particle;
    if (!ParseParticleObject(particleJsObject, particle)) {
        return false;
    }
    emitterOption.SetParticle(particle);
    int32_t emitRate = PARTICLE_DEFAULT_EMITTER_RATE;
    auto emitRateJsValue = emitterJsObject->GetProperty("emitRate");
    if (emitRateJsValue->IsNumber()) {
        emitRate = emitRateJsValue->ToNumber<int32_t>() >= 0 ? emitRateJsValue->ToNumber<int32_t>() : emitRate;
    }
    emitterOption.SetEmitterRate(emitRate);

    auto emitShape = OHOS::Ace::NG::ParticleEmitterShape::RECTANGLE;
    auto emitShapeJsValue = emitterJsObject->GetProperty("shape");
    if (emitShapeJsValue->IsNumber()) {
        auto emitShapeInt = emitShapeJsValue->ToNumber<int32_t>();
        if (emitShapeInt >= static_cast<int32_t>(OHOS::Ace::NG::ParticleEmitterShape::RECTANGLE) &&
            emitShapeInt <= static_cast<int32_t>(OHOS::Ace::NG::ParticleEmitterShape::ELLIPSE)) {
            emitShape = static_cast<OHOS::Ace::NG::ParticleEmitterShape>(emitShapeInt);
        }
    }
    emitterOption.SetShape(emitShape);
    auto positionX = 0.0f;
    auto positionY = 0.0f;
    auto positionJsValue = emitterJsObject->GetProperty("position");
    if (positionJsValue->IsArray()) {
        auto positionJsArray = JSRef<JSArray>::Cast(positionJsValue);
        if (positionJsArray->Length() == ARRAY_SIZE && positionJsArray->GetValueAt(0)->IsNumber() &&
            positionJsArray->GetValueAt(1)->IsNumber()) {
            auto positionXValue = positionJsArray->GetValueAt(0)->ToNumber<float>();
            auto positionYValue = positionJsArray->GetValueAt(1)->ToNumber<float>();
            if (GreatOrEqual(positionXValue, 0.0f)) {
                positionX = positionXValue;
            }
            if (GreatOrEqual(positionYValue, 0.0f)) {
                positionY = positionYValue;
            }
        }
    }
    auto positionValue = std::pair<Dimension, Dimension>(
        Dimension(positionX, DimensionUnit::VP), Dimension(positionY, DimensionUnit::VP));
    emitterOption.SetPosition(positionValue);

    auto width = Dimension(1.0, DimensionUnit::PERCENT);
    auto height = Dimension(1.0, DimensionUnit::PERCENT);
    auto sizeValue = std::pair<Dimension, Dimension>(width, height);
    auto sizeJsValue = emitterJsObject->GetProperty("size");
    ParsSize(sizeValue, sizeJsValue);
    emitterOption.SetSize(sizeValue);
    return true;
}

void ParseAnimationColorArray(
    JSRef<JSArray>& curveConfigJsArray, std::list<NG::ParticlePropertyAnimation<Color>>& particleAnimationColorArray)
{
    auto arraySize = static_cast<int32_t>(curveConfigJsArray->Length());
    for (int i = 0; i < arraySize; i++) {
        auto arrayItemJsValue = curveConfigJsArray->GetValueAt(i);
        NG::ParticlePropertyAnimation<Color> colorPropertyAnimation;
        if (!arrayItemJsValue->IsObject()) {
            continue;
        }
        auto arrayItemJsObject = JSRef<JSObject>::Cast(arrayItemJsValue);
        auto fromJsValue = arrayItemJsObject->GetProperty("from");
        Color from;
        if (!JSParticle::ParseJsColor(fromJsValue, from)) {
            continue;
        }
        colorPropertyAnimation.SetFrom(from);
        auto toJsValue = arrayItemJsObject->GetProperty("to");
        Color to;
        if (!JSParticle::ParseJsColor(toJsValue, to)) {
            continue;
        }
        colorPropertyAnimation.SetTo(to);
        auto startMillisJsValue = arrayItemJsObject->GetProperty("startMillis");
        auto startMillis = static_cast<int32_t>(0);
        if (!JSParticle::ParseJsInt32(startMillisJsValue, startMillis) || startMillis < 0) {
            continue;
        }
        colorPropertyAnimation.SetStartMills(startMillis);
        auto endMillisJsValue = arrayItemJsObject->GetProperty("endMillis");
        auto endMillis = static_cast<int32_t>(0);
        if (!JSParticle::ParseJsInt32(endMillisJsValue, endMillis) || endMillis < 0) {
            continue;
        }
        colorPropertyAnimation.SetEndMills(endMillis);
        auto curveJsValue = arrayItemJsObject->GetProperty("curve");
        auto curve = ParseCurve(curveJsValue);
        if (curve) {
            colorPropertyAnimation.SetCurve(curve);
        }
        particleAnimationColorArray.emplace_back(colorPropertyAnimation);
    }
}

bool ParseColorUpdater(JSRef<JSObject>& updaterJsObject, OHOS::Ace::NG::ParticleColorPropertyUpdater& updater)
{
    auto typeJsValue = updaterJsObject->GetProperty("type");
    if (typeJsValue->IsNumber()) {
        auto typeIntValue = typeJsValue->ToNumber<int32_t>();
        if (typeIntValue < NG::UpdaterType::NONE_UPDATER || typeIntValue > NG::UpdaterType::CURVE) {
            return false;
        }
        auto type = static_cast<NG::UpdaterType>(typeIntValue);
        updater.SetUpdateType(type);
        auto configJsValue = updaterJsObject->GetProperty("config");
        if (type == NG::UpdaterType::RANDOM) {
            if (!configJsValue->IsObject()) {
                return false;
            }
            auto randomConfigJsObject = JSRef<JSObject>::Cast(configJsValue);
            auto rJsValue = randomConfigJsObject->GetProperty("r");
            auto gJsValue = randomConfigJsObject->GetProperty("g");
            auto bJsValue = randomConfigJsObject->GetProperty("b");
            auto aJsValue = randomConfigJsObject->GetProperty("a");
            auto rRangeValue = ParseParticleRange<float>(rJsValue);
            auto gRangeValue = ParseParticleRange<float>(gJsValue);
            auto bRangeValue = ParseParticleRange<float>(bJsValue);
            auto aRangeValue = ParseParticleRange<float>(aJsValue);
            if (!rRangeValue.has_value() || !gRangeValue.has_value() || !bRangeValue.has_value() ||
                !aRangeValue.has_value()) {
                return false;
            }
            NG::ColorParticleRandomUpdateConfig colorRandomConfig;
            colorRandomConfig.SetRedRandom(rRangeValue.value());
            colorRandomConfig.SetGreenRandom(gRangeValue.value());
            colorRandomConfig.SetBlueRandom(bRangeValue.value());
            colorRandomConfig.SetAlphaRandom(aRangeValue.value());
            NG::ParticleColorPropertyUpdaterConfig randomUpdaterConfig;
            randomUpdaterConfig.SetRandomConfig(colorRandomConfig);
            updater.SetConfig(randomUpdaterConfig);
        } else if (type == NG::UpdaterType::CURVE) {
            if (!configJsValue->IsArray()) {
                return false;
            }
            auto curveConfigJsArray = JSRef<JSArray>::Cast(configJsValue);
            std::list<NG::ParticlePropertyAnimation<Color>> particleAnimationColorArray;
            ParseAnimationColorArray(curveConfigJsArray, particleAnimationColorArray);
            NG::ParticleColorPropertyUpdaterConfig randomUpdaterConfig;
            randomUpdaterConfig.SetAnimationArray(particleAnimationColorArray);
            updater.SetConfig(randomUpdaterConfig);
        }
    }
    return true;
}

bool ParseColorOption(JSRef<JSObject>& colorJsObject, OHOS::Ace::NG::ParticleColorPropertyOption& colorOption)
{
    auto colorRangeJsValue = colorJsObject->GetProperty("range");
    if (!colorRangeJsValue->IsArray()) {
        return false;
    }
    auto colorRangeJsArray = JSRef<JSArray>::Cast(colorRangeJsValue);
    if (static_cast<int32_t>(colorRangeJsArray->Length()) != ARRAY_SIZE) {
        return false;
    }
    Color fromColor;
    if (!JSParticle::ParseJsColor(colorRangeJsArray->GetValueAt(0), fromColor)) {
        return false;
    }
    Color toColor;
    if (!JSParticle::ParseJsColor(colorRangeJsArray->GetValueAt(1), toColor)) {
        return false;
    }
    auto range = std::pair<Color, Color>(fromColor, toColor);
    colorOption.SetRange(range);
    auto updaterJsValue = colorJsObject->GetProperty("updater");
    if (updaterJsValue->IsObject()) {
        auto updaterJsObject = JSRef<JSObject>::Cast(updaterJsValue);
        NG::ParticleColorPropertyUpdater updater;
        ParseColorUpdater(updaterJsObject, updater);
        colorOption.SetUpdater(updater);
    }
    return true;
}

bool ParseParticleVelocity(JSRef<JSVal> jsValue, OHOS::Ace::NG::VelocityProperty& velocity)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    auto jsValueObj = JSRef<JSObject>::Cast(jsValue);
    auto speedJsValue = jsValueObj->GetProperty("speed");
    auto angleJsValue = jsValueObj->GetProperty("angle");
    if (!speedJsValue->IsArray() || angleJsValue->IsArray()) {
        return false;
    }
    auto speedPair = ParseParticleRange<float>(speedJsValue);
    if (speedPair.has_value()) {
        velocity.SetSpeedRange(speedPair.value());
    }
    auto anglePair = ParseParticleRange<float>(angleJsValue);
    if (anglePair.has_value()) {
        velocity.SetAngleRange(anglePair.value());
    }
    return true;
}

void ParseParticleAcceleration(JSRef<JSVal> jsValue, OHOS::Ace::NG::AccelerationProperty& acceleration)
{
    if (!jsValue->IsObject()) {
        return;
    }
    auto jsValueObj = JSRef<JSObject>::Cast(jsValue);
    auto speedValue = jsValueObj->GetProperty("speed");
    auto alphaValue = jsValueObj->GetProperty("angle");
    OHOS::Ace::NG::ParticleFloatPropertyOption speedOption;
    if (speedValue->IsObject()) {
        auto speedObject = JSRef<JSObject>::Cast(speedValue);
        if (ParseFloatOption(speedObject, speedOption)) {
            acceleration.SetSpeed(speedOption);
        }
    }

    OHOS::Ace::NG::ParticleFloatPropertyOption angleOption;
    if (alphaValue->IsObject()) {
        auto alphaObject = JSRef<JSObject>::Cast(alphaValue);
        if (ParseFloatOption(alphaObject, angleOption)) {
            acceleration.SetAngle(angleOption);
        }
    }
}

bool ParseParticleOption(JSRef<JSObject>& particleJsObj, OHOS::Ace::NG::ParticleOption& particleOption)
{
    auto emitterJsValue = particleJsObj->GetProperty("emitter");
    if (!emitterJsValue->IsObject()) {
        return false;
    }
    auto emitterJsObj = JSRef<JSObject>::Cast(emitterJsValue);
    OHOS::Ace::NG::EmitterOption emitterOption;
    if (!ParseEmitterOption(emitterJsObj, emitterOption)) {
        return false;
    }
    particleOption.SetEmitterOption(emitterOption);
    auto colorJsValue = particleJsObj->GetProperty("color");
    if (colorJsValue->IsObject()) {
        auto colorJsObj = JSRef<JSObject>::Cast(colorJsValue);
        OHOS::Ace::NG::ParticleColorPropertyOption colorOption;
        if (ParseColorOption(colorJsObj, colorOption)) {
            particleOption.SetParticleColorOption(colorOption);
        }
    }
    auto opacityJsValue = particleJsObj->GetProperty("opacity");
    if (opacityJsValue->IsObject()) {
        auto opacityJsObj = JSRef<JSObject>::Cast(opacityJsValue);
        OHOS::Ace::NG::ParticleFloatPropertyOption opacityOption;
        if (ParseFloatOption(opacityJsObj, opacityOption)) {
            particleOption.SetParticleOpacityOption(opacityOption);
        }
    }

    auto scaleJsValue = particleJsObj->GetProperty("scale");
    if (scaleJsValue->IsObject()) {
        auto scaleJsObj = JSRef<JSObject>::Cast(scaleJsValue);
        OHOS::Ace::NG::ParticleFloatPropertyOption scaleOption;
        if (ParseFloatOption(scaleJsObj, scaleOption)) {
            particleOption.SetParticleScaleOption(scaleOption);
        }
    }

    auto velocityJsValue = particleJsObj->GetProperty("velocity");
    OHOS::Ace::NG::VelocityProperty velocity;
    if (ParseParticleVelocity(velocityJsValue, velocity)) {
        particleOption.SetParticleVelocityOption(velocity);
    }

    auto accelerationJsValue = particleJsObj->GetProperty("acceleration");
    OHOS::Ace::NG::AccelerationProperty acceleration;
    ParseParticleAcceleration(accelerationJsValue, acceleration);
    particleOption.SetParticleAccelerationOption(acceleration);

    auto spinJsValue = particleJsObj->GetProperty("spin");
    if (spinJsValue->IsObject()) {
        auto spinJsObj = JSRef<JSObject>::Cast(spinJsValue);
        OHOS::Ace::NG::ParticleFloatPropertyOption spinOption;
        if (ParseFloatOption(spinJsObj, spinOption)) {
            particleOption.SetParticleSpinOption(spinOption);
        }
    }
    return true;
}

void ParseParticleArray(JSRef<JSArray>& paramArray, std::list<OHOS::Ace::NG::ParticleOption>& arrayValue)
{
    for (size_t i = 0; i < paramArray->Length(); i++) {
        if (!paramArray->GetValueAt(i)->IsObject()) {
            continue;
        }
        OHOS::Ace::NG::ParticleOption option;
        auto particleJsObj = JSRef<JSObject>::Cast(paramArray->GetValueAt(i));
        if (!ParseParticleOption(particleJsObj, option)) {
            continue;
        }
        arrayValue.emplace_back(option);
    }
}
} // namespace
void JSParticle::Create(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    std::list<OHOS::Ace::NG::ParticleOption> arrayValue;
    if (args[0]->IsObject()) {
        JSRef<JSObject> paramObj = JSRef<JSObject>::Cast(args[0]);
        auto particlesJsArray = paramObj->GetProperty("particles");
        if (particlesJsArray->IsArray()) {
            auto paramArray = JSRef<JSArray>::Cast(particlesJsArray);
            ParseParticleArray(paramArray, arrayValue);
        }
    }
    ParticleModel::GetInstance()->Create(arrayValue);
}

void JSParticle::JSBind(BindingTarget globalObj)
{
    JSClass<JSParticle>::Declare("Particle");
    JSClass<JSParticle>::StaticMethod("create", &JSParticle::Create);
    JSClass<JSParticle>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
