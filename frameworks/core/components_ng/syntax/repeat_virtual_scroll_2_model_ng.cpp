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

#include "core/components_ng/syntax/repeat_virtual_scroll_2_model_ng.h"

#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_ng/syntax/syntax_item.h"

namespace OHOS::Ace::NG {

void RepeatVirtualScroll2ModelNG::Create(uint32_t arrLen, uint32_t totalCount,
    const std::function<std::pair<uint32_t, uint32_t>(int32_t)>& onGetRid4Index,
    const std::function<void(int32_t, int32_t)>& onRecycleItems,
    const std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)>& onActiveRange,
    const std::function<void(int32_t, int32_t)>& onMoveFromTo, const std::function<void()>& onPurge)
{
    ACE_SCOPED_TRACE("RepeatVirtualScroll2ModelNG::Create");
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto repeatNode = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        nodeId, arrLen, totalCount, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);

    stack->Push(repeatNode);
    stack->PopContainer();
}

void RepeatVirtualScroll2ModelNG::RemoveNode(uint32_t rid)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto repeatNode = AceType::DynamicCast<RepeatVirtualScroll2Node>(stack->GetMainElementNode());
    CHECK_NULL_VOID(repeatNode);
    repeatNode->RemoveNode(rid);
}

void RepeatVirtualScroll2ModelNG::SetInvalid(int32_t repeatElmtId, uint32_t rid)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto repeatNode = AceType::DynamicCast<RepeatVirtualScroll2Node>(stack->GetMainElementNode());
    if (repeatNode == nullptr) {
        repeatNode = ElementRegister::GetInstance()->GetSpecificItemById<RepeatVirtualScroll2Node>(repeatElmtId);
    }
    CHECK_NULL_VOID(repeatNode);
    repeatNode->SetInvalid(rid);
}

void RepeatVirtualScroll2ModelNG::RequestContainerReLayout(
    int32_t repeatElmtId, uint32_t arrLen, uint32_t totalCount, int32_t invalidateContainerLayoutFromChildIndex)
{
    // called as part of Repeat re-render, call chain starts on TS side
    // therefore, can not put RepeatVirtualScroll2Node to the ViewStackProcessor
    // instead, lookup the node from ElementRegister
    auto repeatNode = ElementRegister::GetInstance()->GetSpecificItemById<RepeatVirtualScroll2Node>(repeatElmtId);
    CHECK_NULL_VOID(repeatNode);
    repeatNode->UpdateTotalCount(totalCount);
    repeatNode->UpdateArrLen(arrLen);
    repeatNode->RequestContainerReLayout(invalidateContainerLayoutFromChildIndex);
}

void RepeatVirtualScroll2ModelNG::NotifyContainerLayoutChange(int32_t repeatElmtId, uint32_t arrLen,
    uint32_t totalCount, int32_t index, int32_t count, NG::UINode::NotificationType notificationType)
{
    auto repeatNode = ElementRegister::GetInstance()->GetSpecificItemById<RepeatVirtualScroll2Node>(repeatElmtId);
    CHECK_NULL_VOID(repeatNode);
    repeatNode->UpdateTotalCount(totalCount);
    repeatNode->UpdateArrLen(arrLen);
    repeatNode->NotifyContainerLayoutChange(index, count, notificationType);
}

void RepeatVirtualScroll2ModelNG::UpdateL1Rid4Index(int32_t repeatElmtId, uint32_t arrLen, uint32_t totalCount,
    uint32_t invalidateContainerLayoutFromChildIndex, std::map<int32_t, uint32_t>& l1Rd4Index)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto repeatNode = AceType::DynamicCast<RepeatVirtualScroll2Node>(stack->GetMainElementNode());
    if (repeatNode == nullptr) {
        repeatNode = ElementRegister::GetInstance()->GetSpecificItemById<RepeatVirtualScroll2Node>(repeatElmtId);
    }
    CHECK_NULL_VOID(repeatNode);
    repeatNode->UpdateTotalCount(totalCount);
    repeatNode->UpdateArrLen(arrLen);
    repeatNode->UpdateL1Rid4Index(l1Rd4Index);
    repeatNode->RequestContainerReLayout(invalidateContainerLayoutFromChildIndex);
}

void RepeatVirtualScroll2ModelNG::OnMove(int32_t repeatElmtId, std::function<void(int32_t, int32_t)>&& onMove)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto repeatNode = AceType::DynamicCast<RepeatVirtualScroll2Node>(stack->GetMainElementNode());
    if (repeatNode == nullptr) {
        repeatNode = ElementRegister::GetInstance()->GetSpecificItemById<RepeatVirtualScroll2Node>(repeatElmtId);
    }
    CHECK_NULL_VOID(repeatNode);
    repeatNode->SetOnMove(std::move(onMove));
}

void RepeatVirtualScroll2ModelNG::SetItemDragHandler(int32_t repeatElmtId, std::function<void(int32_t)>&& onLongPress,
    std::function<void(int32_t)>&& onDragStart, std::function<void(int32_t, int32_t)>&& onMoveThrough,
    std::function<void(int32_t)>&& onDrop)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto repeatNode = AceType::DynamicCast<RepeatVirtualScroll2Node>(stack->GetMainElementNode());
    if (repeatNode == nullptr) {
        repeatNode = ElementRegister::GetInstance()->GetSpecificItemById<RepeatVirtualScroll2Node>(repeatElmtId);
    }
    CHECK_NULL_VOID(repeatNode);
    repeatNode->SetItemDragHandler(
        std::move(onLongPress), std::move(onDragStart), std::move(onMoveThrough), std::move(onDrop));
}

void RepeatVirtualScroll2ModelNG::SetCreateByTemplate(bool isCreatedByTemplate)
{
    auto childOfRepeat = ViewStackProcessor::GetInstance()->GetMainElementNode();
    if (childOfRepeat) {
        childOfRepeat->SetAllowReusableV2Descendant(!isCreatedByTemplate);
    }
}

} // namespace OHOS::Ace::NG
