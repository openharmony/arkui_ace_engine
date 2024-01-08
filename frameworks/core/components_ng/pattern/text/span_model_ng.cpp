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
    ACE_UPDATE_SPAN_PROPERTY(TextColor, value, PropertyInfo::FONTCOLOR);
}

void SpanModelNG::SetItalicFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_SPAN_PROPERTY(ItalicFontStyle, value, PropertyInfo::FONTSTYLE);
}

void SpanModelNG::SetFontWeight(Ace::FontWeight value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontWeight, value, PropertyInfo::FONTWEIGHT);
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

void SpanModelNG::SetLetterSpacing(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(LetterSpacing, value, PropertyInfo::LETTERSPACE);
}

void SpanModelNG::SetLineHeight(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(LineHeight, value, PropertyInfo::LINEHEIGHT);
}

void SpanModelNG::SetOnClick(std::function<void(const BaseEventInfo* info)>&& click)
{
    auto clickFunc = [func = std::move(click)](GestureEvent& info) { func(&info); };
    ACE_UPDATE_SPAN_PROPERTY(OnClickEvent, std::move(clickFunc), PropertyInfo::NONE);
}

void SpanModelNG::ClearOnClick()
{
    ACE_UPDATE_SPAN_PROPERTY(OnClickEvent, nullptr, PropertyInfo::NONE);
}

void SpanModelNG::SetFontWeight(FrameNode* frameNode, FontWeight value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateFontWeight(value);
    spanNode->AddPropertyInfo(PropertyInfo::FONTWEIGHT);
}

void SpanModelNG::SetTextCase(FrameNode* frameNode, TextCase value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextCase(value);
    spanNode->AddPropertyInfo(PropertyInfo::TEXTCASE);
}

void SpanModelNG::SetItalicFontStyle(FrameNode* frameNode, Ace::FontStyle value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateItalicFontStyle(value);
    spanNode->AddPropertyInfo(PropertyInfo::FONTSTYLE);
}

void SpanModelNG::SetLineHeight(FrameNode* frameNode, const Dimension& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateLineHeight(value);
    spanNode->AddPropertyInfo(PropertyInfo::LINEHEIGHT);
}

void SpanModelNG::SetFontSize(FrameNode* frameNode, const Dimension& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateFontSize(value);
    spanNode->AddPropertyInfo(PropertyInfo::FONTSIZE);
}

void SpanModelNG::SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateFontFamily(value);
    spanNode->AddPropertyInfo(PropertyInfo::FONTFAMILY);
}

void SpanModelNG::SetTextDecoration(FrameNode* frameNode, TextDecoration value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextDecoration(value);
    spanNode->AddPropertyInfo(PropertyInfo::TEXTDECORATION);
}

void SpanModelNG::SetTextDecorationStyle(FrameNode* frameNode, TextDecorationStyle value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextDecorationStyle(value);
    spanNode->AddPropertyInfo(PropertyInfo::NONE);
}

void SpanModelNG::SetTextDecorationColor(FrameNode* frameNode, const Color& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextDecorationColor(value);
    spanNode->AddPropertyInfo(PropertyInfo::NONE);
}

void SpanModelNG::SetTextColor(FrameNode* frameNode, const Color& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextColor(value);
    spanNode->AddPropertyInfo(PropertyInfo::FONTCOLOR);
}

void SpanModelNG::SetLetterSpacing(FrameNode* frameNode, const Dimension& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateLetterSpacing(value);
    spanNode->AddPropertyInfo(PropertyInfo::LETTERSPACE);
}

void SpanModelNG::SetFont(FrameNode* frameNode, const Font& value)
{
    if (value.fontSize.has_value()) {
        SetFontSize(frameNode, value.fontSize.value());
    }
    if (value.fontWeight.has_value()) {
        SetFontWeight(frameNode, value.fontWeight.value());
    }
    if (!value.fontFamilies.empty()) {
        SetFontFamily(frameNode, value.fontFamilies);
    }
    if (value.fontStyle.has_value()) {
        SetItalicFontStyle(frameNode, value.fontStyle.value());
    }
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
} // namespace OHOS::Ace::NG
