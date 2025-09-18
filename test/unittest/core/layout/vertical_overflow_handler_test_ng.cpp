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
#include "core/components_ng/layout/vertical_overflow_handler.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
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
    handler.scrollDistance_ = 0.0f;
    /**
     * @tc.expected: scrollDistance_ == 0 means we can only scroll up the child components.
     */
    EXPECT_TRUE(handler.OutOfBoundary(10.f));
    EXPECT_FALSE(handler.OutOfBoundary(-10.f));
    handler.scrollDistance_ = -50.0f;
    /**
     * @tc.expected: scrollDistance_ == -50.0f means we can scroll up or scroll down the child components.
     */
    EXPECT_FALSE(handler.OutOfBoundary(10.f));
    EXPECT_FALSE(handler.OutOfBoundary(-10.f));
    /**
     * @tc.expected: scrollDistance_ == contentRect——.Height() - totalChildFrameRect_.Height()
     *               means we can only scroll down the child components.
     */
    handler.scrollDistance_ = -200.0f;
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
    EXPECT_EQ(vOverflowHandler->scrollDistance_.value_or(-1), 0.f);
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
    EXPECT_EQ(vOverflowHandler->scrollDistance_.value_or(-1), -100.f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 0.0f);
    vOverflowHandler->SetTotalChildFrameRect(RectF(0.f, 100.f, 400.f, 200.f));
    vOverflowHandler->InitOffsetAfterLayout();
    /**
     * @tc.expected: when reaching the bottom boundary, we start to adjust the totalFrameRect's top edge
     */
    EXPECT_EQ(vOverflowHandler->scrollDistance_.value_or(-1), 0.f);
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
    EXPECT_EQ(vOverflowHandler->scrollDistance_.value_or(-1), -200.0f);
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
    EXPECT_EQ(vOverflowHandler->scrollDistance_.value_or(-1), 0.f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 100.0f);
    vOverflowHandler->SetTotalChildFrameRect(RectF(0.f, 100.f, 400.f, 200.f));
    vOverflowHandler->InitOffsetAfterLayout();
    /**
     * @tc.expected: when reaching the top boundary, we start to adjust the totalFrameRect's bottom edge
     */
    EXPECT_EQ(vOverflowHandler->scrollDistance_.value_or(-1), 0.f);
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
    EXPECT_EQ(vOverflowHandler->scrollDistance_.value_or(-1), -100.0f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 100.0f);
    vOverflowHandler->HandleScrollImpl(-200.0f, 0);
    /**
     * @tc.expected: when scrolling up by -200, we should clamp scrollDistance_ to avoid exceeding scrolling boundary
     *               the scrollDistance_ is equal to -200 and offsetToChildFrameBottom_ is equal to 0
     */
    EXPECT_EQ(vOverflowHandler->scrollDistance_.value_or(-1), -200.0f);
    EXPECT_EQ(vOverflowHandler->offsetToChildFrameBottom_, 0.0f);
    vOverflowHandler->HandleScrollImpl(300.0f, 0);
    /**
     * @tc.expected: when scrolling down by 300, we should clamp scrollDistance_ to avoid exceeding scrolling boundary
     *               the scrollDistance_ is equal to 0 and offsetToChildFrameBottom_ is equal to 0 + 400 - 200 = 200
     */
    EXPECT_EQ(vOverflowHandler->scrollDistance_.value_or(-1), 0.0f);
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
    EXPECT_EQ(handler.scrollDistance_.value_or(-1), 0);
    EXPECT_EQ(handler.offsetToChildFrameBottom_, 60);
    EXPECT_NE(handler.scrollableEvent_, nullptr);
    EXPECT_FALSE(handler.hasParentAdjust_);
    handler.HandleScrollImpl(-20, 0);
    /**
     * @tc.expected: After scrolling up by 20, scrollDistance == 20 and children have correct offset
     */
    EXPECT_EQ(handler.scrollDistance_.value_or(-1), -20);
    EXPECT_EQ(handler.offsetToChildFrameBottom_, 40);
    EXPECT_TRUE(handler.hasParentAdjust_);
    EXPECT_EQ(child4->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, -20));
    EXPECT_EQ(child5->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, 40));
    handler.SetTotalChildFrameRect(RectF(0, 0, 50, 50));
    handler.HandleContentOverflow();
     /**
     * @tc.expected: Unregister scrollEvent and reset
     */
    EXPECT_FALSE(handler.scrollDistance_.has_value());
    EXPECT_EQ(handler.scrollableEvent_, nullptr);
    EXPECT_FALSE(handler.hasParentAdjust_);
}
} // namespace OHOS::Ace::NG