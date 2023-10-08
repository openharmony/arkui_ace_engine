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

#include "frameworks/bridge/declarative_frontend/jsview/js_text_controller.h"

namespace OHOS::Ace::Framework {
void JSTextController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextController>::Declare("TextController");
    JSClass<JSTextController>::Method("caretPosition", &JSTextController::CaretPosition);
    JSClass<JSTextController>::Method("setTextSelection", &JSTextController::SetTextSelection);
    JSClass<JSTextController>::CustomMethod("getTextContentRect", &JSTextController::GetTextContentRect);
    JSClass<JSTextController>::CustomMethod("getTextContentLineCount",
        &JSTextController::GetTextContentLinesNum);
    JSClass<JSTextController>::Method("stopEditing", &JSTextController::StopEditing);
    JSClass<JSTextController>::Bind(globalObj, JSTextController::Constructor, JSTextController::Destructor);
}

void JSTextController::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSTextController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSTextController::Destructor(JSTextController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSTextController::CaretPosition(int32_t caretPosition)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->CaretPosition(caretPosition);
    }
}

void JSTextController::SetTextSelection(int32_t selectionStart, int32_t selectionEnd)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->SetTextSelection(selectionStart, selectionEnd);
    }
}

JSRef<JSObject> JSTextController::CreateRectangle(const Rect& info)
{
    JSRef<JSObject> rectObj = JSRef<JSObject>::New();
    rectObj->SetProperty<double>("x", info.Left());
    rectObj->SetProperty<double>("y", info.Top());
    rectObj->SetProperty<double>("width", info.Width());
    rectObj->SetProperty<double>("height", info.Height());
    return rectObj;
}

void JSTextController::GetTextContentRect(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        auto rectObj = CreateRectangle(controller->GetTextContentRect());
        JSRef<JSVal> rect = JSRef<JSObject>::Cast(rectObj);
        info.SetReturnValue(rect);
    } else {
        LOGE("GetTextContentRect: The JSTextController is NULL");
    }
}

void JSTextController::GetTextContentLinesNum(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        auto lines = controller->GetTextContentLinesNum();
        auto linesNum = JSVal(ToJSValue(lines));
        auto textLines = JSRef<JSVal>::Make(linesNum);
        info.SetReturnValue(textLines);
    } else {
        LOGE("GetTextContentRect: The JSTextController is NULL");
    }
}

void JSTextController::StopEditing()
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->StopEditing();
    }
}
} // namespace OHOS::Ace::Framework