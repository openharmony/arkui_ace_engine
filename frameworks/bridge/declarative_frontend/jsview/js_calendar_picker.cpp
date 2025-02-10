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

#include "frameworks/bridge/declarative_frontend/jsview/js_calendar_picker.h"

#include "base/log/ace_scoring_log.h"
#include "base/utils/date_util.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/calendar_picker_model_impl.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
std::unique_ptr<CalendarPickerModel> CalendarPickerModel::instance_ = nullptr;
std::once_flag CalendarPickerModel::onceFlag_;

CalendarPickerModel* CalendarPickerModel::GetInstance()
{
    std::call_once(onceFlag_, []() {
#ifdef NG_BUILD
        instance_.reset(new NG::CalendarPickerModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::CalendarPickerModelNG());
        } else {
            instance_.reset(new Framework::CalendarPickerModelImpl());
        }
#endif
    });

    return instance_.get();
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

double GetMSByDate(const std::string& date)
{
    auto json = JsonUtil::ParseJsonString(date);
    if (!json || json->IsNull()) {
        return 0.0f;
    }

    std::tm dateTime {};
    auto year = json->GetValue("year");
    if (year && year->IsNumber()) {
        dateTime.tm_year = year->GetInt() - 1900; // local date start from 1900
    }
    auto month = json->GetValue("month");
    if (month && month->IsNumber()) {
        dateTime.tm_mon = month->GetInt() - 1;
    }
    auto day = json->GetValue("day");
    if (day && day->IsNumber()) {
        dateTime.tm_mday = day->GetInt();
    }
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto local = std::localtime(&now);
    CHECK_NULL_RETURN(local, 0.0f);
    dateTime.tm_hour = local->tm_hour;
    dateTime.tm_min = local->tm_min;
    dateTime.tm_sec = local->tm_sec;
    return Date::GetMilliSecondsByDateTime(dateTime);
}

void JSCalendarPicker::JSBind(BindingTarget globalObj)
{
    JSClass<JSCalendarPicker>::Declare("CalendarPicker");
    JSClass<JSCalendarPicker>::StaticMethod("create", &JSCalendarPicker::Create, MethodOptions::NONE);
    JSClass<JSCalendarPicker>::StaticMethod("edgeAlign", &JSCalendarPicker::SetEdgeAlign);
    JSClass<JSCalendarPicker>::StaticMethod("textStyle", &JSCalendarPicker::SetTextStyle);
    JSClass<JSCalendarPicker>::StaticMethod("onChange", &JSCalendarPicker::SetOnChange);
    JSClass<JSCalendarPicker>::StaticMethod("border", &JSCalendarPicker::SetBorder);
    JSClass<JSCalendarPicker>::StaticMethod("padding", &JSCalendarPicker::JsPadding);
    JSClass<JSCalendarPicker>::StaticMethod("height", &JSCalendarPicker::JsHeight);
    JSClass<JSCalendarPicker>::StaticMethod("borderColor", &JSCalendarPicker::JsBorderColor);
    JSClass<JSCalendarPicker>::StaticMethod("borderRadius", &JSCalendarPicker::JsBorderRadius);
    JSClass<JSCalendarPicker>::StaticMethod("markToday", &JSCalendarPicker::JsMarkToday);
    JSClass<JSCalendarPicker>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCalendarPicker>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSCalendarPicker>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSCalendarPicker>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSCalendarPicker>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSCalendarPicker>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSCalendarPicker>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSCalendarPicker>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSCalendarPicker>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSCalendarPicker::SetBorder(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        CalendarPickerModel::GetInstance()->ClearBorder();
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
    auto valueWidth = object->GetProperty("width");
    CalcDimension value;
    if (ParseJsDimensionVpNG(valueWidth, value) || valueWidth->IsObject()) {
        ParseBorderWidth(valueWidth);
    } else {
        CalendarPickerModel::GetInstance()->ClearBorderWidth();
    }

    // use default value when undefined.
    ParseCalendarPickerBorderColor(object->GetProperty("color"));

    auto valueRadius = object->GetProperty("radius");
    if (!valueRadius->IsUndefined()) {
        ParseBorderRadius(valueRadius);
    }
    // use default value when undefined.
    ParseBorderStyle(object->GetProperty("style"));

    info.ReturnSelf();
}

void JSCalendarPicker::ParseCalendarPickerBorderColor(const JSRef<JSVal>& args)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        ViewAbstractModel::GetInstance()->SetBorderColor(theme->GetEntryBorderColor());
    } else {
        JSViewAbstract::ParseBorderColor(args);
    }
}

void JSCalendarPicker::SetEdgeAlign(const JSCallbackInfo& info)
{
    NG::CalendarEdgeAlign alignType = NG::CalendarEdgeAlign::EDGE_ALIGN_END;
    DimensionOffset offset;
    if (info[0]->IsNumber()) {
        alignType = static_cast<NG::CalendarEdgeAlign>(info[0]->ToNumber<int32_t>());
    }

    if (!info[1]->IsObject()) {
        CalendarPickerModel::GetInstance()->SetEdgeAlign(alignType, offset);
        return;
    }
    auto offsetObj = JSRef<JSObject>::Cast(info[1]);
    CalcDimension dx;
    auto dxValue = offsetObj->GetProperty("dx");
    ParseJsDimensionVp(dxValue, dx);
    CalcDimension dy;
    auto dyValue = offsetObj->GetProperty("dy");
    ParseJsDimensionVp(dyValue, dy);
    offset = DimensionOffset(dx, dy);

    CalendarPickerModel::GetInstance()->SetEdgeAlign(alignType, offset);
}

void JSCalendarPicker::SetTextStyle(const JSCallbackInfo& info)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    NG::PickerTextStyle textStyle;
    textStyle.fontSize = calendarTheme->GetEntryFontSize();
    textStyle.textColor = calendarTheme->GetEntryFontColor();
    textStyle.fontWeight = FontWeight::NORMAL;
    if (!info[0]->IsObject()) {
        CalendarPickerModel::GetInstance()->SetTextStyle(textStyle);
        return;
    }
    JSCalendarPicker::ParseTextStyle(info[0], textStyle);
    CalendarPickerModel::GetInstance()->SetTextStyle(textStyle);
}

void JSCalendarPicker::SetOnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        const std::string& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("CalendarPicker.onChange");
        PipelineContext::SetCallBackNode(node);
        auto dateObj = JSDate::New(GetMSByDate(info));
        func->ExecuteJS(1, &dateObj);
    };
    CalendarPickerModel::GetInstance()->SetOnChange(std::move(onChange));
}

void JSCalendarPicker::JsPadding(const JSCallbackInfo& info)
{
    NG::PaddingProperty padding;
    if (info[0]->IsObject()) {
        CommonCalcDimension commonCalcDimension;
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);
        JSViewAbstract::ParseCommonMarginOrPaddingCorner(paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            padding = SetPaddings(commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left,
                commonCalcDimension.right);
            CalendarPickerModel::GetInstance()->SetPadding(padding);
            return;
        }
    }

    CalcDimension length(-1);
    if (ParseJsDimensionVpNG(info[0], length) && length.IsNonNegative()) {
        padding.SetEdges(NG::CalcLength(length));
        CalendarPickerModel::GetInstance()->SetPadding(padding);
    } else {
        CalendarPickerModel::GetInstance()->ClearPadding();
    }
}

void JSCalendarPicker::JsHeight(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CalcDimension value;
    if (ParseJsDimensionVpNG(jsValue, value) && value.IsValid()) {
        JSViewAbstract::JsHeight(info);
    } else {
        CalendarPickerModel::GetInstance()->ClearHeight();
    }
}

void JSCalendarPicker::JsBorderColor(const JSCallbackInfo& info)
{
    Color borderColor;
    auto jsValue = info[0];
    if (ParseJsColor(jsValue, borderColor) || jsValue->IsObject()) {
        JSViewAbstract::JsBorderColor(info);
    } else {
        CalendarPickerModel::GetInstance()->ClearBorderColor();
    }
}

void JSCalendarPicker::JsBorderRadius(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CalcDimension value;
    if (ParseJsDimensionVpNG(jsValue, value) || jsValue->IsObject()) {
        JSViewAbstract::JsBorderRadius(info);
    } else {
        CalendarPickerModel::GetInstance()->ClearBorderRadius();
    }
}

NG::PaddingProperty JSCalendarPicker::SetPaddings(const std::optional<CalcDimension>& top,
    const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
    const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty paddings;
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            paddings.top =
                NG::CalcLength(top.value().IsNonNegative() ? top.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.top = NG::CalcLength(top.value().IsNonNegative() ? top.value() : CalcDimension());
        }
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            paddings.bottom = NG::CalcLength(
                bottom.value().IsNonNegative() ? bottom.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.bottom = NG::CalcLength(bottom.value().IsNonNegative() ? bottom.value() : CalcDimension());
        }
    }
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            paddings.left =
                NG::CalcLength(left.value().IsNonNegative() ? left.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.left = NG::CalcLength(left.value().IsNonNegative() ? left.value() : CalcDimension());
        }
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            paddings.right =
                NG::CalcLength(right.value().IsNonNegative() ? right.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.right = NG::CalcLength(right.value().IsNonNegative() ? right.value() : CalcDimension());
        }
    }

    return paddings;
}

void JSCalendarPicker::ParseSelectedDateObject(const JSCallbackInfo& info, const JSRef<JSObject>& selectedObject)
{
    JSRef<JSVal> changeEventVal = selectedObject->GetProperty("changeEvent");
    if (!changeEventVal->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto changeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                           const std::string& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("DatePicker.SelectedDateTimeChangeEvent");
        PipelineContext::SetCallBackNode(node);
        auto dateObj = JSDate::New(GetMSByDate(info));
        func->ExecuteJS(1, &dateObj);
    };
    CalendarPickerModel::GetInstance()->SetChangeEvent(std::move(changeEvent));
}

void JSCalendarPicker::ParseDisabledDateRange(
    const JSRef<JSVal>& disabledDateRangeVal, NG::CalendarSettingData& settingData)
{
    if (disabledDateRangeVal->IsUndefined() || disabledDateRangeVal->IsNull() || !disabledDateRangeVal->IsArray()) {
        return;
    }

    JSRef<JSArray> array = JSRef<JSArray>::Cast(disabledDateRangeVal);
    for (size_t i = 0; i < array->Length(); i++) {
        JSRef<JSVal> dateRangeValue = array->GetValueAt(i);
        auto dateRangeObj = JSRef<JSObject>::Cast(dateRangeValue);
        auto startValue = dateRangeObj->GetProperty("start");
        auto endValue = dateRangeObj->GetProperty("end");
        if (startValue->IsObject() && endValue->IsObject()) {
            auto startDate = ParseDate(startValue, false);
            auto endDate = ParseDate(endValue, false);
            if (startDate.GetYear() == 0 || endDate.GetYear() == 0 || endDate < startDate)
                continue;
            std::pair<PickerDate, PickerDate> pickerDateRange;
            pickerDateRange.first = startDate;
            pickerDateRange.second = endDate;
            settingData.disabledDateRange.emplace_back(pickerDateRange);
        }
    }
}

void JSCalendarPicker::Create(const JSCallbackInfo& info)
{
    NG::CalendarSettingData settingData;
    RefPtr<CalendarTheme> calendarTheme = GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    CalcDimension dayRadius;
    if (info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        if (!ParseJsDimensionVpNG(obj->GetProperty("hintRadius"), dayRadius)) {
            dayRadius = calendarTheme->GetCalendarDayRadius();
        }
        auto selected = obj->GetProperty("selected");
        auto parseSelectedDate = ParseDate(selected);
        if (selected->IsObject() && parseSelectedDate.GetYear() != 0) {
            JSRef<JSObject> selectedDateObj = JSRef<JSObject>::Cast(selected);
            JSRef<JSVal> changeEventVal = selectedDateObj->GetProperty("changeEvent");
            if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction()) {
                ParseSelectedDateObject(info, selectedDateObj);
                settingData.selectedDate = ParseDate(selectedDateObj->GetProperty("value"));
            } else {
                settingData.selectedDate = parseSelectedDate;
            }
        }
        auto disabledDateRange = obj->GetProperty("disabledDateRange");
        ParseDisabledDateRange(disabledDateRange, settingData);
        PickerDate::SortAndMergeDisabledDateRange(settingData.disabledDateRange);
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
            auto startDate = obj->GetProperty("start");
            auto endDate = obj->GetProperty("end");
            auto parseStartDate = ParseDate(startDate, false);
            auto parseEndDate = ParseDate(endDate, false);
            if (parseEndDate.GetYear() > 0 && parseStartDate.ToDays() > parseEndDate.ToDays()) {
                parseStartDate = PickerDate();
                parseEndDate = PickerDate();
            }
            settingData.startDate = parseStartDate;
            settingData.endDate = parseEndDate;
        }
    } else {
        dayRadius = calendarTheme->GetCalendarDayRadius();
    }
    settingData.dayRadius = dayRadius;
    CalendarPickerModel::GetInstance()->Create(settingData);
}

void JSCalendarPicker::ParseTextStyle(const JSRef<JSObject>& paramObj, NG::PickerTextStyle& textStyle)
{
    auto fontColor = paramObj->GetProperty("color");
    auto fontStyle = paramObj->GetProperty("font");

    Color color;
    if (ParseJsColor(fontColor, color)) {
        textStyle.textColor = color;
    }

    if (!fontStyle->IsObject()) {
        return;
    }
    JSRef<JSObject> fontObj = JSRef<JSObject>::Cast(fontStyle);
    auto fontSize = fontObj->GetProperty("size");
    auto fontWeight = fontObj->GetProperty("weight");
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        textStyle.fontSize = Dimension(-1);
    } else {
        CalcDimension size;
        if (!ParseJsDimensionFpNG(fontSize, size) || size.Unit() == DimensionUnit::PERCENT) {
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
}

PickerDate JSCalendarPicker::ParseDate(const JSRef<JSVal>& dateVal, bool useCurrentDate)
{
    auto pickerDate = useCurrentDate ? PickerDate::Current() : PickerDate();
    if (!dateVal->IsObject()) {
        return pickerDate;
    }
    auto dateObj = JSRef<JSObject>::Cast(dateVal);
    auto yearFuncJsVal = dateObj->GetProperty("getFullYear");
    auto monthFuncJsVal = dateObj->GetProperty("getMonth");
    auto dateFuncJsVal = dateObj->GetProperty("getDate");
    if (!(yearFuncJsVal->IsFunction() && monthFuncJsVal->IsFunction() && dateFuncJsVal->IsFunction())) {
        return pickerDate;
    }
    auto yearFunc = JSRef<JSFunc>::Cast(yearFuncJsVal);
    auto monthFunc = JSRef<JSFunc>::Cast(monthFuncJsVal);
    auto dateFunc = JSRef<JSFunc>::Cast(dateFuncJsVal);
    JSRef<JSVal> year = yearFunc->Call(dateObj);
    JSRef<JSVal> month = monthFunc->Call(dateObj);
    JSRef<JSVal> date = dateFunc->Call(dateObj);

    if (year->IsNumber() && month->IsNumber() && date->IsNumber()) {
        pickerDate.SetYear(year->ToNumber<int32_t>());
        pickerDate.SetMonth(month->ToNumber<int32_t>() + 1); // 0-11 means 1 to 12 months
        pickerDate.SetDay(date->ToNumber<int32_t>());
    }
    return pickerDate;
}

void JSCalendarPicker::JsMarkToday(const JSCallbackInfo& info)
{
    bool isMarkToday = false;
    if (info[0]->IsBoolean()) {
        isMarkToday = info[0]->ToBoolean();
    }
    CalendarPickerModel::GetInstance()->SetMarkToday(isMarkToday);
}

void JSCalendarPickerDialog::JSBind(BindingTarget globalObj)
{
    JSClass<JSCalendarPickerDialog>::Declare("CalendarPickerDialog");
    JSClass<JSCalendarPickerDialog>::StaticMethod("show", &JSCalendarPickerDialog::Show);
    JSClass<JSCalendarPickerDialog>::Bind<>(globalObj);
}

void JSCalendarPickerDialog::Show(const JSCallbackInfo& info)
{
    auto scopedDelegate = EngineHelper::GetCurrentDelegateSafely();
    CHECK_NULL_VOID(scopedDelegate);
    if (!info[0]->IsObject()) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto buttonInfos = ParseButtonStyles(paramObject);
        auto dialogEvent = ChangeDialogEvent(info);
        auto dialogCancelEvent = DialogCancelEvent(info);
        auto dialogLifeCycleEvent = LifeCycleDialogEvent(info);
        CalendarPickerDialogShow(paramObject, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos);
    }
}

std::map<std::string, NG::DialogEvent> JSCalendarPickerDialog::ChangeDialogEvent(const JSCallbackInfo& info)
{
    std::map<std::string, NG::DialogEvent> dialogEvent;
    if (!info[0]->IsObject()) {
        return dialogEvent;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto onChange = paramObject->GetProperty("onChange");
    if (!onChange->IsUndefined() && onChange->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onChange));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto changeId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                            const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CalendarDialog.onChange");
            PipelineContext::SetCallBackNode(node);
            auto dateObj = JSDate::New(GetMSByDate(info));
            func->ExecuteJS(1, &dateObj);
        };
        dialogEvent["changeId"] = changeId;
    }
    auto onAccept = paramObject->GetProperty("onAccept");
    if (!onAccept->IsUndefined() && onAccept->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAccept));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto acceptId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                            const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CalendarDialog.onAccept");
            PipelineContext::SetCallBackNode(node);
            auto dateObj = JSDate::New(GetMSByDate(info));
            func->ExecuteJS(1, &dateObj);
        };
        dialogEvent["acceptId"] = acceptId;
    }
    return dialogEvent;
}

std::map<std::string, NG::DialogGestureEvent> JSCalendarPickerDialog::DialogCancelEvent(const JSCallbackInfo& info)
{
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    if (!info[0]->IsObject()) {
        return dialogCancelEvent;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto onCancel = paramObject->GetProperty("onCancel");
    if (!onCancel->IsUndefined() && onCancel->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onCancel));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto cancelId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                            const GestureEvent& /* info */) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CalendarDialog.onCancel");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        dialogCancelEvent["cancelId"] = cancelId;
    }
    return dialogCancelEvent;
}

void AppearDialogEvent(const JSCallbackInfo& info, std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidAppear = paramObject->GetProperty("onDidAppear");
    if (!onDidAppear->IsUndefined() && onDidAppear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDidAppear));
        auto didAppearId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CalendarDialog.onDidAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        dialogLifeCycleEvent["didAppearId"] = didAppearId;
    }
    auto onWillAppear = paramObject->GetProperty("onWillAppear");
    if (!onWillAppear->IsUndefined() && onWillAppear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillAppear));
        auto willAppearId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CalendarDialog.onWillAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        dialogLifeCycleEvent["willAppearId"] = willAppearId;
    }
}

void DisappearDialogEvent(
    const JSCallbackInfo& info, std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidDisappear = paramObject->GetProperty("onDidDisappear");
    if (!onDidDisappear->IsUndefined() && onDidDisappear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDidDisappear));
        auto didDisappearId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CalendarDialog.onDidDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        dialogLifeCycleEvent["didDisappearId"] = didDisappearId;
    }
    auto onWillDisappear = paramObject->GetProperty("onWillDisappear");
    if (!onWillDisappear->IsUndefined() && onWillDisappear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillDisappear));
        auto willDisappearId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                                      node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CalendarDialog.onWillDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        dialogLifeCycleEvent["willDisappearId"] = willDisappearId;
    }
}

std::map<std::string, NG::DialogCancelEvent> JSCalendarPickerDialog::LifeCycleDialogEvent(const JSCallbackInfo& info)
{
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    if (!info[0]->IsObject()) {
        return dialogLifeCycleEvent;
    }
    AppearDialogEvent(info, dialogLifeCycleEvent);
    DisappearDialogEvent(info, dialogLifeCycleEvent);
    return dialogLifeCycleEvent;
}

PickerDate JSCalendarPickerDialog::ParseDate(const JSRef<JSVal>& dateVal, bool useCurrentDate)
{
    auto pickerDate = useCurrentDate ? PickerDate::Current() : PickerDate();
    if (!dateVal->IsObject()) {
        return pickerDate;
    }
    auto dateObj = JSRef<JSObject>::Cast(dateVal);

    auto yearFuncJsVal = dateObj->GetProperty("getFullYear");
    auto monthFuncJsVal = dateObj->GetProperty("getMonth");
    auto dateFuncJsVal = dateObj->GetProperty("getDate");
    if (!(yearFuncJsVal->IsFunction() && monthFuncJsVal->IsFunction() && dateFuncJsVal->IsFunction())) {
        return pickerDate;
    }
    auto yearFunc = JSRef<JSFunc>::Cast(yearFuncJsVal);
    auto monthFunc = JSRef<JSFunc>::Cast(monthFuncJsVal);
    auto dateFunc = JSRef<JSFunc>::Cast(dateFuncJsVal);
    JSRef<JSVal> year = yearFunc->Call(dateObj);
    JSRef<JSVal> month = monthFunc->Call(dateObj);
    JSRef<JSVal> date = dateFunc->Call(dateObj);

    if (year->IsNumber() && month->IsNumber() && date->IsNumber()) {
        pickerDate.SetYear(year->ToNumber<int32_t>());
        pickerDate.SetMonth(month->ToNumber<int32_t>() + 1); // 0-11 means 1 to 12 months
        pickerDate.SetDay(date->ToNumber<int32_t>());
    }
    return pickerDate;
}

void JSCalendarPickerDialog::ParseDisabledDateRange(
    const JSRef<JSVal>& disabledDateRangeVal, NG::CalendarSettingData& settingData)
{
    if (disabledDateRangeVal->IsUndefined() || disabledDateRangeVal->IsNull() || !disabledDateRangeVal->IsArray()) {
        return;
    }

    JSRef<JSArray> array = JSRef<JSArray>::Cast(disabledDateRangeVal);
    for (size_t i = 0; i < array->Length(); i++) {
        JSRef<JSVal> dateRangeValue = array->GetValueAt(i);
        auto dateRangeObj = JSRef<JSObject>::Cast(dateRangeValue);
        auto startValue = dateRangeObj->GetProperty("start");
        auto endValue = dateRangeObj->GetProperty("end");
        if (startValue->IsObject() && endValue->IsObject()) {
            auto startDate = ParseDate(startValue);
            auto endDate = ParseDate(endValue);
            if (startDate.GetYear() == 0 || endDate.GetYear() == 0 || endDate < startDate)
                continue;
            std::pair<PickerDate, PickerDate> pickerDateRange;
            pickerDateRange.first = startDate;
            pickerDateRange.second = endDate;
            settingData.disabledDateRange.emplace_back(pickerDateRange);
        }
    }
}

void JSCalendarPickerDialog::CalendarPickerDialogShow(const JSRef<JSObject>& paramObj,
    const std::map<std::string, NG::DialogEvent>& dialogEvent,
    const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent,
    const std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent,
    const std::vector<ButtonInfo>& buttonInfos)
{
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto executor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(executor);

    auto theme = GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    auto calendarTheme = pipelineContext->GetTheme<CalendarTheme>();
    NG::CalendarSettingData settingData;
    auto markToday = paramObj->GetProperty("markToday");
    bool isMarkToday = false;
    if (markToday->IsBoolean()) {
        isMarkToday = markToday->ToBoolean();
    }
    settingData.markToday = isMarkToday;
    auto disabledDateRange = paramObj->GetProperty("disabledDateRange");
    ParseDisabledDateRange(disabledDateRange, settingData);
    PickerDate::SortAndMergeDisabledDateRange(settingData.disabledDateRange);
    auto selectedDate = paramObj->GetProperty("selected");
    auto parseSelectedDate = ParseDate(selectedDate, true);

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        auto startDate = paramObj->GetProperty("start");
        auto endDate = paramObj->GetProperty("end");
        auto parseStartDate = ParseDate(startDate);
        auto parseEndDate = ParseDate(endDate);
        if (parseEndDate.GetYear() > 0 && parseStartDate.ToDays() > parseEndDate.ToDays()) {
            parseStartDate = PickerDate();
            parseEndDate = PickerDate();
        }
        settingData.startDate = parseStartDate;
        settingData.endDate = parseEndDate;
        parseSelectedDate = PickerDate::AdjustDateToRange(parseSelectedDate, parseStartDate, parseEndDate);
    }

    if (parseSelectedDate.GetYear() != 0) {
        settingData.selectedDate = parseSelectedDate;
    }

    CalcDimension radius;
    if (ParseJsDimensionVpNG(paramObj->GetProperty("hintRadius"), radius)) {
        settingData.dayRadius = radius;
    }

    DialogProperties properties;
    properties.alignment = theme->GetAlignment();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        properties.alignment = DialogAlignment::CENTER;
    }

    auto backgroundColorValue = paramObj->GetProperty("backgroundColor");
    Color backgroundColor;
    if (JSViewAbstract::ParseJsColor(backgroundColorValue, backgroundColor)) {
        properties.backgroundColor = backgroundColor;
    }

    auto backgroundBlurStyle = paramObj->GetProperty("backgroundBlurStyle");
    if (backgroundBlurStyle->IsNumber()) {
        auto blurStyle = backgroundBlurStyle->ToNumber<int32_t>();
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            properties.backgroundBlurStyle = blurStyle;
        }
    }

    auto shadowValue = paramObj->GetProperty("shadow");
    Shadow shadow;
    if ((shadowValue->IsObject() || shadowValue->IsNumber()) && JSViewAbstract::ParseShadowProps(shadowValue, shadow)) {
        properties.shadow = shadow;
    }

    properties.customStyle = false;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
        NG::BorderRadiusProperty dialogRadius;
        dialogRadius.SetRadius(calendarTheme->GetDialogBorderRadius());
        properties.borderRadius = dialogRadius;
    }
    JSViewAbstract::SetDialogHoverModeProperties(paramObj, properties);

    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowCalendarDialog(
                properties, settingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos);
        },
        TaskExecutor::TaskType::UI, "ArkUIDialogShowCalendarPicker",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}
} // namespace OHOS::Ace::Framework
