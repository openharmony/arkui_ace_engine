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

class JSTextPickerParser : public JSViewAbstract {
public:
    static bool ParseIconTextArray(const JSRef<JSObject>& paramObject, std::vector<NG::RangeContent>& result,
        uint32_t& kind, uint32_t& selected);
    static bool ParseTextArray(const JSRef<JSObject>& paramObject, std::vector<NG::RangeContent>& result,
        uint32_t& kind, uint32_t& selected, std::string& value);
    static void ParseTextStyle(const JSRef<JSObject>& paramObj, NG::PickerTextStyle& textStyle);
};

class JSTextPicker : public JSViewAbstract {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);

    static void SetDefaultPickerItemHeight(const JSCallbackInfo& info);

    static void OnAccept(const JSCallbackInfo& info);
    static void OnCancel(const JSCallbackInfo& info);
    static void OnChange(const JSCallbackInfo& info);
    static void SetDisappearTextStyle(const JSCallbackInfo& info);
    static void SetTextStyle(const JSCallbackInfo& info);
    static void SetSelectedTextStyle(const JSCallbackInfo& info);
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
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTPICKER_H