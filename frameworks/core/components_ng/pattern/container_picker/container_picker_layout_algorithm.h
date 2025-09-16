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
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"

namespace OHOS::Ace::NG {

struct PickerItemInfo {
    float startPos = 0.0f;
    float endPos = 0.0f;
    RefPtr<FrameNode> node = nullptr;
    OffsetF finalOffset = OffsetF();
    CancelableCallback<void()> task = CancelableCallback<void()>();
    bool isFinishAnimation = false;
};

class ACE_EXPORT ContainerPickerLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(ContainerPickerLayoutAlgorithm, LayoutAlgorithm);
public:
    ContainerPickerLayoutAlgorithm() = default;
    ~ContainerPickerLayoutAlgorithm() override = default;

    using PositionMap = std::map<int32_t, PickerItemInfo>;

    void SetItemsPosition(const PositionMap& itemPosition)
    {
        itemPosition_ = itemPosition;
    }

    PositionMap&& GetItemPosition()
    {
        return std::move(itemPosition_);
    }

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void SetTotalItemCount(int32_t realTotalCount)
    {
        totalItemCount_ = realTotalCount;
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
        if (GetEndIndex() == totalItemCount_ - 1 && !isLoop_) {
            return itemPosition_.rbegin()->second.endPos;
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

    int32_t GetLoopIndex(int32_t originalIndex) const
    {
        if (totalItemCount_ <= 0) {
            return originalIndex;
        }
        auto loopIndex = originalIndex;
        while (loopIndex < 0) {
            loopIndex = loopIndex + totalItemCount_;
        }
        loopIndex %= totalItemCount_;
        return loopIndex;
    }

    void SetCurrentIndex(int32_t currentIndex)
    {
        currentIndex_ = currentIndex;
    }

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

    void SetContentMainSize(float contentMainSize)
    {
        contentMainSize_ = contentMainSize;
        oldContentMainSize_ = contentMainSize;
    }

    float GetContentMainSize() const
    {
        return contentMainSize_;
    }

    const LayoutConstraintF& GetLayoutConstraint() const
    {
        return childLayoutConstraint_;
    }

private:
    void LayoutItem(LayoutWrapper* layoutWrapper, OffsetF offset, std::pair<int32_t, PickerItemInfo> pos);
    void MeasureSize(LayoutConstraintF& contentConstraint);
    void HandleLayoutPolicy(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize);
    void MeasurePicker(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint);
    void SetPatternContentMainSize(LayoutWrapper* layoutWrapper);
    void LayoutForward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, int32_t startIndex,
        float startPos, bool cachedLayout = false);
    void LayoutBackward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, int32_t endIndex,
        float endPos, bool cachedLayout = false);
    bool LayoutForwardItem(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
        int32_t& currentIndex, float startPos, float& endPos);
    bool LayoutBackwardItem(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
        int32_t& currentIndex, float endPos, float& startPos);
    void SetInactiveOnForward(LayoutWrapper* layoutWrapper);
    void SetInactiveOnBackward(LayoutWrapper* layoutWrapper);
    bool NeedMeasureForward(int32_t currentIndex, float currentEndPos, float forwardEndPos, bool cachedLayout) const;
    bool NeedMeasureBackward(
        int32_t currentIndex, float currentStartPos, float backwardStartPos, bool isStretch, bool cachedLayout) const;
    void AdjustOffsetOnForward(float currentEndPos);
    void AdjustOffsetOnBackward(float currentStartPos);
    float GetChildMainAxisSize(const RefPtr<LayoutWrapper>& childWrapper);
    void ResetOffscreenItemPosition(LayoutWrapper* layoutWrapper, int32_t index, bool isForward) const;
    void AdjustStartInfoOnSwipeByGroup(
        int32_t startIndex, const PositionMap& itemPosition, int32_t& startIndexInVisibleWindow, float& startPos);
    LayoutConstraintF childLayoutConstraint_;
    PositionMap itemPosition_;
    PositionMap prevItemPosition_;
    PositionMap itemPositionInAnimation_;
    Axis axis_ = Axis::VERTICAL;

    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> targetIndex_;
    std::set<int32_t> measuredItems_;

    int32_t showCount_ = 7;
    int32_t totalItemCount_ = 0;
    int32_t currentIndex_ = 0;
    float startMainPos_ = 0.0f;
    float endMainPos_ = 0.0f;
    float targetStartPos_ = 0.0f;
    float contentMainSize_ = 0.0f;
    float oldContentMainSize_ = 0.0f;
    float contentCrossSize_ = 0.0f;
    float currentDelta_ = 0.0f;
    float currentOffset_ = 0.0f;
    float pickerItemHeight_ = 40.0f;
    float dividerSpacingFontScale_ = 1.0f;
    float gradientFontScale_ = 1.0f;
    bool mainSizeIsMeasured_ = false;
    bool measured_ = false;
    bool isLoop_ = true;
    bool overScrollFeature_ = false;
    bool canOverScroll_ = false;

    std::mutex pickerMutex_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_LAYOUT_ALGORITHM_H