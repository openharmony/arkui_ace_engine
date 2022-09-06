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

private:
    Axis GetAxis(LayoutWrapper* layoutWrapper) const;
    void UpdateChildConstraint(LayoutConstraintF& childConstraint,
        const RefPtr<TabBarLayoutProperty>& layoutProperty, const SizeF& ideaSize, int32_t childCount, Axis axis);

    std::vector<OffsetF> tabItemOffset_;
    float currentOffset_ = 0.0f;
    float childrenMainSize_ = 0.0f; // Children total size in main axis.
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_BAR_LAYOUT_ALGORITHM_H
