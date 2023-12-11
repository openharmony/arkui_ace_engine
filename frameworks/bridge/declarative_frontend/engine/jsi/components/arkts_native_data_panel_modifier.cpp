/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_data_panel_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_CLOSE_EFFECT = false;
constexpr double DEFAULT_STROKE_WIDTH = 24.0;
const std::string DEFAULT_TRACK_BACKGROUND = "#08182431";
}
void SetCloseEffect(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetCloseEffect(frameNode, value);
}

void ResetCloseEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetCloseEffect(frameNode, IS_CLOSE_EFFECT);
}

void SetDataPanelTrackBackgroundColor(NodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetTrackBackground(frameNode, Color(value));
}

void ResetDataPanelTrackBackgroundColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetTrackBackground(frameNode, Color::FromString(DEFAULT_TRACK_BACKGROUND));
}

void SetDataPanelStrokeWidth(NodeHandle node, double value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    DataPanelModelNG::SetStrokeWidth(frameNode, Dimension(value, unitEnum));
}

void ResetDataPanelStrokeWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetStrokeWidth(frameNode, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
}

ArkUIDataPanelModifierAPI GetDataPanelModifier()
{
    static const ArkUIDataPanelModifierAPI modifier = { SetCloseEffect, ResetCloseEffect,
        SetDataPanelTrackBackgroundColor, ResetDataPanelTrackBackgroundColor, SetDataPanelStrokeWidth,
        ResetDataPanelStrokeWidth };

    return modifier;
}
} // namespace OHOS::Ace::NG