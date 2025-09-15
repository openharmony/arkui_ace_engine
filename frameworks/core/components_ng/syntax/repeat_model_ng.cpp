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

#include "core/components_ng/syntax/repeat_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/repeat_node.h"
#include "core/components_ng/syntax/syntax_item.h"

namespace OHOS::Ace::NG {


void RepeatModelNG::StartRender()
{
    ACE_SCOPED_TRACE("RepeatModelNG::StartRender");
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(nodeId);
    stack->Push(repeatNode);

    // move current id array and children to temp
    repeatNode->CreateTempItems();
}

void RepeatModelNG::FinishRender(std::list<int32_t>& removedElmtId)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto repeatNode = AceType::DynamicCast<RepeatNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(repeatNode);
    repeatNode->FinishRepeatRender(removedElmtId);
    stack->PopContainer();
}

void RepeatModelNG::MoveChild(uint32_t fromIndex)
{
    ACE_SCOPED_TRACE("RepeatModelNG::MoveChild()");
    auto* stack = ViewStackProcessor::GetInstance();
    auto repeatNode = AceType::DynamicCast<RepeatNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(repeatNode);
    repeatNode->MoveChild(fromIndex);
}

void RepeatModelNG::CreateNewChildStart(const std::string& key)
{
    ACE_SCOPED_TRACE("RepeatModelNG::CreateNewChildStart()");
    auto* stack = NG::ViewStackProcessor::GetInstance();
    stack->PushKey(key);
    const auto stacksKey = stack->GetKey();
    auto node = AceType::MakeRefPtr<SyntaxItem>(stacksKey);
    ElementRegister::GetInstance()->AddUINode(node);
    stack->Push(node);
}

void RepeatModelNG::CreateNewChildFinish(const std::string& key)
{
    ACE_SCOPED_TRACE("RepeatModelNG::CreateNewChildFinish()");
    auto* stack = ViewStackProcessor::GetInstance();
    stack->PopKey();
    stack->PopContainer();
}

void RepeatModelNG::AfterAddChild()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<RepeatNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    node->AfterAddChild();
}

void RepeatModelNG::OnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<RepeatNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    node->SetOnMove(std::move(onMove));
}

void RepeatModelNG::SetItemDragHandler(std::function<void(int32_t)>&& onLongPress,
    std::function<void(int32_t)>&& onDragStart, std::function<void(int32_t, int32_t)>&& onMoveThrough,
    std::function<void(int32_t)>&& onDrop)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<RepeatNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    node->SetItemDragHandler(
        std::move(onLongPress), std::move(onDragStart), std::move(onMoveThrough), std::move(onDrop));
}
} // namespace OHOS::Ace::NG
