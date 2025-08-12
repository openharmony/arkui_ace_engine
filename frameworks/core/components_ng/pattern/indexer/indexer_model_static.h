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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_MODEL_STATIC_H

#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT IndexerModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetArrayValue(FrameNode* frameNode, const std::vector<std::string>& arrayValue);
    static void SetSelected(FrameNode* frameNode, int32_t selected);
    static void SetOnSelected(FrameNode* frameNode, std::function<void(const int32_t selected)>&& onSelect);
    static void SetColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetPopupColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetPopupBackground(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetPopupSelectedColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetPopupUnselectedColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetPopupItemBackground(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetUsingPopup(FrameNode* frameNode, const std::optional<bool>& state);
    static void SetSelectedFont(FrameNode* frameNode, const std::optional<Dimension>& fontSize,
        const std::optional<FontWeight>& fontWeight, const std::optional<std::vector<std::string>>& fontFamily,
        const std::optional<OHOS::Ace::FontStyle>& fontStyle);
    static void SetPopupFont(FrameNode* frameNode, const std::optional<Dimension>& fontSize,
        const std::optional<FontWeight>& fontWeight, const std::optional<std::vector<std::string>>& fontFamily,
        const std::optional<OHOS::Ace::FontStyle>& fontStyle);
    static void SetFontSize(FrameNode* frameNode, const Dimension& fontSize);
    static void SetFontWeight(FrameNode* frameNode, const FontWeight weight);
    static void SetItemSize(FrameNode* frameNode, const Dimension& value);
    static void SetFont(FrameNode* frameNode, const std::optional<Dimension>& fontSize,
        const std::optional<FontWeight>& fontWeight, const std::optional<std::vector<std::string>>& fontFamily,
        const std::optional<OHOS::Ace::FontStyle>& fontStyle);
    static void SetChangeEvent(FrameNode* frameNode, std::function<void(const int32_t selected)>&& changeEvent);
    static void SetOnRequestPopupData(
        FrameNode* frameNode, std::function<std::vector<std::string>(const int32_t selected)>&& requestPopupData);
    static void SetOnPopupSelected(FrameNode* frameNode, std::function<void(const int32_t selected)>&& onPopupSelected);
    static void SetPopupPositionX(FrameNode* frameNode, const std::optional<Dimension>& popupPositionXOpt);
    static void SetPopupPositionY(FrameNode* frameNode, const std::optional<Dimension>& popupPositionYOpt);
    static void SetAutoCollapse(FrameNode* frameNode, const std::optional<bool>& autoCollapse);
    static void SetPopupItemBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radius);
    static void SetPopupBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radius);
    static void SetItemBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radius);
    static void SetIndexerBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radius);
    static void SetPopupBackgroundBlurStyle(FrameNode* frameNode, const BlurStyleOption& indexerBlurStyle);
    static void SetPopupTitleBackground(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetEnableHapticFeedback(FrameNode* frameNode, const std::optional<bool>& state);
    static void SetAlignStyle(FrameNode* frameNode, const std::optional<AlignStyle>& alignStyle);
    static void SetPopupHorizontalSpace(FrameNode* frameNode, const std::optional<Dimension>& popupHorizontalSpace);
    static void SetCreatChangeEvent(FrameNode* frameNode, std::function<void(const int32_t selected)>&& changeEvent);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_MODEL_STATIC_H
