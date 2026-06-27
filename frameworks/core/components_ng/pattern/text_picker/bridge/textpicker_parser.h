/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_BRIDGE_TEXTPICKER_PARSER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_BRIDGE_TEXTPICKER_PARSER_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "core/components_ng/pattern/text_picker/textpicker_types.h"

namespace OHOS::Ace::NG {
struct TextCascadePickerOptions;
struct ParseTextArrayParam {
    std::vector<RangeContent> result;
    uint32_t kind = TEXT;
    uint32_t selected = 0;
    std::vector<Dimension> columnWidths;
    std::string value;
    std::vector<TextCascadePickerOptions> options;
    std::vector<uint32_t> selecteds;
    std::vector<std::string> values;
    Local<JSValueRef> valueChangeEventVal;
    Local<JSValueRef> selectedChangeEventVal;
    RefPtr<ResourceObject> resultResObj;
    RefPtr<ResourceObject> valueResObj;
    std::vector<RefPtr<ResourceObject>> columnWidthResObjs;
    std::vector<RefPtr<ResourceObject>> valueArrResObj;
};
struct TextPickerOptions {
    std::vector<RangeContent> range;
    uint32_t kind = 0;
    uint32_t selected = 0;
    std::string value = "";
    std::vector<TextCascadePickerOptions> options;
    std::vector<uint32_t> selecteds;
    std::vector<std::string> values;
    std::vector<Dimension> columnWidths;
    bool hasValue = false;
    bool hasSelected = false;
    bool isCascade = false;
    uint32_t maxCount = 0;
};
void ValidateSingleTextPickerOptions(TextPickerOptions& options);
void ValidateMultiTextPickerOptions(TextPickerOptions& options);
class TextPickerParser {
public:
    static void ParseTextStyleFontSize(const EcmaVM* vm, const Local<JSValueRef>& fontSize, PickerTextStyle& textStyle);
    static void ParseDefaultTextStyle(
        const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, PickerTextStyle& textStyle);
    static void IsUserDefinedFontFamily(const std::string& pos);
    static void ParsePickerBackgroundStyle(
        const EcmaVM* vm, const Local<JSValueRef>& paramObj, PickerBackgroundStyle& bgStyle);
    static void ParseTextStyle(
        const EcmaVM* vm, const Local<panda::ObjectRef>& secondArg, PickerTextStyle& textStyle, const std::string& pos);
    static bool GenerateCascadeOptionsInternal(
        const EcmaVM* vm, const Local<panda::ObjectRef>& jsObj, std::vector<TextCascadePickerOptions>& options);
    static void SetSelectedValues(std::vector<uint32_t>& selectedValues, std::vector<std::string>& values,
        uint32_t index, bool isHasSelectAttr, std::vector<std::string>& resultStr);
    static bool GenerateCascadeOptions(
        const EcmaVM* vm, const Local<panda::ArrayRef>& array, std::vector<TextCascadePickerOptions>& options);
    static bool ParseJsStrArray(const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::vector<std::string>& result);
    static bool ParseInternalArray(const EcmaVM* vm, const Local<panda::ArrayRef>& jsRangeValue,
        std::vector<uint32_t>& selectedValues, std::vector<std::string>& values, uint32_t index, bool isHasSelectAttr);
    static bool ParseMultiTextArrayRangeInternal(
        const EcmaVM* vm, const Local<JSValueRef>& value, std::vector<TextCascadePickerOptions>& options);
    static bool ParseMultiTextArrayRange(const EcmaVM* vm, const Local<panda::ArrayRef>& jsRangeValue,
        std::vector<NG::TextCascadePickerOptions>& options);
    static void ParseMultiTextArrayValueInternal(
        const std::vector<TextCascadePickerOptions>& options, std::vector<std::string>& values);
    static void ParseMultiTextArrayValueSingleInternal(const std::vector<TextCascadePickerOptions>& options,
        const std::string& value, std::vector<std::string>& values);
    static bool ParseMultiTextArrayValue(
        const EcmaVM* vm, const Local<JSValueRef>& jsValue, ParseTextArrayParam& param);
    static void ParseMultiTextArraySelectInternal(const std::vector<TextCascadePickerOptions>& options,
        const std::vector<std::string>& values, std::vector<uint32_t>& selectedValues);
    static void ParseMultiTextArraySelectArrayInternal(
        const std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues);
    static bool ParseMultiTextArraySelect(
        const EcmaVM* vm, const Local<JSValueRef>& jsSelectedValue, ParseTextArrayParam& param);
    static bool ParseMultiTextArray(
        const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, ParseTextArrayParam& param);
    static bool ParseCascadeTextArray(const EcmaVM* vm, const Local<panda::ObjectRef>& paramObject,
        ParseTextArrayParam& param, TextCascadePickerOptionsAttr& attr);
    static bool ParseJsStrArrayInternal(const EcmaVM* vm, const panda::Local<panda::ArrayRef>& jsArray,
        std::vector<std::string>& result, std::vector<RefPtr<ResourceObject>>& resObjArray);
    static bool ParseJsStrArray(const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::vector<std::string>& result,
        RefPtr<ResourceObject>& resObj, std::vector<RefPtr<ResourceObject>>& resObjArray);
    static bool ParseJsLengthMetricsArray(const EcmaVM* vm, const Local<JSValueRef>& jsValue,
        std::vector<Dimension>& result, std::vector<RefPtr<ResourceObject>>& resObjArray);
    static bool ParseMultiColumnWidths(
        const EcmaVM* vm, const Local<JSValueRef>& jsColumnWidthsValue, ParseTextArrayParam& param);
    static bool ParseColumnWidths(
        const EcmaVM* vm, const Local<panda::ObjectRef>& paramObject, ParseTextArrayParam& param);
    static bool ParseTextArray(const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, ParseTextArrayParam& param);
    static bool ParseIconTextArray(
        const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, ParseTextArrayParam& param);
    static std::optional<CalcDimension> ParseBindSheetBorderRadiusProp(
        const EcmaVM* vm, const Local<panda::ObjectRef>& object, const char* prop, RefPtr<ResourceObject>& resourceObj);
    static void RegisterRadiusRes(BorderRadiusProperty& radius, RefPtr<ResourceObject> topStartResObj,
        RefPtr<ResourceObject> topEndResObj, RefPtr<ResourceObject> bottomStartResObj,
        RefPtr<ResourceObject> bottomEndResObj);
    static void ParseBorderRadiusProps(
        const EcmaVM* vm, const Local<panda::ObjectRef>& object, NG::BorderRadiusProperty& radius);
    static bool ParseBindSheetBorderRadiusProps(
        const EcmaVM* vm, const Local<JSValueRef>& args, BorderRadiusProperty& radius);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_BRIDGE_TEXTPICKER_PARSER_H
