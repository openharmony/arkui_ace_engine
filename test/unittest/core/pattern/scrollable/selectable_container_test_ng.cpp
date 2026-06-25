/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/components_ng/pattern/mock_nestable_scroll_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"


#include "core/animation/select_motion.h"
#include "core/components_ng/pattern/scrollable/selectable_container_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SelectableContainerTestNg : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    void InitNestedScrolls();
    RefPtr<FrameNode> selectScroll_;
    RefPtr<FrameNode> mockScroll_;
};

void SelectableContainerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void SelectableContainerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SelectableContainerTestNg::SetUp()
{
    InitNestedScrolls();
    MockPipelineContext::SetUp();
}

void SelectableContainerTestNg::TearDown()
{
    selectScroll_.Reset();
    mockScroll_.Reset();
    MockPipelineContext::TearDown();
}

void SelectableContainerTestNg::InitNestedScrolls()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    selectScroll_ = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, nodeId, AceType::MakeRefPtr<PartiallyMockedSelectableContainer>());
    stack->Push(selectScroll_);
    mockScroll_ = FrameNode::CreateFrameNode("mockScroll", -1, AceType::MakeRefPtr<MockNestableScrollContainer>());
    selectScroll_->MountToParent(mockScroll_);
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    scrollPn->AddScrollEvent();
    scrollPn->SetEdgeEffect();
}

/**
 * @tc.name: SelectWithScroll001
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SelectWithScroll001, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(false));
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->GetOutOfScrollableOffset(), 0.0f);
}

/**
 * @tc.name: SelectWithScroll002
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SelectWithScroll002, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1);
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);
}

/**
 * @tc.name: SelectWithScroll003
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SelectWithScroll003, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), 0.0f);
}

/**
 * @tc.name: SelectWithScroll004
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SelectWithScroll004, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*scrollPn, IsAtTop).Times(1);
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->isAnimationStop_ = false;
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);
}

/**
 * @tc.name: SelectWithScroll005
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SelectWithScroll005, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*scrollPn, IsAtTop).Times(1);
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->isAnimationStop_ = true;
    scrollPn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);
}

/**
 * @tc.name: LimitMouseEndOffset001
 * @tc.desc: Test nested LimitMouseEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, LimitMouseEndOffset001, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    scrollPn->parent_ = mockPn;

    scrollPn->SetAxis(Axis::HORIZONTAL);
    scrollPn->mouseEndOffset_ = OffsetF(-1.0f, -1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);

    scrollPn->SetAxis(Axis::VERTICAL);
    scrollPn->mouseEndOffset_ = OffsetF(1.0f, 1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);
}

/**
 * @tc.name: MarkSelectedItems001
 * @tc.desc: Test nested MarkSelectedItems
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, MarkSelectedItems001, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    scrollPn->parent_ = mockPn;

    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->multiSelectable_ = true;
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->mousePressed_ = true;
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->mouseStartOffset_ = OffsetF(0.0f, 0.0f);
    scrollPn->mouseEndOffset_ = OffsetF(1.0f, 1.0f);
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
}

/**
 * @tc.name: ShouldSelectScrollBeStopped001
 * @tc.desc: Test nested ShouldSelectScrollBeStopped
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, ShouldSelectScrollBeStopped001, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    scrollPn->parent_ = mockPn;

    scrollPn->mousePressed_ = true;
    scrollPn->SetAxis(Axis::HORIZONTAL);
    Offset localLocation;
    localLocation.SetX(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetX(), -1.1f);
    auto result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    scrollPn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetY(0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), 0.0f);
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ShouldSelectScrollBeStopped002
 * @tc.desc: Test nested ShouldSelectScrollBeStopped
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, ShouldSelectScrollBeStopped002, TestSize.Level1)
{
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollPn->parent_ = mockPn;
    auto result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ShouldSelectScrollBeStopped003
 * @tc.desc: Test nested ShouldSelectScrollBeStopped
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, ShouldSelectScrollBeStopped003, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    scrollPn->parent_ = mockPn;

    scrollPn->mousePressed_ = true;
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetY(1.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), 1.0f);
    auto result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetOffsetWithLimit001
 * @tc.desc: Test nested GetOffsetWithLimit
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, GetOffsetWithLimit001, TestSize.Level1)
{
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollPn->parent_ = mockPn;

    float offset = 0.2f;
    auto result = scrollPn->GetOffsetWithLimit(offset);
    EXPECT_NE(result, offset);
}

/**
 * @tc.name: GetOffsetWithLimit002
 * @tc.desc: Test nested GetOffsetWithLimit
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, GetOffsetWithLimit002, TestSize.Level1)
{
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollPn->parent_ = mockPn;

    float offset = -0.1f;
    auto result = scrollPn->GetOffsetWithLimit(offset);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: GetOffsetWithLimit003
 * @tc.desc: Test nested GetOffsetWithLimit
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, GetOffsetWithLimit003, TestSize.Level1)
{
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollPn->parent_ = mockPn;

    float offset = 0.0f;
    auto result = scrollPn->GetOffsetWithLimit(offset);
    EXPECT_EQ(result, offset);
}

/**
 * @tc.name: InitMouseEvent001
 * @tc.desc: Test multiSelectable event and mouse scroll event
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, InitMouseEvent001, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    ASSERT_NE(selectScroll_, nullptr);
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    ASSERT_NE(scrollPn, nullptr);
    scrollPn->parent_ = mockPn;
    auto gestureHub = selectScroll_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_EQ(gestureHub->panEventActuator_, nullptr);

    scrollPn->InitMouseEvent();
    gestureHub = selectScroll_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    ASSERT_NE(gestureHub->panEventActuator_, nullptr);
    EXPECT_TRUE(gestureHub->panEventActuator_->isExcludedAxis_);
}

/**
 * @tc.name: SelectWithScrollFling001
 * @tc.desc: Test SelectWithScroll with fling context (extracted from Fling003)
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SelectWithScrollFling001, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(false));
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->GetOutOfScrollableOffset(), 0.0f);

    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1);
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);

    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetX(-1.0f);
    localLocation.SetY(0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), 0.0f);

    EXPECT_CALL(*scrollPn, IsAtTop).Times(AtLeast(1));
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->isAnimationStop_ = false;
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);
}

/**
 * @tc.name: SelectWithScrollFling002
 * @tc.desc: Test SelectWithScroll in fling context (extracted from Fling004)
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SelectWithScrollFling002, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->isAnimationStop_ = true;
    scrollPn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);
}

/**
 * @tc.name: LimitMouseEndOffsetFling001
 * @tc.desc: Test LimitMouseEndOffset in fling context (extracted from Fling004)
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, LimitMouseEndOffsetFling001, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    scrollPn->SetAxis(Axis::HORIZONTAL);
    scrollPn->mouseEndOffset_ = OffsetF(-1.0f, -1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);

    scrollPn->SetAxis(Axis::VERTICAL);
    scrollPn->mouseEndOffset_ = OffsetF(1.0f, 1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);
}

/**
 * @tc.name: MarkSelectedItemsFling001
 * @tc.desc: Test MarkSelectedItems and ShouldSelectScrollBeStopped (extracted from Fling006)
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, MarkSelectedItemsFling001, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->multiSelectable_ = true;
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->mousePressed_ = true;
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->mouseStartOffset_ = OffsetF(0.0f, 0.0f);
    scrollPn->mouseEndOffset_ = OffsetF(1.0f, 1.0f);
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());

    scrollPn->GetHost();
    scrollPn->parent_ = mockPn;
    scrollPn->mousePressed_ = true;
    scrollPn->SetAxis(Axis::HORIZONTAL);
    Offset localLocation;
    localLocation.SetX(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetX(), -1.1f);
    auto result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    scrollPn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetY(0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), 0.0f);
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SelectWithScrollFling003
 * @tc.desc: Test SelectWithScroll (extracted from Fling014)
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SelectWithScrollFling003, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(false));
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->GetOutOfScrollableOffset(), 0.0f);

    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1);
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);

    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetX(-1.0f);
    localLocation.SetY(0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), 0.0f);

    EXPECT_CALL(*scrollPn, IsAtTop).Times(AtLeast(1));
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->isAnimationStop_ = false;
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);
}

/**
 * @tc.name: SelectWithScrollFling004
 * @tc.desc: Test SelectWithScroll and LimitMouseEndOffset (extracted from Fling015)
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SelectWithScrollFling004, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->isAnimationStop_ = true;
    scrollPn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);

    scrollPn->SetAxis(Axis::HORIZONTAL);
    scrollPn->mouseEndOffset_ = OffsetF(-1.0f, -1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);

    scrollPn->SetAxis(Axis::VERTICAL);
    scrollPn->mouseEndOffset_ = OffsetF(1.0f, 1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);
}

/**
 * @tc.name: MarkSelectedItemsFling002
 * @tc.desc: Test MarkSelectedItems and ShouldSelectScrollBeStopped (extracted from Fling017)
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, MarkSelectedItemsFling002, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = selectScroll_->GetPattern<PartiallyMockedSelectableContainer>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->multiSelectable_ = true;
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->mousePressed_ = true;
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->mouseStartOffset_ = OffsetF(0.0f, 0.0f);
    scrollPn->mouseEndOffset_ = OffsetF(1.0f, 1.0f);
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());

    scrollPn->GetHost();
    scrollPn->parent_ = mockPn;
    scrollPn->mousePressed_ = true;
    scrollPn->SetAxis(Axis::HORIZONTAL);
    Offset localLocation;
    localLocation.SetX(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetX(), -1.1f);
    auto result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    scrollPn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetY(0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), 0.0f);
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: BoxSelectTest001
 * @tc.desc: Test SelectableContainerPattern::HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, BoxSelectTest001, TestSize.Level1)
{
    auto selectablePattern = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    auto selectableNodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto selectableNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, selectableNodeId, selectablePattern);
    GestureEvent info;
    info.SetRawGlobalLocation(Offset(50, 50));
    info.SetOffsetX(5);
    info.SetOffsetY(10);
    selectablePattern->HandleDragStart(info);
    EXPECT_EQ(selectablePattern->mouseStartOffset_, OffsetF(45, 40));
}

/**
 * @tc.name: TryEnterEditModeForSwipeSelect001
 * @tc.desc: Test TryEnterEditModeForSwipeSelect returns early when edit mode already enabled
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, TryEnterEditModeForSwipeSelect001, TestSize.Level1)
{
    auto selectablePattern = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    auto selectableNodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto selectableNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, selectableNodeId, selectablePattern);

    selectablePattern->SetEnableEditMode(true);
    selectablePattern->ResetEditModeChanged();

    bool eventFired = false;
    selectablePattern->SetEnableEditModeChangeEvent([&eventFired](bool) { eventFired = true; });

    selectablePattern->TryEnterEditModeForSwipeSelect();

    EXPECT_TRUE(selectablePattern->GetEnableEditMode());
    EXPECT_FALSE(selectablePattern->IsEditModeChanged());
    EXPECT_FALSE(eventFired);
}

/**
 * @tc.name: TryEnterEditModeForSwipeSelect002
 * @tc.desc: Test TryEnterEditModeForSwipeSelect sets editModeChanged when default multi-select style disabled
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, TryEnterEditModeForSwipeSelect002, TestSize.Level1)
{
    auto selectablePattern = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    auto selectableNodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto selectableNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, selectableNodeId, selectablePattern);

    EditModeOptions options;
    options.useDefaultMultiSelectStyle = false;
    selectablePattern->SetEditModeOptions(options);

    bool eventFired = false;
    bool eventValue = false;
    selectablePattern->SetEnableEditModeChangeEvent([&eventFired, &eventValue](bool enable) {
        eventFired = true;
        eventValue = enable;
    });

    EXPECT_CALL(*selectablePattern, ApplyEditModeToVisibleItems).Times(0);

    selectablePattern->TryEnterEditModeForSwipeSelect();

    EXPECT_TRUE(selectablePattern->GetEnableEditMode());
    EXPECT_TRUE(selectablePattern->IsEditModeChanged());
    EXPECT_TRUE(eventFired);
    EXPECT_TRUE(eventValue);
}

/**
 * @tc.name: TryEnterEditModeForSwipeSelect003
 * @tc.desc: Test TryEnterEditModeForSwipeSelect calls ApplyEditModeToVisibleItems when default style enabled
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, TryEnterEditModeForSwipeSelect003, TestSize.Level1)
{
    auto selectablePattern = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    auto selectableNodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto selectableNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, selectableNodeId, selectablePattern);

    EditModeOptions options;
    options.useDefaultMultiSelectStyle = true;
    selectablePattern->SetEditModeOptions(options);

    bool eventFired = false;
    bool eventValue = false;
    selectablePattern->SetEnableEditModeChangeEvent([&eventFired, &eventValue](bool enable) {
        eventFired = true;
        eventValue = enable;
    });

    EXPECT_CALL(*selectablePattern, ApplyEditModeToVisibleItems).Times(1);

    selectablePattern->TryEnterEditModeForSwipeSelect();

    EXPECT_TRUE(selectablePattern->GetEnableEditMode());
    EXPECT_TRUE(selectablePattern->IsEditModeChanged());
    EXPECT_TRUE(eventFired);
    EXPECT_TRUE(eventValue);
}
/**
 * @tc.name: SetEditModeOptionsUseDefaultMultiSelectStyleChanged001
 * @tc.desc: Test SetEditModeOptions sets editModeChanged when useDefaultMultiSelectStyle changes from true to false
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SetEditModeOptionsUseDefaultMultiSelectStyleChanged001, TestSize.Level1)
{
    auto selectablePattern = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    auto selectableNodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto selectableNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, selectableNodeId, selectablePattern);

    EditModeOptions initialOptions;
    initialOptions.useDefaultMultiSelectStyle = true;
    selectablePattern->SetEditModeOptions(initialOptions);
    selectablePattern->ResetEditModeChanged();
    EXPECT_FALSE(selectablePattern->IsEditModeChanged());

    EditModeOptions newOptions;
    newOptions.useDefaultMultiSelectStyle = false;
    selectablePattern->SetEditModeOptions(newOptions);

    EXPECT_TRUE(selectablePattern->IsEditModeChanged());
}

/**
 * @tc.name: SetEditModeOptionsUseDefaultMultiSelectStyleChanged002
 * @tc.desc: Test SetEditModeOptions sets editModeChanged when useDefaultMultiSelectStyle changes from false to true
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SetEditModeOptionsUseDefaultMultiSelectStyleChanged002, TestSize.Level1)
{
    auto selectablePattern = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    auto selectableNodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto selectableNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, selectableNodeId, selectablePattern);

    EditModeOptions initialOptions;
    initialOptions.useDefaultMultiSelectStyle = false;
    selectablePattern->SetEditModeOptions(initialOptions);
    selectablePattern->ResetEditModeChanged();
    EXPECT_FALSE(selectablePattern->IsEditModeChanged());

    EditModeOptions newOptions;
    newOptions.useDefaultMultiSelectStyle = true;
    selectablePattern->SetEditModeOptions(newOptions);

    EXPECT_TRUE(selectablePattern->IsEditModeChanged());
}

/**
 * @tc.name: SetEditModeOptionsUseDefaultMultiSelectStyleChanged003
 * @tc.desc: Test SetEditModeOptions does not set editModeChanged when useDefaultMultiSelectStyle unchanged
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SetEditModeOptionsUseDefaultMultiSelectStyleChanged003, TestSize.Level1)
{
    auto selectablePattern = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    auto selectableNodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto selectableNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, selectableNodeId, selectablePattern);

    EditModeOptions initialOptions;
    initialOptions.useDefaultMultiSelectStyle = true;
    selectablePattern->SetEditModeOptions(initialOptions);
    selectablePattern->ResetEditModeChanged();
    EXPECT_FALSE(selectablePattern->IsEditModeChanged());

    EditModeOptions sameOptions;
    sameOptions.useDefaultMultiSelectStyle = true;
    selectablePattern->SetEditModeOptions(sameOptions);

    EXPECT_FALSE(selectablePattern->IsEditModeChanged());
}

/**
 * @tc.name: SetEditModeOptionsUseDefaultMultiSelectStyleChanged004
 * @tc.desc: Test changing useDefaultMultiSelectStyle while editMode enabled triggers IsDefaultMultiSelectStyleEnabled
 * @tc.type: FUNC
 */
HWTEST_F(SelectableContainerTestNg, SetEditModeOptionsUseDefaultMultiSelectStyleChanged004, TestSize.Level1)
{
    auto selectablePattern = AceType::MakeRefPtr<FullyMockedSelectableContainer>();
    auto selectableNodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto selectableNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, selectableNodeId, selectablePattern);

    selectablePattern->SetEnableEditMode(true);
    selectablePattern->ResetEditModeChanged();

    EditModeOptions initialOptions;
    initialOptions.useDefaultMultiSelectStyle = false;
    selectablePattern->SetEditModeOptions(initialOptions);
    EXPECT_FALSE(selectablePattern->IsDefaultMultiSelectStyleEnabled());

    EditModeOptions newOptions;
    newOptions.useDefaultMultiSelectStyle = true;
    selectablePattern->SetEditModeOptions(newOptions);

    EXPECT_TRUE(selectablePattern->IsEditModeChanged());
    EXPECT_TRUE(selectablePattern->IsDefaultMultiSelectStyleEnabled());

    selectablePattern->ResetEditModeChanged();
    EXPECT_FALSE(selectablePattern->IsEditModeChanged());
}

} // namespace OHOS::Ace::NG
