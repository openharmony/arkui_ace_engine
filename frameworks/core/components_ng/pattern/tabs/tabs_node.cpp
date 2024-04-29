/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tabs_node.h"

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_algorithm.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

constexpr int32_t ANIMATION_DURATION_DEFAULT = 200;
const std::string BAR_BLURSTYLE[] = {
    "BlurStyle.NONE",
    "BlurStyle.Thin",
    "BlurStyle.Regular",
    "BlurStyle.Thick",
    "BlurStyle.BACKGROUND_THIN",
    "BlurStyle.BACKGROUND_REGULAR",
    "BlurStyle.BACKGROUND_THICK",
    "BlurStyle.BACKGROUND_ULTRA_THICK",
    "BlurStyle.COMPONENT_ULTRA_THIN",
    "BlurStyle.COMPONENT_THIN",
    "BlurStyle.COMPONENT_REGULAR",
    "BlurStyle.COMPONENT_THICK",
    "BlurStyle.COMPONENT_ULTRA_THICK"
};

} // namespace

void TabsNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    if (swiperChildren_.find(child->GetId()) != swiperChildren_.end()) {
        return;
    }

    swiperChildren_.emplace(child->GetId());
    auto swiperNode = GetTabs();
    if (swiperNode) {
        child->MountToParent(swiperNode);
    }
}

void TabsNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    FrameNode::ToJsonValue(json, filter);
    json->PutExtAttr("index", std::to_string(GetIndex()).c_str(), filter);
    json->PutFixedAttr("scrollable", Scrollable(), filter, FIXED_ATTR_SCROLLABLE);
    json->PutExtAttr("animationDuration", GetAnimationDuration(), filter);
    if (GetTabBarMode() == TabBarMode::SCROLLABLE) {
        auto optionsJson = JsonUtil::Create(true);
        auto options = GetScrollableBarModeOptions();
        optionsJson->Put("margin", options.margin.ToString().c_str());
        if (options.nonScrollableLayoutStyle == LayoutStyle::ALWAYS_AVERAGE_SPLIT) {
            optionsJson->Put("nonScrollableLayoutStyle", "LayoutStyle.ALWAYS_AVERAGE_SPLIT");
        } else if (options.nonScrollableLayoutStyle == LayoutStyle::SPACE_BETWEEN_OR_CENTER) {
            optionsJson->Put("nonScrollableLayoutStyle", "LayoutStyle.SPACE_BETWEEN_OR_CENTER");
        } else {
            optionsJson->Put("nonScrollableLayoutStyle", "LayoutStyle.ALWAYS_CENTER");
        }
        std::string barMode = "BarMode.Scrollable," + optionsJson->ToString();
        json->PutExtAttr("barMode", barMode.c_str(), filter);
    } else {
        json->PutExtAttr("barMode", "BarMode.Fixed", filter);
    }
    json->PutExtAttr("barWidth", std::to_string(GetBarWidth().Value()).c_str(), filter);
    json->PutExtAttr("barHeight",
        GetBarAdaptiveHeight() ? "auto" : std::to_string(GetBarHeight().Value()).c_str(), filter);
    json->PutExtAttr("fadingEdge", GetFadingEdge() ? "true" : "false", filter);
    json->PutExtAttr("barBackgroundColor", GetBarBackgroundColor().ColorToString().c_str(), filter);
    json->PutExtAttr("barBackgroundBlurStyle",
        BAR_BLURSTYLE[static_cast<int32_t>(GetBarBackgroundBlurStyle())].c_str(), filter);

    auto barGridAlignJson = JsonUtil::Create(true);
    auto barGridAlign = GetBarGridAlign();
    barGridAlignJson->Put("gutter", barGridAlign.gutter.ToString().c_str());
    barGridAlignJson->Put("margin", barGridAlign.margin.ToString().c_str());
    barGridAlignJson->Put("sm", std::to_string(barGridAlign.sm).c_str());
    barGridAlignJson->Put("md", std::to_string(barGridAlign.md).c_str());
    barGridAlignJson->Put("lg", std::to_string(barGridAlign.lg).c_str());

    json->PutExtAttr("barGridAlign", barGridAlignJson, filter);
}

bool TabsNode::Scrollable() const
{
    if (!swiperId_.has_value()) {
        return true;
    }
    auto swiperNode = GetFrameNode(V2::SWIPER_ETS_TAG, swiperId_.value());
    CHECK_NULL_RETURN(swiperNode, true);
    auto props = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, true);
    return !props->GetDisableSwipe().value_or(false);
}

int32_t TabsNode::GetAnimationDuration() const
{
    if (!swiperId_.has_value()) {
        return ANIMATION_DURATION_DEFAULT;
    }
    auto swiperNode = GetFrameNode(V2::SWIPER_ETS_TAG, swiperId_.value());
    CHECK_NULL_RETURN(swiperNode, ANIMATION_DURATION_DEFAULT);
    auto paintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, ANIMATION_DURATION_DEFAULT);
    return paintProperty->GetDuration().value_or(ANIMATION_DURATION_DEFAULT);
}

int32_t TabsNode::GetIndex() const
{
    if (!swiperId_.has_value()) {
        return 0;
    }
    auto swiperNode = GetFrameNode(V2::SWIPER_ETS_TAG, swiperId_.value());
    CHECK_NULL_RETURN(swiperNode, 0);
    auto layoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);
    return layoutProperty->GetIndex().value_or(0);
}

TabBarMode TabsNode::GetTabBarMode() const
{
    if (!tabBarId_.has_value()) {
        return TabBarMode::FIXED;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, TabBarMode::FIXED);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarProperty, TabBarMode::FIXED);
    return tabBarProperty->GetTabBarMode().value_or(TabBarMode::FIXED);
}

Dimension TabsNode::GetBarWidth() const
{
    if (!tabBarId_.has_value()) {
        return 0.0_vp;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, 0.0_vp);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarProperty, 0.0_vp);
    return tabBarProperty->GetTabBarWidth().value_or(0.0_vp);
}

bool TabsNode::GetBarAdaptiveHeight() const
{
    if (!tabBarId_.has_value()) {
        return false;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, false);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarProperty, false);
    return tabBarProperty->GetBarAdaptiveHeight().value_or(false);
}

Dimension TabsNode::GetBarHeight() const
{
    if (!tabBarId_.has_value()) {
        return 0.0_vp;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, 0.0_vp);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarProperty, 0.0_vp);
    return tabBarProperty->GetTabBarHeight().value_or(0.0_vp);
}

Color TabsNode::GetBarBackgroundColor() const
{
    auto backgroundColor = Color::BLACK.BlendOpacity(0.0f);
    if (!tabBarId_.has_value()) {
        return backgroundColor;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, backgroundColor);
    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    CHECK_NULL_RETURN(tabBarPaintProperty, backgroundColor);
    return tabBarPaintProperty->GetBarBackgroundColor().value_or(backgroundColor);
}

BlurStyle TabsNode::GetBarBackgroundBlurStyle() const
{
    auto barBackgroundBlurStyle = BlurStyle::NO_MATERIAL;
    if (!tabBarId_.has_value()) {
        return barBackgroundBlurStyle;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, barBackgroundBlurStyle);
    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    CHECK_NULL_RETURN(tabBarPaintProperty, barBackgroundBlurStyle);
    return tabBarPaintProperty->GetTabBarBlurStyle().value_or(barBackgroundBlurStyle);
}

bool TabsNode::GetFadingEdge() const
{
    if (!tabBarId_.has_value()) {
        return true;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, true);
    auto tabBarProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    CHECK_NULL_RETURN(tabBarProperty, true);
    return tabBarProperty->GetFadingEdge().value_or(true);
}

BarGridColumnOptions TabsNode::GetBarGridAlign() const
{
    BarGridColumnOptions option;
    if (!tabBarId_.has_value()) {
        return option;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, option);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarProperty, option);
    return tabBarProperty->GetBarGridAlign().value_or(option);
}

ScrollableBarModeOptions TabsNode::GetScrollableBarModeOptions() const
{
    ScrollableBarModeOptions option;
    if (!tabBarId_.has_value()) {
        return option;
    }
    auto tabBarNode = GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarId_.value());
    CHECK_NULL_RETURN(tabBarNode, option);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarProperty, option);
    return tabBarProperty->GetScrollableBarModeOptions().value_or(option);
}
} // namespace OHOS::Ace::NG
