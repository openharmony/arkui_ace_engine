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

#include <array>
#include <optional>
#include <utility>
#include <vector>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/syntax/with_env_node.h"

namespace OHOS::Ace::NG {
namespace {
constexpr bool USE_LEGACY_EXPLICIT_SCOPE_WALK_NOTIFY = false;
constexpr size_t PROPERTY_KIND_COUNT = 2;

using ValueChangedCallbackRegistry =
    std::array<std::unordered_map<std::string, EnvironmentValueChangedCallback>, PROPERTY_KIND_COUNT>;

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
    return kind == EnvironmentPropertyKind::SYSTEM || kind == EnvironmentPropertyKind::CUSTOM;
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

bool HasEnvironmentProperty(const RefPtr<WithEnvNode>& scope, EnvironmentPropertyKind kind, const std::string& key)
{
    CHECK_NULL_RETURN(scope, false);
    switch (kind) {
        case EnvironmentPropertyKind::SYSTEM:
            return scope->HasSystemEnvProperty(key);
        case EnvironmentPropertyKind::CUSTOM:
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

void DispatchDirectionChanged(const SystemEnvDispatchContext& context)
{
    auto customNode = AceType::DynamicCast<CustomNode>(context.node);
    if (customNode) {
        customNode->MarkNeedUpdate();
    }

    auto frameNode = context.frameNode;
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->MarkEnvDirty(ENV_KEY_DIRECTION);
    }
    ConfigurationChange configurationChange;
    configurationChange.directionUpdate = true;
    frameNode->OnConfigurationUpdate(configurationChange);
}

void DispatchFontScaleChanged(const SystemEnvDispatchContext& context)
{
    auto customNode = AceType::DynamicCast<CustomNode>(context.node);
    if (customNode) {
        customNode->MarkNeedUpdate();
    }

    auto frameNode = context.frameNode;
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->MarkEnvDirty(ENV_KEY_FONT_SCALE);
    }
    ConfigurationChange configurationChange;
    configurationChange.fontScaleUpdate = true;
    frameNode->OnConfigurationUpdate(configurationChange);
}

} // namespace

EnvironmentManager::EnvironmentManager()
{
    RegisterSystemEnvHandler({
        ENV_KEY_DIRECTION,
        SystemEnvImplicitNotifyMode::FULL,
        DispatchDirectionChanged,
    });
    RegisterSystemEnvHandler({
        ENV_KEY_FONT_SCALE,
        SystemEnvImplicitNotifyMode::FULL,
        DispatchFontScaleChanged,
    });
}

void EnvironmentManager::RegisterValueChangedCallback(
    EnvironmentPropertyKind kind, const std::string& key, EnvironmentValueChangedCallback callback)
{
    if (!IsValidKind(kind) || !callback) {
        return;
    }
    GetValueChangedCallbacks()[ToIndex(kind)][key] = callback;
}

void EnvironmentManager::RegisterSystemEnvHandler(const SystemEnvHandler& handler)
{
    if (handler.key.empty()) {
        return;
    }
    systemEnvHandlers_[handler.key] = handler;
}

SystemEnvImplicitNotifyMode EnvironmentManager::GetSystemEnvImplicitNotifyMode(std::string_view key) const
{
    auto handler = FindSystemEnvHandler(key);
    return handler ? handler->implicitNotifyMode : SystemEnvImplicitNotifyMode::NONE;
}

void EnvironmentManager::DispatchImplicitSystemEnvChanged(const SystemEnvDispatchContext& context)
{
    auto handler = FindSystemEnvHandler(context.key);
    if (!handler || !handler->dispatchImplicit) {
        return;
    }
    handler->dispatchImplicit(context);
}

bool EnvironmentManager::RemoveSystemEnvValue(const RefPtr<UINode>& scope, const std::string& key)
{
    auto withEnvNode = AceType::DynamicCast<WithEnvNode>(scope);
    CHECK_NULL_RETURN(withEnvNode, false);
    if (!withEnvNode->HasSystemEnvProperty(key)) {
        return true;
    }

    withEnvNode->RemoveSystemEnvProperty(key);
    NotifyValueChanged(scope, EnvironmentPropertyKind::SYSTEM, key, EnvironmentValueChangeType::REMOVE);
    return true;
}

bool EnvironmentManager::SetSystemEnvValue(const RefPtr<UINode>& scope, const std::string& key, SystemEnvValue value)
{
    auto withEnvNode = AceType::DynamicCast<WithEnvNode>(scope);
    CHECK_NULL_RETURN(withEnvNode, false);
    auto changeType = withEnvNode->HasSystemEnvProperty(key) ? EnvironmentValueChangeType::UPDATE
                                                             : EnvironmentValueChangeType::ADD;
    if (!withEnvNode->SetSystemEnvProperty(key, value)) {
        return false;
    }

    ChangedEnvValue changedValue;
    changedValue.systemValue.emplace(value);
    NotifyValueChanged(scope, EnvironmentPropertyKind::SYSTEM, key, changeType, changedValue);
    return true;
}

bool EnvironmentManager::FindSystemEnvValueByKey(
    const RefPtr<UINode>& consumer, const std::string& key, SystemEnvValue& outValue)
{
    RegisterExplicitSystemEnvReader(consumer, key);
    auto value = ResolveSystemValue(consumer, key);
    if (!value) {
        return false;
    }
    outValue = *value;
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
    NotifyValueChanged(scope, EnvironmentPropertyKind::CUSTOM, key, EnvironmentValueChangeType::REMOVE);
    return true;
}

bool EnvironmentManager::SetCustomEnvValue(const RefPtr<UINode>& scope, const std::string& key, std::any value)
{
    auto withEnvNode = AceType::DynamicCast<WithEnvNode>(scope);
    CHECK_NULL_RETURN(withEnvNode, false);
    auto changeType = withEnvNode->HasCustomEnvProperty(key) ? EnvironmentValueChangeType::UPDATE
                                                             : EnvironmentValueChangeType::ADD;

    ChangedEnvValue changedValue;
    changedValue.customValue.emplace(value);
    withEnvNode->SetCustomEnvProperty(key, std::move(value));
    NotifyValueChanged(scope, EnvironmentPropertyKind::CUSTOM, key, changeType, changedValue);
    return true;
}

bool EnvironmentManager::FindCustomEnvValueByKey(
    const RefPtr<UINode>& consumer, const std::string& key, std::any& outValue)
{
    RegisterExplicitCustomEnvReader(consumer, key);
    auto value = ResolveCustomValue(consumer, key);
    if (!value) {
        return false;
    }
    outValue = *value;
    return true;
}

bool EnvironmentManager::ResolveSystemEnvValueForImplicitReader(
    const RefPtr<UINode>& reader, const std::string& key, SystemEnvValue& outValue) const
{
    auto value = ResolveSystemValue(reader, key);
    if (!value) {
        return false;
    }
    outValue = *value;
    return true;
}

std::optional<SystemEnvValue> EnvironmentManager::ResolveSystemValue(
    const RefPtr<UINode>& startScope, const std::string& key) const
{
    auto currentScope = FindWithEnvNodeInternal(startScope);
    while (currentScope) {
        auto value = currentScope->GetSystemEnvProperty(key);
        if (value) {
            return value;
        }
        currentScope = FindWithEnvNodeInternal(currentScope->GetParent());
    }
    return std::nullopt;
}

std::optional<std::any> EnvironmentManager::ResolveCustomValue(
    const RefPtr<UINode>& startScope, const std::string& key) const
{
    auto currentScope = FindWithEnvNodeInternal(startScope);
    while (currentScope) {
        auto value = currentScope->GetCustomEnvPropertyAny(key);
        if (value) {
            return value;
        }
        currentScope = FindWithEnvNodeInternal(currentScope->GetParent());
    }
    return std::nullopt;
}

RefPtr<WithEnvNode> EnvironmentManager::ResolveOwnerScope(
    const RefPtr<UINode>& startScope, EnvironmentPropertyKind kind, const std::string& key) const
{
    auto currentScope = FindWithEnvNodeInternal(startScope);
    while (currentScope) {
        if (HasEnvironmentProperty(currentScope, kind, key)) {
            return currentScope;
        }
        currentScope = FindWithEnvNodeInternal(currentScope->GetParent());
    }
    return nullptr;
}

void EnvironmentManager::RegisterExplicitSystemEnvReader(const RefPtr<UINode>& readerNode, const std::string& key)
{
    RegisterExplicitEnvReader(
        systemExplicitReaders_, systemExplicitScopes_, readerNode, EnvironmentPropertyKind::SYSTEM, key);
}

void EnvironmentManager::RegisterExplicitCustomEnvReader(const RefPtr<UINode>& readerNode, const std::string& key)
{
    RegisterExplicitEnvReader(
        customExplicitReaders_, customExplicitScopes_, readerNode, EnvironmentPropertyKind::CUSTOM, key);
}

void EnvironmentManager::RegisterExplicitEnvReader(ExplicitEnvReaderRegistry& readerRegistry,
    EnvScopeReaderRegistry& scopeRegistry, const RefPtr<UINode>& readerNode, EnvironmentPropertyKind kind,
    const std::string& key)
{
    CHECK_NULL_VOID(readerNode);
    auto readerId = readerNode->GetId();
    auto& record = readerRegistry[readerId];
    if (record.weak.Upgrade() != readerNode) {
        RemoveExplicitReaderFromAllScopes(scopeRegistry, readerId, record.ownerScopes);
        record.weak = WeakPtr<UINode>(readerNode);
        record.ownerScopes.clear();
    }
    auto previousOwner = record.ownerScopes[key].Upgrade();
    auto ownerScope = ResolveOwnerScope(readerNode, kind, key);
    if (previousOwner != ownerScope) {
        RemoveExplicitReaderFromScope(scopeRegistry, previousOwner, readerId, key);
        AddExplicitReaderToScope(scopeRegistry, ownerScope, readerId, key);
        record.ownerScopes[key] = WeakPtr<WithEnvNode>(ownerScope);
    }
}

void EnvironmentManager::AddExplicitReaderToScope(EnvScopeReaderRegistry& scopeRegistry,
    const RefPtr<WithEnvNode>& ownerScope, int32_t readerId, const std::string& key)
{
    CHECK_NULL_VOID(ownerScope);
    auto& scopeRecord = scopeRegistry[ownerScope->GetId()];
    if (scopeRecord.weak.Upgrade() != ownerScope) {
        scopeRecord.weak = WeakPtr<WithEnvNode>(ownerScope);
        scopeRecord.readerIdsByKey.clear();
    }
    scopeRecord.readerIdsByKey[key].insert(readerId);
}

void EnvironmentManager::RemoveExplicitReaderFromScope(EnvScopeReaderRegistry& scopeRegistry,
    const RefPtr<WithEnvNode>& ownerScope, int32_t readerId, const std::string& key)
{
    CHECK_NULL_VOID(ownerScope);
    auto scopeIter = scopeRegistry.find(ownerScope->GetId());
    if (scopeIter == scopeRegistry.end()) {
        return;
    }
    if (scopeIter->second.weak.Upgrade() != ownerScope) {
        scopeRegistry.erase(scopeIter);
        return;
    }
    auto keyIter = scopeIter->second.readerIdsByKey.find(key);
    if (keyIter == scopeIter->second.readerIdsByKey.end()) {
        return;
    }
    keyIter->second.erase(readerId);
    if (keyIter->second.empty()) {
        scopeIter->second.readerIdsByKey.erase(keyIter);
    }
    if (scopeIter->second.readerIdsByKey.empty()) {
        scopeRegistry.erase(scopeIter);
    }
}

void EnvironmentManager::RemoveExplicitReaderFromAllScopes(EnvScopeReaderRegistry& scopeRegistry, int32_t readerId,
    const std::unordered_map<std::string, WeakPtr<WithEnvNode>>& ownerScopes)
{
    for (const auto& [key, weakScope] : ownerScopes) {
        RemoveExplicitReaderFromScope(scopeRegistry, weakScope.Upgrade(), readerId, key);
    }
}

bool EnvironmentManager::RebindExplicitEnvReader(ExplicitEnvReaderRegistry& readerRegistry,
    EnvScopeReaderRegistry& scopeRegistry, const RefPtr<UINode>& readerNode, EnvironmentPropertyKind kind,
    const std::string& key)
{
    CHECK_NULL_RETURN(readerNode, false);
    auto readerIter = readerRegistry.find(readerNode->GetId());
    if (readerIter == readerRegistry.end()) {
        return false;
    }
    if (readerIter->second.weak.Upgrade() != readerNode) {
        RemoveExplicitReaderFromAllScopes(scopeRegistry, readerNode->GetId(), readerIter->second.ownerScopes);
        readerRegistry.erase(readerIter);
        return false;
    }
    auto keyIter = readerIter->second.ownerScopes.find(key);
    if (keyIter == readerIter->second.ownerScopes.end()) {
        return false;
    }

    auto previousOwner = keyIter->second.Upgrade();
    auto ownerScope = ResolveOwnerScope(readerNode, kind, key);
    if (previousOwner == ownerScope) {
        return false;
    }
    RemoveExplicitReaderFromScope(scopeRegistry, previousOwner, readerNode->GetId(), key);
    AddExplicitReaderToScope(scopeRegistry, ownerScope, readerNode->GetId(), key);
    keyIter->second = WeakPtr<WithEnvNode>(ownerScope);
    return true;
}

void EnvironmentManager::NotifyValueChanged(
    const RefPtr<UINode>& scope, EnvironmentPropertyKind kind, const std::string& key,
    EnvironmentValueChangeType changeType, const std::optional<ChangedEnvValue>& changedValue)
{
    CHECK_NULL_VOID(scope);
    if (kind == EnvironmentPropertyKind::SYSTEM) {
        NotifyImplicitSystemEnvChanged(scope, key, changeType);
        NotifyExplicitEnvChanged(scope, kind, key, changeType, changedValue);
        return;
    }
    NotifyExplicitEnvChanged(scope, kind, key, changeType, changedValue);
}

void EnvironmentManager::NotifyImplicitSystemEnvChanged(
    const RefPtr<UINode>& scope, const std::string& key, EnvironmentValueChangeType changeType)
{
    CHECK_NULL_VOID(scope);
    auto notifyMode = GetSystemEnvImplicitNotifyMode(key);
    auto legacyCallback = GetValueChangedCallback(EnvironmentPropertyKind::SYSTEM, key);
    if (notifyMode == SystemEnvImplicitNotifyMode::NONE && legacyCallback == nullptr) {
        return;
    }
    if (notifyMode == SystemEnvImplicitNotifyMode::PRECISE) {
        NotifyPreciseImplicitSystemEnvChanged(scope, key, changeType);
        return;
    }
    if (notifyMode != SystemEnvImplicitNotifyMode::FULL && legacyCallback == nullptr) {
        return;
    }
    auto innerCoversKey = [&key](const RefPtr<WithEnvNode>& inner) {
        return HasEnvironmentProperty(inner, EnvironmentPropertyKind::SYSTEM, key);
    };
    for (const auto& child : scope->GetChildren()) {
        DfsNotifyScopeSubtree(child, innerCoversKey,
            [this, &key](const RefPtr<UINode>& node) {
                DispatchImplicitSystemEnvChangedToNode(node, key);
            });
    }
}

void EnvironmentManager::NotifyPreciseImplicitSystemEnvChanged(
    const RefPtr<UINode>& scope, const std::string& key, EnvironmentValueChangeType changeType)
{
    (void)scope;
    (void)key;
    (void)changeType;
    // Reserved for future system env implicit reader indexes.
}

void EnvironmentManager::NotifyExplicitEnvChanged(
    const RefPtr<UINode>& scope, EnvironmentPropertyKind kind, const std::string& key,
    EnvironmentValueChangeType changeType, const std::optional<ChangedEnvValue>& changedValue)
{
    CHECK_NULL_VOID(scope);
    if constexpr (USE_LEGACY_EXPLICIT_SCOPE_WALK_NOTIFY) {
        NotifyLegacyExplicitEnvChanged(scope, kind, key, changedValue);
        return;
    }

    auto ownerScope = AceType::DynamicCast<WithEnvNode>(scope);
    CHECK_NULL_VOID(ownerScope);
    auto& readerRegistry =
        kind == EnvironmentPropertyKind::SYSTEM ? systemExplicitReaders_ : customExplicitReaders_;
    auto& scopeRegistry =
        kind == EnvironmentPropertyKind::SYSTEM ? systemExplicitScopes_ : customExplicitScopes_;

    switch (changeType) {
        case EnvironmentValueChangeType::UPDATE:
            NotifyExplicitReadersOwnedByScope(readerRegistry, scopeRegistry, ownerScope, kind, key, changedValue);
            return;
        case EnvironmentValueChangeType::ADD:
            RebindExplicitReadersUnderScope(readerRegistry, scopeRegistry, scope, kind, key, changedValue);
            return;
        case EnvironmentValueChangeType::REMOVE:
            NotifyExplicitReadersOwnedByScope(readerRegistry, scopeRegistry, ownerScope, kind, key, changedValue);
            return;
    }
}

void EnvironmentManager::NotifyLegacyExplicitEnvChanged(const RefPtr<UINode>& scope, EnvironmentPropertyKind kind,
    const std::string& key, const std::optional<ChangedEnvValue>& changedValue)
{
    CHECK_NULL_VOID(scope);
    auto innerCoversKey = [kind, &key](const RefPtr<WithEnvNode>& inner) {
        return HasEnvironmentProperty(inner, kind, key);
    };
    for (const auto& child : scope->GetChildren()) {
        DfsNotifyScopeSubtree(child, innerCoversKey,
            [this, kind, &key, &changedValue](const RefPtr<UINode>& node) {
                DispatchExplicitEnvChanged(node, kind, key, changedValue);
            });
    }
}

void EnvironmentManager::NotifyExplicitReadersOwnedByScope(ExplicitEnvReaderRegistry& readerRegistry,
    EnvScopeReaderRegistry& scopeRegistry, const RefPtr<WithEnvNode>& ownerScope, EnvironmentPropertyKind kind,
    const std::string& key, const std::optional<ChangedEnvValue>& changedValue)
{
    CHECK_NULL_VOID(ownerScope);
    auto scopeIter = scopeRegistry.find(ownerScope->GetId());
    if (scopeIter == scopeRegistry.end()) {
        return;
    }
    if (scopeIter->second.weak.Upgrade() != ownerScope) {
        scopeRegistry.erase(scopeIter);
        return;
    }
    auto keyIter = scopeIter->second.readerIdsByKey.find(key);
    if (keyIter == scopeIter->second.readerIdsByKey.end()) {
        return;
    }
    std::vector<int32_t> readerIds(keyIter->second.begin(), keyIter->second.end());
    for (auto readerId : readerIds) {
        auto readerIter = readerRegistry.find(readerId);
        if (readerIter == readerRegistry.end()) {
            continue;
        }
        auto readerNode = readerIter->second.weak.Upgrade();
        if (!readerNode) {
            RemoveExplicitReaderFromAllScopes(scopeRegistry, readerId, readerIter->second.ownerScopes);
            readerRegistry.erase(readerIter);
            continue;
        }
        if (readerIter->second.ownerScopes.find(key) == readerIter->second.ownerScopes.end()) {
            continue;
        }
        RebindExplicitEnvReader(readerRegistry, scopeRegistry, readerNode, kind, key);
        DispatchExplicitEnvChanged(readerNode, kind, key, changedValue);
    }
}

void EnvironmentManager::RebindExplicitReadersUnderScope(ExplicitEnvReaderRegistry& readerRegistry,
    EnvScopeReaderRegistry& scopeRegistry, const RefPtr<UINode>& scope, EnvironmentPropertyKind kind,
    const std::string& key, const std::optional<ChangedEnvValue>& changedValue)
{
    CHECK_NULL_VOID(scope);
    auto innerCoversKey = [kind, &key](const RefPtr<WithEnvNode>& inner) {
        return HasEnvironmentProperty(inner, kind, key);
    };
    for (const auto& child : scope->GetChildren()) {
        DfsNotifyScopeSubtree(child, innerCoversKey,
            [this, &readerRegistry, &scopeRegistry, kind, &key, &changedValue](const RefPtr<UINode>& node) {
                auto readerIter = readerRegistry.find(node->GetId());
                if (readerIter == readerRegistry.end()) {
                    return;
                }
                if (readerIter->second.weak.Upgrade() != node) {
                    RemoveExplicitReaderFromAllScopes(scopeRegistry, node->GetId(), readerIter->second.ownerScopes);
                    readerRegistry.erase(readerIter);
                    return;
                }
                if (readerIter->second.ownerScopes.find(key) == readerIter->second.ownerScopes.end()) {
                    return;
                }
                if (RebindExplicitEnvReader(readerRegistry, scopeRegistry, node, kind, key)) {
                    DispatchExplicitEnvChanged(node, kind, key, changedValue);
                }
            });
    }
}

const SystemEnvHandler* EnvironmentManager::FindSystemEnvHandler(std::string_view key) const
{
    auto iter = systemEnvHandlers_.find(key);
    if (iter == systemEnvHandlers_.end()) {
        return nullptr;
    }
    return &iter->second;
}

void EnvironmentManager::DispatchImplicitSystemEnvChangedToNode(const RefPtr<UINode>& node, const std::string& key)
{
    CHECK_NULL_VOID(node);
    auto callback = GetValueChangedCallback(EnvironmentPropertyKind::SYSTEM, key);
    if (callback) {
        callback(node, EnvironmentPropertyKind::SYSTEM, key);
    }
    SystemEnvDispatchContext context { *this, node, AceType::DynamicCast<FrameNode>(node), key };
    DispatchImplicitSystemEnvChanged(context);
}

void EnvironmentManager::DispatchExplicitEnvChanged(
    const RefPtr<UINode>& node, EnvironmentPropertyKind kind, const std::string& key,
    const std::optional<ChangedEnvValue>& changedValue)
{
    CHECK_NULL_VOID(node);
    auto customNode = AceType::DynamicCast<CustomNode>(node);
    CHECK_NULL_VOID(customNode);
    if (kind == EnvironmentPropertyKind::CUSTOM) {
        if (changedValue) {
            customNode->FireOnCustomEnvUpdate(key, changedValue->customValue.value_or(std::any()));
        } else {
            customNode->FireOnCustomEnvUpdate(key);
        }
    } else if (kind == EnvironmentPropertyKind::SYSTEM) {
        if (changedValue) {
            customNode->FireOnSystemEnvUpdate(key, changedValue->systemValue.value_or(SystemEnvValue()));
        } else {
            customNode->FireOnSystemEnvUpdate(key);
        }
    }
    customNode->MarkNeedUpdate();
}

} // namespace OHOS::Ace::NG
