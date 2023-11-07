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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_BAR_ITEM_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_BAR_ITEM_LAYOUT_ALGORITHM_H

#include <cstdint>

#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT BarItemLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(BarItemLayoutAlgorithm, LayoutAlgorithm);

public:
    BarItemLayoutAlgorithm() = default;
    ~BarItemLayoutAlgorithm() override = default;
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void MeasureIcon(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
        const RefPtr<LayoutProperty>& barItemLayoutProperty);

    void MeasureText(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
        const RefPtr<LayoutProperty>& barItemLayoutProperty);

    void MeasureToolbarItemText(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
        const RefPtr<LayoutProperty>& barItemLayoutProperty);

    float LayoutIcon(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
        const RefPtr<LayoutProperty>& barItemLayoutProperty, float barItemHeight);

    void LayoutText(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
        const RefPtr<LayoutProperty>& barItemLayoutProperty, float iconOffsetY);

    Dimension iconSize_;
    Dimension menuHeight_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_BAR_ITEM_LAYOUT_ALGORITHM_H
