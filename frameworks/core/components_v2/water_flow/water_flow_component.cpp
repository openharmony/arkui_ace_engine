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
#include "core/pipeline/base/multi_composed_component.h"

namespace OHOS::Ace::V2 {
RefPtr<Element> WaterFlowComponent::CreateElement()
{
    return AceType::MakeRefPtr<WaterFlowElement>();
}

RefPtr<RenderNode> WaterFlowComponent::CreateRenderNode()
{
    return RenderWaterFlow::Create();
}

void WaterFlowComponent::SetMainLength(const Dimension& mainLength)
{
    if (mainLength.Value() < 0.0) {
        LOGW("Invalid MainLength use 0px");
        return;
    }
    mainLength_ = mainLength;
}

void WaterFlowComponent::SetColumnsGap(const Dimension& columnsGap)
{
    if (columnsGap.Value() < 0.0) {
        LOGW("Invalid RowGap, use 0px");
        columnsGap_ = 0.0_px;
        return;
    }
    columnsGap_ = columnsGap;
}

void WaterFlowComponent::SetRowsGap(const Dimension& rowsGap)
{
    if (rowsGap.Value() < 0.0) {
        LOGW("Invalid RowGap, use 0px");
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

void WaterFlowComponent::SetFlexAlign(FlexAlign flexAlign)
{
    if (flexAlign < FlexAlign::FLEX_START || flexAlign > FlexAlign::STRETCH) {
        LOGW("Invalid flexAlign %{public}d", flexAlign);
        return;
    }
    flexAlign_ = flexAlign;
}

void WaterFlowComponent::SetController(const RefPtr<V2::WaterFlowPositionController>& controller)
{
    controller_ = controller;
}

void WaterFlowComponent::SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy)
{
    scrollBarProxy_ = scrollBarProxy;
}

void WaterFlowComponent::SetRightToLeft(bool rightToLeft)
{
    rightToLeft_ = rightToLeft;
}

void WaterFlowComponent::SetScrolledEvent(const EventMarker& event)
{
    scrolledEvent_ = event;
}

void WaterFlowComponent::SetScrollBarDisplayMode(DisplayMode displayMode)
{
    displayMode_ = displayMode;
}

void WaterFlowComponent::SetScrollBarColor(const std::string& color)
{
    scrollBarColor_ = color;
}

void WaterFlowComponent::SetScrollBarWidth(const std::string& width)
{
    scrollBarWidth_ = width;
}
} // namespace OHOS::Ace::V2
