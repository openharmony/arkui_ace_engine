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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CALENDAR_PICKER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CALENDAR_PICKER_H

#include "frameworks/bridge/declarative_frontend/jsview/dialog/js_alert_dialog.h"

namespace OHOS::Ace::Framework {
class JSCalendarPicker : public JSViewAbstract, public JSInteractableView {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);

    static void SetEdgeAlign(const JSCallbackInfo& info);
    static void SetTextStyle(const JSCallbackInfo& info);
    static void SetOnChange(const JSCallbackInfo& info);
    static void SetBorder(const JSCallbackInfo& info);
    static void JsPadding(const JSCallbackInfo& info);
    static void JsHeight(const JSCallbackInfo& info);
    static void JsBorderColor(const JSCallbackInfo& info);
    static void JsBorderRadius(const JSCallbackInfo& info);
    static void JsMarkToday(const JSCallbackInfo& info);

private:
    static void ParseTextStyle(const JSRef<JSObject>& paramObj, NG::PickerTextStyle& textStyle);
    static void ParseSelectedDateObject(const JSCallbackInfo& info, const JSRef<JSObject>& selectedObject);
    static PickerDate ParseDate(const JSRef<JSVal>& dateVal, bool useCurrentDate = true);
    static void ParseCalendarPickerBorderColor(const JSRef<JSVal>& args);
    static NG::PaddingProperty SetPaddings(const std::optional<CalcDimension>& top,
        const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
        const std::optional<CalcDimension>& right);
    static bool ParseJsDimensionVpWithCheck(const JSRef<JSVal>& jsValue, CalcDimension& result);
    static void ParseDisabledDateRange(const JSRef<JSVal>& disabledDateRangeVal, NG::CalendarSettingData& settingData);
};

class JSCalendarPickerDialog : JSAlertDialog {
public:
    static void JSBind(BindingTarget globalObj);
    static void Show(const JSCallbackInfo& info);
    static void CalendarPickerDialogShow(const JSRef<JSObject>& paramObj,
        const std::map<std::string, NG::DialogEvent>& dialogEvent,
        const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent,
        const std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent,
        const std::vector<ButtonInfo>& buttonInfos);

private:
    static std::map<std::string, NG::DialogEvent> ChangeDialogEvent(const JSCallbackInfo& info);
    static std::map<std::string, NG::DialogGestureEvent> DialogCancelEvent(const JSCallbackInfo& info);
    static std::map<std::string, NG::DialogCancelEvent> LifeCycleDialogEvent(const JSCallbackInfo& info);

    static PickerDate ParseDate(const JSRef<JSVal>& dateVal, bool useCurrentDate = false);
    static void ParseDisabledDateRange(const JSRef<JSVal>& disabledDateRangeVal, NG::CalendarSettingData& settingData);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CALENDAR_PICKER_H
