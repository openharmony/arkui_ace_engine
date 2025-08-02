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

#include "core/components_ng/pattern/list/list_item_group_model_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {

void ListItemGroupModelStatic::SetDivider(FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider)
{
    if (divider.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, frameNode);
    }
}

RefPtr<FrameNode> ListItemGroupModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, nodeId,
        AceType::MakeRefPtr<ListItemGroupPattern>(nullptr, V2::ListItemGroupStyle::NONE));
    return frameNode;
}

void ListItemGroupModelStatic::SetHeader(FrameNode* frameNode, std::function<RefPtr<UINode>()>&& builder)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    RefPtr<UINode> unitNode = builder();
    pattern->AddHeader(unitNode);
}

void ListItemGroupModelStatic::SetFooter(FrameNode* frameNode, std::function<RefPtr<UINode>()>&& builder)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    RefPtr<UINode> unitNode = builder();
    pattern->AddFooter(unitNode);
}

RefPtr<ListChildrenMainSize> ListItemGroupModelStatic::GetOrCreateListChildrenMainSize(
    FrameNode* frameNode, const std::optional<float>& defaultSize)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto childrenMainSize = pattern->GetOrCreateListChildrenMainSize();
    if (defaultSize.has_value()) {
        childrenMainSize->UpdateDefaultSize(defaultSize.value());
    }
    return childrenMainSize;
}

RefPtr<ListChildrenMainSize> ListItemGroupModelStatic::GetOrCreateListChildrenMainSize(
    FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetOrCreateListChildrenMainSize();
}

void ListItemGroupModelStatic::SetSpace(FrameNode* frameNode, const std::optional<Dimension>& space)
{
    if (space.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Space, space.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Space, frameNode);
    }
}

void ListItemGroupModelStatic::SetStyle(FrameNode* frameNode, const std::optional<V2::ListItemGroupStyle>& style)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetListItemGroupStyle(style.value_or(V2::ListItemGroupStyle::NONE));
}
} // namespace OHOS::Ace::NG