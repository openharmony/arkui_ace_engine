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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_checkbox_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/utils/arkts_native_parse.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
const Color STROKE_COLOR = Color::WHITE;
const double DEFAULT_MARK_WIDTH = 2.0;

ArkUINativeModuleValue CheckboxBridge::SetMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t strokeColorValue = STROKE_COLOR.GetValue();

    if (!colorArg->IsUndefined()) {
        strokeColorValue= colorArg->Uint32Value(vm);
    }
    
    CalcDimension size;
    CalcDimension width;

    if (!sizeArg->IsUndefined() && !widthArg->IsUndefined()) {
        ParseJsDimensionVp(vm, sizeArg, size);
        if (!ParseJsDimensionVp(vm, widthArg, width)) {
            width.SetValue(DEFAULT_MARK_WIDTH);
        }
    }

    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetMark(nativeNode,
        strokeColorValue, width.Value(), size.Value());

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::SetSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool select = secondArg->ToBoolean(vm)->Value();

    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetSelect(nativeNode, select);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::SetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t selectedColor = secondArg->Uint32Value(vm);

    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetSelectedColor(nativeNode, selectedColor);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::SetUnSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t unSelectedColor = secondArg->Uint32Value(vm);

    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetUnSelectedColor(nativeNode, unSelectedColor);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::SetCheckboxWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    CalcDimension width;
    if (!jsValue->IsUndefined()) {
        ParseJsDimensionVp(vm, jsValue, width);
        if (width.IsNegative()) {
            GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetCheckboxWidth(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
    
        GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetCheckboxWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::SetCheckboxHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    CalcDimension height;
    if (!jsValue->IsUndefined()) {
        ParseJsDimensionVp(vm, jsValue, height);
        if (height.IsNegative()) {
            GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetCheckboxHeight(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
    
        GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetCheckboxHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::ResetMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetMark(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::ResetSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetSelect(nativeNode, false);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::ResetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto theme = Framework::JSViewAbstract::GetTheme<CheckboxTheme>();
    uint32_t selectedColor = theme->GetActiveColor().GetValue();

    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetSelectedColor(nativeNode, selectedColor);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::ResetUnSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto theme = Framework::JSViewAbstract::GetTheme<CheckboxTheme>();
    uint32_t unSelectedColor = theme->GetInactiveColor().GetValue();

    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetUnSelectedColor(nativeNode, unSelectedColor);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::ResetCheckboxWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetCheckboxWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::ResetCheckboxHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetCheckboxHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
