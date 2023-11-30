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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_alphabet_indexer_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/jsview/models/indexer_model_impl.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
const std::string FORMAT_FONT = "%s|%s|%s";
bool ParseJsDimensionFp(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& result)
{
    if (value->IsNumber()) {
        result = CalcDimension(value->ToNumber(vm)->Value(), DimensionUnit::FP);
        return true;
    }
    if (value->IsString()) {
        result = StringUtils::StringToCalcDimension(value->ToString(vm)->ToString(), false, DimensionUnit::FP);
        return true;
    }
    // resource ignore by design
    return false;
}

bool ParseJsInteger(const EcmaVM* vm, const Local<JSValueRef>& value, int32_t& result)
{
    if (value->IsNumber()) {
        result = value->Int32Value(vm);
        return true;
    }
    // resouce ignore by design
    return false;
}

bool ParseJsDimensionVp(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& result)
{
    if (value->IsNumber()) {
        result = CalcDimension(value->ToNumber(vm)->Value(), DimensionUnit::VP);
        return true;
    }
    if (value->IsString()) {
        result = StringUtils::StringToCalcDimension(value->ToString(vm)->ToString(), false, DimensionUnit::VP);
        return true;
    }
    // resouce ignore by design
    return false;
}
} // namespace

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupItemFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    CalcDimension fontSize;
    if (!ParseJsDimensionFp(vm, secondArg, fontSize) || thirdArg->IsNull()) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupItemFont(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetPopupItemFont(nativeNode, fontSize.Value(),
            static_cast<int>(fontSize.Unit()), thirdArg->ToString(vm)->ToString().c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupItemFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupItemFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetSelectedFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined() && thirdArg->IsUndefined() && fourthArg->IsUndefined() && fifthArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetSelectedFont(nativeNode);
    }
    std::string fontSize = "-1";
    std::string weight = "-1";
    std::string fontFamily = "-1";
    int32_t styleVal = 0;
    fontSize = secondArg->ToString(vm)->ToString();
    weight = thirdArg->ToString(vm)->ToString();
    fontFamily = fourthArg->ToString(vm)->ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    styleVal = fifthArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetSelectedFont(nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetSelectedFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetSelectedFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined() && thirdArg->IsUndefined() && fourthArg->IsUndefined() && fifthArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupFont(nativeNode);
    }
    std::string fontSize = "-1";
    std::string weight = "-1";
    std::string fontFamily = "-1";
    int32_t styleVal = 0;
    fontSize = secondArg->ToString(vm)->ToString();
    weight = thirdArg->ToString(vm)->ToString();
    fontFamily = fourthArg->ToString(vm)->ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    styleVal = fifthArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetPopupFont(nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined() && thirdArg->IsUndefined() && fourthArg->IsUndefined() && fifthArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetAlphabetIndexerFont(nativeNode);
    }
    std::string fontSize = "-1";
    std::string weight = "-1";
    std::string fontFamily = "-1";
    int32_t styleVal = 0;
    fontSize = secondArg->ToString(vm)->ToString();
    weight = thirdArg->ToString(vm)->ToString();
    fontFamily = fourthArg->ToString(vm)->ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    styleVal = fifthArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetAlphabetIndexerFont(
        nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetAlphabetIndexerFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupItemBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupItemBackgroundColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetPopupItemBackgroundColor(
            nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupItemBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupItemBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetAlphabetIndexerColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetAlphabetIndexerColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetAlphabetIndexerColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetPopupColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetAlphabetIndexerSelectedColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetAlphabetIndexerSelectedColor(
            nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetAlphabetIndexerSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupBackground(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupBackground(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetPopupBackground(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupBackground(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupBackground(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetSelectedBackgroundColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetSelectedBackgroundColor(
            nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetSelectedBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupUnselectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupUnselectedColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetPopupUnselectedColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupUnselectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupUnselectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetAlignStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t value = Container::IsCurrentUseNewPipeline() ? static_cast<int32_t>(NG::AlignStyle::RIGHT)
                                                         : static_cast<int32_t>(V2::AlignStyle::RIGHT);
    if (!secondArg->IsNumber()) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetAlignStyle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t alignValue = secondArg->Int32Value(vm);
    if (alignValue >= 0 && alignValue < static_cast<int32_t>(ALIGN_STYLE.size())) {
        value = alignValue;
    }
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetAlignStyle(nativeNode, value);
    CalcDimension popupHorizontalSpace;
    if (!thirdArg->IsUndefined() && ParseJsDimensionVp(vm, thirdArg, popupHorizontalSpace)) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetPopupHorizontalSpace(
            nativeNode, popupHorizontalSpace.Value(), static_cast<int>(popupHorizontalSpace.Unit()));
    } else {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupHorizontalSpace(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetAlignStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetAlignStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupSelectedColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetPopupSelectedColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetUsingPopup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool usingPopup = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetUsingPopup(nativeNode, usingPopup);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetUsingPopup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetUsingPopup(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t selected = 0;
    if (ParseJsInteger(vm, secondArg, selected)) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetAlphabetIndexerSelected(nativeNode, selected);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetAlphabetIndexerSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetItemSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    CalcDimension itemSize;
    if (ParseJsDimensionVp(vm, secondArg, itemSize) && GreatNotEqual(itemSize.Value(), 0.0) &&
        itemSize.Unit() != DimensionUnit::PERCENT) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetItemSize(
            nativeNode, itemSize.Value(), static_cast<int>(itemSize.Unit()));
    } else {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetItemSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetItemSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetItemSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> sizeX = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> sizeY = runtimeCallInfo->GetCallArgRef(NUM_2);

    CalcDimension x;
    CalcDimension y;
    // param is x and y,parse CalcDimension by utility
    if (!ParseJsDimensionVp(vm, sizeX, x) && !ParseJsDimensionVp(vm, sizeY, y)) {
        GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupPosition(nativeNode);
    }

    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().SetPopupPosition(
        nativeNode, x.Value(), static_cast<int>(x.Unit()), y.Value(), static_cast<int>(y.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetAlphabetIndexerModifier().ResetPopupPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
