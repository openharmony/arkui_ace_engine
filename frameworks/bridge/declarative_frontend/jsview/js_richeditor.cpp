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
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
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
void JSRichEditor::SetAboutToIMEInput(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("args not function");
        return;
    }
    auto jsAboutToIMEInputFunc = AceType::MakeRefPtr<JsEventFunction<NG::RichEditorInsertValue, 1>>(
        JSRef<JSFunc>::Cast(args[0]), CreateJsAboutToIMEInputObj);
    auto callback = [execCtx = args.GetExecutionContext(), func = std::move(jsAboutToIMEInputFunc)](
                        const NG::RichEditorInsertValue& insertValue) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, true);
        auto ret = func->ExecuteWithValue(insertValue);
        if (ret->IsBoolean()) {
            return ret->ToBoolean();
        }
        return true;
    };
    RichEditorModel::GetInstance()->SetAboutToIMEInput(std::move(callback));
}

void JSRichEditor::SetOnIMEInputComplete(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("args not function");
        return;
    }
    auto jsOnIMEInputCompleteFunc = AceType::MakeRefPtr<JsEventFunction<NG::RichEditorAbstractSpanResult, 1>>(
        JSRef<JSFunc>::Cast(args[0]), CreateJsOnIMEInputComplete);
    auto callback = [execCtx = args.GetExecutionContext(), func = std::move(jsOnIMEInputCompleteFunc)](
                        const NG::RichEditorAbstractSpanResult& textSpanResult) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->Execute(textSpanResult);
    };
    RichEditorModel::GetInstance()->SetOnIMEInputComplete(std::move(callback));
}
void JSRichEditor::SetAboutToDelete(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("args not function");
        return;
    }
    auto jsAboutToDeleteFunc = AceType::MakeRefPtr<JsEventFunction<NG::RichEditorDeleteValue, 1>>(
        JSRef<JSFunc>::Cast(args[0]), CreateJsAboutToDelet);
    auto callback = [execCtx = args.GetExecutionContext(), func = std::move(jsAboutToDeleteFunc)](
                        const NG::RichEditorDeleteValue& deleteValue) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, true);
        auto ret = func->ExecuteWithValue(deleteValue);
        if (ret->IsBoolean()) {
            return ret->ToBoolean();
        }
        return true;
    };
    RichEditorModel::GetInstance()->SetAboutToDelete(std::move(callback));
}

void JSRichEditor::SetOnDeleteComplete(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("args not function");
        return;
    }
    JsEventCallback<void()> callback(args.GetExecutionContext(), JSRef<JSFunc>::Cast(args[0]));
    RichEditorModel::GetInstance()->SetOnDeleteComplete(callback);
}

JSRef<JSVal> JSRichEditor::CreateJsAboutToIMEInputObj(const NG::RichEditorInsertValue& insertValue)
{
    JSRef<JSObject> aboutToIMEInputObj = JSRef<JSObject>::New();
    aboutToIMEInputObj->SetProperty<int32_t>("insertOffset", insertValue.GetInsertOffset());
    aboutToIMEInputObj->SetProperty<std::string>("insertValue", insertValue.GetInsertValue());
    return JSRef<JSVal>::Cast(aboutToIMEInputObj);
}

JSRef<JSVal> JSRichEditor::CreateJsOnIMEInputComplete(const NG::RichEditorAbstractSpanResult& textSpanResult)
{
    JSRef<JSObject> onIMEInputCompleteObj = JSRef<JSObject>::New();
    JSRef<JSObject> spanPositionObj = JSRef<JSObject>::New();
    JSRef<JSArray> spanRange = JSRef<JSArray>::New();
    JSRef<JSObject> textStyleObj = JSRef<JSObject>::New();
    JSRef<JSObject> decorationObj = JSRef<JSObject>::New();
    JSRef<JSArray> offsetInSpan = JSRef<JSArray>::New();
    spanRange->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(textSpanResult.GetSpanRangeStart())));
    spanRange->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(textSpanResult.GetSpanRangeEnd())));
    offsetInSpan->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(textSpanResult.OffsetInSpan())));
    offsetInSpan->SetValueAt(
        1, JSRef<JSVal>::Make(ToJSValue(textSpanResult.OffsetInSpan() + textSpanResult.GetEraseLength())));
    spanPositionObj->SetPropertyObject("spanRange", spanRange);
    spanPositionObj->SetProperty<int32_t>("spanIndex", textSpanResult.GetSpanIndex());
    decorationObj->SetProperty<TextDecoration>("type", textSpanResult.GetTextDecoration());
    decorationObj->SetProperty<std::string>("color", textSpanResult.GetColor());
    textStyleObj->SetProperty<std::string>("fontColor", textSpanResult.GetFontColor());
    textStyleObj->SetProperty<double>("fontSize", textSpanResult.GetFontSize());
    textStyleObj->SetProperty<int32_t>("fontStyle", static_cast<int32_t>(textSpanResult.GetFontStyle()));
    textStyleObj->SetProperty<int32_t>("fontWeight", textSpanResult.GetFontWeight());
    textStyleObj->SetProperty<std::string>("fontFamily", textSpanResult.GetFontFamily());
    textStyleObj->SetPropertyObject("decoration", decorationObj);
    onIMEInputCompleteObj->SetPropertyObject("spanPosition", spanPositionObj);
    onIMEInputCompleteObj->SetProperty<std::string>("value", textSpanResult.GetValue());
    onIMEInputCompleteObj->SetPropertyObject("textStyle", textStyleObj);
    onIMEInputCompleteObj->SetPropertyObject("offsetInSpan", offsetInSpan);
    return JSRef<JSVal>::Cast(onIMEInputCompleteObj);
}

JSRef<JSVal> JSRichEditor::CreateJsAboutToDelet(const NG::RichEditorDeleteValue& deleteValue)
{
    JSRef<JSObject> AboutToDeletObj = JSRef<JSObject>::New();
    AboutToDeletObj->SetProperty<int32_t>("offset", deleteValue.GetOffset());
    AboutToDeletObj->SetProperty<int32_t>(
        "direction", static_cast<int32_t>(deleteValue.GetRichEditorDeleteDirection()));
    AboutToDeletObj->SetProperty<int32_t>("length", deleteValue.GetLength());
    JSRef<JSArray> richEditorDeleteSpans = JSRef<JSArray>::New();
    auto list = deleteValue.GetRichEditorDeleteSpans();
    int32_t index = 0;
    for (const auto& it : list) {
        JSRef<JSObject> spanResultObj = JSRef<JSObject>::New();
        JSRef<JSObject> spanPositionObj = JSRef<JSObject>::New();
        JSRef<JSArray> spanRange = JSRef<JSArray>::New();
        JSRef<JSArray> offsetInSpan = JSRef<JSArray>::New();
        spanRange->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(it.GetSpanRangeStart())));
        spanRange->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(it.GetSpanRangeEnd())));
        offsetInSpan->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(it.OffsetInSpan())));
        offsetInSpan->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(it.OffsetInSpan() + it.GetEraseLength())));
        spanPositionObj->SetPropertyObject("spanRange", spanRange);
        spanPositionObj->SetProperty<int32_t>("spanIndex", it.GetSpanIndex());
        spanResultObj->SetPropertyObject("spanPosition", spanPositionObj);
        spanResultObj->SetPropertyObject("offsetInSpan", offsetInSpan);
        switch (it.GetType()) {
            case NG::SpanResultType::TEXT: {
                JSRef<JSObject> textStyleObj = JSRef<JSObject>::New();
                CreateTextStyleObj(textStyleObj, it);
                spanResultObj->SetProperty<std::string>("value", it.GetValue());
                spanResultObj->SetPropertyObject("textStyle", textStyleObj);
                break;
            }
            case NG::SpanResultType::IMAGE: {
                JSRef<JSObject> imageStyleObj = JSRef<JSObject>::New();
                CreateImageStyleObj(imageStyleObj, spanResultObj, it);
                spanResultObj->SetPropertyObject("imageStyle", imageStyleObj);
                break;
            }
            default:
                break;
        }
        richEditorDeleteSpans->SetValueAt(index++, spanResultObj);
    }
    AboutToDeletObj->SetPropertyObject("richEditorDeleteSpans", richEditorDeleteSpans);
    return JSRef<JSVal>::Cast(AboutToDeletObj);
}

void JSRichEditor::CreateTextStyleObj(JSRef<JSObject>& textStyleObj, const NG::RichEditorAbstractSpanResult& spanResult)
{
    JSRef<JSObject> decorationObj = JSRef<JSObject>::New();
    decorationObj->SetProperty<TextDecoration>("type", spanResult.GetTextDecoration());
    decorationObj->SetProperty<std::string>("color", spanResult.GetColor());
    textStyleObj->SetProperty<std::string>("fontColor", spanResult.GetFontColor());
    textStyleObj->SetProperty<double>("fontSize", spanResult.GetFontSize());
    textStyleObj->SetProperty<int32_t>("fontStyle", static_cast<int32_t>(spanResult.GetFontStyle()));
    textStyleObj->SetProperty<int32_t>("fontWeight", spanResult.GetFontWeight());
    textStyleObj->SetProperty<std::string>("fontFamily", spanResult.GetFontFamily());
    textStyleObj->SetPropertyObject("decoration", decorationObj);
}

void JSRichEditor::CreateImageStyleObj(
    JSRef<JSObject>& imageStyleObj, JSRef<JSObject>& spanResultObj, const NG::RichEditorAbstractSpanResult& spanResult)
{
    JSRef<JSArray> imageSize = JSRef<JSArray>::New();
    imageSize->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(spanResult.GetSizeWidth())));
    imageSize->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(spanResult.GetSizeHeight())));
    imageStyleObj->SetPropertyObject("size", imageSize);
    imageStyleObj->SetProperty<int32_t>("verticalAlign", static_cast<int32_t>(spanResult.GetVerticalAlign()));
    imageStyleObj->SetProperty<int32_t>("objectFit", static_cast<int32_t>(spanResult.GetObjectFit()));
    if (spanResult.GetValuePixelMap()) {
#ifdef PIXEL_MAP_SUPPORTED
        std::shared_ptr<Media::PixelMap> pixelMap = spanResult.GetValuePixelMap()->GetPixelMapSharedPtr();
        auto engine = EngineHelper::GetCurrentEngine();
        if (engine) {
            NativeEngine* nativeEngine = engine->GetNativeEngine();
            napi_env env = reinterpret_cast<napi_env>(nativeEngine);
            napi_value napiValue = OHOS::Media::PixelMapNapi::CreatePixelMap(env, pixelMap);
            NativeValue* nativeValue = reinterpret_cast<NativeValue*>(napiValue);
            auto jsPixelMap = JsConverter::ConvertNativeValueToJsVal(nativeValue);
            spanResultObj->SetPropertyObject("value", jsPixelMap);
        }
#endif
    } else {
        spanResultObj->SetProperty<std::string>("valueResourceStr", spanResult.GetValueResourceStr());
    }
}

void JSRichEditor::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichEditor>::Declare("RichEditor");
    JSClass<JSRichEditor>::StaticMethod("create", &JSRichEditor::Create);
    JSClass<JSRichEditor>::StaticMethod("onReady", &JSRichEditor::SetOnReady);
    JSClass<JSRichEditor>::StaticMethod("onSelect", &JSRichEditor::SetOnSelect);
    JSClass<JSRichEditor>::StaticMethod("aboutToIMEInput", &JSRichEditor::SetAboutToIMEInput);
    JSClass<JSRichEditor>::StaticMethod("onIMEInputComplete", &JSRichEditor::SetOnIMEInputComplete);
    JSClass<JSRichEditor>::StaticMethod("aboutToDelete", &JSRichEditor::SetAboutToDelete);
    JSClass<JSRichEditor>::StaticMethod("onDeleteComplete", &JSRichEditor::SetOnDeleteComplete);
    JSClass<JSRichEditor>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRichEditor>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRichEditor>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRichEditor>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRichEditor>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRichEditor>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
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
    if (!args[0]->IsEmpty() && args[0]->ToString() != "") {
        options = CreateJsImageOptions(args);
    } else {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(-1)));
        return;
    }
    if (options.image.has_value()) {
        SrcType srcType = ImageSourceInfo::ResolveURIType(options.image.value());
        if (srcType == SrcType::ASSET) {
            auto pipelineContext = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto assetManager = pipelineContext->GetAssetManager();
            CHECK_NULL_VOID(assetManager);
            auto assetData = assetManager->GetAsset(options.image.value());
            if (!assetData) {
                args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(-1)));
                return;
            }
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

ImageSpanOptions JSRichEditorController::CreateJsImageOptions(const JSCallbackInfo& args)
{
    ImageSpanOptions options;
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, options);
    bool isCard = context->IsFormRender();
    std::string image;
    std::string bundleName;
    std::string moduleName;
    bool srcValid = JSContainerBase::ParseJsMedia(args[0], image);
    if (isCard && args[0]->IsString()) {
        SrcType srcType = ImageSourceInfo::ResolveURIType(image);
        bool notSupport = (srcType == SrcType::NETWORK || srcType == SrcType::FILE || srcType == SrcType::DATA_ABILITY);
        if (notSupport) {
            image.clear();
        }
    }
    JSImage::GetJsMediaBundleInfo(args[0], bundleName, moduleName);
    options.image = image;
    options.bundleName = bundleName;
    options.moduleName = moduleName;
    if (!srcValid) {
#if defined(PIXEL_MAP_SUPPORTED)
        if (!isCard) {
            if (IsDrawable(args[0])) {
                options.imagePixelMap = GetDrawablePixmap(args[0]);
            } else {
                options.imagePixelMap = CreatePixelMapFromNapiValue(args[0]);
            }
        }
#endif
    }
    return options;
}

bool JSRichEditorController::IsDrawable(const JSRef<JSVal>& jsValue)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    if (jsObj->IsUndefined()) {
        return false;
    }
    JSRef<JSVal> func = jsObj->GetProperty("getPixelMap");
    return (!func->IsNull() && func->IsFunction());
}

void JSRichEditorController::AddTextSpan(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    TextSpanOptions options;
    std::string spanValue;
    if (!args[0]->IsEmpty() && args[0]->ToString() != "" && JSContainerBase::ParseJsString(args[0], spanValue)) {
        options.value = spanValue;
    } else {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(-1)));
        return;
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

void JSRichEditorController::DeleteSpans(const JSCallbackInfo& args)
{
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    if (!args[0]->IsObject() || !controller) {
        return;
    }
    JSRef<JSObject> spanObject = JSRef<JSObject>::Cast(args[0]);
    RangeOptions options;
    JSRef<JSVal> startVal = spanObject->GetProperty("start");
    int32_t start = 0;
    if (!startVal->IsNull() && JSContainerBase::ParseJsInt32(startVal, start)) {
        options.start = start;
    }
    JSRef<JSVal> endVal = spanObject->GetProperty("end");
    int32_t end = 0;
    if (!startVal->IsNull() && JSContainerBase::ParseJsInt32(endVal, end)) {
        options.end = end;
    }
    controller->DeleteSpans(options);
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
    JSClass<JSRichEditorController>::CustomMethod("deleteSpans", &JSRichEditorController::DeleteSpans);
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

    int32_t start = -1;
    int32_t end = -1;
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
