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

#include "core/components_ng/pattern/text/text_model_ng.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
FontWeight ConvertFontWeight(FontWeight fontWeight)
{
    FontWeight convertValue = fontWeight;
    switch (fontWeight) {
        case FontWeight::LIGHTER:
            convertValue = FontWeight::W100;
            break;
        case FontWeight::NORMAL:
        case FontWeight::REGULAR:
            convertValue = FontWeight::W400;
            break;
        case FontWeight::MEDIUM:
            convertValue = FontWeight::W500;
            break;
        case FontWeight::BOLD:
            convertValue = FontWeight::W700;
            break;
        case FontWeight::BOLDER:
            convertValue = FontWeight::W900;
            break;
        default:
            convertValue = fontWeight;
            break;
    }
    return convertValue;
}
} // namespace

void TextModelNG::Create(const std::string& content)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    stack->Push(frameNode);

    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, Content, content);
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextAlign, TextAlign::START);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::CENTER_LEFT);
}

void TextModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontSize, value);
}

void TextModelNG::SetTextColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextColor, value);
}

void TextModelNG::SetItalicFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, ItalicFontStyle, value);
}

void TextModelNG::SetFontWeight(Ace::FontWeight value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontWeight, ConvertFontWeight(value));
}

void TextModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontFamily, value);
}

void TextModelNG::SetTextAlign(Ace::TextAlign value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextAlign, value);
    if (value == Ace::TextAlign::START) {
        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::CENTER_LEFT);
    } else if (value == Ace::TextAlign::END) {
        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::CENTER_RIGHT);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::CENTER);
    }
}

void TextModelNG::SetTextOverflow(Ace::TextOverflow value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextOverflow, value);
}

void TextModelNG::SetMaxLines(uint32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, MaxLines, value);
}

void TextModelNG::SetLineHeight(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, LineHeight, value);
}

void TextModelNG::SetTextDecoration(Ace::TextDecoration value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecoration, value);
}

void TextModelNG::SetTextDecorationColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecorationColor, value);
}

void TextModelNG::SetBaselineOffset(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, BaselineOffset, value);
}

void TextModelNG::SetTextCase(Ace::TextCase value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextCase, value);
}

void TextModelNG::SetLetterSpacing(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, LetterSpacing, value);
}

void TextModelNG::SetAdaptMinFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, AdaptMinFontSize, value);
}

void TextModelNG::SetAdaptMaxFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, AdaptMaxFontSize, value);
}

void TextModelNG::SetOnClick(std::function<void(const BaseEventInfo* info)>&& click)
{
    LOGE("no support OnClick");
}

void TextModelNG::SetRemoteMessage(std::function<void()>&& event)
{
    LOGE("no support RemoteMessage");
}

void TextModelNG::SetCopyOption(CopyOptions copyOption)
{
    LOGE("no support CopyOption");
}

void TextModelNG::SetOnDragStartId(const OnDragFunc& onDragStartId)
{
    LOGE("no support SetOnDragStartId");
}

void TextModelNG::SetOnDragEnterId(const OnDropFunc& onDragEnterId)
{
    LOGE("no support SetOnDragEnterId");
}

void TextModelNG::SetOnDragMoveId(const OnDropFunc& onDragMoveId)
{
    LOGE("no support SetOnDragMoveId");
}

void TextModelNG::SetOnDragLeaveId(const OnDropFunc& onDragLeaveId)
{
    LOGE("no support SetOnDragLeaveId");
}

void TextModelNG::SetOnDropId(const OnDropFunc& onDropId)
{
    LOGE("no support SetOnDropId");
}

} // namespace OHOS::Ace::NG
