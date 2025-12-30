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
#include "frameworks/core/components_ng/pattern/qrcode/bridge/arkts_native_qrcode_bridge.h"

#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_qrcode_theme.h"

namespace OHOS::Ace::NG {

bool IsJsView(const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    return firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
}

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (firstArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        nativeNode = nullptr;
        return true;
    }

    return false;
}

void QRCodeBridge::RegisterQRCodeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setQRColor", "resetQRColor", "setQRBackgroundColor",
        "resetQRBackgroundColor", "setContentOpacity", "resetContentOpacity", "setQRValue" };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), QRCodeBridge::CreateQRCode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), QRCodeBridge::SetQRColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), QRCodeBridge::ResetQRColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), QRCodeBridge::SetQRBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), QRCodeBridge::ResetQRBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), QRCodeBridge::SetContentOpacity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), QRCodeBridge::ResetContentOpacity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), QRCodeBridge::SetQRValue),
    };
    auto qrcode = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "qrcode"), qrcode);
}

ArkUINativeModuleValue QRCodeBridge::CreateQRCode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> value = runtimeCallInfo->GetCallArgRef(0);
    static QRCodeModelNG model;

    std::string qrValue;
    RefPtr<ResourceObject> resObj;
    if (value->IsNumber()) {
        qrValue = std::to_string(static_cast<int32_t>(value->ToNumber(vm)->Value()));
    } else if (value->IsNull()) {
        qrValue = "null";
    } else if (value->IsUndefined()) {
        qrValue = "undefined";
    } else {
        ArkTSUtils::ParseJsString(vm, value, qrValue, resObj);
    }
    GetArkUINodeModifiers()->getQRCodeModifier()->createModel(qrValue.c_str());
    Framework::JSQRCodeTheme::ApplyTheme();
    if (SystemProperties::ConfigChangePerform()) {
        model.CreateWithResourceObj(QRCodeResourceType::CREATE, resObj);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue QRCodeBridge::SetQRColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> qrColorArg = runtimeCallInfo->GetCallArgRef(1);
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);

    auto themeColors = Framework::JSThemeUtils::GetThemeColors();

    if (!ArkTSUtils::ParseJsColorAlpha(vm, qrColorArg, color, colorResObj, nodeInfo) &&
        (IsJsView(firstArg, vm) || !Framework::JSQRCodeTheme::ObtainQRCodeColor(color))) {
        GetArkUINodeModifiers()->getQRCodeModifier()->resetQRColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getQRCodeModifier()->setQRColorPtr(nativeNode, color.GetValue(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue QRCodeBridge::ResetQRColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getQRCodeModifier()->resetQRColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue QRCodeBridge::SetQRBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> qrBackgroundColor = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    auto isJsView = IsJsView(firstArg, vm);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, qrBackgroundColor, color, colorResObj, nodeInfo) &&
        (isJsView || !Framework::JSQRCodeTheme::ObtainBackgroundColor(color))) {
        GetArkUINodeModifiers()->getQRCodeModifier()->resetQRBackgroundColor(nativeNode, isJsView);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getQRCodeModifier()->setQRBackgroundColorPtr(
            nativeNode, color.GetValue(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue QRCodeBridge::ResetQRBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto isJsView = IsJsView(firstArg, vm);
    GetArkUINodeModifiers()->getQRCodeModifier()->resetQRBackgroundColor(nativeNode, isJsView);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue QRCodeBridge::SetContentOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> qrContentOpacity = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    double opacity;
    RefPtr<ResourceObject> opacityResObj;
    if (!ArkTSUtils::ParseJsDouble(vm, qrContentOpacity, opacity, opacityResObj)) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getQRCodeModifier()->resetContentOpacity,
            panda::NativePointerRef::New(vm, nullptr));
        GetArkUINodeModifiers()->getQRCodeModifier()->resetContentOpacity(nativeNode);
    } else {
        auto opacityRawPtr = AceType::RawPtr(opacityResObj);
        CHECK_NULL_RETURN(
            GetArkUINodeModifiers()->getQRCodeModifier()->setContentOpacityPtr, panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getQRCodeModifier()->setContentOpacityPtr(
            nativeNode, static_cast<ArkUI_Float32>(opacity), opacityRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue QRCodeBridge::ResetContentOpacity(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(
        GetArkUINodeModifiers()->getQRCodeModifier()->resetContentOpacity, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getQRCodeModifier()->resetContentOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue QRCodeBridge::SetQRValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> value = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(
        GetArkUINodeModifiers()->getQRCodeModifier()->setQRValue, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getQRCodeModifier()->setQRValue(nativeNode, value->ToString(vm)->ToString(vm).c_str());
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
