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

#include "base/geometry/ng/offset_t.h"
#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/patternlock/patternlock_layout_algorithm.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_method.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"
#include "core/components_ng/pattern/patternlock/patternlock_pattern.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr Dimension SIDE_LENGTH = 300.0_vp;
constexpr Dimension CIRCLE_RADIUS = 14.0_vp;
const Color REGULAR_COLOR = Color::BLACK;
const Color SELECTED_COLOR = Color::BLUE;
const Color ACTIVE_COLOR = Color::RED;
const Color PATH_COLOR = Color::GRAY;
constexpr Dimension PATH_STROKE_WIDTH = 34.0_vp;
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

class PatternLockPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}
};

void PatternLockPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void PatternLockPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: PatternLockPaintPropertyTest001
 * @tc.desc: Set PatternLock value into PatternLockPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    /**
     * @tc.steps: step2. Init PatternLock parameters and set them to PatternLock property
     */
    TestProperty testProperty;
    testProperty.circleRadius = std::make_optional(CIRCLE_RADIUS);
    testProperty.regularColor = std::make_optional(REGULAR_COLOR);
    testProperty.selectedColor = std::make_optional(SELECTED_COLOR);
    testProperty.activeColor = std::make_optional(ACTIVE_COLOR);
    testProperty.pathColor = std::make_optional(PATH_COLOR);
    testProperty.strokeWidth = std::make_optional(PATH_STROKE_WIDTH);
    testProperty.autoReset = std::make_optional(true);
    patternLockModelNG.SetCircleRadius(testProperty.circleRadius.value());
    patternLockModelNG.SetRegularColor(testProperty.regularColor.value());
    patternLockModelNG.SetSelectedColor(testProperty.selectedColor.value());
    patternLockModelNG.SetActiveColor(testProperty.activeColor.value());
    patternLockModelNG.SetPathColor(testProperty.pathColor.value());
    patternLockModelNG.SetStrokeWidth(testProperty.strokeWidth.value());
    patternLockModelNG.SetAutoReset(testProperty.autoReset.value());

    /**
     * @tc.steps: step3. Get paint property and get PatternLock property
     * @tc.expected: step3. Check the PatternLock property value
     */
    auto patternLockPaintProperty = frameNode->GetPaintProperty<PatternLockPaintProperty>();
    ASSERT_NE(patternLockPaintProperty, nullptr);
    EXPECT_EQ(patternLockPaintProperty->GetCircleRadiusValue(), CIRCLE_RADIUS);
    EXPECT_EQ(patternLockPaintProperty->GetRegularColorValue(), REGULAR_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetSelectedColorValue(), SELECTED_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetActiveColorValue(), ACTIVE_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetPathColorValue(), PATH_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetPathStrokeWidthValue(), PATH_STROKE_WIDTH);
    EXPECT_TRUE(patternLockPaintProperty->GetAutoResetValue());
}

/**
 * @tc.name: PatternLockLayoutPropertyTest001
 * @tc.desc: Set PatternLock value into PatternLockLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockLayoutPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    /**
     * @tc.steps: step2. Init PatternLock parameters and set them to PatternLock property
     */
    TestProperty testProperty;
    testProperty.sideLength = std::make_optional(SIDE_LENGTH);
    patternLockModelNG.SetSideLength(testProperty.sideLength.value());

    /**
     * @tc.steps: step3. Get layout property and get PatternLock property
     * @tc.expected: step3. Check the PatternLock property value
     */
    auto patternLockLayoutProperty = frameNode->GetLayoutProperty<PatternLockLayoutProperty>();
    ASSERT_NE(patternLockLayoutProperty, nullptr);
    EXPECT_EQ(patternLockLayoutProperty->GetSideLength(), SIDE_LENGTH);
}

/**
 * @tc.name: PatternLockEventTest001
 * @tc.desc: Test PatternLock onComplete event.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockEventTest001, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::PatternLockEventHub>();
    ASSERT_NE(eventHub, nullptr);
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
 * @tc.name: PatternLockPatternTest001
 * @tc.desc: Test PatternLock pattern method HandleReset.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest001, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    ASSERT_NE(pattern, nullptr);

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
    ASSERT_NE(pattern->patternLockController_->resetImpl_, nullptr);
    pattern->patternLockController_->resetImpl_();
    EXPECT_EQ(pattern->isMoveEventValid_, false);
    EXPECT_EQ(pattern->choosePoint_.empty(), true);
    EXPECT_EQ(pattern->cellCenter_, OffsetF(0, 0));
}

/**
 * @tc.name: PatternLockPatternTest002
 * @tc.desc: Test PatternLock pattern method CheckAutoReset.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest002, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call CheckAutoReset
     * @tc.expected: step3. Check the return value of PatternLock pattern method CheckAutoReset
     */
    bool result1 = pattern->CheckAutoReset();
    EXPECT_EQ(pattern->autoReset_, true);
    EXPECT_EQ(result1, true);
    auto patternLockPaintProperty = frameNode->GetPaintProperty<PatternLockPaintProperty>();
    ASSERT_NE(patternLockPaintProperty, nullptr);
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
 * @tc.name: PatternLockPatternTest003
 * @tc.desc: Test PatternLock pattern method AddPassPoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest003, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    ASSERT_NE(pattern, nullptr);
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
 * @tc.name: PatternLockPatternTest004
 * @tc.desc: Test PatternLock pattern method CheckChoosePoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest004, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    ASSERT_NE(pattern, nullptr);

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
 * @tc.name: PatternLockPatternTest005
 * @tc.desc: Test PatternLock pattern method AddChoosePoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest005, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    ASSERT_NE(pattern, nullptr);
    frameNode->GetGeometryNode()->SetContentSize(SizeF(300.0f, 300.0f));

    /**
     * @tc.cases: when distance is unvalid, Point(x, y) will not AddChoosePoint.
     */
    float offsetX = 75.0f;
    float offsetY = 75.0f;
    OffsetF offset(offsetX, offsetY);
    bool result1 = pattern->AddChoosePoint(offset, 1, 1);
    EXPECT_FALSE(result1);
    auto patternLockPaintProperty = frameNode->GetPaintProperty<PatternLockPaintProperty>();
    ASSERT_NE(patternLockPaintProperty, nullptr);
    patternLockPaintProperty->UpdateCircleRadius(CIRCLE_RADIUS);
    bool result2 = pattern->AddChoosePoint(offset, 1, 1);
    EXPECT_FALSE(result2);

    /**
     * @tc.cases: when distance is valid, Point(x, y) will AddChoosePoint.
     */
    patternLockPaintProperty->UpdateCircleRadius(Dimension(20.0));
    EXPECT_EQ(pattern->choosePoint_.size(), 0);
    EXPECT_FALSE(pattern->CheckChoosePoint(1, 1));
    bool result3 = pattern->AddChoosePoint(offset, 1, 1);
    EXPECT_EQ(pattern->choosePoint_.size(), 1);
    EXPECT_TRUE(result3);

    EXPECT_TRUE(pattern->CheckChoosePoint(1, 1));
    bool result4 = pattern->AddChoosePoint(offset, 1, 1);
    EXPECT_EQ(pattern->choosePoint_.size(), 1);
    EXPECT_TRUE(result4);

    offsetX = 150.0f;
    offsetY = 150.0f;
    offset.SetX(offsetX);
    offset.SetY(offsetY);
    EXPECT_FALSE(pattern->CheckChoosePoint(2, 2));
    bool result5 = pattern->AddChoosePoint(offset, 2, 2);
    EXPECT_EQ(pattern->choosePoint_.size(), 2);
    EXPECT_TRUE(result5);
}

/**
 * @tc.name: PatternLockPatternTest006
 * @tc.desc: Test PatternLock pattern method OnTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest006, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    ASSERT_NE(pattern, nullptr);

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
 * @tc.name: PatternLockPatternTest007
 * @tc.desc: Test PatternLock pattern method HandleGestureUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest007, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call OnTouchMove
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    float offsetX = 1.0f;
    float offsetY = 1.0f;
    Offset offset(offsetX, offsetY);
    pattern->isMoveEventValid_ = false;
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    pattern->HandleGestureUpdate(info);
    EXPECT_EQ(pattern->cellCenter_.GetX(), .0f);
    EXPECT_EQ(pattern->cellCenter_.GetY(), .0f);
    info.SetLocalLocation(offset);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    pattern->HandleGestureUpdate(info);
    EXPECT_EQ(pattern->cellCenter_.GetX(), .0f);
    EXPECT_EQ(pattern->cellCenter_.GetY(), .0f);
    pattern->isMoveEventValid_ = true;
    pattern->HandleGestureUpdate(info);
    EXPECT_EQ(pattern->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern->cellCenter_.GetY(), offset.GetY());
}

/**
 * @tc.name: PatternLockPatternTest008
 * @tc.desc: Test PatternLock pattern method OnTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest008, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    ASSERT_NE(pattern, nullptr);

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
 * @tc.name: PatternLockPatternTest009
 * @tc.desc: Test PatternLock pattern method HandleTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest009, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    ASSERT_NE(pattern, nullptr);

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
    TouchLocationInfo locationInfoTouchUnkown(0);
    locationInfoTouchUnkown.SetLocalLocation(offset);
    locationInfoTouchUnkown.SetTouchType(TouchType::UNKNOWN);
    TouchEventInfo touchEventInfoTouchUnkown("onTouchUnkown");
    touchEventInfoTouchUnkown.AddTouchLocationInfo(std::move(locationInfoTouchUnkown));
    pattern->HandleTouchEvent(touchEventInfoTouchUnkown);
}

/**
 * @tc.name: PatternLockPatternTest010
 * @tc.desc: Test PatternLock pattern method InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest010, TestSize.Level1)
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
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call InitTouchEvent
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    pattern->InitTouchEvent(gestureHub, pattern->touchDownListener_);
    ASSERT_NE(pattern->touchDownListener_, nullptr);
    auto touchEvent = gestureHub->touchEventActuator_->touchEvents_.back();
    ASSERT_NE(touchEvent, nullptr);
    auto info = TouchEventInfo("");
    touchEvent->callback_(info);
    pattern->InitTouchEvent(gestureHub, pattern->touchDownListener_);
    EXPECT_EQ(gestureHub->touchEventActuator_->touchEvents_.back(), touchEvent);
}

/**
 * @tc.name: PatternLockPaintMethodTest001
 * @tc.desc: Test PatternLockPaintMethod GetThemeProp and UpdateContentModifier Function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create patternLock PaintMethod and PatternLockTheme.
     */
    std::vector<PatternLockCell> vecCell;
    auto modifier = AceType::MakeRefPtr<PatternLockModifier>();
    PatternLockPaintMethod paintMethod(OffsetF(), false, vecCell, modifier);
    auto patternLockPaintProperty = AceType::MakeRefPtr<PatternLockPaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF());
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    patternlockTheme->regularColor_ = REGULAR_COLOR;
    patternlockTheme->selectedColor_ = SELECTED_COLOR;
    patternlockTheme->activeColor_ = ACTIVE_COLOR;
    patternlockTheme->pathColor_ = PATH_COLOR;
    patternlockTheme->circleRadius_ = CIRCLE_RADIUS;
    patternlockTheme->pathStrokeWidth_ = PATH_STROKE_WIDTH;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));
    /**
     * @tc.case: case1. call GetThemeProp with PatternLockTheme.
     */
    paintMethod.GetThemeProp();
    EXPECT_EQ(paintMethod.sideLength_, .0f);
    EXPECT_EQ(paintMethod.circleRadius_, CIRCLE_RADIUS);
    EXPECT_EQ(paintMethod.pathStrokeWidth_, PATH_STROKE_WIDTH);
    EXPECT_EQ(paintMethod.regularColor_, REGULAR_COLOR);
    EXPECT_EQ(paintMethod.selectedColor_, SELECTED_COLOR);
    EXPECT_EQ(paintMethod.activeColor_, ACTIVE_COLOR);
    EXPECT_EQ(paintMethod.pathColor_, PATH_COLOR);
    /**
     * @tc.case: case2. call UpdateContentModifier with unvalid PatternLockPaintProperty.
     */
    PaintWrapper paintWrapper(nullptr, geometryNode, patternLockPaintProperty);
    paintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(paintMethod.sideLength_, paintWrapper.GetContentSize().Width());
    EXPECT_EQ(paintMethod.circleRadius_, CIRCLE_RADIUS);
    EXPECT_EQ(paintMethod.pathStrokeWidth_, PATH_STROKE_WIDTH);
    EXPECT_EQ(paintMethod.regularColor_, REGULAR_COLOR);
    EXPECT_EQ(paintMethod.selectedColor_, SELECTED_COLOR);
    EXPECT_EQ(paintMethod.activeColor_, ACTIVE_COLOR);
    EXPECT_EQ(paintMethod.pathColor_, PATH_COLOR);
    /**
     * @tc.case: case3. call UpdateContentModifier with valid PatternLockPaintProperty.
     */
    patternLockPaintProperty->UpdateCircleRadius(Dimension(20.0));
    patternLockPaintProperty->UpdatePathStrokeWidth(Dimension(10.0));
    patternLockPaintProperty->UpdateAutoReset(false);
    patternLockPaintProperty->UpdateRegularColor(Color::RED);
    patternLockPaintProperty->UpdateSelectedColor(Color::GREEN);
    patternLockPaintProperty->UpdateActiveColor(Color::BLACK);
    patternLockPaintProperty->UpdatePathColor(Color::WHITE);
    paintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(paintMethod.circleRadius_, patternLockPaintProperty->GetCircleRadiusValue());
    EXPECT_EQ(paintMethod.pathStrokeWidth_, patternLockPaintProperty->GetPathStrokeWidthValue());
    EXPECT_EQ(paintMethod.regularColor_, patternLockPaintProperty->GetRegularColorValue());
    EXPECT_EQ(paintMethod.selectedColor_, patternLockPaintProperty->GetSelectedColorValue());
    EXPECT_EQ(paintMethod.activeColor_, patternLockPaintProperty->GetActiveColorValue());
    EXPECT_EQ(paintMethod.pathColor_, patternLockPaintProperty->GetPathColorValue());
}

/**
 * @tc.name: PatternLockModifierTest001
 * @tc.desc: Test PatternLockModifier onDraw function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockModifierTest001, TestSize.Level1)
{
    PatternLockModifier patternlockModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100.0f, 100.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(9);
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    patternlockModifier.onDraw(context);
}

/**
 * @tc.name: PatternLockModifierTest002
 * @tc.desc: Test GetCircleCenterByXY function can get correct offset.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockModifierTest002, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<PatternLockModifier>();
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
HWTEST_F(PatternLockPatternTestNg, PatternLockModifierTest003, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    OffsetF offset;
    /**
     * @tc.case: case1. PatternLock's choosePoint count = 0.
     */
    std::vector<PatternLockCell> vecCell;
    auto patternlockModifier1 = AceType::MakeRefPtr<PatternLockModifier>();
    patternlockModifier1->SetChoosePoint(vecCell);
    EXPECT_CALL(canvas, Restore()).Times(0);
    patternlockModifier1->PaintLockLine(canvas, offset);
    /**
     * @tc.case: case2. pathStrokeWidth_ <= 0.
     */
    std::vector<PatternLockCell> vecCell2 = { PatternLockCell(0, 1), PatternLockCell(0, 2) };
    auto patternlockModifier2 = AceType::MakeRefPtr<PatternLockModifier>();
    patternlockModifier2->SetChoosePoint(vecCell2);
    patternlockModifier2->SetPathStrokeWidth(0.0);
    EXPECT_CALL(canvas, Restore()).Times(0);
    patternlockModifier2->PaintLockLine(canvas, offset);
    /**
     * @tc.case: case3. isMoveEventValid_ is flase.
     */
    std::vector<PatternLockCell> vecCell3 = { PatternLockCell(0, 1), PatternLockCell(0, 2), PatternLockCell(1, 2) };
    auto patternlockModifier3 = AceType::MakeRefPtr<PatternLockModifier>();
    patternlockModifier3->SetChoosePoint(vecCell3);
    patternlockModifier3->SetPathStrokeWidth(Dimension(10.0).ConvertToPx());
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(vecCell3.size() - 1);
    EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(1);
    patternlockModifier3->PaintLockLine(canvas, offset);
    /**
     * @tc.case: case4. isMoveEventValid_ is true.
     */
    std::vector<PatternLockCell> vecCell4 = { PatternLockCell(0, 1), PatternLockCell(0, 2), PatternLockCell(1, 2),
        PatternLockCell(2, 2) };
    auto patternlockModifier4 = AceType::MakeRefPtr<PatternLockModifier>();
    patternlockModifier4->SetChoosePoint(vecCell4);
    patternlockModifier4->SetPathStrokeWidth(Dimension(10.0).ConvertToPx());
    patternlockModifier4->SetIsMoveEventValid(true);
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(vecCell4.size());
    EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(1);
    patternlockModifier4->PaintLockLine(canvas, offset);
}

/**
 * @tc.name: PatternLockModifierTest004
 * @tc.desc: Test PaintLockCircle function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockModifierTest004, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    OffsetF offset;
    std::vector<PatternLockCell> vecCell = { PatternLockCell(0, 0), PatternLockCell(0, 2), PatternLockCell(1, 2) };
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>();
    patternlockModifier->SetChoosePoint(vecCell);
    patternlockModifier->SetSideLength(36.0);
    /**
     * @tc.case: case1. Current Point (x, y) is not checked.
     */
    patternlockModifier->SetCircleRadius(-4.0);
    EXPECT_FALSE(patternlockModifier->CheckChoosePoint(1, 4));
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(canvas, DetachBrush()).WillOnce(ReturnRef(canvas));
    patternlockModifier->PaintLockCircle(canvas, offset, 1, 4);
    /**
     * @tc.case: case2. Current Point (x, y) is checked but the selected Point is not the last Point.
     */
    patternlockModifier->SetCircleRadius(10.0);
    EXPECT_TRUE(patternlockModifier->CheckChoosePoint(0, 0));
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(canvas, DetachBrush()).WillOnce(ReturnRef(canvas));
    patternlockModifier->PaintLockCircle(canvas, offset, 0, 0);
    /**
     * @tc.case: case3. last Point (x, y) is checked and isMoveEventValid_ is false.
     */
    patternlockModifier->SetCircleRadius(3.0);
    EXPECT_FALSE(patternlockModifier->isMoveEventValid_->Get());
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(canvas, DetachBrush()).WillOnce(ReturnRef(canvas));
    patternlockModifier->PaintLockCircle(canvas, offset, 1, 2);
    /**
     * @tc.case: case4. last Point (x, y) is checked but isMoveEventValid_ is true.
     */
    patternlockModifier->SetIsMoveEventValid(true);
    EXPECT_TRUE(patternlockModifier->isMoveEventValid_->Get());
    EXPECT_TRUE(patternlockModifier->CheckChoosePointIsLastIndex(1, 2, 1));
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(canvas, DetachBrush()).WillOnce(ReturnRef(canvas));
    patternlockModifier->PaintLockCircle(canvas, offset, 1, 2);
}

/**
 * @tc.name: PatternLockLayoutAlgorithmTest001
 * @tc.desc: Test MeasureContent function .
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockLayoutAlgorithmTest001, TestSize.Level1)
{
    constexpr Dimension sideLength = Dimension(20.0);
    PatternLockLayoutAlgorithm layoutAlgorithm(sideLength);
    auto layoutProperty = AceType::MakeRefPtr<PatternLockLayoutProperty>();
    LayoutWrapper layoutWrapper(nullptr, nullptr, layoutProperty);
    /**
     * @tc.case: case1.
     */
    LayoutConstraintF constraint1;
    auto size1 = layoutAlgorithm.MeasureContent(constraint1, &layoutWrapper);
    EXPECT_EQ(size1.value(), SizeF(20.0f, 20.0f));
    /**
     * @tc.case: case2.
     */
    LayoutConstraintF constraint2;
    constraint2.maxSize = SizeF(10.0f, 25.0f);
    constraint2.minSize = SizeF(15.0f, 20.0f);
    auto size2 = layoutAlgorithm.MeasureContent(constraint2, &layoutWrapper);
    EXPECT_EQ(size2.value(), SizeF(15.0f, 15.0f));
    /**
     * @tc.case: case3.
     */
    LayoutConstraintF constraint3;
    constraint3.maxSize = SizeF(40.0f, 30.0f);
    constraint3.minSize = SizeF(15.0f, 20.0f);
    layoutProperty->UpdateSideLength(Dimension(30.0));
    auto size3 = layoutAlgorithm.MeasureContent(constraint3, &layoutWrapper);
    EXPECT_EQ(size3.value(), SizeF(30.0f, 30.0f));
}
} // namespace OHOS::Ace::NG
