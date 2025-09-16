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

#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_algorithm.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/container_picker/container_picker_utils.h"
#include "core/pipeline_ng/pipeline_context.h"
#include <cstdint>
#include <iterator>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
namespace {
    const float PICKER_DEFAULT_HEIGHT = 910.0f;
    const float PICKER_DEFAULT_WIDTH = 300.0f;
} // namespace

void ContainerPickerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    std::lock_guard<std::mutex> lock(pickerMutex_);
    CHECK_NULL_VOID(layoutWrapper);
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(pickerLayoutProperty);

    // calculate main size.
    auto contentConstraint = pickerLayoutProperty->GetContentLayoutConstraint().value();
    OptionalSizeF contentIdealSize = CreateIdealSizeByPercentRef(contentConstraint, axis_,
        MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (layoutWrapper->ConstraintChanged()) {
        mainSizeIsMeasured_ = false;
    }
    const auto& padding = pickerLayoutProperty->CreatePaddingAndBorder();
    contentMainSize_ = PICKER_DEFAULT_HEIGHT;
    auto childLayoutConstraint =
        ContainerPickerUtils::CreateChildConstraint(pickerLayoutProperty, contentIdealSize);
    childLayoutConstraint_ = childLayoutConstraint;
    if (totalItemCount_ > 0) {
        currentOffset_ = currentDelta_;
        startMainPos_ = currentOffset_;
        endMainPos_ = currentOffset_ + contentMainSize_;
        MeasureSize(contentConstraint);
        HandleLayoutPolicy(layoutWrapper, contentIdealSize);
        MeasurePicker(layoutWrapper, childLayoutConstraint);
    } else {
        itemPosition_.clear();
    }

    if (itemPosition_.empty()) {
        layoutWrapper->SetActiveChildRange(-1, -1);
    } else {
        // startIndex maybe target to invalid blank items in group mode, need to be adjusted.
        int32_t startIndex = GetLoopIndex(GetStartIndex()) < totalItemCount_ ? GetLoopIndex(GetStartIndex()) : 0;
        int32_t endIndex = std::min(GetLoopIndex(GetEndIndex()), totalItemCount_ - 1);
        if (!isLoop_) {
            layoutWrapper->SetActiveChildRange(startIndex, endIndex, std::min(1, startIndex),
                std::min(1, totalItemCount_ - 1 - endIndex));
        } else {
            layoutWrapper->SetActiveChildRange(startIndex, endIndex, 1, 1);
        }
    }

    contentIdealSize.SetMainSize(contentMainSize_, axis_);
    AddPaddingToSize(padding, contentIdealSize);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    if (geometryNode) {
        geometryNode->SetFrameSize(contentIdealSize.ConvertToSizeT());
    }
    if (!itemPosition_.empty()) {
        mainSizeIsMeasured_ = true;
    }
    measured_ = true;
    SetPatternContentMainSize(layoutWrapper);
}

void ContainerPickerLayoutAlgorithm::MeasureSize(LayoutConstraintF& contentConstraint)
{
    float pickerWidth = 0.0f;
    auto width = contentConstraint.parentIdealSize.Width();
    if (width.has_value()) {
        pickerWidth = std::min(width.value(), PICKER_DEFAULT_WIDTH);
    } else {
        pickerWidth = PICKER_DEFAULT_WIDTH;
    }
    float pickerHeight = 0.0f;
    auto height = contentConstraint.parentIdealSize.Height();
    if (height.has_value()) {
        pickerHeight = std::min(width.value(), contentMainSize_);
    } else {
        pickerHeight = contentMainSize_;
    }
    contentConstraint.selfIdealSize.SetHeight(pickerHeight);
    contentConstraint.selfIdealSize.SetWidth(pickerWidth);
}

void ContainerPickerLayoutAlgorithm::HandleLayoutPolicy(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(pickerLayoutProperty);

    // calculate main size.
    auto contentConstraint = pickerLayoutProperty->GetContentLayoutConstraint().value();
    auto layoutPolicy = pickerLayoutProperty->GetLayoutPolicyProperty();
    auto isMainMatchParent = false;
    auto isCrossMatchParent = false;
    auto isCrossWrap = false;
    if (layoutPolicy.has_value()) {
        auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        isMainMatchParent = heightLayoutPolicy == LayoutCalPolicy::MATCH_PARENT;
        isCrossMatchParent = widthLayoutPolicy == LayoutCalPolicy::MATCH_PARENT;
        isCrossWrap = widthLayoutPolicy == LayoutCalPolicy::WRAP_CONTENT;

        // when the main/cross axis is set matchParent, Update contentIdealSize
        if (isMainMatchParent || isCrossMatchParent) {
            auto layoutPolicySize = ConstrainIdealSizeByLayoutPolicy(contentConstraint,
                widthLayoutPolicy, heightLayoutPolicy, axis_);
            contentIdealSize.UpdateIllegalSizeWithCheck(layoutPolicySize);
        }
    }
    auto crossSize = contentIdealSize.CrossSize(axis_);
    contentCrossSize_ = crossSize.value();
}

void ContainerPickerLayoutAlgorithm::SetPatternContentMainSize(LayoutWrapper* layoutWrapper)
{
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto pickerPattern = hostNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    pickerPattern->SetContentMainSize(contentMainSize_);
}

void ContainerPickerLayoutAlgorithm::MeasurePicker(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint)
{
    int32_t startIndex = 0;
    int32_t endIndex = 0;
    float startPos = 0.0f;
    float endPos = 0.0f;
    int32_t startIndexInVisibleWindow = 0;
    prevItemPosition_ = itemPosition_;
    if (!itemPosition_.empty()) {
        startPos = itemPosition_.begin()->second.startPos;
        endPos = itemPosition_.rbegin()->second.endPos;
        for (const auto& item : itemPosition_) {
            float itemEndPos = item.second.endPos;
            if (Positive(itemEndPos)) {
                startIndexInVisibleWindow = item.first;
                startPos = item.second.startPos;
                break;
            }
        }
        startIndex = GetStartIndex();
        endIndex = GetEndIndex();
        if (!isLoop_) {
            startIndex = std::min(GetLoopIndex(GetStartIndex()), totalItemCount_ - 1);
            endIndex = std::min(GetLoopIndex(GetEndIndex()), totalItemCount_ - 1);
            startIndexInVisibleWindow = std::min(GetLoopIndex(startIndexInVisibleWindow), totalItemCount_ - 1);
        }

        itemPosition_.clear();
    }

    bool overScrollTop = startIndexInVisibleWindow == 0 && GreatNotEqual(startPos, startMainPos_);
    if ((!overScrollFeature_ && NonNegative(currentOffset_)) || (overScrollFeature_ && overScrollTop)) {
        LayoutForward(layoutWrapper, layoutConstraint, startIndexInVisibleWindow, startPos);
        auto adjustStartMainPos = startMainPos_;
        if (GetStartIndex() > 0 && GreatNotEqual(GetStartPosition(), adjustStartMainPos)) {
            LayoutBackward(layoutWrapper, layoutConstraint, GetStartIndex() - 1, GetStartPosition());
        }
    } else {
        LayoutBackward(layoutWrapper, layoutConstraint, endIndex, endPos);
        if (GetEndIndex() < (totalItemCount_ - 1) && LessNotEqual(GetEndPosition(), endMainPos_)) {
            LayoutForward(layoutWrapper, layoutConstraint, GetEndIndex() + 1, GetEndPosition());
        }
    }
}

void ContainerPickerLayoutAlgorithm::AdjustStartInfoOnSwipeByGroup(
    int32_t startIndex, const PositionMap& itemPosition, int32_t& startIndexInVisibleWindow, float& startPos)
{
    startIndexInVisibleWindow = startIndex;
    auto iter = itemPosition.find(startIndex);
    if (iter != itemPosition.end()) {
        startPos = iter->second.startPos;
    }
}

void ContainerPickerLayoutAlgorithm::LayoutForward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos, bool cachedLayout)
{
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    float endMainPos = overScrollFeature_ ? std::max(startPos + contentMainSize_, endMainPos_) : endMainPos_;
    if (targetIndex_) {
        endMainPos = Infinity<float>();
    }

    auto currentIndex = startIndex - 1;
    do {
        currentStartPos = currentEndPos;
        auto result = LayoutForwardItem(layoutWrapper, layoutConstraint, currentIndex, currentStartPos, currentEndPos);
        if (!result) {
            break;
        }
        // reach the valid target index
        if (targetIndex_ && currentIndex >= targetIndex_.value()) {
            targetIndex_.reset();
        }
    } while (NeedMeasureForward(currentIndex, currentEndPos, endMainPos, cachedLayout));

    if (overScrollFeature_) {
        return;
    }

    if (LessNotEqual(currentEndPos, endMainPos_)) {
        AdjustOffsetOnForward(currentEndPos);
    }

    SetInactiveOnForward(layoutWrapper);
}

void ContainerPickerLayoutAlgorithm::LayoutBackward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t endIndex, float endPos, bool cachedLayout)
{
    float currentStartPos = endPos;
    float currentEndPos = 0.0f;
    float startMainPos = overScrollFeature_ ? std::min(endPos - contentMainSize_, startMainPos_) : startMainPos_;
    if (targetIndex_) {
        startMainPos = -Infinity<float>();
    }
    auto currentIndex = endIndex + 1;

    auto isStretch = false;
    float adjustStartMainPos = 0.0f;
    do {
        currentEndPos = currentStartPos;
        auto result = LayoutBackwardItem(layoutWrapper, layoutConstraint, currentIndex, currentEndPos, currentStartPos);
        if (!result) {
            break;
        }
        // reach the valid target index
        if (targetIndex_ && LessOrEqual(currentIndex, targetIndex_.value())) {
            startMainPos = currentStartPos;
            targetIndex_.reset();
        }
        adjustStartMainPos = startMainPos;
    } while (NeedMeasureBackward(currentIndex, currentStartPos, adjustStartMainPos, isStretch, cachedLayout));

    // adjust offset. If edgeEffect is SPRING, jump adjust to allow swiper scroll through boundary
    if (GreatNotEqual(currentStartPos, startMainPos_)) {
        AdjustOffsetOnBackward(currentStartPos);
    }

    if (overScrollFeature_) {
        return;
    }

    SetInactiveOnBackward(layoutWrapper);
}

bool ContainerPickerLayoutAlgorithm::LayoutForwardItem(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t& currentIndex, float startPos, float& endPos)
{
    if ((currentIndex + 1 >= totalItemCount_ && !isLoop_) ||
        (static_cast<int32_t>(itemPosition_.size()) >= totalItemCount_)) {
        return false;
    }

    auto measureIndex = GetLoopIndex(currentIndex + 1);
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(measureIndex);
    ++currentIndex;
    wrapper->Measure(layoutConstraint);
    measuredItems_.insert(measureIndex);

    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(pickerLayoutProperty, false);

    float mainAxisSize = GetChildMainAxisSize(wrapper);
    endPos = startPos + mainAxisSize;
    itemPosition_[currentIndex] = { startPos, endPos, wrapper->GetHostNode() };
    return true;
}

bool ContainerPickerLayoutAlgorithm::LayoutBackwardItem(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t& currentIndex, float endPos, float& startPos)
{
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(pickerLayoutProperty, false);
    int32_t displayCount = 7;
    bool itemPositionIsFull = static_cast<int32_t>(itemPosition_.size()) >= totalItemCount_ + displayCount - 1;
    if ((currentIndex - 1 < 0 && !isLoop_)) {
        return false;
    }

    auto measureIndex = GetLoopIndex(currentIndex - 1);
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetLoopIndex(measureIndex));
    --currentIndex;
    wrapper->Measure(layoutConstraint);
    measuredItems_.insert(measureIndex);

    float mainAxisSize = GetChildMainAxisSize(wrapper);
    startPos = endPos - mainAxisSize;
    if (!itemPositionIsFull) {
        itemPosition_[currentIndex] = { startPos, endPos, wrapper->GetHostNode() };
    }
    if (targetIndex_ && currentIndex == targetIndex_.value()) {
        targetStartPos_ = startPos;
    }
    return true;
}

bool ContainerPickerLayoutAlgorithm::NeedMeasureForward(
    int32_t currentIndex, float currentEndPos, float forwardEndPos, bool cachedLayout) const
{
    auto contentMainSize = contentMainSize_;
    bool isLayoutOver = overScrollFeature_ && GreatOrEqual(currentEndPos, contentMainSize);
    return !isLayoutOver &&
           (LessNotEqual(currentEndPos, forwardEndPos) || (targetIndex_ && currentIndex < targetIndex_.value()));
}

bool ContainerPickerLayoutAlgorithm::NeedMeasureBackward(
    int32_t currentIndex, float currentStartPos, float backwardStartPos, bool isStretch, bool cachedLayout) const
{
    return GreatNotEqual(currentStartPos, backwardStartPos) ||
           (!isStretch && targetIndex_ && currentIndex > targetIndex_.value());
}

void ContainerPickerLayoutAlgorithm::AdjustOffsetOnForward(float currentEndPos)
{
    if (itemPosition_.empty()) {
        return;
    }

    auto firstItemTop = GetStartPosition();
    auto itemTotalSize = currentEndPos - firstItemTop;
    if (LessOrEqual(itemTotalSize, contentMainSize_) && (itemPosition_.begin()->first == 0)) {
        // all items size is less than swiper.
        if (!canOverScroll_) {
            currentOffset_ = firstItemTop;
            startMainPos_ = currentOffset_;
        }
    } else {
        // adjust offset. If edgeEffect is SPRING, jump adjust to allow swiper scroll through boundary
        if (!canOverScroll_ || jumpIndex_.has_value()) {
            currentOffset_ = currentEndPos - contentMainSize_;
        }
        startMainPos_ = currentEndPos - contentMainSize_;
        endMainPos_ = currentEndPos;
    }
}

void ContainerPickerLayoutAlgorithm::AdjustOffsetOnBackward(float currentStartPos)
{
    if (!canOverScroll_ || jumpIndex_.has_value()) {
        currentOffset_ = currentStartPos;
    }
    endMainPos_ = currentStartPos + contentMainSize_;
    startMainPos_ = currentStartPos;
}

void ContainerPickerLayoutAlgorithm::SetInactiveOnForward(LayoutWrapper* layoutWrapper)
{
    for (auto pos = itemPosition_.begin(); pos != itemPosition_.end();) {
        auto endPos = pos->second.endPos;
        
        if (GreatNotEqual(endPos, startMainPos_)) {
            break;
        }

        ResetOffscreenItemPosition(layoutWrapper, GetLoopIndex(pos->first), true);
        pos = itemPosition_.erase(pos);
    }
}

void ContainerPickerLayoutAlgorithm::SetInactiveOnBackward(LayoutWrapper* layoutWrapper)
{
    std::list<int32_t> removeIndexes;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        auto startPos = pos->second.startPos;
        auto index = pos->first;

        if (LessNotEqual(startPos, endMainPos_)) {
            break;
        }

        ResetOffscreenItemPosition(layoutWrapper, GetLoopIndex(index), false);
        removeIndexes.emplace_back(index);
    }

    for (const auto& index : removeIndexes) {
        itemPosition_.erase(index);
    }
}

void ContainerPickerLayoutAlgorithm::ResetOffscreenItemPosition(
    LayoutWrapper* layoutWrapper, int32_t index, bool isForward) const
{
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(childWrapper);

    auto childGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeometryNode);
    auto frameRect = geometryNode->GetFrameRect();
    auto childFrameRect = childGeometryNode->GetFrameRect();

    OffsetF offset(0.0f, 0.0f);
    offset.SetY(isForward ? -childFrameRect.Height() : frameRect.Height());

    childGeometryNode->SetMarginFrameOffset(offset);
    childWrapper->Layout();
}

float ContainerPickerLayoutAlgorithm::GetChildMainAxisSize(const RefPtr<LayoutWrapper>& childWrapper)
{
    CHECK_NULL_RETURN(childWrapper, 0.0f);
    auto geometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);

    float mainAxisSize = GetMainAxisSize(geometryNode->GetMarginFrameSize(), axis_);

    return mainAxisSize;
}

void ContainerPickerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(pickerLayoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    axis_ = Axis::VERTICAL;
    auto size = geometryNode->GetFrameSize();
    auto padding = pickerLayoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto paddingOffset = padding.Offset();

    // layout items.
    std::set<int32_t> layoutIndexSet;
    for (auto& pos : itemPosition_) {
        layoutIndexSet.insert(GetLoopIndex(pos.first));
        pos.second.startPos -= currentOffset_;
        pos.second.endPos -= currentOffset_;
        LayoutItem(layoutWrapper, paddingOffset, pos);
    }
}

void ContainerPickerLayoutAlgorithm::LayoutItem(LayoutWrapper* layoutWrapper, OffsetF offset,
    std::pair<int32_t, PickerItemInfo> pos)
{
    auto layoutIndex = GetLoopIndex(pos.first);
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(layoutIndex);

    float crossOffset = 0.0f;
    offset += OffsetF(crossOffset, pos.second.startPos);
    CHECK_NULL_VOID(wrapper->GetGeometryNode());
    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    wrapper->Layout();
}
} // namespace OHOS::Ace::NG