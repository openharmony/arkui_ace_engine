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

#include <hilog/log.h>

#include "ScenarioManager.h"


namespace NativeXComponentSample {

/**
 * @brief Destructor for ScenarioManager
 */
ScenarioManager::~ScenarioManager()
{
    Cleanup();
}

/**
 * @brief Gets the singleton instance of ScenarioManager
 * @return Reference to the singleton instance
 */
ScenarioManager& ScenarioManager::GetInstance()
{
    static ScenarioManager instance;
    return instance;
}

/**
 * @brief Registers a scenario with a given ID
 * @param id The unique identifier for the scenario
 * @param scenario Pointer to the scenario to register
 */
void ScenarioManager::RegisterScenario(const std::string& id,
    ScenarioBase* scenario)
{
    if (scenario == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ScenarioManager",
            "Failed to register scenario: scenario is null, id=%{public}s",
            id.c_str());
        return;
    }

    // Check if already exists
    if (scenarios_.find(id) != scenarios_.end()) {
        OH_LOG_Print(LOG_APP, LOG_WARN, LOG_PRINT_DOMAIN, "ScenarioManager",
            "Scenario already registered, will replace: id=%{public}s",
            id.c_str());
        delete scenarios_[id];
    }

    scenarios_[id] = scenario;
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ScenarioManager",
        "Registered scenario: id=%{public}s, name=%{public}s",
        id.c_str(), scenario->GetName());
}

/**
 * @brief Gets the scenario associated with an instance
 * @param instanceId The instance ID to look up
 * @return Pointer to the scenario, or nullptr if not found
 */
ScenarioBase* ScenarioManager::GetScenario(const std::string& instanceId)
{
    // Find the scenario ID for this instance
    auto it = instanceScenarios_.find(instanceId);
    if (it != instanceScenarios_.end()) {
        const std::string& scenarioId = it->second;
        auto scenarioIt = scenarios_.find(scenarioId);
        if (scenarioIt != scenarios_.end()) {
            return scenarioIt->second;
        }

        OH_LOG_Print(LOG_APP, LOG_WARN, LOG_PRINT_DOMAIN, "ScenarioManager",
            "Scenario not found: scenarioId=%{public}s",
            scenarioId.c_str());
    } else {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_PRINT_DOMAIN, "ScenarioManager",
            "Instance not found in instanceScenarios: "
            "instanceId=%{public}s",
            instanceId.c_str());
    }

    // If not found, return the first scenario as default
    if (!scenarios_.empty()) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ScenarioManager",
            "Returning default scenario: %{public}s",
            scenarios_.begin()->first.c_str());
        return scenarios_.begin()->second;
    }

    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ScenarioManager",
        "No scenarios registered");
    return nullptr;
}

/**
 * @brief Sets the scenario for a specific instance
 * @param instanceId The instance ID
 * @param scenarioId The scenario ID to associate with the instance
 */
void ScenarioManager::SetScenarioForInstance(const std::string& instanceId,
    const std::string& scenarioId)
{
    // Check if scenario exists
    if (scenarios_.find(scenarioId) == scenarios_.end()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ScenarioManager",
            "Scenario not found: scenarioId=%{public}s",
            scenarioId.c_str());
        return;
    }

    // Record the mapping from instance to scenario
    instanceScenarios_[instanceId] = scenarioId;

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ScenarioManager",
        "Set instance %{public}s to scenario %{public}s",
        instanceId.c_str(), scenarioId.c_str());

    // Initialize the scenario (if not yet initialized)
    auto* scenario = scenarios_[scenarioId];
    if (scenario) {
        // Check if already initialized
        if (initializedScenarios_.find(scenarioId) ==
            initializedScenarios_.end() ||
            !initializedScenarios_[scenarioId]) {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ScenarioManager",
                "Initializing scenario: %{public}s (%{public}s",
                scenarioId.c_str(), scenario->GetName());
            scenario->Initialize();
            initializedScenarios_[scenarioId] = true;
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ScenarioManager",
                "Scenario initialized: %{public}s",
                scenarioId.c_str());
        } else {
            OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_PRINT_DOMAIN, "ScenarioManager",
                "Scenario already initialized: %{public}s",
                scenarioId.c_str());
        }
    }
}

/**
 * @brief Cleans up all scenarios and resources
 */
void ScenarioManager::Cleanup()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ScenarioManager",
        "Cleaning up %{public}zu scenarios", scenarios_.size());

    for (auto& pair : scenarios_) {
        if (pair.second) {
            pair.second->Cleanup();
            delete pair.second;
        }
    }

    scenarios_.clear();
    instanceScenarios_.clear();
    initializedScenarios_.clear();
}

} // namespace NativeXComponentSample
