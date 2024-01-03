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
#include "base/memory/ace_type.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/layout_param.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
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

void ListLayoutAlgorithm::UpdateListItemConstraint(
    Axis axis, const OptionalSizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = selfIdealSize;
    contentConstraint.maxSize.SetMainSize(Infinity<float>(), axis);
    auto crossSize = selfIdealSize.CrossSize(axis);
    if (crossSize.has_value()) {
        contentConstraint.maxSize.SetCrossSize(crossSize.value(), axis);
        contentConstraint.percentReference.SetCrossSize(crossSize.value(), axis);
    }
}

void ListLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);

    const auto& layoutConstraint = listLayoutProperty->GetLayoutConstraint().value();

    // calculate idealSize and set FrameSize
    axis_ = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    auto startOffset = listLayoutProperty->GetContentStartOffset().value_or(0.0f);
    contentStartOffset_ = std::max(PipelineBase::Vp2PxWithCurrentDensity(startOffset), 0.0);
    auto endOffset = listLayoutProperty->GetContentEndOffset().value_or(0.0f);
    contentEndOffset_ = std::max(PipelineBase::Vp2PxWithCurrentDensity(endOffset), 0.0);

    // calculate main size.
    auto contentConstraint = listLayoutProperty->GetContentLayoutConstraint().value();

    float expandHeight = ScrollableUtils::CheckHeightExpansion(listLayoutProperty, axis_);
    contentEndOffset_ += expandHeight;
    // expand contentSize
    contentConstraint.MinusPadding(std::nullopt, std::nullopt, std::nullopt, -expandHeight);

    auto contentIdealSize = CreateIdealSize(
        contentConstraint, axis_, listLayoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS));

    const auto& padding = listLayoutProperty->CreatePaddingAndBorder();
    paddingBeforeContent_ = axis_ == Axis::HORIZONTAL ? padding.left.value_or(0) : padding.top.value_or(0);
    paddingAfterContent_ = axis_ == Axis::HORIZONTAL ? padding.right.value_or(0) : padding.bottom.value_or(0);
    contentMainSize_ = 0.0f;
    totalItemCount_ = layoutWrapper->GetTotalChildCount();
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
    if (GreatOrEqual(contentStartOffset_ + contentEndOffset_, contentMainSize_)) {
        contentStartOffset_ = 0;
        contentEndOffset_ = 0;
    }

    if (totalItemCount_ > 0) {
        OnSurfaceChanged(layoutWrapper);

        stickyStyle_ = listLayoutProperty->GetStickyStyle().value_or(V2::StickyStyle::NONE);
        childLayoutConstraint_ = listLayoutProperty->CreateChildConstraint();
        auto mainPercentRefer = GetMainAxisSize(childLayoutConstraint_.percentReference, axis_);
        auto space = listLayoutProperty->GetSpace().value_or(Dimension(0));
        spaceWidth_ = ConvertToPx(space, layoutConstraint.scaleProperty, mainPercentRefer).value_or(0);
        if (Negative(spaceWidth_) || GreatOrEqual(spaceWidth_, contentMainSize_)) {
            spaceWidth_ = 0.0f;
        }
        if (listLayoutProperty->GetDivider().has_value()) {
            auto divider = listLayoutProperty->GetDivider().value();
            std::optional<float> dividerSpace = divider.strokeWidth.ConvertToPx();
            if (GreatOrEqual(dividerSpace.value(), contentMainSize_)) {
                dividerSpace.reset();
            }
            if (dividerSpace.has_value()) {
                spaceWidth_ = std::max(spaceWidth_, static_cast<float>(Round(dividerSpace.value())));
            }
        }
        spaceWidth_ += chainInterval_;
        CheckJumpToIndex();
        currentOffset_ = currentDelta_;
        startMainPos_ = currentOffset_;
        endMainPos_ = currentOffset_ + contentMainSize_;
        CalculateLanes(listLayoutProperty, layoutConstraint, contentIdealSize.CrossSize(axis_), axis_);
        listItemAlign_ = listLayoutProperty->GetListItemAlign().value_or(V2::ListItemAlign::START);
        // calculate child layout constraint.
        UpdateListItemConstraint(axis_, contentIdealSize, childLayoutConstraint_);
        MeasureList(layoutWrapper);
    } else {
        itemPosition_.clear();
        layoutWrapper->RemoveAllChildInRenderTree();
    }

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
    layoutWrapper->SetCacheCount(listLayoutProperty->GetCachedCountValue(1) * GetLanes());
}

float ListLayoutAlgorithm::GetChildMaxCrossSize(LayoutWrapper* layoutWrapper, Axis axis) const
{
    if (GetItemPosition().empty()) {
        return 0.0f;
    }
    float maxCrossSize = 0.0f;
    float crossSize = 0.0f;
    float prevPos = GetItemPosition().begin()->second.startPos;
    for (const auto& pos : GetItemPosition()) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos.first, false);
        if (!wrapper) {
            continue;
        }
        auto getGeometryNode = wrapper->GetGeometryNode();
        if (!getGeometryNode) {
            continue;
        }
        if (NearEqual(prevPos, pos.second.startPos)) {
            crossSize += getGeometryNode->GetMarginFrameSize().CrossSize(axis);
        } else {
            crossSize = getGeometryNode->GetMarginFrameSize().CrossSize(axis);
        }
        prevPos = pos.second.startPos;
        maxCrossSize = std::max(crossSize, maxCrossSize);
    }
    return maxCrossSize;
}

void ListLayoutAlgorithm::CalculateEstimateOffset(ScrollAlign align)
{
    if (itemPosition_.empty()) {
        estimateOffset_ = 0.0f;
        return;
    }
    float itemsHeight = (itemPosition_.rbegin()->second.endPos - itemPosition_.begin()->second.startPos) + spaceWidth_;
    auto lines = static_cast<int32_t>(itemPosition_.size());
    if (GetLanes() > 1) {
        lines = (lines / GetLanes()) + (lines % GetLanes() > 0 ? 1 : 0);
    }
    if (lines > 0) {
        float averageHeight = itemsHeight / static_cast<float>(lines);
        switch (align) {
            case ScrollAlign::START:
            case ScrollAlign::NONE:
                estimateOffset_ = averageHeight * static_cast<float>(jumpIndex_.value() / GetLanes()) -
                    contentStartOffset_;
                break;
            case ScrollAlign::CENTER:
                estimateOffset_ = averageHeight * static_cast<float>(jumpIndex_.value() / GetLanes()) -
                    contentMainSize_ / 2.0f + (averageHeight - spaceWidth_) / 2.0f;
                break;
            case ScrollAlign::END:
                estimateOffset_ = averageHeight * static_cast<float>(jumpIndex_.value() / GetLanes() + 1) -
                    spaceWidth_ - contentMainSize_ + contentEndOffset_;
                break;
            case ScrollAlign::AUTO:
                switch (scrollAutoType_) {
                    case ScrollAutoType::NOT_CHANGE:
                        estimateOffset_ = averageHeight * static_cast<float>(itemPosition_.begin()->first /
                            GetLanes()) - itemPosition_.begin()->second.startPos;
                        break;
                    case ScrollAutoType::START:
                        estimateOffset_ = averageHeight * static_cast<float>(jumpIndex_.value() / GetLanes());
                        break;
                    case ScrollAutoType::END:
                        estimateOffset_ = averageHeight * static_cast<float>(jumpIndex_.value() / GetLanes() + 1) -
                            spaceWidth_ - contentMainSize_;
                        break;
                }
                break;
        }
    } else {
        estimateOffset_ = 0.0f;
    }
}

void ListLayoutAlgorithm::ClearAllItemPosition(LayoutWrapper* layoutWrapper)
{
    for (auto& pos : itemPosition_) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos.first);
        if (!wrapper) {
            continue;
        }
        auto algorithm = wrapper->GetLayoutAlgorithm(true);
        if (!algorithm) {
            continue;
        }
        auto groupAlgorithm = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(algorithm->GetLayoutAlgorithm());
        if (!groupAlgorithm) {
            continue;
        }
        CHECK_NULL_VOID(groupAlgorithm);
        groupAlgorithm->ClearItemPosition(&(*wrapper));
    }
    itemPosition_.clear();
    layoutWrapper->RemoveAllChildInRenderTree();
}

void ListLayoutAlgorithm::BeginLayoutForward(float startPos, LayoutWrapper* layoutWrapper)
{
    int32_t index = GetLanesFloor(layoutWrapper, jumpIndex_.value());
    LayoutForward(layoutWrapper, index, startPos);
    if ((GetStartIndex() > 0) && GreatNotEqual(GetStartPosition(), startMainPos_)) {
        LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
        if ((GetEndIndex() < totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
            LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
        }
    }
}

void ListLayoutAlgorithm::BeginLayoutBackward(float startPos, LayoutWrapper* layoutWrapper)
{
    int32_t index = GetLanesCeil(layoutWrapper, jumpIndex_.value());
    LayoutBackward(layoutWrapper, index, startPos);
    if (LessOrEqual(GetEndIndex(), totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
        LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
        if ((GetStartIndex() > 0) && GreatNotEqual(GetStartPosition(), startMainPos_)) {
            LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
        }
    }
}

void ListLayoutAlgorithm::HandleJumpAuto(LayoutWrapper* layoutWrapper,
    int32_t& startIndex, int32_t& endIndex, float& startPos, float& endPos)
{
    bool isSmoothJump = false;
    int32_t jumpIndex = 0;
    if (jumpIndex_.has_value()) {
        jumpIndex = jumpIndex_.value();
    } else {
        jumpIndex = targetIndex_.value();
        isSmoothJump = true;
    }
    int32_t tempStartIndex = startIndex;
    int32_t tempEndIndex = endIndex;
    if (GreatNotEqual(GetLanes(), 1)) {
        jumpIndex = GetLanesFloor(layoutWrapper, jumpIndex);
        tempStartIndex = GetLanesFloor(layoutWrapper, tempStartIndex);
        tempEndIndex = GetLanesFloor(layoutWrapper, tempEndIndex);
    }
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(jumpIndex);
    CHECK_NULL_VOID(wrapper);
    bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (!isGroup) {
        if (jumpIndex >= tempEndIndex) {
            scrollAutoType_ = ScrollAutoType::END;
            if (!isSmoothJump) {
                jumpIndex_ = GetLanesCeil(layoutWrapper, jumpIndex_.value());
                startPos = contentMainSize_;
                BeginLayoutBackward(startPos, layoutWrapper);
            }
        } else if (jumpIndex <= tempStartIndex) {
            scrollAutoType_ = ScrollAutoType::START;
            if (!isSmoothJump) {
                jumpIndex_ = GetLanesFloor(layoutWrapper, jumpIndex_.value());
                startPos = 0.0f;
                BeginLayoutForward(startPos, layoutWrapper);
            }
        }
    } else if (jumpIndexInGroup_) {
        if (scrollAutoType_ == ScrollAutoType::START) {
            scrollAlign_ = ScrollAlign::START;
            HandleJumpStart(layoutWrapper);
        } else if (scrollAutoType_ == ScrollAutoType::END) {
            scrollAlign_ = ScrollAlign::END;
            HandleJumpEnd(layoutWrapper);
        }
    } else if (jumpIndex <= tempStartIndex) {
        auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, jumpIndex, contentMainSize_, false, listLayoutProperty, false);
        wrapper->Measure(childLayoutConstraint_);
        float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
        if (GreatNotEqual(contentMainSize_, mainLen)) {
            scrollAutoType_ = ScrollAutoType::START;
            if (!isSmoothJump) {
                startPos = 0.0f;
                BeginLayoutForward(startPos, layoutWrapper);
            }
        } else {
            scrollAutoType_ = ScrollAutoType::END;
            if (!isSmoothJump) {
                startPos = contentMainSize_;
                BeginLayoutBackward(startPos, layoutWrapper);
            }
        }
    } else if (jumpIndex >= tempEndIndex) {
        auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, jumpIndex, 0.0f, false, listLayoutProperty, false);
        wrapper->Measure(childLayoutConstraint_);
        float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
        if (GreatOrEqual(mainLen, contentMainSize_)) {
            scrollAutoType_ = ScrollAutoType::START;
            if (!isSmoothJump) {
                startPos = 0.0f;
                BeginLayoutForward(startPos, layoutWrapper);
            }
        } else {
            scrollAutoType_ = ScrollAutoType::END;
            if (!isSmoothJump) {
                startPos = contentMainSize_;
                BeginLayoutBackward(startPos, layoutWrapper);
            }
        }
    }
}

void ListLayoutAlgorithm::HandleJumpCenter(LayoutWrapper* layoutWrapper)
{
    int32_t index = GetLanesFloor(layoutWrapper, jumpIndex_.value());
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    bool isGroup = wrapper && wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup && jumpIndexInGroup_.has_value()) {
        int32_t indexInGroup = jumpIndexInGroup_.value();
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, index, 0.0f, true, listLayoutProperty, false);
        wrapper->Measure(GetGroupLayoutConstraint());
        itemPosition_[index] = GetListItemGroupPosition(wrapper, indexInGroup);
        if (LessNotEqual(GetEndPosition(), endMainPos_)) {
            LayoutForward(layoutWrapper, index + 1, GetEndPosition());
        }
    } else {
        float mainLen = MeasureAndGetChildHeight(layoutWrapper, index);
        float startPos = (contentMainSize_ - mainLen) / 2.0f;
        if (LessNotEqual(startPos, endMainPos_)) {
            LayoutForward(layoutWrapper, index, startPos);
        }
    }
    if (GreatNotEqual(GetStartPosition(), startMainPos_)) {
        LayoutBackward(layoutWrapper, index - 1, GetStartPosition());
    }
    if ((GetEndIndex() < totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_ - contentEndOffset_)) {
        LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
    }
}

void ListLayoutAlgorithm::HandleJumpStart(LayoutWrapper* layoutWrapper)
{
    int32_t index = GetLanesFloor(layoutWrapper, jumpIndex_.value());
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    bool isGroup = wrapper && wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup && jumpIndexInGroup_.has_value()) {
        int32_t indexInGroup = jumpIndexInGroup_.value();
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, index, 0.0f, true, listLayoutProperty, false);
        wrapper->Measure(GetGroupLayoutConstraint());
        itemPosition_[index] = GetListItemGroupPosition(wrapper, indexInGroup);
        if (LessNotEqual(GetEndPosition(), endMainPos_)) {
            LayoutForward(layoutWrapper, index + 1, GetEndPosition());
        }
        if (GetStartIndex() > 0 && GreatNotEqual(GetStartPosition(), startMainPos_)) {
            LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
        }
    } else {
        BeginLayoutForward(contentStartOffset_, layoutWrapper);
    }
}

void ListLayoutAlgorithm::HandleJumpEnd(LayoutWrapper* layoutWrapper)
{
    int32_t index = GetLanesCeil(layoutWrapper, jumpIndex_.value());
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    bool isGroup = wrapper && wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup && jumpIndexInGroup_.has_value()) {
        int32_t indexInGroup = jumpIndexInGroup_.value();
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, index, contentMainSize_, true, listLayoutProperty, false);
        wrapper->Measure(GetGroupLayoutConstraint());
        itemPosition_[index] = GetListItemGroupPosition(wrapper, indexInGroup);
        if (GreatNotEqual(GetStartPosition(), startMainPos_)) {
            LayoutBackward(layoutWrapper, index - 1, GetStartPosition());
        }
        if (GetEndIndex() <= totalItemCount_ -1 && LessNotEqual(GetEndPosition(), endMainPos_)) {
            LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
        }
    } else {
        BeginLayoutBackward(contentMainSize_ - contentEndOffset_, layoutWrapper);
    }
}

bool ListLayoutAlgorithm::CheckNoNeedJumpListItem(LayoutWrapper* layoutWrapper,
    float startPos, float endPos, int32_t startIndex, int32_t endIndex, int32_t jumpIndex)
{
    int32_t tempJumpIndex = jumpIndex;
    int32_t tempStartIndex = startIndex;
    int32_t tempEndIndex = endIndex;
    if (GreatNotEqual(GetLanes(), 1)) {
        tempJumpIndex = GetLanesFloor(layoutWrapper, jumpIndex);
        tempStartIndex = GetLanesFloor(layoutWrapper, tempStartIndex);
        tempEndIndex = GetLanesFloor(layoutWrapper, tempEndIndex);
    }
    if (tempJumpIndex > tempStartIndex && tempJumpIndex < tempEndIndex) {
        return true;
    }
    if (tempJumpIndex == tempStartIndex && tempJumpIndex == tempEndIndex) {
        return true;
    }
    if ((tempJumpIndex == tempStartIndex) && GreatOrEqual(startPos, 0.0f)) {
        return true;
    }
    if ((tempJumpIndex == tempEndIndex) && LessOrEqual(endPos, contentMainSize_)) {
        return true;
    }
    return false;
}

bool ListLayoutAlgorithm::CheckNoNeedJumpListItemGroup(LayoutWrapper* layoutWrapper,
    int32_t startIndex, int32_t endIndex, int32_t jumpIndex, float jumpIndexStartPos)
{
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(jumpIndex);
    CHECK_NULL_RETURN(wrapper, true);
    if (wrapper->GetHostTag() != V2::LIST_ITEM_GROUP_ETS_TAG) {
        return true;
    }
    int32_t jumpIndexInGroup = 0;
    if (jumpIndexInGroup_.has_value()) {
        jumpIndexInGroup = jumpIndexInGroup_.value();
    } else {
        return false;
    }

    auto layoutAlgorithm = wrapper->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithm, true);
    auto groupLayoutAlgorithm =
        AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithm->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(groupLayoutAlgorithm, true);
    auto groupItemPosition = groupLayoutAlgorithm->GetItemPosition();
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(listLayoutProperty, false);

    if (jumpIndex >= startIndex && jumpIndex <= endIndex) {
        auto it = groupItemPosition.find(jumpIndexInGroup);
        if (it != groupItemPosition.end()) {
            auto topPos = jumpIndexStartPos + it->second.first;
            auto bottomPos = jumpIndexStartPos + it->second.second;
            if (JudgeInOfScreenScrollAutoType(wrapper, listLayoutProperty, topPos, bottomPos)) {
                return true;
            }
        } else if (groupItemPosition.size() > 0) {
            JudgeOutOfScreenScrollAutoType(wrapper, jumpIndex, listLayoutProperty, jumpIndexInGroup, jumpIndexInGroup,
                groupItemPosition.begin()->first, groupItemPosition.rbegin()->first);
        } else {
            scrollAutoType_ = ScrollAutoType::NOT_CHANGE;
            return true;
        }
    } else  {
        JudgeOutOfScreenScrollAutoType(wrapper, jumpIndex, listLayoutProperty, jumpIndexInGroup, jumpIndex,
            startIndex, endIndex);
    }
    return false;
}

bool ListLayoutAlgorithm::JudgeInOfScreenScrollAutoType(const RefPtr<LayoutWrapper>& layoutWrapper,
    const RefPtr<ListLayoutProperty>& layoutProperty, float topPos, float bottomPos)
{
    auto stickyStyle = layoutProperty->GetStickyStyle().value_or(V2::StickyStyle::NONE);

    auto groupNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(groupNode, true);
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(groupPattern, true);
    
    float headerMainSize = 0.0f;
    float footerMainSize = 0.0f;
    if (stickyStyle == V2::StickyStyle::BOTH || stickyStyle == V2::StickyStyle::HEADER) {
        headerMainSize = groupPattern->GetHeaderMainSize();
    } else if (stickyStyle == V2::StickyStyle::BOTH || stickyStyle == V2::StickyStyle::FOOTER) {
        footerMainSize = groupPattern->GetFooterMainSize();
    }

    if (GreatOrEqual(topPos, startMainPos_ + headerMainSize) &&
        LessOrEqual(bottomPos, endMainPos_ - footerMainSize)) {
        scrollAutoType_ = ScrollAutoType::NOT_CHANGE;
        return true;
    } else if (NearEqual(topPos, startMainPos_ + headerMainSize) ||
        NearEqual(bottomPos, endMainPos_ - footerMainSize)) {
        scrollAutoType_ = ScrollAutoType::NOT_CHANGE;
        return true;
    } else if (GreatOrEqual(std::abs(topPos - startMainPos_), std::abs(endMainPos_ - bottomPos))) {
        scrollAutoType_ = ScrollAutoType::END;
    } else if (LessNotEqual(std::abs(topPos - startMainPos_), std::abs(endMainPos_ - bottomPos))) {
        scrollAutoType_ = ScrollAutoType::START;
    }

    return false;
}

void ListLayoutAlgorithm::JudgeOutOfScreenScrollAutoType(const RefPtr<LayoutWrapper>& layoutWrapper, int32_t index,
    const RefPtr<ListLayoutProperty>& layoutProperty, int32_t indexInGroup, int32_t judgeIndex,
    int32_t startIndex, int32_t endIndex)
{
    SetListItemGroupParam(layoutWrapper, index, 0.0f, true, layoutProperty, false);
    layoutWrapper->Measure(childLayoutConstraint_);
    auto jumpItemHeight = GetListGroupItemHeight(layoutWrapper, indexInGroup);
    jumpIndexInGroup_ = indexInGroup;

    if (judgeIndex < startIndex) {
        if (jumpItemHeight > contentMainSize_) {
            scrollAutoType_ = ScrollAutoType::END;
        } else {
            scrollAutoType_ = ScrollAutoType::START;
        }
    } else if (judgeIndex > endIndex) {
        if (jumpItemHeight > contentMainSize_) {
            scrollAutoType_ = ScrollAutoType::START;
        } else {
            scrollAutoType_ = ScrollAutoType::END;
        }
    }
}

bool ListLayoutAlgorithm::NoNeedJump(LayoutWrapper* layoutWrapper, float startPos, float endPos,
    int32_t startIndex, int32_t endIndex, int32_t jumpIndex, float jumpIndexStartPos)
{
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(jumpIndex);
    CHECK_NULL_RETURN(wrapper, true);
    if (wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG && jumpIndexInGroup_.has_value()) {
        if (CheckNoNeedJumpListItemGroup(layoutWrapper, startIndex, endIndex, jumpIndex, jumpIndexStartPos)) {
            return true;
        }
    } else {
        if (CheckNoNeedJumpListItem(layoutWrapper, startPos, endPos, startIndex, endIndex, jumpIndex)) {
            return true;
        }
    }
    return false;
}

float ListLayoutAlgorithm::MeasureAndGetChildHeight(LayoutWrapper* layoutWrapper, int32_t childIndex)
{
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(childIndex);
    CHECK_NULL_RETURN(wrapper, 0.0f);
    bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup) {
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        // true: layout forward, true: layout all group items.
        SetListItemGroupParam(wrapper, childIndex, 0.0f, true, listLayoutProperty, true);
    }
    wrapper->Measure(childLayoutConstraint_);
    float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    return mainLen;
}

void ListLayoutAlgorithm::CheckJumpToIndex()
{
    if (jumpIndex_.has_value()) {
        return;
    }
    if (LessOrEqual(std::abs(currentDelta_), contentMainSize_ * 2.0f) || itemPosition_.empty()) {
        return;
    }
    for (const auto& pos : itemPosition_) {
        if (pos.second.isGroup) {
            return;
        }
    }
    float totalHeight = itemPosition_.rbegin()->second.endPos - itemPosition_.begin()->second.startPos + spaceWidth_;
    float averageHeight = totalHeight / itemPosition_.size();
    int32_t targetIndex = itemPosition_.begin()->first;
    currentDelta_ -= itemPosition_.begin()->second.startPos;
    if (NonNegative(currentDelta_)) {
        int32_t items = currentDelta_ / averageHeight;
        targetIndex += items;
        currentDelta_ -= items * averageHeight;
    } else {
        int32_t items = -currentDelta_ / averageHeight;
        targetIndex -= items;
        currentDelta_ += items * averageHeight;
        if (targetIndex <= 0) {
            currentDelta_ = 0;
        }
    }
    jumpIndex_ = std::clamp(targetIndex, 0, totalItemCount_ - 1);
}

void ListLayoutAlgorithm::UpdateSnapCenterContentOffset(LayoutWrapper* layoutWrapper)
{
    if (IsScrollSnapAlignCenter(layoutWrapper) && !itemPosition_.empty()) {
        float itemHeight = 0.0f;
        if (GetStartIndex() == 0) {
            itemHeight = itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos;
            contentStartOffset_ = (contentMainSize_ - itemHeight) / 2.0f;
        }
        if (GetEndIndex() == totalItemCount_ - 1) {
            itemHeight = itemPosition_.rbegin()->second.endPos - itemPosition_.rbegin()->second.startPos;
            contentEndOffset_ = (contentMainSize_ - itemHeight) / 2.0f;
        }
    }
}

bool ListLayoutAlgorithm::CheckJumpValid(LayoutWrapper* layoutWrapper)
{
    if (jumpIndex_.value() == LAST_ITEM) {
        jumpIndex_ = totalItemCount_ - 1;
    } else if ((jumpIndex_.value() < 0) || (jumpIndex_.value() >= totalItemCount_)) {
        return false;
    }
    if (jumpIndex_ && jumpIndexInGroup_) {
        auto groupWrapper = layoutWrapper->GetOrCreateChildByIndex(jumpIndex_.value());
        CHECK_NULL_RETURN(groupWrapper, false);
        if (groupWrapper->GetHostTag() != V2::LIST_ITEM_GROUP_ETS_TAG) {
            return false;
        }
        auto groupNode = groupWrapper->GetHostNode();
        CHECK_NULL_RETURN(groupNode, false);
        auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
        CHECK_NULL_RETURN(groupPattern, false);

        auto groupItemCount = groupWrapper->GetTotalChildCount() - groupPattern->GetItemStartIndex();

        if (jumpIndexInGroup_.value() == LAST_ITEM) {
            jumpIndexInGroup_ = groupItemCount - 1;
        } else if ((jumpIndexInGroup_.value() < 0) || (jumpIndexInGroup_.value() >= groupItemCount)) {
            return false;
        }
    }
    return true;
}

void ListLayoutAlgorithm::MeasureList(LayoutWrapper* layoutWrapper)
{
    int32_t startIndex = 0;
    int32_t endIndex = 0;
    int32_t midIndex = 0;
    float midItemMidPos = 0.0f;
    float startPos = 0.0f;
    float endPos = 0.0f;
    float jumpIndexStartPos = 0.0f;
    int32_t jumpIndex = 0;

    if (jumpIndex_ && scrollAlign_ == ScrollAlign::AUTO) {
        if (jumpIndex_.has_value()) {
            jumpIndex = jumpIndex_.value();
        }
        auto it = itemPosition_.find(jumpIndex);
        if (it != itemPosition_.end()) {
            jumpIndexStartPos = it->second.startPos;
        }
    }

    if (jumpIndex_) {
        if (!CheckJumpValid(layoutWrapper)) {
            jumpIndex_.reset();
            jumpIndexInGroup_.reset();
        } else {
            if (jumpIndex_ && scrollAlign_ == ScrollAlign::CENTER) {
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
        startIndex = std::min(GetStartIndex(), totalItemCount_ - 1);
        endIndex = std::min(GetEndIndex(), totalItemCount_ - 1);
        if (GetStartIndex() > totalItemCount_ - 1 && !jumpIndex_.has_value()) {
            jumpIndex_ = totalItemCount_ - 1;
            scrollAlign_ = ScrollAlign::END;
        }
        if (overScrollFeature_) {
            UpdateSnapCenterContentOffset(layoutWrapper);
        }
        if (IsScrollSnapAlignCenter(layoutWrapper)) {
            midIndex = GetMidIndex(layoutWrapper, true);
            midItemMidPos = (itemPosition_[midIndex].startPos + itemPosition_[midIndex].endPos) / 2.0f -
                prevContentMainSize_ / 2.0f + contentMainSize_ / 2.0f;
            midIndex = std::min(midIndex, totalItemCount_ - 1);
        }
        OffScreenLayoutDirection();
        itemPosition_.clear();
        layoutWrapper->RemoveAllChildInRenderTree();
    }
    if (jumpIndex_ && scrollAlign_ == ScrollAlign::AUTO &&
        NoNeedJump(layoutWrapper, startPos, endPos, startIndex, endIndex, jumpIndex, jumpIndexStartPos)) {
        jumpIndex_.reset();
        jumpIndexInGroup_.reset();
    }
    if (jumpIndex_) {
        switch (scrollAlign_) {
            case ScrollAlign::START:
            case ScrollAlign::NONE:
                HandleJumpStart(layoutWrapper);
                break;
            case ScrollAlign::CENTER:
                HandleJumpCenter(layoutWrapper);
                break;
            case ScrollAlign::END:
                HandleJumpEnd(layoutWrapper);
                break;
            case ScrollAlign::AUTO:
                HandleJumpAuto(layoutWrapper, startIndex, endIndex, startPos, endPos);
                break;
        }
        CalculateEstimateOffset(scrollAlign_);
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
        jumpIndexInGroup_.reset();
        bool overScrollTop = startIndex == 0 && GreatNotEqual(startPos, startMainPos_ + contentStartOffset_);
        float midItemHeight = 0.0f;
        if (IsScrollSnapAlignCenter(layoutWrapper)) {
            midItemHeight = MeasureAndGetChildHeight(layoutWrapper, midIndex);
        }
        if (NearZero(currentOffset_) || (!overScrollFeature_ && NonNegative(currentOffset_)) ||
            (overScrollFeature_ && overScrollTop)) {
            if (overScrollTop && !canOverScroll_) {
                startPos = startMainPos_ + contentStartOffset_;
            }
            if (IsScrollSnapAlignCenter(layoutWrapper)) {
                midIndex = GetLanesFloor(layoutWrapper, midIndex);
                LayoutForward(layoutWrapper, midIndex, midItemMidPos - midItemHeight / 2.0f);
            } else {
                startIndex = GetLanesFloor(layoutWrapper, startIndex);
                LayoutForward(layoutWrapper, startIndex, startPos);
            }
            if (GetStartIndex() > 0 && GreatNotEqual(GetStartPosition(), startMainPos_)) {
                LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
            }
        } else {
            if (overScrollFeature_ && !overScrollTop && !NearZero(prevContentMainSize_)) {
                endPos += contentMainSize_ - prevContentMainSize_;
            }
            if (IsScrollSnapAlignCenter(layoutWrapper)) {
                endIndex = midIndex;
                endPos = midItemMidPos + midItemHeight / 2.0f;
            }
            endIndex = GetLanesCeil(layoutWrapper, endIndex);
            LayoutBackward(layoutWrapper, endIndex, endPos);
            if (GetEndIndex() < (totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
                LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
            }
        }
    }
}

int32_t ListLayoutAlgorithm::LayoutALineForward(LayoutWrapper* layoutWrapper,
    int32_t& currentIndex, float startPos, float& endPos)
{
    if (currentIndex + 1 >= totalItemCount_) {
        return 0;
    }
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex + 1);
    CHECK_NULL_RETURN(wrapper, 0);
    int32_t id = wrapper->GetHostNode()->GetId();
    ++currentIndex;
    bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup) {
        auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, currentIndex, startPos, true, listLayoutProperty, false);
    }
    {
        ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
        wrapper->Measure(childLayoutConstraint_);
    }
    float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    endPos = startPos + mainLen;
    itemPosition_[currentIndex] = { id, startPos, endPos, isGroup };
    OnItemPositionAddOrUpdate(layoutWrapper, currentIndex);
    return 1;
}

int32_t ListLayoutAlgorithm::LayoutALineBackward(LayoutWrapper* layoutWrapper,
    int32_t& currentIndex, float endPos, float& startPos)
{
    if (currentIndex - 1 < 0) {
        return 0;
    }
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex - 1);
    CHECK_NULL_RETURN(wrapper, 0);
    int32_t id = wrapper->GetHostNode()->GetId();
    --currentIndex;
    bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup) {
        auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, currentIndex, endPos, false, listLayoutProperty, false);
    }
    {
        ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
        wrapper->Measure(childLayoutConstraint_);
    }
    float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    startPos = endPos - mainLen;
    itemPosition_[currentIndex] = { id, startPos, endPos, isGroup };
    OnItemPositionAddOrUpdate(layoutWrapper, currentIndex);
    return 1;
}

void ListLayoutAlgorithm::LayoutForward(LayoutWrapper* layoutWrapper, int32_t startIndex, float startPos)
{
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    float endMainPos = overScrollFeature_ ?
        std::max(startPos + contentMainSize_ - contentStartOffset_, endMainPos_) : endMainPos_;
    if (forwardFeature_ && targetIndex_ && NonNegative(targetIndex_.value())) {
        endMainPos = Infinity<float>();
    }

    auto currentIndex = startIndex - 1;
    auto chainOffset = 0.0f;
    do {
        currentStartPos = currentEndPos;
        int32_t count = LayoutALineForward(layoutWrapper, currentIndex, currentStartPos, currentEndPos);
        if (count == 0) {
            break;
        }
        if (currentIndex >= 0 && currentIndex < (totalItemCount_ - 1)) {
            currentEndPos += spaceWidth_;
        }
        chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(currentIndex) : 0.0f;
        // reach the valid target index
        if (forwardFeature_ && targetIndex_ && GreatNotEqual(currentIndex, targetIndex_.value())) {
            endMainPos = GetEndPosition() + contentMainSize_;
            targetIndex_.reset();
        }
    } while (LessNotEqual(currentEndPos + chainOffset, endMainPos));

    currentEndPos += chainOffset;
    // adjust offset.
    UpdateSnapCenterContentOffset(layoutWrapper);
    if (LessNotEqual(currentEndPos, endMainPos_ - contentEndOffset_) && !itemPosition_.empty()) {
        endMainPos_ = currentEndPos + contentEndOffset_;
        startMainPos_ = endMainPos_ - contentMainSize_;
        auto firstItemTop = itemPosition_.begin()->second.startPos;
        if (GreatNotEqual(firstItemTop, startMainPos_) && itemPosition_.begin()->second.isGroup) {
            AdjustPostionForListItemGroup(layoutWrapper, axis_, GetStartIndex(), true);
            firstItemTop = itemPosition_.begin()->second.startPos;
        }
        auto itemTotalSize = currentEndPos - firstItemTop + contentEndOffset_ + contentStartOffset_;
        if (LessOrEqual(itemTotalSize, contentMainSize_) && (itemPosition_.begin()->first == 0)) {
            // all items size is less than list.
            if (!canOverScroll_) {
                currentOffset_ = firstItemTop - contentStartOffset_;
                startMainPos_ = currentOffset_;
                endMainPos_ = startMainPos_ + contentMainSize_;
            }
            if (!mainSizeIsDefined_) {
                // adapt child size.
                contentMainSize_ = itemTotalSize;
            }
        } else {
            // adjust offset. If edgeEffect is SPRING, jump adjust to allow list scroll through boundary
            if (!canOverScroll_ || jumpIndex_.has_value()) {
                currentOffset_ = currentEndPos + contentEndOffset_ - contentMainSize_;
            }
        }
    }
    if (overScrollFeature_ && canOverScroll_) {
        return;
    }
    // Mark inactive in wrapper.
    for (auto pos = itemPosition_.begin(); pos != itemPosition_.end();) {
        chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(pos->first) : 0.0f;
        // Don't recycle When the head item is Visibility.None.
        if (GreatNotEqual(pos->second.endPos + chainOffset, startMainPos_) ||
            GreatOrEqual(pos->second.startPos + chainOffset, startMainPos_)) {
            if (pos->second.isGroup) {
                CheckListItemGroupRecycle(layoutWrapper, pos->first, pos->second.startPos + chainOffset, true);
            }
            break;
        }
        layoutWrapper->RemoveChildInRenderTree(pos->first);
        itemPosition_.erase(pos++);
    }
}

void ListLayoutAlgorithm::LayoutBackward(LayoutWrapper* layoutWrapper, int32_t endIndex, float endPos)
{
    float currentStartPos = endPos;
    float currentEndPos = 0.0f;
    float startMainPos = overScrollFeature_ ?
        std::min(endPos - contentMainSize_ + contentEndOffset_, startMainPos_) : startMainPos_;
    if (backwardFeature_ && targetIndex_ && NonNegative(targetIndex_.value())) {
        startMainPos = -Infinity<float>();
    }
    auto currentIndex = endIndex + 1;
    auto chainOffset = 0.0f;
    do {
        currentEndPos = currentStartPos;
        int32_t count = LayoutALineBackward(layoutWrapper, currentIndex, currentEndPos, currentStartPos);
        if (count == 0) {
            break;
        }
        if (currentIndex > 0) {
            currentStartPos = currentStartPos - spaceWidth_;
        }
        chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(currentIndex) : 0.0f;
        // reach the valid target index
        if (backwardFeature_ && targetIndex_ && LessOrEqual(currentIndex, targetIndex_.value())) {
            startMainPos = GetStartPosition() - contentMainSize_;
            targetIndex_.reset();
        }
    } while (GreatNotEqual(currentStartPos + chainOffset, startMainPos));

    currentStartPos += chainOffset;
    // adjust offset. If edgeEffect is SPRING, jump adjust to allow list scroll through boundary
    UpdateSnapCenterContentOffset(layoutWrapper);
    if (GreatNotEqual(currentStartPos, startMainPos_ + contentStartOffset_)) {
        auto itemTotalSize = GetEndPosition() - currentStartPos + contentEndOffset_ + contentStartOffset_;
        bool overBottom = (GetEndIndex() == totalItemCount_ - 1) && (LessNotEqual(itemTotalSize, contentMainSize_));
        if (overBottom && !mainSizeIsDefined_ && GreatNotEqual(contentMainSize_, itemTotalSize)) {
            if (overScrollFeature_ && !NearZero(prevContentMainSize_)) {
                currentOffset_ += contentMainSize_ - prevContentMainSize_;
            }
            contentMainSize_ = itemTotalSize;
        }
        if (!canOverScroll_ || jumpIndex_.has_value()) {
            currentOffset_ = currentStartPos - contentStartOffset_;
        }
        endMainPos_ = currentStartPos - contentStartOffset_ + contentMainSize_;
        startMainPos_ = currentStartPos - contentStartOffset_;
        if (Positive(currentOffset_) && itemPosition_.rbegin()->second.isGroup) {
            AdjustPostionForListItemGroup(layoutWrapper, axis_, GetEndIndex(), false);
        }
    }

    if (overScrollFeature_) {
        return;
    }

    // Mark inactive in wrapper.
    std::list<int32_t> removeIndexes;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(pos->first) : 0.0f;
        // Don't recycle When the tail item is Visibility.None.
        if (LessNotEqual(pos->second.startPos + chainOffset, endMainPos_) ||
            LessOrEqual(pos->second.endPos + chainOffset, endMainPos_)) {
            if (pos->second.isGroup) {
                CheckListItemGroupRecycle(layoutWrapper, pos->first, pos->second.endPos + chainOffset, false);
            }
            break;
        }
        layoutWrapper->RemoveChildInRenderTree(pos->first);
        removeIndexes.emplace_back(pos->first);
    }
    for (const auto& index : removeIndexes) {
        itemPosition_.erase(index);
    }
}

void ListLayoutAlgorithm::FixPredictSnapOffset(const RefPtr<ListLayoutProperty>& listLayoutProperty)
{
    if (!predictSnapOffset_.has_value()) {
        return;
    }
    auto scrollSnapAlign = listLayoutProperty->GetScrollSnapAlign().value_or(V2::ScrollSnapAlign::NONE);
    if ((scrollSnapAlign != V2::ScrollSnapAlign::START) && (scrollSnapAlign != V2::ScrollSnapAlign::CENTER) &&
        (scrollSnapAlign != V2::ScrollSnapAlign::END)) {
        predictSnapOffset_.reset();
        predictSnapEndPos_.reset();
        return;
    }

    auto predictEndPos = totalOffset_ - predictSnapOffset_.value();
    int32_t endIndex = FindPredictSnapEndIndexInItemPositions(predictEndPos, scrollSnapAlign);
    if (endIndex != -1) {
        predictEndPos = CalculatePredictSnapEndPositionByIndex(endIndex, scrollSnapAlign);
        predictSnapOffset_ = totalOffset_ - predictEndPos + currentOffset_;
        predictSnapEndPos_.reset();
    } else {
        if (IsUniformHeightProbably()) {
            auto scrollSnapAlign = listLayoutProperty->GetScrollSnapAlign().value_or(V2::ScrollSnapAlign::NONE);
            if (scrollSnapAlign == V2::ScrollSnapAlign::START) {
                FixPredictSnapOffsetAlignStart();
            } else if (scrollSnapAlign == V2::ScrollSnapAlign::CENTER) {
                FixPredictSnapOffsetAlignCenter();
            } else if (scrollSnapAlign == V2::ScrollSnapAlign::END) {
                FixPredictSnapOffsetAlignEnd();
            }
        } else {
            predictSnapEndPos_ = predictEndPos;
        }
    }

    return;
}

bool ListLayoutAlgorithm::IsScrollSnapAlignCenter(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(listLayoutProperty, false);
    auto scrollSnapAlign = listLayoutProperty->GetScrollSnapAlign().value_or(V2::ScrollSnapAlign::NONE);
    if (scrollSnapAlign == V2::ScrollSnapAlign::CENTER) {
        return true;
    }

    return false;
}

void ListLayoutAlgorithm::FixPredictSnapOffsetAlignStart()
{
    if (itemPosition_.empty()) {
        return;
    }
    auto predictEndPos = totalOffset_ - predictSnapOffset_.value();
    auto itemHeight = itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos + spaceWidth_;
    float startPos = contentStartOffset_;
    float endPos = contentMainSize_ - contentEndOffset_;

    if (LessNotEqual(predictEndPos, -startPos)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = -startPos;
    } else if (GreatNotEqual(predictEndPos, itemHeight * GetMaxListItemIndex() + spaceWidth_)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = itemHeight * totalItemCount_ - spaceWidth_ - endPos;
    } else {
        int32_t index;
        for (index = 0; index <= GetMaxListItemIndex(); index++) {
            if (std::abs(predictEndPos - index * itemHeight) < itemHeight / 2.0f) {
                break;
            }
        }
        predictEndPos = index * itemHeight - startPos;
        if (LessNotEqual(predictEndPos, -startPos)) {
            predictEndPos = -startPos;
        } else if (GreatNotEqual(predictEndPos, itemHeight * GetMaxListItemIndex() + spaceWidth_)) {
            predictEndPos = itemHeight * totalItemCount_ - spaceWidth_ - endPos;
        }
    }

    predictSnapOffset_ = totalOffset_ - predictEndPos;
    predictSnapEndPos_ = predictEndPos;
}

void ListLayoutAlgorithm::FixPredictSnapOffsetAlignCenter()
{
    if (itemPosition_.empty()) {
        return;
    }
    auto predictEndPos = totalOffset_ - predictSnapOffset_.value();
    auto itemHeight = itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos + spaceWidth_;

    if (LessNotEqual(predictEndPos, itemHeight / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = itemHeight / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f;
    } else if (GreatNotEqual(
        predictEndPos + contentMainSize_ / 2.0f, itemHeight * totalItemCount_ - itemHeight / 2.0f)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = itemHeight * totalItemCount_ - itemHeight / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f;
    } else {
        int32_t index;
        for (index = 0; index <= GetMaxListItemIndex(); index++) {
            if (std::abs(predictEndPos + contentMainSize_ / 2.0f - index * itemHeight - itemHeight / 2.0f) <
                itemHeight / 2.0f) {
                break;
            }
        }
        predictEndPos = index * itemHeight + itemHeight / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f;
        if (LessNotEqual(predictEndPos, itemHeight / 2.0f - contentMainSize_ / 2.0f)) {
            predictEndPos = itemHeight / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f;
        } else if (GreatNotEqual(
            predictEndPos + contentMainSize_ / 2.0f, itemHeight * totalItemCount_ - itemHeight / 2.0f)) {
            predictEndPos =
                itemHeight * totalItemCount_ - itemHeight / 2.0f - contentMainSize_ / 2.0f - spaceWidth_ / 2.0f;
        }
    }

    predictSnapOffset_ = totalOffset_ - predictEndPos;
    predictSnapEndPos_ = predictEndPos;
}

void ListLayoutAlgorithm::FixPredictSnapOffsetAlignEnd()
{
    if (itemPosition_.empty()) {
        return;
    }
    auto predictEndPos = totalOffset_ - predictSnapOffset_.value();
    auto itemHeight = itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos + spaceWidth_;
    float startPos = contentStartOffset_;
    float endPos = contentMainSize_ - contentEndOffset_;

    if (LessNotEqual(predictEndPos, -startPos)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = -startPos;
    } else if (GreatNotEqual(predictEndPos, itemHeight * GetMaxListItemIndex() + spaceWidth_)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = itemHeight * totalItemCount_ - spaceWidth_ - endPos;
    } else {
        int32_t index;
        for (index = 0; index <= GetMaxListItemIndex(); index++) {
            if (std::abs(predictEndPos + endPos - index * itemHeight) < itemHeight / 2.0f) {
                break;
            }
        }
        predictEndPos = index * itemHeight - endPos - spaceWidth_;
        if (LessNotEqual(predictEndPos, -startPos)) {
            predictEndPos = -startPos;
        } else if (GreatNotEqual(predictEndPos, itemHeight * GetMaxListItemIndex() + spaceWidth_)) {
            predictEndPos = itemHeight * totalItemCount_ - spaceWidth_ - endPos;
        }
    }

    predictSnapOffset_ = totalOffset_ - predictEndPos;
    predictSnapEndPos_ = predictEndPos;
}

void ListLayoutAlgorithm::LayoutItem(RefPtr<LayoutWrapper>& wrapper, int32_t index, const ListItemInfo& pos,
    int32_t& startIndex, float crossSize)
{
    CHECK_NULL_VOID(wrapper);
    auto offset = paddingOffset_;
    float childCrossSize = GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    float crossOffset = 0.0f;
    if (GetLanes() > 1) {
        int32_t laneIndex = 0;
        if (pos.isGroup) {
            startIndex = index + 1;
        } else {
            laneIndex = (index - startIndex) % GetLanes();
        }

        float laneGutter = GetLaneGutter();
        crossOffset = CalculateLaneCrossOffset(crossSize, childCrossSize * GetLanes());
        crossOffset += ((crossSize + laneGutter) / GetLanes()) * laneIndex;
    } else {
        crossOffset = CalculateLaneCrossOffset(crossSize, childCrossSize);
    }
    auto chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(index) : 0.0f;
    if (axis_ == Axis::VERTICAL) {
        offset = offset + OffsetF(crossOffset, pos.startPos + chainOffset);
    } else {
        offset = offset + OffsetF(pos.startPos + chainOffset, crossOffset);
    }
    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    SetListItemIndex(wrapper, index);
}

void ListLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);
    auto axis_ = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    paddingOffset_ = padding.Offset();
    float crossSize = GetCrossAxisSize(size, axis_);
    totalItemCount_ = layoutWrapper->GetTotalChildCount();
    listItemAlign_ = listLayoutProperty->GetListItemAlign().value_or(V2::ListItemAlign::START);
    int32_t startIndex = GetStartIndex();

    totalOffset_ += currentOffset_;
    FixPredictSnapOffset(listLayoutProperty);
    // layout items.
    for (auto& pos : itemPosition_) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos.first);
        if (!wrapper) {
            continue;
        }
        pos.second.startPos -= currentOffset_;
        pos.second.endPos -= currentOffset_;
        LayoutItem(wrapper, pos.first, pos.second, startIndex, crossSize);
        wrapper->Layout();
    }
    auto cacheCount = listLayoutProperty->GetCachedCountValue(1);
    if (!itemPosition_.empty() && cacheCount > 0) {
        auto items = LayoutCachedItem(layoutWrapper, cacheCount);
        if (!items.empty()) {
            PostIdleTask(layoutWrapper->GetHostNode(), { items, childLayoutConstraint_ });
        } else {
            auto host = layoutWrapper->GetHostNode();
            CHECK_NULL_VOID(host);
            auto pattern = host->GetPattern<ListPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetPredictLayoutParam(std::nullopt);
        }
    }
}

float ListLayoutAlgorithm::CalculateLaneCrossOffset(float crossSize, float childCrossSize)
{
    float delta = crossSize - GetLaneGutter() - childCrossSize;
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
            return 0.0f;
    }
}

void ListLayoutAlgorithm::OnSurfaceChanged(LayoutWrapper* layoutWrapper)
{
    if (GreatOrEqual(contentMainSize_, prevContentMainSize_)) {
        return;
    }
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    // textField not in List
    if (!focusHub->IsCurrentFocus()) {
        return;
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    // only when textField is onFocus
    auto textField = textFieldManager->GetOnFocusTextField().Upgrade();
    CHECK_NULL_VOID(textField);
    auto textFieldHost = textField->GetHost();
    CHECK_NULL_VOID(textFieldHost);
    auto position = textFieldHost->GetTransformRelativeOffset().GetY() + textField->GetHostFrameSize()->Height();
    auto globalOffset = host->GetTransformRelativeOffset();
    auto offset = contentMainSize_ + globalOffset.GetY() - position;
    if (LessOrEqual(offset, 0.0)) {
        // negative offset to scroll down
        currentDelta_ -= static_cast<float>(offset);
    }
}

void ListLayoutAlgorithm::SetListItemGroupParam(const RefPtr<LayoutWrapper>& layoutWrapper, int32_t index,
    float referencePos, bool forwardLayout, const RefPtr<ListLayoutProperty>& layoutProperty, bool groupNeedAllLayout)
{
    auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm(true);
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(itemGroup);
    if (jumpIndexInGroup_.has_value() && scrollAlign_ == ScrollAlign::CENTER) {
        referencePos = (startMainPos_ + endMainPos_) / 2; // 2:average
    }
    if (jumpIndex_) {
        auto wrapper = layoutWrapper;
        itemGroup->ClearItemPosition(&(*wrapper));
    }
    itemGroup->SetListMainSize(startMainPos_, endMainPos_, referencePos, forwardLayout);
    itemGroup->SetListLayoutProperty(layoutProperty);
    itemGroup->SetContentOffset(contentStartOffset_, contentEndOffset_);
    if (jumpIndex_.has_value() && (!jumpIndexInGroup_.has_value())) {
        if (forwardLayout&& (scrollAlign_ == ScrollAlign::START ||
            (scrollAlign_ == ScrollAlign::AUTO && scrollAutoType_ == ScrollAutoType::START))) {
            jumpIndexInGroup_ = 0;
        } else if (!forwardLayout && (scrollAlign_ == ScrollAlign::END ||
            (scrollAlign_ == ScrollAlign::AUTO && scrollAutoType_ == ScrollAutoType::END))) {
            jumpIndexInGroup_ = LAST_ITEM;
        }
    }

    if (groupNeedAllLayout || targetIndex_) {
        auto groupItemPosition = itemGroup->GetItemPosition();
        int32_t groupTotalItemCount = layoutWrapper->GetTotalChildCount() - itemGroup->GetItemStartIndex();
        if (groupNeedAllLayout ||
            (targetIndex_ && targetIndex_.value() == index) ||
            (!(forwardLayout && !groupItemPosition.empty() &&
            groupItemPosition.rbegin()->first == groupTotalItemCount - 1) &&
            !(!forwardLayout && !groupItemPosition.empty() &&
            groupItemPosition.begin()->first == 0))) {
            itemGroup->SetNeedAllLayout();
        }
    }

    if (jumpIndexInGroup_.has_value()) {
        itemGroup->SetJumpIndex(jumpIndexInGroup_.value());
        itemGroup->SetScrollAlign(scrollAlign_);
        jumpIndexInGroup_.reset();
    }
    layoutWrapper->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
}

ListItemInfo ListLayoutAlgorithm::GetListItemGroupPosition(const RefPtr<LayoutWrapper>& layoutWrapper, int32_t index)
{
    int32_t id = layoutWrapper->GetHostNode()->GetId();
    ListItemInfo pos = { id, 0, 0, true };
    auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm(true);
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, pos);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(itemGroup, pos);
    auto res = itemGroup->GetItemGroupPosition(index);
    return { id, res.first, res.second, true };
}

float ListLayoutAlgorithm::GetListGroupItemHeight(const RefPtr<LayoutWrapper>& layoutWrapper, int32_t index)
{
    auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm(true);
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, 0.0f);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(itemGroup, 0.0f);
    return itemGroup->GetItemHeight(index);
}

void ListLayoutAlgorithm::SetListItemIndex(const RefPtr<LayoutWrapper>& layoutWrapper, int32_t index)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto listItem = host->GetPattern<ListItemPattern>();
    if (listItem) {
        listItem->SetIndexInList(index);
        return;
    }
    auto listItemGroup = host->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(listItemGroup);
    listItemGroup->SetIndexInList(index);
}

void ListLayoutAlgorithm::CheckListItemGroupRecycle(LayoutWrapper* layoutWrapper, int32_t index,
    float referencePos, bool forwardLayout) const
{
    if (targetIndex_.has_value()) {
        return;
    }
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(wrapper);
    auto algorithmWrapper = wrapper->GetLayoutAlgorithm();
    CHECK_NULL_VOID(algorithmWrapper);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(algorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(itemGroup);
    itemGroup->CheckRecycle(wrapper, startMainPos_, endMainPos_, referencePos, forwardLayout);
}

void ListLayoutAlgorithm::AdjustPostionForListItemGroup(LayoutWrapper* layoutWrapper, Axis axis, int32_t index,
    bool forwardLayout)
{
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(wrapper);
    auto algorithmWrapper = wrapper->GetLayoutAlgorithm();
    CHECK_NULL_VOID(algorithmWrapper);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(algorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(itemGroup);
    if (forwardLayout) {
        itemGroup->SetListMainSize(startMainPos_, endMainPos_, itemPosition_[index].endPos, !forwardLayout);
    } else {
        itemGroup->SetListMainSize(startMainPos_, endMainPos_, itemPosition_[index].startPos, !forwardLayout);
    }
    itemGroup->SetScrollAlign(ScrollAlign::NONE);
    wrapper->Measure(GetGroupLayoutConstraint());
    float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis);
    auto& pos = itemPosition_[index];
    if (forwardLayout) {
        pos.startPos = pos.endPos - mainLen;
    } else {
        pos.endPos = pos.startPos + mainLen;
    }
}

void ListLayoutAlgorithm::OffScreenLayoutDirection()
{
    if (!targetIndex_ || itemPosition_.empty() || (itemPosition_.find(targetIndex_.value()) != itemPosition_.end())) {
        forwardFeature_ = false;
        backwardFeature_ = false;
        return;
    }
    if (GreatNotEqual(targetIndex_.value(), GetEndIndex())) {
        forwardFeature_ = true;
        backwardFeature_ = false;
    } else {
        forwardFeature_ = false;
        backwardFeature_ = true;
    }
}

int32_t ListLayoutAlgorithm::GetMidIndex(LayoutWrapper* layoutWrapper, bool usePreContentMainSize)
{
    float contentSize = usePreContentMainSize ? prevContentMainSize_ : contentMainSize_;
    float midPos = contentSize / 2.0f;
    if (GetStartIndex() == 0 && !IsScrollSnapAlignCenter(layoutWrapper) &&
        GreatNotEqual(GetStartPosition(), startMainPos_)) {
        midPos = GetStartPosition() + contentSize / 2.0f;
    } else if (GetEndIndex() == totalItemCount_ - 1 && !IsScrollSnapAlignCenter(layoutWrapper) &&
        LessNotEqual(GetEndPosition(), endMainPos_) &&
        (GetStartIndex() != 0 || !NearEqual(GetStartPosition(), startMainPos_))) {
        midPos = GetEndPosition() - contentSize / 2.0f;
    }
    for (auto & pos : itemPosition_) {
        if (midPos <= pos.second.endPos + spaceWidth_ / 2) { /* 2:half */
            return pos.first;
        }
    }
    return totalItemCount_ - 1;
}

void ListLayoutAlgorithm::SyncGeometry(RefPtr<LayoutWrapper>& wrapper)
{
    CHECK_NULL_VOID(wrapper);
    auto host = wrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    host->ForceSyncGeometryNode();
}

std::list<int32_t> ListLayoutAlgorithm::LayoutCachedItem(LayoutWrapper* layoutWrapper, int32_t cacheCount)
{
    std::list<int32_t> predictBuildList;
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    float crossSize = GetCrossAxisSize(size, axis_);

    auto currIndex = itemPosition_.rbegin()->first + 1;
    auto currPos = itemPosition_.rbegin()->second.endPos + spaceWidth_;
    for (int32_t i = 0; i < cacheCount && currIndex + i < totalItemCount_; i++) {
        int32_t index = currIndex + i;
        auto wrapper = layoutWrapper->GetChildByIndex(index);
        if (!wrapper || wrapper->CheckNeedForceMeasureAndLayout()) {
            predictBuildList.emplace_back(index);
            continue;
        }
        bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        auto childSize = wrapper->GetGeometryNode()->GetMarginFrameSize();
        auto endPos = currPos + GetMainAxisSize(childSize, axis_);
        int32_t id = wrapper->GetHostNode()->GetId();
        ListItemInfo pos = { id, currPos, endPos, isGroup };
        currPos = endPos + spaceWidth_;
        auto startIndex = index;
        LayoutItem(wrapper, index, pos, startIndex, crossSize);
        SyncGeometry(wrapper);
        wrapper->SetActive(false);
    }

    currIndex = itemPosition_.begin()->first - 1;
    currPos = itemPosition_.begin()->second.startPos - spaceWidth_;
    for (int32_t i = 0; i < cacheCount && currIndex - i >= 0; i++) {
        int32_t index = currIndex - i;
        auto wrapper = layoutWrapper->GetChildByIndex(index);
        if (!wrapper || wrapper->CheckNeedForceMeasureAndLayout()) {
            predictBuildList.emplace_back(index);
            continue;
        }
        bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        auto childSize = wrapper->GetGeometryNode()->GetMarginFrameSize();
        auto startPos = currPos - GetMainAxisSize(childSize, axis_);
        int32_t id = wrapper->GetHostNode()->GetId();
        ListItemInfo pos = { id, startPos, currPos, isGroup };
        currPos = startPos - spaceWidth_;
        auto startIndex = index;
        LayoutItem(wrapper, index, pos, startIndex, crossSize);
        SyncGeometry(wrapper);
        wrapper->SetActive(false);
    }
    return predictBuildList;
}

bool ListLayoutAlgorithm::PredictBuildItem(RefPtr<LayoutWrapper> wrapper, const LayoutConstraintF& constraint)
{
    CHECK_NULL_RETURN(wrapper, false);
    wrapper->SetActive(false);
    bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (!isGroup) {
        auto frameNode = wrapper->GetHostNode();
        CHECK_NULL_RETURN(frameNode, false);
        frameNode->GetGeometryNode()->SetParentLayoutConstraint(constraint);
        FrameNode::ProcessOffscreenNode(frameNode);
        return true;
    }
    return false;
}

void ListLayoutAlgorithm::PostIdleTask(RefPtr<FrameNode> frameNode, const ListPredictLayoutParam& param)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetPredictLayoutParam()) {
        pattern->SetPredictLayoutParam(param);
        return;
    }
    pattern->SetPredictLayoutParam(param);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask([weak = WeakClaim(RawPtr(frameNode))](int64_t deadline, bool canUseLongPredictTask) {
        ACE_SCOPED_TRACE("List predict");
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<ListPattern>();
        CHECK_NULL_VOID(pattern);
        if (!pattern->GetPredictLayoutParam().has_value()) {
            return;
        }
        bool needMarkDirty = false;
        auto param = pattern->GetPredictLayoutParam().value();
        for (auto it = param.items.begin(); it != param.items.end();) {
            if (GetSysTimestamp() > deadline) {
                break;
            }
            auto wrapper = frameNode->GetOrCreateChildByIndex(*it, false);
            if (wrapper && wrapper->GetHostNode() && !wrapper->GetHostNode()->RenderCustomChild(deadline)) {
                break;
            }
            needMarkDirty |= PredictBuildItem(wrapper, param.layoutConstraint);
            param.items.erase(it++);
        }
        if (needMarkDirty) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        }
        pattern->SetPredictLayoutParam(std::nullopt);
        if (!param.items.empty()) {
            ListLayoutAlgorithm::PostIdleTask(frameNode, param);
            pattern->SetPredictLayoutParam(param);
        }
    });
}

float ListLayoutAlgorithm::GetStopOnScreenOffset(V2::ScrollSnapAlign scrollSnapAlign)
{
    float stopOnScreen = 0;
    if (scrollSnapAlign == V2::ScrollSnapAlign::START) {
        stopOnScreen = contentStartOffset_;
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::CENTER) {
        stopOnScreen = contentMainSize_ / 2.0f;
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::END) {
        stopOnScreen = contentMainSize_ - contentEndOffset_;
    }
    return stopOnScreen;
}

int32_t ListLayoutAlgorithm::FindPredictSnapEndIndexInItemPositions(
    float predictEndPos, V2::ScrollSnapAlign scrollSnapAlign)
{
    int32_t endIndex = -1;
    float stopOnScreen = GetStopOnScreenOffset(scrollSnapAlign);
    float startPos = 0.0f;
    float endPos = 0.0f;
    float itemHeight = 0.0f;

    if (scrollSnapAlign == V2::ScrollSnapAlign::START) {
        for (const auto& positionInfo : itemPosition_) {
            startPos = totalOffset_ + positionInfo.second.startPos - itemHeight / 2.0f;
            itemHeight = positionInfo.second.endPos - positionInfo.second.startPos + spaceWidth_;
            endPos = totalOffset_ + positionInfo.second.startPos + itemHeight / 2.0f;
            if (GreatOrEqual(predictEndPos + stopOnScreen, startPos) &&
                LessNotEqual(predictEndPos + stopOnScreen, endPos)) {
                endIndex = positionInfo.first;
                break;
            }
        }
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::CENTER) {
        for (const auto& positionInfo : itemPosition_) {
            startPos = totalOffset_ + positionInfo.second.startPos - spaceWidth_ / 2.0f;
            endPos = totalOffset_ + positionInfo.second.endPos + spaceWidth_ / 2.0f;
            if (GreatOrEqual(predictEndPos + stopOnScreen, startPos) &&
                LessNotEqual(predictEndPos + stopOnScreen, endPos)) {
                endIndex = positionInfo.first;
                break;
            }
        }
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::END) {
        for (const auto& positionInfo : itemPosition_) {
            startPos = totalOffset_ + positionInfo.second.endPos - itemHeight / 2.0f;
            itemHeight = positionInfo.second.endPos - positionInfo.second.startPos + spaceWidth_;
            endPos = totalOffset_ + positionInfo.second.endPos + itemHeight / 2.0f;
            if (GreatOrEqual(predictEndPos + stopOnScreen, startPos) &&
                LessNotEqual(predictEndPos + stopOnScreen, endPos)) {
                endIndex = positionInfo.first;
                break;
            }
        }
    }
    return endIndex;
}

bool ListLayoutAlgorithm::IsUniformHeightProbably()
{
    bool isUniformHeightProbably = true;
    float itemHeight = 0.0f;
    float currentItemHeight = 0.0f;
    for (const auto& positionInfo : itemPosition_) {
        currentItemHeight = positionInfo.second.endPos - positionInfo.second.startPos;
        if (NearZero(itemHeight)) {
            itemHeight = currentItemHeight;
        } else if (!NearEqual(currentItemHeight, itemHeight)) {
            isUniformHeightProbably = false;
            break;
        }
    }
    return isUniformHeightProbably;
}

float ListLayoutAlgorithm::CalculatePredictSnapEndPositionByIndex(uint32_t index, V2::ScrollSnapAlign scrollSnapAlign)
{
    float predictSnapEndPos = 0;
    if (scrollSnapAlign == V2::ScrollSnapAlign::START) {
        predictSnapEndPos = totalOffset_ + itemPosition_[index].startPos - contentStartOffset_;
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::CENTER) {
        float itemHeight = itemPosition_[index].endPos - itemPosition_[index].startPos;
        predictSnapEndPos = totalOffset_ + itemPosition_[index].startPos + itemHeight / 2.0f - contentMainSize_ / 2.0f;
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::END) {
        predictSnapEndPos = totalOffset_ + itemPosition_[index].endPos - contentMainSize_ + contentEndOffset_;
    }
    return predictSnapEndPos;
}

void ListLayoutAlgorithm::OnItemPositionAddOrUpdate(LayoutWrapper* layoutWrapper, uint32_t index)
{
    if (!predictSnapEndPos_.has_value()) {
        return;
    }
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);
    auto scrollSnapAlign = listLayoutProperty->GetScrollSnapAlign().value_or(V2::ScrollSnapAlign::NONE);
    if ((scrollSnapAlign != V2::ScrollSnapAlign::START) && (scrollSnapAlign != V2::ScrollSnapAlign::CENTER) &&
        (scrollSnapAlign != V2::ScrollSnapAlign::END)) {
        return;
    }

    float predictSnapEndPos = predictSnapEndPos_.value();
    float stopOnScreen = GetStopOnScreenOffset(scrollSnapAlign);
    float startPos = totalOffset_ + itemPosition_[index].startPos - spaceWidth_ / 2.0f;
    float endPos = totalOffset_ + itemPosition_[index].endPos + spaceWidth_ / 2.0f;
    if (GreatOrEqual(predictSnapEndPos + stopOnScreen, startPos) &&
        LessNotEqual(predictSnapEndPos + stopOnScreen, endPos)) {
        predictSnapEndPos = CalculatePredictSnapEndPositionByIndex(index, scrollSnapAlign);
    } else {
        return;
    }

    if (!NearEqual(predictSnapEndPos, predictSnapEndPos_.value())) {
        predictSnapEndPos_ = predictSnapEndPos;
    }
}
} // namespace OHOS::Ace::NG
