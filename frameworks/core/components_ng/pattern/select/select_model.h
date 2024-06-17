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

    virtual void Create(const std::vector<SelectParam>& params);
    virtual void SetSelected(int32_t idx);
    virtual void SetValue(const std::string& value);
    virtual void SetFontSize(const Dimension& value);
    virtual void SetFontWeight(const FontWeight& value);
    virtual void SetFontFamily(const std::vector<std::string>& value);
    virtual void SetItalicFontStyle(const Ace::FontStyle& value);
    virtual void SetFontColor(const Color& color);
    virtual void SetSelectedOptionBgColor(const Color& color);
    virtual void SetSelectedOptionFontSize(const Dimension& value);
    virtual void SetSelectedOptionFontWeight(const FontWeight& value);
    virtual void SetSelectedOptionFontFamily(const std::vector<std::string>& value);
    virtual void SetSelectedOptionItalicFontStyle(const Ace::FontStyle& value);
    virtual void SetSelectedOptionFontColor(const Color& color);
    virtual void SetOptionBgColor(const Color& color);
    virtual void SetOptionFontSize(const Dimension& value);
    virtual void SetOptionFontWeight(const FontWeight& value);
    virtual void SetOptionFontFamily(const std::vector<std::string>& value);
    virtual void SetOptionItalicFontStyle(const Ace::FontStyle& value);
    virtual void SetOptionFontColor(const Color& color);
    virtual void SetOnSelect(NG::SelectEvent&& onSelect);
    virtual void SetWidth(Dimension& value);
    virtual void SetHeight(Dimension& value);
    virtual void SetSize(Dimension& width, Dimension& height);
    virtual void SetPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right);
    virtual void SetPadding(const CalcDimension& value);
    virtual void SetPaddingLeft(const CalcDimension& value);
    virtual void SetPaddingTop(const CalcDimension& value);
    virtual void SetPaddingRight(const CalcDimension& value);
    virtual void SetPaddingBottom(const CalcDimension& value);
    virtual void SetSpace(const Dimension& value);
    virtual void SetArrowPosition(const ArrowPosition value);
    virtual void SetMenuAlign(const MenuAlign& menuAlign);
    virtual void SetSelectChangeEvent(NG::SelectChangeEvent&& selectChangeEvent);
    virtual void SetValueChangeEvent(NG::ValueChangeEvent&& valueChangeEvent);
    virtual void SetOptionWidth(const Dimension& value);
    virtual void SetOptionHeight(const Dimension& value);
    virtual void SetOptionWidthFitTrigger(bool isFitTrigger);
    virtual void SetHasOptionWidth(bool hasOptionWidth);
    virtual void SetMenuBackgroundColor(const Color& color);
    virtual void SetMenuBackgroundBlurStyle(const BlurStyleOption& blurStyle);
    virtual void SetDivider(const NG::SelectDivider& divider);
    virtual void SetControlSize(const std::optional<ControlSize>& controlSize);
    virtual void SetLayoutDirection(TextDirection value);
    virtual ControlSize GetControlSize();
private:
    static std::unique_ptr<SelectModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_MODEL_H
