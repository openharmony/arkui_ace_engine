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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_SIDE_BAR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_SIDE_BAR_PATTERN_H

#include <optional>

#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/manager/recoverable/recoverable_view.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_layout_algorithm.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_side_bar_layout_algorithm.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/event/pan_event.h"
#include "core/components/common/properties/gradient.h"
#include "core/animation/curve.h"

namespace OHOS::Ace::NG {

class TabsSideBarPattern : public Pattern {
    DECLARE_ACE_TYPE(TabsSideBarPattern, Pattern);

public:
    TabsSideBarPattern() = default;
    ~TabsSideBarPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TabsSideBarLayoutAlgorithm>();
    }

    void SetHeaderNode(const RefPtr<UINode>& header)
    {
        headerNode_ = header;
    }

    void SetFooterNode(const RefPtr<UINode>& footer)
    {
        footerNode_ = footer;
    }

    void SetBottomBarNode(const RefPtr<UINode>& bottomBar)
    {
        bottomBarNode_ = bottomBar;
    }

    RefPtr<UINode> GetHeaderNode() const
    {
        return curHeaderNode_;
    }

    RefPtr<FrameNode> GetBottomBarContainerNode() const
    {
        return bottomBarContainerNode_;
    }

    RefPtr<FrameNode> GetHeaderContainerNode() const
    {
        return headerContainerNode_;
    }

    RefPtr<FrameNode> GetTabListNode() const
    {
        return tabListNode_;
    }

    RefPtr<FrameNode> GetHeaderContainerMaskBlurNode() const
    {
        return headerContainerMaskBlurNode_;
    }

    RefPtr<FrameNode> GetHeaderContainerMaskNode() const
    {
        return headerContainerMaskNode_;
    }

    RefPtr<FrameNode> GetBottomBarMaskBlurNode() const
    {
        return bottomBarMaskBlurNode_;
    }

    RefPtr<FrameNode> GetBottomBarMaskNode() const
    {
        return bottomBarMaskNode_;
    }

    RefPtr<FrameNode> GetFooterContainerNode() const
    {
        return footerContainerNode_;
    }

    void SetSwiperController(const RefPtr<SwiperController>& controller)
    {
        swiperController_ = controller;
    }

    void SetSideBarSearchableOptions(const TabsSidebarSearchableOptions& options)
    {
        incommingOptions_ = options;
    }

    void CreateChildNodeIfNeeded(const RefPtr<FrameNode>& tabsNode);

    bool IsScrollEffectEnabled() const
    {
        return isScrollEffectEnabled_;
    }

    bool IsBottomBarScrollEffectEnabled() const
    {
        return isBottomBarScrollEffectEnabled_;
    }

private:
    void OnModifyDone() override;
    void CreateTabListIfNeeded(const RefPtr<FrameNode>& tabsNode);
    void UpdateTabListIfNeeded();
    void UpdateHeaderNodeIfNeeded();
    void UpdateFooterNodeIfNeeded();
    void UpdateBottomBarNodeIfNeeded();
    void UpdateSearchNodeIfNeeded();
    void OnSearchChange(const std::u16string& newText);
    void CreateHeaderContainerIfNeeded();
    void CreateBottomBarContainerIfNeeded();
    RefPtr<FrameNode> CreateSearchContainer();
    void CreateMaskNodeIfNeeded();
    void CreateBottomBarMaskNodeIfNeeded();
    void OnTabListScroll(float totalOffset, float scrollableDistance);

    // Gradual blur effect
    void InitHeaderContainerScrollEffect(bool isScrollEffectEnabled);
    void UpdateHeaderContainerBlurStyle(float scrollScale);
    void InitBottomBarScrollEffect(bool isScrollEffectEnabled);
    void UpdateBottomBarBlurStyle(float scrollScale);
    void InitScrollEffectImpl(bool isScrollEffectEnabled, bool& isEnabledFlag, float& cachedScale,
        const RefPtr<FrameNode>& maskBlurNode, const RefPtr<FrameNode>& maskNode,
        GradientDirection direction);
    void UpdateBlurStyleImpl(float scrollScale, float& cachedScale, bool isEnabled,
        const RefPtr<FrameNode>& maskBlurNode, const RefPtr<FrameNode>& maskNode,
        GradientDirection direction);
    RefPtr<FrameNode> CreateEffectNode(const std::string& tag);

    WeakPtr<FrameNode> tabsNode_ = nullptr;
    RefPtr<UINode> headerNode_ = nullptr;
    RefPtr<UINode> footerNode_ = nullptr;
    RefPtr<UINode> bottomBarNode_ = nullptr;
    std::optional<TabsSidebarSearchableOptions> incommingOptions_;
    TabsSidebarSearchableOptions searchableOptions_;
    RefPtr<UINode> curHeaderNode_ = nullptr;
    RefPtr<UINode> curFooterNode_ = nullptr;
    RefPtr<UINode> curBottomBarNode_ = nullptr;
    RefPtr<FrameNode> searchContainerNode_ = nullptr;
    RefPtr<FrameNode> headerContainerNode_ = nullptr;
    RefPtr<FrameNode> bottomBarContainerNode_ = nullptr;
    RefPtr<FrameNode> footerContainerNode_ = nullptr;
    RefPtr<FrameNode> tabListNode_ = nullptr;
    RefPtr<SwiperController> swiperController_ = nullptr;

    // Gradual blur effect nodes & state
    RefPtr<FrameNode> headerContainerMaskBlurNode_ = nullptr;
    RefPtr<FrameNode> headerContainerMaskNode_ = nullptr;
    bool isScrollEffectEnabled_ = false;
    float scrollScale_ = -1.0f;

    // BottomBar gradual blur effect nodes & state
    RefPtr<FrameNode> bottomBarMaskBlurNode_ = nullptr;
    RefPtr<FrameNode> bottomBarMaskNode_ = nullptr;
    bool isBottomBarScrollEffectEnabled_ = false;
    float bottomBarScrollScale_ = -1.0f;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_SIDE_BAR_PATTERN_H
