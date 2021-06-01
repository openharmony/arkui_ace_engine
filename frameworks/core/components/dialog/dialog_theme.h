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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DIALOG_DIALOG_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DIALOG_DIALOG_THEME_H

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/radius.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

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
            theme->radius_ = Radius(
                themeConstants->GetDimension(THEME_DIALOG_RADIUS), themeConstants->GetDimension(THEME_DIALOG_RADIUS));
            theme->backgroundColor_ = themeConstants->GetColor(THEME_DIALOG_BACKGROUND_COLOR);
            theme->titleTextStyle_.SetTextColor(themeConstants->GetColor(THEME_DIALOG_TITLE_TEXT_COLOR));
            theme->titleTextStyle_.SetFontSize(themeConstants->GetDimension(THEME_DIALOG_TITLE_TEXT_FONTSIZE));
            theme->titleTextStyle_.SetFontWeight(
                FontWeight(themeConstants->GetInt(THEME_DIALOG_TITLE_TEXT_FONTWEIGHT)));
            theme->titleMinFontSize_ = themeConstants->GetDimension(THEME_DIALOG_TITLE_TEXT_FONTSIZE_MIN);
            theme->contentMinFontSize_ = themeConstants->GetDimension(THEME_DIALOG_CONTENT_TEXT_FONTSIZE_MIN);
            auto titleMaxLines = themeConstants->GetInt(THEME_DIALOG_TITLE_TEXT_MAX_LINES);
            theme->titleMaxLines_ = titleMaxLines < 0 ? theme->titleMaxLines_ : static_cast<uint32_t>(titleMaxLines);
            theme->contentTextStyle_.SetTextColor(themeConstants->GetColor(THEME_DIALOG_CONTENT_TEXT_COLOR));
            theme->contentTextStyle_.SetFontSize(themeConstants->GetDimension(THEME_DIALOG_CONTENT_TEXT_FONTSIZE));
            theme->defaultPadding_ = Edge(themeConstants->GetDimension(THEME_DIALOG_PADDING_LEFT),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_TOP),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_RIGHT),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_BOTTOM));
            theme->adjustPadding_ = Edge(themeConstants->GetDimension(THEME_DIALOG_PADDING_LEFT_ADJUST),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_TOP_ADJUST),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_RIGHT_ADJUST),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_BOTTOM_ADJUST));
            theme->titleDefaultPadding_ = Edge(themeConstants->GetDimension(THEME_DIALOG_PADDING_LEFT),
                themeConstants->GetDimension(THEME_DIALOG_TITLE_PADDING_VERTICAL),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_RIGHT),
                themeConstants->GetDimension(THEME_DIALOG_TITLE_PADDING_VERTICAL));
            theme->titleAdjustPadding_ = Edge(themeConstants->GetDimension(THEME_DIALOG_PADDING_LEFT_ADJUST),
                themeConstants->GetDimension(THEME_DIALOG_TITLE_PADDING_VERTICAL),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_RIGHT_ADJUST),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_BOTTOM_ADJUST));
            theme->contentDefaultPadding_ = Edge(themeConstants->GetDimension(THEME_DIALOG_PADDING_LEFT),
                themeConstants->GetDimension(THEME_DIALOG_TITLE_PADDING_VERTICAL),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_RIGHT),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_BOTTOM));
            theme->contentAdjustPadding_ = Edge(themeConstants->GetDimension(THEME_DIALOG_PADDING_LEFT_ADJUST),
                themeConstants->GetDimension(THEME_DIALOG_TITLE_PADDING_VERTICAL),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_RIGHT_ADJUST),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_BOTTOM_ADJUST));
            theme->actionsPadding_ = Edge(themeConstants->GetDimension(THEME_DIALOG_PADDING_ACTIONS_LEFT),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_ACTIONS_TOP),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_ACTIONS_RIGHT),
                themeConstants->GetDimension(THEME_DIALOG_PADDING_ACTIONS_BOTTOM));
            theme->buttonPaddingLeft_ =
                Edge(themeConstants->GetDimension(THEME_DIALOG_PADDING_MIN).Value(), 0.0, 0.0, 0.0, DimensionUnit::VP);
            theme->buttonPaddingRight_ =
                Edge(0.0, 0.0, themeConstants->GetDimension(THEME_DIALOG_PADDING_MIN).Value(), 0.0, DimensionUnit::VP);
            theme->buttonPaddingCenter_ = Edge(0.0, themeConstants->GetDimension(THEME_DIALOG_PADDING_MID).Value(), 0.0,
                themeConstants->GetDimension(THEME_DIALOG_PADDING_MID).Value(), DimensionUnit::VP);
            theme->buttonSpacingHorizontal_ = themeConstants->GetDimension(THEME_DIALOG_BUTTON_SPACING_HORIZONTAL);
            theme->buttonSpacingVertical_ = themeConstants->GetDimension(THEME_DIALOG_BUTTON_SPACING_VERTICAL);
            theme->buttonBackgroundColor_ = themeConstants->GetColor(THEME_DIALOG_BUTTON_BG_COLOR);
            theme->buttonClickedColor_ = themeConstants->GetColor(THEME_DIALOG_BUTTON_CLICKED_COLOR);
            theme->frameStart_ = themeConstants->GetDouble(THEME_DIALOG_FRAME_START);
            theme->frameEnd_ = themeConstants->GetDouble(THEME_DIALOG_FRAME_END);
            theme->scaleStart_ = themeConstants->GetDouble(THEME_DIALOG_SCALE_START);
            theme->scaleEnd_ = themeConstants->GetDouble(THEME_DIALOG_SCALE_END);
            theme->opacityStart_ = themeConstants->GetDouble(THEME_DIALOG_OPACITY_START);
            theme->opacityEnd_ = themeConstants->GetDouble(THEME_DIALOG_OPACITY_END);
            theme->maskColorStart_ = themeConstants->GetColor(THEME_DIALOG_MASK_COLOR_START);
            theme->maskColorEnd_ = themeConstants->GetColor(THEME_DIALOG_MASK_COLOR_END);
            theme->animationDurationIn_ = themeConstants->GetInt(THEME_DIALOG_ANIMATION_DURATION_IN);
            theme->animationDurationOut_ = themeConstants->GetInt(THEME_DIALOG_ANIMATION_DURATION_OUT);
            theme->translateValue_ = Dimension(themeConstants->GetDouble(THEME_DIALOG_TRANSLATE), DimensionUnit::PX);
            theme->dividerColor_ = themeConstants->GetColor(THEME_DIALOG_DIVIDER_COLOR);
            theme->dividerWidth_ = themeConstants->GetDimension(THEME_DIALOG_DIVIDER_WIDTH);
            theme->dividerHeight_ = themeConstants->GetDimension(THEME_DIALOG_DIVIDER_HEIGHT);
            theme->dividerPadding_ = Edge(themeConstants->GetDimension(THEME_DIALOG_DIVIDER_PADDING_HORIZON),
                themeConstants->GetDimension(THEME_DIALOG_DIVIDER_PADDING_VERTICAL),
                themeConstants->GetDimension(THEME_DIALOG_DIVIDER_PADDING_HORIZON),
                themeConstants->GetDimension(THEME_DIALOG_DIVIDER_PADDING_VERTICAL));
            theme->marginBottom_ = themeConstants->GetDimension(THEME_OHOS_DIMENS_DIALOG_BOTTOM);
            theme->marginLeft_ = themeConstants->GetDimension(THEME_OHOS_DIMENS_DIALOG_START);
            theme->marginRight_ = themeConstants->GetDimension(THEME_OHOS_DIMENS_DIALOG_END);
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<DialogTheme>& theme) const
        {
            if (!themeStyle) {
                LOGI("progress theme style is null");
                return;
            }
            theme->backgroundColor_ = themeStyle->GetAttr<Color>(THEME_ATTR_COLOR_DIALOG_BG, Color::BLACK);
            theme->titleTextStyle_.SetTextColor(themeStyle->GetAttr<Color>(THEME_ATTR_COLOR_PRIMARY, Color::BLACK));
            theme->contentTextStyle_.SetTextColor(themeStyle->GetAttr<Color>(THEME_ATTR_COLOR_PRIMARY, Color::BLACK));
            theme->buttonBackgroundColor_ = themeStyle->GetAttr<Color>(THEME_ATTR_COLOR_DIALOG_BG, Color::BLACK);
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

    const TextStyle& GetTitleTextStyle() const
    {
        return titleTextStyle_;
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

    const Dimension& GetButtonSpacingHorizontal() const
    {
        return buttonSpacingHorizontal_;
    }

    const Dimension& GetButtonSpacingVertical() const
    {
        return buttonSpacingVertical_;
    }

    const Color& GetButtonBackgroundColor() const
    {
        return buttonBackgroundColor_;
    }

    const Color& GetButtonClickedColor() const
    {
        return buttonClickedColor_;
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

protected:
    DialogTheme() = default;

private:
    Radius radius_;
    Color backgroundColor_;
    TextStyle titleTextStyle_;
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
    Color buttonBackgroundColor_;
    Color buttonClickedColor_;
    Dimension translateValue_;
    double frameStart_ = 0.0;
    double frameEnd_ = 1.0;
    double scaleStart_ = 0.0;
    double scaleEnd_ = 1.0;
    double opacityStart_ = 0.0;
    double opacityEnd_ = 1.0;
    int32_t animationDurationIn_ = 250;
    int32_t animationDurationOut_ = 250;
    Color maskColorStart_;
    Color maskColorEnd_;
    Color dividerColor_;
    Dimension dividerWidth_;
    Dimension dividerHeight_;
    Edge dividerPadding_;
    Dimension marginLeft_;
    Dimension marginRight_;
    Dimension marginBottom_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DIALOG_DIALOG_THEME_H
