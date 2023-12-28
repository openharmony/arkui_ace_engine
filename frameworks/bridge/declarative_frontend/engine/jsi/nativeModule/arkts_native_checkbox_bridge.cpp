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

#include "core/interfaces/native/node/api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr float CHECK_BOX_MARK_SIZE_INVALID_VALUE = -1.0f;
const bool DEFAULT_SELECTED = false;

ArkUINativeModuleValue CheckboxBridge::SetMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1); // mark color
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(2);  // mark stroke size
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(3); // mark stroke width
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    auto theme = ArkTSUtils::GetTheme<CheckboxTheme>();
    Color strokeColor;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, strokeColor)) {
        strokeColor = theme->GetPointColor();
    }

    CalcDimension size;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, sizeArg, size, false)) || (size.Unit() == DimensionUnit::PERCENT) ||
        (size.ConvertToVp() < 0)) {
        size = Dimension(CHECK_BOX_MARK_SIZE_INVALID_VALUE);
    }

    CalcDimension strokeWidth;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, widthArg, strokeWidth, false)) ||
        (strokeWidth.Unit() == DimensionUnit::PERCENT) || (strokeWidth.ConvertToVp() < 0)) {
        strokeWidth = theme->GetCheckStroke();
    }

    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetMark(
        nativeNode, strokeColor.GetValue(), size.Value(), strokeWidth.Value());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> selectedArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    bool select = DEFAULT_SELECTED;
    if (selectedArg->IsBoolean()) {
        select = selectedArg->ToBoolean(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetSelect(nativeNode, select);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    Color selectedColor;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, selectedColor)) {
        GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetSelectedColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetSelectedColor(nativeNode, selectedColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetUnSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    Color unSelectedColor;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, unSelectedColor)) {
        GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetUnSelectedColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetUnSelectedColor(nativeNode, unSelectedColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetCheckboxWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    CalcDimension width;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, width)) {
        GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetCheckboxWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetCheckboxWidth(
        nativeNode, width.Value(), static_cast<int>(width.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetCheckboxHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, height)) {
        GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetCheckboxHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetCheckboxHeight(
        nativeNode, height.Value(), static_cast<int>(height.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetMark(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxModifier().SetSelect(nativeNode, DEFAULT_SELECTED);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetUnSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetUnSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetCheckboxWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetCheckboxWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetCheckboxHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCheckboxModifier().ResetCheckboxHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
