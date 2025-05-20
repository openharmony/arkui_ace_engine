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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> repeatVirtualScroll2Node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
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
} // namespace OHOS::Ace::NG