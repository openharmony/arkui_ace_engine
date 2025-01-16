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

#include "core/components_ng/syntax/repeat_virtual_scroll_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"

namespace OHOS::Ace::NG {

void RepeatVirtualScrollModelNG::Create(
    uint32_t totalCount,
    const std::map<std::string, std::pair<bool, uint32_t>>& templateCachedCountMap,
    const std::function<void(uint32_t forIndex)>& onCreateNode,
    const std::function<void(const std::string& fromKey, uint32_t forIndex)>& onUpdateNode,
    const std::function<std::list<std::string>(uint32_t from, uint32_t to)>& onGetKeys4Range,
    const std::function<std::list<std::string>(uint32_t from, uint32_t to)>& onGetTypes4Range,
    const std::function<void(int32_t from, int32_t to)>& onSetActiveRange,
    bool reusable)
{
    ACE_SCOPED_TRACE("RepeatVirtualScrollModelNG::Create");
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        nodeId,
        totalCount,
        templateCachedCountMap,
        onCreateNode,
        onUpdateNode,
        onGetKeys4Range,
        onGetTypes4Range,
        onSetActiveRange,
        reusable);
    stack->Push(repeatNode);
    stack->PopContainer();
}

void RepeatVirtualScrollModelNG::UpdateRenderState(uint32_t totalCount, bool visibleItemsChanged)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto repeatNode = ElementRegister::GetInstance()->GetSpecificItemById<RepeatVirtualScrollNode>(nodeId);
    CHECK_NULL_VOID(repeatNode);
    repeatNode->UpdateTotalCount(totalCount);
    repeatNode->UpdateRenderState(visibleItemsChanged);
}

void RepeatVirtualScrollModelNG::OnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<RepeatVirtualScrollNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    node->SetOnMove(std::move(onMove));
}

void RepeatVirtualScrollModelNG::SetCreateByTemplate(bool isCreatedByTemplate)
{
    auto childOfRepeat = ViewStackProcessor::GetInstance()->GetMainElementNode();
    if (childOfRepeat) {
        childOfRepeat->SetAllowReusableV2Descendant(!isCreatedByTemplate);
    }
}
} // namespace OHOS::Ace::NG
