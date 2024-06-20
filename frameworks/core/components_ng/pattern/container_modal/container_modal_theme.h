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

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"

namespace OHOS::Ace::NG {


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
            theme->normalBtnBackgroundColor_ = pattern->GetAttr<Color>("ohos_id_normalbtn_bg", Color());
            theme->normalBtnImageFillColor_ = pattern->GetAttr<Color>("ohos_id_color_primary", Color());
            theme->normalBtnPressedBackgroundColor_ = pattern->GetAttr<Color>("ohos_id_normalbtn_press_bg", Color());
            theme->normalBtnHoverBackgroundColor_ = pattern->GetAttr<Color>("ohos_id_normalbtn_hover_bg", Color());
            theme->normalBtnImageHoverFillColor_ = pattern->GetAttr<Color>("ohos_id_color_primary", Color());
            theme->closeBtnBackgroundColor_  = pattern->GetAttr<Color>("ohos_id_closebtn_focus_bg", Color());
            theme->closeBtnImageFillColor_ = pattern->GetAttr<Color>("ohos_id_closebtn_color_warning", Color());
            theme->closeBtnPressBackGroundColor_ = pattern->GetAttr<Color>("ohos_id_closebtn_press_bg", Color());
            theme->closeBtnImagePressFillColor_ = pattern->GetAttr<Color>("ohos_id_color_foreground_contrary", Color());
            theme->closeBtnHoverBackGroundColor_  = pattern->GetAttr<Color>("ohos_id_closebtn_color_warning", Color());
            theme->closeBtnImageHoverFillColor_ = pattern->GetAttr<Color>("ohos_id_color_foreground_contrary", Color());
            theme->normalBtnUnfocusBackGroundColor_ = pattern->GetAttr<Color>("ohos_id_normalbtn_unfocus_bg", Color());
            theme->closeBtnUnfocusBackGroundColor_ = pattern->GetAttr<Color>("ohos_id_closebtn_unfocus_bg", Color());
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
        Color btnColor;
        switch (type) {
            case ControlBtnColorType::NORMAL:
                btnColor = !isCloseBtn ? normalBtnBackgroundColor_.ChangeOpacity(1.0f)
                                       : closeBtnBackgroundColor_.ChangeOpacity(1.0f);
                break;
            case ControlBtnColorType::NORMAL_FILL:
                btnColor = !isCloseBtn ? normalBtnImageFillColor_.ChangeOpacity(1.0f)
                                       : closeBtnImageFillColor_.ChangeOpacity(1.0f);
                break;
            case ControlBtnColorType::HOVER:
                btnColor = !isCloseBtn ? normalBtnHoverBackgroundColor_.ChangeOpacity(0.05f)
                                       : closeBtnHoverBackGroundColor_.ChangeOpacity(1.0f);
                break;
            case ControlBtnColorType::HOVER_FILL:
                btnColor = !isCloseBtn ? normalBtnImageHoverFillColor_.ChangeOpacity(1.0f)
                                       : closeBtnImageHoverFillColor_.ChangeOpacity(1.0f);
                break;
            case ControlBtnColorType::PRESS:
                btnColor = !isCloseBtn ? normalBtnPressedBackgroundColor_.ChangeOpacity(1.0f)
                                       : closeBtnPressBackGroundColor_.ChangeOpacity(1.0f);
                break;
            case ControlBtnColorType::PRESS_FILL:
                btnColor = !isCloseBtn ? normalBtnImageFillColor_.ChangeOpacity(1.0f)
                                       : closeBtnImagePressFillColor_.ChangeOpacity(1.0f);
                break;
            case ControlBtnColorType::UNFOCUS:
                btnColor = !isCloseBtn ? normalBtnUnfocusBackGroundColor_.ChangeOpacity(0.6f)
                                       : closeBtnUnfocusBackGroundColor_.ChangeOpacity(0.6f);
                break;
            case ControlBtnColorType::UNFOCUS_FILL:
                btnColor = !isCloseBtn ? normalBtnImageFillColor_.ChangeOpacity(0.4f)
                                       : closeBtnImageFillColor_.ChangeOpacity(0.4f);
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
    Color normalBtnBackgroundColor_;
    Color normalBtnImageFillColor_;
    Color normalBtnPressedBackgroundColor_;
    Color normalBtnHoverBackgroundColor_;
    Color closeBtnBackgroundColor_;
    Color closeBtnImageFillColor_;
    Color closeBtnPressBackGroundColor_;
    Color closeBtnImagePressFillColor_;
    Color closeBtnHoverBackGroundColor_;
    Color closeBtnImageHoverFillColor_;
    Color normalBtnUnfocusBackGroundColor_;
    Color closeBtnUnfocusBackGroundColor_;
    Color normalBtnImageHoverFillColor_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUTTON_BUTTON_THEME_H