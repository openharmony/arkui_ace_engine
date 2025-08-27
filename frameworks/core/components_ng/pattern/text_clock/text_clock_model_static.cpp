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

#include "core/components_ng/pattern/text_clock/text_clock_model_static.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"

namespace OHOS::Ace::NG {
void TextClockModelStatic::SetFormat(FrameNode* frameNode, const std::optional<std::string>& format)
{
    if (!format.has_value() || format.value().empty()) {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, Format, frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, Format, format.value(), frameNode);
    }
}

void TextClockModelStatic::SetHoursWest(FrameNode* frameNode, const std::optional<float>& hoursWest)
{
    if (hoursWest.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, HoursWest, hoursWest.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, HoursWest, frameNode);
    }
}

void TextClockModelStatic::SetFontColor(FrameNode* frameNode,  const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, TextColor, color.value(), frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, color.value(), frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, TextColor, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorFlag, frameNode);
    }
}

void TextClockModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& size)
{
    if (size.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontSize, size.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontSize, frameNode);
    }
}

void TextClockModelStatic::SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
{
    if (value.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, ItalicFontStyle, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, ItalicFontStyle, frameNode);
    }
}

void TextClockModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<Ace::FontWeight>& value)
{
    if (value.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontWeight, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontWeight, frameNode);
    }
}

void TextClockModelStatic::SetDateTimeOptions(FrameNode* frameNode, const std::optional<ZeroPrefixType>& hourType)
{
    CHECK_NULL_VOID(frameNode);
    if (hourType.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, PrefixHour, hourType.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, PrefixHour, frameNode);
    }
}
} // namespace OHOS::Ace::NG
