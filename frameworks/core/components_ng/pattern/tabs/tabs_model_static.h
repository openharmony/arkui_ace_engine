/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_MODEL_STATIC_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"
#include "core/components_ng/pattern/tabs/tabs_controller.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"

namespace OHOS::Ace::NG {

class SwiperPaintProperty;
class ACE_EXPORT TabsModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetTabBarPosition(FrameNode* frameNode, const std::optional<BarPosition>& tabBarPositionOpt);
    static void InitIndex(FrameNode* tabsNode, const std::optional<int32_t>& indexOpt);
    static RefPtr<TabsControllerNG> GetSwiperController(FrameNode* frameNode);
    static void SetIsVertical(FrameNode* frameNode, bool isVertical);
    static void SetScrollable(FrameNode* frameNode, bool scrollable);
    static void SetScrollableBarModeOptions(FrameNode* frameNode, const ScrollableBarModeOptions& option);
    static void SetTabBarMode(FrameNode* frameNode, const std::optional<TabBarMode>& tabBarModeOpt);
    static void SetTabBarWidth(FrameNode* frameNode, const std::optional<Dimension>& tabBarWidth);
    static void SetTabBarHeight(FrameNode* frameNode, const std::optional<Dimension>& tabBarHeightOpt);
    static void SetAnimationDuration(FrameNode* frameNode, float duration);
    static void SetAnimateMode(FrameNode* frameNode, const std::optional<TabAnimateMode>& modeOpt);
    static void SetEdgeEffect(FrameNode* frameNode, const std::optional<int32_t>& edgeEffect);
    static void SetOnChange(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& onChange);
    static void SetOnSelected(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& onSelected);
    static void SetOnTabBarClick(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& onTabBarClick);
    static void SetOnUnselected(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& onUnselected);
    static void SetOnAnimationStart(FrameNode* frameNode, AnimationStartEvent&& onAnimationStart);
    static void SetOnAnimationEnd(FrameNode* frameNode, AnimationEndEvent&& onAnimationEnd);
    static void SetOnGestureSwipe(FrameNode* frameNode, GestureSwipeEvent&& onGestureSwipe);
    static void SetFadingEdge(FrameNode* frameNode, bool fadingEdge);
    static void SetDivider(FrameNode* frameNode, const std::optional<TabsItemDivider>& dividerOpt);
    static void InitDivider(FrameNode* frameNode);
    static void SetBarOverlap(FrameNode* frameNode, bool barOverlap);
    static void SetBarBackgroundBlurStyle(FrameNode* frameNode, const BlurStyleOption& styleOption);
    static void SetBarBackgroundColor(FrameNode* frameNode,  const std::optional<Color>& backgroundColorOpt);
    static void SetBarGridAlign(FrameNode* frameNode, const BarGridColumnOptions& BarGridColumnOptions);
    static void SetIsCustomAnimation(FrameNode* frameNode, bool isCustom);
    static void SetOnCustomAnimation(FrameNode* frameNode, TabsCustomAnimationEvent&& onCustomAnimation);
    static void SetBarBackgroundEffect(FrameNode* frameNode, const EffectOption& effectOption);
    static void SetPageFlipMode(FrameNode* frameNode, int32_t options);
    static void SetOnContentWillChange(FrameNode* frameNode, std::function<bool(int32_t, int32_t)>&& callback);
    static void SetCachedMaxCount(FrameNode* frameNode, std::optional<int32_t> cachedMaxCount,
        std::optional<TabsCacheMode> cacheMode);
    static void SetOnChangeEvent(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& onChangeEvent);

private:
    static RefPtr<TabsNode> GetOrCreateTabsNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
    static RefPtr<SwiperController> GetSwiperController(const RefPtr<FrameNode>& swiperNode,
        const RefPtr<SwiperController>& swiperController);
    static void InitTabsNode(RefPtr<TabsNode> tabsNode, const RefPtr<SwiperController>& swiperController);
    static void InitSelectedMaskNode(const RefPtr<FrameNode>& selectedMaskNode);
    static void InitUnselectedMaskNode(const RefPtr<FrameNode>& maskNode);
    static void InitAccessibilityZIndex(RefPtr<FrameNode>& swiperNode, RefPtr<FrameNode>& tabBarNode);
    static RefPtr<TabBarLayoutProperty> GetTabBarLayoutProperty(FrameNode* frameNode);
    static RefPtr<SwiperLayoutProperty> GetSwiperLayoutProperty(FrameNode* frameNode);
    static RefPtr<SwiperPaintProperty> GetSwiperPaintProperty(FrameNode* frameNode);
    static RefPtr<TabBarPaintProperty> GetTabBarPaintProperty(FrameNode* frameNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_MODEL_STATIC_H