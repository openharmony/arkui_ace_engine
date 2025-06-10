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

#include "core/components_ng/pattern/list/list_item_group_model_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {

void ListItemGroupModelNG::Create(V2::ListItemGroupStyle listItemGroupStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::LIST_ITEM_GROUP_ETS_TAG, nodeId);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, nodeId, [itemGroupStyle = listItemGroupStyle]() {
            return AceType::MakeRefPtr<ListItemGroupPattern>(nullptr, itemGroupStyle);
        });
    stack->Push(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto layoutProperty = frameNode->GetLayoutProperty<ListItemGroupLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->ResetDividerColorSetByUser();
    }
}

RefPtr<FrameNode> ListItemGroupModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, nodeId,
        AceType::MakeRefPtr<ListItemGroupPattern>(nullptr, V2::ListItemGroupStyle::NONE));
    return frameNode;
}

void ListItemGroupModelNG::SetSpace(const Dimension& space)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Space, space);
}

void ListItemGroupModelNG::SetDivider(const V2::ItemDivider& divider)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider);
}

void ListItemGroupModelNG::SetHeader(std::function<void()>&& header)
{
    RefPtr<NG::UINode> headerNode;
    if (header) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        header();
        headerNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    CHECK_NULL_VOID(headerNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddHeader(headerNode);
    pattern->SetHeaderComponentContentExist(false);
}

void ListItemGroupModelNG::SetFooter(std::function<void()>&& footer)
{
    RefPtr<NG::UINode> footerNode;
    if (footer) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        footer();
        footerNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    CHECK_NULL_VOID(footerNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(footerNode);
    pattern->SetFooterComponentContentExist(false);
}

void ListItemGroupModelNG::SetDivider(FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider)
{
    if (divider.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, frameNode);
    }
}

void ListItemGroupModelNG::SetHeader(FrameNode* frameNode, FrameNode* headerNode)
{
    CHECK_NULL_VOID(headerNode);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddHeader(AceType::Claim<UINode>(headerNode));
    pattern->SetHeaderComponentContentExist(true);
}

void ListItemGroupModelNG::SetFooter(FrameNode* frameNode, FrameNode* footerNode)
{
    CHECK_NULL_VOID(footerNode);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(AceType::Claim<UINode>(footerNode));
    pattern->SetFooterComponentContentExist(true);
}

RefPtr<ListChildrenMainSize> ListItemGroupModelNG::GetOrCreateListChildrenMainSize()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetOrCreateListChildrenMainSize();
}

void ListItemGroupModelNG::SetListChildrenMainSize(
    FrameNode* frameNode, float defaultSize, const std::vector<float>& mainSize)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetListChildrenMainSize(defaultSize, mainSize);
}

void ListItemGroupModelNG::ResetListChildrenMainSize(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetChildrenSize();
}

V2::ItemDivider ListItemGroupModelNG::GetDivider(FrameNode* frameNode)
{
    V2::ItemDivider value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ListItemGroupLayoutProperty, Divider, value, frameNode, value);
    return value;
}

void ListItemGroupModelNG::SetSpace(FrameNode* frameNode, const Dimension& space)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Space, space, frameNode);
}

void ListItemGroupModelNG::SetStyle(FrameNode* frameNode, V2::ListItemGroupStyle style)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetListItemGroupStyle(style);
}

void ListItemGroupModelNG::SetFooterComponent(const RefPtr<NG::UINode>& footerComponent)
{
    CHECK_NULL_VOID(footerComponent);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(footerComponent);
    pattern->SetFooterComponentContentExist(true);
}

void ListItemGroupModelNG::SetHeaderComponent(const RefPtr<NG::UINode>& headerComponent)
{
    CHECK_NULL_VOID(headerComponent);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddHeader(headerComponent);
    pattern->SetHeaderComponentContentExist(true);
}

void ListItemGroupModelNG::RemoveFooter()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveFooter();
}

void ListItemGroupModelNG::RemoveHeader()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveHeader();
}

void ListItemGroupModelNG::RemoveFooter(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveFooter();
}

void ListItemGroupModelNG::RemoveHeader(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveHeader();
}

bool ListItemGroupModelNG::HasFooter(FrameNode* frameNode)
{
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsHasFooter();
}

bool ListItemGroupModelNG::HasHeader(FrameNode* frameNode)
{
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsHasHeader();
}

void ListItemGroupModelNG::ParseResObjDividerStrokeWidth(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("listItemGroup.divider.strokeWidth");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [frameNode](const RefPtr<ResourceObject>& resObj) {
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
            return;
        }
        V2::ItemDivider divider = GetDivider(frameNode);
        divider.strokeWidth = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("listItemGroup.divider.strokeWidth", resObj, std::move(updateFunc));
}

void ListItemGroupModelNG::ParseResObjDividerColor(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("listItemGroup.divider.color");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [frameNode](const RefPtr<ResourceObject>& resObj) {
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            return;
        }
        V2::ItemDivider divider = GetDivider(frameNode);
        divider.color = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("listItemGroup.divider.color", resObj, std::move(updateFunc));
}

void ListItemGroupModelNG::ParseResObjDividerStartMargin(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("listItemGroup.divider.startMargin");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [frameNode](const RefPtr<ResourceObject>& resObj) {
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
            return;
        }
        V2::ItemDivider divider = GetDivider(frameNode);
        divider.startMargin = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("listItemGroup.divider.startMargin", resObj, std::move(updateFunc));
}
void ListItemGroupModelNG::ParseResObjDividerEndMargin(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("listItemGroup.divider.endMargin");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [frameNode](const RefPtr<ResourceObject>& resObj) {
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
            return;
        }
        V2::ItemDivider divider = GetDivider(frameNode);
        divider.endMargin = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("listItemGroup.divider.endMargin", resObj, std::move(updateFunc));
}

void ListItemGroupModelNG::ParseResObjDividerStrokeWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("listItemGroup.divider.strokeWidth");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [frameNode](const RefPtr<ResourceObject>& resObj) {
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
            return;
        }
        V2::ItemDivider divider = GetDivider(frameNode);
        divider.strokeWidth = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("listItemGroup.divider.strokeWidth", resObj, std::move(updateFunc));
}

void ListItemGroupModelNG::ParseResObjDividerColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("listItemGroup.divider.color");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [frameNode](const RefPtr<ResourceObject>& resObj) {
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            return;
        }
        V2::ItemDivider divider = GetDivider(frameNode);
        divider.color = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("listItemGroup.divider.color", resObj, std::move(updateFunc));
}

void ListItemGroupModelNG::ParseResObjDividerStartMargin(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{

    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("listItemGroup.divider.startMargin");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [frameNode](const RefPtr<ResourceObject>& resObj) {
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
            return;
        }
        V2::ItemDivider divider = GetDivider(frameNode);
        divider.startMargin = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("listItemGroup.divider.startMargin", resObj, std::move(updateFunc));
}

void ListItemGroupModelNG::ParseResObjDividerEndMargin(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("listItemGroup.divider.endMargin");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [frameNode](const RefPtr<ResourceObject>& resObj) {
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
            return;
        }
        V2::ItemDivider divider = GetDivider(frameNode);
        divider.endMargin = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("listItemGroup.divider.endMargin", resObj, std::move(updateFunc));
}

void ListItemGroupModelNG::SetDividerColorByUser(bool isByUser)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    ACE_UPDATE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, DividerColorSetByUser, isByUser);
}

void ListItemGroupModelNG::SetDividerColorByUser(FrameNode* frameNode, bool colorSetByUser)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, DividerColorSetByUser, colorSetByUser, frameNode);
}
} // namespace OHOS::Ace::NG
