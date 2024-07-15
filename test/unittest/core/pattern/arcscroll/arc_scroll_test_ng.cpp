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
#include "core/components_ng/pattern/arc_scroll/arc_scroll_paint_method.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
namespace OHOS::Ace::NG {
constexpr float WIDTH = 12.0f;
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
        }, SNAP_ITEM_NUMBER);
}

void ArcScrollTestNg::CreateContent(int32_t childNumber)
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
     * @tc.steps: step1. Create CreateWithContent, call UpdateOverlayModifier
     * @tc.expected: paintWrapper is not nullptr
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON)); });
    auto paint = AceType::MakeRefPtr<ArcScrollPaintMethod>();

    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    ASSERT_NE(paintWrapper, nullptr);
    paint->UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));

    auto scrollBar = AceType::DynamicCast<ArcScrollBar> (pattern_->GetScrollBar());
    scrollBar->positionModeUpdate_ = true;
    paint->UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
    ASSERT_NE(scrollBar, nullptr);
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


    /**
     * @tc.steps: step1. SetDisplayMode is off, call InBarTouchRegion
     * @tc.expected: expect InBarTouchRegion return false
     */
    scrollBar->SetDisplayMode(DisplayMode::OFF);
    EXPECT_FALSE(scrollBar->InBarTouchRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarHoverRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarRectRegion(Point(0, 0)));
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
    scrollBar->normalWidth_ = Dimension(WIDTH);
    double normalWidth = scrollBar->GetNormalWidthToPx();
    scrollBar->SetBarRegion(paintOffset_, viewPortSize_);
    EXPECT_EQ(normalWidth, 12.0);

    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar> (pattern_->GetScrollBar());
    scrollBar->normalWidth_ = Dimension(WIDTH);
    double normalWidth1 = scrollBar->GetNormalWidthToPx();
    arcScrollBar->SetRoundTrickRegion(estimatedHeight, estimatedHeight, estimatedHeight,
        estimatedHeight, estimatedHeight, viewPortSize_);
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
     * @tc.steps: step1. Create CreateWithContent, call HandlingTouch
     * @tc.expected: expect scrollBar is not nullptr
     */
    TouchLocationInfo locationInfo(1);
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON)); });
    auto scrollBar = AceType::DynamicCast<ArcScrollBar> (pattern_->GetScrollBar());
    TouchEventInfo eventInfo("touch");
    eventInfo.SetSourceDevice(SourceType::TOUCH);
    eventInfo.AddTouchLocationInfo(std::move(locationInfo));
    scrollBar->HandlingTouch(eventInfo);
    ASSERT_NE(scrollBar, nullptr);

    locationInfo.SetTouchType(TouchType::DOWN);
    locationInfo.SetSourceDevice(SourceType::TOUCH);
    eventInfo.AddTouchLocationInfo(std::move(locationInfo));
    scrollBar->HandlingTouch(eventInfo);
    locationInfo.SetTouchType(TouchType::DOWN);
    locationInfo.SetSourceDevice(SourceType::MOUSE);
    eventInfo.AddTouchLocationInfo(std::move(locationInfo));
    scrollBar->HandlingTouch(eventInfo);
}

/**
 * @tc.name: ArcScrollTestNg005
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CreateWithContent, call CalcPatternOffset
     * @tc.expected: expect value is 0
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON)); });
    auto scrollBar = pattern_->GetScrollBar();
    float scrollBarOffset = 0;
    auto value = scrollBar->CalcPatternOffset(scrollBarOffset);
    EXPECT_EQ(value, 0);

    scrollBar->isDriving_ = true;
    scrollBar->barRegionSize_ = 100.0;
    auto offset = scrollBar->CalcPatternOffset(scrollBarOffset);
    EXPECT_EQ(offset, 0);
}

/**
 * @tc.name: ArcScrollTestNg006
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CreateWithContent, call ScheduleShrinkDelayTask
     * @tc.expected: expect scrollBar is not nullptr
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON)); });
    auto scrollBar = AceType::DynamicCast<ArcScrollBar> (pattern_->GetScrollBar());
    scrollBar->ScheduleShrinkDelayTask();
    ASSERT_NE(scrollBar, nullptr);
}

/**
 * @tc.name: ArcScrollTestNg007
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CreateWithContent, call PlayScrollBarAppearAnimation
     * @tc.expected: expect scrollBar is not nullptr
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON)); });
    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->PlayScrollBarAppearAnimation();
    ASSERT_NE(scrollBar, nullptr);
}

/**
 * @tc.name: ArcScrollTestNg008
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg008, TestSize.Level1)
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
 * @tc.name: ArcScrollTestNg009
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifer, call onDraw
     * @tc.expected: expect strokeWidth_ is not nullptr
     */
    RSCanvas canvas;
    float width = 0;
    float height = 0;
    DrawingContext context { canvas, width, height };
    ArcScrollBarOverlayModifier modifer;
    modifer.onDraw(context);
    ASSERT_NE(modifer.strokeWidth_, nullptr);
    ASSERT_NE(modifer.curveCenter_, nullptr);
    ASSERT_NE(modifer.startAngle_, nullptr);
    ASSERT_NE(modifer.sweepAngle_, nullptr);
    ASSERT_NE(modifer.curveRadius_, nullptr);
}

/**
 * @tc.name: ArcScrollTestNg010
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifer, call DrawArc
     * @tc.expected: expect startAngle_ is not nullptr
     */
    RSCanvas canvas;
    float width = 0;
    float height = 0;
    DrawingContext context { canvas, width, height };
    ArcScrollBarOverlayModifier modifer;
    modifer.DrawArc(context);
    ASSERT_NE(modifer.startAngle_, nullptr);
    ASSERT_NE(modifer.curveRadius_, nullptr);
}

/**
 * @tc.name: ArcScrollTestNg011
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifer, call DrawBackgroundArc
     * @tc.expected: expect backgroundStartAngle_ is not nullptr
     */
    RSCanvas canvas;
    float width = 0;
    float height = 0;
    DrawingContext context { canvas, width, height };
    ArcScrollBarOverlayModifier modifer;
    modifer.DrawBackgroundArc(context);
    ASSERT_NE(modifer.backgroundStartAngle_, nullptr);
    ASSERT_NE(modifer.backgroundSweepAngle_, nullptr);
}

/**
 * @tc.name: ArcScrollTestNg012
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifer, call StartArcBarAnimation
     * @tc.expected: expect needAdaptAnimation is true
     */
    bool needAdaptAnimation = true;
    Point centerPoint(1, 1);
    float radius = 1;
    ArcRound arcBarRect(centerPoint, radius, radius, radius, radius);
    ArcScrollBarOverlayModifier modifer;
    modifer.StartArcBarAnimation(HoverAnimationType::GROW, OpacityAnimationType::APPEAR, needAdaptAnimation,
        arcBarRect, arcBarRect);
    EXPECT_TRUE(needAdaptAnimation);
}

/**
 * @tc.name: ArcScrollTestNg013
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollTestNg, ArcScrollTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create arcmodifer, call StartHoverAnimation and HoverAnimationType is GROW
     * @tc.expected: expect hoverAnimation_ is not nullptr
     */
    Point centerPoint(1, 1);
    float radius = 1;
    ArcRound arcBarRect(centerPoint, radius, radius, radius, radius);
    ArcScrollBarOverlayModifier arcmodifer;
    arcmodifer.StartHoverAnimation(arcBarRect, arcBarRect, HoverAnimationType::GROW);

    /**
     * @tc.steps: step1. Create arcmodifer, HoverAnimationType is NONE
     */
    arcmodifer.StartHoverAnimation(arcBarRect, arcBarRect, HoverAnimationType::NONE);
    ScrollBarOverlayModifier modifer;
    EXPECT_EQ(modifer.hoverAnimation_, nullptr);
}
} // namespace OHOS::Ace::NG