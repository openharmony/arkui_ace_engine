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

std::vector<std::tuple<std::string, Ark_BarState, std::string>> testFixtureEnumBarStateValidValues = {
    { "ARK_BAR_STATE_OFF", ARK_BAR_STATE_OFF, "BarState.Off" },
    { "ARK_BAR_STATE_AUTO", ARK_BAR_STATE_AUTO, "BarState.Auto" },
    { "ARK_BAR_STATE_ON", ARK_BAR_STATE_ON, "BarState.On" },
};

std::vector<std::tuple<std::string, Ark_BarState>> testFixtureEnumBarStateInvalidValues = {
    { "-1", static_cast<Ark_BarState>(-1) },
    { "INT_MAX", static_cast<Ark_BarState>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_BarStyle, std::string>> testFixtureEnumBarStyleValidValues = {
    { "ARK_BAR_STYLE_STANDARD", ARK_BAR_STYLE_STANDARD, "BarStyle.STANDARD" },
    { "ARK_BAR_STYLE_STACK", ARK_BAR_STYLE_STACK, "BarStyle.STACK" },
};

std::vector<std::tuple<std::string, Ark_BarStyle>> testFixtureEnumBarStyleInvalidValues = {
    { "-1", static_cast<Ark_BarStyle>(-1) },
    { "INT_MAX", static_cast<Ark_BarStyle>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_BlurStyle, std::string>> testFixtureEnumBlurStyleValidValues = {
    { "ARK_BLUR_STYLE_THIN", ARK_BLUR_STYLE_THIN, "BlurStyle.Thin" },
    { "ARK_BLUR_STYLE_REGULAR", ARK_BLUR_STYLE_REGULAR, "BlurStyle.Regular" },
    { "ARK_BLUR_STYLE_THICK", ARK_BLUR_STYLE_THICK, "BlurStyle.Thick" },
    { "ARK_BLUR_STYLE_BACKGROUND_THIN", ARK_BLUR_STYLE_BACKGROUND_THIN, "BlurStyle.BACKGROUND_THIN" },
    { "ARK_BLUR_STYLE_BACKGROUND_REGULAR", ARK_BLUR_STYLE_BACKGROUND_REGULAR, "BlurStyle.BACKGROUND_REGULAR" },
    { "ARK_BLUR_STYLE_BACKGROUND_THICK", ARK_BLUR_STYLE_BACKGROUND_THICK, "BlurStyle.BACKGROUND_THICK" },
    { "ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK", ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK,
        "BlurStyle.BACKGROUND_ULTRA_THICK" },
    { "ARK_BLUR_STYLE_NONE", ARK_BLUR_STYLE_NONE, "BlurStyle.NONE" },
    { "ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN", ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN, "BlurStyle.COMPONENT_ULTRA_THIN" },
    { "ARK_BLUR_STYLE_COMPONENT_THIN", ARK_BLUR_STYLE_COMPONENT_THIN, "BlurStyle.COMPONENT_THIN" },
    { "ARK_BLUR_STYLE_COMPONENT_REGULAR", ARK_BLUR_STYLE_COMPONENT_REGULAR, "BlurStyle.COMPONENT_REGULAR" },
    { "ARK_BLUR_STYLE_COMPONENT_THICK", ARK_BLUR_STYLE_COMPONENT_THICK, "BlurStyle.COMPONENT_THICK" },
    { "ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK", ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK, "BlurStyle.COMPONENT_ULTRA_THICK" },
};

std::vector<std::tuple<std::string, Ark_BlurStyle>> testFixtureEnumBlurStyleInvalidValues = {
    { "-1", static_cast<Ark_BlurStyle>(-1) },
    { "INT_MAX", static_cast<Ark_BlurStyle>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_BreakpointsReference, std::string>>
    testFixtureEnumBreakpointsReferenceValidValues = {
        { "ARK_BREAKPOINTS_REFERENCE_WINDOW_SIZE", ARK_BREAKPOINTS_REFERENCE_WINDOW_SIZE,
            "BreakpointsReference.WindowSize" },
        { "ARK_BREAKPOINTS_REFERENCE_COMPONENT_SIZE", ARK_BREAKPOINTS_REFERENCE_COMPONENT_SIZE,
            "BreakpointsReference.ComponentSize" },
    };

std::vector<std::tuple<std::string, Ark_BreakpointsReference>> testFixtureEnumBreakpointsReferenceInvalidValues = {
    { "-1", static_cast<Ark_BreakpointsReference>(-1) },
    { "INT_MAX", static_cast<Ark_BreakpointsReference>(INT_MAX) },
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

std::vector<std::tuple<std::string, Ark_CacheMode, std::string>> testFixtureEnumCacheModeValidValues = {
    { "ARK_CACHE_MODE_DEFAULT", ARK_CACHE_MODE_DEFAULT, "CacheMode.Default" },
    { "ARK_CACHE_MODE_NONE", ARK_CACHE_MODE_NONE, "CacheMode.None" },
    { "ARK_CACHE_MODE_ONLINE", ARK_CACHE_MODE_ONLINE, "CacheMode.Online" },
    { "ARK_CACHE_MODE_ONLY", ARK_CACHE_MODE_ONLY, "CacheMode.Only" },
};

std::vector<std::tuple<std::string, Ark_CacheMode>> testFixtureEnumCacheModeInvalidValues = {
    { "-1", static_cast<Ark_CacheMode>(-1) },
    { "INT_MAX", static_cast<Ark_CacheMode>(INT_MAX) },
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

std::vector<std::tuple<std::string, Ark_EdgeEffect, std::string>> testFixtureEnumEdgeEffectValidValues = {
    { "ARK_EDGE_EFFECT_SPRING", ARK_EDGE_EFFECT_SPRING, "EdgeEffect.Spring" },
    { "ARK_EDGE_EFFECT_FADE", ARK_EDGE_EFFECT_FADE, "EdgeEffect.Fade" },
    { "ARK_EDGE_EFFECT_NONE", ARK_EDGE_EFFECT_NONE, "EdgeEffect.None" },
};

std::vector<std::tuple<std::string, Ark_EdgeEffect>> testFixtureEnumEdgeEffectInvalidValues = {
    { "-1", static_cast<Ark_EdgeEffect>(-1) },
    { "INT_MAX", static_cast<Ark_EdgeEffect>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_EllipsisMode, std::string>> testFixtureEnumEllipsisModeValidValues = {
    { "ARK_ELLIPSIS_MODE_START", ARK_ELLIPSIS_MODE_START, "EllipsisMode.START" },
    { "ARK_ELLIPSIS_MODE_CENTER", ARK_ELLIPSIS_MODE_CENTER, "EllipsisMode.CENTER" },
    { "ARK_ELLIPSIS_MODE_END", ARK_ELLIPSIS_MODE_END, "EllipsisMode.END" },
};

std::vector<std::tuple<std::string, Ark_EllipsisMode>> testFixtureEnumEllipsisModeInvalidValues = {
    { "-1", static_cast<Ark_EllipsisMode>(-1) },
    { "INT_MAX", static_cast<Ark_EllipsisMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_EnterKeyType, std::string>> testFixtureEnumEnterKeyTypeValidValues = {
    { "ARK_ENTER_KEY_TYPE_GO", ARK_ENTER_KEY_TYPE_GO, "EnterKeyType.Go" },
    { "ARK_ENTER_KEY_TYPE_SEARCH", ARK_ENTER_KEY_TYPE_SEARCH, "EnterKeyType.Search" },
    { "ARK_ENTER_KEY_TYPE_SEND", ARK_ENTER_KEY_TYPE_SEND, "EnterKeyType.Send" },
    { "ARK_ENTER_KEY_TYPE_NEXT", ARK_ENTER_KEY_TYPE_NEXT, "EnterKeyType.Next" },
    { "ARK_ENTER_KEY_TYPE_DONE", ARK_ENTER_KEY_TYPE_DONE, "EnterKeyType.Done" },
    { "ARK_ENTER_KEY_TYPE_PREVIOUS", ARK_ENTER_KEY_TYPE_PREVIOUS, "EnterKeyType.PREVIOUS" },
    { "ARK_ENTER_KEY_TYPE_NEW_LINE", ARK_ENTER_KEY_TYPE_NEW_LINE, "EnterKeyType.NEW_LINE" },
};

std::vector<std::tuple<std::string, Ark_EnterKeyType>> testFixtureEnumEnterKeyTypeInvalidValues = {
    { "-1", static_cast<Ark_EnterKeyType>(-1) },
    { "INT_MAX", static_cast<Ark_EnterKeyType>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_FlexDirection, std::string>> testFixtureEnumFlexDirectionValidValues = {
    { "ARK_FLEX_DIRECTION_ROW", ARK_FLEX_DIRECTION_ROW, "FlexDirection.Row" },
    { "ARK_FLEX_DIRECTION_COLUMN", ARK_FLEX_DIRECTION_COLUMN, "FlexDirection.Column" },
    { "ARK_FLEX_DIRECTION_ROW_REVERSE", ARK_FLEX_DIRECTION_ROW_REVERSE, "FlexDirection.RowReverse" },
    { "ARK_FLEX_DIRECTION_COLUMN_REVERSE", ARK_FLEX_DIRECTION_COLUMN_REVERSE, "FlexDirection.ColumnReverse" },
};

std::vector<std::tuple<std::string, Ark_FlexDirection>> testFixtureEnumFlexDirectionInvalidValues = {
    { "-1", static_cast<Ark_FlexDirection>(-1) },
    { "INT_MAX", static_cast<Ark_FlexDirection>(INT_MAX) },
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

std::vector<std::tuple<std::string, Ark_GridRowDirection, std::string>> testFixtureEnumGridRowDirectionValidValues = {
    { "ARK_GRID_ROW_DIRECTION_ROW", ARK_GRID_ROW_DIRECTION_ROW, "GridRowDirection.Row" },
    { "ARK_GRID_ROW_DIRECTION_ROW_REVERSE", ARK_GRID_ROW_DIRECTION_ROW_REVERSE, "GridRowDirection.RowReverse" },
};

std::vector<std::tuple<std::string, Ark_GridRowDirection>> testFixtureEnumGridRowDirectionInvalidValues = {
    { "-1", static_cast<Ark_GridRowDirection>(-1) },
    { "INT_MAX", static_cast<Ark_GridRowDirection>(INT_MAX) },
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

std::vector<std::tuple<std::string, Ark_InputType, std::string>> testFixtureEnumInputTypeValidValues = {
    { "ARK_INPUT_TYPE_NORMAL", ARK_INPUT_TYPE_NORMAL, "InputType.Normal" },
    { "ARK_INPUT_TYPE_NUMBER", ARK_INPUT_TYPE_NUMBER, "InputType.Number" },
    { "ARK_INPUT_TYPE_PHONE_NUMBER", ARK_INPUT_TYPE_PHONE_NUMBER, "InputType.PhoneNumber" },
    { "ARK_INPUT_TYPE_EMAIL", ARK_INPUT_TYPE_EMAIL, "InputType.Email" },
    { "ARK_INPUT_TYPE_PASSWORD", ARK_INPUT_TYPE_PASSWORD, "InputType.Password" },
    { "ARK_INPUT_TYPE_NUMBER_PASSWORD", ARK_INPUT_TYPE_NUMBER_PASSWORD, "InputType.NUMBER_PASSWORD" },
    { "ARK_INPUT_TYPE_SCREEN_LOCK_PASSWORD", ARK_INPUT_TYPE_SCREEN_LOCK_PASSWORD, "InputType.SCREEN_LOCK_PASSWORD" },
    { "ARK_INPUT_TYPE_USER_NAME", ARK_INPUT_TYPE_USER_NAME, "InputType.USER_NAME" },
    { "ARK_INPUT_TYPE_NEW_PASSWORD", ARK_INPUT_TYPE_NEW_PASSWORD, "InputType.NEW_PASSWORD" },
    { "ARK_INPUT_TYPE_NUMBER_DECIMAL", ARK_INPUT_TYPE_NUMBER_DECIMAL, "InputType.NUMBER_DECIMAL" },
    { "ARK_INPUT_TYPE_URL", ARK_INPUT_TYPE_URL, "InputType.URL" },
};

std::vector<std::tuple<std::string, Ark_InputType>> testFixtureEnumInputTypeInvalidValues = {
    { "-1", static_cast<Ark_InputType>(-1) },
    { "INT_MAX", static_cast<Ark_InputType>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ItemAlign, std::string>> testFixtureEnumItemAlignValidValues = {
    { "ARK_ITEM_ALIGN_AUTO", ARK_ITEM_ALIGN_AUTO, "ItemAlign.Auto" },
    { "ARK_ITEM_ALIGN_START", ARK_ITEM_ALIGN_START, "ItemAlign.Start" },
    { "ARK_ITEM_ALIGN_CENTER", ARK_ITEM_ALIGN_CENTER, "ItemAlign.Center" },
    { "ARK_ITEM_ALIGN_END", ARK_ITEM_ALIGN_END, "ItemAlign.End" },
    { "ARK_ITEM_ALIGN_BASELINE", ARK_ITEM_ALIGN_BASELINE, "ItemAlign.Baseline" },
    { "ARK_ITEM_ALIGN_STRETCH", ARK_ITEM_ALIGN_STRETCH, "ItemAlign.Stretch" },
};

std::vector<std::tuple<std::string, Ark_ItemAlign>> testFixtureEnumItemAlignInvalidValues = {
    { "-1", static_cast<Ark_ItemAlign>(-1) },
    { "INT_MAX", static_cast<Ark_ItemAlign>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_LineBreakStrategy, std::string>> testFixtureEnumLineBreakStrategyValidValues = {
    { "ARK_LINE_BREAK_STRATEGY_GREEDY", ARK_LINE_BREAK_STRATEGY_GREEDY, "LineBreakStrategy.GREEDY" },
    { "ARK_LINE_BREAK_STRATEGY_HIGH_QUALITY", ARK_LINE_BREAK_STRATEGY_HIGH_QUALITY, "LineBreakStrategy.HIGH_QUALITY" },
    { "ARK_LINE_BREAK_STRATEGY_BALANCED", ARK_LINE_BREAK_STRATEGY_BALANCED, "LineBreakStrategy.BALANCED" },
};

std::vector<std::tuple<std::string, Ark_LineBreakStrategy>> testFixtureEnumLineBreakStrategyInvalidValues = {
    { "-1", static_cast<Ark_LineBreakStrategy>(-1) },
    { "INT_MAX", static_cast<Ark_LineBreakStrategy>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_MixedMode, std::string>> testFixtureEnumMixedModeValidValues = {
    { "ARK_MIXED_MODE_ALL", ARK_MIXED_MODE_ALL, "MixedMode.All" },
    { "ARK_MIXED_MODE_COMPATIBLE", ARK_MIXED_MODE_COMPATIBLE, "MixedMode.Compatible" },
    { "ARK_MIXED_MODE_NONE", ARK_MIXED_MODE_NONE, "MixedMode.None" },
};

std::vector<std::tuple<std::string, Ark_MixedMode>> testFixtureEnumMixedModeInvalidValues = {
    { "-1", static_cast<Ark_MixedMode>(-1) },
    { "INT_MAX", static_cast<Ark_MixedMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_NavBarPosition, std::string>> testFixtureEnumNavBarPositionValidValues = {
    { "ARK_NAV_BAR_POSITION_START", ARK_NAV_BAR_POSITION_START, "NavBarPosition.Start" },
    { "ARK_NAV_BAR_POSITION_END", ARK_NAV_BAR_POSITION_END, "NavBarPosition.End" },
};

std::vector<std::tuple<std::string, Ark_NavBarPosition>> testFixtureEnumNavBarPositionInvalidValues = {
    { "-1", static_cast<Ark_NavBarPosition>(-1) },
    { "INT_MAX", static_cast<Ark_NavBarPosition>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_NavigationMode, std::string>> testFixtureEnumNavigationModeValidValues = {
    { "ARK_NAVIGATION_MODE_STACK", ARK_NAVIGATION_MODE_STACK, "NavigationMode.Stack" },
    { "ARK_NAVIGATION_MODE_SPLIT", ARK_NAVIGATION_MODE_SPLIT, "NavigationMode.Split" },
    { "ARK_NAVIGATION_MODE_AUTO", ARK_NAVIGATION_MODE_AUTO, "NavigationMode.Auto" },
};

std::vector<std::tuple<std::string, Ark_NavigationMode>> testFixtureEnumNavigationModeInvalidValues = {
    { "-1", static_cast<Ark_NavigationMode>(-1) },
    { "INT_MAX", static_cast<Ark_NavigationMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_NavigationTitleMode, std::string>>
    testFixtureEnumNavigationTitleModeValidValues = {
        { "ARK_NAVIGATION_TITLE_MODE_FREE", ARK_NAVIGATION_TITLE_MODE_FREE, "NavigationTitleMode.Free" },
        { "ARK_NAVIGATION_TITLE_MODE_FULL", ARK_NAVIGATION_TITLE_MODE_FULL, "NavigationTitleMode.Full" },
        { "ARK_NAVIGATION_TITLE_MODE_MINI", ARK_NAVIGATION_TITLE_MODE_MINI, "NavigationTitleMode.Mini" },
    };

std::vector<std::tuple<std::string, Ark_NavigationTitleMode>> testFixtureEnumNavigationTitleModeInvalidValues = {
    { "-1", static_cast<Ark_NavigationTitleMode>(-1) },
    { "INT_MAX", static_cast<Ark_NavigationTitleMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_NestedScrollMode, std::string>> testFixtureEnumNestedScrollModeValidValues = {
    { "ARK_NESTED_SCROLL_MODE_SELF_ONLY", ARK_NESTED_SCROLL_MODE_SELF_ONLY, "NestedScrollMode.SELF_ONLY" },
    { "ARK_NESTED_SCROLL_MODE_SELF_FIRST", ARK_NESTED_SCROLL_MODE_SELF_FIRST, "NestedScrollMode.SELF_FIRST" },
    { "ARK_NESTED_SCROLL_MODE_PARENT_FIRST", ARK_NESTED_SCROLL_MODE_PARENT_FIRST, "NestedScrollMode.PARENT_FIRST" },
    { "ARK_NESTED_SCROLL_MODE_PARALLEL", ARK_NESTED_SCROLL_MODE_PARALLEL, "NestedScrollMode.PARALLEL" },
};

std::vector<std::tuple<std::string, Ark_NestedScrollMode>> testFixtureEnumNestedScrollModeInvalidValues = {
    { "-1", static_cast<Ark_NestedScrollMode>(-1) },
    { "INT_MAX", static_cast<Ark_NestedScrollMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_OverScrollMode, std::string>> testFixtureEnumOverScrollModeValidValues = {
    { "ARK_OVER_SCROLL_MODE_NEVER", ARK_OVER_SCROLL_MODE_NEVER, "OverScrollMode.NEVER" },
    { "ARK_OVER_SCROLL_MODE_ALWAYS", ARK_OVER_SCROLL_MODE_ALWAYS, "OverScrollMode.ALWAYS" },
};

std::vector<std::tuple<std::string, Ark_OverScrollMode>> testFixtureEnumOverScrollModeInvalidValues = {
    { "-1", static_cast<Ark_OverScrollMode>(-1) },
    { "INT_MAX", static_cast<Ark_OverScrollMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ProgressStatus, std::string>> testFixtureEnumProgressStatusValidValues = {
    { "ARK_PROGRESS_STATUS_LOADING", ARK_PROGRESS_STATUS_LOADING, "ProgressStatus.LOADING" },
    { "ARK_PROGRESS_STATUS_PROGRESSING", ARK_PROGRESS_STATUS_PROGRESSING, "ProgressStatus.PROGRESSING" },
};

std::vector<std::tuple<std::string, Ark_ProgressStatus>> testFixtureEnumProgressStatusInvalidValues = {
    { "-1", static_cast<Ark_ProgressStatus>(-1) },
    { "INT_MAX", static_cast<Ark_ProgressStatus>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_ProgressStyle, std::string>> testFixtureEnumProgressStyleValidValues = {
    { "ARK_PROGRESS_STYLE_LINEAR", ARK_PROGRESS_STYLE_LINEAR, "ProgressStyle.Linear" },
    { "ARK_PROGRESS_STYLE_RING", ARK_PROGRESS_STYLE_RING, "ProgressStyle.Ring" },
    { "ARK_PROGRESS_STYLE_ECLIPSE", ARK_PROGRESS_STYLE_ECLIPSE, "ProgressStyle.Eclipse" },
    { "ARK_PROGRESS_STYLE_SCALE_RING", ARK_PROGRESS_STYLE_SCALE_RING, "ProgressStyle.ScaleRing" },
    { "ARK_PROGRESS_STYLE_CAPSULE", ARK_PROGRESS_STYLE_CAPSULE, "ProgressStyle.Capsule" },
};

std::vector<std::tuple<std::string, Ark_ProgressStyle>> testFixtureEnumProgressStyleInvalidValues = {
    { "-1", static_cast<Ark_ProgressStyle>(-1) },
    { "INT_MAX", static_cast<Ark_ProgressStyle>(INT_MAX) },
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

std::vector<std::tuple<std::string, Ark_RenderMode, std::string>> testFixtureEnumRenderModeValidValues = {
    { "ARK_RENDER_MODE_ASYNC_RENDER", ARK_RENDER_MODE_ASYNC_RENDER, "RenderMode.ASYNC_RENDER" },
    { "ARK_RENDER_MODE_SYNC_RENDER", ARK_RENDER_MODE_SYNC_RENDER, "RenderMode.SYNC_RENDER" },
};

std::vector<std::tuple<std::string, Ark_RenderMode>> testFixtureEnumRenderModeInvalidValues = {
    { "-1", static_cast<Ark_RenderMode>(-1) },
    { "INT_MAX", static_cast<Ark_RenderMode>(INT_MAX) },
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

std::vector<std::tuple<std::string, Ark_SymbolEffectStrategy, std::string>>
    testFixtureEnumSymbolEffectStrategyValidValues = {
        { "ARK_SYMBOL_EFFECT_STRATEGY_NONE", ARK_SYMBOL_EFFECT_STRATEGY_NONE, "SymbolEffectStrategy.NONE" },
        { "ARK_SYMBOL_EFFECT_STRATEGY_SCALE", ARK_SYMBOL_EFFECT_STRATEGY_SCALE, "SymbolEffectStrategy.SCALE" },
        { "ARK_SYMBOL_EFFECT_STRATEGY_HIERARCHICAL", ARK_SYMBOL_EFFECT_STRATEGY_HIERARCHICAL,
            "SymbolEffectStrategy.HIERARCHICAL" },
    };

std::vector<std::tuple<std::string, Ark_SymbolEffectStrategy>> testFixtureEnumSymbolEffectStrategyInvalidValues = {
    { "-1", static_cast<Ark_SymbolEffectStrategy>(-1) },
    { "INT_MAX", static_cast<Ark_SymbolEffectStrategy>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_SymbolRenderingStrategy, std::string>>
    testFixtureEnumSymbolRenderingStrategyValidValues = {
        { "ARK_SYMBOL_RENDERING_STRATEGY_SINGLE", ARK_SYMBOL_RENDERING_STRATEGY_SINGLE,
            "SymbolRenderingStrategy.SINGLE" },
        { "ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_COLOR", ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_COLOR,
            "SymbolRenderingStrategy.MULTIPLE_COLOR" },
        { "ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_OPACITY", ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_OPACITY,
            "SymbolRenderingStrategy.MULTIPLE_OPACITY" },
    };

std::vector<std::tuple<std::string, Ark_SymbolRenderingStrategy>>
    testFixtureEnumSymbolRenderingStrategyInvalidValues = {
        { "-1", static_cast<Ark_SymbolRenderingStrategy>(-1) },
        { "INT_MAX", static_cast<Ark_SymbolRenderingStrategy>(INT_MAX) },
    };

std::vector<std::tuple<std::string, Ark_TextAlign, std::string>> testFixtureEnumTextAlignValidValues = {
    { "ARK_TEXT_ALIGN_CENTER", ARK_TEXT_ALIGN_CENTER, "TextAlign.Center" },
    { "ARK_TEXT_ALIGN_START", ARK_TEXT_ALIGN_START, "TextAlign.Start" },
    { "ARK_TEXT_ALIGN_END", ARK_TEXT_ALIGN_END, "TextAlign.End" },
    { "ARK_TEXT_ALIGN_JUSTIFY", ARK_TEXT_ALIGN_JUSTIFY, "TextAlign.JUSTIFY" },
};

std::vector<std::tuple<std::string, Ark_TextAlign>> testFixtureEnumTextAlignInvalidValues = {
    { "-1", static_cast<Ark_TextAlign>(-1) },
    { "INT_MAX", static_cast<Ark_TextAlign>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_TextAreaType, std::string>> testFixtureEnumTextAreaTypeValidValues = {
    { "ARK_TEXT_AREA_TYPE_NORMAL", ARK_TEXT_AREA_TYPE_NORMAL, "TextAreaType.NORMAL" },
    { "ARK_TEXT_AREA_TYPE_NUMBER", ARK_TEXT_AREA_TYPE_NUMBER, "TextAreaType.NUMBER" },
    { "ARK_TEXT_AREA_TYPE_PHONE_NUMBER", ARK_TEXT_AREA_TYPE_PHONE_NUMBER, "TextAreaType.PHONE_NUMBER" },
    { "ARK_TEXT_AREA_TYPE_EMAIL", ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
    { "ARK_TEXT_AREA_TYPE_NUMBER_DECIMAL", ARK_TEXT_AREA_TYPE_NUMBER_DECIMAL, "TextAreaType.NUMBER_DECIMAL" },
    { "ARK_TEXT_AREA_TYPE_URL", ARK_TEXT_AREA_TYPE_URL, "TextAreaType.URL" },
};

std::vector<std::tuple<std::string, Ark_TextAreaType>> testFixtureEnumTextAreaTypeInvalidValues = {
    { "-1", static_cast<Ark_TextAreaType>(-1) },
    { "INT_MAX", static_cast<Ark_TextAreaType>(INT_MAX) },
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

std::vector<std::tuple<std::string, Ark_TextContentStyle, std::string>> testFixtureEnumTextContentStyleValidValues = {
    { "ARK_TEXT_CONTENT_STYLE_DEFAULT", ARK_TEXT_CONTENT_STYLE_DEFAULT, "TextContentStyle.DEFAULT" },
    { "ARK_TEXT_CONTENT_STYLE_INLINE", ARK_TEXT_CONTENT_STYLE_INLINE, "TextContentStyle.INLINE" },
};

std::vector<std::tuple<std::string, Ark_TextContentStyle>> testFixtureEnumTextContentStyleInvalidValues = {
    { "-1", static_cast<Ark_TextContentStyle>(-1) },
    { "INT_MAX", static_cast<Ark_TextContentStyle>(INT_MAX) },
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

std::vector<std::tuple<std::string, Ark_TextInputStyle, std::string>> testFixtureEnumTextInputStyleValidValues = {
    { "ARK_TEXT_INPUT_STYLE_DEFAULT", ARK_TEXT_INPUT_STYLE_DEFAULT, "TextInputStyle.Default" },
    { "ARK_TEXT_INPUT_STYLE_INLINE", ARK_TEXT_INPUT_STYLE_INLINE, "TextInputStyle.Inline" },
};

std::vector<std::tuple<std::string, Ark_TextInputStyle>> testFixtureEnumTextInputStyleInvalidValues = {
    { "-1", static_cast<Ark_TextInputStyle>(-1) },
    { "INT_MAX", static_cast<Ark_TextInputStyle>(INT_MAX) },
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

std::vector<std::tuple<std::string, Ark_TitleHeight, std::string>> testFixtureEnumTitleHeightValidValues = {
    { "ARK_TITLE_HEIGHT_MAIN_ONLY", ARK_TITLE_HEIGHT_MAIN_ONLY, "TitleHeight.MainOnly" },
    { "ARK_TITLE_HEIGHT_MAIN_WITH_SUB", ARK_TITLE_HEIGHT_MAIN_WITH_SUB, "TitleHeight.MainWithSub" },
};

std::vector<std::tuple<std::string, Ark_TitleHeight>> testFixtureEnumTitleHeightInvalidValues = {
    { "-1", static_cast<Ark_TitleHeight>(-1) },
    { "INT_MAX", static_cast<Ark_TitleHeight>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_WaterFlowLayoutMode, std::string>>
    testFixtureEnumWaterFlowLayoutModeValidValues = {
        { "ARK_WATER_FLOW_LAYOUT_MODE_ALWAYS_TOP_DOWN", ARK_WATER_FLOW_LAYOUT_MODE_ALWAYS_TOP_DOWN,
            "WaterFlowLayoutMode.ALWAYS_TOP_DOWN" },
        { "ARK_WATER_FLOW_LAYOUT_MODE_SLIDING_WINDOW", ARK_WATER_FLOW_LAYOUT_MODE_SLIDING_WINDOW,
            "WaterFlowLayoutMode.SLIDING_WINDOW" },
    };

std::vector<std::tuple<std::string, Ark_WaterFlowLayoutMode>> testFixtureEnumWaterFlowLayoutModeInvalidValues = {
    { "-1", static_cast<Ark_WaterFlowLayoutMode>(-1) },
    { "INT_MAX", static_cast<Ark_WaterFlowLayoutMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_WebDarkMode, std::string>> testFixtureEnumWebDarkModeValidValues = {
    { "ARK_WEB_DARK_MODE_OFF", ARK_WEB_DARK_MODE_OFF, "WebDarkMode.Off" },
    { "ARK_WEB_DARK_MODE_ON", ARK_WEB_DARK_MODE_ON, "WebDarkMode.On" },
    { "ARK_WEB_DARK_MODE_AUTO", ARK_WEB_DARK_MODE_AUTO, "WebDarkMode.Auto" },
};

std::vector<std::tuple<std::string, Ark_WebDarkMode>> testFixtureEnumWebDarkModeInvalidValues = {
    { "-1", static_cast<Ark_WebDarkMode>(-1) },
    { "INT_MAX", static_cast<Ark_WebDarkMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_WebKeyboardAvoidMode, std::string>>
    testFixtureEnumWebKeyboardAvoidModeValidValues = {
        { "ARK_WEB_KEYBOARD_AVOID_MODE_RESIZE_VISUAL", ARK_WEB_KEYBOARD_AVOID_MODE_RESIZE_VISUAL,
            "WebKeyboardAvoidMode.RESIZE_VISUAL" },
        { "ARK_WEB_KEYBOARD_AVOID_MODE_RESIZE_CONTENT", ARK_WEB_KEYBOARD_AVOID_MODE_RESIZE_CONTENT,
            "WebKeyboardAvoidMode.RESIZE_CONTENT" },
        { "ARK_WEB_KEYBOARD_AVOID_MODE_OVERLAYS_CONTENT", ARK_WEB_KEYBOARD_AVOID_MODE_OVERLAYS_CONTENT,
            "WebKeyboardAvoidMode.OVERLAYS_CONTENT" },
    };

std::vector<std::tuple<std::string, Ark_WebKeyboardAvoidMode>> testFixtureEnumWebKeyboardAvoidModeInvalidValues = {
    { "-1", static_cast<Ark_WebKeyboardAvoidMode>(-1) },
    { "INT_MAX", static_cast<Ark_WebKeyboardAvoidMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_WebLayoutMode, std::string>> testFixtureEnumWebLayoutModeValidValues = {
    { "ARK_WEB_LAYOUT_MODE_NONE", ARK_WEB_LAYOUT_MODE_NONE, "WebLayoutMode.NONE" },
    { "ARK_WEB_LAYOUT_MODE_FIT_CONTENT", ARK_WEB_LAYOUT_MODE_FIT_CONTENT, "WebLayoutMode.FIT_CONTENT" },
};

std::vector<std::tuple<std::string, Ark_WebLayoutMode>> testFixtureEnumWebLayoutModeInvalidValues = {
    { "-1", static_cast<Ark_WebLayoutMode>(-1) },
    { "INT_MAX", static_cast<Ark_WebLayoutMode>(INT_MAX) },
};

} // namespace OHOS::Ace::NG::Fixtures
