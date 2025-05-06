/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text_editable_controller.h"
#include "frameworks/core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace::Framework {

void JSTextEditableController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextEditableController>::Method("caretPosition", &JSTextEditableController::CaretPosition);
    JSClass<JSTextEditableController>::CustomMethod("getCaretOffset", &JSTextEditableController::GetCaretOffset);
    JSClass<JSTextEditableController>::CustomMethod("setTextSelection", &JSTextEditableController::SetTextSelection);
    JSClass<JSTextEditableController>::CustomMethod("showPassword", &JSTextEditableController::ShowPassword);
    JSClass<JSTextEditableController>::CustomMethod("hidePassword", &JSTextEditableController::HidePassword);
    JSClass<JSTextEditableController>::CustomMethod(
        "getTextContentRect", &JSTextEditableController::GetTextContentRect);
    JSClass<JSTextEditableController>::CustomMethod(
        "getTextContentLineCount", &JSTextEditableController::GetTextContentLinesNum);
    JSClass<JSTextEditableController>::CustomMethod("addText", &JSTextEditableController::AddText);
    JSClass<JSTextEditableController>::CustomMethod("deleteText", &JSTextEditableController::DeleteText);
    JSClass<JSTextEditableController>::CustomMethod("getSelection", &JSTextEditableController::GetSelection);
    JSClass<JSTextEditableController>::CustomMethod("clearPreviewText", &JSTextEditableController::ClearPreviewText);
    JSClass<JSTextEditableController>::CustomMethod("getText", &JSTextEditableController::GetText);
    JSClass<JSTextEditableController>::Method("stopEditing", &JSTextEditableController::StopEditing);
    JSClass<JSTextEditableController>::Bind(
        globalObj, JSTextEditableController::Constructor, JSTextEditableController::Destructor);
}

void JSTextEditableController::Constructor(const JSCallbackInfo& args)
{
    auto controller = Referenced::MakeRefPtr<JSTextEditableController>();
    controller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(controller));
}

void JSTextEditableController::Destructor(JSTextEditableController* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}

void JSTextEditableController::CaretPosition(int32_t caretPosition)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            caretPosition = caretPosition < 0 ? 0 : caretPosition;
        } else {
            // do nothing
        }
        controller->CaretPosition(caretPosition);
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "CaretPosition: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::ShowPassword(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->SetPasswordState(false);
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "ShowPassword: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::HidePassword(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->SetPasswordState(true);
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "HidePassword: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::SetTextSelection(const JSCallbackInfo& info)
{
    if (info.Length() < 2) { /* 2:args number */
        return;
    }
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        const auto& start = info[0];
        const auto& end = info[1];
        std::optional<SelectionOptions> options = std::nullopt;
        if (!start->IsNumber() || !end->IsNumber()) {
            TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "SetTextSelection: The selectionStart or selectionEnd is NULL");
        }
        int32_t selectionStart = start->ToNumber<int32_t>();
        int32_t selectionEnd = end->ToNumber<int32_t>();

        if (info.Length() == 3 && info[2]->IsObject()) { /* 2, 3:args number */
            SelectionOptions optionTemp;
            JSRef<JSObject> optionsObj = JSRef<JSObject>::Cast(info[2]); /* 2:args number */
            JSRef<JSVal> menuPolicy = optionsObj->GetProperty("menuPolicy");
            int32_t tempPolicy = 0;
            if (!menuPolicy->IsNull() && JSContainerBase::ParseJsInt32(menuPolicy, tempPolicy)) {
                optionTemp.menuPolicy = static_cast<MenuPolicy>(tempPolicy);
                options = optionTemp;
            }
        } else {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "SetTextSelection: The selectionOption is null");
        }
        controller->SetTextSelection(selectionStart, selectionEnd, options);
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "SetTextSelection: The JSTextEditableController is NULL");
    }
}

JSRef<JSObject> JSTextEditableController::CreateRectangle(const Rect& info)
{
    JSRef<JSObject> rectObj = JSRef<JSObject>::New();
    rectObj->SetProperty<double>("x", info.Left());
    rectObj->SetProperty<double>("y", info.Top());
    rectObj->SetProperty<double>("width", info.Width());
    rectObj->SetProperty<double>("height", info.Height());
    return rectObj;
}

void JSTextEditableController::GetTextContentRect(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        auto rectObj = CreateRectangle(controller->GetTextContentRect());
        JSRef<JSVal> rect = JSRef<JSObject>::Cast(rectObj);
        info.SetReturnValue(rect);
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "GetTextContentRect: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::GetTextContentLinesNum(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        auto lines = controller->GetTextContentLinesNum();
        auto linesNum = JSVal(ToJSValue(lines));
        auto textLines = JSRef<JSVal>::Make(linesNum);
        info.SetReturnValue(textLines);
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "GetTextContentLinesNum: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::AddText(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        const auto& text = info[0];
        const auto& options = info[1];
        std::u16string textValue;
        if (text->IsString()) {
            textValue = text->ToU16String();
        } else {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "AddText: The text is null");
            auto returnValue = JSVal(ToJSValue(controller->GetCaretIndex()));
            info.SetReturnValue(JSRef<JSVal>::Make(returnValue));
            return;
        }
        int32_t offsetIndex = -1;
        if (options->IsObject()) {
            JSRef<JSObject> optionObj = JSRef<JSObject>::Cast(options);
            JSRef<JSVal> offset = optionObj->GetProperty("offset");
            if (offset->IsNumber()) {
                offsetIndex = offset->ToNumber<int32_t>();
                offsetIndex = std::max(0, offsetIndex);
            }
        }
        // add text
        int32_t result = controller->AddText(textValue, offsetIndex);
        auto returnValue = JSVal(ToJSValue(result));
        info.SetReturnValue(JSRef<JSVal>::Make(returnValue));
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "AddText: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::DeleteText(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        const auto& textRange = info[0];
        if (!textRange->IsObject()) {
            controller->DeleteText(-1, -1);
            return;
        }
        JSRef<JSObject> rangeObj = JSRef<JSObject>::Cast(textRange);

        int32_t startIndex = -1;
        int32_t endIndex = -1;
        JSRef<JSVal> start = rangeObj->GetProperty("start");
        if (start->IsNumber()) {
            startIndex = start->ToNumber<int32_t>();
            startIndex = startIndex < 0 ? 0 : startIndex;
        }
        JSRef<JSVal> end = rangeObj->GetProperty("end");
        if (end->IsNumber()) {
            endIndex = end->ToNumber<int32_t>();
            endIndex = endIndex < 0 ? -1 : endIndex;
        }
        controller->DeleteText(startIndex, endIndex);
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "DeleteText: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::GetSelection(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        SelectionInfo selectInfo = controller->GetSelection();
        JSRef<JSObject> selectionObject = JSRef<JSObject>::New();
        selectionObject->SetPropertyObject("start",
            JSRef<JSVal>::Make(ToJSValue(selectInfo.GetSelection().selection[0])));
        selectionObject->SetPropertyObject("end",
            JSRef<JSVal>::Make(ToJSValue(selectInfo.GetSelection().selection[1])));
        info.SetReturnValue(JSRef<JSVal>::Cast(selectionObject));
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "GetSelection: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::GetCaretOffset(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        JSRef<JSObject> caretObj = JSRef<JSObject>::New();
        NG::OffsetF caretOffset = controller->GetCaretPosition();
        caretObj->SetProperty<int32_t>("index", controller->GetCaretIndex());
        caretObj->SetProperty<float>("x", caretOffset.GetX());
        caretObj->SetProperty<float>("y", caretOffset.GetY());
        JSRef<JSVal> ret = JSRef<JSObject>::Cast(caretObj);
        info.SetReturnValue(ret);
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "GetCaretOffset: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::ClearPreviewText(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->ClearPreviewText();
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "ClearPreviewText: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::GetText(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        std::u16string content = controller->GetText();
        const auto& textRange = info[0];
        int32_t startIndex = 0;
        int32_t endIndex = static_cast<int32_t>(content.length());
        if (textRange->IsObject()) {
            JSRef<JSObject> rangeObj = JSRef<JSObject>::Cast(textRange);
            JSRef<JSVal> start = rangeObj->GetProperty("start");
            if (start->IsNumber()) {
                startIndex = start->ToNumber<int32_t>();
                startIndex = startIndex < 0 ? 0 : startIndex;
                startIndex = std::clamp(startIndex, 0, static_cast<int32_t>(content.length()));
            }
            JSRef<JSVal> end = rangeObj->GetProperty("end");
            if (end->IsNumber()) {
                endIndex = end->ToNumber<int32_t>();
                endIndex = endIndex < 0 ? static_cast<int32_t>(content.length()) : endIndex;
                endIndex = std::clamp(endIndex, 0, static_cast<int32_t>(content.length()));
            }
            if (startIndex > endIndex) {
                std::swap(startIndex, endIndex);
            }
        }
        std::u16string result = content.substr(startIndex, endIndex - startIndex);
        auto returnValue = JSVal(ToJSValue(result));
        info.SetReturnValue(JSRef<JSVal>::Make(returnValue));
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "GetText: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::StopEditing()
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->StopEditing();
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "StopEditing: The JSTextEditableController is NULL");
    }
}
} // namespace OHOS::Ace::Framework
