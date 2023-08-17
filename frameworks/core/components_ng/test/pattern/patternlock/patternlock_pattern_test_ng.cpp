/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
const Color HOVER_COLOR = Color::GRAY;
const Color PRESS_COLOR = Color::GRAY;
constexpr Dimension PATH_STROKE_WIDTH = 34.0_vp;
constexpr Dimension HOTSPOT_CIRCLE_RADIUS = 48.0_vp;
constexpr float SIDE_LENGH = 36.0f;
constexpr float POINT_NOT_CHECK_FLOAT = -4.0f;
constexpr float POINT_CHECK_FLOAT = 10.0f;
constexpr float LAST_POINT_CHECK_FLOAT = 3.0f;
constexpr float FIRST_POINT_CHECK_FLOAT = 200.0f;
constexpr float CONTENT_SIZE_FLOAT = 300.0f;
constexpr float CONTENT_OFFSET_FLOAT = 150.0f;
constexpr float CIRCLE_RADIUS_FLOAT = 200.0f;
constexpr float DEFAULT_SIDE_LENGTH = 20.0f;
constexpr int32_t PATTERN_LOCK_COL_COUNT = 3;
constexpr int32_t RADIUS_TO_DIAMETER = 2;
inline int32_t GetPointIndex(int32_t x, int32_t y)
{
    return (x - 1) * PATTERN_LOCK_COL_COUNT + (y - 1);
}
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
 * @tc.name: PatternLockEventTest002
 * @tc.desc: Test PatternLock onDotConnected event.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();

    /**
     * @tc.steps: step2. Init dotConnected result data structure and onDotConnected function
     */
    int32_t connectedDot = -1;
    auto onDotConnected = [&connectedDot](int32_t currentIndex) { connectedDot = currentIndex; };
    patternLockModelNG.SetDotConnected(onDotConnected);

    /**
     * @tc.steps: step3. Get event hub and call UpdateDotConnectedEvent function
     * @tc.expected: step3. Check the event result value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::PatternLockEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->UpdateDotConnectedEvent(1);
    EXPECT_EQ(connectedDot, 1);
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
    pattern->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    ASSERT_NE(pattern->patternLockModifier_, nullptr);

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
    pattern->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    ASSERT_NE(pattern->patternLockModifier_, nullptr);
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
    pattern->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    ASSERT_NE(pattern->patternLockModifier_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    ASSERT_NE(patternlockTheme, nullptr);
    patternlockTheme->hotSpotCircleRadius_ = HOTSPOT_CIRCLE_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));

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
    patternLockPaintProperty->UpdateCircleRadius(Dimension(200.0));
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
    pattern->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    ASSERT_NE(pattern->patternLockModifier_, nullptr);

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
    pattern->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    ASSERT_NE(pattern->patternLockModifier_, nullptr);

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
    pattern->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    ASSERT_NE(pattern->patternLockModifier_, nullptr);

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
 * @tc.name: PatternLockPatternTest011
 * @tc.desc: Test PatternLock pattern method HandleFocusEvent, HandleBlurEvent and GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest011, TestSize.Level1)
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
    auto focushub = frameNode->GetFocusHub();
    ASSERT_NE(focushub, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    ASSERT_NE(patternlockTheme, nullptr);
    patternlockTheme->hotSpotCircleRadius_ = HOTSPOT_CIRCLE_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));
    /**
     * @tc.steps: step3. Set PatternLock pattern variable and Init FocusHub.
     */
    pattern->isMoveEventValid_ = false;
    pattern->choosePoint_.push_back(PatternLockCell(1, 2));
    pattern->cellCenter_ = OffsetF(1.0f, 1.0f);
    pattern->currentPoint_ = {0, 0};
    pattern->InitFocusEvent();
    /**
     * @tc.steps: step4. Call HandleFocusEvent function.
     */
    ASSERT_NE(focushub->onFocusInternal_, nullptr);
    focushub->onFocusInternal_();
    EXPECT_EQ(pattern->isMoveEventValid_, true);
    EXPECT_EQ(pattern->choosePoint_.empty(), true);
    EXPECT_EQ(pattern->cellCenter_, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(pattern->currentPoint_, std::make_pair(1, 1));
    /**
     * @tc.steps: step5. Call HandleBlurEvent function.
     */
    ASSERT_NE(focushub->onBlurInternal_, nullptr);
    focushub->onBlurInternal_();
    EXPECT_EQ(pattern->isMoveEventValid_, false);
    /**
     * @tc.steps: step6. Call GetInnerFocusPaintRect function.
     */
    ASSERT_NE(focushub->getInnerFocusRectFunc_, nullptr);
    RoundRect focusRectInner;
    focushub->getInnerFocusRectFunc_(focusRectInner);
    EXPECT_FALSE(focusRectInner.radius_.data_.empty());
}

/**
 * @tc.name: PatternLockPatternTest012
 * @tc.desc: Test PatternLock pattern method HandleFocusEvent, HandleBlurEvent and GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest012, TestSize.Level1)
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
    auto focushub = frameNode->GetFocusHub();
    ASSERT_NE(focushub, nullptr);
    pattern->InitFocusEvent();
    ASSERT_NE(focushub->onKeyEventsInternal_[OnKeyEventType::DEFAULT], nullptr);
    /**
     * @tc.steps: step3. Call OnKeyEvent function.
     */
    auto event = KeyEvent();
    /**
     * @tc.case: case1: KeyAction is UNKNOWN.
     */
    event.action = KeyAction::UNKNOWN;
    EXPECT_FALSE(focushub->onKeyEventsInternal_[OnKeyEventType::DEFAULT](event));
    /**
     * @tc.case: case2: KeyAction is DOWN and KeyCode is KEY_SPACE.
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_SPACE;
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case3: KeyAction is DOWN, KeyCode is KEY_ENTER and isMoveEventValid_ is true.
     */
    event.code = KeyCode::KEY_ENTER;
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case4: KeyAction is DOWN, KeyCode is KEY_ENTER and isMoveEventValid_ is false.
     */
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case5: KeyAction is DOWN, KeyCode is KEY_DPAD_UP and current point is first point.
     */
    event.code = KeyCode::KEY_DPAD_UP;
    pattern->currentPoint_ = {1, 1};
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case6: KeyAction is DOWN, KeyCode is KEY_DPAD_UP and current point is last point.
     */
    pattern->currentPoint_ = {3, 3};
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case7: KeyAction is DOWN, KeyCode is KEY_DPAD_DOWN and current point is first point.
     */
    event.code = KeyCode::KEY_DPAD_DOWN;
    pattern->currentPoint_ = {1, 1};
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case8: KeyAction is DOWN, KeyCode is KEY_DPAD_DOWN and current point is last point.
     */
    pattern->currentPoint_ = {3, 3};
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case9: KeyAction is DOWN, KeyCode is KEY_DPAD_LEFT and current point is first point.
     */
    event.code = KeyCode::KEY_DPAD_LEFT;
    pattern->currentPoint_ = {1, 1};
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case10: KeyAction is DOWN, KeyCode is KEY_DPAD_LEFT and current point is last point.
     */
    pattern->currentPoint_ = {3, 3};
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case11: KeyAction is DOWN, KeyCode is KEY_DPAD_RIGHT and current point is first point.
     */
    event.code = KeyCode::KEY_DPAD_RIGHT;
    pattern->currentPoint_ = {1, 1};
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case12: KeyAction is DOWN, KeyCode is KEY_DPAD_RIGHT and current point is last point.
     */
    pattern->currentPoint_ = {3, 3};
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case13: KeyAction is DOWN, KeyCode is KEY_MOVE_HOME and current point is last point.
     */
    event.code = KeyCode::KEY_MOVE_HOME;
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case14: KeyAction is DOWN, KeyCode is KEY_MOVE_END and current point is first point.
     */
    event.code = KeyCode::KEY_MOVE_END;
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case15: KeyAction is DOWN and KeyCode is KEY_ESCAPE.
     */
    event.code = KeyCode::KEY_ESCAPE;
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    /**
     * @tc.case: case16: KeyAction is DOWN and KeyCode is illegal.
     */
    event.code = KeyCode::KEY_FORWARD_DEL;
    EXPECT_FALSE(pattern->OnKeyEvent(event));
}

/**
 * @tc.name: PatternLockPatternTest013
 * @tc.desc: Test PatternLock pattern OnFocusClick.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest013, TestSize.Level1)
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
     * @tc.steps: step3. Call OnFocusClick.
     */
    /**
     * @tc.case: case1: CheckAutoReset is false.
     */
    pattern->autoReset_ = false;
    pattern->choosePoint_ = { PatternLockCell(1, 2) };
    pattern->isMoveEventValid_ = false;
    EXPECT_FALSE(pattern->CheckAutoReset());
    pattern->OnFocusClick();
    EXPECT_FALSE(pattern->isMoveEventValid_);
    /**
     * @tc.case: case2: CheckAutoReset is true and isMoveEventValid_ is false.
     */
    pattern->autoReset_ = true;
    pattern->currentPoint_ = std::make_pair(1, 1);
    pattern->OnFocusClick();
    EXPECT_TRUE(pattern->isMoveEventValid_);
    EXPECT_FALSE(pattern->choosePoint_.empty());
    /**
     * @tc.case: case3: CheckAutoReset is true, isMoveEventValid_ is false current point is checked.
     */
    pattern->OnFocusClick();
    EXPECT_TRUE(pattern->isMoveEventValid_);
}

/**
 * @tc.name: PatternLockPatternTest014
 * @tc.desc: Test PatternLock pattern method HandleHoverEvent and HandleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init PatternLock node
     */
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();
    /**
     * @tc.steps: step2. Init PatternLock pattern
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    ASSERT_NE(pattern, nullptr);
    frameNode->GetGeometryNode()->SetContentSize(SizeF(CONTENT_SIZE_FLOAT, CONTENT_SIZE_FLOAT));
    frameNode->GetGeometryNode()->SetContentOffset(OffsetF(CONTENT_OFFSET_FLOAT, CONTENT_OFFSET_FLOAT));
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputEventHub = eventHub->GetInputEventHub();
    CHECK_NULL_VOID(inputEventHub);
    pattern->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    ASSERT_NE(pattern->patternLockModifier_, nullptr);
    auto patternLockPaintProperty = frameNode->GetPaintProperty<PatternLockPaintProperty>();
    ASSERT_NE(patternLockPaintProperty, nullptr);
    patternLockPaintProperty->UpdateCircleRadius(Dimension(CIRCLE_RADIUS_FLOAT));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    ASSERT_NE(patternlockTheme, nullptr);
    patternlockTheme->hotSpotCircleRadius_ = HOTSPOT_CIRCLE_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));
    pattern->InitMouseEvent();
    ASSERT_FALSE(inputEventHub->hoverEventActuator_->inputEvents_.empty());
    ASSERT_FALSE(inputEventHub->mouseEventActuator_->inputEvents_.empty());
    /**
     * @tc.steps: step3. Call HandleHoverEvent function.
     */
    for (const auto& hoverCallback : inputEventHub->hoverEventActuator_->inputEvents_) {
        ASSERT_NE(hoverCallback, nullptr);
        (*hoverCallback)(false);
    }
    EXPECT_FALSE(pattern->patternLockModifier_->isHover_->Get());
    /**
     * @tc.steps: step4. Call HandleMouseEvent function and hover not on point.
     */
    auto info = MouseInfo();
    info.SetLocalLocation(Offset(0.0f, 0.0f));
    for (const auto& mouseCallback : inputEventHub->mouseEventActuator_->inputEvents_) {
        ASSERT_NE(mouseCallback, nullptr);
        (*mouseCallback)(info);
    }
    EXPECT_EQ(pattern->patternLockModifier_->hoverIndex_->Get(), -1);
    /**
     * @tc.steps: step5. Call HandleMouseEvent function and hover on point.
     */
    info.SetLocalLocation(Offset(FIRST_POINT_CHECK_FLOAT, FIRST_POINT_CHECK_FLOAT));
    for (const auto& mouseCallback : inputEventHub->mouseEventActuator_->inputEvents_) {
        ASSERT_NE(mouseCallback, nullptr);
        (*mouseCallback)(info);
    }
    EXPECT_EQ(pattern->patternLockModifier_->hoverIndex_->Get(), 0);
}

/**
 * @tc.name: PatternLockPatternTest015
 * @tc.desc: Test PatternLock pattern method SetChallengeResult.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest015, TestSize.Level1)
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
    pattern->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    ASSERT_NE(pattern->patternLockModifier_, nullptr);
    ASSERT_NE(pattern->patternLockController_->setChallengeResultImpl_, nullptr);

    /**
     * @tc.steps: step3. Call SetChallengeResult function and challenge result set CORRECT.
     */
    pattern->patternLockController_->SetChallengeResult(V2::PatternLockChallengeResult::CORRECT);
    ASSERT_TRUE(pattern->patternLockModifier_->challengeResult_.has_value());
    EXPECT_EQ(pattern->patternLockModifier_->challengeResult_.value(), NG::PatternLockChallengeResult::CORRECT);

    /**
     * @tc.steps: step4. Call SetChallengeResult function and challenge result set WRONG.
     */
    pattern->patternLockController_->SetChallengeResult(V2::PatternLockChallengeResult::WRONG);
    ASSERT_TRUE(pattern->patternLockModifier_->challengeResult_.has_value());
    EXPECT_EQ(pattern->patternLockModifier_->challengeResult_.value(), NG::PatternLockChallengeResult::WRONG);

    /**
     * @tc.steps: step5. When isMoveEventValid_ is true call SetChallengeResult function and challenge result set
     * CORRECT.
     */
    EXPECT_EQ(pattern->patternLockModifier_->challengeResult_, NG::PatternLockChallengeResult::WRONG);
    pattern->isMoveEventValid_ = true;
    pattern->patternLockController_->SetChallengeResult(V2::PatternLockChallengeResult::CORRECT);
    ASSERT_TRUE(pattern->patternLockModifier_->challengeResult_.has_value());
    EXPECT_EQ(pattern->patternLockModifier_->challengeResult_.value(), NG::PatternLockChallengeResult::WRONG);

    /**
     * @tc.steps: step6. Call SetChallengeResult function and challenge result illegal.
     */
    pattern->isMoveEventValid_ = false;
    pattern->patternLockController_->SetChallengeResult(V2::PatternLockChallengeResult(0));
    ASSERT_FALSE(pattern->patternLockModifier_->challengeResult_.has_value());
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
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
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
    EXPECT_CALL(canvas, Save()).Times(0);
    EXPECT_CALL(canvas, Restore()).Times(0);
    patternlockModifier1->PaintLockLine(canvas, offset);
    /**
     * @tc.case: case2. pathStrokeWidth_ <= 0.
     */
    std::vector<PatternLockCell> vecCell2 = { PatternLockCell(0, 1), PatternLockCell(0, 2) };
    auto patternlockModifier2 = AceType::MakeRefPtr<PatternLockModifier>();
    patternlockModifier2->SetChoosePoint(vecCell2);
    patternlockModifier2->SetPathStrokeWidth(0.0);
    EXPECT_CALL(canvas, Save()).Times(0);
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
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(vecCell3.size() - 2);
    EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, Save()).Times(1);
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
    patternlockModifier4->sideLength_->Set(SIDE_LENGTH.Value());
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(vecCell4.size());
    EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, Save()).Times(1);
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
    patternlockModifier->SetSideLength(SIDE_LENGH);
    /**
     * @tc.case: case1. Current Point (x, y) is not checked.
     */
    patternlockModifier->SetCircleRadius(POINT_NOT_CHECK_FLOAT);
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
    patternlockModifier->SetHoverIndex(GetPointIndex(0, 0));
    EXPECT_FALSE(patternlockModifier->isMoveEventValid_->Get());
    EXPECT_FALSE(patternlockModifier->isHover_->Get());
    EXPECT_EQ(patternlockModifier->hoverIndex_->Get(), GetPointIndex(0, 0));
    EXPECT_TRUE(patternlockModifier->CheckChoosePoint(0, 0));
    EXPECT_CALL(canvas, AttachBrush(_)).Times(2).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(2);
    EXPECT_CALL(canvas, DetachBrush()).Times(2).WillRepeatedly(ReturnRef(canvas));
    patternlockModifier->PaintLockCircle(canvas, offset, 0, 0);
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
}

/**
 * @tc.name: PatternLockModifierTest005
 * @tc.desc: Test PaintLockCircle function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockModifierTest005, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    OffsetF offset;
    std::vector<PatternLockCell> vecCell = { PatternLockCell(0, 0), PatternLockCell(0, 2), PatternLockCell(1, 2) };
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>();
    patternlockModifier->SetChoosePoint(vecCell);
    patternlockModifier->SetSideLength(SIDE_LENGH);
    /**
     * @tc.case: case1. last Point (x, y) is checked, isHover_is false, hover index is not current Point,
     * isMoveEventValid_ is false and challengeResult_ has value.
     */
    std::optional<NG::PatternLockChallengeResult> ngChallengeResult = NG::PatternLockChallengeResult::WRONG;
    ngChallengeResult = NG::PatternLockChallengeResult::CORRECT;
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
    EXPECT_CALL(canvas, AttachBrush(_)).Times(3).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(3);
    EXPECT_CALL(canvas, DetachBrush()).Times(3).WillRepeatedly(ReturnRef(canvas));
    patternlockModifier->PaintLockCircle(canvas, offset, 1, 2);
}

/**
 * @tc.name: PatternLockModifierTest006
 * @tc.desc: Test ConnectedCircleAnimate and ConnectedLineAnimate functions.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockModifierTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier and  Set ChoosePoint
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>();
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
HWTEST_F(PatternLockPatternTestNg, PatternLockModifierTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier and  Set ChoosePoint
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>();
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
HWTEST_F(PatternLockPatternTestNg, PatternLockModifierTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>();
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
 * @tc.desc: Test PaintCanceledLineTail and PaintConnectedLineTail function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockModifierTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>();
    std::vector<PatternLockCell> vecCell = { PatternLockCell(0, 0) };
    patternlockModifier->SetChoosePoint(vecCell);
    patternlockModifier->sideLength_->Set(SIDE_LENGTH.Value());
    /**
     * @tc.steps: step2. call PaintCanceledLineTail func
     * @tc.expected:Related function is called.
     */
    patternlockModifier->needCanceledLine_ = true;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(1);
    patternlockModifier->PaintCanceledLineTail(canvas, patternlockModifier->offset_->Get());

    /**
     * @tc.steps: step3. call PaintConnectedLineTail func
     * @tc.expected:Related function is not called.
     */
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(0);
    patternlockModifier->PaintConnectedLineTail(canvas, patternlockModifier->offset_->Get());

    /**
     * @tc.steps: step4. add one choosePoint then call PaintConnectedLineTail func
     * @tc.expected:Related function is called.
     */
    patternlockModifier->choosePoint_.emplace_back(PatternLockCell(1, 1));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(1);
    patternlockModifier->PaintConnectedLineTail(canvas, patternlockModifier->offset_->Get());
}

/**
 * @tc.name: PatternLockModifierTest010
 * @tc.desc: Test SetHoverColor, SetPressColor, SetSelectColor and SetChallengeResult function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockModifierTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>();
    /**
     * @tc.steps: step2. call SetHoverColor func
     */
    patternlockModifier->SetHoverColor(HOVER_COLOR);
    EXPECT_EQ(patternlockModifier->hoverColor_->Get(), HOVER_COLOR);
    patternlockModifier->SetHoverColor(HOVER_COLOR);
    EXPECT_EQ(patternlockModifier->hoverColor_->Get(), HOVER_COLOR);
    /**
     * @tc.steps: step3. call SetPressColor func
     */
    patternlockModifier->SetPressColor(PRESS_COLOR);
    EXPECT_EQ(patternlockModifier->pressColor_->Get(), PRESS_COLOR);
    patternlockModifier->SetPressColor(PRESS_COLOR);
    EXPECT_EQ(patternlockModifier->pressColor_->Get(), PRESS_COLOR);
    /**
     * @tc.steps: step4. call SetSelectColor func
     */
    patternlockModifier->SetSelectColor(SELECTED_COLOR);
    EXPECT_EQ(patternlockModifier->selectedColor_->Get(), SELECTED_COLOR);
    patternlockModifier->SetSelectColor(SELECTED_COLOR);
    EXPECT_EQ(patternlockModifier->selectedColor_->Get(), SELECTED_COLOR);
    /**
     * @tc.steps: step5. call SetChallengeResult func
     */
    std::optional<NG::PatternLockChallengeResult> ngChallengeResult = NG::PatternLockChallengeResult::WRONG;
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
HWTEST_F(PatternLockPatternTestNg, PatternLockModifierTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create patternlockModifier
     */
    auto patternlockModifier = AceType::MakeRefPtr<PatternLockModifier>();
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
 * @tc.name: PatternLockLayoutAlgorithmTest001
 * @tc.desc: Test MeasureContent function .
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPatternTestNg, PatternLockLayoutAlgorithmTest001, TestSize.Level1)
{
    PatternLockLayoutAlgorithm layoutAlgorithm;
    auto layoutProperty = AceType::MakeRefPtr<PatternLockLayoutProperty>();
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, layoutProperty);
    /**
     * @tc.case: case1.
     */
    layoutProperty->UpdateSideLength(Dimension(DEFAULT_SIDE_LENGTH));
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
