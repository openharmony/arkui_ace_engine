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

#ifndef ACCESSIBILITY_CAPI_SCENARIO_BASE_H
#define ACCESSIBILITY_CAPI_SCENARIO_BASE_H

#include <string>
#include <vector>
#include "fakenode/fake_node.h"

namespace NativeXComponentSample {

/**
 * @brief 场景基类，所有场景都需要继承此类
 *
 * 每个场景代表一个独立的无障碍节点集合，用于演示特定的Native接口
 */
class ScenarioBase {
public:
    virtual ~ScenarioBase() = default;

    /**
     * @brief 获取场景ID（唯一标识符）
     * @return 场景ID字符串
     */
    virtual const char* GetId() const = 0;

    /**
     * @brief 获取场景名称
     * @return 场景名称字符串
     */
    virtual const char* GetName() const = 0;

    /**
     * @brief 获取场景描述
     * @return 场景描述字符串
     */
    virtual const char* GetDescription() const = 0;

    /**
     * @brief 初始化场景，创建所有节点
     */
    virtual void Initialize() = 0;

    /**
     * @brief 获取场景的所有节点
     * @return 节点列表
     */
    virtual const std::vector<AccessibleObject*>& GetNodes() const = 0;

    /**
     * @brief 获取根节点
     * @return 根节点指针
     */
    virtual AccessibleObject* GetRootNode() const = 0;

    /**
     * @brief 根据元素ID获取节点
     * @param elementId 元素ID
     * @return 节点指针，找不到返回nullptr
     */
    virtual AccessibleObject* GetNodeById(int64_t elementId) = 0;

    /**
     * @brief 处理无障碍操作
     * @param elementId 元素ID
     * @param action 操作类型
     * @return 是否成功处理
     */
    virtual bool HandleAction(int64_t elementId,
                             ArkUI_Accessibility_ActionType action) = 0;

    /**
     * @brief 清理资源
     */
    virtual void Cleanup() = 0;

    /**
     * @brief 获取覆盖的接口数量
     * @return 接口数量
     */
    virtual int GetInterfaceCount() const = 0;

    /**
     * @brief 获取测试用例数量
     * @return 用例数量
     */
    virtual int GetTestCaseCount() const = 0;
};

} // namespace NativeXComponentSample

#endif // ACCESSIBILITY_CAPI_SCENARIO_BASE_H
