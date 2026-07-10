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

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/with_env_node.h"
#include "core/pipeline_ng/environment_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace NG {

namespace {

class TestableLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(TestableLayoutProperty, LayoutProperty);

public:
    bool NeedReadFontScaleFromEnv() const override
    {
        return true;
    }
};

class TestablePattern : public Pattern {
    DECLARE_ACE_TYPE(TestablePattern, Pattern);

public:
    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TestableLayoutProperty>();
    }
};

} // namespace

/**
 * @tc.name: GetEnvFontScaleLazyRead001
 * @tc.desc: GetEnvFontScale returns nullopt when no WithEnv ancestor exists
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, GetEnvFontScaleLazyRead001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode("test", nodeId, AceType::MakeRefPtr<TestablePattern>());
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TestableLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto envFontScale = layoutProperty->GetEnvFontScale();
    EXPECT_FALSE(envFontScale.has_value());

    frameNode = nullptr;
}

/**
 * @tc.name: GetEnvFontScaleLazyRead002
 * @tc.desc: GetEnvFontScale returns the value when WithEnv ancestor defines fontScale
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, GetEnvFontScaleLazyRead002, TestSize.Level1)
{
    auto envNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(envNodeId);
    ASSERT_NE(withEnvNode, nullptr);
    withEnvNode->SetSystemEnvProperty(ENV_KEY_FONT_SCALE, SystemEnvValue::FromDouble(2.5));

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode("test", nodeId, AceType::MakeRefPtr<TestablePattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->SetParent(withEnvNode);

    auto layoutProperty = frameNode->GetLayoutProperty<TestableLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto envFontScale = layoutProperty->GetEnvFontScale();
    ASSERT_TRUE(envFontScale.has_value());
    EXPECT_FLOAT_EQ(envFontScale.value(), 2.5f);

    frameNode = nullptr;
}

/**
 * @tc.name: LayoutFontScaleEnvCallback001
 * @tc.desc: fontScale handler marks layout property dirty and lazy getter resolves updated value
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, LayoutFontScaleEnvCallback001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto envManager = context_->GetEnvironmentManager();
    ASSERT_NE(envManager, nullptr);

    auto envNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(envNodeId);
    ASSERT_NE(withEnvNode, nullptr);
    withEnvNode->SetSystemEnvProperty(ENV_KEY_FONT_SCALE, SystemEnvValue::FromDouble(1.0));

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode("test", nodeId, AceType::MakeRefPtr<TestablePattern>());
    ASSERT_NE(frameNode, nullptr);
    withEnvNode->AddChild(frameNode);

    auto layoutProperty = frameNode->GetLayoutProperty<TestableLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto initialEnvFontScale = layoutProperty->GetEnvFontScale();
    ASSERT_TRUE(initialEnvFontScale.has_value());
    EXPECT_FLOAT_EQ(initialEnvFontScale.value(), 1.0f);

    ASSERT_TRUE(envManager->SetSystemEnvValue(withEnvNode, ENV_KEY_FONT_SCALE, SystemEnvValue::FromDouble(1.5)));

    auto envFontScale = layoutProperty->GetEnvFontScale();
    ASSERT_TRUE(envFontScale.has_value());
    EXPECT_FLOAT_EQ(envFontScale.value(), 1.5f);

    frameNode = nullptr;
}

/**
 * @tc.name: OnModifyDoneNoReadFontScale001
 * @tc.desc: OnModifyDone does NOT trigger auto-read of fontScale (performance regression prevention)
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, OnModifyDoneNoReadFontScale001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode("test", nodeId, AceType::MakeRefPtr<TestablePattern>());
    ASSERT_NE(frameNode, nullptr);

    auto envNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(envNodeId);
    ASSERT_NE(withEnvNode, nullptr);
    withEnvNode->SetSystemEnvProperty(ENV_KEY_FONT_SCALE, SystemEnvValue::FromDouble(4.0));
    withEnvNode->AddChild(frameNode);

    auto pattern = frameNode->GetPattern<TestablePattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TestableLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    pattern->OnModifyDone();

    withEnvNode->SetSystemEnvProperty(ENV_KEY_FONT_SCALE, SystemEnvValue::FromDouble(4.0));

    auto envFontScaleAfter = layoutProperty->GetEnvFontScale();
    ASSERT_TRUE(envFontScaleAfter.has_value());
    EXPECT_FLOAT_EQ(envFontScaleAfter.value(), 4.0f);

    frameNode = nullptr;
}

/**
 * @tc.name: GetFontScaleFromEnvFallback001
 * @tc.desc: GetFontScaleFromEnv returns system fontScale when envFontScale is nullopt
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, GetFontScaleFromEnvFallback001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    float systemFontScale = 1.25f;
    context_->SetFontScale(systemFontScale);

    float result = context_->GetFontScaleFromEnv(nullptr);
    EXPECT_FLOAT_EQ(result, systemFontScale);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode("test", nodeId, AceType::MakeRefPtr<TestablePattern>());
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TestableLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetEnvFontScale().has_value());

    result = context_->GetFontScaleFromEnv(frameNode);
    EXPECT_FLOAT_EQ(result, systemFontScale);

    frameNode = nullptr;
}

/**
 * @tc.name: GetFontScaleFromEnvWithEnvValue001
 * @tc.desc: GetFontScaleFromEnv returns env fontScale when envFontScale has value
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, GetFontScaleFromEnvWithEnvValue001, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    float systemFontScale = 1.0f;
    context_->SetFontScale(systemFontScale);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode("test", nodeId, AceType::MakeRefPtr<TestablePattern>());
    ASSERT_NE(frameNode, nullptr);

    auto envNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(envNodeId);
    ASSERT_NE(withEnvNode, nullptr);
    withEnvNode->SetSystemEnvProperty(ENV_KEY_FONT_SCALE, SystemEnvValue::FromDouble(2.0));
    withEnvNode->AddChild(frameNode);

    auto layoutProperty = frameNode->GetLayoutProperty<TestableLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto envFontScale = layoutProperty->GetEnvFontScale();
    ASSERT_TRUE(envFontScale.has_value());
    EXPECT_FLOAT_EQ(envFontScale.value(), 2.0f);

    float result = context_->GetFontScaleFromEnv(frameNode);
    EXPECT_FLOAT_EQ(result, 2.0f);

    frameNode = nullptr;
}

} // namespace NG
} // namespace OHOS::Ace
