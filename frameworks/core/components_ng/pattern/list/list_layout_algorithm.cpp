/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "base/log/event_report.h"
#include "base/memory/ace_type.h"
#include "base/utils/feature_param.h"
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
    contentConstraint.maxSize.SetMainSize(LayoutInfinity<float>(), axis);
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
    if (isRoundingMode_) {
        spaceWidth_ = Round(spaceWidth_);
    }
    spaceWidth_ += chainInterval_;
}

void ListLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);
    listLayoutProperty_ = listLayoutProperty;

    axis_ = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    isStackFromEnd_ = listLayoutProperty->GetStackFromEnd().value_or(false);
    // Pre-recycle
    ScrollableUtils::RecycleItemsOutOfBoundary(axis_, -currentDelta_, GetStartIndex(), GetEndIndex(), layoutWrapper);

    const auto& layoutConstraintOps = listLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraintOps);
    const auto& layoutConstraint = layoutConstraintOps.value();

    // calculate idealSize and set FrameSize
    CalcContentOffset(layoutWrapper);

    // calculate main size.
    const auto& contentConstraintOps = listLayoutProperty->GetContentLayoutConstraint();
    CHECK_NULL_VOID(contentConstraintOps);
    auto contentConstraint = contentConstraintOps.value();

    float expandHeight = ScrollableUtils::CheckHeightExpansion(listLayoutProperty, axis_);
    contentEndOffset_ += expandHeight;
    // expand contentSize
    contentConstraint.MinusPadding(std::nullopt, std::nullopt, std::nullopt, -expandHeight);
    auto&& safeAreaOpts = listLayoutProperty->GetSafeAreaExpandOpts();
    expandSafeArea_ = safeAreaOpts && safeAreaOpts->Expansive();

    auto contentIdealSize = CreateIdealSize(
        contentConstraint, axis_, listLayoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS));
    const auto& padding = listLayoutProperty->CreatePaddingAndBorder();

    auto layoutPolicy = listLayoutProperty->GetLayoutPolicyProperty();
    auto isCrossWrap = false;
    auto isCrossFix = false;
    auto isMainFix = false;
    if (layoutPolicy.has_value()) {
        auto isVertical = axis_ == Axis::VERTICAL;
        auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        isMainFix = (isVertical ? heightLayoutPolicy : widthLayoutPolicy) == LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
        isCrossWrap = (isVertical ? widthLayoutPolicy : heightLayoutPolicy) == LayoutCalPolicy::WRAP_CONTENT;
        isCrossFix = (isVertical ? widthLayoutPolicy : heightLayoutPolicy) == LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
        auto layoutPolicySize =
            ConstrainIdealSizeByLayoutPolicy(layoutConstraint, widthLayoutPolicy, heightLayoutPolicy, axis_);
        MinusPaddingToSize(padding, layoutPolicySize);
        contentIdealSize.UpdateIllegalSizeWithCheck(layoutPolicySize);
    }

    paddingBeforeContent_ = axis_ == Axis::HORIZONTAL ? padding.left.value_or(0) : padding.top.value_or(0);
    paddingAfterContent_ = axis_ == Axis::HORIZONTAL ? padding.right.value_or(0) : padding.bottom.value_or(0);
    contentMainSize_ = 0.0f;
    CalculateTotalCountByRepeat(layoutWrapper);
    scrollSnapAlign_ = listLayoutProperty->GetScrollSnapAlign().value_or(ScrollSnapAlign::NONE);
    if (childrenSize_) {
        childrenSize_->ResizeChildrenSize(totalItemCount_);
    }
    if (!GetMainAxisSize(contentIdealSize, axis_)) {
        if (totalItemCount_ == 0) {
            contentMainSize_ = 0.0f;
        } else {
            // use parent max size first.
            auto parentMaxSize = contentConstraint.maxSize;
            contentMainSize_ = isMainFix ? LayoutInfinity<float>() : GetMainAxisSize(parentMaxSize, axis_);
            mainSizeIsDefined_ = false;
        }
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            contentMainSize_ = std::max(contentMainSize_, GetMainAxisSize(contentConstraint.minSize, axis_));
        }
    } else {
        contentMainSize_ = GetMainAxisSize(contentIdealSize.ConvertToSizeT(), axis_);
        mainSizeIsDefined_ = true;
    }
    syncLoad_ = IsNeedSyncLoad(listLayoutProperty);
    if (GreatOrEqual(contentStartOffset_ + contentEndOffset_, contentMainSize_) ||
        IsScrollSnapAlignCenter(layoutWrapper)) {
        contentStartOffset_ = 0;
        contentEndOffset_ = 0;
    }
    MeasureHeader(layoutWrapper);
    if (totalItemCount_ > 0) {
        OnSurfaceChanged(layoutWrapper);

        stickyStyle_ = listLayoutProperty->GetStickyStyle().value_or(V2::StickyStyle::NONE);
        childLayoutConstraint_ = listLayoutProperty->CreateChildConstraint();
        auto mainPercentRefer = GetMainAxisSize(childLayoutConstraint_.percentReference, axis_);
        auto space = listLayoutProperty->GetSpace().value_or(Dimension(0));
        spaceWidth_ = ConvertToPx(space, layoutConstraint.scaleProperty, mainPercentRefer).value_or(0);
        ReviseSpace(listLayoutProperty);
        CheckJumpToIndex();
        CalculateLanes(listLayoutProperty, layoutConstraint, contentIdealSize.CrossSize(axis_), axis_);
        if (childrenSize_ && posMap_) {
            posMap_->UpdatePosMap(layoutWrapper, GetLanes(), spaceWidth_, childrenSize_);
        }
        ProcessStackFromEnd();
        currentOffset_ = currentDelta_;
        startMainPos_ = currentOffset_;
        endMainPos_ = currentOffset_ + contentMainSize_;
        listItemAlign_ = listLayoutProperty->GetListItemAlign().value_or(V2::ListItemAlign::START);
        // calculate child layout constraint.
        UpdateListItemConstraint(axis_, contentIdealSize, childLayoutConstraint_);
        MeasureList(layoutWrapper);
    } else {
        itemPosition_.clear();
        if (childrenSize_ && posMap_) {
            posMap_->ClearPosMap();
        }
    }
    // In the secondary layout scenario, the previous contentMainSize_ is used as the next prevContentMainSize_.
    prevContentMainSize_ = contentMainSize_;
    
    auto crossSize = contentIdealSize.CrossSize(axis_);
    if ((crossSize.has_value() && GreaterOrEqualToInfinity(crossSize.value())) || isCrossFix) {
        contentIdealSize.SetCrossSize(GetChildMaxCrossSize(layoutWrapper, axis_), axis_);
        crossMatchChild_ = true;
    } else if (isCrossWrap) {
        contentIdealSize.SetCrossSize(
            std::min(GetChildMaxCrossSize(layoutWrapper, axis_), crossSize.value_or(0.0f)), axis_);
        crossMatchChild_ = true;
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && !mainSizeIsDefined_ && !isMainFix) {
        contentMainSize_ = std::max(contentMainSize_, GetMainAxisSize(contentConstraint.minSize, axis_));
    }
    contentIdealSize.SetMainSize(contentMainSize_, axis_);
    AddPaddingToSize(padding, contentIdealSize);

    auto size = contentIdealSize.ConvertToSizeT();
    // Cancel frame size expansion, only expand content size here.
    // Frame expansion will be determined after Layout.
    size.MinusHeight(expandHeight);
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);

    if (listLayoutProperty->HasCacheRange()) {
        ScrollableUtils::DisableLazyForEachBuildCache(layoutWrapper->GetHostNode());
    }

    // set list cache info.
    SetCacheCount(layoutWrapper, listLayoutProperty->GetCachedCountWithDefault());
    isLayouted_ = false;
}

void ListLayoutAlgorithm::CalcContentOffset(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto property = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(property);
    auto startOffset = property->GetContentStartOffset();
    if (!startOffset.has_value()) {
        contentStartOffset_ = 0.0f;
    }
    auto endOffset = property->GetContentEndOffset();
    if (!endOffset.has_value()) {
        contentEndOffset_ = 0.0f;
    }
    if (!endOffset && !startOffset) {
        return;
    }
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (startOffset) {
        contentStartOffset_ = std::max(pipeline->NormalizeToPx(Dimension(startOffset.value(), DimensionUnit::VP)), 0.0);
    }
    if (endOffset) {
        contentEndOffset_ = std::max(pipeline->NormalizeToPx(Dimension(endOffset.value(), DimensionUnit::VP)), 0.0);
    }
}

void ListLayoutAlgorithm::SetCacheCount(LayoutWrapper* layoutWrapper, int32_t cacheCount)
{
    layoutWrapper->SetCacheCount(cacheCount);
}

void ListLayoutAlgorithm::SetActiveChildRange(LayoutWrapper* layoutWrapper,
    int32_t cacheStart, int32_t cacheEnd, bool show)
{
    if (measureInNextFrame_) {
        return;
    }
    if (itemPosition_.empty()) {
        layoutWrapper->SetActiveChildRange(-1, -1);
        return;
    }
    auto start = !isStackFromEnd_ ? itemStartIndex_ + itemPosition_.begin()->first :
                                    itemStartIndex_ + totalItemCount_ - itemPosition_.rbegin()->first - 1;
    auto end = !isStackFromEnd_ ? itemStartIndex_ + itemPosition_.rbegin()->first :
                                  itemStartIndex_ + totalItemCount_ - itemPosition_.begin()->first - 1;
    if (draggingIndex_ >= 0) {
        start = std::min(start, draggingIndex_);
        end = std::max(end, draggingIndex_);
    }
    LostChildFocusToSelf(layoutWrapper, start - cacheStart, end + cacheEnd);
    layoutWrapper->SetActiveChildRange(start, end, cacheStart, cacheEnd, show);
}

void ListLayoutAlgorithm::LostChildFocusToSelf(LayoutWrapper* layoutWrapper, int32_t start, int32_t end)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    CHECK_NULL_VOID(focusHub->IsCurrentFocus());
    auto listPattern = host->GetPattern<ListPattern>();
    CHECK_NULL_VOID(listPattern);
    auto focusIndex = listPattern->GetFocusIndex();
    CHECK_NULL_VOID(focusIndex.has_value());
    if (focusIndex.value() >= start - itemStartIndex_ && focusIndex.value() <= end) {
        return;
    }
    int32_t indexInList = -1;
    auto childFocusHub = focusHub->GetLastWeakFocusNode().Upgrade();
    CHECK_NULL_VOID(childFocusHub);
    auto focusNode = childFocusHub->GetFrameNode();
    CHECK_NULL_VOID(focusNode);
    auto childItemPattern = focusNode->GetPattern<ListItemPattern>();
    if (!childItemPattern) {
        auto listItemGroupPattern = focusNode->GetPattern<ListItemGroupPattern>();
        CHECK_NULL_VOID(listItemGroupPattern);
        indexInList = listItemGroupPattern->GetIndexInList();
    } else {
        indexInList = childItemPattern->GetIndexInList();
    }
    if (indexInList == focusIndex && childFocusHub->IsCurrentFocus()) {
        listPattern->HandleFocusParentCheck(childFocusHub, focusHub);
    }
}

bool ListLayoutAlgorithm::CheckNeedMeasure(const RefPtr<LayoutWrapper>& layoutWrapper) const
{
    if (layoutWrapper->CheckNeedForceMeasureAndLayout() || !IsListLanesEqual(layoutWrapper) ||
        layoutWrapper->IsIgnoreOptsValid()) {
        return true;
    }
    return CheckLayoutConstraintChanged(layoutWrapper);
}

bool ListLayoutAlgorithm::CheckLayoutConstraintChanged(const RefPtr<LayoutWrapper>& layoutWrapper) const
{
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    auto constraint = geometryNode->GetParentLayoutConstraint();
    CHECK_NULL_RETURN(constraint, true);
    bool isGroup = layoutWrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    return isGroup ? constraint.value() != GetGroupLayoutConstraint() : constraint.value() != childLayoutConstraint_;
}

bool ListLayoutAlgorithm::IsListLanesEqual(const RefPtr<LayoutWrapper>& wrapper) const
{
    CHECK_NULL_RETURN(listLayoutProperty_, true);
    auto groupProps = AceType::DynamicCast<ListItemGroupLayoutProperty>(wrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(groupProps, true);
    return groupProps->IsListLanesEqual(listLayoutProperty_->GetLanes(),
        listLayoutProperty_->GetLaneMinLength(), listLayoutProperty_->GetLaneMaxLength());
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
        auto wrapper = GetListItem(layoutWrapper, pos.first, false);
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
        auto wrapper = GetListItem(layoutWrapper, pos.first);
        if (!wrapper) {
            ReportGetChildError("ClearAllItemPosition", pos.first);
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
    float chainOffset = GetChainOffset(startIndex);
    if (startIndex == 0) {
        return itemPosition_.begin()->second.startPos + chainOffset;
    }
    return itemPosition_.begin()->second.startPos + chainOffset - spaceWidth_;
}

void ListLayoutAlgorithm::BeginLayoutForward(float startPos, LayoutWrapper* layoutWrapper)
{
    if (!jumpIndex_.has_value()) {
        return;
    }
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
    if (!jumpIndex_.has_value()) {
        return;
    }
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
    auto wrapper = GetListItem(layoutWrapper, jumpIndex);
    if (!wrapper) {
        ReportGetChildError("HandleJumpAuto", jumpIndex);
        return;
    }
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
            BeginLayoutForward(contentStartOffset, layoutWrapper);
        } else {
            scrollAutoType_ = ScrollAutoType::END;
            BeginLayoutBackward(contentMainSize_ - contentEndOffset, layoutWrapper);
        }
    } else if (jumpIndex >= endIndex) {
        float mainLen = childrenSize_ ?
            GetChildHeight(layoutWrapper, jumpIndex) : MeasureAndGetChildHeight(layoutWrapper, jumpIndex, false);
        if (GreatOrEqual(mainLen, contentMainSize_ - contentStartOffset - contentEndOffset)) {
            scrollAutoType_ = ScrollAutoType::START;
            BeginLayoutForward(contentStartOffset, layoutWrapper);
        } else {
            scrollAutoType_ = ScrollAutoType::END;
            BeginLayoutBackward(contentMainSize_ - contentEndOffset, layoutWrapper);
        }
    }
}

void ListLayoutAlgorithm::HandleJumpCenter(LayoutWrapper* layoutWrapper)
{
    int32_t index = GetLanesFloor(layoutWrapper, jumpIndex_.value());
    auto wrapper = GetListItem(layoutWrapper, index);
    if (!wrapper) {
        ReportGetChildError("HandleJumpCenter", index);
    }
    bool isGroup = wrapper && wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup && jumpIndexInGroup_.has_value()) {
        int32_t indexInGroup = jumpIndexInGroup_.value();
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, index, 0.0f, true, listLayoutProperty, false);
        wrapper->Measure(GetGroupLayoutConstraint());
        itemPosition_[index] = GetListItemGroupPosition(wrapper, indexInGroup);
        CheckGroupMeasureBreak(wrapper);
        if (!measureInNextFrame_ && LessNotEqual(GetEndPosition(), endMainPos_)) {
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
    if (!measureInNextFrame_ && GreatNotEqual(GetStartPosition(), startMainPos_)) {
        LayoutBackward(layoutWrapper, index - 1, GetStartPosition());
    }
    if (!measureInNextFrame_ && (GetEndIndex() < totalItemCount_ - 1) &&
        LessNotEqual(GetEndPosition(), endMainPos_ - contentEndOffset_)) {
        LayoutForward(layoutWrapper, GetEndIndex() + 1, GetEndPosition());
    }
}

void ListLayoutAlgorithm::HandleJumpStart(LayoutWrapper* layoutWrapper)
{
    auto wrapper = GetListItem(layoutWrapper, jumpIndex_.value());
    if (!wrapper) {
        ReportGetChildError("HandleJumpStart", jumpIndex_.value());
    }
    bool isGroup = wrapper && wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup && jumpIndexInGroup_.has_value()) {
        int32_t indexInGroup = jumpIndexInGroup_.value();
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, jumpIndex_.value(), 0.0f, true, listLayoutProperty, false);
        wrapper->Measure(GetGroupLayoutConstraint());
        itemPosition_[jumpIndex_.value()] = GetListItemGroupPosition(wrapper, indexInGroup);
        CheckGroupMeasureBreak(wrapper);
        if (!measureInNextFrame_ && LessNotEqual(GetEndPosition(), endMainPos_)) {
            LayoutForward(layoutWrapper, jumpIndex_.value() + 1, GetEndPosition());
        }
        if (!measureInNextFrame_ && GetStartIndex() > 0 && GreatNotEqual(GetStartPosition(), startMainPos_)) {
            LayoutBackward(layoutWrapper, GetStartIndex() - 1, GetStartPosition());
        }
    } else {
        BeginLayoutForward(IsScrollSnapAlignCenter(layoutWrapper) ? 0.0f : contentStartOffset_, layoutWrapper);
    }
}

void ListLayoutAlgorithm::HandleJumpEnd(LayoutWrapper* layoutWrapper)
{
    auto wrapper = GetListItem(layoutWrapper, jumpIndex_.value());
    if (!wrapper) {
        ReportGetChildError("HandleJumpEnd", jumpIndex_.value());
    }
    bool isGroup = wrapper && wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup && jumpIndexInGroup_.has_value()) {
        int32_t indexInGroup = jumpIndexInGroup_.value();
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        SetListItemGroupParam(wrapper, jumpIndex_.value(), contentMainSize_, true, listLayoutProperty, false);
        wrapper->Measure(GetGroupLayoutConstraint());
        itemPosition_[jumpIndex_.value()] = GetListItemGroupPosition(wrapper, indexInGroup);
        CheckGroupMeasureBreak(wrapper);
        if (!measureInNextFrame_ && GreatNotEqual(GetStartPosition(), startMainPos_)) {
            LayoutBackward(layoutWrapper, jumpIndex_.value() - 1, GetStartPosition());
        }
        if (!measureInNextFrame_ && GetEndIndex() <= totalItemCount_ -1 &&
            LessNotEqual(GetEndPosition(), endMainPos_)) {
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
    auto wrapper = GetListItem(layoutWrapper, jumpIndex);
    if (!wrapper) {
        ReportGetChildError("CheckNoNeedJumpListItemGroup", jumpIndex);
        return true;
    }
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
    auto wrapper = GetListItem(layoutWrapper, jumpIndex);
    if (!wrapper) {
        ReportGetChildError("NoNeedJump", jumpIndex);
        return true;
    }
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
    auto wrapper = GetListItem(layoutWrapper, childIndex);
    if (!wrapper) {
        ReportGetChildError("MeasureAndGetChildHeight", childIndex);
        return 0.0f;
    }
    bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup) {
        auto listLayoutProperty =
            AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
        // true: layout forward, 0.0f: layout start position.
        SetListItemGroupParam(wrapper, childIndex, 0.0f, true, listLayoutProperty, groupLayoutAll);
    }
    wrapper->Measure(childLayoutConstraint_);
    float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    if (isGroup) {
        CheckGroupMeasureBreak(wrapper);
    }
    return mainLen;
}

std::pair<int32_t, float> ListLayoutAlgorithm::FindIndexAndDeltaInPosMap(float delta) const
{
    // If cannot find or inappropriate, return index -1 and delta 0.f.
    // If a suitable location can be found based on posMap_, return the corresponding index and delta.
    // The delta and index in the return value satisfies the following constraints:
    // 1) delta >= -spaceWidth_;
    // 2) delta < posMap[index].mainSize.
    if (!posMap_) {
        return { -1, 0.f };
    }
    // itemPosition_ has been checked nonNull before the func is called.
    int32_t curIndex = itemPosition_.begin()->first;
    float startPos = itemPosition_.begin()->second.startPos;
    // Consume a portion of delta to align item with the top of the List.
    if (Negative(delta) && LessOrEqual(startPos, delta)) {
        return { curIndex, delta - startPos };
    }
    delta -= startPos;
    float curPos = posMap_->GetPositionInfo(curIndex).mainPos;
    float curSize = posMap_->GetPositionInfo(curIndex).mainSize;
    // The abs value of the input param of the func is greater than 2 * contentMainSize_, so
    // the delta here must not be 0.f
    int32_t step = Negative(delta) ? -1 : 1;
    while (!Negative(curPos)) { // if curIndex
        if (LessOrEqual(-spaceWidth_, delta) && LessNotEqual(delta, curSize)) {
            return { curIndex, delta };
        }
        curIndex += step;
        curPos = posMap_->GetPositionInfo(curIndex).mainPos;
        curSize = posMap_->GetPositionInfo(curIndex).mainSize;
        float gap = curSize + spaceWidth_;
        delta -= (step > 0 ? gap : -gap);
    }
    return { -1, 0.f };
}

bool ListLayoutAlgorithm::CanUseInfoInPosMap(int32_t index, float delta) const
{
    if (index < 0 || index > totalItemCount_ - 1 || !posMap_) {
        return false;
    }
    const auto& info = posMap_->GetPositionInfo(index);
    if (info.isGroup && GreatNotEqual(info.mainSize, contentMainSize_ * 2.0f)) {
        return false;
    }
    return true;
}

void ListLayoutAlgorithm::CheckJumpToIndex()
{
    if (jumpIndex_.has_value() || !isNeedCheckOffset_ || childrenSize_) {
        return;
    }
    if (LessOrEqual(std::abs(currentDelta_), contentMainSize_ * 2.0f) || itemPosition_.empty()) {
        return;
    }
    auto [index, delta] = FindIndexAndDeltaInPosMap(currentDelta_);
    if (CanUseInfoInPosMap(index, delta)) {
        jumpIndex_ = index;
        currentDelta_ = delta;
        isNeedCheckOffset_ = false;
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
        items = std::min(items, totalItemCount_ - 1 - targetIndex);
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
        auto groupWrapper = GetListItem(layoutWrapper, jumpIndex_.value());
        if (!groupWrapper) {
            ReportGetChildError("CheckJumpValid", jumpIndex_.value());
            return false;
        }
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
    auto wrapper = GetListItem(layoutWrapper, startIndex);
    if (!wrapper) {
        ReportGetChildError("CheckAndMeasureStartItem", startIndex);
        return;
    }
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
    measureInNextFrame_ = itemGroup->GroupMeasureInNextFrame();
    startPos = itemGroup->GetRefPos();
    ListItemInfo itemInfo;
    if (forwardLayout) {
        itemInfo = { id, startPos, startPos + childrenSize_->GetChildSize(startIndex, isStackFromEnd_), isGroup };
    } else {
        itemInfo = { id, startPos - childrenSize_->GetChildSize(startIndex, isStackFromEnd_), startPos, isGroup };
    }
    firstItemInfo_ = std::make_pair(startIndex, itemInfo);
}

void ListLayoutAlgorithm::GetStartIndexInfo(int32_t& index, float& pos, bool& isGroup)
{
    auto it = itemPosition_.begin();
    if (!overScrollFeature_) {
        auto nextIt = it;
        ++nextIt;
        while (nextIt != itemPosition_.end() &&
            LessNotEqual(it->second.endPos + GetChainOffset(it->first), startMainPos_)) {
            it = nextIt;
            ++nextIt;
        }
    }
    index = std::min(it->first, totalItemCount_ - 1);
    pos = it->second.startPos;
    isGroup = it->second.isGroup;
}

void ListLayoutAlgorithm::GetEndIndexInfo(int32_t& index, float& pos, bool& isGroup)
{
    auto it = itemPosition_.rbegin();
    if (!overScrollFeature_ && NearEqual(contentMainSize_, prevContentMainSize_)) {
        auto nextIt = it;
        ++nextIt;
        while (nextIt != itemPosition_.rend() &&
            GreatNotEqual(it->second.startPos + GetChainOffset(it->first), endMainPos_)) {
            it = nextIt;
            ++nextIt;
        }
    }
    index = std::min(it->first, totalItemCount_ - 1);
    pos = it->second.endPos;
    isGroup = it->second.isGroup;
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
    if (!isLayouted_) {
        noLayoutedItems_ = std::move(itemPosition_);
        itemPosition_ = pattern->GetItemPosition();
    }
    auto prevTotalItemCount = pattern->GetMaxListItemIndex() + 1;
    ReverseItemPosition(itemPosition_, prevTotalItemCount, prevContentMainSize_);
    ReverseItemPosition(cachedItemPosition_, prevTotalItemCount, prevContentMainSize_);
    preStartIndex_ = isStackFromEnd_ ? prevTotalItemCount - pattern->GetEndIndexInItemPosition() - 1:
                                       pattern->GetStartIndexInItemPosition();
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
            jumpIndex_ = isStackFromEnd_ ? totalItemCount_ - jumpIndex_.value() - 1 : jumpIndex_.value();
        }
    }
    if (targetIndex_) {
        if (targetIndex_.value() == LAST_ITEM) {
            targetIndex_ = totalItemCount_ - 1;
        }
        targetIndex_ = isStackFromEnd_ ? totalItemCount_ - targetIndex_.value() - 1 : targetIndex_.value();
        if ((targetIndex_.value() < 0) || (targetIndex_.value() >= totalItemCount_)) {
            targetIndex_.reset();
        }
        targetIndexStaged_ = targetIndex_;
    }
    if (!itemPosition_.empty()) {
        GetStartIndexInfo(startIndex, startPos, startItemIsGroup);
        GetEndIndexInfo(endIndex, endPos, endItemIsGroup);
        itemTotalSize = GetEndPosition() - GetStartPosition();
        if (GetStartIndex() > totalItemCount_ - 1 && !jumpIndex_.has_value()) {
            jumpIndex_ = totalItemCount_ - 1;
            scrollAlign_ = ScrollAlign::END;
        }
        UpdateSnapCenterContentOffset(layoutWrapper);
        if (IsScrollSnapAlignCenter(layoutWrapper) && draggingIndex_ < 0) {
            midIndex = GetMidIndex(layoutWrapper, true);
            midItemMidPos = (itemPosition_[midIndex].startPos + itemPosition_[midIndex].endPos) / 2.0f -
                            prevContentMainSize_ / 2.0f + contentMainSize_ / 2.0f;
            midIndex = std::min(midIndex, totalItemCount_ - 1);
        } else if (scrollSnapAlign_ == ScrollSnapAlign::START && pattern->GetScrollState() == ScrollState::IDLE) {
            auto res = GetSnapStartIndexAndPos();
            startIndex = res.first;
            startPos = res.second;
        } else if (scrollSnapAlign_ == ScrollSnapAlign::END && pattern->GetScrollState() == ScrollState::IDLE) {
            auto res = GetSnapEndIndexAndPos();
            needLayoutBackward = res.first != -1;
            endIndex = needLayoutBackward ? res.first : endIndex;
            endPos = needLayoutBackward ? res.second : endPos;
        }
        needLayoutBackward = needLayoutBackward || (draggingIndex_ >= 0 &&
            revertIndex(draggingIndex_) <= startIndex && NearEqual(prevContentMainSize_, contentMainSize_));
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
        bool overScrollTop =
            startIndex == 0 && GreatNotEqual(startPos + GetChainOffset(0), startMainPos_ + contentStartOffset_);
        bool overScrollBottom = (endIndex == totalItemCount_ - 1) &&
            LessNotEqual(endPos + GetChainOffset(totalItemCount_ - 1), prevContentMainSize_ - prevContentEndOffset_);
        float midItemHeight = 0.0f;
        if (IsScrollSnapAlignCenter(layoutWrapper) && draggingIndex_ < 0) {
            midItemHeight = childrenSize_ ?
                GetChildHeight(layoutWrapper, midIndex) : MeasureAndGetChildHeight(layoutWrapper, midIndex);
            startIndex = midIndex;
            endIndex = midIndex;
        }
        if ((NonNegative(currentOffset_) || overScrollFeature_) && !needLayoutBackward) {
            startIndex = GetLanesFloor(layoutWrapper, startIndex);
            if (overScrollTop && !canOverScrollStart_) {
                startPos = startMainPos_ + contentStartOffset_;
            }
            if (IsScrollSnapAlignCenter(layoutWrapper) && draggingIndex_ < 0) {
                startPos = midItemMidPos - midItemHeight / 2.0f;
            }
            if (overScrollBottom && GreatNotEqual(contentMainSize_, prevContentMainSize_) &&
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
            if (IsScrollSnapAlignCenter(layoutWrapper) && draggingIndex_ < 0) {
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
    UpdateNoLayoutedItems();
}

void ListLayoutAlgorithm::UpdateNoLayoutedItems()
{
    if (isLayouted_) {
        return;
    }
    for (const auto& item : itemPosition_) {
        noLayoutedItems_.erase(item.first);
    }
    for (const auto& item : recycledItemPosition_) {
        noLayoutedItems_.erase(item.first);
    }
}

LayoutDirection ListLayoutAlgorithm::LayoutDirectionForTargetIndex(LayoutWrapper* layoutWrapper, int startIndex)
{
    CHECK_NULL_RETURN(targetIndex_, LayoutDirection::NONE);
    if (startIndex < targetIndex_.value()) {
        return LayoutDirection::FORWARD;
    } else if (startIndex > targetIndex_.value()) {
        return LayoutDirection::BACKWARD;
    } else if (targetIndexInGroup_.has_value()) {
        auto groupWrapper = GetListItem(layoutWrapper, targetIndex_.value());
        if (!groupWrapper) {
            ReportGetChildError("LayoutDirectionForTargetIndex", targetIndex_.value());
            return LayoutDirection::NONE;
        }
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
    if (scrollSnapAlign_ == ScrollSnapAlign::NONE || childrenSize_) {
        return;
    }
    auto startChild = itemPosition_.begin();
    auto endChild = itemPosition_.rbegin();
    if (startChild != itemPosition_.end() && startChild->second.isGroup) {
        float chainOffset = GetChainOffset(startChild->first);
        CheckListItemGroupRecycle(layoutWrapper, startChild->first, startChild->second.startPos + chainOffset, true);
    }
    if (endChild != itemPosition_.rend() && endChild->second.isGroup) {
        float chainOffset = GetChainOffset(endChild->first);
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
        auto wrapper = GetListItem(layoutWrapper, currentIndex + 1);
        if (!wrapper) {
            ReportGetChildError("LayoutALineForward", currentIndex + 1);
            return 0;
        }
        int32_t id = wrapper->GetHostNode()->GetId();
        ++currentIndex;
        bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        if (isGroup) {
            auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItemGroup:%d, %f", currentIndex, startPos);
            SetListItemGroupParam(wrapper, currentIndex, startPos, true, listLayoutProperty, false);
            wrapper->Measure(childLayoutConstraint_);
            if (LessOrEqual(startPos, 0.0f) || prevMeasureBreak_) {
                AdjustStartPosition(wrapper, startPos);
            }
            CheckGroupMeasureBreak(wrapper);
        } else if (expandSafeArea_ || CheckNeedMeasure(wrapper)) {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d, %f", currentIndex, startPos);
            wrapper->Measure(childLayoutConstraint_);
        }
        float mainLen = childrenSize_ ? childrenSize_->GetChildSize(currentIndex, isStackFromEnd_) :
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
    return 1;
}

int32_t ListLayoutAlgorithm::LayoutALineBackward(LayoutWrapper* layoutWrapper,
    int32_t& currentIndex, float endPos, float& startPos)
{
    if (currentIndex - 1 < 0) {
        return 0;
    }
    if (!firstItemInfo_ || firstItemInfo_.value().first != currentIndex - 1) {
        auto wrapper = GetListItem(layoutWrapper, currentIndex - 1);
        if (!wrapper) {
            ReportGetChildError("LayoutALineBackward", currentIndex - 1);
            return 0;
        }
        int32_t id = wrapper->GetHostNode()->GetId();
        --currentIndex;
        bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        if (isGroup) {
            auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
            SetListItemGroupParam(wrapper, currentIndex, endPos, false, listLayoutProperty, false);
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItemGroup:%d, %f", currentIndex, endPos);
            wrapper->Measure(childLayoutConstraint_);
            CheckGroupMeasureBreak(wrapper);
        } else if (expandSafeArea_ || CheckNeedMeasure(wrapper)) {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d, %f", currentIndex, endPos);
            wrapper->Measure(childLayoutConstraint_);
        }
        float mainLen = childrenSize_ ? childrenSize_->GetChildSize(currentIndex, isStackFromEnd_) :
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
    return 1;
}

void ListLayoutAlgorithm::LayoutForward(LayoutWrapper* layoutWrapper, int32_t startIndex, float startPos)
{
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    float endMainPos = (overScrollFeature_ && startIndex == 0) ?
        std::max(startPos + contentMainSize_ - contentStartOffset_, endMainPos_) : endMainPos_;
    layoutEndMainPos_ = endMainPos;
    float endFixPos = GetLayoutFixOffset();
    auto currentIndex = startIndex - 1;
    auto chainOffset = 0.0f;
    do {
        if (!itemPosition_.empty() && !syncLoad_ && layoutWrapper->ReachResponseDeadline()) {
            measureInNextFrame_ = true;
            return;
        }
        currentStartPos = currentEndPos;
        int32_t count = LayoutALineForward(layoutWrapper, currentIndex, currentStartPos, currentEndPos);
        if (count == 0) {
            break;
        }
        if (currentIndex >= 0 && currentIndex < (totalItemCount_ - 1)) {
            currentEndPos += spaceWidth_;
        }
        chainOffset = GetChainOffset(currentIndex);
        // reach the valid target index
        if (forwardFeature_ && targetIndex_ && currentIndex >= targetIndex_.value()) {
            endMainPos = layoutEndMainPos_.value_or(endMainPos_);
            forwardFeature_ = false;
        }
    } while (LessNotEqual(currentEndPos + chainOffset, endMainPos + endFixPos) || forwardFeature_);
    currentEndPos += chainOffset;

    while (itemPosition_.size() > 1 && !targetIndex_) {
        auto pos = itemPosition_.rbegin();
        float chainDelta = GetChainOffset(pos->first);
        if (GreatNotEqual(pos->second.endPos + chainDelta, endMainPos) &&
            GreatOrEqual(pos->second.startPos + chainDelta, endMainPos)) {
            recycledItemPosition_.emplace(pos->first, pos->second);
            itemPosition_.erase(pos->first);
        } else {
            break;
        }
    }
    // adjust offset.
    UpdateSnapCenterContentOffset(layoutWrapper);
    if (LessNotEqual(currentEndPos, endMainPos - contentEndOffset_) && !itemPosition_.empty()) {
        endMainPos_ = currentEndPos + contentEndOffset_;
        startMainPos_ = endMainPos_ - contentMainSize_;
        ReMeasureListItemGroup(layoutWrapper, true);
        auto firstItemTop = itemPosition_.begin()->second.startPos;
        auto itemTotalSize = currentEndPos - firstItemTop + contentEndOffset_ + contentStartOffset_;
        if (LessOrEqual(itemTotalSize, contentMainSize_) && (itemPosition_.begin()->first == 0)) {
            // all items size is less than list.
            if ((GreatOrEqual(firstItemTop, currentOffset_ + contentStartOffset_) && !canOverScrollStart_) ||
                (LessOrEqual(firstItemTop, currentOffset_ + contentStartOffset_) && !canOverScrollEnd_)) {
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
            if (!canOverScrollEnd_ || jumpIndex_.has_value()) {
                currentOffset_ = currentEndPos + contentEndOffset_ - contentMainSize_;
            }
        }
    }
    if ((overScrollFeature_ && (canOverScrollStart_ || canOverScrollEnd_)) || targetIndex_) {
        return;
    }
    // Mark inactive in wrapper.
    for (auto pos = itemPosition_.begin(); pos != itemPosition_.end();) {
        chainOffset = GetChainOffset(pos->first);
        // Don't recycle When the head item is Visibility.None.
        if (GreatNotEqual(pos->second.endPos + chainOffset + endFixPos, startMainPos_) ||
            GreatOrEqual(pos->second.startPos + chainOffset + endFixPos, startMainPos_)) {
            if (pos->second.isGroup) {
                CheckListItemGroupRecycle(layoutWrapper, pos->first, pos->second.startPos + chainOffset, true);
            }
            break;
        }
        recycledItemPosition_.emplace(pos->first, pos->second);
        pos = itemPosition_.erase(pos);
    }
}

void ListLayoutAlgorithm::LayoutBackward(LayoutWrapper* layoutWrapper, int32_t endIndex, float endPos)
{
    float currentStartPos = endPos;
    float currentEndPos = 0.0f;
    float startMainPos = (overScrollFeature_ && endIndex == totalItemCount_ - 1) ?
        std::min(endPos - contentMainSize_ + contentEndOffset_, startMainPos_) : startMainPos_;
    layoutStartMainPos_ = startMainPos;
    float startFixPos = GetLayoutFixOffset();
    auto currentIndex = endIndex + 1;
    auto chainOffset = 0.0f;
    do {
        if (!itemPosition_.empty() && !syncLoad_ && layoutWrapper->ReachResponseDeadline()) {
            measureInNextFrame_ = true;
            return;
        }
        currentEndPos = currentStartPos;
        int32_t count = LayoutALineBackward(layoutWrapper, currentIndex, currentEndPos, currentStartPos);
        if (count == 0) {
            break;
        }
        if (currentIndex > 0) {
            currentStartPos = currentStartPos - spaceWidth_;
        }
        chainOffset = GetChainOffset(currentIndex);
        // reach the valid target index
        if (backwardFeature_ && targetIndex_ && LessOrEqual(currentIndex, targetIndex_.value())) {
            startMainPos = layoutStartMainPos_.value_or(startMainPos_);
            backwardFeature_ = false;
        }
    } while (GreatNotEqual(currentStartPos + chainOffset + startFixPos, startMainPos) || backwardFeature_);

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
        if ((!canOverScrollStart_ && GreatOrEqual(currentStartPos, contentStartOffset_ + currentOffset_)) ||
            jumpIndex_.has_value()) {
            currentOffset_ = currentStartPos - contentStartOffset_;
        }
        endMainPos_ = currentStartPos - contentStartOffset_ + contentMainSize_;
        startMainPos_ = currentStartPos - contentStartOffset_;
        ReMeasureListItemGroup(layoutWrapper, false);
    }

    if (overScrollFeature_ || targetIndex_) {
        return;
    }
    // Mark inactive in wrapper.
    std::list<int32_t> removeIndexes;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        chainOffset = GetChainOffset(pos->first);
        // Don't recycle When the tail item is Visibility.None.
        if (LessNotEqual(pos->second.startPos + chainOffset - startFixPos, endMainPos_) ||
            LessOrEqual(pos->second.endPos + chainOffset - startFixPos, endMainPos_)) {
            if (pos->second.isGroup) {
                CheckListItemGroupRecycle(layoutWrapper, pos->first, pos->second.endPos + chainOffset, false);
            }
            break;
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
            float chainOffset = GetChainOffset(pos->first);
            if (GreatOrEqual(pos->second.startPos + chainOffset, endMainPos_)) {
                break;
            } else if (!pos->second.isGroup) {
                continue;
            }
            AdjustPostionForListItemGroup(layoutWrapper, axis_, pos->first, forwardLayout);
        }
        return;
    }
    if (LessNotEqual(itemPosition_.begin()->second.endPos, currentOffset_)) {
        for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); pos++) {
            float chainOffset = GetChainOffset(pos->first);
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

void ListLayoutAlgorithm::FixPredictSnapPos()
{
    if (!predictSnapEndPos_.has_value() || itemPosition_.empty()) {
        return;
    }
    float predictEndPos = predictSnapEndPos_.value();
    int32_t predictIndex = -1;
    int32_t curIndex = -1; // here invalid.
    switch (scrollSnapAlign_) {
        case ScrollSnapAlign::START:
            FindPredictSnapIndexInItemPositionsStart(predictEndPos, predictIndex, curIndex);
            break;
        case ScrollSnapAlign::CENTER:
            FindPredictSnapIndexInItemPositionsCenter(predictEndPos, predictIndex, curIndex);
            break;
        case ScrollSnapAlign::END:
            FindPredictSnapIndexInItemPositionsEnd(predictEndPos, predictIndex, curIndex);
            break;
        default:
            return;
    }
    if (GetStartIndex() <= predictIndex && predictIndex <= GetEndIndex()) {
        predictEndPos = CalculatePredictSnapEndPositionByIndex(predictIndex, scrollSnapAlign_);
    }
    if (!NearEqual(predictEndPos, predictSnapEndPos_.value())) {
        predictSnapEndPos_ = predictEndPos;
    }
}

void ListLayoutAlgorithm::FixPredictSnapOffset(const RefPtr<ListLayoutProperty>& listLayoutProperty)
{
    if (!predictSnapOffset_.has_value() || itemPosition_.empty()) {
        return;
    }
    if (scrollSnapAlign_ == ScrollSnapAlign::NONE) {
        predictSnapOffset_.reset();
        predictSnapEndPos_.reset();
        return;
    }

    auto predictEndPos = totalOffset_ - predictSnapOffset_.value();
    int32_t endIndex = FindPredictSnapEndIndexInItemPositions(predictEndPos, scrollSnapAlign_);
    if (GetStartIndex() <= endIndex && endIndex <= GetEndIndex()) {
        predictEndPos = CalculatePredictSnapEndPositionByIndex(endIndex, scrollSnapAlign_);
        predictSnapOffset_ = totalOffset_ - predictEndPos;
        predictSnapEndPos_ = predictEndPos;
    } else {
        if (IsUniformHeightProbably()) {
            if (scrollSnapAlign_ == ScrollSnapAlign::START) {
                FixPredictSnapOffsetAlignStart();
            } else if (scrollSnapAlign_ == ScrollSnapAlign::CENTER) {
                FixPredictSnapOffsetAlignCenter();
            } else if (scrollSnapAlign_ == ScrollSnapAlign::END) {
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
    auto scrollSnapAlign = listLayoutProperty->GetScrollSnapAlign().value_or(ScrollSnapAlign::NONE);
    if (scrollSnapAlign == ScrollSnapAlign::CENTER) {
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
        int32_t lanes = 1;
        if (pos.isGroup) {
            startIndex = index + 1;
        } else {
            laneIndex = (index - startIndex) % GetLanes();
            lanes = GetLanes();
        }

        float laneGutter = GetLaneGutter();
        crossOffset = CalculateLaneCrossOffset(crossSize, childCrossSize * lanes, pos.isGroup);
        crossOffset += ((crossSize + laneGutter) / GetLanes()) * laneIndex;
    } else {
        crossOffset = CalculateLaneCrossOffset(crossSize, childCrossSize, pos.isGroup);
    }
    auto chainOffset = GetChainOffset(index);
    auto startPos = !isStackFromEnd_ ? pos.startPos + chainOffset : contentMainSize_ - pos.endPos - chainOffset;
    auto endPos = !isStackFromEnd_ ? pos.endPos + chainOffset : contentMainSize_ - pos.startPos - chainOffset;
    if (isReverse_) {
        if (axis_ == Axis::VERTICAL) {
            auto size = wrapper->GetGeometryNode()->GetMarginFrameSize();
            offset = offset + OffsetF(crossSize - crossOffset - size.Width(), startPos);
        } else {
            offset = offset + OffsetF(contentMainSize_ - endPos, crossOffset);
        }
    } else {
        if (axis_ == Axis::VERTICAL) {
            offset = offset + OffsetF(crossOffset, startPos);
        } else {
            offset = offset + OffsetF(startPos, crossOffset);
        }
    }
    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    index = isStackFromEnd_ ? totalItemCount_ - index - 1 : index;
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
            if (scrollSnapAlign_ != ScrollSnapAlign::CENTER) {
                value.contentStartOffset = contentStartOffset_;
                value.contentEndOffset = contentEndOffset_;
            }
            PostIdleTaskV2(host, { items, childLayoutConstraint_, GetGroupLayoutConstraint() }, value, show);
        } else {
            auto pattern = host->GetPattern<ListPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetPredictLayoutParamV2(std::nullopt);
        }
    } else {
        ResetLayoutItem(layoutWrapper);
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

int32_t ListLayoutAlgorithm::GetListItemGroupItemCount(const RefPtr<LayoutWrapper>& wrapper) const
{
    CHECK_NULL_RETURN(wrapper, 0);
    auto layoutAlgorithmWrapper = wrapper->GetLayoutAlgorithm(true);
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, 0);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(itemGroup, 0);
    int32_t itemCount = itemGroup->GetListItemCount();
    return itemCount == 0 ? 1 : itemCount;
}

bool ListLayoutAlgorithm::IsNeedSyncLoad(const RefPtr<ListLayoutProperty>& property) const
{
    bool syncLoad = property->GetSyncLoad().value_or(!FeatureParam::IsSyncLoadEnabled());
    return !(!syncLoad && NearZero(currentDelta_) && !targetIndex_.has_value() && mainSizeIsDefined_);
}

void ListLayoutAlgorithm::CheckGroupMeasureBreak(const RefPtr<LayoutWrapper>& wrapper)
{
    if (syncLoad_) {
        return;
    }
    CHECK_NULL_VOID(wrapper);
    auto layoutAlgorithmWrapper = wrapper->GetLayoutAlgorithm(true);
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(itemGroup);
    if (itemGroup->GroupMeasureInNextFrame()) {
        measureInNextFrame_ = true;
    }
}

void ListLayoutAlgorithm::ResetLayoutItem(LayoutWrapper* layoutWrapper)
{
    ResetUnLayoutedItems(layoutWrapper, recycledItemPosition_);
    ResetUnLayoutedItems(layoutWrapper, noLayoutedItems_);
}

void ListLayoutAlgorithm::ResetUnLayoutedItems(LayoutWrapper* layoutWrapper, PositionMap& positionMap)
{
    for (auto& pos : positionMap) {
        auto wrapper = GetListItem(layoutWrapper, pos.first);
        if (!wrapper) {
            ReportGetChildError("ResetLayoutItem", pos.first);
        }
        pos.second.startPos -= currentOffset_;
        pos.second.endPos -= currentOffset_;
        if (pos.second.isGroup) {
            pos.second.groupInfo = GetListItemGroupLayoutInfo(wrapper);
            if (wrapper && wrapper->GetHostNode() && wrapper->GetHostNode()->GetPattern<ListItemGroupPattern>()) {
                auto groupPattern = wrapper->GetHostNode()->GetPattern<ListItemGroupPattern>();
                groupPattern->ClearItemPosition();
            }
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
    CalculateTotalCountByRepeat(layoutWrapper);
    listItemAlign_ = listProps->GetListItemAlign().value_or(V2::ListItemAlign::START);
    int32_t startIndex = GetStartIndex();
    isReverse_ = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection() == TextDirection::RTL;

    // layout items.
    int32_t itemCount = 0;
    for (auto& pos : itemPosition_) {
        auto wrapper = GetListItem(layoutWrapper, pos.first);
        if (!wrapper) {
            ReportGetChildError("Layout", pos.first);
            continue;
        }
        pos.second.startPos -= currentOffset_;
        pos.second.endPos -= currentOffset_;
        if (pos.second.isGroup) {
            pos.second.groupInfo = GetListItemGroupLayoutInfo(wrapper);
            itemCount += GetListItemGroupItemCount(wrapper);
        } else {
            pos.second.groupInfo.reset();
            itemCount++;
        }
        LayoutItem(wrapper, pos.first, pos.second, startIndex, crossSize);
        auto childLayoutProperty = wrapper->GetLayoutProperty();
        if (expandSafeArea_ || wrapper->CheckNeedForceMeasureAndLayout() || wrapper->IsIgnoreOptsValid()) {
            wrapper->Layout();
        } else {
            SyncGeometry(wrapper);
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(wrapper);
        if (frameNode) {
            auto childNode = layoutWrapper->GetHostNode();
            if (pos.second.isGroup && childNode && childNode->GetSuggestOpIncActivatedOnce()) {
                frameNode->SetSuggestOpIncActivatedOnce();
            } else if (!pos.second.isGroup) {
                frameNode->MarkAndCheckNewOpIncNode(axis_);
            }
        }
    }
    auto cacheCount = listProps->GetCachedCountWithDefault();
    if (!listProps->HasCachedCount()) {
        int32_t newCacheCount = UpdateDefaultCachedCount(cacheCount, itemCount);
        listProps->SetDefaultCachedCount(newCacheCount);
    }
    ProcessCacheCount(layoutWrapper, cacheCount, listProps->GetShowCachedItemsValue(false));
    FixItemLayoutOffset(layoutWrapper);
    LayoutHeader(layoutWrapper, paddingOffset_, crossSize);
    UpdateOverlay(layoutWrapper);
    ProcessStackFromEnd();
    ReverseItemPosition(itemPosition_, totalItemCount_, contentMainSize_);
    ReverseItemPosition(cachedItemPosition_, totalItemCount_, contentMainSize_);
    ReverseItemPosition(recycledItemPosition_, totalItemCount_, contentMainSize_);
    totalOffset_ += currentOffset_;
    FixPredictSnapPos();
    FixPredictSnapOffset(listProps);
    isLayouted_ = true;
}

void ListLayoutAlgorithm::UpdateOverlay(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    bool defaultFadingEdge = paintProperty->GetDefaultFadingEdge().value_or(false);
    if (!paintProperty->GetFadingEdge().value_or(defaultFadingEdge)) {
        return;
    }
    auto overlayNode = frameNode->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto listFrameSize = geometryNode->GetFrameSize(true);
    auto overlayGeometryNode = overlayNode->GetGeometryNode();
    CHECK_NULL_VOID(overlayGeometryNode);
    overlayGeometryNode->SetFrameSize(listFrameSize);
}

float ListLayoutAlgorithm::CalculateLaneCrossOffset(float crossSize, float childCrossSize, bool isGroup)
{
    float delta = isGroup ? crossSize - childCrossSize : crossSize - GetLaneGutter() - childCrossSize;
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
                jumpIndexInGroup_ = isStackFromEnd_ ? LAST_ITEM : 0;
            } else if (!forwardLayout && (scrollAlign_ == ScrollAlign::END ||
                (scrollAlign_ == ScrollAlign::AUTO && scrollAutoType_ == ScrollAutoType::END))) {
                jumpIndexInGroup_ = isStackFromEnd_ ? 0 : LAST_ITEM;
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
    itemGroup->SetNeedSyncLoad(syncLoad_);
    if (scrollSnapAlign_ != ScrollSnapAlign::CENTER) {
        itemGroup->SetContentOffset(contentStartOffset_, contentEndOffset_);
    }
    SetListItemGroupJumpIndex(itemGroup, forwardLayout, index);

    if (groupNeedAllLayout || (targetIndex_ && targetIndex_.value() == index) ||
        (scrollSnapAlign_ != ScrollSnapAlign::NONE && !childrenSize_)) {
        itemGroup->SetNeedAllLayout();
    } else if (forwardFeature_ || backwardFeature_) {
        itemGroup->CheckNeedAllLayout(layoutWrapper, forwardLayout);
    }
    if (CheckNeedMeasure(layoutWrapper)) {
        itemGroup->ResetCachedItemPosition();
        itemGroup->ResetCachedIndex();
        if (layoutWrapper->GetHostNode() && layoutWrapper->GetHostNode()->GetPattern<ListItemGroupPattern>()) {
            auto groupPattern = layoutWrapper->GetHostNode()->GetPattern<ListItemGroupPattern>();
            groupPattern->SetRecache(true);
        }
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
    measureInNextFrame_ = itemGroup->GroupMeasureInNextFrame();
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
    auto wrapper = GetListItem(layoutWrapper, index);
    if (!wrapper) {
        ReportGetChildError("CheckListItemGroupRecycle", index);
        return;
    }
    auto algorithmWrapper = wrapper->GetLayoutAlgorithm();
    CHECK_NULL_VOID(algorithmWrapper);
    auto itemGroup = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(algorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(itemGroup);
    itemGroup->CheckRecycle(wrapper, startMainPos_, endMainPos_, referencePos, forwardLayout);
}

void ListLayoutAlgorithm::AdjustPostionForListItemGroup(LayoutWrapper* layoutWrapper, Axis axis, int32_t index,
    bool forwardLayout)
{
    auto wrapper = GetListItem(layoutWrapper, index);
    if (!wrapper) {
        ReportGetChildError("AdjustPostionForListItemGroup", index);
        return;
    }
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
    measureInNextFrame_ = itemGroup->GroupMeasureInNextFrame();
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

void ListLayoutAlgorithm::SyncGeometry(RefPtr<LayoutWrapper>& wrapper, bool isDirty)
{
    CHECK_NULL_VOID(wrapper);
    auto host = wrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    if (!(isDirty && host->IsGeometrySizeChange())) {
        host->ForceSyncGeometryNode();
    } else if (host->IsActive()) {
        DirtySwapConfig emptyConfig;
        host->SyncGeometryNode(true, emptyConfig);
    }
    host->ResetLayoutAlgorithm();
    host->RebuildRenderContextTree();
}

// return current CachedCount and max CacheCount
CachedIndexInfo ListLayoutAlgorithm::GetLayoutGroupCachedCount(LayoutWrapper* layoutWrapper,
    const RefPtr<LayoutWrapper>& wrapper, int32_t forwardCache, int32_t backwardCache, int32_t index, bool outOfView)
{
    CachedIndexInfo res;
    auto groupNode = AceType::DynamicCast<FrameNode>(wrapper);
    CHECK_NULL_RETURN(groupNode, res);
    auto group = groupNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(group, res);
    const auto& itemPos = group->GetItemPosition();
    bool reCache = false;
    if (outOfView && recycledItemPosition_.count(index) == 0) {
        reCache = CheckNeedMeasure(wrapper);
    } else if (outOfView) {
        wrapper->SetActive(true);
        wrapper->Layout();
        group->SyncItemsToCachedItemPosition();
    }
    bool forward = forwardCache > -1;
    bool backward = backwardCache > -1;
    if (forward && backward && itemPos.empty()) {
        forward = group->NeedCacheForward(layoutWrapper);
        backward = !forward;
        forwardCache = forward ? forwardCache : -1;
        backwardCache = backward ? backwardCache : -1;
    }
    res = group->UpdateCachedIndex(outOfView, reCache, forwardCache, backwardCache);
    ACE_SCOPED_TRACE("GetLayoutGroupCachedCount forward:%d, %d, backward:%d, %d",
        res.forwardCachedCount, res.forwardCacheMax, res.backwardCachedCount, res.backwardCacheMax);
    if ((group->GetTotalItemCount() == 0 && outOfView) || !group->IsVisible()) {
        if (CheckNeedMeasure(wrapper)) {
            res = {0, 0, 1, 1};
        } else {
            res = {1, 1, 1, 1};
        }
    }
    return res;
}

float ListLayoutAlgorithm::GetLayoutCrossAxisSize(LayoutWrapper* layoutWrapper)
{
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    if (layoutProperty) {
        auto padding = layoutProperty->CreatePaddingAndBorder();
        MinusPaddingToSize(padding, size);
    }
    return GetCrossAxisSize(size, axis_);
}

int32_t ListLayoutAlgorithm::LayoutCachedForward(LayoutWrapper* layoutWrapper,
    int32_t cacheCount, int32_t& cachedCount, int32_t curIndex, std::list<PredictLayoutItem>& predictList, bool show)
{
    float crossSize = GetLayoutCrossAxisSize(layoutWrapper);
    curIndex = itemPosition_.rbegin()->first + 1;
    auto currPos = itemPosition_.rbegin()->second.endPos + spaceWidth_;
    while (cachedCount < cacheCount && curIndex < totalItemCount_) {
        auto wrapper = GetChildByIndex(layoutWrapper, curIndex + itemStartIndex_, !show);
        if (!wrapper) {
            predictList.emplace_back(PredictLayoutItem { curIndex, cachedCount, -1 });
            return curIndex - 1;
        }
        bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        bool isDirty = wrapper->CheckNeedForceMeasureAndLayout() || !IsListLanesEqual(wrapper);
        if (!isGroup && (isDirty || CheckLayoutConstraintChanged(wrapper)) && !wrapper->CheckHasPreMeasured()) {
            predictList.emplace_back(PredictLayoutItem { curIndex, cachedCount, -1 });
        }
        if (!isGroup && isDirty && !wrapper->GetHostNode()->IsLayoutComplete() && !wrapper->CheckHasPreMeasured()) {
            return curIndex - 1;
        }
        auto childSize = wrapper->GetGeometryNode()->GetMarginFrameSize();
        auto endPos = currPos + GetMainAxisSize(childSize, axis_);
        int32_t id = wrapper->GetHostNode()->GetId();
        ListItemInfo pos = { id, currPos, endPos, isGroup };
        currPos = endPos + spaceWidth_;
        auto startIndex = curIndex;
        LayoutItem(wrapper, curIndex, pos, startIndex, crossSize);
        cachedItemPosition_[curIndex] = pos;
        if (isGroup) {
            auto res = GetLayoutGroupCachedCount(
                layoutWrapper, wrapper, cacheCount - cachedCount, -1, curIndex, true);
            if (res.forwardCachedCount < res.forwardCacheMax && res.forwardCachedCount < cacheCount - cachedCount) {
                predictList.emplace_back(PredictLayoutItem { curIndex, cachedCount, -1 });
                return res.forwardCachedCount > 0 ? curIndex : curIndex - 1;
            }
            cachedCount += std::max(res.forwardCacheMax, 1);
        } else {
            cachedCount++;
        }
        ExpandWithSafeAreaPadding(wrapper);
        wrapper->SetActive(show);
        SyncGeometry(wrapper, isDirty);
        curIndex++;
    }
    return curIndex - 1;
}

int32_t ListLayoutAlgorithm::LayoutCachedBackward(LayoutWrapper* layoutWrapper,
    int32_t cacheCount, int32_t& cachedCount, int32_t curIndex, std::list<PredictLayoutItem>& predictList, bool show)
{
    float crossSize = GetLayoutCrossAxisSize(layoutWrapper);
    curIndex = itemPosition_.begin()->first - 1;
    auto currPos = itemPosition_.begin()->second.startPos - spaceWidth_;
    while (cachedCount < cacheCount && curIndex >= 0) {
        auto wrapper = GetChildByIndex(layoutWrapper, curIndex + itemStartIndex_, !show);
        if (!wrapper) {
            predictList.emplace_back(PredictLayoutItem { curIndex, -1, cachedCount });
            return curIndex + 1;
        }
        bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
        bool isDirty = wrapper->CheckNeedForceMeasureAndLayout() || !IsListLanesEqual(wrapper);
        if (!isGroup && (isDirty || CheckLayoutConstraintChanged(wrapper)) && !wrapper->CheckHasPreMeasured()) {
            predictList.emplace_back(PredictLayoutItem { curIndex, -1, cachedCount });
        }
        if (!isGroup && isDirty && !wrapper->GetHostNode()->IsLayoutComplete() && !wrapper->CheckHasPreMeasured()) {
            return curIndex + 1;
        }
        auto childSize = wrapper->GetGeometryNode()->GetMarginFrameSize();
        auto startPos = currPos - GetMainAxisSize(childSize, axis_);
        int32_t id = wrapper->GetHostNode()->GetId();
        ListItemInfo pos = { id, startPos, currPos, isGroup };
        currPos = startPos - spaceWidth_;
        auto startIndex = curIndex;
        LayoutItem(wrapper, curIndex, pos, startIndex, crossSize);
        cachedItemPosition_[curIndex] = pos;
        if (isGroup) {
            auto res = GetLayoutGroupCachedCount(
                layoutWrapper, wrapper, -1, cacheCount - cachedCount, curIndex, true);
            if (res.backwardCachedCount < res.backwardCacheMax && res.backwardCachedCount < cacheCount - cachedCount) {
                predictList.emplace_back(PredictLayoutItem { curIndex, -1, cachedCount });
                return res.backwardCachedCount > 0 ? curIndex : curIndex + 1;
            }
            cachedCount += std::max(res.backwardCacheMax, 1);
        } else {
            cachedCount++;
        }
        ExpandWithSafeAreaPadding(wrapper);
        wrapper->SetActive(show);
        SyncGeometry(wrapper, isDirty);
        curIndex--;
    }
    return curIndex + 1;
}

void ListLayoutAlgorithm::ExpandWithSafeAreaPadding(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    IgnoreLayoutSafeAreaOpts options = { .type = NG::LAYOUT_SAFE_AREA_TYPE_NONE,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_NONE };
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    if (layoutProperty) {
        auto&& nodeOpts = layoutWrapper->GetLayoutProperty()->GetIgnoreLayoutSafeAreaOpts();
        if (nodeOpts) {
            options = *nodeOpts;
        }
    }

    auto geometryNode = layoutWrapper->GetGeometryNode();
    if (geometryNode) {
        auto offset = geometryNode->GetMarginFrameOffset();
        auto ignoreAdjust = geometryNode->GetIgnoreAdjust();
        offset -= ignoreAdjust;
        geometryNode->SetMarginFrameOffset(offset);
    }
}

std::tuple<int32_t, int32_t, int32_t, int32_t> ListLayoutAlgorithm::LayoutCachedItemInEdgeGroup(
    LayoutWrapper* layoutWrapper, int32_t cacheCount, std::list<PredictLayoutItem>& predictList)
{
    int32_t startIndex = GetStartIndex();
    int32_t endIndex = GetEndIndex();
    int32_t cachedForward = 0;
    int32_t cachedBackward = 0;
    if (startIndex == endIndex && itemPosition_.begin()->second.isGroup) {
        auto wrapper = GetChildByIndex(layoutWrapper, startIndex);
        auto res = GetLayoutGroupCachedCount(layoutWrapper, wrapper, cacheCount, cacheCount, startIndex, false);
        if ((res.forwardCachedCount < res.forwardCacheMax && res.forwardCachedCount < cacheCount) ||
            (res.backwardCachedCount < res.backwardCacheMax && res.backwardCachedCount < cacheCount)) {
            int32_t forwardCached = res.forwardCacheMax > 0 ? cachedForward : -1;
            int32_t backwardCached = res.backwardCacheMax > 0 ? cachedBackward : -1;
            predictList.emplace_back(PredictLayoutItem { startIndex, forwardCached, backwardCached });
        }
        cachedForward += res.forwardCacheMax;
        cachedBackward += res.backwardCacheMax;
    } else {
        if (itemPosition_.rbegin()->second.isGroup) {
            auto wrapper = GetChildByIndex(layoutWrapper, endIndex);
            auto res = GetLayoutGroupCachedCount(layoutWrapper, wrapper, cacheCount, -1, endIndex, false);
            if (res.forwardCachedCount < res.forwardCacheMax && res.forwardCachedCount < cacheCount) {
                predictList.emplace_back(PredictLayoutItem { endIndex, cachedForward, -1 });
            }
            cachedForward += res.forwardCacheMax;
        }
        if (itemPosition_.begin()->second.isGroup) {
            auto wrapper = GetChildByIndex(layoutWrapper, startIndex);
            auto res = GetLayoutGroupCachedCount(layoutWrapper, wrapper, -1, cacheCount, startIndex, false);
            if (res.backwardCachedCount < res.backwardCacheMax && res.backwardCachedCount < cacheCount) {
                predictList.emplace_back(PredictLayoutItem { startIndex, -1, cachedBackward });
            }
            cachedBackward += res.backwardCacheMax;
        }
    }
    return { startIndex, endIndex, cachedForward, cachedBackward };
}

void CheckMinCacheRange(LayoutWrapper* layoutWrapper, std::list<PredictLayoutItem>& list,
    int32_t cacheCount, int32_t start, int32_t end)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto prop = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(prop);
    int32_t minCacheCount = prop->GetMinCacheCount();
    if (minCacheCount >= cacheCount) {
        return;
    }
    for (auto it = list.begin(); it != list.end();) {
        if (it->index < start - minCacheCount || it->index > end + minCacheCount) {
            it = list.erase(it);
        } else {
            ++it;
        }
    }
}

std::list<PredictLayoutItem> ListLayoutAlgorithm::LayoutCachedItemV2(LayoutWrapper* layoutWrapper, int32_t cacheCount,
    bool show)
{
    ACE_SCOPED_TRACE("LayoutCachedItemV2");
    std::list<PredictLayoutItem> predictBuildList;
    auto [startIndex, endIndex, cachedForward, cachedBackward] =
        LayoutCachedItemInEdgeGroup(layoutWrapper, cacheCount, predictBuildList);
    if (cachedForward < cacheCount && endIndex < totalItemCount_ - 1) {
        endIndex = LayoutCachedForward(layoutWrapper, cacheCount, cachedForward, endIndex, predictBuildList, show);
    }
    if (cachedBackward < cacheCount && startIndex > 0) {
        startIndex =
            LayoutCachedBackward(layoutWrapper, cacheCount, cachedBackward, startIndex, predictBuildList, show);
    }
    CheckMinCacheRange(layoutWrapper, predictBuildList, cacheCount,
        itemPosition_.begin()->first, itemPosition_.rbegin()->first);
    int32_t cacheStart = itemPosition_.begin()->first - startIndex;
    int32_t cacheEnd = endIndex - itemPosition_.rbegin()->first;
    if (isStackFromEnd_) {
        std::swap(cacheStart, cacheEnd);
    }
    ResetLayoutItem(layoutWrapper);
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
    values.contentStartOffset = listMainSizeValues.contentStartOffset;
    values.contentEndOffset = listMainSizeValues.contentEndOffset;
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
        auto index = !pattern->IsStackFromEnd() ? (*it).index : frameNode->GetTotalChildCount() - (*it).index - 1;
        auto wrapper = frameNode->GetOrCreateChildByIndex(index + pattern->GetItemStartIndex(), show, true);
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
    if (!context->IsWindowSizeDragging()) {
        context->AddPredictTask([weak = WeakClaim(RawPtr(frameNode)), listMainSizeValues, show]
            (int64_t deadline, bool canUseLongPredictTask) {
                ListLayoutAlgorithm::PredictBuildV2(weak.Upgrade(), deadline, listMainSizeValues, show);
            }
        );
        return;
    }
    context->AddWindowSizeDragEndCallback([weak = WeakClaim(RawPtr(frameNode)), listMainSizeValues, show]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<ListPattern>();
        CHECK_NULL_VOID(pattern);
        if (!pattern->GetPredictLayoutParamV2().has_value()) {
            return;
        }
        auto context = frameNode->GetContext();
        CHECK_NULL_VOID(context);
        context->AddPredictTask([weak = WeakClaim(RawPtr(frameNode)), listMainSizeValues, show]
            (int64_t deadline, bool canUseLongPredictTask) {
                ListLayoutAlgorithm::PredictBuildV2(weak.Upgrade(), deadline, listMainSizeValues, show);
            }
        );
    });
}

float ListLayoutAlgorithm::GetStopOnScreenOffset(ScrollSnapAlign scrollSnapAlign) const
{
    float stopOnScreen = 0;
    if (scrollSnapAlign == ScrollSnapAlign::START) {
        stopOnScreen = contentStartOffset_;
    } else if (scrollSnapAlign == ScrollSnapAlign::CENTER) {
        stopOnScreen = contentMainSize_ / 2.0f;
    } else if (scrollSnapAlign == ScrollSnapAlign::END) {
        stopOnScreen = contentMainSize_ - contentEndOffset_;
    }
    return stopOnScreen;
}

void ListLayoutAlgorithm::FindPredictSnapIndexInItemPositionsStart(
    float predictEndPos, int32_t& endIndex, int32_t& currIndex) const
{
    float stopOnScreen = GetStopOnScreenOffset(ScrollSnapAlign::START);
    float itemHeight = itemPosition_.begin()->second.endPos - itemPosition_.begin()->second.startPos;
    std::optional<float> lastSnapPos;
    if (GetEndIndex() == totalItemCount_ - 1) {
        // Bottom-aligned position
        lastSnapPos = contentStartOffset_ + GetEndPosition() - (contentMainSize_ - contentEndOffset_);
    }
    for (const auto& positionInfo : itemPosition_) {
        auto startPos = positionInfo.second.startPos - itemHeight / 2.0f - spaceWidth_;
        itemHeight = positionInfo.second.endPos - positionInfo.second.startPos;
        auto endPos = positionInfo.second.startPos + itemHeight / 2.0f;

        float lastEndPos = std::numeric_limits<float>::infinity();
        if (lastSnapPos.has_value() && LessNotEqual(positionInfo.second.startPos, lastSnapPos.value()) &&
            LessNotEqual(lastSnapPos.value(), positionInfo.second.endPos)) {
            // To calculate whether to align the start position of the item or to the bottom of the list
            lastEndPos = (lastSnapPos.value() + positionInfo.second.startPos) / 2.0f;
        }
        if (GreatOrEqual(predictEndPos + stopOnScreen, totalOffset_ + startPos) &&
            LessNotEqual(predictEndPos + stopOnScreen, totalOffset_ + endPos)) {
            endIndex = positionInfo.first;
            if (GreatNotEqual(predictEndPos + stopOnScreen, totalOffset_ + lastEndPos)) {
                // Bottom-aligned is closer than start-aligned.
                endIndex++;
            }
        }
        if (GreatOrEqual(stopOnScreen, startPos) && LessNotEqual(stopOnScreen, endPos)) {
            currIndex = positionInfo.first;
            if (GreatNotEqual(stopOnScreen, lastEndPos)) {
                // Bottom-aligned currently.
                currIndex++;
            }
        }
        if (endIndex >= 0 && currIndex >= 0) {
            break;
        }
    }
}

void ListLayoutAlgorithm::FindPredictSnapIndexInItemPositionsCenter(
    float predictEndPos, int32_t& endIndex, int32_t& currIndex) const
{
    float stopOnScreen = GetStopOnScreenOffset(ScrollSnapAlign::CENTER);
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
    float stopOnScreen = GetStopOnScreenOffset(ScrollSnapAlign::END);
    float itemHeight = itemPosition_.rbegin()->second.endPos - itemPosition_.rbegin()->second.startPos;
    std::optional<float> firstSnapPos;
    if (GetStartIndex() == 0) {
        // Top-aligned position
        firstSnapPos = (contentMainSize_ - contentEndOffset_) + GetStartPosition() - contentStartOffset_;
    }
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        auto endPos = pos->second.endPos + itemHeight / 2.0f + spaceWidth_;
        itemHeight = pos->second.endPos - pos->second.startPos;
        auto startPos = pos->second.endPos - itemHeight / 2.0f;

        float firstEndPos = -std::numeric_limits<float>::infinity();
        if (firstSnapPos.has_value() && LessNotEqual(pos->second.startPos, firstSnapPos.value()) &&
            LessNotEqual(firstSnapPos.value(), pos->second.endPos)) {
            // To calculate whether to align the end position of the item or to the top of the list
            firstEndPos = (firstSnapPos.value() + pos->second.endPos) / 2.0f;
        }
        if (GreatOrEqual(predictEndPos + stopOnScreen, totalOffset_ + startPos) &&
            LessNotEqual(predictEndPos + stopOnScreen, totalOffset_ + endPos)) {
            endIndex = pos->first;
            if (LessNotEqual(predictEndPos + stopOnScreen, totalOffset_ + firstEndPos)) {
                // Top-aligned is closer than end-aligned.
                endIndex--;
            }
        }
        if (GreatOrEqual(stopOnScreen, startPos) && LessNotEqual(stopOnScreen, endPos)) {
            currIndex = pos->first;
            if (LessNotEqual(stopOnScreen, firstEndPos)) {
                // Top-aligned currently.
                currIndex--;
            }
        }
        if (endIndex >= 0 && currIndex >= 0) {
            break;
        }
    }
}

int32_t ListLayoutAlgorithm::FindPredictSnapEndIndexInItemPositions(
    float predictEndPos, ScrollSnapAlign scrollSnapAlign)
{
    int32_t endIndex = -1;
    int32_t currIndex = -1;

    if (scrollSnapAlign == ScrollSnapAlign::START) {
        FindPredictSnapIndexInItemPositionsStart(predictEndPos, endIndex, currIndex);
    } else if (scrollSnapAlign == ScrollSnapAlign::CENTER) {
        FindPredictSnapIndexInItemPositionsCenter(predictEndPos, endIndex, currIndex);
    } else if (scrollSnapAlign == ScrollSnapAlign::END) {
        FindPredictSnapIndexInItemPositionsEnd(predictEndPos, endIndex, currIndex);
    }
    if (endIndex == currIndex && currIndex >= 0) {
        if (scrollSnapVelocity_ < -SCROLL_SNAP_VELOCITY_TH * Scrollable::GetVelocityScale()) {
            endIndex = std::min(GetEndIndex(), endIndex + 1);
        } else if (scrollSnapVelocity_ > SCROLL_SNAP_VELOCITY_TH * Scrollable::GetVelocityScale()) {
            endIndex = std::max(GetStartIndex(), endIndex - 1);
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

float ListLayoutAlgorithm::CalculatePredictSnapEndPositionByIndex(int32_t index, ScrollSnapAlign scrollSnapAlign)
{
    float predictSnapEndPos = 0;
    if (scrollSnapAlign == ScrollSnapAlign::START) {
        predictSnapEndPos = totalOffset_ + itemPosition_[index].startPos - contentStartOffset_;
        float endPos = GetEndPosition();
        float itemTotalSize = endPos - GetStartPosition();
        float contentSize = contentMainSize_ - contentEndOffset_ - contentStartOffset_;
        if ((GetEndIndex() == totalItemCount_ - 1) && GreatNotEqual(itemTotalSize, contentSize) &&
            GreatNotEqual(predictSnapEndPos + contentMainSize_ - contentEndOffset_, totalOffset_ + endPos)) {
            predictSnapEndPos = totalOffset_ + endPos - contentMainSize_ + contentEndOffset_;
        }
    } else if (scrollSnapAlign == ScrollSnapAlign::CENTER) {
        float itemHeight = itemPosition_[index].endPos - itemPosition_[index].startPos;
        predictSnapEndPos = totalOffset_ + itemPosition_[index].startPos + itemHeight / 2.0f - contentMainSize_ / 2.0f;
    } else if (scrollSnapAlign == ScrollSnapAlign::END) {
        predictSnapEndPos = totalOffset_ + itemPosition_[index].endPos - contentMainSize_ + contentEndOffset_;
        if (GetStartIndex() == 0 && LessNotEqual(predictSnapEndPos, totalOffset_ + GetStartPosition())) {
            predictSnapEndPos = totalOffset_ + GetStartPosition() - contentStartOffset_;
        }
    }
    return predictSnapEndPos;
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
                NearEqual(GetEndPosition(), prevContentMainSize_ - prevContentEndOffset_) && !canOverScrollStart_) {
                startIndex = pos.first;
                startPos = contentStartOffset_;
                adjustOffset_ = pos.second.startPos - prevContentStartOffset_;
            }
            break;
        }
    }
    return std::make_pair(std::min(startIndex, totalItemCount_ -1), startPos);
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
            if ((GetStartIndex() == 0) && NearEqual(GetStartPosition(), prevContentStartOffset_) &&
                !canOverScrollEnd_) {
                endIndex = pos->first;
                endPos = prevContentMainSize_ - contentEndOffset_;
                adjustOffset_ = pos->second.endPos + prevContentEndOffset_ - prevContentMainSize_;
            }
            break;
        }
    }
    return std::make_pair(std::min(endIndex, totalItemCount_ - 1), endPos);
}

void ListLayoutAlgorithm::ReverseItemPosition(
    ListLayoutAlgorithm::PositionMap& itemPosition, int32_t totalItemCount, float mainSize)
{
    if (!isStackFromEnd_ || itemPosition.empty()) {
        return;
    }
    ListLayoutAlgorithm::PositionMap posMap;
    for (auto pos : itemPosition) {
        auto startPos = mainSize - pos.second.endPos;
        auto endPos = mainSize - pos.second.startPos;
        pos.second.startPos = startPos;
        pos.second.endPos = endPos;
        posMap[totalItemCount - pos.first - 1] = pos.second;
    }
    itemPosition = std::move(posMap);
}

void ListLayoutAlgorithm::ProcessStackFromEnd()
{
    if (isStackFromEnd_ && totalItemCount_ > 0) {
        currentDelta_ = -currentDelta_;
        currentOffset_ = -currentOffset_;
        std::swap(canOverScrollStart_, canOverScrollEnd_);
        std::swap(contentStartOffset_, contentEndOffset_);
        if (scrollAlign_ == ScrollAlign::START) {
            scrollAlign_ = ScrollAlign::END;
        } else if (scrollAlign_ == ScrollAlign::END) {
            scrollAlign_ = ScrollAlign::START;
        }
        if (childrenSize_ && posMap_) {
            posMap_->ReversePosMap();
        }
    }
}

int32_t ListLayoutAlgorithm::UpdateDefaultCachedCount(const int32_t oldCacheCount, const int32_t itemCount)
{
    if (itemCount <= 0) {
        return oldCacheCount;
    }
    thread_local float pageCount = SystemProperties::GetPageCount();
    if (pageCount <= 0.0f) {
        return oldCacheCount;
    }
    constexpr int32_t MAX_DEFAULT_CACHED_COUNT = 16;
    int32_t newCachedCount = static_cast<int32_t>(ceil(pageCount * itemCount));
    if (newCachedCount > MAX_DEFAULT_CACHED_COUNT) {
        TAG_LOGI(AceLogTag::ACE_LIST, "Default cachedCount exceed 16");
        return MAX_DEFAULT_CACHED_COUNT;
    } else {
        return std::max(newCachedCount, oldCacheCount);
    }
}

void ListLayoutAlgorithm::ReportGetChildError(const std::string& funcName, int32_t index) const
{
    if (index < 0 || index > totalItemCount_ - 1) {
        return;
    }
    std::string subErrorType = funcName + " get item: " + std::to_string(index) + " failed.";
    EventReport::ReportScrollableErrorEvent("List", ScrollableErrorType::GET_CHILD_FAILED, subErrorType);
}

void ListLayoutAlgorithm::CalculateTotalCountByRepeat(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    auto repeatDifference = 0;
    firstRepeatCount_ = 0;
    totalItemCount_ = 0;
    pattern->GetRepeatCountInfo(host, repeatDifference, firstRepeatCount_, totalItemCount_);
    pattern->SetRepeatDifference(repeatDifference);
    totalItemCount_ = (repeatDifference > 0 ? firstRepeatCount_ : totalItemCount_) - itemStartIndex_;
}
} // namespace OHOS::Ace::NG
