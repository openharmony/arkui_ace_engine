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

class ACE_EXPORT TabBarLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(TabBarLayoutAlgorithm, LayoutAlgorithm);

public:
    TabBarLayoutAlgorithm() = default;
    ~TabBarLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    const std::vector<OffsetF>& GetTabItemOffset() const
    {
        return tabItemOffset_;
    }

    void SetCurrentOffset(float currentOffset)
    {
        currentOffset_ = currentOffset;
    }

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

    void SetChildrenMainSize(float childrenMainSize)
    {
        childrenMainSize_ = childrenMainSize;
    }

    float GetChildrenMainSize() const
    {
        return childrenMainSize_;
    }

    void SetIndicator(int32_t indicator)
    {
        indicator_ = indicator;
    }

    int32_t GetIndicator() const
    {
        return indicator_;
    }

    void SetIsBuilder(bool isBuilder)
    {
        isBuilder_ = isBuilder;
    }

    void SetTabBarStyle(TabBarStyle tabBarStyle)
    {
        tabBarStyle_ = tabBarStyle;
    }

    void SetNeedSetCentered()
    {
        needSetCentered_ = true;
    }

private:
    Axis GetAxis(LayoutWrapper* layoutWrapper) const;
    void UpdateChildConstraint(LayoutConstraintF& childConstraint, const RefPtr<TabBarLayoutProperty>& layoutProperty,
        const SizeF& ideaSize, int32_t childCount, Axis axis);
    float GetSpace(LayoutWrapper* layoutWrapper, int32_t indicator, const SizeF& frameSize, Axis axis);
    float CalculateFrontChildrenMainSize(LayoutWrapper* layoutWrapper, int32_t indicator, Axis axis);
    void LayoutChildren(LayoutWrapper* layoutWrapper, const SizeF& frameSize, Axis axis, OffsetF& childOffset);
    void LayoutMask(LayoutWrapper* layoutWrapper);
    float CalculateBackChildrenMainSize(LayoutWrapper* layoutWrapper, int32_t indicator, Axis axis);

    std::vector<OffsetF> tabItemOffset_;
    float currentOffset_ = 0.0f;
    float childrenMainSize_ = 0.0f; // Children total size in main axis.
    int32_t indicator_ = 0;
    bool isBuilder_ = false;
    TabBarStyle tabBarStyle_;
    bool needSetCentered_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_BAR_LAYOUT_ALGORITHM_H
