/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/span_model_static.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/text/text_emoji_processor.h"

#define ACE_UPDATE_NODE_SPAN_PROPERTY(name, value, frameNode)                                                    \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);                                               \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Update##name(value);                                                                           \
    } while (false)
#define ACE_RESET_NODE_SPAN_PROPERTY(name, frameNode)                                                            \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);                                               \
        CHECK_NULL_VOID(spanNode);                                                                               \
        if (spanNode->Has##name()) {                                                                             \
            spanNode->MarkTextDirty();                                                                           \
        }                                                                                                        \
        spanNode->Reset##name();                                                                                 \
    } while (false)

namespace OHOS::Ace::NG {

RefPtr<ContainerSpanNode> SpanModelStatic::CreateContainerSpanNode(int32_t nodeId)
{
    auto spanNode = ContainerSpanNode::GetOrCreateSpanNode(nodeId);
    CHECK_NULL_RETURN(spanNode, nullptr);
    return spanNode;
}

void SpanModelStatic::SetTextShadow(UINode* uiNode, const std::optional<std::vector<Shadow>>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(TextShadow, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(TextShadow, uiNode);
    }
}

void SpanModelStatic::InitSpan(UINode* uiNode, const std::optional<std::u16string>& content)
{
    if (content) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(Content, content.value(), uiNode);
    }
}

void SpanModelStatic::SetFontWeight(UINode* uiNode, const std::optional<FontWeight>& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(FontWeight, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(FontWeight, uiNode);
    }
}

void SpanModelStatic::SetTextCase(UINode* uiNode, const std::optional<TextCase>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(TextCase, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(TextCase, uiNode);
    }
}

void SpanModelStatic::SetItalicFontStyle(UINode* uiNode, const std::optional<Ace::FontStyle>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(ItalicFontStyle, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(ItalicFontStyle, uiNode);
    }
}

void SpanModelStatic::SetLineHeight(UINode* uiNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(LineHeight, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(LineHeight, uiNode);
    }
}

void SpanModelStatic::SetFontSize(UINode* uiNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(FontSize, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(FontSize, uiNode);
    }
}

void SpanModelStatic::SetFontFamily(UINode* uiNode, const std::optional<std::vector<std::string>>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(FontFamily, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(FontFamily, uiNode);
    }
}

void SpanModelStatic::SetTextDecoration(UINode* uiNode, const std::optional<TextDecoration>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(TextDecoration, {value.value()}, uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(TextDecoration, uiNode);
    }
}

void SpanModelStatic::SetTextDecorationStyle(UINode* uiNode, const std::optional<TextDecorationStyle>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(TextDecorationStyle, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(TextDecorationStyle, uiNode);
    }
}

void SpanModelStatic::SetTextDecorationColor(UINode* uiNode, const std::optional<Color>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(TextDecorationColor, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(TextDecorationColor, uiNode);
    }
}

void SpanModelStatic::SetTextColor(UINode* uiNode, const std::optional<Color>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(SpanTextColor, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(TextColor, uiNode);
    }
}

void SpanModelStatic::SetLetterSpacing(UINode* uiNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(LetterSpacing, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(LetterSpacing, uiNode);
    }
}

void SpanModelStatic::SetBaselineOffset(UINode* uiNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(BaselineOffset, value.value(), uiNode);
    } else {
        ACE_RESET_NODE_SPAN_PROPERTY(BaselineOffset, uiNode);
    }
}

} // namespace OHOS::Ace::NG
