/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_search.h"

#include <optional>
#include <string>

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/js_textfield.h"
#include "bridge/declarative_frontend/jsview/js_textinput.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/search_model_impl.h"
#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/common/layout/constants.h"
#include "core/components/search/search_component.h"
#include "core/components/search/search_theme.h"
#include "core/components/text_field/text_field_component.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/search/search_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<SearchModel> SearchModel::instance_ = nullptr;

SearchModel* SearchModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::SearchModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::SearchModelNG());
        } else {
            instance_.reset(new Framework::SearchModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

namespace {
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };
} // namespace

void JSSearch::JSBind(BindingTarget globalObj)
{
    JSClass<JSSearch>::Declare("Search");
    MethodOptions opt = MethodOptions::NONE;

    JSClass<JSSearch>::StaticMethod("create", &JSSearch::Create, opt);
    JSClass<JSSearch>::StaticMethod("searchButton", &JSSearch::SetSearchButton, opt);
    JSClass<JSSearch>::StaticMethod("placeholderColor", &JSSearch::SetPlaceholderColor, opt);
    JSClass<JSSearch>::StaticMethod("placeholderFont", &JSSearch::SetPlaceholderFont, opt);
    JSClass<JSSearch>::StaticMethod("textFont", &JSSearch::SetTextFont, opt);
    JSClass<JSSearch>::StaticMethod("textAlign", &JSSearch::SetTextAlign, opt);
    JSClass<JSSearch>::StaticMethod("onSubmit", &JSSearch::OnSubmit, opt);
    JSClass<JSSearch>::StaticMethod("onChange", &JSSearch::OnChange, opt);
    JSClass<JSSearch>::StaticMethod("border", &JSSearch::JsBorder);
    JSClass<JSSearch>::StaticMethod("borderWidth", &JSSearch::JsBorderWidth);
    JSClass<JSSearch>::StaticMethod("borderColor", &JSSearch::JsBorderColor);
    JSClass<JSSearch>::StaticMethod("borderStyle", &JSSearch::JsBorderStyle);
    JSClass<JSSearch>::StaticMethod("borderRadius", &JSSearch::JsBorderRadius);
    JSClass<JSSearch>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSearch>::StaticMethod("height", &JSSearch::SetHeight);
    JSClass<JSSearch>::StaticMethod("width", &JSViewAbstract::JsWidth);
    JSClass<JSSearch>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSearch>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSearch>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSSearch>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSearch>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSearch>::StaticMethod("onCopy", &JSSearch::SetOnCopy);
    JSClass<JSSearch>::StaticMethod("onCut", &JSSearch::SetOnCut);
    JSClass<JSSearch>::StaticMethod("onPaste", &JSSearch::SetOnPaste);
    JSClass<JSSearch>::StaticMethod("copyOption", &JSSearch::SetCopyOption);
    JSClass<JSSearch>::Inherit<JSViewAbstract>();
    JSClass<JSSearch>::Bind(globalObj);
}

void JSSearch::Create(const JSCallbackInfo& info)
{
    std::optional<std::string> key;
    std::optional<std::string> tip;
    std::optional<std::string> src;
    JSSearchController* jsController = nullptr;
    if (info[0]->IsObject()) {
        auto param = JSRef<JSObject>::Cast(info[0]);
        std::string placeholder;
        if (param->GetProperty("placeholder")->IsUndefined()) {
            tip = "";
        }
        if (ParseJsString(param->GetProperty("placeholder"), placeholder)) {
            tip = placeholder;
        }
        std::string text;
        if (param->GetProperty("value")->IsUndefined()) {
            key = "";
        }
        if (ParseJsString(param->GetProperty("value"), text)) {
            key = text;
        }
        std::string icon;
        if (ParseJsString(param->GetProperty("icon"), icon)) {
            src = icon;
        }
        auto controllerObj = param->GetProperty("controller");
        if (!controllerObj->IsUndefined() && !controllerObj->IsNull()) {
            jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSSearchController>();
        }
    }
    auto controller = SearchModel::GetInstance()->Create(key, tip, src);
    if (jsController) {
        jsController->SetController(controller);
    }
    if (!Container::IsCurrentUseNewPipeline()) {
        JSInteractableView::SetFocusable(true);
        JSInteractableView::SetFocusNode(true);
    }
}

void JSSearch::SetSearchButton(const std::string& text)
{
    SearchModel::GetInstance()->SetSearchButton(text);
}

void JSSearch::SetPlaceholderColor(const JSCallbackInfo& info)
{
    auto value = JSRef<JSVal>::Cast(info[0]);
    Color colorVal;
    if (ParseJsColor(value, colorVal)) {
        SearchModel::GetInstance()->SetPlaceholderColor(colorVal);
    }
}

void JSSearch::SetPlaceholderFont(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto param = JSRef<JSObject>::Cast(info[0]);
    Font font;
    auto fontSize = param->GetProperty("size");
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        font.fontSize = Dimension(-1);
    } else {
        Dimension size;
        if (!ParseJsDimensionFp(fontSize, size) || size.Unit() == DimensionUnit::PERCENT) {
            font.fontSize = Dimension(-1);
            LOGW("Parse to dimension FP failed.");
        } else {
            font.fontSize = size;
        }
    }

    auto weight = param->GetProperty("weight");
    if (!weight->IsNull()) {
        std::string weightVal;
        if (weight->IsNumber()) {
            weightVal = std::to_string(weight->ToNumber<int32_t>());
        } else {
            ParseJsString(weight, weightVal);
        }
        font.fontWeight = ConvertStrToFontWeight(weightVal);
    }

    auto family = param->GetProperty("family");
    if (!family->IsNull() && family->IsString()) {
        auto familyVal = family->ToString();
        font.fontFamilies = ConvertStrToFontFamilies(familyVal);
    }

    auto style = param->GetProperty("style");
    if (!style->IsNull() && style->IsNumber()) {
        FontStyle styleVal = static_cast<FontStyle>(style->ToNumber<int32_t>());
        font.fontStyle = styleVal;
    }
    SearchModel::GetInstance()->SetPlaceholderFont(font);
}

void JSSearch::SetTextFont(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto param = JSRef<JSObject>::Cast(info[0]);
    Font font;
    auto fontSize = param->GetProperty("size");
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        font.fontSize = Dimension(-1);
    } else {
        Dimension size;
        if (!ParseJsDimensionFp(fontSize, size) || size.Unit() == DimensionUnit::PERCENT) {
            font.fontSize = Dimension(-1);
            LOGW("Parse to dimension FP failed.");
        } else {
            font.fontSize = size;
        }
    }

    auto weight = param->GetProperty("weight");
    if (!weight->IsNull()) {
        std::string weightVal;
        if (weight->IsNumber()) {
            weightVal = std::to_string(weight->ToNumber<int32_t>());
        } else {
            ParseJsString(weight, weightVal);
        }
        font.fontWeight = ConvertStrToFontWeight(weightVal);
    }

    auto family = param->GetProperty("family");
    if (!family->IsNull() && family->IsString()) {
        auto familyVal = family->ToString();
        font.fontFamilies = ConvertStrToFontFamilies(familyVal);
    }

    auto style = param->GetProperty("style");
    if (!style->IsNull() && style->IsNumber()) {
        FontStyle styleVal = static_cast<FontStyle>(style->ToNumber<int32_t>());
        font.fontStyle = styleVal;
    }
    SearchModel::GetInstance()->SetTextFont(font);
}

void JSSearch::SetTextAlign(int32_t value)
{
    if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
        SearchModel::GetInstance()->SetTextAlign(TEXT_ALIGNS[value]);
    } else {
        LOGE("the value is error");
    }
}

void JSSearch::JsBorder(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsBorder(info);
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("args is not a object. %s", info[0]->ToString().c_str());
        return;
    }
    RefPtr<Decoration> decoration = nullptr;
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchComponent) {
        LOGE("search component error");
        return;
    }
    auto childComponent = searchComponent->GetChild();
    if (!childComponent) {
        LOGE("component error");
        return;
    }
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    if (!textFieldComponent) {
        LOGE("text component error");
        return;
    }
    decoration = textFieldComponent->GetDecoration();
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
    auto valueWidth = object->GetProperty("width");
    if (!valueWidth->IsUndefined()) {
        ParseBorderWidth(valueWidth);
    }
    auto valueColor = object->GetProperty("color");
    if (!valueColor->IsUndefined()) {
        ParseBorderColor(valueColor);
    }
    auto valueRadius = object->GetProperty("radius");
    if (!valueRadius->IsUndefined()) {
        ParseBorderRadius(valueRadius);
    }
    auto valueStyle = object->GetProperty("style");
    if (!valueStyle->IsUndefined()) {
        ParseBorderStyle(valueStyle);
    }
    ViewAbstractModelImpl::SwapBackBorder(decoration);
    textFieldComponent->SetOriginBorder(decoration->GetBorder());
    info.ReturnSelf();
}

void JSSearch::JsBorderWidth(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsBorderWidth(info);
        return;
    }
    if (!info[0]->IsObject() && !info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("args need a string or number or object");
        return;
    }
    RefPtr<Decoration> decoration = nullptr;
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchComponent) {
        LOGE("search component error");
        return;
    }
    auto childComponent = searchComponent->GetChild();
    if (!childComponent) {
        LOGE("component error");
        return;
    }
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    if (!textFieldComponent) {
        LOGE("text component error");
        return;
    }
    decoration = textFieldComponent->GetDecoration();
    JSViewAbstract::ParseBorderWidth(info[0]);
    ViewAbstractModelImpl::SwapBackBorder(decoration);
    textFieldComponent->SetOriginBorder(decoration->GetBorder());
}

void JSSearch::JsBorderColor(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsBorderColor(info);
        return;
    }
    if (!info[0]->IsObject() && !info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("args need a string or number or object");
        return;
    }
    RefPtr<Decoration> decoration = nullptr;
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchComponent) {
        LOGE("search component error");
        return;
    }
    auto childComponent = searchComponent->GetChild();
    if (!childComponent) {
        LOGE("component error");
        return;
    }
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    if (!textFieldComponent) {
        LOGE("text component error");
        return;
    }
    decoration = textFieldComponent->GetDecoration();
    JSViewAbstract::ParseBorderColor(info[0]);
    ViewAbstractModelImpl::SwapBackBorder(decoration);
    textFieldComponent->SetOriginBorder(decoration->GetBorder());
}

void JSSearch::JsBorderStyle(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsBorderStyle(info);
        return;
    }
    if (!info[0]->IsObject() && !info[0]->IsNumber()) {
        LOGE("args need a string or number or object");
        return;
    }
    RefPtr<Decoration> decoration = nullptr;
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchComponent) {
        LOGE("search component error");
        return;
    }
    auto childComponent = searchComponent->GetChild();
    if (!childComponent) {
        LOGE("component error");
        return;
    }
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    if (!textFieldComponent) {
        LOGE("text component error");
        return;
    }
    decoration = textFieldComponent->GetDecoration();
    JSViewAbstract::ParseBorderStyle(info[0]);
    ViewAbstractModelImpl::SwapBackBorder(decoration);
    textFieldComponent->SetOriginBorder(decoration->GetBorder());
}

void JSSearch::JsBorderRadius(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsBorderRadius(info);
        return;
    }
    if (!info[0]->IsObject() && !info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("args need a string or number or object");
        return;
    }
    RefPtr<Decoration> decoration = nullptr;
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchComponent) {
        LOGE("search component error");
        return;
    }
    auto childComponent = searchComponent->GetChild();
    if (!childComponent) {
        LOGE("component error");
        return;
    }
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    if (!textFieldComponent) {
        LOGE("text component error");
        return;
    }
    decoration = textFieldComponent->GetDecoration();
    JSViewAbstract::ParseBorderRadius(info[0]);
    ViewAbstractModelImpl::SwapBackBorder(decoration);
    textFieldComponent->SetOriginBorder(decoration->GetBorder());
}

void JSSearch::OnSubmit(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    SearchModel::GetInstance()->SetOnSubmit(std::move(callback));
}

void JSSearch::OnChange(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    SearchModel::GetInstance()->SetOnChange(std::move(callback));
}

void JSSearch::SetHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        LOGE("The arg is wrong, it is supposed to be a number arguments");
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetHeight(NG::CalcLength(value));
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(stack->GetMainComponent());
    if (!searchComponent) {
        LOGE("SearchComponent set height failed, SearchComponent is null.");
        return;
    }
    auto childComponent = searchComponent->GetChild();
    if (!childComponent) {
        LOGE("component error");
        return;
    }
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    if (!textFieldComponent) {
        LOGE("text component error");
        return;
    }
    textFieldComponent->SetHeight(value);
}

void JSSearch::SetOnCopy(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    SearchModel::GetInstance()->SetOnCopy(std::move(callback));
}

void JSSearch::SetOnCut(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    SearchModel::GetInstance()->SetOnCut(std::move(callback));
}

void JSSearch::SetOnPaste(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    SearchModel::GetInstance()->SetOnPaste(std::move(callback));
}

void JSSearch::SetCopyOption(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto copyOptions = CopyOptions::None;
    if (info[0]->IsNumber()) {
        auto emunNumber = info[0]->ToNumber<int>();
        copyOptions = static_cast<CopyOptions>(emunNumber);
    }
    SearchModel::GetInstance()->SetCopyOption(copyOptions);
}

void JSSearchController::JSBind(BindingTarget globalObj)
{
    JSClass<JSSearchController>::Declare("SearchController");
    JSClass<JSSearchController>::Method("caretPosition", &JSSearchController::CaretPosition);
    JSClass<JSSearchController>::Bind(globalObj, JSSearchController::Constructor, JSSearchController::Destructor);
}

void JSSearchController::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSSearchController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSSearchController::Destructor(JSSearchController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSSearchController::CaretPosition(int32_t caretPosition)
{
    auto controller = controller_.Upgrade();
    if (controller) {
        controller->CaretPosition(caretPosition);
    }
}

} // namespace OHOS::Ace::Framework
