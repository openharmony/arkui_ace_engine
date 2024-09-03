/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

namespace OHOS::Ace::NG {

namespace {
constexpr double DEFAULT_INDICATOR_OFFSET = 16.0;
constexpr int32_t DEFAULT_FRICTION_RATIO = 62;
constexpr double DEFAULT_REFRESH_OFFSET = 64.0f;
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
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        auto pattern = frameNode->GetPattern<RefreshPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateNestedModeForChildren(NestedScrollOptions({
            .forward = NestedScrollMode::PARENT_FIRST,
            .backward = NestedScrollMode::SELF_FIRST,
        }));
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        RefreshLayoutProperty, IndicatorOffset, Dimension(DEFAULT_INDICATOR_OFFSET, DimensionUnit::VP));
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, Friction, DEFAULT_FRICTION_RATIO);
}

RefPtr<FrameNode> RefreshModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::REFRESH_ETS_TAG, nodeId, AceType::MakeRefPtr<RefreshPattern>());
    CHECK_NULL_RETURN(frameNode, frameNode);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        auto pattern = frameNode->GetPattern<RefreshPattern>();
        CHECK_NULL_RETURN(pattern, frameNode);
        pattern->UpdateNestedModeForChildren(NestedScrollOptions({
            .forward = NestedScrollMode::PARENT_FIRST,
            .backward = NestedScrollMode::SELF_FIRST,
        }));
    }
    auto layoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    layoutProperty->UpdateIndicatorOffset(Dimension(DEFAULT_INDICATOR_OFFSET, DimensionUnit::VP));
    layoutProperty->UpdateFriction(DEFAULT_FRICTION_RATIO);
    return frameNode;
}

void RefreshModelNG::SetPullToRefresh(bool pullToRefresh)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, PullToRefresh, pullToRefresh);
}

void RefreshModelNG::SetRefreshOffset(const Dimension& offset)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, RefreshOffset, offset);
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

void RefreshModelNG::SetLoadingText(const std::string& loadingText)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, LoadingText, loadingText);
}

void RefreshModelNG::ResetLoadingText()
{
    ACE_RESET_LAYOUT_PROPERTY(RefreshLayoutProperty, LoadingText);
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

void RefreshModelNG::SetChangeEvent(RefreshChangeEvent&& changeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}

void RefreshModelNG::SetOnOffsetChange(OffsetChangeEvent&& dragOffset)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnOffsetChange(std::move(dragOffset));
}

void RefreshModelNG::ResetOnOffsetChange()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ResetOnOffsetChange();
}

void RefreshModelNG::SetPullDownRatio(const std::optional<float>& pullDownRatio)
{
    if (pullDownRatio.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, PullDownRatio, pullDownRatio.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY(RefreshLayoutProperty, PullDownRatio);
    }
}

void RefreshModelNG::SetPullDownRatio(FrameNode* frameNode, const std::optional<float>& pullDownRatio)
{
    if (pullDownRatio.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, PullDownRatio, pullDownRatio.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, PullDownRatio, frameNode);
    }
}

void RefreshModelNG::SetCustomBuilder(const RefPtr<NG::UINode>& customBuilder)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RefreshPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddCustomBuilderNode(customBuilder);
}

void RefreshModelNG::SetIsCustomBuilderExist(bool isCustomBuilderExist)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsCustomBuilderExist, isCustomBuilderExist);
}

void RefreshModelNG::SetCustomBuilder(FrameNode* frameNode, FrameNode* customBuilder)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RefreshPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddCustomBuilderNode(AceType::Claim<UINode>(customBuilder));
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

void RefreshModelNG::SetOnOffsetChange(FrameNode* frameNode, OffsetChangeEvent&& dragOffset)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnOffsetChange(std::move(dragOffset));
}

void RefreshModelNG::ResetOnOffsetChange(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ResetOnOffsetChange();
}

void RefreshModelNG::SetRefreshing(FrameNode* frameNode, bool isRefreshing)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsRefreshing, isRefreshing, frameNode);
}

bool RefreshModelNG::GetRefreshing(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(RefreshLayoutProperty, IsRefreshing, value, frameNode, value);
    return value;
}

void RefreshModelNG::SetRefreshOffset(FrameNode* frameNode, const Dimension& offset)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, RefreshOffset, offset, frameNode);
}

void RefreshModelNG::SetPullToRefresh(FrameNode* frameNode, bool pullToRefresh)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, PullToRefresh, pullToRefresh, frameNode);
}

float RefreshModelNG::GetPullDownRatio(FrameNode* frameNode)
{
    float value = 1.0;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(RefreshLayoutProperty, PullDownRatio, value, frameNode, value);
    return value;
}

Dimension RefreshModelNG::GetRefreshOffset(FrameNode* frameNode)
{
    Dimension value(DEFAULT_REFRESH_OFFSET, DimensionUnit::VP);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(RefreshLayoutProperty, RefreshOffset, value, frameNode, value);
    return value;
}

bool RefreshModelNG::GetPullToRefresh(FrameNode* frameNode)
{
    bool value = true;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(RefreshLayoutProperty, PullToRefresh, value, frameNode, value);
    return value;
}

void RefreshModelNG::SetChangeEvent(FrameNode* frameNode, RefreshChangeEvent&& changeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}
} // namespace OHOS::Ace::NG
