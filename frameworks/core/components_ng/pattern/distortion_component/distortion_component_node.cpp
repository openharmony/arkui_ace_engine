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

#include "core/components_ng/pattern/distortion_component/distortion_component_node.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

RefPtr<DistortionComponentNode> DistortionComponentNode::GetOrCreateDistortionComponentNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    ACE_UINODE_TRACE(nodeId);
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<DistortionComponentNode>(frameNode));
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto distortionComponentNode = AceType::MakeRefPtr<DistortionComponentNode>(tag, nodeId, pattern);
    distortionComponentNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(distortionComponentNode);
    return distortionComponentNode;
}

void DistortionComponentNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    auto pattern = GetPattern<DistortionComponentPattern>();
    CHECK_NULL_VOID(pattern);
    auto contentNode = pattern->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    contentNode->AddChild(child, slot);
}

} // namespace OHOS::Ace::NG
