/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "ui/view_stack/view_stack_processor.h"

#include "gtest/gtest.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_pattern.h"
#include "ui/view_factory/abstract_view_factory.h"
#include "frameworks/core/components_ng/base/view_stack_model.h"
#include "frameworks/core/components_ng/base/view_stack_model_ng.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Kit;
using namespace OHOS::Ace::NG;

namespace OHOS::Ace {
ViewStackModel* ViewStackModel::GetInstance()
{
    static NG::ViewStackModelNG instance;
    return &instance;
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Kit {
class ViewStackProcessorTest : public testing::Test {};

/**
 * @tc.name: ViewStackProcessorTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTest, ViewStackProcessorTest001, TestSize.Level1)
{
    const std::string tag = "TEST";
    auto framenode = AbstractViewFactory::CreateFrameNode(tag, 0, AceType::MakeRefPtr<MockAceKitPattern>());
    EXPECT_NE(framenode, nullptr);
    ViewStackProcessor::Push(framenode);
    auto topNode = ViewStackProcessor::GetTopNode();
    EXPECT_EQ(topNode, framenode);
}

/**
 * @tc.name: ViewStackProcessorTest002
 * @tc.desc: Test NewScope method functionality
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTest, ViewStackProcessorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create first FrameNode
     * @tc.expected: step1. Node created successfully and not null
     */
    const std::string tag1 = "FIRST";
    auto node1 = AbstractViewFactory::CreateFrameNode(tag1, 0, AceType::MakeRefPtr<MockAceKitPattern>());
    EXPECT_NE(node1, nullptr);

    /**
     * @tc.steps: step2. Start first scope and push node
     * @tc.expected: step2. Finish returns correct node
     */
    ViewStackProcessor::NewScope();
    ViewStackProcessor::Push(node1);
    auto finish1 = ViewStackProcessor::Finish();
    EXPECT_EQ(finish1, node1);

    /**
     * @tc.steps: step3. Create second FrameNode
     * @tc.expected: step3. Node created successfully and not null
     */
    const std::string tag2 = "SECOND";
    auto node2 = AbstractViewFactory::CreateFrameNode(tag2, 0, AceType::MakeRefPtr<MockAceKitPattern>());
    EXPECT_NE(node2, nullptr);

    /**
     * @tc.steps: step4. Start second scope and push node
     * @tc.expected: step4. Finish returns new node different from first
     */
    ViewStackProcessor::NewScope();
    ViewStackProcessor::Push(node2);
    auto finish2 = ViewStackProcessor::Finish();

    EXPECT_EQ(finish2, node2);
    EXPECT_NE(finish2, finish1);
}

/**
 * @tc.name: ViewStackProcessorTest003
 * @tc.desc: Test single node build in NewScope
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTest, ViewStackProcessorTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Start new scope
     */
    ViewStackProcessor::NewScope();

    /**
     * @tc.steps: step2. Create and push FrameNode
     * @tc.expected: step2. Node created successfully
     */
    const std::string tag = "SINGLE_NODE";
    auto node = AbstractViewFactory::CreateFrameNode(tag, 0, AceType::MakeRefPtr<MockAceKitPattern>());
    ViewStackProcessor::Push(node);

    /**
     * @tc.steps: step3. Finish scope and get result
     * @tc.expected: step3. Returned node matches pushed node
     */
    auto result = ViewStackProcessor::Finish();
    EXPECT_EQ(result, node);
}

/**
 * @tc.name: ViewStackProcessorTest004
 * @tc.desc: Test nested scopes
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTest, ViewStackProcessorTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Start outer scope and push outer node
     */
    ViewStackProcessor::NewScope();
    const std::string outerTag = "OUTER";
    auto outerNode = AbstractViewFactory::CreateFrameNode(outerTag, 0, AceType::MakeRefPtr<MockAceKitPattern>());
    ViewStackProcessor::Push(outerNode);

    /**
     * @tc.steps: step2. Create and push inner node in nested scope
     * @tc.expected: step2. Inner scope finish returns correct inner node
     */
    ViewStackProcessor::NewScope();
    const std::string innerTag = "INNER";
    auto innerNode = AbstractViewFactory::CreateFrameNode(innerTag, 0, AceType::MakeRefPtr<MockAceKitPattern>());
    ViewStackProcessor::Push(innerNode);
    auto innerResult = ViewStackProcessor::Finish();
    EXPECT_EQ(innerResult, innerNode);

    /**
     * @tc.steps: step3. Finish outer scope
     * @tc.expected: step3. Returns outer node different from inner node
     */
    auto outerResult = ViewStackProcessor::Finish();
    EXPECT_EQ(outerResult, outerNode);
}

/**
• @tc.name: ViewStackProcessorTest005
• @tc.desc: Test Finish with FrameNode that already has kitNode
• @tc.type: FUNC
*/
HWTEST_F(ViewStackProcessorTest, ViewStackProcessorTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Start new scope
     */
    ViewStackProcessor::NewScope();

    /**
     * @tc.steps: step2. Create FrameNode with kitNode
     * @tc.expected: step2. Node created successfully
     */
    const std::string tag = "NORMAL_FRAME";
    auto node = AbstractViewFactory::CreateFrameNode(tag, 0, AceType::MakeRefPtr<MockAceKitPattern>());
    ASSERT_NE(node, nullptr);

    /**
     * @tc.steps: step3. Push node and record top node
     * @tc.expected: step3. Top node matches created node
     */
    ViewStackProcessor::Push(node);
    auto preTop = ViewStackProcessor::GetTopNode();

    /**
     * @tc.steps: step4. Finish scope
     * @tc.expected: step4. Returned node has same ID as created node
     */
    auto result = ViewStackProcessor::Finish();
    EXPECT_EQ(result, preTop);
    EXPECT_EQ(result->GetId(), node->GetId());
}
} // namespace OHOS::Ace::Kit
