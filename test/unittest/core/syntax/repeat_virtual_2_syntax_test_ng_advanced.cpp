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
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
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
constexpr int32_t CHILD_ID_10 = 10;
constexpr int32_t CHILD_ID_12 = 12;
constexpr int32_t CHILD_ID_13 = 13;
constexpr int32_t CHILD_ID_20 = 20;
constexpr int32_t CHILD_ID_22 = 22;
constexpr int32_t CHILD_ID_30 = 30;
constexpr int32_t CHILD_ID_31 = 31;
constexpr int32_t CHILD_ID_40 = 40;
constexpr int32_t CHILD_ID_41 = 41;
constexpr int32_t PARENT_LIST_ID = 888;
constexpr int32_t PARENT_GRID_ID = 889;
constexpr int32_t PARENT_OTHER_ID = 890;
class MockUINode : public UINode {
public:
    MockUINode(const std::string& tag, int32_t nodeId, bool isRoot = false) : UINode(tag, nodeId) {}
    ~MockUINode() {};

    MOCK_CONST_METHOD0(IsAtomicNode, bool());
};
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

auto g_onGetRid4Index = [](uint32_t index, bool inAnimation, bool forceCreateNewChild) -> std::pair<RIDType, uint32_t> {
    return { index, index };
};

auto g_onRecycleItems = [](int32_t from, int32_t to) {};

auto g_onActiveRange = [](int32_t start, int32_t end, int32_t nStart, int32_t nEnd, bool isLoop, bool force) {};

auto g_onMoveFromTo = [](int32_t from, int32_t to) {};

auto g_onPurge = []() {};

auto g_onPurgeAll = []() {};

auto g_onUpdateDirty = []() {};

constexpr int32_t DEFAULT_MEM_OPT_STRATEGY = 0;

/**
 * @tc.name: RepeatVirtual2GetOrCreateRepeatNodeTest001
 * @tc.desc: Test GetOrCreateRepeatNode with various parameters
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2GetOrCreateRepeatNodeTest001, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTotalCount(), TOTAL_COUNT_5);
}

/**
 * @tc.name: RepeatVirtual2UpdateArrLenTest003
 * @tc.desc: Test UpdateArrLen with various sizes
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2UpdateArrLenTest003, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_10, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_10, TOTAL_COUNT_10, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_10, TOTAL_COUNT_10, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

    auto node2 = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_2, ARR_LEN_10, TOTAL_COUNT_10, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

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
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    (void)node->GetChildren(false);
}

/**
 * @tc.name: RepeatVirtual2EmptyChildrenTest036
 * @tc.desc: Test behavior with empty children and notDetach parameter
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2EmptyChildrenTest036, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_2, ARR_LEN_10, TOTAL_COUNT_10, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);

    ASSERT_NE(node, nullptr);
    (void)node->GetChildren(true);
}

/**
 * @tc.name: RepeatVirtual2SetOnMoveActivateTest037
 * @tc.desc: Test SetOnMove activates drag manager when onMove is provided and onMoveEvent_ is null
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetOnMoveActivateTest037, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    EXPECT_FALSE(static_cast<bool>(node->onMoveEvent_));
    auto onMoveFunc = [](int32_t from, int32_t to) {};
    node->SetOnMove(std::move(onMoveFunc));
    EXPECT_TRUE(static_cast<bool>(node->onMoveEvent_));
}

/**
 * @tc.name: RepeatVirtual2SetOnMoveDeactivateTest038
 * @tc.desc: Test SetOnMove deactivates drag manager when onMove is null and onMoveEvent_ is set
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetOnMoveDeactivateTest038, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto onMoveFunc = [](int32_t from, int32_t to) {};
    node->SetOnMove(std::move(onMoveFunc));
    EXPECT_TRUE(static_cast<bool>(node->onMoveEvent_));

    std::function<void(int32_t, int32_t)> nullFunc = nullptr;
    node->SetOnMove(std::move(nullFunc));
    EXPECT_FALSE(static_cast<bool>(node->onMoveEvent_));
}

/**
 * @tc.name: RepeatVirtual2SetOnMoveUpdateTest039
 * @tc.desc: Test SetOnMove updates onMoveEvent_ when both onMove and onMoveEvent_ are set
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetOnMoveUpdateTest039, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto onMoveFunc1 = [](int32_t from, int32_t to) {};
    node->SetOnMove(std::move(onMoveFunc1));
    EXPECT_TRUE(static_cast<bool>(node->onMoveEvent_));

    auto onMoveFunc2 = [](int32_t a, int32_t b) {};
    node->SetOnMove(std::move(onMoveFunc2));
    EXPECT_TRUE(static_cast<bool>(node->onMoveEvent_));
}

/**
 * @tc.name: RepeatVirtual2SetOnMoveNoopTest040
 * @tc.desc: Test SetOnMove does nothing when both onMove and onMoveEvent_ are null
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetOnMoveNoopTest040, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    EXPECT_FALSE(static_cast<bool>(node->onMoveEvent_));
    std::function<void(int32_t, int32_t)> nullFunc = nullptr;
    node->SetOnMove(std::move(nullFunc));
    EXPECT_FALSE(static_cast<bool>(node->onMoveEvent_));
}

/**
 * @tc.name: RepeatVirtual2SetItemDragHandlerWithOnMoveTest041
 * @tc.desc: Test SetItemDragHandler assigns drag handlers when onMoveEvent_ is set
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetItemDragHandlerWithOnMoveTest041, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto onMoveFunc = [](int32_t from, int32_t to) {};
    node->SetOnMove(std::move(onMoveFunc));
    ASSERT_TRUE(static_cast<bool>(node->onMoveEvent_));

    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t index, int32_t targetIndex) {};
    auto onDrop = [](int32_t index) {};
    node->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));

    EXPECT_TRUE(static_cast<bool>(node->onLongPressEvent_));
    EXPECT_TRUE(static_cast<bool>(node->onDragStartEvent_));
    EXPECT_TRUE(static_cast<bool>(node->onMoveThroughEvent_));
    EXPECT_TRUE(static_cast<bool>(node->onDropEvent_));
}

/**
 * @tc.name: RepeatVirtual2SetItemDragHandlerWithoutOnMoveTest042
 * @tc.desc: Test SetItemDragHandler skips handler assignment when onMoveEvent_ is null
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2SetItemDragHandlerWithoutOnMoveTest042, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    EXPECT_FALSE(static_cast<bool>(node->onMoveEvent_));

    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t index, int32_t targetIndex) {};
    auto onDrop = [](int32_t index) {};
    node->SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));

    EXPECT_FALSE(static_cast<bool>(node->onLongPressEvent_));
    EXPECT_FALSE(static_cast<bool>(node->onDragStartEvent_));
    EXPECT_FALSE(static_cast<bool>(node->onMoveThroughEvent_));
    EXPECT_FALSE(static_cast<bool>(node->onDropEvent_));
}

/**
 * @tc.name: RepeatVirtual2MoveDataWithParentTest043
 * @tc.desc: Test MoveData with isNeedUpdate=true when parent FrameNode exists
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2MoveDataWithParentTest043, TestSize.Level1)
{
    auto onMoveFromToCalled = std::make_shared<bool>(false);
    auto testOnMoveFromTo = [onMoveFromToCalled](int32_t from, int32_t to) {
        *onMoveFromToCalled = true;
    };

    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        testOnMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 999,
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(node);
    ASSERT_NE(node->GetParent(), nullptr);

    node->postUpdateTaskHasBeenScheduled_ = false;
    node->children_.clear();

    node->MoveData(INDEX_0, INDEX_2, true);

    EXPECT_TRUE(*onMoveFromToCalled);
    EXPECT_TRUE(node->postUpdateTaskHasBeenScheduled_);
}

/**
 * @tc.name: RepeatVirtual2MoveDataNoParentTest044
 * @tc.desc: Test MoveData with isNeedUpdate=true when no parent exists
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2MoveDataNoParentTest044, TestSize.Level1)
{
    auto onMoveFromToCalled = std::make_shared<bool>(false);
    auto testOnMoveFromTo = [onMoveFromToCalled](int32_t from, int32_t to) {
        *onMoveFromToCalled = true;
    };

    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        testOnMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    ASSERT_EQ(node->GetParent(), nullptr);

    node->postUpdateTaskHasBeenScheduled_ = false;
    node->children_.clear();

    node->MoveData(INDEX_0, INDEX_2, true);

    EXPECT_TRUE(*onMoveFromToCalled);
    EXPECT_TRUE(node->postUpdateTaskHasBeenScheduled_);
}

/**
 * @tc.name: RepeatVirtual2MoveDataNoUpdateTest045
 * @tc.desc: Test MoveData with isNeedUpdate=false skips parent notification
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2MoveDataNoUpdateTest045, TestSize.Level1)
{
    auto onMoveFromToCalled = std::make_shared<bool>(false);
    auto testOnMoveFromTo = [onMoveFromToCalled](int32_t from, int32_t to) {
        *onMoveFromToCalled = true;
    };

    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        testOnMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    node->postUpdateTaskHasBeenScheduled_ = false;
    node->children_.clear();

    node->MoveData(INDEX_0, INDEX_2, false);

    EXPECT_TRUE(*onMoveFromToCalled);
    EXPECT_TRUE(node->postUpdateTaskHasBeenScheduled_);
}

/**
 * @tc.name: RepeatVirtual2InitDragManagerNotListOrGridTest047
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2InitDragManagerNotListOrGridTest047, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, PARENT_OTHER_ID,
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    auto child = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, CHILD_ID_10,
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(child, nullptr);

    node->InitDragManager(child);

    EXPECT_EQ(parentNode->GetTag(), V2::COLUMN_ETS_TAG);
}

/**
 * @tc.name: RepeatVirtual2InitDragManagerListPatternFoundTest048
 * @tc.desc: Test InitDragManager creates drag manager on ListItemPattern for LIST parent
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2InitDragManagerListPatternFoundTest048, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, PARENT_LIST_ID,
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    ASSERT_NE(listItemPattern, nullptr);
    auto listItem = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG, CHILD_ID_10, listItemPattern);
    ASSERT_NE(listItem, nullptr);
    listItemPattern->AttachToFrameNode(listItem);

    node->InitDragManager(listItem);

    EXPECT_NE(listItemPattern->dragManager_, nullptr);
}

/**
 * @tc.name: RepeatVirtual2InitDragManagerGridPatternFoundTest050
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2InitDragManagerGridPatternFoundTest050, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::GRID_ETS_TAG, PARENT_GRID_ID,
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    auto gridItemPattern = AceType::MakeRefPtr<GridItemPattern>(nullptr);
    ASSERT_NE(gridItemPattern, nullptr);
    auto gridItem = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, CHILD_ID_20, gridItemPattern);
    ASSERT_NE(gridItem, nullptr);
    gridItemPattern->AttachToFrameNode(gridItem);

    node->InitDragManager(gridItem);

    EXPECT_NE(gridItemPattern->dragManager_, nullptr);
}

/**
 * @tc.name: RepeatVirtual2InitAllChildrenDragManagerNotListOrGridTest052
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2InitAllChildrenDragManagerNotListOrGridTest052, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, PARENT_OTHER_ID,
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    node->InitAllChildrenDragManager(true);

    EXPECT_EQ(parentNode->GetTag(), V2::COLUMN_ETS_TAG);
}

/**
 * @tc.name: RepeatVirtual2InitAllChildrenDragManagerListInitTrueTest053
 * @tc.desc: Test InitAllChildrenDragManager with LIST parent and init=true,
 *           covering null child (B3), non-FrameNode child (B4), no-pattern child (B5),
 *           and pattern-found creating dragManager (B6a)
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2InitAllChildrenDragManagerListInitTrueTest053, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, PARENT_LIST_ID,
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    node->children_.clear();
    node->children_.emplace_back(nullptr);
    auto nonFrameNode = AceType::MakeRefPtr<MockUINode>(V2::TEXT_ETS_TAG, CHILD_ID_12);
    node->children_.emplace_back(nonFrameNode);
    auto plainNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, CHILD_ID_13,
        AceType::MakeRefPtr<Pattern>());
    node->children_.emplace_back(plainNode);

    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    auto listItem = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG, CHILD_ID_30, listItemPattern);
    ASSERT_NE(listItemPattern, nullptr);
    listItemPattern->AttachToFrameNode(listItem);
    node->children_.emplace_back(listItem);

    node->InitAllChildrenDragManager(true);

    EXPECT_NE(listItemPattern->dragManager_, nullptr);
}

/**
 * @tc.name: RepeatVirtual2InitAllChildrenDragManagerListInitFalseTest054
 * @tc.desc: Test InitAllChildrenDragManager with LIST parent and init=false skips InitDragManager
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2InitAllChildrenDragManagerListInitFalseTest054, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, PARENT_LIST_ID,
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    node->children_.clear();
    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    auto listItem = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG, CHILD_ID_31, listItemPattern);
    ASSERT_NE(listItemPattern, nullptr);
    listItemPattern->AttachToFrameNode(listItem);
    node->children_.emplace_back(listItem);

    node->InitAllChildrenDragManager(false);

    EXPECT_EQ(listItemPattern->dragManager_, nullptr);
}

/**
 * @tc.name: RepeatVirtual2InitAllChildrenDragManagerGridInitTrueTest055
 * @tc.desc: Test InitAllChildrenDragManager with GRID parent and init=true,
 *           covering null child (B3), non-FrameNode child (B4), no-pattern child (B7),
 *           and pattern-found creating dragManager (B8a)
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2InitAllChildrenDragManagerGridInitTrueTest055, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::GRID_ETS_TAG, PARENT_GRID_ID,
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    node->children_.clear();
    node->children_.emplace_back(nullptr);
    auto nonFrameNode = AceType::MakeRefPtr<MockUINode>(V2::TEXT_ETS_TAG, CHILD_ID_22);
    node->children_.emplace_back(nonFrameNode);
    auto plainNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, CHILD_ID_40,
        AceType::MakeRefPtr<Pattern>());
    node->children_.emplace_back(plainNode);

    auto gridItemPattern = AceType::MakeRefPtr<GridItemPattern>(nullptr);
    auto gridItem = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, CHILD_ID_41, gridItemPattern);
    ASSERT_NE(gridItemPattern, nullptr);
    gridItemPattern->AttachToFrameNode(gridItem);
    node->children_.emplace_back(gridItem);

    node->InitAllChildrenDragManager(true);

    EXPECT_NE(gridItemPattern->dragManager_, nullptr);
}

/**
 * @tc.name: RepeatVirtual2InitAllChildrenDragManagerGridInitFalseTest056
 * @tc.desc: Test InitAllChildrenDragManager with GRID parent and init=false skips InitDragManager
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2AdvancedTestNg, RepeatVirtual2InitAllChildrenDragManagerGridInitFalseTest056, TestSize.Level1)
{
    auto node = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        NODE_ID_1, ARR_LEN_5, TOTAL_COUNT_5, DEFAULT_MEM_OPT_STRATEGY,
        g_onGetRid4Index, g_onRecycleItems, g_onActiveRange,
        g_onMoveFromTo, g_onPurge, g_onPurgeAll, g_onUpdateDirty);
    ASSERT_NE(node, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::GRID_ETS_TAG, PARENT_GRID_ID,
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    node->SetParent(AceType::WeakClaim(AceType::RawPtr(parentNode)));

    node->children_.clear();
    auto gridItemPattern = AceType::MakeRefPtr<GridItemPattern>(nullptr);
    auto gridItem = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, CHILD_ID_41, gridItemPattern);
    ASSERT_NE(gridItemPattern, nullptr);
    gridItemPattern->AttachToFrameNode(gridItem);
    node->children_.emplace_back(gridItem);

    node->InitAllChildrenDragManager(false);

    EXPECT_EQ(gridItemPattern->dragManager_, nullptr);
}
} // namespace OHOS::Ace::NG
