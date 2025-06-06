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

#include "foundation/arkui/ace_engine/test/unittest/core/syntax/mock_lazy_for_each_builder.h"
#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_item_drag_manager.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListItemManagerTestNg : public TestNG {
public:
};

/**
 * @tc.name: GetListFrameNode001
 * @tc.desc: Test ListItemDragManager GetListFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, GetListFrameNode001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(node, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    frameNode->parent_ = node;
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    host->parent_ = frameNode;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    auto result = listItemDragManager->GetListFrameNode();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: ScaleAxisNearItem001
 * @tc.desc: Test ListItemDragManager ScaleAxisNearItem
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, ScaleAxisNearItem001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, listPattern);
    ASSERT_NE(node, nullptr);
    node->geometryNode_->frame_.rect_.SetRect(OffsetF(20.0f, 20.0f), SizeF(100.0f, 100.0f));
    frameNode->children_ = { node };
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto builder = AceType::MakeRefPtr<MockLazyForEachBuilder>();
    builder->cachedItems_[0] = LazyForEachChild("item", frameNode);
    lazyForEachNode->builder_ = builder;
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    RectF rect(60.0f, 60.0f, 100.0f, 100.0f);
    OffsetF delta(10.0f, 10.0f);
    auto result = listItemDragManager->ScaleAxisNearItem(0, rect, delta, Axis::HORIZONTAL);
    EXPECT_EQ(result.needMove, false);
}

/**
 * @tc.name: ScaleAxisNearItem002
 * @tc.desc: Test ListItemDragManager ScaleAxisNearItem
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, ScaleAxisNearItem002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, listPattern);
    node->geometryNode_->frame_.rect_.SetRect(OffsetF(20.0f, 20.0f), SizeF(100.0f, 100.0f));
    frameNode->children_ = { node };
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto builder = AceType::MakeRefPtr<MockLazyForEachBuilder>();
    builder->cachedItems_[0] = LazyForEachChild("item", frameNode);
    lazyForEachNode->builder_ = builder;
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    RectF rect(20.0f, 0.0f, 100.0f, 0.0f);
    OffsetF delta(10.0f, 10.0f);
    auto result = listItemDragManager->ScaleAxisNearItem(0, rect, delta, Axis::VERTICAL);
    EXPECT_EQ(result.scale, 1.0f);
}

/**
 * @tc.name: ScaleDiagonalItem001
 * @tc.desc: Test ListItemDragManager ScaleDiagonalItem
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, ScaleDiagonalItem001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, listPattern);
    node->geometryNode_->frame_.rect_.SetRect(OffsetF(20.0f, 20.0f), SizeF(100.0f, 100.0f));
    frameNode->children_ = { node };
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto builder = AceType::MakeRefPtr<MockLazyForEachBuilder>();
    builder->cachedItems_[0] = LazyForEachChild("item", frameNode);
    lazyForEachNode->builder_ = builder;
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    RectF rect(0.0f, 0.0f, 0.0f, 0.0f);
    OffsetF delta(10.0f, 10.0f);
    listItemDragManager->ScaleDiagonalItem(0, rect, delta);
    EXPECT_TRUE(listItemDragManager->scaleNode_.empty());
}

/**
 * @tc.name: ScaleNearItem001
 * @tc.desc: Test ListItemDragManager ScaleNearItem
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, ScaleNearItem001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, listPattern);
    node->geometryNode_->frame_.rect_.SetRect(OffsetF(20.0f, 20.0f), SizeF(100.0f, 100.0f));
    frameNode->children_ = { node };
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto builder = AceType::MakeRefPtr<MockLazyForEachBuilder>();
    builder->cachedItems_[0] = LazyForEachChild("item", frameNode);
    lazyForEachNode->builder_ = builder;
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    listItemDragManager->isStackFromEnd_ = true;
    RectF rect(20.0f, 25.0f, 20.0f, 10.0f);
    OffsetF delta(10.0f, 10.0f);
    auto result = listItemDragManager->ScaleNearItem(0, rect, delta);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: ScaleNearItem002
 * @tc.desc: Test ListItemDragManager ScaleNearItem
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, ScaleNearItem002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, listPattern);
    node->geometryNode_->frame_.rect_.SetRect(OffsetF(20.0f, 20.0f), SizeF(100.0f, 100.0f));
    frameNode->children_ = { node };
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto builder = AceType::MakeRefPtr<MockLazyForEachBuilder>();
    builder->cachedItems_[0] = LazyForEachChild("item", frameNode);
    lazyForEachNode->builder_ = builder;
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    listItemDragManager->isStackFromEnd_ = false;
    RectF rect(20.0f, 25.0f, 20.0f, 10.0f);
    OffsetF delta(-10.0f, -10.0f);
    auto result = listItemDragManager->ScaleNearItem(0, rect, delta);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: HandleAutoScroll001
 * @tc.desc: Test ListItemDragManager HandleAutoScroll
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, HandleAutoScroll001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    host->previewOption_.enableEdgeAutoScroll = false;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    listItemDragManager->listNode_ = host;
    listItemDragManager->scrolling_ = true;
    PointF point(30.0f, 30.0f);
    RectF rect(20.0f, 25.0f, 20.0f, 10.0f);
    listItemDragManager->HandleAutoScroll(0, point, rect);
    EXPECT_FALSE(listItemDragManager->scrolling_);
}

/**
 * @tc.name: HandleScrollCallback001
 * @tc.desc: Test ListItemDragManager HandleScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, HandleScrollCallback001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> groupItemPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    groupItemPattern->itemTotalCount_ = 2;
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(node, nullptr);
    node->geometryNode_ = nullptr;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, groupItemPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    frameNode->parent_ = node;
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    host->geometryNode_->frame_.rect_.SetRect(OffsetF(20.0f, 20.0f), SizeF(100.0f, 100.0f));
    host->children_ = { frameNode, node };
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    listItemDragManager->listNode_ = node;
    listItemDragManager->scrolling_ = true;
    listItemDragManager->HandleScrollCallback();
    EXPECT_FALSE(listItemDragManager->scrolling_);
}

/**
 * @tc.name: HandleOnItemDragUpdate001
 * @tc.desc: Test ListItemDragManager HandleOnItemDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ListItemManagerTestNg, HandleOnItemDragUpdate001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto host = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, listPattern);
    ASSERT_NE(host, nullptr);
    host->geometryNode_->frame_.rect_.SetRect(OffsetF(20.0f, 20.0f), SizeF(100.0f, 100.0f));
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    ASSERT_NE(lazyForEachNode, nullptr);
    auto listItemDragManager = AceType::MakeRefPtr<ListItemDragManager>(host, lazyForEachNode);
    listItemDragManager->axis_ = Axis::HORIZONTAL;
    listItemDragManager->listNode_ = nullptr;
    listItemDragManager->dragOffset_ = OffsetF(10.0f, 10.0f);
    listItemDragManager->realOffset_ = OffsetF(20.0f, 20.0f);
    GestureEvent info;
    info.SetOffsetX(30.0f);
    info.SetOffsetY(20.0f);
    listItemDragManager->HandleOnItemDragUpdate(info);
    EXPECT_EQ(listItemDragManager->realOffset_.GetY(), 10.0f);
}
} // namespace OHOS::Ace::NG