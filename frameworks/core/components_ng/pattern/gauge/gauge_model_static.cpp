/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/gauge/gauge_model_static.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"

namespace OHOS::Ace::NG {
void GaugeModelStatic::SetValue(FrameNode* frameNode, const std::optional<float>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(GaugePaintProperty, Value, *value, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(GaugePaintProperty, Value, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void GaugeModelStatic::SetMin(FrameNode* frameNode, const std::optional<float>& min)
{
    if (min) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(GaugePaintProperty, Min, *min, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(GaugePaintProperty, Min, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void GaugeModelStatic::SetMax(FrameNode* frameNode, const std::optional<float>& max)
{
    if (max) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(GaugePaintProperty, Max, *max, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(GaugePaintProperty, Max, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void GaugeModelStatic::SetGaugeStrokeWidth(FrameNode* frameNode, const std::optional<Dimension>& strokeWidth)
{
    if (strokeWidth) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(GaugePaintProperty, StrokeWidth, *strokeWidth, frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GaugeLayoutProperty, StrokeWidth, *strokeWidth, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(GaugePaintProperty, StrokeWidth, PROPERTY_UPDATE_RENDER, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(GaugeLayoutProperty, StrokeWidth, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void GaugeModelStatic::SetIndicatorSpace(FrameNode* frameNode, const std::optional<Dimension>& space)
{
    if (space) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(GaugePaintProperty, IndicatorSpace, *space, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(GaugePaintProperty, IndicatorSpace, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void GaugeModelStatic::SetPrivacySensitive(FrameNode* frameNode, const std::optional<bool>& flag)
{
    // if (flag) {
    //     ACE_UPDATE_NODE_PAINT_PROPERTY(GaugePaintProperty, IsSensitive, *flag, frameNode);
    // } else {
    //     ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(GaugePaintProperty, IsSensitive, PROPERTY_UPDATE_RENDER, frameNode);
    // }
    // ViewAbstract::SetPrivacySensitive(frameNode, flag);
}
} // namespace OHOS::Ace::NG
