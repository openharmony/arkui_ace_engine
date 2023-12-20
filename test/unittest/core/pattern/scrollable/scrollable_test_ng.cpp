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
    EXPECT_FALSE(res);
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
    scrollPn->OnScrollEndRecursive();
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
} // namespace OHOS::Ace::NG
