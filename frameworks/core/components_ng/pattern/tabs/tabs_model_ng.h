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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_MODEL_NG_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"

namespace OHOS::Ace::NG {

class SwiperPaintProperty;
class ACE_EXPORT TabsModelNG : public OHOS::Ace::TabsModel {
public:
    void Create(BarPosition barPosition, int32_t index, const RefPtr<TabController>& tabController,
        const RefPtr<SwiperController>& swiperController) override;
    void Pop() override;
    void SetIndex(int32_t index) override;
    void SetTabBarPosition(BarPosition tabBarPosition) override;
    void SetBarBackgroundBlurStyle(const BlurStyleOption& styleOption) override;
    void SetTabBarMode(TabBarMode tabBarMode) override;
    void SetTabBarWidth(const Dimension& tabBarWidth) override;
    void SetTabBarHeight(const Dimension& tabBarHeight) override;
    void SetWidthAuto(bool isAuto) override;
    void SetHeightAuto(bool isAuto) override;
    void SetBarAdaptiveHeight(bool barAdaptiveHeight) override;
    void SetIsVertical(bool isVertical) override;
    void SetScrollable(bool scrollable) override;
    void SetAnimationDuration(float duration) override;
    void SetOnChange(std::function<void(const BaseEventInfo*)>&& onChange) override;
    void SetOnTabBarClick(std::function<void(const BaseEventInfo*)>&& onTabBarClick) override;
    void SetOnAnimationStart(AnimationStartEvent&& onAnimationStart) override;
    void SetOnAnimationEnd(AnimationEndEvent&& onAnimationEnd) override;
    void SetOnGestureSwipe(GestureSwipeEvent&& gestureSwipe) override;
    void SetDivider(const TabsItemDivider& divider) override;
    void SetFadingEdge(bool fadingEdge) override;
    void SetBarOverlap(bool barOverlap) override;
    void SetOnChangeEvent(std::function<void(const BaseEventInfo*)>&& onChangeEvent) override;
    void SetBarBackgroundColor(const Color& backgroundColor) override;
    void SetClipEdge(bool clipEdge) override;
    void SetScrollableBarModeOptions(const ScrollableBarModeOptions& option) override;
    void SetBarGridAlign(const BarGridColumnOptions& BarGridColumnOptions) override;
    void SetIsCustomAnimation(bool isCustom) override;
    void SetOnCustomAnimation(TabsCustomAnimationEvent&& onCustomAnimation) override;
    void SetOnContentWillChange(std::function<bool(int32_t, int32_t)>&& callback) override;
    void SetAnimateMode(TabAnimateMode mode) override;
    void SetEdgeEffect(EdgeEffect edgeEffect) override;
    void SetBarBackgroundEffect(const EffectOption& effectOption) override;
    static RefPtr<TabsNode> GetOrCreateTabsNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetWidthAuto(FrameNode* frameNode, bool isAuto);
    static void SetHeightAuto(FrameNode* frameNode, bool isAuto);
    static void SetTabBarMode(FrameNode* frameNode, TabBarMode tabBarMode);
    static void SetBarGridAlign(FrameNode* frameNode, const BarGridColumnOptions& BarGridColumnOptions);
    static void SetDivider(FrameNode* frameNode, const TabsItemDivider& divider);
    static void SetFadingEdge(FrameNode* frameNode, bool fadingEdge);
    static void SetBarBackgroundColor(FrameNode* frameNode, const Color& backgroundColor);
    static void SetBarBackgroundBlurStyle(FrameNode* frameNode, const BlurStyleOption& styleOption);
    static void SetBarOverlap(FrameNode* frameNode, bool barOverlap);
    static void SetIsVertical(FrameNode* frameNode, bool isVertical);
    static void SetTabBarPosition(FrameNode* frameNode, BarPosition tabBarPosition);
    static void SetScrollable(FrameNode* frameNode, bool scrollable);
    static void SetTabBarWidth(FrameNode* frameNode, const Dimension& tabBarWidth);
    static void SetTabBarHeight(FrameNode* frameNode, const Dimension& tabBarHeight);
    static void SetAnimationDuration(FrameNode* frameNode, float duration);
    static void SetBarAdaptiveHeight(FrameNode* frameNode, bool barAdaptiveHeight);
    static void SetScrollableBarModeOptions(FrameNode* frameNode, const ScrollableBarModeOptions& option);
    static void SetClipEdge(FrameNode* frameNode, bool clipEdge);
    static void SetAnimateMode(FrameNode* frameNode, TabAnimateMode mode);
    static void SetEdgeEffect(FrameNode* frameNode, int32_t edgeEffect);
    static void SetBarBackgroundEffect(FrameNode* frameNode, const EffectOption& effectOption);

private:
    static void InitTabsNode(RefPtr<TabsNode> tabsNode, const RefPtr<SwiperController>& swiperController);
    static RefPtr<SwiperController> GetSwiperController(const RefPtr<FrameNode>& swiperNode,
        const RefPtr<SwiperController>& swiperController);
    static void InitSelectedMaskNode(const RefPtr<FrameNode>& maskNode);
    static void InitUnselectedMaskNode(const RefPtr<FrameNode>& maskNode);
    static RefPtr<TabBarLayoutProperty> GetTabBarLayoutProperty();
    static RefPtr<TabBarPaintProperty> GetTabBarPaintProperty();
    static RefPtr<SwiperLayoutProperty> GetSwiperLayoutProperty();
    static RefPtr<SwiperPaintProperty> GetSwiperPaintProperty();
    static RefPtr<TabBarLayoutProperty> GetTabBarLayoutProperty(FrameNode* frameNode);
    static RefPtr<TabBarPaintProperty> GetTabBarPaintProperty(FrameNode* frameNode);
    static RefPtr<SwiperLayoutProperty> GetSwiperLayoutProperty(FrameNode* frameNode);
    static RefPtr<SwiperPaintProperty> GetSwiperPaintProperty(FrameNode* frameNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_MODEL_NG_H
