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

#include "base/geometry/dimension.h"
#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/layout_param.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/blur_style_option.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/radius.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {
namespace {
constexpr double PRIMARY_RGBA_OPACITY = 0.9f;
constexpr double SECONDARY_RGBA_OPACITY = 0.6f;
constexpr int DEFAULT_ANIMATION_DURATION_OUT = 220;
constexpr int DEFAULT_ANIMATION_DURATION_IN = 250;
constexpr int DEFAULT_DIALOG_ALIGNMENT = 2;
constexpr double DEFAULT_DIALOG_MAXSIZE_SCALE_LANDSCAPE = 0.9f;
constexpr double DEFAULT_DIALOG_MAXSIZE_SCALE_PORTRAIT = 0.8f;
constexpr int DEFAULT_DIALOG_SCROLL_FLEX_ALIGN = 1;
constexpr int DEFAULT_DIALOG_COLUMN_MEASURE_TYPE = 1;
constexpr int DIALOG_TITLE_MAX_LINES_VALUE = 2;
constexpr float DEFAULT_ALIGN_DIALOG = 3.0;
constexpr float SHADOW_NONE = 6.0;

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
            RefPtr<DialogTheme> theme = AceType::MakeRefPtr<DialogTheme>();
            if (!themeConstants) {
                return theme;
            }
            // init theme from global data
            ParseNewPattern(themeConstants, theme);
            ParsePattern(themeConstants, theme);
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<DialogTheme>& theme) const;
        void ParseNewPattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<DialogTheme>& theme) const;
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

    const Dimension& GetButtonBottomTopMargin() const
    {
        return buttonBottomTopMargin_;
    }

    const Dimension& GetTitlePaddingHorizontal() const
    {
        return titlePaddingHorizontal_;
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

    int GetDialogBackgroundBlurStyle() const
    {
        return dialogBackgroundBlurStyle_;
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

    const Dimension& GetContainerMaxWidth() const
    {
        return containerMaxWidth_;
    }

    uint32_t GetDefaultShadowOn() const
    {
        return defaultShadowOn_;
    }

    uint32_t GetDefaultShadowOff() const
    {
        return defaultShadowOff_;
    }
    const DialogAlignment& GetAlignment() const
    {
        return alignment_;
    }

    double GetMaxSizeScaleLandscape() const
    {
        return maxSizeScaleLandscape_;
    }

    double GetMaxSizeScalePortrait() const
    {
        return maxSizeScalePortrait_;
    }

    const FlexAlign& GetScrollFlexAlign() const
    {
        return scrollFlexAlign_;
    }

    const NG::MeasureType& GetColumnMeasureType() const
    {
        return columnMeasureType_;
    }

    int32_t GetDialogDoubleBorderEnable() const
    {
        return dialogDoubleBorderEnable_;
    }

    double GetDialogOuterBorderWidth() const
    {
        return dialogOuterBorderWidth_;
    }

    Color GetDialogOuterBorderColor() const
    {
        return dialogOuterBorderColor_;
    }

    double GetDialogInnerBorderWidth() const
    {
        return dialogInnerBorderWidth_;
    }

    Color GetDialogInnerBorderColor() const
    {
        return dialogInnerBorderColor_;
    }

    double GetMinFontScaleForElderly() const
    {
        return minFontScaleForElderly_;
    }

    double GetDialogDefaultScale() const
    {
        return dialogDefaultScale_;
    }

    double GetContentMaxFontScale() const
    {
        return contentMaxFontScale_;
    }

    double GetContentLandscapeMaxFontScale() const
    {
        return contentLandscapeMaxFontScale_;
    }

    double GetButtonMaxFontScale() const
    {
        return buttonMaxFontScale_;
    }

    double GetButtonLandscapeMaxFontScale() const
    {
        return buttonLandscapeMaxFontScale_;
    }

    double GetTitleMaxFontScale() const
    {
        return titleMaxFontScale_;
    }

    const Dimension& GetDialogLandscapeHeightBoundary() const
    {
        return dialogLandscapeHeightBoundary_;
    }

    const Color& GetBackgroudBorderColor() const
    {
        return backgroundBorderColor_;
    }

    const Dimension& GetBackgroudBorderWidth()
    {
        return backgroundBorderWidth_;
    }

    double GetDialogRatioHeight() const
    {
        return dialogRatioHeight_;
    }

    int32_t GetTextAlignContent() const
    {
        return text_align_content_;
    }

    int32_t GetTextAlignTitle() const
    {
        return text_align_title_;
    }

    uint32_t GetShadowDialog() const
    {
        return shadowDialog_;
    }

    int32_t GetAlignDialog() const
    {
        return alignDialog_;
    }

    int32_t GetButtonType() const
    {
        return button_type_;
    }

    const Color& GetColorBgWithBlur() const
    {
        return colorBgWithBlur_;
    }

    const Dimension& GetPaddingTopTitle() const
    {
        return paddingTopTitle_;
    }

    const Dimension& GetPaddingSingleTitle() const
    {
        return paddingSingleTitle_;
    }

    const Dimension& GetNormalButtonFontSize() const
    {
        return normalButtonFontSize_;
    }

    const std::string& GetCancelText() const
    {
        return cancelText_;
    }

    const std::string& GetConfirmText() const
    {
        return confirmText_;
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
    Dimension buttonBottomTopMargin_;
    Dimension titlePaddingHorizontal_;
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
    Dimension dialogLandscapeHeightBoundary_;
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
    double minFontScaleForElderly_ = 1.75;
    double dialogDefaultScale_ = 1.0;
    double contentMaxFontScale_ = 3.2;
    double contentLandscapeMaxFontScale_ = 2.0;
    double buttonMaxFontScale_ = 3.2;
    double buttonLandscapeMaxFontScale_ = 2.0;
    double titleMaxFontScale_ = 2.0;
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
    Dimension containerMaxWidth_;
    uint32_t defaultShadowOn_ = 6;
    uint32_t defaultShadowOff_ = 6;
    DialogAlignment alignment_;
    double maxSizeScaleLandscape_ = 0.9;
    double maxSizeScalePortrait_ = 0.8;
    FlexAlign scrollFlexAlign_ = FlexAlign::FLEX_START;
    NG::MeasureType columnMeasureType_ = NG::MeasureType::MATCH_CONTENT;
    int32_t dialogDoubleBorderEnable_ = 0;
    double dialogOuterBorderWidth_ = 0.0f;
    Color dialogOuterBorderColor_;
    double dialogInnerBorderWidth_ = 0.0f;
    Color dialogInnerBorderColor_;
    Dimension paddingSingleTitle_;
    Dimension paddingTopTitle_;
    Dimension backgroundBorderWidth_;
    double dialogRatioHeight_ = 0.9;
    int32_t text_align_content_ = 0;
    int32_t text_align_title_ = 0;
    int32_t button_type_ = 0;
    uint32_t shadowDialog_ = 6;
    int32_t alignDialog_ = 3;
    Dimension normalButtonFontSize_;
    Color colorBgWithBlur_;
    Color backgroundBorderColor_;
    int dialogBackgroundBlurStyle_ = static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK);
    std::string cancelText_;
    std::string confirmText_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DIALOG_DIALOG_THEME_H
