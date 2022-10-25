/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_algorithm.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {

constexpr int32_t ANIMATION_DURATION_DEFAULT = 200;

} // namespace

void TabsNode::AddChildToGroup(const RefPtr<UINode>& child)
{
    if (swiperChildren_.find(child->GetId()) != swiperChildren_.end()) {
        LOGW("Child has already exist.");
        return;
    }

    swiperChildren_.emplace(child->GetId());
    auto swiperNode = GetChildren().back();
    if (swiperNode) {
        child->MountToParent(swiperNode);
    }
}

void TabsNode::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    FrameNode::ToJsonValue(json);
    json->Put("index", GetIndex());
    json->Put("scrollable", Scrollable() ? "true" : "false");
    json->Put("animationDuration", GetAnimationDuration());
    json->Put("barMode", GetTabBarMode() == TabBarMode::SCROLLABLE ? "BarMode.Scrollable" : "BarMode.Fixed");
    json->Put("barWidth", GetBarWidth().ToString().c_str());
    json->Put("barHeight", GetBarHeight().ToString().c_str());
}

bool TabsNode::Scrollable() const
{
    if (!swiperId_.has_value()) {
        return true;
    }
    auto swiperNode = GetFrameNode(V2::SWIPER_ETS_TAG, swiperId_.value());
    CHECK_NULL_RETURN(swiperNode, true);
    auto paintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, true);
    return !paintProperty->GetDisableSwipe().value_or(false);
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

} // namespace OHOS::Ace::NG