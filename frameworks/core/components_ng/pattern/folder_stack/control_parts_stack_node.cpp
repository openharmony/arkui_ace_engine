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

#include "core/components_ng/pattern/folder_stack/control_parts_stack_node.h"

namespace OHOS::Ace::NG {
RefPtr<ControlPartsStackNode> ControlPartsStackNode::GetOrCreateControlPartsStackNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<ControlPartsStackNode>(frameNode));
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto controlPartsStackNode = AceType::MakeRefPtr<ControlPartsStackNode>(tag, nodeId, pattern);
    controlPartsStackNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(controlPartsStackNode);
    return controlPartsStackNode;
}
} // namespace OHOS::Ace::NG