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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_checkboxgroup_bridge.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t COLOR_ALPHA_VALUE = 0xffffff;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr double NUM_4 = 2.0;
bool ParseJsDimensionVp(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& result)
{
    if (value->IsNumber()) {
        result = CalcDimension(value->ToNumber(vm)->Value(), DimensionUnit::VP);
        return true;
    }
    if (value->IsString()) {
        result = StringUtils::StringToCalcDimension(value->ToString(vm)->ToString(), false, DimensionUnit::VP);
        return true;
    }
    // resouce ignore by design
    return false;
}
}   // namespace
ArkUINativeModuleValue CheckboxGroupBridge::SetGroupSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t selectedColor = secondArg->Uint32Value(vm);

    GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().SetGroupSelectedColor(nativeNode, selectedColor);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetGroupSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().ResetGroupSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::SetGroupUnSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t unSelectedColor = secondArg->Uint32Value(vm);

    GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().SetGroupUnSelectedColor(nativeNode, unSelectedColor);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetGroupUnSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().ResetGroupUnSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::SetGroupSelectAll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool selectAll = secondArg->ToBoolean(vm)->Value();

    GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().SetGroupSelectAll(nativeNode, selectAll);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetGroupSelectAll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().ResetGroupSelectAll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension width;
    if (!jsValue->IsUndefined()) {
        ParseJsDimensionVp(vm, jsValue, width);
        if (width.IsNegative()) {
            GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().ResetCheckboxGroupWidth(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }

        GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().SetCheckboxGroupWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetCheckboxGroupWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().ResetCheckboxGroupWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension height;
    if (!jsValue->IsUndefined()) {
        ParseJsDimensionVp(vm, jsValue, height);
        if (height.IsNegative()) {
            GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().ResetCheckboxGroupHeight(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }

        GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().SetCheckboxGroupHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetCheckboxGroupHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().ResetCheckboxGroupHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::SetGroupMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t strokeColorValue = COLOR_ALPHA_VALUE;

    if (!colorArg->IsUndefined()) {
        strokeColorValue = colorArg->Uint32Value(vm);
    }
    
    CalcDimension size;
    CalcDimension width;

    if (!sizeArg->IsUndefined() && !widthArg->IsUndefined()) {
        ParseJsDimensionVp(vm, sizeArg, size);
        if (!ParseJsDimensionVp(vm, widthArg, width)) {
            width.SetValue(NUM_4);
        }
    }

    GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().SetGroupMark(nativeNode,
        strokeColorValue, width.Value(), size.Value());

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetGroupMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxGroupModifier().ResetGroupMark(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
