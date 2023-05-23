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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_MODEL_NG_H

#include "core/components_ng/pattern/select/select_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SelectModelNG : public OHOS::Ace::SelectModel {
public:
    void Create(const std::vector<SelectParam>& params) override;
    void SetSelected(int32_t idx) override;
    void SetValue(const std::string& value) override;
    void SetFontSize(const Dimension& value) override;
    void SetFontWeight(const FontWeight& value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void SetItalicFontStyle(const Ace::FontStyle& value) override;
    void SetFontColor(const Color& color) override;
    void SetSelectedOptionBgColor(const Color& color) override;
    void SetSelectedOptionFontSize(const Dimension& value) override;
    void SetSelectedOptionFontWeight(const FontWeight& value) override;
    void SetSelectedOptionFontFamily(const std::vector<std::string>& value) override;
    void SetSelectedOptionItalicFontStyle(const Ace::FontStyle& value) override;
    void SetSelectedOptionFontColor(const Color& color) override;
    void SetOptionBgColor(const Color& color) override;
    void SetOptionFontSize(const Dimension& value) override;
    void SetOptionFontWeight(const FontWeight& value) override;
    void SetOptionFontFamily(const std::vector<std::string>& value) override;
    void SetOptionItalicFontStyle(const Ace::FontStyle& value) override;
    void SetOptionFontColor(const Color& color) override;
    void SetOnSelect(NG::SelectEvent&& onSelect) override;
    void SetWidth(Dimension& value) override;
    void SetHeight(Dimension& value) override;
    void SetSize(Dimension& width, Dimension& height) override;
    void SetPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) override;
    void SetPadding(const CalcDimension& value) override;
    void SetPaddingLeft(const CalcDimension& value) override;
    void SetPaddingTop(const CalcDimension& value) override;
    void SetPaddingRight(const CalcDimension& value) override;
    void SetPaddingBottom(const CalcDimension& value) override;
    void SetSpace(const Dimension& value) override;
    void SetArrowPosition(const ArrowPosition value) override;
    void SetMenuAlign(const MenuAlign& menuAlign) override;
    void SetSelectChangeEvent(NG::SelectChangeEvent&& selectChangeEvent) override;
    void SetValueChangeEvent(NG::ValueChangeEvent&& valueChangeEvent) override;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_MODEL_NG_H
