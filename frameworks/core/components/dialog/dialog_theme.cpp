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

#include "core/components/dialog/dialog_theme.h"

namespace OHOS::Ace {
void DialogTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<DialogTheme>& theme) const
{
    auto themeStyle = themeConstants->GetThemeStyle();
    if (!themeStyle) {
        return;
    }
    RefPtr<ThemeStyle> dialogPattern = themeConstants->GetPatternByName(THEME_PATTERN_DIALOG);
    if (!dialogPattern) {
        return;
    }
    theme->titleTextStyle_.SetTextColor(dialogPattern->GetAttr<Color>("title_text_color", Color::BLACK));
    theme->titleTextStyle_.SetFontSize(dialogPattern->GetAttr<Dimension>("title_text_font_size", 20.0_fp));
    theme->titleTextStyle_.SetFontWeight(FontWeight::MEDIUM);
    theme->subtitleTextStyle_.SetTextColor(dialogPattern->GetAttr<Color>("subtitle_text_color", Color::BLACK));

    theme->subtitleTextStyle_.SetFontSize(dialogPattern->GetAttr<Dimension>("subtitle_text_font_size", 14.0_fp));
    theme->contentTextStyle_.SetTextColor(dialogPattern->GetAttr<Color>("content_text_color", Color::BLACK));
    theme->contentTextStyle_.SetFontSize(dialogPattern->GetAttr<Dimension>("content_text_font_size", 16.0_fp));
    theme->buttonBackgroundColor_ = dialogPattern->GetAttr<Color>("button_bg_color", Color::BLACK);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        theme->radius_ = Radius(dialogPattern->GetAttr<Dimension>("dialog_container_radius", 32.0_vp));
        theme->backgroundColor_ = dialogPattern->GetAttr<Color>("bg_color_version_twelve", Color(0xffffff));
    } else {
        theme->radius_ = Radius(dialogPattern->GetAttr<Dimension>("radius", 24.0_vp));
        theme->backgroundColor_ = dialogPattern->GetAttr<Color>(PATTERN_BG_COLOR, Color(0xd9ffffff));
    }
    theme->dividerLength_ = dialogPattern->GetAttr<Dimension>(DIALOG_DIVIDER_LENGTH, 24.0_vp);
    theme->dividerBetweenButtonWidth_ = dialogPattern->GetAttr<Dimension>(DIALOG_DIVIDER_BETWEEN_BUTTON_WIDTH, 2.0_px);
    theme->dividerColor_ = dialogPattern->GetAttr<Color>("divider_color", Color(0x33000000));
    auto defaultPadding = dialogPattern->GetAttr<Dimension>(DIALOG_CONTENT_TOP_PADDING, 24.0_vp);
    theme->contentAdjustPadding_ = Edge(defaultPadding, defaultPadding, defaultPadding, 0.0_vp);
    theme->defaultPaddingBottomFixed_ = dialogPattern->GetAttr<Dimension>("default_padding_bottom_fixed", 24.0_vp);
    theme->defaultDialogMarginBottom_ = dialogPattern->GetAttr<Dimension>("default_dialog_margin_bottom", 16.0_vp);
    theme->buttonHighlightBgColor_ = dialogPattern->GetAttr<Color>("button_bg_highlight_color", Color(0xff007dff));
    theme->buttonHighlightFontColor_ = dialogPattern->GetAttr<Color>("first_button_text_color", Color::WHITE);
    theme->buttonDefaultBgColor_ = dialogPattern->GetAttr<Color>("button_default_bg_color", Color::TRANSPARENT);
    theme->buttonDefaultFontColor_ = dialogPattern->GetAttr<Color>("button_default_font_color", Color(0xff007dff));
    theme->buttonPaddingBottom_ = dialogPattern->GetAttr<Dimension>("button_padding_bottom", 16.0_vp);
    theme->singleButtonPaddingStart_ = dialogPattern->GetAttr<Dimension>("single_button_padding_start", 16.0_vp);
    theme->singleButtonPaddingEnd_ = dialogPattern->GetAttr<Dimension>("single_button_padding_end", 16.0_vp);
    theme->mutiButtonPaddingStart_ = dialogPattern->GetAttr<Dimension>("muti_button_padding_start", 16.0_vp);
    theme->mutiButtonPaddingEnd_ = dialogPattern->GetAttr<Dimension>("muti_button_padding_end", 16.0_vp);
    theme->mutiButtonPaddingHorizontal_ = dialogPattern->GetAttr<Dimension>("muti_button_padding_horizontal", 8.0_vp);
    theme->mutiButtonPaddingVertical_ = dialogPattern->GetAttr<Dimension>("muti_button_padding_vertical", 4.0_vp);
    theme->multipleDialogDisplay_ = dialogPattern->GetAttr<std::string>("multiple_dialog_display", "stack");
    theme->actionsPadding_ = Edge(dialogPattern->GetAttr<Dimension>("dialog_padding_actions_left", 16.0_vp),
        dialogPattern->GetAttr<Dimension>("dialog_padding_actions_top", 8.0_vp),
        dialogPattern->GetAttr<Dimension>("dialog_padding_actions_right", 16.0_vp),
        dialogPattern->GetAttr<Dimension>("dialog_padding_actions_bottom", 16.0_vp));
    theme->buttonWithContentPadding_ = dialogPattern->GetAttr<Dimension>("dialog_buttonwithcontent_padding", 8.0_vp);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        theme->expandDisplay_ = false;
    } else {
        std::string expandDisplay = dialogPattern->GetAttr<std::string>("dialog_expand_display", "");
        theme->expandDisplay_ = (expandDisplay == "true");
    }
    theme->titleMaxFontScale_ = dialogPattern->GetAttr<double>("dialog_title_max_scale_aging", 2.0f);
    theme->dialogDefaultScale_ = dialogPattern->GetAttr<double>("dialog_default_scale_aging", 1.0f);
    theme->contentMaxFontScale_ = dialogPattern->GetAttr<double>("dialog_content_max_scale_aging", 3.2f);
    theme->contentLandscapeMaxFontScale_ =
        dialogPattern->GetAttr<double>("dialog_content_landscape_max_scale_aging", 2.0f);
    theme->buttonMaxFontScale_ = dialogPattern->GetAttr<double>("dialog_button_max_scale_aging", 3.2f);
    theme->buttonLandscapeMaxFontScale_ =
        dialogPattern->GetAttr<double>("dialog_button_landscape_max_scale_aging", 2.0f);
    theme->minFontScaleForElderly_ = dialogPattern->GetAttr<double>("dialog_min_scale_aging", 1.75f);
    theme->dialogLandscapeHeightBoundary_ =
        dialogPattern->GetAttr<Dimension>("dialog_landscape_boundary_aging", 640.0_vp);
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
    theme->titleMaxLines_ =
        static_cast<uint32_t>(dialogPattern->GetAttr<int32_t>(DIALOG_TITLE_MAX_LINES, DIALOG_TITLE_MAX_LINES_VALUE));
    theme->buttonSpacingHorizontal_ = actionsTopPadding;
    theme->commonButtonTextColor_ = dialogPattern->GetAttr<Color>(DIALOG_COMMON_BUTTON_TEXT_COLOR, Color::WHITE);
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

void DialogTheme::Builder::ParseNewPattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<DialogTheme>& theme) const
{
    RefPtr<ThemeStyle> dialogPattern = themeConstants->GetPatternByName(THEME_PATTERN_DIALOG);
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
    theme->buttonPaddingLeft_ =
        Edge(dialogPattern->GetAttr<Dimension>("dialog_padding_min", 4.0_vp).Value(), 0.0, 0.0, 0.0, DimensionUnit::VP);
    theme->buttonPaddingRight_ =
        Edge(0.0, 0.0, dialogPattern->GetAttr<Dimension>("dialog_padding_min", 4.0_vp).Value(), 0.0, DimensionUnit::VP);
    theme->buttonPaddingCenter_ = Edge(0.0, dialogPattern->GetAttr<Dimension>("dialog_padding_mid", 8.0_vp).Value(),
        0.0, dialogPattern->GetAttr<Dimension>("dialog_padding_mid", 8.0_vp).Value(), DimensionUnit::VP);
    theme->buttonSpacingHorizontal_ = dialogPattern->GetAttr<Dimension>("dialog_button_spacing_vertical", 8.0_vp);
    theme->buttonSpacingVertical_ = dialogPattern->GetAttr<Dimension>("dialog_button_spacing_vertical", 8.0_vp);
    theme->buttonClickedColor_ = dialogPattern->GetAttr<Color>("button_color_clicked", Color(0x19182431));
    theme->frameStart_ = dialogPattern->GetAttr<double>("dialog_frame_start", 0.0f);
    theme->frameEnd_ = dialogPattern->GetAttr<double>("dialog_frame_end", 1.0f);
    theme->scaleStart_ = dialogPattern->GetAttr<double>("dialog_scale_start", 0.85f);
    theme->scaleEnd_ = dialogPattern->GetAttr<double>("dialog_scale_end", 1.0f);
    theme->opacityStart_ = dialogPattern->GetAttr<double>("dialog_opacity_start", 0.0f);
    theme->opacityEnd_ = dialogPattern->GetAttr<double>("dialog_opacity_end", 1.0f);
    theme->maskColorStart_ = dialogPattern->GetAttr<Color>("dialog_mask_color_start", Color(0x00000000));
    theme->maskColorEnd_ = dialogPattern->GetAttr<Color>("dialog_mask_color_end", Color(0x33000000));
    theme->animationDurationIn_ =
        dialogPattern->GetAttr<int>("dialog_animation_duration_in", DEFAULT_ANIMATION_DURATION_IN);
    theme->animationDurationOut_ =
        dialogPattern->GetAttr<int>("dialog_animation_duration_out", DEFAULT_ANIMATION_DURATION_OUT);
    theme->translateValue_ = Dimension(dialogPattern->GetAttr<double>("dialog_translate", 500.0f), DimensionUnit::PX);
    theme->dividerWidth_ = dialogPattern->GetAttr<Dimension>("dialog_divider_width", 1.0_vp);
    theme->dividerHeight_ = dialogPattern->GetAttr<Dimension>("dialog_divider_height", 24.0_vp);
    theme->dividerPadding_ = Edge(dialogPattern->GetAttr<Dimension>("dialog_divider_padding_horizon", 4.0_vp),
        dialogPattern->GetAttr<Dimension>("dialog_divider_padding_vertical", 6.0_vp),
        dialogPattern->GetAttr<Dimension>("dialog_divider_padding_horizon", 4.0_vp),
        dialogPattern->GetAttr<Dimension>("dialog_divider_padding_vertical", 6.0_vp));
    theme->marginBottom_ = dialogPattern->GetAttr<Dimension>("dialog_dimension_bottom", 16.0_vp);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        theme->marginLeft_ = dialogPattern->GetAttr<Dimension>("dialog_container_margin_left", 16.0_vp);
        theme->marginRight_ = dialogPattern->GetAttr<Dimension>("dialog_container_margin_right", 16.0_vp);
    } else {
        theme->marginLeft_ = dialogPattern->GetAttr<Dimension>("dialog_dimension_start", 12.0_vp);
        theme->marginRight_ = dialogPattern->GetAttr<Dimension>("dialog_dimension_end", 12.0_vp);
    }
    theme->containerMaxWidth_ = dialogPattern->GetAttr<Dimension>("dialog_container_max_width", 400.0_vp);
    theme->defaultShadowOn_ = static_cast<uint32_t>(
        dialogPattern->GetAttr<int>("dialog_background_shadow_on", static_cast<int>(ShadowStyle::None)));
    theme->defaultShadowOff_ = static_cast<uint32_t>(
        dialogPattern->GetAttr<int>("dialog_background_shadow_off", static_cast<int>(ShadowStyle::None)));
    theme->alignment_ =
        static_cast<DialogAlignment>(dialogPattern->GetAttr<int>("dialog_alignment", DEFAULT_DIALOG_ALIGNMENT));
    theme->maxSizeScaleLandscape_ =
        dialogPattern->GetAttr<double>("dialog_maxsize_scale_landscape", DEFAULT_DIALOG_MAXSIZE_SCALE_LANDSCAPE);
    theme->maxSizeScalePortrait_ =
        dialogPattern->GetAttr<double>("dialog_maxsize_scale_portrait", DEFAULT_DIALOG_MAXSIZE_SCALE_PORTRAIT);
    theme->scrollFlexAlign_ = static_cast<FlexAlign>(
        dialogPattern->GetAttr<int>("dialog_scroll_flex_align", DEFAULT_DIALOG_SCROLL_FLEX_ALIGN));
    theme->columnMeasureType_ = static_cast<NG::MeasureType>(
        dialogPattern->GetAttr<int>("dialog_column_measure_type", DEFAULT_DIALOG_COLUMN_MEASURE_TYPE));
    theme->dialogDoubleBorderEnable_ = dialogPattern->GetAttr<int>("dialog_double_border_enable", 0);
    theme->dialogOuterBorderColor_ = dialogPattern->GetAttr<Color>("dialog_outer_border_color", Color::TRANSPARENT);
    theme->dialogOuterBorderWidth_ = dialogPattern->GetAttr<double>("dialog_outer_border_width", 0.0f);
    theme->dialogInnerBorderColor_ = dialogPattern->GetAttr<Color>("dialog_inner_border_color", Color::TRANSPARENT);
    theme->dialogInnerBorderWidth_ = dialogPattern->GetAttr<double>("dialog_inner_border_width", 0.0f);
    theme->buttonBottomTopMargin_ = dialogPattern->GetAttr<Dimension>("button_bottom_top_margin", 10.0_vp);
    theme->titlePaddingHorizontal_ = dialogPattern->GetAttr<Dimension>("title_padding_horizontal", 16.0_vp);
}
} // namespace OHOS::Ace