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

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_image.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "bridge/declarative_frontend/jsview/js_textfield.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/richeditor_model_impl.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_v2/inspector/utils.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"

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

namespace {

std::optional<NG::MarginProperty> ParseMarginAttr(JsiRef<JSVal> marginAttr)
{
    std::optional<NG::MarginProperty> marginProp = std::nullopt;
    CalcDimension length;
    if (!marginAttr->IsObject() && !marginAttr->IsNumber() && !marginAttr->IsString()) {
        length.Reset();
        marginProp = NG::ConvertToCalcPaddingProperty(length, length, length, length);
        return marginProp;
    }
    if (JSViewAbstract::ParseJsDimensionVp(marginAttr, length)) {
        marginProp = NG::ConvertToCalcPaddingProperty(length, length, length, length);
    } else if (marginAttr->IsObject()) {
        auto marginObj = JSRef<JSObject>::Cast(marginAttr);
        std::optional<CalcDimension> left;
        std::optional<CalcDimension> right;
        std::optional<CalcDimension> top;
        std::optional<CalcDimension> bottom;
        JSViewAbstract::ParseMarginOrPaddingCorner(marginObj, top, bottom, left, right);
        marginProp = NG::ConvertToCalcPaddingProperty(top, bottom, left, right);
    }
    return marginProp;
}

std::optional<NG::BorderRadiusProperty> ParseBorderRadiusAttr(JsiRef<JSVal> args)
{
    std::optional<NG::BorderRadiusProperty> prop = std::nullopt;
    CalcDimension radiusDim;
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        radiusDim.Reset();
        NG::BorderRadiusProperty borderRadius;
        borderRadius.SetRadius(radiusDim);
        borderRadius.multiValued = false;
        prop = borderRadius;
        return prop;
    }
    if (JSViewAbstract::ParseJsDimensionVp(args, radiusDim)) {
        if (radiusDim.Unit() == DimensionUnit::PERCENT) {
            radiusDim.Reset();
        }
        NG::BorderRadiusProperty borderRadius;
        borderRadius.SetRadius(radiusDim);
        borderRadius.multiValued = false;
        prop = borderRadius;
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        CalcDimension topLeft;
        CalcDimension topRight;
        CalcDimension bottomLeft;
        CalcDimension bottomRight;
        JSViewAbstract::ParseAllBorderRadiuses(object, topLeft, topRight, bottomLeft, bottomRight);
        NG::BorderRadiusProperty borderRadius;
        borderRadius.radiusTopLeft = topLeft;
        borderRadius.radiusTopRight = topRight;
        borderRadius.radiusBottomLeft = bottomLeft;
        borderRadius.radiusBottomRight = bottomRight;
        borderRadius.multiValued = true;
        prop = borderRadius;
    }
    return prop;
}

} // namespace

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
    if (!args[0]->IsFunction()) {
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

JSRef<JSObject> JSRichEditor::CreateJSSymbolSpanStyleResult(const SymbolSpanStyle& symbolSpanStyle)
{
    JSRef<JSObject> symbolSpanStyleObj = JSRef<JSObject>::New();
    symbolSpanStyleObj->SetProperty<std::string>("fontColor", symbolSpanStyle.symbolColor);
    symbolSpanStyleObj->SetProperty<double>("fontSize", symbolSpanStyle.fontSize);
    symbolSpanStyleObj->SetProperty<int32_t>("fontWeight", symbolSpanStyle.fontWeight);
    symbolSpanStyleObj->SetProperty<std::optional<uint32_t>>("renderingStrategy", symbolSpanStyle.renderingStrategy);

    return symbolSpanStyleObj;
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
    lmObj->SetPropertyObject("size", size);
#ifdef PIXEL_MAP_SUPPORTED
    if (info.leadingMarginPixmap) {
        lmObj->SetPropertyObject("pixelMap", ConvertPixmap(info.leadingMarginPixmap));
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
    if (resultObject.type == SelectSpanType::TYPESPAN) {
        resultObj->SetProperty<std::string>("value", resultObject.valueString);
        resultObj->SetPropertyObject("textStyle", CreateJSTextStyleResult(resultObject.textStyle));
    } else if (resultObject.type == SelectSpanType::TYPESYMBOLSPAN) {
        resultObj->SetProperty<std::string>("value", resultObject.valueString);
        resultObj->SetPropertyObject("symbolSpanStyle", CreateJSSymbolSpanStyleResult(resultObject.symbolSpanStyle));
    } else if (resultObject.type == SelectSpanType::TYPEIMAGE) {
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

JSRef<JSVal> JSRichEditor::CreateJSSelection(const SelectionInfo& selectInfo)
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
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsSelectFunc =
        AceType::MakeRefPtr<JsEventFunction<SelectionInfo, 1>>(JSRef<JSFunc>::Cast(args[0]), CreateJSSelection);
    auto onSelect = [execCtx = args.GetExecutionContext(), func = std::move(jsSelectFunc)](const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<SelectionInfo>(info);
        func->Execute(*eventInfo);
    };
    NG::RichEditorModelNG::GetInstance()->SetOnSelect(std::move(onSelect));
}
void JSRichEditor::SetAboutToIMEInput(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
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
    if (!args[0]->IsFunction()) {
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
    if (!args[0]->IsFunction()) {
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
    if (!args[0]->IsFunction()) {
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
    if (!args[0]->IsObject()) {
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
    decorationObj->SetProperty<int32_t>("type", (int32_t)(spanResult.GetTextDecoration()));
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
    imageSize->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(spanResult.GetSizeHeight())));
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

void JSRichEditor::JsClip(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        ViewAbstractModel::GetInstance()->SetClipEdge(true);
        return;
    }
    if (info[0]->IsObject()) {
        JSShapeAbstract* clipShape = JSRef<JSObject>::Cast(info[0])->Unwrap<JSShapeAbstract>();
        if (clipShape == nullptr) {
            return;
        }
        ViewAbstractModel::GetInstance()->SetClipShape(clipShape->GetBasicShape());
    } else if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetClipEdge(info[0]->ToBoolean());
    }
}

void JSRichEditor::JsFocusable(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsBoolean()) {
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
    NG::TextSpanType editorType = NG::TextSpanType::NONE;
    if (info.Length() >= 1 && info[0]->IsUndefined()) {
        editorType = NG::TextSpanType::TEXT;
    }
    if (info.Length() >= 1 && info[0]->IsNumber()) {
        auto spanType = info[0]->ToNumber<int32_t>();
        editorType = static_cast<NG::TextSpanType>(spanType);
    }

    // Builder
    if (info.Length() < 2 || !info[1]->IsObject()) {
        return;
    }

    JSRef<JSObject> menuObj = JSRef<JSObject>::Cast(info[1]);
    auto builder = menuObj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);

    // responseType
    NG::TextResponseType responseType = NG::TextResponseType::LONG_PRESS;
    if (info.Length() >= 3 && info[2]->IsNumber()) {
        auto response = info[2]->ToNumber<int32_t>();
        responseType = static_cast<NG::TextResponseType>(response);
    }
    std::function<void()> buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BindSelectionMenu");
        func->Execute();
    };
    NG::SelectMenuParam menuParam;
    int32_t requiredParamCount = 3;
    if (info.Length() > requiredParamCount && info[requiredParamCount]->IsObject()) {
        JSText::ParseMenuParam(info, info[requiredParamCount], menuParam);
    }
    RichEditorModel::GetInstance()->BindSelectionMenu(editorType, responseType, buildFunc, menuParam);
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
    WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onPaste = [execCtx = info.GetExecutionContext(), func = std::move(jsTextFunc), node = targetNode](
                       NG::TextCommonEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onPaste");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    RichEditorModel::GetInstance()->SetOnPaste(std::move(onPaste));
}

void JSRichEditor::JsEnableDataDetector(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto tmpInfo = info[0];
    if (!tmpInfo->IsBoolean()) {
        RichEditorModel::GetInstance()->SetTextDetectEnable(false);
        return;
    }
    auto enable = tmpInfo->ToBoolean();
    RichEditorModel::GetInstance()->SetTextDetectEnable(enable);
}

void JSRichEditor::JsDataDetectorConfig(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }

    std::string textTypes;
    std::function<void(const std::string&)> onResult;
    if (!ParseDataDetectorConfig(info, textTypes, onResult)) {
        return;
    }
    RichEditorModel::GetInstance()->SetTextDetectConfig(textTypes, std::move(onResult));
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
    JSClass<JSRichEditor>::StaticMethod("clip", &JSRichEditor::JsClip);
    JSClass<JSRichEditor>::StaticMethod("focusable", &JSRichEditor::JsFocusable);
    JSClass<JSRichEditor>::StaticMethod("copyOptions", &JSRichEditor::SetCopyOptions);
    JSClass<JSRichEditor>::StaticMethod("bindSelectionMenu", &JSRichEditor::BindSelectionMenu);
    JSClass<JSRichEditor>::StaticMethod("onPaste", &JSRichEditor::SetOnPaste);
    JSClass<JSRichEditor>::StaticMethod("enableDataDetector", &JSRichEditor::JsEnableDataDetector);
    JSClass<JSRichEditor>::StaticMethod("dataDetectorConfig", &JSRichEditor::JsDataDetectorConfig);
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
    auto layoutStyleObj = imageAttribute->GetProperty("layoutStyle");
    auto layoutStyleObject = JSRef<JSObject>::Cast(layoutStyleObj);
    if (!layoutStyleObject->IsUndefined()) {
        auto marginAttr = layoutStyleObject->GetProperty("margin");
        imageStyle.marginProp = ParseMarginAttr(marginAttr);
        updateSpanStyle_.marginProp = imageStyle.marginProp;
        auto borderRadiusAttr = layoutStyleObject->GetProperty("borderRadius");
        imageStyle.borderRadius = ParseBorderRadiusAttr(borderRadiusAttr);
        updateSpanStyle_.borderRadius = imageStyle.borderRadius;
    }
    return imageStyle;
}

void JSRichEditorController::ParseJsTextStyle(
    const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    JSRef<JSVal> fontColor = styleObject->GetProperty("fontColor");
    Color textColor;
    if (!fontColor->IsNull() && JSContainerBase::ParseJsColor(fontColor, textColor)) {
        updateSpanStyle.updateTextColor = textColor;
        style.SetTextColor(textColor);
        updateSpanStyle.hasResourceFontColor = fontColor->IsObject();
    }
    JSRef<JSVal> fontSize = styleObject->GetProperty("fontSize");
    CalcDimension size;
    if (!fontSize->IsNull() && JSContainerBase::ParseJsDimensionFp(fontSize, size) &&
        !size.IsNegative() && size.Unit() != DimensionUnit::PERCENT) {
        updateSpanStyle.updateFontSize = size;
        style.SetFontSize(size);
    } else if (size.IsNegative() || size.Unit() == DimensionUnit::PERCENT) {
        auto theme = JSContainerBase::GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        size = theme->GetTextStyle().GetFontSize();
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
    ParseTextDecoration(styleObject, style, updateSpanStyle);
    ParseTextShadow(styleObject, style, updateSpanStyle);
}

void JSRichEditorController::ParseJsSymbolSpanStyle(
    const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    JSRef<JSVal> fontColor = styleObject->GetProperty("fontColor");
    std::vector<Color> symbolColor;
    if (!fontColor->IsNull() && JSContainerBase::ParseJsSymbolColor(fontColor, symbolColor)) {
        updateSpanStyle.updateSymbolColor = symbolColor;
        style.SetSymbolColorList(symbolColor);
        updateSpanStyle.hasResourceFontColor = fontColor->IsObject();
    }
    JSRef<JSVal> fontSize = styleObject->GetProperty("fontSize");
    CalcDimension size;
    if (!fontSize->IsNull() && JSContainerBase::ParseJsDimensionFp(fontSize, size) &&
        !size.IsNegative() && size.Unit() != DimensionUnit::PERCENT) {
        updateSpanStyle.updateFontSize = size;
        style.SetFontSize(size);
    } else if (size.IsNegative() || size.Unit() == DimensionUnit::PERCENT) {
        auto theme = JSContainerBase::GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        size = theme->GetTextStyle().GetFontSize();
        updateSpanStyle.updateFontSize = size;
        style.SetFontSize(size);
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
    JSRef<JSVal> renderingStrategy = styleObject->GetProperty("renderingStrategy");
    uint32_t symbolRenderStrategy;
    if (!renderingStrategy->IsNull() && renderingStrategy->IsNumber()) {
        updateSpanStyle.updateSymbolRenderingStrategy = symbolRenderStrategy;
        style.SetRenderStrategy(symbolRenderStrategy);
    }
}

void JSRichEditorController::ParseTextShadow(
    const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    auto shadowObject = styleObject->GetProperty("textShadow");
    if (shadowObject->IsNull()) {
        return;
    }
    std::vector<Shadow> shadows;
    ParseTextShadowFromShadowObject(shadowObject, shadows);
    if (!shadows.empty()) {
        updateSpanStyle.updateTextShadows = shadows;
        style.SetTextShadows(shadows);
    }
}

void JSRichEditorController::ParseTextDecoration(
    const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    auto decorationObj = styleObject->GetProperty("decoration");
    JSRef<JSObject> decorationObject = JSRef<JSObject>::Cast(decorationObj);
    if (!decorationObject->IsUndefined()) {
        JSRef<JSVal> type = decorationObject->GetProperty("type");
        if (!type->IsNull() && !type->IsUndefined()) {
            updateSpanStyle.updateTextDecoration = static_cast<TextDecoration>(type->ToNumber<int32_t>());
            style.SetTextDecoration(static_cast<TextDecoration>(type->ToNumber<int32_t>()));
        }
        JSRef<JSVal> color = decorationObject->GetProperty("color");
        Color decorationColor;
        if (!color->IsNull() && JSContainerBase::ParseJsColor(color, decorationColor)) {
            updateSpanStyle.updateTextDecorationColor = decorationColor;
            style.SetTextDecorationColor(decorationColor);
            updateSpanStyle.hasResourceDecorationColor = color->IsObject();
        }
    }
}

void ParseUserGesture(
    const JSCallbackInfo& args, UserGestureOptions& gestureOption, const std::string& spanType)
{
    if (args.Length() < 2) {
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(args[1]);
    auto gesture = object->GetProperty("gesture");
    if (!gesture->IsUndefined()) {
        auto gestureObj = JSRef<JSObject>::Cast(gesture);
        auto clickFunc = gestureObj->GetProperty("onClick");
        if (clickFunc->IsUndefined() && IsDisableEventVersion()) {
            gestureOption.onClick = nullptr;
        } else if (!clickFunc->IsFunction()) {
            gestureOption.onClick = nullptr;
        } else {
            auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(clickFunc));
            auto onClick = [
                    execCtx = args.GetExecutionContext(), func = jsOnClickFunc, spanTypeInner = spanType
                    ](const BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                const auto* clickInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
                ACE_SCORING_EVENT(spanTypeInner + ".onClick");
                func->Execute(*clickInfo);
            };
            auto tmpClickFunc = [func = std::move(onClick)](GestureEvent& info) { func(&info); };
            gestureOption.onClick = std::move(tmpClickFunc);
        }
        auto onLongPressFunc = gestureObj->GetProperty("onLongPress");
        if (onLongPressFunc->IsUndefined() && IsDisableEventVersion()) {
            gestureOption.onLongPress = nullptr;
        } else if (!onLongPressFunc->IsFunction()) {
            gestureOption.onLongPress = nullptr;
        } else {
            auto jsLongPressFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(onLongPressFunc));
            auto onLongPress = [
                    execCtx = args.GetExecutionContext(), func = jsLongPressFunc, spanTypeInner = spanType
                    ](const BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                const auto* longPressInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
                ACE_SCORING_EVENT(spanTypeInner + ".onLongPress");
                func->Execute(*longPressInfo);
            };
            auto tmpOnLongPressFunc = [func = std::move(onLongPress)](GestureEvent& info) { func(&info); };
            gestureOption.onLongPress = std::move(tmpOnLongPressFunc);
        }
    }
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
        UserGestureOptions gestureOption;
        ParseUserGesture(args, gestureOption, "ImageSpan");
        options.userGestureOption = std::move(gestureOption);
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
            auto pipelineContext = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto theme = pipelineContext->GetTheme<TextTheme>();
            TextStyle style = theme ? theme->GetTextStyle() : TextStyle();
            ParseJsTextStyle(styleObject, style, updateSpanStyle_);
            options.style = style;
            options.hasResourceFontColor = updateSpanStyle_.hasResourceFontColor;
            options.hasResourceDecorationColor = updateSpanStyle_.hasResourceDecorationColor;
        }
        auto paraStyle = spanObject->GetProperty("paragraphStyle");
        auto paraStyleObj = JSRef<JSObject>::Cast(paraStyle);
        if (!paraStyleObj->IsUndefined()) {
            struct UpdateParagraphStyle style;
            if (ParseParagraphStyle(paraStyleObj, style)) {
                options.paraStyle = style;
            }
        }
        UserGestureOptions gestureOption;
        ParseUserGesture(args, gestureOption, "TextSpan");
        options.userGestureOption = std::move(gestureOption);
    }
    auto controller = controllerWeak_.Upgrade();
    int32_t spanIndex = 0;
    if (controller) {
        spanIndex = controller->AddTextSpan(options);
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(spanIndex)));
}

void JSRichEditorController::AddSymbolSpan(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    SymbolSpanOptions options;
    uint32_t symbolId;
    if (!args[0]->IsEmpty() && JSContainerBase::ParseJsSymbolId(args[0], symbolId)) {
        options.symbolId = symbolId;
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
            auto pipelineContext = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto theme = pipelineContext->GetTheme<TextTheme>();
            TextStyle style = theme ? theme->GetTextStyle() : TextStyle();
            ParseJsTextStyle(styleObject, style, updateSpanStyle_);
            options.style = style;
        }
    }

    auto controller = controllerWeak_.Upgrade();
    int32_t spanIndex = 0;
    if (controller) {
        spanIndex = controller->AddSymbolSpan(options);
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(spanIndex)));
}

JSRef<JSVal> JSRichEditorController::CreateJSSpansInfo(const SelectionInfo& info)
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
        SelectionInfo value = controllerWeak_.Upgrade()->GetSpansInfo(start, end);
        args.SetReturnValue(CreateJSSpansInfo(value));
    }
}

void JSRichEditorController::DeleteSpans(const JSCallbackInfo& args)
{
    RangeOptions options;
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);

    if (args.Length() < 1) {
        controller->DeleteSpans(options);
        return;
    }

    if (!args[0]->IsObject() || !controller) {
        return;
    }
    JSRef<JSObject> spanObject = JSRef<JSObject>::Cast(args[0]);
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

void JSRichEditorController::AddPlaceholderSpan(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    auto customVal = args[0];
    if (!customVal->IsFunction() && !customVal->IsObject()) {
        return;
    }
    JSRef<JSVal> funcValue;
    auto customObject = JSRef<JSObject>::Cast(customVal);
    auto builder = customObject->GetProperty("builder");
    // if failed to get builder, parse function directly
    if (builder->IsEmpty() || builder->IsNull() || !builder->IsFunction()) {
        funcValue = customVal;
    } else {
        funcValue = builder;
    }
    SpanOptionBase options;
    {
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(funcValue));
        CHECK_NULL_VOID(builderFunc);
        ViewStackModel::GetInstance()->NewScope();
        builderFunc->Execute();
        auto customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
        auto controller = controllerWeak_.Upgrade();
        int32_t spanIndex = 0;
        if (controller) {
            ParseOptions(args, options);
            spanIndex = controller->AddPlaceholderSpan(customNode, options);
        }
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(spanIndex)));
    }
}

void JSRichEditorController::ParseOptions(const JSCallbackInfo& args, SpanOptionBase& placeholderSpan)
{
    if (args.Length() < 2) {
        return;
    }
    if (!args[1]->IsObject()) {
        return;
    }
    JSRef<JSObject> placeholderOptionObject = JSRef<JSObject>::Cast(args[1]);
    JSRef<JSVal> offset = placeholderOptionObject->GetProperty("offset");
    int32_t placeholderOffset = 0;
    if (!offset->IsNull() && JSContainerBase::ParseJsInt32(offset, placeholderOffset)) {
        placeholderSpan.offset = placeholderOffset >= 0 ? placeholderOffset : Infinity<int32_t>();
    }
}

void JSRichEditorController::CloseSelectionMenu()
{
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    controller->CloseSelectionMenu();
}

void JSRichEditorController::SetSelection(int32_t selectionStart, int32_t selectionEnd)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        controller->SetSelection(selectionStart, selectionEnd);
    }
}

void JSRichEditorController::GetSelection(const JSCallbackInfo& args)
{
    auto controller = controllerWeak_.Upgrade();
    if (controller) {
        SelectionInfo value = controller->GetSelectionSpansInfo();
        args.SetReturnValue(JSRichEditor::CreateJSSelection(value));
    }
}

void JSRichEditorController::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichEditorController>::Declare("RichEditorController");
    JSClass<JSRichEditorController>::CustomMethod("addImageSpan", &JSRichEditorController::AddImageSpan);
    JSClass<JSRichEditorController>::CustomMethod("addTextSpan", &JSRichEditorController::AddTextSpan);
    JSClass<JSRichEditorController>::CustomMethod("addSymbolSpan", &JSRichEditorController::AddSymbolSpan);
    JSClass<JSRichEditorController>::CustomMethod("addBuilderSpan", &JSRichEditorController::AddPlaceholderSpan);
    JSClass<JSRichEditorController>::CustomMethod("setCaretOffset", &JSRichEditorController::SetCaretOffset);
    JSClass<JSRichEditorController>::CustomMethod("getCaretOffset", &JSRichEditorController::GetCaretOffset);
    JSClass<JSRichEditorController>::CustomMethod("updateSpanStyle", &JSRichEditorController::UpdateSpanStyle);
    JSClass<JSRichEditorController>::CustomMethod(
        "updateParagraphStyle", &JSRichEditorController::UpdateParagraphStyle);
    JSClass<JSRichEditorController>::CustomMethod("getTypingStyle", &JSRichEditorController::GetTypingStyle);
    JSClass<JSRichEditorController>::CustomMethod("setTypingStyle", &JSRichEditorController::SetTypingStyle);
    JSClass<JSRichEditorController>::CustomMethod("getSpans", &JSRichEditorController::GetSpansInfo);
    JSClass<JSRichEditorController>::CustomMethod("getParagraphs", &JSRichEditorController::GetParagraphsInfo);
    JSClass<JSRichEditorController>::CustomMethod("deleteSpans", &JSRichEditorController::DeleteSpans);
    JSClass<JSRichEditorController>::Method("setSelection", &JSRichEditorController::SetSelection);
    JSClass<JSRichEditorController>::CustomMethod("getSelection", &JSRichEditorController::GetSelection);
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
    if (!info[0]->IsNumber() && !info[0]->IsObject()) {
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
    if (start < 0) {
        start = 0;
    }
    if (end < 0) {
        end = INT_MAX;
    }
    if (start > end) {
        std::swap(start, end);
    }
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
    auto lm = styleObject->GetProperty("leadingMargin");
    if (lm->IsObject()) {
        // [LeadingMarginPlaceholder]
        JSRef<JSObject> leadingMarginObject = JSRef<JSObject>::Cast(lm);
        style.leadingMargin = std::make_optional<NG::LeadingMargin>();
        JSRef<JSVal> placeholder = leadingMarginObject->GetProperty("pixelMap");
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
            style.leadingMargin->size = NG::SizeF(width.ConvertToPx(), height.ConvertToPx());
        } else if (sizeVal->IsUndefined()) {
            std::string resWidthStr;
            if (JSContainerBase::ParseJsString(lm, resWidthStr)) {
                Dimension resWidth = Dimension::FromString(resWidthStr);
                style.leadingMargin->size = NG::SizeF(resWidth.Value(), 0.0);
            }
        }
    } else if (!lm->IsNull()) {
        // [Dimension]
        style.leadingMargin = std::make_optional<NG::LeadingMargin>();
        CalcDimension width;
        JSContainerBase::ParseJsDimensionVp(lm, width);
        style.leadingMargin->size = NG::SizeF(width.ConvertToPx(), 0.0);
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
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    TextStyle textStyle = theme ? theme->GetTextStyle() : TextStyle();
    ImageSpanAttribute imageStyle;
    auto richEditorTextStyle = JSRef<JSObject>::Cast(jsObject->GetProperty("textStyle"));
    auto richEditorImageStyle = JSRef<JSObject>::Cast(jsObject->GetProperty("imageStyle"));
    auto richEditorSymbolSpanStyle = JSRef<JSObject>::Cast(jsObject->GetProperty("symbolStyle"));
    updateSpanStyle_.ResetStyle();
    if (!richEditorTextStyle->IsUndefined()) {
        ParseJsTextStyle(richEditorTextStyle, textStyle, updateSpanStyle_);
    }
    if (!richEditorImageStyle->IsUndefined()) {
        imageStyle = ParseJsImageSpanAttribute(richEditorImageStyle);
    }
    if (!richEditorSymbolSpanStyle->IsUndefined()) {
        ParseJsSymbolSpanStyle(richEditorSymbolSpanStyle, textStyle, updateSpanStyle_);
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
    if (start == end) {
        return;
    }
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
    if (start == end) {
        return;
    }
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

JSRef<JSObject> JSRichEditorController::CreateTypingStyleResult(const struct UpdateSpanStyle& typingStyle)
{
    auto tyingStyleObj = JSRef<JSObject>::New();
    TextStyle textStyle;
    if (typingStyle.updateFontFamily.has_value()) {
        std::string family = V2::ConvertFontFamily(typingStyle.updateFontFamily.value());
        tyingStyleObj->SetProperty<std::string>("fontFamily", family);
    }
    if (typingStyle.updateFontSize.has_value()) {
        tyingStyleObj->SetProperty<double>("fontSize", typingStyle.updateFontSize.value().ConvertToVp());
    }
    if (typingStyle.updateTextColor.has_value()) {
        tyingStyleObj->SetProperty<std::string>("fontColor", typingStyle.updateTextColor.value().ColorToString());
    }
    if (typingStyle.updateItalicFontStyle.has_value()) {
        tyingStyleObj->SetProperty<int32_t>(
            "fontStyle", static_cast<int32_t>(typingStyle.updateItalicFontStyle.value()));
    }
    if (typingStyle.updateFontWeight.has_value()) {
        tyingStyleObj->SetProperty<int32_t>("fontWeight", static_cast<int32_t>(typingStyle.updateFontWeight.value()));
    }

    JSRef<JSObject> decorationObj = JSRef<JSObject>::New();
    if (typingStyle.updateTextDecoration.has_value()) {
        decorationObj->SetProperty<int32_t>("type", static_cast<int32_t>(typingStyle.updateTextDecoration.value()));
    }
    if (typingStyle.updateTextDecorationColor.has_value()) {
        decorationObj->SetProperty<std::string>("color", typingStyle.updateTextDecorationColor.value().ColorToString());
    }
    if (typingStyle.updateTextDecoration.has_value() || typingStyle.updateTextDecorationColor.has_value()) {
        tyingStyleObj->SetPropertyObject("decoration", decorationObj);
    }
    return tyingStyleObj;
}

void JSRichEditorController::GetTypingStyle(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    auto style = CreateTypingStyleResult(typingStyle_);
    info.SetReturnValue(JSRef<JSVal>::Cast(style));
}

void JSRichEditorController::SetTypingStyle(const JSCallbackInfo& info)
{
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    if (!info[0]->IsObject()) {
        return;
    }
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    TextStyle textStyle = theme ? theme->GetTextStyle() : TextStyle();
    JSRef<JSObject> richEditorTextStyle = JSRef<JSObject>::Cast(info[0]);
    typingStyle_.ResetStyle();
    if (!richEditorTextStyle->IsUndefined()) {
        ParseJsTextStyle(richEditorTextStyle, textStyle, typingStyle_);
    }
    controller->SetTypingStyle(typingStyle_, textStyle);
}

JSRef<JSVal> JSRichEditorController::CreateJSParagraphsInfo(const std::vector<ParagraphInfo>& info)
{
    auto array = JSRef<JSArray>::New();
    for (size_t i = 0; i < info.size(); ++i) {
        auto obj = JSRef<JSObject>::New();
        obj->SetPropertyObject("style", JSRichEditor::CreateParagraphStyleResult(info[i]));

        auto range = JSRef<JSArray>::New();
        range->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(info[i].range.first)));
        range->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(info[i].range.second)));
        obj->SetPropertyObject("range", range);
        array->SetValueAt(i, obj);
    }
    return JSRef<JSVal>::Cast(array);
}
} // namespace OHOS::Ace::Framework
