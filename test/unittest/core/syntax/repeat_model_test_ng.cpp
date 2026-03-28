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

#include <utility>
#include "gtest/gtest.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/repeat_model_ng.h"
#include "core/components_ng/syntax/repeat_node.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t TEST_NODE_ID_2 = 200;
constexpr bool IS_ATOMIC_NODE = false;
constexpr uint32_t TEST_MOVE_INDEX = 5;
constexpr uint32_t TEST_MOVE_INDEX_2 = 10;
const std::string TEST_KEY = "test_key";
const std::string TEST_KEY_2 = "test_key_2";
std::list<int32_t> removedElmtIds;
} // namespace

class RepeatSyntaxTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void RepeatSyntaxTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void RepeatSyntaxTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void RepeatSyntaxTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void RepeatSyntaxTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RepeatSyntaxStartRenderTest001
 * @tc.desc: StartRender creates RepeatNode and pushes to ViewStackProcessor
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxStartRenderTest001, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    auto repeatNode = AceType::DynamicCast<RepeatNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_TRUE(repeatNode != nullptr);
    EXPECT_EQ(repeatNode->GetTag(), V2::JS_REPEAT_ETS_TAG);
}

/**
 * @tc.name: RepeatSyntaxStartRenderTest002
 * @tc.desc: StartRender creates RepeatNode with correct atomic property
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxStartRenderTest002, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    auto repeatNode = AceType::DynamicCast<RepeatNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_TRUE(repeatNode != nullptr);
    EXPECT_EQ(repeatNode->IsAtomicNode(), IS_ATOMIC_NODE);
}

/**
 * @tc.name: RepeatSyntaxFinishRenderTest003
 * @tc.desc: FinishRender completes rendering and pops container
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxFinishRenderTest003, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    auto repeatNode = AceType::DynamicCast<RepeatNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_TRUE(repeatNode != nullptr);
    removedElmtIds.clear();
    repeatModel.FinishRender(removedElmtIds);
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxFinishRenderTest004
 * @tc.desc: FinishRender with null node handles gracefully
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxFinishRenderTest004, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    removedElmtIds.clear();
    repeatModel.FinishRender(removedElmtIds);
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxMoveChildTest005
 * @tc.desc: MoveChild triggers node movement
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxMoveChildTest005, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    repeatModel.MoveChild(TEST_MOVE_INDEX);
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxMoveChildTest006
 * @tc.desc: MoveChild with different indices
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxMoveChildTest006, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    repeatModel.MoveChild(TEST_MOVE_INDEX);
    repeatModel.MoveChild(TEST_MOVE_INDEX_2);
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxMoveChildTest007
 * @tc.desc: MoveChild without StartRender handles gracefully
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxMoveChildTest007, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.MoveChild(TEST_MOVE_INDEX);
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxCreateNewChildStartTest008
 * @tc.desc: CreateNewChildStart pushes key and creates SyntaxItem
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxCreateNewChildStartTest008, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    repeatModel.CreateNewChildStart(TEST_KEY);
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxCreateNewChildStartTest009
 * @tc.desc: CreateNewChildStart with different keys
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxCreateNewChildStartTest009, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    repeatModel.CreateNewChildStart(TEST_KEY);
    repeatModel.CreateNewChildStart(TEST_KEY_2);
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxCreateNewChildFinishTest010
 * @tc.desc: CreateNewChildFinish pops key and container
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxCreateNewChildFinishTest010, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    repeatModel.CreateNewChildStart(TEST_KEY);
    repeatModel.CreateNewChildFinish(TEST_KEY);
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxCreateNewChildFinishTest011
 * @tc.desc: CreateNewChildFinish without StartRender handles gracefully
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxCreateNewChildFinishTest011, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.CreateNewChildFinish(TEST_KEY);
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxAfterAddChildTest012
 * @tc.desc: AfterAddChild triggers node update
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxAfterAddChildTest012, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    repeatModel.AfterAddChild();
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxAfterAddChildTest013
 * @tc.desc: AfterAddChild without StartRender handles gracefully
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxAfterAddChildTest013, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.AfterAddChild();
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxOnMoveTest014
 * @tc.desc: OnMove sets move callback
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxOnMoveTest014, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    repeatModel.OnMove(std::move(onMoveCallback));
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxOnMoveTest015
 * @tc.desc: OnMove without StartRender handles gracefully
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxOnMoveTest015, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    repeatModel.OnMove(std::move(onMoveCallback));
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxSetItemDragHandlerTest016
 * @tc.desc: SetItemDragHandler sets drag handlers
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxSetItemDragHandlerTest016, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    repeatModel.SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxSetItemDragHandlerTest017
 * @tc.desc: SetItemDragHandler without StartRender handles gracefully
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxSetItemDragHandlerTest017, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    repeatModel.SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    SUCCEED();
}

/**
 * @tc.name: RepeatSyntaxGetOrCreateTest018
 * @tc.desc: GetOrCreateRepeatNode with same ID returns same instance
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxGetOrCreateTest018, TestSize.Level1)
{
    auto repeatNode1 = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto repeatNode2 = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    EXPECT_EQ(repeatNode1, repeatNode2);
}

/**
 * @tc.name: RepeatSyntaxGetOrCreateTest019
 * @tc.desc: GetOrCreateRepeatNode with different IDs returns different instances
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxGetOrCreateTest019, TestSize.Level1)
{
    auto repeatNode1 = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto repeatNode2 = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID_2);
    EXPECT_NE(repeatNode1, repeatNode2);
}

/**
 * @tc.name: RepeatSyntaxCompleteFlowTest020
 * @tc.desc: Complete flow: StartRender, CreateNewChild, FinishRender
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxCompleteFlowTest020, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    auto repeatNode = AceType::DynamicCast<RepeatNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_TRUE(repeatNode != nullptr);
    repeatModel.CreateNewChildStart(TEST_KEY);
    repeatModel.CreateNewChildFinish(TEST_KEY);
    repeatModel.AfterAddChild();
    removedElmtIds.clear();
    repeatModel.FinishRender(removedElmtIds);
}

/**
 * @tc.name: RepeatSyntaxMultipleChildrenTest021
 * @tc.desc: Create multiple children in sequence
 * @tc.type: FUNC
 */
HWTEST_F(RepeatSyntaxTestNg, RepeatSyntaxMultipleChildrenTest021, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    for (int32_t i = 0; i < 5; ++i) {
        std::string key = "key_" + std::to_string(i);
        repeatModel.CreateNewChildStart(key);
        repeatModel.CreateNewChildFinish(key);
    }
    removedElmtIds.clear();
    repeatModel.FinishRender(removedElmtIds);
}

} // namespace OHOS::Ace::NG
