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

#include "frameworks/core/components_ng/pattern/date_picker/bridge/arkts_native_date_picker_bridge.h"

#include "interfaces/napi/kits/utils/napi_utils.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_date_picker_theme.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/date_picker/picker_theme.h"
#include "core/components_ng/pattern/date_picker/picker_type_define.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_FAMILY = "HarmonyOS Sans";
constexpr int PARAM_ARR_LENGTH_1 = 1;

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

void ParseSelectedDateTimeObject(
    ArkUIRuntimeCallInfo* runtimeCallInfo, const panda::Local<panda::ObjectRef>& selectedObject, bool isDatePicker)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    auto changeEventVal = ArkTSUtils::GetProperty(vm, selectedObject, "changeEvent");
    if (changeEventVal->IsUndefined() || !changeEventVal->IsFunction(vm)) {
        return;
    }

    panda::Local<panda::FunctionRef> func = changeEventVal->ToObject(vm);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    std::function<void(const BaseEventInfo*)> changeEvent =
        [vm, func = panda::CopyableGlobal(vm, func), node = targetNode, isDatePicker](const BaseEventInfo* info) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("DatePicker.SelectedDateTimeChangeEvent");

            const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(info);
            CHECK_NULL_VOID(eventInfo);
            auto selectedStr = eventInfo->GetSelectedStr();
            auto sourceJson = JsonUtil::ParseJsonString(selectedStr);
            if (!sourceJson || sourceJson->IsNull()) {
                return;
            }

            auto dateObj = GetDateObj(vm, sourceJson, isDatePicker);
            panda::Local<panda::JSValueRef> params[] = { dateObj };
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };

    if (isDatePicker) {
        GetArkUINodeModifiers()->getDatePickerModifier()->setJSChangeEvent(reinterpret_cast<void*>(&changeEvent));
    } else {
        GetArkUINodeModifiers()->getTimepickerModifier()->setJSChangeEvent(reinterpret_cast<void*>(&changeEvent));
    }
}

void ParseStartEndDate(const EcmaVM* vm, const Local<JSValueRef>& startDate, const Local<JSValueRef>& endDate)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    auto parseStartDate = ParseDate(vm, startDate);
    auto parseEndDate = ParseDate(vm, endDate);
    if (parseStartDate.GetYear() <= 0) {
        parseStartDate = theme->GetDefaultStartDate();
    }
    if (parseEndDate.GetYear() <= 0) {
        parseEndDate = theme->GetDefaultEndDate();
    }
    if (parseStartDate.ToDays() > parseEndDate.ToDays()) {
        parseStartDate = theme->GetDefaultStartDate();
        parseEndDate = theme->GetDefaultEndDate();
    }

    GetArkUINodeModifiers()->getDatePickerModifier()->createDatePicker(
        reinterpret_cast<void*>(AceType::RawPtr(theme)));

    if (startDate->IsObject(vm)) {
        GetArkUINodeModifiers()->getDatePickerModifier()->setJSStartDate(
            reinterpret_cast<void*>(&parseStartDate));
    }
    if (endDate->IsObject(vm)) {
        GetArkUINodeModifiers()->getDatePickerModifier()->setJSEndDate(
            reinterpret_cast<void*>(&parseEndDate));
    }
}

void ParseDatePickerMode(const Local<JSValueRef>& mode, const EcmaVM* vm)
{
    auto datePickerMode = DatePickerMode::DATE;
    if (!mode->IsNull() && mode->IsNumber()) {
        auto parseMode = mode->ToNumber(vm)->Int32Value(vm);
        if (parseMode >= static_cast<int32_t>(DatePickerMode::DATE) &&
            parseMode <= static_cast<int32_t>(DatePickerMode::MONTH_AND_DAY)) {
            datePickerMode = static_cast<DatePickerMode>(parseMode);
        }
    }
    GetArkUINodeModifiers()->getDatePickerModifier()->setJSDatePickerMode(
        static_cast<ArkUI_Int32>(datePickerMode));
}

void SetDefaultAttributes()
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    auto selectedStyle = theme->GetOptionStyle(true, false);
    NG::PickerTextStyle selectedTextStyle;
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        selectedTextStyle.textColor = selectedStyle.GetTextColor();
    }
    selectedTextStyle.fontSize = selectedStyle.GetFontSize();
    selectedTextStyle.fontWeight = selectedStyle.GetFontWeight();
    GetArkUINodeModifiers()->getDatePickerModifier()->setJSSelectedTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&selectedTextStyle));

    auto disappearStyle = theme->GetDisappearOptionStyle();
    NG::PickerTextStyle disappearTextStyle;
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        disappearTextStyle.textColor = disappearStyle.GetTextColor();
    }
    disappearTextStyle.fontSize = disappearStyle.GetFontSize();
    disappearTextStyle.fontWeight = disappearStyle.GetFontWeight();
    GetArkUINodeModifiers()->getDatePickerModifier()->setJSDisappearTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&disappearTextStyle));

    auto normalStyle = theme->GetOptionStyle(false, false);
    NG::PickerTextStyle normalTextStyle;
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        normalTextStyle.textColor = normalStyle.GetTextColor();
    }
    normalTextStyle.fontSize = normalStyle.GetFontSize();
    normalTextStyle.fontWeight = normalStyle.GetFontWeight();
    GetArkUINodeModifiers()->getDatePickerModifier()->setJSTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&normalTextStyle));
}

std::string ParseFontSize(
    const EcmaVM* vm, const Local<JSValueRef>& fontSizeArgs, RefPtr<ResourceObject>& fontSizeResObj)
{
    CalcDimension fontSizeData;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArgs, fontSizeData, fontSizeResObj, true, false) ||
        fontSizeData.Unit() == DimensionUnit::PERCENT) {
        fontSizeData = Dimension(-1);
    }
    return fontSizeData.ToString();
}

std::string ParseFontFamily(
    const EcmaVM* vm, const Local<JSValueRef>& fontFamilyArgs, RefPtr<ResourceObject>& fontFamilyResObj)
{
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArgs, fontFamily, fontFamilyResObj) ||
        fontFamily.empty()) {
        fontFamily = DEFAULT_FAMILY;
    }
    return fontFamily;
}

void ParseTextStyleFontSize(const EcmaVM* vm, const Local<JSValueRef>& fontSizeArg, NG::PickerTextStyle& textStyle)
{
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) {
        textStyle.fontSize = Dimension(-1);
    } else {
        CalcDimension size;
        if (!ArkTSUtils::ParseJsDimensionNG(
            vm, fontSizeArg, size, DimensionUnit::FP, textStyle.fontSizeResObj, false) ||
            size.Unit() == DimensionUnit::PERCENT) {
            textStyle.fontSize = Dimension(-1);
        } else {
            textStyle.fontSize = size;
        }
    }
}

void ParseTextStyleFontWeight(const EcmaVM* vm, const Local<JSValueRef>& fontWeightArg, NG::PickerTextStyle& textStyle)
{
    if (!fontWeightArg->IsNull() && !fontWeightArg->IsUndefined()) {
        std::string weight;
        if (fontWeightArg->IsNumber()) {
            weight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            ArkTSUtils::ParseJsString(vm, fontWeightArg, weight);
        }
        textStyle.fontWeight = Framework::ConvertStrToFontWeight(weight);
    }
}

void ParseTextStyleFontFamily(
    const EcmaVM* vm, const Local<JSValueRef>& fontFamilyArg, NG::PickerTextStyle& textStyle, const std::string& pos)
{
    if (!fontFamilyArg->IsNull() && !fontFamilyArg->IsUndefined()) {
        std::vector<std::string> fontFamilies;
        if (ArkTSUtils::ParseJsFontFamilies(vm, fontFamilyArg, fontFamilies, textStyle.fontFamilyResObj)) {
            textStyle.fontFamily = fontFamilies;
            IsUserDefinedFontFamily(pos);
        }
    }
}

void ParseTextStyleFontStyle(const EcmaVM* vm, const Local<JSValueRef>& fontStyleArg, NG::PickerTextStyle& textStyle)
{
    if (fontStyleArg->IsNumber()) {
        int32_t fontStyle = fontStyleArg->Int32Value(vm);
        if (fontStyle < 0 || fontStyle > 1) {
            return;
        }
        textStyle.fontStyle = static_cast<Ace::FontStyle>(fontStyle);
    }
}

void ParseTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo, NG::PickerTextStyle& textStyle, const std::string& pos)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_5);

    Color textColor;
    if (ArkTSUtils::ParseJsColor(vm, colorArg, textColor, textStyle.textColorResObj)) {
        textStyle.textColor = textColor;
        textStyle.textColorSetByUser = true;
    }
    ParseTextStyleFontSize(vm, fontSizeArg, textStyle);
    ParseTextStyleFontWeight(vm, fontWeightArg, textStyle);
    ParseTextStyleFontFamily(vm, fontFamilyArg, textStyle, pos);
    ParseTextStyleFontStyle(vm, fontStyleArg, textStyle);
}

ArkUINativeModuleValue SetJSSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto theme = frameNode->GetTheme<PickerTheme>(true);
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    NG::PickerTextStyle textStyle;
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        if (!theme->IsCircleDial()) {
            Framework::JSDatePickerTheme::ObtainSelectedTextStyle(textStyle);
        }
    }
    ParseTextStyle(runtimeCallInfo, textStyle, "selectedTextStyle");
    GetArkUINodeModifiers()->getDatePickerModifier()->setJSSelectedTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&textStyle));
    if (textStyle.textColor.has_value() && theme->IsCircleDial()) {
        GetArkUINodeModifiers()->getDatePickerModifier()->updateUserSetSelectColor();
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetJSTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto theme = frameNode->GetTheme<PickerTheme>(true);
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    NG::PickerTextStyle textStyle;
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        Framework::JSDatePickerTheme::ObtainTextStyle(textStyle);
    }
    ParseTextStyle(runtimeCallInfo, textStyle, "textStyle");
    GetArkUINodeModifiers()->getDatePickerModifier()->setJSTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&textStyle));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetJSDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto theme = frameNode->GetTheme<PickerTheme>(true);
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    PickerTextStyle textStyle;
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        Framework::JSDatePickerTheme::ObtainTextStyle(textStyle);
    }
    ParseTextStyle(runtimeCallInfo, textStyle, "disappearTextStyle");
    GetArkUINodeModifiers()->getDatePickerModifier()->setJSDisappearTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&textStyle));
    return panda::JSValueRef::Undefined(vm);
}

Local<JSValueRef> DatePickerChangeEventToJSValue(const EcmaVM* vm, const DatePickerChangeEvent& eventInfo)
{
    auto obj = panda::ObjectRef::New(const_cast<panda::EcmaVM*>(vm));
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(eventInfo.GetSelectedStr());
    if (!argsPtr) {
        return obj;
    }
    std::vector<std::string> keys = { "year", "month", "day", "hour", "minute", "second" };
    for (auto iter = keys.begin(); iter != keys.end(); iter++) {
        const std::string key = *iter;
        const auto value = argsPtr->GetValue(key);
        if (!value || value->ToString().empty()) {
            continue;
        }
        auto pandaKey = panda::StringRef::NewFromUtf8(vm, key.c_str());
        auto pandaValue = panda::IntegerRef::New(vm, value->GetInt());
        obj->Set(vm, pandaKey, pandaValue);
    }
    return obj;
}

Local<JSValueRef> DatePickerDateChangeEventToJSValue(const EcmaVM* vm, const DatePickerChangeEvent& eventInfo)
{
    auto obj = panda::ObjectRef::New(const_cast<panda::EcmaVM*>(vm));
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(eventInfo.GetSelectedStr());
    if (!argsPtr) {
        return obj;
    }
    return GetDateObj(const_cast<panda::EcmaVM*>(vm), argsPtr, true);
}

void SetJSDatePickerOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return;
    }
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(nativeNode);
    FrameNode* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_VOID(frameNode);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        return;
    }
    Local<panda::FunctionRef> jsfunc = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo*)> onChange = [vm, func = panda::CopyableGlobal(vm, jsfunc),
                                                             node = AceType::WeakClaim(frameNode)](
                                                             const BaseEventInfo* index) {
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("datePicker.onChange");
        PipelineContext::SetCallBackNode(node);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(index);
        panda::Local<panda::JSValueRef> params[] = { DatePickerChangeEventToJSValue(vm, *eventInfo) };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getDatePickerModifier()->setDatePickerOnChange(
        nativeNode, reinterpret_cast<void*>(&onChange));
    return;
}

void SetJSDatePickerOnDateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return;
    }
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(nativeNode);
    FrameNode* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_VOID(frameNode);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        return;
    }
    Local<panda::FunctionRef> jsfunc = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo*)> onChange = [vm, func = panda::CopyableGlobal(vm, jsfunc),
                                                             node = AceType::WeakClaim(frameNode)](
                                                             const BaseEventInfo* index) {
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("datePicker.onDateChange");
        PipelineContext::SetCallBackNode(node);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(index);
        panda::Local<panda::JSValueRef> params[] = { DatePickerDateChangeEventToJSValue(vm, *eventInfo) };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getDatePickerModifier()->setDatePickerOnDateChange(
        nativeNode, reinterpret_cast<void*>(&onChange));
    return;
}
} // namespace

void DatePickerBridge::RegisterDatePickerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setSelectedTextStyle", "resetSelectedTextStyle", "setTextStyle",
        "resetTextStyle", "setDisappearTextStyle", "resetDisappearTextStyle", "setLunar", "resetLunar",
        "setBackgroundColor", "resetBackgroundColor", "setEnableHapticFeedback", "resetEnableHapticFeedback",
        "setDatePickerOnChange", "resetDatePickerOnChange", "setDatePickerOnDateChange", "resetDatePickerOnDateChange",
        "setDigitalCrownSensitivity", "resetDigitalCrownSensitivity", "setCanLoop", "resetCanLoop", "setOpacity",
        "setUseMilitaryTime" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::CreateDatePicker),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetSelectedTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetSelectedTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetDisappearTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetDisappearTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetLunar),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetLunar),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetDatePickerOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetDatePickerOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetDatePickerOnDateChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetDatePickerOnDateChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetDigitalCrownSensitivity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetDigitalCrownSensitivity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetCanLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetCanLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetOpacity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetUseMilitaryTime),
    };

    auto datePicker = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "datePicker"), datePicker);
}

ArkUINativeModuleValue DatePickerBridge::CreateDatePicker(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    DatePickerType pickerType = DatePickerType::DATE;
    panda::Local<panda::ObjectRef> obj = panda::ObjectRef::New(vm);
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber >= NUM_1 && runtimeCallInfo->GetCallArgRef(NUM_0)->IsObject(vm)) {
        obj = runtimeCallInfo->GetCallArgRef(NUM_0)->ToObject(vm);
        auto typeArg = ArkTSUtils::GetProperty(vm, obj, "type");
        if (typeArg->IsNumber()) {
            pickerType = static_cast<DatePickerType>(typeArg->ToNumber(vm)->Int32Value(vm));
        }
    }

    switch (pickerType) {
        case DatePickerType::TIME: {
            auto theme = GetTheme<PickerTheme>();
            CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));

            GetArkUINodeModifiers()->getDatePickerModifier()->createTimePicker(
                reinterpret_cast<void*>(AceType::RawPtr(theme)));

            auto selectedTime = ArkTSUtils::GetProperty(vm, obj, "selected");
            if (selectedTime->IsObject(vm)) {
                auto selectedTimeObj = selectedTime->ToObject(vm);
                auto changeEventVal = ArkTSUtils::GetProperty(vm, selectedTimeObj, "changeEvent");
                if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction(vm)) {
                    ParseSelectedDateTimeObject(runtimeCallInfo, selectedTimeObj, false);
                    auto valueArg = ArkTSUtils::GetProperty(vm, selectedTimeObj, "value");
                    auto parseSelectedTime = ParseTime(vm, valueArg);
                    GetArkUINodeModifiers()->getDatePickerModifier()->setJSSelectedTime(
                        reinterpret_cast<void*>(&parseSelectedTime));
                } else {
                    auto parseSelectedTime = ParseTime(vm, selectedTime);
                    GetArkUINodeModifiers()->getDatePickerModifier()->setJSSelectedTime(
                        reinterpret_cast<void*>(&parseSelectedTime));
                }
            }
            break;
        }
        case DatePickerType::DATE: {
            auto startDate = ArkTSUtils::GetProperty(vm, obj, "start");
            auto endDate = ArkTSUtils::GetProperty(vm, obj, "end");
            auto selectedDate = ArkTSUtils::GetProperty(vm, obj, "selected");
            auto mode = ArkTSUtils::GetProperty(vm, obj, "mode");

            ParseStartEndDate(vm, startDate, endDate);

            PickerDate parseSelectedDate = PickerDate::Current();
            if (selectedDate->IsObject(vm)) {
                auto selectedDateObj = selectedDate->ToObject(vm);
                auto changeEventVal = ArkTSUtils::GetProperty(vm, selectedDateObj, "changeEvent");
                if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction(vm)) {
                    ParseSelectedDateTimeObject(runtimeCallInfo, selectedDateObj, true);
                    auto valueArg = ArkTSUtils::GetProperty(vm, selectedDateObj, "value");
                    parseSelectedDate = ParseDate(vm, valueArg);
                } else {
                    parseSelectedDate = ParseDate(vm, selectedDate);
                }
            }

            GetArkUINodeModifiers()->getDatePickerModifier()->setJSSelectedDate(
                reinterpret_cast<void*>(&parseSelectedDate));
            ParseDatePickerMode(mode, vm);
            SetDefaultAttributes();
            break;
        }
        default:
            break;
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> textColorArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArgs = runtimeCallInfo->GetCallArgRef(NUM_5);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        SetJSSelectedTextStyle(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }

    bool isUndefinedValue = ((textColorArgs->IsNull() || textColorArgs->IsUndefined()) &&
                             (fontSizeArgs->IsNull() || fontSizeArgs->IsUndefined()) &&
                             (fontWeightArgs->IsNull() || fontWeightArgs->IsUndefined()) &&
                             (fontFamilyArgs->IsNull() || fontFamilyArgs->IsUndefined()) &&
                             (fontStyleArgs->IsNull() || fontStyleArgs->IsUndefined()));
    if (isUndefinedValue) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetSelectedTextStyle(nativeNode);
    }

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSize = ParseFontSize(vm, fontSizeArgs, fontSizeResObj);

    std::string weight = "FontWeight.Medium";
    if (fontWeightArgs->IsString(vm) || fontWeightArgs->IsNumber()) {
        weight = fontWeightArgs->ToString(vm)->ToString(vm);
    }

    RefPtr<ResourceObject> fontFamilyResObj;
    std::string fontFamily = ParseFontFamily(vm, fontFamilyArgs, fontFamilyResObj);

    int32_t fontStyle = fontStyleArgs->IsNumber() ? fontStyleArgs->Int32Value(vm) : 0;
    Color color;
    RefPtr<ResourceObject> textColorResObj;
    ArkUIPickerTextStyleStruct textStyleStruct;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, textColorArgs, color, textColorResObj, nodeInfo)) {
        Color::ParseColorString("#ff0a59f7", color);
        textStyleStruct.textColorSetByUser = false;
    } else {
        textStyleStruct.textColorSetByUser = true;
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());

    textStyleStruct.textColor = color.GetValue();
    textStyleStruct.fontStyle = fontStyle;
    textStyleStruct.fontInfo = fontInfo.c_str();
    textStyleStruct.fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    textStyleStruct.fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    textStyleStruct.textColorRawPtr = AceType::RawPtr(textColorResObj);
    GetArkUINodeModifiers()->getDatePickerModifier()->setSelectedTextStyleWithResObj(nativeNode, &textStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetSelectedTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> textColorArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArgs = runtimeCallInfo->GetCallArgRef(NUM_5);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        SetJSTextStyle(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }

    bool isUndefinedValue = ((textColorArgs->IsNull() || textColorArgs->IsUndefined()) &&
                             (fontSizeArgs->IsNull() || fontSizeArgs->IsUndefined()) &&
                             (fontWeightArgs->IsNull() || fontWeightArgs->IsUndefined()) &&
                             (fontFamilyArgs->IsNull() || fontFamilyArgs->IsUndefined()) &&
                             (fontStyleArgs->IsNull() || fontStyleArgs->IsUndefined()));
    if (isUndefinedValue) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetDatePickerTextStyle(nativeNode);
    }

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSize = ParseFontSize(vm, fontSizeArgs, fontSizeResObj);

    std::string weight = "FontWeight.Regular";
    if (fontWeightArgs->IsString(vm) || fontWeightArgs->IsNumber()) {
        weight = fontWeightArgs->ToString(vm)->ToString(vm);
    }

    RefPtr<ResourceObject> fontFamilyResObj;
    std::string fontFamily = ParseFontFamily(vm, fontFamilyArgs, fontFamilyResObj);

    int32_t fontStyle = fontStyleArgs->IsNumber() ? fontStyleArgs->Int32Value(vm) : 0;
    Color color;
    RefPtr<ResourceObject> textColorResObj;
    ArkUIPickerTextStyleStruct textStyleStruct;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, textColorArgs, color, textColorResObj, nodeInfo)) {
        Color::ParseColorString("#ff182431", color);
        textStyleStruct.textColorSetByUser = false;
    } else {
        textStyleStruct.textColorSetByUser = true;
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());

    textStyleStruct.textColor = color.GetValue();
    textStyleStruct.fontStyle = fontStyle;
    textStyleStruct.fontInfo = fontInfo.c_str();
    textStyleStruct.fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    textStyleStruct.fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    textStyleStruct.textColorRawPtr = AceType::RawPtr(textColorResObj);
    GetArkUINodeModifiers()->getDatePickerModifier()->setDatePickerTextStyleWithResObj(nativeNode, &textStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetDatePickerTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> textColorArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArgs = runtimeCallInfo->GetCallArgRef(NUM_5);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        SetJSDisappearTextStyle(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }

    bool isUndefinedValue = ((textColorArgs->IsNull() || textColorArgs->IsUndefined()) &&
                             (fontSizeArgs->IsNull() || fontSizeArgs->IsUndefined()) &&
                             (fontWeightArgs->IsNull() || fontWeightArgs->IsUndefined()) &&
                             (fontFamilyArgs->IsNull() || fontFamilyArgs->IsUndefined()) &&
                             (fontStyleArgs->IsNull() || fontStyleArgs->IsUndefined()));
    if (isUndefinedValue) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetDisappearTextStyle(nativeNode);
    }

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSize = ParseFontSize(vm, fontSizeArgs, fontSizeResObj);

    std::string weight = "FontWeight.Regular";
    if (fontWeightArgs->IsString(vm) || fontWeightArgs->IsNumber()) {
        weight = fontWeightArgs->ToString(vm)->ToString(vm);
    }

    RefPtr<ResourceObject> fontFamilyResObj;
    std::string fontFamily = ParseFontFamily(vm, fontFamilyArgs, fontFamilyResObj);

    int32_t fontStyle = fontStyleArgs->IsNumber() ? fontStyleArgs->Int32Value(vm) : 0;
    Color color;
    RefPtr<ResourceObject> textColorResObj;
    ArkUIPickerTextStyleStruct textStyleStruct;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, textColorArgs, color, textColorResObj, nodeInfo)) {
        Color::ParseColorString("#ff182431", color);
        textStyleStruct.textColorSetByUser = false;
    } else {
        textStyleStruct.textColorSetByUser = true;
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());

    textStyleStruct.textColor = color.GetValue();
    textStyleStruct.fontStyle = fontStyle;
    textStyleStruct.fontInfo = fontInfo.c_str();
    textStyleStruct.fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    textStyleStruct.fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    textStyleStruct.textColorRawPtr = AceType::RawPtr(textColorResObj);
    GetArkUINodeModifiers()->getDatePickerModifier()->setDisappearTextStyleWithResObj(nativeNode, &textStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetDisappearTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetLunar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> isLunarArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(nodeArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    if (isLunarArg->IsNull() || isLunarArg->IsUndefined() || !isLunarArg->IsBoolean()) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetLunar(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool isLunar = static_cast<ArkUI_Bool>(isLunarArg->Uint32Value(vm));
    GetArkUINodeModifiers()->getDatePickerModifier()->setLunar(nativeNode, isLunar);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetLunar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetLunar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        CommonBridge::SetBackgroundColor(runtimeCallInfo);
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));

        Color color = Color::TRANSPARENT;
        if (SystemProperties::ConfigChangePerform()) {
            RefPtr<ResourceObject> colorResObj;
            if (!ArkTSUtils::ParseJsColor(vm, colorArg, color, colorResObj)) {
                return panda::JSValueRef::Undefined(vm);
            }
            GetArkUINodeModifiers()->getDatePickerModifier()->setBackgroundColorWithResourceObj(
                color.GetValue(), reinterpret_cast<void*>(AceType::RawPtr(colorResObj)));
        } else {
            if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
                return panda::JSValueRef::Undefined(vm);
            }
            GetArkUINodeModifiers()->getCommonModifier()->setBackgroundColorWithColorSpace(
                nativeNode, color.GetValue(), color.GetColorSpace(), nullptr);
        }
        GetArkUINodeModifiers()->getDatePickerModifier()->setDatePickerBackgroundColorWithColorSpace(
            nativeNode, color.GetValue(), color.GetColorSpace());
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t color = colorArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getDatePickerModifier()->setDatePickerBackgroundColor(nativeNode, color);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::ResetBackgroundColor(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetDatePickerBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetDigitalCrownSensitivity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> crownSensitivityArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(nodeArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    int32_t crownSensitivity = OHOS::Ace::NG::DEFAULT_CROWNSENSITIVITY;
    bool isUndefinedValue = (crownSensitivityArg->IsNull() || crownSensitivityArg->IsUndefined());
    if (!isUndefinedValue && crownSensitivityArg->IsNumber()) {
        crownSensitivity = crownSensitivityArg->ToNumber(vm)->Value();
    }
    auto modifier = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(modifier, panda::NativePointerRef::New(vm, nullptr));
    modifier->getDatePickerModifier()->setDatePickerDigitalCrownSensitivity(nativeNode, crownSensitivity);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetDigitalCrownSensitivity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto modifier = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(modifier, panda::NativePointerRef::New(vm, nullptr));
    modifier->getDatePickerModifier()->resetDatePickerDigitalCrownSensitivity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableHapticFeedbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(nodeArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto datePickerModifier = nodeModifiers->getDatePickerModifier();
    CHECK_NULL_RETURN(datePickerModifier, panda::NativePointerRef::New(vm, nullptr));
    bool isUndefinedValue = (enableHapticFeedbackArg->IsNull() || enableHapticFeedbackArg->IsUndefined());
    if (!isUndefinedValue && enableHapticFeedbackArg->IsBoolean()) {
        bool value = enableHapticFeedbackArg->ToBoolean(vm)->Value();
        datePickerModifier->setEnableHapticFeedback(nativeNode, value);
    } else {
        datePickerModifier->resetEnableHapticFeedback(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto datePickerModifier = nodeModifiers->getDatePickerModifier();
    CHECK_NULL_RETURN(datePickerModifier, panda::NativePointerRef::New(vm, nullptr));
    datePickerModifier->resetEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetCanLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> canLoopArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(nodeArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto datePickerModifier = nodeModifiers->getDatePickerModifier();
    CHECK_NULL_RETURN(datePickerModifier, panda::NativePointerRef::New(vm, nullptr));
    bool isUndefinedValue = (canLoopArg->IsNull() || canLoopArg->IsUndefined());
    if (!isUndefinedValue && canLoopArg->IsBoolean()) {
        bool value = canLoopArg->ToBoolean(vm)->Value();
        datePickerModifier->setCanLoop(nativeNode, value);
    } else {
        datePickerModifier->resetCanLoop(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetCanLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto datePickerModifier = nodeModifiers->getDatePickerModifier();
    CHECK_NULL_RETURN(datePickerModifier, panda::NativePointerRef::New(vm, nullptr));
    datePickerModifier->resetCanLoop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        ArkTSUtils::JsOpacity(vm, secondArg);
        GetArkUINodeModifiers()->getDatePickerModifier()->hasUserDefinedOpacity();
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetUseMilitaryTime(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> useMilitaryArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(nodeArg, vm)) {
        if (useMilitaryArg->IsBoolean()) {
            bool value = static_cast<ArkUI_Bool>(useMilitaryArg->Uint32Value(vm));
            GetArkUINodeModifiers()->getDatePickerModifier()->setUseMilitaryTime(value);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

double GetMSByDateToDouble(const std::string& date)
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
        dateTime.tm_mon = month->GetInt();
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
panda::Local<panda::ObjectRef> CreateOnChange(EcmaVM* vm, const BaseEventInfo* info)
{
    const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(info);
    CHECK_NULL_RETURN(eventInfo, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> jsonValue =
        panda::JSON::Parse(vm, panda::StringRef::NewFromUtf8(vm, eventInfo->GetSelectedStr().c_str()));
    if (jsonValue->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto datePickerResultObj = jsonValue->ToObject(vm);
    return datePickerResultObj;
}
ArkUINativeModuleValue DatePickerBridge::SetDatePickerOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        SetJSDatePickerOnChange(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetDatePickerOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo*)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                             const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto dateObj = CreateOnChange(vm, info);
        panda::Local<panda::JSValueRef> params[] = { dateObj };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getDatePickerModifier()->setDatePickerOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue DatePickerBridge::ResetDatePickerOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetDatePickerOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::SetDatePickerOnDateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        SetJSDatePickerOnDateChange(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetDatePickerOnDateChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo*)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                             const BaseEventInfo* info) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(info);
        CHECK_NULL_VOID(eventInfo);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::DateRef> dateObj =
            panda::DateRef::New(vm, GetMSByDateToDouble(eventInfo->GetSelectedStr()));
        panda::Local<panda::JSValueRef> params[] = { dateObj };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getDatePickerModifier()->setDatePickerOnDateChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DatePickerBridge::ResetDatePickerOnDateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDatePickerModifier()->resetDatePickerOnDateChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
