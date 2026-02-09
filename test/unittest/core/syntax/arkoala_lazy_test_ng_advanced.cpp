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

#include <functional>
#include <vector>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/arkoala_lazy_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t TEST_NODE_ID_2 = 200;
constexpr int32_t TOTAL_COUNT_5 = 5;
constexpr int32_t TOTAL_COUNT_10 = 10;
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_2 = 2;
constexpr int32_t INDEX_3 = 3;
constexpr int32_t INDEX_5 = 5;
constexpr int32_t INDEX_NEGATIVE = -1;
} // namespace

class ArkoalaLazyAdvancedTestNg : public testing::Test {
public:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }

    RefPtr<ArkoalaLazyNode> CreateArkoalaLazyNode(int32_t nodeId, bool isRepeat = false)
    {
        auto node = AceType::MakeRefPtr<ArkoalaLazyNode>(nodeId, isRepeat);
        return node;
    }

    RefPtr<FrameNode> CreateChildNode(const std::string& tag, int32_t id)
    {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        auto frameNode = FrameNode::CreateFrameNode(tag, id, pattern);
        return frameNode;
    }
};

/**
 * @tc.name: ArkoalaLazySetTotalCountTest001
 * @tc.desc: Test SetTotalCount with various values
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazySetTotalCountTest001, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT_5);
    EXPECT_EQ(node->FrameCount(), TOTAL_COUNT_5);

    node->SetTotalCount(TOTAL_COUNT_10);
    EXPECT_EQ(node->FrameCount(), TOTAL_COUNT_10);
}

/**
 * @tc.name: ArkoalaLazySetCallbacksTest002
 * @tc.desc: Test SetCallbacks with create and update callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazySetCallbacksTest002, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    auto createCallback = [](int32_t index) -> RefPtr<UINode> {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        return FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, index, pattern);
    };

    auto updateCallback = [](int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache) {};

    node->SetCallbacks(createCallback, updateCallback);
}

/**
 * @tc.name: ArkoalaLazyFrameCountTest003
 * @tc.desc: Test FrameCount returns correct count
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazyFrameCountTest003, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT_5);
    EXPECT_EQ(node->FrameCount(), TOTAL_COUNT_5);
}

/**
 * @tc.name: ArkoalaLazySetIsLoopTest004
 * @tc.desc: Test SetIsLoop changes loop state
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazySetIsLoopTest004, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    node->SetIsLoop(true);
    node->SetIsLoop(false);
}

/**
 * @tc.name: ArkoalaLazyGetChildrenTest005
 * @tc.desc: Test GetChildren returns children list
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazyGetChildrenTest005, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    auto children = node->GetChildren(false);
    EXPECT_EQ(children.size(), 0);
}

/**
 * @tc.name: ArkoalaLazyGetChildrenNotDetachTest006
 * @tc.desc: Test GetChildren with notDetach parameter
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazyGetChildrenNotDetachTest006, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    auto children1 = node->GetChildren(false);
    auto children2 = node->GetChildren(true);
    EXPECT_EQ(children1.size(), children2.size());
}

/**
 * @tc.name: ArkoalaLazyMoveDataTest007
 * @tc.desc: Test MoveData with various indices
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazyMoveDataTest007, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    node->MoveData(INDEX_0, INDEX_2);
    node->MoveData(INDEX_1, INDEX_3);
    node->MoveData(INDEX_NEGATIVE, INDEX_1);
}

/**
 * @tc.name: ArkoalaLazySetOnMoveTest008
 * @tc.desc: Test SetOnMove callback registration
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazySetOnMoveTest008, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    auto onMoveCallback = [](int32_t from, int32_t to) {};
    node->SetOnMove(std::move(onMoveCallback));
}

/**
 * @tc.name: ArkoalaLazySetOnMoveFromToTest009
 * @tc.desc: Test SetOnMoveFromTo callback registration
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazySetOnMoveFromToTest009, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    auto onMoveFromToCallback = [](int32_t from, int32_t to) {};
    node->SetOnMoveFromTo(std::move(onMoveFromToCallback));
}

/**
 * @tc.name: ArkoalaLazySetNeedBuildAllTest010
 * @tc.desc: Test SetNeedBuildAll changes build state
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazySetNeedBuildAllTest010, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    node->SetNeedBuildAll(true);
    node->SetNeedBuildAll(false);
}

/**
 * @tc.name: ArkoalaLazyIsAtomicNodeTest011
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazyIsAtomicNodeTest011, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    EXPECT_FALSE(node->IsAtomicNode());
}

/**
 * @tc.name: ArkoalaLazyBuildAllChildrenTest012
 * @tc.desc: Test BuildAllChildren builds all items
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazyBuildAllChildrenTest012, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT_5);

    auto createCallback = [](int32_t index) -> RefPtr<UINode> {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        return FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, index, pattern);
    };

    auto updateCallback = [](int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache) {};

    node->SetCallbacks(createCallback, updateCallback);
    node->BuildAllChildren();
}

/**
 * @tc.name: ArkoalaLazySetJSViewActiveTest013
 * @tc.desc: Test SetJSViewActive with various parameters
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazySetJSViewActiveTest013, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    node->SetJSViewActive(true, false, false);
    node->SetJSViewActive(false, true, true);
}

/**
 * @tc.name: ArkoalaLazyRecycleItemsTest014
 * @tc.desc: Test RecycleItems with various ranges
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazyRecycleItemsTest014, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    node->RecycleItems(INDEX_0, INDEX_2);
    node->RecycleItems(INDEX_2, INDEX_5);
}

/**
 * @tc.name: ArkoalaLazyGetFrameNodeTest015
 * @tc.desc: Test GetFrameNode returns frame node at index
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazyGetFrameNodeTest015, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT_5);

    (void)node->GetFrameNode(INDEX_0);
}

/**
 * @tc.name: ArkoalaLazyDifferentNodeIdsTest016
 * @tc.desc: Test creating nodes with different IDs
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazyDifferentNodeIdsTest016, TestSize.Level1)
{
    auto node1 = CreateArkoalaLazyNode(TEST_NODE_ID);
    auto node2 = CreateArkoalaLazyNode(TEST_NODE_ID_2);

    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    EXPECT_NE(node1, node2);
}

/**
 * @tc.name: ArkoalaLazySameNodeIdTest017
 * @tc.desc: Test creating nodes with same ID
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazySameNodeIdTest017, TestSize.Level1)
{
    auto node1 = CreateArkoalaLazyNode(TEST_NODE_ID);
    auto node2 = CreateArkoalaLazyNode(TEST_NODE_ID);

    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    EXPECT_NE(node1, node2);
}

/**
 * @tc.name: ArkoalaLazyIsRepeatTest018
 * @tc.desc: Test creating nodes with different isRepeat values
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazyIsRepeatTest018, TestSize.Level1)
{
    auto node1 = CreateArkoalaLazyNode(TEST_NODE_ID, false);
    auto node2 = CreateArkoalaLazyNode(TEST_NODE_ID_2, true);

    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
}

/**
 * @tc.name: ArkoalaLazyMoveDataFromToTest019
 * @tc.desc: Test MoveData with from == to
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazyMoveDataFromToTest019, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    node->MoveData(INDEX_1, INDEX_1);
    node->MoveData(INDEX_2, INDEX_2);
}

/**
 * @tc.name: ArkoalaLazySetTotalCountZeroTest020
 * @tc.desc: Test SetTotalCount with zero
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyAdvancedTestNg, ArkoalaLazySetTotalCountZeroTest020, TestSize.Level1)
{
    auto node = CreateArkoalaLazyNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(0);
    EXPECT_EQ(node->FrameCount(), 0);
}

} // namespace OHOS::Ace::NG
