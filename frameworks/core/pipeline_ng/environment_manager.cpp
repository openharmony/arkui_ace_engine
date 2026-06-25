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

#include <utility>

#include "core/components/common/layout/constants.h"
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

bool ScopeDefinesValue(const RefPtr<WithEnvNode>& scope, EnvironmentPropertyKind kind, const std::string& key)
{
    CHECK_NULL_RETURN(scope, false);
    if (kind == EnvironmentPropertyKind::ENV) {
        return scope->HasSystemEnvProperty(key);
    }
    if (kind == EnvironmentPropertyKind::CUSTOM) {
        return scope->HasCustomEnvProperty(key);
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

bool EnvironmentManager::RemoveSystemEnvValue(const RefPtr<UINode>& scope, const std::string& key)
{
    auto withEnvNode = AceType::DynamicCast<WithEnvNode>(scope);
    CHECK_NULL_RETURN(withEnvNode, false);

    if (!withEnvNode->HasSystemEnvProperty(key)) {
        return true;
    }
    withEnvNode->RemoveSystemEnvProperty(key);
    NotifyValueChanged(scope, EnvironmentPropertyKind::ENV, key);
    return true;
}

bool EnvironmentManager::SetSystemEnvValue(const RefPtr<UINode>& scope, const std::string& key, SystemEnvValue value)
{
    auto withEnvNode = AceType::DynamicCast<WithEnvNode>(scope);
    CHECK_NULL_RETURN(withEnvNode, false);

    if (!withEnvNode->SetSystemEnvProperty(key, value)) {
        return false;
    }
    ChangedEnvValue changedValue;
    changedValue.systemValue.emplace(value);
    NotifyValueChanged(scope, EnvironmentPropertyKind::ENV, key, changedValue);
    return true;
}

bool EnvironmentManager::FindSystemEnvValueByKey(
    const RefPtr<UINode>& consumer, const std::string& key, SystemEnvValue& outValue)
{
    if (!ResolveSystemEnvValue(consumer, key, outValue)) {
        if (consumer) {
            EraseDependency(EnvironmentPropertyKind::ENV, consumer->GetId(), key);
        }
        return false;
    }
    RegisterDependency(EnvironmentPropertyKind::ENV, consumer, key);
    return true;
}

bool EnvironmentManager::RemoveCustomEnvValue(const RefPtr<UINode>& scope, const std::string& key)
{
    auto withEnvNode = AceType::DynamicCast<WithEnvNode>(scope);
    CHECK_NULL_RETURN(withEnvNode, false);

    if (!withEnvNode->HasCustomEnvProperty(key)) {
        return true;
    }
    withEnvNode->RemoveCustomEnvProperty(key);
    NotifyValueChanged(scope, EnvironmentPropertyKind::CUSTOM, key);
    return true;
}

bool EnvironmentManager::SetCustomEnvValue(const RefPtr<UINode>& scope, const std::string& key, std::any value)
{
    auto withEnvNode = AceType::DynamicCast<WithEnvNode>(scope);
    CHECK_NULL_RETURN(withEnvNode, false);

    ChangedEnvValue changedValue;
    changedValue.customValue.emplace(value);
    withEnvNode->SetCustomEnvProperty(key, std::move(value));
    NotifyValueChanged(scope, EnvironmentPropertyKind::CUSTOM, key, changedValue);
    return true;
}

bool EnvironmentManager::FindCustomEnvValueByKey(
    const RefPtr<UINode>& consumer, const std::string& key, std::any& outValue)
{
    if (!ResolveCustomEnvValue(consumer, key, outValue)) {
        if (consumer) {
            EraseDependency(EnvironmentPropertyKind::CUSTOM, consumer->GetId(), key);
        }
        return false;
    }
    RegisterDependency(EnvironmentPropertyKind::CUSTOM, consumer, key);
    return true;
}

bool EnvironmentManager::ResolveSystemEnvValueForImplicitReader(
    const RefPtr<UINode>& reader, const std::string& key, SystemEnvValue& outValue) const
{
    return ResolveSystemEnvValue(reader, key, outValue);
}

bool EnvironmentManager::ResolveSystemEnvValue(
    const RefPtr<UINode>& startScope, const std::string& key, SystemEnvValue& outValue) const
{
    auto currentScope = FindWithEnvNodeInternal(startScope);
    while (currentScope) {
        auto value = currentScope->GetSystemEnvProperty(key);
        if (value) {
            outValue = *value;
            return true;
        }
        currentScope = FindWithEnvNodeInternal(currentScope->GetParent());
    }
    return false;
}

bool EnvironmentManager::ResolveCustomEnvValue(
    const RefPtr<UINode>& startScope, const std::string& key, std::any& outValue) const
{
    auto currentScope = FindWithEnvNodeInternal(startScope);
    while (currentScope) {
        auto value = currentScope->GetCustomEnvPropertyAny(key);
        if (value) {
            outValue = *value;
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

void EnvironmentManager::NotifyValueChanged(const RefPtr<UINode>& scope, EnvironmentPropertyKind kind,
    const std::string& key, const std::optional<ChangedEnvValue>& changedValue)
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
            [this, kind, &key, &changedValue, shouldDispatchAllAffectedNodes, &registry](const RefPtr<UINode>& node) {
                if (shouldDispatchAllAffectedNodes) {
                    DispatchValueChangedToAffectedNode(node, kind, key, changedValue);
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
                DispatchValueChangedToAffectedNode(node, kind, key, changedValue);
            });
    }
}

void EnvironmentManager::DispatchValueChangedToAffectedNode(const RefPtr<UINode>& node, EnvironmentPropertyKind kind,
    const std::string& key, const std::optional<ChangedEnvValue>& changedValue)
{
    CHECK_NULL_VOID(node);
    auto callback = GetValueChangedCallback(kind, key);
    if (callback) {
        callback(node, kind, key);
    }
    if (kind == EnvironmentPropertyKind::CUSTOM) {
        auto customNode = AceType::DynamicCast<CustomNode>(node);
        if (customNode) {
            if (changedValue) {
                customNode->FireOnCustomEnvUpdate(key, changedValue->customValue.value_or(std::any()));
            } else {
                customNode->FireOnCustomEnvUpdate(key);
            }
            customNode->MarkNeedUpdate();
        }
    }
    if (kind == EnvironmentPropertyKind::ENV) {
        auto customNode = AceType::DynamicCast<CustomNode>(node);
        if (customNode) {
            if (changedValue) {
                customNode->FireOnSystemEnvUpdate(key, changedValue->systemValue.value_or(SystemEnvValue()));
            } else {
                customNode->FireOnSystemEnvUpdate(key);
            }
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
