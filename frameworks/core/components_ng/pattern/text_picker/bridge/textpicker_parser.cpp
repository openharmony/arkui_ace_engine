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
#include "core/components_ng/pattern/text_picker/bridge/textpicker_parser.h"

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
#include "frameworks/core/components_ng/pattern/text_picker/textpicker_properties.h"

namespace OHOS::Ace::NG {
namespace {
const char* TOP_START_PROPERTY = "topStart";
const char* TOP_END_PROPERTY = "topEnd";
const char* BOTTOM_START_PROPERTY = "bottomStart";
const char* BOTTOM_END_PROPERTY = "bottomEnd";
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };

bool GetResourceIdAndType(const EcmaVM* vm, const Local<panda::ObjectRef>& jsObj, int32_t& resId, int32_t& resType)
{
    auto id = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    auto type = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (!id->IsNumber() || !type->IsNumber()) {
        return false;
    }

    resId = id->Int32Value(vm);
    resType = type->Int32Value(vm);
    return true;
}

void SetBorderRadiusWithCheck(std::optional<BorderRadiusProperty>& result, BorderRadiusProperty& borderRadius)
{
    if (borderRadius.radiusTopLeft.has_value() && !borderRadius.radiusTopLeft->IsNegative() &&
        borderRadius.radiusTopRight.has_value() && !borderRadius.radiusTopRight->IsNegative() &&
        borderRadius.radiusBottomLeft.has_value() && !borderRadius.radiusBottomLeft->IsNegative() &&
        borderRadius.radiusBottomRight.has_value() && !borderRadius.radiusBottomRight->IsNegative()) {
        result = borderRadius;
    }
}

bool IsGetResourceByName(const EcmaVM* vm, const Local<JSValueRef>& jsObj)
{
    auto obj = jsObj->ToObject(vm);
    auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
    if (!args->IsArray(vm)) {
        return false;
    }
    auto bundleName = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
    auto moduleName = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
    if (!bundleName->IsString(vm) || !moduleName->IsString(vm)) {
        return false;
    }
    Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
    if (ArkTSUtils::GetArrayLength(vm, params) == 0) {
        return false;
    }
    return true;
}

bool CheckLengthMetrics(const EcmaVM* vm, const Local<panda::ObjectRef>& jsObject)
{
    if (jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "start")) ||
        jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "end")) ||
        jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "topStart")) ||
        jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "topEnd")) ||
        jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "bottomStart")) ||
        jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "bottomEnd"))) {
        return true;
    }
    auto jsTop = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "top"));
    if (jsTop->IsObject(vm)) {
        auto topObj = jsTop->ToObject(vm);
        if (topObj->Has(vm, panda::StringRef::NewFromUtf8(vm, "value"))) {
            return true;
        }
    }
    auto jsBottom = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "bottom"));
    if (jsBottom->IsObject(vm)) {
        auto bottomObj = jsBottom->ToObject(vm);
        if (bottomObj->Has(vm, panda::StringRef::NewFromUtf8(vm, "value"))) {
            return true;
        }
    }
    return false;
}
} // namespace

void TextPickerParser::ParseTextStyleFontSize(
    const EcmaVM* vm, const Local<JSValueRef>& fontSize, PickerTextStyle& textStyle)
{
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        textStyle.fontSize = Dimension(-1);
    } else {
        CalcDimension size;
        if (!ArkTSUtils::ParseJsDimensionFp(vm, fontSize, size, textStyle.fontSizeResObj) ||
            size.Unit() == DimensionUnit::PERCENT) {
            textStyle.fontSize = Dimension(-1);
        } else {
            textStyle.fontSize = size;
        }
    }
}

void TextPickerParser::ParseDefaultTextStyle(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, PickerTextStyle& textStyle)
{
    auto minFontSize = ArkTSUtils::GetProperty(vm, paramObj, "minFontSize");
    auto maxFontSize = ArkTSUtils::GetProperty(vm, paramObj, "maxFontSize");

    if (!minFontSize->IsNull() && !minFontSize->IsUndefined()) {
        CalcDimension minSize;
        if (ArkTSUtils::ParseJsDimensionFp(vm, minFontSize, minSize, textStyle.minFontSizeResObj) &&
            minSize.Unit() != DimensionUnit::PERCENT) {
            textStyle.minFontSize = minSize;
        }
    }
    if (!maxFontSize->IsNull() && !maxFontSize->IsUndefined()) {
        CalcDimension maxSize;
        if (ArkTSUtils::ParseJsDimensionFp(vm, maxFontSize, maxSize, textStyle.maxFontSizeResObj) &&
            maxSize.Unit() != DimensionUnit::PERCENT) {
            textStyle.maxFontSize = maxSize;
        }
    }
    auto overflow = ArkTSUtils::GetProperty(vm, paramObj, "overflow");
    if (!overflow->IsNull() && !overflow->IsUndefined()) {
        if (overflow->IsNumber()) {
            int32_t overflowValue = overflow->Int32Value(vm);
            if (overflowValue >= 0 && overflowValue < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
                textStyle.textOverflow = TEXT_OVERFLOWS[overflowValue];
            }
        }
    }
}

void TextPickerParser::IsUserDefinedFontFamily(const std::string& pos)
{
    if (pos == "disappearTextStyle") {
        GetArkUINodeModifiers()->getTextPickerModifier()->hasUserDefinedDisappearFontFamily(true);
    } else if (pos == "textStyle") {
        GetArkUINodeModifiers()->getTextPickerModifier()->hasUserDefinedNormalFontFamily(true);
    } else if (pos == "selectedTextStyle") {
        GetArkUINodeModifiers()->getTextPickerModifier()->hasUserDefinedSelectedFontFamily(true);
    }
}

void TextPickerParser::ParseTextStyle(
    const EcmaVM* vm, const Local<panda::ObjectRef>& secondArg, PickerTextStyle& textStyle, const std::string& pos)
{
    auto fontColor = ArkTSUtils::GetProperty(vm, secondArg, "color");
    auto fontOptions = ArkTSUtils::GetProperty(vm, secondArg, "font");

    Color textColor;
    if (ArkTSUtils::ParseJsColor(vm, fontColor, textColor, textStyle.textColorResObj)) {
        textStyle.textColor = textColor;
        textStyle.textColorSetByUser = true;
    }
    ParseDefaultTextStyle(vm, secondArg, textStyle);
    if (!fontOptions->IsObject(vm)) {
        return;
    }
    auto fontObj = fontOptions->ToObject(vm);
    auto fontSize = ArkTSUtils::GetProperty(vm, fontObj, "size");
    auto fontWeight = ArkTSUtils::GetProperty(vm, fontObj, "weight");
    auto fontFamily = ArkTSUtils::GetProperty(vm, fontObj, "family");
    auto fontStyle = ArkTSUtils::GetProperty(vm, fontObj, "style");
    ParseTextStyleFontSize(vm, fontSize, textStyle);
    if (!fontWeight->IsNull() && !fontWeight->IsUndefined()) {
        std::string weight;
        if (fontWeight->IsNumber()) {
            weight = std::to_string(static_cast<int32_t>(fontWeight->ToNumber(vm)->Value()));
        } else {
            ArkTSUtils::ParseJsString(vm, fontWeight, weight);
        }
        textStyle.fontWeight = Framework::ConvertStrToFontWeight(weight);
    }
    if (!fontFamily->IsNull() && !fontFamily->IsUndefined()) {
        std::vector<std::string> families;
        if (ArkTSUtils::ParseJsFontFamilies(vm, fontFamily, families, textStyle.fontFamilyResObj)) {
            textStyle.fontFamily = families;
            IsUserDefinedFontFamily(pos);
        }
    }

    if (fontStyle->IsNumber()) {
        auto style = fontStyle->ToNumber(vm)->Value();
        if (style < 0 || style > 1) {
            return;
        }
        textStyle.fontStyle = static_cast<FontStyle>(style);
    }
}

bool TextPickerParser::GenerateCascadeOptionsInternal(
    const EcmaVM* vm, const Local<panda::ObjectRef>& jsObj, std::vector<TextCascadePickerOptions>& options)
{
    TextCascadePickerOptions option;
    auto text = ArkTSUtils::GetProperty(vm, jsObj, "text");
    std::string textStr = "";
    if (ArkTSUtils::ParseJsString(vm, text, textStr, option.rangeResultResObj)) {
        option.rangeResult.emplace_back(textStr);
    } else {
        return false;
    }

    auto children = ArkTSUtils::GetProperty(vm, jsObj, "children");
    if (children->IsArray(vm)) {
        auto arrayChildren = panda::Local<panda::ArrayRef>(children);
        auto lengthValue = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, arrayChildren));
        if (lengthValue > 0) {
            if (!TextPickerParser::GenerateCascadeOptions(vm, arrayChildren, option.children)) {
                return false;
            }
        }
    }
    options.emplace_back(option);
    return true;
}

void TextPickerParser::SetSelectedValues(std::vector<uint32_t>& selectedValues, std::vector<std::string>& values,
    uint32_t index, bool isHasSelectAttr, std::vector<std::string>& resultStr)
{
    if (index + 1 > selectedValues.size()) {
        selectedValues.emplace_back(0);
    } else {
        if (selectedValues[index] >= resultStr.size()) {
            selectedValues[index] = 0;
        }
    }

    if (!isHasSelectAttr && selectedValues[index] == 0 && !values[index].empty()) {
        auto valueIterator = std::find(resultStr.begin(), resultStr.end(), values[index]);
        if (valueIterator != resultStr.end()) {
            auto localDistance = std::distance(resultStr.begin(), valueIterator);
            selectedValues[index] = localDistance > 0 ? static_cast<uint32_t>(localDistance) : 0;
        }
    }
}

bool TextPickerParser::GenerateCascadeOptions(
    const EcmaVM* vm, const Local<panda::ArrayRef>& array, std::vector<TextCascadePickerOptions>& options)
{
    auto length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, array));
    for (uint32_t i = 0; i < length; i++) {
        auto element = panda::ArrayRef::GetValueAt(vm, array, i);
        if (element->IsObject(vm)) {
            auto jsObj = element->ToObject(vm);
            if (!TextPickerParser::GenerateCascadeOptionsInternal(vm, jsObj, options)) {
                return false;
            }
        } else {
            options.clear();
            return false;
        }
    }
    return true;
}

bool TextPickerParser::ParseJsStrArray(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::vector<std::string>& result)
{
    RefPtr<ResourceObject> resObj;
    std::vector<RefPtr<ResourceObject>> resObjArray;
    return TextPickerParser::ParseJsStrArray(vm, jsValue, result, resObj, resObjArray);
}

bool TextPickerParser::ParseInternalArray(const EcmaVM* vm, const Local<panda::ArrayRef>& jsRangeValue,
    std::vector<uint32_t>& selectedValues, std::vector<std::string>& values, uint32_t index, bool isHasSelectAttr)
{
    std::vector<std::string> resultStr;
    auto length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, jsRangeValue));
    for (uint32_t i = 0; i < length; i++) {
        auto element = panda::ArrayRef::GetValueAt(vm, jsRangeValue, i);
        if (element->IsObject(vm)) {
            auto jsObj = element->ToObject(vm);
            auto getText = ArkTSUtils::GetProperty(vm, jsObj, "text");
            std::string textStr = "";
            if (ArkTSUtils::ParseJsString(vm, getText, textStr)) {
                resultStr.emplace_back(textStr);
            } else {
                return false;
            }
        }
    }
    if (index + 1 > values.size()) {
        if (resultStr.size() > 0) {
            values.emplace_back(resultStr.front());
        } else {
            values.emplace_back("");
        }
    } else {
        if (resultStr.size() > 0) {
            auto valueIterator = std::find(resultStr.begin(), resultStr.end(), values[index]);
            if (valueIterator == resultStr.end()) {
                values[index] = resultStr.front();
            }
        } else {
            values[index] = "";
        }
    }

    TextPickerParser::SetSelectedValues(selectedValues, values, index, isHasSelectAttr, resultStr);

    if (!panda::ArrayRef::GetValueAt(vm, jsRangeValue, selectedValues[index])->IsObject(vm)) {
        return true;
    }
    auto jsObj = panda::ArrayRef::GetValueAt(vm, jsRangeValue, selectedValues[index])->ToObject(vm);
    auto getChildren = ArkTSUtils::GetProperty(vm, jsObj, "children");
    if (getChildren->IsArray(vm)) {
        auto jsArray = panda::Local<panda::ArrayRef>(getChildren);
        ParseInternalArray(vm, jsArray, selectedValues, values, index + 1, isHasSelectAttr);
    }
    return true;
}

bool TextPickerParser::ParseMultiTextArrayRangeInternal(
    const EcmaVM* vm, const Local<JSValueRef>& value, std::vector<TextCascadePickerOptions>& options)
{
    if (value->IsArray(vm)) {
        TextCascadePickerOptions option;
        std::vector<RefPtr<ResourceObject>> resObjVector;
        if (!TextPickerParser::ParseJsStrArray(vm, value, option.rangeResult, option.rangeResultResObj, resObjVector)) {
            return false;
        } else {
            options.emplace_back(option);
        }
    } else {
        return false;
    }
    return true;
}

bool TextPickerParser::ParseMultiTextArrayRange(
    const EcmaVM* vm, const Local<panda::ArrayRef>& jsRangeValue, std::vector<NG::TextCascadePickerOptions>& options)
{
    options.clear();
    auto length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, jsRangeValue));
    if (length > 0) {
        for (size_t i = 0; i < length; i++) {
            auto value = panda::ArrayRef::GetValueAt(vm, jsRangeValue, i);
            if (!TextPickerParser::ParseMultiTextArrayRangeInternal(vm, value, options)) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

void TextPickerParser::ParseMultiTextArrayValueInternal(
    const std::vector<TextCascadePickerOptions>& options, std::vector<std::string>& values)
{
    for (uint32_t i = 0; i < options.size(); i++) {
        if (values.size() > 0 && values.size() < i + 1) {
            if (options[i].rangeResult.size() > 0) {
                values.emplace_back(options[i].rangeResult[0]);
            } else {
                values.emplace_back("");
            }
        } else if (i < values.size() && !options[i].rangeResult.empty()) {
            auto valueIterator = std::find(options[i].rangeResult.begin(), options[i].rangeResult.end(), values[i]);
            if (valueIterator == options[i].rangeResult.end()) {
                values[i] = options[i].rangeResult.front();
            }
        } else if (!options[i].rangeResult.empty()) {
            values.emplace_back(options[i].rangeResult[0]);
        } else {
            values.emplace_back("");
        }
    }
}

void TextPickerParser::ParseMultiTextArrayValueSingleInternal(
    const std::vector<TextCascadePickerOptions>& options, const std::string& value, std::vector<std::string>& values)
{
    if (options.size() > 0) {
        auto valueIterator = std::find(options[0].rangeResult.begin(), options[0].rangeResult.end(), value);
        if (valueIterator != options[0].rangeResult.end()) {
            values.emplace_back(value);
        } else {
            values.emplace_back(options[0].rangeResult.front());
        }
        for (uint32_t i = 1; i < options.size(); i++) {
            values.emplace_back(options[i].rangeResult.front());
        }
    } else {
        for (uint32_t i = 0; i < options.size(); i++) {
            values.emplace_back(options[i].rangeResult.front());
        }
    }
}

bool TextPickerParser::ParseMultiTextArrayValue(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, ParseTextArrayParam& param)
{
    if (jsValue->IsArray(vm)) {
        if (!TextPickerParser::ParseJsStrArray(vm, jsValue, param.values)) {
            return false;
        }
        TextPickerParser::ParseMultiTextArrayValueInternal(param.options, param.values);
    } else {
        std::string value;
        if (ArkTSUtils::ParseJsString(vm, jsValue, value)) {
            TextPickerParser::ParseMultiTextArrayValueSingleInternal(param.options, value, param.values);
        } else {
            for (uint32_t i = 0; i < param.options.size(); i++) {
                if (param.options[i].rangeResult.size() > 0) {
                    param.values.emplace_back(param.options[i].rangeResult.front());
                }
            }
        }
    }
    return true;
}

void TextPickerParser::ParseMultiTextArraySelectInternal(const std::vector<NG::TextCascadePickerOptions>& options,
    const std::vector<std::string>& values, std::vector<uint32_t>& selectedValues)
{
    uint32_t selectedValue = 0;
    auto sizeOfValues = values.size();
    for (uint32_t i = 0; i < options.size(); i++) {
        if ((sizeOfValues >= 0 && sizeOfValues < i + 1) || values[i].empty()) {
            selectedValues.emplace_back(0);
            continue;
        }

        auto valueIterator = std::find(options[i].rangeResult.begin(), options[i].rangeResult.end(), values[i]);
        if (valueIterator != options[i].rangeResult.end()) {
            selectedValue = static_cast<uint32_t>(std::distance(options[i].rangeResult.begin(), valueIterator));
            selectedValues.emplace_back(selectedValue);
        } else {
            selectedValues.emplace_back(0);
        }
    }
}

void TextPickerParser::ParseMultiTextArraySelectArrayInternal(
    const std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues)
{
    for (uint32_t i = 0; i < options.size(); i++) {
        if (selectedValues.size() > 0 && selectedValues.size() < i + 1) {
            selectedValues.emplace_back(0);
        } else {
            if (selectedValues[i] >= options[i].rangeResult.size()) {
                selectedValues[i] = 0;
            }
        }
    }
}

bool TextPickerParser::ParseMultiTextArraySelect(
    const EcmaVM* vm, const Local<JSValueRef>& jsSelectedValue, ParseTextArrayParam& param)
{
    if (jsSelectedValue->IsArray(vm)) {
        if (!ArkTSUtils::ParseJsIntegerArray(vm, jsSelectedValue, param.selecteds)) {
            return false;
        }
        TextPickerParser::ParseMultiTextArraySelectArrayInternal(param.options, param.selecteds);
    } else {
        uint32_t selectedValue = 0;
        if (ArkTSUtils::ParseJsInteger(vm, jsSelectedValue, selectedValue)) {
            if (param.options.size() < 1 || selectedValue >= param.options[0].rangeResult.size()) {
                selectedValue = 0;
            }
            param.selecteds.emplace_back(selectedValue);
            for (uint32_t i = 1; i < param.options.size(); i++) {
                param.selecteds.emplace_back(0);
            }
        } else {
            TextPickerParser::ParseMultiTextArraySelectInternal(param.options, param.values, param.selecteds);
        }
    }
    return true;
}

bool TextPickerParser::ParseMultiTextArray(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, ParseTextArrayParam& param)
{
    auto getSelected = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "selected"));
    auto getValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
    auto getRange = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "range"));
    auto getColumnWidths = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "columnWidths"));

    if (getRange->IsNull() || getRange->IsUndefined()) {
        return false;
    }
    if (!getRange->IsArray(vm)) {
        return false;
    }

    auto array = panda::Local<panda::ArrayRef>(getRange);
    if (!TextPickerParser::ParseMultiTextArrayRange(vm, array, param.options)) {
        return false;
    }
    if (getValue->IsObject(vm)) {
        auto valueObj = getValue->ToObject(vm);
        param.valueChangeEventVal = valueObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
        if (!param.valueChangeEventVal->IsUndefined() && param.valueChangeEventVal->IsFunction(vm)) {
            getValue = valueObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        }
    }
    if (!TextPickerParser::ParseMultiTextArrayValue(vm, getValue, param)) {
        return false;
    }

    if (getSelected->IsObject(vm)) {
        auto selectedObj = getSelected->ToObject(vm);
        param.selectedChangeEventVal = selectedObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
        if (!param.selectedChangeEventVal->IsUndefined() && param.selectedChangeEventVal->IsFunction(vm)) {
            getSelected = selectedObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        }
    }

    if (!TextPickerParser::ParseMultiTextArraySelect(vm, getSelected, param)) {
        return false;
    }
    if (!getColumnWidths->IsNull() && !getColumnWidths->IsUndefined()) {
        if (!TextPickerParser::ParseMultiColumnWidths(vm, getColumnWidths, param)) {
            return false;
        }
    }
    return true;
}

bool TextPickerParser::ParseCascadeTextArray(const EcmaVM* vm, const Local<panda::ObjectRef>& paramObject,
    ParseTextArrayParam& param, TextCascadePickerOptionsAttr& attr)
{
    std::vector<uint32_t>& selectedValues = param.selecteds;
    std::vector<std::string>& values = param.values;

    auto getRange = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "range"));
    auto getSelected = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "selected"));
    auto getValue = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
    if (getValue->IsArray(vm)) {
        RefPtr<ResourceObject> resObj;
        std::vector<RefPtr<ResourceObject>> resObjVector;
        if (!TextPickerParser::ParseJsStrArray(vm, getValue, values, resObj, resObjVector)) {
            return false;
        }

        if (resObjVector.size() > 0) {
            param.valueArrResObj = resObjVector;
        }
    } else {
        std::string value = "";
        if (!ArkTSUtils::ParseJsString(vm, getValue, value)) {
            value = "";
        }
        values.emplace_back(value);
    }
    if (getSelected->IsArray(vm)) {
        if (!ArkTSUtils::ParseJsIntegerArray(vm, getSelected, selectedValues)) {
            attr.isHasSelectAttr = false;
            return false;
        } else {
            attr.isHasSelectAttr = true;
        }
    } else {
        uint32_t selectValue = 0;
        if (!ArkTSUtils::ParseJsInteger(vm, getSelected, selectValue)) {
            selectValue = 0;
            attr.isHasSelectAttr = false;
        } else {
            attr.isHasSelectAttr = true;
        }
        selectedValues.emplace_back(selectValue);
    }
    auto jsArray = panda::Local<panda::ArrayRef>(getRange);
    return TextPickerParser::ParseInternalArray(vm, jsArray, selectedValues, values, 0, attr.isHasSelectAttr);
}

bool TextPickerParser::ParseJsStrArrayInternal(const EcmaVM* vm, const panda::Local<panda::ArrayRef>& jsArray,
    std::vector<std::string>& result, std::vector<RefPtr<ResourceObject>>& resObjArray)
{
    auto length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, jsArray));
    for (size_t i = 0; i < length; i++) {
        RefPtr<ResourceObject> resObj;
        auto value = panda::ArrayRef::GetValueAt(vm, jsArray, i);
        if (value->IsString(vm)) {
            result.emplace_back(value->ToString(vm)->ToString(vm));
        } else if (value->IsObject(vm)) {
            std::string singleResStr;
            if (ArkTSUtils::ParseJsString(vm, value, singleResStr, resObj)) {
                result.emplace_back(singleResStr);
            } else {
                resObjArray.clear();
                return false;
            }
        } else {
            resObjArray.clear();
            return false;
        }
        resObjArray.emplace_back(resObj);
    }
    return true;
}

bool TextPickerParser::ParseJsStrArray(const EcmaVM* vm, const Local<JSValueRef>& jsValue,
    std::vector<std::string>& result, RefPtr<ResourceObject>& resObj, std::vector<RefPtr<ResourceObject>>& resObjArray)
{
    if (!jsValue->IsArray(vm) && !jsValue->IsObject(vm)) {
        return false;
    }
    if (jsValue->IsArray(vm)) {
        auto jsArray = panda::Local<panda::ArrayRef>(jsValue);
        return TextPickerParser::ParseJsStrArrayInternal(vm, jsArray, result, resObjArray);
    }
    int32_t resIdNum;
    int32_t resType;
    auto jsObj = jsValue->ToObject(vm);
    ArkTSUtils::CompleteResourceObject(vm, jsObj);
    if (jsObj->IsNull() || !GetResourceIdAndType(vm, jsObj, resIdNum, resType)) {
        return false;
    }
    resObj = ArkTSUtils::GetResourceObject(vm, jsObj);
    auto resourceWrapper = ArkTSUtils::CreateJsResourceWrapper(vm, jsValue, resObj);
    if (!resourceWrapper) {
        return false;
    }
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, jsValue)) {
            return false;
        }
        auto args = ArkTSUtils::GetProperty(vm, jsObj, "params");
        if (!args->IsArray(vm)) {
            return false;
        }
        auto params = panda::Local<panda::ArrayRef>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        if (resType == static_cast<int32_t>(ResourceType::STRARRAY)) {
            result = resourceWrapper->GetStringArrayByName(param->ToString(vm)->ToString(vm));
            return true;
        }
        return false;
    }
    if (resType == static_cast<int32_t>(ResourceType::STRARRAY)) {
        result = resourceWrapper->GetStringArray(static_cast<uint32_t>(resIdNum));
        return true;
    }
    return false;
}

bool TextPickerParser::ParseJsLengthMetricsArray(const EcmaVM* vm, const Local<JSValueRef>& jsValue,
    std::vector<Dimension>& result, std::vector<RefPtr<ResourceObject>>& resObjArray)
{
    if (!jsValue->IsNull() && jsValue->IsArray(vm)) {
        auto arrayObj = panda::Local<panda::ArrayRef>(jsValue);
        auto length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, arrayObj));
        for (uint32_t i = 0; i < length; i++) {
            RefPtr<ResourceObject> resObj;
            auto value = panda::ArrayRef::GetValueAt(vm, arrayObj, i);
            Dimension calc;
            ArkTSUtils::ParseJsLengthMetricsToDimension(vm, value, calc, resObj);
            result.emplace_back(calc);
            resObjArray.emplace_back(resObj);
        }
        return true;
    }
    return false;
}

bool TextPickerParser::ParseMultiColumnWidths(
    const EcmaVM* vm, const Local<JSValueRef>& jsColumnWidthsValue, ParseTextArrayParam& param)
{
    if (jsColumnWidthsValue->IsArray(vm) && TextPickerParser::ParseJsLengthMetricsArray(vm, jsColumnWidthsValue,
                                                param.columnWidths, param.columnWidthResObjs)) {
        return true;
    }
    return false;
}

bool TextPickerParser::ParseColumnWidths(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObject, ParseTextArrayParam& param)
{
    auto getColumnWidths = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "columnWidths"));
    if (!getColumnWidths->IsNull() && !getColumnWidths->IsUndefined()) {
        if (!TextPickerParser::ParseMultiColumnWidths(vm, getColumnWidths, param)) {
            return false;
        }
    }
    return true;
}

bool TextPickerParser::ParseIconTextArray(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObject, ParseTextArrayParam& param)
{
    auto getSelected = ArkTSUtils::GetProperty(vm, paramObject, "selected");
    auto getRange = ArkTSUtils::GetProperty(vm, paramObject, "range");
    if (getRange->IsNull() || getRange->IsUndefined() || !getRange->IsArray(vm)) {
        return false;
    }

    auto array = panda::Local<panda::ArrayRef>(getRange);
    auto length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, array));
    param.result.clear();
    param.kind = 0;
    for (uint32_t i = 0; i < length; i++) {
        auto element = panda::ArrayRef::GetValueAt(vm, array, i);
        if (!element->IsObject(vm)) {
            continue;
        }
        auto jsObj = element->ToObject(vm);
        auto rangeIcon = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "icon"));
        auto rangeText = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "text"));
        RangeContent content;
        std::string icon;
        std::string text;
        RefPtr<ResourceObject> iconResObj;
        RefPtr<ResourceObject> textResObj;
        if (ArkTSUtils::ParseJsMedia(vm, rangeIcon, icon, iconResObj)) {
            content.icon_ = icon;
            param.kind |= ICON;
            content.iconResObj_ = iconResObj;
        }

        if (ArkTSUtils::ParseJsString(vm, rangeText, text, textResObj)) {
            content.text_ = text;
            param.kind |= TEXT;
            content.textResObj_ = textResObj;
        }
        param.result.emplace_back(content);
    }

    if (param.kind != ICON && param.kind != (ICON | TEXT)) {
        return false;
    }

    if (!ArkTSUtils::ParseJsInteger(vm, getSelected, param.selected)) {
        param.selected = 0;
    }

    if (!TextPickerParser::ParseColumnWidths(vm, paramObject, param)) {
        return false;
    }
    return true;
}

bool TextPickerParser::ParseTextArray(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, ParseTextArrayParam& param)
{
    auto getSelected = ArkTSUtils::GetProperty(vm, paramObj, "selected");
    auto getValue = ArkTSUtils::GetProperty(vm, paramObj, "value");
    auto getRange = ArkTSUtils::GetProperty(vm, paramObj, "range");

    std::vector<std::string> getRangeVector;

    if (!getRange->IsNull() && !getRange->IsUndefined()) {
        if (!TextPickerParser::ParseJsStrArray(vm, getRange, getRangeVector)) {
            return false;
        }
        param.result.clear();
        for (const auto& text : getRangeVector) {
            RangeContent content;
            content.icon_ = "";
            content.text_ = text;
            param.result.emplace_back(content);
        }

        param.kind = TEXT;

        if (!getValue->IsNull() && getValue->IsObject(vm)) {
            auto valueObj = getValue->ToObject(vm);
            param.valueChangeEventVal = ArkTSUtils::GetProperty(vm, valueObj, "changeEvent");
            if (!param.valueChangeEventVal->IsUndefined() && param.valueChangeEventVal->IsFunction(vm)) {
                getValue = ArkTSUtils::GetProperty(vm, valueObj, "value");
            }
        }

        bool valueParsed = ArkTSUtils::ParseJsString(vm, getValue, param.value, param.valueResObj);
        if (!valueParsed && !getRangeVector.empty()) {
            param.value = getRangeVector.front();
        }

        if (!getSelected->IsNull() && getSelected->IsObject(vm)) {
            auto selectedObj = getSelected->ToObject(vm);
            param.selectedChangeEventVal = ArkTSUtils::GetProperty(vm, selectedObj, "changeEvent");
            if (!param.selectedChangeEventVal->IsUndefined() && param.selectedChangeEventVal->IsFunction(vm)) {
                getSelected = ArkTSUtils::GetProperty(vm, selectedObj, "value");
            }
        }

        bool selectedParsed = ArkTSUtils::ParseJsInteger(vm, getSelected, param.selected);
        if (!selectedParsed && !param.value.empty()) {
            auto valueIterator = std::find(getRangeVector.begin(), getRangeVector.end(), param.value);
            if (valueIterator != getRangeVector.end()) {
                param.selected = static_cast<uint32_t>(std::distance(getRangeVector.begin(), valueIterator));
            }
        }

        if (param.selected >= getRangeVector.size()) {
            param.selected = 0;
        }

        if (!TextPickerParser::ParseColumnWidths(vm, paramObj, param)) {
            return false;
        }
    }

    return true;
}

void TextPickerParser::RegisterRadiusRes(BorderRadiusProperty& radius, RefPtr<ResourceObject> topStartResObj,
    RefPtr<ResourceObject> topEndResObj, RefPtr<ResourceObject> bottomStartResObj,
    RefPtr<ResourceObject> bottomEndResObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (topStartResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BorderRadiusProperty& radius) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            radius.radiusTopLeft = result;
            radius.multiValued = true;
        };
        radius.AddResource("radius.topStart", topStartResObj, std::move(updateFunc));
    } else {
        radius.RemoveResource("radius.topStart");
    }
    if (topEndResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BorderRadiusProperty& radius) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            radius.radiusTopRight = result;
            radius.multiValued = true;
        };
        radius.AddResource("radius.topEnd", topEndResObj, std::move(updateFunc));
    } else {
        radius.RemoveResource("radius.topEnd");
    }
    if (bottomStartResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BorderRadiusProperty& radius) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            radius.radiusBottomRight = result;
            radius.multiValued = true;
        };
        radius.AddResource("radius.bottomStart", bottomStartResObj, std::move(updateFunc));
    } else {
        radius.RemoveResource("radius.bottomStart");
    }
    if (bottomEndResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BorderRadiusProperty& radius) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            radius.radiusBottomLeft = result;
            radius.multiValued = true;
        };
        radius.AddResource("radius.bottomEnd", bottomEndResObj, std::move(updateFunc));
    } else {
        radius.RemoveResource("radius.bottomEnd");
    }
}

void TextPickerParser::ParseBorderRadiusProps(
    const EcmaVM* vm, const Local<panda::ObjectRef>& object, NG::BorderRadiusProperty& radius)
{
    std::optional<CalcDimension> radiusTopLeft;
    std::optional<CalcDimension> radiusTopRight;
    std::optional<CalcDimension> radiusBottomLeft;
    std::optional<CalcDimension> radiusBottomRight;
    CalcDimension topLeft;
    RefPtr<ResourceObject> topStartResObj;
    if (ArkTSUtils::ParseJsDimensionVpNG(
            vm, ArkTSUtils::GetProperty(vm, object, "topLeft"), topLeft, topStartResObj, true)) {
        radiusTopLeft = topLeft;
    }
    CalcDimension topRight;
    RefPtr<ResourceObject> topEndResObj;
    if (ArkTSUtils::ParseJsDimensionVpNG(
            vm, ArkTSUtils::GetProperty(vm, object, "topRight"), topRight, topEndResObj, true)) {
        radiusTopRight = topRight;
    }
    CalcDimension bottomLeft;
    RefPtr<ResourceObject> bottomStartResObj;
    if (ArkTSUtils::ParseJsDimensionVpNG(
            vm, ArkTSUtils::GetProperty(vm, object, "bottomLeft"), bottomLeft, bottomStartResObj, true)) {
        radiusBottomLeft = bottomLeft;
    }
    CalcDimension bottomRight;
    RefPtr<ResourceObject> bottomEndResObj;
    if (ArkTSUtils::ParseJsDimensionVpNG(
            vm, ArkTSUtils::GetProperty(vm, object, "bottomRight"), bottomRight, bottomEndResObj, true)) {
        radiusBottomRight = bottomRight;
    }
    CheckLengthMetrics(vm, object);
    radius.radiusTopLeft = radiusTopLeft;
    radius.radiusTopRight = radiusTopRight;
    radius.radiusBottomLeft = radiusBottomLeft;
    radius.radiusBottomRight = radiusBottomRight;
    radius.multiValued = true;
    TextPickerParser::RegisterRadiusRes(radius, topStartResObj, topEndResObj, bottomStartResObj, bottomEndResObj);
    return;
}

std::optional<CalcDimension> TextPickerParser::ParseBindSheetBorderRadiusProp(
    const EcmaVM* vm, const Local<panda::ObjectRef>& object, const char* prop, RefPtr<ResourceObject>& resourceObj)
{
    if (object.IsEmpty()) {
        return std::nullopt;
    }
    if (ArkTSUtils::HasProperty(vm, object, prop) && ArkTSUtils::GetProperty(vm, object, prop)->IsObject(vm)) {
        auto propObj = ArkTSUtils::GetProperty(vm, object, prop)->ToObject(vm);
        CalcDimension calcDimension;
        if (ArkTSUtils::ParseJsLengthMetrics(vm, propObj, calcDimension, resourceObj)) {
            return calcDimension;
        }
    }
    return std::nullopt;
}

bool TextPickerParser::ParseBindSheetBorderRadiusProps(
    const EcmaVM* vm, const Local<JSValueRef>& args, BorderRadiusProperty& radius)
{
    if (args->IsObject(vm)) {
        auto object = args->ToObject(vm);
        if (CheckLengthMetrics(vm, object)) {
            RefPtr<ResourceObject> topStartResObj;
            std::optional<CalcDimension> radiusTopStart =
                ParseBindSheetBorderRadiusProp(vm, object, TOP_START_PROPERTY, topStartResObj);
            RefPtr<ResourceObject> topEndResObj;
            std::optional<CalcDimension> radiusTopEnd =
                ParseBindSheetBorderRadiusProp(vm, object, TOP_END_PROPERTY, topEndResObj);
            RefPtr<ResourceObject> bottomStartResObj;
            std::optional<CalcDimension> radiusBottomStart =
                ParseBindSheetBorderRadiusProp(vm, object, BOTTOM_START_PROPERTY, bottomStartResObj);
            RefPtr<ResourceObject> bottomEndResObj;
            std::optional<CalcDimension> radiusBottomEnd =
                ParseBindSheetBorderRadiusProp(vm, object, BOTTOM_END_PROPERTY, bottomEndResObj);
            auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
            radius.radiusTopLeft = isRightToLeft ? radiusTopEnd : radiusTopStart;
            radius.radiusTopRight = isRightToLeft ? radiusTopStart : radiusTopEnd;
            radius.radiusBottomLeft = isRightToLeft ? radiusBottomEnd : radiusBottomStart;
            radius.radiusBottomRight = isRightToLeft ? radiusBottomStart : radiusBottomEnd;
            radius.multiValued = true;
            if (isRightToLeft) {
                TextPickerParser::RegisterRadiusRes(
                    radius, topEndResObj, topStartResObj, bottomEndResObj, bottomStartResObj);
            } else {
                TextPickerParser::RegisterRadiusRes(
                    radius, topStartResObj, topEndResObj, bottomStartResObj, bottomEndResObj);
            }
        } else {
            TextPickerParser::ParseBorderRadiusProps(vm, object, radius);
        }
        return true;
    }
    return false;
}

void TextPickerParser::ParsePickerBackgroundStyle(
    const EcmaVM* vm, const Local<JSValueRef>& paramObj, PickerBackgroundStyle& bgStyle)
{
    auto paramObject = paramObj->ToObject(vm);
    auto color = ArkTSUtils::GetProperty(vm, paramObject, "color");
    auto borderRadius = ArkTSUtils::GetProperty(vm, paramObject, "borderRadius");
    if (!color->IsUndefined() && !color->IsNull()) {
        Color buttonBgColor;
        if (ArkTSUtils::ParseJsColor(vm, color, buttonBgColor, bgStyle.colorResObj)) {
            bgStyle.color = buttonBgColor;
            bgStyle.textColorSetByUser = true;
        }
    }
    if (!borderRadius->IsUndefined() && !borderRadius->IsNull()) {
        CalcDimension calcDimension;
        BorderRadiusProperty borderRadiusProperty;
        if (ArkTSUtils::ParseLengthMetricsToDimension(vm, borderRadius, calcDimension, bgStyle.borderRadiusResObj)) {
            if (GreatOrEqual(calcDimension.Value(), 0.0f)) {
                bgStyle.borderRadius = BorderRadiusProperty(calcDimension);
            } else {
                bgStyle.borderRadiusResObj = nullptr;
            }
        } else if (TextPickerParser::ParseBindSheetBorderRadiusProps(vm, borderRadius, borderRadiusProperty)) {
            SetBorderRadiusWithCheck(bgStyle.borderRadius, borderRadiusProperty);
        }
    }
}
} // namespace OHOS::Ace::NG
