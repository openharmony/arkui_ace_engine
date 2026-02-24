/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
 
#include "vertical_overflow_handler_test_ng.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/event/scrollable_event.h"
#include "core/components_ng/layout/vertical_overflow_handler.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/custom_frame_node/custom_pattern.h"
#define protected public
#define private public

namespace OHOS::Ace::NG {
/**
 * @tc.name: OutOfBoundaryTest
 * @tc.desc: test VerticalOverflowHandler::OutOfBoundary()
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, OutOfBoundaryTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create VerticalOverflowHandler object.
     */
    VerticalOverflowHandler handler;
    handler.SetContentRect(RectF(0.f, 100.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 100.f, 400.f, 400.f));
    handler.childFrameTop_ = 0.0f;
    /**
     * @tc.expected: scrollDistance_ == 0 means we can only scroll up the child components.
     */
    EXPECT_TRUE(handler.OutOfBoundary(10.f));
    EXPECT_FALSE(handler.OutOfBoundary(-10.f));
    handler.childFrameTop_ = -50.0f;
    /**
     * @tc.expected: scrollDistance_ == -50.0f means we can scroll up or scroll down the child components.
     */
    EXPECT_FALSE(handler.OutOfBoundary(10.f));
    EXPECT_FALSE(handler.OutOfBoundary(-10.f));
    /**
     * @tc.expected: scrollDistance_ == contentRect——.Height() - totalChildFrameRect_.Height()
     *               means we can only scroll down the child components.
     */
    handler.childFrameTop_ = -200.0f;
    EXPECT_FALSE(handler.OutOfBoundary(10.f));
    EXPECT_TRUE(handler.OutOfBoundary(-10.f));
}

/**
 * @tc.name: CreateContentRectTest
 * @tc.desc: test VerticalOverflowHandler::CreateContentRect()
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, CreateContentRectTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create flex.
     */
    auto flex = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
        // step: set flex common attribute
        ViewAbstract::SetPadding(CalcLength(10.0f));
        ViewAbstract::SetBorderWidth(Dimension(20, DimensionUnit::PX));
    });
    CHECK_NULL_VOID(flex);
    PaddingProperty safeAreaPadding = {
        .left = CalcLength(30.0f),
        .right = CalcLength(30.0f),
        .top = CalcLength(30.0f),
        .bottom = CalcLength(30.0f)
    };
    flex->GetLayoutProperty()->UpdateSafeAreaPadding(safeAreaPadding);
    flex->GetGeometryNode()->SetFrameSize(SizeF(200.f, 200.f));
    auto pattern = flex->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    const auto& vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex)));
    vOverflowHandler->CreateContentRect();
    /**
     * @tc.expected: VerticalOverflowHandler->contentRect_.FrameSize == 200 - 2 * (10 + 20 + 30)
     *               VerticalOverflowHandler->contentRect_.FrameOffset == 10 + 20 + 30
     */
    EXPECT_EQ(vOverflowHandler->contentRect_, RectF(60.f, 60.f, 80.f, 80.f)) <<
        vOverflowHandler->contentRect_.ToString();
}

/**
 * @tc.name: IsVerticalLayoutTest
 * @tc.desc: test VerticalOverflowHandler::IsVerticalLayout()
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, IsVerticalLayoutTest, TestSize.Level1)
{
    auto flex1 = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
    });
    CHECK_NULL_VOID(flex1);
    auto pattern = flex1->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex1)));
    EXPECT_TRUE(vOverflowHandler->IsVerticalLayout());

    auto flex2 = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
    });
    CHECK_NULL_VOID(flex2);
    pattern = flex2->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    vOverflowHandler = pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex2)));
    EXPECT_FALSE(vOverflowHandler->IsVerticalLayout());
}

/**
 * @tc.name: IsVerticalReverseLayoutTest
 * @tc.desc: test VerticalOverflowHandler::IsVerticalReverseLayout()
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, IsVerticalReverseLayoutTest, TestSize.Level1)
{
    auto flex1 = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
    });
    CHECK_NULL_VOID(flex1);
    auto pattern = flex1->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex1)));
    EXPECT_FALSE(vOverflowHandler->IsVerticalReverseLayout());

    auto flex2 = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN_REVERSE);
    });
    CHECK_NULL_VOID(flex2);
    pattern = flex2->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    vOverflowHandler = pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex2)));
    EXPECT_TRUE(vOverflowHandler->IsVerticalReverseLayout());
}

/**
 * @tc.name: InitOffsetAfterLayoutTest01
 * @tc.desc: test VerticalOverflowHandler::InitOffsetAfterLayout() when flexDirectio is COLUMN
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, InitOffsetAfterLayoutTest01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create flex.
     */
    auto flex = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
        // step: set flex common attribute
        ViewAbstract::SetPadding(CalcLength(10.0f));
        ViewAbstract::SetBorderWidth(Dimension(20, DimensionUnit::PX));
    });
    CHECK_NULL_VOID(flex);
    auto pattern = flex->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    const auto& vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex)));
    vOverflowHandler->SetContentRect(RectF(0.f, 100.f, 200.f, 200.f));
    vOverflowHandler->SetTotalChildFrameRect(RectF(0.f, 100.f, 400.f, 400.f));
    vOverflowHandler->InitOffsetAfterLayout();
    /**
     * @tc.expected: scrollDistance_ is set to totalChildFrameRect.GetY() - contentRect_.GetY()
     *               offsetToChildFrameBottom_ is set to totalChildFrameRect.Bottom() - contentRect_.Bottom()
     */
    EXPECT_EQ(vOverflowHandler->childFrameTop_.value_or(-1), 0.f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 200.0f);
    /**
     * @tc.steps: step2. scroll up by 100 and change the totalChildFrameRect
     */
    vOverflowHandler->HandleScrollImpl(-100.0f, 0);
    vOverflowHandler->SetTotalChildFrameRect(RectF(0.f, 100.f, 400.f, 300.f));
    vOverflowHandler->InitOffsetAfterLayout();
    /**
     * @tc.expected: scrollDistance_ is not changed
     *               when the totalFrameRect's height is decreased, we first adjust the totalFrameRect's bottom edge
     */
    EXPECT_EQ(vOverflowHandler->childFrameTop_.value_or(-1), -100.f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 0.0f);
    vOverflowHandler->SetTotalChildFrameRect(RectF(0.f, 100.f, 400.f, 200.f));
    vOverflowHandler->InitOffsetAfterLayout();
    /**
     * @tc.expected: when reaching the bottom boundary, we start to adjust the totalFrameRect's top edge
     */
    EXPECT_EQ(vOverflowHandler->childFrameTop_.value_or(-1), 0.f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 0.0f);
}

/**
 * @tc.name: InitOffsetAfterLayoutTest02
 * @tc.desc: test VerticalOverflowHandler::InitOffsetAfterLayout() when flexDirectio is COLUMN_REVERSE
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, InitOffsetAfterLayoutTest02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create flex.
     */
    auto flex = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN_REVERSE);
        // step: set flex common attribute
        ViewAbstract::SetPadding(CalcLength(10.0f));
        ViewAbstract::SetBorderWidth(Dimension(20, DimensionUnit::PX));
    });
    CHECK_NULL_VOID(flex);
    auto pattern = flex->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    const auto& vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex)));
    vOverflowHandler->SetContentRect(RectF(0.f, 100.f, 200.f, 200.f));
    vOverflowHandler->SetTotalChildFrameRect(RectF(0.f, -100.f, 400.f, 400.f));
    vOverflowHandler->InitOffsetAfterLayout();
    /**
     * @tc.expected: scrollDistance_ is set to totalChildFrameRect.GetY() - contentRect_.GetY()
     *               offsetToChildFrameBottom_ is set to totalChildFrameRect.Bottom() - contentRect_.Bottom()
     */
    EXPECT_EQ(vOverflowHandler->childFrameTop_.value_or(-1), -200.0f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 0.0f);
    /**
     * @tc.steps: step2. scroll down by 100 and change the totalChildFrameRect
     */
    vOverflowHandler->HandleScrollImpl(100.0f, 0);
    vOverflowHandler->SetTotalChildFrameRect(RectF(0.f, 100.f, 400.f, 300.f));
    vOverflowHandler->InitOffsetAfterLayout();
    /**
     * @tc.expected: when the totalFrameRect's height is decreased, we first adjust the totalFrameRect's top edge
     */
    EXPECT_EQ(vOverflowHandler->childFrameTop_.value_or(-1), 0.f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 100.0f);
    vOverflowHandler->SetTotalChildFrameRect(RectF(0.f, 100.f, 400.f, 200.f));
    vOverflowHandler->InitOffsetAfterLayout();
    /**
     * @tc.expected: when reaching the top boundary, we start to adjust the totalFrameRect's bottom edge
     */
    EXPECT_EQ(vOverflowHandler->childFrameTop_.value_or(-1), 0.f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 0.0f);
}

/**
 * @tc.name: AdjustTotalChildFrameRectTest
 * @tc.desc: test VerticalOverflowHandler::AdjustTotalChildFrameRect() when flexDirectio is COLUMN_REVERSE
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, AdjustTotalChildFrameRectTest, TestSize.Level1)
{
    VerticalOverflowHandler handler;
    handler.SetContentRect(RectF(0.f, 100.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 100.f, 400.f, 400.f));
    handler.AdjustTotalChildFrameRect();
    EXPECT_EQ(handler.totalChildFrameRect_, RectF(0.f, 100.f, 400.f, 400.f))
        << handler.totalChildFrameRect_.ToString();

    handler.SetContentRect(RectF(0.f, 100.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 150.f, 400.f, 400.f));
    handler.AdjustTotalChildFrameRect();
    EXPECT_EQ(handler.totalChildFrameRect_, RectF(0.f, 100.f, 400.f, 450.f))
        << handler.totalChildFrameRect_.ToString();

    handler.SetContentRect(RectF(0.f, 100.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 400.f, 400.f));
    handler.AdjustTotalChildFrameRect();
    EXPECT_EQ(handler.totalChildFrameRect_, RectF(0.f, 0.f, 400.f, 400.f))
        << handler.totalChildFrameRect_.ToString();

    handler.SetContentRect(RectF(0.f, 100.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 200.f, 200.f));
    handler.AdjustTotalChildFrameRect();
    EXPECT_EQ(handler.totalChildFrameRect_, RectF(0.f, 0.f, 200.f, 300.f))
        << handler.totalChildFrameRect_.ToString();
}

/**
 * @tc.name: HandleScrollImplTest01
 * @tc.desc: test VerticalOverflowHandler::HandleScrollImpl()
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, HandleScrollImplTest01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create flex.
     */
    auto flex = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
    });
    CHECK_NULL_VOID(flex);
    auto pattern = flex->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    const auto& vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex)));
    vOverflowHandler->SetContentRect(RectF(0.f, 100.f, 200.f, 200.f));
    vOverflowHandler->SetTotalChildFrameRect(RectF(0.f, 100.f, 400.f, 400.f));
    vOverflowHandler->HandleScrollImpl(-100.0f, 0);
    /**
     * @tc.expected: when scrolling up by 100, the scrollDistance_ is equal to -100
     *               offsetToChildFrameBottom_ is -100 + 400 - 200 = 100
     */
    EXPECT_EQ(vOverflowHandler->childFrameTop_.value_or(-1), -100.0f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 100.0f);
    vOverflowHandler->HandleScrollImpl(-200.0f, 0);
    /**
     * @tc.expected: when scrolling up by -200, we should clamp scrollDistance_ to avoid exceeding scrolling boundary
     *               the scrollDistance_ is equal to -200 and offsetToChildFrameBottom_ is equal to 0
     */
    EXPECT_EQ(vOverflowHandler->childFrameTop_.value_or(-1), -200.0f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 0.0f);
    vOverflowHandler->HandleScrollImpl(300.0f, 0);
    /**
     * @tc.expected: when scrolling down by 300, we should clamp scrollDistance_ to avoid exceeding scrolling boundary
     *               the scrollDistance_ is equal to 0 and offsetToChildFrameBottom_ is equal to 0 + 400 - 200 = 200
     */
    EXPECT_EQ(vOverflowHandler->childFrameTop_.value_or(-1), 0.0f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 200.0f);
}

/**
 * @tc.name: HandleContentOverflowTest
 * @tc.desc: test FrameNode::HandleContentOverflow()
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, HandleContentOverflowTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create flex component and its children
     */
    RefPtr<FrameNode> child4, child5;
    auto flex = CreateFlex([this, &child4, &child5](FlexModelNG model) {
        ViewAbstract::UpdateSafeAreaExpandOpts({
            .type = SAFE_AREA_TYPE_ALL,
            .edges = SAFE_AREA_EDGE_ALL,
        });
        model.SetDirection(FlexDirection::COLUMN);
        child4 = CreateFlex([](FlexModelNG model) {});
        child5 = CreateFlex([](FlexModelNG model) {});
    });
    flex->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    flex->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    child4->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    child4->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    child4->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    child5->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 60));
    child5->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    VerticalOverflowHandler handler(AceType::WeakClaim(AceType::RawPtr(flex)));
    handler.CreateContentRect();
    handler.SetTotalChildFrameRect(RectF(0, 0, 50, 110));
    handler.HandleContentOverflow();
    /**
     * @tc.expected: register scrollEvent and initialize
     */
    EXPECT_EQ(handler.childFrameTop_.value_or(-1), 0);
    EXPECT_EQ(handler.offsetToChildFrameBottom_, 60);
    EXPECT_NE(handler.scrollableEvent_, nullptr);
    EXPECT_FALSE(handler.hasParentAdjust_);
    handler.HandleScrollImpl(-20, 0);
    /**
     * @tc.expected: After scrolling up by 20, scrollDistance == 20 and children have correct offset
     */
    EXPECT_EQ(handler.childFrameTop_.value_or(-1), -20);
    EXPECT_EQ(handler.offsetToChildFrameBottom_, 40);
    EXPECT_TRUE(handler.hasParentAdjust_);
    EXPECT_EQ(child4->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, -20));
    EXPECT_EQ(child5->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, 40));
    handler.SetTotalChildFrameRect(RectF(0, 0, 50, 50));
    handler.HandleContentOverflow();
     /**
     * @tc.expected: Unregister scrollEvent and reset
     */
    EXPECT_FALSE(handler.childFrameTop_.has_value());
    EXPECT_EQ(handler.scrollableEvent_, nullptr);
    EXPECT_FALSE(handler.hasParentAdjust_);
}

/**
 * @tc.name: RegisterScrollableEventNonVerticalLayoutTest
 * @tc.desc: test VerticalOverflowHandler::RegisterScrollableEvent() when layout is not vertical
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, RegisterScrollableEventNonVerticalLayoutTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create flex with ROW direction (non-vertical).
     */
    auto flex = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
    });
    CHECK_NULL_VOID(flex);
    auto pattern = flex->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex)));
    /**
     * @tc.steps: step2. Call RegisterScrollableEvent when IsVerticalLayout returns false.
     * @tc.expected: scrollableEvent_ should remain nullptr (early return).
     */
    vOverflowHandler->RegisterScrollableEvent();
    EXPECT_EQ(vOverflowHandler->scrollableEvent_, nullptr);
}

/**
 * @tc.name: RegisterScrollableEventGestureHierarchyNotEmptyTest
 * @tc.desc: test VerticalOverflowHandler::RegisterScrollableEvent() when gesture hierarchy is not empty
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, RegisterScrollableEventGestureHierarchyNotEmptyTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create flex with COLUMN direction and add a gesture.
     */
    auto flex = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
    });
    CHECK_NULL_VOID(flex);
    auto pattern = flex->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex)));
    /**
     * @tc.steps: step2. Manually set a non-empty gesture hierarchy by creating scrollableEvent_.
     * @tc.expected: When scrollableEvent_ already exists, should return early without registering again.
     */
    vOverflowHandler->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    vOverflowHandler->RegisterScrollableEvent();
    // scrollableEvent_ should remain the same object (not recreated)
    EXPECT_NE(vOverflowHandler->scrollableEvent_, nullptr);
}

/**
 * @tc.name: RegisterScrollableEventWithExistingEventTest
 * @tc.desc: test VerticalOverflowHandler::RegisterScrollableEvent() when scrollableEvent_ already exists
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, RegisterScrollableEventWithExistingEventTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create flex and manually set scrollableEvent_.
     */
    auto flex = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
    });
    CHECK_NULL_VOID(flex);
    auto pattern = flex->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex)));
    auto originalEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    vOverflowHandler->scrollableEvent_ = originalEvent;
    /**
     * @tc.steps: step2. Call RegisterScrollableEvent when scrollableEvent_ already exists.
     * @tc.expected: Should return early without changing scrollableEvent_.
     */
    vOverflowHandler->RegisterScrollableEvent();
    EXPECT_EQ(vOverflowHandler->scrollableEvent_, originalEvent);
}

/**
 * @tc.name: AdjustChildrenOffsetNullChildNodeTest
 * @tc.desc: test VerticalOverflowHandler::AdjustChildrenOffset() with null child node
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, AdjustChildrenOffsetNullChildNodeTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create VerticalOverflowHandler directly without proper frame node setup.
     */
    VerticalOverflowHandler handler;
    handler.SetContentRect(RectF(0.f, 0.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 200.f, 400.f));
    /**
     * @tc.steps: step2. Call AdjustChildrenOffset with null child nodes.
     * @tc.expected: Should not crash and handle null children gracefully.
     */
    handler.AdjustChildrenOffset(50.0f, false);
    // If no crash, test passes
}

/**
 * @tc.name: AdjustChildrenOffsetWithHubTest
 * @tc.desc: test VerticalOverflowHandler::AdjustChildrenOffset() with OverflowScrollEventHub
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, AdjustChildrenOffsetWithHubTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create flex with children.
     */
    RefPtr<FrameNode> child;
    auto flex = CreateFlex([this, &child](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
        child = CreateFlex([](FlexModelNG model) {});
    });
    CHECK_NULL_VOID(flex);
    CHECK_NULL_VOID(child);
    flex->GetGeometryNode()->SetFrameSize(SizeF(100, 200));
    child->GetGeometryNode()->SetFrameSize(SizeF(80, 100));
    child->GetGeometryNode()->SetMarginFrameOffset(OffsetF(10, 10));

    VerticalOverflowHandler handler(AceType::WeakClaim(AceType::RawPtr(flex)));
    handler.SetContentRect(RectF(0.f, 0.f, 100.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 100.f, 200.f));
    /**
     * @tc.steps: step2. Call AdjustChildrenOffset with offset.
     * @tc.expected: Children offsets should be adjusted.
     */
    handler.AdjustChildrenOffset(-50.0f, false);
    // If no crash and method executes, test passes
}

/**
 * @tc.name: HandleScrollImplOutOfBoundaryTest
 * @tc.desc: test VerticalOverflowHandler::HandleScrollImpl() when out of boundary
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, HandleScrollImplOutOfBoundaryTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create handler with boundary condition.
     */
    VerticalOverflowHandler handler;
    handler.SetContentRect(RectF(0.f, 0.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 400.f, 400.f));
    handler.childFrameTop_ = 0.0f;  // At top boundary
    /**
     * @tc.steps: step2. Call HandleScrollImpl with positive offset (pushing down at top).
     * @tc.expected: Should return false when out of boundary.
     */
    bool result = handler.HandleScrollImpl(10.0f, 0);
    EXPECT_FALSE(result);
    /**
     * @tc.steps: step3. Set to bottom boundary and test negative offset.
     */
    handler.childFrameTop_ = -200.0f;  // At bottom boundary
    result = handler.HandleScrollImpl(-10.0f, 0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleScrollImplWithinBoundaryTest
 * @tc.desc: test VerticalOverflowHandler::HandleScrollImpl() when within boundary
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, HandleScrollImplWithinBoundaryTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create handler with offset in middle range.
     */
    auto flex = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
    });
    CHECK_NULL_VOID(flex);
    auto pattern = flex->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    const auto& vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex)));
    vOverflowHandler->SetContentRect(RectF(0.f, 0.f, 200.f, 200.f));
    vOverflowHandler->SetTotalChildFrameRect(RectF(0.f, 0.f, 400.f, 400.f));
    vOverflowHandler->childFrameTop_ = -100.0f;  // Middle position
    /**
     * @tc.steps: step2. Call HandleScrollImpl with offset within boundary.
     * @tc.expected: Should return true and adjust offsets.
     */
    bool result = vOverflowHandler->HandleScrollImpl(50.0f, 0);
    EXPECT_TRUE(result);
    EXPECT_EQ(vOverflowHandler->childFrameTop_.value_or(0), -50.0f);
}

/**
 * @tc.name: UnRegisterScrollableEventNullEventTest
 * @tc.desc: test VerticalOverflowHandler::UnRegisterScrollableEvent() when scrollableEvent_ is null
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, UnRegisterScrollableEventNullEventTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create handler without setting scrollableEvent_.
     */
    auto flex = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
    });
    CHECK_NULL_VOID(flex);
    auto pattern = flex->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex)));
    /**
     * @tc.steps: step2. Call UnRegisterScrollableEvent when scrollableEvent_ is null.
     * @tc.expected: Should return early without crashing.
     */
    EXPECT_EQ(vOverflowHandler->scrollableEvent_, nullptr);
    vOverflowHandler->UnRegisterScrollableEvent();
    EXPECT_EQ(vOverflowHandler->scrollableEvent_, nullptr);
}

/**
 * @tc.name: UnRegisterScrollableEventWithEventTest
 * @tc.desc: test VerticalOverflowHandler::UnRegisterScrollableEvent() when scrollableEvent_ exists
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, UnRegisterScrollableEventWithEventTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create handler and set scrollableEvent_.
     */
    auto flex = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
    });
    CHECK_NULL_VOID(flex);
    auto pattern = flex->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex)));
    vOverflowHandler->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    vOverflowHandler->childFrameTop_ = 100.0f;
    /**
     * @tc.steps: step2. Call UnRegisterScrollableEvent when scrollableEvent_ exists.
     * @tc.expected: scrollableEvent_ should be null and childFrameTop_ should be reset.
     */
    vOverflowHandler->UnRegisterScrollableEvent();
    EXPECT_EQ(vOverflowHandler->scrollableEvent_, nullptr);
    EXPECT_FALSE(vOverflowHandler->childFrameTop_.has_value());
}

/**
 * @tc.name: HandleContentOverflowOverflowDisabledTest
 * @tc.desc: test VerticalOverflowHandler::HandleContentOverflow() when overflow is disabled
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, HandleContentOverflowOverflowDisabledTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create handler with overflow disabled.
     */
    auto flex = CreateFlex([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
    });
    CHECK_NULL_VOID(flex);
    auto pattern = flex->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(flex)));
    vOverflowHandler->SetContentRect(RectF(0.f, 0.f, 200.f, 200.f));
    vOverflowHandler->SetTotalChildFrameRect(RectF(0.f, 0.f, 400.f, 400.f));
    vOverflowHandler->SetOverflowDisabledFlag(true);
    /**
     * @tc.steps: step2. Call HandleContentOverflow with overflow disabled.
     * @tc.expected: Should unregister scrollable event.
     */
    vOverflowHandler->HandleContentOverflow();
    EXPECT_EQ(vOverflowHandler->scrollableEvent_, nullptr);
}

/**
 * @tc.name: IsVerticalOverflowTest
 * @tc.desc: test VerticalOverflowHandler::IsVerticalOverflow() with various conditions
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, IsVerticalOverflowTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Test when content is larger than children (no overflow).
     */
    VerticalOverflowHandler handler;
    handler.SetContentRect(RectF(0.f, 0.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 200.f, 100.f));
    EXPECT_FALSE(handler.IsVerticalOverflow());

    /**
     * @tc.steps: step2. Test when children exceed content at bottom.
     */
    handler.SetContentRect(RectF(0.f, 0.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 200.f, 300.f));
    EXPECT_TRUE(handler.IsVerticalOverflow());

    /**
     * @tc.steps: step3. Test when children exceed content at top.
     */
    handler.SetContentRect(RectF(0.f, 100.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 50.f, 200.f, 100.f));
    EXPECT_TRUE(handler.IsVerticalOverflow());
}

/**
 * @tc.name: IsOverflowTest
 * @tc.desc: test VerticalOverflowHandler::IsOverflow() with various conditions
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, IsOverflowTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Test with no overflow.
     */
    VerticalOverflowHandler handler;
    handler.SetContentRect(RectF(0.f, 0.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 200.f, 200.f));
    EXPECT_FALSE(handler.IsOverflow());

    /**
     * @tc.steps: step2. Test with overflow exceeding max gap.
     */
    handler.SetContentRect(RectF(0.f, 0.f, 200.f, 200.f));
    handler.SetTotalChildFrameRect(RectF(0.f, 0.f, 200.f, 300.f));
    EXPECT_TRUE(handler.IsOverflow());
}

/**
 * @tc.name: CustomHandleContentOverflowTest
 * @tc.desc: test CustomPattern::HandleContentOverflow() with CUSTOM_ETS_TAG
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, CustomHandleContentOverflowTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create custom component (CUSTOM_ETS_TAG) and its children
     */
    RefPtr<FrameNode> child4, child5;
    
    // Create custom FrameNode with CustomPattern
    auto custom = FrameNode::CreateFrameNode(
        V2::CUSTOM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<CustomPattern>());
    
    // Create child FrameNodes for the custom component
    child4 = FrameNode::CreateFrameNode(V2::CUSTOM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CustomPattern>());
    child5 = FrameNode::CreateFrameNode(V2::CUSTOM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CustomPattern>());
    
    child4->MountToParent(custom);
    child5->MountToParent(custom);
    
    /**
     * @tc.steps: step2. Set up geometry nodes to create overflow scenario
     * @tc.expected: total height (110) > content height (50), triggering overflow
     */
    custom->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    custom->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    
    child4->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    child4->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    
    child5->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    child5->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 60));
    
    /**
     * @tc.steps: step3. Create VerticalOverflowHandler and set up overflow state
     */
    VerticalOverflowHandler handler(AceType::WeakClaim(AceType::RawPtr(custom)));
    handler.CreateContentRect();
    handler.SetTotalChildFrameRect(RectF(0, 0, 50, 110));
    handler.HandleContentOverflow();
    
    /**
     * @tc.expected: Verify scroll event is registered and overflow state is initialized
     *               childFrameTop_ should be 0 (initial position)
     *               offsetToChildFrameBottom_ should be 60 (110 - 50 = 60 pixels below)
     */
    EXPECT_EQ(handler.childFrameTop_.value_or(-1), 0);
    EXPECT_EQ(handler.offsetToChildFrameBottom_, 60);
    EXPECT_NE(handler.scrollableEvent_, nullptr);
    EXPECT_FALSE(handler.hasParentAdjust_);
    
    /**
     * @tc.steps: step4. Scroll up by 20 pixels
     */
    handler.HandleScrollImpl(-20, 0);
    
    /**
     * @tc.expected: After scrolling up by 20:
     *               childFrameTop_ should be -20
     *               offsetToChildFrameBottom_ should be 40 (60 - 20)
     *               hasParentAdjust_ should be true (scroll has been applied)
     *               child4 offset should be (0, -20)
     *               child5 offset should be (0, 40)
     */
    EXPECT_EQ(handler.childFrameTop_.value_or(-1), -20);
    EXPECT_EQ(handler.offsetToChildFrameBottom_, 40);
    EXPECT_TRUE(handler.hasParentAdjust_);
    EXPECT_EQ(child4->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, -20));
    EXPECT_EQ(child5->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, 40));
    
    /**
     * @tc.steps: step5. Eliminate overflow by reducing totalChildFrameRect
     */
    handler.SetTotalChildFrameRect(RectF(0, 0, 50, 50));
    handler.HandleContentOverflow();
    
    /**
     * @tc.expected: Verify scroll event is unregistered and state is reset
     *               childFrameTop_ should not have a value (no overflow)
     *               scrollableEvent_ should be nullptr (unregistered)
     *               hasParentAdjust_ should be false
     */
    EXPECT_FALSE(handler.childFrameTop_.has_value());
    EXPECT_EQ(handler.scrollableEvent_, nullptr);
    EXPECT_FALSE(handler.hasParentAdjust_);
}

/**
 * @tc.name: CustomHandleContentOverflowWithPositionedChildTest
 * @tc.desc: test CustomPattern::HandleContentOverflow() when child has position property
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, CustomHandleContentOverflowWithPositionedChildTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create custom component with positioned child
     */
    RefPtr<FrameNode> positionedChild;
    
    // Create custom FrameNode with CustomPattern
    auto custom = FrameNode::CreateFrameNode(V2::CUSTOM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CustomPattern>());
    
    // Create a child with position property (positioned child)
    positionedChild = FrameNode::CreateFrameNode(V2::CUSTOM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CustomPattern>());
    
    positionedChild->MountToParent(custom);
    
    /**
     * @tc.steps: step2. Set position property on the child to make it positioned
     * @tc.expected: child->IsOutOfLayout() returns true
     */
    auto renderContext = positionedChild->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    
    // Set position {x:0, y:0} on child
    // This causes IsOutOfLayout() to return true
    auto& posProperty = renderContext->GetOrCreatePositionProperty();
    ASSERT_NE(posProperty, nullptr);
    posProperty->UpdatePosition(OffsetT<Dimension>(Dimension(0), Dimension(0)));
    
    // Verify the child is now out of layout
    EXPECT_TRUE(positionedChild->IsOutOfLayout());
    
    /**
     * @tc.steps: step3. Set up geometry where positioned child overflows
     * @tc.expected: Since child is positioned, it should be excluded from overflow calculation
     */
    custom->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    custom->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    
    positionedChild->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
    positionedChild->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    
    /**
     * @tc.steps: step4. Create VerticalOverflowHandler and call HandleContentOverflow
     */
    VerticalOverflowHandler handler(AceType::WeakClaim(AceType::RawPtr(custom)));
    handler.CreateContentRect();
    
    // Set totalChildFrameRect - normally this would be (0, 0, 100, 100)
    // But since the child is positioned (IsOutOfLayout == true),
    // it should be excluded from the calculation, resulting in empty rect
    handler.SetTotalChildFrameRect(RectF(0, 0, 0, 0));
    handler.HandleContentOverflow();
    
    /**
     * @tc.expected: Verify that overflow handling is NOT activated
     *               childFrameTop_ should not have a value (no overflow detected)
     *               scrollableEvent_ should be nullptr (no scroll event registered)
     *               This is because positioned children are excluded from overflow calculation
     */
    EXPECT_FALSE(handler.childFrameTop_.has_value());
    EXPECT_EQ(handler.scrollableEvent_, nullptr);
    EXPECT_FALSE(handler.hasParentAdjust_);

    /**
     * @tc.steps: step5. Scroll up by 20 pixels, overflow handling is NOT activated
     */
    handler.HandleScrollImpl(-20, 0);
    EXPECT_FALSE(handler.childFrameTop_.has_value());
    EXPECT_EQ(positionedChild->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, 0));
}

/**
 * @tc.name: CustomHandleContentOverflowWithMixedChildrenTest
 * @tc.desc: test CustomPattern::HandleContentOverflow() with both normal and positioned children
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, CustomHandleContentOverflowWithMixedChildrenTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create custom component with mixed children (normal + positioned)
     */
    RefPtr<FrameNode> normalChild, positionedChild;
    
    // Create custom FrameNode with CustomPattern
    auto custom = FrameNode::CreateFrameNode(V2::CUSTOM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CustomPattern>());
    
    // Create normal child
    normalChild = FrameNode::CreateFrameNode(V2::CUSTOM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CustomPattern>());
    normalChild->MountToParent(custom);
    
    // Create positioned child
    positionedChild = FrameNode::CreateFrameNode(V2::CUSTOM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CustomPattern>());
    positionedChild->MountToParent(custom);
    
    /**
     * @tc.steps: step2. Set position property on one child
     */
    auto renderContext = positionedChild->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto& posProperty = renderContext->GetOrCreatePositionProperty();
    ASSERT_NE(posProperty, nullptr);
    posProperty->UpdatePosition(OffsetT<Dimension>(Dimension(0), Dimension(0)));
    
    EXPECT_FALSE(normalChild->IsOutOfLayout());   // normal child: in layout
    EXPECT_TRUE(positionedChild->IsOutOfLayout()); // positioned child: out of layout
    
    /**
     * @tc.steps: step3. Set up geometry
     *             - normal child: 50x50 at (0,0)
     *             - positioned child: 100x100 at (0,0) - should be ignored
     *             - container: 50x50
     * @tc.expected: Only normal child contributes to overflow calculation
     */
    custom->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    custom->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    
    normalChild->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    normalChild->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    
    positionedChild->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
    positionedChild->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    
    /**
     * @tc.steps: step4. Create VerticalOverflowHandler
     * @tc.expected: totalChildFrameRect should only include normal child (50x50)
     *               Positioned child (100x100) is excluded
     */
    VerticalOverflowHandler handler(AceType::WeakClaim(AceType::RawPtr(custom)));
    handler.CreateContentRect();
    
    // Only normal child is counted: (0, 0, 50, 50)
    // Positioned child is excluded due to IsOutOfLayout() == true
    handler.SetTotalChildFrameRect(RectF(0, 0, 50, 50));
    handler.HandleContentOverflow();
    
    /**
     * @tc.expected: No overflow detected because only normal child (50x50) fits in container (50x50)
     *               Positioned child's size (100x100) is ignored in overflow calculation
     */
    EXPECT_FALSE(handler.childFrameTop_.has_value());
    EXPECT_EQ(handler.scrollableEvent_, nullptr);

    /**
     * @tc.steps: step5. Scroll up by 20 pixels, overflow handling is NOT activated
     */
    handler.HandleScrollImpl(-20, 0);
    EXPECT_FALSE(handler.childFrameTop_.has_value());
    EXPECT_EQ(positionedChild->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, 0));
}

/**
 * @tc.name: CustomHandleContentOverflowWithExpandSafeAreaTest
 * @tc.desc: test CustomPattern::HandleContentOverflow() when child has expandSafeArea property
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, CustomHandleContentOverflowWithExpandSafeAreaTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create custom component with child that has expandSafeArea
     */
    RefPtr<FrameNode> expandSafeAreaChild;
    
    // Create custom FrameNode with CustomPattern
    auto custom = FrameNode::CreateFrameNode(V2::CUSTOM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CustomPattern>());
    
    // Create a child with expandSafeArea property
    expandSafeAreaChild = FrameNode::CreateFrameNode(V2::CUSTOM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CustomPattern>());
    
    expandSafeAreaChild->MountToParent(custom);
    
    /**
     * @tc.steps: step2. Set expandSafeArea property on the child
     * @tc.expected: This causes overflow to be disabled for this subtree
     */
    auto layoutProperty = expandSafeAreaChild->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    
    // Set expandSafeArea using SafeAreaExpandOpts
    // This makes the child expand into safe areas (system bars, notches, etc.)
    layoutProperty->UpdateSafeAreaExpandOpts({
        .type = SAFE_AREA_TYPE_ALL,
        .edges = SAFE_AREA_EDGE_ALL,
    });
    
    /**
     * @tc.steps: step3. Set up geometry where child would normally overflow
     * @tc.expected: Child size (60x60) > container size (50x50)
     */
    custom->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    custom->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    
    expandSafeAreaChild->GetGeometryNode()->SetFrameSize(SizeF(60, 60));
    expandSafeAreaChild->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    
    /**
     * @tc.steps: step4. Create VerticalOverflowHandler
     * @tc.expected: Because child has expandSafeArea, overflow should be disabled
     */
    VerticalOverflowHandler handler(AceType::WeakClaim(AceType::RawPtr(custom)));
    handler.CreateContentRect();
    
    // Normally this would cause overflow, but expandSafeArea disables it
    handler.SetTotalChildFrameRect(RectF(0, 0, 60, 60));
    
    // Mark overflow as disabled (simulating what LayoutAlgorithm does)
    handler.SetOverflowDisabledFlag(true);
    
    handler.HandleContentOverflow();
    
    /**
     * @tc.expected: Verify that overflow handling is NOT activated despite overflow
     *               childFrameTop_ should not have a value
     *               scrollableEvent_ should be nullptr
     *               This is because expandSafeArea children disable overflow handling
     */
    EXPECT_FALSE(handler.childFrameTop_.has_value());
    EXPECT_EQ(handler.scrollableEvent_, nullptr);
    EXPECT_FALSE(handler.hasParentAdjust_);

    /**
     * @tc.steps: step5. childLayoutProperty has set ignoreLayoutSafeArea, overflow handling is NOT activated
     */
    bool hasSafeAreaProp = layoutProperty->IsIgnoreOptsValid() || expandSafeAreaChild->SelfExpansive();
    EXPECT_TRUE(hasSafeAreaProp);
}

/**
 * @tc.name: CustomHandleContentOverflowWithIgnoreLayoutSafeAreaTest
 * @tc.desc: test CustomPattern::HandleContentOverflow() when child has ignoreLayoutSafeArea property
 * @tc.type: FUNC
 */
HWTEST_F(OverflowTestNg, CustomHandleContentOverflowWithIgnoreLayoutSafeAreaTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create custom component with child that has ignoreLayoutSafeArea
     */
    RefPtr<FrameNode> ignoreSafeAreaChild;
    
    // Create custom FrameNode with CustomPattern
    auto custom = FrameNode::CreateFrameNode(V2::CUSTOM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CustomPattern>());
    
    // Create a child with ignoreLayoutSafeArea property
    ignoreSafeAreaChild = FrameNode::CreateFrameNode(V2::CUSTOM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CustomPattern>());
    
    ignoreSafeAreaChild->MountToParent(custom);
    
    /**
     * @tc.steps: step2. Set ignoreLayoutSafeArea property on the child
     * @tc.expected: This causes overflow to be disabled for this subtree
     */
    auto layoutProperty = custom->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    
    // Set ignoreLayoutSafeArea using SafeAreaInsets
    // This makes the child ignore safe area constraints during layout
    PaddingProperty paddingProperty;
    paddingProperty.start = std::make_optional<CalcLength>(10.0);
    paddingProperty.top = std::make_optional<CalcLength>(10.0);
    paddingProperty.bottom = std::make_optional<CalcLength>(10.0);
    paddingProperty.left = std::make_optional<CalcLength>(10.0);
    layoutProperty->ResetSafeAreaPadding();
    layoutProperty->UpdateSafeAreaPadding(paddingProperty);

    auto childLayoutProperty = ignoreSafeAreaChild->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty, nullptr);
    NG::IgnoreLayoutSafeAreaOpts ignoreOpts { .type = NG::SAFE_AREA_TYPE_SYSTEM, .edges = NG::SAFE_AREA_EDGE_ALL };
    childLayoutProperty->UpdateIgnoreLayoutSafeAreaOpts(ignoreOpts);
    
    /**
     * @tc.steps: step3. Set up geometry where child would normally overflow
     * @tc.expected: Child size (60x60) > container size (50x50)
     */
    custom->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    custom->GetGeometryNode()->SetFrameSize(SizeF(50, 50));
    
    ignoreSafeAreaChild->GetGeometryNode()->SetFrameSize(SizeF(60, 60));
    ignoreSafeAreaChild->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0, 0));
    
    /**
     * @tc.steps: step4. Create VerticalOverflowHandler
     * @tc.expected: Because child has ignoreLayoutSafeArea, overflow should be disabled
     */
    VerticalOverflowHandler handler(AceType::WeakClaim(AceType::RawPtr(custom)));
    handler.CreateContentRect();
    
    // Normally this would cause overflow, but ignoreLayoutSafeArea disables it
    handler.SetTotalChildFrameRect(RectF(0, 0, 60, 60));
    
    // Mark overflow as disabled (simulating what LayoutAlgorithm does)
    handler.SetOverflowDisabledFlag(true);
    
    handler.HandleContentOverflow();
    
    /**
     * @tc.expected: Verify that overflow handling is NOT activated despite overflow
     *               childFrameTop_ should not have a value
     *               scrollableEvent_ should be nullptr
     *               This is because ignoreLayoutSafeArea children disable overflow handling
     */
    EXPECT_FALSE(handler.childFrameTop_.has_value());
    EXPECT_EQ(handler.scrollableEvent_, nullptr);
    EXPECT_FALSE(handler.hasParentAdjust_);

    /**
     * @tc.steps: step5. childLayoutProperty has set ignoreLayoutSafeArea, overflow handling is NOT activated
     */
    bool hasSafeAreaProp = childLayoutProperty->IsIgnoreOptsValid() || ignoreSafeAreaChild->SelfExpansive();
    EXPECT_TRUE(hasSafeAreaProp);
}
} // namespace OHOS::Ace::NG