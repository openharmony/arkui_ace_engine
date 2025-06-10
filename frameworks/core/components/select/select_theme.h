/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SELECT_SELECT_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SELECT_SELECT_THEME_H

#include "base/geometry/dimension.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"

namespace OHOS::Ace {

constexpr double SELECT_OPTION_LEFT_LENGTH = 16.0;
constexpr double SELECT_OPTION_TOP_LENGTH = 15.0;
constexpr double SELECT_OPTION_RIGHT_LENGTH = 16.0;
constexpr double SELECT_OPTION_BOTTOM_LENGTH = 15.0;
constexpr uint32_t CONTENT_ALIGN_LEFT = 4;
constexpr double SELECT_FOCUS_SCALE = 1.0;
constexpr double NONE_SHADOW_VALUE = 6.0;
constexpr Dimension VERTICAL_INTERVAL = 14.4_vp;
constexpr Dimension MENU_END_ICON_WIDTH = 24.0_vp;
constexpr Dimension MENU_END_ICON_HEIGHT = 24.0_vp;
constexpr Dimension DEFAULT_MENU_WIDTH = 0.0_vp;
constexpr Dimension MIN_MENU_WIDTH = 64.0_vp;
constexpr double TITLE_LEFT_PADDING = 16.0;
constexpr double TITLE_TOP_PADDING = 8.0;
constexpr double TITLE_RIGHT_PADDING = 8.0;
constexpr double TITLE_BOTTOM_PADDING = 16.0;
constexpr double SELECT_OPTION_INTERVAL = 6.0;
constexpr FontWeight SELECT_MENU_CHECK_MARK_FONT_WEIGHT = FontWeight::REGULAR;
constexpr Dimension SELECT_MENU_CHECK_MARK_FONT_SIZE = 24.0_vp;
constexpr uint32_t SELECT_MENU_CHECK_MARK_DEFAULT_COLOR = 0xFF182431;

/**
 * SelectTheme defines color and styles of SelectComponent. SelectTheme should be build
 * using SelectTheme::Builder.
 */
class SelectTheme : public virtual Theme {
    DECLARE_ACE_TYPE(SelectTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<SelectTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<SelectTheme> theme = AceType::MakeRefPtr<SelectTheme>();
            if (!themeConstants) {
                return theme;
            }
            ParseNewPattern(themeConstants, theme);
            Parse(themeConstants, theme);
            return theme;
        }

        void Parse(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SelectTheme>& theme) const
        {
            if (!theme) {
                return;
            }
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_SELECT);
            if (!pattern) {
                LOGE("Pattern of select is null, please check!");
                return;
            }
            const double defaultTextColorAlpha = 0.9;
            const double defaultDisabledColorAlpha = 0.4;
            const double defaultSecondaryColorAlpha = 0.6;
            const double defaultTertiaryColorAlpha = 0.6;
            const double bgColorSelectedAlpha = 0.2;

            theme->fontColor_ =
                pattern->GetAttr<Color>("text_color", theme->fontColor_)
                    .BlendOpacity(pattern->GetAttr<double>("menu_text_primary_alpha", defaultTextColorAlpha));
            theme->disabledFontColorAlpha_ =
                pattern->GetAttr<double>("color_disabled_alpha", defaultDisabledColorAlpha);
            theme->secondaryFontColor_ =
                pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, theme->fontColor_)
                    .BlendOpacity(pattern->GetAttr<double>("menu_text_secondary_alpha", defaultSecondaryColorAlpha));
            theme->menuFontColor_ = pattern->GetAttr<Color>("text_color", theme->menuFontColor_);
            theme->disabledMenuFontColor_ = theme->menuFontColor_.BlendOpacity(
                pattern->GetAttr<double>("menu_text_tertiary_alpha", defaultTertiaryColorAlpha));
            theme->selectedColor_ =
                pattern->GetAttr<Color>(PATTERN_BG_COLOR_SELECTED, theme->selectedColor_)
                    .BlendOpacity(pattern->GetAttr<double>("bg_color_selected_alpha", bgColorSelectedAlpha));
            theme->fontSize_ = pattern->GetAttr<Dimension>(PATTERN_TEXT_SIZE, theme->fontSize_);
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                theme->selectFontSizeMap_.insert(
                    std::pair<ControlSize, Dimension>(ControlSize::NORMAL, theme->fontSize_));
                theme->selectFontSizeMap_.insert(std::pair<ControlSize, Dimension>(
                    ControlSize::SMALL, pattern->GetAttr<Dimension>("small_text_font_size", 0.0_vp)));
            }
            theme->menuFontSize_ = pattern->GetAttr<Dimension>("menu_text_font_size", theme->menuFontSize_);
            theme->menuTitleFontSize_ =
                pattern->GetAttr<Dimension>("menu_title_text_font_size", theme->menuTitleFontSize_);
            theme->menuTitleFontColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, theme->menuTitleFontColor_);
            theme->menuTitleHeight_ = pattern->GetAttr<Dimension>("menu_title_height", theme->menuTitleHeight_);
            theme->spinnerSource_ = themeConstants->GetSymbolByName("sys.symbol.arrowtriangle_down_fill");
            theme->checkMarkIconId_ = themeConstants->GetSymbolByName("sys.symbol.checkmark");
            ParsePartOne(theme, pattern);
            ParsePartTwo(theme, pattern);
            ParsePartThree(theme, pattern);
            ParsePartFourth(theme, pattern);
        }

        void ParseNewPattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SelectTheme>& theme) const
        {
            if (!theme) {
                return;
            }
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_SELECT);
            if (!pattern) {
                LOGE("Pattern of select is null, please check!");
                return;
            }
            theme->disabledColor_ = pattern->GetAttr<Color>("select_color_text_primary", Color(0x5C000000));
            theme->clickedColor_ = pattern->GetAttr<Color>("select_clicked_color", Color(0x19000000));
            theme->selectedColor_ = pattern->GetAttr<Color>("select_selected_color", Color(0x19254FF7));
            theme->fontFamily_ = "sans-serif";
            theme->fontSize_ = pattern->GetAttr<Dimension>("text_font_size", 16.0_fp);
            theme->fontColor_ = pattern->GetAttr<Color>("select_font_color", Color(0xe5000000));
            theme->fontWeight_ = FontWeight::NORMAL;
            theme->textDecoration_ = TextDecoration::NONE;
            auto optionSize = pattern->GetAttr<int>("select_option_show_count", INT32_MAX);
            theme->optionSize_ = optionSize < 0 ? theme->optionSize_ : static_cast<size_t>(optionSize);
            theme->rrectSize_ = pattern->GetAttr<Dimension>("select_itself_rrect_size", 8.0_vp);
            theme->popupBorderWidth_ = pattern->GetAttr<Dimension>("select_popup_border_width", 2.0_vp);
            theme->popupShadowWidth_ = pattern->GetAttr<Dimension>("select_popup_shadow_width", 60.0_vp);
            theme->popupRRectSize_ = pattern->GetAttr<Dimension>("select_popup_rrect_size", 16.0_vp);
            theme->popupMinWidth_ = pattern->GetAttr<Dimension>("select_popup_min_width", 136.0_vp);
            theme->normalPadding_ = pattern->GetAttr<Dimension>("select_normal_padding", 16.0_vp);
            theme->iconSize_ = pattern->GetAttr<Dimension>("select_itself_icon_size", 8.0_vp);
            theme->isTV_ = pattern->GetAttr<int>("select_is_tv", 0);
            theme->horizontalSpacing_ = pattern->GetAttr<Dimension>("select_popup_spacing_horizontal", 24.0_vp);
            theme->verticalSpacing_ = pattern->GetAttr<Dimension>("select_popup_spacing_vertical", 27.0_vp);
            theme->contentSpacing_ = pattern->GetAttr<Dimension>("select_popup_spacing_content", 0.0_vp);
            theme->selectShowTime_ = 250; // unit is ms.
            theme->selectHideTime_ = 250; // unit is ms.
            theme->menuShowTime_ = 250;   // unit is ms.
            theme->menuHideTime_ = 250;   // unit is ms.
            theme->hoverAnimationDuration_ = 250;
            theme->pressAnimationDuration_ = 100;

            ParseAttribute(theme, pattern);
        }

    private:
        void ParsePartOne(const RefPtr<SelectTheme>& theme, const RefPtr<ThemeStyle>& pattern) const
        {
            theme->disabledFontColor_ = theme->fontColor_.BlendOpacity(theme->disabledFontColorAlpha_);
            theme->clickedColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_CLICKED, theme->clickedColor_);
            theme->selectedColorText_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR_SELECTED, theme->selectedColorText_);
            theme->hoverColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_HOVERED, theme->hoverColor_);
            theme->backgroundColor_ = pattern->GetAttr<Color>("bg_color", theme->backgroundColor_);
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                theme->backgroundColorButton_ =
                    pattern->GetAttr<Color>("bg_color_select_button", theme->backgroundColorButton_);
            }
            theme->disabledBackgroundColor_ =
                theme->disabledBackgroundColor_.BlendOpacity(theme->disabledFontColorAlpha_);
            theme->lineColor_ = pattern->GetAttr<Color>("line_color", theme->lineColor_);
            theme->spinnerColor_ = pattern->GetAttr<Color>("select_icon_color", theme->spinnerColor_);
            theme->disabledSpinnerColor_ = theme->spinnerColor_.BlendOpacity(theme->disabledFontColorAlpha_);
            theme->spinnerSymbolColor_ = pattern->GetAttr<Color>("select_symbol_color", theme->spinnerSymbolColor_);
            theme->disabledSpinnerSymbolColor_ =
                theme->spinnerSymbolColor_.BlendOpacity(theme->disabledFontColorAlpha_);
            theme->selectBorderRadius_ = pattern->GetAttr<Dimension>("border_radius", theme->selectBorderRadius_);
            theme->menuBorderRadius_ = pattern->GetAttr<Dimension>("menu_border_radius", theme->menuBorderRadius_);
            theme->innerBorderRadius_ = pattern->GetAttr<Dimension>("inner_border_radius", theme->innerBorderRadius_);
            theme->menuIconPadding_ = pattern->GetAttr<Dimension>("menu_icon_padding", theme->menuIconPadding_);
            theme->iconContentPadding_ =
                pattern->GetAttr<Dimension>("icon_content_padding", theme->iconContentPadding_);
            theme->menuIconColor_ = pattern->GetAttr<Color>("menu_icon_color", theme->menuIconColor_);
            theme->dividerPaddingVertical_ =
                pattern->GetAttr<Dimension>("divider_padding_vertical", theme->dividerPaddingVertical_);
            theme->optionMinHeight_ = pattern->GetAttr<Dimension>("option_min_height", theme->optionMinHeight_);
            theme->selectMenuPadding_ = pattern->GetAttr<Dimension>("select_menu_padding", theme->selectMenuPadding_);
            theme->outPadding_ = pattern->GetAttr<Dimension>("out_padding", theme->outPadding_);
            theme->defaultPaddingStart_ =
                pattern->GetAttr<Dimension>("default_padding_start", theme->defaultPaddingStart_);
            theme->defaultPaddingEnd_ = pattern->GetAttr<Dimension>("default_padding_end", theme->defaultPaddingEnd_);
            theme->defaultPaddingTop_ = pattern->GetAttr<Dimension>("default_padding_top", theme->defaultPaddingTop_);
            theme->defaultPaddingBottomFixed_ =
                pattern->GetAttr<Dimension>("default_padding_bottom_fixed", theme->defaultPaddingBottomFixed_);
            theme->contentSpinnerPadding_ =
                pattern->GetAttr<Dimension>("content_spinner_padding", theme->contentSpinnerPadding_);
            theme->menuAnimationOffset_ =
                pattern->GetAttr<Dimension>("menu_animation_offset", theme->menuAnimationOffset_);
            theme->spinnerWidth_ = pattern->GetAttr<Dimension>("spinner_width", theme->spinnerWidth_);
            theme->menuItemNeedFocus_ = static_cast<bool>(pattern->GetAttr<int>("menu_item_need_focus", 0));
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                theme->selectSpinnerWidthMap_.insert(
                    std::pair<ControlSize, Dimension>(ControlSize::NORMAL, theme->spinnerWidth_));
                theme->selectSpinnerWidthMap_.insert(std::pair<ControlSize, Dimension>(
                    ControlSize::SMALL, pattern->GetAttr<Dimension>("small_spinner_width", 0.0_vp)));
            }
        }

        void ParsePartTwo(const RefPtr<SelectTheme>& theme, const RefPtr<ThemeStyle>& pattern) const
        {
            theme->spinnerHeight_ = pattern->GetAttr<Dimension>("spinner_height", theme->spinnerHeight_);
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                theme->selectSpinnerHeightMap_.insert(
                    std::pair<ControlSize, Dimension>(ControlSize::NORMAL, theme->spinnerHeight_));
                theme->selectSpinnerHeightMap_.insert(std::pair<ControlSize, Dimension>(
                    ControlSize::SMALL, pattern->GetAttr<Dimension>("small_spinner_height", 0.0_vp)));
            }
            theme->defaultDividerWidth_ =
                pattern->GetAttr<Dimension>("default_divider_width", theme->defaultDividerWidth_);
            theme->selectMinWidth_ = pattern->GetAttr<Dimension>("select_min_width", theme->selectMinWidth_);
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                theme->selectMinWidthMap_.insert(std::pair<ControlSize, Dimension>(
                    ControlSize::NORMAL, pattern->GetAttr<Dimension>("normal_select_min_width", 0.0_vp)));
                theme->selectMinWidthMap_.insert(std::pair<ControlSize, Dimension>(
                    ControlSize::SMALL, pattern->GetAttr<Dimension>("small_select_min_width", 0.0_vp)));
            }
            theme->selectDefaultHeight_ = pattern->GetAttr<Dimension>("select_min_height", theme->selectDefaultHeight_);
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                theme->selectMinHeightMap_.insert(
                    std::pair<ControlSize, Dimension>(ControlSize::NORMAL, theme->selectDefaultHeight_));
                theme->selectMinHeightMap_.insert(std::pair<ControlSize, Dimension>(
                    ControlSize::SMALL, pattern->GetAttr<Dimension>("small_select_min_height", 0.0_vp)));
            }
            theme->iconSideLength_ = pattern->GetAttr<Dimension>("icon_side_length", theme->iconSideLength_);
            theme->endIconWidth_ = MENU_END_ICON_WIDTH;
            theme->endIconHeight_ = MENU_END_ICON_HEIGHT;
            theme->contentMargin_ = pattern->GetAttr<Dimension>("content_margin", theme->contentMargin_);
            theme->selectDefaultBgColor_ =
                pattern->GetAttr<Color>("select_default_bg_color", theme->selectDefaultBgColor_);
            theme->selectDefaultBorderRadius_ =
                pattern->GetAttr<Dimension>("select_default_border_radius", theme->selectDefaultBorderRadius_);
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                theme->selectBorderRadiusMap_.insert(
                    std::pair<ControlSize, Dimension>(ControlSize::NORMAL, theme->selectDefaultBorderRadius_));
                theme->selectBorderRadiusMap_.insert(std::pair<ControlSize, Dimension>(
                    ControlSize::SMALL, pattern->GetAttr<Dimension>("small_select_border_radius", 0.0_vp)));
            }
            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                theme->expandDisplay_ = false;
            } else {
                std::string expandDisplay = pattern->GetAttr<std::string>("menu_expand_display", "");
                theme->expandDisplay_ = (expandDisplay == "true");
            }
            theme->maxPaddingStart_ = pattern->GetAttr<Dimension>("max_padding_start", theme->maxPaddingStart_);
            theme->maxPaddingEnd_ = pattern->GetAttr<Dimension>("max_padding_end", theme->maxPaddingEnd_);
        }

        void ParsePartThree(const RefPtr<SelectTheme>& theme, const RefPtr<ThemeStyle>& pattern) const
        {
            theme->selectNormalBorderWidth_ = pattern->GetAttr<Dimension>("select_normal_border_width", 0.0_vp);
            theme->selectNormalBorderColor_ = pattern->GetAttr<Color>("select_normal_border_color", Color::TRANSPARENT);
            theme->selectNormalShadow_ = static_cast<ShadowStyle>(
                static_cast<uint32_t>(pattern->GetAttr<double>("select_normal_shadow", NONE_SHADOW_VALUE)));
            theme->selectFocusedShadow_ = static_cast<ShadowStyle>(
                static_cast<uint32_t>(pattern->GetAttr<double>("select_focused_shadow", NONE_SHADOW_VALUE)));
            theme->selectHoverOrFocusedScale_ = pattern->GetAttr<double>("select_focused_scale", SELECT_FOCUS_SCALE);
            theme->selectFocusedTextColor_ = pattern->GetAttr<Color>("select_focused_text_color", Color(0xff182431));
            theme->selectFocusedBackgroundColor_ =
                pattern->GetAttr<Color>("select_focused_back_ground_color", Color::TRANSPARENT);
            theme->menuNormalBorderWidth_ = pattern->GetAttr<Dimension>("menu_normal_border_width", 0.0_vp);
            theme->menuNormalBorderColor_ = pattern->GetAttr<Color>("menu_normal_border_color", Color::TRANSPARENT);
            theme->menuNormalBackgroundBlurStyle_ =
                static_cast<int>(pattern->GetAttr<double>("menu_normal_back_ground_blur_type", 0));
            theme->optionNormalTopBottomMargin_ =
                pattern->GetAttr<Dimension>("option_normal_top_bottom_margin", 0.0_vp);
            theme->optionContentNormalLeftRightPadding_ =
                pattern->GetAttr<Dimension>("option_content_normal_left_right_padding", 0.0_vp);
            theme->optionContentNormalAlign_ =
                static_cast<uint32_t>(pattern->GetAttr<double>("option_content_normal_align", CONTENT_ALIGN_LEFT));
            theme->optionFocusedLeftRightMargin_ =
                pattern->GetAttr<Dimension>("option_focused_left_right_margin", 0.0_vp);
            theme->optionFocusedBackgroundColor_ =
                pattern->GetAttr<Color>("option_focused_back_ground_color", Color::TRANSPARENT);
            theme->optionFocusedShadow_ =
                static_cast<uint32_t>(pattern->GetAttr<double>("option_focus_shadow", NONE_SHADOW_VALUE));
            theme->optionFocusedFontColor_ = pattern->GetAttr<Color>("option_focused_font_color", Color(0xff182431));
            theme->shadowNormal_ =
                static_cast<uint32_t>(pattern->GetAttr<double>("option_default_shadow", NONE_SHADOW_VALUE));
            theme->optionSelectedBorderColor_ =
                pattern->GetAttr<Color>("option_selected_border_color", Color::TRANSPARENT);
            theme->optionSelectedBorderWidth_ = pattern->GetAttr<Dimension>("option_selected_border_width", 0.0_vp);
            theme->optionNormalWidth_ = pattern->GetAttr<Dimension>("option_normal_width", 156.0_vp);
            theme->selectedFontSizeText = pattern->GetAttr<Dimension>("select_font_size_text", 16.0_fp);
            theme->selectNormalLeftRightMargin_ =
        pattern->GetAttr<Dimension>("select_normal_left_right_margin", 8.0_vp);
            theme->menuBlendBgColor_ = pattern->GetAttr<int>("menu_is_blend_bg_color", 0);
        theme->optionFocusedBoxPadding_ =
                pattern->GetAttr<Dimension>("option_focused_box_padding", 0.0_vp);
            theme->spinnerFocusedSymbolColor_ =
                pattern->GetAttr<Color>("select_focused_symbol_color", theme->spinnerFocusedSymbolColor_);
            theme->spinnerFocusedColor_ =
                pattern->GetAttr<Color>("select_focused_icon_color", theme->spinnerFocusedColor_);
            theme->optionApplyFocusedStyle_ = pattern->GetAttr<int>("option_is_apply_focus_style", 0);
            theme->isSlideMoreOffset_ = pattern->GetAttr<int>("select_slide_more_offset", 0);
        }

        void ParsePartFourth(const RefPtr<SelectTheme>& theme, const RefPtr<ThemeStyle>& pattern) const
        {
            theme->defaultDividerStartMargin_ = pattern->GetAttr<Dimension>("menu_divider_start_margin", 0.0_vp);
            theme->defaultDividerEndMargin_ = pattern->GetAttr<Dimension>("menu_divider_end_margin", 0.0_vp);
            theme->defaultShowDivider_ = static_cast<bool>(pattern->GetAttr<int>("menu_default_show_divider", 0));
            theme->menuItemTopBottomMargin_ = pattern->GetAttr<Dimension>("menu_item_top_bottom_margin", 0.0_vp);
            theme->menuItemLeftRightMargin_ = pattern->GetAttr<Dimension>("menu_item_left_right_margin", 0.0_vp);
            theme->menuTargetSecuritySpace_ = pattern->GetAttr<Dimension>("menu_target_security_space", 8.0_vp);
            theme->menuItemFocusedBgColor_ = pattern->GetAttr<Color>("menu_item_focused_bg_color", Color::TRANSPARENT);
            theme->menuItemFocusedTextColor_ =
                pattern->GetAttr<Color>("menu_item_focused_text_color", Color(0xff182431));
            theme->menuItemFocusedShadowStyle_ =
                static_cast<uint32_t>(pattern->GetAttr<double>("menu_item_focused_shadow_style", NONE_SHADOW_VALUE));
            theme->menuItemContentAlign_ =
                static_cast<uint32_t>(pattern->GetAttr<double>("menu_item_content_align", CONTENT_ALIGN_LEFT));
            theme->selectFocusStyleType_ = pattern->GetAttr<double>("select_focus_style_type", 0.0);
            theme->optionFocusStyleType_ = pattern->GetAttr<double>("option_focus_style_type", 0.0);
            theme->menuItemHorIntervalPadding_ =
                pattern->GetAttr<Dimension>("menu_item_hor_interval", theme->menuItemHorIntervalPadding_);
            theme->menuPadding_ = pattern->GetAttr<Dimension>("menu_padding_interval", theme->menuPadding_);
            if (theme->GetExpandDisplay()) {
                theme->menuWordBreak_ = WordBreak::BREAK_ALL;
            } else {
                theme->menuWordBreak_ = WordBreak::BREAK_WORD;
            }
            theme->checkMarkFontWeight_ = FontWeight(static_cast<int32_t>(pattern->GetAttr<double>(
                "select_check_mark_font_weight", static_cast<double>(SELECT_MENU_CHECK_MARK_FONT_WEIGHT))));
            theme->checkMarkFontSize_ =
                pattern->GetAttr<Dimension>("select_check_mark_font_size", SELECT_MENU_CHECK_MARK_FONT_SIZE);
            theme->checkMarkColor_ =
                pattern->GetAttr<Color>("select_check_mark_color", Color(SELECT_MENU_CHECK_MARK_DEFAULT_COLOR));
        }

        void ParseAttribute(const RefPtr<SelectTheme>& theme, const RefPtr<ThemeStyle>& pattern) const
        {
            theme->titleLeftPadding_ = Dimension(TITLE_LEFT_PADDING, DimensionUnit::VP);
            theme->titleTopPadding_ = Dimension(TITLE_TOP_PADDING, DimensionUnit::VP);
            theme->titleRightPadding_ = Dimension(TITLE_RIGHT_PADDING, DimensionUnit::VP);
            theme->titleBottomPadding_ = Dimension(TITLE_BOTTOM_PADDING, DimensionUnit::VP);
            theme->titleStyle_.SetFontSize(pattern->GetAttr<Dimension>("text_size_headline7", 24.0_vp));
            std::vector<std::string> families;
            families.emplace_back("sans-serif");
            theme->titleStyle_.SetFontFamilies(families);
            theme->titleStyle_.SetFontWeight(FontWeight::W500);
            theme->titleStyle_.SetTextColor(pattern->GetAttr<Color>("select_font_color", Color(0xe5000000)));
            theme->titleStyle_.SetTextDecoration(TextDecoration::NONE);
            theme->optionPadding_ = Edge(SELECT_OPTION_LEFT_LENGTH, SELECT_OPTION_TOP_LENGTH,
                SELECT_OPTION_RIGHT_LENGTH, SELECT_OPTION_BOTTOM_LENGTH, DimensionUnit::VP);
            theme->optionInterval_ = theme->isTV_ ? Dimension(SELECT_OPTION_INTERVAL, DimensionUnit::VP) : 0.0_vp;
            theme->tvFocusTextColor_ = Color(0xE6000000);
            theme->tvNormalBackColor_ = Color(0x33FFFFFF);
            theme->tvBackColor_ = (theme->isTV_ ? Color(0x99000000) : Color::TRANSPARENT);
            // disabled color
            theme->normalDisableColor_ = pattern->GetAttr<Color>("select_option_disable_color", Color(0x32FFFFFF));
            theme->focusedDisableColor_ =
                pattern->GetAttr<Color>("select_option_focused_disable_color", Color(0x5DFFFFFF));
            theme->normalTextDisableColor_ =
                pattern->GetAttr<Color>("select_option_focused_disable_color", Color(0x5DFFFFFF));
            theme->focusedTextDisableColor_ =
                pattern->GetAttr<Color>("select_option_focused_disable_text_color", Color(0x66000000));
            theme->optionTextStyle_.SetFontSize(pattern->GetAttr<Dimension>("text_font_size", 16.0_fp));
            theme->optionTextStyle_.SetFontFamilies({ pattern->GetAttr<std::string>("text_font_family_regular",
                "sans-serif") });
            theme->optionTextStyle_.SetFontWeight(FontWeight::NORMAL);
            theme->optionTextStyle_.SetTextColor(pattern->GetAttr<Color>("select_font_color", Color(0xe5000000)));
            theme->optionTextStyle_.SetTextDecoration(TextDecoration::NONE);
            theme->menuLargeMargin_ = pattern->GetAttr<Dimension>("menu_large_margin", theme->menuLargeMargin_);
            theme->menuMediumMargin_ = pattern->GetAttr<Dimension>("menu_medium_margin", theme->menuMediumMargin_);
            theme->menuItemChildMinHeight_ = pattern->GetAttr<Dimension>("menu_item_child_min_height", 32.0_vp);
            theme->menuItemVerticalPadding_ = pattern->GetAttr<Dimension>("menu_item_vertical_padding", 8.0_vp);
            theme->menuItemGroupTitleTextFontSize_ =
                pattern->GetAttr<Dimension>("menu_item_group_title_text_font_size", 18.0_vp);
            theme->menuDefaultRadius_ = pattern->GetAttr<Dimension>("menu_border_radius_new", 20.0_vp);
            theme->menuDefaultInnerRadius_ = pattern->GetAttr<Dimension>("inner_border_radius_new", 16.0_vp);
            theme->menuTextColor_= pattern->GetAttr<Color>("menu_text_color", Color(0xe5000000));
            theme->menuDefaultWidth_ = pattern->GetAttr<Dimension>("menu_default_width", 160.0_vp);
            theme->menuMinWidth_ = pattern->GetAttr<Dimension>("menu_min_width", 64.0_vp);
            theme->menuMaxWidth_ = pattern->GetAttr<Dimension>("menu_max_width", 224.0_vp);
            theme->menuMaxWidthRatio_ = pattern->GetAttr<double>("menu_max_width_ratio", 0.67f);
            theme->menuBackgroundBlurStyle_ =
                pattern->GetAttr<int>("menu_background_blur_style", static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK));
            theme->menuAnimationDuration_ = pattern->GetAttr<int>("menu_animation_duration", 0);
            theme->menuAnimationScale_ = pattern->GetAttr<double>("menu_animation_scale", 0.6f);
            theme->menuAnimationCurve_ = pattern->GetAttr<std::string>("menu_animation_curve", "fast_out_slow_in");
        }
    };

    ~SelectTheme() override = default;

    RefPtr<SelectTheme> clone()
    {
        RefPtr<SelectTheme> theme = AceType::MakeRefPtr<SelectTheme>();
        ClonePartOne(theme);
        ClonePartTwo(theme);
        ClonePartThree(theme);
        CloneWideScreenAttrs(theme);
        return theme;
    }

    void ClonePartOne(RefPtr<SelectTheme>& theme)
    {
        theme->disabledColor_ = disabledColor_;
        theme->clickedColor_ = clickedColor_;
        theme->selectedColor_ = selectedColor_;
        theme->fontSize_ = fontSize_;
        theme->fontFamily_ = fontFamily_;
        theme->fontColor_ = fontColor_;
        theme->disabledFontColor_ = disabledFontColor_;
        theme->disabledFontColorAlpha_ = disabledFontColorAlpha_;
        theme->secondaryFontColor_ = secondaryFontColor_;
        theme->fontWeight_ = fontWeight_;
        theme->textDecoration_ = textDecoration_;
        theme->rrectSize_ = rrectSize_;
        theme->iconSize_ = iconSize_;
        theme->normalPadding_ = normalPadding_;
        theme->optionSize_ = optionSize_;
        theme->popupRRectSize_ = popupRRectSize_;
        theme->popupMinWidth_ = popupMinWidth_;
        theme->popupShadowWidth_ = popupShadowWidth_;
        theme->popupBorderWidth_ = popupBorderWidth_;
        theme->titleLeftPadding_ = titleLeftPadding_;
        theme->titleTopPadding_ = titleTopPadding_;
        theme->titleRightPadding_ = titleRightPadding_;
        theme->titleBottomPadding_ = titleBottomPadding_;
        theme->titleStyle_ = titleStyle_;
        theme->isTV_ = isTV_;
        theme->horizontalSpacing_ = horizontalSpacing_;
        theme->verticalSpacing_ = verticalSpacing_;
        theme->contentSpacing_ = contentSpacing_;
        theme->menuHideTime_ = menuHideTime_;
        theme->menuShowTime_ = menuShowTime_;
        theme->selectShowTime_ = selectShowTime_;
        theme->selectHideTime_ = selectHideTime_;
        theme->hoverAnimationDuration_ = hoverAnimationDuration_;
        theme->pressAnimationDuration_ = pressAnimationDuration_;
        theme->optionPadding_ = optionPadding_;
        theme->optionInterval_ = optionInterval_;
        theme->optionMinHeight_ = optionMinHeight_;
        theme->tvFocusTextColor_ = tvFocusTextColor_;
        theme->tvNormalBackColor_ = tvNormalBackColor_;
    }

    void ClonePartTwo(RefPtr<SelectTheme>& theme)
    {
        theme->tvBackColor_ = tvBackColor_;
        theme->focusedDisableColor_ = focusedDisableColor_;
        theme->normalDisableColor_ = normalDisableColor_;
        theme->focusedTextDisableColor_ = focusedTextDisableColor_;
        theme->normalTextDisableColor_ = normalTextDisableColor_;
        theme->spinnerColor_ = spinnerColor_;
        theme->disabledSpinnerColor_ = disabledSpinnerColor_;
        theme->spinnerSymbolColor_ = spinnerSymbolColor_;
        theme->disabledSpinnerSymbolColor_ = disabledSpinnerSymbolColor_;
        theme->spinnerSource_ = spinnerSource_;
        theme->backgroundColor_ = backgroundColor_;
        theme->backgroundColorButton_ = backgroundColorButton_;
        theme->disabledBackgroundColor_ = disabledBackgroundColor_;
        theme->hoverColor_ = hoverColor_;
        theme->selectedColorText_ = selectedColorText_;
        theme->lineColor_ = lineColor_;
        theme->optionTextStyle_ = optionTextStyle_;
        theme->selectBorderRadius_ = selectBorderRadius_;
        theme->menuBorderRadius_ = menuBorderRadius_;
        theme->innerBorderRadius_ = innerBorderRadius_;
        theme->menuFontSize_ = menuFontSize_;
        theme->menuTitleFontSize_ = menuTitleFontSize_;
        theme->menuTitleFontColor_ = menuTitleFontColor_;
        theme->menuTitleHeight_ = menuTitleHeight_;
        theme->menuFontColor_ = menuFontColor_;
        theme->disabledMenuFontColor_ = disabledMenuFontColor_;
        theme->menuIconPadding_ = menuIconPadding_;
        theme->iconContentPadding_ = iconContentPadding_;
        theme->dividerPaddingVertical_ = dividerPaddingVertical_;
        theme->menuIconColor_ = menuIconColor_;
        theme->optionMinHeight_ = optionMinHeight_;
        theme->selectMenuPadding_ = selectMenuPadding_;
        theme->outPadding_ = outPadding_;
        theme->defaultPaddingStart_ = defaultPaddingStart_;
        theme->defaultPaddingEnd_ = defaultPaddingEnd_;
        theme->defaultPaddingTop_ = defaultPaddingTop_;
        theme->defaultPaddingBottomFixed_ = defaultPaddingBottomFixed_;
        theme->contentSpinnerPadding_ = contentSpinnerPadding_;
        theme->menuAnimationOffset_ = menuAnimationOffset_;
        theme->spinnerWidth_ = spinnerWidth_;
        theme->spinnerHeight_ = spinnerHeight_;
    }

    void ClonePartThree(RefPtr<SelectTheme>& theme)
    {
        theme->defaultDividerWidth_ = defaultDividerWidth_;
        theme->selectMinWidth_ = selectMinWidth_;
        theme->selectDefaultHeight_ = selectDefaultHeight_;
        theme->iconSideLength_ = iconSideLength_;
        theme->endIconWidth_ = endIconWidth_;
        theme->endIconHeight_ = endIconHeight_;
        theme->checkMarkIconId_ = checkMarkIconId_;
        theme->checkMarkFontSize_ = checkMarkFontSize_;
        theme->checkMarkFontWeight_ = checkMarkFontWeight_;
        theme->checkMarkColor_ = checkMarkColor_;
        theme->contentMargin_ = contentMargin_;
        theme->selectDefaultBgColor_ = selectDefaultBgColor_;
        theme->selectDefaultBorderRadius_ = selectDefaultBorderRadius_;
        theme->expandDisplay_ = expandDisplay_;
        theme->maxPaddingStart_ = maxPaddingStart_;
        theme->maxPaddingEnd_ = maxPaddingEnd_;
        theme->menuLargeMargin_ = menuLargeMargin_;
        theme->menuMediumMargin_ = menuMediumMargin_;
        theme->menuItemChildMinHeight_ = menuItemChildMinHeight_;
        theme->menuItemVerticalPadding_ = menuItemVerticalPadding_;
        theme->menuItemGroupTitleTextFontSize_ = menuItemGroupTitleTextFontSize_;
        theme->menuDefaultRadius_ = menuDefaultRadius_;
        theme->menuDefaultInnerRadius_ = menuDefaultInnerRadius_;
        theme->menuTextColor_ = menuTextColor_;
        theme->menuDefaultWidth_ = menuDefaultWidth_;
        theme->menuMinWidth_ = menuMinWidth_;
        theme->menuMaxWidth_ = menuMaxWidth_;
        theme->menuMaxWidthRatio_ = menuMaxWidthRatio_;
        theme->menuBackgroundBlurStyle_ = menuBackgroundBlurStyle_;
        theme->menuItemHorIntervalPadding_ = menuItemHorIntervalPadding_;
        theme->menuPadding_ = menuPadding_;
        theme->menuWordBreak_ = menuWordBreak_;
    }

    void CloneWideScreenAttrs(RefPtr<SelectTheme>& theme)
    {
        theme->selectNormalBorderWidth_ = selectNormalBorderWidth_;
        theme->selectNormalBorderColor_ = selectNormalBorderColor_;
        theme->selectNormalShadow_ = selectNormalShadow_;
        theme->selectFocusedShadow_ = selectFocusedShadow_;
        theme->selectHoverOrFocusedScale_ = selectHoverOrFocusedScale_;
        theme->selectFocusedTextColor_ = selectFocusedTextColor_;
        theme->selectFocusedBackgroundColor_ = selectFocusedBackgroundColor_;
        theme->menuNormalBorderWidth_ = menuNormalBorderWidth_;
        theme->menuNormalBorderColor_ = menuNormalBorderColor_;
        theme->menuNormalBackgroundBlurStyle_ = menuNormalBackgroundBlurStyle_;
        theme->optionNormalTopBottomMargin_ = optionNormalTopBottomMargin_;
        theme->optionContentNormalLeftRightPadding_ = optionContentNormalLeftRightPadding_;
        theme->optionContentNormalAlign_ = optionContentNormalAlign_;
        theme->optionFocusedLeftRightMargin_ = optionFocusedLeftRightMargin_;
        theme->optionFocusedBackgroundColor_ = optionFocusedBackgroundColor_;
        theme->optionFocusedShadow_ = optionFocusedShadow_;
        theme->optionFocusedFontColor_ = optionFocusedFontColor_;
        theme->shadowNormal_ = shadowNormal_;
        theme->optionSelectedBorderColor_ = optionSelectedBorderColor_;
        theme->optionSelectedBorderWidth_ = optionSelectedBorderWidth_;
        theme->optionNormalWidth_ = optionNormalWidth_;
        theme->selectedFontSizeText = selectedFontSizeText;
        theme->selectNormalLeftRightMargin_ = selectNormalLeftRightMargin_;
        theme->menuBlendBgColor_ = menuBlendBgColor_;
        theme->optionFocusedBoxPadding_ = optionFocusedBoxPadding_;
        theme->spinnerFocusedSymbolColor_ = spinnerFocusedSymbolColor_;
        theme->spinnerFocusedColor_ = spinnerFocusedColor_;
        theme->optionApplyFocusedStyle_ = optionApplyFocusedStyle_;
        theme->isSlideMoreOffset_ = isSlideMoreOffset_;
        theme->menuItemTopBottomMargin_ = menuItemTopBottomMargin_;
        theme->menuItemLeftRightMargin_ = menuItemLeftRightMargin_;
        theme->menuTargetSecuritySpace_ = menuTargetSecuritySpace_;
        theme->menuItemFocusedBgColor_ = menuItemFocusedBgColor_;
        theme->menuItemFocusedTextColor_ = menuItemFocusedTextColor_;
        theme->menuItemFocusedShadowStyle_ = menuItemFocusedShadowStyle_;
        theme->menuItemContentAlign_ = menuItemContentAlign_;
        theme->selectFocusStyleType_ = selectFocusStyleType_;
        theme->optionFocusStyleType_ = optionFocusStyleType_;
    }

    const Color& GetSelectedColorText() const
    {
        return selectedColorText_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetButtonBackgroundColor() const
    {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            return backgroundColorButton_;
        }
        return backgroundColor_;
    }
    void SetButtonBackgroundColor(const Color& value)
    {
        backgroundColorButton_ = value;
    }

    const Color& GetDisabledBackgroundColor() const
    {
        return disabledBackgroundColor_;
    }

    const Color& GetDisabledColor() const
    {
        return disabledColor_;
    }
    void SetDisabledColor(const Color& value)
    {
        disabledColor_ = value;
    }

    const Color& GetClickedColor() const
    {
        return clickedColor_;
    }
    void SetClickedColor(const Color& value)
    {
        clickedColor_ = value;
    }

    const Color& GetSelectedColor() const
    {
        return selectedColor_;
    }

    void SetSelectedColor(const Color& value)
    {
        selectedColor_ = value;
    }

    const Dimension& GetFontSize() const
    {
        return fontSize_;
    }

    const Dimension& GetFontSize(ControlSize controlSize) const
    {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            auto result = selectFontSizeMap_.find(controlSize);
            if (result != selectFontSizeMap_.end()) {
                return result->second;
            }
        }
        return fontSize_;
    }

    void SetFontSize(const Dimension& value)
    {
        fontSize_ = value;
    }

    const Color& GetFontColor() const
    {
        return fontColor_;
    }
    void SetFontColor(const Color& value)
    {
        fontColor_ = value;
    }

    const Color& GetDisabledFontColor() const
    {
        return disabledFontColor_;
    }

    double GetDisabledFontColorAlpha() const
    {
        return disabledFontColorAlpha_;
    }

    const Color& GetSecondaryFontColor() const
    {
        return secondaryFontColor_;
    }

    const std::string& GetFontFamily() const
    {
        return fontFamily_;
    }
    void SetFontFamily(const std::string& value)
    {
        fontFamily_ = value;
    }

    FontWeight GetFontWeight() const
    {
        return fontWeight_;
    }
    void SetFontWeight(FontWeight value)
    {
        fontWeight_ = value;
    }

    TextDecoration GetTextDecoration() const
    {
        return textDecoration_;
    }
    void SetTextDecoration(TextDecoration value)
    {
        textDecoration_ = value;
    }

    std::size_t GetOptionSize() const
    {
        return optionSize_;
    }
    void SetOptionSize(std::size_t value)
    {
        optionSize_ = value;
    }

    const Dimension& GetRRectSize() const
    {
        return rrectSize_;
    }
    void SetRRectSize(const Dimension& value)
    {
        rrectSize_ = value;
    }

    const Dimension& GetPopupRRectSize() const
    {
        return popupRRectSize_;
    }
    void SetPopupRRectSize(const Dimension& value)
    {
        popupRRectSize_ = value;
    }

    const Dimension& GetPopupBorderWidth() const
    {
        return popupBorderWidth_;
    }
    void SetPopupBorderWidth(const Dimension& value)
    {
        popupBorderWidth_ = value;
    }

    const Dimension& GetPopupShadowWidth() const
    {
        return popupShadowWidth_;
    }
    void SetPopupShadowWidth(const Dimension& value)
    {
        popupShadowWidth_ = value;
    }

    const Dimension& GetPopupMinWidth() const
    {
        return popupMinWidth_;
    }
    void SetPopupMinWidth(const Dimension& value)
    {
        popupMinWidth_ = value;
    }

    const Dimension& GetNormalPadding() const
    {
        return normalPadding_;
    }
    void SetNormalPadding(const Dimension& value)
    {
        normalPadding_ = value;
    }

    const Dimension& GetIconSize() const
    {
        return iconSize_;
    }
    void SetIconSize(const Dimension& value)
    {
        iconSize_ = value;
    }

    const Dimension& GetTitleLeftPadding() const
    {
        return titleLeftPadding_;
    }
    void SetTitleLeftPadding(const Dimension& value)
    {
        titleLeftPadding_ = value;
    }

    const Dimension& GetTitleTopPadding() const
    {
        return titleTopPadding_;
    }
    void SetTitleTopPadding(const Dimension& value)
    {
        titleTopPadding_ = value;
    }

    const Dimension& GetTitleRightPadding() const
    {
        return titleRightPadding_;
    }
    void SetTitleRightPadding(const Dimension& value)
    {
        titleRightPadding_ = value;
    }

    const Dimension& GetTitleBottomPadding() const
    {
        return titleBottomPadding_;
    }
    void SetTitleBottomPadding(const Dimension& value)
    {
        titleBottomPadding_ = value;
    }

    const TextStyle& GetTitleStyle()
    {
        return titleStyle_;
    }
    void SetTitleStyle(const TextStyle& value)
    {
        titleStyle_ = value;
    }

    bool IsTV() const
    {
        return isTV_;
    }
    void SetIsTV(bool isTV)
    {
        isTV_ = isTV;
    }

    const Dimension& GetHorizontalSpacing() const
    {
        return horizontalSpacing_;
    }
    void SetHorizontalSpacing(const Dimension& horizontalSpacing)
    {
        horizontalSpacing_ = horizontalSpacing;
    }

    const Dimension& GetVerticalSpacing() const
    {
        return verticalSpacing_;
    }
    void SetVerticalSpacing(const Dimension& verticalSpacing)
    {
        verticalSpacing_ = verticalSpacing;
    }

    const Dimension& GetContentSpacing() const
    {
        return contentSpacing_;
    }
    void SetContentSpacing(const Dimension& contentSpacing)
    {
        contentSpacing_ = contentSpacing;
    }

    const Edge& GetOptionPadding() const
    {
        return optionPadding_;
    }
    void SetOptionPadding(const Edge& value)
    {
        optionPadding_ = value;
    }

    uint32_t GetShowTime(bool isMenu) const
    {
        if (isMenu) {
            return menuShowTime_;
        } else {
            return selectShowTime_;
        }
    }

    uint32_t GetHideTime(bool isMenu) const
    {
        if (isMenu) {
            return menuHideTime_;
        } else {
            return selectHideTime_;
        }
    }

    int32_t GetHoverAnimationDuration() const
    {
        return hoverAnimationDuration_;
    }

    int32_t GetPressAnimationDuration() const
    {
        return pressAnimationDuration_;
    }

    SelectTheme() = default;

    bool IsAllowScale() const
    {
        return allowScale_;
    }

    void SetAllowScale(bool allowScale)
    {
        allowScale_ = allowScale;
    }

    const Dimension& GetOptionInterval() const
    {
        return optionInterval_;
    }

    const Dimension& GetOptionMinHeight() const
    {
        return optionMinHeight_;
    }

    const Color& GetTvFocusTextColor() const
    {
        return tvFocusTextColor_;
    }

    const Color& GetTvNormalBackColor() const
    {
        return tvNormalBackColor_;
    }

    const Color& GetTvBackColor() const
    {
        return tvBackColor_;
    }

    const Color& GetFocusedDisableColor() const
    {
        return focusedDisableColor_;
    }

    const Color& GetCheckMarkColor() const
    {
        return checkMarkColor_;
    }

    FontWeight GetCheckMarkFontWeight() const
    {
        return checkMarkFontWeight_;
    }

    const Color& GetNormalDisableColor() const
    {
        return normalDisableColor_;
    }

    const Color& GetFocusedTextDisableColor() const
    {
        return focusedTextDisableColor_;
    }

    const Color& GetNormalTextDisableColor() const
    {
        return normalTextDisableColor_;
    }

    const Color& GetSpinnerColor() const
    {
        return spinnerColor_;
    }

    const Color& GetDisabledSpinnerColor() const
    {
        return disabledSpinnerColor_;
    }

    const Color& GetSpinnerSymbolColor() const
    {
        return spinnerSymbolColor_;
    }

    const Color& GetDisabledSpinnerSymbolColor() const
    {
        return disabledSpinnerSymbolColor_;
    }

    const uint32_t& GetSpinnerSource() const
    {
        return spinnerSource_;
    }

    const uint32_t& GetCheckMarkIconId() const
    {
        return checkMarkIconId_;
    }

    const Color& GetMenuIconColor() const
    {
        return menuIconColor_;
    }

    const Color& GetLineColor() const
    {
        return lineColor_;
    }

    const TextStyle& GetOptionTextStyle() const
    {
        return optionTextStyle_;
    }

    const Dimension& GetSelectBorderRadius() const
    {
        return selectBorderRadius_;
    }

    const Dimension& GetMenuBorderRadius() const
    {
        return menuBorderRadius_;
    }

    const Dimension& GetInnerBorderRadius() const
    {
        return innerBorderRadius_;
    }

    const Dimension& GetMenuFontSize() const
    {
        return menuFontSize_;
    }

    const Dimension& GetMenuTitleFontSize() const
    {
        return menuTitleFontSize_;
    }

    const Color& GetMenuTitleFontColor() const
    {
        return menuTitleFontColor_;
    }

    const Dimension& GetMenuTitleHeight() const
    {
        return menuTitleHeight_;
    }

    const Color& GetMenuFontColor() const
    {
        return menuFontColor_;
    }

    const Color& GetDisabledMenuFontColor() const
    {
        return disabledMenuFontColor_;
    }
    void SetDisabledMenuFontColor(const Color& value)
    {
        disabledMenuFontColor_ = value;
    }

    const Dimension& GetMenuIconPadding() const
    {
        return menuIconPadding_;
    }

    const Dimension& GetMenuItemHorIntervalPadding() const
    {
        return menuItemHorIntervalPadding_;
    }

    const Dimension& GetMenuPadding() const
    {
        return menuPadding_;
    }

    const Dimension& GetIconContentPadding() const
    {
        return iconContentPadding_;
    }

    const Dimension& GetDividerPaddingVertical() const
    {
        return dividerPaddingVertical_;
    }

    const Dimension& GetSelectMenuPadding() const
    {
        return selectMenuPadding_;
    }

    const Dimension& GetOutPadding() const
    {
        return outPadding_;
    }

    const Dimension& GetDefaultPaddingStart() const
    {
        return defaultPaddingStart_;
    }

    const Dimension& GetDefaultPaddingEnd() const
    {
        return defaultPaddingEnd_;
    }

    const Dimension& GetDefaultPaddingTop() const
    {
        return defaultPaddingTop_;
    }

    const Dimension& GetDefaultPaddingBottomFixed() const
    {
        return defaultPaddingBottomFixed_;
    }

    const Dimension& GetContentSpinnerPadding() const
    {
        return contentSpinnerPadding_;
    }

    const Dimension& GetMenuAnimationOffset() const
    {
        return menuAnimationOffset_;
    }

    const Dimension& GetSpinnerWidth() const
    {
        return spinnerWidth_;
    }

    bool GetMenuItemNeedFocus() const
    {
        return menuItemNeedFocus_;
    }

    const Dimension& GetSpinnerWidth(ControlSize controlSize) const
    {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            auto result = selectSpinnerWidthMap_.find(controlSize);
            if (result != selectSpinnerWidthMap_.end()) {
                return result->second;
            }
        }
        return spinnerWidth_;
    }

    const Dimension& GetSpinnerHeight() const
    {
        return spinnerHeight_;
    }

    const Dimension& GetSpinnerHeight(ControlSize controlSize) const
    {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            auto result = selectSpinnerHeightMap_.find(controlSize);
            if (result != selectSpinnerHeightMap_.end()) {
                return result->second;
            }
        }
        return spinnerHeight_;
    }

    const Dimension& GetDefaultDividerWidth() const
    {
        return defaultDividerWidth_;
    }

    const Dimension& GetSelectMinWidth() const
    {
        return selectMinWidth_;
    }

    const Dimension& GetSelectMinWidth(ControlSize controlSize) const
    {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            auto result = selectMinWidthMap_.find(controlSize);
            if (result != selectMinWidthMap_.end()) {
                return result->second;
            }
        }
        return selectMinWidth_;
    }

    const Dimension& GetSelectDefaultHeight() const
    {
        return selectDefaultHeight_;
    }

    const Dimension& GetSelectDefaultHeight(ControlSize controlSize) const
    {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            auto result = selectMinHeightMap_.find(controlSize);
            if (result != selectMinHeightMap_.end()) {
                return result->second;
            }
        }
        return selectDefaultHeight_;
    }

    const Dimension& GetIconSideLength() const
    {
        return iconSideLength_;
    }

    const Dimension& GetEndIconWidth() const
    {
        return endIconWidth_;
    }

    const Dimension& GetEndIconHeight() const
    {
        return endIconHeight_;
    }

    const Dimension& GetCheckMarkFontSize() const
    {
        return checkMarkFontSize_;
    }

    const Dimension& GetContentMargin() const
    {
        return contentMargin_;
    }

    const Color& GetSelectDefaultBgColor() const
    {
        return selectDefaultBgColor_;
    }

    const Dimension& GetSelectDefaultBorderRadius() const
    {
        return selectDefaultBorderRadius_;
    }

    const Dimension& GetSelectDefaultBorderRadius(ControlSize controlSize) const
    {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            auto result = selectBorderRadiusMap_.find(controlSize);
            if (result != selectBorderRadiusMap_.end()) {
                return result->second;
            }
        }
        return selectDefaultBorderRadius_;
    }

    bool GetExpandDisplay() const
    {
        return expandDisplay_;
    }

    const Dimension& GetMaxPaddingStart() const
    {
        return maxPaddingStart_;
    }

    const Dimension& GetMaxPaddingEnd() const
    {
        return maxPaddingEnd_;
    }
    const Dimension& GetMenuLargeMargin() const
    {
        return menuLargeMargin_;
    }
    const Dimension& GetMenuMediumMargin() const
    {
        return menuMediumMargin_;
    }

    const Dimension& GetMenuChildMinHeight() const
    {
        return menuItemChildMinHeight_;
    }

    const Dimension& GetMenuItemVerticalPadding() const
    {
        return menuItemVerticalPadding_;
    }

    const Dimension& GetMenuItemGroupTitleTextFontSize() const
    {
        return menuItemGroupTitleTextFontSize_;
    }

    const Dimension& GetMenuDefaultRadius() const
    {
        return menuDefaultRadius_;
    }

    const Dimension& GetMenuDefaultInnerRadius() const
    {
        return menuDefaultInnerRadius_;
    }

    const Dimension& GetMenuDefaultWidth() const
    {
        return menuDefaultWidth_;
    }

    const Dimension& GetMenuMinWidth() const
    {
        return menuMinWidth_;
    }

    const Dimension& GetMenuMaxWidth() const
    {
        return menuMaxWidth_;
    }

    double GetMenuMaxWidthRatio() const
    {
        return menuMaxWidthRatio_;
    }

    const Color& GetMenuTextColor() const
    {
        return menuTextColor_;
    }

    const uint32_t& GetMenuItemContentAlign() const
    {
        return menuItemContentAlign_;
    }

    Dimension GetSelectNormalBorderWidth() const
    {
        return selectNormalBorderWidth_;
    }

    Color GetSelectNormalBorderColor() const
    {
        return selectNormalBorderColor_;
    }

    ShadowStyle GetSelectNormalShadow() const
    {
        return selectNormalShadow_;
    }

    ShadowStyle GetSelectFocusedShadow() const
    {
        return selectFocusedShadow_;
    }

    double GetSelectHoverOrFocusedScale() const
    {
        return selectHoverOrFocusedScale_;
    }

    Color GetSelectFocusedBackground() const
    {
        return selectFocusedBackgroundColor_;
    }

    Color GetSelectFocusTextColor() const
    {
        return selectFocusedTextColor_;
    }

    Dimension GetMenuNormalBorderWidth() const
    {
        return menuNormalBorderWidth_;
    }

    int GetMenuNormalBackgroundBlurStyle() const
    {
        return menuNormalBackgroundBlurStyle_;
    }

    Color GetMenuNormalBorderColor() const
    {
        return menuNormalBorderColor_;
    }

    Dimension GetOptionNormalTopBottomMargin() const
    {
        return optionNormalTopBottomMargin_;
    }

    Dimension GetOptionFocusedLeftRightMargin() const
    {
        return optionFocusedLeftRightMargin_;
    }

    Color GetOptionFocusedBackgroundColor() const
    {
        return optionFocusedBackgroundColor_;
    }

    uint32_t GetOptionFocusedShadow() const
    {
        return optionFocusedShadow_;
    }

    Color GetOptionFocusedFontColor() const
    {
        return optionFocusedFontColor_;
    }

    Dimension GetOptionContentNormalLeftRightPadding() const
    {
        return optionContentNormalLeftRightPadding_;
    }

    uint32_t GetOptionContentNormalAlign() const
    {
        return optionContentNormalAlign_;
    }

    uint32_t GetShadowNormal() const
    {
        return shadowNormal_;
    }

    Color GetOptionSelectedBorderColor() const
    {
        return optionSelectedBorderColor_;
    }

    Dimension GetOptionSelectedBorderWidth() const
    {
        return optionSelectedBorderWidth_;
    }

    Dimension GetMenuNormalWidth() const
    {
        return optionNormalWidth_;
    }

    Dimension GetSelectFontSizeText() const
    {
        return selectedFontSizeText;
    }

    Dimension GetSelectNormalLeftRightMargin() const
    {
        return selectNormalLeftRightMargin_;
    }

    bool GetMenuBlendBgColor() const
    {
        return menuBlendBgColor_;
    }

    Dimension GetOptionFocusedBoxPadding() const
    {
        return optionFocusedBoxPadding_;
    }

    Color GetSpinnerFocusedSymbolColor() const
    {
        return spinnerFocusedSymbolColor_;
    }

    Color GetSpinnerFocusedColor() const
    {
        return spinnerFocusedColor_;
    }

    bool GetoptionApplyFocusedStyle() const
    {
        return optionApplyFocusedStyle_;
    }

    bool GetScrollSlideMoreOffset() const
    {
        return isSlideMoreOffset_;
    }

    Dimension GetDefaultDividerStartMargin() const
    {
        return defaultDividerStartMargin_;
    }

    Dimension GetDefaultDividerEndMargin() const
    {
        return defaultDividerEndMargin_;
    }

    bool GetDefaultShowDivider() const
    {
        return defaultShowDivider_;
    }

    Dimension GetMenuItemTopBottomMargin() const
    {
        return menuItemTopBottomMargin_;
    }

    Dimension GetMenuItemLeftRightMargin() const
    {
        return menuItemLeftRightMargin_;
    }

    Dimension GetMenuTargetSecuritySpace() const
    {
        return menuTargetSecuritySpace_;
    }

    Color GetMenuItemFocusedBgColor() const
    {
        return menuItemFocusedBgColor_;
    }

    Color GetMenuItemFocusedTextColor() const
    {
        return menuItemFocusedTextColor_;
    }

    uint32_t GetMenuItemFocusedShadowStyle() const
    {
        return menuItemFocusedShadowStyle_;
    }

    double GetSelectFocusStyleType_() const
    {
        return selectFocusStyleType_;
    }

    double GetOptionFocusStyleType_() const
    {
        return optionFocusStyleType_;
    }

    int GetMenuBackgroundBlurStyle() const
    {
        return menuBackgroundBlurStyle_;
    }

    WordBreak GetWordBreak() const
    {
        return menuWordBreak_;
    }
    
    int32_t GetMenuAnimationDuration() const
    {
        return menuAnimationDuration_;
    }

    double GetMenuAnimationScale() const
    {
        return menuAnimationScale_;
    }

    RefPtr<Curve> GetMenuAnimationCurve() const
    {
        if (menuAnimationCurve_ == "smooth") {
            return Curves::SMOOTH;
        } else {
            return Curves::FAST_OUT_SLOW_IN;
        }
    }

private:
    Color disabledColor_;
    Color clickedColor_;
    Color selectedColor_;

    Color backgroundColor_ = Color::WHITE;
    Color backgroundColorButton_ = Color::WHITE;
    Color disabledBackgroundColor_;
    Color hoverColor_ = Color(0x0c000000);
    Color selectedColorText_ = Color(0xff0a59f7);
    Color lineColor_ = Color(0x33000000);
    Color spinnerColor_ = Color(0xE5182431);
    Color disabledSpinnerColor_;
    Color spinnerSymbolColor_ = Color(0xff182431);
    Color disabledSpinnerSymbolColor_;
    uint32_t spinnerSource_ = 983615;
    uint32_t checkMarkIconId_ = 0;
    Color menuIconColor_ = Color(0x99182431);
    Color menuFontColor_;
    Color disabledMenuFontColor_;
    Color menuTitleFontColor_;

    bool allowScale_ = true;
    Dimension fontSize_;
    Color fontColor_;
    Color disabledFontColor_;
    double disabledFontColorAlpha_ = 0.0;
    Color secondaryFontColor_;
    std::string fontFamily_;
    FontWeight fontWeight_ { FontWeight::NORMAL };
    FontWeight checkMarkFontWeight_ { FontWeight::REGULAR };
    TextDecoration textDecoration_ { TextDecoration::NONE };

    std::size_t optionSize_ { 0 };
    Dimension rrectSize_;
    Dimension iconSize_;
    Dimension normalPadding_;

    Dimension popupRRectSize_;
    Dimension popupBorderWidth_;
    Dimension popupShadowWidth_;
    Dimension popupMinWidth_;

    Dimension titleLeftPadding_;
    Dimension titleTopPadding_;
    Dimension titleRightPadding_;
    Dimension titleBottomPadding_;
    Dimension horizontalSpacing_;
    Dimension verticalSpacing_;
    Dimension contentSpacing_;
    Dimension optionInterval_;
    Dimension optionMinHeight_;

    Dimension selectBorderRadius_;
    Dimension menuBorderRadius_;
    Dimension innerBorderRadius_;
    Dimension menuFontSize_;
    Dimension menuTitleFontSize_;
    Dimension menuTitleHeight_;
    Dimension menuIconPadding_;
    Dimension menuItemHorIntervalPadding_;
    Dimension menuPadding_;
    Dimension iconContentPadding_;
    Dimension dividerPaddingVertical_;

    Dimension selectMenuPadding_;
    Dimension outPadding_;
    Dimension defaultPaddingStart_;
    Dimension defaultPaddingEnd_;
    Dimension defaultPaddingTop_;
    Dimension defaultPaddingBottomFixed_;
    Dimension contentSpinnerPadding_;
    Dimension menuAnimationOffset_;
    Dimension spinnerWidth_;
    Dimension spinnerHeight_;
    Dimension defaultDividerWidth_;

    Dimension selectMinWidth_;
    Dimension selectDefaultHeight_;
    Dimension iconSideLength_;
    Dimension endIconWidth_;
    Dimension endIconHeight_;
    Dimension contentMargin_;
    Dimension checkMarkFontSize_;

    Color tvFocusTextColor_;
    Color tvNormalBackColor_;
    Color tvBackColor_;

    Color focusedDisableColor_;
    Color normalDisableColor_;
    Color focusedTextDisableColor_;
    Color normalTextDisableColor_;
    Color checkMarkColor_;

    TextStyle titleStyle_;
    TextStyle optionTextStyle_;
    bool isTV_ = false;
    uint32_t menuShowTime_ = 0;
    uint32_t selectShowTime_ = 0;
    uint32_t menuHideTime_ = 0;
    uint32_t selectHideTime_ = 0;
    int32_t hoverAnimationDuration_ = 0;
    int32_t pressAnimationDuration_ = 0;

    Edge optionPadding_;

    Color selectDefaultBgColor_;
    Dimension selectDefaultBorderRadius_;
    bool expandDisplay_ = false;
    Dimension maxPaddingStart_;
    Dimension maxPaddingEnd_;
    std::unordered_map<ControlSize, Dimension> selectMinWidthMap_;
    std::unordered_map<ControlSize, Dimension> selectMinHeightMap_;
    std::unordered_map<ControlSize, Dimension> selectBorderRadiusMap_;
    std::unordered_map<ControlSize, Dimension> selectSpinnerWidthMap_;
    std::unordered_map<ControlSize, Dimension> selectSpinnerHeightMap_;
    std::unordered_map<ControlSize, Dimension> selectFontSizeMap_;
    Dimension menuLargeMargin_;
    Dimension menuMediumMargin_;
    Dimension menuItemChildMinHeight_;
    Dimension menuItemVerticalPadding_;
    Dimension menuItemGroupTitleTextFontSize_;
    Dimension menuDefaultRadius_;
    Dimension menuDefaultInnerRadius_;
    Dimension menuDefaultWidth_;
    Dimension menuMinWidth_;
    Dimension menuMaxWidth_;
    double menuMaxWidthRatio_;
    Color menuTextColor_;
    uint32_t menuItemContentAlign_ = CONTENT_ALIGN_LEFT;
    Dimension selectNormalBorderWidth_;
    Color selectNormalBorderColor_;
    Color selectFocusedTextColor_;
    Color selectFocusedBackgroundColor_;
    ShadowStyle selectNormalShadow_;
    ShadowStyle selectFocusedShadow_;
    double selectHoverOrFocusedScale_;
    Dimension menuNormalBorderWidth_;
    Color menuNormalBorderColor_;
    int menuNormalBackgroundBlurStyle_;
    Dimension optionNormalTopBottomMargin_;
    Dimension optionContentNormalLeftRightPadding_;
    uint32_t optionContentNormalAlign_;
    Dimension optionFocusedLeftRightMargin_;
    Color optionFocusedBackgroundColor_;
    uint32_t optionFocusedShadow_;
    Color optionFocusedFontColor_;
    uint32_t shadowNormal_;  // no shadow
    Color optionSelectedBorderColor_;
    Dimension optionSelectedBorderWidth_;
    Dimension optionNormalWidth_;
    Dimension selectedFontSizeText;
    Dimension selectNormalLeftRightMargin_  = 8.0_vp;
    bool menuBlendBgColor_ = false;
    Dimension optionFocusedBoxPadding_ = 0.0_vp;
    Color spinnerFocusedSymbolColor_ = Color(0xff182431);
    Color spinnerFocusedColor_ = Color(0xE5182431);
    bool optionApplyFocusedStyle_ = false;
    bool isSlideMoreOffset_ = false;
    bool defaultShowDivider_ = false;
    uint32_t menuItemFocusedShadowStyle_;
    Dimension defaultDividerStartMargin_;
    Dimension defaultDividerEndMargin_;
    Dimension menuItemTopBottomMargin_;
    Dimension menuItemLeftRightMargin_;
    Dimension menuTargetSecuritySpace_;
    Color menuItemFocusedBgColor_;
    Color menuItemFocusedTextColor_;
    double selectFocusStyleType_ = 0.0;
    double optionFocusStyleType_ = 0.0;
    bool menuItemNeedFocus_ = false;
    int menuBackgroundBlurStyle_ = static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK);
    WordBreak menuWordBreak_ = WordBreak::BREAK_WORD;
    int32_t menuAnimationDuration_ = 0;
    double menuAnimationScale_ = 0.6;
    std::string menuAnimationCurve_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SELECT_SELECT_THEME_H
