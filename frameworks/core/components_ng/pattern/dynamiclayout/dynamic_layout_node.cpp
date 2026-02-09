/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_node.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
std::pair<RefPtr<DynamicLayoutNode>, bool> DynamicLayoutNode::GetOrCreateDynamicLayoutNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto dynamicLayoutNode = ElementRegister::GetInstance()->GetSpecificItemById<DynamicLayoutNode>(nodeId);
    if (dynamicLayoutNode) {
        if (dynamicLayoutNode->GetTag() == tag) {
            return {dynamicLayoutNode, false};
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = dynamicLayoutNode->GetParent();
        if (parent) {
            parent->RemoveChild(dynamicLayoutNode);
        }
    }
    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    dynamicLayoutNode = AceType::MakeRefPtr<DynamicLayoutNode>(tag, nodeId, pattern, false);
    dynamicLayoutNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(dynamicLayoutNode);
    return {dynamicLayoutNode, true};
}
} // namespace OHOS::Ace::NG