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

static void ParseDisturbanceField(const Local<JSValueRef>& jsValue,
    std::vector<ArkUIInt32orFloat32>& data, EcmaVM* vm, int index)
{
    Local<panda::ObjectRef> paramObj = jsValue->ToObject(vm);
    float strengthValue = 0.0f;
    ArkTSUtils::ParseNumberFromObject(vm, paramObj, "strength", strengthValue);
    data[index].f32 = strengthValue;
    int shapeValue = 0;
    ArkTSUtils::ParseNumberFromObject(vm, paramObj, "shape", shapeValue);
    data[index+1].i32 = shapeValue;
    auto jsSizeValueSize = paramObj->Get(vm, "size");
    if (jsSizeValueSize->IsObject()) {
        auto jsObject = jsSizeValueSize->ToObject(vm);
        int width = 0;
        int height = 0;
        ArkTSUtils::ParseNumberFromObject(vm, jsObject, "width", width);
        ArkTSUtils::ParseNumberFromObject(vm, jsObject, "height", height);
        data[index + 2].i32 = width;
        data[index + 3].i32 = height;
    }
    auto jsValuePosition = paramObj->Get(vm, "position");
    if (jsValuePosition->IsObject()) {
        auto jsObject = jsValuePosition->ToObject(vm);
        int x = 0;
        int y = 0;
        ArkTSUtils::ParseNumberFromObject(vm, jsObject, "x", x);
        ArkTSUtils::ParseNumberFromObject(vm, jsObject, "y", y);
        data[index + 4].i32 = x;
        data[index + 5].i32 = y;
    }
    int feather = 0;
    ArkTSUtils::ParseNumberFromObject(vm, paramObj, "feather", feather);
    feather = std::clamp(feather, 0, 100);
    data[index+6].i32 = feather;
    float noiseScale = 1.0f;
    bool noiseScaleSuccess = ArkTSUtils::ParseNumberFromObject(vm, paramObj, "noiseScale", noiseScale);
    if (!noiseScaleSuccess && noiseScale < 0.0f) {
        noiseScale = 1.0f;
    }
    data[index+7].f32 = noiseScale;
    float noiseFrequency = 1.0f;
    bool noiseFrequencySuccess = ArkTSUtils::ParseNumberFromObject(
        vm, paramObj, "noiseFrequency", noiseFrequency);
    if (!noiseFrequencySuccess && noiseScale < 0.0f) {
        noiseFrequency = 1.0f;
    }
    data[index+8].f32 = noiseFrequency;
    float noiseAmplitude = 1.0f;
    bool noiseAmplitudeSuccess = ArkTSUtils::ParseNumberFromObject(
        vm, paramObj, "noiseAmplitude", noiseAmplitude);
    if (!noiseAmplitudeSuccess && noiseScale < 0.0f) {
        noiseAmplitude = 1.0f;
    }
    data[index+9].f32 = noiseAmplitude;
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
    dataVector.resize(length*10);
    for (uint32_t index = 0; index < length; index++) {
        Local<JSValueRef> item = panda::ArrayRef::GetValueAt(vm, array, index);
        if (!item->IsObject()) {
            continue;
        }
        ParseDisturbanceField(item, dataVector, vm, index*10);
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
}