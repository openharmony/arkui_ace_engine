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

#include "bridge/declarative_frontend/jsview/js_richeditor.h"

#include <string>

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#include "pixel_map_napi.h"
#endif
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_image.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/richeditor_model_impl.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace {
std::unique_ptr<RichEditorModel> RichEditorModel::instance_ = nullptr;
std::mutex RichEditorModel::mutex_;
RichEditorModel* RichEditorModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::RichEditorModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::RichEditorModelNG());
            } else {
                // empty implementation
                instance_.reset(new Framework::RichEditorModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSRichEditor::Create(const JSCallbackInfo& info)
{
    JSRichEditorController* jsController = nullptr;
    if (info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto controllerObj = paramObject->GetProperty("controller");
        if (!controllerObj->IsUndefined() && !controllerObj->IsNull()) {
            jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSRichEditorController>();
        }
    }
    RichEditorModel::GetInstance()->Create();
    RefPtr<RichEditorControllerBase> controller = RichEditorModel::GetInstance()->GetRichEditorController();
    if (jsController) {
        jsController->SetController(controller);
    }
}

void JSRichEditor::SetOnReady(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("args not function");
        return;
    }
    JsEventCallback<void()> callback(args.GetExecutionContext(), JSRef<JSFunc>::Cast(args[0]));
    RichEditorModel::GetInstance()->SetOnReady(callback);
}

JSRef<JSObject> JSRichEditor::CreateJSTextStyleResult(const TextStyleResult& textStyleResult)
{
    JSRef<JSObject> textStyleObj = JSRef<JSObject>::New();
    textStyleObj->SetProperty<std::string>("fontColor", textStyleResult.fontColor);
    textStyleObj->SetProperty<double>("fontSize", textStyleResult.fontSize);
    textStyleObj->SetProperty<int32_t>("fontStyle", textStyleResult.fontStyle);
    textStyleObj->SetProperty<int32_t>("fontWeight", textStyleResult.fontWeight);
    textStyleObj->SetProperty<std::string>("fontFamily", textStyleResult.fontFamily);
    JSRef<JSObject> decorationObj = JSRef<JSObject>::New();
    decorationObj->SetProperty<int32_t>("type", textStyleResult.decorationType);
    decorationObj->SetProperty<std::string>("color", textStyleResult.decorationColor);
    textStyleObj->SetPropertyObject("decoration", decorationObj);

    return textStyleObj;
}

JSRef<JSObject> JSRichEditor::CreateJSImageStyleResult(const ImageStyleResult& imageStyleResult)
{
    JSRef<JSObject> imageSpanStyleObj = JSRef<JSObject>::New();

    JSRef<JSArray> sizeArray = JSRef<JSArray>::New();
    sizeArray->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(imageStyleResult.size[0])));
    sizeArray->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(imageStyleResult.size[1])));
    imageSpanStyleObj->SetPropertyObject("size", sizeArray);
    imageSpanStyleObj->SetProperty<int32_t>("verticalAlign", imageStyleResult.verticalAlign);
    imageSpanStyleObj->SetProperty<int32_t>("objectFit", imageStyleResult.objectFit);

    return imageSpanStyleObj;
}

JSRef<JSObject> JSRichEditor::CreateJSSpanResultObject(const ResultObject& resultObject)
{
    JSRef<JSArray> offsetArray = JSRef<JSArray>::New();
    JSRef<JSArray> spanRangeArray = JSRef<JSArray>::New();
    JSRef<JSObject> spaneRsultObj = JSRef<JSObject>::New();
    JSRef<JSObject> spanPositionObj = JSRef<JSObject>::New();
    offsetArray->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(resultObject.offsetInSpan[0])));
    offsetArray->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(resultObject.offsetInSpan[1])));
    spanRangeArray->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(resultObject.spanPosition.spanRange[0])));
    spanRangeArray->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(resultObject.spanPosition.spanRange[1])));
    spanPositionObj->SetProperty<int32_t>("spanIndex", resultObject.spanPosition.spanIndex);
    spanPositionObj->SetPropertyObject("spanRange", spanRangeArray);
    spaneRsultObj->SetPropertyObject("offsetInSpan", offsetArray);
    spaneRsultObj->SetPropertyObject("spanPosition", spanPositionObj);
    if (resultObject.type == RichEditorSpanType::TYPESPAN) {
        spaneRsultObj->SetProperty<std::string>("value", resultObject.valueString);
        spaneRsultObj->SetPropertyObject("textStyle", CreateJSTextStyleResult(resultObject.textStyle));
    } else if (resultObject.type == RichEditorSpanType::TYPEIMAGE) {
        if (resultObject.valuePixelMap) {
#ifdef PIXEL_MAP_SUPPORTED
            std::shared_ptr<Media::PixelMap> pixelMap = resultObject.valuePixelMap->GetPixelMapSharedPtr();
            auto engine = EngineHelper::GetCurrentEngine();
            if (engine) {
                NativeEngine* nativeEngine = engine->GetNativeEngine();
                napi_env env = reinterpret_cast<napi_env>(nativeEngine);
                napi_value napiValue = OHOS::Media::PixelMapNapi::CreatePixelMap(env, pixelMap);
                NativeValue* nativeValue = reinterpret_cast<NativeValue*>(napiValue);
                auto jsPixelMap = JsConverter::ConvertNativeValueToJsVal(nativeValue);
                spaneRsultObj->SetPropertyObject("valuePixelMap", jsPixelMap);
            }
#endif
        } else {
            spaneRsultObj->SetProperty<std::string>("valueResourceStr", resultObject.valueString);
        }
        spaneRsultObj->SetPropertyObject("imageStyle", CreateJSImageStyleResult(resultObject.imageStyle));
    }

    return spaneRsultObj;
}

JSRef<JSVal> JSRichEditor::CreateJSSelection(const RichEditorSelection& selectInfo)
{
    uint32_t idx = 0;

    JSRef<JSArray> selectionArray = JSRef<JSArray>::New();
    JSRef<JSArray> spanObjectArray = JSRef<JSArray>::New();
    JSRef<JSObject> selectionObject = JSRef<JSObject>::New();

    const std::list<ResultObject>& spanObjectList = selectInfo.GetSelection().resultObjects;
    for (const ResultObject& spanObject : spanObjectList) {
        spanObjectArray->SetValueAt(idx++, CreateJSSpanResultObject(spanObject));
    }

    selectionArray->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(selectInfo.GetSelection().selection[0])));
    selectionArray->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(selectInfo.GetSelection().selection[1])));

    selectionObject->SetPropertyObject("selection", selectionArray);
    selectionObject->SetPropertyObject("spans", spanObjectArray);
    return JSRef<JSVal>::Cast(selectionObject);
}

void JSRichEditor::SetOnSelect(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGI("args not function");
        return;
    }
    auto jsSelectFunc =
        AceType::MakeRefPtr<JsEventFunction<RichEditorSelection, 1>>(JSRef<JSFunc>::Cast(args[0]), CreateJSSelection);
    auto onSelect = [execCtx = args.GetExecutionContext(), func = std::move(jsSelectFunc)](const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<RichEditorSelection>(info);
        func->Execute(*eventInfo);
    };
    NG::RichEditorModelNG::GetInstance()->SetOnSelect(std::move(onSelect));
}

void JSRichEditor::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichEditor>::Declare("RichEditor");
    JSClass<JSRichEditor>::StaticMethod("create", &JSRichEditor::Create);
    JSClass<JSRichEditor>::StaticMethod("onReady", &JSRichEditor::SetOnReady);
    JSClass<JSRichEditor>::StaticMethod("onSelect", &JSRichEditor::SetOnSelect);
    JSClass<JSRichEditor>::InheritAndBind<JSViewAbstract>(globalObj);
}

ImageSpanAttribute JSRichEditorController::ParseJsImageSpanAttribute(JSRef<JSObject> imageAttribute)
{
    ImageSpanAttribute imageStyle;
    auto sizeObj = imageAttribute->GetProperty("size");
    if (sizeObj->IsArray()) {
        ImageSpanSize imageSize;
        JSRef<JSArray> size = JSRef<JSArray>::Cast(sizeObj);
        JSRef<JSVal> width = size->GetValueAt(0);
        CalcDimension imageSpanWidth;
        if (!width->IsNull() && (JSContainerBase::ParseJsDimensionVp(width, imageSpanWidth) ||
                                    JSContainerBase::ParseJsDimensionFp(width, imageSpanWidth) ||
                                    JSContainerBase::ParseJsDimensionPx(width, imageSpanWidth))) {
            imageSize.width = imageSpanWidth;
            updateSpanStyle_.updateImageWidth = imageSpanWidth;
        }
        JSRef<JSVal> height = size->GetValueAt(1);
        CalcDimension imageSpanHeight;
        if (!height->IsNull() && (JSContainerBase::ParseJsDimensionVp(height, imageSpanHeight) ||
                                     JSContainerBase::ParseJsDimensionFp(height, imageSpanHeight) ||
                                     JSContainerBase::ParseJsDimensionPx(height, imageSpanHeight))) {
            imageSize.height = imageSpanHeight;
            updateSpanStyle_.updateImageHeight = imageSpanHeight;
        }
        imageStyle.size = imageSize;
    }
    JSRef<JSVal> verticalAlign = imageAttribute->GetProperty("verticalAlign");
    if (!verticalAlign->IsNull()) {
        auto align = static_cast<VerticalAlign>(verticalAlign->ToNumber<int32_t>());
        if (align < VerticalAlign::TOP || align > VerticalAlign::NONE) {
            align = VerticalAlign::BOTTOM;
        }
        imageStyle.verticalAlign = align;
        updateSpanStyle_.updateImageVerticalAlign = align;
    }
    JSRef<JSVal> objectFit = imageAttribute->GetProperty("objectFit");
    if (!objectFit->IsNull() && objectFit->IsNumber()) {
        auto fit = static_cast<ImageFit>(objectFit->ToNumber<int32_t>());
        if (fit < ImageFit::FILL || fit > ImageFit::SCALE_DOWN) {
            fit = ImageFit::COVER;
        }
        imageStyle.objectFit = fit;
        updateSpanStyle_.updateImageFit = fit;
    } else {
        imageStyle.objectFit = ImageFit::COVER;
    }
    return imageStyle;
}

TextStyle JSRichEditorController::ParseJsTextStyle(JSRef<JSObject> styleObject)
{
    TextStyle style;
    JSRef<JSVal> fontColor = styleObject->GetProperty("fontColor");
    Color textColor;
    if (!fontColor->IsNull() && JSContainerBase::ParseJsColor(fontColor, textColor)) {
        updateSpanStyle_.updateTextColor = textColor;
        style.SetTextColor(textColor);
    }
    JSRef<JSVal> fontSize = styleObject->GetProperty("fontSize");
    CalcDimension size;
    if (!fontSize->IsNull() && JSContainerBase::ParseJsDimensionFp(fontSize, size)) {
        updateSpanStyle_.updateFontSize = size;
        style.SetFontSize(size);
    }
    JSRef<JSVal> fontStyle = styleObject->GetProperty("fontStyle");
    if (!fontStyle->IsNull()) {
        updateSpanStyle_.updateItalicFontStyle = static_cast<FontStyle>(fontStyle->ToNumber<int32_t>());
        style.SetFontStyle(static_cast<FontStyle>(fontStyle->ToNumber<int32_t>()));
    }
    JSRef<JSVal> fontWeight = styleObject->GetProperty("fontWeight");
    std::string weight;
    if (!fontWeight->IsNull() && JSContainerBase::ParseJsString(fontWeight, weight)) {
        updateSpanStyle_.updateFontWeight = ConvertStrToFontWeight(weight);
        style.SetFontWeight(ConvertStrToFontWeight(weight));
    }
    JSRef<JSVal> fontFamily = styleObject->GetProperty("fontFamily");
    std::vector<std::string> family;
    if (!fontFamily->IsNull() && JSContainerBase::ParseJsFontFamilies(fontFamily, family)) {
        updateSpanStyle_.updateFontFamily = family;
        style.SetFontFamilies(family);
    }
    auto decorationObj = styleObject->GetProperty("decoration");
    JSRef<JSObject> decorationObject = JSRef<JSObject>::Cast(decorationObj);
    if (!decorationObject->IsUndefined()) {
        JSRef<JSVal> type = decorationObject->GetProperty("type");
        if (!type->IsNull()) {
            updateSpanStyle_.updateTextDecoration = static_cast<TextDecoration>(type->ToNumber<int32_t>());
            style.SetTextDecoration(static_cast<TextDecoration>(type->ToNumber<int32_t>()));
        }
        JSRef<JSVal> color = decorationObject->GetProperty("color");
        Color decorationColor;
        if (!color->IsNull() && JSContainerBase::ParseJsColor(color, decorationColor)) {
            updateSpanStyle_.updateTextDecorationColor = decorationColor;
            style.SetTextDecorationColor(decorationColor);
        }
    }
    return style;
}

void JSRichEditorController::AddImageSpan(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    ImageSpanOptions options;
    std::string image;
    std::string bundleName;
    std::string moduleName;
    if (!args[0]->IsNull()) {
        if (!JSContainerBase::ParseJsMedia(args[0], image)) {
#if defined(PIXEL_MAP_SUPPORTED)
            options.imagePixelMap = CreatePixelMapFromNapiValue(args[0]);
#endif
        } else {
            JSImage::GetJsMediaBundleInfo(args[0], bundleName, moduleName);
            options.image = image;
            options.bundleName = bundleName;
            options.moduleName = moduleName;
        }
    }
    if (args.Length() > 1 && args[1]->IsObject()) {
        JSRef<JSObject> imageObject = JSRef<JSObject>::Cast(args[1]);

        JSRef<JSVal> offset = imageObject->GetProperty("offset");
        int32_t imageOffset = 0;
        if (!offset->IsNull() && JSContainerBase::ParseJsInt32(offset, imageOffset)) {
            options.offset = imageOffset;
        }
        auto imageStyleObj = imageObject->GetProperty("imageStyle");
        JSRef<JSObject> imageAttribute = JSRef<JSObject>::Cast(imageStyleObj);
        if (!imageAttribute->IsUndefined()) {
            ImageSpanAttribute imageStyle = ParseJsImageSpanAttribute(imageAttribute);
            options.imageAttribute = imageStyle;
        }
    }
    auto controller = controllerWeak_.Upgrade();
    int32_t spanIndex = 0;
    if (controller) {
        spanIndex = controller->AddImageSpan(options);
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(spanIndex)));
}

void JSRichEditorController::AddTextSpan(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    TextSpanOptions options;
    std::string spanValue;
    if (!args[0]->IsNull() && JSContainerBase::ParseJsString(args[0], spanValue)) {
        options.value = spanValue;
    }
    if (args.Length() > 1 && args[1]->IsObject()) {
        JSRef<JSObject> spanObject = JSRef<JSObject>::Cast(args[1]);
        JSRef<JSVal> offset = spanObject->GetProperty("offset");
        int32_t spanOffset = 0;
        if (!offset->IsNull() && JSContainerBase::ParseJsInt32(offset, spanOffset)) {
            options.offset = spanOffset;
        }
        auto styleObj = spanObject->GetProperty("style");
        JSRef<JSObject> styleObject = JSRef<JSObject>::Cast(styleObj);
        if (!styleObject->IsUndefined()) {
            TextStyle style = ParseJsTextStyle(styleObject);
            options.style = style;
        }
    }
    auto controller = controllerWeak_.Upgrade();
    int32_t spanIndex = 0;
    if (controller) {
        spanIndex = controller->AddTextSpan(options);
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(spanIndex)));
}

JSRef<JSVal> JSRichEditorController::CreateCreateJSSpansInfo(const RichEditorSelection& info)
{
    uint32_t idx = 0;

    JSRef<JSArray> spanObjectArray = JSRef<JSArray>::New();
    JSRef<JSObject> selectionObject = JSRef<JSObject>::New();

    const std::list<ResultObject>& spanObjectList = info.GetSelection().resultObjects;
    for (const ResultObject& spanObject : spanObjectList) {
        spanObjectArray->SetValueAt(idx++, JSRichEditor::CreateJSSpanResultObject(spanObject));
    }

    return JSRef<JSVal>::Cast(spanObjectArray);
}

void JSRichEditorController::GetSpansInfo(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        LOGI("info[0] not is Object");
        return;
    }

    int32_t end = -1;
    int32_t start = -1;
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    JSRef<JSVal> startVal = obj->GetProperty("start");
    JSRef<JSVal> endVal = obj->GetProperty("end");

    if (!startVal->IsNull() && startVal->IsNumber()) {
        start = startVal->ToNumber<int32_t>();
    }

    if (!endVal->IsNull() && endVal->IsNumber()) {
        end = endVal->ToNumber<int32_t>();
    }

    if (controllerWeak_.Upgrade()) {
        RichEditorSelection value = controllerWeak_.Upgrade()->GetSpansInfo(start, end);
        args.SetReturnValue(CreateCreateJSSpansInfo(value));
    }
}

void JSRichEditorController::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichEditorController>::Declare("RichEditorController");
    JSClass<JSRichEditorController>::CustomMethod("addImageSpan", &JSRichEditorController::AddImageSpan);
    JSClass<JSRichEditorController>::CustomMethod("addTextSpan", &JSRichEditorController::AddTextSpan);
    JSClass<JSRichEditorController>::CustomMethod("setCaretOffset", &JSRichEditorController::SetCaretOffset);
    JSClass<JSRichEditorController>::CustomMethod("getCaretOffset", &JSRichEditorController::GetCaretOffset);
    JSClass<JSRichEditorController>::CustomMethod("updateSpanStyle", &JSRichEditorController::UpdateSpanStyle);
    JSClass<JSRichEditorController>::CustomMethod("getSpans", &JSRichEditorController::GetSpansInfo);
    JSClass<JSRichEditorController>::Bind(
        globalObj, JSRichEditorController::Constructor, JSRichEditorController::Destructor);
}

void JSRichEditorController::GetCaretOffset(const JSCallbackInfo& args)
{
    auto controller = controllerWeak_.Upgrade();
    int32_t caretOffset = -1;
    if (controller) {
        caretOffset = controller->GetCaretOffset();
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(caretOffset)));
    } else {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(caretOffset)));
    }
}

void JSRichEditorController::SetCaretOffset(const JSCallbackInfo& args)
{
    auto controller = controllerWeak_.Upgrade();
    int32_t caretPosition = -1;
    bool success = false;
    JSViewAbstract::ParseJsInteger<int32_t>(args[0], caretPosition);
    caretPosition = caretPosition < 0 ? -1 : caretPosition;
    if (controller) {
        success = controller->SetCaretOffset(caretPosition);
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(success)));
    } else {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(success)));
    }
}

void JSRichEditorController::UpdateSpanStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsNumber() && !info[0]->IsObject()) {
        LOGW("info[0] not is Object or Number");
        return;
    }
    auto jsObject = JSRef<JSObject>::Cast(info[0]);

    int32_t start = 0;
    int32_t end = 0;
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    JSContainerBase::ParseJsInt32(jsObject->GetProperty("start"), start);
    JSContainerBase::ParseJsInt32(jsObject->GetProperty("end"), end);
    auto richEditorTextStyle = JSRef<JSObject>::Cast(jsObject->GetProperty("textStyle"));
    auto richEditorImageStyle = JSRef<JSObject>::Cast(jsObject->GetProperty("imageStyle"));
    updateSpanStyle_.ResetStyle();
    if (!richEditorTextStyle->IsUndefined()) {
        textStyle = ParseJsTextStyle(richEditorTextStyle);
    }
    if (!richEditorImageStyle->IsUndefined()) {
        imageStyle = ParseJsImageSpanAttribute(richEditorImageStyle);
    }

    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->SetUpdateSpanStyle(updateSpanStyle_);
        controller->UpdateSpanStyle(start, end, textStyle, imageStyle);
    }
}
} // namespace OHOS::Ace::Framework
