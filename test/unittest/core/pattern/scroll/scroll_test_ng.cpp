/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "scroll_test_ng.h"

namespace OHOS::Ace::NG {
void ScrollTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto scrollBarTheme = AceType::MakeRefPtr<ScrollBarTheme>();
    scrollBarTheme->normalWidth_ = Dimension(NORMAL_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollBarTheme));
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void ScrollTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ScrollTestNg::SetUp() {}

void ScrollTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    scrollBar_ = nullptr;
}

void ScrollTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ScrollPattern>();
    eventHub_ = frameNode_->GetEventHub<ScrollEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ScrollLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ScrollAccessibilityProperty>();
}

void ScrollTestNg::Create(const std::function<void(ScrollModelNG)>& callback)
{
    ScrollModelNG model;
    model.Create();
    auto proxy = model.CreateScrollBarProxy();
    model.SetScrollBarProxy(proxy);
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void ScrollTestNg::CreateWithContent(const std::function<void(ScrollModelNG)>& callback, int32_t childNumber)
{
    Create([callback, childNumber](ScrollModelNG model) {
        if (callback) {
            callback(model);
        }
        CreateContent(childNumber);
    });
}

void ScrollTestNg::CreateSnapScroll(ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
    const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide)
{
    CreateWithContent(
        [scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide](ScrollModelNG model) {
            model.SetScrollSnap(scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide);
        }, SNAP_ITEM_NUMBER);
}

void ScrollTestNg::CreateContent(int32_t childNumber)
{
    if (GetAxis() == Axis::HORIZONTAL) {
        RowModelNG rowModel;
        rowModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(Dimension(childNumber * ITEM_WIDTH)));
        ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
        for (int32_t index = 0; index < childNumber; index++) {
            RowModelNG rowModel;
            rowModel.Create(Dimension(0), nullptr, "");
            ViewAbstract::SetWidth(CalcLength(Dimension(ITEM_WIDTH)));
            ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
            ViewStackProcessor::GetInstance()->Pop();
        }
    } else {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(Dimension(childNumber * ITEM_HEIGHT)));
        for (int32_t index = 0; index < childNumber; index++) {
            ColumnModelNG colModel;
            colModel.Create(Dimension(0), nullptr, "");
            ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
            ViewAbstract::SetHeight(CalcLength(Dimension(ITEM_HEIGHT)));
            ViewStackProcessor::GetInstance()->Pop();
        }
    }
    ViewStackProcessor::GetInstance()->Pop();
}

void ScrollTestNg::UpdateCurrentOffset(float offset)
{
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
}

RefPtr<FrameNode> ScrollTestNg::GetContentChild(int32_t index)
{
    auto content = GetChildFrameNode(frameNode_, 0);
    auto contentChild = GetChildFrameNode(content, index);
    return contentChild;
}

void ScrollTestNg::Touch(TouchLocationInfo locationInfo, SourceType sourceType)
{
    TouchEventInfo eventInfo("touch");
    eventInfo.SetSourceDevice(sourceType);
    eventInfo.AddTouchLocationInfo(std::move(locationInfo));
    auto touchEvent = pattern_->GetScrollBar()->touchEvent_->GetTouchEventCallback();
    touchEvent(eventInfo);
}

void ScrollTestNg::Touch(TouchType touchType, Offset offset, SourceType sourceType)
{
    TouchLocationInfo locationInfo(1);
    locationInfo.SetTouchType(touchType);
    locationInfo.SetLocalLocation(offset);
    Touch(locationInfo, sourceType);
}

void ScrollTestNg::Mouse(MouseInfo mouseInfo)
{
    auto mouseEventHub = frameNode_->GetOrCreateInputEventHub();
    RefPtr<InputEvent> inputEvent = mouseEventHub->mouseEventActuator_->inputEvents_.front();
    auto mouseEvent = inputEvent->GetOnMouseEventFunc();
    mouseEvent(mouseInfo);
}

void ScrollTestNg::Mouse(Offset moveOffset)
{
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::MOVE);
    mouseInfo.SetLocalLocation(moveOffset);
    Mouse(mouseInfo);
}

void ScrollTestNg::Hover(bool isHover)
{
    auto hoverEventHub = frameNode_->GetOrCreateInputEventHub();
    RefPtr<InputEvent> inputEvent = hoverEventHub->hoverEventActuator_->inputEvents_.front();
    auto hoverEvent = inputEvent->GetOnHoverEventFunc();
    hoverEvent(isHover);
}

bool ScrollTestNg::OnScrollCallback(float offset, int32_t source)
{
    bool result = pattern_->OnScrollCallback(offset, source);
    FlushLayoutTask(frameNode_);
    return result;
}

void ScrollTestNg::ScrollToEdge(ScrollEdgeType scrollEdgeType)
{
    pattern_->ScrollToEdge(scrollEdgeType, false);
    FlushLayoutTask(frameNode_);
}

void ScrollTestNg::ScrollTo(float offset)
{
    pattern_->ScrollTo(offset);
    FlushLayoutTask(frameNode_);
}

Axis ScrollTestNg::GetAxis()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty<ScrollLayoutProperty>();
    auto axis = layoutProperty->GetAxis();
    return axis.has_value() ? axis.value() : Axis::VERTICAL;
}

float ScrollTestNg::GetOffset(float childNumber)
{
    bool isHorizontal = pattern_->GetAxis() == Axis::HORIZONTAL;
    float offset = childNumber * (isHorizontal ? ITEM_WIDTH : ITEM_HEIGHT);
    return offset;
}

AssertionResult ScrollTestNg::UpdateAndVerifyPosition(float childNumber, float expectChildNumber, int32_t source)
{
    pattern_->UpdateCurrentOffset(GetOffset(childNumber), source);
    return IsEqualCurrentPosition(GetOffset(expectChildNumber));
}

AssertionResult ScrollTestNg::ScrollToNode(int32_t childIndex, float expectChildNumber)
{
    pattern_->ScrollToNode(GetContentChild(childIndex));
    return IsEqualCurrentPosition(GetOffset(expectChildNumber));
}

AssertionResult ScrollTestNg::IsEqualCurrentPosition(float expectOffset)
{
    FlushLayoutTask(frameNode_);
    float currentOffset = pattern_->GetCurrentPosition();
    return IsEqual(currentOffset, expectOffset);
}

/**
 * @tc.name: AttrScrollable001
 * @tc.desc: Test attribute about scrollable,
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, AttrScrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Text default value: VERTICAL
     */
    CreateWithContent();
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1));

    /**
     * @tc.steps: step2. Text set value: HORIZONTAL
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::HORIZONTAL); });
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1));

    /**
     * @tc.steps: step3. Text set value: NONE
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::NONE); });
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1));
}

/**
 * @tc.name: AttrEnableScrollInteraction001
 * @tc.desc: Test attribute about enableScrollInteraction,
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, AttrEnableScrollInteraction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test default value: true
     */
    CreateWithContent();
    EXPECT_TRUE(pattern_->GetScrollableEvent()->GetEnable());

    /**
     * @tc.steps: step2. Test set value: false
     */
    CreateWithContent([](ScrollModelNG model) { model.SetScrollEnabled(false); });
    EXPECT_FALSE(pattern_->GetScrollableEvent()->GetEnable());
}

/**
 * @tc.name: ScrollTest002
 * @tc.desc: When setting a fixed length and width, verify the related functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest002, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) {
        model.SetAxis(Axis::HORIZONTAL);
        model.SetDisplayMode(static_cast<int>(DisplayMode::OFF));
        auto scrollProxy = model.CreateScrollBarProxy();
        model.SetScrollBarProxy(scrollProxy);
    });

    /**
     * @tc.steps: step1. When Axis is HORIZONTAL, Verify the callback function registered in scrollBarProxy.
     * @tc.expected: Check whether the return value is as expected.
     */
    auto scrollBarProxy = pattern_->GetScrollBarProxy();
    EXPECT_FALSE(scrollBarProxy->scrollableNodes_.empty());
    bool ret = scrollBarProxy->scrollableNodes_.back().onPositionChanged(0.0, SCROLL_FROM_BAR);
    EXPECT_TRUE(ret);
    ret = scrollBarProxy->scrollableNodes_.back().onPositionChanged(0.0, SCROLL_FROM_START);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ScrollTest003
 * @tc.desc: When setting a fixed length and width, verify the related callback functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ScrollSpringEffect and call relevant callback functions.
     * @tc.expected: Check whether the return value is correct.
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, true); });
    EXPECT_EQ(pattern_->scrollableDistance_, VERTICAL_SCROLLABLE_DISTANCE);
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    auto springEffect = AceType::DynamicCast<ScrollSpringEffect>(scrollEdgeEffect);
    pattern_->currentOffset_ = 100.f;
    EXPECT_TRUE(springEffect->outBoundaryCallback_());
    auto currentPosition = scrollEdgeEffect->currentPositionCallback_();
    EXPECT_EQ(currentPosition, 100.0);

    /**
     * @tc.steps: step2. When direction is the default value, call the relevant callback function.
     * @tc.expected: Check whether the return value is correct.
     */
    auto leading = scrollEdgeEffect->leadingCallback_();
    auto trailing = scrollEdgeEffect->trailingCallback_();
    auto initLeading = scrollEdgeEffect->initLeadingCallback_();
    auto initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(leading, -VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(trailing, 0.0);
    EXPECT_EQ(initLeading, -VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(initTrailing, 0.0);

    /**
     * @tc.steps: step3. When direction is ROW_REVERSE, call the relevant callback function.
     * @tc.expected: Check whether the return value is correct.
     */
    pattern_->direction_ = FlexDirection::ROW_REVERSE;
    leading = scrollEdgeEffect->leadingCallback_();
    trailing = scrollEdgeEffect->trailingCallback_();
    initLeading = scrollEdgeEffect->initLeadingCallback_();
    initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(leading, 0.0);
    EXPECT_EQ(trailing, VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(initLeading, 0.0);
    EXPECT_EQ(initTrailing, VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step4. When direction is COLUMN_REVERSE, call the relevant callback function.
     * @tc.expected: Check whether the return value is correct.
     */
    pattern_->direction_ = FlexDirection::COLUMN_REVERSE;
    leading = scrollEdgeEffect->leadingCallback_();
    trailing = scrollEdgeEffect->trailingCallback_();
    initLeading = scrollEdgeEffect->initLeadingCallback_();
    initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(leading, 0.0);
    EXPECT_EQ(trailing, VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(initLeading, 0.0);
    EXPECT_EQ(initTrailing, VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step5. When direction is the default value and scrollableDistance_ <= 0.
     * @tc.expected: return 0.0
     */
    Create([](ScrollModelNG model) {
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        CreateContent(VIEW_LINE_NUMBER);
    });
    EXPECT_EQ(pattern_->scrollableDistance_, 0);
    scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    leading = scrollEdgeEffect->leadingCallback_();
    initLeading = scrollEdgeEffect->initLeadingCallback_();
    EXPECT_EQ(leading, 0.0);
    EXPECT_EQ(initLeading, 0.0);
}

/**
 * @tc.name: ScrollTest004
 * @tc.desc: When setting a fixed length and width, verify the related functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ScrollFadeEffect and call relevant callback functions.
     * @tc.expected: Check whether the return value is correct.
     */
    CreateWithContent();
    pattern_->SetEdgeEffect(EdgeEffect::FADE);
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    ASSERT_NE(scrollEdgeEffect, nullptr);
    pattern_->currentOffset_ = 100.f;
    pattern_->scrollableDistance_ = 100.f;
    auto scrollFade = AceType::DynamicCast<ScrollFadeEffect>(scrollEdgeEffect);
    ASSERT_NE(scrollFade, nullptr);
    scrollFade->handleOverScrollCallback_();
    ASSERT_NE(scrollFade->fadeController_, nullptr);
    pattern_->SetEdgeEffect(EdgeEffect::NONE);
    EXPECT_EQ(pattern_->scrollEffect_, nullptr);
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test UpdateCurrentOffset that return
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When unscrollable
     * @tc.expected: currentOffset would not change
     */
    Create();
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, 0, SCROLL_FROM_UPDATE));

    /**
     * @tc.steps: step2. When !HandleEdgeEffect and !IsOutOfBoundary
     * @tc.expected: currentOffset would not change
     */
    CreateWithContent();
    EXPECT_TRUE(UpdateAndVerifyPosition(1, 0, SCROLL_FROM_UPDATE));

    /**
     * @tc.steps: step3. When !HandleEdgeEffect and IsOutOfBoundary
     * @tc.expected: currentOffset would not change
     */
    CreateWithContent();
    pattern_->currentOffset_ = 10.f;
    EXPECT_TRUE(UpdateAndVerifyPosition(1, 0, SCROLL_FROM_UPDATE));
}

/**
 * @tc.name: UpdateCurrentOffset002
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, UpdateCurrentOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When Axis::VERTICAL
     */
    CreateWithContent();
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1, SCROLL_FROM_JUMP));
    EXPECT_TRUE(UpdateAndVerifyPosition(1, 0, SCROLL_FROM_BAR));
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1, SCROLL_FROM_ROTATE));
    EXPECT_TRUE(UpdateAndVerifyPosition(1, 0, SCROLL_FROM_ANIMATION));
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1, SCROLL_FROM_ANIMATION_SPRING));

    /**
     * @tc.steps: step2. When Axis::HORIZONTAL
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::HORIZONTAL); });
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1, SCROLL_FROM_JUMP));
    EXPECT_TRUE(UpdateAndVerifyPosition(1, 0, SCROLL_FROM_BAR));
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1, SCROLL_FROM_ROTATE));
    EXPECT_TRUE(UpdateAndVerifyPosition(1, 0, SCROLL_FROM_ANIMATION));
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1, SCROLL_FROM_ANIMATION_SPRING));

    /**
     * @tc.steps: step3. When EdgeEffect::SPRING, Test ValidateOffset
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, true); });
    EXPECT_FALSE(pattern_->IsRestrictBoundary());
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1, SCROLL_FROM_JUMP));
    EXPECT_TRUE(UpdateAndVerifyPosition(1, 0, SCROLL_FROM_BAR));
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1, SCROLL_FROM_BAR_FLING));
    EXPECT_TRUE(UpdateAndVerifyPosition(1, 0, SCROLL_FROM_ROTATE));

    pattern_->currentOffset_ = -10.f;
    pattern_->UpdateScrollBarOffset();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetScrollBarOutBoundaryExtent(), 0);

    pattern_->currentOffset_ = -1000.f;
    pattern_->UpdateScrollBarOffset();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetScrollBarOutBoundaryExtent(),
        -pattern_->currentOffset_ - (ITEM_HEIGHT * TOTAL_LINE_NUMBER - SCROLL_HEIGHT));

    pattern_->currentOffset_ = -100.f;
    pattern_->UpdateScrollBarOffset();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetScrollBarOutBoundaryExtent(), 0.0f);
}

/**
 * @tc.name: UpdateCurrentOffset003
 * @tc.desc: Test whether the isAnimateOverScroll_ can be set right.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, UpdateCurrentOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll model with spring edgeEffect.
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, true); });
    pattern_->isAnimationStop_ = false;

    /**
     * @tc.steps: step2. Make animateCanOverScroll_ true, UpdateCurrentOffset to a position where over the boundary.
     * @tc.expected: pattern_->isAnimateOverScroll_ can be set to true.
     */
    pattern_->animateCanOverScroll_ = true;
    pattern_->isAnimateOverScroll_ = false;
    pattern_->UpdateCurrentOffset(100, SCROLL_FROM_ANIMATION_CONTROLLER);
    EXPECT_EQ(pattern_->isAnimateOverScroll_, true);

    /**
     * @tc.steps: step3. Make animateCanOverScroll_ false, UpdateCurrentOffset to a position where over the boundary.
     * @tc.expected: pattern_->isAnimateOverScroll_ can't be set to true.
     */
    pattern_->animateCanOverScroll_ = false;
    pattern_->isAnimateOverScroll_ = false;
    pattern_->UpdateCurrentOffset(100, SCROLL_FROM_ANIMATION_CONTROLLER);
    EXPECT_EQ(pattern_->isAnimateOverScroll_, false);
}

/**
 * @tc.name: UpdateCurrentOffset004
 * @tc.desc: Test return value of UpdateCurrentOffset.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, UpdateCurrentOffset004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll model with spring edgeEffect.
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, true); });
    /**
     * @tc.steps: step2. Make animateCanOverScroll_ true, UpdateCurrentOffset to a position where over the boundary.
     * @tc.expected: the return value of UpdateCurrentOffset is true.
     */
    pattern_->animateCanOverScroll_ = true;
    EXPECT_EQ(pattern_->UpdateCurrentOffset(100, SCROLL_FROM_ANIMATION_CONTROLLER), true);

    /**
     * @tc.steps: step3. Make animateCanOverScroll_ false, UpdateCurrentOffset to a position where over the boundary.
     * @tc.expected: the return value of UpdateCurrentOffset is false.
     */
    pattern_->animateCanOverScroll_ = false;
    EXPECT_EQ(pattern_->UpdateCurrentOffset(100, SCROLL_FROM_ANIMATION_CONTROLLER), false);
}

/**
 * @tc.name: Measure001
 * @tc.desc: Test Measure
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Measure001, TestSize.Level1)
{
    ScrollModelNG model;
    model.Create();
    model.SetAxis(Axis::NONE);
    CreateContent();
    GetInstance();

    /**
     * @tc.steps: step1. Do not set idealSize
     * @tc.expected: The idealSize would be child size
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { SCROLL_WIDTH, SCROLL_HEIGHT };
    LayoutConstraint.percentReference = { SCROLL_WIDTH, SCROLL_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
    auto scrollSize = frameNode_->GetGeometryNode()->GetFrameSize();
    auto expectSize = SizeF(SCROLL_WIDTH, ITEM_HEIGHT * TOTAL_LINE_NUMBER);
    EXPECT_EQ(scrollSize, expectSize) << "scrollSize: " << scrollSize.ToString()
                                      << " expectSize: " << expectSize.ToString();
}

/**
 * @tc.name: Layout001
 * @tc.desc: Test Layout
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Layout001, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::NONE); });
    layoutProperty_->UpdateAlignment(Alignment::CENTER);
    FlushLayoutTask(frameNode_);
    auto col = frameNode_->GetChildAtIndex(0);
    auto colNode = AceType::DynamicCast<FrameNode>(col);
    auto colOffset = colNode->GetGeometryNode()->GetMarginFrameOffset();
    auto expectOffset = OffsetF(0, 0);
    EXPECT_EQ(colOffset, expectOffset) << "colOffset: " << colOffset.ToString()
                                       << " expectOffset: " << expectOffset.ToString();
}

/**
 * @tc.name: ScrollToNode001
 * @tc.desc: Test ScrollToNode
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollToNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ScrollToNode in VERTICAL
     * @tc.expected: currentOffset_ is correct
     */
    CreateWithContent();
    EXPECT_TRUE(ScrollToNode(5, 0));
    EXPECT_TRUE(ScrollToNode(8, -1));
    EXPECT_TRUE(ScrollToNode(9, -2));
    EXPECT_TRUE(ScrollToNode(5, -2));
    EXPECT_TRUE(ScrollToNode(0, 0));

    /**
     * @tc.steps: step2. ScrollToNode in HORIZONTAL
     * @tc.expected: currentOffset_ is correct
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::HORIZONTAL); });
    EXPECT_TRUE(ScrollToNode(5, 0));
    EXPECT_TRUE(ScrollToNode(8, -1));
    EXPECT_TRUE(ScrollToNode(9, -2));
    EXPECT_TRUE(ScrollToNode(5, -2));
    EXPECT_TRUE(ScrollToNode(0, 0));

    /**
     * @tc.steps: step1. ScrollToNode itSelf
     * @tc.expected: currentOffset_ is zero
     */
    CreateWithContent();
    pattern_->ScrollToNode(frameNode_);
    EXPECT_TRUE(IsEqualCurrentPosition(0));
    pattern_->ScrollToNode(GetChildFrameNode(frameNode_, 0));
    EXPECT_TRUE(IsEqualCurrentPosition(0));
}

/**
 * @tc.name: Pattern003
 * @tc.desc: Test HandleScrollBarOutBoundary
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Pattern003, TestSize.Level1)
{
    CreateWithContent();

    /**
     * @tc.steps: step1. When scrollBar is not OFF
     * @tc.expected: outBoundary_ would be set
     */
    pattern_->HandleScrollBarOutBoundary(100.f);
    auto scrollBar = pattern_->GetScrollBar();
    EXPECT_EQ(scrollBar->outBoundary_, 100.f);

    /**
     * @tc.steps: step1. When scrollBar is OFF
     * @tc.expected: outBoundary_ would not be set
     */
    scrollBar->displayMode_ = DisplayMode::OFF;
    pattern_->HandleScrollBarOutBoundary(200.f);
    EXPECT_EQ(scrollBar->outBoundary_, 100.f);
}

/**
 * @tc.name: Test001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Test001, TestSize.Level1)
{
    CreateWithContent();

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    OverScrollOffset expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->currentOffset_ = -ITEM_HEIGHT;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->currentOffset_ = -ITEM_HEIGHT * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->currentOffset_ = ITEM_HEIGHT;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { -ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->currentOffset_ = -ITEM_HEIGHT * 3;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { 0, ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test AccessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, AccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create unscrollable scroll, test SetSpecificSupportAction
     * @tc.expected: action is correct
     */
    Create();
    accessibilityProperty_->ResetSupportAction();
    EXPECT_EQ(GetActions(accessibilityProperty_), 0);

    /**
     * @tc.steps: step2. scroll is at top
     * @tc.expected: action is correct
     */
    CreateWithContent();
    accessibilityProperty_->ResetSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);

    /**
     * @tc.steps: step3. scroll to middle
     * @tc.expected: action is correct
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);

    /**
     * @tc.steps: step4. scroll to bottom
     * @tc.expected: action is correct
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);

    /**
     * @tc.steps: step6. test IsScrollable()
     * @tc.expected: return value is correct
     */
    CreateWithContent();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::NONE); });
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, OnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create to trigger OnModifyDone
     * @tc.expected: Has ScrollableEvent, has AccessibilityAction, set Axis::VERTICAL
     */
    CreateWithContent();
    ASSERT_NE(pattern_->GetScrollableEvent(), nullptr);
    ASSERT_NE(accessibilityProperty_->actionScrollForwardImpl_, nullptr);
    ASSERT_NE(accessibilityProperty_->actionScrollBackwardImpl_, nullptr);
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);

    /**
     * @tc.steps: step2. Change axis and trigger OnModifyDone
     * @tc.expected: Axis would be changed
     */
    layoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);

    /**
     * @tc.steps: step3. Change scrollSnapUpdate_ to true
     * @tc.expected: Will MarkDirtyNode
     */
    pattern_->scrollSnapUpdate_ = true;
    pattern_->OnModifyDone();
}

/**
 * @tc.name: Pattern002
 * @tc.desc: Test SetAccessibilityAction
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Pattern002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test SetAccessibilityAction with scrollable scroll
     * @tc.expected: Can trigger AnimateTo()
     */
    CreateWithContent();
    accessibilityProperty_->actionScrollForwardImpl_();
    ASSERT_NE(pattern_->springAnimation_, nullptr);
    pattern_->springAnimation_ = nullptr;
    accessibilityProperty_->actionScrollBackwardImpl_();
    ASSERT_NE(pattern_->springAnimation_, nullptr);

    /**
     * @tc.steps: step2. Test SetAccessibilityAction with unScrollable scroll, scrollableDistance_ <= 0
     * @tc.expected: Cannot trigger AnimateTo()
     */
    Create();
    accessibilityProperty_->actionScrollForwardImpl_();
    EXPECT_EQ(pattern_->animator_, nullptr);
    accessibilityProperty_->actionScrollBackwardImpl_();
    EXPECT_EQ(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step3. Test SetAccessibilityAction with unScrollable scroll, Axis::NONE
     * @tc.expected: Cannot trigger AnimateTo()
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::NONE); });
    accessibilityProperty_->actionScrollForwardImpl_();
    EXPECT_EQ(pattern_->animator_, nullptr);
    accessibilityProperty_->actionScrollBackwardImpl_();
    EXPECT_EQ(pattern_->animator_, nullptr);
}

/**
 * @tc.name: ScrollTest005
 * @tc.desc: Scroll Accessibility PerformAction test ScrollForward and ScrollBackward..
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties.
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::NONE); });

    /**
     * @tc.steps: step2. Get scroll frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    pattern_->scrollableDistance_ = 0.0;
    pattern_->SetAccessibilityAction();

    /**
     * @tc.steps: step4. When scroll is not scrollable and scrollable distance is 0, call the callback function in
     *                   accessibilityProperty_.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When scroll is not scrollable and scrollable distance is not 0, call the callback function in
     *                   accessibilityProperty_.
     * @tc.expected: Related function is called.
     */
    pattern_->scrollableDistance_ = 100.f;
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollBackward());

    /**
     * @tc.steps: step6. When scroll is scrollable and scrollable distance is not 0, call the callback function in
     *                   accessibilityProperty_.
     * @tc.expected: Related function is called.
     */
    pattern_->SetAxis(Axis::VERTICAL);
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollBackward());

    /**
     * @tc.steps: step7. When scroll is scrollable and scrollable distance is 0, call the callback function in
     *                   accessibilityProperty_.
     * @tc.expected: Related function is called.
     */
    pattern_->scrollableDistance_ = 0.0;
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollBackward());
}

/**
 * @tc.name: ScrollSetFrictionTest001
 * @tc.desc: Test SetFriction
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollSetFrictionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set friction less than 0
     * @tc.expected: should be more than 0.0,if out of range,should be default value.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    double friction = -1;
    ScrollModelNG scrollModelNG_1;
    scrollModelNG_1.Create();
    scrollModelNG_1.SetFriction(friction);
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), NEW_DEFAULT_FRICTION);

    /**
     * @tc.steps: step1. set friction more than 0
     * @tc.expected: friction should be more than 0.0,if out of range,should be default value.
     */
    friction = 10;
    ScrollModelNG scrollModelNG_2;
    scrollModelNG_2.Create();
    scrollModelNG_2.SetFriction(friction);
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), friction);
}

/**
 * @tc.name: Snap001
 * @tc.desc: Test snap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Snap001, TestSize.Level1)
{
    Dimension intervalSize = Dimension(10.f);
    std::vector<Dimension> snapPaginations = {
        Dimension(10.f),
        Dimension(20.f),
        Dimension(30.f),
    };

    // snapOffsets_: { 0.f, -10.f, -20.f, -30.f, -2200.f }
    std::pair<bool, bool> enableSnapToSide = { false, false };
    CreateSnapScroll(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(0.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-20.f).has_value());
    pattern_->currentOffset_ = -20.f;
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(0.f).has_value());

    pattern_->currentOffset_ = -10.f;
    EXPECT_TRUE(pattern_->NeedScrollSnapToSide(-10.f));
    EXPECT_FALSE(pattern_->NeedScrollSnapToSide(10.f));
    pattern_->currentOffset_ = -20.f;
    EXPECT_FALSE(pattern_->NeedScrollSnapToSide(0.f));

    enableSnapToSide = { true, false };
    CreateSnapScroll(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-40.f).has_value());
    pattern_->currentOffset_ = 20.f;
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-40.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(0.f).has_value());

    pattern_->currentOffset_ = -30.f;
    EXPECT_TRUE(pattern_->NeedScrollSnapToSide(10.f));
    EXPECT_FALSE(pattern_->NeedScrollSnapToSide(-10.f));
    pattern_->currentOffset_ = -20.f;
    EXPECT_FALSE(pattern_->NeedScrollSnapToSide(0.f));

    // snapOffsets_: { 0.f, -10.f, -20.f, -30.f, -40.f, ... , -180.f, -190.f, -200.f }
    snapPaginations = {};
    CreateSnapScroll(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(10.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-(SNAP_SCROLLABLE_DISTANCE + 10.f)).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-2.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-158.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-10.f).has_value());
}

/**
 * @tc.name: Snap002
 * @tc.desc: Test snap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Snap002, TestSize.Level1)
{
    Dimension intervalSize = Dimension(10.f / SCROLL_HEIGHT, DimensionUnit::PERCENT);
    std::vector<Dimension> snapPaginations = {
        Dimension(0.f, DimensionUnit::PERCENT),
        Dimension(10.f / SCROLL_HEIGHT, DimensionUnit::PERCENT),
        Dimension(20.f / SCROLL_HEIGHT, DimensionUnit::PERCENT),
        Dimension(30.f / SCROLL_HEIGHT, DimensionUnit::PERCENT),
        Dimension((VERTICAL_SCROLLABLE_DISTANCE + 10.f) / SCROLL_HEIGHT, DimensionUnit::PERCENT),
    };

    // snapOffsets_: { 0.f, -1205.f, -2200.f }
    std::pair<bool, bool> enableSnapToSide = { false, false };
    CreateSnapScroll(ScrollSnapAlign::CENTER, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(0.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-20.f).has_value());
    pattern_->currentOffset_ = -20.f;
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(0.f).has_value());

    enableSnapToSide = { true, false };
    CreateSnapScroll(ScrollSnapAlign::CENTER, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-40.f).has_value());
    pattern_->currentOffset_ = -1200.f;
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-40.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(0.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(0.f).value(), -5.f);

    // snapOffsets_: { 0.f, -5.f, -15.f, -25.f, -35.f, ... , -2185.f, -2195.f }
    snapPaginations = {};
    CreateSnapScroll(ScrollSnapAlign::CENTER, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(10.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-(SNAP_SCROLLABLE_DISTANCE + 10.f)).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-2.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-158.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-10.f).has_value());
}

/**
 * @tc.name: Snap003
 * @tc.desc: Test snap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Snap003, TestSize.Level1)
{
    Dimension intervalSize = Dimension(10.f);
    std::vector<Dimension> snapPaginations = {
        Dimension(10.f),
        Dimension(20.f),
        Dimension(30.f),
    };

    // snapOffsets_: { 0.f, -2200.f }
    std::pair<bool, bool> enableSnapToSide = { false, false };
    CreateSnapScroll(ScrollSnapAlign::END, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(0.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-20.f).has_value());
    pattern_->currentOffset_ = -20.f;
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(0.f).has_value());

    enableSnapToSide = { true, false };
    CreateSnapScroll(ScrollSnapAlign::END, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-40.f).has_value());
    pattern_->currentOffset_ = 20.f;
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-40.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(0.f).has_value());

    // snapOffsets_: { 0.f, -10.f, -20.f, -30.f, -40.f, ... , -180.f, -190.f, -200.f }
    snapPaginations = {};
    CreateSnapScroll(ScrollSnapAlign::END, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(10.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-(SNAP_SCROLLABLE_DISTANCE + 10.f)).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-2.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-158.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-10.f).has_value());
}

/**
 * @tc.name: CaleSnapOffsetsByPaginations001
 * @tc.desc: Test CaleSnapOffsetsByPaginations where the page size is lesser than the scroll size.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, CaleSnapOffsetsByPaginations001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init snapPaginations.
     */
    Dimension intervalSize = Dimension(0.f);
    std::vector<Dimension> snapPaginations = {
        Dimension(400.f),
        Dimension(800.f),
        Dimension(1400.f),
        Dimension(1600.f),
        Dimension(2200.f),
    };

    /**
     * @tc.steps: step2. EnableSnapToSide is { true, true } and SnapAlign is ScrollSnapAlign::START.
     * @tc.expected: SnapOffsets is correct.
     */
    // snapPaginations: { 400.f, 800.f, 1400.f, 1600.f, 2200.f }
    std::pair<bool, bool> enableSnapToSide = { true, true };
    CreateSnapScroll(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    pattern_->CaleSnapOffsets();
    auto snapOffsets = pattern_->GetSnapOffsets();
    std::vector<float> testSnapOffsets = { 0.f, -400.f, -800.f, -1400.f, -1600.f, -2200.f };
    EXPECT_TRUE(snapOffsets == testSnapOffsets);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-200.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-200.f).value(), -400.f);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-2000.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-2000.f).value(), -2200.f);

    /**
     * @tc.steps: step3. EnableSnapToSide is { false, false }.
     * @tc.expected: SnapOffsets is correct.
     */
    pattern_->SetEnableSnapToSide({ false, false });
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-200.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-2000.f).has_value());

    /**
     * @tc.steps: step4. EnableSnapToSide is { true, true } and SnapAlign is ScrollSnapAlign::CENTER.
     * @tc.expected: SnapOffsets is correct.
     */
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    pattern_->SetEnableSnapToSide({ true, true });
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollSnapAlign, ScrollSnapAlign::CENTER, host);
    pattern_->CaleSnapOffsets();
    snapOffsets = pattern_->GetSnapOffsets();
    testSnapOffsets = { 0.f, -200.f, -700.f, -1100.f, -1500.f, -2200.f };
    EXPECT_TRUE(snapOffsets == testSnapOffsets);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-99.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-99.f).value(), 0.f);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-1700.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-1700.f).value(), -1500.f);

    /**
     * @tc.steps: step5. EnableSnapToSide is { false, false }.
     * @tc.expected: SnapOffsets is correct.
     */
    pattern_->SetEnableSnapToSide({ false, false });
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-99.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-1700.f).has_value());

    /**
     * @tc.steps: step6. EnableSnapToSide is { true, true } and SnapAlign is ScrollSnapAlign::END.
     * @tc.expected: SnapOffsets is correct.
     */
    pattern_->SetEnableSnapToSide({ true, true });
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollSnapAlign, ScrollSnapAlign::END, host);
    pattern_->CaleSnapOffsets();
    snapOffsets = pattern_->GetSnapOffsets();
    testSnapOffsets = { 0.f, -600.f, -800.f, -1400.f, -2200.f };
    EXPECT_TRUE(snapOffsets == testSnapOffsets);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-300.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-300.f).value(), -600.f);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-1799.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-1799.f).value(), -1400.f);

    /**
     * @tc.steps: step7. EnableSnapToSide is { false, false }.
     * @tc.expected: SnapOffsets is correct.
     */
    pattern_->SetEnableSnapToSide({ false, false });
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-300.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-1799.f).has_value());
}

/**
 * @tc.name: CaleSnapOffsetsByPaginations002
 * @tc.desc: Test CaleSnapOffsetsByPaginations where the page size is greater than the scroll size.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, CaleSnapOffsetsByPaginations002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init snapPaginations.
     */
    Dimension intervalSize = Dimension(0.f);
    std::vector<Dimension> snapPaginations = {
        Dimension(1000.f),
        Dimension(1200.f),
        Dimension(2000.f),
    };

    /**
     * @tc.steps: step2. EnableSnapToSide is { true, true } and SnapAlign is ScrollSnapAlign::START.
     * @tc.expected: SnapOffsets is correct.
     */
    // snapPaginations: { 1000.f, 1200.f, 2000.f }
    std::pair<bool, bool> enableSnapToSide = { true, true };
    CreateSnapScroll(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    pattern_->CaleSnapOffsets();
    auto snapOffsets = pattern_->GetSnapOffsets();
    std::vector<float> testSnapOffsets = { 0.f, -1000.f, -1200.f, -2000.f, -2200.f };
    EXPECT_TRUE(snapOffsets == testSnapOffsets);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-500.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-500.f).value(), -1000.f);
    pattern_->currentOffset_ = -2000.f;
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-100.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-100.f).value(), -200.f);
    // The midpoint of -1200.f and -2000.f is -1600.f
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(400.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(400.f).value(), 0.f);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(401.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(401.f).value(), 800.f);

    /**
     * @tc.steps: step3. EnableSnapToSide is { false, false }.
     * @tc.expected: SnapOffsets is correct.
     */
    pattern_->SetEnableSnapToSide({ false, false });
    pattern_->currentOffset_ = -1900.f;
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-100.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-100.f).value(), -100.f);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-101.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(900.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(900.f).value(), 900.f);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(901.f).has_value());

    /**
     * @tc.steps: step4. EnableSnapToSide is { true, true } and SnapAlign is ScrollSnapAlign::CENTER.
     * @tc.expected: SnapOffsets is correct.
     */
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    pattern_->currentOffset_ = 0.f;
    pattern_->SetEnableSnapToSide({ true, true });
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollSnapAlign, ScrollSnapAlign::CENTER, host);
    pattern_->CaleSnapOffsets();
    snapOffsets = pattern_->GetSnapOffsets();
    testSnapOffsets = { 0.f, -100.f, -700.f, -1200.f, -2100.f, -2200.f };
    EXPECT_TRUE(snapOffsets == testSnapOffsets);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-49.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-49.f).value(), 0.f);
    pattern_->currentOffset_ = -2000.f;
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-100.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-100.f).value(), -100.f);
    // The midpoint of -1200.f and -2100.f is -1650.f
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(350.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(350.f).value(), -100.f);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(351.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(351.f).value(), 800.f);

    /**
     * @tc.steps: step5. EnableSnapToSide is { false, false }.
     * @tc.expected: SnapOffsets is correct.
     */
    pattern_->SetEnableSnapToSide({ false, false });
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-100.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-100.f).value(), -100.f);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-101.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(1900.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(1900.f).value(), 1900.f);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(1901.f).has_value());

    /**
     * @tc.steps: step6. EnableSnapToSide is { true, true } and SnapAlign is ScrollSnapAlign::END.
     * @tc.expected: SnapOffsets is correct.
     */
    pattern_->currentOffset_ = 0.f;
    pattern_->SetEnableSnapToSide({ true, true });
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollSnapAlign, ScrollSnapAlign::END, host);
    pattern_->CaleSnapOffsets();
    snapOffsets = pattern_->GetSnapOffsets();
    testSnapOffsets = { 0.f, -200.f, -400.f, -1200.f, -2200.f };
    EXPECT_TRUE(snapOffsets == testSnapOffsets);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-100.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-100.f).value(), -200.f);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-1200.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-1200.f).value(), -1200.f);
    pattern_->currentOffset_ = -300.f;
    // The midpoint of 0.f and -200.f is -100.f
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(200.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(200.f).value(), 100.f);
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(201.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(201.f).value(), 300.f);

    /**
     * @tc.steps: step7. EnableSnapToSide is { false, false }.
     * @tc.expected: SnapOffsets is correct.
     */
    pattern_->SetEnableSnapToSide({ false, false });
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(100.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(100.f).value(), 100.f);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(101.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-900.f).has_value());
    EXPECT_DOUBLE_EQ(pattern_->CalePredictSnapOffset(-900.f).value(), -900.f);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-901.f).has_value());
}

/**
 * @tc.name: Distributed001
 * @tc.desc: Test the distributed capability of Scroll.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Distributed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize Scroll node
     */
    CreateWithContent();

    // need dpi to be 1
    /**
     * @tc.steps: step2. get pattern .
     * @tc.expected: function ProvideRestoreInfo is called.
     */
    pattern_->currentOffset_ = 1.0f;
    std::string ret = pattern_->ProvideRestoreInfo();

    /**
     * @tc.steps: step3. function OnRestoreInfo is called.
     * @tc.expected: Passing JSON format.
     */
    pattern_->OnRestoreInfo(ret);
    EXPECT_DOUBLE_EQ(pattern_->currentOffset_, 1.0f);
}

/**
 * @tc.name: ScrollGetItemRect001
 * @tc.desc: Test Scroll GetItemRect function.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollGetItemRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize Scroll.
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::HORIZONTAL); });

    /**
     * @tc.steps: step2. Get invalid ScrollItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(-1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(1), Rect()));

    /**
     * @tc.steps: step3. Get valid ScrollItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(
        pattern_->GetItemRect(0), Rect(0, 0, TOTAL_LINE_NUMBER * ITEM_WIDTH, FILL_LENGTH.Value() * SCROLL_HEIGHT)));
}

/**
 * @tc.name: ScrollWidth001
 * @tc.desc: Test the usability of scroll width property and its get and set function.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll by calling CreateWithContent() and verify the scroll width property
     * of scroll layout property.
     * @tc.expected: Default value is ought to be false.
     */
    CreateWithContent();
    float scrollWidth = 150.0f;
    EXPECT_FALSE(layoutProperty_->GetScrollWidth().has_value());
    layoutProperty_->UpdateScrollWidth(scrollWidth);
    EXPECT_EQ(layoutProperty_->GetScrollWidth().value(), scrollWidth);
}

/**
 * @tc.name: SelectScroll001
 * @tc.desc: Test the flags of select scroll that determines whether it belong to or be modified by a select
 * and their get and set functions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, SelectScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll by calling CreateWithContent() and verify the default value of the flags
     * which inform whether the scroll belongs to or is modified by a select.
     * @tc.expected: Default value is ought to be false.
     */
    CreateWithContent();
    EXPECT_FALSE(pattern_->IsWidthModifiedBySelect());
    EXPECT_FALSE(pattern_->IsSelectScroll());
    /**
     * @tc.steps: step2. Set both flags to be true and verify the usability of their get and set functions in
     * select pattern.
     * @tc.expected: After setting the value should be true.
     */
    pattern_->SetIsWidthModifiedBySelect(true);
    pattern_->SetIsSelectScroll(true);
    EXPECT_TRUE(pattern_->IsWidthModifiedBySelect());
    EXPECT_TRUE(pattern_->IsSelectScroll());
}

/**
 * @tc.name: Measure002
 * @tc.desc: Test ScrollLayoutAlgorithm Measure when the scroll belongs to a select.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Measure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll model and set the width, height, axis of the scroll, create the content of
     * the scroll and get its instance.
     * @tc.expected: Objects are created successfully.
     */
    CreateWithContent();
    ScrollModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    model.SetAxis(Axis::NONE);
    CreateContent();
    GetInstance();

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    pattern_->SetIsSelectScroll(true);
    FlushLayoutTask(frameNode_);
    layoutWrapper->MountToHostOnMainThread();

    RefPtr<GridColumnInfo> columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    columnInfo->GetParent()->BuildColumnWidth();
    auto defaultWidth = static_cast<float>(columnInfo->GetWidth(2));
    auto scrollSize = frameNode_->GetGeometryNode()->GetFrameSize();
    auto expectSize = SizeF(defaultWidth, ITEM_HEIGHT * TOTAL_LINE_NUMBER);
    EXPECT_NE(scrollSize, expectSize) << "scrollSize: " << scrollSize.ToString()
                                      << " expectSize: " << expectSize.ToString();
}

/**
 * @tc.name: Measure003
 * @tc.desc: Test ScrollLayoutAlgorithm Measure.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Measure003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll without children
     */
    Create();
    auto scrollSize = frameNode_->GetGeometryNode()->GetFrameSize();
    auto expectSize = SizeF(SCROLL_WIDTH, SCROLL_HEIGHT);
    EXPECT_TRUE(IsEqual(scrollSize, expectSize));

    /**
     * @tc.steps: step1. set idealSize
     * @tc.expected: The frameSize would be idealSize
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(300.f));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(500.f));
    FlushLayoutTask(frameNode_);

    scrollSize = frameNode_->GetGeometryNode()->GetFrameSize();
    expectSize = SizeF(300.f, 500.f);
    EXPECT_TRUE(IsEqual(scrollSize, expectSize));
}

/**
 * @tc.name: SelectScroll002
 * @tc.desc: Test select scroll default width.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, SelectScroll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the width of select scroll without setting it, this case is meant to test the correctness
     * of its default value.
     * @tc.expected: Default width of select scroll should be 0.0.
     */
    CreateWithContent();
    ASSERT_NE(pattern_, nullptr);
    auto ScrollWidth = pattern_->GetSelectScrollWidth();
    ASSERT_NE(ScrollWidth, 0.0);
}

/**
 * @tc.name: EnablePaging001
 * @tc.desc: Test enablePaging
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, EnablePaging001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties.
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEnablePaging(true); });
    auto viewPortLength = pattern_->GetMainContentSize();
    pattern_->scrollableDistance_ = viewPortLength * 10;
    pattern_->currentOffset_ = -viewPortLength * 5 - 10.0f;
    SizeF viewPortExtent(SCROLL_WIDTH, viewPortLength * 11);
    pattern_->viewPortExtent_ = viewPortExtent;
    pattern_->SetIntervalSize(Dimension(static_cast<double>(viewPortLength)));
    pattern_->CaleSnapOffsets();

    /**
     * @tc.steps: step2. dragDistance and dragSpeed less than threshold
     * @tc.expected: predictSnapOffset.value() less than 0
     */
    auto dragDistance = viewPortLength * 0.5 - 1;
    auto dragSpeed = SCROLL_PAGING_SPEED_THRESHOLD - 1;
    auto predictSnapOffset = pattern_->CalePredictSnapOffset(0.f, dragDistance, dragSpeed);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_LT(predictSnapOffset.value(), 0);

    /**
     * @tc.steps: step3. dragDistance and dragSpeed larger than threshold
     * @tc.expected: the absolute value of predictSnapOffset.value() less than viewPortLength
     */
    dragDistance = viewPortLength * 0.5 * 5;
    dragSpeed = SCROLL_PAGING_SPEED_THRESHOLD * 5;
    predictSnapOffset = pattern_->CalePredictSnapOffset(0.f, dragDistance, dragSpeed);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_LT(abs(predictSnapOffset.value()), viewPortLength);
    EXPECT_GT(predictSnapOffset.value(), 0);

    /**
     * @tc.steps: step4. dragDistance equals threshold and dragSpeed less than threshold
     * @tc.expected: the absolute value of predictSnapOffset.value() less than viewPortLength
     */
    dragDistance = viewPortLength * 0.5;
    dragSpeed = SCROLL_PAGING_SPEED_THRESHOLD - 1;
    predictSnapOffset = pattern_->CalePredictSnapOffset(0.f, dragDistance, dragSpeed);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_LT(abs(predictSnapOffset.value()), viewPortLength);
    EXPECT_GT(predictSnapOffset.value(), 0);

    /**
     * @tc.steps: step5. dragDistance less than threshold and dragSpeed equals threshold
     * @tc.expected: the absolute value of predictSnapOffset.value() less than viewPortLength
     */
    dragDistance = viewPortLength * 0.5 - 1;
    dragSpeed = SCROLL_PAGING_SPEED_THRESHOLD;
    predictSnapOffset = pattern_->CalePredictSnapOffset(0.f, dragDistance, dragSpeed);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_LT(abs(predictSnapOffset.value()), viewPortLength);
    EXPECT_GT(predictSnapOffset.value(), 0);
}

/**
 * @tc.name: EnablePaging002
 * @tc.desc: Test enablePaging
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, EnablePaging002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and set enablePaging.
     * @tc.expected: the value of GetEnablePaging() is VALID
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEnablePaging(true); });
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::VALID);

    /**
     * @tc.steps: step2. Create scroll, first set enablePaging and than set snap.
     * @tc.expected: the value of GetEnablePaging() is INVALID
     */
    Dimension intervalSize = Dimension(10.f);
    std::vector<Dimension> snapPaginations = {
        Dimension(10.f),
        Dimension(20.f),
        Dimension(30.f),
    };
    std::pair<bool, bool> enableSnapToSide = { false, false };
    auto scrollSnapAlign = ScrollSnapAlign::START;
    CreateWithContent([scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide](ScrollModelNG model) {
        model.SetEnablePaging(true);
        model.SetScrollSnap(scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide);
    });
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::INVALID);

    /**
     * @tc.steps: step3. Create scroll, first set snap and than set enablePaging.
     * @tc.expected: the value of GetEnablePaging() is INVALID
     */
    CreateWithContent([scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide](ScrollModelNG model) {
        model.SetScrollSnap(scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide);
        model.SetEnablePaging(true);
    });
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::INVALID);

    /**
     * @tc.steps: step4. Create scroll, set enablePaging true and than set enablePaging false.
     * @tc.expected: the value of GetEnablePaging() is NONE
     */
    CreateWithContent([](ScrollModelNG model) {
        model.SetEnablePaging(true);
        model.SetEnablePaging(false);
    });
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::NONE);

    /**
     * @tc.steps: step5. Create scroll, set enablePaging false and than set enablePaging true.
     * @tc.expected: the value of GetEnablePaging() is VALID
     */
    CreateWithContent([](ScrollModelNG model) {
        model.SetEnablePaging(false);
        model.SetEnablePaging(true);
    });
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::VALID);
}

/**
 * @tc.name: InitialOffset001
 * @tc.desc: Test initialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, InitialOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll.
     * @tc.expected: the value of currentOffset_ is 0
     */
    CreateWithContent([](ScrollModelNG model) {});
    EXPECT_EQ(pattern_->currentOffset_, 0.f);

    /**
     * @tc.steps: step2. Create scroll and set initialOffset ITEM_HEIGHT.
     * @tc.expected: the value of currentOffset_ is -ITEM_HEIGHT
     */
    CreateWithContent([](ScrollModelNG model) {
        model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(ITEM_HEIGHT)));
    });
    EXPECT_EQ(pattern_->currentOffset_, -ITEM_HEIGHT);

    /**
     * @tc.steps: step3. Create scroll , set axis HORIZONTAL and set initialOffset ITEM_HEIGHT.
     * @tc.expected: the value of currentOffset_ is -ITEM_WIDTH
     */
    CreateWithContent([](ScrollModelNG model) {
        model.SetInitialOffset(OffsetT(CalcDimension(ITEM_WIDTH), CalcDimension(0.f)));
        model.SetAxis(Axis::HORIZONTAL);
    });
    EXPECT_EQ(pattern_->currentOffset_, - ITEM_WIDTH);

    /**
     * @tc.steps: step4. Create scroll , set initialOffset 10%.
     * @tc.expected: the value of currentOffset_ is -ITEM_WIDTH
     */
    CreateWithContent([](ScrollModelNG model) {
        auto offset = Dimension(0.1, DimensionUnit::PERCENT);
        model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(offset)));
    });
    EXPECT_EQ(pattern_->currentOffset_, - SCROLL_HEIGHT * 0.1f);

    /**
     * @tc.steps: step5. Create scroll , set axis HORIZONTAL and set initialOffset 10%.
     * @tc.expected: the value of currentOffset_ is -ITEM_WIDTH
     */
    CreateWithContent([](ScrollModelNG model) {
        auto offset = Dimension(0.1, DimensionUnit::PERCENT);
        model.SetInitialOffset(OffsetT(CalcDimension(offset), CalcDimension(0.f)));
        model.SetAxis(Axis::HORIZONTAL);
    });
    EXPECT_EQ(pattern_->currentOffset_, - SCROLL_WIDTH * 0.1f);
}

/**
 * @tc.name: InitialOffset002
 * @tc.desc: Test initialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, InitialOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and set initialOffset 2*ITEM_HEIGHT.
     * @tc.expected: the value of currentOffset_ is -2*ITEM_HEIGHT
     */
    CreateWithContent([](ScrollModelNG model) {
        model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(2 * ITEM_HEIGHT)));
    });
    EXPECT_EQ(pattern_->currentOffset_, - 2 * ITEM_HEIGHT);

    /**
     * @tc.steps: step2. Create scroll and set initialOffset 3*ITEM_HEIGHT.
     * @tc.expected: the value of currentOffset_ is -2*ITEM_HEIGHT
     */
    CreateWithContent([](ScrollModelNG model) {
        model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(3 * ITEM_HEIGHT)));
    });
    EXPECT_EQ(pattern_->currentOffset_, - 2 * ITEM_HEIGHT);

    /**
     * @tc.steps: step3. Create scroll and set initialOffset -ITEM_HEIGHT.
     * @tc.expected: the value of currentOffset_ is 0
     */
    CreateWithContent([](ScrollModelNG model) {
        model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(- ITEM_HEIGHT)));
    });
    EXPECT_EQ(pattern_->currentOffset_, 0.f);

    /**
     * @tc.steps: step4. Create scroll , set initialOffset 100%.
     * @tc.expected: the value of currentOffset_ is -2*ITEM_WIDTH
     */
    CreateWithContent([](ScrollModelNG model) {
        auto offset = Dimension(100, DimensionUnit::PERCENT);
        model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(offset)));
    });
    EXPECT_EQ(pattern_->currentOffset_, - 2 * ITEM_HEIGHT);
}
} // namespace OHOS::Ace::NG
