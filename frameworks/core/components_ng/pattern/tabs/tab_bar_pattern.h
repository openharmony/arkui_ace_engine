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
#include <unordered_map>

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
#include "core/event/mouse_event.h"

namespace OHOS::Ace::NG {

using TabBarBuilderFunc = std::function<void()>;
class TabBarParam : public virtual Referenced {
public:
    TabBarParam(const std::string& textParam, const std::string& iconParam, TabBarBuilderFunc&& builderParam)
        : text_(textParam), icon_(iconParam), builder_(std::move(builderParam)) {};

    const std::string& GetIcon() const
    {
        return icon_;
    }

    void SetIcon(const std::string& icon)
    {
        icon_ = icon;
    }

    const std::string& GetText() const
    {
        return text_;
    }

    void SetText(const std::string& text)
    {
        text_ = text;
    }

    bool HasBuilder() const
    {
        return builder_ != nullptr;
    }

    void SetBuilder(TabBarBuilderFunc&& builderParam)
    {
        builder_ = std::move(builderParam);
    }

    void ExecuteBuilder() const
    {
        if (builder_ != nullptr) {
            builder_();
        }
    }

private:
    std::string text_;
    std::string icon_;
    TabBarBuilderFunc builder_;
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
        layoutAlgorithm->SetChildrenMainSize(childrenMainSize_);
        layoutAlgorithm->SetCurrentOffset(currentOffset_);
        layoutAlgorithm->SetIndicator(indicator_);
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

    void SetChildrenMainSize(float childrenMainSize)
    {
        childrenMainSize_ = childrenMainSize;
    }

    void SetIndicator(int32_t indicator)
    {
        indicator_ = indicator;
    }

    void UpdateCurrentOffset(float offset);

    void UpdateIndicator(int32_t indicator);

    void UpdateTextColor(int32_t indicator);

    void AddTabBarItemType(int32_t tabContentId, bool isBuilder)
    {
        tabBarType_.emplace(std::make_pair(tabContentId, isBuilder));
    }

    bool IsContainsBuilder();

    void SetAnimationDuration(int32_t animationDuration)
    {
        animationDuration_ = animationDuration;
    }

    void SetTouching(bool isTouching)
    {
        touching_ = isTouching;
    }

    bool IsTouching() const
    {
        return touching_;
    }

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void InitClick(const RefPtr<GestureEventHub>& gestureHub);
    void InitScrollable(const RefPtr<GestureEventHub>& gestureHub);
    void InitTouch(const RefPtr<GestureEventHub>& gestureHub);
    void InitHoverEvent();
    void InitMouseEvent();

    void HandleMouseEvent(const MouseInfo& info);
    void HandleHoverEvent(bool isHover);
    void HandleHoverOnEvent(int32_t index);
    void HandleMoveAway(int32_t index);
    void HandleClick(const GestureEvent& info);
    void HandleTouchEvent(const TouchLocationInfo& info);

    void HandleTouchDown(int32_t index);
    void HandleTouchUp(int32_t index);
    int32_t CalculateSelectedIndex(const Offset& info);

    void PlayPressAnimation(int32_t index, float endOpacityRatio);

    RefPtr<ClickEvent> clickEvent_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<ScrollableEvent> scrollableEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<InputEvent> hoverEvent_;
    RefPtr<SwiperController> swiperController_;

    float currentOffset_ = 0.0f;
    float childrenMainSize_ = 0.0f;
    int32_t indicator_ = 0;
    Axis axis_ = Axis::HORIZONTAL;
    std::vector<OffsetF> tabItemOffsets_;
    std::unordered_map<int32_t, bool> tabBarType_;
    std::optional<int32_t> animationDuration_;

    bool isRTL_ = false; // TODO Adapt RTL.

    bool touching_ = false; // whether the item is in touching
    bool isHover_ = false;
    float hoverOpacity_ = 0.0;
    int32_t touchingIndex_ = 0;
    std::optional<int32_t> hoverIndex_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_PATTERN_H