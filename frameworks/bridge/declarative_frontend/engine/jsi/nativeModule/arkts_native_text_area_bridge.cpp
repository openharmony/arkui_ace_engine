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
#include "core/interfaces/native/node/api.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr uint32_t KEY_BOARD_FOCUS_DEFAULT = 1;
constexpr uint32_t SHOW_COUNTER_DEFAULT = 0;
const int32_t MINI_VAILD_VALUE = 1;
const int32_t MAX_VAILD_VALUE = 100;
const std::string DEFAULT_FONT_WEIGHT = "400";
const std::vector<OHOS::Ace::TextAlign> TEXT_ALIGNS = { OHOS::Ace::TextAlign::START, OHOS::Ace::TextAlign::CENTER,
    OHOS::Ace::TextAlign::END, OHOS::Ace::TextAlign::JUSTIFY };
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };

ArkUINativeModuleValue TextAreaBridge::SetStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsString()) {
        auto str = secondArg->ToString(vm)->ToString();
        if (str == "Inline") {
            GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaStyle(nativeNode,
                static_cast<int32_t>(InputStyle::INLINE));
        } else {
            GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaStyle(nativeNode,
                static_cast<int32_t>(InputStyle::DEFAULT));
        }
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaStyle(nativeNode);
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
    int32_t copyOptions = static_cast<int32_t>(OHOS::Ace::CopyOptions::None);
    int32_t copyOptionsDistributed = static_cast<int32_t>(OHOS::Ace::CopyOptions::Distributed);
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= copyOptions &&
        secondArg->Int32Value(vm) <= copyOptionsDistributed) {
        copyOptions = secondArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaCopyOption(nativeNode, copyOptions);
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
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaPlaceholderColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaPlaceholderColor(nativeNode, color.GetValue());
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
    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
            GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaTextAlign(nativeNode, value);
        } else {
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaTextAlign(nativeNode);
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
    Local<JSValueRef> fontSzieArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    struct ArkUIResourceLength fontSize = { 0.0, -1, nullptr };
    CalcDimension size;
    std::string calcStr;
    if (ArkTSUtils::ParseJsDimensionNG(vm, fontSzieArg, size, DimensionUnit::FP, false)) {
        if (size.Unit() == DimensionUnit::CALC) {
            fontSize.Uint = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            fontSize.string = calcStr.c_str();
        } else {
            fontSize.value = size.Value();
            fontSize.Uint = static_cast<int32_t>(size.Unit());
            fontSize.string = calcStr.c_str();
        }
    }
    std::string fontWeight;
    if (!fontWeightArg->IsNull()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else if (fontWeightArg->IsString()) {
            fontWeight = fontWeightArg->ToString(vm)->ToString();
        }
    }
    std::vector<std::string> fontFamilies;
    std::string family;
    if (ArkTSUtils::ParseJsFontFamilies(vm, fontFamilyArg, fontFamilies)) {
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            family += fontFamilies.at(i);
            family += ',';
        }
        family.pop_back();
    }
    int32_t style = -1;
    if (fontStyleArg->IsNumber()) {
        style = fontStyleArg->Int32Value(vm);
        if (style <= 0 || style > static_cast<int32_t>(FONT_STYLES.size())) {
            style = -1;
        }
    }
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaPlaceholderFont(nativeNode, &fontSize,
        fontWeight.c_str(), family.c_str(), style);
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
    std::vector<std::string> fontFamilies;
    if (!ArkTSUtils::ParseJsFontFamilies(vm, secondArg, fontFamilies)) {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaFontFamily(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string families;
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families += fontFamilies.at(i);
        families += ',';
    }
    families.pop_back();
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaFontFamily(nativeNode, families.c_str());
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
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showCounterArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> inputNumberArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t value = SHOW_COUNTER_DEFAULT;
    if (showCounterArg->IsBoolean()) {
        value = static_cast<uint32_t>(showCounterArg->ToBoolean(vm)->Value());
        if (inputNumberArg->IsNumber() && inputNumberArg->Int32Value(vm) > MINI_VAILD_VALUE &&
            inputNumberArg->Int32Value(vm) < MAX_VAILD_VALUE) {
            GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetCounterType(nativeNode, inputNumberArg->Int32Value(vm));
        }
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaShowCounter(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaShowCounter(nativeNode);
    }
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
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaCaretColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaCaretColor(nativeNode, color.GetValue());
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
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= 0) {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaMaxLength(nativeNode, secondArg->Int32Value(vm));
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaMaxLength(nativeNode);
    }
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
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaFontColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaFontColor(nativeNode, color.GetValue());
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
        int32_t fontStyle = secondArg->Int32Value(vm);
        if (fontStyle >= 0 && fontStyle < static_cast<int32_t>(FONT_STYLES.size())) {
            GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaFontStyle(nativeNode,
                static_cast<uint32_t>(fontStyle));
        } else {
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaFontStyle(nativeNode);
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
    std::string fontWeight = DEFAULT_FONT_WEIGHT;
    if (!secondArg->IsNull()) {
        if (secondArg->IsNumber()) {
            fontWeight = std::to_string(secondArg->Int32Value(vm));
        } else if (secondArg->IsString()) {
            fontWeight = secondArg->ToString(vm)->ToString();
        }
    }
    GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaFontWeight(nativeNode, fontWeight.c_str());
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
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    struct ArkUIResourceLength fontSize = { 0.0, 0, nullptr };
    CalcDimension size;
    std::string calcStr;
    if (jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionNG(vm, jsValue, size, DimensionUnit::FP, false)) {
        GetArkUIInternalNodeAPI()->GetTextAreaModifier().ResetTextAreaFontSize(nativeNode);
    } else {
        if (size.Unit() == DimensionUnit::CALC) {
            fontSize.Uint = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            fontSize.string = calcStr.c_str();
            GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaFontSize(nativeNode, &fontSize);
        } else {
            fontSize.value = size.Value();
            fontSize.Uint = static_cast<int32_t>(size.Unit());
            fontSize.string = calcStr.c_str();
            GetArkUIInternalNodeAPI()->GetTextAreaModifier().SetTextAreaFontSize(nativeNode, &fontSize);
        }
    }
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
