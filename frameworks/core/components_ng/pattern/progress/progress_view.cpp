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

    ACE_UPDATE_LAYOUT_PROPERTY(ProgressLayoutProperty, Value, value);
    ACE_UPDATE_LAYOUT_PROPERTY(ProgressLayoutProperty, MaxValue, max);
}

void ProgressView::SetValue(const double& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ProgressLayoutProperty, Value, value);
}

void ProgressView::SetMaxValue(const double& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ProgressLayoutProperty, MaxValue, value);
}

void ProgressView::SetColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ProgressLayoutProperty, Color, value);
}

} // namespace OHOS::Ace::NG
