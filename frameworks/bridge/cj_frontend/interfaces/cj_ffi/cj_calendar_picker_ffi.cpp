/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_calendar_picker_ffi.h"

#include "cj_lambda.h"

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "bridge/common/utils/utils.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {

void SetRadius(NG::BorderRadiusProperty& dialogRadius, const Dimension& borderRadius)
{
#ifndef ARKUI_WEARABLE
    dialogRadius.radiusTopLeft = borderRadius;
    dialogRadius.radiusTopRight = borderRadius;
    dialogRadius.radiusBottomLeft = borderRadius;
    dialogRadius.radiusBottomRight = borderRadius;
#endif
}

PickerDate ParseDate(const FfiTime& date)
{
#ifndef ARKUI_WEARABLE
    auto pickerDate = PickerDate();
    pickerDate.SetYear(date.year);
    pickerDate.SetMonth(date.month);
    pickerDate.SetDay(date.day);
    return pickerDate;
#else
    return PickerDate();
#endif
}

NG::BorderRadiusProperty ParseNativeBorderRadiuses(const NativeBorderRadiuses& nativeBorderRadiuses)
{
#ifndef ARKUI_WEARABLE
    NG::BorderRadiusProperty radius;
    CalcDimension topLeft(
        nativeBorderRadiuses.topLeftRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.topLeftUnit));
    CalcDimension topRight(
        nativeBorderRadiuses.topRightRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.topRightUnit));
    CalcDimension bottomLeft(
        nativeBorderRadiuses.bottomLeftRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.bottomLeftUnit));
    CalcDimension bottomRight(
        nativeBorderRadiuses.bottomRightRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.bottomRightUnit));
    radius.radiusTopLeft = topLeft;
    radius.radiusTopRight = topRight;
    radius.radiusBottomLeft = bottomLeft;
    radius.radiusBottomRight = bottomRight;
    radius.multiValued = true;
    return radius;
#else
    return NG::BorderRadiusProperty();
#endif
}

Shadow ParseNativeShadowOptions(NativeShadowOptions shadowOptions)
{
#ifndef ARKUI_WEARABLE
    Shadow shadow;
    if (LessNotEqual(shadowOptions.radius, 0.0)) {
        shadowOptions.radius = 0.0;
    }
    shadow.SetBlurRadius(shadowOptions.radius);
    Color shadowColor = Color(shadowOptions.color);
    shadow.SetColor(shadowColor);
    shadow.SetShadowType(static_cast<ShadowType>(shadowOptions.shadowType));
    shadow.SetIsFilled(shadowOptions.fill);
    shadow.SetOffsetX(shadowOptions.offsetX);
    shadow.SetOffsetY(shadowOptions.offsetY);
    return shadow;
#else
    return Shadow();
#endif
}

FfiTime GetFfiTime(const std::string& date)
{
#ifndef ARKUI_WEARABLE
    auto json = JsonUtil::ParseJsonString(date);
    if (!json || json->IsNull()) {
        return FfiTime();
    }

    FfiTime dateTime {};
    auto year = json->GetValue("year");
    if (year && year->IsNumber()) {
        dateTime.year = year->GetInt(); // local date start from 1900
    }
    auto month = json->GetValue("month");
    if (month && month->IsNumber()) {
        dateTime.month = month->GetInt();
    }
    auto day = json->GetValue("day");
    if (day && day->IsNumber()) {
        dateTime.day = day->GetInt();
    }
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto local = std::localtime(&now);
    if (!local) {
        dateTime.hour = 0;
        dateTime.min = 0;
        dateTime.sec = 0;
    } else {
        dateTime.hour = local->tm_hour;
        dateTime.min = local->tm_min;
        dateTime.sec = local->tm_sec;
    }
    return dateTime;
#else
    return FfiTime();
#endif
}

void ParseFontOfButtonStyle(const NativePickerDialogButtonStyle& buttonStyle, ButtonInfo& buttonInfo)
{
#ifndef ARKUI_WEARABLE
    if (buttonStyle.fontSize.hasValue) {
        CalcDimension fontSize =
            CalcDimension(buttonStyle.fontSize.value.value, DimensionUnit(buttonStyle.fontSize.value.unitType));
        if (fontSize.Unit() != DimensionUnit::PERCENT && GreatNotEqual(fontSize.Value(), 0.0)) {
            buttonInfo.fontSize = fontSize;
        }
    }
    if (buttonStyle.fontColor.hasValue) {
        buttonInfo.fontColor = Color(buttonStyle.fontColor.value);
    }
    if (buttonStyle.fontStyle.hasValue) {
        buttonInfo.fontWeight = ConvertStrToFontWeight(buttonStyle.fontWeight.value);
    }
    if (buttonStyle.fontStyle.hasValue) {
        auto style = buttonStyle.fontStyle.value;
        if (style >= 0 && style < static_cast<int32_t>(FontStyle::NONE)) {
            buttonInfo.fontStyle = static_cast<FontStyle>(style);
        }
    }
    if (buttonStyle.fontFamily.hasValue) {
        buttonInfo.fontFamily = ConvertStrToFontFamilies(buttonStyle.fontFamily.value);
    }
#endif
}

void AppearDialogEvent(
    const NativeCalendarDialogOptions& options, std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent)
{
#ifndef ARKUI_WEARABLE
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (options.onDidAppear.hasValue) {
        auto didAppearId = [func = CJLambda::Create(options.onDidAppear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
        dialogLifeCycleEvent["didAppearId"] = didAppearId;
    }

    if (options.onWillAppear.hasValue) {
        auto willAppearId = [func = CJLambda::Create(options.onWillAppear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
        dialogLifeCycleEvent["willAppearId"] = willAppearId;
    }
#endif
}

void DisappearDialogEvent(
    const NativeCalendarDialogOptions& options, std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent)
{
#ifndef ARKUI_WEARABLE
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (options.onDidDisappear.hasValue) {
        auto didDisappearId = [func = CJLambda::Create(options.onDidDisappear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
        dialogLifeCycleEvent["didDisappearId"] = didDisappearId;
    }

    if (options.onWillDisappear.hasValue) {
        auto willDisappearId = [func = CJLambda::Create(options.onWillDisappear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
        dialogLifeCycleEvent["willDisappearId"] = willDisappearId;
    }
#endif
}

ButtonInfo ParseButtonStyle(const NativePickerDialogButtonStyle& buttonStyle)
{
#ifndef ARKUI_WEARABLE
    ButtonInfo buttonInfo;
    if (buttonStyle.type.hasValue) {
        int32_t buttonTypeIntValue = buttonStyle.type.value;
        if (buttonTypeIntValue == static_cast<int32_t>(ButtonType::CAPSULE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::CIRCLE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ARC) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::NORMAL) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ROUNDED_RECTANGLE)) {
            buttonInfo.type = static_cast<ButtonType>(buttonTypeIntValue);
        }
    }
    if (buttonStyle.style.hasValue) {
        int32_t styleModeIntValue = buttonStyle.style.value;
        if (styleModeIntValue >= static_cast<int32_t>(ButtonStyleMode::NORMAL) &&
            styleModeIntValue <= static_cast<int32_t>(ButtonStyleMode::TEXT)) {
            buttonInfo.buttonStyle = static_cast<ButtonStyleMode>(styleModeIntValue);
        }
    }
    if (buttonStyle.role.hasValue) {
        int32_t buttonRoleIntValue = buttonStyle.style.value;
        if (buttonRoleIntValue >= static_cast<int32_t>(ButtonRole::NORMAL) &&
            buttonRoleIntValue <= static_cast<int32_t>(ButtonRole::ERROR)) {
            buttonInfo.role = static_cast<ButtonRole>(buttonRoleIntValue);
        }
    }
    ParseFontOfButtonStyle(buttonStyle, buttonInfo);
    if (buttonStyle.backgroundColor.hasValue) {
        buttonInfo.backgroundColor = Color(buttonStyle.backgroundColor.value);
    }
    if (buttonStyle.borderRadius.hasValue) {
        buttonInfo.borderRadius = ParseNativeBorderRadiuses(buttonStyle.borderRadius.value);
    }
    if (buttonStyle.primary.hasValue) {
        buttonInfo.isPrimary = buttonStyle.primary.value;
    }
    return buttonInfo;
#else
    return ButtonInfo();
#endif
}

std::vector<ButtonInfo> ParseButtonStyles(const NativeCalendarDialogOptions& options)
{
#ifndef ARKUI_WEARABLE
    std::vector<ButtonInfo> buttonInfos;
    if (options.acceptButtonStyle.hasValue) {
        buttonInfos.emplace_back(ParseButtonStyle(options.acceptButtonStyle.value));
        buttonInfos[0].isAcceptButton = true;
    } else {
        buttonInfos.emplace_back(ButtonInfo());
    }
    if (options.cancelButtonStyle.hasValue) {
        buttonInfos.emplace_back(ParseButtonStyle(options.cancelButtonStyle.value));
    }
    return buttonInfos;
#else
    return {};
#endif
}

std::map<std::string, NG::DialogEvent> ChangeDialogEvent(const NativeCalendarDialogOptions& options)
{
#ifndef ARKUI_WEARABLE
    std::map<std::string, NG::DialogEvent> dialogEvent;
    if (options.onChange.hasValue) {
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto changeId = [func = CJLambda::Create(options.onChange.value), node = targetNode](const std::string& info) {
            PipelineContext::SetCallBackNode(node);
            auto date = GetFfiTime(info);
            func(date);
        };
        dialogEvent["changeId"] = changeId;
    }
    if (options.onAccept.hasValue) {
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto acceptId = [func = CJLambda::Create(options.onAccept.value), node = targetNode](const std::string& info) {
            PipelineContext::SetCallBackNode(node);
            auto date = GetFfiTime(info);
            func(date);
        };
        dialogEvent["acceptId"] = acceptId;
    }
    return dialogEvent;
#else
    return {};
#endif
}

std::map<std::string, NG::DialogGestureEvent> DialogCancelEvent(const NativeCalendarDialogOptions& options)
{
#ifndef ARKUI_WEARABLE
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    if (options.onCancel.hasValue) {
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto cancelId = [func = CJLambda::Create(options.onCancel.value), node = targetNode](
                            const GestureEvent& /*info*/) {
            PipelineContext::SetCallBackNode(node);
            func();
        };
        dialogCancelEvent["cancelId"] = cancelId;
    }
    return dialogCancelEvent;
#else
    return {};
#endif
}

std::map<std::string, NG::DialogCancelEvent> LifeCycleDialogEvent(const NativeCalendarDialogOptions& options)
{
#ifndef ARKUI_WEARABLE
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    AppearDialogEvent(options, dialogLifeCycleEvent);
    DisappearDialogEvent(options, dialogLifeCycleEvent);
    return dialogLifeCycleEvent;
#else
    return {};
#endif
}

void CalendarPickerDialogShow(const NativeCalendarDialogOptions& options,
    const std::map<std::string, NG::DialogEvent>& dialogEvent,
    const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent,
    const std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent,
    const std::vector<ButtonInfo>& buttonInfos)
{
#ifndef ARKUI_WEARABLE
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);

    auto theme = GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    auto calendarTheme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    NG::CalendarSettingData settingData;
    auto parseSelectedDate = ParseDate(options.selected);
    if (parseSelectedDate.GetYear() != 0) {
        settingData.selectedDate = parseSelectedDate;
    }
    settingData.dayRadius = CalcDimension(options.hintRadius.value, DimensionUnit(options.hintRadius.unitType));

    DialogProperties properties;
    properties.alignment = DialogAlignment::CENTER;
    properties.backgroundColor = Color(options.backgroundColor);
    if (options.backgroundBlurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        options.backgroundBlurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        properties.backgroundBlurStyle = options.backgroundBlurStyle;
    }

    if (options.shadow.hasValue) {
        properties.shadow = ParseNativeShadowOptions(options.shadow.value);
    }

    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    NG::BorderRadiusProperty dialogRadius;
    SetRadius(dialogRadius, calendarTheme->GetDialogBorderRadius());
    properties.borderRadius = dialogRadius;
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    auto weak = WeakPtr<NG::OverlayManager>(overlayManager);
    auto overlayManager_ = weak.Upgrade();
    CHECK_NULL_VOID(overlayManager_);
    overlayManager_->ShowCalendarDialog(
        properties, settingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos);
#endif
}

#ifndef ARKUI_WEARABLE
NG::CalendarPickerModelNG* GetCalendarPickerModel()
{
    static NG::CalendarPickerModelNG* cachedModel = nullptr;
    if (!cachedModel) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("CalendarPicker");
        if (module == nullptr) {
            LOGF("Can't find calendarPicker dynamic module");
            abort();
        }
        cachedModel = reinterpret_cast<NG::CalendarPickerModelNG*>(module->GetModel());
    }
    return cachedModel;
}
#endif
} // namespace

extern "C" {
void FfiOHOSAceFrameworkCalendarPickerCreate(double size, int32_t unit, FfiTime date)
{
#ifndef ARKUI_WEARABLE
    NG::CalendarSettingData settingData;
    CalcDimension dayRadius = { size, DimensionUnit(unit) };
    settingData.selectedDate = ParseDate(date);
    settingData.dayRadius = dayRadius;
    GetCalendarPickerModel()->Create(settingData);
#endif
}

void FfiOHOSAceFrameworkCalendarPickerSetEdgeAlign(int32_t alignType, NativeOffset offset)
{
#ifndef ARKUI_WEARABLE
    NG::CalendarEdgeAlign alignType_ = static_cast<NG::CalendarEdgeAlign>(alignType);
    CalcDimension dx = CalcDimension(offset.dx.value, DimensionUnit(offset.dx.unitType));
    CalcDimension dy = CalcDimension(offset.dy.value, DimensionUnit(offset.dy.unitType));
    DimensionOffset offset_ = DimensionOffset(dx, dy);
    GetCalendarPickerModel()->SetEdgeAlign(alignType_, offset_);
#endif
}

void FfiOHOSAceFrameworkCalendarPickerSetTextStyle(
    uint32_t color, NativeLength size, const char* weight, const char* family, uint32_t style)
{
#ifndef ARKUI_WEARABLE
    NG::PickerTextStyle textStyle;
    textStyle.textColor = Color(color);
    CalcDimension fontSize = CalcDimension(size.value, DimensionUnit(size.unitType));
    textStyle.fontSize = fontSize;
    textStyle.fontWeight = ConvertStrToFontWeight(weight);
    textStyle.fontFamily = ConvertStrToFontFamilies(family);
    GetCalendarPickerModel()->SetTextStyle(textStyle);
#endif
}

void FfiOHOSAceFrameworkCalendarPickerSetOnChange(void (*callback)(FfiTime))
{
#ifndef ARKUI_WEARABLE
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [func = CJLambda::Create(callback), node = targetNode](const std::string& info) -> void {
        PipelineContext::SetCallBackNode(node);
        auto time = GetFfiTime(info);
        func(time);
    };
    GetCalendarPickerModel()->SetOnChange(std::move(onChange));
#endif
}

void FfiOHOSAceFrameworkCalendarPickerDialogShow(NativeCalendarDialogOptions options)
{
#ifndef ARKUI_WEARABLE
    if (Container::IsCurrentUseNewPipeline()) {
        auto buttonInfos = ParseButtonStyles(options);
        auto dialogEvent = ChangeDialogEvent(options);
        auto dialogCancelEvent = DialogCancelEvent(options);
        auto dialogLifeCycleEvent = LifeCycleDialogEvent(options);
        CalendarPickerDialogShow(options, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos);
    }
#endif
}
}