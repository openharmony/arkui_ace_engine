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

#include "core/components_ng/pattern/navigation/navigation_layout_algorithm.h"

#include "core/components_ng/pattern/navigation/navigation_layout_util.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

constexpr static float HALF = 0.5f;
constexpr static int32_t PLATFORM_VERSION_TEN = 10;
constexpr Dimension WINDOW_WIDTH = 520.0_vp;

namespace {
constexpr NavigationMode INITIAL_MODE = NavigationMode::AUTO;
constexpr int32_t MODE_SWITCH_ANIMATION_DURATION = 500; // ms
const RefPtr<CubicCurve> MODE_SWITCH_CURVE = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.2f, 0.1f, 1.0f);
constexpr Dimension DIVIDER_DRAG_BAR_WIDTH = 12.0_vp;
constexpr Dimension DIVIDER_DRAG_BAR_HEIGHT = 48.0_vp;
constexpr Dimension DRAG_BAR_ITEM_WIDTH = 2.0_vp;
constexpr Dimension DRAG_BAR_ITEM_HEIGHT = 24.0_vp;

bool IsNavBarVisible(const RefPtr<NavigationGroupNode>& navigation)
{
    CHECK_NULL_RETURN(navigation, false);
    auto navBar = AceType::DynamicCast<FrameNode>(navigation->GetNavBarNode());
    CHECK_NULL_RETURN(navBar, false);
    auto navBarProperty = navBar->GetLayoutProperty();
    CHECK_NULL_RETURN(navBarProperty, false);
    return navBarProperty->GetVisibilityValue(VisibleType::INVISIBLE) == VisibleType::VISIBLE;
}

void MeasureDivider(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& dividerSize)
{
    auto dividerNode = hostNode->GetDividerNode();
    CHECK_NULL_VOID(dividerNode);
    auto index = hostNode->GetChildIndexById(dividerNode->GetId());
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(dividerWrapper);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    constraint.selfIdealSize = OptionalSizeF(dividerSize.Width(), dividerSize.Height());
    dividerWrapper->Measure(constraint);
}

void MeasureSplitPlaceholder(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& splitPlaceholderSize)
{
    auto splitPlaceholder = hostNode->GetPlaceholderContentNode();
    CHECK_NULL_VOID(splitPlaceholder);
    auto index = hostNode->GetChildIndexById(splitPlaceholder->GetId());
    auto splitPlaceholderWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(splitPlaceholderWrapper);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    auto placeholderLayoutProperty = AceType::DynamicCast<FrameNode>(splitPlaceholder)->GetLayoutProperty();
    CHECK_NULL_VOID(placeholderLayoutProperty);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_VOID(navigationStack);
    bool isHideNavBar = navigationLayoutProperty->GetHideNavBar().value_or(false);
    // cases that require measure of placeholder content
    // 1. navigation stack is empty
    // 2. navigation mode is SPLIT
    // 3. navBar is not hidden
    if (navigationStack->Empty() && navigationPattern->GetNavigationMode() == NavigationMode::SPLIT && !isHideNavBar) {
        placeholderLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        if (NavigationLayoutAlgorithm::IsAutoHeight(navigationLayoutProperty)) {
            constraint.selfIdealSize.SetWidth(splitPlaceholderSize.Width());
        } else {
            constraint.selfIdealSize = OptionalSizeF(splitPlaceholderSize.Width(), splitPlaceholderSize.Height());
        }
    } else {
        placeholderLayoutProperty->UpdateVisibility(VisibleType::GONE);
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
    }
    splitPlaceholderWrapper->Measure(constraint);
}

void MeasureDragBar(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& dividerSize)
{
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    auto dragNode = hostNode->GetDragBarNode();
    CHECK_NULL_VOID(dragNode);
    auto index = hostNode->GetChildIndexById(dragNode->GetId());
    auto dargWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(dargWrapper);
    auto dragBarItem = AceType::DynamicCast<FrameNode>(dragNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(dragBarItem);
    auto dragBarItemLayoutProperty = dragBarItem->GetLayoutProperty();
    CHECK_NULL_VOID(dragBarItemLayoutProperty);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    if (NearZero(dividerSize.Width()) || !navigationPattern->GetEnableDragBar()) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        dragBarItemLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(0.0f), CalcLength(0.0f)));
    } else {
        constraint.selfIdealSize = OptionalSizeF(static_cast<float>(DIVIDER_DRAG_BAR_WIDTH.ConvertToPx()),
            static_cast<float>(DIVIDER_DRAG_BAR_HEIGHT.ConvertToPx()));
        dragBarItemLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(DRAG_BAR_ITEM_WIDTH), CalcLength(DRAG_BAR_ITEM_HEIGHT)));
    }
    dargWrapper->Measure(constraint);
}

void LayoutDragBar(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, float navBarWidth, const NavBarPosition& position)
{
    auto dargNode = hostNode->GetDragBarNode();
    CHECK_NULL_VOID(dargNode);
    auto index = hostNode->GetChildIndexById(dargNode->GetId());
    auto dargWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(dargWrapper);
    auto geometryNode = dargWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto navigationGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(navigationGeometryNode);
    auto navigationWidth = navigationGeometryNode->GetFrameSize().Width();
    auto navigationHeight = navigationGeometryNode->GetFrameSize().Height();
    auto offsetX = navBarWidth - geometryNode->GetFrameSize().Width() * HALF;
    auto offsetY = navigationHeight * HALF - geometryNode->GetFrameSize().Height() * HALF;
    OffsetT<float> dragOffset = OffsetT<float>(offsetX, offsetY);
    bool isNavBarInRight = (position == NavBarPosition::END && !AceApplicationInfo::GetInstance().IsRightToLeft()) ||
        (position == NavBarPosition::START && AceApplicationInfo::GetInstance().IsRightToLeft());
    if (isNavBarInRight) {
        dragOffset.SetX(navigationWidth - navBarWidth - geometryNode->GetFrameSize().Width() * HALF);
    }
    const auto& padding = navigationLayoutProperty->CreatePaddingAndBorder();
    dragOffset.AddX(padding.left.value_or(0.0f));
    dragOffset.AddY(padding.top.value_or(0.0f));
    geometryNode->SetMarginFrameOffset(dragOffset);
    dargWrapper->Layout();
}

float LayoutPrimaryContentNode(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty)
{
    CHECK_NULL_RETURN(hostNode, 0.0f);
    auto primaryContentNode = hostNode->GetPrimaryContentNode();
    CHECK_NULL_RETURN(primaryContentNode, 0.0f);
    auto navigationGeometryNode = layoutWrapper->GetGeometryNode();
    bool isNavBarInRight = AceApplicationInfo::GetInstance().IsRightToLeft();
    const auto& padding = navigationLayoutProperty->CreatePaddingAndBorder();
    auto index = hostNode->GetChildIndexById(primaryContentNode->GetId());
    auto nodeWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(nodeWrapper, 0.0f);
    auto geometryNode = nodeWrapper->GetGeometryNode();
    auto nodeOffset = OffsetT<float>(0.0f, 0.0f);
    if (isNavBarInRight) {
        nodeOffset.SetX(navigationGeometryNode->GetFrameSize().Width() - geometryNode->GetFrameSize().Width());
    }
    nodeOffset.AddX(padding.left.value_or(0.0f));
    nodeOffset.AddY(padding.top.value_or(0.0f));
    geometryNode->SetMarginFrameOffset(nodeOffset);
    nodeWrapper->Layout();
    return geometryNode->GetFrameSize().Width();
}

float LayoutNavBarOrHomeDestination(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, NavBarPosition position,
    OffsetF& returnNavBarOffset)
{
    CHECK_NULL_RETURN(hostNode, 0.0f);
    auto navigationPattern = hostNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(navigationPattern, 0.0f);
    auto targetNode = AceType::DynamicCast<FrameNode>(hostNode->GetNavBarOrHomeDestinationNode());
    CHECK_NULL_RETURN(targetNode, 0.0f);
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_RETURN(contentNode, 0.0f);
    auto index = hostNode->GetChildIndexById(targetNode->GetId());
    auto targetNodeWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(targetNodeWrapper, 0.0f);
    auto geometryNode = targetNodeWrapper->GetGeometryNode();
    auto navigationGeometryNode = layoutWrapper->GetGeometryNode();
    auto navBarOffset = OffsetT<float>(0.0f, 0.0f);
    bool isNavBarInRight = (position == NavBarPosition::END && !AceApplicationInfo::GetInstance().IsRightToLeft()) ||
        (position == NavBarPosition::START && AceApplicationInfo::GetInstance().IsRightToLeft());
    bool isHideNavBar = navigationLayoutProperty->GetHideNavBar().value_or(false);
    NavigationMode navigationMode = navigationPattern->GetNavigationMode();
    if (isNavBarInRight && !isHideNavBar && navigationMode == NavigationMode::SPLIT) {
        // only in SPLIT mode can navBar show on the left or right side of navigation, otherwise it is centered.
        navBarOffset.SetX(navigationGeometryNode->GetFrameSize().Width() - geometryNode->GetFrameSize().Width());
    }
    const auto& padding = navigationLayoutProperty->CreatePaddingAndBorder();
    navBarOffset.AddX(padding.left.value_or(0.0f));
    navBarOffset.AddY(padding.top.value_or(0.0f));
    geometryNode->SetMarginFrameOffset(navBarOffset);
    targetNodeWrapper->Layout();
    returnNavBarOffset = navBarOffset;
    return isHideNavBar && navigationMode == NavigationMode::SPLIT ? 0.0f : geometryNode->GetFrameSize().Width();
}

float LayoutDivider(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, float navBarWidth, const NavBarPosition& position)
{
    auto dividerNode = hostNode->GetDividerNode();
    CHECK_NULL_RETURN(dividerNode, 0.0f);
    auto index = hostNode->GetChildIndexById(dividerNode->GetId());
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(dividerWrapper, 0.0f);
    auto geometryNode = dividerWrapper->GetGeometryNode();
    auto navigationGeometryNode = layoutWrapper->GetGeometryNode();
    auto dividerOffsetX = navBarWidth;
    if (position == NavBarPosition::END) {
        dividerOffsetX =
            navigationGeometryNode->GetFrameSize().Width() - geometryNode->GetFrameSize().Width() - dividerOffsetX;
    }
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        dividerOffsetX =
            navigationGeometryNode->GetFrameSize().Width() - geometryNode->GetFrameSize().Width() - dividerOffsetX;
    }
    OffsetT<float> dividerOffset = OffsetT<float>(dividerOffsetX, 0.0f);
    const auto& padding = navigationLayoutProperty->CreatePaddingAndBorder();
    dividerOffset.AddX(padding.left.value_or(0));
    dividerOffset.AddY(padding.top.value_or(0));
    geometryNode->SetMarginFrameOffset(dividerOffset);
    dividerWrapper->Layout();
    return geometryNode->GetFrameSize().Width();
}

void LayoutContent(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, float navBarWidth, float dividerWidth,
    const NavBarPosition& position)
{
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto index = hostNode->GetChildIndexById(contentNode->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(contentWrapper);
    auto geometryNode = contentWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    auto contentChildSize = contentNode->GetChildren().size();

    if (pattern->IsForceSplitSuccess()) {
        auto contentOffset = OffsetT<float>(0.0f, 0.0f);
        if (!AceApplicationInfo::GetInstance().IsRightToLeft()) {
            contentOffset = OffsetF(navBarWidth + dividerWidth, 0.0f);
        }
        const auto& padding = navigationLayoutProperty->CreatePaddingAndBorder();
        contentOffset.AddX(padding.left.value_or(0));
        contentOffset.AddY(padding.top.value_or(0));
        geometryNode->SetMarginFrameOffset(contentOffset);
        contentWrapper->Layout();
        return;
    }

    // cases that content layouts from start
    // 1. displaying content pages in STACK mode
    // 2. placing navBar at the end
    // 3. hiding navBar in SPLIT mode
    auto contentOffset = OffsetT<float>(0.0f, 0.0f);
    if ((contentChildSize != 0 && navigationPattern->GetNavigationMode() == NavigationMode::STACK) ||
        position == NavBarPosition::END ||
        (navigationLayoutProperty->GetHideNavBar().value_or(false) &&
            navigationPattern->GetNavigationMode() == NavigationMode::SPLIT)) {
        if (AceApplicationInfo::GetInstance().IsRightToLeft() &&
            navigationPattern->GetNavigationMode() == NavigationMode::SPLIT) {
            contentOffset = OffsetT<float>(navBarWidth + dividerWidth, 0.0f);
        }
        const auto& padding = navigationLayoutProperty->CreatePaddingAndBorder();
        contentOffset.AddX(padding.left.value_or(0));
        contentOffset.AddY(padding.top.value_or(0));
        geometryNode->SetMarginFrameOffset(contentOffset);
        contentWrapper->Layout();
        return;
    }
    if (!AceApplicationInfo::GetInstance().IsRightToLeft()) {
        contentOffset = OffsetT<float>(navBarWidth + dividerWidth, 0.0f);
    }
    const auto& padding = navigationLayoutProperty->CreatePaddingAndBorder();
    contentOffset.AddX(padding.left.value_or(0));
    contentOffset.AddY(padding.top.value_or(0));
    geometryNode->SetMarginFrameOffset(contentOffset);
    contentWrapper->Layout();
}

void LayoutSplitPalceholderContent(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, float splitPlaceholderOffsetX,
    const NavBarPosition& position)
{
    CHECK_NULL_VOID(hostNode);
    auto splitPlaceholder = hostNode->GetPlaceholderContentNode();
    CHECK_NULL_VOID(splitPlaceholder);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_VOID(navigationStack);
    bool isHideNavBar = navigationLayoutProperty->GetHideNavBar().value_or(false);
    // cases that require layout of placeholder content
    // 1. navigation stack is empty
    // 2. navigation mode is SPLIT
    // 3. navBar is not hidden
    if (navigationStack->Empty() && navigationPattern->GetNavigationMode() == NavigationMode::SPLIT && !isHideNavBar) {
        bool isNavBarInRight =
            (position == NavBarPosition::END && !AceApplicationInfo::GetInstance().IsRightToLeft()) ||
            (position == NavBarPosition::START && AceApplicationInfo::GetInstance().IsRightToLeft());
        auto index = hostNode->GetChildIndexById(splitPlaceholder->GetId());
        auto splitPlaceholderWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(splitPlaceholderWrapper);
        auto splitPlaceholderGeometryNode = splitPlaceholderWrapper->GetGeometryNode();
        CHECK_NULL_VOID(splitPlaceholderGeometryNode);
        if (isNavBarInRight) {
            splitPlaceholderOffsetX = 0.0f;
        }
        auto splitPlaceholderOffset = OffsetT<float>(splitPlaceholderOffsetX, 0.0f);
        const auto& padding = navigationLayoutProperty->CreatePaddingAndBorder();
        splitPlaceholderOffset.AddX(padding.left.value_or(0));
        splitPlaceholderOffset.AddY(padding.top.value_or(0));
        splitPlaceholderGeometryNode->SetMarginFrameOffset(splitPlaceholderOffset);
        splitPlaceholderWrapper->Layout();
    }
}

void FitScrollFullWindow(SizeF& frameSize)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (frameSize.Width() == Infinity<float>()) {
        frameSize.SetWidth(pipeline->GetRootWidth());
    }
    if (frameSize.Height() == Infinity<float>()) {
        frameSize.SetHeight(pipeline->GetRootHeight());
    }
}

void SwitchModeWithAnimation(const RefPtr<NavigationGroupNode>& hostNode)
{
    CHECK_NULL_VOID(hostNode);
    hostNode->SetDoingModeSwitchAnimationFlag(true);
    hostNode->SetNeedSetInvisible(false);
    AnimationOption option;
    option.SetCurve(MODE_SWITCH_CURVE);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(MODE_SWITCH_ANIMATION_DURATION);
    option.SetOnFinishEvent([weakHost = WeakPtr<NavigationGroupNode>(hostNode)]() {
        auto hostNode = weakHost.Upgrade();
        CHECK_NULL_VOID(hostNode);
        hostNode->ReduceModeSwitchAnimationCnt();
        if (hostNode->GetModeSwitchAnimationCnt() == 0) {
            auto dividerNode = AceType::DynamicCast<FrameNode>(hostNode->GetDividerNode());
            CHECK_NULL_VOID(dividerNode);
            auto layoutProperty = dividerNode->GetLayoutProperty();
            CHECK_NULL_VOID(layoutProperty);
            layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            auto pattern = hostNode->GetPattern<NavigationPattern>();
            CHECK_NULL_VOID(pattern);
            auto lastStandardIndex = hostNode->GetLastStandardIndex();
            auto navigationLayoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
            CHECK_NULL_VOID(navigationLayoutProperty);
            bool navbarIsHidden = (pattern->GetNavigationMode() == NavigationMode::STACK && lastStandardIndex >= 0) ||
                                  navigationLayoutProperty->GetHideNavBar().value_or(false);
            hostNode->SetNeedSetInvisible(navbarIsHidden);
            hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    });
    AnimationUtils::Animate(option, [weakHost = WeakPtr<NavigationGroupNode>(hostNode)]() {
        auto hostNode = weakHost.Upgrade();
        CHECK_NULL_VOID(hostNode);
        auto dividerNode = AceType::DynamicCast<FrameNode>(hostNode->GetDividerNode());
        CHECK_NULL_VOID(dividerNode);
        auto layoutProperty = dividerNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        hostNode->IncreaseModeSwitchAnimationCnt();
        hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        hostNode->GetContext()->FlushUITasks();
        hostNode->SetDoingModeSwitchAnimationFlag(false);
    }, option.GetOnFinishEvent(), nullptr /* repeatCallback */, hostNode->GetContextRefPtr());
}

} // namespace

void NavigationLayoutAlgorithm::LayoutForceSplitPlaceHolderNode(
    LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, float navBarWidth, float dividerWidth)
{
    auto phNode = AceType::DynamicCast<FrameNode>(hostNode->GetForceSplitPlaceHolderNode());
    CHECK_NULL_VOID(phNode);
    auto index = hostNode->GetChildIndexById(phNode->GetId());
    auto phWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(phWrapper);
    auto geometryNode = phWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto phOffset = OffsetT<float>(0.0f, 0.0f);
    if (!AceApplicationInfo::GetInstance().IsRightToLeft()) {
        phOffset = OffsetF(navBarWidth + dividerWidth, 0.0f);
    }
    const auto& padding = navigationLayoutProperty->CreatePaddingAndBorder();
    phOffset.AddX(padding.left.value_or(0));
    phOffset.AddY(padding.top.value_or(0));
    geometryNode->SetMarginFrameOffset(phOffset);
    phWrapper->Layout();
}

bool NavigationLayoutAlgorithm::IsAutoHeight(const RefPtr<LayoutProperty>& layoutProperty)
{
    CHECK_NULL_RETURN(layoutProperty, false);
    auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (!calcLayoutConstraint || !calcLayoutConstraint->selfIdealSize.has_value() ||
        !calcLayoutConstraint->selfIdealSize->Height().has_value() ||
        (calcLayoutConstraint->selfIdealSize->Height().value().ToString().find("auto") == std::string::npos)) {
        return false;
    }
    return true;
}

void NavigationLayoutAlgorithm::RangeCalculation(
    const RefPtr<NavigationGroupNode>& hostNode, const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty)
{
    const auto& constraint = navigationLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto parentSize = CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    auto frameSize = parentSize.ConvertToSizeT();
    float frameSizeWidth = frameSize.Width();
    Dimension defaultValue = Dimension(-1.0);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    minContentWidthValue_ = navigationLayoutProperty->GetMinContentWidthValue(defaultValue);
    if (minContentWidthValue_ == defaultValue) {
        userSetMinContentFlag_ = false;
        minContentWidthValue_ = DEFAULT_MIN_CONTENT_WIDTH;
    } else {
        userSetMinContentFlag_ = true;
    }
    minNavBarWidthValue_ = navigationLayoutProperty->GetMinNavBarWidthValue(DEFAULT_MIN_NAV_BAR_WIDTH);
    auto userSetMaxNavBarWidthValue = navigationLayoutProperty->GetMaxNavBarWidthValue(defaultValue);

    float minNavBarWidth =
        std::min(static_cast<float>(minNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f))),
            frameSizeWidth);
    float maxNavBarWidth = 0.0f;
    if (userSetMaxNavBarWidthValue == defaultValue) {
        userSetNavBarRangeFlag_ = false;
        maxNavBarWidth = std::min(
            static_cast<float>(DEFAULT_MAX_NAV_BAR_WIDTH.ConvertToPx()), frameSizeWidth * MAX_NAV_BAR_WIDTH_SCALE);
    } else {
        userSetNavBarRangeFlag_ = true;
        maxNavBarWidth =
            static_cast<float>(userSetMaxNavBarWidthValue.ConvertToPxWithSize(parentSize.Width().value_or(0.0f)));
    }
    maxNavBarWidthValue_ = Dimension(Dimension(std::max(maxNavBarWidth, minNavBarWidth)).ConvertToVp(),
        DimensionUnit::VP);
    auto currentPlatformVersion = pipeline->GetMinPlatformVersion();
    if (currentPlatformVersion >= PLATFORM_VERSION_TEN) {
        auto minNavBarWidth = minNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
        auto maxNavBarWidth = maxNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
        realNavBarWidth_ = std::max(realNavBarWidth_, static_cast<float>(minNavBarWidth));
        realNavBarWidth_ = std::min(realNavBarWidth_, static_cast<float>(maxNavBarWidth));
    }
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    navigationPattern->SetMinNavBarWidthValue(minNavBarWidthValue_);
    navigationPattern->SetMaxNavBarWidthValue(maxNavBarWidthValue_);
    navigationPattern->SetMinContentWidthValue(minContentWidthValue_);
    navigationPattern->SetUserSetNavBarRangeFlag(userSetNavBarRangeFlag_);
    navigationPattern->SetUserSetMinContentFlag(userSetMinContentFlag_);
}

void NavigationLayoutAlgorithm::GetRange(const RefPtr<NavigationGroupNode>& hostNode)
{
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    minNavBarWidthValue_ = navigationPattern->GetMinNavBarWidthValue();
    maxNavBarWidthValue_ = navigationPattern->GetMaxNavBarWidthValue();
    minContentWidthValue_ = navigationPattern->GetMinContentWidthValue();
    userSetNavBarRangeFlag_ = navigationPattern->GetUserSetNavBarRangeFlag();
    userSetMinContentFlag_ = navigationPattern->GetUserSetMinContentFlag();
    userSetNavBarWidthFlag_ = navigationPattern->GetUserSetNavBarWidthFlag();
}

float NavigationLayoutAlgorithm::CalculateNavigationWidth(const RefPtr<NavigationGroupNode>& hostNode)
{
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(hostNode->GetLayoutProperty());
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto currentPlatformVersion = pipeline->GetMinPlatformVersion();
    auto navigationWidth = 0.0f;
    if (currentPlatformVersion >= PLATFORM_VERSION_TEN) {
        CHECK_NULL_RETURN(navigationLayoutProperty, navigationWidth);
        const auto& constraint = navigationLayoutProperty->GetLayoutConstraint();
        auto parentSize = CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
        auto minNavBarWidth = minNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
        navigationWidth = static_cast<float>(minNavBarWidth + minContentWidthValue_.ConvertToPx());
    } else {
        navigationWidth = static_cast<float>(WINDOW_WIDTH.ConvertToPx());
    }
    return navigationWidth;
}

void NavigationLayoutAlgorithm::UpdateNavigationMode(const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty,
    const SizeF& frameSize, const RefPtr<NavigationGroupNode>& hostNode)
{
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto usrNavigationMode = navigationLayoutProperty->GetUsrNavigationModeValue(NavigationMode::AUTO);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    if (navigationPattern->IsForceSplitSuccess()) {
        usrNavigationMode = NavigationMode::SPLIT;
    }
    if (usrNavigationMode == NavigationMode::AUTO) {
        if (frameSize.Width() >= CalculateNavigationWidth(hostNode)) {
            usrNavigationMode = NavigationMode::SPLIT;
            auto targetNode = hostNode->GetNavBarOrHomeDestinationNode();
            if (targetNode) {
                targetNode->SetJSViewActive(true);
            }
        } else {
            usrNavigationMode = NavigationMode::STACK;
        }
    }
    bool modeChange = navigationPattern->GetNavigationMode() != usrNavigationMode;
    bool isFirstTimeLayout = (navigationPattern->GetNavigationMode() == INITIAL_MODE);
    bool enableModeChangeAnimation = navigationLayoutProperty->GetEnableModeChangeAnimation().value_or(true);
    bool doModeSwitchAnimationInAnotherTask =
        enableModeChangeAnimation && modeChange && !isFirstTimeLayout && !hostNode->IsOnModeSwitchAnimation();
    if (doModeSwitchAnimationInAnotherTask) {
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        if (container->IsFoldable()) {
            // If screen-fold-state changed, no need to do mode switch animation.
            // Only when navigation-mode changed, it is necessary to update the current screen-fold-state.
            doModeSwitchAnimationInAnotherTask =
                !navigationPattern->JudgeFoldStateChangeAndUpdateState() && doModeSwitchAnimationInAnotherTask;
        }
    }
    if (!doModeSwitchAnimationInAnotherTask) {
        navigationPattern->SetNavigationMode(usrNavigationMode);
        navigationPattern->SetNavigationModeChange(modeChange);
    }

    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([weakNavigationPattern = WeakPtr<NavigationPattern>(navigationPattern),
        modeChange, doModeSwitchAnimationInAnotherTask]() {
        auto navigationPattern = weakNavigationPattern.Upgrade();
        CHECK_NULL_VOID(navigationPattern);
        if (doModeSwitchAnimationInAnotherTask) {
            navigationPattern->OnNavBarStateChange(false);
            SwitchModeWithAnimation(AceType::DynamicCast<NavigationGroupNode>(navigationPattern->GetHost()));
        } else {
            if (navigationPattern->IsHomeDestinationVisible()) {
                navigationPattern->FireHomeDestinationLifeCycleIfNeeded(NavDestinationLifecycle::ON_SHOW, true);
                navigationPattern->FireHomeDestinationLifeCycleIfNeeded(NavDestinationLifecycle::ON_ACTIVE, true);
            } else {
                navigationPattern->FireHomeDestinationLifeCycleIfNeeded(NavDestinationLifecycle::ON_INACTIVE, true);
                navigationPattern->FireHomeDestinationLifeCycleIfNeeded(NavDestinationLifecycle::ON_HIDE, true);
            }
            navigationPattern->OnNavBarStateChange(modeChange);
            navigationPattern->OnNavigationModeChange(modeChange);
        }
    });
}

void NavigationLayoutAlgorithm::SizeCalculationForForceSplit(
    LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& frameSize)
{
    auto dividerWidth = static_cast<float>(DIVIDER_WIDTH.ConvertToPx());
    dividerSize_ = SizeF(dividerWidth, frameSize.Height());
    auto halfWidth = (frameSize.Width() - dividerWidth) / 2.0f;
    navBarSize_ = SizeF(halfWidth, frameSize.Height());
    primaryNodeSize_ = SizeF(halfWidth, frameSize.Height());
    contentSize_ = SizeF(halfWidth, frameSize.Height());
    realNavBarWidth_ = halfWidth;
    realContentWidth_ = halfWidth;
    realDividerWidth_ = halfWidth;
}

void NavigationLayoutAlgorithm::SizeCalculation(LayoutWrapper* layoutWrapper,
    const RefPtr<NavigationGroupNode>& hostNode, const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty,
    const SizeF& frameSize)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto constraint = navigationLayoutProperty->GetLayoutConstraint();
    auto parentSize = CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    auto currentPlatformVersion = pipeline->GetMinPlatformVersion();
    if (currentPlatformVersion >= PLATFORM_VERSION_TEN) {
        auto minNavBarWidth = minNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
        auto maxNavBarWidth = maxNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
        realNavBarWidth_ = std::min(realNavBarWidth_, static_cast<float>(maxNavBarWidth));
        realNavBarWidth_ = std::max(realNavBarWidth_, static_cast<float>(minNavBarWidth));
    } else {
        auto navBarWidthValue = navigationLayoutProperty->GetNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH);
        auto navBarWidth = navBarWidthValue.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
        realNavBarWidth_ = navBarWidth;
    }
    navBarSize_ = frameSize;
    contentSize_ = frameSize;
    dividerSize_ = SizeF(0.0f, frameSize.Height());
    if (navigationPattern->GetNavigationMode() == NavigationMode::SPLIT ||
        (navigationPattern->IsForceSplitSuccess() && navigationPattern->IsForceSplitUseNavBar())) {
        SizeCalculationSplit(hostNode, navigationLayoutProperty, frameSize);
    } else {
        SizeCalculationStack(hostNode, navigationLayoutProperty, frameSize);
    }
}

void NavigationLayoutAlgorithm::SizeCalculationSplit(const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& frameSize)
{
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    float frameWidth = frameSize.Width();
    auto parentSize = CreateIdealSizeByPercentRef(
        navigationLayoutProperty->GetLayoutConstraint().value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    auto navBarWidthValue = navigationLayoutProperty->GetNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH);
    auto userSetNavBarWidth = navBarWidthValue.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    auto dividerWidth = static_cast<float>(DIVIDER_WIDTH.ConvertToPx());
    auto minNavBarWidth = minNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    auto minContentWidth = minContentWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    realContentWidth_ = minContentWidth;

    bool isHideNavbar = navigationLayoutProperty->GetHideNavBar().value_or(false);
    if (pattern->IsForceSplitSuccess() && pattern->IsForceSplitUseNavBar()) {
        dividerSize_.SetWidth(dividerWidth);
        auto halfWidth = (frameSize.Width() - dividerWidth) / 2.0f;
        navBarSize_.SetWidth(halfWidth);
        realNavBarWidth_ = halfWidth;
        realContentWidth_ = halfWidth;
    } else if (isHideNavbar) {
        CHECK_NULL_VOID(hostNode);
        auto targetNode = AceType::DynamicCast<FrameNode>(hostNode->GetNavBarOrHomeDestinationNode());
        CHECK_NULL_VOID(targetNode);
        auto geometryNode = targetNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        navBarSize_.SetWidth(geometryNode->GetFrameSize().Width());
        dividerSize_.SetWidth(0.0f);
        realNavBarWidth_ = 0.0f;
        realContentWidth_ = frameWidth;
    } else {
        CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    }

    realDividerWidth_ = std::max(realDividerWidth_, 0.0f);
    realContentWidth_ = std::max(realContentWidth_, 0.0f);
    realNavBarWidth_ = std::min(realNavBarWidth_, frameWidth);
    realContentWidth_ = std::min(realContentWidth_, frameWidth);
    if (realNavBarWidth_ == 0.0f || realContentWidth_ == 0.0f) {
        realDividerWidth_ = 0.0f;
    } else {
        realDividerWidth_ = dividerWidth;
    }
    if (!isHideNavbar) {
        navBarSize_.SetWidth(realNavBarWidth_);
        dividerSize_.SetWidth(realDividerWidth_);
    }
    contentSize_.SetWidth(realContentWidth_);
}

void NavigationLayoutAlgorithm::CheckSizeInSplit(
    const float frameWidth, const float userSetNavBarWidth, const float minNavBarWidth, const float minContentWidth)
{
    auto dividerWidth = static_cast<float>(DIVIDER_WIDTH.ConvertToPx());

    if (userSetMinContentFlag_ && !userSetNavBarRangeFlag_) {
        if (minContentWidth >= frameWidth) {
            realContentWidth_ = frameWidth;
            realNavBarWidth_ = 0.0f;
        } else if (realNavBarWidth_ + dividerWidth + minContentWidth <= frameWidth) {
            realContentWidth_ = frameWidth - realNavBarWidth_ - dividerWidth;
        } else {
            realContentWidth_ = minContentWidth;
            realNavBarWidth_ = frameWidth - realContentWidth_ - dividerWidth;
        }
    } else if (!userSetNavBarRangeFlag_ && !userSetMinContentFlag_ && userSetNavBarWidthFlag_) {
        realNavBarWidth_ = userSetNavBarWidth;
        realContentWidth_ = frameWidth - realNavBarWidth_ - dividerWidth;
    } else {
        float remainingSpace = frameWidth - realNavBarWidth_ - dividerWidth;
        float remainingMaxSpace = frameWidth - minNavBarWidth - dividerWidth;
        if (remainingSpace >= minContentWidth) {
            realContentWidth_ = remainingSpace;
        } else if (remainingSpace < minContentWidth && remainingMaxSpace > minContentWidth &&
                   realNavBarWidth_ > minNavBarWidth) {
            realContentWidth_ = minContentWidth;
            realNavBarWidth_ = frameWidth - minContentWidth - dividerWidth;
        } else {
            realNavBarWidth_ = minNavBarWidth;
            realContentWidth_ = frameWidth - minNavBarWidth - dividerWidth;
        }
    }
}

void NavigationLayoutAlgorithm::SizeCalculationStack(const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& frameSize)
{
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    realDividerWidth_ = 0.0f;
    float frameWidth = frameSize.Width();
    navBarSize_.SetWidth(frameWidth);
    dividerSize_.SetWidth(realDividerWidth_);
    contentSize_.SetWidth(frameWidth);
    realContentWidth_ = frameWidth;
}

void NavigationLayoutAlgorithm::MeasurePrimaryContentNode(
    LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& primaryNodeSize)
{
    CHECK_NULL_VOID(hostNode);
    auto primaryContentNode = hostNode->GetPrimaryContentNode();
    CHECK_NULL_VOID(primaryContentNode);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    bool isAutoHeight = IsAutoHeight(navigationLayoutProperty);
    auto index = hostNode->GetChildIndexById(primaryContentNode->GetId());
    auto nodeWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(nodeWrapper);
    if (isAutoHeight) {
        nodeWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            navigationLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.value());
        constraint.selfIdealSize.SetWidth(primaryNodeSize.Width());
    } else {
        constraint.selfIdealSize = OptionalSizeF(primaryNodeSize.Width(), primaryNodeSize.Height());
    }
    nodeWrapper->Measure(constraint);
    realNavBarHeight_ = nodeWrapper->GetGeometryNode()->GetFrameSize().Height();
}

void NavigationLayoutAlgorithm::MeasureNavBarOrHomeDestination(
    LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& navBarSize)
{
    CHECK_NULL_VOID(hostNode);
    auto targetNode = AceType::DynamicCast<NavDestinationNodeBase>(hostNode->GetNavBarOrHomeDestinationNode());
    CHECK_NULL_VOID(targetNode);
    auto index = hostNode->GetChildIndexById(targetNode->GetId());
    auto targetNodeWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(targetNodeWrapper);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    if (IsAutoHeight(navigationLayoutProperty)) {
        targetNodeWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            navigationLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.value());
        constraint.selfIdealSize.SetWidth(navBarSize.Width());
    } else {
        constraint.selfIdealSize = OptionalSizeF(navBarSize.Width(), navBarSize.Height());
    }
    auto adjustConstraint = targetNode->AdjustLayoutConstarintIfNeeded(constraint);
    targetNodeWrapper->Measure(adjustConstraint);
    realNavBarHeight_ = targetNodeWrapper->GetGeometryNode()->GetFrameSize().Height();
    realNavBarWidth_ = targetNodeWrapper->GetGeometryNode()->GetFrameSize().Width();
}

void NavigationLayoutAlgorithm::MeasureContentChild(LayoutWrapper* layoutWrapper,
    const RefPtr<NavigationGroupNode>& hostNode, const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty,
    const SizeF& contentSize)
{
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto index = hostNode->GetChildIndexById(contentNode->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(contentWrapper);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    if (contentNode->GetChildren().empty()) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
    } else {
        NavigationLayoutUtil::UpdateConstraintWhenFixOrWrap(navigationLayoutProperty, constraint, contentSize);
    }
    contentWrapper->Measure(constraint);
    realContentHeight_ = contentWrapper->GetGeometryNode()->GetFrameSize().Height();
    realContentWidth_ = contentWrapper->GetGeometryNode()->GetFrameSize().Width();
}

void NavigationLayoutAlgorithm::MeasureForceSplitPlaceHolderNode(
    LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& phSize)
{
    auto phNode = AceType::DynamicCast<FrameNode>(hostNode->GetForceSplitPlaceHolderNode());
    CHECK_NULL_VOID(phNode);
    auto phProperty = phNode->GetLayoutProperty();
    CHECK_NULL_VOID(phProperty);
    auto index = hostNode->GetChildIndexById(phNode->GetId());
    auto phWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(phWrapper);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    if (phProperty->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
    } else {
        if (IsAutoHeight(navigationLayoutProperty)) {
            constraint.selfIdealSize.SetWidth(phSize.Width());
        } else {
            constraint.selfIdealSize = OptionalSizeF(phSize.Width(), phSize.Height());
        }
    }
    phWrapper->Measure(constraint);
}

void NavigationLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navigationLayoutProperty);
    const auto& constraint = navigationLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    auto size =
        CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT).ConvertToSizeT();
    FitScrollFullWindow(size);
    pattern->SetNavigationSize(size);

    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);

    pattern->TryForceSplitIfNeeded(size);
    if (ifNeedInit_) {
        RangeCalculation(hostNode, navigationLayoutProperty);
    }
    if (size.Width() == 0.0f) {
        auto layoutAlgorithm = layoutWrapper->GetLayoutAlgorithm();
        if (layoutAlgorithm) {
            layoutAlgorithm->SetSkipLayout();
        }
        return;
    }
    GetRange(hostNode);
    UpdateNavigationMode(navigationLayoutProperty, size, hostNode);

    if (pattern->IsForceSplitSuccess() && !pattern->IsForceSplitUseNavBar()) {
        SizeCalculationForForceSplit(layoutWrapper, hostNode, navigationLayoutProperty, size);
        if (IsNavBarVisible(hostNode)) {
            MeasureNavBarOrHomeDestination(layoutWrapper, hostNode, navigationLayoutProperty, navBarSize_);
        }
        MeasurePrimaryContentNode(layoutWrapper, hostNode, navigationLayoutProperty, primaryNodeSize_);
    } else {
        SizeCalculation(layoutWrapper, hostNode, navigationLayoutProperty, size);
        MeasureNavBarOrHomeDestination(layoutWrapper, hostNode, navigationLayoutProperty, navBarSize_);
    }
    if (pattern->IsForceSplitSuccess()) {
        MeasureForceSplitPlaceHolderNode(layoutWrapper, hostNode, navigationLayoutProperty, contentSize_);
    }

    MeasureContentChild(layoutWrapper, hostNode, navigationLayoutProperty, contentSize_);
    MeasureDivider(layoutWrapper, hostNode, navigationLayoutProperty, dividerSize_);
    MeasureDragBar(layoutWrapper, hostNode, navigationLayoutProperty, dividerSize_);
    MeasureSplitPlaceholder(layoutWrapper, hostNode, navigationLayoutProperty, contentSize_);
    
    ReCalcNavigationSize(layoutWrapper, size);
}

void NavigationLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto layoutAlgorithm = layoutWrapper->GetLayoutAlgorithm();
    if (layoutAlgorithm && layoutAlgorithm->SkipLayout()) {
        return;
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navigationLayoutProperty);

    NavBarPosition navBarPosition = NavBarPosition::START;
    float navBarOrPrimarNodeWidth = 0.0f;
    if (pattern->IsForceSplitSuccess() && !pattern->IsForceSplitUseNavBar()) {
        if (IsNavBarVisible(hostNode)) {
            OffsetF navBarOffset(0.0, 0.0);
            LayoutNavBarOrHomeDestination(
                layoutWrapper, hostNode, navigationLayoutProperty, navBarPosition, navBarOffset);
        }
        navBarOrPrimarNodeWidth = LayoutPrimaryContentNode(layoutWrapper, hostNode, navigationLayoutProperty);
    } else {
        navBarPosition = pattern->IsForceSplitUseNavBar() ? NavBarPosition::START :
            navigationLayoutProperty->GetNavBarPositionValue(NavBarPosition::START);
        OffsetF navBarOffset(0.0, 0.0);
        navBarOrPrimarNodeWidth = LayoutNavBarOrHomeDestination(
            layoutWrapper, hostNode, navigationLayoutProperty, navBarPosition, navBarOffset);
    }

    float dividerWidth = LayoutDivider(
        layoutWrapper, hostNode, navigationLayoutProperty, navBarOrPrimarNodeWidth, navBarPosition);
    auto splitPlaceholderOffsetX = navBarOrPrimarNodeWidth + dividerWidth;
    LayoutSplitPalceholderContent(
        layoutWrapper, hostNode, navigationLayoutProperty, splitPlaceholderOffsetX, navBarPosition);
    LayoutContent(
        layoutWrapper, hostNode, navigationLayoutProperty, navBarOrPrimarNodeWidth, dividerWidth, navBarPosition);
    LayoutDragBar(layoutWrapper, hostNode, navigationLayoutProperty, navBarOrPrimarNodeWidth, navBarPosition);
    if (pattern->IsForceSplitSuccess()) {
        LayoutForceSplitPlaceHolderNode(
            layoutWrapper, hostNode, navigationLayoutProperty, navBarOrPrimarNodeWidth, dividerWidth);
    }

    auto&& opts = navigationLayoutProperty->GetSafeAreaExpandOpts();
    if (opts) {
        auto geometryNode = hostNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        TAG_LOGD(AceLogTag::ACE_NAVIGATION,
            "Navigation id is %{public}d, frameRect is %{public}s",
            hostNode->GetId(), geometryNode->GetFrameRect().ToString().c_str());
    }
}

void NavigationLayoutAlgorithm::SetNavigationHeight(LayoutWrapper* layoutWrapper, SizeF& size)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_VOID(navigationStack);
    if (navigationStack->Empty()) {
        size.SetHeight(realNavBarHeight_);
    } else if (navigationPattern->GetNavigationMode() == NavigationMode::STACK) {
        size.SetHeight(realContentHeight_);
    } else if (navigationPattern->GetNavigationMode() == NavigationMode::SPLIT) {
        float navHeight = std::max(realContentHeight_, realNavBarHeight_);
        size.SetHeight(navHeight);
    }
}

void NavigationLayoutAlgorithm::SetNavigationWidth(LayoutWrapper* layoutWrapper, SizeF& size)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_VOID(navigationStack);
    auto navigationLayoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    if (navigationStack->Empty()) {
        size.SetWidth(realNavBarWidth_);
    } else if (navigationPattern->GetNavigationMode() == NavigationMode::STACK) {
        size.SetWidth(realContentWidth_);
    } else if (navigationPattern->GetNavigationMode() == NavigationMode::SPLIT) {
        float navWidth = realContentWidth_ + realNavBarWidth_;
        size.SetWidth(navWidth);
        size.AddWidth(realDividerWidth_);
    }
}

void NavigationLayoutAlgorithm::ReCalcNavigationSize(LayoutWrapper* layoutWrapper, SizeF& size)
{
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navigationLayoutProperty);
    const auto& padding = navigationLayoutProperty->CreatePaddingAndBorder();

    auto layoutPolicy = navigationLayoutProperty->GetLayoutPolicyProperty();
    bool isHeightWrapOrFix =
        layoutPolicy.has_value() ? (layoutPolicy->IsHeightWrap() || layoutPolicy->IsHeightFix()) : false;
    bool isWidthWrapOrFix =
        layoutPolicy.has_value() ? (layoutPolicy->IsWidthWrap() || layoutPolicy->IsWidthFix()) : false;
    if (IsAutoHeight(navigationLayoutProperty) || isHeightWrapOrFix) {
        SetNavigationHeight(layoutWrapper, size);
    }
    if (isWidthWrapOrFix) {
        SetNavigationWidth(layoutWrapper, size);
    }
    size.AddWidth(padding.left.value_or(0.0f) + padding.right.value_or(0.0f));
    size.AddHeight(padding.top.value_or(0.0f) + padding.bottom.value_or(0.0f));

    auto realSize = UpdateOptionSizeByCalcLayoutConstraint(OptionalSizeF(size.Width(), size.Height()),
        navigationLayoutProperty->GetCalcLayoutConstraint(),
        navigationLayoutProperty->GetLayoutConstraint()->percentReference);

    layoutWrapper->GetGeometryNode()->SetFrameSize(realSize.ConvertToSizeT());
}

} // namespace OHOS::Ace::NG
