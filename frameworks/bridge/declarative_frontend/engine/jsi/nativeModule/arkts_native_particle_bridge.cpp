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
    for (uint32_t index = 0; index < length / 10; index++) {
        Local<JSValueRef> strength = panda::ArrayRef::GetValueAt(vm, array, index * 10 + 0);
        int32_t strengthValue = 0;
        ArkTSUtils::ParseJsInteger(vm, strength, strengthValue);
        dataVector[index * 10 + 0].f32 = static_cast<float>(strengthValue);
        Local<JSValueRef> shape = panda::ArrayRef::GetValueAt(vm, array, index * 10 + 1);
        uint32_t shapeValue = 0;
        ArkTSUtils::ParseJsInteger(vm, shape, shapeValue);
        dataVector[index * 10 + 1].i32 = shapeValue;
        Local<JSValueRef> sizeWidth = panda::ArrayRef::GetValueAt(vm, array, index * 10 + 2);
        int32_t sizeWidthValue = 0;
        ArkTSUtils::ParseJsInteger(vm, sizeWidth, sizeWidthValue);
        dataVector[index * 10 + 2].i32 = sizeWidthValue;
        Local<JSValueRef> sizeHeight = panda::ArrayRef::GetValueAt(vm, array, index * 10 + 3);
        int32_t sizeHeightValue = 0;
        ArkTSUtils::ParseJsInteger(vm, sizeHeight, sizeHeightValue);
        dataVector[index * 10 + 3].i32 = sizeHeightValue;
        Local<JSValueRef> positionX = panda::ArrayRef::GetValueAt(vm, array, index * 10 + 4);
        int32_t positionXValue = 0;
        ArkTSUtils::ParseJsInteger(vm, positionX, positionXValue);
        dataVector[index * 10 + 4].i32 = positionXValue;
        Local<JSValueRef> positionY = panda::ArrayRef::GetValueAt(vm, array, index * 10 + 5);
        int32_t positionYValue = 0;
        ArkTSUtils::ParseJsInteger(vm, positionY, positionYValue);
        dataVector[index * 10 + 5].i32 = positionYValue;
        Local<JSValueRef> feather = panda::ArrayRef::GetValueAt(vm, array, index * 10 + 6);
        int32_t featherValue = 0;
        ArkTSUtils::ParseJsInteger(vm, feather, featherValue);
        dataVector[index * 10 + 6].i32 = featherValue;
        Local<JSValueRef> noiseScale = panda::ArrayRef::GetValueAt(vm, array, index * 10 + 7);
        double noiseScaleValue = 1.0;
        ArkTSUtils::ParseJsDouble(vm, noiseScale, noiseScaleValue);
        dataVector[index * 10 + 7].f32 = static_cast<float>(noiseScaleValue);
        Local<JSValueRef> noiseFrequency = panda::ArrayRef::GetValueAt(vm, array, index * 10 + 8);
        double noiseFrequencyValue = 1.0;
        ArkTSUtils::ParseJsDouble(vm, noiseFrequency, noiseFrequencyValue);
        dataVector[index * 10 + 8].f32 = static_cast<float>(noiseScaleValue);
        Local<JSValueRef> noiseAmplitude = panda::ArrayRef::GetValueAt(vm, array, index * 10 + 9);
        double noiseAmplitudeValue = 1.0;
        ArkTSUtils::ParseJsDouble(vm, noiseAmplitude, noiseAmplitudeValue);
        dataVector[index * 10 + 9].f32 = static_cast<float>(noiseAmplitudeValue);
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
    std::vector<ArkUIInt32orFloat32> dataVector;
    dataVector.resize(length);

    for (uint32_t i = 0; i < length / 9; i++) {
        Local<JSValueRef> index = panda::ArrayRef::GetValueAt(vm, array, i * 9 + 0);
        int32_t indexValue = 0;
        ArkTSUtils::ParseJsInteger(vm, index, indexValue);
        dataVector[i * 9 + 0].i32 = indexValue;

        Local<JSValueRef> hasEmitRate = panda::ArrayRef::GetValueAt(vm, array, i * 9 + 1);
        int32_t hasEmitRateValue = 0;
        ArkTSUtils::ParseJsInteger(vm, hasEmitRate, hasEmitRateValue);
        dataVector[i * 9 + 1].i32 = hasEmitRateValue;

        if (hasEmitRateValue == 1) { // has emitRate
            Local<JSValueRef> emitRate = panda::ArrayRef::GetValueAt(vm, array, i * 9 + 2);
            int32_t emitRateValue = 0;
            ArkTSUtils::ParseJsInteger(vm, emitRate, emitRateValue);
            dataVector[i * 9 + 2].i32 = emitRateValue;
        }

        Local<JSValueRef> hasPosition = panda::ArrayRef::GetValueAt(vm, array, i * 9 + 3);
        int32_t hasPositionValue = 0;
        ArkTSUtils::ParseJsInteger(vm, hasPosition, hasPositionValue);
        dataVector[i * 9 + 3].i32 = hasPositionValue;

        if (hasPositionValue == 1) { // has position
            Local<JSValueRef> positionX = panda::ArrayRef::GetValueAt(vm, array, i * 9 + 4);
            double positionXValue = 0.0;
            ArkTSUtils::ParseJsDouble(vm, positionX, positionXValue);
            dataVector[i * 9 + 4].f32 = static_cast<float>(positionXValue);
            Local<JSValueRef> positionY = panda::ArrayRef::GetValueAt(vm, array, i * 9 + 5);
            double positionYValue = 0.0;
            ArkTSUtils::ParseJsDouble(vm, positionY, positionYValue);
            dataVector[i * 9 + 5].f32 = static_cast<float>(positionYValue);
        }

        Local<JSValueRef> hasSize = panda::ArrayRef::GetValueAt(vm, array, i * 9 + 6);
        int32_t hasSizeValue = 0;
        ArkTSUtils::ParseJsInteger(vm, hasSize, hasSizeValue);
        dataVector[i * 9 + 6].i32 = hasSizeValue;

        if (hasSizeValue == 1) { // has size
            Local<JSValueRef> sizeWidth = panda::ArrayRef::GetValueAt(vm, array, i * 9 + 7);
            double sizeWidthValue = 0.0;
            ArkTSUtils::ParseJsDouble(vm, sizeWidth, sizeWidthValue);
            dataVector[i * 9 + 7].f32 = static_cast<float>(sizeWidthValue);
            Local<JSValueRef> sizeHeight = panda::ArrayRef::GetValueAt(vm, array, i * 9 + 8);
            double sizeHeightValue = 0.0;
            ArkTSUtils::ParseJsDouble(vm, sizeHeight, sizeHeightValue);
            dataVector[i * 9 + 8].f32 = static_cast<float>(sizeHeightValue);
        }
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