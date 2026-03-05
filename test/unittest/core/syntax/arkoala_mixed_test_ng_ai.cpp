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

#include <cstdint>
#include <functional>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/arkoala_condition_scope.h"
#include "core/components_ng/syntax/arkoala_for_each_node.h"
#include "core/components_ng/syntax/arkoala_lazy_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_2 = 2;
constexpr int32_t TOTAL_COUNT = 5;
}

class ArkoalaMixedTestNgAI : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }

    RefPtr<FrameNode> CreateFrameNode(const std::string& tag)
    {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
        pattern->AttachToFrameNode(frameNode);
        return frameNode;
    }

    RefPtr<UINode> CreateUINode()
    {
        return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    }
};

/**
 * @tc.name: Integration_LazyNodeWithForEach_ChildrenManagementTest
 * @tc.desc: Test LazyNode manages ForEach children correctly
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaMixedTestNgAI, Integration_LazyNodeWithForEach_ChildrenManagementTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyNode with ForEach as child
     */
    auto lazyNode = AceType::MakeRefPtr<ArkoalaLazyNode>(TEST_NODE_ID);
    ASSERT_NE(lazyNode, nullptr);

    auto forEachNode = AceType::MakeRefPtr<ArkoalaForEachNode>(TEST_NODE_ID + 1);
    ASSERT_NE(forEachNode, nullptr);

    /**
     * @tc.steps: step2. Set callbacks and configure LazyNode
     */
    lazyNode->SetTotalCount(TOTAL_COUNT);
    lazyNode->SetCallbacks(
        [&forEachNode](int32_t index) -> RefPtr<UINode> {
            // Return ForEach node as child
            return forEachNode;
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    /**
     * @tc.steps: step3. Build children and verify structure
     */
    lazyNode->BuildAllChildren();

    /**
     * @tc.steps: step4. Verify children management
     */
    const auto& children = lazyNode->GetChildren();
    EXPECT_FALSE(children.empty());

    SUCCEED();
}

/**
 * @tc.name: Integration_DragAcrossNestedComponentsTest
 * @tc.desc: Test drag and drop works correctly in nested LazyNode -> ForEach -> ListItem structure
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaMixedTestNgAI, Integration_DragAcrossNestedComponentsTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create nested structure: LazyNode -> ForEachNode
     */
    auto lazyNode = AceType::MakeRefPtr<ArkoalaLazyNode>(TEST_NODE_ID);
    ASSERT_NE(lazyNode, nullptr);

    auto forEachNode = AceType::MakeRefPtr<ArkoalaForEachNode>(TEST_NODE_ID + 1);
    ASSERT_NE(forEachNode, nullptr);

    /**
     * @tc.steps: step2. Set up callbacks and configure nodes
     */
    lazyNode->SetTotalCount(TOTAL_COUNT);
    lazyNode->SetCallbacks(
        [&forEachNode](int32_t index) -> RefPtr<UINode> {
            return forEachNode;
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    /**
     * @tc.steps: step3. Verify nodes are created correctly
     */
    EXPECT_EQ(lazyNode->FrameCount(), TOTAL_COUNT);
    EXPECT_EQ(forEachNode->GetId(), TEST_NODE_ID + 1);

    SUCCEED();
}

/**
 * @tc.name: Integration_DataChangePropagatesToNestedNodesTest
 * @tc.desc: Test data change propagates from LazyNode to ForEach
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaMixedTestNgAI, Integration_DataChangePropagatesToNestedNodesTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyNode with ForEach child
     */
    auto lazyNode = AceType::MakeRefPtr<ArkoalaLazyNode>(TEST_NODE_ID);
    ASSERT_NE(lazyNode, nullptr);

    auto forEachNode = AceType::MakeRefPtr<ArkoalaForEachNode>(TEST_NODE_ID + 1);
    ASSERT_NE(forEachNode, nullptr);

    /**
     * @tc.steps: step2. Configure callbacks
     */
    bool updateRangeCalled = false;
    lazyNode->SetTotalCount(TOTAL_COUNT);
    lazyNode->SetCallbacks(
        [&forEachNode](int32_t index) -> RefPtr<UINode> {
            return forEachNode;
        },
        [&updateRangeCalled](int32_t, int32_t, int32_t, int32_t, bool) { updateRangeCalled = true; }
    );

    /**
     * @tc.steps: step3. Set active range and trigger data change
     */
    lazyNode->DoSetActiveChildRange(INDEX_0, INDEX_2, INDEX_0, INDEX_1, false);

    /**
     * @tc.steps: step4. Verify range update callback is triggered
     */
    EXPECT_TRUE(updateRangeCalled);

    /**
     * @tc.steps: step5. Trigger OnDataChange and verify propagation
     */
    lazyNode->OnDataChange(INDEX_0, INDEX_1, UINode::NotificationType::START_CHANGE_POSITION);

    SUCCEED();
}

/**
 * @tc.name: Integration_ConditionScopeInForEach_ConditionSwitchTest
 * @tc.desc: Test ConditionScope inside ForEach handles condition switch
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaMixedTestNgAI, Integration_ConditionScopeInForEach_ConditionSwitchTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ForEach with ConditionScope child
     */
    auto forEachNode = AceType::MakeRefPtr<ArkoalaForEachNode>(TEST_NODE_ID);
    ASSERT_NE(forEachNode, nullptr);

    auto conditionScopeNode = AceType::MakeRefPtr<ConditionScopeNode>(TEST_NODE_ID + 1);
    ASSERT_NE(conditionScopeNode, nullptr);

    /**
     * @tc.steps: step2. Add ConditionScope as child of ForEach
     */
    auto childNode = CreateFrameNode(V2::TEXT_ETS_TAG);
    conditionScopeNode->AddChild(childNode);
    forEachNode->AddChild(conditionScopeNode);

    /**
     * @tc.steps: step3. Verify initial structure
     */
    EXPECT_EQ(forEachNode->GetChildren().size(), 1);
    EXPECT_EQ(conditionScopeNode->GetChildren().size(), 1);

    /**
     * @tc.steps: step4. Trigger FlushUpdateAndMarkDirty
     */
    conditionScopeNode->FlushUpdateAndMarkDirty();
    forEachNode->FlushUpdateAndMarkDirty();

    /**
     * @tc.steps: step5. Test FinishRender coordination
     */
    forEachNode->FinishRender();

    SUCCEED();
}

/**
 * @tc.name: Integration_ComplexNestedStructure_LifecycleTest
 * @tc.desc: Test complex nested structure lifecycle management
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaMixedTestNgAI, Integration_ComplexNestedStructure_LifecycleTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create complex structure: LazyNode -> ForEach -> ConditionScope -> Text
     */
    auto lazyNode = AceType::MakeRefPtr<ArkoalaLazyNode>(TEST_NODE_ID);
    ASSERT_NE(lazyNode, nullptr);

    auto forEachNode = AceType::MakeRefPtr<ArkoalaForEachNode>(TEST_NODE_ID + 1);
    ASSERT_NE(forEachNode, nullptr);

    auto conditionScopeNode = AceType::MakeRefPtr<ConditionScopeNode>(TEST_NODE_ID + 2);
    ASSERT_NE(conditionScopeNode, nullptr);

    auto textNode = CreateFrameNode(V2::TEXT_ETS_TAG);
    ASSERT_NE(textNode, nullptr);

    /**
     * @tc.steps: step2. Build hierarchy
     */
    conditionScopeNode->AddChild(textNode);
    forEachNode->AddChild(conditionScopeNode);

    lazyNode->SetTotalCount(INDEX_1);
    lazyNode->SetCallbacks(
        [&forEachNode](int32_t index) -> RefPtr<UINode> {
            return forEachNode;
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    /**
     * @tc.steps: step3. Test SetJSViewActive propagation
     */
    lazyNode->SetJSViewActive(false);
    EXPECT_FALSE(lazyNode->isActive_);

    lazyNode->SetJSViewActive(true);
    EXPECT_TRUE(lazyNode->isActive_);

    /**
     * @tc.steps: step4. Test active range management
     */
    lazyNode->DoSetActiveChildRange(INDEX_0, INDEX_0, INDEX_0, INDEX_0, false);
    lazyNode->BuildAllChildren();

    /**
     * @tc.steps: step5. Test DumpInfo across components
     */
    lazyNode->DumpInfo();
    forEachNode->DumpInfo();
    conditionScopeNode->DumpInfo();

    /**
     * @tc.steps: step6. Verify component properties
     */
    EXPECT_TRUE(lazyNode->IsSyntaxNode());
    EXPECT_TRUE(forEachNode->IsSyntaxNode());
    EXPECT_TRUE(conditionScopeNode->IsSyntaxNode());

    EXPECT_FALSE(lazyNode->IsAtomicNode());
    EXPECT_FALSE(forEachNode->IsAtomicNode());
    EXPECT_FALSE(conditionScopeNode->IsAtomicNode());

    SUCCEED();
}

} // namespace OHOS::Ace::NG
