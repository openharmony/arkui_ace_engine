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

#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "gtest/internal/gtest-internal.h"

#define private public
#define protected public

#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/select_overlay/select_overlay_content_modifier.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_modifier.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class MyRSCanvas : public OHOS::Ace::Testing::TestingCanvas {
public:
    void ClipRect(const Testing::TestingRect& rect, Testing::ClipOp op, bool doAntiAlias)
    {
        myRect_ = rect;
    }

    Testing::TestingRect myRect_;
};

class SelectOverlayContentModifierTestNg : public testing::Test {
public:
};

/**
 * @tc.name: ClipHandleDrawRect001
 * @tc.desc: test ClipHandleDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, ClipHandleDrawRect001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    MyRSCanvas canvas;
    RectF handleRect = RectF(5.0f, 5.0f, 5.0f, 5.0f);
    contentModifier.SetClipHandleDrawRect(true);
    contentModifier.ClipHandleDrawRect(canvas, handleRect, true, true);
    EXPECT_EQ(canvas.myRect_.GetLeft(), 5.0f);
    EXPECT_EQ(canvas.myRect_.GetRight(), 0.0f);
    EXPECT_EQ(canvas.myRect_.GetTop(), 0.0f);
    EXPECT_EQ(canvas.myRect_.GetBottom(), 0.0f);
}

/**
 * @tc.name: ClipHandleDrawRect002
 * @tc.desc: test ClipHandleDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, ClipHandleDrawRect002, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    MyRSCanvas canvas;
    RectF handleRect = RectF(5.0f, 0.0f, 5.0f, 0.0f);
    contentModifier.SetClipHandleDrawRect(true);
    contentModifier.ClipHandleDrawRect(canvas, handleRect, false, false);
    EXPECT_EQ(canvas.myRect_.GetLeft(), 5.0f);
    EXPECT_EQ(canvas.myRect_.GetRight(), 0.0f);
    EXPECT_EQ(canvas.myRect_.GetTop(), -2.5f);
    EXPECT_EQ(canvas.myRect_.GetBottom(), 0.0f);
}

/**
 * @tc.name: ClipHandleDrawRect003
 * @tc.desc: test ClipHandleDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, ClipHandleDrawRect003, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    MyRSCanvas canvas;
    RectF handleRect = RectF(5.0f, -5.0f, 5.0f, -5.0f);
    contentModifier.SetClipHandleDrawRect(true);
    contentModifier.ClipHandleDrawRect(canvas, handleRect, true, false);
    EXPECT_EQ(canvas.myRect_.GetLeft(), 5.0f);
    EXPECT_EQ(canvas.myRect_.GetRight(), 0.0f);
    EXPECT_EQ(canvas.myRect_.GetTop(), 0.0f);
    EXPECT_EQ(canvas.myRect_.GetBottom(), 2.5f);
}

/**
 * @tc.name: ClipHandleDrawRect004
 * @tc.desc: test ClipHandleDrawRect.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, ClipHandleDrawRect004, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    MyRSCanvas canvas;
    RectF handleRect = RectF(5.0f, 5.0f, 5.0f, 5.0f);
    contentModifier.SetClipHandleDrawRect(true);
    contentModifier.ClipHandleDrawRect(canvas, handleRect, false, false);
    EXPECT_EQ(canvas.myRect_.GetLeft(), 5.0f);
    EXPECT_EQ(canvas.myRect_.GetRight(), 0.0f);
    EXPECT_EQ(canvas.myRect_.GetTop(), -2.5f);
    EXPECT_EQ(canvas.myRect_.GetBottom(), 0.0f);
}

/**
 * @tc.name: PaintHandle001
 * @tc.desc: test PaintHandle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, PaintHandle001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    Testing::MockCanvas canvas;
    HandleDrawInfo handleInfo;
    handleInfo.isCircleShow = false;
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Translate(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachPen()).Times(0);
    contentModifier.PaintHandle(canvas, handleInfo);
}

/**
 * @tc.name: PaintHandleLine001
 * @tc.desc: test PaintHandleLine.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, PaintHandleLine001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    Testing::MockCanvas canvas;
    HandleDrawInfo handleInfo;
    Color handleColor;
    EXPECT_CALL(canvas, DetachPen()).Times(0);
    contentModifier.PaintHandleLine(canvas, handleInfo, handleColor);
}

/**
 * @tc.name: GetFirstPaintRect001
 * @tc.desc: test GetFirstPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, GetFirstPaintRect001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    contentModifier.SetPaintHandleUsePoints(true);
    SelectHandlePaintInfo firstHandlePaintInfo;
    firstHandlePaintInfo.startPoint = OffsetF(0.0f, 0.0f);
    firstHandlePaintInfo.endPoint = OffsetF(120.0f, 120.0f);
    contentModifier.SetFirstHandlePaintInfo(firstHandlePaintInfo);
    auto result = contentModifier.GetFirstPaintRect();
    EXPECT_EQ(result.Width(), 120.0f);
    EXPECT_EQ(result.Height(), 120.0f);
}

/**
 * @tc.name: GetSecondPaintRect001
 * @tc.desc: test GetSecondPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, GetSecondPaintRect001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    contentModifier.SetPaintHandleUsePoints(true);
    SelectHandlePaintInfo secondHandlePaintInfo;
    secondHandlePaintInfo.startPoint = OffsetF(0.0f, 0.0f);
    secondHandlePaintInfo.endPoint = OffsetF(120.0f, 120.0f);
    contentModifier.SetSecondHandlePaintInfo(secondHandlePaintInfo);
    auto result = contentModifier.GetSecondPaintRect();
    EXPECT_EQ(result.Width(), 120.0f);
    EXPECT_EQ(result.Height(), 120.0f);
}

/**
 * @tc.name: ClipViewPort001
 * @tc.desc: test ClipViewPort.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, ClipViewPort001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    Testing::MockCanvas canvas;
    RectF handleRect = RectF(5.0f, 5.0f, 5.0f, 5.0f);
    contentModifier.SetIsOverlayMode(false);
    EXPECT_CALL(canvas, ClipRect(_, _, _)).Times(0);
    contentModifier.ClipViewPort(canvas);
}

/**
 * @tc.name: ClipViewPort002
 * @tc.desc: test ClipViewPort.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, ClipViewPort002, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    Testing::MockCanvas canvas;
    RectF handleRect = RectF(5.0f, 5.0f, 5.0f, 5.0f);
    contentModifier.SetIsOverlayMode(true);
    contentModifier.SetClipHandleDrawRect(true);
    EXPECT_CALL(canvas, ClipRect(_, _, _)).Times(0);
    contentModifier.ClipViewPort(canvas);
}

/**
 * @tc.name: PaintDoubleHandleWithRect001
 * @tc.desc: test PaintDoubleHandleWithRect.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, PaintDoubleHandleWithRect001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    Testing::MockCanvas canvas;
    contentModifier.SetFirstHandleIsShow(false);
    contentModifier.SetSecondHandleIsShow(false);
    contentModifier.SetClipHandleDrawRect(false);
    EXPECT_CALL(canvas, Restore()).Times(0);
    contentModifier.PaintDoubleHandleWithRect(canvas);
}

/**
 * @tc.name: PaintDoubleHandleWithPoint001
 * @tc.desc: test PaintDoubleHandleWithPoint.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, PaintDoubleHandleWithPoint001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    Testing::MockCanvas canvas;
    contentModifier.SetPaintHandleUsePoints(true);
    contentModifier.SetFirstHandleIsShow(false);
    contentModifier.SetSecondHandleIsShow(false);
    EXPECT_CALL(canvas, Save()).Times(0);
    contentModifier.PaintDoubleHandleWithPoint(canvas);
}

/**
 * @tc.name: PaintSingleHandleWithRect001
 * @tc.desc: test PaintSingleHandleWithRect.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, PaintSingleHandleWithRect001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    Testing::MockCanvas canvas;
    contentModifier.SetFirstHandleIsShow(false);
    contentModifier.SetSecondHandleIsShow(false);
    contentModifier.SetClipHandleDrawRect(false);
    EXPECT_CALL(canvas, Restore()).Times(0);
    contentModifier.PaintSingleHandleWithRect(canvas);
}

/**
 * @tc.name: PaintSingleHandleWithPoints001
 * @tc.desc: test PaintSingleHandleWithPoints.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, PaintSingleHandleWithPoints001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    SelectOverlayContentModifier contentModifier = SelectOverlayContentModifier(pattern);
    Testing::MockCanvas canvas;
    contentModifier.SetPaintHandleUsePoints(true);
    contentModifier.SetFirstHandleIsShow(false);
    contentModifier.SetSecondHandleIsShow(false);
    EXPECT_CALL(canvas, Save()).Times(0);
    contentModifier.PaintSingleHandleWithPoints(canvas);
}

/**
 * @tc.name: DrawbCircles001
 * @tc.desc: test DrawbCircles.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, DrawbCircles001, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    Testing::MockCanvas canvas;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetHasExtensionMenu(true);
    DrawingContext drawingContext { canvas, 100, 100 };
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Translate(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Rotate(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(4).WillRepeatedly(Return());
    selectOverlayModifier.DrawbCircles(drawingContext);
}

/**
 * @tc.name: DrawbCircles002
 * @tc.desc: test DrawbCircles.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, DrawbCircles002, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    Testing::MockCanvas canvas;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetHasExtensionMenu(true);
    DrawingContext drawingContext { canvas, 100, 100 };
    selectOverlayModifier.SetIsReverse(false);
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Translate(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Rotate(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(4).WillRepeatedly(Return());
    selectOverlayModifier.DrawbCircles(drawingContext);
}

/**
 * @tc.name: DrawbCircles003
 * @tc.desc: test DrawbCircles.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, DrawbCircles003, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    Testing::MockCanvas canvas;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetHasExtensionMenu(true);
    DrawingContext drawingContext { canvas, 100, 100 };
    selectOverlayModifier.circleOffset_.resize(3);
    selectOverlayModifier.SetIsReverse(false);
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(0);
    selectOverlayModifier.DrawbCircles(drawingContext);
}

/**
 * @tc.name: DrawbBackArrow001
 * @tc.desc: test DrawbBackArrow.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, DrawbBackArrow001, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    Testing::MockCanvas canvas;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetHasExtensionMenu(true);
    DrawingContext drawingContext { canvas, 100, 100 };
    selectOverlayModifier.circleOffset_.resize(3);
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Rotate(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).Times(0);
    selectOverlayModifier.DrawbBackArrow(drawingContext);
}

/**
 * @tc.name: DrawbBackArrow002
 * @tc.desc: test DrawbBackArrow.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, DrawbBackArrow002, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    Testing::MockCanvas canvas;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetHasExtensionMenu(true);
    DrawingContext drawingContext { canvas, 100, 100 };
    selectOverlayModifier.lineEndOffset_.resize(2);
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Rotate(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).Times(0);
    selectOverlayModifier.DrawbBackArrow(drawingContext);
}

/**
 * @tc.name: DrawbBackArrow003
 * @tc.desc: test DrawbBackArrow.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, DrawbBackArrow003, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    Testing::MockCanvas canvas;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetHasExtensionMenu(true);
    DrawingContext drawingContext { canvas, 100, 100 };
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Rotate(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).Times(1).WillRepeatedly(Return());
    selectOverlayModifier.DrawbBackArrow(drawingContext);
}

/**
 * @tc.name: onDraw001
 * @tc.desc: test onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, onDraw001, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    Testing::MockCanvas canvas;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetHasExtensionMenu(true);
    DrawingContext drawingContext { canvas, 100, 100 };
    EXPECT_CALL(canvas, Save()).Times(0);
    selectOverlayModifier.onDraw(drawingContext);
}

/**
 * @tc.name: onDraw002
 * @tc.desc: test onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, onDraw002, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    Testing::MockCanvas canvas;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetHasExtensionMenu(true);
    DrawingContext drawingContext { canvas, 100, 100 };
    selectOverlayModifier.SetIsNewAvoid(true);
    EXPECT_CALL(canvas, Restore()).Times(0);
    selectOverlayModifier.onDraw(drawingContext);
}

/**
 * @tc.name: onDraw003
 * @tc.desc: test onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, onDraw003, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    Testing::MockCanvas canvas;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetHasExtensionMenu(true);
    DrawingContext drawingContext { canvas, 100, 100 };
    selectOverlayModifier.SetFirstHandleIsShow(true);
    EXPECT_CALL(canvas, Restore()).Times(0);
    selectOverlayModifier.onDraw(drawingContext);
}

/**
 * @tc.name: onDraw004
 * @tc.desc: test onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, onDraw004, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    Testing::MockCanvas canvas;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetHasExtensionMenu(true);
    DrawingContext drawingContext { canvas, 100, 100 };
    selectOverlayModifier.SetSecondHandleIsShow(true);
    EXPECT_CALL(canvas, Restore()).Times(0);
    selectOverlayModifier.onDraw(drawingContext);
}

/**
 * @tc.name: BackArrowTransitionAnimation001
 * @tc.desc: test BackArrowTransitionAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, BackArrowTransitionAnimation001, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.BackArrowTransitionAnimation(true);
    EXPECT_EQ(selectOverlayModifier.circleOffset_[1]->Get().GetX(), 0);
    EXPECT_EQ(selectOverlayModifier.circleOffset_[1]->Get().GetY(), 0);
}

/**
 * @tc.name: BackArrowTransitionChange001
 * @tc.desc: test BackArrowTransitionChange.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, BackArrowTransitionChange001, TestSize.Level1)
{
    OffsetF menuOptionOffset(5, 5);
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetIsReverse(true);
    selectOverlayModifier.BackArrowTransitionChange(menuOptionOffset, 2);
    EXPECT_EQ(selectOverlayModifier.circleOffset_[2]->Get().GetX(), 5);
    EXPECT_EQ(selectOverlayModifier.circleOffset_[2]->Get().GetY(), 5);
}

/**
 * @tc.name: BackArrowTransitionChange002
 * @tc.desc: test BackArrowTransitionChange.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, BackArrowTransitionChange002, TestSize.Level1)
{
    OffsetF menuOptionOffset(5, 5);
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetIsReverse(true);
    selectOverlayModifier.circleOffset_.resize(1);
    selectOverlayModifier.BackArrowTransitionChange(menuOptionOffset, 2);
    EXPECT_EQ(selectOverlayModifier.lineEndOffset_[0]->Get().GetX(), 0);
    EXPECT_EQ(selectOverlayModifier.lineEndOffset_[0]->Get().GetY(), 0);
}

/**
 * @tc.name: BackArrowTransitionChange003
 * @tc.desc: test BackArrowTransitionChange.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, BackArrowTransitionChange003, TestSize.Level1)
{
    OffsetF menuOptionOffset(5, 5);
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetIsReverse(true);
    selectOverlayModifier.lineEndOffset_.resize(4);
    selectOverlayModifier.BackArrowTransitionChange(menuOptionOffset, 6);
    EXPECT_EQ(selectOverlayModifier.lineEndOffset_[0]->Get().GetX(), 0);
    EXPECT_EQ(selectOverlayModifier.lineEndOffset_[0]->Get().GetY(), 0);
}

/**
 * @tc.name: LineEndOffsetWithAnimation001
 * @tc.desc: test LineEndOffsetWithAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, LineEndOffsetWithAnimation001, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.LineEndOffsetWithAnimation(true, true);
    EXPECT_EQ(selectOverlayModifier.rotationAngle_->Get(), 0);
}

/**
 * @tc.name: ChangeCircle001
 * @tc.desc: test ChangeCircle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, ChangeCircle001, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.circleOffset_.resize(3);
    selectOverlayModifier.rotationAngle_->Set(1);
    selectOverlayModifier.ChangeCircle();
    EXPECT_EQ(selectOverlayModifier.rotationAngle_->Get(), 1);
}

/**
 * @tc.name: ChangeCircle002
 * @tc.desc: test ChangeCircle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, ChangeCircle002, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.lineEndOffset_.resize(2);
    selectOverlayModifier.rotationAngle_->Set(1);
    selectOverlayModifier.ChangeCircle();
    EXPECT_EQ(selectOverlayModifier.rotationAngle_->Get(), 1);
}

/**
 * @tc.name: ChangeCircle003
 * @tc.desc: test ChangeCircle.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, ChangeCircle003, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetIsReverse(true);
    selectOverlayModifier.rotationAngle_->Set(1);
    selectOverlayModifier.ChangeCircle();
    EXPECT_EQ(selectOverlayModifier.rotationAngle_->Get(), 0);
}

/**
 * @tc.name: SetLineEndOffset001
 * @tc.desc: test SetLineEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, SetLineEndOffset001, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetIsReverse(true);
    selectOverlayModifier.lineEndOffset_.resize(2);
    selectOverlayModifier.rotationAngle_->Set(1);
    selectOverlayModifier.SetLineEndOffset(true, true);
    EXPECT_EQ(selectOverlayModifier.rotationAngle_->Get(), 1);
}

/**
 * @tc.name: SetDefaultCircleAndLineEndOffset001
 * @tc.desc: test SetDefaultCircleAndLineEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayContentModifierTestNg, SetDefaultCircleAndLineEndOffset001, TestSize.Level1)
{
    OffsetF menuOptionOffset;
    SelectOverlayModifier selectOverlayModifier(menuOptionOffset, true);
    selectOverlayModifier.SetIsReverse(true);
    selectOverlayModifier.circleOffset_.clear();
    selectOverlayModifier.lineEndOffset_.clear();
    selectOverlayModifier.rotationAngle_->Set(1);
    selectOverlayModifier.SetDefaultCircleAndLineEndOffset();
    EXPECT_FALSE(selectOverlayModifier.circleOffset_.empty());
}
} // namespace OHOS::Ace::NG
