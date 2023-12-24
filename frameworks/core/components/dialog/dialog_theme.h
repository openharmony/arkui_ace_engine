/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DIALOG_DIALOG_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DIALOG_DIALOG_THEME_H

#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/radius.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {
namespace {
constexpr double PRIMARY_RGBA_OPACITY = 0.9f;
constexpr double SECONDARY_RGBA_OPACITY = 0.6f;
constexpr int DEFAULT_ANIMATION_DURATION_OUT = 220;
constexpr int DEFAULT_ANIMATION_DURATION_IN = 250;
} // namespace
/**
 * DialogTheme defines color and styles of DialogComponent. DialogTheme should be built
 * using DialogTheme::Builder.
 */
class DialogTheme : public virtual Theme {
    DECLARE_ACE_TYPE(DialogTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<DialogTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<DialogTheme> theme = AceType::Claim(new DialogTheme());
            if (!themeConstants) {
                return theme;
            }
            // init theme from global data
            ParseNewPattern(themeConstants->GetThemeStyle(), theme);
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<DialogTheme>& theme) const
        {
            if (!themeStyle) {
                LOGI("dialog theme style is null");
                return;
            }
            auto dialogPattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_DIALOG, nullptr);
            if (!dialogPattern) {
                return;
            }
            theme->backgroundColor_ = dialogPattern->GetAttr<Color>(PATTERN_BG_COLOR, Color(0xd9ffffff));
            theme->titleTextStyle_.SetTextColor(dialogPattern->GetAttr<Color>("title_text_color", Color::BLACK));
            theme->titleTextStyle_.SetFontSize(dialogPattern->GetAttr<Dimension>("title_text_font_size", 20.0_fp));
            theme->titleTextStyle_.SetFontWeight(FontWeight::MEDIUM);
            theme->subtitleTextStyle_.SetTextColor(dialogPattern->GetAttr<Color>("subtitle_text_color", Color::BLACK));
            theme->subtitleTextStyle_.SetFontSize(
                dialogPattern->GetAttr<Dimension>("subtitle_text_font_size", 14.0_fp));
            theme->contentTextStyle_.SetTextColor(dialogPattern->GetAttr<Color>("content_text_color", Color::BLACK));
            theme->contentTextStyle_.SetFontSize(dialogPattern->GetAttr<Dimension>("content_text_font_size", 16.0_fp));
            theme->buttonBackgroundColor_ = dialogPattern->GetAttr<Color>("button_bg_color", Color::BLACK);
            theme->radius_ = Radius(dialogPattern->GetAttr<Dimension>("radius", 24.0_vp));
            theme->dividerLength_ = dialogPattern->GetAttr<Dimension>(DIALOG_DIVIDER_LENGTH, 24.0_vp);
            theme->dividerBetweenButtonWidth_ =
                dialogPattern->GetAttr<Dimension>(DIALOG_DIVIDER_BETWEEN_BUTTON_WIDTH, 2.0_px);
            theme->dividerColor_ = dialogPattern->GetAttr<Color>("divider_color", Color(0x33000000));

            auto defaultPadding = dialogPattern->GetAttr<Dimension>(DIALOG_CONTENT_TOP_PADDING, 24.0_vp);
            theme->contentAdjustPadding_ = Edge(defaultPadding, defaultPadding, defaultPadding, 0.0_vp);
            theme->defaultPaddingBottomFixed_ =
                dialogPattern->GetAttr<Dimension>("default_padding_bottom_fixed", 24.0_vp);
            theme->defaultDialogMarginBottom_ =
                dialogPattern->GetAttr<Dimension>("default_dialog_margin_bottom", 16.0_vp);
            theme->buttonHighlightBgColor_ =
                dialogPattern->GetAttr<Color>("button_bg_highlight_color", Color(0xff007dff));
            theme->buttonHighlightFontColor_ = dialogPattern->GetAttr<Color>("first_button_text_color", Color::WHITE);
            theme->buttonDefaultBgColor_ = dialogPattern->GetAttr<Color>("button_default_bg_color", Color::TRANSPARENT);
            theme->buttonDefaultFontColor_ =
                dialogPattern->GetAttr<Color>("button_default_font_color", Color(0xff007dff));
            theme->buttonPaddingBottom_ = dialogPattern->GetAttr<Dimension>("button_padding_bottom", 16.0_vp);
            theme->singleButtonPaddingStart_ =
                dialogPattern->GetAttr<Dimension>("single_button_padding_start", 16.0_vp);
            theme->singleButtonPaddingEnd_ = dialogPattern->GetAttr<Dimension>("single_button_padding_end", 16.0_vp);
            theme->mutiButtonPaddingStart_ = dialogPattern->GetAttr<Dimension>("muti_button_padding_start", 16.0_vp);
            theme->mutiButtonPaddingEnd_ = dialogPattern->GetAttr<Dimension>("muti_button_padding_end", 16.0_vp);
            theme->mutiButtonPaddingHorizontal_ =
                dialogPattern->GetAttr<Dimension>("muti_button_padding_horizontal", 8.0_vp);
            theme->mutiButtonPaddingVertical_ =
                dialogPattern->GetAttr<Dimension>("muti_button_padding_vertical", 4.0_vp);
            theme->multipleDialogDisplay_ = dialogPattern->GetAttr<std::string>("multiple_dialog_display", "stack");
            theme->actionsPadding_ = Edge(dialogPattern->GetAttr<Dimension>("dialog_padding_actions_left", 16.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_actions_top", 8.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_actions_right", 16.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_actions_bottom", 16.0_vp));
            theme->buttonWithContentPadding_ =
                dialogPattern->GetAttr<Dimension>("dialog_buttonwithcontent_padding", 8.0_vp);
            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                theme->expandDisplay_ = false;
            } else {
                std::string expandDisplay = dialogPattern->GetAttr<std::string>("dialog_expand_display", "");
                theme->expandDisplay_ = (expandDisplay == "true");
            }
            if (SystemProperties::GetDeviceType() != DeviceType::CAR) {
                return;
            }
            auto titlePadding = dialogPattern->GetAttr<Dimension>(DIALOG_TITLE_TOP_PADDING, 0.0_vp);
            auto actionsTopPadding = dialogPattern->GetAttr<Dimension>(DIALOG_ACTIONS_TOP_PADDING, 0.0_vp);
            theme->titleAdjustPadding_ = Edge(defaultPadding, titlePadding, defaultPadding, titlePadding);
            theme->titleDefaultPadding_ = Edge(defaultPadding, titlePadding, defaultPadding, titlePadding);
            theme->defaultPadding_ = Edge(defaultPadding, defaultPadding, defaultPadding, defaultPadding);
            theme->adjustPadding_ = Edge(defaultPadding, defaultPadding, defaultPadding, 0.0_vp);
            theme->contentDefaultPadding_ = Edge(defaultPadding, 0.0_vp, defaultPadding, defaultPadding);
            theme->contentAdjustPadding_ = Edge(defaultPadding, 0.0_vp, defaultPadding, 0.0_vp);
            theme->buttonHeight_ = dialogPattern->GetAttr<Dimension>(DIALOG_BUTTON_HEIGHT, 0.0_vp);
            theme->titleMaxLines_ = static_cast<uint32_t>(dialogPattern->GetAttr<int32_t>(DIALOG_TITLE_MAX_LINES, 2));
            theme->buttonSpacingHorizontal_ = actionsTopPadding;
            theme->commonButtonTextColor_ =
                dialogPattern->GetAttr<Color>(DIALOG_COMMON_BUTTON_TEXT_COLOR, Color::WHITE);
            theme->buttonMinTextSize_ = dialogPattern->GetAttr<Dimension>(DIALOG_MIN_BUTTON_TEXT_SIZE, 10.0_vp);
            theme->minButtonWidth_ = dialogPattern->GetAttr<Dimension>(DIALOG_MIN_BUTTON_WIDTH, 104.0_vp);
            theme->maxButtonWidth_ = dialogPattern->GetAttr<Dimension>(DIALOG_MAX_BUTTON_WIDTH, 260.0_vp);
            theme->maskColorEnd_ = dialogPattern->GetAttr<Color>(DIALOG_MASK_COLOR_END, Color::WHITE);
            // pattern config
            theme->titleTextStyle_.SetFontSize(dialogPattern->GetAttr<Dimension>("title_text_font_size", 20.0_vp));
            theme->titleMinFontSize_ = dialogPattern->GetAttr<Dimension>("title_text_font_size_min", 20.0_vp);
            theme->commonButtonBgColor_ = dialogPattern->GetAttr<Color>("common_button_bg_color", Color::GRAY);
            theme->emphasizeButtonBgColor_ = dialogPattern->GetAttr<Color>("first_button_bg_color", Color::BLACK);
            theme->emphasizeButtonTextColor_ = dialogPattern->GetAttr<Color>("first_button_text_color", Color::WHITE);
            theme->buttonTextSize_ = dialogPattern->GetAttr<Dimension>("button_text_font_size", 16.0_vp);
            theme->buttonClickedColor_ = dialogPattern->GetAttr<Color>("button_bg_color_clicked", Color::BLACK);
            theme->contentTextStyle_.SetFontSize(themeStyle->GetAttr<Dimension>("content_text_font_size", 16.0_vp));
            theme->contentMinFontSize_ = themeStyle->GetAttr<Dimension>("content_text_font_size_min", 16.0_vp);
        }

        void ParseNewPattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<DialogTheme>& theme) const
        {
            if (!themeStyle) {
                LOGI("dialog theme style is null");
                return;
            }
            auto dialogPattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_DIALOG, nullptr);
            if (!dialogPattern) {
                return;
            }
            theme->titleMinFontSize_ = dialogPattern->GetAttr<Dimension>("dialog_title_text_font_size_min", 15.0_fp);
            theme->contentMinFontSize_ = dialogPattern->GetAttr<Dimension>("content_text_font_size_min", 16.0_fp);
            auto titleMaxLines = dialogPattern->GetAttr<int>("dialog_title_text_max_lines", 2);
            theme->titleMaxLines_ = titleMaxLines < 0 ? theme->titleMaxLines_ : static_cast<uint32_t>(titleMaxLines);
            theme->defaultPadding_ = Edge(dialogPattern->GetAttr<Dimension>("dialog_padding_left", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_top", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_right", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_bottom", 24.0_vp));
            theme->adjustPadding_ = Edge(dialogPattern->GetAttr<Dimension>("dialog_padding_left_adjust", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_top_adjust", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_right_adjust", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_bottom_adjust", 0.0_vp));
            theme->titleDefaultPadding_ = Edge(dialogPattern->GetAttr<Dimension>("dialog_padding_left", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("button_title_padding_vertical", 14.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_right", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("button_title_padding_vertical", 14.0_vp));
            theme->titleAdjustPadding_ = Edge(dialogPattern->GetAttr<Dimension>("dialog_padding_left_adjust", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("button_title_padding_vertical", 14.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_right_adjust", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_bottom_adjust", 0.0_vp));
            theme->contentDefaultPadding_ = Edge(dialogPattern->GetAttr<Dimension>("dialog_padding_left", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_top", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_right", 24.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_padding_bottom", 24.0_vp));
            theme->buttonPaddingLeft_ = Edge(dialogPattern->GetAttr<Dimension>("dialog_padding_min", 4.0_vp).Value(),
                0.0, 0.0, 0.0, DimensionUnit::VP);
            theme->buttonPaddingRight_ = Edge(0.0, 0.0,
                dialogPattern->GetAttr<Dimension>("dialog_padding_min", 4.0_vp).Value(), 0.0, DimensionUnit::VP);
            theme->buttonPaddingCenter_ = Edge(0.0,
                dialogPattern->GetAttr<Dimension>("dialog_padding_mid", 8.0_vp).Value(),
                0.0, dialogPattern->GetAttr<Dimension>("dialog_padding_mid", 8.0_vp).Value(), DimensionUnit::VP);
            theme->buttonSpacingHorizontal_ = dialogPattern->GetAttr<Dimension>("dialog_button_spacing_vertical",
                8.0_vp);
            theme->buttonSpacingVertical_ = dialogPattern->GetAttr<Dimension>("dialog_button_spacing_vertical",
                8.0_vp);
            theme->buttonClickedColor_ = dialogPattern->GetAttr<Color>("button_color_clicked", Color(0x19182431));
            theme->frameStart_ = dialogPattern->GetAttr<double>("dialog_frame_start", 0.0f);
            theme->frameEnd_ = dialogPattern->GetAttr<double>("dialog_frame_end", 1.0f);
            theme->scaleStart_ = dialogPattern->GetAttr<double>("dialog_scale_start", 0.85f);
            theme->scaleEnd_ = dialogPattern->GetAttr<double>("dialog_scale_end", 1.0f);
            theme->opacityStart_ = dialogPattern->GetAttr<double>("dialog_opacity_start", 0.0f);
            theme->opacityEnd_ = dialogPattern->GetAttr<double>("dialog_opacity_end", 1.0f);
            theme->maskColorStart_ = dialogPattern->GetAttr<Color>("dialog_mask_color_start", Color(0x00000000));
            theme->maskColorEnd_ = dialogPattern->GetAttr<Color>("dialog_mask_color_end", Color(0x33000000));
            theme->animationDurationIn_ = dialogPattern->GetAttr<int>("dialog_animation_duration_in",
                DEFAULT_ANIMATION_DURATION_IN);
            theme->animationDurationOut_ = dialogPattern->GetAttr<int>("dialog_animation_duration_out",
                DEFAULT_ANIMATION_DURATION_OUT);
            theme->translateValue_ = Dimension(dialogPattern->GetAttr<double>("dialog_translate", 500.0f),
                DimensionUnit::PX);
            theme->dividerWidth_ = dialogPattern->GetAttr<Dimension>("dialog_divider_width", 1.0_vp);
            theme->dividerHeight_ = dialogPattern->GetAttr<Dimension>("dialog_divider_height", 24.0_vp);
            theme->dividerPadding_ = Edge(dialogPattern->GetAttr<Dimension>("dialog_divider_padding_horizon", 4.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_divider_padding_vertical", 6.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_divider_padding_horizon", 4.0_vp),
                dialogPattern->GetAttr<Dimension>("dialog_divider_padding_vertical", 6.0_vp));
            theme->marginBottom_ = dialogPattern->GetAttr<Dimension>("dialog_dimension_bottom", 16.0_vp);
            theme->marginLeft_ = dialogPattern->GetAttr<Dimension>("dialog_dimension_start", 12.0_vp);
            theme->marginRight_ = dialogPattern->GetAttr<Dimension>("dialog_dimension_end", 12.0_vp);
        }
    };

    ~DialogTheme() override = default;

    const Radius& GetRadius() const
    {
        return radius_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetCommonButtonBgColor() const
    {
        return commonButtonBgColor_;
    }

    const Color& GetEmphasizeButtonBgColor() const
    {
        return emphasizeButtonBgColor_;
    }

    const TextStyle& GetTitleTextStyle() const
    {
        return titleTextStyle_;
    }

    const TextStyle& GetSubTitleTextStyle() const
    {
        return subtitleTextStyle_;
    }

    const Dimension& GetTitleMinFontSize() const
    {
        return titleMinFontSize_;
    }

    const Dimension& GetContentMinFontSize() const
    {
        return contentMinFontSize_;
    }

    uint32_t GetTitleMaxLines() const
    {
        return titleMaxLines_;
    }

    const TextStyle& GetContentTextStyle() const
    {
        return contentTextStyle_;
    }

    const Edge& GetDefaultPadding() const
    {
        return defaultPadding_;
    }

    const Edge& GetAdjustPadding() const
    {
        return adjustPadding_;
    }

    const Edge& GetTitleDefaultPadding() const
    {
        return titleDefaultPadding_;
    }

    const Edge& GetTitleAdjustPadding() const
    {
        return titleAdjustPadding_;
    }

    const Edge& GetContentDefaultPadding() const
    {
        return contentDefaultPadding_;
    }

    const Edge& GetContentAdjustPadding() const
    {
        return contentAdjustPadding_;
    }

    const Edge& GetActionsPadding() const
    {
        return actionsPadding_;
    }

    const Edge& GetButtonPaddingLeft() const
    {
        return buttonPaddingLeft_;
    }

    const Edge& GetButtonPaddingRight() const
    {
        return buttonPaddingRight_;
    }

    const Edge& GetButtonPaddingCenter() const
    {
        return buttonPaddingCenter_;
    }

    const Dimension& GetButtonPaddingBottom() const
    {
        return buttonPaddingBottom_;
    }

    const Dimension& GetSingleButtonPaddingStart() const
    {
        return singleButtonPaddingStart_;
    }

    const Dimension& GetSingleButtonPaddingEnd() const
    {
        return singleButtonPaddingEnd_;
    }

    const Dimension& GetMutiButtonPaddingStart() const
    {
        return mutiButtonPaddingStart_;
    }

    const Dimension& GetMutiButtonPaddingEnd() const
    {
        return mutiButtonPaddingEnd_;
    }

    const Dimension& GetMutiButtonPaddingHorizontal() const
    {
        return mutiButtonPaddingHorizontal_;
    }

    const Dimension& GetMutiButtonPaddingVertical() const
    {
        return mutiButtonPaddingVertical_;
    }

    const Dimension& GetButtonSpacingHorizontal() const
    {
        return buttonSpacingHorizontal_;
    }

    const Dimension& GetButtonSpacingVertical() const
    {
        return buttonSpacingVertical_;
    }

    const Dimension& GetDividerLength() const
    {
        return dividerLength_;
    }

    const Dimension& GetDividerBetweenButtonWidth_() const
    {
        return dividerBetweenButtonWidth_;
    }

    const Color& GetButtonBackgroundColor() const
    {
        return buttonBackgroundColor_;
    }

    const Color& GetButtonClickedColor() const
    {
        return buttonClickedColor_;
    }

    const Color& GetButtonHighlightBgColor() const
    {
        return buttonHighlightBgColor_;
    }

    const Color& GetButtonHighlightFontColor() const
    {
        return buttonHighlightFontColor_;
    }

    const Color& GetButtonDefaultBgColor() const
    {
        return buttonDefaultBgColor_;
    }

    const Color& GetButtonDefaultFontColor() const
    {
        return buttonDefaultFontColor_;
    }

    double GetFrameStart() const
    {
        return frameStart_;
    }

    double GetFrameEnd() const
    {
        return frameEnd_;
    }

    double GetScaleStart() const
    {
        return scaleStart_;
    }

    double GetScaleEnd() const
    {
        return scaleEnd_;
    }

    double GetOpacityStart() const
    {
        return opacityStart_;
    }

    double GetOpacityEnd() const
    {
        return opacityEnd_;
    }

    const Dimension& GetTranslateValue() const
    {
        return translateValue_;
    }

    const Color& GetMaskColorStart() const
    {
        return maskColorStart_;
    }

    const Color& GetMaskColorEnd() const
    {
        return maskColorEnd_;
    }

    const Color& GetCommonButtonTextColor() const
    {
        return commonButtonTextColor_;
    }

    const Color& GetEmphasizeButtonTextColor() const
    {
        return emphasizeButtonTextColor_;
    }

    int32_t GetOpacityAnimationDurIn() const
    {
        return opacityAnimationDurIn_;
    }

    int32_t GetAnimationDurationIn() const
    {
        return animationDurationIn_;
    }

    int32_t GetAnimationDurationOut() const
    {
        return animationDurationOut_;
    }

    const Color& GetDividerColor()
    {
        return dividerColor_;
    }

    const Dimension& GetDividerWidth()
    {
        return dividerWidth_;
    }

    const Dimension& GetDividerHeight()
    {
        return dividerHeight_;
    }

    const Edge& GetDividerPadding()
    {
        return dividerPadding_;
    }

    const Dimension& GetMarginBottom() const
    {
        return marginBottom_;
    }

    const Dimension& GetMarginLeft() const
    {
        return marginLeft_;
    }

    const Dimension& GetMarginRight() const
    {
        return marginRight_;
    }

    const Dimension& GetButtonHeight() const
    {
        return buttonHeight_;
    }

    const Dimension& GetButtonTextSize() const
    {
        return buttonTextSize_;
    }

    const Dimension& GetMinButtonTextSize() const
    {
        return buttonMinTextSize_;
    }

    const Dimension& GetDefaultPaddingBottomFixed()
    {
        return defaultPaddingBottomFixed_;
    }

    const Dimension& GetDefaultDialogMarginBottom()
    {
        return defaultDialogMarginBottom_;
    }
    const std::string& GetMultipleDialogDisplay()
    {
        return multipleDialogDisplay_;
    }

    bool GetExpandDisplay() const
    {
        return expandDisplay_;
    }

    const Dimension& GetButtonWithContentPadding() const
    {
        return buttonWithContentPadding_;
    }
protected:
    DialogTheme() = default;

private:
    Radius radius_;
    Color backgroundColor_;
    TextStyle titleTextStyle_;
    TextStyle subtitleTextStyle_;
    TextStyle contentTextStyle_;
    Dimension titleMinFontSize_;
    Dimension contentMinFontSize_;
    uint32_t titleMaxLines_ = 1;
    Edge defaultPadding_;
    Edge adjustPadding_;
    Edge titleDefaultPadding_;
    Edge titleAdjustPadding_;
    Edge contentDefaultPadding_;
    Edge contentAdjustPadding_;
    Edge actionsPadding_;
    Edge buttonPaddingLeft_;
    Edge buttonPaddingRight_;
    Edge buttonPaddingCenter_;
    Dimension buttonSpacingHorizontal_;
    Dimension buttonSpacingVertical_;
    Dimension dividerLength_;
    Dimension dividerBetweenButtonWidth_;
    Color buttonBackgroundColor_;
    Color buttonClickedColor_;
    Color buttonHighlightBgColor_;
    Color buttonHighlightFontColor_;
    Color buttonDefaultBgColor_;
    Color buttonDefaultFontColor_;
    Color emphasizeButtonTextColor_;
    Dimension translateValue_;
    double frameStart_ = 0.0;
    double frameEnd_ = 1.0;
    double scaleStart_ = 0.0;
    double scaleEnd_ = 1.0;
    double opacityStart_ = 0.0;
    double opacityEnd_ = 1.0;
    int32_t animationDurationIn_ = 250;
    int32_t opacityAnimationDurIn_ = 150;
    int32_t animationDurationOut_ = 250;
    Color maskColorStart_;
    Color maskColorEnd_;
    Color dividerColor_;
    Color commonButtonBgColor_;
    Color commonButtonTextColor_;
    Color emphasizeButtonBgColor_;
    Dimension dividerWidth_;
    Dimension dividerHeight_;
    Edge dividerPadding_;
    Dimension marginLeft_;
    Dimension marginRight_;
    Dimension marginBottom_;
    Dimension buttonHeight_;
    Dimension buttonTextSize_;
    Dimension buttonMinTextSize_;
    Dimension minButtonWidth_;
    Dimension maxButtonWidth_;
    Dimension defaultPaddingBottomFixed_;
    Dimension defaultDialogMarginBottom_;
    Dimension buttonPaddingBottom_;
    Dimension singleButtonPaddingStart_;
    Dimension singleButtonPaddingEnd_;
    Dimension mutiButtonPaddingStart_;
    Dimension mutiButtonPaddingEnd_;
    Dimension mutiButtonPaddingHorizontal_;
    Dimension mutiButtonPaddingVertical_;
    std::string multipleDialogDisplay_;
    bool expandDisplay_ = false;
    Dimension buttonWithContentPadding_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DIALOG_DIALOG_THEME_H
