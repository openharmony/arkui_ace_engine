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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_MODEL_STATIC_H

#include <functional>
#include <string>

#include "interfaces/native/node/styled_string.h"

#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/text/text_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TextModelStatic {
    inline static const int32_t DEFAULT_VARIABLE_FONT_WEIGHT = 400;
public:
    static void SetFontWeight(FrameNode* frameNode, const std::optional<Ace::FontWeight>&);
    static void SetVariableFontWeight(FrameNode* frameNode, const std::optional<int32_t>& value);
    static void SetEnableVariableFontWeight(FrameNode* frameNode, const std::optional<bool>& value);
    static void SetMinFontScale(FrameNode* frameNode, const std::optional<float>& value);
    static void SetMaxFontScale(FrameNode* frameNode, const std::optional<float>& value);
    static void SetItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value);
    static void SetTextAlign(FrameNode* frameNode, const std::optional<Ace::TextAlign>& value);
    static void SetTextColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetLineHeight(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetLineSpacing(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetTextOverflow(FrameNode* frameNode, const std::optional<TextOverflow>& value);
    static void SetTextDecoration(FrameNode* frameNode, const std::optional<TextDecoration>& value);
    static void SetTextDecorationColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetTextDecorationStyle(FrameNode* frameNode, const std::optional<TextDecorationStyle>& value);
    static void SetTextCase(FrameNode* frameNode, const std::optional<TextCase>& value);
    static void SetMaxLines(FrameNode* frameNode, const std::optional<uint32_t>& value);
    static void SetAdaptMinFontSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetAdaptMaxFontSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& value);
    static void SetCopyOption(FrameNode* frameNode, const std::optional<CopyOptions>& copyOption);
    static void SetTextShadow(FrameNode* frameNode, const std::optional<std::vector<Shadow>>& value);
    static void SetHeightAdaptivePolicy(FrameNode* frameNode, const std::optional<TextHeightAdaptivePolicy>& value);
    static void SetTextIndent(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetBaselineOffset(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetLetterSpacing(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetFont(FrameNode* frameNode, const std::optional<Font>& value);
    static void SetWordBreak(FrameNode* frameNode, const std::optional<WordBreak>& value);
    static void SetLineBreakStrategy(FrameNode* frameNode, const std::optional<LineBreakStrategy>& value);
    static void SetEllipsisMode(FrameNode* frameNode, const std::optional<EllipsisMode>& value);
    static void SetCaretColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetHalfLeading(FrameNode* frameNode, const std::optional<bool>& valueOpt);
    static void SetEnableHapticFeedback(FrameNode* frameNode, const std::optional<bool>& state);

    static void SetTextSelectableMode(FrameNode* frameNode, const std::optional<TextSelectableMode>& value);
    static void BindSelectionMenu(FrameNode* frameNode, TextSpanType& spanType, TextResponseType& responseType,
        std::function<void()>&& buildFunc, SelectMenuParam& menuParam);
    static void SetSelectionMenuOptions(FrameNode* frameNode, const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_MODEL_STATIC_H
