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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_BAR_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_BAR_LAYOUT_ALGORITHM_H

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"

namespace OHOS::Ace::NG {

struct ItemInfo {
    float startPos = 0.0f;
    float endPos = 0.0f;
};

class ACE_EXPORT TabBarLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(TabBarLayoutAlgorithm, LayoutAlgorithm);

public:
    TabBarLayoutAlgorithm() = default;
    ~TabBarLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void SetCurrentDelta(float currentDelta)
    {
        currentDelta_ = currentDelta;
    }

    void SetTabBarStyle(TabBarStyle tabBarStyle)
    {
        tabBarStyle_ = tabBarStyle;
    }

    float GetScrollMargin()
    {
        return scrollMargin_;
    }

    void SetJumpIndex(std::optional<int32_t> jumpIndex)
    {
        jumpIndex_ = jumpIndex;
    }

    std::optional<int32_t> GetJumpIndex()
    {
        return jumpIndex_;
    }

    void SetTargetIndex(std::optional<int32_t> targetIndex)
    {
        targetIndex_ = targetIndex;
    }

    void SetFocusIndex(std::optional<int32_t> focusIndex)
    {
        focusIndex_ = focusIndex;
    }

    void SetVisibleItemPosition(std::map<int32_t, ItemInfo> visibleItemPosition)
    {
        visibleItemPosition_ = visibleItemPosition;
    }

    std::map<int32_t, ItemInfo> GetVisibleItemPosition()
    {
        return visibleItemPosition_;
    }

    void SetCanOverScroll(bool canOverScroll)
    {
        canOverScroll_ = canOverScroll;
    }

    float GetBarGridMargin()
    {
        return barGridMargin_;
    }

private:
    void MeasureFixedMode(LayoutWrapper* layoutWrapper, SizeF frameSize);
    void MeasureScrollableMode(LayoutWrapper* layoutWrapper, SizeF frameSize);
    LayoutConstraintF GetChildConstraint(LayoutWrapper* layoutWrapper, SizeF& frameSize);
    void LayoutChildren(LayoutWrapper* layoutWrapper, const SizeF& contentSize, OffsetF& childOffset);
    void LayoutMask(LayoutWrapper* layoutWrapper, const std::map<int32_t, OffsetF>& childOffsetDelta);
    void HandleSpaceBetweenOrCenterLayoutStyle(LayoutWrapper* layoutWrapper);
    void HandleAlwaysAverageSplitLayoutStyle(LayoutWrapper* layoutWrapper);
    void MeasureVisibleItems(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint);
    void MeasureTargetIndex(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint);
    void MeasureJumpIndex(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint);
    void MeasureFocusIndex(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint);
    void MeasureWithOffset(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint);
    void AdjustPosition(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint,
        int32_t startIndex, int32_t endIndex, float startPos, float endPos);
    void MeasureItem(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint, int32_t index);
    void MeasureItemSecond(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint, SizeF& frameSize);
    void LayoutForward(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint,
        int32_t& endIndex, float& endPos);
    void LayoutBackward(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint,
        int32_t& startIndex, float& startPos);
    void MeasureMaxHeight(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint);
    GridSizeType GetGridSizeType(const SizeF& frameSize) const;
    float GetGridWidth(const BarGridColumnOptions& option, const SizeF& frameSize, int32_t columns) const;
    float ApplyBarGridAlign(const RefPtr<TabBarLayoutProperty>& layoutProperty, const SizeF& contentSize) const;
    void ApplySymmetricExtensible(LayoutWrapper* layoutWrapper, float allocatedWidth);
    void ApplyLayoutMode(LayoutWrapper* layoutWrapper, float allocatedWidth);
    float GetContentMainSize(LayoutWrapper* layoutWrapper, const SizeF& contentSize);
    void CalculateItemWidthsForSymmetricExtensible(LayoutWrapper* layoutWrapper,
        const std::vector<float>& spaceRequests, const std::vector<float>& leftBuffer,
        const std::vector<float>& rightBuffer, float allocatedWidth);
    void MeasureMask(LayoutWrapper* layoutWrapper) const;
    void UpdateChildMarginProperty(float rightMargin, float leftMargin, const RefPtr<LayoutWrapper>& childWrapper);
    bool GetBarAdaptiveHeight(LayoutWrapper* layoutWrapper);
    bool GetNoMinHeightLimit(LayoutWrapper* layoutWrapper);
    bool NeedAdaptForAging(RefPtr<FrameNode> host);
    void SetTabBarMargin(RefPtr<LayoutWrapper> layoutWrapper, int32_t index);
    void UpdateMaxLines(LayoutWrapper* layoutWrapper, int32_t index);
    float GetCurrentOffset(RefPtr<TabBarLayoutProperty>& layoutProperty, ScrollableBarModeOptions& layoutStyle);
    void CheckBorderAndPadding(SizeF& frameSize, const PaddingPropertyF& padding);

    bool isRTL_ = false;
    Axis axis_ = Axis::NONE;
    TabBarStyle tabBarStyle_;
    int32_t childCount_ = 0;
    float scrollMargin_ = 0.0f;
    float contentMainSize_ = 0.0f;
    float visibleChildrenMainSize_ = 0.0f;
    float startMainPos_ = 0.0f;
    float endMainPos_ = 0.0f;
    float currentDelta_ = 0.0f;
    float barGridMargin_ = 0.0f;
    float verticalPadding_ = 0.0f;
    std::map<int32_t, float> visibleItemLength_;
    std::map<int32_t, ItemInfo> visibleItemPosition_;
    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> targetIndex_;
    std::optional<int32_t> focusIndex_;
    std::optional<float> maxHeight_;
    std::optional<float> defaultHeight_;
    bool isBarAdaptiveHeight_ = false;
    bool isNoMinHeightLimit_ = false;
    bool useItemWidth_ = true;
    bool canOverScroll_ = false;
    Dimension leftAndRightMargin_ = 0.0_vp;
    Dimension indicatorStyleMarginTop_ = 0.0_vp;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_BAR_LAYOUT_ALGORITHM_H
