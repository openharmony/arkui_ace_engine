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

#include <cstddef>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#define private public
#define protected public
#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_layout_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef private
#undef protected
#include "core/animation/animator.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

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
constexpr int32_t SWIPER_ERROR = -1;
constexpr int32_t INDEX_NUM = 10;
constexpr double SWIPER_INDICATOR_SIZE = 100.0;
constexpr double SWIPER_INDICATOR_SIZE_MINUS = -1000.0;
constexpr double SWIPER_INDEX_ONE = 1.0;
constexpr double SWIPER_INDEX_ZERO = 0.0;
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
const OffsetF MARGIN_OFFSET = OffsetF(50.0, 60.0);
constexpr float CONTEXT_WIDTH = 100.0f;
constexpr float CONTEXT_HEIGHT = 100.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float ITEM_WIDTH = 20.0f;
constexpr float ITEM_HEIGHT = 10.0f;
constexpr float ITEM_HEIGHT_LARGE = 25.0f;
constexpr float SELECTED_ITEM_WIDTH = 30.0f;
constexpr float SELECTED_ITEM_HEIGHT = 15.0f;
constexpr float SELECTED_ITEM_HEIGHT_LARGE = 35.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::pair<float, float>& LONG_POINT_CENTER_X = { 0, 0 };
static Axis indicatorDirection_;
static SwiperIndicatorType indicatorType_;
constexpr int32_t SWIPER_ITEMCOUNT = 10;
constexpr int32_t SWIPER_HOVERINDEX = 10;
constexpr int32_t SWIPER_CURRENTINDEX = 10;
constexpr int32_t SWIPER_MOUSECLICKINDEX = 5;
const SizeF SWIPER_CHILD_SIZEF_SMALL = SizeF(20.0, 20.0);
const SizeF SWIPER_CHILD_SIZEF_BIG = SizeF(30.0, 30.0);
constexpr float INDICATOR_ZOOM_IN_SCALE = 1.33f;
} // namespace

class SwiperPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void CommomAttrInfo();
    void SetUp() override;
    void TearDown() override;
    void InitSwiperTestNg();
    void CreateChildWrapperAppendToHostWrapper(
        int32_t startIndex, int32_t endIndex, const RefPtr<LayoutWrapper>& hostWrapper);
    void InitLayoutWrapper(const RefPtr<FrameNode>& frameNode, RefPtr<LayoutAlgorithm>& algorithm,
        RefPtr<FrameNode>& indicatorNode, RefPtr<LayoutWrapper>& layoutWrapper);
    void InitChild(RefPtr<LayoutWrapper>& indicatorNodeWrapper, const RefPtr<FrameNode>& indicatorNode);

    RefPtr<FrameNode> CreateSwiperFrameNode();
    RefPtr<FrameNode> frameNode_;
    RefPtr<SwiperPattern> swiperPattern_;
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty_;
    RefPtr<SwiperAccessibilityProperty> swiperAccessibilityProperty_;
};

RefPtr<FrameNode> SwiperPatternTestNg::CreateSwiperFrameNode()
{
    SwiperModelNG swiper;
    swiper.Create();
    return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
}

void SwiperPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SwiperPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void SwiperPatternTestNg::CommomAttrInfo()
{
    /**
    * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(indicatorDirection_);
    ASSERT_NE(controller, nullptr);
    mode.SetIndicatorType(indicatorType_);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));
}

void SwiperPatternTestNg::InitLayoutWrapper(const RefPtr<FrameNode>& frameNode,
    RefPtr<LayoutAlgorithm>& algorithm, RefPtr<FrameNode>& indicatorNode, RefPtr<LayoutWrapper>& layoutWrapper)
{
    indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
}

void SwiperPatternTestNg::InitChild(
    RefPtr<LayoutWrapper>& indicatorNodeWrapper, const RefPtr<FrameNode>& indicatorNode)
{
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    indicatorNodeWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    RefPtr<LayoutWrapper> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    indicatorNodeWrapper->AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(lastChild, nullptr);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_BIG);
    RefPtr<LayoutWrapper> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    indicatorNodeWrapper->AppendChild(lastLayoutWrapper);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    indicatorNodeWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
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

void SwiperPatternTestNg::SetUp() {}

void SwiperPatternTestNg::TearDown()
{
    frameNode_ = nullptr;
    swiperPattern_ = nullptr;
    swiperLayoutProperty_ = nullptr;
    swiperAccessibilityProperty_ = nullptr;
}

void SwiperPatternTestNg::InitSwiperTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    swiperPattern_ = frameNode_->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern_, nullptr);

    swiperLayoutProperty_ = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty_, nullptr);

    swiperAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    ASSERT_NE(swiperAccessibilityProperty_, nullptr);

    swiperLayoutProperty_->UpdateShowIndicator(false);
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
    const char* name = "HandleTouchDown";
    pattern->controller_ = CREATE_ANIMATOR(name);
    pattern->controller_->status_ = Animator::Status::RUNNING;
    pattern->springController_ = CREATE_ANIMATOR(name);
    pattern->springController_->status_ = Animator::Status::RUNNING;
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);

    touchEventInfo.touches_.begin()->SetTouchType(TouchType::UP);
    pattern->HandleTouchEvent(touchEventInfo);
    pattern->controller_ = nullptr;
    pattern->springController_ = nullptr;
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
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    pattern->InitPanEvent(gestureEventHub);
    EXPECT_EQ(pattern->direction_, Axis::HORIZONTAL);
    pattern->touchEvent_ = nullptr;
    pattern->InitTouchEvent(gestureEventHub);
    TouchEventFunc callback = [](TouchEventInfo& info) {};
    pattern->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback));
    pattern->InitTouchEvent(gestureEventHub);
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
    swiperLayoutAlgorithm->startIndex_ = startIndex;
    swiperLayoutAlgorithm->endIndex_ = endIndex;
    swiperLayoutAlgorithm->currentIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalCount(endIndex - startIndex);
    CreateChildWrapperAppendToHostWrapper(startIndex, endIndex, layoutWrapper);
    swiperLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    swiperLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    auto calcIdealLength =
        (SWIPER_IDEAL_WIDTH - PREVIOUS_MARGIN.Value() - NEXT_MARGIN.Value() - ITEM_SPACE.Value() * (displaycount + 1)) /
        displaycount;
    for (int32_t index = startIndex; index <= endIndex; index++) {
        auto childLayout = layoutWrapper->GetOrCreateChildByIndex(index);
        ASSERT_NE(childLayout, nullptr);
        auto mainDirectionOffset =
            (PREVIOUS_MARGIN.Value() - calcIdealLength) + index * (calcIdealLength + ITEM_SPACE.Value());
        EXPECT_EQ(childLayout->GetGeometryNode()->GetFrameSize(), SizeF(calcIdealLength, calcIdealLength));
        EXPECT_EQ(childLayout->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(mainDirectionOffset, 0.0f));
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
 * @tc.name: SwiperInit002
 * @tc.desc: InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperInit002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(eventHub, FocusType::DISABLE, false);
    pattern->InitOnKeyEvent(focusHub);
    KeyEvent event = KeyEvent();
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(focusHub->onKeyEventInternal_(event));
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
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    pattern->InitPanEvent(gestureEventHub);
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
    EXPECT_EQ(pattern->currentOffset_, MAIN_DELTA);

    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    swiperPaintProperty->propLoop_ = false;
    EXPECT_TRUE(pattern->IsOutOfBoundary(MAIN_DELTA));
    swiperNode->geometryNode_->frame_.SetSize(SizeF(GEOMETRY_WIDTH, GEOMETRY_HEIGHT));
    EXPECT_FALSE(pattern->IsOutOfBoundary(MAIN_DELTA));
    // Swiper has reached boundary.
    swiperNode->geometryNode_->frame_.SetSize(SizeF(0, 0));
    pattern->panEvent_->actionUpdate_(gestureEvent);
    pattern->currentOffset_ = MAIN_DELTA;
    swiperPaintProperty->propEdgeEffect_ = EdgeEffect::FADE;
    pattern->panEvent_->actionUpdate_(gestureEvent);
    pattern->currentOffset_ = MAIN_DELTA;
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
     * @tc.steps: step3.3. Test SetShowIndicator function.
     * @tc.expected: swiperLayoutProperty->GetIndex() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetShowIndicator(true);
    EXPECT_TRUE(swiperLayoutProperty->GetShowIndicator());

    /**
     * @tc.steps: step3.4. Test SetItemSpace function.
     * @tc.expected: swiperLayoutProperty->GetItemSpace() is equal to dimension.
     */
    auto dimension = Dimension(-1.0);
    swiperModelNG.SetItemSpace(dimension);
    EXPECT_EQ(swiperLayoutProperty->GetItemSpace(), dimension);

    /**
     * @tc.steps: step3.5. Test SetCachedCount function.
     * @tc.expected:DisplayCount = -1 swiperLayoutProperty->SetCachedCount() is equal to SWIPER_DEFAULT_INDEX.
     * @tc.expected:DisplayCount = 1 swiperLayoutProperty->SetCachedCount() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetCachedCount(-SWIPER_DEFAULT_INDEX);
    swiperModelNG.SetCachedCount(SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperLayoutProperty->GetCachedCount(), SWIPER_DEFAULT_INDEX);

    /**
     * @tc.steps: step3.6. Test SetIsIndicatorCustomSize function.
     * @tc.expected: swiperPattern->IsIndicatorCustomSize() is equal to true.
     */
    swiperModelNG.SetIsIndicatorCustomSize(true);
    EXPECT_TRUE(swiperPattern->IsIndicatorCustomSize());

    /**
     * @tc.steps: step3.7. Test SetAutoPlay function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlay() is equal to true.
     */
    swiperModelNG.SetAutoPlay(true);
    EXPECT_TRUE(swiperPaintProperty->GetAutoPlay());

    /**
     * @tc.steps: step3.8. Test SetAutoPlayInterval function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlayInterval() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetAutoPlayInterval(SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperPaintProperty->GetAutoPlayInterval(), SWIPER_DEFAULT_INDEX);

    /**
     * @tc.steps: step3.9. Test SetDuration function.
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
    swiperArrowParameters.isShowBackground = true;
    swiperArrowParameters.backgroundSize = dimension;
    swiperArrowParameters.backgroundColor = Color(Color::BLUE);
    swiperArrowParameters.arrowSize = dimension;
    swiperArrowParameters.arrowColor = Color(Color::RED);
    swiperArrowParameters.isSidebarMiddle = true;
    swiperModelNG.SetArrowStyle(swiperArrowParameters);
    EXPECT_TRUE(swiperLayoutProperty->GetIsShowBackground());
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundSize(), dimension);
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundColor(), Color(Color::BLUE));
    EXPECT_EQ(swiperLayoutProperty->GetArrowSize(), dimension);
    EXPECT_EQ(swiperLayoutProperty->GetArrowColor(), Color(Color::RED));
    EXPECT_TRUE(swiperLayoutProperty->GetIsSidebarMiddle());

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

/**
 * @tc.name: SwiperFlushFocus001
 * @tc.desc: Swiper FlushFocus.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperFlushFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode, pattern.
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
     * @tc.steps: step2. Create curShowFrameNode, addChild to frameNode.
     */
    auto curShowFrame = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    curShowFrame->AddChild(child);
    swiperFrameNode->AddChild(child2);

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(swiperFrameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);

    /**
     * @tc.steps: step3. test FlushFocus with IsShowIndicator() is false.
     * @tc.expected: curShowFrame->GetFirstFocusHubChild()->lastWeakFocusNode_ is not null.
     */
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperPattern->isLastIndicatorFocused_ = true;
    EXPECT_FALSE(swiperPattern->IsShowIndicator());
    swiperPattern->FlushFocus(curShowFrame);
    EXPECT_FALSE(curShowFrame->GetFirstFocusHubChild()->currentFocus_);
    swiperPattern->isLastIndicatorFocused_ = false;
    swiperPattern->FlushFocus(curShowFrame);
    EXPECT_EQ(swiperPattern->lastWeakShowNode_, AceType::WeakClaim(AceType::RawPtr(curShowFrame)));

    /**
     * @tc.steps: step4. test FlushFocus with IsShowIndicator() is true and hasLeftButton and hasRightButton.
     * @tc.expected: curShowFrame->GetFirstFocusHubChild()->currentFocus_ is false.
     */
    swiperLayoutProperty->UpdateShowIndicator(true);
    swiperPattern->GetLeftButtonId();
    swiperPattern->GetRightButtonId();
    EXPECT_TRUE(swiperLayoutProperty->GetShowIndicatorValue(true));
    EXPECT_TRUE(swiperPattern->IsShowIndicator());
    focusHub->currentFocus_ = true;
    swiperPattern->FlushFocus(curShowFrame);
    EXPECT_FALSE(curShowFrame->GetFirstFocusHubChild()->currentFocus_);
    swiperPattern->isLastIndicatorFocused_ = false;
    swiperPattern->FlushFocus(curShowFrame);
}

/**
 * @tc.name: SwiperGetNextFocusNode001
 * @tc.desc: Swiper GetNextFocusNode.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperGetNextFocusNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode, pattern.
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
     * @tc.steps: step2. Create localShowNode and focusNode.
     */
    auto localShowNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHubLocal = AceType::MakeRefPtr<EventHub>();
    eventHubLocal->AttachHost(localShowNode);
    auto focusHubLocal = AceType::MakeRefPtr<FocusHub>(eventHubLocal);

    auto focusNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(focusNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);

    swiperPattern->lastWeakShowNode_ = AceType::WeakClaim(AceType::RawPtr(localShowNode));

    /**
     * @tc.steps: step3. Test different Axis and FocusStep.
     */
    /**
     * @tc.steps: step3.1. Test different Axis::HORIZONTAL and FocusStep::UP.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::HORIZONTAL;
    swiperPattern->GetNextFocusNode(FocusStep::UP, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.2. Test different Axis::VERTICAL and FocusStep::LEFT.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::VERTICAL;
    swiperPattern->GetNextFocusNode(FocusStep::LEFT, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.3. Test different Axis::HORIZONTAL and FocusStep::DOWN.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::HORIZONTAL;
    swiperPattern->GetNextFocusNode(FocusStep::LEFT, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.4. Test different Axis::VERTICAL and FocusStep::RIGHT.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::VERTICAL;
    swiperPattern->GetNextFocusNode(FocusStep::RIGHT, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.5. Test different Axis::FREE.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::FREE;
    swiperPattern->GetNextFocusNode(FocusStep::RIGHT, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.6. Test different Axis::HORIZONTAL and FocusStep::UP and has left right button.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->GetLeftButtonId();
    swiperPattern->GetRightButtonId();
    swiperPattern->direction_ = Axis::HORIZONTAL;
    swiperPattern->GetNextFocusNode(FocusStep::UP, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.7. Test different Axis::HORIZONTAL and FocusStep::UP and has left right button.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::HORIZONTAL;
    swiperPattern->GetNextFocusNode(FocusStep::DOWN, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperPreviousFocus001
 * @tc.desc: Swiper PreviousFocus.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperPreviousFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode, pattern.
     */
    SwiperModelNG swiperModelNG;
    swiperModelNG.Create();

    auto swiperFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    auto swiperLeftArrowNode =
        AceType::MakeRefPtr<FrameNode>(V2::SWIPER_LEFT_ARROW_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    auto swiperRightArrowNode =
        AceType::MakeRefPtr<FrameNode>(V2::SWIPER_INDICATOR_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    swiperFrameNode->AddChild(swiperLeftArrowNode);
    swiperFrameNode->AddChild(swiperRightArrowNode);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(swiperFrameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);

    auto curEventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SWIPER_LEFT_ARROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    curEventHub->AttachHost(frameNode);
    auto curFocusHub = AceType::MakeRefPtr<FocusHub>(curEventHub);

    auto focusChildren = focusHub->GetChildren();
    swiperPattern->leftButtonId_ = std::nullopt;
    swiperPattern->PreviousFocus(curFocusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);
    EXPECT_FALSE(curFocusHub->parentFocusable_);
    swiperModelNG.SetLoop(false);
    swiperPattern->PreviousFocus(curFocusHub);
    EXPECT_TRUE(curFocusHub->parentFocusable_);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);
    curFocusHub->GetFrameNode()->tag_ = V2::SWIPER_INDICATOR_ETS_TAG;
    swiperPattern->PreviousFocus(curFocusHub);
    EXPECT_TRUE(swiperPattern->isLastIndicatorFocused_);
    curFocusHub->GetFrameNode()->tag_ = V2::SWIPER_RIGHT_ARROW_ETS_TAG;
    swiperPattern->PreviousFocus(curFocusHub);
    swiperModelNG.SetLoop(true);
    swiperPattern->GetLeftButtonId();
    EXPECT_FALSE(swiperLayoutProperty->GetHoverShowValue(false));
    swiperPattern->PreviousFocus(curFocusHub);
    EXPECT_TRUE(swiperPattern->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperAccessibilityPropertyGetCurrentIndex001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetCurrentIndex(), SWIPER_ERROR);

    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode_->AddChild(indicatorNode);
    swiperPattern_->currentIndex_ = INDEX_NUM;
    EXPECT_EQ(swiperAccessibilityProperty_->GetCurrentIndex(), INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetBeginIndex001
 * @tc.desc: Test GetBeginIndex of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperAccessibilityPropertyGetBeginIndex001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetBeginIndex(), SWIPER_ERROR);

    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode_->AddChild(indicatorNode);
    swiperPattern_->startIndex_ = INDEX_NUM;
    EXPECT_EQ(swiperAccessibilityProperty_->GetBeginIndex(), INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetEndIndex001
 * @tc.desc: Test GetEndIndex of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperAccessibilityPropertyGetEndIndex001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetEndIndex(), SWIPER_ERROR);

    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode_->AddChild(indicatorNode);
    swiperPattern_->endIndex_ = INDEX_NUM;
    EXPECT_EQ(swiperAccessibilityProperty_->GetEndIndex(), INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetAccessibilityValue001
 * @tc.desc: Test GetAccessibilityValue of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperAccessibilityPropertyGetAccessibilityValue001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_TRUE(swiperAccessibilityProperty_->HasRange());
    AccessibilityValue result = swiperAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, 0);
    EXPECT_EQ(result.current, 0);

    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->currentIndex_ = INDEX_NUM;

    result = swiperAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, INDEX_NUM);
    EXPECT_EQ(result.current, INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    InitSwiperTestNg();

    auto swiperPaintProperty = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    EXPECT_FALSE(swiperAccessibilityProperty_->IsScrollable());

    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->OnModifyDone();
    EXPECT_TRUE(swiperAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetCollectionItemCounts001
 * @tc.desc: Test GetCollectionItemCounts of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperAccessibilityPropertyGetCollectionItemCounts001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetCollectionItemCounts(), 0);

    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->OnModifyDone();
    EXPECT_EQ(swiperAccessibilityProperty_->GetCollectionItemCounts(), INDEX_NUM + 1);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    InitSwiperTestNg();

    auto swiperPaintProperty = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->currentIndex_ = 1;
    swiperPattern_->OnModifyDone();
    swiperAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = swiperAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    swiperPaintProperty->UpdateLoop(true);
    swiperAccessibilityProperty_->ResetSupportAction();
    supportAceActions = swiperAccessibilityProperty_->GetSupportAction();
    actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}

/**
 * @tc.name: SwiperAccessibilityPropertySetSpecificSupportAction001
 * @tc.desc: Test GetSupportAction of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperAccessibilityPropertySetSpecificSupportAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. InitSwiperTestNg.
     */
    InitSwiperTestNg();

    /**
     * @tc.steps: step2. call SetSpecificSupportAction with swiperAccessibilityProperty_->IsScrollable() is false.
     * @tc.expected: swiperAccessibilityProperty_->IsScrollable() is false.
     */
    auto swiperPaintProperty = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    swiperAccessibilityProperty_->SetSpecificSupportAction();

    /**
     * @tc.steps: step2. call SetSpecificSupportAction.
     * @tc.expected: GetCurrentIndex() < 0.
     */
    swiperPattern_->GetLeftButtonId();
    swiperPattern_->GetRightButtonId();
    swiperAccessibilityProperty_->SetSpecificSupportAction();
    EXPECT_LT(swiperAccessibilityProperty_->GetCurrentIndex(), 0);

    /**
     * @tc.steps: step2. call SetSpecificSupportAction.
     * @tc.expected: GetCurrentIndex() > GetCollectionItemCounts().
     */
    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperAccessibilityProperty_->SetSpecificSupportAction();
    swiperPattern_->currentIndex_ = swiperPattern_->TotalCount();
    EXPECT_GE(swiperAccessibilityProperty_->GetCurrentIndex(), swiperAccessibilityProperty_->GetCollectionItemCounts());
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test for measure method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();
    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmMeasure002
 * @tc.desc: Test for measure method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorLayoutAlgorithmMeasure002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();
    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);
    frameNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSize(Dimension(SWIPER_INDICATOR_SIZE_MINUS, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout001
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLeft(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(100.00, 568.00));
    layoutProperty->Reset();
    ASSERT_NE(layoutProperty->Clone(), nullptr);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout002
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateRight(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty right is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(620.00, 1136.00));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout003
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout003, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateRight(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(620.00, 1136.00));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout004
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout004, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTop(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty top is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 100.00));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout005
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout005, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateBottom(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty bottom is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 1036.00));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout006
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout006, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 568.00));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    RefPtr<DotIndicatorLayoutAlgorithm> algorithm =
        AceType::DynamicCast<DotIndicatorLayoutAlgorithm>(indicatorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(0.7, DimensionUnit::PERCENT)), 60.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(0.5, DimensionUnit::PERCENT)), 50.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 20.0, Dimension(0.0, DimensionUnit::PERCENT)), 0.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(70.0, DimensionUnit::PX)), 60.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(-10.0, 40.0, Dimension(-20.0, DimensionUnit::PX)), 0.0);
}

/**
 * @tc.name: SwiperIndicatorOnAttachToFrameNodeTest001
 * @tc.desc: Test SwiperIndicator OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorOnAttachToFrameNodeTest001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create theme manager and set theme
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnAttachToFrameNode();

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
}

/**
 * @tc.name: SwiperIndicatorOnModifyDone001
 * @tc.desc: Test SwiperIndicator OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorOnModifyDone001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    DirtySwapConfig config;
    config.frameSizeChange = false;
    EXPECT_FALSE(indicatorPattern->OnDirtyLayoutWrapperSwap(nullptr, config));
    config.frameSizeChange = true;
    EXPECT_TRUE(indicatorPattern->OnDirtyLayoutWrapperSwap(nullptr, config));
}

/**
 * @tc.name: SwiperIndicatorInitClickEvent001
 * @tc.desc: Test SwiperIndicator InitClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorInitClickEvent001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    indicatorPattern->clickEvent_ = nullptr;
    RefPtr<GestureEventHub> gestureHub = frameNode->GetOrCreateGestureEventHub();
    indicatorPattern->InitClickEvent(gestureHub);
    indicatorPattern->InitClickEvent(gestureHub);
    gestureHub->ActClick();
}

/**
 * @tc.name: SwiperIndicatorHandleClick001
 * @tc.desc: Test SwiperIndicator HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorHandleClick001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    GestureEvent info;
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));
    indicatorPattern->HandleClick(info);
}

/**
 * @tc.name: SwiperIndicatorGetContentModifier001
 * @tc.desc: Test SwiperIndicator GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorGetContentModifier001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper and GetContentModifier.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod =
        AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    /**
     * @tc.steps: step3. call GetContentModifier.
     */
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->UpdateContentModifier(&paintWrapper);
    RefPtr<Modifier> ptrModifier = paintMethod->GetContentModifier(&paintWrapper);
    ASSERT_NE(ptrModifier, nullptr);
}

/**
 * @tc.name: SelectedFontSize001
 * @tc.desc: Test SwiperIndicator SelectedFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SelectedFontSize001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. SelectedFontSize is 14.
     */
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(frontTextFrameNode, nullptr);
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    ASSERT_NE(frontTextLayoutProperty, nullptr);
    EXPECT_EQ(frontTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);

    /**
     * @tc.steps: step4. SelectedFontSize is 60.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    Dimension fontSize = 60.0_px;
    layoutProperty->UpdateSelectedFontSize(fontSize);
    indicatorPattern->OnModifyDone();
    EXPECT_EQ(frontTextLayoutProperty->GetFontSize()->ConvertToPx(), 60);
}

/**
 * @tc.name: SelectedFontSize002
 * @tc.desc: Test SwiperIndicator SelectedFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SelectedFontSize002, TestSize.Level2)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);

    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(frontTextFrameNode, nullptr);
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    ASSERT_NE(frontTextLayoutProperty, nullptr);

    /**
     * @tc.steps: step4. SelectedFontSize is -1.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    Dimension fontSize = -1.0_px;
    layoutProperty->UpdateSelectedFontSize(fontSize);
    indicatorPattern->OnModifyDone();
    EXPECT_EQ(frontTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);
}

/**
 * @tc.name: FontSize001
 * @tc.desc: Test SwiperIndicator FontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FontSize001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. FontSize is 14.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(backTextFrameNode, nullptr);
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    ASSERT_NE(backTextLayoutProperty, nullptr);
    EXPECT_EQ(backTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);

    /**
     * @tc.steps: step3. FontSize is 30.
     */

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    Dimension fontSize = 30.0_px;
    layoutProperty->UpdateFontSize(fontSize);
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    EXPECT_EQ(backTextLayoutProperty->GetFontSize()->ConvertToPx(), 30);
}

/**
 * @tc.name: FontSize002
 * @tc.desc: Test SwiperIndicator FontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FontSize002, TestSize.Level2)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(backTextFrameNode, nullptr);
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    ASSERT_NE(backTextLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. FontSize is -10.
     */

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    Dimension fontSize = -10.0_px;
    layoutProperty->UpdateFontSize(fontSize);
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    EXPECT_EQ(backTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);
}

/**
 * @tc.name: FontColor001
 * @tc.desc: Test SwiperIndicator FontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FontColor001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. FontColor is 0xff000000.
     */
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(backTextFrameNode, nullptr);
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    ASSERT_NE(backTextLayoutProperty, nullptr);
    EXPECT_EQ(backTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);

    /**
     * @tc.steps: step3. FontColor is WHITE.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontColor(Color::WHITE);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(backTextLayoutProperty->GetTextColor()->GetValue(), 0xffffffff);
}

/**
 * @tc.name: FontColor002
 * @tc.desc: Test SwiperIndicator FontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FontColor002, TestSize.Level2)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(backTextFrameNode, nullptr);
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    ASSERT_NE(backTextLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. FontColor is 0xff00ff00.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontColor(Color());
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(backTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);
}

/**
 * @tc.name: SelectedFontColor001
 * @tc.desc: Test SwiperIndicator SelectedFontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SelectedFontColor001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. SelectedFontColor001 is 0xff000000.
     */
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(frontTextFrameNode, nullptr);
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    ASSERT_NE(frontTextLayoutProperty, nullptr);
    EXPECT_EQ(frontTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);

    /**
     * @tc.steps: step4. SelectedFontColor is WHITE.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSelectedFontColor(Color::WHITE);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(frontTextLayoutProperty->GetTextColor()->GetValue(), 0xffffffff);
}

/**
 * @tc.name: SelectedFontColor002
 * @tc.desc: Test SwiperIndicator SelectedFontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SelectedFontColor002, TestSize.Level2)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(frontTextFrameNode, nullptr);
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    ASSERT_NE(frontTextLayoutProperty, nullptr);
    /**
     * @tc.steps: step3. SelectedFontColor is Color().
     */
    layoutProperty->UpdateSelectedFontColor(Color());
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(frontTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);
}

/**
 * @tc.name: FontWeight001
 * @tc.desc: Test SwiperIndicator FontWeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, FontWeight001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. FontWeight is NORMAL.
     */
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(backTextFrameNode, nullptr);
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    ASSERT_NE(backTextLayoutProperty, nullptr);
    EXPECT_EQ(backTextLayoutProperty->GetFontWeight(), FontWeight::NORMAL);
    /**
     * @tc.steps: step3. FontWeight is BOLDER.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontWeight(FontWeight::BOLDER);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(backTextLayoutProperty->GetFontWeight(), FontWeight::BOLDER);
}

/**
 * @tc.name: SelectedFontWeight001
 * @tc.desc: Test SwiperIndicator SelectedFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SelectedFontWeight001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. SelectedFontWeight is NORMAL.
     */
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(frontTextFrameNode, nullptr);
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    ASSERT_NE(frontTextLayoutProperty, nullptr);
    EXPECT_EQ(frontTextLayoutProperty->GetFontWeight(), FontWeight::NORMAL);
    /**
     * @tc.steps: step3. SelectedFontWeight is MEDIUM.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSelectedFontWeight(FontWeight::MEDIUM);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(frontTextLayoutProperty->GetFontWeight(), FontWeight::MEDIUM);
}

/**
 * @tc.name: ItemWidth001
 * @tc.desc: Test SwiperIndicator ItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, ItemWidth001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateItemWidth(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemWidth002
 * @tc.desc: Test SwiperIndicator ItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, ItemWidth002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);
    frameNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateItemWidth(Dimension(SWIPER_INDICATOR_SIZE_MINUS, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemWidth is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemHeight001
 * @tc.desc: Test SwiperIndicator ItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, ItemHeight001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateItemHeight(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemHeight is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemHeight002
 * @tc.desc: Test SwiperIndicator ItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, ItemHeight002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    frameNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateItemHeight(Dimension(SWIPER_INDICATOR_SIZE_MINUS, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemHeight is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemWidth001
 * @tc.desc: Test SwiperIndicator SelectedItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SelectedItemWidth001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSelectedItemWidth(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemWidth is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemWidth002
 * @tc.desc: Test SwiperIndicator SelectedItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SelectedItemWidth002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);
    frameNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSelectedItemWidth(Dimension(SWIPER_INDICATOR_SIZE_MINUS, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemWidth is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemHeight001
 * @tc.desc: Test SwiperIndicator SelectedItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SelectedItemHeight001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSelectedItemHeight(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemHeight is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemHeight002
 * @tc.desc: Test SwiperIndicator SelectedItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SelectedItemHeight002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);
    frameNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSelectedItemHeight(Dimension(SWIPER_INDICATOR_SIZE_MINUS, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemHeight is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout001
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperLayoutAlgorithmLayout001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapper> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    auto swiperPatternAlgorithm = swiperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(swiperPatternAlgorithm, nullptr);
    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->GetLayoutProperty());
    swiperLayoutProperty->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapper swiperLayoutWrapper = LayoutWrapper(swiperNode, geometryNode, swiperLayoutProperty);
    ASSERT_NE(indicatorNodeWrapper, nullptr);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 327.0, 1106.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
    EXPECT_EQ(indicatorNodeWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(327.0, 1098.0));
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout002
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperLayoutAlgorithmLayout002, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapper> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    auto swiperPatternAlgorithm = swiperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(swiperPatternAlgorithm, nullptr);
    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->GetLayoutProperty());
    swiperLayoutProperty->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapper swiperLayoutWrapper = LayoutWrapper(swiperNode, geometryNode, swiperLayoutProperty);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 654.0, 553.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
    EXPECT_EQ(indicatorNodeWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(654.0, 553.0));
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout003
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperLayoutAlgorithmLayout003, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapper> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    auto swiperPatternAlgorithm = swiperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(swiperPatternAlgorithm, nullptr);
    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->GetLayoutProperty());
    swiperLayoutProperty->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    Dimension dimension = 20.0_vp;
    swiperLayoutProperty->UpdateLeft(dimension);
    swiperLayoutProperty->UpdateTop(dimension);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapper swiperLayoutWrapper = LayoutWrapper(swiperNode, geometryNode, swiperLayoutProperty);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 20.0, 20.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
    EXPECT_EQ(indicatorNodeWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(20.0, 20.0));
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout004
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperLayoutAlgorithmLayout004, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();
    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapper> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    auto swiperPatternAlgorithm = swiperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(swiperPatternAlgorithm, nullptr);
    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->GetLayoutProperty());
    swiperLayoutProperty->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    Dimension dimension = 20.0_vp;
    swiperLayoutProperty->UpdateRight(dimension);
    swiperLayoutProperty->UpdateBottom(dimension);
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapper swiperLayoutWrapper = LayoutWrapper(swiperNode, geometryNode, swiperLayoutProperty);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 634.0, 1086.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
    EXPECT_EQ(indicatorNodeWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(634.0, 1086.0));
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier001
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorUpdateContentModifier001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper and GetContentModifier.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isPressed_ = true;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isPressed_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorUpdateContentModifier002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper and GetContentModifier.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isHover_ = true;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isHover_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsHover());
}

/**
 * @tc.name: SwiperIndicatorPaintNormalIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorPaintNormalIndicator001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(CONTAINER_SIZE);
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(ITEM_WIDTH, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(ITEM_HEIGHT, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(SELECTED_ITEM_WIDTH, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(SELECTED_ITEM_HEIGHT, DimensionUnit::PX));

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);

    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: paintMethod->normalMargin_.X is 336.0
     *               paintMethod->normalMargin_.Y is 547.5
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 346.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 547.5);
}

/**
 * @tc.name: SwiperIndicatorPaintNormalIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorPaintNormalIndicator002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(CONTAINER_SIZE);
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(ITEM_WIDTH, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(ITEM_HEIGHT, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(SELECTED_ITEM_WIDTH, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(SELECTED_ITEM_HEIGHT, DimensionUnit::PX));

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);
    paintMethod->itemCount_ = SWIPER_ITEMCOUNT;

    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: paintMethod->normalMargin_.X is 196.0
     *               paintMethod->normalMargin_.Y is 547.5
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 206.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 547.5);
}

/**
 * @tc.name: SwiperIndicatorPaintPressIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorPaintPressIndicator001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);

    /**
     * @tc.steps: step3. call PaintPressIndicator.
     * @tc.expected: paintMethod->dotIndicatorModifier_ is true.
     */
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorPaintPressIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorPaintPressIndicator002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    paintProperty->UpdateItemHeight(Dimension(ITEM_HEIGHT, DimensionUnit::PX));
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);
    paintMethod->itemCount_ = SWIPER_ITEMCOUNT;

    /**
     * @tc.steps: step3. call PaintPressIndicator.
     * @tc.expected: itemHalfSizes_->Get()[1] is 6.65 .
     */
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(NearEqual(
        paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get()[1], ITEM_HEIGHT * 0.5 * INDICATOR_ZOOM_IN_SCALE));
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorPaintHoverIndicator001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->hoverIndex_ = SWIPER_HOVERINDEX;
    paintMethod->currentIndex_ = SWIPER_CURRENTINDEX;
    paintMethod->mouseClickIndex_ = SWIPER_MOUSECLICKINDEX;
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetNormalToHoverIndex(SWIPER_MOUSECLICKINDEX);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);

    /**
     * @tc.steps: step3. call PaintHoverIndicator.
     * @tc.expected: dotIndicatorModifier_->GetIsPressed is false.
     */
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorPaintHoverIndicator002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    paintProperty->UpdateItemWidth(Dimension(ITEM_WIDTH, DimensionUnit::PX));
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);

    /**
     * @tc.steps: step3. call PaintHoverIndicator.
     * @tc.expected: itemHalfSizes_->Get()[0] is 13.30 .
     */
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_TRUE(NearEqual(
        paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get()[0], ITEM_WIDTH * 0.5 * INDICATOR_ZOOM_IN_SCALE));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);

    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    RefPtr<LayoutWrapper> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);

    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(lastChild, nullptr);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_BIG);
    RefPtr<LayoutWrapper> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Measure.
     * @tc.expected: layoutWrapper MarginFrameSize is 66.00, 30.00
     */
    algorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameSize(), SizeF(66.00, 30.00));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout002
 * @tc.desc: Test TxtParagraph SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);

    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(CONTAINER_SIZE);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    RefPtr<LayoutWrapper> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);

    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(lastChild, nullptr);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_BIG);
    RefPtr<LayoutWrapper> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: firstLayoutWrapper MarginFrameOffset is 8.00, 558.00
     *               lastLayoutWrapper MarginFrameOffset is 682.00, 553.00
     */
    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(8.00, 558.00));
    EXPECT_EQ(lastLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(682.00, 553.00));
}

/**
 * @tc.name: SwiperIndicatorHandleClick002
 * @tc.desc: Test SwiperIndicatorPattern SwiperIndicatorHandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorHandleClick002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);
    frameNode->AddChild(swiperNode);

    auto swiperNodeTwo = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNodeTwo, nullptr);
    frameNode->AddChild(swiperNodeTwo);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    GestureEvent info;
    info.SetSourceDevice(SourceType::MOUSE);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateItemWidth(Dimension(10, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10, DimensionUnit::PX));
    indicatorPattern->mouseClickIndex_ = SWIPER_MOUSECLICKINDEX;
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->indicatorDoingAnimation_ = false;
    swiperPattern->currentIndex_ = 10;
    indicatorPattern->hoverPoint_.SetX(5.0);
    indicatorPattern->hoverPoint_.SetY(15.0);

    /**
     * @tc.steps: step3. call HandleClick.
     * @tc.expected: swiperPattern->indicatorDoingAnimation_ is true.
     */
    indicatorPattern->HandleClick(info);
    EXPECT_TRUE(swiperPattern->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperIndicatorHandleClick003
 * @tc.desc: Test SwiperIndicatorPattern SwiperIndicatorHandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperIndicatorHandleClick003, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));
    paintProperty->UpdateItemWidth(Dimension(-1.0, DimensionUnit::PX));
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    swiperPattern->indicatorDoingAnimation_ = true;

    /**
     * @tc.steps: step3. call HandleClick.
     * @tc.expected: swiperPattern->indicatorDoingAnimation_ is false.
     */
    indicatorPattern->HandleClick(info);
    EXPECT_FALSE(swiperPattern->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperInitIndicator001
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperInitIndicator001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    swiperNode->AddChild(indicatorNode);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: swiperNode lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    swiperPattern->InitIndicator();
    ASSERT_EQ(swiperNode->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator002
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperInitIndicator002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    swiperNode->AddChild(indicatorNode);
    auto layoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateShowIndicator(false);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: swiperNode->GetLastChild is 1.
     */
    swiperPattern->InitIndicator();
    ASSERT_EQ(swiperNode->GetLastChild(), 1);
}

/**
 * @tc.name: SwiperInitIndicator003
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperInitIndicator003, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    swiperNode->AddChild(textNode);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: swiperNode lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    swiperPattern->InitIndicator();
    ASSERT_EQ(swiperNode->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator004
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperInitIndicator004, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    swiperNode->AddChild(textNode);
    auto layoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateShowIndicator(false);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: swiperNode lastChild is TEXT_ETS_TAG
     */
    swiperPattern->InitIndicator();
    ASSERT_EQ(swiperNode->GetLastChild()->GetTag(), V2::TEXT_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator005
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperInitIndicator005, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    swiperNode->AddChild(indicatorNode);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: swiperNode lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    swiperPattern->InitIndicator();
    ASSERT_EQ(swiperNode->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SetDotIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDotIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SetDotIndicatorStyle001, TestSize.Level1)
{
    SwiperModelNG mode;
    auto controller = mode.Create();
    ASSERT_NE(controller, nullptr);
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperNode, nullptr);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. call SetDotIndicatorStyle.
     * @tc.expected: swiperParameters_ colorVal is swiperParameters colorVal
     */
    mode.SetDotIndicatorStyle(swiperParameters);
    ASSERT_EQ(pattern->swiperParameters_->colorVal, swiperParameters.colorVal);
}

/**
 * @tc.name: SetDigitIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDigitIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SetDigitIndicatorStyle001, TestSize.Level1)
{
    SwiperModelNG mode;
    auto controller = mode.Create();
    ASSERT_NE(controller, nullptr);
    SwiperDigitalParameters digitalParameters;
    digitalParameters.fontColor = Color(Color::GREEN);

    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperNode, nullptr);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. call SetDigitIndicatorStyle.
     * @tc.expected: swiperDigitalParameters_ fontColor is digitalParameters fontColor
     */
    mode.SetDigitIndicatorStyle(digitalParameters);
    ASSERT_EQ(pattern->swiperDigitalParameters_->fontColor, digitalParameters.fontColor);
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout001
 * @tc.desc: Test DigitIndicatorLayoutAlgorithm SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);

    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNode children is empty.
     */
    algorithm->Layout(&layoutWrapper);
    auto hostNode = layoutWrapper.GetHostNode();
    ASSERT_NE(hostNode, nullptr);
    auto children = hostNode->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: DotIndicatorModifier001
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, DotIndicatorModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DotIndicatorModifier. Update PaintProperty.Call the function onDraw.
     * @tc.expected: step1. Check the PaintProperty update success.
     */
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(ITEM_WIDTH);
    LinearVector<float> normalItemHalfSizes;
    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT == SELECTED_ITEM_HALF_HEIGHT.
    normalItemHalfSizes.emplace_back(ITEM_WIDTH);
    normalItemHalfSizes.emplace_back(ITEM_WIDTH);
    normalItemHalfSizes.emplace_back(ITEM_WIDTH);
    normalItemHalfSizes.emplace_back(ITEM_WIDTH);

    dotIndicatorModifier.UpdateShrinkPaintProperty(
        MARGIN_OFFSET, normalItemHalfSizes, vectorBlackPointCenterX, LONG_POINT_CENTER_X);
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[1] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[2] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[3] is ITEM_WIDTH.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], ITEM_WIDTH);

    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT < SELECTED_ITEM_HALF_HEIGHT.
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ZERO;
    LinearVector<float> normalItemHalfSizesSecond;
    normalItemHalfSizesSecond.emplace_back(ITEM_WIDTH);
    normalItemHalfSizesSecond.emplace_back(ITEM_HEIGHT_LARGE);
    normalItemHalfSizesSecond.emplace_back(ITEM_WIDTH);
    normalItemHalfSizesSecond.emplace_back(SELECTED_ITEM_HEIGHT);
    dotIndicatorModifier.UpdateShrinkPaintProperty(
        MARGIN_OFFSET, normalItemHalfSizesSecond, vectorBlackPointCenterX, LONG_POINT_CENTER_X);
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[1] is ITEM_HEIGHT_LARGE.
     *               itemHalfSizes_->Get()[2] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[3] is SELECTED_ITEM_HEIGHT.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], ITEM_HEIGHT_LARGE);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], SELECTED_ITEM_HEIGHT);
}

/**
 * @tc.name: DotIndicatorModifier002
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, DotIndicatorModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DotIndicatorModifier. Update PaintProperty.Call the function onDraw.
     * @tc.expected: step1. Check the PaintProperty update success.
     */
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(ITEM_WIDTH);

    // ITEM_HALF_WIDTH != SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT > SELECTED_ITEM_HALF_HEIGHT.
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ONE;
    LinearVector<float> normalItemHalfSizesThird;
    normalItemHalfSizesThird.emplace_back(ITEM_WIDTH);
    normalItemHalfSizesThird.emplace_back(ITEM_HEIGHT);
    normalItemHalfSizesThird.emplace_back(SELECTED_ITEM_WIDTH);
    normalItemHalfSizesThird.emplace_back(SELECTED_ITEM_HEIGHT_LARGE);
    dotIndicatorModifier.UpdateShrinkPaintProperty(
        MARGIN_OFFSET, normalItemHalfSizesThird, vectorBlackPointCenterX, LONG_POINT_CENTER_X);
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[1] is ITEM_HEIGHT.
     *               itemHalfSizes_->Get()[2] is SELECTED_ITEM_WIDTH.
     *               itemHalfSizes_->Get()[3] is SELECTED_ITEM_HEIGHT_LARGE.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], ITEM_HEIGHT);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], SELECTED_ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], SELECTED_ITEM_HEIGHT_LARGE);
}

/**
 * @tc.name: DotIndicatorModifier003
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, DotIndicatorModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DotIndicatorModifier. Update PaintProperty.Call the function onDraw.
     * @tc.expected: step1. Check the PaintProperty update success.
     */
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(ITEM_WIDTH);
    // call the UpdateDilatePaintProperty to set property.
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ONE;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(ITEM_WIDTH);
    itemHalfSizes.emplace_back(ITEM_HEIGHT);
    itemHalfSizes.emplace_back(SELECTED_ITEM_WIDTH);
    itemHalfSizes.emplace_back(SELECTED_ITEM_HEIGHT_LARGE);
    dotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, LONG_POINT_CENTER_X);
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[1] is ITEM_HEIGHT.
     *               itemHalfSizes_->Get()[2] is SELECTED_ITEM_WIDTH.
     *               itemHalfSizes_->Get()[3] is SELECTED_ITEM_HEIGHT_LARGE.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], ITEM_HEIGHT);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], SELECTED_ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], SELECTED_ITEM_HEIGHT_LARGE);
    // call the UpdateHoverPaintProperty to set property.
    dotIndicatorModifier.UpdateHoverPaintProperty(itemHalfSizes, vectorBlackPointCenterX, LONG_POINT_CENTER_X);
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[1] is ITEM_HEIGHT.
     *               itemHalfSizes_->Get()[2] is SELECTED_ITEM_WIDTH.
     *               itemHalfSizes_->Get()[3] is SELECTED_ITEM_HEIGHT_LARGE.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], ITEM_HEIGHT);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], SELECTED_ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], SELECTED_ITEM_HEIGHT_LARGE);
}
} // namespace OHOS::Ace::NG
