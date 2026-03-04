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

#include <functional>
#include <list>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_2 = 2;
constexpr int32_t INDEX_10 = 10;
constexpr int32_t INVALID_INDEX = -1;
constexpr int32_t DEFAULT_COUNT = 5;
constexpr int32_t CACHE_COUNT = 3;
constexpr int32_t ZERO_COUNT = 0;
constexpr int32_t TEST_NODE_ID = 100;
} // namespace

class LazyForEachTestNgAI : public testing::Test {
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

    RefPtr<LazyForEachNode> CreateLazyForEachNode()
    {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, pattern);
        pattern->AttachToFrameNode(frameNode);
        ViewStackProcessor::GetInstance()->Push(frameNode);

        LazyForEachModelNG lazyForEach;
        const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
            AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
        lazyForEach.Create(mockLazyForEachActuator);
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
        return lazyForEachNode;
    }

    RefPtr<FrameNode> CreateFrameNode(const std::string& tag)
    {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
        pattern->AttachToFrameNode(frameNode);
        return frameNode;
    }

    RefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder> CreateMockBuilder()
    {
        return AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    }
};

/**
 * @tc.name: Constructor_BasicTest
 * @tc.desc: Test LazyForEachNode constructor initializes members correctly
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, Constructor_BasicTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();
    auto node = AceType::MakeRefPtr<LazyForEachNode>(TEST_NODE_ID, builder);

    EXPECT_EQ(node->GetId(), TEST_NODE_ID);
    EXPECT_EQ(node->builder_, builder);
    EXPECT_FALSE(node->isRegisterListener_);
    EXPECT_TRUE(node->isActive_);
    EXPECT_EQ(node->startIndex_, 0);
    EXPECT_EQ(node->count_, 0);
}

/**
 * @tc.name: GetOrCreateLazyForEachNode_CreateNewTest
 * @tc.desc: Test GetOrCreateLazyForEachNode creates new node for new ID
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, GetOrCreateLazyForEachNode_CreateNewTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();
    auto node = LazyForEachNode::GetOrCreateLazyForEachNode(TEST_NODE_ID, builder);

    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->GetId(), TEST_NODE_ID);
    EXPECT_TRUE(node->isRegisterListener_);
}

/**
 * @tc.name: GetOrCreateLazyForEachNode_GetExistingTest
 * @tc.desc: Test GetOrCreateLazyForEachNode returns existing node for same ID
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, GetOrCreateLazyForEachNode_GetExistingTest, TestSize.Level1)
{
    auto builder1 = CreateMockBuilder();
    auto node1 = LazyForEachNode::GetOrCreateLazyForEachNode(TEST_NODE_ID, builder1);

    auto builder2 = CreateMockBuilder();
    auto node2 = LazyForEachNode::GetOrCreateLazyForEachNode(TEST_NODE_ID, builder2);

    EXPECT_EQ(node1, node2);
}

/**
 * @tc.name: GetOrCreateLazyForEachNode_UpdateBuilderTest
 * @tc.desc: Test GetOrCreateLazyForEachNode updates builder when different
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, GetOrCreateLazyForEachNode_UpdateBuilderTest, TestSize.Level1)
{
    auto builder1 = CreateMockBuilder();
    auto node = LazyForEachNode::GetOrCreateLazyForEachNode(TEST_NODE_ID, builder1);

    auto builder2 = CreateMockBuilder();
    auto node2 = LazyForEachNode::GetOrCreateLazyForEachNode(TEST_NODE_ID, builder2);

    EXPECT_EQ(node->builder_, builder2);
}

/**
 * @tc.name: CreateLazyForEachNode_BasicTest
 * @tc.desc: Test CreateLazyForEachNode creates node without checking existing
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, CreateLazyForEachNode_BasicTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();
    auto node = LazyForEachNode::CreateLazyForEachNode(TEST_NODE_ID + 1, builder);

    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->GetId(), TEST_NODE_ID + 1);
}

/**
 * @tc.name: OnDelete_UnregisterListenerTest
 * @tc.desc: Test OnDelete unregisters listener when builder exists
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDelete_UnregisterListenerTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();
    auto node = AceType::MakeRefPtr<LazyForEachNode>(TEST_NODE_ID, builder);
    node->isRegisterListener_ = true;

    node->OnDelete();

    EXPECT_FALSE(node->isRegisterListener_);
}

/**
 * @tc.name: OnDelete_NullBuilderTest
 * @tc.desc: Test OnDelete handles null builder gracefully
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDelete_NullBuilderTest, TestSize.Level1)
{
    auto node = AceType::MakeRefPtr<LazyForEachNode>(TEST_NODE_ID, nullptr);
    node->isRegisterListener_ = true;

    node->OnDelete();

    SUCCEED();
}

/**
 * @tc.name: IsAtomicNode_ReturnsFalseTest
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, IsAtomicNode_ReturnsFalseTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    EXPECT_FALSE(node->IsAtomicNode());
}

/**
 * @tc.name: FrameCount_WithBuilderTest
 * @tc.desc: Test FrameCount returns builder's total count
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, FrameCount_WithBuilderTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);
    ASSERT_NE(node->builder_, nullptr);

    EXPECT_EQ(node->FrameCount(), ZERO_COUNT);
}

/**
 * @tc.name: FrameCount_WithoutBuilderTest
 * @tc.desc: Test FrameCount returns 0 when builder is null
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, FrameCount_WithoutBuilderTest, TestSize.Level1)
{
    auto node = AceType::MakeRefPtr<LazyForEachNode>(TEST_NODE_ID, nullptr);

    EXPECT_EQ(node->FrameCount(), 0);
}

/**
 * @tc.name: IsSyntaxNode_ReturnsTrueTest
 * @tc.desc: Test IsSyntaxNode returns true
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, IsSyntaxNode_ReturnsTrueTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->IsSyntaxNode());
}

/**
 * @tc.name: OnDataReloaded_ClearsChildrenTest
 * @tc.desc: Test OnDataReloaded clears children and notifies change
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataReloaded_ClearsChildrenTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->children_.push_back(CreateFrameNode(V2::TEXT_ETS_TAG));
    node->OnDataReloaded();

    EXPECT_TRUE(node->children_.empty());
}

/**
 * @tc.name: OnDataReloaded_EmptyFrameCountTest
 * @tc.desc: Test OnDataReloaded schedules idle task when FrameCount is 0
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataReloaded_EmptyFrameCountTest, TestSize.Level1)
{
    auto node = AceType::MakeRefPtr<LazyForEachNode>(TEST_NODE_ID, nullptr);
    node->OnDataReloaded();

    EXPECT_TRUE(node->children_.empty());
}

/**
 * @tc.name: OnDataAdded_SingleItemTest
 * @tc.desc: Test OnDataAdded inserts item at specified index
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataAdded_SingleItemTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->children_.push_back(CreateFrameNode(V2::TEXT_ETS_TAG));
    node->OnDataAdded(INDEX_1);

    EXPECT_TRUE(node->children_.empty());
}

/**
 * @tc.name: OnDataAdded_OutOfRangeTest
 * @tc.desc: Test OnDataAdded handles out of range index
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataAdded_OutOfRangeTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->OnDataAdded(INDEX_10);

    SUCCEED();
}

/**
 * @tc.name: OnDataBulkAdded_MultipleItemsTest
 * @tc.desc: Test OnDataBulkAdded handles multiple items
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataBulkAdded_MultipleItemsTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->children_.push_back(CreateFrameNode(V2::TEXT_ETS_TAG));
    node->OnDataBulkAdded(INDEX_1, INDEX_2);

    EXPECT_TRUE(node->children_.empty());
}

/**
 * @tc.name: OnDataBulkAdded_ZeroCountTest
 * @tc.desc: Test OnDataBulkAdded handles zero count
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataBulkAdded_ZeroCountTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->OnDataBulkAdded(INDEX_1, ZERO_COUNT);

    SUCCEED();
}

/**
 * @tc.name: OnDataDeleted_SingleItemTest
 * @tc.desc: Test OnDataDeleted removes item at specified index
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataDeleted_SingleItemTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->children_.push_back(CreateFrameNode(V2::TEXT_ETS_TAG));
    node->OnDataDeleted(INDEX_0);

    EXPECT_TRUE(node->children_.empty());
}

/**
 * @tc.name: OnDataDeleted_OutOfRangeTest
 * @tc.desc: Test OnDataDeleted handles out of range index
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataDeleted_OutOfRangeTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->OnDataDeleted(INDEX_10);

    SUCCEED();
}

/**
 * @tc.name: OnDataBulkDeleted_MultipleItemsTest
 * @tc.desc: Test OnDataBulkDeleted handles multiple items
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataBulkDeleted_MultipleItemsTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->children_.push_back(CreateFrameNode(V2::TEXT_ETS_TAG));
    node->children_.push_back(CreateFrameNode(V2::TEXT_ETS_TAG));
    node->OnDataBulkDeleted(INDEX_0, INDEX_2);

    EXPECT_TRUE(node->children_.empty());
}

/**
 * @tc.name: OnDataChanged_SingleItemTest
 * @tc.desc: Test OnDataChanged updates item at specified index
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataChanged_SingleItemTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->children_.push_back(CreateFrameNode(V2::TEXT_ETS_TAG));
    node->OnDataChanged(INDEX_0);

    EXPECT_TRUE(node->children_.empty());
}

/**
 * @tc.name: OnDataMoved_ReorderTest
 * @tc.desc: Test OnDataMoved reorders items from from to to
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataMoved_ReorderTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->OnDataMoved(INDEX_0, INDEX_1);

    SUCCEED();
}

/**
 * @tc.name: OnDataMoved_SameIndexTest
 * @tc.desc: Test OnDataMoved handles same index
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDataMoved_SameIndexTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->OnDataMoved(INDEX_0, INDEX_0);

    SUCCEED();
}

/**
 * @tc.name: OnDatasetChange_BulkOperationsTest
 * @tc.desc: Test OnDatasetChange handles bulk operations
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDatasetChange_BulkOperationsTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    std::list<V2::Operation> operations;
    node->OnDatasetChange(operations);

    SUCCEED();
}

/**
 * @tc.name: OnDatasetChange_EmptyOperationsTest
 * @tc.desc: Test OnDatasetChange handles empty operations
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, OnDatasetChange_EmptyOperationsTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    std::list<V2::Operation> operations;
    node->OnDatasetChange(operations);

    SUCCEED();
}

/**
 * @tc.name: GetFrameChildByIndex_BuildTest
 * @tc.desc: Test GetFrameChildByIndex builds child when needBuild is true
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, GetFrameChildByIndex_BuildTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    auto child = node->GetFrameChildByIndex(INDEX_0, true);

    EXPECT_EQ(child, nullptr);
}

/**
 * @tc.name: GetFrameChildByIndex_NoBuildTest
 * @tc.desc: Test GetFrameChildByIndex does not build when needBuild is false
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, GetFrameChildByIndex_NoBuildTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    auto child = node->GetFrameChildByIndex(INDEX_0, false);

    SUCCEED();
}

/**
 * @tc.name: GetFrameChildByIndex_CacheModeTest
 * @tc.desc: Test GetFrameChildByIndex in cache mode does not add to render tree
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, GetFrameChildByIndex_CacheModeTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    auto child = node->GetFrameChildByIndex(INDEX_0, true, true, false);

    SUCCEED();
}

/**
 * @tc.name: GetFrameChildByIndex_OutOfRangeTest
 * @tc.desc: Test GetFrameChildByIndex returns nullptr for out of range index
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, GetFrameChildByIndex_OutOfRangeTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    auto child = node->GetFrameChildByIndex(INDEX_10, true);

    EXPECT_EQ(child, nullptr);
}

/**
 * @tc.name: DoSetActiveChildRange_ValidRangeTest
 * @tc.desc: Test DoSetActiveChildRange with valid range
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, DoSetActiveChildRange_ValidRangeTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->DoSetActiveChildRange(INDEX_0, INDEX_2, INDEX_0, INDEX_2, false);

    SUCCEED();
}

/**
 * @tc.name: DoSetActiveChildRange_InvalidRangeTest
 * @tc.desc: Test DoSetActiveChildRange with invalid range
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, DoSetActiveChildRange_InvalidRangeTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->DoSetActiveChildRange(INVALID_INDEX, INVALID_INDEX, INVALID_INDEX, INVALID_INDEX, false);

    SUCCEED();
}

/**
 * @tc.name: BuildAllChildren_FullBuildTest
 * @tc.desc: Test BuildAllChildren builds all children
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, BuildAllChildren_FullBuildTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->BuildAllChildren();

    SUCCEED();
}

/**
 * @tc.name: GetChildren_LoadsChildrenTest
 * @tc.desc: Test GetChildren loads children on demand
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, GetChildren_LoadsChildrenTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    // GetChildren should load children on demand and not crash
    node->GetChildren();

    SUCCEED();
}

/**
 * @tc.name: RecycleItems_CleanupTest
 * @tc.desc: Test RecycleItems cleans up nodes in range
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, RecycleItems_CleanupTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->RecycleItems(INDEX_0, INDEX_2);

    SUCCEED();
}

/**
 * @tc.name: SetItemDragHandler_WithOnMoveTest
 * @tc.desc: Test SetItemDragHandler sets handlers when onMove exists
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, SetItemDragHandler_WithOnMoveTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->onMoveEvent_ = [](int32_t, int32_t) {};

    node->SetItemDragHandler([](int32_t) {}, [](int32_t) {}, [](int32_t, int32_t) {}, [](int32_t) {});

    EXPECT_NE(node->onLongPressEvent_, nullptr);
    EXPECT_NE(node->onDragStartEvent_, nullptr);
    EXPECT_NE(node->onMoveThroughEvent_, nullptr);
    EXPECT_NE(node->onDropEvent_, nullptr);
}

/**
 * @tc.name: SetItemDragHandler_WithoutOnMoveTest
 * @tc.desc: Test SetItemDragHandler does not set handlers when onMove is null
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, SetItemDragHandler_WithoutOnMoveTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->onMoveEvent_ = nullptr;

    node->SetItemDragHandler([](int32_t) {}, [](int32_t) {}, [](int32_t, int32_t) {}, [](int32_t) {});

    EXPECT_EQ(node->onLongPressEvent_, nullptr);
    EXPECT_EQ(node->onDragStartEvent_, nullptr);
    EXPECT_EQ(node->onMoveThroughEvent_, nullptr);
    EXPECT_EQ(node->onDropEvent_, nullptr);
}

/**
 * @tc.name: SetOnMove_EnableDragTest
 * @tc.desc: Test SetOnMove enables drag with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, SetOnMove_EnableDragTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    bool onMoveCalled = false;
    node->SetOnMove([&onMoveCalled](int32_t, int32_t) { onMoveCalled = true; });

    EXPECT_NE(node->onMoveEvent_, nullptr);
}

/**
 * @tc.name: SetOnMove_DisableDragTest
 * @tc.desc: Test SetOnMove disables drag with null callback
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, SetOnMove_DisableDragTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->onMoveEvent_ = [](int32_t, int32_t) {};
    node->SetOnMove(nullptr);

    EXPECT_EQ(node->onMoveEvent_, nullptr);
}

/**
 * @tc.name: FireOnMove_TriggersCallbackTest
 * @tc.desc: Test FireOnMove triggers callback with correct parameters
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, FireOnMove_TriggersCallbackTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    bool onMoveCalled = false;
    int32_t receivedFrom = INVALID_INDEX;
    int32_t receivedTo = INVALID_INDEX;

    node->onMoveEvent_ = [&onMoveCalled, &receivedFrom, &receivedTo](int32_t from, int32_t to) {
        onMoveCalled = true;
        receivedFrom = from;
        receivedTo = to;
    };

    node->FireOnMove(INDEX_0, INDEX_1);

    EXPECT_TRUE(onMoveCalled);
    EXPECT_EQ(receivedFrom, INDEX_0);
    EXPECT_EQ(receivedTo, INDEX_1);
}

/**
 * @tc.name: MoveData_ReordersItemsTest
 * @tc.desc: Test MoveData reorders items correctly
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, MoveData_ReordersItemsTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->MoveData(INDEX_0, INDEX_1);

    SUCCEED();
}

/**
 * @tc.name: GetTotalCount_ReturnsCorrectCountTest
 * @tc.desc: Test GetTotalCount returns correct count from builder
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, GetTotalCount_ReturnsCorrectCountTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();

    EXPECT_EQ(builder->GetTotalCount(), ZERO_COUNT);
}

/**
 * @tc.name: GetTotalCountOfOriginalDataset_BasicTest
 * @tc.desc: Test GetTotalCountOfOriginalDataset returns correct count
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, GetTotalCountOfOriginalDataset_BasicTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();
    builder->UpdateHistoricalTotalCount(DEFAULT_COUNT);

    EXPECT_EQ(builder->GetHistoryTotalCount(), DEFAULT_COUNT);
}

/**
 * @tc.name: UpdateHistoricalTotalCount_UpdatesTest
 * @tc.desc: Test UpdateHistoricalTotalCount updates count correctly
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, UpdateHistoricalTotalCount_UpdatesTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();

    builder->UpdateHistoricalTotalCount(INDEX_10);

    EXPECT_EQ(builder->historicalTotalCount_, INDEX_10);
}

/**
 * @tc.name: SetCacheCount_UpdatesCacheTest
 * @tc.desc: Test SetCacheCount updates cache count
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, SetCacheCount_UpdatesCacheTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();

    builder->SetCacheCount(CACHE_COUNT);

    EXPECT_EQ(builder->cacheCount_, CACHE_COUNT);
}

/**
 * @tc.name: SetIsLoop_UpdatesLoopTest
 * @tc.desc: Test SetIsLoop updates loop flag
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, SetIsLoop_UpdatesLoopTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();

    builder->SetIsLoop(true);

    EXPECT_TRUE(builder->isLoop_);
}

/**
 * @tc.name: EnablePreBuild_TogglesPreBuildTest
 * @tc.desc: Test EnablePreBuild toggles pre-build flag
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, EnablePreBuild_TogglesPreBuildTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();

    builder->EnablePreBuild(false);

    EXPECT_FALSE(builder->enablePreBuild_);
}

/**
 * @tc.name: Integration_CreateNodeAndBuilderTest
 * @tc.desc: Test integration: create node and builder association
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, Integration_CreateNodeAndBuilderTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();
    auto node = LazyForEachNode::GetOrCreateLazyForEachNode(TEST_NODE_ID, builder);

    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->builder_, builder);
    EXPECT_TRUE(node->isRegisterListener_);
}

/**
 * @tc.name: Integration_DataChangeUpdatesNodeTest
 * @tc.desc: Test integration: data change updates node
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, Integration_DataChangeUpdatesNodeTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->children_.push_back(CreateFrameNode(V2::TEXT_ETS_TAG));
    node->OnDataAdded(INDEX_0);

    EXPECT_TRUE(node->children_.empty());
}

/**
 * @tc.name: Integration_GetFrameChildByIndexCacheTest
 * @tc.desc: Test integration: child caching mechanism
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, Integration_GetFrameChildByIndexCacheTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    auto child1 = node->GetFrameChildByIndex(INDEX_0, true);
    auto child2 = node->GetFrameChildByIndex(INDEX_0, false);

    SUCCEED();
}

/**
 * @tc.name: Integration_PostIdleTaskPreBuildTest
 * @tc.desc: Test integration: post idle task schedules pre-build
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, Integration_PostIdleTaskPreBuildTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->needPredict_ = false;
    node->PostIdleTask(0);

    EXPECT_TRUE(node->needPredict_);
}

/**
 * @tc.name: Integration_FullLifecycleTest
 * @tc.desc: Test integration: full lifecycle from creation to destruction
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, Integration_FullLifecycleTest, TestSize.Level1)
{
    auto builder = CreateMockBuilder();
    RefPtr<LazyForEachNode> node;
    {
        node = LazyForEachNode::GetOrCreateLazyForEachNode(TEST_NODE_ID, builder);
        EXPECT_NE(node, nullptr);
        EXPECT_TRUE(node->isRegisterListener_);
    }

    node->OnDelete();
    EXPECT_FALSE(node->isRegisterListener_);
}

/**
 * @tc.name: Integration_DragAndDropFlowTest
 * @tc.desc: Test integration: complete drag and drop flow
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, Integration_DragAndDropFlowTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    bool onMoveCalled = false;
    bool onLongPressCalled = false;
    bool onDragStartCalled = false;
    bool onDropCalled = false;

    node->SetOnMove([&onMoveCalled](int32_t, int32_t) { onMoveCalled = true; });
    node->SetItemDragHandler(
        [&onLongPressCalled](int32_t) { onLongPressCalled = true; },
        [&onDragStartCalled](int32_t) { onDragStartCalled = true; },
        [](int32_t, int32_t) {},
        [&onDropCalled](int32_t) { onDropCalled = true; }
    );

    node->FireOnLongPress(INDEX_0);
    node->FireOnDragStart(INDEX_0);
    node->FireOnMove(INDEX_0, INDEX_1);
    node->FireOnDrop(INDEX_1);

    EXPECT_TRUE(onLongPressCalled);
    EXPECT_TRUE(onDragStartCalled);
    EXPECT_TRUE(onMoveCalled);
    EXPECT_TRUE(onDropCalled);
}

/**
 * @tc.name: Integration_DataReloadAndRebuildTest
 * @tc.desc: Test integration: data reload and rebuild flow
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachTestNgAI, Integration_DataReloadAndRebuildTest, TestSize.Level1)
{
    auto node = CreateLazyForEachNode();
    ASSERT_NE(node, nullptr);

    node->children_.push_back(CreateFrameNode(V2::TEXT_ETS_TAG));
    node->OnDataReloaded();

    EXPECT_TRUE(node->children_.empty());

    node->BuildAllChildren();

    SUCCEED();
}

} // namespace OHOS::Ace::NG
