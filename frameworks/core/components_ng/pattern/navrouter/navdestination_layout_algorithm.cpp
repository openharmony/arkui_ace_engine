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
#include "core/components_ng/pattern/navigation/navigation_layout_util.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
const std::unordered_set<std::string> EMBEDDED_NODE_TAG = { V2::SHEET_WRAPPER_TAG, V2::ALERT_DIALOG_ETS_TAG,
    V2::ACTION_SHEET_DIALOG_ETS_TAG, V2::DIALOG_ETS_TAG };

float MeasureTitleBar(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, const SizeF& size,
    const std::optional<float>& containerModalTitleHeight)
{
    auto navDestinationPattern = hostNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(navDestinationPattern, 0.0f);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto index = hostNode->GetChildIndexById(titleBarNode->GetId());
    auto titleBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(titleBarWrapper, 0.0f);
    auto constraint = navDestinationLayoutProperty->CreateChildConstraint();
    auto translateState = navDestinationLayoutProperty->GetTitleBarTranslateStateValue(BarTranslateState::NONE);
    /**
     * In the follow scenarios, we need to set the titleBar size to zero.
     * 1. TitleBar has no mainTitle&subTitle and hide backBotton.
     * 2. Titlebar is hidden and no titleBar animation is running.
     */
    if ((translateState == BarTranslateState::NONE &&
            navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) ||
        (!titleBarNode->GetSubtitle() && !titleBarNode->GetTitle() && !navDestinationPattern->GetBackButtonState())) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        titleBarWrapper->Measure(constraint);
        return 0.0f;
    }

    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_RETURN(titleBarLayoutProperty, 0.0f);
    bool isCustomTitleBarSize = titleBarLayoutProperty->GetIsCustomTitleBarSizeValue(false);
    if (containerModalTitleHeight.has_value() && !isCustomTitleBarSize) {
        constraint.selfIdealSize.SetHeight(containerModalTitleHeight.value());
        titleBarWrapper->Measure(constraint);
        return containerModalTitleHeight.value();
    }

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

SizeF MeasureContentChild(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty,
    const SizeF& size, float titleBarAndToolBarHeight)
{
    auto contentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
    CHECK_NULL_RETURN(contentNode, SizeF());
    auto index = hostNode->GetChildIndexById(contentNode->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(contentWrapper, SizeF());
    auto constraint = navDestinationLayoutProperty->CreateChildConstraint();
    float contentHeight = size.Height() - titleBarAndToolBarHeight;
    auto contentSize = SizeF(size.Width(), contentHeight);
    NavigationLayoutUtil::UpdateConstraintWhenFixOrWrap(navDestinationLayoutProperty, constraint, contentSize);
    if (constraint.selfIdealSize.Height().has_value()) {
        auto currentHeight = constraint.selfIdealSize.Height().value();
        constraint.selfIdealSize.SetHeight(currentHeight);
    }
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    if (contentLayoutProperty->IsIgnoreOptsValid()) {
        IgnoreLayoutSafeAreaOpts& opts = *(contentLayoutProperty->GetIgnoreLayoutSafeAreaOpts());
        auto navDestinationLayoutPropety =
            AceType::DynamicCast<NavDestinationLayoutProperty>(hostNode->GetLayoutProperty());
        auto isVerticalCanExtend =
            NavigationLayoutUtil::CheckVerticalExtend(navDestinationLayoutPropety, hostNode, opts);
        bool isHorizontalExtend =
            (opts.edges & LAYOUT_SAFE_AREA_EDGE_HORIZONTAL) && (opts.type & LAYOUT_SAFE_AREA_TYPE_SYSTEM);
        if (isVerticalCanExtend.first || isVerticalCanExtend.second || isHorizontalExtend) {
            return contentSize;
        }
    }
    contentWrapper->Measure(constraint);
    return contentWrapper->GetGeometryNode()->GetFrameSize();
}

float LayoutTitleBar(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, float decorBarHeight = 0.0f)
{
    /**
     * When all the following conditions are met, we consider the titleBar height to be 0:
     * 1. TitleBar should hide.
     * 2. No titleBar animation is running or titleBar was translate out of navigation area.
     */
    auto translateState = navDestinationLayoutProperty->GetTitleBarTranslateStateValue(BarTranslateState::NONE);
    if (translateState != BarTranslateState::TRANSLATE_ZERO &&
        navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) {
        return 0.0f;
    }
    auto titleBarNode = hostNode->GetTitleBarNode();
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto index = hostNode->GetChildIndexById(titleBarNode->GetId());
    auto titleBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(titleBarWrapper, 0.0f);
    auto geometryNode = titleBarWrapper->GetGeometryNode();
    auto offsetY = NavigationTitleUtil::CalculateTitlebarOffset(titleBarNode);
    offsetY += decorBarHeight;
    auto navDestinationPattern = hostNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(navDestinationPattern, 0.0f);
    navDestinationPattern->SetTitleBarOffsetY(offsetY);
    auto titleBarOffset = OffsetT<float>(0.0f, offsetY);
    const auto& padding = navDestinationLayoutProperty->CreatePaddingAndBorder();
    titleBarOffset.AddX(padding.left.value_or(0.0f));
    titleBarOffset.AddY(padding.top.value_or(0.0f));
    geometryNode->SetMarginFrameOffset(titleBarOffset);
    titleBarWrapper->Layout();
    return geometryNode->GetFrameSize().Height();
}

void LayoutContent(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, float titlebarHeight)
{
    auto contentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
    CHECK_NULL_VOID(contentNode);
    auto index = hostNode->GetChildIndexById(hostNode->GetContentNode()->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(contentWrapper);
    auto geometryNode = contentWrapper->GetGeometryNode();
    auto pattern = hostNode->GetPattern<NavDestinationPattern>();
    float avoidKeyboardOffset = 0.0f;
    if (pattern) {
        avoidKeyboardOffset = pattern->GetAvoidKeyboardOffset();
    }
    auto contentOffset = OffsetF(0.0f, avoidKeyboardOffset);
    contentOffset += OffsetF(0.0f, titlebarHeight);
    const auto& padding = navDestinationLayoutProperty->CreatePaddingAndBorder();
    contentOffset.AddX(padding.left.value_or(0.0f));
    contentOffset.AddY(padding.top.value_or(0.0f));

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

void MeasureOverlay(const RefPtr<NavDestinationGroupNode>& hostNode,
    const LayoutConstraintF& constraint)
{
    for (const auto& children : hostNode->GetAllChildrenWithBuild()) {
        if (children && EMBEDDED_NODE_TAG.find(children->GetHostNode()->GetTag()) != EMBEDDED_NODE_TAG.end()) {
            children->Measure(constraint);
        }
    }
}

void LayoutOverlay(const RefPtr<NavDestinationGroupNode>& hostNode)
{
    auto navdestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_VOID(navdestinationLayoutProperty);
    for (const auto& children : hostNode->GetAllChildrenWithBuild()) {
        if (children && EMBEDDED_NODE_TAG.find(children->GetHostNode()->GetTag()) != EMBEDDED_NODE_TAG.end()) {
            auto geometryNode = children->GetGeometryNode();
            auto paddingOffset = OffsetT<float>(0.0f, 0.0f);
            const auto& padding = navdestinationLayoutProperty->CreatePaddingAndBorder();
            paddingOffset.AddX(padding.left.value_or(0.0f));
            paddingOffset.AddY(padding.top.value_or(0.0f));
            geometryNode->SetMarginFrameOffset(paddingOffset);
            children->Layout();
        }
    }
}

float TransferBarHeight(const RefPtr<NavDestinationGroupNode>& hostNode, float defaultBarHeight, bool isTitleBar)
{
    CHECK_NULL_RETURN(hostNode, 0.0f);
    auto navDestinationPattern = hostNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(navDestinationPattern, defaultBarHeight);
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_RETURN(navDestinationLayoutProperty, defaultBarHeight);
    if (isTitleBar) {
        /**
         * In the follow scenarios, we need to convert titleBar's height to zero.
         * 1. TitleBar has translate out of the navigation area.
         * 2. Titlebar is hidden and no titleBar animation is running.
         */
        auto translateState = navDestinationLayoutProperty->GetTitleBarTranslateStateValue(BarTranslateState::NONE);
        if (translateState == BarTranslateState::TRANSLATE_HEIGHT ||
            (translateState == BarTranslateState::NONE && navDestinationLayoutProperty->GetHideTitleBarValue(false))) {
            return 0.0f;
        }
    } else {
        /**
         * In the follow scenarios, we need to convert toolBar's height to zero.
         * 1. ToolBar has translate out of the navigation area.
         * 2. Toolbar is hidden and no toolBar animation is running.
         */
        auto translateState = navDestinationLayoutProperty->GetToolBarTranslateStateValue(BarTranslateState::NONE);
        if (translateState == BarTranslateState::TRANSLATE_HEIGHT ||
            (translateState == BarTranslateState::NONE && navDestinationLayoutProperty->GetHideToolBarValue(false))) {
            return 0.0f;
        }
    }
    auto barStyle = isTitleBar ? navDestinationPattern->GetTitleBarStyle() : navDestinationPattern->GetToolBarStyle();
    return barStyle.value_or(BarStyle::STANDARD) == BarStyle::STANDARD ? defaultBarHeight : 0.0f;
}

bool IsDestSizeMatchNavigation(const RefPtr<NavDestinationGroupNode>& destNode, const SizeF& navDestSize)
{
    CHECK_NULL_RETURN(destNode, false);
    auto rotateAngle = destNode->GetPageRotateAngle();
    if (rotateAngle.has_value() && rotateAngle.value() != ROTATION_0) {
        return true;
    }

    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(destNode->GetNavigationNode());
    CHECK_NULL_RETURN(navigationNode, false);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(navigationPattern, false);
    auto navigationSize = navigationPattern->GetNavigationSize();
    return NearEqual(navDestSize.Width(), navigationSize.Width()) &&
        NearEqual(navDestSize.Height(), navigationSize.Height());
}

std::optional<float> GetContainerModalTitleHeightIfNeeded(
    const RefPtr<NavDestinationPattern>& navDestPattern, const SizeF& navDestSize)
{
    std::optional<float> titleHeight;
    CHECK_NULL_RETURN(navDestPattern, titleHeight);
    auto navDestNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestPattern->GetHost());
    CHECK_NULL_RETURN(navDestNode, titleHeight);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, titleHeight);
    /**
     * When all of the following conditions are met, the titleBar height of NavDestination
     * needs to be set to the window titleBar height:
     *  1. TitleBar of window is invisible.
     *  2. Size of Navigation match size of belonged page.
     *  3. Height of NavDestination match height of Navigation.
     *
     * When all of the following conditions are met, the titleBar of NavDestination
     * needs to avoid the Control Buttons of ContainerModal:
     *  1. TitleBar of window is invisible.
     *  2. Size of Navigation match size of belonged page.
     */
    titleBarNode->SetUseContainerModalTitleHeight(false);
    titleBarNode->SetNeedAvoidContainerModal(false);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navDestPattern->GetNavigationNode());
    CHECK_NULL_RETURN(navigationNode, titleHeight);
    auto pipeline = navigationNode->GetContext();
    CHECK_NULL_RETURN(pipeline, titleHeight);
    auto avoidInfoMgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_RETURN(avoidInfoMgr, titleHeight);
    if (!avoidInfoMgr->NeedAvoidContainerModal()) {
        return titleHeight;
    }
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(navigationPattern, titleHeight);
    if (!navigationPattern->IsFullPageNavigation()) {
        return titleHeight;
    }
    titleBarNode->SetNeedAvoidContainerModal(true);
    auto navigationSize = navigationPattern->GetNavigationSize();
    if (!NearEqual(navigationSize.Height(), navDestSize.Height())) {
        return titleHeight;
    }
    auto height = avoidInfoMgr->GetContainerModalTitleHeight();
    if (height <= 0) {
        return titleHeight;
    }
    titleBarNode->SetUseContainerModalTitleHeight(true);
    titleHeight = height;
    return titleHeight;
}
} // namespace

void NavDestinationLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navDestinationPattern = hostNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    auto navDestinationLayoutProperty =
        AceType::DynamicCast<NavDestinationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    const auto& constraint = navDestinationLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    auto size = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    auto containerModalTitleHeight = GetContainerModalTitleHeightIfNeeded(navDestinationPattern, size);
    bool sizeMatch = IsDestSizeMatchNavigation(hostNode, size);
    hostNode->SetIsSizeMatchNavigation(sizeMatch);

    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    NavigationLayoutUtil::UpdateTitleBarMenuNode(hostNode, size);
    float titleBarHeight = MeasureTitleBar(
        layoutWrapper, hostNode, navDestinationLayoutProperty, size, containerModalTitleHeight);
    navDestinationPattern->MarkSafeAreaPaddingChangedWithCheckTitleBar(titleBarHeight);
    navDestinationPattern->SetTitleBarHeight(titleBarHeight);
    auto transferedTitleBarHeight = TransferBarHeight(hostNode, titleBarHeight, true);
    float toolBarHeight =
        NavigationLayoutUtil::MeasureToolBar(layoutWrapper, hostNode, navDestinationLayoutProperty, size);
    navDestinationPattern->SetToolBarHeight(toolBarHeight);
    auto transferedToolBarHeight = TransferBarHeight(hostNode, toolBarHeight, false);
    float toolBarDividerHeight = NavigationLayoutUtil::MeasureToolBarDivider(
        layoutWrapper, hostNode, navDestinationLayoutProperty, size, toolBarHeight);
    navDestinationPattern->SetToolBarDividerHeight(toolBarDividerHeight);
    // after the visibility of title/tool bar determined, update safeAreaPadding of content node if needed.
    NavigationLayoutUtil::UpdateContentSafeAreaPadding(hostNode, titleBarHeight);
    auto transferedToolBarDividerHeight = TransferBarHeight(hostNode, toolBarDividerHeight, false);
    float titleBarAndToolBarHeight =
        transferedTitleBarHeight + transferedToolBarHeight + transferedToolBarDividerHeight;
    auto contentChildSize =
        MeasureContentChild(layoutWrapper, hostNode, navDestinationLayoutProperty, size, titleBarAndToolBarHeight);
    size.SetHeight(transferedTitleBarHeight + transferedToolBarHeight + transferedToolBarDividerHeight +
                   contentChildSize.Height());
    size.SetWidth(contentChildSize.Width());
    
    ReCalcNavDestinationSize(layoutWrapper, size);

    MeasureOverlay(hostNode, navDestinationLayoutProperty->CreateChildConstraint());

    MeasureAdaptiveLayoutChildren(
        layoutWrapper, size, transferedTitleBarHeight, transferedToolBarHeight + transferedToolBarDividerHeight);
}

void NavDestinationLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navDestinationLayoutProperty =
        AceType::DynamicCast<NavDestinationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navDestinationLayoutProperty);

    float decorBarHeight = 0.0f;
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(hostNode->GetNavigationNode());
    if (navigationNode) {
        auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
        auto navDestinationPattern = hostNode->GetPattern<NavDestinationPattern>();
        if (navigationPattern && navDestinationPattern) {
            auto toolbarManager = navigationPattern->GetToolBarManager();
            auto barStyle = navDestinationPattern->GetTitleBarStyle().value_or(BarStyle::STANDARD);
            if (toolbarManager && toolbarManager->GetIsMoveUp() && barStyle == BarStyle::STACK) {
                decorBarHeight = static_cast<float>(toolbarManager->GetTitleHeight().ConvertToPx());
            }
        }
    }
    float titlebarHeight = LayoutTitleBar(layoutWrapper, hostNode, navDestinationLayoutProperty, decorBarHeight);
    auto resetTitleBarHeight = TransferBarHeight(hostNode, titlebarHeight, true);
    LayoutContent(layoutWrapper, hostNode, navDestinationLayoutProperty, resetTitleBarHeight);
    float toolbarHeight = NavigationLayoutUtil::LayoutToolBar(
        layoutWrapper, hostNode, navDestinationLayoutProperty, true);
    NavigationLayoutUtil::LayoutToolBarDivider(
        layoutWrapper, hostNode, navDestinationLayoutProperty, toolbarHeight, true);
    auto&& opts = navDestinationLayoutProperty->GetSafeAreaExpandOpts();
    if (opts) {
        auto geometryNode = hostNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        TAG_LOGD(AceLogTag::ACE_NAVIGATION,
            "Navdestination id is %{public}d, frameRect is %{public}s",
            hostNode->GetId(), geometryNode->GetFrameRect().ToString().c_str());
    }
    LayoutOverlay(hostNode);
}

void NavDestinationLayoutAlgorithm::MeasureAdaptiveLayoutChildren(
    LayoutWrapper* layoutWrapper, SizeF& realSize, float titleBarHeight, float toolBarHeight)
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navDestinationLayoutPropety =
        AceType::DynamicCast<NavDestinationLayoutPropertyBase>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navDestinationLayoutPropety);
    auto contentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
    CHECK_NULL_VOID(contentNode);
    auto parent = AceType::DynamicCast<FrameNode>(hostNode->GetParent());
    CHECK_NULL_VOID(parent);
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty->IsIgnoreOptsValid());
    IgnoreLayoutSafeAreaOpts& opts = *(contentLayoutProperty->GetIgnoreLayoutSafeAreaOpts());

    auto isVerticalCanExtend = NavigationLayoutUtil::CheckVerticalExtend(navDestinationLayoutPropety, hostNode, opts);
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

    auto childConstraint = navDestinationLayoutPropety->CreateChildConstraint();
    childConstraint.selfIdealSize.SetSize(realSize);
    contentNode->GetGeometryNode()->SetParentLayoutConstraint(childConstraint);
    IgnoreLayoutSafeAreaBundle bundle;
    bundle.second = hostNode;
    bundle.first.emplace_back(AceType::DynamicCast<FrameNode>(hostNode->GetContentNode()));
    auto context = hostNode->GetContextWithCheck();
    CHECK_NULL_VOID(context);
    contentNode->SetDelaySelfLayoutForIgnore();
    hostNode->SetDelaySelfLayoutForIgnore();
    context->AddIgnoreLayoutSafeAreaBundle(std::move(bundle));
}

void NavDestinationLayoutAlgorithm::ReCalcNavDestinationSize(LayoutWrapper* layoutWrapper, SizeF& size)
{
    auto navDestinationLayoutProperty =
        AceType::DynamicCast<NavDestinationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    const auto& padding = navDestinationLayoutProperty->CreatePaddingAndBorder();

    if (NearZero(size.Height())) {
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
} // namespace OHOS::Ace::NG