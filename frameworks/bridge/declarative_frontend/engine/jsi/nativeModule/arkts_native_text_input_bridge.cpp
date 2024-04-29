/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_input_bridge.h"

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include <string>
#include "jsnapi_expo.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textfield.h"
namespace OHOS::Ace::NG {
constexpr int16_t DEFAULT_ALPHA = 255;
constexpr double DEFAULT_OPACITY = 0.2;
constexpr double DEFAULT_FONT_SIZE = 16.0;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::string DEFAULT_FONT_WEIGHT = "400";
constexpr int CALL_ARG_0 = 0;
constexpr int CALL_ARG_1 = 1;
constexpr int CALL_ARG_2 = 2;
constexpr int CALL_ARG_3 = 3;
constexpr int CALL_ARG_4 = 4;
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr int PARAM_ARR_LENGTH_2 = 2;
constexpr int32_t ARG_GROUP_LENGTH = 4;
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr uint32_t ILLEGAL_VALUE = 0;
constexpr uint32_t DEFAULT_MODE = -1;
const int32_t MINI_VALID_VALUE = 1;
const int32_t MAX_VALID_VALUE = 100;
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };

ArkUINativeModuleValue TextInputBridge::SetCaretColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCaretColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCaretColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetCaretColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCaretColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputType(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputType(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        uint32_t value = secondArg->Uint32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputMaxLines(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxLines(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxLines(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetPlaceholderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPlaceholderColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetPlaceholderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetCaretPosition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsInt() && secondArg->Int32Value(vm) >= 0) {
        int32_t caretPosition = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCaretPosition(nativeNode, caretPosition);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCaretPosition(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetCaretPosition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCaretPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetCopyOption(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t option = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCopyOption(nativeNode, option);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCopyOption(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetCopyOption(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetShowPasswordIcon(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowPasswordIcon(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowPasswordIcon(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetShowPasswordIcon(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowPasswordIcon(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetShowPassword(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowPassword(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowPassword(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetShowPassword(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowPassword(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetPasswordIcon(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    PasswordIcon passwordIcon;
    struct ArkUIPasswordIconType value = {"", "", "", "", "", ""};
    if (!ArkTSUtils::GetJsPasswordIcon(vm, secondArg, thirdArg, passwordIcon)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPasswordIcon(nativeNode);
    } else {
        value.showResult = passwordIcon.showResult.c_str();
        value.hideResult = passwordIcon.hideResult.c_str();
        value.showBundleName = passwordIcon.showBundleName.c_str();
        value.showModuleName = passwordIcon.showModuleName.c_str();
        value.hideBundleName = passwordIcon.hideBundleName.c_str();
        value.hideModuleName = passwordIcon.hideModuleName.c_str();
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPasswordIcon(nativeNode, &value);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetPasswordIcon(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPasswordIcon(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextAlign(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputTextAlign(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputTextAlign(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextAlign(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputTextAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString() && secondArg->ToString(vm)->ToString() == "Inline") {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputStyle(nativeNode,
            static_cast<int32_t>(InputStyle::INLINE));
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetSelectionMenuHidden(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsBoolean()) {
        uint32_t menuHiddenValue = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputSelectionMenuHidden(nativeNode, menuHiddenValue);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectionMenuHidden(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetSelectionMenuHidden(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectionMenuHidden(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextInputShowUnderline(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsBoolean()) {
        uint32_t showUnderLine = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowUnderline(nativeNode, showUnderLine);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowUnderline(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextInputShowUnderline(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowUnderline(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetPasswordRules(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString()) {
        auto value = secondArg->ToString(vm)->ToString();
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPasswordRules(nativeNode, value.c_str());
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPasswordRules(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetPasswordRules(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPasswordRules(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetEnableAutoFill(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsBoolean()) {
        uint32_t enableAutoFill = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputEnableAutoFill(nativeNode, enableAutoFill);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnableAutoFill(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetEnableAutoFill(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnableAutoFill(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetCaretStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> caretWidthArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> caretColorArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto textFieldTheme = ArkTSUtils::GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, panda::JSValueRef::Undefined(vm));
    CalcDimension caretWidth = textFieldTheme->GetCursorWidth();
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, caretWidthArg, caretWidth, false) ||
            LessNotEqual(caretWidth.Value(), 0.0)) {
        caretWidth = textFieldTheme->GetCursorWidth();
    }
    Color color;
    uint32_t caretColor;
    if (ArkTSUtils::ParseJsColorAlpha(vm, caretColorArg, color)) {
        caretColor = color.GetValue();
    } else {
        caretColor = textFieldTheme->GetCursorColor().GetValue();
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCaretStyle(
        nativeNode, caretWidth.Value(), static_cast<int8_t>(caretWidth.Unit()), caretColor);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetCaretStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCaretStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputEnableKeyboardOnFocus(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowPasswordIcon(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnableKeyboardOnFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputBarState(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputBarState(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputBarState(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextInputEnterKeyType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputEnterKeyType(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnterKeyType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextInputEnterKeyType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnterKeyType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextInputFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string weight;
    if (secondArg->IsString()) {
        weight = secondArg->ToString(vm)->ToString();
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontWeightStr(nativeNode, weight.c_str());
    } else if (secondArg->IsNumber()) {
        weight = std::to_string(secondArg->Int32Value(vm));
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontWeightStr(nativeNode, weight.c_str());
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontWeight(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextInputFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    CalcDimension fontSize;
    ArkUILengthType value{ nullptr, 0.0, static_cast<int8_t>(DimensionUnit::FP) };
    if (!ArkTSUtils::ParseJsDimensionNG(vm, secondArg, fontSize, DimensionUnit::FP, false)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontSize(nativeNode);
    } else {
        value.unit = static_cast<int8_t>(fontSize.Unit());
        if (fontSize.CalcValue() != "") {
            value.string = fontSize.CalcValue().c_str();
        } else {
            value.number = fontSize.Value();
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontSize(nativeNode, &value);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxLength(nativeNode);
    } else {
        uint32_t maxLength = secondArg->Uint32Value(vm);
        if (GreatOrEqual(maxLength, 0)) {
            GetArkUINodeModifiers()->getTextInputModifier()->setTextInputMaxLength(nativeNode, maxLength);
        } else {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxLength(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetSelectedBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectedBackgroundColor(nativeNode);
    } else {
        if (color.GetAlpha() == DEFAULT_ALPHA) {
            color = color.ChangeOpacity(DEFAULT_OPACITY);
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputSelectedBackgroundColor(
            nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectedBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetShowError(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool visible;
    std::string error = "";
    if (secondArg->IsString()) {
        visible = true;
        error = secondArg->ToString(vm)->ToString();
    } else {
        visible = false;
    }

    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowError(nativeNode, error.c_str(),
        static_cast<uint32_t>(visible));

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetShowError(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowError(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetPlaceholderFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> jsSize = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> jsWeight = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> jsFamily = runtimeCallInfo->GetCallArgRef(3);
    Local<JSValueRef> jsStyle = runtimeCallInfo->GetCallArgRef(4);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ArkUILengthType length{ nullptr, DEFAULT_FONT_SIZE, static_cast<int8_t>(DimensionUnit::FP) };
    CalcDimension size(DEFAULT_FONT_SIZE, DimensionUnit::FP);
    if (!ArkTSUtils::ParseJsDimensionFp(vm, jsSize, size) || size.Unit() == DimensionUnit::PERCENT) {
        auto theme = ArkTSUtils::GetTheme<TextFieldTheme>();
        if (theme != nullptr) {
            size = theme->GetFontSize();
        }
    }
    length.unit = static_cast<int8_t>(size.Unit());
    if (size.CalcValue() != "") {
        length.string = size.CalcValue().c_str();
    } else {
        length.number = size.Value();
    }
    
    std::string weight = DEFAULT_FONT_WEIGHT;
    if (!jsWeight->IsNull()) {
        if (jsWeight->IsString()) {
            weight = jsWeight->ToString(vm)->ToString();
        }
        if (jsWeight->IsNumber()) {
            weight = std::to_string(jsWeight->Int32Value(vm));
        }
    }

    int32_t style = static_cast<int32_t>(DEFAULT_FONT_STYLE);
    if (jsStyle->IsNumber()) {
        style = jsStyle->ToNumber(vm)->Value();
    }

    struct ArkUIPlaceholderFontType placeholderFont;
    placeholderFont.size = &length;
    placeholderFont.weight = weight.c_str();
    placeholderFont.style = style;
    std::vector<std::string> fontFamilies;
    bool isSuccess = !ArkTSUtils::ParseJsFontFamilies(vm, jsFamily, fontFamilies);
    auto families = std::make_unique<char* []>(fontFamilies.size());
    if (isSuccess) {
        placeholderFont.fontFamilies = nullptr;
        placeholderFont.length = 0;
    } else {
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            families[i] = const_cast<char*>(fontFamilies.at(i).c_str());
        }
        placeholderFont.fontFamilies = const_cast<const char**>(families.get());
        placeholderFont.length = fontFamilies.size();
    }
    
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPlaceholderFont(
        nativeNode, &placeholderFont);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetPlaceholderFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        uint32_t fontStyle = secondArg->Uint32Value(vm);
        if (fontStyle < static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL) ||
            fontStyle > static_cast<uint32_t>(OHOS::Ace::FontStyle::ITALIC)) {
            fontStyle = static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL);
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontStyle(nativeNode, fontStyle);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::vector<std::string> fontFamilies;
    if (!ArkTSUtils::ParseJsFontFamilies(vm, secondArg, fontFamilies)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontFamily(nativeNode);
    } else {
        auto families = std::make_unique<char* []>(fontFamilies.size());
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            families[i] = const_cast<char*>(fontFamilies.at(i).c_str());
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontFamily(nativeNode,
            const_cast<const char**>(families.get()), fontFamilies.size());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetUnderlineColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> underlineColorArg = runtimeCallInfo->GetCallArgRef(1);  // 1: underlineColor value
    Local<JSValueRef> normalArg = runtimeCallInfo->GetCallArgRef(2);  // 2: normal value
    Local<JSValueRef> typingArg = runtimeCallInfo->GetCallArgRef(3);   // 3: typing value
    Local<JSValueRef> errorArg = runtimeCallInfo->GetCallArgRef(4); // 4: error value
    Local<JSValueRef> disableArg = runtimeCallInfo->GetCallArgRef(5); // 5: disable value
    
    Color underlineColor;
    if (!underlineColorArg->IsUndefined() && ArkTSUtils::ParseJsColorAlpha(vm, underlineColorArg, underlineColor)) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputNormalUnderlineColor(
            nativeNode, underlineColor.GetValue());
    } else if (!normalArg->IsUndefined() || !typingArg->IsUndefined() ||
         !errorArg->IsUndefined() || !disableArg->IsUndefined()) {
        UserUnderlineColor userColor = UserUnderlineColor();
        Color typingColor;
        if (ArkTSUtils::ParseJsColorAlpha(vm, typingArg, typingColor)) {
            userColor.typing = typingColor;
        }
        Color normalColor;
        if (ArkTSUtils::ParseJsColorAlpha(vm, normalArg, normalColor)) {
            userColor.normal = normalColor;
        }
        Color errorColor;
        if (ArkTSUtils::ParseJsColorAlpha(vm, errorArg, errorColor)) {
            userColor.error = errorColor;
        }
        Color disableColor;
        if (ArkTSUtils::ParseJsColorAlpha(vm, disableArg, disableColor)) {
            userColor.disable = disableColor;
        }
        uint32_t size = ARG_GROUP_LENGTH;
        ArkUI_Uint32 values[size];
        values[CALL_ARG_0] = userColor.typing->GetValue();
        values[CALL_ARG_1] = userColor.normal->GetValue();
        values[CALL_ARG_2] = userColor.error->GetValue();
        values[CALL_ARG_3] = userColor.disable->GetValue();
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputUserUnderlineColor(nativeNode, values, size);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputUserUnderlineColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1); // 1: textInputDecoration value
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);  // 2: color value
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    Color color = theme->GetTextStyle().GetTextDecorationColor();
    int32_t textInputDecoration = static_cast<int32_t>(theme->GetTextStyle().GetTextDecoration());
    if (secondArg->IsInt()) {
        textInputDecoration = secondArg->Int32Value(vm);
    }
    ArkTSUtils::ParseJsColorAlpha(vm, thirdArg, color, Color::BLACK);
    int32_t textDecorationStyle = static_cast<int32_t>(DEFAULT_DECORATION_STYLE);
    if (fourthArg->IsInt()) {
        textDecorationStyle = fourthArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputDecoration(
        nativeNode, textInputDecoration, color.GetValue(), textDecorationStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputDecoration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension value;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, false)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLetterSpacing(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputLetterSpacing(
            nativeNode, value.Value(), static_cast<int>(value.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetUnderlineColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputUserUnderlineColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLetterSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension value;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, true)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLineHeight(nativeNode);
    } else {
        if (value.IsNegative()) {
            value.Reset();
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputLineHeight(
            nativeNode, value.Value(), static_cast<int>(value.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension value;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::NativePointerRef::New(vm, nullptr));
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, panda::NativePointerRef::New(vm, nullptr));
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, false)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputAdaptMinFontSize(nativeNode);
    } else {
        if (value.IsNegative()) {
            value = theme->GetTextStyle().GetAdaptMinFontSize();
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputAdaptMinFontSize(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputAdaptMinFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension value;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::NativePointerRef::New(vm, nullptr));
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, panda::NativePointerRef::New(vm, nullptr));
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, false)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputAdaptMaxFontSize(nativeNode);
    } else {
        if (value.IsNegative()) {
            value = theme->GetTextStyle().GetAdaptMaxFontSize();
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputAdaptMaxFontSize(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLineHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString()) {
        auto value = secondArg->ToString(vm)->ToString();
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontFeature(nativeNode, value.c_str());
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontFeature(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontFeature(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetWordBreak(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> workBreakArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (workBreakArg->IsNull() || workBreakArg->IsUndefined() || !workBreakArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputWordBreak(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t wordBreak = workBreakArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputWordBreak(nativeNode, wordBreak);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetWordBreak(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputWordBreak(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetLineBreakStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> lineBreakStrategyArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (lineBreakStrategyArg->IsNull() || lineBreakStrategyArg->IsUndefined() || !lineBreakStrategyArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLineBreakStrategy(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t lineBreakStrategy = lineBreakStrategyArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputLineBreakStrategy(nativeNode, lineBreakStrategy);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetLineBreakStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLineBreakStrategy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputAdaptMaxFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetHeightAdaptivePolicy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    int32_t value = valueArg->ToNumber(vm)->Value();
    if (value < 0 || value >= static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICY.size())) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputHeightAdaptivePolicy(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetHeightAdaptivePolicy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputHeightAdaptivePolicy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t value;
    if (secondArg->IsUndefined()) {
        value = 0;
    } else if (secondArg->IsNumber()) {
        value = secondArg->Int32Value(vm);
    } else {
        return panda::JSValueRef::Undefined(vm);
    }
    if (value < 0 || value >= static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputTextOverflow(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputTextOverflow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension indent;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, secondArg, indent, DimensionUnit::VP, true)) {
        indent.Reset();
    }
    
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputTextIndent(
        nativeNode, indent.Value(), static_cast<int8_t>(indent.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputTextIndent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

static CancelButtonStyle ConvertStrToCancelButtonStyle(const std::string& value)
{
    if (value == "CONSTANT") {
        return CancelButtonStyle::CONSTANT;
    } else if (value == "INVISIBLE") {
        return CancelButtonStyle::INVISIBLE;
    } else {
        return CancelButtonStyle::INPUT;
    }
}

ArkUINativeModuleValue TextInputBridge::SetCancelButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    Local<JSValueRef> srcArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_4);

    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));

    int32_t style = static_cast<int32_t>(theme->GetCancelButtonStyle());
    if (styleArg->IsString()) {
        CancelButtonStyle cancelButtonStyle = ConvertStrToCancelButtonStyle(styleArg->ToString(vm)->ToString());
        style = static_cast<int32_t>(cancelButtonStyle);
    }

    CalcDimension iconSize;
    if (!sizeArg->IsUndefined() && !sizeArg->IsNull() &&
        ArkTSUtils::ParseJsDimensionVpNG(vm, sizeArg, iconSize, false)) {
        if (LessNotEqual(iconSize.Value(), 0.0) || iconSize.Unit() == DimensionUnit::PERCENT) {
            iconSize = theme->GetCancelButtonIconHeight();
        }
    } else {
        iconSize = theme->GetCancelButtonIconHeight();
    }

    Color value;
    uint32_t color;
    if (!colorArg->IsUndefined() && !colorArg->IsNull() &&
        ArkTSUtils::ParseJsColorAlpha(vm, colorArg, value)) {
        color = value.GetValue();
    } else {
        color = theme->GetCancelButtonIconColor().GetValue();
    }

    std::string srcStr;
    if (srcArg->IsUndefined() || srcArg->IsNull() ||
        !ArkTSUtils::ParseJsMedia(vm, srcArg, srcStr)) {
        srcStr = "";
    }

    struct ArkUISizeType size = {iconSize.Value(), static_cast<int8_t>(iconSize.Unit())};
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCancelButton(nativeNode,
        style, &size, color, srcStr.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetCancelButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCancelButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetSelectAll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        uint32_t enableSelectAll = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputSelectAll(nativeNode, enableSelectAll);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectAll(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetSelectAll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectAll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetShowCounter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> showCounterArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> highlightBorderArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    Local<JSValueRef> thresholdArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto showCounter = false;
    if (showCounterArg->IsBoolean()) {
        showCounter = showCounterArg->BooleaValue();
    }
    auto highlightBorder = true;
    if (highlightBorderArg->IsBoolean()) {
        highlightBorder = highlightBorderArg->BooleaValue();
    }
    auto thresholdValue = DEFAULT_MODE;
    if (thresholdArg->IsNumber()) {
        thresholdValue = thresholdArg->Int32Value(vm);
        if (thresholdValue < MINI_VALID_VALUE || thresholdValue > MAX_VALID_VALUE) {
            thresholdValue = ILLEGAL_VALUE;
            showCounter = false;
        }
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowCounter(
        nativeNode, static_cast<uint32_t>(showCounter), thresholdValue, static_cast<uint32_t>(highlightBorder));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetShowCounter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowCounter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnEditChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnEditChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](bool isInEditStatus) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::BooleanRef::New(vm, isInEditStatus) };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnEditChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnEditChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnEditChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetInputFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> inputFilterArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> errorCallbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (inputFilterArg->IsUndefined() || inputFilterArg->IsNull() || !inputFilterArg->IsString()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFilter(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string inputFilter = inputFilterArg->ToString(vm)->ToString();
    if (errorCallbackArg->IsUndefined() || errorCallbackArg->IsNull() ||
        !errorCallbackArg->IsFunction()) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFilter(nativeNode, inputFilter.c_str(), nullptr);
    } else {
        panda::Local<panda::FunctionRef> func = errorCallbackArg->ToObject(vm);
        std::function<void(const std::string&)> callback = [vm, frameNode,
            func = panda::CopyableGlobal(vm, func)](const std::string& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
                panda::StringRef::NewFromUtf8(vm, info.c_str()) };
            func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        };
        GetArkUINodeModifiers()->getTextInputModifier()->
            setTextInputFilter(nativeNode, inputFilter.c_str(), reinterpret_cast<void*>(&callback));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetInputFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFilter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnSubmitWithEvent(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, NG::TextFieldCommonEvent&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](int32_t key, NG::TextFieldCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto eventObject = panda::ObjectRef::New(vm);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "text"),
            panda::StringRef::NewFromUtf8(vm, event.GetText().c_str()));
        eventObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "keepEditableState"),
            panda::FunctionRef::New(vm, Framework::JSTextField::JsKeepEditableState));
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = {
            panda::IntegerRef::New(vm, key), eventObject };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnSubmitWithEvent(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnSubmitWithEvent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::string&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](const std::string& changeValue) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::StringRef::NewFromUtf8(vm, changeValue.c_str()) };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnTextSelectionChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](int32_t selectionStart, int selectionEnd) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> startParam = panda::NumberRef::New(vm, selectionStart);
        panda::Local<panda::NumberRef> endParam = panda::NumberRef::New(vm, selectionEnd);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = { startParam, endParam };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnTextSelectionChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnTextSelectionChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnContentScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnContentScroll(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(float, float)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](float totalOffsetX, float totalOffsetY) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = {
            panda::NumberRef::New(vm, totalOffsetX), panda::NumberRef::New(vm, totalOffsetY) };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnContentScroll(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnContentScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnContentScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnCopy(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::string&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](const std::string& copyStr) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::StringRef::NewFromUtf8(vm, copyStr.c_str()) };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnCopy(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnCut(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::string&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](const std::string& cutStr) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::StringRef::NewFromUtf8(vm, cutStr.c_str()) };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnCut(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnCut(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnPaste(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::string&, NG::TextCommonEvent&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](const std::string& val, NG::TextCommonEvent& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto eventObject = panda::ObjectRef::New(vm);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "preventDefault"),
            panda::FunctionRef::New(vm, Framework::JsPreventDefault));
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&info));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = {
            panda::StringRef::NewFromUtf8(vm, val.c_str()), eventObject };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnPaste(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnPaste(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetPadding(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_4);

    struct ArkUISizeType top = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };
    struct ArkUISizeType right = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };
    struct ArkUISizeType bottom = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };
    struct ArkUISizeType left = { 0.0, static_cast<int8_t>(DimensionUnit::VP) };

    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension rightDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension leftDimen(0, DimensionUnit::VP);
    
    ArkTSUtils::ParsePadding(vm, secondArg, topDimen, top);
    ArkTSUtils::ParsePadding(vm, thirdArg, rightDimen, right);
    ArkTSUtils::ParsePadding(vm, forthArg, bottomDimen, bottom);
    ArkTSUtils::ParsePadding(vm, fifthArg, leftDimen, left);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPadding(nativeNode, &top, &right, &bottom, &left);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}