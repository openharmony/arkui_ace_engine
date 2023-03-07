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

#include "core/components_ng/pattern/counter/counter_node.h"

namespace OHOS::Ace::NG {

RefPtr<CounterNode> CounterNode::GetOrCreateCounterNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto counterNode = ElementRegister::GetInstance()->GetSpecificItemById<CounterNode>(nodeId);
    if (counterNode) {
        if (counterNode->GetTag() == tag) {
            return counterNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = counterNode->GetParent();
        if (parent) {
            parent->RemoveChild(counterNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    counterNode = AceType::MakeRefPtr<CounterNode>(tag, nodeId, pattern, false);
    counterNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(counterNode);
    return counterNode;
}

void CounterNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    int32_t contentId = GetPattern<CounterPattern>()->GetContentId();
    auto contentNode = GetChildAtIndex(GetChildIndexById(contentId));
    CHECK_NULL_VOID(contentNode);
    child->MountToParent(contentNode);
}

void CounterNode::DeleteChildFromGroup(int32_t slot)
{
    auto pattern = GetPattern<CounterPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->HasContentNode()) {
        return;
    }
    int32_t contentId = pattern->GetContentId();
    const auto contentNode = GetChildAtIndex(GetChildIndexById(contentId));
    CHECK_NULL_VOID(contentNode);
    contentNode->RemoveChild(contentNode->GetFirstChild());
}

} // namespace OHOS::Ace::NG