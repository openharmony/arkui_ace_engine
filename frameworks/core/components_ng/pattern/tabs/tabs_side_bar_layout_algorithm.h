/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_SIDE_BAR_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_SIDE_BAR_LAYOUT_ALGORITHM_H

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TabsSideBarLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(TabsSideBarLayoutAlgorithm, LayoutAlgorithm);

public:
    TabsSideBarLayoutAlgorithm() = default;
    ~TabsSideBarLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    float MeasureHeaderContainer(LayoutWrapper* layoutWrapper, const SizeF& size);
    void MeasureHeaderContainerMaskNode(LayoutWrapper* layoutWrapper, const SizeF& size, float headerContainerHeight);
    void MeasureTabList(LayoutWrapper* layoutWrapper, const SizeF& size, float totalFixedHeight);
    void LayoutChild(LayoutWrapper* layoutWrapper, const RefPtr<FrameNode>& hostNode,
        const RefPtr<UINode>& childUINode, const OffsetF& offset);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_SIDE_BAR_LAYOUT_ALGORITHM_H
