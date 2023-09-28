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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTCONTROLLER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTCONTROLLER_H

#include "bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace::Framework {
class JSTextController final : public Referenced {
public:
    JSTextController() = default;
    ~JSTextController() override = default;

    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSTextController* scroller);
    void CaretPosition(int32_t caretPosition);
    void SetTextSelection(int32_t selectionStart, int32_t selectionEnd);
    void StopEditing();
    void SetController(const RefPtr<TextFieldControllerBase>& controller)
    {
        controllerWeak_ = controller;
    }

    void GetTextContentRect(const JSCallbackInfo& info);
    void GetTextContentLinesNum(const JSCallbackInfo& info);
private:
    JSRef<JSObject> CreateRectangle(const Rect& info);

    WeakPtr<TextFieldControllerBase> controllerWeak_;
    ACE_DISALLOW_COPY_AND_MOVE(JSTextController);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTCONTROLLER_H