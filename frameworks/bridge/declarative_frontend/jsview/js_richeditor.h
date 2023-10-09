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

#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {
class JSRichEditor : public JSContainerBase {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void SetOnReady(const JSCallbackInfo& args);
    static void SetOnSelect(const JSCallbackInfo& args);
    static void SetAboutToIMEInput(const JSCallbackInfo& args);
    static void SetOnIMEInputComplete(const JSCallbackInfo& args);
    static void SetAboutToDelete(const JSCallbackInfo& args);
    static void SetOnDeleteComplete(const JSCallbackInfo& args);
    static void SetCustomKeyboard(const JSCallbackInfo& args);
    static JSRef<JSVal> CreateJsAboutToIMEInputObj(const NG::RichEditorInsertValue& insertValue);
    static JSRef<JSVal> CreateJsOnIMEInputComplete(const NG::RichEditorAbstractSpanResult& textSpanResult);
    static JSRef<JSVal> CreateJsAboutToDelet(const NG::RichEditorDeleteValue& deleteValue);
    static void JsFocusable(const JSCallbackInfo& info);
    static void SetCopyOptions(const JSCallbackInfo& info);
    static void BindSelectionMenu(const JSCallbackInfo& info);
    static void SetOnPaste(const JSCallbackInfo& info);
    static JSRef<JSVal> CreateJSTextCommonEvent(NG::TextCommonEvent& event);
    static JSRef<JSObject> CreateJSSpanResultObject(const ResultObject& resultObject);
    static JSRef<JSVal> CreateJSSelection(const RichEditorSelection& selectInfo);
    static JSRef<JSObject> CreateJSTextStyleResult(const TextStyleResult& textStyleResult);
    static JSRef<JSObject> CreateJSImageStyleResult(const ImageStyleResult& imageStyleResult);
    static JSRef<JSObject> CreateParagraphStyleResult(const ParagraphInfo& info);

private:
    static void CreateTextStyleObj(JSRef<JSObject>& textStyleObj, const NG::RichEditorAbstractSpanResult& spanResult);
    static void CreateImageStyleObj(JSRef<JSObject>& imageStyleObj, JSRef<JSObject>& spanResultObj,
        const NG::RichEditorAbstractSpanResult& spanResult);
    static void ParseMenuParam(
        const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, SelectMenuParam& menuParam);
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
    TextStyle ParseJsTextStyle(JSRef<JSObject> styleObject, struct UpdateSpanStyle& updateSpanStyle);
    ImageSpanOptions CreateJsImageOptions(const JSCallbackInfo& args);
    void SetCaretOffset(const JSCallbackInfo& args);
    void GetCaretOffset(const JSCallbackInfo& args);
    void UpdateSpanStyle(const JSCallbackInfo& info);
    void UpdateParagraphStyle(const JSCallbackInfo& info);
    void GetSpansInfo(const JSCallbackInfo& args);
    void GetParagraphsInfo(const JSCallbackInfo& args);
    void SetTypingStyle(const JSCallbackInfo& info);
    void CloseSelectionMenu();

private:
    bool ParseParagraphStyle(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
    bool IsPixelMap(const JSRef<JSVal>& jsValue);
    bool IsDrawable(const JSRef<JSVal>& jsValue);
    void ParseTextDecoration(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);

    static JSRef<JSVal> CreateJSSpansInfo(const RichEditorSelection& info);
    static JSRef<JSVal> CreateJSParagraphsInfo(const std::vector<ParagraphInfo>& info);

    WeakPtr<RichEditorControllerBase> controllerWeak_;
    ACE_DISALLOW_COPY_AND_MOVE(JSRichEditorController);
    struct UpdateSpanStyle updateSpanStyle_;
    struct UpdateSpanStyle typingStyle_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RICHEDITOR_H
