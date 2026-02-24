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

#include "core/components_ng/pattern/time_picker/bridge/arkts_native_timepicker_bridge.h"

#include "interfaces/inner_api/ace_kit/include/ui/base/utils/utils.h"
#include "jsnapi_expo.h"
#include "ui/base/ace_type.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "frameworks/base/i18n/time_format.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "frameworks/compatible/components/picker/picker_base_component.h"

namespace OHOS::Ace::NG {
namespace {
const std::string DEFAULT_ERR_CODE = "-1";
const std::string FORMAT_FONT = "%s|%s|%s";
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr uint32_t DEFAULT_TIME_PICKER_TEXT_COLOR = 0xFF182431;
constexpr uint32_t DEFAULT_TIME_PICKER_SELECTED_TEXT_COLOR = 0xFF0A59F7;
constexpr int PARAM_ARR_LENGTH_1 = 1;

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (firstArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        nativeNode = nullptr;
        return true;
    }

    return false;
}

bool IsJsView(const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    return firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
}

void IsUserDefinedFontFamily(const std::string& pos)
{
    if (pos == "disappearTextStyleTime") {
        GetArkUINodeModifiers()->getTimepickerModifier()->hasUserDefinedDisappearFontFamily(true);
    } else if (pos == "textStyleTime") {
        GetArkUINodeModifiers()->getTimepickerModifier()->hasUserDefinedNormalFontFamily(true);
    } else if (pos == "selectedTextStyleTime") {
        GetArkUINodeModifiers()->getTimepickerModifier()->hasUserDefinedSelectedFontFamily(true);
    }
}

std::string ParseFontSize(
    const EcmaVM* vm, const Local<JSValueRef>& fontSizeArg, RefPtr<ResourceObject>& fontSizeResObj)
{
    CalcDimension fontSizeData;
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) {
        fontSizeData = Dimension(-1);
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, fontSizeArg, fontSizeData, DimensionUnit::FP, fontSizeResObj, false)) {
            fontSizeData = Dimension(-1);
        }
    }
    return fontSizeData.ToString();
}

void ParseTextStyleFontSize(const EcmaVM* vm, const Local<JSValueRef>& fontSizeArg, NG::PickerTextStyle& textStyle)
{
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) {
        textStyle.fontSize = Dimension(-1);
    } else {
        CalcDimension size;
        if (!ArkTSUtils::ParseJsDimensionNG(
                vm, fontSizeArg, size, DimensionUnit::FP, textStyle.fontSizeResObj, false)) {
            textStyle.fontSize = Dimension(-1);
        } else {
            textStyle.fontSize = size;
        }
    }
}

std::string ParseFontWeight(const EcmaVM* vm, const Local<JSValueRef>& fontWeightArg)
{
    std::string weight = DEFAULT_ERR_CODE;
    if (!fontWeightArg->IsNull() && !fontWeightArg->IsUndefined()) {
        if (fontWeightArg->IsNumber()) {
            weight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, fontWeightArg, weight) || weight.empty()) {
                weight = DEFAULT_ERR_CODE;
            }
        }
    }
    return weight;
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

PickerTime ParseTime(
    const EcmaVM* vm, const Local<JSValueRef>& timeVal, PickerTime defaultTime, bool startEndCheckValue)
{
    auto pickerTime = startEndCheckValue ? defaultTime : PickerTime::Current();
    if (!timeVal->IsObject(vm)) {
        return pickerTime;
    }
    panda::TryCatch trycatch(vm);
    auto timeObj = timeVal->ToObject(vm);
    auto yearFuncJsVal = ArkTSUtils::GetProperty(vm, timeObj, "getFullYear");
    if (yearFuncJsVal->IsFunction(vm)) {
        Local<panda::FunctionRef> yearFunc = yearFuncJsVal->ToObject(vm);
        auto year = yearFunc->Call(vm, timeObj, nullptr, 0);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, year);
        if (year->IsNumber() && LessOrEqual(year->ToNumber(vm)->Int32Value(vm), 0)) {
            return pickerTime;
        }
    }

    auto hourFuncJsVal = ArkTSUtils::GetProperty(vm, timeObj, "getHours");
    auto minuteFuncJsVal = ArkTSUtils::GetProperty(vm, timeObj, "getMinutes");
    auto secondFuncJsVal = ArkTSUtils::GetProperty(vm, timeObj, "getSeconds");
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

panda::Local<panda::DateRef> GetDateObj(EcmaVM* vm, const std::unique_ptr<JsonValue>& selectedJson)
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
    auto milliseconds = Date::GetMilliSecondsByDateTime(dateTime);
    auto dateObj = panda::DateRef::New(vm, milliseconds);
    return dateObj;
}

void ParseSelectedDateTimeObject(ArkUIRuntimeCallInfo* runtimeCallInfo, const panda::Local<panda::ObjectRef>& selected)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    auto changeEventVal = selected->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
    if (changeEventVal->IsUndefined() || !changeEventVal->IsFunction(vm)) {
        return;
    }
    panda::Local<panda::FunctionRef> func = changeEventVal->ToObject(vm);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto changeEvent = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode](const BaseEventInfo* info) {
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
        auto dateObj = GetDateObj(vm, sourceJson);
        panda::Local<panda::JSValueRef> params[] = { dateObj };
        PipelineContext::SetCallBackNode(node);
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getTimepickerModifier()->setJSChangeEvent(reinterpret_cast<void*>(&changeEvent));
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

void SetDefaultAttributes()
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;
    auto selectedStyle = theme->GetOptionStyle(true, false);
    textStyle.fontSize = selectedStyle.GetFontSize();
    textStyle.fontWeight = selectedStyle.GetFontWeight();
    GetArkUINodeModifiers()->getTimepickerModifier()->setJSSelectedTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&textStyle));
    auto disappearStyle = theme->GetDisappearOptionStyle();
    textStyle.fontSize = disappearStyle.GetFontSize();
    textStyle.fontWeight = disappearStyle.GetFontWeight();
    GetArkUINodeModifiers()->getTimepickerModifier()->setJSDisappearTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&textStyle));

    auto normalStyle = theme->GetOptionStyle(false, false);
    textStyle.fontSize = normalStyle.GetFontSize();
    textStyle.fontWeight = normalStyle.GetFontWeight();
    GetArkUINodeModifiers()->getTimepickerModifier()->setJSNormalTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&textStyle));
}

ArkUINativeModuleValue SetJSTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    PickerTextStyle textStyle;
    ParseTextStyle(runtimeCallInfo, textStyle, "textStyleTime");
    GetArkUINodeModifiers()->getTimepickerModifier()->setJSNormalTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&textStyle));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetJSSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    PickerTextStyle textStyle;
    ParseTextStyle(runtimeCallInfo, textStyle, "selectedTextStyleTime");
    GetArkUINodeModifiers()->getTimepickerModifier()->setJSSelectedTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&textStyle));
    if (textStyle.textColor.has_value() && theme->IsCircleDial()) {
        GetArkUINodeModifiers()->getTimepickerModifier()->updateUserSetSelectColor();
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetJSDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    PickerTextStyle textStyle;
    ParseTextStyle(runtimeCallInfo, textStyle, "disappearTextStyleTime");
    GetArkUINodeModifiers()->getTimepickerModifier()->setJSDisappearTextStyle(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), reinterpret_cast<void*>(&textStyle));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetJSTimepickerDateTimeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> paramArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    Local<panda::ObjectRef> paramObject;
    ZeroPrefixType hourType = ZeroPrefixType::AUTO;
    ZeroPrefixType minuteType = ZeroPrefixType::AUTO;
    ZeroPrefixType secondType = ZeroPrefixType::AUTO;
    if (!paramArg->IsUndefined() && !paramArg->IsNull() && !paramArg.IsEmpty() && paramArg->IsObject(vm)) {
        paramObject = paramArg->ToObject(vm);
        auto hourArg = ArkTSUtils::GetProperty(vm, paramObject, "hour");
        auto minuteArg = ArkTSUtils::GetProperty(vm, paramObject, "minute");
        auto secondArg = ArkTSUtils::GetProperty(vm, paramObject, "second");
        std::string hour = "hour";
        if (hourArg->IsString(vm)) {
            std::string hour = hourArg->ToString(vm)->ToString(vm);
            if (hour == "2-digit") {
                hourType = ZeroPrefixType::SHOW;
            } else if (hour == "numeric") {
                hourType = ZeroPrefixType::HIDE;
            }
        }
        std::string minute = "minute";
        if (minuteArg->IsString(vm)) {
            minuteType = ZeroPrefixType::SHOW;
            std::string minute = minuteArg->ToString(vm)->ToString(vm);
            if (minute == "numeric") {
                minuteType = ZeroPrefixType::HIDE;
            }
        }
        std::string second = "second";
        if (secondArg->IsString(vm)) {
            secondType = ZeroPrefixType::SHOW;
            std::string second = secondArg->ToString(vm)->ToString(vm);
            if (second == "numeric") {
                secondType = ZeroPrefixType::HIDE;
            }
        }
    }

    GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerDateTimeOptions(nativeNode,
        static_cast<ArkUI_Int32>(hourType), static_cast<ArkUI_Int32>(minuteType), static_cast<ArkUI_Int32>(secondType));
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::ObjectRef> CreateTimePickerOnChange(EcmaVM* vm, const BaseEventInfo* info)
{
    const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(info);
    auto jsonValue = JsonUtil::Create(true);
    CHECK_NULL_RETURN(eventInfo, panda::JSValueRef::Undefined(vm));
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(eventInfo->GetSelectedStr());
    if (!argsPtr) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<std::string> keys = { "year", "month", "day", "hour", "minute", "second" };
    for (auto iter = keys.begin(); iter != keys.end(); iter++) {
        const std::string key = *iter;
        const auto value = argsPtr->GetValue(key);
        if (!value || value->ToString().empty()) {
            continue;
        }
        jsonValue->Put(key.c_str(), value->ToString().c_str());
    }
    Local<JSValueRef> jsValue =
        panda::JSON::Parse(vm, panda::StringRef::NewFromUtf8(vm, jsonValue->ToString().c_str()));
    if (jsValue->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }
    return jsValue->ToObject(vm);
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

void SetJSTimePickerOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerOnChange(
        nativeNode, reinterpret_cast<void*>(&onChange));
    return;
}
} // namespace

void TimePickerBridge::RegisterTimePickerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setTextStyle", "resetTextStyle", "setSelectedTextStyle",
        "resetSelectedTextStyle", "setDisappearTextStyle", "resetDisappearTextStyle", "setBackgroundColor",
        "resetBackgroundColor", "setTimepickerUseMilitaryTime", "resetTimepickerUseMilitaryTime", "setTimepickerLoop",
        "resetTimepickerLoop", "setTimepickerDateTimeOptions", "resetTimepickerDateTimeOptions",
        "setTimepickerEnableHapticFeedback", "resetTimepickerEnableHapticFeedback", "setTimepickerEnableCascade",
        "resetTimepickerEnableCascade", "setTimepickerOnChange", "resetTimepickerOnChange",
        "setDigitalCrownSensitivity", "resetDigitalCrownSensitivity", "setOpacity", "setOnEnterSelectedArea" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::CreateTimePicker),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::ResetTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetSelectedTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::ResetSelectedTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetDisappearTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::ResetDisappearTextStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetTimepickerBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::ResetTimepickerBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetTimepickerUseMilitaryTime),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::ResetTimepickerUseMilitaryTime),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetTimepickerLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::ResetTimepickerLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetTimepickerDateTimeOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::ResetTimepickerDateTimeOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetTimepickerEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::ResetTimepickerEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetTimepickerEnableCascade),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::ResetTimepickerEnableCascade),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetTimepickerOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::ResetTimepickerOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetDigitalCrownSensitivity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::ResetDigitalCrownSensitivity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetOpacity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerBridge::SetOnEnterSelectedArea),
    };

    auto timePicker = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "timePicker"), timePicker);
}

ArkUINativeModuleValue TimePickerBridge::CreateTimePicker(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::ObjectRef> obj = panda::ObjectRef::New(vm);
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber >= NUM_1 && runtimeCallInfo->GetCallArgRef(0)->IsObject(vm)) {
        obj = runtimeCallInfo->GetCallArgRef(0)->ToObject(vm);
    }
    panda::Local<panda::JSValueRef> formatArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "format"));
    panda::Local<panda::JSValueRef> startTimeArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "start"));
    panda::Local<panda::JSValueRef> endTimeArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "end"));

    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    auto parseStartTime = ParseTime(vm, startTimeArg, theme->GetDefaultStartTime(), true);
    auto parseEndTime = ParseTime(vm, endTimeArg, theme->GetDefaultEndTime(), true);
    if (parseStartTime.ToMinutes() > parseEndTime.ToMinutes()) {
        parseStartTime = theme->GetDefaultStartTime();
        parseEndTime = theme->GetDefaultEndTime();
    }
    bool showSecond = false;
    if (formatArg->IsNumber()) {
        auto displayedFormat = static_cast<TimePickerFormat>(formatArg->ToNumber(vm)->Value());
        if (displayedFormat == TimePickerFormat::HOUR_MINUTE_SECOND) {
            showSecond = true;
        }
    }
    GetArkUINodeModifiers()->getTimepickerModifier()->create(
        reinterpret_cast<void*>(AceType::RawPtr(theme)), showSecond);
    GetArkUINodeModifiers()->getTimepickerModifier()->setJSTimepickerStart(reinterpret_cast<void*>(&parseStartTime));
    GetArkUINodeModifiers()->getTimepickerModifier()->setJSTimepickerEnd(reinterpret_cast<void*>(&parseEndTime));
    panda::Local<panda::JSValueRef> selectedArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "selected"));
    if (selectedArg->IsObject(vm)) {
        auto selectedTimeObj = selectedArg->ToObject(vm);
        auto changeEventVal = selectedTimeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
        if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction(vm)) {
            ParseSelectedDateTimeObject(runtimeCallInfo, selectedTimeObj);
            auto parseSelectedTime = ParseTime(
                vm, selectedTimeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value")), PickerTime(), false);
            GetArkUINodeModifiers()->getTimepickerModifier()->setJSSelectedTime(
                reinterpret_cast<void*>(&parseSelectedTime));
        } else {
            auto parseSelectedTime = ParseTime(vm, selectedArg, PickerTime(), false);
            GetArkUINodeModifiers()->getTimepickerModifier()->setJSSelectedTime(
                reinterpret_cast<void*>(&parseSelectedTime));
        }
    }
    SetDefaultAttributes();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetTimepickerBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        Color color = Color::TRANSPARENT;
        if (SystemProperties::ConfigChangePerform()) {
            RefPtr<ResourceObject> colorResObj;
            ArkTSUtils::ParseJsColor(vm, secondArg, color, colorResObj);
            GetArkUINodeModifiers()->getTimepickerModifier()->setBackgroundColorWithResourceObj(
                color.GetValue(), reinterpret_cast<void*>(AceType::RawPtr(colorResObj)));
        } else {
            RefPtr<ResourceObject> colorResObj;
            ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color);
            auto bgColorRawPtr = AceType::RawPtr(colorResObj);
            GetArkUINodeModifiers()->getCommonModifier()->setBackgroundColorWithColorSpace(
                nativeNode, color.GetValue(), color.GetColorSpace(), bgColorRawPtr);
        }
        GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerBackgroundColor(nativeNode, color.GetValue());
    } else {
        uint32_t color = secondArg->Uint32Value(vm);
        GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerBackgroundColor(nativeNode, color);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::ResetTimepickerBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        SetJSTextStyle(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUIPickerTextStyleStruct textStyleStruct;
    Color color;
    RefPtr<ResourceObject> textColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (colorArg->IsNull() || colorArg->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, textColorResObj, nodeInfo)) {
        color.SetValue(DEFAULT_TIME_PICKER_TEXT_COLOR);
        textStyleStruct.textColorSetByUser = false;
    } else {
        textStyleStruct.textColorSetByUser = true;
    }

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSizeStr = ParseFontSize(vm, fontSizeArg, fontSizeResObj);

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

    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());

    textStyleStruct.textColor = color.GetValue();
    textStyleStruct.fontStyle = styleVal;
    textStyleStruct.fontInfo = fontInfo.c_str();
    textStyleStruct.fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    textStyleStruct.fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    textStyleStruct.textColorRawPtr = AceType::RawPtr(textColorResObj);
    GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerTextStyleWithResObj(nativeNode, &textStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        SetJSSelectedTextStyle(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUIPickerTextStyleStruct textStyleStruct;
    Color color;
    RefPtr<ResourceObject> textColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (colorArg->IsNull() || colorArg->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, textColorResObj, nodeInfo)) {
        color.SetValue(DEFAULT_TIME_PICKER_SELECTED_TEXT_COLOR);
        textStyleStruct.textColorSetByUser = false;
    } else {
        textStyleStruct.textColorSetByUser = true;
    }

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSizeStr = ParseFontSize(vm, fontSizeArg, fontSizeResObj);

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

    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());

    textStyleStruct.textColor = color.GetValue();
    textStyleStruct.fontStyle = styleVal;
    textStyleStruct.fontInfo = fontInfo.c_str();
    textStyleStruct.fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    textStyleStruct.fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    textStyleStruct.textColorRawPtr = AceType::RawPtr(textColorResObj);
    GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerSelectedTextStyleWithResObj(
        nativeNode, &textStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        SetJSDisappearTextStyle(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUIPickerTextStyleStruct textStyleStruct;
    Color color;
    RefPtr<ResourceObject> textColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (colorArg->IsNull() || colorArg->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, textColorResObj, nodeInfo)) {
        color.SetValue(DEFAULT_TIME_PICKER_TEXT_COLOR);
        textStyleStruct.textColorSetByUser = false;
    } else {
        textStyleStruct.textColorSetByUser = true;
    }

    RefPtr<ResourceObject> fontSizeResObj;
    std::string fontSizeStr = ParseFontSize(vm, fontSizeArg, fontSizeResObj);

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

    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), fontFamily.c_str());

    textStyleStruct.textColor = color.GetValue();
    textStyleStruct.fontStyle = styleVal;
    textStyleStruct.fontInfo = fontInfo.c_str();
    textStyleStruct.fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    textStyleStruct.fontFamilyRawPtr = AceType::RawPtr(fontFamilyResObj);
    textStyleStruct.textColorRawPtr = AceType::RawPtr(textColorResObj);
    GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerDisappearTextStyleWithResObj(
        nativeNode, &textStyleStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::ResetTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::ResetSelectedTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerSelectedTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::ResetDisappearTextStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerDisappearTextStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetTimepickerUseMilitaryTime(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> useMilitaryArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nodeArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    if (useMilitaryArg->IsBoolean()) {
        bool value = useMilitaryArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerUseMilitaryTime(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerUseMilitaryTime(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::ResetTimepickerUseMilitaryTime(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerUseMilitaryTime(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetTimepickerLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> loopArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nodeArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    if (loopArg->IsBoolean()) {
        bool value = loopArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerLoop(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerLoop(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::ResetTimepickerLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerLoop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetTimepickerDateTimeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> hourArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> minuteArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        SetJSTimepickerDateTimeOptions(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    ZeroPrefixType hourType = ZeroPrefixType::AUTO;
    ZeroPrefixType minuteType = ZeroPrefixType::AUTO;
    ZeroPrefixType secondType = ZeroPrefixType::AUTO;
    std::string hour = "hour";
    if (hourArg->IsString(vm)) {
        std::string hour = hourArg->ToString(vm)->ToString(vm);
        if (hour == "2-digit") {
            hourType = ZeroPrefixType::SHOW;
        } else if (hour == "numeric") {
            hourType = ZeroPrefixType::HIDE;
        }
    }
    std::string minute = "minute";
    if (minuteArg->IsString(vm)) {
        minuteType = ZeroPrefixType::SHOW;
        std::string minute = minuteArg->ToString(vm)->ToString(vm);
        if (minute == "numeric") {
            minuteType = ZeroPrefixType::HIDE;
        }
    }
    std::string second = "second";
    if (secondArg->IsString(vm)) {
        secondType = ZeroPrefixType::SHOW;
        std::string second = secondArg->ToString(vm)->ToString(vm);
        if (second == "numeric") {
            secondType = ZeroPrefixType::HIDE;
        }
    }
    GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerDateTimeOptions(nativeNode,
        static_cast<ArkUI_Int32>(hourType), static_cast<ArkUI_Int32>(minuteType), static_cast<ArkUI_Int32>(secondType));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::ResetTimepickerDateTimeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerDateTimeOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetTimepickerEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableHapticFeedbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nodeArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    if (enableHapticFeedbackArg->IsBoolean()) {
        bool value = enableHapticFeedbackArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerEnableHapticFeedback(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerEnableHapticFeedback(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::ResetTimepickerEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetTimepickerEnableCascade(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);          // 0: index of parameter frameNode
    Local<JSValueRef> enableCascadeArg = runtimeCallInfo->GetCallArgRef(1); // 1: index of parameter enableCascade
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nodeArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    if (enableCascadeArg->IsBoolean()) {
        bool value = enableCascadeArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerEnableCascade(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerEnableCascade(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::ResetTimepickerEnableCascade(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0: index of parameter frameNode
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerEnableCascade(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetDigitalCrownSensitivity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> crownSensitivityArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nodeArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    int32_t crownSensitivity = OHOS::Ace::NG::DEFAULT_CROWNSENSITIVITY;
    if (crownSensitivityArg->IsNumber()) {
        crownSensitivity = crownSensitivityArg->ToNumber(vm)->Value();
    }
    auto modifier = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(modifier, panda::NativePointerRef::New(vm, nullptr));
    modifier->getTimepickerModifier()->setTimePickerDigitalCrownSensitivity(nativeNode, crownSensitivity);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::ResetDigitalCrownSensitivity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto modifier = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(modifier, panda::NativePointerRef::New(vm, nullptr));
    modifier->getTimepickerModifier()->resetTimePickerDigitalCrownSensitivity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetTimepickerOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nativeNodeArg, vm)) {
        SetJSTimePickerOnChange(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo*)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                             const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto dateObj = CreateTimePickerOnChange(vm, info);
        panda::Local<panda::JSValueRef> params[] = { dateObj };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getTimepickerModifier()->setTimepickerOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TimePickerBridge::ResetTimepickerOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTimepickerModifier()->resetTimepickerOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        ArkTSUtils::JsOpacity(vm, secondArg);
        GetArkUINodeModifiers()->getTimepickerModifier()->hasUserDefinedOpacity();
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TimePickerBridge::SetOnEnterSelectedArea(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    CHECK_EQUAL_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nativeNodeArg, vm)) {
        nativeNode = nodePtr(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    } else {
        return panda::JSValueRef::Undefined(vm);
    }
    FrameNode* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo*)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                             const BaseEventInfo* index) {
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("datePicker.onEnterSelectedArea");
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(index);
        panda::Local<panda::JSValueRef> params[] = { DatePickerChangeEventToJSValue(vm, *eventInfo) };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getTimepickerModifier()->setOnEnterSelectedArea(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
