/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTPICKER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTPICKER_H

#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/picker/picker_text_component.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"

namespace OHOS::Ace::Framework {

enum class PickerStyle {
    INLINE = 0,
    BLOCK,
    FADE,
};

struct ParseTextArrayParam {
    std::vector<NG::RangeContent> result;
    uint32_t kind = 0;
    uint32_t selected = 0;
    std::string value;
    std::vector<NG::TextCascadePickerOptions> options;
    std::vector<uint32_t> selecteds;
    std::vector<std::string> values;
    JSRef<JSVal> valueChangeEventVal;
    JSRef<JSVal> selectedChangeEventVal;
};

class JSTextPickerParser : public JSViewAbstract {
public:
    static bool ParseIconTextArray(const JSRef<JSObject>& paramObject, std::vector<NG::RangeContent>& result,
        uint32_t& kind, uint32_t& selected);
    static bool ParseTextArray(const JSRef<JSObject>& paramObject, ParseTextArrayParam& param);
    static void ParseTextStyle(const JSRef<JSObject>& paramObj, NG::PickerTextStyle& textStyle, const std::string& pos);
    static bool ParseMultiTextArray(const JSRef<JSObject>& paramObj, ParseTextArrayParam& param);
    static bool ParseCascadeTextArray(const JSRef<JSObject>& paramObj, std::vector<uint32_t>& selecteds,
        std::vector<std::string>& values, NG::TextCascadePickerOptionsAttr& attr);
    static bool GenerateCascadeOptions(const JSRef<JSArray>& array,
        std::vector<NG::TextCascadePickerOptions>& options);
    static bool GenerateCascadeOptionsInternal(const JSRef<JSObject>& jsObj,
        std::vector<NG::TextCascadePickerOptions>& options);
    static bool ParseInternalArray(const JSRef<JSArray>& jsRangeValue, std::vector<uint32_t>& selecteds,
        std::vector<std::string>& values, uint32_t index, bool isHasSelectAttr);
    static void SetSelectedValues(std::vector<uint32_t>& selectedValues, std::vector<std::string>& values,
        uint32_t index, bool isHasSelectAttr, std::vector<std::string>& resultStr);
    static bool ParseMultiTextArrayValue(const JsiRef<JsiValue>& jsValue, ParseTextArrayParam& param);
    static bool ParseMultiTextArraySelect(const JsiRef<JsiValue>& jsSelectedValue, ParseTextArrayParam& param);
    static void ParseMultiTextArraySelectInternal(const std::vector<NG::TextCascadePickerOptions>& options,
        const std::vector<std::string>& values, std::vector<uint32_t>& selecteds);
    static bool ParseMultiTextArrayRange(const JSRef<JSArray>& jsRangeValue,
        std::vector<NG::TextCascadePickerOptions>& options);
    static bool ParseMultiTextArrayRangeInternal(const JSRef<JSVal>& value,
        std::vector<NG::TextCascadePickerOptions>& options);
    static void ParseMultiTextArraySelectArrayInternal(const std::vector<NG::TextCascadePickerOptions>& options,
        std::vector<uint32_t>& selecteds);
    static void ParseMultiTextArrayValueInternal(const std::vector<NG::TextCascadePickerOptions>& options,
        std::vector<std::string>& values);
    static void ParseMultiTextArrayValueSingleInternal(
        const std::vector<NG::TextCascadePickerOptions>& options, const std::string& value,
        std::vector<std::string>& values);
    static void IsUserDefinedFontFamily(const std::string& pos);
};

class JSTextPicker : public JSViewAbstract {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);

    static void SetDefaultPickerItemHeight(const JSCallbackInfo& info);
    static void SetCanLoop(const JSCallbackInfo& info);

    static void OnAccept(const JSCallbackInfo& info);
    static void OnCancel(const JSCallbackInfo& info);
    static void OnChange(const JSCallbackInfo& info);
    static void SetDisappearTextStyle(const JSCallbackInfo& info);
    static void SetTextStyle(const JSCallbackInfo& info);
    static void SetSelectedTextStyle(const JSCallbackInfo& info);
    static void SetSelectedIndex(const JSCallbackInfo& info);
    static void PickerBackgroundColor(const JSCallbackInfo& info);
    static void SetDivider(const JSCallbackInfo& info);
    static void SetGradientHeight(const JSCallbackInfo& info);
    static void JsOpacity(const JSCallbackInfo& info);
private:
    static size_t ProcessCascadeOptionDepth(const NG::TextCascadePickerOptions& option);
    static void ProcessCascadeSelected(const std::vector<NG::TextCascadePickerOptions>& options,
        uint32_t index, std::vector<uint32_t>& selecteds);
    static bool ProcessCascadeOptions(const JSRef<JSObject>& paramObjec,
        std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selecteds,
        std::vector<std::string>& values, NG::TextCascadePickerOptionsAttr& attr);
    static void SetSelectedIndexMulti(const JsiRef<JsiValue>& jsSelectedValue);
    static void SetSelectedIndexMultiInternal(uint32_t count, std::vector<NG::TextCascadePickerOptions>& options,
        std::vector<uint32_t>& selecteds);
    static void SetSelectedInternal(uint32_t count, std::vector<NG::TextCascadePickerOptions>& options,
        std::vector<uint32_t>& selecteds);
    static void SetSelectedIndexSingle(const JsiRef<JsiValue>& jsSelectedValue);
    static bool ProcessSingleRangeValue(const JSRef<JSObject>& paramObjec, ParseTextArrayParam& param);
    static void SetSelectedIndexSingleInternal(const std::vector<NG::TextCascadePickerOptions>& options,
        uint32_t count, uint32_t& selectedValue, std::vector<uint32_t>& selectedValues);
    static void CreateMulti(const RefPtr<PickerTheme>& theme, const std::vector<std::string>& values,
        const std::vector<uint32_t>& selectedValues, const NG::TextCascadePickerOptionsAttr& attr,
        const std::vector<NG::TextCascadePickerOptions>& options);
    static bool CheckDividerValue(const Dimension &dimension);
};

class JSTextPickerDialog {
public:
    static void JSBind(BindingTarget globalObj);
    static void Show(const JSCallbackInfo& info);
    static void TextPickerDialogShow(const JSRef<JSObject>& paramObj,
        const std::map<std::string, NG::DialogTextEvent>& dialogEvent,
        const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent);
    static std::map<std::string, NG::DialogTextEvent> DialogEvent(const JSCallbackInfo& info);
    static std::map<std::string, NG::DialogGestureEvent> DialogCancelEvent(const JSCallbackInfo& info);

private:
    static void ParseText(RefPtr<PickerTextComponent>& component, const JSRef<JSObject>& paramObj);
    static void AddEvent(RefPtr<PickerTextComponent>& picker, const JSCallbackInfo& info);
    static bool ParseShowData(const JSRef<JSObject>& paramObj, NG::TextPickerSettingData& settingData);
    static void ParseTextProperties(const JSRef<JSObject>& paramObj, NG::PickerTextProperties& result);
    static void ParseShowDataMultiContent(const std::vector<NG::TextCascadePickerOptions>& options,
        const std::vector<uint32_t>& selecteds, const std::vector<std::string>& values,
        NG::TextCascadePickerOptionsAttr& attr, NG::TextPickerSettingData& settingData);
    static bool ParseShowDataAttribute(const JSRef<JSObject>& paramObject,
        NG::TextPickerSettingData& settingData);
    static bool ParseCanLoop(const JSRef<JSObject>& paramObject,
        bool& canLoop);
    static bool ParseShowDataOptions(
        const JSRef<JSObject>& paramObject, ParseTextArrayParam& param, NG::TextCascadePickerOptionsAttr& attr);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTPICKER_H
