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

#include "repeat_virtual_2_test_ng.h"
 
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

using CacheItem = RepeatVirtualScroll2Caches::CacheItem;
using OptCacheItem = RepeatVirtualScroll2Caches::OptCacheItem;
using GetFrameChildResult = RepeatVirtualScroll2Caches::GetFrameChildResult;

RefPtr<FrameNode> RepeatVirtual2TestNg::CreateNode(const std::string& tag)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, elmtId_, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    return frameNode;
}

RefPtr<RepeatVirtualScroll2Node> RepeatVirtual2TestNg::CreateRepeatVirtualNode(uint32_t totalCount)
{
    l1Rid4Index_ = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5},
        {5, 6}
    };
    onGetRid4Index_ = [&](IndexType index) -> std::pair<RIDType, uint32_t> {
        auto it = l1Rid4Index_.find(0);
        if (it != l1Rid4Index_.end()) {
            return {index, 2};
        }
        return {index, 1};
    };
    onRecycleItems_ = [](IndexType fromIndex, IndexType toIndex) -> void {
        return;
    };
    onActiveRange_ = [](int32_t fromIndex, int32_t toIndex, int32_t vStart, int32_t vEnd, bool isLoop,
        bool forceUpdate) -> void {
        return;
    };
    onMoveFromTo_ = [](IndexType, IndexType) -> void {
        return;
    };
    onPurge_ = []() -> void {
        return;
    };
    return RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        GetElmtId(), totalCount, totalCount, onGetRid4Index_, onRecycleItems_, onActiveRange_, onMoveFromTo_, onPurge_);
}

RefPtr<FrameNode> RepeatVirtual2TestNg::CreateListItemNode()
{
    auto tag = "TEXT_ETS_TAG";
    auto* stack = ViewStackProcessor::GetInstance();
    auto listItemFrameNode = FrameNode::GetOrCreateFrameNode(V2::LIST_ITEM_ETS_TAG, GetElmtId(), []() {
        return AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    });

    auto textNode = CreateNode(V2::TEXT_ETS_TAG);

    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto textFrameNode = AceType::MakeRefPtr<FrameNode>(tag, GetElmtId(), pattern);
    pattern->AttachToFrameNode(textFrameNode);
    listItemFrameNode->AddChild(textFrameNode);

    pattern = AceType::MakeRefPtr<Pattern>();
    textFrameNode = AceType::MakeRefPtr<FrameNode>(tag, GetElmtId(), pattern);
    pattern->AttachToFrameNode(textFrameNode);
    listItemFrameNode->AddChild(textFrameNode);
    stack->Push(listItemFrameNode);
    return listItemFrameNode;
}

/**
 * @tc.name: CreateRepeat001
 * @tc.desc: Test creation of GetOrCreateRepeatNode
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, CreateRepeat001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    /**
     * @tc.steps: step1. Create node object
     * @tc.expected: Object is not nullptr.
     */
    auto repeatNode = RepeatVirtualScroll2Node::GetOrCreateRepeatNode(
        nodeId, 10, 10, onGetRid4Index_, onRecycleItems_, onActiveRange_, onMoveFromTo_, onPurge_);

    EXPECT_NE(repeatNode, nullptr);
}

/**
 * @tc.name: FrameCount001
 * @tc.desc: Test node.FrameCount
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, FrameCount001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);

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
 * @tc.name: GetChildren001
 * @tc.desc: Test node.GetChildren
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, GetChildren001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test node.GetChildren when repeat is empty
     * @tc.expected: children size shoule be 0
     */
    auto repeatNode = CreateRepeatVirtualNode(10);
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
 * @tc.name: GetFrameChild001
 * @tc.desc: Test caches.GetFrameChild
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, GetFrameChild001, TestSize.Level1)
{
    RepeatVirtualScroll2Caches caches(onGetRid4Index_);

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
 * @tc.name: RemoveNode001
 * @tc.desc: Test caches.RemoveNode
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, RemoveNode001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
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
 * @tc.name: CheckActiveRange001
 * @tc.desc: Test node.CheckActiveRange for List/Swiper-no-Loop scenario
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, CheckActiveRange001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
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
 * @tc.name: CheckActiveRange002
 * @tc.desc: Test node.CheckActiveRange for Grid/WaterFlow scenario
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, CheckActiveRange002, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
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
 * @tc.name: CheckActiveRange003
 * @tc.desc: Test node.CheckActiveRange for Swiper-Loop scenario
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, CheckActiveRange003, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
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
    auto repeatNode2 = CreateRepeatVirtualNode(4);
    repeatNode2->SetIsLoop(true);
    activeRange = repeatNode2->CheckActiveRange(3, 0, 2, 2);
    std::pair<IndexType, IndexType> expect_result4(3, 2);
    EXPECT_EQ(activeRange, expect_result4);

    /**
     * @tc.steps: step5. check active range for: [0 1] 2 3..
     * @tc.expected: active range is {-2,3}
     */
    auto repeatNode3 = CreateRepeatVirtualNode(10);
    repeatNode3->SetIsLoop(true);
    activeRange = repeatNode3->CheckActiveRange(0, 1, 2, 2);
    std::pair<IndexType, IndexType> expect_result5(-2, 3);
    EXPECT_EQ(activeRange, expect_result5);
}

/**
 * @tc.name: CheckActiveRange004
 * @tc.desc: Test node.CheckActiveRange for List/Grid/WaterFlow/Swiper-no-Loop scenario (multiple components)
 *   X indicates a non-repeat child
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, CheckActiveRange004, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
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
 * @tc.name: CheckNodeInL1001
 * @tc.desc: Test node.CheckNode4IndexInL1
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, CheckNodeInL1001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
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
 * @tc.name: SetActiveRange001
 * @tc.desc: Test node.DoSetActiveChildRange
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, SetActiveRange001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);

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
 * @tc.name: GetL1Nodes001
 * @tc.desc: Test caches.GetL1Index4Node
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, GetL1Nodes001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
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
 * @tc.name: GetAllNodes001
 * @tc.desc: Test caches.GetCacheItem4RID
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, GetAllNodes001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
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
 * @tc.name: GetRID4Index001
 * @tc.desc: Test caches.GetRID4Index
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, GetRID4Index001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
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
 * @tc.name: CallOnGetRid4Index001
 * @tc.desc: Test caches.CallOnGetRid4Index
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, CallOnGetRid4Index001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);

    repeatNode->caches_.onGetRid4Index_ = [](IndexType index)->std::pair<RIDType, uint32_t> {
        return {1, OnGetRid4IndexResult::CREATED_NEW_NODE}; };
    auto item0 = repeatNode->caches_.CallOnGetRid4Index(0).value();
    EXPECT_EQ(item0, nullptr);

    repeatNode->caches_.onGetRid4Index_ = [&](IndexType index)->std::pair<RIDType, uint32_t> {
        CreateListItemNode(); return {1, OnGetRid4IndexResult::CREATED_NEW_NODE}; };
    auto item1 = repeatNode->caches_.CallOnGetRid4Index(0).value();
    EXPECT_EQ(item1->node_->GetId(), 10002);

    repeatNode->caches_.onGetRid4Index_ = [&](IndexType index)->std::pair<RIDType, uint32_t> {
        CreateListItemNode(); return {0, OnGetRid4IndexResult::CREATED_NEW_NODE}; };
    auto item2 = repeatNode->caches_.CallOnGetRid4Index(0);
    EXPECT_EQ(item2, std::nullopt);

    repeatNode->caches_.onGetRid4Index_ = [](IndexType index)->std::pair<RIDType, uint32_t> {
        return {1, OnGetRid4IndexResult::UPDATED_NODE}; };
    auto item3 = repeatNode->caches_.CallOnGetRid4Index(0).value();
    EXPECT_EQ(item3->node_->GetId(), 10002);

    repeatNode->caches_.onGetRid4Index_ = [](IndexType index)->std::pair<RIDType, uint32_t> {
        return {2, OnGetRid4IndexResult::UPDATED_NODE}; };
    auto item4 = repeatNode->caches_.CallOnGetRid4Index(0);
    EXPECT_EQ(item4, std::nullopt);

    repeatNode->caches_.onGetRid4Index_ = [](IndexType index)->std::pair<RIDType, uint32_t> {
        return {1, OnGetRid4IndexResult::UPDATED_NODE}; };
    repeatNode->caches_.GetCacheItem4RID(1).value()->node_ = nullptr;
    auto item5 = repeatNode->caches_.CallOnGetRid4Index(0);
    EXPECT_EQ(item5, std::nullopt);

    repeatNode->caches_.onGetRid4Index_ = [](IndexType index)->std::pair<RIDType, uint32_t> {
        return {0, OnGetRid4IndexResult::UPDATED_NODE}; };
    auto item6 = repeatNode->caches_.CallOnGetRid4Index(0);
    EXPECT_EQ(item6, std::nullopt);

    repeatNode->caches_.onGetRid4Index_ = [](IndexType index)->std::pair<RIDType, uint32_t> {
        return {1, OnGetRid4IndexResult::NO_NODE}; };
    auto item7 = repeatNode->caches_.CallOnGetRid4Index(0);
    EXPECT_EQ(item7, std::nullopt);
}

/**
 * @tc.name: ConvertFromToIndex001
 * @tc.desc: Test caches.ConvertFromToIndex
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, ConvertFromToIndex001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(6);
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
 * @tc.name: ConvertFromToIndex002
 * @tc.desc: Test caches.ConvertFromToIndexRevert
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, ConvertFromToIndex002, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(6);
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

/**
 * @tc.name: UpdateFrameChildIndexRecord001
 * @tc.desc: Test node.updateFrameChildIndexRecord
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, UpdateFrameChildIndexRecord001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(6);
    repeatNode->minFrameChildIndex_ = 0;
    repeatNode->maxFrameChildIndex_ = 0;
    repeatNode->needRecordFirstFrameChild_ = true;

    /**
     * @tc.steps: step1.
     * @tc.expected: minFrameChildIndex_ is 2, maxFrameChildIndex_ is 2, needRecordFirstFrameChild_ is false.
     */
    repeatNode->updateFrameChildIndexRecord(2);
    EXPECT_EQ(repeatNode->minFrameChildIndex_, 2);
    EXPECT_EQ(repeatNode->maxFrameChildIndex_, 2);
    EXPECT_EQ(repeatNode->needRecordFirstFrameChild_, false);

    /**
     * @tc.steps: step2.
     * @tc.expected: minFrameChildIndex_ is 1, maxFrameChildIndex_ is 3
     */
    repeatNode->updateFrameChildIndexRecord(1);
    repeatNode->updateFrameChildIndexRecord(3);
    EXPECT_EQ(repeatNode->minFrameChildIndex_, 1);
    EXPECT_EQ(repeatNode->maxFrameChildIndex_, 3);
}

/**
 * @tc.name: NotifyColorModeChange001
 * @tc.desc: Test caches.NotifyColorModeChange
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, NotifyColorModeChange001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
    repeatNode->caches_.l1Rid4Index_ = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}
    };
    RefPtr<UINode> uiNode = AceType::MakeRefPtr<FrameNode>("node", 2016, AceType::MakeRefPtr<Pattern>());
    CacheItem cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode, true);
    repeatNode->caches_.cacheItem4Rid_ = {
        { 1, cacheItem }, { 2, cacheItem }, { 3, cacheItem }, { 4, cacheItem }
    };
    repeatNode->NotifyColorModeChange(1);
    EXPECT_TRUE(cacheItem->node_->measureAnyWay_);
}

/**
 * @tc.name: NotifyColorModeChange002
 * @tc.desc: Test caches.NotifyColorModeChange
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, NotifyColorModeChange002, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
    repeatNode->caches_.l1Rid4Index_ = {
        {0, 1}
    };
    RefPtr<UINode> uiNode = AceType::MakeRefPtr<CustomNode>(2016, "node");
    RefPtr<UINode> childNode = AceType::MakeRefPtr<CustomNode>(2016, "childNode");
    uiNode->children_ = { childNode };
    uiNode->SetDarkMode(true);
    CacheItem cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode, true);
    repeatNode->caches_.cacheItem4Rid_ = {
        { 1, cacheItem }
    };
    EXPECT_FALSE(childNode->CheckIsDarkMode());
    repeatNode->NotifyColorModeChange(1);
    EXPECT_TRUE(childNode->CheckIsDarkMode());
}

/**
 * @tc.name: UpdateIsL1001
 * @tc.desc: Test caches.UpdateIsL1
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, UpdateIsL1001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
    RefPtr<UINode> uiNode = AceType::MakeRefPtr<FrameNode>("node", 2017, AceType::MakeRefPtr<Pattern>());
    CacheItem cacheItem0 = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode, true);
    CacheItem cacheItem1 = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode, true);
    cacheItem0->node_ = nullptr;
    repeatNode->caches_.UpdateIsL1(cacheItem0, false);
    EXPECT_EQ(cacheItem0->isL1_, false);
    EXPECT_EQ(repeatNode->caches_.recycledNodeIds_.size(), 0);
    repeatNode->caches_.UpdateIsL1(cacheItem1, false);
    EXPECT_EQ(cacheItem1->isL1_, false);
    EXPECT_EQ(repeatNode->caches_.recycledNodeIds_.size(), 1);
    repeatNode->caches_.UpdateIsL1(cacheItem0, true);
    EXPECT_EQ(cacheItem0->isL1_, true);
    EXPECT_EQ(repeatNode->caches_.recycledNodeIds_.size(), 1);
    repeatNode->caches_.UpdateIsL1(cacheItem1, true);
    EXPECT_EQ(cacheItem1->isL1_, true);
    EXPECT_EQ(repeatNode->caches_.recycledNodeIds_.size(), 0);
    repeatNode->caches_.UpdateIsL1(cacheItem1, false, false);
    EXPECT_EQ(cacheItem1->isL1_, false);
    EXPECT_EQ(repeatNode->caches_.recycledNodeIds_.size(), 0);
}

/**
 * @tc.name: UpdateL1Rid4Index001
 * @tc.desc: Test caches.UpdateL1Rid4Index
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2TestNg, UpdateL1Rid4Index001, TestSize.Level1)
{
    auto repeatNode = CreateRepeatVirtualNode(10);
    RefPtr<UINode> uiNode0 = AceType::MakeRefPtr<FrameNode>("node", 2018, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> uiNode1 = AceType::MakeRefPtr<FrameNode>("node", 2019, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> uiNode2 = AceType::MakeRefPtr<FrameNode>("node", 2020, AceType::MakeRefPtr<Pattern>());
    CacheItem cacheItem0 = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode0, true);
    CacheItem cacheItem1 = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode1, true);
    CacheItem cacheItem2 = RepeatVirtualScroll2CacheItem::MakeCacheItem(uiNode2, false);
    repeatNode->caches_.cacheItem4Rid_ = {
        { 1, cacheItem0 }, { 2, cacheItem1 }, { 3, cacheItem2 }
    };
    repeatNode->caches_.UpdateL1Rid4Index({ { 1, 2 }, { 2, 3 } }, { 2 });
    EXPECT_EQ(cacheItem0->isL1_, false);
    EXPECT_EQ(cacheItem1->isL1_, true);
    EXPECT_EQ(cacheItem2->isL1_, true);
}

} // namespace OHOS::Ace::NG