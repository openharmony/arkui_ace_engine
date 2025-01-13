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

#include "core/components_ng/pattern/ui_extension/dynamic_node.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/ui_extension/dynamic_pattern.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
DynamicNode::DynamicNode(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot)
    : FrameNode(tag, nodeId, pattern, isRoot)
{
    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "Create DynamicNode");
}

DynamicNode::~DynamicNode()
{
    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "Destory DynamicNode");
}

RefPtr<DynamicNode> DynamicNode::GetOrCreateDynamicNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto dynamicNode = ElementRegister::GetInstance()->GetSpecificItemById<DynamicNode>(nodeId);
    if (dynamicNode) {
        if (dynamicNode->GetTag() == tag) {
            return dynamicNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = dynamicNode->GetParent();
        if (parent) {
            parent->RemoveChild(dynamicNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    dynamicNode = AceType::MakeRefPtr<DynamicNode>(tag, nodeId, pattern, false);
    dynamicNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(dynamicNode);
    return dynamicNode;
}

void DynamicNode::DumpTree(int32_t depth, bool hasJson)
{
    UINode::DumpTree(depth, hasJson);
    auto pattern = GetPattern<DynamicPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->DumpDynamicRenderer(depth + 1, hasJson);
}
} // namespace OHOS::Ace::NG
