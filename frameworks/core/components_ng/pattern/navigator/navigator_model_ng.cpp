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

#include "core/components_ng/pattern/navigator/navigator_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"

namespace OHOS::Ace::NG {

void NavigatorModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVIGATOR_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::NAVIGATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavigatorPattern>(); });
    stack->Push(frameNode);
}

void NavigatorModelNG::SetType(NavigatorType value)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetType(value);
}

void NavigatorModelNG::SetActive(bool active)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetActive(active);
}

void NavigatorModelNG::SetUri(const std::string& uri)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetUrl(uri);
}

void NavigatorModelNG::SetParams(const std::string& params)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetParams(params);
}

RefPtr<FrameNode> NavigatorModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::NAVIGATOR_ETS_TAG, nodeId,
        AceType::MakeRefPtr<NavigatorPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode;
}

void NavigatorModelNG::SetParams(FrameNode* frameNode, const std::string& params)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetParams(params);
}

void NavigatorModelNG::SetType(FrameNode* frameNode, NavigatorType value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetType(value);
}

void NavigatorModelNG::SetUri(FrameNode* frameNode, const std::string& uri)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetUrl(uri);
}

void NavigatorModelNG::SetActive(FrameNode* frameNode, bool active)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NavigatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetActive(active);
}
} // namespace OHOS::Ace::NG
