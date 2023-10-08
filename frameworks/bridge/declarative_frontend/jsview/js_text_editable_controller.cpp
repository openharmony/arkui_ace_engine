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

#include "frameworks/bridge/declarative_frontend/jsview/js_text_editable_controller.h"

namespace OHOS::Ace::Framework {
void JSTextEditableController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextEditableController>::Declare("TextController");
    JSClass<JSTextEditableController>::Method("caretPosition", &JSTextEditableController::CaretPosition);
    JSClass<JSTextEditableController>::Method("setTextSelection", &JSTextEditableController::SetTextSelection);
    JSClass<JSTextEditableController>::CustomMethod("getTextContentRect", &JSTextEditableController::GetTextContentRect);
    JSClass<JSTextEditableController>::CustomMethod("getTextContentLineCount",
        &JSTextEditableController::GetTextContentLinesNum);
    JSClass<JSTextEditableController>::Method("stopEditing", &JSTextEditableController::StopEditing);
    JSClass<JSTextEditableController>::Bind(globalObj, JSTextEditableController::Constructor, JSTextEditableController::Destructor);
}

void JSTextEditableController::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSTextEditableController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSTextEditableController::Destructor(JSTextEditableController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSTextEditableController::CaretPosition(int32_t caretPosition)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->CaretPosition(caretPosition);
    }
}

void JSTextEditableController::SetTextSelection(int32_t selectionStart, int32_t selectionEnd)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->SetTextSelection(selectionStart, selectionEnd);
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
        LOGE("GetTextContentRect: The JSTextEditableController is NULL");
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
        LOGE("GetTextContentRect: The JSTextEditableController is NULL");
    }
}

void JSTextEditableController::StopEditing()
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->StopEditing();
    }
}
} // namespace OHOS::Ace::Framework