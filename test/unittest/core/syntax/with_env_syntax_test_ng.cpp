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

#include <string>

#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/with_env_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

#define private public
#include "core/components_ng/syntax/with_env_node.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t WITH_ENV_NODE_ID = 100;
constexpr int32_t WITH_ENV_NODE_ID_ALT = 200;
const std::string ENV_KEY_DIRECTION = "system.arkui.layout.direction";
const std::string ENV_VALUE_TRUE = "true";
const std::string ENV_VALUE_FALSE = "false";
const std::string CUSTOM_KEY_THEME = "app.theme";
const std::string CUSTOM_VALUE_DARK = "dark";
constexpr double CUSTOM_DOUBLE_VALUE = 3.14;
constexpr double CUSTOM_DOUBLE_INT_VALUE = 42.0;
constexpr bool CUSTOM_BOOL_VALUE = true;
constexpr bool IS_ATOMIC_NODE = false;
constexpr bool IS_SYNTAX_NODE = true;
} // namespace

class WithEnvSyntaxTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void WithEnvSyntaxTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "WithEnvSyntaxTestNg SetUpTestCase";
}

void WithEnvSyntaxTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "WithEnvSyntaxTestNg TearDownTestCase";
}

void WithEnvSyntaxTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void WithEnvSyntaxTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: WithEnvSyntaxTest001
 * @tc.desc: Create WithEnvNode through model and verify node properties.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest001, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    auto withEnvNode = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(withEnvNode, nullptr);
    EXPECT_EQ(withEnvNode->GetTag(), V2::JS_WITH_ENV_ETS_TAG);
    EXPECT_EQ(withEnvNode->IsAtomicNode(), IS_ATOMIC_NODE);
    EXPECT_EQ(withEnvNode->IsSyntaxNode(), IS_SYNTAX_NODE);
}

/**
 * @tc.name: WithEnvSyntaxTest002
 * @tc.desc: GetOrCreateWithEnvNode returns same node for same id.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest002, TestSize.Level1)
{
    auto node1 = WithEnvNode::GetOrCreateWithEnvNode(WITH_ENV_NODE_ID);
    auto node2 = WithEnvNode::GetOrCreateWithEnvNode(WITH_ENV_NODE_ID);
    EXPECT_EQ(node1, node2);
}

/**
 * @tc.name: WithEnvSyntaxTest003
 * @tc.desc: GetWithEnvNode returns nullptr for non-existent id, returns node after creation.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest003, TestSize.Level1)
{
    auto notFound = WithEnvNode::GetWithEnvNode(WITH_ENV_NODE_ID_ALT);
    EXPECT_EQ(notFound, nullptr);

    auto created = WithEnvNode::CreateWithEnvNode(WITH_ENV_NODE_ID_ALT);
    ASSERT_NE(created, nullptr);

    auto found = WithEnvNode::GetWithEnvNode(WITH_ENV_NODE_ID_ALT);
    EXPECT_EQ(found, created);
}

/**
 * @tc.name: WithEnvSyntaxTest004
 * @tc.desc: SetEnvProperty with string value and verify HasEnvProperty.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest004, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetEnvProperty(ENV_KEY_DIRECTION, ENV_VALUE_TRUE);

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->HasEnvProperty(ENV_KEY_DIRECTION));
    EXPECT_FALSE(node->HasEnvProperty("non.existent.key"));
}

/**
 * @tc.name: WithEnvSyntaxTest005
 * @tc.desc: SetEnvProperty with double value and verify HasEnvProperty.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest005, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetEnvProperty(CUSTOM_KEY_THEME, CUSTOM_DOUBLE_VALUE);

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->HasEnvProperty(CUSTOM_KEY_THEME));
}

/**
 * @tc.name: WithEnvSyntaxTest006
 * @tc.desc: SetEnvProperty with bool value and verify HasEnvProperty.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest006, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetEnvProperty(ENV_KEY_DIRECTION, CUSTOM_BOOL_VALUE);

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->HasEnvProperty(ENV_KEY_DIRECTION));
}

/**
 * @tc.name: WithEnvSyntaxTest007
 * @tc.desc: SetCustomEnvProperty with std::any, then GetCustomEnvPropertyAny returns valid pointer.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest007, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetCustomEnvProperty(CUSTOM_KEY_THEME, std::any(CUSTOM_VALUE_DARK));

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->HasEnvProperty(CUSTOM_KEY_THEME));

    auto* anyPtr = node->GetCustomEnvPropertyAny(CUSTOM_KEY_THEME);
    ASSERT_NE(anyPtr, nullptr);

    auto retrieved = std::any_cast<std::string>(*anyPtr);
    EXPECT_EQ(retrieved, CUSTOM_VALUE_DARK);
}

/**
 * @tc.name: WithEnvSyntaxTest008
 * @tc.desc: GetCustomEnvPropertyAny returns nullptr for non-existent key.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest008, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);

    auto* anyPtr = node->GetCustomEnvPropertyAny("non.existent.key");
    EXPECT_EQ(anyPtr, nullptr);
}

/**
 * @tc.name: WithEnvSyntaxTest009
 * @tc.desc: SetCustomEnvProperty with double stored as std::any, retrieve and cast back.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest009, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetCustomEnvProperty(CUSTOM_KEY_THEME, std::any(CUSTOM_DOUBLE_VALUE));

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);

    auto* anyPtr = node->GetCustomEnvPropertyAny(CUSTOM_KEY_THEME);
    ASSERT_NE(anyPtr, nullptr);

    auto retrieved = std::any_cast<double>(*anyPtr);
    EXPECT_DOUBLE_EQ(retrieved, CUSTOM_DOUBLE_VALUE);
}

/**
 * @tc.name: WithEnvSyntaxTest010
 * @tc.desc: SetCustomEnvProperty with bool stored as std::any, retrieve and cast back.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest010, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetCustomEnvProperty(ENV_KEY_DIRECTION, std::any(CUSTOM_BOOL_VALUE));

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);

    auto* anyPtr = node->GetCustomEnvPropertyAny(ENV_KEY_DIRECTION);
    ASSERT_NE(anyPtr, nullptr);
    auto retrieved = std::any_cast<bool>(*anyPtr);
    EXPECT_EQ(retrieved, CUSTOM_BOOL_VALUE);
}

/**
 * @tc.name: WithEnvSyntaxTest011
 * @tc.desc: HasEnvProperty returns false when no properties are set.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest011, TestSize.Level1)
{
    auto node = WithEnvNode::CreateWithEnvNode(WITH_ENV_NODE_ID);
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(node->HasEnvProperty(ENV_KEY_DIRECTION));
    EXPECT_FALSE(node->HasEnvProperty(CUSTOM_KEY_THEME));
}

/**
 * @tc.name: WithEnvSyntaxTest012
 * @tc.desc: SetCustomEnvProperty overwrites previous value for same key.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest012, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetCustomEnvProperty(CUSTOM_KEY_THEME, std::any(std::string("light")));
    model.SetCustomEnvProperty(CUSTOM_KEY_THEME, std::any(std::string("dark")));

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);

    auto* anyPtr = node->GetCustomEnvPropertyAny(CUSTOM_KEY_THEME);
    ASSERT_NE(anyPtr, nullptr);
    auto retrieved = std::any_cast<std::string>(*anyPtr);
    EXPECT_EQ(retrieved, "dark");
}

/**
 * @tc.name: WithEnvSyntaxTest013
 * @tc.desc: SetEnvProperty with double integer-like value stored correctly.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest013, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetEnvProperty(CUSTOM_KEY_THEME, CUSTOM_DOUBLE_INT_VALUE);

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);
    EXPECT_TRUE(node->HasEnvProperty(CUSTOM_KEY_THEME));

    auto* anyPtr = node->GetCustomEnvPropertyAny(CUSTOM_KEY_THEME);
    EXPECT_EQ(anyPtr, nullptr); // double goes to envPropertiesDoubleType_, not customEnvObjProperties_
}

/**
 * @tc.name: WithEnvSyntaxTest014
 * @tc.desc: ModelNG GetCustomEnvPropertyAny delegates to node correctly.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest014, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    auto* instance = WithEnvModel::GetInstance();
    ASSERT_NE(instance, nullptr);

    instance->SetCustomEnvProperty(CUSTOM_KEY_THEME, std::any(CUSTOM_VALUE_DARK));

    auto* anyPtr = instance->GetCustomEnvPropertyAny(CUSTOM_KEY_THEME);
    ASSERT_NE(anyPtr, nullptr);
    auto retrieved = std::any_cast<std::string>(*anyPtr);
    EXPECT_EQ(retrieved, CUSTOM_VALUE_DARK);

    // Non-existent key returns nullptr
    auto* notFound = instance->GetCustomEnvPropertyAny("non.existent.key");
    EXPECT_EQ(notFound, nullptr);

    ViewStackProcessor::GetInstance()->Finish();
}

} // namespace OHOS::Ace::NG
