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

#include "core/components_ng/pattern/indexer/indexer_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT IndexerModelNG : public OHOS::Ace::IndexerModel {
public:
    void Create(std::vector<std::string>& indexerArray, int32_t selectedVal) override;
    void SetSelectedColor(const std::optional<Color>& color) override;
    void SetColor(const std::optional<Color>& color) override;
    void SetPopupColor(const std::optional<Color>& color) override;
    void SetSelectedBackgroundColor(const std::optional<Color>& color) override;
    void SetPopupBackground(const std::optional<Color>& color) override;
    void SetUsingPopup(bool state) override;
    void SetSelectedFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
        std::optional<std::vector<std::string>>& fontFamily, std::optional<FontStyle>& fontStyle) override;
    void SetPopupFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
        std::optional<std::vector<std::string>>& fontFamily, std::optional<FontStyle>& fontStyle) override;
    void SetFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
        std::optional<std::vector<std::string>>& fontFamily, std::optional<FontStyle>& fontStyle) override;
    void SetItemSize(const Dimension& value) override;
    void SetPopupHorizontalSpace(const Dimension& value) override;
    void SetAlignStyle(int32_t value) override;
    void SetSelected(int32_t selected) override;
    void SetPopupPositionX(const Dimension& positionX) override;
    void SetPopupPositionY(const Dimension& positionY) override;
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
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_MODEL_NG_H
