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

#include "core/components_ng/pattern/stage/force_split/parallel_stage_layout_algorithm.h"

#include <algorithm>
#include <cmath>

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/manager/force_split/force_split_manager.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_manager.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Dimension DIVIDER_WIDTH = 1.0_px;
constexpr Dimension DIVIDER_DRAG_BAR_WIDTH = 12.0_vp;
constexpr Dimension DIVIDER_DRAG_BAR_HEIGHT = 48.0_vp;
constexpr Dimension DRAG_BAR_ITEM_WIDTH = 2.0_vp;
constexpr Dimension DRAG_BAR_ITEM_HEIGHT = 24.0_vp;
constexpr float HALF_RATIO = 0.5f;

bool IsVirtualStackBasedSplit(const RefPtr<FrameNode>& hostNode)
{
    CHECK_NULL_RETURN(hostNode, false);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto forceSplitMgr = pipeline->GetForceSplitManager();
    CHECK_NULL_RETURN(forceSplitMgr, false);
    return forceSplitMgr->CanPushPageToPrimary();
}
}

float ParallelStageLayoutAlgorithm::GetDividerOffsetX() const
{
    auto rtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    // In RTL, secondary column is laid out on the physical left side, so divider follows secondary width.
    return rtl ? secondarySize_.Width() : primarySize_.Width();
}

OffsetF ParallelStageLayoutAlgorithm::GetPrimarySlotOffset(float pageWidth) const
{
    auto rtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (!rtl) {
        return OffsetF(std::max(0.0f, primarySize_.Width() - pageWidth), 0.0f);
    }
    return OffsetF(
        secondarySize_.Width() + dividerSize_.Width() + std::max(0.0f, primarySize_.Width() - pageWidth), 0.0f);
}

OffsetF ParallelStageLayoutAlgorithm::GetSecondarySlotOffset() const
{
    auto rtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (rtl) {
        return OffsetF(0.0f, 0.0f);
    }
    return OffsetF(primarySize_.Width() + dividerSize_.Width(), 0.0f);
}

ForceSplitPageColumnType ParallelStageLayoutAlgorithm::GetPageLayoutColumnType(
    const RefPtr<FrameNode>& pageNode, int32_t pageIndex) const
{
    CHECK_NULL_RETURN(pageNode, ForceSplitPageColumnType::NONE);
    auto pattern = pageNode->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(pattern, ForceSplitPageColumnType::NONE);
    if (!pattern->IsInSplitTransitionLayout()) {
        auto layoutProperty = pageNode->GetLayoutProperty();
        if (layoutProperty && layoutProperty->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE) {
            return ForceSplitPageColumnType::NONE;
        }
    }
    auto pageType = pattern->GetPageType();
    if (pageType == RouterPageType::PLACEHOLDER_PAGE || pageType == RouterPageType::RELATED_PAGE) {
        return pageIndex == secondaryIndex_ ? ForceSplitPageColumnType::SECONDARY : ForceSplitPageColumnType::NONE;
    }
    if (pattern->IsInSplitTransitionLayout()) {
        return pattern->GetSplitTransitionColumnType();
    }
    if (pageIndex == primaryIndex_) {
        return ForceSplitPageColumnType::PRIMARY;
    }
    if (pageIndex == secondaryIndex_) {
        return ForceSplitPageColumnType::SECONDARY;
    }
    return ForceSplitPageColumnType::NONE;
}

void ParallelStageLayoutAlgorithm::MeasureInNewRouterSplitFlow(
    const RefPtr<FrameNode>& hostNode, LayoutWrapper* layoutWrapper, const RefPtr<ParallelStagePattern>& stagePattern)
{
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(layoutWrapper);
    CHECK_NULL_VOID(stagePattern);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto stageManager = AceType::DynamicCast<ParallelStageManager>(pipeline->GetStageManager());
    CHECK_NULL_VOID(stageManager);
    auto stageSize = static_cast<int32_t>(hostNode->GetChildren().size());
    if (stageSize <= 0) {
        return;
    }
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    SizeCalculationForForceSplit(hostNode, frameSize);
    primaryIndex_ = -1;
    secondaryIndex_ = -1;
    auto resolveIndex = [&hostNode](const RefPtr<FrameNode>& node) -> int32_t {
        CHECK_NULL_RETURN(node, -1);
        return hostNode->GetChildIndex(node);
    };
    // Only use the stable visible result calculated by manager:
    // primary comes from the current primary column, and secondary falls back to placeholder/related page.
    auto primaryNode = stageManager->GetTopPrimaryColumnPage();
    auto secondaryNode = stageManager->GetTopSecondaryColumnPage();
    if (!secondaryNode || resolveIndex(secondaryNode) < 0) {
        secondaryNode = stageManager->GetRelatedOrPlaceHolderPage();
    }
    primaryIndex_ = resolveIndex(primaryNode);
    secondaryIndex_ = resolveIndex(secondaryNode);
    if (primaryIndex_ < 0) {
        return;
    }
    if (primaryIndex_ == secondaryIndex_) {
        secondaryIndex_ = -1;
    }
    // layout divider node
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(dividerWrapper);
    auto dividerProperty = dividerWrapper->GetLayoutProperty();
    auto dividerConstraint = dividerProperty->CreateChildConstraint();
    dividerConstraint.selfIdealSize.SetSize(dividerSize_);
    dividerWrapper->Measure(dividerConstraint);
    MeasureRouterSplitPages(hostNode, layoutWrapper);
    MeasureDragBar(layoutWrapper, hostNode);
}

void ParallelStageLayoutAlgorithm::LayoutInNewRouterSplitFlow(
    const RefPtr<FrameNode>& hostNode, LayoutWrapper* layoutWrapper, const RefPtr<ParallelStagePattern>& stagePattern)
{
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(layoutWrapper);
    CHECK_NULL_VOID(stagePattern);
    // layout divider
    auto dividerOffset = GetDividerOffsetX();
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(dividerWrapper);
    auto dividerGeometry = dividerWrapper->GetGeometryNode();
    CHECK_NULL_VOID(dividerGeometry);
    OffsetF dividerOffsetF;
    dividerOffsetF.SetX(dividerOffset);
    dividerOffsetF.SetY(0.0f);
    dividerGeometry->SetMarginFrameOffset(dividerOffsetF);
    dividerWrapper->Layout();
    LayoutRouterSplitPages(hostNode, layoutWrapper);
    LayoutDragBar(layoutWrapper, hostNode, primarySize_.Width());
}

void ParallelStageLayoutAlgorithm::MeasurePageInColumn(
    const RefPtr<LayoutWrapper>& layoutWrapper, ForceSplitPageColumnType columnType)
{
    switch (columnType) {
        case ForceSplitPageColumnType::PRIMARY:
            MeasurePage(layoutWrapper, primarySize_);
            return;
        case ForceSplitPageColumnType::SECONDARY:
            MeasurePage(layoutWrapper, secondarySize_);
            return;
        default:
            return;
    }
}

void ParallelStageLayoutAlgorithm::MeasureRouterSplitPages(
    const RefPtr<FrameNode>& hostNode, LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(layoutWrapper);
    auto stageSize = static_cast<int32_t>(hostNode->GetChildren().size());
    for (int32_t index = 0; index < stageSize; ++index) {
        if (index == 0) {
            continue;
        }
        auto pageNode = AceType::DynamicCast<FrameNode>(hostNode->GetChildAtIndex(index));
        if (!pageNode || pageNode->GetTag() != V2::PAGE_ETS_TAG) {
            continue;
        }
        auto columnType = GetPageLayoutColumnType(pageNode, index);
        if (columnType == ForceSplitPageColumnType::NONE) {
            continue;
        }
        auto pageWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(pageWrapper);
        MeasurePageInColumn(pageWrapper, columnType);
    }
}

void ParallelStageLayoutAlgorithm::LayoutPageInColumn(
    const RefPtr<LayoutWrapper>& layoutWrapper, ForceSplitPageColumnType columnType)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    OffsetF offset;
    switch (columnType) {
        case ForceSplitPageColumnType::PRIMARY:
            offset = GetPrimarySlotOffset(geometryNode->GetFrameSize().Width());
            break;
        case ForceSplitPageColumnType::SECONDARY:
            offset = GetSecondarySlotOffset();
            break;
        default:
            return;
    }
    geometryNode->SetMarginFrameOffset(offset);
    layoutWrapper->Layout();
}

void ParallelStageLayoutAlgorithm::LayoutRouterSplitPages(
    const RefPtr<FrameNode>& hostNode, LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(layoutWrapper);
    auto stageSize = static_cast<int32_t>(hostNode->GetChildren().size());
    for (int32_t index = 0; index < stageSize; ++index) {
        if (index == 0) {
            continue;
        }
        auto pageNode = AceType::DynamicCast<FrameNode>(hostNode->GetChildAtIndex(index));
        if (!pageNode || pageNode->GetTag() != V2::PAGE_ETS_TAG) {
            continue;
        }
        auto columnType = GetPageLayoutColumnType(pageNode, index);
        if (columnType == ForceSplitPageColumnType::NONE) {
            continue;
        }
        auto pageWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(pageWrapper);
        LayoutPageInColumn(pageWrapper, columnType);
    }
}

void ParallelStageLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto stagePattern = AceType::DynamicCast<ParallelStagePattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(stagePattern);
    // if mian page and split mode is not enable or current mode is stack, use box layout
    if (!stagePattern->GetIsSplit()) {
        BoxLayoutAlgorithm::Measure(layoutWrapper);
        return;
    }
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& constraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto size =
        CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT).ConvertToSizeT();
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
    
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto forceSplitMgr = pipeline->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (stagePattern->GetIsSplit() && forceSplitMgr->IsForceSplitDragging()) {
        SizeCalculationForForceSplit(hostNode, size);
        auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
        CHECK_NULL_VOID(dividerWrapper);
        auto dividerProperty = dividerWrapper->GetLayoutProperty();
        auto dividerConstraint = dividerProperty->CreateChildConstraint();
        dividerConstraint.selfIdealSize.SetSize(dividerSize_);
        dividerWrapper->Measure(dividerConstraint);
        MeasureDragBar(layoutWrapper, hostNode);
        MeasureForceSplitMaskNodes(layoutWrapper, hostNode);
        return;
    }

    if (IsVirtualStackBasedSplit(hostNode)) {
        MeasureInNewRouterSplitFlow(hostNode, layoutWrapper, stagePattern);
        MeasureDragBar(layoutWrapper, hostNode);
        return;
    }

    auto homePage = stagePattern->GetHomePage();
    if (homePage) {
        primaryIndex_ = hostNode->GetChildIndex(homePage);
    } else {
        primaryIndex_ = -1;
    }
    auto stageSize = static_cast<int32_t>(hostNode->GetChildren().size());
    if (stageSize <= 0) {
        return;
    }
    if (primaryIndex_ == -1) {
        // Legacy split behavior keeps the single router page centered until home page is identified.
        MeasureDetailPage(layoutWrapper->GetOrCreateChildByIndex(stageSize - 1));
        return;
    }
    SizeCalculationForForceSplit(hostNode, size);
    auto primaryPageWrapper = layoutWrapper->GetOrCreateChildByIndex(primaryIndex_);
    MeasurePage(primaryPageWrapper, primarySize_);
    // layout divider node
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(dividerWrapper);
    auto dividerProperty = dividerWrapper->GetLayoutProperty();
    auto dividerConstraint = dividerProperty->CreateChildConstraint();
    dividerConstraint.selfIdealSize.SetSize(dividerSize_);
    dividerWrapper->Measure(dividerConstraint);
    auto detailWrapper = layoutWrapper->GetOrCreateChildByIndex(stageSize - 1);
    // If failed to load relatedPage, the primaryPage and the last child of stage might be the same page.
    if (detailWrapper == primaryPageWrapper) {
        return;
    }
    MeasurePage(detailWrapper, secondarySize_);
    MeasureDragBar(layoutWrapper, hostNode);
}

void ParallelStageLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto stagePattern = AceType::DynamicCast<ParallelStagePattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(stagePattern);
    if (!stagePattern->GetIsSplit()) {
        BoxLayoutAlgorithm::Layout(layoutWrapper);
        return;
    }

    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto forceSplitMgr = pipeline->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (stagePattern->GetIsSplit() && forceSplitMgr->IsForceSplitDragging()) {
        float dragRatio = forceSplitMgr->GetTemporarySplitRatio().has_value() ?
            forceSplitMgr->GetTemporarySplitRatio().value() : forceSplitMgr->GetSplitRatio();
        float frameWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
        float navBarOrPrimaryNodeWidth = (frameWidth - dividerSize_.Width()) * (1.0f - dragRatio);

        auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
        CHECK_NULL_VOID(dividerWrapper);
        auto dividerGeometry = dividerWrapper->GetGeometryNode();
        CHECK_NULL_VOID(dividerGeometry);
        OffsetF dividerOffsetF;
        dividerOffsetF.SetX(navBarOrPrimaryNodeWidth);
        dividerOffsetF.SetY(0.0f);
        dividerGeometry->SetMarginFrameOffset(dividerOffsetF);
        dividerWrapper->Layout();

        LayoutDragBar(layoutWrapper, hostNode, navBarOrPrimaryNodeWidth);
        LayoutForceSplitMaskNodes(layoutWrapper, hostNode);
        return;
    }

    LayoutInSplitMode(hostNode, layoutWrapper);
}

void ParallelStageLayoutAlgorithm::LayoutInSplitMode(const RefPtr<FrameNode>& hostNode, LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(layoutWrapper);
    auto stageSize = static_cast<int32_t>(hostNode->GetChildren().size());
    if (stageSize <= 0) {
        return;
    }
    auto stagePattern = AceType::DynamicCast<ParallelStagePattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(stagePattern);
    if (IsVirtualStackBasedSplit(hostNode)) {
        if (primaryIndex_ < 0) {
            return;
        }
        LayoutInNewRouterSplitFlow(hostNode, layoutWrapper, stagePattern);
        return;
    }

    auto stageWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    if (primaryIndex_ == -1) {
        auto pageWrapper = layoutWrapper->GetOrCreateChildByIndex(stageSize - 1);
        CHECK_NULL_VOID(pageWrapper);
        auto geometryNode = pageWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto pageSize = geometryNode->GetFrameSize().Width();
        const int32_t half = 2;
        auto offsetX = (stageWidth - pageSize) / half;
        geometryNode->SetMarginFrameOffset(OffsetF { offsetX, 0.0f });
        pageWrapper->Layout();
        return;
    }

    // layout primary page
    auto primaryPageWrapper = layoutWrapper->GetOrCreateChildByIndex(primaryIndex_);
    CHECK_NULL_VOID(primaryPageWrapper);
    auto primaryGeometryNode = primaryPageWrapper->GetGeometryNode();
    CHECK_NULL_VOID(primaryGeometryNode);
    auto primaryPageWidth = primaryGeometryNode->GetFrameSize().Width();
    auto dividerWidth = dividerSize_.Width();
    auto dividerOffset = primarySize_.Width();
    auto primaryOffset = std::max(0.0f, (float)(dividerOffset - primaryPageWidth));
    OffsetF offset;
    offset.SetX(primaryOffset);
    offset.SetY(0.0f);
    primaryGeometryNode->SetMarginFrameOffset(offset);
    primaryPageWrapper->Layout();

    // layout divider
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(dividerWrapper);
    auto dividerGeometry = dividerWrapper->GetGeometryNode();
    CHECK_NULL_VOID(dividerGeometry);
    offset.SetX(dividerOffset);
    offset.SetY(0.0f);
    dividerGeometry->SetMarginFrameOffset(offset);
    dividerWrapper->Layout();

    // layout secondary page
    auto detailPageWrapper = layoutWrapper->GetOrCreateChildByIndex(stageSize - 1);
    CHECK_NULL_VOID(detailPageWrapper);
    // If failed to load relatedPage, the primaryPage and the last child of stage might be the same page.
    if (detailPageWrapper == primaryPageWrapper) {
        return;
    }
    offset.SetX(dividerOffset + dividerWidth);
    offset.SetY(0.0f);
    auto geometryNode = detailPageWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetMarginFrameOffset(offset);
    detailPageWrapper->Layout();

    LayoutDragBar(layoutWrapper, hostNode, primarySize_.Width());
}

void ParallelStageLayoutAlgorithm::MeasureDetailPage(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto detailPage = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(detailPage);
    auto pipelineContext = detailPage->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto detailProperty = detailPage->GetLayoutProperty();
    CHECK_NULL_VOID(detailProperty);
    auto constraint = detailProperty->CreateChildConstraint();
    const int32_t halfContent = 2;
    auto pageWidth = pipelineContext->GetRootWidth() / halfContent;
    auto pageHeight = pipelineContext->GetRootHeight();
    auto forceSplitMgr = pipelineContext->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (forceSplitMgr->IsForceSplitSupported(true)) {
        constraint.scaleProperty = ScaleProperty::CreateScaleProperty(pipelineContext);
    }
    constraint.selfIdealSize.UpdateSizeWithCheck(SizeF(pageWidth, pageHeight));
    constraint.maxSize.SetWidth(pageWidth);
    constraint.maxSize.SetHeight(pageHeight);
    layoutWrapper->Measure(constraint);
}

void ParallelStageLayoutAlgorithm::MeasurePage(const RefPtr<LayoutWrapper>& layoutWrapper, const SizeF& size)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto layoutProperty = hostNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto constraint = layoutProperty->CreateChildConstraint();
    auto pipelineContext = hostNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto forceSplitMgr = pipelineContext->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (forceSplitMgr->IsForceSplitSupported(true)) {
        constraint.scaleProperty = ScaleProperty::CreateScaleProperty(pipelineContext);
    }
    constraint.selfIdealSize.UpdateSizeWithCheck(size);
    layoutWrapper->Measure(constraint);
}

void ParallelStageLayoutAlgorithm::SizeCalculationForForceSplit(const RefPtr<FrameNode>& hostNode, const SizeF& size)
{
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto forceSplitMgr = pipeline->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    float ratio = forceSplitMgr->GetTemporarySplitRatio().has_value() ?
         forceSplitMgr->GetTemporarySplitRatio().value() : forceSplitMgr->GetSplitRatio();
    float dividerWidth = static_cast<float>(DIVIDER_WIDTH.ConvertToPx());
    dividerWidth = std::ceil(dividerWidth);
    auto secondaryWidth = (size.Width() - dividerWidth) * ratio;
    secondaryWidth = std::max(std::floor(secondaryWidth), 0.0f);
    auto primaryWidth = size.Width() - secondaryWidth - dividerWidth;
    primaryWidth = std::max(std::floor(primaryWidth), 0.0f);
    dividerSize_ = SizeF(dividerWidth, size.Height());
    primarySize_ = SizeF(primaryWidth, size.Height());
    secondarySize_ = SizeF(secondaryWidth, size.Height());
}

void ParallelStageLayoutAlgorithm::MeasureDragBar(
    LayoutWrapper* layoutWrapper, const RefPtr<FrameNode>& hostNode)
{
    auto stagePattern = AceType::DynamicCast<ParallelStagePattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(stagePattern);
    auto dragBarNode = stagePattern->GetDragBarNode();
    CHECK_NULL_VOID(dragBarNode);
    auto index = hostNode->GetChildIndexById(dragBarNode->GetId());
    auto dragWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(dragWrapper);
    auto dragBarItem = AceType::DynamicCast<FrameNode>(dragBarNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(dragBarItem);
    auto dragBarItemLayoutProperty = dragBarItem->GetLayoutProperty();
    CHECK_NULL_VOID(dragBarItemLayoutProperty);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto forceSplitMgr = pipeline->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    bool shouldMeasureDragBar = stagePattern->GetIsSplit() && forceSplitMgr->IsSplitDraggable();
    auto hostLayoutProperty = hostNode->GetLayoutProperty();
    CHECK_NULL_VOID(hostLayoutProperty);
    auto constraint = hostLayoutProperty->CreateChildConstraint();
    if (!shouldMeasureDragBar || NearZero(dividerSize_.Width())) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        dragBarItemLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(0.0f), CalcLength(0.0f)));
    } else {
        constraint.selfIdealSize = OptionalSizeF(
            static_cast<float>(DIVIDER_DRAG_BAR_WIDTH.ConvertToPx()),
            static_cast<float>(DIVIDER_DRAG_BAR_HEIGHT.ConvertToPx()));
        dragBarItemLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(DRAG_BAR_ITEM_WIDTH), CalcLength(DRAG_BAR_ITEM_HEIGHT)));
    }
    dragWrapper->Measure(constraint);
}

void ParallelStageLayoutAlgorithm::LayoutDragBar(
    LayoutWrapper* layoutWrapper, const RefPtr<FrameNode>& hostNode, float primaryWidth)
{
    auto stagePattern = AceType::DynamicCast<ParallelStagePattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(stagePattern);
    auto dragBarNode = stagePattern->GetDragBarNode();
    CHECK_NULL_VOID(dragBarNode);
    auto index = hostNode->GetChildIndexById(dragBarNode->GetId());
    auto dragWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(dragWrapper);
    auto geometryNode = dragWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto navigationGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(navigationGeometryNode);
    auto navigationWidth = navigationGeometryNode->GetFrameSize().Width();
    auto navigationHeight = navigationGeometryNode->GetFrameSize().Height();
    auto offsetX = primaryWidth - geometryNode->GetFrameSize().Width() * HALF_RATIO;
    auto offsetY = navigationHeight * HALF_RATIO - geometryNode->GetFrameSize().Height() * HALF_RATIO;
    OffsetT<float> dragOffset(offsetX, offsetY);
    auto rtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (rtl) {
        dragOffset.SetX(navigationWidth - primaryWidth - geometryNode->GetFrameSize().Width() * HALF_RATIO);
    }
    geometryNode->SetMarginFrameOffset(dragOffset);
    dragWrapper->Layout();
}

void ParallelStageLayoutAlgorithm::MeasureForceSplitMaskNodes(
    LayoutWrapper* layoutWrapper, const RefPtr<FrameNode>& hostNode)
{
    auto stagePattern = AceType::DynamicCast<ParallelStagePattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(stagePattern);
    do {
        auto leftMaskNode = stagePattern->GetOrCreateMaskNode(true);
        CHECK_NULL_BREAK(leftMaskNode);
        auto index = hostNode->GetChildIndexById(leftMaskNode->GetId());
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index, true);
        CHECK_NULL_BREAK(childWrapper);
        MeasurePage(childWrapper, primarySize_);
    } while (false);
    auto rightMaskNode = stagePattern->GetOrCreateMaskNode(false);
    CHECK_NULL_VOID(rightMaskNode);
    auto index = hostNode->GetChildIndexById(rightMaskNode->GetId());
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index, true);
    CHECK_NULL_VOID(childWrapper);
    MeasurePage(childWrapper, secondarySize_);
}

void ParallelStageLayoutAlgorithm::LayoutForceSplitMaskNodes(
    LayoutWrapper* layoutWrapper, const RefPtr<FrameNode>& hostNode)
{
    auto stagePattern = AceType::DynamicCast<ParallelStagePattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(stagePattern);
    do {
        auto leftMaskNode = stagePattern->GetOrCreateMaskNode(true);
        CHECK_NULL_BREAK(leftMaskNode);
        auto index = hostNode->GetChildIndexById(leftMaskNode->GetId());
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index, true);
        CHECK_NULL_BREAK(childWrapper);
        LayoutPageInColumn(childWrapper, ForceSplitPageColumnType::PRIMARY);
    } while (false);
    auto rightMaskNode = stagePattern->GetOrCreateMaskNode(false);
    CHECK_NULL_VOID(rightMaskNode);
    auto index = hostNode->GetChildIndexById(rightMaskNode->GetId());
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index, true);
    CHECK_NULL_VOID(childWrapper);
    LayoutPageInColumn(childWrapper, ForceSplitPageColumnType::SECONDARY);
}
} // namespace OHOS::Ace::NG
