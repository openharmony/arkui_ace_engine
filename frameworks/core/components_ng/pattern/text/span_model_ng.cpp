/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/span_model_ng.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

#define ACE_UPDATE_SPAN_PROPERTY(name, value, flag)                                                              \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode()); \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Update##name(value);                                                                           \
        spanNode->AddPropertyInfo(flag);                                                                         \
    } while (false)
#define ACE_UPDATE_NODE_SPAN_PROPERTY(name, value, flag, frameNode)                                              \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);                                               \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Update##name(value);                                                                           \
        spanNode->AddPropertyInfo(flag);                                                                         \
    } while (false)
#define ACE_RESET_NODE_SPAN_PROPERTY(name, flag, frameNode)                                                      \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);                                               \
        CHECK_NULL_VOID(spanNode);                                                                               \
        if (spanNode->Has##name()) {                                                                             \
            spanNode->MarkTextDirty();                                                                           \
        }                                                                                                        \
        spanNode->Reset##name();                                                                                 \
        spanNode->ResetPropertyInfo(flag);                                                                       \
    } while (false)
namespace OHOS::Ace::NG {

void SpanModelNG::Create(const std::string& content)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(nodeId);
    stack->Push(spanNode);

    ACE_UPDATE_SPAN_PROPERTY(Content, content, PropertyInfo::NONE);
}

RefPtr<SpanNode> SpanModelNG::CreateSpanNode(int32_t nodeId, const std::string& content)
{
    auto spanNode = SpanNode::CreateSpanNode(nodeId);
    CHECK_NULL_RETURN(spanNode, nullptr);
    spanNode->UpdateContent(content);
    spanNode->AddPropertyInfo(PropertyInfo::NONE);
    return spanNode;
}

void SpanModelNG::SetFont(const Font& value)
{
    if (value.fontSize.has_value()) {
        SetFontSize(value.fontSize.value());
    }
    if (value.fontWeight.has_value()) {
        SetFontWeight(value.fontWeight.value());
    }
    if (!value.fontFamilies.empty()) {
        SetFontFamily(value.fontFamilies);
    }
    if (value.fontStyle.has_value()) {
        SetItalicFontStyle(value.fontStyle.value());
    }
}

void SpanModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontSize, value, PropertyInfo::FONTSIZE);
}

void SpanModelNG::SetTextColor(const Color& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateSpanTextColor(value);
    spanNode->AddPropertyInfo(PropertyInfo::FONTCOLOR);
}

void SpanModelNG::SetItalicFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_SPAN_PROPERTY(ItalicFontStyle, value, PropertyInfo::FONTSTYLE);
}

void SpanModelNG::SetFontWeight(Ace::FontWeight value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontWeight, value, PropertyInfo::FONTWEIGHT);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateUserFontWeight(true);
}

void SpanModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontFamily, value, PropertyInfo::FONTFAMILY);
}

void SpanModelNG::SetTextDecoration(Ace::TextDecoration value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecoration, value, PropertyInfo::TEXTDECORATION);
}

void SpanModelNG::SetTextDecorationStyle(Ace::TextDecorationStyle value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecorationStyle, value, PropertyInfo::NONE);
}

void SpanModelNG::SetTextDecorationColor(const Color& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecorationColor, value, PropertyInfo::NONE);
}

void SpanModelNG::SetTextCase(Ace::TextCase value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextCase, value, PropertyInfo::TEXTCASE);
}

void SpanModelNG::SetTextShadow(const std::vector<Shadow>& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextShadow, value, PropertyInfo::TEXTSHADOW);
}

void SpanModelNG::SetTextShadow(UINode* uiNode, const std::vector<Shadow>& value)
{
    ACE_UPDATE_NODE_SPAN_PROPERTY(TextShadow, value, PropertyInfo::TEXTSHADOW, uiNode);
}

void SpanModelNG::ResetTextShadow(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextShadow, PropertyInfo::TEXTSHADOW, uiNode);
}

void SpanModelNG::SetLetterSpacing(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(LetterSpacing, value, PropertyInfo::LETTERSPACE);
}

void SpanModelNG::SetBaselineOffset(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(BaselineOffset, value, PropertyInfo::BASELINE_OFFSET);
}

void SpanModelNG::SetLineHeight(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(LineHeight, value, PropertyInfo::LINEHEIGHT);
}

void SpanModelNG::SetOnClick(std::function<void(BaseEventInfo* info)>&& click)
{
    auto clickFunc = [func = std::move(click)](GestureEvent& info) { func(&info); };
    ACE_UPDATE_SPAN_PROPERTY(OnClickEvent, std::move(clickFunc), PropertyInfo::NONE);
}

void SpanModelNG::SetOnClick(UINode* uiNode, GestureEventFunc&& click)
{
    ACE_UPDATE_NODE_SPAN_PROPERTY(OnClickEvent, std::move(click), PropertyInfo::NONE, uiNode);
}

void SpanModelNG::ClearOnClick()
{
    ACE_UPDATE_SPAN_PROPERTY(OnClickEvent, nullptr, PropertyInfo::NONE);
}

void SpanModelNG::ClearOnClick(UINode* uiNode)
{
    ACE_UPDATE_NODE_SPAN_PROPERTY(OnClickEvent, nullptr, PropertyInfo::NONE, uiNode);
}

void SpanModelNG::SetAccessibilityText(const std::string& text)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityText(text);
}

void SpanModelNG::SetAccessibilityDescription(const std::string& description)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityDescription(description);
}

void SpanModelNG::SetAccessibilityImportance(const std::string& importance)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityLevel(importance);
}

void SpanModelNG::InitSpan(UINode* uiNode, const std::string& content)
{
    ACE_UPDATE_NODE_SPAN_PROPERTY(Content, content, PropertyInfo::NONE, uiNode);
}

void SpanModelNG::SetFontWeight(UINode* uiNode, FontWeight value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateFontWeight(value);
    spanNode->AddPropertyInfo(PropertyInfo::FONTWEIGHT);
    spanNode->UpdateUserFontWeight(true);
}

void SpanModelNG::ResetFontWeight(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(FontWeight, PropertyInfo::FONTWEIGHT, uiNode);
}

void SpanModelNG::SetTextCase(UINode* uiNode, TextCase value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextCase(value);
    spanNode->AddPropertyInfo(PropertyInfo::TEXTCASE);
}

void SpanModelNG::ResetTextCase(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextCase, PropertyInfo::TEXTCASE, uiNode);
}

void SpanModelNG::SetItalicFontStyle(UINode* uiNode, Ace::FontStyle value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateItalicFontStyle(value);
    spanNode->AddPropertyInfo(PropertyInfo::FONTSTYLE);
}

void SpanModelNG::ResetItalicFontStyle(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(ItalicFontStyle, PropertyInfo::FONTSTYLE, uiNode);
}

void SpanModelNG::SetLineHeight(UINode* uiNode, const Dimension& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateLineHeight(value);
    spanNode->AddPropertyInfo(PropertyInfo::LINEHEIGHT);
}

void SpanModelNG::ResetLineHeight(UINode* uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(LineHeight, PropertyInfo::LINEHEIGHT, uiNode);
}

void SpanModelNG::SetFontSize(UINode* uiNode, const Dimension& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateFontSize(value);
    spanNode->AddPropertyInfo(PropertyInfo::FONTSIZE);
}

void SpanModelNG::ResetFontSize(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(FontSize, PropertyInfo::FONTSIZE, uiNode);
}

void SpanModelNG::SetFontFamily(UINode* uiNode, const std::vector<std::string>& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateFontFamily(value);
    spanNode->AddPropertyInfo(PropertyInfo::FONTFAMILY);
}

void SpanModelNG::ResetFontFamily(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(FontFamily, PropertyInfo::FONTFAMILY, uiNode);
}

void SpanModelNG::SetTextDecoration(UINode* uiNode, TextDecoration value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextDecoration(value);
    spanNode->AddPropertyInfo(PropertyInfo::TEXTDECORATION);
}

void SpanModelNG::ResetTextDecoration(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextDecoration, PropertyInfo::TEXTDECORATION, uiNode);
}

void SpanModelNG::SetTextDecorationStyle(UINode* uiNode, TextDecorationStyle value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextDecorationStyle(value);
    spanNode->AddPropertyInfo(PropertyInfo::NONE);
}

void SpanModelNG::ResetTextDecorationStyle(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextDecorationStyle, PropertyInfo::NONE, uiNode);
}

void SpanModelNG::SetTextDecorationColor(UINode* uiNode, const Color& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextDecorationColor(value);
    spanNode->AddPropertyInfo(PropertyInfo::NONE);
}

void SpanModelNG::ResetTextDecorationColor(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextDecorationColor, PropertyInfo::NONE, uiNode);
}

void SpanModelNG::SetTextColor(UINode* uiNode, const Color& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateSpanTextColor(value);
    spanNode->AddPropertyInfo(PropertyInfo::FONTCOLOR);
}

void SpanModelNG::ResetTextColor(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextColor, PropertyInfo::FONTCOLOR, uiNode);
}

void SpanModelNG::SetLetterSpacing(UINode* uiNode, const Dimension& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateLetterSpacing(value);
    spanNode->AddPropertyInfo(PropertyInfo::LETTERSPACE);
}

void SpanModelNG::ResetLetterSpacing(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(LetterSpacing, PropertyInfo::LETTERSPACE, uiNode);
}

void SpanModelNG::SetBaselineOffset(UINode* uiNode, const Dimension& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateBaselineOffset(value);
    spanNode->AddPropertyInfo(PropertyInfo::BASELINE_OFFSET);
}

void SpanModelNG::SetFont(UINode* uiNode, const Font& value)
{
    if (value.fontSize.has_value()) {
        SetFontSize(uiNode, value.fontSize.value());
    }
    if (value.fontWeight.has_value()) {
        SetFontWeight(uiNode, value.fontWeight.value());
    }
    if (!value.fontFamilies.empty()) {
        SetFontFamily(uiNode, value.fontFamilies);
    }
    if (value.fontStyle.has_value()) {
        SetItalicFontStyle(uiNode, value.fontStyle.value());
    }
}

void SpanModelNG::ResetFont(UINode *uiNode)
{
    ResetFontSize(uiNode);
    ResetFontWeight(uiNode);
    ResetFontFamily(uiNode);
    ResetItalicFontStyle(uiNode);
}

void SpanModelNG::CreateContainSpan()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = ContainerSpanNode::GetOrCreateSpanNode(nodeId);
    stack->Push(spanNode);
}

void SpanModelNG::SetTextBackgroundStyle(const TextBackgroundStyle& style)
{
    auto baseSpan = AceType::DynamicCast<BaseSpan>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(baseSpan);
    baseSpan->SetTextBackgroundStyle(style);
}

void SpanModelNG::SetTextBackgroundStyle(UINode* uiNode, const TextBackgroundStyle& style)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->SetTextBackgroundStyle(style);
}

void SpanModelNG::SetTextBackgroundStyleByBaseSpan(UINode* uiNode, const TextBackgroundStyle& style)
{
    auto spanNode = AceType::DynamicCast<BaseSpan>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->SetTextBackgroundStyle(style);
}

std::string SpanModelNG::GetContent(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, "");
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_RETURN(spanItem, "");
    return spanItem->GetSpanContent();
}

Ace::TextDecoration SpanModelNG::GetTextDecoration(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, TextDecoration::NONE);
    return spanNode->GetTextDecoration().value_or(TextDecoration::NONE);
}

Color SpanModelNG::GetTextDecorationColor(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, Color::BLACK);
    return spanNode->GetTextDecorationColor().value_or(Color::BLACK);
}

Ace::TextDecorationStyle SpanModelNG::GetTextDecorationStyle(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, TextDecorationStyle::SOLID);
    return spanNode->GetTextDecorationStyle().value_or(TextDecorationStyle::SOLID);
}

TextStyle SpanModelNG::GetDefaultTextStyle()
{
    TextStyle textStyle;
    auto pipelineContext = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipelineContext, textStyle);
    auto textTheme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(textTheme, textStyle);
    return textTheme->GetTextStyle();
}

Color SpanModelNG::GetFontColor(UINode* uiNode)
{
    auto defaultColor = GetDefaultTextStyle().GetTextColor();
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, defaultColor);
    return spanNode->GetTextColor().value_or(defaultColor);
}

Dimension SpanModelNG::GetFontSize(UINode* uiNode)
{
    const Dimension& defaultFontSize = GetDefaultTextStyle().GetFontSize();
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, defaultFontSize);
    return spanNode->GetFontSize().value_or(defaultFontSize);
}

Ace::FontStyle SpanModelNG::GetFontStyle(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, Ace::FontStyle::NORMAL);
    return spanNode->GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL);
}

FontWeight SpanModelNG::GetFontWeight(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, FontWeight::NORMAL);
    return spanNode->GetFontWeight().value_or(FontWeight::NORMAL);
}

Dimension SpanModelNG::GetTextLineHeight(UINode* uiNode)
{
    Dimension defaultLineHeight(0);
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, Dimension(0));
    return spanNode->GetLineHeight().value_or(defaultLineHeight);
}

Ace::TextCase SpanModelNG::GetTextCase(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, TextCase::NORMAL);
    return spanNode->GetTextCase().value_or(TextCase::NORMAL);
}

Dimension SpanModelNG::GetLetterSpacing(UINode* uiNode)
{
    Dimension defaultLetterSpacing(0);
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, defaultLetterSpacing);
    return spanNode->GetLetterSpacing().value_or(defaultLetterSpacing);
}

Dimension SpanModelNG::GetBaselineOffset(UINode* uiNode)
{
    Dimension defaultBaselineOffset(0);
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, defaultBaselineOffset);
    return spanNode->GetBaselineOffset().value_or(defaultBaselineOffset);
}

TextBackgroundStyle SpanModelNG::GetSpanTextBackgroundStyle(UINode* uiNode)
{
    TextBackgroundStyle backgroundStyle;
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, backgroundStyle);
    return spanNode->GetTextBackgroundStyle().value_or(backgroundStyle);
}

std::vector<Shadow> SpanModelNG::GetTextShadow(UINode* uiNode)
{
    std::vector<Shadow> defaultShadow;
    CHECK_NULL_RETURN(uiNode, defaultShadow);
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, defaultShadow);
    return spanNode->GetTextShadow().value_or(defaultShadow);
}

void SpanModelNG::SetAccessibilityText(UINode* uiNode, const std::string& text)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityText(text);
}

void SpanModelNG::SetAccessibilityDescription(UINode* uiNode, const std::string& description)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityDescription(description);
}

void SpanModelNG::SetAccessibilityImportance(UINode* uiNode, const std::string& importance)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityLevel(importance);
}

std::vector<std::string> SpanModelNG::GetSpanFontFamily(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    std::vector<std::string> value;
    CHECK_NULL_RETURN(spanNode, value);
    return spanNode->GetFontFamily().value_or(value);
}
} // namespace OHOS::Ace::NG
