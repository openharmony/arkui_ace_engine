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

#include "core/components_v2/water_flow/water_flow_component.h"

#include "core/components_v2/water_flow/render_water_flow.h"
#include "core/components_v2/water_flow/water_flow_element.h"

namespace OHOS::Ace::V2 {
RefPtr<Element> WaterFlowComponent::CreateElement()
{
    return AceType::MakeRefPtr<WaterFlowElement>();
}

RefPtr<RenderNode> WaterFlowComponent::CreateRenderNode()
{
    return RenderWaterFlow::Create();
}

void WaterFlowComponent::SetColumnsGap(const Dimension& columnsGap)
{
    if (LessNotEqual(columnsGap.Value(), 0.0)) {
        LOGW("Invalid RowGap, use 0.0px");
        columnsGap_ = 0.0_px;
        return;
    }
    columnsGap_ = columnsGap;
}

void WaterFlowComponent::SetRowsGap(const Dimension& rowsGap)
{
    if (LessNotEqual(rowsGap.Value(), 0.0)) {
        LOGW("Invalid RowGap, use 0.0px");
        rowsGap_ = 0.0_px;
        return;
    }
    rowsGap_ = rowsGap;
}

void WaterFlowComponent::SetLayoutDirection(FlexDirection direction)
{
    if (direction < FlexDirection::ROW || direction > FlexDirection::COLUMN_REVERSE) {
        LOGW("Invalid direction %{public}d", direction);
        return;
    }
    direction_ = direction;
}

void WaterFlowComponent::SetController(const RefPtr<V2::WaterFlowPositionController>& controller)
{
    controller_ = controller;
}

void WaterFlowComponent::SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy)
{
    scrollBarProxy_ = scrollBarProxy;
}

void WaterFlowComponent::SetScrolledEvent(const EventMarker& event)
{
    scrolledEvent_ = event;
}

void WaterFlowComponent::SetScrollBarDisplayMode(DisplayMode displayMode)
{
    displayMode_ = displayMode;
}

void WaterFlowComponent::SetColumnsArgs(const std::string& columnsArgs)
{
    columnsArgs_ = columnsArgs;
}

void WaterFlowComponent::SetRowsArgs(const std::string& rowsArgs)
{
    rowsArgs_ = rowsArgs;
}

void WaterFlowComponent::SetMinWidth(const Dimension& minWidth)
{
    if (LessNotEqual(minWidth.Value(), 0.0)) {
        LOGW("Invalid minWidth, use 0.0px");
        minWidth_ = 0.0_px;
        return;
    }
    minWidth_ = minWidth;
}

void WaterFlowComponent::SetMinHeight(const Dimension& minHeight)
{
    if (LessNotEqual(minHeight.Value(), 0.0)) {
        LOGW("Invalid minHeight, use 0.0px");
        minHeight_ = 0.0_px;
        return;
    }
    minHeight_ = minHeight;
}

void WaterFlowComponent::SetMaxWidth(const Dimension& maxWidth)
{
    if (LessNotEqual(maxWidth.Value(), 0.0)) {
        LOGW("Invalid maxWidth, use 0.0px");
        maxWidth_ = 0.0_px;
        return;
    }
    maxWidth_ = maxWidth;
}

void WaterFlowComponent::SetMaxHeight(const Dimension& maxHeight)
{
    if (LessNotEqual(maxHeight.Value(), 0.0)) {
        LOGW("Invalid maxHeight, use 0.0px");
        maxHeight_ = 0.0_px;
        return;
    }
    maxHeight_ = maxHeight;
}

void WaterFlowComponent::SetFooterComponent(RefPtr<Component> component)
{
    footerComponent_ = std::move(component);
}
} // namespace OHOS::Ace::V2
