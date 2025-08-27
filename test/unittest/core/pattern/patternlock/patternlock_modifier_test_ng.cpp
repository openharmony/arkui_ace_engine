/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "patternlock_test_ng.h"

namespace OHOS::Ace::NG {
namespace {} // namespace
constexpr Dimension DEFAULT_CIRCLE_RADIUS = 6.0_vp;
constexpr Dimension DEFAULT_ACTIVE_CIRCLE_RADIUS = 7.0_vp;
constexpr Dimension DEFAULT_BACKGROUND_CIRCLE_RADIUS = 11.0_vp;
class PatternLockModifierTestNg : public PatternLockTestNg {
public:
};

/**
 * @tc.name: PatternLockModifierTest001
 * @tc.desc: Test PatternLockModifier onDraw function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest001, TestSize.Level1)
{
    PatternLockModifier patternlockModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100.0f, 100.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(9);
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    patternlockModifier.onDraw(context);
}

/**
 * @tc.name: PatternLockModifierTest002
 * @tc.desc: Test GetCircleCenterByXY function can get correct offset.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest002, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    modifier->SetSideLength(36.0);
    int32_t x = 1;
    int32_t y = 1;
    auto cellCenter = modifier->GetCircleCenterByXY(OffsetF(1.0, 1.0), x, y);
    EXPECT_EQ(cellCenter.GetX(), 7.0);
    EXPECT_EQ(cellCenter.GetY(), 7.0);
}

/**
 * @tc.name: PatternLockModifierTest003
 * @tc.desc: Test PaintLockLine function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest003, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    OffsetF offset;
    /**
     * @tc.case: case1. PatternLock's choosePoint count = 0.
     */
    std::vector<PatternLockCell> vecCell;
    auto patternlockModifier1 = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    patternlockModifier1->SetChoosePoint(vecCell);
    EXPECT_CALL(canvas, Save()).Times(0);
    EXPECT_CALL(canvas, Restore()).Times(0);
    patternlockModifier1->PaintLockLine(canvas, offset);
    /**
     * @tc.case: case2. pathStrokeWidth_ <= 0.
     */
    std::vector<PatternLockCell> vecCell2 = { PatternLockCell(0, 1), PatternLockCell(0, 2) };
    auto patternlockModifier2 = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    patternlockModifier2->SetChoosePoint(vecCell2);
    patternlockModifier2->SetPathStrokeWidth(0.0);
    EXPECT_CALL(canvas, Save()).Times(0);
    EXPECT_CALL(canvas, Restore()).Times(0);
    patternlockModifier2->PaintLockLine(canvas, offset);
    /**
     * @tc.case: case3. isMoveEventValid_ is flase.
     */
    std::vector<PatternLockCell> vecCell3 = { PatternLockCell(0, 1), PatternLockCell(0, 2), PatternLockCell(1, 2) };
    auto patternlockModifier3 = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    patternlockModifier3->SetChoosePoint(vecCell3);
    patternlockModifier3->SetPathStrokeWidth(Dimension(10.0).ConvertToPx());
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(1);
    EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, Save()).Times(1);
    EXPECT_CALL(canvas, Restore()).Times(1);
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(1);
    patternlockModifier3->PaintLockLine(canvas, offset);
    /**
     * @tc.case: case4. isMoveEventValid_ is true.
     */
    std::vector<PatternLockCell> vecCell4 = { PatternLockCell(0, 1), PatternLockCell(0, 2), PatternLockCell(1, 2),
        PatternLockCell(2, 2) };
    auto patternlockModifier4 = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    patternlockModifier4->SetChoosePoint(vecCell4);
    patternlockModifier4->SetPathStrokeWidth(Dimension(10.0).ConvertToPx());
    patternlockModifier4->SetIsMoveEventValid(true);
    patternlockModifier4->sideLength_->Set(SIDE_LENGTH.Value());
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(1);
    EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, Save()).Times(1);
    EXPECT_CALL(canvas, Restore()).Times(1);
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(1);
    patternlockModifier4->PaintLockLine(canvas, offset);
}

/**
 * @tc.name: PatternLockModifierTest004
 * @tc.desc: Test PaintLockCircle function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest004, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    OffsetF offset;
    std::vector<PatternLockCell> vecCell = { PatternLockCell(0, 0), PatternLockCell(0, 2), PatternLockCell(1, 2) };
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    patternlockModifier->SetChoosePoint(vecCell);
    patternlockModifier->SetSideLength(SIDE_LENGH);
    /**
     * @tc.case: case1. Current Point (x, y) is not checked.
     */
    patternlockModifier->SetCircleRadius(POINT_NOT_CHECK_FLOAT);
    patternlockModifier->SetActiveCircleRadius(POINT_NOT_CHECK_FLOAT);
    EXPECT_FALSE(patternlockModifier->CheckChoosePoint(1, 4));
    EXPECT_CALL(canvas, AttachBrush(_)).Times(1).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(canvas, DetachBrush()).Times(1).WillRepeatedly(ReturnRef(canvas));
    patternlockModifier->PaintLockCircle(canvas, offset, 1, 4);
    /**
     * @tc.case: case2. Current Point (x, y) is checked, isMoveEventValid_ is false, isHover_is false, hover index is
     * current Point index and the selected Point is not the last Point.
     */
    patternlockModifier->SetCircleRadius(POINT_CHECK_FLOAT);
    patternlockModifier->SetActiveCircleRadius(POINT_CHECK_FLOAT);
    patternlockModifier->SetHoverIndex(GetPointIndex(0, 0));
    EXPECT_FALSE(patternlockModifier->isMoveEventValid_->Get());
    EXPECT_FALSE(patternlockModifier->isHover_->Get());
    EXPECT_EQ(patternlockModifier->hoverIndex_->Get(), GetPointIndex(0, 0));
    EXPECT_TRUE(patternlockModifier->CheckChoosePoint(0, 0));
    EXPECT_CALL(canvas, AttachBrush(_)).Times(2).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(2);
    EXPECT_CALL(canvas, DetachBrush()).Times(2).WillRepeatedly(ReturnRef(canvas));
    patternlockModifier->PaintLockCircle(canvas, offset, 0, 0);
    patternlockModifier->PaintActiveCircle(canvas, offset);
    /**
     * @tc.case: case3. Current Point (x, y) is checked, isMoveEventValid_ is true, isHover_is true, hover index is
     * current Point index and the selected Point is not the last Point.
     */
    patternlockModifier->SetIsMoveEventValid(true);
    patternlockModifier->SetIsHover(true);
    EXPECT_TRUE(patternlockModifier->isMoveEventValid_->Get());
    EXPECT_TRUE(patternlockModifier->isHover_->Get());
    EXPECT_EQ(patternlockModifier->hoverIndex_->Get(), GetPointIndex(0, 0));
    EXPECT_TRUE(patternlockModifier->CheckChoosePoint(0, 0));
    EXPECT_CALL(canvas, AttachBrush(_)).Times(3).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(3);
    EXPECT_CALL(canvas, DetachBrush()).Times(3).WillRepeatedly(ReturnRef(canvas));
    patternlockModifier->PaintLockCircle(canvas, offset, 0, 0);
    patternlockModifier->PaintActiveCircle(canvas, offset);
}

/**
 * @tc.name: PatternLockModifierTest005
 * @tc.desc: Test PaintLockCircle function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest005, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    OffsetF offset;
    std::vector<PatternLockCell> vecCell = { PatternLockCell(0, 0), PatternLockCell(0, 2), PatternLockCell(1, 2) };
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    patternlockModifier->SetChoosePoint(vecCell);
    patternlockModifier->SetSideLength(SIDE_LENGH);
    /**
     * @tc.case: case1. last Point (x, y) is checked, isHover_is false, hover index is not current Point,
     * isMoveEventValid_ is false and challengeResult_ has value.
     */
    std::optional<PatternLockChallengeResult> ngChallengeResult = PatternLockChallengeResult::WRONG;
    ngChallengeResult = PatternLockChallengeResult::CORRECT;
    patternlockModifier->SetChallengeResult(ngChallengeResult);
    EXPECT_FALSE(patternlockModifier->isMoveEventValid_->Get());
    EXPECT_FALSE(patternlockModifier->isHover_->Get());
    EXPECT_NE(patternlockModifier->hoverIndex_->Get(), GetPointIndex(1, 2));
    EXPECT_TRUE(patternlockModifier->challengeResult_.has_value());
    EXPECT_TRUE(patternlockModifier->CheckChoosePointIsLastIndex(1, 2, 1));
    EXPECT_CALL(canvas, AttachBrush(_)).Times(2).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(2);
    EXPECT_CALL(canvas, DetachBrush()).Times(2).WillRepeatedly(ReturnRef(canvas));
    patternlockModifier->PaintLockCircle(canvas, offset, 1, 2);
    patternlockModifier->PaintActiveCircle(canvas, offset);
    /**
     * @tc.case: case2. last Point (x, y) is checked, isHover_is true, hover index is not current Point,
     * isMoveEventValid_ is true and challengeResult_ has value.
     */
    patternlockModifier->SetIsMoveEventValid(true);
    patternlockModifier->SetIsHover(true);
    patternlockModifier->SetCircleRadius(LAST_POINT_CHECK_FLOAT);
    patternlockModifier->SetChallengeResult(ngChallengeResult);
    EXPECT_TRUE(patternlockModifier->isMoveEventValid_->Get());
    EXPECT_TRUE(patternlockModifier->isHover_->Get());
    EXPECT_NE(patternlockModifier->hoverIndex_->Get(), GetPointIndex(1, 2));
    EXPECT_TRUE(patternlockModifier->challengeResult_.has_value());
    EXPECT_TRUE(patternlockModifier->CheckChoosePointIsLastIndex(1, 2, 1));
    EXPECT_CALL(canvas, AttachBrush(_)).Times(2).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(2);
    EXPECT_CALL(canvas, DetachBrush()).Times(2).WillRepeatedly(ReturnRef(canvas));
    patternlockModifier->PaintLockCircle(canvas, offset, 1, 2);
    patternlockModifier->PaintActiveCircle(canvas, offset);
}

/**
 * @tc.name: PatternLockModifierTest006
 * @tc.desc: Test ConnectedCircleAnimate and ConnectedLineAnimate functions.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier and  Set ChoosePoint
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    std::vector<PatternLockCell> vecCell = { PatternLockCell(0, 0) };
    patternlockModifier->SetChoosePoint(vecCell);
    /**
     * @tc.steps: step2. call ConnectedCircleAnimate and ConnectedLineAnimate func
     * @tc.expected:the value of Animatable Properties is updated
     */
    patternlockModifier->SetCircleRadius(CIRCLE_RADIUS.Value());
    patternlockModifier->StartConnectedCircleAnimate(1, 1);
    patternlockModifier->StartConnectedLineAnimate(1, 1);
    EXPECT_EQ(patternlockModifier->GetBackgroundCircleRadius(0), 0);
    EXPECT_EQ(patternlockModifier->GetActiveCircleRadius(0), 0);
    EXPECT_EQ(patternlockModifier->GetLightRingCircleRadius(0), 0);
    EXPECT_EQ(patternlockModifier->GetLightRingAlphaF(0), 0);
    OffsetF pointEnd = patternlockModifier->GetCircleCenterByXY(patternlockModifier->offset_->Get(), 1, 1);
    EXPECT_TRUE(patternlockModifier->GetConnectedLineTailPoint() == pointEnd);
    /**
     * @tc.steps: step3. call SetConnectedLineTailPoint func
     * @tc.expected:the value of connectedLineTailPoint_ is updated
     */
    patternlockModifier->connectedLineTailPoint_->Set(OffsetF());
    patternlockModifier->isMoveEventValid_->Set(true);
    patternlockModifier->isTouchDown_ = true;
    patternlockModifier->SetConnectedLineTailPoint(1, 1);
    pointEnd = patternlockModifier->GetCircleCenterByXY(patternlockModifier->offset_->Get(), 1, 1);
    EXPECT_TRUE(patternlockModifier->GetConnectedLineTailPoint() == pointEnd);

    /**
     * @tc.steps: step4. call SetConnectedLineTailPoint func when choosePoint_ is empty
     * @tc.expected:the value of connectedLineTailPoint_ is not updated
     */
    pointEnd = OffsetF();
    patternlockModifier->choosePoint_.clear();
    patternlockModifier->connectedLineTailPoint_->Set(pointEnd);
    patternlockModifier->SetConnectedLineTailPoint(1, 1);
    EXPECT_TRUE(patternlockModifier->GetConnectedLineTailPoint() == pointEnd);
}

/**
 * @tc.name: PatternLockModifierTest007
 * @tc.desc: Test StartCanceledAnimate function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier and  Set ChoosePoint
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    std::vector<PatternLockCell> vecCell = { PatternLockCell(0, 0) };
    patternlockModifier->SetChoosePoint(vecCell);
    /**
     * @tc.steps: step2. call StartCanceledAnimate func
     * @tc.expected:the value of canceledLineTailPoint_ is updated
     */
    patternlockModifier->StartCanceledAnimate();
    OffsetF pointEnd = patternlockModifier->GetCircleCenterByXY(patternlockModifier->offset_->Get(), 0, 0);
    EXPECT_TRUE(patternlockModifier->GetCanceledLineTailPoint() == pointEnd);
}

/**
 * @tc.name: PatternLockModifierTest008
 * @tc.desc: Test PaintLightRing function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    /**
     * @tc.steps: step2. call PaintLightRing func
     * @tc.expected:Related function is called.
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(1);
    patternlockModifier->PaintLightRing(canvas, 0, 0, CIRCLE_RADIUS.Value(), 1);
}

/**
 * @tc.name: PatternLockModifierTest009
 * @tc.desc: Test PaintLockLine function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    std::vector<PatternLockCell> vecCell = { PatternLockCell(0, 0) };
    patternlockModifier->SetChoosePoint(vecCell);
    patternlockModifier->sideLength_->Set(SIDE_LENGTH.Value());
    patternlockModifier->needCanceledLine_ = true;
    patternlockModifier->pathStrokeWidth_->Set(PATH_STROKE_WIDTH.Value());
    /**
     * @tc.steps: step2. Call PaintLockLine func
     * @tc.expected:Related function is called.
     */

    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(1);
    EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, Save()).Times(1);
    EXPECT_CALL(canvas, Restore()).Times(1);
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(1);
    patternlockModifier->PaintLockLine(canvas, patternlockModifier->offset_->Get());

    /**
     * @tc.steps: step3. Add one choosePoint then call PaintLockLine func
     * @tc.expected:Related function is called.
     */
    patternlockModifier->choosePoint_.emplace_back(PatternLockCell(1, 1));
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(1);
    EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, Save()).Times(1);
    EXPECT_CALL(canvas, Restore()).Times(1);
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(1);
    patternlockModifier->PaintLockLine(canvas, patternlockModifier->offset_->Get());
}

/**
 * @tc.name: PatternLockModifierTest010
 * @tc.desc: Test SetHoverColor, SetSelectColor and SetChallengeResult function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    /**
     * @tc.steps: step2. call SetHoverColor func
     */
    patternlockModifier->SetHoverColor(HOVER_COLOR);
    EXPECT_EQ(patternlockModifier->hoverColor_->Get(), HOVER_COLOR);
    patternlockModifier->SetHoverColor(HOVER_COLOR);
    EXPECT_EQ(patternlockModifier->hoverColor_->Get(), HOVER_COLOR);
    /**
     * @tc.steps: step3. call SetSelectColor func
     */
    patternlockModifier->SetSelectColor(SELECTED_COLOR);
    EXPECT_EQ(patternlockModifier->selectedColor_->Get(), SELECTED_COLOR);
    patternlockModifier->SetSelectColor(SELECTED_COLOR);
    EXPECT_EQ(patternlockModifier->selectedColor_->Get(), SELECTED_COLOR);
    /**
     * @tc.steps: step4. call SetChallengeResult func
     */
    std::optional<PatternLockChallengeResult> ngChallengeResult = PatternLockChallengeResult::WRONG;
    patternlockModifier->SetChallengeResult(ngChallengeResult);
    EXPECT_TRUE(patternlockModifier->challengeResult_.has_value());
    patternlockModifier->SetChallengeResult(ngChallengeResult);
    EXPECT_TRUE(patternlockModifier->challengeResult_.has_value());
    ngChallengeResult.reset();
    patternlockModifier->SetChallengeResult(ngChallengeResult);
    EXPECT_FALSE(patternlockModifier->challengeResult_.has_value());
}

/**
 * @tc.name: PatternLockModifierTest011
 * @tc.desc: Test SetContentOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    /**
     * @tc.steps: step2. call SetContentOffset func
     * @tc.expected:the value of offset_ is updated
     */
    patternlockModifier->SetContentOffset(OffsetF(CONTENT_OFFSET_FLOAT, CONTENT_OFFSET_FLOAT));
    EXPECT_EQ(patternlockModifier->offset_->Get(), OffsetF(CONTENT_OFFSET_FLOAT, CONTENT_OFFSET_FLOAT));
    /**
     * @tc.steps: step3. set ChoosePoint_ of patternlockModifier
     * @tc.expected:the ChoosePoint_ is not empty
     */
    std::vector<PatternLockCell> vecCell = { PatternLockCell(1, 1) };
    patternlockModifier->SetChoosePoint(vecCell);
    EXPECT_FALSE(patternlockModifier->choosePoint_.empty());
    /**
     * @tc.steps: step4. call SetContentOffset func
     * @tc.expected:connectedLineTailPoint_ and canceledLineTailPoint_ are updated
     */
    patternlockModifier->SetSideLength(DEFAULT_SIDE_LENGTH);
    patternlockModifier->SetContentOffset(OffsetF(0.0f, 0.0f));
    auto firstPointOffset = OffsetF(DEFAULT_SIDE_LENGTH / PATTERN_LOCK_COL_COUNT / RADIUS_TO_DIAMETER,
        DEFAULT_SIDE_LENGTH / PATTERN_LOCK_COL_COUNT / RADIUS_TO_DIAMETER);
    EXPECT_EQ(patternlockModifier->connectedLineTailPoint_->Get(), firstPointOffset);
    EXPECT_EQ(patternlockModifier->canceledLineTailPoint_->Get(), firstPointOffset);
}

/**
 * @tc.name: PatternLockModifierTest012
 * @tc.desc: Test ConnectedCircleAnimate functions when disableWaveEffect.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier and  Set ChoosePoint
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    std::vector<PatternLockCell> vecCell = { PatternLockCell(0, 0) };
    patternlockModifier->SetChoosePoint(vecCell);
    /**
     * @tc.steps: step2. set wave, call ConnectedCircleAnimate and ConnectedLineAnimate func
     * @tc.expected:the value of Animatable Properties is updated
     */
    patternlockModifier->SetCircleRadius(CIRCLE_RADIUS.Value());
    patternlockModifier->SetEnableWaveEffect(false);
    patternlockModifier->StartConnectedCircleAnimate(1, 1);
    patternlockModifier->StartConnectedLineAnimate(1, 1);
    EXPECT_EQ(patternlockModifier->GetBackgroundCircleRadius(0), 0);
    EXPECT_EQ(patternlockModifier->GetActiveCircleRadius(0), 0);
    EXPECT_EQ(patternlockModifier->GetLightRingCircleRadius(0), 0);
    EXPECT_EQ(patternlockModifier->GetLightRingAlphaF(0), 0);
    OffsetF pointEnd = patternlockModifier->GetCircleCenterByXY(patternlockModifier->offset_->Get(), 1, 1);
    EXPECT_TRUE(patternlockModifier->GetConnectedLineTailPoint() == pointEnd);
}

/**
 * @tc.name: PatternLockModifierTest013
 * @tc.desc: Test the function of SetCircleRadius.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier and Set SideLength.
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    patternlockModifier->SetBackgroundCircleRadiusScale(
        DEFAULT_BACKGROUND_CIRCLE_RADIUS.Value() / DEFAULT_CIRCLE_RADIUS.Value());
    patternlockModifier->SetSideLength(275);
    /**
     * @tc.steps: step2. set CircleRadius 24\25\100
     * @tc.expected:the max value of ActiveCircleRadius is SideLength/11
     */
    patternlockModifier->SetCircleRadius(24);
    patternlockModifier->SetActiveCircleRadius(0);
    EXPECT_EQ(patternlockModifier->GetActiveCircleRadius(0), 24);

    patternlockModifier->SetCircleRadius(25);
    patternlockModifier->SetActiveCircleRadius(0);
    EXPECT_EQ(patternlockModifier->GetActiveCircleRadius(0), 25);

    patternlockModifier->SetCircleRadius(100);
    patternlockModifier->SetActiveCircleRadius(0);
    EXPECT_EQ(patternlockModifier->GetActiveCircleRadius(0), 25);
}

/**
 * @tc.name: PatternLockModifierTest014
 * @tc.desc: Test the function of SetCircleRadius.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockModifierTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier and Set SideLength.
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>(nullptr);
    std::vector<PatternLockCell> vecCell = { PatternLockCell(1, 1) };
    patternlockModifier->SetChoosePoint(vecCell);
    patternlockModifier->SetBackgroundCircleRadiusScale(
        DEFAULT_BACKGROUND_CIRCLE_RADIUS.Value() / DEFAULT_CIRCLE_RADIUS.Value());
    patternlockModifier->SetActiveCircleRadiusScale(
        DEFAULT_ACTIVE_CIRCLE_RADIUS.Value() / DEFAULT_CIRCLE_RADIUS.Value());
    patternlockModifier->SetSideLength(275);
    /**
     * @tc.steps: step2. set CircleRadius 24\25\100
     * @tc.expected:the max value of ActiveCircleRadius is SideLength/11
     */
    patternlockModifier->SetCircleRadius(24);
    EXPECT_EQ(patternlockModifier->GetActiveCircleRadius(0), 28);
}

}
}