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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
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
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension BAR_BLUR_RADIUS = 200.0_vp;
constexpr Dimension BAR_SATURATE = 1.3_vp;
} // namespace

void TabsModelNG::Create(BarPosition barPosition, int32_t index, const RefPtr<TabController>& /*tabController*/,
    const RefPtr<SwiperController>& swiperController)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto tabsNode = GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });

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
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    swiperPaintProperty->UpdateEdgeEffect(EdgeEffect::SPRING);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    swiperPaintProperty->UpdateDuration(tabTheme->GetTabContentAnimationDuration());
    swiperPaintProperty->UpdateCurve(TabBarPhysicalCurve);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    swiperLayoutProperty->UpdateLoop(false);
    swiperLayoutProperty->UpdateCachedCount(0);
    swiperLayoutProperty->UpdateShowIndicator(false);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto controller = swiperController ? swiperController : swiperPattern->GetSwiperController();
    if (!controller) {
        controller = AceType::MakeRefPtr<SwiperController>();
    }
    swiperPattern->SetSwiperController(controller);

    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, dividerId, []() { return AceType::MakeRefPtr<DividerPattern>(); });

    // Create TabBar to contain TabBar of TabContent.
    auto tabBarNode = FrameNode::GetOrCreateFrameNode(
        V2::TAB_BAR_ETS_TAG, tabBarId, [controller]() { return AceType::MakeRefPtr<TabBarPattern>(controller); });

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
        auto selectedImageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
        selectedImageNode->MountToParent(selectedMaskNode);
        auto selectedMaskRenderContext = selectedMaskNode->GetRenderContext();
        auto selectedMaskProperty = selectedMaskNode->GetLayoutProperty<LinearLayoutProperty>();
        selectedMaskProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
        selectedMaskRenderContext->SetClipToBounds(true);
    }
    if (!hasUnselectedMaskNode) {
        unselectedMaskNode->MountToParent(tabBarNode);
        auto unselectedImageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
        unselectedImageNode->MountToParent(unselectedMaskNode);
        auto unselectedMaskRenderContext = unselectedMaskNode->GetRenderContext();
        auto unselectedMaskProperty = unselectedMaskNode->GetLayoutProperty<LinearLayoutProperty>();
        unselectedMaskProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
        unselectedMaskRenderContext->SetClipToBounds(true);
    }

    ViewStackProcessor::GetInstance()->Push(tabsNode);

    SetTabBarPosition(barPosition);
    if (!hasTabBarNode) {
        auto tabsFrameNode = AceType::DynamicCast<FrameNode>(tabsNode);
        CHECK_NULL_VOID(tabsFrameNode);
        auto tabsLayoutProperty = tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>();
        tabsLayoutProperty->UpdateIndex(index < 0 ? 0 : index);
        return;
    }
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    auto preIndex = tabsLayoutProperty->GetIndexValue(0);
    if ((index != preIndex) && (index >= 0)) {
        SetIndex(index);
        auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
        tabBarPattern->SetMaskAnimationByCreate(true);
        tabBarPattern->UpdateImageColor(index);
    }
}

void TabsModelNG::SetTabBarPosition(BarPosition tabBarPosition)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabsLayoutProperty, TabBarPosition, tabBarPosition);
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
    auto tabContentNum = swiperNode->TotalChildCount();
    if (tabContentNum == 0) {
        return;
    }
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    if (index > tabContentNum - 1 || index < 0) {
        index = 0;
    }
    tabBarLayoutProperty->UpdateIndicator(index);
    tabBarPattern->UpdateTextColor(index);
    swiperLayoutProperty->UpdateIndex(index);
    auto tabsFrameNode = AceType::DynamicCast<FrameNode>(tabsNode);
    CHECK_NULL_VOID(tabsFrameNode);
    auto tabsLayoutProperty = tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>();
    tabsLayoutProperty->UpdateIndex(index);
    swiperNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TabsModelNG::SetScrollable(bool scrollable)
{
    auto swiperPaintProperty = GetSwiperPaintProperty();
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateDisableSwipe(!scrollable);
}

void TabsModelNG::SetAnimationDuration(float duration)
{
    if (duration < 0) {
        return;
    }
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->SetAnimationDuration(static_cast<int32_t>(duration));
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

    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_VOID(tabBarRenderContext);
    if (barOverlap) {
        tabBarRenderContext->UpdateBackBlurRadius(BAR_BLUR_RADIUS);
        tabBarRenderContext->UpdateFrontSaturate(BAR_SATURATE);
    } else {
        tabBarRenderContext->UpdateBackBlurRadius(0.0_vp);
        tabBarRenderContext->ResetFrontSaturate();
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto defaultBgColorBlur = tabTheme->GetColorBottomTabSubBgBlur();
    auto tabBarPaintProperty = GetTabBarPaintProperty();
    CHECK_NULL_VOID(tabBarPaintProperty);
    if (barOverlap && !tabBarPaintProperty->GetBarBackgroundColor().has_value()) {
        tabBarRenderContext->UpdateBackgroundColor(defaultBgColorBlur);
    } else {
        tabBarRenderContext->UpdateBackgroundColor(
            tabBarPaintProperty->GetBarBackgroundColor().value_or(Color::BLACK.BlendOpacity(0.0f)));
    }
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
    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    CHECK_NULL_VOID(tabBarPaintProperty);
    tabBarPaintProperty->UpdateBarBackgroundColor(backgroundColor);
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
    auto index = tabsLayoutProperty->GetIndexValue(0);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);

    auto tabBarPosition = tabsLayoutProperty->GetTabBarPosition().value_or(BarPosition::START);
    auto tabsFocusNode = tabsNode->GetFocusHub();
    CHECK_NULL_VOID(tabsFocusNode);
    auto tabBarFocusNode = tabBarNode->GetFocusHub();
    CHECK_NULL_VOID(tabBarFocusNode);
    if (tabBarPosition == BarPosition::START) {
        tabsFocusNode->SetLastWeakFocusNode(AceType::WeakClaim(AceType::RawPtr(tabBarFocusNode)));
    }

    auto tabContentNum = swiperNode->TotalChildCount();
    if (index > tabContentNum - 1 || index < 0) {
        index = 0;
    }
    tabBarLayoutProperty->UpdateIndicator(index);
    tabBarPattern->UpdateTextColor(index);
    swiperLayoutProperty->UpdateIndex(index);

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

    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateVertical(axis == Axis::VERTICAL);
    dividerLayoutProperty->UpdateStrokeWidth(dividerStrokeWidth);
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
    auto tabsNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabsNode);
    auto tabsRenderContext = tabsNode->GetRenderContext();
    CHECK_NULL_VOID(tabsRenderContext);
    tabsRenderContext->UpdateClipEdge(clipEdge);
    auto tabsChildren = tabsNode->GetChildren();
    for (const auto& child : tabsChildren) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(childFrameNode);
        auto renderContext = childFrameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateClipEdge(clipEdge);
    }
}

void TabsModelNG::SetScrollableBarModeOptions(const ScrollableBarModeOptions& option)
{
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateScrollableBarModeOptions(option);
}

void TabsModelNG::SetBarGridAlign(const BarGridColumnOptions& BarGridColumnOptions)
{
    auto tabBarLayoutProperty = GetTabBarLayoutProperty();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateBarGridAlign(BarGridColumnOptions);
}
} // namespace OHOS::Ace::NG
