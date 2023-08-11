/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_span.h"

#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/models/span_model_impl.h"
#include "bridge/declarative_frontend/jsview/models/text_model_impl.h"
#ifndef NG_BUILD
#include "bridge/declarative_frontend/view_stack_processor.h"
#endif
#include "bridge/declarative_frontend/jsview/js_text.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/text/span_model.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model.h"

namespace OHOS::Ace {

std::unique_ptr<SpanModel> SpanModel::instance_ = nullptr;
std::mutex SpanModel::mutex_;

SpanModel* SpanModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::SpanModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::SpanModelNG());
            } else {
                instance_.reset(new Framework::SpanModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {

const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextCase> TEXT_CASES = { TextCase::NORMAL, TextCase::LOWERCASE, TextCase::UPPERCASE };

} // namespace

void JSSpan::SetFont(const JSCallbackInfo& info)
{
    Font font;
    JSText::GetFontInfo(info, font);
    SpanModel::GetInstance()->SetFont(font);
}

void JSSpan::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }

    SpanModel::GetInstance()->SetFontSize(fontSize);
}

void JSSpan::SetFontWeight(const std::string& value)
{
    SpanModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(value));
}

void JSSpan::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        return;
    }
    SpanModel::GetInstance()->SetTextColor(textColor);
}

void JSSpan::SetFontStyle(int32_t value)
{
    if (value >= 0 && value < static_cast<int32_t>(FONT_STYLES.size())) {
        auto style = FONT_STYLES[value];
        SpanModel::GetInstance()->SetItalicFontStyle(style);
    } else {
        LOGE("Text fontStyle(%{public}d) illegal value", value);
    }
}

void JSSpan::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        LOGE("Parse FontFamilies failed");
        return;
    }
    SpanModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSSpan::SetLetterSpacing(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionFp(info[0], value)) {
        return;
    }
    SpanModel::GetInstance()->SetLetterSpacing(value);
}

void JSSpan::SetTextCase(int32_t value)
{
    if (value >= 0 && value < static_cast<int32_t>(TEXT_CASES.size())) {
        auto textCase = TEXT_CASES[value];
        SpanModel::GetInstance()->SetTextCase(textCase);
    } else {
        LOGE("Text textCase(%{public}d) illegal value", value);
    }
}

void JSSpan::SetDecoration(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        LOGE("info[0] not is Object");
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> typeValue = obj->GetProperty("type");
    JSRef<JSVal> colorValue = obj->GetProperty("color");
    JSRef<JSVal> styleValue = obj->GetProperty("style");

    std::optional<TextDecoration> textDecoration;
    if (typeValue->IsNumber()) {
        textDecoration = static_cast<TextDecoration>(typeValue->ToNumber<int32_t>());
    }
    std::optional<TextDecorationStyle> textDecorationStyle;
    if (styleValue->IsNumber()) {
        textDecorationStyle = static_cast<TextDecorationStyle>(styleValue->ToNumber<int32_t>());
    }
    std::optional<Color> colorVal;
    Color result;
    if (ParseJsColor(colorValue, result)) {
        colorVal = result;
    } else {
        // default color
        colorVal = Color::BLACK;
    }
    if (textDecoration) {
        SpanModel::GetInstance()->SetTextDecoration(textDecoration.value());
    }
    if (colorVal) {
        SpanModel::GetInstance()->SetTextDecorationColor(colorVal.value());
    }
    if (textDecorationStyle) {
        SpanModel::GetInstance()->SetTextDecorationStyle(textDecorationStyle.value());
    }
}

void JSSpan::JsOnClick(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        if (info[0]->IsUndefined() && IsDisableEventVersion()) {
            LOGD("JsOnClick callback is undefined");
            SpanModel::GetInstance()->ClearOnClick();
            return;
        }
        if (!info[0]->IsFunction()) {
            LOGW("the info is not click function");
            return;
        }
        auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto onClick = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc](const BaseEventInfo* info) {
            const auto* clickInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onClick");
            func->Execute(*clickInfo);
        };
        SpanModel::GetInstance()->SetOnClick(std::move(onClick));
        return;
    }
#ifndef NG_BUILD
    if (info[0]->IsFunction()) {
        auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
        CHECK_NULL_VOID(inspector);
        auto impl = inspector->GetInspectorFunctionImpl();
        RefPtr<JsClickFunction> jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto clickFunc = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc), impl](
                             const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            LOGD("About to call onclick method on js");
            const auto* clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
            auto newInfo = *clickInfo;
            if (impl) {
                impl->UpdateEventInfo(newInfo);
            }
            ACE_SCORING_EVENT("Span.onClick");
            func->Execute(newInfo);
        };
        SpanModel::GetInstance()->SetOnClick(std::move(clickFunc));
    }
#endif
}

void JSSpan::JsRemoteMessage(const JSCallbackInfo& info)
{
#ifndef NG_BUILD
    RemoteCallback remoteCallback;
    JSInteractableView::JsRemoteMessage(info, remoteCallback);
    EventMarker remoteMessageEventId(std::move(remoteCallback));
    auto* stack = ViewStackProcessor::GetInstance();
    auto textSpanComponent = AceType::DynamicCast<TextSpanComponent>(stack->GetMainComponent());
    textSpanComponent->SetRemoteMessageEventId(remoteMessageEventId);
#endif
}

void JSSpan::SetLineHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionFp(info[0], value)) {
        return;
    }
    SpanModel::GetInstance()->SetLineHeight(value);
}

void JSSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSSpan>::Declare("Span");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSpan>::StaticMethod("create", &JSSpan::Create, opt);
    JSClass<JSSpan>::StaticMethod("font", &JSSpan::SetFont, opt);
    JSClass<JSSpan>::StaticMethod("fontColor", &JSSpan::SetTextColor, opt);
    JSClass<JSSpan>::StaticMethod("fontSize", &JSSpan::SetFontSize, opt);
    JSClass<JSSpan>::StaticMethod("fontWeight", &JSSpan::SetFontWeight, opt);
    JSClass<JSSpan>::StaticMethod("fontStyle", &JSSpan::SetFontStyle, opt);
    JSClass<JSSpan>::StaticMethod("fontFamily", &JSSpan::SetFontFamily, opt);
    JSClass<JSSpan>::StaticMethod("letterSpacing", &JSSpan::SetLetterSpacing, opt);
    JSClass<JSSpan>::StaticMethod("textCase", &JSSpan::SetTextCase, opt);
    JSClass<JSSpan>::StaticMethod("decoration", &JSSpan::SetDecoration);
    JSClass<JSSpan>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSpan>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSSpan>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSpan>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSpan>::StaticMethod("remoteMessage", &JSSpan::JsRemoteMessage);
    JSClass<JSSpan>::StaticMethod("onClick", &JSSpan::JsOnClick);
    JSClass<JSSpan>::StaticMethod("lineHeight", &JSSpan::SetLineHeight, opt);
    JSClass<JSSpan>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSSpan::Create(const JSCallbackInfo& info)
{
    std::string label;
    if (info.Length() > 0) {
        ParseJsString(info[0], label);
    }
    SpanModel::GetInstance()->Create(label);
}

} // namespace OHOS::Ace::Framework
