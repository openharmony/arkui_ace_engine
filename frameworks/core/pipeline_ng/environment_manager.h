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
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace::NG {

class UINode;

enum class EnvConsumerPhase : uint8_t {
    NONE = 0,
    BUILD,
    MODIFY,
    LAYOUT,
    PAINT,
};

class ACE_FORCE_EXPORT ScopedEnvConsumer final {
public:
    explicit ScopedEnvConsumer(const RefPtr<UINode>& node, EnvConsumerPhase phase = EnvConsumerPhase::NONE);
    ~ScopedEnvConsumer();

private:
    WeakPtr<UINode> previousNode_;
    EnvConsumerPhase previousPhase_ = EnvConsumerPhase::NONE;
    bool active_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ScopedEnvConsumer);
};

enum class EnvironmentPropertyKind : uint8_t {
    ENV = 0,
    CUSTOM,
};

enum class EnvironmentValueType : uint8_t {
    NONE = 0,
    BOOLEAN,
    NUMBER,
    STRING,
    CUSTOM,
};

struct EnvironmentQueryResult {
    EnvironmentValueType type = EnvironmentValueType::NONE;
    bool boolValue = false;
    double numberValue = 0.0;
    std::string stringValue;
    const std::any* value = nullptr;
};

using EnvironmentValueChangedCallback =
    void (*)(const RefPtr<UINode>& node, EnvironmentPropertyKind kind, const std::string& key);

class ACE_FORCE_EXPORT EnvironmentManager : public virtual AceType {
    DECLARE_ACE_TYPE(EnvironmentManager, AceType);

public:
    EnvironmentManager() = default;
    ~EnvironmentManager() override = default;

    static RefPtr<UINode> GetCurrentEnvConsumerNode();
    static void RegisterValueChangedCallback(
        EnvironmentPropertyKind kind, const std::string& key, EnvironmentValueChangedCallback callback);

    RefPtr<UINode> FindWithEnvNode(const RefPtr<UINode>& startNode) const;

    bool RemoveValue(
        const RefPtr<UINode>& scope, EnvironmentPropertyKind kind, const std::string& key);
    bool SetValue(
        const RefPtr<UINode>& scope, EnvironmentPropertyKind kind, const std::string& key, std::any value);
    bool FindValueByKey(const RefPtr<UINode>& startScope, EnvironmentPropertyKind kind, const std::string& key,
        EnvironmentQueryResult& outResult);
    bool FindValueByKey(const RefPtr<UINode>& startScope, const RefPtr<UINode>& dependentNode,
        EnvironmentPropertyKind kind, const std::string& key, EnvironmentQueryResult& outResult);

    void OnNodeAttached(const RefPtr<UINode>& node);
    void OnNodeDetached(const RefPtr<UINode>& node);

private:
    struct DependentEntry {
        // UINode::GetId() can be reused after node destruction. Keep the weak pointer
        // to verify that the registry entry still belongs to the same live node.
        WeakPtr<UINode> weak;
        // Keys that this node has queried and is currently depending on.
        std::unordered_set<std::string> keys;
    };

    using DependentRegistry = std::unordered_map<int32_t, DependentEntry>;

    bool ResolveOwnerScopeAndValue(const RefPtr<UINode>& startScope, EnvironmentPropertyKind kind,
        const std::string& key, EnvironmentQueryResult& outResult) const;

    void RegisterDependency(EnvironmentPropertyKind kind, const RefPtr<UINode>& dependentNode, const std::string& key);
    void EraseDependency(EnvironmentPropertyKind kind, int32_t nodeId, const std::string& key);

    void NotifyValueChanged(const RefPtr<UINode>& scope, EnvironmentPropertyKind kind, const std::string& key);
    void DispatchValueChangedToAffectedNode(
        const RefPtr<UINode>& node, EnvironmentPropertyKind kind, const std::string& key);

    void FireAllRegisteredCallbacksOf(const RefPtr<UINode>& liveNode);

    static constexpr size_t PROPERTY_KIND_COUNT = 2;
    std::array<DependentRegistry, PROPERTY_KIND_COUNT> dependents_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_ENVIRONMENT_MANAGER_H
