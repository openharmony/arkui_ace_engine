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

#include "core/components_ng/pattern/navigation/nav_bar_layout_algorithm.h"

#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_layout_util.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
float MeasureTitleBar(LayoutWrapper* layoutWrapper, const RefPtr<NavBarNode>& hostNode,
    const RefPtr<NavBarLayoutProperty>& navBarLayoutProperty, const SizeF& navigationSize)
{
    CHECK_NULL_RETURN(hostNode, 0.0f);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto index = hostNode->GetChildIndexById(titleBarNode->GetId());
    auto titleBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(titleBarWrapper, 0.0f);
    auto constraint = navBarLayoutProperty->CreateChildConstraint();

    /**
     * In the follow scenarios, we need to set the titleBar size to zero.
     * 1. TitleBar has no child.
     * 2. Titlebar is hidden and no titleBar animation is running.
     */
    auto translateState = navBarLayoutProperty->GetTitleBarTranslateStateValue(BarTranslateState::NONE);
    if ((translateState == BarTranslateState::NONE && navBarLayoutProperty->GetHideTitleBarValue(false)) ||
        titleBarNode->GetChildren().empty()) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        titleBarWrapper->Measure(constraint);
        return 0.0f;
    }
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_RETURN(titleBarLayoutProperty, 0.0f);
    if (titleBarLayoutProperty->HasTitleHeight()) {
        auto titleHeight =
            titleBarLayoutProperty->GetTitleHeightValue().ConvertToPxWithSize(constraint.percentReference.Height());
        constraint.selfIdealSize.SetHeight(static_cast<float>(titleHeight));
        titleBarWrapper->Measure(constraint);
        return static_cast<float>(titleHeight);
    }

    auto singleLineTitleHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    auto doubleLineTitleBarHeight = static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        doubleLineTitleBarHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    }
    // MINI mode
    if (navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        if (titleBarNode->GetSubtitle()) {
            constraint.selfIdealSize =
                OptionalSizeF(navigationSize.Width(), doubleLineTitleBarHeight);
            titleBarWrapper->Measure(constraint);
            return doubleLineTitleBarHeight;
        }

        constraint.selfIdealSize =
            OptionalSizeF(navigationSize.Width(), singleLineTitleHeight);
        titleBarWrapper->Measure(constraint);
        return singleLineTitleHeight;
    }

    float titleBarHeight = 0.0f;
    if (navBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::FREE) {
        auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_RETURN(titlePattern, 0.0f);
        titleBarHeight = titlePattern->GetTempTitleBarHeight();
    }

    // FREE 和 FULL 模式，有subtitle
    if (titleBarNode->GetSubtitle()) {
        if (NearZero(titleBarHeight)) {
            titleBarHeight = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
        }
        constraint.selfIdealSize = OptionalSizeF(navigationSize.Width(), titleBarHeight);
        titleBarWrapper->Measure(constraint);
        return titleBarHeight;
    }

    // no subtitle
    if (NearZero(titleBarHeight)) {
        titleBarHeight = static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    }
    constraint.selfIdealSize = OptionalSizeF(navigationSize.Width(), titleBarHeight);
    titleBarWrapper->Measure(constraint);
    return titleBarHeight;
}


SizeF MeasureContentChild(LayoutWrapper* layoutWrapper, const RefPtr<NavBarNode>& hostNode,
    const RefPtr<NavBarLayoutProperty>& navBarLayoutProperty, const SizeF& navigationSize, float titleBarHeight,
    float toolBarHeight, float toolBarDividerHeight)
{
    auto contentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
    CHECK_NULL_RETURN(contentNode, SizeF());
    auto index = hostNode->GetChildIndexById(contentNode->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(contentWrapper, SizeF());
    auto constraint = navBarLayoutProperty->CreateChildConstraint();
    float contentHeight = navigationSize.Height() - titleBarHeight - toolBarHeight - toolBarDividerHeight;
    auto contentSize = SizeF(navigationSize.Width(), contentHeight);
    NavigationLayoutUtil::UpdateConstraintWhenFixOrWrap(navBarLayoutProperty, constraint, contentSize);
    if (constraint.selfIdealSize.Height().has_value()) {
        auto currentHeight = constraint.selfIdealSize.Height().value();
        constraint.selfIdealSize.SetHeight(currentHeight);
    }
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    if (contentLayoutProperty->IsIgnoreOptsValid()) {
        IgnoreLayoutSafeAreaOpts& opts = *(contentLayoutProperty->GetIgnoreLayoutSafeAreaOpts());
        auto navBarLayoutPropety = AceType::DynamicCast<NavDestinationLayoutProperty>(hostNode->GetLayoutProperty());
        auto isVerticalCanExtend =
            NavigationLayoutUtil::CheckVerticalExtend(navBarLayoutPropety, hostNode, opts);
        bool isHorizontalExtend =
            (opts.edges & LAYOUT_SAFE_AREA_EDGE_HORIZONTAL) && (opts.type & LAYOUT_SAFE_AREA_TYPE_SYSTEM);
        if (isVerticalCanExtend.first || isVerticalCanExtend.second || isHorizontalExtend) {
            return contentSize;
        }
    }
    contentWrapper->Measure(constraint);
    return contentWrapper->GetGeometryNode()->GetFrameSize();
}

float LayoutTitleBar(LayoutWrapper* layoutWrapper, const RefPtr<NavBarNode>& hostNode,
    const RefPtr<NavBarLayoutProperty>& navBarLayoutProperty, float decorBarHeight = 0.0f)
{
    /**
     * When all the following conditions are met, we consider the titleBar height to be 0:
     * 1. TitleBar should hide.
     * 2. No titleBar animation is running or titleBar was translate out of navigation area.
     */
    auto translateState = navBarLayoutProperty->GetTitleBarTranslateStateValue(BarTranslateState::NONE);
    if (navBarLayoutProperty->GetHideTitleBarValue(false) && translateState != BarTranslateState::TRANSLATE_ZERO) {
        return 0.0f;
    }
    auto titleBarNode = hostNode->GetTitleBarNode();
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto index = hostNode->GetChildIndexById(titleBarNode->GetId());
    auto titleBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(titleBarWrapper, 0.0f);
    auto geometryNode = titleBarWrapper->GetGeometryNode();
    float offsetY = 0.0f;
    offsetY = NavigationTitleUtil::CalculateTitlebarOffset(titleBarNode);
    offsetY += decorBarHeight;
    auto titleBarOffset = OffsetF(0.0f, offsetY);
    auto navBarPattern = hostNode->GetPattern<NavBarPattern>();
    CHECK_NULL_RETURN(navBarPattern, 0.0f);
    navBarPattern->SetTitleBarOffsetY(offsetY);
    geometryNode->SetMarginFrameOffset(titleBarOffset);
    titleBarWrapper->Layout();
    return geometryNode->GetFrameSize().Height();
}

void LayoutContent(LayoutWrapper* layoutWrapper, const RefPtr<NavBarNode>& hostNode,
    const RefPtr<NavBarLayoutProperty>& navBarLayoutProperty, float titlebarHeight)
{
    auto contentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
    CHECK_NULL_VOID(contentNode);
    auto index = hostNode->GetChildIndexById(hostNode->GetContentNode()->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(contentWrapper);
    auto geometryNode = contentWrapper->GetGeometryNode();
    auto pattern = hostNode->GetPattern<NavBarPattern>();
    float avoidKeyboardOffset = pattern ? pattern->GetAvoidKeyboardOffset() : 0.0f;
    auto contentOffset = OffsetF(0.0f, avoidKeyboardOffset);
    contentOffset += OffsetF(0.0f, titlebarHeight);

    auto layoutProperty = contentNode->GetLayoutProperty();
    if (layoutProperty && layoutProperty->IsIgnoreOptsValid()) {
        geometryNode->SetMarginFrameOffset(contentOffset);
        IgnoreLayoutSafeAreaOpts& opts = *(layoutProperty->GetIgnoreLayoutSafeAreaOpts());
        auto safeExpand = contentNode->GetAccumulatedSafeAreaExpand(false, opts);
        auto offsetX = safeExpand.left.value_or(0.0f);
        auto offsetY = safeExpand.top.value_or(0.0f);
        
        auto barStyle = pattern->GetTitleBarStyle().value_or(BarStyle::STANDARD);
        auto navBaseLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
        CHECK_NULL_VOID(navBaseLayoutProperty);
        if (!(navBaseLayoutProperty->GetHideTitleBar().value_or(false) || barStyle == BarStyle::STACK ||
                (barStyle == BarStyle::SAFE_AREA_PADDING && !NearZero(pattern->GetTitleBarOffsetY())))) {
            offsetY = 0.0f;
        }
        contentOffset -= OffsetF(offsetX, offsetY);
    }
    geometryNode->SetMarginFrameOffset(contentOffset);
    contentWrapper->Layout();
}


float TransferBarHeight(const RefPtr<NavBarNode>& hostNode, float originBarHeight, bool isTitleBar)
{
    auto navBarPattern = hostNode->GetPattern<NavBarPattern>();
    CHECK_NULL_RETURN(navBarPattern, originBarHeight);
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_RETURN(navBarLayoutProperty, originBarHeight);
    auto barStyle = isTitleBar ? navBarPattern->GetTitleBarStyle() : navBarPattern->GetToolBarStyle();
    if (isTitleBar) {
        /**
         * In the follow scenarios, we need to convert titleBar's height to zero.
         * 1. TitleBar has translate out of the navigation area.
         * 2. Titlebar is hidden and no titleBar animation is running.
         */
        auto translateState = navBarLayoutProperty->GetTitleBarTranslateStateValue(BarTranslateState::NONE);
        if (translateState == BarTranslateState::TRANSLATE_HEIGHT ||
            (translateState == BarTranslateState::NONE && navBarLayoutProperty->GetHideTitleBarValue(false))) {
            return 0.0f;
        }
    } else {
        /**
         * In the follow scenarios, we need to convert toolBar's height to zero.
         * 1. ToolBar has translate out of the navigation area.
         * 2. Toolbar is hidden and no toolBar animation is running.
         */
        auto translateState = navBarLayoutProperty->GetToolBarTranslateStateValue(BarTranslateState::NONE);
        if (translateState == BarTranslateState::TRANSLATE_HEIGHT ||
            (translateState == BarTranslateState::NONE && navBarLayoutProperty->GetHideToolBarValue(false))) {
            return 0.0f;
        }
    }
    return barStyle.value_or(BarStyle::STANDARD) == BarStyle::STANDARD ? originBarHeight : 0.0f;
}
} // namespace

void NavBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navBarPattern = hostNode->GetPattern<NavBarPattern>();
    CHECK_NULL_VOID(navBarPattern);
    auto navBarLayoutProperty = AceType::DynamicCast<NavBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navBarLayoutProperty);
    const auto& constraint = navBarLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    auto size = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    NavigationLayoutUtil::UpdateTitleBarMenuNode(hostNode, size);
    float titleBarHeight = MeasureTitleBar(layoutWrapper, hostNode, navBarLayoutProperty, size);
    navBarPattern->MarkSafeAreaPaddingChangedWithCheckTitleBar(titleBarHeight);
    navBarPattern->SetTitleBarHeight(titleBarHeight);
    auto transferedTitleBarHeight = TransferBarHeight(hostNode, titleBarHeight, true);
    float toolBarHeight = NavigationLayoutUtil::MeasureToolBar(layoutWrapper, hostNode, navBarLayoutProperty, size);
    navBarPattern->SetToolBarHeight(toolBarHeight);
    // after the visibility of title/tool bar determined, update safeAreaPadding of content node if needed.
    NavigationLayoutUtil::UpdateContentSafeAreaPadding(hostNode, titleBarHeight);
    auto transferedToolBarHeight = TransferBarHeight(hostNode, toolBarHeight, false);
    float toolBarDividerHeight = NavigationLayoutUtil::MeasureToolBarDivider(
        layoutWrapper, hostNode, navBarLayoutProperty, size, transferedToolBarHeight);
    navBarPattern->SetToolBarDividerHeight(toolBarDividerHeight);
    auto transferedToolBarDividerHeight = TransferBarHeight(hostNode, toolBarDividerHeight, false);
    auto contentChildSize = MeasureContentChild(layoutWrapper, hostNode, navBarLayoutProperty, size,
        transferedTitleBarHeight, transferedToolBarHeight, transferedToolBarDividerHeight);
    size.SetHeight(transferedTitleBarHeight + transferedToolBarHeight + transferedToolBarDividerHeight +
                   contentChildSize.Height());
    size.SetWidth(contentChildSize.Width());
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);

    MeasureAdaptiveLayoutChildren(
        layoutWrapper, size, transferedTitleBarHeight, transferedToolBarHeight + transferedToolBarDividerHeight);
}

void NavBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navBarLayoutProperty = AceType::DynamicCast<NavBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navBarLayoutProperty);

    float decorBarHeight = 0.0f;
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(hostNode->GetNavigationNode());
    if (navigationNode) {
        auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
        auto navBarPattern = hostNode->GetPattern<NavBarPattern>();
        if (navigationPattern && navBarPattern) {
            auto toolbarManager = navigationPattern->GetToolBarManager();
            auto barStyle = navBarPattern->GetTitleBarStyle().value_or(BarStyle::STANDARD);
            if (toolbarManager && toolbarManager->GetIsMoveUp() && barStyle == BarStyle::STACK) {
                decorBarHeight = static_cast<float>(toolbarManager->GetTitleHeight().ConvertToPx());
            }
        }
    }
    float titlebarHeight = LayoutTitleBar(layoutWrapper, hostNode, navBarLayoutProperty, decorBarHeight);
    auto transferedTitleBarHeight = TransferBarHeight(hostNode, titlebarHeight, true);
    LayoutContent(layoutWrapper, hostNode, navBarLayoutProperty, transferedTitleBarHeight);
    float toolbarHeight = NavigationLayoutUtil::LayoutToolBar(
        layoutWrapper, hostNode, navBarLayoutProperty, false);
    NavigationLayoutUtil::LayoutToolBarDivider(
        layoutWrapper, hostNode, navBarLayoutProperty, toolbarHeight, false);
}

void NavBarLayoutAlgorithm::MeasureAdaptiveLayoutChildren(
    LayoutWrapper* layoutWrapper, SizeF& realSize, float titleBarHeight, float toolBarHeight)
{
    auto hostNode = AceType::DynamicCast<NavBarNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navBarLayoutProperty = AceType::DynamicCast<NavBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto contentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
    CHECK_NULL_VOID(contentNode);
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty->IsIgnoreOptsValid());
    IgnoreLayoutSafeAreaOpts& opts = *(contentLayoutProperty->GetIgnoreLayoutSafeAreaOpts());

    auto isVerticalCanExtend = NavigationLayoutUtil::CheckVerticalExtend(navBarLayoutProperty, hostNode, opts);
    bool isHorizontalExtend =
        (opts.edges & LAYOUT_SAFE_AREA_EDGE_HORIZONTAL) && (opts.type & LAYOUT_SAFE_AREA_TYPE_SYSTEM);
    if (!isVerticalCanExtend.first && !isVerticalCanExtend.second && !isHorizontalExtend) {
        return;
    }

    ExpandEdges sae = hostNode->GetAccumulatedSafeAreaExpand(true, opts);
    if (!isVerticalCanExtend.first) {
        realSize.MinusHeight(titleBarHeight);
        realSize.MinusHeight(sae.top.value_or(0.0f));
    }
    if (!isVerticalCanExtend.second) {
        realSize.MinusHeight(toolBarHeight);
        realSize.MinusHeight(sae.bottom.value_or(0.0f));
    }

    auto childConstraint = navBarLayoutProperty->CreateChildConstraint();
    childConstraint.selfIdealSize.SetSize(realSize);
    contentNode->GetGeometryNode()->SetParentLayoutConstraint(childConstraint);
    IgnoreLayoutSafeAreaBundle bundle;
    bundle.second = hostNode;
    bundle.first.emplace_back(contentNode);
    auto context = hostNode->GetContextWithCheck();
    CHECK_NULL_VOID(context);
    hostNode->SetDelaySelfLayoutForIgnore();
    contentNode->SetDelaySelfLayoutForIgnore();
    context->AddIgnoreLayoutSafeAreaBundle(std::move(bundle));
}
} // namespace OHOS::Ace::NG
