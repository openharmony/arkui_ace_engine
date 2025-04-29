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

#include "core/components_ng/syntax/for_each_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/syntax_item.h"

namespace OHOS::Ace::NG {

void ForEachModelNG::Pop()
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->PopContainer();
}

void ForEachModelNG::Create(const std::string& compilerGenId, const OHOS::Ace::ForEachFunc& ForEachFunc)
{
    TAG_LOGW(AceLogTag::ACE_FOREACH, "Create (with 2 params) unsupported by ForEachModelNG");
}

void ForEachModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto forEachNode = ForEachNode::GetOrCreateForEachNode(nodeId);
    stack->Push(forEachNode);

    // move current id array and children to temp.
    // when call pop function, compare new id array and children with old one to update.
    forEachNode->CreateTempItems();
}

std::list<std::string> ForEachModelNG::GetCurrentIdList(int32_t nodeId)
{
    auto forEachNode = ForEachNode::GetOrCreateForEachNode(nodeId);
    return forEachNode->GetTempIds();
}

void ForEachModelNG::SetNewIds(std::list<std::string>&& newIds)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<ForEachNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    node->SetIds(std::move(newIds));
}

void ForEachModelNG::SetRemovedElmtIds(std::list<int32_t>& removedElmtId)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<ForEachNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    node->CollectRemovingIds(removedElmtId);
}

void ForEachModelNG::CreateNewChildStart(const std::string& id)
{
    auto* stack = NG::ViewStackProcessor::GetInstance();
    stack->PushKey(id);
    const auto stacksKey = stack->GetKey();
    auto node = AceType::MakeRefPtr<SyntaxItem>(stacksKey);
    ElementRegister::GetInstance()->AddUINode(node);
    stack->Push(node);
}

void ForEachModelNG::CreateNewChildFinish(const std::string& id)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->PopKey();
    stack->PopContainer();
}

void ForEachModelNG::OnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<ForEachNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    node->SetOnMove(std::move(onMove));
}

void ForEachModelNG::SetItemDragHandler(std::function<void(int32_t)>&& onLongPress,
    std::function<void(int32_t)>&& onDragStart, std::function<void(int32_t, int32_t)>&& onMoveThrough,
    std::function<void(int32_t)>&& onDrop)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<ForEachNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    node->SetItemDragHandler(
        std::move(onLongPress), std::move(onDragStart), std::move(onMoveThrough), std::move(onDrop));
}
} // namespace OHOS::Ace::NG
