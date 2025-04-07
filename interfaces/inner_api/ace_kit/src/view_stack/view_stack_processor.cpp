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

#include "ui/view_stack/view_stack_processor.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/utils/utils.h"

#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"

namespace OHOS::Ace::Kit {

int32_t ViewStackProcessor::ClaimNodeId()
{
    return NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
}

void ViewStackProcessor::Push(const RefPtr<FrameNode>& node)
{
    auto nodeImpl = AceType::DynamicCast<FrameNodeImpl>(node);
    CHECK_NULL_VOID(nodeImpl);
    NG::ViewStackProcessor::GetInstance()->Push(nodeImpl->MoveOwnershipAndGetAceNode());
}

RefPtr<FrameNode> ViewStackProcessor::GetTopNode()
{
    auto* mainNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(mainNode, nullptr);
    auto kitNode = mainNode->GetKitNode();
    if (!kitNode) {
        kitNode = Referenced::MakeRefPtr<FrameNodeImpl>(mainNode);
        mainNode->SetKitNode(kitNode);
    }
    return kitNode;
}

void ViewStackProcessor::NewScope()
{
    Ace::ViewStackModel::GetInstance()->NewScope();
}

RefPtr<FrameNode> ViewStackProcessor::Finish()
{
    auto node = Ace::ViewStackModel::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);

    if (frameNode) {
        auto kitNode = frameNode->GetKitNode();
        if (!kitNode) {
            kitNode = AceType::MakeRefPtr<FrameNodeImpl>(frameNode);
        }
        return kitNode;
    }

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto proxyNode = NG::FrameNode::GetOrCreateFrameNode(
        "BuilderProxyNode", nodeId, []() { return AceType::MakeRefPtr<NG::StackPattern>(); });
    proxyNode->AddChild(AceType::DynamicCast<NG::UINode>(node));

    return AceType::MakeRefPtr<FrameNodeImpl>(proxyNode);
}

} // namespace OHOS::Ace::Kit
