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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVIGATION_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVIGATION_LAYOUT_ALGORITHM_H

#include <cstdint>

#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavigationLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(NavigationLayoutAlgorithm, LayoutAlgorithm);

public:
    NavigationLayoutAlgorithm() = default;
    ~NavigationLayoutAlgorithm() override = default;
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void SetRealNavBarWidth(float realNavBarWidth)
    {
        realNavBarWidth_ = realNavBarWidth;
    }

    float GetRealNavBarWidth() const
    {
        return realNavBarWidth_;
    }

    void SetIfNeedInit(bool ifNeedInit)
    {
        ifNeedInit_ = ifNeedInit;
    }

    static bool IsAutoHeight(const RefPtr<LayoutProperty>& layoutProperty);

private:
    ACE_DISALLOW_COPY_AND_MOVE(NavigationLayoutAlgorithm);

    void MeasurePrimaryContentNode(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
        const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& homePositionDestSize);
    void MeasureNavBarOrHomeDestination(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
        const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& navBarSize);

    void MeasureContentChild(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
        const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& contentSize_);

    void RangeCalculation(
        const RefPtr<NavigationGroupNode>& hostNode, const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty);

    void GetRange(const RefPtr<NavigationGroupNode>& hostNode);

    void UpdateNavigationMode(const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& frameSize,
        const RefPtr<NavigationGroupNode>& hostNode);

    void SizeCalculation(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
        const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& frameSize);

    void SizeCalculationSplit(const RefPtr<NavigationGroupNode>& hostNode,
        const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& frameSize);
    void CheckSizeInSplit(const float frameWidth, const float userSetNavBarWidth, const float minNavBarWidth,
        const float minContentWidth);

    void SizeCalculationStack(const RefPtr<NavigationGroupNode>& hostNode,
        const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& frameSize);

    float CalculateNavigationWidth(const RefPtr<NavigationGroupNode>& hostNode);

    void SetNavigationHeight(LayoutWrapper* layoutWrapper, SizeF& size);

    void SizeCalculationForForceSplit(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
        const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty, const SizeF& frameSize);

    bool ifNeedInit_ = true;

    bool userSetNavBarRangeFlag_ = false;
    bool userSetMinContentFlag_ = false;
    bool userSetNavBarWidthFlag_ = false;
    Dimension minNavBarWidthValue_ = 0.0_vp;
    Dimension maxNavBarWidthValue_ = 0.0_vp;
    Dimension minContentWidthValue_ = 0.0_vp;

    float realNavBarWidth_ = 0.0f;
    float realDividerWidth_ = 0.0f;
    float realNavBarHeight_ = 0.0f;
    float realContentWidth_ = 0.0f;
    float realContentHeight_ = 0.0f;

    SizeF primaryNodeSize_ = SizeF(0.0f, 0.0f);
    SizeF navBarSize_ = SizeF(0.0f, 0.0f);
    SizeF contentSize_ = SizeF(0.0f, 0.0f);
    SizeF dividerSize_ = SizeF(0.0f, 0.0f);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVIGATION_LAYOUT_ALGORITHM_H
