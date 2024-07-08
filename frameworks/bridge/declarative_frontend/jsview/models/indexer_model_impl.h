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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_FORM_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_FORM_MODEL_IMPL_H

#include "core/components_ng/pattern/indexer/indexer_model.h"

namespace OHOS::Ace::Framework {
class IndexerModelImpl : public OHOS::Ace::IndexerModel {
public:
    void Create(std::vector<std::string>& indexerArray, int32_t selectedVal, bool isArc = false) override;
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
    void SetAlignStyle(int32_t value) override;
    void SetOnSelected(std::function<void(const int32_t selected)>&& onSelect) override;
    void SetOnRequestPopupData(
        std::function<std::vector<std::string>(const int32_t selected)>&& RequestPopupData) override;
    void SetOnPopupSelected(std::function<void(const int32_t selected)>&& onPopupSelected) override;
    void SetTextStyle(TextStyle& textStyle, std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
        std::optional<std::vector<std::string>>& fontFamily, std::optional<FontStyle>& fontStyle);
    void SetAutoCollapse(bool state) override {}
    void SetEnableHapticFeedback(bool state) override {}
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_FORM_MODEL_IMPL_H
