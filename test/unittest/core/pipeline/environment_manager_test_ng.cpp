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
#include <string_view>

#include "core/components_ng/base/frame_node.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/with_env_node.h"
#include "core/pipeline_ng/environment_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace NG {
namespace {
const std::string CUSTOM_ENV_TEST_KEY = "arkui.test.custom.env";
const std::string CUSTOM_ENV_TEST_VALUE = "dark";
const std::string CUSTOM_ENV_TEST_VALUE_INNER = "light";
const std::string CUSTOM_ENV_TEST_VALUE_UPDATED = "blue";
constexpr char SYSTEM_ENV_DISPATCHER_FULL_KEY[] = "arkui.test.dispatcher.full";
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

void ExpectAnyString(const std::any& value, const std::string& expected)
{
    auto stringValue = std::any_cast<std::string>(&value);
    ASSERT_NE(stringValue, nullptr);
    EXPECT_EQ(*stringValue, expected);
}

void ExpectCustomReaderOwnedBy(const RefPtr<EnvironmentManager>& envManager, const RefPtr<UINode>& readerNode,
    const std::string& key, const RefPtr<WithEnvNode>& ownerScope)
{
    ASSERT_NE(envManager, nullptr);
    ASSERT_NE(readerNode, nullptr);
    auto readerIter = envManager->customExplicitReaders_.find(readerNode->GetId());
    ASSERT_NE(readerIter, envManager->customExplicitReaders_.end());
    auto registeredReader = readerIter->second.weak.Upgrade();
    EXPECT_EQ(AceType::RawPtr(registeredReader), AceType::RawPtr(readerNode));

    auto ownerIter = readerIter->second.ownerScopes.find(key);
    ASSERT_NE(ownerIter, readerIter->second.ownerScopes.end());
    auto registeredOwner = ownerIter->second.Upgrade();
    EXPECT_EQ(AceType::RawPtr(registeredOwner), AceType::RawPtr(ownerScope));

    if (!ownerScope) {
        return;
    }
    auto scopeIter = envManager->customExplicitScopes_.find(ownerScope->GetId());
    ASSERT_NE(scopeIter, envManager->customExplicitScopes_.end());
    auto registeredScope = scopeIter->second.weak.Upgrade();
    EXPECT_EQ(AceType::RawPtr(registeredScope), AceType::RawPtr(ownerScope));

    auto keyIter = scopeIter->second.readerIdsByKey.find(key);
    ASSERT_NE(keyIter, scopeIter->second.readerIdsByKey.end());
    EXPECT_EQ(keyIter->second.count(readerNode->GetId()), 1U);
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

    std::any queryResult;
    ASSERT_TRUE(envManager->FindCustomEnvValueByKey(customNode, CUSTOM_ENV_TEST_KEY, queryResult));
    ExpectAnyString(queryResult, CUSTOM_ENV_TEST_VALUE);

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
    EXPECT_FALSE(envManager->FindSystemEnvValueByKey(customNode, ENV_KEY_DIRECTION, queryResult));
    EXPECT_FALSE(withEnvNode->HasSystemEnvProperty(ENV_KEY_DIRECTION));

    EXPECT_TRUE(envManager->SetSystemEnvValue(
        withEnvNode, ENV_KEY_DIRECTION, SystemEnvValue::FromDirection(TextDirection::AUTO)));

    EXPECT_EQ(*callbackCount, 2);
    EXPECT_EQ(*receivedKey, ENV_KEY_DIRECTION);
    ASSERT_TRUE(receivedValue->has_value());
    auto direction = (*receivedValue)->GetDirection();
    ASSERT_TRUE(direction.has_value());
    EXPECT_EQ(direction.value(), TextDirection::AUTO);
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
 * @tc.name: EnvironmentManagerResolveOwnerScope001
 * @tc.desc: ResolveOwnerScope and ResolveCustomValue return the nearest WithEnv owner for a custom key.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerResolveOwnerScope001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto outerWithEnv = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(outerWithEnv, nullptr);
    outerWithEnv->SetCustomEnvProperty(CUSTOM_ENV_TEST_KEY, std::any(CUSTOM_ENV_TEST_VALUE));

    auto innerWithEnv = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(innerWithEnv, nullptr);
    outerWithEnv->AddChild(innerWithEnv);

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "customEnv");
    ASSERT_NE(customNode, nullptr);
    innerWithEnv->AddChild(customNode);

    auto ownerScope = envManager->ResolveOwnerScope(customNode, EnvironmentPropertyKind::CUSTOM, CUSTOM_ENV_TEST_KEY);
    EXPECT_EQ(AceType::RawPtr(ownerScope), AceType::RawPtr(outerWithEnv));
    auto customValue = envManager->ResolveCustomValue(customNode, CUSTOM_ENV_TEST_KEY);
    ASSERT_TRUE(customValue.has_value());
    ExpectAnyString(*customValue, CUSTOM_ENV_TEST_VALUE);

    innerWithEnv->SetCustomEnvProperty(CUSTOM_ENV_TEST_KEY, std::any(CUSTOM_ENV_TEST_VALUE_INNER));
    ownerScope = envManager->ResolveOwnerScope(customNode, EnvironmentPropertyKind::CUSTOM, CUSTOM_ENV_TEST_KEY);
    EXPECT_EQ(AceType::RawPtr(ownerScope), AceType::RawPtr(innerWithEnv));
    customValue = envManager->ResolveCustomValue(customNode, CUSTOM_ENV_TEST_KEY);
    ASSERT_TRUE(customValue.has_value());
    ExpectAnyString(*customValue, CUSTOM_ENV_TEST_VALUE_INNER);
}

/**
 * @tc.name: EnvironmentManagerExplicitReaderRegistry001
 * @tc.desc: RegisterExplicitCustomEnvReader records reader and owner scope indexes for a custom key.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerExplicitReaderRegistry001, TestSize.Level1)
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

    envManager->RegisterExplicitCustomEnvReader(customNode, CUSTOM_ENV_TEST_KEY);
    ExpectCustomReaderOwnedBy(envManager, customNode, CUSTOM_ENV_TEST_KEY, withEnvNode);

    envManager->RegisterExplicitCustomEnvReader(customNode, CUSTOM_ENV_TEST_KEY);
    auto scopeIter = envManager->customExplicitScopes_.find(withEnvNode->GetId());
    ASSERT_NE(scopeIter, envManager->customExplicitScopes_.end());
    EXPECT_EQ(scopeIter->second.readerIdsByKey[CUSTOM_ENV_TEST_KEY].count(customNode->GetId()), 1U);
}

/**
 * @tc.name: EnvironmentManagerSystemExplicitReaderRegistry001
 * @tc.desc: RegisterExplicitSystemEnvReader records reader and owner scope indexes for a system key.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerSystemExplicitReaderRegistry001, TestSize.Level1)
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

    envManager->RegisterExplicitSystemEnvReader(customNode, ENV_KEY_DIRECTION);
    auto readerIter = envManager->systemExplicitReaders_.find(customNode->GetId());
    ASSERT_NE(readerIter, envManager->systemExplicitReaders_.end());
    auto registeredReader = readerIter->second.weak.Upgrade();
    EXPECT_EQ(AceType::RawPtr(registeredReader), AceType::RawPtr(customNode));

    auto ownerIter = readerIter->second.ownerScopes.find(ENV_KEY_DIRECTION);
    ASSERT_NE(ownerIter, readerIter->second.ownerScopes.end());
    auto registeredOwner = ownerIter->second.Upgrade();
    EXPECT_EQ(AceType::RawPtr(registeredOwner), AceType::RawPtr(withEnvNode));

    auto scopeIter = envManager->systemExplicitScopes_.find(withEnvNode->GetId());
    ASSERT_NE(scopeIter, envManager->systemExplicitScopes_.end());
    auto keyIter = scopeIter->second.readerIdsByKey.find(ENV_KEY_DIRECTION);
    ASSERT_NE(keyIter, scopeIter->second.readerIdsByKey.end());
    EXPECT_EQ(keyIter->second.count(customNode->GetId()), 1U);
}

/**
 * @tc.name: EnvironmentManagerRebindExplicitEnvReader001
 * @tc.desc: RebindExplicitEnvReader moves a reader from the old owner scope to a nearer owner scope.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerRebindExplicitEnvReader001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto outerWithEnv = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(outerWithEnv, nullptr);
    outerWithEnv->SetCustomEnvProperty(CUSTOM_ENV_TEST_KEY, std::any(CUSTOM_ENV_TEST_VALUE));

    auto innerWithEnv = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(innerWithEnv, nullptr);
    outerWithEnv->AddChild(innerWithEnv);

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "customEnv");
    ASSERT_NE(customNode, nullptr);
    innerWithEnv->AddChild(customNode);

    envManager->RegisterExplicitCustomEnvReader(customNode, CUSTOM_ENV_TEST_KEY);
    ExpectCustomReaderOwnedBy(envManager, customNode, CUSTOM_ENV_TEST_KEY, outerWithEnv);

    innerWithEnv->SetCustomEnvProperty(CUSTOM_ENV_TEST_KEY, std::any(CUSTOM_ENV_TEST_VALUE_INNER));
    EXPECT_TRUE(envManager->RebindExplicitEnvReader(envManager->customExplicitReaders_,
        envManager->customExplicitScopes_, customNode, EnvironmentPropertyKind::CUSTOM, CUSTOM_ENV_TEST_KEY));

    EXPECT_EQ(envManager->customExplicitScopes_.find(outerWithEnv->GetId()), envManager->customExplicitScopes_.end());
    ExpectCustomReaderOwnedBy(envManager, customNode, CUSTOM_ENV_TEST_KEY, innerWithEnv);
    EXPECT_FALSE(envManager->RebindExplicitEnvReader(envManager->customExplicitReaders_,
        envManager->customExplicitScopes_, customNode, EnvironmentPropertyKind::CUSTOM, CUSTOM_ENV_TEST_KEY));
}

/**
 * @tc.name: EnvironmentManagerRebindExplicitReadersUnderScope001
 * @tc.desc: RebindExplicitReadersUnderScope rebinds a missing reader when a scope starts defining the key.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerRebindExplicitReadersUnderScope001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(withEnvNode, nullptr);
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "customEnv");
    ASSERT_NE(customNode, nullptr);
    withEnvNode->AddChild(customNode);

    envManager->RegisterExplicitCustomEnvReader(customNode, CUSTOM_ENV_TEST_KEY);
    ExpectCustomReaderOwnedBy(envManager, customNode, CUSTOM_ENV_TEST_KEY, nullptr);
    EXPECT_EQ(envManager->customExplicitScopes_.find(withEnvNode->GetId()), envManager->customExplicitScopes_.end());

    auto callbackCount = std::make_shared<int32_t>(0);
    auto receivedValue = std::make_shared<std::optional<std::any>>();
    customNode->SetOnCustomEnvUpdateFunc(
        [callbackCount, receivedValue](const std::string&, const std::optional<std::any>& value) {
            ++(*callbackCount);
            *receivedValue = value;
        });

    withEnvNode->SetCustomEnvProperty(CUSTOM_ENV_TEST_KEY, std::any(CUSTOM_ENV_TEST_VALUE));
    EnvironmentManager::ChangedEnvValue changedValue;
    changedValue.customValue.emplace(std::any(CUSTOM_ENV_TEST_VALUE));
    envManager->RebindExplicitReadersUnderScope(envManager->customExplicitReaders_, envManager->customExplicitScopes_,
        withEnvNode, EnvironmentPropertyKind::CUSTOM, CUSTOM_ENV_TEST_KEY, changedValue);

    ExpectCustomReaderOwnedBy(envManager, customNode, CUSTOM_ENV_TEST_KEY, withEnvNode);
    EXPECT_EQ(*callbackCount, 1);
    ASSERT_TRUE(receivedValue->has_value());
    ExpectAnyString(receivedValue->value(), CUSTOM_ENV_TEST_VALUE);
    ClearCustomEnvUpdateFunc(customNode);
}

/**
 * @tc.name: EnvironmentManagerNotifyExplicitReadersOwnedByScope001
 * @tc.desc: NotifyExplicitReadersOwnedByScope dispatches only registered readers for the owner scope.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerNotifyExplicitReadersOwnedByScope001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(withEnvNode, nullptr);
    withEnvNode->SetCustomEnvProperty(CUSTOM_ENV_TEST_KEY, std::any(CUSTOM_ENV_TEST_VALUE));

    auto registeredNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "customEnv");
    ASSERT_NE(registeredNode, nullptr);
    auto unregisteredNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "customEnv");
    ASSERT_NE(unregisteredNode, nullptr);
    withEnvNode->AddChild(registeredNode);
    withEnvNode->AddChild(unregisteredNode);

    envManager->RegisterExplicitCustomEnvReader(registeredNode, CUSTOM_ENV_TEST_KEY);

    auto registeredCount = std::make_shared<int32_t>(0);
    auto unregisteredCount = std::make_shared<int32_t>(0);
    auto receivedValue = std::make_shared<std::optional<std::any>>();
    registeredNode->SetOnCustomEnvUpdateFunc(
        [registeredCount, receivedValue](const std::string&, const std::optional<std::any>& value) {
            ++(*registeredCount);
            *receivedValue = value;
        });
    unregisteredNode->SetOnCustomEnvUpdateFunc(
        [unregisteredCount](const std::string&, const std::optional<std::any>&) {
            ++(*unregisteredCount);
        });

    EnvironmentManager::ChangedEnvValue changedValue;
    changedValue.customValue.emplace(std::any(CUSTOM_ENV_TEST_VALUE_UPDATED));
    envManager->NotifyExplicitReadersOwnedByScope(envManager->customExplicitReaders_, envManager->customExplicitScopes_,
        withEnvNode, EnvironmentPropertyKind::CUSTOM, CUSTOM_ENV_TEST_KEY, changedValue);

    EXPECT_EQ(*registeredCount, 1);
    EXPECT_EQ(*unregisteredCount, 0);
    ASSERT_TRUE(receivedValue->has_value());
    ExpectAnyString(receivedValue->value(), CUSTOM_ENV_TEST_VALUE_UPDATED);
    ClearCustomEnvUpdateFunc(registeredNode);
    ClearCustomEnvUpdateFunc(unregisteredNode);
}

/**
 * @tc.name: EnvironmentManagerNotifyImplicitSystemEnvChanged001
 * @tc.desc: NotifyImplicitSystemEnvChanged dispatches FULL handlers and leaves PRECISE as no-op.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerNotifyImplicitSystemEnvChanged001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(withEnvNode, nullptr);
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "systemEnv");
    ASSERT_NE(customNode, nullptr);
    withEnvNode->AddChild(customNode);

    g_systemEnvDispatchCount = 0;
    g_lastSystemEnvDispatchKey.clear();
    envManager->RegisterSystemEnvHandler(
        { SYSTEM_ENV_DISPATCHER_FULL_KEY, SystemEnvImplicitNotifyMode::FULL, &TestSystemEnvDispatchCallback });
    envManager->NotifyImplicitSystemEnvChanged(withEnvNode, SYSTEM_ENV_DISPATCHER_FULL_KEY,
        EnvironmentManager::EnvironmentValueChangeType::UPDATE);

    EXPECT_EQ(g_systemEnvDispatchCount, 1);
    EXPECT_EQ(g_lastSystemEnvDispatchKey, SYSTEM_ENV_DISPATCHER_FULL_KEY);

    g_systemEnvDispatchCount = 0;
    g_lastSystemEnvDispatchKey.clear();
    envManager->RegisterSystemEnvHandler(
        { SYSTEM_ENV_DISPATCHER_TEST_KEY, SystemEnvImplicitNotifyMode::PRECISE, &TestSystemEnvDispatchCallback });
    envManager->NotifyImplicitSystemEnvChanged(withEnvNode, SYSTEM_ENV_DISPATCHER_TEST_KEY,
        EnvironmentManager::EnvironmentValueChangeType::UPDATE);

    EXPECT_EQ(g_systemEnvDispatchCount, 0);
    EXPECT_TRUE(g_lastSystemEnvDispatchKey.empty());
}

/**
 * @tc.name: EnvironmentManagerCustomEnvRebindOnAdd001
 * @tc.desc: Adding a nearer WithEnv value rebinds existing explicit reader and ignores later outer updates.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerCustomEnvRebindOnAdd001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto outerWithEnv = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(outerWithEnv, nullptr);
    outerWithEnv->SetCustomEnvProperty(CUSTOM_ENV_TEST_KEY, std::any(CUSTOM_ENV_TEST_VALUE));

    auto innerWithEnv = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(innerWithEnv, nullptr);
    outerWithEnv->AddChild(innerWithEnv);

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "customEnv");
    ASSERT_NE(customNode, nullptr);
    innerWithEnv->AddChild(customNode);

    std::any queryResult;
    ASSERT_TRUE(envManager->FindCustomEnvValueByKey(customNode, CUSTOM_ENV_TEST_KEY, queryResult));
    ExpectAnyString(queryResult, CUSTOM_ENV_TEST_VALUE);

    auto callbackCount = std::make_shared<int32_t>(0);
    auto receivedValue = std::make_shared<std::optional<std::any>>();
    customNode->SetOnCustomEnvUpdateFunc(
        [callbackCount, receivedValue](const std::string&, const std::optional<std::any>& value) {
            ++(*callbackCount);
            *receivedValue = value;
        });

    EXPECT_TRUE(envManager->SetCustomEnvValue(innerWithEnv, CUSTOM_ENV_TEST_KEY,
        std::any(CUSTOM_ENV_TEST_VALUE_INNER)));

    EXPECT_EQ(*callbackCount, 1);
    ASSERT_TRUE(receivedValue->has_value());
    ExpectAnyString(receivedValue->value(), CUSTOM_ENV_TEST_VALUE_INNER);

    ASSERT_TRUE(envManager->FindCustomEnvValueByKey(customNode, CUSTOM_ENV_TEST_KEY, queryResult));
    ExpectAnyString(queryResult, CUSTOM_ENV_TEST_VALUE_INNER);

    *callbackCount = 0;
    receivedValue->reset();
    EXPECT_TRUE(envManager->SetCustomEnvValue(outerWithEnv, CUSTOM_ENV_TEST_KEY,
        std::any(CUSTOM_ENV_TEST_VALUE_UPDATED)));

    EXPECT_EQ(*callbackCount, 0);
    EXPECT_FALSE(receivedValue->has_value());
    ClearCustomEnvUpdateFunc(customNode);
}

/**
 * @tc.name: EnvironmentManagerCustomEnvRebindOnRemove001
 * @tc.desc: Removing an inner WithEnv value rebinds explicit reader back to the outer owner scope.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, EnvironmentManagerCustomEnvRebindOnRemove001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto outerWithEnv = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(outerWithEnv, nullptr);
    outerWithEnv->SetCustomEnvProperty(CUSTOM_ENV_TEST_KEY, std::any(CUSTOM_ENV_TEST_VALUE));

    auto innerWithEnv = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(innerWithEnv, nullptr);
    innerWithEnv->SetCustomEnvProperty(CUSTOM_ENV_TEST_KEY, std::any(CUSTOM_ENV_TEST_VALUE_INNER));
    outerWithEnv->AddChild(innerWithEnv);

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "customEnv");
    ASSERT_NE(customNode, nullptr);
    innerWithEnv->AddChild(customNode);

    std::any queryResult;
    ASSERT_TRUE(envManager->FindCustomEnvValueByKey(customNode, CUSTOM_ENV_TEST_KEY, queryResult));
    ExpectAnyString(queryResult, CUSTOM_ENV_TEST_VALUE_INNER);

    auto callbackCount = std::make_shared<int32_t>(0);
    auto receivedValue = std::make_shared<std::optional<std::any>>(
        std::any(CUSTOM_ENV_TEST_VALUE_INNER));
    customNode->SetOnCustomEnvUpdateFunc(
        [callbackCount, receivedValue](const std::string&, const std::optional<std::any>& value) {
            ++(*callbackCount);
            *receivedValue = value;
        });

    EXPECT_TRUE(envManager->RemoveCustomEnvValue(innerWithEnv, CUSTOM_ENV_TEST_KEY));

    EXPECT_EQ(*callbackCount, 1);
    EXPECT_FALSE(receivedValue->has_value());
    ASSERT_TRUE(envManager->FindCustomEnvValueByKey(customNode, CUSTOM_ENV_TEST_KEY, queryResult));
    ExpectAnyString(queryResult, CUSTOM_ENV_TEST_VALUE);

    *callbackCount = 0;
    receivedValue->reset();
    EXPECT_TRUE(envManager->SetCustomEnvValue(outerWithEnv, CUSTOM_ENV_TEST_KEY,
        std::any(CUSTOM_ENV_TEST_VALUE_UPDATED)));

    EXPECT_EQ(*callbackCount, 1);
    ASSERT_TRUE(receivedValue->has_value());
    ExpectAnyString(receivedValue->value(), CUSTOM_ENV_TEST_VALUE_UPDATED);
    ClearCustomEnvUpdateFunc(customNode);
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

    EXPECT_EQ(envManager->GetSystemEnvImplicitNotifyMode(SYSTEM_ENV_DISPATCHER_UNREGISTERED_KEY),
        SystemEnvImplicitNotifyMode::NONE);
    envManager->RegisterSystemEnvHandler(
        { SYSTEM_ENV_DISPATCHER_TEST_KEY, SystemEnvImplicitNotifyMode::PRECISE, &TestSystemEnvDispatchCallback });
    EXPECT_EQ(envManager->GetSystemEnvImplicitNotifyMode(SYSTEM_ENV_DISPATCHER_TEST_KEY),
        SystemEnvImplicitNotifyMode::PRECISE);
    auto handler = envManager->FindSystemEnvHandler(SYSTEM_ENV_DISPATCHER_TEST_KEY);
    ASSERT_NE(handler, nullptr);
    EXPECT_EQ(handler->key, std::string_view(SYSTEM_ENV_DISPATCHER_TEST_KEY));
    EXPECT_EQ(handler->implicitNotifyMode, SystemEnvImplicitNotifyMode::PRECISE);
    EXPECT_EQ(handler->dispatchImplicit, &TestSystemEnvDispatchCallback);

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "dispatcher");
    ASSERT_NE(customNode, nullptr);
    SystemEnvDispatchContext dispatchContext { *envManager, customNode, nullptr, SYSTEM_ENV_DISPATCHER_TEST_KEY };
    envManager->DispatchImplicitSystemEnvChanged(dispatchContext);

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

    envManager->RegisterSystemEnvHandler({ "", SystemEnvImplicitNotifyMode::FULL, &TestSystemEnvDispatchCallback });
    EXPECT_EQ(envManager->GetSystemEnvImplicitNotifyMode(""), SystemEnvImplicitNotifyMode::NONE);

    envManager->RegisterSystemEnvHandler(
        { SYSTEM_ENV_DISPATCHER_NO_CALLBACK_KEY, SystemEnvImplicitNotifyMode::FULL, nullptr });
    EXPECT_EQ(envManager->GetSystemEnvImplicitNotifyMode(SYSTEM_ENV_DISPATCHER_NO_CALLBACK_KEY),
        SystemEnvImplicitNotifyMode::FULL);

    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "dispatcher");
    ASSERT_NE(customNode, nullptr);
    SystemEnvDispatchContext dispatchContext {
        *envManager, customNode, nullptr, SYSTEM_ENV_DISPATCHER_NO_CALLBACK_KEY
    };
    envManager->DispatchImplicitSystemEnvChanged(dispatchContext);

    EXPECT_EQ(g_systemEnvDispatchCount, 0);
    EXPECT_TRUE(g_lastSystemEnvDispatchKey.empty());
}

} // namespace NG
} // namespace OHOS::Ace
