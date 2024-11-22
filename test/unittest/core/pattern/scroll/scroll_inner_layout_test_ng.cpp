/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "mock_task_executor.h"
#include "scroll_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

namespace OHOS::Ace::NG {
namespace {
const Offset OUT_SCROLLBAR_OFFSET = Offset(100.f, 100.f);
const Offset IN_ACTIVE_BAR_OFFSET = Offset(238.f, 80.f);
const Point OUT_SCROLLBAR_POINT = Point(100.f, 100.f);
const Point IN_ACTIVE_BAR_POINT = Point(238.f, 80.f);
const Point BELOW_ACTIVE_BAR_POINT = Point(238.f, 300.f);
} // namespace

class ScrollInnerLayoutTestNg : public ScrollTestNg {
private:
    void VerifyDrawScrollBar(bool needDraw);
};

void ScrollInnerLayoutTestNg::VerifyDrawScrollBar(bool needDraw)
{
    Testing::MockCanvas canvas;
    // if has barWidth and barHeight, need draw scrollBar
    if (needDraw) {
        EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
        EXPECT_CALL(canvas, AttachBrush).WillOnce(ReturnRef(canvas));
        EXPECT_CALL(canvas, DetachBrush).WillOnce(ReturnRef(canvas));
    } else {
        EXPECT_CALL(canvas, DrawRoundRect(_)).Times(0);
    }
    DrawingContext drawingContext = { canvas, SCROLL_WIDTH, SCROLL_HEIGHT };
    FlushLayoutTask(frameNode_);
    auto scrollBarOverlayModifier = pattern_->GetScrollBarOverlayModifier();
    scrollBarOverlayModifier->onDraw(drawingContext);
}

/**
 * @tc.name: DrawScrollBar001
 * @tc.desc: Test Draw scrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, DrawScrollBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Has barWidth and barHeight
     * @tc.expected: Draw ScrollBar
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    VerifyDrawScrollBar(true);

    /**
     * @tc.steps: step2. No barWidth
     * @tc.expected: No Draw ScrollBar
     */
    scrollBar_->SetNormalWidth(Dimension(0));
    VerifyDrawScrollBar(false);

    /**
     * @tc.steps: step3. No barHeight
     * @tc.expected: No Draw ScrollBar
     */
    scrollBar_->SetNormalWidth(Dimension(10.f));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(0));
    FlushLayoutTask(frameNode_);
    VerifyDrawScrollBar(false);
}

/**
 * @tc.name: AdaptAnimation001
 * @tc.desc: Test ScrollBar Adapt Animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, AdaptAnimation001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Change Scroll height.
     * @tc.expected: The ScrollBar height self-adapt
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(2);
    EXPECT_CALL(canvas, AttachBrush).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush).WillRepeatedly(ReturnRef(canvas));
    DrawingContext drawingContext = { canvas, SCROLL_WIDTH, SCROLL_HEIGHT };
    auto scrollBarOverlayModifier = pattern_->GetScrollBarOverlayModifier();
    MockAnimationManager::GetInstance().SetTicks(TICK);
    const float contentHeight = SCROLL_HEIGHT - 10.f;
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(contentHeight));
    FlushLayoutTask(frameNode_, true);
    float ratio = contentHeight / CONTENT_MAIN_SIZE;
    float activeBarHeight = contentHeight * ratio;
    EXPECT_FLOAT_EQ(scrollBar_->activeRect_.Height(), activeBarHeight);
    MockAnimationManager::GetInstance().Tick();
    scrollBarOverlayModifier->onDraw(drawingContext);
    EXPECT_FALSE(scrollBarOverlayModifier->isAdaptAnimationStop_);
    MockAnimationManager::GetInstance().Tick();
    scrollBarOverlayModifier->onDraw(drawingContext);
    EXPECT_TRUE(scrollBarOverlayModifier->isAdaptAnimationStop_);
}

/**
 * @tc.name: Opacity001
 * @tc.desc: Test ScrollBar Opacity Animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, Opacity001, TestSize.Level1)
{
    auto mockTaskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = mockTaskExecutor;
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    mockTaskExecutor->RunDelayTask();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step1. DisplayMode::AUTO
     * @tc.expected: scrollBar is default hide
     */
    EXPECT_TRUE(scrollBar_->NeedPaint());
    auto scrollBarOverlayModifier = pattern_->GetScrollBarOverlayModifier();
    EXPECT_EQ(scrollBarOverlayModifier->GetOpacity(), 0);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Auto");

    /**
     * @tc.steps: step2. DisplayMode::ON
     * @tc.expected: Always show scrollBar
     */
    paintProperty_->UpdateScrollBarMode(DisplayMode::ON);
    pattern_->SetScrollBar(DisplayMode::ON);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.On");
    EXPECT_TRUE(scrollBar_->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->GetOpacity(), UINT8_MAX);

    /**
     * @tc.steps: step3. DisplayMode::OFF
     * @tc.expected: No scrollBar
     */
    paintProperty_->UpdateScrollBarMode(DisplayMode::OFF);
    pattern_->SetScrollBar(DisplayMode::OFF);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Off");
    EXPECT_EQ(pattern_->scrollBar_, nullptr);
    EXPECT_EQ(scrollBarOverlayModifier->GetOpacity(), 0);
}

/**
 * @tc.name: ScrollBarRect001
 * @tc.desc: Test scrollBar rect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, ScrollBarRect001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(scrollBar_->GetPositionMode(), PositionMode::RIGHT);
    float ratio = SCROLL_HEIGHT / CONTENT_MAIN_SIZE;
    float activeBarHeight = SCROLL_HEIGHT * ratio;
    EXPECT_TRUE(IsEqual(scrollBar_->touchRegion_, Rect(208, 0, DEFAULT_TOUCH_WIDTH, activeBarHeight)));
    EXPECT_TRUE(IsEqual(scrollBar_->hoverRegion_, Rect(232, 0, DEFAULT_ACTIVE_WIDTH, activeBarHeight)));
    EXPECT_TRUE(IsEqual(scrollBar_->barRect_, Rect(236, 0, NORMAL_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(scrollBar_->activeRect_, Rect(236, 0, NORMAL_WIDTH, activeBarHeight)));

    /**
     * @tc.steps: step1. Scroll some distance
     * @tc.expected: The ScrollBar offset has changed
     */
    ScrollTo(ITEM_MAIN_SIZE);
    float offsetY = ITEM_MAIN_SIZE * ratio;
    EXPECT_EQ(scrollBar_->touchRegion_.Top(), offsetY);
    EXPECT_EQ(scrollBar_->hoverRegion_.Top(), offsetY);
    EXPECT_EQ(scrollBar_->activeRect_.Top(), offsetY);
}

/**
 * @tc.name: ScrollBarRect002
 * @tc.desc: Test scrollBar rect with set barWidth
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, ScrollBarRect002, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetScrollBarWidth(Dimension(BAR_WIDTH));
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(scrollBar_->GetPositionMode(), PositionMode::RIGHT);
    float ratio = SCROLL_HEIGHT / CONTENT_MAIN_SIZE;
    float activeBarHeight = SCROLL_HEIGHT * ratio;
    EXPECT_TRUE(IsEqual(scrollBar_->touchRegion_, Rect(230, 0, BAR_WIDTH, activeBarHeight)));
    EXPECT_TRUE(IsEqual(scrollBar_->hoverRegion_, Rect(230, 0, BAR_WIDTH, activeBarHeight)));
    EXPECT_TRUE(IsEqual(scrollBar_->barRect_, Rect(230, 0, BAR_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(scrollBar_->activeRect_, Rect(230, 0, BAR_WIDTH, activeBarHeight)));
}

/**
 * @tc.name: ScrollBarRect003
 * @tc.desc: Test scrollBar rect in in RTL layout
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, ScrollBarRect003, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ScrollModelNG model = CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(scrollBar_->GetPositionMode(), PositionMode::LEFT);
    float ratio = SCROLL_HEIGHT / CONTENT_MAIN_SIZE;
    float activeBarHeight = SCROLL_HEIGHT * ratio;
    EXPECT_TRUE(
        IsEqual(scrollBar_->touchRegion_, Rect(0, 0, DEFAULT_TOUCH_WIDTH + DEFAULT_INACTIVE_WIDTH, activeBarHeight)));
    EXPECT_TRUE(
        IsEqual(scrollBar_->hoverRegion_, Rect(0, 0, DEFAULT_ACTIVE_WIDTH + DEFAULT_INACTIVE_WIDTH, activeBarHeight)));
    EXPECT_TRUE(IsEqual(scrollBar_->barRect_, Rect(0, 0, NORMAL_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(scrollBar_->activeRect_, Rect(0, 0, NORMAL_WIDTH, activeBarHeight)));

    /**
     * @tc.steps: step1. Scroll some distance
     * @tc.expected: The ScrollBar offset has changed
     */
    ScrollTo(ITEM_MAIN_SIZE);
    float offsetY = ITEM_MAIN_SIZE * ratio;
    EXPECT_EQ(scrollBar_->touchRegion_.Top(), offsetY);
    EXPECT_EQ(scrollBar_->hoverRegion_.Top(), offsetY);
    EXPECT_EQ(scrollBar_->activeRect_.Top(), offsetY);
}

/**
 * @tc.name: ScrollBarRect004
 * @tc.desc: Test scrollBar rect in in RTL layout with set barWidth
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, ScrollBarRect004, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ScrollModelNG model = CreateScroll();
    model.SetScrollBarWidth(Dimension(BAR_WIDTH));
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(scrollBar_->GetPositionMode(), PositionMode::LEFT);
    float ratio = SCROLL_HEIGHT / CONTENT_MAIN_SIZE;
    float activeBarHeight = SCROLL_HEIGHT * ratio;
    EXPECT_TRUE(IsEqual(scrollBar_->touchRegion_, Rect(0, 0, BAR_WIDTH, activeBarHeight)));
    EXPECT_TRUE(IsEqual(scrollBar_->hoverRegion_, Rect(0, 0, BAR_WIDTH, activeBarHeight)));
    EXPECT_TRUE(IsEqual(scrollBar_->barRect_, Rect(0, 0, BAR_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(scrollBar_->activeRect_, Rect(0, 0, BAR_WIDTH, activeBarHeight)));
}

/**
 * @tc.name: ScrollBarRect005
 * @tc.desc: Test scrollBar rect in Horizontal layout
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, ScrollBarRect005, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(scrollBar_->GetPositionMode(), PositionMode::BOTTOM);
    float ratio = SCROLL_WIDTH / CONTENT_MAIN_SIZE;
    float activeBarWidth = SCROLL_WIDTH * ratio;
    EXPECT_TRUE(IsEqual(scrollBar_->touchRegion_, Rect(0, 368, activeBarWidth, DEFAULT_TOUCH_WIDTH)));
    EXPECT_TRUE(IsEqual(scrollBar_->hoverRegion_, Rect(0, 392, activeBarWidth, DEFAULT_ACTIVE_WIDTH)));
    EXPECT_TRUE(IsEqual(scrollBar_->barRect_, Rect(0, 396, SCROLL_WIDTH, NORMAL_WIDTH)));
    EXPECT_TRUE(IsEqual(scrollBar_->activeRect_, Rect(0, 396, activeBarWidth, NORMAL_WIDTH)));

    /**
     * @tc.steps: step1. Scroll some distance
     * @tc.expected: The ScrollBar offset has changed
     */
    ScrollTo(ITEM_MAIN_SIZE);
    float offsetX = ITEM_MAIN_SIZE * ratio;
    EXPECT_FLOAT_EQ(scrollBar_->touchRegion_.Left(), offsetX);
    EXPECT_FLOAT_EQ(scrollBar_->hoverRegion_.Left(), offsetX);
    EXPECT_FLOAT_EQ(scrollBar_->activeRect_.Left(), offsetX);
}

/**
 * @tc.name: ScrollBarRect006
 * @tc.desc: Test scrollBar rect in Horizontal layout with set barWidth
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, ScrollBarRect006, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    model.SetScrollBarWidth(Dimension(BAR_WIDTH));
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(scrollBar_->GetPositionMode(), PositionMode::BOTTOM);
    float ratio = SCROLL_WIDTH / CONTENT_MAIN_SIZE;
    float activeBarWidth = SCROLL_WIDTH * ratio;
    EXPECT_TRUE(IsEqual(scrollBar_->touchRegion_, Rect(0, 390, activeBarWidth, BAR_WIDTH)));
    EXPECT_TRUE(IsEqual(scrollBar_->hoverRegion_, Rect(0, 390, activeBarWidth, BAR_WIDTH)));
    EXPECT_TRUE(IsEqual(scrollBar_->barRect_, Rect(0, 390, SCROLL_WIDTH, BAR_WIDTH)));
    EXPECT_TRUE(IsEqual(scrollBar_->activeRect_, Rect(0, 390, activeBarWidth, BAR_WIDTH)));
}

/**
 * @tc.name: ScrollBarWidth001
 * @tc.desc: Test scrollbar diff width
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, ScrollBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Not set scrollBar width
     * @tc.expected: It will be default
     */
    ScrollModelNG model = CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(scrollBar_->activeRect_.Width(), NORMAL_WIDTH);
    EXPECT_EQ(scrollBar_->barRect_.Width(), NORMAL_WIDTH);

    /**
     * @tc.steps: step2. Set scrollBar width less than scrollBar height
     * @tc.expected: It will be the value that was set
     */
    model.SetScrollBarWidth(AceType::RawPtr(frameNode_), Dimension(BAR_WIDTH));
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(scrollBar_->activeRect_.Width(), BAR_WIDTH);
    EXPECT_EQ(scrollBar_->barRect_.Width(), BAR_WIDTH);

    /**
     * @tc.steps: step3. Set scrollBar width greater than SCROLL_HEIGHT
     * @tc.expected: It will be default
     */
    model.SetScrollBarWidth(AceType::RawPtr(frameNode_), Dimension(SCROLL_HEIGHT + 1));
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(scrollBar_->activeRect_.Width(), NORMAL_WIDTH);
    EXPECT_EQ(scrollBar_->barRect_.Width(), NORMAL_WIDTH);

    /**
     * @tc.steps: step4. Set scrollBar width less than SCROLL_HEIGHT
     * @tc.expected: The scrollBar width will be the value that was set,
     * and scrollBar height will be equal to scrollBar width
     */
    float barWidth = SCROLL_HEIGHT - 1;
    model.SetScrollBarWidth(AceType::RawPtr(frameNode_), Dimension(barWidth));
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(scrollBar_->activeRect_.Width(), barWidth);
    EXPECT_EQ(scrollBar_->activeRect_.Height(), barWidth);
    EXPECT_EQ(scrollBar_->barRect_.Width(), barWidth);
    EXPECT_EQ(scrollBar_->barRect_.Height(), SCROLL_HEIGHT);
}

/**
 * @tc.name: ScrollBarRound001
 * @tc.desc: Test SetRoundTrickRegion
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, ScrollBarRound001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    scrollBar_->SetShapeMode(ShapeMode::ROUND);
    scrollBar_->FlushBarWidth();
    EXPECT_EQ(scrollBar_->trickStartAngle_, -30);

    scrollBar_->SetPositionMode(PositionMode::LEFT);
    scrollBar_->FlushBarWidth();
    EXPECT_EQ(scrollBar_->trickStartAngle_, -150);

    auto contentNode = GetChildFrameNode(frameNode_, 0);
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(SCROLL_WIDTH));
    FlushLayoutTask(frameNode_, true);
    scrollBar_->FlushBarWidth();
    EXPECT_EQ(scrollBar_->trickStartAngle_, -150);
}

/**
 * @tc.name: CalcReservedHeight001
 * @tc.desc: Test CalcReservedHeight
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, CalcReservedHeight001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    scrollBar_->SetPositionMode(PositionMode::LEFT);
    scrollBar_->SetNormalWidth(Dimension(1)); // call CalcReservedHeight;
    EXPECT_EQ(scrollBar_->endReservedHeight_.Value(), 0);

    BorderRadiusProperty borderRadiusProperty;
    float radius = 13.f;
    borderRadiusProperty.radiusTopRight = std::make_optional<Dimension>(radius);
    borderRadiusProperty.radiusBottomRight = std::make_optional<Dimension>(radius);
    scrollBar_->SetHostBorderRadius(borderRadiusProperty);
    scrollBar_->SetPadding(Edge(1, 1, 1, 1));
    scrollBar_->SetPositionMode(PositionMode::RIGHT);
    scrollBar_->SetNormalWidth(Dimension(2)); // call CalcReservedHeight;
    EXPECT_EQ(scrollBar_->startReservedHeight_.ConvertToPx(), 14.5);
    EXPECT_EQ(scrollBar_->endReservedHeight_.ConvertToPx(), 14.5);

    borderRadiusProperty.radiusBottomLeft = std::make_optional<Dimension>(radius);
    borderRadiusProperty.radiusBottomRight = std::make_optional<Dimension>(radius);
    scrollBar_->SetHostBorderRadius(borderRadiusProperty);
    scrollBar_->SetPadding(Edge(1, 1, 1, 1));
    scrollBar_->SetPositionMode(PositionMode::BOTTOM);
    scrollBar_->SetNormalWidth(Dimension(6)); // call CalcReservedHeight;
    EXPECT_EQ(scrollBar_->startReservedHeight_.ConvertToPx(), 11.25);
    EXPECT_EQ(scrollBar_->endReservedHeight_.ConvertToPx(), 11.25);
}

/**
 * @tc.name: OtherTest001
 * @tc.desc: Test InBarTouchRegion/InBarHoverRegion/InBarRectRegion
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, OtherTest001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. NeedPaint and ShapeMode::RECT
     */
    EXPECT_TRUE(scrollBar_->NeedPaint());
    EXPECT_EQ(scrollBar_->GetShapeMode(), ShapeMode::RECT);
    EXPECT_FALSE(scrollBar_->InBarTouchRegion(OUT_SCROLLBAR_POINT));
    EXPECT_FALSE(scrollBar_->InBarHoverRegion(OUT_SCROLLBAR_POINT));
    EXPECT_FALSE(scrollBar_->InBarRectRegion(OUT_SCROLLBAR_POINT));
    EXPECT_TRUE(scrollBar_->InBarTouchRegion(IN_ACTIVE_BAR_POINT));
    EXPECT_TRUE(scrollBar_->InBarHoverRegion(IN_ACTIVE_BAR_POINT));
    EXPECT_TRUE(scrollBar_->InBarRectRegion(IN_ACTIVE_BAR_POINT));
    EXPECT_FALSE(scrollBar_->InBarTouchRegion(BELOW_ACTIVE_BAR_POINT));
    EXPECT_FALSE(scrollBar_->InBarHoverRegion(BELOW_ACTIVE_BAR_POINT));
    EXPECT_TRUE(scrollBar_->InBarRectRegion(BELOW_ACTIVE_BAR_POINT));

    /**
     * @tc.steps: step2. NeedPaint and ShapeMode::ROUND
     */
    scrollBar_->SetShapeMode(ShapeMode::ROUND);
    EXPECT_TRUE(scrollBar_->NeedPaint());
    EXPECT_EQ(scrollBar_->GetShapeMode(), ShapeMode::ROUND);
    EXPECT_FALSE(scrollBar_->InBarTouchRegion(IN_ACTIVE_BAR_POINT));
    EXPECT_FALSE(scrollBar_->InBarHoverRegion(IN_ACTIVE_BAR_POINT));
    EXPECT_FALSE(scrollBar_->InBarRectRegion(IN_ACTIVE_BAR_POINT));

    /**
     * @tc.steps: step3. !NeedPaint and ShapeMode::RECT
     */
    scrollBar_->SetDisplayMode(DisplayMode::OFF);
    scrollBar_->SetShapeMode(ShapeMode::RECT);
    EXPECT_FALSE(scrollBar_->NeedPaint());
    EXPECT_EQ(scrollBar_->GetShapeMode(), ShapeMode::RECT);
    EXPECT_FALSE(scrollBar_->InBarTouchRegion(IN_ACTIVE_BAR_POINT));
    EXPECT_FALSE(scrollBar_->InBarHoverRegion(IN_ACTIVE_BAR_POINT));
    EXPECT_FALSE(scrollBar_->InBarRectRegion(IN_ACTIVE_BAR_POINT));
}

/**
 * @tc.name: OtherTest002
 * @tc.desc: Test UpdateActiveRectSize/UpdateActiveRectOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, OtherTest002, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();

    scrollBar_->SetPositionMode(PositionMode::LEFT);
    scrollBar_->UpdateActiveRectSize(20.f);
    EXPECT_EQ(scrollBar_->touchRegion_.Height(), 20.f);
    scrollBar_->UpdateActiveRectOffset(30.f);
    EXPECT_EQ(scrollBar_->touchRegion_.Top(), 30.f);

    scrollBar_->SetPositionMode(PositionMode::BOTTOM);
    scrollBar_->UpdateActiveRectSize(20.f);
    EXPECT_EQ(scrollBar_->touchRegion_.Width(), 20.f);
    scrollBar_->UpdateActiveRectOffset(30.f);
    EXPECT_EQ(scrollBar_->touchRegion_.Left(), 30.f);

    scrollBar_->SetPositionMode(PositionMode::RIGHT);
    scrollBar_->UpdateActiveRectSize(20.f);
    EXPECT_EQ(scrollBar_->touchRegion_.Width(), 20.f);
    scrollBar_->UpdateActiveRectOffset(30.f);
    EXPECT_EQ(scrollBar_->touchRegion_.Left(), 30.f);
}

/**
 * @tc.name: SetScrollBar001
 * @tc.desc: Test set inner scrollbar off
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, SetScrollBar001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step1. DisplayMode::AUTO
     * @tc.expected: the opacity of scrollBar is 255
     */
    EXPECT_TRUE(scrollBar_->NeedPaint());
    auto scrollBarOverlayModifier = pattern_->GetScrollBarOverlayModifier();
    EXPECT_EQ(scrollBarOverlayModifier->GetOpacity(), 255);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Auto");

    /**
     * @tc.steps: step2. set DisplayMode::OFF and not trigger onModifyDone
     * @tc.expected: the opacity of scrollBar is 0
     */
    paintProperty_->UpdateScrollBarMode(DisplayMode::OFF);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Off");
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->GetScrollBarOverlayModifier()->GetOpacity(), 0);
}

/**
 * @tc.name: SetScrollBar002
 * @tc.desc: Test set inner scrollbar on
 * @tc.type: FUNC
 */
HWTEST_F(ScrollInnerLayoutTestNg, SetScrollBar002, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent();
    CreateScrollDone();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step1. DisplayMode::OFF
     * @tc.expected: the opacity of scrollBar is 0
     */
    paintProperty_->UpdateScrollBarMode(DisplayMode::OFF);
    pattern_->TriggerModifyDone();
    FlushLayoutTask(frameNode_);
    auto scrollBarOverlayModifier = pattern_->GetScrollBarOverlayModifier();
    EXPECT_EQ(scrollBarOverlayModifier->GetOpacity(), 0);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Off");

    /**
     * @tc.steps: step2. set DisplayMode::On and not trigger OnDirtyLayoutWrapperSwap
     * @tc.expected: the opacity of scrollBar is 255
     */
    paintProperty_->UpdateScrollBarMode(DisplayMode::ON);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.On");
    pattern_->TriggerModifyDone();
    EXPECT_EQ(pattern_->GetScrollBarOverlayModifier()->GetOpacity(), 255);
}
} // namespace OHOS::Ace::NG
