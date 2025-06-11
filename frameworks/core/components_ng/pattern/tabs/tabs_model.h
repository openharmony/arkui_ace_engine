/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_MODEL_H

#include <mutex>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components/tab_bar/tab_controller.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components/tab_bar/tabs_event.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/tabs/tab_content_transition_proxy.h"
#include "core/event/ace_events.h"
#include "core/pipeline/pipeline_context.h"
#include "ui/view/components/tabs/tabs_data.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace {

enum class TabsCacheMode {
    CACHE_BOTH_SIDE = 0,
    CACHE_LATEST_SWITCHED
};

namespace {
enum class TabJsResType {
    BAR_BACKGROUND_COLOR,
    BAR_WIDTH,
    BAR_HEIGHT,
    BAR_GRID_GUTTER,
    BAR_GRID_MARGIN,
    DIVIDER_STROKE_WIDTH,
    DIVIDER_COLOR,
    DIVIDER_START_MARGIN,
    DIVIDER_END_MARGIN,
    SCROLLABLE_BAR_MARGIN,
    COLOR,
    INACTIVE_COLOR,
    BlurStyle_INACTIVE_COLOR
};
}

struct TabsItemDivider final {
    Dimension strokeWidth = 0.0_vp;
    Dimension startMargin = 0.0_vp;
    Dimension endMargin = 0.0_vp;
    Color color = Color::BLACK;
    bool isNull = false;
    TabsItemDivider()
    {
        auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
        if (!pipelineContext) {
            return;
        }
        auto tabTheme = pipelineContext->GetTheme<TabTheme>();
        if (!tabTheme) {
            return;
        }
        color = tabTheme->GetDividerColor();
    }
    bool operator==(const TabsItemDivider& itemDivider) const
    {
        return (strokeWidth == itemDivider.strokeWidth) && (startMargin == itemDivider.startMargin) &&
               (endMargin == itemDivider.endMargin) && (color == itemDivider.color) && (isNull == itemDivider.isNull);
    }
};

struct BarGridColumnOptions final {
    int32_t sm = -1;
    int32_t md = -1;
    int32_t lg = -1;
    Dimension gutter = 0.0_vp;
    Dimension margin = 0.0_vp;

    BarGridColumnOptions()
    {
        auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
        if (!pipelineContext) {
            return;
        }
        auto tabTheme = pipelineContext->GetTheme<TabTheme>();
        if (!tabTheme) {
            return;
        }
        gutter = tabTheme->GetTabBarColumnGutter();
        margin = tabTheme->GetTabBarColumnMargin();
    }

    bool operator==(const BarGridColumnOptions& option) const
    {
        return (sm == option.sm) && (md == option.md) && (lg == option.lg) && (margin == option.margin) &&
               (gutter == option.gutter);
    }
};

using TabsCustomAnimationEvent = std::function<TabContentAnimatedTransition(int32_t from, int32_t to)>;

class ACE_FORCE_EXPORT TabsModel {
public:
    static TabsModel* GetInstance();
    virtual ~TabsModel() = default;

    virtual void Create(BarPosition barPosition, int32_t index, const RefPtr<TabController>& tabController,
        const RefPtr<SwiperController>& swiperController) = 0;
    virtual void Pop() = 0;
    virtual void SetIndex(int32_t index) = 0;
    virtual void SetTabBarPosition(BarPosition tabBarPosition) = 0;
    virtual void SetBarBackgroundBlurStyle(const BlurStyleOption& styleOption) {}
    virtual void SetTabBarMode(TabBarMode tabBarMode) = 0;
    virtual void SetTabBarWidth(const Dimension& tabBarWidth) = 0;
    virtual void SetTabBarHeight(const Dimension& tabBarHeight) = 0;
    virtual void SetWidthAuto(bool isAuto) = 0;
    virtual void SetHeightAuto(bool isAuto) = 0;
    virtual void SetBarAdaptiveHeight(bool barAdaptiveHeight) = 0;
    virtual void SetNoMinHeightLimit(bool noMinHeightLimit) = 0;
    virtual void SetIsVertical(bool isVertical) = 0;
    virtual void SetScrollable(bool scrollable) = 0;
    virtual void SetAnimationCurve(const RefPtr<Curve>& curve) {};
    virtual void SetAnimationDuration(float duration) = 0;
    virtual void SetOnChange(std::function<void(const BaseEventInfo*)>&& onChange) = 0;
    virtual void SetOnTabBarClick(std::function<void(const BaseEventInfo*)>&& onTabBarClick) = 0;
    virtual void SetOnUnselected(std::function<void(const BaseEventInfo*)>&& onUnselected) {}
    virtual void SetOnAnimationStart(AnimationStartEvent&& onAnimationStart) {}
    virtual void SetOnAnimationEnd(AnimationEndEvent&& onAnimationEnd) {}
    virtual void SetOnGestureSwipe(GestureSwipeEvent&& gestureSwipe) {}
    virtual void SetOnSelected(std::function<void(const BaseEventInfo*)>&& onSelected) {}
    virtual void SetDivider(const TabsItemDivider& divider) = 0;
    virtual void SetDividerColorByUser(bool isByUser) = 0;
    virtual void SetFadingEdge(bool fadingEdge) = 0;
    virtual void SetBarOverlap(bool barOverlap) = 0;
    virtual void SetOnChangeEvent(std::function<void(const BaseEventInfo*)>&& onChangeEvent) = 0;
    virtual void SetBarBackgroundColor(const Color& backgroundColor) = 0;
    virtual void SetBarBackgroundColorByUser(bool isByUser) = 0;
    virtual void SetClipEdge(bool clipEdge) = 0;
    virtual void SetScrollableBarModeOptions(const ScrollableBarModeOptions& option) = 0;
    virtual void ResetScrollableBarModeOptions() = 0;
    virtual void SetBarGridAlign(const BarGridColumnOptions& BarGridColumnOptions) = 0;
    virtual void SetIsCustomAnimation(bool isCustom) {}
    virtual void SetOnCustomAnimation(TabsCustomAnimationEvent&& onCustomAnimation) {}
    virtual void SetOnContentWillChange(std::function<bool(int32_t, int32_t)>&& callback) {}
    virtual void SetAnimateMode(TabAnimateMode mode) {}
    virtual void SetEdgeEffect(EdgeEffect edgeEffect) {}
    virtual void SetBarBackgroundEffect(const EffectOption& effectOption) {}
    virtual void SetPageFlipMode(int32_t pageFlipMode) {}
    virtual void SetBarModifier(std::function<void(WeakPtr<NG::FrameNode>)>&& onApply) {}
    virtual void SetCachedMaxCount(std::optional<int32_t> cachedMaxCount, TabsCacheMode cacheMode) {}
    virtual void CreateWithResourceObj(TabJsResType colorType, const RefPtr<ResourceObject>& resObj) {}

private:
    static std::unique_ptr<TabsModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_MODEL_H
