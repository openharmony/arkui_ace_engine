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

#include <optional>
#include <string>

#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_image.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_textfield.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/richeditor_model_impl.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_selection.h"
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

JSRef<JSObject> JSRichEditor::CreateParagraphStyleResult(const ParagraphInfo& info)
{
    auto obj = JSRef<JSObject>::New();
    obj->SetProperty<int32_t>("textAlign", info.textAlign);

    auto lmObj = JSRef<JSObject>::New();
    auto size = JSRef<JSArray>::New();
    size->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(info.leadingMarginSize[0])));
    size->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(info.leadingMarginSize[1])));
    lmObj->SetProperty("size", size);
#ifdef PIXEL_MAP_SUPPORTED
    if (info.leadingMarginPixmap) {
        lmObj->SetProperty("placeholder", ConvertPixmap(info.leadingMarginPixmap));
    }
#endif
    obj->SetPropertyObject("leadingMargin", lmObj);
    return obj;
}

JSRef<JSObject> JSRichEditor::CreateJSSpanResultObject(const ResultObject& resultObject)
{
    JSRef<JSArray> offsetArray = JSRef<JSArray>::New();
    JSRef<JSArray> spanRangeArray = JSRef<JSArray>::New();
    JSRef<JSObject> resultObj = JSRef<JSObject>::New();
    JSRef<JSObject> spanPositionObj = JSRef<JSObject>::New();
    offsetArray->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(resultObject.offsetInSpan[0])));
    offsetArray->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(resultObject.offsetInSpan[1])));
    spanRangeArray->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(resultObject.spanPosition.spanRange[0])));
    spanRangeArray->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(resultObject.spanPosition.spanRange[1])));
    spanPositionObj->SetProperty<int32_t>("spanIndex", resultObject.spanPosition.spanIndex);
    spanPositionObj->SetPropertyObject("spanRange", spanRangeArray);
    resultObj->SetPropertyObject("offsetInSpan", offsetArray);
    resultObj->SetPropertyObject("spanPosition", spanPositionObj);
    if (resultObject.type == RichEditorSpanType::TYPESPAN) {
        resultObj->SetProperty<std::string>("value", resultObject.valueString);
        resultObj->SetPropertyObject("textStyle", CreateJSTextStyleResult(resultObject.textStyle));
    } else if (resultObject.type == RichEditorSpanType::TYPEIMAGE) {
        if (resultObject.valuePixelMap) {
#ifdef PIXEL_MAP_SUPPORTED
            auto jsPixmap = ConvertPixmap(resultObject.valuePixelMap);
            if (!jsPixmap->IsUndefined()) {
                resultObj->SetPropertyObject("valuePixelMap", jsPixmap);
            }
#endif
        } else {
            resultObj->SetProperty<std::string>("valueResourceStr", resultObject.valueString);
        }
        resultObj->SetPropertyObject("imageStyle", CreateJSImageStyleResult(resultObject.imageStyle));
    }

    return resultObj;
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

void JSRichEditor::SetCustomKeyboard(const JSCallbackInfo& args)
{
    if (args.Length() > 0 && (args[0]->IsUndefined() || args[0]->IsNull())) {
        RichEditorModel::GetInstance()->SetCustomKeyboard(nullptr);
        return;
    }
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    std::function<void()> buildFunc;
    if (JSTextField::ParseJsCustomKeyboardBuilder(args, 0, buildFunc)) {
        RichEditorModel::GetInstance()->SetCustomKeyboard(std::move(buildFunc));
    }
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
        auto jsPixmap = ConvertPixmap(spanResult.GetValuePixelMap());
        if (!jsPixmap->IsUndefined()) {
            spanResultObj->SetPropertyObject("value", jsPixmap);
        }
#endif
    } else {
        spanResultObj->SetProperty<std::string>("valueResourceStr", spanResult.GetValueResourceStr());
    }
}

void JSRichEditor::JsFocusable(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsBoolean()) {
        LOGW("The info is wrong, it is supposed to be an boolean");
        return;
    }
    JSInteractableView::SetFocusable(info[0]->ToBoolean());
    JSInteractableView::SetFocusNode(false);
}

void JSRichEditor::SetCopyOptions(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto copyOptions = CopyOptions::Distributed;
    auto tmpInfo = info[0];
    if (tmpInfo->IsNumber()) {
        auto emunNumber = tmpInfo->ToNumber<int>();
        copyOptions = static_cast<CopyOptions>(emunNumber);
    }
    RichEditorModel::GetInstance()->SetCopyOption(copyOptions);
}

void JSRichEditor::BindSelectionMenu(const JSCallbackInfo& info)
{
    RichEditorType editorType = RichEditorType::TEXT;
    if (info.Length() >= 1 && info[0]->IsNumber()) {
        auto spanType = info[0]->ToNumber<int32_t>();
        LOGI("Set the spanType is %{public}d.", spanType);
        editorType = static_cast<RichEditorType>(spanType);
    }

    // Builder
    if (info.Length() < 2 || !info[1]->IsObject()) {
        return;
    }

    JSRef<JSObject> menuObj = JSRef<JSObject>::Cast(info[1]);
    auto builder = menuObj->GetProperty("builder");
    if (!builder->IsFunction()) {
        LOGE("builder param is not a function.");
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);

    // responseType
    ResponseType responseType = ResponseType::LONG_PRESS;
    if (info.Length() >= 3 && info[2]->IsNumber()) {
        auto response = info[2]->ToNumber<int32_t>();
        LOGI("Set the responseType is %{public}d.", response);
        responseType = static_cast<ResponseType>(response);
    }
    std::function<void()> buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BindSelectionMenu");
        func->Execute();
    };
    SelectMenuParam menuParam;
    if (info.Length() > 3 && info[3]->IsObject()) {
        ParseMenuParam(info, info[3], menuParam);
    }
    RichEditorModel::GetInstance()->BindSelectionMenu(editorType, responseType, buildFunc, menuParam);
}

void JSRichEditor::ParseMenuParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, SelectMenuParam& menuParam)
{
    auto onAppearValue = menuOptions->GetProperty("onAppear");
    if (onAppearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAppearValue));
        auto onAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnAppearFunc)](
                            int32_t start, int32_t end) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onAppear");

            JSRef<JSVal> params[2];
            params[0] = JSRef<JSVal>::Make(ToJSValue(start));
            params[1] = JSRef<JSVal>::Make(ToJSValue(end));
            func->ExecuteJS(2, params);
        };
        menuParam.onAppear = std::move(onAppear);
    }

    auto onDisappearValue = menuOptions->GetProperty("onDisappear");
    if (onDisappearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnDisAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDisappearValue));
        auto onDisappear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDisAppearFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            LOGI("About to call onAppear method on js");
            ACE_SCORING_EVENT("onDisappear");
            func->Execute();
        };
        menuParam.onDisappear = std::move(onDisappear);
    }
}

JSRef<JSVal> JSRichEditor::CreateJSTextCommonEvent(NG::TextCommonEvent& event)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> object = objectTemplate->NewInstance();
    object->SetPropertyObject("preventDefault", JSRef<JSFunc>::New<FunctionCallback>(JsPreventDefault));
    object->Wrap<NG::TextCommonEvent>(&event);
    return JSRef<JSVal>::Cast(object);
}

void JSRichEditor::SetOnPaste(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    auto jsTextFunc = AceType::MakeRefPtr<JsCitedEventFunction<NG::TextCommonEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), CreateJSTextCommonEvent);

    auto onPaste = [execCtx = info.GetExecutionContext(), func = std::move(jsTextFunc)](NG::TextCommonEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onPaste");
        func->Execute(info);
    };
    RichEditorModel::GetInstance()->SetOnPaste(std::move(onPaste));
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
    JSClass<JSRichEditor>::StaticMethod("customKeyboard", &JSRichEditor::SetCustomKeyboard);
    JSClass<JSRichEditor>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRichEditor>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRichEditor>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRichEditor>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRichEditor>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRichEditor>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRichEditor>::StaticMethod("focusable", &JSRichEditor::JsFocusable);
    JSClass<JSRichEditor>::StaticMethod("copyOptions", &JSRichEditor::SetCopyOptions);
    JSClass<JSRichEditor>::StaticMethod("bindSelectionMenu", &JSRichEditor::BindSelectionMenu);
    JSClass<JSRichEditor>::StaticMethod("onPaste", &JSRichEditor::SetOnPaste);
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
        if (!width->IsNull() && JSContainerBase::ParseJsDimensionVp(width, imageSpanWidth)) {
            imageSize.width = imageSpanWidth;
            updateSpanStyle_.updateImageWidth = imageSpanWidth;
        }
        JSRef<JSVal> height = size->GetValueAt(1);
        CalcDimension imageSpanHeight;
        if (!height->IsNull() && JSContainerBase::ParseJsDimensionVp(height, imageSpanHeight)) {
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

TextStyle JSRichEditorController::ParseJsTextStyle(JSRef<JSObject> styleObject, struct UpdateSpanStyle& updateSpanStyle)
{
    TextStyle style;
    JSRef<JSVal> fontColor = styleObject->GetProperty("fontColor");
    Color textColor;
    if (!fontColor->IsNull() && JSContainerBase::ParseJsColor(fontColor, textColor)) {
        updateSpanStyle.updateTextColor = textColor;
        style.SetTextColor(textColor);
    }
    JSRef<JSVal> fontSize = styleObject->GetProperty("fontSize");
    CalcDimension size;
    if (!fontSize->IsNull() && JSContainerBase::ParseJsDimensionFp(fontSize, size)) {
        updateSpanStyle.updateFontSize = size;
        style.SetFontSize(size);
    }
    JSRef<JSVal> fontStyle = styleObject->GetProperty("fontStyle");
    if (!fontStyle->IsNull() && fontStyle->IsNumber()) {
        updateSpanStyle.updateItalicFontStyle = static_cast<FontStyle>(fontStyle->ToNumber<int32_t>());
        style.SetFontStyle(static_cast<FontStyle>(fontStyle->ToNumber<int32_t>()));
    }
    JSRef<JSVal> fontWeight = styleObject->GetProperty("fontWeight");
    std::string weight;
    if (!fontWeight->IsNull() && (fontWeight->IsNumber() || JSContainerBase::ParseJsString(fontWeight, weight))) {
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        }
        updateSpanStyle.updateFontWeight = ConvertStrToFontWeight(weight);
        style.SetFontWeight(ConvertStrToFontWeight(weight));
    }
    JSRef<JSVal> fontFamily = styleObject->GetProperty("fontFamily");
    std::vector<std::string> family;
    if (!fontFamily->IsNull() && JSContainerBase::ParseJsFontFamilies(fontFamily, family)) {
        updateSpanStyle.updateFontFamily = family;
        style.SetFontFamilies(family);
    }
    auto decorationObj = styleObject->GetProperty("decoration");
    JSRef<JSObject> decorationObject = JSRef<JSObject>::Cast(decorationObj);
    if (!decorationObject->IsUndefined()) {
        JSRef<JSVal> type = decorationObject->GetProperty("type");
        if (!type->IsNull()) {
            updateSpanStyle.updateTextDecoration = static_cast<TextDecoration>(type->ToNumber<int32_t>());
            style.SetTextDecoration(static_cast<TextDecoration>(type->ToNumber<int32_t>()));
        }
        JSRef<JSVal> color = decorationObject->GetProperty("color");
        Color decorationColor;
        if (!color->IsNull() && JSContainerBase::ParseJsColor(color, decorationColor)) {
            updateSpanStyle.updateTextDecorationColor = decorationColor;
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
        std::string assetSrc = options.image.value();
        SrcType srcType = ImageSourceInfo::ResolveURIType(assetSrc);
        if (assetSrc[0] == '/') {
            assetSrc = assetSrc.substr(1); // get the asset src without '/'.
        } else if (assetSrc[0] == '.' && assetSrc.size() > 2 && assetSrc[1] == '/') {
            assetSrc = assetSrc.substr(2); // get the asset src without './'.
        }
        if (srcType == SrcType::ASSET) {
            auto pipelineContext = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto assetManager = pipelineContext->GetAssetManager();
            CHECK_NULL_VOID(assetManager);
            auto assetData = assetManager->GetAsset(assetSrc);
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

bool JSRichEditorController::IsPixelMap(const JSRef<JSVal>& jsValue)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    if (jsObj->IsUndefined()) {
        return false;
    }
    JSRef<JSVal> func = jsObj->GetProperty("readPixelsToBuffer");
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
            TextStyle style = ParseJsTextStyle(styleObject, updateSpanStyle_);
            options.style = style;
        }
        auto paraStyle = spanObject->GetProperty("paragraphStyle");
        auto paraStyleObj = JSRef<JSObject>::Cast(paraStyle);
        if (!paraStyleObj->IsUndefined()) {
            struct UpdateParagraphStyle style;
            if (ParseParagraphStyle(paraStyleObj, style)) {
                options.paraStyle = style;
            }
        }
    }
    auto controller = controllerWeak_.Upgrade();
    int32_t spanIndex = 0;
    if (controller) {
        spanIndex = controller->AddTextSpan(options);
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(spanIndex)));
}

JSRef<JSVal> JSRichEditorController::CreateJSSpansInfo(const RichEditorSelection& info)
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
    int32_t end = -1;
    int32_t start = -1;
    if (args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> startVal = obj->GetProperty("start");
        JSRef<JSVal> endVal = obj->GetProperty("end");

        if (!startVal->IsNull() && startVal->IsNumber()) {
            start = startVal->ToNumber<int32_t>();
        }

        if (!endVal->IsNull() && endVal->IsNumber()) {
            end = endVal->ToNumber<int32_t>();
        }
    }
    if (controllerWeak_.Upgrade()) {
        RichEditorSelection value = controllerWeak_.Upgrade()->GetSpansInfo(start, end);
        args.SetReturnValue(CreateJSSpansInfo(value));
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

void JSRichEditorController::CloseSelectionMenu()
{
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    controller->CloseSelectionMenu();
}

void JSRichEditorController::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichEditorController>::Declare("RichEditorController");
    JSClass<JSRichEditorController>::CustomMethod("addImageSpan", &JSRichEditorController::AddImageSpan);
    JSClass<JSRichEditorController>::CustomMethod("addTextSpan", &JSRichEditorController::AddTextSpan);
    JSClass<JSRichEditorController>::CustomMethod("setCaretOffset", &JSRichEditorController::SetCaretOffset);
    JSClass<JSRichEditorController>::CustomMethod("getCaretOffset", &JSRichEditorController::GetCaretOffset);
    JSClass<JSRichEditorController>::CustomMethod("updateSpanStyle", &JSRichEditorController::UpdateSpanStyle);
    JSClass<JSRichEditorController>::CustomMethod(
        "updateParagraphStyle", &JSRichEditorController::UpdateParagraphStyle);
    JSClass<JSRichEditorController>::CustomMethod("setTypingStyle", &JSRichEditorController::SetTypingStyle);
    JSClass<JSRichEditorController>::CustomMethod("getSpans", &JSRichEditorController::GetSpansInfo);
    JSClass<JSRichEditorController>::CustomMethod("getParagraphs", &JSRichEditorController::GetParagraphsInfo);
    JSClass<JSRichEditorController>::CustomMethod("deleteSpans", &JSRichEditorController::DeleteSpans);
    JSClass<JSRichEditorController>::Method("closeSelectionMenu", &JSRichEditorController::CloseSelectionMenu);
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

namespace {
bool ValidationCheck(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("The argv is wrong, it is supposed to have at least 1 argument");
        return false;
    }
    if (!info[0]->IsNumber() && !info[0]->IsObject()) {
        LOGW("info[0] not is Object or Number");
        return false;
    }
    return true;
}

std::pair<int32_t, int32_t> ParseRange(const JSRef<JSObject>& object)
{
    int32_t start = -1;
    int32_t end = -1;
    JSContainerBase::ParseJsInt32(object->GetProperty("start"), start);
    JSContainerBase::ParseJsInt32(object->GetProperty("end"), end);
    return std::make_pair(start, end);
}
} // namespace

bool JSRichEditorController::ParseParagraphStyle(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style)
{
    auto textAlignObj = styleObject->GetProperty("textAlign");
    if (!textAlignObj->IsNull() && textAlignObj->IsNumber()) {
        auto align = static_cast<TextAlign>(textAlignObj->ToNumber<int32_t>());
        if (align < TextAlign::START || align > TextAlign::JUSTIFY) {
            align = TextAlign::START;
        }
        style.textAlign = align;
    }
    auto leadingMarginObj = styleObject->GetProperty("leadingMargin");
    JSRef<JSObject> leadingMarginObject = JSRef<JSObject>::Cast(leadingMarginObj);
    if (!leadingMarginObject->IsUndefined()) {
        style.leadingMargin = std::make_optional<NG::LeadingMargin>();
        JSRef<JSVal> placeholder = leadingMarginObject->GetProperty("placeholder");
        if (IsPixelMap(placeholder)) {
#if defined(PIXEL_MAP_SUPPORTED)
            auto pixelMap = CreatePixelMapFromNapiValue(placeholder);
            style.leadingMargin->pixmap = pixelMap;
#endif
        }

        JSRef<JSVal> sizeVal = leadingMarginObject->GetProperty("size");
        if (!sizeVal->IsUndefined() && sizeVal->IsArray()) {
            auto rangeArray = JSRef<JSArray>::Cast(sizeVal);
            JSRef<JSVal> widthVal = rangeArray->GetValueAt(0);
            JSRef<JSVal> heightVal = rangeArray->GetValueAt(1);

            CalcDimension width;
            CalcDimension height;
            JSContainerBase::ParseJsDimensionVp(widthVal, width);
            JSContainerBase::ParseJsDimensionVp(heightVal, height);
            auto size = NG::SizeF(width.ConvertToPx(), height.ConvertToPx());
            style.leadingMargin->size = size;
        }
    }
    return true;
}

void JSRichEditorController::UpdateSpanStyle(const JSCallbackInfo& info)
{
    if (!ValidationCheck(info)) {
        return;
    }
    auto jsObject = JSRef<JSObject>::Cast(info[0]);

    auto [start, end] = ParseRange(jsObject);
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    auto richEditorTextStyle = JSRef<JSObject>::Cast(jsObject->GetProperty("textStyle"));
    auto richEditorImageStyle = JSRef<JSObject>::Cast(jsObject->GetProperty("imageStyle"));
    updateSpanStyle_.ResetStyle();
    if (!richEditorTextStyle->IsUndefined()) {
        textStyle = ParseJsTextStyle(richEditorTextStyle, updateSpanStyle_);
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

void JSRichEditorController::GetParagraphsInfo(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        return;
    }
    auto [start, end] = ParseRange(JSRef<JSObject>::Cast(args[0]));
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        auto info = controller->GetParagraphsInfo(start, end);
        args.SetReturnValue(CreateJSParagraphsInfo(info));
    }
}

void JSRichEditorController::UpdateParagraphStyle(const JSCallbackInfo& info)
{
    if (!ValidationCheck(info)) {
        return;
    }
    auto object = JSRef<JSObject>::Cast(info[0]);
    auto [start, end] = ParseRange(object);
    auto styleObj = JSRef<JSObject>::Cast(object->GetProperty("style"));

    if (styleObj->IsUndefined()) {
        return;
    }

    struct UpdateParagraphStyle style;
    if (!ParseParagraphStyle(styleObj, style)) {
        return;
    }
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->UpdateParagraphStyle(start, end, style);
    }
}

void JSRichEditorController::SetTypingStyle(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    if (info.Length() < 1) {
        LOGW("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGW("info[0] not is Object");
        return;
    }
    TextStyle textStyle;
    JSRef<JSObject> richEditorTextStyle = JSRef<JSObject>::Cast(info[0]);
    typingStyle_.ResetStyle();
    if (!richEditorTextStyle->IsUndefined()) {
        textStyle = ParseJsTextStyle(richEditorTextStyle, typingStyle_);
    }
    controller->SetTypingStyle(typingStyle_, textStyle);
}

JSRef<JSVal> JSRichEditorController::CreateJSParagraphsInfo(const std::vector<ParagraphInfo>& info)
{
    auto array = JSRef<JSArray>::New();
    for (size_t i = 0; i < info.size(); ++i) {
        auto obj = JSRef<JSObject>::New();
        obj->SetProperty("style", JSRichEditor::CreateParagraphStyleResult(info[i]));

        auto range = JSRef<JSArray>::New();
        range->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(info[i].range.first)));
        range->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(info[i].range.second)));
        obj->SetProperty("range", range);
        array->SetValueAt(i, obj);
    }
    return JSRef<JSVal>::Cast(array);
}
} // namespace OHOS::Ace::Framework
