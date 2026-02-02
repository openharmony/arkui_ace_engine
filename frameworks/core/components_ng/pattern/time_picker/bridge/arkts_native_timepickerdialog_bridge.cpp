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

#include "core/components_ng/pattern/time_picker/bridge/arkts_native_timepickerdialog_bridge.h"

#include "ark_native_engine.h"
#include "jsnapi_expo.h"
#include "native_engine.h"
#include "ui/base/ace_type.h"
#include "ui/base/utils/utils.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/picker/picker_model.h"
#include "core/components_ng/pattern/time_picker/timepicker_model.h"
namespace OHOS::Ace::NG {
namespace {
const DimensionOffset DATEPICKER_OFFSET_DEFAULT_TOP = DimensionOffset(0.0_vp, 40.0_vp);
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const char TIMEPICKER_OPTIONS_HOUR[] = "hour";
const char TIMEPICKER_OPTIONS_MINUTE[] = "minute";
const std::string TIMEPICKER_OPTIONS_NUMERIC_VAL = "numeric";
const std::string TIMEPICKER_OPTIONS_TWO_DIGIT_VAL = "2-digit";
const std::vector<HoverModeAreaType> HOVER_MODE_AREA_TYPE = { HoverModeAreaType::TOP_SCREEN,
    HoverModeAreaType::BOTTOM_SCREEN };

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
    ArkTSUtils::HandleCallbackJobs(vm, trycatch, year);
    Local<JSValueRef> date = dateFunc->Call(vm, dateObj, nullptr, 0);
    ArkTSUtils::HandleCallbackJobs(vm, trycatch, year);

    if (year->IsNumber() && month->IsNumber() && date->IsNumber()) {
        pickerDate.SetYear(year->ToNumber(vm)->Value());
        pickerDate.SetMonth(month->ToNumber(vm)->Value() + 1); // 0-11 means 1 to 12 months
        pickerDate.SetDay(date->ToNumber(vm)->Value());
    }
    return pickerDate;
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
    ParseTextStyleFontWeight(vm, fontWeight, textStyle);
    ParseTextStyleFontFamily(vm, fontFamily, textStyle, pos);
    ParseTextStyleFontStyle(vm, fontStyle, textStyle);
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

void TimePickerDialogAppearEvent(ArkUIRuntimeCallInfo* runtimeCallInfo, TimePickerDialogEvent& timePickerDialogEvent)
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
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidAppear = ArkTSUtils::GetProperty(vm, paramObject, "onDidAppear");
    if (!onDidAppear->IsUndefined() && onDidAppear->IsFunction(vm)) {
        Local<panda::FunctionRef> jsFunc = onDidAppear->ToObject(vm);
        didAppearEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), node = targetNode]() {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("DatePickerDialog.onDidAppear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    auto onWillAppear = ArkTSUtils::GetProperty(vm, paramObject, "onWillAppear");
    if (!onWillAppear->IsUndefined() && onWillAppear->IsFunction(vm)) {
        Local<panda::FunctionRef> jsFunc = onWillAppear->ToObject(vm);
        willAppearEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), node = targetNode]() {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("DatePickerDialog.onWillAppear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    timePickerDialogEvent.onDidAppear = std::move(didAppearEvent);
    timePickerDialogEvent.onWillAppear = std::move(willAppearEvent);
}

void TimePickerDialogDisappearEvent(ArkUIRuntimeCallInfo* runtimeCallInfo, TimePickerDialogEvent& timePickerDialogEvent)
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
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidDisappear = ArkTSUtils::GetProperty(vm, paramObject, "onDidDisappear");
    if (!onDidDisappear->IsUndefined() && onDidDisappear->IsFunction(vm)) {
        Local<panda::FunctionRef> jsFunc = onDidDisappear->ToObject(vm);
        didDisappearEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), node = targetNode]() {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("DatePickerDialog.onDidDisappear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    auto onWillDisappear = ArkTSUtils::GetProperty(vm, paramObject, "onWillDisappear");
    if (!onWillDisappear->IsUndefined() && onWillDisappear->IsFunction(vm)) {
        Local<panda::FunctionRef> jsFunc = onWillDisappear->ToObject(vm);
        willDisappearEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), node = targetNode]() {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("DatePickerDialog.onWillDisappear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    timePickerDialogEvent.onDidDisappear = std::move(didDisappearEvent);
    timePickerDialogEvent.onWillDisappear = std::move(willDisappearEvent);
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
    CHECK_NULL_VOID(vm);
    auto blurStyleValue = ArkTSUtils::GetProperty(vm, paramObject, "backgroundBlurStyleOptions");
    if (blurStyleValue->IsObject(vm)) {
        if (!pickerDialog.blurStyleOption.has_value()) {
            pickerDialog.blurStyleOption.emplace();
        }
        ArkTSUtils::ParseBlurStyleOption(vm, blurStyleValue, pickerDialog.blurStyleOption.value());
    }
}

void ParseDatePickerEffectOption(const EcmaVM* vm, PickerDialogInfo& pickerDialog, const Local<JSValueRef>& paramObject)
{
    CHECK_NULL_VOID(vm);
    auto effectOptionValue = ArkTSUtils::GetProperty(vm, paramObject, "backgroundEffect");
    if (effectOptionValue->IsObject(vm)) {
        if (!pickerDialog.effectOption.has_value()) {
            pickerDialog.effectOption.emplace();
        }
        ArkTSUtils::ParseEffectOption(vm, effectOptionValue, pickerDialog.effectOption.value());
    }
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
} // namespace

void TimePickerDialogBridge::RegisterTimePickerDialogAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "show" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimePickerDialogBridge::JSShow),
    };

    auto timePickerDialog =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "timePickerDialog"), timePickerDialog);
}
ArkUINativeModuleValue TimePickerDialogBridge::JSShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    std::function<void()> cancelEvent;
    std::function<void(const std::string&)> acceptEvent;
    std::function<void(const std::string&)> changeEvent;
    std::function<void(const std::string&)> enterEvent;
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = ArkTSUtils::GetProperty(vm, paramObject, "onChange");
    if (!onChange->IsUndefined() && onChange->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onChange->ToObject(vm);
        changeEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), targetNode](const std::string& info) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("DatePickerDialog.onChange");
            PipelineContext::SetCallBackNode(targetNode);
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
    }
    auto onEnterSelectedArea = ArkTSUtils::GetProperty(vm, paramObject, "onEnterSelectedArea");
    if (!onEnterSelectedArea->IsUndefined() && onEnterSelectedArea->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onEnterSelectedArea->ToObject(vm);
        enterEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), targetNode](const std::string& info) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("DatePickerDialog.onEnterSelectedArea");
            PipelineContext::SetCallBackNode(targetNode);
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
    }
    auto onAccept = ArkTSUtils::GetProperty(vm, paramObject, "onAccept");
    if (!onAccept->IsUndefined() && onAccept->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onAccept->ToObject(vm);
        acceptEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), targetNode](const std::string& info) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("DatePickerDialog.onAccept");
            PipelineContext::SetCallBackNode(targetNode);
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
    }
    auto onCancel = ArkTSUtils::GetProperty(vm, paramObject, "onCancel");
    if (!onCancel->IsUndefined() && onCancel->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onCancel;
        cancelEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), targetNode]() {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(targetNode);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    auto startTime = ArkTSUtils::GetProperty(vm, paramObject, "start");
    auto endTime = ArkTSUtils::GetProperty(vm, paramObject, "end");
    auto selectedTime = ArkTSUtils::GetProperty(vm, paramObject, "selected");
    auto useMilitaryTime = ArkTSUtils::GetProperty(vm, paramObject, "useMilitaryTime");
    auto enableCascade = ArkTSUtils::GetProperty(vm, paramObject, "enableCascade");
    NG::TimePickerSettingData settingData;
    PickerDialogInfo pickerDialog;
    settingData.isUseMilitaryTime = useMilitaryTime->ToBoolean(vm)->Value();
    settingData.isEnableCascade = enableCascade->ToBoolean(vm)->Value();
    pickerDialog.isUseMilitaryTime = useMilitaryTime->ToBoolean(vm)->Value();
    pickerDialog.isEnableCascade = enableCascade->ToBoolean(vm)->Value();
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, panda::NativePointerRef::New(vm, nullptr));
    auto parseStartTime = ParseTime(vm, startTime, theme->GetDefaultStartTime(), true);
    auto parseEndTime = ParseTime(vm, endTime, theme->GetDefaultEndTime(), true);
    if (parseStartTime.ToMinutes() > parseEndTime.ToMinutes()) {
        parseStartTime = theme->GetDefaultStartTime();
        parseEndTime = theme->GetDefaultEndTime();
    }
    pickerDialog.parseStartTime = parseStartTime;
    pickerDialog.parseEndTime = parseEndTime;

    if (selectedTime->IsObject(vm)) {
        PickerDate dialogTitleDate = ParseDate(vm, selectedTime);
        if (dialogTitleDate.GetYear() != 0) {
            settingData.dialogTitleDate = dialogTitleDate;
            pickerDialog.isSelectedTime = true;
            pickerDialog.pickerTime = ParseTime(vm, selectedTime, PickerTime(), false);
        }
    }
    ParseTextProperties(vm, paramObject, settingData.properties);
    auto dateTimeOptionsValue = ArkTSUtils::GetProperty(vm, paramObject, "dateTimeOptions");
    if (dateTimeOptionsValue->IsObject(vm)) {
        auto dateTimeOptionsObj = dateTimeOptionsValue->ToObject(vm);
        ParseDateTimeOptions(vm, dateTimeOptionsObj, settingData.dateTimeOptions);
    }

    // Parse alignment
    auto alignmentValue = ArkTSUtils::GetProperty(vm, paramObject, "alignment");
    if (alignmentValue->IsNumber()) {
        auto alignment = alignmentValue->ToNumber(vm)->Int32Value(vm);
        if (alignment >= 0 && alignment < static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
            pickerDialog.alignment = DIALOG_ALIGNMENT[alignment];
        }
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
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

    ParseDatePickerHoverMode(vm, pickerDialog, paramObject);
    ParseDatePickerBlurStyleOption(vm, pickerDialog, paramObject);
    ParseDatePickerEffectOption(vm, pickerDialog, paramObject);

    auto buttonInfos = ParseButtonStyles(vm, paramObject);

    auto shadowValue = ArkTSUtils::GetProperty(vm, paramObject, "shadow");
    Shadow shadow;
    if ((shadowValue->IsObject(vm) || shadowValue->IsNumber()) &&
        ArkTSUtils::ParseShadowProps(vm, shadowValue, shadow)) {
        pickerDialog.shadow = shadow;
    }
    auto formatValue = ArkTSUtils::GetProperty(vm, paramObject, "format");
    bool showSecond = false;
    if (formatValue->IsNumber()) {
        auto displayedFormat = static_cast<TimePickerFormat>(formatValue->ToNumber(vm)->Int32Value(vm));
        if (displayedFormat == TimePickerFormat::HOUR_MINUTE_SECOND) {
            showSecond = true;
        }
    }
    settingData.showSecond = showSecond;
    auto enableHapticFeedbackValue = ArkTSUtils::GetProperty(vm, paramObject, "enableHapticFeedback");
    bool isEnableHapticFeedback = true;
    if (enableHapticFeedbackValue->IsBoolean()) {
        isEnableHapticFeedback = enableHapticFeedbackValue->ToBoolean(vm)->BooleaValue(vm);
    }
    settingData.isEnableHapticFeedback = isEnableHapticFeedback;
    OHOS::Ace::TimePickerDialogEvent timePickerDialogEvent { nullptr, nullptr, nullptr, nullptr };
    TimePickerDialogAppearEvent(runtimeCallInfo, timePickerDialogEvent);
    TimePickerDialogDisappearEvent(runtimeCallInfo, timePickerDialogEvent);
    GetArkUINodeModifiers()->getTimepickerModifier()->show(reinterpret_cast<void*>(&pickerDialog),
        reinterpret_cast<void*>(&settingData), reinterpret_cast<void*>(&cancelEvent),
        reinterpret_cast<void*>(&acceptEvent), reinterpret_cast<void*>(&changeEvent),
        reinterpret_cast<void*>(&enterEvent), reinterpret_cast<void*>(&timePickerDialogEvent),
        reinterpret_cast<void*>(&buttonInfos));
    return panda::NativePointerRef::New(vm, nullptr);
}
} // namespace OHOS::Ace::NG
