/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "base/utils/utf_helper.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model_static.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void TextModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontSize, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontSize, frameNode);
    }
}

void TextModelStatic::SetTextColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        TextModelNG::SetTextColor(frameNode, color.value());
        return;
    }
    TextModelNG::ResetTextColor(frameNode);
}

void TextModelStatic::SetItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
{
    if (value.has_value()) {
        TextModelNG::SetItalicFontStyle(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, ItalicFontStyle, frameNode);
    }
}

void TextModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<Ace::FontWeight>& value)
{
    if (value.has_value()) {
        TextModelNG::SetFontWeight(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontWeight, frameNode);
    }
}

void TextModelStatic::SetVariableFontWeight(FrameNode* frameNode, const std::optional<int32_t>& value)
{
    TextModelNG::SetVariableFontWeight(frameNode, value.value_or(DEFAULT_VARIABLE_FONT_WEIGHT));
}

void TextModelStatic::SetEnableVariableFontWeight(FrameNode* frameNode, const std::optional<bool>& value)
{
    if (value.has_value()) {
        TextModelNG::SetEnableVariableFontWeight(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, EnableVariableFontWeight, frameNode);
    }
}

void TextModelStatic::SetTextAlign(FrameNode* frameNode, const std::optional<Ace::TextAlign>& value)
{
    if (value.has_value()) {
        TextModelNG::SetTextAlign(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextAlign, frameNode);
    }
}

void TextModelStatic::SetTextOverflow(FrameNode* frameNode, const std::optional<Ace::TextOverflow>& value)
{
    if (value.has_value()) {
        TextModelNG::SetTextOverflow(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextOverflow, frameNode);
    }
}

void TextModelStatic::SetLineHeight(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value.has_value()) {
        TextModelNG::SetLineHeight(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, LineHeight, frameNode);
    }
}

void TextModelStatic::SetLineSpacing(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, LineSpacing, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, LineSpacing, frameNode);
    }
}

void TextModelStatic::SetTextDecoration(FrameNode* frameNode, const std::optional<TextDecoration>& value)
{
    if (value.has_value()) {
        TextModelNG::SetTextDecoration(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecoration, frameNode);
    }
}

void TextModelStatic::SetTextDecorationColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value.has_value()) {
        TextModelNG::SetTextDecorationColor(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecorationColor, frameNode);
    }
}

void TextModelStatic::SetTextDecorationStyle(FrameNode* frameNode, const std::optional<TextDecorationStyle>& value)
{
    if (value.has_value()) {
        TextModelNG::SetTextDecorationStyle(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecorationStyle, frameNode);
    }
}

void TextModelStatic::SetTextCase(FrameNode* frameNode, const std::optional<Ace::TextCase>& value)
{
    if (value.has_value()) {
        TextModelNG::SetTextCase(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextCase, frameNode);
    }
}

void TextModelStatic::SetMaxLines(FrameNode* frameNode, const std::optional<uint32_t>& value)
{
    if (value.has_value()) {
        TextModelNG::SetMaxLines(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, MaxLines, frameNode);
    }
}

void TextModelStatic::SetAdaptMinFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value.has_value()) {
        TextModelNG::SetAdaptMinFontSize(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, AdaptMinFontSize, frameNode);
    }
}

void TextModelStatic::SetAdaptMaxFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value.has_value()) {
        TextModelNG::SetAdaptMaxFontSize(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, AdaptMaxFontSize, frameNode);
    }
}

void TextModelStatic::SetMinFontScale(FrameNode* frameNode, const std::optional<float>& value)
{
    if (value.has_value()) {
        TextModelNG::SetMinFontScale(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, MinFontScale, frameNode);
    }
}

void TextModelStatic::SetMaxFontScale(FrameNode* frameNode, const std::optional<float>& value)
{
    if (value.has_value()) {
        TextModelNG::SetMaxFontScale(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, MaxFontScale, frameNode);
    }
}

void TextModelStatic::SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& value)
{
    if (value.has_value()) {
        TextModelNG::SetFontFamily(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontFamily, frameNode);
    }
}

void TextModelStatic::SetCopyOption(FrameNode* frameNode, const std::optional<CopyOptions>& copyOption)
{
    if (copyOption.has_value()) {
        TextModelNG::SetCopyOption(frameNode, copyOption.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, CopyOption, frameNode);
    }
}

void TextModelStatic::SetTextShadow(FrameNode* frameNode, const std::optional<std::vector<Shadow>>& value)
{
    if (value.has_value()) {
        TextModelNG::SetTextShadow(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextShadow, frameNode);
    }
}

void TextModelStatic::SetHeightAdaptivePolicy(FrameNode* frameNode,
    const std::optional<TextHeightAdaptivePolicy>& value)
{
    if (value.has_value()) {
        TextModelNG::SetHeightAdaptivePolicy(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, HeightAdaptivePolicy, frameNode);
    }
}

void TextModelStatic::SetTextIndent(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value.has_value()) {
        TextModelNG::SetTextIndent(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextIndent, frameNode);
    }
}

void TextModelStatic::SetBaselineOffset(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value.has_value()) {
        TextModelNG::SetBaselineOffset(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, BaselineOffset, frameNode);
    }
}

void TextModelStatic::SetFont(FrameNode* frameNode, const std::optional<Font>& value)
{
    if (!value.has_value()) {
        SetFontSize(frameNode, std::nullopt);
        SetFontWeight(frameNode, std::nullopt);
        SetFontFamily(frameNode, std::nullopt);
        SetItalicFontStyle(frameNode, std::nullopt);
        SetEnableVariableFontWeight(frameNode, std::nullopt);
        return;
    }
    SetFontSize(frameNode, value.value().fontSize);
    SetFontWeight(frameNode, value.value().fontWeight);
    SetFontFamily(frameNode, value.value().fontFamilies);
    SetItalicFontStyle(frameNode, value.value().fontStyle);
    SetEnableVariableFontWeight(frameNode, value.value().enableVariableFontWeight);
}

void TextModelStatic::SetLetterSpacing(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value.has_value()) {
        TextModelNG::SetLetterSpacing(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, LetterSpacing, frameNode);
    }
}

void TextModelStatic::SetWordBreak(FrameNode* frameNode, const std::optional<Ace::WordBreak>& value)
{
    if (value.has_value()) {
        TextModelNG::SetWordBreak(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, WordBreak, frameNode);
    }
}

void TextModelStatic::SetLineBreakStrategy(FrameNode* frameNode, const std::optional<Ace::LineBreakStrategy>& value)
{
    if (value.has_value()) {
        TextModelNG::SetLineBreakStrategy(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, LineBreakStrategy, frameNode);
    }
}

void TextModelStatic::SetTextSelectableMode(FrameNode* frameNode, const std::optional<Ace::TextSelectableMode>& value)
{
    TextModelNG::SetTextSelectableMode(frameNode, value.value_or(TextSelectableMode::SELECTABLE_UNFOCUSABLE));
}

void TextModelStatic::SetEllipsisMode(FrameNode* frameNode, const std::optional<Ace::EllipsisMode>& value)
{
    if (value.has_value()) {
        TextModelNG::SetEllipsisMode(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, EllipsisMode, frameNode);
    }
}

void TextModelStatic::SetCaretColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value.has_value()) {
        TextModelNG::SetCaretColor(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, CursorColor, frameNode);
    }
}

void TextModelStatic::SetSelectedBackgroundColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value.has_value()) {
        TextModelNG::SetSelectedBackgroundColor(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, SelectedBackgroundColor, frameNode);
    }
}

void TextModelStatic::SetSelectionMenuOptions(FrameNode* frameNode,
    const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick)
{
    CHECK_NULL_VOID(frameNode);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick), nullptr);
}

void TextModelStatic::BindSelectionMenu(FrameNode* frameNode, TextSpanType& spanType,
    TextResponseType& responseType, std::function<void()>&& buildFunc, SelectMenuParam& menuParam)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextPattern>();
    if (pattern) {
        pattern->BindSelectionMenu(spanType, responseType, buildFunc, menuParam);
    }
}

void TextModelStatic::SetHalfLeading(FrameNode* frameNode, const std::optional<bool>& valueOpt)
{
    TextModelNG::SetHalfLeading(frameNode, valueOpt.value_or(false));
}

void TextModelStatic::SetEnableHapticFeedback(FrameNode* frameNode, const std::optional<bool>& state)
{
    TextModelNG::SetEnableHapticFeedback(frameNode, state.value_or(true));
}

} // namespace OHOS::Ace::NG
