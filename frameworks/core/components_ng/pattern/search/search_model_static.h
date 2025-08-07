/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_STATIC_H

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/search/search_theme.h"
#include "core/components_ng/pattern/search/search_model.h"
#include "core/components_ng/pattern/search/search_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SearchModelStatic {
public:
    static void SetAdaptMinFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt);
    static void SetAdaptMaxFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt);
    static void SetTextIndent(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetPlaceholderFont(FrameNode* frameNode, const std::optional<Font>& font);
    static void SetSearchImageIcon(FrameNode* frameNode, std::optional<IconOptions>& iconOptions);
    static void SetSearchButtonFontSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetSearchButtonFontColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetSearchButtonAutoDisable(FrameNode* frameNode, const std::optional<bool>& needToDisable);
    static void SetTextColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetCopyOption(FrameNode* frameNode, const std::optional<CopyOptions>& copyOptionOpt);
    static void SetTextFont(FrameNode* frameNode, const std::optional<Font>& font);
    static void SetPlaceholderColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetCaretWidth(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetCaretColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void ResetCaretColor(FrameNode* frameNode);
    static void SetTextAlign(FrameNode* frameNode, const std::optional<TextAlign>& valueOpt);
    static void SetMinFontScale(FrameNode* frameNode, const std::optional<float>& value);
    static void SetMaxFontScale(FrameNode* frameNode, const std::optional<float>& value);
    static void SetCancelButtonStyle(FrameNode* frameNode, const std::optional<CancelButtonStyle>& style);
    static void SetCancelImageIcon(FrameNode* frameNode, std::optional<NG::IconOptions>& iconOptions);
    static void SetSearchEnterKeyType(FrameNode* frameNode, const std::optional<TextInputAction>& valueOpt);
    static void SetTextDecoration(FrameNode* frameNode, const std::optional<Ace::TextDecoration>& valueOpt);
    static void SetTextDecorationColor(FrameNode* frameNode, const std::optional<Color>& valueOpt);
    static void SetTextDecorationStyle(FrameNode* frameNode, const std::optional<Ace::TextDecorationStyle>& valueOpt);
    static void SetLetterSpacing(FrameNode* frameNode, const std::optional<Dimension>& valueOpt);
    static void SetLineHeight(FrameNode* frameNode, const std::optional<Dimension>& valueOpt);
    static void SetHalfLeading(FrameNode* frameNode, const std::optional<bool>& value);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetType(FrameNode* frameNode, const std::optional<TextInputType>& valueOpt);
    static void SetCustomKeyboard(FrameNode* frameNode, const std::function<void()>&& buildFunc, bool supportAvoidance);
    static void SetStopBackPress(FrameNode* frameNode, const std::optional<bool>& isStopBackPress);
    static void SetKeyboardAppearance(FrameNode* frameNode, const std::optional<KeyboardAppearance>& value);
    static void SetSelectionMenuOptions(FrameNode* frameNode, const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick);
    static void RequestKeyboardOnFocus(FrameNode* frameNode, std::optional<bool>& needToRequest);
    static void SetSelectionMenuHidden(FrameNode* frameNode, std::optional<bool>& selectionMenuHidden);
    static void SetEnablePreviewText(FrameNode* frameNode, std::optional<bool>& enablePreviewText);
    static void SetEnableHapticFeedback(FrameNode* frameNode, std::optional<bool>& state);
    static RefPtr<SearchTheme> GetTheme(const FrameNode *frameNode);
    static void SetSearchDefaultIcon(FrameNode *frameNode);
    static void SetCancelDefaultIcon(FrameNode* frameNode);
    static void SetOnChangeEvent(FrameNode* frameNode, std::function<void(const std::u16string&)>&& onChangeEvent);

private:

};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_STATIC_H
