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

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_algorithm.h"

#include <cstddef>
#include <cstdint>
#include <iterator>

#include "base/utils/time_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/utils.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_pattern.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/property/templates_parser.h"
#include "core/components/common/properties/alignment.h"

namespace OHOS::Ace::NG {

void LazyGridLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutInfo_);
    UpdateHeaderFooterIndexes(layoutWrapper);
    totalItemCount_ = CalculateItemCount(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<LazyGridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint().value();
    auto contentIdealSize = CreateIdealSize(contentConstraint, axis_, layoutProperty->GetMeasureType());
    if (!GetCrossAxisSize(contentIdealSize, axis_)) {
        auto maxSize = GetCrossAxisSize(contentConstraint.maxSize, axis_);
        if (GreaterOrEqualToInfinity(maxSize)) {
            maxSize = GetCrossAxisSize(contentConstraint.percentReference, axis_);
        }
        SetCrossAxisSize(maxSize, axis_, contentIdealSize);
    }
    realMainSize_ = layoutWrapper->GetGeometryNode()->GetPaddingSize().MainSize(axis_);
    totalMainSize_ = layoutInfo_->totalMainSize_;
    UpdateGap(layoutProperty, contentIdealSize);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    UpdateGridItemConstraint(contentIdealSize, childLayoutConstraint);

    // Measure the header before resolving the viewport baseline so the body-local startPos_/endPos_ derived in
    // UpdateReferencePos already absorb the current frame's header height (avoids one-frame misalignment after
    // header size changes).
    MeasureHeader(layoutWrapper);
    UpdateReferencePos(layoutWrapper, contentConstraint.viewPosRef);

    // DynamicLayout branch: non-lazy loading mode =====
    if (isDynamicLayout_) {
        MeasureDynamicLayout(layoutWrapper, contentIdealSize, padding);
        return;
    }

    if (totalItemCount_ == 0) {
        layoutInfo_->SetTotalItemCount(0);
        totalMainSize_ = 0.0f;
    } else if (layoutInfo_->deadline_) {
        layoutInfo_->SetTotalItemCount(totalItemCount_);
        layoutInfo_->SetLanes(lanes_);
        layoutInfo_->SetSpace(spaceWidth_);
        auto paddingOffset = OffsetF(padding.left.value_or(0.0f), padding.top.value_or(0.0f));
        PredictLayoutForward(layoutWrapper, crossSize_, paddingOffset);
        PredictLayoutBackward(layoutWrapper, crossSize_, paddingOffset);
        SyncPredictLayoutInfo(layoutWrapper);
    } else if (needAllLayout_) {
        MeasureGridItemAll(layoutWrapper);
    } else {
        MeasureGridItemLazy(layoutWrapper);
    }

    MeasureFooter(layoutWrapper);
    totalMainSize_ += layoutInfo_->headerMainSize_ + layoutInfo_->footerMainSize_;
    layoutInfo_->totalMainSize_ = totalMainSize_;

    SetFrameSize(layoutWrapper, contentIdealSize, padding);
}

void LazyGridLayoutAlgorithm::MeasureDynamicLayout(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize,
    const PaddingPropertyF& padding)
{
    if (totalItemCount_ == 0) {
        layoutInfo_->SetTotalItemCount(0);
        totalMainSize_ = 0.0f;
    } else {
        // DynamicLayout: measure all child nodes (non-lazy loading)
        MeasureGridItemAll(layoutWrapper);
    }
    MeasureFooter(layoutWrapper);
    // Fold header / footer into the section's total main size so SetFrameSize receives the full extent.
    totalMainSize_ += layoutInfo_->headerMainSize_ + layoutInfo_->footerMainSize_;
    layoutInfo_->totalMainSize_ = totalMainSize_;
    SetFrameSize(layoutWrapper, contentIdealSize, padding);
}

void LazyGridLayoutAlgorithm::SetFrameSize(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize,
    const PaddingPropertyF& padding)
{
    auto property = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    const auto& layoutConstraint = property->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    OptionalSizeF frameSize;
    // Use idea size first if it is valid.
    frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
    if (frameSize.IsValid()) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
        return;
    }

    auto layoutPolicy = property->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value()) {
        auto isVertical = axis_ == Axis::VERTICAL;
        auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto layoutPolicySize = ConstrainIdealSizeByLayoutPolicy(
            property->GetLayoutConstraint().value(), widthLayoutPolicy, heightLayoutPolicy, axis_);
        contentIdealSize.UpdateIllegalSizeWithCheck(layoutPolicySize.ConvertToSizeT());
        auto isMainWrap = (isVertical ? heightLayoutPolicy : widthLayoutPolicy) == LayoutCalPolicy::WRAP_CONTENT;
        auto isMainFix = (isVertical ? heightLayoutPolicy : widthLayoutPolicy) == LayoutCalPolicy::FIX_AT_IDEAL_SIZE ||
                         (isVertical ? heightLayoutPolicy : widthLayoutPolicy) == LayoutCalPolicy::NO_MATCH;
        if (isMainWrap) {
            contentIdealSize.SetMainSize(totalMainSize_, axis_);
            contentIdealSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
        } else if (isMainFix) {
            contentIdealSize.SetMainSize(totalMainSize_, axis_);
        }
    } else {
        contentIdealSize.SetMainSize(totalMainSize_, axis_);
    }

    AddPaddingToSize(padding, contentIdealSize);
    frameSize.UpdateIllegalSizeWithCheck(contentIdealSize);
    if (layoutConstraint->selfIdealSize.Width()) {
        frameSize.ConstrainFloat(minSize, maxSize, false, true);
    } else if (layoutConstraint->selfIdealSize.Height()) {
        frameSize.ConstrainFloat(minSize, maxSize, true, true);
    } else {
        frameSize.Constrain(minSize, maxSize, true);
    }
    frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

void LazyGridLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = AceType::DynamicCast<LazyGridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    layoutDirection_ = layoutProperty->GetNonAutoLayoutDirection();
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto paddingOffset = OffsetF(left, top);
    float crossSize = GetCrossAxisSize(size, axis_);

    auto stickyStyle = ResolveStickyStyle(layoutWrapper);
    const auto headerMainSize = layoutInfo_->headerMainSize_;
    const auto footerMainSize = layoutInfo_->footerMainSize_;
    // Sticky math expects view/section coords (header included) in the same frame as totalMainSize_. LazyGrid
    // stores startPos_/endPos_ in body-local coords (header subtracted in UpdateReferencePos); add the header
    // back so the metrics match totalMainSize_'s section frame.
    const HeaderFooterStickyMetrics stickyMetrics { startPos_ + headerMainSize, endPos_ + headerMainSize,
        totalMainSize_, headerMainSize, footerMainSize, stickyTopInset_, stickyBottomInset_ };
    const auto stickyHeaderPos = HeaderFooterUtils::CalcStickyHeaderPos(stickyMetrics);
    const auto stickyFooterPos = HeaderFooterUtils::CalcStickyFooterPos(stickyMetrics);

    // posMap_ holds items in self-local body coords [0, bodyHeight). Shift them down by headerMainSize_ so the
    // section reads top-to-bottom as header -> items -> footer.
    const auto itemPaddingOffset = paddingOffset + OffsetF(0.0f, headerMainSize);

    if (isDynamicLayout_) {
        // DynamicLayout: layout all child nodes + handle alignment
        LayoutHeader(layoutWrapper, paddingOffset, stickyStyle, stickyHeaderPos);
        LayoutGridItems(layoutWrapper, crossSize, itemPaddingOffset);
        LayoutFooter(layoutWrapper, paddingOffset, stickyStyle, stickyFooterPos);
        return;
    }

    if (layoutInfo_->deadline_) {
        layoutInfo_->deadline_.reset();
        // Re-lay the sticky header/footer on predictive frames too, else the edges freeze for a frame and flicker.
        LayoutHeader(layoutWrapper, paddingOffset, stickyStyle, stickyHeaderPos);
        LayoutFooter(layoutWrapper, paddingOffset, stickyStyle, stickyFooterPos);
        return;
    }
    LayoutHeader(layoutWrapper, paddingOffset, stickyStyle, stickyHeaderPos);
    LayoutGridItems(layoutWrapper, crossSize, itemPaddingOffset);
    LayoutCachedItems(layoutWrapper, crossSize, itemPaddingOffset);
    LayoutFooter(layoutWrapper, paddingOffset, stickyStyle, stickyFooterPos);
}

int32_t LazyGridLayoutAlgorithm::LanesFloor(int32_t index) const
{
    int32_t tempIndex = std::min(index, totalItemCount_ - 1);
    return lanes_ <= 1 ? tempIndex : (tempIndex - tempIndex % lanes_);
}

int32_t LazyGridLayoutAlgorithm::LanesCeil(int32_t index) const
{
    int32_t tempIndex = lanes_ <= 1 ? index : (index - index % lanes_ + lanes_ - 1);
    return std::min(tempIndex, totalItemCount_ - 1);
}

void LazyGridLayoutAlgorithm::UpdateGap(const RefPtr<LazyGridLayoutProperty>& layoutProperty,
    const OptionalSizeF& selfIdealSize)
{
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint().value();
    auto mainPercentRefer = GetMainAxisSize(contentConstraint.percentReference, axis_);
    auto rowGapDim = layoutProperty->GetRowGap().value_or(Dimension(0));
    float rowGap = ConvertToPx(rowGapDim, contentConstraint.scaleProperty, mainPercentRefer).value_or(0);
    rowGap = std::max(rowGap, 0.0f);
    auto columnGapDim = layoutProperty->GetColumnGap().value_or(Dimension(0));
    float columnGap = ConvertToPx(columnGapDim, contentConstraint.scaleProperty, mainPercentRefer).value_or(0);
    columnGap = std::max(columnGap, 0.0f);
    if (axis_ == Axis::VERTICAL) {
        spaceWidth_ = rowGap;
        laneGutter_ = columnGap;
    } else {
        spaceWidth_ = columnGap;
        laneGutter_ = rowGap;
    }
    auto columnsTemplate = layoutProperty->GetColumnsTemplate().value_or("");
    auto itemFillPolicy = layoutProperty->GetItemFillPolicy();

    auto crossPercentRefer = GetCrossAxisSize(contentConstraint.percentReference, axis_);
    crossSize_ = selfIdealSize.CrossSize(axis_).value_or(crossPercentRefer);

    // If ItemFillPolicy is set, use standard function BuildItemFillPolicyColumns to calculate column template
    if (itemFillPolicy.has_value()) {
        columnsTemplate = BuildItemFillPolicyColumns(
            itemFillPolicy.value(),
            crossSize_,
            contentConstraint.scaleProperty.vpScale)
            .value_or("");
    }
    auto cross = ParseTemplateArgs(columnsTemplate, crossSize_, laneGutter_, totalItemCount_);
    laneGutter_ = cross.second;
    if (cross.first.empty()) {
        cross.first = { crossSize_ };
    }
    crossLens_ = std::move(cross.first);
    lanes_ = static_cast<int32_t>(crossLens_.size());
    crossPos_.resize(lanes_);
    double crossPos = 0.0;
    int32_t index = 0;
    for (auto len : crossLens_) {
        crossPos_[index] = crossPos;
        crossPos += len + laneGutter_;
        ++index;
    }
}

bool LazyGridLayoutAlgorithm::CheckNeedMeasure(const RefPtr<LayoutWrapper>& layoutWrapper, int32_t laneIdx) const
{
    if (layoutWrapper->CheckNeedForceMeasureAndLayout()) {
        return true;
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    auto constraint = geometryNode->GetParentLayoutConstraint();
    CHECK_NULL_RETURN(constraint, true);
    return constraint.value() != childLayoutConstraints_[laneIdx];
}

void LazyGridLayoutAlgorithm::UpdateGridItemConstraint(const OptionalSizeF& selfIdealSize,
    LayoutConstraintF& contentConstraint)
{
    auto fullCrossSize = selfIdealSize.CrossSize(axis_).value_or(
        GetCrossAxisSize(contentConstraint.percentReference, axis_));
    // Header/footer always measure against the full section width instead of a single lane width.
    edgeLayoutConstraint_ = contentConstraint;
    edgeLayoutConstraint_.parentIdealSize = selfIdealSize;
    edgeLayoutConstraint_.maxSize.SetMainSize(Infinity<float>(), axis_);
    edgeLayoutConstraint_.percentReference.SetCrossSize(fullCrossSize, axis_);
    edgeLayoutConstraint_.parentIdealSize.SetCrossSize(fullCrossSize, axis_);
    edgeLayoutConstraint_.maxSize.SetCrossSize(fullCrossSize, axis_);
    edgeLayoutConstraint_.viewPosRef.reset();

    std::vector<LayoutConstraintF> layoutConstraints;
    for (auto cross : crossLens_) {
        auto childConstraint = contentConstraint;
        childConstraint.parentIdealSize = selfIdealSize;
        childConstraint.maxSize.SetMainSize(Infinity<float>(), axis_);
        childConstraint.percentReference.SetCrossSize(cross, axis_);
        childConstraint.parentIdealSize.SetCrossSize(cross, axis_);
        childConstraint.maxSize.SetCrossSize(cross, axis_);
        childConstraint.viewPosRef.reset();
        layoutConstraints.emplace_back(childConstraint);
    }
    childLayoutConstraints_ = std::move(layoutConstraints);
}

void LazyGridLayoutAlgorithm::UpdateReferencePos(LayoutWrapper* layoutWrapper, std::optional<ViewPosReference>& posRef)
{
    if (!posRef.has_value()) {
        posRef = LazyLayoutUtils::GetViewPosReference(layoutWrapper->GetHostNode(),
            { V2::LAZY_V_GRID_LAYOUT_ETS_TAG });
    }
    if (!posRef.has_value() || posRef.value().axis != axis_) {
        needAllLayout_ = true;
        stickyTopInset_ = 0.0f;
        stickyBottomInset_ = 0.0f;
        return;
    }
    forwardLayout_ = posRef.value().referenceEdge == ReferenceEdge::START;
    referencePos_ = posRef.value().referencePos;
    viewExtStart_ = posRef.value().viewExtStart;
    viewExtEnd_ = posRef.value().viewExtEnd;
    stickyTopInset_ = posRef.value().stickyInsetStart;
    stickyBottomInset_ = posRef.value().stickyInsetEnd;
    if (forwardLayout_) {
        startPos_ = posRef.value().viewPosStart - viewExtStart_ - referencePos_;
        endPos_ = posRef.value().viewPosEnd + viewExtEnd_ - referencePos_;
    } else {
        referencePos_ += totalMainSize_ - realMainSize_;
        startPos_ = posRef.value().viewPosStart - viewExtStart_ - (referencePos_ - totalMainSize_);
        endPos_ = posRef.value().viewPosEnd + viewExtEnd_ - (referencePos_ - totalMainSize_);
    }
    float viewSize = posRef.value().viewPosEnd - posRef.value().viewPosStart;
    cacheStartPos_ = startPos_ - viewSize * cacheSize_;
    cacheEndPos_ = endPos_ + viewSize * cacheSize_;
    // h/f/s: the viewport coords above are in section coords. posMap_ keeps items in body-local coords ([0,
    // bodyHeight)), so translate to body coords once here so MeasureForward/Backward / CheckRecycle keep using
    // their existing comparisons unchanged.
    const auto headerMainSize = layoutInfo_->headerMainSize_;
    if (!NearZero(headerMainSize)) {
        startPos_ -= headerMainSize;
        endPos_ -= headerMainSize;
        cacheStartPos_ -= headerMainSize;
        cacheEndPos_ -= headerMainSize;
    }
    needAllLayout_ = false;
    // When not in own idle task but parent is doing predictive layout in idle,
    // inherit deadline and cache positions
    if (!layoutInfo_->deadline_.has_value() && posRef.value().deadline.has_value()) {
        layoutInfo_->deadline_ = posRef.value().deadline.value();
        layoutInfo_->cacheStartPos_ = cacheStartPos_;
        layoutInfo_->cacheEndPos_ = cacheEndPos_;
    }
}

void LazyGridLayoutAlgorithm::MeasureGridItemAll(LayoutWrapper* layoutWrapper)
{
    float totalSize = 0.0f;
    layoutInfo_->posMap_.clear();
    layoutInfo_->spaceWidth_ = spaceWidth_;
    layoutInfo_->lanes_ = lanes_;
    int32_t curIndex = 0;
    while (curIndex < totalItemCount_) {
        float lineSize = 0.0f;
        int32_t laneIdx = 0;
        for (; laneIdx < lanes_ && curIndex + laneIdx < totalItemCount_; laneIdx++) {
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(curIndex + laneIdx));
            if (!wrapper) {
                continue;
            }
            if (CheckNeedMeasure(wrapper, laneIdx)) {
                wrapper->Measure(childLayoutConstraints_[laneIdx]);
            }
            float mainSize = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
            lineSize = std::max(mainSize, lineSize);
        }
        for (int32_t i = 0; i < laneIdx; i++) {
            layoutInfo_->posMap_[curIndex + i] = { i, totalSize, lineSize + totalSize };
        }
        totalSize += spaceWidth_ + lineSize;
        curIndex += lanes_;
    }
    totalSize -= spaceWidth_;
    layoutInfo_->startIndex_ = 0;
    layoutInfo_->endIndex_ = totalItemCount_ - 1;
    layoutInfo_->visibleStartIndex_ = 0;
    layoutInfo_->visibleEndIndex_ = totalItemCount_ - 1;
    layoutInfo_->totalMainSize_ = totalSize;
    layoutInfo_->totalItemCount_ = totalItemCount_;
    totalMainSize_ = totalSize;
}

void LazyGridLayoutAlgorithm::MeasureGridItemLazy(LayoutWrapper* layoutWrapper)
{
    if (forwardLayout_) {
        int32_t startIndex = 0;
        float startPos = 0.0f;
        GetStartIndexInfo(startIndex, startPos);
        layoutInfo_->SetLanes(lanes_);
        layoutInfo_->SetTotalItemCount(totalItemCount_);
        layoutInfo_->SetSpace(spaceWidth_);
        layoutInfo_->startIndex_ = startIndex;
        layoutInfo_->endIndex_ = startIndex;
        if (startIndex >= 0) {
            MeasureForward(layoutWrapper, startIndex, startPos);
            MeasureBackward(layoutWrapper, startIndex - 1, startPos - spaceWidth_);
        }
    } else {
        int32_t endIndex = layoutInfo_->endIndex_;
        float endPos = totalMainSize_;
        GetEndIndexInfo(endIndex, endPos);
        layoutInfo_->SetLanes(lanes_);
        layoutInfo_->SetTotalItemCount(totalItemCount_);
        layoutInfo_->SetSpace(spaceWidth_);
        layoutInfo_->endIndex_ = endIndex;
        layoutInfo_->startIndex_ = endIndex;
        if (endIndex < totalItemCount_) {
            MeasureBackward(layoutWrapper, endIndex, endPos);
            MeasureForward(layoutWrapper, endIndex + 1, endPos + spaceWidth_);
        }
    }
    CheckRecycle();
    layoutInfo_->UpdatePosMap();
    float delta = layoutInfo_->adjustOffset_.start;
    referencePos_ += delta;
    startPos_ += delta;
    endPos_ += delta;
    cacheStartPos_ += delta;
    cacheEndPos_ += delta;
    totalMainSize_ = layoutInfo_->totalMainSize_;
    CalculateVisibleStartIndex();
    CalculateVisibleEndIndex();
}

void LazyGridLayoutAlgorithm::GetStartIndexInfo(int32_t& index, float& pos)
{
    if (GreatNotEqual(startPos_, totalMainSize_)) {
        index = layoutInfo_->totalItemCount_;
        pos = totalMainSize_;
        return;
    } else if (LessNotEqual(endPos_, 0)) {
        pos = 0.0f;
        index = -1;
        return;
    } else if (LessOrEqual(startPos_, 0) || layoutInfo_->endIndex_ < 0) {
        pos = 0.0f;
        index = 0;
        return;
    }
    auto it = layoutInfo_->posMap_.find(layoutInfo_->startIndex_);
    if (it == layoutInfo_->posMap_.end()) {
        pos = 0.0f;
        index = 0;
        return;
    }
    auto nextIt = it;
    ++nextIt;
    while (nextIt != layoutInfo_->posMap_.end() && LessNotEqual(it->second.endPos, startPos_)) {
        it = nextIt;
        ++nextIt;
    }
    if (LessOrEqual(it->second.startPos - spaceWidth_, startPos_)) {
        index = LanesFloor(it->first);
        pos = it->second.startPos;
        return;
    }
    std::reverse_iterator<std::map<int, GridItemMainPos>::iterator> rit(it);
    while (rit != layoutInfo_->posMap_.rend() && GreatNotEqual(rit->second.startPos - spaceWidth_, startPos_)) {
        ++rit;
    }
    --rit;
    pos = rit->second.startPos;
    index = LanesFloor(rit->first);
}

void LazyGridLayoutAlgorithm::GetEndIndexInfo(int32_t& index, float& pos)
{
    if (LessNotEqual(endPos_, 0)) {
        index = -1;
        pos = 0;
        return;
    } else if (GreatNotEqual(startPos_, totalMainSize_)) {
        index = totalItemCount_;
        pos = totalMainSize_;
        return;
    } else if (GreatOrEqual(endPos_, totalMainSize_) || layoutInfo_->endIndex_ >= layoutInfo_->totalItemCount_) {
        pos = totalMainSize_;
        index = LanesCeil(totalItemCount_ - 1);
        return;
    }
    auto it = layoutInfo_->posMap_.find(layoutInfo_->endIndex_);
    if (it == layoutInfo_->posMap_.end()) {
        pos = totalMainSize_;
        index = LanesCeil(layoutInfo_->totalItemCount_ - 1);
        return;
    }
    std::reverse_iterator<std::map<int, GridItemMainPos>::iterator> rit(++it);
    auto nextIt = rit;
    ++nextIt;
    while (nextIt != layoutInfo_->posMap_.rend() && GreatNotEqual(rit->second.startPos, endPos_)) {
        rit = nextIt;
        ++nextIt;
    }
    if (GreatOrEqual(rit->second.endPos + spaceWidth_, endPos_)) {
        index = LanesCeil(rit->first);
        pos = rit->second.endPos;
        return;
    }
    while (it != layoutInfo_->posMap_.end() && LessNotEqual(it->second.endPos + spaceWidth_, endPos_)) {
        ++it;
    }
    --it;
    index = LanesCeil(it->first);
    pos = it->second.endPos;
}

void LazyGridLayoutAlgorithm::CheckRecycle()
{
    auto it = layoutInfo_->posMap_.find(layoutInfo_->startIndex_);
    while (it != layoutInfo_->posMap_.end()) {
        if (LessNotEqual(it->second.endPos, startPos_)) {
            layoutInfo_->startIndex_ = it->first + 1;
            ++it;
        } else {
            break;
        }
    }
    it = layoutInfo_->posMap_.find(layoutInfo_->endIndex_);
    if (it == layoutInfo_->posMap_.end()) {
        return;
    }
    std::reverse_iterator<std::map<int, GridItemMainPos>::iterator> rit(++it);
    while (rit != layoutInfo_->posMap_.rend()) {
        if (GreatNotEqual(rit->second.startPos, endPos_)) {
            layoutInfo_->endIndex_ = rit->first - 1;
            ++rit;
        } else {
            break;
        }
    }
}

void LazyGridLayoutAlgorithm::CheckCacheRecycle()
{
    auto it = layoutInfo_->posMap_.find(layoutInfo_->cachedStartIndex_);
    while (it != layoutInfo_->posMap_.end()) {
        if (LessNotEqual(it->second.endPos, layoutInfo_->cacheStartPos_)) {
            layoutedStartIndex_ = it->first + 1;
            layoutedStart_ = it->second.endPos;
            cachedStartIndex_ = layoutedStartIndex_;
            ++it;
        } else {
            break;
        }
    }
    if (layoutedStartIndex_ >= totalItemCount_) {
        layoutedEndIndex_ = totalItemCount_;
        layoutedEnd_ = totalMainSize_;
        cachedEndIndex_ = layoutedEndIndex_;
        return;
    }
    it = layoutInfo_->posMap_.find(layoutInfo_->cachedEndIndex_);
    if (it == layoutInfo_->posMap_.end()) {
        return;
    }
    std::reverse_iterator<std::map<int, GridItemMainPos>::iterator> rit(++it);
    while (rit != layoutInfo_->posMap_.rend()) {
        if (GreatNotEqual(rit->second.startPos, layoutInfo_->cacheEndPos_)) {
            layoutedEndIndex_ = rit->first - 1;
            layoutedEnd_ = rit->second.startPos;
            cachedEndIndex_ = layoutedEndIndex_;
            ++rit;
        } else {
            break;
        }
    }
    if (layoutedEndIndex_ < 0) {
        layoutedStartIndex_ = -1;
        layoutedStart_ = 0.0f;
        cachedStartIndex_ = layoutedStartIndex_;
        return;
    }
}

void LazyGridLayoutAlgorithm::FixIndexRange(int32_t& startIndex, int32_t& endIndex)
{
    if (startIndex < 0 && endIndex >= 0 && endIndex < totalItemCount_) {
        startIndex = 0;
    }
    if ((endIndex < 0 || endIndex >= totalItemCount_) && startIndex >= 0 && startIndex < totalItemCount_) {
        endIndex = totalItemCount_ - 1;
    }
}

void LazyGridLayoutAlgorithm::CalculateVisibleStartIndex()
{
    layoutInfo_->visibleStartIndex_ = layoutInfo_->startIndex_;
    if (LessOrEqual(viewExtStart_, 0.0f)) {
        return;
    }
    auto iter = layoutInfo_->posMap_.find(layoutInfo_->startIndex_);
    if (iter == layoutInfo_->posMap_.end()) {
        return;
    }
    float visibleStartPos = startPos_ + viewExtStart_;
    while (iter != layoutInfo_->posMap_.end()) {
        if (LessNotEqual(iter->second.endPos, visibleStartPos)) {
            layoutInfo_->visibleStartIndex_ = iter->first + 1;
            ++iter;
        } else {
            break;
        }
    }
}

void LazyGridLayoutAlgorithm::CalculateVisibleEndIndex()
{
    layoutInfo_->visibleEndIndex_ = layoutInfo_->endIndex_;
    if (LessOrEqual(viewExtEnd_, 0.0f)) {
        return;
    }
    auto iter = layoutInfo_->posMap_.find(layoutInfo_->endIndex_);
    if (iter == layoutInfo_->posMap_.end()) {
        return;
    }
    float visibleEndPos = endPos_ - viewExtEnd_;
    std::reverse_iterator<std::map<int32_t, GridItemMainPos>::iterator> riter(++iter);
    while (riter != layoutInfo_->posMap_.rend()) {
        if (GreatNotEqual(riter->second.startPos, visibleEndPos)) {
            layoutInfo_->visibleEndIndex_ = riter->first - 1;
            ++riter;
        } else {
            break;
        }
    }
}

void LazyGridLayoutAlgorithm::MeasureForward(LayoutWrapper* layoutWrapper, int32_t startIndex, float startPos)
{
    float currentEndPos = startPos;
    float currentStartPos = startPos;
    int32_t curIndex = startIndex;
    while (LessOrEqual(currentEndPos, endPos_) && curIndex < totalItemCount_) {
        currentStartPos = currentEndPos;
        float lineSize = 0.0f;
        int32_t laneIdx = 0;
        for (; laneIdx < lanes_ && curIndex + laneIdx < totalItemCount_; laneIdx++) {
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(curIndex + laneIdx));
            if (!wrapper) {
                continue;
            }
            if (CheckNeedMeasure(wrapper, laneIdx)) {
                wrapper->Measure(childLayoutConstraints_[laneIdx]);
            }
            float mainSize = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
            lineSize = std::max(mainSize, lineSize);
        }
        currentEndPos += lineSize;
        for (int32_t i = 0; i < laneIdx; i++) {
            layoutInfo_->SetPosMap(curIndex + i, { i, currentStartPos, currentEndPos });
        }
        layoutInfo_->endIndex_ = curIndex + laneIdx - 1;
        if (curIndex < (totalItemCount_ - 1)) {
            currentEndPos += spaceWidth_;
        }
        curIndex += lanes_;
    }
}

void LazyGridLayoutAlgorithm::MeasureBackward(LayoutWrapper* layoutWrapper, int32_t endIndex, float endPos)
{
    float currentEndPos = endPos;
    float currentStartPos = endPos;
    int32_t curIndex = std::min(endIndex, totalItemCount_ - 1);
    while (curIndex >= 0 && GreatOrEqual(currentStartPos, startPos_)) {
        currentEndPos = currentStartPos;
        float lineSize = 0.0f;
        int32_t laneIdx = curIndex % lanes_;
        for (int32_t i = 0; i <= laneIdx && curIndex - i >= 0; i++) {
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(curIndex - i));
            if (!wrapper) {
                continue;
            }
            if (CheckNeedMeasure(wrapper, laneIdx - i)) {
                wrapper->Measure(childLayoutConstraints_[laneIdx - i]);
            }
            float mainSize = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
            lineSize = std::max(mainSize, lineSize);
        }
        currentStartPos -= lineSize;
        for (int32_t i = 0; i <= laneIdx; i++) {
            layoutInfo_->SetPosMap(curIndex - i, { laneIdx - i, currentStartPos, currentEndPos });
        }
        layoutInfo_->startIndex_ = curIndex - laneIdx;
        if (curIndex > 0) {
            currentStartPos -= spaceWidth_;
        }
        curIndex -= laneIdx + 1;
    }
}

void LazyGridLayoutAlgorithm::LayoutGridItems(LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset)
{
    // DynamicLayout mode: pre-calculate alignment parameters
    bool needAlign = false;
    Alignment align = Alignment::TOP_CENTER;

    if (isDynamicLayout_) {
        auto layoutProperty = AceType::DynamicCast<LazyGridLayoutProperty>(layoutWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(layoutProperty);
        needAlign = true;

        // Get alignment mode (common property, from PositionProperty)
        align = axis_ == Axis::VERTICAL ? Alignment::TOP_CENTER : Alignment::CENTER_LEFT;
        if (layoutProperty->GetPositionProperty()) {
            if (layoutProperty->GetPositionProperty()->HasLocalizedAlignment()) {
                align = ConvertStringToAlignment(layoutProperty->GetPositionProperty()->GetLocalizedAlignmentValue());
            } else {
                align = layoutProperty->GetPositionProperty()->GetAlignment().value_or(align);
            }
        }
    }

    // layout items.
    auto iter = layoutInfo_->posMap_.find(layoutInfo_->startIndex_);
    for (; iter != layoutInfo_->posMap_.end() && iter->first <= layoutInfo_->endIndex_; iter++) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(iter->first));
        if (!wrapper) {
            continue;
        }

        // DynamicLayout: get actual row height from posMap_ (endPos - startPos)
        float currentRowHeight = 0.0f;
        if (needAlign) {
            currentRowHeight = iter->second.endPos - iter->second.startPos;
        }

        // Call SetItemOffset uniformly, handle alignment internally
        SetItemOffset(wrapper, iter->second, crossSize, paddingOffset, needAlign, currentRowHeight, align);

        // Execute Layout or SyncGeometry
        if (wrapper->CheckNeedForceMeasureAndLayout()) {
            wrapper->Layout();
        } else {
            SyncGeometry(wrapper);
        }
    }
}

void LazyGridLayoutAlgorithm::SetItemOffset(RefPtr<LayoutWrapper>& wrapper, const GridItemMainPos& pos,
    float crossSize, const OffsetF& paddingOffset,
    bool needAlign, float rowHeight, Alignment align)
{
    auto offset = paddingOffset;
    float laneWidth = crossSize / lanes_;
    bool isRtl = (layoutDirection_ == TextDirection::RTL);
    if (isRtl) {
        if (axis_ == Axis::VERTICAL) {
            auto size = wrapper->GetGeometryNode()->GetMarginFrameSize();
            float laneOffset = crossPos_[pos.laneIdx];
            offset = offset + OffsetF(crossSize - size.Width() - laneOffset, pos.startPos);
        } else {
            offset = offset + OffsetF(totalMainSize_ - pos.endPos, laneWidth * pos.laneIdx);
        }
    } else {
        if (axis_ == Axis::VERTICAL) {
            offset = offset + OffsetF(crossPos_[pos.laneIdx], pos.startPos);
        } else {
            offset = offset + OffsetF(pos.startPos, crossPos_[pos.laneIdx]);
        }
    }

    // DynamicLayout: apply alignment offset
    if (needAlign) {
        float cellHeight = rowHeight;
        // Calculate alignment offset
        SizeF cellSize = SizeF(crossLens_[pos.laneIdx], cellHeight, axis_);
        auto childSize = wrapper->GetGeometryNode()->GetFrameSize();
        if (!isRtl) {
            auto alignPosition = Alignment::GetAlignPosition(cellSize, childSize, align);
            // Apply alignment offset
            offset = offset + alignPosition;
        } else {
            if (align.GetHorizontal() > 0) {    // Right
                auto alignPosition = Alignment::GetAlignPosition(cellSize, childSize, align);
                alignPosition.SetX(0.0f);
                offset = offset + alignPosition;
            } else {    // Left or Center
                auto alignPosition = Alignment::GetAlignPositionWithDirection(cellSize, childSize, align,
                    layoutDirection_);
                alignPosition.SetY(-alignPosition.GetY());
                offset = offset - alignPosition;
            }
        }
    }

    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
}

void LazyGridLayoutAlgorithm::SyncGeometry(RefPtr<LayoutWrapper>& wrapper)
{
    CHECK_NULL_VOID(wrapper);
    auto host = wrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    host->ForceSyncGeometryNode();
    host->ResetLayoutAlgorithm();
}

void LazyGridLayoutAlgorithm::LayoutCachedItems(LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset)
{
    LayoutCachedItemsForward(layoutWrapper, crossSize, paddingOffset);
    LayoutCachedItemsBackward(layoutWrapper, crossSize, paddingOffset);
    FixIndexRange(cachedStartIndex_, cachedEndIndex_);
    // h/f/s: keep header / footer in the active set so they aren't pruned alongside the item cache window.
    SetHeaderFooterActive(layoutWrapper, cachedStartIndex_, cachedEndIndex_);
    layoutInfo_->layoutedStart_ = layoutedStart_;
    layoutInfo_->layoutedEnd_ = layoutedEnd_;
    layoutInfo_->layoutedStartIndex_ = layoutedStartIndex_;
    layoutInfo_->layoutedEndIndex_ = layoutedEndIndex_;
    layoutInfo_->cacheStartPos_ = cacheStartPos_;
    layoutInfo_->cacheEndPos_ = cacheEndPos_;
    layoutInfo_->cachedStartIndex_ = cachedStartIndex_;
    layoutInfo_->cachedEndIndex_ = cachedEndIndex_;
}

void LazyGridLayoutAlgorithm::LayoutCachedItemsForward(LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset)
{
    auto iter = layoutInfo_->posMap_.begin();
    // h/f/s: posMap_ and cacheStartPos_/cacheEndPos_ are in body-local coords (header subtracted at SetReferences),
    // so the "past the last item" sentinel must also be the body-local end, not the section total.
    const float bodyEnd = totalMainSize_ - layoutInfo_->headerMainSize_ - layoutInfo_->footerMainSize_;
    if (layoutInfo_->endIndex_ >= totalItemCount_ - 1) {
        layoutedEnd_ = bodyEnd;
        cachedEndIndex_ = layoutInfo_->endIndex_;
    } else if (layoutInfo_->endIndex_ < 0) {
        cachedEndIndex_ = -1;
        layoutedEnd_ = 0;
    } else {
        cachedEndIndex_ = layoutInfo_->endIndex_;
        iter = layoutInfo_->posMap_.find(layoutInfo_->endIndex_);
        if (iter == layoutInfo_->posMap_.end()) {
            TAG_LOGE(AceLogTag::ACE_LAZY_GRID, "find end index error:%{public}d", layoutInfo_->endIndex_);
            return;
        }
        layoutedEnd_ = iter->second.endPos + spaceWidth_;
        iter++;
    }
    layoutedEndIndex_ = cachedEndIndex_;
    bool hadDirty = false;
    while (iter != layoutInfo_->posMap_.end() && LessNotEqual(iter->second.startPos, cacheEndPos_)) {
        if (cachedEndIndex_ + 1 != iter->first) {
            break;
        }
        auto wrapper = layoutWrapper->GetChildByIndex(GetRawIndexForItem(iter->first), true);
        if (!wrapper) {
            break;
        }
        SetItemOffset(wrapper, iter->second, crossSize, paddingOffset);
        SyncGeometry(wrapper);
        if (hadDirty || CheckNeedMeasure(wrapper, iter->second.laneIdx)) {
            hadDirty = true;
        } else {
            if (iter->second.laneIdx >= lanes_ - 1) {
                layoutedEnd_ = iter->second.endPos + spaceWidth_;
            }
            layoutedEndIndex_ = iter->first;
        }
        cachedEndIndex_ = iter->first;
        iter++;
    }
}

void LazyGridLayoutAlgorithm::LayoutCachedItemsBackward(LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset)
{
    auto rIter = layoutInfo_->posMap_.rbegin();
    // h/f/s: see note in LayoutCachedItemsForward — sentinel uses body-local end (bodyEnd) to match cacheStartPos_.
    const float bodyEnd = totalMainSize_ - layoutInfo_->headerMainSize_ - layoutInfo_->footerMainSize_;
    if (layoutInfo_->startIndex_ == 0) {
        layoutedStart_ = 0.0f;
        cachedStartIndex_ = 0;
    } else if (layoutInfo_->startIndex_ >= totalItemCount_) {
        layoutedStart_ = bodyEnd;
        cachedStartIndex_ = totalItemCount_;
    } else {
        cachedStartIndex_ = layoutInfo_->startIndex_;
        auto iter = layoutInfo_->posMap_.find(layoutInfo_->startIndex_);
        if (iter == layoutInfo_->posMap_.end()) {
            TAG_LOGE(AceLogTag::ACE_LAZY_GRID, "find start index error:%{public}d", layoutInfo_->endIndex_);
            return;
        }
        layoutedStart_ = iter->second.startPos - spaceWidth_;
        std::reverse_iterator<std::map<int, GridItemMainPos>::iterator> rit(iter);
        rIter = rit;
    }
    layoutedStartIndex_ = cachedStartIndex_;
    bool hadDirty = false;
    while (rIter != layoutInfo_->posMap_.rend() && GreatNotEqual(rIter->second.endPos, cacheStartPos_)) {
        if (cachedStartIndex_ - 1 != rIter->first) {
            break;
        }
        auto wrapper = layoutWrapper->GetChildByIndex(GetRawIndexForItem(rIter->first), true);
        if (!wrapper) {
            break;
        }
        SetItemOffset(wrapper, rIter->second, crossSize, paddingOffset);
        SyncGeometry(wrapper);
        if (hadDirty || CheckNeedMeasure(wrapper, rIter->second.laneIdx)) {
            hadDirty = true;
        } else {
            if (rIter->second.laneIdx <= 0) {
                layoutedStart_ = rIter->second.startPos - spaceWidth_;
            }
            layoutedStartIndex_ = rIter->first;
        }
        cachedStartIndex_ = rIter->first;
        rIter++;
    }
}

bool LazyGridLayoutAlgorithm::InitPredictForwardState(int32_t& currIndex, int32_t& currLane,
    float& currPos, float& mainSize, float& layoutedEnd)
{
    currIndex = layoutInfo_->layoutedEndIndex_;
    layoutedEnd = layoutInfo_->layoutedEnd_;
    currLane = 0;
    currPos = layoutedEnd;
    mainSize = 0.0f;
    // Allow forward prediction when not yet laid out (currIndex<0) and forward layout,
    // or when already laid out (currIndex>=0) and item exists in posMap
    if (currIndex < 0 && forwardLayout_) {
        currIndex = -1;
        return true;
    } else if (currIndex >= 0 && layoutInfo_->posMap_.find(currIndex) != layoutInfo_->posMap_.end()) {
        auto iter = layoutInfo_->posMap_.find(currIndex);
        currLane = iter->second.laneIdx;
        currPos = iter->second.startPos;
        mainSize = iter->second.endPos - currPos;
        return true;
    } else {
        return false;
    }
}

void LazyGridLayoutAlgorithm::PredictLayoutForward(LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset)
{
    int32_t currIndex;
    int32_t currLane;
    float currPos;
    float mainSize;
    float layoutedEnd;
    if (!InitPredictForwardState(currIndex, currLane, currPos, mainSize, layoutedEnd)) {
        return;
    }

    auto deadline = layoutInfo_->deadline_.value();
    bool needFix = false;
    while (currIndex < totalItemCount_ - 1 && LessNotEqual(layoutedEnd, layoutInfo_->cacheEndPos_)) {
        if (GetSysTimestamp() > deadline) {
            break;
        }
        int32_t index = currIndex + 1;
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(index));
        if (!wrapper || !wrapper->GetHostNode() || !wrapper->GetHostNode()->RenderCustomChild(deadline)) {
            break;
        }
        currLane += 1;
        if (currLane >= lanes_) {
            currLane = 0;
            currPos = layoutedEnd;
            mainSize = 0.0f;
            if (needFix) {
                FixPosMapBackward(currIndex);
                needFix = false;
            }
        }
        wrapper->Measure(childLayoutConstraints_[currLane]);
        auto size = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
        needFix = needFix || (currLane > 0 && GreatNotEqual(size, mainSize));
        mainSize = std::max(mainSize, size);
        GridItemMainPos pos { currLane, currPos, currPos + mainSize };
        layoutInfo_->SetCachedPosMap(index, pos);
        SetItemOffset(wrapper, pos, crossSize, paddingOffset);
        wrapper->Layout();
        currIndex = index;
        layoutedEnd = (currLane >= lanes_ - 1) ? (currPos + mainSize + spaceWidth_) : layoutedEnd;
    }
    if (currLane >= lanes_ - 1 && needFix) {
        FixPosMapBackward(currIndex);
    }
    layoutedEndIndex_ = currIndex;
    cachedEndIndex_ = std::max(layoutInfo_->cachedEndIndex_, currIndex);
    layoutedEnd_ = layoutedEnd;
}

bool LazyGridLayoutAlgorithm::InitPredictBackwardState(int32_t& currIndex, int32_t& currLane,
    float& currPos, float& mainSize, float& layoutedStart)
{
    currIndex = layoutInfo_->layoutedStartIndex_;
    layoutedStart = layoutInfo_->layoutedStart_;
    currLane = lanes_ - 1;
    currPos = layoutedStart;
    mainSize = 0.0f;
    // Allow backward prediction when not yet laid out (currIndex<0) and backward layout,
    // or when already laid out (currIndex>=0) and item exists in posMap
    if (currIndex < 0 && !forwardLayout_) {
        currIndex = totalItemCount_;
        return true;
    } else if (currIndex >= 0 && layoutInfo_->posMap_.find(currIndex) != layoutInfo_->posMap_.end()) {
        auto iter = layoutInfo_->posMap_.find(currIndex);
        currLane = iter->second.laneIdx;
        currPos = iter->second.endPos;
        mainSize = currPos - iter->second.startPos;
        return true;
    } else {
        return false;
    }
}

void LazyGridLayoutAlgorithm::PredictLayoutBackward(LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset)
{
    int32_t currIndex;
    int32_t currLane;
    float currPos;
    float mainSize;
    float layoutedStart;
    if (!InitPredictBackwardState(currIndex, currLane, currPos, mainSize, layoutedStart)) {
        return;
    }

    auto deadline = layoutInfo_->deadline_.value();
    bool needFix = false;
    while (currIndex > 0 && (GreatNotEqual(layoutedStart, layoutInfo_->cacheStartPos_))) {
        if (GetSysTimestamp() > deadline) {
            break;
        }
        int32_t index = currIndex - 1;
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(index));
        if (!wrapper || !wrapper->GetHostNode() || !wrapper->GetHostNode()->RenderCustomChild(deadline)) {
            break;
        }
        currLane -= 1;
        if (currLane < 0) {
            currLane = lanes_ - 1;
            currPos = layoutedStart;
            mainSize = 0.0f;
            if (needFix) {
                FixPosMapForward(currIndex, layoutWrapper, crossSize, paddingOffset);
                needFix = false;
            }
        }
        wrapper->Measure(childLayoutConstraints_[currLane]);
        float size = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
        needFix = needFix || (currLane < lanes_ - 1 && GreatNotEqual(size, mainSize));
        mainSize = std::max(mainSize, size);
        GridItemMainPos pos { currLane, currPos - mainSize, currPos };
        layoutInfo_->SetCachedPosMap(index, pos);
        SetItemOffset(wrapper, pos, crossSize, paddingOffset);
        wrapper->Layout();
        currIndex = index;
        layoutedStart = (currLane <= 0) ? (currPos - mainSize - spaceWidth_) : layoutedStart;
    }
    if (currLane <= 0 && needFix) {
        FixPosMapForward(currIndex, layoutWrapper, crossSize, paddingOffset);
    }
    layoutedStartIndex_ = currIndex;
    cachedStartIndex_ = layoutInfo_->cachedStartIndex_ >= 0
        ? std::min(layoutInfo_->cachedStartIndex_, currIndex)
        : currIndex;
    layoutedStart_ = layoutedStart;
}

void LazyGridLayoutAlgorithm::SyncPredictLayoutInfo(LayoutWrapper* layoutWrapper)
{
    // Recycle items outside visible and cache range
    CheckRecycle();
    CheckCacheRecycle();
    CalculateVisibleStartIndex();
    CalculateVisibleEndIndex();
    // Expand cached range to cover the full predicted area
    if (LessOrEqual(layoutedStart_, layoutInfo_->cacheStartPos_) || layoutedStartIndex_ <= 0) {
        cachedStartIndex_ = layoutedStartIndex_;
    }
    if (GreatOrEqual(layoutedEnd_, layoutInfo_->cacheEndPos_) || layoutedEndIndex_ >= totalItemCount_ - 1) {
        cachedEndIndex_ = layoutedEndIndex_;
    }
    FixIndexRange(cachedStartIndex_, cachedEndIndex_);
    FixIndexRange(layoutedStartIndex_, layoutedEndIndex_);
    // Update active child range if cache boundaries changed
    if ((layoutInfo_->cachedStartIndex_ != cachedStartIndex_) || (layoutInfo_->cachedEndIndex_ != cachedEndIndex_)) {
        SetHeaderFooterActive(layoutWrapper, cachedStartIndex_, cachedEndIndex_);
    }
    // Sync prediction results back to layoutInfo
    layoutInfo_->layoutedStartIndex_ = layoutedStartIndex_;
    layoutInfo_->cachedStartIndex_ = cachedStartIndex_;
    layoutInfo_->layoutedStart_ = layoutedStart_;

    layoutInfo_->layoutedEndIndex_ = layoutedEndIndex_;
    layoutInfo_->cachedEndIndex_ = cachedEndIndex_;
    layoutInfo_->layoutedEnd_ = layoutedEnd_;

    // Skip posMap update if only self measure changed, as child positions remain valid
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPropertyChangeFlag() == PROPERTY_UPDATE_MEASURE_SELF) {
        // Reset to body total: Measure() re-adds header+footer afterward, so keeping the section total here would
        // double-count them every predictive frame.
        totalMainSize_ = layoutInfo_->totalMainSize_ - layoutInfo_->headerMainSize_ - layoutInfo_->footerMainSize_;
        return;
    }
    layoutInfo_->UpdatePosMap();
    totalMainSize_ = layoutInfo_->totalMainSize_;
}

void LazyGridLayoutAlgorithm::FixPosMapBackward(int32_t index)
{
    auto iter = layoutInfo_->posMap_.find(index);
    if (iter == layoutInfo_->posMap_.end()) {
        return;
    }
    float mainSize = iter->second.endPos - iter->second.startPos;
    for (int32_t i = 1; i < lanes_; i++) {
        auto iter = layoutInfo_->posMap_.find(index - i);
        if (iter == layoutInfo_->posMap_.end()) {
            return;
        }
        iter->second.endPos = iter->second.startPos + mainSize;
    }
}

void LazyGridLayoutAlgorithm::FixPosMapForward(int32_t index, LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset)
{
    auto iter = layoutInfo_->posMap_.find(index);
    if (iter == layoutInfo_->posMap_.end()) {
        return;
    }
    float mainSize = iter->second.endPos - iter->second.startPos;
    for (int32_t i = 1; i < lanes_; i++) {
        auto iter = layoutInfo_->posMap_.find(index + i);
        if (iter == layoutInfo_->posMap_.end()) {
            return;
        }
        float startPos = iter->second.endPos - mainSize;
        if (!NearEqual(startPos, iter->second.startPos)) {
            iter->second.startPos = startPos;
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(index + i));
            CHECK_NULL_VOID(wrapper);
            SetItemOffset(wrapper, iter->second, crossSize, paddingOffset);
            SyncGeometry(wrapper);
        }
    }
}

void LazyGridLayoutAlgorithm::UpdateHeaderFooterIndexes(LayoutWrapper* layoutWrapper)
{
    if (!layoutWrapper) {
        headerIndex_ = -1;
        footerIndex_ = -1;
        return;
    }
    // Re-resolve edges from the owner: a reused algorithm's construction-time weak-ref dangles after the edge
    // nodes are rebuilt (e.g. toggling sticky), which would otherwise drop the header.
    if (auto host = layoutWrapper->GetHostNode()) {
        if (auto pattern = host->GetPattern<LazyGridLayoutPattern>()) {
            header_ = pattern->GetHeaderNode();
            footer_ = pattern->GetFooterNode();
        }
    }
    const auto rawCount = layoutWrapper->GetTotalChildCount();
    // Header / footer are normalized by SyncHeaderFooter(): header at raw index 0, footer at raw index last.
    const bool hasHeader = header_.Upgrade() != nullptr && rawCount > 0;
    const bool hasFooter = footer_.Upgrade() != nullptr && rawCount > (hasHeader ? 1 : 0);
    headerIndex_ = hasHeader ? 0 : -1;
    footerIndex_ = hasFooter ? rawCount - 1 : -1;
}

int32_t LazyGridLayoutAlgorithm::CalculateItemCount(LayoutWrapper* layoutWrapper) const
{
    CHECK_NULL_RETURN(layoutWrapper, 0);
    // rawCount is the host's total child count. Content item count = rawCount - header(0/1) - footer(0/1).
    // hasFooter additionally requires footerIndex_ != headerIndex_ so that a corner case where a single section
    // edge is held by both header and footer never gets subtracted twice.
    const auto rawCount = layoutWrapper->GetTotalChildCount();
    const bool hasHeader = headerIndex_ >= 0 && headerIndex_ < rawCount;
    const bool hasFooter = footerIndex_ >= 0 && footerIndex_ < rawCount && footerIndex_ != headerIndex_;
    return std::max(rawCount - (hasHeader ? 1 : 0) - (hasFooter ? 1 : 0), 0);
}

int32_t LazyGridLayoutAlgorithm::GetRawIndexForItem(int32_t itemIndex) const
{
    return itemIndex + (headerIndex_ >= 0 ? 1 : 0);
}

StickyStyle LazyGridLayoutAlgorithm::ResolveStickyStyle(LayoutWrapper* layoutWrapper) const
{
    CHECK_NULL_RETURN(layoutWrapper, StickyStyle::NONE);
    auto layoutProperty = AceType::DynamicCast<LazyGridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, StickyStyle::NONE);
    return layoutProperty->GetStickyStyle().value_or(StickyStyle::NONE);
}

float LazyGridLayoutAlgorithm::MeasureHeader(LayoutWrapper* layoutWrapper)
{
    float headerMainSize = 0.0f;
    if (header_.Upgrade() && headerIndex_ >= 0) {
        headerMainSize = HeaderFooterUtils::MeasureHeaderFooter(
            layoutWrapper, headerIndex_, edgeLayoutConstraint_, axis_);
    }
    layoutInfo_->headerMainSize_ = headerMainSize;
    return headerMainSize;
}

float LazyGridLayoutAlgorithm::MeasureFooter(LayoutWrapper* layoutWrapper)
{
    float footerMainSize = 0.0f;
    if (footer_.Upgrade() && footerIndex_ >= 0) {
        footerMainSize = HeaderFooterUtils::MeasureHeaderFooter(
            layoutWrapper, footerIndex_, edgeLayoutConstraint_, axis_);
    }
    layoutInfo_->footerMainSize_ = footerMainSize;
    return footerMainSize;
}

void LazyGridLayoutAlgorithm::LayoutHeaderFooter(
    LayoutWrapper* layoutWrapper, int32_t rawIndex, const OffsetF& offset, bool isSticky) const
{
    if (rawIndex < 0) {
        return;
    }
    auto child = layoutWrapper->GetChildByIndex(rawIndex);
    if (!child) {
        child = layoutWrapper->GetOrCreateChildByIndex(rawIndex);
    }
    CHECK_NULL_VOID(child);
    auto hostNode = child->GetHostNode();
    // Once promoted by sticky the zIndex stays at 1 even after sticky toggles off; for a header/footer with no
    // overlapping sibling the value is visually neutral, and not restoring sidesteps the ambiguity between
    // framework-set 1 and user-set 1.
    if (isSticky) {
        HeaderFooterUtils::EnsureStickyDefaultZIndex(hostNode);
    }
    auto geometryNode = child->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto finalOffset = offset;
    if (layoutDirection_ == TextDirection::RTL && axis_ == Axis::VERTICAL) {
        finalOffset.SetX(offset.GetX() + crossSize_ - geometryNode->GetMarginFrameSize().Width());
    }
    geometryNode->SetMarginFrameOffset(finalOffset);
    // Header / footer must always be in the render tree on every layout pass. GetChildByIndex() above does not
    // activate the child, so a stale inactive state from a prior frame would otherwise suppress
    // SyncGeometryProperties() and freeze the edge at its previous rendered position.
    child->SetActive(true);
    child->Layout();
}

void LazyGridLayoutAlgorithm::LayoutHeader(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset,
    StickyStyle stickyStyle, float stickyHeaderPos) const
{
    if (headerIndex_ < 0) {
        return;
    }
    auto isSticky = stickyStyle == StickyStyle::HEADER || stickyStyle == StickyStyle::BOTH;
    auto offset = paddingOffset + (isSticky ? OffsetF(0.0f, stickyHeaderPos) : OffsetF());
    LayoutHeaderFooter(layoutWrapper, headerIndex_, offset, isSticky);
}

void LazyGridLayoutAlgorithm::LayoutFooter(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset,
    StickyStyle stickyStyle, float stickyFooterPos) const
{
    if (footerIndex_ < 0) {
        return;
    }
    auto isSticky = stickyStyle == StickyStyle::FOOTER || stickyStyle == StickyStyle::BOTH;
    auto footerPos = isSticky ? stickyFooterPos : totalMainSize_ - layoutInfo_->footerMainSize_;
    auto offset = OffsetF(paddingOffset.GetX(), paddingOffset.GetY() + footerPos);
    LayoutHeaderFooter(layoutWrapper, footerIndex_, offset, isSticky);
}

void LazyGridLayoutAlgorithm::SetHeaderFooterActive(
    LayoutWrapper* layoutWrapper, int32_t cachedStart, int32_t cachedEnd) const
{
    // Item cache window is expressed in item indices. Translate to raw indices and union with header /
    // footer so the active set covers the full section.
    if (headerIndex_ < 0 && footerIndex_ < 0) {
        layoutWrapper->SetActiveChildRange(cachedStart, cachedEnd, 0, 0);
        return;
    }
    ActiveChildSets activeChildSets;
    int32_t rawStart = -1;
    int32_t rawEnd = -1;
    if (cachedStart >= 0 && cachedEnd >= cachedStart) {
        rawStart = GetRawIndexForItem(cachedStart);
        rawEnd = GetRawIndexForItem(cachedEnd);
        for (auto index = rawStart; index <= rawEnd; ++index) {
            activeChildSets.activeItems.insert(index);
        }
    }
    if (headerIndex_ >= 0) {
        activeChildSets.activeItems.insert(headerIndex_);
    }
    if (footerIndex_ >= 0) {
        activeChildSets.activeItems.insert(footerIndex_);
    }
    // Pass nullopt: a real range would also deactivate the header/footer nodes. Activate content items separately.
    layoutWrapper->SetActiveChildRange(std::optional<ActiveChildSets>(activeChildSets), std::nullopt);
    ActivateContentItemRange(layoutWrapper, rawStart, rawEnd);
}

void LazyGridLayoutAlgorithm::ActivateContentItemRange(
    LayoutWrapper* layoutWrapper, int32_t rawStart, int32_t rawEnd) const
{
    if (rawStart < 0) {
        return;
    }
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    int32_t childStart = 0;
    for (const auto& child : host->GetChildren()) {
        if (!child) {
            continue;
        }
        auto childCount = child->FrameCount();
        if (childCount <= 0) {
            continue;
        }
        const auto childEnd = childStart + childCount - 1;
        const bool isHeader = headerIndex_ >= childStart && headerIndex_ <= childEnd;
        const bool isFooter = footerIndex_ >= childStart && footerIndex_ <= childEnd;
        if (!isHeader && !isFooter) {
            child->DoSetActiveChildRange(rawStart - childStart, rawEnd - childStart, 0, 0);
        }
        childStart += childCount;
    }
}
} // namespace OHOS::Ace::NG
