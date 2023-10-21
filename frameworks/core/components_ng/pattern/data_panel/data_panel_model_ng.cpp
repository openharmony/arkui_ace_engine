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

#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void DataPanelModelNG::Create(const std::vector<double>& values, double max, int32_t dataPanelType)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::DATA_PANEL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DataPanelPattern>(); });
    stack->Push(frameNode);

    ACE_UPDATE_PAINT_PROPERTY(DataPanelPaintProperty, Values, values);
    ACE_UPDATE_PAINT_PROPERTY(DataPanelPaintProperty, Max, max);
    ACE_UPDATE_PAINT_PROPERTY(DataPanelPaintProperty, DataPanelType, dataPanelType);
}

void DataPanelModelNG::SetEffect(bool isCloseEffect)
{
    ACE_UPDATE_PAINT_PROPERTY(DataPanelPaintProperty, Effect, !isCloseEffect);
}

void DataPanelModelNG::SetValueColors(const std::vector<Gradient>& valueColors)
{
    ACE_UPDATE_PAINT_PROPERTY(DataPanelPaintProperty, ValueColors, valueColors);
}

void DataPanelModelNG::SetTrackBackground(const Color& trackBackgroundColor)
{
    ACE_UPDATE_PAINT_PROPERTY(DataPanelPaintProperty, TrackBackground, trackBackgroundColor);
}

void DataPanelModelNG::SetStrokeWidth(const Dimension& strokeWidth)
{
    ACE_UPDATE_PAINT_PROPERTY(DataPanelPaintProperty, StrokeWidth, strokeWidth);
}

void DataPanelModelNG::SetShadowOption(const DataPanelShadow& shadowOption)
{
    ACE_UPDATE_PAINT_PROPERTY(DataPanelPaintProperty, ShadowOption, shadowOption);
}

} // namespace OHOS::Ace::NG
