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

#include "core/components_ng/pattern/texttimer/text_timer_model_static.h"

#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/texttimer/text_timer_pattern.h"

namespace OHOS::Ace::NG {
constexpr double MAX_COUNT_DOWN = 86400000.0;

void TextTimerModelStatic::SetIsCountDown(FrameNode* frameNode, const std::optional<bool>& isCountDown)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, IsCountDown, isCountDown.value_or(false), frameNode);
}

void TextTimerModelStatic::SetInputCount(FrameNode* frameNode, const std::optional<double>& count)
{
    if (count && count.value() > 0 && count.value() < MAX_COUNT_DOWN) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, InputCount, count.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, InputCount, frameNode);
    }
}

void TextTimerModelStatic::SetFontColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextColor, value.value(), frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, value.value(), frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextColor, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorFlag, frameNode);
    }
}

void TextTimerModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontSize, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontSize, frameNode);
    }
}

void TextTimerModelStatic::SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
{
    if (value.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, ItalicFontStyle, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, ItalicFontStyle, frameNode);
    }
}

void TextTimerModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<Ace::FontWeight>& value)
{
    if (value.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontWeight, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontWeight, frameNode);
    }
}

void TextTimerModelStatic::SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& value)
{
    if (value && value->size() > 0) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontFamily, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontFamily, frameNode);
    }
}

void TextTimerModelStatic::SetFormat(FrameNode* frameNode, const std::optional<std::string>& format)
{
    if (format) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, Format, format.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, Format, frameNode);
    }
}

void TextTimerModelStatic::SetTextShadow(FrameNode* frameNode, const std::optional<std::vector<Shadow>>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextShadow, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextShadow, frameNode);
    }
}
} // namespace OHOS::Ace::NG
