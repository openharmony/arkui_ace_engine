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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_textpicker_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_ERR_CODE = "-1";
const int32_t DEFAULT_NEGATIVE_NUM = -1;
constexpr uint32_t DEFAULT_TIME_PICKER_TEXT_COLOR = 0xFF182431;
constexpr uint32_t DEFAULT_TIME_PICKER_SELECTED_TEXT_COLOR = 0xFF007DFF;

ArkUINativeModuleValue TextPickerBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CommonBridge::SetBackgroundColor(runtimeCallInfo);
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CommonBridge::ResetBackgroundColor(runtimeCallInfo);
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetCanLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> canLoopArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool canLoop = true;
    if (canLoopArg->IsBoolean()) {
        canLoop = canLoopArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerCanLoop(nativeNode, canLoop);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetSelectedIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> indexArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::vector<uint32_t> selectedValues;

    if (indexArg->IsArray(vm)) {
        if (!ArkTSUtils::ParseJsIntegerArray(vm, indexArg, selectedValues)) {
            selectedValues.clear();
            GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerSelectedIndex(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        if (selectedValues.size() > 0) {
            GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerSelectedIndex(
                nativeNode, selectedValues.data(), selectedValues.size());
        } else {
            GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerSelectedIndex(nativeNode);
        }
    } else {
        uint32_t selectedValue = 0;
        if (indexArg->IsNumber()) {
            selectedValue = indexArg->Uint32Value(vm);
            selectedValues.emplace_back(selectedValue);
            GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerSelectedIndex(
                nativeNode, selectedValues.data(), DEFAULT_NEGATIVE_NUM); // represent this is a number.
        } else {
            selectedValues.clear();
            GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerSelectedIndex(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);      // text color
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(2);   // text font size
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(3); // text font weight
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(4); // text font family
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(5);  // text font style
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Color textColor;
    if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, textColor)) {
        textColor.SetValue(DEFAULT_TIME_PICKER_TEXT_COLOR);
    }
    CalcDimension size;
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) {
        size = Dimension(DEFAULT_NEGATIVE_NUM);
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, fontSizeArg, size, DimensionUnit::FP, false)) {
            size = Dimension(DEFAULT_NEGATIVE_NUM);
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
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerTextStyle(
        nativeNode, textColor.GetValue(), fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);      // text color
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(2);   // text font size
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(3); // text font weight
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(4); // text font family
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(5);  // text font style
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Color textColor;
    if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, textColor)) {
        textColor.SetValue(DEFAULT_TIME_PICKER_SELECTED_TEXT_COLOR);
    }
    CalcDimension size;
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) {
        size = Dimension(DEFAULT_NEGATIVE_NUM);
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, fontSizeArg, size, DimensionUnit::FP, false)) {
            size = Dimension(DEFAULT_NEGATIVE_NUM);
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
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerSelectedTextStyle(
        nativeNode, textColor.GetValue(), fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);      // text color
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(2);   // text font size
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(3); // text font weight
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(4); // text font family
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(5);  // text font style
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Color textColor;
    if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, textColor)) {
        textColor.SetValue(DEFAULT_TIME_PICKER_TEXT_COLOR);
    }
    CalcDimension size;
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) {
        size = Dimension(DEFAULT_NEGATIVE_NUM);
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, fontSizeArg, size, DimensionUnit::FP, false)) {
            size = Dimension(DEFAULT_NEGATIVE_NUM);
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
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerDisappearTextStyle(
        nativeNode, textColor.GetValue(), fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetDefaultPickerItemHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> itemHeightValue = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    CalcDimension height;
    if (itemHeightValue->IsNumber() || itemHeightValue->IsString()) {
        if (!ArkTSUtils::ParseJsDimensionFp(vm, itemHeightValue, height)) {
            GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerDefaultPickerItemHeight(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
    }

    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerDefaultPickerItemHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()));

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetCanLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerCanLoop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetSelectedIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerSelectedIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerSelectedTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerDisappearTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetDefaultPickerItemHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerDefaultPickerItemHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG