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

#include <cmath>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/property/calc_length.h"

namespace OHOS::Ace::NG {

constexpr static int32_t PLATFORM_VERSION_TEN = 10;
constexpr Dimension WINDOW_WIDTH = 520.0_vp;

namespace {

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

void MeasureContentChild(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& contentSize)
{
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto index = hostNode->GetChildIndexById(contentNode->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(contentWrapper);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    constraint.selfIdealSize = OptionalSizeF(contentSize.Width(), contentSize.Height());
    contentWrapper->Measure(constraint);
}

float LayoutNavBar(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const NavBarPosition& position)
{
    if (navigationLayoutProperty->GetHideNavBar().value_or(false) &&
        navigationLayoutProperty->GetNavigationModeValue() == NavigationMode::SPLIT) {
        return 0.0f;
    }

    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_RETURN(contentNode, 0.0f);
    auto navBarNode = hostNode->GetNavBarNode();
    CHECK_NULL_RETURN(navBarNode, 0.0f);
    auto index = hostNode->GetChildIndexById(navBarNode->GetId());
    auto navBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(navBarWrapper, 0.0f);
    auto geometryNode = navBarWrapper->GetGeometryNode();
    auto navigationGeometryNode = layoutWrapper->GetGeometryNode();
    if (position == NavBarPosition::END) {
        auto navBarOffset =
            OffsetT<float>(navigationGeometryNode->GetFrameSize().Width() - geometryNode->GetFrameSize().Width(),
                geometryNode->GetFrameOffset().GetY());
        geometryNode->SetMarginFrameOffset(navBarOffset);
        navBarWrapper->Layout();
        return geometryNode->GetFrameSize().Width();
    }
    if (hostNode->GetIsModeChange() && (navigationLayoutProperty->GetDestinationChange().value_or(false) ||
            contentNode->FindChildNodeOfClass<NavDestinationGroupNode>()) &&
        navigationLayoutProperty->GetNavigationMode() == NavigationMode::STACK) {
        auto contentOffset = OffsetT<float>(-geometryNode->GetFrameSize().Width(), 0.0f);
        geometryNode->SetMarginFrameOffset(contentOffset);
        navBarWrapper->Layout();
        return geometryNode->GetFrameSize().Width();
    }
    auto navBarOffset = OffsetT<float>(0.0f, 0.0f);
    geometryNode->SetMarginFrameOffset(navBarOffset);
    navBarWrapper->Layout();
    return geometryNode->GetFrameSize().Width();
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
    OffsetT<float> dividerOffset;
    if (position == NavBarPosition::END) {
        dividerOffset = OffsetT<float>(
            navigationGeometryNode->GetFrameSize().Width() - geometryNode->GetFrameSize().Width() - navBarWidth,
            geometryNode->GetFrameOffset().GetY());
    } else {
        dividerOffset = OffsetT<float>(navBarWidth, geometryNode->GetFrameOffset().GetY());
    }
    geometryNode->SetMarginFrameOffset(dividerOffset);
    dividerWrapper->Layout();
    return geometryNode->GetFrameSize().Width();
}

void LayoutContent(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, float navBarWidth, float dividerWidth,
    const NavBarPosition& position)
{
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto index = hostNode->GetChildIndexById(contentNode->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(contentWrapper);
    auto geometryNode = contentWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    const auto& navigationGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(navigationGeometryNode);

    OffsetT<float> contentOffset;
    if ((navigationLayoutProperty->GetDestinationChange().value_or(false) ||
            contentNode->FindChildNodeOfClass<NavDestinationGroupNode>()) &&
        navigationLayoutProperty->GetNavigationMode() == NavigationMode::STACK) {
        contentOffset = OffsetT<float>(0.0f, 0.0f);
        geometryNode->SetMarginFrameOffset(contentOffset);
        contentWrapper->Layout();
        return;
    }
    if (position == NavBarPosition::END) {
        navigationLayoutProperty->GetNavigationMode() == NavigationMode::STACK
            ? contentOffset = OffsetT<float>(-geometryNode->GetFrameSize().Width(), 0.0f)
            : contentOffset = OffsetT<float>(0.0f, 0.0f);
        geometryNode->SetMarginFrameOffset(contentOffset);
        contentWrapper->Layout();
        return;
    }
    navigationLayoutProperty->GetNavigationMode() == NavigationMode::STACK
        ? contentOffset =
              OffsetT<float>(navigationGeometryNode->GetFrameSize().Width(), geometryNode->GetFrameOffset().GetY())
        : contentOffset = OffsetT<float>(navBarWidth + dividerWidth, geometryNode->GetFrameOffset().GetY());
    geometryNode->SetMarginFrameOffset(contentOffset);
    contentWrapper->Layout();
}

void FitScrollFullWindow(SizeF& frameSize)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    if (frameSize.Width() == Infinity<float>()) {
        frameSize.SetWidth(pipeline->GetRootWidth());
    }
    if (frameSize.Height() == Infinity<float>()) {
        frameSize.SetHeight(pipeline->GetRootHeight());
    }
}

} // namespace

void NavigationLayoutAlgorithm::MeasureNavBar(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& navBarSize)
{
    auto navBarNode = hostNode->GetNavBarNode();
    CHECK_NULL_VOID(navBarNode);
    auto index = hostNode->GetChildIndexById(navBarNode->GetId());
    auto navBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(navBarWrapper);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    constraint.selfIdealSize = OptionalSizeF(navBarSize.Width(), navBarSize.Height());
    navBarWrapper->Measure(constraint);
    realNavBarHeight_ = navBarWrapper->GetGeometryNode()->GetFrameSize().Height();
}

void NavigationLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navigationLayoutProperty);
    const auto& constraint = navigationLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    auto size = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    auto parentSize = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    FitScrollFullWindow(size);
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);

    auto navBarWidthValue = navigationLayoutProperty->GetNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH);
    auto minNavBarWidthValue = navigationLayoutProperty->GetMinNavBarWidthValue(DEFAULT_MIN_NAV_BAR_WIDTH);
    auto maxNavBarWidthValue = navigationLayoutProperty->GetMaxNavBarWidthValue(DEFAULT_MAX_NAV_BAR_WIDTH);
    auto minContentWidthValue = navigationLayoutProperty->GetMinContentWidthValue(DEFAULT_MIN_CONTENT_WIDTH);

    usrNavigationMode_ = navigationLayoutProperty->GetUsrNavigationModeValue(NavigationMode::AUTO);
    navigationMode_ = usrNavigationMode_;
    navigationLayoutProperty->UpdateNavigationMode(navigationMode_);
    
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto currentPlatformVersion = pipeline->GetMinPlatformVersion();

    auto navigationWidth = 0.0f;

    if (currentPlatformVersion >= PLATFORM_VERSION_TEN) {
        navigationWidth = static_cast<float>(minNavBarWidthValue.ConvertToPx() + minContentWidthValue.ConvertToPx());
    } else {
        navigationWidth = static_cast<float>(WINDOW_WIDTH.ConvertToPx());
    }

    if (navigationMode_ == NavigationMode::AUTO) {
        if (size.Width() >= navigationWidth) {
            navigationMode_ = NavigationMode::SPLIT;
            navigationLayoutProperty->UpdateNavigationMode(navigationMode_);
        } else {
            navigationMode_ = NavigationMode::STACK;
            navigationLayoutProperty->UpdateNavigationMode(navigationMode_);
        }
    } else {
        auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
        CHECK_NULL_VOID(layoutAlgorithmWrapper);
        auto navigationLayoutAlgorithm =
            DynamicCast<NavigationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
        navigationLayoutAlgorithm->SetNavigationMode(navigationMode_);
    }

    auto navBarWidth = navBarWidthValue.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));

    if (currentPlatformVersion >= PLATFORM_VERSION_TEN) {
        auto minNavBarWidth = minNavBarWidthValue.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
        auto maxNavBarWidth = maxNavBarWidthValue.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
        auto minContentWidth = minContentWidthValue.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));

        if (ifNeedInit_) {
            if (navBarWidth <= minNavBarWidth) {
                navBarWidth = minNavBarWidth;
            } else if (navBarWidth >= maxNavBarWidth) {
                navBarWidth = maxNavBarWidth;
            }
            realNavBarWidth_ = navBarWidth;
        }

        if (realNavBarWidth_ + static_cast<float>(DIVIDER_WIDTH.ConvertToPx()) + minContentWidth > size.Width()) {
            realNavBarWidth_ = size.Width() - minContentWidth - static_cast<float>(DIVIDER_WIDTH.ConvertToPx());
            if (realNavBarWidth_ <= minNavBarWidth) {
                realNavBarWidth_ = minNavBarWidth;
            }
        }
        if (navBarWidth != realNavBarWidth_) {
            navBarWidth = realNavBarWidth_;
        }
    }

    auto navBarSize = size;
    auto contentSize = size;
    auto dividerSize = SizeF(0.0f, 0.0f);
    float contentWidth = 0.0f;
    float dividerWidth = 0.0f;

    if (navigationLayoutProperty->GetNavigationModeValue(navigationMode_) == NavigationMode::SPLIT) {
        if (navigationLayoutProperty->GetHideNavBar().value_or(false)) {
            contentWidth = size.Width();
            navBarSize.SetWidth(0.0f);
            navBarSize.SetHeight(0.0f);
            contentSize.SetWidth(contentWidth);
            MeasureNavBar(layoutWrapper, hostNode, navigationLayoutProperty, navBarSize);
            MeasureContentChild(layoutWrapper, hostNode, navigationLayoutProperty, contentSize);
            MeasureDivider(layoutWrapper, hostNode, navigationLayoutProperty, dividerSize);
            layoutWrapper->GetGeometryNode()->SetFrameSize(size);
            return;
        }
        contentWidth = std::floor(size.Width() - static_cast<float>(DIVIDER_WIDTH.ConvertToPx()) - navBarWidth);
        dividerWidth = size.Width() - navBarWidth - contentWidth;
        navBarSize.SetWidth(navBarWidth);
        contentSize.SetWidth(contentWidth);
        dividerSize.SetWidth(dividerWidth);
        dividerSize.SetHeight(size.Height());
    } else if (hostNode->GetIsModeChange()) {
        if (navigationLayoutProperty->GetDestinationChange().value_or(false) ||
            contentNode->FindChildNodeOfClass<NavDestinationGroupNode>()) {
            navigationLayoutProperty->GetNavBarPositionValue(NavBarPosition::START) == NavBarPosition::END
                ? navBarSize.SetWidth(0.0f)
                : navBarSize.SetWidth(navBarWidth);
        } else {
            if (navigationLayoutProperty->GetNavBarPositionValue(NavBarPosition::START) == NavBarPosition::END) {
                contentWidth = std::floor(size.Width() - static_cast<float>(DIVIDER_WIDTH.ConvertToPx()) - navBarWidth);
            }
            contentSize.SetWidth(contentWidth);
        }
    }
    MeasureNavBar(layoutWrapper, hostNode, navigationLayoutProperty, navBarSize);
    MeasureContentChild(layoutWrapper, hostNode, navigationLayoutProperty, contentSize);
    MeasureDivider(layoutWrapper, hostNode, navigationLayoutProperty, dividerSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
}

void NavigationLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto navBarPosition = navigationLayoutProperty->GetNavBarPositionValue(NavBarPosition::START);
    float navBarWidth = LayoutNavBar(layoutWrapper, hostNode, navigationLayoutProperty, navBarPosition);
    float dividerWidth = LayoutDivider(layoutWrapper, hostNode, navigationLayoutProperty, navBarWidth, navBarPosition);
    LayoutContent(layoutWrapper, hostNode, navigationLayoutProperty, navBarWidth, dividerWidth, navBarPosition);
}

} // namespace OHOS::Ace::NG
