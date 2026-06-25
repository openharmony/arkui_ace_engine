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
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/arkoala_lazy_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_2 = 2;
constexpr int32_t INDEX_3 = 3;
constexpr int32_t INDEX_4 = 4;
constexpr int32_t INDEX_5 = 5;
constexpr int32_t INDEX_6 = 6;
constexpr int32_t INDEX_7 = 7;
constexpr int32_t INDEX_8 = 8;
constexpr int32_t INDEX_9 = 9;
constexpr int32_t INDEX_10 = 10;
constexpr int32_t INVALID_INDEX = -1;
constexpr int32_t TOTAL_COUNT = 10;

void SetCallbacksForTest(const RefPtr<ArkoalaLazyNode>& node, ArkoalaLazyNode::CreateItemCb create,
    ArkoalaLazyNode::UpdateRangeCb update)
{
    node->SetCallbacks(create, update, []() {}, [](int32_t) {});
}

class NonFrameTestNode : public UINode {
public:
    NonFrameTestNode() : UINode("non_frame", -1) {}
    ~NonFrameTestNode() override = default;
    bool IsAtomicNode() const override
    {
        return false;
    }
};
}

class ArkoalaLazyTestNgAI : public testing::Test {
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

    RefPtr<ArkoalaLazyNode> CreateLazyNode(bool isRepeat = false)
    {
        return AceType::MakeRefPtr<ArkoalaLazyNode>(TEST_NODE_ID, isRepeat);
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
 * @tc.name: Constructor_BasicTest
 * @tc.desc: Test ArkoalaLazyNode constructor initializes correctly
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, Constructor_BasicTest, TestSize.Level1)
{
    auto node = CreateLazyNode(false);
    ASSERT_NE(node, nullptr);

    EXPECT_EQ(node->GetId(), TEST_NODE_ID);
    EXPECT_EQ(node->GetTag(), V2::JS_LAZY_FOR_EACH_ETS_TAG);
    EXPECT_FALSE(node->isRepeat_);
    EXPECT_TRUE(node->isActive_);
    EXPECT_EQ(node->totalCount_, 0);
}

/**
 * @tc.name: Constructor_RepeatNodeTest
 * @tc.desc: Test ArkoalaLazyNode constructor with isRepeat=true
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, Constructor_RepeatNodeTest, TestSize.Level1)
{
    auto node = CreateLazyNode(true);
    ASSERT_NE(node, nullptr);

    EXPECT_EQ(node->GetTag(), V2::JS_REPEAT_ETS_TAG);
    EXPECT_TRUE(node->isRepeat_);
}

/**
 * @tc.name: IsAtomicNode_ReturnsFalseTest
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, IsAtomicNode_ReturnsFalseTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    EXPECT_FALSE(node->IsAtomicNode());
}

/**
 * @tc.name: IsSyntaxNode_ReturnsTrueTest
 * @tc.desc: Test IsSyntaxNode returns true
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, IsSyntaxNode_ReturnsTrueTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->IsSyntaxNode());
}

/**
 * @tc.name: FrameCount_ReturnsTotalCountTest
 * @tc.desc: Test FrameCount returns totalCount
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, FrameCount_ReturnsTotalCountTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);
    EXPECT_EQ(node->FrameCount(), TOTAL_COUNT);
}

/**
 * @tc.name: SetTotalCount_UpdatesCountTest
 * @tc.desc: Test SetTotalCount updates total count
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, SetTotalCount_UpdatesCountTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);
    EXPECT_EQ(node->totalCount_, TOTAL_COUNT);

    node->SetTotalCount(INDEX_0);
    EXPECT_EQ(node->totalCount_, INDEX_0);
}

/**
 * @tc.name: SetCallbacks_SetsCallbacksTest
 * @tc.desc: Test SetCallbacks sets createItem and updateRange callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, SetCallbacks_SetsCallbacksTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    bool createItemCalled = false;
    bool updateRangeCalled = false;

    ArkoalaLazyNode::CreateItemCb createCb = [&createItemCalled](int32_t) -> RefPtr<UINode> {
        createItemCalled = true;
        return nullptr;
    };

    ArkoalaLazyNode::UpdateRangeCb updateCb = [&updateRangeCalled](int32_t, int32_t, int32_t, int32_t, bool) {
        updateRangeCalled = true;
    };

    SetCallbacksForTest(node, std::move(createCb), std::move(updateCb));

    EXPECT_NE(node->createItem_, nullptr);
    EXPECT_NE(node->updateRange_, nullptr);
}

/**
 * @tc.name: SetIsLoop_UpdatesLoopFlagTest
 * @tc.desc: Test SetIsLoop updates loop flag
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, SetIsLoop_UpdatesLoopFlagTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    EXPECT_FALSE(node->isLoop_);

    node->SetIsLoop(true);
    EXPECT_TRUE(node->isLoop_);

    node->SetIsLoop(false);
    EXPECT_FALSE(node->isLoop_);
}

/**
 * @tc.name: SetJSViewActive_SetsActiveTest
 * @tc.desc: Test SetJSViewActive sets active state
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, SetJSViewActive_SetsActiveTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->isActive_);

    node->SetJSViewActive(false);
    EXPECT_FALSE(node->isActive_);

    node->SetJSViewActive(true);
    EXPECT_TRUE(node->isActive_);
}

/**
 * @tc.name: DoSetActiveChildRange_SetsRangeTest
 * @tc.desc: Test DoSetActiveChildRange sets active range
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, DoSetActiveChildRange_SetsRangeTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);
    SetCallbacksForTest(node, [](int32_t) { return nullptr; }, [](int32_t, int32_t, int32_t, int32_t, bool) {});

    node->DoSetActiveChildRange(INDEX_0, INDEX_2, INDEX_0, INDEX_1, false);

    EXPECT_EQ(node->activeRangeParam_.start, INDEX_0);
    EXPECT_EQ(node->activeRangeParam_.end, INDEX_2);
}

/**
 * @tc.name: DoSetActiveChildRange_SameRangeTest
 * @tc.desc: Test DoSetActiveChildRange returns early for same range
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, DoSetActiveChildRange_SameRangeTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node, [](int32_t) { return nullptr; }, [](int32_t, int32_t, int32_t, int32_t, bool) {});

    node->DoSetActiveChildRange(INDEX_0, INDEX_2, INDEX_0, INDEX_0, false);

    // Same range should not trigger update
    node->DoSetActiveChildRange(INDEX_0, INDEX_2, INDEX_0, INDEX_0, false);

    EXPECT_EQ(node->activeRangeParam_.start, INDEX_0);
    EXPECT_EQ(node->activeRangeParam_.end, INDEX_2);
}

/**
 * @tc.name: DoSetActiveChildRange_WithShowCacheTest
 * @tc.desc: Test DoSetActiveChildRange with showCache=true expands range
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, DoSetActiveChildRange_WithShowCacheTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node, [](int32_t) { return nullptr; }, [](int32_t, int32_t, int32_t, int32_t, bool) {});

    node->DoSetActiveChildRange(INDEX_1, INDEX_2, INDEX_0, INDEX_1, true);

    EXPECT_EQ(node->activeRangeParam_.start, INDEX_1);
    EXPECT_EQ(node->activeRangeParam_.end, INDEX_3);
}

/**
 * @tc.name: SetOnMove_SetsCallbackTest
 * @tc.desc: Test SetOnMove sets the onMove callback
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, SetOnMove_SetsCallbackTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    bool onMoveCalled = false;
    node->SetOnMove([&onMoveCalled](int32_t, int32_t) { onMoveCalled = true; });

    EXPECT_NE(node->onMoveEvent_, nullptr);
}

/**
 * @tc.name: SetOnMoveFromTo_SetsCallbackTest
 * @tc.desc: Test SetOnMoveFromTo sets the onMoveFromTo callback
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, SetOnMoveFromTo_SetsCallbackTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    bool callbackCalled = false;
    node->SetOnMoveFromTo([&callbackCalled](int32_t, int32_t) { callbackCalled = true; });

    EXPECT_NE(node->onMoveFromTo_, nullptr);
}

/**
 * @tc.name: SetItemDragEvent_SetsHandlersTest
 * @tc.desc: Test SetItemDragEvent sets drag handlers
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, SetItemDragEvent_SetsHandlersTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->onMoveEvent_ = [](int32_t, int32_t) {};

    node->SetItemDragEvent([](int32_t) {}, [](int32_t) {}, [](int32_t, int32_t) {}, [](int32_t) {});

    EXPECT_NE(node->onLongPressEvent_, nullptr);
    EXPECT_NE(node->onDragStartEvent_, nullptr);
    EXPECT_NE(node->onMoveThroughEvent_, nullptr);
    EXPECT_NE(node->onDropEvent_, nullptr);
}

/**
 * @tc.name: MoveData_ReordersItemsTest
 * @tc.desc: Test MoveData updates moveFromTo_
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, MoveData_ReordersItemsTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->MoveData(INDEX_0, INDEX_1);

    EXPECT_FALSE(node->moveFromTo_.has_value());
}

/**
 * @tc.name: MoveData_SameIndexTest
 * @tc.desc: Test MoveData with same index
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, MoveData_SameIndexTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->MoveData(INDEX_0, INDEX_0);

    EXPECT_FALSE(node->moveFromTo_.has_value());
}

/**
 * @tc.name: ResetMoveFromTo_ClearsDataTest
 * @tc.desc: Test ResetMoveFromTo clears moveFromTo_
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, ResetMoveFromTo_ClearsDataTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->moveFromTo_ = std::make_pair(INDEX_0, INDEX_1);
    EXPECT_TRUE(node->moveFromTo_.has_value());

    node->ResetMoveFromTo();
    EXPECT_FALSE(node->moveFromTo_.has_value());
}

/**
 * @tc.name: ConvertFromToIndex_ConvertsTest
 * @tc.desc: Test ConvertFromToIndex converts index correctly
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, ConvertFromToIndex_ConvertsTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    // Without moveFromTo_, should return same index
    auto result = node->ConvertFromToIndex(INDEX_1);
    EXPECT_EQ(result, INDEX_1);
}

/**
 * @tc.name: ConvertFromToIndexRevert_RevertsTest
 * @tc.desc: Test ConvertFromToIndexRevert reverts index correctly
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, ConvertFromToIndexRevert_RevertsTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    // Without moveFromTo_, should return same index
    auto result = node->ConvertFromToIndexRevert(INDEX_1);
    EXPECT_EQ(result, INDEX_1);
}

/**
 * @tc.name: IsInActiveRange_ChecksRangeTest
 * @tc.desc: Test IsInActiveRange checks if index is in active range
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, IsInActiveRange_ChecksRangeTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    ActiveRangeParam param = { INDEX_0, INDEX_2, INDEX_0, INDEX_0 };

    EXPECT_TRUE(node->IsInActiveRange(INDEX_0, param));
    EXPECT_TRUE(node->IsInActiveRange(INDEX_1, param));
    EXPECT_TRUE(node->IsInActiveRange(INDEX_2, param));
    EXPECT_FALSE(node->IsInActiveRange(INDEX_10, param));
}

/**
 * @tc.name: IsInCacheRange_ChecksRangeTest
 * @tc.desc: Test IsInCacheRange checks if index is in cache range
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, IsInCacheRange_ChecksRangeTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    ActiveRangeParam param = { INDEX_1, INDEX_2, INDEX_0, INDEX_1 };

    EXPECT_FALSE(node->IsInCacheRange(INDEX_0, param));
    EXPECT_FALSE(node->IsInCacheRange(INDEX_1, param));
    EXPECT_FALSE(node->IsInCacheRange(INDEX_2, param));
    EXPECT_FALSE(node->IsInCacheRange(INDEX_10, param));
}

/**
 * @tc.name: GetChildByIndex_CreatesAndCachesTest
 * @tc.desc: Test GetChildByIndex creates and caches child
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetChildByIndex_CreatesAndCachesTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    bool createItemCalled = false;
    SetCallbacksForTest(node,
        [&createItemCalled](int32_t index) -> RefPtr<UINode> {
            createItemCalled = true;
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    auto child = node->GetChildByIndex(INDEX_0);
    EXPECT_FALSE(createItemCalled);
    EXPECT_EQ(child, nullptr);
}

/**
 * @tc.name: GetChildByIndex_ReturnsCachedTest
 * @tc.desc: Test GetChildByIndex returns cached child
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetChildByIndex_ReturnsCachedTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    int createCount = 0;
    SetCallbacksForTest(node,
        [&createCount](int32_t index) -> RefPtr<UINode> {
            createCount++;
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    auto child1 = node->GetChildByIndex(INDEX_0);
    auto child2 = node->GetChildByIndex(INDEX_0);

    EXPECT_EQ(createCount, 0);
    EXPECT_EQ(child1, nullptr);
    EXPECT_EQ(child2, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndex_WithBuildTest
 * @tc.desc: Test GetFrameChildByIndex with needBuild=true
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndex_WithBuildTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    auto child = node->GetFrameChildByIndex(INDEX_0, true, false, true);

    EXPECT_NE(child, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndex_WithoutBuildTest
 * @tc.desc: Test GetFrameChildByIndex with needBuild=false
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndex_WithoutBuildTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child = node->GetFrameChildByIndex(INDEX_0, false, false, true);

    EXPECT_EQ(child, nullptr);
}

/**
 * @tc.name: OnDataChange_HandlesChangeTest
 * @tc.desc: Test OnDataChange handles data change
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, OnDataChange_HandlesChangeTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->OnDataChange(INDEX_0, INDEX_1, UINode::NotificationType::START_CHANGE_POSITION);

    EXPECT_EQ(node->node4Index_.Size(), 0);
}

/**
 * @tc.name: BuildAllChildren_BuildsAllTest
 * @tc.desc: Test BuildAllChildren builds all children
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, BuildAllChildren_BuildsAllTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(INDEX_2);
    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    node->BuildAllChildren();

    EXPECT_TRUE(node->needBuildAll_);
    EXPECT_EQ(node->node4Index_.Size(), 2);
}

/**
 * @tc.name: GetChildren_ReassemblesChildrenTest
 * @tc.desc: Test GetChildren reassembles children list
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetChildren_ReassemblesChildrenTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(INDEX_2);
    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    node->DoSetActiveChildRange(INDEX_0, INDEX_1, INDEX_0, INDEX_0, false);

    EXPECT_EQ(node->activeRangeParam_.start, INDEX_0);
    EXPECT_EQ(node->activeRangeParam_.end, INDEX_1);
}

/**
 * @tc.name: RecycleItems_NotImplementedTest
 * @tc.desc: Test RecycleItems is not implemented yet
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, RecycleItems_NotImplementedTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->RecycleItems(INDEX_0, INDEX_2);

    EXPECT_EQ(node->GetId(), TEST_NODE_ID);
}

/**
 * @tc.name: GetFrameNodeIndex_NotImplementedTest
 * @tc.desc: Test GetFrameNodeIndex is not implemented yet
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameNodeIndex_NotImplementedTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto frameNode = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto index = node->GetFrameNodeIndex(frameNode);

    EXPECT_EQ(index, INVALID_INDEX);
}

/**
 * @tc.name: SetNeedBuildAll_UpdatesFlagTest
 * @tc.desc: Test SetNeedBuildAll updates needBuildAll_ flag
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, SetNeedBuildAll_UpdatesFlagTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->needBuildAll_);

    node->SetNeedBuildAll(false);
    EXPECT_FALSE(node->needBuildAll_);

    node->SetNeedBuildAll(true);
    EXPECT_TRUE(node->needBuildAll_);
}

/**
 * @tc.name: DumpInfo_LogsInfoTest
 * @tc.desc: Test DumpInfo logs node information without crash
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, DumpInfo_LogsInfoTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->DumpInfo();

    EXPECT_EQ(node->GetTag(), V2::JS_LAZY_FOR_EACH_ETS_TAG);
}

/**
 * @tc.name: DoSetActiveChildRange_NoCallbackTest
 * @tc.desc: Test DoSetActiveChildRange without updateRange_ callback
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, DoSetActiveChildRange_NoCallbackTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);

    node->DoSetActiveChildRange(INDEX_0, INDEX_2, INDEX_0, INDEX_0, false);

    EXPECT_EQ(node->activeRangeParam_.start, INDEX_0);
    EXPECT_EQ(node->activeRangeParam_.end, INDEX_2);
}

/**
 * @tc.name: GetFrameNode_EmptyTest
 * @tc.desc: Test GetFrameNode returns null
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameNode_EmptyTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto result = node->GetFrameNode(INDEX_0);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: PostIdleTask_AlreadyScheduledTest
 * @tc.desc: Test PostIdleTask returns early when already scheduled
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, PostIdleTask_AlreadyScheduledTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->postUpdateTaskHasBeenScheduled_ = true;
    node->PostIdleTask();

    EXPECT_TRUE(node->postUpdateTaskHasBeenScheduled_);
}

/**
 * @tc.name: SetOnMove_DeactivateTest
 * @tc.desc: Test SetOnMove with nullptr when onMoveEvent_ is set
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, SetOnMove_DeactivateTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->onMoveEvent_ = [](int32_t, int32_t) {};
    node->SetOnMove(nullptr);

    EXPECT_EQ(node->onMoveEvent_, nullptr);
}

/**
 * @tc.name: SetItemDragEvent_WithoutOnMoveTest
 * @tc.desc: Test SetItemDragEvent does not set handlers when onMove is null
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, SetItemDragEvent_WithoutOnMoveTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetItemDragEvent([](int32_t) {}, [](int32_t) {}, [](int32_t, int32_t) {}, [](int32_t) {});

    EXPECT_EQ(node->onLongPressEvent_, nullptr);
    EXPECT_EQ(node->onDragStartEvent_, nullptr);
    EXPECT_EQ(node->onMoveThroughEvent_, nullptr);
    EXPECT_EQ(node->onDropEvent_, nullptr);
}

/**
 * @tc.name: DumpInfo_RepeatNodeTest
 * @tc.desc: Test DumpInfo for repeat node without crash
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, DumpInfo_RepeatNodeTest, TestSize.Level1)
{
    auto node = CreateLazyNode(true);
    ASSERT_NE(node, nullptr);

    node->DumpInfo();

    EXPECT_TRUE(node->isRepeat_);
}

/**
 * @tc.name: DumpUINode_NullTest
 * @tc.desc: Test DumpUINode with null node
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, DumpUINode_NullTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto result = node->DumpUINode(nullptr);
    EXPECT_EQ(result, "UINode: nullptr");
}

/**
 * @tc.name: DumpUINode_NonNullTest
 * @tc.desc: Test DumpUINode with non-null node
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, DumpUINode_NonNullTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child = CreateUINode();
    auto result = node->DumpUINode(child);
    EXPECT_NE(result, "UINode: nullptr");
}

/**
 * @tc.name: BuildAllChildren_EmptyTest
 * @tc.desc: Test BuildAllChildren with zero count
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, BuildAllChildren_EmptyTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->BuildAllChildren();

    EXPECT_EQ(node->node4Index_.Size(), 0);
}

/**
 * @tc.name: SetJSViewActive_WithItemsTest
 * @tc.desc: Test SetJSViewActive with items in cache
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, SetJSViewActive_WithItemsTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, INDEX_0, AceType::MakeRefPtr<Pattern>());
    node->node4Index_.Put(INDEX_0, child);

    node->SetJSViewActive(false);
    EXPECT_FALSE(node->isActive_);
}

/**
 * @tc.name: GetFrameNodeIndex_NullNodeTest
 * @tc.desc: Test GetFrameNodeIndex with null node
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameNodeIndex_NullNodeTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto index = node->GetFrameNodeIndex(nullptr);
    EXPECT_EQ(index, INVALID_INDEX);
}

/**
 * @tc.name: MoveData_ChildrenEmptyTest
 * @tc.desc: Test MoveData returns early when children is empty
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, MoveData_ChildrenEmptyTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->MoveData(INDEX_0, INDEX_1);

    EXPECT_FALSE(node->moveFromTo_.has_value());
}

/**
 * @tc.name: MoveData_FullPathTest
 * @tc.desc: Test MoveData full path with children and onMoveFromTo_
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, MoveData_FullPathTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child1 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto& children = node->ModifyChildren();
    children.push_back(child0);
    children.push_back(child1);

    node->node4Index_.Put(INDEX_0, child0);
    node->node4Index_.Put(INDEX_1, child1);

    bool moveFromToCalled = false;
    node->SetOnMoveFromTo([&moveFromToCalled](int32_t, int32_t) { moveFromToCalled = true; });

    node->MoveData(INDEX_0, INDEX_1);

    EXPECT_TRUE(moveFromToCalled);
}

/**
 * @tc.name: MoveData_FromOutOfRangeTest
 * @tc.desc: Test MoveData returns early when from index out of range
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, MoveData_FromOutOfRangeTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto& children = node->ModifyChildren();
    children.push_back(child0);
    node->node4Index_.Put(INDEX_0, child0);

    node->MoveData(INDEX_5, INDEX_0);

    EXPECT_FALSE(node->moveFromTo_.has_value());
}

/**
 * @tc.name: MoveData_WithNeedUpdateTest
 * @tc.desc: Test MoveData with isNeedUpdate=true
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, MoveData_WithNeedUpdateTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto parentNode = CreateFrameNode(V2::COLUMN_ETS_TAG);
    parentNode->AddChild(node);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child1 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto& children = node->ModifyChildren();
    children.push_back(child0);
    children.push_back(child1);
    node->node4Index_.Put(INDEX_0, child0);
    node->node4Index_.Put(INDEX_1, child1);

    node->SetOnMoveFromTo([](int32_t, int32_t) {});
    node->MoveData(INDEX_0, INDEX_1, true);

    EXPECT_TRUE(node->isActive_);
}

/**
 * @tc.name: MoveData_StartOptMissingTest
 * @tc.desc: Test MoveData returns early when start child not in node4Index_
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, MoveData_StartOptMissingTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child1 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto& children = node->ModifyChildren();
    children.push_back(child0);
    children.push_back(child1);

    node->MoveData(INDEX_0, INDEX_1);

    EXPECT_FALSE(node->moveFromTo_.has_value());
}

/**
 * @tc.name: ConvertFromToIndex_WithMoveFromToTest
 * @tc.desc: Test ConvertFromToIndex with moveFromTo_ set
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, ConvertFromToIndex_WithMoveFromToTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->moveFromTo_ = std::make_pair(INDEX_0, INDEX_2);

    // second == index -> return first
    EXPECT_EQ(node->ConvertFromToIndex(INDEX_2), INDEX_0);
    // first <= index < second -> return index + 1
    EXPECT_EQ(node->ConvertFromToIndex(INDEX_1), INDEX_2);
    // index out of range -> return index unchanged
    EXPECT_EQ(node->ConvertFromToIndex(INDEX_3), INDEX_3);
}

/**
 * @tc.name: ConvertFromToIndexRevert_WithMoveFromToTest
 * @tc.desc: Test ConvertFromToIndexRevert with moveFromTo_ set
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, ConvertFromToIndexRevert_WithMoveFromToTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->moveFromTo_ = std::make_pair(INDEX_0, INDEX_2);

    // first == index -> return second
    EXPECT_EQ(node->ConvertFromToIndexRevert(INDEX_0), INDEX_2);
    // first < index <= second -> return index - 1
    EXPECT_EQ(node->ConvertFromToIndexRevert(INDEX_1), INDEX_0);
    EXPECT_EQ(node->ConvertFromToIndexRevert(INDEX_2), INDEX_1);
    // index out of range -> return index
    EXPECT_EQ(node->ConvertFromToIndexRevert(INDEX_3), INDEX_3);
}

/**
 * @tc.name: ConvertFromToIndex_ReverseMoveTest
 * @tc.desc: Test ConvertFromToIndex with reverse move (from > to)
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, ConvertFromToIndex_ReverseMoveTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->moveFromTo_ = std::make_pair(INDEX_2, INDEX_0);

    // second < index <= first -> return index - 1
    EXPECT_EQ(node->ConvertFromToIndex(INDEX_2), INDEX_1);
    EXPECT_EQ(node->ConvertFromToIndex(INDEX_1), INDEX_0);
    // index out of range -> return index
    EXPECT_EQ(node->ConvertFromToIndex(INDEX_3), INDEX_3);
}

/**
 * @tc.name: ConvertFromToIndexRevert_ReverseMoveTest
 * @tc.desc: Test ConvertFromToIndexRevert with reverse move (from > to)
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, ConvertFromToIndexRevert_ReverseMoveTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->moveFromTo_ = std::make_pair(INDEX_2, INDEX_0);

    // second <= index < first -> return index + 1
    EXPECT_EQ(node->ConvertFromToIndexRevert(INDEX_0), INDEX_1);
    EXPECT_EQ(node->ConvertFromToIndexRevert(INDEX_1), INDEX_2);
    // first == index -> return second
    EXPECT_EQ(node->ConvertFromToIndexRevert(INDEX_2), INDEX_0);
    // index out of range -> return index
    EXPECT_EQ(node->ConvertFromToIndexRevert(INDEX_3), INDEX_3);
}

/**
 * @tc.name: UpdateMoveFromTo_FirstTimeTest
 * @tc.desc: Test UpdateMoveFromTo creates new pair
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, UpdateMoveFromTo_FirstTimeTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->UpdateMoveFromTo(INDEX_0, INDEX_1);

    EXPECT_TRUE(node->moveFromTo_.has_value());
    EXPECT_EQ(node->moveFromTo_.value().first, INDEX_0);
    EXPECT_EQ(node->moveFromTo_.value().second, INDEX_1);
}

/**
 * @tc.name: UpdateMoveFromTo_UpdateTest
 * @tc.desc: Test UpdateMoveFromTo updates existing pair
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, UpdateMoveFromTo_UpdateTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->moveFromTo_ = std::make_pair(INDEX_0, INDEX_1);
    node->UpdateMoveFromTo(INDEX_0, INDEX_2);

    EXPECT_TRUE(node->moveFromTo_.has_value());
    EXPECT_EQ(node->moveFromTo_.value().second, INDEX_2);
}

/**
 * @tc.name: UpdateMoveFromTo_ResetTest
 * @tc.desc: Test UpdateMoveFromTo resets when second equals first
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, UpdateMoveFromTo_ResetTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->moveFromTo_ = std::make_pair(INDEX_0, INDEX_1);
    node->UpdateMoveFromTo(INDEX_0, INDEX_0);

    EXPECT_FALSE(node->moveFromTo_.has_value());
}

/**
 * @tc.name: FireOnMove_TriggersCallbackTest
 * @tc.desc: Test FireOnMove calls onMoveFromTo_ and base
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, FireOnMove_TriggersCallbackTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    bool onMoveFromToCalled = false;
    node->SetOnMoveFromTo([&onMoveFromToCalled](int32_t from, int32_t to) {
        onMoveFromToCalled = true;
    });

    bool onMoveCalled = false;
    node->onMoveEvent_ = [&onMoveCalled](int32_t, int32_t) { onMoveCalled = true; };

    node->FireOnMove(INDEX_0, INDEX_1);

    EXPECT_TRUE(onMoveCalled);
}

/**
 * @tc.name: UpdateItemsForOnMove_NoMoveTest
 * @tc.desc: Test UpdateItemsForOnMove returns early without moveFromTo_
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, UpdateItemsForOnMove_NoMoveTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->UpdateItemsForOnMove();

    EXPECT_FALSE(node->moveFromTo_.has_value());
}

/**
 * @tc.name: UpdateItemsForOnMove_FullPathTest
 * @tc.desc: Test UpdateItemsForOnMove rearranges node4Index_
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, UpdateItemsForOnMove_FullPathTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child1 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child2 = CreateFrameNode(V2::TEXT_ETS_TAG);
    node->node4Index_.Put(INDEX_0, child0);
    node->node4Index_.Put(INDEX_1, child1);
    node->node4Index_.Put(INDEX_2, child2);

    // Test same index early return
    node->moveFromTo_ = std::make_pair(INDEX_1, INDEX_1);
    node->UpdateItemsForOnMove();
    EXPECT_EQ(node->node4Index_.Size(), 3);

    // Test actual move
    node->moveFromTo_ = std::make_pair(INDEX_0, INDEX_2);
    node->UpdateItemsForOnMove();
    EXPECT_EQ(node->node4Index_.Size(), 3);
}

/**
 * @tc.name: IsInActiveRange_LoopTest
 * @tc.desc: Test IsInActiveRange with loop mode
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, IsInActiveRange_LoopTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->isLoop_ = true;

    // wrapped: start > end
    ActiveRangeParam wrappedParam = { INDEX_2, INDEX_0, INDEX_0, INDEX_0 };
    EXPECT_TRUE(node->IsInActiveRange(INDEX_2, wrappedParam));
    EXPECT_TRUE(node->IsInActiveRange(INDEX_0, wrappedParam));
    EXPECT_FALSE(node->IsInActiveRange(INDEX_1, wrappedParam));

    // normal: start <= end
    ActiveRangeParam normalParam = { INDEX_0, INDEX_2, INDEX_0, INDEX_0 };
    EXPECT_TRUE(node->IsInActiveRange(INDEX_1, normalParam));
    EXPECT_FALSE(node->IsInActiveRange(INDEX_3, normalParam));
}

/**
 * @tc.name: IsInCacheRange_NonLoopTest
 * @tc.desc: Test IsInCacheRange in non-loop mode with valid data
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, IsInCacheRange_NonLoopTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);

    ActiveRangeParam param = { INDEX_1, INDEX_2, INDEX_1, INDEX_1 };
    // within cache bounds: start=1-1=0, end=2+1=3 -> [0, 3]
    EXPECT_TRUE(node->IsInCacheRange(INDEX_0, param));
    EXPECT_TRUE(node->IsInCacheRange(INDEX_3, param));
    // outside cache bounds
    EXPECT_FALSE(node->IsInCacheRange(INDEX_4, param));
    // total=0 -> false
    ActiveRangeParam emptyParam = { INDEX_1, INDEX_2, INDEX_0, INDEX_1 };
    EXPECT_FALSE(node->IsInCacheRange(INDEX_0, emptyParam));
}

/**
 * @tc.name: IsInCacheRange_LoopFullCoverageTest
 * @tc.desc: Test IsInCacheRange loop mode with full coverage
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, IsInCacheRange_LoopFullCoverageTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);
    node->isLoop_ = true;

    // wrapped: start > end, full coverage (cache regions connect or overlap)
    ActiveRangeParam wrappedFull = { INDEX_8, INDEX_2, INDEX_5, INDEX_5 };
    EXPECT_TRUE(node->IsInCacheRange(INDEX_0, wrappedFull));

    // not wrapped, full coverage (covers entire list)
    ActiveRangeParam normalFull = { INDEX_0, INDEX_6, INDEX_0, INDEX_3 };
    EXPECT_TRUE(node->IsInCacheRange(INDEX_0, normalFull));
}

/**
 * @tc.name: IsInCacheRange_LoopRegionTest
 * @tc.desc: Test IsInCacheRange loop mode with non-full coverage
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, IsInCacheRange_LoopRegionTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);
    node->isLoop_ = true;

    // wrapped, not full coverage, single continuous region
    ActiveRangeParam wrappedRegion = { INDEX_8, INDEX_2, INDEX_1, INDEX_1 };
    EXPECT_TRUE(node->IsInCacheRange(INDEX_0, wrappedRegion));
    EXPECT_FALSE(node->IsInCacheRange(INDEX_5, wrappedRegion));

    // not wrapped, not full coverage, single continuous region
    ActiveRangeParam normalRegion = { INDEX_2, INDEX_5, INDEX_1, INDEX_1 };
    EXPECT_TRUE(node->IsInCacheRange(INDEX_2, normalRegion));
    EXPECT_FALSE(node->IsInCacheRange(INDEX_7, normalRegion));
}

/**
 * @tc.name: IsInCacheRange_LoopTwoRegionsTest
 * @tc.desc: Test IsInCacheRange loop mode with two separate regions
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, IsInCacheRange_LoopTwoRegionsTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);
    node->isLoop_ = true;

    // start=2, end=5, cacheStart=3, cacheEnd=3
    // cache bounds: 2-3=-1, 5+3=8
    // normalized: normCacheStart=9(-1%10+10=9), normCacheEnd=8
    // normCacheStart > normCacheEnd -> two regions
    // regions: [0, 8] + [9, 9]
    ActiveRangeParam twoRegionParam = { INDEX_2, INDEX_5, INDEX_3, INDEX_3 };
    EXPECT_TRUE(node->IsInCacheRange(INDEX_0, twoRegionParam));
    EXPECT_TRUE(node->IsInCacheRange(INDEX_9, twoRegionParam));
    EXPECT_TRUE(node->IsInCacheRange(INDEX_8, twoRegionParam));
}

/**
 * @tc.name: GetChildren_NonEmptyTest
 * @tc.desc: Test GetChildren returns early when children_ non-empty
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetChildren_NonEmptyTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child = CreateFrameNode(V2::TEXT_ETS_TAG);
    node->children_.push_back(child);

    const auto& result = node->GetChildren();

    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: GetChildren_WithOnMoveTest
 * @tc.desc: Test GetChildren with moveFromTo_ set
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetChildren_WithOnMoveTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(INDEX_2);
    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );
    node->SetNeedBuildAll(false);
    node->DoSetActiveChildRange(INDEX_0, INDEX_1, INDEX_0, INDEX_0, false);

    node->moveFromTo_ = std::make_pair(INDEX_0, INDEX_1);
    // trigger GetChildren rebuild via idle task flow
    node->children_.clear();

    node->GetChildren();
    EXPECT_GE(node->children_.size(), 0);
}

/**
 * @tc.name: InitDragManager_NullChildTest
 * @tc.desc: Test InitDragManager returns early with null child
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, InitDragManager_NullChildTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->InitDragManager(nullptr);

    EXPECT_EQ(node->GetParent(), nullptr);
}

/**
 * @tc.name: InitDragManager_NoParentTest
 * @tc.desc: Test InitDragManager returns early without parent
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, InitDragManager_NoParentTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto childNode = CreateFrameNode(V2::TEXT_ETS_TAG);
    node->InitDragManager(childNode);

    EXPECT_EQ(node->GetParent(), nullptr);
}

/**
 * @tc.name: InitDragManager_NonListGridTest
 * @tc.desc: Test InitDragManager returns early with non-list/grid parent
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, InitDragManager_NonListGridTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto parentNode = CreateFrameNode(V2::COLUMN_ETS_TAG);
    parentNode->AddChild(node);

    auto childNode = CreateFrameNode(V2::TEXT_ETS_TAG);
    node->InitDragManager(childNode);

    EXPECT_NE(node->GetParent(), nullptr);
}

/**
 * @tc.name: InitAllChildren_NoParentTest
 * @tc.desc: Test InitAllChildrenDragManager returns early with null parent
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, InitAllChildren_NoParentTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->InitAllChildrenDragManager(true);

    EXPECT_EQ(node->GetParent(), nullptr);
}

/**
 * @tc.name: InitAllChildren_NonListGridTest
 * @tc.desc: Test InitAllChildrenDragManager returns early with non-list/grid parent
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, InitAllChildren_NonListGridTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto parentNode = CreateFrameNode(V2::COLUMN_ETS_TAG);
    parentNode->AddChild(node);

    node->InitAllChildrenDragManager(true);

    EXPECT_NE(node->GetParent(), nullptr);
}

/**
 * @tc.name: GetFrameChildByIndexImpl_CreateFailsTest
 * @tc.desc: Test GetFrameChildByIndexImpl when createItem_ returns null
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndexImpl_CreateFailsTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node,
        [](int32_t) -> RefPtr<UINode> {
            return nullptr;
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    auto result = node->GetFrameChildByIndex(INDEX_0, true, false, false);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndexImpl_NeedBuildNoCreateItemTest
 * @tc.desc: Test GetFrameChildByIndexImpl with needBuild but no createItem_
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndexImpl_NeedBuildNoCreateItemTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto result = node->GetFrameChildByIndex(INDEX_0, true, false, false);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndexImpl_IsCacheTest
 * @tc.desc: Test GetFrameChildByIndexImpl with isCache=true
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndexImpl_IsCacheTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    auto result = node->GetFrameChildByIndex(INDEX_0, true, true, false);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndexImpl_AddToRenderTreeTest
 * @tc.desc: Test GetFrameChildByIndexImpl with addToRenderTree=true
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndexImpl_AddToRenderTreeTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );
    node->isActive_ = true;

    auto result = node->GetFrameChildByIndex(INDEX_0, true, false, true);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndexImpl_WithOnMoveTest
 * @tc.desc: Test GetFrameChildByIndexImpl with onMoveEvent_ set
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndexImpl_WithOnMoveTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );
    node->onMoveEvent_ = [](int32_t, int32_t) {};

    auto result = node->GetFrameChildByIndex(INDEX_0, true, false, true);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndexImpl_IsCacheRepeatTest
 * @tc.desc: Test GetFrameChildByIndexImpl with isCache and isRepeat
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndexImpl_IsCacheRepeatTest, TestSize.Level1)
{
    auto node = CreateLazyNode(true);
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    auto result = node->GetFrameChildByIndex(INDEX_0, true, true, false);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndexImpl_OnMainTreeTest
 * @tc.desc: Test GetFrameChildByIndexImpl when node is on main tree
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndexImpl_OnMainTreeTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );
    node->onMainTree_ = true;

    auto result = node->GetFrameChildByIndex(INDEX_0, true, false, true);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndexImpl_AddToRenderTreeFalseTest
 * @tc.desc: Test GetFrameChildByIndexImpl with addToRenderTree=false and isCache=false
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndexImpl_AddToRenderTreeFalseTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    auto result = node->GetFrameChildByIndex(INDEX_0, true, false, false);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndexImpl_IsActiveFalseTest
 * @tc.desc: Test GetFrameChildByIndexImpl with isActive_=false
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndexImpl_IsActiveFalseTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );
    node->isActive_ = false;

    auto result = node->GetFrameChildByIndex(INDEX_0, true, false, true);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndexImpl_CustomFreezeDisableTest
 * @tc.desc: Test GetFrameChildByIndexImpl with customComponentFreeze DISABLED
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndexImpl_CustomFreezeDisableTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );
    node->options_.customComponentFreezeMode = LazyForEachCustomComponentFreezeMode::DISABLED;

    auto result = node->GetFrameChildByIndex(INDEX_0, true, true, false);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndexImpl_CustomFreezeEnableTest
 * @tc.desc: Test GetFrameChildByIndexImpl with customComponentFreeze ENABLED
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameChildByIndexImpl_CustomFreezeEnableTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );
    node->options_.customComponentFreezeMode = LazyForEachCustomComponentFreezeMode::ENABLED;

    auto result = node->GetFrameChildByIndex(INDEX_0, true, true, false);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: UpdateIsCache_ShouldTriggerFalseTest
 * @tc.desc: Test UpdateIsCache returns early when shouldTrigger=false
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, UpdateIsCache_ShouldTriggerFalseTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child = CreateUINode();
    node->UpdateIsCache(child, true, false);

    EXPECT_EQ(node->recycleNodeIds_.size(), 0);
}

/**
 * @tc.name: UpdateIsCache_ReuseTest
 * @tc.desc: Test UpdateIsCache triggers OnReuse
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, UpdateIsCache_ReuseTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, INDEX_0, AceType::MakeRefPtr<Pattern>());
    node->recycleNodeIds_.insert(INDEX_0);

    node->UpdateIsCache(child, true, true);

    EXPECT_TRUE(node->recycleNodeIds_.empty());
}

/**
 * @tc.name: UpdateIsCache_RecycleTest
 * @tc.desc: Test UpdateIsCache triggers OnRecycle
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, UpdateIsCache_RecycleTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, INDEX_0, AceType::MakeRefPtr<Pattern>());

    node->UpdateIsCache(child, false, true);

    EXPECT_FALSE(node->recycleNodeIds_.empty());
}

/**
 * @tc.name: GetFrameNodeIndex_FoundTest
 * @tc.desc: Test GetFrameNodeIndex finds node in node4Index_
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, GetFrameNodeIndex_FoundTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    // null entry should be skipped
    node->node4Index_.Put(INDEX_0, nullptr);

    auto innerChild = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, INDEX_0, AceType::MakeRefPtr<Pattern>());
    auto outerChild = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, INDEX_1, AceType::MakeRefPtr<Pattern>());
    outerChild->AddChild(innerChild);
    node->node4Index_.Put(INDEX_1, outerChild);

    auto result = node->GetFrameNodeIndex(innerChild);

    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: PurgeNode_RemovesOutsideCacheTest
 * @tc.desc: Test PurgeNode removes items outside cache range
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, PurgeNode_RemovesOutsideCacheTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);
    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto child1 = CreateFrameNode(V2::TEXT_ETS_TAG);
    node->node4Index_.Put(INDEX_0, child0);
    node->node4Index_.Put(INDEX_1, child1);
    node->activeRangeParam_ = { INDEX_0, INDEX_0, INDEX_0, INDEX_0 };

    node->PurgeNode();

    EXPECT_EQ(node->node4Index_.Size(), 1);
}

/**
 * @tc.name: RemovingExpiringItem_NonEmptyTest
 * @tc.desc: Test RemovingExpiringItem with non-empty list
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, RemovingExpiringItem_NonEmptyTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto child0 = CreateFrameNode(V2::TEXT_ETS_TAG);
    node->removingNodeList_.push_back(child0);

    node->RemovingExpiringItem(GetSysTimestamp() + 1000000);

    EXPECT_TRUE(node->removingNodeList_.empty());
}

/**
 * @tc.name: RebuildCache_RemovesInactiveTest
 * @tc.desc: Test RebuildCache processes nodes
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, RebuildCache_RemovesInactiveTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    auto child = node->GetFrameChildByIndex(INDEX_0, true, false, true);
    ASSERT_NE(child, nullptr);

    node->activeRangeParam_ = { INDEX_1, INDEX_2, INDEX_0, INDEX_0 };

    node->RebuildCache();

    EXPECT_EQ(node->node4Index_.Size(), 1);
}

/**
 * @tc.name: RebuildCache_NullNodeTest
 * @tc.desc: Test RebuildCache skips null nodes
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, RebuildCache_NullNodeTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);
    auto child = CreateFrameNode(V2::TEXT_ETS_TAG);
    node->node4Index_.Put(INDEX_0, child);
    node->node4Index_.Put(INDEX_1, nullptr);
    node->activeRangeParam_ = { INDEX_0, INDEX_1, INDEX_0, INDEX_0 };

    node->RebuildCache();

    EXPECT_EQ(node->node4Index_.Size(), 2);
}

/**
 * @tc.name: RebuildCache_RepeatTest
 * @tc.desc: Test RebuildCache with isRepeat_ enabled
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, RebuildCache_RepeatTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetTotalCount(TOTAL_COUNT);
    node->isRepeat_ = true;

    SetCallbacksForTest(node,
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    auto child = node->GetFrameChildByIndex(INDEX_0, true, false, true);
    ASSERT_NE(child, nullptr);
    node->activeRangeParam_ = { INDEX_0, INDEX_0, INDEX_0, INDEX_0 };

    node->RebuildCache();

    EXPECT_EQ(node->node4Index_.Size(), 1);
}

/**
 * @tc.name: InitAllChildren_ListInitTest
 * @tc.desc: Test InitAllChildrenDragManager with List parent, init=true
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, InitAllChildren_ListInitTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto parentNode = CreateFrameNode(V2::LIST_ETS_TAG);
    parentNode->AddChild(node);

    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr);
    auto innerNode = AceType::MakeRefPtr<FrameNode>(V2::LIST_ITEM_ETS_TAG, -1, listItemPattern);
    listItemPattern->AttachToFrameNode(innerNode);

    auto outerNode = AceType::MakeRefPtr<FrameNode>(V2::LIST_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    outerNode->AddChild(innerNode);
    node->node4Index_.Put(INDEX_0, outerNode);

    node->InitAllChildrenDragManager(true);

    EXPECT_NE(node->GetParent(), nullptr);
}

/**
 * @tc.name: InitAllChildren_ListDeinitTest
 * @tc.desc: Test InitAllChildrenDragManager with List parent, init=false
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, InitAllChildren_ListDeinitTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto parentNode = CreateFrameNode(V2::LIST_ETS_TAG);
    parentNode->AddChild(node);

    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr);
    auto innerNode = AceType::MakeRefPtr<FrameNode>(V2::LIST_ITEM_ETS_TAG, -1, listItemPattern);
    listItemPattern->AttachToFrameNode(innerNode);

    auto outerNode = AceType::MakeRefPtr<FrameNode>(V2::LIST_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    outerNode->AddChild(innerNode);
    node->node4Index_.Put(INDEX_0, outerNode);

    node->InitAllChildrenDragManager(false);

    EXPECT_NE(node->GetParent(), nullptr);
}

/**
 * @tc.name: InitAllChildren_GridInitTest
 * @tc.desc: Test InitAllChildrenDragManager with Grid parent, init=true
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, InitAllChildren_GridInitTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto parentNode = CreateFrameNode(V2::GRID_ETS_TAG);
    parentNode->AddChild(node);

    auto gridItemPattern = AceType::MakeRefPtr<GridItemPattern>(nullptr);
    auto innerNode = AceType::MakeRefPtr<FrameNode>(V2::GRID_ITEM_ETS_TAG, -1, gridItemPattern);
    gridItemPattern->AttachToFrameNode(innerNode);

    auto outerNode = AceType::MakeRefPtr<FrameNode>(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    outerNode->AddChild(innerNode);
    node->node4Index_.Put(INDEX_0, outerNode);

    node->InitAllChildrenDragManager(true);

    EXPECT_NE(node->GetParent(), nullptr);
}

/**
 * @tc.name: InitAllChildren_GridDeinitTest
 * @tc.desc: Test InitAllChildrenDragManager with Grid parent, init=false
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, InitAllChildren_GridDeinitTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto parentNode = CreateFrameNode(V2::GRID_ETS_TAG);
    parentNode->AddChild(node);

    auto gridItemPattern = AceType::MakeRefPtr<GridItemPattern>(nullptr);
    auto innerNode = AceType::MakeRefPtr<FrameNode>(V2::GRID_ITEM_ETS_TAG, -1, gridItemPattern);
    gridItemPattern->AttachToFrameNode(innerNode);

    auto outerNode = AceType::MakeRefPtr<FrameNode>(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    outerNode->AddChild(innerNode);
    node->node4Index_.Put(INDEX_0, outerNode);

    node->InitAllChildrenDragManager(false);

    EXPECT_NE(node->GetParent(), nullptr);
}

/**
 * @tc.name: InitAllChildren_SkipInvalidTest
 * @tc.desc: Test InitAllChildrenDragManager skips invalid items
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, InitAllChildren_SkipInvalidTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    auto parentNode = CreateFrameNode(V2::LIST_ETS_TAG);
    parentNode->AddChild(node);

    // null child in map -> !child -> continue
    node->node4Index_.Put(INDEX_0, nullptr);

    // non-FrameNode child -> !item -> continue
    auto nonFrameChild = AceType::MakeRefPtr<NonFrameTestNode>();
    node->node4Index_.Put(INDEX_1, nonFrameChild);

    // child with valid inner node but no ListItemPattern -> pattern null -> continue
    auto innerNoPattern = CreateFrameNode(V2::TEXT_ETS_TAG);
    auto outerNoPattern = AceType::MakeRefPtr<FrameNode>(V2::LIST_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    outerNoPattern->AddChild(innerNoPattern);
    node->node4Index_.Put(INDEX_2, outerNoPattern);

    // valid path
    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr);
    auto innerValid = AceType::MakeRefPtr<FrameNode>(V2::LIST_ITEM_ETS_TAG, -1, listItemPattern);
    listItemPattern->AttachToFrameNode(innerValid);
    auto outerValid = AceType::MakeRefPtr<FrameNode>(V2::LIST_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    outerValid->AddChild(innerValid);
    node->node4Index_.Put(INDEX_3, outerValid);

    node->InitAllChildrenDragManager(true);

    EXPECT_NE(node->GetParent(), nullptr);
}

} // namespace OHOS::Ace::NG
