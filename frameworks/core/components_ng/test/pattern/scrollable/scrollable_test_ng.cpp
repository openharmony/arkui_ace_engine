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
#include "gtest/gtest.h"
#include "gtest/hwext/gtest-ext.h"

#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"

#define protected public
#define private public
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/test/mock/pattern/scrollable/mock_nestable_scroll_container.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ScrollableTestNg : public testing::Test {
    void SetUp() override;
    void TearDown() override;

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

    MOCK_METHOD(OverScrollOffset, GetOverScrollOffset, (double delta), (const, override));
};

void ScrollableTestNg::SetUp()
{
    InitNestedScrolls();
    MockPipelineBase::SetUp();
}

void ScrollableTestNg::TearDown()
{
    scroll_.Reset();
    mockScroll_.Reset();
    MockPipelineBase::TearDown();
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
        .Times(6)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(3).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(3).WillRepeatedly(Return(true));

    // test self only
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_ONLY, .backward = NestedScrollMode::SELF_ONLY };
    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);

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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(2).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(2).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    auto result = scrollPn->HandleScroll(20, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL);
    EXPECT_TRUE(result.reachEdge);
    EXPECT_EQ(result.remain, 5.0f);

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
        .Times(1)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
        .Times(1)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
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
        .Times(1)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 0, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
        .Times(1)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
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
        .Times(1)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
        .Times(1)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 0, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 5, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
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
        .Times(2)
        .WillRepeatedly(Return(OverScrollOffset { .start = 0, .end = 0 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
        .Times(1)
        .WillRepeatedly(Return(OverScrollOffset { .start = 0, .end = 5 }));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1).WillRepeatedly(Return(false));
    EXPECT_CALL(*scrollPn, UpdateCurrentOffset).Times(1).WillRepeatedly(Return(true));

    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(0);

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_ONLY, .backward = NestedScrollMode::SELF_ONLY };

    bool res = scrollPn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);

    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
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
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(1).WillOnce(Return(true));
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };
    bool res = scrollPn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(1).WillOnce(Return(false));
    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
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
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(2).WillRepeatedly(Return(false));
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };
    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);
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
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);

    EXPECT_CALL(*mockPn, HandleScrollVelocity).Times(0);
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };
    scrollPn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    bool res = scrollPn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);
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

    EXPECT_CALL(*scrollPn, IsAtTop).Times(1);
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
} // namespace OHOS::Ace::NG
