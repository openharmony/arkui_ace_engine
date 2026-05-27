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

#include <any>
#include <string>

#include "gtest/gtest.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/with_env_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/environment_manager.h"

#define private public
#include "core/components_ng/syntax/with_env_node.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t WITH_ENV_NODE_ID = 100;
constexpr int32_t WITH_ENV_NODE_ID_ALT = 200;
const std::string CUSTOM_KEY_THEME = "app.theme";
const std::string CUSTOM_VALUE_DARK = "dark";
constexpr double CUSTOM_DOUBLE_VALUE = 3.14;
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
    auto pipeline = MockPipelineContext::GetCurrent();
    if (pipeline) {
        pipeline->environmentManager_ = AceType::MakeRefPtr<EnvironmentManager>();
    }
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
 * @tc.name: WithEnvSyntaxTest007
 * @tc.desc: SetCustomEnvProperty with std::any, then GetCustomEnvPropertyAny returns valid value.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest007, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetCustomEnvProperty(CUSTOM_KEY_THEME, std::any(CUSTOM_VALUE_DARK));

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->HasCustomEnvProperty(CUSTOM_KEY_THEME));

    auto anyValue = node->GetCustomEnvPropertyAny(CUSTOM_KEY_THEME);
    ASSERT_TRUE(anyValue.has_value());

    auto retrieved = std::any_cast<std::string>(*anyValue);
    EXPECT_EQ(retrieved, CUSTOM_VALUE_DARK);
}

/**
 * @tc.name: WithEnvSyntaxTest008
 * @tc.desc: GetCustomEnvPropertyAny returns nullopt for non-existent key.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvSyntaxTest008, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);

    auto anyValue = node->GetCustomEnvPropertyAny("non.existent.key");
    EXPECT_FALSE(anyValue.has_value());
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

    auto anyValue = node->GetCustomEnvPropertyAny(CUSTOM_KEY_THEME);
    ASSERT_TRUE(anyValue.has_value());

    auto retrieved = std::any_cast<double>(*anyValue);
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

    model.SetCustomEnvProperty(CUSTOM_KEY_THEME, std::any(CUSTOM_BOOL_VALUE));

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);

    auto anyValue = node->GetCustomEnvPropertyAny(CUSTOM_KEY_THEME);
    ASSERT_TRUE(anyValue.has_value());
    auto retrieved = std::any_cast<bool>(*anyValue);
    EXPECT_EQ(retrieved, CUSTOM_BOOL_VALUE);
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

    auto anyValue = node->GetCustomEnvPropertyAny(CUSTOM_KEY_THEME);
    ASSERT_TRUE(anyValue.has_value());
    auto retrieved = std::any_cast<std::string>(*anyValue);
    EXPECT_EQ(retrieved, "dark");
}

/**
 * @tc.name: WithEnvNodeSystemEnvProperty001
 * @tc.desc: SetSystemEnvProperty accepts direction values and rejects mismatched or unsupported system keys.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvNodeSystemEnvProperty001, TestSize.Level1)
{
    auto node = WithEnvNode::GetOrCreateWithEnvNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->SetSystemEnvProperty(ENV_KEY_DIRECTION, SystemEnvValue::FromDirection(TextDirection::RTL)));
    auto directionValue = node->GetSystemEnvProperty(ENV_KEY_DIRECTION);
    ASSERT_TRUE(directionValue.has_value());
    auto direction = directionValue->GetDirection();
    ASSERT_TRUE(direction.has_value());
    EXPECT_EQ(direction.value(), TextDirection::RTL);

    EXPECT_FALSE(node->SetSystemEnvProperty(ENV_KEY_DIRECTION, SystemEnvValue::FromDouble(1.0)));
    EXPECT_FALSE(
        node->SetSystemEnvProperty("arkui.test.unsupported", SystemEnvValue::FromDirection(TextDirection::LTR)));
}

/**
 * @tc.name: WithEnvModelSystemDirection001
 * @tc.desc: WithEnvModelNG sets system direction property on current WithEnvNode through EnvironmentManager.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvModelSystemDirection001, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetSystemEnvProperty(ENV_KEY_DIRECTION, TextDirection::RTL);

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);
    auto value = node->GetSystemEnvProperty(ENV_KEY_DIRECTION);
    ASSERT_TRUE(value.has_value());
    auto direction = value->GetDirection();
    ASSERT_TRUE(direction.has_value());
    EXPECT_EQ(direction.value(), TextDirection::RTL);
}

/**
 * @tc.name: WithEnvModelSystemDirectionInvalidKey001
 * @tc.desc: WithEnvModelNG ignores direction value when system key is unsupported.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvModelSystemDirectionInvalidKey001, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetSystemEnvProperty("arkui.test.unsupported", TextDirection::RTL);

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(node->HasSystemEnvProperty("arkui.test.unsupported"));
}

/**
 * @tc.name: WithEnvModelRemoveSystemEnvProperty001
 * @tc.desc: WithEnvModelNG removes an existing system direction property.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvModelRemoveSystemEnvProperty001, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetSystemEnvProperty(ENV_KEY_DIRECTION, TextDirection::LTR);
    model.RemoveSystemEnvProperty(ENV_KEY_DIRECTION);

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(node->HasSystemEnvProperty(ENV_KEY_DIRECTION));
}

/**
 * @tc.name: WithEnvModelRemoveCustomEnvProperty001
 * @tc.desc: WithEnvModelNG removes an existing custom env property.
 * @tc.type: FUNC
 */
HWTEST_F(WithEnvSyntaxTestNg, WithEnvModelRemoveCustomEnvProperty001, TestSize.Level1)
{
    WithEnvModelNG model;
    model.Create();

    model.SetCustomEnvProperty(CUSTOM_KEY_THEME, std::any(CUSTOM_VALUE_DARK));
    model.RemoveCustomEnvProperty(CUSTOM_KEY_THEME);

    auto node = AceType::DynamicCast<WithEnvNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(node->HasCustomEnvProperty(CUSTOM_KEY_THEME));
}

} // namespace OHOS::Ace::NG
