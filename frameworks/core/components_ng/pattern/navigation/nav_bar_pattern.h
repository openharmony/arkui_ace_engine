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
#include "core/components_ng/pattern/navigation/nav_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class NavBarPattern : public Pattern {
    DECLARE_ACE_TYPE(NavBarPattern, Pattern);

public:
    NavBarPattern() = default;
    ~NavBarPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<NavBarLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<NavBarLayoutAlgorithm>();
    }

    bool GetspringEffect()
    {
        return springEffect_;
    }

    void SetTitleBarMenuItems(const std::vector<NG::BarItem>& menuItems)
    {
        titleBarMenuItems_ = menuItems;
    }

    const std::vector<NG::BarItem>& GetTitleBarMenuItems() const
    {
        return titleBarMenuItems_;
    }

    void SetToolBarMenuItems(const std::vector<NG::BarItem>& menuItems)
    {
        toolBarMenuItems_ = menuItems;
    }

    const std::vector<NG::BarItem>& GetToolBarMenuItems() const
    {
        return toolBarMenuItems_;
    }

protected:
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

private:
    void RegistOritationListener();
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    void OnModifyDone() override;
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleOnDragStart(float offset);
    void HandleOnDragUpdate(float offset);
    void HandleOnDragEnd();
    void InitCoordinationEvent();
    void OnCoordScrollStart();
    void OnCoordScrollUpdate(float offset);
    void OnCoordScrollEnd();
    RefPtr<FrameNode> FindScrollableChild();
    float offset_ = 0.0f;
    bool springEffect_ = false;
    RefPtr<PanEvent> panEvent_;
    WeakPtr<FrameNode> scrollableNode_;
    bool isOritationListenerRegisted_ = false;
    bool isHideToolbar_ = false;
    DeviceOrientation deviceOrientationType_ = DeviceOrientation::PORTRAIT;
    std::vector<NG::BarItem> titleBarMenuItems_;
    std::vector<NG::BarItem> toolBarMenuItems_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAV_BAR_PATTERN_H