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

#include "test/unittest/core/pattern/test_ng.h"

#define protected public
#define private public
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components_ng/pattern/recycle_view/recycle_dummy_node.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ScrollableUtilsTest : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;

    void FillChildren(int32_t count, Axis axis, SizeF size);
    void ClearChildren();

private:
    RefPtr<FrameNode> scrollable_;
    RefPtr<LazyForEachNode> lazyNode_;
};

void ScrollableUtilsTest::SetUp()
{
    scrollable_ = FrameNode::CreateFrameNode("ScrollableContainer", -1, AceType::MakeRefPtr<Pattern>());
    auto lazyBuilder = AceType::MakeRefPtr<Framework::MockLazyForEachBuilder>();
    lazyNode_ = AceType::MakeRefPtr<LazyForEachNode>(-1, lazyBuilder);
    scrollable_->AddChild(lazyNode_);
};

void ScrollableUtilsTest::TearDown()
{
    scrollable_.Reset();
    lazyNode_.Reset();
};

void ScrollableUtilsTest::FillChildren(int32_t count, Axis axis, SizeF size)
{
    OffsetF step = { 0, 0 };
    if (axis == Axis::HORIZONTAL) {
        step.SetX(size.Width());
        step.SetY(0);
    } else if (axis == Axis::VERTICAL) {
        step.SetX(0);
        step.SetY(size.Height());
    } else {
        return;
    }
    OffsetF offset = { 0, 0 };
    for (int32_t i = 0; i < count; i++) {
        auto node = FrameNode::CreateFrameNode("ScrollableChild", -1, AceType::MakeRefPtr<Pattern>());
        node->geometryNode_->SetFrameSize(size);
        node->geometryNode_->SetFrameOffset(offset);
        auto dummyNode = RecycleDummyNode::WrapRecycleDummyNode(node);
        lazyNode_->builder_->cachedItems_[i] = LazyForEachChild("mock_id", AceType::DynamicCast<UINode>(dummyNode));
        offset += step;
    }
}

void ScrollableUtilsTest::ClearChildren()
{
    lazyNode_->builder_->cachedItems_.clear();
    lazyNode_->builder_->outOfBoundaryNodes_.clear();
}

/**
 * @tc.name: RecycleItemsOutOfBoundary001
 * @tc.desc: Test when pre-recycle won't take place.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, RecycleItemsOutOfBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. when offset equals 0, do nothing
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::HORIZONTAL, 0, 0, 100, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(scrollable_->GetChildren().size(), 1);

    /**
     * @tc.steps: step2. when axis is not horizontal or vertical, do nothing
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::FREE, 10, 0, 100, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(scrollable_->GetChildren().size(), 1);
}

/**
 * @tc.name: RecycleItemsOutOfBoundary002
 * @tc.desc: Test when axis is Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, RecycleItemsOutOfBoundary002, TestSize.Level1)
{
    FillChildren(10, Axis::HORIZONTAL, { 100, 100 });
    scrollable_->geometryNode_->SetFrameSize({ 1000, 100 });
    /**
     * @tc.steps: step1. when axis is horizontal and offset is positive
     * @tc.expected: no child is out of parent.
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::HORIZONTAL, 100, 0, 9, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(lazyNode_->builder_->outOfBoundaryNodes_.size(), 0);

    ClearChildren();
}

/**
 * @tc.name: RecycleItemsOutOfBoundary003
 * @tc.desc: Test when axis is Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, RecycleItemsOutOfBoundary003, TestSize.Level1)
{
    FillChildren(10, Axis::HORIZONTAL, { 100, 100 });
    scrollable_->geometryNode_->SetFrameSize({ 1000, 100 });
    /**
     * @tc.steps: step1. when axis is horizontal and offset is positive
     * @tc.expected: 1 child is out of parent.
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::HORIZONTAL, 101, 0, 9, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(lazyNode_->builder_->outOfBoundaryNodes_.size(), 1);

    ClearChildren();
}

/**
 * @tc.name: RecycleItemsOutOfBoundary004
 * @tc.desc: Test when axis is Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, RecycleItemsOutOfBoundary004, TestSize.Level1)
{
    FillChildren(10, Axis::HORIZONTAL, { 100, 100 });
    scrollable_->geometryNode_->SetFrameSize({ 1000, 100 });
    /**
     * @tc.steps: step1. when axis is horizontal and offset is positive
     * @tc.expected: 2 child is out of parent.
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::HORIZONTAL, 201, 0, 9, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(lazyNode_->builder_->outOfBoundaryNodes_.size(), 2);

    ClearChildren();
}

/**
 * @tc.name: RecycleItemsOutOfBoundary005
 * @tc.desc: Test when axis is Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, RecycleItemsOutOfBoundary005, TestSize.Level1)
{
    FillChildren(10, Axis::HORIZONTAL, { 100, 100 });
    scrollable_->geometryNode_->SetFrameSize({ 1000, 100 });
    /**
     * @tc.steps: step1. when axis is horizontal and offset is negative
     * @tc.expected: 1 child is out of parent.
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::HORIZONTAL, -101, 0, 9, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(lazyNode_->builder_->outOfBoundaryNodes_.size(), 1);

    ClearChildren();
}

/**
 * @tc.name: RecycleItemsOutOfBoundary006
 * @tc.desc: Test when axis is Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, RecycleItemsOutOfBoundary006, TestSize.Level1)
{
    FillChildren(10, Axis::HORIZONTAL, { 100, 100 });
    scrollable_->geometryNode_->SetFrameSize({ 1000, 100 });
    /**
     * @tc.steps: step1. when axis is horizontal and offset is negative
     * @tc.expected: 2 child is out of parent.
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::HORIZONTAL, -201, 0, 9, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(lazyNode_->builder_->outOfBoundaryNodes_.size(), 2);

    ClearChildren();
}

/**
 * @tc.name: RecycleItemsOutOfBoundary007
 * @tc.desc: Test when axis is Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, RecycleItemsOutOfBoundary007, TestSize.Level1)
{
    FillChildren(10, Axis::VERTICAL, { 100, 100 });
    scrollable_->geometryNode_->SetFrameSize({ 100, 1000 });
    /**
     * @tc.steps: step1. when axis is horizontal and offset is positive
     * @tc.expected: no child is out of parent.
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::VERTICAL, 100, 0, 9, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(lazyNode_->builder_->outOfBoundaryNodes_.size(), 0);

    ClearChildren();
}

/**
 * @tc.name: RecycleItemsOutOfBoundary008
 * @tc.desc: Test when axis is Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, RecycleItemsOutOfBoundary008, TestSize.Level1)
{
    FillChildren(10, Axis::VERTICAL, { 100, 100 });
    scrollable_->geometryNode_->SetFrameSize({ 100, 1000 });
    /**
     * @tc.steps: step1. when axis is horizontal and offset is positive
     * @tc.expected: 1 child is out of parent.
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::VERTICAL, 101, 0, 9, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(lazyNode_->builder_->outOfBoundaryNodes_.size(), 1);

    ClearChildren();
}

/**
 * @tc.name: RecycleItemsOutOfBoundary009
 * @tc.desc: Test when axis is Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, RecycleItemsOutOfBoundary009, TestSize.Level1)
{
    FillChildren(10, Axis::VERTICAL, { 100, 100 });
    scrollable_->geometryNode_->SetFrameSize({ 100, 1000 });
    /**
     * @tc.steps: step1. when axis is horizontal and offset is positive
     * @tc.expected: 2 child is out of parent.
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::VERTICAL, 201, 0, 9, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(lazyNode_->builder_->outOfBoundaryNodes_.size(), 2);

    ClearChildren();
}

/**
 * @tc.name: RecycleItemsOutOfBoundary010
 * @tc.desc: Test when axis is Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, RecycleItemsOutOfBoundary010, TestSize.Level1)
{
    FillChildren(10, Axis::VERTICAL, { 100, 100 });
    scrollable_->geometryNode_->SetFrameSize({ 100, 1000 });
    /**
     * @tc.steps: step1. when axis is horizontal and offset is negative
     * @tc.expected: 1 child is out of parent.
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::VERTICAL, -101, 0, 9, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(lazyNode_->builder_->outOfBoundaryNodes_.size(), 1);

    ClearChildren();
}

/**
 * @tc.name: RecycleItemsOutOfBoundary011
 * @tc.desc: Test when axis is Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, RecycleItemsOutOfBoundary011, TestSize.Level1)
{
    FillChildren(10, Axis::VERTICAL, { 100, 100 });
    scrollable_->geometryNode_->SetFrameSize({ 100, 1000 });
    /**
     * @tc.steps: step1. when axis is horizontal and offset is negative
     * @tc.expected: 2 child is out of parent.
     */
    ScrollableUtils::RecycleItemsOutOfBoundary(Axis::VERTICAL, -201, 0, 9, Referenced::RawPtr(scrollable_));
    ASSERT_EQ(lazyNode_->builder_->outOfBoundaryNodes_.size(), 2);

    ClearChildren();
}

/**
 * @tc.name: GetMoveOffset001
 * @tc.desc: Test when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, GetMoveOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. when frameNode is nullptr
     * @tc.expected: return 0.0f;
     */
    auto parentFrameNode = FrameNode::CreateFrameNode("ScrollableContainer", -1, AceType::MakeRefPtr<Pattern>());
    auto notMove = ScrollableUtils::GetMoveOffset(parentFrameNode, nullptr, true, 1.0f, 2.0f);
    EXPECT_EQ(notMove, 0.0f);
}

/**
 * @tc.name: GetMoveOffset002
 * @tc.desc: Test when frameNode with default data
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, GetMoveOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. when frameNode with default data
     * @tc.expected: return 0.0f;
     */
    auto parentFrameNode = FrameNode::CreateFrameNode("ScrollableContainer", -1, AceType::MakeRefPtr<Pattern>());
    parentFrameNode->geometryNode_->SetFrameSize({ 1000, 100 });
    auto curFrameNode = FrameNode::CreateFrameNode("ScrollableContainer", -1, AceType::MakeRefPtr<Pattern>());
    curFrameNode->geometryNode_->SetFrameSize({ 1000, 100 });
    auto notMove = ScrollableUtils::GetMoveOffset(parentFrameNode, curFrameNode, true, 1.0f, 2.0f);
    EXPECT_EQ(notMove, 0.0f);
}
} // namespace OHOS::Ace::NG
