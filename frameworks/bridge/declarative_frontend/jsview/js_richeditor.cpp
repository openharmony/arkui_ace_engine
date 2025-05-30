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

#include "bridge/declarative_frontend/jsview/js_richeditor.h"

#include <optional>
#include <string>
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/functions/js_hover_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_image.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_layout_manager.h"
#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "bridge/declarative_frontend/jsview/js_textfield.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/richeditor_model_impl.h"
#include "bridge/declarative_frontend/style_string/js_span_string.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/rich_editor/color_mode_processor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_base_controller.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_span.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"

namespace OHOS::Ace {
std::unique_ptr<RichEditorModel> RichEditorModel::instance_ = nullptr;
std::mutex RichEditorModel::mutex_;
constexpr int32_t SYSTEM_SYMBOL_BOUNDARY = 0XFFFFF;
const std::string DEFAULT_SYMBOL_FONTFAMILY = "HM Symbol";
static std::atomic<int32_t> spanStringControllerStoreIndex_;

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
enum class RenderingStrategy {
    SINGLE = 0,
    MULTIPLE_COLOR,
    MULTIPLE_OPACITY
};

CalcDimension JSRichEditor::ParseLengthMetrics(const JSRef<JSObject>& obj)
{
    CalcDimension size;
    auto value = 0.0;
    auto valueObj = obj->GetProperty("value");
    if (!valueObj->IsNull() && valueObj->IsNumber()) {
        value = valueObj->ToNumber<float>();
    }
    auto unit = DimensionUnit::VP;
    auto unitObj = obj->GetProperty("unit");
    if (!unitObj->IsNull() && unitObj->IsNumber()) {
        unit = static_cast<DimensionUnit>(unitObj->ToNumber<int32_t>());
    }
    if (value >= 0 && unit != DimensionUnit::PERCENT) {
        size = CalcDimension(value, unit);
    }
    return size;
}
std::optional<NG::MarginProperty> JSRichEditor::ParseMarginAttr(JsiRef<JSVal> marginAttr)
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
        if (marginObj->HasProperty("value")) {
            length = ParseLengthMetrics(marginObj);
            marginProp = NG::ConvertToCalcPaddingProperty(length, length, length, length);
            return marginProp;
        }
        std::optional<CalcDimension> left;
        std::optional<CalcDimension> right;
        std::optional<CalcDimension> top;
        std::optional<CalcDimension> bottom;
        JSViewAbstract::ParseMarginOrPaddingCorner(marginObj, top, bottom, left, right);
        marginProp = NG::ConvertToCalcPaddingProperty(top, bottom, left, right);
    }
    return marginProp;
}

std::optional<NG::BorderRadiusProperty> JSRichEditor::ParseBorderRadiusAttr(JsiRef<JSVal> args)
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
        if (object->HasProperty("value")) {
            NG::BorderRadiusProperty borderRadius;
            borderRadius.SetRadius(ParseLengthMetrics(object));
            borderRadius.multiValued = false;
            prop = borderRadius;
            return prop;
        }
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

void JSRichEditor::Create(const JSCallbackInfo& info)
{
    JSRichEditorBaseController* jsBaseController = nullptr;
    if (info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto controllerObj = paramObject->GetProperty("controller");
        if (!controllerObj->IsUndefined() && !controllerObj->IsNull() && controllerObj->IsObject()) {
            jsBaseController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSRichEditorBaseController>();
        }
    }
    bool isStyledStringMode = jsBaseController && jsBaseController->IsStyledStringMode();
    RichEditorModel::GetInstance()->Create(isStyledStringMode);
    RefPtr<RichEditorBaseControllerBase> controller = RichEditorModel::GetInstance()->GetRichEditorController();
    if (jsBaseController) {
        jsBaseController->SetInstanceId(Container::CurrentId());
        jsBaseController->SetController(controller);
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
    decorationObj->SetProperty<int32_t>("style", textStyleResult.decorationStyle);
    textStyleObj->SetPropertyObject("decoration", decorationObj);

    textStyleObj->SetProperty<double>("lineHeight", textStyleResult.lineHeight);
    textStyleObj->SetProperty<bool>("halfLeading", textStyleResult.halfLeading);
    textStyleObj->SetProperty<double>("letterSpacing", textStyleResult.letterSpacing);
    textStyleObj->SetProperty<std::string>("fontFeature", UnParseFontFeatureSetting(textStyleResult.fontFeature));
    textStyleObj->SetPropertyObject("textShadow", CreateJsTextShadowObjectArray(textStyleResult));
    SetJsTextBackgroundStyle(textStyleObj, textStyleResult);

    return textStyleObj;
}

JSRef<JSArray> JSRichEditor::CreateJsTextShadowObjectArray(const TextStyleResult& textSpanResult)
{
    return CreateJsTextShadowObjectArray(textSpanResult.textShadows);
}

JSRef<JSArray> JSRichEditor::CreateJsTextShadowObjectArray(const std::vector<Shadow>& textShadows)
{
    JSRef<JSArray> textShadowArray = JSRef<JSArray>::New();
    int32_t index = 0;
    for (const auto& it : textShadows) {
        JSRef<JSObject> textShadowObj = JSRef<JSObject>::New();
        textShadowObj->SetProperty<double>("radius", it.GetBlurRadius());
        textShadowObj->SetProperty<std::string>("color", it.GetColor().ToString());
        textShadowObj->SetProperty<double>("offsetX", it.GetOffset().GetX());
        textShadowObj->SetProperty<double>("offsetY", it.GetOffset().GetY());
        textShadowArray->SetValueAt(index, textShadowObj);
        index++;
    }
    return textShadowArray;
}

void JSRichEditor::SetJsTextBackgroundStyle(JSRef<JSObject>& textStyleObj, const TextStyleResult& textSpanResult)
{
    auto textBackgroundStyle = textSpanResult.textBackgroundStyle;
    CHECK_NULL_VOID(textBackgroundStyle.has_value());
    textStyleObj->SetPropertyObject("textBackgroundStyle", CreateJsTextBackgroundStyle(textBackgroundStyle.value()));
}

JSRef<JSObject> JSRichEditor::CreateJsTextBackgroundStyle(const TextBackgroundStyle& style)
{
    JSRef<JSObject> textBackgroundStyleObj = JSRef<JSObject>::New();
    textBackgroundStyleObj->SetProperty<std::string>("color", style.backgroundColor->ColorToString());
    textBackgroundStyleObj->SetProperty<std::string>("radius", style.backgroundRadius->ToString());
    return textBackgroundStyleObj;
}

JSRef<JSObject> JSRichEditor::CreateJSParagraphStyle(const TextStyleResult& textStyleResult)
{
    JSRef<JSObject> paragraphStyleObj = JSRef<JSObject>::New();
    paragraphStyleObj->SetProperty<int32_t>("textAlign", textStyleResult.textAlign);
    JSRef<JSArray> leadingMarginArray = JSRef<JSArray>::New();
    leadingMarginArray->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(textStyleResult.leadingMarginSize[0])));
    leadingMarginArray->SetValueAt(1, JSRef<JSVal>::Make(ToJSValue(textStyleResult.leadingMarginSize[1])));
    paragraphStyleObj->SetPropertyObject("leadingMargin", leadingMarginArray);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        paragraphStyleObj->SetProperty<int32_t>("wordBreak", textStyleResult.wordBreak);
        paragraphStyleObj->SetProperty<int32_t>("lineBreakStrategy", textStyleResult.lineBreakStrategy);
    }
    if (textStyleResult.paragraphSpacing.has_value()) {
        paragraphStyleObj->SetProperty<double>("paragraphSpacing",
            textStyleResult.paragraphSpacing.value().ConvertToFp());
    }
    return paragraphStyleObj;
}

void JSRichEditor::SetJSUrlStyle(const std::u16string& urlAddress, JSRef<JSObject>& resultObj)
{
    CHECK_NULL_VOID(!urlAddress.empty());
    JSRef<JSObject> urlStyleObj = JSRef<JSObject>::New();
    urlStyleObj->SetProperty<std::u16string>("url", urlAddress);
    resultObj->SetPropertyObject("urlStyle", urlStyleObj);
}

JSRef<JSObject> JSRichEditor::CreateJSSymbolSpanStyleResult(const SymbolSpanStyle& symbolSpanStyle)
{
    JSRef<JSObject> symbolSpanStyleObj = JSRef<JSObject>::New();
    symbolSpanStyleObj->SetProperty<std::string>("fontColor", symbolSpanStyle.symbolColor);
    symbolSpanStyleObj->SetProperty<NG::FONT_FEATURES_LIST>("fontFeature", symbolSpanStyle.fontFeature);
    symbolSpanStyleObj->SetProperty<double>("fontSize", symbolSpanStyle.fontSize);
    symbolSpanStyleObj->SetProperty<double>("lineHeight", symbolSpanStyle.lineHeight);
    symbolSpanStyleObj->SetProperty<double>("letterSpacing", symbolSpanStyle.letterSpacing);
    symbolSpanStyleObj->SetProperty<int32_t>("fontWeight", symbolSpanStyle.fontWeight);
    symbolSpanStyleObj->SetProperty<uint32_t>("renderingStrategy", symbolSpanStyle.renderingStrategy);
    symbolSpanStyleObj->SetProperty<uint32_t>("effectStrategy", symbolSpanStyle.effectStrategy);

    return symbolSpanStyleObj;
}

JSRef<JSObject> JSRichEditor::CreateJSValueResource(const RefPtr<ResourceObject>& valueResource)
{
    JSRef<JSObject> valueResourceObj = JSRef<JSObject>::New();
    CHECK_NULL_RETURN(valueResource, valueResourceObj);
    valueResourceObj->SetProperty<std::string>("bundleName", valueResource->GetBundleName());
    valueResourceObj->SetProperty<std::string>("moduleName", valueResource->GetModuleName());
    valueResourceObj->SetProperty<uint32_t>("id", valueResource->GetId());
    valueResourceObj->SetProperty<std::vector<ResourceObjectParams>>("params", valueResource->GetParams());
    valueResourceObj->SetProperty<uint32_t>("type", valueResource->GetType());

    return valueResourceObj;
}

JSRef<JSObject> JSRichEditor::CreateJSLayoutStyle(const ImageStyleResult& imageStyleResult)
{
    JSRef<JSObject> layoutStyleObj = JSRef<JSObject>::New();

    layoutStyleObj->SetProperty<std::string>("borderRadius", imageStyleResult.borderRadius);
    layoutStyleObj->SetProperty<std::string>("margin", imageStyleResult.margin);

    return layoutStyleObj;
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
    imageSpanStyleObj->SetPropertyObject("layoutStyle", CreateJSLayoutStyle(imageStyleResult));

    return imageSpanStyleObj;
}

JSRef<JSObject> JSRichEditor::CreateParagraphStyleResult(const ParagraphInfo& info)
{
    auto obj = JSRef<JSObject>::New();
    obj->SetProperty<int32_t>("textAlign", info.textAlign);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        obj->SetProperty<int32_t>("wordBreak", info.wordBreak);
        obj->SetProperty<int32_t>("lineBreakStrategy", info.lineBreakStrategy);
    }

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
    if (info.paragraphSpacing.has_value()) {
        obj->SetProperty<double>("paragraphSpacing", info.paragraphSpacing.value());
    }
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
    SetJSSpanResultObject(resultObj, resultObject);
    return resultObj;
}

void JSRichEditor::SetJSSpanResultObject(JSRef<JSObject>& resultObj, const ResultObject& resultObject)
{
    if (resultObject.type == SelectSpanType::TYPESPAN) {
        resultObj->SetProperty<std::u16string>("value", resultObject.valueString);
        resultObj->SetProperty<std::u16string>("previewText", resultObject.previewText);
        resultObj->SetPropertyObject("textStyle", CreateJSTextStyleResult(resultObject.textStyle));
        resultObj->SetPropertyObject("paragraphStyle", CreateJSParagraphStyle(resultObject.textStyle));
        SetJSUrlStyle(resultObject.urlAddress, resultObj);
    } else if (resultObject.type == SelectSpanType::TYPESYMBOLSPAN) {
        resultObj->SetProperty<std::u16string>("value", resultObject.valueString);
        resultObj->SetPropertyObject("symbolSpanStyle", CreateJSSymbolSpanStyleResult(resultObject.symbolSpanStyle));
        resultObj->SetPropertyObject("valueResource", CreateJSValueResource(resultObject.valueResource));
    } else if (resultObject.type == SelectSpanType::TYPEIMAGE) {
        if (resultObject.valuePixelMap) {
#ifdef PIXEL_MAP_SUPPORTED
            auto jsPixmap = ConvertPixmap(resultObject.valuePixelMap);
            if (!jsPixmap->IsUndefined()) {
                resultObj->SetPropertyObject("valuePixelMap", jsPixmap);
            }
#endif
        } else {
            resultObj->SetProperty<std::u16string>("valueResourceStr", resultObject.valueString);
        }
        resultObj->SetPropertyObject("imageStyle", CreateJSImageStyleResult(resultObject.imageStyle));
    }
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

void JSRichEditor::SetOnEditingChange(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    JsEventCallback<void(bool)> callback(args.GetExecutionContext(), JSRef<JSFunc>::Cast(args[0]));
    NG::RichEditorModelNG::GetInstance()->SetOnEditingChange(std::move(callback));
}

JSRef<JSVal> JSRichEditor::CreateJSSelectionRange(const SelectionRangeInfo& selectRange)
{
    JSRef<JSObject> selectionRangeObject = JSRef<JSObject>::New();

    JSRef<JSVal> start = JSRef<JSVal>::Make(ToJSValue(selectRange.start_));
    JSRef<JSVal> end = JSRef<JSVal>::Make(ToJSValue(selectRange.end_));

    selectionRangeObject->SetPropertyObject("start", start);
    selectionRangeObject->SetPropertyObject("end", end);
    return JSRef<JSVal>::Cast(selectionRangeObject);
}

void JSRichEditor::SetOnSelectionChange(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsSelectFunc =
        AceType::MakeRefPtr<JsEventFunction<SelectionRangeInfo, 1>>(JSRef<JSFunc>::Cast(args[0]),
        CreateJSSelectionRange);
    auto onSelectionChange =
        [execCtx = args.GetExecutionContext(), func = std::move(jsSelectFunc)](const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        func->Execute(*eventInfo);
    };
    NG::RichEditorModelNG::GetInstance()->SetOnSelectionChange(std::move(onSelectionChange));
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
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onIMEInputComplete");
    };
    RichEditorModel::GetInstance()->SetOnIMEInputComplete(std::move(callback));
}

void JSRichEditor::SetOnDidIMEInput(const JSCallbackInfo& args)
{
    CHECK_NULL_VOID(args[0]->IsFunction());
    auto jsOnDidIMEInputFunc =
        AceType::MakeRefPtr<JsEventFunction<TextRange, 1>>(JSRef<JSFunc>::Cast(args[0]), CreateJsOnDidIMEInput);
    auto callback = [execCtx = args.GetExecutionContext(), func = std::move(jsOnDidIMEInputFunc)](
                        const TextRange& textRange) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->Execute(textRange);
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onDidIMEInput");
    };
    RichEditorModel::GetInstance()->SetOnDidIMEInput(std::move(callback));
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

void JSRichEditor::SetOnWillChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsOnWillChangeFunc = AceType::MakeRefPtr<JsEventFunction<NG::RichEditorChangeValue, 1>>(
        JSRef<JSFunc>::Cast(info[0]), CreateJsOnWillChange);
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsOnWillChangeFunc)](
                        const NG::RichEditorChangeValue& changeValue) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, true);
        auto ret = func->ExecuteWithValue(changeValue);
        if (ret->IsBoolean()) {
            return ret->ToBoolean();
        }
        return true;
    };
    RichEditorModel::GetInstance()->SetOnWillChange(std::move(callback));
}

void JSRichEditor::SetOnDidChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto JsEventCallback =
        AceType::MakeRefPtr<JsCommonEventFunction<NG::RichEditorChangeValue, 2>>(JSRef<JSFunc>::Cast(info[0]));
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(JsEventCallback)](
                        const NG::RichEditorChangeValue& changeValue) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        const auto& rangeBefore = changeValue.GetRangeBefore();
        JSRef<JSObject> rangeBeforeObj = JSRef<JSObject>::New();
        rangeBeforeObj->SetPropertyObject("start", JSRef<JSVal>::Make(ToJSValue(rangeBefore.start)));
        rangeBeforeObj->SetPropertyObject("end", JSRef<JSVal>::Make(ToJSValue(rangeBefore.end)));

        const auto& rangeAfter = changeValue.GetRangeAfter();
        JSRef<JSObject> rangeAfterObj = JSRef<JSObject>::New();
        rangeAfterObj->SetPropertyObject("start", JSRef<JSVal>::Make(ToJSValue(rangeAfter.start)));
        rangeAfterObj->SetPropertyObject("end", JSRef<JSVal>::Make(ToJSValue(rangeAfter.end)));

        JSRef<JSVal> param[2] = { JSRef<JSVal>::Cast(rangeBeforeObj), JSRef<JSVal>::Cast(rangeAfterObj) };
        func->Execute(param);
    };
    RichEditorModel::GetInstance()->SetOnDidChange(std::move(callback));
}

void JSRichEditor::SetOnCut(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    auto jsTextFunc = AceType::MakeRefPtr<JsCitedEventFunction<NG::TextCommonEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), CreateJSTextCommonEvent);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onCut = [execCtx = info.GetExecutionContext(), func = std::move(jsTextFunc), node = targetNode](
                     NG::TextCommonEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onCut");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    RichEditorModel::GetInstance()->SetOnCut(std::move(onCut));
}

void JSRichEditor::SetOnCopy(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    auto jsTextFunc = AceType::MakeRefPtr<JsCitedEventFunction<NG::TextCommonEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), CreateJSTextCommonEvent);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onCopy = [execCtx = info.GetExecutionContext(), func = std::move(jsTextFunc), node = targetNode](
                      NG::TextCommonEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onCopy");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    RichEditorModel::GetInstance()->SetOnCopy(std::move(onCopy));
}

void JSRichEditor::EditMenuOptions(const JSCallbackInfo& info)
{
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    JSViewAbstract::ParseEditMenuOptions(info, onCreateMenuCallback, onMenuItemClick);
    RichEditorModel::GetInstance()->SetSelectionMenuOptions(
        std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

void JSRichEditor::SetOnShare(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    auto jsTextFunc = AceType::MakeRefPtr<JsCitedEventFunction<NG::TextCommonEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), CreateJSTextCommonEvent);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onShare = [execCtx = info.GetExecutionContext(), func = std::move(jsTextFunc), node = targetNode](
                        NG::TextCommonEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onShare");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    RichEditorModel::GetInstance()->SetOnShare(std::move(onShare));
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
    bool supportAvoidance = false;
    if (args.Length() == 2 && args[1]->IsObject()) {  //  2 here refers to the number of parameters
        auto paramObject = JSRef<JSObject>::Cast(args[1]);
        auto isSupportAvoidance = paramObject->GetProperty("supportAvoidance");
        if (!isSupportAvoidance->IsNull() && isSupportAvoidance->IsBoolean()) {
            supportAvoidance = isSupportAvoidance->ToBoolean();
        }
    }
    std::function<void()> buildFunc;
    if (JSTextField::ParseJsCustomKeyboardBuilder(args, 0, buildFunc)) {
        RichEditorModel::GetInstance()->SetCustomKeyboard(std::move(buildFunc), supportAvoidance);
    }
}

JSRef<JSVal> JSRichEditor::CreateJsAboutToIMEInputObj(const NG::RichEditorInsertValue& insertValue)
{
    JSRef<JSObject> aboutToIMEInputObj = JSRef<JSObject>::New();
    aboutToIMEInputObj->SetProperty<int32_t>("insertOffset", insertValue.GetInsertOffset());
    aboutToIMEInputObj->SetProperty<std::u16string>("insertValue", insertValue.GetInsertValue());
    aboutToIMEInputObj->SetProperty<std::u16string>("previewText", insertValue.GetPreviewText());
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
    decorationObj->SetProperty<int32_t>("type", static_cast<int32_t>(textSpanResult.GetTextDecoration()));
    decorationObj->SetProperty<std::string>("color", textSpanResult.GetColor());
    decorationObj->SetProperty<int32_t>("style", static_cast<int32_t>(textSpanResult.GetTextDecorationStyle()));
    textStyleObj->SetProperty<std::string>("fontColor", textSpanResult.GetFontColor());
    textStyleObj->SetProperty<std::string>("fontFeature", UnParseFontFeatureSetting(textSpanResult.GetFontFeatures()));
    textStyleObj->SetProperty<double>("fontSize", textSpanResult.GetFontSize());
    textStyleObj->SetProperty<double>("lineHeight", textSpanResult.GetTextStyle().lineHeight);
    textStyleObj->SetProperty<bool>("halfLeading", textSpanResult.GetTextStyle().halfLeading);
    textStyleObj->SetProperty<double>("letterSpacing", textSpanResult.GetTextStyle().letterSpacing);
    textStyleObj->SetProperty<int32_t>("fontStyle", static_cast<int32_t>(textSpanResult.GetFontStyle()));
    textStyleObj->SetProperty<int32_t>("fontWeight", textSpanResult.GetFontWeight());
    textStyleObj->SetProperty<std::string>("fontFamily", textSpanResult.GetFontFamily());
    textStyleObj->SetPropertyObject("decoration", decorationObj);
    textStyleObj->SetPropertyObject("textShadow", CreateJsTextShadowObjectArray(textSpanResult.GetTextStyle()));
    SetJsTextBackgroundStyle(textStyleObj, textSpanResult.GetTextStyle());
    onIMEInputCompleteObj->SetPropertyObject("spanPosition", spanPositionObj);
    onIMEInputCompleteObj->SetProperty<std::u16string>("value", textSpanResult.GetValue());
    onIMEInputCompleteObj->SetProperty<std::u16string>("previewText", textSpanResult.GetPreviewText());
    onIMEInputCompleteObj->SetPropertyObject("textStyle", textStyleObj);
    onIMEInputCompleteObj->SetPropertyObject("offsetInSpan", offsetInSpan);
    onIMEInputCompleteObj->SetPropertyObject("paragraphStyle", CreateJSParagraphStyle(textSpanResult.GetTextStyle()));
    SetJSUrlStyle(textSpanResult.GetUrlAddress(), onIMEInputCompleteObj);
    return JSRef<JSVal>::Cast(onIMEInputCompleteObj);
}

JSRef<JSVal> JSRichEditor::CreateJsOnDidIMEInput(const TextRange& range)
{
    JSRef<JSObject> rangeObj = JSRef<JSObject>::New();
    rangeObj->SetPropertyObject("start", JSRef<JSVal>::Make(ToJSValue(range.start)));
    rangeObj->SetPropertyObject("end", JSRef<JSVal>::Make(ToJSValue(range.end)));
    return JSRef<JSVal>::Cast(rangeObj);
}

JSRef<JSVal> JSRichEditor::CreateJsAboutToDelet(const NG::RichEditorDeleteValue& deleteValue)
{
    JSRef<JSObject> AboutToDeletObj = JSRef<JSObject>::New();
    AboutToDeletObj->SetProperty<int32_t>("offset", deleteValue.GetOffset());
    AboutToDeletObj->SetProperty<int32_t>(
        "direction", static_cast<int32_t>(deleteValue.GetRichEditorDeleteDirection()));
    AboutToDeletObj->SetProperty<int32_t>("length", deleteValue.GetLength());
    AboutToDeletObj->SetPropertyObject("richEditorDeleteSpans", CreateJSDeleteSpans(deleteValue));
    return JSRef<JSVal>::Cast(AboutToDeletObj);
}

JSRef<JSArray> JSRichEditor::CreateJSDeleteSpans(const NG::RichEditorDeleteValue& deleteValue)
{
    JSRef<JSArray> richEditorDeleteSpans = JSRef<JSArray>::New();
    int32_t index = 0;
    auto list = deleteValue.GetRichEditorDeleteSpans();
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
        SetJSDeleteSpan(spanResultObj, it);
        richEditorDeleteSpans->SetValueAt(index++, spanResultObj);
    }
    return richEditorDeleteSpans;
}

void JSRichEditor::SetJSDeleteSpan(JSRef<JSObject>& spanResultObj, const NG::RichEditorAbstractSpanResult& it)
{
    switch (it.GetType()) {
        case NG::SpanResultType::TEXT: {
            JSRef<JSObject> textStyleObj = JSRef<JSObject>::New();
            CreateTextStyleObj(textStyleObj, it);
            spanResultObj->SetProperty<std::u16string>("value", it.GetValue());
            spanResultObj->SetProperty<std::u16string>("previewText", it.GetPreviewText());
            spanResultObj->SetPropertyObject("textStyle", textStyleObj);
            spanResultObj->SetPropertyObject("paragraphStyle", CreateJSParagraphStyle(it.GetTextStyle()));
            SetJSUrlStyle(it.GetUrlAddress(), spanResultObj);
            break;
        }
        case NG::SpanResultType::IMAGE: {
            JSRef<JSObject> imageStyleObj = JSRef<JSObject>::New();
            CreateImageStyleObj(imageStyleObj, spanResultObj, it);
            JSRef<JSObject> layoutStyleObj = JSRef<JSObject>::New();
            layoutStyleObj->SetProperty<std::string>("borderRadius", it.GetBorderRadius());
            layoutStyleObj->SetProperty<std::string>("margin", it.GetMargin());
            imageStyleObj->SetPropertyObject("layoutStyle", layoutStyleObj);
            spanResultObj->SetPropertyObject("imageStyle", imageStyleObj);
            break;
        }
        case NG::SpanResultType::SYMBOL: {
            spanResultObj->SetProperty<std::string>("value", it.GetValueString());
            spanResultObj->SetPropertyObject(
                "symbolSpanStyle", CreateJSSymbolSpanStyleResult(it.GetSymbolSpanStyle()));
            spanResultObj->SetPropertyObject("valueResource", CreateJSValueResource(it.GetValueResource()));
            break;
        }
        default:
            break;
    }
}

void JSRichEditor::SetChangeTextSpans(
    JSRef<JSArray>& jsArray, const std::vector<NG::RichEditorAbstractSpanResult>& spanList)
{
    int32_t index = 0;
    for (const auto& it : spanList) {
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
            case NG::SpanResultType::TEXT:
                SetTextChangeSpanResult(spanResultObj, it);
                break;
            case NG::SpanResultType::IMAGE:
                SetImageChangeSpanResult(spanResultObj, it);
                break;
            case NG::SpanResultType::SYMBOL:
                SetSymbolChangeSpanResult(spanResultObj, it);
                break;
            default:
                break;
        }
        jsArray->SetValueAt(index++, spanResultObj);
    }
}

void JSRichEditor::SetTextChangeSpanResult(JSRef<JSObject>& resultObj,
    const NG::RichEditorAbstractSpanResult& spanResult)
{
    JSRef<JSObject> textStyleObj = JSRef<JSObject>::New();
    CreateTextStyleObj(textStyleObj, spanResult);
    resultObj->SetProperty<std::u16string>("value", spanResult.GetValue());
    resultObj->SetProperty<std::u16string>("previewText", spanResult.GetPreviewText());
    resultObj->SetPropertyObject("textStyle", textStyleObj);
    resultObj->SetPropertyObject("paragraphStyle", CreateJSParagraphStyle(spanResult.GetTextStyle()));
    SetJSUrlStyle(spanResult.GetUrlAddress(), resultObj);
}

void JSRichEditor::SetSymbolChangeSpanResult(JSRef<JSObject>& resultObj,
    const NG::RichEditorAbstractSpanResult& spanResult)
{
    resultObj->SetProperty<std::string>("value", spanResult.GetValueString());
    resultObj->SetPropertyObject("symbolSpanStyle", CreateJSSymbolSpanStyleResult(spanResult.GetSymbolSpanStyle()));
    resultObj->SetPropertyObject("valueResource", CreateJSValueResource(spanResult.GetValueResource()));
    resultObj->SetPropertyObject("paragraphStyle", CreateJSParagraphStyle(spanResult.GetTextStyle()));
}

void JSRichEditor::SetImageChangeSpanResult(JSRef<JSObject>& resultObj,
    const NG::RichEditorAbstractSpanResult& spanResult)
{
    auto valuePixelMap = spanResult.GetValuePixelMap();
    auto returnWidth = spanResult.GetSizeWidth();
    auto returnHeight = spanResult.GetSizeHeight();
    if (valuePixelMap) {
#ifdef PIXEL_MAP_SUPPORTED
        if (NearZero(returnWidth) || NearZero(returnHeight)) {
            returnWidth = valuePixelMap->GetWidth();
            returnHeight = valuePixelMap->GetHeight();
        }
        auto jsPixmap = ConvertPixmap(valuePixelMap);
        if (!jsPixmap->IsUndefined()) {
            resultObj->SetPropertyObject("valuePixelMap", jsPixmap);
        }
#endif
    } else {
        resultObj->SetProperty<std::string>("valueResourceStr", spanResult.GetValueResourceStr());
    }
    ImageStyleResult imageStyleResult;
    imageStyleResult.size[0] = static_cast<double>(returnWidth);
    imageStyleResult.size[1] = static_cast<double>(returnHeight);
    imageStyleResult.verticalAlign = static_cast<int32_t>(spanResult.GetVerticalAlign());
    imageStyleResult.objectFit = static_cast<int32_t>(spanResult.GetObjectFit());
    imageStyleResult.borderRadius = spanResult.GetBorderRadius();
    imageStyleResult.margin = spanResult.GetMargin();
    resultObj->SetPropertyObject("imageStyle", CreateJSImageStyleResult(imageStyleResult));
}

JSRef<JSVal> JSRichEditor::CreateJsOnWillChange(const NG::RichEditorChangeValue& changeValue)
{
    JSRef<JSObject> OnWillChangeObj = JSRef<JSObject>::New();

    const auto& rangeBefore = changeValue.GetRangeBefore();
    JSRef<JSObject> rangeBeforeObj = JSRef<JSObject>::New();
    rangeBeforeObj->SetPropertyObject("start", JSRef<JSVal>::Make(ToJSValue(rangeBefore.start)));
    rangeBeforeObj->SetPropertyObject("end", JSRef<JSVal>::Make(ToJSValue(rangeBefore.end)));
    OnWillChangeObj->SetPropertyObject("rangeBefore", rangeBeforeObj);

    JSRef<JSArray> replacedSpans = JSRef<JSArray>::New();
    SetChangeTextSpans(replacedSpans, changeValue.GetRichEditorReplacedSpans());
    OnWillChangeObj->SetPropertyObject("replacedSpans", replacedSpans);

    JSRef<JSArray> replacedImageSpans = JSRef<JSArray>::New();
    SetChangeTextSpans(replacedImageSpans, changeValue.GetRichEditorReplacedImageSpans());
    OnWillChangeObj->SetPropertyObject("replacedImageSpans", replacedImageSpans);

    JSRef<JSArray> replacedSymbolSpans = JSRef<JSArray>::New();
    SetChangeTextSpans(replacedSymbolSpans, changeValue.GetRichEditorReplacedSymbolSpans());
    OnWillChangeObj->SetPropertyObject("replacedSymbolSpans", replacedSymbolSpans);

    return JSRef<JSVal>::Cast(OnWillChangeObj);
}

JSRef<JSVal> JSRichEditor::CreateJsOnDidChange(const std::vector<NG::RichEditorAbstractSpanResult>& spanList)
{
    JSRef<JSArray> richEditorReplacedSpans = JSRef<JSArray>::New();
    SetChangeTextSpans(richEditorReplacedSpans, spanList);
    return JSRef<JSVal>::Cast(richEditorReplacedSpans);
}

void JSRichEditor::CreateTextStyleObj(JSRef<JSObject>& textStyleObj, const NG::RichEditorAbstractSpanResult& spanResult)
{
    JSRef<JSObject> decorationObj = JSRef<JSObject>::New();
    decorationObj->SetProperty<int32_t>("type", (int32_t)(spanResult.GetTextDecoration()));
    decorationObj->SetProperty<std::string>("color", spanResult.GetColor());
    decorationObj->SetProperty<int32_t>("style", (int32_t)(spanResult.GetTextDecorationStyle()));
    textStyleObj->SetProperty<std::string>("fontColor", spanResult.GetFontColor());
    textStyleObj->SetProperty<std::string>("fontFeature", UnParseFontFeatureSetting(spanResult.GetFontFeatures()));
    textStyleObj->SetProperty<double>("fontSize", spanResult.GetFontSize());
    textStyleObj->SetProperty<double>("lineHeight", spanResult.GetTextStyle().lineHeight);
    textStyleObj->SetProperty<bool>("halfLeading", spanResult.GetTextStyle().halfLeading);
    textStyleObj->SetProperty<double>("letterSpacing", spanResult.GetTextStyle().letterSpacing);
    textStyleObj->SetProperty<int32_t>("fontStyle", static_cast<int32_t>(spanResult.GetFontStyle()));
    textStyleObj->SetProperty<int32_t>("fontWeight", spanResult.GetFontWeight());
    textStyleObj->SetProperty<std::string>("fontFamily", spanResult.GetFontFamily());
    textStyleObj->SetPropertyObject("decoration", decorationObj);
    textStyleObj->SetPropertyObject("textShadow", CreateJsTextShadowObjectArray(spanResult.GetTextStyle()));
    SetJsTextBackgroundStyle(textStyleObj, spanResult.GetTextStyle());
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
    const int32_t builderParamIndex = 1;
    CHECK_NULL_VOID(info.Length() > builderParamIndex);
    RefPtr<JsFunction> builderFunc = nullptr;
    if (!info[1]->IsUndefined() && info[1]->IsObject()) {
        JSRef<JSObject> menuObj = JSRef<JSObject>::Cast(info[1]);
        auto builder = menuObj->GetProperty("builder");
        if (builder->IsFunction()) {
            builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
        }
    }

    // responseType
    NG::TextResponseType responseType = NG::TextResponseType::LONG_PRESS;
    if (info.Length() >= 3 && info[2]->IsNumber()) {
        auto response = info[2]->ToNumber<int32_t>();
        responseType = static_cast<NG::TextResponseType>(response);
    }
    std::function<void()> buildFunc = nullptr;
    if (builderFunc) {
        buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("BindSelectionMenu");
            func->Execute();
        };
    }
    NG::SelectMenuParam menuParam;
    const int32_t requiredParamCount = 3;
    if (info.Length() > requiredParamCount && info[requiredParamCount]->IsObject()) {
        JSRef<JSObject> menuOptions = info[requiredParamCount];
        JSText::ParseMenuParam(info, menuOptions, menuParam);
        auto menuType = menuOptions->GetProperty("menuType");
        bool isPreviewMenu = menuType->IsNumber() && menuType->ToNumber<int32_t>() == 1;
        bool bindImagePreviewMenu = isPreviewMenu && responseType == NG::TextResponseType::LONG_PRESS;
        if (bindImagePreviewMenu) {
            RichEditorModel::GetInstance()->SetPreviewMenuParam(editorType, buildFunc, menuParam);
            return;
        }
    }
    CHECK_NULL_VOID(buildFunc);
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
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onPaste = [execCtx = info.GetExecutionContext(), func = std::move(jsTextFunc), node = targetNode](
                       NG::TextCommonEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onPaste");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onPaste");
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

void JSRichEditor::JsEnablePreviewText(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto tmpInfo = info[0];
    if (!tmpInfo->IsBoolean()) {
        RichEditorModel::GetInstance()->SetSupportPreviewText(true);
        return;
    }
    auto enable = tmpInfo->ToBoolean();
    RichEditorModel::GetInstance()->SetSupportPreviewText(enable);
}

void JSRichEditor::SetPlaceholder(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto pipelineContext = PipelineBase::GetCurrentContext();
    if (!pipelineContext) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "pipelineContext is null");
        return;
    }
    std::u16string placeholderValue;
    PlaceholderOptions options;
    JSContainerBase::ParseJsString(info[0], placeholderValue);
    options.value = placeholderValue;
    Font font;
    if (info.Length() > 1 && info[1]->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(info[1]);
        auto fontObject = object->GetProperty("font");
        if (fontObject->IsObject()) {
            ParseJsFont(fontObject, font);
        }
        JSRef<JSVal> colorVal = object->GetProperty("fontColor");
        Color fontColor;
        if (!colorVal->IsNull() && JSContainerBase::ParseJsColor(colorVal, fontColor)) {
            options.fontColor = fontColor;
        }
    }
    auto textTheme = pipelineContext->GetTheme<TextTheme>();
    TextStyle textStyle = textTheme ? textTheme->GetTextStyle() : TextStyle();
    options.fontSize = font.fontSize.value_or(textStyle.GetFontSize());
    options.fontFamilies = !font.fontFamilies.empty() ? font.fontFamilies : textStyle.GetFontFamilies();
    options.fontWeight = font.fontWeight.value_or(textStyle.GetFontWeight());
    options.fontStyle = font.fontStyle.value_or(textStyle.GetFontStyle());
    if (!options.fontColor.has_value()) {
        Color fontColor;
        auto richEditorTheme = pipelineContext->GetTheme<NG::RichEditorTheme>();
        options.fontColor = richEditorTheme ? richEditorTheme->GetPlaceholderColor() : fontColor;
    }
    RichEditorModel::GetInstance()->SetPlaceholder(options);
}

void JSRichEditor::ParseJsFont(const JSRef<JSObject>& fontObject, Font& font)
{
    if (fontObject->IsUndefined()) {
        return;
    }
    JSRef<JSVal> fontSize = fontObject->GetProperty("size");
    CalcDimension size;
    if (!fontSize->IsNull() && JSContainerBase::ParseJsDimensionFpNG(fontSize, size) && !size.IsNegative() &&
        size.Unit() != DimensionUnit::PERCENT) {
        font.fontSize = size;
    } else if (size.IsNegative() || size.Unit() == DimensionUnit::PERCENT) {
        auto theme = JSContainerBase::GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        size = theme->GetTextStyle().GetFontSize();
        font.fontSize = size;
    }

    JSRef<JSVal> fontStyle = fontObject->GetProperty("style");
    if (!fontStyle->IsNull() && fontStyle->IsNumber()) {
        font.fontStyle = static_cast<FontStyle>(fontStyle->ToNumber<int32_t>());
    }

    JSRef<JSVal> fontWeight = fontObject->GetProperty("weight");
    if (!fontWeight->IsNull()) {
        std::string weight;
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        } else {
            JSContainerBase::ParseJsString(fontWeight, weight);
        }
        font.fontWeight = ConvertStrToFontWeight(weight);
    }

    JSRef<JSVal> fontFamily = fontObject->GetProperty("family");
    if (!fontFamily->IsNull()) {
        std::vector<std::string> fontFamilies;
        if (JSContainerBase::ParseJsFontFamilies(fontFamily, fontFamilies)) {
            font.fontFamilies = fontFamilies;
        }
    }
}

void JSRichEditor::JsDataDetectorConfig(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }

    TextDetectConfig textDetectConfig;
    if (!ParseDataDetectorConfig(info, textDetectConfig)) {
        return;
    }
    RichEditorModel::GetInstance()->SetTextDetectConfig(textDetectConfig);
}

void JSRichEditor::SetCaretColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Info length error");
        return;
    }
    Color color;
    JSRef<JSVal> colorVal = info[0];
    if (!ParseJsColor(colorVal, color)) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetThemeManager()->GetTheme<NG::RichEditorTheme>();
        CHECK_NULL_VOID(theme);
        color = theme->GetCaretColor();
    }
    RichEditorModel::GetInstance()->SetCaretColor(color);
}

void JSRichEditor::SetSelectedBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Info length error");
        return;
    }
    Color selectedColor;
    JSRef<JSVal> colorVal = info[0];
    if (!ParseJsColor(colorVal, selectedColor)) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetThemeManager()->GetTheme<NG::RichEditorTheme>();
        CHECK_NULL_VOID(theme);
        selectedColor = theme->GetSelectedBackgroundColor();
    }
    RichEditorModel::GetInstance()->SetSelectedBackgroundColor(selectedColor);
}

void JSRichEditor::SetEnterKeyType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto action = info[0];
    if (action->IsUndefined()) {
        RichEditorModel::GetInstance()->SetEnterKeyType(TextInputAction::UNSPECIFIED);
        return;
    }
    if (!action->IsNumber()) {
        return;
    }
    TextInputAction textInputAction = CastToTextInputAction(action->ToNumber<int32_t>());
    RichEditorModel::GetInstance()->SetEnterKeyType(textInputAction);
}

Local<JSValueRef> JSRichEditor::JsKeepEditableState(panda::JsiRuntimeCallInfo* info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo =
        static_cast<NG::TextFieldCommonEvent*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(
            info->GetVM(), 0));
    if (eventInfo) {
        eventInfo->SetKeepEditable(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

void JSRichEditor::CreateJsRichEditorCommonEvent(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsTextFunc =
        AceType::MakeRefPtr<JsCommonEventFunction<NG::TextFieldCommonEvent, 2>>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsTextFunc), node = targetNode](
                        int32_t key, NG::TextFieldCommonEvent& event) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onSubmit");
        PipelineContext::SetCallBackNode(node);
        JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
        objectTemplate->SetInternalFieldCount(2);
        JSRef<JSObject> object = objectTemplate->NewInstance();
        object->SetProperty<std::u16string>("text", event.GetText());
        object->SetPropertyObject("keepEditableState", JSRef<JSFunc>::New<FunctionCallback>(JsKeepEditableState));
        object->Wrap<NG::TextFieldCommonEvent>(&event);
        JSRef<JSVal> keyEvent = JSRef<JSVal>::Make(ToJSValue(key));
        JSRef<JSVal> dataObject = JSRef<JSVal>::Cast(object);
        JSRef<JSVal> param[2] = { keyEvent, dataObject };
        func->Execute(param);
    };
    RichEditorModel::GetInstance()->SetOnSubmit(std::move(callback));
}

void JSRichEditor::SetOnSubmit(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    CreateJsRichEditorCommonEvent(info);
}

void JSRichEditor::SetEnableKeyboardOnFocus(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info.Length() > 0);
    auto jsValue = info[0];
    if (jsValue->IsUndefined() || !jsValue->IsBoolean()) {
        RichEditorModel::GetInstance()->SetRequestKeyboardOnFocus(true);
        return;
    }
    RichEditorModel::GetInstance()->SetRequestKeyboardOnFocus(jsValue->ToBoolean());
}

void JSRichEditor::SetEnableHapticFeedback(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info.Length() > 0);
    auto jsValue = info[0];
    if (jsValue->IsUndefined() || !jsValue->IsBoolean()) {
        RichEditorModel::GetInstance()->SetEnableHapticFeedback(true);
        return;
    }
    RichEditorModel::GetInstance()->SetEnableHapticFeedback(jsValue->ToBoolean());
}

void JSRichEditor::SetBarState(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info.Length() > 0);
    auto jsValue = info[0];
    CHECK_NULL_VOID(!jsValue->IsUndefined() && jsValue->IsNumber());
    int32_t barState = jsValue->ToNumber<int32_t>();
    CHECK_NULL_VOID(barState >= static_cast<int32_t>(DisplayMode::OFF));
    CHECK_NULL_VOID(barState <= static_cast<int32_t>(DisplayMode::ON));
    RichEditorModel::GetInstance()->SetBarState(static_cast<DisplayMode>(barState));
}

void JSRichEditor::SetMaxLength(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    if (jsValue->IsUndefined()) {
        RichEditorModel::GetInstance()->ResetMaxLength();
        return;
    } else if (!jsValue->IsNumber()) {
        RichEditorModel::GetInstance()->ResetMaxLength();
        return;
    }
    int32_t maxLength = jsValue->ToNumber<int32_t>();
    if (std::isinf(jsValue->ToNumber<float>())) {
        maxLength = INT32_MAX;
    }
    if (GreatOrEqual(maxLength, 0)) {
        RichEditorModel::GetInstance()->SetMaxLength(maxLength);
    } else {
        RichEditorModel::GetInstance()->ResetMaxLength();
    }
}

void JSRichEditor::SetMaxLines(const JSCallbackInfo& info)
{
    auto normalMaxLines = Infinity<uint32_t>();
    auto isValid = info.Length() >= 1 && info[0]->IsNumber() && info[0]->ToNumber<int32_t>() > 0;
    if (isValid) {
        normalMaxLines = info[0]->ToNumber<uint32_t>();
    }
    RichEditorModel::GetInstance()->SetMaxLines(normalMaxLines);
}

void JSRichEditor::SetEnableAutoSpacing(const JSCallbackInfo& info)
{
    bool enabled = false;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        enabled = info[0]->ToBoolean();
    }
    RichEditorModel::GetInstance()->SetEnableAutoSpacing(enabled);
}

void JSRichEditor::SetStopBackPress(const JSCallbackInfo& info)
{
    bool isStopBackPress = true;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        isStopBackPress = info[0]->ToBoolean();
    }
    RichEditorModel::GetInstance()->SetStopBackPress(isStopBackPress);
}

void JSRichEditor::SetUndoStyle(const JSCallbackInfo& info)
{
    bool enable = false;
    if (info.Length() >= 1 && info[0]->IsNumber()) {
        auto undoStyle = info[0]->ToNumber<int32_t>();
        enable = (undoStyle == static_cast<int32_t>(UndoStyle::KEEP_STYLE));
    }
    RichEditorModel::GetInstance()->SetSupportStyledUndo(enable);
}

void JSRichEditor::SetKeyboardAppearance(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        return;
    }
    auto keyboardAppearance = info[0]->ToNumber<int32_t>();
    if (keyboardAppearance < static_cast<int32_t>(KeyboardAppearance::NONE_IMMERSIVE) ||
        keyboardAppearance > static_cast<int32_t>(KeyboardAppearance::DARK_IMMERSIVE)) {
        RichEditorModel::GetInstance()->SetKeyboardAppearance(KeyboardAppearance::NONE_IMMERSIVE);
        return;
    }
    RichEditorModel::GetInstance()->
        SetKeyboardAppearance(static_cast<KeyboardAppearance>(keyboardAppearance));
}

void JSRichEditor::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichEditor>::Declare("RichEditor");
    JSClass<JSRichEditor>::StaticMethod("create", &JSRichEditor::Create);
    JSClass<JSRichEditor>::StaticMethod("onReady", &JSRichEditor::SetOnReady);
    JSClass<JSRichEditor>::StaticMethod("onSelect", &JSRichEditor::SetOnSelect);
    JSClass<JSRichEditor>::StaticMethod("onSelectionChange", &JSRichEditor::SetOnSelectionChange);
    JSClass<JSRichEditor>::StaticMethod("aboutToIMEInput", &JSRichEditor::SetAboutToIMEInput);
    JSClass<JSRichEditor>::StaticMethod("onIMEInputComplete", &JSRichEditor::SetOnIMEInputComplete);
    JSClass<JSRichEditor>::StaticMethod("onDidIMEInput", &JSRichEditor::SetOnDidIMEInput);
    JSClass<JSRichEditor>::StaticMethod("aboutToDelete", &JSRichEditor::SetAboutToDelete);
    JSClass<JSRichEditor>::StaticMethod("onDeleteComplete", &JSRichEditor::SetOnDeleteComplete);
    JSClass<JSRichEditor>::StaticMethod("customKeyboard", &JSRichEditor::SetCustomKeyboard);
    JSClass<JSRichEditor>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRichEditor>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRichEditor>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRichEditor>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRichEditor>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSRichEditor>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRichEditor>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSRichEditor>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRichEditor>::StaticMethod("clip", &JSRichEditor::JsClip);
    JSClass<JSRichEditor>::StaticMethod("focusable", &JSRichEditor::JsFocusable);
    JSClass<JSRichEditor>::StaticMethod("copyOptions", &JSRichEditor::SetCopyOptions);
    JSClass<JSRichEditor>::StaticMethod("bindSelectionMenu", &JSRichEditor::BindSelectionMenu);
    JSClass<JSRichEditor>::StaticMethod("onPaste", &JSRichEditor::SetOnPaste);
    JSClass<JSRichEditor>::StaticMethod("enableDataDetector", &JSRichEditor::JsEnableDataDetector);
    JSClass<JSRichEditor>::StaticMethod("enablePreviewText", &JSRichEditor::JsEnablePreviewText);
    JSClass<JSRichEditor>::StaticMethod("dataDetectorConfig", &JSRichEditor::JsDataDetectorConfig);
    JSClass<JSRichEditor>::StaticMethod("placeholder", &JSRichEditor::SetPlaceholder);
    JSClass<JSRichEditor>::StaticMethod("caretColor", &JSRichEditor::SetCaretColor);
    JSClass<JSRichEditor>::StaticMethod("selectedBackgroundColor", &JSRichEditor::SetSelectedBackgroundColor);
    JSClass<JSRichEditor>::StaticMethod("onEditingChange", &JSRichEditor::SetOnEditingChange);
    JSClass<JSRichEditor>::StaticMethod("enterKeyType", &JSRichEditor::SetEnterKeyType);
    JSClass<JSRichEditor>::StaticMethod("onSubmit", &JSRichEditor::SetOnSubmit);
    JSClass<JSRichEditor>::StaticMethod("onWillChange", &JSRichEditor::SetOnWillChange);
    JSClass<JSRichEditor>::StaticMethod("onDidChange", &JSRichEditor::SetOnDidChange);
    JSClass<JSRichEditor>::StaticMethod("onCut", &JSRichEditor::SetOnCut);
    JSClass<JSRichEditor>::StaticMethod("onCopy", &JSRichEditor::SetOnCopy);
    JSClass<JSRichEditor>::StaticMethod("onShare", &JSRichEditor::SetOnShare);
    JSClass<JSRichEditor>::StaticMethod("editMenuOptions", &JSRichEditor::EditMenuOptions);
    JSClass<JSRichEditor>::StaticMethod("enableKeyboardOnFocus", &JSRichEditor::SetEnableKeyboardOnFocus);
    JSClass<JSRichEditor>::StaticMethod("enableHapticFeedback", &JSRichEditor::SetEnableHapticFeedback);
    JSClass<JSRichEditor>::StaticMethod("barState", &JSRichEditor::SetBarState);
    JSClass<JSRichEditor>::StaticMethod("maxLength", &JSRichEditor::SetMaxLength);
    JSClass<JSRichEditor>::StaticMethod("maxLines", &JSRichEditor::SetMaxLines);
    JSClass<JSRichEditor>::StaticMethod("enableAutoSpacing", &JSRichEditor::SetEnableAutoSpacing);
    JSClass<JSRichEditor>::StaticMethod("stopBackPress", &JSRichEditor::SetStopBackPress);
    JSClass<JSRichEditor>::StaticMethod("keyboardAppearance", &JSRichEditor::SetKeyboardAppearance);
    JSClass<JSRichEditor>::StaticMethod("undoStyle", &JSRichEditor::SetUndoStyle);
    JSClass<JSRichEditor>::InheritAndBind<JSViewAbstract>(globalObj);
}

ImageSpanAttribute JSRichEditorController::ParseJsImageSpanAttribute(JSRef<JSObject> imageAttribute)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
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
    auto layoutStyleObject = JSObjectCast(imageAttribute->GetProperty("layoutStyle"));
    if (!layoutStyleObject->IsUndefined()) {
        auto marginAttr = layoutStyleObject->GetProperty("margin");
        imageStyle.marginProp = JSRichEditor::ParseMarginAttr(marginAttr);
        updateSpanStyle_.marginProp = imageStyle.marginProp;
        auto borderRadiusAttr = layoutStyleObject->GetProperty("borderRadius");
        imageStyle.borderRadius = JSRichEditor::ParseBorderRadiusAttr(borderRadiusAttr);
        updateSpanStyle_.borderRadius = imageStyle.borderRadius;
    }
    return imageStyle;
}

void JSRichEditorController::ParseJsCustomSymbolStyle(const JSRef<JSVal>& jsValue, TextStyle& style, uint32_t& symbolId)
{
    std::vector<std::string> fontFamilies;
    if (symbolId > SYSTEM_SYMBOL_BOUNDARY) {
        JSContainerBase::ParseJsSymbolCustomFamilyNames(fontFamilies, jsValue);
        style.SetSymbolType(SymbolType::CUSTOM);
        style.SetFontFamilies(fontFamilies);
    } else {
        style.SetSymbolType(SymbolType::SYSTEM);
        fontFamilies.push_back(DEFAULT_SYMBOL_FONTFAMILY);
        style.SetFontFamilies(fontFamilies);
    }
}

void JSRichEditorController::ParseJsSymbolSpanStyle(
    const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    JSRef<JSVal> fontColor = styleObject->GetProperty("fontColor");
    COLOR_MODE_LOCK(GetColorMode());
    std::vector<Color> symbolColor;
    if (!fontColor->IsNull() && JSContainerBase::ParseJsSymbolColor(fontColor, symbolColor)) {
        updateSpanStyle.updateSymbolColor = symbolColor;
        style.SetSymbolColorList(symbolColor);
    }
    JSRef<JSVal> fontSize = styleObject->GetProperty("fontSize");
    CalcDimension size;
    if (!fontSize->IsNull() && JSContainerBase::ParseJsDimensionFpNG(fontSize, size, false) &&
        !FontSizeRangeIsNegative(size) && size.Unit() != DimensionUnit::PERCENT) {
        updateSpanStyle.updateSymbolFontSize = size;
        style.SetFontSize(size);
    } else if (FontSizeRangeIsNegative(size) || size.Unit() == DimensionUnit::PERCENT) {
        auto theme = JSContainerBase::GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        size = theme->GetTextStyle().GetFontSize();
        style.SetFontSize(size);
    }
    JSRef<JSVal> fontWeight = styleObject->GetProperty("fontWeight");
    std::string weight;
    if (!fontWeight->IsNull() && (fontWeight->IsNumber() || JSContainerBase::ParseJsString(fontWeight, weight))) {
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        }
        updateSpanStyle.updateSymbolFontWeight = ConvertStrToFontWeight(weight);
        style.SetFontWeight(ConvertStrToFontWeight(weight));
    }
    JSRef<JSVal> renderingStrategy = styleObject->GetProperty("renderingStrategy");
    uint32_t symbolRenderStrategy;
    if (!renderingStrategy->IsNull() && JSContainerBase::ParseJsInteger(renderingStrategy, symbolRenderStrategy)) {
        if (symbolRenderStrategy < 0 ||
            symbolRenderStrategy > static_cast<uint32_t>(RenderingStrategy::MULTIPLE_OPACITY)) {
            symbolRenderStrategy = static_cast<uint32_t>(RenderingStrategy::SINGLE);
        }
        updateSpanStyle.updateSymbolRenderingStrategy = symbolRenderStrategy;
        style.SetRenderStrategy(symbolRenderStrategy);
    }
    JSRef<JSVal> effectStrategy = styleObject->GetProperty("effectStrategy");
    uint32_t symbolEffectStrategy;
    if (!effectStrategy->IsNull() && JSContainerBase::ParseJsInteger(effectStrategy, symbolEffectStrategy)) {
        updateSpanStyle.updateSymbolEffectStrategy = 0;
        style.SetEffectStrategy(0);
    }
}

void JSRichEditorBaseController::ParseTextUrlStyle(const JSRef<JSObject>& jsObject,
    std::optional<std::u16string>& urlAddressOpt)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    JSRef<JSObject> urlStyleObj = JSObjectCast(jsObject->GetProperty("urlStyle"));
    CHECK_NULL_VOID(!urlStyleObj->IsUndefined());
 
    JSRef<JSVal> urlObj = urlStyleObj->GetProperty("url");
    std::u16string urlAddress;
    CHECK_NULL_VOID(JSContainerBase::ParseJsString(urlObj, urlAddress));
    urlAddressOpt = urlAddress;
}

void JSRichEditorController::ParseUserGesture(
    const JSCallbackInfo& args, UserGestureOptions& gestureOption, const std::string& spanType)
{
    if (args.Length() < 2) {
        return;
    }
    if (!args[1]->IsObject()) {
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(args[1]);
    auto gesture = object->GetProperty("gesture");
    if (!gesture->IsUndefined() && gesture->IsObject()) {
        auto gestureObj = JSRef<JSObject>::Cast(gesture);
        ParseUserClickEvent(args, gestureObj, gestureOption, spanType);
        auto onLongPressFunc = gestureObj->GetProperty("onLongPress");
        if ((onLongPressFunc->IsUndefined() && IsDisableEventVersion()) || !onLongPressFunc->IsFunction()) {
            gestureOption.onLongPress = nullptr;
            return;
        }
        auto jsLongPressFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(onLongPressFunc));
        auto* targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto onLongPress = [execCtx = args.GetExecutionContext(), func = jsLongPressFunc, spanTypeInner = spanType,
                                node =  AceType::WeakClaim(targetNode)](GestureEvent& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT(spanTypeInner + ".onLongPress");
            func->Execute(info);
        };
        gestureOption.onLongPress = std::move(onLongPress);
    }
}

void JSRichEditorController::ParseUserMouseOption(
    const JSCallbackInfo& args, UserMouseOptions& mouseOption, const std::string& spanType)
{
    if (args.Length() < 2) {
        return;
    }
    if (!args[1]->IsObject()) {
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(args[1]);
    auto onHoverFunc = object->GetProperty("onHover");
    if (onHoverFunc->IsUndefined() || !onHoverFunc->IsFunction()) {
        mouseOption.onHover = nullptr;
        return;
    }
    RefPtr<JsHoverFunction> jsOnHoverFunc = AceType::MakeRefPtr<JsHoverFunction>(JSRef<JSFunc>::Cast(onHoverFunc));
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onHover = [execCtx = args.GetExecutionContext(), func = jsOnHoverFunc, spanTypeInner = spanType,
                       node = AceType::WeakClaim(targetNode)](bool isHover, HoverInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        PipelineContext::SetCallBackNode(node);
        ACE_SCORING_EVENT(spanTypeInner + ".onHover");
        func->HoverExecute(isHover, info);
    };
    mouseOption.onHover = std::move(onHover);
}

void JSRichEditorController::ParseUserClickEvent(const JSCallbackInfo& args, const JSRef<JSObject>& gestureObj,
    UserGestureOptions& gestureOption, const std::string& spanType)
{
    CHECK_NULL_VOID(!gestureObj->IsUndefined());
    auto clickFunc = gestureObj->GetProperty("onClick");
    if ((clickFunc->IsUndefined() && IsDisableEventVersion()) || !clickFunc->IsFunction()) {
        gestureOption.onClick = nullptr;
    } else {
        auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(clickFunc));
        auto* targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto onClick = [execCtx = args.GetExecutionContext(), func = jsOnClickFunc, spanTypeInner = spanType,
                            node = AceType::WeakClaim(targetNode)](GestureEvent& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT(spanTypeInner + ".onClick");
            PipelineContext::SetCallBackNode(node);
            func->Execute(info);
        };
        gestureOption.onClick = std::move(onClick);
    }
    auto onDoubleClickFunc = gestureObj->GetProperty("onDoubleClick");
    if ((onDoubleClickFunc->IsUndefined() && IsDisableEventVersion()) || !onDoubleClickFunc->IsFunction()) {
        gestureOption.onDoubleClick = nullptr;
    } else {
        auto jsDoubleClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(onDoubleClickFunc));
        auto* targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto onDoubleClick = [execCtx = args.GetExecutionContext(), func = jsDoubleClickFunc, spanTypeInner = spanType,
                                node =  AceType::WeakClaim(targetNode)](GestureEvent& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT(spanTypeInner + ".onDoubleClick");
            func->Execute(info);
        };
        gestureOption.onDoubleClick = std::move(onDoubleClick);
    }
}

void JSRichEditorController::AddImageSpan(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
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
        if (!CheckImageSource(assetSrc)) {
            TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "CheckImageSource failed");
            args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(-1)));
            return;
        }
    }
    if (args.Length() > 1 && args[1]->IsObject()) {
        JSRef<JSObject> imageObject = JSRef<JSObject>::Cast(args[1]);

        JSRef<JSVal> offset = imageObject->GetProperty("offset");
        int32_t imageOffset = 0;
        if (!offset->IsNull() && JSContainerBase::ParseJsInt32(offset, imageOffset)) {
            options.offset = imageOffset > 0 ? imageOffset : 0;
        }
        auto imageAttribute = JSObjectCast(imageObject->GetProperty("imageStyle"));
        if (!imageAttribute->IsUndefined()) {
            ImageSpanAttribute imageStyle = ParseJsImageSpanAttribute(imageAttribute);
            options.imageAttribute = imageStyle;
        }
        UserGestureOptions gestureOption;
        ParseUserGesture(args, gestureOption, "ImageSpan");
        UserMouseOptions mouseOption;
        ParseUserMouseOption(args, mouseOption, "ImageSpan");
        options.userGestureOption = std::move(gestureOption);
        options.userMouseOption = std::move(mouseOption);
    }
    auto controller = controllerWeak_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    int32_t spanIndex = 0;
    if (richEditorController) {
        spanIndex = richEditorController->AddImageSpan(options);
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(spanIndex)));
}

bool JSRichEditorController::CheckImageSource(std::string assetSrc)
{
    SrcType srcType = ImageSourceInfo::ResolveURIType(assetSrc);
    if (assetSrc[0] == '/') {
        assetSrc = assetSrc.substr(1); // get the asset src without '/'.
    } else if (assetSrc[0] == '.' && assetSrc.size() > 2 && assetSrc[1] == '/') {
        assetSrc = assetSrc.substr(2); // get the asset src without './'.
    }
    if (srcType == SrcType::ASSET) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        if (!pipelineContext) {
            TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "pipelineContext is null");
            return false;
        }
        auto assetManager = pipelineContext->GetAssetManager();
        if (!assetManager) {
            TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "assetManager is null");
            return false;
        }
        auto assetData = assetManager->GetAsset(assetSrc);
        if (!assetData) {
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "assetData is null");
            return false;
        }
    }
    return true;
}

ImageSpanOptions JSRichEditorController::CreateJsImageOptions(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
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

bool JSRichEditorBaseController::IsPixelMap(const JSRef<JSVal>& jsValue)
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
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    if (args.Length() < 1) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "args length invalid");
        return;
    }
    TextSpanOptions options;
    std::u16string spanValue;
    if (auto tempArg = args[0]; tempArg->IsEmpty() || (!tempArg->IsString() && !tempArg->IsObject()) ||
        !JSContainerBase::ParseJsString(tempArg, spanValue) || spanValue.empty()) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "args error");
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(-1)));
        return;
    }
    options.value = spanValue;

    auto controller = controllerWeak_.Upgrade();
    if (args.Length() > 1 && args[1]->IsObject()) {
        JSRef<JSObject> spanObject = JSRef<JSObject>::Cast(args[1]);
        JSRef<JSVal> offset = spanObject->GetProperty("offset");
        int32_t spanOffset = 0;
        if (!offset->IsNull() && JSContainerBase::ParseJsInt32(offset, spanOffset)) {
            options.offset = spanOffset > 0 ? spanOffset : 0;
        }
        auto styleObject = JSObjectCast(spanObject->GetProperty("style"));
        updateSpanStyle_.ResetStyle();
        if (!styleObject->IsUndefined()) {
            auto pipelineContext = PipelineBase::GetCurrentContext();
            if (!pipelineContext) {
                TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "pipelineContext is null");
                return;
            }
            if (!controller) {
                TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "add text span, rich editor controller error");
                args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(0)));
                return;
            }
            auto theme = controller->GetTheme();
            TextStyle style = theme ? theme->GetTextStyle() : TextStyle();
            ParseJsTextStyle(styleObject, style, updateSpanStyle_);
            options.style = style;
            options.useThemeFontColor = updateSpanStyle_.useThemeFontColor;
            options.useThemeDecorationColor = updateSpanStyle_.useThemeDecorationColor;
        }
        auto paraStyleObj = JSObjectCast(spanObject->GetProperty("paragraphStyle"));
        struct UpdateParagraphStyle style;
        if (ParseParagraphStyle(paraStyleObj, style)) {
            options.paraStyle = style;
        }
        ParseTextUrlStyle(spanObject, options.urlAddress);
        UserGestureOptions gestureOption;
        ParseUserGesture(args, gestureOption, "TextSpan");
        options.userGestureOption = std::move(gestureOption);
    }
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    int32_t spanIndex = 0;
    if (richEditorController) {
        spanIndex = richEditorController->AddTextSpan(options);
    } else {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "rich editor controller error");
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(spanIndex)));
}

void JSRichEditorController::AddSymbolSpan(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    if (args.Length() < 1) {
        return;
    }
    SymbolSpanOptions options;
    uint32_t symbolId;
    RefPtr<ResourceObject> resourceObject;
    if (!args[0]->IsEmpty() && JSContainerBase::ParseJsSymbolId(args[0], symbolId, resourceObject)) {
        options.symbolId = symbolId;
        options.resourceObject = resourceObject;
    } else {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(-1)));
        return;
    }
    auto controller = controllerWeak_.Upgrade();
    if (args.Length() > 1 && args[1]->IsObject()) {
        JSRef<JSObject> spanObject = JSRef<JSObject>::Cast(args[1]);
        JSRef<JSVal> offset = spanObject->GetProperty("offset");
        int32_t spanOffset = 0;
        if (!offset->IsNull() && JSContainerBase::ParseJsInt32(offset, spanOffset)) {
            options.offset = spanOffset > 0 ? spanOffset : 0;
        }
        auto styleObject = JSObjectCast(spanObject->GetProperty("style"));
        if (!styleObject->IsUndefined()) {
            auto pipelineContext = PipelineBase::GetCurrentContext();
            if (!pipelineContext) {
                TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "pipelineContext is null");
                return;
            }
            if (!controller) {
                TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "add symbol span, rich editor controller error");
                args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(0)));
                return;
            }
            auto theme = controller->GetTheme();
            TextStyle style = theme ? theme->GetTextStyle() : TextStyle();
            ParseJsSymbolSpanStyle(styleObject, style, updateSpanStyle_);
            ParseJsCustomSymbolStyle(args[0], style, symbolId);
            options.style = style;
        }
    }

    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    int32_t spanIndex = 0;
    if (richEditorController) {
        spanIndex = richEditorController->AddSymbolSpan(options);
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
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
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
    auto controller = controllerWeak_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    CHECK_NULL_VOID(richEditorController);
    SelectionInfo value = richEditorController->GetSpansInfo(start, end);
    args.SetReturnValue(CreateJSSpansInfo(value));
}

void JSRichEditorBaseController::GetPreviewTextInfo(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    auto info = controller->GetPreviewTextInfo();
    args.SetReturnValue(CreateJSPreviewTextInfo(info));
}

JSRef<JSObject> JSRichEditorBaseController::CreateJSPreviewTextInfo(const PreviewTextInfo& info)
{
    auto resultObj = JSRef<JSObject>::New();
    resultObj->SetProperty<std::u16string>("value", info.value.value_or(u""));
    resultObj->SetProperty<int32_t>("offset", info.offset.value_or(0));
    return resultObj;
}

void JSRichEditorController::DeleteSpans(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    RangeOptions options;
    auto controller = controllerWeak_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    CHECK_NULL_VOID(richEditorController);

    if (args.Length() < 1) {
        richEditorController->DeleteSpans(options);
        return;
    }

    if (!args[0]->IsObject() || !richEditorController) {
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
    richEditorController->DeleteSpans(options);
}

void JSRichEditorController::AddPlaceholderSpan(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
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
        if (!funcValue->IsFunction()) {
            return;
        }
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(funcValue));
        CHECK_NULL_VOID(builderFunc);
        ViewStackModel::GetInstance()->NewScope();
        builderFunc->Execute();
        auto customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
        CHECK_NULL_VOID(customNode);
        auto controller = controllerWeak_.Upgrade();
        auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
        int32_t spanIndex = 0;
        if (richEditorController) {
            ParseOptions(args, options);
            spanIndex = richEditorController->AddPlaceholderSpan(customNode, options);
        }
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(spanIndex)));
    }
}

void JSRichEditorController::ParseOptions(const JSCallbackInfo& args, SpanOptionBase& placeholderSpan)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
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
        if (placeholderOffset >= 0) {
            placeholderSpan.offset = placeholderOffset;
        }
    }
    COLOR_MODE_LOCK(GetColorMode());
    JSRef<JSVal> colorMetrics = placeholderOptionObject->GetProperty("dragBackgroundColor");
    if (Color dragBackgroundColor; !colorMetrics->IsNull() &&
        JSContainerBase::ParseColorMetricsToColor(colorMetrics, dragBackgroundColor)) {
        placeholderSpan.dragBackgroundColor = dragBackgroundColor;
    }
    JSRef<JSVal> isDragShadowNeeded = placeholderOptionObject->GetProperty("isDragShadowNeeded");
    if (!isDragShadowNeeded->IsNull() && isDragShadowNeeded->IsBoolean()) {
        placeholderSpan.isDragShadowNeeded = isDragShadowNeeded->ToBoolean();
    }
}

void JSRichEditorController::GetSelection(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto controller = controllerWeak_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    CHECK_NULL_VOID(richEditorController);
    SelectionInfo value = richEditorController->GetSelectionSpansInfo();
    args.SetReturnValue(JSRichEditor::CreateJSSelection(value));
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
    JSClass<JSRichEditorController>::CustomMethod("getCaretRect", &JSRichEditorController::GetCaretRect);
    JSClass<JSRichEditorController>::CustomMethod("updateSpanStyle", &JSRichEditorController::UpdateSpanStyle);
    JSClass<JSRichEditorController>::CustomMethod(
        "updateParagraphStyle", &JSRichEditorController::UpdateParagraphStyle);
    JSClass<JSRichEditorController>::CustomMethod("getTypingStyle", &JSRichEditorController::GetTypingStyle);
    JSClass<JSRichEditorController>::CustomMethod("setTypingStyle", &JSRichEditorController::SetTypingStyle);
    JSClass<JSRichEditorController>::CustomMethod(
        "setTypingParagraphStyle", &JSRichEditorController::SetTypingParagraphStyle);
    JSClass<JSRichEditorController>::CustomMethod("getSpans", &JSRichEditorController::GetSpansInfo);
    JSClass<JSRichEditorController>::CustomMethod("getPreviewText", &JSRichEditorController::GetPreviewTextInfo);
    JSClass<JSRichEditorController>::CustomMethod("getParagraphs", &JSRichEditorController::GetParagraphsInfo);
    JSClass<JSRichEditorController>::CustomMethod("deleteSpans", &JSRichEditorController::DeleteSpans);
    JSClass<JSRichEditorController>::CustomMethod("setSelection", &JSRichEditorController::SetSelection);
    JSClass<JSRichEditorController>::CustomMethod("getSelection", &JSRichEditorController::GetSelection);
    JSClass<JSRichEditorController>::CustomMethod("getLayoutManager", &JSRichEditorController::GetLayoutManager);
    JSClass<JSRichEditorController>::CustomMethod("isEditing", &JSRichEditorController::IsEditing);
    JSClass<JSRichEditorController>::CustomMethod("toStyledString", &JSRichEditorController::ToStyledString);
    JSClass<JSRichEditorController>::CustomMethod("fromStyledString", &JSRichEditorController::FromStyledString);
    JSClass<JSRichEditorController>::Method("stopEditing", &JSRichEditorController::StopEditing);
    JSClass<JSRichEditorController>::Method("closeSelectionMenu", &JSRichEditorController::CloseSelectionMenu);
    JSClass<JSRichEditorController>::Bind(
        globalObj, JSRichEditorController::Constructor, JSRichEditorController::Destructor);
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
    if (!JSContainerBase::ParseJsInt32(object->GetProperty("start"), start)) {
        start = 0;
    }
    if (!JSContainerBase::ParseJsInt32(object->GetProperty("end"), end)) {
        end = INT_MAX;
    }
    if (start < 0) {
        start = 0;
    }
    if (end < 0) {
        end = INT_MAX;
    }
    if (start > end) {
        start = 0;
        end = INT_MAX;
    }
    return std::make_pair(start, end);
}
} // namespace

void JSRichEditorBaseController::ParseWordBreakParagraphStyle(const JSRef<JSObject>& styleObject,
    struct UpdateParagraphStyle& style)
{
    auto wordBreakObj = styleObject->GetProperty("wordBreak");
    if (wordBreakObj->IsNull() || !wordBreakObj->IsNumber()) {
        return;
    }
    auto index = wordBreakObj->ToNumber<int32_t>();
    if (index < 0 || index >= static_cast<int32_t>(WORD_BREAK_TYPES.size())) {
        index = static_cast<int32_t>(WordBreak::BREAK_WORD);
    }
    style.wordBreak = WORD_BREAK_TYPES[index];
}

void JSRichEditorBaseController::ParseLineBreakStrategyParagraphStyle(
    const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style)
{
    auto breakStrategyObj = styleObject->GetProperty("lineBreakStrategy");
    if (!breakStrategyObj->IsNull() && breakStrategyObj->IsNumber()) {
        auto breakStrategy = static_cast<LineBreakStrategy>(breakStrategyObj->ToNumber<int32_t>());
        if (breakStrategy < LineBreakStrategy::GREEDY || breakStrategy > LineBreakStrategy::BALANCED) {
            breakStrategy = LineBreakStrategy::GREEDY;
        }
        style.lineBreakStrategy = breakStrategy;
    }
}

void JSRichEditorBaseController::ParseTextAlignParagraphStyle(const JSRef<JSObject>& styleObject,
    struct UpdateParagraphStyle& style)
{
    auto textAlignObj = styleObject->GetProperty("textAlign");
    if (!textAlignObj->IsNull() && textAlignObj->IsNumber()) {
        auto align = static_cast<TextAlign>(textAlignObj->ToNumber<int32_t>());
        if (align < TextAlign::START || align > TextAlign::JUSTIFY) {
            align = TextAlign::START;
        }
        style.textAlign = align;
    }
}

void JSRichEditorBaseController::ParseParagraphSpacing(const JSRef<JSObject>& styleObject,
    struct UpdateParagraphStyle& style)
{
    auto paragraphSpacing = styleObject->GetProperty("paragraphSpacing");
    CalcDimension size;
    if (!paragraphSpacing->IsNull() && JSContainerBase::ParseJsDimensionFpNG(paragraphSpacing, size, false) &&
        !size.IsNegative() && size.Unit() != DimensionUnit::PERCENT) {
        style.paragraphSpacing = size;
    }
}

bool JSRichEditorBaseController::ParseParagraphStyle(const JSRef<JSObject>& styleObject, struct UpdateParagraphStyle& style)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    if (styleObject->IsUndefined()) {
        return false;
    }
    ParseTextAlignParagraphStyle(styleObject, style);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        ParseLineBreakStrategyParagraphStyle(styleObject, style);
        ParseWordBreakParagraphStyle(styleObject, style);
    }
    ParseParagraphSpacing(styleObject, style);

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
            style.leadingMargin->size = NG::LeadingMarginSize(width, height);
        } else if (sizeVal->IsUndefined()) {
            std::string resWidthStr;
            if (JSContainerBase::ParseJsString(lm, resWidthStr)) {
                CalcDimension width;
                JSContainerBase::ParseJsDimensionVp(lm, width);
                style.leadingMargin->size = NG::LeadingMarginSize(width, Dimension(0.0, width.Unit()));
            }
        }
    } else if (!lm->IsNull()) {
        // [Dimension]
        style.leadingMargin = std::make_optional<NG::LeadingMargin>();
        CalcDimension width;
        JSContainerBase::ParseJsDimensionVp(lm, width);
        style.leadingMargin->size = NG::LeadingMarginSize(width, Dimension(0.0, width.Unit()));
    }
    return true;
}

void JSRichEditorController::UpdateSpanStyle(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    if (!ValidationCheck(info)) {
        return;
    }
    auto jsObject = JSRef<JSObject>::Cast(info[0]);

    auto [start, end] = ParseRange(jsObject);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    if (!pipelineContext) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "pipelineContext is null");
        return;
    }
    auto controller = controllerWeak_.Upgrade();
    if (!controller) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "update span style, rich editor controller error");
        return;
    }
    auto theme = controller->GetTheme();
    TextStyle textStyle = theme ? theme->GetTextStyle() : TextStyle();
    ImageSpanAttribute imageStyle;
    auto richEditorTextStyle = JSObjectCast(jsObject->GetProperty("textStyle"));
    auto richEditorImageStyle = JSObjectCast(jsObject->GetProperty("imageStyle"));
    auto richEditorSymbolSpanStyle = JSObjectCast(jsObject->GetProperty("symbolStyle"));
    updateSpanStyle_.ResetStyle();
    if (!richEditorTextStyle->IsUndefined()) {
        ParseJsTextStyle(richEditorTextStyle, textStyle, updateSpanStyle_);
    }
    if (!richEditorImageStyle->IsUndefined()) {
        imageStyle = ParseJsImageSpanAttribute(richEditorImageStyle);
    }
    if (!richEditorSymbolSpanStyle->IsUndefined()) {
        TextStyle symbolTextStyle;
        ParseJsSymbolSpanStyle(richEditorSymbolSpanStyle, symbolTextStyle, updateSpanStyle_);
    }
    ParseTextUrlStyle(jsObject, updateSpanStyle_.updateUrlAddress);

    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    CHECK_NULL_VOID(richEditorController);
    richEditorController->SetUpdateSpanStyle(updateSpanStyle_);
    richEditorController->UpdateSpanStyle(start, end, textStyle, imageStyle);
}

void JSRichEditorController::GetParagraphsInfo(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    if (!args[0]->IsObject()) {
        return;
    }
    auto [start, end] = ParseRange(JSRef<JSObject>::Cast(args[0]));
    if (start == end) {
        return;
    }
    auto controller = controllerWeak_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    CHECK_NULL_VOID(richEditorController);
    auto info = richEditorController->GetParagraphsInfo(start, end);
    args.SetReturnValue(CreateJSParagraphsInfo(info));
}

void JSRichEditorController::UpdateParagraphStyle(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    if (!ValidationCheck(info)) {
        return;
    }
    auto object = JSRef<JSObject>::Cast(info[0]);
    auto [start, end] = ParseRange(object);
    if (start == end) {
        return;
    }
    auto styleObj = JSObjectCast(object->GetProperty("style"));

    struct UpdateParagraphStyle style;
    if (!ParseParagraphStyle(styleObj, style)) {
        return;
    }
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    CHECK_NULL_VOID(richEditorController);
    richEditorController->UpdateParagraphStyle(start, end, style);
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

void JSRichEditorBaseController::GetCaretOffset(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto controller = controllerWeak_.Upgrade();
    int32_t caretOffset = -1;
    if (controller) {
        caretOffset = controller->GetCaretOffset();
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(caretOffset)));
    } else {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(caretOffset)));
    }
}

void JSRichEditorBaseController::GetCaretRect(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    auto caretRect = controller->GetCaretRect();
    CHECK_EQUAL_VOID(caretRect.IsValid(), false);
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty<float>("x", caretRect.GetOffset().GetX());
    obj->SetProperty<float>("y", caretRect.GetOffset().GetY());
    obj->SetProperty<float>("width", caretRect.Width());
    obj->SetProperty<float>("height", caretRect.Height());
    args.SetReturnValue(obj);
}

void JSRichEditorBaseController::SetCaretOffset(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
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

void JSRichEditorBaseController::SetTypingStyle(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    bool isBelowApi12 = !AceApplicationInfo::GetInstance().
        GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE);
    if (isBelowApi12 && !info[0]->IsObject()) {
        return;
    }
    auto pipelineContext = PipelineBase::GetCurrentContext();
    if (!pipelineContext) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "pipelineContext is null");
        return;
    }
    auto theme = controller->GetTheme();
    TextStyle textStyle = theme ? theme->GetTextStyle() : TextStyle();
    bool isUndefined = false;
    if (info[0]->IsObject()) {
        JSRef<JSObject> richEditorTextStyle = JSRef<JSObject>::Cast(info[0]);
        isUndefined = richEditorTextStyle->IsUndefined();
        typingStyle_.ResetStyle();
        if (isBelowApi12) {
            typingStyle_.updateTextColor = theme->GetTextStyle().GetTextColor();
        }
        if (!richEditorTextStyle->IsUndefined()) {
            ParseJsTextStyle(richEditorTextStyle, textStyle, typingStyle_);
        }
    }
    bool isNeedReset = !isBelowApi12 && (!info[0]->IsObject() || isUndefined);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetTypingStyle %{public}d", isNeedReset);
    if (isNeedReset) {
        controller->SetTypingStyle(std::nullopt, std::nullopt);
        return;
    }
    controller->SetTypingStyle(typingStyle_, textStyle);
}


void JSRichEditorBaseController::SetTypingParagraphStyle(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);

    do {
        CHECK_NULL_BREAK(info[0]->IsObject());
        JSRef<JSObject> paraStyleObj = JSRef<JSObject>::Cast(info[0]);
        CHECK_NULL_BREAK(!paraStyleObj->IsUndefined());
        struct UpdateParagraphStyle style;
        CHECK_NULL_BREAK(ParseParagraphStyle(paraStyleObj, style));
        controller->SetTypingParagraphStyle(style);
        return;
    } while (0);
    controller->SetTypingParagraphStyle(std::nullopt);
}

bool JSRichEditorBaseController::FontSizeRangeIsNegative(const CalcDimension& size)
{
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        return size.IsNegative();
    }
    return size.IsNonPositive();
}

void JSRichEditorBaseController::ParseJsTextStyle(
    const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    JSRef<JSVal> fontColor = styleObject->GetProperty("fontColor");
    COLOR_MODE_LOCK(GetColorMode());
    Color textColor;
    if (!fontColor->IsNull() && JSContainerBase::ParseJsColor(fontColor, textColor)) {
        style.SetTextColor(textColor);
        updateSpanStyle.updateTextColor = textColor;
        updateSpanStyle.useThemeFontColor = false;
    }
    JSRef<JSVal> fontSize = styleObject->GetProperty("fontSize");
    CalcDimension size;
    if (!fontSize->IsNull() && JSContainerBase::ParseJsDimensionFpNG(fontSize, size) &&
        !FontSizeRangeIsNegative(size) && size.Unit() != DimensionUnit::PERCENT) {
        updateSpanStyle.updateFontSize = size;
        style.SetFontSize(size);
    } else if (FontSizeRangeIsNegative(size) || size.Unit() == DimensionUnit::PERCENT) {
        auto theme = JSContainerBase::GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        size = theme->GetTextStyle().GetFontSize();
        style.SetFontSize(size);
    }
    ParseJsLineHeightLetterSpacingTextStyle(styleObject, style, updateSpanStyle);
    ParseJsFontFeatureTextStyle(styleObject, style, updateSpanStyle);
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
    ParseJsHalfLeadingTextStyle(styleObject, style, updateSpanStyle);
    ParseTextDecoration(styleObject, style, updateSpanStyle);
    ParseTextShadow(styleObject, style, updateSpanStyle);
    ParseTextBackgroundStyle(styleObject, style, updateSpanStyle);
}

void JSRichEditorBaseController::ParseJsLineHeightLetterSpacingTextStyle(const JSRef<JSObject>& styleObject,
    TextStyle& style, struct UpdateSpanStyle& updateSpanStyle, bool isSupportPercent)
{
    JSRef<JSVal> lineHeight = styleObject->GetProperty("lineHeight");
    CalcDimension height;
    if (!lineHeight->IsNull() && JSContainerBase::ParseJsDimensionFpNG(lineHeight, height, isSupportPercent) &&
        !height.IsNegative() && height.Unit() != DimensionUnit::PERCENT) {
        updateSpanStyle.updateLineHeight = height;
        style.SetLineHeight(height);
    } else if (height.IsNegative() || height.Unit() == DimensionUnit::PERCENT) {
        auto theme = JSContainerBase::GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        height = theme->GetTextStyle().GetLineHeight();
        updateSpanStyle.updateLineHeight = height;
        style.SetLineHeight(height);
    } else if (!lineHeight->IsUndefined() &&
               !std::all_of(lineHeight->ToString().begin(), lineHeight->ToString().end(), ::isdigit)) {
        auto theme = JSContainerBase::GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        height = theme->GetTextStyle().GetLineHeight();
        updateSpanStyle.updateLineHeight = height;
        style.SetLineHeight(height);
    }
    JSRef<JSVal> letterSpacing = styleObject->GetProperty("letterSpacing");
    CalcDimension letters;
    if (JSContainerBase::ParseJsDimensionFpNG(letterSpacing, letters, isSupportPercent) &&
        letters.Unit() != DimensionUnit::PERCENT) {
        updateSpanStyle.updateLetterSpacing = letters;
        style.SetLetterSpacing(letters);
    } else if (letters.Unit() == DimensionUnit::PERCENT) {
        auto theme = JSContainerBase::GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        letters = theme->GetTextStyle().GetLetterSpacing();
        updateSpanStyle.updateLetterSpacing = letters;
        style.SetLetterSpacing(letters);
    } else if (!letterSpacing->IsUndefined() && !letterSpacing->IsNull() &&
               !std::all_of(letterSpacing->ToString().begin(), letterSpacing->ToString().end(), ::isdigit)) {
        auto theme = JSContainerBase::GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        letters = theme->GetTextStyle().GetLetterSpacing();
        updateSpanStyle.updateLetterSpacing = letters;
        style.SetLetterSpacing(letters);
    }
}

void JSRichEditorBaseController::ParseJsFontFeatureTextStyle(const JSRef<JSObject>& styleObject,
    TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    JSRef<JSVal> fontFeature = styleObject->GetProperty("fontFeature");
    std::string feature;
    if (!fontFeature->IsNull() && JSContainerBase::ParseJsString(fontFeature, feature)) {
        NG::FONT_FEATURES_LIST fontFeatures = ParseFontFeatureSettings(feature);
        updateSpanStyle.updateFontFeature = fontFeatures;
        style.SetFontFeatures(fontFeatures);
    } else {
        auto theme = JSContainerBase::GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        auto fontFeatures = theme->GetTextStyle().GetFontFeatures();
        updateSpanStyle.updateFontFeature = fontFeatures;
        style.SetFontFeatures(fontFeatures);
    }
}

void JSRichEditorBaseController::ParseJsHalfLeadingTextStyle(const JSRef<JSObject>& styleObject,
    TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    JSRef<JSVal> halfLeading = styleObject->GetProperty("halfLeading");
    bool isHalfLeading = false;
    if (!halfLeading->IsNull() && halfLeading->IsBoolean()) {
        isHalfLeading = halfLeading->ToBoolean();
        updateSpanStyle.updateHalfLeading = isHalfLeading;
        style.SetHalfLeading(isHalfLeading);
    }
}

void JSRichEditorBaseController::ParseTextDecoration(
    const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto decorationObject = JSObjectCast(styleObject->GetProperty("decoration"));
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
            updateSpanStyle.useThemeDecorationColor = false;
        }
        JSRef<JSVal> textDecorationStyle = decorationObject->GetProperty("style");
        if (!textDecorationStyle->IsNull() && !textDecorationStyle->IsUndefined()) {
            updateSpanStyle.updateTextDecorationStyle =
                static_cast<TextDecorationStyle>(textDecorationStyle->ToNumber<int32_t>());
            style.SetTextDecorationStyle(static_cast<TextDecorationStyle>(textDecorationStyle->ToNumber<int32_t>()));
        }
        updateSpanStyle.isInitDecoration = true;
    }
    if (!updateSpanStyle.updateTextDecorationColor.has_value() && updateSpanStyle.updateTextColor.has_value()) {
        updateSpanStyle.updateTextDecorationColor = style.GetTextColor();
        style.SetTextDecorationColor(style.GetTextColor());
        CHECK_NULL_VOID(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
        updateSpanStyle.useThemeDecorationColor = false;
    }
}

void JSRichEditorBaseController::ParseTextShadow(
    const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
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

void JSRichEditorBaseController::ParseTextBackgroundStyle(
    const JSRef<JSObject>& styleObject, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto backgroundObject = styleObject->GetProperty("textBackgroundStyle");
    CHECK_NULL_VOID(!backgroundObject->IsNull() && !backgroundObject->IsUndefined());
    auto textBackgroundValue = JSContainerSpan::ParseTextBackgroundStyle(backgroundObject);
    style.SetTextBackgroundStyle(textBackgroundValue);
    updateSpanStyle.updateTextBackgroundStyle = textBackgroundValue;
}

void JSRichEditorBaseController::GetTypingStyle(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    auto typingStyle = controller->GetTypingStyle();
    auto style = CreateTypingStyleResult(typingStyle.value_or(UpdateSpanStyle()));
    info.SetReturnValue(JSRef<JSVal>::Cast(style));
}

JSRef<JSObject> JSRichEditorBaseController::CreateTypingStyleResult(const struct UpdateSpanStyle& typingStyle)
{
    auto tyingStyleObj = JSRef<JSObject>::New();
    if (typingStyle.updateTextColor.has_value()) {
        tyingStyleObj->SetProperty<std::string>("fontColor", typingStyle.updateTextColor.value().ColorToString());
    }
    if (typingStyle.updateFontSize.has_value()) {
        tyingStyleObj->SetProperty<double>("fontSize", typingStyle.updateFontSize.value().ConvertToVp());
    }
    if (typingStyle.updateItalicFontStyle.has_value()) {
        tyingStyleObj->SetProperty<int32_t>(
            "fontStyle", static_cast<int32_t>(typingStyle.updateItalicFontStyle.value()));
    }
    if (typingStyle.updateFontWeight.has_value()) {
        tyingStyleObj->SetProperty<int32_t>("fontWeight", static_cast<int32_t>(typingStyle.updateFontWeight.value()));
    }
    if (typingStyle.updateFontFamily.has_value()) {
        std::string family = V2::ConvertFontFamily(typingStyle.updateFontFamily.value());
        tyingStyleObj->SetProperty<std::string>("fontFamily", family);
    }
    if (typingStyle.isInitDecoration) {
        tyingStyleObj->SetPropertyObject("decoration", CreateJsDecorationObj(typingStyle));
    }
    if (typingStyle.updateTextShadows.has_value()) {
        tyingStyleObj->SetPropertyObject("textShadows",
            JSRichEditor::CreateJsTextShadowObjectArray(typingStyle.updateTextShadows.value()));
    }
    if (typingStyle.updateLineHeight.has_value()) {
        tyingStyleObj->SetProperty<double>("lineHeight", typingStyle.updateLineHeight.value().ConvertToVp());
    }
    if (typingStyle.updateHalfLeading.has_value()) {
        tyingStyleObj->SetProperty<bool>("halfLeading", typingStyle.updateHalfLeading.value());
    }
    if (typingStyle.updateLetterSpacing.has_value()) {
        tyingStyleObj->SetProperty<double>("letterSpacing", typingStyle.updateLetterSpacing.value().ConvertToVp());
    }
    if (typingStyle.updateFontFeature.has_value()) {
        tyingStyleObj->SetProperty<std::string>(
            "fontFeature", UnParseFontFeatureSetting(typingStyle.updateFontFeature.value()));
    }
    if (typingStyle.updateTextBackgroundStyle.has_value()) {
        tyingStyleObj->SetPropertyObject("textBackgroundStyle",
            JSRichEditor::CreateJsTextBackgroundStyle(typingStyle.updateTextBackgroundStyle.value()));
    }

    return tyingStyleObj;
}

JSRef<JSObject> JSRichEditorBaseController::CreateJsDecorationObj(const struct UpdateSpanStyle& typingStyle)
{
    JSRef<JSObject> decorationObj = JSRef<JSObject>::New();
    if (typingStyle.updateTextDecoration.has_value()) {
        decorationObj->SetProperty<int32_t>("type", static_cast<int32_t>(typingStyle.updateTextDecoration.value()));
    }
    if (typingStyle.updateTextDecorationColor.has_value()) {
        decorationObj->SetProperty<std::string>(
            "color", typingStyle.updateTextDecorationColor.value().ColorToString());
    }
    if (typingStyle.updateTextDecorationStyle.has_value()) {
        decorationObj->SetProperty<int32_t>("style",
            static_cast<int32_t>(typingStyle.updateTextDecorationStyle.value()));
    }
    return decorationObj;
}

void JSRichEditorBaseController::CloseSelectionMenu()
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    controller->CloseSelectionMenu();
}

void JSRichEditorBaseController::IsEditing(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    bool value = controller->IsEditing();
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    args.SetReturnValue(JsiRef<JsiValue>::Make(panda::BooleanRef::New(runtime->GetEcmaVm(), value)));
}

void JSRichEditorController::ToStyledString(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
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
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controllerWeak_.Upgrade());
    CHECK_NULL_VOID(richEditorController);
    auto spanStringBase = richEditorController->ToStyledString(start, end);
    auto spanString = AceType::DynamicCast<SpanString>(spanStringBase);
    CHECK_NULL_VOID(spanString);
    JSRef<JSObject> obj = JSClass<JSSpanString>::NewInstance();
    auto jsSpanString = Referenced::Claim(obj->Unwrap<JSSpanString>());
    jsSpanString->SetController(spanString);
    args.SetReturnValue(obj);
}

void JSRichEditorController::FromStyledString(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    if ((args.Length() != 1) || !args[0]->IsObject()) {
        return;
    }
    auto* spanString = JSRef<JSObject>::Cast(args[0])->Unwrap<JSSpanString>();
    CHECK_NULL_VOID(spanString);
    auto spanStringController = spanString->GetController();
    CHECK_NULL_VOID(spanStringController);
    auto controller = controllerWeak_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    CHECK_NULL_VOID(richEditorController);
    SelectionInfo value = richEditorController->FromStyledString(spanStringController);
    args.SetReturnValue(CreateJSSpansInfo(value));
}

void JSRichEditorBaseController::StopEditing()
{
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    controller->StopEditing();
}

JSRef<JSObject> JSRichEditorBaseController::JSObjectCast(JSRef<JSVal> jsValue)
{
    JSRef<JSObject> jsObject;
    if (!jsValue->IsObject()) {
        return jsObject;
    }
    return JSRef<JSObject>::Cast(jsValue);
}

void JSRichEditorBaseController::SetSelection(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    if (args.Length() < 2) { // 2:At least two parameters
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Info length error.");
        return;
    }
    int32_t selectionStart = 0;
    int32_t selectionEnd = 0;
    JSContainerBase::ParseJsInt32(args[0], selectionStart);
    JSContainerBase::ParseJsInt32(args[1], selectionEnd);
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    std::optional<SelectionOptions> options = std::nullopt;
    ParseJsSelectionOptions(args, options);
    controller->SetSelection(selectionStart, selectionEnd, options);
}

void JSRichEditorBaseController::GetLayoutManager(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    JSRef<JSObject> obj = JSClass<JSLayoutManager>::NewInstance();
    auto jsLayoutManager = Referenced::Claim(obj->Unwrap<JSLayoutManager>());
    CHECK_NULL_VOID(jsLayoutManager);
    auto controller = controllerWeak_.Upgrade();
    CHECK_NULL_VOID(controller);
    auto layoutInfoInterface = controller->GetLayoutInfoInterface();
    jsLayoutManager->SetLayoutInfoInterface(layoutInfoInterface);
    args.SetReturnValue(obj);
}

void JSRichEditorBaseController::ParseJsSelectionOptions(
    const JSCallbackInfo& args, std::optional<SelectionOptions>& options)
{
    if (args.Length() < 3) { // 3:Protect operations
        return;
    }
    auto temp = args[2]; // 2:Get the third parameter
    if (!temp->IsObject()) {
        return;
    }
    SelectionOptions optionTemp;
    JSRef<JSObject> placeholderOptionObject = JSRef<JSObject>::Cast(temp);
    JSRef<JSVal> menuPolicy = placeholderOptionObject->GetProperty("menuPolicy");
    double tempPolicy = 0.0;
    if (!menuPolicy->IsNull() && JSContainerBase::ParseJsDouble(menuPolicy, tempPolicy)) {
        if (0 == tempPolicy || 1 == tempPolicy || 2 == tempPolicy) { // 0:DEFAULT, 1:HIDE, 2:SHOW
            optionTemp.menuPolicy = static_cast<MenuPolicy>(tempPolicy);
            options = optionTemp;
        }
    }
}

void JSRichEditorStyledStringController::SetController(const RefPtr<RichEditorBaseControllerBase>& controller)
{
    JSRichEditorBaseController::SetController(controller);
    auto styledStringCache = GetStyledStringCache();
    CHECK_NULL_VOID(styledStringCache);
    auto styledStringController = AceType::DynamicCast<RichEditorStyledStringControllerBase>(controller);
    CHECK_NULL_VOID(styledStringController);
    styledStringController->SetStyledString(styledStringCache);
    SetStyledStringCache(nullptr);
}

void JSRichEditorStyledStringController::GetSelection(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto controller = controllerWeak_.Upgrade();
    auto styledStringController = AceType::DynamicCast<RichEditorStyledStringControllerBase>(controller);
    CHECK_NULL_VOID(styledStringController);
    SelectionRangeInfo value = styledStringController->GetSelection();
    args.SetReturnValue(JSRichEditor::CreateJSSelectionRange(value));
}

void JSRichEditorStyledStringController::SetStyledString(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    if ((args.Length() != 1) || !args[0]->IsObject()) {
        return;
    }
    auto* spanString = JSRef<JSObject>::Cast(args[0])->Unwrap<JSSpanString>();
    CHECK_NULL_VOID(spanString);
    auto spanStringController = spanString->GetController();
    CHECK_NULL_VOID(spanStringController);
    auto controller = controllerWeak_.Upgrade();
    if (!controller) {
        SetStyledStringCache(spanStringController->GetSubSpanString(0, spanStringController->GetLength()));
    }
    auto styledStringController = AceType::DynamicCast<RichEditorStyledStringControllerBase>(controller);
    CHECK_NULL_VOID(styledStringController);
    styledStringController->SetStyledString(spanStringController);

    auto thisObj = args.This();
    auto storeIndex = spanStringControllerStoreIndex_.fetch_add(1);
    std::string storeKey = "STYLED_STRING_SPANSTRING_RICH_STORE_" + std::to_string(storeIndex);
    thisObj->SetPropertyObject(storeKey.c_str(), args[0]);
}

void JSRichEditorStyledStringController::GetStyledString(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    auto controller = controllerWeak_.Upgrade();
    auto styledStringController = AceType::DynamicCast<RichEditorStyledStringControllerBase>(controller);
    CHECK_NULL_VOID(styledStringController);
    auto mutableSpanString = AceType::DynamicCast<MutableSpanString>(styledStringController->GetStyledString());
    CHECK_NULL_VOID(mutableSpanString);
    JSRef<JSObject> obj = JSClass<JSMutableSpanString>::NewInstance();
    auto jsMutableSpanString = Referenced::Claim(obj->Unwrap<JSMutableSpanString>());
    CHECK_NULL_VOID(jsMutableSpanString);
    jsMutableSpanString->SetController(mutableSpanString);
    jsMutableSpanString->SetMutableController(mutableSpanString);
    args.SetReturnValue(obj);
}

void JSRichEditorStyledStringController::OnContentChanged(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);
    CHECK_NULL_VOID(args[0]->IsObject());
    SetOnWillChange(args);
    SetOnDidChange(args);
}

void JSRichEditorStyledStringController::SetOnWillChange(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(args[0]);
    auto onWillChangeFunc = paramObject->GetProperty("onWillChange");
    if (onWillChangeFunc->IsNull() || !onWillChangeFunc->IsFunction()) {
        return;
    }
    auto jsOnWillChangeFunc = AceType::MakeRefPtr<JsEventFunction<NG::StyledStringChangeValue, 1>>(
        JSRef<JSFunc>::Cast(onWillChangeFunc), CreateJsOnWillChange);
    auto callback = [execCtx = args.GetExecutionContext(), func = std::move(jsOnWillChangeFunc)](
                        const NG::StyledStringChangeValue& changeValue) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, true);
        auto ret = func->ExecuteWithValue(changeValue);
        if (ret->IsBoolean()) {
            return ret->ToBoolean();
        }
        return true;
    };
    auto controller = controllerWeak_.Upgrade();
    auto styledStringController = AceType::DynamicCast<RichEditorStyledStringControllerBase>(controller);
    CHECK_NULL_VOID(styledStringController);
    styledStringController->SetOnWillChange(std::move(callback));
}

void JSRichEditorStyledStringController::SetOnDidChange(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(args[0]);
    auto onDidChangeFunc = paramObject->GetProperty("onDidChange");
    if (onDidChangeFunc->IsNull() || !onDidChangeFunc->IsFunction()) {
        return;
    }
    auto jsOnDidChangeFunc = AceType::MakeRefPtr<JsCommonEventFunction<NG::StyledStringChangeValue, 2>>(
        JSRef<JSFunc>::Cast(onDidChangeFunc));
    auto callback = [execCtx = args.GetExecutionContext(), func = std::move(jsOnDidChangeFunc)](
                        const NG::StyledStringChangeValue& changeValue) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        const auto& rangeBefore = changeValue.GetRangeBefore();
        JSRef<JSObject> rangeBeforeObj = JSRef<JSObject>::New();
        rangeBeforeObj->SetPropertyObject("start", JSRef<JSVal>::Make(ToJSValue(rangeBefore.start)));
        rangeBeforeObj->SetPropertyObject("end", JSRef<JSVal>::Make(ToJSValue(rangeBefore.end)));

        const auto& rangeAfter = changeValue.GetRangeAfter();
        JSRef<JSObject> rangeAfterObj = JSRef<JSObject>::New();
        rangeAfterObj->SetPropertyObject("start", JSRef<JSVal>::Make(ToJSValue(rangeAfter.start)));
        rangeAfterObj->SetPropertyObject("end", JSRef<JSVal>::Make(ToJSValue(rangeAfter.end)));

        JSRef<JSVal> param[2] = { JSRef<JSVal>::Cast(rangeBeforeObj), JSRef<JSVal>::Cast(rangeAfterObj) };
        func->Execute(param);
    };
    auto controller = controllerWeak_.Upgrade();
    auto styledStringController = AceType::DynamicCast<RichEditorStyledStringControllerBase>(controller);
    CHECK_NULL_VOID(styledStringController);
    styledStringController->SetOnDidChange(std::move(callback));
}

JSRef<JSVal> JSRichEditorStyledStringController::CreateJsOnWillChange(const NG::StyledStringChangeValue& changeValue)
{
    JSRef<JSObject> onWillChangeObj = JSRef<JSObject>::New();
    JSRef<JSObject> rangeObj = JSRef<JSObject>::New();
    auto rangeBefore = changeValue.GetRangeBefore();
    rangeObj->SetPropertyObject("start", JSRef<JSVal>::Make(ToJSValue(rangeBefore.start)));
    rangeObj->SetPropertyObject("end", JSRef<JSVal>::Make(ToJSValue(rangeBefore.end)));
    auto spanString = AceType::DynamicCast<SpanString>(changeValue.GetReplacementString());
    CHECK_NULL_RETURN(spanString, JSRef<JSVal>::Cast(onWillChangeObj));
    JSRef<JSObject> replacementStringObj = JSClass<JSSpanString>::NewInstance();
    auto jsSpanString = Referenced::Claim(replacementStringObj->Unwrap<JSSpanString>());
    jsSpanString->SetController(spanString);
    onWillChangeObj->SetPropertyObject("range", rangeObj);
    onWillChangeObj->SetPropertyObject("replacementString", replacementStringObj);
    if (changeValue.GetPreviewText()) {
        JSRef<JSObject> previewTextObj = JSClass<JSSpanString>::NewInstance();
        auto jsPreviewTextSpanString = Referenced::Claim(previewTextObj->Unwrap<JSSpanString>());
        jsPreviewTextSpanString->SetController(AceType::DynamicCast<SpanString>(changeValue.GetPreviewText()));
        onWillChangeObj->SetPropertyObject("previewText", previewTextObj);
    }
    return JSRef<JSVal>::Cast(onWillChangeObj);
}

void JSRichEditorStyledStringController::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichEditorStyledStringController>::Declare("RichEditorStyledStringController");
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "setCaretOffset", &JSRichEditorStyledStringController::SetCaretOffset);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "getCaretOffset", &JSRichEditorStyledStringController::GetCaretOffset);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "getCaretRect", &JSRichEditorStyledStringController::GetCaretRect);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "getTypingStyle", &JSRichEditorStyledStringController::GetTypingStyle);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "setTypingStyle", &JSRichEditorStyledStringController::SetTypingStyle);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "setTypingParagraphStyle", &JSRichEditorStyledStringController::SetTypingParagraphStyle);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "getSelection", &JSRichEditorStyledStringController::GetSelection);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "getPreviewText", &JSRichEditorStyledStringController::GetPreviewTextInfo);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "setSelection", &JSRichEditorStyledStringController::SetSelection);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "isEditing", &JSRichEditorStyledStringController::IsEditing);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "setStyledString", &JSRichEditorStyledStringController::SetStyledString);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "getStyledString", &JSRichEditorStyledStringController::GetStyledString);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "onContentChanged", &JSRichEditorStyledStringController::OnContentChanged);
    JSClass<JSRichEditorStyledStringController>::CustomMethod(
        "getLayoutManager", &JSRichEditorStyledStringController::GetLayoutManager);
    JSClass<JSRichEditorStyledStringController>::Method(
        "stopEditing", &JSRichEditorStyledStringController::StopEditing);
    JSClass<JSRichEditorStyledStringController>::Method(
        "closeSelectionMenu", &JSRichEditorStyledStringController::CloseSelectionMenu);
    JSClass<JSRichEditorStyledStringController>::Bind(
        globalObj, JSRichEditorStyledStringController::Constructor, JSRichEditorStyledStringController::Destructor);
}

} // namespace OHOS::Ace::Framework
