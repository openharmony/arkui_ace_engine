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
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"

namespace OHOS::Ace::NG {

struct SwiperItemInfo {
    float startPos = 0.0f;
    float endPos = 0.0f;
    RefPtr<FrameNode> node;
    OffsetF finalOffset;
    CancelableCallback<void()> task;
    bool isFinishAnimation = false;
};

class ACE_EXPORT SwiperLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(SwiperLayoutAlgorithm, LayoutAlgorithm);

public:
    using PositionMap = std::map<int32_t, SwiperItemInfo>;

    SwiperLayoutAlgorithm() = default;
    ~SwiperLayoutAlgorithm() override
    {
        std::lock_guard<std::mutex> lock(swiperMutex_);
    }

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

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
        if (GetStartIndex() == 0 && !isLoop_) {
            return itemPosition_.begin()->second.startPos;
        }
        return itemPosition_.begin()->second.startPos - spaceWidth_;
    }

    float GetEndPosition() const
    {
        if (itemPosition_.empty()) {
            return 0.0f;
        }
        if (GetEndIndex() == totalItemCount_ - 1 && !isLoop_) {
            return itemPosition_.rbegin()->second.endPos;
        }
        return itemPosition_.rbegin()->second.endPos + spaceWidth_;
    }

    void SetMainSizeIsMeasured(bool mainSizeIsMeasured)
    {
        mainSizeIsMeasured_ = mainSizeIsMeasured;
    }

    bool GetMainSizeIsMeasured() const
    {
        return mainSizeIsMeasured_;
    }

    void SetCurrentIndex(int32_t currentIndex)
    {
        currentIndex_ = currentIndex;
    }

    int32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }

    bool IsCrossMatchChild() const
    {
        return crossMatchChild_;
    }

    void SetUseCustomAnimation(bool useCustomAnimation)
    {
        useCustomAnimation_ = useCustomAnimation;
    }

    void SetCustomAnimationToIndex(std::optional<int32_t> customAnimationToIndex)
    {
        customAnimationToIndex_ = customAnimationToIndex;
    }

    void SetRemoveFromRSTreeIndex(std::optional<int32_t> removeFromRSTreeIndex)
    {
        removeFromRSTreeIndex_ = removeFromRSTreeIndex;
    }

    void SetIndexsInAnimation(const std::set<int32_t>& indexsInAnimation)
    {
        indexsInAnimation_ = indexsInAnimation;
    }

    void SetNeedUnmountIndexs(const std::set<int32_t>& needUnmountIndexs)
    {
        needUnmountIndexs_ = needUnmountIndexs;
    }

    std::set<int32_t> GetNeedUnmountIndexs() const
    {
        return needUnmountIndexs_;
    }

    void SetSwipeByGroup(bool swipeByGroup)
    {
        swipeByGroup_ = swipeByGroup;
    }

    void SetRealTotalCount(int32_t realTotalCount)
    {
        realTotalCount_ = realTotalCount;
    }

    void SetPlaceItemWidth(std::optional<float> placeItemWidth)
    {
        placeItemWidth_ = placeItemWidth;
    }

    void SetHasCachedCapture(bool hasCachedCapture)
    {
        hasCachedCapture_ = hasCachedCapture;
    }

    void SetIsCaptureReverse(bool isCaptureReverse)
    {
        isCaptureReverse_ = isCaptureReverse;
    }

    bool GetIsCaptureReverse() const
    {
        return isCaptureReverse_;
    }

    bool GetIsNeedUpdateCapture() const
    {
        return isNeedUpdateCapture_;
    }

    void SetItemsPositionInAnimation(const PositionMap& itemPositionInAnimation)
    {
        itemPositionInAnimation_ = itemPositionInAnimation;
    }

    PositionMap&& GetItemsPositionInAnimation()
    {
        return std::move(itemPositionInAnimation_);
    }

    void SetIsMeasureOneMoreItem(bool isMeasureOneMoreItem)
    {
        isMeasureOneMoreItem_ = isMeasureOneMoreItem;
    }

    void SetIsFrameAnimation(bool isFrameAnimation)
    {
        isFrameAnimation_ = isFrameAnimation;
    }

    float GetTargetStartPos() const
    {
        return targetStartPos_;
    }

    void SetCachedCount(int32_t cachedCount)
    {
        cachedCount_ = cachedCount > realTotalCount_ ? realTotalCount_ : cachedCount;
    }

    const std::set<int32_t>& GetCachedItems() const
    {
        return cachedItems_;
    }

    const LayoutConstraintF& GetLayoutConstraint() const
    {
        return childLayoutConstraint_;
    }

    void SetNextMarginIgnoreBlank(bool nextMarginIgnoreBlank)
    {
        nextMarginIgnoreBlank_ = nextMarginIgnoreBlank;
    }

    void SetIgnoreBlankOffset(float ignoreBlankOffset)
    {
        ignoreBlankOffset_ = ignoreBlankOffset;
    }

private:
    void LayoutForward(
        LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos);
    void LayoutBackward(
        LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint, int32_t endIndex, float endPos);
    bool LayoutForwardItem(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
        int32_t& currentIndex, float startPos, float& endPos);
    bool LayoutBackwardItem(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
        int32_t& currentIndex, float endPos, float& startPos);
    float GetChildMaxSize(LayoutWrapper* layoutWrapper, bool isMainAxis) const;
    int32_t GetLoopIndex(int32_t originalIndex) const;

    void LayoutSwiperIndicator(
        LayoutWrapper* layoutWrapper, const RefPtr<SwiperLayoutProperty>& swiperLayoutProperty,
        const PaddingPropertyF& padding);
    void MeasureSwiper(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint);
    void MeasureTabsCustomAnimation(LayoutWrapper* layoutWrapper);
    void MeasureSwiperCustomAnimation(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint);
    void LayoutCustomAnimation(LayoutWrapper* layoutWrapper) const;
    void LayoutItem(LayoutWrapper* layoutWrapper, OffsetF offset, std::pair<int32_t, SwiperItemInfo> pos);
    void SetInactive(
        LayoutWrapper* layoutWrapper, float startMainPos, float endMainPos, std::optional<int32_t> targetIndex);

    void PlaceDigitChild(const RefPtr<LayoutWrapper>& indicatorWrapper, const RefPtr<LayoutProperty>& layoutProperty);
    RefPtr<LayoutWrapper> GetNodeLayoutWrapperByTag(LayoutWrapper* layoutWrapper, const std::string& tagName) const;
    void MeasureArrow(const RefPtr<LayoutWrapper>& arrowWrapper, const RefPtr<LayoutProperty>& layoutProperty) const;
    void ArrowLayout(
        LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& arrowWrapper, const PaddingPropertyF padding) const;
    void ResetOffscreenItemPosition(LayoutWrapper* layoutWrapper, int32_t index, bool isForward) const;
    int32_t GetDisplayCount(LayoutWrapper* layoutWrapper) const;
    void SetInactiveOnForward(LayoutWrapper* layoutWrapper);
    void SetInactiveOnBackward(LayoutWrapper* layoutWrapper);
    void AdjustStartInfoOnSwipeByGroup(
        int32_t startIndex, const PositionMap& itemPosition, int32_t& startIndexInVisibleWindow, float& startPos);
    bool HasCustomIndicatorOffset(const RefPtr<LayoutWrapper>& indicatorWrapper);
    const OffsetF CalculateCustomOffset(
        const RefPtr<LayoutWrapper>& indicatorWrapper, const OffsetF& currentOffset);
    void CaptureMeasure(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint);
    void CaptureLayout(LayoutWrapper* layoutWrapper);
    bool IsNormalItem(const RefPtr<LayoutWrapper>& wrapper) const;
    bool CheckIsSingleCase(const RefPtr<SwiperLayoutProperty>& property);
    void UpdateLayoutInfoBeforeMeasureSwiper(
        const RefPtr<SwiperLayoutProperty>& property, const LayoutConstraintF& layoutConstraint);
    void IndicatorAndArrowMeasure(LayoutWrapper* layoutWrapper, const OptionalSizeF& parentIdealSize);
    float GetChildMainAxisSize(
        const RefPtr<LayoutWrapper>& childWrapper, const RefPtr<SwiperLayoutProperty>& swiperProperty);

    void CheckCachedItem(int32_t startIndex, int32_t endIndex, LayoutWrapper* layoutWrapper);
    void MeasureSwiperOnJump(LayoutWrapper* layoutWrapper, const LayoutConstraintF& constraint, int32_t jumpIndex);

    bool isLoop_ = true;
    float prevMargin_ = 0.0f;
    float nextMargin_ = 0.0f;

    PositionMap itemPosition_;
    PositionMap prevItemPosition_;
    PositionMap itemPositionInAnimation_;
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
    bool crossMatchChild_ = false;
    bool measured_ = false; // to distinguish first and second measure in flex layout

    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> targetIndex_;
    std::optional<int32_t> currentTargetIndex_;
    std::optional<int32_t> customAnimationToIndex_;
    std::optional<int32_t> removeFromRSTreeIndex_;
    std::optional<SizeF> leftCaptureSize_ = std::nullopt;
    std::optional<SizeF> rightCaptureSize_ = std::nullopt;
    int32_t currentIndex_ = 0;
    bool targetIsSameWithStartFlag_ = false;
    bool useCustomAnimation_ = false;
    std::set<int32_t> indexsInAnimation_;
    std::set<int32_t> needUnmountIndexs_;
    bool swipeByGroup_ = false;
    int32_t realTotalCount_ = 0;
    std::optional<float> placeItemWidth_;
    bool useCustomIndicatorOffset = false;
    bool hasCachedCapture_ = false;
    bool isCaptureReverse_ = false;
    bool isNeedUpdateCapture_ = false;
    bool isMeasureOneMoreItem_ = false;
    bool isFrameAnimation_ = false;
    bool nextMarginIgnoreBlank_ = false;
    float ignoreBlankOffset_ = 0.0f;
    std::set<int32_t> measuredItems_;
    std::set<int32_t> activeItems_;
    std::set<int32_t> cachedItems_;
    // only be used in AutoLinear mode
    float targetStartPos_ = 0.0f;
    int32_t cachedCount_ = 0;
    LayoutConstraintF childLayoutConstraint_;
    Axis axis_ = Axis::HORIZONTAL;

    std::mutex swiperMutex_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_ALGORITHM_H
