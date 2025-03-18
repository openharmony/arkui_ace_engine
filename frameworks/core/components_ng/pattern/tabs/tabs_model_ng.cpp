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

#include "core/components_ng/pattern/tabs/tabs_model_ng.h"

#include <type_traits>

#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/animation/animation_pub.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_controller.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint16_t PIXEL_ROUND = static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_START) |
                                static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_TOP) |
                                static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_END) |
                                static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_BOTTOM);
} // namespace

void TabsModelNG::Create(BarPosition barPosition, int32_t index, const RefPtr<TabController>& /*tabController*/,
    const RefPtr<SwiperController>& swiperController)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d][index:%d]", V2::TABS_ETS_TAG, nodeId, index);
    auto tabsNode = GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    InitTabsNode(tabsNode, swiperController);
    ViewStackProcessor::GetInstance()->Push(tabsNode);

    SetTabBarPosition(barPosition);
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);
    if (tabsLayoutProperty->GetIndex().has_value()) {
        auto preIndex = tabsLayoutProperty->GetIndex().value();
        if (preIndex == index || index < 0) {
            return;
        }
    }
    tabsLayoutProperty->UpdateIndexSetByUser(index);
}

RefPtr<SwiperController> TabsModelNG::GetSwiperController(const RefPtr<FrameNode>& swiperNode,
    const RefPtr<SwiperController>& swiperController)
{
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    swiperPaintProperty->UpdateEdgeEffect(EdgeEffect::SPRING);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_RETURN(tabTheme, nullptr);
    swiperPaintProperty->UpdateDuration(tabTheme->GetTabContentAnimationDuration());
    swiperPaintProperty->UpdateCurve(TabBarPhysicalCurve);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    swiperLayoutProperty->UpdateLoop(false);
    swiperLayoutProperty->UpdateCachedCount(0);
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperLayoutProperty->UpdateSafeAreaExpandOpts(
        { .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_TOP + SAFE_AREA_EDGE_BOTTOM });
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, nullptr);
    RefPtr<SwiperController> controller;
    if (swiperController) {
        controller = swiperController;
    } else {
        controller = AceType::MakeRefPtr<TabsControllerNG>();
    }
    swiperPattern->SetSwiperController(controller);
    swiperPattern->SetFinishCallbackType(FinishCallbackType::LOGICALLY);
    swiperPattern->SetHasTabsAncestor(true);
    return controller;
}

void TabsModelNG::InitSelectedMaskNode(const RefPtr<FrameNode>& selectedMaskNode)
{
    auto selectedImageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    selectedImageNode->MountToParent(selectedMaskNode);
    auto selectedMaskRenderContext = selectedMaskNode->GetRenderContext();
    auto selectedMaskProperty = selectedMaskNode->GetLayoutProperty<LinearLayoutProperty>();
    selectedMaskProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    selectedMaskRenderContext->SetClipToBounds(true);
}

void TabsModelNG::InitUnselectedMaskNode(const RefPtr<FrameNode>& unselectedMaskNode)
{
    auto unselectedImageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    unselectedImageNode->MountToParent(unselectedMaskNode);
    auto unselectedMaskRenderContext = unselectedMaskNode->GetRenderContext();
    auto unselectedMaskProperty = unselectedMaskNode->GetLayoutProperty<LinearLayoutProperty>();
    unselectedMaskProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    unselectedMaskRenderContext->SetClipToBounds(true);
}

void TabsModelNG::InitTabsNode(RefPtr<TabsNode> tabsNode, const RefPtr<SwiperController>& swiperController)
{
    bool hasSwiperNode = tabsNode->HasSwiperNode();
    bool hasTabBarNode = tabsNode->HasTabBarNode();
    bool hasDividerNode = tabsNode->HasDividerNode();
    bool hasSelectedMaskNode = tabsNode->HasSelectedMaskNode();
    bool hasUnselectedMaskNode = tabsNode->HasUnselectedMaskNode();
    auto swiperId = tabsNode->GetSwiperId();
    auto tabBarId = tabsNode->GetTabBarId();
    auto dividerId = tabsNode->GetDividerId();
    auto selectedMaskId = tabsNode->GetSelectedMaskId();
    auto unselectedMaskId = tabsNode->GetUnselectedMaskId();

    // Create Swiper node to contain TabContent.
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_ETS_TAG, swiperId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto controller = GetSwiperController(swiperNode, swiperController);
    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, dividerId, []() { return AceType::MakeRefPtr<DividerPattern>(); });

    // Create TabBar to contain TabBar of TabContent.
    auto tabBarNode = FrameNode::GetOrCreateFrameNode(
        V2::TAB_BAR_ETS_TAG, tabBarId, []() { return AceType::MakeRefPtr<TabBarPattern>(); });
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    if (tabBarPattern) {
        tabBarPattern->SetController(controller);
    }

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    if (tabBarLayoutProperty->GetPixelRound() == static_cast<uint16_t>(PixelRoundPolicy::ALL_FORCE_ROUND)) {
        tabBarLayoutProperty->UpdatePixelRound(PIXEL_ROUND);
    }

    auto selectedMaskNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, selectedMaskId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });

    auto unselectedMaskNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, unselectedMaskId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });

    if (!hasSwiperNode) {
        swiperNode->MountToParent(tabsNode);
    }
    if (!hasDividerNode) {
        dividerNode->MountToParent(tabsNode);
    }
    if (!hasTabBarNode) {
        tabBarNode->MountToParent(tabsNode);
    }
    if (!hasSelectedMaskNode) {
        selectedMaskNode->MountToParent(tabBarNode);
        InitSelectedMaskNode(selectedMaskNode);
    }
    if (!hasUnselectedMaskNode) {
        unselectedMaskNode->MountToParent(tabBarNode);
        InitUnselectedMaskNode(unselectedMaskNode);
    }
    InitAccessibilityZIndex(swiperNode, tabBarNode);
}

void TabsModelNG::InitAccessibilityZIndex(RefPtr<FrameNode>& swiperNode, RefPtr<FrameNode>& tabBarNode)
{
    CHECK_NULL_VOID(swiperNode);
    CHECK_NULL_VOID(tabBarNode);
    auto swiperAccessibilityProperty = swiperNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(swiperAccessibilityProperty);
    auto tabBarAccessibilityProperty = tabBarNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(tabBarAccessibilityProperty);
    swiperAccessibilityProperty->SetAccessibilityZIndex(1);
    tabBarAccessibilityProperty->SetAccessibilityZIndex(0);
}

RefPtr<FrameNode> TabsModelNG::CreateFrameNode(int32_t nodeId)
{
    auto tabsNode = GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    InitTabsNode(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    tabBarNode->MarkModifyDone();
    return tabsNode;
}

void TabsModelNG::SetTabBarPosition(BarPosition tabBarPosition)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabsLayoutProperty, TabBarPosition, tabBarPosition);
}

void TabsModelNG::SetBarBackgroundBlurStyle(const BlurStyleOption& styleOption)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetBarBackgroundBlurStyle(frameNode, styleOption);
}

void TabsModelNG::SetTabBarMode(TabBarMode tabBarMode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabsLayoutProperty, TabBarMode, tabBarMode);
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateTabBarMode(tabBarMode);
}

void TabsModelNG::SetTabBarWidth(const Dimension& tabBarWidth)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabsLayoutProperty, BarWidth, tabBarWidth);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto scaleProperty = ScaleProperty::CreateScaleProperty();
    auto tabBarWidthToPx =
        ConvertToPx(tabBarWidth, scaleProperty, tabBarLayoutProperty->GetLayoutConstraint()->percentReference.Width());
    if (LessNotEqual(tabBarWidthToPx.value_or(0.0), 0.0)) {
        tabBarLayoutProperty->ClearUserDefinedIdealSize(true, false);
    } else {
        tabBarLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(tabBarWidth), std::nullopt));
    }
    tabBarLayoutProperty->UpdateTabBarWidth(tabBarWidth);
}

void TabsModelNG::SetTabBarHeight(const Dimension& tabBarHeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabsLayoutProperty, BarHeight, tabBarHeight);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto scaleProperty = ScaleProperty::CreateScaleProperty();
    auto tabBarHeightToPx = ConvertToPx(
        tabBarHeight, scaleProperty, tabBarLayoutProperty->GetLayoutConstraint()->percentReference.Height());
    if (LessNotEqual(tabBarHeightToPx.value_or(0.0), 0.0)) {
        tabBarLayoutProperty->ClearUserDefinedIdealSize(false, true);
    } else {
        tabBarLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, NG::CalcLength(tabBarHeight)));
    }
    tabBarLayoutProperty->UpdateTabBarHeight(tabBarHeight);
}

void TabsModelNG::SetBarModifier(std::function<void(WeakPtr<NG::FrameNode>)>&& onApply)
{
    CHECK_NULL_VOID(onApply);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    onApply(tabBarNode);
}

void TabsModelNG::SetWidthAuto(bool isAuto)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(TabsLayoutProperty, WidthAuto, isAuto);
}

void TabsModelNG::SetWidthAuto(FrameNode* frameNode, bool isAuto)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, WidthAuto, isAuto, frameNode);
}

void TabsModelNG::SetHeightAuto(bool isAuto)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(TabsLayoutProperty, HeightAuto, isAuto);
}

void TabsModelNG::SetHeightAuto(FrameNode* frameNode, bool isAuto)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, HeightAuto, isAuto, frameNode);
}

void TabsModelNG::SetBarAdaptiveHeight(bool barAdaptiveHeight)
{
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateBarAdaptiveHeight(barAdaptiveHeight);
}

void TabsModelNG::SetIsVertical(bool isVertical)
{
    auto axis = isVertical ? Axis::VERTICAL : Axis::HORIZONTAL;
    ACE_UPDATE_LAYOUT_PROPERTY(TabsLayoutProperty, Axis, axis);

    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    if (tabBarLayoutProperty->GetAxis().value_or(Axis::HORIZONTAL) != axis) {
        auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        CHECK_NULL_VOID(tabsNode);
        auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
        CHECK_NULL_VOID(tabBarNode);
        auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
        CHECK_NULL_VOID(tabBarPattern);
        tabBarPattern->UpdateCurrentOffset(0.0f);
    }
    tabBarLayoutProperty->UpdateAxis(axis);
    auto swiperLayoutProperty = GetSwiperLayoutProperty();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateDirection(axis);
}

void TabsModelNG::SetIndex(int32_t index)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateIndex(index);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    if (index < 0) {
        index = 0;
    }
    tabBarPattern->UpdateIndicator(index);
    tabBarPattern->UpdateTextColorAndFontWeight(index);
    swiperLayoutProperty->UpdateIndex(index);
    auto tabsFrameNode = AceType::DynamicCast<FrameNode>(tabsNode);
    CHECK_NULL_VOID(tabsFrameNode);
    auto tabsLayoutProperty = tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>();
    tabsLayoutProperty->UpdateIndex(index);
    swiperNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TabsModelNG::SetScrollable(bool scrollable)
{
    auto props = GetSwiperLayoutProperty();
    CHECK_NULL_VOID(props);
    props->UpdateDisableSwipe(!scrollable);
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetIsDisableSwipe(!scrollable);
}

void TabsModelNG::SetAnimationDuration(float duration)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->SetAnimationDuration(static_cast<int32_t>(duration));
    if (static_cast<int32_t>(duration) < 0) {
        return;
    }
    auto swiperPaintProperty = GetSwiperPaintProperty();
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateDuration(static_cast<int32_t>(duration));
}

void TabsModelNG::SetFadingEdge(bool fadingEdge)
{
    auto tabBarPaintProperty = GetTabBarPaintProperty();
    CHECK_NULL_VOID(tabBarPaintProperty);
    tabBarPaintProperty->UpdateFadingEdge(fadingEdge);
}

void TabsModelNG::SetBarOverlap(bool barOverlap)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabsLayoutProperty, BarOverlap, barOverlap);

    BlurStyleOption option;
    if (barOverlap) {
        option.blurStyle = BlurStyle::COMPONENT_THICK;
    }
    SetBarBackgroundBlurStyle(option);
}

void TabsModelNG::SetOnChange(std::function<void(const BaseEventInfo*)>&& onChange)
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetOnChangeEvent(std::move(onChange));
}

void TabsModelNG::SetOnTabBarClick(std::function<void(const BaseEventInfo*)>&& onTabBarClick)
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetOnTabBarClickEvent(std::move(onTabBarClick));
}

void TabsModelNG::SetOnUnselected(std::function<void(const BaseEventInfo* info)>&& onUnselected)
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetOnUnselectedEvent(std::move(onUnselected));
}

void TabsModelNG::SetOnAnimationStart(AnimationStartEvent&& onAnimationStart)
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetAnimationStartEvent(std::move(onAnimationStart));
}

void TabsModelNG::SetOnAnimationEnd(AnimationEndEvent&& onAnimationEnd)
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetAnimationEndEvent(std::move(onAnimationEnd));
}

void TabsModelNG::SetOnGestureSwipe(GestureSwipeEvent&& onGestureSwipe)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetGestureSwipeEvent(std::move(onGestureSwipe));
}

void TabsModelNG::SetOnSelected(std::function<void(const BaseEventInfo* info)>&& onSelected)
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetOnSelectedEvent(std::move(onSelected));
}

void TabsModelNG::SetOnSelected(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& onSelected)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnSelectedEvent(std::move(onSelected));
}

void TabsModelNG::SetDivider(const TabsItemDivider& divider)
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(1));
    CHECK_NULL_VOID(dividerNode);
    auto dividerRenderContext = dividerNode->GetRenderContext();
    CHECK_NULL_VOID(dividerRenderContext);
    if (divider.isNull) {
        dividerRenderContext->UpdateOpacity(0.0f);
        auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
        CHECK_NULL_VOID(tabsLayoutProperty);
        auto currentDivider = tabsLayoutProperty->GetDivider().value_or(TabsItemDivider());
        currentDivider.strokeWidth = Dimension(1.0f);
        currentDivider.isNull = true;
        ACE_UPDATE_LAYOUT_PROPERTY(TabsLayoutProperty, Divider, currentDivider);
    } else {
        dividerRenderContext->UpdateOpacity(1.0f);
        ACE_UPDATE_LAYOUT_PROPERTY(TabsLayoutProperty, Divider, divider);
    }
}

void TabsModelNG::SetBarBackgroundColor(const Color& backgroundColor)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_VOID(tabBarRenderContext);
    tabBarRenderContext->UpdateBackgroundColor(backgroundColor);
}

RefPtr<TabBarLayoutProperty> TabsModelNG::GetTabBarLayoutProperty()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarLayoutProperty, nullptr);
    return tabBarLayoutProperty;
}

RefPtr<TabBarPaintProperty> TabsModelNG::GetTabBarPaintProperty()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    CHECK_NULL_RETURN(tabBarPaintProperty, nullptr);
    return tabBarPaintProperty;
}

RefPtr<SwiperLayoutProperty> TabsModelNG::GetSwiperLayoutProperty()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    return swiperLayoutProperty;
}

RefPtr<SwiperPaintProperty> TabsModelNG::GetSwiperPaintProperty()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, nullptr);
    return swiperPaintProperty;
}

void TabsModelNG::Pop()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    tabBarNode->MarkModifyDone();
    tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
    CHECK_NULL_VOID(dividerNode);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto axis = layoutProperty->GetAxis().value_or((Axis::HORIZONTAL));
    TabsItemDivider defaultDivider;
    auto divider = layoutProperty->GetDivider().value_or(defaultDivider);
    auto dividerColor = divider.color;
    auto dividerStrokeWidth = divider.strokeWidth;

    auto dividerHub = dividerNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(dividerHub);

    auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(dividerColor);
    dividerRenderProperty->UpdateLineCap(LineCap::BUTT);

    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateVertical(axis == Axis::VERTICAL);
    dividerLayoutProperty->UpdateStrokeWidth(dividerStrokeWidth);
    dividerLayoutProperty->UpdateStrokeWidthLimitation(false);
    CHECK_NULL_VOID(dividerNode);
    dividerNode->MarkModifyDone();

    swiperNode->MarkModifyDone();
    swiperNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    ViewStackProcessor::GetInstance()->PopContainer();
}

RefPtr<TabsNode> TabsModelNG::GetOrCreateTabsNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto tabsNode = ElementRegister::GetInstance()->GetSpecificItemById<TabsNode>(nodeId);
    if (tabsNode) {
        if (tabsNode->GetTag() == tag) {
            return tabsNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = tabsNode->GetParent();
        if (parent) {
            parent->RemoveChild(tabsNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    tabsNode = AceType::MakeRefPtr<TabsNode>(tag, nodeId, pattern, false);
    tabsNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(tabsNode);
    return tabsNode;
}

void TabsModelNG::SetOnChangeEvent(std::function<void(const BaseEventInfo*)>&& onChangeEvent)
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetOnIndexChangeEvent(std::move(onChangeEvent));
}

void TabsModelNG::SetClipEdge(bool clipEdge)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    ViewAbstract::SetClipEdge(clipEdge);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperRenderContext = swiperNode->GetRenderContext();
    CHECK_NULL_VOID(swiperRenderContext);
    swiperRenderContext->UpdateClipEdge(clipEdge);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
    CHECK_NULL_VOID(dividerNode);
    auto dividerRenderContext = dividerNode->GetRenderContext();
    CHECK_NULL_VOID(dividerRenderContext);
    dividerRenderContext->UpdateClipEdge(clipEdge);
}

void TabsModelNG::SetScrollableBarModeOptions(const ScrollableBarModeOptions& option)
{
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateScrollableBarModeOptions(option);
}

void TabsModelNG::ResetScrollableBarModeOptions()
{
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->ResetScrollableBarModeOptions();
}

void TabsModelNG::SetBarGridAlign(const BarGridColumnOptions& BarGridColumnOptions)
{
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateBarGridAlign(BarGridColumnOptions);
}

RefPtr<TabBarLayoutProperty> TabsModelNG::GetTabBarLayoutProperty(FrameNode* frameNode)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarLayoutProperty, nullptr);
    return tabBarLayoutProperty;
}

RefPtr<TabBarPaintProperty> TabsModelNG::GetTabBarPaintProperty(FrameNode* frameNode)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    CHECK_NULL_RETURN(tabBarPaintProperty, nullptr);
    return tabBarPaintProperty;
}

RefPtr<SwiperLayoutProperty> TabsModelNG::GetSwiperLayoutProperty(FrameNode* frameNode)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    return swiperLayoutProperty;
}

RefPtr<SwiperPaintProperty> TabsModelNG::GetSwiperPaintProperty(FrameNode* frameNode)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, nullptr);
    return swiperPaintProperty;
}

void TabsModelNG::SetTabBarMode(FrameNode* frameNode, TabBarMode tabBarMode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, TabBarMode, tabBarMode, frameNode);
    auto tabBarLayoutProperty = GetTabBarLayoutProperty(frameNode);
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateTabBarMode(tabBarMode);
}

void TabsModelNG::SetBarGridAlign(FrameNode* frameNode, const BarGridColumnOptions& BarGridColumnOptions)
{
    CHECK_NULL_VOID(frameNode);
    auto tabBarLayoutProperty = GetTabBarLayoutProperty(frameNode);
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateBarGridAlign(BarGridColumnOptions);
}

void TabsModelNG::SetOnUnselected(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& onUnselected)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnUnselectedEvent(std::move(onUnselected));
}

void TabsModelNG::SetDivider(FrameNode* frameNode, const TabsItemDivider& divider)
{
    CHECK_NULL_VOID(frameNode);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(1));
    CHECK_NULL_VOID(dividerNode);
    auto dividerRenderContext = dividerNode->GetRenderContext();
    CHECK_NULL_VOID(dividerRenderContext);
    if (divider.isNull) {
        dividerRenderContext->UpdateOpacity(0.0f);
        auto tabsLayoutProperty = frameNode->GetLayoutProperty<TabsLayoutProperty>();
        CHECK_NULL_VOID(tabsLayoutProperty);
        auto currentDivider = tabsLayoutProperty->GetDivider().value_or(TabsItemDivider());
        currentDivider.strokeWidth = Dimension(1.0f);
        currentDivider.isNull = true;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, Divider, currentDivider, frameNode);
    } else {
        dividerRenderContext->UpdateOpacity(1.0f);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, Divider, divider, frameNode);
    }
}

void TabsModelNG::SetFadingEdge(FrameNode* frameNode, bool fadingEdge)
{
    CHECK_NULL_VOID(frameNode);
    auto tabBarPaintProperty = GetTabBarPaintProperty(frameNode);
    CHECK_NULL_VOID(tabBarPaintProperty);
    tabBarPaintProperty->UpdateFadingEdge(fadingEdge);
}

void TabsModelNG::SetBarBackgroundColor(FrameNode* frameNode, const Color& backgroundColor)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_VOID(tabBarRenderContext);
    tabBarRenderContext->UpdateBackgroundColor(backgroundColor);
}

void TabsModelNG::SetBarBackgroundBlurStyle(FrameNode* frameNode, const BlurStyleOption& styleOption)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto pipeline = tabBarNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (styleOption.policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
        pipeline->AddWindowFocusChangedCallback(tabBarNode->GetId());
    } else {
        pipeline->RemoveWindowFocusChangedCallback(tabBarNode->GetId());
    }
    auto target = tabBarNode->GetRenderContext();
    if (target) {
        if (target->GetBackgroundEffect().has_value()) {
            target->UpdateBackgroundEffect(std::nullopt);
        }
        target->UpdateBackBlurStyle(styleOption);
        if (target->GetBackBlurRadius().has_value()) {
            target->UpdateBackBlurRadius(Dimension());
        }
    }
}

void TabsModelNG::SetBarOverlap(FrameNode* frameNode, bool barOverlap)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, BarOverlap, barOverlap, frameNode);

    BlurStyleOption option;
    if (barOverlap) {
        option.blurStyle = BlurStyle::COMPONENT_THICK;
    }
    SetBarBackgroundBlurStyle(frameNode, option);
}

void TabsModelNG::SetIsVertical(FrameNode* frameNode, bool isVertical)
{
    auto axis = isVertical ? Axis::VERTICAL : Axis::HORIZONTAL;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, Axis, axis, frameNode);

    auto tabBarLayoutProperty = GetTabBarLayoutProperty(frameNode);
    CHECK_NULL_VOID(tabBarLayoutProperty);
    if (tabBarLayoutProperty->GetAxis().value_or(Axis::HORIZONTAL) != axis) {
        auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
        CHECK_NULL_VOID(tabsNode);
        auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
        CHECK_NULL_VOID(tabBarNode);
        auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
        CHECK_NULL_VOID(tabBarPattern);
        tabBarPattern->UpdateCurrentOffset(0.0f);
    }
    tabBarLayoutProperty->UpdateAxis(axis);
    auto swiperLayoutProperty = GetSwiperLayoutProperty(frameNode);
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateDirection(axis);
}

void TabsModelNG::SetTabBarPosition(FrameNode* frameNode, BarPosition tabBarPosition)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, TabBarPosition, tabBarPosition, frameNode);
}

void TabsModelNG::SetScrollable(FrameNode* frameNode, bool scrollable)
{
    CHECK_NULL_VOID(frameNode);
    auto props = GetSwiperLayoutProperty(frameNode);
    CHECK_NULL_VOID(props);
    props->UpdateDisableSwipe(!scrollable);
    auto tabPattern = frameNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetIsDisableSwipe(!scrollable);
}

void TabsModelNG::SetTabBarWidth(FrameNode* frameNode, const Dimension& tabBarWidth)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, BarWidth, tabBarWidth, frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto scaleProperty = ScaleProperty::CreateScaleProperty();
    auto tabBarWidthToPx =
        ConvertToPx(tabBarWidth, scaleProperty, tabBarLayoutProperty->GetLayoutConstraint()->percentReference.Width());
    if (LessNotEqual(tabBarWidthToPx.value_or(0.0), 0.0)) {
        tabBarLayoutProperty->ClearUserDefinedIdealSize(true, false);
    } else {
        tabBarLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(tabBarWidth), std::nullopt));
    }
    tabBarLayoutProperty->UpdateTabBarWidth(tabBarWidth);
}

void TabsModelNG::SetTabBarHeight(FrameNode* frameNode, const Dimension& tabBarHeight)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, BarHeight, tabBarHeight, frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto scaleProperty = ScaleProperty::CreateScaleProperty();
    auto tabBarHeightToPx = ConvertToPx(
        tabBarHeight, scaleProperty, tabBarLayoutProperty->GetLayoutConstraint()->percentReference.Height());
    if (LessNotEqual(tabBarHeightToPx.value_or(0.0), 0.0)) {
        tabBarLayoutProperty->ClearUserDefinedIdealSize(false, true);
    } else {
        tabBarLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, NG::CalcLength(tabBarHeight)));
    }
    tabBarLayoutProperty->UpdateTabBarHeight(tabBarHeight);
}

void TabsModelNG::SetAnimationDuration(FrameNode* frameNode, float duration)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->SetAnimationDuration(static_cast<int32_t>(duration));
    if (static_cast<int32_t>(duration) < 0) {
        return;
    }
    auto swiperPaintProperty = GetSwiperPaintProperty(frameNode);
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateDuration(static_cast<int32_t>(duration));
}

void TabsModelNG::SetScrollableBarModeOptions(FrameNode* frameNode, const ScrollableBarModeOptions& option)
{
    CHECK_NULL_VOID(frameNode);
    auto tabBarLayoutProperty = GetTabBarLayoutProperty(frameNode);
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateScrollableBarModeOptions(option);
}

void TabsModelNG::SetBarAdaptiveHeight(FrameNode* frameNode, bool barAdaptiveHeight)
{
    CHECK_NULL_VOID(frameNode);
    auto tabBarLayoutProperty = GetTabBarLayoutProperty(frameNode);
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateBarAdaptiveHeight(barAdaptiveHeight);
}

void TabsModelNG::SetIsCustomAnimation(bool isCustom)
{
    auto swiperLayoutProperty = GetSwiperLayoutProperty();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateIsCustomAnimation(isCustom);
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetIsCustomAnimation(isCustom);
}

void TabsModelNG::SetOnCustomAnimation(TabsCustomAnimationEvent&& onCustomAnimation)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->SetTabsCustomContentTransition(std::move(onCustomAnimation));
}

void TabsModelNG::SetClipEdge(FrameNode* frameNode, bool clipEdge)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    ViewAbstract::SetClipEdge(tabsNode, clipEdge);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperRenderContext = swiperNode->GetRenderContext();
    CHECK_NULL_VOID(swiperRenderContext);
    swiperRenderContext->UpdateClipEdge(clipEdge);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
    CHECK_NULL_VOID(dividerNode);
    auto dividerRenderContext = dividerNode->GetRenderContext();
    CHECK_NULL_VOID(dividerRenderContext);
    dividerRenderContext->UpdateClipEdge(clipEdge);
}

void TabsModelNG::SetOnContentWillChange(std::function<bool(int32_t, int32_t)>&& callback)
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetInterceptStatus(true);
    tabPattern->SetOnContentWillChange(std::move(callback));
}

void TabsModelNG::SetAnimateMode(TabAnimateMode mode)
{
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetAnimateMode(mode);
}

void TabsModelNG::SetAnimateMode(FrameNode* frameNode, TabAnimateMode mode)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetAnimateMode(mode);
}

void TabsModelNG::SetEdgeEffect(EdgeEffect edgeEffect)
{
    auto swiperPaintProperty = GetSwiperPaintProperty();
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateEdgeEffect(edgeEffect);
}

void TabsModelNG::SetEdgeEffect(FrameNode* frameNode, int32_t edgeEffect)
{
    auto swiperPaintProperty = GetSwiperPaintProperty(frameNode);
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateEdgeEffect(static_cast<EdgeEffect>(edgeEffect));
}

void TabsModelNG::SetTabBarIndex(FrameNode* frameNode, int32_t index)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);
    if (tabsLayoutProperty->GetIndex().has_value()) {
        auto preIndex = tabsLayoutProperty->GetIndex().value();
        if (preIndex == index || index < 0) {
            return;
        }
    }
    tabsLayoutProperty->UpdateIndexSetByUser(index);
}

void TabsModelNG::SetTabsController(FrameNode* frameNode, const RefPtr<SwiperController>& tabsController)
{
    CHECK_NULL_VOID(frameNode);
    auto nodeId = frameNode->GetId();
    auto tabsNode = GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    CHECK_NULL_VOID(tabsNode);
    InitTabsNode(tabsNode, tabsController);
}

void TabsModelNG::SetBarBackgroundEffect(const EffectOption& effectOption)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetBarBackgroundEffect(frameNode, effectOption);
}

void TabsModelNG::SetBarBackgroundEffect(FrameNode* frameNode, const EffectOption& effectOption)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto pipeline = tabBarNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (effectOption.policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
        pipeline->AddWindowFocusChangedCallback(tabBarNode->GetId());
    } else {
        pipeline->RemoveWindowFocusChangedCallback(tabBarNode->GetId());
    }
    auto target = tabBarNode->GetRenderContext();
    if (target) {
        if (target->GetBackBlurRadius().has_value()) {
            target->UpdateBackBlurRadius(Dimension());
        }
        if (target->GetBackBlurStyle().has_value()) {
            target->UpdateBackBlurStyle(std::nullopt);
        }
        target->UpdateBackgroundEffect(effectOption);
    }
}

void TabsModelNG::SetPageFlipMode(int32_t pageFlipMode)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->SetPageFlipMode(pageFlipMode);
}

void TabsModelNG::SetPageFlipMode(FrameNode* frameNode, int32_t options)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->SetPageFlipMode(options);
}

void TabsModelNG::SetCachedMaxCount(std::optional<int32_t> cachedMaxCount, TabsCacheMode cacheMode)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetCachedMaxCount(frameNode, cachedMaxCount, cacheMode);
}

void TabsModelNG::SetCachedMaxCount(
    FrameNode* frameNode, std::optional<int32_t> cachedMaxCount, TabsCacheMode cacheMode)
{
    CHECK_NULL_VOID(frameNode);
    if (cachedMaxCount.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, CachedMaxCount, cachedMaxCount.value(), frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, CacheMode, cacheMode, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, CachedMaxCount, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, CacheMode, frameNode);
    }
}
} // namespace OHOS::Ace::NG
