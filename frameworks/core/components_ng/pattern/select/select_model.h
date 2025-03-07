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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_MODEL_H

#include <optional>
#include <string_view>

#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/symbol_modifier.h"
#include "core/components_ng/pattern/select/select_event_hub.h"
#include "core/components_ng/pattern/select/select_properties.h"
#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace {
enum class ArrowPosition {
    END = 0,
    START,
};

enum class MenuAlignType {
    START = 0,
    CENTER,
    END,
};

struct MenuAlign {
    MenuAlignType alignType = MenuAlignType::START;
    DimensionOffset offset = DimensionOffset(Dimension(0, DimensionUnit::VP), Dimension(0, DimensionUnit::VP));
};

struct SelectParam {
    std::string text;
    std::string icon;
    std::function<void(WeakPtr<NG::FrameNode>)> symbolIcon = nullptr;
    RefPtr<SymbolModifier> symbolModifier = nullptr;
};

class ACE_FORCE_EXPORT SelectModel {
public:
    static SelectModel* GetInstance();
    virtual ~SelectModel() = default;

    virtual void Create(const std::vector<SelectParam>& params) = 0;
    virtual void SetSelected(int32_t idx) = 0;
    virtual void SetValue(const std::string& value) = 0;
    virtual void SetFontSize(const Dimension& value) = 0;
    virtual void SetFontWeight(const FontWeight& value) = 0;
    virtual void SetFontFamily(const std::vector<std::string>& value) = 0;
    virtual void SetItalicFontStyle(const Ace::FontStyle& value) = 0;
    virtual void SetFontColor(const Color& color) = 0;
    virtual void SetSelectedOptionBgColor(const Color& color) = 0;
    virtual void SetSelectedOptionFontSize(const Dimension& value) = 0;
    virtual void SetSelectedOptionFontWeight(const FontWeight& value) = 0;
    virtual void SetSelectedOptionFontFamily(const std::vector<std::string>& value) = 0;
    virtual void SetSelectedOptionItalicFontStyle(const Ace::FontStyle& value) = 0;
    virtual void SetSelectedOptionFontColor(const Color& color) = 0;
    virtual void SetOptionBgColor(const Color& color) = 0;
    virtual void SetOptionFontSize(const Dimension& value) = 0;
    virtual void SetOptionFontWeight(const FontWeight& value) = 0;
    virtual void SetOptionFontFamily(const std::vector<std::string>& value) = 0;
    virtual void SetOptionItalicFontStyle(const Ace::FontStyle& value) = 0;
    virtual void SetOptionFontColor(const Color& color) = 0;
    virtual void SetOnSelect(NG::SelectEvent&& onSelect) = 0;
    virtual void SetWidth(Dimension& value) = 0;
    virtual void SetHeight(Dimension& value) = 0;
    virtual void SetSize(Dimension& width, Dimension& height) = 0;
    virtual void SetPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) = 0;
    virtual void SetPadding(const CalcDimension& value) = 0;
    virtual void SetPaddingLeft(const CalcDimension& value) = 0;
    virtual void SetPaddingTop(const CalcDimension& value) = 0;
    virtual void SetPaddingRight(const CalcDimension& value) = 0;
    virtual void SetPaddingBottom(const CalcDimension& value) = 0;
    virtual void SetSpace(const Dimension& value) = 0;
    virtual void SetArrowPosition(const ArrowPosition value) = 0;
    virtual void SetMenuAlign(const MenuAlign& menuAlign) = 0;
    virtual void SetSelectChangeEvent(NG::SelectChangeEvent&& selectChangeEvent) = 0;
    virtual void SetValueChangeEvent(NG::ValueChangeEvent&& valueChangeEvent) = 0;
    virtual void SetOptionWidth(const Dimension& value) = 0;
    virtual void SetOptionHeight(const Dimension& value) = 0;
    virtual void SetOptionWidthFitTrigger(bool isFitTrigger) = 0;
    virtual void SetHasOptionWidth(bool hasOptionWidth) = 0;
    virtual void SetMenuBackgroundColor(const Color& color) = 0;
    virtual void SetMenuBackgroundBlurStyle(const BlurStyleOption& blurStyle) = 0;
    virtual void SetDivider(const NG::SelectDivider& divider) = 0;
    virtual void SetControlSize(const std::optional<ControlSize>& controlSize) = 0;
    virtual void SetLayoutDirection(TextDirection value) = 0;
    virtual ControlSize GetControlSize() = 0;
private:
    static std::unique_ptr<SelectModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_MODEL_H
