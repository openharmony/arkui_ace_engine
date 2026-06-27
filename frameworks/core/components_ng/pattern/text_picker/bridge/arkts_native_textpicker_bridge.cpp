/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_picker/bridge/arkts_native_textpicker_bridge.h"

#include "interfaces/inner_api/ace_kit/include/ui/base/utils/utils.h"
#include "jsnapi_expo.h"
#include "ui/base/ace_type.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_text_picker_theme.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_object.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/date_picker/picker_theme.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_types.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/i18n/time_format.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "frameworks/compatible/components/picker/picker_base_component.h"
#include "frameworks/core/components_ng/pattern/text_picker/bridge/textpicker_parser.h"
#include "frameworks/core/components_ng/pattern/text_picker/textpicker_properties.h"

namespace OHOS::Ace::NG {
namespace {
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_ERR_CODE = "-1";
const int32_t DEFAULT_NEGATIVE_NUM = -1;
const int32_t DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_BORDER_RADIUS = 24;
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
constexpr uint32_t DEFAULT_TIME_PICKER_TEXT_COLOR = 0xFF182431;
constexpr uint32_t DEFAULT_TIME_PICKER_SELECTED_TEXT_COLOR = 0xFF0A59F7;
constexpr uint32_t DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_COLOR = 0x0C182431;

constexpr int32_t NODE_INDEX = 0;

constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
constexpr int32_t STROKE_WIDTH_INDEX = 1;
constexpr int32_t COLOR_INDEX = 2;
constexpr int32_t START_MARGIN_INDEX = 3;
constexpr int32_t END_MARGIN_INDEX = 4;
constexpr int32_t UNIT_VP = 1;

constexpr int32_t ARG_GROUP_LENGTH = 3;
constexpr int PARAM_ARR_LENGTH_2 = 2;
constexpr int VALUE_MAX_SIZE = 4;
constexpr int GETVALUE_MAX_SIZE = 5;

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

bool ParseDividerDimension(
    const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& valueDim, RefPtr<ResourceObject>& resourceObject)
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

std::string ParseFontSize(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t argIndex, RefPtr<ResourceObject>& fontSizeResObj)
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

std::string ParseFontFamily(
    const EcmaVM* vm, const Local<JSValueRef>& fontFamilyArg, RefPtr<ResourceObject>& fontFamilyResObj)
{
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily, fontFamilyResObj) ||
        fontFamily.empty()) {
        fontFamily = DEFAULT_ERR_CODE;
    }
    return fontFamily;
}

Color ParseTextColor(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t argIndex,
    RefPtr<ResourceObject>& textColorResObj, uint32_t defaultTextColor, ArkUINodeHandle nativeNode,
    int32_t& isSetByUser)
{
    Color textColor;
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(argIndex);

    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (colorArg.IsNull() || colorArg->IsNull() || colorArg->IsUndefined() ||
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
    ArkUI_Float32 value[VALUE_MAX_SIZE] = { DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_BORDER_RADIUS,
        DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_BORDER_RADIUS, DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_BORDER_RADIUS,
        DEFAULT_TEXT_PICKER_SELECTED_BACKGROUND_BORDER_RADIUS };
    ArkUI_Int32 unit[VALUE_MAX_SIZE] = { UNIT_VP, UNIT_VP, UNIT_VP, UNIT_VP };
    auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    CalcDimension calcDimension;
    RefPtr<ResourceObject> tmpResObj;
    for (int i = 0; i < VALUE_MAX_SIZE; i++) {
        if (ArkTSUtils::ParseJsLengthMetrics(vm, runtimeCallInfo->GetCallArgRef(i + NUM_2), calcDimension, tmpResObj) &&
            !calcDimension.IsNegative()) {
            isHasValue[i + NUM_1] = true;
            value[i] = calcDimension.Value();
            unit[i] = static_cast<int>(calcDimension.Unit());
            radiusResObjs[i] = tmpResObj;
        }
        if (ArkTSUtils::ParseJsDimensionVp(vm, runtimeCallInfo->GetCallArgRef(i + NUM_2), calcDimension, tmpResObj) &&
            !calcDimension.IsNegative()) {
            isHasValue[i + NUM_1] = true;
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

void SetSelectedInternal(
    uint32_t count, std::vector<TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues)
{
    for (uint32_t i = 0; i < count; i++) {
        if (selectedValues.size() > 0 && selectedValues.size() < i + 1) {
            selectedValues.emplace_back(0);
        } else {
            if (selectedValues.size() > 0 && options.size() > 0 && selectedValues[i] >= options[i].rangeResult.size()) {
                selectedValues[i] = 0;
            }
        }
    }
}

void ProcessCascadeSelected(
    const std::vector<TextCascadePickerOptions>& options, uint32_t index, std::vector<uint32_t>& selectedValues)
{
    std::vector<std::string> rangeResultValue;
    for (size_t i = 0; i < options.size(); i++) {
        rangeResultValue.emplace_back(options[i].rangeResult[0]);
    }

    if (static_cast<int32_t>(index) > static_cast<int32_t>(selectedValues.size()) - 1) {
        selectedValues.emplace_back(0);
    }
    if (selectedValues[index] >= rangeResultValue.size()) {
        selectedValues[index] = 0;
    }
    if (static_cast<int32_t>(selectedValues[index]) <= static_cast<int32_t>(options.size()) - 1 &&
        options[selectedValues[index]].children.size() > 0) {
        ProcessCascadeSelected(options[selectedValues[index]].children, index + 1, selectedValues);
    }
}

void SetSelectedIndexMultiInternal(ArkUINodeHandle nativeNode, uint32_t count,
    std::vector<TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues)
{
    if (!GetArkUINodeModifiers()->getTextPickerModifier()->isJsCascade(nativeNode)) {
        SetSelectedInternal(count, options, selectedValues);
    } else {
        GetArkUINodeModifiers()->getTextPickerModifier()->setJsHasSelectAttr(nativeNode, true);
        ProcessCascadeSelected(options, 0, selectedValues);
        uint32_t maxCount = GetArkUINodeModifiers()->getTextPickerModifier()->getJsMaxCount();
        if (selectedValues.size() < maxCount) {
            auto differ = maxCount - selectedValues.size();
            for (uint32_t i = 0; i < differ; i++) {
                selectedValues.emplace_back(0);
            }
        }
    }
}

void SetSelectedIndexSingleInternal(const std::vector<TextCascadePickerOptions>& options, uint32_t count,
    uint32_t& selectedValue, std::vector<uint32_t>& selectedValues)
{
    if (options.size() > 0) {
        if (selectedValue >= options[0].rangeResult.size()) {
            selectedValue = 0;
        }
        selectedValues.emplace_back(selectedValue);
        for (uint32_t i = 1; i < count; i++) {
            selectedValues.emplace_back(0);
        }
    } else {
        for (uint32_t i = 0; i < count; i++) {
            selectedValues.emplace_back(0);
        }
    }
}

bool CheckDividerValue(const Dimension& dimension)
{
    if (dimension.Value() >= 0.0f && dimension.Unit() != DimensionUnit::PERCENT) {
        return true;
    }
    return false;
}

void ParseDivider(EcmaVM* vm, Local<panda::ObjectRef>& obj, ItemDivider& divider, ArkUINodeHandle nativeNode)
{
    CalcDimension defaultStrokeWidth = 0.0_vp;
    CalcDimension defaultMargin = 0.0_vp;
    Color defaultColor = Color::TRANSPARENT;

    CalcDimension strokeWidth = defaultStrokeWidth;
    RefPtr<ResourceObject> strokeWidthResObj;
    Local<JSValueRef> strokeWidthVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth"));
    if (ArkTSUtils::ConvertFromJSValueNG(vm, strokeWidthVal, strokeWidth, strokeWidthResObj) &&
        CheckDividerValue(strokeWidth)) {
        divider.strokeWidth = strokeWidth;
        divider.strokeWidthResObj = strokeWidthResObj;
    }

    Color color = defaultColor;
    RefPtr<ResourceObject> colorResObj;
    Local<JSValueRef> colorVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
    if (ArkTSUtils::ParseJsColor(vm, colorVal, color, colorResObj)) {
        divider.color = color;
        divider.colorResObj = colorResObj;
        divider.isDefaultColor = false;
    }

    CalcDimension startMargin = defaultMargin;
    RefPtr<ResourceObject> startMarginResObj;
    Local<JSValueRef> startMarginVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "startMargin"));
    if (ArkTSUtils::ConvertFromJSValueNG(vm, startMarginVal, startMargin, startMarginResObj) &&
        CheckDividerValue(startMargin)) {
        divider.startMargin = startMargin;
        divider.startMarginResObj = startMarginResObj;
    }

    CalcDimension endMargin = defaultMargin;
    RefPtr<ResourceObject> endMarginResObj;
    Local<JSValueRef> endMarginVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "endMargin"));
    if (ArkTSUtils::ConvertFromJSValueNG(vm, endMarginVal, endMargin, endMarginResObj) &&
        CheckDividerValue(endMargin)) {
        divider.endMargin = endMargin;
        divider.endMarginResObj = endMarginResObj;
    }
}

void ParseJsDefaultPickerItemHeight(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, Local<JSValueRef> secondArg)
{
    CalcDimension height;
    if (secondArg->IsNumber() || secondArg->IsString(vm)) {
        if (!ArkTSUtils::ParseJsDimensionFp(vm, secondArg, height)) {
            return;
        }
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerDefaultPickerItemHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()));
}

void SetJsOnChange(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode)
{
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        return;
    }
    Local<panda::FunctionRef> jsFunc = callbackArg->ToObject(vm);
    std::function<void(const std::vector<std::string>&, const std::vector<double>&)> onChange =
        [vm, func = panda::CopyableGlobal(vm, jsFunc)](
            const std::vector<std::string>& value, const std::vector<double>& index) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPicker.onChange");
            if (value.size() == 1 && index.size() == 1) {
                auto params = ArkTSUtils::ConvertToJSValues(vm, value[0], index[0]);
                auto result = func->Call(vm, func.ToLocal(), params.data(), static_cast<int32_t>(params.size()));
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            } else {
                panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2];
                auto valueArray = panda::ArrayRef::New(vm);
                for (size_t i = 0; i < value.size(); i++) {
                    panda::Local<panda::StringRef> item = panda::StringRef::NewFromUtf8(vm, value[i].c_str());
                    panda::ArrayRef::SetValueAt(vm, valueArray, i, item);
                }
                params[0] = valueArray;
                auto indexArray = panda::ArrayRef::New(vm);
                for (size_t i = 0; i < index.size(); i++) {
                    panda::Local<panda::NumberRef> item = panda::NumberRef::New(vm, index[i]);
                    panda::ArrayRef::SetValueAt(vm, indexArray, i, item);
                }
                params[1] = indexArray;
                auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerOnChange(
        nativeNode, reinterpret_cast<void*>(&onChange));
}

void SetJsOnScrollStop(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode)
{
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        return;
    }
    Local<panda::FunctionRef> jsFunc = callbackArg->ToObject(vm);
    std::function<void(const std::vector<std::string>&, const std::vector<double>&)> onScrollStop =
        [vm, func = panda::CopyableGlobal(vm, jsFunc)](
            const std::vector<std::string>& value, const std::vector<double>& index) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPicker.onScrollStop");
            if (value.size() == 1 && index.size() == 1) {
                auto params = ArkTSUtils::ConvertToJSValues(vm, value[0], index[0]);
                auto result = func->Call(vm, func.ToLocal(), params.data(), static_cast<int32_t>(params.size()));
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            } else {
                panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2];
                auto valueArray = panda::ArrayRef::New(vm);
                for (size_t i = 0; i < value.size(); i++) {
                    panda::Local<panda::StringRef> item = panda::StringRef::NewFromUtf8(vm, value[i].c_str());
                    panda::ArrayRef::SetValueAt(vm, valueArray, i, item);
                }
                params[0] = valueArray;
                auto indexArray = panda::ArrayRef::New(vm);
                for (size_t i = 0; i < index.size(); i++) {
                    panda::Local<panda::NumberRef> item = panda::NumberRef::New(vm, index[i]);
                    panda::ArrayRef::SetValueAt(vm, indexArray, i, item);
                }
                params[1] = indexArray;
                auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerOnScrollStop(
        nativeNode, reinterpret_cast<void*>(&onScrollStop));
}

ArkUINativeModuleValue SetJsGradientHeight(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode)
{
    CalcDimension height;
    RefPtr<ResourceObject> heightResObj;
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto pickerTheme = frameNode->GetTheme<PickerTheme>(true);
    Local<JSValueRef> arg1 = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (arg1->IsNull() || arg1->IsUndefined()) {
        if (pickerTheme) {
            height = pickerTheme->GetGradientHeight();
        } else {
            height = 0.0_vp;
        }
    } else {
        if (!ArkTSUtils::ParseJsDimensionVp(vm, arg1, height, heightResObj)) {
            if (pickerTheme) {
                height = pickerTheme->GetGradientHeight();
            }
        }
        if ((height.Unit() == DimensionUnit::PERCENT) && ((height.Value() > 1.0f) || (height.Value() < 0.0f))) {
            if (pickerTheme) {
                height = pickerTheme->GetGradientHeight();
            } else {
                height = 0.0_vp;
            }
        }
    }
    auto heightRawPtr = AceType::RawPtr(heightResObj);
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerGradientHeightWithResObj(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), heightRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

void SetSelectedIndexSingle(const EcmaVM* vm, const Local<JSValueRef>& jsSelectedValue, ArkUINodeHandle nativeNode)
{
    std::vector<RangeContent> rangeResult;
    GetArkUINodeModifiers()->getTextPickerModifier()->getJsSingleRange(nativeNode, &rangeResult);
    if (jsSelectedValue->IsArray(vm)) {
        std::vector<uint32_t> selectedValues;
        if (!ArkTSUtils::ParseJsIntegerArray(vm, jsSelectedValue, selectedValues)) {
            uint32_t selectedValue = 0;
            GetArkUINodeModifiers()->getTextPickerModifier()->setJsSelected(nativeNode, selectedValue);
            return;
        }
        if (selectedValues.size() > 0) {
            if (selectedValues[0] >= rangeResult.size()) {
                selectedValues[0] = 0;
            }
        } else {
            selectedValues.emplace_back(0);
        }

        GetArkUINodeModifiers()->getTextPickerModifier()->setJsSelected(nativeNode, selectedValues[0]);
    } else {
        uint32_t selectedValue = 0;
        if (ArkTSUtils::ParseJsInteger(vm, jsSelectedValue, selectedValue)) {
            if (selectedValue >= rangeResult.size()) {
                selectedValue = 0;
            }
        }
        GetArkUINodeModifiers()->getTextPickerModifier()->setJsSelected(nativeNode, selectedValue);
    }
}

void SetSelectedIndexMulti(const EcmaVM* vm, const Local<JSValueRef>& jsSelectedValue, ArkUINodeHandle nativeNode)
{
    std::vector<uint32_t> selectedValues;
    std::vector<TextCascadePickerOptions> options;
    GetArkUINodeModifiers()->getTextPickerModifier()->getJsMultiOptions(nativeNode, &options);
    auto count = GetArkUINodeModifiers()->getTextPickerModifier()->isJsCascade(nativeNode)
                     ? GetArkUINodeModifiers()->getTextPickerModifier()->getJsMaxCount()
                     : options.size();
    if (jsSelectedValue->IsArray(vm)) {
        if (!ArkTSUtils::ParseJsIntegerArray(vm, jsSelectedValue, selectedValues)) {
            selectedValues.clear();
            for (uint32_t i = 0; i < count; i++) {
                selectedValues.emplace_back(0);
            }
            GetArkUINodeModifiers()->getTextPickerModifier()->setJsSelecteds(
                nativeNode, selectedValues.data(), selectedValues.size());
            GetArkUINodeModifiers()->getTextPickerModifier()->setJsHasSelectAttr(nativeNode, false);
            return;
        }
        SetSelectedIndexMultiInternal(nativeNode, count, options, selectedValues);
    } else {
        uint32_t selectedValue = 0;
        if (ArkTSUtils::ParseJsInteger(vm, jsSelectedValue, selectedValue)) {
            GetArkUINodeModifiers()->getTextPickerModifier()->setJsHasSelectAttr(nativeNode, true);
            SetSelectedIndexSingleInternal(options, count, selectedValue, selectedValues);
        } else {
            selectedValues.clear();
            GetArkUINodeModifiers()->getTextPickerModifier()->setJsHasSelectAttr(nativeNode, false);
            for (uint32_t i = 0; i < count; i++) {
                selectedValues.emplace_back(0);
            }
        }
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setJsSelecteds(
        nativeNode, selectedValues.data(), selectedValues.size());
}

void SetJsEnableHapticFeedback(const EcmaVM* vm, Local<JSValueRef> enableHapticFeedbackArg, ArkUINodeHandle nativeNode)
{
    bool isEnableHapticFeedback = true;
    if (enableHapticFeedbackArg->IsBoolean()) {
        isEnableHapticFeedback = enableHapticFeedbackArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerEnableHapticFeedback(
        nativeNode, isEnableHapticFeedback);
}

size_t ProcessCascadeOptionDepth(const TextCascadePickerOptions& option)
{
    size_t depth = 1;
    if (option.children.size() == 0) {
        return depth;
    }

    for (auto&& pos : option.children) {
        size_t tmpDep = 1;
        tmpDep += ProcessCascadeOptionDepth(pos);
        if (tmpDep > depth) {
            depth = tmpDep;
        }
    }
    return depth;
}

bool ProcessCascadeOptions(const EcmaVM* vm, const Local<panda::ObjectRef>& paramObject, ParseTextArrayParam& param,
    TextCascadePickerOptionsAttr& attr)
{
    auto getRange = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "range"));
    if (getRange->IsNull() || getRange->IsUndefined()) {
        param.options.clear();
        return false;
    }
    if (!TextPickerParser::ParseCascadeTextArray(vm, paramObject, param, attr)) {
        param.options.clear();
        return false;
    } else {
        TextPickerParser::GenerateCascadeOptions(vm, getRange->ToObject(vm), param.options);
        uint32_t maxCount = param.options.empty() ? 0 : 1;
        for (size_t i = 0; i < param.options.size(); i++) {
            size_t tmp = ProcessCascadeOptionDepth(param.options[i]);
            if (tmp > maxCount) {
                maxCount = tmp;
            }
        }
        if (param.selecteds.size() < maxCount) {
            auto differ = maxCount - param.selecteds.size();
            for (uint32_t i = 0; i < differ; i++) {
                param.selecteds.emplace_back(0);
            }
        }
        if (param.values.size() < maxCount) {
            auto differ = maxCount - param.values.size();
            for (uint32_t i = 0; i < differ; i++) {
                param.values.emplace_back("");
            }
        }
        attr.isCascade = true;
        GetArkUINodeModifiers()->getTextPickerModifier()->setJsMaxCount(maxCount);
        if (!TextPickerParser::ParseColumnWidths(vm, paramObject, param)) {
            return false;
        }
    }
    return true;
}

bool ProcessSingleRangeValue(const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, ParseTextArrayParam& param)
{
    bool ret = true;
    auto getRange = ArkTSUtils::GetProperty(vm, paramObj, "range");
    if (getRange->IsNull() || getRange->IsUndefined()) {
        if (GetArkUINodeModifiers()->getTextPickerModifier()->getCreateSingleRange()) {
            return ret;
        }
        return false;
    }

    if (!TextPickerParser::ParseTextArray(vm, paramObj, param)) {
        if (!TextPickerParser::ParseIconTextArray(vm, paramObj, param)) {
            param.result.clear();
            ret = false;
        }
    }
    return ret;
}

void ParseTextPickerValueObject(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, const Local<JSValueRef>& changeEventVal)
{
    if (changeEventVal->IsUndefined() || !changeEventVal->IsFunction(vm)) {
        return;
    }
    panda::Local<panda::FunctionRef> jsFunc = changeEventVal->ToObject(vm);
    WeakPtr<FrameNode> targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    std::function<void(const std::vector<std::string>&)> callback =
        [vm, func = panda::CopyableGlobal(vm, jsFunc), node = targetNode](const std::vector<std::string>& value) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPicker.onValueChange");
            if (value.size() == NUM_1) {
                PipelineContext::SetCallBackNode(node);
                panda::Local<panda::StringRef> paramValue = StringToStringValueWithVM(vm, value[NUM_0].c_str());
                panda::Local<panda::JSValueRef> params[1] = { paramValue };
                auto result = func->Call(vm, func.ToLocal(), params, 1);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            } else {
                int32_t i = NUM_0;
                auto valueArray = panda::ArrayRef::New(vm);
                for (const std::string& str : value) {
                    panda::Local<panda::StringRef> item = StringToStringValueWithVM(vm, str.c_str());
                    panda::ArrayRef::SetValueAt(vm, valueArray, i++, item);
                }
                panda::Local<panda::JSValueRef> params[1] = { valueArray };
                PipelineContext::SetCallBackNode(node);
                auto result = func->Call(vm, func.ToLocal(), params, 1);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getTextPickerModifier()->setJsOnValueChangeEvent(reinterpret_cast<void*>(&callback));
}

void ParseTextPickerSelectedObject(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, const Local<JSValueRef>& changeEventVal)
{
    if (changeEventVal->IsUndefined() || !changeEventVal->IsFunction(vm)) {
        return;
    }
    panda::Local<panda::FunctionRef> jsFunc = changeEventVal->ToObject(vm);
    WeakPtr<FrameNode> targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    std::function<void(const std::vector<double>&)> callback =
        [vm, func = panda::CopyableGlobal(vm, jsFunc), node = targetNode](const std::vector<double>& index) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPicker.onSelectedChange");
            if (index.size() == NUM_1) {
                PipelineContext::SetCallBackNode(node);
                panda::Local<panda::NumberRef> paramIndex = panda::NumberRef::New(vm, index[NUM_0]);
                panda::Local<panda::JSValueRef> params[1] = { paramIndex };
                auto result = func->Call(vm, func.ToLocal(), params, 1);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            } else {
                int32_t i = NUM_0;
                auto indexArray = panda::ArrayRef::New(vm);
                for (const double& it : index) {
                    panda::Local<panda::NumberRef> item = panda::NumberRef::New(vm, it);
                    panda::ArrayRef::SetValueAt(vm, indexArray, i++, item);
                }
                PipelineContext::SetCallBackNode(node);
                panda::Local<panda::JSValueRef> params[1] = { indexArray };
                auto result = func->Call(vm, func.ToLocal(), params, 1);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getTextPickerModifier()->setJsOnSelectedChangeEvent(reinterpret_cast<void*>(&callback));
}
} // namespace

ArkUINativeModuleValue TextPickerBridge::CreateTextPicker(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto argsNumber = runtimeCallInfo->GetArgsNumber();
    ParseTextArrayParam param;
    TextCascadePickerOptionsAttr optionsAttr;
    if (argsNumber >= NUM_1 && runtimeCallInfo->GetCallArgRef(0)->IsObject(vm)) {
        Local<panda::ObjectRef> paramObject = runtimeCallInfo->GetCallArgRef(0)->ToObject(vm);
        bool optionsMultiContentCheckErr = false;
        bool optionsCascadeContentCheckErr = false;
        auto isSingleRange = ProcessSingleRangeValue(vm, paramObject, param);
        GetArkUINodeModifiers()->getTextPickerModifier()->setJsSingleRange(isSingleRange);
        if (!isSingleRange) {
            if (!TextPickerParser::ParseMultiTextArray(vm, paramObject, param)) {
                param.options.clear();
                optionsMultiContentCheckErr = true;
            }
            if (optionsMultiContentCheckErr) {
                optionsCascadeContentCheckErr = !ProcessCascadeOptions(vm, paramObject, param, optionsAttr);
            }
        }
        if (!isSingleRange && optionsMultiContentCheckErr && optionsCascadeContentCheckErr) {
            param.result.clear();
            param.options.clear();
            auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
            bool firstBuild = targetNode && targetNode->IsFirstBuilding();
            if (!firstBuild) {
                return panda::JSValueRef::Undefined(vm);
            }
        }
    }
    if (!param.result.empty()) {
        GetArkUINodeModifiers()->getTextPickerModifier()->createJsSingle(&param);
    } else {
        GetArkUINodeModifiers()->getTextPickerModifier()->createJsMulti(&optionsAttr, &param);
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setJsDefaultAttributes();
    if (!param.valueChangeEventVal.IsEmpty() && !param.valueChangeEventVal->IsUndefined() &&
        param.valueChangeEventVal->IsFunction(vm)) {
        ParseTextPickerValueObject(vm, runtimeCallInfo, param.valueChangeEventVal);
    }
    if (!param.selectedChangeEventVal.IsEmpty() && !param.selectedChangeEventVal->IsUndefined() &&
        param.selectedChangeEventVal->IsFunction(vm)) {
        ParseTextPickerSelectedObject(vm, runtimeCallInfo, param.selectedChangeEventVal);
    }
    return panda::JSValueRef::Undefined(vm);
}

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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> overflowArg = runtimeCallInfo->GetCallArgRef(NUM_8);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    ArkUIPickerTextStyleStruct textStyleStruct;
    RefPtr<ResourceObject> textColorResObj;
    Color textColor = ParseTextColor(vm, runtimeCallInfo, NUM_1, textColorResObj, DEFAULT_TIME_PICKER_TEXT_COLOR,
        nativeNode, textStyleStruct.textColorSetByUser);

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSizeStr = ParseFontSize(vm, runtimeCallInfo, NUM_2, fontSizeResObj);

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
    std::string minSize = ParseFontSize(vm, runtimeCallInfo, NUM_6, minFontSizeResObj);

    RefPtr<ResourceObject> maxFontSizeResObj;
    std::string maxSize = ParseFontSize(vm, runtimeCallInfo, NUM_7, maxFontSizeResObj);

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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> overflowArg = runtimeCallInfo->GetCallArgRef(NUM_8);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    ArkUIPickerTextStyleStruct textStyleStruct;
    RefPtr<ResourceObject> textColorResObj;
    Color textColor = ParseTextColor(vm, runtimeCallInfo, NUM_1, textColorResObj,
        DEFAULT_TIME_PICKER_SELECTED_TEXT_COLOR, nativeNode, textStyleStruct.textColorSetByUser);

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSizeStr = ParseFontSize(vm, runtimeCallInfo, NUM_2, fontSizeResObj);

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
    std::string minSize = ParseFontSize(vm, runtimeCallInfo, NUM_6, minFontSizeResObj);

    RefPtr<ResourceObject> maxFontSizeResObj;
    std::string maxSize = ParseFontSize(vm, runtimeCallInfo, NUM_7, maxFontSizeResObj);

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
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerSelectedTextStyleWithResObj(
        nativeNode, &textStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> overflowArg = runtimeCallInfo->GetCallArgRef(NUM_8);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    ArkUIPickerTextStyleStruct textStyleStruct;
    RefPtr<ResourceObject> textColorResObj;
    Color textColor = ParseTextColor(vm, runtimeCallInfo, NUM_1, textColorResObj, DEFAULT_TIME_PICKER_TEXT_COLOR,
        nativeNode, textStyleStruct.textColorSetByUser);

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSizeStr = ParseFontSize(vm, runtimeCallInfo, NUM_2, fontSizeResObj);
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
    std::string minSize = ParseFontSize(vm, runtimeCallInfo, NUM_6, minFontSizeResObj);

    RefPtr<ResourceObject> maxFontSizeResObj;
    std::string maxSize = ParseFontSize(vm, runtimeCallInfo, NUM_7, maxFontSizeResObj);

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
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerDisappearTextStyleWithResObj(
        nativeNode, &textStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetDefaultPickerItemHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> itemHeightValue = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (isJsView) {
        ParseJsDefaultPickerItemHeight(vm, runtimeCallInfo, nativeNode, itemHeightValue);
        return panda::JSValueRef::Undefined(vm);
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(nodeArg, vm)) {
        SetJsGradientHeight(vm, runtimeCallInfo, nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> overflowArg = runtimeCallInfo->GetCallArgRef(NUM_8);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    ArkUIPickerTextStyleStruct textStyleStruct;
    RefPtr<ResourceObject> textColorResObj;
    Color textColor = ParseTextColor(vm, runtimeCallInfo, NUM_1, textColorResObj, DEFAULT_TIME_PICKER_TEXT_COLOR,
        nativeNode, textStyleStruct.textColorSetByUser);

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSize = ParseFontSize(vm, runtimeCallInfo, NUM_2, fontSizeResObj);

    std::string weight = ParseFontWeight(vm, fontWeightArg);

    RefPtr<ResourceObject> fontFamilyResObj;
    std::string fontFamily = ParseFontFamily(vm, fontFamilyArg, fontFamilyResObj);

    int32_t styleVal = 0;
    if (!fontStyleArg->IsNull() && !fontStyleArg->IsUndefined() && fontStyleArg->IsNumber()) {
        styleVal = fontStyleArg->Int32Value(vm);
    }

    RefPtr<ResourceObject> minFontSizeResObj;
    std::string minSize = ParseFontSize(vm, runtimeCallInfo, NUM_6, minFontSizeResObj);

    RefPtr<ResourceObject> maxFontSizeResObj;
    std::string maxSize = ParseFontSize(vm, runtimeCallInfo, NUM_7, maxFontSizeResObj);

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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);                 // framenode
    Local<JSValueRef> enableHapticFeedbackArg = runtimeCallInfo->GetCallArgRef(1); // isEnableHapticFeedback
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    if (ArkTSUtils::IsJsView(nodeArg, vm)) {
        SetJsEnableHapticFeedback(vm, enableHapticFeedbackArg, nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);  // frameNode
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1); // background color
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);

    ArkUI_Bool isHasValue[GETVALUE_MAX_SIZE] = { false, false, false, false, false };
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

    RefPtr<ResourceObject> radiusResObjs[VALUE_MAX_SIZE] = { nullptr, nullptr, nullptr, nullptr };
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    int32_t crownSensitivity = DEFAULT_CROWNSENSITIVITY;
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(nativeNodeArg, vm)) {
        SetJsOnChange(vm, runtimeCallInfo, nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(nativeNodeArg, vm)) {
        SetJsOnScrollStop(vm, runtimeCallInfo, nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
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

ArkUINativeModuleValue TextPickerBridge::SetJsDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto theme = frameNode->GetTheme<PickerTheme>(true);
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    PickerTextStyle textStyle;
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        Framework::JSTextPickerTheme::ObtainTextStyle(textStyle);
    }
    if (secondArg->IsObject(vm)) {
        auto arg = secondArg->ToObject(vm);
        TextPickerParser::ParseTextStyle(vm, arg, textStyle, "disappearTextStyle");
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setJsDisappearTextStyle(nativeNode, &textStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetJsTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    PickerTextStyle textStyle;
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        Framework::JSTextPickerTheme::ObtainTextStyle(textStyle);
    }
    if (secondArg->IsObject(vm)) {
        auto arg = secondArg->ToObject(vm);
        TextPickerParser::ParseTextStyle(vm, arg, textStyle, "textStyle");
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setJsNormalTextStyle(nativeNode, &textStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetJsSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    PickerTextStyle textStyle;
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        Framework::JSTextPickerTheme::ObtainSelectedTextStyle(textStyle);
    }
    if (secondArg->IsObject(vm)) {
        auto arg = secondArg->ToObject(vm);
        TextPickerParser::ParseTextStyle(vm, arg, textStyle, "selectedTextStyle");
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setJsSelectedTextStyle(nativeNode, &textStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetJsDefaultTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    PickerTextStyle textStyle;
    if (secondArg->IsObject(vm)) {
        auto arg = secondArg->ToObject(vm);
        TextPickerParser::ParseTextStyle(vm, arg, textStyle, "defaultTextStyle");
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setJsDefaultTextStyle(nativeNode, &textStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetOnEnterSelectedArea(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::FunctionRef> jsFunc = callbackArg->ToObject(vm);
    std::function<void(const std::vector<std::string>&, const std::vector<double>&)> onChange =
        [vm, func = panda::CopyableGlobal(vm, jsFunc)](
            const std::vector<std::string>& value, const std::vector<double>& index) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPicker.onEnterSelectedArea");
            if (value.size() == 1 && index.size() == 1) {
                auto params = ArkTSUtils::ConvertToJSValues(vm, value[0], index[0]);
                auto result = func->Call(vm, func.ToLocal(), params.data(), static_cast<int32_t>(params.size()));
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            } else {
                panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2];
                auto valueArray = panda::ArrayRef::New(vm);
                for (size_t i = 0; i < value.size(); i++) {
                    panda::Local<panda::StringRef> item = panda::StringRef::NewFromUtf8(vm, value[i].c_str());
                    panda::ArrayRef::SetValueAt(vm, valueArray, i, item);
                }
                params[0] = valueArray;
                auto indexArray = panda::ArrayRef::New(vm);
                for (size_t i = 0; i < index.size(); i++) {
                    panda::Local<panda::NumberRef> item = panda::NumberRef::New(vm, index[i]);
                    panda::ArrayRef::SetValueAt(vm, indexArray, i, item);
                }
                params[1] = indexArray;
                auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getTextPickerModifier()->setOnEnterSelectedArea(
        nativeNode, reinterpret_cast<void*>(&onChange));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetJsBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color backgroundColor;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, backgroundColor)) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setTextPickerBackgroundColor(
        nativeNode, backgroundColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextPickerModifier()->hasUserDefinedOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetJsDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();

    ItemDivider divider;
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto pickerTheme = frameNode->GetTheme<PickerTheme>(true);
    Dimension defaultStrokeWidth = 0.0_vp;
    Color defaultColor = Color::TRANSPARENT;
    if (pickerTheme) {
        defaultStrokeWidth = pickerTheme->GetDividerThickness();
        defaultColor = pickerTheme->GetDividerColor();
        divider.strokeWidth = defaultStrokeWidth;
        divider.color = defaultColor;
        divider.isDefaultColor = true;
    }

    if (argsNumber >= NUM_2 && secondArg->IsObject(vm)) {
        auto obj = secondArg->ToObject(vm);
        ParseDivider(vm, obj, divider, nativeNode);
    } else if (argsNumber >= NUM_2 && secondArg->IsNull()) {
        divider.strokeWidth = 0.0_vp;
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setJsDivider(nativeNode, &divider);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetJsSelectedIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto jsSelectedValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (jsSelectedValue->IsUndefined() || jsSelectedValue->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }

    if (GetArkUINodeModifiers()->getTextPickerModifier()->isSingle(nativeNode)) {
        SetSelectedIndexSingle(vm, jsSelectedValue, nativeNode);
    } else {
        SetSelectedIndexMulti(vm, jsSelectedValue, nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextPickerBridge::SetJsSelectedBackgroundStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (secondArg->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto pickerTheme = frameNode->GetTheme<PickerTheme>(true);
    PickerBackgroundStyle backgroundStyle;
    if (secondArg->IsObject(vm)) {
        TextPickerParser::ParsePickerBackgroundStyle(vm, secondArg, backgroundStyle);
    }
    GetArkUINodeModifiers()->getTextPickerModifier()->setJsSelectedBackgroundStyle(nativeNode, &backgroundStyle);
    return panda::JSValueRef::Undefined(vm);
}

void TextPickerBridge::RegisterTextPickerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setCanLoop", "setSelectedIndex", "setTextStyle", "setSelectedTextStyle",
        "setDisappearTextStyle", "setDefaultPickerItemHeight", "setBackgroundColor", "resetCanLoop",
        "resetSelectedIndex", "resetTextStyle", "resetSelectedTextStyle", "resetDisappearTextStyle",
        "resetDefaultPickerItemHeight", "resetBackgroundColor", "setDivider", "resetDivider", "setGradientHeight",
        "resetGradientHeight", "setDisableTextStyleAnimation", "resetDisableTextStyleAnimation", "setDefaultTextStyle",
        "resetDefaultTextStyle", "setTextpickerEnableHapticFeedback", "resetTextpickerEnableHapticFeedback",
        "setOnChange", "resetOnChange", "setOnScrollStop", "resetOnScrollStop", "setTextpickerSelectedBackgroundStyle",
        "resetTextpickerSelectedBackgroundStyle", "setDigitalCrownSensitivity", "resetDigitalCrownSensitivity",
        "setJsDisappearTextStyle", "setJsTextStyle", "setJsSelectedTextStyle", "setJsDefaultTextStyle",
        "setOnEnterSelectedArea", "setJsBackgroundColor", "setOpacity", "setJsDivider", "setJsSelectedIndex",
        "setJsSelectedBackgroundStyle" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::CreateTextPicker),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetCanLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetSelectedIndex),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetSelectedTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDisappearTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDefaultPickerItemHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetCanLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetSelectedIndex),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetSelectedTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDisappearTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDefaultPickerItemHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetGradientHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetGradientHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDisableTextStyleAnimation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDisableTextStyleAnimation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDefaultTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDefaultTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetTextPickerEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetTextPickerEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetOnScrollStop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetOnScrollStop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetTextPickerSelectedBackgroundStyle),
        panda::FunctionRef::New(
            const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetTextPickerSelectedBackgroundStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDigitalCrownSensitivity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDigitalCrownSensitivity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetJsDisappearTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetJsTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetJsSelectedTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetJsDefaultTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetOnEnterSelectedArea),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetJsBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetOpacity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetJsDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetJsSelectedIndex),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetJsSelectedBackgroundStyle),

    };

    auto textPicker = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textpicker"), textPicker);
}
} // namespace OHOS::Ace::NG
