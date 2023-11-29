/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_area_bridge.h"

#include "bridge/common/utils/utils.h"
#include "core/components/common/properties/text_style.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr uint32_t KEY_BOARD_FOCUS_DEFAULT = 1;
constexpr uint32_t SHOW_COUNTER_DEFAULT = 0;

ArkUINativeModuleValue TextAreaBridge::SetStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto str = secondArg->ToString(vm)->ToString();
    if (str == "Inline") {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaStyle(nativeNode,
            static_cast<int32_t>(InputStyle::INLINE));
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaStyle(nativeNode,
            static_cast<int32_t>(InputStyle::DEFAULT));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetSelectionMenuHidden(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t contextMenuHidden = 0;
    if (secondArg->IsBoolean()) {
        contextMenuHidden = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaSelectionMenuHidden(nativeNode, contextMenuHidden);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetSelectionMenuHidden(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaSelectionMenuHidden(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) > 0) {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaMaxLines(nativeNode, secondArg->Uint32Value(vm));
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaMaxLines(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaMaxLines(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetCopyOption(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaCopyOption(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaCopyOption(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetCopyOption(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetPlaceholderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    struct ArkUIResourceColorType colortype = { 0, nullptr };
    std::string colorStr;
    if (!secondArg->IsNumber() && !secondArg->IsString()) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        if (secondArg->IsString()) {
            colorStr = secondArg->ToString(vm)->ToString();
            colortype.string = colorStr.c_str();
        } else {
            colortype.number = secondArg->Uint32Value(vm);
        }
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaPlaceholderColor(nativeNode, &colortype);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetPlaceholderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaPlaceholderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetTextAreaTextAlign(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= 0) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaTextAlign(nativeNode, value);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetTextAreaTextAlign(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaTextAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetPlaceholderFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontSzie = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontWeight = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontFamily = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontStyle = runtimeCallInfo->GetCallArgRef(NUM_4);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    struct StringAndDouble size = { 0.0, nullptr };
    std::string valueSize;
    if (fontSzie->IsNumber()) {
        size.value = fontSzie->ToNumber(vm)->Value();
    } else if (fontSzie->IsString()) {
        valueSize = fontSzie->ToString(vm)->ToString();
        size.valueStr = valueSize.c_str();
    }

    struct ArkUIFontWeight weight = { 0, nullptr };
    std::string valueWeight;
    if (fontWeight->IsNumber()) {
        weight.value = fontWeight->ToNumber(vm)->Value();
    } else if (fontWeight->IsString()) {
        valueWeight = fontWeight->ToString(vm)->ToString();
        weight.valueStr = valueWeight.c_str();
    }
    std::string family;
    if (fontFamily->IsString()) {
        family = fontFamily->ToString(vm)->ToString();
    }
    int32_t style = -1;
    if (fontStyle->IsNumber()) {
        style = fontStyle->ToNumber(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaPlaceholderFont(nativeNode, &size, &weight,
        family.c_str(), style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetPlaceholderFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaPlaceholderFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNumber()) {
        uint32_t barStateValue = secondArg->Uint32Value(vm);
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaBarState(nativeNode, barStateValue);
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaBarState(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaBarState(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t keyboardOnFocusValue = KEY_BOARD_FOCUS_DEFAULT;
    if (secondArg->IsBoolean()) {
        keyboardOnFocusValue = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaEnableKeyboardOnFocus(nativeNode, keyboardOnFocusValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaEnableKeyboardOnFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    std::string fontFamily;
    if (secondArg->IsString()) {
        fontFamily = secondArg->ToString(vm)->ToString();
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaFontFamily(nativeNode, fontFamily.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetShowCounter(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t value = SHOW_COUNTER_DEFAULT;
    if (secondArg->IsBoolean()) {
        value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaShowCounter(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetShowCounter(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaShowCounter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetCaretColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    struct ArkUIResourceColorType colortype = { 0, nullptr };
    std::string colorStr;
    if (!secondArg->IsNumber() && !secondArg->IsString()) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        if (secondArg->IsString()) {
            colorStr = secondArg->ToString(vm)->ToString();
            colortype.string = colorStr.c_str();
        } else {
            colortype.number = secondArg->Uint32Value(vm);
        }
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaCaretColor(nativeNode, &colortype);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetCaretColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaCaretColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t value;
    if (secondArg->IsNumber()) {
        value = secondArg->Int32Value(vm);
    } else {
        value = 0;
    }
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaMaxLength(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaMaxLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    struct ArkUIResourceColorType colortype = { 0, nullptr };
    std::string colorStr;
    if (!secondArg->IsNumber() && !secondArg->IsString()) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        if (secondArg->IsString()) {
            colorStr = secondArg->ToString(vm)->ToString();
            colortype.string = colorStr.c_str();
        } else {
            colortype.number = secondArg->Uint32Value(vm);
        }
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaFontColor(nativeNode, &colortype);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (secondArg->IsNumber()) {
        uint32_t fontStyle = secondArg->Uint32Value(vm);
        if (fontStyle < static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL) ||
            fontStyle > static_cast<uint32_t>(OHOS::Ace::FontStyle::ITALIC)) {
            fontStyle = static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL);
        }
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaFontStyle(nativeNode, fontStyle);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t fontWeight = static_cast<uint32_t>(FontWeight::NORMAL);
    if (secondArg->IsString()) {
        fontWeight = static_cast<uint32_t>(Framework::ConvertStrToFontWeight(secondArg->ToString(vm)->ToString()));
    } else if (secondArg->IsInt()) {
        fontWeight = secondArg->Uint32Value(vm);
    }
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaFontWeight(nativeNode, fontWeight);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    struct StringAndDouble size = { 0.0, nullptr };
    std::string value;
    if (!secondArg->IsNull() && !secondArg->IsUndefined()) {
        if (secondArg->IsNumber()) {
            size.value = secondArg->ToNumber(vm)->Value();
        } else if (secondArg->IsString()) {
            value = secondArg->ToString(vm)->ToString();
            size.valueStr = value.c_str();
        }
    } else {
        size.value = -1;
    }
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaFontSize(nativeNode, &size);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
