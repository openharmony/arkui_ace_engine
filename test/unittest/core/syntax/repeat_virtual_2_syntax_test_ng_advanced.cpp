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

#include <optional>
#include <utility>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID_1 = 100;
constexpr int32_t NODE_ID_2 = 200;
constexpr uint32_t ARR_LEN_5 = 5;
constexpr uint32_t ARR_LEN_10 = 10;
constexpr uint32_t TOTAL_COUNT_5 = 5;
constexpr uint32_t TOTAL_COUNT_10 = 10;
constexpr uint32_t TOTAL_COUNT_20 = 20;
constexpr uint32_t INDEX_0 = 0;
constexpr uint32_t INDEX_1 = 1;
constexpr uint32_t INDEX_2 = 2;
constexpr uint32_t INDEX_5 = 5;
constexpr uint32_t INDEX_10 = 10;
constexpr int32_t START_INDEX_0 = 0;
constexpr int32_t START_INDEX_5 = 5;
constexpr int32_t COUNT_3 = 3;
constexpr int32_t COUNT_5 = 5;
} // namespace

class RepeatVirtual2AdvancedTestNg : public testing::Test {
public:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }

    RefPtr<FrameNode> CreateNode(const std::string& tag, int32_t elmtId)
    {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, elmtId, pattern);
        pattern->AttachToFrameNode(frameNode);
        ViewStackProcessor::GetInstance()->Push(frameNode);
        return frameNode;
    }
};

auto g_onGetRid4Index = [](uint32_t index) -> std::pair<RIDType, uint32_t> {
    return { index, index };
};

auto g_onRecycleItems = [](int32_t from, int32_t to) {};

auto g_onActiveRange = [](int32_t start, int32_t end, int32_t nStart, int32_t nEnd, bool isLoop, bool force) {};

auto g_onMoveFromTo = [](int32_t from, int32_t to) {};

auto g_onPurge = []() {};

auto g_onUpdateDirty = []() {};

/**
 * @tc.name: RepeatVirtual2GetOrCreateRepeatNodeTest001
 * @tc.desc: Test GetOrCreateRepeatNode with various parameters
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2GetOrCreateRepeatNodeTest001, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTotalCount(), TOTAL_COUNT_5);
}

/**
 * @tc.name: RepeatVirtual2GetOrCreateRepeatNodeSameIdTest002
 * @tc.desc: Test GetOrCreateRepeatNode with same nodeId returns same instance
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2GetOrCreateRepeatNodeSameIdTest002, TestSize.Level1)
{
    auto node1 = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    auto node2 = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_10, TOTAL_COUNT_10,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    EXPECT_EQ(node1, node2);
}

/**
 * @tc.name: RepeatVirtual2UpdateArrLenTest003
 * @tc.desc: Test UpdateArrLen with various sizes
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2UpdateArrLenTest003, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->UpdateArrLen(ARR_LEN_10);
    node->UpdateArrLen(ARR_LEN_5);
}

/**
 * @tc.name: RepeatVirtual2GetTotalCountTest004
 * @tc.desc: Test GetTotalCount returns correct count
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2GetTotalCountTest004, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_10,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    auto totalCount = node->GetTotalCount();
    EXPECT_EQ(totalCount, TOTAL_COUNT_10);
}

/**
 * @tc.name: RepeatVirtual2FrameCountTest005
 * @tc.desc: Test FrameCount returns correct count
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2FrameCountTest005, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    auto frameCount = node->FrameCount();
    EXPECT_GE(frameCount, 0);
}

/**
 * @tc.name: RepeatVirtual2RequestContainerReLayoutTest006
 * @tc.desc: Test RequestContainerReLayout with various startIndex values
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2RequestContainerReLayoutTest006, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->RequestContainerReLayout(START_INDEX_0);
    node->RequestContainerReLayout(START_INDEX_5);
}

/**
 * @tc.name: RepeatVirtual2NotifyContainerLayoutChangeTest007
 * @tc.desc: Test NotifyContainerLayoutChange with different parameters
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2NotifyContainerLayoutChangeTest007, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->NotifyContainerLayoutChange(INDEX_0, COUNT_3, UINode::NotificationType::START_CHANGE_POSITION);
    node->NotifyContainerLayoutChange(INDEX_5, COUNT_5, UINode::NotificationType::END_CHANGE_POSITION);
}

/**
 * @tc.name: RepeatVirtual2GetChildrenTest008
 * @tc.desc: Test GetChildren with notDetach parameter
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2GetChildrenTest008, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    (void)node->GetChildren(false);
    (void)node->GetChildren(true);
}

/**
 * @tc.name: RepeatVirtual2GetChildrenForInspectorTest009
 * @tc.desc: Test GetChildrenForInspector with needCacheNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2GetChildrenForInspectorTest009, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    (void)node->GetChildrenForInspector(false);
    (void)node->GetChildrenForInspector(true);
}

/**
 * @tc.name: RepeatVirtual2DoSetActiveChildRangeTest010
 * @tc.desc: Test DoSetActiveChildRange with start and end indices
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2DoSetActiveChildRangeTest010, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_10, TOTAL_COUNT_10,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->DoSetActiveChildRange(INDEX_0, INDEX_5, INDEX_0, INDEX_0);
    node->DoSetActiveChildRange(INDEX_2, INDEX_5, INDEX_0, INDEX_2, true);
}

/**
 * @tc.name: RepeatVirtual2DoSetActiveChildRangeSetBasedTest011
 * @tc.desc: Test DoSetActiveChildRange with set-based parameters
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2DoSetActiveChildRangeSetBasedTest011, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    std::set<int32_t> activeItems = {0, 1, 2};
    std::set<int32_t> cachedItems = {0, 1, 2, 3, 4};
    node->DoSetActiveChildRange(activeItems, cachedItems, INDEX_0);
}

/**
 * @tc.name: RepeatVirtual2RecycleItemsTest012
 * @tc.desc: Test RecycleItems with various ranges
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2RecycleItemsTest012, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_10, TOTAL_COUNT_10,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->RecycleItems(INDEX_0, INDEX_2);
    node->RecycleItems(INDEX_5, INDEX_10);
}

/**
 * @tc.name: RepeatVirtual2SetNodeIndexOffsetTest013
 * @tc.desc: Test SetNodeIndexOffset affects index calculations
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetNodeIndexOffsetTest013, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->SetNodeIndexOffset(START_INDEX_0, COUNT_3);
    node->SetNodeIndexOffset(START_INDEX_5, COUNT_5);
}

/**
 * @tc.name: RepeatVirtual2GetFrameChildByIndexTest014
 * @tc.desc: Test GetFrameChildByIndex with various parameters
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2GetFrameChildByIndexTest014, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    (void)node->GetFrameChildByIndex(INDEX_0, false, false, true);
    (void)node->GetFrameChildByIndex(INDEX_2, true, false, true);
}

/**
 * @tc.name: RepeatVirtual2SetOnMoveTest015
 * @tc.desc: Test SetOnMove callback registration
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetOnMoveTest015, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    auto onMoveFunc = [](int32_t from, int32_t to) {};
    node->SetOnMove(std::move(onMoveFunc));
}

/**
 * @tc.name: RepeatVirtual2SetItemDragHandlerTest016
 * @tc.desc: Test SetItemDragHandler registration
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetItemDragHandlerTest016, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t index, int32_t targetIndex) {};
    auto onDrop = [](int32_t index) {};

    node->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
}

/**
 * @tc.name: RepeatVirtual2MoveDataTest017
 * @tc.desc: Test MoveData with various indices
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2MoveDataTest017, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->MoveData(INDEX_0, INDEX_2);
    node->MoveData(INDEX_1, INDEX_5);
}

/**
 * @tc.name: RepeatVirtual2FireOnMoveTest018
 * @tc.desc: Test FireOnMove triggers registered callback
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2FireOnMoveTest018, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    auto onMoveFunc = [](int32_t from, int32_t to) {};
    node->SetOnMove(std::move(onMoveFunc));
    node->FireOnMove(INDEX_0, INDEX_2);
}

/**
 * @tc.name: RepeatVirtual2InitDragManagerTest019
 * @tc.desc: Test InitDragManager with various node types
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2InitDragManagerTest019, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    auto child = CreateNode(V2::TEXT_ETS_TAG, 1);
    node->InitDragManager(child);
}

/**
 * @tc.name: RepeatVirtual2InitAllChildrenDragManagerTest020
 * @tc.desc: Test InitAllChildrenDragManager edge cases
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2InitAllChildrenDragManagerTest020, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->InitAllChildrenDragManager(true);
    node->InitAllChildrenDragManager(false);
}

/**
 * @tc.name: RepeatVirtual2GetFrameNodeTest021
 * @tc.desc: Test GetFrameNode retrieval
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2GetFrameNodeTest021, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    (void)node->GetFrameNode(INDEX_0);
}

/**
 * @tc.name: RepeatVirtual2GetFrameNodeIndexTest022
 * @tc.desc: Test GetFrameNodeIndex with various states
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2GetFrameNodeIndexTest022, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG, 1);
    auto index = node->GetFrameNodeIndex(frameNode);
    EXPECT_GE(index, -1);
}

/**
 * @tc.name: RepeatVirtual2OnConfigurationUpdateTest023
 * @tc.desc: Test OnConfigurationUpdate with different config types
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2OnConfigurationUpdateTest023, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    ConfigurationChange config;
    config.colorModeUpdate = true;
    node->OnConfigurationUpdate(config);
}

/**
 * @tc.name: RepeatVirtual2NotifyColorModeChangeTest024
 * @tc.desc: Test NotifyColorModeChange with various modes
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2NotifyColorModeChangeTest024, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->NotifyColorModeChange(0);
    node->NotifyColorModeChange(1);
}

/**
 * @tc.name: RepeatVirtual2SetJSViewActiveTest025
 * @tc.desc: Test SetJSViewActive propagation to children
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetJSViewActiveTest025, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->SetJSViewActive(true);
    node->SetJSViewActive(false);
}

/**
 * @tc.name: RepeatVirtual2PaintDebugBoundaryTreeAllTest026
 * @tc.desc: Test PaintDebugBoundaryTreeAll recursive behavior
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2PaintDebugBoundaryTreeAllTest026, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->PaintDebugBoundaryTreeAll(true);
    node->PaintDebugBoundaryTreeAll(false);
}

/**
 * @tc.name: RepeatVirtual2RemoveNodeTest027
 * @tc.desc: Test RemoveNode with various RID values
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2RemoveNodeTest027, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->RemoveNode(0);
    node->RemoveNode(100);
}

/**
 * @tc.name: RepeatVirtual2SetInvalidTest028
 * @tc.desc: Test SetInvalid verification
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetInvalidTest028, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->SetInvalid(0);
    node->SetInvalid(100);
}

/**
 * @tc.name: RepeatVirtual2UpdateL1Rid4IndexTest029
 * @tc.desc: Test UpdateL1Rid4Index with complex mappings
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2UpdateL1Rid4IndexTest029, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    std::map<int32_t, uint32_t> l1Rid4Index;
    l1Rid4Index[0] = 0;
    l1Rid4Index[2] = 200;
    l1Rid4Index[5] = 500;
    node->UpdateL1Rid4Index(l1Rid4Index);
}

/**
 * @tc.name: RepeatVirtual2SetIsLoopTest030
 * @tc.desc: Test SetIsLoop impact on behavior
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetIsLoopTest030, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->SetIsLoop(true);
    node->SetIsLoop(false);
}

/**
 * @tc.name: RepeatVirtual2FireOnUpdateDirtyTest031
 * @tc.desc: Test fireOnUpdateDirty callback testing
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2FireOnUpdateDirtyTest031, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->fireOnUpdateDirty();
}

/**
 * @tc.name: RepeatVirtual2IsAtomicNodeTest032
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2IsAtomicNodeTest032, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(node->IsAtomicNode());
}

/**
 * @tc.name: RepeatVirtual2UpdateTotalCountTest033
 * @tc.desc: Test UpdateTotalCount with various values
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2UpdateTotalCountTest033, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    node->UpdateTotalCount(TOTAL_COUNT_10);
    EXPECT_EQ(node->GetTotalCount(), TOTAL_COUNT_10);

    node->UpdateTotalCount(TOTAL_COUNT_20);
    EXPECT_EQ(node->GetTotalCount(), TOTAL_COUNT_20);
}

/**
 * @tc.name: RepeatVirtual2DifferentNodeIdsTest034
 * @tc.desc: Test different nodeIds return different instances
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2DifferentNodeIdsTest034, TestSize.Level1)
{
    auto node1 = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    auto node2 = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_2, ARR_LEN_10, TOTAL_COUNT_10,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    EXPECT_NE(node1, node2);
}

/**
 * @tc.name: RepeatVirtual2EmptyChildrenTest035
 * @tc.desc: Test behavior with empty children
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2EmptyChildrenTest035, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    (void)node->GetChildren(false);
}

} // namespace OHOS::Ace::NG
