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

void DataPickerParseJsWeight(const EcmaVM* vm, const Local<JSValueRef>& value, std::string weight)
{
    if (!value->IsNull() && !value->IsUndefined()) {
        if (value->IsNumber()) {
            weight = std::to_string(value->Uint32Value(vm));
        } else {
            weight = value->ToString(vm)->ToString();
        }
    }
}

void DataPickerParseJsSize(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& size)
{
    if (value->IsNull() || value->IsUndefined()) {
        size = Dimension(-1);
    } else {
        if (!ArkTSUtils::ParseJsDimensionFp(vm, value, size) || size.Unit() == DimensionUnit::PERCENT) {
            size = Dimension(-1);
        }
    }
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

    Color textColor;
    CalcDimension fontSize;
    std::string fontWeight;
    std::string fontFamily;
    int32_t fontStyle = PLACE_HOLDER_ARRAY;

    DataPickerParseJsSize(vm, fontSizeArgs, fontSize);
    DataPickerParseJsWeight(vm, fontWeightArgs, fontWeight);
    DataPickerParseJsColor(vm, textColorArgs, textColor);
    if (fontStyleArgs->IsNumber()) {
        fontStyle = fontStyleArgs->Int32Value(vm);
    }
    if (!fontFamilyArgs->IsNull() && !fontFamilyArgs->IsUndefined() && fontFamilyArgs->IsString()) {
        fontFamily = fontFamilyArgs->ToString(vm)->ToString();
    }

    int values[NUM_3] {};
    values[NUM_0] = textColor.GetValue();
    values[NUM_1] = static_cast<int>(fontSize.Unit());
    values[NUM_2] = fontStyle;

    GetArkUIInternalNodeAPI()->GetDatePickerModifier().SetSelectedTextStyle(
        nativeNode, fontWeight.c_str(), fontFamily.c_str(), values, NUM_3);
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

    Color textColor;
    CalcDimension fontSize;
    std::string fontWeight;
    std::string fontFamily;
    int32_t fontStyle = PLACE_HOLDER_ARRAY;

    DataPickerParseJsSize(vm, fontSizeArgs, fontSize);
    DataPickerParseJsWeight(vm, fontWeightArgs, fontWeight);
    DataPickerParseJsColor(vm, textColorArgs, textColor);
    if (fontStyleArgs->IsNumber()) {
        fontStyle = fontStyleArgs->Int32Value(vm);
    }
    if (!fontFamilyArgs->IsNull() && !fontFamilyArgs->IsUndefined() && fontFamilyArgs->IsString()) {
        fontFamily = fontFamilyArgs->ToString(vm)->ToString();
    }

    int values[NUM_3];
    values[NUM_0] = textColor.GetValue();
    values[NUM_1] = static_cast<int>(fontSize.Unit());
    values[NUM_2] = fontStyle;

    GetArkUIInternalNodeAPI()->GetDatePickerModifier().SetDatePickerTextStyle(
        nativeNode, fontWeight.c_str(), fontFamily.c_str(), values, NUM_3);
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

    Color textColor;
    CalcDimension fontSize;
    std::string fontWeight;
    std::string fontFamily;
    int32_t fontStyle = PLACE_HOLDER_ARRAY;

    DataPickerParseJsSize(vm, fontSizeArgs, fontSize);
    DataPickerParseJsWeight(vm, fontWeightArgs, fontWeight);
    DataPickerParseJsColor(vm, textColorArgs, textColor);
    if (fontStyleArgs->IsNumber()) {
        fontStyle = fontStyleArgs->Int32Value(vm);
    }
    if (!fontFamilyArgs->IsNull() && !fontFamilyArgs->IsUndefined() && fontFamilyArgs->IsString()) {
        fontFamily = fontFamilyArgs->ToString(vm)->ToString();
    }

    int values[NUM_3];
    values[NUM_0] = textColor.GetValue();
    values[NUM_1] = static_cast<int>(fontSize.Unit());
    values[NUM_2] = fontStyle;
    GetArkUIInternalNodeAPI()->GetDatePickerModifier().SetDisappearTextStyle(
        nativeNode, fontWeight.c_str(), fontFamily.c_str(), values, NUM_3);
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
