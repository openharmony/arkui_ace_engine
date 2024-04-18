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
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "CaretPosition: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::ShowPassword(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "begin to show password");
        controller->SetPasswordState(false);
    } else {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "ShowPassword: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::HidePassword(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "begin to hide password");
        controller->SetPasswordState(true);
    } else {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HidePassword: The JSTextEditableController is NULL");
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
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "SetTextSelection: The selectionStart or selectionEnd is NULL");
        }
        int32_t selectionStart = start->ToNumber<int32_t>();
        int32_t selectionEnd = end->ToNumber<int32_t>();

        if (info.Length() == 3 && info[2]->IsObject()) { /* 2, 3:args number */
            SelectionOptions optionTemp;
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "SetTextSelection: The selectionOption is set");
            JSRef<JSObject> optionsObj = JSRef<JSObject>::Cast(info[2]); /* 2:args number */
            JSRef<JSVal> menuPolicy = optionsObj->GetProperty("menuPolicy");
            int32_t tempPolicy = 0;
            if (!menuPolicy->IsNull() && JSContainerBase::ParseJsInt32(menuPolicy, tempPolicy)) {
                optionTemp.menuPolicy = static_cast<MenuPolicy>(tempPolicy);
                options = optionTemp;
            }
        }
        controller->SetTextSelection(selectionStart, selectionEnd, options);
    } else {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "SetTextSelection: The JSTextEditableController is NULL");
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
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "GetTextContentRect: The JSTextEditableController is NULL");
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
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "GetTextContentLinesNum: The JSTextEditableController is NULL");
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
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "GetCaretOffset: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::StopEditing()
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->StopEditing();
    } else {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "StopEditing: The JSTextEditableController is NULL");
    }
}
} // namespace OHOS::Ace::Framework
