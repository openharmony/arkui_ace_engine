/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include <securec.h>

#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_datepicker.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/textpicker_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {

std::unique_ptr<TextPickerModel> TextPickerModel::textPickerInstance_ = nullptr;

TextPickerModel* TextPickerModel::GetInstance()
{
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
    return textPickerInstance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSTextPicker::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextPicker>::Declare("TextPicker");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTextPicker>::StaticMethod("create", &JSTextPicker::Create, opt);
    JSClass<JSTextPicker>::StaticMethod("defaultPickerItemHeight", &JSTextPicker::SetDefaultPickerItemHeight);
    JSClass<JSTextPicker>::StaticMethod("disappearTextStyle", &JSTextPicker::SetDisappearTextStyle);
    JSClass<JSTextPicker>::StaticMethod("textStyle", &JSTextPicker::SetTextStyle);
    JSClass<JSTextPicker>::StaticMethod("selectedTextStyle", &JSTextPicker::SetSelectedTextStyle);
    JSClass<JSTextPicker>::StaticMethod("onAccept", &JSTextPicker::OnAccept);
    JSClass<JSTextPicker>::StaticMethod("onCancel", &JSTextPicker::OnCancel);
    JSClass<JSTextPicker>::StaticMethod("onChange", &JSTextPicker::OnChange);
    JSClass<JSTextPicker>::StaticMethod("backgroundColor", &JSDatePicker::PickerBackgroundColor);
    JSClass<JSTextPicker>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTextPicker>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTextPicker>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTextPicker>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTextPicker>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTextPicker>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTextPicker>::Inherit<JSViewAbstract>();
    JSClass<JSTextPicker>::Bind(globalObj);
}

void JSTextPicker::Create(const JSCallbackInfo& info)
{
    if (info.Length() >= 1 && info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        std::vector<NG::RangeContent> rangeResult;
        uint32_t selected = 0;
        uint32_t kind = 0;
        std::string value = "";
        if (!JSTextPickerParser::ParseTextArray(paramObject, rangeResult, kind, selected, value)) {
            if (!JSTextPickerParser::ParseIconTextArray(paramObject, rangeResult, kind, selected)) {
                LOGE("parse range error.");
                return;
            }
        }

        auto theme = GetTheme<PickerTheme>();
        if (!theme) {
            LOGE("PickerText Theme is null");
            return;
        }
        TextPickerModel::GetInstance()->Create(theme, kind);
        TextPickerModel::GetInstance()->SetRange(rangeResult);
        TextPickerModel::GetInstance()->SetSelected(selected);
        TextPickerModel::GetInstance()->SetValue(value);
        TextPickerModel::GetInstance()->SetDefaultAttributes(theme);
        JSInteractableView::SetFocusable(false);
        JSInteractableView::SetFocusNode(true);
    }
}

bool JSTextPickerParser::ParseTextArray(const JSRef<JSObject>& paramObject,
    std::vector<NG::RangeContent>& result, uint32_t& kind, uint32_t& selected, std::string& value)
{
    auto getSelected = paramObject->GetProperty("selected");
    auto getValue = paramObject->GetProperty("value");
    JSRef<JSArray> getRange = paramObject->GetProperty("range");
    std::vector<std::string> getRangeVector;
    if (getRange->Length() == 0) {
        return false;
    }
    if (!ParseJsStrArray(getRange, getRangeVector)) {
        LOGE("parse str array error.");
        return false;
    }
    result.clear();
    for (const auto& text : getRangeVector) {
        NG::RangeContent content;
        content.icon_ = "";
        content.text_ = text;
        result.emplace_back(content);
    }
    kind = NG::TEXT;
    if (!ParseJsString(getValue, value)) {
        value = getRangeVector.front();
    }
    if (!ParseJsInteger(getSelected, selected) && !value.empty()) {
        auto valueIterator = std::find(getRangeVector.begin(), getRangeVector.end(), value);
        if (valueIterator != getRangeVector.end()) {
            selected = std::distance(getRangeVector.begin(), valueIterator);
        }
    }

    if (selected < 0 || selected >= getRangeVector.size()) {
        LOGE("selected is out of range");
        selected = 0;
    }
    return true;
}

bool JSTextPickerParser::ParseIconTextArray(const JSRef<JSObject>& paramObject,
    std::vector<NG::RangeContent>& result, uint32_t& kind, uint32_t& selected)
{
    auto getSelected = paramObject->GetProperty("selected");
    auto getRange = paramObject->GetProperty("range");
    if (!getRange->IsArray()) {
        LOGE("arg is not array.");
        return false;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(getRange);
    result.clear();
    kind = 0;
    for (size_t i = 0; i < array->Length(); i++) {
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
    if (!kind) {
        LOGE("kind is wrong.");
        return false;
    }

    if (!ParseJsInteger(getSelected, selected)) {
        selected = 0;
    }
    return true;
}

void JSTextPickerParser::ParseTextStyle(const JSRef<JSObject>& paramObj, NG::PickerTextStyle& textStyle)
{
    auto fontColor = paramObj->GetProperty("color");
    auto fontStyle = paramObj->GetProperty("font");

    Color textColor;
    if (ParseJsColor(fontColor, textColor)) {
        textStyle.textColor = textColor;
    }

    if (!fontStyle->IsObject()) {
        LOGE("fontStyle is not obj.");
        return;
    }
    JSRef<JSObject> fontObj = JSRef<JSObject>::Cast(fontStyle);
    auto fontSize = fontObj->GetProperty("size");
    auto fontWeight = fontObj->GetProperty("weight");
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        textStyle.fontSize = Dimension(-1);
    } else {
        Dimension size;
        if (!ParseJsDimensionFp(fontSize, size) || size.Unit() == DimensionUnit::PERCENT) {
            textStyle.fontSize = Dimension(-1);
            LOGW("Parse to dimension FP failed.");
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
}

void JSTextPicker::SetDefaultPickerItemHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 argument.");
        return;
    }
    Dimension height;
    if (info[0]->IsNumber() || info[0]->IsString()) {
        if (!ParseJsDimensionFp(info[0], height)) {
            return;
        }
    }
    TextPickerModel::GetInstance()->SetDefaultPickerItemHeight(height);
}

void JSTextPicker::SetDisappearTextStyle(const JSCallbackInfo& info)
{
    auto theme = GetTheme<PickerTheme>();
    if (!theme) {
        LOGE("PickerText Theme is null");
        return;
    }
    NG::PickerTextStyle textStyle;
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
    } else {
        JSTextPickerParser::ParseTextStyle(info[0], textStyle);
    }
    TextPickerModel::GetInstance()->SetDisappearTextStyle(theme, textStyle);
}

void JSTextPicker::SetTextStyle(const JSCallbackInfo& info)
{
    auto theme = GetTheme<PickerTheme>();
    if (!theme) {
        LOGE("PickerText Theme is null");
        return;
    }
    NG::PickerTextStyle textStyle;
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
    } else {
        JSTextPickerParser::ParseTextStyle(info[0], textStyle);
    }
    TextPickerModel::GetInstance()->SetNormalTextStyle(theme, textStyle);
}

void JSTextPicker::SetSelectedTextStyle(const JSCallbackInfo& info)
{
    auto theme = GetTheme<PickerTheme>();
    if (!theme) {
        LOGE("PickerText Theme is null");
        return;
    }
    NG::PickerTextStyle textStyle;
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
    } else {
        JSTextPickerParser::ParseTextStyle(info[0], textStyle);
    }
    TextPickerModel::GetInstance()->SetSelectedTextStyle(theme, textStyle);
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
                        const std::string& value, double index) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("TextPicker.onChange");
        auto params = ConvertToJSValues(value, index);
        func->Call(JSRef<JSObject>(), static_cast<int>(params.size()), params.data());
    };
    TextPickerModel::GetInstance()->SetOnChange(std::move(onChange));
    info.ReturnSelf();
}

void JSTextPickerDialog::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextPickerDialog>::Declare("TextPickerDialog");
    JSClass<JSTextPickerDialog>::StaticMethod("show", &JSTextPickerDialog::Show);

    JSClass<JSTextPickerDialog>::Bind<>(globalObj);
}

void JSTextPickerDialog::Show(const JSCallbackInfo& info)
{
    auto scopedDelegate = EngineHelper::GetCurrentDelegate();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        LOGE("scopedDelegate is null, please check");
        return;
    }
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("TextPicker create error, info is non-valid");
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);

    if (Container::IsCurrentUseNewPipeline()) {
        auto dialogEvent = DialogEvent(info);
        auto dialogCancelEvent = DialogCancelEvent(info);
        TextPickerDialogShow(paramObject, dialogEvent, dialogCancelEvent);
        return;
    }

    auto PickerText = AceType::MakeRefPtr<PickerTextComponent>();
    if (!PickerText) {
        LOGE("PickerText Component is null");
        return;
    }
    ParseText(PickerText, paramObject);
    DialogProperties properties {};
    properties.alignment = DialogAlignment::CENTER;
    properties.customComponent = PickerText;
    properties.customStyle = true;
    AddEvent(PickerText, info);
    PickerText->SetDialogName("pickerTextDialog");
    PickerText->OpenDialog(properties);
}

void JSTextPickerDialog::TextPickerDialogShow(const JSRef<JSObject>& paramObj,
    const std::map<std::string, NG::DialogTextEvent>& dialogEvent,
    const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent)
{
    auto container = Container::Current();
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
    if (!theme) {
        LOGE("DialogTheme is null");
        return;
    }

    NG::TextPickerSettingData settingData;
    if (!ParseShowData(paramObj, settingData)) {
        return;
    }

    DialogProperties properties;
    ButtonInfo buttonInfo;
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        properties.alignment = DialogAlignment::BOTTOM;
    } else {
        properties.alignment = DialogAlignment::CENTER;
    }
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));

    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowTextDialog(properties, settingData, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI);
}

bool JSTextPickerDialog::ParseShowData(const JSRef<JSObject>& paramObject, NG::TextPickerSettingData& settingData)
{
    std::vector<NG::RangeContent> rangeResult;
    uint32_t selected = 0;
    uint32_t kind = 0;
    std::string value = "";
    if (!JSTextPickerParser::ParseTextArray(paramObject, rangeResult, kind, selected, value)) {
        if (!JSTextPickerParser::ParseIconTextArray(paramObject, rangeResult, kind, selected)) {
            LOGE("parse range error.");
            return false;
        }
    }

    Dimension height;
    auto defaultHeight = paramObject->GetProperty("defaultPickerItemHeight");
    if (defaultHeight->IsNumber() || defaultHeight->IsString()) {
        if (!JSViewAbstract::ParseJsDimensionFp(defaultHeight, height)) {
            return false;
        }
    }

    NG::PickerTextProperties textProperties;
    ParseTextProperties(paramObject, textProperties);
    if (memset_s(&settingData, sizeof(NG::TextPickerSettingData), 0, sizeof(NG::TextPickerSettingData)) != EOK) {
        LOGE("memset settingData error.");
        return false;
    }
    settingData.height = height;
    settingData.selected = selected;
    settingData.columnKind = kind;
    if (memcpy_s(&settingData.properties, sizeof(NG::PickerTextProperties),
        &textProperties, sizeof(NG::PickerTextProperties)) != EOK) {
        LOGE("memcpy properties error.");
        return false;
    }
    for (const auto& item : rangeResult) {
        settingData.rangeVector.emplace_back(item);
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
        JSTextPickerParser::ParseTextStyle(disappearObj, result.disappearTextStyle_);
    }

    if (!normalProperty->IsNull() && normalProperty->IsObject()) {
        JSRef<JSObject> noramlObj = JSRef<JSObject>::Cast(normalProperty);
        JSTextPickerParser::ParseTextStyle(noramlObj, result.normalTextStyle_);
    }

    if (!selectedProperty->IsNull() && selectedProperty->IsObject()) {
        JSRef<JSObject> selectedObj = JSRef<JSObject>::Cast(selectedProperty);
        JSTextPickerParser::ParseTextStyle(selectedObj, result.selectedTextStyle_);
    }
}

std::map<std::string, NG::DialogTextEvent> JSTextPickerDialog::DialogEvent(const JSCallbackInfo& info)
{
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("TextPicker AddEvent error, info is non-valid");
        return dialogEvent;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto onAccept = paramObject->GetProperty("onAccept");
    if (!onAccept->IsUndefined() && onAccept->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAccept));
        auto acceptId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "value", "index" };
            ACE_SCORING_EVENT("TextPickerDialog.onAccept");
            func->Execute(keys, info);
        };
        dialogEvent["acceptId"] = acceptId;
    }
    auto onChange = paramObject->GetProperty("onChange");
    if (!onChange->IsUndefined() && onChange->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onChange));
        auto changeId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "value", "index" };
            ACE_SCORING_EVENT("TextPickerDialog.onChange");
            func->Execute(keys, info);
        };
        dialogEvent["changeId"] = changeId;
    }
    return dialogEvent;
}

std::map<std::string, NG::DialogGestureEvent> JSTextPickerDialog::DialogCancelEvent(const JSCallbackInfo& info)
{
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("TextPicker AddEvent error, info is non-valid");
        return dialogCancelEvent;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto onCancel = paramObject->GetProperty("onCancel");
    if (!onCancel->IsUndefined() && onCancel->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onCancel));
        auto cancelId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const GestureEvent& /*info*/) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("TextPickerDialog.onCancel");
            func->Execute();
        };
        dialogCancelEvent["cancelId"] = cancelId;
    }
    return dialogCancelEvent;
}

void JSTextPickerDialog::AddEvent(RefPtr<PickerTextComponent>& picker, const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("TextPicker AddEvent error, info is non-valid");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto onAccept = paramObject->GetProperty("onAccept");
    if (!onAccept->IsUndefined() && onAccept->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAccept));
        auto acceptId =
            EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                std::vector<std::string> keys = { "value", "index" };
                ACE_SCORING_EVENT("TextPickerDialog.onAccept");
                func->Execute(keys, info);
            });
        picker->SetDialogAcceptEvent(acceptId);
    }
    auto onCancel = paramObject->GetProperty("onCancel");
    if (!onCancel->IsUndefined() && onCancel->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onCancel));
        auto cancelId = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("TextPickerDialog.onCancel");
            func->Execute();
        });
        picker->SetDialogCancelEvent(cancelId);
    }
    auto onChange = paramObject->GetProperty("onChange");
    if (!onChange->IsUndefined() && onChange->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onChange));
        auto changeId =
            EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                std::vector<std::string> keys = { "value", "index" };
                ACE_SCORING_EVENT("TextPickerDialog.onChange");
                func->Execute(keys, info);
            });
        picker->SetDialogChangeEvent(changeId);
    }
}

void JSTextPickerDialog::ParseText(RefPtr<PickerTextComponent>& component, const JSRef<JSObject>& paramObj)
{
    auto getSelected = paramObj->GetProperty("selected");
    auto defaultHeight = paramObj->GetProperty("defaultPickerItemHeight");
    JSRef<JSArray> getRange = paramObj->GetProperty("range");
    std::vector<std::string> getRangeVector;
    if (!JSViewAbstract::ParseJsStrArray(getRange, getRangeVector)) {
        LOGE("parse range failed");
        return;
    }

    std::string value = "";
    uint32_t selected = 0;
    auto getValue = paramObj->GetProperty("value");
    if (!JSViewAbstract::ParseJsInteger(getSelected, selected) && JSViewAbstract::ParseJsString(getValue, value)) {
        auto valueIterator = std::find(getRangeVector.begin(), getRangeVector.end(), value);
        if (valueIterator != getRangeVector.end()) {
            selected = std::distance(getRangeVector.begin(), valueIterator);
        }
    }

    if (selected < 0 || selected >= getRangeVector.size()) {
        LOGE("selected is out of range");
        selected = 0;
    }

    Dimension height;
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
    component->SetSelected(selected);
    component->SetRange(getRangeVector);
}
} // namespace OHOS::Ace::Framework
