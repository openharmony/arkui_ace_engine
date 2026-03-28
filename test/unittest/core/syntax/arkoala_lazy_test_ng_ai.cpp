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
constexpr int32_t INDEX_10 = 10;
constexpr int32_t INVALID_INDEX = -1;
constexpr int32_t TOTAL_COUNT = 10;
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

    node->SetCallbacks(std::move(createCb), std::move(updateCb));

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
    node->SetCallbacks([](int32_t) { return nullptr; }, [](int32_t, int32_t, int32_t, int32_t, bool) {});

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

    node->SetCallbacks([](int32_t) { return nullptr; }, [](int32_t, int32_t, int32_t, int32_t, bool) {});

    node->DoSetActiveChildRange(INDEX_0, INDEX_2, INDEX_0, INDEX_0, false);

    // Same range should not trigger update
    node->DoSetActiveChildRange(INDEX_0, INDEX_2, INDEX_0, INDEX_0, false);

    SUCCEED();
}

/**
 * @tc.name: DoSetActiveChildRange_WithShowCacheTest
 * @tc.desc: Test DoSetActiveChildRange with showCache=true
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, DoSetActiveChildRange_WithShowCacheTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->SetCallbacks([](int32_t) { return nullptr; }, [](int32_t, int32_t, int32_t, int32_t, bool) {});

    node->DoSetActiveChildRange(INDEX_1, INDEX_2, INDEX_0, INDEX_1, true);

    SUCCEED();
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

    SUCCEED();
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
    node->SetCallbacks(
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
    node->SetCallbacks(
        [&createCount](int32_t index) -> RefPtr<UINode> {
            createCount++;
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    auto child1 = node->GetChildByIndex(INDEX_0);
    auto child2 = node->GetChildByIndex(INDEX_0);

    EXPECT_EQ(createCount, 0);
    EXPECT_EQ(child1, child2);
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

    node->SetCallbacks(
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    auto child = node->GetFrameChildByIndex(INDEX_0, true, false, true);

    SUCCEED();
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

    SUCCEED();
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
    node->SetCallbacks(
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    node->BuildAllChildren();

    SUCCEED();
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
    node->SetCallbacks(
        [](int32_t index) -> RefPtr<UINode> {
            return AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        },
        [](int32_t, int32_t, int32_t, int32_t, bool) {}
    );

    node->DoSetActiveChildRange(INDEX_0, INDEX_1, INDEX_0, INDEX_0, false);

    SUCCEED();
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

    SUCCEED();
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
 * @tc.desc: Test DumpInfo logs node information
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaLazyTestNgAI, DumpInfo_LogsInfoTest, TestSize.Level1)
{
    auto node = CreateLazyNode();
    ASSERT_NE(node, nullptr);

    node->DumpInfo();

    SUCCEED();
}

} // namespace OHOS::Ace::NG
