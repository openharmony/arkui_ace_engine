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

#include "core/common/ace_application_info.h"
#include "core/components/text/text_theme.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr double DEFAULT_LETTER_SPACING = 0; // unit is px
constexpr double DEFAULT_LINE_HEIGHT = 0;    // unit is px
const char DEFAULT_FONT_FAMILY[] = "sans-serif";

} // namespace

DOMText::DOMText(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    textChild_ = AceType::MakeRefPtr<TextComponent>("");
    if (IsRightToLeft()) {
        textChild_->SetTextDirection(TextDirection::RTL);
    }
}

void DOMText::ResetInitializedStyle()
{
    InitializeStyle();
}

bool DOMText::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (attr.first == DOM_VALUE) {
        textChild_->SetData(attr.second);
        return true;
    }
    LOGD("Use default text attribute");
    return false;
}

bool DOMText::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    // static linear map must be sorted by key.
    static const LinearMapNode<void (*)(const std::string&, const DOMText&, TextComponent&, TextStyle&)>
        textStyleOperators[] = {
            { DOM_TEXT_ALLOW_SCALE, [](const std::string& val, const DOMText& node, TextComponent& text,
                                    TextStyle& textStyle) { textStyle.SetAllowScale(StringToBool(val)); } },
            { DOM_TEXT_COLOR, [](const std::string& val, const DOMText& node, TextComponent& text,
                              TextStyle& textStyle) { textStyle.SetTextColor(node.ParseColor(val)); } },
            { DOM_TEXT_FONT_FAMILY, [](const std::string& val, const DOMText& node, TextComponent& text,
                                    TextStyle& textStyle) { textStyle.SetFontFamilies(node.ParseFontFamilies(val)); } },
            { DOM_TEXT_FONT_SIZE, [](const std::string& val, const DOMText& node, TextComponent& text,
                                  TextStyle& textStyle) { textStyle.SetFontSize(node.ParseDimension(val)); } },
            { DOM_TEXT_FONT_SIZE_STEP,
                [](const std::string& val, const DOMText& node, TextComponent& text, TextStyle& textStyle) {
                    textStyle.SetAdaptFontSizeStep(node.ParseDimension(val));
                } },
            { DOM_TEXT_FONT_STYLE, [](const std::string& val, const DOMText& node, TextComponent& text,
                                   TextStyle& textStyle) { textStyle.SetFontStyle(ConvertStrToFontStyle(val)); } },
            { DOM_TEXT_FONT_WEIGHT, [](const std::string& val, const DOMText& node, TextComponent& text,
                                    TextStyle& textStyle) { textStyle.SetFontWeight(ConvertStrToFontWeight(val)); } },
            { DOM_TEXT_LETTER_SPACING, [](const std::string& val, const DOMText& node, TextComponent& text,
                                       TextStyle& textStyle) { textStyle.SetLetterSpacing(StringToDouble(val)); } },
            { DOM_TEXT_LINE_HEIGHT, [](const std::string& val, const DOMText& node, TextComponent& text,
                                    TextStyle& textStyle) { textStyle.SetLineHeight(node.ParseLineHeight(val)); } },
            { DOM_TEXT_LINES, [](const std::string& val, const DOMText& node, TextComponent& text,
                              TextStyle& textStyle) { textStyle.SetMaxLines(StringUtils::StringToInt(val)); } },
            { DOM_TEXT_MAX_FONT_SIZE,
                [](const std::string& val, const DOMText& node, TextComponent& text, TextStyle& textStyle) {
                    textStyle.SetAdaptMaxFontSize(node.ParseDimension(val));
                } },
            { DOM_TEXT_MAX_LINES, [](const std::string& val, const DOMText& node, TextComponent& text,
                                  TextStyle& textStyle) { textStyle.SetMaxLines(StringUtils::StringToInt(val)); } },
            { DOM_TEXT_MIN_FONT_SIZE,
                [](const std::string& val, const DOMText& node, TextComponent& text, TextStyle& textStyle) {
                    textStyle.SetAdaptMinFontSize(node.ParseDimension(val));
                } },
            { DOM_TEXT_PREFER_FONT_SIZES,
                [](const std::string& val, const DOMText& node, TextComponent& text, TextStyle& textStyle) {
                    textStyle.SetPreferFontSizes(node.ParsePreferFontSizes(val));
                } },
            { DOM_TEXT_ALIGN, [](const std::string& val, const DOMText& node, TextComponent& text,
                              TextStyle& textStyle) { textStyle.SetTextAlign(ConvertStrToTextAlign(val)); } },
            { DOM_TEXT_DECORATION,
                [](const std::string& val, const DOMText& node, TextComponent& text, TextStyle& textStyle) {
                    textStyle.SetTextDecoration(ConvertStrToTextDecoration(val));
                } },
            { DOM_TEXT_OVERFLOW,
                [](const std::string& val, const DOMText& node, TextComponent& text,
                    TextStyle& textStyle) { textStyle.SetTextOverflow(ConvertStrToTextOverflow(val));
                } },
            { DOM_TEXT_WORD_BREAK,
                [](const std::string& val, const DOMText& node, TextComponent& text,
                    TextStyle& textStyle) { textStyle.SetWordBreak(ConvertStrToWordBreak(val));
                } },
        };
    auto operatorIter = BinarySearchFindIndex(textStyleOperators, ArraySize(textStyleOperators), style.first.c_str());
    if (operatorIter != -1) {
        textStyleOperators[operatorIter].value(style.second, *this, *textChild_, textStyle_);
        if (style.first == DOM_TEXT_COLOR) {
            hasSetTextColor_ = true;
        } else if (style.first == DOM_TEXT_FONT_SIZE) {
            hasSetTextFontSize_ = true;
        } else {
            LOGD("DOMText has no font-size and color");
        }
        return true;
    }
    return false;
}

void DOMText::CheckAndSetSpanStyle(const RefPtr<DOMSpan>& dmoSpan, TextStyle& spanStyle)
{
    if (!dmoSpan->HasSetFontSize()) {
        LOGD("Set Text Font Size to Span");
        spanStyle.SetFontSize(textStyle_.GetFontSize());
    }
    if (!dmoSpan->HasSetFontStyle()) {
        LOGD("Set Text Font Style to Span");
        spanStyle.SetFontStyle(textStyle_.GetFontStyle());
    }
    if (!dmoSpan->HasSetFontColor()) {
        LOGD("Set Text Font Color to Span");
        spanStyle.SetTextColor(textStyle_.GetTextColor());
    }
    if (!dmoSpan->HasSetFontWeight()) {
        LOGD("Set Text Font Weight to Span");
        spanStyle.SetFontWeight(textStyle_.GetFontWeight());
    }
    if (!dmoSpan->HasSetTextDecoration()) {
        LOGD("Set Text Decoration to Span");
        spanStyle.SetTextDecoration(textStyle_.GetTextDecoration());
    }
    if (!dmoSpan->HasSetFontFamily()) {
        LOGD("Set Text Font Family to Span");
        spanStyle.SetFontFamilies(textStyle_.GetFontFamilies());
    }
    if (!dmoSpan->HasSetAllowScale()) {
        LOGD("Set Allow Scale to Span");
        spanStyle.SetAllowScale(textStyle_.IsAllowScale());
    }
    spanStyle.SetLetterSpacing(textStyle_.GetLetterSpacing());
    spanStyle.SetLineHeight(textStyle_.GetLineHeight(), textStyle_.HasHeightOverride());
}

void DOMText::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    ACE_DCHECK(child);
    auto spanComponent = AceType::DynamicCast<TextSpanComponent>(child->GetSpecializedComponent());
    if (!spanComponent) {
        LOGW("text only support span child");
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
    bool isCard = AceApplicationInfo::GetInstance().GetIsCardType();
    if (isCard) {
        textStyle_.SetAllowScale(false);
        if (textStyle_.GetFontSize().Unit() == DimensionUnit::FP) {
            textStyle_.SetAllowScale(true);
        }
    }
    textChild_->SetTextStyle(textStyle_);
    // Text focus color is same as text style color.
    textChild_->SetFocusColor(textStyle_.GetTextColor());
    textChild_->SetMaxWidthLayout(boxComponent_->GetWidthDimension().IsValid());

    // set box align
    if (!textChild_->GetMaxWidthLayout()) {
        SetBoxAlignForText();
    }
}

void DOMText::SetBoxAlignForText()
{
    switch (textStyle_.GetTextAlign()) {
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

void DOMText::InitializeStyle()
{
    RefPtr<TextTheme> theme = GetTheme<TextTheme>();
    if (theme) {
        textStyle_ = theme->GetTextStyle();
        std::vector<std::string> defaultFontFamilis;
        defaultFontFamilis.emplace_back(DEFAULT_FONT_FAMILY);
        textStyle_.SetFontFamilies(defaultFontFamilis);
        textStyle_.SetLetterSpacing(DEFAULT_LETTER_SPACING);
        textStyle_.SetLineHeight(Dimension(DEFAULT_LINE_HEIGHT, DimensionUnit::PX), false);
    }
}

} // namespace OHOS::Ace::Framework
