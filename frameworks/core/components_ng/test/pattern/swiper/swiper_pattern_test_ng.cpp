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

#define private public
#define protected public
#include "core/animation/animator.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float SWIPER_IDEAL_WIDTH = 720.0f;
constexpr float SWIPER_IDEAL_HEIGHT = 1200.0f;
constexpr int32_t CURRENT_INDEX = 1;
constexpr int32_t CACHED_COUNT = 1;
constexpr int32_t DISPLAY_COUNT = 3;
constexpr Dimension ITEM_SPACE = Dimension(20, DimensionUnit::PX);
constexpr Dimension PREVIOUS_MARGIN = Dimension(50, DimensionUnit::PX);
constexpr Dimension NEXT_MARGIN = Dimension(50, DimensionUnit::PX);
constexpr Dimension NEXT_MARGIN_EXTRA_LARGE = Dimension(600, DimensionUnit::PX);
constexpr int32_t MAX_NODE_NUMBER = 3;
constexpr double MAIN_DELTA = 20.0;
constexpr float GEOMETRY_WIDTH = 10.0f;
constexpr float GEOMETRY_HEIGHT = 10.0f;
constexpr int32_t SWIPER_DEFAULT_INDEX = 1;
} // namespace

class SwiperPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void CreateChildWrapperAppendToHostWrapper(
        int32_t startIndex, int32_t endIndex, const RefPtr<LayoutWrapper>& hostWrapper);
    RefPtr<FrameNode> CreateSwiperFrameNode();
};

RefPtr<FrameNode> SwiperPatternTestNg::CreateSwiperFrameNode()
{
    SwiperModelNG swiper;
    swiper.Create();
    return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
}

void SwiperPatternTestNg::CreateChildWrapperAppendToHostWrapper(
    int32_t startIndex, int32_t endIndex, const RefPtr<LayoutWrapper>& hostWrapper)
{
    ASSERT_NE(hostWrapper, nullptr);
    for (int32_t index = startIndex; index <= endIndex; index++) {
        auto childPattern = AceType::MakeRefPtr<Pattern>();
        auto childFrameNode = FrameNode::CreateFrameNode(BOX_NAME, index, childPattern);
        ASSERT_NE(childFrameNode, nullptr);
        auto host = hostWrapper->GetHostNode();
        ASSERT_NE(host, nullptr);
        host->AddChild(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(childGeometryNode, nullptr);
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        ASSERT_NE(childLayoutProperty, nullptr);
        childLayoutProperty->UpdateAspectRatio(1.0f);
        RefPtr<LayoutWrapper> childLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
        auto layoutAlgorithm = childPattern->CreateLayoutAlgorithm();
        ASSERT_NE(layoutAlgorithm, nullptr);
        childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
        hostWrapper->AppendChild(std::move(childLayoutWrapper));
    }
}

/**
 * @tc.name: SwiperEvent001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperEvent001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoList;
    infoList.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoList;
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);

    touchEventInfo.touches_.begin()->SetTouchType(TouchType::UP);
    pattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::CANCEL);
    pattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::MOVE);
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperEvent002
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperEvent002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    pattern->InitPanEvent();
    EXPECT_EQ(pattern->direction_, Axis::HORIZONTAL);
    pattern->touchEvent_ = nullptr;
    pattern->InitTouchEvent();
    TouchEventFunc callback = [](TouchEventInfo& info) {};
    pattern->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback));
    pattern->InitTouchEvent();
    EXPECT_TRUE(pattern->touchEvent_);

    EXPECT_TRUE(pattern->panEvent_);
    GestureEvent gestureEvent = GestureEvent();
    gestureEvent.inputEventType_ = InputEventType::AXIS;
    pattern->panEvent_->actionStart_(gestureEvent);
    pattern->panEvent_->actionUpdate_(gestureEvent);
    pattern->panEvent_->actionEnd_(gestureEvent);
    gestureEvent.inputEventType_ = InputEventType::TOUCH_SCREEN;
    CommonFunc func = []() {};
    pattern->swiperController_->SetTabBarFinishCallback(func);
    pattern->panEvent_->actionStart_(gestureEvent);
    pattern->panEvent_->actionEnd_(gestureEvent);
    pattern->swiperController_->SetRemoveSwiperEventCallback(func);
    pattern->panEvent_->actionStart_(gestureEvent);
    pattern->panEvent_->actionEnd_(gestureEvent);
    pattern->panEvent_->actionCancel_();
    EXPECT_TRUE(pattern->swiperController_->tabBarFinishCallback_);
    EXPECT_TRUE(pattern->swiperController_->removeSwiperEventCallback_);
}

/**
 * @tc.name: SwiperUtilsTest001
 * @tc.desc: Test Swiper measure and layout function, set prevMargin and nextMargin property is 50_px.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest001, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    RefPtr<GeometryNode> swiperGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(swiperGeometryNode, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    swiperLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    swiperLayoutProperty->UpdateContentConstraint();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(swiperFrameNode, swiperGeometryNode, swiperLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    int32_t displaycount = 3;
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    swiperLayoutProperty->UpdateDisplayCount(displaycount);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperPaintProperty->UpdateLoop(false);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm));
    int32_t startIndex = 0;
    int32_t endIndex = 4;
    swiperLayoutAlgorithm->SetTotalCount(endIndex - startIndex);
    CreateChildWrapperAppendToHostWrapper(startIndex, endIndex, layoutWrapper);
    swiperLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    swiperLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    auto calcIdealLength =
        (SWIPER_IDEAL_WIDTH - PREVIOUS_MARGIN.Value() - NEXT_MARGIN.Value() - ITEM_SPACE.Value() * (displaycount + 1)) /
        displaycount;

    for (int32_t index = startIndex; index < endIndex; index++) {
        auto childLayout = layoutWrapper->GetOrCreateChildByIndex(index);
        ASSERT_NE(childLayout, nullptr);
        auto mainDirectionOffset = OffsetF(50.0f + 20.0f, 0.0f) +
                                   OffsetF(swiperLayoutAlgorithm->GetPagesOffsetTimes(index) * 200, 0);
        EXPECT_EQ(childLayout->GetGeometryNode()->GetFrameSize(), SizeF(calcIdealLength, calcIdealLength));
        EXPECT_EQ(childLayout->GetGeometryNode()->GetMarginFrameOffset(), mainDirectionOffset);
    }
}

/**
 * @tc.name: SwiperUtilsTest002
 * @tc.desc: Verify the CreateChildConstraint function when DisplayCount is -1.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest002, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateDisplayCount(-1);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest003
 * @tc.desc: Verify the CreateChildConstraint function when DisplayMode is AUTO_LINEAR.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest003, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest004
 * @tc.desc: Verify the CreateChildConstraint function when NextMargin is normal and abnormal.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest004, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);

    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN_EXTRA_LARGE);
    result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest005
 * @tc.desc: Verify the CreateChildConstraint function does not set a value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest005, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest006
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest006, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);

    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN_EXTRA_LARGE);
    result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest007
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL and does not set value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest007, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest008
 * @tc.desc: Verify the CreateChildConstraint function when Direction is FREE.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperUtilsTest008, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::FREE);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperInit001
 * @tc.desc: InitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperInit001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto indicatorNode =
        FrameNode::GetOrCreateFrameNode("Indicator", 0, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    swiperNode->children_.clear();
    swiperNode->AddChild(indicatorNode);
    pattern->InitIndicator();
    EXPECT_EQ(swiperNode->children_.size(), 2);
    swiperNode->children_.clear();
    indicatorNode = FrameNode::GetOrCreateFrameNode(
        "SwiperIndicator", 0, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    swiperNode->AddChild(indicatorNode);
    pattern->InitIndicator();
    EXPECT_EQ(swiperNode->children_.size(), 1);
}

/**
 * @tc.name: SwiperFunc001
 * @tc.desc: OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperFunc001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    KeyEvent event = KeyEvent();
    event.action = KeyAction::CLICK;
    EXPECT_FALSE(pattern->OnKeyEvent(event));
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(pattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(pattern->OnKeyEvent(event));
}

/**
 * @tc.name: SwiperFunc002
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperFunc002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    bool isVisible = false;
    pattern->OnVisibleChange(isVisible);
    pattern->isInit_ = false;
    pattern->OnWindowHide();
    pattern->OnVisibleChange(isVisible);
    EXPECT_FALSE(pattern->isVisible_);
    isVisible = true;
    pattern->OnWindowShow();
    pattern->OnVisibleChange(isVisible);
    EXPECT_TRUE(pattern->isVisible_);
}

/**
 * @tc.name: SwiperFunc003
 * @tc.desc: OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperFunc003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    pattern->OnIndexChange();
    int32_t nodeId = 0;
    while (nodeId < MAX_NODE_NUMBER) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(
            "SwiperIndicator", nodeId, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        swiperNode->AddChild(indicatorNode);
        nodeId++;
    }
    pattern->OnIndexChange();
    EXPECT_EQ(pattern->TotalCount(), MAX_NODE_NUMBER - 1);
}

/**
 * @tc.name: SwiperFunc004
 * @tc.desc: HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperFunc004, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    pattern->InitPanEvent();
    EXPECT_EQ(pattern->direction_, Axis::HORIZONTAL);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(
        "SwiperIndicator", 0, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    swiperNode->AddChild(indicatorNode);
    EXPECT_TRUE(swiperNode->geometryNode_);
    swiperNode->geometryNode_->frame_.SetOffset(OffsetF(0, 0));
    EXPECT_TRUE(pattern->panEvent_);
    GestureEvent gestureEvent = GestureEvent();
    gestureEvent.SetMainDelta(MAIN_DELTA);
    gestureEvent.SetLocalLocation(Offset(0, 0));
    gestureEvent.inputEventType_ = InputEventType::TOUCH_SCREEN;
    pattern->panEvent_->actionUpdate_(gestureEvent);

    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    swiperPaintProperty->propLoop_ = false;
    swiperNode->geometryNode_->frame_.SetSize(SizeF(GEOMETRY_WIDTH, GEOMETRY_HEIGHT));
    // Swiper has reached boundary.
    swiperNode->geometryNode_->frame_.SetSize(SizeF(0, 0));
    pattern->panEvent_->actionUpdate_(gestureEvent);
    swiperPaintProperty->propEdgeEffect_ = EdgeEffect::FADE;
    pattern->panEvent_->actionUpdate_(gestureEvent);
    swiperPaintProperty->propEdgeEffect_ = EdgeEffect::NONE;
    pattern->panEvent_->actionUpdate_(gestureEvent);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Swiper Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper and initialize related properties.
     */
    SwiperModelNG swiperModelNG;
    swiperModelNG.Create();

    /**
     * @tc.steps: step2. Get swiper frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperPaintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    swiperPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get swiper accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto swiperAccessibilityProperty = frameNode->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    ASSERT_NE(swiperAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When swiper is not scrollable, call the callback function in swiperAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(swiperAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(swiperAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When swiper is scrollable, call the callback function in swiperAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    swiperPaintProperty->UpdateLoop(true);
    EXPECT_TRUE(swiperAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(swiperAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: SwiperModelNg001
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperModelNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SwiperModelNG.
     */
    SwiperModelNG swiperModelNG;
    swiperModelNG.Create();

    /**
     * @tc.steps: step2. Create frameNode, pattern.
     */
    auto swiperFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    /**
     * @tc.steps: step3.1. Test SetIndex function.
     * @tc.expected: swiperLayoutProperty->GetIndex() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetIndex(SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperLayoutProperty->GetIndex(), SWIPER_DEFAULT_INDEX);

    /**
     * @tc.steps: step3.2. Test SetDisplayMode function.
     * @tc.expected: swiperLayoutProperty->GetDisplayMode() is equal to swiperDisplayMode.
     */
    swiperModelNG.SetDisplayMode(SwiperDisplayMode::STRETCH);
    EXPECT_EQ(swiperLayoutProperty->GetDisplayMode(), SwiperDisplayMode::STRETCH);

    /**
     * @tc.steps: step3.3. Test SetDisplayCount function.
     * @tc.expected:DisplayCount = -1 swiperLayoutProperty->GetDisplayCount() is equal to SWIPER_DEFAULT_INDEX.
     * @tc.expected:DisplayCount = 1 swiperLayoutProperty->GetDisplayCount() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetDisplayCount(-SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperLayoutProperty->GetDisplayCount(), SWIPER_DEFAULT_INDEX);
    swiperModelNG.SetDisplayCount(SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperLayoutProperty->GetDisplayCount(), SWIPER_DEFAULT_INDEX);

    /**
     * @tc.steps: step3.4. Test SetShowIndicator function.
     * @tc.expected: swiperLayoutProperty->GetIndex() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetShowIndicator(true);
    EXPECT_TRUE(swiperLayoutProperty->GetShowIndicator());

    /**
     * @tc.steps: step3.5. Test SetItemSpace function.
     * @tc.expected: swiperLayoutProperty->GetItemSpace() is equal to dimension.
     */
    auto dimension = Dimension(-1.0);
    swiperModelNG.SetItemSpace(dimension);
    EXPECT_EQ(swiperLayoutProperty->GetItemSpace(), dimension);

    /**
     * @tc.steps: step3.6. Test SetCachedCount function.
     * @tc.expected:DisplayCount = -1 swiperLayoutProperty->SetCachedCount() is equal to SWIPER_DEFAULT_INDEX.
     * @tc.expected:DisplayCount = 1 swiperLayoutProperty->SetCachedCount() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetCachedCount(-SWIPER_DEFAULT_INDEX);
    swiperModelNG.SetCachedCount(SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperLayoutProperty->GetCachedCount(), SWIPER_DEFAULT_INDEX);

    /**
     * @tc.steps: step3.7. Test SetIsIndicatorCustomSize function.
     * @tc.expected: swiperPattern->IsIndicatorCustomSize() is equal to true.
     */
    swiperModelNG.SetIsIndicatorCustomSize(true);
    EXPECT_TRUE(swiperPattern->IsIndicatorCustomSize());

    /**
     * @tc.steps: step3.8. Test SetAutoPlay function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlay() is equal to true.
     */
    swiperModelNG.SetAutoPlay(true);
    EXPECT_TRUE(swiperPaintProperty->GetAutoPlay());

    /**
     * @tc.steps: step3.9. Test SetAutoPlayInterval function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlayInterval() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetAutoPlayInterval(SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperPaintProperty->GetAutoPlayInterval(), SWIPER_DEFAULT_INDEX);

    /**
     * @tc.steps: step3.10. Test SetDuration function.
     * @tc.expected: SwiperPaintProperty->GetDuration() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetDuration(SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperPaintProperty->GetDuration(), SWIPER_DEFAULT_INDEX);
}

/**
 * @tc.name: SwiperModelNg002
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperModelNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SwiperModelNG.
     */
    SwiperModelNG swiperModelNG;
    swiperModelNG.Create();

    /**
     * @tc.steps: step2. Create frameNode, pattern.
     */
    auto swiperFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    auto eventHub = swiperFrameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step3.1. Test SetLoop function.
     * @tc.expected: SwiperPaintProperty->GetLoop() is true.
     */
    swiperModelNG.SetLoop(true);
    EXPECT_TRUE(swiperPaintProperty->GetLoop());

    /**
     * @tc.steps: step3.2. Test SetEnabled function.
     * @tc.expected: SwiperPaintProperty->GetEnabled() is true.
     */
    swiperModelNG.SetEnabled(true);
    EXPECT_TRUE(swiperPaintProperty->GetEnabled());

    /**
     * @tc.steps: step3.3. Test SetDisableSwipe function.
     * @tc.expected: SwiperPaintProperty->GetDisableSwipe() is true.
     */
    swiperModelNG.SetDisableSwipe(true);
    EXPECT_TRUE(swiperPaintProperty->GetDisableSwipe());

    /**
     * @tc.steps: step3.4. Test SetEdgeEffect function.
     * @tc.expected: SwiperPaintProperty->GetEdgeEffect() is true.
     */
    swiperModelNG.SetEdgeEffect(EdgeEffect::FADE);
    EXPECT_EQ(swiperPaintProperty->GetEdgeEffect(), EdgeEffect::FADE);

    /**
     * @tc.steps: step3.5. Test SetOnChange function.
     * @tc.expected:swiperPattern->changeEvent_ not null.
     */
    auto onChange = [](const BaseEventInfo* info) {};
    swiperModelNG.SetOnChange(std::move(onChange));
    EXPECT_NE(swiperPattern->changeEvent_, nullptr);

    /**
     * @tc.steps: step3.6. Test SetOnAnimationStart function.
     * @tc.expected:swiperPattern->animationStartEvent_ not null.
     */
    auto onAnimationStart = [](const BaseEventInfo* info) {};
    swiperModelNG.SetOnAnimationStart(std::move(onAnimationStart));
    EXPECT_NE(eventHub->animationStartEvent_, nullptr);

    /**
     * @tc.steps: step3.7. Test SetOnAnimationEnd function.
     * @tc.expected:swiperPattern->animationEndEvent_ not null.
     */
    auto onAnimationEnd = [](const BaseEventInfo* info) {};
    swiperModelNG.SetOnAnimationEnd(std::move(onAnimationEnd));
    EXPECT_NE(eventHub->animationEndEvent_, nullptr);
}

/**
 * @tc.name: SwiperModelNg003
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperModelNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SwiperModelNG.
     */
    SwiperModelNG swiperModelNG;
    swiperModelNG.Create();

    /**
     * @tc.steps: step2. Create frameNode, pattern.
     */
    auto swiperFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    auto eventHub = swiperFrameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step3.1. Test SetIndicatorStyle function.
     * @tc.expected: SwiperPaintProperty->swiperParameters_->colorVal is swiperParameters.colorVal.
     */
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    swiperModelNG.SetIndicatorStyle(swiperParameters);
    EXPECT_EQ(swiperPattern->swiperParameters_->colorVal, swiperParameters.colorVal);

    /**
     * @tc.steps: step3.2. Test SetPreviousMargin function.
     * @tc.expected: swiperPaintProperty->GetPrevMargin() is equal to dimension.
     */
    auto dimension = Dimension(-1.0);
    swiperModelNG.SetPreviousMargin(dimension);
    EXPECT_EQ(swiperLayoutProperty->GetPrevMargin(), dimension);

    /**
     * @tc.steps: step3.3. Test SetNextMargin function.
     * @tc.expected: swiperPaintProperty->GetNextMargin() is equal to dimension.
     */
    swiperModelNG.SetNextMargin(dimension);
    EXPECT_EQ(swiperLayoutProperty->GetNextMargin(), dimension);

    /**
     * @tc.steps: step3.4. Test SetOnChangeEvent function.
     * @tc.expected: swiperPaintProperty->GetLoop() is not null.
     */
    auto onAnimationEnd = [](const BaseEventInfo* info) {};
    swiperModelNG.SetOnChangeEvent(std::move(onAnimationEnd));
    EXPECT_NE(swiperPattern->onIndexChangeEvent_, nullptr);

    /**
     * @tc.steps: step3.5. Test SetIndicatorIsBoolean function.
     * @tc.expected: swiperPattern->indicatorIsBoolean_ is true.
     */
    swiperModelNG.SetIndicatorIsBoolean(true);
    EXPECT_TRUE(swiperPattern->indicatorIsBoolean_);

    /**
     * @tc.steps: step3.6. Test SetArrowStyle function.
     * @tc.expected: before set swiperArrowParameters, all result is null.
     */
    SwiperArrowParameters swiperArrowParameters;
    swiperModelNG.SetArrowStyle(swiperArrowParameters);

    /**
     * @tc.steps: step3.7. Test SetArrowStyle function.
     * @tc.expected: after set swiperArrowParameters, swiperLayoutProperty->IsShowBoard is true.
     */
    swiperArrowParameters.isShowBoard = true;
    swiperArrowParameters.boardSize = dimension;
    swiperArrowParameters.boardColor = Color(Color::BLUE);
    swiperArrowParameters.arrowSize = dimension;
    swiperArrowParameters.arrowColor = Color(Color::RED);
    swiperArrowParameters.isSiderMiddle = true;
    swiperModelNG.SetArrowStyle(swiperArrowParameters);
    EXPECT_TRUE(swiperLayoutProperty->GetIsShowBoard());
    EXPECT_EQ(swiperLayoutProperty->GetBoardSize(), dimension);
    EXPECT_EQ(swiperLayoutProperty->GetBoardColor(), Color(Color::BLUE));
    EXPECT_EQ(swiperLayoutProperty->GetArrowSize(), dimension);
    EXPECT_EQ(swiperLayoutProperty->GetArrowColor(), Color(Color::RED));
    EXPECT_TRUE(swiperLayoutProperty->GetIsSiderMiddle());

    /**
     * @tc.steps: step3.8. Test SetDisplayArrow function.
     * @tc.expected: swiperLayoutProperty->GetDisplayArrow() is true.
     */
    swiperModelNG.SetDisplayArrow(true);
    EXPECT_TRUE(swiperLayoutProperty->GetDisplayArrow());

    /**
     * @tc.steps: step3.9. Test SetHoverShow function.
     * @tc.expected: swiperLayoutProperty->GetHoverShow() is true.
     */
    swiperModelNG.SetHoverShow(true);
    EXPECT_TRUE(swiperLayoutProperty->GetHoverShow());
}
} // namespace OHOS::Ace::NG
