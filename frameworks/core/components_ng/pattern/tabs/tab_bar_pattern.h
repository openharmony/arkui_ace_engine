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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_PATTERN_H

#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_algorithm.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_method.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"

namespace OHOS::Ace::NG {

using TabBarBuilderFunc = std::function<void()>;
struct TabBarParam {
    std::string text;
    std::string icon;
    TabBarBuilderFunc builder;
};

class TabBarPattern : public Pattern {
    DECLARE_ACE_TYPE(TabBarPattern, Pattern);

public:
    explicit TabBarPattern(const RefPtr<SwiperController>& swiperController) : swiperController_(swiperController) {};
    ~TabBarPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TabBarLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<TabBarLayoutAlgorithm>();
        layoutAlgorithm->SetCurrentOffset(currentOffset_);
        return layoutAlgorithm;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<TabBarPaintProperty>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<TabBarPaintMethod>();
    }

    void UpdateCurrentOffset(float offset);

    void UpdateIndicator(int32_t indicator);

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void InitClick(const RefPtr<GestureEventHub>& gestureHub);
    void InitScrollable(const RefPtr<GestureEventHub>& gestureHub);
    void InitTouch(const RefPtr<GestureEventHub>& gestureHub);
    void HandleClick(const GestureEvent& info) const;
    void HandleTouchEvent(const TouchLocationInfo& info);

    RefPtr<ClickEvent> clickEvent_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<ScrollableEvent> scrollableEvent_;
    RefPtr<SwiperController> swiperController_;

    float currentOffset_ = 0.0f;
    Axis axis_ = Axis::HORIZONTAL;
    std::vector<OffsetF> tabItemOffsets_;

    bool isRTL_ = false; // TODO Adapt RTL.
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_PATTERN_H