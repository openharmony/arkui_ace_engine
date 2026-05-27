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

#include "test/unittest/core/pipeline/pipeline_context_test_ng.h"

#include <any>
#include <functional>
#include <memory>
#include <optional>
#include <string>

#include "core/components/common/layout/constants.h"
#include "core/components_ng/manager/environment/system_env_dispatcher.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/syntax/with_env_node.h"
#include "core/pipeline_ng/environment_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace NG {
namespace {
const std::string CUSTOM_ENV_TEST_KEY = "arkui.test.custom.env";
const std::string CUSTOM_ENV_TEST_VALUE = "dark";
constexpr char SYSTEM_ENV_DISPATCHER_TEST_KEY[] = "arkui.test.dispatcher.precise";
constexpr char SYSTEM_ENV_DISPATCHER_NO_CALLBACK_KEY[] = "arkui.test.dispatcher.no_callback";
constexpr char SYSTEM_ENV_DISPATCHER_UNREGISTERED_KEY[] = "arkui.test.dispatcher.unregistered";

using CustomEnvUpdateFunc = std::function<void(const std::string&, const std::optional<std::any>&)>;
using SystemEnvUpdateFunc = std::function<void(const std::string&, const std::optional<SystemEnvValue>&)>;

int32_t g_systemEnvDispatchCount = 0;
std::string g_lastSystemEnvDispatchKey;

void TestSystemEnvDispatchCallback(const SystemEnvDispatchContext& context)
{
    ++g_systemEnvDispatchCount;
    g_lastSystemEnvDispatchKey = std::string(context.key);
}

void ClearCustomEnvUpdateFunc(const RefPtr<CustomNode>& customNode)
{
    ASSERT_NE(customNode, nullptr);
    customNode->SetOnCustomEnvUpdateFunc(CustomEnvUpdateFunc());
}

void ClearSystemEnvUpdateFunc(const RefPtr<CustomNode>& customNode)
{
    ASSERT_NE(customNode, nullptr);
    customNode->SetOnSystemEnvUpdateFunc(SystemEnvUpdateFunc());
}
} // namespace

/**
 * @tc.name: EnvironmentManagerCustomEnvRemovedValue001
 * @tc.desc: RemoveCustomEnvValue dispatches empty value to affected CustomNode callback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerCustomEnvRemovedValue001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(withEnvNode, nullptr);
    withEnvNode->SetCustomEnvProperty(CUSTOM_ENV_TEST_KEY, std::any(CUSTOM_ENV_TEST_VALUE));

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "customEnv");
    ASSERT_NE(customNode, nullptr);
    withEnvNode->AddChild(customNode);

    auto callbackCount = std::make_shared<int32_t>(0);
    auto receivedKey = std::make_shared<std::string>();
    auto receivedValue = std::make_shared<std::optional<std::any>>(std::any(CUSTOM_ENV_TEST_VALUE));
    customNode->SetOnCustomEnvUpdateFunc(
        [callbackCount, receivedKey, receivedValue](const std::string& key, const std::optional<std::any>& value) {
            ++(*callbackCount);
            *receivedKey = key;
            *receivedValue = value;
        });

    EXPECT_TRUE(envManager->RemoveCustomEnvValue(withEnvNode, CUSTOM_ENV_TEST_KEY));

    EXPECT_EQ(*callbackCount, 1);
    EXPECT_EQ(*receivedKey, CUSTOM_ENV_TEST_KEY);
    EXPECT_FALSE(receivedValue->has_value());
    EXPECT_FALSE(withEnvNode->HasCustomEnvProperty(CUSTOM_ENV_TEST_KEY));
    ClearCustomEnvUpdateFunc(customNode);
}

/**
 * @tc.name: EnvironmentManagerSystemEnvChangedValue001
 * @tc.desc: SetSystemEnvValue dispatches changed direction value to dependent CustomNode callback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerSystemEnvChangedValue001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(withEnvNode, nullptr);
    ASSERT_TRUE(
        withEnvNode->SetSystemEnvProperty(ENV_KEY_DIRECTION, SystemEnvValue::FromDirection(TextDirection::LTR)));

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "systemEnv");
    ASSERT_NE(customNode, nullptr);
    withEnvNode->AddChild(customNode);

    SystemEnvValue queryResult;
    ASSERT_TRUE(envManager->FindSystemEnvValueByKey(customNode, ENV_KEY_DIRECTION, queryResult));
    ASSERT_TRUE(queryResult.GetDirection().has_value());
    EXPECT_EQ(queryResult.GetDirection().value(), TextDirection::LTR);

    auto callbackCount = std::make_shared<int32_t>(0);
    auto receivedKey = std::make_shared<std::string>();
    auto receivedValue = std::make_shared<std::optional<SystemEnvValue>>();
    customNode->SetOnSystemEnvUpdateFunc(
        [callbackCount, receivedKey, receivedValue](
            const std::string& key, const std::optional<SystemEnvValue>& value) {
            ++(*callbackCount);
            *receivedKey = key;
            *receivedValue = value;
        });

    EXPECT_TRUE(envManager->SetSystemEnvValue(
        withEnvNode, ENV_KEY_DIRECTION, SystemEnvValue::FromDirection(TextDirection::RTL)));

    EXPECT_EQ(*callbackCount, 1);
    EXPECT_EQ(*receivedKey, ENV_KEY_DIRECTION);
    ASSERT_TRUE(receivedValue->has_value());
    auto direction = (*receivedValue)->GetDirection();
    ASSERT_TRUE(direction.has_value());
    EXPECT_EQ(direction.value(), TextDirection::RTL);
    ClearSystemEnvUpdateFunc(customNode);
}

/**
 * @tc.name: EnvironmentManagerSystemEnvRemovedValue001
 * @tc.desc: RemoveSystemEnvValue dispatches empty value to dependent CustomNode callback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerSystemEnvRemovedValue001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(withEnvNode, nullptr);
    ASSERT_TRUE(
        withEnvNode->SetSystemEnvProperty(ENV_KEY_DIRECTION, SystemEnvValue::FromDirection(TextDirection::LTR)));

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "systemEnv");
    ASSERT_NE(customNode, nullptr);
    withEnvNode->AddChild(customNode);

    SystemEnvValue queryResult;
    ASSERT_TRUE(envManager->FindSystemEnvValueByKey(customNode, ENV_KEY_DIRECTION, queryResult));

    auto callbackCount = std::make_shared<int32_t>(0);
    auto receivedKey = std::make_shared<std::string>();
    auto receivedValue = std::make_shared<std::optional<SystemEnvValue>>(
        SystemEnvValue::FromDirection(TextDirection::LTR));
    customNode->SetOnSystemEnvUpdateFunc(
        [callbackCount, receivedKey, receivedValue](
            const std::string& key, const std::optional<SystemEnvValue>& value) {
            ++(*callbackCount);
            *receivedKey = key;
            *receivedValue = value;
        });

    EXPECT_TRUE(envManager->RemoveSystemEnvValue(withEnvNode, ENV_KEY_DIRECTION));

    EXPECT_EQ(*callbackCount, 1);
    EXPECT_EQ(*receivedKey, ENV_KEY_DIRECTION);
    EXPECT_FALSE(receivedValue->has_value());
    EXPECT_FALSE(withEnvNode->HasSystemEnvProperty(ENV_KEY_DIRECTION));
    ClearSystemEnvUpdateFunc(customNode);
}

/**
 * @tc.name: EnvironmentManagerSystemEnvInnerScope001
 * @tc.desc: Outer WithEnv updates do not cross inner WithEnv scope defining the same system key.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerSystemEnvInnerScope001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto outerWithEnv = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(outerWithEnv, nullptr);
    ASSERT_TRUE(
        outerWithEnv->SetSystemEnvProperty(ENV_KEY_DIRECTION, SystemEnvValue::FromDirection(TextDirection::LTR)));

    auto innerWithEnv = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(innerWithEnv, nullptr);
    ASSERT_TRUE(
        innerWithEnv->SetSystemEnvProperty(ENV_KEY_DIRECTION, SystemEnvValue::FromDirection(TextDirection::RTL)));
    outerWithEnv->AddChild(innerWithEnv);

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "systemEnv");
    ASSERT_NE(customNode, nullptr);
    innerWithEnv->AddChild(customNode);

    SystemEnvValue queryResult;
    ASSERT_TRUE(envManager->FindSystemEnvValueByKey(customNode, ENV_KEY_DIRECTION, queryResult));
    auto direction = queryResult.GetDirection();
    ASSERT_TRUE(direction.has_value());
    EXPECT_EQ(direction.value(), TextDirection::RTL);

    auto callbackCount = std::make_shared<int32_t>(0);
    customNode->SetOnSystemEnvUpdateFunc([callbackCount](const std::string&, const std::optional<SystemEnvValue>&) {
        ++(*callbackCount);
    });

    EXPECT_TRUE(envManager->SetSystemEnvValue(
        outerWithEnv, ENV_KEY_DIRECTION, SystemEnvValue::FromDirection(TextDirection::AUTO)));

    EXPECT_EQ(*callbackCount, 0);
    ClearSystemEnvUpdateFunc(customNode);
}

/**
 * @tc.name: EnvironmentManagerSystemEnvDispatcher001
 * @tc.desc: RegisterSystemEnvHandler stores notify mode and dispatches through registered callback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerSystemEnvDispatcher001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    g_systemEnvDispatchCount = 0;
    g_lastSystemEnvDispatchKey.clear();

    EXPECT_EQ(
        GetSystemEnvImplicitNotifyMode(SYSTEM_ENV_DISPATCHER_UNREGISTERED_KEY), SystemEnvImplicitNotifyMode::NONE);
    RegisterSystemEnvHandler(
        { SYSTEM_ENV_DISPATCHER_TEST_KEY, SystemEnvImplicitNotifyMode::PRECISE, &TestSystemEnvDispatchCallback });
    EXPECT_EQ(GetSystemEnvImplicitNotifyMode(SYSTEM_ENV_DISPATCHER_TEST_KEY), SystemEnvImplicitNotifyMode::PRECISE);

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "dispatcher");
    ASSERT_NE(customNode, nullptr);
    SystemEnvDispatchContext dispatchContext { *envManager, customNode, nullptr, SYSTEM_ENV_DISPATCHER_TEST_KEY };
    DispatchImplicitSystemEnvChanged(dispatchContext);

    EXPECT_EQ(g_systemEnvDispatchCount, 1);
    EXPECT_EQ(g_lastSystemEnvDispatchKey, SYSTEM_ENV_DISPATCHER_TEST_KEY);
}

/**
 * @tc.name: EnvironmentManagerSystemEnvDispatcher002
 * @tc.desc: RegisterSystemEnvHandler ignores empty keys and skips dispatch when callback is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerSystemEnvDispatcher002, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    g_systemEnvDispatchCount = 0;
    g_lastSystemEnvDispatchKey.clear();

    RegisterSystemEnvHandler({ "", SystemEnvImplicitNotifyMode::FULL, &TestSystemEnvDispatchCallback });
    EXPECT_EQ(GetSystemEnvImplicitNotifyMode(""), SystemEnvImplicitNotifyMode::NONE);

    RegisterSystemEnvHandler({ SYSTEM_ENV_DISPATCHER_NO_CALLBACK_KEY, SystemEnvImplicitNotifyMode::FULL, nullptr });
    EXPECT_EQ(GetSystemEnvImplicitNotifyMode(SYSTEM_ENV_DISPATCHER_NO_CALLBACK_KEY), SystemEnvImplicitNotifyMode::FULL);

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "dispatcher");
    ASSERT_NE(customNode, nullptr);
    SystemEnvDispatchContext dispatchContext {
        *envManager, customNode, nullptr, SYSTEM_ENV_DISPATCHER_NO_CALLBACK_KEY
    };
    DispatchImplicitSystemEnvChanged(dispatchContext);

    EXPECT_EQ(g_systemEnvDispatchCount, 0);
    EXPECT_TRUE(g_lastSystemEnvDispatchKey.empty());
}

} // namespace NG
} // namespace OHOS::Ace
