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
#include "swiper_test_ng.h"

#include "core/components_ng/syntax/repeat_virtual_scroll_2_caches.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"

namespace OHOS::Ace::NG {
class SwiperPatternTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: HasCustomIndicatorOffset
 * @tc.desc: Test SwiperLayoutAlgorithm HasCustomIndicatorOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, HasCustomIndicatorOffset, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutAlgorithm> swiperLayoutAlgorithm = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    RefPtr<SwiperIndicatorLayoutProperty> swiperIndicatorLayoutProperty =
        AceType::MakeRefPtr<SwiperIndicatorLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = swiperIndicatorLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> indicatorWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, swiperIndicatorLayoutProperty);
    indicatorWrapper->hostNode_ = frameNode;
    auto result = swiperLayoutAlgorithm->HasCustomIndicatorOffset(indicatorWrapper);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CalcWillScrollOffset001
 * @tc.desc: Test SwiperPattern CalcWillScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcWillScrollOffset001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    swiperPattern->itemPosition_.clear();
    auto result = swiperPattern->CalcWillScrollOffset(2);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: CalcWillScrollOffset002
 * @tc.desc: Test SwiperPattern CalcWillScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcWillScrollOffset002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    swiperLayoutProperty->propMinSize_ = std::nullopt;
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->ignoreItemSpace_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->contentMainSize_ = 10.0f;
    swiperPattern->prevMarginIgnoreBlank_ = true;
    swiperPattern->nextMarginIgnoreBlank_ = true;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[3] = itemInfo;
    auto result = swiperPattern->CalcWillScrollOffset(2);
    EXPECT_EQ(result, 2.0f);
}

/**
 * @tc.name: CalcWillScrollOffset003
 * @tc.desc: Test SwiperPattern CalcWillScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcWillScrollOffset003, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    swiperLayoutProperty->propMinSize_ = std::nullopt;
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->ignoreItemSpace_ = true;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->contentMainSize_ = 10.0f;
    swiperPattern->prevMarginIgnoreBlank_ = true;
    swiperPattern->nextMarginIgnoreBlank_ = true;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[3] = itemInfo;
    auto result = swiperPattern->CalcWillScrollOffset(2);
    EXPECT_EQ(result, 10.0f);
}

/**
 * @tc.name: CalcWillScrollOffset004
 * @tc.desc: Test SwiperPattern CalcWillScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcWillScrollOffset004, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    swiperLayoutProperty->propMinSize_ = std::nullopt;
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->ignoreItemSpace_ = true;
    swiperLayoutProperty->propSwipeByGroup_ = false;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->contentMainSize_ = 10.0f;
    swiperPattern->prevMarginIgnoreBlank_ = true;
    swiperPattern->nextMarginIgnoreBlank_ = true;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[3] = itemInfo;
    auto result = swiperPattern->CalcWillScrollOffset(2);
    EXPECT_EQ(result, 2.0f);
}

/**
 * @tc.name: CalcWillScrollOffset005
 * @tc.desc: Test SwiperPattern CalcWillScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcWillScrollOffset005, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    swiperLayoutProperty->propMinSize_ = std::nullopt;
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->ignoreItemSpace_ = true;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->contentMainSize_ = 10.0f;
    swiperPattern->prevMarginIgnoreBlank_ = true;
    swiperPattern->nextMarginIgnoreBlank_ = true;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[3] = itemInfo;
    auto result = swiperPattern->CalcWillScrollOffset(5);
    EXPECT_EQ(result, 10.0f);
}

/**
 * @tc.name: CalcWillScrollOffset006
 * @tc.desc: Test SwiperPattern CalcWillScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcWillScrollOffset006, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    swiperLayoutProperty->propMinSize_ = std::nullopt;
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->ignoreItemSpace_ = true;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->contentMainSize_ = 10.0f;
    swiperPattern->prevMarginIgnoreBlank_ = true;
    swiperPattern->nextMarginIgnoreBlank_ = true;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[3] = itemInfo;
    swiperPattern->currentIndex_ = 50;
    auto result = swiperPattern->CalcWillScrollOffset(10);
    EXPECT_EQ(result, 10.0f);
}

/**
 * @tc.name: CalcWillScrollOffset007
 * @tc.desc: Test SwiperPattern CalcWillScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcWillScrollOffset007, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    swiperLayoutProperty->propMinSize_ = std::nullopt;
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->ignoreItemSpace_ = true;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->contentMainSize_ = 10.0f;
    swiperPattern->prevMarginIgnoreBlank_ = false;
    swiperPattern->nextMarginIgnoreBlank_ = true;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[3] = itemInfo;
    auto result = swiperPattern->CalcWillScrollOffset(5);
    EXPECT_EQ(result, 10.0f);
}

/**
 * @tc.name: CalcWillScrollOffset008
 * @tc.desc: Test SwiperPattern CalcWillScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcWillScrollOffset008, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    swiperLayoutProperty->propMinSize_ = std::nullopt;
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->ignoreItemSpace_ = true;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->contentMainSize_ = 10.0f;
    swiperPattern->prevMarginIgnoreBlank_ = true;
    swiperPattern->nextMarginIgnoreBlank_ = false;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[3] = itemInfo;
    swiperPattern->currentIndex_ = 50;
    auto result = swiperPattern->CalcWillScrollOffset(10);
    EXPECT_EQ(result, 10.0f);
}

/**
 * @tc.name: CalcWillScrollOffset009
 * @tc.desc: Test SwiperPattern CalcWillScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcWillScrollOffset009, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    swiperLayoutProperty->propMinSize_ = std::nullopt;
    swiperLayoutProperty->propDisplayCount_ = 3;
    swiperLayoutProperty->ignoreItemSpace_ = true;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->contentMainSize_ = 10.0f;
    swiperPattern->prevMarginIgnoreBlank_ = true;
    swiperPattern->nextMarginIgnoreBlank_ = true;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[3] = itemInfo;
    swiperPattern->currentIndex_ = 30;
    auto result = swiperPattern->CalcWillScrollOffset(0);
    EXPECT_EQ(result, 10.0f);
}

/**
 * @tc.name: CalcWillScrollOffset010
 * @tc.desc: Test SwiperPattern CalcWillScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcWillScrollOffset010, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    swiperLayoutProperty->propMinSize_ = std::nullopt;
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->ignoreItemSpace_ = true;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->contentMainSize_ = 10.0f;
    swiperPattern->prevMarginIgnoreBlank_ = true;
    swiperPattern->nextMarginIgnoreBlank_ = true;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[3] = itemInfo;
    swiperPattern->currentIndex_ = 100;
    auto result = swiperPattern->CalcWillScrollOffset(5);
    EXPECT_EQ(result, 10.0f);
}

/**
 * @tc.name: CalcFirstItemWithoutItemSpace001
 * @tc.desc: Test SwiperPattern CalcFirstItemWithoutItemSpace
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcFirstItemWithoutItemSpace001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    swiperLayoutProperty->ignoreItemSpace_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->itemPosition_.clear();
    auto result = swiperPattern->CalcFirstItemWithoutItemSpace();
    EXPECT_EQ(result.first, 0);
}

/**
 * @tc.name: CalcFirstItemWithoutItemSpace002
 * @tc.desc: Test SwiperPattern CalcFirstItemWithoutItemSpace
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcFirstItemWithoutItemSpace002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    swiperLayoutProperty->ignoreItemSpace_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = -8.0f;
    itemInfo.endPos = -2.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[3] = itemInfo;
    auto result = swiperPattern->CalcFirstItemWithoutItemSpace();
    EXPECT_EQ(result.first, 3);
}

/**
 * @tc.name: CalcComingIndex001
 * @tc.desc: Test SwiperPattern CalcComingIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CalcComingIndex001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->ignoreItemSpace_ = true;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = -2.0f;
    itemInfo.endPos = -8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[3] = itemInfo;
    swiperPattern->currentIndex_ = 50;
    auto result = swiperPattern->CalcComingIndex(2.0f);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: UpdateBottomTypeOnMultipleRTL001
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultipleRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultipleRTL001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 3;
    swiperPattern->targetIndex_ = 0;
    swiperPattern->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    swiperPattern->UpdateBottomTypeOnMultipleRTL(2);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: UpdateBottomTypeOnMultipleRTL002
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultipleRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultipleRTL002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 3;
    swiperPattern->targetIndex_ = 2;
    swiperPattern->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    swiperPattern->UpdateBottomTypeOnMultipleRTL(20);
    EXPECT_EQ(swiperPattern->gestureState_, GestureState::GESTURE_STATE_INIT);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
}

/**
 * @tc.name: UpdateBottomTypeOnMultipleRTL003
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultipleRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultipleRTL003, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = 9;
    swiperPattern->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    swiperPattern->UpdateBottomTypeOnMultipleRTL(2);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: UpdateBottomTypeOnMultipleRTL004
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultipleRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultipleRTL004, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = 3;
    swiperPattern->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    swiperPattern->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    swiperPattern->UpdateBottomTypeOnMultipleRTL(9);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
}

/**
 * @tc.name: UpdateBottomTypeOnMultipleRTL005
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultipleRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultipleRTL005, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = 3;
    swiperPattern->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    swiperPattern->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    swiperPattern->UpdateBottomTypeOnMultipleRTL(9);
    EXPECT_EQ(swiperPattern->gestureState_, GestureState::GESTURE_STATE_RELEASE_LEFT);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
}

/**
 * @tc.name: UpdateBottomTypeOnMultipleRTL006
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultipleRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultipleRTL006, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = 3;
    swiperPattern->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    swiperPattern->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    swiperPattern->UpdateBottomTypeOnMultipleRTL(0);
    EXPECT_EQ(swiperPattern->gestureState_, GestureState::GESTURE_STATE_RELEASE_LEFT);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
}

/**
 * @tc.name: UpdateBottomTypeOnMultipleRTL007
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultipleRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultipleRTL007, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 3;
    swiperPattern->targetIndex_ = 3;
    swiperPattern->UpdateBottomTypeOnMultipleRTL(0);
    EXPECT_EQ(swiperPattern->gestureState_, GestureState::GESTURE_STATE_INIT);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: UpdateBottomTypeOnMultipleRTL008
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultipleRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultipleRTL008, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = 3;
    swiperPattern->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    swiperPattern->UpdateBottomTypeOnMultipleRTL(0);
    EXPECT_EQ(swiperPattern->gestureState_, GestureState::GESTURE_STATE_RELEASE_RIGHT);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: OnContentWillScroll001
 * @tc.desc: Test SwiperPattern OnContentWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, OnContentWillScroll001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    auto result = swiperPattern->OnContentWillScroll(2, 3, 2.0f);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: OnContentWillScroll002
 * @tc.desc: Test SwiperPattern OnContentWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, OnContentWillScroll002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    swiperPattern->onContentWillScroll_ =
        std::make_shared<ContentWillScrollEvent>([](const SwiperContentWillScrollResult& result) { return true; });
    swiperPattern->targetIndex_ = 3;
    auto result = swiperPattern->OnContentWillScroll(3, 3, 2.0f);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: CheckContentWillScroll001
 * @tc.desc: Test SwiperPattern CheckContentWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, CheckContentWillScroll001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    swiperPattern->itemPosition_.clear();
    auto result = swiperPattern->CheckContentWillScroll(2.0f, 2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: UpdateBottomTypeOnMultiple001
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultiple
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultiple001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = 9;
    swiperPattern->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    swiperPattern->UpdateBottomTypeOnMultiple(2);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: UpdateBottomTypeOnMultiple002
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultiple
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultiple002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = 3;
    swiperPattern->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    swiperPattern->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    swiperPattern->UpdateBottomTypeOnMultiple(9);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
}

/**
 * @tc.name: UpdateBottomTypeOnMultiple003
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultiple
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultiple003, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = 3;
    swiperPattern->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    swiperPattern->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    swiperPattern->UpdateBottomTypeOnMultiple(3);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: UpdateBottomTypeOnMultiple004
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultiple
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultiple004, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = 3;
    swiperPattern->gestureState_ = GestureState::GESTURE_STATE_NONE;
    swiperPattern->UpdateBottomTypeOnMultiple(9);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: UpdateBottomTypeOnMultiple005
 * @tc.desc: Test SwiperPattern UpdateBottomTypeOnMultiple
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, UpdateBottomTypeOnMultiple005, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = 3;
    swiperPattern->gestureState_ = GestureState::GESTURE_STATE_NONE;
    swiperPattern->UpdateBottomTypeOnMultiple(0);
    EXPECT_EQ(swiperPattern->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: FindLazyForEachNode001
 * @tc.desc: Test SwiperPattern FindLazyForEachNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FindLazyForEachNode001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
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
    RefPtr<RepeatVirtualScrollNode> node = AceType::MakeRefPtr<RepeatVirtualScrollNode>(2, 5, templateCacheCountMap,
        onCreateNode, onUpdateNode, onGetKeys4Range, onGetTypes4Range, onSetActiveRange, true);
    ASSERT_NE(node, nullptr);
    auto result = swiperPattern->FindLazyForEachNode(node, true);
    EXPECT_EQ(result.value(), AceType::DynamicCast<RepeatVirtualScrollNode>(node));
}

/**
 * @tc.name: FindLazyForEachNode002
 * @tc.desc: Test SwiperPattern FindLazyForEachNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FindLazyForEachNode002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    auto result = swiperPattern->FindLazyForEachNode(node, true);
    EXPECT_EQ(result.value(), AceType::DynamicCast<RepeatVirtualScroll2Node>(node));
}

/**
 * @tc.name: FindForEachNode001
 * @tc.desc: Test SwiperPattern FindForEachNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FindForEachNode001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
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
    RefPtr<RepeatVirtualScrollNode> node = AceType::MakeRefPtr<RepeatVirtualScrollNode>(2, 5, templateCacheCountMap,
        onCreateNode, onUpdateNode, onGetKeys4Range, onGetTypes4Range, onSetActiveRange, true);
    ASSERT_NE(node, nullptr);
    auto result = swiperPattern->FindForEachNode(node, true);
    EXPECT_EQ(result.value(), AceType::DynamicCast<RepeatVirtualScrollNode>(node));
}

/**
 * @tc.name: FindForEachNode002
 * @tc.desc: Test SwiperPattern FindForEachNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FindForEachNode002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    auto result = swiperPattern->FindForEachNode(node, true);
    EXPECT_EQ(result.value(), AceType::DynamicCast<RepeatVirtualScroll2Node>(node));
}

/**
 * @tc.name: FindForEachNode003
 * @tc.desc: Test SwiperPattern FindForEachNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FindForEachNode003, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    auto result = swiperPattern->FindForEachNode(frameNode, false);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: FindForEachNode004
 * @tc.desc: Test SwiperPattern FindForEachNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FindForEachNode004, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    auto result = swiperPattern->FindForEachNode(frameNode, true);
    EXPECT_EQ(result.value(), AceType::DynamicCast<RepeatVirtualScroll2Node>(node));
}

/**
 * @tc.name: FindForEachNode005
 * @tc.desc: Test SwiperPattern FindForEachNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FindForEachNode005, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    auto result = swiperPattern->FindForEachNode(frameNode, true);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: HasRepeatTotalCountDifference001
 * @tc.desc: Test SwiperPattern HasRepeatTotalCountDifference
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, HasRepeatTotalCountDifference001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    swiperPattern->frameNode_ = frameNode;
    auto result = swiperPattern->HasRepeatTotalCountDifference(frameNode);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HasRepeatTotalCountDifference002
 * @tc.desc: Test SwiperPattern HasRepeatTotalCountDifference
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, HasRepeatTotalCountDifference002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperPattern->frameNode_ = frameNode;
    auto result = swiperPattern->HasRepeatTotalCountDifference(frameNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ChangeIndex_AnimationMode001
 * @tc.desc: Test SwiperPattern ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, ChangeIndex_AnimationMode001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    RefPtr<IndicatorPattern> indicatorPattern = AceType::MakeRefPtr<IndicatorPattern>();
    auto indicatorNode = FrameNode::CreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, 2, indicatorPattern);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = std::nullopt;
    swiperPattern->isBindIndicator_ = true;
    swiperPattern->indicatorNode_ = indicatorNode;
    indicatorNode->tag_ = V2::SWIPER_INDICATOR_ETS_TAG;
    indicatorPattern->swiperParameters_ = std::make_shared<SwiperParameters>();
    indicatorPattern->swiperParameters_->maxDisplayCountVal = 7;
    swiperPattern->ChangeIndex(2, SwiperAnimationMode::NO_ANIMATION);
    EXPECT_FALSE(swiperPattern->needFireCustomAnimationEvent_);
    EXPECT_EQ(indicatorPattern->startIndex_, std::nullopt);
    EXPECT_EQ(indicatorPattern->changeIndexWithAnimation_.value(), false);

    swiperPattern->needFireCustomAnimationEvent_ = true;
    swiperPattern->ChangeIndex(2, SwiperAnimationMode::DEFAULT_ANIMATION);
    EXPECT_TRUE(swiperPattern->needFireCustomAnimationEvent_);
    EXPECT_EQ(indicatorPattern->changeIndexWithAnimation_.value(), true);

    swiperPattern->ChangeIndex(2, SwiperAnimationMode::FAST_ANIMATION);
    EXPECT_TRUE(swiperPattern->needFireCustomAnimationEvent_);
    EXPECT_EQ(indicatorPattern->changeIndexWithAnimation_.value(), true);
}

/**
 * @tc.name: ChangeIndex_Bool001
 * @tc.desc: Test SwiperPattern ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, ChangeIndex_Bool001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    RefPtr<IndicatorPattern> indicatorPattern = AceType::MakeRefPtr<IndicatorPattern>();
    auto indicatorNode = FrameNode::CreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, 2, indicatorPattern);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = 0;
    swiperPattern->isBindIndicator_ = true;
    swiperPattern->indicatorNode_ = indicatorNode;
    indicatorNode->tag_ = V2::SWIPER_INDICATOR_ETS_TAG;
    indicatorPattern->swiperParameters_ = std::make_shared<SwiperParameters>();
    indicatorPattern->swiperParameters_->maxDisplayCountVal = 7;
    swiperPattern->ChangeIndex(2, true);
    indicatorPattern->changeIndexWithAnimation_ = std::nullopt;
    swiperPattern->fastCurrentIndex_ = 2;
    EXPECT_EQ(indicatorPattern->changeIndexWithAnimation_, std::nullopt);
    EXPECT_TRUE(swiperPattern->needFireCustomAnimationEvent_);
    EXPECT_EQ(swiperPattern->fastCurrentIndex_.value(), 2);

    swiperPattern->targetIndex_ = std::nullopt;
    swiperPattern->ChangeIndex(2, true);
    EXPECT_FALSE(swiperPattern->fastCurrentIndex_.has_value());
    EXPECT_TRUE(swiperPattern->needFireCustomAnimationEvent_);
    EXPECT_EQ(indicatorPattern->startIndex_, std::nullopt);
    EXPECT_EQ(indicatorPattern->changeIndexWithAnimation_.value(), true);

    swiperPattern->ChangeIndex(2, false);
    EXPECT_FALSE(swiperPattern->fastCurrentIndex_.has_value());
    EXPECT_FALSE(swiperPattern->needFireCustomAnimationEvent_);
    EXPECT_EQ(indicatorPattern->changeIndexWithAnimation_.value(), false);
}

/**
 * @tc.name: AutoLinearIsOutOfBoundary001
 * @tc.desc: Test SwiperPattern AutoLinearIsOutOfBoundary
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, AutoLinearIsOutOfBoundary001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    frameNode->children_.emplace_back(node);
    RefPtr<IndicatorPattern> indicatorPattern = AceType::MakeRefPtr<IndicatorPattern>();
    auto indicatorNode = FrameNode::CreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, 2, indicatorPattern);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 2;
    swiperPattern->targetIndex_ = std::nullopt;
    swiperPattern->isBindIndicator_ = true;
    swiperPattern->indicatorNode_ = indicatorNode;
    indicatorNode->tag_ = V2::SWIPER_INDICATOR_ETS_TAG;
    indicatorPattern->swiperParameters_ = std::make_shared<SwiperParameters>();
    indicatorPattern->swiperParameters_->maxDisplayCountVal = 7;
    swiperPattern->itemPosition_.clear();
    auto result = swiperPattern->AutoLinearIsOutOfBoundary(2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AutoLinearIsOutOfBoundary002
 * @tc.desc: Test SwiperPattern AutoLinearIsOutOfBoundary
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, AutoLinearIsOutOfBoundary002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->itemPosition_.clear();
    swiperPattern->hasCachedCapture_ = true;
    auto result = swiperPattern->AutoLinearIsOutOfBoundary(2.0f);
    EXPECT_FALSE(result);

    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_[3] = itemInfo;
    result = swiperPattern->AutoLinearIsOutOfBoundary(4.0f);
    EXPECT_FALSE(result);

    frameNode->children_.clear();
    frameNode->children_.emplace_back(frameNode);
    swiperLayoutProperty->propDisplayCount_ = 1;
    swiperPattern->itemPosition_[2] = itemInfo;
    result = swiperPattern->AutoLinearIsOutOfBoundary(6.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetDistanceToEdge001
 * @tc.desc: Test SwiperPattern GetDistanceToEdge
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, GetDistanceToEdge001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index = [](int32_t index) {
        return std::make_pair(2, 0);
    };
    std::function<void(IndexType, IndexType)> onRecycleItems = [](int32_t start, int32_t end) {};
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    frameNode->children_.emplace_back(node);
    swiperLayoutProperty->propDisplayCount_ = 5;
    swiperLayoutProperty->propSwipeByGroup_ = true;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[0] = itemInfo;
    auto result = swiperPattern->GetDistanceToEdge();
    EXPECT_EQ(result, -2.0f);
}

/**
 * @tc.name: FocusMoveOnKey001
 * @tc.desc: Test SwiperPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FocusMoveOnKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with displayCount 4 and 10 items.
     */
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 4);
    CreateSwiperItems(10);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_EQ(pattern_->currentFocusIndex_, 0);
    for (auto& item : pattern_->itemPosition_) {
        auto child = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(item.first));
        auto focusHub = child->GetFocusHub();
        EXPECT_TRUE(focusHub->IsEnabled());
        EXPECT_TRUE(focusHub->IsShow());
        EXPECT_TRUE(focusHub->focusable_);
        EXPECT_TRUE(focusHub->parentFocusable_);
    }
    /**
     * @tc.steps: step2. Press right key.
     * @tc.expected: currentFocusIndex_ change from 0 to 1.
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 1);
}

/**
 * @tc.name: FocusMoveOnKey002
 * @tc.desc: Test SwiperPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FocusMoveOnKey002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with displayCount 4 and 10 items.
     */
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 4);
    CreateSwiperItems(10);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_EQ(pattern_->currentFocusIndex_, 0);
    /**
     * @tc.steps: step2. Make the second child not focusable and press right key.
     * @tc.expected: currentFocusIndex_ change from 0 to 2.
     */
    auto secondChild = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(1));
    ViewAbstract::SetFocusable(AceType::RawPtr(secondChild), false);
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 2);
}

/**
 * @tc.name: FocusMoveOnKey003
 * @tc.desc: Test SwiperPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FocusMoveOnKey003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with displayCount 4 and 10 items.
     */
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 4);
    CreateSwiperItems(10);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_EQ(pattern_->currentFocusIndex_, 0);
    /**
     * @tc.steps: step2. Make the second child not visible and press right key.
     * @tc.expected: currentFocusIndex_ change from 0 to 2, currentIndex_ not change.
     */
    auto secondChild = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(1));
    ViewAbstract::SetVisibility(AceType::RawPtr(secondChild), VisibleType::INVISIBLE);
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 2);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    /**
     * @tc.steps: step3. Press left key.
     * @tc.expected: currentFocusIndex_ change from 2 to 0, currentIndex_ not change.
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 0);
    EXPECT_EQ(pattern_->currentIndex_, 0);
}

/**
 * @tc.name: FocusMoveOnKey004
 * @tc.desc: Test SwiperPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FocusMoveOnKey004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with displayCount 4 and 10 items.
     */
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 4);
    CreateSwiperItems(10);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_EQ(pattern_->currentFocusIndex_, 0);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    /**
     * @tc.steps: step2. Make the children from 2 to 4 not enabled and press right key.
     * @tc.expected: currentIndex_ change from 0 to 1, currentFocusIndex_ change from 0 to 4.
     */
    for (auto i = 1; i < 4; i++) {
        auto secondChild = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(i));
        ViewAbstract::SetEnabled(AceType::RawPtr(secondChild), false);
    }
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 4);
    EXPECT_EQ(pattern_->currentIndex_, 1);
    /**
     * @tc.steps: step3. Press left key.
     * @tc.expected: currentIndex_ change from 1 to 0, currentFocusIndex_ change from 4 to 0.
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 0);
    EXPECT_EQ(pattern_->currentIndex_, 0);
}

/**
 * @tc.name: FocusMoveOnKey005
 * @tc.desc: Test SwiperPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FocusMoveOnKey005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with displayCount 4, swipeByGroup and 10 items.
     */
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 4);
    SwiperModelNG::SetSwipeByGroup(AceType::RawPtr(frameNode_), true);
    CreateSwiperItems(10);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_EQ(pattern_->currentFocusIndex_, 0);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    /**
     * @tc.steps: step2. Make the children from 2 to 5 not enabled and press right key.
     * @tc.expected: currentIndex_ change from 0 to 5, currentFocusIndex_ change from 0 to 4.
     */
    for (auto i = 1; i < 5; i++) {
        auto secondChild = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(i));
        ViewAbstract::SetEnabled(AceType::RawPtr(secondChild), false);
    }
    EXPECT_TRUE(pattern_->isVisibleArea_);
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 5);
    EXPECT_EQ(pattern_->currentIndex_, 4);
    /**
     * @tc.steps: step3. Press left key.
     * @tc.expected: currentIndex_ change from 4 to -1, currentFocusIndex_ change from 4 to 0.
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, -1);
    EXPECT_EQ(pattern_->currentIndex_, 0);
}

/**
 * @tc.name: FocusMoveOnKey006
 * @tc.desc: Test SwiperPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FocusMoveOnKey006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with displayCount 4, swipeByGroup and 10 items.
     */
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 4);
    SwiperModelNG::SetSwipeByGroup(AceType::RawPtr(frameNode_), true);
    CreateSwiperItems(10);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_EQ(pattern_->currentFocusIndex_, 0);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    EXPECT_TRUE(SwiperModelNG::GetLoop(AceType::RawPtr(frameNode_)));
    /**
     * @tc.steps: step2. Make the second child not enabled and press right key.
     * @tc.expected: currentIndex_ is not changed, currentFocusIndex_ change from 0 to 2.
     */
    auto secondChild = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(1));
    ViewAbstract::SetEnabled(AceType::RawPtr(secondChild), false);
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 2);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    /**
     * @tc.steps: step3. Press left key.
     * @tc.expected: currentIndex_ is not changed, currentFocusIndex_ change from 2 to 0.
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 0);
    EXPECT_EQ(pattern_->currentIndex_, 0);
}
} // namespace OHOS::Ace::NG