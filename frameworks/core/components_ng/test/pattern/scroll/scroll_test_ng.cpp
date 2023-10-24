/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"

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
#include "core/components_ng/test/pattern/test_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t VIEW_NUMBER = 10;
constexpr int32_t TOTAL_NUMBER = 12;
constexpr float DEFAULT_ACTIVE_WIDTH = 8.0f;
constexpr float DEFAULT_INACTIVE_WIDTH = 4.0f;
constexpr float DEFAULT_NORMAL_WIDTH = 4.0f;
constexpr float DEFAULT_TOUCH_WIDTH = 32.0f;
constexpr float HORIZONTAL_LENGTH = DEVICE_WIDTH / VIEW_NUMBER;
constexpr float VERTICAL_LENGTH = DEVICE_HEIGHT / VIEW_NUMBER;
constexpr float VERTICAL_SCROLLABLE_DISTANCE = (TOTAL_NUMBER - VIEW_NUMBER) * VERTICAL_LENGTH;
} // namespace

class ScrollTestNg : public testing::Test, public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    void UpdateCurrentOffset(float offset);

    void Create(const std::function<void(ScrollModelNG)>& callback = nullptr);
    void CreateWithContent(const std::function<void(ScrollModelNG)>& callback = nullptr);
    void CreateSnapScroll(ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
    const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide);

    static void CreateContent(int32_t childNumber = TOTAL_NUMBER);
    RefPtr<FrameNode> GetContentChild(int32_t index);
    void Touch(TouchLocationInfo locationInfo, SourceType sourceType);
    void Touch(TouchType touchType, Offset offset, SourceType sourceType);
    void Mouse(MouseInfo mouseInfo);
    void Mouse(Offset moveOffset);
    void Hover(bool isHover);
    bool OnScrollCallback(float offset, int32_t source);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType);
    static Axis GetAxis();
    float GetOffset(float childNumber);
    AssertionResult UpdateAndVerifyPosition(float offset, float expectOffset, int32_t source = SCROLL_FROM_UPDATE);
    AssertionResult ScrollToNode(int32_t childIndex, float expectChildNumber);
    AssertionResult IsEqualCurrentPosition(float expectOffset);

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
    MockPipelineBase::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
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

void ScrollTestNg::Create(const std::function<void(ScrollModelNG)>& callback)
{
    ScrollModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

void ScrollTestNg::CreateWithContent(const std::function<void(ScrollModelNG)>& callback)
{
    Create([callback](ScrollModelNG model) {
        if (callback) {
            callback(model);
        }
        CreateContent();
    });
}

void ScrollTestNg::CreateSnapScroll(ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
    const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide)
{
    CreateWithContent(
        [scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide](ScrollModelNG model) {
        model.SetScrollSnap(scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide);
    });
}

void ScrollTestNg::CreateContent(int32_t childNumber)
{
    if (GetAxis() == Axis::HORIZONTAL) {
        RowModelNG rowModelNG;
        rowModelNG.Create(Dimension(0), nullptr, "");
        SetWidth(Dimension(childNumber * HORIZONTAL_LENGTH));
        SetHeight(FILL_LENGTH);
        for (int32_t index = 0; index < childNumber; index++) {
            RowModelNG rowModelNG;
            rowModelNG.Create(Dimension(0), nullptr, "");
            SetWidth(Dimension(HORIZONTAL_LENGTH));
            SetHeight(FILL_LENGTH);
            ViewStackProcessor::GetInstance()->Pop();
        }
    } else {
        ColumnModelNG columnModel;
        columnModel.Create(Dimension(0), nullptr, "");
        SetWidth(FILL_LENGTH);
        SetHeight(Dimension(childNumber * VERTICAL_LENGTH));
        for (int32_t index = 0; index < childNumber; index++) {
            ColumnModelNG columnModel;
            columnModel.Create(Dimension(0), nullptr, "");
            SetWidth(FILL_LENGTH);
            SetHeight(Dimension(VERTICAL_LENGTH));
            ViewStackProcessor::GetInstance()->Pop();
        }
    }
    ViewStackProcessor::GetInstance()->Pop();
}

void ScrollTestNg::UpdateCurrentOffset(float offset)
{
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode_);
}

RefPtr<FrameNode> ScrollTestNg::GetContentChild(int32_t index)
{
    auto content = GetChildFrameNode(frameNode_, 0);
    auto contentChild = GetChildFrameNode(content, index);
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
    RunMeasureAndLayout(frameNode_);
    return result;
}

void ScrollTestNg::ScrollToEdge(ScrollEdgeType scrollEdgeType)
{
    pattern_->ScrollToEdge(scrollEdgeType, false);
    RunMeasureAndLayout(frameNode_);
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
    float offset = childNumber * (isHorizontal ? HORIZONTAL_LENGTH : VERTICAL_LENGTH);
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
    RunMeasureAndLayout(frameNode_);
    float currentOffset = pattern_->GetCurrentPosition();
    if (NearEqual(currentOffset, expectOffset)) {
        return AssertionSuccess();
    }
    return AssertionFailure() << "currentOffset: " << currentOffset << " != " << "expectOffset: " << expectOffset;
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
 * @tc.name: AttrScrollBar001
 * @tc.desc: Test attribute about scrollBar,
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, AttrScrollBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Text default value: AUTO
     */
    CreateWithContent();
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Auto");

    /**
     * @tc.steps: step2. Text set value: OFF
     */
    CreateWithContent([](ScrollModelNG model) {  model.SetDisplayMode(static_cast<int>(NG::DisplayMode::OFF)); });
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Off");

    /**
     * @tc.steps: step3. Text set value: ON
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int>(NG::DisplayMode::ON)); });
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
     * @tc.steps: step1. Text default value: [color:foregroundColor_, width: 4]
     */
    CreateWithContent();
    auto themeManager = MockPipelineBase::GetCurrent()->GetThemeManager();
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    EXPECT_EQ(paintProperty_->GetBarColor(), scrollBarTheme->GetForegroundColor());
    EXPECT_EQ(paintProperty_->GetBarWidth(), scrollBarTheme->GetNormalWidth());

    /**
     * @tc.steps: step2. Text set value: Color::RED
     */
    CreateWithContent([](ScrollModelNG model) { model.SetScrollBarColor(Color::RED); });
    EXPECT_EQ(paintProperty_->GetBarColor(), Color::RED);

    /**
     * @tc.steps: step3. Text set width value: Dimension(10)
     */
    CreateWithContent([](ScrollModelNG model) { model.SetScrollBarWidth(Dimension(10)); });
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
     * @tc.steps: step1. Text default value: NONE
     */
    CreateWithContent();
    EXPECT_EQ(layoutProperty_->GetEdgeEffectValue(), EdgeEffect::NONE);

    /**
     * @tc.steps: step2. Text set value: SPRING
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING); });
    EXPECT_EQ(layoutProperty_->GetEdgeEffectValue(), EdgeEffect::SPRING);

    /**
     * @tc.steps: step3. Text set width value: FADE
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::FADE); });
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
 * @tc.name: Event001
 * @tc.desc: Test RegisterScrollEventTask
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Event001, TestSize.Level1)
{
    auto event1 = [](Dimension, ScrollState) { return ScrollFrameResult(); };
    auto event2 = [](Dimension, Dimension) { return ScrollInfo(); };
    CreateWithContent([event1, event2](ScrollModelNG model) {
        model.SetOnScrollFrameBegin(event1);
        model.SetOnScrollBegin(event2);
    });

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
    /**
     * @tc.steps: step1. Test event in VERTICAL
     */
    bool isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        NG::ScrollEvent event = [&isTrigger](Dimension, Dimension) { isTrigger = true; };
        model.SetOnScroll(std::move(event));
    });

    /**
     * @tc.steps: step2. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-VERTICAL_LENGTH * TOTAL_NUMBER, SCROLL_FROM_UPDATE);
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
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        NG::ScrollEvent event = [&isTrigger](Dimension, Dimension) { isTrigger = true; };
        model.SetAxis(Axis::HORIZONTAL);
        model.SetOnScroll(std::move(event));
    });

    /**
     * @tc.steps: step5. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->OnScrollCallback(-HORIZONTAL_LENGTH * TOTAL_NUMBER, SCROLL_FROM_UPDATE);
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
    /**
     * @tc.steps: step1. Test event in VERTICAL
     */
    bool isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        NG::ScrollEdgeEvent event = [&isTrigger](ScrollEdge) { isTrigger = true; };
        model.SetOnScrollEdge(std::move(event));
    });

    /**
     * @tc.steps: step2. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-VERTICAL_LENGTH * TOTAL_NUMBER, SCROLL_FROM_UPDATE);
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
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        NG::ScrollEdgeEvent event = [&isTrigger](ScrollEdge) { isTrigger = true; };
        model.SetAxis(Axis::HORIZONTAL);
        model.SetOnScrollEdge(std::move(event));
    });

    /**
     * @tc.steps: step5. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-HORIZONTAL_LENGTH * TOTAL_NUMBER, SCROLL_FROM_UPDATE);
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
    /**
     * @tc.steps: step1. Test onScrollStart event in VERTICAL
     */
    bool isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        OnScrollStartEvent event = [&isTrigger]() { isTrigger = true; };
        model.SetOnScrollStart(std::move(event));
        model.SetOnScrollStop(std::move(event));
        model.SetOnScrollEnd(std::move(event));
    });

    /**
     * @tc.steps: step2. Trigger onScrollStart event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-VERTICAL_LENGTH * TOTAL_NUMBER, SCROLL_FROM_START);
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
    RunMeasureAndLayout(frameNode_); // Trigger onScrollStop
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step5. Set scrollAbort_ to true
     * @tc.expected: onScrollStop would not be trigger
     */
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Resume();
    pattern_->AnimateTo(VERTICAL_LENGTH * TOTAL_NUMBER, 1.f, Curves::LINEAR, false);
    EXPECT_TRUE(pattern_->GetScrollAbort());

    isTrigger = false;
    pattern_->OnScrollEndCallback(); // Trigger onScrollEnd, set scrollStop_ = true;
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    RunMeasureAndLayout(frameNode_); // Trigger onScrollStop
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: ScrollPositionController001
 * @tc.desc: Test ScrollPositionController with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollPositionController001, TestSize.Level1)
{
    CreateWithContent();
    auto controller = pattern_->GetScrollPositionController();
    controller->JumpTo(1, false, ScrollAlign::START, 0);

    /**
     * @tc.steps: step1. Test AnimateTo
     */
    bool animate = controller->AnimateTo(Dimension(VERTICAL_LENGTH * TOTAL_NUMBER), -1.f, Curves::LINEAR, false);
    EXPECT_TRUE(animate);
    animate = controller->AnimateTo(Dimension(1.0, DimensionUnit::PERCENT), 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(animate);

    /**
     * @tc.steps: step2. jump to a position
     * @tc.expected: CurrentOffset would be to the position
     */
    pattern_->DoJump(-VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(-VERTICAL_LENGTH));

    /**
     * @tc.steps: step3. jump to the same position
     * @tc.expected: CurrentOffset would not be change
     */
    pattern_->DoJump(-VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(-VERTICAL_LENGTH));

    /**
     * @tc.steps: step4. ScrollBy 0
     * @tc.expected: CurrentOffset would not change
     */
    CreateWithContent();
    controller = pattern_->GetScrollPositionController();
    controller->ScrollBy(0, 0, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step5. ScrollBy a distance
     * @tc.expected: Scroll by the distance
     */
    controller->ScrollBy(HORIZONTAL_LENGTH, VERTICAL_LENGTH, false);
    EXPECT_TRUE(IsEqualCurrentPosition(-VERTICAL_LENGTH));

    /**
     * @tc.steps: step6. ScrollTo same currentOffset_
     * @tc.expected: JumpToPosition do not SendEventToAccessibility
     */
    pattern_->ScrollTo(-pattern_->currentOffset_);
    EXPECT_TRUE(IsEqualCurrentPosition(-VERTICAL_LENGTH));

    /**
     * @tc.steps: step7. Test GetCurrentPosition
     */
    EXPECT_EQ(controller->GetCurrentPosition(), -VERTICAL_LENGTH);

    /**
     * @tc.steps: step8. Test ScrollEdgeType::SCROLL_NONE
     * @tc.expected: CurrentOffset would not be change
     */
    CreateWithContent();
    controller = pattern_->GetScrollPositionController();
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step9. Test ScrollEdgeType::SCROLL_BOTTOM
     * @tc.expected: CurrentOffset would to be bottom
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualCurrentPosition(DEVICE_HEIGHT - VERTICAL_LENGTH * TOTAL_NUMBER));

    /**
     * @tc.steps: step10. Test ScrollEdgeType::SCROLL_TOP
     * @tc.expected: CurrentOffset would to be top
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step11. Test ScrollPage
     */
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualCurrentPosition(DEVICE_HEIGHT - VERTICAL_LENGTH * TOTAL_NUMBER));

    /**
     * @tc.steps: step12. Test ScrollPage
     */
    controller->ScrollPage(true, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step13. Test IsAtEnd
     */
    EXPECT_FALSE(controller->IsAtEnd());
    UpdateCurrentOffset(-(VERTICAL_LENGTH * TOTAL_NUMBER - DEVICE_HEIGHT));
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: ScrollPositionController002
 * @tc.desc: Test ScrollPositionController with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollPositionController002, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::HORIZONTAL); });
    auto controller = pattern_->GetScrollPositionController();
    controller->JumpTo(1, false, ScrollAlign::START, 0);

    /**
     * @tc.steps: step1. Test AnimateTo
     */
    bool animate = controller->AnimateTo(Dimension(VERTICAL_LENGTH * TOTAL_NUMBER), -1.f, Curves::LINEAR, false);
    EXPECT_TRUE(animate);
    animate = controller->AnimateTo(Dimension(1.0, DimensionUnit::PERCENT), 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(animate);

    /**
     * @tc.steps: step2. jump to a position
     * @tc.expected: CurrentOffset would be to the position
     */
    pattern_->DoJump(-HORIZONTAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(-HORIZONTAL_LENGTH));

    /**
     * @tc.steps: step3. jump to the same position
     * @tc.expected: CurrentOffset would not be change
     */
    pattern_->DoJump(-HORIZONTAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(-HORIZONTAL_LENGTH));

    /**
     * @tc.steps: step4. ScrollBy 0
     * @tc.expected: CurrentOffset would not change
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::HORIZONTAL); });
    controller = pattern_->GetScrollPositionController();
    controller->ScrollBy(0, 0, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step5. ScrollBy a distance
     * @tc.expected: Scroll by the distance
     */
    controller->ScrollBy(HORIZONTAL_LENGTH, VERTICAL_LENGTH, false);
    EXPECT_TRUE(IsEqualCurrentPosition(-HORIZONTAL_LENGTH));

    /**
     * @tc.steps: step6. Test GetCurrentPosition
     */
    EXPECT_EQ(controller->GetCurrentPosition(), -HORIZONTAL_LENGTH);

    /**
     * @tc.steps: step7. Test ScrollEdgeType::SCROLL_NONE
     * @tc.expected: CurrentOffset would not be change
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::HORIZONTAL); });
    controller = pattern_->GetScrollPositionController();
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step8. Test ScrollEdgeType::SCROLL_BOTTOM
     * @tc.expected: CurrentOffset would to be bottom
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualCurrentPosition(DEVICE_WIDTH - HORIZONTAL_LENGTH * TOTAL_NUMBER));

    /**
     * @tc.steps: step9. Test ScrollEdgeType::SCROLL_TOP
     * @tc.expected: CurrentOffset would to be top
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step10. Test ScrollPage
     */
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualCurrentPosition(DEVICE_WIDTH - HORIZONTAL_LENGTH * TOTAL_NUMBER));

    /**
     * @tc.steps: step11. Test ScrollPage
     */
    controller->ScrollPage(true, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step12. Test IsAtEnd
     */
    EXPECT_FALSE(controller->IsAtEnd());
    UpdateCurrentOffset(-(HORIZONTAL_LENGTH * TOTAL_NUMBER - DEVICE_WIDTH));
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: ScrollPositionControlle003
 * @tc.desc: Test ScrollPositionController with Axis::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollPositionControlle003, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::NONE); });
    auto controller = pattern_->GetScrollPositionController();

    /**
     * @tc.steps: step1. Test AnimateTo
     */
    bool animate = controller->AnimateTo(Dimension(VERTICAL_LENGTH * TOTAL_NUMBER), 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(animate);

    /**
     * @tc.steps: step2. ScrollToEdge AnimateTo
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step3. Test ScrollPage
     */
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));
}

/**
 * @tc.name: ScrollBarAnimation001
 * @tc.desc: Test ScrollBar Hover Animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollBarAnimation001, TestSize.Level1)
{
    RSCanvas canvas;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);

    const Offset downInBar = Offset(DEVICE_WIDTH - 1.f, 0.f);
    const Offset moveInBar = Offset(DEVICE_WIDTH - 1.f, 10.f);
    const Offset upInBar = moveInBar;

    /**
     * @tc.steps: step1. Axis::NONE
     * @tc.expected: scrollBar->NeedPaint() is false and scrollBarOverlayModifier is nullptr.
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::NONE); });
    auto paint = pattern_->CreateNodePaintMethod();
    auto scrollPaint = AceType::DynamicCast<ScrollPaintMethod>(paint);
    auto scrollBar = scrollPaint->scrollBar_.Upgrade();
    EXPECT_FALSE(scrollBar->NeedPaint());
    auto modifier = scrollPaint->GetOverlayModifier(&paintWrapper);
    auto scrollBarOverlayModifier = AceType::DynamicCast<ScrollBarOverlayModifier>(modifier);
    EXPECT_EQ(scrollBarOverlayModifier, nullptr);

    /**
     * @tc.steps: step2. Axis::Vertical, test grow animation.
     * @tc.expected: scrollBarOverlayModifier->hoverAnimatingType_ is HoverAnimationType::GROW and the width of.
     * scrollBar is DEFAULT_ACTIVE_WIDTH
     */
    CreateWithContent();
    paint = pattern_->CreateNodePaintMethod();
    scrollPaint = AceType::DynamicCast<ScrollPaintMethod>(paint);
    scrollBar = scrollPaint->scrollBar_.Upgrade();
    scrollBar->SetTouchWidth(Dimension(DEFAULT_TOUCH_WIDTH, DimensionUnit::VP));
    scrollBar->SetActiveWidth(Dimension(DEFAULT_ACTIVE_WIDTH, DimensionUnit::VP));
    scrollBar->SetInactiveWidth(Dimension(DEFAULT_INACTIVE_WIDTH, DimensionUnit::VP));
    scrollBar->SetNormalWidth(Dimension(DEFAULT_NORMAL_WIDTH, DimensionUnit::VP));
    EXPECT_TRUE(scrollBar->NeedPaint());
    modifier = scrollPaint->GetOverlayModifier(&paintWrapper);
    scrollBarOverlayModifier = AceType::DynamicCast<ScrollBarOverlayModifier>(modifier);
    ASSERT_NE(scrollBarOverlayModifier, nullptr);
    DrawingContext drawingContext = { canvas, DEVICE_WIDTH, DEVICE_HEIGHT };
    scrollBarOverlayModifier->onDraw(drawingContext);
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    scrollPaint->UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(scrollBarOverlayModifier->hoverAnimatingType_, HoverAnimationType::GROW);
    EXPECT_EQ(scrollBar->GetActiveRect().Width(), DEFAULT_ACTIVE_WIDTH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);

    /**
     * @tc.steps: step3. Axis::Vertical, test shrink animation.
     * @tc.expected: scrollBarOverlayModifier->hoverAnimatingType_ is HoverAnimationType::SHRINK and the width of
     * scrollBar is DEFAULT_INACTIVE_WIDTH.
     */
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    scrollPaint->UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(scrollBarOverlayModifier->hoverAnimatingType_, HoverAnimationType::SHRINK);
    EXPECT_EQ(scrollBar->GetActiveRect().Width(), DEFAULT_INACTIVE_WIDTH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
}

/**
 * @tc.name: ScrollBarAnimation002
 * @tc.desc: Test ScrollBar Opacity Animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollBarAnimation002, TestSize.Level1)
{
    RSCanvas canvas;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);

    /**
     * @tc.steps: step1. DisplayMode::ON
     * @tc.expected: the opacity of scrollBarOverlayModifier is UINT8_MAX and opacityAnimatingType_ is
     * OpacityAnimationType::NONE.
     */
    CreateWithContent();
    auto paint = pattern_->CreateNodePaintMethod();
    auto scrollPaint = AceType::DynamicCast<ScrollPaintMethod>(paint);
    auto scrollBar = scrollPaint->scrollBar_.Upgrade();
    auto modifier = scrollPaint->GetOverlayModifier(&paintWrapper);
    auto scrollBarOverlayModifier = AceType::DynamicCast<ScrollBarOverlayModifier>(modifier);
    pattern_->SetScrollBar(DisplayMode::ON);
    EXPECT_TRUE(scrollBar->NeedPaint());
    ASSERT_NE(scrollBarOverlayModifier, nullptr);
    EXPECT_EQ(scrollBarOverlayModifier->GetOpacity(), UINT8_MAX);
    EXPECT_EQ(scrollBarOverlayModifier->opacityAnimation_, nullptr);
    EXPECT_EQ(scrollBarOverlayModifier->opacityAnimatingType_, OpacityAnimationType::NONE);

    /**
     * @tc.steps: step2. DisplayMode::AUTO
     * @tc.expected: opacityAnimatingType_ is OpacityAnimationType::DISAPPEAR.
     */
    pattern_->SetScrollBar(DisplayMode::AUTO);
    EXPECT_TRUE(scrollBar->NeedPaint());
    ASSERT_NE(scrollBarOverlayModifier, nullptr);
    scrollPaint->UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(scrollBarOverlayModifier->opacityAnimatingType_, OpacityAnimationType::DISAPPEAR);

    /**
     * @tc.steps: step3. play appear animation.
     * @tc.expected: opacityAnimatingType_ is OpacityAnimationType::APPEAR.
     */
    scrollBar->PlayScrollBarAppearAnimation();
    scrollPaint->UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(scrollBarOverlayModifier->opacityAnimatingType_, OpacityAnimationType::APPEAR);

    /**
     * @tc.steps: step4. DisplayMode::OFF
     * @tc.expected: scrollBar->NeedPaint() is false.
     */
    pattern_->SetScrollBar(DisplayMode::OFF);
    EXPECT_FALSE(scrollBar->NeedPaint());
}

/**
 * @tc.name: ScrollBarAnimation003
 * @tc.desc: Test ScrollBar Adapt Animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollBarAnimation003, TestSize.Level1)
{
    RSCanvas canvas;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);

    CreateWithContent();
    auto paint = pattern_->CreateNodePaintMethod();
    auto scrollPaint = AceType::DynamicCast<ScrollPaintMethod>(paint);
    auto scrollBar = scrollPaint->scrollBar_.Upgrade();
    auto modifier = scrollPaint->GetOverlayModifier(&paintWrapper);
    auto scrollBarOverlayModifier = AceType::DynamicCast<ScrollBarOverlayModifier>(modifier);
    pattern_->SetScrollBar(DisplayMode::ON);
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_TRUE(NearEqual(scrollBar->GetActiveRect().Height(), 666.667f));

    /**
     * @tc.steps: step1. change scrollBar height.
     * @tc.expected: scrollBar->needAdaptAnimation_ is true.
     */
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(480.0, 800.0), Offset::Zero(), 1080.0f);
    scrollPaint->UpdateOverlayModifier(&paintWrapper);
    EXPECT_TRUE(NearEqual(scrollBar->GetActiveRect().Height(), 592.592f));
    EXPECT_TRUE(scrollBar->needAdaptAnimation_);
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

    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING); });
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
 * @tc.name: ScrollTest002
 * @tc.desc: When setting a fixed length and width, verify the related functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest002, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) {
        model.SetAxis(Axis::HORIZONTAL);
        model.SetDisplayMode(static_cast<int>(NG::DisplayMode::OFF));
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
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING); });
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
        model.SetEdgeEffect(EdgeEffect::SPRING);
        CreateContent(VIEW_NUMBER);
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
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING); });
    EXPECT_FALSE(pattern_->IsRestrictBoundary());
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1, SCROLL_FROM_JUMP));
    EXPECT_TRUE(UpdateAndVerifyPosition(1, 0, SCROLL_FROM_BAR));
    EXPECT_TRUE(UpdateAndVerifyPosition(-1, -1, SCROLL_FROM_BAR_FLING));
    EXPECT_TRUE(UpdateAndVerifyPosition(1, 0, SCROLL_FROM_ROTATE));

    pattern_->currentOffset_ = 10.f;
    pattern_->UpdateCurrentOffset(-5.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetScrollBarOutBoundaryExtent(), 5.f);

    pattern_->currentOffset_ = -1000.f;
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetScrollBarOutBoundaryExtent(),
        -pattern_->currentOffset_ - (VERTICAL_LENGTH * TOTAL_NUMBER - DEVICE_HEIGHT));

    pattern_->currentOffset_ = -100.f;
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetScrollBarOutBoundaryExtent(), 0.0f);
}

/**
 * @tc.name: ScrollFadeEffect001
 * @tc.desc: Test the correlation function in ScrollFadeEffect under different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollFadeEffect001, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::FADE); });
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
    const SizeF viewPort(DEVICE_WIDTH, DEVICE_HEIGHT);
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
    // maxExtent: VERTICAL_LENGTH * 2
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(VERTICAL_LENGTH, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-VERTICAL_LENGTH, true), 0.0));

    UpdateCurrentOffset(-VERTICAL_LENGTH);
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(VERTICAL_LENGTH * 2, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-VERTICAL_LENGTH * 2, true), 0.0));

    UpdateCurrentOffset(-VERTICAL_LENGTH);
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(VERTICAL_LENGTH, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-VERTICAL_LENGTH, true), 0.0));

    pattern_->currentOffset_ = VERTICAL_LENGTH;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(VERTICAL_LENGTH, true), -VERTICAL_LENGTH));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), -VERTICAL_LENGTH));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-VERTICAL_LENGTH * 2, true), 0.0));

    pattern_->currentOffset_ = -VERTICAL_LENGTH;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(VERTICAL_LENGTH * 2, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-VERTICAL_LENGTH, true), 0.0));

    // over scroll
    pattern_->currentOffset_ = -VERTICAL_LENGTH * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(VERTICAL_LENGTH * 2, true), VERTICAL_LENGTH));

    // crash the bottom
    pattern_->currentOffset_ = -VERTICAL_LENGTH * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(VERTICAL_LENGTH, true), VERTICAL_LENGTH));
    pattern_->currentOffset_ = -VERTICAL_LENGTH * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(VERTICAL_LENGTH, false), 0.0));
    pattern_->currentOffset_ = -VERTICAL_LENGTH * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(VERTICAL_LENGTH * 3, false), 0.0));
}

/**
 * @tc.name: ScrollFadeEffect002
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollFadeEffect002, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::FADE); });
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
    EXPECT_EQ(fadeController->opacityCeil_, 0.0);
    EXPECT_EQ(fadeController->scaleSizeFloor_, 3.25);
    EXPECT_EQ(fadeController->scaleSizeCeil_, 0.0);
    EXPECT_EQ(fadeController->state_, OverScrollState::RECEDE);

    /**
     * @tc.steps: step5. When OverScrollState is PULL, call the ProcessAbsorb function and callback function in
     *                   fadeController.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    fadeController->ProcessAbsorb(-10.0);
    fadeController->decele_->NotifyListener(100.0);
    EXPECT_EQ(fadeController->opacity_, -29.7);
    EXPECT_EQ(fadeController->scaleSize_, -321.75);
    fadeController->controller_->NotifyStopListener();
    EXPECT_EQ(fadeController->state_, OverScrollState::IDLE);
    fadeController->ProcessAbsorb(100.0);
    fadeController->ProcessPull(1.0, 1.0, 1.0);
    fadeController->decele_->NotifyListener(100.0);
    EXPECT_EQ(param1, 2940.3);
    EXPECT_EQ(param2, 31853.25);
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
 * @tc.desc: Test SetGestureEvent() / SetMouseEvent() / SetHoverEvent()
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
    CreateWithContent([barWidth](ScrollModelNG model) {
        model.SetScrollBarWidth(Dimension(barWidth));
    });
    auto scrollBar = pattern_->GetScrollBar();
    const Offset downInBar = Offset(DEVICE_WIDTH - 1.f, 0.f);
    const Offset moveInBar = Offset(DEVICE_WIDTH - 1.f, 10.f);
    const Offset upInBar = moveInBar;
    const Offset upOutBar = Offset(DEVICE_WIDTH - barWidth - 1.f, 10.f);

    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);

    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step2. Touch in bar and up out of bar
     * @tc.expected: touchAnimator_ is take effect
     */
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upOutBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step3. Touch in bar with SourceType::MOUSE
     * @tc.expected: touchAnimator_ is take effect
     */
    Touch(TouchType::DOWN, downInBar, SourceType::MOUSE);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::MOUSE);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::MOUSE);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step4. Touch in bar with SourceType::TOUCH_PAD
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH_PAD);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH_PAD);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH_PAD);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step5. Touch out of bar
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    Touch(TouchType::DOWN, Offset::Zero(), SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step6. Touch in bar and scrollBar->IsHover() is true
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBar->SetHover(true);
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step7. Mouse in bar and move out of bar (out->in->in->out)
     * @tc.expected: touchAnimator_ is take effect
     */
    CreateWithContent([barWidth](ScrollModelNG model) {
        model.SetScrollBarWidth(Dimension(barWidth));
    });
    scrollBar = pattern_->GetScrollBar();
    const Offset moveOutBar = Offset(DEVICE_WIDTH - barWidth - 1.f, 0.f);
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    Mouse(moveOutBar);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsHover());
    Mouse(moveInBar);
    EXPECT_TRUE(scrollBar->IsHover());
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    Mouse(moveInBar);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    EXPECT_TRUE(scrollBar->IsHover());
    Mouse(moveOutBar);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    EXPECT_FALSE(scrollBar->IsHover());

    /**
     * @tc.steps: step8. (out->in->in->out) and scrollBar->IsPressed() is true
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBar->SetPressed(true);
    Mouse(moveOutBar);
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsHover());
    Mouse(moveInBar);
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    EXPECT_TRUE(scrollBar->IsHover());
    Mouse(moveInBar);
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    EXPECT_TRUE(scrollBar->IsHover());
    Mouse(moveOutBar);
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsHover());

    /**
     * @tc.steps: step9. Mouse in bar and move out of component containing bar
     * @tc.expected: HoverAnimation is take effect
     */
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    Hover(true);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    scrollBar->SetHover(false);
    Hover(false);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    scrollBar->SetHover(true);
    scrollBar->SetPressed(true);
    Hover(false);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    scrollBar->SetHover(true);
    scrollBar->SetPressed(false);
    Hover(false);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
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
    const float ratio = static_cast<float>(VIEW_NUMBER) / TOTAL_NUMBER;
    CreateWithContent([barWidth](ScrollModelNG model) {
        model.SetScrollBarWidth(Dimension(barWidth));
    });
    auto scrollBar = pattern_->GetScrollBar();

    Rect rect = scrollBar->touchRegion_;
    Rect expectRect = Rect(
        DEVICE_WIDTH - barWidth,
        0.f,
        barWidth,
        DEVICE_HEIGHT * ratio
    );
    EXPECT_TRUE(IsEqual(rect, expectRect));

    UpdateCurrentOffset(-VERTICAL_LENGTH);
    rect = scrollBar->touchRegion_;
    expectRect = Rect(
        DEVICE_WIDTH - barWidth,
        VERTICAL_LENGTH * ratio,
        barWidth,
        DEVICE_HEIGHT * ratio
    );
    EXPECT_TRUE(IsEqual(rect, expectRect));

    /**
     * @tc.steps: step2. Test Bar in HORIZONTAL
     * @tc.expected: Verify bar rect
     */
    CreateWithContent([barWidth](ScrollModelNG model) {
        model.SetAxis(Axis::HORIZONTAL);
        model.SetScrollBarWidth(Dimension(barWidth));
    });
    scrollBar = pattern_->GetScrollBar();

    rect = scrollBar->touchRegion_;
    expectRect = Rect(
        0.f,
        DEVICE_HEIGHT - barWidth,
        DEVICE_WIDTH * ratio,
        barWidth
    );
    EXPECT_TRUE(IsEqual(rect, expectRect));

    UpdateCurrentOffset(-HORIZONTAL_LENGTH);
    rect = scrollBar->touchRegion_;
    expectRect = Rect(
        HORIZONTAL_LENGTH * ratio,
        DEVICE_HEIGHT - barWidth,
        DEVICE_WIDTH * ratio,
        barWidth
    );
    EXPECT_TRUE(IsEqual(rect, expectRect));
}

/**
 * @tc.name: ScrollBar004
 * @tc.desc: Test ScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollBar004, TestSize.Level1)
{
    const float barWidth = 10.f;
    CreateWithContent([barWidth](ScrollModelNG model) {
        model.SetScrollBarWidth(Dimension(barWidth));
    });
    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->SetShapeMode(ShapeMode::ROUND);
    EXPECT_FALSE(scrollBar->InBarTouchRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarHoverRegion(Point(0, 0)));
    scrollBar->FlushBarWidth();

    scrollBar->SetDisplayMode(DisplayMode::OFF);
    EXPECT_FALSE(scrollBar->InBarTouchRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarHoverRegion(Point(0, 0)));

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
 * @tc.name: ScrollBar005
 * @tc.desc: Test CalcReservedHeight()
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollBar005, TestSize.Level1)
{
    CreateWithContent();
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
    LayoutConstraint.parentIdealSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.percentReference = { DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
    auto scrollSize = frameNode_->GetGeometryNode()->GetFrameSize();
    auto expectSize = SizeF(DEVICE_WIDTH, VERTICAL_LENGTH * TOTAL_NUMBER);
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
    RunMeasureAndLayout(frameNode_);
    auto col = frameNode_->GetChildAtIndex(0);
    auto colNode = AceType::DynamicCast<FrameNode>(col);
    auto colOffset = colNode->GetGeometryNode()->GetMarginFrameOffset();
    auto expectOffset = OffsetF(0, 0);
    EXPECT_EQ(colOffset, expectOffset) << "colOffset: " << colOffset.ToString()
                                       << " expectOffset: " << expectOffset.ToString();
}

/**
 * @tc.name: OnScrollCallback001
 * @tc.desc: Test OnScrollCallback that has no effect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, OnScrollCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Axis::NONE and SCROLL_FROM_UPDATE
     * @tc.expected: Do nothing
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::NONE); });
    EXPECT_FALSE(OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_UPDATE));

    /**
     * @tc.steps: step2. animator_ is running and SCROLL_FROM_UPDATE
     * @tc.expected: Do nothing
     */
    CreateWithContent();
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Resume();
    EXPECT_FALSE(OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_UPDATE));
}

/**
 * @tc.name: OnScrollCallback002
 * @tc.desc: Test OnScrollCallback about trigger FireOnScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, OnScrollCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. no animator and SCROLL_FROM_START
     * @tc.expected: Trigger FireOnScrollStart()
     */
    bool isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        OnScrollStartEvent event = [&isTrigger]() { isTrigger = true; };
        model.SetOnScrollStart(std::move(event));
    });
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_START);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. animator is Stopped and SCROLL_FROM_START
     * @tc.expected: Trigger FireOnScrollStart()
     */
    isTrigger = false;
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Stop();
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_START);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step3. animator is running and SCROLL_FROM_START
     * @tc.expected: because of scrollAbort_ is true, would not trigger event, and animator stop()
     */
    isTrigger = false;
    pattern_->animator_->Resume();
    auto scrollable = pattern_->scrollableEvent_->GetScrollable();
    auto onScrollCallback = scrollable->callback_;
    onScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->animator_->IsStopped());
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: OnScrollCallback003
 * @tc.desc: Test OnScrollCallback about AdjustOffset/UpdateCurrentOffset when scrollableDistance_ bigger than 0
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, OnScrollCallback003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the content that total size is bigger than Scroll Component
     * @tc.expected: The scrollableDistance_ is two of VERTICAL_LENGTH
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING); });
    EXPECT_EQ(pattern_->scrollableDistance_, VERTICAL_LENGTH * 2);

    /**
     * @tc.steps: step2. scroll to above of content
     * @tc.expected: friction is not effected
     */
    OnScrollCallback(VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(VERTICAL_LENGTH));

    /**
     * @tc.steps: step3. Continue scroll up
     * @tc.expected: friction is effected
     */
    OnScrollCallback(VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    double currentOffset = pattern_->GetCurrentPosition();
    EXPECT_LT(currentOffset, VERTICAL_LENGTH * 2);

    /**
     * @tc.steps: step4. Scroll down
     * @tc.expected: friction is not effected
     */
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(currentOffset - VERTICAL_LENGTH));

    /**
     * @tc.steps: step5. Scroll to bottom for test other condition
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(IsEqualCurrentPosition(-VERTICAL_LENGTH * 2));

    /**
     * @tc.steps: step6. scroll to below of content
     * @tc.expected: friction is not effected
     */
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(-VERTICAL_LENGTH * 3));

    /**
     * @tc.steps: step7. Continue scroll down
     * @tc.expected: friction is effected
     */
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    currentOffset = pattern_->GetCurrentPosition();
    EXPECT_LT(currentOffset, -VERTICAL_LENGTH * 3);
    EXPECT_GT(currentOffset, -VERTICAL_LENGTH * 4);

    /**
     * @tc.steps: step8. Scroll up
     * @tc.expected: friction is not effected
     */
    OnScrollCallback(VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(currentOffset + VERTICAL_LENGTH));

    /**
     * @tc.steps: step9. scroll to middle of content
     * @tc.expected: friction is not effected
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0);
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(-VERTICAL_LENGTH));
}

/**
 * @tc.name: OnScrollCallback004
 * @tc.desc: Test OnScrollCallback about AdjustOffset/UpdateCurrentOffset when scrollableDistance_ is 0
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, OnScrollCallback004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the content that total size is not bigger than Scroll Component
     * @tc.expected: The scrollableDistance_ is 0
     */
    Create([](ScrollModelNG model) {
        model.SetEdgeEffect(EdgeEffect::SPRING);
        CreateContent(VIEW_NUMBER);
    });
    EXPECT_EQ(pattern_->scrollableDistance_, 0);

    /**
     * @tc.steps: step2. scroll to above of content
     * @tc.expected: friction is not effected
     */
    OnScrollCallback(VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(VERTICAL_LENGTH));

    /**
     * @tc.steps: step3. Continue scroll up
     * @tc.expected: friction is effected
     */
    OnScrollCallback(VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    double currentOffset = pattern_->GetCurrentPosition();
    EXPECT_LT(currentOffset, VERTICAL_LENGTH * 2);

    /**
     * @tc.steps: step4. Scroll down
     * @tc.expected: friction is not effected
     */
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(currentOffset - VERTICAL_LENGTH));

    /**
     * @tc.steps: step5. Scroll to bottom for test other condition
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step6. scroll to below of content
     * @tc.expected: friction is not effected
     */
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(-VERTICAL_LENGTH));

    /**
     * @tc.steps: step7. Continue scroll down
     * @tc.expected: friction is effected
     */
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    currentOffset = pattern_->GetCurrentPosition();
    EXPECT_LT(currentOffset, -VERTICAL_LENGTH * 1);
    EXPECT_GT(currentOffset, -VERTICAL_LENGTH * 2);

    /**
     * @tc.steps: step8. Scroll up
     * @tc.expected: friction is not effected
     */
    OnScrollCallback(VERTICAL_LENGTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(currentOffset + VERTICAL_LENGTH));
}

/**
 * @tc.name: OnScrollCallback005
 * @tc.desc: Test AdjustOffset that return
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, OnScrollCallback005, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING); });

    /**
     * @tc.steps: step1. The delta is 0
     * @tc.expected: AdjustOffset return
     */
    OnScrollCallback(0, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step2. The source is SCROLL_FROM_ANIMATION
     * @tc.expected: AdjustOffset return
     */
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_ANIMATION);
    EXPECT_TRUE(IsEqualCurrentPosition(-VERTICAL_LENGTH));

    /**
     * @tc.steps: step3. The source is SCROLL_FROM_ANIMATION_SPRING
     * @tc.expected: AdjustOffset return
     */
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(IsEqualCurrentPosition(-VERTICAL_LENGTH * 2));

    /**
     * @tc.steps: step4. The viewPortLength_ is 0
     * @tc.expected: AdjustOffset return
     */
    ScrollModelNG model;
    model.Create();
    model.SetEdgeEffect(EdgeEffect::SPRING);
    GetInstance();
    RunMeasureAndLayout(frameNode_, -1, -1);
    OnScrollCallback(-VERTICAL_LENGTH, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(IsEqualCurrentPosition(-VERTICAL_LENGTH));
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
    EXPECT_TRUE(ScrollToNode(10, -1));
    EXPECT_TRUE(ScrollToNode(11, -2));
    EXPECT_TRUE(ScrollToNode(5, -2));
    EXPECT_TRUE(ScrollToNode(0, 0));

    /**
     * @tc.steps: step2. ScrollToNode in HORIZONTAL
     * @tc.expected: currentOffset_ is correct
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::HORIZONTAL); });
    EXPECT_TRUE(ScrollToNode(5, 0));
    EXPECT_TRUE(ScrollToNode(10, -1));
    EXPECT_TRUE(ScrollToNode(11, -2));
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

    OverScrollOffset offset = pattern_->GetOverScrollOffset(VERTICAL_LENGTH);
    OverScrollOffset expectOffset = { VERTICAL_LENGTH, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-VERTICAL_LENGTH);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->currentOffset_ = -VERTICAL_LENGTH;
    offset = pattern_->GetOverScrollOffset(VERTICAL_LENGTH * 2);
    expectOffset = { VERTICAL_LENGTH, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-VERTICAL_LENGTH * 2);
    expectOffset = { 0, -VERTICAL_LENGTH };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->currentOffset_ = -VERTICAL_LENGTH * 2;
    offset = pattern_->GetOverScrollOffset(VERTICAL_LENGTH);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-VERTICAL_LENGTH);
    expectOffset = { 0, -VERTICAL_LENGTH };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->currentOffset_ = VERTICAL_LENGTH;
    offset = pattern_->GetOverScrollOffset(VERTICAL_LENGTH);
    expectOffset = { VERTICAL_LENGTH, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-VERTICAL_LENGTH * 2);
    expectOffset = { -VERTICAL_LENGTH, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    pattern_->currentOffset_ = -VERTICAL_LENGTH * 3;
    offset = pattern_->GetOverScrollOffset(VERTICAL_LENGTH * 2);
    expectOffset = { 0, VERTICAL_LENGTH };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-VERTICAL_LENGTH);
    expectOffset = { 0, -VERTICAL_LENGTH };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
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
    UpdateCurrentOffset(-VERTICAL_LENGTH);
    accessibilityProperty_->ResetSupportAction();
    expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);

    /**
     * @tc.steps: step4. scroll to bottom
     * @tc.expected: action is correct
     */
    UpdateCurrentOffset(-VERTICAL_LENGTH);
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
    ASSERT_NE(pattern_->animator_, nullptr);
    pattern_->animator_ = nullptr;
    accessibilityProperty_->actionScrollBackwardImpl_();
    ASSERT_NE(pattern_->animator_, nullptr);

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
     * @tc.expected: shouled be more than 0.0,if out of range,should be default value.
     */
    double friction = -1;
    ScrollModelNG scrollModelNG_1;
    scrollModelNG_1.Create();
    scrollModelNG_1.SetFriction(friction);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);

    /**
     * @tc.steps: step1. set friction more than 0
     * @tc.expected: friction shouled be more than 0.0,if out of range,should be default value.
     */
    friction = 10;
    ScrollModelNG scrollModelNG_2;
    scrollModelNG_2.Create();
    scrollModelNG_2.SetFriction(friction);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
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

    // snapOffsets_: {0, -10, -20, -30, -160}
    std::pair<bool, bool> enableSnapToSide = {false, false};
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

    enableSnapToSide = {true, false};
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

    // snapOffsets_: {-5, -15, -145, -155}
    snapPaginations = {};
    CreateSnapScroll(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(10.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-(VERTICAL_SCROLLABLE_DISTANCE + 10.f)).has_value());
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
    Dimension intervalSize = Dimension(10.f / DEVICE_HEIGHT, DimensionUnit::PERCENT);
    std::vector<Dimension> snapPaginations = {
        Dimension(0.f, DimensionUnit::PERCENT),
        Dimension(10.f / DEVICE_HEIGHT, DimensionUnit::PERCENT),
        Dimension(20.f / DEVICE_HEIGHT, DimensionUnit::PERCENT),
        Dimension(30.f / DEVICE_HEIGHT, DimensionUnit::PERCENT),
        Dimension((VERTICAL_SCROLLABLE_DISTANCE + 10.f) / DEVICE_HEIGHT, DimensionUnit::PERCENT),
    };

    // snapOffsets_: {0, -10, -20, -30, -160}
    std::pair<bool, bool> enableSnapToSide = {false, false};
    CreateSnapScroll(ScrollSnapAlign::CENTER, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(0.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-20.f).has_value());
    pattern_->currentOffset_ = -20.f;
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(0.f).has_value());

    enableSnapToSide = {true, false};
    CreateSnapScroll(ScrollSnapAlign::CENTER, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-40.f).has_value());
    pattern_->currentOffset_ = 20.f;
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-40.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(0.f).has_value());

    // snapOffsets_: {-5, -15, -145, -155}
    snapPaginations = {};
    CreateSnapScroll(ScrollSnapAlign::CENTER, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(10.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-(VERTICAL_SCROLLABLE_DISTANCE + 10.f)).has_value());
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

    // snapOffsets_: {0, -10, -20, -30, -160}
    std::pair<bool, bool> enableSnapToSide = {false, false};
    CreateSnapScroll(ScrollSnapAlign::END, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(0.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-20.f).has_value());
    pattern_->currentOffset_ = -20.f;
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(0.f).has_value());

    enableSnapToSide = {true, false};
    CreateSnapScroll(ScrollSnapAlign::END, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-40.f).has_value());
    pattern_->currentOffset_ = 20.f;
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-40.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(0.f).has_value());

    // snapOffsets_: {-5, -15, -145, -155}
    snapPaginations = {};
    CreateSnapScroll(ScrollSnapAlign::END, intervalSize, snapPaginations, enableSnapToSide);
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(10.f).has_value());
    EXPECT_FALSE(pattern_->CalePredictSnapOffset(-(VERTICAL_SCROLLABLE_DISTANCE + 10.f)).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-2.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-158.f).has_value());
    EXPECT_TRUE(pattern_->CalePredictSnapOffset(-10.f).has_value());
}

/**
 * @tc.name: Drag001
 * @tc.desc: Test snap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Drag001, TestSize.Level1)
{
    CreateWithContent();
    auto scrollBar = pattern_->GetScrollBar();
    GestureEvent info;
    scrollBar->HandleDragStart(info);
    EXPECT_TRUE(scrollBar->isDriving_);
    scrollBar->HandleDragUpdate(info);
    info.SetMainVelocity(0.0);
    scrollBar->HandleDragEnd(info);
    EXPECT_FALSE(scrollBar->isDriving_);
    info.SetMainVelocity(1000.0);
    scrollBar->HandleDragEnd(info);
}

/**
 * @tc.name: Distributed001
 * @tc.desc: Test the distributed capability of Scroll.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, Distributed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Scroll node
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
     * @tc.steps: step1. Init Scroll.
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
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0),
        Rect(0, 0, TOTAL_NUMBER * HORIZONTAL_LENGTH, FILL_LENGTH.Value() * DEVICE_HEIGHT)));
}
} // namespace OHOS::Ace::NG
