/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/list/arc_list_layout_algorithm.h"

#include <algorithm>
#include <unordered_set>
#include <utility>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/layout_param.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/arc_list_item_pattern.h"
#include "core/components_ng/pattern/list/arc_list_pattern.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/list/list_properties.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float ARC_LIST_ITER_SCALE = 0.92f;
constexpr float ARC_LIST_ONE_PERCENT = 0.01f;
} // namespace

ArcListLayoutAlgorithm::CenterPos2ScaleMap ArcListLayoutAlgorithm::centerPos2ScaleMap_ = { { 141, 78 }, { 118, 88 },
    { 94, 97 }, { 70.6, 103 }, { 47, 107 }, { 23.5, 107.5 }, { 0, 108 }, { -23, 107.5 }, { -45, 107 }, { -66, 103 },
    { -89, 98 }, { -112, 90 }, { -132, 82 } };

float ArcListLayoutAlgorithm::GetNearScale(const float pos)
{
    if (centerPos2ScaleMap_.empty()) {
        return 0.0;
    }

    if (LessOrEqual(pos, centerPos2ScaleMap_.begin()->first)) {
        return centerPos2ScaleMap_.begin()->second * ARC_LIST_ONE_PERCENT;
    }
    if (GreatOrEqual(pos, (--centerPos2ScaleMap_.end())->first)) {
        return (--centerPos2ScaleMap_.end())->second * ARC_LIST_ONE_PERCENT;
    }

    for (auto it = centerPos2ScaleMap_.begin(); it != centerPos2ScaleMap_.end(); ++it) {
        if (GreatNotEqual(it->first, pos)) {
            float t = std::abs(pos - it->first) / std::abs(it->first - std::prev(it, 1)->first);
            return GetLerpValue(it->second, std::prev(it, 1)->second, t) * ARC_LIST_ONE_PERCENT;
        }
    }

    return 0.0;
}

void ArcListLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);

    axis_ = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    // Pre-recycle
    ScrollableUtils::RecycleItemsOutOfBoundary(axis_, -currentDelta_, GetStartIndex(), GetEndIndex(), layoutWrapper);

    const auto& layoutConstraint = listLayoutProperty->GetLayoutConstraint().value();

    // calculate idealSize and set FrameSize
    contentStartOffset_ = 0.0;
    contentEndOffset_ = 0.0;

    // calculate main size.
    auto contentConstraint = listLayoutProperty->GetContentLayoutConstraint().value();

    float expandHeight = ScrollableUtils::CheckHeightExpansion(listLayoutProperty, axis_);
    contentEndOffset_ += expandHeight;
    // expand contentSize
    contentConstraint.MinusPadding(std::nullopt, std::nullopt, std::nullopt, -expandHeight);
    auto&& safeAreaOpts = listLayoutProperty->GetSafeAreaExpandOpts();
    expandSafeArea_ = safeAreaOpts && safeAreaOpts->Expansive();

    auto contentIdealSize = CreateIdealSize(
        contentConstraint, axis_, listLayoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS));

    const auto& padding = listLayoutProperty->CreatePaddingAndBorder();
    paddingBeforeContent_ = axis_ == Axis::HORIZONTAL ? padding.left.value_or(0) : padding.top.value_or(0);
    paddingAfterContent_ = axis_ == Axis::HORIZONTAL ? padding.right.value_or(0) : padding.bottom.value_or(0);
    contentMainSize_ = 0.0f;
    totalItemCount_ = layoutWrapper->GetTotalChildCount() - itemStartIndex_;
    if (childrenSize_) {
        childrenSize_->ResizeChildrenSize(totalItemCount_);
    }
    if (!GetMainAxisSize(contentIdealSize, axis_)) {
        if (totalItemCount_ == 0) {
            contentMainSize_ = 0.0f;
        } else {
            // use parent max size first.
            auto parentMaxSize = contentConstraint.maxSize;
            contentMainSize_ = GetMainAxisSize(parentMaxSize, axis_);
            mainSizeIsDefined_ = false;
        }
    } else {
        contentMainSize_ = GetMainAxisSize(contentIdealSize.ConvertToSizeT(), axis_);
        mainSizeIsDefined_ = true;
    }
    contentStartOffset_ = 0;
    contentEndOffset_ = 0;

    MeasureHeader(layoutWrapper);

    if (totalItemCount_ > 0) {
        OnSurfaceChanged(layoutWrapper);

        childLayoutConstraint_ = listLayoutProperty->CreateChildConstraint();
        auto mainPercentRefer = GetMainAxisSize(childLayoutConstraint_.percentReference, axis_);
        auto space = listLayoutProperty->GetSpace().value_or(Dimension(0));
        spaceWidth_ = ConvertToPx(space, layoutConstraint.scaleProperty, mainPercentRefer).value_or(0);
        ReviseSpace(listLayoutProperty);
        CheckJumpToIndex();
        currentOffset_ = currentDelta_;
        startMainPos_ = currentOffset_;
        endMainPos_ = currentOffset_ + contentMainSize_;
        // calculate child layout constraint.
        UpdateListItemConstraint(axis_, contentIdealSize, childLayoutConstraint_);
        if (posMap_) {
            posMap_->UpdatePosMap(layoutWrapper, 0, spaceWidth_, childrenSize_);
        }
        MeasureList(layoutWrapper);
    } else {
        itemPosition_.clear();
        if (posMap_) {
            posMap_->ClearPosMap();
        }
    }

    SetActiveChildRange(layoutWrapper);

    auto crossSize = contentIdealSize.CrossSize(axis_);
    if (crossSize.has_value() && GreaterOrEqualToInfinity(crossSize.value())) {
        contentIdealSize.SetCrossSize(GetChildMaxCrossSize(layoutWrapper, axis_), axis_);
        crossMatchChild_ = true;
    }
    contentIdealSize.SetMainSize(contentMainSize_, axis_);
    AddPaddingToSize(padding, contentIdealSize);

    auto size = contentIdealSize.ConvertToSizeT();
    // Cancel frame size expansion, only expand content size here.
    // Frame expansion will be determined after Layout.
    size.MinusHeight(expandHeight);
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);

    // set list cache info.
    SetCacheCount(layoutWrapper, listLayoutProperty->GetCachedCountValue(1));
}

void ArcListLayoutAlgorithm::MeasureList(LayoutWrapper* layoutWrapper)
{
    int32_t startIndex = 0;
    int32_t endIndex = 0;
    int32_t midIndex = 0;
    float midItemMidPos = contentMainSize_ / 2.0f;
    float startPos = headerMainSize_;
    float endPos = 0.0f;
    float itemTotalSize = 0.0f;

    if (jumpIndex_) {
        if (!CheckJumpValid(layoutWrapper)) {
            jumpIndex_.reset();
        } else {
            if (jumpIndex_) {
                ClearAllItemPosition(layoutWrapper);
            }
        }
    }
    if (targetIndex_) {
        if (targetIndex_.value() == LAST_ITEM) {
            targetIndex_ = totalItemCount_ - 1;
        } else if ((targetIndex_.value() < 0) || (targetIndex_.value() >= totalItemCount_)) {
            targetIndex_.reset();
        }
        targetIndexStaged_ = targetIndex_;
    }
    if (!itemPosition_.empty()) {
        startPos = itemPosition_.begin()->second.startPos;
        endPos = itemPosition_.rbegin()->second.endPos;
        itemTotalSize = GetEndPosition() - GetStartPosition();
        startIndex = std::min(GetStartIndex(), totalItemCount_ - 1);
        endIndex = std::min(GetEndIndex(), totalItemCount_ - 1);
        if (GetStartIndex() > totalItemCount_ - 1 && !jumpIndex_.has_value()) {
            jumpIndex_ = totalItemCount_ - 1;
        }
        UpdateSnapCenterContentOffset(layoutWrapper);
        midIndex = GetMidIndex(layoutWrapper, true);
        midItemMidPos = (itemPosition_[midIndex].startPos + itemPosition_[midIndex].endPos) / 2.0f -
                        prevContentMainSize_ / 2.0f + contentMainSize_ / 2.0f;
        midIndex = std::min(midIndex, totalItemCount_ - 1);
        OffScreenLayoutDirection();

        itemPosition_.clear();
    }
    if (jumpIndex_) {
        HandleJumpCenter(layoutWrapper);
        needEstimateOffset_ = true;
    } else if (targetIndex_.has_value()) {
        if (LessOrEqual(startIndex, targetIndex_.value())) {
            LayoutForward(layoutWrapper, startIndex, startPos);
            if (GetStartIndex() > 0 && GreatNotEqual(GetStartPosition(), startMainPos_)) {
                LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
            }
        } else if (GreatNotEqual(startIndex, targetIndex_.value())) {
            LayoutBackward(layoutWrapper, endIndex, endPos);
            if (GetEndIndex() < (totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
                LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
            }
        }
    } else {
        bool overScrollTop = startIndex == 0 && GreatNotEqual(startPos, contentStartOffset_);
        float midItemHeight = 0.0f;
        midItemHeight =
            childrenSize_ ? GetChildHeight(layoutWrapper, midIndex) : MeasureAndGetChildHeight(layoutWrapper, midIndex);
        startIndex = midIndex;
        endIndex = midIndex;
        if (NearZero(currentOffset_) || (!overScrollFeature_ && NonNegative(currentOffset_)) ||
            (overScrollFeature_ && overScrollTop) ||
            LessOrEqual(itemTotalSize, contentMainSize_ - contentStartOffset_ - contentEndOffset_)) {
            startPos = midItemMidPos - midItemHeight / 2.0f;
            if (childrenSize_) {
                posMap_->OptimizeBeforeMeasure(startIndex, startPos, currentOffset_, contentMainSize_);
            }
            LayoutForward(layoutWrapper, startIndex, startPos);
            if (GetStartIndex() > 0 && GreatNotEqual(GetStartPosition(), startMainPos_)) {
                LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
            }
        } else {
            endPos = midItemMidPos + midItemHeight / 2.0f;
            if (childrenSize_) {
                posMap_->OptimizeBeforeMeasure(endIndex, endPos, currentOffset_, contentMainSize_);
            }
            LayoutBackward(layoutWrapper, endIndex, endPos);
            if (GetEndIndex() < (totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
                LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
            }
        }
    }
}

int32_t ArcListLayoutAlgorithm::LayoutALineForward(
    LayoutWrapper* layoutWrapper, int32_t& currentIndex, float startPos, float& endPos)
{
    if (currentIndex + 1 >= totalItemCount_) {
        return 0;
    }

    auto wrapper = GetListItem(layoutWrapper, currentIndex + 1);
    CHECK_NULL_RETURN(wrapper, 0);
    int32_t id = wrapper->GetHostNode()->GetId();
    ++currentIndex;
    ACE_SCOPED_TRACE("ArcListLayoutAlgorithm::MeasureListItem:%d, %f", currentIndex, startPos);

    auto layoutConstraint = childLayoutConstraint_;
    LayoutConstraintApplyScale(layoutConstraint, ARC_LIST_ITER_SCALE);
    wrapper->Measure(layoutConstraint);

    float mainLen = childrenSize_ ? childrenSize_->GetChildSize(currentIndex)
                                  : GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);

    endPos = startPos + mainLen;
    itemPosition_[currentIndex] = { id, startPos, endPos };

    OnItemPositionAddOrUpdate(layoutWrapper, currentIndex);
    return 1;
}

int32_t ArcListLayoutAlgorithm::LayoutALineBackward(
    LayoutWrapper* layoutWrapper, int32_t& currentIndex, float endPos, float& startPos)
{
    if (currentIndex - 1 < 0) {
        return 0;
    }

    auto wrapper = GetListItem(layoutWrapper, currentIndex - 1);
    CHECK_NULL_RETURN(wrapper, 0);
    int32_t id = wrapper->GetHostNode()->GetId();
    --currentIndex;
    ACE_SCOPED_TRACE("ArcListLayoutAlgorithm::MeasureListItem:%d, %f", currentIndex, endPos);

    auto layoutConstraint = childLayoutConstraint_;
    LayoutConstraintApplyScale(layoutConstraint, ARC_LIST_ITER_SCALE);
    wrapper->Measure(layoutConstraint);

    float mainLen = childrenSize_ ? childrenSize_->GetChildSize(currentIndex)
                                  : GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);

    startPos = endPos - mainLen;
    itemPosition_[currentIndex] = { id, startPos, endPos };

    OnItemPositionAddOrUpdate(layoutWrapper, currentIndex);
    return 1;
}

float ArcListLayoutAlgorithm::CalculateLaneCrossOffset(float crossSize, float childCrossSize)
{
    float delta = crossSize - childCrossSize;
    if (LessOrEqual(delta, 0)) {
        return 0.0f;
    }
    return delta / 2.0f;
}

void ArcListLayoutAlgorithm::FixPredictSnapOffset(const RefPtr<ListLayoutProperty>& listLayoutProperty)
{
    if (!predictSnapOffset_.has_value()) {
        return;
    }
    auto predictEndPos = totalOffset_ - predictSnapOffset_.value();
    int32_t endIndex = FindPredictSnapEndIndexInItemPositions(predictEndPos, V2::ScrollSnapAlign::CENTER);
    if (endIndex != -1) {
        predictEndPos = CalculatePredictSnapEndPositionByIndex(endIndex, predictEndPos);
        predictSnapOffset_ = totalOffset_ - predictEndPos + currentOffset_;
        predictSnapEndPos_.reset();
    } else {
        if (IsUniformHeightProbably()) {
            FixPredictSnapOffsetAlignCenter();
        } else {
            predictSnapEndPos_ = predictEndPos;
        }
    }

    return;
}

void ArcListLayoutAlgorithm::FixPredictSnapOffsetAlignCenter()
{
    if (itemPosition_.empty()) {
        return;
    }

    auto predictEndPos = totalOffset_ - predictSnapOffset_.value();
    auto itemHeight = itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos + spaceWidth_;
    float snapSize = LessOrEqual(itemHeight, ARC_LIST_ITEM_SNAP_SIZE + spaceWidth_)
                         ? itemHeight
                         : ARC_LIST_ITEM_SNAP_SIZE + spaceWidth_;
    if (LessNotEqual(predictEndPos, snapSize / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = snapSize / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f;
    } else if (GreatNotEqual(
        predictEndPos + contentMainSize_ / 2.0f, itemHeight * totalItemCount_ - snapSize / 2.0f)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = itemHeight * totalItemCount_ - snapSize / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f;
    } else {
        int32_t index;
        for (index = 0; index <= GetMaxListItemIndex(); index++) {
            if (std::abs(predictEndPos + contentMainSize_ / 2.0f - index * itemHeight - itemHeight / 2.0f) <
                itemHeight / 2.0f) {
                break;
            }
        }
        float snapLow = index * itemHeight + snapSize / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f;
        float snapHigh = (index + 1) * itemHeight - snapSize / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f;
        predictEndPos = LessNotEqual(predictEndPos, snapLow) ? snapLow : predictEndPos;
        predictEndPos = LessNotEqual(snapHigh, predictEndPos) ? snapHigh : predictEndPos;
        if (LessNotEqual(predictEndPos, snapSize / 2.0f - contentMainSize_ / 2.0f)) {
            predictEndPos = snapSize / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f;
        } else if (GreatNotEqual(
            predictEndPos + contentMainSize_ / 2.0f, itemHeight * totalItemCount_ - snapSize / 2.0f)) {
            predictEndPos =
                itemHeight * totalItemCount_ - snapSize / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f;
        }
    }

    predictSnapOffset_ = totalOffset_ - predictEndPos;
    predictSnapEndPos_ = predictEndPos;
}

void ArcListLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);
    auto axis_ = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    paddingOffset_ = padding.Offset();
    float crossSize = GetCrossAxisSize(size, axis_);
    totalItemCount_ = layoutWrapper->GetTotalChildCount() - itemStartIndex_;
    int32_t startIndex = GetStartIndex();

    totalOffset_ += currentOffset_;
    FixPredictSnapOffset(listLayoutProperty);
    // layout items.
    for (auto& pos : itemPosition_) {
        auto wrapper = GetListItem(layoutWrapper, pos.first);
        if (!wrapper) {
            continue;
        }
        pos.second.startPos -= currentOffset_;
        pos.second.endPos -= currentOffset_;
        LayoutItem(wrapper, pos.first, pos.second, startIndex, crossSize);
        if (expandSafeArea_ || wrapper->CheckNeedForceMeasureAndLayout()) {
            wrapper->Layout();
        } else {
            SyncGeometry(wrapper);
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(wrapper);
        if (frameNode) {
            frameNode->MarkAndCheckNewOpIncNode();
        }
    }
    for (auto& pos : recycledItemPosition_) {
        pos.second.startPos -= currentOffset_;
        pos.second.endPos -= currentOffset_;
    }

    GenerateItemOffset(layoutWrapper);

    for (auto& pos : itemPosition_) {
        auto wrapper = GetListItem(layoutWrapper, pos.first);
        if (!wrapper) {
            continue;
        }

        auto frameNode = wrapper->GetHostNode();
        if (!frameNode) {
            continue;
        }

        auto renderContext = frameNode->GetRenderContext();
        if (!renderContext) {
            continue;
        }

        // Adjust item location.
        // This must be adjust item location first and then scale it, otherwise it will not work properly.
        renderContext->UpdateTranslateInXY({ 0, pos.second.offsetY });

        // Scale item.
        renderContext->UpdateTransformScale({ pos.second.scale, pos.second.scale });
    }

    LayoutHeader(layoutWrapper, paddingOffset_, crossSize);

    auto cacheCount = listLayoutProperty->GetCachedCountValue(1);
    if (!itemPosition_.empty() && cacheCount > 0) {
        auto items = LayoutCachedItem(layoutWrapper, cacheCount);
        if (!items.empty()) {
            PostIdleTask(layoutWrapper->GetHostNode(), { items, childLayoutConstraint_ });
        } else {
            auto host = layoutWrapper->GetHostNode();
            CHECK_NULL_VOID(host);
            auto pattern = host->GetPattern<ArcListPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetPredictLayoutParam(std::nullopt);
        }
    }
}

void ArcListLayoutAlgorithm::GenerateItemOffset(LayoutWrapper* layoutWrapper)
{
    for (auto& pos : itemPosition_) {
        auto wrapper = GetListItem(layoutWrapper, pos.first);
        if (wrapper == nullptr) {
            continue;
        }

        auto autoScale = false;
        auto listItemLayoutProperty = AceType::DynamicCast<ArcListItemLayoutProperty>(wrapper->GetLayoutProperty());
        if (listItemLayoutProperty != nullptr) {
            autoScale = listItemLayoutProperty->GetAutoScale().value_or(true);
        }

        float scale = 1.0;
        auto contentCenterPos = contentMainSize_ / 2.0;
        if (autoScale) {
            auto itemCenterPos = (pos.second.startPos + pos.second.endPos) / 2.0;
            scale = GetNearScale(itemCenterPos - contentCenterPos);
        }

        pos.second.scale = scale;

        pos.second.offsetY = (pos.second.endPos - pos.second.startPos) * (scale - 1);
    }

    int32_t midIndex = GetMidIndex(layoutWrapper, true);

    auto iter = itemPosition_.find(midIndex);
    if (iter == itemPosition_.end()) {
        TAG_LOGE(AceLogTag::ACE_LIST, "No mid element was found in the forward traversal");
    } else {
        auto offset = iter->second.offsetY / 2.0;
        for (++iter; iter != itemPosition_.end(); ++iter) {
            auto bak = offset + iter->second.offsetY / 2.0;
            offset += iter->second.offsetY;
            iter->second.offsetY = bak;
        }
    }

    auto riter = itemPosition_.rbegin();
    while (riter != itemPosition_.rend() && riter->first != midIndex) {
        ++riter;
    }
    if (riter == itemPosition_.rend()) {
        TAG_LOGE(AceLogTag::ACE_LIST, "No mid element was found in the backward traversal");
    } else {
        auto offset = riter->second.offsetY / 2.0;
        riter->second.offsetY = 0.0f;
        for (++riter; riter != itemPosition_.rend(); ++riter) {
            auto bak = offset + riter->second.offsetY / 2.0;
            offset += riter->second.offsetY;
            riter->second.offsetY = -bak;
        }
    }
}

float ArcListLayoutAlgorithm::CalculatePredictSnapEndPositionByIndex(uint32_t index, float prevPredictEndPos)
{
    float predictSnapEndPos = prevPredictEndPos;
    float predictPos = prevPredictEndPos + contentMainSize_ / 2.0f - totalOffset_;
    float itemHeight = itemPosition_[index].endPos - itemPosition_[index].startPos;
    float snapSize = LessOrEqual(itemHeight, ARC_LIST_ITEM_SNAP_SIZE) ? itemHeight : ARC_LIST_ITEM_SNAP_SIZE;
    float snapLow = itemPosition_[index].startPos + snapSize / 2.0f;
    float snapHigh = itemPosition_[index].endPos - snapSize / 2.0f;
    predictPos = LessNotEqual(predictPos, snapLow) ? snapLow : predictPos;
    predictPos = LessNotEqual(snapHigh, predictPos) ? snapHigh : predictPos;
    predictSnapEndPos = totalOffset_ + predictPos - contentMainSize_ / 2.0f;
    return predictSnapEndPos;
}

void ArcListLayoutAlgorithm::OnItemPositionAddOrUpdate(LayoutWrapper* layoutWrapper, uint32_t index)
{
    if (!predictSnapEndPos_.has_value()) {
        return;
    }

    float startPos = 0.0f;
    float endPos = 0.0f;
    startPos = totalOffset_ + itemPosition_[index].startPos - spaceWidth_ / 2.0f;
    endPos = totalOffset_ + itemPosition_[index].endPos + spaceWidth_ / 2.0f;

    float predictSnapEndPos = predictSnapEndPos_.value();
    float stopOnScreen = contentMainSize_ / 2.0f;
    if (GreatOrEqual(predictSnapEndPos + stopOnScreen, startPos) &&
        LessNotEqual(predictSnapEndPos + stopOnScreen, endPos)) {
        predictSnapEndPos = CalculatePredictSnapEndPositionByIndex(index, predictSnapEndPos);
    } else {
        return;
    }

    if (!NearEqual(predictSnapEndPos, predictSnapEndPos_.value())) {
        predictSnapEndPos_ = predictSnapEndPos;
    }
}

void ArcListLayoutAlgorithm::MeasureHeader(LayoutWrapper* layoutWrapper)
{
    if (headerIndex_ < 0) {
        return;
    }

    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    auto headerLayoutConstraint = layoutProperty->CreateChildConstraint();
    headerLayoutConstraint.maxSize.SetMainSize(Infinity<float>(), axis_);

    auto headerWrapper = layoutWrapper->GetOrCreateChildByIndex(headerIndex_);
    CHECK_NULL_VOID(headerWrapper);
    headerWrapper->Measure(headerLayoutConstraint);
    headerMainSize_ = GetMainAxisSize(headerWrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
}

void ArcListLayoutAlgorithm::SetActiveChildRange(LayoutWrapper* layoutWrapper)
{
    if (itemPosition_.empty()) {
        layoutWrapper->SetActiveChildRange(-1, -1);
        return;
    }
    auto start = itemStartIndex_ + itemPosition_.begin()->first;
    auto end = itemStartIndex_ + itemPosition_.rbegin()->first;
    layoutWrapper->SetActiveChildRange(start, end);
}

void ArcListLayoutAlgorithm::LayoutHeader(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset, float crossSize)
{
    if (headerIndex_ < 0) {
        return;
    }

    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(headerIndex_);
    CHECK_NULL_VOID(wrapper);
    UpdateZIndex(wrapper);

    auto chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(headerIndex_) : 0.0f;
    if (itemPosition_.count(0) != 0) {
        auto info = itemPosition_[0];
        float itemDeltaHeight = (info.endPos - info.startPos) * (info.scale - 1);
        float itemDispStartPos = info.startPos + info.offsetY - itemDeltaHeight / 2.0f;
        if (LessOrEqual(itemDispStartPos, headerMainSize_)) {
            startHeaderPos_ = itemDispStartPos - headerMainSize_;
        } else {
            startHeaderPos_ = -chainOffset;
        }
    } else {
        startHeaderPos_ = -chainOffset - headerMainSize_;
    }

    auto offset = paddingOffset;
    float childCrossSize = GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    float crossOffset = (crossSize - childCrossSize) / 2;
    crossOffset = GreatOrEqual(crossOffset, 0.0f) ? crossOffset : 0.0f;

    offset = offset + OffsetF(crossOffset, startHeaderPos_ + chainOffset);

    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);

    if (expandSafeArea_ || wrapper->CheckNeedForceMeasureAndLayout()) {
        wrapper->Layout();
    } else {
        SyncGeometry(wrapper);
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(wrapper);
    if (frameNode) {
        frameNode->MarkAndCheckNewOpIncNode();
    }
}

void ArcListLayoutAlgorithm::UpdateZIndex(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateZIndex(1);
}

} // namespace OHOS::Ace::NG
