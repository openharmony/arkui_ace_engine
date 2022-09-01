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

#include "core/components_ng/pattern/tabs/tabs_view.h"
#include <type_traits>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void TabsView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto groupNode = GetOrCreateGroupNode(V2::TABS_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });

    // Create Swiper node to contain TabContent.
    auto swiperNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    swiperLayoutProperty->UpdateLayoutWeight(3.0); // TODO use tabBarWidth and tabBarHeight.
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    swiperPaintProperty->UpdateLoop(false);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperController = swiperPattern->GetSwiperController();

    // Create TabBar to contain TabBar of TabContent.
    auto tabBarNode = FrameNode::GetOrCreateFrameNode(V2::TAB_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        [swiperController]() { return AceType::MakeRefPtr<TabBarPattern>(swiperController); });
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    tabBarLayoutProperty->UpdateLayoutWeight(1.0);

    tabBarNode->MountToParent(groupNode);
    tabBarNode->MarkModifyDone();

    swiperNode->MountToParent(groupNode);
    swiperNode->MarkModifyDone();

    ViewStackProcessor::GetInstance()->Push(groupNode);
}

RefPtr<GroupNode> TabsView::GetGroupNode(const std::string& tag, int32_t nodeId)
{
    auto groupNode = ElementRegister::GetInstance()->GetSpecificItemById<TabsNode>(nodeId);
    if (!groupNode) {
        return nullptr;
    }
    if (groupNode->GetTag() != tag) {
        LOGE("the tag is changed");
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = groupNode->GetParent();
        if (parent) {
            parent->RemoveChild(groupNode);
        }
        return nullptr;
    }
    return groupNode;
}

void TabsView::SetTabBarPosition(BarPosition tabBarPosition) {}

void TabsView::SetTabBarMode(TabBarMode tabBarMode)
{
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateTabBarMode(tabBarMode);
}

void TabsView::SetTabBarWidth(const Dimension& tabBarWidth)
{
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateTabBarWidth(tabBarWidth);
}

void TabsView::SetTabBarHeight(const Dimension& tabBarHeight)
{
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateTabBarHeight(tabBarHeight);
}

void TabsView::SetAxis(Axis axis)
{
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateAxis(axis);
}

void TabsView::SetIndex(int32_t index)
{
    auto swiperLayoutProperty = GetSwiperLayoutProperty();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateIndex(index);
}

void TabsView::SetScrollable(bool scrollable)
{
    auto swiperPaintProperty = GetSwiperPaintProperty();
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateDisableSwipe(scrollable);
}

void TabsView::SetAnimationDuration(int32_t duration)
{
    auto swiperPaintProperty = GetSwiperPaintProperty();
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateDuration(duration);
}

RefPtr<TabBarLayoutProperty> TabsView::GetTabBarLayoutProperty()
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildren().front());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarLayoutProperty, nullptr);
    return tabBarLayoutProperty;
}

RefPtr<SwiperLayoutProperty> TabsView::GetSwiperLayoutProperty()
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildren().back());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    return swiperLayoutProperty;
}

RefPtr<SwiperPaintProperty> TabsView::GetSwiperPaintProperty()
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildren().back());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, nullptr);
    return swiperPaintProperty;
}

RefPtr<GroupNode> TabsView::CreateGroupNode(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot)
{
    auto groupNode = AceType::MakeRefPtr<TabsNode>(tag, nodeId, pattern, isRoot);
    groupNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(groupNode);
    return groupNode;
}

RefPtr<GroupNode> TabsView::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto groupNode = GetGroupNode(tag, nodeId);
    if (groupNode) {
        return groupNode;
    }
    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    return CreateGroupNode(tag, nodeId, pattern);
}

} // namespace OHOS::Ace::NG
