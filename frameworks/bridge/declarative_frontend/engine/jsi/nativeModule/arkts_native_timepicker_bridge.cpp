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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_timepicker_bridge.h"

#include "core/interfaces/native/node/api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
const std::string DEFAULT_ERR_CODE = "-1";
const std::string FORMAT_FONT = "%s|%s|%s";
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr uint32_t DEFAULT_TIME_PICKER_TEXT_COLOR = 0xFF182431;
constexpr uint32_t DEFAULT_TIME_PICKER_SELECTED_TEXT_COLOR = 0xFF007DFF;

ArkUINativeModuleValue TimepickerBridge::SetTimepickerBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t color = secondArg->Uint32Value(vm);
    GetArkUIInternalNodeAPI()->GetTimepickerModifier().SetTimepickerBackgroundColor(nativeNode, color);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimepickerBridge::ResetTimepickerBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTimepickerModifier().ResetTimepickerBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimepickerBridge::SetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        color.SetValue(DEFAULT_TIME_PICKER_TEXT_COLOR);
    }
    CalcDimension size;
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) {
        size = Dimension(-1);
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, fontSizeArg, size, DimensionUnit::FP, false)) {
            size = Dimension(-1);
        }
    }
    std::string weight = DEFAULT_ERR_CODE;
    if (!fontWeightArg->IsNull() && !fontWeightArg->IsUndefined()) {
        if (fontWeightArg->IsNumber()) {
            weight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, fontWeightArg, weight) || weight.empty()) {
                weight = DEFAULT_ERR_CODE;
            }
        }
    }
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_ERR_CODE;
    }
    int32_t styleVal = 0;
    if (!fontStyleArg->IsNull() && !fontStyleArg->IsUndefined()) {
        styleVal = fontStyleArg->Int32Value(vm);
    }
    std::string fontSizeStr = size.ToString();
    std::string fontInfo = StringUtils::FormatString(
        FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUIInternalNodeAPI()->GetTimepickerModifier().SetTimepickerTextStyle(
        nativeNode, color.GetValue(), fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimepickerBridge::SetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        color.SetValue(DEFAULT_TIME_PICKER_SELECTED_TEXT_COLOR);
    }
    CalcDimension size;
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) {
        size = Dimension(-1);
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, fontSizeArg, size, DimensionUnit::FP, false)) {
            size = Dimension(-1);
        }
    }
    std::string weight = DEFAULT_ERR_CODE;
    if (!fontWeightArg->IsNull() && !fontWeightArg->IsUndefined()) {
        if (fontWeightArg->IsNumber()) {
            weight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, fontWeightArg, weight) || weight.empty()) {
                weight = DEFAULT_ERR_CODE;
            }
        }
    }
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_ERR_CODE;
    }
    int32_t styleVal = 0;
    if (!fontStyleArg->IsNull() && !fontStyleArg->IsUndefined()) {
        styleVal = fontStyleArg->Int32Value(vm);
    }
    std::string fontSizeStr = size.ToString();
    std::string fontInfo = StringUtils::FormatString(
        FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUIInternalNodeAPI()->GetTimepickerModifier().SetTimepickerSelectedTextStyle(
        nativeNode, color.GetValue(), fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimepickerBridge::SetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        color.SetValue(DEFAULT_TIME_PICKER_TEXT_COLOR);
    }
    CalcDimension size;
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) {
        size = Dimension(-1);
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, fontSizeArg, size, DimensionUnit::FP, false)) {
            size = Dimension(-1);
        }
    }
    std::string weight = DEFAULT_ERR_CODE;
    if (!fontWeightArg->IsNull() && !fontWeightArg->IsUndefined()) {
        if (fontWeightArg->IsNumber()) {
            weight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, fontWeightArg, weight) || weight.empty()) {
                weight = DEFAULT_ERR_CODE;
            }
        }
    }
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_ERR_CODE;
    }
    int32_t styleVal = 0;
    if (!fontStyleArg->IsNull() && !fontStyleArg->IsUndefined()) {
        styleVal = fontStyleArg->Int32Value(vm);
    }
    std::string fontSizeStr = size.ToString();
    std::string fontInfo = StringUtils::FormatString(
        FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUIInternalNodeAPI()->GetTimepickerModifier().SetTimepickerDisappearTextStyle(
        nativeNode, color.GetValue(), fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimepickerBridge::ResetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTimepickerModifier().ResetTimepickerTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimepickerBridge::ResetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTimepickerModifier().ResetTimepickerSelectedTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimepickerBridge::ResetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTimepickerModifier().ResetTimepickerDisappearTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimepickerBridge::SetTimepickerUseMilitaryTime(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> useMilitaryArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (useMilitaryArg->IsBoolean()) {
        bool value = useMilitaryArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetTimepickerModifier().SetTimepickerUseMilitaryTime(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetTimepickerModifier().ResetTimepickerUseMilitaryTime(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimepickerBridge::ResetTimepickerUseMilitaryTime(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTimepickerModifier().ResetTimepickerUseMilitaryTime(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG