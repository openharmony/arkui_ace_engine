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
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"

namespace OHOS::Ace::NG {
namespace {
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_ERR_CODE = "-1";
const int32_t DEFAULT_NEGATIVE_NUM = -1;
constexpr uint32_t DEFAULT_TIME_PICKER_TEXT_COLOR = 0xFF182431;
constexpr uint32_t DEFAULT_TIME_PICKER_SELECTED_TEXT_COLOR = 0xFF0A59F7;

constexpr int32_t NODE_INDEX = 0;
constexpr int32_t STROKE_WIDTH_INDEX = 1;
constexpr int32_t COLOR_INDEX = 2;
constexpr int32_t START_MARGIN_INDEX = 3;
constexpr int32_t END_MARGIN_INDEX = 4;
constexpr int32_t NUM_1 = 1;

constexpr int32_t ARG_GROUP_LENGTH = 3;
constexpr int PARAM_ARR_LENGTH_2 = 2;
constexpr int NUM_0 = 0;
constexpr int NUM_2 = 2;
bool ParseDividerDimension(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& valueDim)
{
    return !ArkTSUtils::ParseJsDimensionVpNG(vm, value, valueDim, false) || LessNotEqual(valueDim.Value(), 0.0f) ||
        (valueDim.Unit() != DimensionUnit::PX && valueDim.Unit() != DimensionUnit::VP &&
        valueDim.Unit() != DimensionUnit::LPX && valueDim.Unit() != DimensionUnit::FP);
}

void PopulateValues(const CalcDimension& dividerStrokeWidth, const CalcDimension& dividerStartMargin,
    const CalcDimension& dividerEndMargin, ArkUI_Float32 values[], uint32_t size)
{
    values[NODE_INDEX] = static_cast<ArkUI_Float32>(dividerStrokeWidth.Value());
    values[STROKE_WIDTH_INDEX] = static_cast<ArkUI_Float32>(dividerStartMargin.Value());
    values[COLOR_INDEX] = static_cast<ArkUI_Float32>(dividerEndMargin.Value());
}

void PopulateUnits(const CalcDimension& dividerStrokeWidth, const CalcDimension& dividerStartMargin,
    const CalcDimension& dividerEndMargin, int32_t units[], uint32_t size)
{
    units[NODE_INDEX] = static_cast<int32_t>(dividerStrokeWidth.Unit());
    units[STROKE_WIDTH_INDEX] = static_cast<int32_t>(dividerStartMargin.Unit());
    units[COLOR_INDEX] = static_cast<int32_t>(dividerEndMargin.Unit());
}

void ParseFontSize(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen)
{
    if (value->IsNull() || value->IsUndefined()) {
        dimen = Dimension(DEFAULT_NEGATIVE_NUM);
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, value, dimen, DimensionUnit::FP, false)) {
            dimen = Dimension(DEFAULT_NEGATIVE_NUM);
        }
    }
}

void ParseFontWeight(const EcmaVM* vm, const Local<JSValueRef>& value, std::string& weight)
{
    if (!value->IsNull() && !value->IsUndefined()) {
        if (value->IsNumber()) {
            weight = std::to_string(value->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, value, weight) || weight.empty()) {
                weight = DEFAULT_ERR_CODE;
            }
        }
    }
}
} // namespace

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
    if (itemHeightValue->IsNumber() || itemHeightValue->IsString(vm)) {
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

ArkUINativeModuleValue TextPickerBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> dividerStrokeWidthArgs = runtimeCallInfo->GetCallArgRef(STROKE_WIDTH_INDEX);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(COLOR_INDEX);
    Local<JSValueRef> dividerStartMarginArgs = runtimeCallInfo->GetCallArgRef(START_MARGIN_INDEX);
    Local<JSValueRef> dividerEndMarginArgs = runtimeCallInfo->GetCallArgRef(END_MARGIN_INDEX);
    CalcDimension dividerStrokeWidth;
    CalcDimension dividerStartMargin;
    CalcDimension dividerEndMargin;
    Color colorObj;
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, panda::NativePointerRef::New(vm, nullptr));
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::NativePointerRef::New(vm, nullptr));
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, panda::NativePointerRef::New(vm, nullptr));
    if (ParseDividerDimension(vm, dividerStrokeWidthArgs, dividerStrokeWidth)) {
        if (pickerTheme) {
            dividerStrokeWidth = pickerTheme->GetDividerThickness();
        } else {
            dividerStrokeWidth = 0.0_vp;
        }
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, colorObj)) {
        if (pickerTheme) {
            colorObj = pickerTheme->GetDividerColor();
        } else {
            colorObj = Color::TRANSPARENT;
        }
    }
    if (ParseDividerDimension(vm, dividerStartMarginArgs, dividerStartMargin)) {
        dividerStartMargin = 0.0_vp;
    }
    if (ParseDividerDimension(vm, dividerEndMarginArgs, dividerEndMargin)) {
        dividerEndMargin = 0.0_vp;
    }
    uint32_t size = ARG_GROUP_LENGTH;
    ArkUI_Float32 values[size];
    int32_t units[size];
    PopulateValues(dividerStrokeWidth, dividerStartMargin, dividerEndMargin, values, size);
    PopulateUnits(dividerStrokeWidth, dividerStartMargin, dividerEndMargin, units, size);
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerDivider(
        nativeNode, colorObj.GetValue(), values, units, size);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    if (valueArg->IsNull()) {
        GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerDividerNull(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerDivider(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetGradientHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> itemHeightValue = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, panda::NativePointerRef::New(vm, nullptr));
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::NativePointerRef::New(vm, nullptr));
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, panda::NativePointerRef::New(vm, nullptr));
    CalcDimension height;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, itemHeightValue, height, true)) {
        GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerGradientHeight(
            nativeNode, height.Value(), static_cast<int32_t>(height.Unit()));
    } else {
        GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerGradientHeight(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetGradientHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerGradientHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetDisableTextStyleAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> disableTextStyleAnimationArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool disableTextStyleAnimation = false;
    if (disableTextStyleAnimationArg->IsBoolean()) {
        disableTextStyleAnimation = disableTextStyleAnimationArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerDisableTextStyleAnimation(
        nativeNode, disableTextStyleAnimation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetDisableTextStyleAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerDisableTextStyleAnimation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetDefaultTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);      // text color
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(2);   // text font size
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(3); // text font weight
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(4); // text font family
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(5);  // text font style
    Local<JSValueRef> minFontSizeArg = runtimeCallInfo->GetCallArgRef(6); // text minFontSize
    Local<JSValueRef> maxFontSizeArg = runtimeCallInfo->GetCallArgRef(7);  // text maxFontSize
    Local<JSValueRef> overflowArg = runtimeCallInfo->GetCallArgRef(8);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Color textColor;
    if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, textColor)) {
        textColor.SetValue(DEFAULT_TIME_PICKER_TEXT_COLOR);
    }
    CalcDimension size;
    ParseFontSize(vm, fontSizeArg, size);
    std::string weight = DEFAULT_ERR_CODE;
    ParseFontWeight(vm, fontWeightArg, weight);
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_ERR_CODE;
    }
    int32_t styleVal = 0;
    if (!fontStyleArg->IsNull() && !fontStyleArg->IsUndefined() && fontStyleArg->IsNumber()) {
        styleVal = fontStyleArg->Int32Value(vm);
    }
    CalcDimension minSize;
    ParseFontSize(vm, minFontSizeArg, minSize);
    CalcDimension maxSize;
    ParseFontSize(vm, maxFontSizeArg, maxSize);
    int32_t overflowVal = 0;
    if (!overflowArg->IsNull() && !overflowArg->IsUndefined() && overflowArg->IsNumber()) {
        overflowVal = overflowArg->Int32Value(vm);
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), size.ToString().c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerDefaultTextStyle(
        nativeNode, textColor.GetValue(), fontInfo.c_str(), styleVal, minSize.ToString().c_str(),
        maxSize.ToString().c_str(), overflowVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetDefaultTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerDefaultTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetTextPickerEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);   // framenode
    Local<JSValueRef> enableHapticFeedbackArg = runtimeCallInfo->GetCallArgRef(1); // isEnableHapticFeedback
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto modifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(modifiers, panda::NativePointerRef::New(vm, nullptr));
    auto textPickerModifier = modifiers->getTextPickerModifier();
    CHECK_NULL_RETURN(textPickerModifier, panda::NativePointerRef::New(vm, nullptr));
    if (enableHapticFeedbackArg->IsBoolean()) {
        bool value = enableHapticFeedbackArg->ToBoolean(vm)->Value();
        textPickerModifier->setTextPickerEnableHapticFeedback(nativeNode, value);
    } else {
        textPickerModifier->resetTextPickerEnableHapticFeedback(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetTextPickerEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // framenode
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto modifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(modifiers, panda::NativePointerRef::New(vm, nullptr));
    auto textPickerModifier = modifiers->getTextPickerModifier();
    CHECK_NULL_RETURN(textPickerModifier, panda::NativePointerRef::New(vm, nullptr));
    textPickerModifier->resetTextPickerEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetDigitalCrownSensitivity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_INDEX);
    Local<JSValueRef> crownSensitivityArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    int32_t crownSensitivity = OHOS::Ace::NG::DEFAULT_CROWNSENSITIVITY;
    if (crownSensitivityArg->IsNumber()) {
        crownSensitivity = crownSensitivityArg->ToNumber(vm)->Value();
    }
    auto modifier = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(modifier, panda::NativePointerRef::New(vm, nullptr));
    modifier->getTextPickerModifier()->setTextPickerDigitalCrownSensitivity(nativeNode, crownSensitivity);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetDigitalCrownSensitivity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto modifier = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(modifier, panda::NativePointerRef::New(vm, nullptr));
    modifier->getTextPickerModifier()->resetTextPickerDigitalCrownSensitivity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
template<typename T>
panda::Local<panda::JSValueRef> StringToStringValueWithVM(const EcmaVM* vm, T val)
{
    if constexpr (std::is_same_v<T, std::string>) {
        return panda::StringRef::NewFromUtf8(vm, val.c_str());
    } else if constexpr (std::is_same_v<T, const char*>) {
        return panda::StringRef::NewFromUtf8(vm, val);
    } else if constexpr (std::is_same_v<T, std::u16string>) {
        return panda::StringRef::NewFromUtf16(vm, val.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextPickerBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    int32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::vector<std::string>&, const std::vector<double>&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
            const std::vector<std::string>& value, const std::vector<double>& index) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            if (value.size() == NUM_1 && index.size() == NUM_1) {
                panda::Local<panda::NumberRef> paramIndex = panda::NumberRef::New(vm, index[NUM_0]);
                panda::Local<panda::StringRef> paramVaule = StringToStringValueWithVM(vm, value[NUM_0].c_str());
                panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = { paramVaule, paramIndex };
                func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
            } else {
                int32_t i = NUM_0;
                int32_t j = NUM_0;
                auto valueArray = panda::ArrayRef::New(vm);
                auto indexArray = panda::ArrayRef::New(vm);
                for (const double& it : index) {
                    panda::Local<panda::NumberRef> item = panda::NumberRef::New(vm, it);
                    panda::ArrayRef::SetValueAt(vm, indexArray, i++, item);
                }
                for (const std::string& str : value) {
                    panda::Local<panda::StringRef> item = StringToStringValueWithVM(vm, str.c_str());
                    panda::ArrayRef::SetValueAt(vm, valueArray, j++, item);
                }
                panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = { valueArray, indexArray };
                func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
            }
        };
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextPickerBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextPickerBridge::SetOnScrollStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    int32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerOnScrollStop(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::vector<std::string>&, const std::vector<double>&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
            const std::vector<std::string>& value, const std::vector<double>& index) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            if (value.size() == NUM_1 && index.size() == NUM_1) {
                panda::Local<panda::NumberRef> paramIndex = panda::NumberRef::New(vm, index[NUM_0]);
                panda::Local<panda::StringRef> paramVaule = StringToStringValueWithVM(vm, value[NUM_0].c_str());
                panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = { paramVaule, paramIndex };
                func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
            } else {
                int32_t i = NUM_0;
                int32_t j = NUM_0;
                auto valueArray = panda::ArrayRef::New(vm);
                auto indexArray = panda::ArrayRef::New(vm);
                for (const double& it : index) {
                    panda::Local<panda::NumberRef> item = panda::NumberRef::New(vm, it);
                    panda::ArrayRef::SetValueAt(vm, indexArray, i++, item);
                }
                for (const std::string& str : value) {
                    panda::Local<panda::StringRef> item = StringToStringValueWithVM(vm, str.c_str());
                    panda::ArrayRef::SetValueAt(vm, valueArray, j++, item);
                }
                panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = { valueArray, indexArray };
                func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
            }
        };
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerOnScrollStop(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextPickerBridge::ResetOnScrollStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextPickerModifier()->resetTextPickerOnScrollStop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
