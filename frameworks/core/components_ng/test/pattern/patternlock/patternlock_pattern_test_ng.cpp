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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_method.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"
#include "core/components_ng/pattern/patternlock/patternlock_pattern.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const Dimension SIDE_LENGTH = 300.0_vp;
const Dimension CIRCLE_RADIUS = 14.0_vp;
const Color REGULAR_COLOR = Color::BLACK;
const Color SELECTED_COLOR = Color::BLACK;
const Color ACTIVE_COLOR = Color::BLACK;
const Color PATH_COLOR = Color::BLUE;
const Dimension PATH_STROKE_WIDTH = 34.0_vp;
} // namespace

struct TestProperty {
    std::optional<Dimension> sideLength = std::nullopt;
    std::optional<Dimension> circleRadius = std::nullopt;
    std::optional<Color> regularColor = std::nullopt;
    std::optional<Color> selectedColor = std::nullopt;
    std::optional<Color> activeColor = std::nullopt;
    std::optional<Color> pathColor = std::nullopt;
    std::optional<Dimension> strokeWidth = std::nullopt;
    std::optional<bool> autoReset = std::nullopt;
};

class PatternLockPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}
};

void PatternLockPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void PatternLockPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: PatternLockPaintPropertyTest001
 * @tc.desc: Set PatternLock value into PatternLockPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    /**
     * @tc.steps: step2. Init PatternLock parameters and set them to PatternLock property
     */
    TestProperty testProperty;
    testProperty.sideLength = std::make_optional(SIDE_LENGTH);
    testProperty.circleRadius = std::make_optional(CIRCLE_RADIUS);
    testProperty.regularColor = std::make_optional(REGULAR_COLOR);
    testProperty.selectedColor = std::make_optional(SELECTED_COLOR);
    testProperty.activeColor = std::make_optional(ACTIVE_COLOR);
    testProperty.pathColor = std::make_optional(PATH_COLOR);
    testProperty.strokeWidth = std::make_optional(PATH_STROKE_WIDTH);
    testProperty.autoReset = std::make_optional(true);
    EXPECT_TRUE(testProperty.sideLength.has_value());
    patternLockModelNG.SetSideLength(testProperty.sideLength.value());
    patternLockModelNG.SetCircleRadius(testProperty.circleRadius.value());
    patternLockModelNG.SetRegularColor(testProperty.regularColor.value());
    patternLockModelNG.SetSelectedColor(testProperty.selectedColor.value());
    patternLockModelNG.SetActiveColor(testProperty.activeColor.value());
    patternLockModelNG.SetPathColor(testProperty.pathColor.value());
    patternLockModelNG.SetStrokeWidth(testProperty.strokeWidth.value());
    patternLockModelNG.SetAutoReset(testProperty.autoReset.value());

    /**
     * @tc.steps: step3. Get layout property and get PatternLock property
     * @tc.expected: step3. Check the PatternLock property value
     */
    auto patternLockPaintProperty = frameNode->GetPaintProperty<PatternLockPaintProperty>();
    EXPECT_FALSE(patternLockPaintProperty == nullptr);
    EXPECT_EQ(patternLockPaintProperty->GetSideLengthValue(), SIDE_LENGTH);
    EXPECT_EQ(patternLockPaintProperty->GetCircleRadiusValue(), CIRCLE_RADIUS);
    EXPECT_EQ(patternLockPaintProperty->GetRegularColorValue(), REGULAR_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetSelectedColorValue(), SELECTED_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetActiveColorValue(), ACTIVE_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetPathColorValue(), PATH_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetPathStrokeWidthValue(), PATH_STROKE_WIDTH);
    EXPECT_EQ(patternLockPaintProperty->GetAutoResetValue(), true);
}

/**
 * @tc.name: PatternLockEventTest002
 * @tc.desc: Test PatternLock onComplete event.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();

    /**
     * @tc.steps: step2. Init complete result data structure and onComplete function
     */
    std::vector<int> chooseCellVec;
    std::vector<int> afterComplete;
    chooseCellVec.push_back(1);
    chooseCellVec.push_back(2);
    chooseCellVec.push_back(3);
    chooseCellVec.push_back(4);
    chooseCellVec.push_back(5);
    chooseCellVec.push_back(6);
    auto patternCompleteEvent = V2::PatternCompleteEvent(chooseCellVec);
    auto onComplete = [&afterComplete](const BaseEventInfo* completeResult) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<V2::PatternCompleteEvent>(completeResult);
        afterComplete = eventInfo->GetInput();
    };
    patternLockModelNG.SetPatternComplete(onComplete);

    /**
     * @tc.steps: step3. Get event hub and call UpdateCompleteEvent function
     * @tc.expected: step3. Check the event result value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto eventHub = frameNode->GetEventHub<NG::PatternLockEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    eventHub->UpdateCompleteEvent(&patternCompleteEvent);
    EXPECT_FALSE(afterComplete.empty());
    EXPECT_EQ(afterComplete.back(), 6);
    afterComplete.pop_back();
    EXPECT_EQ(afterComplete.back(), 5);
    afterComplete.pop_back();
    EXPECT_EQ(afterComplete.back(), 4);
    afterComplete.pop_back();
    EXPECT_EQ(afterComplete.back(), 3);
    afterComplete.pop_back();
    EXPECT_EQ(afterComplete.back(), 2);
    afterComplete.pop_back();
    EXPECT_EQ(afterComplete.back(), 1);
}

/**
 * @tc.name: PatternLockPatternTest003
 * @tc.desc: Test PatternLock pattern method HandleReset.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();

    /**
     * @tc.steps: step2. Get PatternLock pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call HandleReset
     * @tc.expected: step3. Check the PatternLock pattern variable
     */
    pattern->isMoveEventValid_ = true;
    pattern->choosePoint_.push_back(PatternLockCell(1, 2));
    pattern->cellCenter_ = OffsetF(1.0, 1.0);
    pattern->HandleReset();
    EXPECT_EQ(pattern->isMoveEventValid_, false);
    EXPECT_EQ(pattern->choosePoint_.empty(), true);
    EXPECT_EQ(pattern->cellCenter_, OffsetF(0, 0));

    /**
     * @tc.steps: step4. PatternLock Init PatternLockController.
     */
    pattern->InitPatternLockController();
    EXPECT_FALSE(pattern->patternLockController_->resetImpl_ == nullptr);
    pattern->patternLockController_->resetImpl_();
    EXPECT_EQ(pattern->isMoveEventValid_, false);
    EXPECT_EQ(pattern->choosePoint_.empty(), true);
    EXPECT_EQ(pattern->cellCenter_, OffsetF(0, 0));
}

/**
 * @tc.name: PatternLockPatternTest004
 * @tc.desc: Test PatternLock pattern method CheckAutoReset.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();
    patternLockModelNG.SetAutoReset(true);

    /**
     * @tc.steps: step2. Get PatternLock pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call CheckAutoReset
     * @tc.expected: step3. Check the return value of PatternLock pattern method CheckAutoReset
     */
    bool result1 = pattern->CheckAutoReset();
    EXPECT_EQ(pattern->autoReset_, true);
    EXPECT_EQ(result1, true);
    auto patternLockPaintProperty = frameNode->GetPaintProperty<PatternLockPaintProperty>();
    EXPECT_FALSE(patternLockPaintProperty == nullptr);
    patternLockPaintProperty->Reset();
    bool result2 = pattern->CheckAutoReset();
    EXPECT_EQ(result2, true);
    pattern->autoReset_ = false;
    pattern->choosePoint_ = { PatternLockCell(1, 2) };
    pattern->isMoveEventValid_ = false;
    bool result3 = pattern->CheckAutoReset();
    EXPECT_EQ(result3, false);
}

/**
 * @tc.name: PatternLockPatternTest005
 * @tc.desc: Test PatternLock pattern method AddPassPoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();
    /**
     * @tc.steps: step2. Get PatternLock pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    EXPECT_FALSE(pattern == nullptr);
    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call AddPassPoint
     * @tc.expected: step3. Check the return value of PatternLock pattern method AddPassPoint
     */
    /**
     * @tc.case: case1: choosePoint_ vec is empty.
     */
    pattern->AddPassPoint(1, 2);
    EXPECT_TRUE(pattern->choosePoint_.empty());
    /**
     * @tc.case: case2: choosePoint_ vec is not empty.
     */
    pattern->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern->AddPassPoint(1, 2);
    EXPECT_EQ(pattern->choosePoint_.back().GetRow(), 1);
    EXPECT_EQ(pattern->choosePoint_.back().GetColumn(), 1);
    /**
     * @tc.case: case3: lastPoint(1, 2), add Point(2, 2), no passPoint.
     */
    pattern->choosePoint_.clear();
    pattern->choosePoint_.push_back(PatternLockCell(1, 2));
    pattern->AddPassPoint(2, 2);
    EXPECT_EQ(pattern->choosePoint_.back().GetRow(), 2);
    EXPECT_EQ(pattern->choosePoint_.back().GetColumn(), 1);
    /**
     * @tc.case: case4: lastPoint(0, 2), add Point(2, 2), passPoint(1, 2)
     */
    pattern->choosePoint_.clear();
    pattern->choosePoint_.push_back(PatternLockCell(0, 2));
    pattern->AddPassPoint(2, 2);
    EXPECT_EQ(pattern->choosePoint_.back().GetColumn(), 1);
    EXPECT_EQ(pattern->choosePoint_.back().GetRow(), 2);
    EXPECT_EQ(pattern->choosePoint_.size(), 2);
    /**
     * @tc.case: case5: lastPoint(2, 2), add Point(0, 0), passPoint(1, 1)
     */
    pattern->choosePoint_.clear();
    pattern->choosePoint_.push_back(PatternLockCell(2, 2));
    pattern->AddPassPoint(0, 0);
    EXPECT_EQ(pattern->choosePoint_.back().GetColumn(), 1);
    EXPECT_EQ(pattern->choosePoint_.back().GetRow(), 1);
    EXPECT_EQ(pattern->choosePoint_.size(), 2);
}

/**
 * @tc.name: PatternLockPatternTest006
 * @tc.desc: Test PatternLock pattern method CheckChoosePoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();

    /**
     * @tc.steps: step2. Get PatternLock pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call CheckChoosePoint
     * @tc.expected: step3. Check the return value of PatternLock pattern method CheckChoosePoint
     */
    pattern->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern->choosePoint_.push_back(PatternLockCell(1, 2));
    auto result1 = pattern->CheckChoosePoint(1, 2);
    EXPECT_EQ(result1, true);
    auto result2 = pattern->CheckChoosePoint(2, 2);
    EXPECT_EQ(result2, false);
}

/**
 * @tc.name: PatternLockPatternTest007
 * @tc.desc: Test PatternLock pattern method AddChoosePoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();

    /**
     * @tc.steps: step2. Get PatternLock pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call AddChoosePoint
     * @tc.expected: step3. Check the return value of PatternLock pattern method AddChoosePoint
     */
    float offsetX = 75.0f;
    float offsetY = 75.0f;
    OffsetF offset(offsetX, offsetY);
    bool result1 = pattern->AddChoosePoint(offset, 1, 1);
    EXPECT_EQ(result1, false);
    bool result2 = pattern->AddChoosePoint(offset, 1, 1);
    EXPECT_EQ(result2, false);
    auto patternLockPaintProperty = frameNode->GetPaintProperty<PatternLockPaintProperty>();
    EXPECT_FALSE(patternLockPaintProperty == nullptr);
    patternLockPaintProperty->UpdateSideLength(SIDE_LENGTH);
    patternLockPaintProperty->UpdateCircleRadius(CIRCLE_RADIUS);
    offsetX = 150.0f;
    offsetY = 150.0f;
    offset.SetX(offsetX);
    offset.SetY(offsetY);
    bool result3 = pattern->AddChoosePoint(offset, 1, 1);
    EXPECT_EQ(result3, false);

    /**
     * @tc.cases: when distance is valid, Point(x, y) will AddChoosePoint.
     */
    patternLockPaintProperty->UpdateSideLength(SIDE_LENGTH);
    patternLockPaintProperty->UpdateCircleRadius(Dimension(200.0));
    bool result4 = pattern->AddChoosePoint(offset, 1, 1);
    EXPECT_EQ(result4, true);
    EXPECT_EQ(pattern->choosePoint_.size(), 1);
    bool result5 = pattern->AddChoosePoint(offset, 1, 1);
    EXPECT_EQ(pattern->choosePoint_.size(), 1);
    EXPECT_EQ(result5, true);
    bool result6 = pattern->AddChoosePoint(offset, 1, 2);
    EXPECT_EQ(pattern->choosePoint_.size(), 2);
    EXPECT_EQ(result6, true);
}

/**
 * @tc.name: PatternLockPatternTest008
 * @tc.desc: Test PatternLock pattern method OnTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();

    /**
     * @tc.steps: step2. Get PatternLock pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call OnTouchUp
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    pattern->autoReset_ = false;
    pattern->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern->isMoveEventValid_ = false;
    pattern->OnTouchUp();
    pattern->isMoveEventValid_ = true;
    pattern->OnTouchUp();
    EXPECT_EQ(pattern->isMoveEventValid_, false);
}

/**
 * @tc.name: PatternLockPatternTest009
 * @tc.desc: Test PatternLock pattern method OnTouchMove.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();

    /**
     * @tc.steps: step2. Get PatternLock pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call OnTouchMove
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    float offsetX = 1.0f;
    float offsetY = 1.0f;
    Offset offset(offsetX, offsetY);
    pattern->isMoveEventValid_ = false;
    TouchLocationInfo locationInfo(0);
    locationInfo.SetTouchType(TouchType::MOVE);
    locationInfo.SetLocalLocation(offset);
    TouchEventInfo touchEventInfo("onTouchMove");
    touchEventInfo.AddTouchLocationInfo(std::move(locationInfo));
    pattern->OnTouchMove(touchEventInfo);
    pattern->isMoveEventValid_ = true;
    pattern->OnTouchMove(touchEventInfo);
    EXPECT_EQ(pattern->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern->cellCenter_.GetY(), offset.GetY());
}

/**
 * @tc.name: PatternLockPatternTest010
 * @tc.desc: Test PatternLock pattern method OnTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();

    /**
     * @tc.steps: step2. Get PatternLock pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call OnTouchDown
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    float offsetX = 1.0f;
    float offsetY = 1.0f;
    Offset offset(offsetX, offsetY);
    pattern->autoReset_ = false;
    pattern->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern->isMoveEventValid_ = false;
    TouchLocationInfo locationInfo(0);
    locationInfo.SetLocalLocation(offset);
    TouchEventInfo touchEventInfo("onTouchDown");
    touchEventInfo.AddTouchLocationInfo(std::move(locationInfo));
    pattern->OnTouchDown(touchEventInfo);
    pattern->isMoveEventValid_ = true;
    pattern->OnTouchDown(touchEventInfo);
    EXPECT_EQ(pattern->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern->cellCenter_.GetY(), offset.GetY());
}

/**
 * @tc.name: PatternLockPatternTest011
 * @tc.desc: Test PatternLock pattern method HandleTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();

    /**
     * @tc.steps: step2. Get PatternLock pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call HandleTouchEvent
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    float offsetX = 1.0f;
    float offsetY = 1.0f;
    Offset offset(offsetX, offsetY);
    TouchLocationInfo locationInfoTouchDown(0);
    locationInfoTouchDown.SetLocalLocation(offset);
    locationInfoTouchDown.SetTouchType(TouchType::DOWN);
    TouchEventInfo touchEventInfoTouchDown("onTouchDown");
    touchEventInfoTouchDown.AddTouchLocationInfo(std::move(locationInfoTouchDown));
    pattern->HandleTouchEvent(touchEventInfoTouchDown);
    EXPECT_EQ(pattern->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern->cellCenter_.GetY(), offset.GetY());
    pattern->cellCenter_.Reset();

    pattern->isMoveEventValid_ = true;
    TouchLocationInfo locationInfoTouchUp(0);
    locationInfoTouchUp.SetLocalLocation(offset);
    locationInfoTouchUp.SetTouchType(TouchType::UP);
    TouchEventInfo touchEventInfoUp("onTouchUp");
    touchEventInfoUp.AddTouchLocationInfo(std::move(locationInfoTouchUp));
    pattern->HandleTouchEvent(touchEventInfoUp);
    EXPECT_EQ(pattern->isMoveEventValid_, false);

    pattern->isMoveEventValid_ = true;
    TouchLocationInfo locationInfoTouchMove(0);
    locationInfoTouchMove.SetLocalLocation(offset);
    locationInfoTouchMove.SetTouchType(TouchType::MOVE);
    TouchEventInfo touchEventInfoTouchMove("onTouchMove");
    touchEventInfoTouchMove.AddTouchLocationInfo(std::move(locationInfoTouchMove));
    pattern->HandleTouchEvent(touchEventInfoTouchMove);
    EXPECT_EQ(pattern->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern->cellCenter_.GetY(), offset.GetY());
    pattern->cellCenter_.Reset();

    TouchLocationInfo locationInfoTouchUnkown(0);
    locationInfoTouchUnkown.SetLocalLocation(offset);
    locationInfoTouchUnkown.SetTouchType(TouchType::UNKNOWN);
    TouchEventInfo touchEventInfoTouchUnkown("onTouchUnkown");
    touchEventInfoTouchUnkown.AddTouchLocationInfo(std::move(locationInfoTouchUnkown));
    pattern->HandleTouchEvent(touchEventInfoTouchUnkown);
}

/**
 * @tc.name: PatternLockPatternTest012
 * @tc.desc: Test PatternLock pattern method InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();

    /**
     * @tc.steps: step2. Get PatternLock pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call InitTouchEvent
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    pattern->InitTouchEvent(gestureHub, pattern->touchDownListener_);
    EXPECT_FALSE(pattern->touchDownListener_ == nullptr);
    auto touchEvent = gestureHub->touchEventActuator_->touchEvents_.back();
    EXPECT_FALSE(touchEvent == nullptr);
    auto info = TouchEventInfo("");
    touchEvent->callback_(info);
    pattern->InitTouchEvent(gestureHub, pattern->touchDownListener_);
    EXPECT_EQ(gestureHub->touchEventActuator_->touchEvents_.back(), touchEvent);
}
} // namespace OHOS::Ace::NG
