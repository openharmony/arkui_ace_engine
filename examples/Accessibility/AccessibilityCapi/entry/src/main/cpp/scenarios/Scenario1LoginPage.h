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

#ifndef ACCESSIBILITY_CAPI_SCENARIO1_LOGIN_PAGE_H
#define ACCESSIBILITY_CAPI_SCENARIO1_LOGIN_PAGE_H

#include "ScenarioBase.h"
#include "fakenode/FakeTextField.h"
#include "fakenode/FakeCheckbox.h"
#include "fakenode/fake_node.h"
#include "fakenode/FakeCustomWidget.h"

namespace NativeXComponentSample {

/**
 * @brief 场景1：登录页面
 *
 * 演示基础属性、状态设置、焦点管理
 * 覆盖接口：19个
 * 测试用例：7个
 */
class Scenario1LoginPage : public ScenarioBase {
public:
    Scenario1LoginPage();
    ~Scenario1LoginPage() override;

    // 实现ScenarioBase接口
    const char* GetId() const override
    {
        return "scenario1_login";
    }

    const char* GetName() const override
    {
        return "登录页面";
    }

    const char* GetDescription() const override
    {
        return "演示基础属性、状态设置、焦点管理（19个接口）";
    }

    void Initialize() override;
    const std::vector<AccessibleObject*>& GetNodes() const override;
    AccessibleObject* GetRootNode() const override;
    AccessibleObject* GetNodeById(int64_t elementId) override;
    bool HandleAction(int64_t elementId, ArkUI_Accessibility_ActionType action) override;
    void Cleanup() override;

    int GetInterfaceCount() const override
    {
        return 19;
    }

    int GetTestCaseCount() const override
    {
        return 7;
    }

private:
    void CreateNodes();
    void ConfigureNodes();

    AccessibleObject* rootNode_ = nullptr;
    FakeTextField* usernameField_ = nullptr;
    FakeTextField* passwordField_ = nullptr;
    FakeCheckbox* rememberCheckbox_ = nullptr;
    FakeButton* loginButton_ = nullptr;
    FakeButton* cancelButton_ = nullptr;

    std::vector<AccessibleObject*> nodes_;
    int32_t nextElementId_ = 1;

    int32_t AllocateElementId()
    {
        return nextElementId_++;
    }
};

} // namespace NativeXComponentSample

#endif // ACCESSIBILITY_CAPI_SCENARIO1_LOGIN_PAGE_H
