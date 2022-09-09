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

#include "core/components_ng/pattern/text/text_view.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void TextView::Create(const std::string& content)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    stack->Push(frameNode);

    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, Content, content);
}

void TextView::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontSize, value);
}

void TextView::SetTextColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextColor, value);
}

void TextView::SetItalicFontStyle(const NG::ItalicFontStyle& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, ItalicFontStyle, value);
}

void TextView::SetFontWeight(const Ace::FontWeight& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontWeight, value);
}

void TextView::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontFamily, value);
}

void TextView::SetTextAlign(const Ace::TextAlign& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextAlign, value);
}

void TextView::SetTextOverflow(const Ace::TextOverflow& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextOverflow, value);
}

void TextView::SetMaxLines(const uint32_t& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, MaxLines, value);
}

void TextView::SetLineHeight(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, LineHeight, value);
}

void TextView::SetTextDecoration(const Ace::TextDecoration& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecoration, value);
}

void TextView::SetTextDecorationColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecorationColor, value);
}

void TextView::SetBaselineOffset(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, BaselineOffset, value);
}

void TextView::SetTextCase(const Ace::TextCase& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextCase, value);
}

void TextView::SetLetterSpacing(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, LetterSpacing, value);
}

void TextView::SetAdaptMinFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, AdaptMinFontSize, value);
}

void TextView::SetAdaptMaxFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, AdaptMaxFontSize, value);
}

} // namespace OHOS::Ace::NG
