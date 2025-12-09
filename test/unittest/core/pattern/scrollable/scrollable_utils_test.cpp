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
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class DummyNode : public UINode {
    DECLARE_ACE_TYPE(DummyNode, UINode);

public:
    static RefPtr<DummyNode> CreateNode(const std::string& tag, int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<DummyNode>(tag, nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit DummyNode(const std::string& tag, int32_t nodeId) : UINode(tag, nodeId) {}
    ~DummyNode() override = default;
};

class ScrollableUtilsTest : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;

    void FillChildren(int32_t count, Axis axis, SizeF size);
    void ClearChildren();

    RefPtr<FrameNode> CreateScrollable();
    RefPtr<FrameNode> CreateScrollableChild();
    RefPtr<UINode> CreateScrollableChildUINode();
    RefPtr<LazyForEachNode> CreateLazyForEachNode(int32_t childCount = 0);
    RefPtr<RepeatVirtualScroll2Node> CreateRepeatNode(int32_t childCount = 0);

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

RefPtr<FrameNode> ScrollableUtilsTest::CreateScrollable()
{
    return FrameNode::CreateFrameNode("ScrollableContainer", -1, AceType::MakeRefPtr<Pattern>());
}

RefPtr<FrameNode> ScrollableUtilsTest::CreateScrollableChild()
{
    return FrameNode::CreateFrameNode("ScrollableChild", -1, AceType::MakeRefPtr<Pattern>());
}

RefPtr<LazyForEachNode> ScrollableUtilsTest::CreateLazyForEachNode(int32_t childCount)
{
    auto lazyBuilder = AceType::MakeRefPtr<Framework::MockLazyForEachBuilder>();
    for (int32_t i = 0; i < childCount; i++) {
        auto childNode = CreateScrollableChildUINode();
        lazyBuilder->cachedItems_[i] = LazyForEachChild("mock_id", childNode);
    }
    return AceType::MakeRefPtr<LazyForEachNode>(-1, lazyBuilder);
}

RefPtr<UINode> ScrollableUtilsTest::CreateScrollableChildUINode()
{
    return DummyNode::CreateNode("ScrollableChildUINode", -1);
}

RefPtr<RepeatVirtualScroll2Node> ScrollableUtilsTest::CreateRepeatNode(int32_t childCount)
{
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
    node->arrLen_ = childCount;
    node->totalCount_ = childCount;
    return node;
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
    MoveOffsetParam param {
        true,
        1.0f,
        2.0f,
        false
    };
    auto notMove = ScrollableUtils::GetMoveOffset(parentFrameNode, nullptr, param);
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
    MoveOffsetParam param {
        true,
        1.0f,
        2.0f,
        false
    };
    auto notMove = ScrollableUtils::GetMoveOffset(parentFrameNode, curFrameNode, param);
    EXPECT_EQ(notMove, 0.0f);
}

/**
 * @tc.name: IsChildLazy001
 * @tc.desc: Test when scrollable node doesn't have lazy child.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, IsChildLazy001, TestSize.Level1)
{
    auto scrollable = CreateScrollable();
    auto child = CreateScrollableChild();
    int32_t childIndex = 0;
    scrollable->AddChild(child);
    /**
     * @tc.steps: step1. when scrollable node doesn't have lazy child.
     * @tc.expected: return false.
     */
    bool isLazy = ScrollableUtils::IsChildLazy(scrollable, childIndex);
    EXPECT_EQ(isLazy, false);
}

/**
 * @tc.name: IsChildLazy002
 * @tc.desc: Test when scrollable have lazy child. But lazy child is under FrameNode child.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, IsChildLazy002, TestSize.Level1)
{
    auto scrollable = CreateScrollable();
    auto frameChild = CreateScrollableChild();
    auto lazyChild = CreateLazyForEachNode();
    int32_t childIndex = 0;
    frameChild->AddChild(lazyChild);
    scrollable->AddChild(frameChild);
    /**
     * @tc.steps: step1. when scrollable have lazy child. But lazy child is under FrameNode child.
     * @tc.expected: return false.
     */
    bool isLazy = ScrollableUtils::IsChildLazy(scrollable, childIndex);
    EXPECT_EQ(isLazy, false);
}

/**
 * @tc.name: IsChildLazy003
 * @tc.desc: Test when scrollable have lazy child. And lazy child is under UINode.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, IsChildLazy003, TestSize.Level1)
{
    auto scrollable = CreateScrollable();
    auto dummyNode = CreateScrollableChildUINode();
    auto lazyChild = CreateLazyForEachNode(10);
    int32_t childIndex = 0;
    dummyNode->AddChild(lazyChild);
    scrollable->AddChild(dummyNode);
    /**
     * @tc.steps: step1. when scrollable have lazy child. But lazy child is under FrameNode child.
     * @tc.expected: return true.
     */
    bool isLazy = ScrollableUtils::IsChildLazy(scrollable, childIndex);
    EXPECT_EQ(isLazy, true);
}

/**
 * @tc.name: IsChildLazy004
 * @tc.desc: Test when scrollable have lazy child.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, IsChildLazy004, TestSize.Level1)
{
    auto scrollable = CreateScrollable();
    auto lazyChild = CreateLazyForEachNode(10);
    int32_t childIndex = 0;
    scrollable->AddChild(lazyChild);
    /**
     * @tc.steps: step1. when scrollable have lazy child.
     * @tc.expected: return true.
     */
    bool isLazy = ScrollableUtils::IsChildLazy(scrollable, childIndex);
    EXPECT_EQ(isLazy, true);

    childIndex = 5;
    isLazy = ScrollableUtils::IsChildLazy(scrollable, childIndex);
    EXPECT_EQ(isLazy, true);
}

/**
 * @tc.name: IsChildLazy005
 * @tc.desc: Test when scrollable have both repeat and lazy child.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, IsChildLazy005, TestSize.Level1)
{
    auto scrollable = CreateScrollable();
    auto repeatChild = CreateRepeatNode(10);
    auto lazyChild = CreateLazyForEachNode(10);
    int32_t childIndex = 0;
    scrollable->AddChild(repeatChild);
    scrollable->AddChild(lazyChild);
    /**
     * @tc.steps: step1. when scrollable have both repeat and lazy child.
     * @tc.expected: return true.
     */
    bool isLazy = ScrollableUtils::IsChildLazy(scrollable, childIndex);
    EXPECT_EQ(isLazy, true);

    childIndex = 9;
    isLazy = ScrollableUtils::IsChildLazy(scrollable, childIndex);
    EXPECT_EQ(isLazy, true);

    childIndex = 19;
    isLazy = ScrollableUtils::IsChildLazy(scrollable, childIndex);
    EXPECT_EQ(isLazy, true);
}

/**
 * @tc.name: IsChildLazy006
 * @tc.desc: Test when scrollable have repeat child.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableUtilsTest, IsChildLazy006, TestSize.Level1)
{
    auto scrollable = CreateScrollable();
    auto repeatChild = CreateRepeatNode();
    int32_t childIndex = 0;
    scrollable->AddChild(repeatChild);
    /**
     * @tc.steps: step1. when scrollable have repeat child.
     * @tc.expected: return true.
     */
    bool isLazy = ScrollableUtils::IsChildLazy(scrollable, childIndex);
    EXPECT_EQ(isLazy, false);
}
} // namespace OHOS::Ace::NG
