/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <memory>
#include <utility>

#include "gtest/gtest-test-part.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/animation/animator.h"
#include "core/components/common/properties/color.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_paint_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float ROOT_WIDTH = 720.0f;
constexpr float ROOT_HEIGHT = 1136.0f;
constexpr Dimension FILL_LENGTH = Dimension(1.0, DimensionUnit::PERCENT);
constexpr int32_t VIEWPORT_CHILD_NUMBER = 10;
constexpr float COLUMN_CHILD_WIDTH = ROOT_WIDTH / VIEWPORT_CHILD_NUMBER;
constexpr float COLUMN_CHILD_HEIGHT = ROOT_HEIGHT / VIEWPORT_CHILD_NUMBER;
constexpr int32_t CHILD_NUMBER = 12;
constexpr float COLUMN_WIDTH = COLUMN_CHILD_WIDTH * CHILD_NUMBER;
constexpr float COLUMN_HEIGHT = COLUMN_CHILD_HEIGHT * CHILD_NUMBER;
constexpr int32_t BAR_EXPAND_DURATION = 150; // 150ms, scroll bar width expands from 4dp to 8dp
constexpr int32_t BAR_SHRINK_DURATION = 250; // 250ms, scroll bar width shrinks from 8dp to 4dp
const static int32_t PLATFORM_VERSION_TEN = 10;
} // namespace

class ScrollTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    static void SetWidth(const Dimension& width);
    static void SetHeight(const Dimension& height);
    RefPtr<LayoutWrapper> CreateScroll(Axis axis = Axis::VERTICAL);
    RefPtr<LayoutWrapper> CreateScroll(NG::DisplayMode displayMode);
    RefPtr<LayoutWrapper> CreateScroll(Color color);
    RefPtr<LayoutWrapper> CreateScroll(Dimension barWidth, Axis axis = Axis::VERTICAL);
    RefPtr<LayoutWrapper> CreateScroll(EdgeEffect edgeEffect);
    RefPtr<LayoutWrapper> CreateScroll(Axis axis, NG::ScrollEvent&& event);
    RefPtr<LayoutWrapper> CreateScroll(Axis axis, NG::ScrollEdgeEvent&& event);
    RefPtr<LayoutWrapper> CreateScroll(Axis axis, OnScrollStartEvent&& event);
    RefPtr<LayoutWrapper> CreateScroll(bool isScrollEnabled);
    void CreateContent(Axis axis = Axis::VERTICAL);
    RefPtr<LayoutWrapper> RunMeasureAndLayout(float width = ROOT_WIDTH, float height = ROOT_HEIGHT);
    RefPtr<FrameNode> GetContentChild(int32_t index);
    void Touch(TouchLocationInfo locationInfo, SourceType sourceType);
    void Touch(TouchType touchType, Offset offset, SourceType sourceType);
    void Mouse(MouseInfo mouseInfo);
    void Mouse(Offset moveOffset);
    RefPtr<FrameNode> GetColumnChild(int32_t index);
    void UpdateCurrentOffset(float offset);
    uint64_t GetActions();
    testing::AssertionResult IsEqualCurrentOffset(Offset expectOffset);
    testing::AssertionResult IsEqualOverScrollOffset(OverScrollOffset offset, OverScrollOffset expectOffset);
    testing::AssertionResult IsEqualRect(Rect rect, Rect expectRect);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ScrollPattern> pattern_;
    RefPtr<ScrollEventHub> eventHub_;
    RefPtr<ScrollLayoutProperty> layoutProperty_;
    RefPtr<ScrollPaintProperty> paintProperty_;
    RefPtr<ScrollAccessibilityProperty> accessibilityProperty_;
};

void ScrollTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto scrollBarTheme = AceType::MakeRefPtr<ScrollBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollBarTheme));
}

void ScrollTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
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
}

void ScrollTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ScrollPattern>();
    eventHub_ = frameNode_->GetEventHub<ScrollEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ScrollLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ScrollPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ScrollAccessibilityProperty>();
}

void ScrollTestNg::SetWidth(const Dimension& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
}

void ScrollTestNg::SetHeight(const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
}

RefPtr<LayoutWrapper> ScrollTestNg::CreateScroll(Axis axis)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(axis);
    CreateContent(axis);
    GetInstance();
    return RunMeasureAndLayout();
}

RefPtr<LayoutWrapper> ScrollTestNg::CreateScroll(NG::DisplayMode displayMode)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetDisplayMode(static_cast<int>(displayMode));
    CreateContent();
    GetInstance();
    return RunMeasureAndLayout();
}

RefPtr<LayoutWrapper> ScrollTestNg::CreateScroll(Color color)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetScrollBarColor(color);
    CreateContent();
    GetInstance();
    return RunMeasureAndLayout();
}

RefPtr<LayoutWrapper> ScrollTestNg::CreateScroll(Dimension barWidth, Axis axis)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(axis);
    scrollModel.SetScrollBarWidth(barWidth);
    CreateContent(axis);
    GetInstance();
    return RunMeasureAndLayout();
}

RefPtr<LayoutWrapper> ScrollTestNg::CreateScroll(EdgeEffect edgeEffect)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetEdgeEffect(edgeEffect);
    CreateContent();
    GetInstance();
    return RunMeasureAndLayout();
}

RefPtr<LayoutWrapper> ScrollTestNg::CreateScroll(Axis axis, NG::ScrollEvent&& event)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(axis);
    scrollModel.SetOnScroll(std::move(event));
    CreateContent(axis);
    GetInstance();
    return RunMeasureAndLayout();
}

RefPtr<LayoutWrapper> ScrollTestNg::CreateScroll(Axis axis, NG::ScrollEdgeEvent&& event)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(axis);
    scrollModel.SetOnScrollEdge(std::move(event));
    CreateContent(axis);
    GetInstance();
    return RunMeasureAndLayout();
}

RefPtr<LayoutWrapper> ScrollTestNg::CreateScroll(Axis axis, OnScrollStartEvent&& event)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(axis);
    scrollModel.SetOnScrollStart(std::move(event));
    scrollModel.SetOnScrollStop(std::move(event));
    scrollModel.SetOnScrollEnd(std::move(event));
    CreateContent(axis);
    GetInstance();
    return RunMeasureAndLayout();
}

RefPtr<LayoutWrapper> ScrollTestNg::CreateScroll(bool isScrollEnabled)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetScrollEnabled(isScrollEnabled);
    CreateContent();
    GetInstance();
    return RunMeasureAndLayout();
}

void ScrollTestNg::CreateContent(Axis axis)
{
    if (axis == Axis::HORIZONTAL) {
        RowModelNG rowModelNG;
        rowModelNG.Create(Dimension(0), nullptr, "");
        SetWidth(Dimension(COLUMN_WIDTH));
        SetHeight(FILL_LENGTH);
        for (int32_t index = 0; index < CHILD_NUMBER; index++) {
            RowModelNG rowModelNG;
            rowModelNG.Create(Dimension(0), nullptr, "");
            SetWidth(Dimension(COLUMN_CHILD_WIDTH));
            SetHeight(FILL_LENGTH);
            ViewStackProcessor::GetInstance()->Pop();
        }
    } else {
        ColumnModelNG columnModel;
        columnModel.Create(Dimension(0), nullptr, "");
        SetWidth(FILL_LENGTH);
        SetHeight(Dimension(COLUMN_HEIGHT));
        for (int32_t index = 0; index < CHILD_NUMBER; index++) {
            ColumnModelNG columnModel;
            columnModel.Create(Dimension(0), nullptr, "");
            SetWidth(FILL_LENGTH);
            SetHeight(Dimension(COLUMN_CHILD_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
        }
    }
    ViewStackProcessor::GetInstance()->Pop();
}

RefPtr<LayoutWrapper> ScrollTestNg::RunMeasureAndLayout(float width, float height)
{
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { ROOT_WIDTH, ROOT_HEIGHT };
    LayoutConstraint.percentReference = { ROOT_WIDTH, ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { width, height };
    LayoutConstraint.maxSize = { width, height };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
    return layoutWrapper;
}

void ScrollTestNg::UpdateCurrentOffset(float offset)
{
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
}

uint64_t ScrollTestNg::GetActions()
{
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    return actions;
}

RefPtr<FrameNode> ScrollTestNg::GetContentChild(int32_t index)
{
    auto content = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto contentChild = AceType::DynamicCast<FrameNode>(content->GetChildAtIndex(index));
    return contentChild;
}

void ScrollTestNg::Touch(TouchLocationInfo locationInfo, SourceType sourceType)
{
    auto touchEventHub = frameNode_->GetOrCreateGestureEventHub();
    RefPtr<TouchEventImpl> touchEventImpl = touchEventHub->touchEventActuator_->touchEvents_.front();
    auto touchEvent = touchEventImpl->GetTouchEventCallback();
    TouchEventInfo eventInfo("touch");
    eventInfo.SetSourceDevice(sourceType);
    eventInfo.AddTouchLocationInfo(std::move(locationInfo));
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

testing::AssertionResult ScrollTestNg::IsEqualCurrentOffset(Offset expectOffset)
{
    RunMeasureAndLayout();
    Offset currentOffset = pattern_->GetCurrentOffset();
    if (expectOffset == currentOffset) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "GetCurrentOffset(): " << currentOffset.ToString() << " != "
                                       << "expectOffset: " << expectOffset.ToString();
}

testing::AssertionResult ScrollTestNg::IsEqualOverScrollOffset(OverScrollOffset offset, OverScrollOffset expectOffset)
{
    if (NearEqual(offset.start, expectOffset.start) && NearEqual(offset.end, expectOffset.end)) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "offset: "
                                       << "{ " << offset.start << " , " << offset.end << " }"
                                       << " != "
                                       << "expectOffset: "
                                       << "{ " << expectOffset.start << " , " << expectOffset.end << " }";
}

testing::AssertionResult ScrollTestNg::IsEqualRect(Rect rect, Rect expectRect)
{
    if (rect == expectRect) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "rect: " << rect.ToString() << " != "
                                       << "expectRect: " << expectRect.ToString();
}

/**
 * @tc.name: AttrScrollable001
 * @tc.desc: Test attribute about scrollable,
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, AttrScrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Text default value: Vertical
     */
    CreateScroll();
    const float delta = -100.f;
    UpdateCurrentOffset(delta);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, delta)));

    /**
     * @tc.steps: step2. Text set value: Horizontal
     */
    CreateScroll(Axis::HORIZONTAL);
    UpdateCurrentOffset(delta);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(delta, 0)));

    /**
     * @tc.steps: step3. Text set value: None
     */
    CreateScroll(Axis::NONE);
    UpdateCurrentOffset(delta);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, delta)));
}

/**
 * @tc.name: AttrScrollBar001
 * @tc.desc: Test attribute about scrollBar,
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, AttrScrollBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Text default value: Auto
     */
    CreateScroll();
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Auto");

    /**
     * @tc.steps: step2. Text set value: Off
     */
    CreateScroll(NG::DisplayMode::OFF);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Off");

    /**
     * @tc.steps: step3. Text set value: On
     */
    CreateScroll(NG::DisplayMode::ON);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.On");
}

/**
 * @tc.name: AttrScrollBarColorWidth001
 * @tc.desc: Test attribute about scrollBarColor/scrollBarWidth,
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, AttrScrollBarColorWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Text default value:[color:foregroundColor_, width: 4]
     */
    CreateScroll();
    auto themeManager = MockPipelineBase::GetCurrent()->GetThemeManager();
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    EXPECT_EQ(paintProperty_->GetBarColor(), scrollBarTheme->GetForegroundColor());
    EXPECT_EQ(paintProperty_->GetBarWidth(), scrollBarTheme->GetNormalWidth());

    /**
     * @tc.steps: step2. Text set value: Color::RED
     */
    CreateScroll(Color::RED);
    EXPECT_EQ(paintProperty_->GetBarColor(), Color::RED);

    /**
     * @tc.steps: step3. Text set width value
     */
    CreateScroll(Dimension(10));
    EXPECT_EQ(paintProperty_->GetBarWidth(), Dimension(10));
}

/**
 * @tc.name: AttrEdgeEffect001
 * @tc.desc: Test attribute about edgeEffect,
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, AttrEdgeEffect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Text default value: None
     */
    CreateScroll();
    EXPECT_EQ(layoutProperty_->GetEdgeEffectValue(), EdgeEffect::NONE);

    /**
     * @tc.steps: step2. Text set value: SPRING
     */
    CreateScroll(EdgeEffect::SPRING);
    EXPECT_EQ(layoutProperty_->GetEdgeEffectValue(), EdgeEffect::SPRING);

    /**
     * @tc.steps: step3. Text set value: SPRING
     */
    CreateScroll(EdgeEffect::FADE);
    EXPECT_EQ(layoutProperty_->GetEdgeEffectValue(), EdgeEffect::FADE);
}

/**
 * @tc.name: AttrEnableScrollInteraction001
 * @tc.desc: Test attribute about enableScrollInteraction,
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, AttrEnableScrollInteraction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test set value: true
     */
    CreateScroll(true);
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), true);

    const float delta = -100.f;
    UpdateCurrentOffset(delta);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, delta)));

    /**
     * @tc.steps: step2. Test set value: false
     */
    CreateScroll(false);
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), false);

    UpdateCurrentOffset(delta);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, delta)));
}

/**
 * @tc.name: Event001
 * @tc.desc: Test RegisterScrollEventTask
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Event001, TestSize.Level1)
{
    auto event1 = [](Dimension, ScrollState) {
        ScrollFrameResult result;
        return result;
    };
    auto event2 = [](Dimension, Dimension) {
        ScrollInfo result;
        return result;
    };
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetOnScrollFrameBegin(event1);
    scrollModel.SetOnScrollBegin(event2);
    CreateContent();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. When set event
     * @tc.expected: scrollableEvent would has event that setted
     */
    ASSERT_NE(eventHub_->GetScrollFrameBeginEvent(), nullptr);
    ASSERT_NE(eventHub_->GetScrollBeginEvent(), nullptr);
}

/**
 * @tc.name: Event002
 * @tc.desc: Test attribute about onScroll,
 * Event is triggered while scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Event002, TestSize.Level1)
{
    bool isTrigger = false;
    NG::ScrollEvent event = [&isTrigger](Dimension, Dimension) { isTrigger = true; };

    /**
     * @tc.steps: step1. Test event in VERTICAL
     */
    CreateScroll(Axis::VERTICAL, std::move(event));

    /**
     * @tc.steps: step2. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-COLUMN_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step3. Trigger event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step4. Test event in HORIZONTAL
     */
    isTrigger = false;
    CreateScroll(Axis::HORIZONTAL, std::move(event));

    /**
     * @tc.steps: step5. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->OnScrollCallback(-COLUMN_WIDTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step6. Trigger event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event003
 * @tc.desc: Test attribute about onScrollEdge,
 * Event is triggered while scroll to edge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Event003, TestSize.Level1)
{
    bool isTrigger = false;
    NG::ScrollEdgeEvent event = [&isTrigger](ScrollEdge) { isTrigger = true; };

    /**
     * @tc.steps: step1. Test event in VERTICAL
     */
    CreateScroll(Axis::VERTICAL, std::move(event));

    /**
     * @tc.steps: step2. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-COLUMN_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step3. Trigger event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step4. Test event in HORIZONTAL
     */
    isTrigger = false;
    CreateScroll(Axis::HORIZONTAL, std::move(event));

    /**
     * @tc.steps: step5. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-COLUMN_WIDTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step6. Trigger event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event004
 * @tc.desc: Test attribute about onScrollStart and onScrollStop and onScrollEnd,
 * Event is triggered while scrolling start
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Event004, TestSize.Level1)
{
    bool isTrigger = false;
    OnScrollStartEvent event = [&isTrigger]() { isTrigger = true; };

    /**
     * @tc.steps: step1. Test onScrollStart event in VERTICAL
     */
    CreateScroll(Axis::VERTICAL, std::move(event));

    /**
     * @tc.steps: step2. Trigger onScrollStart event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-COLUMN_HEIGHT, SCROLL_FROM_START);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step3. Trigger onScrollStart event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step4. Trigger onScrollStop / onScrollEnd event
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->OnScrollEndCallback(); // Trigger onScrollEnd, set scrollStop_ = true;
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    RunMeasureAndLayout(); // Trigger onScrollStop
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: ScrollPositionController001
 * @tc.desc: Test ScrollPositionController with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollPositionController001, TestSize.Level1)
{
    CreateScroll();

    auto controller = pattern_->GetScrollPositionController();
    const Dimension position1(COLUMN_HEIGHT);
    const float duration1 = -1.f;
    bool animate = controller->AnimateTo(position1, duration1, Curves::LINEAR, false);
    EXPECT_TRUE(animate);

    const Dimension position2(1.0, DimensionUnit::PERCENT);
    const float duration2 = 1.f;
    animate = controller->AnimateTo(position2, duration2, Curves::LINEAR, false);
    EXPECT_FALSE(animate);

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    const Offset expectOffset1(0, ROOT_HEIGHT - COLUMN_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset1));

    controller->ScrollPage(false, false);
    const Offset expectOffset2(0, ROOT_HEIGHT - COLUMN_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset2));

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_FALSE(controller->IsAtEnd());
    const float delta = COLUMN_HEIGHT - ROOT_HEIGHT;
    UpdateCurrentOffset(-delta);
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: ScrollPositionControlle002
 * @tc.desc: Test ScrollPositionController with Axis::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollPositionControlle002, TestSize.Level1)
{
    CreateScroll(Axis::NONE);

    auto controller = pattern_->GetScrollPositionController();
    const Dimension position(COLUMN_HEIGHT);
    const float duration = 1.f;
    bool animate = controller->AnimateTo(position, duration, Curves::LINEAR, false);
    EXPECT_FALSE(animate);

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    const Offset expectOffset1(0, 0);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset1));

    controller->ScrollPage(false, false);
    const Offset expectOffset2(0, 0);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset2));
}

/**
 * @tc.name: PaintMethod001
 * @tc.desc: Test PaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, PaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Do not SetScrollBarWidth
     * @tc.expected: scrollBar->NeedPaint() is false
     */
    CreateScroll();
    auto paint_1 = pattern_->CreateNodePaintMethod();
    auto scrollPaint_1 = AceType::DynamicCast<ScrollPaintMethod>(paint_1);
    RSCanvas canvas_1;
    RefPtr<GeometryNode> geometryNode_1 = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper_1(nullptr, geometryNode_1, paintProperty_);
    scrollPaint_1->PaintScrollBar(canvas_1, &paintWrapper_1);
    EXPECT_FALSE(scrollPaint_1->scrollBar_.Upgrade()->NeedPaint());

    /**
     * @tc.steps: step1. SetScrollBarWidth
     * @tc.expected: scrollBar->NeedPaint() is true
     */
    CreateScroll(Dimension(10.f));
    auto paint_2 = pattern_->CreateNodePaintMethod();
    auto scrollPaint_2 = AceType::DynamicCast<ScrollPaintMethod>(paint_2);
    RSCanvas canvas_2;
    RefPtr<GeometryNode> geometryNode_2 = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper_2(nullptr, geometryNode_2, paintProperty_);
    scrollPaint_2->PaintScrollBar(canvas_2, &paintWrapper_2);
    EXPECT_TRUE(scrollPaint_2->scrollBar_.Upgrade()->NeedPaint());
}

/**
 * @tc.name: SpringEffect001
 * @tc.desc: Test SpringEffect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, SpringEffect001, TestSize.Level1)
{
    auto springEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
    springEffect->ProcessScrollOver(0.0);

    CreateScroll(EdgeEffect::SPRING);
    springEffect = AceType::DynamicCast<ScrollSpringEffect>(pattern_->GetScrollEdgeEffect());
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    springEffect->SetScrollable(scrollable);
    springEffect->ProcessScrollOver(0.0);

    scrollable->MarkAvailable(false);
    springEffect->ProcessScrollOver(0.0);

    pattern_->SetDirection(FlexDirection::ROW_REVERSE);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    springEffect->ProcessScrollOver(0.0);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: ScrollTest001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest001, TestSize.Level1)
{
    auto layoutWrapper = CreateScroll();
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    auto dirty = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(dirty);

    config.skipMeasure = true;
    config.skipLayout = true;
    dirty = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(dirty);

    config.skipMeasure = false;
    config.skipLayout = false;
    dirty = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(dirty);
}

/**
 * @tc.name: ScrollTest002
 * @tc.desc: When setting a fixed length and width, verify the related functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest002, TestSize.Level1)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::HORIZONTAL);
    scrollModel.SetDisplayMode(static_cast<int>(NG::DisplayMode::OFF));
    auto scrollProxy = scrollModel.CreateScrollBarProxy();
    scrollModel.SetScrollBarProxy(scrollProxy);
    CreateContent();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step5. When Axis is HORIZONTAL, Verify the callback function registered in scrollBarProxy.
     * @tc.expected: step5. Check whether the return value is as expected.
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
    CreateScroll();

    /**
     * @tc.steps: step5. Set ScrollSpringEffect and call relevant callback functions.
     * @tc.expected: step5. Check whether the return value is correct.
     */
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    ASSERT_NE(scrollEdgeEffect, nullptr);
    auto springEffect = AceType::DynamicCast<ScrollSpringEffect>(scrollEdgeEffect);
    ASSERT_NE(springEffect, nullptr);
    pattern_->currentOffset_ = 100.f;
    pattern_->scrollableDistance_ = 100.f;
    auto isOutBoundary = springEffect->outBoundaryCallback_();
    EXPECT_TRUE(isOutBoundary);
    auto currentPosition = scrollEdgeEffect->currentPositionCallback_();
    EXPECT_EQ(currentPosition, 100.0);

    /**
     * @tc.steps: step6. When direction is the default value, call the relevant callback function.
     * @tc.expected: step6. Check whether the return value is correct.
     */
    auto leading = scrollEdgeEffect->leadingCallback_();
    EXPECT_EQ(leading, -100.f);
    auto trailing = scrollEdgeEffect->trailingCallback_();
    EXPECT_EQ(trailing, 0.0);
    auto initLeading = scrollEdgeEffect->initLeadingCallback_();
    EXPECT_EQ(initLeading, -100.f);
    auto initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(initTrailing, 0.0);

    /**
     * @tc.steps: step7. When direction is ROW_REVERSE, call the relevant callback function.
     * @tc.expected: step7. Check whether the return value is correct.
     */
    pattern_->direction_ = FlexDirection::ROW_REVERSE;
    leading = scrollEdgeEffect->leadingCallback_();
    EXPECT_EQ(leading, 0.0);
    trailing = scrollEdgeEffect->trailingCallback_();
    EXPECT_EQ(trailing, 100.f);
    initLeading = scrollEdgeEffect->initLeadingCallback_();
    EXPECT_EQ(initLeading, 0.0);
    initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(initTrailing, 100.f);

    /**
     * @tc.steps: step8. When direction is COLUMN_REVERSE, call the relevant callback function.
     * @tc.expected: step8. Check whether the return value is correct.
     */
    pattern_->direction_ = FlexDirection::COLUMN_REVERSE;
    leading = scrollEdgeEffect->leadingCallback_();
    EXPECT_EQ(leading, 0.0);
    trailing = scrollEdgeEffect->trailingCallback_();
    EXPECT_EQ(trailing, 100.f);
    initLeading = scrollEdgeEffect->initLeadingCallback_();
    EXPECT_EQ(initLeading, 0.0);
    initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(initTrailing, 100.f);
}

/**
 * @tc.name: ScrollTest004
 * @tc.desc: When setting a fixed length and width, verify the related functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest004, TestSize.Level1)
{
    CreateScroll();

    /**
     * @tc.steps: step6. Set ScrollFadeEffect and call relevant callback functions.
     * @tc.expected: step6. Check whether the return value is correct.
     */
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
 * @tc.name: ScrollTest005
 * @tc.desc: Scroll Accessibility PerformAction test ScrollForward and ScrollBackward..
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::NONE);

    /**
     * @tc.steps: step2. Get scroll frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto scrollPattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 0.0;
    scrollPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get scroll accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto scrollAccessibilityProperty = frameNode->GetAccessibilityProperty<ScrollAccessibilityProperty>();
    ASSERT_NE(scrollAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When scroll is not scrollable and scrollable distance is 0, call the callback function in
     *                   scrollAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(scrollAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(scrollAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When scroll is not scrollable and scrollable distance is not 0, call the callback function in
     *                   scrollAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    scrollPattern->scrollableDistance_ = 100.f;
    EXPECT_TRUE(scrollAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(scrollAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step6. When scroll is scrollable and scrollable distance is not 0, call the callback function in
     *                   scrollAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    scrollPattern->SetAxis(Axis::VERTICAL);
    EXPECT_TRUE(scrollAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(scrollAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step7. When scroll is scrollable and scrollable distance is 0, call the callback function in
     *                   scrollAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    scrollPattern->scrollableDistance_ = 0.0;
    EXPECT_TRUE(scrollAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(scrollAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When unscrollable
     * @tc.expected: currentOffset would not change
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    GetInstance();
    RunMeasureAndLayout();
    pattern_->UpdateCurrentOffset(10.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    /**
     * @tc.steps: step1. When Axis::VERTICAL
     */
    CreateScroll();
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_JUMP);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -10.f)));
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_BAR);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -20.f)));
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_ROTATE);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -30.f)));
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_ANIMATION);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -40.f)));
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -50.f)));

    /**
     * @tc.steps: step1. When Axis::HORIZONTAL
     */
    CreateScroll(Axis::HORIZONTAL);
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_JUMP);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(-10.f, 0)));
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_BAR);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(-20.f, 0)));
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_ROTATE);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(-30.f, 0)));
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_ANIMATION);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(-40.f, 0)));
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(-50.f, 0)));

    /**
     * @tc.steps: step1. When EdgeEffect::SPRING, Test ValidateOffset
     */
    CreateScroll(EdgeEffect::SPRING);
    EXPECT_FALSE(pattern_->IsRestrictBoundary());
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_JUMP);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -10.f)));
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_BAR);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -20.f)));
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_ROTATE);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -30.f)));
    pattern_->currentOffset_ = 10.f;
    pattern_->UpdateCurrentOffset(-5.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetScrollBarOutBoundaryExtent(), 5.f);
    pattern_->currentOffset_ = -1000.f;
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetScrollBarOutBoundaryExtent(), -pattern_->currentOffset_ - (COLUMN_HEIGHT - ROOT_HEIGHT));
}

/**
 * @tc.name: ScrollFadeEffect001
 * @tc.desc: Test the correlation function in ScrollFadeEffect under different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollFadeEffect001, TestSize.Level1)
{
    CreateScroll(EdgeEffect::FADE);
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollEdgeEffect->SetScrollable(scrollable);

    /**
     * @tc.steps: step1. call InitialEdgeEffect()
     */
    auto scrollFadeEffect = AceType::DynamicCast<ScrollFadeEffect>(scrollEdgeEffect);
    scrollEdgeEffect->InitialEdgeEffect();
    EXPECT_EQ(scrollFadeEffect->fadeColor_, Color::GRAY);
    scrollFadeEffect->fadeController_->DecelerateListener(1.0);

    /**
     * @tc.steps: step2. call HandleOverScroll(), overScroll is 0
     * @tc.expected: do nothing
     */
    const SizeF viewPort(ROOT_WIDTH, ROOT_HEIGHT);
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, 0.f, viewPort);

    /**
     * @tc.steps: step3. call HandleOverScroll()
     */
    scrollFadeEffect->fadeController_ = nullptr;
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, -1.f, viewPort);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::UP);
    ASSERT_NE(scrollFadeEffect->fadeController_, nullptr);
    scrollFadeEffect->fadeController_->DecelerateListener(1.0);

    scrollFadeEffect->scrollable_->currentVelocity_ = 1000.0;
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, 1.f, viewPort);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::DOWN);

    scrollFadeEffect->scrollable_->currentVelocity_ = 0.0;
    scrollFadeEffect->HandleOverScroll(Axis::HORIZONTAL, -1.f, viewPort);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::LEFT);

    scrollFadeEffect->scrollable_->currentVelocity_ = 1000.0;
    scrollFadeEffect->HandleOverScroll(Axis::HORIZONTAL, 1.f, viewPort);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::RIGHT);

    /**
     * @tc.steps: step4. scrollable_ is null, call HandleOverScroll()
     */
    scrollFadeEffect->scrollable_ = nullptr;
    scrollFadeEffect->HandleOverScroll(Axis::HORIZONTAL, -1.f, viewPort);

    /**
     * @tc.steps: step5. Call CalculateOverScroll()
     */
    // minExtent:  0
    // maxExtent: COLUMN_CHILD_HEIGHT * 2
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(COLUMN_CHILD_HEIGHT, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-COLUMN_CHILD_HEIGHT, true), 0.0));

    UpdateCurrentOffset(-COLUMN_CHILD_HEIGHT);
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(COLUMN_CHILD_HEIGHT * 2, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-COLUMN_CHILD_HEIGHT * 2, true), 0.0));

    UpdateCurrentOffset(-COLUMN_CHILD_HEIGHT);
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(COLUMN_CHILD_HEIGHT, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-COLUMN_CHILD_HEIGHT, true), 0.0));

    pattern_->currentOffset_ = COLUMN_CHILD_HEIGHT;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(COLUMN_CHILD_HEIGHT, true), -COLUMN_CHILD_HEIGHT));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), -COLUMN_CHILD_HEIGHT));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-COLUMN_CHILD_HEIGHT * 2, true), 0.0));

    pattern_->currentOffset_ = -COLUMN_CHILD_HEIGHT;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(COLUMN_CHILD_HEIGHT * 2, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-COLUMN_CHILD_HEIGHT, true), 0.0));

    // over scroll
    pattern_->currentOffset_ = -COLUMN_CHILD_HEIGHT * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(COLUMN_CHILD_HEIGHT * 2, true), COLUMN_CHILD_HEIGHT));

    // crash the bottom
    pattern_->currentOffset_ = -COLUMN_CHILD_HEIGHT * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(COLUMN_CHILD_HEIGHT, true), COLUMN_CHILD_HEIGHT));
    pattern_->currentOffset_ = -COLUMN_CHILD_HEIGHT * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(COLUMN_CHILD_HEIGHT, false), 0.0));
    pattern_->currentOffset_ = -COLUMN_CHILD_HEIGHT * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(COLUMN_CHILD_HEIGHT * 3, false), 0.0));
}

/**
 * @tc.name: FadeController001
 * @tc.desc: Test scroll_fade_controller
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, FadeController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollFadeController and set callback function.
     */
    auto fadeController = AceType::MakeRefPtr<ScrollFadeController>();
    ASSERT_NE(fadeController, nullptr);
    double param1 = 10.f;
    double param2 = -10.0;
    auto callback = [&param1, &param2](double parameter1, double parameter2) {
        param1 = parameter1;
        param2 = parameter2;
    };
    fadeController->SetCallback(callback);

    /**
     * @tc.steps: step2. Verify the ProcessAbsorb function and callback function in fadeController.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    fadeController->ProcessAbsorb(100.0);
    EXPECT_EQ(fadeController->opacityFloor_, 0.3);
    EXPECT_EQ(fadeController->opacityCeil_, 0.3);
    EXPECT_EQ(fadeController->scaleSizeFloor_, 0.0);
    EXPECT_EQ(fadeController->scaleSizeCeil_, 0.0325);
    EXPECT_EQ(fadeController->state_, OverScrollState::ABSORB);
    fadeController->decele_->NotifyListener(100.0);
    EXPECT_EQ(fadeController->opacity_, 0.3);
    EXPECT_EQ(fadeController->scaleSize_, 3.25);
    EXPECT_EQ(param1, fadeController->opacity_);
    EXPECT_EQ(param2, fadeController->scaleSize_);

    /**
     * @tc.steps: step2. When OverScrollState is ABSORB, call the callback function in fadeController.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    fadeController->controller_->NotifyStopListener();
    EXPECT_EQ(fadeController->opacityCeil_, 0.0);
    EXPECT_EQ(fadeController->scaleSizeCeil_, 0.0);
    EXPECT_EQ(fadeController->state_, OverScrollState::RECEDE);

    /**
     * @tc.steps: step3. When OverScrollState is RECEDE, call the ProcessRecede function and callback function in
     *                   fadeController.
     * @tc.expected: step3. Check whether relevant parameters are correct.
     */
    fadeController->ProcessRecede(1000);
    fadeController->controller_->NotifyStopListener();
    EXPECT_EQ(fadeController->state_, OverScrollState::IDLE);
    EXPECT_EQ(fadeController->pullDistance_, 0.0);
    fadeController->ProcessRecede(1000);
    EXPECT_EQ(fadeController->pullDistance_, 0.0);

    /**
     * @tc.steps: step4. When OverScrollState is IDLE, call the ProcessPull function and callback function in
     *                   fadeController.
     * @tc.expected: step4. Check whether relevant parameters are correct.
     */
    fadeController->ProcessPull(1.0, 1.0, 1.0);
    EXPECT_EQ(fadeController->opacityFloor_, 0.3);
    EXPECT_EQ(fadeController->opacityCeil_, 0.5);
    EXPECT_EQ(fadeController->scaleSizeFloor_, 3.25);
    EXPECT_EQ(fadeController->scaleSizeCeil_, 3.25);
    EXPECT_EQ(fadeController->state_, OverScrollState::PULL);

    /**
     * @tc.steps: step5. When OverScrollState is PULL, call the ProcessAbsorb function and callback function in
     *                   fadeController.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    fadeController->ProcessAbsorb(-10.0);
    fadeController->decele_->NotifyListener(100.0);
    EXPECT_EQ(fadeController->opacity_, 20.3);
    EXPECT_EQ(fadeController->scaleSize_, 3.25);
    fadeController->controller_->NotifyStopListener();
    EXPECT_EQ(fadeController->state_, OverScrollState::PULL);
    fadeController->ProcessAbsorb(100.0);
    fadeController->ProcessPull(1.0, 1.0, 1.0);
    fadeController->decele_->NotifyListener(100.0);
    EXPECT_EQ(param1, 20.3);
    EXPECT_EQ(param2, 3.25);
}

/**
 * @tc.name: ScrollBar001
 * @tc.desc: Test UpdateScrollBarRegion function in ScrollBar under different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When the ShapeMode is RECT and DisplayMode is LEFT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step1. Check whether relevant parameters are correct.
     */
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    ASSERT_NE(scrollBar, nullptr);
    scrollBar->shapeMode_ = ShapeMode::RECT;
    scrollBar->positionMode_ = PositionMode::LEFT;
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 1.0);
    auto barRect = Rect(0.0, 0.0, 0.0, 100.0) + Offset::Zero();
    EXPECT_EQ(scrollBar->barRect_, barRect);
    EXPECT_EQ(scrollBar->activeRect_, Rect(0.0, -9900.0, 0.0, 10000.0));
    EXPECT_EQ(scrollBar->touchRegion_, Rect(0.0, -9900.0, 0.0, 10000.0));

    /**
     * @tc.steps: step2. When the ShapeMode is RECT and DisplayMode is BOTTOM, verify the UpdateScrollBarRegion
     *            function.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::BOTTOM;
    scrollBar->SetOutBoundary(1.0);
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 1.0);
    barRect = Rect(0.0, 100.0, 100.0, 0.0) + Offset::Zero();
    EXPECT_EQ(scrollBar->barRect_, barRect);
    EXPECT_EQ(scrollBar->activeRect_, Rect(-9899.0, 100.0, 9999.0, 0.0));
    EXPECT_EQ(scrollBar->touchRegion_, Rect(-9899.0, 100.0, 9999.0, 0.0));

    /**
     * @tc.steps: step3. When the ShapeMode is RECT and DisplayMode is RIGHT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step3. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::RIGHT;
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 1.0);
    barRect = Rect(100.0, 0.0, 0.0, 100.0) + Offset::Zero();
    EXPECT_EQ(scrollBar->barRect_, barRect);
    EXPECT_EQ(scrollBar->activeRect_, Rect(100.0, -9899.0, 0.0, 9999.0));
    EXPECT_EQ(scrollBar->touchRegion_, Rect(100.0, -9899.0, 0.0, 9999.0));

    /**
     * @tc.steps: step4. When the ShapeMode is ROUND and DisplayMode is LEFT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step4. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->shapeMode_ = ShapeMode::ROUND;
    scrollBar->positionMode_ = PositionMode::LEFT;
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 1.0);
    EXPECT_EQ(scrollBar->trickStartAngle_, 150);
    EXPECT_EQ(scrollBar->trickSweepAngle_, -6000);

    /**
     * @tc.steps: step5. When the ShapeMode is ROUND and DisplayMode is RIGHT, verify the UpdateScrollBarRegion
     *                   function.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::RIGHT;
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 1.0);
    EXPECT_EQ(scrollBar->trickStartAngle_, 30);
    EXPECT_EQ(scrollBar->trickSweepAngle_, 6000);

    /**
     * @tc.steps: step6. When the ShapeMode is ROUND and DisplayMode is LEFT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step6. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::LEFT;
    scrollBar->bottomAngle_ = 50.f;
    scrollBar->topAngle_ = 100.0;
    scrollBar->SetOutBoundary(1.0);
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 200.0);
    EXPECT_EQ(scrollBar->trickStartAngle_, -155);
    EXPECT_EQ(scrollBar->trickSweepAngle_, -10);
}

/**
 * @tc.name: ScrollBar002
 * @tc.desc: Test SetGestureEvent() / SetMouseEvent()
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollBar002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Touch in bar
     * @tc.expected: touchAnimator_ is take effect
     */
    // pattern_->GetScrollBar()->touchRegion_ == Rect (710.00, 0.00) - [10.00 x 946.67]
    const float barWidth = 10.f;
    CreateScroll(Dimension(barWidth));
    auto scrollBar = pattern_->GetScrollBar();
    const Offset downInBar = Offset(ROOT_WIDTH - 1.f, 0.f);
    const Offset moveInBar = Offset(ROOT_WIDTH - 1.f, 10.f);
    const Offset upInBar = moveInBar;
    const Offset upOutBar = Offset(ROOT_WIDTH - barWidth - 1.f, 10.f);

    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), BAR_EXPAND_DURATION);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), BAR_SHRINK_DURATION);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step2. Touch in bar and up out of bar
     * @tc.expected: touchAnimator_ is take effect
     */
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), BAR_EXPAND_DURATION);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upOutBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), BAR_SHRINK_DURATION);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step3. Touch in bar with SourceType::MOUSE
     * @tc.expected: touchAnimator_ is take effect
     */
    Touch(TouchType::DOWN, downInBar, SourceType::MOUSE);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), BAR_EXPAND_DURATION);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::MOUSE);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::MOUSE);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), BAR_SHRINK_DURATION);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step4. Touch in bar with SourceType::TOUCH_PAD
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->touchAnimator_->SetDuration(0);
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH_PAD);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH_PAD);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH_PAD);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step5. Touch out of bar
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->touchAnimator_->SetDuration(0);
    Touch(TouchType::DOWN, Offset::Zero(), SourceType::TOUCH);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step6. Touch in bar and scrollBar->IsHover() is true
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->touchAnimator_->SetDuration(0);
    scrollBar->SetHover(true);
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step7. Mouse in bar and move out of bar (out->in->in->out)
     * @tc.expected: touchAnimator_ is take effect
     */
    CreateScroll(Dimension(barWidth));
    scrollBar = pattern_->GetScrollBar();
    const Offset moveOutBar = Offset(ROOT_WIDTH - barWidth - 1.f, 0.f);

    Mouse(moveOutBar);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_FALSE(scrollBar->IsHover());
    Mouse(moveInBar);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), BAR_EXPAND_DURATION);
    EXPECT_TRUE(scrollBar->IsHover());
    Mouse(moveInBar);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), BAR_EXPAND_DURATION);
    EXPECT_TRUE(scrollBar->IsHover());
    Mouse(moveOutBar);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), BAR_SHRINK_DURATION);
    EXPECT_FALSE(scrollBar->IsHover());

    /**
     * @tc.steps: step8. (out->in->in->out) and scrollBar->IsPressed() is true
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->touchAnimator_->SetDuration(0);
    scrollBar->SetPressed(true);
    Mouse(moveOutBar);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_FALSE(scrollBar->IsHover());
    Mouse(moveInBar);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_TRUE(scrollBar->IsHover());
    Mouse(moveInBar);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_TRUE(scrollBar->IsHover());
    Mouse(moveOutBar);
    EXPECT_EQ(scrollBar->touchAnimator_->GetDuration(), 0);
    EXPECT_FALSE(scrollBar->IsHover());
}

/**
 * @tc.name: ScrollBar003
 * @tc.desc: Test bar rect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollBar003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test Bar in VERTICAL
     * @tc.expected: Verify bar rect
     */
    const float barWidth = 10.f;
    CreateScroll(Dimension(barWidth));
    auto scrollBar = pattern_->GetScrollBar();

    EXPECT_TRUE(IsEqualRect(scrollBar->touchRegion_,
        Rect(ROOT_WIDTH - barWidth, 0.f, barWidth, ROOT_HEIGHT / CHILD_NUMBER * VIEWPORT_CHILD_NUMBER)));

    UpdateCurrentOffset(-COLUMN_CHILD_HEIGHT);
    EXPECT_TRUE(IsEqualRect(
        scrollBar->touchRegion_, Rect(ROOT_WIDTH - barWidth, COLUMN_CHILD_HEIGHT / CHILD_NUMBER * VIEWPORT_CHILD_NUMBER,
                                     barWidth, ROOT_HEIGHT / CHILD_NUMBER * VIEWPORT_CHILD_NUMBER)));

    UpdateCurrentOffset(-COLUMN_CHILD_HEIGHT);
    EXPECT_TRUE(IsEqualRect(scrollBar->touchRegion_,
        Rect(ROOT_WIDTH - barWidth, COLUMN_CHILD_HEIGHT * 2 / CHILD_NUMBER * VIEWPORT_CHILD_NUMBER, barWidth,
            ROOT_HEIGHT / CHILD_NUMBER * VIEWPORT_CHILD_NUMBER)));

    /**
     * @tc.steps: step2. Test Bar in HORIZONTAL
     * @tc.expected: Verify bar rect
     */
    CreateScroll(Dimension(barWidth), Axis::HORIZONTAL);
    scrollBar = pattern_->GetScrollBar();

    EXPECT_TRUE(IsEqualRect(scrollBar->touchRegion_,
        Rect(0.f, ROOT_HEIGHT - barWidth, ROOT_WIDTH / CHILD_NUMBER * VIEWPORT_CHILD_NUMBER, barWidth)));

    UpdateCurrentOffset(-COLUMN_CHILD_WIDTH);
    EXPECT_TRUE(IsEqualRect(
        scrollBar->touchRegion_, Rect(COLUMN_CHILD_WIDTH / CHILD_NUMBER * VIEWPORT_CHILD_NUMBER, ROOT_HEIGHT - barWidth,
                                     ROOT_WIDTH / CHILD_NUMBER * VIEWPORT_CHILD_NUMBER, barWidth)));

    UpdateCurrentOffset(-COLUMN_CHILD_WIDTH);
    EXPECT_TRUE(IsEqualRect(scrollBar->touchRegion_,
        Rect(COLUMN_CHILD_WIDTH * 2 / CHILD_NUMBER * VIEWPORT_CHILD_NUMBER, ROOT_HEIGHT - barWidth,
            ROOT_WIDTH / CHILD_NUMBER * VIEWPORT_CHILD_NUMBER, barWidth)));
}

/**
 * @tc.name: ScrollBar004
 * @tc.desc: Test ScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollBar004, TestSize.Level1)
{
    const float barWidth = 10.f;
    CreateScroll(Dimension(barWidth));
    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->SetShapeMode(ShapeMode::ROUND);
    EXPECT_FALSE(scrollBar->InBarTouchRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarActiveRegion(Point(0, 0)));
    scrollBar->FlushBarWidth();

    scrollBar->SetDisplayMode(DisplayMode::OFF);
    EXPECT_FALSE(scrollBar->InBarTouchRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarActiveRegion(Point(0, 0)));

    scrollBar->SetPositionMode(PositionMode::LEFT);
    scrollBar->UpdateActiveRectSize(20.f);
    EXPECT_EQ(scrollBar->touchRegion_.Height(), 20.f);
    scrollBar->UpdateActiveRectOffset(30.f);
    EXPECT_EQ(scrollBar->touchRegion_.Top(), 30.f);
    scrollBar->SetPositionMode(PositionMode::BOTTOM);
    scrollBar->UpdateActiveRectSize(20.f);
    EXPECT_EQ(scrollBar->touchRegion_.Width(), 20.f);
    scrollBar->UpdateActiveRectOffset(30.f);
    EXPECT_EQ(scrollBar->touchRegion_.Left(), 30.f);
}

/**
 * @tc.name: Measure001
 * @tc.desc: Test Measure
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Measure001, TestSize.Level1)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::NONE);
    CreateContent();
    GetInstance();

    /**
     * @tc.steps: step1. Do not set idealSize
     * @tc.expected: The idealSize would be child size
     */
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { ROOT_WIDTH, ROOT_HEIGHT };
    LayoutConstraint.percentReference = { ROOT_WIDTH, ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
    auto scrollSize = frameNode_->GetGeometryNode()->GetFrameSize();
    auto expectSize = SizeF(ROOT_WIDTH, COLUMN_HEIGHT);
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
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::NONE);
    CreateContent();
    GetInstance();
    RunMeasureAndLayout();

    layoutProperty_->UpdateAlignment(Alignment::CENTER);
    RunMeasureAndLayout();
    auto col = frameNode_->GetChildAtIndex(0);
    auto colNode = AceType::DynamicCast<FrameNode>(col);
    auto colOffset = colNode->GetGeometryNode()->GetMarginFrameOffset();
    auto expectOffset = OffsetF(0, 0);
    EXPECT_EQ(colOffset, expectOffset) << "colOffset: " << colOffset.ToString()
                                       << " expectOffset: " << expectOffset.ToString();
}

/**
 * @tc.name: OnScrollCallback001
 * @tc.desc: Test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, OnScrollCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Axis::NONE and SCROLL_FROM_UPDATE
     * @tc.expected: Do nothing
     */
    CreateScroll(Axis::NONE);
    EXPECT_FALSE(pattern_->OnScrollCallback(-100.f, SCROLL_FROM_UPDATE));

    /**
     * @tc.steps: step2. animator is running and SCROLL_FROM_UPDATE
     * @tc.expected: Do nothing
     */
    CreateScroll();
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Resume();
    EXPECT_FALSE(pattern_->OnScrollCallback(-100.f, SCROLL_FROM_UPDATE));

    /**
     * @tc.steps: step3. animator is stopped and SCROLL_FROM_UPDATE
     * @tc.expected: Trigger UpdateCurrentOffset()
     */
    CreateScroll();
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Stop();
    EXPECT_TRUE(pattern_->OnScrollCallback(-100.f, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -100.f)));

    /**
     * @tc.steps: step4. scrollBar->IsDriving() is true and SCROLL_FROM_UPDATE
     * @tc.expected: Trigger UpdateCurrentOffset()
     */
    CreateScroll();
    EXPECT_TRUE(pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -100.f / pattern_->GetScrollBar()->offsetScale_)));

    /**
     * @tc.steps: step5. no animator and SCROLL_FROM_START
     * @tc.expected: Trigger FireOnScrollStart()
     */
    bool isTrigger = false;
    OnScrollStartEvent event = [&isTrigger]() { isTrigger = true; };
    CreateScroll(Axis::VERTICAL, std::move(event));
    EXPECT_TRUE(pattern_->OnScrollCallback(-100.f, SCROLL_FROM_START));
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step6. animator is Stopped and SCROLL_FROM_START
     * @tc.expected: Trigger FireOnScrollStart()
     */
    isTrigger = false;
    CreateScroll(Axis::VERTICAL, std::move(event));
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Stop();
    EXPECT_TRUE(pattern_->OnScrollCallback(-100.f, SCROLL_FROM_START));
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step7. animator is running and SCROLL_FROM_START
     * @tc.expected: because of scrollAbort_ is true, would not trigger event, and animator stop()
     */
    isTrigger = false;
    CreateScroll(Axis::VERTICAL, std::move(event));
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Resume();
    auto onScrollCallback = pattern_->scrollableEvent_->GetScrollPositionCallback();
    EXPECT_TRUE(onScrollCallback(-100.f, SCROLL_FROM_START));
    EXPECT_TRUE(pattern_->animator_->IsStopped());
    EXPECT_FALSE(isTrigger);
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
    CreateScroll();
    pattern_->ScrollToNode(GetContentChild(5));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
    pattern_->ScrollToNode(GetContentChild(10));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -COLUMN_CHILD_HEIGHT)));
    pattern_->ScrollToNode(GetContentChild(11));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -COLUMN_CHILD_HEIGHT * 2)));
    pattern_->ScrollToNode(GetContentChild(0));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    /**
     * @tc.steps: step2. ScrollToNode in HORIZONTAL
     * @tc.expected: currentOffset_ is correct
     */
    CreateScroll(Axis::HORIZONTAL);
    pattern_->ScrollToNode(GetContentChild(5));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
    pattern_->ScrollToNode(GetContentChild(10));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(-COLUMN_CHILD_WIDTH, 0)));
    pattern_->ScrollToNode(GetContentChild(11));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(-COLUMN_CHILD_WIDTH * 2, 0)));
    pattern_->ScrollToNode(GetContentChild(0));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    /**
     * @tc.steps: step1. ScrollToNode itSelf
     * @tc.expected: currentOffset_ is zero
     */
    CreateScroll();
    pattern_->ScrollToNode(frameNode_);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
    pattern_->ScrollToNode(AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0)));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
}

/**
 * @tc.name: Pattern001
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Pattern001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Trigger OnModifyDone
     * @tc.expected: Has ScrollableEvent, has AccessibilityAction
     */
    CreateScroll();
    ASSERT_NE(pattern_->GetScrollableEvent(), nullptr);
    ASSERT_NE(accessibilityProperty_->actionScrollForwardImpl_, nullptr);
    ASSERT_NE(accessibilityProperty_->actionScrollBackwardImpl_, nullptr);

    /**
     * @tc.steps: step1. Change axis and trigger OnModifyDone
     * @tc.expected: Axis would be changed and Would not RegisterScrollEventTask again
     */
    layoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
    ASSERT_NE(pattern_->GetScrollableEvent(), nullptr);
}

/**
 * @tc.name: Pattern004
 * @tc.desc: Test SetAccessibilityAction
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Pattern004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test SetAccessibilityAction with unScrollable scroll
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Trigger actionScrollForwardImpl_
     * @tc.expected: Can not ScrollPage
     */
    accessibilityProperty_->actionScrollForwardImpl_();
    EXPECT_EQ(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step3. Trigger actionScrollBackwardImpl_
     * @tc.expected: Can not ScrollPage
     */
    accessibilityProperty_->actionScrollBackwardImpl_();
    EXPECT_EQ(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step4. Test SetAccessibilityAction with Axis::NONE
     */
    CreateScroll(Axis::NONE);

    /**
     * @tc.steps: step5. Trigger actionScrollForwardImpl_
     * @tc.expected: Can not ScrollPage
     */
    accessibilityProperty_->actionScrollForwardImpl_();
    EXPECT_EQ(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step6. Trigger actionScrollBackwardImpl_
     * @tc.expected: Can not ScrollPage
     */
    accessibilityProperty_->actionScrollBackwardImpl_();
    EXPECT_EQ(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step7. Test SetAccessibilityAction with Axis::Vertical
     */
    CreateScroll();

    /**
     * @tc.steps: step8. Trigger actionScrollForwardImpl_
     * @tc.expected: ScrollPage forward, would trigger AnimateTo()
     */
    accessibilityProperty_->actionScrollForwardImpl_();
    ASSERT_NE(pattern_->animator_, nullptr);

    /**
     * @tc.steps: step9. Trigger actionScrollBackwardImpl_
     * @tc.expected: ScrollPage backward, would trigger AnimateTo()
     */
    pattern_->animator_ = nullptr;
    accessibilityProperty_->actionScrollBackwardImpl_();
    ASSERT_NE(pattern_->animator_, nullptr);
}

/**
 * @tc.name: Pattern007
 * @tc.desc: Test HandleScrollBarOutBoundary
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Pattern007, TestSize.Level1)
{
    CreateScroll();

    /**
     * @tc.steps: step1. When scrollBar is not OFF
     * @tc.expected: outBoundary_ would be set
     */
    pattern_->SetScrollBarOutBoundaryExtent(100.f);
    pattern_->HandleScrollBarOutBoundary();
    auto scrollBar = pattern_->GetScrollBar();
    EXPECT_EQ(scrollBar->outBoundary_, 100.f);

    /**
     * @tc.steps: step1. When scrollBar is OFF
     * @tc.expected: outBoundary_ would not be set
     */
    pattern_->SetScrollBarOutBoundaryExtent(200.f);
    scrollBar->displayMode_ = DisplayMode::OFF;
    pattern_->HandleScrollBarOutBoundary();
    EXPECT_EQ(scrollBar->outBoundary_, 100.f);
}

/**
 * @tc.name: Pattern010
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Pattern010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test DoJump
     */
    CreateScroll();

    /**
     * @tc.steps: step2. jump to a position
     * @tc.expected: CurrentOffset would be to the position
     */
    pattern_->DoJump(-100.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -100.f)));

    /**
     * @tc.steps: step3. jump to the same position
     * @tc.expected: CurrentOffset would not be change
     */
    pattern_->DoJump(-100.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -100.f)));

    /**
     * @tc.steps: step4. Test ScrollBy
     */
    CreateScroll();

    /**
     * @tc.steps: step5. ScrollBy 0
     * @tc.expected: CurrentOffset would not change
     */
    pattern_->ScrollBy(0, 0, false);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    /**
     * @tc.steps: step6. ScrollBy a distance
     * @tc.expected: Scroll by the distance
     */
    pattern_->ScrollBy(0, -100.f, false);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, -100.f)));

    /**
     * @tc.steps: step7. Test ScrollToEdge
     */
    CreateScroll();

    /**
     * @tc.steps: step8. ScrollEdgeType::SCROLL_NONE
     * @tc.expected: CurrentOffset would not be change
     */
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    /**
     * @tc.steps: step9. ScrollEdgeType::SCROLL_BOTTOM
     * @tc.expected: CurrentOffset would down to bottom
     */
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, ROOT_HEIGHT - COLUMN_HEIGHT)));

    /**
     * @tc.steps: step10. ScrollEdgeType::SCROLL_TOP
     * @tc.expected: CurrentOffset would up to top
     */
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
}

/**
 * @tc.name: Pattern011
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Pattern011, TestSize.Level1)
{
    CreateScroll(EdgeEffect::FADE);
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    auto scrollFadeEffect = AceType::DynamicCast<ScrollFadeEffect>(scrollEdgeEffect);
    scrollFadeEffect->InitialEdgeEffect();

    Testing::MockCanvas rsCanvas;
    OffsetF offset = OffsetF(0, 0);
    scrollFadeEffect->fadePainter_->SetOpacity(0);
    scrollFadeEffect->fadePainter_->direction_ = OverScrollDirection::UP;
    scrollFadeEffect->Paint(rsCanvas, SizeF(1, 1), offset);
    scrollFadeEffect->fadePainter_->SetOpacity(1);
    scrollFadeEffect->fadePainter_->direction_ = OverScrollDirection::DOWN;
    scrollFadeEffect->Paint(rsCanvas, SizeF(0, 1), offset);
    scrollFadeEffect->fadePainter_->direction_ = OverScrollDirection::LEFT;
    scrollFadeEffect->Paint(rsCanvas, SizeF(1, 0), offset);
    scrollFadeEffect->fadePainter_->direction_ = OverScrollDirection::RIGHT;
    scrollFadeEffect->Paint(rsCanvas, SizeF(0, 0), offset);
    SUCCEED();
}

/**
 * @tc.name: Pattern012
 * @tc.desc: Test CalcReservedHeight()
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Pattern012, TestSize.Level1)
{
    CreateScroll();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->SetMinPlatformVersion(PLATFORM_VERSION_TEN + 1);
    auto scrollBar = pattern_->GetScrollBar();

    scrollBar->SetPositionMode(PositionMode::LEFT);
    scrollBar->SetNormalWidth(Dimension(1)); // call CalcReservedHeight;
    EXPECT_EQ(scrollBar->startReservedHeight_, Dimension(0.0));
    EXPECT_EQ(scrollBar->endReservedHeight_, Dimension(0.0));

    BorderRadiusProperty borderRadiusProperty;
    float radius = 13.f;
    borderRadiusProperty.radiusTopRight = std::make_optional<Dimension>(radius);
    borderRadiusProperty.radiusBottomRight = std::make_optional<Dimension>(radius);
    scrollBar->SetHostBorderRadius(borderRadiusProperty);
    scrollBar->SetPadding(Edge(1, 1, 1, 1));
    scrollBar->SetPositionMode(PositionMode::RIGHT);
    scrollBar->SetNormalWidth(Dimension(2)); // call CalcReservedHeight;
    EXPECT_EQ(scrollBar->startReservedHeight_, Dimension(14.5))
        << "startReservedHeight_: " << scrollBar->startReservedHeight_.ConvertToPx();
    EXPECT_EQ(scrollBar->endReservedHeight_, Dimension(14.5))
        << "endReservedHeight_: " << scrollBar->endReservedHeight_.ConvertToPx();

    borderRadiusProperty.radiusBottomLeft = std::make_optional<Dimension>(radius);
    borderRadiusProperty.radiusBottomRight = std::make_optional<Dimension>(radius);
    scrollBar->SetHostBorderRadius(borderRadiusProperty);
    scrollBar->SetPadding(Edge(1, 1, 1, 1));
    scrollBar->SetPositionMode(PositionMode::BOTTOM);
    scrollBar->SetNormalWidth(Dimension(6)); // call CalcReservedHeight;
    EXPECT_EQ(scrollBar->startReservedHeight_, Dimension(11.25))
        << "startReservedHeight_: " << scrollBar->startReservedHeight_.ConvertToPx();
    EXPECT_EQ(scrollBar->endReservedHeight_, Dimension(11.25))
        << "endReservedHeight_: " << scrollBar->endReservedHeight_.ConvertToPx();
}

/**
 * @tc.name: Test001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Test001, TestSize.Level1)
{
    CreateScroll();

    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(COLUMN_CHILD_HEIGHT), { COLUMN_CHILD_HEIGHT, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-COLUMN_CHILD_HEIGHT), { 0, 0 }));

    UpdateCurrentOffset(-COLUMN_CHILD_HEIGHT);
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(COLUMN_CHILD_HEIGHT * 2), { COLUMN_CHILD_HEIGHT, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-COLUMN_CHILD_HEIGHT * 2), { 0, -COLUMN_CHILD_HEIGHT }));

    UpdateCurrentOffset(-COLUMN_CHILD_HEIGHT);
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(COLUMN_CHILD_HEIGHT), { 0, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-COLUMN_CHILD_HEIGHT), { 0, -COLUMN_CHILD_HEIGHT }));

    pattern_->currentOffset_ = COLUMN_CHILD_HEIGHT;
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(COLUMN_CHILD_HEIGHT), { COLUMN_CHILD_HEIGHT, 0 }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-COLUMN_CHILD_HEIGHT * 2), { -COLUMN_CHILD_HEIGHT, 0 }));

    pattern_->currentOffset_ = -COLUMN_CHILD_HEIGHT * 3;
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(COLUMN_CHILD_HEIGHT * 2), { 0, COLUMN_CHILD_HEIGHT }));
    EXPECT_TRUE(IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(0.f), { 0, 0 }));
    EXPECT_TRUE(
        IsEqualOverScrollOffset(pattern_->GetOverScrollOffset(-COLUMN_CHILD_HEIGHT), { 0, -COLUMN_CHILD_HEIGHT }));
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
    ScrollModelNG scrollModel;
    scrollModel.Create();
    GetInstance();
    RunMeasureAndLayout();
    accessibilityProperty_->ResetSupportAction();
    uint64_t expectActions = 0;
    EXPECT_EQ(GetActions(), expectActions);

    /**
     * @tc.steps: step2. scroll is at top
     * @tc.expected: action is correct
     */
    CreateScroll();
    accessibilityProperty_->ResetSupportAction();
    expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(), expectActions);

    /**
     * @tc.steps: step3. scroll to middle
     * @tc.expected: action is correct
     */
    UpdateCurrentOffset(-COLUMN_CHILD_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(), expectActions);

    /**
     * @tc.steps: step4. scroll to bottom
     * @tc.expected: action is correct
     */
    UpdateCurrentOffset(-COLUMN_CHILD_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(), expectActions);

    /**
     * @tc.steps: step6. test IsScrollable()
     * @tc.expected: return value is correct
     */
    CreateScroll();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    CreateScroll(Axis::NONE);
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: ScrollSetFrictionTest001
 * @tc.desc: Test ScrollSetFriction
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollSetFrictionTest001, TestSize.Level1)
{
    constexpr double friction = -1;
    ScrollModelNG scrollModelNG;
    scrollModelNG.Create();
    scrollModelNG.SetFriction(friction);
    GetInstance();
    /**
     * @tc.expected: friction shouled be more than 0.0,if out of range,should be default value.
     */
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 0.6);
}

/**
 * @tc.name: ScrollSetFrictionTest002
 * @tc.desc: Test ScrollSetFriction
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollSetFrictionTest002, TestSize.Level1)
{
    constexpr double friction = 10;
    ScrollModelNG scrollModelNG;
    scrollModelNG.Create();
    scrollModelNG.SetFriction(friction);
    GetInstance();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 10);
}
} // namespace OHOS::Ace::NG
