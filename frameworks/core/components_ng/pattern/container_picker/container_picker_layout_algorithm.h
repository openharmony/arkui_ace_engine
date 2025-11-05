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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_LAYOUT_ALGORITHM_H

#include <optional>

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_utils.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ContainerPickerLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(ContainerPickerLayoutAlgorithm, LayoutAlgorithm);

public:
    ContainerPickerLayoutAlgorithm() = default;
    ~ContainerPickerLayoutAlgorithm() override = default;

    void SetItemPosition(const ContainerPickerUtils::PositionMap& itemPosition)
    {
        itemPosition_ = itemPosition;
        prevItemPosition_ = itemPosition_;
    }

    ContainerPickerUtils::PositionMap&& GetItemPosition()
    {
        return std::move(itemPosition_);
    }

    const std::vector<int32_t>& GetOffScreenItems()
    {
        return std::move(offScreenItemsIndex_);
    }

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void SetTotalItemCount(int32_t realTotalCount)
    {
        totalItemCount_ = realTotalCount;
    }

    int32_t GetTotalItemCount()
    {
        return totalItemCount_;
    }

    void SetPrevTotalItemCount(int32_t prevTotalCount)
    {
        prevTotalItemCount_ = prevTotalCount;
    }

    void SetCurrentDelta(float offset)
    {
        currentOffset_ = offset;
        currentDelta_ = offset;
    }

    float GetStartPosition() const
    {
        if (itemPosition_.empty()) {
            return 0.0f;
        }
        return itemPosition_.begin()->second.startPos;
    }

    float GetEndPosition() const
    {
        if (itemPosition_.empty()) {
            return 0.0f;
        }
        return itemPosition_.rbegin()->second.endPos;
    }

    int32_t GetStartIndex() const
    {
        return itemPosition_.empty() ? 0 : itemPosition_.begin()->first;
    }

    int32_t GetEndIndex() const
    {
        return itemPosition_.empty() ? 0 : itemPosition_.rbegin()->first;
    }

    void SetIsLoop(bool isLoop)
    {
        isLoop_ = isLoop;
    }

    void SetSelectedIndex(int32_t index)
    {
        if (index < 0 || index >= totalItemCount_) {
            index = 0;
        }
        selectedIndex_ = index;
    }

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

    void SetContentMainSize(float contentMainSize)
    {
        contentMainSize_ = contentMainSize;
    }

    float GetContentMainSize() const
    {
        return contentMainSize_;
    }

    float GetContentCrossSize() const
    {
        return contentCrossSize_;
    }

    void SetHeight(float height)
    {
        height_ = height;
    }

    float GetHeight() const
    {
        return height_;
    }

    void SetPickerHeight(float height)
    {
        pickerDefaultHeight_ = height;
    }

    void SetPickerHeightBeforeRotate(float height)
    {
        pickerHeightBeforeRotate_ = height;
    }

    void SetItemHeight(float height)
    {
        pickerItemHeight_ = height;
    }

    float GetTopPadding() const
    {
        return topPadding_;
    }

    void CalcMainAndMiddlePos();

    const LayoutConstraintF& GetLayoutConstraint() const
    {
        return childLayoutConstraint_;
    }

    bool IsCrossMatchChild() const
    {
        return crossMatchChild_;
    }

private:
    void LayoutItem(LayoutWrapper* layoutWrapper, OffsetF offset, std::pair<int32_t, PickerItemInfo> pos);
    void HandleLayoutPolicy(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize);
    void HandleAspectRatio(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize);
    void MeasureHeight(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize);
    void MeasureWidth(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize);
    float GetChildMaxWidth(LayoutWrapper* layoutWrapper) const;
    void MeasurePickerItems(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint);
    void ResetOffscreenItemPosition(LayoutWrapper* layoutWrapper, int32_t index) const;
    void SetPatternContentMainSize(LayoutWrapper* layoutWrapper);
    void MeasureBelow(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, int32_t startIndex,
        float startPos, bool cachedLayout = false);
    void MeasureAbove(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, int32_t endIndex,
        float endPos, bool cachedLayout = false);
    bool MeasureBelowItem(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
        int32_t& currentIndex, float startPos, float& endPos);
    bool MeasureAboveItem(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
        int32_t& currentIndex, float endPos, float& startPos);
    bool NeedMeasureBelow(int32_t currentIndex, float currentStartPos, float endMainPos, bool cachedLayout) const;
    bool NeedMeasureAbove(int32_t currentIndex, float currentEndPos, float startMainPos, bool cachedLayout) const;
    void AdjustOffsetOnBelow(float currentEndPos);
    void AdjustOffsetOnAbove(float currentStartPos);
    std::pair<int32_t, PickerItemInfo> CalcCurrentMiddleItem() const;
    void TranslateAndRotate(RefPtr<FrameNode> node, OffsetF& offset);
    void UpdateFadeItems(RefPtr<FrameNode> node, std::pair<int32_t, PickerItemInfo> pos);

    LayoutConstraintF childLayoutConstraint_;
    ContainerPickerUtils::PositionMap itemPosition_;
    ContainerPickerUtils::PositionMap prevItemPosition_;
    Axis axis_ = Axis::VERTICAL;
    Alignment align_ = Alignment::CENTER;

    std::optional<int32_t> targetIndex_;
    std::vector<int32_t> offScreenItemsIndex_;

    int32_t totalItemCount_ = 0;
    int32_t prevTotalItemCount_ = 0;
    int32_t selectedIndex_ = 0;

    float startMainPos_ = 0.0f;
    float endMainPos_ = 0.0f;
    float topPadding_ = 0.0f;
    float height_ = 0.0f; // usage: record picker real height
    float contentMainSize_ = 0.0f;  // usage: picker content area height
    float contentCrossSize_ = 0.0f; // usage: picker content area width
    float middleItemStartPos_ = 0.0f;
    float middleItemEndPos_ = 0.0f;
    float currentDelta_ = 0.0f;
    float currentOffset_ = 0.0f;

    float pickerItemHeight_ = 0.0f;
    float pickerDefaultHeight_ = 0.0f;
    float pickerHeightBeforeRotate_ = 0.0f;

    bool crossMatchChild_ = false;
    bool measured_ = false;
    bool isLoop_ = false;
    bool canOverScroll_ = true;
    bool reMeasure_ = false;

    std::mutex pickerMutex_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_LAYOUT_ALGORITHM_H
