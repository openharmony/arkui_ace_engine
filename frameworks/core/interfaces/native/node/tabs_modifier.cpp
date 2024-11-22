/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/tabs_modifier.h"

#include "core/components_ng/pattern/tabs/tabs_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int DEFAULT_LENGTH = 3;
constexpr int DEFAULT_LENGTH_OF_BAR_GRID_ALIGN = 5;
constexpr int DEFAULT_LENGTH_OF_BAR_GRID_ALIGN_VALUES = 2;
constexpr int DEFAULT_ANIMATION_DURATION = 300;

void SetTabBarMode(ArkUINodeHandle node, ArkUI_Int32 tabsBarMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto barMode = static_cast<TabBarMode>(tabsBarMode);
    TabsModelNG::SetTabBarMode(frameNode, barMode);
}
void SetScrollableBarModeOptions(ArkUINodeHandle node, const ArkUI_Float32 value,
    ArkUI_Int32 unit, ArkUI_Int32 layoutStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableBarModeOptions option;
    CalcDimension margin = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    option.margin = margin;
    option.nonScrollableLayoutStyle = (static_cast<LayoutStyle>(layoutStyle));
    TabsModelNG::SetScrollableBarModeOptions(frameNode, option);
}
void SetBarGridAlign(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesLength,
    const ArkUI_Int32* units, ArkUI_Int32 unitsLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (unitsLength != DEFAULT_LENGTH_OF_BAR_GRID_ALIGN || valuesLength != DEFAULT_LENGTH_OF_BAR_GRID_ALIGN_VALUES) {
        return;
    }
    BarGridColumnOptions columnOption;
    columnOption.sm = units[NUM_2];
    columnOption.md = units[NUM_3];
    columnOption.lg = units[NUM_4];
    columnOption.gutter = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    columnOption.margin = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));

    TabsModelNG::SetBarGridAlign(frameNode, columnOption);
}
void SetDivider(ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values, const ArkUI_Int32* units,
    ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (length != DEFAULT_LENGTH) {
        return;
    }
    TabsItemDivider divider;
    divider.strokeWidth = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    divider.startMargin = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    divider.endMargin = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    divider.color = Color(color);

    TabsModelNG::SetDivider(frameNode, divider);
}
void SetFadingEdge(ArkUINodeHandle node, ArkUI_Bool fadingEdge)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetFadingEdge(frameNode, fadingEdge);
}
void SetBarBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarBackgroundColor(frameNode, Color(color));
}
void SetBarBackgroundBlurStyle(ArkUINodeHandle node, ArkUITabBarBackgroundBlurStyle* styleOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Int32 blurStyle = styleOption->blurStyle;
    ArkUI_Int32 colorMode = styleOption->colorMode;
    ArkUI_Int32 adaptiveColor = styleOption->adaptiveColor;
    ArkUI_Int32 policy = styleOption->policy;
    ArkUI_Int32 blurType = styleOption->blurType;
    BlurStyleOption bgBlurStyle;
    if (blurStyle >= 0) {
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            bgBlurStyle.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }
    bool isHasOptions = !((styleOption->colorMode < 0) && (styleOption->adaptiveColor < 0) &&
        (styleOption->scale < 0) && (styleOption->blurValuesSize == 0));
    if (isHasOptions) {
        if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
            colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
            bgBlurStyle.colorMode = static_cast<ThemeColorMode>(colorMode);
        }
        if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
            adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
            bgBlurStyle.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
        }
        bgBlurStyle.scale = std::clamp(styleOption->scale, 0.0f, 1.0f);
        BlurOption blurOption;
        blurOption.grayscale.assign(styleOption->blurValues, styleOption->blurValues + styleOption->blurValuesSize);
        bgBlurStyle.blurOption = blurOption;
    }
    bgBlurStyle.policy = static_cast<BlurStyleActivePolicy>(policy);
    bgBlurStyle.blurType = static_cast<BlurType>(blurType);
    bgBlurStyle.isValidColor = styleOption->isValidColor;
    Color inactiveColor(styleOption->inactiveColor);
    bgBlurStyle.inactiveColor = inactiveColor;
    TabsModelNG::SetBarBackgroundBlurStyle(frameNode, bgBlurStyle);
}
void SetBarOverlap(ArkUINodeHandle node, ArkUI_Bool barOverlap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarOverlap(frameNode, barOverlap);
}
void SetIsVertical(ArkUINodeHandle node, ArkUI_Bool isVertical)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetIsVertical(frameNode, isVertical);
}
void SetTabBarPosition(ArkUINodeHandle node, ArkUI_Int32 barVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetTabBarPosition(frameNode, static_cast<BarPosition>(barVal));
}
void SetScrollable(ArkUINodeHandle node, ArkUI_Bool scrollable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetScrollable(frameNode, scrollable);
}
void SetBarAdaptiveHeight(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarAdaptiveHeight(frameNode, value);
}
void SetTabBarWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    TabsModelNG::SetTabBarWidth(frameNode, width);
}
void SetTabBarHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    TabsModelNG::SetTabBarHeight(frameNode, width);
}

void SetAnimationDuration(ArkUINodeHandle node, ArkUI_Float32 duration)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (std::isnan(duration)) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto tabTheme = pipelineContext->GetTheme<TabTheme>();
        CHECK_NULL_VOID(tabTheme);
        TabsModelNG::SetAnimationDuration(frameNode,
            static_cast<ArkUI_Float32>(tabTheme->GetTabContentAnimationDuration()));
    }
    TabsModelNG::SetAnimationDuration(frameNode, duration);
}
void ResetTabBarMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabBarMode barMode = TabBarMode::FIXED;
    TabsModelNG::SetTabBarMode(frameNode, barMode);
}
void ResetScrollableBarModeOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableBarModeOptions defaultOption;
    CalcDimension margin = Dimension(0.0, DimensionUnit::VP);
    defaultOption.margin = margin;
    defaultOption.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    TabsModelNG::SetScrollableBarModeOptions(frameNode, defaultOption);
}
void ResetBarGridAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BarGridColumnOptions columnOption;
    TabsModelNG::SetBarGridAlign(frameNode, columnOption);
}
void ResetDivider(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    TabsItemDivider divider;
    divider.isNull = true;

    TabsModelNG::SetDivider(frameNode, divider);
}

void ResetFadingEdge(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetFadingEdge(frameNode, true);
}
void ResetBarBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarBackgroundColor(frameNode, Color::BLACK.BlendOpacity(0.0f));
}
void ResetBarBackgroundBlurStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption bgBlurStyle;
    TabsModelNG::SetBarBackgroundBlurStyle(frameNode, bgBlurStyle);
}
void ResetBarOverlap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarOverlap(frameNode, false);
}
void ResetIsVertical(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetIsVertical(frameNode, false);
}

void ResetTabBarPosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetTabBarPosition(frameNode, BarPosition::START);
}

void ResetScrollable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetScrollable(frameNode, true);
}
void ResetTabBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(-1.0, DimensionUnit::VP);
    TabsModelNG::SetTabBarWidth(frameNode, width);
}
void ResetTabBarHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(-1.0, DimensionUnit::VP);
    TabsModelNG::SetTabBarHeight(frameNode, width);
}

void ResetAnimationDuration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetAnimationDuration(frameNode, DEFAULT_ANIMATION_DURATION);
}

void ResetBarAdaptiveHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarAdaptiveHeight(frameNode, false);
}

void SetTabClip(ArkUINodeHandle node, ArkUI_Bool clipEdge)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetClipEdge(frameNode, clipEdge);
}

void ResetTabClip(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetClipEdge(frameNode, false);
}

void SetTabEdgeEffect(ArkUINodeHandle node, ArkUI_Uint32 edgeEffect)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetEdgeEffect(frameNode, edgeEffect);
}

void ResetTabEdgeEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetEdgeEffect(frameNode, NUM_0);
}

void SetTabWidthAuto(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
    TabsModelNG::SetWidthAuto(frameNode, true);
}

void ResetTabWidthAuto(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetWidthAuto(frameNode, false);
}

void SetTabHeightAuto(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
    TabsModelNG::SetHeightAuto(frameNode, true);
}

void ResetTabHeightAuto(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetHeightAuto(frameNode, false);
}

void SetAnimateMode(ArkUINodeHandle node, ArkUI_Uint32 mode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetAnimateMode(frameNode, static_cast<TabAnimateMode>(mode));
}

void ResetAnimateMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetAnimateMode(frameNode, TabAnimateMode::CONTENT_FIRST);
}

void SetBarBackgroundEffect(ArkUINodeHandle node, ArkUITabBarBackgroundEffect* effectOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension radius;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FOURTEEN)) {
        radius = CalcDimension(effectOption->radius, DimensionUnit::VP);
    } else {
        radius = CalcDimension(effectOption->radius, DimensionUnit::PX);
    }
    Color color(effectOption->color);
    BlurOption blurOption;
    blurOption.grayscale.assign(effectOption->blurValues, effectOption->blurValues + effectOption->blurValuesSize);

    EffectOption option;
    option.radius = radius;
    option.saturation = effectOption->saturation;
    option.brightness = effectOption->brightness;
    option.color = color;
    option.adaptiveColor = static_cast<AdaptiveColor>(effectOption->adaptiveColor);
    option.blurOption = blurOption;
    option.blurType = static_cast<BlurType>(effectOption->blurType);
    option.policy = static_cast<BlurStyleActivePolicy>(effectOption->policy);
    Color inactiveColor(effectOption->inactiveColor);
    option.inactiveColor = inactiveColor;
    option.isValidColor = effectOption->isValidColor;
    TabsModelNG::SetBarBackgroundEffect(frameNode, option);
}

void ResetBarBackgroundEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension radius;
    radius.SetValue(0.0f);
    double saturation = 1.0f;
    double brightness = 1.0f;
    Color color = Color::TRANSPARENT;
    color.SetValue(Color::TRANSPARENT.GetValue());
    auto adaptiveColor = AdaptiveColor::DEFAULT;
    BlurOption blurOption;
    EffectOption effectOption = { radius, saturation, brightness, color, adaptiveColor, blurOption };
    TabsModelNG::SetBarBackgroundEffect(frameNode, effectOption);
}

namespace NodeModifier {
const ArkUITabsModifier* GetTabsModifier()
{
    static const ArkUITabsModifier modifier = {
        SetTabBarMode,
        SetScrollableBarModeOptions,
        SetBarGridAlign,
        SetDivider,
        SetFadingEdge,
        SetBarBackgroundColor,
        SetBarBackgroundBlurStyle,
        SetBarOverlap,
        SetIsVertical,
        SetTabBarPosition,
        SetScrollable,
        SetTabBarWidth,
        SetTabBarHeight,
        SetBarAdaptiveHeight,
        SetAnimationDuration,
        ResetTabBarMode,
        ResetScrollableBarModeOptions,
        ResetBarGridAlign,
        ResetDivider,
        ResetFadingEdge,
        ResetBarBackgroundColor,
        ResetBarBackgroundBlurStyle,
        ResetBarOverlap,
        ResetIsVertical,
        ResetTabBarPosition,
        ResetScrollable,
        ResetTabBarWidth,
        ResetTabBarHeight,
        ResetBarAdaptiveHeight,
        ResetAnimationDuration,
        SetTabClip,
        ResetTabClip,
        SetTabEdgeEffect,
        ResetTabEdgeEffect,
        SetTabWidthAuto,
        ResetTabWidthAuto,
        SetTabHeightAuto,
        ResetTabHeightAuto,
        SetAnimateMode,
        ResetAnimateMode,
        SetBarBackgroundEffect,
        ResetBarBackgroundEffect,
    };

    return &modifier;
}

const CJUITabsModifier* GetCJUITabsModifier()
{
    static const CJUITabsModifier modifier = {
        SetTabBarMode,
        SetScrollableBarModeOptions,
        SetBarGridAlign,
        SetDivider,
        SetFadingEdge,
        SetBarBackgroundColor,
        SetBarBackgroundBlurStyle,
        SetBarOverlap,
        SetIsVertical,
        SetTabBarPosition,
        SetScrollable,
        SetTabBarWidth,
        SetTabBarHeight,
        SetBarAdaptiveHeight,
        SetAnimationDuration,
        ResetTabBarMode,
        ResetScrollableBarModeOptions,
        ResetBarGridAlign,
        ResetDivider,
        ResetFadingEdge,
        ResetBarBackgroundColor,
        ResetBarBackgroundBlurStyle,
        ResetBarOverlap,
        ResetIsVertical,
        ResetTabBarPosition,
        ResetScrollable,
        ResetTabBarWidth,
        ResetTabBarHeight,
        ResetBarAdaptiveHeight,
        ResetAnimationDuration,
        SetTabClip,
        ResetTabClip,
        SetTabEdgeEffect,
        ResetTabEdgeEffect,
        SetTabWidthAuto,
        ResetTabWidthAuto,
        SetTabHeightAuto,
        ResetTabHeightAuto,
        SetAnimateMode,
        ResetAnimateMode,
        SetBarBackgroundEffect,
        ResetBarBackgroundEffect,
    };

    return &modifier;
}
}
} // namespace OHOS::Ace::NG