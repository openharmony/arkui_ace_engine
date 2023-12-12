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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_navigation_modifier.h"

#include "base/geometry/calc_dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr int32_t NAV_BAR_POSITION_RANGE_MODIFIER = 1;
constexpr int32_t NAVIGATION_MODE_RANGE_MODIFIER = 2;
constexpr int32_t DEFAULT_NAV_BAR_WIDTH_FOR_MODIFIER = 240;
void SetHideToolBar(NodeHandle node, bool hide)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideToolBar(frameNode, hide);
}

void ResetHideToolBar(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideToolBar(frameNode, false);
}

void SetMinContentWidth(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    NavigationModelNG::SetMinContentWidth(frameNode, width);
}

void ResetMinContentWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetMinContentWidth(frameNode, DEFAULT_MIN_CONTENT_WIDTH);
}

void SetMinNavBarWidth(NodeHandle node, double minValue, int minUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension minNavBarWidth = Dimension(minValue, static_cast<OHOS::Ace::DimensionUnit>(minUnit));
    if (LessNotEqual(minNavBarWidth.Value(), 0.0)) {
        minNavBarWidth = DEFAULT_MIN_NAV_BAR_WIDTH;
    }

    NavigationModelNG::SetMinNavBarWidth(frameNode, minNavBarWidth);
}

void ResetMinNavBarWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension minNavBarWidth = DEFAULT_MIN_NAV_BAR_WIDTH;
    NavigationModelNG::SetMinNavBarWidth(frameNode, minNavBarWidth);
}

void SetMaxNavBarWidth(NodeHandle node, double maxValue, int maxUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension maxNavBarWidth = Dimension(maxValue, static_cast<OHOS::Ace::DimensionUnit>(maxUnit));
    if (LessNotEqual(maxNavBarWidth.Value(), 0.0)) {
        maxNavBarWidth = DEFAULT_MAX_NAV_BAR_WIDTH;
    }
    
    NavigationModelNG::SetMaxNavBarWidth(frameNode, maxNavBarWidth);
}

void ResetMaxNavBarWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension maxNavBarWidth = DEFAULT_MAX_NAV_BAR_WIDTH;
    NavigationModelNG::SetMaxNavBarWidth(frameNode, maxNavBarWidth);
}

void SetNavBarWidth(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    NavigationModelNG::SetNavBarWidth(frameNode, width);
}

void ResetNavBarWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension navBarWidth;
    navBarWidth.SetValue(DEFAULT_NAV_BAR_WIDTH_FOR_MODIFIER);
    NavigationModelNG::SetNavBarWidth(frameNode, navBarWidth);
}

void SetNavBarPosition(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value >= 0 && value <= NAV_BAR_POSITION_RANGE_MODIFIER) {
        NavigationModelNG::SetNavBarPosition(frameNode, static_cast<NG::NavBarPosition>(value));
    } else {
        NavigationModelNG::SetNavBarPosition(frameNode, NG::NavBarPosition::START);
    }
}

void ResetNavBarPosition(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetNavBarPosition(frameNode, NG::NavBarPosition::START);
}

void SetHideNavBar(NodeHandle node, bool hideNavBar)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideNavBar(frameNode, hideNavBar);
}

void ResetHideNavBar(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideNavBar(frameNode, false);
}

void SetSubtitle(NodeHandle node, const char* subtitle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string value = subtitle;
    NavigationModelNG::SetSubtitle(frameNode, value);
}

void ResetSubtitle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetSubtitle(frameNode, "");
}

void SetHideBackButton(NodeHandle node, bool hideBackButton)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideBackButton(frameNode, hideBackButton);
}

void ResetHideBackButton(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideBackButton(frameNode, false);
}

void SetTitleMode(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetTitleMode(frameNode, static_cast<NG::NavigationTitleMode>(value));
}

void ResetTitleMode(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetTitleMode(frameNode, NG::NavigationTitleMode::FREE);
}

void SetUsrNavigationMode(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value >= 0 && value <= NAVIGATION_MODE_RANGE_MODIFIER) {
        NavigationModelNG::SetUsrNavigationMode(frameNode, static_cast<NG::NavigationMode>(value));
    } else {
        NavigationModelNG::SetUsrNavigationMode(frameNode, NG::NavigationMode::AUTO);
    }
}
void ResetUsrNavigationMode(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetUsrNavigationMode(frameNode, NG::NavigationMode::AUTO);
}

void SetNavHideTitleBar(NodeHandle node, bool hideBackButton)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideTitleBar(frameNode, hideBackButton);
}

void ResetNavHideTitleBar(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideTitleBar(frameNode, false);
}

ArkUINavigationModifierAPI GetNavigationModifier()
{
    static const ArkUINavigationModifierAPI modifier = {
        SetHideToolBar,
        ResetHideToolBar,
        SetHideNavBar,
        ResetHideNavBar,
        SetTitleMode,
        ResetTitleMode,
        SetHideBackButton,
        ResetHideBackButton,
        SetSubtitle,
        ResetSubtitle,
        ResetUsrNavigationMode,
        SetUsrNavigationMode,
        SetNavHideTitleBar,
        ResetNavHideTitleBar,
        SetNavBarPosition,
        ResetNavBarPosition,
        SetMinContentWidth,
        ResetMinContentWidth,
        SetMaxNavBarWidth,
        ResetMaxNavBarWidth,
        SetMinNavBarWidth,
        ResetMinNavBarWidth,
        SetNavBarWidth,
        ResetNavBarWidth,
    };

    return modifier;
}
} // namespace OHOS::Ace::NG