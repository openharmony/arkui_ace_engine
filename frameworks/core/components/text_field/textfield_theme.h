/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXTFIELD_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXTFIELD_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/radius.h"
#include "core/components/swiper/render_swiper.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace {

/**
 * TextFieldTheme defines color and styles of SliderComponent. TextFieldTheme should be built
 * using TextFieldTheme::Builder.
 */
class TextFieldTheme : public virtual Theme {
    DECLARE_ACE_TYPE(TextFieldTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<TextFieldTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<TextFieldTheme> theme = AceType::Claim(new TextFieldTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    protected:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<TextFieldTheme>& theme) const
        {
            theme->height_ = themeConstants->GetDimension(THEME_TEXTFIELD_HEIGHT);
            theme->showSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.eye");
            theme->hideSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.eye_slash");
            theme->cancelSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.xmark");
            auto themeStyle = themeConstants->GetThemeStyle();
            if (!themeStyle || !theme) {
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>("textfield_pattern", nullptr);
            if (!pattern) {
                LOGW("find pattern of textfield fail");
                return;
            }
            ParsePatternSubFirstPart(pattern, theme);
            ParsePatternSubSecondPart(pattern, theme);
            ParsePatternSubThirdPart(pattern, theme);
            ParsePatternSubFourthPart(pattern, theme);
        }
    private:
        void ParsePatternSubFirstPart(const RefPtr<ThemeStyle>& pattern, const RefPtr<TextFieldTheme>& theme) const
        {
            theme->padding_ = Edge(pattern->GetAttr<Dimension>("textfield_padding_horizontal", 0.0_vp),
                pattern->GetAttr<Dimension>("textfield_padding_vertical", 0.0_vp),
                pattern->GetAttr<Dimension>("textfield_padding_horizontal", 0.0_vp),
                pattern->GetAttr<Dimension>("textfield_padding_vertical", 0.0_vp));
            theme->underlinePadding_ =
                Edge(pattern->GetAttr<Dimension>("textfield_underline_padding_horizontal", 0.0_vp),
                    pattern->GetAttr<Dimension>("textfield_underline_padding_vertical", 12.0_vp),
                    pattern->GetAttr<Dimension>("textfield_underline_padding_horizontal", 0.0_vp),
                    pattern->GetAttr<Dimension>("textfield_underline_padding_vertical", 12.0_vp));
            theme->fontWeight_ =
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_font_weight", 0.0)));
            theme->borderRadius_ = Radius(pattern->GetAttr<Dimension>("textfield_border_radius", 0.0_vp));
            theme->disableOpacityRatio_ = pattern->GetAttr<double>("textfield_disable_opacity_ratio", 0.0);
            theme->overHideLength_ = pattern->GetAttr<Dimension>("textfield_over_hide_length", 0.0_vp);
            theme->cursorRadius_ = pattern->GetAttr<Dimension>("textfield_cursor_radius", 0.0_vp);
            theme->needFade_ = static_cast<bool>(pattern->GetAttr<double>("textfield_need_fade", 0.0));
            theme->iconSize_ = pattern->GetAttr<Dimension>("textfield_icon_size", 0.0_vp);
            theme->iconHotZoneSize_ = pattern->GetAttr<Dimension>("textfield_icon_hot_zone_size", 0.0_vp);
            theme->symbolSize_ = pattern->GetAttr<Dimension>("textfield_icon_size", 0.0_vp);
            theme->symbolColor_ = pattern->GetAttr<Color>("textfield_symbol_color", Color());
            theme->showEllipsis_ = static_cast<bool>(pattern->GetAttr<double>("textfield_show_ellipsis", 0.0));
            theme->errorSpacing_ = pattern->GetAttr<Dimension>("textfield_error_spacing", 0.0_vp);
            theme->errorIsInner_ = static_cast<bool>(pattern->GetAttr<double>("textfield_error_is_inner", 0.0));
            theme->errorBorderWidth_ = pattern->GetAttr<Dimension>("textfield_error_border_width", 0.0_vp);
            theme->errorTextStyle_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_error_font_weight", 0.0))));
            theme->countTextStyle_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_count_font_weight", 0.0))));
            theme->overCountStyle_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_over_count_font_weight", 0.0))));
            theme->countTextStyleOuter_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_count_font_weight", 0.0))));
            theme->overCountStyleOuter_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_over_count_font_weight", 0.0))));
            theme->fontSize_ = pattern->GetAttr<Dimension>(PATTERN_TEXT_SIZE, 0.0_fp);
            theme->textColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color());
            theme->focusTextColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR_FOCUSED, Color());
            theme->placeholderColor_ = pattern->GetAttr<Color>("tips_text_color", Color());
            theme->focusPlaceholderColor_ = pattern->GetAttr<Color>("tips_text_color_focused", Color());
            theme->bgColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR, Color());
            theme->focusBgColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_FOCUSED, Color());
            theme->glassOutlinePrimaryColor_ =
                pattern->GetAttr<Color>("glass_material_outline_primary", Color(0xffffff));
            theme->glassOutlineSecondaryColor_ =
                pattern->GetAttr<Color>("glass_material_outline_secondary", Color(0xf0f0f0));
            theme->glassMaskPrimaryColor_ = pattern->GetAttr<Color>("glass_material_mask_primary", Color(0x00808080));
            theme->glassMaskSecondaryColor_ =
                pattern->GetAttr<Color>("glass_material_mask_secondary", Color(0x26808080));
        }

        void ParsePatternSubSecondPart(const RefPtr<ThemeStyle>& pattern, const RefPtr<TextFieldTheme>& theme) const
        {
            const double defaultErrorAlpha = 0.6;
            const double defaultUnderlineAlpha = 0.6;
            const double defaultDisableUnderlineAlpha = 0.4;
            const Color defaultUnderlineColor = Color(0x33182431);
            const Color defaultUnderlineTextColor = Color(0x99182431);
            const Color defaultCounterColor = Color(0x66182431);
            const Color overCounterColor = Color(0x99FA2A2D);
            // color of error border blend 60% opacity
            theme->errorBorderColor_ =
                pattern->GetAttr<Color>("error_text_border_color", Color())
                    .BlendOpacity(pattern->GetAttr<double>("error_text_border_color_alpha", defaultErrorAlpha));
            theme->errorUnderlineColor_ = pattern->GetAttr<Color>(ERROR_UNDERLINE_COLOR, Color());
            theme->underlineColor_ = pattern->GetAttr<Color>(UNDERLINE_COLOR, defaultUnderlineColor);
            theme->disableUnderlineColor_ =
                pattern->GetAttr<Color>(UNDERLINE_COLOR, defaultUnderlineColor)
                    .BlendOpacity(pattern->GetAttr<double>(DISABLE_UNDERLINE_ALPHA, defaultDisableUnderlineAlpha));
            theme->underlineTextColor_ = pattern->GetAttr<Color>(UNDERLINE_TEXT_COLOR, defaultUnderlineTextColor);
            theme->defaultCounterColor_ = pattern->GetAttr<Color>(DEFAULT_COUNTER_COLOR, defaultCounterColor);
            theme->overCounterColor_ = pattern->GetAttr<Color>(OVER_COUNTER_COLOR, overCounterColor);
            theme->underlineFontSize_ = pattern->GetAttr<Dimension>(UNDERLINE_FONT_SIZE, 0.0_fp);
            theme->errorTextStyle_.SetTextColor(pattern->GetAttr<Color>(ERROR_UNDERLINE_TEXT_COLOR, Color()));
            theme->errorTextStyle_.SetFontSize(pattern->GetAttr<Dimension>(ERROR_UNDERLINE_TEXT_SIZE, 0.0_fp));
            theme->errorTextAlign_ =
                static_cast<bool>(pattern->GetAttr<double>("textfield_error_text_align", 0.0));

            theme->countTextStyle_.SetTextColor(pattern->GetAttr<Color>("count_text_color", Color()));
            theme->countTextStyle_.SetFontSize(pattern->GetAttr<Dimension>("count_text_font_size", 0.0_fp));
            theme->overCountStyle_.SetTextColor(pattern->GetAttr<Color>("over_text_color", Color()));
            theme->overCountStyle_.SetFontSize(pattern->GetAttr<Dimension>("over_text_font_size", 0.0_fp));

            theme->countTextStyleOuter_.SetTextColor(pattern->GetAttr<Color>("count_outer_text_color", Color()));
            theme->countTextStyleOuter_.SetFontSize(pattern->GetAttr<Dimension>("count_outer_text_font_size", 0.0_fp));
            theme->overCountStyleOuter_.SetTextColor(pattern->GetAttr<Color>("over_outer_text_color", Color()));
            theme->overCountStyleOuter_.SetFontSize(pattern->GetAttr<Dimension>("over_outer_text_font_size", 0.0_fp));
            theme->overCountTextStyle_.SetTextColor(pattern->GetAttr<Color>(OVER_COUNT_TEXT_COLOR, Color()));
            theme->overCountTextStyle_.SetFontSize(pattern->GetAttr<Dimension>(OVER_COUNT_TEXT_FONT_SIZE, 0.0_fp));
            theme->selectedColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_SELECTED, Color());
            theme->disableTextColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR_DISABLED, Color());
            theme->underlineActivedColor_ =
                pattern->GetAttr<Color>(PATTERN_UNDERLINE_ACTIVED_COLOR, Color())
                    .BlendOpacity(pattern->GetAttr<double>(UNDERLINE_COLOR_ALPHA, defaultUnderlineAlpha));
            theme->underlineTypingColor_ =
                pattern->GetAttr<Color>(PATTERN_UNDERLINE_TYPING_COLOR, Color())
                    .BlendOpacity(pattern->GetAttr<double>(UNDERLINE_COLOR_ALPHA, defaultUnderlineAlpha));
        }

        void ParsePatternSubThirdPart(const RefPtr<ThemeStyle>& pattern, const RefPtr<TextFieldTheme>& theme) const
        {
            const double defaultErrorAlpha = 0.6;
            theme->textColorDisable_ = pattern->GetAttr<Color>(PATTERN_DISABLED_TEXT_COLOR, Color());
            theme->cursorColor_ = pattern->GetAttr<Color>("cursor_color", Color());
            theme->cursorWidth_ = pattern->GetAttr<Dimension>("cursor_width", 2.0_vp);
            theme->hoverColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_HOVERED, Color());
            theme->pressColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_PRESSED, Color());
            theme->borderRadiusSize_ = Radius(pattern->GetAttr<Dimension>(BORDER_RADIUS_SIZE, 20.0_vp));
            theme->disabledIconFillColor_ = theme->bgColor_.BlendOpacity(theme->disableOpacityRatio_);
            theme->passwordErrorTextColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color());
            theme->passwordErrorInputColor_ = pattern->GetAttr<Color>(ERROR_PASSWORD_INPUT_COLOR, Color());
            theme->passwordErrorBorderColor_ =
                pattern->GetAttr<Color>(ERROR_PASSWORD_BORDER_COLOR, Color())
                    .BlendOpacity(pattern->GetAttr<double>(ERROR_PASSWORD_BORDER_ALPHA, defaultErrorAlpha));
            theme->passwordErrorLableColor_ = pattern->GetAttr<Color>(ERROR_PASSWORD_TEXT_COLOR, Color());
            theme->overCountBorderColor_ =
                pattern->GetAttr<Color>(OVER_COUNT_BORDER_COLOR, Color())
                    .BlendOpacity(pattern->GetAttr<double>(OVER_COUNT_BORDER_COLOR_ALPHA, defaultErrorAlpha));
            theme->inlineTextColor_ = pattern->GetAttr<Color>(INLINE_TEXT_COLOR, Color());
            theme->inlineRadiusSize_ = Radius(pattern->GetAttr<Dimension>(INLINE_RADIUS_SIZE, 4.0_vp));
            theme->inlineBgColor_ = pattern->GetAttr<Color>(INLINE_BG_COLOR, Color());
            theme->inlineBorderColor_ = pattern->GetAttr<Color>(INLINE_BORDER_COLOR, Color());
            auto draggable = pattern->GetAttr<std::string>("draggable", "0");
            theme->draggable_ = StringUtils::StringToInt(draggable);
            theme->height_ = pattern->GetAttr<Dimension>("textinput_default_height", 24.0_vp);
            theme->contentHeight_ = pattern->GetAttr<Dimension>("textfield_content_height", 0.0_vp);
            auto showPasswordDirectly = pattern->GetAttr<std::string>("show_password_directly", "0");
            theme->showPasswordDirectly_ = StringUtils::StringToInt(showPasswordDirectly);
            auto textfieldShowHandle = pattern->GetAttr<std::string>("textfield_show_handle", "0");
            theme->textfieldShowHandle_ = StringUtils::StringToInt(textfieldShowHandle);

            theme->cancelButtonIconColor_ = pattern->GetAttr<Color>("textfield_symbol_color", Color());
            theme->previewUnderlineColor_ = pattern->GetAttr<Color>(PREVIEW_UNDERLINE_COLOR, Color());
            theme->previewBoardColor_ = pattern->GetAttr<Color>(PREVIEW_BOARD_COLOR, Color());

            theme->placeholderLineSpacing_ = pattern->GetAttr<Dimension>("text_field_placeholder_linespacing", 0.0_vp);

            theme->cancelButton_ = pattern->GetAttr<std::string>("textfield_accessibility_clear", "");
            theme->cancelImageText_ = pattern->GetAttr<std::string>("textfield_accessibility_property_clear", "");
            theme->showPassword_ = pattern->GetAttr<std::string>("textfield_show_password_button", "");
            theme->hidePassword_ = pattern->GetAttr<std::string>("textfield_hide_password_button", "");
            theme->hasShowedPassword_ = pattern->GetAttr<std::string>("textfield_has_showed_password", "");
            theme->hasHiddenPassword_ = pattern->GetAttr<std::string>("textfield_has_hidden_password", "");
            theme->aiWriteBundleName_ = pattern->GetAttr<std::string>("textfield_writting_bundle_name", "");
            theme->aiWriteAbilityName_ = pattern->GetAttr<std::string>("textfield_writting_ability_name", "");
            theme->aiWriteIsSupport_ = pattern->GetAttr<std::string>("textfield_writting_is_support", "");

            theme->inlinePaddingLeft_ = pattern->GetAttr<Dimension>("inline_padding_left", 2.0_vp);
            theme->inlinePaddingRight_ = pattern->GetAttr<Dimension>("inline_padding_right", 12.0_vp);
            auto supportTranslate = pattern->GetAttr<std::string>("menu_translate_is_support", "0");
            theme->translateIsSupport_ = StringUtils::StringToInt(supportTranslate);
            auto supportSearch = pattern->GetAttr<std::string>("textfield_menu_search_is_support", "0");
            theme->supportSearch_ = StringUtils::StringToInt(supportSearch);
        }

        void ParsePatternSubFourthPart(const RefPtr<ThemeStyle>& pattern, const RefPtr<TextFieldTheme>& theme) const
        {
            std::string isTextFadeout = pattern->GetAttr<std::string>("text_fadeout_enable", "");
            theme->textFadeoutEnabled_ = isTextFadeout == "true";
            theme->textInputBorderColor_ = pattern->GetAttr<Color>("text_input_border_color", Color());
            theme->textInputBorderWidth_ = pattern->GetAttr<Dimension>("text_input_border_width", 0.0_vp);
            theme->errorTextInputBorderWidth_ = pattern->GetAttr<Dimension>("error_text_input_border_width", 1.0_vp);
            theme->showPasswordIcon_ = static_cast<bool>(pattern->GetAttr<double>("show_icon_text_input", 1.0));
            theme->hoverAndPressBgColorEnabled_ =
                static_cast<uint32_t>(pattern->GetAttr<int>("textfield_hover_press_bg_color_enabled", 0));
            theme->needFocusBox_ = static_cast<bool>(pattern->GetAttr<double>("text_input_need_focus_box", 0.0));
            theme->focusPadding_ = pattern->GetAttr<Dimension>("text_input_focus_padding", 0.0_vp);
            theme->independentControlKeyboard_ =
                static_cast<bool>(pattern->GetAttr<double>("independent_control_keyboard", 0.0));
            theme->directionKeysMoveFocusOut_ =
                static_cast<bool>(pattern->GetAttr<double>("direction_keys_move_focus_out", 0.0));
        }
    };

    ~TextFieldTheme() override = default;

    const Edge& GetPadding() const
    {
        return padding_;
    }

    const Edge& GetUnderlinePadding() const
    {
        return underlinePadding_;
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    const Dimension& GetContentHeight() const
    {
        return contentHeight_;
    }

    const Dimension& GetFontSize() const
    {
        return fontSize_;
    }

    const Dimension& GetUnderlineFontSize() const
    {
        return underlineFontSize_;
    }

    const FontWeight& GetFontWeight() const
    {
        return fontWeight_;
    }

    const Radius& GetBorderRadius() const
    {
        return borderRadius_;
    }

    const Color& GetBgColor() const
    {
        return bgColor_;
    }

    const Color& GetPlaceholderColor() const
    {
        return placeholderColor_;
    }

    const Color& GetFocusBgColor() const
    {
        return focusBgColor_;
    }

    const Color& GetFocusPlaceholderColor() const
    {
        return focusPlaceholderColor_;
    }

    const Color& GetFocusTextColor() const
    {
        return focusTextColor_;
    }

    const Color& GetTextColor() const
    {
        return textColor_;
    }

    const Color& GetDisableTextColor() const
    {
        return disableTextColor_;
    }

    const Color& GetTextColorDisable() const
    {
        return textColorDisable_;
    }

    const Color& GetUnderlineActivedColor() const
    {
        return underlineActivedColor_;
    }

    const Color& GetUnderlineTypingColor() const
    {
        return underlineTypingColor_;
    }

    const Color& GetSelectedColor() const
    {
        return selectedColor_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetPressColor() const
    {
        return pressColor_;
    }

    const Radius& GetBorderRadiusSize() const
    {
        return borderRadiusSize_;
    }

    double GetDisableOpacityRatio() const
    {
        return disableOpacityRatio_;
    }

    const Color& GetDisabledIconFillColor() const
    {
        return disabledIconFillColor_;
    }

    const Dimension& GetOverHideLength() const
    {
        return overHideLength_;
    }

    const Color& GetCursorColor() const
    {
        return cursorColor_;
    }

    const Dimension& GetCursorRadius() const
    {
        return cursorRadius_;
    }

    const Dimension& GetCursorWidth() const
    {
        return cursorWidth_;
    }

    bool NeedFade() const
    {
        return needFade_;
    }

    const Dimension& GetIconSize() const
    {
        return iconSize_;
    }

    const Dimension& GetCancelIconSize() const
    {
        return cancelIconSize_;
    }

    const Dimension& GetPasswordIconSize() const
    {
        return passwordIconSize_;
    }

    const Dimension& GetCancelIconPadding() const
    {
        return cancelIconPadding_;
    }

    const Dimension& GetPasswordIconPadding() const
    {
        return passwordIconPadding_;
    }

    const Dimension& GetIconHotZoneSize() const
    {
        return iconHotZoneSize_;
    }

    const Dimension& GetSymbolSize() const
    {
        return symbolSize_;
    }

    const Color& GetSymbolColor() const
    {
        return symbolColor_;
    }

    uint32_t GetShowSymbolId() const
    {
        return showSymbolId_;
    }

    uint32_t GetHideSymbolId() const
    {
        return hideSymbolId_;
    }

    uint32_t GetCancelSymbolId() const
    {
        return cancelSymbolId_;
    }

    bool ShowEllipsis() const
    {
        return showEllipsis_;
    }

    const Dimension& GetErrorSpacing() const
    {
        return errorSpacing_;
    }

    bool GetErrorIsInner() const
    {
        return errorIsInner_;
    }

    bool GetIndependentControlKeyboard() const
    {
        return independentControlKeyboard_;
    }

    bool GetDirectionKeysMoveFocusOut() const
    {
        return directionKeysMoveFocusOut_;
    }

    const Dimension& GetErrorBorderWidth() const
    {
        return errorBorderWidth_;
    }

    const Color& GetErrorBorderColor() const
    {
        return errorBorderColor_;
    }

    const Color& GetErrorUnderlineColor() const
    {
        return errorUnderlineColor_;
    }

    const Color& GetUnderlineColor() const
    {
        return underlineColor_;
    }

    const Color& GetDisableUnderlineColor() const
    {
        return disableUnderlineColor_;
    }

    const Color& GetUnderlineTextColor() const
    {
        return underlineTextColor_;
    }

    const Color& GetOverCountBorderColor() const
    {
        return overCountBorderColor_;
    }

    TextStyle GetTextStyle() const
    {
        return textStyle_;
    }

    const TextStyle& GetErrorTextStyle() const
    {
        return errorTextStyle_;
    }

    const TextStyle& GetCountTextStyle() const
    {
        return countTextStyle_;
    }

    const TextStyle& GetOverCountStyle() const
    {
        return overCountStyle_;
    }

    const TextStyle& GetCountTextStyleOuter() const
    {
        return countTextStyleOuter_;
    }

    const TextStyle& GetOverCountStyleOuter() const
    {
        return overCountStyleOuter_;
    }

    const Color& GetPasswordErrorTextColor() const
    {
        return passwordErrorTextColor_;
    }

    const Color& GetPasswordErrorInputColor() const
    {
        return passwordErrorInputColor_;
    }

    const Color& GetPasswordErrorBorderColor() const
    {
        return passwordErrorBorderColor_;
    }

    const Color& GetPasswordErrorLableColor() const
    {
        return passwordErrorLableColor_;
    }

    const TextStyle& GetOverCountTextStyle() const
    {
        return overCountTextStyle_;
    }

    const Color& GetInlineTextColor() const
    {
        return inlineTextColor_;
    }

    const Radius& GetInlineRadiusSize() const
    {
        return inlineRadiusSize_;
    }

    const Color& GetInlineBgColor() const
    {
        return inlineBgColor_;
    }

    const Color& GetInlineBorderColor() const
    {
        return inlineBorderColor_;
    }

    const Dimension& GetInlineBorderWidth() const
    {
        return inlineBorderWidth_;
    }

    bool GetDraggable() const
    {
        return draggable_;
    }

    const Color& GetDefaultCounterColor() const
    {
        return defaultCounterColor_;
    }

    const Color& GetOverCounterColor() const
    {
        return overCounterColor_;
    }

    const Color& GetGlassOutlinePrimaryColor() const
    {
        return glassOutlinePrimaryColor_;
    }

    const Color& GetGlassOutlineSecondaryColor() const
    {
        return glassOutlineSecondaryColor_;
    }

    const Color& GetGlassMaskPrimaryColor() const
    {
        return glassMaskPrimaryColor_;
    }

    const Color& GetGlassMaskSecondaryColor() const
    {
        return glassMaskSecondaryColor_;
    }

    const Dimension& GetInsertCursorOffset() const
    {
        return insertCursorOffset_;
    }

    const Dimension& GetPasswordTypeHeight() const
    {
        return passwordTypeHeight_;
    }

    bool IsShowPasswordDirectly() const
    {
        return showPasswordDirectly_;
    }

    bool IsTextFieldShowHandle() const
    {
        return textfieldShowHandle_;
    }

    const Dimension& GetAvoidKeyboardOffset() const
    {
        return avoidKeyboardOffset_;
    }

    const CancelButtonStyle& GetCancelButtonStyle() const
    {
        return cancelButtonStyle_;
    }

    const Color& GetCancelButtonIconColor() const
    {
        return cancelButtonIconColor_;
    }

    const Color& GetPreviewUnderlineColor() const
    {
        return previewUnderlineColor_;
    }

    const Color& GetPreviewBoardColor() const
    {
        return previewBoardColor_;
    }

    const std::string& GetCancelButton() const
    {
        return cancelButton_;
    }

    const std::string& GetCancelImageText() const
    {
        return cancelImageText_;
    }

    const Dimension& getInlinePaddingLeft() const
    {
        return inlinePaddingLeft_;
    }

    const Dimension& getInlinePaddingRight() const
    {
        return inlinePaddingRight_;
    }

    const Dimension& GetPlaceholderLineSpacing() const
    {
        return placeholderLineSpacing_;
    }

    const std::string& GetShowPasswordPromptInformation() const
    {
        return showPassword_;
    }

    const std::string& GetHiddenPasswordPromptInformation() const
    {
        return hidePassword_;
    }

    const std::string& GetHasShowedPassword() const
    {
        return hasShowedPassword_;
    }

    const std::string& GetHasHiddenPassword() const
    {
        return hasHiddenPassword_;
    }

    const std::string& GetAIWriteBundleName() const
    {
        return aiWriteBundleName_;
    }

    const std::string& GetAIWriteAbilityName() const
    {
        return aiWriteAbilityName_;
    }

    bool GetTranslateIsSupport() const
    {
        return translateIsSupport_;
    }

    bool GetIsSupportSearch() const
    {
        return supportSearch_;
    }

    const std::string& GetAIWriteIsSupport() const
    {
        return aiWriteIsSupport_;
    }

    const Dimension& GetCounterTextTopMargin() const
    {
        return counterTextTopMargin_;
    }

    const Dimension& GetCounterTextBottomMargin() const
    {
        return counterTextBottomMargin_;
    }

    const Dimension& GetStandardCounterTextMargin() const
    {
        return standardCounterTextMargin_;
    }

    const Dimension& GetErrorTextTopMargin() const
    {
        return errorTextTopMargin_;
    }

    const Dimension& GetErrorTextBottomMargin() const
    {
        return errorTextBottomMargin_;
    }

    const Dimension& GetCounterTextMarginOffset() const
    {
        return counterTextMarginOffset_;
    }

    const Dimension& GetErrorTextUnderlineMargin() const
    {
        return errorTextUnderlineMargin_;
    }

    const Dimension& GetErrorTextCapsuleMargin() const
    {
        return errorTextCapsuleMargin_;
    }

    float GetErrorTextMaxFontScale() const
    {
        return errorTextMaxFontScale_;
    }

    uint32_t GetCounterTextMaxline() const
    {
        return counterTextMaxline_;
    }

    uint32_t GetErrorTextMaxLine() const
    {
        return errorTextMaxLine_;
    }

    bool TextFadeoutEnabled() const
    {
        return textFadeoutEnabled_;
    }

    const Dimension& GetTextInputWidth() const
    {
        return textInputBorderWidth_;
    }

    const Color& GetTextInputColor() const
    {
        return textInputBorderColor_;
    }

    bool IsShowPasswordIcon() const
    {
        return showPasswordIcon_;
    }

    bool GetHoverAndPressBgColorEnabled() const
    {
        return hoverAndPressBgColorEnabled_;
    }

    const Dimension& GetErrorTextInputBorderWidth() const
    {
        return errorTextInputBorderWidth_;
    }

    bool NeedFocusBox() const
    {
        return needFocusBox_;
    }

    const Dimension& GetFocusPadding() const
    {
        return focusPadding_;
    }

    bool GetErrorTextCenter() const
    {
        return errorTextAlign_;
    }

protected:
    TextFieldTheme() = default;
    TextStyle textStyle_;
    Color textColor_;
    Color placeholderColor_;
    Color bgColor_;
    Color focusBgColor_;
    Color inlineBgColor_;
    Color cursorColor_;
    Color symbolColor_;
    Color textColorDisable_;

private:
    Edge padding_;
    Edge underlinePadding_;
    Dimension height_;
    Dimension contentHeight_;
    Dimension fontSize_;
    Dimension underlineFontSize_;
    FontWeight fontWeight_ = FontWeight::NORMAL;
    Radius borderRadius_;

    Radius borderRadiusSize_;
    Color focusPlaceholderColor_;
    Color focusTextColor_;
    Color disableTextColor_;
    Color underlineActivedColor_;
    Color underlineTypingColor_;
    Color selectedColor_;
    Color hoverColor_;
    Color pressColor_;
    Color disabledIconFillColor_;
    Dimension errorSpacing_;
    bool errorIsInner_ = false;
    Dimension errorBorderWidth_;
    Color errorBorderColor_;
    Color overCountBorderColor_;
    Color errorUnderlineColor_;
    Color underlineColor_;
    Color disableUnderlineColor_;
    Color underlineTextColor_;
    Color passwordErrorTextColor_;
    Color passwordErrorInputColor_;
    Color passwordErrorBorderColor_;
    Color passwordErrorLableColor_;
    TextStyle errorTextStyle_;
    TextStyle countTextStyle_;
    TextStyle overCountStyle_;
    TextStyle countTextStyleOuter_;
    TextStyle overCountStyleOuter_;
    TextStyle overCountTextStyle_;
    Color inlineTextColor_;
    Radius inlineRadiusSize_;
    Color inlineBorderColor_;
    Color defaultCounterColor_;
    Color overCounterColor_;
    Color glassOutlinePrimaryColor_;
    Color glassOutlineSecondaryColor_;
    Color glassMaskPrimaryColor_;
    Color glassMaskSecondaryColor_;

    // UX::disable state: opacity is set to 38% of the default
    double disableOpacityRatio_ = 1.0;

    // UX::over length state
    Dimension overHideLength_;

    // UX::cursor state cursor-color=#000000, cursor blur-radius=0.9, cursor-width=2, cursor-height=24, cursor-radius=1
    Dimension cursorRadius_;
    Dimension cursorWidth_;
    bool needFade_ = false;

    // UX::icon size = 24, hotZoneSize = 36
    Dimension iconSize_;
    Dimension iconHotZoneSize_;
    Dimension inlineBorderWidth_ = 2.0_vp;
    Dimension cancelIconSize_ = 16.0_vp;
    Dimension passwordIconSize_ = 20.0_vp;
    Dimension cancelIconPadding_ = 14.0_vp;
    Dimension passwordIconPadding_ = 10.0_vp;

    // Replace image(icon) with symbol
    Dimension symbolSize_;
    uint32_t showSymbolId_ = 0;
    uint32_t hideSymbolId_ = 0;
    uint32_t cancelSymbolId_ = 0;

    // UX::insert cursor offset up by 24vp
    Dimension insertCursorOffset_ = 24.0_vp;

    Dimension avoidKeyboardOffset_ = 24.0_vp;

    bool showEllipsis_ = true;
    bool draggable_ = false;
    bool showPasswordDirectly_ = false;
    bool textfieldShowHandle_ = false;
    bool translateIsSupport_ = false;
    bool supportSearch_ = false;
    Dimension passwordTypeHeight_ = 40.0_vp;

    // cancelButton
    Color cancelButtonIconColor_;
    CancelButtonStyle cancelButtonStyle_ = CancelButtonStyle::INPUT;
    Color previewUnderlineColor_;
    Color previewBoardColor_;

    bool textFadeoutEnabled_ = false;
    Dimension textInputBorderWidth_ = 0.0_vp;
    Dimension errorTextInputBorderWidth_ = 1.0_vp;
    Color textInputBorderColor_;
    bool showPasswordIcon_ = true;
    bool hoverAndPressBgColorEnabled_ = false;
    bool independentControlKeyboard_ = false;
    bool directionKeysMoveFocusOut_ = false;

    std::string cancelButton_;

    Dimension inlinePaddingLeft_ = 0.0_vp;
    Dimension inlinePaddingRight_ = 0.0_vp;
    Dimension placeholderLineSpacing_ = 0.0_vp;

    Dimension counterTextTopMargin_ = 8.0_vp;
    Dimension counterTextBottomMargin_ = 8.0_vp;
    Dimension standardCounterTextMargin_ = 22.0_vp;
    Dimension errorTextTopMargin_ = 8.0_vp;
    Dimension errorTextBottomMargin_ = 8.0_vp;
    Dimension counterTextMarginOffset_ = 8._vp;
    Dimension errorTextUnderlineMargin_ = 8.0_vp;
    Dimension errorTextCapsuleMargin_ = 8.0_vp;
    
    float errorTextMaxFontScale_ = 2.0f;
    uint32_t counterTextMaxline_ = 1;
    uint32_t errorTextMaxLine_ = 1;

    bool errorTextAlign_ = false;

    std::string hasShowedPassword_;
    std::string hasHiddenPassword_;
    std::string showPassword_;
    std::string hidePassword_;
    std::string aiWriteBundleName_;
    std::string aiWriteAbilityName_;
    std::string aiWriteIsSupport_;
    std::string cancelImageText_;
    bool needFocusBox_ = false;
    Dimension focusPadding_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXTFIELD_THEME_H
