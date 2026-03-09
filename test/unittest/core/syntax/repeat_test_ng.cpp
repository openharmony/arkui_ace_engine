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
#include "core/components_ng/syntax/repeat_node.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t TEST_NODE_ID_2 = 200;
constexpr int32_t INVALID_NODE_ID = -1;
constexpr bool IS_ATOMIC_NODE = false;
constexpr int32_t TEST_MOVE_FROM = 1;
constexpr int32_t TEST_MOVE_TO = 3;
constexpr int32_t TEST_INDEX = 0;
constexpr int32_t TEST_INDEX_OUT_OF_RANGE = 100;
constexpr uint32_t TEST_MOVE_CHILD_INDEX = 2;
constexpr int32_t TEST_ACTIVE_START = 0;
constexpr int32_t TEST_ACTIVE_END = 5;
constexpr int32_t TEST_CACHE_START = 1;
constexpr int32_t TEST_CACHE_END = 2;
constexpr int32_t TEST_CHILD_NODE_ID_1 = 1;
constexpr int32_t TEST_CHILD_NODE_ID_2 = 2;
constexpr int32_t TEST_CHILD_NODE_ID_3 = 3;
constexpr int32_t TEST_LOOP_COUNT = 5;
constexpr int32_t TEST_CHILD_COUNT = 3;
constexpr int32_t TEST_ADJUST_INDEX_1 = 2;
constexpr int32_t TEST_ADJUST_INDEX_2 = 4;
constexpr int32_t TEST_ADJUST_INDEX_3 = 5;
constexpr int32_t TEST_ADJUST_INDEX_4 = 3;
constexpr int32_t TEST_PARENT_NODE_ID = 1;
constexpr int32_t TEST_FIRE_INDEX_1 = 1;
constexpr int32_t TEST_FIRE_INDEX_2 = 2;
constexpr int32_t TEST_FIRE_SAME_INDEX = 1;
constexpr int32_t TEST_FIRST_CHILD_INDEX = 0;
const std::string TEST_KEY_1 = "key_1";
const std::string TEST_KEY_2 = "key_2";
const std::string TEST_KEY_3 = "key_3";
} // namespace

class RepeatNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void RepeatNodeTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void RepeatNodeTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void RepeatNodeTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void RepeatNodeTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RepeatNodeGetOrCreateTest001
 * @tc.desc: GetOrCreateRepeatNode creates new node when node does not exist
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeGetOrCreateTest001, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    EXPECT_TRUE(repeatNode != nullptr);
    EXPECT_EQ(repeatNode->GetTag(), V2::JS_REPEAT_ETS_TAG);
}

/**
 * @tc.name: RepeatNodeGetOrCreateTest002
 * @tc.desc: GetOrCreateRepeatNode returns existing node when node already exists
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeGetOrCreateTest002, TestSize.Level1)
{
    auto repeatNode1 = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto repeatNode2 = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    EXPECT_EQ(repeatNode1, repeatNode2);
}

/**
 * @tc.name: RepeatNodeGetOrCreateTest003
 * @tc.desc: GetOrCreateRepeatNode creates different nodes for different IDs
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeGetOrCreateTest003, TestSize.Level1)
{
    auto repeatNode1 = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto repeatNode2 = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID_2);
    EXPECT_TRUE(repeatNode1 != nullptr);
    EXPECT_TRUE(repeatNode2 != nullptr);
    EXPECT_NE(repeatNode1, repeatNode2);
}

/**
 * @tc.name: RepeatNodeIsAtomicNodeTest004
 * @tc.desc: IsAtomicNode returns false for RepeatNode
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeIsAtomicNodeTest004, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    EXPECT_EQ(repeatNode->IsAtomicNode(), IS_ATOMIC_NODE);
}

/**
 * @tc.name: RepeatNodeCreateTempItemsTest005
 * @tc.desc: CreateTempItems swaps ids and tempIds correctly
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeCreateTempItemsTest005, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    std::list<std::string> ids = { TEST_KEY_1, TEST_KEY_2, TEST_KEY_3 };
    repeatNode->SetIds(std::move(ids));
    EXPECT_TRUE(repeatNode->GetTempIds().empty());
    repeatNode->CreateTempItems();
    auto tempIds = repeatNode->GetTempIds();
    EXPECT_EQ(tempIds.size(), static_cast<size_t>(3));
}

/**
 * @tc.name: RepeatNodeCreateTempItemsTest006
 * @tc.desc: CreateTempItems swaps children correctly
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeCreateTempItemsTest006, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto childNode1 = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_1, AceType::MakeRefPtr<Pattern>());
    auto childNode2 = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_2, AceType::MakeRefPtr<Pattern>());
    repeatNode->AddChild(childNode1);
    repeatNode->AddChild(childNode2);
    EXPECT_EQ(repeatNode->GetChildren().size(), static_cast<size_t>(TEST_CHILD_NODE_ID_2));
    repeatNode->CreateTempItems();
    EXPECT_EQ(repeatNode->GetChildren().size(), static_cast<size_t>(TEST_INDEX));
}

/**
 * @tc.name: RepeatNodeFlushUpdateAndMarkDirtyTest007
 * @tc.desc: FlushUpdateAndMarkDirty clears tempIds and marks dirty
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeFlushUpdateAndMarkDirtyTest007, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    std::list<std::string> ids = { TEST_KEY_1, TEST_KEY_2 };
    repeatNode->SetIds(std::move(ids));
    repeatNode->CreateTempItems();
    EXPECT_FALSE(repeatNode->GetTempIds().empty());
    repeatNode->FlushUpdateAndMarkDirty();
    EXPECT_TRUE(repeatNode->GetTempIds().empty());
}

/**
 * @tc.name: RepeatNodeMoveDataTest008
 * @tc.desc: MoveData with from equal to to returns early
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeMoveDataTest008, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto childNode1 = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_1, AceType::MakeRefPtr<Pattern>());
    auto childNode2 = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_2, AceType::MakeRefPtr<Pattern>());
    auto childNode3 = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_3, AceType::MakeRefPtr<Pattern>());
    repeatNode->AddChild(childNode1);
    repeatNode->AddChild(childNode2);
    repeatNode->AddChild(childNode3);
    repeatNode->MoveData(TEST_MOVE_FROM, TEST_MOVE_FROM);
    EXPECT_EQ(repeatNode->GetChildren().size(), static_cast<size_t>(TEST_CHILD_NODE_ID_3));
}

/**
 * @tc.name: RepeatNodeMoveDataTest009
 * @tc.desc: MoveData with negative from returns early
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeMoveDataTest009, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto childNode1 = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_1, AceType::MakeRefPtr<Pattern>());
    repeatNode->AddChild(childNode1);
    repeatNode->MoveData(INVALID_NODE_ID, TEST_MOVE_TO);
    EXPECT_EQ(repeatNode->GetChildren().size(), static_cast<size_t>(TEST_CHILD_NODE_ID_1));
}

/**
 * @tc.name: RepeatNodeMoveDataTest010
 * @tc.desc: MoveData with negative to returns early
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeMoveDataTest010, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto childNode1 = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_1, AceType::MakeRefPtr<Pattern>());
    repeatNode->AddChild(childNode1);
    repeatNode->MoveData(TEST_MOVE_FROM, INVALID_NODE_ID);
    EXPECT_EQ(repeatNode->GetChildren().size(), static_cast<size_t>(TEST_CHILD_NODE_ID_1));
}

/**
 * @tc.name: RepeatNodeMoveDataTest011
 * @tc.desc: MoveData moves child from one position to another
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeMoveDataTest011, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    for (int32_t i = 0; i < TEST_LOOP_COUNT; ++i) {
        auto childNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i, AceType::MakeRefPtr<Pattern>());
        repeatNode->AddChild(childNode);
    }
    repeatNode->MoveData(TEST_MOVE_FROM, TEST_MOVE_TO);
    EXPECT_EQ(repeatNode->from_, TEST_MOVE_FROM);
    EXPECT_EQ(repeatNode->to_, TEST_MOVE_TO);
}

/**
 * @tc.name: RepeatNodeMoveDataTest012
 * @tc.desc: MoveData resets from_ and to_ when they are equal after adjustment
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeMoveDataTest012, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    for (int32_t i = 0; i < TEST_LOOP_COUNT; ++i) {
        auto childNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i, AceType::MakeRefPtr<Pattern>());
        repeatNode->AddChild(childNode);
    }
    repeatNode->MoveData(TEST_CHILD_NODE_ID_2, TEST_CHILD_NODE_ID_2);
    EXPECT_EQ(repeatNode->from_, INVALID_NODE_ID);
    EXPECT_EQ(repeatNode->to_, INVALID_NODE_ID);
}

/**
 * @tc.name: RepeatNodeGetFrameNodeTest013
 * @tc.desc: GetFrameNode returns null when index is out of range
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeGetFrameNodeTest013, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto frameNode = repeatNode->GetFrameNode(TEST_INDEX_OUT_OF_RANGE);
    EXPECT_TRUE(frameNode == nullptr);
}

/**
 * @tc.name: RepeatNodeGetFrameNodeTest014
 * @tc.desc: GetFrameNode returns FrameNode at valid index
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeGetFrameNodeTest014, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto childFrameNode = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_1, AceType::MakeRefPtr<Pattern>());
    repeatNode->AddChild(childFrameNode);
    auto frameNode = repeatNode->GetFrameNode(TEST_INDEX);
    EXPECT_TRUE(frameNode != nullptr);
}

/**
 * @tc.name: RepeatNodeAfterAddChildTest015
 * @tc.desc: AfterAddChild does not crash when children list is empty
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeAfterAddChildTest015, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    repeatNode->AfterAddChild();
    SUCCEED();
}

/**
 * @tc.name: RepeatNodeAfterAddChildTest016
 * @tc.desc: AfterAddChild initializes drag manager for last child
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeAfterAddChildTest016, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto childNode = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_1, AceType::MakeRefPtr<Pattern>());
    repeatNode->AddChild(childNode);
    repeatNode->AfterAddChild();
    SUCCEED();
}

/**
 * @tc.name: RepeatNodeSetOnMoveTest017
 * @tc.desc: SetOnMove sets onMoveEvent callback
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeSetOnMoveTest017, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    repeatNode->SetOnMove(std::move(onMoveCallback));
    EXPECT_FALSE(repeatNode->onMoveEvent_ != nullptr);
}

/**
 * @tc.name: RepeatNodeSetOnMoveTest018
 * @tc.desc: SetOnMove with null callback clears onMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeSetOnMoveTest018, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    repeatNode->SetOnMove(std::move(onMoveCallback));
    repeatNode->SetOnMove(nullptr);
    EXPECT_TRUE(repeatNode->onMoveEvent_ == nullptr);
}

/**
 * @tc.name: RepeatNodeSetItemDragHandlerTest019
 * @tc.desc: SetItemDragHandler sets drag handlers when onMoveEvent is set
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeSetItemDragHandlerTest019, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    repeatNode->SetOnMove(std::move(onMoveCallback));
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    repeatNode->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    EXPECT_FALSE(repeatNode->onLongPressEvent_ != nullptr);
    EXPECT_FALSE(repeatNode->onDragStartEvent_ != nullptr);
    EXPECT_FALSE(repeatNode->onMoveThroughEvent_ != nullptr);
    EXPECT_FALSE(repeatNode->onDropEvent_ != nullptr);
}

/**
 * @tc.name: RepeatNodeSetItemDragHandlerTest020
 * @tc.desc: SetItemDragHandler does not set handlers when onMoveEvent is null
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeSetItemDragHandlerTest020, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    repeatNode->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    EXPECT_TRUE(repeatNode->onLongPressEvent_ == nullptr);
    EXPECT_TRUE(repeatNode->onDragStartEvent_ == nullptr);
    EXPECT_TRUE(repeatNode->onMoveThroughEvent_ == nullptr);
    EXPECT_TRUE(repeatNode->onDropEvent_ == nullptr);
}

/**
 * @tc.name: RepeatNodeGetActiveRangeTest021
 * @tc.desc: GetActiveRange returns correct range after DoSetActiveChildRange
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeGetActiveRangeTest021, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    repeatNode->DoSetActiveChildRange(TEST_ACTIVE_START, TEST_ACTIVE_END,
        TEST_CACHE_START, TEST_CACHE_END, false);
    auto range = repeatNode->GetActiveRange();
    EXPECT_EQ(range.first, TEST_ACTIVE_START - TEST_CACHE_START);
    EXPECT_EQ(range.second, TEST_ACTIVE_END + TEST_CACHE_END);
}

/**
 * @tc.name: RepeatNodeGetActiveRangeTest022
 * @tc.desc: GetActiveRange returns default values before setting
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeGetActiveRangeTest022, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto range = repeatNode->GetActiveRange();
    EXPECT_EQ(range.first, INVALID_NODE_ID);
    EXPECT_EQ(range.second, INVALID_NODE_ID);
}

/**
 * @tc.name: RepeatNodeAdjustFromIndexTest023
 * @tc.desc: AdjustFromIndex returns same index when from_ is negative
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeAdjustFromIndexTest023, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    uint32_t index = 5;
    uint32_t adjustedIndex = repeatNode->AdjustFromIndex(index);
    EXPECT_EQ(adjustedIndex, index);
}

/**
 * @tc.name: RepeatNodeAdjustFromIndexTest024
 * @tc.desc: AdjustFromIndex adjusts index when from_ and to_ are set
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeAdjustFromIndexTest024, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    repeatNode->from_ = TEST_ADJUST_INDEX_1;
    repeatNode->to_ = TEST_ADJUST_INDEX_2;
    uint32_t adjustedIndex = repeatNode->AdjustFromIndex(TEST_ADJUST_INDEX_1);
    EXPECT_EQ(static_cast<int32_t>(adjustedIndex), repeatNode->to_);
}

/**
 * @tc.name: RepeatNodeAdjustFromIndexTest025
 * @tc.desc: AdjustFromIndex decrements index when between from_ and to_
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeAdjustFromIndexTest025, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    repeatNode->from_ = TEST_ADJUST_INDEX_1;
    repeatNode->to_ = TEST_ADJUST_INDEX_3;
    uint32_t index = TEST_ADJUST_INDEX_2;
    uint32_t adjustedIndex = repeatNode->AdjustFromIndex(index);
    EXPECT_EQ(adjustedIndex, static_cast<uint32_t>(TEST_ADJUST_INDEX_4));
}

/**
 * @tc.name: RepeatNodeAdjustFromIndexTest026
 * @tc.desc: AdjustFromIndex increments index when between to_ and from_
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeAdjustFromIndexTest026, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    repeatNode->from_ = TEST_ADJUST_INDEX_3;
    repeatNode->to_ = TEST_ADJUST_INDEX_1;
    uint32_t index = TEST_ADJUST_INDEX_4;
    uint32_t adjustedIndex = repeatNode->AdjustFromIndex(index);
    EXPECT_EQ(adjustedIndex, static_cast<uint32_t>(TEST_ADJUST_INDEX_2));
}

/**
 * @tc.name: RepeatNodeDumpInfoTest027
 * @tc.desc: DumpInfo adds correct descriptions
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeDumpInfoTest027, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    std::list<std::string> ids = { TEST_KEY_1, TEST_KEY_2 };
    repeatNode->SetIds(std::move(ids));
    repeatNode->DumpInfo();
    SUCCEED();
}

/**
 * @tc.name: RepeatNodeIsAllowAnimationTest028
 * @tc.desc: IsAllowAnimation returns false when parent is not List
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeIsAllowAnimationTest028, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto parentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, TEST_PARENT_NODE_ID, AceType::MakeRefPtr<Pattern>());
    repeatNode->SetParent(parentNode);
    EXPECT_FALSE(repeatNode->IsAllowAnimation());
}

/**
 * @tc.name: RepeatNodeIsChildInAnimationTest029
 * @tc.desc: IsChildInAnimation returns false when child index is out of range
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeIsChildInAnimationTest029, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    bool result = repeatNode->IsChildInAnimation(TEST_MOVE_CHILD_INDEX);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: RepeatNodeIsSyntaxNodeTest030
 * @tc.desc: IsSyntaxNode returns true for RepeatNode
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeIsSyntaxNodeTest030, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    EXPECT_TRUE(repeatNode->IsSyntaxNode());
}

/**
 * @tc.name: RepeatNodeMoveChildTest031
 * @tc.desc: MoveChild with index out of range does nothing
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeMoveChildTest031, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    repeatNode->MoveChild(TEST_MOVE_CHILD_INDEX);
    SUCCEED();
}

/**
 * @tc.name: RepeatNodeMoveChildTest032
 * @tc.desc: MoveChild adds child at specified index
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeMoveChildTest032, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto childNode1 = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_1, AceType::MakeRefPtr<Pattern>());
    auto childNode2 = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_2, AceType::MakeRefPtr<Pattern>());
    repeatNode->tempChildrenOfRepeat_.push_back(childNode1);
    repeatNode->tempChildrenOfRepeat_.push_back(childNode2);
    repeatNode->MoveChild(TEST_FIRST_CHILD_INDEX);
    EXPECT_EQ(repeatNode->GetChildren().size(), static_cast<size_t>(TEST_CHILD_NODE_ID_1));
}

/**
 * @tc.name: RepeatNodeFinishRepeatRenderTest033
 * @tc.desc: FinishRepeatRender clears temp containers
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeFinishRepeatRenderTest033, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto childNode1 = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_1, AceType::MakeRefPtr<Pattern>());
    repeatNode->tempChildrenOfRepeat_.push_back(childNode1);
    std::list<int32_t> removedElmtId;
    repeatNode->FinishRepeatRender(removedElmtId);
    EXPECT_TRUE(repeatNode->tempChildrenOfRepeat_.empty());
    EXPECT_EQ(repeatNode->from_, INVALID_NODE_ID);
    EXPECT_EQ(repeatNode->to_, INVALID_NODE_ID);
}

/**
 * @tc.name: RepeatNodeInitAllChildrenDragManagerTest034
 * @tc.desc: InitAllChildrenDragManager returns early when parent is null
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeInitAllChildrenDragManagerTest034, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    repeatNode->InitAllChildrenDragManager(true);
    SUCCEED();
}

/**
 * @tc.name: RepeatNodeInitAllChildrenDragManagerTest035
 * @tc.desc: InitAllChildrenDragManager clears onMoveEvent when parent is not List
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeInitAllChildrenDragManagerTest035, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    repeatNode->SetOnMove(std::move(onMoveCallback));
    auto parentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, TEST_PARENT_NODE_ID, AceType::MakeRefPtr<Pattern>());
    repeatNode->SetParent(parentNode);
    repeatNode->InitAllChildrenDragManager(true);
    EXPECT_TRUE(repeatNode->onMoveEvent_ == nullptr);
}

/**
 * @tc.name: RepeatNodeFireOnMoveTest036
 * @tc.desc: FireOnMove calls onMoveEvent callback when from != to
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeFireOnMoveTest036, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    bool callbackCalled = false;
    auto onMoveCallback = [&callbackCalled](int32_t from, int32_t to) { callbackCalled = true; };
    repeatNode->SetOnMove(std::move(onMoveCallback));
    repeatNode->FireOnMove(TEST_FIRE_INDEX_1, TEST_FIRE_INDEX_2);
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: RepeatNodeFireOnMoveTest037
 * @tc.desc: FireOnMove does not call callback when from == to
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeFireOnMoveTest037, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    bool callbackCalled = false;
    auto onMoveCallback = [&callbackCalled](int32_t from, int32_t to) { callbackCalled = true; };
    repeatNode->SetOnMove(std::move(onMoveCallback));
    repeatNode->FireOnMove(TEST_FIRE_SAME_INDEX, TEST_FIRE_SAME_INDEX);
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: RepeatNodeFireOnLongPressTest038
 * @tc.desc: FireOnLongPress calls onLongPressEvent callback
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeFireOnLongPressTest038, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    bool callbackCalled = false;
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    repeatNode->SetOnMove(std::move(onMoveCallback));
    auto onLongPress = [&callbackCalled](int32_t index) { callbackCalled = true; };
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    repeatNode->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    repeatNode->FireOnLongPress(TEST_FIRST_CHILD_INDEX);
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: RepeatNodeFireOnDragStartTest039
 * @tc.desc: FireOnDragStart calls onDragStartEvent callback
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeFireOnDragStartTest039, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    bool callbackCalled = false;
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    repeatNode->SetOnMove(std::move(onMoveCallback));
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [&callbackCalled](int32_t index) { callbackCalled = true; };
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    repeatNode->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    repeatNode->FireOnDragStart(TEST_FIRST_CHILD_INDEX);
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: RepeatNodeFireOnMoveThroughTest040
 * @tc.desc: FireOnMoveThrough calls onMoveThroughEvent callback
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeFireOnMoveThroughTest040, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    bool callbackCalled = false;
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    repeatNode->SetOnMove(std::move(onMoveCallback));
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [&callbackCalled](int32_t from, int32_t to) { callbackCalled = true; };
    auto onDrop = [](int32_t index) {};
    repeatNode->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    repeatNode->FireOnMoveThrough(TEST_FIRST_CHILD_INDEX, TEST_CACHE_START);
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: RepeatNodeFireOnDropTest041
 * @tc.desc: FireOnDrop calls onDropEvent callback
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeFireOnDropTest041, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    bool callbackCalled = false;
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    repeatNode->SetOnMove(std::move(onMoveCallback));
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [&callbackCalled](int32_t index) { callbackCalled = true; };
    repeatNode->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    repeatNode->FireOnDrop(TEST_FIRST_CHILD_INDEX);
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: RepeatNodeCompleteFlowTest042
 * @tc.desc: Complete flow: CreateTempItems, MoveChild, FinishRepeatRender
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeCompleteFlowTest042, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    std::list<std::string> ids = { TEST_KEY_1, TEST_KEY_2, TEST_KEY_3 };
    repeatNode->SetIds(std::move(ids));
    for (int32_t i = 0; i < TEST_CHILD_COUNT; ++i) {
        auto childNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i, AceType::MakeRefPtr<Pattern>());
        repeatNode->AddChild(childNode);
    }
    repeatNode->CreateTempItems();
    EXPECT_EQ(repeatNode->tempChildrenOfRepeat_.size(), static_cast<size_t>(TEST_CHILD_COUNT));
    repeatNode->MoveChild(0);
    EXPECT_EQ(repeatNode->GetChildren().size(), static_cast<size_t>(1));
    std::list<int32_t> removedElmtId;
    repeatNode->FinishRepeatRender(removedElmtId);
    EXPECT_TRUE(repeatNode->tempChildrenOfRepeat_.empty());
}

/**
 * @tc.name: RepeatNodeInitDragManagerTest043
 * @tc.desc: InitDragManager returns early when onMoveEvent is null
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeInitDragManagerTest043, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto childNode = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, TEST_CHILD_NODE_ID_1, AceType::MakeRefPtr<Pattern>());
    repeatNode->AddChild(childNode);
    repeatNode->InitDragManager(childNode);
    SUCCEED();
}

/**
 * @tc.name: RepeatNodeInitDragManagerTest044
 * @tc.desc: InitDragManager returns early when child is null
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeTestNg, RepeatNodeInitDragManagerTest044, TestSize.Level1)
{
    auto repeatNode = RepeatNode::GetOrCreateRepeatNode(TEST_NODE_ID);
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    repeatNode->SetOnMove(std::move(onMoveCallback));
    repeatNode->InitDragManager(nullptr);
    SUCCEED();
}

} // namespace OHOS::Ace::NG
