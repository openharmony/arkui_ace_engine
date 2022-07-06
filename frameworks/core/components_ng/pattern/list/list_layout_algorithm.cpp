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

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {

constexpr int32_t ILLEGAL_INDEX = -1;
constexpr float VIEWPORT_SCALE = 0.1;

float GetMainAxisOffset(const OffsetF& offset, Axis axis)
{
    return axis == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
}

float GetMainAxisSize(const SizeF& size, Axis axis)
{
    return axis == Axis::HORIZONTAL ? size.Width() : size.Height();
}

float GetCrossAxisSize(const SizeF& size, Axis axis)
{
    return axis == Axis::HORIZONTAL ? size.Height() : size.Width();
}

void SetCrossAxisSize(float value, Axis axis, SizeF& size)
{
    if (axis == Axis::VERTICAL) {
        size.SetWidth(value);
        return;
    }
    size.SetHeight(value);
}

SizeF CreateIdealSize(const LayoutConstraintF& layoutConstraint, Axis axis, MeasureType measureType)
{
    SizeF idealSize = { -1.0f, -1.0f };
    do {
        // Use idea size first if it is valid.
        if (layoutConstraint.selfIdealSize.has_value()) {
            const auto& selfIdeaSize = layoutConstraint.selfIdealSize.value();
            idealSize.UpdateSizeWithCheck(selfIdeaSize);
            if (idealSize.IsNonNegative()) {
                break;
            }
        }

        if (measureType == MeasureType::MATCH_PARENT && layoutConstraint.parentIdealSize.has_value()) {
            idealSize.UpdateIllegalSizeWithCheck(*layoutConstraint.parentIdealSize);
            if (idealSize.IsNonNegative()) {
                break;
            }
        }
        if (GetCrossAxisSize(idealSize, axis) < 0) {
            auto parentCrossSize = GetCrossAxisSize(layoutConstraint.parentIdealSize.value_or(SizeF(-1, -1)), axis);
            if (parentCrossSize < 0) {
                parentCrossSize = GetCrossAxisSize(layoutConstraint.maxSize, axis);
            }
            SetCrossAxisSize(parentCrossSize, axis, idealSize);
        }
    } while (false);
    idealSize.UpdateIllegalSizeWithCheck(layoutConstraint.maxSize);
    return idealSize;
}

void UpdateListItemConstraint(Axis axis, const SizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = selfIdealSize;
    if (axis == Axis::VERTICAL) {
        contentConstraint.maxSize.SetHeight(std::numeric_limits<float>::infinity());
        auto width = selfIdealSize.Width();
        if (width == std::numeric_limits<float>::infinity()) {
            contentConstraint.maxSize.SetWidth(width);
            contentConstraint.minSize.SetWidth(width);
        }
        return;
    }
    contentConstraint.maxSize.SetWidth(std::numeric_limits<float>::infinity());
    auto height = selfIdealSize.Height();
    if (height == std::numeric_limits<float>::infinity()) {
        contentConstraint.maxSize.SetHeight(height);
        contentConstraint.minSize.SetHeight(height);
    }
}

} // namespace

void ListLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    auto idealSize =
        CreateIdealSize(listLayoutProperty->GetLayoutConstraint().value(), axis, listLayoutProperty->GetMeasureType());
    if (GetMainAxisSize(idealSize, axis) == std::numeric_limits<float>::infinity()) {
        LOGE("the list is infinity, error");
        return;
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    MinusPaddingToSize(listLayoutProperty->CreatePaddingPropertyF(), idealSize);
    // calculate main size.
    auto mainSize = GetMainAxisSize(idealSize, axis);
    auto cachedSize = mainSize * VIEWPORT_SCALE;
    startMainPos_ = currentOffset_ - cachedSize;
    endMainPos_ = currentOffset_ + mainSize + cachedSize;
    LOGD("pre start index: %{public}d, pre end index: %{public}d", preStartIndex_, preEndIndex_);

    // calculate child layout constraint.
    auto contentLayoutConstraint = listLayoutProperty->CreateChildConstraint();
    UpdateListItemConstraint(axis, idealSize, contentLayoutConstraint.value());

    // calculate cached items.
    itemPosition_.clear();
    auto cachedInfo = LayoutOrRecycleCachedItems(layoutWrapper, contentLayoutConstraint.value(), axis);
    LOGD("cached item edge info : %{public}d, pos: %{public}f", cachedInfo.first, cachedInfo.second);

    // check if need request new item.
    int32_t newStartIndex = 0;
    float newStartPos = 0.0f;

    // forward path
    if (NonNegative(currentOffset_)) {
        if (cachedInfo.first != -1) {
            newStartIndex = cachedInfo.first + 1;
            newStartPos = cachedInfo.second;
        }
        auto info =
            RequestNewItemsForward(layoutWrapper, contentLayoutConstraint.value(), newStartIndex, newStartPos, axis);
        if (info.second < endMainPos_) {
            // adjust offset.
            currentOffset_ = info.second - mainSize;
        }
        endIndex_ = info.first != -1 ? info.first : 0;
        if (layoutWrapper->GetChildren().empty()) {
            startIndex_ = 0;
        } else {
            startIndex_ = endIndex_.value() - static_cast<int32_t>(layoutWrapper->GetChildren().size()) + 1;
        }
        LOGD("new start index is %{public}d, new end index is %{public}d", startIndex_.value(), endIndex_.value());
        return;
    }

    // backward path
    if (cachedInfo.first != -1) {
        newStartIndex = cachedInfo.first - 1;
        newStartPos = cachedInfo.second;
    }
    auto info =
        RequestNewItemsBackward(layoutWrapper, contentLayoutConstraint.value(), newStartIndex, newStartPos, axis);
    if (info.second > startMainPos_) {
        // adjust offset.
        currentOffset_ = info.second;
    }
    startIndex_ = info.first != -1 ? info.first : 0;
    if (layoutWrapper->GetChildren().empty()) {
        endIndex_ = 0;
    } else {
        endIndex_ = startIndex_.value() + static_cast<int32_t>(layoutWrapper->GetChildren().size()) - 1;
    }
    LOGD("new start index is %{public}d, new end index is %{public}d", startIndex_.value(), endIndex_.value());
}

std::pair<int32_t, float> ListLayoutAlgorithm::LayoutOrRecycleCachedItems(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis)
{
    auto& children = layoutWrapper->ModifyChildren();
    if (children.empty()) {
        return { ILLEGAL_INDEX, 0.0f };
    }
    auto indexIter = children.begin();
    auto currentItemStartPos = GetMainAxisOffset((*indexIter)->GetGeometryNode()->GetFrameOffset(), axis);
    auto currentItemEndPos = currentItemStartPos;
    auto host = layoutWrapper->GetHostNode();
    auto currentIndex = preStartIndex_;
    std::list<int32_t> remainItems;
    for (; indexIter != children.end(); currentIndex++) {
        currentItemStartPos = currentItemEndPos;
        (*indexIter)->Measure(layoutConstraint);
        auto mainLength = GetMainAxisSize((*indexIter)->GetGeometryNode()->GetFrameSize(), axis);
        currentItemEndPos = currentItemStartPos + mainLength;
        itemPosition_[currentIndex] = { currentItemStartPos, currentItemEndPos };
        // backward path
        if (currentItemStartPos > endMainPos_) {
            host->RemoveChild((*indexIter)->GetHostNode());
            indexIter = children.erase(indexIter);
            continue;
        }
        // forward path
        if (currentItemEndPos < startMainPos_) {
            host->RemoveChild((*indexIter)->GetHostNode());
            indexIter = children.erase(indexIter);
            continue;
        }
        remainItems.emplace_back(currentIndex);
        indexIter++;
    }
    if (NonNegative(currentOffset_)) {
        // forward path
        if (remainItems.empty()) {
            // use the last item of cached.
            return { preEndIndex_, itemPosition_[preEndIndex_].second };
        }
        auto lastIndex = *remainItems.rbegin();
        return { lastIndex, itemPosition_[lastIndex].second };
    }
    // backward path
    if (remainItems.empty()) {
        // use the first item of cached.
        return { preStartIndex_, itemPosition_[preStartIndex_].second };
    }
    auto firstIndex = *remainItems.begin();
    return { firstIndex, itemPosition_[firstIndex].first };
}

std::pair<int32_t, float> ListLayoutAlgorithm::RequestNewItemsForward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos, Axis axis)
{
    auto host = layoutWrapper->GetHostNode();
    if (!builder_) {
        LOGW("can not find builder to request more item");
        return { ILLEGAL_INDEX, 0.0f };
    }
    auto nextIndex = startIndex;
    auto currentStartPos = startPos;
    auto currentEndPos = startPos;
    while (LessNotEqual(currentEndPos, endMainPos_)) {
        // build more item and layout.
        RefPtr<FrameNode> newChild;
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::BuildListItem");
            newChild = builder_->GetChildByIndex(nextIndex);
            if (!newChild) {
                break;
            }
        }
        newChild->MountToParent(host);
        auto childWrapper = newChild->CreateLayoutWrapperOnCreate();
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem");
            childWrapper->Measure(layoutConstraint);
        }
        auto mainLength = GetMainAxisSize(childWrapper->GetGeometryNode()->GetFrameSize(), axis);
        currentStartPos = currentEndPos;
        currentEndPos = currentEndPos + mainLength;
        if (currentEndPos < startMainPos_) {
            host->RemoveChild(newChild);
        } else {
            itemPosition_[nextIndex] = { currentStartPos, currentEndPos };
            layoutWrapper->AddChild(childWrapper);
        }
        nextIndex++;
    }
    return { nextIndex - 1, currentEndPos };
}

std::pair<int32_t, float> ListLayoutAlgorithm::RequestNewItemsBackward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos, Axis axis)
{
    auto host = layoutWrapper->GetHostNode();
    if (!builder_) {
        LOGW("can not find builder to request more item");
        return { ILLEGAL_INDEX, 0.0f };
    }
    auto nextIndex = startIndex;
    auto currentStartPos = startPos;
    auto currentEndPos = startPos;
    while (GreatNotEqual(currentStartPos, startMainPos_)) {
        // build more item and layout.
        RefPtr<FrameNode> newChild;
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::BuildListItem");
            newChild = builder_->GetChildByIndex(nextIndex);
            if (!newChild) {
                break;
            }
        }
        newChild->MountToParent(host, 0);
        auto childWrapper = newChild->CreateLayoutWrapperOnCreate();
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem");
            childWrapper->Measure(layoutConstraint);
        }
        auto mainLength = GetMainAxisSize(childWrapper->GetGeometryNode()->GetFrameSize(), axis);
        currentEndPos = currentStartPos;
        currentStartPos = currentStartPos - mainLength;
        if (currentStartPos > endMainPos_) {
            host->RemoveChild(newChild);
        } else {
            itemPosition_[nextIndex] = { currentStartPos, currentEndPos };
            layoutWrapper->AddChild(childWrapper, 0);
        }
        nextIndex--;
    }
    return { nextIndex + 1, currentStartPos };
}

void ListLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listLayoutProperty);
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingPropertyF();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto paddingOffset = OffsetF(left, top);

    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();

    // layout items.
    const auto& children = layoutWrapper->GetChildren();
    auto currentIndex = startIndex_.value_or(0);
    for (auto indexIter = children.begin(); indexIter != children.end(); indexIter++, currentIndex++) {
        auto offset = paddingOffset;
        if (axis == Axis::VERTICAL) {
            offset = offset + OffsetF(0, itemPosition_[currentIndex].first - currentOffset_);
        } else {
            offset = offset + OffsetF(itemPosition_[currentIndex].first - currentOffset_, 0);
        }
        (*indexIter)->GetGeometryNode()->SetFrameOffset(offset);
        (*indexIter)->Layout(parentOffset);
    }
}

} // namespace OHOS::Ace::NG
