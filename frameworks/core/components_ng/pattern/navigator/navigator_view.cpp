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

#include "core/components_ng/pattern/navigator/navigator_view.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void NavigatorView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::NAVIGATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavigatorPattern>(); });
    stack->Push(frameNode);
}

void NavigatorView::SetType(NavigatorType value)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    auto eventHub = frameNode->GetEventHub<NavigatorEventHub>();
    eventHub->SetType(value);
}

void NavigatorView::SetActive(bool active)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    auto eventHub = frameNode->GetEventHub<NavigatorEventHub>();
    eventHub->SetActive(active);
}

void NavigatorView::SetUri(const std::string& uri)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    auto eventHub = frameNode->GetEventHub<NavigatorEventHub>();
    eventHub->SetUrl(uri);
}

void NavigatorView::SetParams(const std::string& params)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    auto eventHub = frameNode->GetEventHub<NavigatorEventHub>();
    eventHub->SetParams(params);
}

void NavigatorView::SetIsDefHeight(bool isDefHeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigatorLayoutProperty, IsDefHeight, isDefHeight);
}

void NavigatorView::SetIsDefWidth(bool isDefWidth)
{
    ACE_UPDATE_LAYOUT_PROPERTY(NavigatorLayoutProperty, IsDefWidth, isDefWidth);
}

} // namespace OHOS::Ace::NG
