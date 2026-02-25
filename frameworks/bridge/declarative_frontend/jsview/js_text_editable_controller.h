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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_EDITABLE_CONTROLLER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_EDITABLE_CONTROLLER_H

#include "core/components_ng/pattern/text/span/span_string.h"
#include "frameworks/core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace::Framework {
class JSTextEditableController : public Referenced {
public:
    JSTextEditableController() = default;
    ~JSTextEditableController() override = default;

    static void Destructor(JSTextEditableController* scroller);
    void CaretPosition(int32_t caretPosition);
    void StopEditing();

    void SetController(const RefPtr<TextFieldControllerBase>& controller)
    {
        controllerWeak_ = controller;
    }

    ACE_FORCE_EXPORT RefPtr<SpanString> GetPlaceholderStyledString() const;
    ACE_FORCE_EXPORT void ClearPlaceholderStyledString();
    void DeleteBackward();

private:
    friend class JSTextEditableControllerBinding;
    WeakPtr<TextFieldControllerBase> controllerWeak_;
    WeakPtr<SpanString> placeholderStyledString_;
    ACE_DISALLOW_COPY_AND_MOVE(JSTextEditableController);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_EDITABLE_CONTROLLER_H
