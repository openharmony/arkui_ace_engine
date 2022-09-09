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

#include "core/components_ng/pattern/progress/progress_view.h"

#include "base/geometry/dimension.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void ProgressView::Create(double min, double value, double cachedValue, double max, ProgressType type)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::PROGRESS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ProgressPattern>(); });
    stack->Push(frameNode);

    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Value, value);
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, MaxValue, max);
    ACE_UPDATE_LAYOUT_PROPERTY(ProgressLayoutProperty, Type, type);
}

void ProgressView::SetValue(double value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Value, value);
}

void ProgressView::SetMaxValue(double value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, MaxValue, value);
}

void ProgressView::SetColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Color, value);
}

void ProgressView::SetStrokeWidth(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ProgressLayoutProperty, StrokeWidth, value);
}

void ProgressView::SetScaleCount(int32_t value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, ScaleCount, value);
}

void ProgressView::SetScaleWidth(const Dimension& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, ScaleWidth, value);
}
} // namespace OHOS::Ace::NG
