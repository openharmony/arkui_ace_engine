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

#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"

#include "core/components_ng/pattern/navigation/navigation_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

namespace OHOS::Ace::NG {
namespace {

bool CheckTopEdgeOverlap(const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty,
    const RefPtr<NavDestinationGroupNode>& hostNode, SafeAreaExpandOpts opts)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto safeAreaManager = pipeline->GetSafeAreaManager();

    auto parentGlobalOffset = hostNode->GetParentGlobalOffsetDuringLayout();
    auto NavDesGeometryNode = hostNode->GetGeometryNode();
    CHECK_NULL_RETURN(NavDesGeometryNode, false);
    auto frame = NavDesGeometryNode->GetFrameRect() + parentGlobalOffset;

    const auto& padding = navDestinationLayoutProperty->CreatePaddingAndBorder();
    if ((opts.edges & SAFE_AREA_EDGE_TOP) && (opts.type & SAFE_AREA_TYPE_SYSTEM)
        && NearEqual(padding.top.value(), 0.0f)) {
        SafeAreaExpandOpts opts = {.type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_TOP};
        auto safeAreaPos = safeAreaManager->GetCombinedSafeArea(opts);

        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
        CHECK_NULL_RETURN(titleBarNode, false);
        auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_RETURN(titlePattern, false);
        auto options = titlePattern->GetTitleBarOptions();
        auto barStyle = options.bgOptions.barStyle.value_or(BarStyle::STANDARD);
        if ((navDestinationLayoutProperty->GetHideTitleBar().value_or(false) || barStyle == BarStyle::STACK) &&
            safeAreaPos.top_.IsOverlapped(frame.Top())) {
            return true;
        }
    }
    return false;
}

bool CheckBottomEdgeOverlap(const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty,
    const RefPtr<NavDestinationGroupNode>& hostNode, SafeAreaExpandOpts opts)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto safeAreaManager = pipeline->GetSafeAreaManager();

    auto parentGlobalOffset = hostNode->GetParentGlobalOffsetDuringLayout();
    auto NavBarGeometryNode = hostNode->GetGeometryNode();
    CHECK_NULL_RETURN(NavBarGeometryNode, false);
    auto frame = NavBarGeometryNode->GetFrameRect() + parentGlobalOffset;

    const auto& padding = navDestinationLayoutProperty->CreatePaddingAndBorder();
    if ((opts.edges & SAFE_AREA_EDGE_BOTTOM) && (opts.type & SAFE_AREA_TYPE_SYSTEM)
        && NearEqual(padding.bottom.value(), 0.0f)) {
        SafeAreaExpandOpts opts = {.type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_BOTTOM};
        auto safeAreaPos = safeAreaManager->GetCombinedSafeArea(opts);
        if (safeAreaPos.bottom_.IsOverlapped(frame.Bottom())) {
            return true;
        }
    }
    return false;
}

NavSafeArea CheckIgnoreLayoutSafeArea(LayoutWrapper* layoutWrapper,
    const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty)
{
    NavSafeArea safeArea;
    auto opts = navDestinationLayoutProperty->GetIgnoreLayoutSafeAreaValue({.type = SAFE_AREA_TYPE_NONE,
        .edges = SAFE_AREA_TYPE_NONE});
    
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, safeArea);
    auto inset = pipeline->GetSafeArea();
    auto safeAreaManager = pipeline->GetSafeAreaManager();

    bool edgeTopOverLayCondition = CheckTopEdgeOverlap(navDestinationLayoutProperty, hostNode, opts);
    bool edgeBottomOverLayCondition = CheckBottomEdgeOverlap(navDestinationLayoutProperty, hostNode, opts);

    if (edgeTopOverLayCondition) {
        auto contentNode =  AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
        CHECK_NULL_RETURN(contentNode, safeArea);
        SafeAreaExpandOpts opts = {.type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_NONE};
        contentNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
        safeArea.top = static_cast<float>(inset.top_.Length());
    }

    if (edgeBottomOverLayCondition) {
        safeArea.bottom = static_cast<float>(inset.bottom_.Length());
    }
    return safeArea;
}

float MeasureTitleBar(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, const SizeF& size)
{
    auto navDestinationPattern = hostNode->GetPattern<NavDestinationPattern>();
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto index = hostNode->GetChildIndexById(titleBarNode->GetId());
    auto titleBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(titleBarWrapper, 0.0f);
    auto constraint = navDestinationLayoutProperty->CreateChildConstraint();
    if (navDestinationLayoutProperty->GetHideTitleBar().value_or(false) ||
        (!titleBarNode->GetSubtitle() && !titleBarNode->GetTitle() && !navDestinationPattern->GetBackButtonState())) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        titleBarWrapper->Measure(constraint);
        return 0.0f;
    }
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_RETURN(titleBarLayoutProperty, 0.0f);
    if (titleBarLayoutProperty->HasTitleHeight()) {
        auto titleHeight = static_cast<float>(
            titleBarLayoutProperty->GetTitleHeightValue().ConvertToPxWithSize(constraint.percentReference.Height()));
        constraint.selfIdealSize.SetHeight((titleHeight));
        titleBarWrapper->Measure(constraint);
        return titleHeight;
    }
    auto singleLineTitleHeight = SINGLE_LINE_TITLEBAR_HEIGHT;
    auto doubleLineTitleBarHeight = DOUBLE_LINE_TITLEBAR_HEIGHT;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        doubleLineTitleBarHeight = SINGLE_LINE_TITLEBAR_HEIGHT;
    }
    auto titleHeight = titleBarLayoutProperty->GetTitleHeightValue(
        titleBarNode->GetSubtitle() ? doubleLineTitleBarHeight : singleLineTitleHeight);
    constraint.selfIdealSize = OptionalSizeF(
        size.Width(), static_cast<float>(titleHeight.ConvertToPxWithSize(constraint.percentReference.Height())));
    titleBarWrapper->Measure(constraint);
    return static_cast<float>(titleHeight.ConvertToPxWithSize(constraint.percentReference.Height()));
}

float MeasureContentChild(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, const SizeF& size, float titleBarHeight)
{
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_RETURN(contentNode, 0.0f);
    auto index = hostNode->GetChildIndexById(contentNode->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(contentWrapper, 0.0f);
    auto constraint = navDestinationLayoutProperty->CreateChildConstraint();
    float contentHeight = size.Height() - titleBarHeight;
    if (NavigationLayoutAlgorithm::IsAutoHeight(navDestinationLayoutProperty)) {
        constraint.selfIdealSize.SetWidth(size.Width());
    } else {
        constraint.selfIdealSize = OptionalSizeF(size.Width(), contentHeight);
    }
    auto currentHeight = constraint.selfIdealSize.Height().value() ;
    auto safeArea = CheckIgnoreLayoutSafeArea(layoutWrapper, hostNode, navDestinationLayoutProperty);
    constraint.selfIdealSize.SetHeight(currentHeight + safeArea.top + safeArea.bottom);
    contentWrapper->Measure(constraint);
    return currentHeight;
}

float LayoutTitleBar(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty)
{
    if (navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) {
        return 0.0f;
    }
    auto titleBarNode = hostNode->GetTitleBarNode();
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto index = hostNode->GetChildIndexById(titleBarNode->GetId());
    auto titleBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(titleBarWrapper, 0.0f);
    auto geometryNode = titleBarWrapper->GetGeometryNode();
    auto titleBarOffset = OffsetT<float>(0.0f, 0.0f);
    const auto& padding = navDestinationLayoutProperty->CreatePaddingAndBorder();
    titleBarOffset.AddX(padding.left.value_or(0));
    titleBarOffset.AddY(padding.top.value_or(0));
    geometryNode->SetMarginFrameOffset(titleBarOffset);
    titleBarWrapper->Layout();
    return geometryNode->GetFrameSize().Height();
}

void LayoutContent(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, float titlebarHeight)
{
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto index = hostNode->GetChildIndexById(hostNode->GetContentNode()->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(contentWrapper);
    auto geometryNode = contentWrapper->GetGeometryNode();
    auto contentOffset = OffsetT<float>(0.0f, 0.0f);
    if (!navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) {
        contentOffset = OffsetT<float>(0.0f, titlebarHeight);
    }
    const auto& padding = navDestinationLayoutProperty->CreatePaddingAndBorder();
    contentOffset.AddX(padding.left.value_or(0.0f));
    contentOffset.AddY(padding.top.value_or(0.0f));

    auto safeArea = CheckIgnoreLayoutSafeArea(layoutWrapper, hostNode, navDestinationLayoutProperty);
    auto offsetY = contentOffset.GetY();
    auto opts = navDestinationLayoutProperty->GetIgnoreLayoutSafeAreaValue({.type = SAFE_AREA_TYPE_NONE,
        .edges = SAFE_AREA_TYPE_NONE});
    if ((opts.edges & SAFE_AREA_EDGE_TOP) && NearEqual(offsetY, 0.0f)) {
        offsetY -= safeArea.top;
        contentOffset.SetY(offsetY);
    }

    geometryNode->SetMarginFrameOffset(contentOffset);
    contentWrapper->Layout();
}

float TransferTitleBarHeight(const RefPtr<NavDestinationGroupNode>& hostNode, float titleBarHeight)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titlePattern, 0.0f);
    auto options = titlePattern->GetTitleBarOptions();
    auto barStyle = options.bgOptions.barStyle.value_or(BarStyle::STANDARD);
    float resetTitleBarHeight = 0.0f;
    if (barStyle == BarStyle::STACK) {
        resetTitleBarHeight = 0.0f;
    } else {
        resetTitleBarHeight = titleBarHeight;
    }
    return resetTitleBarHeight;
}

} // namespace

void NavDestinationLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navDestinationLayoutProperty =
        AceType::DynamicCast<NavDestinationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    const auto& constraint = navDestinationLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    auto size = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);

    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);

    float titleBarHeight = MeasureTitleBar(layoutWrapper, hostNode, navDestinationLayoutProperty, size);
    auto resetTitleBarHeight = TransferTitleBarHeight(hostNode, titleBarHeight);
    float contentChildHeight =
            MeasureContentChild(layoutWrapper, hostNode, navDestinationLayoutProperty, size, resetTitleBarHeight);

    size.SetHeight(resetTitleBarHeight + contentChildHeight);
    if (NearZero(resetTitleBarHeight + contentChildHeight)) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto height = pipeline->GetRootHeight();
        size.SetHeight(height);
    } else {
        size.AddWidth(padding.left.value_or(0.0f) + padding.right.value_or(0.0f));
        size.AddHeight(padding.top.value_or(0.0f) + padding.bottom.value_or(0.0f));
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
}

void NavDestinationLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navDestinationLayoutProperty =
        AceType::DynamicCast<NavDestinationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navDestinationLayoutProperty);

    auto expandOpts = navDestinationLayoutProperty->GetIgnoreLayoutSafeAreaValue({.type = SAFE_AREA_TYPE_NONE,
        .edges = SAFE_AREA_TYPE_NONE});
    bool edgeTopOverLayCondition = CheckTopEdgeOverlap(navDestinationLayoutProperty, hostNode, expandOpts);
    bool edgeBottomOverLayCondition = CheckBottomEdgeOverlap(navDestinationLayoutProperty, hostNode, expandOpts);
    if (edgeTopOverLayCondition || edgeBottomOverLayCondition) {
        Measure(layoutWrapper);
    }

    float titlebarHeight = LayoutTitleBar(layoutWrapper, hostNode, navDestinationLayoutProperty);
    auto resetTitleBarHeight = TransferTitleBarHeight(hostNode, titlebarHeight);
    LayoutContent(layoutWrapper, hostNode, navDestinationLayoutProperty, resetTitleBarHeight);

    auto&& opts = navDestinationLayoutProperty->GetSafeAreaExpandOpts();
    if (opts) {
        auto geometryNode = hostNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        TAG_LOGD(AceLogTag::ACE_NAVIGATION,
            "Navdestination id is %d{public}, frameRect is %{public}s",
            hostNode->GetId(), geometryNode->GetFrameRect().ToString().c_str());
    }
}

} // namespace OHOS::Ace::NG