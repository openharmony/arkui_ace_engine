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
#include "core/components_ng/pattern/folder_stack/folder_stack_group_node.h"

#include "core/components_ng/pattern/folder_stack/control_parts_stack_node.h"
#include "core/components_ng/pattern/folder_stack/hover_stack_node.h"

namespace OHOS::Ace::NG {
RefPtr<FolderStackGroupNode> FolderStackGroupNode::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<FolderStackGroupNode>(frameNode));
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto folderStackGroupNode = AceType::MakeRefPtr<FolderStackGroupNode>(tag, nodeId, pattern);
    folderStackGroupNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(folderStackGroupNode);
    return folderStackGroupNode;
}
void FolderStackGroupNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    childNode_.push_back(child);
    std::vector<std::string> itemId = GetItemId();
    auto hoverStackNode = AceType::DynamicCast<HoverStackNode>(GetHoverNode());
    CHECK_NULL_VOID(hoverStackNode);
    auto controlPartsStackNode = AceType::DynamicCast<ControlPartsStackNode>(GetControlPartsStackNode());
    CHECK_NULL_VOID(controlPartsStackNode);
    if (itemId.empty()) {
        controlPartsStackNode->AddChild(child);
        return;
    }
    if (std::count(itemId.begin(), itemId.end(), child->GetInspectorId())) {
        hoverStackNode->AddChild(child);
    } else {
        controlPartsStackNode->AddChild(child);
    };
}
} // namespace OHOS::Ace::NG