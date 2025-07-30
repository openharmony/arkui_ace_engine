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

#include "core/components_ng/pattern/recycle_view/recycle_manager.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void RecycleManager::Push(int32_t elmtId, WeakPtr<CustomNodeBase> &&node)
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    context->GetRecycleManager()->PushNode(elmtId, std::move(node));
}

void RecycleManager::ClearAll()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->GetRecycleManager()->ClearAllNodes();
}

void RecycleManager::Pop(int32_t elmtId)
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    context->GetRecycleManager()->PopNode(elmtId);
}

void RecycleManager::Erase(int32_t elmtId)
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    context->GetRecycleManager()->EraseNode(elmtId);
}

void RecycleManager::Notify(const ConfigurationChange &config)
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    context->GetRecycleManager()->NotifyConfigurationChange(config);
}

void RecycleManager::PushNode(int32_t elmtId, WeakPtr<CustomNodeBase>&& node)
{
    recyclePool_.try_emplace(elmtId, std::make_unique<RecycleNodeState>(std::move(node)));
}

void RecycleManager::ClearAllNodes()
{
    recyclePool_.clear();
}

void RecycleManager::PopNode(int32_t elmtId)
{
    auto it = recyclePool_.find(elmtId);
    CHECK_EQUAL_VOID(it, recyclePool_.end());
    auto node = it->second->node.Upgrade();
    if (!node) {
        recyclePool_.erase(it);
        return;
    }
    if (it->second->config.IsNeedUpdate()) {
        AceType::DynamicCast<UINode>(node)->UpdateConfigurationUpdate(it->second->config);
    }
    recyclePool_.erase(it);
}

void RecycleManager::EraseNode(int32_t elmtId)
{
    recyclePool_.erase(elmtId);
}

void RecycleManager::NotifyConfigurationChange(const ConfigurationChange& config)
{
    for (auto& state : recyclePool_) {
        state.second->MergeConfig(config);
    }
}
} // namespace OHOS::Ace::NG
