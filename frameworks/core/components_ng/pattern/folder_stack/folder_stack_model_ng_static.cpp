/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/folder_stack/folder_stack_model_ng_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/folder_stack/control_parts_stack_node.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_pattern.h"
#include "core/components_ng/pattern/folder_stack/hover_stack_node.h"
#include "folder_stack_model_ng.h"


namespace OHOS::Ace::NG {

RefPtr<FrameNode> FolderStackModelNGStatic::CreateFrameNode(int32_t nodeId)
{
    auto folderStackGroupNode = FolderStackGroupNode::GetOrCreateGroupNode(
        V2::FOLDER_STACK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<FolderStackPattern>(); });
    if (!folderStackGroupNode->GetHoverNode()) {
        int32_t hoverId = ElementRegister::GetInstance()->MakeUniqueId();
        auto hoverStackNode = HoverStackNode::GetOrCreateHoverStackNode(
            V2::HOVER_STACK_ETS_TAG, hoverId, []() { return AceType::MakeRefPtr<HoverStackPattern>(); });
        folderStackGroupNode->AddChild(hoverStackNode);
        folderStackGroupNode->SetHoverNode(hoverStackNode);
    }
    if (!folderStackGroupNode->GetControlPartsStackNode()) {
        int32_t controlPartsId = ElementRegister::GetInstance()->MakeUniqueId();
        auto controlPartsNode = ControlPartsStackNode::GetOrCreateControlPartsStackNode(V2::CONTROL_PARTS_STACK_ETS_TAG,
            controlPartsId, []() { return AceType::MakeRefPtr<ControlPartsStackPattern>(); });
        folderStackGroupNode->AddChild(controlPartsNode);
        folderStackGroupNode->SetControlPartsStackNode(controlPartsNode);
    }
    std::vector<std::string> itemId;
    SetUpdateUpperItems(folderStackGroupNode.GetRawPtr(), itemId);
    return folderStackGroupNode;
}

void FolderStackModelNGStatic::SetUpdateUpperItems(FrameNode* frameNode, const std::vector<std::string>& itemId)
{
    auto folderStackGroupNode = AceType::DynamicCast<FolderStackGroupNode>(frameNode);
    folderStackGroupNode->SetItemId(itemId);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FolderStackLayoutProperty, UpperItems, itemId, frameNode);
}

void FolderStackModelNGStatic::SetAlignment(FrameNode* frameNode, const std::optional<Alignment>& valueOpt)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, Alignment, valueOpt.value_or(Alignment::CENTER), frameNode);
}

}
