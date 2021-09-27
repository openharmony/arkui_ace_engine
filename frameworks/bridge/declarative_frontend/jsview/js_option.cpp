/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_option.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/components/menu/menu_component.h"
#include "frameworks/core/components/text/text_component.h"
#include "frameworks/core/components/theme/theme_manager.h"

namespace OHOS::Ace::Framework {
void JSOption::Create(const JSCallbackInfo& info)
{
    std::string content;
    ParseJsString(info[0], content);
    auto optionTheme = GetTheme<SelectTheme>();
    auto textComponent = AceType::MakeRefPtr<OHOS::Ace::TextComponent>(content);
    auto optionComponent = AceType::MakeRefPtr<OHOS::Ace::OptionComponent>(optionTheme);
    optionComponent->SetTheme(optionTheme);
    optionComponent->SetText(textComponent);
    optionComponent->SetValue(content);

    auto stack = ViewStackProcessor::GetInstance();
    auto currentComponent = AceType::DynamicCast<Component>(stack->GetMainComponent());
    if (AceType::TypeId(currentComponent) != MenuComponent::TypeId()) {
        LOGE("option parent type is not menu!");
        return;
    }
    auto tmp = AceType::DynamicCast<MenuComponent>(currentComponent);
    tmp->AppendOption(optionComponent);
    stack->Push(optionComponent);
    JSInteractableView::SetFocusNode(true);
}

void JSOption::JSBind(BindingTarget globalObj)
{
    JSClass<JSOption>::Declare("Option");
    JSClass<JSOption>::StaticMethod("create", &JSOption::Create);

    // Commom click event
    JSClass<JSOption>::StaticMethod("onClick", &JSOption::JSOnClick);

    // Common text style
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSOption>::StaticMethod("fontColor", &JSOption::SetFontColor, opt);
    JSClass<JSOption>::StaticMethod("fontSize", &JSOption::SetFontSize, opt);
    JSClass<JSOption>::StaticMethod("fontWeight", &JSOption::SetFontWeight, opt);
    JSClass<JSOption>::StaticMethod("fontFamily", &JSOption::SetFontFamily, opt);

    JSClass<JSOption>::Inherit<JSViewAbstract>();
    JSClass<JSOption>::Bind<>(globalObj);
}

void JSOption::JSOnClick(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        JSRef<JSFunc> clickFunction = JSRef<JSFunc>::Cast(info[0]);
        auto onClickFunc = AceType::MakeRefPtr<JsClickFunction>(clickFunction);
        auto optionComponent = JSOption::GetOptionComponent();
        optionComponent->SetCustomizedCallback([func = std::move(onClickFunc)]() {
            func->Execute();
        });
    }
}

RefPtr<OptionComponent> JSOption::GetOptionComponent()
{
    auto stack = ViewStackProcessor::GetInstance();
    if (!stack) {
        LOGE("Can't get view stack");
        return nullptr;
    }
    auto optionComponent = AceType::DynamicCast<OptionComponent>(stack->GetMainComponent());
    if (!optionComponent) {
        LOGE("Can't get option component");
        return nullptr;
    }
    return optionComponent;
}

void JSOption::SetFontColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        return;
    }
    auto optionComponent = GetOptionComponent();
    if (!optionComponent) {
        return;
    }
    optionComponent->SetFontColor(textColor);
}

void JSOption::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    auto optionComponent = GetOptionComponent();
    if (!optionComponent) {
        return;
    }
    optionComponent->SetFontSize(fontSize);
}

void JSOption::SetFontWeight(std::string value)
{
    auto optionComponent = GetOptionComponent();
    if (!optionComponent) {
        return;
    }
    optionComponent->SetFontWeight(ConvertStrToFontWeight(value));
}

void JSOption::SetFontFamily(std::string value)
{
    auto optionComponent = GetOptionComponent();
    if (!optionComponent) {
        return;
    }
    optionComponent->SetFontFamily(value);
}
} // namespace OHOS::Ace::Framework