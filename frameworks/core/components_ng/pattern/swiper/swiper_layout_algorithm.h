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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_ALGORITHM_H

#include <cstdint>
#include <optional>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

struct SwiperItemInfo {
    float startPos = 0.0f;
    float endPos = 0.0f;
    RefPtr<FrameNode> node;
    OffsetF finialOffset;
};

class ACE_EXPORT SwiperLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(SwiperLayoutAlgorithm, LayoutAlgorithm);

public:
    using PositionMap = std::map<int32_t, SwiperItemInfo>;

    SwiperLayoutAlgorithm() = default;
    ~SwiperLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void LayoutForward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis,
        int32_t startIndex, float startPos);
    void LayoutBackward(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis,
        int32_t endIndex, float endPos);
    bool LayoutForwardItem(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis,
        int32_t& currentIndex, float startPos, float& endPos);
    bool LayoutBackwardItem(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis,
        int32_t& currentIndex, float endPos, float& startPos);
    float GetChildMaxSize(LayoutWrapper* layoutWrapper, Axis axis, bool isMainAxis) const;
    int32_t GetLoopIndex(int32_t originalIndex) const;

    void SetItemsPosition(const PositionMap& itemPosition)
    {
        itemPosition_ = itemPosition;
    }

    PositionMap&& GetItemPosition()
    {
        return std::move(itemPosition_);
    }

    void SetJumpIndex(int32_t index)
    {
        jumpIndex_ = index;
    }

    void SetCurrentDelta(float offset)
    {
        currentDelta_ = offset;
        currentOffset_ = offset;
    }

    void SetOverScrollFeature()
    {
        overScrollFeature_ = true;
    }

    void SetCanOverScroll(bool canOverScroll)
    {
        canOverScroll_ = canOverScroll;
    }

    void SetTotalItemCount(int32_t totalItemCount)
    {
        totalItemCount_ = totalItemCount;
    }

    float GetContentMainSize() const
    {
        return contentMainSize_;
    }

    void SetContentMainSize(float contentMainSize)
    {
        contentMainSize_ = contentMainSize;
    }

    float GetContentCrossSize() const
    {
        return contentCrossSize_;
    }

    void SetContentCrossSize(float contentCrossSize)
    {
        contentCrossSize_ = contentCrossSize;
    }

    void SetCurrentOffset(float offset)
    {
        currentOffset_ = offset;
    }

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

    void SetTargetIndex(std::optional<int32_t> targetIndex)
    {
        targetIndex_ = targetIndex;
    }

    void SetIsLoop(bool isLoop)
    {
        isLoop_ = isLoop;
    }

    int32_t GetStartIndex() const
    {
        return itemPosition_.empty() ? 0 : itemPosition_.begin()->first;
    }

    int32_t GetEndIndex() const
    {
        return itemPosition_.empty() ? 0 : itemPosition_.rbegin()->first;
    }

    float GetStartPosition() const
    {
        if (itemPosition_.empty()) {
            return 0.0f;
        }
        if (GetStartIndex() == 0) {
            return itemPosition_.begin()->second.startPos;
        }
        return itemPosition_.begin()->second.startPos - spaceWidth_;
    }

    float GetEndPosition() const
    {
        if (itemPosition_.empty()) {
            return 0.0f;
        }
        if (GetEndIndex() == totalItemCount_ - 1) {
            return itemPosition_.rbegin()->second.endPos;
        }
        return itemPosition_.rbegin()->second.endPos + spaceWidth_;
    }

    int32_t GetAutoPlayCurrentIndex() const
    {
        return autoPlayCurrentIndex_;
    }

    void SetMainSizeIsMeasured(bool mainSizeIsMeasured)
    {
        mainSizeIsMeasured_ = mainSizeIsMeasured;
    }

    bool GetMainSizeIsMeasured() const
    {
        return mainSizeIsMeasured_;
    }

    int32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }

    void SetIsNeedResetPrevMarginAndNextMargin()
    {
        isNeedResetPrevMarginAndNextMargin_ = false;
    }

    bool GetIsNeedResetPrevMarginAndNextMargin() const
    {
        return isNeedResetPrevMarginAndNextMargin_;
    }

private:
    void MeasureSwiper(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, Axis axis);
    void SetInactive(
        LayoutWrapper* layoutWrapper, float startMainPos, float endMainPos, std::optional<int32_t> targetIndex);

    void PlaceDigitChild(const RefPtr<LayoutWrapper>& indicatorWrapper, const RefPtr<LayoutProperty>& layoutProperty);
    double GetValidEdgeLength(float swiperLength, float indicatorLength, const Dimension& edge);
    RefPtr<LayoutWrapper> GetNodeLayoutWrapperByTag(LayoutWrapper* layoutWrapper, const std::string& tagName) const;
    void MeasureArrow(const RefPtr<LayoutWrapper>& arrowWrapper, const RefPtr<LayoutProperty>& layoutProperty) const;
    void ArrowLayout(
        LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& arrowWrapper, const PaddingPropertyF padding) const;
    bool isLoop_ = true;
    float prevMargin_ = 0.0f;
    float nextMargin_ = 0.0f;

    PositionMap itemPosition_;
    int32_t autoPlayCurrentIndex_ = 0;
    float currentOffset_ = 0.0f;
    float currentDelta_ = 0.0f;
    float startMainPos_ = 0.0f;
    float endMainPos_ = 0.0f;

    float paddingBeforeContent_ = 0.0f;
    float paddingAfterContent_ = 0.0f;
    float contentMainSize_ = 0.0f;
    float contentCrossSize_ = 0.0f;
    int32_t totalItemCount_ = 0;
    bool mainSizeIsDefined_ = false;

    float spaceWidth_ = 0.0f;
    bool overScrollFeature_ = false;
    bool canOverScroll_ = false;

    bool mainSizeIsMeasured_ = false;

    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> targetIndex_;
    std::optional<int32_t> currentTargetIndex_;
    int32_t currentIndex_ = 0;
    bool targetIsSameWithStartFlag_ = false;
    bool isNeedResetPrevMarginAndNextMargin_ = false;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_ALGORITHM_H
