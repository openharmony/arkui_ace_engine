/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include <optional>
#include "gtest/gtest.h"
#include "base/geometry/dimension.h"

#define protected public
#define private public
#include "test/unittest/core/pattern/scroll/scroll_test_ng.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#include "test/unittest/core/pattern/scroll/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
constexpr float DEFAULT_WIDTH = 12.0f;
constexpr float SCROLL_WIDTH = 480.f;
constexpr float SCROLL_HEIGHT = 800.f;
constexpr int32_t TOTAL_LINE_NUMBER = 10;
const Color BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR = Color(0XFFFFFF00);

namespace {} // namespace
class ArcScrollTestNg : public TestNG {
public:
static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(const std::function<void(ScrollModelNG)>& callback = nullptr);
    void CreateWithContent(
        const std::function<void(ScrollModelNG)>& callback = nullptr, int32_t childNumber = TOTAL_LINE_NUMBER);
    void CreateSnapScroll(ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
        const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide);

    static void CreateContent(int32_t childNumber = TOTAL_LINE_NUMBER);
    static Axis GetAxis();

    RefPtr<FrameNode> frameNode_;
    RefPtr<ScrollPattern> pattern_;
    RefPtr<ScrollEventHub> eventHub_;
    RefPtr<ScrollLayoutProperty> layoutProperty_;
    RefPtr<ScrollablePaintProperty> paintProperty_;
    RefPtr<ScrollAccessibilityProperty> accessibilityProperty_;
    RefPtr<ArcScrollBar> arcscrollBar_;
};

void ArcScrollTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto scrollBarTheme = AceType::MakeRefPtr<ScrollBarTheme>();
    scrollBarTheme->normalWidth_ = Dimension(NORMAL_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollBarTheme));
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void ArcScrollTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ArcScrollTestNg::SetUp() {}

void ArcScrollTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    arcscrollBar_ = nullptr;
}

void ArcScrollTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ScrollPattern>();
    eventHub_ = frameNode_->GetEventHub<ScrollEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ScrollLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ScrollAccessibilityProperty>();
}

void ArcScrollTestNg::Create(const std::function<void(ScrollModelNG)>& callback)
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

void ArcScrollTestNg::CreateWithContent(const std::function<void(ScrollModelNG)>& callback, int32_t childNumber)
{
    Create([callback, childNumber](ScrollModelNG model) {
        if (callback) {
            callback(model);
        }
        CreateContent(childNumber);
    });
}

void ArcScrollTestNg::CreateSnapScroll(ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
    const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide)
{
    CreateWithContent(
        [scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide](ScrollModelNG model) {
            model.SetScrollSnap(scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide);
        }, TOTAL_LINE_NUMBER);
}

void ArcScrollTestNg::CreateContent(int32_t childNumber)
{
    if (GetAxis() == Axis::HORIZONTAL) {
        RowModelNG rowModel;
        rowModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(Dimension(childNumber * TITLE_WIDTH)));
        ViewAbstract::SetHeight(CalcLength(LIGHT_HEIGHT));
        for (int32_t index = 0; index < childNumber; index++) {
            RowModelNG rowModel;
            rowModel.Create(Dimension(0), nullptr, "");
            ViewAbstract::SetWidth(CalcLength(Dimension(TITLE_WIDTH)));
            ViewAbstract::SetHeight(CalcLength(LIGHT_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
        }
    } else {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(LIGHT_HEIGHT));
        ViewAbstract::SetHeight(CalcLength(Dimension(childNumber * LIGHT_HEIGHT)));
        for (int32_t index = 0; index < childNumber; index++) {
            ColumnModelNG colModel;
            colModel.Create(Dimension(0), nullptr, "");
            ViewAbstract::SetWidth(CalcLength(LIGHT_HEIGHT));
            ViewAbstract::SetHeight(CalcLength(Dimension(LIGHT_HEIGHT)));
            ViewStackProcessor::GetInstance()->Pop();
        }
    }
    ViewStackProcessor::GetInstance()->Pop();
}

Axis ArcScrollTestNg::GetAxis()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty<ScrollLayoutProperty>();
    auto axis = layoutProperty->GetAxis();
    return axis.has_value() ? axis.value() : Axis::VERTICAL;
}

/**
 * @tc.name: ArcScrollTestNg001
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CreateWithContent, call SetShapeMode
     * @tc.expected: shapeMode_ is not DEFAULT
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON)); });
    auto paint = AceType::MakeRefPtr<ScrollPaintMethod>();

    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    ASSERT_NE(paintWrapper, nullptr);

    paint->UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
    auto scrollBar = pattern_->GetScrollBar();
    EXPECT_EQ(scrollBar->shapeMode_, ShapeMode::RECT);
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);

    scrollBar->SetShapeMode(ShapeMode::ROUND);
    EXPECT_EQ(scrollBar->shapeMode_, ShapeMode::ROUND);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
}

/**
 * @tc.name: ArcScrollTestNg002
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CreateWithContent, call InBarTouchRegion
     * @tc.expected: expect InBarTouchRegion return false
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON)); });
    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->SetShapeMode(ShapeMode::ROUND);
    EXPECT_FALSE(scrollBar->InBarTouchRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarHoverRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarRectRegion(Point(0, 0)));
    EXPECT_TRUE(scrollBar->isScrollable_);
}

/**
 * @tc.name: ArcScrollTestNg003
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CreateWithContent, call SetBarRegion
     * @tc.expected: expect normalWidth is return 12.0
     */
    Offset paintOffset_;
    Size viewPortSize_;
    double estimatedHeight = 0.0;
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON)); });
    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->normalWidth_ = Dimension(DEFAULT_WIDTH);
    double normalWidth = scrollBar->GetNormalWidthToPx();
    scrollBar->SetBarRegion(paintOffset_, viewPortSize_);
    EXPECT_EQ(normalWidth, 12.0);

    auto arcScrollBar = pattern_->GetScrollBar();
    scrollBar->normalWidth_ = Dimension(DEFAULT_WIDTH);
    double normalWidth1 = scrollBar->GetNormalWidthToPx();
    arcScrollBar->SetRoundTrickRegion(paintOffset_, viewPortSize_, paintOffset_, estimatedHeight);
    EXPECT_EQ(normalWidth1, 12.0);
}

/**
 * @tc.name: ArcScrollTestNg004
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CreateWithContent, call CalcPatternOffset
     * @tc.expected: expect value is 0
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON)); });
    auto scrollBar = pattern_->GetScrollBar();
    float scrollBarOffset = 0;
    EXPECT_FALSE(scrollBar->isDriving_);
    EXPECT_EQ(scrollBar->CalcPatternOffset(scrollBarOffset), 0);
}

/**
 * @tc.name: ArcScrollTestNg005
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CreateWithContent, call PlayScrollBarAppearAnimation
     * @tc.expected: expect scrollBar->displayMode_ is DisplayMode::ON
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON)); });

    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->PlayScrollBarAppearAnimation();
    EXPECT_EQ(scrollBar->displayMode_, DisplayMode::ON);
    EXPECT_TRUE(scrollBar->isScrollable_);
}

/**
 * @tc.name: ArcScrollTestNg006
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifer, call StartHoverAnimation
     * @tc.expected: expect hoverAnimatingType_ is SHRINK
     */
    ArcScrollBarOverlayModifier modifer;
    Point centerPoint(1, 1);
    float radius = 1;
    float startAngle = 1;
    float sweepAngle = 1;
    float width = 1;
    ArcRound backgroundArcBarRect(centerPoint, radius, startAngle, sweepAngle, width);
    auto hoverType = HoverAnimationType::SHRINK;
    modifer.StartHoverAnimation(backgroundArcBarRect, backgroundArcBarRect, HoverAnimationType::SHRINK);
    EXPECT_EQ(modifer.hoverAnimatingType_, hoverType);
}

/**
 * @tc.name: ArcScrollTestNg007
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifer, call onDraw
     */
    RSCanvas canvas;
    float width = 20;
    float height = 20;
    DrawingContext context { canvas, width, height };
    ArcScrollBarOverlayModifier modifer;
    modifer.onDraw(context);
    ASSERT_NE(modifer.strokeWidth_, nullptr);
    EXPECT_EQ(modifer.lastMainModeHeight_, 0.0f);
    EXPECT_EQ(modifer.lastMainModeOffset_, 0.0f);
    EXPECT_EQ(modifer.positionMode_, PositionMode::RIGHT);
    EXPECT_TRUE(modifer.isNavDestinationShow_);
}

/**
 * @tc.name: ArcScrollTestNg008
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifer, call DrawArc
     */
    RSCanvas canvas;
    float width = 0.0f;
    float height = 0.0f;
    DrawingContext context { canvas, width, height };
    ArcScrollBarOverlayModifier modifer;
    modifer.DrawArc(context);
    EXPECT_EQ(modifer.startAngle_->Get(), 0.0f);
    EXPECT_EQ(modifer.curveRadius_->Get(), 0.0f);
    EXPECT_EQ(modifer.positionMode_, PositionMode::RIGHT);
    EXPECT_TRUE(modifer.isScrollable_);
}

/**
 * @tc.name: ArcScrollTestNg009
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifer, call DrawBackgroundArc
     */
    RSCanvas canvas;
    float width = 0.0f;
    float height = 0.0f;
    DrawingContext context { canvas, width, height };
    ArcScrollBarOverlayModifier modifer;
    modifer.DrawBackgroundArc(context);
    EXPECT_EQ(modifer.backgroundStartAngle_->Get(), 0.0f);
    EXPECT_EQ(modifer.backgroundSweepAngle_->Get(), 0.0f);
}

/**
 * @tc.name: ArcScrollTestNg010
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifer, call StartArcBarAnimation
     * @tc.expected: expect backgroundStrokeWidth_->Get() is 5
     */
    bool needAdaptAnimation = true;
    Point centerPoint(1, 1);
    float radius = 5;
    ArcRound arcBarRect(centerPoint, radius, radius, radius, radius);
    ArcScrollBarOverlayModifier modifer;
    modifer.StartArcBarAnimation(HoverAnimationType::GROW,
        OpacityAnimationType::APPEAR, needAdaptAnimation, arcBarRect, arcBarRect);
    EXPECT_EQ(modifer.backgroundStrokeWidth_->Get(), 5);
    EXPECT_EQ(modifer.backgroundCurveRadius_->Get(), 5);
    EXPECT_EQ(modifer.backgroundStartAngle_->Get(), 5);
    EXPECT_EQ(modifer.backgroundSweepAngle_->Get(), 5);
}

/**
 * @tc.name: ArcScrollTestNg011
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create arcmodifer, call StartHoverAnimation and HoverAnimationType is GROW
     */
    Point centerPoint(1, 1);
    float radius = 20;
    ArcRound arcBarRect(centerPoint, radius, radius, radius, radius);
    ArcScrollBarOverlayModifier arcmodifer;
    arcmodifer.StartHoverAnimation(arcBarRect, arcBarRect, HoverAnimationType::GROW);
    arcmodifer.SetBackgroundBarColor(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);
    arcmodifer.SetCurveCenter(centerPoint);
    EXPECT_EQ(arcmodifer.backgroundStrokeWidth_->Get(), 20);
    EXPECT_EQ(arcmodifer.backgroundCurveRadius_->Get(), 20);
    EXPECT_EQ(arcmodifer.backgroundStartAngle_->Get(), 20);
    EXPECT_EQ(arcmodifer.backgroundSweepAngle_->Get(), 20);
    EXPECT_EQ(arcmodifer.curveCenter_->Get().GetX(), 1);
    EXPECT_EQ(arcmodifer.curveCenter_->Get().GetY(), 1);
}
} // namespace OHOS::Ace::NG
