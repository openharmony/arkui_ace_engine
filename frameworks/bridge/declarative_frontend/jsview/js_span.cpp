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
#include "frameworks/bridge/declarative_frontend/jsview/js_container_span.h"

#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_hover_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/models/span_model_impl.h"
#include "bridge/declarative_frontend/jsview/models/text_model_impl.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
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
#ifdef NG_BUILD
    static NG::SpanModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::SpanModelNG instance;
        return &instance;
    } else {
        static Framework::SpanModelImpl instance;
        return &instance;
    }
#endif
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {

const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextCase> TEXT_CASES = { TextCase::NORMAL, TextCase::LOWERCASE, TextCase::UPPERCASE };
constexpr TextDecorationStyle DEFAULT_TEXT_DECORATION_STYLE = TextDecorationStyle::SOLID;

} // namespace

void JSSpan::SetFont(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto infoZero = info[0];
    if (infoZero->IsUndefined() || infoZero->IsNull()) {
        SpanModel::GetInstance()->ResetFont();
        return;
    }
    Font font;
    JSText::GetFontInfo(info, font);
    SpanModel::GetInstance()->SetFont(font);
}

void JSSpan::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension fontSize;
    if (!ParseJsDimensionFpNG(info[0], fontSize, false) || fontSize.IsNegative()) {
        SpanModel::GetInstance()->ResetFontSize();
        return;
    }
    SpanModel::GetInstance()->SetFontSize(fontSize);
}

void JSSpan::SetFontWeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    JSRef<JSVal> args = info[0];
    std::string fontWeight;
    if (args->IsNumber()) {
        fontWeight = args->ToString();
    } else {
        ParseJsString(args, fontWeight);
    }
    SpanModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(fontWeight));
}

void JSSpan::SetTextColor(const JSCallbackInfo& info)
{
    Color textColor;
    auto infoZero = info[0];
    if (infoZero->IsUndefined() || infoZero->IsNull()) {
        SpanModel::GetInstance()->ResetTextColor();
        return;
    }
    if (!ParseJsColor(infoZero, textColor)) {
        SpanModel::GetInstance()->ResetTextColor();
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
        SpanModel::GetInstance()->ResetItalicFontStyle();
    }
}

void JSSpan::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        SpanModel::GetInstance()->ResetFontFamily();
        return;
    }
    SpanModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSSpan::SetLetterSpacing(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionFpNG(info[0], value, false)) {
        value.Reset();
        SpanModel::GetInstance()->SetLetterSpacing(value);
        return;
    }
    SpanModel::GetInstance()->SetLetterSpacing(value);
}

void JSSpan::SetBaselineOffset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    NG::CalcLength value;
    if (ConvertFromJSValueNG(info[0], value) &&
        value.GetDimensionContainsNegative().Unit() != DimensionUnit::PERCENT) {
        SpanModel::GetInstance()->SetBaselineOffset(value.GetDimensionContainsNegative());
        return;
    }
    value.Reset();
    SpanModel::GetInstance()->SetBaselineOffset(value.GetDimensionContainsNegative());
}

void JSSpan::SetTextCase(int32_t value)
{
    if (value >= 0 && value < static_cast<int32_t>(TEXT_CASES.size())) {
        auto textCase = TEXT_CASES[value];
        SpanModel::GetInstance()->SetTextCase(textCase);
    }
}

void JSSpan::SetDecoration(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        SpanModel::GetInstance()->SetTextDecoration(TextDecoration::NONE);
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> typeValue = obj->GetProperty("type");
    JSRef<JSVal> colorValue = obj->GetProperty("color");
    JSRef<JSVal> styleValue = obj->GetProperty("style");
    JSRef<JSVal> thicknessScaleValue = obj->GetProperty("thicknessScale");

    std::optional<TextDecoration> textDecoration;
    if (typeValue->IsNumber()) {
        textDecoration = static_cast<TextDecoration>(typeValue->ToNumber<int32_t>());
    } else {
        auto theme = GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        textDecoration = theme->GetTextDecoration();
    }
    std::optional<TextDecorationStyle> textDecorationStyle;
    if (styleValue->IsNumber()) {
        textDecorationStyle = static_cast<TextDecorationStyle>(styleValue->ToNumber<int32_t>());
    } else {
        textDecorationStyle = DEFAULT_TEXT_DECORATION_STYLE;
    }
    std::optional<Color> colorVal;
    Color result;
    if (ParseJsColor(colorValue, result)) {
        colorVal = result;
    } else {
        auto theme = GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        if (Container::CurrentColorMode() == ColorMode::DARK) {
            colorVal = theme->GetTextStyle().GetTextColor();
        } else {
            colorVal = Color::BLACK;
        }
    }
    float lineThicknessScale = 1.0f;
    if (thicknessScaleValue->IsNumber()) {
        lineThicknessScale = thicknessScaleValue->ToNumber<float>();
    }
    lineThicknessScale = lineThicknessScale < 0 ? 1.0f : lineThicknessScale;
    if (textDecoration) {
        SpanModel::GetInstance()->SetTextDecoration(textDecoration.value());
    }
    if (colorVal) {
        SpanModel::GetInstance()->SetTextDecorationColor(colorVal.value());
    }
    SpanModel::GetInstance()->SetTextDecorationStyle(textDecorationStyle.value());
    SpanModel::GetInstance()->SetLineThicknessScale(lineThicknessScale);
}

void JSSpan::JsOnClick(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        if (info[0]->IsUndefined() && IsDisableEventVersion()) {
            SpanModel::GetInstance()->ClearOnClick();
            return;
        }
        if (!info[0]->IsFunction()) {
            return;
        }
        auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onClick = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = targetNode](
                           BaseEventInfo* info) {
            auto* clickInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onClick");
            PipelineContext::SetCallBackNode(node);
            func->Execute(*clickInfo);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
            JSInteractableView::ReportClickEvent(node);
#endif
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
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto clickFunc = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc), impl,
                             node = targetNode](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            const auto* clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
            auto newInfo = *clickInfo;
            if (impl) {
                impl->UpdateEventInfo(newInfo);
            }
            ACE_SCORING_EVENT("Span.onClick");
            PipelineContext::SetCallBackNode(node);
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
    CalcDimension value;
    if (!ParseJsDimensionFpNG(info[0], value)) {
        value.Reset();
        SpanModel::GetInstance()->SetLineHeight(value);
        return;
    }
    if (value.IsNegative()) {
        value.Reset();
    }
    SpanModel::GetInstance()->SetLineHeight(value);
}

void JSSpan::SetTextShadow(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::vector<Shadow> shadows;
    ParseTextShadowFromShadowObject(info[0], shadows);
    SpanModel::GetInstance()->SetTextShadow(shadows);
}
 

void JSSpan::SetAccessibilityText(const JSCallbackInfo& info)
{
    std::string text;
    if ((info.Length() > 0) && info[0]->IsString()) {
        text = info[0]->ToString();
    }
    SpanModel::GetInstance()->SetAccessibilityText(text);
}

void JSSpan::SetAccessibilityDescription(const JSCallbackInfo& info)
{
    std::string description;
    if ((info.Length() > 0) && info[0]->IsString()) {
        description = info[0]->ToString();
    }
    SpanModel::GetInstance()->SetAccessibilityDescription(description);
}

void JSSpan::SetAccessibilityLevel(const JSCallbackInfo& info)
{
    std::string level;
    if ((info.Length() > 0) && info[0]->IsString()) {
        level = info[0]->ToString();
    }
    SpanModel::GetInstance()->SetAccessibilityImportance(level);
}

void JSSpan::SetOnHover(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        SpanModel::GetInstance()->ResetOnHover();
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }
    RefPtr<JsHoverFunction> jsOnHoverFunc = AceType::MakeRefPtr<JsHoverFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onHover = [execCtx = info.GetExecutionContext(), func = std::move(jsOnHoverFunc), node = frameNode](
        bool isHover, HoverInfo& hoverInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onHover");
        PipelineContext::SetCallBackNode(node);
        func->HoverExecute(isHover, hoverInfo);
    };
    SpanModel::GetInstance()->SetOnHover(std::move(onHover));
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
    JSClass<JSSpan>::StaticMethod("baselineOffset", &JSSpan::SetBaselineOffset, opt);
    JSClass<JSSpan>::StaticMethod("textCase", &JSSpan::SetTextCase, opt);
    JSClass<JSSpan>::StaticMethod("textShadow", &JSSpan::SetTextShadow, opt);
    JSClass<JSSpan>::StaticMethod("decoration", &JSSpan::SetDecoration);
    JSClass<JSSpan>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSpan>::StaticMethod("onHover", &JSSpan::SetOnHover);
    JSClass<JSSpan>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSpan>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSpan>::StaticMethod("remoteMessage", &JSSpan::JsRemoteMessage);
    JSClass<JSSpan>::StaticMethod("onClick", &JSSpan::JsOnClick);
    JSClass<JSSpan>::StaticMethod("lineHeight", &JSSpan::SetLineHeight, opt);
    JSClass<JSSpan>::StaticMethod("textBackgroundStyle", &JSContainerSpan::SetTextBackgroundStyle, opt);
    JSClass<JSSpan>::StaticMethod("accessibilityText", &JSSpan::SetAccessibilityText, opt);
    JSClass<JSSpan>::StaticMethod("accessibilityDescription", &JSSpan::SetAccessibilityDescription, opt);
    JSClass<JSSpan>::StaticMethod("accessibilityLevel", &JSSpan::SetAccessibilityLevel, opt);
    JSClass<JSSpan>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSSpan::Create(const JSCallbackInfo& info)
{
    std::u16string label;
    if (info.Length() > 0) {
        ParseJsString(info[0], label);
    }
    SpanModel::GetInstance()->Create(label);
}

} // namespace OHOS::Ace::Framework
