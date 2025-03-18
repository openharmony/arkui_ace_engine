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
#include "core/components_ng/syntax/repeat_virtual_scroll_2_caches.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
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

using CacheItem = RepeatVirtualScroll2Caches::CacheItem;
using OptCacheItem = RepeatVirtualScroll2Caches::OptCacheItem;
using GetFrameChildResult = RepeatVirtualScroll2Caches::GetFrameChildResult;

namespace {
/**
 * Map: Repeat node index -> L1 cache repeat node rid
 */
const std::map<IndexType, RIDType> L1_RID_4_INDEX = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 4},
    {4, 5},
    {5, 6}
};

/**
 * Function needed by RepeatVirtualScrollCaches constructor is special test case
 */
const auto ON_GET_RID_4_INDEX = [](IndexType index) -> std::pair<RIDType, uint32_t> {
    auto it = L1_RID_4_INDEX.find(0);
    if (it != L1_RID_4_INDEX.end()) {
        return {index, 2};
    }
    return {index, 1};
};

const auto ON_RECYCLE_ITEMS = [](IndexType fromIndex, IndexType toIndex) -> void {
    return;
};

const auto ON_ACTIVE_RANGE = [](int32_t fromIndex, int32_t toIndex, bool isLoop) -> void {
    return;
};

const auto ON_MOVE_FROM_TO = [](IndexType, IndexType) -> void {
    return;
};

const auto ON_PURGE = []() -> void {
    return;
};
}

class RepeatNodeCache2SyntaxTest : public testing::Test {
public:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }

    RefPtr<FrameNode> CreateNode(const std::string& tag, int32_t elmtId);

    RefPtr<RepeatVirtualScroll2Node> CreateRepeatVirtualNode(int32_t elmtId, uint32_t totalCount);

    /**
     * create ListItemNode with 2 Text Node inside
     */
    RefPtr<FrameNode> CreateListItemNode(int32_t elmtId);
};

RefPtr<FrameNode> RepeatNodeCache2SyntaxTest::CreateNode(const std::string& tag, int32_t elmtId)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, elmtId, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    return frameNode;
}

RefPtr<RepeatVirtualScroll2Node> RepeatNodeCache2SyntaxTest::CreateRepeatVirtualNode(
    int32_t elmtId, uint32_t totalCount)
{
    return RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        elmtId, totalCount, ON_GET_RID_4_INDEX, ON_RECYCLE_ITEMS, ON_ACTIVE_RANGE, ON_MOVE_FROM_TO, ON_PURGE);
}

RefPtr<FrameNode> RepeatNodeCache2SyntaxTest::CreateListItemNode(int32_t elmtId)
{
    auto tag = "TEXT_ETS_TAG";

    auto* stack = ViewStackProcessor::GetInstance();
    auto listItemFrameNode = FrameNode::GetOrCreateFrameNode(V2::LIST_ITEM_ETS_TAG, elmtId,
        []() { return AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE); });

    auto textNode = CreateNode(V2::TEXT_ETS_TAG, 100 * elmtId);

    auto pattern = AceType::MakeRefPtr<Pattern>();
    const uint32_t uniqNumMultiplier1 = 200;
    auto textFrameNode = AceType::MakeRefPtr<FrameNode>(tag, uniqNumMultiplier1 * elmtId, pattern);
    pattern->AttachToFrameNode(textFrameNode);
    listItemFrameNode->AddChild(textFrameNode);

    pattern = AceType::MakeRefPtr<Pattern>();
    const uint32_t uniqNumMultiplier2 = 100;
    textFrameNode = AceType::MakeRefPtr<FrameNode>(tag, uniqNumMultiplier2 * elmtId, pattern);
    pattern->AttachToFrameNode(textFrameNode);
    listItemFrameNode->AddChild(textFrameNode);
    stack->Push(listItemFrameNode);
    return listItemFrameNode;
}

/**
 * @tc.name: RepeatNodeCache2Test000
 * @tc.desc: Test creation of GetOrCreateRepeatNode
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test000, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    /**
     * @tc.steps: step1. Create node object
     * @tc.expected: Object is not nullptr.
     */
    auto repeatNode = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        nodeId, 10, ON_GET_RID_4_INDEX, ON_RECYCLE_ITEMS, ON_ACTIVE_RANGE, ON_MOVE_FROM_TO, ON_PURGE);

    EXPECT_NE(repeatNode, nullptr);
}

/**
 * @tc.name: RepeatNodeCache2Test001
 * @tc.desc: Test node.FrameCount
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1001, 10);

    /**
     * @tc.steps: step2. Get frame count
     * @tc.expected: frame count should be 10
     */
    auto frameCount = repeatNode->FrameCount();
    EXPECT_EQ(frameCount, 10);

    /**
     * @tc.steps: step2. Update totalCount to 2
     * @tc.expected: frame count should be 2
     */
    repeatNode->UpdateTotalCount(2);
    frameCount = repeatNode->FrameCount();
    EXPECT_EQ(frameCount, 2);
}

/**
 * @tc.name: RepeatNodeCache2Test002
 * @tc.desc: Test node.GetChildren
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test node.GetChildren when repeat is empty
     * @tc.expected: children size shoule be 0
     */
    auto repeatNode = CreateRepeatVirtualNode(1002, 10);
    auto children = repeatNode->GetChildren();
    EXPECT_EQ(children.size(), 0);

    /**
     * @tc.steps: step2. Test node.GetChildren when repeat has 1 item
     * @tc.expected: children size shoule be 0
     */
    repeatNode->caches_.l1Rid4Index_ = {
        {0, 1}
    };
    RefPtr<UINode> uiNode = AceType::MakeRefPtr<FrameNode>("node", 2002, AceType::MakeRefPtr<Pattern>());
    CacheItem cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode, true);
    std::map<RIDType, CacheItem> cacheItem4Rid_ = {{ 0, cacheItem }};
    repeatNode->children_ = { uiNode };
    children = repeatNode->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: RepeatNodeCache2Test003
 * @tc.desc: Test caches.GetFrameChild
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test003, TestSize.Level1)
{
    RepeatVirtualScroll2Caches caches(ON_GET_RID_4_INDEX);

    /**
     * @tc.steps: step1. give l1 cache items include item (rid == 1)
     * @tc.expected: return rid
     */
    GetFrameChildResult result = caches.GetFrameChild(1, false);
    EXPECT_EQ(result.second, 0);

    /**
     * @tc.steps: step2. give l1 cache items include item (rid == 10)
     * @tc.expected: return nullptr
     */
    result = caches.GetFrameChild(10, false);
    EXPECT_EQ(result.second, nullptr);
}

/**
 * @tc.name: RepeatNodeCache2Test004
 * @tc.desc: Test caches.RemoveNode
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test004, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1004, 10);
    repeatNode->caches_.l1Rid4Index_ = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}
    };
    RefPtr<UINode> uiNode = AceType::MakeRefPtr<FrameNode>("node", 2004, AceType::MakeRefPtr<Pattern>());
    CacheItem cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode, true);
    repeatNode->caches_.cacheItem4Rid_ = {
        { 1, cacheItem }, { 2, cacheItem }, { 3, cacheItem }, { 4, cacheItem }
    };

    /**
     * @tc.steps: step1. remove 1 item from L1
     * @tc.expected: repeat has 3 children left
     */
    EXPECT_EQ(repeatNode->GetChildren().size(), 4);
    repeatNode->caches_.RemoveNode(2);
    repeatNode->children_.clear();
    EXPECT_EQ(repeatNode->GetChildren().size(), 3);
}

/**
 * @tc.name: RepeatNodeCache2Test005
 * @tc.desc: Test node.CheckActiveRange for List/Swiper-no-Loop scenario
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test005, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1005, 10);
    ActiveRangeType activeRange;

    /**
     * @tc.steps: step1. check active range: [0 1 2] 3 4 5..
     * @tc.expected: active range is {0,4}
     */
    activeRange = repeatNode->CheckActiveRange(0, 2, 0, 2);
    std::pair<IndexType, IndexType> expect_result1(0, 4);
    EXPECT_EQ(activeRange, expect_result1);

    /**
     * @tc.steps: step2. check active range: ..1 2 [3 4 5] 6 7..
     * @tc.expected: active range is {1,7}
     */
    activeRange = repeatNode->CheckActiveRange(3, 5, 2, 2);
    std::pair<IndexType, IndexType> expect_result2(1, 7);
    EXPECT_EQ(activeRange, expect_result2);

    /**
     * @tc.steps: step3. check active range: ..5 6 [7 8 9]
     * @tc.expected: active range is {5,9}
     */
    activeRange = repeatNode->CheckActiveRange(7, 9, 2, 0);
    std::pair<IndexType, IndexType> expect_result3(5, 9);
    EXPECT_EQ(activeRange, expect_result3);
}

/**
 * @tc.name: RepeatNodeCache2Test006
 * @tc.desc: Test node.CheckActiveRange for Grid/WaterFlow scenario
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test006, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1006, 10);
    ActiveRangeType activeRange;

    /**
     * @tc.steps: step1. check active range for: [0 1 2] 3 4 5..
     * @tc.expected: active range is {0,4}
     */
    activeRange = repeatNode->CheckActiveRange(0, 2, 2, 2);
    std::pair<IndexType, IndexType> expect_result1(0, 4);
    EXPECT_EQ(activeRange, expect_result1);

    /**
     * @tc.steps: step2. check active range for: ..1 2 [3 4 5] 6 7..
     * @tc.expected: active range is {1,7}
     */
    activeRange = repeatNode->CheckActiveRange(3, 5, 2, 2);
    std::pair<IndexType, IndexType> expect_result2(1, 7);
    EXPECT_EQ(activeRange, expect_result2);

    /**
     * @tc.steps: step3. check active range for: ..5 6 [7 8 9]
     * @tc.expected: active range is {5,9}
     */
    activeRange = repeatNode->CheckActiveRange(7, 9, 2, 2);
    std::pair<IndexType, IndexType> expect_result3(5, 9);
    EXPECT_EQ(activeRange, expect_result3);
}

/**
 * @tc.name: RepeatNodeCache2Test007
 * @tc.desc: Test node.CheckActiveRange for Swiper-Loop scenario
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test007, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1007, 10);
    repeatNode->SetIsLoop(true);
    ActiveRangeType activeRange;

    /**
     * @tc.steps: step1. check active range for: ..8 9 [0 1 2] 3 4..
     * @tc.expected: active range is {-2,4}
     */
    activeRange = repeatNode->CheckActiveRange(0, 2, 2, 2);
    std::pair<IndexType, IndexType> expect_result1(-2, 4);
    EXPECT_EQ(activeRange, expect_result1);

    /**
     * @tc.steps: step2. check active range for: ..7 8 [9 0 1] 2 3..
     * @tc.expected: active range is {7,3}
     */
    activeRange = repeatNode->CheckActiveRange(9, 1, 2, 2);
    std::pair<IndexType, IndexType> expect_result2(7, 3);
    EXPECT_EQ(activeRange, expect_result2);

    /**
     * @tc.steps: step3. check active range for: ..5 6 [7 8 9] 0 1..
     * @tc.expected: active range is {5,11}
     */
    activeRange = repeatNode->CheckActiveRange(7, 9, 2, 2);
    std::pair<IndexType, IndexType> expect_result3(5, 11);
    EXPECT_EQ(activeRange, expect_result3);

    /**
     * @tc.steps: step4. check active range for: 2 [3 0] 1
     * @tc.expected: active range is {3,2} (overlapped)
     */
    auto repeatNode2 = CreateRepeatVirtualNode(10071, 4);
    repeatNode2->SetIsLoop(true);
    activeRange = repeatNode2->CheckActiveRange(3, 0, 2, 2);
    std::pair<IndexType, IndexType> expect_result4(3, 2);
    EXPECT_EQ(activeRange, expect_result4);

    /**
     * @tc.steps: step5. check active range for: [0 1] 2 3..
     * @tc.expected: active range is {-2,3}
     */
    auto repeatNode3 = CreateRepeatVirtualNode(10072, 10);
    repeatNode3->SetIsLoop(true);
    activeRange = repeatNode3->CheckActiveRange(0, 1, 2, 2);
    std::pair<IndexType, IndexType> expect_result5(-2, 3);
    EXPECT_EQ(activeRange, expect_result5);
}

/**
 * @tc.name: RepeatNodeCache2Test008
 * @tc.desc: Test node.CheckActiveRange for List/Grid/WaterFlow/Swiper-no-Loop scenario (multiple components)
 *   X indicates a non-repeat child
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test008, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1008, 10);
    ActiveRangeType activeRange;

    /**
     * @tc.steps: step1. check active range for: ..[X X 0 1 2] 3 4..
     * @tc.expected: active range is {0,4}
     */
    activeRange = repeatNode->CheckActiveRange(-2, 2, 2, 2);
    std::pair<IndexType, IndexType> expect_result1(0, 4);
    EXPECT_EQ(activeRange, expect_result1);

    /**
     * @tc.steps: step2. check active range for: ..[X X X] 0 1 2..
     * @tc.expected: active range is {0,1}
     */
    activeRange = repeatNode->CheckActiveRange(-5, -1, 2, 2);
    std::pair<IndexType, IndexType> expect_result2(0, 1);
    EXPECT_EQ(activeRange, expect_result2);

    /**
     * @tc.steps: step3. check active range for: ..[X X X] X X 0 1..
     * @tc.expected: active range is {INT32_MAX,INT32_MAX}
     */
    activeRange = repeatNode->CheckActiveRange(-5, -3, 2, 2);
    std::pair<IndexType, IndexType> expect_result3(INT32_MAX, INT32_MAX);
    EXPECT_EQ(activeRange, expect_result3);

    /**
     * @tc.steps: step4. check active range for: ..5 6 [7 8 9 X X]..
     * @tc.expected: active range is {5,9}
     */
    activeRange = repeatNode->CheckActiveRange(7, 11, 2, 2);
    std::pair<IndexType, IndexType> expect_result4(5, 9);
    EXPECT_EQ(activeRange, expect_result4);

    /**
     * @tc.steps: step5. check active range for: ..8 9 [X X X]..
     * @tc.expected: active range is {8,9}
     */
    activeRange = repeatNode->CheckActiveRange(10, 12, 2, 2);
    std::pair<IndexType, IndexType> expect_result5(8, 9);
    EXPECT_EQ(activeRange, expect_result5);

    /**
     * @tc.steps: step6. check active range for: ..8 9 X X [X X X]..
     * @tc.expected: active range is {INT32_MAX,INT32_MAX}
     */
    activeRange = repeatNode->CheckActiveRange(12, 14, 2, 2);
    std::pair<IndexType, IndexType> expect_result6(INT32_MAX, INT32_MAX);
    EXPECT_EQ(activeRange, expect_result6);
}

/**
 * @tc.name: RepeatNodeCache2Test009
 * @tc.desc: Test node.CheckNode4IndexInL1
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test009, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1009, 10);
    RefPtr<UINode> uiNode = AceType::MakeRefPtr<FrameNode>("node", 2009, AceType::MakeRefPtr<Pattern>());
    CacheItem cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode, true);
    bool remainInL1;

    /**
     * @tc.steps: step1. check normal active range
     * @tc.expected: node in L1 cache, return true
     */
    remainInL1 = repeatNode->CheckNode4IndexInL1(1, 0, 9, cacheItem);
    EXPECT_EQ(remainInL1, true);
    remainInL1 = repeatNode->CheckNode4IndexInL1(5, 6, 9, cacheItem);
    EXPECT_EQ(remainInL1, false);
    remainInL1 = repeatNode->CheckNode4IndexInL1(10, 6, 9, cacheItem);
    EXPECT_EQ(remainInL1, false);

    /**
     * @tc.steps: step2. check swiper-loop range
     * @tc.expected: node in L1 cache, return true
     */
    repeatNode->SetIsLoop(true);
    remainInL1 = repeatNode->CheckNode4IndexInL1(5, 0, 9, cacheItem);
    EXPECT_EQ(remainInL1, true);
    remainInL1 = repeatNode->CheckNode4IndexInL1(3, 2, 1, cacheItem);
    EXPECT_EQ(remainInL1, true);
}

/**
 * @tc.name: RepeatNodeCache2Test010
 * @tc.desc: Test node.DoSetActiveChildRange
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test010, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1010, 10);

    /**
     * @tc.steps: step1. check normal active range
     * @tc.expected: repeat has 8 items
     */
    repeatNode->children_.clear();
    RefPtr<UINode> uiNode = AceType::MakeRefPtr<FrameNode>("node", 2010, AceType::MakeRefPtr<Pattern>());
    CacheItem cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode, true);
    for (int i = 0; i < 10; ++i) {
        repeatNode->caches_.l1Rid4Index_.insert({i, i + 1});
        repeatNode->caches_.cacheItem4Rid_.insert({i + 1, cacheItem});
    }
    repeatNode->DoSetActiveChildRange(0, 5, 2, 2);
    EXPECT_EQ(repeatNode->GetChildren().size(), 8);

    /**
     * @tc.steps: step2. check swiper-loop range
     * @tc.expected: repeat has 6 items
     */
    repeatNode->children_.clear();
    repeatNode->caches_.l1Rid4Index_.clear();
    for (int i = 0; i < 10; ++i) {
        repeatNode->caches_.l1Rid4Index_.insert({i, i + 1});
        repeatNode->caches_.cacheItem4Rid_.insert({i + 1, cacheItem});
    }
    repeatNode->SetIsLoop(true);
    repeatNode->DoSetActiveChildRange(8, 1, 1, 1);
    EXPECT_EQ(repeatNode->GetChildren().size(), 6);
}

/**
 * @tc.name: RepeatNodeCache2Test011
 * @tc.desc: Test caches.GetL1Index4Node
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test011, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1011, 10);
    RefPtr<UINode> uiNode = AceType::MakeRefPtr<FrameNode>("node", 2011, AceType::MakeRefPtr<Pattern>());
    CacheItem cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode, true);
    repeatNode->caches_.l1Rid4Index_ = {
        {0, 1}
    };
    repeatNode->caches_.cacheItem4Rid_ = {
        {1, cacheItem}
    };

    /**
     * @tc.steps: step1.
     * @tc.expected: GetL1Index4Node return 1
     */
    std::optional<IndexType> result = repeatNode->caches_.GetL1Index4Node(AceType::DynamicCast<FrameNode>(uiNode));
    EXPECT_EQ(result.value(), 0);
}

/**
 * @tc.name: RepeatNodeCache2Test012
 * @tc.desc: Test caches.GetCacheItem4RID
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test012, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1012, 10);
    RefPtr<UINode> uiNode = AceType::MakeRefPtr<FrameNode>("node", 2012, AceType::MakeRefPtr<Pattern>());
    CacheItem cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode, true);

    /**
     * @tc.steps: step1.
     * @tc.expected: should return cacheItem
     */
    repeatNode->caches_.l1Rid4Index_ = {
        {0, 1}
    };
    repeatNode->caches_.cacheItem4Rid_ = {
        {1, cacheItem}
    };
    OptCacheItem optCacheItem = repeatNode->caches_.GetCacheItem4RID(1);
    EXPECT_EQ(optCacheItem.has_value(), true);
}

/**
 * @tc.name: RepeatNodeCache2Test013
 * @tc.desc: Test caches.GetRID4Index
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test013, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1013, 10);
    RefPtr<UINode> uiNode = AceType::MakeRefPtr<FrameNode>("node", 2013, AceType::MakeRefPtr<Pattern>());
    CacheItem cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode, true);

    /**
     * @tc.steps: step1.
     * @tc.expected: should return rid=1
     */
    repeatNode->caches_.l1Rid4Index_ = {
        {0, 1}
    };
    repeatNode->caches_.cacheItem4Rid_ = {
        {1, cacheItem}
    };
    std::optional<RIDType> rid = repeatNode->caches_.GetRID4Index(0);
    EXPECT_EQ(rid.value(), 1);
}

/**
 * @tc.name: RepeatNodeCache2Test014
 * @tc.desc: Test caches.ConvertFromToIndex
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test014, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1014, 6);
    repeatNode->MoveData(0, 1);
    repeatNode->MoveData(1, 2);
    repeatNode->MoveData(2, 3);
    
    /**
     * @tc.steps: step1.
     * @tc.expected: index is 0, mappedIndex should be 1.
     */
    IndexType mappedIndex = repeatNode->caches_.ConvertFromToIndex(0);
    EXPECT_EQ(mappedIndex, 1);

    /**
     * @tc.steps: step2.
     * @tc.expected: index is 1, mappedIndex should be 2.
     */
    mappedIndex = repeatNode->caches_.ConvertFromToIndex(1);
    EXPECT_EQ(mappedIndex, 2);

    /**
     * @tc.steps: step3.
     * @tc.expected: index is 2, mappedIndex should be 3.
     */
    mappedIndex = repeatNode->caches_.ConvertFromToIndex(2);
    EXPECT_EQ(mappedIndex, 3);

    /**
     * @tc.steps: step4.
     * @tc.expected: index is 3, mappedIndex should be 0.
     */
    mappedIndex = repeatNode->caches_.ConvertFromToIndex(3);
    EXPECT_EQ(mappedIndex, 0);

    /**
     * @tc.steps: step5.
     * @tc.expected: index is 4, 5, 6, mappedIndex should be same with index.
     */
    mappedIndex = repeatNode->caches_.ConvertFromToIndex(4);
    EXPECT_EQ(mappedIndex, 4);
    mappedIndex = repeatNode->caches_.ConvertFromToIndex(5);
    EXPECT_EQ(mappedIndex, 5);
    mappedIndex = repeatNode->caches_.ConvertFromToIndex(6);
    EXPECT_EQ(mappedIndex, 6);
}

/**
 * @tc.name: RepeatNodeCache2Test015
 * @tc.desc: Test caches.ConvertFromToIndexRevert
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCache2SyntaxTest, RepeatNodeCache2Test015, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(1015, 6);
    repeatNode->MoveData(0, 1);
    repeatNode->MoveData(1, 2);
    repeatNode->MoveData(2, 3);
    
    /**
     * @tc.steps: step1.
     * @tc.expected: index is 0, mappedIndex should be 3.
     */
    IndexType mappedIndex = repeatNode->caches_.ConvertFromToIndexRevert(0);
    EXPECT_EQ(mappedIndex, 3);

    /**
     * @tc.steps: step2.
     * @tc.expected: index is 1, mappedIndex should be 0.
     */
    mappedIndex = repeatNode->caches_.ConvertFromToIndexRevert(1);
    EXPECT_EQ(mappedIndex, 0);

    /**
     * @tc.steps: step3.
     * @tc.expected: index is 2, mappedIndex should be 1.
     */
    mappedIndex = repeatNode->caches_.ConvertFromToIndexRevert(2);
    EXPECT_EQ(mappedIndex, 1);

    /**
     * @tc.steps: step4.
     * @tc.expected: index is 3, mappedIndex should be 2.
     */
    mappedIndex = repeatNode->caches_.ConvertFromToIndexRevert(3);
    EXPECT_EQ(mappedIndex, 2);

    /**
     * @tc.steps: step5.
     * @tc.expected: index is 4, 5, 6, mappedIndex should be same with index.
     */
    mappedIndex = repeatNode->caches_.ConvertFromToIndexRevert(4);
    EXPECT_EQ(mappedIndex, 4);
    mappedIndex = repeatNode->caches_.ConvertFromToIndexRevert(5);
    EXPECT_EQ(mappedIndex, 5);
    mappedIndex = repeatNode->caches_.ConvertFromToIndexRevert(6);
    EXPECT_EQ(mappedIndex, 6);
}
} // namespace OHOS::Ace::NG