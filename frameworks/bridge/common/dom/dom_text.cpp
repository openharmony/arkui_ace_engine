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

#include "frameworks/bridge/common/dom/dom_text.h"

namespace OHOS::Ace::Framework {

DOMText::DOMText(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    textChild_ = AceType::MakeRefPtr<TextComponent>("");
}

void DOMText::ResetInitializedStyle()
{
    if (declaration_) {
        declaration_->InitializeStyle();
    }
    CheckAndSetAllSpanStyle();
}

void DOMText::CheckAndSetAllSpanStyle()
{
    for (const auto& child : GetChildList()) {
        auto domSpan = AceType::DynamicCast<DOMSpan>(child);
        if (!domSpan) {
            continue;
        }
        auto spanComponent = AceType::DynamicCast<TextSpanComponent>(domSpan->GetSpecializedComponent());
        if (!spanComponent) {
            continue;
        }

        // If span component has no developer-set styles, then set text styles to span
        TextStyle spanStyle = spanComponent->GetTextStyle();
        CheckAndSetSpanStyle(domSpan, spanStyle);
        domSpan->SetTextStyle(spanStyle);
        spanComponent->SetTextStyle(spanStyle);
    }
}

void DOMText::CheckAndSetSpanStyle(const RefPtr<DOMSpan>& dmoSpan, TextStyle& spanStyle)
{
    auto textDeclaration = AceType::DynamicCast<TextDeclaration>(declaration_);
    if (!textDeclaration) {
        return;
    }

    const auto& textStyle = textDeclaration->GetTextStyle();
    if (!dmoSpan->HasSetFontSize()) {
        spanStyle.SetFontSize(textStyle.GetFontSize());
    }
    if (!dmoSpan->HasSetFontStyle()) {
        spanStyle.SetFontStyle(textStyle.GetFontStyle());
    }
    if (!dmoSpan->HasSetFontColor()) {
        spanStyle.SetTextColor(textStyle.GetTextColor());
    }
    if (!dmoSpan->HasSetFontWeight()) {
        spanStyle.SetFontWeight(textStyle.GetFontWeight());
    }
    if (!dmoSpan->HasSetTextDecoration()) {
        spanStyle.SetTextDecoration(textStyle.GetTextDecoration());
    }
    if (!dmoSpan->HasSetTextDecorationColor()) {
        spanStyle.SetTextDecorationColor(textStyle.GetTextDecorationColor());
    }
    if (!dmoSpan->HasSetTextDecorationStyle()) {
        spanStyle.SetTextDecorationStyle(textStyle.GetTextDecorationStyle());
    }
    if (!dmoSpan->HasSetFontFamily()) {
        spanStyle.SetFontFamilies(textStyle.GetFontFamilies());
    }
    if (!dmoSpan->HasSetAllowScale()) {
        spanStyle.SetAllowScale(textStyle.IsAllowScale());
    }
    if (!dmoSpan->HasSetFontFeatures()) {
        spanStyle.SetFontFeatures(textStyle.GetFontFeatures());
    }
    spanStyle.SetLetterSpacing(textStyle.GetLetterSpacing());
    spanStyle.SetLineHeight(textStyle.GetLineHeight(), textStyle.HasHeightOverride());
}

void DOMText::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    ACE_DCHECK(child);
    auto spanComponent = AceType::DynamicCast<TextSpanComponent>(child->GetSpecializedComponent());
    if (!spanComponent) {
        return;
    }

    // If span component has no developer-set styles, then set text styles to span
    TextStyle spanStyle = spanComponent->GetTextStyle();
    auto domSpan = AceType::DynamicCast<DOMSpan>(child);
    ACE_DCHECK(domSpan);
    CheckAndSetSpanStyle(domSpan, spanStyle);
    domSpan->SetTextStyle(spanStyle);
    spanComponent->SetTextStyle(spanStyle);
    textChild_->InsertChild(slot, child->GetRootComponent());
}

void DOMText::OnChildNodeRemoved(const RefPtr<DOMNode>& child)
{
    ACE_DCHECK(child);
    textChild_->RemoveChild(child->GetRootComponent());
}

void DOMText::PrepareSpecializedComponent()
{
    textChild_->SetTextDirection(IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR);

    auto textDeclaration = AceType::DynamicCast<TextDeclaration>(declaration_);
    if (!textDeclaration) {
        return;
    }
    bool isCard = AceApplicationInfo::GetInstance().GetIsCardType();
    if (isCard) {
        auto& style = textDeclaration->MaybeResetStyle<TextSpecializedStyle>(StyleTag::SPECIALIZED_STYLE);
        if (style.IsValid()) {
            style.textStyle.SetAllowScale(false);
            if (style.textStyle.GetFontSize().Unit() == DimensionUnit::FP) {
                style.textStyle.SetAllowScale(true);
            }
        }
    }
    textDeclaration->SetIsMaxWidthLayout(boxComponent_->GetWidthDimension().IsValid());
    CheckAndSetAllSpanStyle();
    textChild_->SetDeclaration(textDeclaration);

    // set box align
    if (!textDeclaration->IsMaxWidthLayout()) {
        SetBoxAlignForText();
    }
}

void DOMText::SetBoxAlignForText()
{
    auto textDeclaration = AceType::DynamicCast<TextDeclaration>(declaration_);
    if (!textDeclaration) {
        return;
    }

    switch (textDeclaration->GetTextStyle().GetTextAlign()) {
        case TextAlign::LEFT:
            SetAlignment(Alignment::CENTER_LEFT);
            break;
        case TextAlign::CENTER:
            SetAlignment(Alignment::CENTER);
            break;
        case TextAlign::RIGHT:
            SetAlignment(Alignment::CENTER_RIGHT);
            break;
        case TextAlign::START:
            SetAlignment(IsRightToLeft() ? Alignment::CENTER_RIGHT : Alignment::CENTER_LEFT);
            break;
        case TextAlign::END:
            SetAlignment(IsRightToLeft() ? Alignment::CENTER_LEFT : Alignment::CENTER_RIGHT);
            break;
        default:
            break;
    }
}

} // namespace OHOS::Ace::Framework
