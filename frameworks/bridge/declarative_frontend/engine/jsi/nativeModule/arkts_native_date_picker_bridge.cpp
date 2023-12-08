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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
const double PLACE_HOLDER_ARRAY = -10001;
const std::string FORMAT_FONT = "%s|%s|%s";

bool DataPickerParseJsColor(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result)
{
    if (!value->IsNumber() && !value->IsString() && !value->IsObject()) {
        return false;
    }
    if (value->IsNumber()) {
        result = Color(ArkTSUtils::ColorAlphaAdapt(value->Uint32Value(vm)));
        return true;
    }
    if (value->IsString()) {
        return Color::ParseColorString(value->ToString(vm)->ToString(), result);
    }
    // resouce ignore by design
    return false;
}

ArkUINativeModuleValue DatePickerBridge::SetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> textColorArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArgs = runtimeCallInfo->GetCallArgRef(NUM_5);

    if (textColorArgs->IsUndefined() && fontSizeArgs->IsUndefined() &&
        fontWeightArgs->IsUndefined() && fontFamilyArgs->IsUndefined() &&
        fontStyleArgs->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetDatePickerModifier().ResetSelectedTextStyle(nativeNode);
    }
    Color textColor;
    std::string fontSize;
    std::string fontWeight;
    std::string fontFamily;
    int32_t fontStyle = PLACE_HOLDER_ARRAY;
    if (!textColorArgs->IsNull() && !textColorArgs->IsUndefined()) {
        ArkTSUtils::ParseJsColorAlpha(vm, textColorArgs, textColor);
    }
    if (!fontSizeArgs->IsNull() && !fontSizeArgs->IsUndefined()) {
        if (fontSizeArgs->IsNumber()) {
            fontSize = std::to_string(fontSizeArgs->Uint32Value(vm));
        } else {
            ArkTSUtils::ParseJsString(vm, fontSizeArgs, fontSize);
        }
    }
    if (!fontWeightArgs->IsNull() && !fontWeightArgs->IsUndefined()) {
        ArkTSUtils::ParseJsString(vm, fontWeightArgs, fontWeight);
    }
    if (!fontFamilyArgs->IsNull() && !fontFamilyArgs->IsUndefined()) {
        ArkTSUtils::ParseJsString(vm, fontFamilyArgs, fontFamily);
    }
    if (!fontStyleArgs->IsNull() && !fontStyleArgs->IsUndefined() && fontStyleArgs->IsNumber()) {
        fontStyle = fontStyleArgs->Int32Value(vm);
    }

    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), fontWeight.c_str(), fontFamily.c_str());

    GetArkUIInternalNodeAPI()->GetDatePickerModifier().SetSelectedTextStyle(
        nativeNode, fontInfo.c_str(), fontStyle, textColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDatePickerModifier().ResetSelectedTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> textColorArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArgs = runtimeCallInfo->GetCallArgRef(NUM_5);

    if (textColorArgs->IsUndefined() && fontSizeArgs->IsUndefined() &&
        fontWeightArgs->IsUndefined() && fontFamilyArgs->IsUndefined() &&
        fontStyleArgs->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetDatePickerModifier().ResetSelectedTextStyle(nativeNode);
    }
    Color textColor;
    std::string fontSize;
    std::string fontWeight;
    std::string fontFamily;
    int32_t fontStyle = PLACE_HOLDER_ARRAY;
    if (!textColorArgs->IsNull() && !textColorArgs->IsUndefined()) {
        ArkTSUtils::ParseJsColorAlpha(vm, textColorArgs, textColor);
    }
    if (!fontSizeArgs->IsNull() && !fontSizeArgs->IsUndefined()) {
        if (fontSizeArgs->IsNumber()) {
            fontSize = std::to_string(fontSizeArgs->Uint32Value(vm));
        } else {
            ArkTSUtils::ParseJsString(vm, fontSizeArgs, fontSize);
        }
    }
    if (!fontWeightArgs->IsNull() && !fontWeightArgs->IsUndefined()) {
        ArkTSUtils::ParseJsString(vm, fontWeightArgs, fontWeight);
    }
    if (!fontFamilyArgs->IsNull() && !fontFamilyArgs->IsUndefined()) {
        ArkTSUtils::ParseJsString(vm, fontFamilyArgs, fontFamily);
    }
    if (!fontStyleArgs->IsNull() && !fontStyleArgs->IsUndefined() && fontStyleArgs->IsNumber()) {
        fontStyle = fontStyleArgs->Int32Value(vm);
    }

    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), fontWeight.c_str(), fontFamily.c_str());
    
    GetArkUIInternalNodeAPI()->GetDatePickerModifier().SetDatePickerTextStyle(
        nativeNode, fontInfo.c_str(), fontStyle, textColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDatePickerModifier().ResetDatePickerTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> textColorArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArgs = runtimeCallInfo->GetCallArgRef(NUM_5);

    if (textColorArgs->IsUndefined() && fontSizeArgs->IsUndefined() &&
        fontWeightArgs->IsUndefined() && fontFamilyArgs->IsUndefined() &&
        fontStyleArgs->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetDatePickerModifier().ResetSelectedTextStyle(nativeNode);
    }
    Color textColor;
    std::string fontSize;
    std::string fontWeight;
    std::string fontFamily;
    int32_t fontStyle = PLACE_HOLDER_ARRAY;
    if (!textColorArgs->IsNull() && !textColorArgs->IsUndefined()) {
        ArkTSUtils::ParseJsColorAlpha(vm, textColorArgs, textColor);
    }
    if (!fontSizeArgs->IsNull() && !fontSizeArgs->IsUndefined()) {
        if (fontSizeArgs->IsNumber()) {
            fontSize = std::to_string(fontSizeArgs->Uint32Value(vm));
        } else {
            ArkTSUtils::ParseJsString(vm, fontSizeArgs, fontSize);
        }
    }
    if (!fontWeightArgs->IsNull() && !fontWeightArgs->IsUndefined()) {
        ArkTSUtils::ParseJsString(vm, fontWeightArgs, fontWeight);
    }
    if (!fontFamilyArgs->IsNull() && !fontFamilyArgs->IsUndefined()) {
        ArkTSUtils::ParseJsString(vm, fontFamilyArgs, fontFamily);
    }
    if (!fontStyleArgs->IsNull() && !fontStyleArgs->IsUndefined() && fontStyleArgs->IsNumber()) {
        fontStyle = fontStyleArgs->Int32Value(vm);
    }

    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), fontWeight.c_str(), fontFamily.c_str());

    GetArkUIInternalNodeAPI()->GetDatePickerModifier().SetDisappearTextStyle(
        nativeNode, fontInfo.c_str(), fontStyle, textColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDatePickerModifier().ResetDisappearTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetLunar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool isLunar = secondArg->ToBoolean(vm)->Value();
    
    GetArkUIInternalNodeAPI()->GetDatePickerModifier().SetLunar(nativeNode, isLunar);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetLunar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDatePickerModifier().ResetLunar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
