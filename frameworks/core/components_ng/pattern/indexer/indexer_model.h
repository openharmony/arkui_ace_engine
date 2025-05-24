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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_MODEL_H

#include <mutex>

#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_v2/indexer/indexer_component.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace {
namespace {
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<V2::AlignStyle> ALIGN_STYLE = { V2::AlignStyle::LEFT, V2::AlignStyle::RIGHT, V2::AlignStyle::START,
    V2::AlignStyle::END };
const std::vector<NG::AlignStyle> NG_ALIGN_STYLE = { NG::AlignStyle::LEFT, NG::AlignStyle::RIGHT, NG::AlignStyle::START,
    NG::AlignStyle::END };
}; // namespace

enum class IndexerJsResourceType : int32_t {
    COLOR,
    SELECTED_COLOR,
    POPUP_COLOR,
    SELECTED_BACKGROUND_COLOR,
    POPUP_BACKGROUND,
    SELECTED_FONT_SIZE,
    SELECTED_FONT_FAMILY,
    POPUP_FONT_SIZE,
    POPUP_FONT_FAMILY,
    FONT_SIZE,
    FONT_FAMILY,
    ALIGN_OFFSET,
    POPUP_POSITION_X,
    POPUP_POSITION_Y,
    POPUP_SELECTED_COLOR,
    POPUP_UNSELECTED_COLOR,
    POPUP_ITEM_FONT_SIZE,
    POPUP_ITEM_FONT_FAMILY,
    POPUP_ITEM_BACKGROUND_COLOR,
    POPUP_TITLE_BACKGROUND,
    POPUP_HORIZONTAL_SPACE,
};

class ACE_FORCE_EXPORT IndexerModel {
public:
    static IndexerModel* GetInstance();
    virtual ~IndexerModel() = default;

    virtual void Create(std::vector<std::string>& indexerArray, int32_t selectedVal, bool isArc = false) = 0;
    virtual void SetSelectedColor(const std::optional<Color>& color) = 0;
    virtual void SetColor(const std::optional<Color>& color) = 0;
    virtual void SetPopupColor(const std::optional<Color>& color) = 0;
    virtual void SetSelectedBackgroundColor(const std::optional<Color>& color) = 0;
    virtual void SetPopupBackground(const std::optional<Color>& color) = 0;
    virtual void SetUsingPopup(bool state) = 0;
    virtual void SetSelectedFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
        std::optional<std::vector<std::string>>& fontFamily, std::optional<FontStyle>& fontStyle) = 0;
    virtual void SetPopupFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
        std::optional<std::vector<std::string>>& fontFamily, std::optional<FontStyle>& fontStyle) = 0;
    virtual void SetFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
        std::optional<std::vector<std::string>>& fontFamily, std::optional<FontStyle>& fontStyle) = 0;
    virtual void SetItemSize(const Dimension& value) = 0;
    virtual void SetPopupHorizontalSpace(const Dimension& value) {};
    virtual void SetAlignStyle(int32_t value) = 0;
    virtual void SetSelected(int32_t selected) {};
    virtual void SetPopupItemBackground(const std::optional<Color>& color) {};
    virtual void SetPopupSelectedColor(const std::optional<Color>& color) {};
    virtual void SetPopupUnselectedColor(const std::optional<Color>& color) {};
    virtual void SetFontSize(const Dimension& fontSize) {};
    virtual void SetFontWeight(const FontWeight weight) {};
    virtual void SetPopupPositionX(const std::optional<Dimension>& popupPositionXOpt) {};
    virtual void SetPopupPositionY(const std::optional<Dimension>& popupPositionYOpt) {};
    virtual void SetOnSelected(std::function<void(const int32_t selected)>&& onSelect) = 0;
    virtual void SetOnRequestPopupData(
        std::function<std::vector<std::string>(const int32_t selected)>&& RequestPopupData) = 0;
    virtual void SetOnPopupSelected(std::function<void(const int32_t selected)>&& onPopupSelected) = 0;
    virtual void SetChangeEvent(std::function<void(const int32_t selected)>&& changeEvent) {};
    virtual void SetCreatChangeEvent(std::function<void(const int32_t selected)>&& changeEvent) {};
    virtual void SetAutoCollapse(bool state) = 0;
    virtual void SetPopupBorderRadius(const Dimension& radius) {};
    virtual void SetPopupItemBorderRadius(const Dimension& radius) {};
    virtual void SetItemBorderRadius(const Dimension& radius) {};
    virtual void SetIndexerBorderRadius(const Dimension& radius) {};
    virtual void SetPopupBackgroundBlurStyle(const BlurStyleOption& indexerBlurStyle) {};
    virtual void SetPopupTitleBackground(const std::optional<Color>& color) {};
    virtual void SetAdaptiveWidth(bool state) {};
    virtual void SetEnableHapticFeedback(bool state) = 0;
    virtual void CreateWithResourceObj(IndexerJsResourceType jsType, const RefPtr<ResourceObject>& resObj) {};

private:
    static std::unique_ptr<IndexerModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_MODEL_H
