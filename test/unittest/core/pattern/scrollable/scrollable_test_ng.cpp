/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "gmock/gmock-actions.h"
#include "gtest/gtest.h"
#include "gtest/hwext/gtest-ext.h"

#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ScrollableTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite();
    static void TearDownTestSuite();

private:
    void InitNestedScrolls();

    RefPtr<FrameNode> scroll_;
    RefPtr<FrameNode> mockScroll_;
};

// implement interfaces with mock
class PartiallyMockedScrollable : public ScrollablePattern {
    DECLARE_ACE_TYPE(PartiallyMockedScrollable, ScrollablePattern);

public:
    MOCK_METHOD(bool, UpdateCurrentOffset, (float delta, int32_t source), (override));
    MOCK_METHOD(bool, IsAtTop, (), (const, override));
    MOCK_METHOD(bool, IsAtBottom, (), (const, override));
    MOCK_METHOD(void, UpdateScrollBarOffset, (), (override));
    MOCK_METHOD(bool, IsScrollable, (), (const, override));
    MOCK_METHOD(OverScrollOffset, GetOverScrollOffset, (double delta), (const, override));
};

class FullyMockedScrollable : public PartiallyMockedScrollable {
    DECLARE_ACE_TYPE(FullyMockedScrollable, PartiallyMockedScrollable);

public:
    MOCK_METHOD(bool, HandleScrollVelocity, (float), (override));
};

void ScrollableTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void ScrollableTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void ScrollableTestNg::SetUp()
{
    InitNestedScrolls();
}

void ScrollableTestNg::TearDown()
{
    scroll_.Reset();
    mockScroll_.Reset();
}

void ScrollableTestNg::InitNestedScrolls()
{
    scroll_ = FrameNode::CreateFrameNode("scroll", -1, AceType::MakeRefPtr<PartiallyMockedScrollable>());
    mockScroll_ = FrameNode::CreateFrameNode("mockScroll", -1, AceType::MakeRefPtr<MockNestableScrollContainer>());
    scroll_->MountToParent(mockScroll_);

    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    // to enable need parent
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };
    EXPECT_CALL(*(mockScroll_->GetPattern<MockNestableScrollContainer>()), GetAxis).Times(1);
    scrollPn->SetParentScrollable();
}

/**
 * @tc.name: HandleSelf001
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleSelf001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll).Times(0);
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(3).WillRepeatedly(Return(true));

    // test self only
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_ONLY, .backward = NestedScrollMode::SELF_ONLY };
    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;

    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 5.0f);

    result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 5);

    result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 0);
}

/**
 * @tc.name: HandleParallel001
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleParallel001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillOnce(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = false,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(2).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollPn->edgeEffect_ = EdgeEffect::NONE;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 5.0f);

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleParallel002
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleParallel002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(2)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = true,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollPn->edgeEffect_ = EdgeEffect::NONE;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleParallel003
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleParallel003, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = true,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollPn->edgeEffect_ = EdgeEffect::NONE;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 5.0f);
}

/**
 * @tc.name: HandleParallel004
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleParallel004, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = true,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleParallel005
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleParallel005, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = false,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_FALSE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleSelfFirst001
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleSelfFirst001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 0.0f,
            .reachEdge = false,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL);
    EXPECT_FALSE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleSelfFirst002
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleSelfFirst002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = false,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollPn->edgeEffect_ = EdgeEffect::NONE;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL);
    EXPECT_FALSE(result.reachEdge);
    EXPECT_EQ(result.remain, 5.0f);
}

/**
 * @tc.name: HandleSelfFirst003
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleSelfFirst003, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = false,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleSelfFirst004
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleSelfFirst004, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll).Times(0);
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 0, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_FALSE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleSelfFirst005
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleSelfFirst005, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 0.0f,
            .reachEdge = false,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_FALSE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleSelfFirst006
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleSelfFirst006, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = false,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_FALSE(result.reachEdge);
    EXPECT_EQ(result.remain, 5.0f);
}

/**
 * @tc.name: HandleSelfFirst007
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleSelfFirst007, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(2)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = true,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleScrollParent001
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollParent001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = true,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollPn->edgeEffect_ = EdgeEffect::NONE;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 5.0f);
}

/**
 * @tc.name: HandleScrollParent002
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollParent002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll).Times(0);
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleScrollParent003
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollParent003, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 0.0f,
            .reachEdge = true,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollPn->edgeEffect_ = EdgeEffect::NONE;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_FALSE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleScrollParent004
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollParent004, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = true,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 0, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollPn->edgeEffect_ = EdgeEffect::NONE;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_FALSE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleScrollParent005
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollParent005, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = true,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollPn->edgeEffect_ = EdgeEffect::NONE;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 5.0f);
}

/**
 * @tc.name: HandleScrollParent006
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollParent006, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(2)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = true,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollPn->edgeEffect_ = EdgeEffect::NONE;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleScrollParent007
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollParent007, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll)
        .Times(1)
        .WillRepeatedly(Return(ScrollResult {
            .remain = 5.0f,
            .reachEdge = false,
        }));
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 0, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_FALSE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleScroll002
 * @tc.desc: Test nested HandleScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScroll002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScroll).Times(0);
    EXPECT_CALL(*scrollPn, GetOverScrollOffset)
        .WillRepeatedly(Return(OverScrollOffset { .start = 0, .end = 5 }));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    auto result = scrollPn->HandleScroll(0, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_FALSE(result.reachEdge);
    EXPECT_EQ(result.remain, 0.0f);
}

/**
 * @tc.name: HandleScrollVelocity001
 * @tc.desc: Test nested HandleScroll onScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity001, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(0);
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(true));

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_ONLY, .backward = NestedScrollMode::SELF_ONLY };

    bool res = scrollPn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollPn->edgeEffect_ = EdgeEffect::NONE;
    res = scrollPn->HandleScrollVelocity(5);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: HandleScrollVelocity002
 * @tc.desc: Test nested HandleScroll onScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity002, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(true));
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };
    bool res = scrollPn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(1).WillOnce(Return(false));
    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    res = scrollPn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: HandleScrollVelocity003
 * @tc.desc: Test nested HandleScroll onScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity003, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(2).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(true));
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };
    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);
    scrollPn->edgeEffect_ = EdgeEffect::FADE;
    bool res = scrollPn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: HandleScrollVelocity004
 * @tc.desc: Test nested HandleScroll onScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity004, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(0);
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(true));
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };
    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    bool res = scrollPn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: HandleScrollVelocity005
 * @tc.desc: Test nested HandleScroll with different scroll mode forward/backward
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity005, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(0);
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(true));

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->edgeEffect_ = EdgeEffect::SPRING;
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::SELF_ONLY };

    bool res = scrollPn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollPn->edgeEffect_ = EdgeEffect::NONE;
    res = scrollPn->HandleScrollVelocity(5);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: HandleScrollVelocity006
 * @tc.desc: Test HandleScrollVelocity without scrollableEvent, shouldn't crash
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity006, TestSize.Level1)
{
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(0);
    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(false));

    bool res = scrollPn->HandleScrollVelocity(5);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: OnScrollStart001
 * @tc.desc: Test nested HandleScroll onScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, OnScrollStart001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*scrollPn, IsAtTop).Times(AtLeast(1));
    EXPECT_CALL(*mockPn, GetAxis).Times(1);

    EXPECT_CALL(*mockPn, OnScrollStartRecursive).Times(1);
    scrollPn->OnScrollStartRecursive(5.0f);
}

/**
 * @tc.name: OnScrollEnd001
 * @tc.desc: Test nested HandleScroll onScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, OnScrollEnd001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, OnScrollEndRecursive).Times(1);
    scrollPn->OnScrollEndRecursive(std::nullopt);
}

HWTEST_F(ScrollableTestNg, IsInHotZone001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto pipeLine = PipelineBase::GetCurrentContext();
    auto frameNode = scrollPn->GetHost();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(700.0, 1200.0));
    frameNode->SetGeometryNode(geometryNode);

    scrollPn->SetAxis(Axis::VERTICAL);
    EXPECT_TRUE(scrollPn->IsInHotZone(PointF(80.0, 250.0)) == 0.0f);
    EXPECT_TRUE(Positive(scrollPn->IsInHotZone(PointF(0.0, 0.0))));
    EXPECT_TRUE(Negative(scrollPn->IsInHotZone(PointF(0.0, 1200.0))));

    scrollPn->SetAxis(Axis::HORIZONTAL);
    EXPECT_TRUE(Positive(scrollPn->IsInHotZone(PointF(0.0, 0.0))));
    EXPECT_TRUE(Negative(scrollPn->IsInHotZone(PointF(700.0, 0.0))));
}

HWTEST_F(ScrollableTestNg, IsVertical, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->SetAxis(Axis::HORIZONTAL);
    EXPECT_FALSE(scrollPn->isVertical());
    scrollPn->SetAxis(Axis::VERTICAL);
    EXPECT_TRUE(scrollPn->isVertical());
}

HWTEST_F(ScrollableTestNg, HandleMoveEventInComp, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    auto pt = PointF(0.0, 0.0);
    scrollPn->HandleMoveEventInComp(pt);
    EXPECT_TRUE(scrollPn->velocityMotion_);
    EXPECT_TRUE(scrollPn->animator_);
    pt = PointF(80.0, 250.0);
    scrollPn->HandleMoveEventInComp(pt);
    EXPECT_TRUE(scrollPn->animator_->IsStopped());
}

HWTEST_F(ScrollableTestNg, HotZoneScroll, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    float offsetPct = 0.5f;
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->HotZoneScroll(offsetPct);
    EXPECT_TRUE(scrollPn->animator_);
    EXPECT_TRUE(scrollPn->velocityMotion_);
    EXPECT_TRUE(NearEqual(scrollPn->lastHonezoneOffsetPct_, offsetPct));
}

/**
 * @tc.name: SetCanOverScroll001
 * @tc.desc: Test nested SetCanOverScroll failure status
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SetCanOverScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Set the parameter scrollable to be nullptr
     * @tc.expected: Scrollable is nullptr
     */
    RefPtr<Scrollable> scrollable = nullptr;
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    scrollPn->SetCanOverScroll(false);
    EXPECT_EQ(scrollPn->scrollableEvent_->GetScrollable(), nullptr);
}

/**
 * @tc.name: HandleScrollVelocity007
 * @tc.desc: Test nested HandleScrollVelocity for IsAtBottom
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Set the parameter scrollable is true and IsAtBottom is false
     * @tc.expected: Scrollable is not nullptr
     */
    EXPECT_CALL(*scrollPn, IsAtBottom).WillRepeatedly(Return(false));
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    EXPECT_NE(scrollPn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step3. Call the HandleScrollVelocity method
     * @tc.expected: The result is true
     */
    bool res = scrollPn->HandleScrollVelocity(-1.1f);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: GetCanOverScroll001
 * @tc.desc: Test nested GetCanOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetCanOverScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the GetCanOverScroll method, Set the parameter scrollable is false
     * @tc.expected: The result is true
     */
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step3. Call the GetCanOverScroll method, Set the parameter scrollable is true
     * @tc.expected: The result is true
     */
    auto scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SelectWithScroll001
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SelectWithScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter IsScrollable is false
     * @tc.expected: The OutOfScrollableOffset is 0.0
     */
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(false));
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->GetOutOfScrollableOffset(), 0.0f);
}

/**
 * @tc.name: SelectWithScroll002
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SelectWithScroll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter IsScrollable is true
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
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
HWTEST_F(ScrollableTestNg, SelectWithScroll003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter IsScrollable is true and deltaY_ is 0
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -0.0f);
}

/**
 * @tc.name: SelectWithScroll004
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SelectWithScroll004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter isAnimationStop_ is false
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
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
HWTEST_F(ScrollableTestNg, SelectWithScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter isAnimationStop_ is true
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
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
HWTEST_F(ScrollableTestNg, LimitMouseEndOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the LimitMouseEndOffset method, Set the parameter is Axis::HORIZONTAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    scrollPn->SetAxis(Axis::HORIZONTAL);
    scrollPn->mouseEndOffset_ = OffsetF(-1.0f, -1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);

    /**
     * @tc.steps: step3. Call the LimitMouseEndOffset method, Set the parameter is Axis::VERTICAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    scrollPn->SetAxis(Axis::VERTICAL);
    scrollPn->mouseEndOffset_ = OffsetF(1.0f, 1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);
}

/**
 * @tc.name: HotZoneScroll001
 * @tc.desc: Test nested HotZoneScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HotZoneScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the HotZoneScroll method, Set the parameter status of animator is idle
     * @tc.expected: The animator is not nullptr
     */
    float offsetPct = 0.5f;
    scrollPn->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    scrollPn->animator_->Reverse();
    EXPECT_NE(scrollPn->animator_->GetStatus(), Animator::Status::RUNNING);
    scrollPn->HotZoneScroll(offsetPct);
    EXPECT_NE(scrollPn->animator_, nullptr);

    /**
     * @tc.steps: step3. Call the HotZoneScroll method, Set the parameter is Axis::HORIZONTAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The offset is
     */
    scrollPn->velocityMotion_ =
        AceType::MakeRefPtr<BezierVariableVelocityMotion>(offsetPct, [](float offset) -> bool { return true; });
    scrollPn->HotZoneScroll(offsetPct);
    EXPECT_EQ(scrollPn->lastHonezoneOffsetPct_, 0.0f);
}

/**
 * @tc.name: CoordinateWithRefresh001
 * @tc.desc: Test nested CoordinateWithRefresh
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, CoordinateWithRefresh001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the CoordinateWithRefresh method
     * @tc.expected: The result is UNKNOWN
     */
    double offset = 0.2f;
    int32_t source = 1;
    bool isAtTop = true;
    scrollPn->refreshCoordination_ = AceType::MakeRefPtr<RefreshCoordination>(scrollPn->GetHost());
    auto result = scrollPn->CoordinateWithRefresh(offset, source, isAtTop);
    EXPECT_EQ(result, RefreshCoordinationMode::UNKNOWN);
}

/**
 * @tc.name: SetMaxFlingVelocity001
 * @tc.desc: Test nested SetMaxFlingVelocity
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SetMaxFlingVelocity001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the SetMaxFlingVelocity method
     * @tc.expected: The maxFlingVelocity is MAX_VELOCITY or max
     */
    double max = 0.0f;
    scrollPn->SetMaxFlingVelocity(max);
    EXPECT_EQ(scrollPn->maxFlingVelocity_, MAX_VELOCITY);
    max = 0.2f;
    scrollPn->SetMaxFlingVelocity(max);
    EXPECT_EQ(scrollPn->maxFlingVelocity_, 0.2f);
}

/**
 * @tc.name: MarkSelectedItems001
 * @tc.desc: Test nested MarkSelectedItems
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, MarkSelectedItems001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the MarkSelectedItems method
     * @tc.expected: The IsScrollable is false
     */
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
HWTEST_F(ScrollableTestNg, ShouldSelectScrollBeStopped001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);

    /**
     * @tc.steps: step2. When lastMouseMove is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is false
     */
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

    /**
     * @tc.steps: step3. When selectMotion is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is false
     */
    scrollPn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. When lastMouseMove is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is true
     */
    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetY(-0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -0.0f);
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ShouldSelectScrollBeStopped002
 * @tc.desc: Test nested ShouldSelectScrollBeStopped
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ShouldSelectScrollBeStopped002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer and call ShouldSelectScrollBeStopped
     * @tc.expected: Pointer is not nullptr and result is true
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;
    auto result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ShouldSelectScrollBeStopped003
 * @tc.desc: Test nested ShouldSelectScrollBeStopped
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ShouldSelectScrollBeStopped003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the ShouldSelectScrollBeStopped method
     * @tc.expected: The result is false
     */
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
 * @tc.name: UpdateMouseStart001
 * @tc.desc: Test nested UpdateMouseStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, UpdateMouseStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the UpdateMouseStart method
     * @tc.expected: The GetY is 0.1
     */
    scrollPn->SetAxis(Axis::VERTICAL);
    float offset = 0.1f;
    scrollPn->UpdateMouseStart(offset);
    EXPECT_EQ(scrollPn->mouseStartOffset_.GetY(), 0.1f);
}

/**
 * @tc.name: UpdateMouseStart002
 * @tc.desc: Test nested UpdateMouseStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, UpdateMouseStart002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the UpdateMouseStart method
     * @tc.expected: The GetX is 0.1
     */
    scrollPn->SetAxis(Axis::HORIZONTAL);
    float offset = 0.2f;
    scrollPn->UpdateMouseStart(offset);
    EXPECT_EQ(scrollPn->mouseStartOffset_.GetX(), 0.2f);
}

/**
 * @tc.name: GetOffsetWithLimit001
 * @tc.desc: Test nested GetOffsetWithLimit
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetOffsetWithLimit001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the GetOffsetWithLimit method
     * @tc.expected: The result is 0.2
     */
    float offset = 0.2f;
    auto result = scrollPn->GetOffsetWithLimit(offset);
    EXPECT_NE(result, offset);
}

/**
 * @tc.name: GetOffsetWithLimit002
 * @tc.desc: Test nested GetOffsetWithLimit
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetOffsetWithLimit002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the GetOffsetWithLimit method
     * @tc.expected: The result is 0.0
     */
    float offset = -0.1f;
    auto result = scrollPn->GetOffsetWithLimit(offset);
    EXPECT_EQ(result, -0.0f);
}

/**
 * @tc.name: GetOffsetWithLimit003
 * @tc.desc: Test nested GetOffsetWithLimit
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetOffsetWithLimit003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the GetOffsetWithLimit method
     * @tc.expected: The result is 0.0
     */
    float offset = 0.0f;
    auto result = scrollPn->GetOffsetWithLimit(offset);
    EXPECT_EQ(result, offset);
}

/**
 * @tc.name: OnScrollStop001
 * @tc.desc: Test nested OnScrollStop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, OnScrollStop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the OnScrollStop method
     * @tc.expected: The scrollStop is false
     */
    scrollPn->scrollStop_ = true;
    scrollPn->SetScrollAbort(true);
    bool isStopTrigger = false;
    OnScrollStopEvent stopEvent = [&isStopTrigger]() { isStopTrigger = true; };
    scrollPn->OnScrollStop(stopEvent);
    EXPECT_FALSE(scrollPn->scrollStop_);
}

/**
 * @tc.name: HandleHotZone001
 * @tc.desc: Test nested HandleHotZone
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleHotZone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the HandleHotZone method
     * @tc.expected: The scrollable is false
     */
    const RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    notifyDragEvent->SetX(0.1f);
    EXPECT_EQ(notifyDragEvent->GetX(), 0.1f);
    notifyDragEvent->SetY(0.2f);
    EXPECT_EQ(notifyDragEvent->GetY(), 0.2f);
    int32_t minPlatformVersion = 11;
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
    scrollPn->HandleHotZone(DragEventType::ENTER, notifyDragEvent);
    scrollPn->HandleHotZone(DragEventType::LEAVE, notifyDragEvent);
    EXPECT_FALSE(scrollPn->IsScrollable());
}

/**
 * @tc.name: HandleHotZone002
 * @tc.desc: Test nested HandleHotZone
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleHotZone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the HandleHotZone method
     * @tc.expected: The scrollable is false
     */
    const RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    notifyDragEvent->SetX(0.1f);
    EXPECT_EQ(notifyDragEvent->GetX(), 0.1f);
    notifyDragEvent->SetY(0.2f);
    EXPECT_EQ(notifyDragEvent->GetY(), 0.2f);
    int32_t minPlatformVersion = 12;
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
    scrollPn->HandleHotZone(DragEventType::MOVE, notifyDragEvent);
    EXPECT_FALSE(scrollPn->IsScrollable());
}

/**
 * @tc.name: HandleHotZone003
 * @tc.desc: Test nested HandleHotZone
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleHotZone003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the HandleHotZone method
     * @tc.expected: The scrollable is false
     */
    const RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    notifyDragEvent->SetX(0.1f);
    EXPECT_EQ(notifyDragEvent->GetX(), 0.1f);
    notifyDragEvent->SetY(0.2f);
    EXPECT_EQ(notifyDragEvent->GetY(), 0.2f);
    int32_t minPlatformVersion = 12;
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
    scrollPn->HandleHotZone(DragEventType::START, notifyDragEvent);
    EXPECT_FALSE(scrollPn->IsScrollable());
}

/**
 * @tc.name: NeedCoordinateScrollWithNavigation001
 * @tc.desc: Test nested NeedCoordinateScrollWithNavigation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, NeedCoordinateScrollWithNavigation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr and result is false
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->navBarPattern_ = nullptr;
    OverScrollOffset overScrollOffset = { 0.0f, 0.5f };
    bool result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedCoordinateScrollWithNavigation002
 * @tc.desc: Test nested NeedCoordinateScrollWithNavigation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, NeedCoordinateScrollWithNavigation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->GetParentNavigation();

    /**
     * @tc.steps: step2. Call the NeedCoordinateScrollWithNavigation method
     * @tc.expected: The scrollable is false
     */
    scrollPn->navBarPattern_ = AceType::MakeRefPtr<NavBarPattern>();
    OverScrollOffset overScrollOffset = { 0.0f, 0.5f };
    bool result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. Call the NeedCoordinateScrollWithNavigation method
     * @tc.expected: The scrollable is false
     */
    overScrollOffset = { 0.1f, 0.5f };
    result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. Call the NeedCoordinateScrollWithNavigation method
     * @tc.expected: The scrollable is false
     */
    scrollPn->SetAxis(Axis::VERTICAL);
    result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step5. Call the NeedCoordinateScrollWithNavigation method, set source is SCROLL_FROM_CHILD
     * @tc.expected: The scrollable is true
     */
    result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_CHILD, overScrollOffset);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NotifyMoved001
 * @tc.desc: Test nested NotifyMoved failure status
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, NotifyMoved001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the NotifyMoved method
     * @tc.expected: Scrollable is nullptr
     */
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollPn->NotifyMoved(false);
    EXPECT_FALSE(scrollPn->scrollableEvent_->GetScrollable());

    /**
     * @tc.steps: step3. Call the NotifyMoved method
     * @tc.expected: Scrollable is not nullptr
     */
    auto scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    scrollPn->NotifyMoved(false);
    EXPECT_TRUE(scrollPn->scrollableEvent_->GetScrollable());
}

/**
 * @tc.name: NeedSplitScroll001
 * @tc.desc: Test nested NeedSplitScroll failure status
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, NeedSplitScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the NeedSplitScroll method
     * @tc.expected: return false
     */
    OverScrollOffset overScrollOffset = {0.0f, 0.0f};
    EXPECT_FALSE(scrollPn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));
    overScrollOffset = {0.0f, 0.1f};
    EXPECT_FALSE(scrollPn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));
    scrollPn->refreshCoordination_ = nullptr;
    EXPECT_FALSE(scrollPn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto scrollableNode = AceType::MakeRefPtr<FrameNode>("tag", 0, pattern);
    scrollPn->refreshCoordination_ = AceType::MakeRefPtr<RefreshCoordination>(scrollableNode);
    EXPECT_FALSE(scrollPn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));
}
} // namespace OHOS::Ace::NG
