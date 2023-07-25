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

#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/syntax_item.h"

namespace OHOS::Ace::NG {

void ForEachModelNG::Pop()
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->PopContainer();
}

// FIXME, change to emply implementation
void ForEachModelNG::Create(const std::string& compilerGenId, const OHOS::Ace::ForEachFunc& ForEachFunc)
{
    LOGE("Create (with 2 params) unsupported by ForEachModelNG");
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
    // FIXME: is the nodeId needed, or can we do lile SetNewIds ?
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

void ForEachModelNG::CreateNewChildStart(const std::string& id)
{
    LOGD("Start create child with array id %{public}s.", id.c_str());
    auto* stack = NG::ViewStackProcessor::GetInstance();
    stack->PushKey(id);
    const auto stacksKey = stack->GetKey();
    auto node = AceType::MakeRefPtr<SyntaxItem>(stacksKey);
    ElementRegister::GetInstance()->AddUINode(node);
    stack->Push(node);
}

void ForEachModelNG::CreateNewChildFinish(const std::string& id)
{
    LOGD("Finish create child with array id %{public}s.", id.c_str());
    auto* stack = ViewStackProcessor::GetInstance();
    stack->PopKey();
    stack->PopContainer();
}

} // namespace OHOS::Ace::NG
