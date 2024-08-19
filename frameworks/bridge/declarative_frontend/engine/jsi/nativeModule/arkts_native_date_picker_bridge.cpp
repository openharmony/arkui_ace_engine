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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_date_picker_bridge.h"

#include "interfaces/napi/kits/utils/napi_utils.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_FAMILY = "HarmonyOS Sans";
ArkUINativeModuleValue DatePickerBridge::SetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> textColorArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArgs = runtimeCallInfo->GetCallArgRef(NUM_5);

    if (textColorArgs->IsUndefined() && fontSizeArgs->IsUndefined() && fontWeightArgs->IsUndefined() &&
        fontFamilyArgs->IsUndefined() && fontStyleArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetSelectedTextStyle(nativeNode);
    }

    CalcDimension fontSizeData;
    std::string fontSize;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArgs, fontSizeData, true, false) ||
        fontSizeData.Unit() == DimensionUnit::PERCENT) {
        fontSizeData = Dimension(-1);
    }
    fontSize = fontSizeData.ToString();

    std::string weight = "FontWeight.Medium";
    if (fontWeightArgs->IsString(vm) || fontWeightArgs->IsNumber()) {
        weight = fontWeightArgs->ToString(vm)->ToString(vm);
    }

    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArgs, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_FAMILY;
    }
    int32_t fontStyle = 0;
    if (fontStyleArgs->IsNumber()) {
        fontStyle = fontStyleArgs->Int32Value(vm);
    }
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, textColorArgs, color)) {
        Color::ParseColorString("#ff0a59f7", color);
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUINodeModifiers()->getDatePickerModifier()->setSelectedTextStyle(
        nativeNode, fontInfo.c_str(), color.GetValue(), fontStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetSelectedTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> textColorArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArgs = runtimeCallInfo->GetCallArgRef(NUM_5);

    if (textColorArgs->IsUndefined() && fontSizeArgs->IsUndefined() && fontWeightArgs->IsUndefined() &&
        fontFamilyArgs->IsUndefined() && fontStyleArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetSelectedTextStyle(nativeNode);
    }
    CalcDimension fontSizeData;
    std::string fontSize;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArgs, fontSizeData, true, false) ||
        fontSizeData.Unit() == DimensionUnit::PERCENT) {
        fontSizeData = Dimension(-1);
    }
    fontSize = fontSizeData.ToString();

    std::string weight = "FontWeight.Regular";
    if (fontWeightArgs->IsString(vm) || fontWeightArgs->IsNumber()) {
        weight = fontWeightArgs->ToString(vm)->ToString(vm);
    }

    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArgs, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_FAMILY;
    }
    int32_t fontStyle = 0;
    if (fontStyleArgs->IsNumber()) {
        fontStyle = fontStyleArgs->Int32Value(vm);
    }
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, textColorArgs, color)) {
        Color::ParseColorString("#ff182431", color);
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUINodeModifiers()->getDatePickerModifier()->setDatePickerTextStyle(
        nativeNode, fontInfo.c_str(), color.GetValue(), fontStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetDatePickerTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> textColorArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArgs = runtimeCallInfo->GetCallArgRef(NUM_5);

    if (textColorArgs->IsUndefined() && fontSizeArgs->IsUndefined() && fontWeightArgs->IsUndefined() &&
        fontFamilyArgs->IsUndefined() && fontStyleArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetSelectedTextStyle(nativeNode);
    }
    CalcDimension fontSizeData;
    std::string fontSize;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArgs, fontSizeData, true, false) ||
        fontSizeData.Unit() == DimensionUnit::PERCENT) {
        fontSizeData = Dimension(-1);
    }
    fontSize = fontSizeData.ToString();

    std::string weight = "FontWeight.Regular";
    if (fontWeightArgs->IsString(vm) || fontWeightArgs->IsNumber()) {
        weight = fontWeightArgs->ToString(vm)->ToString(vm);
    }

    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArgs, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_FAMILY;
    }
    int32_t fontStyle = 0;
    if (fontStyleArgs->IsNumber()) {
        fontStyle = fontStyleArgs->Int32Value(vm);
    }
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, textColorArgs, color)) {
        Color::ParseColorString("#ff182431", color);
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUINodeModifiers()->getDatePickerModifier()->setDisappearTextStyle(
        nativeNode, fontInfo.c_str(), color.GetValue(), fontStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetDisappearTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetLunar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> isLunarArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (isLunarArg->IsUndefined() || !isLunarArg->IsBoolean()) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetLunar(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool isLunar = isLunarArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getDatePickerModifier()->setLunar(nativeNode, isLunar);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetLunar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetLunar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::SetBackgroundColor(runtimeCallInfo);

    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetDatePickerBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getDatePickerModifier()->setDatePickerBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::ResetBackgroundColor(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetDatePickerBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
