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

#include <utility>

#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/scrollable/scrollable_test_utils.h"
#include "water_flow_test_ng.h"

#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {
/**
 * @tc.name: Clip001
 * @tc.desc: Test contentClip.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Clip001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetMargin(CalcLength(5.0f));
    ViewAbstract::SetPadding(CalcLength(5.0f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    auto props = frameNode_->GetPaintProperty<ScrollablePaintProperty>();

    auto rect = AceType::MakeRefPtr<ShapeRect>();
    rect->SetWidth(Dimension(200.0f));
    rect->SetHeight(Dimension(200.0f));
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(rect))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CUSTOM, rect });
    FlushUITasks();

    auto waterFlowRect = frameNode_->GetGeometryNode()->GetPaddingRect();
    waterFlowRect.SetOffset(
        frameNode_->GetGeometryNode()->GetPaddingOffset() - frameNode_->GetGeometryNode()->GetFrameOffset());
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(waterFlowRect))).Times(1);
    props->UpdateContentClip({ ContentClipMode::SAFE_AREA, nullptr });
    FlushUITasks();

    waterFlowRect = frameNode_->GetGeometryNode()->GetFrameRect();
    waterFlowRect.SetOffset({ 0.0f, 0.0f });
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(waterFlowRect))).Times(1);
    props->UpdateContentClip({ ContentClipMode::BOUNDARY, nullptr });
    FlushUITasks();
}

/**
 * @tc.name: Clip002
 * @tc.desc: Test contentClip with relative offset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Clip002, TestSize.Level1)
{
    RefPtr<UINode> col;
    CreateColumn([&](ColumnModelNG colModel) {
        ViewAbstract::SetMargin(CalcLength(5.0f));
        col = ViewStackProcessor::GetInstance()->GetMainElementNode();

        WaterFlowModelNG model = CreateWaterFlow();
        ViewAbstract::SetMargin(CalcLength(5.0f));
        ViewAbstract::SetPadding(CalcLength(5.0f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
        CreateWaterFlowItems();
        CreateDone();
    });
    ASSERT_TRUE(col);
    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    auto props = frameNode_->GetPaintProperty<ScrollablePaintProperty>();

    auto rect = AceType::MakeRefPtr<ShapeRect>();
    rect->SetWidth(Dimension(200.0f));
    rect->SetHeight(Dimension(200.0f));
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(rect))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CUSTOM, rect });
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(frameNode_->GetGeometryNode()->GetPaddingSize(true), SizeF(470.0f, 790.0f));
    auto rect1 = frameNode_->GetGeometryNode()->GetPaddingRect();
    rect1.SetOffset(OffsetF(5.0f, 5.0f)); // padding offset
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(rect1))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CONTENT_ONLY, nullptr });
    FlushLayoutTask(frameNode_);

    auto rect2 = frameNode_->GetGeometryNode()->GetFrameRect();
    rect2.SetOffset(OffsetF(0.0f, 0.0f));
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(rect2))).Times(1);
    props->UpdateContentClip({ ContentClipMode::BOUNDARY, nullptr });
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: Clip003
 * @tc.desc: Test contentClip with SafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Clip003, TestSize.Level1)
{
    RefPtr<UINode> col;
    CreateColumn([&](ColumnModelNG colModel) {
        ViewAbstract::SetSafeAreaPadding(CalcLength(2.0f));
        ViewAbstract::SetMargin(CalcLength(5.0f));
        col = ViewStackProcessor::GetInstance()->GetMainElementNode();

        WaterFlowModelNG model = CreateWaterFlow();
        ViewAbstract::SetSafeAreaPadding(CalcLength(5.0f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
        CreateWaterFlowItems();
        CreateDone();
    });
    ASSERT_TRUE(col);
    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    auto props = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameRect().ToString(), "RectT (2.00, 2.00) - [480.00 x 800.00]");
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(RectF(5, 5, 470.0f, 790.0f)))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CONTENT_ONLY, nullptr });
    FlushLayoutTask(frameNode_);

    ASSERT_TRUE(frameNode_->GetGeometryNode()->GetResolvedSingleSafeAreaPadding());
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(RectF(-2, -2, 484, 804)))).Times(1);
    props->UpdateContentClip({ ContentClipMode::SAFE_AREA, nullptr });
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: Clip004
 * @tc.desc: Test contentClip with SafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Clip004, TestSize.Level1)
{
    RefPtr<UINode> col;
    CreateColumn([&](ColumnModelNG colModel) {
        ViewAbstract::SetSafeAreaPadding(CalcLength(2.0f));
        ViewAbstract::SetMargin(CalcLength(5.0f));
        col = ViewStackProcessor::GetInstance()->GetMainElementNode();

        WaterFlowModelNG model = CreateWaterFlow();
        ViewAbstract::SetSafeAreaPadding(CalcLength(5.0f));
        ViewAbstract::SetPadding(CalcLength(1.0f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
        CreateWaterFlowItems();
        CreateDone();
    });
    ASSERT_TRUE(col);
    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    auto props = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameRect().ToString(), "RectT (2.00, 2.00) - [480.00 x 800.00]");

    ASSERT_TRUE(frameNode_->GetGeometryNode()->GetResolvedSingleSafeAreaPadding());
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(RectF(1, 1, 478, 798)))).Times(1);
    props->UpdateContentClip({ ContentClipMode::SAFE_AREA, nullptr });
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: Clip005
 * @tc.desc: Test contentClip with SafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Clip005, TestSize.Level1)
{
    RefPtr<UINode> col;
    CreateColumn([&](ColumnModelNG colModel) {
        ViewAbstract::SetSafeAreaPadding(CalcLength(2.0f));
        ViewAbstract::SetMargin(CalcLength(5.0f));
        col = ViewStackProcessor::GetInstance()->GetMainElementNode();

        WaterFlowModelNG model = CreateWaterFlow();
        ViewAbstract::SetSafeAreaPadding(CalcLength(5.0f));
        ViewAbstract::SetMargin(CalcLength(1.0f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
        CreateWaterFlowItems();
        CreateDone();
    });
    ASSERT_TRUE(col);
    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    auto props = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameRect().ToString(), "RectT (3.00, 3.00) - [480.00 x 800.00]");

    ASSERT_TRUE(frameNode_->GetGeometryNode()->GetResolvedSingleSafeAreaPadding());
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(RectF(0, 0, 480, 800)))).Times(1);
    props->UpdateContentClip({ ContentClipMode::SAFE_AREA, nullptr });
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: WaterFlowPaintMethod001
 * @tc.desc: Test UpdateOverlayModifier.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowPaintMethod001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    model.SetScrollBarMode(DisplayMode::AUTO);
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step2. not set positionMode.
     * @tc.expected: the positionMode_ of scrollBarOverlayModifier_ is default value.
     */
    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->SetScrollable(true);

    auto paintMethod = pattern_->CreateNodePaintMethod();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(),
        frameNode_->GetPaintProperty<ScrollablePaintProperty>());
    paintMethod->UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(pattern_->GetScrollBarOverlayModifier()->positionMode_, PositionMode::RIGHT);

    /**
     * @tc.steps: step3. scrollBar setting positionMode set to bottom.
     * @tc.expected: the positionMode_ of scrollBarOverlayModifier_ is bottom.
     */
    pattern_->SetEdgeEffect(EdgeEffect::FADE);
    scrollBar->SetPositionMode(PositionMode::BOTTOM);

    paintMethod = pattern_->CreateNodePaintMethod();
    paintWrapper = AceType::MakeRefPtr<PaintWrapper>(frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(),
        frameNode_->GetPaintProperty<ScrollablePaintProperty>());
    paintMethod->UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(pattern_->GetScrollBarOverlayModifier()->positionMode_, PositionMode::BOTTOM);
}
} // namespace OHOS::Ace::NG