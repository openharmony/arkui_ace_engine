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

#include "core/components_ng/pattern/list/list_layout_algorithm.h"

#include <algorithm>
#include <unordered_set>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/layout_param.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void ListLayoutAlgorithm::UpdateListItemConstraint(
    Axis axis, const OptionalSizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = selfIdealSize;
    groupLayoutConstraint_ = contentConstraint;
    if (axis == Axis::VERTICAL) {
        contentConstraint.maxSize.SetHeight(Infinity<float>());
        groupLayoutConstraint_.maxSize.SetHeight(Infinity<float>());
        auto width = selfIdealSize.Width();
        if (width.has_value()) {
            float crossSize = width.value();
            groupLayoutConstraint_.maxSize.SetWidth(crossSize);
            if (lanes_.has_value() && lanes_.value() > 1) {
                crossSize /= lanes_.value();
            }
            if (maxLaneLength_.has_value() && maxLaneLength_.value() < crossSize) {
                crossSize = maxLaneLength_.value();
            }
            contentConstraint.percentReference.SetWidth(crossSize);
            contentConstraint.parentIdealSize.SetWidth(crossSize);
            contentConstraint.maxSize.SetWidth(crossSize);
            if (minLaneLength_.has_value()) {
                contentConstraint.minSize.SetWidth(minLaneLength_.value());
            } else {
                contentConstraint.minSize.SetWidth(crossSize);
            }
        }
        return;
    }
    contentConstraint.maxSize.SetWidth(Infinity<float>());
    groupLayoutConstraint_.maxSize.SetWidth(Infinity<float>());
    auto height = selfIdealSize.Height();
    if (height.has_value()) {
        float crossSize = height.value();
        groupLayoutConstraint_.maxSize.SetHeight(crossSize);
        if (lanes_.has_value() && lanes_.value() > 1) {
            crossSize /= lanes_.value();
        }
        if (maxLaneLength_.has_value() && maxLaneLength_.value() < crossSize) {
            crossSize = maxLaneLength_.value();
        }
        contentConstraint.percentReference.SetHeight(crossSize);
        contentConstraint.parentIdealSize.SetHeight(crossSize);
        contentConstraint.maxSize.SetHeight(crossSize);
        if (minLaneLength_.has_value()) {
            contentConstraint.minSize.SetHeight(minLaneLength_.value());
        } else {
            contentConstraint.minSize.SetHeight(crossSize);
        }
    }
}

void ListLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    if (overScrollFeature_ && !layoutWrapper->CheckChildNeedForceMeasureAndLayout()) {
        LOGD("in over scroll case");
        return;
    }
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);

    const auto& layoutConstraint = listLayoutProperty->GetLayoutConstraint().value();

    // calculate idealSize and set FrameSize
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);

    // calculate main size.
    auto contentConstraint = listLayoutProperty->GetContentLayoutConstraint().value();
    auto contentIdealSize = CreateIdealSize(
        contentConstraint, axis, listLayoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS));

    const auto& padding = listLayoutProperty->CreatePaddingAndBorder();
    paddingBeforeContent_ = axis == Axis::HORIZONTAL ? padding.left.value_or(0) : padding.top.value_or(0);
    paddingAfterContent_ = axis == Axis::HORIZONTAL ? padding.right.value_or(0) : padding.bottom.value_or(0);
    contentMainSize_ = 0.0f;
    totalItemCount_ = layoutWrapper->GetTotalChildCount();
    if (!GetMainAxisSize(contentIdealSize, axis)) {
        if (totalItemCount_ == 0) {
            contentMainSize_ = 0.0f;
        } else {
            // use parent max size first.
            auto parentMaxSize = contentConstraint.maxSize;
            contentMainSize_ = GetMainAxisSize(parentMaxSize, axis) - paddingBeforeContent_ - paddingAfterContent_;
            mainSizeIsDefined_ = false;
        }
    } else {
        contentMainSize_ = GetMainAxisSize(contentIdealSize.ConvertToSizeT(), axis);
        mainSizeIsDefined_ = true;
    }

    if (totalItemCount_ > 0) {
        startMainPos_ = currentOffset_;
        endMainPos_ = currentOffset_ + contentMainSize_;
        LOGD("pre start index: %{public}d, pre end index: %{public}d, offset is %{public}f, startMainPos: %{public}f, "
             "endMainPos: %{public}f",
            preStartIndex_, preEndIndex_, currentOffset_, startMainPos_, endMainPos_);

        auto mainPercentRefer = GetMainAxisSize(contentConstraint.percentReference, axis);
        auto space = listLayoutProperty->GetSpace().value_or(Dimension(0));
        spaceWidth_ = ConvertToPx(space, layoutConstraint.scaleProperty, mainPercentRefer).value_or(0);
        if (listLayoutProperty->GetDivider().has_value()) {
            auto divider = listLayoutProperty->GetDivider().value();
            std::optional<float> dividerSpace =
                ConvertToPx(divider.strokeWidth, layoutConstraint.scaleProperty, mainPercentRefer);
            if (dividerSpace.has_value()) {
                spaceWidth_ = std::max(spaceWidth_, dividerSpace.value());
            }
        }

        itemPosition_.clear();

        lanes_ = listLayoutProperty->GetLanes();
        if (listLayoutProperty->GetLaneMinLength().has_value()) {
            minLaneLength_ = ConvertToPx(
                listLayoutProperty->GetLaneMinLength().value(), layoutConstraint.scaleProperty, mainPercentRefer);
        }
        if (listLayoutProperty->GetLaneMaxLength().has_value()) {
            maxLaneLength_ = ConvertToPx(
                listLayoutProperty->GetLaneMaxLength().value(), layoutConstraint.scaleProperty, mainPercentRefer);
        }
        listItemAlign_ = listLayoutProperty->GetListItemAlign().value_or(V2::ListItemAlign::START);
        CalculateLanes(layoutConstraint, axis);
        // calculate child layout constraint.
        auto childLayoutConstraint = listLayoutProperty->CreateChildConstraint();
        UpdateListItemConstraint(axis, contentIdealSize, childLayoutConstraint);
        MeasureList(layoutWrapper, childLayoutConstraint, axis);
    } else {
        LOGI("child size is empty");
    }

    if (axis == Axis::HORIZONTAL) {
        contentIdealSize.SetWidth(contentMainSize_);
    } else {
        contentIdealSize.SetHeight(contentMainSize_);
    }
    AddPaddingToSize(padding, contentIdealSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(contentIdealSize.ConvertToSizeT());

    // set list cache info.
    layoutWrapper->SetCacheCount(listLayoutProperty->GetCachedCountValue(1) * lanes_.value_or(1));

    LOGD("new start index is %{public}d, new end index is %{public}d, offset is %{public}f, mainSize is %{public}f",
        GetStartIndex(), GetEndIndex(), currentOffset_, contentMainSize_);
}

void ListLayoutAlgorithm::RecyclePrevIndex(LayoutWrapper* layoutWrapper)
{
    if (preStartIndex_ < GetStartIndex() && preStartIndex_ >= 0) {
        for (int32_t i = preStartIndex_; i < GetStartIndex(); i++) {
            layoutWrapper->RemoveChildInRenderTree(i);
        }
    }
    if (preEndIndex_ > GetEndIndex()) {
        for (int32_t i = GetEndIndex() + 1; i <= preEndIndex_; i++) {
            layoutWrapper->RemoveChildInRenderTree(i);
        }
    }
}

void ListLayoutAlgorithm::CalculateEstimateOffset()
{
    float itemsHeight = (itemPosition_.rbegin()->second.second - itemPosition_.begin()->second.first) + spaceWidth_;
    auto lines = static_cast<int32_t>(itemPosition_.size());
    if (lanes_.has_value() && lanes_.value() > 1) {
        lines = (lines / lanes_.value()) + (lines % lanes_.value() > 0 ? 1 : 0);
    }
    if (lines > 0) {
        float averageHeight = itemsHeight / static_cast<float>(lines);
        estimateOffset_ = averageHeight * static_cast<float>(itemPosition_.begin()->first);
    } else {
        estimateOffset_ = 0;
    }
}

void ListLayoutAlgorithm::MeasureList(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis)
{
    if (jumpIndex_) {
        if (totalItemCount_ == 0) {
            LOGI("child size is empty");
            return;
        }
        if (jumpIndex_.value() < 0 || jumpIndex_.value() >= totalItemCount_) {
            LOGW("jump index is illegal, %{public}d, %{public}d", jumpIndex_.value(), totalItemCount_);
            jumpIndex_ = std::clamp(jumpIndex_.value(), 0, totalItemCount_ - 1);
        }
        if (lanes_.has_value() && lanes_.value() > 1) {
            jumpIndex_ = jumpIndex_.value() - jumpIndex_.value() % lanes_.value();
        }
        if (scrollIndexAlignment_ == ScrollIndexAlignment::ALIGN_TOP) {
            LayoutForward(layoutWrapper, layoutConstraint, axis, jumpIndex_.value(), 0.0f);
            float endPos = itemPosition_.begin()->second.first - spaceWidth_;
            if (jumpIndex_.value() > 0 && GreatNotEqual(endPos, startMainPos_)) {
                LayoutBackward(layoutWrapper, layoutConstraint, axis, jumpIndex_.value() - 1, endPos);
            }
        } else if (scrollIndexAlignment_ == ScrollIndexAlignment::ALIGN_BUTTON) {
            LayoutBackward(layoutWrapper, layoutConstraint, axis, jumpIndex_.value(), endMainPos_);
            float startPos = itemPosition_.rbegin()->second.second + spaceWidth_;
            if (jumpIndex_.value() < totalItemCount_ - 1 && LessNotEqual(startPos, endMainPos_)) {
                LayoutForward(layoutWrapper, layoutConstraint, axis, jumpIndex_.value() + 1, startPos);
            }
        }
        RecyclePrevIndex(layoutWrapper);
        CalculateEstimateOffset();
    } else if (NonNegative(currentOffset_)) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(preStartIndex_);
        if (!wrapper) {
            LOGI("the %{public}d wrapper is null in LayoutForward", preStartIndex_);
            return;
        }
        // Calculate the end pos of the priv item ahead of the StartIndex.
        // the child frame offset is include list padding and border, need to delete it first to match content origin.
        float startPos =
            GetMainAxisOffset(wrapper->GetGeometryNode()->GetMarginFrameOffset(), axis) - paddingBeforeContent_;
        LayoutForward(layoutWrapper, layoutConstraint, axis, preStartIndex_, startPos);
    } else {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(preEndIndex_);
        if (!wrapper) {
            LOGI("the %{public}d wrapper is null in LayoutBackward", preEndIndex_);
            return;
        }
        // Calculate the start pos of the next item behind the EndIndex.
        // the child frame offset is include list padding and border, need to delete it first to match content origin.
        float endPos = GetMainAxisOffset(wrapper->GetGeometryNode()->GetMarginFrameOffset(), axis) +
                       GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis) - paddingBeforeContent_;
        LayoutBackward(layoutWrapper, layoutConstraint, axis, preEndIndex_, endPos);
    }
}

int ListLayoutAlgorithm::LayoutALineForward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
    Axis axis, int& currentIndex, float& mainLen)
{
    int cnt = 0;
    int lanes = lanes_.has_value() && lanes_.value() > 1 ? lanes_.value() : 1;
    for (int i = 0; i < lanes; i++) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex + 1);
        if (!wrapper) {
            LOGI("the start %{public}d index wrapper is null", currentIndex + 1);
            return cnt;
        }
        auto itemGroup = GetListItemGroup(wrapper);
        if (itemGroup && cnt > 0) {
            break;
        }
        cnt++;
        ++currentIndex;
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem");
            if (itemGroup) {
                SetListItemGroupProperty(itemGroup, axis, lanes);
                wrapper->Measure(groupLayoutConstraint_);
            } else {
                wrapper->Measure(layoutConstraint);
            }
        }
        mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
        if (itemGroup) {
            break;
        }
    }
    return cnt;
}

int ListLayoutAlgorithm::LayoutALineBackward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
    Axis axis, int& currentIndex, float& mainLen)
{
    int cnt = 0;
    int lanes = lanes_.has_value() && lanes_.value() > 1 ? lanes_.value() : 1;
    for (int i = 0; i < lanes; i++) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex - 1);
        if (!wrapper) {
            LOGI("the %{public}d wrapper is null", currentIndex - 1);
            break;
        }
        auto itemGroup = GetListItemGroup(wrapper);
        if (itemGroup && cnt > 0) {
            break;
        }
        --currentIndex;
        cnt++;
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem");
            if (itemGroup) {
                SetListItemGroupProperty(itemGroup, axis, lanes);
                wrapper->Measure(groupLayoutConstraint_);
            } else {
                wrapper->Measure(layoutConstraint);
            }
        }
        mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis));
        if (currentIndex % lanes == 0 || itemGroup) {
            break;
        }
    }
    return cnt;
}

void ListLayoutAlgorithm::LayoutForward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
    Axis axis, int32_t startIndex, float startPos)
{
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    auto currentIndex = startIndex - 1;
    do {
        currentStartPos = currentEndPos;
        float mainLength = 0;
        int count = LayoutALineForward(layoutWrapper, layoutConstraint, axis, currentIndex, mainLength);
        if (count == 0) {
            break;
        }
        currentEndPos = currentStartPos + mainLength;
        for (int i = 0; i < count; i++) {
            itemPosition_[currentIndex - i] = { currentStartPos, currentEndPos };
        }
        if (currentIndex >= 0 && currentIndex < (totalItemCount_ - 1)) {
            currentEndPos += spaceWidth_;
        }
        LOGD("LayoutForward: %{public}d current start pos: %{public}f, current end pos: %{public}f", currentIndex,
            currentStartPos, currentEndPos);
    } while (LessNotEqual(currentEndPos, endMainPos_));

    if (overScrollFeature_) {
        LOGD("during over scroll, just return in LayoutForward");
        return;
    }

    bool normalToOverScroll = false;
    // adjust offset.
    if (LessNotEqual(currentEndPos, endMainPos_) && !itemPosition_.empty()) {
        auto firstItemTop = itemPosition_.begin()->second.first;
        auto itemTotalSize = currentEndPos - firstItemTop;
        if (LessOrEqual(itemTotalSize, contentMainSize_) && (itemPosition_.begin()->first == 0)) {
            // all items size is less than list.
            currentOffset_ = firstItemTop;
            if (!mainSizeIsDefined_) {
                // adapt child size.
                LOGD("LayoutForward: adapt child total size");
                contentMainSize_ = itemTotalSize;
            }
        } else {
            // adjust offset. If edgeEffect is SPRING, jump adjust to allow list scroll through boundary
            auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
            auto edgeEffect = listLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
            if ((edgeEffect != EdgeEffect::SPRING) || jumpIndex_.has_value()) {
                currentOffset_ = currentEndPos - contentMainSize_;
                LOGD("LayoutForward: adjust offset to %{public}f", currentOffset_);
                startMainPos_ = currentOffset_;
                endMainPos_ = currentEndPos;
            } else {
                normalToOverScroll = true;
            }
        }
    }

    if (normalToOverScroll) {
        LOGD("in normal status to overScroll state, ignore inactive operation in LayoutForward");
        return;
    }

    // Mark inactive in wrapper.
    for (auto pos = itemPosition_.begin(); pos != itemPosition_.end();) {
        if (GreatOrEqual(pos->second.second, startMainPos_)) {
            break;
        }
        LOGI("recycle item:%{public}d", pos->first);
        layoutWrapper->RemoveChildInRenderTree(pos->first);
        itemPosition_.erase(pos++);
    }
}

void ListLayoutAlgorithm::LayoutBackward(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis, int endIndex, float endPos)
{
    float currentStartPos = endPos;
    float currentEndPos = 0.0f;
    auto currentIndex = endIndex + 1;
    do {
        currentEndPos = currentStartPos;
        float mainLength = 0;
        int count = LayoutALineBackward(layoutWrapper, layoutConstraint, axis, currentIndex, mainLength);
        if (count == 0) {
            break;
        }
        currentStartPos = currentEndPos - mainLength;

        for (int i = 0; i < count; i++) {
            itemPosition_[currentIndex + i] = { currentStartPos, currentEndPos };
        }

        if (currentIndex > 0) {
            currentStartPos = currentStartPos - spaceWidth_;
        }
        LOGD("LayoutBackward: %{public}d current start pos: %{public}f, current end pos: %{public}f", currentIndex,
            currentStartPos, currentEndPos);
    } while (GreatNotEqual(currentStartPos, startMainPos_));

    if (overScrollFeature_) {
        LOGD("during over scroll, just return in LayoutBackward");
        return;
    }

    bool normalToOverScroll = false;
    // adjust offset. If edgeEffect is SPRING, jump adjust to allow list scroll through boundary
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto edgeEffect = listLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
    if (GreatNotEqual(currentStartPos, startMainPos_)) {
        if ((edgeEffect != EdgeEffect::SPRING) || jumpIndex_.has_value()) {
            currentOffset_ = currentStartPos;
            endMainPos_ = currentOffset_ + contentMainSize_;
            startMainPos_ = currentStartPos;
        } else {
            normalToOverScroll = true;
        }
    }

    if (normalToOverScroll) {
        LOGD("in normal status to overScroll state, ignore inactive operation in LayoutBackward");
        return;
    }
    // Mark inactive in wrapper.
    std::list<int32_t> removeIndexes;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        if (LessOrEqual(pos->second.first, endMainPos_)) {
            break;
        }
        layoutWrapper->RemoveChildInRenderTree(pos->first);
        removeIndexes.emplace_back(pos->first);
    }
    for (const auto& index : removeIndexes) {
        itemPosition_.erase(index);
    }
}

void ListLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto paddingOffset = OffsetF(left, top);
    float crossSize = GetCrossAxisSize(size, axis);
    totalItemCount_ = layoutWrapper->GetTotalChildCount();
    int32_t startIndex = GetStartIndex();

    // layout items.
    for (auto& pos : itemPosition_) {
        int32_t index = pos.first;
        auto offset = paddingOffset;
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!wrapper) {
            LOGI("wrapper is out of boundary");
            continue;
        }
        auto itemGroup = GetListItemGroup(wrapper);
        float childCrossSize = GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis);
        float crossOffset = 0.0f;
        pos.second.first -= currentOffset_;
        pos.second.second -= currentOffset_;
        if (lanes_.has_value() && lanes_.value() > 1) {
            int32_t laneIndex = 0;
            if (itemGroup) {
                startIndex = index + 1;
            } else {
                laneIndex = (index - startIndex) % lanes_.value();
            }
            crossOffset = CalculateLaneCrossOffset(crossSize, childCrossSize * lanes_.value());
            crossOffset += crossSize / lanes_.value() * laneIndex;
        } else {
            lanes_ = 1;
            crossOffset = CalculateLaneCrossOffset(crossSize, childCrossSize);
        }
        if (axis == Axis::VERTICAL) {
            offset = offset + OffsetF(crossOffset, pos.second.first);
        } else {
            offset = offset + OffsetF(pos.second.first, crossOffset);
        }
        wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
        if (!overScrollFeature_ || layoutWrapper->CheckChildNeedForceMeasureAndLayout()) {
            wrapper->Layout();
        }
    }
}

float ListLayoutAlgorithm::CalculateLaneCrossOffset(float crossSize, float childCrossSize)
{
    if (!lanes_.has_value() || lanes_.value() <= 0) {
        return 0.0f;
    }
    float delta = (crossSize - childCrossSize) / lanes_.value();
    if (LessOrEqual(delta, 0)) {
        return 0.0f;
    }
    switch (listItemAlign_) {
        case OHOS::Ace::V2::ListItemAlign::START:
            return 0.0f;
        case OHOS::Ace::V2::ListItemAlign::CENTER:
            return delta / 2.0f;
        case OHOS::Ace::V2::ListItemAlign::END:
            return delta;
        default:
            LOGW("Invalid ListItemAlign: %{public}d", listItemAlign_);
            return 0.0f;
    }
}

void ListLayoutAlgorithm::CalculateLanes(const LayoutConstraintF& layoutConstraint, Axis axis)
{
    do {
        SizeF layoutParamMaxSize = layoutConstraint.maxSize;
        SizeF layoutParamMinSize = layoutConstraint.minSize;
        // Case 1: lane length constrain is not set
        //      1.1: use [lanes_] set by user if [lanes_] is set
        //      1.2: set [lanes_] to 1 if [lanes_] is not set
        if (!minLaneLength_.has_value() || !maxLaneLength_.has_value()) {
            if (!lanes_.has_value() || lanes_.value() <= 0) {
                lanes_ = 1;
            }
            maxLaneLength_ = GetCrossAxisSize(layoutParamMaxSize, axis) / lanes_.value();
            minLaneLength_ = GetCrossAxisSize(layoutParamMinSize, axis) / lanes_.value();
            break;
        }
        // Case 2: lane length constrain is set --> need to calculate [lanes_] according to contraint.
        // We agreed on such rules (assuming we have a vertical list here):
        // rule 1: [minLaneLength_] has a higher priority than [maxLaneLength_] when decide [lanes_], for e.g.,
        //         if [minLaneLength_] is 40, [maxLaneLength_] is 60, list's width is 120,
        //         the [lanes_] is 3 rather than 2.
        // rule 2: after [lanes_] is determined by rule 1, the width of lane will be as large as it can be, for
        // e.g.,
        //         if [minLaneLength_] is 40, [maxLaneLength_] is 60, list's width is 132, the [lanes_] is 3
        //         according to rule 1, then the width of lane will be 132 / 3 = 44 rather than 40,
        //         its [minLaneLength_].
        ModifyLaneLength(layoutConstraint, axis);

        // if minLaneLength is 40, maxLaneLength is 60
        // when list's width is 120, lanes_ = 3
        // when list's width is 80, lanes_ = 2
        // when list's width is 70, lanes_ = 1
        float maxCrossSize = GetCrossAxisSize(layoutParamMaxSize, axis);
        float maxLanes = maxCrossSize / minLaneLength_.value();
        float minLanes = maxCrossSize / maxLaneLength_.value();
        // let's considerate scenarios when maxCrossSize > 0
        // now it's guaranteed that [minLaneLength_] <= [maxLaneLength_], i.e., maxLanes >= minLanes > 0
        // there are 3 scenarios:
        // 1. 1 > maxLanes >= minLanes > 0
        // 2. maxLanes >= 1 >= minLanes > 0
        // 3. maxLanes >= minLanes > 1

        // 1. 1 > maxLanes >= minLanes > 0 ---> maxCrossSize < minLaneLength_ =< maxLaneLength
        if (GreatNotEqual(1, maxLanes) && GreatOrEqual(maxLanes, minLanes)) {
            lanes_ = 1;
            minLaneLength_ = maxCrossSize;
            maxLaneLength_ = maxCrossSize;
            break;
        }
        // 2. maxLanes >= 1 >= minLanes > 0 ---> minLaneLength_ = maxCrossSize < maxLaneLength
        if (GreatOrEqual(maxLanes, 1) && LessOrEqual(minLanes, 1)) {
            lanes_ = std::floor(maxLanes);
            maxLaneLength_ = maxCrossSize;
            break;
        }
        // 3. maxLanes >= minLanes > 1 ---> minLaneLength_ <= maxLaneLength < maxCrossSize
        if (GreatOrEqual(maxLanes, minLanes) && GreatNotEqual(minLanes, 1)) {
            lanes_ = std::floor(maxLanes);
            break;
        }
        lanes_ = 1;
        LOGE("unexpected situation, set lanes to 1, maxLanes: %{public}f, minLanes: %{public}f, minLaneLength_: "
             "%{public}f, maxLaneLength_: %{public}f",
            maxLanes, minLanes, minLaneLength_.value(), maxLaneLength_.value());
    } while (false);
}

void ListLayoutAlgorithm::ModifyLaneLength(const LayoutConstraintF& layoutConstraint, Axis axis)
{
    if (LessOrEqual(maxLaneLength_.value(), 0.0)) {
        maxLaneLength_ = GetCrossAxisSize(layoutConstraint.maxSize, axis);
    }
    if (LessOrEqual(minLaneLength_.value(), 0.0)) {
        minLaneLength_ = std::min(GetCrossAxisSize(layoutConstraint.maxSize, axis), maxLaneLength_.value());
    }
    if (GreatNotEqual(minLaneLength_.value(), maxLaneLength_.value())) {
        LOGI("minLaneLength: %{public}f is greater than maxLaneLength: %{public}f, assign minLaneLength to"
             " maxLaneLength",
            minLaneLength_.value(), maxLaneLength_.value());
        maxLaneLength_ = minLaneLength_;
    }
}

RefPtr<ListItemGroupLayoutProperty> ListLayoutAlgorithm::GetListItemGroup(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    return AceType::DynamicCast<ListItemGroupLayoutProperty>(layoutProperty);
}

void ListLayoutAlgorithm::SetListItemGroupProperty(const RefPtr<ListItemGroupLayoutProperty>& itemGroup,
    Axis axis, int32_t lanes)
{
    itemGroup->UpdateListDirection(axis);
    itemGroup->UpdateLanes(lanes);
    itemGroup->UpdateListItemAlign(listItemAlign_);
}
} // namespace OHOS::Ace::NG
