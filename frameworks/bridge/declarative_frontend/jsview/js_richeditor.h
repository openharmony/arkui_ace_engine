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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RICHEDITOR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RICHEDITOR_H

#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {
class JSRichEditor : public JSContainerBase {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void SetOnReady(const JSCallbackInfo& args);
    static void SetOnSelect(const JSCallbackInfo& args);
    static JSRef<JSVal> CreateJSSelection(const RichEditorSelection& selectInfo);
    static JSRef<JSObject> CreateJSSpanResultObject(const ResultObject& resultObject);
    static JSRef<JSObject> CreateJSTextStyleResult(const TextStyleResult& textStyleResult);
    static JSRef<JSObject> CreateJSImageStyleResult(const ImageStyleResult& imageStyleResult);
};

class JSRichEditorController final : public Referenced {
public:
    JSRichEditorController() = default;
    ~JSRichEditorController() override = default;

    static void JSBind(BindingTarget globalObj);

    static void Constructor(const JSCallbackInfo& args)
    {
        auto controller = Referenced::MakeRefPtr<JSRichEditorController>();
        controller->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(controller));
    }

    static void Destructor(JSRichEditorController* controller)
    {
        if (controller != nullptr) {
            controller->DecRefCount();
        }
    }

    void SetController(const RefPtr<RichEditorControllerBase>& controller)
    {
        controllerWeak_ = controller;
    }
    void AddImageSpan(const JSCallbackInfo& args);
    void AddTextSpan(const JSCallbackInfo& args);
    void DeleteSpans(const JSCallbackInfo& args);
    ImageSpanAttribute ParseJsImageSpanAttribute(JSRef<JSObject> imageAttribute);
    TextStyle ParseJsTextStyle(JSRef<JSObject> styleObject);
    void SetCaretOffset(const JSCallbackInfo& args);
    void GetCaretOffset(const JSCallbackInfo& args);
    void UpdateSpanStyle(const JSCallbackInfo& info);
    void GetSpansInfo(const JSCallbackInfo& args);
    JSRef<JSVal> CreateCreateJSSpansInfo(const RichEditorSelection& info);

private:
    WeakPtr<RichEditorControllerBase> controllerWeak_;
    ACE_DISALLOW_COPY_AND_MOVE(JSRichEditorController);
    struct UpdateSpanStyle updateSpanStyle_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RICHEDITOR_H
