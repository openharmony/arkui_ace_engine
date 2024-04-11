/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define protected public
#define private public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/tool_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
    constexpr Color FRONT_COLOR = Color(0xff0000ff);
} // namespace
class ToolBarTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<NavToolbarPattern> toolBarPattern_;
    RefPtr<NavToolbarNode> toolBarNode_;
};

void ToolBarTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void ToolBarTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void ToolBarTestNg::SetUp()
{
    toolBarPattern_ = AceType::MakeRefPtr<NavToolbarPattern>();
    toolBarNode_ = AceType::MakeRefPtr<NavToolbarNode>("tag", 1);
}

void ToolBarTestNg::TearDown()
{
    toolBarPattern_ = nullptr;
    toolBarNode_ = nullptr;
}

/**
 * @tc.name: ToolBarPatternTest001
 * @tc.desc: Test the CreateLayoutAlgorithm and IsAtomicNode function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test the CreateLayoutAlgorithm function.
     * @tc.expected: result is not empty.
     */
    auto result = toolBarPattern_->CreateLayoutAlgorithm();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step2. Test the IsAtomicNode function.
     * @tc.expected: result is false.
     */
    auto atomicNode = toolBarPattern_->IsAtomicNode();
    EXPECT_FALSE(atomicNode);
}

/**
 * @tc.name: ToolbarNodeTest001
 * @tc.desc: Test the SetToolbarContainerNode, GetToolbarContainerNode and IsAtomicNode function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolbarNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test the SetToolbarContainerNode and GetToolbarContainerNode function.
     * @tc.expected: result is empty.
     */
    RefPtr<UINode> customNode = nullptr;
    toolBarNode_->SetToolbarContainerNode(customNode);
    auto result = toolBarNode_->GetToolbarContainerNode();
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps: step2. Test the IsAtomicNode function.
     * @tc.expected: result is false.
     */
    auto atomicNode = toolBarNode_->IsAtomicNode();
    EXPECT_FALSE(atomicNode);
}

/**
 * @tc.name: ToolbarNodeTest002
 * @tc.desc: Test the GetOrCreateToolbarNode function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolbarNodeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialization.
     */
    std::string tag = "tag";
    int32_t nodeId = 1;
    std::function<RefPtr<Pattern>(void)> patternCreator;

    /**
     * @tc.steps: step2. Test the GetOrCreateToolbarNode function.
     * @tc.expected: result is not empty.
     */
    auto result = toolBarNode_->GetOrCreateToolbarNode(tag, nodeId, patternCreator);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: ToolBarPatternTest002
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest002, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest003
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest003, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.bgOptions.color = std::make_optional(FRONT_COLOR);
    opt.bgOptions.blurStyle = std::make_optional(BlurStyle::NO_MATERIAL);
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest004
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest004, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.bgOptions.blurStyle = std::make_optional(BlurStyle::NO_MATERIAL);
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest005
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest005, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.bgOptions.color = std::make_optional(FRONT_COLOR);
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest006
 * @tc.desc: Test the SetDefaultBackgroundColorIfNeeded function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest006, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    navToolbarPattern->options_.bgOptions.color = std::make_optional(FRONT_COLOR);
    navToolbarPattern->SetDefaultBackgroundColorIfNeeded(frameNode);
}
} // namespace OHOS::Ace::NG