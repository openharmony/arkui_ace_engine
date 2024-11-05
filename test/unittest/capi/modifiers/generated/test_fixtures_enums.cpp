/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "test_fixtures_enums.h"

#include <climits>

namespace OHOS::Ace::NG::Fixtures {
std::vector<std::tuple<std::string, Ark_Axis, std::string>> testFixtureEnumAxisValidValues = {
    { "ARK_AXIS_VERTICAL", ARK_AXIS_VERTICAL, "Axis.Vertical" },
    { "ARK_AXIS_HORIZONTAL", ARK_AXIS_HORIZONTAL, "Axis.Horizontal" },
};

std::vector<std::tuple<std::string, Ark_Axis>> testFixtureEnumAxisInvalidValues = {
    { "-1", static_cast<Ark_Axis>(-1) },
    { "INT_MAX", static_cast<Ark_Axis>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ButtonRole, std::string>> testFixtureEnumButtonRoleValidValues = {
    { "ARK_BUTTON_ROLE_NORMAL", ARK_BUTTON_ROLE_NORMAL, "ButtonRole.NORMAL" },
    { "ARK_BUTTON_ROLE_ERROR", ARK_BUTTON_ROLE_ERROR, "ButtonRole.ERROR" },
};

std::vector<std::tuple<std::string, Ark_ButtonRole>> testFixtureEnumButtonRoleInvalidValues = {
    { "-1", static_cast<Ark_ButtonRole>(-1) },
    { "INT_MAX", static_cast<Ark_ButtonRole>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ButtonStyleMode, std::string>> testFixtureEnumButtonStyleModeValidValues = {
    { "ARK_BUTTON_STYLE_MODE_NORMAL", ARK_BUTTON_STYLE_MODE_NORMAL, "ButtonStyleMode.NORMAL" },
    { "ARK_BUTTON_STYLE_MODE_EMPHASIZED", ARK_BUTTON_STYLE_MODE_EMPHASIZED, "ButtonStyleMode.EMPHASIZED" },
    { "ARK_BUTTON_STYLE_MODE_TEXTUAL", ARK_BUTTON_STYLE_MODE_TEXTUAL, "ButtonStyleMode.TEXTUAL" },
};

std::vector<std::tuple<std::string, Ark_ButtonStyleMode>> testFixtureEnumButtonStyleModeInvalidValues = {
    { "-1", static_cast<Ark_ButtonStyleMode>(-1) },
    { "INT_MAX", static_cast<Ark_ButtonStyleMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ButtonType, std::string>> testFixtureEnumButtonTypeValidValues = {
    { "ARK_BUTTON_TYPE_CAPSULE", ARK_BUTTON_TYPE_CAPSULE, "ButtonType.Capsule" },
    { "ARK_BUTTON_TYPE_CIRCLE", ARK_BUTTON_TYPE_CIRCLE, "ButtonType.Circle" },
    { "ARK_BUTTON_TYPE_NORMAL", ARK_BUTTON_TYPE_NORMAL, "ButtonType.Normal" },
    { "ARK_BUTTON_TYPE_ROUNDED_RECTANGLE", ARK_BUTTON_TYPE_ROUNDED_RECTANGLE, "ButtonType.ROUNDED_RECTANGLE" },
};

std::vector<std::tuple<std::string, Ark_ButtonType>> testFixtureEnumButtonTypeInvalidValues = {
    { "-1", static_cast<Ark_ButtonType>(-1) },
    { "INT_MAX", static_cast<Ark_ButtonType>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_Color, std::string>> testFixtureEnumColorValidValues = {
    { "ARK_COLOR_WHITE", ARK_COLOR_WHITE, "Color.White" },
    { "ARK_COLOR_BLACK", ARK_COLOR_BLACK, "Color.Black" },
    { "ARK_COLOR_BLUE", ARK_COLOR_BLUE, "Color.Blue" },
    { "ARK_COLOR_BROWN", ARK_COLOR_BROWN, "Color.Brown" },
    { "ARK_COLOR_GRAY", ARK_COLOR_GRAY, "Color.Gray" },
    { "ARK_COLOR_GREEN", ARK_COLOR_GREEN, "Color.Green" },
    { "ARK_COLOR_GREY", ARK_COLOR_GREY, "Color.Grey" },
    { "ARK_COLOR_ORANGE", ARK_COLOR_ORANGE, "Color.Orange" },
    { "ARK_COLOR_PINK", ARK_COLOR_PINK, "Color.Pink" },
    { "ARK_COLOR_RED", ARK_COLOR_RED, "Color.Red" },
    { "ARK_COLOR_YELLOW", ARK_COLOR_YELLOW, "Color.Yellow" },
    { "ARK_COLOR_TRANSPARENT", ARK_COLOR_TRANSPARENT, "Color.Transparent" },
};

std::vector<std::tuple<std::string, Ark_Color>> testFixtureEnumColorInvalidValues = {
    { "-1", static_cast<Ark_Color>(-1) },
    { "INT_MAX", static_cast<Ark_Color>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ColoringStrategy, std::string>> testFixtureEnumColoringStrategyValidValues = {
    { "ARK_COLORING_STRATEGY_INVERT", ARK_COLORING_STRATEGY_INVERT, "ColoringStrategy.INVERT" },
    { "ARK_COLORING_STRATEGY_AVERAGE", ARK_COLORING_STRATEGY_AVERAGE, "ColoringStrategy.AVERAGE" },
    { "ARK_COLORING_STRATEGY_PRIMARY", ARK_COLORING_STRATEGY_PRIMARY, "ColoringStrategy.PRIMARY" },
};

std::vector<std::tuple<std::string, Ark_ColoringStrategy>> testFixtureEnumColoringStrategyInvalidValues = {
    { "-1", static_cast<Ark_ColoringStrategy>(-1) },
    { "INT_MAX", static_cast<Ark_ColoringStrategy>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ControlSize, std::string>> testFixtureEnumControlSizeValidValues = {
    { "ARK_CONTROL_SIZE_SMALL", ARK_CONTROL_SIZE_SMALL, "ControlSize.SMALL" },
    { "ARK_CONTROL_SIZE_NORMAL", ARK_CONTROL_SIZE_NORMAL, "ControlSize.NORMAL" },
};

std::vector<std::tuple<std::string, Ark_ControlSize>> testFixtureEnumControlSizeInvalidValues = {
    { "-1", static_cast<Ark_ControlSize>(-1) },
    { "INT_MAX", static_cast<Ark_ControlSize>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_CopyOptions, std::string>> testFixtureEnumCopyOptionsValidValues = {
    { "ARK_COPY_OPTIONS_NONE", ARK_COPY_OPTIONS_NONE, "CopyOptions.None" },
    { "ARK_COPY_OPTIONS_IN_APP", ARK_COPY_OPTIONS_IN_APP, "CopyOptions.InApp" },
    { "ARK_COPY_OPTIONS_LOCAL_DEVICE", ARK_COPY_OPTIONS_LOCAL_DEVICE, "CopyOptions.LocalDevice" },
    { "ARK_COPY_OPTIONS_CROSS_DEVICE", ARK_COPY_OPTIONS_CROSS_DEVICE, "CopyOptions.CROSS_DEVICE" },
};

std::vector<std::tuple<std::string, Ark_CopyOptions>> testFixtureEnumCopyOptionsInvalidValues = {
    { "-1", static_cast<Ark_CopyOptions>(-1) },
    { "INT_MAX", static_cast<Ark_CopyOptions>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_DynamicRangeMode, std::string>> testFixtureEnumDynamicRangeModeValidValues = {
    { "ARK_DYNAMIC_RANGE_MODE_HIGH", ARK_DYNAMIC_RANGE_MODE_HIGH, "DynamicRangeMode.HIGH" },
    { "ARK_DYNAMIC_RANGE_MODE_CONSTRAINT", ARK_DYNAMIC_RANGE_MODE_CONSTRAINT, "DynamicRangeMode.CONSTRAINT" },
    { "ARK_DYNAMIC_RANGE_MODE_STANDARD", ARK_DYNAMIC_RANGE_MODE_STANDARD, "DynamicRangeMode.STANDARD" },
};

std::vector<std::tuple<std::string, Ark_DynamicRangeMode>> testFixtureEnumDynamicRangeModeInvalidValues = {
    { "-1", static_cast<Ark_DynamicRangeMode>(-1) },
    { "INT_MAX", static_cast<Ark_DynamicRangeMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_FontStyle, std::string>> testFixtureEnumFontStyleValidValues = {
    { "ARK_FONT_STYLE_NORMAL", ARK_FONT_STYLE_NORMAL, "FontStyle.Normal" },
    { "ARK_FONT_STYLE_ITALIC", ARK_FONT_STYLE_ITALIC, "FontStyle.Italic" },
};

std::vector<std::tuple<std::string, Ark_FontStyle>> testFixtureEnumFontStyleInvalidValues = {
    { "-1", static_cast<Ark_FontStyle>(-1) },
    { "INT_MAX", static_cast<Ark_FontStyle>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_FontWeight, std::string>> testFixtureEnumFontWeightValidValues = {
    { "ARK_FONT_WEIGHT_LIGHTER", ARK_FONT_WEIGHT_LIGHTER, "FontWeight.Lighter" },
    { "ARK_FONT_WEIGHT_NORMAL", ARK_FONT_WEIGHT_NORMAL, "FontWeight.Normal" },
    { "ARK_FONT_WEIGHT_REGULAR", ARK_FONT_WEIGHT_REGULAR, "FontWeight.Regular" },
    { "ARK_FONT_WEIGHT_MEDIUM", ARK_FONT_WEIGHT_MEDIUM, "FontWeight.Medium" },
    { "ARK_FONT_WEIGHT_BOLD", ARK_FONT_WEIGHT_BOLD, "FontWeight.Bold" },
    { "ARK_FONT_WEIGHT_BOLDER", ARK_FONT_WEIGHT_BOLDER, "FontWeight.Bolder" },
};

std::vector<std::tuple<std::string, Ark_FontWeight>> testFixtureEnumFontWeightInvalidValues = {
    { "-1", static_cast<Ark_FontWeight>(-1) },
    { "INT_MAX", static_cast<Ark_FontWeight>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_GradientDirection, std::string>> testFixtureEnumGradientDirectionValidValues = {
    { "ARK_GRADIENT_DIRECTION_LEFT", ARK_GRADIENT_DIRECTION_LEFT, "GradientDirection.Left" },
    { "ARK_GRADIENT_DIRECTION_TOP", ARK_GRADIENT_DIRECTION_TOP, "GradientDirection.Top" },
    { "ARK_GRADIENT_DIRECTION_RIGHT", ARK_GRADIENT_DIRECTION_RIGHT, "GradientDirection.Right" },
    { "ARK_GRADIENT_DIRECTION_BOTTOM", ARK_GRADIENT_DIRECTION_BOTTOM, "GradientDirection.Bottom" },
    { "ARK_GRADIENT_DIRECTION_LEFT_TOP", ARK_GRADIENT_DIRECTION_LEFT_TOP, "GradientDirection.LeftTop" },
    { "ARK_GRADIENT_DIRECTION_LEFT_BOTTOM", ARK_GRADIENT_DIRECTION_LEFT_BOTTOM, "GradientDirection.LeftBottom" },
    { "ARK_GRADIENT_DIRECTION_RIGHT_TOP", ARK_GRADIENT_DIRECTION_RIGHT_TOP, "GradientDirection.RightTop" },
    { "ARK_GRADIENT_DIRECTION_RIGHT_BOTTOM", ARK_GRADIENT_DIRECTION_RIGHT_BOTTOM, "GradientDirection.RightBottom" },
    { "ARK_GRADIENT_DIRECTION_NONE", ARK_GRADIENT_DIRECTION_NONE, "GradientDirection.None" },
};

std::vector<std::tuple<std::string, Ark_GradientDirection>> testFixtureEnumGradientDirectionInvalidValues = {
    { "-1", static_cast<Ark_GradientDirection>(-1) },
    { "INT_MAX", static_cast<Ark_GradientDirection>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_IlluminatedType, std::string>> testFixtureEnumIlluminatedTypeValidValues = {
    { "ARK_ILLUMINATED_TYPE_NONE", ARK_ILLUMINATED_TYPE_NONE, "IlluminatedType.NONE" },
    { "ARK_ILLUMINATED_TYPE_BORDER", ARK_ILLUMINATED_TYPE_BORDER, "IlluminatedType.BORDER" },
    { "ARK_ILLUMINATED_TYPE_CONTENT", ARK_ILLUMINATED_TYPE_CONTENT, "IlluminatedType.CONTENT" },
    { "ARK_ILLUMINATED_TYPE_BORDER_CONTENT", ARK_ILLUMINATED_TYPE_BORDER_CONTENT, "IlluminatedType.BORDER_CONTENT" },
    { "ARK_ILLUMINATED_TYPE_BLOOM_BORDER", ARK_ILLUMINATED_TYPE_BLOOM_BORDER, "IlluminatedType.BLOOM_BORDER" },
    { "ARK_ILLUMINATED_TYPE_BLOOM_BORDER_CONTENT", ARK_ILLUMINATED_TYPE_BLOOM_BORDER_CONTENT,
        "IlluminatedType.BLOOM_BORDER_CONTENT" },
};

std::vector<std::tuple<std::string, Ark_IlluminatedType>> testFixtureEnumIlluminatedTypeInvalidValues = {
    { "-1", static_cast<Ark_IlluminatedType>(-1) },
    { "INT_MAX", static_cast<Ark_IlluminatedType>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ImageContent, std::string>> testFixtureEnumImageContentValidValues = {
    { "ARK_IMAGE_CONTENT_EMPTY", ARK_IMAGE_CONTENT_EMPTY, "ImageContent.EMPTY" },
};

std::vector<std::tuple<std::string, Ark_ImageContent>> testFixtureEnumImageContentInvalidValues = {
    { "-1", static_cast<Ark_ImageContent>(-1) },
    { "INT_MAX", static_cast<Ark_ImageContent>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ImageFit, std::string>> testFixtureEnumImageFitValidValues = {
    { "ARK_IMAGE_FIT_CONTAIN", ARK_IMAGE_FIT_CONTAIN, "ImageFit.Contain" },
    { "ARK_IMAGE_FIT_COVER", ARK_IMAGE_FIT_COVER, "ImageFit.Cover" },
    { "ARK_IMAGE_FIT_AUTO", ARK_IMAGE_FIT_AUTO, "ImageFit.Auto" },
    { "ARK_IMAGE_FIT_FILL", ARK_IMAGE_FIT_FILL, "ImageFit.Fill" },
    { "ARK_IMAGE_FIT_SCALE_DOWN", ARK_IMAGE_FIT_SCALE_DOWN, "ImageFit.ScaleDown" },
    { "ARK_IMAGE_FIT_NONE", ARK_IMAGE_FIT_NONE, "ImageFit.None" },
    { "ARK_IMAGE_FIT_TOP_START", ARK_IMAGE_FIT_TOP_START, "ImageFit.TOP_START" },
    { "ARK_IMAGE_FIT_TOP", ARK_IMAGE_FIT_TOP, "ImageFit.TOP" },
    { "ARK_IMAGE_FIT_TOP_END", ARK_IMAGE_FIT_TOP_END, "ImageFit.TOP_END" },
    { "ARK_IMAGE_FIT_START", ARK_IMAGE_FIT_START, "ImageFit.START" },
    { "ARK_IMAGE_FIT_CENTER", ARK_IMAGE_FIT_CENTER, "ImageFit.CENTER" },
    { "ARK_IMAGE_FIT_END", ARK_IMAGE_FIT_END, "ImageFit.END" },
    { "ARK_IMAGE_FIT_BOTTOM_START", ARK_IMAGE_FIT_BOTTOM_START, "ImageFit.BOTTOM_START" },
    { "ARK_IMAGE_FIT_BOTTOM", ARK_IMAGE_FIT_BOTTOM, "ImageFit.BOTTOM" },
    { "ARK_IMAGE_FIT_BOTTOM_END", ARK_IMAGE_FIT_BOTTOM_END, "ImageFit.BOTTOM_END" },
};

std::vector<std::tuple<std::string, Ark_ImageFit>> testFixtureEnumImageFitInvalidValues = {
    { "-1", static_cast<Ark_ImageFit>(-1) },
    { "INT_MAX", static_cast<Ark_ImageFit>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ImageInterpolation, std::string>>
    testFixtureEnumImageInterpolationValidValues = {
        { "ARK_IMAGE_INTERPOLATION_NONE", ARK_IMAGE_INTERPOLATION_NONE, "ImageInterpolation.None" },
        { "ARK_IMAGE_INTERPOLATION_LOW", ARK_IMAGE_INTERPOLATION_LOW, "ImageInterpolation.Low" },
        { "ARK_IMAGE_INTERPOLATION_MEDIUM", ARK_IMAGE_INTERPOLATION_MEDIUM, "ImageInterpolation.Medium" },
        { "ARK_IMAGE_INTERPOLATION_HIGH", ARK_IMAGE_INTERPOLATION_HIGH, "ImageInterpolation.High" },
    };

std::vector<std::tuple<std::string, Ark_ImageInterpolation>> testFixtureEnumImageInterpolationInvalidValues = {
    { "-1", static_cast<Ark_ImageInterpolation>(-1) },
    { "INT_MAX", static_cast<Ark_ImageInterpolation>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ImageRenderMode, std::string>> testFixtureEnumImageRenderModeValidValues = {
    { "ARK_IMAGE_RENDER_MODE_ORIGINAL", ARK_IMAGE_RENDER_MODE_ORIGINAL, "ImageRenderMode.Original" },
    { "ARK_IMAGE_RENDER_MODE_TEMPLATE", ARK_IMAGE_RENDER_MODE_TEMPLATE, "ImageRenderMode.Template" },
};

std::vector<std::tuple<std::string, Ark_ImageRenderMode>> testFixtureEnumImageRenderModeInvalidValues = {
    { "-1", static_cast<Ark_ImageRenderMode>(-1) },
    { "INT_MAX", static_cast<Ark_ImageRenderMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ImageRepeat, std::string>> testFixtureEnumImageRepeatValidValues = {
    { "ARK_IMAGE_REPEAT_NO_REPEAT", ARK_IMAGE_REPEAT_NO_REPEAT, "ImageRepeat.NoRepeat" },
    { "ARK_IMAGE_REPEAT_X", ARK_IMAGE_REPEAT_X, "ImageRepeat.X" },
    { "ARK_IMAGE_REPEAT_Y", ARK_IMAGE_REPEAT_Y, "ImageRepeat.Y" },
    { "ARK_IMAGE_REPEAT_XY", ARK_IMAGE_REPEAT_XY, "ImageRepeat.XY" },
};

std::vector<std::tuple<std::string, Ark_ImageRepeat>> testFixtureEnumImageRepeatInvalidValues = {
    { "-1", static_cast<Ark_ImageRepeat>(-1) },
    { "INT_MAX", static_cast<Ark_ImageRepeat>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_RadioIndicatorType, std::string>>
    testFixtureEnumRadioIndicatorTypeValidValues = {
        { "ARK_RADIO_INDICATOR_TYPE_TICK", ARK_RADIO_INDICATOR_TYPE_TICK, "RadioIndicatorType.TICK" },
        { "ARK_RADIO_INDICATOR_TYPE_DOT", ARK_RADIO_INDICATOR_TYPE_DOT, "RadioIndicatorType.DOT" },
        { "ARK_RADIO_INDICATOR_TYPE_CUSTOM", ARK_RADIO_INDICATOR_TYPE_CUSTOM, "RadioIndicatorType.CUSTOM" },
    };

std::vector<std::tuple<std::string, Ark_RadioIndicatorType>> testFixtureEnumRadioIndicatorTypeInvalidValues = {
    { "-1", static_cast<Ark_RadioIndicatorType>(-1) },
    { "INT_MAX", static_cast<Ark_RadioIndicatorType>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ShadowType, std::string>> testFixtureEnumShadowTypeValidValues = {
    { "ARK_SHADOW_TYPE_COLOR", ARK_SHADOW_TYPE_COLOR, "ShadowType.COLOR" },
    { "ARK_SHADOW_TYPE_BLUR", ARK_SHADOW_TYPE_BLUR, "ShadowType.BLUR" },
};

std::vector<std::tuple<std::string, Ark_ShadowType>> testFixtureEnumShadowTypeInvalidValues = {
    { "-1", static_cast<Ark_ShadowType>(-1) },
    { "INT_MAX", static_cast<Ark_ShadowType>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_SliderBlockType, std::string>> testFixtureEnumSliderBlockTypeValidValues = {
    { "ARK_SLIDER_BLOCK_TYPE_DEFAULT", ARK_SLIDER_BLOCK_TYPE_DEFAULT, "SliderBlockType.DEFAULT" },
    { "ARK_SLIDER_BLOCK_TYPE_IMAGE", ARK_SLIDER_BLOCK_TYPE_IMAGE, "SliderBlockType.IMAGE" },
    { "ARK_SLIDER_BLOCK_TYPE_SHAPE", ARK_SLIDER_BLOCK_TYPE_SHAPE, "SliderBlockType.SHAPE" },
};

std::vector<std::tuple<std::string, Ark_SliderBlockType>> testFixtureEnumSliderBlockTypeInvalidValues = {
    { "-1", static_cast<Ark_SliderBlockType>(-1) },
    { "INT_MAX", static_cast<Ark_SliderBlockType>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_SliderInteraction, std::string>> testFixtureEnumSliderInteractionValidValues = {
    { "ARK_SLIDER_INTERACTION_SLIDE_AND_CLICK", ARK_SLIDER_INTERACTION_SLIDE_AND_CLICK,
        "SliderInteraction.SLIDE_AND_CLICK" },
    { "ARK_SLIDER_INTERACTION_SLIDE_ONLY", ARK_SLIDER_INTERACTION_SLIDE_ONLY, "SliderInteraction.SLIDE_ONLY" },
    { "ARK_SLIDER_INTERACTION_SLIDE_AND_CLICK_UP", ARK_SLIDER_INTERACTION_SLIDE_AND_CLICK_UP,
        "SliderInteraction.SLIDE_AND_CLICK_UP" },
};

std::vector<std::tuple<std::string, Ark_SliderInteraction>> testFixtureEnumSliderInteractionInvalidValues = {
    { "-1", static_cast<Ark_SliderInteraction>(-1) },
    { "INT_MAX", static_cast<Ark_SliderInteraction>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_SliderStyle, std::string>> testFixtureEnumSliderStyleValidValues = {
    { "ARK_SLIDER_STYLE_OUT_SET", ARK_SLIDER_STYLE_OUT_SET, "SliderStyle.OutSet" },
    { "ARK_SLIDER_STYLE_IN_SET", ARK_SLIDER_STYLE_IN_SET, "SliderStyle.InSet" },
    { "ARK_SLIDER_STYLE_NONE", ARK_SLIDER_STYLE_NONE, "SliderStyle.NONE" },
};

std::vector<std::tuple<std::string, Ark_SliderStyle>> testFixtureEnumSliderStyleInvalidValues = {
    { "-1", static_cast<Ark_SliderStyle>(-1) },
    { "INT_MAX", static_cast<Ark_SliderStyle>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_TextCase, std::string>> testFixtureEnumTextCaseValidValues = {
    { "ARK_TEXT_CASE_NORMAL", ARK_TEXT_CASE_NORMAL, "TextCase.Normal" },
    { "ARK_TEXT_CASE_LOWER_CASE", ARK_TEXT_CASE_LOWER_CASE, "TextCase.LowerCase" },
    { "ARK_TEXT_CASE_UPPER_CASE", ARK_TEXT_CASE_UPPER_CASE, "TextCase.UpperCase" },
};

std::vector<std::tuple<std::string, Ark_TextCase>> testFixtureEnumTextCaseInvalidValues = {
    { "-1", static_cast<Ark_TextCase>(-1) },
    { "INT_MAX", static_cast<Ark_TextCase>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_TextDecorationStyle, std::string>>
    testFixtureEnumTextDecorationStyleValidValues = {
        { "ARK_TEXT_DECORATION_STYLE_SOLID", ARK_TEXT_DECORATION_STYLE_SOLID, "TextDecorationStyle.SOLID" },
        { "ARK_TEXT_DECORATION_STYLE_DOUBLE", ARK_TEXT_DECORATION_STYLE_DOUBLE, "TextDecorationStyle.DOUBLE" },
        { "ARK_TEXT_DECORATION_STYLE_DOTTED", ARK_TEXT_DECORATION_STYLE_DOTTED, "TextDecorationStyle.DOTTED" },
        { "ARK_TEXT_DECORATION_STYLE_DASHED", ARK_TEXT_DECORATION_STYLE_DASHED, "TextDecorationStyle.DASHED" },
        { "ARK_TEXT_DECORATION_STYLE_WAVY", ARK_TEXT_DECORATION_STYLE_WAVY, "TextDecorationStyle.WAVY" },
    };

std::vector<std::tuple<std::string, Ark_TextDecorationStyle>> testFixtureEnumTextDecorationStyleInvalidValues = {
    { "-1", static_cast<Ark_TextDecorationStyle>(-1) },
    { "INT_MAX", static_cast<Ark_TextDecorationStyle>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_TextDecorationType, std::string>>
    testFixtureEnumTextDecorationTypeValidValues = {
        { "ARK_TEXT_DECORATION_TYPE_NONE", ARK_TEXT_DECORATION_TYPE_NONE, "TextDecorationType.None" },
        { "ARK_TEXT_DECORATION_TYPE_UNDERLINE", ARK_TEXT_DECORATION_TYPE_UNDERLINE, "TextDecorationType.Underline" },
        { "ARK_TEXT_DECORATION_TYPE_OVERLINE", ARK_TEXT_DECORATION_TYPE_OVERLINE, "TextDecorationType.Overline" },
        { "ARK_TEXT_DECORATION_TYPE_LINE_THROUGH", ARK_TEXT_DECORATION_TYPE_LINE_THROUGH,
            "TextDecorationType.LineThrough" },
    };

std::vector<std::tuple<std::string, Ark_TextDecorationType>> testFixtureEnumTextDecorationTypeInvalidValues = {
    { "-1", static_cast<Ark_TextDecorationType>(-1) },
    { "INT_MAX", static_cast<Ark_TextDecorationType>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_TextHeightAdaptivePolicy, std::string>>
    testFixtureEnumTextHeightAdaptivePolicyValidValues = {
        { "ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST", ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST,
            "TextHeightAdaptivePolicy.MAX_LINES_FIRST" },
        { "ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST", ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST,
            "TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST" },
        { "ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST",
            ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST,
            "TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST" },
    };

std::vector<std::tuple<std::string, Ark_TextHeightAdaptivePolicy>>
    testFixtureEnumTextHeightAdaptivePolicyInvalidValues = {
        { "-1", static_cast<Ark_TextHeightAdaptivePolicy>(-1) },
        { "INT_MAX", static_cast<Ark_TextHeightAdaptivePolicy>(INT_MAX) },
    };

std::vector<std::tuple<std::string, Ark_TextOverflow, std::string>> testFixtureEnumTextOverflowValidValues = {
    { "ARK_TEXT_OVERFLOW_NONE", ARK_TEXT_OVERFLOW_NONE, "TextOverflow.None" },
    { "ARK_TEXT_OVERFLOW_CLIP", ARK_TEXT_OVERFLOW_CLIP, "TextOverflow.Clip" },
    { "ARK_TEXT_OVERFLOW_ELLIPSIS", ARK_TEXT_OVERFLOW_ELLIPSIS, "TextOverflow.Ellipsis" },
    { "ARK_TEXT_OVERFLOW_MARQUEE", ARK_TEXT_OVERFLOW_MARQUEE, "TextOverflow.MARQUEE" },
};

std::vector<std::tuple<std::string, Ark_TextOverflow>> testFixtureEnumTextOverflowInvalidValues = {
    { "-1", static_cast<Ark_TextOverflow>(-1) },
    { "INT_MAX", static_cast<Ark_TextOverflow>(INT_MAX) },
};

} // namespace OHOS::Ace::NG::Fixtures
