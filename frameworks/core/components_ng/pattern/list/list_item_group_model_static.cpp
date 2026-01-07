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

#include "base/utils/multi_thread.h"
#include "core/components/list/list_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {

void ListItemGroupModelStatic::SetDivider(
    FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider, bool needGetThemeColor)
{
    CHECK_NULL_VOID(frameNode);
    if (divider.has_value()) {
        FREE_NODE_CHECK(frameNode, SetDivider, frameNode, divider, needGetThemeColor);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(ListItemGroupLayoutProperty, Divider,
            PROPERTY_UPDATE_MEASURE, frameNode);
        auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        paintProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
    }
}

void ListItemGroupModelStatic::SetDividerMultiThread(
    FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider, bool needGetThemeColor)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([
        weak = AceType::WeakClaim(frameNode), divider, needGetThemeColor]() {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        V2::ItemDivider dividerValue = divider.value();
        if (needGetThemeColor) {
            auto context = node->GetContext();
            CHECK_NULL_VOID(context);
            auto listTheme = context->GetTheme<ListTheme>();
            auto themeColor = listTheme ? listTheme->GetDividerColor() : Color::TRANSPARENT;
            dividerValue.color = themeColor;
        }
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, dividerValue, node);
    });
}

RefPtr<FrameNode> ListItemGroupModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, nodeId,
        AceType::MakeRefPtr<ListItemGroupPattern>(nullptr, V2::ListItemGroupStyle::NONE));
    return frameNode;
}

void ListItemGroupModelStatic::SetHeader(FrameNode* frameNode, const RefPtr<NG::UINode>& node, bool isContent)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    if (node) {
        pattern->AddHeader(node);
        if (isContent) {
            pattern->SetHeaderComponentContentExist(true);
        }
    } else {
        pattern->SetHeaderComponentContentExist(true);
        pattern->RemoveHeader();
    }
}

void ListItemGroupModelStatic::SetFooter(FrameNode* frameNode, const RefPtr<NG::UINode>& node, bool isContent)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    if (node) {
        pattern->AddFooter(node);
        if (isContent) {
            pattern->SetFooterComponentContentExist(true);
        }
    } else {
        pattern->SetFooterComponentContentExist(true);
        pattern->RemoveFooter();
    }
}

RefPtr<ListChildrenMainSize> ListItemGroupModelStatic::GetOrCreateListChildrenMainSize(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetOrCreateListChildrenMainSize();
}

void ListItemGroupModelStatic::ResetListChildrenMainSize(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetChildrenSize();
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