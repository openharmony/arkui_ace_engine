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

#include "bridge/declarative_frontend/jsview/js_textpicker.h"

#include <cstdint>
#include <securec.h>

#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_text_picker_theme.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_datepicker.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/textpicker_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_properties.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {
const DimensionOffset TEXT_PICKER_OFFSET_DEFAULT_TOP = DimensionOffset(0.0_vp, 40.0_vp);
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const std::vector<HoverModeAreaType> HOVER_MODE_AREA_TYPE = { HoverModeAreaType::TOP_SCREEN,
    HoverModeAreaType::BOTTOM_SCREEN };
const std::regex DIMENSION_REGEX(R"(^[-+]?\d+(?:\.\d+)?(?:px|vp|fp|lpx)?$)", std::regex::icase);
}

std::unique_ptr<TextPickerModel> TextPickerModel::textPickerInstance_ = nullptr;
std::unique_ptr<TextPickerDialogModel> TextPickerDialogModel::textPickerDialogInstance_ = nullptr;
std::mutex TextPickerModel::mutex_;
std::mutex TextPickerDialogModel::mutex_;

TextPickerModel* TextPickerModel::GetInstance()
{
    if (!textPickerInstance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!textPickerInstance_) {
#ifdef NG_BUILD
            textPickerInstance_.reset(new NG::TextPickerModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                textPickerInstance_.reset(new NG::TextPickerModelNG());
            } else {
                textPickerInstance_.reset(new Framework::TextPickerModelImpl());
            }
#endif
        }
    }
    return textPickerInstance_.get();
}

TextPickerDialogModel* TextPickerDialogModel::GetInstance()
{
    if (!textPickerDialogInstance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!textPickerDialogInstance_) {
#ifdef NG_BUILD
            textPickerDialogInstance_.reset(new NG::TextPickerDialogModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                textPickerDialogInstance_.reset(new NG::TextPickerDialogModelNG());
            } else {
                textPickerDialogInstance_.reset(new Framework::TextPickerDialogModelImpl());
            }
#endif
        }
    }
    return textPickerDialogInstance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
void ParseFontOfButtonStyle(const JSRef<JSObject>& pickerButtonParamObject, ButtonInfo& buttonInfo)
{
    CalcDimension fontSize;
    JSRef<JSVal> sizeProperty = pickerButtonParamObject->GetProperty("fontSize");
    if (JSViewAbstract::ParseJsDimensionVpNG(sizeProperty, fontSize) && fontSize.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(fontSize.Value(), 0.0)) {
        if (JSViewAbstract::ParseJsDimensionFp(sizeProperty, fontSize)) {
            buttonInfo.fontSize = fontSize;
        }
    }
    Color fontColor;
    if (JSViewAbstract::ParseJsColor(pickerButtonParamObject->GetProperty("fontColor"), fontColor)) {
        buttonInfo.fontColor = fontColor;
    }
    auto fontWeight = pickerButtonParamObject->GetProperty("fontWeight");
    if (fontWeight->IsString() || fontWeight->IsNumber()) {
        buttonInfo.fontWeight = ConvertStrToFontWeight(fontWeight->ToString(), FontWeight::MEDIUM);
    }
    JSRef<JSVal> style = pickerButtonParamObject->GetProperty("fontStyle");
    if (style->IsNumber()) {
        auto value = style->ToNumber<int32_t>();
        if (value >= 0 && value < static_cast<int32_t>(FontStyle::NONE)) {
            buttonInfo.fontStyle = static_cast<FontStyle>(value);
        }
    }
    JSRef<JSVal> family = pickerButtonParamObject->GetProperty("fontFamily");
    std::vector<std::string> fontFamilies;
    if (JSViewAbstract::ParseJsFontFamilies(family, fontFamilies)) {
        buttonInfo.fontFamily = fontFamilies;
    }
}

ButtonInfo ParseButtonStyle(const JSRef<JSObject>& pickerButtonParamObject)
{
    ButtonInfo buttonInfo;
    if (pickerButtonParamObject->GetProperty("type")->IsNumber()) {
        auto buttonTypeIntValue = pickerButtonParamObject->GetProperty("type")->ToNumber<int32_t>();
        if (buttonTypeIntValue == static_cast<int32_t>(ButtonType::CAPSULE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::CIRCLE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ARC) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::NORMAL) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ROUNDED_RECTANGLE)) {
            buttonInfo.type = static_cast<ButtonType>(buttonTypeIntValue);
        }
    }
    if (pickerButtonParamObject->GetProperty("style")->IsNumber()) {
        auto styleModeIntValue = pickerButtonParamObject->GetProperty("style")->ToNumber<int32_t>();
        if (styleModeIntValue >= static_cast<int32_t>(ButtonStyleMode::NORMAL) &&
            styleModeIntValue <= static_cast<int32_t>(ButtonStyleMode::TEXT)) {
            buttonInfo.buttonStyle = static_cast<ButtonStyleMode>(styleModeIntValue);
        }
    }
    if (pickerButtonParamObject->GetProperty("role")->IsNumber()) {
        auto buttonRoleIntValue = pickerButtonParamObject->GetProperty("role")->ToNumber<int32_t>();
        if (buttonRoleIntValue >= static_cast<int32_t>(ButtonRole::NORMAL) &&
            buttonRoleIntValue <= static_cast<int32_t>(ButtonRole::ERROR)) {
            buttonInfo.role = static_cast<ButtonRole>(buttonRoleIntValue);
        }
    }
    ParseFontOfButtonStyle(pickerButtonParamObject, buttonInfo);
    Color backgroundColor;
    if (JSViewAbstract::ParseJsColor(pickerButtonParamObject->GetProperty("backgroundColor"), backgroundColor)) {
        buttonInfo.backgroundColor = backgroundColor;
    }
    auto radius = ParseBorderRadiusAttr(pickerButtonParamObject->GetProperty("borderRadius"));
    if (radius.has_value()) {
        buttonInfo.borderRadius = radius.value();
    }

    auto primaryValue = pickerButtonParamObject->GetProperty("primary");
    if (primaryValue->IsBoolean()) {
        buttonInfo.isPrimary = primaryValue->ToBoolean();
    }

    return buttonInfo;
}

std::vector<ButtonInfo> ParseButtonStyles(const JSRef<JSObject>& paramObject)
{
    std::vector<ButtonInfo> buttonInfos;
    auto acceptButtonStyle = paramObject->GetProperty("acceptButtonStyle");
    if (acceptButtonStyle->IsObject()) {
        auto acceptButtonStyleParamObject = JSRef<JSObject>::Cast(acceptButtonStyle);
        buttonInfos.emplace_back(ParseButtonStyle(acceptButtonStyleParamObject));
        buttonInfos[0].isAcceptButton = true;
    } else {
        ButtonInfo buttonInfo;
        buttonInfos.emplace_back(buttonInfo);
    }
    auto cancelButtonStyle = paramObject->GetProperty("cancelButtonStyle");
    if (cancelButtonStyle->IsObject()) {
        auto cancelButtonStyleParamObject = JSRef<JSObject>::Cast(cancelButtonStyle);
        buttonInfos.emplace_back(ParseButtonStyle(cancelButtonStyleParamObject));
    }

    return buttonInfos;
}
} // namespace

void JSTextPicker::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextPicker>::Declare("TextPicker");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTextPicker>::StaticMethod("create", &JSTextPicker::Create, opt);
    JSClass<JSTextPicker>::StaticMethod("defaultPickerItemHeight", &JSTextPicker::SetDefaultPickerItemHeight);
    JSClass<JSTextPicker>::StaticMethod("canLoop", &JSTextPicker::SetCanLoop);
    JSClass<JSTextPicker>::StaticMethod("disappearTextStyle", &JSTextPicker::SetDisappearTextStyle);
    JSClass<JSTextPicker>::StaticMethod("textStyle", &JSTextPicker::SetTextStyle);
    JSClass<JSTextPicker>::StaticMethod("selectedTextStyle", &JSTextPicker::SetSelectedTextStyle);
    JSClass<JSTextPicker>::StaticMethod("selectedIndex", &JSTextPicker::SetSelectedIndex);
    JSClass<JSTextPicker>::StaticMethod("divider", &JSTextPicker::SetDivider);
    JSClass<JSTextPicker>::StaticMethod("opacity", &JSTextPicker::JsOpacity);

    JSClass<JSTextPicker>::StaticMethod("onAccept", &JSTextPicker::OnAccept);
    JSClass<JSTextPicker>::StaticMethod("onCancel", &JSTextPicker::OnCancel);
    JSClass<JSTextPicker>::StaticMethod("onChange", &JSTextPicker::OnChange);
    JSClass<JSTextPicker>::StaticMethod("onScrollStop", &JSTextPicker::OnScrollStop);
    JSClass<JSTextPicker>::StaticMethod("backgroundColor", &JSTextPicker::PickerBackgroundColor);
    JSClass<JSTextPicker>::StaticMethod("gradientHeight", &JSTextPicker::SetGradientHeight);
    JSClass<JSTextPicker>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTextPicker>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTextPicker>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTextPicker>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTextPicker>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSTextPicker>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTextPicker>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSTextPicker>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTextPicker>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSTextPicker::PickerBackgroundColor(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBackgroundColor(info);

    if (info.Length() < 1) {
        return;
    }
    Color backgroundColor;
    if (!ParseJsColor(info[0], backgroundColor)) {
        return;
    }
    TextPickerModel::GetInstance()->SetBackgroundColor(backgroundColor);
}

void JSTextPicker::JsOpacity(const JSCallbackInfo& info)
{
    JSViewAbstract::JsOpacity(info);
    TextPickerModel::GetInstance()->HasUserDefinedOpacity();
}

size_t JSTextPicker::ProcessCascadeOptionDepth(const NG::TextCascadePickerOptions& option)
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

void JSTextPicker::CreateMulti(const RefPtr<PickerTheme>& theme, const std::vector<std::string>& values,
    const std::vector<uint32_t>& selectedValues, const NG::TextCascadePickerOptionsAttr& attr,
    const std::vector<NG::TextCascadePickerOptions>& options)
{
    TextPickerModel::GetInstance()->MultiInit(theme);
    TextPickerModel::GetInstance()->SetValues(values);
    TextPickerModel::GetInstance()->SetSelecteds(selectedValues);
    TextPickerModel::GetInstance()->SetIsCascade(attr.isCascade);
    TextPickerModel::GetInstance()->SetHasSelectAttr(attr.isHasSelectAttr);
    TextPickerModel::GetInstance()->SetColumns(options);
}

void ParseTextPickerValueObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onValueChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                             const std::vector<std::string>& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("TextPicker.onValueChange");
        if (value.size() == 1) {
            JSRef<JSVal> newJSVal = JSRef<JSVal>::Make(ToJSValue(value[0]));
            PipelineContext::SetCallBackNode(node);
            func->ExecuteJS(1, &newJSVal);
        } else {
            JSRef<JSArray> valueArray = JSRef<JSArray>::New();
            for (uint32_t i = 0; i < value.size(); i++) {
                valueArray->SetValueAt(i, JSRef<JSVal>::Make(ToJSValue(value[i])));
            }
            JSRef<JSVal> newJSVal = JSRef<JSVal>::Cast(valueArray);
            PipelineContext::SetCallBackNode(node);
            func->ExecuteJS(1, &newJSVal);
        }
    };
    TextPickerModel::GetInstance()->SetOnValueChangeEvent(std::move(onValueChange));
}

void ParseTextPickerSelectedObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onSelectedChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                                const std::vector<double>& index) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("TextPicker.onSelectedChange");
        if (index.size() == 1) {
            PipelineContext::SetCallBackNode(node);
            JSRef<JSVal> newJSVal = JSRef<JSVal>::Make(ToJSValue(index[0]));
            func->ExecuteJS(1, &newJSVal);
        } else {
            JSRef<JSArray> indexArray = JSRef<JSArray>::New();
            for (uint32_t i = 0; i < index.size(); i++) {
                indexArray->SetValueAt(i, JSRef<JSVal>::Make(ToJSValue(index[i])));
            }
            PipelineContext::SetCallBackNode(node);
            JSRef<JSVal> newJSVal = JSRef<JSVal>::Cast(indexArray);
            func->ExecuteJS(1, &newJSVal);
        }
    };
    TextPickerModel::GetInstance()->SetOnSelectedChangeEvent(std::move(onSelectedChange));
}

void JSTextPicker::Create(const JSCallbackInfo& info)
{
    if (info.Length() >= 1 && info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        ParseTextArrayParam param;
        NG::TextCascadePickerOptionsAttr optionsAttr;
        bool optionsMultiContentCheckErr = false;
        bool optionsCascadeContentCheckErr = false;
        auto isSingleRange = ProcessSingleRangeValue(paramObject, param);
        TextPickerModel::GetInstance()->SetSingleRange(isSingleRange);
        if (!isSingleRange) {
            if (!JSTextPickerParser::ParseMultiTextArray(paramObject, param)) {
                param.options.clear();
                optionsMultiContentCheckErr = true;
            }
            if (optionsMultiContentCheckErr) {
                optionsCascadeContentCheckErr =
                    !ProcessCascadeOptions(paramObject, param.options, param.selecteds, param.values, optionsAttr);
            }
        }
        if (!isSingleRange && optionsMultiContentCheckErr && optionsCascadeContentCheckErr) {
            param.result.clear();
            param.options.clear();

            auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
            bool firstBuild = targetNode && targetNode->IsFirstBuilding();
            if (!firstBuild) {
                return;
            }
        }
        auto theme = GetTheme<PickerTheme>();
        CHECK_NULL_VOID(theme);
        if (!param.result.empty()) {
            TextPickerModel::GetInstance()->Create(theme, param.kind);
            TextPickerModel::GetInstance()->SetRange(param.result);
            TextPickerModel::GetInstance()->SetSelected(param.selected);
            TextPickerModel::GetInstance()->SetValue(param.value);
        } else {
            CreateMulti(theme, param.values, param.selecteds, optionsAttr, param.options);
        }
        TextPickerModel::GetInstance()->SetDefaultAttributes(theme);
        JSInteractableView::SetFocusable(true);
        JSInteractableView::SetFocusNode(true);
        if (param.valueChangeEventVal->IsFunction()) {
            ParseTextPickerValueObject(info, param.valueChangeEventVal);
        }
        if (param.selectedChangeEventVal->IsFunction()) {
            ParseTextPickerSelectedObject(info, param.selectedChangeEventVal);
        }
        JSTextPickerTheme::ApplyTheme();
    }
}

bool JSTextPicker::ProcessSingleRangeValue(const JSRef<JSObject>& paramObjec, ParseTextArrayParam& param)
{
    bool ret = true;
    auto getRange = paramObjec->GetProperty("range");
    if (getRange->IsNull() || getRange->IsUndefined()) {
        if (TextPickerModel::GetInstance()->GetSingleRange()) {
            return ret;
        }
        return false;
    }
    if (!JSTextPickerParser::ParseTextArray(paramObjec, param)) {
        if (!JSTextPickerParser::ParseIconTextArray(paramObjec, param.result, param.kind, param.selected)) {
            param.result.clear();
            ret = false;
        }
    }
    return ret;
}

bool JSTextPicker::ProcessCascadeOptions(const JSRef<JSObject>& paramObject,
    std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues,
    std::vector<std::string>& values, NG::TextCascadePickerOptionsAttr& attr)
{
    auto getRange = paramObject->GetProperty("range");
    if (getRange->IsNull() || getRange->IsUndefined()) {
        options.clear();
        return false;
    }
    if (!JSTextPickerParser::ParseCascadeTextArray(paramObject, selectedValues, values, attr)) {
        options.clear();
        return false;
    } else {
        JSTextPickerParser::GenerateCascadeOptions(getRange, options);
        uint32_t maxCount = options.empty() ? 0 : 1;
        for (size_t i = 0; i < options.size(); i++) {
            size_t tmp = ProcessCascadeOptionDepth(options[i]);
            if (tmp > maxCount) {
                maxCount = tmp;
            }
        }
        if (selectedValues.size() < maxCount) {
            auto differ = maxCount - selectedValues.size();
            for (uint32_t i = 0; i < differ; i++) {
                selectedValues.emplace_back(0);
            }
        }
        if (values.size() < maxCount) {
            auto differ = maxCount - values.size();
            for (uint32_t i = 0; i < differ; i++) {
                values.emplace_back("");
            }
        }
        attr.isCascade = true;
        TextPickerModel::GetInstance()->SetMaxCount(maxCount);
    }
    return true;
}

bool JSTextPickerParser::GenerateCascadeOptionsInternal(
    const JSRef<JSObject>& jsObj, std::vector<NG::TextCascadePickerOptions>& options)
{
    NG::TextCascadePickerOptions option;
    auto text = jsObj->GetProperty("text");
    std::string textStr = "";
    if (ParseJsString(text, textStr)) {
        option.rangeResult.emplace_back(textStr);
    } else {
        return false;
    }

    auto children = jsObj->GetProperty("children");
    if (children->IsArray()) {
        JSRef<JSArray> arrayChildren = JSRef<JSArray>::Cast(children);
        if (arrayChildren->Length() > 0) {
            if (!GenerateCascadeOptions(arrayChildren, option.children)) {
                return false;
            }
        }
    }
    options.emplace_back(option);
    return true;
}

bool JSTextPickerParser::GenerateCascadeOptions(
    const JSRef<JSArray>& array, std::vector<NG::TextCascadePickerOptions>& options)
{
    for (size_t i = 0; i < array->Length(); i++) {
        if (array->GetValueAt(i)->IsObject()) {
            auto jsObj = JSRef<JSObject>::Cast(array->GetValueAt(i));
            if (!GenerateCascadeOptionsInternal(jsObj, options)) {
                return false;
            }
        } else {
            options.clear();
            return false;
        }
    }
    return true;
}

bool JSTextPickerParser::ParseMultiTextArrayRangeInternal(
    const JSRef<JSVal>& value, std::vector<NG::TextCascadePickerOptions>& options)
{
    if (value->IsArray()) {
        NG::TextCascadePickerOptions option;
        if (!ParseJsStrArray(value, option.rangeResult)) {
            return false;
        } else {
            options.emplace_back(option);
        }
    } else {
        return false;
    }
    return true;
}

bool JSTextPickerParser::ParseMultiTextArrayRange(
    const JSRef<JSArray>& jsRangeValue, std::vector<NG::TextCascadePickerOptions>& options)
{
    options.clear();
    if (jsRangeValue->Length() > 0) {
        for (size_t i = 0; i < jsRangeValue->Length(); i++) {
            JSRef<JSVal> value = jsRangeValue->GetValueAt(i);
            if (!ParseMultiTextArrayRangeInternal(value, options)) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

void JSTextPickerParser::ParseMultiTextArraySelectInternal(const std::vector<NG::TextCascadePickerOptions>& options,
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

void JSTextPickerParser::ParseMultiTextArraySelectArrayInternal(
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

bool JSTextPickerParser::ParseMultiTextArraySelect(const JsiRef<JsiValue>& jsSelectedValue, ParseTextArrayParam& param)
{
    if (jsSelectedValue->IsArray()) {
        if (!ParseJsIntegerArray(jsSelectedValue, param.selecteds)) {
            return false;
        }
        ParseMultiTextArraySelectArrayInternal(param.options, param.selecteds);
    } else {
        uint32_t selectedValue = 0;
        if (ParseJsInteger(jsSelectedValue, selectedValue)) {
            if (param.options.size() < 1 || selectedValue >= param.options[0].rangeResult.size()) {
                selectedValue = 0;
            }
            param.selecteds.emplace_back(selectedValue);
            for (uint32_t i = 1; i < param.options.size(); i++) {
                param.selecteds.emplace_back(0);
            }
        } else {
            ParseMultiTextArraySelectInternal(param.options, param.values, param.selecteds);
        }
    }
    return true;
}

void JSTextPickerParser::ParseMultiTextArrayValueInternal(
    const std::vector<NG::TextCascadePickerOptions>& options, std::vector<std::string>& values)
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

void JSTextPickerParser::ParseMultiTextArrayValueSingleInternal(
    const std::vector<NG::TextCascadePickerOptions>& options, const std::string& value,
    std::vector<std::string>& values)
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

bool JSTextPickerParser::ParseMultiTextArrayValue(const JsiRef<JsiValue>& jsValue, ParseTextArrayParam& param)
{
    if (jsValue->IsArray()) {
        if (!ParseJsStrArray(jsValue, param.values)) {
            return false;
        }
        ParseMultiTextArrayValueInternal(param.options, param.values);
    } else {
        std::string value;
        if (ParseJsString(jsValue, value)) {
            ParseMultiTextArrayValueSingleInternal(param.options, value, param.values);
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

bool JSTextPickerParser::ParseMultiTextArray(const JSRef<JSObject>& paramObject, ParseTextArrayParam& param)
{
    auto getSelected = paramObject->GetProperty("selected");
    auto getValue = paramObject->GetProperty("value");
    auto getRange = paramObject->GetProperty("range");
    if (getRange->IsNull() || getRange->IsUndefined()) {
        return false;
    }
    if (!getRange->IsArray()) {
        return false;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(getRange);
    if (!ParseMultiTextArrayRange(array, param.options)) {
        return false;
    }
    if (getValue->IsObject()) {
        JSRef<JSObject> valueObj = JSRef<JSObject>::Cast(getValue);
        param.valueChangeEventVal = valueObj->GetProperty("changeEvent");
        if (param.valueChangeEventVal->IsFunction()) {
            getValue = valueObj->GetProperty("value");
        }
    }
    if (!ParseMultiTextArrayValue(getValue, param)) {
        return false;
    }
    if (getSelected->IsObject()) {
        JSRef<JSObject> selectedObj = JSRef<JSObject>::Cast(getSelected);
        param.selectedChangeEventVal = selectedObj->GetProperty("changeEvent");
        if (param.selectedChangeEventVal->IsFunction()) {
            getSelected = selectedObj->GetProperty("value");
        }
    }
    if (!ParseMultiTextArraySelect(getSelected, param)) {
        return false;
    }
    return true;
}

bool JSTextPickerParser::ParseInternalArray(const JSRef<JSArray>& jsRangeValue, std::vector<uint32_t>& selectedValues,
    std::vector<std::string>& values, uint32_t index, bool isHasSelectAttr)
{
    std::vector<std::string> resultStr;
    for (size_t i = 0; i < jsRangeValue->Length(); i++) {
        if (jsRangeValue->GetValueAt(i)->IsObject()) {
            auto jsObj = JSRef<JSObject>::Cast(jsRangeValue->GetValueAt(i));
            auto getText = jsObj->GetProperty("text");
            std::string textStr = "";
            if (ParseJsString(getText, textStr)) {
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

    SetSelectedValues(selectedValues, values, index, isHasSelectAttr, resultStr);

    if (!jsRangeValue->GetValueAt(selectedValues[index])->IsObject()) {
        return true;
    }
    auto jsObj = JSRef<JSObject>::Cast(jsRangeValue->GetValueAt(selectedValues[index]));
    auto getChildren = jsObj->GetProperty("children");
    if (getChildren->IsArray()) {
        ParseInternalArray(getChildren, selectedValues, values, index + 1, isHasSelectAttr);
    }
    return true;
}

void JSTextPickerParser::SetSelectedValues(std::vector<uint32_t>& selectedValues, std::vector<std::string>& values,
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

bool JSTextPickerParser::ParseCascadeTextArray(const JSRef<JSObject>& paramObject,
    std::vector<uint32_t>& selectedValues, std::vector<std::string>& values, NG::TextCascadePickerOptionsAttr& attr)
{
    JSRef<JSArray> getRange = paramObject->GetProperty("range");
    auto getSelected = paramObject->GetProperty("selected");
    auto getValue = paramObject->GetProperty("value");
    if (getValue->IsArray()) {
        if (!ParseJsStrArray(getValue, values)) {
            return false;
        }
    } else {
        std::string value = "";
        if (!ParseJsString(getValue, value)) {
            value = "";
        }
        values.emplace_back(value);
    }
    if (getSelected->IsArray()) {
        if (!ParseJsIntegerArray(getSelected, selectedValues)) {
            attr.isHasSelectAttr = false;
            return false;
        } else {
            attr.isHasSelectAttr = true;
        }
    } else {
        uint32_t selectValue = 0;
        if (!ParseJsInteger(getSelected, selectValue)) {
            selectValue = 0;
            attr.isHasSelectAttr = false;
        } else {
            attr.isHasSelectAttr = true;
        }
        selectedValues.emplace_back(selectValue);
    }
    return ParseInternalArray(getRange, selectedValues, values, 0, attr.isHasSelectAttr);
}

bool JSTextPickerParser::ParseTextArray(const JSRef<JSObject>& paramObject, ParseTextArrayParam& param)
{
    auto getSelected = paramObject->GetProperty("selected");
    auto getValue = paramObject->GetProperty("value");
    JSRef<JSArray> getRange = paramObject->GetProperty("range");
    std::vector<std::string> getRangeVector;
    if (getRange->Length() > 0) {
        if (!ParseJsStrArray(getRange, getRangeVector)) {
            return false;
        }

        param.result.clear();
        for (const auto& text : getRangeVector) {
            NG::RangeContent content;
            content.icon_ = "";
            content.text_ = text;
            param.result.emplace_back(content);
        }
        param.kind = NG::TEXT;
        if (getValue->IsObject()) {
            JSRef<JSObject> valueObj = JSRef<JSObject>::Cast(getValue);
            param.valueChangeEventVal = valueObj->GetProperty("changeEvent");
            if (param.valueChangeEventVal->IsFunction()) {
                getValue = valueObj->GetProperty("value");
            }
        }
        if (!ParseJsString(getValue, param.value)) {
            param.value = getRangeVector.front();
        }
        if (getSelected->IsObject()) {
            JSRef<JSObject> selectedObj = JSRef<JSObject>::Cast(getSelected);
            param.selectedChangeEventVal = selectedObj->GetProperty("changeEvent");
            if (param.selectedChangeEventVal->IsFunction()) {
                getSelected = selectedObj->GetProperty("value");
            }
        }
        if (!ParseJsInteger(getSelected, param.selected) && !param.value.empty()) {
            auto valueIterator = std::find(getRangeVector.begin(), getRangeVector.end(), param.value);
            if (valueIterator != getRangeVector.end()) {
                param.selected = static_cast<uint32_t>(std::distance(getRangeVector.begin(), valueIterator));
            }
        }
        if (param.selected >= getRangeVector.size()) {
            param.selected = 0;
        }
    }

    return true;
}

bool JSTextPickerParser::ParseIconTextArray(
    const JSRef<JSObject>& paramObject, std::vector<NG::RangeContent>& result, uint32_t& kind, uint32_t& selectedValue)
{
    auto getSelected = paramObject->GetProperty("selected");
    auto getRange = paramObject->GetProperty("range");
    if (!getRange->IsArray()) {
        return false;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(getRange);
    result.clear();
    kind = 0;
    for (size_t i = 0; i < array->Length(); i++) {
        if (!array->GetValueAt(i)->IsObject()) {
            continue;
        }
        auto jsObj = JSRef<JSObject>::Cast(array->GetValueAt(i));
        auto rangeIcon = jsObj->GetProperty("icon");
        auto rangeText = jsObj->GetProperty("text");
        NG::RangeContent content;
        std::string icon;
        std::string text;
        if (ParseJsMedia(rangeIcon, icon)) {
            content.icon_ = icon;
            kind |= NG::ICON;
        }

        if (ParseJsString(rangeText, text)) {
            content.text_ = text;
            kind |= NG::TEXT;
        }
        result.emplace_back(content);
    }

    if (kind != NG::ICON && kind != (NG::ICON | NG::TEXT)) {
        return false;
    }

    if (!ParseJsInteger(getSelected, selectedValue)) {
        selectedValue = 0;
    }
    return true;
}

void JSTextPickerParser::IsUserDefinedFontFamily(const std::string& pos)
{
    if (pos == "disappearTextStyle") {
        TextPickerModel::GetInstance()->HasUserDefinedDisappearFontFamily(true);
    } else if (pos == "textStyle") {
        TextPickerModel::GetInstance()->HasUserDefinedNormalFontFamily(true);
    } else if (pos == "selectedTextStyle") {
        TextPickerModel::GetInstance()->HasUserDefinedSelectedFontFamily(true);
    }
}

void JSTextPickerParser::ParseTextStyle(
    const JSRef<JSObject>& paramObj, NG::PickerTextStyle& textStyle, const std::string& pos)
{
    auto fontColor = paramObj->GetProperty("color");
    auto fontOptions = paramObj->GetProperty("font");

    Color textColor;
    if (ParseJsColor(fontColor, textColor)) {
        textStyle.textColor = textColor;
    }

    if (!fontOptions->IsObject()) {
        return;
    }
    JSRef<JSObject> fontObj = JSRef<JSObject>::Cast(fontOptions);
    auto fontSize = fontObj->GetProperty("size");
    auto fontWeight = fontObj->GetProperty("weight");
    auto fontFamily = fontObj->GetProperty("family");
    auto fontStyle = fontObj->GetProperty("style");
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        textStyle.fontSize = Dimension(-1);
    } else {
        CalcDimension size;
        if (!ParseJsDimensionFp(fontSize, size) || size.Unit() == DimensionUnit::PERCENT) {
            textStyle.fontSize = Dimension(-1);
        } else {
            textStyle.fontSize = size;
        }
    }

    if (!fontWeight->IsNull() && !fontWeight->IsUndefined()) {
        std::string weight;
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        } else {
            ParseJsString(fontWeight, weight);
        }
        textStyle.fontWeight = ConvertStrToFontWeight(weight);
    }

    if (!fontFamily->IsNull() && !fontFamily->IsUndefined()) {
        std::vector<std::string> families;
        if (ParseJsFontFamilies(fontFamily, families)) {
            textStyle.fontFamily = families;
            IsUserDefinedFontFamily(pos);
        }
    }

    if (fontStyle->IsNumber()) {
        auto style = fontStyle->ToNumber<int32_t>();
        if (style < 0 || style > 1) {
            return;
        }
        textStyle.fontStyle = static_cast<FontStyle>(style);
    }
}

void JSTextPicker::SetDefaultPickerItemHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension height;
    if (info[0]->IsNumber() || info[0]->IsString()) {
        if (!ParseJsDimensionFp(info[0], height)) {
            return;
        }
    }
    TextPickerModel::GetInstance()->SetDefaultPickerItemHeight(height);
}

void JSTextPicker::SetGradientHeight(const JSCallbackInfo& info)
{
    CalcDimension height;
    auto pickerTheme = GetTheme<PickerTheme>();
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        if (pickerTheme) {
            height = pickerTheme->GetGradientHeight();
        } else {
            height = 0.0_vp;
        }
    }
    if (info.Length() >= 1) {
        if (!ConvertFromJSValueNG(info[0], height)) {
            if (pickerTheme) {
                height = pickerTheme->GetGradientHeight();
            }
        }
        if ((height.Unit() == DimensionUnit::PERCENT) &&
            ((height.Value() > 1.0f) || (height.Value() < 0.0f))) {
            if (pickerTheme) {
                height = pickerTheme->GetGradientHeight();
            } else {
                height = 0.0_vp;
            }
        }
    }
    TextPickerModel::GetInstance()->SetGradientHeight(height);
}

void JSTextPicker::SetCanLoop(const JSCallbackInfo& info)
{
    bool value = true;
    if (info[0]->IsBoolean()) {
        value = info[0]->ToBoolean();
    }
    TextPickerModel::GetInstance()->SetCanLoop(value);
}

void JSTextPicker::SetDisappearTextStyle(const JSCallbackInfo& info)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;
    JSTextPickerTheme::ObtainTextStyle(textStyle);
    if (info[0]->IsObject()) {
        JSTextPickerParser::ParseTextStyle(info[0], textStyle, "disappearTextStyle");
    }
    TextPickerModel::GetInstance()->SetDisappearTextStyle(theme, textStyle);
}

void JSTextPicker::SetTextStyle(const JSCallbackInfo& info)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;
    JSTextPickerTheme::ObtainTextStyle(textStyle);
    if (info[0]->IsObject()) {
        JSTextPickerParser::ParseTextStyle(info[0], textStyle, "textStyle");
    }
    TextPickerModel::GetInstance()->SetNormalTextStyle(theme, textStyle);
}

void JSTextPicker::SetSelectedTextStyle(const JSCallbackInfo& info)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;
    JSTextPickerTheme::ObtainSelectedTextStyle(textStyle);
    if (info[0]->IsObject()) {
        JSTextPickerParser::ParseTextStyle(info[0], textStyle, "selectedTextStyle");
    }
    TextPickerModel::GetInstance()->SetSelectedTextStyle(theme, textStyle);
}

void JSTextPicker::ProcessCascadeSelected(
    const std::vector<NG::TextCascadePickerOptions>& options, uint32_t index, std::vector<uint32_t>& selectedValues)
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

void JSTextPicker::SetSelectedInternal(
    uint32_t count, std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues)
{
    for (uint32_t i = 0; i < count; i++) {
        if (selectedValues.size() > 0 && selectedValues.size() < i + 1) {
            selectedValues.emplace_back(0);
        } else {
            if (selectedValues[i] >= options[i].rangeResult.size()) {
                selectedValues[i] = 0;
            }
        }
    }
}

void JSTextPicker::SetSelectedIndexMultiInternal(
    uint32_t count, std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues)
{
    if (!TextPickerModel::GetInstance()->IsCascade()) {
        SetSelectedInternal(count, options, selectedValues);
    } else {
        TextPickerModel::GetInstance()->SetHasSelectAttr(true);
        ProcessCascadeSelected(options, 0, selectedValues);
        uint32_t maxCount = TextPickerModel::GetInstance()->GetMaxCount();
        if (selectedValues.size() < maxCount) {
            auto differ = maxCount - selectedValues.size();
            for (uint32_t i = 0; i < differ; i++) {
                selectedValues.emplace_back(0);
            }
        }
    }
}

void JSTextPicker::SetSelectedIndexSingleInternal(const std::vector<NG::TextCascadePickerOptions>& options,
    uint32_t count, uint32_t& selectedValue, std::vector<uint32_t>& selectedValues)
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

void JSTextPicker::SetSelectedIndexMulti(const JsiRef<JsiValue>& jsSelectedValue)
{
    std::vector<uint32_t> selectedValues;
    std::vector<NG::TextCascadePickerOptions> options;
    TextPickerModel::GetInstance()->GetMultiOptions(options);
    auto count =
        TextPickerModel::GetInstance()->IsCascade() ? TextPickerModel::GetInstance()->GetMaxCount() : options.size();
    if (jsSelectedValue->IsArray()) {
        if (!ParseJsIntegerArray(jsSelectedValue, selectedValues)) {
            selectedValues.clear();
            for (uint32_t i = 0; i < count; i++) {
                selectedValues.emplace_back(0);
            }
            TextPickerModel::GetInstance()->SetSelecteds(selectedValues);
            TextPickerModel::GetInstance()->SetHasSelectAttr(false);
            return;
        }
        SetSelectedIndexMultiInternal(count, options, selectedValues);
    } else {
        uint32_t selectedValue = 0;
        if (ParseJsInteger(jsSelectedValue, selectedValue)) {
            TextPickerModel::GetInstance()->SetHasSelectAttr(true);
            SetSelectedIndexSingleInternal(options, count, selectedValue, selectedValues);
        } else {
            selectedValues.clear();
            TextPickerModel::GetInstance()->SetHasSelectAttr(false);
            for (uint32_t i = 0; i < count; i++) {
                selectedValues.emplace_back(0);
            }
        }
    }
    TextPickerModel::GetInstance()->SetSelecteds(selectedValues);
}

void JSTextPicker::SetSelectedIndexSingle(const JsiRef<JsiValue>& jsSelectedValue)
{
    // Single
    std::vector<NG::RangeContent> rangeResult;
    TextPickerModel::GetInstance()->GetSingleRange(rangeResult);
    if (jsSelectedValue->IsArray()) {
        std::vector<uint32_t> selectedValues;
        if (!ParseJsIntegerArray(jsSelectedValue, selectedValues)) {
            uint32_t selectedValue = 0;
            TextPickerModel::GetInstance()->SetSelected(selectedValue);
            return;
        }
        if (selectedValues.size() > 0) {
            if (selectedValues[0] >= rangeResult.size()) {
                selectedValues[0] = 0;
            }
        } else {
            selectedValues.emplace_back(0);
        }

        TextPickerModel::GetInstance()->SetSelected(selectedValues[0]);
    } else {
        uint32_t selectedValue = 0;
        if (ParseJsInteger(jsSelectedValue, selectedValue)) {
            if (selectedValue >= rangeResult.size()) {
                selectedValue = 0;
            }
        }
        TextPickerModel::GetInstance()->SetSelected(selectedValue);
    }
}

void JSTextPicker::SetSelectedIndex(const JSCallbackInfo& info)
{
    if (info.Length() >= 1) {
        auto jsSelectedValue = info[0];
        if (jsSelectedValue->IsNull() || jsSelectedValue->IsUndefined()) {
            return;
        }
        if (TextPickerModel::GetInstance()->IsSingle()) {
            SetSelectedIndexSingle(jsSelectedValue);
        } else {
            SetSelectedIndexMulti(jsSelectedValue);
        }
    }
}

bool JSTextPicker::CheckDividerValue(const Dimension &dimension)
{
    if (dimension.Value() >= 0.0f && dimension.Unit() != DimensionUnit::PERCENT) {
        return true;
    }
    return false;
}

void JSTextPicker::SetDivider(const JSCallbackInfo& info)
{
    NG::ItemDivider divider;
    auto pickerTheme = GetTheme<PickerTheme>();
    Dimension defaultStrokeWidth = 0.0_vp;
    Dimension defaultMargin = 0.0_vp;
    Color defaultColor = Color::TRANSPARENT;
    // Set default strokeWidth and color
    if (pickerTheme) {
        defaultStrokeWidth = pickerTheme->GetDividerThickness();
        defaultColor = pickerTheme->GetDividerColor();
        divider.strokeWidth = defaultStrokeWidth;
        divider.color = defaultColor;
    }

    if (info.Length() >= 1 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
       
        Dimension strokeWidth = defaultStrokeWidth;
        if (ConvertFromJSValueNG(obj->GetProperty("strokeWidth"), strokeWidth) && CheckDividerValue(strokeWidth)) {
            divider.strokeWidth = strokeWidth;
        }
        
        Color color = defaultColor;
        if (ConvertFromJSValue(obj->GetProperty("color"), color)) {
            divider.color = color;
        }

        Dimension startMargin = defaultMargin;
        if (ConvertFromJSValueNG(obj->GetProperty("startMargin"), startMargin) && CheckDividerValue(startMargin)) {
            divider.startMargin = startMargin;
        }

        Dimension endMargin = defaultMargin;
        if (ConvertFromJSValueNG(obj->GetProperty("endMargin"), endMargin) &&  CheckDividerValue(endMargin)) {
            divider.endMargin = endMargin;
        }
    } else if (info.Length() >= 1 && info[0]->IsNull()) {
        divider.strokeWidth = 0.0_vp;
    }
    TextPickerModel::GetInstance()->SetDivider(divider);
}

void JSTextPicker::OnAccept(const JSCallbackInfo& info) {}

void JSTextPicker::OnCancel(const JSCallbackInfo& info) {}

void JSTextPicker::OnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = JSRef<JSFunc>::Cast(info[0]);
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](
                        const std::vector<std::string>& value, const std::vector<double>& index) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("TextPicker.onChange");
        if (value.size() == 1 && index.size() == 1) {
            auto params = ConvertToJSValues(value[0], index[0]);
            func->Call(JSRef<JSObject>(), static_cast<int>(params.size()), params.data());
        } else {
            std::vector<JSRef<JSVal>> result;
            JSRef<JSArray> valueArray = JSRef<JSArray>::New();
            for (uint32_t i = 0; i < value.size(); i++) {
                valueArray->SetValueAt(i, JSRef<JSVal>::Make(ToJSValue(value[i])));
            }
            JSRef<JSVal> valueJs = JSRef<JSVal>::Cast(valueArray);
            result.emplace_back(valueJs);
            JSRef<JSArray> selectedArray = JSRef<JSArray>::New();
            for (uint32_t i = 0; i < index.size(); i++) {
                selectedArray->SetValueAt(i, JSRef<JSVal>::Make(ToJSValue(index[i])));
            }
            JSRef<JSVal> selectedJs = JSRef<JSVal>::Cast(selectedArray);
            result.emplace_back(selectedJs);
            func->Call(JSRef<JSObject>(), static_cast<int>(result.size()), result.data());
        }
    };
    TextPickerModel::GetInstance()->SetOnCascadeChange(std::move(onChange));
    info.ReturnSelf();
}

void JSTextPicker::OnScrollStop(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = JSRef<JSFunc>::Cast(info[0]);
    auto onScrollStop = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](
                        const std::vector<std::string>& value, const std::vector<double>& index) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("TextPicker.onScrollStop");
        if (value.size() == 1 && index.size() == 1) {
            auto params = ConvertToJSValues(value[0], index[0]);
            func->Call(JSRef<JSObject>(), static_cast<int>(params.size()), params.data());
        } else {
            std::vector<JSRef<JSVal>> result;
            JSRef<JSArray> valueArray = JSRef<JSArray>::New();
            for (uint32_t i = 0; i < value.size(); i++) {
                valueArray->SetValueAt(i, JSRef<JSVal>::Make(ToJSValue(value[i])));
            }
            JSRef<JSVal> valueJs = JSRef<JSVal>::Cast(valueArray);
            result.emplace_back(valueJs);
            JSRef<JSArray> selectedArray = JSRef<JSArray>::New();
            for (uint32_t i = 0; i < index.size(); i++) {
                selectedArray->SetValueAt(i, JSRef<JSVal>::Make(ToJSValue(index[i])));
            }
            JSRef<JSVal> selectedJs = JSRef<JSVal>::Cast(selectedArray);
            result.emplace_back(selectedJs);
            func->Call(JSRef<JSObject>(), static_cast<int>(result.size()), result.data());
        }
    };
    TextPickerModel::GetInstance()->SetOnScrollStop(std::move(onScrollStop));
    info.ReturnSelf();
}

void JSTextPickerDialog::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextPickerDialog>::Declare("TextPickerDialog");
    JSClass<JSTextPickerDialog>::StaticMethod("show", &JSTextPickerDialog::Show);

    JSClass<JSTextPickerDialog>::Bind<>(globalObj);
}

void TextPickerDialogAppearEvent(const JSCallbackInfo& info, TextPickerDialogEvent& textPickerDialogEvent)
{
    std::function<void()> didAppearEvent;
    std::function<void()> willAppearEvent;
    if (!info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidAppear = paramObject->GetProperty("onDidAppear");
    if (!onDidAppear->IsUndefined() && onDidAppear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDidAppear));
        didAppearEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("TextPickerDialog.onDidAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
    }
    auto onWillAppear = paramObject->GetProperty("onWillAppear");
    if (!onWillAppear->IsUndefined() && onWillAppear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillAppear));
        willAppearEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("TextPickerDialog.onWillAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
    }
    textPickerDialogEvent.onDidAppear = std::move(didAppearEvent);
    textPickerDialogEvent.onWillAppear = std::move(willAppearEvent);
}

void TextPickerDialogDisappearEvent(const JSCallbackInfo& info, TextPickerDialogEvent& textPickerDialogEvent)
{
    std::function<void()> didDisappearEvent;
    std::function<void()> willDisappearEvent;
    if (!info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidDisappear = paramObject->GetProperty("onDidDisappear");
    if (!onDidDisappear->IsUndefined() && onDidDisappear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDidDisappear));
        didDisappearEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("TextPickerDialog.onDidDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
    }
    auto onWillDisappear = paramObject->GetProperty("onWillDisappear");
    if (!onWillDisappear->IsUndefined() && onWillDisappear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillDisappear));
        willDisappearEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("TextPickerDialog.onWillDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
    }
    textPickerDialogEvent.onDidDisappear = std::move(didDisappearEvent);
    textPickerDialogEvent.onWillDisappear = std::move(willDisappearEvent);
}

void JSTextPickerDialog::Show(const JSCallbackInfo& info)
{
    auto scopedDelegate = EngineHelper::GetCurrentDelegateSafely();
    CHECK_NULL_VOID(scopedDelegate);
    if (!info[0]->IsObject()) {
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    std::function<void()> cancelEvent;
    std::function<void(const std::string&)> acceptEvent;
    std::function<void(const std::string&)> changeEvent;
    auto onCancel = paramObject->GetProperty("onCancel");
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (!onCancel->IsUndefined() && onCancel->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onCancel));
        cancelEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("TextPickerDialog.onCancel");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
    }
    auto onAccept = paramObject->GetProperty("onAccept");
    if (!onAccept->IsUndefined() && onAccept->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAccept));
        acceptEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                          const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "value", "index" };
            ACE_SCORING_EVENT("TextPickerDialog.onAccept");
            PipelineContext::SetCallBackNode(node);
            func->Execute(keys, info);
        };
    }
    auto onChange = paramObject->GetProperty("onChange");
    if (!onChange->IsUndefined() && onChange->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onChange));
        changeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                          const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "value", "index" };
            ACE_SCORING_EVENT("TextPickerDialog.onChange");
            PipelineContext::SetCallBackNode(node);
            func->Execute(keys, info);
        };
    }
    std::function<void(const std::string&)> scrollStopEvent;
    auto onScrollStop = paramObject->GetProperty("onScrollStop");
    if (!onScrollStop->IsUndefined() && onScrollStop->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onScrollStop));
        scrollStopEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                              const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "value", "index" };
            ACE_SCORING_EVENT("TextPickerDialog.onScrollStop");
            PipelineContext::SetCallBackNode(node);
            func->Execute(keys, info);
        };
    }
    NG::TextPickerSettingData settingData;
    TextPickerDialog textPickerDialog;

    auto pickerText = TextPickerDialogModel::GetInstance()->CreateObject();
    if (pickerText == nullptr) {
        // parse Multi column text
        if (!ParseShowData(paramObject, settingData)) {
            return;
        }
    } else {
        auto getSelected = paramObject->GetProperty("selected");
        auto defaultHeight = paramObject->GetProperty("defaultPickerItemHeight");
        auto canLoop = paramObject->GetProperty("canLoop");
        JSRef<JSArray> getRange = paramObject->GetProperty("range");
        std::vector<std::string> getRangeVector;
        if (!JSViewAbstract::ParseJsStrArray(getRange, getRangeVector)) {
            return;
        }
        std::string value = "";
        uint32_t selectedValue = 0;
        auto getValue = paramObject->GetProperty("value");
        if (!JSViewAbstract::ParseJsInteger(getSelected, selectedValue) &&
            JSViewAbstract::ParseJsString(getValue, value)) {
            auto valueIterator = std::find(getRangeVector.begin(), getRangeVector.end(), value);
            if (valueIterator != getRangeVector.end()) {
                selectedValue = static_cast<uint32_t>(std::distance(getRangeVector.begin(), valueIterator));
            }
        }
        if (selectedValue >= getRangeVector.size()) {
            selectedValue = 0;
        }
        CalcDimension height;
        if (defaultHeight->IsNumber() || defaultHeight->IsString()) {
            if (!JSViewAbstract::ParseJsDimensionFp(defaultHeight, height)) {
                return;
            }
        }
        if (!defaultHeight->IsEmpty()) {
            textPickerDialog.isDefaultHeight = true;
        }
        textPickerDialog.height = height;
        textPickerDialog.selectedValue = selectedValue;
        textPickerDialog.getRangeVector = getRangeVector;
    }

    // Parse alignment
    auto alignmentValue = paramObject->GetProperty("alignment");
    if (alignmentValue->IsNumber()) {
        auto alignment = alignmentValue->ToNumber<int32_t>();
        if (alignment >= 0 && alignment <= static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
            textPickerDialog.alignment = DIALOG_ALIGNMENT[alignment];
        }
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            if (alignment == static_cast<int32_t>(DialogAlignment::TOP) ||
                alignment == static_cast<int32_t>(DialogAlignment::TOP_START) ||
                alignment == static_cast<int32_t>(DialogAlignment::TOP_END)) {
                textPickerDialog.offset = TEXT_PICKER_OFFSET_DEFAULT_TOP;
            }
        }
    }

    // Parse offset
    auto offsetValue = paramObject->GetProperty("offset");
    if (offsetValue->IsObject()) {
        auto offsetObj = JSRef<JSObject>::Cast(offsetValue);
        CalcDimension dx;
        auto dxValue = offsetObj->GetProperty("dx");
        JSAlertDialog::ParseJsDimensionVp(dxValue, dx);
        CalcDimension dy;
        auto dyValue = offsetObj->GetProperty("dy");
        JSAlertDialog::ParseJsDimensionVp(dyValue, dy);
        textPickerDialog.offset = DimensionOffset(dx, dy);
    }

    // Parse maskRect.
    auto maskRectValue = paramObject->GetProperty("maskRect");
    DimensionRect maskRect;
    if (JSViewAbstract::ParseJsDimensionRect(maskRectValue, maskRect)) {
        textPickerDialog.maskRect = maskRect;
    }

    auto backgroundColorValue = paramObject->GetProperty("backgroundColor");
    Color backgroundColor;
    if (JSViewAbstract::ParseJsColor(backgroundColorValue, backgroundColor)) {
        textPickerDialog.backgroundColor = backgroundColor;
    }

    auto backgroundBlurStyle = paramObject->GetProperty("backgroundBlurStyle");
    if (backgroundBlurStyle->IsNumber()) {
        auto blurStyle = backgroundBlurStyle->ToNumber<int32_t>();
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            textPickerDialog.backgroundBlurStyle = blurStyle;
        }
    }
    auto shadowValue = paramObject->GetProperty("shadow");
    Shadow shadow;
    if ((shadowValue->IsObject() || shadowValue->IsNumber()) && JSViewAbstract::ParseShadowProps(shadowValue, shadow)) {
        textPickerDialog.shadow = shadow;
    }

    auto enableHoverModeValue = paramObject->GetProperty("enableHoverMode");
    if (enableHoverModeValue->IsBoolean()) {
        textPickerDialog.enableHoverMode = enableHoverModeValue->ToBoolean();
    }

    auto hoverModeAreaValue = paramObject->GetProperty("hoverModeArea");
    if (hoverModeAreaValue->IsNumber()) {
        auto hoverModeArea = hoverModeAreaValue->ToNumber<int32_t>();
        if (hoverModeArea >= 0 && hoverModeArea < static_cast<int32_t>(HOVER_MODE_AREA_TYPE.size())) {
            textPickerDialog.hoverModeArea = HOVER_MODE_AREA_TYPE[hoverModeArea];
        }
    }

    auto buttonInfos = ParseButtonStyles(paramObject);

    TextPickerDialogEvent textPickerDialogEvent { nullptr, nullptr, nullptr, nullptr };
    TextPickerDialogAppearEvent(info, textPickerDialogEvent);
    TextPickerDialogDisappearEvent(info, textPickerDialogEvent);
    TextPickerDialogModel::GetInstance()->SetTextPickerDialogShow(pickerText, settingData, std::move(cancelEvent),
        std::move(acceptEvent), std::move(changeEvent), std::move(scrollStopEvent), textPickerDialog,
        textPickerDialogEvent, buttonInfos);
}

void JSTextPickerDialog::TextPickerDialogShow(const JSRef<JSObject>& paramObj,
    const std::map<std::string, NG::DialogTextEvent>& dialogEvent,
    const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent)
{
    auto container = Container::CurrentSafely();
    if (!container) {
        return;
    }
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        return;
    }

    auto executor = pipelineContext->GetTaskExecutor();
    if (!executor) {
        return;
    }

    auto theme = JSTextPicker::GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);

    NG::TextPickerSettingData settingData;
    if (!ParseShowData(paramObj, settingData)) {
        return;
    }

    DialogProperties properties;
    properties.alignment = theme->GetAlignment();
    if (properties.alignment == DialogAlignment::BOTTOM &&
        Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
        properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    }

    properties.customStyle = false;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    }
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowTextDialog(properties, settingData, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI, "ArkUIDialogShowTextPicker");
}

bool JSTextPickerDialog::ParseShowDataOptions(
    const JSRef<JSObject>& paramObject, ParseTextArrayParam& param, NG::TextCascadePickerOptionsAttr& attr)
{
    bool optionsMultiContentCheckErr = false;
    bool optionsCascadeContentCheckErr = false;
    if (!JSTextPickerParser::ParseMultiTextArray(paramObject, param)) {
        param.options.clear();
        optionsMultiContentCheckErr = true;
    }

    if (optionsMultiContentCheckErr) {
        if (!JSTextPickerParser::ParseCascadeTextArray(paramObject, param.selecteds, param.values, attr)) {
            param.options.clear();
            optionsCascadeContentCheckErr = true;
        } else {
            JSRef<JSArray> getRange = paramObject->GetProperty("range");
            JSTextPickerParser::GenerateCascadeOptions(getRange, param.options);
            attr.isCascade = true;
        }
    }
    if (optionsMultiContentCheckErr && optionsCascadeContentCheckErr) {
        param.options.clear();
        return false;
    }
    return true;
}

bool JSTextPickerDialog::ParseShowDataAttribute(
    const JSRef<JSObject>& paramObject, NG::TextPickerSettingData& settingData)
{
    CalcDimension height;
    auto defaultHeight = paramObject->GetProperty("defaultPickerItemHeight");
    if (defaultHeight->IsNumber() || defaultHeight->IsString()) {
        if (!JSViewAbstract::ParseJsDimensionFp(defaultHeight, height)) {
            return false;
        }
    }
    settingData.height = height;
    ParseTextProperties(paramObject, settingData.properties);
    return true;
}
bool JSTextPickerDialog::ParseCanLoop(const JSRef<JSObject>& paramObject, bool& canLoop)
{
    bool result = false;
    auto prop = paramObject->GetProperty("canLoop");
    bool value = false;
    if (prop->IsBoolean() && JSViewAbstract::ParseJsBool(prop, value)) {
        canLoop = value;
        result = true;
    } else {
        canLoop = true;
        result = false;
    }
    return result;
}

void JSTextPickerDialog::ParseShowDataMultiContent(const std::vector<NG::TextCascadePickerOptions>& options,
    const std::vector<uint32_t>& selectedValues, const std::vector<std::string>& values,
    NG::TextCascadePickerOptionsAttr& attr, NG::TextPickerSettingData& settingData)
{
    settingData.columnKind = NG::TEXT;
    for (auto& item : selectedValues) {
        settingData.selectedValues.emplace_back(item);
    }
    for (auto& item : values) {
        settingData.values.emplace_back(item);
    }
    for (auto& item : options) {
        settingData.options.emplace_back(item);
    }
    settingData.attr.isCascade = attr.isCascade;
    settingData.attr.isHasSelectAttr = attr.isHasSelectAttr;
}

bool JSTextPickerDialog::ParseShowData(const JSRef<JSObject>& paramObject, NG::TextPickerSettingData& settingData)
{
    ParseTextArrayParam param;
    bool rangeContentCheckErr = false;
    bool optionsCascadeContentCheckErr = false;
    NG::TextCascadePickerOptionsAttr attr;
    auto getRange = paramObject->GetProperty("range");
    if (getRange->IsNull() || getRange->IsUndefined()) {
        return false;
    }
    if (!JSTextPickerParser::ParseTextArray(paramObject, param)) {
        if (!JSTextPickerParser::ParseIconTextArray(paramObject, param.result, param.kind, param.selected)) {
            rangeContentCheckErr = true;
            param.result.clear();
        }
    }
    if (rangeContentCheckErr) {
        optionsCascadeContentCheckErr = !ParseShowDataOptions(paramObject, param, attr);
    }
    if (rangeContentCheckErr && optionsCascadeContentCheckErr) {
        return false;
    }
    if (memset_s(&settingData, sizeof(NG::TextPickerSettingData), 0, sizeof(NG::TextPickerSettingData)) != EOK) {
        return false;
    }
    if (!ParseShowDataAttribute(paramObject, settingData)) {
        return false;
    }
    ParseCanLoop(paramObject, settingData.canLoop);
    if (param.result.size() > 0) {
        settingData.selected = param.selected;
        settingData.columnKind = param.kind;
        for (const auto& item : param.result) {
            settingData.rangeVector.emplace_back(item);
        }
    } else {
        ParseShowDataMultiContent(param.options, param.selecteds, param.values, attr, settingData);
    }
    return true;
}

void JSTextPickerDialog::ParseTextProperties(const JSRef<JSObject>& paramObj, NG::PickerTextProperties& result)
{
    auto disappearProperty = paramObj->GetProperty("disappearTextStyle");
    auto normalProperty = paramObj->GetProperty("textStyle");
    auto selectedProperty = paramObj->GetProperty("selectedTextStyle");

    if (!disappearProperty->IsNull() && disappearProperty->IsObject()) {
        JSRef<JSObject> disappearObj = JSRef<JSObject>::Cast(disappearProperty);
        JSTextPickerParser::ParseTextStyle(disappearObj, result.disappearTextStyle_, "disappearTextStyle");
    }

    if (!normalProperty->IsNull() && normalProperty->IsObject()) {
        JSRef<JSObject> noramlObj = JSRef<JSObject>::Cast(normalProperty);
        JSTextPickerParser::ParseTextStyle(noramlObj, result.normalTextStyle_, "textStyle");
    }

    if (!selectedProperty->IsNull() && selectedProperty->IsObject()) {
        JSRef<JSObject> selectedObj = JSRef<JSObject>::Cast(selectedProperty);
        JSTextPickerParser::ParseTextStyle(selectedObj, result.selectedTextStyle_, "selectedTextStyle");
    }
}

std::map<std::string, NG::DialogTextEvent> JSTextPickerDialog::DialogEvent(const JSCallbackInfo& info)
{
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    if (!info[0]->IsObject()) {
        return dialogEvent;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto onAccept = paramObject->GetProperty("onAccept");
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (!onAccept->IsUndefined() && onAccept->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAccept));
        auto acceptId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                            const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "value", "index" };
            ACE_SCORING_EVENT("TextPickerDialog.onAccept");
            PipelineContext::SetCallBackNode(node);
            func->Execute(keys, info);
        };
        dialogEvent["acceptId"] = acceptId;
    }
    auto onChange = paramObject->GetProperty("onChange");
    if (!onChange->IsUndefined() && onChange->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onChange));
        auto changeId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                            const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "value", "index" };
            ACE_SCORING_EVENT("TextPickerDialog.onChange");
            PipelineContext::SetCallBackNode(node);
            func->Execute(keys, info);
        };
        dialogEvent["changeId"] = changeId;
    }
    auto onScrollStop = paramObject->GetProperty("onScrollStop");
    if (!onScrollStop->IsUndefined() && onScrollStop->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onScrollStop));
        auto scrollStopId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                            const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "value", "index" };
            ACE_SCORING_EVENT("TextPickerDialog.onScrollStop");
            PipelineContext::SetCallBackNode(node);
            func->Execute(keys, info);
        };
        dialogEvent["scrollStopId"] = scrollStopId;
    }
    return dialogEvent;
}

std::map<std::string, NG::DialogGestureEvent> JSTextPickerDialog::DialogCancelEvent(const JSCallbackInfo& info)
{
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    if (!info[0]->IsObject()) {
        return dialogCancelEvent;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto onCancel = paramObject->GetProperty("onCancel");
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (!onCancel->IsUndefined() && onCancel->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onCancel));
        auto cancelId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                            const GestureEvent& /* info */) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("TextPickerDialog.onCancel");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        dialogCancelEvent["cancelId"] = cancelId;
    }
    return dialogCancelEvent;
}

void JSTextPickerDialog::AddEvent(RefPtr<PickerTextComponent>& picker, const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto onAccept = paramObject->GetProperty("onAccept");
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (!onAccept->IsUndefined() && onAccept->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAccept));
        auto acceptId = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                                        const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "value", "index" };
            ACE_SCORING_EVENT("TextPickerDialog.onAccept");
            PipelineContext::SetCallBackNode(node);
            func->Execute(keys, info);
        });
        picker->SetDialogAcceptEvent(acceptId);
    }
    auto onCancel = paramObject->GetProperty("onCancel");
    if (!onCancel->IsUndefined() && onCancel->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onCancel));
        auto cancelId =
            EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("TextPickerDialog.onCancel");
                PipelineContext::SetCallBackNode(node);
                func->Execute();
            });
        picker->SetDialogCancelEvent(cancelId);
    }
    auto onChange = paramObject->GetProperty("onChange");
    if (!onChange->IsUndefined() && onChange->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onChange));
        auto changeId = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                                        const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "value", "index" };
            ACE_SCORING_EVENT("TextPickerDialog.onChange");
            PipelineContext::SetCallBackNode(node);
            func->Execute(keys, info);
        });
        picker->SetDialogChangeEvent(changeId);
    }
}

void JSTextPickerDialog::ParseText(RefPtr<PickerTextComponent>& component, const JSRef<JSObject>& paramObj)
{
    auto getSelected = paramObj->GetProperty("selected");
    auto defaultHeight = paramObj->GetProperty("defaultPickerItemHeight");
    auto canLoop = paramObj->GetProperty("canLoop");
    JSRef<JSArray> getRange = paramObj->GetProperty("range");
    std::vector<std::string> getRangeVector;
    if (!JSViewAbstract::ParseJsStrArray(getRange, getRangeVector)) {
        return;
    }

    std::string value = "";
    uint32_t selectedValue = 0;
    auto getValue = paramObj->GetProperty("value");
    if (!JSViewAbstract::ParseJsInteger(getSelected, selectedValue) && JSViewAbstract::ParseJsString(getValue, value)) {
        auto valueIterator = std::find(getRangeVector.begin(), getRangeVector.end(), value);
        if (valueIterator != getRangeVector.end()) {
            selectedValue = static_cast<uint32_t>(std::distance(getRangeVector.begin(), valueIterator));
        }
    }

    if (selectedValue >= getRangeVector.size()) {
        selectedValue = 0;
    }

    CalcDimension height;
    if (defaultHeight->IsNumber() || defaultHeight->IsString()) {
        if (!JSViewAbstract::ParseJsDimensionFp(defaultHeight, height)) {
            return;
        }
    }

    component->SetIsDialog(true);
    component->SetIsCreateDialogComponent(true);
    if (!defaultHeight->IsEmpty()) {
        component->SetColumnHeight(height);
        component->SetDefaultHeight(true);
    }
    component->SetSelected(selectedValue);
    component->SetRange(getRangeVector);
}
} // namespace OHOS::Ace::Framework
