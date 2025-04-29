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

#include "frameworks/bridge/declarative_frontend/jsview/js_piece.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/piece/piece_component.h"

namespace OHOS::Ace::Framework {

const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };

void JSPiece::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto getContent = paramObject->GetProperty("content");
    auto getIcon = paramObject->GetProperty("icon");
    std::string content;
    std::string icon;
    if (getContent->IsString()) {
        content = getContent->ToString();
    }
    if (getIcon->IsString()) {
        icon = getIcon->ToString();
    }
    auto component = AceType::MakeRefPtr<PieceComponent>();
    component->SetContent(content);
    component->SetIcon(icon);
    auto theme = GetTheme<PieceTheme>();
    if (!theme) {
        return;
    }
    component->InitializeStyle(theme);
    Border border;
    border.SetBorderRadius(Radius(theme->GetHeight() / 2.0));
    component->SetBorder(border);
    ViewStackProcessor::GetInstance()->Push(component);

    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    box->SetHeight(theme->GetHeight(), option);
    Edge edge;
    edge.SetLeft(theme->GetPaddingHorizontal());
    edge.SetRight(theme->GetPaddingHorizontal());
    edge.SetTop(theme->GetPaddingVertical());
    edge.SetBottom(theme->GetPaddingVertical());
    box->SetPadding(edge);
}

void JSPiece::JSBind(BindingTarget globalObj)
{
    JSClass<JSPiece>::Declare("Piece");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSPiece>::StaticMethod("create", &JSPiece::Create, opt);
    JSClass<JSPiece>::StaticMethod("iconPosition", &JSPiece::SetIconPosition, opt);
    JSClass<JSPiece>::StaticMethod("showDelete", &JSPiece::SetShowDelete, opt);
    JSClass<JSPiece>::StaticMethod("fontColor", &JSPiece::SetTextColor, opt);
    JSClass<JSPiece>::StaticMethod("fontSize", &JSPiece::SetFontSize, opt);
    JSClass<JSPiece>::StaticMethod("fontStyle", &JSPiece::SetFontStyle, opt);
    JSClass<JSPiece>::StaticMethod("fontWeight", &JSPiece::SetFontWeight, opt);
    JSClass<JSPiece>::StaticMethod("fontFamily", &JSPiece::SetFontFamily, opt);
    JSClass<JSPiece>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSPiece>::StaticMethod("onClose", &JSPiece::JsOnClose);
    JSClass<JSPiece>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSPiece>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSPiece>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSPiece>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSPiece>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSPiece>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSPiece>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSPiece>::InheritAndBind<JSViewAbstract>(globalObj);
}

// showDelete Parameters should be bool type,but after click event triggering,
// The callback function transfers parameters, and the parameter type changes to number.
void JSPiece::SetShowDelete(const JSCallbackInfo& info)
{
    bool showDelete = false;
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<PieceComponent>(stack->GetMainComponent());
    if (!component) {
        return;
    }
    if (info[0]->IsBoolean()) {
        showDelete = info[0]->ToBoolean();
        component->SetShowDelete(showDelete);
    } else if (info[0]->IsNumber()) {
        int32_t arg = info[0]->ToNumber<int32_t>();
        if (arg == 0 || arg == 1) {
            showDelete = static_cast<bool>(arg);
            component->SetShowDelete(showDelete);
        }
    } else {
        component->SetShowDelete(showDelete);
    }
}

void JSPiece::JsOnClose(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        JSRef<JSFunc> clickFunction = JSRef<JSFunc>::Cast(info[0]);
        auto onClickFunc = AceType::MakeRefPtr<JsClickFunction>(clickFunction);
        EventMarker clickEventId(
            [execCtx = info.GetExecutionContext(), func = std::move(onClickFunc)](const BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("Piece.onClose");
                func->Execute();
            });
        auto pieceComponent =
            AceType::DynamicCast<PieceComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (pieceComponent) {
            pieceComponent->SetOnDelete(clickEventId);
        }
    }
}

void JSPiece::SetTextColor(const JSCallbackInfo& info)
{
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<PieceComponent>(stack->GetMainComponent());
    if (!component) {
        return;
    }
    auto textStyle = component->GetTextStyle();
    textStyle.SetTextColor(textColor);
    component->SetTextStyle(std::move(textStyle));
}

void JSPiece::SetFontSize(const JSCallbackInfo& info)
{
    CalcDimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<PieceComponent>(stack->GetMainComponent());
    if (!component) {
        return;
    }
    auto textStyle = component->GetTextStyle();
    textStyle.SetFontSize(fontSize);
    component->SetTextStyle(std::move(textStyle));
}

void JSPiece::SetFontStyle(int32_t value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<PieceComponent>(stack->GetMainComponent());
    if (!component) {
        return;
    }
    if (value >= 0 && value < static_cast<int32_t>(FONT_STYLES.size())) {
        auto textStyle = component->GetTextStyle();
        textStyle.SetFontStyle(FONT_STYLES[value]);
        component->SetTextStyle(std::move(textStyle));
    }
}

void JSPiece::SetFontWeight(const std::string& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<PieceComponent>(stack->GetMainComponent());
    if (!component) {
        return;
    }

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontWeight(ConvertStrToFontWeight(value));
    component->SetTextStyle(std::move(textStyle));
}

void JSPiece::SetFontFamily(const JSCallbackInfo& info)
{
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<PieceComponent>(stack->GetMainComponent());
    if (!component) {
        return;
    }
    auto textStyle = component->GetTextStyle();
    textStyle.SetFontFamilies(fontFamilies);
    component->SetTextStyle(std::move(textStyle));
}

void JSPiece::SetIconPosition(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<PieceComponent>(stack->GetMainComponent());
    if (!component) {
        return;
    }

    auto pieceIconPosition = static_cast<OHOS::Ace::IconPosition>(info[0]->ToNumber<int32_t>());
    component->SetIconPosition(pieceIconPosition);
}

} // namespace OHOS::Ace::Framework
