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

#include "core/components/text/text_component.h"

#include "core/components/text/render_text.h"
#include "core/components/text/text_element.h"

namespace OHOS::Ace {

TextComponent::TextComponent(const std::string& data) : ComponentGroup(std::list<RefPtr<Component>>())
{
    if (!declaration_) {
        declaration_ = AceType::MakeRefPtr<TextDeclaration>();
        declaration_->Init();
    }
    SetData(data);
}

RefPtr<RenderNode> TextComponent::CreateRenderNode()
{
    return RenderText::Create();
}

RefPtr<Element> TextComponent::CreateElement()
{
    return AceType::MakeRefPtr<TextElement>();
}

const std::string& TextComponent::GetData() const
{
    return declaration_->GetData();
}

void TextComponent::SetData(const std::string& data)
{
    declaration_->SetData(data);
}

const TextStyle& TextComponent::GetTextStyle() const
{
    return declaration_->GetTextStyle();
}

void TextComponent::SetTextStyle(const TextStyle& textStyle)
{
    declaration_->SetTextStyle(textStyle);
}

const Color& TextComponent::GetFocusColor() const
{
    return declaration_->GetFocusColor();
}

void TextComponent::SetFocusColor(const Color& focusColor)
{
    declaration_->SetFocusColor(focusColor);
}

bool TextComponent::GetMaxWidthLayout() const
{
    return declaration_->IsMaxWidthLayout();
}

void TextComponent::SetMaxWidthLayout(bool isMaxWidthLayout)
{
    declaration_->SetIsMaxWidthLayout(isMaxWidthLayout);
}

bool TextComponent::GetAutoMaxLines() const
{
    return declaration_->GetAutoMaxLines();
}

void TextComponent::SetAutoMaxLines(bool autoMaxLines)
{
    declaration_->SetAutoMaxLines(autoMaxLines);
}

bool TextComponent::IsChanged() const
{
    return declaration_->IsChanged();
}

void TextComponent::SetIsChanged(bool isChanged)
{
    declaration_->SetIsChanged(isChanged);
}

void TextComponent::SetOnClick(const EventMarker& onClick)
{
    declaration_->SetClickEvent(onClick);
}

void TextComponent::SetDeclaration(const RefPtr<TextDeclaration>& declaration)
{
    if (declaration) {
        declaration_ = declaration;
    }
}

const RefPtr<TextDeclaration>& TextComponent::GetDeclaration() const
{
    return declaration_;
}

} // namespace OHOS::Ace
