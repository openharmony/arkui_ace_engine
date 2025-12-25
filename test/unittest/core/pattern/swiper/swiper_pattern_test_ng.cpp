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
 * @tc.name: ComputeTargetIndex_CurrentFalse
 * @tc.desc: Test SwiperPattern ComputeTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, ComputeTargetIndex_CurrentFalse, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 3, swiperPattern);
    ASSERT_NE(node, nullptr);
    frameNode->children_.clear();
    for (int32_t i = 0; i < 4; i++) {
        frameNode->children_.emplace_back(node);
    }
    swiperLayoutProperty->propDisplayCount_ = 1;
    swiperLayoutProperty->propSwipeByGroup_ = false;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = -4;
    swiperPattern->targetIndex_ = -3;
    int32_t targetIndex = 1;
    auto result = swiperPattern->ComputeTargetIndex(1, targetIndex);
    EXPECT_EQ(targetIndex, -3);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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
    std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)> onActiveRange =
        [](int32_t start, int32_t end, int32_t vStart, int32_t vEnd, bool isCache, bool forceUpdate) {};
    std::function<void(IndexType, IndexType)> onMoveFromTo = [](int32_t start, int32_t end) {};
    std::function<void()> onPurge = []() {};
    std::function<void()> onUpdateDirty = []() {};
    RefPtr<RepeatVirtualScroll2Node> node = AceType::MakeRefPtr<RepeatVirtualScroll2Node>(
        2, 2, 5, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge, onUpdateDirty);
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

/**
 * @tc.name: FocusMoveOnKey007
 * @tc.desc: Test SwiperPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FocusMoveOnKey007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with displayCount 3, nextMargin 50vp, non-loop mode and 10 items
     * @tc.expected: Swiper is created successfully with 4 visible items
     */
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 3);
    SwiperModelNG::SetNextMargin(AceType::RawPtr(frameNode_), 50.0_vp, true);
    SwiperModelNG::SetLoop(AceType::RawPtr(frameNode_), false);
    CreateSwiperItems(5);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_EQ(pattern_->currentFocusIndex_, 0);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    EXPECT_FALSE(SwiperModelNG::GetLoop(AceType::RawPtr(frameNode_)));
    /**
     * @tc.steps: step2. Press right key multiple times to move focus
     * @tc.expected: currentFocusIndex_ changes from 0 to 3, currentIndex_ remains 0
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 1);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 2);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 3);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    /**
     * @tc.steps: step3. Continue pressing right key
     * @tc.expected: currentFocusIndex_ changes from 3 to 4, currentIndex_ changes from 0 to 1
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 4);
    EXPECT_EQ(pattern_->currentIndex_, 1);
}

/**
 * @tc.name: FocusMoveOnKey008
 * @tc.desc: Test SwiperPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FocusMoveOnKey008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with displayCount 4, swipeByGroup and 10 items.
     */
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 3);
    SwiperModelNG::SetLoop(AceType::RawPtr(frameNode_), false);
    SwiperModelNG::SetPreviousMargin(AceType::RawPtr(frameNode_), 50.0_vp, true);
    CreateSwiperItems(10);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_EQ(pattern_->currentFocusIndex_, 0);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    EXPECT_FALSE(SwiperModelNG::GetLoop(AceType::RawPtr(frameNode_)));
    /**
     * @tc.steps: step2. Make the second child not enabled and press right key.
     * @tc.expected: currentIndex_ is not changed, currentFocusIndex_ change from 0 to 2.
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 1);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 2);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    /**
     * @tc.steps: step3. Continue pressing right key
     * @tc.expected: currentFocusIndex_ is not changed, currentIndex_ change from 0 to 1.
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 3);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
    pattern_->HandleFocusInternal();
    EXPECT_EQ(pattern_->currentFocusIndex_, 3);
    EXPECT_EQ(pattern_->currentIndex_, 1);
}

/**
 * @tc.name: FocusMoveOnKey009
 * @tc.desc: Test SwiperPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FocusMoveOnKey009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with displayCount 3, nextMargin 50vp, non-loop mode and 10 items
     * @tc.expected: Swiper is created successfully
     */
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 3);
    SwiperModelNG::SetNextMargin(AceType::RawPtr(frameNode_), 50.0_vp, true);
    SwiperModelNG::SetLoop(AceType::RawPtr(frameNode_), false);
    CreateSwiperItems(10);
    CreateSwiperDone();
    /**
     * @tc.steps: step2. Change to last page (index 9)
     * @tc.expected: currentFocusIndex_ is 7, currentIndex_ is 7
     */
    ChangeIndex(9);
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_EQ(pattern_->currentFocusIndex_, 7);
    EXPECT_EQ(pattern_->currentIndex_, 7);
    EXPECT_FALSE(SwiperModelNG::GetLoop(AceType::RawPtr(frameNode_)));
    /**
     * @tc.steps: step3. Press left key to move focus backward
     * @tc.expected: currentFocusIndex_ changes from 7 to 6, currentIndex_ remains 7
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 6);
    EXPECT_EQ(pattern_->currentIndex_, 7);
    /**
     * @tc.steps: step4. Press left key again and handle focus
     * @tc.expected: After handling focus, currentFocusIndex_ remains 6, currentIndex_ changes to 6
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN)));
    pattern_->HandleFocusInternal();
    EXPECT_EQ(pattern_->currentFocusIndex_, 6);
    EXPECT_EQ(pattern_->currentIndex_, 6);
}

/**
 * @tc.name: FocusMoveOnKey0010
 * @tc.desc: Test SwiperPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FocusMoveOnKey0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with displayCount 3, previousMargin 50vp, non-loop mode and 10 items
     * @tc.expected: Swiper is created successfully
     */
    SwiperModelNG model = CreateSwiper();
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 3);
    SwiperModelNG::SetLoop(AceType::RawPtr(frameNode_), false);
    // SwiperModelNG::SetNextMargin(AceType::RawPtr(frameNode_), 50.0_vp, true);
    SwiperModelNG::SetPreviousMargin(AceType::RawPtr(frameNode_), 50.0_vp, true);
    CreateSwiperItems(10);
    CreateSwiperDone();
    /**
     * @tc.steps: step2. Change to last page (index 9)
     * @tc.expected: currentFocusIndex_ is 7, currentIndex_ is 7
     */
    ChangeIndex(9);
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);
    EXPECT_EQ(pattern_->currentFocusIndex_, 7);
    EXPECT_EQ(pattern_->currentIndex_, 7);
    EXPECT_FALSE(SwiperModelNG::GetLoop(AceType::RawPtr(frameNode_)));
    /**
     * @tc.steps: step3. Press left key to move focus backward
     * @tc.expected: currentFocusIndex_ changes from 7 to 6, currentIndex_ remains 7
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 6);
    EXPECT_EQ(pattern_->currentIndex_, 7);
    /**
     * @tc.steps: step4. Press left key again to trigger page change
     * @tc.expected: currentFocusIndex_ changes to 5, currentIndex_ changes from 7 to 6
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN)));
    EXPECT_EQ(pattern_->currentFocusIndex_, 5);
    EXPECT_EQ(pattern_->currentIndex_, 6);
}

/**
 * @tc.name: HandleTouchBottomLoop001
 * @tc.desc: Test SwiperPattern HandleTouchBottomLoop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, HandleTouchBottomLoop001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);

    pattern_->currentFirstIndex_ = -1;
    pattern_->currentIndex_ = -2;
    pattern_->targetIndex_ = 0;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = -2;
    pattern_->targetIndex_ = 0;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
}

/**
 * @tc.name: HandleTouchBottomLoopOnRTL001
 * @tc.desc: Test SwiperPattern HandleTouchBottomLoopOnRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, HandleTouchBottomLoopOnRTL001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);

    pattern_->currentFirstIndex_ = -1;
    pattern_->currentIndex_ = -2;
    pattern_->targetIndex_ = 0;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = -2;
    pattern_->targetIndex_ = 0;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
}

/**
 * @tc.name: SwipeToWithoutAnimation001
 * @tc.desc: Test SwipeToWithoutAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwipeToWithoutAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper, jumpIndexByUser_ is nullopt.
     * @tc.expected: jumpIndexByUser_ is nullopt.
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->jumpIndexByUser_, std::nullopt);

    /**
     * @tc.steps: step2. The call to the SwipeToWithoutAnimation interface is triggered but not
                  by the user using the changindex interface.
     * @tc.expected: jumpIndexByUser_ is not changed.
     */
    pattern_->SwipeToWithoutAnimation(1);
    EXPECT_EQ(pattern_->jumpIndexByUser_, std::nullopt);

    /**
     * @tc.steps: step3. The call to the SwipeToWithoutAnimation interface is triggered
                  by the user using the changindex interface.
     * @tc.expected: jumpIndexByUser_ is changed.
     */
    pattern_->SwipeToWithoutAnimation(1, 1);
    EXPECT_EQ(pattern_->jumpIndexByUser_, 1);

    /**
     * @tc.steps: step4. After executing the BeforeCreateLayoutWrapper interface, the jumpindex will be reset.
     * @tc.expected: jumpIndexByUser_ is nullopt.
     */
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern_->jumpIndexByUser_, std::nullopt);
}

/**
 * @tc.name: SetSwiperEventCallback001
 * @tc.desc: Branch: if (swiperPattern->isTouchDown_) { => true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SetSwiperEventCallback001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    /**
     * @tc.steps: step1. Touch down on indicatorNode_
     * @tc.expected: Animation still running
     */
    pattern_->SetSwiperEventCallback(true);
    pattern_->HandleTouchEvent(CreateTouchEventInfo(TouchType::DOWN, Offset(SWIPER_WIDTH / 2, SWIPER_HEIGHT)));
    EXPECT_TRUE(pattern_->isTouchDown_);

    /**
     * @tc.steps: step2. Touch up
     * @tc.expected: Animation still running
     */
    ASSERT_NE(pattern_->swiperController_, nullptr);
    const auto& removeSwiperEventCallback = pattern_->swiperController_->GetRemoveSwiperEventCallback();
    if (removeSwiperEventCallback) {
        EXPECT_TRUE(pattern_->isTouchDown_);
        removeSwiperEventCallback();
        EXPECT_FALSE(pattern_->isTouchDown_);
    }
}

/**
 * @tc.name: OnFontScaleConfigurationUpdate001
 * @tc.desc: Test SwiperPattern OnFontScaleConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, OnFontScaleConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper, mainSizeIsMeasured_ is false after first layout.
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->mainSizeIsMeasured_, true);

    /**
     * @tc.steps: step2. mainSizeIsMeasured_ needs to be changed to false after OnFontScaleConfigurationUpdate called.
     */
    pattern_->OnFontScaleConfigurationUpdate();
    auto pipelineContext = pattern_->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->OnFlushReloadFinish();
    EXPECT_EQ(pattern_->mainSizeIsMeasured_, false);
}

/**
 * @tc.name: UpdateDefaultColor001
 * @tc.desc: Text UpdateDefaultColor
 */
HWTEST_F(SwiperPatternTestNg, UpdateDefaultColor001, TestSize.Level1)
{
    SwiperParameters swiperParameters;
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    model.SetIndicatorType(AceType::RawPtr(frameNode_), SwiperIndicatorType::DOT);

    pattern_->swiperParameters_ = nullptr;
    pattern_->OnColorModeChange(static_cast<uint32_t>(ColorMode::DARK));

    swiperParameters.colorVal = Color::RED;
    swiperParameters.selectedColorVal = Color::RED;
    pattern_->SetSwiperParameters(swiperParameters);
    pattern_->OnColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    EXPECT_NE(pattern_->swiperParameters_->colorVal, Color::RED);
    EXPECT_NE(pattern_->swiperParameters_->selectedColorVal, Color::RED);

    swiperParameters.parametersByUser.insert("colorVal");
    swiperParameters.parametersByUser.insert("selectedColorVal");
    swiperParameters.colorVal = Color::RED;
    swiperParameters.selectedColorVal = Color::RED;
    pattern_->SetSwiperParameters(swiperParameters);
    pattern_->OnColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    EXPECT_EQ(pattern_->swiperParameters_->colorVal.value(), Color::RED);
    EXPECT_EQ(pattern_->swiperParameters_->selectedColorVal.value(), Color::RED);
}

/**
 * @tc.name: AccumulatingTerminateHelper001
 * @tc.desc: Test SwiperPattern AccumulatingTerminateHelper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, AccumulatingTerminateHelper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper.
     */
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. test AccumulatingTerminateHelper, when "IsScrollableAxisInsensitive" is true.
     */
    frameNode->isScrollableAxis_ = true;
    ExpandEdges padding {0, 5, 10, 15};
    RectF rect {};
    auto result = swiperPattern->AccumulatingTerminateHelper(rect, padding);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AccumulatingTerminateHelper002
 * @tc.desc: Test SwiperPattern AccumulatingTerminateHelper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, AccumulatingTerminateHelper002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper.
     */
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. test AccumulatingTerminateHelper, when "IsScrollableAxisInsensitive" is false.
     */
    frameNode->isScrollableAxis_ = false;
    ExpandEdges padding {15, 10, 5, 0};
    RectF rect {};
    auto result = swiperPattern->AccumulatingTerminateHelper(rect, padding);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PropertyPrefMonitor001
 * @tc.desc: Test PropertyPrefMonitor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, PropertyPrefMonitor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper, isAutoPlayAnimationRunning_ is false.
     * @tc.expected: isAutoPlayAnimationRunning_ is false.
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_FALSE(pattern_->isAutoPlayAnimationRunning_);
    /**
     * @tc.steps: step2. check isBeginPerf is true, isInAutoPlay_ is true, hasTabsAncestor_ is true.
     * @tc.expected: isAutoPlayAnimationRunning_ is false.
     */
    pattern_->isInAutoPlay_ = true;
    pattern_->hasTabsAncestor_ = true;
    pattern_->PropertyPrefMonitor(true);
    EXPECT_FALSE(pattern_->isAutoPlayAnimationRunning_);
    /**
     * @tc.steps: step3. check isBeginPerf is true, isInAutoPlay_ is true, hasTabsAncestor_ is false.
     * @tc.expected: isAutoPlayAnimationRunning_ is true.
     */
    pattern_->hasTabsAncestor_ = false;
    pattern_->PropertyPrefMonitor(true);
    EXPECT_TRUE(pattern_->isAutoPlayAnimationRunning_);
    /**
     * @tc.steps: step4. check isBeginPerf is true, isInAutoPlay_ is false, hasTabsAncestor_ is false.
     * @tc.expected: isAutoPlayAnimationRunning_ is false.
     */
    pattern_->hasTabsAncestor_ = false;
    pattern_->isInAutoPlay_ = false;
    pattern_->isAutoPlayAnimationRunning_ = false;
    pattern_->PropertyPrefMonitor(true);
    EXPECT_FALSE(pattern_->isAutoPlayAnimationRunning_);
    /**
     * @tc.steps: step5. check isBeginPerf is false, isAutoPlayAnimationRunning_ is true, hasTabsAncestor_ is true.
     * @tc.expected: isInAutoPlay_ is false.
     */
    pattern_->hasTabsAncestor_ = true;
    pattern_->PropertyPrefMonitor(false);
    EXPECT_FALSE(pattern_->isInAutoPlay_);
    /**
     * @tc.steps: step6. check isBeginPerf is false, isAutoPlayAnimationRunning_ is true, hasTabsAncestor_ is false.
     * @tc.expected: isAutoPlayAnimationRunning_ is false.
     */
    pattern_->hasTabsAncestor_ = false;
    pattern_->isAutoPlayAnimationRunning_ = true;
    pattern_->PropertyPrefMonitor(false);
    EXPECT_FALSE(pattern_->isAutoPlayAnimationRunning_);
    /**
     * @tc.steps: step7. check isBeginPerf is false, isAutoPlayAnimationRunning_ is false, hasTabsAncestor_ is false.
     * @tc.expected: isAutoPlayAnimationRunning_ is false.
     */
    pattern_->isAutoPlayAnimationRunning_ = false;
    pattern_->PropertyPrefMonitor(false);
    EXPECT_FALSE(pattern_->isAutoPlayAnimationRunning_);
}

/**
 * @tc.name: PropertyPrefMonitor002
 * @tc.desc: Test PropertyPrefMonitor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, PropertyPrefMonitor002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_FALSE(pattern_->isAutoPlayAnimationRunning_);

    pattern_->isInAutoPlay_ = true;
    pattern_->PropertyPrefMonitor(false);
    EXPECT_FALSE(pattern_->isInAutoPlay_);
    EXPECT_FALSE(pattern_->isAutoPlayAnimationRunning_);

    pattern_->isInAutoPlay_ = false;
    pattern_->PropertyPrefMonitor(false);
    EXPECT_FALSE(pattern_->isInAutoPlay_);
    EXPECT_FALSE(pattern_->isAutoPlayAnimationRunning_);

    pattern_->isInAutoPlay_ = false;
    pattern_->isAutoPlayAnimationRunning_ =true;
    pattern_->PropertyPrefMonitor(false);
    EXPECT_FALSE(pattern_->isInAutoPlay_);
    EXPECT_FALSE(pattern_->isAutoPlayAnimationRunning_);
 
    pattern_->isInAutoPlay_ = true;
    pattern_->hasTabsAncestor_ = false;
    pattern_->isAutoPlayAnimationRunning_ =false;
    pattern_->PropertyPrefMonitor(true);
    EXPECT_TRUE(pattern_->isInAutoPlay_);
    EXPECT_TRUE(pattern_->isAutoPlayAnimationRunning_);

    pattern_->isInAutoPlay_ = false;
    pattern_->PropertyPrefMonitor(false);
    EXPECT_FALSE(pattern_->isInAutoPlay_);
    EXPECT_FALSE(pattern_->isAutoPlayAnimationRunning_);
}

/**
 * @tc.name: FillType001
 * @tc.desc: Test FillType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FillType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper.
     * @tc.expected: set fillType is 0.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetFillType(0);
    CreateSwiperItems();
    CreateSwiperDone();
    auto layoutProperty = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_EQ(SwiperModelNG::GetFillType(AceType::RawPtr(frameNode_)), 0);
    /**
     * @tc.steps: step2. Create swiper.
     * @tc.expected: check all contentWidth with fillType is 0.
     */
    pattern_->CalculateDisplayCount();
    EXPECT_EQ(SwiperModelNG::GetDisplayCount(AceType::RawPtr(frameNode_)), 1);
    SwiperUtils::CheckBreakPointDisplayCount(layoutProperty, 100);
    EXPECT_EQ(SwiperModelNG::GetDisplayCount(AceType::RawPtr(frameNode_)), 1);
    SwiperUtils::CheckBreakPointDisplayCount(layoutProperty, 700);
    EXPECT_EQ(SwiperModelNG::GetDisplayCount(AceType::RawPtr(frameNode_)), 2);
    SwiperUtils::CheckBreakPointDisplayCount(layoutProperty, 900);
    EXPECT_EQ(SwiperModelNG::GetDisplayCount(AceType::RawPtr(frameNode_)), 3);
    /**
     * @tc.steps: step3. Create swiper.
     * @tc.expected: check all contentWidth with fillType is 2.
     */
    SwiperModelNG::SetFillType(AceType::RawPtr(frameNode_), 2);
    EXPECT_EQ(SwiperModelNG::GetFillType(AceType::RawPtr(frameNode_)), 2);
    pattern_->CalculateDisplayCount();
    EXPECT_EQ(SwiperModelNG::GetDisplayCount(AceType::RawPtr(frameNode_)), 2);
    SwiperUtils::CheckBreakPointDisplayCount(layoutProperty, 100);
    EXPECT_EQ(SwiperModelNG::GetDisplayCount(AceType::RawPtr(frameNode_)), 2);
    SwiperUtils::CheckBreakPointDisplayCount(layoutProperty, 700);
    EXPECT_EQ(SwiperModelNG::GetDisplayCount(AceType::RawPtr(frameNode_)), 3);
    SwiperUtils::CheckBreakPointDisplayCount(layoutProperty, 900);
    EXPECT_EQ(SwiperModelNG::GetDisplayCount(AceType::RawPtr(frameNode_)), 5);
}

/**
 * @tc.name: FillType002
 * @tc.desc: Test FillType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FillType002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper.
     * @tc.expected: check the effect of padding.
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto layoutProperty = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    PaddingProperty padding { CalcLength(10, DimensionUnit::VP), CalcLength(10, DimensionUnit::VP),
        CalcLength(0, DimensionUnit::VP), CalcLength(0, DimensionUnit::VP) };
    layoutProperty->padding_ = std::make_unique<PaddingProperty>(padding);
    // 840 is LG, contenWidth + padding = 820 + 10 + 10.
    EXPECT_EQ(SwiperUtils::GetWidthBreakpoint(layoutProperty, 820), WidthBreakpoint::WIDTH_LG);
}

/**
 * @tc.name: FillType003
 * @tc.desc: Test FillType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FillType003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper.
     * @tc.expected: check the effect of padding.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto layoutProperty = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    PaddingProperty padding { CalcLength(0, DimensionUnit::VP), CalcLength(0, DimensionUnit::VP),
        CalcLength(10, DimensionUnit::VP), CalcLength(10, DimensionUnit::VP) };
    layoutProperty->padding_ = std::make_unique<PaddingProperty>(padding);
    // 840 is LG, contenWidth + padding = 820 + 10 + 10.
    EXPECT_EQ(SwiperUtils::GetWidthBreakpoint(layoutProperty, 820), WidthBreakpoint::WIDTH_LG);
}

/**
 * @tc.name: JSIndicatorControllerBase001
 * @tc.desc: Test FillType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, JSIndicatorControllerBase001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper.
     * @tc.expected: check the indicatorController type.
     */
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    auto controller = AceType::MakeRefPtr<JSIndicatorControllerBase>();
    swiperPattern->SetIndicatorController(controller);
    EXPECT_EQ(AceType::TypeName(swiperPattern->indicatorController_.Upgrade()), "JSIndicatorControllerBase");
}

/**
 * @tc.:name HandleTargetIndex001
 * @tc.desc: test function UpdateAnimationProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, HandleTargetIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Swiper with SetMinSize and reset displayCount to make IsStretch(props) false.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(1);
    CreateSwiperDone();
    /**
     * @tc.steps: step2. Set animation running flags and same targetIndex.
     * @tc.expected: The if condition is not met because IsStretch is false. Animation should be played.
     */
    pattern_->propertyAnimationIsRunning_ = true;
    pattern_->targetIndex_ = 1;
    pattern_->runningTargetIndex_ = 2;
    pattern_->itemPosition_[1] = { .startPos = 100.0f };

    pattern_->HandleTargetIndex(nullptr, nullptr);
    EXPECT_EQ(pattern_->targetIndex_, pattern_->runningTargetIndex_);

    pattern_->propertyAnimationIsRunning_ = false;
    pattern_->targetIndex_ = 1;
    pattern_->runningTargetIndex_ = 2;

    pattern_->HandleTargetIndex(nullptr, nullptr);
    EXPECT_EQ(pattern_->targetIndex_, pattern_->runningTargetIndex_);

    pattern_->propertyAnimationIsRunning_ = true;
    pattern_->targetIndex_ = 1;
    pattern_->runningTargetIndex_ = 1;

    pattern_->HandleTargetIndex(nullptr, nullptr);
    EXPECT_EQ(pattern_->targetIndex_, pattern_->runningTargetIndex_);

    pattern_->propertyAnimationIsRunning_ = false;
    pattern_->targetIndex_ = 1;
    pattern_->runningTargetIndex_ = 1;

    pattern_->HandleTargetIndex(nullptr, nullptr);
    /**
     * @tc.steps: step3. Verify that a new animation is played.
     * @tc.expected: The runningTargetIndex should be updated to the new targetIndex.
     */
    EXPECT_EQ(pattern_->targetIndex_, pattern_->runningTargetIndex_);
}

/**
 * @tc.name: HandleTargetIndex002
 * @tc.desc: test function UpdateAnimationProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, HandleTargetIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Swiper with SetMinSize and reset displayCount to make IsStretch(props) false.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateItemWithSize(200.f, SWIPER_HEIGHT);
    CreateItemWithSize(300.f, SWIPER_HEIGHT);
    CreateItemWithSize(400.f, SWIPER_HEIGHT);
    CreateItemWithSize(500.f, SWIPER_HEIGHT);
    CreateSwiperDone();
    /**
     * @tc.steps: step2. Set animation running flags and same targetIndex.
     * @tc.expected: The if condition is not met because IsStretch is false. Animation should be played.
     */
    pattern_->propertyAnimationIsRunning_ = true;
    pattern_->targetIndex_ = 1;
    pattern_->runningTargetIndex_ = 2;
    pattern_->itemPosition_[1] = { .startPos = 100.0f };

    pattern_->HandleTargetIndex(nullptr, nullptr);
    EXPECT_EQ(pattern_->targetIndex_, pattern_->runningTargetIndex_);

    pattern_->propertyAnimationIsRunning_ = false;
    pattern_->targetIndex_ = 1;
    pattern_->runningTargetIndex_ = 2;

    pattern_->HandleTargetIndex(nullptr, nullptr);
    EXPECT_EQ(pattern_->targetIndex_, pattern_->runningTargetIndex_);

    pattern_->propertyAnimationIsRunning_ = true;
    pattern_->targetIndex_ = 1;
    pattern_->runningTargetIndex_ = 1;

    pattern_->HandleTargetIndex(nullptr, nullptr);
    EXPECT_EQ(pattern_->targetIndex_, pattern_->runningTargetIndex_);

    pattern_->propertyAnimationIsRunning_ = false;
    pattern_->targetIndex_ = 1;
    pattern_->runningTargetIndex_ = 1;

    pattern_->HandleTargetIndex(nullptr, nullptr);
    /**
     * @tc.steps: step3. Verify that a new animation is played.
     * @tc.expected: The runningTargetIndex should be updated to the new targetIndex.
     */
    EXPECT_EQ(pattern_->targetIndex_, pattern_->runningTargetIndex_);
}

/**
 * @tc.name: OnInjectionEvent001
 * @tc.desc: test OnInjectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, OnInjectionEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node.
     */
    CreateSwiper();
    SwiperModelNG::SetLoop(AceType::RawPtr(frameNode_), false);
    CreateSwiperItems(2);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Test OnInjection function.
     * @tc.expected: Set the command json and check the results.
     */
    std::vector<std::string> jsonInvalid = {
        "",                                                            // Empty input
        R"({})",                                                       // Empty JSON
        R"({"c":1})",                                                  // Missing cmd
        R"({"cmd":1})",                                                // Wrong cmd type
        R"({"cmd":"c"})",                                              // Invalid cmd value
        R"({"cmd":"change","p":1})",                                   // Missing params
        R"({"cmd":"change","params":1})",                              // Wrong params type
        R"({"cmd":"change","params":{"t":1}})",                        // Missing type
        R"({"cmd":"change","params":{"type":1}})",                     // Wrong type type
        R"({"cmd":"change","params":{"type":"i"}})",                   // Invalid type value
        R"({"cmd":"change","params":{"type":"index"}})",               // Missing index
        R"({"cmd":"change","params":{"type":"index","i":1}})",         // Missing index field
        R"({"cmd":"change","params":{"type":"index","index":1}})",     // Wrong index type
        R"({"cmd":"change","params":{"type":"index","index":"1.5"}})", // Invalid index format
        R"({"cmd":"change","params":{"type":"index","index":"5"}})",   // Index out of range
        R"({"cmd":"change","params":{"type":"index","index":"-1"}})",  // Negative index
    };
    for (const auto& json : jsonInvalid) {
        int32_t result = pattern_->OnInjectionEvent(json);
        EXPECT_EQ(result, RET_FAILED);
    }

    std::string jsonCommand = R"({"cmd":"change","params":{"type":"backward"}})";
    int32_t result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_FAILED);

    jsonCommand = R"({"cmd":"change","params":{"type":"forward"}})";
    result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_EQ(pattern_->currentIndex_, 1);

    jsonCommand = R"({"cmd":"change","params":{"type":"forward"}})";
    result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_FAILED);

    jsonCommand = R"({"cmd":"change","params":{"type":"backward"}})";
    result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_EQ(pattern_->currentIndex_, 0);

    jsonCommand = R"({"cmd":"change","params":{"type":"index","index":"1"}})";
    result = pattern_->OnInjectionEvent(jsonCommand);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_FALSE(pattern_->fastCurrentIndex_.has_value());
}

/**
 * @tc.name: GetScrollAbility001
 * @tc.desc: test GetScrollAbility
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, GetScrollAbility001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node.
     * @tc.expected: Create Swiper successfully and it is unable to scroll.
     */
    CreateSwiper();
    SwiperModelNG::SetLoop(AceType::RawPtr(frameNode_), true);
    CreateSwiperItems(1);
    EXPECT_EQ(std::string(pattern_->GetScrollAbility()), "unable");

    /**
     * @tc.steps: step2. Add Swiper items and turn next.
     * @tc.expected: Swiper can scroll bidirectionally.
     */
    CreateSwiperItems(3);
    CreateSwiperDone();
    pattern_->ChangeIndex(1, false);
    EXPECT_EQ(std::string(pattern_->GetScrollAbility()), "bidirectional");

    /**
     * @tc.steps: step3. Disable Swiper.
     * @tc.expected: Swiper is unable to scroll.
     */
    layoutProperty_->UpdateDisableSwipe(true);
    EXPECT_EQ(std::string(pattern_->GetScrollAbility()), "unable");
}

/**
 * @tc.name: GetScrollAbility002
 * @tc.desc: test GetScrollAbility
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, GetScrollAbility002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node and set displayCount equal to totalCount.
     * @tc.expected: Swiper is unable to scroll.
     */
    CreateSwiper();
    SwiperModelNG::SetLoop(AceType::RawPtr(frameNode_), true);
    SwiperModelNG::SetDisplayCount(AceType::RawPtr(frameNode_), 3);
    CreateSwiperItems(3);
    CreateSwiperDone();
    EXPECT_EQ(SwiperModelNG::GetDisplayCount(AceType::RawPtr(frameNode_)), 3);
    EXPECT_EQ(std::string(pattern_->GetScrollAbility()), "unable");
}

/**
 * @tc.name: DumpSimplifyInfoOnlyForParamConfig001
 * @tc.desc: test DumpSimplifyInfoOnlyForParamConfig
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, DumpSimplifyInfoOnlyForParamConfig001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init auto-linear Swiper node.
     */
    SwiperModelNG model = CreateSwiper();
    pattern_->contentMainSize_ = 50.0;
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    model.SetLoop(AceType::RawPtr(frameNode_), false);
    CreateItemWithSize(20.f, SWIPER_HEIGHT);
    CreateItemWithSize(30.f, SWIPER_HEIGHT);
    CreateItemWithSize(40.f, SWIPER_HEIGHT);
    CreateItemWithSize(50.f, SWIPER_HEIGHT);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Check scrollable.
     * @tc.expected: Swiper is only forward or only backward.
     */
    auto json = JsonUtil::CreateSharedPtrJson();
    pattern_->DumpSimplifyInfoOnlyForParamConfig(json, { true, true, true });
    EXPECT_EQ(json->GetString("scrollAbility"), "forward");
    EXPECT_EQ(json->GetString("scrollAxis"), "horizontal");
    EXPECT_EQ(json->GetBool("isLoop"), false);
    auto jsonCommand = R"({"cmd":"change","params":{"type":"forward"}})";
    EXPECT_EQ(pattern_->OnInjectionEvent(jsonCommand), RET_SUCCESS);
}
} // namespace OHOS::Ace::NG