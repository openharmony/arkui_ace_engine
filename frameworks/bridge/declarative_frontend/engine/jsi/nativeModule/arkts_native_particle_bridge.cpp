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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_particle_bridge.h"

#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int32_t DISTURBANCE_FIELD_SIZE = 10;
constexpr int32_t STEP_0 = 0;
constexpr int32_t STEP_1 = 1;
constexpr int32_t STEP_2 = 2;
constexpr int32_t STEP_3 = 3;
constexpr int32_t STEP_4 = 4;
constexpr int32_t STEP_5 = 5;
constexpr int32_t STEP_6 = 6;
constexpr int32_t STEP_7 = 7;
constexpr int32_t STEP_8 = 8;
constexpr int32_t STEP_9 = 9;
constexpr double DEFAULT_CENTER_VALUE = 0.5;
constexpr int32_t DEFAULT_ANNULUS_UNIT = static_cast<int32_t>(DimensionUnit::PERCENT);
constexpr double DEFAULT_START_ANGLE_VALUE = 0.0;
constexpr double DEFAULT_END_ANGLE_VALUE = 360.0;

namespace {
void ParseAnnulusRegionCenter(EcmaVM* vm, panda::Local<panda::FunctionRef> emitterPropertyObj,
    ArkEmitterPropertyOptions& emitterProperty)
{
    //parse annulusRegion center
    auto isSetCenter = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "isSetCenter"));
    int32_t hasCenterValue = 0;
    ArkTSUtils::ParseJsInteger(vm, isSetCenter, hasCenterValue);
    emitterProperty.isSetCenter = hasCenterValue;
    if (hasCenterValue == 1) {
        auto centerXValueJs = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "centerXValue"));
        auto centerXUnitJs = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "centerXUnit"));
        double centerXValue = DEFAULT_CENTER_VALUE;
        int32_t centerXUnit = DEFAULT_ANNULUS_UNIT;
        ArkTSUtils::ParseJsDouble(vm, centerXValueJs, centerXValue);
        ArkTSUtils::ParseJsInteger(vm, centerXUnitJs, centerXUnit);
        ArkUIDimensionType centerX;
        centerX.value = centerXValue;
        centerX.units = centerXUnit;
        emitterProperty.centerX = centerX;

        auto centerYValueJs = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "centerYValue"));
        auto centerYUnitJs = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "centerYUnit"));
        double centerYValue = DEFAULT_CENTER_VALUE;
        int32_t centerYUnit = DEFAULT_ANNULUS_UNIT;
        ArkTSUtils::ParseJsDouble(vm, centerYValueJs, centerYValue);
        ArkTSUtils::ParseJsInteger(vm, centerYUnitJs, centerYUnit);
        ArkUIDimensionType centerY;
        centerY.value = centerYValue;
        centerY.units = centerYUnit;
        emitterProperty.centerY = centerY;
    }
}

void ParseAnnulusRegionRadius(EcmaVM* vm, panda::Local<panda::FunctionRef> emitterPropertyObj,
    ArkEmitterPropertyOptions& emitterProperty)
{
    //parse annulusRegion radius
    auto isSetInnerRadius = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "isSetInnerRadius"));
    int32_t hasInnerRadiusValue = 0;
    ArkTSUtils::ParseJsInteger(vm, isSetInnerRadius, hasInnerRadiusValue);
    emitterProperty.isSetInnerRadius = hasInnerRadiusValue;
    if (hasInnerRadiusValue == 1) {
        auto innerRadiusValueJs = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "innerRadiusValue"));
        auto innerRadiusXUnitJs = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "innerRadiusUnit"));
        double innerRadiusValue = 0.0;
        int32_t innerRadiusXUnit = 0;
        ArkTSUtils::ParseJsDouble(vm, innerRadiusValueJs, innerRadiusValue);
        ArkTSUtils::ParseJsInteger(vm, innerRadiusXUnitJs, innerRadiusXUnit);
        ArkUIDimensionType innerRadius;
        innerRadius.value = innerRadiusValue;
        innerRadius.units = innerRadiusXUnit;
        emitterProperty.innerRadius = innerRadius;
    }

    auto isSetOuterRadius = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "isSetOuterRadius"));
    int32_t hasOuterRadiusValue = 0;
    ArkTSUtils::ParseJsInteger(vm, isSetOuterRadius, hasOuterRadiusValue);
    emitterProperty.isSetOuterRadius = hasOuterRadiusValue;
    if (hasOuterRadiusValue == 1) {
        auto outerRadiusValueJs = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "outerRadiusValue"));
        auto outerRadiusXUnitJs = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "outerRadiusUnit"));
        double outerRadiusValue = 0.0;
        int32_t outerRadiusXUnit = 0;
        ArkTSUtils::ParseJsDouble(vm, outerRadiusValueJs, outerRadiusValue);
        ArkTSUtils::ParseJsInteger(vm, outerRadiusXUnitJs, outerRadiusXUnit);
        ArkUIDimensionType outerRadius;
        outerRadius.value = outerRadiusValue;
        outerRadius.units = outerRadiusXUnit;
        emitterProperty.outerRadius = outerRadius;
    }
}

void ParseAnnulusRegionAngle(EcmaVM* vm, panda::Local<panda::FunctionRef> emitterPropertyObj,
    ArkEmitterPropertyOptions& emitterProperty)
{
    //parse annulusRegion angle
    auto isSetStartAngle = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "isSetStartAngle"));
    int32_t hasStartAngleValue = 0;
    ArkTSUtils::ParseJsInteger(vm, isSetStartAngle, hasStartAngleValue);
    emitterProperty.isSetStartAngle = hasStartAngleValue;
    if (hasStartAngleValue == 1) {
        auto startAngle = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "startAngle"));
        double startAngleValue = DEFAULT_START_ANGLE_VALUE;
        ArkTSUtils::ParseJsDouble(vm, startAngle, startAngleValue);
        emitterProperty.startAngle = startAngleValue;
    }

    auto isSetEndAngle = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "isSetEndAngle"));
    int32_t hasEndAngleValue = 0;
    ArkTSUtils::ParseJsInteger(vm, isSetEndAngle, hasEndAngleValue);
    emitterProperty.isSetEndAngle = hasEndAngleValue;
    if (hasEndAngleValue == 1) {
        auto endAngle = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "endAngle"));
        double endAngleValue = DEFAULT_END_ANGLE_VALUE;
        ArkTSUtils::ParseJsDouble(vm, endAngle, endAngleValue);
        emitterProperty.endAngle = endAngleValue;
    }
}

void ParseEmitterAnnulusRegion(EcmaVM* vm, panda::Local<panda::FunctionRef> emitterPropertyObj,
    ArkEmitterPropertyOptions& emitterProperty)
{
    //parse annulusRegion
    auto isSetAnnulusRegion = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "isSetAnnulusRegion"));
    int32_t hasAnnulusRegionValue = 0;
    ArkTSUtils::ParseJsInteger(vm, isSetAnnulusRegion, hasAnnulusRegionValue);
    emitterProperty.isSetAnnulusRegion = hasAnnulusRegionValue;
    if (hasAnnulusRegionValue == 1) {
        ParseAnnulusRegionCenter(vm, emitterPropertyObj, emitterProperty);
        ParseAnnulusRegionRadius(vm, emitterPropertyObj, emitterProperty);
        ParseAnnulusRegionAngle(vm, emitterPropertyObj, emitterProperty);
    }
}

void ParseEmitterPositionAndSize(EcmaVM* vm, panda::Local<panda::FunctionRef> emitterPropertyObj,
    ArkEmitterPropertyOptions& emitterProperty)
{
    //parse position
    auto isSetPosition = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "isSetPosition"));
    int32_t hasPositionValue = 0;
    ArkTSUtils::ParseJsInteger(vm, isSetPosition, hasPositionValue);
    emitterProperty.isSetPosition = hasPositionValue;
    if (hasPositionValue == 1) {
        auto positionX = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "positionX"));
        double positionXValue = 0.0;
        ArkTSUtils::ParseJsDouble(vm, positionX, positionXValue);
        emitterProperty.positionX = positionXValue;
        auto positionY = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "positionY"));
        double positionYValue = 0.0;
        ArkTSUtils::ParseJsDouble(vm, positionY, positionYValue);
        emitterProperty.positionY = positionYValue;
    }

    //parse size
    auto isSetSize = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "isSetSize"));
    int32_t hasSizeValue = 0;
    ArkTSUtils::ParseJsInteger(vm, isSetSize, hasSizeValue);
    emitterProperty.isSetSize = hasSizeValue;
    if (hasSizeValue == 1) {
        auto sizeWidth = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "sizeWidth"));
        double sizeWidthValue = 0.0;
        ArkTSUtils::ParseJsDouble(vm, sizeWidth, sizeWidthValue);
        emitterProperty.sizeWidth = sizeWidthValue;
        auto sizeHeight = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "sizeHeight"));
        double sizeHeightValue = 0.0;
        ArkTSUtils::ParseJsDouble(vm, sizeHeight, sizeHeightValue);
        emitterProperty.sizeHeight = sizeHeightValue;
    }
}
}

ArkUINativeModuleValue ParticleBridge::SetDisturbanceField(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValueRef = runtimeCallInfo->GetCallArgRef(1);
    if (!jsValueRef->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto array = panda::Local<panda::ArrayRef>(jsValueRef);
    auto length = array->Length(vm);
    std::vector<ArkUIInt32orFloat32> dataVector;
    dataVector.resize(length);
    for (uint32_t index = 0; index < length / DISTURBANCE_FIELD_SIZE; index++) {
        Local<JSValueRef> strength = panda::ArrayRef::GetValueAt(vm, array, index * DISTURBANCE_FIELD_SIZE + STEP_0);
        int32_t strengthValue = 0;
        ArkTSUtils::ParseJsInteger(vm, strength, strengthValue);
        dataVector[index * DISTURBANCE_FIELD_SIZE + STEP_0].f32 = static_cast<float>(strengthValue);
        Local<JSValueRef> shape = panda::ArrayRef::GetValueAt(vm, array, index * DISTURBANCE_FIELD_SIZE + STEP_1);
        int32_t shapeValue = 0;
        ArkTSUtils::ParseJsInteger(vm, shape, shapeValue);
        dataVector[index * DISTURBANCE_FIELD_SIZE + STEP_1].i32 = static_cast<int32_t>(shapeValue);
        Local<JSValueRef> sizeWidth = panda::ArrayRef::GetValueAt(vm, array, index * DISTURBANCE_FIELD_SIZE + STEP_2);
        int32_t sizeWidthValue = 0;
        ArkTSUtils::ParseJsInteger(vm, sizeWidth, sizeWidthValue);
        dataVector[index * DISTURBANCE_FIELD_SIZE + STEP_2].i32 = sizeWidthValue;
        Local<JSValueRef> sizeHeight = panda::ArrayRef::GetValueAt(vm, array, index * DISTURBANCE_FIELD_SIZE + STEP_3);
        int32_t sizeHeightValue = 0;
        ArkTSUtils::ParseJsInteger(vm, sizeHeight, sizeHeightValue);
        dataVector[index * DISTURBANCE_FIELD_SIZE + STEP_3].i32 = sizeHeightValue;
        Local<JSValueRef> positionX = panda::ArrayRef::GetValueAt(vm, array, index * DISTURBANCE_FIELD_SIZE + STEP_4);
        int32_t positionXValue = 0;
        ArkTSUtils::ParseJsInteger(vm, positionX, positionXValue);
        dataVector[index * DISTURBANCE_FIELD_SIZE + STEP_4].i32 = positionXValue;
        Local<JSValueRef> positionY = panda::ArrayRef::GetValueAt(vm, array, index * DISTURBANCE_FIELD_SIZE + STEP_5);
        int32_t positionYValue = 0;
        ArkTSUtils::ParseJsInteger(vm, positionY, positionYValue);
        dataVector[index * DISTURBANCE_FIELD_SIZE + STEP_5].i32 = positionYValue;
        Local<JSValueRef> feather = panda::ArrayRef::GetValueAt(vm, array, index * DISTURBANCE_FIELD_SIZE + STEP_6);
        int32_t featherValue = 0;
        ArkTSUtils::ParseJsInteger(vm, feather, featherValue);
        dataVector[index * DISTURBANCE_FIELD_SIZE + STEP_6].i32 = featherValue;
        Local<JSValueRef> noiseScale = panda::ArrayRef::GetValueAt(vm, array, index * DISTURBANCE_FIELD_SIZE + STEP_7);
        double noiseScaleValue = 1.0;
        ArkTSUtils::ParseJsDouble(vm, noiseScale, noiseScaleValue);
        dataVector[index * DISTURBANCE_FIELD_SIZE + STEP_7].f32 = static_cast<float>(noiseScaleValue);
        Local<JSValueRef> noiseFrequency =
            panda::ArrayRef::GetValueAt(vm, array, index * DISTURBANCE_FIELD_SIZE + STEP_8);
        double noiseFrequencyValue = 1.0;
        ArkTSUtils::ParseJsDouble(vm, noiseFrequency, noiseFrequencyValue);
        dataVector[index * DISTURBANCE_FIELD_SIZE + STEP_8].f32 = static_cast<float>(noiseScaleValue);
        Local<JSValueRef> noiseAmplitude =
            panda::ArrayRef::GetValueAt(vm, array, index * DISTURBANCE_FIELD_SIZE + STEP_9);
        double noiseAmplitudeValue = 1.0;
        ArkTSUtils::ParseJsDouble(vm, noiseAmplitude, noiseAmplitudeValue);
        dataVector[index * DISTURBANCE_FIELD_SIZE + STEP_9].f32 = static_cast<float>(noiseAmplitudeValue);
    }
    ArkUIInt32orFloat32* dataArray = dataVector.data();
    GetArkUINodeModifiers()->getParticleModifier()->SetDisturbanceField(
        nativeNode, dataArray, static_cast<ArkUI_Int32>(dataVector.size()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ParticleBridge::ResetDisturbanceField(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getParticleModifier()->ResetDisturbanceField(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ParticleBridge::SetEmitter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValueRef = runtimeCallInfo->GetCallArgRef(1);
    if (!jsValueRef->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto array = panda::Local<panda::ArrayRef>(jsValueRef);
    auto length = array->Length(vm);
    std::vector<ArkEmitterPropertyOptions> dataVector;
    dataVector.resize(length);

    for (uint32_t i = 0; i < length; i++) {
        ArkEmitterPropertyOptions emitterProperty;
        Local<JSValueRef> emitterPropertyValue = panda::ArrayRef::GetValueAt(vm, array, i);
        if (emitterPropertyValue->IsObject(vm)) {
            auto emitterPropertyObj = emitterPropertyValue->ToObject(vm);

            //parse index
            auto index = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "index"));
            int32_t indexValue = 0;
            ArkTSUtils::ParseJsInteger(vm, index, indexValue);
            emitterProperty.index = indexValue;

            //parse emitRate
            auto isSetEmitRate = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "isSetEmitRate"));
            int32_t hasEmitRateValue = 0;
            ArkTSUtils::ParseJsInteger(vm, isSetEmitRate, hasEmitRateValue);
            emitterProperty.isSetEmitRate = hasEmitRateValue;
            if (hasEmitRateValue == 1) {
                auto emitRate = emitterPropertyObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "emitRate"));
                int32_t emitRateValue = 0;
                ArkTSUtils::ParseJsInteger(vm, emitRate, emitRateValue);
                emitterProperty.emitRate = emitRateValue;
            }
            ParseEmitterPositionAndSize(vm, emitterPropertyObj, emitterProperty);
            ParseEmitterAnnulusRegion(vm, emitterPropertyObj, emitterProperty);
        }
        dataVector.emplace_back(emitterProperty);
    }
    GetArkUINodeModifiers()->getParticleModifier()->SetEmitter(
        nativeNode, dataVector.data(), static_cast<ArkUI_Int32>(dataVector.size()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ParticleBridge::ResetEmitter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getParticleModifier()->ResetEmitter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG