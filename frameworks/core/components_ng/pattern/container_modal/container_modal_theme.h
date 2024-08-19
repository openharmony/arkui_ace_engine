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
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<ContainerModalTheme>& theme) const
        {
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
            theme->colorPrimary_ = pattern->GetAttr<Color>("ohos_id_color_primary", Color());
            theme->colorWarning_ = pattern->GetAttr<Color>("ohos_id_color_warning", Color());
            theme->colorPrimaryContrary_ = pattern->GetAttr<Color>("ohos_id_color_primary_contary", Color());
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
        auto isDarkMode = SystemProperties::GetColorMode() == ColorMode::DARK;

        Color btnColor;
        switch (type) {
            case ControlBtnColorType::NORMAL:
                if (isDarkMode) {
                    btnColor = isCloseBtn ? Color(DARK_MODE_NORMAL_CLOSE_BTN_COLOR) : colorPrimary_.ChangeOpacity(0.2f);
                } else {
                    btnColor = isCloseBtn ? colorWarning_.ChangeOpacity(0.1f) : colorPrimary_.ChangeOpacity(0.1f);
                }
                break;
            case ControlBtnColorType::NORMAL_FILL:
                btnColor = isCloseBtn ? colorWarning_.ChangeOpacity(1.0f)
                                      : colorPrimary_.ChangeOpacity(isDarkMode ? 1.0f : 0.9f);
                break;
            case ControlBtnColorType::HOVER:
                btnColor = isCloseBtn
                               ? colorWarning_.ChangeOpacity(1.0f)
                               : (isDarkMode ? Color(HOVER_CLOSE_BTN_COLOR_DARK) : Color(HOVER_CLOSE_BTN_COLOR_LIGHT));
                break;
            case ControlBtnColorType::HOVER_FILL:
                btnColor = isCloseBtn ? (isDarkMode ? Color(HOVER_FILL_CLOSE_BTN_COLOR_DARK)
                                                    : Color(HOVER_FILL_CLOSE_BTN_COLOR_LIGHT))
                                      : (isDarkMode ? Color(HOVER_FILL_CLOSE_BTN_COLOR_LIGHT).ChangeOpacity(0.86f)
                                                    : Color(HOVER_FILL_CLOSE_BTN_COLOR_LIGHT).ChangeOpacity(0.9f));
                break;
            case ControlBtnColorType::PRESS:
                btnColor =
                    isCloseBtn
                        ? (isDarkMode ? Color(PRESS_CLOSE_BTN_COLOR_DARK) : Color(PRESS_CLOSE_BTN_COLOR_LIGHT))
                        : (isDarkMode ? Color(PRESS_NORMAL_BTN_COLOR_DARK) : Color(PRESS_NORMAL_BTN_COLOR_LIGHT));
                break;
            case ControlBtnColorType::PRESS_FILL:
                btnColor = isCloseBtn ? colorPrimaryContrary_.ChangeOpacity(1.0f) : colorPrimary_.ChangeOpacity(1.0f);
                break;
            case ControlBtnColorType::UNFOCUS:
                btnColor = isCloseBtn ? (isDarkMode ? Color(UNFOCUS_CLOSE_BTN_COLOR_DARK)
                                                    : Color(UNFOCUS_CLOSE_BTN_COLOR_LIGHT))
                                      : (isDarkMode ? Color(UNFOCUS_BTN_COLOR_DARK) : Color(UNFOCUS_BTN_COLOR_LIGHT));
                break;
            case ControlBtnColorType::UNFOCUS_FILL:
                btnColor = GetControlBtnColor(isCloseBtn, ControlBtnColorType::NORMAL_FILL).ChangeOpacity(0.4f);
                break;
            default:
                break;
        }
        return btnColor;
    }

private:
    Color backgroundColor_;
    Color backgroundUnfocusColor_;
    Color titleTextColor_;

    Color colorPrimary_;
    Color colorWarning_;
    Color colorPrimaryContrary_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUTTON_BUTTON_THEME_H