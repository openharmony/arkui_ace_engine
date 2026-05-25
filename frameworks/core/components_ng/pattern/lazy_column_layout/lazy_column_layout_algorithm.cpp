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

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_algorithm.h"

#include <cstddef>
#include <cstdint>
#include <iterator>

#include "base/utils/time_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void LazyColumnLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper && layoutInfo_);
    auto layoutProperty = AceType::DynamicCast<LazyColumnLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint().value_or(LayoutConstraintF());
    auto contentIdealSize = CreateIdealSize(contentConstraint, Axis::VERTICAL, layoutProperty->GetMeasureType());
    if (!contentIdealSize.Width().has_value()) {
        auto maxSize = contentConstraint.maxSize.Width();
        if (GreaterOrEqualToInfinity(maxSize)) {
            maxSize = contentConstraint.percentReference.Width();
        }
        contentIdealSize.SetWidth(maxSize);
    }
    UpdateHeaderFooterIndexes(layoutWrapper);
    totalItemCount_ = CalculateItemCount(layoutWrapper);
    totalMainSize_ = layoutInfo_->totalMainSize_;
    UpdatePosReference(layoutWrapper, contentConstraint.viewPosRef);
    UpdateAttribute(layoutProperty, contentConstraint);
    UpdateChildConstraint(layoutProperty, contentIdealSize);

    // Measure header first so the body baseline starts at headerMainSize_.
    MeasureHeader(layoutWrapper);

    if (totalItemCount_ == 0) {
        layoutInfo_->SetTotalItemCount(0);
        totalMainSize_ = 0.0f;
    } else if (layoutInfo_->deadline_) {
        layoutInfo_->SetTotalItemCount(totalItemCount_);
        layoutInfo_->SetSpace(space_);
        auto crossSize = contentIdealSize.Width().value();
        auto padding = layoutProperty->CreatePaddingAndBorder();
        auto paddingOffset = OffsetF(padding.left.value_or(0.0f), padding.top.value_or(0.0f));
        PredictLayoutForward(layoutWrapper, crossSize, paddingOffset);
        PredictLayoutBackward(layoutWrapper, crossSize, paddingOffset);
        SyncPredictLayoutInfo(layoutWrapper);
    } else if (needAllLayout_) {
        MeasureAllItems(layoutWrapper);
    } else {
        MeasureItemsLazy(layoutWrapper);
    }

    // Measure footer last so its size is available before we recompute total main size below.
    MeasureFooter(layoutWrapper);
    // body span is the lane content excluding footer; clamp at headerMainSize_ so an empty list still
    // reports header height as the body baseline (mirrors LazyVWaterFlowLayout body-height semantics).
    const auto bodyEnd = std::max(layoutInfo_->headerMainSize_, totalMainSize_);
    totalMainSize_ = bodyEnd + layoutInfo_->footerMainSize_;
    layoutInfo_->totalMainSize_ = totalMainSize_;

    SetFrameSize(layoutWrapper, contentIdealSize);
}

void LazyColumnLayoutAlgorithm::MeasureHeader(LayoutWrapper* layoutWrapper)
{
    float headerMainSize = 0.0f;
    if (header_.Upgrade() && headerIndex_ >= 0) {
        headerMainSize = HeaderFooterUtils::MeasureHeaderFooter(
            layoutWrapper, headerIndex_, edgeLayoutConstraint_, Axis::VERTICAL);
    }
    layoutInfo_->headerMainSize_ = headerMainSize;
}

void LazyColumnLayoutAlgorithm::MeasureFooter(LayoutWrapper* layoutWrapper)
{
    float footerMainSize = 0.0f;
    if (footer_.Upgrade() && footerIndex_ >= 0) {
        footerMainSize = HeaderFooterUtils::MeasureHeaderFooter(
            layoutWrapper, footerIndex_, edgeLayoutConstraint_, Axis::VERTICAL);
    }
    layoutInfo_->footerMainSize_ = footerMainSize;
}

void LazyColumnLayoutAlgorithm::UpdatePosReference(LayoutWrapper* layoutWrapper,
    std::optional<ViewPosReference>& posRef)
{
    if (!posRef.has_value()) {
        posRef = LazyLayoutUtils::GetViewPosReference(layoutWrapper->GetHostNode());
    }
    if (!posRef.has_value() || posRef.value().axis != Axis::VERTICAL) {
        needAllLayout_ = true;
        return;
    }
    forwardLayout_ = posRef.value().referenceEdge == ReferenceEdge::START;
    referencePos_ = posRef.value().referencePos;
    viewExtStart_ = posRef.value().viewExtStart;
    viewExtEnd_ = posRef.value().viewExtEnd;
    if (forwardLayout_) {
        startPos_ = posRef.value().viewPosStart - viewExtStart_ - referencePos_;
        endPos_ = posRef.value().viewPosEnd + viewExtEnd_ - referencePos_;
    } else {
        auto geometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto realMainSize = geometryNode->GetPaddingSize().Height();
        referencePos_ += totalMainSize_ - realMainSize;
        startPos_ = posRef.value().viewPosStart - viewExtStart_ - (referencePos_ - totalMainSize_);
        endPos_ = posRef.value().viewPosEnd + viewExtEnd_ - (referencePos_ - totalMainSize_);
    }
    float viewSize = posRef.value().viewPosEnd - posRef.value().viewPosStart;
    cacheStartPos_ = startPos_ - viewSize * cacheSize_;
    cacheEndPos_ = endPos_ + viewSize * cacheSize_;
    needAllLayout_ = false;
    // When not in own idle task but parent is doing predictive layout in idle,
    // inherit deadline and cache positions
    if (!layoutInfo_->deadline_.has_value() && posRef.value().deadline.has_value()) {
        layoutInfo_->deadline_ = posRef.value().deadline.value();
        layoutInfo_->cacheStartPos_ = cacheStartPos_;
        layoutInfo_->cacheEndPos_ = cacheEndPos_;
    }
}

void LazyColumnLayoutAlgorithm::UpdateAttribute(const RefPtr<LazyColumnLayoutProperty>& layoutProperty,
    const LayoutConstraintF& contentConstraint)
{
    auto mainPercentRefer = contentConstraint.percentReference.Height();
    auto spaceDim = layoutProperty->GetSpace().value_or(Dimension(0));
    space_ = ConvertToPx(spaceDim, contentConstraint.scaleProperty, mainPercentRefer).value_or(0);
    space_ = std::max(space_, 0.0f);
    horizontalAlign_ = layoutProperty->GetHorizontalAlign().value_or(HorizontalAlign::CENTER);
    isRtl_ = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
}

void LazyColumnLayoutAlgorithm::UpdateChildConstraint(const RefPtr<LazyColumnLayoutProperty>& layoutProperty,
    const OptionalSizeF& contentIdealSize)
{
    auto width = contentIdealSize.Width().value();
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = contentIdealSize;
    childLayoutConstraint.maxSize.SetHeight(Infinity<float>());
    childLayoutConstraint.maxSize.SetWidth(width);
    childLayoutConstraint.percentReference.SetWidth(width);
    childLayoutConstraint.viewPosRef.reset();
    childLayoutConstraint_ = childLayoutConstraint;

    // Header/footer measure against the full cross size with infinite main size, like content items.
    edgeLayoutConstraint_ = childLayoutConstraint;
}

int32_t LazyColumnLayoutAlgorithm::CalculateItemCount(LayoutWrapper* layoutWrapper) const
{
    CHECK_NULL_RETURN(layoutWrapper, 0);
    // rawCount is the host's total child count. Content item count = rawCount - header(0/1) - footer(0/1).
    // hasFooter additionally requires footerIndex_ != headerIndex_ so the (unlikely) case where one slot is held by
    // both edges is not subtracted twice.
    const auto rawCount = layoutWrapper->GetTotalChildCount();
    const bool hasHeader = headerIndex_ >= 0 && headerIndex_ < rawCount;
    const bool hasFooter = footerIndex_ >= 0 && footerIndex_ < rawCount && footerIndex_ != headerIndex_;
    return std::max(rawCount - (hasHeader ? 1 : 0) - (hasFooter ? 1 : 0), 0);
}

void LazyColumnLayoutAlgorithm::UpdateHeaderFooterIndexes(LayoutWrapper* layoutWrapper)
{
    if (!layoutWrapper) {
        headerIndex_ = -1;
        footerIndex_ = -1;
        return;
    }
    const auto rawCount = layoutWrapper->GetTotalChildCount();
    // Header / footer are normalized by SyncHeaderFooter(): header at raw index 0, footer at raw index last.
    const bool hasHeader = header_.Upgrade() != nullptr && rawCount > 0;
    const bool hasFooter = footer_.Upgrade() != nullptr && rawCount > (hasHeader ? 1 : 0);
    headerIndex_ = hasHeader ? 0 : -1;
    footerIndex_ = hasFooter ? rawCount - 1 : -1;
}

int32_t LazyColumnLayoutAlgorithm::GetRawIndexForItem(int32_t itemIndex) const
{
    return itemIndex + (headerIndex_ >= 0 ? 1 : 0);
}

StickyStyle LazyColumnLayoutAlgorithm::ResolveStickyStyle(LayoutWrapper* layoutWrapper) const
{
    CHECK_NULL_RETURN(layoutWrapper, StickyStyle::NONE);
    auto layoutProperty = AceType::DynamicCast<LazyColumnLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, StickyStyle::NONE);
    return layoutProperty->GetStickyStyle().value_or(StickyStyle::NONE);
}

bool LazyColumnLayoutAlgorithm::CheckNeedMeasure(const RefPtr<LayoutWrapper>& layoutWrapper) const
{
    if (layoutWrapper->CheckNeedForceMeasureAndLayout()) {
        return true;
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    auto constraint = geometryNode->GetParentLayoutConstraint();
    CHECK_NULL_RETURN(constraint, true);
    return constraint.value() != childLayoutConstraint_;
}

void LazyColumnLayoutAlgorithm::MeasureAllItems(LayoutWrapper* layoutWrapper)
{
    // h/f/s: shift the baseline so the first content item starts after the header.
    float totalSize = layoutInfo_->headerMainSize_;
    layoutInfo_->posMap_.clear();
    layoutInfo_->space_ = space_;
    int32_t curIndex = 0;
    while (curIndex < totalItemCount_) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(curIndex));
        if (!wrapper) {
            curIndex++;
            continue;
        }
        if (CheckNeedMeasure(wrapper)) {
            wrapper->Measure(childLayoutConstraint_);
        }
        auto geometryNode = wrapper->GetGeometryNode();
        if (!geometryNode) {
            curIndex++;
            continue;
        }
        float mainSize = geometryNode->GetMarginFrameSize().Height();
        layoutInfo_->posMap_[curIndex] = { totalSize, totalSize + mainSize };
        totalSize += mainSize;
        if (curIndex < totalItemCount_ - 1) {
            totalSize += space_;
        }
        curIndex++;
    }
    layoutInfo_->startIndex_ = 0;
    layoutInfo_->endIndex_ = totalItemCount_ - 1;
    layoutInfo_->visibleStartIndex_ = 0;
    layoutInfo_->visibleEndIndex_ = totalItemCount_ - 1;
    layoutInfo_->totalMainSize_ = totalSize;
    layoutInfo_->totalItemCount_ = totalItemCount_;
    totalMainSize_ = totalSize;
}

void LazyColumnLayoutAlgorithm::GetStartIndexInfo(int32_t& index, float& pos)
{
    // h/f/s: the body baseline is headerMainSize_, and bodyEnd = totalMainSize_ - footerMainSize_.
    const auto headerSize = layoutInfo_->headerMainSize_;
    const auto footerSize = layoutInfo_->footerMainSize_;
    const auto bodyEnd = totalMainSize_ - footerSize;
    if (GreatNotEqual(startPos_, bodyEnd)) {
        index = layoutInfo_->totalItemCount_;
        pos = bodyEnd;
        return;
    } else if (LessNotEqual(endPos_, headerSize)) {
        pos = headerSize;
        index = -1;
        return;
    } else if (LessOrEqual(startPos_, headerSize) || layoutInfo_->endIndex_ < 0) {
        pos = headerSize;
        index = 0;
        return;
    }
    auto it = layoutInfo_->posMap_.find(layoutInfo_->startIndex_);
    if (it == layoutInfo_->posMap_.end()) {
        pos = headerSize;
        index = 0;
        return;
    }
    auto nextIt = it;
    ++nextIt;
    while (nextIt != layoutInfo_->posMap_.end() && LessNotEqual(it->second.endPos, startPos_)) {
        it = nextIt;
        ++nextIt;
    }
    if (LessOrEqual(it->second.startPos - space_, startPos_)) {
        index = it->first;
        pos = it->second.startPos;
        return;
    }
    std::reverse_iterator<std::map<int32_t, ColumnItemMainPos>::iterator> rit(it);
    while (rit != layoutInfo_->posMap_.rend() && GreatNotEqual(rit->second.startPos - space_, startPos_)) {
        ++rit;
    }
    --rit;
    pos = rit->second.startPos;
    index = rit->first;
}

void LazyColumnLayoutAlgorithm::GetEndIndexInfo(int32_t& index, float& pos)
{
    // h/f/s: the body baseline is headerMainSize_, and bodyEnd = totalMainSize_ - footerMainSize_.
    const auto headerSize = layoutInfo_->headerMainSize_;
    const auto footerSize = layoutInfo_->footerMainSize_;
    const auto bodyEnd = totalMainSize_ - footerSize;
    if (LessNotEqual(endPos_, headerSize)) {
        index = -1;
        pos = headerSize;
        return;
    } else if (GreatNotEqual(startPos_, bodyEnd)) {
        index = totalItemCount_;
        pos = bodyEnd;
        return;
    } else if (GreatOrEqual(endPos_, bodyEnd) ||
               layoutInfo_->endIndex_ >= layoutInfo_->totalItemCount_) {
        pos = bodyEnd;
        index = totalItemCount_ - 1;
        return;
    }
    auto it = layoutInfo_->posMap_.find(layoutInfo_->endIndex_);
    if (it == layoutInfo_->posMap_.end()) {
        pos = bodyEnd;
        index = layoutInfo_->totalItemCount_ - 1;
        return;
    }
    std::reverse_iterator<std::map<int32_t, ColumnItemMainPos>::iterator> rit(++it);
    auto nextIt = rit;
    ++nextIt;
    while (nextIt != layoutInfo_->posMap_.rend() && GreatNotEqual(rit->second.startPos, endPos_)) {
        rit = nextIt;
        ++nextIt;
    }
    if (GreatOrEqual(rit->second.endPos + space_, endPos_)) {
        index = rit->first;
        pos = rit->second.endPos;
        return;
    }
    while (it != layoutInfo_->posMap_.end() && LessNotEqual(it->second.endPos + space_, endPos_)) {
        ++it;
    }
    --it;
    index = it->first;
    pos = it->second.endPos;
}

bool LazyColumnLayoutAlgorithm::NeedLazyLayout(const RefPtr<LayoutWrapper>& childWrapper)
{
    CHECK_NULL_RETURN(childWrapper, false);
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(childLayoutProperty, false);
    return childLayoutProperty->GetNeedLazyLayout();
}

LayoutConstraintF LazyColumnLayoutAlgorithm::GetLazyLayoutConstraint(float referencePos, bool forwardLayout)
{
    ViewPosReference ref {
        .viewPosStart = startPos_,
        .viewPosEnd = endPos_,
        .referencePos = referencePos,
        .referenceEdge = forwardLayout ? ReferenceEdge::START : ReferenceEdge::END,
        .axis = Axis::VERTICAL,
        .deadline = layoutInfo_->deadline_,
    };
    auto constraint = childLayoutConstraint_;
    constraint.viewPosRef = ref;
    return constraint;
}

AdjustOffset LazyColumnLayoutAlgorithm::GetAdjustOffset(const RefPtr<LayoutWrapper>& item)
{
    AdjustOffset offset {};
    RefPtr<UINode> child = AceType::DynamicCast<FrameNode>(item);
    do {
        CHECK_NULL_RETURN(child, offset);
        auto frameNode = AceType::DynamicCast<FrameNode>(child);
        if (!frameNode) {
            child = child->GetFirstChild();
            continue;
        }
        if (!frameNode->GetLayoutProperty()->GetNeedLazyLayout()) {
            return offset;
        }
        auto pattern = frameNode->GetPattern<LazyLayoutPattern>();
        if (pattern) {
            return pattern->GetAndResetAdjustOffset();
        }
        child = child->GetFirstChild();
    } while (child);
    return offset;
}

void LazyColumnLayoutAlgorithm::ApplyLazyNodeAdjustOffset(
    const RefPtr<LayoutWrapper>& wrapper, float& referencePos, bool forward)
{
    auto adjustOffset = GetAdjustOffset(wrapper);
    if (NearEqual(adjustOffset.start, 0.0f) && NearEqual(adjustOffset.end, 0.0f)) {
        return;
    }

    if (forward) {
        referencePos -= adjustOffset.start;
    } else {
        referencePos += adjustOffset.end;
    }
}

bool LazyColumnLayoutAlgorithm::MeasureItem(
    LayoutWrapper* layoutWrapper, int32_t curIndex, float currentPos, bool forward, float& mainSize)
{
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(curIndex));
    if (!wrapper) {
        return false;
    }
    if (NeedLazyLayout(wrapper)) {
        wrapper->Measure(GetLazyLayoutConstraint(currentPos, forward));
        ApplyLazyNodeAdjustOffset(wrapper, currentPos, forward);
    } else if (CheckNeedMeasure(wrapper)) {
        wrapper->Measure(childLayoutConstraint_);
    }
    auto geometryNode = wrapper->GetGeometryNode();
    if (!geometryNode) {
        return false;
    }
    mainSize = geometryNode->GetMarginFrameSize().Height();
    return true;
}

void LazyColumnLayoutAlgorithm::MeasureForward(LayoutWrapper* layoutWrapper, int32_t startIndex, float startPos)
{
    float currentPos = startPos;
    int32_t curIndex = startIndex;
    auto estimateItemSize = layoutInfo_->GetEstimateItemSize();
    while (LessOrEqual(currentPos, endPos_) && curIndex < totalItemCount_) {
        auto mainSize = 0.0f;
        auto iter = layoutInfo_->posMap_.find(curIndex);
        if (iter != layoutInfo_->posMap_.end()) {
            mainSize = iter->second.endPos - iter->second.startPos;
        }
        if (!Positive(mainSize)) {
            // Use estimated size for items far outside viewport to avoid jank during large scroll jumps
            mainSize = estimateItemSize;
        }
        bool skipMeasure = Positive(mainSize) && LessNotEqual(currentPos + mainSize, cacheStartPos_);
        if (!skipMeasure && !MeasureItem(layoutWrapper, curIndex, currentPos, true, mainSize)) {
            curIndex++;
            continue;
        }
        layoutInfo_->SetPosMap(curIndex, { currentPos, currentPos + mainSize });
        currentPos += mainSize;
        layoutInfo_->endIndex_ = curIndex;
        if (curIndex < totalItemCount_ - 1) {
            currentPos += space_;
        }
        curIndex++;
    }
}

void LazyColumnLayoutAlgorithm::MeasureBackward(LayoutWrapper* layoutWrapper, int32_t endIndex, float endPos)
{
    float currentPos = endPos;
    int32_t curIndex = std::min(endIndex, totalItemCount_ - 1);
    auto estimateItemSize = layoutInfo_->GetEstimateItemSize();
    while (curIndex >= 0 && GreatOrEqual(currentPos, startPos_)) {
        auto mainSize = 0.0f;
        auto iter = layoutInfo_->posMap_.find(curIndex);
        if (iter != layoutInfo_->posMap_.end()) {
            mainSize = iter->second.endPos - iter->second.startPos;
        }
        if (!Positive(mainSize)) {
            // Use estimated size for items far outside viewport to avoid jank during large scroll jumps
            mainSize = estimateItemSize;
        }
        bool skipMeasure = Positive(mainSize) && GreatNotEqual(currentPos - mainSize, cacheEndPos_);
        if (!skipMeasure && !MeasureItem(layoutWrapper, curIndex, currentPos, false, mainSize)) {
            curIndex--;
            continue;
        }
        layoutInfo_->SetPosMap(curIndex, { currentPos - mainSize, currentPos });
        currentPos -= mainSize;
        layoutInfo_->startIndex_ = curIndex;
        if (curIndex > 0) {
            currentPos -= space_;
        }
        curIndex--;
    }
}

void LazyColumnLayoutAlgorithm::CheckRecycle()
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
    std::reverse_iterator<std::map<int32_t, ColumnItemMainPos>::iterator> rit(++it);
    while (rit != layoutInfo_->posMap_.rend()) {
        if (GreatNotEqual(rit->second.startPos, endPos_)) {
            layoutInfo_->endIndex_ = rit->first - 1;
            ++rit;
        } else {
            break;
        }
    }
}

void LazyColumnLayoutAlgorithm::CalculateVisibleStartIndex()
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

void LazyColumnLayoutAlgorithm::CalculateVisibleEndIndex()
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
    std::reverse_iterator<std::map<int32_t, ColumnItemMainPos>::iterator> riter(++iter);
    while (riter != layoutInfo_->posMap_.rend()) {
        if (GreatNotEqual(riter->second.startPos, visibleEndPos)) {
            layoutInfo_->visibleEndIndex_ = riter->first - 1;
            ++riter;
        } else {
            break;
        }
    }
}

void LazyColumnLayoutAlgorithm::CheckCacheRecycle()
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
    it = layoutInfo_->posMap_.find(layoutInfo_->cachedEndIndex_);
    if (it == layoutInfo_->posMap_.end()) {
        return;
    }
    std::reverse_iterator<std::map<int32_t, ColumnItemMainPos>::iterator> rit(++it);
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
}

void LazyColumnLayoutAlgorithm::MeasureItemsLazy(LayoutWrapper* layoutWrapper)
{
    if (forwardLayout_) {
        int32_t startIndex = 0;
        // h/f/s: start the first content row right after the header.
        float startPos = layoutInfo_->headerMainSize_;
        GetStartIndexInfo(startIndex, startPos);
        layoutInfo_->SetTotalItemCount(totalItemCount_);
        layoutInfo_->SetSpace(space_);
        layoutInfo_->startIndex_ = startIndex;
        layoutInfo_->endIndex_ = startIndex;
        if (startIndex >= 0) {
            MeasureForward(layoutWrapper, startIndex, startPos);
            MeasureBackward(layoutWrapper, startIndex - 1, startPos - space_);
        }
    } else {
        int32_t endIndex = layoutInfo_->endIndex_;
        // h/f/s: body ends at totalMainSize_ - footerMainSize_; backwards walks the body only.
        float endPos = totalMainSize_ - layoutInfo_->footerMainSize_;
        GetEndIndexInfo(endIndex, endPos);
        layoutInfo_->SetTotalItemCount(totalItemCount_);
        layoutInfo_->SetSpace(space_);
        layoutInfo_->endIndex_ = endIndex;
        layoutInfo_->startIndex_ = endIndex;
        if (endIndex < totalItemCount_) {
            MeasureBackward(layoutWrapper, endIndex, endPos);
            MeasureForward(layoutWrapper, endIndex + 1, endPos + space_);
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

void LazyColumnLayoutAlgorithm::SetFrameSize(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize)
{
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto property = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    const auto& layoutConstraint = property->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    OptionalSizeF frameSize;
    frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
    if (frameSize.IsValid()) {
        geometryNode->SetFrameSize(frameSize.ConvertToSizeT());
        return;
    }

    auto layoutPolicy = property->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value()) {
        auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto layoutPolicySize = ConstrainIdealSizeByLayoutPolicy(
            layoutConstraint.value(), widthLayoutPolicy, heightLayoutPolicy, Axis::VERTICAL);
        contentIdealSize.UpdateIllegalSizeWithCheck(layoutPolicySize.ConvertToSizeT());
        auto isMainWrap = heightLayoutPolicy == LayoutCalPolicy::WRAP_CONTENT;
        auto isMainFix = heightLayoutPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE ||
                         heightLayoutPolicy == LayoutCalPolicy::NO_MATCH;
        if (isMainWrap) {
            contentIdealSize.SetHeight(totalMainSize_);
            contentIdealSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
        } else if (isMainFix) {
            contentIdealSize.SetHeight(totalMainSize_);
        }
    } else {
        contentIdealSize.SetHeight(totalMainSize_);
    }

    const auto& padding = property->CreatePaddingAndBorder();
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
    geometryNode->SetFrameSize(frameSize.ConvertToSizeT());
}

void LazyColumnLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<LazyColumnLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto size = geometryNode->GetFrameSize();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto crossSize = size.Width();
    auto paddingOffset = OffsetF(left, top);
    
    if (layoutInfo_->deadline_) {
        layoutInfo_->deadline_.reset();
        return;
    }
    auto stickyStyle = ResolveStickyStyle(layoutWrapper);
    const HeaderFooterStickyMetrics stickyMetrics { startPos_, endPos_, totalMainSize_,
        layoutInfo_->headerMainSize_, layoutInfo_->footerMainSize_ };
    const auto stickyHeaderPos = HeaderFooterUtils::CalcStickyHeaderPos(stickyMetrics);
    const auto stickyFooterPos = HeaderFooterUtils::CalcStickyFooterPos(stickyMetrics);

    // Layout order follows section semantics: header -> content items -> footer.
    LayoutHeader(layoutWrapper, crossSize, paddingOffset, stickyStyle, stickyHeaderPos);
    LayoutItems(layoutWrapper, crossSize, paddingOffset);
    LayoutCachedItems(layoutWrapper, crossSize, paddingOffset);
    LayoutFooter(layoutWrapper, crossSize, paddingOffset, stickyStyle, stickyFooterPos);
}

float LazyColumnLayoutAlgorithm::CalculateCrossOffset(float crossSize, float childCrossSize) const
{
    float delta = crossSize - childCrossSize;
    if (LessOrEqual(delta, 0)) {
        return 0.0f;
    }
    switch (horizontalAlign_) {
        case HorizontalAlign::START:
            return 0.0f;
        case HorizontalAlign::CENTER:
            return delta / 2.0f;
        case HorizontalAlign::END:
            return delta;
        default:
            return 0.0f;
    }
}

void LazyColumnLayoutAlgorithm::SetItemOffset(const RefPtr<LayoutWrapper>& wrapper, const ColumnItemMainPos& pos,
    float crossSize, const OffsetF& paddingOffset)
{
    auto geometryNode = wrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto offset = paddingOffset;
    auto childSize = geometryNode->GetMarginFrameSize();
    float crossOffset = CalculateCrossOffset(crossSize, childSize.Width());
    if (isRtl_) {
        offset = offset + OffsetF(crossSize - childSize.Width() - crossOffset, pos.startPos);
    } else {
        offset = offset + OffsetF(crossOffset, pos.startPos);
    }
    geometryNode->SetMarginFrameOffset(offset);
}

void LazyColumnLayoutAlgorithm::PredictLayoutForward(
    LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset)
{
    int32_t currIndex = layoutInfo_->layoutedEndIndex_;
    // Allow forward prediction when not yet laid out (currIndex<0) with forward layout,
    // or when already laid out (currIndex>=0) with item in posMap
    if ((currIndex < 0 && !forwardLayout_) ||
        (currIndex >= 0 && layoutInfo_->posMap_.find(currIndex) == layoutInfo_->posMap_.end())) {
        return;
    }
    float currPos = layoutInfo_->layoutedEnd_;
    auto deadline = layoutInfo_->deadline_.value();
    while (currIndex < totalItemCount_ - 1 && LessNotEqual(currPos, layoutInfo_->cacheEndPos_)) {
        if (GetSysTimestamp() > deadline) {
            break;
        }
        int32_t index = currIndex + 1;
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(index));
        if (!wrapper || !wrapper->GetHostNode() || !wrapper->GetHostNode()->RenderCustomChild(deadline)) {
            break;
        }
        auto geometryNode = wrapper->GetGeometryNode();
        if (!geometryNode) {
            break;
        }
        if (NeedLazyLayout(wrapper)) {
            wrapper->Measure(GetLazyLayoutConstraint(currPos, true));
        } else {
            wrapper->Measure(childLayoutConstraint_);
        }
        auto size = geometryNode->GetMarginFrameSize().Height();
        ColumnItemMainPos pos { currPos, currPos + size };
        currPos = pos.endPos + space_;
        layoutInfo_->SetCachedPosMap(index, pos);
        SetItemOffset(wrapper, pos, crossSize, paddingOffset);
        wrapper->Layout();
        currIndex = index;
    }
    layoutedEndIndex_ = currIndex;
    cachedEndIndex_ = std::max(layoutInfo_->cachedEndIndex_, currIndex);
    layoutedEnd_ = currPos;
}

void LazyColumnLayoutAlgorithm::PredictLayoutBackward(
    LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset)
{
    int32_t currIndex = layoutInfo_->layoutedStartIndex_;
    // Allow backward prediction when not yet laid out (currIndex<0) with backward layout,
    // or when already laid out (currIndex>=0) with item in posMap
    if ((currIndex < 0 && forwardLayout_) ||
        (currIndex >= 0 && layoutInfo_->posMap_.find(currIndex) == layoutInfo_->posMap_.end())) {
        return;
    }
    if (currIndex < 0 && !forwardLayout_) {
        currIndex = totalItemCount_;
    }
    float currPos = layoutInfo_->layoutedStart_;
    auto deadline = layoutInfo_->deadline_.value();
    while (currIndex > 0 && (GreatNotEqual(currPos, layoutInfo_->cacheStartPos_))) {
        if (GetSysTimestamp() > deadline) {
            break;
        }
        int32_t index = currIndex - 1;
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(index));
        if (!wrapper || !wrapper->GetHostNode() || !wrapper->GetHostNode()->RenderCustomChild(deadline)) {
            break;
        }
        auto geometryNode = wrapper->GetGeometryNode();
        if (!geometryNode) {
            break;
        }
        if (NeedLazyLayout(wrapper)) {
            wrapper->Measure(GetLazyLayoutConstraint(currPos, false));
        } else {
            wrapper->Measure(childLayoutConstraint_);
        }
        float size = geometryNode->GetMarginFrameSize().Height();
        ColumnItemMainPos pos { currPos - size, currPos };
        currPos = pos.startPos - space_;
        layoutInfo_->SetCachedPosMap(index, pos);
        SetItemOffset(wrapper, pos, crossSize, paddingOffset);
        wrapper->Layout();
        currIndex = index;
    }
    layoutedStartIndex_ = currIndex;
    cachedStartIndex_ = layoutInfo_->cachedStartIndex_ >= 0
        ? std::min(layoutInfo_->cachedStartIndex_, currIndex)
        : currIndex;
    layoutedStart_ = currPos;
}

void LazyColumnLayoutAlgorithm::FixIndexRange(int32_t& startIndex, int32_t& endIndex)
{
    if (startIndex < 0 && endIndex >= 0 && endIndex < totalItemCount_) {
        startIndex = 0;
    }
    if ((endIndex < 0 || endIndex >= totalItemCount_) && startIndex >= 0 && startIndex < totalItemCount_) {
        endIndex = totalItemCount_ - 1;
    }
}

void LazyColumnLayoutAlgorithm::SyncPredictLayoutInfo(LayoutWrapper* layoutWrapper)
{
    // Recycle items outside visible and cache range
    CheckRecycle();
    CheckCacheRecycle();
    CalculateVisibleStartIndex();
    CalculateVisibleEndIndex();
    FixIndexRange(cachedStartIndex_, cachedEndIndex_);
    FixIndexRange(layoutedStartIndex_, layoutedEndIndex_);
    // Update active child range if cache boundaries changed
    if ((layoutInfo_->cachedStartIndex_ != cachedStartIndex_) ||
        (layoutInfo_->cachedEndIndex_ != cachedEndIndex_)) {
        // h/f/s: same translation as LayoutCachedItems; keep header / footer active alongside the item cache.
        if (headerIndex_ < 0 && footerIndex_ < 0) {
            layoutWrapper->SetActiveChildRange(cachedStartIndex_, cachedEndIndex_);
        } else if (cachedStartIndex_ < 0 || cachedEndIndex_ < cachedStartIndex_) {
            SetHeaderFooterActive(layoutWrapper);
        } else {
            ActiveChildSets activeChildSets;
            const auto rawStart = GetRawIndexForItem(cachedStartIndex_);
            const auto rawEnd = GetRawIndexForItem(cachedEndIndex_);
            for (auto i = rawStart; i <= rawEnd; ++i) {
                activeChildSets.activeItems.insert(i);
            }
            if (headerIndex_ >= 0) {
                activeChildSets.activeItems.insert(headerIndex_);
            }
            if (footerIndex_ >= 0) {
                activeChildSets.activeItems.insert(footerIndex_);
            }
            layoutWrapper->SetActiveChildRange(std::optional<ActiveChildSets>(activeChildSets), std::nullopt);
        }
    }
    // Sync prediction results back to layoutInfo
    layoutInfo_->layoutedStartIndex_ = layoutedStartIndex_;
    layoutInfo_->cachedStartIndex_ = cachedStartIndex_;
    layoutInfo_->layoutedStart_ = layoutedStart_;

    layoutInfo_->layoutedEndIndex_ = layoutedEndIndex_;
    layoutInfo_->cachedEndIndex_ = cachedEndIndex_;
    layoutInfo_->layoutedEnd_ = layoutedEnd_;

    // Skip posMap update if only self measure changed,
    // as child positions remain valid
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPropertyChangeFlag() == PROPERTY_UPDATE_MEASURE_SELF) {
        return;
    }
    layoutInfo_->UpdatePosMap();
    totalMainSize_ = layoutInfo_->totalMainSize_;
}

void LazyColumnLayoutAlgorithm::SyncGeometry(const RefPtr<LayoutWrapper>& wrapper)
{
    CHECK_NULL_VOID(wrapper);
    auto host = wrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    host->ForceSyncGeometryNode();
    host->ResetLayoutAlgorithm();
}

void LazyColumnLayoutAlgorithm::LayoutItems(
    LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset)
{
    auto iter = layoutInfo_->posMap_.find(layoutInfo_->startIndex_);
    for (; iter != layoutInfo_->posMap_.end() && iter->first <= layoutInfo_->endIndex_; iter++) {
        // h/f/s: posMap_ keys are item indices; translate to raw indices for child fetches.
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetRawIndexForItem(iter->first));
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

void LazyColumnLayoutAlgorithm::LayoutCachedItemsForward(
    LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset)
{
    auto iter = layoutInfo_->posMap_.begin();
    if (layoutInfo_->endIndex_ >= totalItemCount_ - 1) {
        // h/f/s: footer is laid out separately, so cache window ends at body end (= totalMainSize_ - footer).
        layoutedEnd_ = totalMainSize_ - layoutInfo_->footerMainSize_;
        cachedEndIndex_ = layoutInfo_->endIndex_;
    } else if (layoutInfo_->endIndex_ < 0) {
        cachedEndIndex_ = -1;
        // h/f/s: empty body still sits below the header.
        layoutedEnd_ = layoutInfo_->headerMainSize_;
    } else {
        cachedEndIndex_ = layoutInfo_->endIndex_;
        iter = layoutInfo_->posMap_.find(layoutInfo_->endIndex_);
        if (iter == layoutInfo_->posMap_.end()) {
            TAG_LOGE(AceLogTag::ACE_LAZY_COLUMN, "find end index error:%{public}d", layoutInfo_->endIndex_);
            return;
        }
        layoutedEnd_ = iter->second.endPos + space_;
        iter++;
    }
    layoutedEndIndex_ = cachedEndIndex_;
    bool hadDirty = false;
    while (iter != layoutInfo_->posMap_.end() && LessNotEqual(iter->second.startPos, cacheEndPos_)) {
        if (cachedEndIndex_ + 1 != iter->first) {
            break;
        }
        // h/f/s: posMap_ keys are item indices; translate to raw indices for child fetches.
        auto wrapper = layoutWrapper->GetChildByIndex(GetRawIndexForItem(iter->first), true);
        if (!wrapper) {
            break;
        }
        SetItemOffset(wrapper, iter->second, crossSize, paddingOffset);
        SyncGeometry(wrapper);
        if (hadDirty || CheckNeedMeasure(wrapper)) {
            hadDirty = true;
        } else {
            layoutedEnd_ = iter->second.endPos + space_;
            layoutedEndIndex_ = iter->first;
        }
        cachedEndIndex_ = iter->first;
        iter++;
    }
}

void LazyColumnLayoutAlgorithm::LayoutCachedItemsBackward(
    LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset)
{
    auto rIter = layoutInfo_->posMap_.rbegin();
    if (layoutInfo_->startIndex_ == 0) {
        // h/f/s: body starts right below the header.
        layoutedStart_ = layoutInfo_->headerMainSize_;
        cachedStartIndex_ = 0;
    } else if (layoutInfo_->startIndex_ >= totalItemCount_) {
        // h/f/s: when fully scrolled past the body, anchor the cache marker to body end (excludes footer).
        layoutedStart_ = totalMainSize_ - layoutInfo_->footerMainSize_;
        cachedStartIndex_ = totalItemCount_;
    } else {
        cachedStartIndex_ = layoutInfo_->startIndex_;
        auto iter = layoutInfo_->posMap_.find(layoutInfo_->startIndex_);
        if (iter == layoutInfo_->posMap_.end()) {
            TAG_LOGE(AceLogTag::ACE_LAZY_COLUMN, "find start index error:%{public}d", layoutInfo_->endIndex_);
            return;
        }
        layoutedStart_ = iter->second.startPos - space_;
        std::reverse_iterator<std::map<int32_t, ColumnItemMainPos>::iterator> rit(iter);
        rIter = rit;
    }
    layoutedStartIndex_ = cachedStartIndex_;
    bool hadDirty = false;
    while (rIter != layoutInfo_->posMap_.rend() && GreatNotEqual(rIter->second.endPos, cacheStartPos_)) {
        if (cachedStartIndex_ - 1 != rIter->first) {
            break;
        }
        // h/f/s: posMap_ keys are item indices; translate to raw indices for child fetches.
        auto wrapper = layoutWrapper->GetChildByIndex(GetRawIndexForItem(rIter->first), true);
        if (!wrapper) {
            break;
        }
        SetItemOffset(wrapper, rIter->second, crossSize, paddingOffset);
        SyncGeometry(wrapper);
        if (hadDirty || CheckNeedMeasure(wrapper)) {
            hadDirty = true;
        } else {
            layoutedStart_ = rIter->second.startPos - space_;
            layoutedStartIndex_ = rIter->first;
        }
        cachedStartIndex_ = rIter->first;
        rIter++;
    }
}

void LazyColumnLayoutAlgorithm::LayoutCachedItems(
    LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset)
{
    LayoutCachedItemsForward(layoutWrapper, crossSize, paddingOffset);
    LayoutCachedItemsBackward(layoutWrapper, crossSize, paddingOffset);
    FixIndexRange(cachedStartIndex_, cachedEndIndex_);
    // h/f/s: translate item indices to raw indices for SetActiveChildRange. When header / footer are mounted,
    // use ActiveChildSets so the edges stay active alongside the item cache window.
    if (headerIndex_ < 0 && footerIndex_ < 0) {
        layoutWrapper->SetActiveChildRange(cachedStartIndex_, cachedEndIndex_, 0, 0);
    } else if (cachedStartIndex_ < 0 || cachedEndIndex_ < cachedStartIndex_) {
        SetHeaderFooterActive(layoutWrapper);
    } else {
        ActiveChildSets activeChildSets;
        const auto rawStart = GetRawIndexForItem(cachedStartIndex_);
        const auto rawEnd = GetRawIndexForItem(cachedEndIndex_);
        for (auto i = rawStart; i <= rawEnd; ++i) {
            activeChildSets.activeItems.insert(i);
        }
        if (headerIndex_ >= 0) {
            activeChildSets.activeItems.insert(headerIndex_);
        }
        if (footerIndex_ >= 0) {
            activeChildSets.activeItems.insert(footerIndex_);
        }
        layoutWrapper->SetActiveChildRange(std::optional<ActiveChildSets>(activeChildSets), std::nullopt);
    }
    layoutInfo_->layoutedStart_ = layoutedStart_;
    layoutInfo_->layoutedEnd_ = layoutedEnd_;
    layoutInfo_->layoutedStartIndex_ = layoutedStartIndex_;
    layoutInfo_->layoutedEndIndex_ = layoutedEndIndex_;
    layoutInfo_->cacheStartPos_ = cacheStartPos_;
    layoutInfo_->cacheEndPos_ = cacheEndPos_;
    layoutInfo_->cachedStartIndex_ = cachedStartIndex_;
    layoutInfo_->cachedEndIndex_ = cachedEndIndex_;
}

void LazyColumnLayoutAlgorithm::SetHeaderFooterActive(LayoutWrapper* layoutWrapper) const
{
    ActiveChildSets activeChildSets;
    if (headerIndex_ >= 0) {
        activeChildSets.activeItems.insert(headerIndex_);
    }
    if (footerIndex_ >= 0) {
        activeChildSets.activeItems.insert(footerIndex_);
    }
    layoutWrapper->SetActiveChildRange(std::optional<ActiveChildSets>(activeChildSets), std::nullopt);
}

void LazyColumnLayoutAlgorithm::LayoutHeaderFooter(
    LayoutWrapper* layoutWrapper, int32_t rawIndex, const OffsetF& offset, float crossSize, bool isSticky) const
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
    if (isRtl_) {
        finalOffset.SetX(offset.GetX() + crossSize - geometryNode->GetMarginFrameSize().Width());
    }
    geometryNode->SetMarginFrameOffset(finalOffset);
    // Header / footer must always be in the render tree on every layout pass. GetChildByIndex() above does not
    // activate the child, so a stale inactive state from a prior frame would otherwise suppress
    // SyncGeometryProperties() and freeze the edge at its previous rendered position.
    child->SetActive(true);
    child->Layout();
}

void LazyColumnLayoutAlgorithm::LayoutHeader(LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset, StickyStyle stickyStyle, float stickyHeaderPos) const
{
    auto isSticky = stickyStyle == StickyStyle::HEADER || stickyStyle == StickyStyle::BOTH;
    auto offset = paddingOffset + (isSticky ? OffsetF(0.0f, stickyHeaderPos) : OffsetF());
    LayoutHeaderFooter(layoutWrapper, headerIndex_, offset, crossSize, isSticky);
}

void LazyColumnLayoutAlgorithm::LayoutFooter(LayoutWrapper* layoutWrapper, float crossSize,
    const OffsetF& paddingOffset, StickyStyle stickyStyle, float stickyFooterPos) const
{
    auto isSticky = stickyStyle == StickyStyle::FOOTER || stickyStyle == StickyStyle::BOTH;
    auto footerPos = isSticky ? stickyFooterPos : totalMainSize_ - layoutInfo_->footerMainSize_;
    auto offset = OffsetF(paddingOffset.GetX(), paddingOffset.GetY() + footerPos);
    LayoutHeaderFooter(layoutWrapper, footerIndex_, offset, crossSize, isSticky);
}
} // namespace OHOS::Ace::NG
