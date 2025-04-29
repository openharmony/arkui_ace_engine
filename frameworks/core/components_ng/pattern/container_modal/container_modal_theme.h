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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CONTAINER_MODAL_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CONTAINER_MODAL_THEME_H

#include <cstdint>
#include "base/utils/device_config.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"

namespace OHOS::Ace::NG {

constexpr uint32_t DARK_MODE_NORMAL_CLOSE_BTN_COLOR = 0xff3d2e2d;
constexpr uint32_t HOVER_CLOSE_BTN_COLOR_DARK = 0xff414141;
constexpr uint32_t HOVER_CLOSE_BTN_COLOR_LIGHT = 0xffdcdcdc;
constexpr uint32_t HOVER_FILL_CLOSE_BTN_COLOR_DARK = 0xffe5e5e5;
constexpr uint32_t HOVER_FILL_CLOSE_BTN_COLOR_LIGHT = 0xffffffff;
constexpr uint32_t HOVER_FILL_NORMA_BTN_COLOR_LIGHT = 0xff000000;
constexpr uint32_t PRESS_CLOSE_BTN_COLOR_DARK = 0xffde6355;
constexpr uint32_t PRESS_CLOSE_BTN_COLOR_LIGHT = 0xffd03922;
constexpr uint32_t PRESS_NORMAL_BTN_COLOR_DARK = 0xff4b4b4b;
constexpr uint32_t PRESS_NORMAL_BTN_COLOR_LIGHT = 0xffd0d0d0;
constexpr uint32_t UNFOCUS_CLOSE_BTN_COLOR_DARK = 0xff191312;
constexpr uint32_t UNFOCUS_CLOSE_BTN_COLOR_LIGHT = 0xfffef7f6;
constexpr uint32_t UNFOCUS_BTN_COLOR_DARK = 0xff121212;
constexpr uint32_t UNFOCUS_BTN_COLOR_LIGHT = 0xfff5f5f5;

constexpr uint32_t ICON_PRIMARY_LIGHT = 0xE5000000;
constexpr uint32_t ICON_PRIMARY_DARK = 0xDBFFFFFF;
constexpr uint32_t ICON_ON_PRIMARY_LIGHT = 0xFFFFFF;
constexpr uint32_t ICON_ON_PRIMARY_DARK = 0xE5E5E5;
constexpr uint32_t INTERACTIVE_HOVER_LIGHT = 0x0C000000;
constexpr uint32_t INTERACTIVE_HOVER_DARK = 0x19FFFFFF;
constexpr uint32_t INTERACTIVE_CLICK_LIGHT = 0x19000000;
constexpr uint32_t INTERACTIVE_CLICK_DARK = 0x26FFFFFF;
constexpr uint32_t WARNING_LIGHT = 0xE84026;
constexpr uint32_t WARNING_DARK = 0xD94838;
constexpr uint32_t CLOSE_BTN_DARK = 0xE6A5A5;

enum ControlBtnColorType {
    NORMAL,
    NORMAL_FILL,
    HOVER,
    HOVER_FILL,
    PRESS,
    PRESS_FILL,
    FOCUS,
    FOCUS_FILL,
    UNFOCUS,
    UNFOCUS_FILL,
};
class ContainerModalTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ContainerModalTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ContainerModalTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ContainerModalTheme> theme = AceType::Claim(new ContainerModalTheme());
            if (!themeConstants) {
                return theme;
            }
            theme->themeConstants_ = themeConstants;
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ContainerModalTheme>& theme) const
        {
            auto themeStyle = themeConstants->GetThemeStyle();
            if (!themeStyle) {
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_CONTAINER_MODAL, nullptr);
            if (!pattern) {
                return;
            }
            theme->backgroundColor_ = pattern->GetAttr<Color>("container_modal_background", Color());
            theme->backgroundUnfocusColor_ = pattern->GetAttr<Color>("container_modal_unfocus_background", Color());
            theme->titleTextColor_ = pattern->GetAttr<Color>("ohos_id_color_primary", Color());

            auto resAdapter = themeConstants->GetResourceAdapter();
            CHECK_NULL_VOID(resAdapter);
            auto isLightMode = resAdapter->GetResourceColorMode() == ColorMode::LIGHT;

            theme->iconPrimaryColor_ = pattern->GetAttr<Color>(
                "icon_primary",
                isLightMode ? Color(ICON_PRIMARY_LIGHT) : Color(ICON_PRIMARY_DARK)
            );
            theme->iconOnPrimaryColor_ = pattern->GetAttr<Color>(
                "icon_on_primary",
                isLightMode ? Color(ICON_ON_PRIMARY_LIGHT) : Color(ICON_ON_PRIMARY_DARK)
            );
            theme->interactiveHoverColor_ = pattern->GetAttr<Color>(
                "interactive_hover",
                isLightMode ? Color(INTERACTIVE_HOVER_LIGHT) : Color(INTERACTIVE_HOVER_DARK)
            );
            theme->interactiveClickColor_ = pattern->GetAttr<Color>(
                "interactive_click",
                isLightMode ? Color(INTERACTIVE_CLICK_LIGHT) : Color(INTERACTIVE_CLICK_DARK)
            );
            theme->warningColor_ = pattern->GetAttr<Color>(
                "warning",
                isLightMode ? Color(WARNING_LIGHT) : Color(WARNING_DARK)
            );

            theme->windowScreenLeft_ = pattern->GetAttr<std::string>("window_left_screen", "");
            theme->windowScreenRight_ = pattern->GetAttr<std::string>("window_right_screen", "");
        }
    };
    ContainerModalTheme() = default;
    ~ContainerModalTheme() override = default;

    Color GetBackGroundColor(bool isFocus)
    {
        Color backGroundColor = isFocus ? backgroundColor_ : backgroundUnfocusColor_;
        return backGroundColor;
    }

    Color GetControlBtnColor(bool isCloseBtn, ControlBtnColorType type)
    {
        auto isLightMode = IsLightMode();
        auto normalBtnOpacity = isLightMode ? 0.1f : 0.2f;
        auto normalBtnColor = iconPrimaryColor_;
        auto closeBtnOpacity = isLightMode ? 0.1f : 0.3f;
        auto closeBtnColor = isLightMode ? warningColor_ : Color(CLOSE_BTN_DARK);
        Color btnColor;
        switch (type) {
            case ControlBtnColorType::NORMAL:
                btnColor = !isCloseBtn
                    ? normalBtnColor.ChangeOpacity(normalBtnOpacity)
                    : closeBtnColor.ChangeOpacity(closeBtnOpacity);
                break;
            case ControlBtnColorType::NORMAL_FILL:
                btnColor = !isCloseBtn
                    ? iconPrimaryColor_.ChangeOpacity(1.0f) : warningColor_.ChangeOpacity(1.0f);
                break;
            case ControlBtnColorType::HOVER:
                btnColor = !isCloseBtn
                    ? normalBtnColor.ChangeOpacity(normalBtnOpacity).BlendColor(interactiveHoverColor_)
                    : warningColor_.ChangeOpacity(1.0f);
                break;
            case ControlBtnColorType::HOVER_FILL:
                btnColor = !isCloseBtn
                    ? iconPrimaryColor_.ChangeOpacity(1.0f) : iconOnPrimaryColor_.ChangeOpacity(1.0f);
                break;
            case ControlBtnColorType::PRESS:
                btnColor = !isCloseBtn
                    ? normalBtnColor.ChangeOpacity(normalBtnOpacity).BlendColor(interactiveClickColor_)
                    : warningColor_.ChangeOpacity(1.0f).BlendColor(interactiveClickColor_);
                break;
            case ControlBtnColorType::PRESS_FILL:
                btnColor = !isCloseBtn
                    ? iconPrimaryColor_.ChangeOpacity(1.0f) : iconOnPrimaryColor_.ChangeOpacity(1.0f);
                break;
            case ControlBtnColorType::UNFOCUS:
                btnColor = !isCloseBtn
                    ? normalBtnColor.ChangeOpacity(normalBtnOpacity * 0.4f)
                    : closeBtnColor.ChangeOpacity(closeBtnOpacity * 0.4f);
                break;
            case ControlBtnColorType::UNFOCUS_FILL:
                btnColor = !isCloseBtn
                    ? iconPrimaryColor_.ChangeOpacity(0.4f) : warningColor_.ChangeOpacity(0.4f);
                break;
            default:
                break;
        }
        return btnColor;
    }

    bool IsLightMode()
    {
        CHECK_NULL_RETURN(themeConstants_, true);
        auto resAdapter = themeConstants_->GetResourceAdapter();
        CHECK_NULL_RETURN(resAdapter, true);
        return resAdapter->GetResourceColorMode() == ColorMode::LIGHT;
    }

    std::string GetWindowScreen(bool isLeftSplit)
    {
        return isLeftSplit ? windowScreenLeft_ : windowScreenRight_;
    }

private:
    Color backgroundColor_;
    Color backgroundUnfocusColor_;
    Color titleTextColor_;

    Color iconPrimaryColor_;
    Color iconOnPrimaryColor_;
    Color interactiveHoverColor_;
    Color interactiveClickColor_;
    Color warningColor_;
    RefPtr<ThemeConstants> themeConstants_ = nullptr;

    std::string windowScreenLeft_;
    std::string windowScreenRight_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUTTON_BUTTON_THEME_H