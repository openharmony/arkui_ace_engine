/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_MODEL_NG_H

#include "core/components/common/properties/decoration.h"
#include "core/components_ng/pattern/indexer/indexer_model.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT IndexerModelNG : public OHOS::Ace::IndexerModel {
public:
    void CreateWithResourceObj(IndexerJsResourceType jsType, const RefPtr<ResourceObject>& resObj) override;
    void Create(std::vector<std::string>& indexerArray, int32_t selectedVal, bool isArc = false) override;
    void SetSelectedColor(const std::optional<Color>& color) override;
    void SetColor(const std::optional<Color>& color) override;
    void SetPopupColor(const std::optional<Color>& color) override;
    void SetSelectedBackgroundColor(const std::optional<Color>& color) override;
    void SetPopupBackground(const std::optional<Color>& color) override;
    void SetUsingPopup(bool state) override;
    void SetSelectedFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
        std::optional<std::vector<std::string>>& fontFamily, std::optional<OHOS::Ace::FontStyle>& fontStyle) override;
    void SetPopupFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
        std::optional<std::vector<std::string>>& fontFamily, std::optional<OHOS::Ace::FontStyle>& fontStyle) override;
    void SetFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
        std::optional<std::vector<std::string>>& fontFamily, std::optional<OHOS::Ace::FontStyle>& fontStyle) override;
    void SetItemSize(const Dimension& value) override;
    void SetPopupHorizontalSpace(const Dimension& value) override;
    void SetAlignStyle(int32_t value) override;
    void SetSelected(int32_t selected) override;
    void SetPopupPositionX(const std::optional<Dimension>& popupPositionXOpt) override;
    void SetPopupPositionY(const std::optional<Dimension>& popupPositionYOpt) override;
    void SetPopupItemBackground(const std::optional<Color>& color) override;
    void SetPopupSelectedColor(const std::optional<Color>& color) override;
    void SetPopupUnselectedColor(const std::optional<Color>& color) override;
    void SetFontSize(const Dimension& fontSize) override;
    void SetFontWeight(const FontWeight weight) override;
    void SetOnSelected(std::function<void(const int32_t selected)>&& onSelect) override;
    void SetOnRequestPopupData(
        std::function<std::vector<std::string>(const int32_t selected)>&& RequestPopupData) override;
    void SetOnPopupSelected(std::function<void(const int32_t selected)>&& onPopupSelected) override;
    void SetChangeEvent(std::function<void(const int32_t selected)>&& changeEvent) override;
    void SetCreatChangeEvent(std::function<void(const int32_t selected)>&& changeEvent) override;
    void SetAutoCollapse(bool state) override;
    void SetPopupBorderRadius(const Dimension& radius) override;
    void SetPopupItemBorderRadius(const Dimension& radius) override;
    void SetItemBorderRadius(const Dimension& radius) override;
    void SetIndexerBorderRadius(const Dimension& radius) override;
    void SetPopupBackgroundBlurStyle(const BlurStyleOption& indexerBlurStyle) override;
    void SetPopupTitleBackground(const std::optional<Color>& color) override;
    void SetAdaptiveWidth(bool state) override;
    void SetEnableHapticFeedback(bool state) override;
    void SetSelectedColorByUser(bool isByUser) override;
    void SetColorByUser(bool isByUser) override;
    void SetPopupColorByUser(bool isByUser) override;
    void SetSelectedBGColorByUser(bool isByUser) override;
    void SetPopupUnselectedColorByUser(bool isByUser) override;
    void SetPopupTitleBackgroundByUser(bool isByUser) override;
    void SetPopupSelectedColorByUser(bool isByUser) override;
    void SetPopupItemBackgroundColorByUser(bool isByUser) override;
    void SetPopupBackgroundColorByUser(bool isByUser) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId, bool isArc = false);
    static void CreateWithResourceObj(
        FrameNode* frameNode, IndexerJsResourceType jsType, const RefPtr<ResourceObject>& resObj);
    static void SetArrayValue(FrameNode* frameNode, const std::vector<std::string>& arrayValue);
    static void SetAdaptiveWidth(FrameNode* frameNode, bool state);
    static void SetFontSize(FrameNode* frameNode, const Dimension& fontSize);
    static void SetFontWeight(FrameNode* frameNode, const FontWeight weight);
    static void SetSelectedFont(FrameNode* frameNode, std::optional<Dimension>& fontSize,
        std::optional<FontWeight>& fontWeight, std::optional<std::vector<std::string>>& fontFamily,
        std::optional<OHOS::Ace::FontStyle>& fontStyle);
    static void SetPopupFont(FrameNode* frameNode, std::optional<Dimension>& fontSize,
        std::optional<FontWeight>& fontWeight, std::optional<std::vector<std::string>>& fontFamily,
        std::optional<OHOS::Ace::FontStyle>& fontStyle);
    static void SetFont(FrameNode* frameNode, std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
        std::optional<std::vector<std::string>>& fontFamily, std::optional<OHOS::Ace::FontStyle>& fontStyle);
    static void SetPopupUnselectedColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetPopupItemBackground(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetPopupColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetPopupBackground(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetPopupSelectedColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetAlignStyle(FrameNode* frameNode, int32_t value);
    static void SetPopupHorizontalSpace(FrameNode* frameNode, const Dimension& popupHorizontalSpace);
    static void SetUsingPopup(FrameNode* frameNode, bool state);
    static void SetSelected(FrameNode* frameNode, int32_t selected);
    static void SetItemSize(FrameNode* frameNode, const Dimension& value);
    static void SetPopupPositionX(FrameNode* frameNode, const std::optional<Dimension>& popupPositionXOpt);
    static void SetPopupPositionY(FrameNode* frameNode, const std::optional<Dimension>& popupPositionYOpt);
    static void SetPopupBorderRadius(FrameNode* frameNode, const Dimension& radius);
    static void SetPopupItemBorderRadius(FrameNode* frameNode, const Dimension& radius);
    static void SetItemBorderRadius(FrameNode* frameNode, const Dimension& radius);
    static void SetIndexerBorderRadius(FrameNode* frameNode, const Dimension& radius);
    static void SetPopupBackgroundBlurStyle(FrameNode* frameNode, const BlurStyleOption& indexerBlurStyle);
    static void SetPopupTitleBackground(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetAutoCollapse(FrameNode* frameNode, bool autoCollapse);
    static void SetEnableHapticFeedback(FrameNode* frameNode, bool state);
    static void SetOnSelected(FrameNode* frameNode,
        std::function<void(const int32_t selected)>&& onSelect);
    static void SetOnRequestPopupData(FrameNode* frameNode,
        std::function<std::vector<std::string>(const int32_t selected)>&& RequestPopupData);
    static void SetOnPopupSelected(FrameNode* frameNode,
        std::function<void(const int32_t selected)>&& onPopupSelected);
    static void SetChangeEvent(FrameNode* frameNode, std::function<void(const int32_t selected)>&& changeEvent);
    static void SetCreatChangeEvent(FrameNode* frameNode, std::function<void(const int32_t selected)>&& changeEvent);
    static void SetSelectedColorByUser(FrameNode* frameNode, bool isByUser);
    static void SetColorByUser(FrameNode* frameNode, bool isByUser);
    static void SetPopupColorByUser(FrameNode* frameNode, bool isByUser);
    static void SetSelectedBGColorByUser(FrameNode* frameNode, bool isByUser);
    static void SetPopupUnselectedColorByUser(FrameNode* frameNode, bool isByUser);
    static void SetPopupTitleBackgroundByUser(FrameNode* frameNode, bool isByUser);
    static void SetPopupSelectedColorByUser(FrameNode* frameNode, bool isByUser);
    static void SetPopupItemBackgroundByUser(FrameNode* frameNode, bool isByUser);
    static void SetPopupBackgroundByUser(FrameNode* frameNode, bool isByUser);
    static void RemoveColor(FrameNode* frameNode);
    static void RemovePopupColor(FrameNode* frameNode);
    static void RemoveSelectedColor(FrameNode* frameNode);
    static void RemoveSelectedBackgroundColor(FrameNode* frameNode);
    static void RemovePopupUnselectedColor(FrameNode* frameNode);
    static void RemovePopupBackground(FrameNode* frameNode);
    static void RemovePopupSelectedColor(FrameNode* frameNode);
    static void RemovePopupItemBackground(FrameNode* frameNode);
    static void RemovePopupTitleBackground(FrameNode* frameNode);
    static void ChangeFlagForSetByUser(FrameNode* frameNode, std::string type, bool setByUser);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_MODEL_NG_H
