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

#include "frameworks/core/components_ng/pattern/date_picker/bridge/arkts_native_datepickerdialog_bridge.h"

#include "ark_native_engine.h"
#include "jsnapi_expo.h"
#include "native_engine.h"
#include "ui/base/ace_type.h"
#include "ui/base/utils/utils.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/common/properties/text_enums.h"
#include "core/components_ng/pattern/date_picker/picker_model.h"
#include "core/components_ng/pattern/time_picker/timepicker_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
namespace {
const DimensionOffset DATEPICKER_OFFSET_DEFAULT_TOP = DimensionOffset(0.0_vp, 40.0_vp);
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const std::vector<HoverModeAreaType> HOVER_MODE_AREA_TYPE = { HoverModeAreaType::TOP_SCREEN,
    HoverModeAreaType::BOTTOM_SCREEN };
const std::vector<DistortionMode> DIALOG_DISTORTION_MODE = { DistortionMode::DISTORTION_AUTO,
    DistortionMode::DISTORTION_ENABLED, DistortionMode::DISTORTION_DISABLED };
const std::vector<EdgeLightMode> DIALOG_EDGELIGHT_MODE = { EdgeLightMode::EDGELIGHT_AUTO,
    EdgeLightMode::EDGELIGHT_ENABLED, EdgeLightMode::EDGELIGHT_DISABLED };
const char TIMEPICKER_OPTIONS_HOUR[] = "hour";
const char TIMEPICKER_OPTIONS_MINUTE[] = "minute";
const std::string TIMEPICKER_OPTIONS_NUMERIC_VAL = "numeric";
const std::string TIMEPICKER_OPTIONS_TWO_DIGIT_VAL = "2-digit";

PickerDate ParseDate(const EcmaVM* vm, const Local<JSValueRef>& dateVal)
{
    auto pickerDate = PickerDate();
    if (!dateVal->IsObject(vm)) {
        return pickerDate;
    }
    panda::TryCatch trycatch(vm);
    auto dateObj = dateVal->ToObject(vm);
    auto yearFuncJsVal = dateObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "getFullYear"));
    auto monthFuncJsVal = dateObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "getMonth"));
    auto dateFuncJsVal = dateObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "getDate"));
    if (!(yearFuncJsVal->IsFunction(vm) && monthFuncJsVal->IsFunction(vm) && dateFuncJsVal->IsFunction(vm))) {
        return pickerDate;
    }
    panda::Local<panda::FunctionRef> yearFunc = yearFuncJsVal->ToObject(vm);
    panda::Local<panda::FunctionRef> monthFunc = monthFuncJsVal->ToObject(vm);
    panda::Local<panda::FunctionRef> dateFunc = dateFuncJsVal->ToObject(vm);
    Local<JSValueRef> year = yearFunc->Call(vm, dateObj, nullptr, 0);
    ArkTSUtils::HandleCallbackJobs(vm, trycatch, year);
    Local<JSValueRef> month = monthFunc->Call(vm, dateObj, nullptr, 0);
    ArkTSUtils::HandleCallbackJobs(vm, trycatch, month);
    Local<JSValueRef> date = dateFunc->Call(vm, dateObj, nullptr, 0);
    ArkTSUtils::HandleCallbackJobs(vm, trycatch, date);

    if (year->IsNumber() && month->IsNumber() && date->IsNumber()) {
        pickerDate.SetYear(year->ToNumber(vm)->Value());
        pickerDate.SetMonth(month->ToNumber(vm)->Value() + 1); // 0-11 means 1 to 12 months
        pickerDate.SetDay(date->ToNumber(vm)->Value());
    }
    return pickerDate;
}

PickerTime ParseTime(const EcmaVM* vm, const Local<JSValueRef>& timeVal)
{
    PickerTime pickerTime;
    if (!timeVal->IsObject(vm)) {
        return pickerTime;
    }
    panda::TryCatch trycatch(vm);
    auto timeObj = timeVal->ToObject(vm);
    auto hourFuncJsVal = timeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "getHours"));
    auto minuteFuncJsVal = timeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "getMinutes"));
    auto secondFuncJsVal = timeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "getSeconds"));
    if (!(hourFuncJsVal->IsFunction(vm) && minuteFuncJsVal->IsFunction(vm) && secondFuncJsVal->IsFunction(vm))) {
        return pickerTime;
    }

    Local<panda::FunctionRef> hourFunc = hourFuncJsVal->ToObject(vm);
    Local<panda::FunctionRef> minuteFunc = minuteFuncJsVal->ToObject(vm);
    Local<panda::FunctionRef> secondFunc = secondFuncJsVal->ToObject(vm);
    auto hour = hourFunc->Call(vm, timeObj, nullptr, 0);
    ArkTSUtils::HandleCallbackJobs(vm, trycatch, hour);
    auto minute = minuteFunc->Call(vm, timeObj, nullptr, 0);
    ArkTSUtils::HandleCallbackJobs(vm, trycatch, minute);
    auto second = secondFunc->Call(vm, timeObj, nullptr, 0);
    ArkTSUtils::HandleCallbackJobs(vm, trycatch, second);

    if (hour->IsNumber() && minute->IsNumber() && second->IsNumber()) {
        pickerTime.SetHour(hour->ToNumber(vm)->Int32Value(vm));
        pickerTime.SetMinute(minute->ToNumber(vm)->Int32Value(vm));
        pickerTime.SetSecond(second->ToNumber(vm)->Int32Value(vm));
    }
    return pickerTime;
}

void ExecuteInternal(const EcmaVM* vm, const std::unique_ptr<JsonValue>& value, const std::string& key,
    const Local<panda::ObjectRef>& eventInfo)
{
    auto pandaKey = panda::StringRef::NewFromUtf8(vm, key.c_str());
    if (value->IsString()) {
        eventInfo->Set(vm, pandaKey, ArkTSUtils::ToJSValueWithVM(vm, value->GetString()));
    } else if (value->IsNumber()) {
        eventInfo->Set(vm, pandaKey, ArkTSUtils::ToJSValueWithVM(vm, value->GetDouble()));
    } else if (value->IsBool()) {
        eventInfo->Set(vm, pandaKey, ArkTSUtils::ToJSValueWithVM(vm, value->GetBool()));
    } else if (value->IsObject()) {
        auto valueRef = ArkTSUtils::ToJSValueWithVM<std::string>(vm, value->ToString().c_str());
        if (valueRef->IsString(vm)) {
            eventInfo->Set(vm, pandaKey, panda::JSON::Parse(vm, valueRef));
        }
    } else if (value->IsArray()) {
        auto valueArray = panda::ArrayRef::New(vm);
        for (auto index = 0; index < value->GetArraySize(); index++) {
            auto item = value->GetArrayItem(index);
            if (item && item->IsString()) {
                panda::ArrayRef::SetValueAt(vm, valueArray, index, ArkTSUtils::ToJSValueWithVM(vm, item->GetString()));
            }
            if (item && item->IsNumber()) {
                panda::ArrayRef::SetValueAt(vm, valueArray, index, ArkTSUtils::ToJSValueWithVM(vm, item->GetInt()));
            }
        }
        eventInfo->Set(vm, pandaKey, valueArray);
    }
}

panda::Local<panda::DateRef> GetDateObj(
    EcmaVM* vm, const std::unique_ptr<JsonValue>& selectedJson, bool isDatePicker)
{
    std::tm dateTime {};
    auto year = selectedJson->GetValue("year");
    if (year && year->IsNumber()) {
        dateTime.tm_year = year->GetInt() - 1900; // local date start from 1900
    }
    auto month = selectedJson->GetValue("month");
    if (month && month->IsNumber()) {
        dateTime.tm_mon = month->GetInt();
    }
    auto day = selectedJson->GetValue("day");
    if (day && day->IsNumber()) {
        dateTime.tm_mday = day->GetInt();
    }
    auto hour = selectedJson->GetValue("hour");
    if (hour && hour->IsNumber()) {
        dateTime.tm_hour = hour->GetInt();
    }
    auto minute = selectedJson->GetValue("minute");
    if (minute && minute->IsNumber()) {
        dateTime.tm_min = minute->GetInt();
    }
    auto second = selectedJson->GetValue("second");
    if (second && second->IsNumber()) {
        dateTime.tm_sec = second->GetInt();
    }

    dateTime.tm_isdst = -1; // Auto considering daylight saving time
    if (!isDatePicker) {
        auto milliseconds = Date::GetMilliSecondsByDateTime(dateTime);
        return panda::DateRef::New(vm, milliseconds);
    }

    auto timestamp = std::chrono::system_clock::from_time_t(std::mktime(&dateTime));
    auto duration = timestamp.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return panda::DateRef::New(vm, milliseconds);
}

class JsDatePickerDialogVoidCallback {
public:
    JsDatePickerDialogVoidCallback(EcmaVM* vm, const panda::Local<panda::FunctionRef>& func,
        WeakPtr<NG::FrameNode> node, const char* scoringEvent)
        : vm_(vm), func_(vm, func), node_(std::move(node)), scoringEvent_(scoringEvent)
    {}

    void operator()() const
    {
        CHECK_NULL_VOID(vm_);
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm_), false);
        panda::LocalScope pandaScope(vm_);
        panda::TryCatch trycatch(vm_);
        ACE_SCORING_EVENT(scoringEvent_);
        PipelineContext::SetCallBackNode(node_);
        auto result = func_->Call(vm_, func_.ToLocal(), nullptr, 0);
        ArkTSUtils::HandleCallbackJobs(vm_, trycatch, result);
    }

private:
    EcmaVM* vm_ = nullptr;
    panda::CopyableGlobal<panda::FunctionRef> func_;
    WeakPtr<NG::FrameNode> node_;
    const char* scoringEvent_ = nullptr;
};

class JsDatePickerDialogStringCallback {
public:
    JsDatePickerDialogStringCallback(EcmaVM* vm, const panda::Local<panda::FunctionRef>& func,
        WeakPtr<NG::FrameNode> node, const char* scoringEvent)
        : vm_(vm), func_(vm, func), node_(std::move(node)), scoringEvent_(scoringEvent)
    {}

    void operator()(const std::string& info) const
    {
        CHECK_NULL_VOID(vm_);
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm_), false);
            panda::LocalScope pandaScope(vm_);
            panda::TryCatch trycatch(vm_);
            ACE_SCORING_EVENT(scoringEvent_);
            PipelineContext::SetCallBackNode(node_);
            std::vector<std::string> keys;
            keys = { "year", "month", "day" };
            auto argsPtr = JsonUtil::ParseJsonString(info);
            if (!argsPtr) {
                return;
            }
            Local<panda::ObjectRef> eventInfo = panda::ObjectRef::New(vm_);
            for (auto key : keys) {
                const auto value = argsPtr->GetValue(key);
                if (!value) {
                    LOGD("key[%{public}s] not exist.", key.c_str());
                    continue;
                }
                ExecuteInternal(vm_, value, key, eventInfo);
            }
            panda::Local<panda::JSValueRef> params[] = { eventInfo };
            auto result = func_->Call(vm_, func_.ToLocal(), params, 1);
            ArkTSUtils::HandleCallbackJobs(vm_, trycatch, result);
    }

private:
    EcmaVM* vm_ = nullptr;
    panda::CopyableGlobal<panda::FunctionRef> func_;
    WeakPtr<NG::FrameNode> node_;
    const char* scoringEvent_ = nullptr;
};

class JsDatePickerDialogJsonCallback {
public:
    JsDatePickerDialogJsonCallback(EcmaVM* vm, const panda::Local<panda::FunctionRef>& func,
        WeakPtr<NG::FrameNode> node, const char* scoringEvent, DatePickerType pickerType)
        : vm_(vm), func_(vm, func), node_(std::move(node)), scoringEvent_(scoringEvent), pickerType_(pickerType)
    {}

    void operator()(const std::string& info) const
    {
        CHECK_NULL_VOID(vm_);
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm_), false);
        panda::LocalScope pandaScope(vm_);
        panda::TryCatch trycatch(vm_);
        ACE_SCORING_EVENT(scoringEvent_);
        auto selectedJson = JsonUtil::ParseJsonString(info);
        if (!selectedJson || selectedJson->IsNull()) {
            return;
        }
        auto dateObj = GetDateObj(vm_, selectedJson, pickerType_ == DatePickerType::DATE);
        PipelineContext::SetCallBackNode(node_);
        panda::Local<panda::JSValueRef> params[] = { dateObj };
        auto result = func_->Call(vm_, func_.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm_, trycatch, result);
    }

private:
    EcmaVM* vm_ = nullptr;
    panda::CopyableGlobal<panda::FunctionRef> func_;
    WeakPtr<NG::FrameNode> node_;
    const char* scoringEvent_ = nullptr;
    DatePickerType pickerType_ = DatePickerType::DATE;
};

class JsDatePickerDialogAcceptCallback {
public:
    JsDatePickerDialogAcceptCallback(EcmaVM* vm, const panda::Local<panda::FunctionRef>& func,
        WeakPtr<NG::FrameNode> node, const char* scoringEvent)
        : vm_(vm), func_(vm, func), node_(std::move(node)), scoringEvent_(scoringEvent)
    {}

    void operator()(const std::string& info) const
    {
        CHECK_NULL_VOID(vm_);
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm_), false);
        panda::LocalScope pandaScope(vm_);
        panda::TryCatch trycatch(vm_);
        ACE_SCORING_EVENT(scoringEvent_);
        PipelineContext::SetCallBackNode(node_);
        std::vector<std::string> keys = { "year", "month", "day", "hour", "minute", "second" };
        auto argsPtr = JsonUtil::ParseJsonString(info);
        if (!argsPtr) {
            return;
        }
        Local<panda::ObjectRef> eventInfo = panda::ObjectRef::New(vm_);
        for (auto key : keys) {
            const auto value = argsPtr->GetValue(key);
            if (!value) {
                LOGD("key[%{public}s] not exist.", key.c_str());
                continue;
            }
            ExecuteInternal(vm_, value, key, eventInfo);
        }
        panda::Local<panda::JSValueRef> params[] = { eventInfo };
        auto result = func_->Call(vm_, func_.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm_, trycatch, result);
    }

private:
    EcmaVM* vm_ = nullptr;
    panda::CopyableGlobal<panda::FunctionRef> func_;
    WeakPtr<NG::FrameNode> node_;
    const char* scoringEvent_ = nullptr;
};

std::function<void(const std::string&)> GetChangeEvent(
    const Local<panda::ObjectRef>& paramObject, ArkUIRuntimeCallInfo* runtimeCallInfo, const DatePickerType& pickerType,
    const WeakPtr<NG::FrameNode>& frameNode)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    std::function<void(const std::string&)> changeEvent;
    auto onChange = ArkTSUtils::GetProperty(vm, paramObject, "onChange");
    if (!onChange->IsUndefined() && onChange->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onChange->ToObject(vm);
        changeEvent = JsDatePickerDialogStringCallback(vm, jsFunc, frameNode, "DatePickerDialog.onChange");
    }
    return changeEvent;
}

std::function<void(const std::string&)> GetAcceptEvent(
    const Local<panda::ObjectRef>& paramObject, ArkUIRuntimeCallInfo* runtimeCallInfo,
    const WeakPtr<NG::FrameNode>& frameNode)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    std::function<void(const std::string&)> acceptEvent;
    auto onAccept = ArkTSUtils::GetProperty(vm, paramObject, "onAccept");
    if (!onAccept->IsUndefined() && onAccept->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onAccept->ToObject(vm);
        acceptEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), node = frameNode](const std::string& info) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("DatePickerDialog.onAccept");
            PipelineContext::SetCallBackNode(node);
            std::vector<std::string> keys = { "year", "month", "day", "hour", "minute", "second" };
            auto argsPtr = JsonUtil::ParseJsonString(info);
            if (!argsPtr) {
                return;
            }
            Local<panda::ObjectRef> eventInfo = panda::ObjectRef::New(vm);
            for (auto key : keys) {
                const auto value = argsPtr->GetValue(key);
                if (!value) {
                    LOGD("key[%{public}s] not exist.", key.c_str());
                    continue;
                }
                ExecuteInternal(vm, value, key, eventInfo);
            }
            panda::Local<panda::JSValueRef> params[] = { eventInfo };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        acceptEvent = JsDatePickerDialogAcceptCallback(vm, jsFunc, frameNode, "DatePickerDialog.onAccept");
    }
    return acceptEvent;
}

std::function<void()> GetCancelEvent(const Local<panda::ObjectRef>& paramObject,
    ArkUIRuntimeCallInfo* runtimeCallInfo, const WeakPtr<NG::FrameNode>& frameNode)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    std::function<void()> cancelEvent;
    auto onCancel = ArkTSUtils::GetProperty(vm, paramObject, "onCancel");
    if (!onCancel->IsUndefined() && onCancel->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onCancel->ToObject(vm);
        cancelEvent = JsDatePickerDialogVoidCallback(vm, jsFunc, frameNode, "DatePickerDialog.onCancel");
    }
    return cancelEvent;
}

std::function<void(const std::string&)> GetDateChangeEvent(
    const Local<panda::ObjectRef>& paramObject, ArkUIRuntimeCallInfo* runtimeCallInfo, const DatePickerType& pickerType,
    const WeakPtr<NG::FrameNode>& frameNode)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    std::function<void(const std::string&)> dateChangeEvent;
    auto onDateChange = ArkTSUtils::GetProperty(vm, paramObject, "onDateChange");
    if (!onDateChange->IsUndefined() && onDateChange->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onDateChange->ToObject(vm);
        dateChangeEvent =
            JsDatePickerDialogJsonCallback(vm, jsFunc, frameNode, "DatePickerDialog.onDateChange", pickerType);
    }
    return dateChangeEvent;
}

std::function<void(const std::string&)> GetDateAcceptEvent(
    const Local<panda::ObjectRef>& paramObject, ArkUIRuntimeCallInfo* runtimeCallInfo, const DatePickerType& pickerType,
    const WeakPtr<NG::FrameNode>& frameNode)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    std::function<void(const std::string&)> dateAcceptEvent;
    auto onDateAccept = ArkTSUtils::GetProperty(vm, paramObject, "onDateAccept");
    if (!onDateAccept->IsUndefined() && onDateAccept->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onDateAccept->ToObject(vm);
        dateAcceptEvent =
            JsDatePickerDialogJsonCallback(vm, jsFunc, frameNode, "DatePickerDialog.onDateAccept", pickerType);
    }
    return dateAcceptEvent;
}

void ParseTextStyleFontSize(const EcmaVM* vm, const Local<JSValueRef>& fontSize, NG::PickerTextStyle& textStyle)
{
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        textStyle.fontSize = Dimension(-1);
    } else {
        CalcDimension size;
        if (!ArkTSUtils::ParseJsDimensionNG(vm, fontSize, size, DimensionUnit::FP, textStyle.fontSizeResObj, false)) {
            textStyle.fontSize = Dimension(-1);
        } else {
            textStyle.fontSize = size;
        }
    }
}

void IsUserDefinedFontFamily(const std::string& pos)
{
    if (pos == "disappearTextStyle") {
        GetArkUINodeModifiers()->getDatePickerModifier()->hasUserDefinedDisappearFontFamily(true);
    } else if (pos == "textStyle") {
        GetArkUINodeModifiers()->getDatePickerModifier()->hasUserDefinedNormalFontFamily(true);
    } else if (pos == "selectedTextStyle") {
        GetArkUINodeModifiers()->getDatePickerModifier()->hasUserDefinedSelectedFontFamily(true);
    }
}

void ParseTextStyle(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, NG::PickerTextStyle& textStyle, const std::string& pos)
{
    auto fontColor = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
    auto fontOptions = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "font"));

    Color textColor;
    if (ArkTSUtils::ParseJsColor(vm, fontColor, textColor, textStyle.textColorResObj)) {
        textStyle.textColor = textColor;
        textStyle.textColorSetByUser = true;
    }

    if (!fontOptions->IsObject(vm)) {
        return;
    }
    auto fontObj = fontOptions->ToObject(vm);
    auto fontSize = fontObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
    auto fontWeight = fontObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "weight"));
    auto fontFamily = fontObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "family"));
    auto fontStyle = fontObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "style"));

    ParseTextStyleFontSize(vm, fontSize, textStyle);

    if (!fontWeight->IsNull() && !fontWeight->IsUndefined()) {
        std::string weight;
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->Int32Value(vm));
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
        auto style = fontStyle->Int32Value(vm);
        if (style < 0 || style > 1) {
            return;
        }
        textStyle.fontStyle = static_cast<Ace::FontStyle>(style);
    }
}

void ParseDateTimeOptions(const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, DateTimeType& dateTimeOptions)
{
    dateTimeOptions.hourType = ZeroPrefixType::AUTO;
    dateTimeOptions.minuteType = ZeroPrefixType::AUTO;
    dateTimeOptions.secondType = ZeroPrefixType::AUTO;

    auto hourValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, TIMEPICKER_OPTIONS_HOUR));
    if (hourValue->IsString(vm)) {
        std::string hour = hourValue->ToString(vm)->ToString(vm);
        if (hour == TIMEPICKER_OPTIONS_TWO_DIGIT_VAL) {
            dateTimeOptions.hourType = ZeroPrefixType::SHOW;
        } else if (hour == TIMEPICKER_OPTIONS_NUMERIC_VAL) {
            dateTimeOptions.hourType = ZeroPrefixType::HIDE;
        }
    }
    auto minuteValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, TIMEPICKER_OPTIONS_MINUTE));
    if (minuteValue->IsString(vm)) {
        dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
        std::string minute = minuteValue->ToString(vm)->ToString(vm);
        if (minute == TIMEPICKER_OPTIONS_NUMERIC_VAL) {
            dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
        }
    }
}

void ParseTextProperties(const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, NG::PickerTextProperties& result)
{
    auto disappearProperty = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "disappearTextStyle"));
    auto normalProperty = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "textStyle"));
    auto selectedProperty = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "selectedTextStyle"));

    if (!disappearProperty->IsNull() && disappearProperty->IsObject(vm)) {
        auto disappearObj = disappearProperty->ToObject(vm);
        ParseTextStyle(vm, disappearObj, result.disappearTextStyle_, "disappearTextStyle");
    }

    if (!normalProperty->IsNull() && normalProperty->IsObject(vm)) {
        auto noramlObj = normalProperty->ToObject(vm);
        ParseTextStyle(vm, noramlObj, result.normalTextStyle_, "textStyle");
    }

    if (!selectedProperty->IsNull() && selectedProperty->IsObject(vm)) {
        auto selectedObj = selectedProperty->ToObject(vm);
        ParseTextStyle(vm, selectedObj, result.selectedTextStyle_, "selectedTextStyle");
    }
}

void ParseFontOfButtonStyle(const EcmaVM* vm, const Local<JSValueRef>& pickerButtonParamObject, ButtonInfo& buttonInfo)
{
    CalcDimension fontSize;
    auto sizeProperty = ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "fontSize");
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, sizeProperty, fontSize) && fontSize.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(fontSize.Value(), 0.0)) {
        if (ArkTSUtils::ParseJsDimensionFp(vm, sizeProperty, fontSize)) {
            buttonInfo.fontSize = fontSize;
        }
    }
    Color fontColor;
    RefPtr<ResourceObject> fontColorObject;
    if (ArkTSUtils::ParseJsColor(
        vm, ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "fontColor"), fontColor, fontColorObject)) {
        buttonInfo.fontColor = fontColor;
    }
    auto fontWeight = ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "fontWeight");
    if (fontWeight->IsString(vm) || fontWeight->IsNumber()) {
        buttonInfo.fontWeight =
            Framework::ConvertStrToFontWeight(fontWeight->ToString(vm)->ToString(vm), FontWeight::MEDIUM);
    }
    auto style = ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "fontStyle");
    if (style->IsNumber()) {
        auto value = style->ToNumber(vm)->Int32Value(vm);
        if (value >= 0 && value < static_cast<int32_t>(OHOS::Ace::FontStyle::NONE)) {
            buttonInfo.fontStyle = static_cast<OHOS::Ace::FontStyle>(value);
        }
    }
    auto family = ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "fontFamily");
    std::vector<std::string> fontFamilies;
    if (ArkTSUtils::ParseJsFontFamilies(vm, family, fontFamilies)) {
        buttonInfo.fontFamily = fontFamilies;
    }
}

std::optional<NG::BorderRadiusProperty> HandleDifferentRadius(const EcmaVM* vm, const Local<JSValueRef>& args)
{
    std::optional<NG::BorderRadiusProperty> prop = std::nullopt;
    if (!args->IsObject(vm)) {
        return prop;
    }

    std::optional<CalcDimension> radiusTopLeft;
    std::optional<CalcDimension> radiusTopRight;
    std::optional<CalcDimension> radiusBottomLeft;
    std::optional<CalcDimension> radiusBottomRight;
    auto object = args->ToObject(vm);
    CalcDimension topLeft;
    if (ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "topLeft"), topLeft)) {
        radiusTopLeft = topLeft;
    }
    CalcDimension topRight;
    if (ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "topRight"), topRight)) {
        radiusTopRight = topRight;
    }
    CalcDimension bottomLeft;
    if (ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "bottomLeft"), bottomLeft)) {
        radiusBottomLeft = bottomLeft;
    }
    CalcDimension bottomRight;
    if (ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "bottomRight"), bottomRight)) {
        radiusBottomRight = bottomRight;
    }
    if (!radiusTopLeft.has_value() && !radiusTopRight.has_value() && !radiusBottomLeft.has_value() &&
        !radiusBottomRight.has_value()) {
        return prop;
    }
    NG::BorderRadiusProperty borderRadius;
    if (radiusTopLeft.has_value()) {
        borderRadius.radiusTopLeft = radiusTopLeft;
    }
    if (radiusTopRight.has_value()) {
        borderRadius.radiusTopRight = radiusTopRight;
    }
    if (radiusBottomLeft.has_value()) {
        borderRadius.radiusBottomLeft = radiusBottomLeft;
    }
    if (radiusBottomRight.has_value()) {
        borderRadius.radiusBottomRight = radiusBottomRight;
    }
    borderRadius.multiValued = true;
    prop = borderRadius;

    return prop;
}

std::optional<NG::BorderRadiusProperty> ParseBorderRadiusAttr(const EcmaVM* vm, const Local<JSValueRef>& args)
{
    std::optional<NG::BorderRadiusProperty> prop = std::nullopt;
    CalcDimension radiusDim;
    if (!args->IsObject(vm) && !args->IsNumber() && !args->IsString(vm)) {
        return prop;
    }
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, args, radiusDim)) {
        NG::BorderRadiusProperty borderRadius;
        borderRadius.SetRadius(radiusDim);
        borderRadius.multiValued = false;
        prop = borderRadius;
    } else if (args->IsObject(vm)) {
        prop = HandleDifferentRadius(vm, args);
    }
    return prop;
}

ButtonInfo ParseButtonStyle(const EcmaVM* vm, const Local<JSValueRef>& pickerButtonParamObject)
{
    ButtonInfo buttonInfo;
    if (ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "type")->IsNumber()) {
        auto buttonTypeIntValue =
            ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "type")->ToNumber(vm)->Int32Value(vm);
        if (buttonTypeIntValue == static_cast<int32_t>(ButtonType::CAPSULE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::CIRCLE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ARC) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::NORMAL) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ROUNDED_RECTANGLE)) {
            buttonInfo.type = static_cast<ButtonType>(buttonTypeIntValue);
        }
    }
    if (ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "style")->IsNumber()) {
        auto styleModeIntValue =
            ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "style")->ToNumber(vm)->Int32Value(vm);
        if (styleModeIntValue >= static_cast<int32_t>(ButtonStyleMode::NORMAL) &&
            styleModeIntValue <= static_cast<int32_t>(ButtonStyleMode::TEXT)) {
            buttonInfo.buttonStyle = static_cast<ButtonStyleMode>(styleModeIntValue);
        }
    }
    if (ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "role")->IsNumber()) {
        auto buttonRoleIntValue =
            ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "role")->ToNumber(vm)->Int32Value(vm);
        if (buttonRoleIntValue >= static_cast<int32_t>(ButtonRole::NORMAL) &&
            buttonRoleIntValue <= static_cast<int32_t>(ButtonRole::ERROR)) {
            buttonInfo.role = static_cast<ButtonRole>(buttonRoleIntValue);
        }
    }
    ParseFontOfButtonStyle(vm, pickerButtonParamObject, buttonInfo);
    Color backgroundColor;
    RefPtr<ResourceObject> backgroundColorObject;
    if (ArkTSUtils::ParseJsColor(vm, ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "backgroundColor"),
            backgroundColor, backgroundColorObject)) {
        buttonInfo.backgroundColor = backgroundColor;
    }
    auto radius = ParseBorderRadiusAttr(vm, ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "borderRadius"));
    if (radius.has_value()) {
        buttonInfo.borderRadius = radius.value();
    }

    auto primaryValue = ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "primary");
    if (primaryValue->IsBoolean()) {
        buttonInfo.isPrimary = primaryValue->ToBoolean(vm)->ToBoolean(vm)->Value();
    }

    return buttonInfo;
}

std::vector<ButtonInfo> ParseButtonStyles(const EcmaVM* vm, const Local<JSValueRef>& paramObject)
{
    std::vector<ButtonInfo> buttonInfos;
    auto acceptButtonStyle = ArkTSUtils::GetProperty(vm, paramObject, "acceptButtonStyle");
    if (acceptButtonStyle->IsObject(vm)) {
        auto acceptButtonStyleParamObject = acceptButtonStyle->ToObject(vm);
        buttonInfos.emplace_back(ParseButtonStyle(vm, acceptButtonStyleParamObject));
        buttonInfos[0].isAcceptButton = true;
    } else {
        ButtonInfo buttonInfo;
        buttonInfos.emplace_back(buttonInfo);
    }
    auto cancelButtonStyle = ArkTSUtils::GetProperty(vm, paramObject, "cancelButtonStyle");
    if (cancelButtonStyle->IsObject(vm)) {
        auto cancelButtonStyleParamObject = cancelButtonStyle->ToObject(vm);
        buttonInfos.emplace_back(ParseButtonStyle(vm, cancelButtonStyleParamObject));
    }

    return buttonInfos;
}

void ParseDatePickerHoverMode(const EcmaVM* vm, PickerDialogInfo& pickerDialog, const Local<JSValueRef>& paramObject)
{
    auto enableHoverModeValue = ArkTSUtils::GetProperty(vm, paramObject, "enableHoverMode");
    if (enableHoverModeValue->IsBoolean()) {
        pickerDialog.enableHoverMode = enableHoverModeValue->ToBoolean(vm)->Value();
    }

    auto hoverModeAreaValue = ArkTSUtils::GetProperty(vm, paramObject, "hoverModeArea");
    pickerDialog.hoverModeArea = HoverModeAreaType::BOTTOM_SCREEN;
    if (hoverModeAreaValue->IsNumber()) {
        auto hoverModeArea = hoverModeAreaValue->ToNumber(vm)->Int32Value(vm);
        if (hoverModeArea >= 0 && hoverModeArea < static_cast<int32_t>(HOVER_MODE_AREA_TYPE.size())) {
            pickerDialog.hoverModeArea = HOVER_MODE_AREA_TYPE[hoverModeArea];
        }
    }
}

void ParseDatePickerBlurStyleOption(
    const EcmaVM* vm, PickerDialogInfo& pickerDialog, const Local<JSValueRef>& paramObject)
{
    auto blurStyleValue = ArkTSUtils::GetProperty(vm, paramObject, "backgroundBlurStyleOptions");
    if (blurStyleValue->IsObject(vm)) {
        if (!pickerDialog.blurStyleOption.has_value()) {
            pickerDialog.blurStyleOption.emplace();
        }
        ArkTSUtils::ParseBlurStyleOption(vm, blurStyleValue, pickerDialog.blurStyleOption.value());
    }
}

void ParseDatePickerEffectOption(
    const EcmaVM* vm, PickerDialogInfo& pickerDialog, const Local<JSValueRef>& paramObject)
{
    auto effectOptionValue = ArkTSUtils::GetProperty(vm, paramObject, "backgroundEffect");
    if (effectOptionValue->IsObject(vm)) {
        if (!pickerDialog.effectOption.has_value()) {
            pickerDialog.effectOption.emplace();
        }
        ArkTSUtils::ParseEffectOption(vm, effectOptionValue, pickerDialog.effectOption.value());
    }
}

void ParsePickerDialogMaterial(const EcmaVM* vm, PickerDialogInfo& pickerDialog, const Local<JSValueRef>& paramObject)
{
    auto systemMaterialValue = ArkTSUtils::GetProperty(vm, paramObject, "systemMaterial");
    if (systemMaterialValue->IsObject(vm)) {
        auto* systemUiMaterial =
            reinterpret_cast<UiMaterial*>(ArkTSUtils::UnwrapNapiValue(vm, systemMaterialValue->ToObject(vm)));
        pickerDialog.systemMaterial = systemUiMaterial ? systemUiMaterial->Copy() : nullptr;
    }
    
    auto distortionModeValue = ArkTSUtils::GetProperty(vm, paramObject, "distortionMode");
    if (distortionModeValue->IsNumber()) {
        auto distortionModeVal = distortionModeValue->ToNumber(vm)->Int32Value(vm);
        if (distortionModeVal >= 0 && distortionModeVal < static_cast<int32_t>(DIALOG_DISTORTION_MODE.size())) {
            pickerDialog.distortionMode = DIALOG_DISTORTION_MODE[distortionModeVal];
        }
    }
    
    auto edgeLightModeValue = ArkTSUtils::GetProperty(vm, paramObject, "edgeLightMode");
    if (edgeLightModeValue->IsNumber()) {
        auto edgeLightModeVal = edgeLightModeValue->ToNumber(vm)->Int32Value(vm);
        if (edgeLightModeVal >= 0 && edgeLightModeVal < static_cast<int32_t>(DIALOG_EDGELIGHT_MODE.size())) {
            pickerDialog.edgeLightMode = DIALOG_EDGELIGHT_MODE[edgeLightModeVal];
        }
    }
}

void UpdateLunarSwitchSettingData(
    const EcmaVM* vm, const Local<JSValueRef>& paramObject, NG::DatePickerSettingData& settingData)
{
    auto selectedColorValue = ArkTSUtils::GetProperty(vm, paramObject, "selectedColor");
    auto unselectedColorValue = ArkTSUtils::GetProperty(vm, paramObject, "unselectedColor");
    auto strokeColorValue = ArkTSUtils::GetProperty(vm, paramObject, "strokeColor");
    Color selectedColor;
    RefPtr<ResourceObject> selectedColorObj;
    if (ArkTSUtils::ParseJsColor(vm, selectedColorValue, selectedColor, selectedColorObj)) {
        settingData.checkboxSettingData.selectedColor = selectedColor;
    }
    Color unselectedColor;
    RefPtr<ResourceObject> unselectedColorObj;
    if (ArkTSUtils::ParseJsColor(vm, unselectedColorValue, unselectedColor, unselectedColorObj)) {
        settingData.checkboxSettingData.unselectedColor = unselectedColor;
    }
    Color strokeColor;
    RefPtr<ResourceObject> strokeColorObj;
    if (ArkTSUtils::ParseJsColor(vm, strokeColorValue, strokeColor, strokeColorObj)) {
        settingData.checkboxSettingData.strokeColor = strokeColor;
    }
}

void UpdateDatePickerSettingData(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObject, NG::DatePickerSettingData& settingData)
{
    auto lunar = ArkTSUtils::GetProperty(vm, paramObject, "lunar");
    auto lunarSwitch = ArkTSUtils::GetProperty(vm, paramObject, "lunarSwitch");
    auto showTime = ArkTSUtils::GetProperty(vm, paramObject, "showTime");
    auto useMilitary = ArkTSUtils::GetProperty(vm, paramObject, "useMilitaryTime");
    settingData.isLunar = lunar->ToBoolean(vm)->Value();
    settingData.lunarswitch = lunarSwitch->ToBoolean(vm)->Value();
    if (settingData.lunarswitch) {
        auto lunarSwitchStyle = ArkTSUtils::GetProperty(vm, paramObject, "lunarSwitchStyle");
        if ((!lunarSwitchStyle->IsUndefined()) && lunarSwitchStyle->IsObject(vm)) {
            UpdateLunarSwitchSettingData(vm, lunarSwitchStyle, settingData);
        }
    }
    auto enableHapticFeedbackValue = ArkTSUtils::GetProperty(vm, paramObject, "enableHapticFeedback");
    if (enableHapticFeedbackValue->IsBoolean()) {
        settingData.isEnableHapticFeedback = enableHapticFeedbackValue->ToBoolean(vm)->Value();
    }
    settingData.showTime = showTime->ToBoolean(vm)->Value();
    settingData.useMilitary = useMilitary->ToBoolean(vm)->Value();

    auto mode = ArkTSUtils::GetProperty(vm, paramObject, "mode");
    auto datePickerMode = DatePickerMode::DATE;
    if (!mode->IsNull() && mode->IsNumber()) {
        auto parseMode = mode->ToNumber(vm)->Int32Value(vm);
        if (parseMode >= static_cast<int32_t>(DatePickerMode::DATE) &&
            parseMode <= static_cast<int32_t>(DatePickerMode::MONTH_AND_DAY)) {
            datePickerMode = static_cast<DatePickerMode>(parseMode);
        }
    }
    settingData.mode = datePickerMode;
    auto isLoop = ArkTSUtils::GetProperty(vm, paramObject, "canLoop");
    if (isLoop->IsBoolean()) {
        settingData.canLoop = isLoop->ToBoolean(vm)->Value();
    } else {
        settingData.canLoop = true;
    }

    auto dateTimeOptionsValue = ArkTSUtils::GetProperty(vm, paramObject, "dateTimeOptions");
    if (dateTimeOptionsValue->IsObject(vm)) {
        auto dateTimeOptionsObj = dateTimeOptionsValue->ToObject(vm);
        ParseDateTimeOptions(vm, dateTimeOptionsObj, settingData.dateTimeOptions);
    }
    ParseTextProperties(vm, paramObject, settingData.properties);
}

void UpdatePickerDialogTimeInfo(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObject, PickerDialogInfo& pickerDialog)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    auto startDate = ArkTSUtils::GetProperty(vm, paramObject, "start");
    if (startDate->IsObject(vm)) {
        pickerDialog.isStartDate = true;
    }
    auto endDate = ArkTSUtils::GetProperty(vm, paramObject, "end");
    if (endDate->IsObject(vm)) {
        pickerDialog.isEndDate = true;
    }
    auto selectedDate = ArkTSUtils::GetProperty(vm, paramObject, "selected");
    if (selectedDate->IsObject(vm)) {
        pickerDialog.isSelectedDate = true;
    }
    auto parseStartDate = ParseDate(vm, startDate);
    auto parseEndDate = ParseDate(vm, endDate);
    if (parseStartDate.GetYear() <= 0) {
        parseStartDate = theme->GetDefaultStartDate();
    }
    if (parseEndDate.GetYear() <= 0) {
        parseEndDate = theme->GetDefaultEndDate();
    }
    auto startDays = parseStartDate.ToDays();
    auto endDays = parseEndDate.ToDays();
    if (startDays > endDays) {
        parseStartDate = theme->GetDefaultStartDate();
        parseEndDate = theme->GetDefaultEndDate();
    }
    pickerDialog.parseStartDate = parseStartDate;
    pickerDialog.parseEndDate = parseEndDate;
    pickerDialog.parseSelectedDate = ParseDate(vm, selectedDate);
    pickerDialog.pickerTime = ParseTime(vm, selectedDate);
}

void UpdatePickerDialogPositionInfo(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObject, PickerDialogInfo& pickerDialog)
{
    // Parse alignment
    auto alignmentValue = ArkTSUtils::GetProperty(vm, paramObject, "alignment");
    if (alignmentValue->IsNumber()) {
        auto alignment = alignmentValue->ToNumber(vm)->Int32Value(vm);
        if (alignment >= 0 && alignment < static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
            pickerDialog.alignment = DIALOG_ALIGNMENT[alignment];
        }
        if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
            if (alignment == static_cast<int32_t>(DialogAlignment::TOP) ||
                alignment == static_cast<int32_t>(DialogAlignment::TOP_START) ||
                alignment == static_cast<int32_t>(DialogAlignment::TOP_END)) {
                pickerDialog.offset = DATEPICKER_OFFSET_DEFAULT_TOP;
            }
        }
    }

    // Parse offset
    auto offsetValue = ArkTSUtils::GetProperty(vm, paramObject, "offset");
    if (offsetValue->IsObject(vm)) {
        auto offsetObj = offsetValue->ToObject(vm);
        CalcDimension dx;
        auto dxValue = ArkTSUtils::GetProperty(vm, offsetObj, "dx");
        ArkTSUtils::ParseJsDimensionVp(vm, dxValue, dx);
        CalcDimension dy;
        auto dyValue = ArkTSUtils::GetProperty(vm, offsetObj, "dy");
        ArkTSUtils::ParseJsDimensionVp(vm, dyValue, dy);
        pickerDialog.offset = DimensionOffset(dx, dy);
    }
}

void UpdatePickerDialogInfo(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObject, PickerDialogInfo& pickerDialog)
{
    UpdatePickerDialogTimeInfo(vm, paramObject, pickerDialog);
    UpdatePickerDialogPositionInfo(vm, paramObject, pickerDialog);
    // Parse maskRect.
    auto maskRectValue = ArkTSUtils::GetProperty(vm, paramObject, "maskRect");
    DimensionRect maskRect;
    if (ArkTSUtils::ParseJsDimensionRect(vm, maskRectValue, maskRect)) {
        pickerDialog.maskRect = maskRect;
    }

    auto backgroundColorValue = ArkTSUtils::GetProperty(vm, paramObject, "backgroundColor");
    Color backgroundColor;
    RefPtr<ResourceObject> backgroundColorObject;
    if (ArkTSUtils::ParseJsColor(vm, backgroundColorValue, backgroundColor, backgroundColorObject)) {
        pickerDialog.backgroundColor = backgroundColor;
    }

    auto backgroundBlurStyle = ArkTSUtils::GetProperty(vm, paramObject, "backgroundBlurStyle");
    if (backgroundBlurStyle->IsNumber()) {
        auto blurStyle = backgroundBlurStyle->ToNumber(vm)->Int32Value(vm);
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            pickerDialog.backgroundBlurStyle = blurStyle;
        }
    }

    auto shadowValue = ArkTSUtils::GetProperty(vm, paramObject, "shadow");
    Shadow shadow;
    if ((shadowValue->IsObject(vm) || shadowValue->IsNumber()) &&
        ArkTSUtils::ParseShadowProps(vm, shadowValue, shadow)) {
        pickerDialog.shadow = shadow;
    }

    ParseDatePickerHoverMode(vm, pickerDialog, paramObject);
    ParseDatePickerBlurStyleOption(vm, pickerDialog, paramObject);
    ParseDatePickerEffectOption(vm, pickerDialog, paramObject);
    ParsePickerDialogMaterial(vm, pickerDialog, paramObject);
}

void DatePickerDialogAppearEvent(ArkUIRuntimeCallInfo* runtimeCallInfo, PickerDialogEvent& pickerDialogEvent)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    std::function<void()> didAppearEvent;
    std::function<void()> willAppearEvent;
    auto firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (runtimeCallInfo->GetArgsNumber() == 0 || !firstArg->IsObject(vm)) {
        return;
    }
    auto paramObject = firstArg->ToObject(vm);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidAppear = ArkTSUtils::GetProperty(vm, paramObject, "onDidAppear");
    if (!onDidAppear->IsUndefined() && onDidAppear->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onDidAppear->ToObject(vm);
        didAppearEvent = JsDatePickerDialogVoidCallback(vm, jsFunc, frameNode, "DatePickerDialog.onDidAppear");
    }
    auto onWillAppear = ArkTSUtils::GetProperty(vm, paramObject, "onWillAppear");
    if (!onWillAppear->IsUndefined() && onWillAppear->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onWillAppear->ToObject(vm);
        willAppearEvent = JsDatePickerDialogVoidCallback(vm, jsFunc, frameNode, "DatePickerDialog.onWillAppear");
    }
    pickerDialogEvent.onDidAppear = std::move(didAppearEvent);
    pickerDialogEvent.onWillAppear = std::move(willAppearEvent);
}

void DatePickerDialogDisappearEvent(ArkUIRuntimeCallInfo* runtimeCallInfo, PickerDialogEvent& pickerDialogEvent)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    std::function<void()> didDisappearEvent;
    std::function<void()> willDisappearEvent;
    auto firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (runtimeCallInfo->GetArgsNumber() == 0 || !firstArg->IsObject(vm)) {
        return;
    }
    auto paramObject = firstArg->ToObject(vm);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidDisappear = ArkTSUtils::GetProperty(vm, paramObject, "onDidDisappear");
    if (!onDidDisappear->IsUndefined() && onDidDisappear->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onDidDisappear->ToObject(vm);
        didDisappearEvent = JsDatePickerDialogVoidCallback(vm, jsFunc, frameNode, "DatePickerDialog.onDidDisappear");
    }
    auto onWillDisappear = ArkTSUtils::GetProperty(vm, paramObject, "onWillDisappear");
    if (!onWillDisappear->IsUndefined() && onWillDisappear->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onWillDisappear->ToObject(vm);
        willDisappearEvent = JsDatePickerDialogVoidCallback(vm, jsFunc, frameNode, "DatePickerDialog.onWillDisappear");
    }
    pickerDialogEvent.onDidDisappear = std::move(didDisappearEvent);
    pickerDialogEvent.onWillDisappear = std::move(willDisappearEvent);
}
} // namespace

void DatePickerDialogBridge::RegisterDatePickerDialogAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "show" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerDialogBridge::JSShow),
    };

    auto datePickerDialog =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "datePickerDialog"), datePickerDialog);
}

ArkUINativeModuleValue DatePickerDialogBridge::JSShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto scopedDelegate = EngineHelper::GetCurrentDelegateSafely();
    CHECK_NULL_RETURN(scopedDelegate, panda::NativePointerRef::New(vm, nullptr));
    auto param = runtimeCallInfo->GetCallArgRef(0);
    if (!param->IsObject(vm)) {
        return panda::NativePointerRef::New(vm, nullptr);
    }

    auto paramObject = panda::ObjectRef::New(vm);
    if (!(param.IsEmpty() || param->IsNull() || param->IsUndefined())) {
        paramObject = param->ToObject(vm);
    }
    DatePickerType pickerType = DatePickerType::DATE;
    auto type = ArkTSUtils::GetProperty(vm, paramObject, "type");
    if (type->IsNumber()) {
        pickerType = static_cast<DatePickerType>(type->ToNumber(vm)->Int32Value(vm));
    }
    std::function<void()> cancelEvent;
    std::function<void(const std::string&)> acceptEvent;
    std::function<void(const std::string&)> changeEvent;
    std::function<void(const std::string&)> dateChangeEvent;
    std::function<void(const std::string&)> dateAcceptEvent;
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    changeEvent = GetChangeEvent(paramObject, runtimeCallInfo, pickerType, frameNode);
    acceptEvent = GetAcceptEvent(paramObject, runtimeCallInfo, frameNode);
    cancelEvent = GetCancelEvent(paramObject, runtimeCallInfo, frameNode);
    dateChangeEvent = GetDateChangeEvent(paramObject, runtimeCallInfo, pickerType, frameNode);
    dateAcceptEvent = GetDateAcceptEvent(paramObject, runtimeCallInfo, pickerType, frameNode);
    NG::DatePickerSettingData settingData;
    UpdateDatePickerSettingData(vm, paramObject, settingData);
    PickerDialogInfo pickerDialog;
    UpdatePickerDialogInfo(vm, paramObject, pickerDialog);

    auto buttonInfos = ParseButtonStyles(vm, paramObject);
    PickerDialogEvent pickerDialogEvent { nullptr, nullptr, nullptr, nullptr };
    DatePickerDialogAppearEvent(runtimeCallInfo, pickerDialogEvent);
    DatePickerDialogDisappearEvent(runtimeCallInfo, pickerDialogEvent);
    GetArkUINodeModifiers()->getDatePickerModifier()->show(reinterpret_cast<void*>(&pickerDialog),
        reinterpret_cast<void*>(&settingData), reinterpret_cast<void*>(&cancelEvent),
        reinterpret_cast<void*>(&acceptEvent), reinterpret_cast<void*>(&changeEvent),
        reinterpret_cast<void*>(&dateAcceptEvent), reinterpret_cast<void*>(&dateChangeEvent), pickerType,
        reinterpret_cast<void*>(&pickerDialogEvent), reinterpret_cast<void*>(&buttonInfos));
    return panda::NativePointerRef::New(vm, nullptr);
}
} // namespace OHOS::Ace::NG
