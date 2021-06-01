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

#include "core/components/button/button_component.h"

#include "core/components/button/button_element.h"
#include "core/components/button/button_theme.h"
#include "core/components/button/render_button.h"
#include "core/components/padding/padding_component.h"
#include "core/components/text/text_component.h"
#include "core/components/theme/theme_manager.h"

namespace OHOS::Ace {

ButtonComponent::ButtonComponent(const std::list<RefPtr<Component>>& children) : ComponentGroup(children)
{
    buttonController_ = AceType::MakeRefPtr<ButtonProgressController>();
}

RefPtr<RenderNode> ButtonComponent::CreateRenderNode()
{
    return RenderButton::Create();
}

RefPtr<Element> ButtonComponent::CreateElement()
{
    return AceType::MakeRefPtr<ButtonElement>();
}

RefPtr<ButtonComponent> ButtonBuilder::Build(const RefPtr<ThemeManager>& themeManager, const std::string& text)
{
    auto buttonTheme = AceType::DynamicCast<ButtonTheme>(themeManager->GetTheme(ButtonTheme::TypeId()));
    if (!buttonTheme) {
        TextStyle defaultStyle;
        return ButtonBuilder::Build(themeManager, text, defaultStyle);
    }
    TextStyle textStyle = buttonTheme->GetTextStyle();
    textStyle.SetAdaptTextSize(buttonTheme->GetMaxFontSize(), buttonTheme->GetMinFontSize());
    textStyle.SetMaxLines(buttonTheme->GetTextMaxLines());
    textStyle.SetTextOverflow(TextOverflow::ELLIPSIS);
    return ButtonBuilder::Build(themeManager, text, textStyle);
}

RefPtr<ButtonComponent> ButtonBuilder::Build(const RefPtr<ThemeManager>& themeManager, const std::string& text,
    TextStyle& textStyle, const Color& textFocusColor, bool useTextFocus)
{
    auto textComponent = AceType::MakeRefPtr<TextComponent>(text);
    auto padding = AceType::MakeRefPtr<PaddingComponent>();
    padding->SetChild(textComponent);
    std::list<RefPtr<Component>> buttonChildren;
    buttonChildren.emplace_back(padding);
    auto buttonComponent = AceType::MakeRefPtr<ButtonComponent>(buttonChildren);
    auto buttonTheme = AceType::DynamicCast<ButtonTheme>(themeManager->GetTheme(ButtonTheme::TypeId()));
    if (!buttonTheme) {
        return buttonComponent;
    }
    if (useTextFocus) {
        textComponent->SetFocusColor(textFocusColor);
    } else {
        textComponent->SetFocusColor(buttonTheme->GetTextFocusColor());
    }
    textComponent->SetTextStyle(textStyle);
    padding->SetPadding(buttonTheme->GetPadding());
    buttonComponent->SetHeight(buttonTheme->GetHeight());
    buttonComponent->SetRectRadius(buttonTheme->GetHeight() / 2.0);
    buttonComponent->SetBackgroundColor(buttonTheme->GetBgColor());
    buttonComponent->SetClickedColor(buttonTheme->GetClickedColor());
    buttonComponent->SetFocusColor(buttonTheme->GetBgFocusColor());
    buttonComponent->SetFocusAnimationColor(buttonTheme->GetBgFocusColor());
    return buttonComponent;
}

} // namespace OHOS::Ace
