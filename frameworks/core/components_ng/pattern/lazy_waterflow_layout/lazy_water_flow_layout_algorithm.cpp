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

#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_algorithm.h"

#include <algorithm>
#include <cmath>

#include "base/log/log_wrapper.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_pattern.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_pattern.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_utils.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {

namespace {
void RestoreActiveFrameSubtree(const RefPtr<UINode>& node, bool isRoot = true)
{
    CHECK_NULL_VOID(node);
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    if (frameNode) {
        frameNode->SetActive(true);
        if (!isRoot && frameNode->GetPattern<LazyLayoutPattern>()) {
            return;
        }
    }
    for (const auto& child : node->GetChildren()) {
        RestoreActiveFrameSubtree(child, false);
    }
}
} // namespace

RefPtr<LayoutAlgorithm> CreateLazyWaterFlowLayoutAlgorithm(const RefPtr<LazyWaterFlowLayoutInfo>& info,
    const RefPtr<FrameNode>& header, const RefPtr<FrameNode>& footer)
{
    auto algorithm = AceType::MakeRefPtr<LazyWaterFlowLayoutAlgorithm>(info);
    algorithm->SetHeader(header);
    algorithm->SetFooter(footer);
    return algorithm;
}

void LazyWaterFlowLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    CHECK_NULL_VOID(layoutInfo_);
    auto layoutProperty = AceType::DynamicCast<LazyWaterFlowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto contentConstraintOpt = layoutProperty->GetContentLayoutConstraint();
    if (!contentConstraintOpt) {
        return;
    }
    auto contentConstraint = contentConstraintOpt.value();
    auto hostNode = layoutWrapper->GetHostNode();
    const bool fullRangeMeasure = LazyWaterFlowLayoutUtils::NeedFullRangeForDirectWaterFlow(hostNode) ||
        (contentConstraint.viewPosRef.has_value() && contentConstraint.viewPosRef->axis != Axis::VERTICAL);
    topAnchorRebased_ = false;

    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    auto contentIdealSize = CreateIdealSize(contentConstraint, Axis::VERTICAL, layoutProperty->GetMeasureType());
    LazyWaterFlowLayoutUtils::ResolveContentCrossSize(contentConstraint, contentIdealSize);

    realMainSize_ = geometryNode->GetPaddingSize().MainSize(Axis::VERTICAL);
    totalMainSize_ = layoutInfo_->totalMainSize_;
    keepEmptyLanesOutsideContent_ = false;
    UpdateHeaderFooterIndexes(layoutWrapper);
    totalItemCount_ = CalculateItemCount(layoutWrapper);
    UpdateGap(layoutProperty, contentIdealSize);

    auto childConstraint = layoutProperty->CreateChildConstraint();
    UpdateItemConstraints(contentIdealSize, childConstraint);
    // Edge sizes still hold last frame's values here.
    prevBodyMainSize_ = std::max(0.0f, totalMainSize_ - layoutInfo_->headerMainSize_ - layoutInfo_->footerMainSize_);
    MeasureHeader(layoutWrapper);
    MeasureFooter(layoutWrapper);
    UpdateReferencePos(layoutWrapper, contentConstraint.viewPosRef);
    isPredictPass_ = layoutInfo_->deadline_.has_value();
    ComposeChildStickyInsets(layoutWrapper);
    if (fullRangeMeasure) {
        LazyWaterFlowLayoutUtils::ExpandMeasureWindowToFullRange(viewStart_, viewEnd_, cacheStartPos_, cacheEndPos_);
        extendedViewStart_ = viewStart_;
        extendedViewEnd_ = viewEnd_;
    }
    MeasureItems(layoutWrapper);
    SetFrameSize(layoutWrapper, contentIdealSize, padding);
}

void LazyWaterFlowLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<LazyWaterFlowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    layoutDirection_ = layoutProperty->GetNonAutoLayoutDirection();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto paddingOffset = OffsetF(padding.left.value_or(0.0f), padding.top.value_or(0.0f));
    LayoutItems(layoutWrapper, paddingOffset);
    if (IsPredictPass()) {
        layoutInfo_->deadline_.reset();
    }
}

namespace {
struct FillLaneTarget {
    int32_t laneIdx = -1;
    float boundary = 0.0f;
    bool valid = false;
};

float GetLaneFrontBoundary(const LazyWaterFlowLane& lane, float mainGap)
{
    return lane.startPos - (lane.items_.empty() ? 0.0f : mainGap);
}

float GetLaneBackBoundary(const LazyWaterFlowLane& lane, float mainGap)
{
    return lane.endPos + (lane.items_.empty() ? 0.0f : mainGap);
}

FillLaneTarget SelectFrontFillTarget(int32_t startIndex, float bound, const std::vector<LazyWaterFlowLane>& lanes,
    const std::unordered_map<int32_t, size_t>& idxToLane, float mainGap)
{
    auto cachedLaneIter = idxToLane.find(startIndex);
    if (cachedLaneIter != idxToLane.end() && cachedLaneIter->second < lanes.size()) {
        auto laneIdx = static_cast<int32_t>(cachedLaneIter->second);
        return { laneIdx, GetLaneFrontBoundary(lanes[laneIdx], mainGap), true };
    }

    FillLaneTarget target;
    for (size_t index = 0; index < lanes.size(); ++index) {
        auto currentBoundary = GetLaneFrontBoundary(lanes[index], mainGap);
        if (LessOrEqual(currentBoundary, bound)) {
            continue;
        }
        // Reverse-fill tie-break: prepend into the larger lane index first.
        if (!target.valid || GreatNotEqualCustomPrecision(currentBoundary, target.boundary, 0.01f) ||
            (NearEqual(currentBoundary, target.boundary, 0.01f) && index > static_cast<size_t>(target.laneIdx))) {
            target = { static_cast<int32_t>(index), currentBoundary, true };
        }
    }
    return target;
}

FillLaneTarget SelectBackFillTarget(int32_t startIndex, float bound, const std::vector<LazyWaterFlowLane>& lanes,
    const std::unordered_map<int32_t, size_t>& idxToLane, float mainGap)
{
    auto cachedLaneIter = idxToLane.find(startIndex);
    if (cachedLaneIter != idxToLane.end() && cachedLaneIter->second < lanes.size()) {
        auto laneIdx = static_cast<int32_t>(cachedLaneIter->second);
        return { laneIdx, GetLaneBackBoundary(lanes[laneIdx], mainGap), true };
    }

    FillLaneTarget target;
    for (size_t index = 0; index < lanes.size(); ++index) {
        auto currentBoundary = GetLaneBackBoundary(lanes[index], mainGap);
        if (GreatOrEqual(currentBoundary, bound)) {
            continue;
        }
        if (!target.valid || LessNotEqualCustomPrecision(currentBoundary, target.boundary, -0.01f) ||
            (NearEqual(currentBoundary, target.boundary, 0.01f) && index < static_cast<size_t>(target.laneIdx))) {
            target = { static_cast<int32_t>(index), currentBoundary, true };
        }
    }
    return target;
}

float CollectMaxMainSize(const std::vector<LazyWaterFlowLane>& lanes, float baseMainSize)
{
    auto maxMainSize = baseMainSize;
    for (const auto& lane : lanes) {
        maxMainSize = std::max(maxMainSize, lane.endPos);
    }
    return maxMainSize;
}

float ResolveLaneBackItemStartPos(const LazyWaterFlowLane& lane, float mainGap)
{
    float mainPos = lane.startPos;
    float itemStartPos = lane.startPos;
    for (size_t itemIndex = 0; itemIndex < lane.items_.size(); ++itemIndex) {
        const auto& item = lane.items_[itemIndex];
        itemStartPos = mainPos + item.startOffset;
        auto itemEndPos = itemStartPos + item.mainSize;
        if (itemIndex + 1 < lane.items_.size()) {
            mainPos = itemEndPos + mainGap;
        }
    }
    return itemStartPos;
}

bool TryRecycleFrontItem(LazyWaterFlowLayoutInfo& layoutInfo, float bound, float mainGap)
{
    auto index = layoutInfo.StartIndex();
    if (index < 0) {
        return false;
    }
    auto* lane = layoutInfo.GetMutableLane(index);
    if (!lane || lane->items_.empty() || lane->items_.front().idx != index) {
        return false;
    }
    auto itemEndPos = lane->startPos + lane->items_.front().startOffset + lane->items_.front().mainSize;
    if (GreatNotEqual(itemEndPos, bound)) {
        return false;
    }
    lane->items_.pop_front();
    if (lane->items_.empty()) {
        lane->startPos = itemEndPos;
        lane->endPos = itemEndPos;
        return true;
    }
    lane->startPos = itemEndPos + mainGap;
    if (!NearZero(lane->items_.front().startOffset)) {
        lane->startPos += lane->items_.front().startOffset;
        lane->items_.front().startOffset = 0.0f;
    }
    return true;
}

bool TryRecycleBackItem(LazyWaterFlowLayoutInfo& layoutInfo, float bound, float mainGap)
{
    auto index = layoutInfo.EndIndex();
    if (index < 0) {
        return false;
    }
    auto* lane = layoutInfo.GetMutableLane(index);
    if (!lane || lane->items_.empty() || lane->items_.back().idx != index) {
        return false;
    }
    auto itemStartPos = ResolveLaneBackItemStartPos(*lane, mainGap);
    if (LessNotEqual(itemStartPos, bound)) {
        return false;
    }
    lane->items_.pop_back();
    if (lane->items_.empty()) {
        lane->startPos = itemStartPos;
        lane->endPos = itemStartPos;
    } else {
        lane->endPos = itemStartPos - mainGap;
    }
    return true;
}
} // namespace

void LazyWaterFlowLayoutAlgorithm::SetFrameSize(
    LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize, const PaddingPropertyF& padding)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto property = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto layoutConstraint = property->GetLayoutConstraint();
    if (!layoutConstraint) {
        return;
    }
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    OptionalSizeF frameSize;
    frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
    if (frameSize.IsValid()) {
        geometryNode->SetFrameSize(frameSize.ConvertToSizeT());
        return;
    }

    ApplyMainAxisExtentByLayoutPolicy(
        contentIdealSize, layoutConstraint.value(),
            property->GetLayoutPolicyProperty(), Axis::VERTICAL, totalMainSize_);

    AddPaddingToSize(padding, contentIdealSize);
    frameSize.UpdateIllegalSizeWithCheck(contentIdealSize);
    if (layoutConstraint->selfIdealSize.Width()) {
        frameSize.ConstrainFloat(minSize, maxSize, false, true);
    } else if (layoutConstraint->selfIdealSize.Height()) {
        frameSize.ConstrainFloat(minSize, maxSize, true, true);
    } else {
        frameSize.Constrain(minSize, maxSize, true);
    }
    frameSize.UpdateIllegalSizeWithCheck(SizeF(0.0f, 0.0f));
    geometryNode->SetFrameSize(frameSize.ConvertToSizeT());
}

std::optional<ViewPosReference> LazyWaterFlowLayoutAlgorithm::GetReferencePos(const RefPtr<FrameNode>& frameNode)
{
    return LazyLayoutUtils::GetViewPosReference(frameNode);
}

void LazyWaterFlowLayoutAlgorithm::ApplyFallbackReferencePos(
    LayoutWrapper* layoutWrapper, const std::optional<ViewPosReference>& posRef)
{
    referenceEdge_ = ReferenceEdge::START;
    startReferenceViewportOffset_ = 0.0f;
    auto hostNode = layoutWrapper->GetHostNode();
    const bool missingDirectWaterFlowRef =
        !posRef.has_value() && LazyLayoutUtils::HasDirectWaterFlowAncestor(hostNode);
    if (missingDirectWaterFlowRef) {
        TAG_LOGW(AceLogTag::ACE_LAZY_WATER_FLOW, "LazyWaterFlowLayout missing WaterFlow view reference");
    } else if (posRef.has_value()) {
        TAG_LOGW(AceLogTag::ACE_LAZY_WATER_FLOW,
            "LazyWaterFlowLayout received non-vertical view reference axis:%{public}d",
            static_cast<int32_t>(posRef.value().axis));
    }
    viewStart_ = 0.0f;
    viewEnd_ = ResolveFallbackMainSize(layoutWrapper);
    if (missingDirectWaterFlowRef && GreaterOrEqualToInfinity(viewEnd_)) {
        viewEnd_ = Positive(realMainSize_) ? realMainSize_ : 0.0f;
    }
    viewExtStart_ = 0.0f;
    viewExtEnd_ = 0.0f;
    stickyTopInset_ = 0.0f;
    stickyBottomInset_ = 0.0f;
    extendedViewStart_ = viewStart_;
    extendedViewEnd_ = viewEnd_;
    cacheStartPos_ = 0.0f;
    cacheEndPos_ = viewEnd_;
    MakeViewportBodyLocal();
}

void LazyWaterFlowLayoutAlgorithm::MakeViewportBodyLocal()
{
    // Translate the section viewport to body coords once; all window math downstream is body-local.
    const auto headerMainSize = layoutInfo_->headerMainSize_;
    if (NearZero(headerMainSize)) {
        return;
    }
    viewStart_ -= headerMainSize;
    viewEnd_ -= headerMainSize;
    extendedViewStart_ -= headerMainSize;
    extendedViewEnd_ -= headerMainSize;
    cacheStartPos_ -= headerMainSize;
    cacheEndPos_ -= headerMainSize;
}

void LazyWaterFlowLayoutAlgorithm::UpdateReferencePos(
    LayoutWrapper* layoutWrapper, std::optional<ViewPosReference>& posRef)
{
    CHECK_NULL_VOID(layoutWrapper);
    headerAdjustOffset_ = 0.0f;
    startReferenceViewportOffset_ = 0.0f;
    if (!posRef.has_value()) {
        posRef = GetReferencePos(layoutWrapper->GetHostNode());
    }
    if (!posRef.has_value() || posRef.value().axis != Axis::VERTICAL) {
        ApplyFallbackReferencePos(layoutWrapper, posRef);
        return;
    }

    referenceEdge_ = posRef.value().referenceEdge;
    if (!layoutInfo_->deadline_.has_value()) {
        layoutInfo_->deadline_ = posRef.value().deadline;
    }
    float referencePos = posRef.value().referencePos;
    viewExtStart_ = posRef.value().viewExtStart;
    viewExtEnd_ = posRef.value().viewExtEnd;
    if (posRef.value().referenceEdge == ReferenceEdge::START) {
        startReferenceViewportOffset_ = referencePos - posRef.value().viewPosStart;
    }
    stickyTopInset_ = posRef.value().stickyInsetStart;
    stickyBottomInset_ = posRef.value().stickyInsetEnd;
    if (posRef.value().referenceEdge == ReferenceEdge::START) {
        viewStart_ = posRef.value().viewPosStart - viewExtStart_ - referencePos;
        viewEnd_ = posRef.value().viewPosEnd + viewExtEnd_ - referencePos;
    } else {
        referencePos += totalMainSize_ - realMainSize_;
        viewStart_ = posRef.value().viewPosStart - viewExtStart_ - (referencePos - totalMainSize_);
        viewEnd_ = posRef.value().viewPosEnd + viewExtEnd_ - (referencePos - totalMainSize_);
    }
    extendedViewStart_ = viewStart_;
    extendedViewEnd_ = viewEnd_;
    const auto viewSize = posRef.value().viewPosEnd - posRef.value().viewPosStart;
    const auto cacheExtent = viewSize * cacheSize_;
    cacheStartPos_ = viewStart_ - cacheExtent;
    cacheEndPos_ = viewEnd_ + cacheExtent;
    MakeViewportBodyLocal();
    UpdateHeaderAdjustOffset();
}

void LazyWaterFlowLayoutAlgorithm::UpdateGap(
    const RefPtr<LazyWaterFlowLayoutProperty>& layoutProperty, const OptionalSizeF& selfIdealSize)
{
    CHECK_NULL_VOID(layoutProperty);
    auto contentConstraintOpt = layoutProperty->GetContentLayoutConstraint();
    if (!contentConstraintOpt) {
        return;
    }
    auto contentConstraint = contentConstraintOpt.value();
    auto mainPercentRefer = GetMainAxisSize(contentConstraint.percentReference, Axis::VERTICAL);
    auto rowGapDim = layoutProperty->GetRowGap().value_or(Dimension(0));
    auto columnGapDim = layoutProperty->GetColumnGap().value_or(Dimension(0));
    mainGap_ = std::max(ConvertToPx(rowGapDim, contentConstraint.scaleProperty, mainPercentRefer).value_or(0.0f), 0.0f);
    crossGap_ =
        std::max(ConvertToPx(columnGapDim, contentConstraint.scaleProperty, mainPercentRefer).value_or(0.0f), 0.0f);

    crossSize_ = selfIdealSize.CrossSize(Axis::VERTICAL).value_or(
        GetCrossAxisSize(contentConstraint.percentReference, Axis::VERTICAL));
    auto columnsTemplate = LazyWaterFlowLayoutUtils::ResolveColumnsTemplate(layoutProperty, crossSize_,
        contentConstraint);
    auto cross = ParseTemplateArgs(columnsTemplate, crossSize_, crossGap_, totalItemCount_);
    crossGap_ = cross.second;
    if (cross.first.empty()) {
        cross.first = { crossSize_ };
    }
    crossLens_ = std::move(cross.first);
    laneEndPos_.assign(crossLens_.size(), 0.0f);
    LazyWaterFlowLayoutUtils::BuildLaneCrossPositions(crossLens_, crossGap_, crossPos_);
}

void LazyWaterFlowLayoutAlgorithm::UpdateItemConstraints(
    const OptionalSizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    auto fullCrossSize = selfIdealSize.CrossSize(Axis::VERTICAL).value_or(
        GetCrossAxisSize(contentConstraint.percentReference, Axis::VERTICAL));
    // Header/footer always measure against the full section width instead of a single lane width.
    edgeLayoutConstraint_ = contentConstraint;
    edgeLayoutConstraint_.parentIdealSize = selfIdealSize;
    edgeLayoutConstraint_.maxSize.SetMainSize(Infinity<float>(), Axis::VERTICAL);
    edgeLayoutConstraint_.percentReference.SetCrossSize(fullCrossSize, Axis::VERTICAL);
    edgeLayoutConstraint_.parentIdealSize.SetCrossSize(fullCrossSize, Axis::VERTICAL);
    edgeLayoutConstraint_.maxSize.SetCrossSize(fullCrossSize, Axis::VERTICAL);
    edgeLayoutConstraint_.viewPosRef.reset();

    childLayoutConstraints_.clear();
    childLayoutConstraints_.reserve(crossLens_.size());
    for (auto crossSize : crossLens_) {
        auto childConstraint = contentConstraint;
        childConstraint.parentIdealSize = selfIdealSize;
        childConstraint.maxSize.SetMainSize(Infinity<float>(), Axis::VERTICAL);
        childConstraint.percentReference.SetCrossSize(crossSize, Axis::VERTICAL);
        childConstraint.parentIdealSize.SetCrossSize(crossSize, Axis::VERTICAL);
        childConstraint.maxSize.SetCrossSize(crossSize, Axis::VERTICAL);
        childConstraint.viewPosRef.reset();
        childLayoutConstraints_.emplace_back(childConstraint);
    }
}

int32_t LazyWaterFlowLayoutAlgorithm::CalculateItemCount(LayoutWrapper* layoutWrapper) const
{
    CHECK_NULL_RETURN(layoutWrapper, 0);
    return HeaderFooterUtils::CalcContentItemCount(layoutWrapper->GetTotalChildCount(), headerIndex_, footerIndex_);
}

void LazyWaterFlowLayoutAlgorithm::UpdateHeaderFooterIndexes(LayoutWrapper* layoutWrapper)
{
    HeaderFooterUtils::ResolveEdgeIndexes<LazyWaterFlowLayoutPattern>(
        layoutWrapper, header_, footer_, headerIndex_, footerIndex_);
}

int32_t LazyWaterFlowLayoutAlgorithm::GetRawIndexForItem(int32_t itemIndex) const
{
    return itemIndex + (headerIndex_ >= 0 ? 1 : 0);
}

StickyStyle LazyWaterFlowLayoutAlgorithm::ResolveStickyStyle(LayoutWrapper* layoutWrapper) const
{
    CHECK_NULL_RETURN(layoutWrapper, StickyStyle::NONE);
    auto layoutProperty = AceType::DynamicCast<LazyWaterFlowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, StickyStyle::NONE);
    return layoutProperty->GetStickyStyle().value_or(StickyStyle::NONE);
}

bool LazyWaterFlowLayoutAlgorithm::CheckNeedMeasure(const RefPtr<LayoutWrapper>& layoutWrapper, int32_t laneIdx) const
{
    CHECK_NULL_RETURN(layoutWrapper, true);
    if (laneIdx < 0 || laneIdx >= static_cast<int32_t>(childLayoutConstraints_.size())) {
        return true;
    }
    if (layoutWrapper->CheckNeedForceMeasureAndLayout()) {
        return true;
    }
    auto childLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(childLayoutProperty, true);
    if (childLayoutProperty->GetNeedLazyLayout()) {
        // Nested lazy children need a fresh viewPosRef every frame.
        return true;
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    auto constraint = geometryNode->GetParentLayoutConstraint();
    CHECK_NULL_RETURN(constraint, true);
    return constraint.value() != childLayoutConstraints_[laneIdx];
}

float LazyWaterFlowLayoutAlgorithm::ResolveFallbackMainSize(LayoutWrapper* layoutWrapper) const
{
    CHECK_NULL_RETURN(layoutWrapper, Infinity<float>());
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, Infinity<float>());
    auto frameMainSize = geometryNode->GetFrameSize().MainSize(Axis::VERTICAL);
    if (Positive(frameMainSize) && !GreaterOrEqualToInfinity(frameMainSize)) {
        return frameMainSize;
    }
    auto constraint = geometryNode->GetParentLayoutConstraint();
    if (constraint.has_value()) {
        auto maxMainSize = GetMainAxisSize(constraint->maxSize, Axis::VERTICAL);
        if (Positive(maxMainSize) && !GreaterOrEqualToInfinity(maxMainSize)) {
            return maxMainSize;
        }
        auto percentMainSize = GetMainAxisSize(constraint->percentReference, Axis::VERTICAL);
        if (Positive(percentMainSize) && !GreaterOrEqualToInfinity(percentMainSize)) {
            return percentMainSize;
        }
    }
    return Infinity<float>();
}

bool LazyWaterFlowLayoutAlgorithm::IsPredictPass() const
{
    return isPredictPass_;
}

bool LazyWaterFlowLayoutAlgorithm::IsDeadlineReached() const
{
    return IsPredictPass() && layoutInfo_->deadline_.has_value() && GetSysTimestamp() > layoutInfo_->deadline_.value();
}

void LazyWaterFlowLayoutAlgorithm::MeasureItems(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    CHECK_NULL_VOID(layoutInfo_);
    laneTopologyChanged_ = false;
    PrevFrameSnapshot prevFrameSnapshot;
    if (!PrepareMeasureItems(layoutWrapper, prevFrameSnapshot)) {
        return;
    }

    SyncLaneGeometry();
    const int32_t resetFrom = CheckReset();
    float maxMainSize = 0.0f;
    if (totalItemCount_ > 0 && !layoutInfo_->lanes_.empty()) {
        const auto frontBoundary = ResolveFrontBoundary();
        const auto backBoundary = ResolveBackBoundary();
        RefillLaneWindow(layoutWrapper, resetFrom, frontBoundary, backBoundary, maxMainSize);
        ReMeasureItems(layoutWrapper);
        maxMainSize = CollectMaxMainSize(layoutInfo_->lanes_, 0.0f);
    }

    // Boundary edge-trigger snap. Skipped on predict so transient predict frames cannot overwrite
    // totalOffset_ / maxHeight_. Runs before FinishMeasureItems so the staleness check sees the parent's
    // last-frame totalMainSize_ belief.
    if (!IsPredictPass() && totalItemCount_ > 0 && !layoutInfo_->lanes_.empty()) {
        DetectItemBoundary();
        if (layoutInfo_->itemStart_ && !layoutInfo_->prevItemStart_) {
            const float previousTotalOffset = layoutInfo_->totalOffset_;
            AlignFrontTotalOffset();
            // Internal correction; suppress the anchor diff to avoid a spurious scroll past the real top.
            topAnchorRebased_ = topAnchorRebased_ ||
                (!layoutInfo_->hasDataChange_ && !NearEqual(layoutInfo_->totalOffset_, previousTotalOffset));
        }
        if (layoutInfo_->itemEnd_ && !layoutInfo_->prevItemEnd_) {
            AlignBackMaxHeight();
        }
        layoutInfo_->prevItemStart_ = layoutInfo_->itemStart_;
        layoutInfo_->prevItemEnd_ = layoutInfo_->itemEnd_;
    }

    FinishMeasureItems(layoutWrapper, prevFrameSnapshot, maxMainSize);
}

// Pick the row whose top is closest to (but not above) frontBoundary using GetAverageItemHeight; {0,0} when
// no usable estimate is available.
LazyWaterFlowLayoutAlgorithm::FillAnchor LazyWaterFlowLayoutAlgorithm::EstimateFillAnchorFromFront(
    float frontBoundary) const
{
    FillAnchor anchor { 0, 0.0f };
    if (totalItemCount_ <= 0 || layoutInfo_->lanes_.empty() ||
        !GreatNotEqual(frontBoundary, 0.0f)) {
        return anchor;
    }
    const float average = layoutInfo_->GetAverageItemHeight();
    if (!Positive(average)) {
        return anchor;
    }
    const auto laneCount = static_cast<int32_t>(layoutInfo_->lanes_.size());
    const float step = average + mainGap_;
    const float rowsBefore =
        std::max(std::floor(frontBoundary / step), 0.0f);
    anchor.fillStart = std::clamp(
        static_cast<int32_t>(rowsBefore * static_cast<float>(laneCount)),
        0, totalItemCount_ - 1);
    // Re-derive laneBase from the clamped fillStart so the last partial row doesn't overshoot content end.
    const float clampedRowsBefore = std::floor(static_cast<float>(anchor.fillStart) /
        static_cast<float>(std::max(laneCount, 1)));
    anchor.laneBase = clampedRowsBefore * step;
    return anchor;
}

// Rebase to (0, item 0) when the viewport sits at the content origin. Without this short-circuit the
// ClearFront/FillFront path can leave lane.startPos < 0 and subsequent frames never place 0..N-1.
// Skipped on hasDataChange_ so CheckReset's preserve route owns data-driven repositioning.
bool LazyWaterFlowLayoutAlgorithm::TryTopEdgeAnchorRefill(
    LayoutWrapper* layoutWrapper, float backBoundary, float& maxMainSize)
{
    constexpr float TOP_EDGE_EPSILON = 1.0f;
    // Section coords: body-local viewStart_ goes negative under the header, and a mid-scroll header resize
    // must not read as "at content top".
    const float topGap = viewStart_ + layoutInfo_->headerMainSize_;
    const bool atTop = topGap <= TOP_EDGE_EPSILON && GreatNotEqual(viewEnd_, 0.0f);
    if (IsPredictPass() || layoutInfo_->hasDataChange_ || !atTop || totalItemCount_ <= 0) {
        return false;
    }
    layoutInfo_->ResetWithLaneOffset(0.0f);
    layoutInfo_->totalOffset_ = 0.0f;
    maxMainSize = 0.0f;
    topAnchorRebased_ = true;
    FillBack(layoutWrapper, backBoundary, 0, totalItemCount_ - 1, maxMainSize);
    return true;
}

// Viewport sits well above the retained window: estimate fillStart, rebase lanes, refill forward. Avoids
// FillFront prepending hundreds of items one-by-one. Skipped on hasDataChange_ (CheckReset owns that path).
bool LazyWaterFlowLayoutAlgorithm::TryTopJumpRefill(
    LayoutWrapper* layoutWrapper, float frontBoundary, float backBoundary, float& maxMainSize)
{
    if (IsPredictPass() || layoutInfo_->hasDataChange_ || layoutInfo_->lanes_.empty() ||
        totalItemCount_ <= 0) {
        return false;
    }
    const float retainedFront = layoutInfo_->ResolveLaneFrontPos();
    constexpr float JUMP_GAP_EPSILON = 0.5f;
    if (!LessNotEqualCustomPrecision(backBoundary, retainedFront, -JUMP_GAP_EPSILON)) {
        return false;
    }
    if (!Positive(layoutInfo_->GetAverageItemHeight())) {
        return false;
    }
    const auto anchor = EstimateFillAnchorFromFront(frontBoundary);
    layoutInfo_->ResetWithLaneOffset(anchor.laneBase);
    layoutInfo_->totalOffset_ = 0.0f;
    maxMainSize = std::max(maxMainSize, anchor.laneBase);
    topAnchorRebased_ = true;
    FillBack(layoutWrapper, backBoundary, anchor.fillStart, totalItemCount_ - 1, maxMainSize);
    return true;
}

bool LazyWaterFlowLayoutAlgorithm::TryKeepEmptyLanesOutsideVisibleContent(float& maxMainSize)
{
    // A fully offscreen child stays empty unless the parent-expanded view reaches content or the
    // current parent predict pass can begin preloading the overlapping cache window.
    // Floor last frame's belief with the current one: the post-rebase second refill already holds this
    // frame's real total, while the first call must not mix the stale section total with the new header.
    const float bodyEnd = std::max(prevBodyMainSize_, GetBodyMainSize());
    const bool beforeContent = LessOrEqual(extendedViewEnd_, 0.0f);
    const bool afterContent = GreatNotEqual(extendedViewStart_, bodyEnd);
    const bool extendedViewOutsideContent = beforeContent || afterContent;
    const bool cacheOverlapsContent = GreatNotEqual(cacheEndPos_, 0.0f) &&
        LessNotEqual(cacheStartPos_, bodyEnd);
    const bool allowPredictCacheFill = IsPredictPass() && cacheOverlapsContent;
    if (layoutInfo_->hasDataChange_ || totalItemCount_ <= 0 || !Positive(totalMainSize_) ||
        !extendedViewOutsideContent || allowPredictCacheFill) {
        return false;
    }
    layoutInfo_->ResetWithLaneOffset(afterContent ? bodyEnd : 0.0f);
    maxMainSize = std::max(maxMainSize, bodyEnd);
    keepEmptyLanesOutsideContent_ = true;
    return true;
}

// Used when ClearFront emptied every lane: covers initial measure / scroll-to-top (estimate -> {0, 0})
// and jump-past-measured-items (estimate avoids placing item 0 at the cleared-window bottom).
void LazyWaterFlowLayoutAlgorithm::RefillFromEmptyLanes(
    LayoutWrapper* layoutWrapper, float frontBoundary, float backBoundary, float& maxMainSize)
{
    const auto anchor = EstimateFillAnchorFromFront(frontBoundary);
    layoutInfo_->ResetWithLaneOffset(anchor.laneBase);
    maxMainSize = std::max(maxMainSize, anchor.laneBase);
    FillBack(layoutWrapper, backBoundary, anchor.fillStart, totalItemCount_ - 1, maxMainSize);
}

void LazyWaterFlowLayoutAlgorithm::RefillLaneWindow(LayoutWrapper* layoutWrapper, int32_t resetFrom,
    float frontBoundary, float backBoundary, float& maxMainSize)
{
    if (resetFrom >= 0) {
        maxMainSize = CollectMaxMainSize(layoutInfo_->lanes_, 0.0f);
        FillBack(layoutWrapper, backBoundary, resetFrom, totalItemCount_ - 1, maxMainSize);
        return;
    }
    if (TryKeepEmptyLanesOutsideVisibleContent(maxMainSize)) {
        return;
    }
    if (TryTopEdgeAnchorRefill(layoutWrapper, backBoundary, maxMainSize)) {
        return;
    }
    if (TryTopJumpRefill(layoutWrapper, frontBoundary, backBoundary, maxMainSize)) {
        return;
    }
    // Clear at the cache window so half-screen cache items survive scroll frames.
    ClearFront(cacheStartPos_);
    ClearBack(cacheEndPos_);
    maxMainSize = CollectMaxMainSize(layoutInfo_->lanes_, 0.0f);

    const auto startIndex = layoutInfo_->StartIndex();
    const auto endIndex = layoutInfo_->EndIndex();
    if (startIndex < 0 || endIndex < 0) {
        RefillFromEmptyLanes(layoutWrapper, frontBoundary, backBoundary, maxMainSize);
        return;
    }
    FillFront(layoutWrapper, frontBoundary, startIndex - 1, 0, maxMainSize);
    // totalOffset_ is intentionally not written here; mutators are CheckReset preserve, Reset/ClearDataFrom,
    // and the AlignFrontTotalOffset edge-trigger. Stable totalOffset_ during scroll keeps adjustOffset at 0
    // so the parent gesture matches exactly.
    FillBack(layoutWrapper, backBoundary, endIndex + 1, totalItemCount_ - 1, maxMainSize);
}

LazyWaterFlowLayoutAlgorithm::PrevFrameSnapshot LazyWaterFlowLayoutAlgorithm::CapturePrevFrameSnapshot() const
{
    if (layoutInfo_->hasPendingAdjustAnchor_) {
        return { layoutInfo_->pendingAnchor_ };
    }
    return {
        LazyWaterFlowAnchorSnapshot {
            .startIndex = layoutInfo_->startIndex_,
            .endIndex = layoutInfo_->endIndex_,
            .startPos = GetRememberedItemPosition(layoutInfo_->startIndex_),
            .endPos = GetRememberedItemPosition(layoutInfo_->endIndex_),
            // Body delta baseline: a pure edge resize must yield adjustOffset_ == {0,0}.
            .totalMainSize = prevBodyMainSize_,
        },
    };
}

OffsetF LazyWaterFlowLayoutAlgorithm::ResolveItemOffset(
    const OffsetF& paddingOffset, int32_t laneIdx, float childCrossSize, float mainPos) const
{
    // Body-local: posMap_/lanes are body coords; shift items down by the header at layout time.
    const float mainOffset = paddingOffset.GetY() + mainPos + layoutInfo_->headerMainSize_;
    if (laneIdx < 0 || laneIdx >= static_cast<int32_t>(crossPos_.size())) {
        return OffsetF(paddingOffset.GetX(), mainOffset);
    }
    auto laneOffset = static_cast<float>(crossPos_[laneIdx]);
    auto crossOffset = paddingOffset.GetX() + laneOffset;
    if (layoutDirection_ == TextDirection::RTL) {
        crossOffset = paddingOffset.GetX() + crossSize_ - childCrossSize - laneOffset;
    }
    return OffsetF(crossOffset, mainOffset);
}

std::optional<LazyWaterFlowItemMainPos> LazyWaterFlowLayoutAlgorithm::GetRememberedItemPositionInLane(
    int32_t index, size_t laneIdx) const
{
    CHECK_NULL_RETURN(layoutInfo_, std::nullopt);
    if (laneIdx >= layoutInfo_->lanes_.size()) {
        return std::nullopt;
    }
    const auto& lane = layoutInfo_->lanes_[laneIdx];
    auto mainPos = lane.startPos;
    for (size_t itemIndex = 0; itemIndex < lane.items_.size(); ++itemIndex) {
        const auto& item = lane.items_[itemIndex];
        auto itemStart = mainPos + item.startOffset;
        auto itemEnd = itemStart + item.mainSize;
        if (item.idx == index) {
            return LazyWaterFlowItemMainPos {
                .laneIdx = static_cast<int32_t>(laneIdx),
                .startPos = itemStart,
                .endPos = itemEnd,
            };
        }
        mainPos = itemEnd;
        if (itemIndex + 1 < lane.items_.size()) {
            mainPos += mainGap_;
        }
    }
    return std::nullopt;
}

std::optional<LazyWaterFlowItemMainPos> LazyWaterFlowLayoutAlgorithm::GetRememberedItemPosition(int32_t index) const
{
    if (index < 0) {
        return std::nullopt;
    }
    auto cachedLaneIter = layoutInfo_->idxToLane_.find(index);
    if (cachedLaneIter != layoutInfo_->idxToLane_.end()) {
        auto rememberedPos = GetRememberedItemPositionInLane(index, cachedLaneIter->second);
        if (rememberedPos.has_value()) {
            return rememberedPos;
        }
    }
    auto itemPos = layoutInfo_->GetPos(index);
    return itemPos ? std::optional<LazyWaterFlowItemMainPos>(*itemPos) : std::nullopt;
}

bool LazyWaterFlowLayoutAlgorithm::PrepareMeasureItems(
    LayoutWrapper* layoutWrapper, PrevFrameSnapshot& prevFrameSnapshot)
{
    prevFrameSnapshot = CapturePrevFrameSnapshot();
    layoutInfo_->ResetPerFrameState();
    layoutInfo_->SetTotalItemCount(totalItemCount_);
    if (childLayoutConstraints_.empty()) {
        totalMainSize_ = 0.0f;
        return false;
    }

    const bool needsLaneRebuild = layoutInfo_->UpdateLaneCrossLens(crossLens_);
    if (needsLaneRebuild) {
        // Topology change: flag the laneTopologyChanged_ short-circuit so UpdateAdjustOffset stays neutral.
        laneTopologyChanged_ = true;
        layoutInfo_->ResetLanes(static_cast<int32_t>(crossLens_.size()), 0.0f);
    }
    // Lanes anchor at 0: an edge resize needs no lane shift.
    return true;
}

void LazyWaterFlowLayoutAlgorithm::MeasureHeader(LayoutWrapper* layoutWrapper)
{
    const float headerMainSize = HeaderFooterUtils::MeasureEdgeMainSize(
        layoutWrapper, header_, headerIndex_, edgeLayoutConstraint_, Axis::VERTICAL);
    headerMainSizeDelta_ = headerMainSize - layoutInfo_->headerMainSize_;
    layoutInfo_->headerMainSize_ = headerMainSize;
}

void LazyWaterFlowLayoutAlgorithm::MeasureFooter(LayoutWrapper* layoutWrapper)
{
    layoutInfo_->footerMainSize_ = HeaderFooterUtils::MeasureEdgeMainSize(
        layoutWrapper, footer_, footerIndex_, edgeLayoutConstraint_, Axis::VERTICAL);
}

void LazyWaterFlowLayoutAlgorithm::UpdateHeaderAdjustOffset()
{
    // END-edge windows anchor the bottom (RebaseEndReferenceToCurrentSize absorbs section growth): no compensation.
    if (referenceEdge_ != ReferenceEdge::START || NearZero(headerMainSizeDelta_) ||
        layoutInfo_->deadline_.has_value()) {
        return;
    }
    // First lazy frame: the "delta" is the header's full size and there is no parent anchor to preserve.
    const bool hadMeasuredItems = Positive(prevBodyMainSize_) || !layoutInfo_->posMap_.empty();
    if (!hadMeasuredItems) {
        return;
    }
    headerAdjustOffset_ =
        HeaderFooterUtils::CalcHeaderResizeAdjust(headerMainSizeDelta_, viewStart_, layoutInfo_->headerMainSize_);
}

void LazyWaterFlowLayoutAlgorithm::ComposeChildStickyInsets(LayoutWrapper* layoutWrapper)
{
    const auto stickyStyle = ResolveStickyStyle(layoutWrapper);
    childStickyTopInset_ =
        stickyTopInset_ + (HeaderFooterUtils::IsHeaderSticky(stickyStyle) ? layoutInfo_->headerMainSize_ : 0.0f);
    childStickyBottomInset_ =
        stickyBottomInset_ + (HeaderFooterUtils::IsFooterSticky(stickyStyle) ? layoutInfo_->footerMainSize_ : 0.0f);
}

void LazyWaterFlowLayoutAlgorithm::SyncLaneGeometry()
{
    for (auto& lane : layoutInfo_->lanes_) {
        if (lane.items_.empty()) {
            lane.endPos = lane.startPos;
            continue;
        }
        if (!NearZero(lane.items_.front().startOffset)) {
            lane.startPos += lane.items_.front().startOffset;
            lane.items_.front().startOffset = 0.0f;
        }
        float mainPos = lane.startPos;
        float endPos = lane.startPos;
        for (size_t itemIndex = 0; itemIndex < lane.items_.size(); ++itemIndex) {
            auto itemStart = mainPos + lane.items_[itemIndex].startOffset;
            endPos = itemStart + lane.items_[itemIndex].mainSize;
            mainPos = endPos;
            if (itemIndex + 1 < lane.items_.size()) {
                mainPos += mainGap_;
            }
        }
        lane.endPos = endPos;
    }
}

// Fill/Clear use the cache window so scroll frames synchronously materialize the half-screen buffer.
float LazyWaterFlowLayoutAlgorithm::ResolveFrontBoundary() const
{
    return cacheStartPos_;
}

float LazyWaterFlowLayoutAlgorithm::ResolveBackBoundary() const
{
    return cacheEndPos_;
}

int32_t LazyWaterFlowLayoutAlgorithm::CheckReset()
{
    CHECK_NULL_RETURN(layoutInfo_, -1);
    if (!layoutInfo_->hasDataChange_) {
        return -1;
    }
    const int32_t updateIdx = layoutInfo_->updatedStart_;

    if (layoutInfo_->newStartIndex_ >= 0) {
        // Preserve fast path: index remap, refresh totalOffset_, and release the boundary latch so
        // DetectItemBoundary can re-fire on the next user-driven hit.
        const int32_t prevStart = layoutInfo_->StartIndex();
        layoutInfo_->UpdateLanesIndex(updateIdx);
        layoutInfo_->FinalizeAfterDataChangeReset(prevStart, layoutInfo_->StartIndex(), mainGap_);
        return -1;
    }

    if (updateIdx < 0) {
        return -1;
    }
    const auto windowStart = layoutInfo_->StartIndex();
    const auto windowEnd = layoutInfo_->EndIndex();
    if (windowStart < 0 || windowEnd < windowStart) {
        return -1;
    }
    if (updateIdx <= windowStart) {
        // Front anchor dirty: rebuild from the dirty index so the refreshed prefix item can drive adjustOffset.
        layoutInfo_->ResetWithLaneOffset(std::nullopt);
        layoutInfo_->maxHeight_ = 0.0f;
        const int32_t resetFrom = std::clamp(updateIdx, 0, totalItemCount_ - 1);
        layoutInfo_->FinalizeAfterDataChangeReset(windowStart, resetFrom, mainGap_);
        return resetFrom;
    }
    if (updateIdx > windowEnd) {
        // Change past the retained window: lane geometry is fine and a sticky maxHeight_ is wanted in the
        // mid-scroll case. The exception is a tail-delete that puts the window over the new tail while
        // maxHeight_ still tracks now-gone body. Double-gate that case before clearing.
        const bool retainedWindowReachedTail = windowEnd >= totalItemCount_ - 1;
        if (retainedWindowReachedTail) {
            float maxLaneEnd = 0.0f;
            for (const auto& lane : layoutInfo_->lanes_) {
                maxLaneEnd = std::max(maxLaneEnd, lane.endPos);
            }
            if (LessNotEqual(maxLaneEnd, layoutInfo_->maxHeight_)) {
                layoutInfo_->maxHeight_ = 0.0f;
                layoutInfo_->ResetBoundaryLatch();
            }
        }
        return -1;
    }
    // Middle dirty: preserve prefix, rebuild tail from updateIdx onward.
    layoutInfo_->maxHeight_ = 0.0f;
    layoutInfo_->ClearDataFrom(updateIdx, mainGap_);
    layoutInfo_->FinalizeAfterDataChangeReset(windowStart, layoutInfo_->StartIndex(), mainGap_);
    return updateIdx;
}

void LazyWaterFlowLayoutAlgorithm::DetectItemBoundary()
{
    // Rewrites itemStart_/itemEnd_ each frame; edge-trigger is enforced by the caller via prev*.
    // Intentional staleness: layoutInfo_->totalMainSize_ is the LAST frame's value (parent's current
    // belief); comparing viewEnd_ against it gates the back snap to a real-bottom hit, not a transient
    // through-cache materialization.
    CHECK_NULL_VOID(layoutInfo_);
    layoutInfo_->itemStart_ = false;
    layoutInfo_->itemEnd_ = false;
    if (totalItemCount_ <= 0 || layoutInfo_->lanes_.empty()) {
        return;
    }
    const int32_t laneStartIdx = layoutInfo_->StartIndex();
    const int32_t laneEndIdx = layoutInfo_->EndIndex();
    if (laneStartIdx == 0 && LessOrEqual(viewStart_, 0.0f)) {
        layoutInfo_->itemStart_ = true;
    }
    float maxLaneEnd = 0.0f;
    float realContentEnd = 0.0f;
    if (laneEndIdx == totalItemCount_ - 1) {
        for (const auto& lane : layoutInfo_->lanes_) {
            maxLaneEnd = std::max(maxLaneEnd, lane.endPos);
        }
        // lane.endPos is in self-local content coords; the realContentEnd just needs the footer added.
        realContentEnd = maxLaneEnd + layoutInfo_->footerMainSize_;
        // Both gates: content fits in view AND the parent's totalMainSize_ <= view (otherwise mid-scroll
        // materialization through cache would let the snap shrink the scrollable area under the gesture).
        // viewEnd_ is body-local vs the section total; add the header back for a like-for-like comparison.
        if (LessOrEqual(realContentEnd, viewEnd_) &&
            GreatOrEqual(viewEnd_ + layoutInfo_->headerMainSize_, layoutInfo_->totalMainSize_)) {
            layoutInfo_->itemEnd_ = true;
        }
    }
}

void LazyWaterFlowLayoutAlgorithm::AlignFrontTotalOffset()
{
    CHECK_NULL_VOID(layoutInfo_);
    // Goal: lane front aligned to 0; totalOffset_ stays 0 since the alignment is fully baked into lane geometry.
    const float frontPos = layoutInfo_->ResolveLaneFrontPos();
    const float shift = -frontPos;
    if (!NearZero(shift)) {
        for (auto& lane : layoutInfo_->lanes_) {
            lane.startPos += shift;
            lane.endPos += shift;
        }
    }
    layoutInfo_->totalOffset_ = 0.0f;
}

void LazyWaterFlowLayoutAlgorithm::AlignBackMaxHeight()
{
    CHECK_NULL_VOID(layoutInfo_);
    float maxLaneEnd = 0.0f;
    for (const auto& lane : layoutInfo_->lanes_) {
        maxLaneEnd = std::max(maxLaneEnd, lane.endPos);
    }
    // Direct assignment is the point of the snap: deliberately collapse any over-estimate accumulated during
    // scroll back to the real body height once the user is at bottom.
    const float realBodyHeight = std::max(0.0f, maxLaneEnd);
    layoutInfo_->maxHeight_ = realBodyHeight;
}

bool LazyWaterFlowLayoutAlgorithm::AreFrontLanesCovered(float bound) const
{
    return std::all_of(layoutInfo_->lanes_.begin(), layoutInfo_->lanes_.end(), [this, bound](const auto& lane) {
        auto nextPos = lane.startPos - (lane.items_.empty() ? 0.0f : mainGap_);
        return LessOrEqual(nextPos, bound);
    });
}

bool LazyWaterFlowLayoutAlgorithm::AreBackLanesCovered(float bound) const
{
    return std::all_of(layoutInfo_->lanes_.begin(), layoutInfo_->lanes_.end(), [this, bound](const auto& lane) {
        auto nextPos = lane.endPos + (lane.items_.empty() ? 0.0f : mainGap_);
        return GreatOrEqual(nextPos, bound);
    });
}

void LazyWaterFlowLayoutAlgorithm::ClearFront(float bound)
{
    // Iterate by lowest idx (not per-lane) to preserve the continuous-index invariant FillFront relies on.
    CHECK_NULL_VOID(layoutInfo_);
    while (TryRecycleFrontItem(*layoutInfo_, bound, mainGap_)) {
    }
}

void LazyWaterFlowLayoutAlgorithm::ClearBack(float bound)
{
    if (!std::isfinite(bound)) {
        return;
    }
    CHECK_NULL_VOID(layoutInfo_);
    while (TryRecycleBackItem(*layoutInfo_, bound, mainGap_)) {
    }
}

void LazyWaterFlowLayoutAlgorithm::FillFront(
    LayoutWrapper* layoutWrapper, float bound, int32_t startIndex, int32_t minIndex, float& maxMainSize)
{
    startIndex = std::min(startIndex, totalItemCount_ - 1);
    minIndex = std::max(minIndex, 0);
    while (startIndex >= minIndex && !layoutInfo_->lanes_.empty()) {
        if (IsDeadlineReached() || AreFrontLanesCovered(bound)) {
            break;
        }
        auto target = SelectFrontFillTarget(startIndex, bound, layoutInfo_->lanes_, layoutInfo_->idxToLane_, mainGap_);
        if (!target.valid) {
            break;
        }
        auto& lane = layoutInfo_->lanes_[target.laneIdx];
        auto endPos = target.boundary;
        auto childMainSize = MeasureChild(layoutWrapper, startIndex, target.laneIdx, endPos, ReferenceEdge::END);
        if (!childMainSize.has_value()) {
            break;
        }
        if (lane.items_.empty()) {
            lane.endPos = endPos;
        }
        lane.startPos = endPos - childMainSize.value();
        lane.items_.push_front({ startIndex, childMainSize.value() });
        layoutInfo_->idxToLane_[startIndex] = static_cast<size_t>(target.laneIdx);
        maxMainSize = std::max(maxMainSize, lane.endPos);
        --startIndex;
    }
}

void LazyWaterFlowLayoutAlgorithm::FillBack(
    LayoutWrapper* layoutWrapper, float bound, int32_t startIndex, int32_t maxIndex, float& maxMainSize)
{
    startIndex = std::max(startIndex, 0);
    maxIndex = std::min(maxIndex, totalItemCount_ - 1);
    while (startIndex <= maxIndex && !layoutInfo_->lanes_.empty()) {
        if (IsDeadlineReached() || AreBackLanesCovered(bound)) {
            break;
        }
        // Append into the shortest lane, matching WaterFlow forward-fill behavior.
        auto target = SelectBackFillTarget(startIndex, bound, layoutInfo_->lanes_, layoutInfo_->idxToLane_, mainGap_);
        if (!target.valid) {
            break;
        }
        auto& lane = layoutInfo_->lanes_[target.laneIdx];
        auto startPos = target.boundary;
        auto childMainSize = MeasureChild(layoutWrapper, startIndex, target.laneIdx, startPos, ReferenceEdge::START);
        if (!childMainSize.has_value()) {
            break;
        }
        if (lane.items_.empty()) {
            lane.startPos = startPos;
        }
        lane.endPos = startPos + childMainSize.value();
        lane.items_.push_back({ startIndex, childMainSize.value() });
        layoutInfo_->idxToLane_[startIndex] = static_cast<size_t>(target.laneIdx);
        maxMainSize = std::max(maxMainSize, lane.endPos);
        ++startIndex;
    }
}

std::optional<float> LazyWaterFlowLayoutAlgorithm::MeasureChild(
    LayoutWrapper* layoutWrapper, int32_t index, int32_t laneIdx, float referencePos, ReferenceEdge referenceEdge)
{
    if (IsDeadlineReached()) {
        return layoutInfo_->GetCachedHeight(index);
    }
    auto cachedSize = layoutInfo_->GetCachedHeight(index);
    CHECK_NULL_RETURN(layoutWrapper, cachedSize);
    auto rawIndex = GetRawIndexForItem(index);
    auto startPos = referenceEdge == ReferenceEdge::START ? referencePos : referencePos - cachedSize.value_or(0.0f);
    auto endPos = referenceEdge == ReferenceEdge::START ? referencePos + cachedSize.value_or(0.0f) : referencePos;
    const bool maybeVisible = endPos > viewStart_ && startPos < viewEnd_;
    auto child = GetOrCreateChildWrapper(layoutWrapper, rawIndex, maybeVisible);
    if (!child) {
        return cachedSize;
    }
    if (!CanRenderChildInDeadline(child)) {
        return cachedSize;
    }
    if (cachedSize.has_value() && !CheckNeedMeasure(child, laneIdx)) {
        return cachedSize;
    }

    child->Measure(CreateChildConstraintForItem(child, laneIdx, referencePos, referenceEdge));
    auto childGeometryNode = child->GetGeometryNode();
    CHECK_NULL_RETURN(childGeometryNode, cachedSize);
    auto childMainSize = std::max(GetMainAxisSize(childGeometryNode->GetMarginFrameSize(), Axis::VERTICAL), 0.0f);
    UpdateMeasuredLaneItem(index, laneIdx, child, childMainSize, cachedSize);
    layoutInfo_->CacheItemHeight(index, childMainSize);
    return childMainSize;
}

RefPtr<LayoutWrapper> LazyWaterFlowLayoutAlgorithm::GetExistingChildWrapper(
    LayoutWrapper* layoutWrapper, int32_t rawIndex) const
{
    CHECK_NULL_RETURN(layoutWrapper, nullptr);
    auto child = layoutWrapper->GetChildByIndex(rawIndex, false);
    return child ? child : layoutWrapper->GetChildByIndex(rawIndex, true);
}

RefPtr<LayoutWrapper> LazyWaterFlowLayoutAlgorithm::GetOrCreateChildWrapper(
    LayoutWrapper* layoutWrapper, int32_t rawIndex, bool maybeVisible) const
{
    CHECK_NULL_RETURN(layoutWrapper, nullptr);
    // maybeVisible drives whether LazyForEach assigns the node to the active or cache set; getting it wrong
    // means the next frame's ActiveChildRange recycles a node we just used.
    if (maybeVisible) {
        return layoutWrapper->GetOrCreateChildByIndex(rawIndex, true, false);
    }
    auto isCacheItem = !maybeVisible;
    auto child = layoutWrapper->GetChildByIndex(rawIndex, isCacheItem);
    if (!child) {
        child = layoutWrapper->GetOrCreateChildByIndex(rawIndex, !isCacheItem, isCacheItem);
    }
    return child;
}

void LazyWaterFlowLayoutAlgorithm::UpdateMeasuredLaneItem(
    int32_t index, int32_t laneIdx, const RefPtr<LayoutWrapper>& child, float childMainSize,
    const std::optional<float>& cachedSize)
{
    CHECK_NULL_VOID(layoutInfo_);
    if (!cachedSize.has_value() || laneIdx < 0 || laneIdx >= static_cast<int32_t>(layoutInfo_->lanes_.size())) {
        return;
    }
    auto& lane = layoutInfo_->lanes_[laneIdx];
    auto itemIter = std::find_if(
        lane.items_.begin(), lane.items_.end(), [index](const auto& item) { return item.idx == index; });
    if (itemIter == lane.items_.end()) {
        return;
    }
    // Nested lazy children may report an adjustOffset instead of a plain size delta; fold it back into the
    // lane window so parent/child viewports stay aligned.
    auto adjustOffset = LazyWaterFlowLayoutUtils::GetLazyChildAdjustOffset(child);
    auto allAdjustOffset = adjustOffset.start + adjustOffset.end;
    if (!NearZero(allAdjustOffset) && NearEqual(allAdjustOffset, childMainSize - cachedSize.value())) {
        if (itemIter == lane.items_.begin()) {
            lane.startPos -= adjustOffset.start;
        } else {
            itemIter->startOffset -= adjustOffset.start;
        }
    }
    itemIter->mainSize = childMainSize;
}

void LazyWaterFlowLayoutAlgorithm::ReMeasureItemsInLane(LayoutWrapper* layoutWrapper, int32_t laneIdx)
{
    auto& lane = layoutInfo_->lanes_[laneIdx];
    auto childReferenceEdge = LazyWaterFlowLayoutUtils::ResolveChildReferenceEdge(referenceEdge_);
    auto mainPos = lane.startPos;
    for (size_t itemIndex = 0; itemIndex < lane.items_.size(); ++itemIndex) {
        auto& item = lane.items_[itemIndex];
        auto itemStart = mainPos + item.startOffset;
        auto itemEnd = itemStart + item.mainSize;
        auto child = GetExistingChildWrapper(layoutWrapper, GetRawIndexForItem(item.idx));
        if (!child || CheckNeedMeasure(child, laneIdx)) {
            auto childReferencePos =
                LazyWaterFlowLayoutUtils::ResolveChildReferencePos(itemStart, itemEnd, childReferenceEdge);
            auto measuredSize = MeasureChild(layoutWrapper, item.idx, laneIdx, childReferencePos, childReferenceEdge);
            if (measuredSize.has_value()) {
                item.mainSize = measuredSize.value();
            }
            itemStart = itemIndex == 0 ? lane.startPos : mainPos + item.startOffset;
            itemEnd = itemStart + item.mainSize;
        }
        mainPos = itemEnd + mainGap_;
    }
}

void LazyWaterFlowLayoutAlgorithm::ReMeasureItems(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    for (size_t laneIdx = 0; laneIdx < layoutInfo_->lanes_.size(); ++laneIdx) {
        ReMeasureItemsInLane(layoutWrapper, static_cast<int32_t>(laneIdx));
    }
    SyncLaneGeometry();
}

LayoutConstraintF LazyWaterFlowLayoutAlgorithm::CreateChildConstraintForItem(
    const RefPtr<LayoutWrapper>& child, int32_t laneIdx, float referencePos, ReferenceEdge referenceEdge) const
{
    auto constraint = childLayoutConstraints_[laneIdx];
    auto childLayoutProperty = child->GetLayoutProperty();
    if (childLayoutProperty && childLayoutProperty->GetNeedLazyLayout()) {
        // Match LazyGrid/LazyColumn: viewPos is already expanded by parent viewExt.
        constraint.viewPosRef = ViewPosReference {
            .viewPosStart = viewStart_,
            .viewPosEnd = viewEnd_,
            .referencePos = referencePos,
            .referenceEdge = referenceEdge,
            .axis = Axis::VERTICAL,
            .deadline = layoutInfo_->deadline_,
        };
        LazyLayoutUtils::SetStickyInsets(constraint, childStickyTopInset_, childStickyBottomInset_);
    }
    return constraint;
}

bool LazyWaterFlowLayoutAlgorithm::CanRenderChildInDeadline(const RefPtr<LayoutWrapper>& child) const
{
    if (!IsPredictPass()) {
        return true;
    }
    auto hostNode = child->GetHostNode();
    return !hostNode || hostNode->RenderCustomChild(layoutInfo_->deadline_.value());
}

void LazyWaterFlowLayoutAlgorithm::FinishMeasureItems(LayoutWrapper* layoutWrapper,
    const PrevFrameSnapshot& prevFrameSnapshot, float maxMainSize)
{
    layoutInfo_->SyncItemPositions(mainGap_);
    layoutInfo_->EstimateItemSize();
    laneEndPos_ = layoutInfo_->laneEndPos_;
    maxMainSize = std::max(maxMainSize, 0.0f);
    const float bodyHeight = EstimateBodyHeight(maxMainSize);
    totalMainSize_ = bodyHeight + layoutInfo_->headerMainSize_ + layoutInfo_->footerMainSize_;
    layoutInfo_->totalMainSize_ = totalMainSize_;
    // maxHeight_ caches the body-only height to mirror SW semantics. Including footerMainSize_ here would feed back
    // into next frame's EstimateTotalHeight() and double-count the footer when FinishMeasureItems() adds it again.
    layoutInfo_->maxHeight_ = std::max(layoutInfo_->maxHeight_, bodyHeight);
    if (RebaseEndReferenceToCurrentSize()) {
        RefillRebasedMeasureWindow(layoutWrapper);
    }
    UpdateMeasuredRanges();
    if (IsPredictPass()) {
        // Predict must stay transparent to the parent; drop adjustOffset and skip the viewport shift.
        layoutInfo_->adjustOffset_ = AdjustOffset();
        layoutInfo_->ClearDataChanges();
        return;
    }
    const bool hasDataChange = layoutInfo_->hasDataChange_;
    UpdateAdjustOffset(prevFrameSnapshot);
    if (!hasDataChange) {
        layoutInfo_->adjustOffset_ = AdjustOffset();
    }
    const auto consumedOffset =
        referenceEdge_ == ReferenceEdge::END ? layoutInfo_->adjustOffset_.end : layoutInfo_->adjustOffset_.start;
    // Header resize is a section-level shift on top of the body-local anchor diff.
    layoutInfo_->adjustOffset_.start += headerAdjustOffset_;
    // Mirror the exported parent delta into this frame's layout range.
    // No-data body re-anchor is internal; header resize remains exported.
    const auto exportedOffset = consumedOffset + headerAdjustOffset_;
    if (!NearZero(exportedOffset)) {
        ApplyAdjustedMeasureWindow(layoutWrapper, exportedOffset);
    }
    layoutInfo_->ClearDataChanges();
}

void LazyWaterFlowLayoutAlgorithm::ApplyAdjustedMeasureWindow(LayoutWrapper* layoutWrapper, float consumedOffset)
{
    LazyWaterFlowLayoutUtils::ShiftMeasureWindow(consumedOffset, viewStart_, viewEnd_, cacheStartPos_, cacheEndPos_);
    // The shifted cache window is the one the parent will display after consuming adjustOffset; refill its edges
    // so the next frame doesn't show a gap before the user scrolls.
    auto fillMaxMainSize = CollectMaxMainSize(layoutInfo_->lanes_, 0.0f);
    const int32_t endIndex = layoutInfo_->EndIndex();
    if (endIndex >= 0) {
        FillBack(layoutWrapper, cacheEndPos_, endIndex + 1, totalItemCount_ - 1, fillMaxMainSize);
    }
    const int32_t startIndex = layoutInfo_->StartIndex();
    if (startIndex > 0) {
        FillFront(layoutWrapper, cacheStartPos_, startIndex - 1, 0, fillMaxMainSize);
    }
    layoutInfo_->SyncItemPositions(mainGap_);
    layoutInfo_->EstimateItemSize();
    laneEndPos_ = layoutInfo_->laneEndPos_;
    fillMaxMainSize = CollectMaxMainSize(layoutInfo_->lanes_, 0.0f);
    const float bodyHeight = EstimateBodyHeight(fillMaxMainSize);
    totalMainSize_ = bodyHeight + layoutInfo_->headerMainSize_ + layoutInfo_->footerMainSize_;
    layoutInfo_->totalMainSize_ = totalMainSize_;
    layoutInfo_->maxHeight_ = std::max(layoutInfo_->maxHeight_, bodyHeight);
    RebaseEndReferenceToCurrentSize();
    UpdateMeasuredRanges();
}

void LazyWaterFlowLayoutAlgorithm::RefillRebasedMeasureWindow(LayoutWrapper* layoutWrapper)
{
    auto maxMainSize = CollectMaxMainSize(layoutInfo_->lanes_, 0.0f);
    RefillLaneWindow(layoutWrapper, -1, ResolveFrontBoundary(), ResolveBackBoundary(), maxMainSize);
    ReMeasureItems(layoutWrapper);
    layoutInfo_->SyncItemPositions(mainGap_);
    layoutInfo_->EstimateItemSize();
    laneEndPos_ = layoutInfo_->laneEndPos_;
    maxMainSize = CollectMaxMainSize(layoutInfo_->lanes_, 0.0f);
    const float bodyHeight = EstimateBodyHeight(maxMainSize);
    totalMainSize_ = bodyHeight + layoutInfo_->headerMainSize_ + layoutInfo_->footerMainSize_;
    layoutInfo_->totalMainSize_ = totalMainSize_;
    layoutInfo_->maxHeight_ = std::max(layoutInfo_->maxHeight_, bodyHeight);
    RebaseEndReferenceToCurrentSize();
}

float LazyWaterFlowLayoutAlgorithm::EstimateBodyHeight(float maxMainSize) const
{
    if (keepEmptyLanesOutsideContent_) {
        // Lanes are empty by design; carry the best body belief forward.
        return std::max(prevBodyMainSize_, maxMainSize);
    }
    // EstimateTotalMainSize: round-robin "shortest lane first"; best during steady scroll, doesn't layer
    //   maxHeight_.
    // EstimateTotalHeight: windowHeight + suffix-by-average; layers the maxHeight_ sticky, wins when the
    //   retained window sits deep in content (prepend preserve).
    const float estimatedBody = EstimateTotalMainSize(maxMainSize);
    const float swEstimate = layoutInfo_->EstimateTotalHeight(mainGap_);
    return std::max(estimatedBody, swEstimate);
}

float LazyWaterFlowLayoutAlgorithm::EstimateTotalMainSize(float maxMainSize) const
{
    if (totalItemCount_ <= 0) {
        return 0.0f;
    }
    auto measuredEndIndex = layoutInfo_->EndIndex();
    if (measuredEndIndex >= totalItemCount_ - 1) {
        return maxMainSize;
    }
    auto estimatedItemSize = layoutInfo_->estimateItemSize_;
    if (!Positive(estimatedItemSize)) {
        auto measuredCount = measuredEndIndex + 1;
        if (measuredCount > 0) {
            estimatedItemSize = std::max(maxMainSize / static_cast<float>(measuredCount), 0.0f);
        }
    }
    if (!Positive(estimatedItemSize) || laneEndPos_.empty()) {
        return maxMainSize;
    }

    auto estimatedLaneEnds = laneEndPos_;
    auto remainCount = totalItemCount_ - measuredEndIndex - 1;
    auto laneCount = static_cast<int32_t>(estimatedLaneEnds.size());
    auto estimatedStep = estimatedItemSize + mainGap_;
    auto rounds = remainCount / laneCount;
    auto extra = remainCount % laneCount;
    for (auto& laneEndPos : estimatedLaneEnds) {
        laneEndPos += static_cast<float>(rounds) * estimatedStep;
    }
    std::sort(estimatedLaneEnds.begin(), estimatedLaneEnds.end());
    for (int32_t index = 0; index < extra; ++index) {
        estimatedLaneEnds[index] += estimatedStep;
    }
    auto estimatedMaxEnd = *std::max_element(estimatedLaneEnds.begin(), estimatedLaneEnds.end());
    return std::max(maxMainSize, estimatedMaxEnd - mainGap_);
}

bool LazyWaterFlowLayoutAlgorithm::RebaseEndReferenceToCurrentSize()
{
    if (referenceEdge_ != ReferenceEdge::END || !Positive(totalMainSize_)) {
        return false;
    }
    // Section delta is intentional: the window was placed against the previous section belief but body-converted
    // with the CURRENT header, so (section - real) equals the body-window error; a body delta would double-correct.
    auto delta = totalMainSize_ - realMainSize_;
    if (NearZero(delta)) {
        return false;
    }
    LazyWaterFlowLayoutUtils::ShiftMeasureWindow(delta, viewStart_, viewEnd_, cacheStartPos_, cacheEndPos_);
    extendedViewStart_ = viewStart_;
    extendedViewEnd_ = viewEnd_;
    realMainSize_ = totalMainSize_;
    return true;
}

void LazyWaterFlowLayoutAlgorithm::UpdateMeasuredRanges()
{
    layoutInfo_->extendedViewStartPos_ = extendedViewStart_;
    layoutInfo_->extendedViewEndPos_ = extendedViewEnd_;
    layoutInfo_->UpdateVisibleRange(viewStart_, viewEnd_);
    layoutInfo_->UpdateVisibleCallbackRange(viewStart_ + viewExtStart_, viewEnd_ - viewExtEnd_);
    layoutInfo_->UpdateCachedRange(cacheStartPos_, cacheEndPos_);
    layoutInfo_->layoutedStartIndex_ = layoutInfo_->startIndex_;
    layoutInfo_->layoutedEndIndex_ = layoutInfo_->endIndex_;
}

bool LazyWaterFlowLayoutAlgorithm::TryUpdateEndAnchorAdjust(
    const PrevFrameSnapshot& prevFrameSnapshot, float totalDelta)
{
    CHECK_NULL_RETURN(layoutInfo_, false);
    const auto& anchor = prevFrameSnapshot.anchor;
    if (referenceEdge_ != ReferenceEdge::END || anchor.endIndex < 0 || !anchor.endPos.has_value()) {
        return false;
    }
    auto newEndIter = layoutInfo_->posMap_.find(anchor.endIndex);
    if (newEndIter == layoutInfo_->posMap_.end()) {
        return false;
    }
    layoutInfo_->adjustOffset_.end = newEndIter->second.endPos - anchor.endPos->endPos;
    layoutInfo_->adjustOffset_.start = totalDelta - layoutInfo_->adjustOffset_.end;
    return true;
}

void LazyWaterFlowLayoutAlgorithm::UpdateStartAnchorAdjust(const PrevFrameSnapshot& prevFrameSnapshot)
{
    CHECK_NULL_VOID(layoutInfo_);
    const auto& anchor = prevFrameSnapshot.anchor;
    if (anchor.startIndex < 0 || !anchor.startPos.has_value()) {
        return;
    }
    auto newStartIter = layoutInfo_->posMap_.find(anchor.startIndex);
    if (newStartIter != layoutInfo_->posMap_.end()) {
        layoutInfo_->adjustOffset_.start = newStartIter->second.startPos - anchor.startPos->startPos;
        return;
    }
    if (!layoutInfo_->hasDataChange_) {
        return;
    }
    auto fallbackStart = layoutInfo_->GetPos(layoutInfo_->startIndex_);
    if (fallbackStart) {
        layoutInfo_->adjustOffset_.start = fallbackStart->startPos - anchor.startPos->startPos;
    }
}

void LazyWaterFlowLayoutAlgorithm::UpdateVisibleAdjustOffset(float totalDelta)
{
    CHECK_NULL_VOID(layoutInfo_);
    if (referenceEdge_ != ReferenceEdge::START || !layoutInfo_->hasDataChange_ ||
        layoutInfo_->pendingVisiblePositions_.empty()) {
        return;
    }
    auto visibleAdjust = layoutInfo_->adjustOffset_.start;
    auto hasVisibleAdjust = false;
    for (const auto& [index, oldPos] : layoutInfo_->pendingVisiblePositions_) {
        auto newPosIter = layoutInfo_->posMap_.find(index);
        if (newPosIter == layoutInfo_->posMap_.end()) {
            continue;
        }
        auto delta = newPosIter->second.startPos - oldPos.startPos;
        if (!hasVisibleAdjust) {
            visibleAdjust = delta;
            hasVisibleAdjust = true;
            continue;
        }
        visibleAdjust =
            GreatOrEqual(totalDelta, 0.0f) ? std::max(visibleAdjust, delta) : std::min(visibleAdjust, delta);
    }
    if (hasVisibleAdjust) {
        layoutInfo_->adjustOffset_.start = visibleAdjust;
    }
}

float LazyWaterFlowLayoutAlgorithm::GetBodyMainSize() const
{
    return std::max(0.0f, totalMainSize_ - layoutInfo_->headerMainSize_ - layoutInfo_->footerMainSize_);
}

bool LazyWaterFlowLayoutAlgorithm::ShouldKeepStartBoundaryOnFrontInsert(
    const PrevFrameSnapshot& prevFrameSnapshot) const
{
    CHECK_NULL_RETURN(layoutInfo_, false);
    const auto& anchor = prevFrameSnapshot.anchor;
    return referenceEdge_ == ReferenceEdge::START && layoutInfo_->hasDataChange_ && anchor.startIndex >= 0 &&
        anchor.startPos.has_value() && layoutInfo_->newStartIndex_ == anchor.startIndex &&
        NearZero(anchor.startPos->startPos) && GreatNotEqual(startReferenceViewportOffset_, 0.0f);
}

void LazyWaterFlowLayoutAlgorithm::UpdateAdjustOffset(const PrevFrameSnapshot& prevFrameSnapshot)
{
    layoutInfo_->adjustOffset_ = {};
    if (laneTopologyChanged_) {
        return;
    }
    if (topAnchorRebased_) {
        return;
    }
    const auto& anchor = prevFrameSnapshot.anchor;
    const bool hasStartAnchor = anchor.startIndex >= 0 && anchor.startPos.has_value();
    const bool hasEndAnchor = anchor.endIndex >= 0 && anchor.endPos.has_value();
    if (!hasStartAnchor && !hasEndAnchor) {
        return;
    }
    const auto totalDelta = GetBodyMainSize() - anchor.totalMainSize;
    if (ShouldKeepStartBoundaryOnFrontInsert(prevFrameSnapshot)) {
        layoutInfo_->adjustOffset_.end = totalDelta;
        return;
    }
    if (referenceEdge_ == ReferenceEdge::START && layoutInfo_->hasDataChange_ && anchor.startIndex < 0 &&
        LessNotEqual(totalDelta, 0.0f)) {
        // The previous leading anchor was deleted. Let remaining items move up and avoid parent compensation.
        layoutInfo_->adjustOffset_.end = totalDelta;
        return;
    }
    if (hasEndAnchor && TryUpdateEndAnchorAdjust(prevFrameSnapshot, totalDelta)) {
        return;
    }
    bool anchorLocated = false;
    if (hasStartAnchor) {
        anchorLocated =
            layoutInfo_->posMap_.find(anchor.startIndex) != layoutInfo_->posMap_.end();
        UpdateStartAnchorAdjust(prevFrameSnapshot);
    }
    // Only fall back to the visible-item heuristic when the anchor itself isn't in the new layout. Taking the
    // max delta when the anchor is present would clip behind sticky edges with varying-height new items.
    if (!anchorLocated) {
        UpdateVisibleAdjustOffset(totalDelta);
    }
    layoutInfo_->adjustOffset_.end = totalDelta - layoutInfo_->adjustOffset_.start;
}

void LazyWaterFlowLayoutAlgorithm::LayoutItems(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset)
{
    CHECK_NULL_VOID(layoutWrapper);
    CHECK_NULL_VOID(layoutInfo_);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto stickyStyle = ResolveStickyStyle(layoutWrapper);
    const auto headerMainSize = layoutInfo_->headerMainSize_;
    const auto footerMainSize = layoutInfo_->footerMainSize_;
    // Body-local: viewStart_/viewEnd_ are body coords; add the header back so sticky math runs in section coords.
    const HeaderFooterStickyMetrics stickyMetrics { viewStart_ + headerMainSize, viewEnd_ + headerMainSize,
        totalMainSize_, headerMainSize, footerMainSize, stickyTopInset_, stickyBottomInset_ };
    const auto stickyHeaderPos = HeaderFooterUtils::CalcStickyHeaderPos(stickyMetrics);
    const auto stickyFooterPos = HeaderFooterUtils::CalcStickyFooterPos(stickyMetrics);

    // Layout order follows section semantics: header -> content items -> footer.
    LayoutHeader(layoutWrapper, paddingOffset, stickyStyle, stickyHeaderPos);
    auto range = GetLayoutRange();
    LayoutContentItems(layoutWrapper, paddingOffset, range);
    ClearUnlayoutedContentItems(layoutWrapper, range);
    UpdateActiveChildRange(layoutWrapper, layoutInfo_->layoutedStartIndex_, layoutInfo_->layoutedEndIndex_,
        range.start, range.end);
    LayoutFooter(layoutWrapper, paddingOffset, stickyStyle, stickyFooterPos);
}

void LazyWaterFlowLayoutAlgorithm::LayoutHeader(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset,
    StickyStyle stickyStyle, float stickyHeaderPos) const
{
    auto isSticky = HeaderFooterUtils::IsHeaderSticky(stickyStyle);
    auto offset = paddingOffset + (isSticky ? OffsetF(0.0f, stickyHeaderPos) : OffsetF());
    HeaderFooterUtils::LayoutEdge(
        layoutWrapper, headerIndex_, offset, isSticky, layoutDirection_ == TextDirection::RTL, crossSize_);
}

void LazyWaterFlowLayoutAlgorithm::LayoutFooter(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset,
    StickyStyle stickyStyle, float stickyFooterPos) const
{
    auto isSticky = HeaderFooterUtils::IsFooterSticky(stickyStyle);
    auto footerPos = isSticky ? stickyFooterPos : totalMainSize_ - layoutInfo_->footerMainSize_;
    auto offset = OffsetF(paddingOffset.GetX(), paddingOffset.GetY() + footerPos);
    HeaderFooterUtils::LayoutEdge(
        layoutWrapper, footerIndex_, offset, isSticky, layoutDirection_ == TextDirection::RTL, crossSize_);
}

LazyWaterFlowLayoutAlgorithm::LayoutRange LazyWaterFlowLayoutAlgorithm::GetLayoutRange() const
{
    // Prefer the cache window; fall back to visible when cache hasn't been built. Cache items laid out with
    // visible ones avoid recreate cost on the next frame.
    LayoutRange range;
    range.start = layoutInfo_->cachedStartIndex_ >= 0 ? layoutInfo_->cachedStartIndex_ :
                                                        layoutInfo_->layoutedStartIndex_;
    range.end = layoutInfo_->cachedEndIndex_ >= 0 ? layoutInfo_->cachedEndIndex_ : layoutInfo_->layoutedEndIndex_;
    return range;
}

void LazyWaterFlowLayoutAlgorithm::LayoutContentItems(
    LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset, const LayoutRange& range)
{
    for (int32_t itemIndex = std::max(range.start, 0); itemIndex <= range.end; ++itemIndex) {
        LayoutContentItem(layoutWrapper, paddingOffset, itemIndex);
    }
}

void LazyWaterFlowLayoutAlgorithm::LayoutContentItem(
    LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset, int32_t itemIndex)
{
    auto itemPos = layoutInfo_->GetPos(itemIndex);
    if (!IsValidItemPosition(itemPos)) {
        return;
    }
    // During parent-driven offscreen preload there is no visible range yet; use the cache range so those
    // materialized children stay active until they enter the real viewport.
    const bool offscreenPredict = layoutInfo_->layoutedStartIndex_ < 0 && layoutInfo_->layoutedEndIndex_ < 0 &&
        layoutInfo_->cachedStartIndex_ >= 0;
    auto isVisible = offscreenPredict
        ? LazyWaterFlowLayoutUtils::IsItemVisible(
            itemIndex, layoutInfo_->cachedStartIndex_, layoutInfo_->cachedEndIndex_)
        : LazyWaterFlowLayoutUtils::IsItemVisible(
            itemIndex, layoutInfo_->layoutedStartIndex_, layoutInfo_->layoutedEndIndex_);
    auto child = GetLayoutChild(layoutWrapper, itemIndex, isVisible);
    if (!child) {
        return;
    }
    auto geometryNode = child->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto itemOffset = ResolveItemOffset(
        paddingOffset, itemPos->laneIdx, geometryNode->GetMarginFrameSize().Width(), itemPos->startPos);
    geometryNode->SetMarginFrameOffset(itemOffset);
    // SetActive before the geometry push so SyncGeometryProperties runs under the correct active state.
    child->SetActive(isVisible);
    auto childHost = child->GetHostNode();
    if (isVisible && childHost) {
        // A static LazyForEach item can first be built as cache, which marks its JS subtree inactive.
        // Re-activate it before layout when the same wrapper enters the visible range.
        RestoreActiveFrameSubtree(childHost);
        childHost->SetJSViewActive(true);
    }
    const bool nestedLazy = childHost && childHost->GetPattern<LazyLayoutPattern>();
    if (isVisible || nestedLazy || child->CheckNeedForceMeasureAndLayout()) {
        // Visible items need a full layout pass so reactivated JS subtrees, such as Text inside a static
        // LazyForEach item, are synced along with the item root.
        child->Layout();
        if (isVisible && nestedLazy) {
            childHost->SwapDirtyLayoutWrapperOnMainThread(child);
        } else if (!isVisible && childHost) {
            childHost->ForceSyncGeometryNode();
            childHost->ResetLayoutAlgorithm();
        }
    } else if (childHost) {
        // Clean item: force-sync geometry so a repositioned-but-clean item still repaints, e.g. when a sticky
        // header resizes without changing the item's screen position.
        childHost->ForceSyncGeometryNode();
        childHost->ResetLayoutAlgorithm();
    } else {
        child->Layout();
    }
    // SwapDirtyLayoutWrapperOnMainThread can clobber the active state; reassert.
    child->SetActive(isVisible);
    if (isVisible && childHost) {
        RestoreActiveFrameSubtree(childHost);
        childHost->SetJSViewActive(true);
        childHost->MarkNeedSyncRenderTree();
        childHost->RebuildRenderContextTree();
    }
}

bool LazyWaterFlowLayoutAlgorithm::IsValidItemPosition(const LazyWaterFlowItemMainPos* itemPos) const
{
    return itemPos && itemPos->laneIdx >= 0 && itemPos->laneIdx < static_cast<int32_t>(crossPos_.size()) &&
           itemPos->laneIdx < static_cast<int32_t>(childLayoutConstraints_.size());
}

RefPtr<LayoutWrapper> LazyWaterFlowLayoutAlgorithm::GetLayoutChild(
    LayoutWrapper* layoutWrapper, int32_t itemIndex, bool isVisible) const
{
    CHECK_NULL_RETURN(layoutWrapper, nullptr);
    const bool isCacheItem = !isVisible;
    const auto rawIndex = GetRawIndexForItem(itemIndex);
    if (isVisible) {
        return layoutWrapper->GetOrCreateChildByIndex(rawIndex, true, false);
    }
    auto child = layoutWrapper->GetChildByIndex(rawIndex, isCacheItem);
    if (!child && IsPredictPass()) {
        child = layoutWrapper->GetOrCreateChildByIndex(rawIndex, !isCacheItem, isCacheItem);
    }
    return child;
}

void LazyWaterFlowLayoutAlgorithm::ClearUnlayoutedContentItems(
    LayoutWrapper* layoutWrapper, const LayoutRange& range) const
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    const auto rawStart = range.start >= 0 ? GetRawIndexForItem(range.start) : -1;
    const auto rawEnd = range.end >= range.start ? GetRawIndexForItem(range.end) : -1;

    int32_t childStart = 0;
    for (const auto& child : host->GetChildren()) {
        CHECK_NULL_CONTINUE(child);
        const auto childCount = child->FrameCount();
        if (childCount <= 0) {
            continue;
        }
        const auto childEnd = childStart + childCount - 1;
        const bool isHeader = headerIndex_ >= childStart && headerIndex_ <= childEnd;
        const bool isFooter = footerIndex_ >= childStart && footerIndex_ <= childEnd;
        const bool overlapsLayoutRange = rawStart >= 0 && rawEnd >= rawStart && rawStart <= childEnd &&
                                         rawEnd >= childStart;
        if (!isHeader && !isFooter && !overlapsLayoutRange) {
            child->DoSetActiveChildRange(rawStart - childStart, rawEnd - childStart, 0, 0);
            if (auto frameNode = AceType::DynamicCast<FrameNode>(child)) {
                frameNode->ClearSubtreeLayoutAlgorithm();
            }
        }
        childStart += childCount;
    }
}

void LazyWaterFlowLayoutAlgorithm::UpdateActiveChildRange(LayoutWrapper* layoutWrapper, int32_t visibleStart,
    int32_t visibleEnd, int32_t cachedStart, int32_t cachedEnd) const
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);

    // Direct children keep the cache window active like LazyVGridLayout. Grouped syntax children below may still need
    // the visible window and cache expansion separately.
    const auto windowStart = cachedStart >= 0 ? cachedStart : visibleStart;
    const auto windowEnd = cachedEnd >= cachedStart ? cachedEnd : visibleEnd;
    if (windowStart < 0 || windowEnd < windowStart) {
        // h/f/s: keep header / footer active even when no content items fall in the window.
        SetHeaderFooterActive(layoutWrapper);
        return;
    }

    const auto rawWindowStart = GetRawIndexForItem(windowStart);
    const auto rawWindowEnd = GetRawIndexForItem(windowEnd);
    if (headerIndex_ < 0 && footerIndex_ < 0) {
        host->SetActiveChildRange(rawWindowStart, rawWindowEnd, 0, 0);
    } else {
        auto activeChildSets = BuildActiveChildSets(rawWindowStart, rawWindowEnd);
        host->SetActiveChildRange(std::optional<ActiveChildSets>(activeChildSets), std::nullopt);
        ActivateContentItemRange(host, rawWindowStart, rawWindowEnd);
    }
}

void LazyWaterFlowLayoutAlgorithm::SetHeaderFooterActive(LayoutWrapper* layoutWrapper) const
{
    ActiveChildSets activeChildSets;
    if (headerIndex_ >= 0) {
        activeChildSets.activeItems.insert(headerIndex_);
    }
    if (footerIndex_ >= 0) {
        activeChildSets.activeItems.insert(footerIndex_);
    }
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    host->SetActiveChildRange(std::optional<ActiveChildSets>(activeChildSets), std::nullopt);
}

void LazyWaterFlowLayoutAlgorithm::ActivateContentItemRange(
    const RefPtr<FrameNode>& host, int32_t rawStart, int32_t rawEnd) const
{
    if (rawStart < 0 || rawEnd < rawStart) {
        return;
    }
    int32_t childStart = 0;
    for (const auto& child : host->GetChildren()) {
        CHECK_NULL_CONTINUE(child);
        auto childCount = child->FrameCount();
        if (childCount <= 0) {
            continue;
        }
        // h/f/s: header and footer are kept active by the caller via ActiveChildSets; skip them here so
        // we do not clamp them by the item cache window.
        const auto childEnd = childStart + childCount - 1;
        const bool isHeader = headerIndex_ >= childStart && headerIndex_ <= childEnd;
        const bool isFooter = footerIndex_ >= childStart && footerIndex_ <= childEnd;
        if (!isHeader && !isFooter) {
            child->DoSetActiveChildRange(rawStart - childStart, rawEnd - childStart, 0, 0);
        }
        childStart += childCount;
    }
}

ActiveChildSets LazyWaterFlowLayoutAlgorithm::BuildActiveChildSets(int32_t rawStart, int32_t rawEnd) const
{
    ActiveChildSets activeChildSets;
    for (auto index = rawStart; index <= rawEnd; ++index) {
        activeChildSets.activeItems.insert(index);
    }
    if (headerIndex_ >= 0) {
        activeChildSets.activeItems.insert(headerIndex_);
    }
    if (footerIndex_ >= 0) {
        activeChildSets.activeItems.insert(footerIndex_);
    }
    return activeChildSets;
}

} // namespace OHOS::Ace::NG
