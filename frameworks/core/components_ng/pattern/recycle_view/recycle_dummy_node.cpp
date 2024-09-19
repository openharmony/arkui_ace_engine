/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/recycle_view/recycle_dummy_node.h"

#include "core/components_ng/pattern/custom/custom_node_base.h"

namespace OHOS::Ace::NG {
RefPtr<RecycleDummyNode> RecycleDummyNode::CreateRecycleDummyNode(int32_t nodeId)
{
    auto node = MakeRefPtr<RecycleDummyNode>(nodeId);
    return node;
}

RefPtr<AceType> RecycleDummyNode::WrapRecycleDummyNode(const RefPtr<AceType>& customNode, int32_t nodeId)
{
    auto node = CreateRecycleDummyNode(nodeId);
    auto uiNode = AceType::DynamicCast<UINode>(customNode);
    node->AddChild(uiNode);
    return node;
}

RecycleDummyNode::RecycleDummyNode(int32_t nodeId) : UINode(V2::RECYCLE_VIEW_ETS_TAG, nodeId) {}

RecycleDummyNode::~RecycleDummyNode()
{
    auto childCount = TotalChildCount();
    if (childCount != 1) {
        return;
    }
    auto child = GetFirstChild();
    CHECK_NULL_VOID(child);
    if (child->TotalChildCount() == 0) {
        return;
    }
    child->DetachFromMainTree();
    auto customNode = AceType::DynamicCast<CustomNodeBase>(child);
    CHECK_NULL_VOID(customNode);
    customNode->FireRecycleSelf();
}
} // namespace OHOS::Ace::NG
