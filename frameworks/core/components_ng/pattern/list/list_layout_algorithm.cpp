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

#include <utility>

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
#include "core/components_ng/pattern/text/text_base.h"
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
constexpr Dimension RESERVE_BOTTOM_HEIGHT = 24.0_vp;
constexpr float SCROLL_SNAP_VELOCITY_TH = 780;
} // namespace

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

void ListLayoutAlgorithm::ReviseSpace(const RefPtr<ListLayoutProperty>& listLayoutProperty)
{
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
}

void ListLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);

    axis_ = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    // Pre-recycle
    ScrollableUtils::RecycleItemsOutOfBoundary(axis_, -currentDelta_, GetStartIndex(), GetEndIndex(), layoutWrapper);

    const auto& layoutConstraint = listLayoutProperty->GetLayoutConstraint().value();

    // calculate idealSize and set FrameSize
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
    auto&& safeAreaOpts = listLayoutProperty->GetSafeAreaExpandOpts();
    expandSafeArea_ = safeAreaOpts && safeAreaOpts->Expansive();

    auto contentIdealSize = CreateIdealSize(
        contentConstraint, axis_, listLayoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS));

    const auto& padding = listLayoutProperty->CreatePaddingAndBorder();
    paddingBeforeContent_ = axis_ == Axis::HORIZONTAL ? padding.left.value_or(0) : padding.top.value_or(0);
    paddingAfterContent_ = axis_ == Axis::HORIZONTAL ? padding.right.value_or(0) : padding.bottom.value_or(0);
    contentMainSize_ = 0.0f;
    totalItemCount_ = layoutWrapper->GetTotalChildCount();
    scrollSnapAlign_ = listLayoutProperty->GetScrollSnapAlign().value_or(V2::ScrollSnapAlign::NONE);
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
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            contentMainSize_ = std::max(contentMainSize_, GetMainAxisSize(contentConstraint.minSize, axis_));
        }
    } else {
        contentMainSize_ = GetMainAxisSize(contentIdealSize.ConvertToSizeT(), axis_);
        mainSizeIsDefined_ = true;
    }
    if (GreatOrEqual(contentStartOffset_ + contentEndOffset_, contentMainSize_) ||
        IsScrollSnapAlignCenter(layoutWrapper)) {
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
        ReviseSpace(listLayoutProperty);
        CheckJumpToIndex();
        currentOffset_ = currentDelta_;
        startMainPos_ = currentOffset_;
        endMainPos_ = currentOffset_ + contentMainSize_;
        CalculateLanes(listLayoutProperty, layoutConstraint, contentIdealSize.CrossSize(axis_), axis_);
        listItemAlign_ = listLayoutProperty->GetListItemAlign().value_or(V2::ListItemAlign::START);
        // calculate child layout constraint.
        UpdateListItemConstraint(axis_, contentIdealSize, childLayoutConstraint_);
        if (posMap_) {
            posMap_->UpdatePosMap(layoutWrapper, GetLanes(), spaceWidth_, childrenSize_);
        }
        MeasureList(layoutWrapper);
    } else {
        itemPosition_.clear();
        if (posMap_) {
            posMap_->ClearPosMap();
        }
    }

    // In the secondary layout scenario, the previous contentMainSize_ is used as the next prevContentMainSize_.
    prevContentMainSize_ = contentMainSize_;
    
    auto crossSize = contentIdealSize.CrossSize(axis_);
    if (crossSize.has_value() && GreaterOrEqualToInfinity(crossSize.value())) {
        contentIdealSize.SetCrossSize(GetChildMaxCrossSize(layoutWrapper, axis_), axis_);
        crossMatchChild_ = true;
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && !mainSizeIsDefined_) {
        contentMainSize_ = std::max(contentMainSize_, GetMainAxisSize(contentConstraint.minSize, axis_));
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

void ListLayoutAlgorithm::SetCacheCount(LayoutWrapper* layoutWrapper, int32_t cacheCount)
{
    layoutWrapper->SetCacheCount(cacheCount);
}

void ListLayoutAlgorithm::SetActiveChildRange(LayoutWrapper* layoutWrapper,
    int32_t cacheStart, int32_t cacheEnd, bool show)
{
    if (itemPosition_.empty()) {
        layoutWrapper->SetActiveChildRange(-1, -1);
        return;
    }
    layoutWrapper->SetActiveChildRange(
        itemPosition_.begin()->first, itemPosition_.rbegin()->first, cacheStart, cacheEnd, show);
}

bool ListLayoutAlgorithm::CheckNeedMeasure(const RefPtr<LayoutWrapper>& layoutWrapper) const
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

float ListLayoutAlgorithm::GetChildMaxCrossSize(LayoutWrapper* layoutWrapper, Axis axis) const
{
    if (GetItemPosition().empty()) {
        return 0.0f;
    }
    float maxCrossSize = 0.0f;
    float crossSize = -laneGutter_;
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
            crossSize = crossSize + getGeometryNode->GetMarginFrameSize().CrossSize(axis) + laneGutter_;
        } else {
            crossSize = getGeometryNode->GetMarginFrameSize().CrossSize(axis);
        }
        prevPos = pos.second.startPos;
        maxCrossSize = std::max(crossSize, maxCrossSize);
    }
    return maxCrossSize;
}

void ListLayoutAlgorithm::ClearAllItemPosition(LayoutWrapper* layoutWrapper)
{
    for (auto& pos : itemPosition_) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos.first);
        if (!wrapper) {
            continue;
        }
        auto node = wrapper->GetHostNode();
        if (!node) {
            continue;
        }
        auto listItemGroup = node->GetPattern<ListItemGroupPattern>();
        if (!listItemGroup) {
            continue;
        }
        listItemGroup->ClearItemPosition();
        listItemGroup->ClearCachedItemPosition();
    }
    itemPosition_.clear();
}

float ListLayoutAlgorithm::GetStartPositionWithChainOffset() const
{
    if (itemPosition_.empty()) {
        return 0.0f;
    }
    int32_t startIndex = itemPosition_.begin()->first;
    float chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(startIndex) : 0.0f;
    if (startIndex == 0) {
        return itemPosition_.begin()->second.startPos + chainOffset;
    }
    return itemPosition_.begin()->second.startPos + chainOffset - spaceWidth_;
}

void ListLayoutAlgorithm::BeginLayoutForward(float startPos, LayoutWrapper* layoutWrapper)
{
    jumpIndex_ = GetLanesFloor(layoutWrapper, jumpIndex_.value());
    LayoutForward(layoutWrapper, jumpIndex_.value(), startPos);
    if ((GetStartIndex() > 0) && GreatNotEqual(GetStartPosition(), startMainPos_)) {
        LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
        if ((GetEndIndex() < totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
            LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
        }
    }
}

void ListLayoutAlgorithm::BeginLayoutBackward(float startPos, LayoutWrapper* layoutWrapper)
{
    jumpIndex_ = GetLanesCeil(layoutWrapper, jumpIndex_.value());
    LayoutBackward(layoutWrapper, jumpIndex_.value(), startPos);
    if (LessOrEqual(GetEndIndex(), totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
        LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
        if ((GetStartIndex() > 0) && GreatNotEqual(GetStartPosition(), startMainPos_)) {
            LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
        }
    }
}

void ListLayoutAlgorithm::HandleJumpAuto(LayoutWrapper* layoutWrapper, int32_t startIndex, int32_t endIndex)
{
    int32_t jumpIndex = jumpIndex_.has_value() ? jumpIndex_.value() : targetIndex_.value();
    jumpIndex = GetLanesFloor(layoutWrapper, jumpIndex);
    startIndex = GetLanesFloor(layoutWrapper, startIndex);
    endIndex = GetLanesFloor(layoutWrapper, endIndex);
    float contentStartOffset = IsScrollSnapAlignCenter(layoutWrapper) ? 0.0f : contentStartOffset_;
    float contentEndOffset = IsScrollSnapAlignCenter(layoutWrapper) ? 0.0f : contentEndOffset_;
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(jumpIndex);
    CHECK_NULL_VOID(wrapper);
    bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup && jumpIndexInGroup_) {
        if (scrollAutoType_ == ScrollAutoType::START) {
            scrollAlign_ = ScrollAlign::START;
            HandleJumpStart(layoutWrapper);
        } else if (scrollAutoType_ == ScrollAutoType::END) {
            scrollAlign_ = ScrollAlign::END;
            HandleJumpEnd(layoutWrapper);
        }
    } else if (jumpIndex <= startIndex) {
        float mainLen = childrenSize_ ?
            GetChildHeight(layoutWrapper, jumpIndex) : MeasureAndGetChildHeight(layoutWrapper, jumpIndex, false);
        if (GreatNotEqual(contentMainSize_ - contentStartOffset - contentEndOffset, mainLen)) {
            scrollAutoType_ = ScrollAutoType::START;
            if (jumpIndex_.has_value()) {
                BeginLayoutForward(contentStartOffset, layoutWrapper);
            }
        } else {
            scrollAutoType_ = ScrollAutoType::END;
            if (jumpIndex_.has_value()) {
                BeginLayoutBackward(contentMainSize_ - contentEndOffset, layoutWrapper);
            }
        }
    } else if (jumpIndex >= endIndex) {
        float mainLen = childrenSize_ ?
            GetChildHeight(layoutWrapper, jumpIndex) : MeasureAndGetChildHeight(layoutWrapper, jumpIndex, false);
        if (GreatOrEqual(mainLen, contentMainSize_ - contentStartOffset - contentEndOffset)) {
            scrollAutoType_ = ScrollAutoType::START;
            if (jumpIndex_.has_value()) {
                BeginLayoutForward(contentStartOffset, layoutWrapper);
            }
        } else {
            scrollAutoType_ = ScrollAutoType::END;
            if (jumpIndex_.has_value()) {
                BeginLayoutBackward(contentMainSize_ - contentEndOffset, layoutWrapper);
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
        float mainLen = childrenSize_ ?
            GetChildHeight(layoutWrapper, index) : MeasureAndGetChildHeight(layoutWrapper, index);
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
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(jumpIndex_.value());
    bool isGroup = wrapper && wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup && jumpIndexInGroup_.has_value()) {
        int32_t indexInGroup = jumpIndexInGroup_.value();
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, jumpIndex_.value(), 0.0f, true, listLayoutProperty, false);
        wrapper->Measure(GetGroupLayoutConstraint());
        itemPosition_[jumpIndex_.value()] = GetListItemGroupPosition(wrapper, indexInGroup);
        if (LessNotEqual(GetEndPosition(), endMainPos_)) {
            LayoutForward(layoutWrapper, jumpIndex_.value() + 1, GetEndPosition());
        }
        if (GetStartIndex() > 0 && GreatNotEqual(GetStartPosition(), startMainPos_)) {
            LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
        }
    } else {
        BeginLayoutForward(IsScrollSnapAlignCenter(layoutWrapper) ? 0.0f : contentStartOffset_, layoutWrapper);
    }
}

void ListLayoutAlgorithm::HandleJumpEnd(LayoutWrapper* layoutWrapper)
{
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(jumpIndex_.value());
    bool isGroup = wrapper && wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup && jumpIndexInGroup_.has_value()) {
        int32_t indexInGroup = jumpIndexInGroup_.value();
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, jumpIndex_.value(), contentMainSize_, true, listLayoutProperty, false);
        wrapper->Measure(GetGroupLayoutConstraint());
        itemPosition_[jumpIndex_.value()] = GetListItemGroupPosition(wrapper, indexInGroup);
        if (GreatNotEqual(GetStartPosition(), startMainPos_)) {
            LayoutBackward(layoutWrapper, jumpIndex_.value() - 1, GetStartPosition());
        }
        if (GetEndIndex() <= totalItemCount_ -1 && LessNotEqual(GetEndPosition(), endMainPos_)) {
            LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
        }
    } else {
        BeginLayoutBackward(contentMainSize_ - (IsScrollSnapAlignCenter(layoutWrapper) ? 0.0f : contentEndOffset_),
            layoutWrapper);
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
    if ((tempJumpIndex == tempStartIndex) &&
        GreatOrEqual(startPos, IsScrollSnapAlignCenter(layoutWrapper) ? 0.0f : contentStartOffset_)) {
        return true;
    }
    if ((tempJumpIndex == tempEndIndex) &&
        LessOrEqual(endPos, contentMainSize_ - (IsScrollSnapAlignCenter(layoutWrapper) ? 0.0f : contentEndOffset_))) {
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
            auto topPos = jumpIndexStartPos + it->second.startPos -
                (IsScrollSnapAlignCenter(layoutWrapper) ? 0.0f : contentStartOffset_);
            auto bottomPos = jumpIndexStartPos + it->second.endPos +
                (IsScrollSnapAlignCenter(layoutWrapper) ? 0.0f : contentEndOffset_);
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
    }
    if (stickyStyle == V2::StickyStyle::BOTH || stickyStyle == V2::StickyStyle::FOOTER) {
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

float ListLayoutAlgorithm::MeasureAndGetChildHeight(LayoutWrapper* layoutWrapper, int32_t childIndex,
    bool groupLayoutAll)
{
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(childIndex);
    CHECK_NULL_RETURN(wrapper, 0.0f);
    bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup) {
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        // true: layout forward, 0.0f: layout start position.
        SetListItemGroupParam(wrapper, childIndex, 0.0f, true, listLayoutProperty, groupLayoutAll);
    }
    wrapper->Measure(childLayoutConstraint_);
    float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    return mainLen;
}

void ListLayoutAlgorithm::CheckJumpToIndex()
{
    if (jumpIndex_.has_value() || !isNeedCheckOffset_ || childrenSize_) {
        return;
    }
    if (LessOrEqual(std::abs(currentDelta_), contentMainSize_ * 2.0f) || itemPosition_.empty()) {
        return;
    }
    for (const auto& pos : itemPosition_) {
        if (pos.second.isGroup) {
            if (pos.second.groupInfo) {
                groupItemAverageHeight_ = pos.second.groupInfo.value().averageHeight;
            }
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
            contentStartOffset_ = std::max((contentMainSize_ - itemHeight) / 2.0f, 0.0f);
        }
        if (GetEndIndex() == totalItemCount_ - 1) {
            itemHeight = itemPosition_.rbegin()->second.endPos - itemPosition_.rbegin()->second.startPos;
            contentEndOffset_ = std::max((contentMainSize_ - itemHeight) / 2.0f, 0.0f);
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

void ListLayoutAlgorithm::CheckAndMeasureStartItem(LayoutWrapper* layoutWrapper, int32_t startIndex,
    float& startPos, bool isGroup, bool forwardLayout)
{
    if (!isGroup || IsScrollSnapAlignCenter(layoutWrapper) ||
        (forwardLayout && NonNegative(startPos)) || (!forwardLayout && LessOrEqual(startPos, prevContentMainSize_))) {
        return;
    }
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(startIndex);
    CHECK_NULL_VOID(wrapper);
    int32_t id = wrapper->GetHostNode()->GetId();
    isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (!isGroup) {
        return;
    }
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItemGroup:%d", startIndex);
    SetListItemGroupParam(wrapper, startIndex, startPos, forwardLayout, listLayoutProperty, false, true);
    wrapper->Measure(GetGroupLayoutConstraint());
    auto algorithmWrapper = wrapper->GetLayoutAlgorithm();
    CHECK_NULL_VOID(algorithmWrapper);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(algorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(itemGroup);
    startPos = itemGroup->GetRefPos();
    ListItemInfo itemInfo;
    if (forwardLayout) {
        itemInfo = { id, startPos, startPos + childrenSize_->GetChildSize(startIndex), isGroup };
    } else {
        itemInfo = { id, startPos - childrenSize_->GetChildSize(startIndex), startPos, isGroup };
    }
    firstItemInfo_ = std::make_pair(startIndex, itemInfo);
}

void ListLayoutAlgorithm::MeasureList(LayoutWrapper* layoutWrapper)
{
    bool startItemIsGroup = false;
    bool endItemIsGroup = false;
    int32_t startIndex = 0;
    int32_t endIndex = 0;
    int32_t midIndex = 0;
    float midItemMidPos = contentMainSize_ / 2.0f;
    float startPos = contentStartOffset_;
    float endPos = 0.0f;
    float itemTotalSize = 0.0f;
    float jumpIndexStartPos = 0.0f;
    bool needLayoutBackward = false;
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    preStartIndex_ = pattern->GetStartIndex();
    if (jumpIndex_ && scrollAlign_ == ScrollAlign::AUTO) {
        auto it = itemPosition_.find(jumpIndex_.value());
        if (it != itemPosition_.end()) {
            jumpIndexStartPos = it->second.startPos;
        }
    }

    if (jumpIndex_) {
        if (!CheckJumpValid(layoutWrapper)) {
            jumpIndex_.reset();
            jumpIndexInGroup_.reset();
        } else {
            if (jumpIndex_ && scrollAlign_ != ScrollAlign::AUTO) {
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
        startItemIsGroup = itemPosition_.begin()->second.isGroup;
        endItemIsGroup = itemPosition_.rbegin()->second.isGroup;
        startPos = itemPosition_.begin()->second.startPos;
        endPos = itemPosition_.rbegin()->second.endPos;
        itemTotalSize = GetEndPosition() - GetStartPosition();
        startIndex = std::min(GetStartIndex(), totalItemCount_ - 1);
        endIndex = std::min(GetEndIndex(), totalItemCount_ - 1);
        if (GetStartIndex() > totalItemCount_ - 1 && !jumpIndex_.has_value()) {
            jumpIndex_ = totalItemCount_ - 1;
            scrollAlign_ = ScrollAlign::END;
        }
        UpdateSnapCenterContentOffset(layoutWrapper);
        auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(listLayoutProperty);
        auto scrollSnapAlign = listLayoutProperty->GetScrollSnapAlign().value_or(V2::ScrollSnapAlign::NONE);
        if (IsScrollSnapAlignCenter(layoutWrapper)) {
            midIndex = GetMidIndex(layoutWrapper, true);
            midItemMidPos = (itemPosition_[midIndex].startPos + itemPosition_[midIndex].endPos) / 2.0f -
                prevContentMainSize_ / 2.0f + contentMainSize_ / 2.0f;
            midIndex = std::min(midIndex, totalItemCount_ - 1);
        } else if (scrollSnapAlign == V2::ScrollSnapAlign::START && pattern->GetScrollState() == ScrollState::IDLE) {
            auto res = GetSnapStartIndexAndPos();
            startIndex = res.first;
            startPos = res.second;
        } else if (scrollSnapAlign == V2::ScrollSnapAlign::END && pattern->GetScrollState() == ScrollState::IDLE) {
            auto res = GetSnapEndIndexAndPos();
            needLayoutBackward = res.first != -1;
            endIndex = needLayoutBackward ? res.first : endIndex;
            endPos = needLayoutBackward ? res.second : endPos;
        }
        OffScreenLayoutDirection(layoutWrapper);
        itemPosition_.clear();
    }
    if (jumpIndex_ && scrollAlign_ == ScrollAlign::AUTO &&
        NoNeedJump(layoutWrapper, startPos, endPos, startIndex, endIndex, jumpIndex_.value(), jumpIndexStartPos)) {
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
                HandleJumpAuto(layoutWrapper, startIndex, endIndex);
                break;
        }
        needEstimateOffset_ = true;
    } else if (targetIndex_.has_value()) {
        auto layoutDirection = LayoutDirectionForTargetIndex(layoutWrapper, preStartIndex_);
        if (layoutDirection == LayoutDirection::BACKWARD) {
            LayoutBackward(layoutWrapper, endIndex, endPos);
            if (GetEndIndex() < (totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
                LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
            }
        } else {
            LayoutForward(layoutWrapper, startIndex, startPos);
            if (GetStartIndex() > 0 && GreatNotEqual(GetStartPosition(), startMainPos_)) {
                LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
            }
        }
    } else {
        jumpIndexInGroup_.reset();
        bool overScrollTop = startIndex == 0 && GreatNotEqual(startPos + GetChainOffset(0), contentStartOffset_);
        float midItemHeight = 0.0f;
        if (IsScrollSnapAlignCenter(layoutWrapper)) {
            midItemHeight = childrenSize_ ?
                GetChildHeight(layoutWrapper, midIndex) : MeasureAndGetChildHeight(layoutWrapper, midIndex);
            startIndex = midIndex;
            endIndex = midIndex;
        }
        if ((NonNegative(currentOffset_) || overScrollFeature_ || (canOverScroll_ &&
            LessOrEqual(itemTotalSize, contentMainSize_ - contentStartOffset_ - contentEndOffset_))) &&
            !needLayoutBackward) {
            startIndex = GetLanesFloor(layoutWrapper, startIndex);
            if (overScrollTop && !canOverScroll_ && !overScrollFeature_) {
                startPos = startMainPos_ + contentStartOffset_;
            }
            if (IsScrollSnapAlignCenter(layoutWrapper)) {
                startPos = midItemMidPos - midItemHeight / 2.0f;
            }
            if (overScrollFeature_ && !overScrollTop && GreatNotEqual(contentMainSize_, prevContentMainSize_) &&
                GreatNotEqual(itemTotalSize, contentMainSize_)) {
                startPos += contentMainSize_ - prevContentMainSize_;
            }
            if (childrenSize_) {
                CheckAndMeasureStartItem(layoutWrapper, startIndex, startPos, startItemIsGroup, true);
                posMap_->OptimizeBeforeMeasure(startIndex, startPos, currentOffset_, contentMainSize_);
            }
            LayoutForward(layoutWrapper, startIndex, startPos);
            if (GetStartIndex() > 0 && GreatNotEqual(GetStartPositionWithChainOffset(), startMainPos_)) {
                LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
            }
        } else {
            endIndex = GetLanesCeil(layoutWrapper, endIndex);
            if (needLayoutBackward) {
                endPos += contentMainSize_ - prevContentMainSize_;
            }
            if (IsScrollSnapAlignCenter(layoutWrapper)) {
                endPos = midItemMidPos + midItemHeight / 2.0f;
            }
            if (childrenSize_) {
                CheckAndMeasureStartItem(layoutWrapper, endIndex, endPos, endItemIsGroup, false);
                posMap_->OptimizeBeforeMeasure(endIndex, endPos, currentOffset_, contentMainSize_);
            }
            LayoutBackward(layoutWrapper, endIndex, endPos);
            if (GetEndIndex() < (totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
                LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
            }
        }
    }
    RecycleGroupItem(layoutWrapper);
}

LayoutDirection ListLayoutAlgorithm::LayoutDirectionForTargetIndex(LayoutWrapper* layoutWrapper, int startIndex)
{
    CHECK_NULL_RETURN(targetIndex_, LayoutDirection::NONE);
    if (startIndex < targetIndex_.value()) {
        return LayoutDirection::FORWARD;
    } else if (startIndex > targetIndex_.value()) {
        return LayoutDirection::BACKWARD;
    } else if (targetIndexInGroup_.has_value()) {
        auto groupWrapper = layoutWrapper->GetOrCreateChildByIndex(targetIndex_.value());
        CHECK_NULL_RETURN(groupWrapper, LayoutDirection::NONE);
        auto groupHost = groupWrapper->GetHostNode();
        CHECK_NULL_RETURN(groupHost, LayoutDirection::NONE);
        auto groupPattern = groupHost->GetPattern<ListItemGroupPattern>();
        CHECK_NULL_RETURN(groupPattern, LayoutDirection::NONE);
        auto startIndexInGroup = groupPattern->GetDisplayStartIndexInGroup();
        auto endIndexInGroup = groupPattern->GetDisplayEndIndexInGroup();
        auto isTargetGroupEmpty = groupPattern->GetItemPosition().empty();
        auto targetGroupPosition = itemPosition_[targetIndex_.value()].startPos;
        if (targetIndexInGroup_.value() < startIndexInGroup || (isTargetGroupEmpty && Negative(targetGroupPosition))) {
            return LayoutDirection::BACKWARD;
        } else if (targetIndexInGroup_.value() > endIndexInGroup ||
                   (isTargetGroupEmpty && !Negative(targetGroupPosition))) {
            return LayoutDirection::FORWARD;
        }
    }
    return LayoutDirection::NONE;
}

void ListLayoutAlgorithm::RecycleGroupItem(LayoutWrapper* layoutWrapper) const
{
    if (scrollSnapAlign_ != V2::ScrollSnapAlign::CENTER || childrenSize_) {
        return;
    }
    auto startChild = itemPosition_.begin();
    auto endChild = itemPosition_.rbegin();
    if (startChild != itemPosition_.end() && startChild->second.isGroup) {
        float chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(startChild->first) : 0.0f;
        CheckListItemGroupRecycle(layoutWrapper, startChild->first, startChild->second.startPos + chainOffset, true);
    }
    if (endChild != itemPosition_.rend() && endChild->second.isGroup) {
        float chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(endChild->first) : 0.0f;
        CheckListItemGroupRecycle(layoutWrapper, endChild->first, endChild->second.endPos + chainOffset, false);
    }
}

void ListLayoutAlgorithm::AdjustStartPosition(const RefPtr<LayoutWrapper>& layoutWrapper, float& startPos)
{
    auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm(true);
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(itemGroup);
    startPos += itemGroup->GetAdjustReferenceDelta();
}

int32_t ListLayoutAlgorithm::LayoutALineForward(LayoutWrapper* layoutWrapper,
    int32_t& currentIndex, float startPos, float& endPos)
{
    if (currentIndex + 1 >= totalItemCount_) {
        return 0;
    }
    if (!firstItemInfo_ || firstItemInfo_.value().first != currentIndex + 1) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex + 1);
        CHECK_NULL_RETURN(wrapper, 0);
        int32_t id = wrapper->GetHostNode()->GetId();
        ++currentIndex;
        bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        if (isGroup) {
            auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItemGroup:%d, %f", currentIndex, startPos);
            SetListItemGroupParam(wrapper, currentIndex, startPos, true, listLayoutProperty, false);
            wrapper->Measure(childLayoutConstraint_);
            if (LessOrEqual(startPos, 0.0f)) {
                AdjustStartPosition(wrapper, startPos);
            }
        } else if (expandSafeArea_ || CheckNeedMeasure(wrapper)) {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d, %f", currentIndex, startPos);
            wrapper->Measure(childLayoutConstraint_);
        }
        float mainLen = childrenSize_ ? childrenSize_->GetChildSize(currentIndex) :
            GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
        endPos = startPos + mainLen;
        itemPosition_[currentIndex] = { id, startPos, endPos, isGroup };
    } else {
        ++currentIndex;
        itemPosition_[currentIndex] = firstItemInfo_.value().second;
        endPos = itemPosition_[currentIndex].endPos;
    }
    if (firstItemInfo_) {
        firstItemInfo_.reset();
    }
    OnItemPositionAddOrUpdate(layoutWrapper, currentIndex);
    return 1;
}

int32_t ListLayoutAlgorithm::LayoutALineBackward(LayoutWrapper* layoutWrapper,
    int32_t& currentIndex, float endPos, float& startPos)
{
    if (currentIndex - 1 < 0) {
        return 0;
    }
    if (!firstItemInfo_ || firstItemInfo_.value().first != currentIndex - 1) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex - 1);
        CHECK_NULL_RETURN(wrapper, 0);
        int32_t id = wrapper->GetHostNode()->GetId();
        --currentIndex;
        bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        if (isGroup) {
            auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
            SetListItemGroupParam(wrapper, currentIndex, endPos, false, listLayoutProperty, false);
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItemGroup:%d, %f", currentIndex, endPos);
            wrapper->Measure(childLayoutConstraint_);
        } else if (expandSafeArea_ || CheckNeedMeasure(wrapper)) {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d, %f", currentIndex, endPos);
            wrapper->Measure(childLayoutConstraint_);
        }
        float mainLen = childrenSize_ ? childrenSize_->GetChildSize(currentIndex) :
            GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
        startPos = endPos - mainLen;
        itemPosition_[currentIndex] = { id, startPos, endPos, isGroup };
    } else {
        --currentIndex;
        itemPosition_[currentIndex] = firstItemInfo_.value().second;
        startPos = itemPosition_[currentIndex].startPos;
    }
    if (firstItemInfo_) {
        firstItemInfo_.reset();
    }
    OnItemPositionAddOrUpdate(layoutWrapper, currentIndex);
    return 1;
}

void ListLayoutAlgorithm::LayoutForward(LayoutWrapper* layoutWrapper, int32_t startIndex, float startPos)
{
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    float endMainPos = overScrollFeature_ ?
        std::max(startPos + contentMainSize_ - contentStartOffset_, endMainPos_) : endMainPos_;
    layoutEndMainPos_ = endMainPos;

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
        if (forwardFeature_ && targetIndex_ && currentIndex >= targetIndex_.value()) {
            endMainPos = layoutEndMainPos_.value_or(endMainPos_);
            forwardFeature_ = false;
        }
    } while (LessOrEqual(currentEndPos + chainOffset, endMainPos) || forwardFeature_);
    currentEndPos += chainOffset;

    while (!itemPosition_.empty() && !targetIndex_) {
        auto pos = itemPosition_.rbegin();
        float chainDelta = chainOffsetFunc_ ? chainOffsetFunc_(pos->first) : 0.0f;
        if ((GreatNotEqual(pos->second.endPos + chainDelta, endMainPos) &&
            GreatOrEqual(pos->second.startPos + chainDelta, endMainPos))) {
            recycledItemPosition_.emplace(pos->first, pos->second);
            itemPosition_.erase(pos->first);
        } else {
            break;
        }
    }
    // adjust offset.
    UpdateSnapCenterContentOffset(layoutWrapper);
    if (LessNotEqual(currentEndPos, endMainPos_ - contentEndOffset_) && !itemPosition_.empty()) {
        endMainPos_ = currentEndPos + contentEndOffset_;
        startMainPos_ = endMainPos_ - contentMainSize_;
        ReMeasureListItemGroup(layoutWrapper, true);
        auto firstItemTop = itemPosition_.begin()->second.startPos;
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
        if (pos->second.isGroup) {
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos->first);
            if (wrapper && wrapper->GetHostNode() && wrapper->GetHostNode()->GetPattern<ListItemGroupPattern>()) {
                wrapper->GetHostNode()->GetPattern<ListItemGroupPattern>()->ClearItemPosition();
            }
        }
        recycledItemPosition_.emplace(pos->first, pos->second);
        pos = itemPosition_.erase(pos);
    }
}

void ListLayoutAlgorithm::LayoutBackward(LayoutWrapper* layoutWrapper, int32_t endIndex, float endPos)
{
    float currentStartPos = endPos;
    float currentEndPos = 0.0f;
    float startMainPos = overScrollFeature_ ?
        std::min(endPos - contentMainSize_ + contentEndOffset_, startMainPos_) : startMainPos_;
    layoutStartMainPos_ = startMainPos;

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
            startMainPos = layoutStartMainPos_.value_or(startMainPos_);
            backwardFeature_ = false;
        }
    } while (GreatNotEqual(currentStartPos + chainOffset, startMainPos) || backwardFeature_);

    currentStartPos += chainOffset;
    // adjust offset. If edgeEffect is SPRING, jump adjust to allow list scroll through boundary
    UpdateSnapCenterContentOffset(layoutWrapper);
    if (GreatNotEqual(currentStartPos, startMainPos_ + contentStartOffset_) && !itemPosition_.empty()) {
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
        ReMeasureListItemGroup(layoutWrapper, false);
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
        if (pos->second.isGroup) {
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos->first);
            if (wrapper && wrapper->GetHostNode() && wrapper->GetHostNode()->GetPattern<ListItemGroupPattern>()) {
                wrapper->GetHostNode()->GetPattern<ListItemGroupPattern>()->ClearItemPosition();
            }
        }
        recycledItemPosition_.emplace(pos->first, pos->second);
        removeIndexes.emplace_back(pos->first);
    }
    for (const auto& index : removeIndexes) {
        itemPosition_.erase(index);
    }
}

void ListLayoutAlgorithm::ReMeasureListItemGroup(LayoutWrapper* layoutWrapper, bool forwardLayout)
{
    if (forwardFeature_ || backwardFeature_) {
        return;
    }
    if (!forwardLayout) {
        for (auto pos = itemPosition_.begin(); pos != itemPosition_.end(); pos++) {
            float chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(pos->first) : 0.0f;
            if (GreatOrEqual(pos->second.startPos + chainOffset, endMainPos_)) {
                break;
            } else if (!pos->second.isGroup) {
                continue;
            }
            AdjustPostionForListItemGroup(layoutWrapper, axis_, pos->first, forwardLayout);
        }
        return;
    }
    if (isNeedCheckOffset_ && GreatNotEqual(std::abs(currentDelta_), contentMainSize_ * 2.0f)) {
        for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); pos++) {
            float chainOffset = chainOffsetFunc_ ? chainOffsetFunc_(pos->first) : 0.0f;
            if (LessOrEqual(pos->second.endPos + chainOffset, startMainPos_)) {
                break;
            } else if (!pos->second.isGroup) {
                continue;
            }
            AdjustPostionForListItemGroup(layoutWrapper, axis_, pos->first, forwardLayout);
        }
        return;
    }
    if (itemPosition_.begin()->second.isGroup) {
        AdjustPostionForListItemGroup(layoutWrapper, axis_, GetStartIndex(), forwardLayout);
    }
}

void ListLayoutAlgorithm::FixPredictSnapOffset(const RefPtr<ListLayoutProperty>& listLayoutProperty)
{
    if (!predictSnapOffset_.has_value() || itemPosition_.empty()) {
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
    if (GetStartIndex() <= endIndex && endIndex <= GetEndIndex()) {
        predictEndPos = CalculatePredictSnapEndPositionByIndex(endIndex, scrollSnapAlign);
        predictSnapOffset_ = totalOffset_ - predictEndPos + currentOffset_;
        predictSnapEndPos_.reset();
    } else {
        if (IsUniformHeightProbably()) {
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
    float maxPos = itemHeight * totalItemCount_ - spaceWidth_ - endPos;

    if (LessNotEqual(predictEndPos, -startPos)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = -startPos;
    } else if (GreatNotEqual(predictEndPos, maxPos)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = maxPos;
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
        } else if (GreatNotEqual(predictEndPos, maxPos)) {
            predictEndPos = maxPos;
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
    float maxPos = itemHeight * totalItemCount_ - spaceWidth_ - endPos;

    if (LessNotEqual(predictEndPos, -startPos)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = -startPos;
    } else if (GreatNotEqual(predictEndPos, maxPos)) {
        if (isSpringEffect_) {
            return;
        }
        predictEndPos = maxPos;
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
        } else if (GreatNotEqual(predictEndPos, maxPos)) {
            predictEndPos = maxPos;
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
    if (isReverse_) {
        if (axis_ == Axis::VERTICAL) {
            auto size = wrapper->GetGeometryNode()->GetMarginFrameSize();
            offset = offset + OffsetF(crossSize - crossOffset - size.Width(), pos.startPos + chainOffset);
        } else {
            offset = offset + OffsetF(contentMainSize_ - pos.endPos - chainOffset, crossOffset);
        }
    } else {
        if (axis_ == Axis::VERTICAL) {
            offset = offset + OffsetF(crossOffset, pos.startPos + chainOffset);
        } else {
            offset = offset + OffsetF(pos.startPos + chainOffset, crossOffset);
        }
    }
    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    SetListItemIndex(wrapper, index);
}

void ListLayoutAlgorithm::ProcessCacheCount(LayoutWrapper* layoutWrapper, int32_t cacheCount, bool show)
{
    if (!itemPosition_.empty() && cacheCount > 0) {
        auto items = LayoutCachedItemV2(layoutWrapper, cacheCount, show);
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        if (!items.empty()) {
            ListMainSizeValues value = { startMainPos_, endMainPos_, jumpIndexInGroup_, prevContentMainSize_,
                scrollAlign_, layoutStartMainPos_, layoutEndMainPos_ };
            PostIdleTaskV2(host, { items, childLayoutConstraint_, GetGroupLayoutConstraint() }, value, show);
        } else {
            auto pattern = host->GetPattern<ListPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetPredictLayoutParamV2(std::nullopt);
        }
    } else {
        SetActiveChildRange(layoutWrapper, cacheCount, cacheCount, show);
    }
}

std::optional<ListItemGroupLayoutInfo> ListLayoutAlgorithm::GetListItemGroupLayoutInfo(
    const RefPtr<LayoutWrapper>& wrapper) const
{
    CHECK_NULL_RETURN(wrapper, std::nullopt);
    auto layoutAlgorithmWrapper = wrapper->GetLayoutAlgorithm(true);
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, std::nullopt);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(itemGroup, std::nullopt);
    return itemGroup->GetLayoutInfo();
}

void ListLayoutAlgorithm::ResetLayoutItem(LayoutWrapper* layoutWrapper)
{
    for (auto& pos : recycledItemPosition_) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos.first);
        pos.second.startPos -= currentOffset_;
        pos.second.endPos -= currentOffset_;
        if (pos.second.isGroup) {
            pos.second.groupInfo = GetListItemGroupLayoutInfo(wrapper);
        } else {
            pos.second.groupInfo.reset();
        }
        auto wrapperFrameNode = AceType::DynamicCast<FrameNode>(wrapper);
        if (wrapperFrameNode) {
            wrapperFrameNode->ClearSubtreeLayoutAlgorithm();
        }
    }
}

void ListLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto listProps = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listProps);
    auto axis_ = listProps->GetListDirection().value_or(Axis::VERTICAL);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    paddingOffset_ = padding.Offset();
    float crossSize = GetCrossAxisSize(size, axis_);
    totalItemCount_ = layoutWrapper->GetTotalChildCount();
    listItemAlign_ = listProps->GetListItemAlign().value_or(V2::ListItemAlign::START);
    int32_t startIndex = GetStartIndex();
    isReverse_ = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection() == TextDirection::RTL;

    totalOffset_ += currentOffset_;
    FixPredictSnapOffset(listProps);
    // layout items.
    for (auto& pos : itemPosition_) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos.first);
        if (!wrapper) {
            continue;
        }
        pos.second.startPos -= currentOffset_;
        pos.second.endPos -= currentOffset_;
        if (pos.second.isGroup) {
            pos.second.groupInfo = GetListItemGroupLayoutInfo(wrapper);
        } else {
            pos.second.groupInfo.reset();
        }
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
    ResetLayoutItem(layoutWrapper);
    ProcessCacheCount(layoutWrapper, listProps->GetCachedCountValue(1), listProps->GetShowCachedItemsValue(false));
    UpdateOverlay(layoutWrapper);
}

void ListLayoutAlgorithm::UpdateOverlay(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!paintProperty->GetFadingEdge().value_or(false)) {
        return;
    }
    auto overlayNode = frameNode->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto listFrameSize = geometryNode->GetFrameSize();
    auto overlayGeometryNode = overlayNode->GetGeometryNode();
    CHECK_NULL_VOID(overlayGeometryNode);
    overlayGeometryNode->SetFrameSize(listFrameSize);
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
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    // only when textField is onFocus
    auto textField = textFieldManager->GetOnFocusTextField().Upgrade();
    CHECK_NULL_VOID(textField);
    auto textFieldHost = textField->GetHost();
    CHECK_NULL_VOID(textFieldHost);
    auto textBase = DynamicCast<TextBase>(textField);
    CHECK_NULL_VOID(textBase);
    auto caretPos = textFieldHost->GetTransformRelativeOffset().GetY() + textBase->GetCaretRect().Bottom();
    auto globalOffset = host->GetTransformRelativeOffset();
    auto offset = contentMainSize_ + globalOffset.GetY() - caretPos - RESERVE_BOTTOM_HEIGHT.ConvertToPx();
    if (LessOrEqual(offset, 0.0)) {
        // negative offset to scroll down
        currentDelta_ -= static_cast<float>(offset);
    }
}

void ListLayoutAlgorithm::SetListItemGroupJumpIndex(const RefPtr<ListItemGroupLayoutAlgorithm>& itemGroup,
    bool forwardLayout, int32_t index)
{
    if (jumpIndex_.has_value() && jumpIndex_.value() == index) {
        if (!jumpIndexInGroup_.has_value()) {
            if (forwardLayout && (scrollAlign_ == ScrollAlign::START ||
                (scrollAlign_ == ScrollAlign::AUTO && scrollAutoType_ == ScrollAutoType::START))) {
                jumpIndexInGroup_ = 0;
            } else if (!forwardLayout && (scrollAlign_ == ScrollAlign::END ||
                (scrollAlign_ == ScrollAlign::AUTO && scrollAutoType_ == ScrollAutoType::END))) {
                jumpIndexInGroup_ = LAST_ITEM;
            }
        }

        if (jumpIndexInGroup_.has_value()) {
            itemGroup->SetJumpIndex(jumpIndexInGroup_.value());
            itemGroup->SetScrollAlign(scrollAlign_);
            jumpIndexInGroup_.reset();
        }
    }
}

void ListLayoutAlgorithm::SetListItemGroupParam(const RefPtr<LayoutWrapper>& layoutWrapper, int32_t index,
    float referencePos, bool forwardLayout, const RefPtr<ListLayoutProperty>& layoutProperty, bool groupNeedAllLayout,
    bool needAdjustRefPos)
{
    auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm(true);
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(itemGroup);
    if (jumpIndexInGroup_.has_value() && scrollAlign_ == ScrollAlign::CENTER) {
        referencePos = (startMainPos_ + endMainPos_) / 2; // 2:average
    }
    if (jumpIndex_) {
        itemGroup->ClearItemPosition();
    }
    if (forwardLayout) {
        float endPos = layoutEndMainPos_.value_or(endMainPos_);
        float startPos = endPos - contentMainSize_;
        itemGroup->SetListMainSize(startPos, endPos, referencePos, prevContentMainSize_, forwardLayout);
    } else {
        float startPos = layoutStartMainPos_.value_or(startMainPos_);
        float endPos = startPos + contentMainSize_;
        itemGroup->SetListMainSize(startPos, endPos, referencePos, prevContentMainSize_, forwardLayout);
    }
    bool needMeasureFormLastItem = index < preStartIndex_;
    itemGroup->SetNeedMeasureFormLastItem(needMeasureFormLastItem);
    itemGroup->SetNeedAdjustRefPos(needAdjustRefPos);
    itemGroup->SetListLayoutProperty(layoutProperty);
    itemGroup->SetNeedCheckOffset(isNeedCheckOffset_, groupItemAverageHeight_);
    if (scrollSnapAlign_ != V2::ScrollSnapAlign::CENTER) {
        itemGroup->SetContentOffset(contentStartOffset_, contentEndOffset_);
    }
    SetListItemGroupJumpIndex(itemGroup, forwardLayout, index);

    if (groupNeedAllLayout || (targetIndex_ && targetIndex_.value() == index) ||
        (scrollSnapAlign_ != V2::ScrollSnapAlign::NONE && !childrenSize_)) {
        itemGroup->SetNeedAllLayout();
    } else if (forwardFeature_ || backwardFeature_) {
        itemGroup->CheckNeedAllLayout(layoutWrapper, forwardLayout);
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
    auto algorithmWrapper = wrapper->GetLayoutAlgorithm(true);
    CHECK_NULL_VOID(algorithmWrapper);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(algorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(itemGroup);
    if (forwardLayout) {
        itemGroup->SetListMainSize(startMainPos_, endMainPos_, itemPosition_[index].endPos, prevContentMainSize_,
            !forwardLayout);
    } else {
        itemGroup->SetListMainSize(startMainPos_, endMainPos_, itemPosition_[index].startPos, prevContentMainSize_,
            !forwardLayout);
    }
    itemGroup->SetScrollAlign(ScrollAlign::NONE);
    wrapper->Measure(GetGroupLayoutConstraint());
    if (childrenSize_) {
        return;
    }
    float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis);
    auto& pos = itemPosition_[index];
    if (forwardLayout) {
        pos.startPos = pos.endPos - mainLen;
    } else {
        pos.endPos = pos.startPos + mainLen;
    }
}

void ListLayoutAlgorithm::OffScreenLayoutDirection(LayoutWrapper* layoutWrapper)
{
    if (!targetIndex_ || itemPosition_.empty()) {
        forwardFeature_ = false;
        backwardFeature_ = false;
        return;
    }
    auto layoutDirection = LayoutDirectionForTargetIndex(layoutWrapper, preStartIndex_);
    if (layoutDirection == LayoutDirection::BACKWARD) {
        forwardFeature_ = false;
        backwardFeature_ = true;
    } else {
        forwardFeature_ = true;
        backwardFeature_ = false;
    }
}

int32_t ListLayoutAlgorithm::GetMidIndex(LayoutWrapper* layoutWrapper, bool usePreContentMainSize)
{
    float contentSize = usePreContentMainSize ? prevContentMainSize_ : contentMainSize_;
    float midPos = contentSize / 2.0f;
    if (GetStartIndex() == 0 && !IsScrollSnapAlignCenter(layoutWrapper) &&
        GreatNotEqual(GetStartPosition(), contentStartOffset_)) {
        midPos = GetStartPosition() + contentSize / 2.0f - contentStartOffset_;
    } else if (GetEndIndex() == totalItemCount_ - 1 && !IsScrollSnapAlignCenter(layoutWrapper) &&
        LessNotEqual(GetEndPosition(), contentMainSize_ - contentEndOffset_) &&
        (GetStartIndex() != 0 || !NearEqual(GetStartPosition(), startMainPos_))) {
        midPos = GetEndPosition() - contentSize / 2.0f + contentEndOffset_;
    }
    for (auto& pos : itemPosition_) {
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
    host->ResetLayoutAlgorithm();
    host->RebuildRenderContextTree();
}

bool ListLayoutAlgorithm::LayoutCachedALine(LayoutWrapper* layoutWrapper, int32_t index,
    bool forward, float &currPos, float crossSize)
{
    auto wrapper = layoutWrapper->GetChildByIndex(index, true);
    if (!wrapper) {
        return true;
    }
    bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (CheckNeedMeasure(wrapper)) {
        return !isGroup;
    }
    auto childSize = wrapper->GetGeometryNode()->GetMarginFrameSize();
    int32_t id = wrapper->GetHostNode()->GetId();
    ListItemInfo pos;
    if (forward) {
        auto endPos = currPos + GetMainAxisSize(childSize, axis_);
        pos = { id, currPos, endPos, isGroup };
        currPos = endPos + spaceWidth_;
    } else {
        auto startPos = currPos - GetMainAxisSize(childSize, axis_);
        pos = { id, startPos, currPos, isGroup };
        currPos = startPos - spaceWidth_;
    }
    auto startIndex = index;
    LayoutItem(wrapper, index, pos, startIndex, crossSize);
    SyncGeometry(wrapper);
    wrapper->SetActive(false);
    return false;
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
        if (LayoutCachedALine(layoutWrapper, index, true, currPos, crossSize)) {
            predictBuildList.emplace_back(index);
        }
    }

    currIndex = itemPosition_.begin()->first - 1;
    currPos = itemPosition_.begin()->second.startPos - spaceWidth_;
    for (int32_t i = 0; i < cacheCount && currIndex - i >= 0; i++) {
        int32_t index = currIndex - i;
        if (LayoutCachedALine(layoutWrapper, index, false, currPos, crossSize)) {
            predictBuildList.emplace_back(index);
        }
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
    auto context = frameNode->GetContext();
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
            auto wrapper = frameNode->GetOrCreateChildByIndex(*it, false, true);
            if (wrapper && wrapper->GetHostNode() && !wrapper->GetHostNode()->RenderCustomChild(deadline)) {
                break;
            }
            needMarkDirty = PredictBuildItem(wrapper, param.layoutConstraint) || needMarkDirty;
            it = param.items.erase(it);
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

// return current CachedCount and max CacheCount
CachedIndexInfo ListLayoutAlgorithm::GetLayoutGroupCachedCount(LayoutWrapper* layoutWrapper,
    const RefPtr<LayoutWrapper>& wrapper, int32_t forwardCache, int32_t backwardCache, bool outOfView)
{
    CachedIndexInfo res;
    auto groupNode = AceType::DynamicCast<FrameNode>(wrapper);
    CHECK_NULL_RETURN(groupNode, res);
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(groupPattern, res);
    const auto& itemPos = groupPattern->GetItemPosition();
    int32_t itemCount = groupPattern->GetTotalItemCount();
    bool forward = forwardCache > -1;
    bool backward = backwardCache > -1;
    if (groupNode->CheckNeedForceMeasureAndLayout()) {
        groupPattern->CalculateItemStartIndex();
        itemCount = groupNode->GetTotalChildCount() - groupPattern->GetItemStartIndex();
    }
    if (forward && backward && itemPos.empty()) {
        forward = groupPattern->NeedCacheForward(layoutWrapper);
        backward = !forward;
        forwardCache = forward ? forwardCache : -1;
        backwardCache = backward ? backwardCache : -1;
    }
    if (forward && backward) {
        auto [forwardIndex, backwardIndex] = groupPattern->UpdateCachedIndex(outOfView, forwardCache, backwardCache);
        auto startIndex = itemPos.begin()->first;
        auto endIndex = itemPos.rbegin()->first;
        res.forwardCachedCount = forwardIndex - endIndex;
        res.forwardCacheMax = itemCount - 1 - endIndex;
        res.backwardCachedCount = startIndex - backwardIndex;
        res.backwardCacheMax = startIndex;
    } else if (forward) {
        auto [forwardIndex, backwardIndex] = groupPattern->UpdateCachedIndex(outOfView, forwardCache, backwardCache);
        int32_t endIndex = (outOfView || itemPos.empty()) ? -1 : itemPos.rbegin()->first;
        res.forwardCachedCount = forwardIndex - endIndex;
        res.forwardCacheMax = itemCount - 1 - endIndex;
    } else {
        auto [forwardIndex, backwardIndex] = groupPattern->UpdateCachedIndex(outOfView, forwardCache, backwardCache);
        int32_t startIndex = (outOfView || itemPos.empty()) ? itemCount : itemPos.begin()->first;
        res.backwardCachedCount = startIndex - backwardIndex;
        res.backwardCacheMax = startIndex;
    }
    ACE_SCOPED_TRACE("GetLayoutGroupCachedCount forward:%d, %d, backward:%d, %d",
        res.forwardCachedCount, res.forwardCacheMax, res.backwardCachedCount, res.backwardCacheMax);
    return res;
}

int32_t ListLayoutAlgorithm::LayoutCachedForward(LayoutWrapper* layoutWrapper,
    int32_t cacheCount, int32_t& cachedCount, int32_t& currIndex)
{
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    float crossSize = GetCrossAxisSize(size, axis_);
    currIndex = itemPosition_.rbegin()->first + 1;
    auto currPos = itemPosition_.rbegin()->second.endPos + spaceWidth_;
    while (cachedCount < cacheCount && currIndex < totalItemCount_) {
        auto wrapper = layoutWrapper->GetChildByIndex(currIndex, true);
        if (!wrapper) {
            return 0;
        }
        bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        if (!isGroup && CheckNeedMeasure(wrapper)) {
            return 0;
        }
        auto childSize = wrapper->GetGeometryNode()->GetMarginFrameSize();
        auto endPos = currPos + GetMainAxisSize(childSize, axis_);
        int32_t id = wrapper->GetHostNode()->GetId();
        ListItemInfo pos = { id, currPos, endPos, isGroup };
        currPos = endPos + spaceWidth_;
        auto startIndex = currIndex;
        LayoutItem(wrapper, currIndex, pos, startIndex, crossSize);
        if (isGroup) {
            auto res = GetLayoutGroupCachedCount(layoutWrapper, wrapper, cacheCount - cachedCount, -1, true);
            if (res.forwardCachedCount < res.forwardCacheMax && res.forwardCachedCount < cacheCount - cachedCount) {
                return res.forwardCachedCount;
            }
            cachedCount += std::max(res.forwardCacheMax, 1);
        } else {
            cachedCount++;
        }
        SyncGeometry(wrapper);
        wrapper->SetActive(false);
        currIndex++;
    }
    return -1;
}

int32_t ListLayoutAlgorithm::LayoutCachedBackward(LayoutWrapper* layoutWrapper,
    int32_t cacheCount, int32_t& cachedCount, int32_t& currIndex)
{
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    float crossSize = GetCrossAxisSize(size, axis_);
    currIndex = itemPosition_.begin()->first - 1;
    auto currPos = itemPosition_.begin()->second.startPos - spaceWidth_;
    while (cachedCount < cacheCount && currIndex >= 0) {
        auto wrapper = layoutWrapper->GetChildByIndex(currIndex, true);
        if (!wrapper) {
            return 0;
        }
        bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        if (!isGroup && CheckNeedMeasure(wrapper)) {
            return 0;
        }
        auto childSize = wrapper->GetGeometryNode()->GetMarginFrameSize();
        auto startPos = currPos - GetMainAxisSize(childSize, axis_);
        int32_t id = wrapper->GetHostNode()->GetId();
        ListItemInfo pos = { id, startPos, currPos, isGroup };
        currPos = startPos - spaceWidth_;
        auto startIndex = currIndex;
        LayoutItem(wrapper, currIndex, pos, startIndex, crossSize);
        if (isGroup) {
            auto res = GetLayoutGroupCachedCount(layoutWrapper, wrapper, -1, cacheCount - cachedCount, true);
            if (res.backwardCachedCount < res.backwardCacheMax && res.backwardCachedCount < cacheCount - cachedCount) {
                return res.backwardCachedCount;
            }
            cachedCount += std::max(res.backwardCacheMax, 1);
        } else {
            cachedCount++;
        }
        SyncGeometry(wrapper);
        wrapper->SetActive(false);
        currIndex--;
    }
    return -1;
}

std::tuple<int32_t, int32_t, int32_t, int32_t> ListLayoutAlgorithm::LayoutCachedItemInEdgeGroup(
    LayoutWrapper* layoutWrapper, int32_t cacheCount, std::list<PredictLayoutItem>& predictList)
{
    int32_t startIndex = GetStartIndex();
    int32_t endIndex = GetEndIndex();
    int32_t cachedForward = 0;
    int32_t cachedBackward = 0;
    if (startIndex == endIndex && itemPosition_.begin()->second.isGroup) {
        auto wrapper = layoutWrapper->GetChildByIndex(startIndex);
        auto res = GetLayoutGroupCachedCount(layoutWrapper, wrapper, cacheCount, cacheCount, false);
        if ((res.forwardCachedCount < res.forwardCacheMax && res.forwardCachedCount < cacheCount) ||
            (res.backwardCachedCount < res.backwardCacheMax && res.backwardCachedCount < cacheCount)) {
            predictList.emplace_back(PredictLayoutItem { startIndex, cachedForward, cachedBackward });
        }
        cachedForward += res.forwardCacheMax;
        cachedBackward += res.backwardCacheMax;
    } else {
        if (itemPosition_.rbegin()->second.isGroup) {
            auto wrapper = layoutWrapper->GetChildByIndex(endIndex);
            auto res = GetLayoutGroupCachedCount(layoutWrapper, wrapper, cacheCount, -1, false);
            if (res.forwardCachedCount < res.forwardCacheMax && res.forwardCachedCount < cacheCount) {
                predictList.emplace_back(PredictLayoutItem { endIndex, cachedForward, -1 });
            }
            cachedForward += res.forwardCacheMax;
        }
        if (itemPosition_.begin()->second.isGroup) {
            auto wrapper = layoutWrapper->GetChildByIndex(startIndex);
            auto res = GetLayoutGroupCachedCount(layoutWrapper, wrapper, -1, cacheCount, false);
            if (res.backwardCachedCount < res.backwardCacheMax && res.backwardCachedCount < cacheCount) {
                predictList.emplace_back(PredictLayoutItem { startIndex, -1, cachedBackward });
            }
            cachedBackward += res.backwardCacheMax;
        }
    }
    return { startIndex, endIndex, cachedForward, cachedBackward };
}

std::list<PredictLayoutItem> ListLayoutAlgorithm::LayoutCachedItemV2(LayoutWrapper* layoutWrapper, int32_t cacheCount,
    bool show)
{
    ACE_SCOPED_TRACE("LayoutCachedItemV2");
    std::list<PredictLayoutItem> predictBuildList;
    auto [startIndex, endIndex, cachedForward, cachedBackward] =
        LayoutCachedItemInEdgeGroup(layoutWrapper, cacheCount, predictBuildList);
    if (cachedForward < cacheCount && endIndex < totalItemCount_ - 1) {
        int32_t groupCachedCount = LayoutCachedForward(layoutWrapper, cacheCount, cachedForward, endIndex);
        if (groupCachedCount >= 0) {
            predictBuildList.emplace_back(PredictLayoutItem { endIndex, cachedForward, -1 });
        }
        if (groupCachedCount <= 0) {
            endIndex--;
        }
    }
    if (cachedBackward < cacheCount && startIndex > 0) {
        auto groupCachedCount = LayoutCachedBackward(layoutWrapper, cacheCount, cachedBackward, startIndex);
        if (groupCachedCount >= 0) {
            predictBuildList.emplace_back(PredictLayoutItem { startIndex, -1, cachedBackward });
        }
        if (groupCachedCount <= 0) {
            startIndex++;
        }
    }
    int32_t cacheStart = itemPosition_.begin()->first - startIndex;
    int32_t cacheEnd = endIndex - itemPosition_.rbegin()->first;
    SetActiveChildRange(layoutWrapper, cacheStart, cacheEnd, show);
    return predictBuildList;
}

bool ListLayoutAlgorithm::PredictBuildGroup(RefPtr<LayoutWrapper> wrapper, const LayoutConstraintF& constraint,
    int64_t deadline, int32_t forwardCached, int32_t backwardCached, const ListMainSizeValues& listMainSizeValues)
{
    CHECK_NULL_RETURN(wrapper, false);
    auto groupNode = AceType::DynamicCast<FrameNode>(wrapper);
    CHECK_NULL_RETURN(groupNode, false);
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(groupPattern, false);
    float referencePos = 0.0f;
    if (listMainSizeValues.jumpIndexInGroup.has_value() && listMainSizeValues.scrollAlign == ScrollAlign::CENTER) {
        referencePos = (listMainSizeValues.startPos + listMainSizeValues.endPos) / 2; // 2:average
    }
    float endPos = 0.0f;
    float startPos = 0.0f;
    if (listMainSizeValues.forward) {
        startPos = listMainSizeValues.startPos;
        endPos = listMainSizeValues.layoutEndMainPos.value_or(listMainSizeValues.endPos);
    } else {
        startPos = listMainSizeValues.layoutStartMainPos.value_or(listMainSizeValues.startPos);
        endPos = listMainSizeValues.endPos;
    }
    ListMainSizeValues values;
    values.startPos = startPos;
    values.endPos = endPos;
    values.referencePos = referencePos;
    values.prevContentMainSize = listMainSizeValues.prevContentMainSize;
    values.forward = listMainSizeValues.forward;
    values.backward = listMainSizeValues.backward;
    groupPattern->LayoutCache(constraint, deadline, forwardCached, backwardCached, values);
    return true;
}

void ListLayoutAlgorithm::PredictBuildV2(
    RefPtr<FrameNode> frameNode, int64_t deadline, ListMainSizeValues listMainSizeValues, bool show)
{
    ACE_SCOPED_TRACE("List predict v2");
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->GetPredictLayoutParamV2().has_value()) {
        return;
    }
    bool needMarkDirty = false;
    auto param = pattern->GetPredictLayoutParamV2().value();
    for (auto it = param.items.begin(); it != param.items.end();) {
        if (GetSysTimestamp() > deadline) {
            break;
        }
        ACE_SCOPED_TRACE("predict Item:%d", (*it).index);
        auto wrapper = frameNode->GetOrCreateChildByIndex((*it).index, show, true);
        if (!wrapper) {
            it = param.items.erase(it);
            continue;
        }
        if (wrapper->GetHostNode() && !wrapper->GetHostNode()->RenderCustomChild(deadline)) {
            break;
        }
        bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        if (!isGroup) {
            auto frameNode = wrapper->GetHostNode();
            CHECK_NULL_VOID(frameNode);
            frameNode->GetGeometryNode()->SetParentLayoutConstraint(param.layoutConstraint);
            FrameNode::ProcessOffscreenNode(frameNode);
        } else {
            listMainSizeValues.forward = (*it).forwardCacheCount > -1;
            listMainSizeValues.backward = (*it).backwardCacheCount > -1;
            PredictBuildGroup(wrapper, param.groupLayoutConstraint, deadline, (*it).forwardCacheCount,
                (*it).backwardCacheCount, listMainSizeValues);
        }
        needMarkDirty = true;
        it = param.items.erase(it);
    }
    if (needMarkDirty) {
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    }
    pattern->SetPredictLayoutParamV2(std::nullopt);
    if (!param.items.empty()) {
        ListLayoutAlgorithm::PostIdleTaskV2(frameNode, param, listMainSizeValues, show);
    }
}

void ListLayoutAlgorithm::PostIdleTaskV2(RefPtr<FrameNode> frameNode,
    const ListPredictLayoutParamV2& param, ListMainSizeValues listMainSizeValues, bool show)
{
    ACE_SCOPED_TRACE("PostIdleTaskV2");
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetPredictLayoutParamV2()) {
        pattern->SetPredictLayoutParamV2(param);
        return;
    }
    pattern->SetPredictLayoutParamV2(param);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask(
        [weak = WeakClaim(RawPtr(frameNode)), value = listMainSizeValues, show = show](int64_t deadline,
        bool canUseLongPredictTask) { ListLayoutAlgorithm::PredictBuildV2(weak.Upgrade(), deadline, value, show); });
}

float ListLayoutAlgorithm::GetStopOnScreenOffset(V2::ScrollSnapAlign scrollSnapAlign) const
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

void ListLayoutAlgorithm::FindPredictSnapIndexInItemPositionsStart(
    float predictEndPos, int32_t& endIndex, int32_t& currIndex) const
{
    float stopOnScreen = GetStopOnScreenOffset(V2::ScrollSnapAlign::START);
    float itemHeight = itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos;
    for (const auto& positionInfo : itemPosition_) {
        auto startPos = positionInfo.second.startPos - itemHeight / 2.0f - spaceWidth_;
        float itemHeight = positionInfo.second.endPos - positionInfo.second.startPos;
        auto endPos = positionInfo.second.startPos + itemHeight / 2.0f;
        if (GreatOrEqual(predictEndPos + stopOnScreen, totalOffset_ + startPos) &&
            LessNotEqual(predictEndPos + stopOnScreen, totalOffset_ + endPos)) {
            endIndex = positionInfo.first;
        }
        if (GreatOrEqual(stopOnScreen, startPos) && LessNotEqual(stopOnScreen, endPos)) {
            currIndex = positionInfo.first;
        }
        if (endIndex >= 0 && currIndex >= 0) {
            break;
        }
    }
}

void ListLayoutAlgorithm::FindPredictSnapIndexInItemPositionsCenter(
    float predictEndPos, int32_t& endIndex, int32_t& currIndex) const
{
    float stopOnScreen = GetStopOnScreenOffset(V2::ScrollSnapAlign::CENTER);
    for (const auto& positionInfo : itemPosition_) {
        auto startPos = positionInfo.second.startPos - spaceWidth_ / 2.0f;
        auto endPos = positionInfo.second.endPos + spaceWidth_ / 2.0f;
        if (GreatOrEqual(predictEndPos + stopOnScreen, totalOffset_ + startPos) &&
            LessNotEqual(predictEndPos + stopOnScreen, totalOffset_ + endPos)) {
            endIndex = positionInfo.first;
        }
        if (GreatOrEqual(stopOnScreen, startPos) && LessNotEqual(stopOnScreen, endPos)) {
            currIndex = positionInfo.first;
        }
        if (endIndex >= 0 && currIndex >= 0) {
            break;
        }
    }
}

void ListLayoutAlgorithm::FindPredictSnapIndexInItemPositionsEnd(
    float predictEndPos, int32_t& endIndex, int32_t& currIndex) const
{
    float stopOnScreen = GetStopOnScreenOffset(V2::ScrollSnapAlign::END);
    float itemHeight = itemPosition_.rbegin()->second.endPos - itemPosition_.rbegin()->second.startPos;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        auto endPos = pos->second.endPos + itemHeight / 2.0f + spaceWidth_;
        itemHeight = pos->second.endPos - pos->second.startPos;
        auto startPos = pos->second.endPos - itemHeight / 2.0f;
        if (GreatOrEqual(predictEndPos + stopOnScreen, totalOffset_ + startPos) &&
            LessNotEqual(predictEndPos + stopOnScreen, totalOffset_ + endPos)) {
            endIndex = pos->first;
        }
        if (GreatOrEqual(stopOnScreen, startPos) && LessNotEqual(stopOnScreen, endPos)) {
            currIndex = pos->first;
        }
        if (endIndex >= 0 && currIndex >= 0) {
            break;
        }
    }
}

int32_t ListLayoutAlgorithm::FindPredictSnapEndIndexInItemPositions(
    float predictEndPos, V2::ScrollSnapAlign scrollSnapAlign)
{
    int32_t endIndex = -1;
    int32_t currIndex = -1;

    if (scrollSnapAlign == V2::ScrollSnapAlign::START) {
        FindPredictSnapIndexInItemPositionsStart(predictEndPos, endIndex, currIndex);
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::CENTER) {
        FindPredictSnapIndexInItemPositionsCenter(predictEndPos, endIndex, currIndex);
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::END) {
        FindPredictSnapIndexInItemPositionsEnd(predictEndPos, endIndex, currIndex);
    }
    if (endIndex == currIndex && currIndex >= 0) {
        if (scrollSnapVelocity_ < -SCROLL_SNAP_VELOCITY_TH * Scrollable::GetVelocityScale()) {
            endIndex = std::min(GetEndIndex(), endIndex + 1);
        } else if (scrollSnapVelocity_ > SCROLL_SNAP_VELOCITY_TH * Scrollable::GetVelocityScale()) {
            endIndex = std::min(GetStartIndex(), endIndex - 1);
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

float ListLayoutAlgorithm::CalculatePredictSnapEndPositionByIndex(int32_t index, V2::ScrollSnapAlign scrollSnapAlign)
{
    float predictSnapEndPos = 0;
    if (scrollSnapAlign == V2::ScrollSnapAlign::START) {
        predictSnapEndPos = totalOffset_ + itemPosition_[index].startPos - contentStartOffset_;
        if ((GetEndIndex() == totalItemCount_ - 1) &&
            GreatNotEqual(predictSnapEndPos + contentMainSize_, totalOffset_ + GetEndPosition())) {
            predictSnapEndPos = totalOffset_ + GetEndPosition() - contentMainSize_ + contentEndOffset_;
        }
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::CENTER) {
        float itemHeight = itemPosition_[index].endPos - itemPosition_[index].startPos;
        predictSnapEndPos = totalOffset_ + itemPosition_[index].startPos + itemHeight / 2.0f - contentMainSize_ / 2.0f;
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::END) {
        predictSnapEndPos = totalOffset_ + itemPosition_[index].endPos - contentMainSize_ + contentEndOffset_;
        if (GetStartIndex() == 0 && LessNotEqual(predictSnapEndPos, totalOffset_ + GetStartPosition())) {
            predictSnapEndPos = totalOffset_ + GetStartPosition() - contentStartOffset_;
        }
    }
    return predictSnapEndPos;
}

void ListLayoutAlgorithm::OnItemPositionAddOrUpdate(LayoutWrapper* layoutWrapper, int32_t index)
{
    if (!predictSnapEndPos_.has_value()) {
        return;
    }
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);
    auto scrollSnapAlign = listLayoutProperty->GetScrollSnapAlign().value_or(V2::ScrollSnapAlign::NONE);
    float startPos = 0.0f;
    float endPos = 0.0f;
    if (scrollSnapAlign == V2::ScrollSnapAlign::START) {
        startPos = totalOffset_ + itemPosition_[index].startPos - spaceWidth_;
        endPos = totalOffset_ + itemPosition_[index].endPos;
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::CENTER) {
        startPos = totalOffset_ + itemPosition_[index].startPos - spaceWidth_ / 2.0f;
        endPos = totalOffset_ + itemPosition_[index].endPos + spaceWidth_ / 2.0f;
    } else if (scrollSnapAlign == V2::ScrollSnapAlign::END) {
        startPos = totalOffset_ + itemPosition_[index].startPos;
        endPos = totalOffset_ + itemPosition_[index].endPos + spaceWidth_;
    } else {
        return;
    }

    float predictSnapEndPos = predictSnapEndPos_.value();
    float stopOnScreen = GetStopOnScreenOffset(scrollSnapAlign);
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

std::pair<int32_t, float> ListLayoutAlgorithm::GetSnapStartIndexAndPos()
{
    int32_t startIndex = std::min(GetStartIndex(), totalItemCount_ - 1);
    float startPos = itemPosition_.begin()->second.startPos;
    for (auto& pos : itemPosition_) {
        if (NearEqual(pos.second.startPos, prevContentStartOffset_)) {
            startIndex = pos.first;
            startPos = itemPosition_[startIndex].startPos + contentStartOffset_ - prevContentStartOffset_;
            break;
        } else if (GreatNotEqual(pos.second.startPos, prevContentStartOffset_)) {
            if ((GetEndIndex() == totalItemCount_ - 1) &&
                NearEqual(GetEndPosition(), prevContentMainSize_ - prevContentEndOffset_) && !canOverScroll_) {
                startIndex = pos.first;
                startPos = contentStartOffset_;
                adjustOffset_ = pos.second.startPos - prevContentStartOffset_;
            }
            break;
        }
    }
    return std::make_pair(startIndex, startPos);
}

std::pair<int32_t, float> ListLayoutAlgorithm::GetSnapEndIndexAndPos()
{
    int32_t endIndex = -1;
    float endPos = 0.0f;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        if (NearEqual(prevContentMainSize_ - pos->second.endPos, prevContentEndOffset_)) {
            endIndex = pos->first;
            endPos = itemPosition_[endIndex].endPos - contentEndOffset_ + prevContentEndOffset_;
            break;
        } else if (GreatNotEqual(prevContentMainSize_ - pos->second.endPos, prevContentEndOffset_)) {
            if ((GetStartIndex() == 0) && NearEqual(GetStartPosition(), prevContentStartOffset_) && !canOverScroll_) {
                endIndex = pos->first;
                endPos = prevContentMainSize_ - contentEndOffset_;
                adjustOffset_ = pos->second.endPos + prevContentEndOffset_ - prevContentMainSize_;
            }
            break;
        }
    }
    return std::make_pair(endIndex, endPos);
}
} // namespace OHOS::Ace::NG
