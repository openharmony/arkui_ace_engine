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
constexpr int32_t PARTICLE_DEFAULT_EMITTER_RATE = 5;

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
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[0]->IsArray()) {
        GetArkUINodeModifiers()->getParticleModifier()->ResetEmitter(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto paramArray = Framework::JSRef<Framework::JSArray>::Cast(info[0]);

    ArkUIInt32orFloat32 index;
    ArkUIInt32orFloat32 hasEmitRate;
    ArkUIInt32orFloat32 emitRate;
    ArkUIInt32orFloat32 hasPosition;
    ArkUIInt32orFloat32 positionX;
    ArkUIInt32orFloat32 positionY;
    ArkUIInt32orFloat32 hasSize;
    ArkUIInt32orFloat32 sizeX;
    ArkUIInt32orFloat32 sizeY;

    std::vector<ArkUIInt32orFloat32> dataVector;
    auto length = paramArray->Length();
    dataVector.resize(length * 9);
    for (uint32_t i = 0; i < length; i++) {
        auto paramObj = Framework::JSRef<Framework::JSArray>::Cast(paramArray->GetValueAt(i));
        int indexValue = paramObj->GetProperty("index")->ToNumber<int>();
        index.i32 = indexValue;
        auto emitRateProperty = paramObj->GetProperty("emitRate");
        if (emitRateProperty->IsNumber()) {
            hasEmitRate.i32 = 1;
            int emitRateValue = emitRateProperty->ToNumber<int>();
            emitRate.i32 = emitRateValue > 0 ? emitRateValue : PARTICLE_DEFAULT_EMITTER_RATE;
        } else {
            hasEmitRate.i32 = 0;
        }
        auto positionProperty = paramObj->GetProperty("position");
        if (positionProperty->IsObject()) {
            hasPosition.i32 = 1;
            auto positionValue = Framework::JSRef<Framework::JSObject>::Cast(positionProperty);
            auto positonXvalue = positionValue->GetProperty("x")->ToNumber<float>();
            positionX.f32 = positonXvalue;
            auto positonYvalue = positionValue->GetProperty("y")->ToNumber<float>();
            positionY.f32 = positonYvalue;
        } else {
            hasPosition.i32 = 0;
        }
        auto sizeProperty = paramObj->GetProperty("size");
        if (sizeProperty->IsObject()) {
            hasSize.i32 = 1;
            auto sizeValue = Framework::JSRef<Framework::JSObject>::Cast(sizeProperty);
            auto sizeXvalue = sizeValue->GetProperty("width")->ToNumber<float>();
            sizeX.f32 = sizeXvalue;
            auto sizeYvalue = sizeValue->GetProperty("height")->ToNumber<float>();
            sizeY.f32 = sizeYvalue;
        } else {
            hasSize.i32 = 0;
        }
        dataVector.emplace_back(index);
        dataVector.emplace_back(hasEmitRate);
        dataVector.emplace_back(emitRate);
        dataVector.emplace_back(hasPosition);
        dataVector.emplace_back(positionX);
        dataVector.emplace_back(positionY);
        dataVector.emplace_back(hasSize);
        dataVector.emplace_back(sizeX);
        dataVector.emplace_back(sizeY);
    }
    GetArkUINodeModifiers()->getParticleModifier()->SetEmitter(nativeNode, dataVector.data(), dataVector.size());
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