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
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/symbol_modifier.h"
#include "core/components_ng/pattern/select/select_event_hub.h"
#include "core/components_ng/pattern/select/select_properties.h"
#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace {
namespace NG {
struct MenuParam;
}
enum class SelectColorType {
    FONT_COLOR,
    BACKGROUND_COLOR,
    SELECTED_OPTION_BG_COLOR,
    SELECTED_OPTION_FONT_COLOR,
    OPTION_BG_COLOR,
    OPTION_FONT_COLOR,
    MENU_BACKGROUND_COLOR
};

enum class SelectOptionType {
    TEXT,
    ICON
};

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

enum class AvoidanceMode {
    COVER_TARGET = 0,
    AVOID_AROUND_TARGET,
};

struct SelectParam {
    std::string text;
    std::string icon;
    std::function<void(WeakPtr<NG::FrameNode>)> symbolIcon = nullptr;
    RefPtr<SymbolModifier> symbolModifier = nullptr;
};

struct SelectResObjParam {
    RefPtr<ResourceObject> valueResObj = nullptr;
    RefPtr<ResourceObject> iconResObj = nullptr;
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
    virtual void SetAvoidance(AvoidanceMode mode);
    virtual void SetSelectChangeEvent(NG::SelectChangeEvent&& selectChangeEvent);
    virtual void SetValueChangeEvent(NG::ValueChangeEvent&& valueChangeEvent);
    virtual void SetOptionWidth(const Dimension& value);
    virtual void SetOptionHeight(const Dimension& value);
    virtual void SetOptionWidthFitTrigger(bool isFitTrigger);
    virtual void SetHasOptionWidth(bool hasOptionWidth);
    virtual void SetMenuBackgroundColor(const Color& color);
    virtual void SetMenuBackgroundBlurStyle(const BlurStyleOption& blurStyle);
    virtual void SetDivider(const NG::SelectDivider& divider);
    virtual void SetDividerStyle(const NG::SelectDivider& divider, const DividerMode& mode);
    virtual void SetControlSize(const std::optional<ControlSize>& controlSize);
    virtual void SetLayoutDirection(TextDirection value);
    virtual ControlSize GetControlSize();
    virtual void BackgroundColor(const Color& color) = 0;
    virtual void ResetBackgroundColor() = 0;
    virtual void ResetFontColor() {};
    virtual void SetMenuOutline(const NG::MenuParam& menuParam);
    virtual void SetTextModifierApply(const std::function<void(WeakPtr<NG::FrameNode>)>& textApply);
    virtual void SetArrowModifierApply(const std::function<void(WeakPtr<NG::FrameNode>)>& arrowApply);
    virtual void SetOptionTextModifier(const std::function<void(WeakPtr<NG::FrameNode>)>& optionApply);
    virtual void SetSelectedOptionTextModifier(const std::function<void(WeakPtr<NG::FrameNode>)>& optionSelectedApply);
    virtual void SetShowInSubWindow(bool isShowInSubWindow) = 0;
    virtual void ResetShowInSubWindow() = 0;
    virtual void SetShowDefaultSelectedIcon(bool show) = 0;
    virtual void ResetShowDefaultSelectedIcon() = 0;
    virtual void CreateWithColorResourceObj(
        const RefPtr<ResourceObject>& resObj, const SelectColorType& selectColorType) {};
    virtual void CreateWithValueIconResourceObj(const std::vector<SelectResObjParam>& resObjVec) {};
    virtual void CreateWithIntegerResourceObj(const RefPtr<ResourceObject>& resObj) {};
    virtual void CreateWithStringResourceObj(const RefPtr<ResourceObject>& resObj) {};
    virtual void SetOptionFontColorByUser(bool isValidValue = true) {};
    virtual void SetMenuBackgroundColorByUser(bool isValidValue = true) {};
    virtual void SetFontColorByUser(bool isValidValue = true) {};
    virtual void SetSelectedOptionFontColorByUser(bool isValidValue = true) {};
    virtual void SetOptionBgColorByUser(bool isValidValue = true) {};
    virtual void SetSelectedOptionBgColorByUser(bool isValidValue = true) {};

private:
    static std::unique_ptr<SelectModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_MODEL_H
