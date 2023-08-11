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
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
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
    void SetTabBarMode(TabBarMode tabBarMode) override;
    void SetTabBarWidth(const Dimension& tabBarWidth) override;
    void SetTabBarHeight(const Dimension& tabBarHeight) override;
    void SetBarAdaptiveHeight(bool barAdaptiveHeight) override;
    void SetIsVertical(bool isVertical) override;
    void SetScrollable(bool scrollable) override;
    void SetAnimationDuration(float duration) override;
    void SetOnChange(std::function<void(const BaseEventInfo*)>&& onChange) override;
    void SetOnTabBarClick(std::function<void(const BaseEventInfo*)>&& onTabBarClick) override;
    void SetDivider(const TabsItemDivider& divider) override;
    void SetFadingEdge(bool fadingEdge) override;
    void SetBarOverlap(bool barOverlap) override;
    void SetOnChangeEvent(std::function<void(const BaseEventInfo*)>&& onChangeEvent) override;
    void SetBarBackgroundColor(const Color& backgroundColor) override;
    void SetClipEdge(bool clipEdge) override;
    void SetScrollableBarModeOptions(const ScrollableBarModeOptions& option) override;
    void SetBarGridAlign(const BarGridColumnOptions& BarGridColumnOptions) override;
    static RefPtr<TabsNode> GetOrCreateTabsNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

private:
    static RefPtr<TabBarLayoutProperty> GetTabBarLayoutProperty();
    static RefPtr<TabBarPaintProperty> GetTabBarPaintProperty();
    static RefPtr<SwiperLayoutProperty> GetSwiperLayoutProperty();
    static RefPtr<SwiperPaintProperty> GetSwiperPaintProperty();
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_MODEL_NG_H
