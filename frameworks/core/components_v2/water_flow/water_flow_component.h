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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_WATER_FLOW_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_WATER_FLOW_COMPONENT_H

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/scroll_bar/scroll_bar_proxy.h"
#include "core/components_v2/water_flow/water_flow_position_controller.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace::V2 {
class ACE_EXPORT WaterFlowComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(WaterFlowComponent, ComponentGroup);

public:
    WaterFlowComponent(const std::list<RefPtr<Component>>& children, int32_t crossSplice)
        : ComponentGroup(children), crossSplice_(crossSplice)
    {}

    ~WaterFlowComponent() override = default;

    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    void SetMainLength(const Dimension& mainLength);
    void SetColumnsGap(const Dimension& columnsGap);
    void SetRowsGap(const Dimension& rowsGap);
    void SetFlexAlign(FlexAlign flexAlign);
    void SetRightToLeft(bool rightToLeft);
    void SetLayoutDirection(FlexDirection direction);
    void SetController(const RefPtr<V2::WaterFlowPositionController>& controller);
    void SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy);
    void SetScrolledEvent(const EventMarker& event);
    void SetScrollBarDisplayMode(DisplayMode displayMode);
    void SetScrollBarColor(const std::string& color);
    void SetScrollBarWidth(const std::string& width);

    int32_t GetCrossSplice() const
    {
        return crossSplice_;
    }

    const Dimension& GetMainLength() const
    {
        return mainLength_;
    }

    const Dimension& GetColumnsGap() const
    {
        return columnsGap_;
    }

    const Dimension& GetRowsGap() const
    {
        return rowsGap_;
    }

    FlexDirection GetDirection() const
    {
        return direction_;
    }

    FlexAlign GetFlexAlign() const
    {
        return flexAlign_;
    }

    const RefPtr<V2::WaterFlowPositionController>& GetController() const
    {
        return controller_;
    }

    const RefPtr<ScrollBarProxy>& GetScrollBarProxy() const
    {
        return scrollBarProxy_;
    }

    bool GetRightToLeft() const
    {
        return rightToLeft_;
    }

    const EventMarker& GetScrolledEvent() const
    {
        return scrolledEvent_;
    }

    DisplayMode GetScrollBarDisplayMode()
    {
        return displayMode_;
    }

    const std::string& GetScrollBarColor() const
    {
        return scrollBarColor_;
    }

    const std::string& GetScrollBarWidth() const
    {
        return scrollBarWidth_;
    }

private:
    int32_t crossSplice_ = 0;
    Dimension mainLength_ = 0.0_px;
    Dimension columnsGap_ = 0.0_px;
    Dimension rowsGap_ = 0.0_px;
    FlexDirection direction_ = FlexDirection::COLUMN;
    FlexAlign flexAlign_ = FlexAlign::CENTER;
    bool rightToLeft_ = false;

    // scroll bar attribute
    std::string scrollBarColor_;
    std::string scrollBarWidth_;
    DisplayMode displayMode_ = DisplayMode::ON;
    RefPtr<V2::WaterFlowPositionController> controller_;
    RefPtr<ScrollBarProxy> scrollBarProxy_;
    EventMarker scrolledEvent_;
};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_WATER_FLOW_COMPONENT_H
