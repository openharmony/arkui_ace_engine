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
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/property/position_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const float UNDEFINED_SIZE = -1.0f;
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

    HandleLayoutPolicy(layoutWrapper, contentIdealSize);
    MeasureHeight(layoutWrapper, contentIdealSize);

    CalcMainAndMiddlePos();
    auto childLayoutConstraint = ContainerPickerUtils::CreateChildConstraint(pickerLayoutProperty, contentIdealSize);
    childLayoutConstraint_ = childLayoutConstraint;
    if (totalItemCount_ > 0) {
        middleIndexInVisibleWindow_ = selectedIndex_;
        MeasurePickerItems(layoutWrapper);
    } else {
        itemPosition_.clear();
    }
    MeasureWidth(layoutWrapper, contentIdealSize);
    HandleAspectRatio(layoutWrapper, contentIdealSize);
    SetPatternHeight(layoutWrapper);
    HandleOffScreenItems(layoutWrapper);

    const auto& padding = pickerLayoutProperty->CreatePaddingAndBorder();
    AddPaddingToSize(padding, contentIdealSize);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    if (geometryNode) {
        geometryNode->SetFrameSize(contentIdealSize.ConvertToSizeT());
    }
    measured_ = true;
    SetPatternContentMainSize(layoutWrapper);
}

void ContainerPickerLayoutAlgorithm::HandleLayoutPolicy(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(pickerLayoutProperty);
    auto contentConstraint = pickerLayoutProperty->GetContentLayoutConstraint().value();

    // handle layout policy.
    auto layoutPolicy = pickerLayoutProperty->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value()) {
        auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        // when the main/cross axis is set matchParent, Update contentIdealSize
        if (layoutPolicy->IsWidthMatch()) {
            auto layoutPolicySize = ConstrainIdealSizeByLayoutPolicy(
                contentConstraint, widthLayoutPolicy, LayoutCalPolicy::MATCH_PARENT, axis_);
            contentIdealSize.UpdateIllegalSizeWithCheck(layoutPolicySize);
        }
    }
}

void ContainerPickerLayoutAlgorithm::HandleAspectRatio(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(pickerLayoutProperty);
    if (!pickerLayoutProperty->HasAspectRatio() || LessOrEqual(pickerLayoutProperty->GetAspectRatio(), 0)) {
        return;
    }
    auto newHeight = contentCrossSize_ / pickerLayoutProperty->GetAspectRatio();
    if (NearEqual(newHeight, height_)) {
        return;
    }
    height_ = newHeight;
    contentMainSize_ = newHeight;
    contentIdealSize.SetMainSize(newHeight, axis_);
    reMeasure_ = true;
    itemPosition_.clear();
    CalcMainAndMiddlePos();
    if (totalItemCount_ > 0) {
        MeasurePickerItems(layoutWrapper);
    } else {
        itemPosition_.clear();
    }
}

void ContainerPickerLayoutAlgorithm::MeasureHeight(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize)
{
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto contentConstraint = pickerLayoutProperty->GetContentLayoutConstraint().value();
    auto layoutPolicy = pickerLayoutProperty->GetLayoutPolicyProperty();
    float mainSize = GetMainAxisSize(contentConstraint.selfIdealSize, axis_).value_or(UNDEFINED_SIZE);

    // measure height
    float height;
    auto parentMainSize =
        CreateIdealSizeByPercentRef(contentConstraint, axis_, MeasureType::MATCH_PARENT_MAIN_AXIS, true)
            .MainSize(axis_);
    if (layoutPolicy.has_value()) {
        if (layoutPolicy->IsHeightMatch() && parentMainSize.has_value()) {
            height = parentMainSize.value();
        } else if (layoutPolicy->IsHeightFix() || layoutPolicy->IsHeightWrap()) {
            height = parentMainSize.has_value() ? std::min(pickerDefaultHeight_, parentMainSize.value())
                                                : pickerDefaultHeight_;
        } else {
            height = Negative(mainSize) ? std::min(pickerDefaultHeight_, parentMainSize.value()) : mainSize;
        }
    } else {
        height = Negative(mainSize) ? std::min(pickerDefaultHeight_, parentMainSize.value()) : mainSize;
    }
    height_ = height;
    contentMainSize_ = height;
    contentIdealSize.SetMainSize(height, axis_);
}

void ContainerPickerLayoutAlgorithm::MeasureWidth(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize)
{
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto contentConstraint = pickerLayoutProperty->GetContentLayoutConstraint().value();
    auto layoutPolicy = pickerLayoutProperty->GetLayoutPolicyProperty();
    float crossSize = GetCrossAxisSize(contentConstraint.selfIdealSize, axis_).value_or(UNDEFINED_SIZE);

    // measure width
    float width;
    auto childMaxWidth = GetChildMaxWidth(layoutWrapper);
    auto parentCrossSize =
        CreateIdealSizeByPercentRef(contentConstraint, axis_, MeasureType::MATCH_PARENT_CROSS_AXIS, true)
            .CrossSize(axis_);

    auto commonSetWidth = [crossSize, parentCrossSize, childMaxWidth, &width]() -> bool {
        bool crossMatchChild = false;
        if (Negative(crossSize)) {
            width = parentCrossSize.has_value() ? std::min(childMaxWidth, parentCrossSize.value()) : childMaxWidth;
            crossMatchChild = true;
        } else {
            width = crossSize;
        }
        return crossMatchChild;
    };

    if (layoutPolicy.has_value()) {
        if (layoutPolicy->IsWidthWrap()) {
            width = parentCrossSize.has_value() ? std::min(childMaxWidth, parentCrossSize.value()) : childMaxWidth;
            crossMatchChild_ = true;
        } else if (layoutPolicy->IsWidthFix()) {
            width = std::min(childMaxWidth, contentConstraint.maxSize.Width());
            crossMatchChild_ = true;
        } else if (layoutPolicy->IsWidthMatch() && parentCrossSize.has_value()) {
            width = parentCrossSize.value();
        } else {
            crossMatchChild_ = commonSetWidth();
        }
    } else {
        crossMatchChild_ = commonSetWidth();
    }
    contentCrossSize_ = width;
    contentIdealSize.SetCrossSize(width, axis_);
}

void ContainerPickerLayoutAlgorithm::CalcMainAndMiddlePos()
{
    startMainPos_ = std::max((height_ - pickerHeightBeforeRotate_) / HALF, 0.0f);
    endMainPos_ = startMainPos_ + std::min(height_, pickerHeightBeforeRotate_);
    if (Positive(currentDelta_)) {
        endMainPos_ += currentDelta_;
    } else {
        startMainPos_ += currentDelta_;
    }
    middleItemStartPos_ = (height_ - pickerItemHeight_) / HALF;
    middleItemEndPos_ = (height_ + pickerItemHeight_) / HALF;
    if (reMeasure_) {
        middleItemStartPos_ += currentOffsetFromMiddle_;
        middleItemEndPos_ += currentOffsetFromMiddle_;
    }
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

void ContainerPickerLayoutAlgorithm::SetPatternHeight(LayoutWrapper* layoutWrapper)
{
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto pickerPattern = hostNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    pickerPattern->SetHeightFromAlgo(height_);
}

float ContainerPickerLayoutAlgorithm::GetPatternHeight(LayoutWrapper* layoutWrapper)
{
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(hostNode, height_);
    auto pickerPattern = hostNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, height_);
    return pickerPattern->GetHeightFromAlgo();
}

void ContainerPickerLayoutAlgorithm::MeasurePickerItems(LayoutWrapper* layoutWrapper)
{
    float startPos = middleItemStartPos_;
    float endPos = middleItemEndPos_;
    middleIndexInVisibleWindow_ = selectedIndex_;
    if (!itemPosition_.empty()) {
        auto prevHeight = GetPatternHeight(layoutWrapper);
        auto middleItem =
            ContainerPickerUtils::CalcCurrentMiddleItem(itemPosition_, prevHeight, totalItemCount_, isLoop_);
        currentOffsetFromMiddle_ = (middleItem.second.startPos + middleItem.second.endPos - prevHeight) / HALF;
        middleIndexInVisibleWindow_ = middleItem.first;
        startPos += currentOffsetFromMiddle_;
        endPos += currentOffsetFromMiddle_;
        itemPosition_.clear();
    }

    MeasureBelow(layoutWrapper, middleIndexInVisibleWindow_, startPos);
    MeasureAbove(layoutWrapper, middleIndexInVisibleWindow_ - 1, GetStartPosition());
}

void ContainerPickerLayoutAlgorithm::HandleOffScreenItems(LayoutWrapper* layoutWrapper)
{
    std::vector<int32_t> prevItemsIndex;
    std::vector<int32_t> curItemsIndex;
    for (const auto& pair : prevItemPosition_) {
        prevItemsIndex.push_back(ContainerPickerUtils::GetLoopIndex(pair.first, prevTotalItemCount_));
    }
    for (const auto& pair : itemPosition_) {
        curItemsIndex.push_back(ContainerPickerUtils::GetLoopIndex(pair.first, totalItemCount_));
    }
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
    CHECK_NULL_VOID(layoutWrapper);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(childWrapper);

    auto childGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeometryNode);

    OffsetF offset(0.0f, 0.0f);
    offset.SetY(-pickerItemHeight_);
    childGeometryNode->SetMarginFrameOffset(offset);

    NG::ViewAbstract::SetRotate(
        childWrapper->GetHostNode().GetRawPtr(), NG::Vector5F(1.0f, 0.0f, 0.0f, VERTICAL_ANGLE, 0.0f));
    childWrapper->Measure(childLayoutConstraint_);
    childWrapper->Layout();
}

void ContainerPickerLayoutAlgorithm::MeasureBelow(
    LayoutWrapper* layoutWrapper, int32_t startIndex, float startPos, bool cachedLayout)
{
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    float endMainPos = endMainPos_;
    int32_t measuredCount = -1;

    auto currentIndex = startIndex - 1;
    do {
        currentStartPos = currentEndPos;
        auto result = MeasureBelowItem(layoutWrapper, currentIndex, currentStartPos, currentEndPos);
        if (!result) {
            break;
        }
        ++measuredCount;
    } while (NeedMeasureBelow(currentStartPos, endMainPos));
    if (canOverScroll_ || isLoop_) {
        return;
    }

    if (LessNotEqual(currentEndPos, endMainPos_ + contentMainSize_ / HALF)) {
        AdjustOffsetOnBelow(currentEndPos);
    }
}

void ContainerPickerLayoutAlgorithm::MeasureAbove(
    LayoutWrapper* layoutWrapper, int32_t endIndex, float endPos, bool cachedLayout)
{
    float currentStartPos = endPos;
    float currentEndPos = 0.0f;
    float startMainPos = startMainPos_;
    auto currentIndex = endIndex + 1;
    int32_t measuredCount = 0;

    do {
        currentEndPos = currentStartPos;
        auto result = MeasureAboveItem(layoutWrapper, currentIndex, currentEndPos, currentStartPos);
        if (!result) {
            break;
        }
        ++measuredCount;
    } while (NeedMeasureAbove(currentEndPos, startMainPos));
    if (canOverScroll_ || isLoop_) {
        return;
    }

    if (GreatNotEqual(currentStartPos, startMainPos_ - contentMainSize_ / HALF)) {
        AdjustOffsetOnAbove(currentStartPos);
    }
}

bool ContainerPickerLayoutAlgorithm::MeasureBelowItem(
    LayoutWrapper* layoutWrapper, int32_t& currentIndex, float startPos, float& endPos)
{
    if ((currentIndex + 1 >= totalItemCount_ && !isLoop_) ||
        (static_cast<int32_t>(itemPosition_.size()) >= totalItemCount_)) {
        return false;
    }

    auto measureIndex = ContainerPickerUtils::GetLoopIndex(currentIndex + 1, totalItemCount_);
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(measureIndex);
    ++currentIndex;
    if (!reMeasure_) {
        wrapper->Measure(childLayoutConstraint_);
    }

    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(pickerLayoutProperty, false);

    endPos = startPos + pickerItemHeight_;
    itemPosition_[currentIndex] = { startPos, endPos, wrapper->GetHostNode() };
    return true;
}

bool ContainerPickerLayoutAlgorithm::MeasureAboveItem(
    LayoutWrapper* layoutWrapper, int32_t& currentIndex, float endPos, float& startPos)
{
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(pickerLayoutProperty, false);
    if (currentIndex - 1 < 0 && !isLoop_) {
        return false;
    }

    auto measureIndex = ContainerPickerUtils::GetLoopIndex(currentIndex - 1, totalItemCount_);
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(measureIndex);
    --currentIndex;
    if (!reMeasure_) {
        wrapper->Measure(childLayoutConstraint_);
    }

    startPos = endPos - pickerItemHeight_;
    itemPosition_[currentIndex] = { startPos, endPos, wrapper->GetHostNode() };
    return true;
}

bool ContainerPickerLayoutAlgorithm::NeedMeasureBelow(float currentStartPos, float endMainPos) const
{
    return LessNotEqual(currentStartPos, endMainPos);
}

bool ContainerPickerLayoutAlgorithm::NeedMeasureAbove(float currentEndPos, float startMainPos) const
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

void ContainerPickerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pickerLayoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(pickerLayoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    CalcMainAndMiddlePos();
    auto padding = pickerLayoutProperty->CreatePaddingAndBorder();
    topPadding_ = padding.top.value_or(0.0);
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
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto size = geometryNode->GetPaddingSize();
    auto translate = Alignment::GetAlignPosition(size, wrapper->GetGeometryNode()->GetMarginFrameSize(), align_);
    offset += OffsetF(translate.GetX(), pos.second.startPos);
    CHECK_NULL_VOID(wrapper->GetGeometryNode());
    TranslateAndRotate(wrapper->GetHostNode(), offset);
    UpdateFadeItems(wrapper->GetHostNode(), pos);
    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    wrapper->Layout();
}

void ContainerPickerLayoutAlgorithm::TranslateAndRotate(RefPtr<FrameNode> node, OffsetF& offset)
{
    if (NearZero(pickerHeightBeforeRotate_)) {
        return;
    }
    float offsetY = offset.GetY() - middleItemStartPos_ - topPadding_;
    const float pi = 3.14159;
    float radius = pickerItemHeight_ * ITEM_COUNTS / (HALF * pi);
    float yScale = (pi * radius) / pickerHeightBeforeRotate_;
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

void ContainerPickerLayoutAlgorithm::UpdateFadeItems(RefPtr<FrameNode> node, std::pair<int32_t, PickerItemInfo> pos)
{
    CHECK_NULL_VOID(node);
    auto middleItem = ContainerPickerUtils::CalcCurrentMiddleItem(itemPosition_, height_, totalItemCount_, isLoop_);
    auto middleIndex = middleItem.first;
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (pos.first != middleIndex) {
        renderContext->UpdateOpacity(FADE_OPACITY);
    } else {
        renderContext->UpdateOpacity(1);
    }
}

} // namespace OHOS::Ace::NG
