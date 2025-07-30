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

#include "core/components_ng/pattern/data_panel/data_panel_model_static.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"

namespace OHOS::Ace::NG {
namespace {
void SetDefaultBorderRadius(void)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DataPanelTheme>();
    CHECK_NULL_VOID(theme);
    auto defaultRadiusDimension = theme->GetDefaultBorderRadius();
    ViewAbstract::SetBorderRadius(defaultRadiusDimension);
    ViewAbstract::SetClipEdge(true);
}
} // namespace

void DataPanelModelStatic::SetTrackBackground(FrameNode* frameNode, const std::optional<Color>& trackBackgroundColor)
{
    if (trackBackgroundColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            DataPanelPaintProperty, TrackBackground, trackBackgroundColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(DataPanelPaintProperty, TrackBackground, frameNode);
    }
}

void DataPanelModelStatic::SetStrokeWidth(FrameNode* frameNode, const std::optional<Dimension>& strokeWidth)
{
    if (strokeWidth.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(DataPanelPaintProperty, StrokeWidth, strokeWidth.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(DataPanelPaintProperty, StrokeWidth, frameNode);
    }
}

void DataPanelModelStatic::SetValueColors(FrameNode* frameNode, const std::optional<std::vector<Gradient>>& valueColors)
{
    if (valueColors.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(DataPanelPaintProperty, ValueColors, valueColors.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(DataPanelPaintProperty, ValueColors, frameNode);
    }
}

void DataPanelModelStatic::SetValues(FrameNode* frameNode, const std::optional<std::vector<double>>& values)
{
    if (values.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(DataPanelPaintProperty, Values, values.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(DataPanelPaintProperty, Values, frameNode);
    }
}

void DataPanelModelStatic::SetMax(FrameNode* frameNode, const std::optional<double>& max)
{
    if (max.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(DataPanelPaintProperty, Max, max.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(DataPanelPaintProperty, Max, frameNode);
    }
}

void DataPanelModelStatic::SetType(FrameNode* frameNode, const std::optional<int32_t>& type)
{
    if (type.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(DataPanelPaintProperty, DataPanelType, type.value(), frameNode);
        if (type.value() != static_cast<int32_t>(DataPanelType::CIRCLE)) {
            SetDefaultBorderRadius();
        }
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(DataPanelPaintProperty, DataPanelType, frameNode);
    }
}
} // namespace OHOS::Ace::NG
