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

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void ListItemGroupModelNG::Create(V2::ListItemGroupStyle listItemGroupStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, nodeId, [itemGroupStyle = listItemGroupStyle]() {
            return AceType::MakeRefPtr<ListItemGroupPattern>(nullptr, itemGroupStyle);
        });
    stack->Push(frameNode);
}

void ListItemGroupModelNG::SetSpace(const Dimension& space)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListItemGroupLayoutProperty, Space, space);
}

void ListItemGroupModelNG::SetDivider(const V2::ItemDivider& divider)
{
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
    CHECK_NULL_VOID_NOLOG(headerNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddHeader(headerNode);
}

void ListItemGroupModelNG::SetFooter(std::function<void()>&& footer)
{
    RefPtr<NG::UINode> footerNode;
    if (footer) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        footer();
        footerNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    CHECK_NULL_VOID_NOLOG(footerNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(footerNode);
}
} // namespace OHOS::Ace::NG
