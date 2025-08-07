/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tabs_model_static.h"

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

RefPtr<FrameNode> TabsModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto tabsNode = GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    InitTabsNode(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    tabBarNode->MarkModifyDone();
    return tabsNode;
}

RefPtr<TabsNode> TabsModelStatic::GetOrCreateTabsNode(
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

void TabsModelStatic::InitTabsNode(RefPtr<TabsNode> tabsNode, const RefPtr<SwiperController>& swiperController)
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

RefPtr<SwiperController> TabsModelStatic::GetSwiperController(const RefPtr<FrameNode>& swiperNode,
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

void TabsModelStatic::InitSelectedMaskNode(const RefPtr<FrameNode>& selectedMaskNode)
{
    auto selectedImageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    selectedImageNode->MountToParent(selectedMaskNode);
    auto selectedMaskRenderContext = selectedMaskNode->GetRenderContext();
    auto selectedMaskProperty = selectedMaskNode->GetLayoutProperty<LinearLayoutProperty>();
    selectedMaskProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    selectedMaskRenderContext->SetClipToBounds(true);
}

void TabsModelStatic::InitUnselectedMaskNode(const RefPtr<FrameNode>& unselectedMaskNode)
{
    auto unselectedImageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    unselectedImageNode->MountToParent(unselectedMaskNode);
    auto unselectedMaskRenderContext = unselectedMaskNode->GetRenderContext();
    auto unselectedMaskProperty = unselectedMaskNode->GetLayoutProperty<LinearLayoutProperty>();
    unselectedMaskProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    unselectedMaskRenderContext->SetClipToBounds(true);
}

void TabsModelStatic::InitAccessibilityZIndex(RefPtr<FrameNode>& swiperNode, RefPtr<FrameNode>& tabBarNode)
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

void TabsModelStatic::SetTabBarPosition(FrameNode* frameNode, const std::optional<BarPosition>& tabBarPositionOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsLayoutProperty = frameNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);
    auto oldTabBarPosition = tabsLayoutProperty->GetTabBarPosition();
    if (tabBarPositionOpt) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, TabBarPosition, tabBarPositionOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, TabBarPosition, frameNode);
    }
    auto tabBarPosition = tabBarPositionOpt.value_or(BarPosition::START);
    if ((!oldTabBarPosition.has_value() && tabBarPosition == BarPosition::END) ||
        (oldTabBarPosition.has_value() && oldTabBarPosition.value() == tabBarPosition)) {
        return;
    }

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabsFocusNode = tabsNode->GetFocusHub();
    CHECK_NULL_VOID(tabsFocusNode);
    if (!tabsFocusNode->IsCurrentFocus()) {
        tabBarPosition = tabsLayoutProperty->GetTabBarPosition().value_or(BarPosition::START);
        if (tabBarPosition == BarPosition::START) {
            auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
            CHECK_NULL_VOID(tabBarNode);
            auto tabBarFocusNode = tabBarNode->GetFocusHub();
            CHECK_NULL_VOID(tabBarFocusNode);
            tabsFocusNode->SetLastWeakFocusNode(AceType::WeakClaim(AceType::RawPtr(tabBarFocusNode)));
        } else {
            auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
            CHECK_NULL_VOID(swiperNode);
            auto swiperFocusNode = swiperNode->GetFocusHub();
            CHECK_NULL_VOID(swiperFocusNode);
            tabsFocusNode->SetLastWeakFocusNode(AceType::WeakClaim(AceType::RawPtr(swiperFocusNode)));
        }
    }
}

void TabsModelStatic::InitIndex(FrameNode* frameNode, const std::optional<int32_t>& indexOpt)
{
    auto index = (indexOpt && (*indexOpt >= 0)) ? *indexOpt : 0;

    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);

    // Create part
    CHECK_NULL_VOID(tabsNode);
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);
    auto hasTabBarNode = tabsNode->HasTabBarNode();
    if (!hasTabBarNode) {
        tabsLayoutProperty->UpdateIndex(index);
        return;
    }
    auto preIndex = tabsLayoutProperty->GetIndexValue(0);
    CHECK_NULL_VOID(preIndex != index);

    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    if (tabsPattern && tabsPattern->GetInterceptStatus()) {
        auto ret = tabsPattern->OnContentWillChange(preIndex, index);
        CHECK_NULL_VOID(ret && !(*ret));
    }

    // SetIndex part
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabsLayoutProperty->UpdateIndex(index);
    swiperLayoutProperty->UpdateIndex(index);
    tabBarLayoutProperty->UpdateIndicator(index);
    tabBarPattern->UpdateTextColorAndFontWeight(index);
    swiperNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    // end of SetIndex part

    // continue of the Create part
    tabBarPattern->SetMaskAnimationByCreate(true);
    tabBarPattern->UpdateImageColor(index);
    tabBarPattern->UpdateSymbolStats(index, -1);
    tabBarPattern->UpdateSymbolStats(-1, preIndex);
}

RefPtr<TabsControllerNG> TabsModelStatic::GetSwiperController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, nullptr);
    auto swiperController = swiperPattern->GetSwiperController();
    return AceType::DynamicCast<TabsControllerNG>(swiperController);
}

RefPtr<TabBarLayoutProperty> TabsModelStatic::GetTabBarLayoutProperty(FrameNode* frameNode)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarLayoutProperty, nullptr);
    return tabBarLayoutProperty;
}

RefPtr<SwiperLayoutProperty> TabsModelStatic::GetSwiperLayoutProperty(FrameNode* frameNode)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    return swiperLayoutProperty;
}

void TabsModelStatic::SetIsVertical(FrameNode* frameNode, bool isVertical)
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

void TabsModelStatic::SetScrollable(FrameNode* frameNode, bool scrollable)
{
    CHECK_NULL_VOID(frameNode);
    auto props = GetSwiperLayoutProperty(frameNode);
    CHECK_NULL_VOID(props);
    props->UpdateDisableSwipe(!scrollable);
    auto tabPattern = frameNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetIsDisableSwipe(!scrollable);
}

void TabsModelStatic::SetScrollableBarModeOptions(FrameNode* frameNode, const ScrollableBarModeOptions& option)
{
    CHECK_NULL_VOID(frameNode);
    auto tabBarLayoutProperty = GetTabBarLayoutProperty(frameNode);
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateScrollableBarModeOptions(option);
}

void TabsModelStatic::SetTabBarMode(FrameNode* frameNode, const std::optional<TabBarMode>& tabBarModeOpt)
{
    if (tabBarModeOpt) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, TabBarMode, tabBarModeOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, TabBarMode, frameNode);
    }
    auto tabBarLayoutProperty = GetTabBarLayoutProperty(frameNode);
    CHECK_NULL_VOID(tabBarLayoutProperty);
    if (tabBarModeOpt) {
        tabBarLayoutProperty->UpdateTabBarMode(tabBarModeOpt.value());
    } else {
        tabBarLayoutProperty->ResetTabBarMode();
    }
}

void TabsModelStatic::SetTabBarWidth(FrameNode* frameNode, const std::optional<Dimension>& tabBarWidthOpt)
{
    if (tabBarWidthOpt) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, BarWidth, tabBarWidthOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, BarWidth, frameNode);
    }
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto scaleProperty = ScaleProperty::CreateScaleProperty();
    auto tabBarWidth = tabBarWidthOpt.value_or(Dimension(-1.0, DimensionUnit::VP));
    auto tabBarWidthToPx =
        ConvertToPx(tabBarWidth, scaleProperty, tabBarLayoutProperty->GetLayoutConstraint()->percentReference.Width());
    if (LessNotEqual(tabBarWidthToPx.value_or(0.0), 0.0)) {
        tabBarLayoutProperty->ClearUserDefinedIdealSize(true, false);
    } else {
        tabBarLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(tabBarWidth), std::nullopt));
    }
    if (tabBarWidthOpt) {
        tabBarLayoutProperty->UpdateTabBarWidth(tabBarWidthOpt.value());
    } else {
        tabBarLayoutProperty->ResetTabBarWidth();
    }
}

void TabsModelStatic::SetTabBarHeight(FrameNode* frameNode, const std::optional<Dimension>& tabBarHeightOpt)
{
    if (tabBarHeightOpt) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, BarHeight, tabBarHeightOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, BarHeight, frameNode);
    }
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto scaleProperty = ScaleProperty::CreateScaleProperty();
    auto tabBarHeight = tabBarHeightOpt.value_or(Dimension(-1.0, DimensionUnit::VP));
    auto tabBarHeightToPx = ConvertToPx(
        tabBarHeight, scaleProperty, tabBarLayoutProperty->GetLayoutConstraint()->percentReference.Height());
    if (LessNotEqual(tabBarHeightToPx.value_or(0.0), 0.0)) {
        tabBarLayoutProperty->ClearUserDefinedIdealSize(false, true);
    } else {
        tabBarLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, NG::CalcLength(tabBarHeight)));
    }
    if (tabBarHeightOpt) {
        tabBarLayoutProperty->UpdateTabBarHeight(tabBarHeightOpt.value());
    } else {
        tabBarLayoutProperty->ResetTabBarHeight();
    }
}

RefPtr<SwiperPaintProperty> TabsModelStatic::GetSwiperPaintProperty(FrameNode* frameNode)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, nullptr);
    return swiperPaintProperty;
}

void TabsModelStatic::SetAnimationDuration(FrameNode* frameNode, float duration)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->SetAnimationDuration(static_cast<int32_t>(duration));
    auto swiperPaintProperty = GetSwiperPaintProperty(frameNode);
    CHECK_NULL_VOID(swiperPaintProperty);
    if (static_cast<int32_t>(duration) < 0) {
        swiperPaintProperty->ResetDuration();
    } else {
        swiperPaintProperty->UpdateDuration(static_cast<int32_t>(duration));
    }
}

void TabsModelStatic::SetAnimateMode(FrameNode* frameNode, const std::optional<TabAnimateMode>& modeOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    auto mode = modeOpt.value_or(TabAnimateMode::CONTENT_FIRST);
    tabPattern->SetAnimateMode(mode);
}

void TabsModelStatic::SetEdgeEffect(FrameNode* frameNode, const std::optional<int32_t>& edgeEffect)
{
    auto swiperPaintProperty = GetSwiperPaintProperty(frameNode);
    CHECK_NULL_VOID(swiperPaintProperty);
    if (edgeEffect) {
        swiperPaintProperty->UpdateEdgeEffect(static_cast<EdgeEffect>(edgeEffect.value()));
    } else {
        swiperPaintProperty->ResetEdgeEffect();
    }
}

void TabsModelStatic::SetOnChange(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetOnChangeEvent(std::move(onChange));
}

void TabsModelStatic::SetOnSelected(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& onSelected)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnSelectedEvent(std::move(onSelected));
}

void TabsModelStatic::SetOnTabBarClick(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& onTabBarClick)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetOnTabBarClickEvent(std::move(onTabBarClick));
}

void TabsModelStatic::SetOnUnselected(FrameNode* frameNode,
    std::function<void(const BaseEventInfo* info)>&& onUnselected)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnUnselectedEvent(std::move(onUnselected));
}

void TabsModelStatic::SetOnAnimationStart(FrameNode* frameNode, AnimationStartEvent&& onAnimationStart)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetAnimationStartEvent(std::move(onAnimationStart));
}

void TabsModelStatic::SetOnAnimationEnd(FrameNode* frameNode, AnimationEndEvent&& onAnimationEnd)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetAnimationEndEvent(std::move(onAnimationEnd));
}

void TabsModelStatic::SetOnGestureSwipe(FrameNode* frameNode, GestureSwipeEvent&& onGestureSwipe)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetGestureSwipeEvent(std::move(onGestureSwipe));
}

RefPtr<TabBarPaintProperty> TabsModelStatic::GetTabBarPaintProperty(FrameNode* frameNode)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    CHECK_NULL_RETURN(tabBarPaintProperty, nullptr);
    return tabBarPaintProperty;
}

void TabsModelStatic::SetFadingEdge(FrameNode* frameNode, bool fadingEdge)
{
    CHECK_NULL_VOID(frameNode);
    auto tabBarPaintProperty = GetTabBarPaintProperty(frameNode);
    CHECK_NULL_VOID(tabBarPaintProperty);
    tabBarPaintProperty->UpdateFadingEdge(fadingEdge);
}

void TabsModelStatic::SetDivider(FrameNode* frameNode, const std::optional<TabsItemDivider>& dividerOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(1));
    CHECK_NULL_VOID(dividerNode);
    auto dividerRenderContext = dividerNode->GetRenderContext();
    CHECK_NULL_VOID(dividerRenderContext);

    if (!dividerOpt.has_value()) {
        dividerRenderContext->UpdateOpacity(0.0f);
        ACE_RESET_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, Divider, frameNode);
    } else {
        if (dividerOpt.value().isNull) {
            dividerRenderContext->UpdateOpacity(0.0f);
            auto tabsLayoutProperty = frameNode->GetLayoutProperty<TabsLayoutProperty>();
            CHECK_NULL_VOID(tabsLayoutProperty);
            auto currentDivider = tabsLayoutProperty->GetDivider().value_or(TabsItemDivider());
            currentDivider.strokeWidth = Dimension(1.0f);
            currentDivider.isNull = true;
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, Divider, currentDivider, frameNode);
        } else {
            dividerRenderContext->UpdateOpacity(1.0f);
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, Divider, dividerOpt.value(), frameNode);
        }
    }
}

void TabsModelStatic::InitDivider(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
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
}

void TabsModelStatic::SetBarOverlap(FrameNode* frameNode, bool barOverlap)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, BarOverlap, barOverlap, frameNode);

    BlurStyleOption option;
    if (barOverlap) {
        option.blurStyle = BlurStyle::COMPONENT_THICK;
    }
    SetBarBackgroundBlurStyle(frameNode, option);
}

void TabsModelStatic::SetBarBackgroundBlurStyle(FrameNode* frameNode, const BlurStyleOption& styleOption)
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

void TabsModelStatic::SetBarBackgroundColor(FrameNode* frameNode, const std::optional<Color>& backgroundColorOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_VOID(tabBarRenderContext);
    if (backgroundColorOpt) {
        tabBarRenderContext->UpdateBackgroundColor(backgroundColorOpt.value());
    } else {
        tabBarRenderContext->ResetBackgroundColor();
    }
}

void TabsModelStatic::SetBarGridAlign(FrameNode* frameNode, const BarGridColumnOptions& BarGridColumnOptions)
{
    CHECK_NULL_VOID(frameNode);
    auto tabBarLayoutProperty = GetTabBarLayoutProperty(frameNode);
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateBarGridAlign(BarGridColumnOptions);
}

void TabsModelStatic::SetIsCustomAnimation(FrameNode* frameNode, bool isCustom)
{
    CHECK_NULL_VOID(frameNode);
    auto swiperLayoutProperty = GetSwiperLayoutProperty(frameNode);
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateIsCustomAnimation(isCustom);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetIsCustomAnimation(isCustom);
}

void TabsModelStatic::SetOnCustomAnimation(FrameNode* frameNode, TabsCustomAnimationEvent&& onCustomAnimation)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->SetTabsCustomContentTransition(std::move(onCustomAnimation));
}

void TabsModelStatic::SetBarBackgroundEffect(FrameNode* frameNode, const EffectOption& effectOption)
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

void TabsModelStatic::SetPageFlipMode(FrameNode* frameNode, int32_t options)
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

void TabsModelStatic::SetOnContentWillChange(FrameNode* frameNode, std::function<bool(int32_t, int32_t)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetInterceptStatus(true);
    tabPattern->SetOnContentWillChange(std::move(callback));
}

void TabsModelStatic::SetCachedMaxCount(
    FrameNode* frameNode, std::optional<int32_t> cachedMaxCount, std::optional<TabsCacheMode> cacheMode)
{
    CHECK_NULL_VOID(frameNode);
    if (cachedMaxCount.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, CachedMaxCount, cachedMaxCount.value(), frameNode);
        if (cacheMode.has_value()) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, CacheMode, cacheMode.value(), frameNode);
        } else {
            ACE_RESET_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, CacheMode, frameNode);
        }
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, CachedMaxCount, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(TabsLayoutProperty, CacheMode, frameNode);
    }
}

void TabsModelStatic::SetOnChangeEvent(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& onChangeEvent)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode);
    CHECK_NULL_VOID(tabsNode);
    auto tabPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    tabPattern->SetOnIndexChangeEvent(std::move(onChangeEvent));
}
} // namespace OHOS::Ace::NG
