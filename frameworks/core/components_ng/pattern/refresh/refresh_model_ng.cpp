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

#include "core/components_ng/pattern/refresh/refresh_model_ng.h"

#include <string>

#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/geometry/ng/offset_t.h"
#include "frameworks/base/i18n/localization.h"
#include "frameworks/base/utils/time_util.h"
#include "frameworks/core/components/refresh/refresh_theme.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/event/event_hub.h"
#include "frameworks/core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_pattern.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"
#include "frameworks/core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

namespace {
constexpr double DEFAULT_INDICATOR_OFFSET = 16.0;
constexpr int32_t DEFAULT_FRICTION_RATIO = 62;
} // namespace

void RefreshModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::REFRESH_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::REFRESH_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RefreshPattern>(); });
    CHECK_NULL_VOID(frameNode);
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(
        RefreshLayoutProperty, IndicatorOffset, Dimension(DEFAULT_INDICATOR_OFFSET, DimensionUnit::VP));
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, Friction, DEFAULT_FRICTION_RATIO);
}

void RefreshModelNG::SetRefreshing(bool isRefreshing)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsRefreshing, isRefreshing);
}

void RefreshModelNG::SetIndicatorOffset(const Dimension& indicatorOffset)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IndicatorOffset, indicatorOffset);
}

void RefreshModelNG::SetFriction(int32_t friction)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, Friction, friction);
}

void RefreshModelNG::SetProgressColor(const Color& progressColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, ProgressColor, progressColor);
}

void RefreshModelNG::SetOnStateChange(StateChangeEvent&& stateChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStateChange(std::move(stateChange));
}

void RefreshModelNG::SetOnRefreshing(RefreshingEvent&& refreshing)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRefreshing(std::move(refreshing));
}

void RefreshModelNG::SetChangeEvent(ChangeEvent&& changeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}

void RefreshModelNG::SetCustomBuilder(const RefPtr<NG::UINode>& customBuilder)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RefreshPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddCustomBuilderNode(customBuilder);
}

void RefreshModelNG::SetOnStateChange(FrameNode* frameNode, StateChangeEvent&& stateChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStateChange(std::move(stateChange));
}

void RefreshModelNG::SetOnRefreshing(FrameNode* frameNode, RefreshingEvent&& refreshing)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRefreshing(std::move(refreshing));
}

} // namespace OHOS::Ace::NG
