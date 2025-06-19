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
#include "core/components_ng/pattern/folder_stack/folder_stack_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/folder_stack/control_parts_stack_node.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_pattern.h"
#include "core/components_ng/pattern/folder_stack/hover_stack_node.h"
#include "folder_stack_model_ng.h"

namespace OHOS::Ace::NG {
void FolderStackModelNG::Create()
{
    std::vector<std::string> itemId;
    Create(itemId);
}
void FolderStackModelNG::Create(const std::vector<std::string>& itemId)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto folderStackGroupNode = FolderStackGroupNode::GetOrCreateGroupNode(
        V2::FOLDER_STACK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<FolderStackPattern>(); });
    folderStackGroupNode->SetItemId(itemId);
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
    stack->Push(folderStackGroupNode);
    ACE_UPDATE_LAYOUT_PROPERTY(FolderStackLayoutProperty, UpperItems, itemId);
}

RefPtr<FrameNode> FolderStackModelNG::CreateFrameNode(int32_t nodeId)
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

void FolderStackModelNG::SetUpdateUpperItems(FrameNode* frameNode, const std::vector<std::string>& itemId)
{
    auto folderStackGroupNode = AceType::DynamicCast<FolderStackGroupNode>(frameNode);
    folderStackGroupNode->SetItemId(itemId);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FolderStackLayoutProperty, UpperItems, itemId, frameNode);
}

void FolderStackModelNG::SetAlignment(FrameNode* frameNode, const std::optional<Alignment>& valueOpt)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, Alignment, valueOpt.value_or(Alignment::CENTER), frameNode);
}

void FolderStackModelNG::SetAlignment(Alignment alignment)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, alignment);
}

void FolderStackModelNG::SetEnableAnimation(FrameNode* frameNode, bool isEnableAnimation)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FolderStackLayoutProperty, EnableAnimation, isEnableAnimation, frameNode);
}

void FolderStackModelNG::SetEnableAnimation(bool IsEnableAnimation)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FolderStackLayoutProperty, EnableAnimation, IsEnableAnimation);
}

void FolderStackModelNG::SetAutoHalfFold(FrameNode* frameNode, bool isAutoHalfFold)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FolderStackLayoutProperty, AutoHalfFold, isAutoHalfFold, frameNode);
}

void FolderStackModelNG::SetAutoHalfFold(bool IsAutoHalfFold)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FolderStackLayoutProperty, AutoHalfFold, IsAutoHalfFold);
}

void FolderStackModelNG::SetOnFolderStateChange(
    FrameNode* frameNode, std::function<void(const NG::FolderEventInfo& folderEventInfo)>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<FolderStackEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFolderStateChange(std::move(onChange));
}

void FolderStackModelNG::SetOnFolderStateChange(
    std::function<void(const NG::FolderEventInfo& folderEventInfo)>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<FolderStackEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFolderStateChange(std::move(onChange));
}

void FolderStackModelNG::SetOnHoverStatusChange(
    FrameNode* frameNode, std::function<void(const NG::FolderEventInfo& folderEventInfo)>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<FolderStackEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnHoverStatusChange(std::move(onChange));
}

void FolderStackModelNG::SetOnHoverStatusChange(
    std::function<void(const NG::FolderEventInfo& folderEventInfo)>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<FolderStackEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnHoverStatusChange(std::move(onChange));
}
} // namespace OHOS::Ace::NG
