/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_TOKEN_COLORS_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_TOKEN_COLORS_H

#include "ui/base/ace_type.h"
#include "ui/properties/color.h"
#include "ui/resource/resource_object.h"

namespace OHOS::Ace {

struct TokenColorData {
    const char* colorName { nullptr };
    const int32_t systemResourceId {0};
};
class ACE_FORCE_EXPORT TokenColors : public virtual AceType {
    DECLARE_ACE_TYPE(TokenColors, AceType);

public:
    static constexpr int32_t BRAND = 0;
    static constexpr int32_t WARNING = 1;
    static constexpr int32_t ALERT = 2;
    static constexpr int32_t CONFIRM = 3;

    static constexpr int32_t FONT_PRIMARY = 4;
    static constexpr int32_t FONT_SECONDARY = 5;
    static constexpr int32_t FONT_TERTIARY = 6;
    static constexpr int32_t FONT_FOURTH = 7;
    static constexpr int32_t FONT_EMPHASIZE = 8;

    static constexpr int32_t FONT_ON_PRIMARY = 9;
    static constexpr int32_t FONT_ON_SECONDARY = 10;
    static constexpr int32_t FONT_ON_TERTIARY = 11;
    static constexpr int32_t FONT_ON_FOURTH = 12;

    static constexpr int32_t ICON_PRIMARY = 13;
    static constexpr int32_t ICON_SECONDARY = 14;
    static constexpr int32_t ICON_TERTIARY = 15;
    static constexpr int32_t ICON_FOURTH = 16;
    static constexpr int32_t ICON_EMPHASIZE = 17;
    static constexpr int32_t ICON_SUB_EMPHASIZE = 18;

    static constexpr int32_t ICON_ON_PRIMARY = 19;
    static constexpr int32_t ICON_ON_SECONDARY = 20;
    static constexpr int32_t ICON_ON_TERTIARY = 21;
    static constexpr int32_t ICON_ON_FOURTH = 22;

    static constexpr int32_t BACKGROUND_PRIMARY = 23;
    static constexpr int32_t BACKGROUND_SECONDARY = 24;
    static constexpr int32_t BACKGROUND_TERTIARY = 25;
    static constexpr int32_t BACKGROUND_FOURTH = 26;
    static constexpr int32_t BACKGROUND_EMPHASIZE = 27;

    static constexpr int32_t COMP_FOREGROUND_PRIMARY = 28;
    static constexpr int32_t COMP_BACKGROUND_PRIMARY = 29;
    static constexpr int32_t COMP_BACKGROUND_PRIMARY_TRAN = 30;
    static constexpr int32_t COMP_BACKGROUND_PRIMARY_CONTRARY = 31;
    static constexpr int32_t COMP_BACKGROUND_GRAY = 32;
    static constexpr int32_t COMP_BACKGROUND_SECONDARY = 33;
    static constexpr int32_t COMP_BACKGROUND_TERTIARY = 34;
    static constexpr int32_t COMP_BACKGROUND_EMPHASIZE = 35;
    static constexpr int32_t COMP_BACKGROUND_NEUTRAL = 36;
    static constexpr int32_t COMP_EMPHASIZE_SECONDARY = 37;
    static constexpr int32_t COMP_EMPHASIZE_TERTIARY = 38;
    static constexpr int32_t COMP_DIVIDER = 39;
    static constexpr int32_t COMP_COMMON_CONTRARY = 40;
    static constexpr int32_t COMP_BACKGROUND_FOCUS = 41;
    static constexpr int32_t COMP_FOCUSED_PRIMARY = 42;
    static constexpr int32_t COMP_FOCUSED_SECONDARY = 43;
    static constexpr int32_t COMP_FOCUSED_TERTIARY = 44;

    static constexpr int32_t INTERACTIVE_HOVER = 45;
    static constexpr int32_t INTERACTIVE_PRESSED = 46;
    static constexpr int32_t INTERACTIVE_FOCUS = 47;
    static constexpr int32_t INTERACTIVE_ACTIVE = 48;
    static constexpr int32_t INTERACTIVE_SELECT = 49;
    static constexpr int32_t INTERACTIVE_CLICK = 50;
    static constexpr int32_t TOTAL_NUMBER = 51;

    TokenColors() = default;
    virtual ~TokenColors() = default;

    void SetColors(const std::vector<Color>& colors);
    void SetColor(uint32_t idx, const Color& color);
    const std::vector<Color>& GetColors();

    Color Brand() const;
    Color Warning() const;
    Color Alert() const;
    Color Confirm() const;

    Color FontPrimary() const;
    Color FontSecondary() const;
    Color FontTertiary() const;
    Color FontFourth() const;
    Color FontEmphasize() const;

    Color FontOnPrimary() const;
    Color FontOnSecondary() const;
    Color FontOnTertiary() const;
    Color FontOnFourth() const;

    Color IconPrimary() const;
    Color IconSecondary() const;
    Color IconTertiary() const;
    Color IconFourth() const;
    Color IconEmphasize() const;
    Color IconSubEmphasize() const;

    Color IconOnPrimary() const;
    Color IconOnSecondary() const;
    Color IconOnTertiary() const;
    Color IconOnFourth() const;

    Color BackgroundPrimary() const;
    Color BackgroundSecondary() const;
    Color BackgroundTertiary() const;
    Color BackgroundFourth() const;
    Color BackgroundEmphasize() const;

    Color CompForegroundPrimary() const;
    Color CompBackgroundPrimary() const;
    Color CompBackgroundPrimaryTran() const;
    Color CompBackgroundPrimaryContrary() const;
    Color CompBackgroundGray() const;
    Color CompBackgroundSecondary() const;
    Color CompBackgroundTertiary() const;
    Color CompBackgroundEmphasize() const;
    Color CompBackgroundNeutral() const;
    Color CompEmphasizeSecondary() const;
    Color CompEmphasizeTertiary() const;
    Color CompDivider() const;
    Color CompCommonContrary() const;
    Color CompBackgroundFocus() const;
    Color CompFocusedPrimary() const;
    Color CompFocusedSecondary() const;
    Color CompFocusedTertiary() const;

    Color InteractiveHover() const;
    Color InteractivePressed() const;
    Color InteractiveFocus() const;
    Color InteractiveActive() const;
    Color InteractiveSelect() const;
    Color InteractiveClick() const;
    static const char* GetColorNameByIndex(int32_t idx);

    static int32_t GetSystemColorResIdByIndex(int32_t idx);

    Color GetByIndex(uint32_t idx);

    static const TokenColorData& GetTokenColorDataByIndex(int32_t idx);

    void SetResObjs(std::vector<RefPtr<ResourceObject>>&& resObjs)
    {
        resObjs_ = std::move(resObjs);
    }

    const std::vector<RefPtr<ResourceObject>>& GetResObjs() const
    {
        return resObjs_;
    }

    void SetColorMode(const ColorMode& colorMode)
    {
        colorMode_ = colorMode;
    }
private:
    Color GetColorWithResourceObject(int32_t colorIndex) const;
    std::vector<Color> colors_ = std::vector<Color>(TokenColors::TOTAL_NUMBER);
    std::vector<RefPtr<ResourceObject>> resObjs_;
    ColorMode colorMode_ = ColorMode::COLOR_MODE_UNDEFINED;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_TOKEN_COLORS_H
