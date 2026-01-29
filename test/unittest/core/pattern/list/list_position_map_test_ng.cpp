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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/list/list_position_map.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListPositionMapTestNg : public TestNG {
public:
};

/**
 * @tc.name: CalculateUINode001
 * @tc.desc: Test ListPositionMap CalculateUINode
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, CalculateUINode001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    auto listNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listItemGroupPattern);
    ASSERT_NE(listNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(node, nullptr);
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    lazyForEachNode->children_.clear();
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listNode->children_.clear();
    listNode->children_ = { lazyForEachNode };
    listPositionMap->curIndex_ = 2;
    listPositionMap->CalculateUINode(listNode);
    EXPECT_EQ(listPositionMap->curRowHeight_, 0.0f);
    EXPECT_EQ(listPositionMap->curIndex_, 2);
}

/**
 * @tc.name: CalculateUINode002
 * @tc.desc: Test ListPositionMap CalculateUINode
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, CalculateUINode002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    auto listNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listItemGroupPattern);
    ASSERT_NE(listNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(node, nullptr);
    const std::map<std::string, std::pair<bool, uint32_t>> templateCacheCountMap = {
        { "template1", { true, 0 } },
        { "template2", { false, 0 } },
    };
    const std::function<void(uint32_t)> onCreateNode = [](uint32_t index) {};
    const std::function<void(const std::string&, uint32_t)> onUpdateNode = [](const std::string& key, uint32_t index) {
    };
    const std::function<std::list<std::string>(uint32_t, uint32_t)> onGetKeys4Range = [](uint32_t start, uint32_t end) {
        return std::list<std::string> { "template1", "template2" };
    };
    const std::function<std::list<std::string>(uint32_t, uint32_t)> onGetTypes4Range = [](uint32_t start,
                                                                                           uint32_t end) {
        return std::list<std::string> { "template1", "template2" };
    };
    const std::function<void(int32_t, int32_t)> onSetActiveRange = [](int32_t start, int32_t end) {};
    RefPtr<RepeatVirtualScrollNode> repeatVirtualScrollNode = AceType::MakeRefPtr<RepeatVirtualScrollNode>(2, 5,
        templateCacheCountMap, onCreateNode, onUpdateNode, onGetKeys4Range, onGetTypes4Range, onSetActiveRange, true);
    ASSERT_NE(repeatVirtualScrollNode, nullptr);
    repeatVirtualScrollNode->children_ = { node };
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listNode->children_.clear();
    listNode->children_ = { repeatVirtualScrollNode };
    node->children_ = { listNode };
    std::vector<float> mainSize = { 2.0f, 2.0f, 2.0f };
    RefPtr<ListChildrenMainSize> listChildrenMainSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listPositionMap->childrenSize_ = listChildrenMainSize;
    listPositionMap->curIndex_ = 2;
    listPositionMap->curRowHeight_ = 0.0f;
    listPositionMap->CalculateUINode(listNode);
    EXPECT_EQ(listPositionMap->curRowHeight_, 2.0f);
    EXPECT_EQ(listPositionMap->curIndex_, 7);
}

/**
 * @tc.name: CalculateUINode003
 * @tc.desc: Test ListPositionMap CalculateUINode
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, CalculateUINode003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    auto listNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listItemGroupPattern);
    ASSERT_NE(listNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(node, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> repeatVirtualScroll2Node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
    ASSERT_NE(repeatVirtualScroll2Node, nullptr);
    repeatVirtualScroll2Node->children_ = { node };
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listNode->children_.clear();
    listNode->children_ = { repeatVirtualScroll2Node };
    node->children_ = { listNode };
    std::vector<float> mainSize = { 2.0f, 2.0f, 2.0f };
    RefPtr<ListChildrenMainSize> listChildrenMainSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listPositionMap->childrenSize_ = listChildrenMainSize;
    listPositionMap->curIndex_ = 2;
    listPositionMap->curRowHeight_ = 0.0f;
    listPositionMap->CalculateUINode(listNode);
    EXPECT_EQ(listPositionMap->curRowHeight_, 2.0f);
    EXPECT_EQ(listPositionMap->curIndex_, 4);
}

/**
 * @tc.name: CalculateUINode004
 * @tc.desc: Test ListPositionMap CalculateUINode
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, CalculateUINode004, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    auto listNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listItemGroupPattern);
    ASSERT_NE(listNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(node, nullptr);
    auto customNode = CustomNode::CreateCustomNode(2, "test");
    ASSERT_NE(customNode, nullptr);
    customNode->children_ = { node };
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listNode->children_.clear();
    listNode->children_ = { customNode };
    std::vector<float> mainSize = { 2.0f, 2.0f, 2.0f };
    RefPtr<ListChildrenMainSize> listChildrenMainSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listPositionMap->childrenSize_ = listChildrenMainSize;
    node->children_ = { listNode };
    listPositionMap->curIndex_ = 2;
    listPositionMap->curRowHeight_ = 0.0f;
    listPositionMap->CalculateUINode(listNode);
    EXPECT_EQ(listPositionMap->curRowHeight_, 0.0f);
    EXPECT_EQ(listPositionMap->curIndex_, 3);
}

/**
 * @tc.name: GetStartIndexAndPos001
 * @tc.desc: Test ListPositionMap GetStartIndexAndPos
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, GetStartIndexAndPos001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listPositionMap->posMap_.clear();
    auto result = listPositionMap->GetStartIndexAndPos();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 0.0f);
}

/**
 * @tc.name: GetLazyForEachChildIsGroup001
 * @tc.desc: Test ListPositionMap GetLazyForEachChildIsGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, GetLazyForEachChildIsGroup001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    auto listNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listItemGroupPattern);
    ASSERT_NE(listNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(node, nullptr);
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    lazyForEachNode->children_.clear();
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listNode->children_.clear();
    listNode->children_ = { node, node };
    listNode->parent_ = node;
    node->children_ = { lazyForEachNode };
    listPositionMap->curIndex_ = 2;
    auto result = listPositionMap->GetLazyForEachChildIsGroup(listNode);
    EXPECT_EQ(listPositionMap->curIndex_, 2);
    EXPECT_FALSE(result.value());
}

/**
 * @tc.name: GetLazyForEachChildIsGroup002
 * @tc.desc: Test ListPositionMap GetLazyForEachChildIsGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, GetLazyForEachChildIsGroup002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    auto listNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listItemGroupPattern);
    ASSERT_NE(listNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(node, nullptr);
    auto customNode = CustomNode::CreateCustomNode(2, "test");
    ASSERT_NE(customNode, nullptr);
    customNode->children_.clear();
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listNode->children_.clear();
    listNode->children_ = { customNode, node };
    listNode->parent_ = node;
    listPositionMap->curIndex_ = 2;
    auto result = listPositionMap->GetLazyForEachChildIsGroup(listNode);
    EXPECT_EQ(listPositionMap->curRowHeight_, 0.0f);
    EXPECT_EQ(listPositionMap->curIndex_, 2);
    EXPECT_FALSE(result.value());
}

/**
 * @tc.name: GetLazyForEachChildIsGroup003
 * @tc.desc: Test ListPositionMap GetLazyForEachChildIsGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, GetLazyForEachChildIsGroup003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    auto listNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listItemGroupPattern);
    ASSERT_NE(listNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(node, nullptr);
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listNode->children_.clear();
    listNode->parent_ = node;
    listPositionMap->curIndex_ = 2;
    listPositionMap->GetLazyForEachChildIsGroup(listNode);
    EXPECT_EQ(listPositionMap->curRowHeight_, 0.0f);
    EXPECT_EQ(listPositionMap->curIndex_, 2);
}

/**
 * @tc.name: UpdateGroupPosMap001
 * @tc.desc: Test ListPositionMap UpdateGroupPosMap
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, UpdateGroupPosMap001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    std::vector<float> mainSize = { 2.0f, 2.0f, 2.0f };
    RefPtr<ListChildrenMainSize> listChildrenMainSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listPositionMap->childrenSize_ = listChildrenMainSize;
    listPositionMap->curIndex_ = 2;
    listPositionMap->curIndex_ = 2;
    listPositionMap->totalItemCount_ = 2;
    listPositionMap->curRowHeight_ = 4.0f;
    listPositionMap->space_ = 1.0f;
    listPositionMap->curLine_ = 1;
    listPositionMap->lanes_ = 1;
    listPositionMap->dirty_ = LIST_UPDATE_SPACE;
    listPositionMap->headerSize_ = 2.0f;
    listPositionMap->footerSize_ = 4.0f;
    listPositionMap->UpdateGroupPosMap(2, 1, 1.0f, listChildrenMainSize, 2.0f, 4.0f);
    EXPECT_EQ(listPositionMap->curRowHeight_, 0.0f);
    EXPECT_EQ(listPositionMap->curIndex_, 0);
}

/**
 * @tc.name: UpdateGroupPosMap002
 * @tc.desc: Test ListPositionMap UpdateGroupPosMap
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, UpdateGroupPosMap002, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    std::vector<float> mainSize = { 2.0f, 2.0f, 2.0f };
    RefPtr<ListChildrenMainSize> listChildrenMainSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listPositionMap->childrenSize_ = listChildrenMainSize;
    listPositionMap->curIndex_ = 2;
    listPositionMap->curIndex_ = 2;
    listPositionMap->totalItemCount_ = 0;
    listPositionMap->curRowHeight_ = 4.0f;
    listPositionMap->space_ = 1.0f;
    listPositionMap->curLine_ = 1;
    listPositionMap->lanes_ = 1;
    listPositionMap->dirty_ = LIST_UPDATE_SPACE;
    listPositionMap->headerSize_ = 2.0f;
    listPositionMap->footerSize_ = 4.0f;
    listPositionMap->totalHeight_ = 4.0f;
    listPositionMap->UpdateGroupPosMap(0, 1, 1.0f, listChildrenMainSize, 2.0f, 4.0f);
    EXPECT_EQ(listPositionMap->totalHeight_, 0.0f);
}

/**
 * @tc.name: ReversePosMap001
 * @tc.desc: Test ListPositionMap ReversePosMap
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ReversePosMap001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listPositionMap->posMap_[0] = { 2.0f, 4.0f, true };
    listPositionMap->posMap_[1] = { 2.0f, 4.0f, true };
    listPositionMap->posMap_[2] = { 3.0f, 6.0f, true };
    listPositionMap->totalItemCount_ = 3;
    listPositionMap->space_ = 1.0f;
    listPositionMap->ReversePosMap();
    EXPECT_EQ(listPositionMap->totalHeight_, 11.0f);
    EXPECT_EQ(listPositionMap->posMap_[0].mainPos, 0.0f);
    EXPECT_EQ(listPositionMap->posMap_[1].mainPos, 5.0f);
}

/**
 * @tc.name: CalculateGroupNode001
 * @tc.desc: Test ListPositionMap CalculateGroupNode
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, CalculateGroupNode001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    std::vector<float> mainSize = { 2.0f, 2.0f, 2.0f };
    RefPtr<ListChildrenMainSize> listChildrenMainSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listPositionMap->childrenSize_ = listChildrenMainSize;
    listPositionMap->curIndex_ = 2;
    listPositionMap->totalHeight_ = 2.0f;
    listPositionMap->curRowHeight_ = 4.0f;
    listPositionMap->space_ = 1.0f;
    listPositionMap->curLine_ = 1;
    listPositionMap->CalculateGroupNode();
    EXPECT_EQ(listPositionMap->posMap_[0].mainPos, 0.0f);
    EXPECT_EQ(listPositionMap->posMap_[2].mainPos, 7.0f);
}

/**
 * @tc.name: UpdatePosMap001
 * @tc.desc: Test ListPositionMap UpdatePosMap
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, UpdatePosMap001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listItemGroupPattern->itemStartIndex_ = 2;
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    std::vector<float> mainSize = { 2.0f, 2.0f, 2.0f };
    RefPtr<ListChildrenMainSize> listChildrenMainSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listPositionMap->childrenSize_ = listChildrenMainSize;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 2;
    listPositionMap->curIndex_ = 2;
    listPositionMap->curIndex_ = 2;
    listPositionMap->totalItemCount_ = 2;
    listPositionMap->curRowHeight_ = 4.0f;
    listPositionMap->space_ = 1.0f;
    listPositionMap->curLine_ = 1;
    listPositionMap->lanes_ = 1;
    listPositionMap->dirty_ = LIST_UPDATE_DEFAULT_SIZE;
    listPositionMap->UpdatePosMap(&layoutWrapper, 1, 1.0f, listChildrenMainSize);
    EXPECT_EQ(listPositionMap->curRowHeight_, 2.0f);
    EXPECT_EQ(listPositionMap->curIndex_, 0);
}

/**
 * @tc.name: ListPositionMapUpdatePosWithCheck001
 * @tc.desc: Test ListPositionMap UpdatePosWithCheck with smaller mainSize
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapUpdatePosWithCheck001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    // Initialize with a larger size
    ListPositionInfo posInfo = { 0.0f, 200.0f, false };
    listPositionMap->UpdatePos(0, posInfo);

    // Update with a smaller size - should not update
    ListPositionInfo newPosInfo = { 0.0f, 100.0f, false };
    listPositionMap->UpdatePosWithCheck(0, newPosInfo);

    auto result = listPositionMap->GetPositionInfo(0);
    EXPECT_EQ(result.mainSize, 200.0f); // Should keep the larger size
}

/**
 * @tc.name: ListPositionMapUpdatePosWithCheck002
 * @tc.desc: Test ListPositionMap UpdatePosWithCheck with larger mainSize
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapUpdatePosWithCheck002, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    // Initialize with a smaller size
    ListPositionInfo posInfo = { 0.0f, 100.0f, false };
    listPositionMap->UpdatePos(0, posInfo);

    // Update with a larger size - should update
    ListPositionInfo newPosInfo = { 0.0f, 200.0f, false };
    listPositionMap->UpdatePosWithCheck(0, newPosInfo);

    auto result = listPositionMap->GetPositionInfo(0);
    EXPECT_EQ(result.mainSize, 200.0f); // Should update to larger size
}

/**
 * @tc.name: ListPositionMapUpdatePosWithCheck003
 * @tc.desc: Test ListPositionMap UpdatePosWithCheck with new index
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapUpdatePosWithCheck003, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    // Update a non-existent index
    ListPositionInfo posInfo = { 0.0f, 100.0f, false };
    listPositionMap->UpdatePosWithCheck(0, posInfo);

    auto result = listPositionMap->GetPositionInfo(0);
    EXPECT_EQ(result.mainSize, 100.0f);
    EXPECT_FALSE(result.isGroup);
}

/**
 * @tc.name: ListPositionMapUpdatePosWithCheck004
 * @tc.desc: Test ListPositionMap UpdatePosWithCheck with isGroup update
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapUpdatePosWithCheck004, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    // Initialize with isGroup = false
    ListPositionInfo posInfo = { 0.0f, 100.0f, false };
    listPositionMap->UpdatePos(0, posInfo);

    // Update isGroup to true
    ListPositionInfo newPosInfo = { 0.0f, 100.0f, true };
    listPositionMap->UpdatePosWithCheck(0, newPosInfo);

    auto result = listPositionMap->GetPositionInfo(0);
    EXPECT_TRUE(result.isGroup);
}

/**
 * @tc.name: ListPositionMapOptimizeBeforeMeasure001
 * @tc.desc: Test ListPositionMap OptimizeBeforeMeasure with zero offset
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapOptimizeBeforeMeasure001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    ListPositionInfo posInfo = { 0.0f, 100.0f, false };
    listPositionMap->UpdatePos(0, posInfo);
    listPositionMap->totalItemCount_ = 1;
    listPositionMap->totalHeight_ = 100.0f;

    int32_t beginIndex = 0;
    float beginPos = 0.0f;
    float offset = 0.0f;
    float contentSize = 100.0f;

    listPositionMap->OptimizeBeforeMeasure(beginIndex, beginPos, offset, contentSize);

    // Should not change
    EXPECT_EQ(beginIndex, 0);
    EXPECT_EQ(beginPos, 0.0f);
}

/**
 * @tc.name: ListPositionMapOptimizeBeforeMeasure002
 * @tc.desc: Test ListPositionMap OptimizeBeforeMeasure with contentSize >= totalHeight
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapOptimizeBeforeMeasure002, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    ListPositionInfo posInfo = { 0.0f, 100.0f, false };
    listPositionMap->UpdatePos(0, posInfo);
    listPositionMap->totalItemCount_ = 1;
    listPositionMap->totalHeight_ = 100.0f;

    int32_t beginIndex = 0;
    float beginPos = 0.0f;
    float offset = 50.0f;
    float contentSize = 200.0f; // Larger than totalHeight

    listPositionMap->OptimizeBeforeMeasure(beginIndex, beginPos, offset, contentSize);

    // Should not change
    EXPECT_EQ(beginIndex, 0);
    EXPECT_EQ(beginPos, 0.0f);
}

/**
 * @tc.name: ListPositionMapUpdatePosMapStart001
 * @tc.desc: Test ListPositionMap UpdatePosMapStart with groupAtStart false
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapUpdatePosMapStart001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    ListPositionInfo posInfo1 = { 100.0f, 100.0f, false };
    ListPositionInfo posInfo2 = { 210.0f, 100.0f, false };
    listPositionMap->UpdatePos(0, posInfo1);
    listPositionMap->UpdatePos(1, posInfo2);

    double listCurrentPos = 0.0f;
    float space = 10.0f;
    int32_t startIndex = 1;
    float startPos = 220.0f;
    bool groupAtStart = false;

    listPositionMap->UpdatePosMapStart(10.0f, listCurrentPos, space, startIndex, startPos, groupAtStart);

    // Should not update listCurrentPos because prevPos < startPos
    EXPECT_EQ(listCurrentPos, 0.0f);
}

/**
 * @tc.name: ListPositionMapUpdatePosMapEnd001
 * @tc.desc: Test ListPositionMap UpdatePosMapEnd with non-existent index
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapUpdatePosMapEnd001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    ListPositionInfo posInfo = { 0.0f, 100.0f, false };
    listPositionMap->UpdatePos(0, posInfo);

    float space = 10.0f;
    int32_t prevEndIndex = 5; // Non-existent
    bool groupAtEnd = true;

    // Should not crash
    listPositionMap->UpdatePosMapEnd(prevEndIndex, space, groupAtEnd);

    auto result = listPositionMap->GetPositionInfo(0);
    EXPECT_EQ(result.mainPos, 0.0f);
}

/**
 * @tc.name: ListChildrenMainSizeGetChildSize001
 * @tc.desc: Test ListChildrenMainSize GetChildSize with rounding mode
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListChildrenMainSizeGetChildSize001, TestSize.Level1)
{
    std::vector<float> mainSize = { 100.5f, 200.3f, 150.7f };
    RefPtr<ListChildrenMainSize> listChildrenMainSize =
        AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 100.0f);

    listChildrenMainSize->SetIsRoundingMode();

    auto size = listChildrenMainSize->GetChildSize(0);
    EXPECT_NEAR(size, Round(100.5f), 0.001f);
}

/**
 * @tc.name: ListChildrenMainSizeGetChildSize002
 * @tc.desc: Test ListChildrenMainSize GetChildSize with invalid index
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListChildrenMainSizeGetChildSize002, TestSize.Level1)
{
    std::vector<float> mainSize = { 100.0f, 200.0f, 150.0f };
    RefPtr<ListChildrenMainSize> listChildrenMainSize =
        AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 50.0f);

    // Test with out-of-bounds index
    auto size = listChildrenMainSize->GetChildSize(10);
    EXPECT_EQ(size, 50.0f); // Should return default size
}

/**
 * @tc.name: ListChildrenMainSizeGetChildSize003
 * @tc.desc: Test ListChildrenMainSize GetChildSize with DEFAULT_SIZE value
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListChildrenMainSizeGetChildSize003, TestSize.Level1)
{
    std::vector<float> mainSize = { -1.0f, 200.0f, 150.0f };
    float defaultSize = 80.0f;
    RefPtr<ListChildrenMainSize> listChildrenMainSize =
        AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, defaultSize);

    // Test with DEFAULT_SIZE (-1.0f)
    auto size = listChildrenMainSize->GetChildSize(0);
    EXPECT_EQ(size, 80.0f); // Should return default size
}

/**
 * @tc.name: ListChildrenMainSizeChangeData001
 * @tc.desc: Test ListChildrenMainSize ChangeData with deleteCount -1
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListChildrenMainSizeChangeData001, TestSize.Level1)
{
    RefPtr<ListChildrenMainSize> listChildrenMainSize =
        AceType::MakeRefPtr<ListChildrenMainSize>();
    listChildrenMainSize->ResizeChildrenSize(5);

    // Test resize with deleteCount -1
    std::vector<float> newChildrenSize;
    listChildrenMainSize->ChangeData(3, -1, newChildrenSize);

    auto size = listChildrenMainSize->GetChildSize(0);
    EXPECT_EQ(size, 0.0f); // Default size
}

/**
 * @tc.name: ListChildrenMainSizeChangeData002
 * @tc.desc: Test ListChildrenMainSize ChangeData with insert
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListChildrenMainSizeChangeData002, TestSize.Level1)
{
    std::vector<float> mainSize = { 100.0f, 200.0f, 150.0f };
    RefPtr<ListChildrenMainSize> listChildrenMainSize =
        AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 50.0f);

    // Insert new items
    std::vector<float> newChildrenSize = { 120.0f, 130.0f };
    listChildrenMainSize->ChangeData(1, 0, newChildrenSize);

    auto size = listChildrenMainSize->GetChildSize(1);
    EXPECT_EQ(size, 120.0f);
}

/**
 * @tc.name: ListChildrenMainSizeChangeData003
 * @tc.desc: Test ListChildrenMainSize ChangeData with delete more than insert
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListChildrenMainSizeChangeData003, TestSize.Level1)
{
    std::vector<float> mainSize = { 100.0f, 200.0f, 150.0f, 180.0f };
    RefPtr<ListChildrenMainSize> listChildrenMainSize =
        AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 50.0f);

    // Delete 3 items, insert 1
    std::vector<float> newChildrenSize = { 120.0f };
    listChildrenMainSize->ChangeData(1, 3, newChildrenSize);

    // Should have 2 items now
    auto size0 = listChildrenMainSize->GetChildSize(0);
    auto size1 = listChildrenMainSize->GetChildSize(1);
    EXPECT_EQ(size0, 100.0f);
    EXPECT_EQ(size1, 120.0f);
}

/**
 * @tc.name: ListPatternHandleTargetIndex001
 * @tc.desc: Test ListPattern HandleTargetIndex with isJump true
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPatternHandleTargetIndex001, TestSize.Level1)
{
    auto listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->targetIndex_ = 5;

    bool result = listPattern->HandleTargetIndex(true);

    EXPECT_TRUE(result);
    EXPECT_TRUE(listPattern->targetIndex_.has_value());
}

/**
 * @tc.name: ListPatternHandleTargetIndex002
 * @tc.desc: Test ListPattern HandleTargetIndex with non-existent target
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPatternHandleTargetIndex002, TestSize.Level1)
{
    auto listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->itemPosition_[0] = { 0, 0.0f, 100.0f, false };
    listPattern->itemPosition_[1] = { 1, 110.0f, 100.0f, false };
    listPattern->targetIndex_ = 5; // Non-existent

    bool result = listPattern->HandleTargetIndex(false);

    EXPECT_FALSE(result);
    EXPECT_FALSE(listPattern->targetIndex_.has_value());
}

/**
 * @tc.name: ListLayoutAlgorithmGetStartIndex001
 * @tc.desc: Test ListLayoutAlgorithm GetStartIndex with empty position
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListLayoutAlgorithmGetStartIndex001, TestSize.Level1)
{
    ListLayoutAlgorithm listLayoutAlgorithm(0);

    auto startIndex = listLayoutAlgorithm.GetStartIndex();

    EXPECT_EQ(startIndex, -1);
}

/**
 * @tc.name: ListLayoutAlgorithmGetEndIndex001
 * @tc.desc: Test ListLayoutAlgorithm GetEndIndex with empty position
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListLayoutAlgorithmGetEndIndex001, TestSize.Level1)
{
    ListLayoutAlgorithm listLayoutAlgorithm(0);

    auto endIndex = listLayoutAlgorithm.GetEndIndex();

    EXPECT_EQ(endIndex, -1);
}

/**
 * @tc.name: ListLayoutAlgorithmGetStartPosition001
 * @tc.desc: Test ListLayoutAlgorithm GetStartPosition with empty position
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListLayoutAlgorithmGetStartPosition001, TestSize.Level1)
{
    ListLayoutAlgorithm listLayoutAlgorithm(0);

    auto startPos = listLayoutAlgorithm.GetStartPosition();

    EXPECT_EQ(startPos, 0.0f);
}

/**
 * @tc.name: ListLayoutAlgorithmGetEndPosition001
 * @tc.desc: Test ListLayoutAlgorithm GetEndPosition with empty position
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListLayoutAlgorithmGetEndPosition001, TestSize.Level1)
{
    ListLayoutAlgorithm listLayoutAlgorithm(0);

    auto endPos = listLayoutAlgorithm.GetEndPosition();

    EXPECT_EQ(endPos, 0.0f);
}

/**
 * @tc.name: ListPositionMapGetRowStartIndex001
 * @tc.desc: Test ListPositionMap GetRowStartIndex with single lane
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapGetRowStartIndex001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    ListPositionInfo posInfo1 = { 0.0f, 100.0f, false };
    ListPositionInfo posInfo2 = { 110.0f, 100.0f, false };
    ListPositionInfo posInfo3 = { 220.0f, 100.0f, false };
    listPositionMap->UpdatePos(0, posInfo1);
    listPositionMap->UpdatePos(1, posInfo2);
    listPositionMap->UpdatePos(2, posInfo3);
    listPositionMap->totalItemCount_ = 3;

    auto startIndex = listPositionMap->GetRowStartIndex(1);

    EXPECT_EQ(startIndex, 1);
}

/**
 * @tc.name: ListPositionMapGetRowStartIndex002
 * @tc.desc: Test ListPositionMap GetRowStartIndex with multi-lane
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapGetRowStartIndex002, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    // Two items on same row (same position)
    ListPositionInfo posInfo = { 0.0f, 100.0f, false };
    listPositionMap->UpdatePos(0, posInfo);
    listPositionMap->UpdatePos(1, posInfo);
    listPositionMap->totalItemCount_ = 2;

    auto startIndex = listPositionMap->GetRowStartIndex(1);

    EXPECT_EQ(startIndex, 0);
}

/**
 * @tc.name: ListPositionMapGetRowEndIndexAndHeight001
 * @tc.desc: Test ListPositionMap GetRowEndIndexAndHeight for last item
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapGetRowEndIndexAndHeight001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    ListPositionInfo posInfo1 = { 0.0f, 100.0f, false };
    ListPositionInfo posInfo2 = { 110.0f, 100.0f, false };
    listPositionMap->UpdatePos(0, posInfo1);
    listPositionMap->UpdatePos(1, posInfo2);
    listPositionMap->totalItemCount_ = 2;
    listPositionMap->totalHeight_ = 210.0f;
    listPositionMap->space_ = 10.0f;
    listPositionMap->footerSize_ = 0.0f;

    auto [endIndex, height] = listPositionMap->GetRowEndIndexAndHeight(1);

    EXPECT_EQ(endIndex, 1);
    EXPECT_GT(height, 0.0f);
}

/**
 * @tc.name: ListPositionMapGetRowEndIndexAndHeight002
 * @tc.desc: Test ListPositionMap GetRowEndIndexAndHeight with footer
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapGetRowEndIndexAndHeight002, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    ListPositionInfo posInfo1 = { 0.0f, 100.0f, false };
    listPositionMap->UpdatePos(0, posInfo1);
    listPositionMap->totalItemCount_ = 1;
    listPositionMap->totalHeight_ = 150.0f;
    listPositionMap->footerSize_ = 50.0f;

    auto [endIndex, height] = listPositionMap->GetRowEndIndexAndHeight(0);

    EXPECT_EQ(endIndex, 0);
    EXPECT_EQ(height, 100.0f); // totalHeight - pos - footer
}

/**
 * @tc.name: ListPositionMapCheckPosMapUpdateRule001
 * @tc.desc: Test ListPositionMap CheckPosMapUpdateRule with NO_CHANGE
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapCheckPosMapUpdateRule001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listPositionMap->ClearDirty();

    auto result = listPositionMap->CheckPosMapUpdateRule();

    EXPECT_EQ(result, ListPosMapUpdate::NO_CHANGE);
}

/**
 * @tc.name: ListPositionMapCheckPosMapUpdateRule002
 * @tc.desc: Test ListPositionMap CheckPosMapUpdateRule with UPDATE_ALL_SIZE
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapCheckPosMapUpdateRule002, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listPositionMap->MarkDirty(LIST_UPDATE_DEFAULT_SIZE);

    auto result = listPositionMap->CheckPosMapUpdateRule();

    EXPECT_EQ(result, ListPosMapUpdate::UPDATE_ALL_SIZE);
}

/**
 * @tc.name: ListPositionMapCheckPosMapUpdateRule003
 * @tc.desc: Test ListPositionMap CheckPosMapUpdateRule with RE_CALCULATE
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapCheckPosMapUpdateRule003, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listPositionMap->MarkDirty(LIST_UPDATE_CHILD_SIZE);

    auto result = listPositionMap->CheckPosMapUpdateRule();

    EXPECT_EQ(result, ListPosMapUpdate::RE_CALCULATE);
}

/**
 * @tc.name: ListPositionMapUpdateTotalCount001
 * @tc.desc: Test ListPositionMap UpdateTotalCount
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapUpdateTotalCount001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    // Add some positions
    ListPositionInfo posInfo = { 0.0f, 100.0f, false };
    listPositionMap->UpdatePos(0, posInfo);
    listPositionMap->UpdatePos(1, posInfo);
    listPositionMap->UpdatePos(2, posInfo);
    listPositionMap->totalItemCount_ = 3;

    // Reduce total count
    listPositionMap->UpdateTotalCount(2);

    EXPECT_EQ(listPositionMap->totalItemCount_, 2);
}

/**
 * @tc.name: ListPositionMapGetPositionInfo001
 * @tc.desc: Test ListPositionMap GetPositionInfo with non-existent index
 * @tc.type: FUNC
 */
HWTEST_F(ListPositionMapTestNg, ListPositionMapGetPositionInfo001, TestSize.Level1)
{
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();

    auto result = listPositionMap->GetPositionInfo(5);

    EXPECT_EQ(result.mainPos, -1.0f);
    EXPECT_EQ(result.mainSize, -1.0f);
}
} // namespace OHOS::Ace::NG