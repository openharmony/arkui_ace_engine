/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tabs_side_bar_layout_algorithm.h"

#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/tabs/tabs_side_bar_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
const Dimension TAB_LIST_TOP_MARGIN = 4.0_vp;
const Dimension SIDEBAR_PADDING = 16.0_vp;
const Dimension GRADUAL_BLUR_MASK_EXTRA_HEIGHT = 32.0_vp;
} // namespace

void TabsSideBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto size = CreateIdealSize(constraint.value(), Axis::VERTICAL, MeasureType::MATCH_PARENT, true);
    // SideBar frame size is the full size from parent constraint (no padding on the node itself)
    geometryNode->SetFrameSize(size);

    auto containerHeight = MeasureHeaderContainer(layoutWrapper, size);
    MeasureHeaderContainerMaskNode(layoutWrapper, size, containerHeight);
    float totalFixedHeight = containerHeight;
    if (!NearEqual(containerHeight, 0.0f)) {
        totalFixedHeight += TAB_LIST_TOP_MARGIN.ConvertToPx();
    }
    MeasureTabList(layoutWrapper, size, totalFixedHeight);
}

float TabsSideBarLayoutAlgorithm::MeasureHeaderContainer(LayoutWrapper* layoutWrapper, const SizeF& size)
{
    CHECK_NULL_RETURN(layoutWrapper, 0.0f);
    auto hostNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_RETURN(hostNode, 0.0f);
    auto sideBarPattern = hostNode->GetPattern<TabsSideBarPattern>();
    CHECK_NULL_RETURN(sideBarPattern, 0.0f);
    auto headerContainerNode = sideBarPattern->GetHeaderContainerNode();
    CHECK_NULL_RETURN(headerContainerNode, 0.0f);
    auto property = headerContainerNode->GetLayoutProperty();
    CHECK_NULL_RETURN(property, 0.0f);
    if (property->GetVisibilityValue(VisibleType::GONE) != VisibleType::VISIBLE) {
        return 0.0f;
    }
    auto index = hostNode->GetChildIndexById(headerContainerNode->GetId());
    if (index < 0) {
        return 0.0f;
    }
    auto headerContainerWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(headerContainerWrapper, 0.0f);

    float padding = SIDEBAR_PADDING.ConvertToPx();
    float contentWidth = std::max(0.0f, size.Width() - padding - padding);
    float contentHeight = size.Height();
    LayoutConstraintF childConstraint;
    childConstraint.maxSize.SetWidth(contentWidth);
    childConstraint.maxSize.SetHeight(contentHeight);
    childConstraint.minSize.SetWidth(0.0f);
    childConstraint.minSize.SetHeight(0.0f);
    childConstraint.percentReference.SetWidth(contentWidth);
    childConstraint.percentReference.SetHeight(contentHeight);
    headerContainerWrapper->Measure(childConstraint);
    return headerContainerWrapper->GetGeometryNode()->GetFrameSize().Height();
}

void TabsSideBarLayoutAlgorithm::MeasureHeaderContainerMaskNode(
    LayoutWrapper* layoutWrapper, const SizeF& size, float headerContainerHeight)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto hostNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto sideBarPattern = hostNode->GetPattern<TabsSideBarPattern>();
    CHECK_NULL_VOID(sideBarPattern);
    float extraHeight = GRADUAL_BLUR_MASK_EXTRA_HEIGHT.ConvertToPx();
    float maskHeight = headerContainerHeight + extraHeight;
    float maskWidth = size.Width();
    LayoutConstraintF maskConstraint;
    maskConstraint.selfIdealSize.SetWidth(maskWidth);
    maskConstraint.selfIdealSize.SetHeight(maskHeight);
    maskConstraint.maxSize.SetWidth(maskWidth);
    maskConstraint.maxSize.SetHeight(maskHeight);
    maskConstraint.minSize.SetWidth(0.0f);
    maskConstraint.minSize.SetHeight(0.0f);
    RefPtr<FrameNode> effectNodes[] = { sideBarPattern->GetHeaderContainerMaskBlurNode(),
        sideBarPattern->GetHeaderContainerMaskNode() };
    for (const auto& effectNode : effectNodes) {
        CHECK_NULL_CONTINUE(effectNode);
        auto property = effectNode->GetLayoutProperty();
        CHECK_NULL_CONTINUE(property);
        if (NearEqual(headerContainerHeight, 0.0f)) {
            property->UpdateVisibility(VisibleType::INVISIBLE);
            continue;
        }
        if (property->GetVisibilityValue(VisibleType::INVISIBLE) != VisibleType::VISIBLE) {
            continue;
        }
        auto maskIndex = hostNode->GetChildIndexById(effectNode->GetId());
        if (maskIndex < 0) {
            continue;
        }
        auto maskWrapper = layoutWrapper->GetOrCreateChildByIndex(maskIndex);
        CHECK_NULL_CONTINUE(maskWrapper);
        maskWrapper->Measure(maskConstraint);
    }
}

void TabsSideBarLayoutAlgorithm::MeasureTabList(
    LayoutWrapper* layoutWrapper, const SizeF& size, float totalFixedHeight)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto hostNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto sideBarPattern = hostNode->GetPattern<TabsSideBarPattern>();
    CHECK_NULL_VOID(sideBarPattern);
    auto tabListNode = sideBarPattern->GetTabListNode();
    CHECK_NULL_VOID(tabListNode);
    auto index = hostNode->GetChildIndexById(tabListNode->GetId());
    if (index < 0) {
        return;
    }
    auto tabBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(tabBarWrapper);
    auto property = tabListNode->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    // Set safeAreaPadding.top on TabList so that content constraint is reduced by header height,
    // but frame still covers the full area. Combined with clipContent(SAFE_AREA) on Scroll,
    // this makes scroll content render behind the header.
    PaddingProperty safeAreaPadding;
    safeAreaPadding.top = CalcLength(totalFixedHeight);
    property->UpdateSafeAreaPadding(safeAreaPadding);

    float padding = SIDEBAR_PADDING.ConvertToPx();
    float contentWidth = std::max(0.0f, size.Width() - padding - padding);
    float contentHeight = size.Height();
    // Build child constraint manually with content area (padding subtracted)
    LayoutConstraintF tabBarConstraint;
    tabBarConstraint.selfIdealSize.SetWidth(contentWidth);
    tabBarConstraint.selfIdealSize.SetHeight(contentHeight);
    tabBarConstraint.maxSize.SetWidth(contentWidth);
    tabBarConstraint.maxSize.SetHeight(contentHeight);
    tabBarConstraint.minSize.SetWidth(0.0f);
    tabBarConstraint.minSize.SetHeight(0.0f);
    tabBarConstraint.percentReference.SetWidth(contentWidth);
    tabBarConstraint.percentReference.SetHeight(contentHeight);
    tabBarWrapper->Measure(tabBarConstraint);
}

void TabsSideBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto hostNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto sideBarPattern = hostNode->GetPattern<TabsSideBarPattern>();
    CHECK_NULL_VOID(sideBarPattern);

    // Manually apply padding offset for child positioning
    float offsetX = SIDEBAR_PADDING.ConvertToPx();
    LayoutChild(layoutWrapper, hostNode, sideBarPattern->GetHeaderContainerNode(), OffsetF{offsetX, 0.0f});
    LayoutChild(layoutWrapper, hostNode, sideBarPattern->GetHeaderContainerMaskBlurNode(), OffsetF{0.0f, 0.0f});
    LayoutChild(layoutWrapper, hostNode, sideBarPattern->GetHeaderContainerMaskNode(), OffsetF{0.0f, 0.0f});
    LayoutChild(layoutWrapper, hostNode, sideBarPattern->GetTabListNode(), OffsetF{offsetX, 0.0f});
}

void TabsSideBarLayoutAlgorithm::LayoutChild(LayoutWrapper* layoutWrapper,
    const RefPtr<FrameNode>& hostNode, const RefPtr<UINode>& childUINode, const OffsetF& offset)
{
    CHECK_NULL_VOID(childUINode);
    auto index = hostNode->GetChildIndexById(childUINode->GetId());
    if (index < 0) {
        return;
    }
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(childWrapper);
    auto childGeo = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeo);
    childGeo->SetMarginFrameOffset(offset);
    childWrapper->Layout();
}
} // namespace OHOS::Ace::NG
