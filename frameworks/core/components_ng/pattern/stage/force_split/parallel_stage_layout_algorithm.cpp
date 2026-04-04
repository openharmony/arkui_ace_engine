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

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Dimension DIVIDER_WIDTH = 1.0_px;
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
    auto primaryNode = stagePattern->GetPrimaryPage();
    if (primaryNode) {
        primaryIndex_ = hostNode->GetChildIndex(primaryNode);
    } else {
        primaryIndex_ = -1;
    }
    auto stageSize = static_cast<int32_t>(hostNode->GetChildren().size());
    if (stageSize <= 0) {
        return;
    }
    if (primaryIndex_ == -1) {
        // if primary page is not set, layout page in center position
        MeasureDetailPage(layoutWrapper->GetOrCreateChildByIndex(stageSize - 1));
        return;
    }
    SizeCalculationForForceSplit(hostNode, size);
    auto primaryPageWrapper = layoutWrapper->GetOrCreateChildByIndex(primaryIndex_);
    MeasurePage(primaryPageWrapper, leftSize_);
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
    MeasurePage(detailWrapper, rightSize_);
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

    LayoutInSplitMode(hostNode, layoutWrapper);
}

void ParallelStageLayoutAlgorithm::LayoutInSplitMode(const RefPtr<FrameNode>& hostNode, LayoutWrapper* layoutWrapper)
{
    auto stageSize = static_cast<int32_t>(hostNode->GetChildren().size());
    if (stageSize <= 0) {
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
    auto dividerOffset = leftSize_.Width();
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
    auto detailPageRatio = forceSplitMgr->GetSplitRatio();
    auto dividerWidth = DIVIDER_WIDTH.ConvertToPx();
    auto rightWidth = (size.Width() - dividerWidth) * detailPageRatio;
    auto leftWidth = size.Width() - rightWidth - dividerWidth;
    dividerSize_ = SizeF(dividerWidth, size.Height());
    leftSize_ = SizeF(leftWidth, size.Height());
    rightSize_ = SizeF(rightWidth, size.Height());
}
} // namespace OHOS::Ace::NG
