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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_MODEL_H

#include <mutex>

#include "core/components_ng/pattern/indexer/indexer_event_hub.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/indexer/indexer_view.h"
#include "core/components_v2/indexer/indexer_component.h"
#include "core/components_v2/indexer/indexer_event_info.h"
#include "core/components_v2/indexer/render_indexer.h"
#include "core/event/ace_event_handler.h"

namespace OHOS::Ace {
namespace {
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<V2::AlignStyle> ALIGN_STYLE = { V2::AlignStyle::LEFT, V2::AlignStyle::RIGHT };
const std::vector<NG::AlignStyle> NG_ALIGN_STYLE = { NG::AlignStyle::LEFT, NG::AlignStyle::RIGHT };
}; // namespace
class IndexerModel {
public:
    static IndexerModel* GetInstance();
    virtual ~IndexerModel() = default;

    virtual void Create(std::vector<std::string>& indexerArray, int32_t selectedVal) = 0;
    virtual void SetSelectedColor(const Color& color) = 0;
    virtual void SetColor(const Color& color) = 0;
    virtual void SetPopupColor(const Color& color) = 0;
    virtual void SetSelectedBackgroundColor(const Color& color) = 0;
    virtual void SetPopupBackground(const Color& color) = 0;
    virtual void SetUsingPopup(bool state) = 0;
    virtual void SetSelectedFont(const TextStyle& textStyle) = 0;
    virtual void SetPopupFont(const TextStyle& textStyle) = 0;
    virtual void SetFont(const TextStyle& textStyle) = 0;
    virtual void SetItemSize(const Dimension& value) = 0;
    virtual void SetPopupHorizontalSpace(const Dimension& value) {};
    virtual void SetAlignStyle(int32_t value) = 0;
    virtual void SetSelected(int32_t selected) {};
    virtual void SetPopupItemBackground(const std::optional<Color>& color) {};
    virtual void SetPopupSelectedColor(const std::optional<Color>& color) {};
    virtual void SetPopupUnselectedColor(const std::optional<Color>& color) {};
    virtual void SetFontSize(const Dimension& fontSize) {};
    virtual void SetFontWeight(FontWeight weight) {};
    virtual void SetPopupPositionX(const Dimension& positionX) {};
    virtual void SetPopupPositionY(const Dimension& positionY) {};

    virtual void SetFocusable(bool focusable) {};
    virtual void SetFocusNode(bool isFocusNode) {};

    virtual void SetOnSelected(std::function<void(const int32_t selected)>&& onSelect) = 0;
    virtual void SetOnRequestPopupData(
        std::function<std::vector<std::string>(const int32_t selected)>&& RequestPopupData) = 0;
    virtual void SetOnPopupSelected(std::function<void(const int32_t selected)>&& onPopupSelected) = 0;
private:
    static std::unique_ptr<IndexerModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_MODEL_H
