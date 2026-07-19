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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_ENVIRONMENT_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_ENVIRONMENT_MANAGER_H

#include <any>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/manager/environment/environment_types.h"

namespace OHOS::Ace::NG {

class EnvironmentManager;
class FrameNode;
class UINode;
class WithEnvNode;

enum class SystemEnvImplicitNotifyMode : uint8_t {
    NONE = 0,
    FULL,
    PRECISE,
};

struct SystemEnvDispatchContext {
    EnvironmentManager& manager;
    RefPtr<UINode> node;
    RefPtr<FrameNode> frameNode;
    std::string_view key;
};

using SystemEnvDispatchCallback = void (*)(const SystemEnvDispatchContext& context);

struct SystemEnvHandler {
    std::string_view key;
    SystemEnvImplicitNotifyMode implicitNotifyMode = SystemEnvImplicitNotifyMode::NONE;
    SystemEnvDispatchCallback dispatchImplicit = nullptr;
};

enum class EnvironmentPropertyKind : uint8_t {
    SYSTEM = 0,
    ENV = SYSTEM,
    CUSTOM,
};

using EnvironmentValueChangedCallback =
    void (*)(const RefPtr<UINode>& node, EnvironmentPropertyKind kind, const std::string& key);

class ACE_FORCE_EXPORT EnvironmentManager : public virtual AceType {
    DECLARE_ACE_TYPE(EnvironmentManager, AceType);

public:
    EnvironmentManager();
    ~EnvironmentManager() override = default;

    static void RegisterValueChangedCallback(
        EnvironmentPropertyKind kind, const std::string& key, EnvironmentValueChangedCallback callback);

    void RegisterSystemEnvHandler(const SystemEnvHandler& handler);
    SystemEnvImplicitNotifyMode GetSystemEnvImplicitNotifyMode(std::string_view key) const;
    void DispatchImplicitSystemEnvChanged(const SystemEnvDispatchContext& context);

    bool RemoveSystemEnvValue(const RefPtr<UINode>& scope, const std::string& key);
    bool SetSystemEnvValue(const RefPtr<UINode>& scope, const std::string& key, SystemEnvValue value);
    bool FindSystemEnvValueByKey(const RefPtr<UINode>& consumer, const std::string& key, SystemEnvValue& outValue);
    bool RemoveCustomEnvValue(const RefPtr<UINode>& scope, const std::string& key);
    bool SetCustomEnvValue(const RefPtr<UINode>& scope, const std::string& key, std::any value);
    bool FindCustomEnvValueByKey(const RefPtr<UINode>& consumer, const std::string& key, std::any& outValue);
    bool ResolveSystemEnvValueForImplicitReader(
        const RefPtr<UINode>& reader, const std::string& key, SystemEnvValue& outValue) const;

private:
    enum class EnvironmentValueChangeType : uint8_t {
        ADD = 0,
        UPDATE,
        REMOVE,
    };

    struct ExplicitEnvReaderRecord {
        // UINode::GetId() can be reused after node destruction. Keep the weak pointer
        // to verify that the registry entry still belongs to the same live node.
        WeakPtr<UINode> weak;
        // Each key records the WithEnv scope that currently owns this reader. Empty weak means miss.
        std::unordered_map<std::string, WeakPtr<WithEnvNode>> ownerScopes;
    };

    struct EnvScopeReaderRecord {
        WeakPtr<WithEnvNode> weak;
        std::unordered_map<std::string, std::unordered_set<int32_t>> readerIdsByKey;
    };

    struct ChangedEnvValue {
        std::optional<SystemEnvValue> systemValue;
        std::optional<std::any> customValue;
    };

    using ExplicitEnvReaderRegistry = std::unordered_map<int32_t, ExplicitEnvReaderRecord>;
    using EnvScopeReaderRegistry = std::unordered_map<int32_t, EnvScopeReaderRecord>;

    std::optional<SystemEnvValue> ResolveSystemValue(const RefPtr<UINode>& startScope, const std::string& key) const;
    std::optional<std::any> ResolveCustomValue(const RefPtr<UINode>& startScope, const std::string& key) const;
    RefPtr<WithEnvNode> ResolveOwnerScope(
        const RefPtr<UINode>& startScope, EnvironmentPropertyKind kind, const std::string& key) const;

    void RegisterExplicitSystemEnvReader(const RefPtr<UINode>& readerNode, const std::string& key);
    void RegisterExplicitCustomEnvReader(const RefPtr<UINode>& readerNode, const std::string& key);
    void RegisterExplicitEnvReader(ExplicitEnvReaderRegistry& readerRegistry, EnvScopeReaderRegistry& scopeRegistry,
        const RefPtr<UINode>& readerNode, EnvironmentPropertyKind kind, const std::string& key);

    void AddExplicitReaderToScope(EnvScopeReaderRegistry& scopeRegistry,
        const RefPtr<WithEnvNode>& ownerScope, int32_t readerId, const std::string& key);
    void RemoveExplicitReaderFromScope(EnvScopeReaderRegistry& scopeRegistry,
        const RefPtr<WithEnvNode>& ownerScope, int32_t readerId, const std::string& key);
    void RemoveExplicitReaderFromAllScopes(EnvScopeReaderRegistry& scopeRegistry, int32_t readerId,
        const std::unordered_map<std::string, WeakPtr<WithEnvNode>>& ownerScopes);
    bool RebindExplicitEnvReader(ExplicitEnvReaderRegistry& readerRegistry, EnvScopeReaderRegistry& scopeRegistry,
        const RefPtr<UINode>& readerNode, EnvironmentPropertyKind kind, const std::string& key);

    void NotifyValueChanged(const RefPtr<UINode>& scope, EnvironmentPropertyKind kind, const std::string& key,
        EnvironmentValueChangeType changeType, const std::optional<ChangedEnvValue>& changedValue = std::nullopt);
    void NotifyImplicitSystemEnvChanged(
        const RefPtr<UINode>& scope, const std::string& key, EnvironmentValueChangeType changeType);
    void NotifyPreciseImplicitSystemEnvChanged(
        const RefPtr<UINode>& scope, const std::string& key, EnvironmentValueChangeType changeType);
    void NotifyExplicitEnvChanged(const RefPtr<UINode>& scope, EnvironmentPropertyKind kind, const std::string& key,
        EnvironmentValueChangeType changeType, const std::optional<ChangedEnvValue>& changedValue);
    void NotifyLegacyExplicitEnvChanged(const RefPtr<UINode>& scope, EnvironmentPropertyKind kind,
        const std::string& key, const std::optional<ChangedEnvValue>& changedValue);
    void NotifyExplicitReadersOwnedByScope(ExplicitEnvReaderRegistry& readerRegistry,
        EnvScopeReaderRegistry& scopeRegistry, const RefPtr<WithEnvNode>& ownerScope, EnvironmentPropertyKind kind,
        const std::string& key, const std::optional<ChangedEnvValue>& changedValue);
    void RebindExplicitReadersUnderScope(ExplicitEnvReaderRegistry& readerRegistry,
        EnvScopeReaderRegistry& scopeRegistry, const RefPtr<UINode>& scope, EnvironmentPropertyKind kind,
        const std::string& key, const std::optional<ChangedEnvValue>& changedValue);

    const SystemEnvHandler* FindSystemEnvHandler(std::string_view key) const;
    void DispatchImplicitSystemEnvChangedToNode(const RefPtr<UINode>& node, const std::string& key);
    void DispatchExplicitEnvChanged(const RefPtr<UINode>& node, EnvironmentPropertyKind kind, const std::string& key,
        const std::optional<ChangedEnvValue>& changedValue);

    ExplicitEnvReaderRegistry systemExplicitReaders_;
    ExplicitEnvReaderRegistry customExplicitReaders_;
    EnvScopeReaderRegistry systemExplicitScopes_;
    EnvScopeReaderRegistry customExplicitScopes_;
    std::unordered_map<std::string_view, SystemEnvHandler> systemEnvHandlers_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_ENVIRONMENT_MANAGER_H
