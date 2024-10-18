/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/linear_indicator/linear_indicator_model_ng.h"

#include "core/components_ng/pattern/linear_indicator/linear_indicator_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<NG::LinearIndicatorController> LinearIndicatorModelNG::Create(std::size_t progressCount)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::LINEARINDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearIndicatorPattern>(); });
    auto pattern = frameNode->GetPattern<LinearIndicatorPattern>();
    SetProgressCount(frameNode, progressCount);
    stack->Push(frameNode);
    return pattern->GetController();
}

void LinearIndicatorModelNG::SetProgressCount(
    OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> frameNode, std::size_t progressCount)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, ProgressCount, progressCount, frameNode);
}

void LinearIndicatorModelNG::SetSpace(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, Space, value, frameNode);
}

void LinearIndicatorModelNG::SetStrokeWidth(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, StrokeWidth, value, frameNode);
}

void LinearIndicatorModelNG::SetStrokeRadius(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, StrokeRadius, value, frameNode);
}

void LinearIndicatorModelNG::SetTrackBackgroundColor(const Color& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, TrackBackgroundColor, value, frameNode);
}

void LinearIndicatorModelNG::SetTrackColor(const Color& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, TrackColor, value, frameNode);
}

void LinearIndicatorModelNG::Loop(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, Loop, value, frameNode);
}

void LinearIndicatorModelNG::OnChange(std::function<void(int index, float progress)>&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LinearIndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->GetController()->OnChange(std::move(event));
}

void LinearIndicatorModelNG::SetIndicatorStyleSpace(FrameNode* frameNode, const Dimension& space)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, Space, space, frameNode);
}

void LinearIndicatorModelNG::SetIndicatorStyleStrokeWidth(FrameNode* frameNode, const Dimension& strokeWidth)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, StrokeWidth, strokeWidth, frameNode);
}

void LinearIndicatorModelNG::SetIndicatorStyleStrokeRadius(FrameNode* frameNode, const Dimension& strokeRadius)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, StrokeRadius, strokeRadius, frameNode);
}

void LinearIndicatorModelNG::SetIndicatorStyleTrackBackgroundColor(
    FrameNode* frameNode, const Color& trackBackgroundColor)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        LinearIndicatorLayoutProperty, TrackBackgroundColor, trackBackgroundColor, frameNode);
}

void LinearIndicatorModelNG::SetIndicatorStyleTrackColor(FrameNode* frameNode, const Color& trackColor)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, TrackColor, trackColor, frameNode);
}

void LinearIndicatorModelNG::SetLoop(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearIndicatorLayoutProperty, Loop, value, frameNode);
}

void LinearIndicatorModelNG::SetOnChange(FrameNode* frameNode, std::function<void(int index, float progress)>&& event)
{
    auto pattern = frameNode->GetPattern<LinearIndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->GetController()->OnChange(std::move(event));
}
} // namespace OHOS::Ace::NG
