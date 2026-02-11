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

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/scroll_bar/scroll_bar_proxy.h"
#include "core/components_v2/common/common_def.h"
#include "core/components_v2/water_flow/water_flow_position_controller.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace::V2 {
class ACE_EXPORT WaterFlowComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(WaterFlowComponent, ComponentGroup);

public:
    explicit WaterFlowComponent(const std::list<RefPtr<Component>>& children) : ComponentGroup(children) {}

    ~WaterFlowComponent() override = default;

    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    void SetColumnsGap(const Dimension& columnsGap);
    void SetRowsGap(const Dimension& rowsGap);
    void SetLayoutDirection(FlexDirection direction);
    void SetController(const RefPtr<V2::WaterFlowPositionController>& controller);
    void SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy);
    void SetScrolledEvent(const EventMarker& event);
    void SetScrollBarDisplayMode(DisplayMode displayMode);
    void SetScrollBarColor(const std::string& color);
    void SetScrollBarWidth(const std::string& width);
    void SetColumnsArgs(const std::string& columnsArgs);
    void SetRowsArgs(const std::string& rowsArgs);
    void SetMinWidth(const Dimension& minWidth);
    void SetMinHeight(const Dimension& minHeight);
    void SetMaxWidth(const Dimension& maxWidth);
    void SetMaxHeight(const Dimension& maxHeight);
    void SetFooterComponent(RefPtr<Component> component);

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

    const RefPtr<V2::WaterFlowPositionController>& GetController() const
    {
        return controller_;
    }

    const RefPtr<ScrollBarProxy>& GetScrollBarProxy() const
    {
        return scrollBarProxy_;
    }

    const EventMarker& GetScrolledEvent() const
    {
        return scrolledEvent_;
    }

    DisplayMode GetScrollBarDisplayMode()
    {
        return displayMode_;
    }

    const std::string& GetColumnsArgs() const
    {
        return columnsArgs_;
    }

    const std::string& GetRowsArgs() const
    {
        return rowsArgs_;
    }

    const Dimension& GetMinWidth() const
    {
        return minWidth_;
    }

    const Dimension& GetMinHeight() const
    {
        return minHeight_;
    }

    const Dimension& GetMaxWidth() const
    {
        return maxWidth_;
    }

    const Dimension& GetMaxHeight() const
    {
        return maxHeight_;
    }

    RefPtr<Component> GetFooterComponent() const
    {
        return footerComponent_;
    }

    ACE_DEFINE_COMPONENT_EVENT(OnReachStart, void());
    ACE_DEFINE_COMPONENT_EVENT(OnReachEnd, void());

private:
    Dimension columnsGap_ = 0.0_px;
    Dimension rowsGap_ = 0.0_px;
    FlexDirection direction_ = FlexDirection::COLUMN;
    std::string columnsArgs_;
    std::string rowsArgs_;
    Dimension minWidth_ = 0.0_px;
    Dimension minHeight_ = 0.0_px;
    Dimension maxWidth_ = 0.0_px;
    Dimension maxHeight_ = 0.0_px;

    // scroll bar attribute
    DisplayMode displayMode_ = DisplayMode::ON;
    RefPtr<V2::WaterFlowPositionController> controller_;
    RefPtr<ScrollBarProxy> scrollBarProxy_;
    EventMarker scrolledEvent_;
    RefPtr<Component> footerComponent_;
    ACE_DISALLOW_COPY_AND_MOVE(WaterFlowComponent);
};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_WATER_FLOW_COMPONENT_H
