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
constexpr float MIN_BOUNDARY = -100.0f;
constexpr float MIN_LIMIT = -10000.0f;
constexpr float MAX_BOUNDARY = 100.0f;
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

constexpr int DEFAULT_COLOR = 0xffffffff;

void ParsSize(std::pair<Dimension, Dimension>& size, JSRef<JSVal>& sizeJsValue)
{
    if (sizeJsValue->IsArray()) {
        auto sizeJsArray = JSRef<JSArray>::Cast(sizeJsValue);
        if (static_cast<int32_t>(sizeJsArray->Length()) == ARRAY_SIZE) {
            CalcDimension xValue;
            CalcDimension yValue;
            if (JSParticle::ParseJsDimensionVp(sizeJsArray->GetValueAt(0), xValue) &&
                GreatOrEqual(xValue.Value(), 0.0)) {
                size.first = xValue;
            }
            if (JSParticle::ParseJsDimensionVp(sizeJsArray->GetValueAt(1), yValue) &&
                GreatOrEqual(yValue.Value(), 0.0)) {
                size.second = yValue;
            }
        }
    }
}

std::optional<std::pair<float, float>> ParseParticleRange(JSRef<JSVal>& jsValue, float defaultValue)
{
    std::optional<std::pair<float, float>> rangeOpt;
    auto defaultPair = std::pair<float, float>(defaultValue, defaultValue);
    if (!jsValue->IsArray()) {
        rangeOpt = defaultPair;
        return rangeOpt;
    }
    auto jsArray = JSRef<JSArray>::Cast(jsValue);
    if (jsArray->Length() != ARRAY_SIZE) {
        rangeOpt = defaultPair;
        return rangeOpt;
    }
    auto from = defaultValue;
    if (jsArray->GetValueAt(0)->IsNumber()) {
        from = jsArray->GetValueAt(0)->ToNumber<float>();
    }
    auto to = defaultValue;
    if (jsArray->GetValueAt(1)->IsNumber()) {
        to = jsArray->GetValueAt(1)->ToNumber<float>();
    }
    if (GreatNotEqual(from, to)) {
        rangeOpt = defaultPair;
        return rangeOpt;
    }
    rangeOpt = std::pair<float, float>(from, to);
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

void ParseAnimationFloatArray(JSRef<JSArray>& curveConfigJsArray,
    std::list<NG::ParticlePropertyAnimation<float>>& particleAnimationFloatArray, float defaultValue, float minValue,
    float maxValue)
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
        float from = defaultValue;
        if (fromJsValue->IsNumber()) {
            from = fromJsValue->ToNumber<float>();
            if (GreatNotEqual(minValue, MIN_BOUNDARY) && LessNotEqual(from, minValue)) {
                from = defaultValue;
            }
            if (LessNotEqual(maxValue, MAX_BOUNDARY) && GreatNotEqual(from, maxValue)) {
                from = defaultValue;
            }
        }
        floatPropertyAnimation.SetFrom(from);
        auto toJsValue = arrayItemJsObject->GetProperty("to");
        float to = defaultValue;
        if (toJsValue->IsNumber()) {
            to = toJsValue->ToNumber<float>();
            if (GreatNotEqual(minValue, MIN_BOUNDARY) && LessNotEqual(to, minValue)) {
                to = defaultValue;
            }
            if (LessNotEqual(maxValue, MAX_BOUNDARY) && GreatNotEqual(to, maxValue)) {
                to = defaultValue;
            }
        }
        floatPropertyAnimation.SetTo(to);
        auto startMillisJsValue = arrayItemJsObject->GetProperty("startMillis");
        auto startMillis = static_cast<int32_t>(0);
        if (!JSParticle::ParseJsInt32(startMillisJsValue, startMillis) || startMillis < 0) {
            startMillis = 0;
        }
        floatPropertyAnimation.SetStartMills(startMillis);
        auto endMillisJsValue = arrayItemJsObject->GetProperty("endMillis");
        auto endMillis = static_cast<int32_t>(0);
        if (!JSParticle::ParseJsInt32(endMillisJsValue, endMillis) || endMillis < 0) {
            endMillis = 0;
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

bool ParseFloatRandomConfig(JSRef<JSVal>& configJsValue, OHOS::Ace::NG::ParticleFloatPropertyUpdater& updater)
{
    if (!configJsValue->IsArray()) {
        return false;
    }
    auto randomConfigJsArray = JSRef<JSArray>::Cast(configJsValue);
    auto randomArraySize = static_cast<int32_t>(randomConfigJsArray->Length());
    if (randomArraySize != ARRAY_SIZE) {
        return false;
    }
    auto randomRangePair = ParseParticleRange(configJsValue, 0.0f);
    if (!randomRangePair.has_value()) {
        return false;
    }
    NG::ParticleFloatPropertyUpdaterConfig randomUpdaterConfig;
    randomUpdaterConfig.SetRandomConfig(randomRangePair.value());
    updater.SetConfig(randomUpdaterConfig);
    return true;
}

bool ParseFloatCurveConfig(JSRef<JSVal>& configJsValue, OHOS::Ace::NG::ParticleFloatPropertyUpdater& updater,
    float defaultValue, float minValue, float maxValue)
{
    if (!configJsValue->IsArray()) {
        return false;
    }
    auto curveConfigJsArray = JSRef<JSArray>::Cast(configJsValue);
    std::list<NG::ParticlePropertyAnimation<float>> particleAnimationFloatArray;
    ParseAnimationFloatArray(curveConfigJsArray, particleAnimationFloatArray, defaultValue, minValue, maxValue);
    NG::ParticleFloatPropertyUpdaterConfig updateConfig;
    updateConfig.SetAnimations(particleAnimationFloatArray);
    updater.SetConfig(updateConfig);
    return true;
}

bool ParseFloatUpdater(JSRef<JSObject>& updaterJsObject, OHOS::Ace::NG::ParticleFloatPropertyUpdater& updater,
    float defaultValue, float minValue, float maxValue)
{
    auto typeJsValue = updaterJsObject->GetProperty("type");
    if (typeJsValue->IsNumber()) {
        auto typeIntValue = typeJsValue->ToNumber<int32_t>();
        if (typeIntValue < NG::UpdaterType::NONE_UPDATER || typeIntValue > NG::UpdaterType::CURVE) {
            typeIntValue = NG::UpdaterType::NONE_UPDATER;
        }
        auto type = static_cast<NG::UpdaterType>(typeIntValue);
        updater.SetUpdaterType(type);
        auto configJsValue = updaterJsObject->GetProperty("config");
        if (type == NG::UpdaterType::RANDOM) {
            if (!ParseFloatRandomConfig(configJsValue, updater)) {
                auto randomRangePair = std::pair<float, float>(0.0f, 0.0f);
                NG::ParticleFloatPropertyUpdaterConfig randomUpdaterConfig;
                randomUpdaterConfig.SetRandomConfig(randomRangePair);
                updater.SetConfig(randomUpdaterConfig);
            }
            return true;
        } else if (type == NG::UpdaterType::CURVE) {
            if (!ParseFloatCurveConfig(configJsValue, updater, defaultValue, minValue, maxValue)) {
                std::list<NG::ParticlePropertyAnimation<float>> particleAnimationFloatArray;
                NG::ParticleFloatPropertyUpdaterConfig updateConfig;
                updateConfig.SetAnimations(particleAnimationFloatArray);
                updater.SetConfig(updateConfig);
            }
            return true;
        }
    }
    return false;
}

void ParseFloatInitRange(JSRef<JSVal>& floatRangeJsValue, OHOS::Ace::NG::ParticleFloatPropertyOption& floatOption,
    float defaultValue, float minValue, float maxValue)
{
    auto defaultPair = std::pair<float, float>(defaultValue, defaultValue);
    if (!floatRangeJsValue->IsArray()) {
        floatOption.SetRange(defaultPair);
        return;
    }
    auto floatRangeJsArray = JSRef<JSArray>::Cast(floatRangeJsValue);
    if (floatRangeJsArray->Length() != ARRAY_SIZE) {
        floatOption.SetRange(defaultPair);
        return;
    }
    auto from = defaultValue;
    auto fromJsValue = floatRangeJsArray->GetValueAt(0);
    if (fromJsValue->IsNumber()) {
        from = fromJsValue->ToNumber<float>();
        if (GreatNotEqual(minValue, MIN_BOUNDARY) && LessNotEqual(from, minValue)) {
            from = defaultValue;
        }
        if (LessNotEqual(maxValue, MAX_BOUNDARY) && GreatNotEqual(from, maxValue)) {
            from = defaultValue;
        }
    }
    auto to = defaultValue;
    auto toJsValue = floatRangeJsArray->GetValueAt(1);
    if (toJsValue->IsNumber()) {
        to = toJsValue->ToNumber<float>();
        if (GreatNotEqual(minValue, MIN_BOUNDARY) && LessNotEqual(to, minValue)) {
            to = defaultValue;
        }
        if (LessNotEqual(maxValue, MAX_BOUNDARY) && GreatNotEqual(to, maxValue)) {
            to = defaultValue;
        }
    }
    if (GreatNotEqual(from, to)) {
        from = defaultValue;
        to = defaultValue;
    }
    auto range = std::pair<float, float>(from, to);
    floatOption.SetRange(range);
}

void ParseFloatOption(JSRef<JSObject>& floatJsObject, OHOS::Ace::NG::ParticleFloatPropertyOption& floatOption,
    float defaultValue, float minValue, float maxValue)
{
    auto floatRangeJsValue = floatJsObject->GetProperty("range");
    ParseFloatInitRange(floatRangeJsValue, floatOption, defaultValue, minValue, maxValue);
    auto updaterJsValue = floatJsObject->GetProperty("updater");
    NG::ParticleFloatPropertyUpdater updater;
    if (updaterJsValue->IsObject()) {
        auto updaterJsObject = JSRef<JSObject>::Cast(updaterJsValue);
        if (ParseFloatUpdater(updaterJsObject, updater, defaultValue, minValue, maxValue)) {
            floatOption.SetUpdater(updater);
            return;
        }
    }
    updater.SetUpdaterType(NG::UpdaterType::NONE_UPDATER);
    NG::ParticleFloatPropertyUpdaterConfig updateConfig;
    updateConfig.SetNullStr("");
    updater.SetConfig(updateConfig);
    floatOption.SetUpdater(updater);
}

void ParseEmitterPropertyAnnulus(const JSRef<JSObject>& paramObj, EmitterProperty& emitterProperty)
{
    auto annulusRegionProperty = paramObj->GetProperty("annulusRegion");
    if (annulusRegionProperty->IsObject()) {
        auto annulusRegion = Framework::JSRef<Framework::JSObject>::Cast(annulusRegionProperty);
        auto centerProperty = annulusRegion->GetProperty("center");
        std::pair<CalcDimension, CalcDimension> center = {
            DEFAULT_CENTER_VALUE, DEFAULT_CENTER_VALUE
        };
        if (centerProperty->IsObject()) {
            auto centerJson = JSRef<JSObject>::Cast(centerProperty);
            CalcDimension centerXValue;
            CalcDimension centerYValue;
            if (JSViewAbstract::ParseLengthMetricsToDimension(centerJson->GetProperty("x"), centerXValue)) {
                center.first = centerXValue;
            }
            if (JSViewAbstract::ParseLengthMetricsToDimension(centerJson->GetProperty("y"), centerYValue)) {
                center.second = centerYValue;
            }
        }
        CalcDimension innerRadiusValue;
        CalcDimension outerRadiusValue;
        JSViewAbstract::ParseLengthMetricsToDimension(annulusRegion->GetProperty("innerRadius"), innerRadiusValue);
        JSViewAbstract::ParseLengthMetricsToDimension(annulusRegion->GetProperty("outerRadius"), outerRadiusValue);
        auto startAngle = annulusRegion->GetProperty("startAngle");
        auto startAngleValue = startAngle->IsNumber() ? startAngle->ToNumber<float>() : DEFAULT_START_ANGLE_VALUE;
        auto endAngle = annulusRegion->GetProperty("endAngle");
        auto endAngleValue = endAngle->IsNumber() ? endAngle->ToNumber<float>() : DEFAULT_END_ANGLE_VALUE;
        emitterProperty.annulusRegion = {
            center, innerRadiusValue, outerRadiusValue, startAngleValue, endAngleValue
        };
    }
}

void ParseEmitterOptionAnnulus(JSRef<JSObject>& emitterJsObject, OHOS::Ace::NG::EmitterOption& emitterOption)
{
    auto annulusRegionProperty = emitterJsObject->GetProperty("annulusRegion");
    if (annulusRegionProperty->IsObject() &&
        emitterOption.GetShape() == OHOS::Ace::NG::ParticleEmitterShape::ANNULUS) {
        auto annulusRegion = JSRef<JSObject>::Cast(annulusRegionProperty);
        auto centerProperty = annulusRegion->GetProperty("center");
        std::pair<CalcDimension, CalcDimension> center = {
            DEFAULT_CENTER_VALUE, DEFAULT_CENTER_VALUE
            };
        if (centerProperty->IsObject()) {
            auto centerJson = JSRef<JSObject>::Cast(centerProperty);
            CalcDimension centerXValue;
            CalcDimension centerYValue;
            if (JSViewAbstract::ParseLengthMetricsToDimension(centerJson->GetProperty("x"), centerXValue)) {
                center.first = centerXValue;
            }
            if (JSViewAbstract::ParseLengthMetricsToDimension(centerJson->GetProperty("y"), centerYValue)) {
                center.second = centerYValue;
            }
        }
        CalcDimension innerRadiusValue;
        CalcDimension outerRadiusValue;
        JSViewAbstract::ParseLengthMetricsToDimension(annulusRegion->GetProperty("innerRadius"), innerRadiusValue);
        JSViewAbstract::ParseLengthMetricsToDimension(annulusRegion->GetProperty("outerRadius"), outerRadiusValue);
        auto startAngle = annulusRegion->GetProperty("startAngle");
        auto startAngleValue = startAngle->IsNumber() ? startAngle->ToNumber<float>() : DEFAULT_START_ANGLE_VALUE;
        auto endAngle = annulusRegion->GetProperty("endAngle");
        auto endAngleValue = endAngle->IsNumber() ? endAngle->ToNumber<float>() : DEFAULT_END_ANGLE_VALUE;
        auto annulusRegionValue =
            NG::ParticleAnnulusRegion(center, innerRadiusValue, outerRadiusValue, startAngleValue, endAngleValue);
        emitterOption.SetAnnulusRegion(annulusRegionValue);
    }
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
        if (srcJsValue->IsString()) {
            src = srcJsValue->ToString();
        } else if (!JSParticle::ParseJsMedia(srcJsValue, src)) {
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
            if (fitIntValue >= static_cast<int32_t>(ImageFit::FILL) &&
                fitIntValue <= static_cast<int32_t>(ImageFit::SCALE_DOWN)) {
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
        pointParameter.SetRadius(!radius.IsNonPositive() ? radius.ConvertToPx() : 0.0f);
        NG::ParticleConfig particleConfig;
        particleConfig.SetPointParticleParameter(pointParameter);
        particle.SetConfig(particleConfig);
    }

    auto count = 0;
    auto countJsValue = particleJsObject->GetProperty("count");
    if (countJsValue->IsNumber()) {
        auto countIntValue = countJsValue->ToNumber<int32_t>();
        if (countIntValue >= -1) {
            count = countIntValue;
        }
    }
    particle.SetCount(count);

    int64_t lifeTime = 1000;
    auto lifeTimeJsValue = particleJsObject->GetProperty("lifetime");
    if (lifeTimeJsValue->IsNumber()) {
        auto lifeTimeIntValue = lifeTimeJsValue->ToNumber<int64_t>();
        if (lifeTimeIntValue >= -1) {
            lifeTime = lifeTimeIntValue;
        }
    }
    particle.SetLifeTime(lifeTime);
    int64_t lifeTimeRange = 0;
    auto lifeTimeRangeJsValue = particleJsObject->GetProperty("lifetimeRange");
    if (lifeTimeRangeJsValue->IsNumber()) {
        auto lifeTimeRangeIntValue = lifeTimeRangeJsValue->ToNumber<int64_t>();
        if (lifeTimeRangeIntValue >= 0) {
            lifeTimeRange = lifeTimeRangeIntValue;
        }
    }
    particle.SetLifeTimeRange(lifeTimeRange);
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
            emitShapeInt <= static_cast<int32_t>(OHOS::Ace::NG::ParticleEmitterShape::ANNULUS)) {
            emitShape = static_cast<OHOS::Ace::NG::ParticleEmitterShape>(emitShapeInt);
        }
    }
    emitterOption.SetShape(emitShape);
    auto positionJsValue = emitterJsObject->GetProperty("position");
    CalcDimension xValue(0.0);
    CalcDimension yValue(0.0);
    if (positionJsValue->IsArray()) {
        auto positionJsArray = JSRef<JSArray>::Cast(positionJsValue);
        if (positionJsArray->Length() == ARRAY_SIZE) {
            JSParticle::ParseJsDimensionVp(positionJsArray->GetValueAt(0), xValue);
            JSParticle::ParseJsDimensionVp(positionJsArray->GetValueAt(1), yValue);
        }
    }
    auto positionValue = std::pair<Dimension, Dimension>(xValue, yValue);
    emitterOption.SetPosition(positionValue);

    auto width = Dimension(1.0, DimensionUnit::PERCENT);
    auto height = Dimension(1.0, DimensionUnit::PERCENT);
    auto sizeValue = std::pair<Dimension, Dimension>(width, height);
    auto sizeJsValue = emitterJsObject->GetProperty("size");
    ParsSize(sizeValue, sizeJsValue);
    emitterOption.SetSize(sizeValue);
    ParseEmitterOptionAnnulus(emitterJsObject, emitterOption);
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
        Color from(DEFAULT_COLOR);
        JSParticle::ParseJsColor(fromJsValue, from);
        colorPropertyAnimation.SetFrom(from);
        auto toJsValue = arrayItemJsObject->GetProperty("to");
        Color to(DEFAULT_COLOR);
        JSParticle::ParseJsColor(toJsValue, to);
        colorPropertyAnimation.SetTo(to);
        auto startMillisJsValue = arrayItemJsObject->GetProperty("startMillis");
        auto startMillis = static_cast<int32_t>(0);
        if (!JSParticle::ParseJsInt32(startMillisJsValue, startMillis) || startMillis < 0) {
            startMillis = 0;
        }
        colorPropertyAnimation.SetStartMills(startMillis);
        auto endMillisJsValue = arrayItemJsObject->GetProperty("endMillis");
        auto endMillis = static_cast<int32_t>(0);
        if (!JSParticle::ParseJsInt32(endMillisJsValue, endMillis) || endMillis < 0) {
            endMillis = 0;
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

void ParseColorRandomUpdater(JSRef<JSVal> configJsValue, OHOS::Ace::NG::ParticleColorPropertyUpdater& updater)
{
    NG::ParticleColorPropertyUpdaterConfig randomUpdaterConfig;
    NG::ColorParticleRandomUpdateConfig colorRandomConfig;
    if (!configJsValue->IsObject()) {
        auto defaultPair = std::pair<float, float>(0.0f, 0.0f);
        colorRandomConfig.SetRedRandom(defaultPair);
        colorRandomConfig.SetGreenRandom(defaultPair);
        colorRandomConfig.SetBlueRandom(defaultPair);
        colorRandomConfig.SetAlphaRandom(defaultPair);
        randomUpdaterConfig.SetRandomConfig(colorRandomConfig);
        updater.SetConfig(randomUpdaterConfig);
        return;
    }
    auto randomConfigJsObject = JSRef<JSObject>::Cast(configJsValue);
    auto rJsValue = randomConfigJsObject->GetProperty("r");
    auto gJsValue = randomConfigJsObject->GetProperty("g");
    auto bJsValue = randomConfigJsObject->GetProperty("b");
    auto aJsValue = randomConfigJsObject->GetProperty("a");
    std::pair<float, float> defaultPair(0.0f, 0.0f);
    auto rRangeValue = ParseParticleRange(rJsValue, 0.0f);
    auto gRangeValue = ParseParticleRange(gJsValue, 0.0f);
    auto bRangeValue = ParseParticleRange(bJsValue, 0.0f);
    auto aRangeValue = ParseParticleRange(aJsValue, 0.0f);
    colorRandomConfig.SetRedRandom(rRangeValue.value_or(defaultPair));
    colorRandomConfig.SetGreenRandom(gRangeValue.value_or(defaultPair));
    colorRandomConfig.SetBlueRandom(bRangeValue.value_or(defaultPair));
    colorRandomConfig.SetAlphaRandom(aRangeValue.value_or(defaultPair));
    randomUpdaterConfig.SetRandomConfig(colorRandomConfig);
    updater.SetConfig(randomUpdaterConfig);
}

void ParseColorCurveUpdater(JSRef<JSVal> configJsValue, OHOS::Ace::NG::ParticleColorPropertyUpdater& updater)
{
    std::list<NG::ParticlePropertyAnimation<Color>> particleAnimationColorArray;
    NG::ParticleColorPropertyUpdaterConfig randomUpdaterConfig;
    if (!configJsValue->IsArray()) {
        randomUpdaterConfig.SetAnimationArray(particleAnimationColorArray);
        updater.SetConfig(randomUpdaterConfig);
        return;
    }
    auto curveConfigJsArray = JSRef<JSArray>::Cast(configJsValue);
    ParseAnimationColorArray(curveConfigJsArray, particleAnimationColorArray);
    randomUpdaterConfig.SetAnimationArray(particleAnimationColorArray);
    updater.SetConfig(randomUpdaterConfig);
}

bool ParseColorUpdater(JSRef<JSObject>& updaterJsObject, OHOS::Ace::NG::ParticleColorPropertyUpdater& updater)
{
    auto typeJsValue = updaterJsObject->GetProperty("type");
    if (typeJsValue->IsNumber()) {
        auto typeIntValue = typeJsValue->ToNumber<int32_t>();
        if (typeIntValue < NG::UpdaterType::NONE_UPDATER || typeIntValue > NG::UpdaterType::CURVE) {
            typeIntValue = NG::UpdaterType::NONE_UPDATER;
        }
        auto type = static_cast<NG::UpdaterType>(typeIntValue);
        updater.SetUpdateType(type);
        auto configJsValue = updaterJsObject->GetProperty("config");
        if (type == NG::UpdaterType::RANDOM) {
            ParseColorRandomUpdater(configJsValue, updater);
            return true;
        } else if (type == NG::UpdaterType::CURVE) {
            ParseColorCurveUpdater(configJsValue, updater);
            return true;
        }
    }
    return false;
}

void ParseColorInitRange(JSRef<JSVal> colorRangeJsValue, OHOS::Ace::NG::ParticleColorPropertyOption& colorOption)
{
    Color fromColor(DEFAULT_COLOR);
    Color toColor(DEFAULT_COLOR);
    auto defaultRange = std::pair<Color, Color>(fromColor, toColor);
    if (!colorRangeJsValue->IsArray()) {
        colorOption.SetRange(defaultRange);
        return;
    }
    auto colorRangeJsArray = JSRef<JSArray>::Cast(colorRangeJsValue);
    if (static_cast<int32_t>(colorRangeJsArray->Length()) != ARRAY_SIZE) {
        colorOption.SetRange(defaultRange);
        return;
    }
    JSParticle::ParseJsColor(colorRangeJsArray->GetValueAt(0), fromColor);
    JSParticle::ParseJsColor(colorRangeJsArray->GetValueAt(1), toColor);
    auto range = std::pair<Color, Color>(fromColor, toColor);
    colorOption.SetRange(range);
}

void ParseColorOption(JSRef<JSObject>& colorJsObject, OHOS::Ace::NG::ParticleColorPropertyOption& colorOption)
{
    auto colorRangeJsValue = colorJsObject->GetProperty("range");
    ParseColorInitRange(colorRangeJsValue, colorOption);

    auto colorDist = OHOS::Ace::NG::DistributionType::UNIFORM;
    auto colorDistJsValue = colorJsObject->GetProperty("distributionType");
    if (colorDistJsValue->IsNumber()) {
        auto colorDistInt = colorDistJsValue->ToNumber<int32_t>();
        if (colorDistInt >= static_cast<int32_t>(OHOS::Ace::NG::DistributionType::UNIFORM) &&
            colorDistInt <= static_cast<int32_t>(OHOS::Ace::NG::DistributionType::GAUSSIAN)) {
            colorDist = static_cast<OHOS::Ace::NG::DistributionType>(colorDistInt);
        }
    }
    colorOption.SetDistribution(colorDist);

    auto updaterJsValue = colorJsObject->GetProperty("updater");
    NG::ParticleColorPropertyUpdater updater;
    if (updaterJsValue->IsObject()) {
        auto updaterJsObject = JSRef<JSObject>::Cast(updaterJsValue);
        if (ParseColorUpdater(updaterJsObject, updater)) {
            colorOption.SetUpdater(updater);
            return;
        }
    }
    updater.SetUpdateType(NG::UpdaterType::NONE_UPDATER);
    NG::ParticleColorPropertyUpdaterConfig noneUpdaterConfig;
    noneUpdaterConfig.SetInValid(0);
    updater.SetConfig(noneUpdaterConfig);
    colorOption.SetUpdater(updater);
}

void ParseParticleVelocity(JSRef<JSVal> jsValue, OHOS::Ace::NG::VelocityProperty& velocity)
{
    auto defaultPair = std::pair<float, float>(0.0f, 0.0f);
    if (!jsValue->IsObject()) {
        velocity.SetSpeedRange(defaultPair);
        velocity.SetAngleRange(defaultPair);
        return;
    }
    auto jsValueObj = JSRef<JSObject>::Cast(jsValue);
    auto speedJsValue = jsValueObj->GetProperty("speed");
    auto angleJsValue = jsValueObj->GetProperty("angle");
    auto speedPair = ParseParticleRange(speedJsValue, 0.0f);
    if (speedPair.has_value()) {
        velocity.SetSpeedRange(speedPair.value());
    } else {
        velocity.SetSpeedRange(defaultPair);
    }
    auto anglePair = ParseParticleRange(angleJsValue, 0.0f);
    if (anglePair.has_value()) {
        velocity.SetAngleRange(anglePair.value());
    } else {
        velocity.SetAngleRange(defaultPair);
    }
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
        ParseFloatOption(speedObject, speedOption, DEFAULT_SPEED, MIN_SPEED, MAX_SPEED);
        acceleration.SetSpeed(speedOption);
    }
    OHOS::Ace::NG::ParticleFloatPropertyOption angleOption;
    if (alphaValue->IsObject()) {
        auto alphaObject = JSRef<JSObject>::Cast(alphaValue);
        ParseFloatOption(alphaObject, angleOption, DEFAULT_ANGLE, MIN_ANGLE, MAX_ANGLE);
        acceleration.SetAngle(angleOption);
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
        ParseColorOption(colorJsObj, colorOption);
        particleOption.SetParticleColorOption(colorOption);
    }

    auto opacityJsValue = particleJsObj->GetProperty("opacity");
    if (opacityJsValue->IsObject()) {
        auto opacityJsObj = JSRef<JSObject>::Cast(opacityJsValue);
        OHOS::Ace::NG::ParticleFloatPropertyOption opacityOption;
        ParseFloatOption(opacityJsObj, opacityOption, DEFAULT_OPACITY, MIN_OPACITY, MAX_OPACITY);
        particleOption.SetParticleOpacityOption(opacityOption);
    }

    auto scaleJsValue = particleJsObj->GetProperty("scale");
    if (scaleJsValue->IsObject()) {
        auto scaleJsObj = JSRef<JSObject>::Cast(scaleJsValue);
        OHOS::Ace::NG::ParticleFloatPropertyOption scaleOption;
        ParseFloatOption(scaleJsObj, scaleOption, DEFAULT_SCALE, MIN_SCALE, MAX_SCALE);
        particleOption.SetParticleScaleOption(scaleOption);
    }

    auto velocityJsValue = particleJsObj->GetProperty("velocity");
    OHOS::Ace::NG::VelocityProperty velocity;
    ParseParticleVelocity(velocityJsValue, velocity);
    particleOption.SetParticleVelocityOption(velocity);

    auto accelerationJsValue = particleJsObj->GetProperty("acceleration");
    OHOS::Ace::NG::AccelerationProperty acceleration;
    ParseParticleAcceleration(accelerationJsValue, acceleration);
    particleOption.SetParticleAccelerationOption(acceleration);

    auto spinJsValue = particleJsObj->GetProperty("spin");
    if (spinJsValue->IsObject()) {
        auto spinJsObj = JSRef<JSObject>::Cast(spinJsValue);
        OHOS::Ace::NG::ParticleFloatPropertyOption spinOption;
        ParseFloatOption(spinJsObj, spinOption, DEFAULT_SPIN, MIN_SPIN, MAX_SPIN);
        particleOption.SetParticleSpinOption(spinOption);
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
void JSParticle::AddDisturbance(std::vector<OHOS::Ace::ParticleDisturbance>& dataArray, const JSRef<JSObject>& paramObj)
{
    float strength = paramObj->GetProperty("strength")->ToNumber<float>();
    int shape = paramObj->GetProperty("shape")->ToNumber<int>();
    int sizeXValue = 0;
    int sizeYValue = 0;
    int positionXValue = 0;
    int positionYValue = 0;
    GetSizeAndPositionValues(paramObj, sizeXValue, sizeYValue, positionXValue, positionYValue);
    int feather = paramObj->GetProperty("feather")->ToNumber<int>();
    feather = std::clamp(feather, 0, 100);
    float noiseScale = 1.0f;
    if (paramObj->GetProperty("noiseScale")->IsNumber()) {
        noiseScale = paramObj->GetProperty("noiseScale")->ToNumber<float>();
        if (noiseScale < 0.0f) {
            noiseScale = 1.0f;
        }
    }
    float noiseFrequency = 1.0f;
    if (paramObj->GetProperty("noiseFrequency")->IsNumber()) {
        noiseFrequency = paramObj->GetProperty("noiseFrequency")->ToNumber<float>();
        if (noiseFrequency < 0.0f) {
            noiseFrequency = 1.0f;
        }
    }
    float noiseAmplitude = 1.0f;
    if (paramObj->GetProperty("noiseAmplitude")->IsNumber()) {
        noiseAmplitude = paramObj->GetProperty("noiseAmplitude")->ToNumber<float>();
        if (noiseAmplitude < 0.0f) {
            noiseAmplitude = 1.0f;
        }
    }
    ParticleDisturbance disturbanceField;
    disturbanceField.strength = strength;
    disturbanceField.shape = static_cast<ParticleDisturbanceShapeType>(shape);
    disturbanceField.size[0] = sizeXValue;
    disturbanceField.size[1] = sizeYValue;
    disturbanceField.position[0] = positionXValue;
    disturbanceField.position[1] = positionYValue;
    disturbanceField.feather = feather;
    disturbanceField.noiseScale = noiseScale;
    disturbanceField.noiseFrequency = noiseFrequency;
    disturbanceField.noiseAmplitude = noiseAmplitude;
    dataArray.push_back(disturbanceField);
}

void JSParticle::GetSizeAndPositionValues(
    const JSRef<JSObject>& paramObj, int& sizeXValue, int& sizeYValue, int& positionXValue, int& positionYValue)
{
    JSRef<JSVal> sizeJsValue = paramObj->GetProperty("size");
    if (sizeJsValue->IsObject()) {
        JSRef<JSObject> sizeJsObject = JSRef<JSObject>::Cast(sizeJsValue);
        sizeXValue = sizeJsObject->GetProperty("width")->ToNumber<int>();
        sizeYValue = sizeJsObject->GetProperty("height")->ToNumber<int>();
    }

    JSRef<JSVal> positionJsValue = paramObj->GetProperty("position");
    if (positionJsValue->IsObject()) {
        JSRef<JSObject> positionJsObject = JSRef<JSObject>::Cast(positionJsValue);
        positionXValue = positionJsObject->GetProperty("x")->ToNumber<int>();
        positionYValue = positionJsObject->GetProperty("y")->ToNumber<int>();
    }
}

void JSParticle::JsDisturbanceFields(const JSCallbackInfo& args)
{
    if (args.Length() != 1 || !args[0]->IsArray()) {
        return;
    }
    std::vector<ParticleDisturbance> dataArray;
    JSRef<JSArray> dataJsArray = JSRef<JSArray>::Cast(args[0]);
    for (size_t i = 0; i < dataJsArray->Length(); i++) {
        if (dataJsArray->GetValueAt(i)->IsObject()) {
            auto jsObject = JSRef<JSObject>::Cast(dataJsArray->GetValueAt(i));
            AddDisturbance(dataArray, jsObject);
        }
    }

    ParticleModel::GetInstance()->DisturbanceField(dataArray);
}

void JSParticle::ParseEmitterProperty(
    std::vector<OHOS::Ace::EmitterProperty>& data, const JSRef<JSObject>& paramObj)
{
    EmitterProperty emitterProperty;
    uint32_t index = 0u;
    if (paramObj->GetProperty("index")->IsNumber()) {
        uint32_t indexJsValue = paramObj->GetProperty("index")->ToNumber<uint32_t>();
        index = indexJsValue > 0 ? indexJsValue : 0;
    }
    emitterProperty.index = index;

    auto emitRateProperty = paramObj->GetProperty("emitRate");
    if (emitRateProperty->IsNumber()) {
        auto emitRateValue = emitRateProperty->ToNumber<int32_t>();
        emitterProperty.emitRate = emitRateValue >= 0 ? emitRateValue : PARTICLE_DEFAULT_EMITTER_RATE;
    }
    auto positionProperty = paramObj->GetProperty("position");
    if (positionProperty->IsObject()) {
        auto positionValue = Framework::JSRef<Framework::JSObject>::Cast(positionProperty);
        if (positionValue->GetProperty("x")->IsNumber() && positionValue->GetProperty("y")->IsNumber()) {
            auto positionXValue = positionValue->GetProperty("x")->ToNumber<float>();
            auto positonYValue = positionValue->GetProperty("y")->ToNumber<float>();
            emitterProperty.position = { positionXValue, positonYValue };
        }
    }
    auto sizeProperty = paramObj->GetProperty("size");
    if (sizeProperty->IsObject()) {
        auto sizeValue = Framework::JSRef<Framework::JSObject>::Cast(sizeProperty);
        auto sizeXValue = sizeValue->GetProperty("width")->ToNumber<float>();
        auto sizeYValue = sizeValue->GetProperty("height")->ToNumber<float>();
        if (sizeXValue > 0 && sizeYValue > 0) {
            emitterProperty.size = { sizeXValue, sizeYValue };
        }
    }

    ParseEmitterPropertyAnnulus(paramObj, emitterProperty);
    data.push_back(emitterProperty);
}

void JSParticle::JsEmitter(const JSCallbackInfo& args)
{
    if (args.Length() != 1 || !args[0]->IsArray()) {
        return;
    }
    std::vector<EmitterProperty> dataArray;
    JSRef<JSArray> dataJsArray = JSRef<JSArray>::Cast(args[0]);
    size_t length = dataJsArray->Length();
    for (size_t i = 0; i < length; i++) {
        if (dataJsArray->GetValueAt(i)->IsObject()) {
            auto jsObject = JSRef<JSObject>::Cast(dataJsArray->GetValueAt(i));
            ParseEmitterProperty(dataArray, jsObject);
        }
    }
    ParticleModel::GetInstance()->updateEmitter(dataArray);
}

void JSParticle::JSBind(BindingTarget globalObj)
{
    JSClass<JSParticle>::Declare("Particle");
    JSClass<JSParticle>::StaticMethod("create", &JSParticle::Create);
    JSClass<JSParticle>::StaticMethod("disturbanceFields", &JSParticle::JsDisturbanceFields);
    JSClass<JSParticle>::StaticMethod("emitter", &JSParticle::JsEmitter);
    JSClass<JSParticle>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
