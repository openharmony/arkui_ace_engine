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
#include "core/components_ng/pattern/refresh/refresh_model_static.h"

#include <string>

#include "frameworks/core/components_ng/pattern/refresh/refresh_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> RefreshModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::REFRESH_ETS_TAG, nodeId);
    return FrameNode::GetOrCreateFrameNode(
        V2::REFRESH_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RefreshPattern>(); });
}

void RefreshModelStatic::SetRefreshing(FrameNode* frameNode, const std::optional<bool>& isRefreshing)
{
    if (isRefreshing) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsRefreshing, isRefreshing.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsRefreshing, frameNode);
    }
}

void RefreshModelStatic::SetLoadingText(FrameNode* frameNode, const std::optional<std::string>& promptText)
{
    if (promptText) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, LoadingText, promptText.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, LoadingText, frameNode);
    }
}

void RefreshModelStatic::SetCustomBuilder(FrameNode* frameNode, const RefPtr<NG::UINode>& customBuilder)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RefreshPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddCustomBuilderNode(customBuilder);
}

void RefreshModelStatic::SetIsCustomBuilderExist(FrameNode* frameNode, bool isCustomBuilderExist)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsCustomBuilderExist, isCustomBuilderExist, frameNode);
}

void RefreshModelStatic::SetRefreshOffset(FrameNode* frameNode, const std::optional<Dimension>& offset)
{
    if (offset) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, RefreshOffset, offset.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, RefreshOffset, frameNode);
    }
}

void RefreshModelStatic::SetPullToRefresh(FrameNode* frameNode, const std::optional<bool>& pullToRefresh)
{
    if (pullToRefresh) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, PullToRefresh, pullToRefresh.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, PullToRefresh, frameNode);
    }
}

void RefreshModelStatic::SetPullDownRatio(FrameNode* frameNode, const std::optional<float>& pullDownRatio)
{
    if (pullDownRatio) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, PullDownRatio, pullDownRatio.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(RefreshLayoutProperty, PullDownRatio, frameNode);
    }
}

void RefreshModelStatic::SetOnOffsetChange(FrameNode* frameNode, OffsetChangeEvent&& dragOffset)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnOffsetChange(std::move(dragOffset));
}

void RefreshModelStatic::ResetOnOffsetChange(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->ResetOnOffsetChange();
}

void RefreshModelStatic::SetOnStateChange(FrameNode* frameNode, StateChangeEvent&& stateChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStateChange(std::move(stateChange));
}

void RefreshModelStatic::SetOnRefreshing(FrameNode* frameNode, RefreshingEvent&& refreshing)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRefreshing(std::move(refreshing));
}

void RefreshModelStatic::SetChangeEvent(FrameNode* frameNode, RefreshChangeEvent&& changeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}
} // namespace OHOS::Ace::NG
