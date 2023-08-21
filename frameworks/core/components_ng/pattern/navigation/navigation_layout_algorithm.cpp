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
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

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

float LayoutNavBar(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const NavBarPosition& position,
    OffsetF& returnNavBarOffset)
{
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, 0.0f);
    auto navigationLayoutAlgorithm =
        AceType::DynamicCast<NavigationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    if (navigationLayoutProperty->GetHideNavBar().value_or(false) &&
        navigationLayoutAlgorithm->GetNavigationMode() == NavigationMode::SPLIT) {
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
        returnNavBarOffset = navBarOffset;
        return geometryNode->GetFrameSize().Width();
    }
    auto navBarOffset = OffsetT<float>(0.0f, 0.0f);
    geometryNode->SetMarginFrameOffset(navBarOffset);
    navBarWrapper->Layout();
    returnNavBarOffset = navBarOffset;
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

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto navigationLayoutAlgorithm =
        AceType::DynamicCast<NavigationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto contentChildSize = contentNode->GetChildren().size();

    if ((contentChildSize != 0 && navigationLayoutAlgorithm->GetNavigationMode() == NavigationMode::STACK) ||
        position == NavBarPosition::END ||
        (navigationLayoutProperty->GetHideNavBar().value_or(false) &&
            navigationLayoutAlgorithm->GetNavigationMode() == NavigationMode::SPLIT)) {
        auto contentOffset = OffsetT<float>(0.0f, 0.0f);
        geometryNode->SetMarginFrameOffset(contentOffset);
        contentWrapper->Layout();
        return;
    }
    auto contentOffset = OffsetT<float>(navBarWidth + dividerWidth, geometryNode->GetFrameOffset().GetY());
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

bool NavigationLayoutAlgorithm::IsAutoHeight(const RefPtr<LayoutProperty>& layoutProperty)
{
    auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (!calcLayoutConstraint || !calcLayoutConstraint->selfIdealSize.has_value() ||
        !calcLayoutConstraint->selfIdealSize->Height().has_value() ||
        (calcLayoutConstraint->selfIdealSize->Height().value().ToString().find("auto")
        == std::string::npos)) {
            return false;
        }
    return true;
}

void NavigationLayoutAlgorithm::RangeCalculation(
    const RefPtr<NavigationGroupNode>& hostNode, const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty)
{
    const auto& constraint = navigationLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto parentSize =
         CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
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
    maxNavBarWidthValue_ = Dimension(std::max(maxNavBarWidth, minNavBarWidth), DimensionUnit::PX);
    auto navBarWidthValue = navigationLayoutProperty->GetNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH);
    auto navBarWidth = navBarWidthValue.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    realNavBarWidth_ = navBarWidth;
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

void NavigationLayoutAlgorithm::UpdateNavigationMode(
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& frameSize)
{
    auto usrNavigationMode = navigationLayoutProperty->GetUsrNavigationModeValue(NavigationMode::AUTO);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto currentPlatformVersion = pipeline->GetMinPlatformVersion();

    auto navigationWidth = 0.0f;
    if (currentPlatformVersion >= PLATFORM_VERSION_TEN) {
        navigationWidth = static_cast<float>(minNavBarWidthValue_.ConvertToPx() + minContentWidthValue_.ConvertToPx());
    } else {
        navigationWidth = static_cast<float>(WINDOW_WIDTH.ConvertToPx());
    }
    if (usrNavigationMode == NavigationMode::AUTO) {
        if (frameSize.Width() > navigationWidth) {
            usrNavigationMode = NavigationMode::SPLIT;
        } else {
            usrNavigationMode = NavigationMode::STACK;
        }
    }
    SetNavigationMode(usrNavigationMode);
}

void NavigationLayoutAlgorithm::SizeCalculation(LayoutWrapper* layoutWrapper,
    const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& frameSize)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto constraint = navigationLayoutProperty->GetLayoutConstraint();
    auto parentSize =
        CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto navigationLayoutAlgorithm =
    AceType::DynamicCast<NavigationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
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
    if (GetNavigationMode() == NavigationMode::SPLIT) {
        SizeCalculationSplit(navigationLayoutProperty, frameSize);
    } else {
        SizeCalculationStack(hostNode, navigationLayoutProperty, frameSize);
    }
}

void NavigationLayoutAlgorithm::SizeCalculationSplit(
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& frameSize)
{
    float frameWidth = frameSize.Width();
    auto parentSize = CreateIdealSizeByPercentRef(
        navigationLayoutProperty->GetLayoutConstraint().value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    auto navBarWidthValue = navigationLayoutProperty->GetNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH);
    auto userSetNavBarWidth = navBarWidthValue.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    auto dividerWidth = static_cast<float>(DIVIDER_WIDTH.ConvertToPx());
    auto minNavBarWidth = minNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    auto minContentWidth = minContentWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    realContentWidth_ = minContentWidth;

    if (navigationLayoutProperty->GetHideNavBar().value_or(false)) {
        navBarSize_ = SizeF(0.0f, 0.0f);
        dividerSize_ = SizeF(0.0f, 0.0f);
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
    navBarSize_.SetWidth(realNavBarWidth_);
    dividerSize_.SetWidth(realDividerWidth_);
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
    realContentWidth_ = frameWidth;
    navBarSize_.SetWidth(frameWidth);
    dividerSize_.SetWidth(realDividerWidth_);
    contentSize_.SetWidth(realContentWidth_);

}

void NavigationLayoutAlgorithm::MeasureNavBar(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& navBarSize)
{
    auto navBarNode = hostNode->GetNavBarNode();
    CHECK_NULL_VOID(navBarNode);
    auto index = hostNode->GetChildIndexById(navBarNode->GetId());
    auto navBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(navBarWrapper);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    if (IsAutoHeight(navigationLayoutProperty)) {
        navBarWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            navigationLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.value());
        constraint.selfIdealSize.SetWidth(navBarSize.Width());
    } else {
        constraint.selfIdealSize = OptionalSizeF(navBarSize.Width(), navBarSize.Height());
    }
    navBarWrapper->Measure(constraint);
    realNavBarHeight_ = navBarWrapper->GetGeometryNode()->GetFrameSize().Height();
}

void NavigationLayoutAlgorithm::MeasureContentChild(LayoutWrapper* layoutWrapper,
    const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& contentSize)
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
        if (IsAutoHeight(navigationLayoutProperty)) {
            constraint.selfIdealSize.SetWidth(contentSize.Width());
        } else {
            constraint.selfIdealSize = OptionalSizeF(contentSize.Width(), contentSize.Height());
        }
    }
    contentWrapper->Measure(constraint);
    realContentHeight_ = contentWrapper->GetGeometryNode()->GetFrameSize().Height();
}

void NavigationLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navigationLayoutProperty);
    const auto& constraint = navigationLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    auto size =
         CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT).ConvertToSizeT();
    FitScrollFullWindow(size);
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    if (ifNeedInit_) {
        RangeCalculation(hostNode, navigationLayoutProperty);
    }
    if (size.Width() == 0.0f) {
        return;
    }
    GetRange(hostNode);
    UpdateNavigationMode(navigationLayoutProperty, size);
    SizeCalculation(layoutWrapper, hostNode, navigationLayoutProperty, size);

    MeasureNavBar(layoutWrapper, hostNode, navigationLayoutProperty, navBarSize_);
    MeasureContentChild(layoutWrapper, hostNode, navigationLayoutProperty, contentSize_);
    MeasureDivider(layoutWrapper, hostNode, navigationLayoutProperty, dividerSize_);
    SetNavigationHeight(layoutWrapper, size);
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
}

void NavigationLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto navBarPosition = navigationLayoutProperty->GetNavBarPositionValue(NavBarPosition::START);
    OffsetF navBarOffset(0.0, 0.0);
    float navBarWidth = LayoutNavBar(layoutWrapper, hostNode, navigationLayoutProperty, navBarPosition, navBarOffset);
    float dividerWidth = LayoutDivider(layoutWrapper, hostNode, navigationLayoutProperty, navBarWidth, navBarPosition);
    LayoutContent(layoutWrapper, hostNode, navigationLayoutProperty, navBarWidth, dividerWidth, navBarPosition);
    navBarOffset_ = navBarOffset;
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
    } else if (navigationMode_ == NavigationMode::STACK) {
        size.SetHeight(realContentHeight_);
    } else if (navigationMode_ == NavigationMode::SPLIT) {
        float navHeight = std::max(realContentHeight_, realNavBarHeight_);
        size.SetHeight(navHeight);
    }
}

} // namespace OHOS::Ace::NG
