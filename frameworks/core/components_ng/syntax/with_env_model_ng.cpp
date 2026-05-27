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
#include "core/components_ng/manager/environment/environment_types.h"
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

bool SetSystemEnvPropertyByManager(const RefPtr<WithEnvNode>& node, const std::string& key, SystemEnvValue value)
{
    auto envManager = GetEnvironmentManager();
    CHECK_NULL_RETURN(envManager, false);
    return envManager->SetSystemEnvValue(node, key, value);
}

bool RemoveSystemEnvPropertyByManager(const RefPtr<WithEnvNode>& node, const std::string& key)
{
    auto envManager = GetEnvironmentManager();
    CHECK_NULL_RETURN(envManager, false);
    return envManager->RemoveSystemEnvValue(node, key);
}

bool SetCustomEnvPropertyByManager(const RefPtr<WithEnvNode>& node, const std::string& key, std::any value)
{
    auto envManager = GetEnvironmentManager();
    CHECK_NULL_RETURN(envManager, false);
    return envManager->SetCustomEnvValue(node, key, std::move(value));
}

bool RemoveCustomEnvPropertyByManager(const RefPtr<WithEnvNode>& node, const std::string& key)
{
    auto envManager = GetEnvironmentManager();
    CHECK_NULL_RETURN(envManager, false);
    return envManager->RemoveCustomEnvValue(node, key);
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

void WithEnvModelNG::RemoveSystemEnvProperty(const std::string& key)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<WithEnvNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    if (RemoveSystemEnvPropertyByManager(node, key)) {
        return;
    }
    node->RemoveSystemEnvProperty(key);
}

void WithEnvModelNG::SetSystemEnvProperty(const std::string& key, TextDirection value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<WithEnvNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    if (key != ENV_KEY_DIRECTION) {
        return;
    }
    if (SetSystemEnvPropertyByManager(node, key, SystemEnvValue::FromDirection(value))) {
        return;
    }
    node->SetSystemEnvProperty(key, SystemEnvValue::FromDirection(value));
}

void WithEnvModelNG::SetSystemEnvProperty(const std::string& key, double value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<WithEnvNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    if (key != ENV_KEY_FONT_SCALE) {
        return;
    }
    if (SetSystemEnvPropertyByManager(node, key, SystemEnvValue::FromDouble(value))) {
        return;
    }
    node->SetSystemEnvProperty(key, SystemEnvValue::FromDouble(value));
}

void WithEnvModelNG::RemoveCustomEnvProperty(const std::string& key)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<WithEnvNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    if (RemoveCustomEnvPropertyByManager(node, key)) {
        return;
    }
    node->RemoveCustomEnvProperty(key);
}

void WithEnvModelNG::SetCustomEnvProperty(const std::string& key, std::any value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = AceType::DynamicCast<WithEnvNode>(stack->GetMainElementNode());
    CHECK_NULL_VOID(node);
    if (SetCustomEnvPropertyByManager(node, key, value)) {
        return;
    }
    node->SetCustomEnvProperty(key, std::move(value));
}

} // namespace OHOS::Ace::NG
