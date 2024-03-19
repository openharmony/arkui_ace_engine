/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_LAYOUT_ALGORITHM_H

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TabsLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(TabsLayoutAlgorithm, LayoutAlgorithm);

public:
    TabsLayoutAlgorithm() = default;
    ~TabsLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    BarPosition GetBarPosition(LayoutWrapper* layoutWrapper) const;
    Axis GetAxis(LayoutWrapper* layoutWrapper) const;
    TabsItemDivider GetDivider(LayoutWrapper* layoutWrapper) const;
    float MeasureDivider(const RefPtr<TabsLayoutProperty>& layoutProperty,
        const RefPtr<LayoutWrapper>& dividerWrapper, const SizeF& idealSize);
    SizeF MeasureSwiper(const RefPtr<TabsLayoutProperty>& layoutProperty, RefPtr<LayoutWrapper>& swiperWrapper,
        const SizeF& idealSize, const SizeF& tabBarSize, const float dividerWidth);
    std::vector<OffsetF> LayoutOffsetList(
        LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& tabBarWrapper, const SizeF& frameSize) const;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_LAYOUT_ALGORITHM_H
