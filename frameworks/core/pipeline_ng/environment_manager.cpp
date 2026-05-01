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

#include "core/pipeline_ng/environment_manager.h"

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/syntax/with_env_node.h"

namespace OHOS::Ace::NG {
namespace {
thread_local WeakPtr<UINode> g_currentEnvConsumerNode;
thread_local EnvConsumerPhase g_currentEnvConsumerPhase = EnvConsumerPhase::NONE;

constexpr size_t PROPERTY_KIND_COUNT = 2;

using ValueChangedCallbackRegistry = std::array<std::unordered_map<std::string, EnvironmentValueChangedCallback>,
    PROPERTY_KIND_COUNT>;

ValueChangedCallbackRegistry& GetValueChangedCallbacks()
{
    static ValueChangedCallbackRegistry callbacks;
    return callbacks;
}

size_t ToIndex(EnvironmentPropertyKind kind)
{
    return kind == EnvironmentPropertyKind::CUSTOM ? 1 : 0;
}

bool IsValidKind(EnvironmentPropertyKind kind)
{
    return kind == EnvironmentPropertyKind::ENV || kind == EnvironmentPropertyKind::CUSTOM;
}

RefPtr<WithEnvNode> FindWithEnvNodeInternal(const RefPtr<UINode>& startNode)
{
    auto current = startNode;
    while (current) {
        auto scope = AceType::DynamicCast<WithEnvNode>(current);
        if (scope) {
            return scope;
        }
        current = current->GetParent();
    }
    return nullptr;
}

bool ReadScopeValue(
    const RefPtr<WithEnvNode>& scope, EnvironmentPropertyKind kind, const std::string& key,
    EnvironmentQueryResult& outResult)
{
    CHECK_NULL_RETURN(scope, false);
    if (kind == EnvironmentPropertyKind::CUSTOM) {
        auto value = scope->GetCustomEnvPropertyAny(key);
        if (!value) {
            return false;
        }
        outResult.type = EnvironmentValueType::CUSTOM;
        outResult.value = value;
        return true;
    }
    return false;
}

bool ScopeDefinesValue(const RefPtr<WithEnvNode>& scope, EnvironmentPropertyKind kind, const std::string& key)
{
    CHECK_NULL_RETURN(scope, false);
    if (kind == EnvironmentPropertyKind::ENV) {
        return scope->HasEnvProperty(key);
    }
    EnvironmentQueryResult result;
    return ReadScopeValue(scope, kind, key, result);
}

bool SetScopeValue(const RefPtr<WithEnvNode>& scope, EnvironmentPropertyKind kind, const std::string& key,
    const std::any& value)
{
    CHECK_NULL_RETURN(scope, false);
    if (kind == EnvironmentPropertyKind::CUSTOM) {
        scope->SetCustomEnvProperty(key, value);
        return true;
    }
    if (auto boolValue = std::any_cast<bool>(&value)) {
        scope->SetEnvProperty(key, *boolValue);
        return true;
    }
    if (auto doubleValue = std::any_cast<double>(&value)) {
        scope->SetEnvProperty(key, *doubleValue);
        return true;
    }
    if (auto stringValue = std::any_cast<std::string>(&value)) {
        scope->SetEnvProperty(key, *stringValue);
        return true;
    }
    return false;
}

template <typename Predicate, typename Visitor>
void DfsNotifyScopeSubtree(const RefPtr<UINode>& node, Predicate innerCoversKey, Visitor visit)
{
    if (!node) {
        return;
    }
    if (auto inner = AceType::DynamicCast<WithEnvNode>(node)) {
        if (innerCoversKey(inner)) {
            return;
        }
    }
    visit(node);
    for (const auto& child : node->GetChildren()) {
        DfsNotifyScopeSubtree(child, innerCoversKey, visit);
    }
}

template <typename Visitor>
void DfsForEachNode(const RefPtr<UINode>& node, Visitor visit)
{
    if (!node) {
        return;
    }
    visit(node);
    for (const auto& child : node->GetChildren()) {
        DfsForEachNode(child, visit);
    }
}

EnvironmentValueChangedCallback GetValueChangedCallback(EnvironmentPropertyKind kind, const std::string& key)
{
    auto& callbacks = GetValueChangedCallbacks()[ToIndex(kind)];
    auto iter = callbacks.find(key);
    if (iter == callbacks.end()) {
        return nullptr;
    }
    return iter->second;
}
} // namespace

ScopedEnvConsumer::ScopedEnvConsumer(const RefPtr<UINode>& node, EnvConsumerPhase phase)
{
    if (!node) {
        return;
    }
    previousNode_ = g_currentEnvConsumerNode;
    previousPhase_ = g_currentEnvConsumerPhase;
    g_currentEnvConsumerNode = WeakPtr<UINode>(node);
    g_currentEnvConsumerPhase = phase;
    active_ = true;
}

ScopedEnvConsumer::~ScopedEnvConsumer()
{
    if (!active_) {
        return;
    }
    g_currentEnvConsumerNode = previousNode_;
    g_currentEnvConsumerPhase = previousPhase_;
}

RefPtr<UINode> EnvironmentManager::GetCurrentEnvConsumerNode()
{
    if (g_currentEnvConsumerPhase == EnvConsumerPhase::BUILD) {
        auto node = ViewStackProcessor::GetInstance()->GetMainElementNode();
        if (node) {
            return node;
        }
    }
    return g_currentEnvConsumerNode.Upgrade();
}

void EnvironmentManager::RegisterValueChangedCallback(
    EnvironmentPropertyKind kind, const std::string& key, EnvironmentValueChangedCallback callback)
{
    if (!IsValidKind(kind) || !callback) {
        return;
    }
    GetValueChangedCallbacks()[ToIndex(kind)][key] = callback;
}

RefPtr<UINode> EnvironmentManager::FindWithEnvNode(const RefPtr<UINode>& startNode) const
{
    return FindWithEnvNodeInternal(startNode);
}

bool EnvironmentManager::SetValue(
    const RefPtr<UINode>& scope, EnvironmentPropertyKind kind, const std::string& key, std::any value)
{
    if (!IsValidKind(kind)) {
        return false;
    }
    auto withEnvNode = AceType::DynamicCast<WithEnvNode>(scope);
    CHECK_NULL_RETURN(withEnvNode, false);

    if (!SetScopeValue(withEnvNode, kind, key, value)) {
        return false;
    }
    NotifyValueChanged(scope, kind, key);
    return true;
}

bool EnvironmentManager::FindValueByKey(const RefPtr<UINode>& startScope, EnvironmentPropertyKind kind,
    const std::string& key, EnvironmentQueryResult& outResult)
{
    return FindValueByKey(startScope, GetCurrentEnvConsumerNode(), kind, key, outResult);
}

bool EnvironmentManager::FindValueByKey(const RefPtr<UINode>& startScope, const RefPtr<UINode>& dependentNode,
    EnvironmentPropertyKind kind, const std::string& key, EnvironmentQueryResult& outResult)
{
    outResult = {};
    if (!IsValidKind(kind)) {
        return false;
    }
    if (!ResolveOwnerScopeAndValue(startScope, kind, key, outResult)) {
        if (dependentNode) {
            EraseDependency(kind, dependentNode->GetId(), key);
        }
        return false;
    }
    RegisterDependency(kind, dependentNode, key);
    return true;
}

bool EnvironmentManager::ResolveOwnerScopeAndValue(const RefPtr<UINode>& startScope, EnvironmentPropertyKind kind,
    const std::string& key, EnvironmentQueryResult& outResult) const
{
    auto currentScope = FindWithEnvNodeInternal(startScope);
    while (currentScope) {
        if (ReadScopeValue(currentScope, kind, key, outResult)) {
            return true;
        }
        currentScope = FindWithEnvNodeInternal(currentScope->GetParent());
    }
    return false;
}

void EnvironmentManager::RegisterDependency(
    EnvironmentPropertyKind kind, const RefPtr<UINode>& dependentNode, const std::string& key)
{
    CHECK_NULL_VOID(dependentNode);
    auto& entry = dependents_[ToIndex(kind)][dependentNode->GetId()];
    if (entry.weak.Upgrade() != dependentNode) {
        entry.weak = WeakPtr<UINode>(dependentNode);
        entry.keys.clear();
    }
    entry.keys.insert(key);
}

void EnvironmentManager::EraseDependency(EnvironmentPropertyKind kind, int32_t nodeId, const std::string& key)
{
    auto& registry = dependents_[ToIndex(kind)];
    auto iter = registry.find(nodeId);
    if (iter == registry.end()) {
        return;
    }
    iter->second.keys.erase(key);
    if (iter->second.keys.empty()) {
        registry.erase(iter);
    }
}

void EnvironmentManager::NotifyValueChanged(
    const RefPtr<UINode>& scope, EnvironmentPropertyKind kind, const std::string& key)
{
    CHECK_NULL_VOID(scope);
    auto innerCoversKey = [kind, &key](const RefPtr<WithEnvNode>& inner) {
        return ScopeDefinesValue(inner, kind, key);
    };
    bool shouldDispatchAllAffectedNodes =
        kind == EnvironmentPropertyKind::CUSTOM || GetValueChangedCallback(kind, key) != nullptr;
    auto& registry = dependents_[ToIndex(kind)];
    for (const auto& child : scope->GetChildren()) {
        DfsNotifyScopeSubtree(child, innerCoversKey,
            [this, kind, &key, shouldDispatchAllAffectedNodes, &registry](const RefPtr<UINode>& node) {
                if (shouldDispatchAllAffectedNodes) {
                    DispatchValueChangedToAffectedNode(node, kind, key);
                    return;
                }
                auto iter = registry.find(node->GetId());
                if (iter == registry.end()) {
                    return;
                }
                if (iter->second.weak.Upgrade() != node) {
                    registry.erase(iter);
                    return;
                }
                if (iter->second.keys.count(key) == 0) {
                    return;
                }
                DispatchValueChangedToAffectedNode(node, kind, key);
            });
    }
}

void EnvironmentManager::DispatchValueChangedToAffectedNode(
    const RefPtr<UINode>& node, EnvironmentPropertyKind kind, const std::string& key)
{
    CHECK_NULL_VOID(node);
    auto callback = GetValueChangedCallback(kind, key);
    if (callback) {
        callback(node, kind, key);
    }
    if (kind == EnvironmentPropertyKind::CUSTOM) {
        auto customNode = AceType::DynamicCast<CustomNode>(node);
        if (customNode) {
            customNode->FireOnCustomEnvUpdate(key);
            customNode->MarkNeedUpdate();
        }
    }
}

void EnvironmentManager::FireAllRegisteredCallbacksOf(const RefPtr<UINode>& liveNode)
{
    CHECK_NULL_VOID(liveNode);
    auto nodeId = liveNode->GetId();

    for (size_t index = 0; index < dependents_.size(); ++index) {
        auto kind = index == ToIndex(EnvironmentPropertyKind::CUSTOM) ? EnvironmentPropertyKind::CUSTOM
                                                                      : EnvironmentPropertyKind::ENV;
        auto& registry = dependents_[index];
        auto iter = registry.find(nodeId);
        if (iter == registry.end()) {
            continue;
        }
        if (iter->second.weak.Upgrade() != liveNode) {
            registry.erase(iter);
            continue;
        }
        auto keys = iter->second.keys;
        for (const auto& key : keys) {
            DispatchValueChangedToAffectedNode(liveNode, kind, key);
        }
    }
}

void EnvironmentManager::OnNodeAttached(const RefPtr<UINode>& node)
{
    CHECK_NULL_VOID(node);
    DfsForEachNode(node, [this](const RefPtr<UINode>& cur) {
        FireAllRegisteredCallbacksOf(cur);
    });
}

void EnvironmentManager::OnNodeDetached(const RefPtr<UINode>& node)
{
    // Keep dependency entries on detach so a later re-attach can fire callbacks
    // and let the front-end re-query under the new ancestor chain. Truly destroyed
    // nodes are caught by the WeakPtr identity check on later notify/attach.
    (void)node;
}

} // namespace OHOS::Ace::NG
