/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "arkoala_api.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkoala_common_modifier.h"

namespace OHOS::Ace::Framework {

panda::Local<panda::JSValueRef> ArkGetFrameNodeById(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    LOGE("linyihao ArkGetFrameNodeById");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int nodeId = firstArg->ToNumber(vm)->Value();
    LOGE("linyihao nodeId = %{public}d", nodeId);
    auto nodePtr = NG::GetFrameNodeById(nodeId);
    LOGE("linyihao2 nativePtr = %{public}p", nodePtr);
    return panda::NativePointerRef::New(vm, nodePtr);
}

// panda::Local<panda::JSValueRef> ApplyModifierFinish(panda::JsiRuntimeCallInfo* runtimeCallInfo)
// {
//     LOGE("linyihao ApplyModifierFinish");
//     EcmaVM* vm = runtimeCallInfo->GetVM();
//     Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
//     void* nativeNode = firstArg->ToNativePointer(vm)->Value();
//     LOGE("linyihao2 nativeNode = %{public}p", nativeNode);
//     NG::ApplyModifierFinish(nativeNode);
//     return panda::JSValueRef::Undefined(vm);
// }

panda::Local<panda::JSValueRef> ArkSetBackgroundColor(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    LOGE("linyihao ArkBackgroundColor");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    LOGE("linyihao2 nativeNode = %{public}p", nativeNode);
    // std::string color = secondArg->ToString(vm)->ToString();
    int color = secondArg->ToNumber(vm)->Value();
    LOGE("linyihao2 color = %{public}d", color);
    NG::SetBackgroundColor(nativeNode, color);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetWidth(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    float value = secondArg->ToNumber(vm)->Value();
    int unit = thirdArg->ToNumber(vm)->Value();
    NG::SetWidth(nativeNode, value, unit);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetHeight(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    float value = secondArg->ToNumber(vm)->Value();
    int unit = thirdArg->ToNumber(vm)->Value();
    NG::SetHeight(nativeNode, value, unit);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetOpacity(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    float value = secondArg->ToNumber(vm)->Value();
    NG::SetOpacity(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetZIndex(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int zIndex = secondArg->ToNumber(vm)->Value();
    NG::SetZIndex(nativeNode, zIndex);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetHitTestBehavior(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int hitTestBehavior = secondArg->ToNumber(vm)->Value();
    NG::SetHitTestBehavior(nativeNode, hitTestBehavior);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetPosition(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(4);

    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    float x = secondArg->ToNumber(vm)->Value();
    int xunit = thirdArg->ToNumber(vm)->Value();
    float y = fourthArg->ToNumber(vm)->Value();
    int yunit = fifthArg->ToNumber(vm)->Value();
    NG::SetHitTestBehavior(nativeNode, x, xunit, y, yunit);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetBorderWidth(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(3);

    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto secondVal = panda::Local<panda::ArrayRef>(secondArg);
    auto secondLen = arrayVal->Length(vm);
    float* widthValues = new float[secondLen];
    for (auto i = 0U; i < secondLen; i++) {
        auto subItemVal = panda::ArrayRef::GetValueAt(vm, secondVal, i);
        widthValues[i] = subItemVal->ToNumber(vm)->Value();
    }
    auto thirdVal = panda::Local<panda::ArrayRef>(thirdArg);
    auto thirdLen = arrayVal->Length(vm);
    int* widthUnits = new int[thirdLen];
    for (auto i = 0U; i < thirdLen; i++) {
        auto subItemVal = panda::ArrayRef::GetValueAt(vm, thirdVal, i);
        widthUnits[i] = subItemVal->ToNumber(vm)->Value();
    }
    int length = fourthArg->ToNumber(vm)->Value();
    NG::SetBorderWidth(nativeNode, widthValues, widthUnits, length);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetBorderColor(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);

    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto secondVal = panda::Local<panda::ArrayRef>(secondArg);
    auto secondLen = arrayVal->Length(vm);
    int* colors = new int[secondLen];
    for (auto i = 0U; i < secondLen; i++) {
        auto subItemVal = panda::ArrayRef::GetValueAt(vm, secondVal, i);
        colors[i] = subItemVal->ToNumber(vm)->Value();
    }
    int length = thirdArg->ToNumber(vm)->Value();
    NG::SetBorderColor(nativeNode, colors, length);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetBorderStyle(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);

    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto secondVal = panda::Local<panda::ArrayRef>(secondArg);
    auto secondLen = arrayVal->Length(vm);
    int* styles = new int[secondLen];
    for (auto i = 0U; i < secondLen; i++) {
        auto subItemVal = panda::ArrayRef::GetValueAt(vm, secondVal, i);
        styles[i] = subItemVal->ToNumber(vm)->Value();
    }
    int length = thirdArg->ToNumber(vm)->Value();
    NG::SetBorderStyle(nativeNode, styles, length);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetBorderRadius(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(3);

    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto secondVal = panda::Local<panda::ArrayRef>(secondArg);
    auto secondLen = arrayVal->Length(vm);
    float* radiusValues = new float[secondLen];
    for (auto i = 0U; i < secondLen; i++) {
        auto subItemVal = panda::ArrayRef::GetValueAt(vm, secondVal, i);
        radiusValues[i] = subItemVal->ToNumber(vm)->Value();
    }
    auto thirdVal = panda::Local<panda::ArrayRef>(thirdArg);
    auto thirdLen = arrayVal->Length(vm);
    int* radiusUnits = new int[thirdLen];
    for (auto i = 0U; i < thirdLen; i++) {
        auto subItemVal = panda::ArrayRef::GetValueAt(vm, thirdVal, i);
        radiusUnits[i] = subItemVal->ToNumber(vm)->Value();
    }
    int length = fourthArg->ToNumber(vm)->Value();
    NG::SetBorderRadius(nativeNode, radiusValues, radiusUnits, length);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetBackShadow(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);

    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto secondVal = panda::Local<panda::ArrayRef>(secondArg);
    auto secondLen = arrayVal->Length(vm);
    float* shadows = new float[secondLen];
    for (auto i = 0U; i < secondLen; i++) {
        auto subItemVal = panda::ArrayRef::GetValueAt(vm, secondVal, i);
        shadows[i] = subItemVal->ToNumber(vm)->Value();
    }
    int length = thirdArg->ToNumber(vm)->Value();
    NG::SetBackShadow(nativeNode, shadows, length);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> ArkSetTransform(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);

    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto secondVal = panda::Local<panda::ArrayRef>(secondArg);
    auto secondLen = arrayVal->Length(vm);
    float* matrix = new float[secondLen];
    for (auto i = 0U; i < secondLen; i++) {
        auto subItemVal = panda::ArrayRef::GetValueAt(vm, secondVal, i);
        matrix[i] = subItemVal->ToNumber(vm)->Value();
    }
    int length = thirdArg->ToNumber(vm)->Value();
    NG::SetTransform(nativeNode, matrix, length);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> GetArkUINativeModule(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto object = panda::ObjectRef::New(vm);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "ArkGetFrameNodeById"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkGetFrameNodeById));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetBackgroundColor"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetBackgroundColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetWidth"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetWidth));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetHeight"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetHeight));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetOpacity"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetOpacity));

    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetBorderWidth"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetBorderWidth));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetBorderColor"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetBorderColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetBorderStyle"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetBorderStyle));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetBorderRadius"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetBorderRadius));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetBackShadow"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetBackShadow));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetTransform"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetTransform));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetBorder"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetBorder));

    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetZIndex"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetZIndex));    
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetHitTestBehavior"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetHitTestBehavior));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetPosition"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkSetPosition));
    //...
    return object;
}
}