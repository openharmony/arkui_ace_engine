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

#include <vector>

#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_menu.h"
#include "frameworks/core/components/common/properties/text_style.h"

namespace OHOS::Ace::Framework {
void JSMenu::Create(const JSCallbackInfo& info)
{
    auto menuTheme = GetTheme<SelectTheme>();
    auto menuComponent = AceType::MakeRefPtr<OHOS::Ace::MenuComponent>("", "menu");
    menuComponent->SetTheme(menuTheme);
    if (info.Length() > 0) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto titleObject = paramObject->GetProperty("title");
        if (!titleObject->IsString()) {
            LOGE("titlte type error");
            return;
        }
        auto title = titleObject->ToString();
        menuComponent->SetTitle(title);
    }
    ViewStackProcessor::GetInstance()->Push(menuComponent);
}

void JSMenu::JSBind(BindingTarget globalObj)
{
    JSClass<JSMenu>::Declare("Menu");
    JSClass<JSMenu>::StaticMethod("create", &JSMenu::Create);
    JSClass<JSMenu>::StaticMethod("show", &JSMenu::SetShow);
    JSClass<JSMenu>::StaticMethod("showPosition", &JSMenu::MenuShowPosition);

    // Common text style
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSMenu>::StaticMethod("fontColor", &JSMenu::SetFontColor, opt);
    JSClass<JSMenu>::StaticMethod("fontSize", &JSMenu::SetFontSize, opt);
    JSClass<JSMenu>::StaticMethod("fontWeight", &JSMenu::SetFontWeight, opt);
    JSClass<JSMenu>::StaticMethod("fontFamily", &JSMenu::SetFontFamily, opt);
    JSClass<JSMenu>::Inherit<JSContainerBase>();
    JSClass<JSMenu>::Bind<>(globalObj);
}

void JSMenu::SetShow(const JSCallbackInfo& info)
{
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto menuComponent = AceType::DynamicCast<MenuComponent>(mainComponent);
    if (!menuComponent) {
        LOGE("\033[0;31m cannot get menu component \033[0m");
    }

    auto paramObject = info[0];
    bool showStatus = paramObject->IsBoolean() ? paramObject->ToBoolean() : false;
    if (showStatus) {
        menuComponent->SetMenuShow(MenuStatus::ON);
    } else {
        menuComponent->SetMenuShow(MenuStatus::OFF);
    }
}

void JSMenu::MenuShowPosition(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("menu set position error, info is non-valid");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto xObject = paramObject->GetProperty("x");
    auto yObject = paramObject->GetProperty("y");
    if (!xObject->IsNumber() || !yObject->IsNumber()) {
        LOGE("menu show param error");
        return;
    }
    double x = xObject->ToNumber<double>();
    double y = yObject->ToNumber<double>();
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto menuComponent = AceType::DynamicCast<MenuComponent>(mainComponent);
    if (!menuComponent) {
        LOGE("\033[0;31m cannot get menu component \033[0m");
    }
    menuComponent->SetPopupPosition(Offset(x, y));
}

void JSMenu::SetFontColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        return;
    }
    auto menuComponent = GetMenuComponent();
    auto textStyle = menuComponent->GetTitleStyle();
    textStyle.SetTextColor(textColor);
    menuComponent->SetTitleStyle(std::move(textStyle));
}

void JSMenu::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    auto menuComponent = GetMenuComponent();
    auto textStyle = menuComponent->GetTitleStyle();
    textStyle.SetFontSize(fontSize);
    menuComponent->SetTitleStyle(std::move(textStyle));
}

void JSMenu::SetFontWeight(std::string value)
{
    auto menuComponent = GetMenuComponent();
    auto textStyle = menuComponent->GetTitleStyle();
    textStyle.SetFontWeight(ConvertStrToFontWeight(value));
    menuComponent->SetTitleStyle(std::move(textStyle));
}

void JSMenu::SetFontFamily(std::string value)
{
    auto menuComponent = GetMenuComponent();
    auto textStyle = menuComponent->GetTitleStyle();
    textStyle.SetFontFamilies(std::vector<std::string>({ value }));
    menuComponent->SetTitleStyle(std::move(textStyle));
}

RefPtr<MenuComponent> JSMenu::GetMenuComponent()
{
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto menuComponent = AceType::DynamicCast<MenuComponent>(mainComponent);
    if (!menuComponent) {
        LOGE("\033[0;31m cannot get menu component \033[0m");
    }
    return menuComponent;
}
} // namespace OHOS::Ace::Framework