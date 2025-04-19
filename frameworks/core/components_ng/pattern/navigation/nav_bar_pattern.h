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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAV_BAR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAV_BAR_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_event_hub.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"
#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class NavBarPattern : public NavDestinationPatternBase {
    DECLARE_ACE_TYPE(NavBarPattern, NavDestinationPatternBase);

public:
    NavBarPattern() = default;
    ~NavBarPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<NavBarLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<NavBarLayoutAlgorithm>();
    }
    
    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<NavBarEventHub>();
    }

    void OnCoordScrollStart() override;
    float OnCoordScrollUpdate(float offset, float currentOffset) override;
    void OnCoordScrollEnd() override;
    bool CanCoordScrollUp(float offset) const override;

    void OnAttachToFrameNode() override;

    bool NeedCoordWithScroll() override
    {
        return !isHideTitlebar_;
    }
    OffsetF GetShowMenuOffset(const RefPtr<BarItemNode>& barItemNode, const RefPtr<FrameNode>& menuNode);

    float GetTitleBarHeightLessThanMaxBarHeight() const override;

protected:
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

    void MountTitleBar(const RefPtr<FrameNode>& host, bool& needRunTitleBarAnimation);

private:
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    RefPtr<PanEvent> panEvent_;
    WeakPtr<FrameNode> scrollableNode_;
    RefPtr<FrictionMotion> motion_;
    RefPtr<Animator> controller_;
    NavigationTitleMode titleMode_ = NavigationTitleMode::FREE;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAV_BAR_PATTERN_H