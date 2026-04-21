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

#ifndef ACCESSIBILITY_CAPI_SCENARIO_MANAGER_H
#define ACCESSIBILITY_CAPI_SCENARIO_MANAGER_H

#include <map>
#include <string>
#include "ScenarioBase.h"
#include <hilog/log.h>

namespace NativeXComponentSample {

/**
 * @brief 场景管理器，单例模式
 *
 * 负责管理所有场景的注册、切换和查询
 * 支持多实例场景，不同XComponent可以使用不同的场景
 */
class ScenarioManager {
public:
    /**
     * @brief 获取单例实例
     * @return ScenarioManager实例引用
     */
    static ScenarioManager& GetInstance();

    /**
     * @brief 注册场景
     * @param id 场景ID
     * @param scenario 场景对象指针（Manager会接管所有权）
     */
    void RegisterScenario(const std::string& id, ScenarioBase* scenario);

    /**
     * @brief 根据instanceId获取场景（支持多实例）
     * @param instanceId 实例ID（XComponent的id）
     * @return 场景对象指针，找不到返回nullptr
     */
    ScenarioBase* GetScenario(const std::string& instanceId);

    /**
     * @brief 设置当前实例的场景
     * @param instanceId 实例ID
     * @param scenarioId 场景ID
     */
    void SetScenarioForInstance(const std::string& instanceId,
                                const std::string& scenarioId);

    /**
     * @brief 清理所有场景
     */
    void Cleanup();

    /**
     * @brief 获取所有已注册的场景
     * @return 场景ID到场景对象的映射
     */
    const std::map<std::string, ScenarioBase*>& GetAllScenarios() const
    {
        return scenarios_;
    }

private:
    ScenarioManager() = default;
    ~ScenarioManager();

    // 禁止拷贝
    ScenarioManager(const ScenarioManager&) = delete;
    ScenarioManager& operator=(const ScenarioManager&) = delete;

    std::map<std::string, ScenarioBase*> scenarios_;           // scenarioId -> Scenario
    std::map<std::string, std::string> instanceScenarios_;     // instanceId -> scenarioId
    std::map<std::string, bool> initializedScenarios_;         // scenarioId -> initialized
};

} // namespace NativeXComponentSample

#endif // ACCESSIBILITY_CAPI_SCENARIO_MANAGER_H
