/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/syntax/with_env_model_ng.h"

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/with_env_node.h"
#include "core/pipeline_ng/environment_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {

WithEnvModel* WithEnvModel::GetInstance()
{
    static NG::WithEnvModelNG instance;
    return &instance;
}

} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
RefPtr<EnvironmentManager> GetEnvironmentManager()
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetEnvironmentManager();
}

template<typename T>
bool SetEnvPropertyByManager(const RefPtr<WithEnvNode>& node, const std::string& key, T value)
{
    auto envManager = GetEnvironmentManager();
    CHECK_NULL_RETURN(envManager, false);
    return envManager->SetValue(node, EnvironmentPropertyKind::ENV, key, std::any(value));
}
} // namespace

void WithEnvModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(nodeId);
    stack->Push(withEnvNode);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetUseEnvManager(true);
}

void WithEnvModelNG::RemoveEnvProperty(const std::string& key)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<WithEnvNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    auto envManager = GetEnvironmentManager();
    if (envManager && envManager->RemoveValue(node, EnvironmentPropertyKind::ENV, key)) {
        return;
    }
    node->RemoveEnvProperty(key);
}

void WithEnvModelNG::SetEnvProperty(const std::string& key, const std::string& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<WithEnvNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    if (SetEnvPropertyByManager(node, key, value)) {
        return;
    }
    node->SetEnvProperty(key, value);
}

void WithEnvModelNG::SetEnvProperty(const std::string& key, double value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<WithEnvNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);

    if (SetEnvPropertyByManager(node, key, value)) {
        return;
    }
    node->SetEnvProperty(key, value);
}

void WithEnvModelNG::SetEnvProperty(const std::string& key, bool value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<WithEnvNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    if (SetEnvPropertyByManager(node, key, value)) {
        return;
    }
    node->SetEnvProperty(key, value);
}

void WithEnvModelNG::SetCustomEnvProperty(const std::string& key, std::any value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<WithEnvNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    auto envManager = GetEnvironmentManager();
    if (envManager && envManager->SetValue(node, EnvironmentPropertyKind::CUSTOM, key, value)) {
        return;
    }
    node->SetCustomEnvProperty(key, std::move(value));
}

const std::any* WithEnvModelNG::GetCustomEnvPropertyAny(const std::string& key)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<WithEnvNode>(stack->GetMainElementNode());
    CHECK_NULL_RETURN(node, nullptr);
    return node->GetCustomEnvPropertyAny(key);
}

} // namespace OHOS::Ace::NG
