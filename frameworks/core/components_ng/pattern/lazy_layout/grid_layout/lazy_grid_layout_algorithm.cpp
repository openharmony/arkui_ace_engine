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
#include <cstdint>
#include <iterator>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {

void LazyGridLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutInfo_);
    totalItemCount_ = layoutWrapper->GetTotalChildCount();
    layoutInfo_->totalItemCount_ = totalItemCount_;
    auto layoutProperty = AceType::DynamicCast<LazyGridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint().value();
    auto contentIdealSize = CreateIdealSize(
        contentConstraint, axis_, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS));
    realMainSize_ = layoutWrapper->GetGeometryNode()->GetPaddingSize().MainSize(axis_);
    UpdateReferencePos(layoutWrapper, contentConstraint.viewPosRef);
    UpdateGap(layoutProperty, contentIdealSize);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    UpdateGridItemConstraint(contentIdealSize, childLayoutConstraint);
    totalMainSize_ = layoutInfo_->totalMainSize_;

    if (totalItemCount_ == 0) {
        layoutInfo_->posMap_.clear();
        layoutInfo_->startIndex_ = -1;
        layoutInfo_->endIndex_ = -1;
    } else if (needAllLayout_) {
        MeasureGridItemAll(layoutWrapper);
    } else {
        MeasureGridItemLazy(layoutWrapper);
    }

    SetFrameSize(layoutWrapper, contentIdealSize, padding);
}

void LazyGridLayoutAlgorithm::SetFrameSize(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize,
    const PaddingPropertyF& padding)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    OptionalSizeF frameSize;
    // Use idea size first if it is valid.
    frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
    if (frameSize.IsValid()) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
        return;
    }
    contentIdealSize.SetMainSize(totalMainSize_, axis_);
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
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto paddingOffset = OffsetF(left, top);
    float crossSize = GetCrossAxisSize(size, axis_);
    if (layoutInfo_->deadline_) {
        PredictLayoutForward(layoutWrapper, crossSize, paddingOffset);
        PredictLayoutBackward(layoutWrapper, crossSize, paddingOffset);
        return;
    }
    LayoutGridItems(layoutWrapper, crossSize, paddingOffset);
    LayoutCachedItems(layoutWrapper, crossSize, paddingOffset);
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
    auto crossPercentRefer = GetCrossAxisSize(contentConstraint.percentReference, axis_);
    crossSize_ = selfIdealSize.CrossSize(axis_).value_or(crossPercentRefer);
    auto cross = ParseTemplateArgs(columnsTemplate, crossSize_, laneGutter_, totalItemCount_);
    laneGutter_ = cross.second;
    if (cross.first.empty()) {
        cross.first = { crossSize_ };
    }
    crossLens_ = std::move(cross.first);
    lanes_ = crossLens_.size();
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

void LazyGridLayoutAlgorithm::UpdateReferencePos(LayoutWrapper* layoutWrapper,
    const std::optional<ViewPosReference>& posRef)
{
    if (!posRef.has_value() || posRef.value().axis != axis_) {
        needAllLayout_ = true;
        return;
    }
    forwardLayout_ = posRef.value().referenceEdge == ReferenceEdge::START;
    referencePos_ = posRef.value().referencePos;
    if (forwardLayout_) {
        startPos_ = posRef.value().viewPosStart - referencePos_;
        endPos_ = posRef.value().viewPosEnd - referencePos_;
    } else {
        referencePos_ += totalMainSize_ - realMainSize_;
        startPos_ = posRef.value().viewPosStart - (referencePos_ - totalMainSize_);
        endPos_ = posRef.value().viewPosEnd - (referencePos_ - totalMainSize_);
    }
    float viewSize = posRef.value().viewPosEnd - posRef.value().viewPosStart;
    cacheStartPos_ = startPos_ - viewSize * cacheSize_;
    cacheEndPos_ = endPos_ + viewSize * cacheSize_;
    needAllLayout_ = false;
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
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(curIndex + laneIdx);
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
    layoutInfo_->totalMainSize_ = totalSize;
    totalMainSize_ = totalSize;
}

void LazyGridLayoutAlgorithm::MeasureGridItemLazy(LayoutWrapper* layoutWrapper)
{
    if (forwardLayout_) {
        int32_t startIndex = 0;
        float startPos = 0.0f;
        GetStartIndexInfo(startIndex, startPos);
        layoutInfo_->SetLanes(lanes_);
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
    totalMainSize_ = layoutInfo_->totalMainSize_;
}

void LazyGridLayoutAlgorithm::GetStartIndexInfo(int32_t& index, float& pos)
{
    if (GreatNotEqual(startPos_, totalMainSize_)) {
        index = totalItemCount_;
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
        index = std::min(it->first, totalItemCount_ - 1);
        pos = it->second.startPos;
        return;
    }
    std::reverse_iterator<std::map<int, GridItemMainPos>::iterator> rit(it);
    while (rit != layoutInfo_->posMap_.rend() && GreatNotEqual(rit->second.startPos - spaceWidth_, startPos_)) {
        ++rit;
    }
    --rit;
    pos = rit->second.startPos;
    index = rit->first;
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
    } else if (GreatOrEqual(endPos_, totalMainSize_) || layoutInfo_->endIndex_ >= totalItemCount_) {
        pos = totalMainSize_;
        index = totalItemCount_ - 1;
        return;
    }
    auto it = layoutInfo_->posMap_.find(layoutInfo_->endIndex_);
    if (it == layoutInfo_->posMap_.end()) {
        pos = totalMainSize_;
        index = totalItemCount_ - 1;
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
        index = std::min(rit->first, totalItemCount_ - 1);
        pos = rit->second.endPos;
        return;
    }
    while (it != layoutInfo_->posMap_.end() && LessNotEqual(it->second.endPos + spaceWidth_, endPos_)) {
        ++it;
    }
    --it;
    index = it->first;
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
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(curIndex + laneIdx);
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
    while (curIndex >= 0 && GreatNotEqual(currentStartPos, startPos_)) {
        currentEndPos = currentStartPos;
        float lineSize = 0.0f;
        int32_t laneIdx = endIndex % lanes_;
        for (int32_t i = 0; i <= laneIdx && curIndex - i >= 0; i++) {
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(curIndex - i);
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
    // layout items.
    auto iter = layoutInfo_->posMap_.find(layoutInfo_->startIndex_);
    for (; iter != layoutInfo_->posMap_.end() && iter->first <= layoutInfo_->endIndex_; iter++) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(iter->first);
        if (!wrapper) {
            continue;
        }
        SetItemOffset(wrapper, iter->second, crossSize, paddingOffset);
        if (wrapper->CheckNeedForceMeasureAndLayout()) {
            wrapper->Layout();
        } else {
            SyncGeometry(wrapper);
        }
    }
}

void LazyGridLayoutAlgorithm::SetItemOffset(RefPtr<LayoutWrapper>& wrapper, const GridItemMainPos& pos,
    float crossSize, const OffsetF& paddingOffset)
{
    auto offset = paddingOffset;
    float laneWidth = crossSize / lanes_;
    if (layoutDirection_ == TextDirection::RTL) {
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
    if (cachedStartIndex_ < 0 && cachedEndIndex_ >= 0) {
        cachedStartIndex_ = 0;
    }
    if (cachedEndIndex_ >= totalItemCount_ && cachedStartIndex_ <= totalItemCount_ - 1) {
        cachedEndIndex_ = totalItemCount_ - 1;
    }
    layoutWrapper->SetActiveChildRange(cachedStartIndex_, cachedEndIndex_, 0, 0);
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
    if (layoutInfo_->endIndex_ >= totalItemCount_ - 1) {
        layoutedEnd_ = totalMainSize_;
        cachedEndIndex_ = layoutInfo_->endIndex_;
    }
    auto iter = layoutInfo_->posMap_.begin();
    if (layoutInfo_->endIndex_ < 0) {
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
        auto wrapper = layoutWrapper->GetChildByIndex(iter->first, true);
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
    if (layoutInfo_->startIndex_ == 0) {
        layoutedStart_ = 0.0f;
        cachedStartIndex_ = 0;
    }
    auto rIter = layoutInfo_->posMap_.rbegin();
    if (layoutInfo_->startIndex_ >= totalItemCount_) {
        layoutedStart_ = totalMainSize_;
        cachedStartIndex_ = totalItemCount_;
    } else {
        cachedStartIndex_ = layoutInfo_->startIndex_;
        auto iter = layoutInfo_->posMap_.find(layoutInfo_->startIndex_);
        if (iter == layoutInfo_->posMap_.end()) {
            TAG_LOGE(AceLogTag::ACE_LAZY_GRID, "find start index error:%{public}d", layoutInfo_->endIndex_);
            return;
        }
        layoutedStart_ = iter->second.startPos;
        std::reverse_iterator<std::map<int, GridItemMainPos>::iterator> rit(iter);
        rIter = rit;
    }
    layoutedStartIndex_ = cachedStartIndex_;
    bool hadDirty = false;
    while (rIter != layoutInfo_->posMap_.rend() && GreatNotEqual(rIter->second.endPos, cacheStartPos_)) {
        if (cachedStartIndex_ - 1 != rIter->first) {
            break;
        }
        auto wrapper = layoutWrapper->GetChildByIndex(rIter->first, true);
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

void LazyGridLayoutAlgorithm::PredictLayoutForward(LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset)
{
    int32_t currIndex = layoutInfo_->layoutedEndIndex_;
    auto iter = layoutInfo_->posMap_.find(currIndex);
    if (iter == layoutInfo_->posMap_.end()) {
        return;
    }
    float layoutedEnd = layoutInfo_->layoutedEnd_;
    int32_t currLane = iter->second.laneIdx;
    int32_t currPos = iter->second.startPos;
    auto deadline = layoutInfo_->deadline_.value();
    float mainSize = iter->second.endPos - currPos;
    bool needFix = false;
    while (currIndex < totalItemCount_ - 1 && LessNotEqual(layoutedEnd, cacheEndPos_)) {
        if (GetSysTimestamp() > deadline) {
            break;
        }
        int32_t index = currIndex + 1;
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
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
        layoutInfo_->SetPosMap(index, pos);
        SetItemOffset(wrapper, pos, crossSize, paddingOffset);
        wrapper->Layout();
        currIndex = index;
        layoutedEnd = (currLane >= lanes_ - 1) ? (currPos + mainSize + spaceWidth_) : layoutedEnd;
    }
    if (currLane >= lanes_ - 1 && needFix) {
        FixPosMapBackward(currIndex);
    }
    layoutInfo_->layoutedEndIndex_ = currIndex;
    layoutInfo_->cachedEndIndex_ = std::max(layoutInfo_->cachedEndIndex_, currIndex);
    layoutInfo_->layoutedEnd_ = layoutedEnd;
}

void LazyGridLayoutAlgorithm::PredictLayoutBackward(LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset)
{
    int32_t currIndex = layoutInfo_->layoutedStartIndex_;
    auto iter = layoutInfo_->posMap_.find(currIndex);
    if (iter == layoutInfo_->posMap_.end()) {
        return;
    }
    float layoutedStart = layoutInfo_->layoutedStart_;
    int32_t currLane = iter->second.laneIdx;
    int32_t currPos = iter->second.endPos;
    auto deadline = layoutInfo_->deadline_.value();
    float mainSize = currPos - iter->second.startPos;
    bool needFix = false;
    while (currIndex > 0 && (GreatNotEqual(layoutedStart, cacheStartPos_))) {
        if (GetSysTimestamp() > deadline) {
            break;
        }
        int32_t index = currIndex - 1;
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
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
        layoutInfo_->SetPosMap(index, pos);
        SetItemOffset(wrapper, pos, crossSize, paddingOffset);
        wrapper->Layout();
        currIndex = index;
        layoutedStart = (currLane <= 0) ? (currPos - mainSize - spaceWidth_) : layoutedStart;
    }
    if (currLane <= 0 && needFix) {
        FixPosMapForward(currIndex, layoutWrapper, crossSize, paddingOffset);
    }
    layoutInfo_->layoutedStartIndex_ = currIndex;
    layoutInfo_->cachedStartIndex_ = std::max(layoutInfo_->cachedStartIndex_, currIndex);
    layoutInfo_->layoutedStart_ = layoutedStart;
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
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index + i);
            CHECK_NULL_VOID(wrapper);
            SetItemOffset(wrapper, iter->second, crossSize, paddingOffset);
            SyncGeometry(wrapper);
        }
    }
}
} // namespace OHOS::Ace::NG
