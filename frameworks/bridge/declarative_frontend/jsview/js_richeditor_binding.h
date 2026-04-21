/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RICH_EDITOR_BINDING_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RICH_EDITOR_BINDING_H

#include "base/utils/device_config.h"
#include "bridge/declarative_frontend/jsview/js_richeditor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {

class JSRichEditor : public JSContainerBase {
public:
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
    static JSRef<JSArray> CreateJsTextShadowObjectArray(const TextStyleResult& textStyleResult);
    static JSRef<JSArray> CreateJsTextShadowObjectArray(const std::vector<Shadow>& textShadows);
    static JSRef<JSObject> CreateJsTextBackgroundStyle(const TextBackgroundStyle& style);
    static std::optional<NG::BorderRadiusProperty> ParseBorderRadiusAttr(JsiRef<JSVal> args);
    static std::optional<NG::MarginProperty> ParseMarginAttr(JsiRef<JSVal> marginAttr);
    static CalcDimension ParseLengthMetrics(const JSRef<JSObject>& obj, bool validateNonNegative = true);
    static void SetJsTextBackgroundStyle(JSRef<JSObject>& textStyleObj, const TextStyleResult& textSpanResult);
    static bool ParseJsColorWithResource(const JSRef<JSVal>& jsValue, Color& result, RefPtr<ResourceObject>& resObj);
    static bool ParseColorMetricsToColor(const JSRef<JSVal>& jsValue, Color& result, RefPtr<ResourceObject>& resObj);
    static bool ParseJsSymbolColorWithResource(const JSRef<JSVal>& jsValue, std::vector<Color>& result,
        std::vector<std::pair<int32_t, RefPtr<ResourceObject>>>& resObjArr);
    static void SetJSSpanResultObject(JSRef<JSObject>& resultObj, const ResultObject& resultObject);
    static void SetJSUrlStyle(const std::u16string& urlAddress, JSRef<JSObject>& resultObj);
};

class JSRichEditorBaseControllerBinding : public JSRichEditorBaseController {
public:
    void SetCaretOffset(const JSCallbackInfo& args);
    void GetCaretOffset(const JSCallbackInfo& args);
    void GetCaretRect(const JSCallbackInfo& args);
    void SetTypingStyle(const JSCallbackInfo& info);
    void SetTypingParagraphStyle(const JSCallbackInfo& info);
    void SetPlaceholderStyledString(const JSCallbackInfo& info);
    void ParseJsTextStyle(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);
    bool ParseParagraphStyle(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
    bool IsPixelMap(const JSRef<JSVal>& jsValue);
    static void ParseTextAlignParagraphStyle(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
    static void ParseWordBreakParagraphStyle(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
    static void ParseParagraphSpacing(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
    static void ParseTextVerticalAlign(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
    static void ParseTextDirection(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
    static void ParseLineBreakStrategyParagraphStyle(
        const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style);
    void ParseJsLineHeightLetterSpacingTextStyle(const JSRef<JSObject>& styleObject, TextStyle& style,
        struct UpdateSpanStyle& updateSpanStyle, bool isSupportPercent = true);
    void ParseJsFontFeatureTextStyle(const JSRef<JSObject>& styleObject, TextStyle& style,
        struct UpdateSpanStyle& updateSpanStyle);
    void ParseJsHalfLeadingTextStyle(const JSRef<JSObject>& styleObject, TextStyle& style,
        struct UpdateSpanStyle& updateSpanStyle);
    void GetTypingStyle(const JSCallbackInfo& info);
    void IsEditing(const JSCallbackInfo& args);
    void SetSelection(const JSCallbackInfo& args);
    void GetLayoutManager(const JSCallbackInfo& args);
    void DeleteBackward(const JSCallbackInfo& args);
    void GetPreviewTextInfo(const JSCallbackInfo& args);

protected:
    static JSRef<JSObject> CreateTypingStyleResult(const struct UpdateSpanStyle& typingStyle);
    static JSRef<JSObject> CreateJsDecorationObj(const struct UpdateSpanStyle& typingStyle);
    void ParseJsFontFamilyTextStyle(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);
    void ParseTextDecoration(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);
    void ParseTextShadow(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);
    void ParseTextBackgroundStyle(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);
    void ParseJsStrokeWidthTextStyle(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);
    void ParseJsStrokeColorTextStyle(
        const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);
    void ParseTextUrlStyle(const JSRef<JSObject>& styleObject, std::optional<std::u16string>& urlAddressOpt);
    JSRef<JSObject> JSObjectCast(JSRef<JSVal> jsValue);
    void ParseJsSelectionOptions(const JSCallbackInfo& args, std::optional<SelectionOptions>& options);
    JSRef<JSObject> CreateJSPreviewTextInfo(const PreviewTextInfo& info);
};

class JSRichEditorController final: public JSRichEditorBaseControllerBinding {
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
    void ParseAccessibilityOptions(const JSRef<JSObject>& options, SpanOptionBase& placeholderSpan);
    void DeleteSpans(const JSCallbackInfo& args);
    ImageSpanAttribute ParseJsImageSpanAttribute(JSRef<JSObject> imageAttribute);
    void ParseJsCustomSymbolStyle(const JSRef<JSVal>& jsValue, TextStyle& style, uint32_t& symbolId);
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
    static void ParseUserGesture(
        const JSCallbackInfo& args, UserGestureOptions& gestureOption, const std::string& spanType);
    static void ParseUserClickEvent(const JSCallbackInfo& args, const JSRef<JSObject>& gestureObj,
        UserGestureOptions& gestureOption, const std::string& spanType);
    static void ParseUserMouseOption(
        const JSCallbackInfo& args, UserMouseOptions& mouseOption, const std::string& spanType);
    bool IsDrawable(const JSRef<JSVal>& jsValue);
    static JSRef<JSVal> CreateJSSpansInfo(const SelectionInfo& info);
    static JSRef<JSVal> CreateJSParagraphsInfo(const std::vector<ParagraphInfo>& info);
    bool CheckImageSource(std::string assetSrc);

    ACE_DISALLOW_COPY_AND_MOVE(JSRichEditorController);
    struct UpdateSpanStyle updateSpanStyle_;
};

class JSRichEditorStyledStringController final : public JSRichEditorBaseControllerBinding {
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

    void SetController(const RefPtr<RichEditorBaseControllerBase>& controller) override;

    void GetSelection(const JSCallbackInfo& args);
    void SetStyledString(const JSCallbackInfo& args);
    void GetStyledString(const JSCallbackInfo& args);
    void OnContentChanged(const JSCallbackInfo& args);

    void SetStyledStringCache(RefPtr<SpanString> styledString)
    {
        styledStringCache_ = styledString;
    }

    RefPtr<SpanString> GetStyledStringCache() const
    {
        return styledStringCache_;
    }

private:
    void SetOnWillChange(const JSCallbackInfo& args);
    void SetOnDidChange(const JSCallbackInfo& args);
    static JSRef<JSVal> CreateJsOnWillChange(const NG::StyledStringChangeValue& changeValue);
    ACE_DISALLOW_COPY_AND_MOVE(JSRichEditorStyledStringController);
    RefPtr<SpanString> styledStringCache_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RICH_EDITOR_BINDING_H
