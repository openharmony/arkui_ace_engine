/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {
class JSRichEditor : public JSContainerBase {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void SetOnReady(const JSCallbackInfo& args);
    static void SetOnSelect(const JSCallbackInfo& args);
    static void SetOnSelectionChange(const JSCallbackInfo& args);
    static void SetAboutToIMEInput(const JSCallbackInfo& args);
    static void SetOnIMEInputComplete(const JSCallbackInfo& args);
    static void SetOnDidIMEInput(const JSCallbackInfo& args);
    static void SetAboutToDelete(const JSCallbackInfo& args);
    static void SetOnDeleteComplete(const JSCallbackInfo& args);
    static void SetCustomKeyboard(const JSCallbackInfo& args);
    static JSRef<JSVal> CreateJsAboutToIMEInputObj(const NG::RichEditorInsertValue& insertValue);
    static JSRef<JSVal> CreateJsOnIMEInputComplete(const NG::RichEditorAbstractSpanResult& textSpanResult);
    static JSRef<JSVal> CreateJsOnDidIMEInput(const TextRange& textRange);
    static JSRef<JSVal> CreateJsAboutToDelet(const NG::RichEditorDeleteValue& deleteValue);
    static void SetChangeTextSpans(
        JSRef<JSArray>& jsArray, const std::vector<NG::RichEditorAbstractSpanResult>& spanList);
    static JSRef<JSVal> CreateJsOnWillChange(const NG::RichEditorChangeValue& changeValue);
    static JSRef<JSVal> CreateJsOnDidChange(const std::vector<NG::RichEditorAbstractSpanResult>& spanList);
    static void JsClip(const JSCallbackInfo& info);
    static void JsFocusable(const JSCallbackInfo& info);
    static void SetCopyOptions(const JSCallbackInfo& info);
    static void BindSelectionMenu(const JSCallbackInfo& info);
    static void SetOnPaste(const JSCallbackInfo& info);
    static void SetPlaceholder(const JSCallbackInfo& info);
    static void JsEnableDataDetector(const JSCallbackInfo& info);
    static void JsEnablePreviewText(const JSCallbackInfo& info);
    static void JsDataDetectorConfig(const JSCallbackInfo& info);
    static void SetOnWillChange(const JSCallbackInfo& info);
    static void SetOnDidChange(const JSCallbackInfo& info);
    static void SetOnCut(const JSCallbackInfo& info);
    static void SetOnCopy(const JSCallbackInfo& info);
    static JSRef<JSVal> CreateJSTextCommonEvent(NG::TextCommonEvent& event);
    static JSRef<JSObject> CreateJSSpanResultObject(const ResultObject& resultObject);
    static JSRef<JSVal> CreateJSSelection(const SelectionInfo& selectInfo);
    static JSRef<JSVal> CreateJSSelectionRange(const SelectionRangeInfo& selectRange);
    static JSRef<JSObject> CreateJSTextStyleResult(const TextStyleResult& textStyleResult);
    static JSRef<JSObject> CreateJSParagraphStyle(const TextStyleResult& textStyleResult);
    static JSRef<JSObject> CreateJSSymbolSpanStyleResult(const SymbolSpanStyle& symbolSpanStyle);
    static JSRef<JSObject> CreateJSValueResource(const RefPtr<ResourceObject>& valueResource);
    static JSRef<JSObject> CreateJSLayoutStyle(const ImageStyleResult& imageStyleResult);
    static JSRef<JSObject> CreateJSImageStyleResult(const ImageStyleResult& imageStyleResult);
    static JSRef<JSObject> CreateParagraphStyleResult(const ParagraphInfo& info);
    static void SetCaretColor(const JSCallbackInfo& info);
    static void SetSelectedBackgroundColor(const JSCallbackInfo& info);
    static void SetOnEditingChange(const JSCallbackInfo& args);
    static void SetEnterKeyType(const JSCallbackInfo& info);
    static void CreateJsRichEditorCommonEvent(const JSCallbackInfo& info);
    static void SetOnSubmit(const JSCallbackInfo& info);
    static Local<JSValueRef> JsKeepEditableState(panda::JsiRuntimeCallInfo* info);
    static std::optional<NG::BorderRadiusProperty> ParseBorderRadiusAttr(JsiRef<JSVal> args);
    static std::optional<NG::MarginProperty> ParseMarginAttr(JsiRef<JSVal> marginAttr);
    static CalcDimension ParseLengthMetrics(const JSRef<JSObject>& obj);
    static void EditMenuOptions(const JSCallbackInfo& info);
    static void SetEnableKeyboardOnFocus(const JSCallbackInfo& info);
    static void SetEnableHapticFeedback(const JSCallbackInfo& info);
    static JSRef<JSArray> CreateJsTextShadowObjectArray(const TextStyleResult& textStyleResult);
    static JSRef<JSArray> CreateJsTextShadowObjectArray(const std::vector<Shadow>& textShadows);
    static void SetBarState(const JSCallbackInfo& info);
private:
    static void CreateTextStyleObj(JSRef<JSObject>& textStyleObj, const NG::RichEditorAbstractSpanResult& spanResult);
    static void CreateImageStyleObj(JSRef<JSObject>& imageStyleObj, JSRef<JSObject>& spanResultObj,
        const NG::RichEditorAbstractSpanResult& spanResult);
    static JSRef<JSArray> CreateJSDeleteSpans(const NG::RichEditorDeleteValue& deleteValue);
    static void ParseUserGesture(
        const JSCallbackInfo& args, UserGestureOptions& gestureOption, const std::string& spanType);
    static void ParseJsFont(const JSRef<JSObject>& fontObject, Font& font);
    static void SetTextChangeSpanResult(JSRef<JSObject>& resultObj,
        const NG::RichEditorAbstractSpanResult& spanResult);
    static void SetImageChangeSpanResult(JSRef<JSObject>& resultObj,
        const NG::RichEditorAbstractSpanResult& spanResult);
    static void SetSymbolChangeSpanResult(JSRef<JSObject>& resultObj,
        const NG::RichEditorAbstractSpanResult& spanResult);
    static void SetJSSpanResultObject(JSRef<JSObject>& resultObj, const ResultObject& resultObject);
    static void SetJSDeleteSpan(JSRef<JSObject>& spanResultObj, const NG::RichEditorAbstractSpanResult& it);
};

class JSRichEditorBaseController : public Referenced {
public:
    void SetController(const RefPtr<RichEditorBaseControllerBase>& controller)
    {
        controllerWeak_ = controller;
    }

    void SetCaretOffset(const JSCallbackInfo& args);
    void GetCaretOffset(const JSCallbackInfo& args);
    void SetTypingStyle(const JSCallbackInfo& info);
    void ParseJsTextStyle(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);
    void ParseJsLineHeightLetterSpacingTextStyle(const JSRef<JSObject>& styleObject, TextStyle& style,
        struct UpdateSpanStyle& updateSpanStyle, bool isSupportPercent = true);
    void ParseJsFontFeatureTextStyle(const JSRef<JSObject>& styleObject, TextStyle& style,
        struct UpdateSpanStyle& updateSpanStyle);
    void GetTypingStyle(const JSCallbackInfo& info);
    void CloseSelectionMenu();
    void IsEditing(const JSCallbackInfo& args);
    void StopEditing();
    void SetSelection(const JSCallbackInfo& args);
    bool FontSizeRangeIsNegative(const CalcDimension& size);
    void GetLayoutManager(const JSCallbackInfo& args);
    void GetPreviewTextInfo(const JSCallbackInfo& args);

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

    void SetStyledStringMode(bool isStyledStringMode)
    {
        isStyledStringMode_ = isStyledStringMode;
    }

    bool IsStyledStringMode()
    {
        return isStyledStringMode_;
    }

protected:
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    WeakPtr<RichEditorBaseControllerBase> controllerWeak_;
    struct UpdateSpanStyle typingStyle_;
    bool isStyledStringMode_ = false;
    static JSRef<JSObject> CreateTypingStyleResult(const struct UpdateSpanStyle& typingStyle);
    void ParseTextDecoration(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);
    void ParseTextShadow(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);
    JSRef<JSObject> JSObjectCast(JSRef<JSVal> jsValue);
    void ParseJsSelectionOptions(const JSCallbackInfo& args, std::optional<SelectionOptions>& options);
    JSRef<JSObject> CreateJSPreviewTextInfo(const PreviewTextInfo& info);
};

class JSRichEditorController final : public JSRichEditorBaseController {
public:
    JSRichEditorController() = default;
    ~JSRichEditorController() override = default;

    static void JSBind(BindingTarget globalObj);

    static void Constructor(const JSCallbackInfo& args)
    {
        auto controller = Referenced::MakeRefPtr<JSRichEditorController>();
        controller->SetStyledStringMode(false);
        controller->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(controller));
    }

    static void Destructor(JSRichEditorController* controller)
    {
        if (controller != nullptr) {
            controller->DecRefCount();
        }
    }

    void AddImageSpan(const JSCallbackInfo& args);
    void AddTextSpan(const JSCallbackInfo& args);
    void AddSymbolSpan(const JSCallbackInfo& args);
    void AddPlaceholderSpan(const JSCallbackInfo& args);
    void ParseOptions(const JSCallbackInfo& args, SpanOptionBase& placeholderSpan);
    void DeleteSpans(const JSCallbackInfo& args);
    ImageSpanAttribute ParseJsImageSpanAttribute(JSRef<JSObject> imageAttribute);
    void ParseJsSymbolSpanStyle(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);
    ImageSpanOptions CreateJsImageOptions(const JSCallbackInfo& args);
    void UpdateSpanStyle(const JSCallbackInfo& info);
    void UpdateParagraphStyle(const JSCallbackInfo& info);
    void GetSpansInfo(const JSCallbackInfo& args);
    void GetParagraphsInfo(const JSCallbackInfo& args);
    void GetSelection(const JSCallbackInfo& args);
    void ToStyledString(const JSCallbackInfo& args);
    void FromStyledString(const JSCallbackInfo& args);

private:
    bool ParseParagraphStyle(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
    bool IsPixelMap(const JSRef<JSVal>& jsValue);
    bool IsDrawable(const JSRef<JSVal>& jsValue);
    static JSRef<JSVal> CreateJSSpansInfo(const SelectionInfo& info);
    static JSRef<JSVal> CreateJSParagraphsInfo(const std::vector<ParagraphInfo>& info);
    static void ParseWordBreakParagraphStyle(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
    static void ParseTextAlignParagraphStyle(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
    bool CheckImageSource(std::string assetSrc);

    ACE_DISALLOW_COPY_AND_MOVE(JSRichEditorController);
    struct UpdateSpanStyle updateSpanStyle_;
    static void ParseLineBreakStrategyParagraphStyle(
        const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
};

class JSRichEditorStyledStringController final : public JSRichEditorBaseController {
public:
    JSRichEditorStyledStringController() = default;
    ~JSRichEditorStyledStringController() override = default;

    static void JSBind(BindingTarget globalObj);

    static void Constructor(const JSCallbackInfo& args)
    {
        auto controller = Referenced::MakeRefPtr<JSRichEditorStyledStringController>();
        controller->SetStyledStringMode(true);
        controller->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(controller));
    }

    static void Destructor(JSRichEditorStyledStringController* controller)
    {
        if (controller != nullptr) {
            controller->DecRefCount();
        }
    }

    void GetSelection(const JSCallbackInfo& args);
    void SetStyledString(const JSCallbackInfo& args);
    void GetStyledString(const JSCallbackInfo& args);
    void OnContentChanged(const JSCallbackInfo& args);

private:
    void SetOnWillChange(const JSCallbackInfo& args);
    void SetOnDidChange(const JSCallbackInfo& args);
    static JSRef<JSVal> CreateJsOnWillChange(const NG::StyledStringChangeValue& changeValue);
    ACE_DISALLOW_COPY_AND_MOVE(JSRichEditorStyledStringController);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RICHEDITOR_H
