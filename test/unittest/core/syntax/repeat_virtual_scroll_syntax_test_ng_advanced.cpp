/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/syntax/repeat_node.h"
#include "core/components_ng/syntax/repeat_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_caches.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/components_ng/pattern/list/list_item_event_hub.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_item.h"
#include "core/components_ng/pattern/scrollable/scrollable_item_pool.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string NODE_TAG = "node";
const std::list<std::string> FOR_REPEAT_IDS = { "0", "1", "2", "3", "4", "5" };
constexpr int32_t NODE_ID_1 = 100;
constexpr int32_t NODE_ID_2 = 200;
constexpr int32_t COUNT_1 = 1;
constexpr int32_t COUNT_3 = 3;
constexpr int32_t COUNT_5 = 5;
constexpr int32_t COUNT_10 = 10;
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_2 = 2;
constexpr int32_t INDEX_5 = 5;
constexpr int32_t INDEX_10 = 10;
constexpr int32_t INDEX_NEGATIVE = -1;
constexpr int32_t CACHE_SIZE_2 = 2;
constexpr int32_t CACHE_SIZE_5 = 5;
} // namespace

using CacheItem = RepeatVirtualScrollCaches::CacheItem;

class RepeatVirtualScrollAdvancedTestNg : public testing::Test {
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

    RefPtr<FrameNode> CreateListItemNode(int32_t elmtId)
    {
        auto tag = "TEXT_ETS_TAG";
        auto* stack = ViewStackProcessor::GetInstance();
        auto liFrameNode = FrameNode::GetOrCreateFrameNode(V2::LIST_ITEM_ETS_TAG, elmtId,
            []() { return AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE); });

        auto textNode = CreateNode(V2::TEXT_ETS_TAG, 100 * elmtId);

        auto pattern = AceType::MakeRefPtr<Pattern>();
        const uint32_t uniqNumMultiplier1 = 200;
        auto textFrameNode = AceType::MakeRefPtr<FrameNode>(tag, uniqNumMultiplier1 * elmtId, pattern);
        pattern->AttachToFrameNode(textFrameNode);
        liFrameNode->AddChild(textFrameNode);

        pattern = AceType::MakeRefPtr<Pattern>();
        const uint32_t uniqNumMultiplier2 = 100;
        textFrameNode = AceType::MakeRefPtr<FrameNode>(tag, uniqNumMultiplier2 * elmtId, pattern);
        pattern->AttachToFrameNode(textFrameNode);
        liFrameNode->AddChild(textFrameNode);
        stack->Push(liFrameNode);
        return liFrameNode;
    }

    const std::function<void(uint32_t)> onCreateNode = [this](uint32_t forIndex) {
        CreateListItemNode(forIndex);
    };
};

auto g_onUpdateNode = [](const std::string& fromKey, uint32_t forIndex) {};

auto g_onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
    std::list<std::string> keys;
    for (uint32_t i = from; i <= to; ++i) {
        keys.push_back("Key" + std::to_string(i));
    }
    return keys;
};

auto g_onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
    std::list<std::string> types;
    for (uint32_t i = from; i <= to; ++i) {
        types.push_back("Type" + std::to_string(i));
    }
    return types;
};

auto g_onSetActiveRange = [](int32_t from, int32_t to) {};

const std::map<std::string, std::pair<bool, uint32_t>> templateCachedCountMap = {
    {"elmt1", { true, 1 } },
    {"elmt2", { true, 2 } }
};

/**
 * @tc.name: RepeatVirtualGetOrCreateRepeatNodeTest001
 * @tc.desc: Test GetOrCreateRepeatNode with various parameters
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualGetOrCreateRepeatNodeTest001, TestSize.Level1)
{
    auto node1 = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    auto node2 = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    EXPECT_EQ(node1, node2);
}

/**
 * @tc.name: RepeatVirtualGetOrCreateRepeatNodeDifferentIdsTest002
 * @tc.desc: Test GetOrCreateRepeatNode with different nodeIds
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualGetOrCreateRepeatNodeDifferentIdsTest002, TestSize.Level1)
{
    auto node1 = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    auto node2 = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_2, COUNT_5, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    EXPECT_NE(node1, node2);
}

/**
 * @tc.name: RepeatVirtualUpdateTotalCountTest003
 * @tc.desc: Test UpdateTotalCount with various counts
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualUpdateTotalCountTest003, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);

    node->UpdateTotalCount(COUNT_5);
    node->UpdateTotalCount(COUNT_10);
    node->UpdateTotalCount(COUNT_1);
}

/**
 * @tc.name: RepeatVirtualFrameCountTest004
 * @tc.desc: Test FrameCount returns correct count
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualFrameCountTest004, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    auto frameCount = node->FrameCount();
    EXPECT_GE(frameCount, 0);
}

/**
 * @tc.name: RepeatVirtualGetChildrenCachedFalseTest005
 * @tc.desc: Test GetChildren with needCacheNode = false
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualGetChildrenCachedFalseTest005, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    auto children = node->GetChildren(false);
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: RepeatVirtualGetChildrenCachedTrueTest006
 * @tc.desc: Test GetChildren with needCacheNode = true
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualGetChildrenCachedTrueTest006, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    auto children = node->GetChildren(true);
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: RepeatVirtualGetFrameChildByIndexTest007
 * @tc.desc: Test GetFrameChildByIndex with various parameters
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualGetFrameChildByIndexTest007, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);

    (void)node->GetFrameChildByIndex(INDEX_0, false);
    (void)node->GetFrameChildByIndex(INDEX_2, true);
}

/**
 * @tc.name: RepeatVirtualGetFrameNodeTest008
 * @tc.desc: Test GetFrameNode retrieval
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualGetFrameNodeTest008, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    (void)node->GetFrameNode(INDEX_0);
}

/**
 * @tc.name: RepeatVirtualGetFrameNodeIndexTest009
 * @tc.desc: Test GetFrameNodeIndex with various states
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualGetFrameNodeIndexTest009, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    auto frameNode = CreateNode(V2::TEXT_ETS_TAG, 1);
    auto index = node->GetFrameNodeIndex(frameNode);
    EXPECT_GE(index, -1);
}

/**
 * @tc.name: RepeatVirtualSetNodeIndexOffsetTest010
 * @tc.desc: Test SetNodeIndexOffset affects index calculations
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualSetNodeIndexOffsetTest010, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->SetNodeIndexOffset(INDEX_0, COUNT_3);
    node->SetNodeIndexOffset(INDEX_2, COUNT_5);
}

/**
 * @tc.name: RepeatVirtualDoSetActiveChildRangeTest011
 * @tc.desc: Test DoSetActiveChildRange with various ranges
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualDoSetActiveChildRangeTest011, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->DoSetActiveChildRange(INDEX_0, INDEX_2, INDEX_0, INDEX_0);
    node->DoSetActiveChildRange(INDEX_5, INDEX_10, INDEX_2, INDEX_5, true);
}

/**
 * @tc.name: RepeatVirtualDoSetActiveChildRangeSetBasedTest012
 * @tc.desc: Test DoSetActiveChildRange with set-based parameters
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualDoSetActiveChildRangeSetBasedTest012, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    std::set<int32_t> activeItems = {0, 1, 2};
    std::set<int32_t> cachedItems = {0, 1, 2, 3, 4};
    node->DoSetActiveChildRange(activeItems, cachedItems, INDEX_0);
}

/**
 * @tc.name: RepeatVirtualRecycleItemsTest013
 * @tc.desc: Test RecycleItems with various ranges
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualRecycleItemsTest013, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_5, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->RecycleItems(INDEX_0, INDEX_2);
    node->RecycleItems(INDEX_2, INDEX_5);
}

/**
 * @tc.name: RepeatVirtualOnSetCacheCountTest014
 * @tc.desc: Test OnSetCacheCount with various cache sizes
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualOnSetCacheCountTest014, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    std::optional<LayoutConstraintF> itemConstraint;
    node->OnSetCacheCount(CACHE_SIZE_2, itemConstraint);
    node->OnSetCacheCount(CACHE_SIZE_5, itemConstraint);
}

/**
 * @tc.name: RepeatVirtualSetOnMoveTest015
 * @tc.desc: Test SetOnMove callback registration
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualSetOnMoveTest015, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    auto onMoveFunc = [](int32_t from, int32_t to) {};
    node->SetOnMove(std::move(onMoveFunc));
}

/**
 * @tc.name: RepeatVirtualMoveDataTest016
 * @tc.desc: Test MoveData with various indices
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualMoveDataTest016, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_5, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->MoveData(INDEX_0, INDEX_2);
    node->MoveData(INDEX_1, INDEX_5);
    node->MoveData(INDEX_NEGATIVE, INDEX_1);
}

/**
 * @tc.name: RepeatVirtualOnConfigurationUpdateTest017
 * @tc.desc: Test OnConfigurationUpdate with different config types
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualOnConfigurationUpdateTest017, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    ConfigurationChange config;
    config.colorModeUpdate = true;
    node->OnConfigurationUpdate(config);
}

/**
 * @tc.name: RepeatVirtualNotifyColorModeChangeTest018
 * @tc.desc: Test NotifyColorModeChange with various modes
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualNotifyColorModeChangeTest018, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->NotifyColorModeChange(0);
    node->NotifyColorModeChange(1);
}

/**
 * @tc.name: RepeatVirtualSetJSViewActiveTest019
 * @tc.desc: Test SetJSViewActive propagation to children
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualSetJSViewActiveTest019, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->SetJSViewActive(true);
    node->SetJSViewActive(false);
}

/**
 * @tc.name: RepeatVirtualSetDestroyingTest020
 * @tc.desc: Test SetDestroying cleanup verification
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualSetDestroyingTest020, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->SetDestroying(true);
    node->SetDestroying(false);
}

/**
 * @tc.name: RepeatVirtualSetIsLoopTest021
 * @tc.desc: Test SetIsLoop behavior changes
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualSetIsLoopTest021, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->SetIsLoop(true);
    node->SetIsLoop(false);
}

/**
 * @tc.name: RepeatVirtualPaintDebugBoundaryTreeAllTest022
 * @tc.desc: Test PaintDebugBoundaryTreeAll recursive behavior
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualPaintDebugBoundaryTreeAllTest022, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->PaintDebugBoundaryTreeAll(true);
    node->PaintDebugBoundaryTreeAll(false);
}

/**
 * @tc.name: RepeatVirtualGetChildrenForInspectorTest023
 * @tc.desc: Test GetChildrenForInspector with needCacheNode variations
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualGetChildrenForInspectorTest023, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    (void)node->GetChildrenForInspector(false);
    (void)node->GetChildrenForInspector(true);
}

/**
 * @tc.name: RepeatVirtualOnRecycleTest024
 * @tc.desc: Test OnRecycle with various cache states
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualOnRecycleTest024, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->OnRecycle();
}

/**
 * @tc.name: RepeatVirtualOnReuseTest025
 * @tc.desc: Test OnReuse behavior verification
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualOnReuseTest025, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->OnReuse();
}

/**
 * @tc.name: RepeatVirtualIsAtomicNodeTest026
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualIsAtomicNodeTest026, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(node->IsAtomicNode());
}

/**
 * @tc.name: RepeatVirtualInitDragManagerTest027
 * @tc.desc: Test InitDragManager with various node types
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualInitDragManagerTest027, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    auto child = CreateNode(NODE_TAG, 1);
    auto onMoveFunc = [](int32_t from, int32_t to) {};
    node->SetOnMove(std::move(onMoveFunc));
    node->InitDragManager(child);
}

/**
 * @tc.name: RepeatVirtualInitAllChildrenDragManagerTest028
 * @tc.desc: Test InitAllChildrenDragManager edge cases
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualInitAllChildrenDragManagerTest028, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    auto onMoveFunc = [](int32_t from, int32_t to) {};
    node->SetOnMove(std::move(onMoveFunc));
    node->InitAllChildrenDragManager(true);
    node->InitAllChildrenDragManager(false);
}

/**
 * @tc.name: RepeatVirtualUpdateRenderStateTest029
 * @tc.desc: Test UpdateRenderState with various flags
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualUpdateRenderStateTest029, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->UpdateRenderState(true);
    node->UpdateRenderState(false);
}

/**
 * @tc.name: RepeatVirtualUpdateTotalCountZeroTest030
 * @tc.desc: Test UpdateTotalCount with zero count
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualScrollAdvancedTestNg, RepeatVirtualUpdateTotalCountZeroTest030, TestSize.Level1)
{
    auto node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID_1, COUNT_3, templateCachedCountMap,
        onCreateNode, g_onUpdateNode, g_onGetKeys4Range,
        g_onGetTypes4Range, g_onSetActiveRange);

    ASSERT_NE(node, nullptr);
    node->UpdateTotalCount(0);
    EXPECT_EQ(node->FrameCount(), 0);
}

} // namespace OHOS::Ace::NG
