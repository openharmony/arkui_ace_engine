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
const int32_t DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_BORDER_RADIUS = 24;
constexpr uint32_t DEFAULT_TIME_PICKER_TEXT_COLOR = 0xFF182431;
constexpr uint32_t DEFAULT_TIME_PICKER_SELECTED_TEXT_COLOR = 0xFF0A59F7;
constexpr uint32_t DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_COLOR = 0x0C182431;

constexpr int32_t NODE_INDEX = 0;
constexpr int32_t STROKE_WIDTH_INDEX = 1;
constexpr int32_t COLOR_INDEX = 2;
constexpr int32_t START_MARGIN_INDEX = 3;
constexpr int32_t END_MARGIN_INDEX = 4;
constexpr int32_t NUM_1 = 1;
constexpr int32_t UNIT_VP = 1;

constexpr int32_t ARG_GROUP_LENGTH = 3;
constexpr int PARAM_ARR_LENGTH_2 = 2;
constexpr int NUM_0 = 0;
constexpr int NUM_2 = 2;
constexpr int VALUE_MAX_SIZE = 4;
constexpr int GETVALUE_MAX_SIZE = 5;

constexpr int32_t NODE_ARG_INDEX = 0;
constexpr int32_t COLOR_ARG_INDEX = 1;
constexpr int32_t FONT_SIZE_ARG_INDEX = 2;
constexpr int32_t FONT_WEIGHT_ARG_INDEX = 3;
constexpr int32_t FONT_FAMILY_ARG_INDEX = 4;
constexpr int32_t FONT_STYLE_ARG_INDEX = 5;
constexpr int32_t MIN_FONT_SIZE_ARG_INDEX = 6;
constexpr int32_t MAX_FONT_SIZE_ARG_INDEX = 7;
constexpr int32_t OVER_FLOW_ARG_INDEX = 8;

enum GetValueArrayIndex {
    GETCOLOR,
    GETTOPLEFT,
    GETTOPRIGHT,
    GETBOTTOMLEFT,
    GETBOTTOMRIGHT,
};
enum ValueArrayIndex {
    TOPLEFT,
    TOPRIGHT,
    BOTTOMLEFT,
    BOTTOMRIGHT,
};
bool ParseDividerDimension(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& valueDim,
    RefPtr<ResourceObject>& resourceObject)
{
    return !ArkTSUtils::ParseJsDimensionVpNG(vm, value, valueDim, resourceObject, false) ||
        LessNotEqual(valueDim.Value(), 0.0f) ||
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

std::string ParseFontSize(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t argIndex,
    RefPtr<ResourceObject>& fontSizeResObj)
{
    CalcDimension fontSizeData;
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(argIndex);
    if (arg->IsNull() || arg->IsUndefined()) {
        fontSizeData = Dimension(DEFAULT_NEGATIVE_NUM);
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, arg, fontSizeData, DimensionUnit::FP, fontSizeResObj, false)) {
            fontSizeData = Dimension(DEFAULT_NEGATIVE_NUM);
        }
    }
    return fontSizeData.ToString();
}

std::string ParseFontWeight(const EcmaVM* vm, const Local<JSValueRef>& value)
{
    std::string weight = DEFAULT_ERR_CODE;
    if (!value->IsNull() && !value->IsUndefined()) {
        if (value->IsNumber()) {
            weight = std::to_string(value->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, value, weight) || weight.empty()) {
                weight = DEFAULT_ERR_CODE;
            }
        }
    }
    return weight;
}

std::string ParseFontFamily(const EcmaVM* vm, const Local<JSValueRef>& fontFamilyArg,
    RefPtr<ResourceObject>& fontFamilyResObj)
{
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily, fontFamilyResObj) ||
        fontFamily.empty()) {
        fontFamily = DEFAULT_ERR_CODE;
    }
    return fontFamily;
}

Color ParseTextColor(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t argIndex,
    RefPtr<ResourceObject>& textColorResObj, uint32_t defaultTextColor,
    ArkUINodeHandle nativeNode, int32_t& isSetByUser)
{
    Color textColor;
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(argIndex);

    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (colorArg->IsNull() || colorArg->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, textColor, textColorResObj, nodeInfo)) {
        textColor.SetValue(defaultTextColor);
        isSetByUser = false;
    } else {
        isSetByUser = true;
    }
    return textColor;
}

void ParseSelectedBackgroundStyleRadius(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Bool* isHasValue,
    ArkUIPickerBackgroundStyleStruct& backgroundStyleStruct, RefPtr<ResourceObject>* radiusResObjs)
{
    ArkUI_Float32 value[VALUE_MAX_SIZE] = {
        DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_BORDER_RADIUS, DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_BORDER_RADIUS,
        DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_BORDER_RADIUS, DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_BORDER_RADIUS};
    ArkUI_Int32 unit[VALUE_MAX_SIZE] = {UNIT_VP, UNIT_VP, UNIT_VP, UNIT_VP};
    auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    CalcDimension calcDimension;
    RefPtr<ResourceObject> tmpResObj;
    for (int i = 0; i < VALUE_MAX_SIZE; i++) {
        if (ArkTSUtils::ParseJsLengthMetrics(vm, runtimeCallInfo->GetCallArgRef(i + NUM_2), calcDimension, tmpResObj) &&
            !calcDimension.IsNegative()) {
            isHasValue[i + COLOR_ARG_INDEX] = true;
            value[i] = calcDimension.Value();
            unit[i] = static_cast<int>(calcDimension.Unit());
            radiusResObjs[i] = tmpResObj;
        }
        if (ArkTSUtils::ParseJsDimensionVp(vm, runtimeCallInfo->GetCallArgRef(i + NUM_2), calcDimension, tmpResObj) &&
            !calcDimension.IsNegative()) {
            isHasValue[i + COLOR_ARG_INDEX] = true;
            value[i] = calcDimension.Value();
            unit[i] = static_cast<int>(calcDimension.Unit());
            radiusResObjs[i] = tmpResObj;
        }
    }
    if (isRightToLeft && (value[TOPLEFT] != value[BOTTOMLEFT] || value[TOPRIGHT] != value[BOTTOMRIGHT]) &&
        (unit[TOPLEFT] != unit[BOTTOMLEFT] || unit[TOPRIGHT] != unit[BOTTOMRIGHT])) {
        std::swap(value[TOPLEFT], value[BOTTOMLEFT]);
        std::swap(value[TOPRIGHT], value[BOTTOMRIGHT]);
        std::swap(unit[TOPLEFT], unit[BOTTOMLEFT]);
        std::swap(unit[TOPRIGHT], unit[BOTTOMRIGHT]);
        std::swap(isHasValue[GETTOPLEFT], isHasValue[GETTOPRIGHT]);
        std::swap(isHasValue[GETBOTTOMLEFT], isHasValue[GETBOTTOMRIGHT]);
        std::swap(radiusResObjs[TOPLEFT], radiusResObjs[BOTTOMLEFT]);
        std::swap(radiusResObjs[TOPRIGHT], radiusResObjs[BOTTOMRIGHT]);
    }
    backgroundStyleStruct.values = value;
    backgroundStyleStruct.units = unit;
    backgroundStyleStruct.length = VALUE_MAX_SIZE;
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(FONT_WEIGHT_ARG_INDEX);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(FONT_FAMILY_ARG_INDEX);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(FONT_STYLE_ARG_INDEX);
    Local<JSValueRef> overflowArg = runtimeCallInfo->GetCallArgRef(OVER_FLOW_ARG_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    ArkUIPickerTextStyleStruct textStyleStruct;
    RefPtr<ResourceObject> textColorResObj;
    Color textColor = ParseTextColor(vm, runtimeCallInfo, COLOR_ARG_INDEX, textColorResObj,
        DEFAULT_TIME_PICKER_TEXT_COLOR, nativeNode, textStyleStruct.textColorSetByUser);

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSizeStr = ParseFontSize(vm, runtimeCallInfo, FONT_SIZE_ARG_INDEX, fontSizeResObj);

    std::string weight = ParseFontWeight(vm, fontWeightArg);

    std::string fontFamily;
    RefPtr<ResourceObject> fontFamilyResObj;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily, fontFamilyResObj) ||
        fontFamily.empty()) {
        fontFamily = DEFAULT_ERR_CODE;
    }

    int32_t styleVal = 0;
    if (!fontStyleArg->IsNull() && !fontStyleArg->IsUndefined()) {
        styleVal = fontStyleArg->Int32Value(vm);
    }

    RefPtr<ResourceObject> minFontSizeResObj;
    std::string minSize = ParseFontSize(vm, runtimeCallInfo, MIN_FONT_SIZE_ARG_INDEX, minFontSizeResObj);

    RefPtr<ResourceObject> maxFontSizeResObj;
    std::string maxSize = ParseFontSize(vm, runtimeCallInfo, MAX_FONT_SIZE_ARG_INDEX, maxFontSizeResObj);

    int32_t overflowVal = 0;
    if (!overflowArg->IsNull() && !overflowArg->IsUndefined() && overflowArg->IsNumber()) {
        overflowVal = overflowArg->Int32Value(vm);
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());

    textStyleStruct.textColor = textColor.GetValue();
    textStyleStruct.fontStyle = styleVal;
    textStyleStruct.textOverflow = overflowVal;
    textStyleStruct.fontInfo = fontInfo.c_str();
    textStyleStruct.minFontSize = minSize.c_str();
    textStyleStruct.maxFontSize = maxSize.c_str();
    textStyleStruct.fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    textStyleStruct.fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    textStyleStruct.textColorRawPtr = AceType::RawPtr(textColorResObj);
    textStyleStruct.minFontSizeRawPtr = AceType::RawPtr(minFontSizeResObj);
    textStyleStruct.maxFontSizeRawPtr = AceType::RawPtr(maxFontSizeResObj);
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerTextStyleWithResObj(nativeNode, &textStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(FONT_WEIGHT_ARG_INDEX);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(FONT_FAMILY_ARG_INDEX);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(FONT_STYLE_ARG_INDEX);
    Local<JSValueRef> overflowArg = runtimeCallInfo->GetCallArgRef(OVER_FLOW_ARG_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    ArkUIPickerTextStyleStruct textStyleStruct;
    RefPtr<ResourceObject> textColorResObj;
    Color textColor = ParseTextColor(vm, runtimeCallInfo, COLOR_ARG_INDEX, textColorResObj,
        DEFAULT_TIME_PICKER_SELECTED_TEXT_COLOR, nativeNode, textStyleStruct.textColorSetByUser);

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSizeStr = ParseFontSize(vm, runtimeCallInfo, FONT_SIZE_ARG_INDEX, fontSizeResObj);

    std::string weight = ParseFontWeight(vm, fontWeightArg);

    std::string fontFamily;
    RefPtr<ResourceObject> fontFamilyResObj;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily, fontFamilyResObj) ||
        fontFamily.empty()) {
        fontFamily = DEFAULT_ERR_CODE;
    }
    int32_t styleVal = 0;
    if (!fontStyleArg->IsNull() && !fontStyleArg->IsUndefined()) {
        styleVal = fontStyleArg->Int32Value(vm);
    }

    RefPtr<ResourceObject> minFontSizeResObj;
    std::string minSize = ParseFontSize(vm, runtimeCallInfo, MIN_FONT_SIZE_ARG_INDEX, minFontSizeResObj);

    RefPtr<ResourceObject> maxFontSizeResObj;
    std::string maxSize = ParseFontSize(vm, runtimeCallInfo, MAX_FONT_SIZE_ARG_INDEX, maxFontSizeResObj);

    int32_t overflowVal = 0;
    if (!overflowArg->IsNull() && !overflowArg->IsUndefined() && overflowArg->IsNumber()) {
        overflowVal = overflowArg->Int32Value(vm);
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());

    textStyleStruct.textColor = textColor.GetValue();
    textStyleStruct.fontStyle = styleVal;
    textStyleStruct.textOverflow = overflowVal;
    textStyleStruct.fontInfo = fontInfo.c_str();
    textStyleStruct.minFontSize = minSize.c_str();
    textStyleStruct.maxFontSize = maxSize.c_str();
    textStyleStruct.fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    textStyleStruct.fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    textStyleStruct.textColorRawPtr = AceType::RawPtr(textColorResObj);
    textStyleStruct.minFontSizeRawPtr = AceType::RawPtr(minFontSizeResObj);
    textStyleStruct.maxFontSizeRawPtr = AceType::RawPtr(maxFontSizeResObj);
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerSelectedTextStyleWithResObj(nativeNode,
        &textStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(FONT_WEIGHT_ARG_INDEX);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(FONT_FAMILY_ARG_INDEX);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(FONT_STYLE_ARG_INDEX);
    Local<JSValueRef> overflowArg = runtimeCallInfo->GetCallArgRef(OVER_FLOW_ARG_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    ArkUIPickerTextStyleStruct textStyleStruct;
    RefPtr<ResourceObject> textColorResObj;
    Color textColor = ParseTextColor(vm, runtimeCallInfo, COLOR_ARG_INDEX, textColorResObj,
        DEFAULT_TIME_PICKER_TEXT_COLOR, nativeNode, textStyleStruct.textColorSetByUser);

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSizeStr = ParseFontSize(vm, runtimeCallInfo, FONT_SIZE_ARG_INDEX, fontSizeResObj);

    std::string weight = ParseFontWeight(vm, fontWeightArg);

    std::string fontFamily;
    RefPtr<ResourceObject> fontFamilyResObj;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily, fontFamilyResObj) ||
        fontFamily.empty()) {
        fontFamily = DEFAULT_ERR_CODE;
    }

    int32_t styleVal = 0;
    if (!fontStyleArg->IsNull() && !fontStyleArg->IsUndefined()) {
        styleVal = fontStyleArg->Int32Value(vm);
    }

    RefPtr<ResourceObject> minFontSizeResObj;
    std::string minSize = ParseFontSize(vm, runtimeCallInfo, MIN_FONT_SIZE_ARG_INDEX, minFontSizeResObj);

    RefPtr<ResourceObject> maxFontSizeResObj;
    std::string maxSize = ParseFontSize(vm, runtimeCallInfo, MAX_FONT_SIZE_ARG_INDEX, maxFontSizeResObj);

    int32_t overflowVal = 0;
    if (!overflowArg->IsNull() && !overflowArg->IsUndefined() && overflowArg->IsNumber()) {
        overflowVal = overflowArg->Int32Value(vm);
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());

    textStyleStruct.textColor = textColor.GetValue();
    textStyleStruct.fontStyle = styleVal;
    textStyleStruct.textOverflow = overflowVal;
    textStyleStruct.fontInfo = fontInfo.c_str();
    textStyleStruct.minFontSize = minSize.c_str();
    textStyleStruct.maxFontSize = maxSize.c_str();
    textStyleStruct.fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    textStyleStruct.fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    textStyleStruct.textColorRawPtr = AceType::RawPtr(textColorResObj);
    textStyleStruct.minFontSizeRawPtr = AceType::RawPtr(minFontSizeResObj);
    textStyleStruct.maxFontSizeRawPtr = AceType::RawPtr(maxFontSizeResObj);
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerDisappearTextStyleWithResObj(nativeNode,
        &textStyleStruct);
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
    RefPtr<ResourceObject> strokeWidthResObj;
    RefPtr<ResourceObject> colorResObj;
    RefPtr<ResourceObject> startMarginResObj;
    RefPtr<ResourceObject> endMarginResObj;
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, panda::NativePointerRef::New(vm, nullptr));
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::NativePointerRef::New(vm, nullptr));
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, panda::NativePointerRef::New(vm, nullptr));
    if (ParseDividerDimension(vm, dividerStrokeWidthArgs, dividerStrokeWidth, strokeWidthResObj)) {
        dividerStrokeWidth = pickerTheme ? pickerTheme->GetDividerThickness() : 0.0_vp;
    }

    ArkUI_Bool isDefaultColor = false;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, colorObj, colorResObj, nodeInfo)) {
        colorObj = pickerTheme ? pickerTheme->GetDividerColor() : Color::TRANSPARENT;
        isDefaultColor = true;
    }
    if (ParseDividerDimension(vm, dividerStartMarginArgs, dividerStartMargin, startMarginResObj)) {
        dividerStartMargin = 0.0_vp;
    }
    if (ParseDividerDimension(vm, dividerEndMarginArgs, dividerEndMargin, endMarginResObj)) {
        dividerEndMargin = 0.0_vp;
    }
    uint32_t size = ARG_GROUP_LENGTH;
    ArkUI_Float32 values[size];
    int32_t units[size];
    PopulateValues(dividerStrokeWidth, dividerStartMargin, dividerEndMargin, values, size);
    PopulateUnits(dividerStrokeWidth, dividerStartMargin, dividerEndMargin, units, size);

    ArkUIPickerDividerResObjStruct dividerResObjStr;
    dividerResObjStr.colorRawPtr = AceType::RawPtr(colorResObj);
    dividerResObjStr.strokeWidthRawPtr = AceType::RawPtr(strokeWidthResObj);
    dividerResObjStr.startMarginRawPtr = AceType::RawPtr(startMarginResObj);
    dividerResObjStr.endMarginRawPtr = AceType::RawPtr(endMarginResObj);
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerDividerWithResObj(
        nativeNode, colorObj.GetValue(), values, units, size, &dividerResObjStr, isDefaultColor);
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
    RefPtr<ResourceObject> heightResObj;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, itemHeightValue, height, heightResObj, true)) {
        auto heightRawPtr = AceType::RawPtr(heightResObj);
        GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerGradientHeightWithResObj(
            nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), heightRawPtr);
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(FONT_WEIGHT_ARG_INDEX);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(FONT_FAMILY_ARG_INDEX);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(FONT_STYLE_ARG_INDEX);
    Local<JSValueRef> overflowArg = runtimeCallInfo->GetCallArgRef(OVER_FLOW_ARG_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    ArkUIPickerTextStyleStruct textStyleStruct;
    RefPtr<ResourceObject> textColorResObj;
    Color textColor = ParseTextColor(vm, runtimeCallInfo, COLOR_ARG_INDEX, textColorResObj,
        DEFAULT_TIME_PICKER_TEXT_COLOR, nativeNode, textStyleStruct.textColorSetByUser);

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSize = ParseFontSize(vm, runtimeCallInfo, FONT_SIZE_ARG_INDEX, fontSizeResObj);

    std::string weight = ParseFontWeight(vm, fontWeightArg);

    RefPtr<ResourceObject> fontFamilyResObj;
    std::string fontFamily = ParseFontFamily(vm, fontFamilyArg, fontFamilyResObj);

    int32_t styleVal = 0;
    if (!fontStyleArg->IsNull() && !fontStyleArg->IsUndefined() && fontStyleArg->IsNumber()) {
        styleVal = fontStyleArg->Int32Value(vm);
    }

    RefPtr<ResourceObject> minFontSizeResObj;
    std::string minSize = ParseFontSize(vm, runtimeCallInfo, MIN_FONT_SIZE_ARG_INDEX, minFontSizeResObj);

    RefPtr<ResourceObject> maxFontSizeResObj;
    std::string maxSize = ParseFontSize(vm, runtimeCallInfo, MAX_FONT_SIZE_ARG_INDEX, maxFontSizeResObj);

    int32_t overflowVal = 0;
    if (!overflowArg->IsNull() && !overflowArg->IsUndefined() && overflowArg->IsNumber()) {
        overflowVal = overflowArg->Int32Value(vm);
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());

    textStyleStruct.textColor = textColor.GetValue();
    textStyleStruct.fontStyle = styleVal;
    textStyleStruct.textOverflow = overflowVal;
    textStyleStruct.fontInfo = fontInfo.c_str();
    textStyleStruct.minFontSize = minSize.c_str();
    textStyleStruct.maxFontSize = maxSize.c_str();
    textStyleStruct.fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    textStyleStruct.fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    textStyleStruct.textColorRawPtr = AceType::RawPtr(textColorResObj);
    textStyleStruct.minFontSizeRawPtr = AceType::RawPtr(minFontSizeResObj);
    textStyleStruct.maxFontSizeRawPtr = AceType::RawPtr(maxFontSizeResObj);
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerDefaultTextStyleWithResObj(
        nativeNode, &textStyleStruct);
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

ArkUINativeModuleValue TextPickerBridge::SetTextPickerSelectedBackgroundStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // frameNode
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1); // background color
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);

    ArkUI_Bool isHasValue[GETVALUE_MAX_SIZE] = {false, false, false, false, false};
    ArkUIPickerBackgroundStyleStruct backgroundStyleStruct;
    backgroundStyleStruct.colorValue = DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_COLOR;
    Color color;
    RefPtr<ResourceObject> colorResObj;
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
        isHasValue[GETCOLOR] = true;
        backgroundStyleStruct.isColorSetByUser = true;
        backgroundStyleStruct.colorValue = color.GetValue();
    }
    backgroundStyleStruct.colorRawPtr = AceType::RawPtr(colorResObj);

    RefPtr<ResourceObject> radiusResObjs[VALUE_MAX_SIZE] = {nullptr, nullptr, nullptr, nullptr};
    ParseSelectedBackgroundStyleRadius(vm, runtimeCallInfo, isHasValue, backgroundStyleStruct, radiusResObjs);
    backgroundStyleStruct.topLeftRawPtr = AceType::RawPtr(radiusResObjs[TOPLEFT]);
    backgroundStyleStruct.topRightRawPtr = AceType::RawPtr(radiusResObjs[TOPRIGHT]);
    backgroundStyleStruct.bottomLeftRawPtr = AceType::RawPtr(radiusResObjs[BOTTOMLEFT]);
    backgroundStyleStruct.bottomRightRawPtr = AceType::RawPtr(radiusResObjs[BOTTOMRIGHT]);

    auto modifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(modifiers, panda::NativePointerRef::New(vm, nullptr));
    auto textPickerModifier = modifiers->getTextPickerModifier();
    CHECK_NULL_RETURN(textPickerModifier, panda::NativePointerRef::New(vm, nullptr));
    textPickerModifier->setTextPickerSelectedBackgroundStyleWithResObj(nativeNode, isHasValue, &backgroundStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::ResetTextPickerSelectedBackgroundStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto modifier = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(modifier, panda::NativePointerRef::New(vm, nullptr));
    modifier->getTextPickerModifier()->resetTextPickerSelectedBackgroundStyle(nativeNode);
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
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
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
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
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
