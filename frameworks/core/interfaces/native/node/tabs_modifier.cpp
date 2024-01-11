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

#include "base/utils/string_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/bridge/common/utils/utils.h"

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

void SetTabBarMode(NodeHandle node, int32_t tabsBarMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto barMode = static_cast<TabBarMode>(tabsBarMode);
    TabsModelNG::SetTabBarMode(frameNode, barMode);
}
void SetScrollableBarModeOptions(NodeHandle node, const double value, const int unit, const int layoutStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableBarModeOptions option;
    CalcDimension margin = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    option.margin = margin;
    option.nonScrollableLayoutStyle = (static_cast<LayoutStyle>(layoutStyle));
    TabsModelNG::SetScrollableBarModeOptions(frameNode, option);
}
void SetBarGridAlign(NodeHandle node, const double* values, int32_t valuesLength, const int* units, int32_t unitsLength)
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
void SetDivider(NodeHandle node, uint32_t color, const double* values, const int32_t* units, int32_t length)
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
void SetFadingEdge(NodeHandle node, bool fadingEdge)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetFadingEdge(frameNode, fadingEdge);
}
void SetBarBackgroundColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarBackgroundColor(frameNode, Color(color));
}
void SetBarOverlap(NodeHandle node, bool barOverlap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarOverlap(frameNode, barOverlap);
}
void SetIsVertical(NodeHandle node, bool isVertical)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetIsVertical(frameNode, isVertical);
}
void SetTabBarPosition(NodeHandle node, int32_t barVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetTabBarPosition(frameNode, static_cast<BarPosition>(barVal));
}
void SetScrollable(NodeHandle node, bool scrollable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetScrollable(frameNode, scrollable);
}
void SetBarAdaptiveHeight(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarAdaptiveHeight(frameNode, value);
}
void SetTabBarWidth(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    TabsModelNG::SetTabBarWidth(frameNode, width);
}
void SetTabBarHeight(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    TabsModelNG::SetTabBarHeight(frameNode, width);
}

void SetAnimationDuration(NodeHandle node, float duration)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (std::isnan(duration)) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto tabTheme = pipelineContext->GetTheme<TabTheme>();
        CHECK_NULL_VOID(tabTheme);
        TabsModelNG::SetAnimationDuration(frameNode, static_cast<float>(tabTheme->GetTabContentAnimationDuration()));
    }
    TabsModelNG::SetAnimationDuration(frameNode, duration);
}
void ResetTabBarMode(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabBarMode barMode = TabBarMode::FIXED;
    TabsModelNG::SetTabBarMode(frameNode, barMode);
}
void ResetScrollableBarModeOptions(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableBarModeOptions defaultOption;
    CalcDimension margin = Dimension(0.0, DimensionUnit::VP);
    defaultOption.margin = margin;
    defaultOption.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    TabsModelNG::SetScrollableBarModeOptions(frameNode, defaultOption);
}
void ResetBarGridAlign(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BarGridColumnOptions columnOption;
    TabsModelNG::SetBarGridAlign(frameNode, columnOption);
}
void ResetDivider(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    TabsItemDivider divider;
    divider.isNull = true;

    TabsModelNG::SetDivider(frameNode, divider);
}

void ResetFadingEdge(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetFadingEdge(frameNode, true);
}
void ResetBarBackgroundColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarBackgroundColor(frameNode, Color::BLACK.BlendOpacity(0.0f));
}
void ResetBarOverlap(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarOverlap(frameNode, false);
}
void ResetIsVertical(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetIsVertical(frameNode, false);
}

void ResetTabBarPosition(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetTabBarPosition(frameNode, BarPosition::START);
}

void ResetScrollable(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetScrollable(frameNode, true);
}
void ResetTabBarWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(-1.0, DimensionUnit::VP);
    TabsModelNG::SetTabBarWidth(frameNode, width);
}
void ResetTabBarHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(-1.0, DimensionUnit::VP);
    TabsModelNG::SetTabBarHeight(frameNode, width);
}

void ResetAnimationDuration(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetAnimationDuration(frameNode, DEFAULT_ANIMATION_DURATION);
}

void ResetBarAdaptiveHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarAdaptiveHeight(frameNode, false);
}

void SetTabClip(NodeHandle node, bool clipEdge)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetClipEdge(frameNode, clipEdge);
}

void ResetTabClip(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetClipEdge(frameNode, false);
}

ArkUITabsModifierAPI GetTabsModifier()
{
    static const ArkUITabsModifierAPI modifier = {
        SetTabBarMode,
        SetScrollableBarModeOptions,
        SetBarGridAlign,
        SetDivider,
        SetFadingEdge,
        SetBarBackgroundColor,
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
    };

    return modifier;
}
} // namespace OHOS::Ace::NG