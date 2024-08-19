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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_panel_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue PanelBridge::SetPanelBackgroundMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelBackgroundMask(nativeNode);
    } else {
        GetArkUINodeModifiers()->getPanelModifier()->setPanelBackgroundMask(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelBackgroundMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelBackgroundMask(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (modeArg->IsNumber()) {
        int32_t mode = modeArg->Int32Value(vm);
        GetArkUINodeModifiers()->getPanelModifier()->setPanelMode(nativeNode, mode);
    } else {
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (typeArg->IsNumber()) {
        int32_t type = typeArg->Int32Value(vm);
        GetArkUINodeModifiers()->getPanelModifier()->setPanelType(nativeNode, type);
    } else {
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelFullHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelFullHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelFullHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension height;

    if (jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height, true)) {
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelFullHeight(nativeNode);
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getPanelModifier()->setPanelFullHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelHalfHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelHalfHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelHalfHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension height;

    if (jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height, true)) {
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelHalfHeight(nativeNode);
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getPanelModifier()->setPanelHalfHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelMiniHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelMiniHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelMiniHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension height;

    if (jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height, true)) {
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelMiniHeight(nativeNode);
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getPanelModifier()->setPanelMiniHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetPanelCustomHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension customHeight;

    if (jsValue->IsUndefined()) {
        GetArkUINodeModifiers()->getPanelModifier()->resetPanelCustomHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (jsValue->IsString(vm) && jsValue->ToString(vm)->ToString(vm).find("wrapContent") != std::string::npos) {
        GetArkUINodeModifiers()->getPanelModifier()->setPanelCustomHeightByString(
            nativeNode, jsValue->ToString(vm)->ToString(vm).c_str());
        return panda::JSValueRef::Undefined(vm);
    } else if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, customHeight)) {
        customHeight = Dimension(0.0);
    }
    GetArkUINodeModifiers()->getPanelModifier()->setPanelCustomHeight(
        nativeNode, customHeight.Value(), static_cast<int>(customHeight.Unit()));

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetPanelCustomHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetPanelCustomHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetShowCloseIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> showCloseArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (showCloseArg->IsNull()) {
        GetArkUINodeModifiers()->getPanelModifier()->resetShowCloseIcon(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool boolValue = false;
    if (showCloseArg->IsBoolean()) {
        boolValue = showCloseArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getPanelModifier()->setShowCloseIcon(nativeNode, boolValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetShowCloseIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetShowCloseIcon(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetDragBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> dragBarArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (dragBarArg->IsNull()) {
        GetArkUINodeModifiers()->getPanelModifier()->resetDragBar(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool boolValue = true;
    if (dragBarArg->IsBoolean()) {
        boolValue = dragBarArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getPanelModifier()->setDragBar(nativeNode, boolValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::ResetDragBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetDragBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PanelBridge::SetShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> showArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) &&
        (showArg->IsUndefined() || showArg->IsNull())) {
        GetArkUINodeModifiers()->getPanelModifier()->setShow(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    } else {
        bool boolValue = true;
        if (showArg->IsBoolean()) {
            boolValue = showArg->ToBoolean(vm)->Value();
        }
        GetArkUINodeModifiers()->getPanelModifier()->setShow(nativeNode, boolValue);
        return panda::JSValueRef::Undefined(vm);
    }
}

ArkUINativeModuleValue PanelBridge::ResetShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPanelModifier()->resetShow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG