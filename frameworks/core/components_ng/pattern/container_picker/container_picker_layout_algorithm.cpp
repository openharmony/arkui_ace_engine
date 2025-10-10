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

#include "core/components_ng/pattern/container_picker/container_picker_layout_algorithm.h"

#include <cstdint>
#include <iterator>

#include "core/components/picker/picker_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {
namespace {
const float PICKER_DEFAULT_HEIGHT = 910.0f;
const float PICKER_DEFAULT_WIDTH = 300.0f;
const float UNDEFINED_SIZE = -1.0f;
const float HALF = 2.0;
const Dimension PICKER_DEFAULT_ITEM_HEIGHT = 40.0_vp;
const int32_t ITEM_COUNTS = 10;
const float HORIZONTAL_ANGLE = 180.0f;
const float VERTICAL_ANGLE = 90.0f;
} // namespace

void ContainerPickerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    std::lock_guard<std::mutex> lock(pickerMutex_);
    CHECK_NULL_VOID(layoutWrapper);
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(pickerLayoutProperty);

    // calculate main size.
    auto contentConstraint = pickerLayoutProperty->GetContentLayoutConstraint().value();

    OptionalSizeF contentIdealSize =
        CreateIdealSizeByPercentRef(contentConstraint, axis_, MeasureType::MATCH_PARENT_MAIN_AXIS);

    MeasureSize(layoutWrapper, contentIdealSize);

    CalcMainAndMiddlePos();
    auto childLayoutConstraint = ContainerPickerUtils::CreateChildConstraint(pickerLayoutProperty, contentIdealSize);
    childLayoutConstraint_ = childLayoutConstraint;
    if (totalItemCount_ > 0) {
        MeasurePickerItems(layoutWrapper, childLayoutConstraint);
    } else {
        itemPosition_.clear();
    }

    const auto& padding = pickerLayoutProperty->CreatePaddingAndBorder();
    AddPaddingToSize(padding, contentIdealSize);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    if (geometryNode) {
        geometryNode->SetFrameSize(contentIdealSize.ConvertToSizeT());
    }
    measured_ = true;
    SetPatternContentMainSize(layoutWrapper);
}

void ContainerPickerLayoutAlgorithm::MeasureSize(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(pickerLayoutProperty);
    auto contentConstraint = pickerLayoutProperty->GetContentLayoutConstraint().value();

    // handle layout policy.
    auto layoutPolicy = pickerLayoutProperty->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value()) {
        widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto isCrossMatchParent = widthLayoutPolicy == LayoutCalPolicy::MATCH_PARENT;

        // when the main/cross axis is set matchParent, Update contentIdealSize
        if (isCrossMatchParent) {
            auto layoutPolicySize = ConstrainIdealSizeByLayoutPolicy(
                contentConstraint, widthLayoutPolicy, LayoutCalPolicy::MATCH_PARENT, axis_);
            contentIdealSize.UpdateIllegalSizeWithCheck(layoutPolicySize);
        }
    }
    MeasureHeight(layoutWrapper, contentIdealSize);
    MeasureWidth(layoutWrapper, contentIdealSize);
}

void ContainerPickerLayoutAlgorithm::MeasureHeight(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize)
{
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto contentConstraint = pickerLayoutProperty->GetContentLayoutConstraint().value();
    auto isHeightDefined = false;
    float height = GetMainAxisSize(contentConstraint.selfIdealSize, axis_).value_or(UNDEFINED_SIZE);
    if (NonNegative(height)) {
        isHeightDefined = true;
    }

    // measure height
    if (!isHeightDefined) {
        auto parentMaxHeight = GetMainAxisSize(contentConstraint.maxSize, axis_);
        height = std::min(parentMaxHeight, PICKER_DEFAULT_HEIGHT);
    }

    if (!NearEqual(height, height_)) {
        // picker height changed
        itemPosition_.clear();
    }
    SetHeight(height);
    contentMainSize_ = std::min(height, PICKER_DEFAULT_HEIGHT);
    contentIdealSize.SetMainSize(height, axis_);
}

void ContainerPickerLayoutAlgorithm::MeasureWidth(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize)
{
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto contentConstraint = pickerLayoutProperty->GetContentLayoutConstraint().value();
    float width;

    auto isCrossWrap = widthLayoutPolicy == LayoutCalPolicy::WRAP_CONTENT;
    auto isCrossMatchParent = widthLayoutPolicy == LayoutCalPolicy::MATCH_PARENT;
    auto isCrossFix = widthLayoutPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE;

    // measure width
    auto crossSize = contentIdealSize.CrossSize(axis_);
    // when matchParent, idealSize'crossSize Keep the original value
    if (!isCrossMatchParent) {
        if ((crossSize.has_value() && GreaterOrEqualToInfinity(crossSize.value())) || !crossSize.has_value()) {
            width = GetChildMaxWidth(layoutWrapper);
            contentIdealSize.SetCrossSize(width, axis_);
            crossMatchChild_ = true;
        } else {
            width = NonNegative(crossSize.value()) ? crossSize.value() : PICKER_DEFAULT_WIDTH;
        }
    } else {
        width = NonNegative(crossSize.value()) ? crossSize.value() : PICKER_DEFAULT_WIDTH;
    }

    if (isCrossWrap) {
        auto parentCrossSize =
            CreateIdealSizeByPercentRef(contentConstraint, axis_, MeasureType::MATCH_PARENT_CROSS_AXIS)
                .CrossSize(axis_);
        width = GetChildMaxWidth(layoutWrapper);
        if (!parentCrossSize.has_value()) {
            contentIdealSize.SetCrossSize(width, axis_);
        } else {
            contentIdealSize.SetCrossSize(std::min(width, parentCrossSize.value()), axis_);
            width = std::min(width, parentCrossSize.value());
        }
        crossMatchChild_ = true;
    }

    if (isCrossFix) {
        width = GetChildMaxWidth(layoutWrapper);
        crossMatchChild_ = true;
    }

    contentIdealSize.SetCrossSize(width, axis_);
}

void ContainerPickerLayoutAlgorithm::CalcMainAndMiddlePos()
{
    startMainPos_ = std::max((height_ - PICKER_DEFAULT_HEIGHT) / HALF, 0.0f);
    endMainPos_ = startMainPos_ + std::min(height_, PICKER_DEFAULT_HEIGHT);
    middleItemStartPos_ = (height_ - PICKER_ITEM_DEFAULT_HEIGHT) / HALF;
    middleItemEndPos_ = (height_ + PICKER_ITEM_DEFAULT_HEIGHT) / HALF;
}

float ContainerPickerLayoutAlgorithm::GetChildMaxWidth(LayoutWrapper* layoutWrapper) const
{
    if (itemPosition_.empty()) {
        return 0.0f;
    }
    float maxSize = 0.0f;
    for (const auto& pos : itemPosition_) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(
            ContainerPickerUtils::GetLoopIndex(pos.first, totalItemCount_), false);
        if (!wrapper) {
            continue;
        }
        auto geometryNode = wrapper->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }
        maxSize = std::max(geometryNode->GetMarginFrameSize().Width(), maxSize);
    }
    return maxSize;
}

void ContainerPickerLayoutAlgorithm::SetPatternContentMainSize(LayoutWrapper* layoutWrapper)
{
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto pickerPattern = hostNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    pickerPattern->SetContentMainSize(contentMainSize_);
}

void ContainerPickerLayoutAlgorithm::MeasurePickerItems(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint)
{
    float startPos = middleItemStartPos_;
    float endPos = middleItemEndPos_;
    int32_t middleIndexInVisibleWindow = selectedIndex_;
    prevItemPosition_ = itemPosition_;
    if (!itemPosition_.empty()) {
        auto middleItem = ContainerPickerUtils::CalcCurrentMiddleItem(itemPosition_, height_, totalItemCount_, isLoop_);
        middleIndexInVisibleWindow = middleItem.first;
        startPos = middleItem.second.startPos;
        endPos = middleItem.second.endPos;
        itemPosition_.clear();
    }

    MeasureBelow(layoutWrapper, layoutConstraint, middleIndexInVisibleWindow, startPos);
    MeasureAbove(layoutWrapper, layoutConstraint, middleIndexInVisibleWindow - 1, GetStartPosition());

    std::vector<int32_t> prevItemsIndex;
    std::vector<int32_t> curItemsIndex;
    for (const auto& pair : prevItemPosition_)
        prevItemsIndex.push_back(ContainerPickerUtils::GetLoopIndex(pair.first, totalItemCount_));
    for (const auto& pair : itemPosition_)
        curItemsIndex.push_back(ContainerPickerUtils::GetLoopIndex(pair.first, totalItemCount_));
    std::sort(prevItemsIndex.begin(), prevItemsIndex.end());
    std::sort(curItemsIndex.begin(), curItemsIndex.end());
    std::set_difference(prevItemsIndex.begin(), prevItemsIndex.end(), curItemsIndex.begin(), curItemsIndex.end(),
        std::back_inserter(offScreenItemsIndex_));

    for (int32_t index : offScreenItemsIndex_) {
        ResetOffscreenItemPosition(layoutWrapper, index);
    }
}

void ContainerPickerLayoutAlgorithm::ResetOffscreenItemPosition(LayoutWrapper* layoutWrapper, int32_t index) const
{
    auto swiperGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(swiperGeometryNode);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(childWrapper);

    auto childGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeometryNode);

    OffsetF offset(0.0f, 0.0f);
    offset.SetY(-PICKER_ITEM_DEFAULT_HEIGHT);

    childGeometryNode->SetMarginFrameOffset(offset);
    childWrapper->Layout();
}

void ContainerPickerLayoutAlgorithm::MeasureBelow(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos, bool cachedLayout)
{
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    float endMainPos = overScrollFeature_ ? std::max(startPos + contentMainSize_, endMainPos_) : endMainPos_;

    auto currentIndex = startIndex - 1;
    do {
        currentStartPos = currentEndPos;
        auto result = MeasureBelowItem(layoutWrapper, layoutConstraint, currentIndex, currentStartPos, currentEndPos);
        if (!result) {
            break;
        }
    } while (NeedMeasureBelow(currentIndex, currentStartPos, endMainPos, cachedLayout));

    if (overScrollFeature_ || isLoop_) {
        return;
    }

    if (LessNotEqual(currentEndPos, endMainPos_ + contentMainSize_ / HALF)) {
        AdjustOffsetOnBelow(currentEndPos);
    }
}

void ContainerPickerLayoutAlgorithm::MeasureAbove(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t endIndex, float endPos, bool cachedLayout)
{
    float currentStartPos = endPos;
    float currentEndPos = 0.0f;
    float startMainPos = overScrollFeature_ ? std::min(endPos - contentMainSize_, startMainPos_) : startMainPos_;
    auto currentIndex = endIndex + 1;

    do {
        currentEndPos = currentStartPos;
        auto result = MeasureAboveItem(layoutWrapper, layoutConstraint, currentIndex, currentEndPos, currentStartPos);
        if (!result) {
            break;
        }
    } while (NeedMeasureAbove(currentIndex, currentEndPos, startMainPos, cachedLayout));

    if (overScrollFeature_ || isLoop_) {
        return;
    }

    if (GreatNotEqual(currentStartPos, startMainPos_ - contentMainSize_ / HALF)) {
        AdjustOffsetOnAbove(currentStartPos);
    }
}

bool ContainerPickerLayoutAlgorithm::MeasureBelowItem(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t& currentIndex, float startPos, float& endPos)
{
    if ((currentIndex + 1 >= totalItemCount_ && !isLoop_) ||
        (static_cast<int32_t>(itemPosition_.size()) >= totalItemCount_)) {
        return false;
    }

    auto measureIndex = ContainerPickerUtils::GetLoopIndex(currentIndex + 1, totalItemCount_);
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

bool ContainerPickerLayoutAlgorithm::MeasureAboveItem(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t& currentIndex, float endPos, float& startPos)
{
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(pickerLayoutProperty, false);
    if (currentIndex - 1 < 0 && !isLoop_) {
        return false;
    }

    auto measureIndex = ContainerPickerUtils::GetLoopIndex(currentIndex - 1, totalItemCount_);
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(measureIndex);
    --currentIndex;
    wrapper->Measure(layoutConstraint);
    measuredItems_.insert(measureIndex);

    float mainAxisSize = GetChildMainAxisSize(wrapper);
    startPos = endPos - mainAxisSize;
    itemPosition_[currentIndex] = { startPos, endPos, wrapper->GetHostNode() };
    return true;
}

bool ContainerPickerLayoutAlgorithm::NeedMeasureBelow(
    int32_t currentIndex, float currentStartPos, float endMainPos, bool cachedLayout) const
{
    auto contentMainSize = contentMainSize_;
    bool isLayoutOver = overScrollFeature_ && GreatOrEqual(currentStartPos, contentMainSize);
    return !isLayoutOver && LessNotEqual(currentStartPos, endMainPos);
}

bool ContainerPickerLayoutAlgorithm::NeedMeasureAbove(
    int32_t currentIndex, float currentEndPos, float startMainPos, bool cachedLayout) const
{
    return GreatNotEqual(currentEndPos, startMainPos);
}

void ContainerPickerLayoutAlgorithm::AdjustOffsetOnBelow(float currentEndPos)
{
    if (itemPosition_.empty()) {
        return;
    }

    auto lastItemEndPos = GetEndPosition();
    if (LessOrEqual(lastItemEndPos, middleItemEndPos_) && (itemPosition_.rbegin()->first == totalItemCount_ - 1)) {
        if (!canOverScroll_ && GreatOrEqual(currentOffset_, 0.0f)) {
            currentOffset_ = 0.0f;
        }
    }
}

void ContainerPickerLayoutAlgorithm::AdjustOffsetOnAbove(float currentStartPos)
{
    if (itemPosition_.empty()) {
        return;
    }

    auto firstItemStartPos = GetStartPosition();
    if (GreatOrEqual(firstItemStartPos, middleItemStartPos_) && (itemPosition_.begin()->first == 0)) {
        if (!canOverScroll_ && LessOrEqual(currentOffset_, 0.0f)) {
            currentOffset_ = 0.0f;
        }
    }
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
    CalcMainAndMiddlePos();
    auto padding = pickerLayoutProperty->CreatePaddingAndBorder();
    topPadding_ = padding.top.value_or(0.0);
    MinusPaddingToSize(padding, size);
    auto paddingOffset = padding.Offset();

    // layout items.
    for (auto& pos : itemPosition_) {
        pos.second.startPos -= currentOffset_;
        pos.second.endPos -= currentOffset_;
        LayoutItem(layoutWrapper, paddingOffset, pos);
    }
}

void ContainerPickerLayoutAlgorithm::LayoutItem(
    LayoutWrapper* layoutWrapper, OffsetF offset, std::pair<int32_t, PickerItemInfo> pos)
{
    auto layoutIndex = ContainerPickerUtils::GetLoopIndex(pos.first, totalItemCount_);
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(layoutIndex);
    CHECK_NULL_VOID(wrapper);

    offset += OffsetF(0.0f, pos.second.startPos);
    CHECK_NULL_VOID(wrapper->GetGeometryNode());
    TranslateAndRotate(wrapper->GetHostNode(), offset);
    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    wrapper->Layout();
}

void ContainerPickerLayoutAlgorithm::TranslateAndRotate(RefPtr<FrameNode> node, OffsetF& offset)
{
    float offsetY = offset.GetY() - middleItemStartPos_ - topPadding_;
    const float pi = 3.14159;
    double itemHeight = PICKER_DEFAULT_ITEM_HEIGHT.ConvertToPx();
    float radius = itemHeight * ITEM_COUNTS / (HALF * pi);
    float yScale = (pi * radius) / PICKER_DEFAULT_HEIGHT;
    float radian = (offsetY * yScale) / radius;
    float angle = radian * (HORIZONTAL_ANGLE / pi);
    float correctFactor = angle > 0 ? 1.0 : -1.0;
    double translateY = correctFactor * radius * std::sin(std::abs(radian)) - offsetY * yScale;

    if (GreatNotEqual(angle, VERTICAL_ANGLE)) {
        angle = VERTICAL_ANGLE;
    } else if (LessNotEqual(angle, -VERTICAL_ANGLE)) {
        angle = -VERTICAL_ANGLE;
    } else {
        translateY = translateY / yScale;
        offset.AddY(translateY);
    }
    NG::ViewAbstract::SetRotate(node.GetRawPtr(), NG::Vector5F(1.0f, 0.0f, 0.0f, -angle, 0.0f));
}

} // namespace OHOS::Ace::NG