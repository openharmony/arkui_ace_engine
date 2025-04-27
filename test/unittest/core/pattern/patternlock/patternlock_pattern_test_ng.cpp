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
using namespace testing;
using namespace testing::ext;
namespace {
constexpr float SCROLL_WIDTH = 480.f;
constexpr float SCROLL_HEIGHT = 800.f;
constexpr float PATTERNLOCK_WIDTH = 400.f;
constexpr float PATTERNLOCK_HEIGHT = 400.f;
constexpr Dimension SIDE_LENGTH = 300.0_vp;
constexpr Dimension CIRCLE_RADIUS = 14.0_vp;
constexpr Dimension ACTIVE_CIRCLE_RADIUS = 18.0_vp;
const Color REGULAR_COLOR = Color::BLACK;
const Color SELECTED_COLOR = Color::BLUE;
const Color ACTIVE_COLOR = Color::RED;
const Color PATH_COLOR = Color::GRAY;
const Color ACTIVE_CIRCLE_COLOR = Color::GREEN;
constexpr Dimension PATH_STROKE_WIDTH = 34.0_vp;
constexpr Dimension HOTSPOT_CIRCLE_RADIUS = 48.0_vp;
constexpr float FIRST_POINT_CHECK_FLOAT = 200.0f;
constexpr float CONTENT_SIZE_FLOAT = 300.0f;
constexpr float CONTENT_OFFSET_FLOAT = 150.0f;
constexpr float CIRCLE_RADIUS_FLOAT = 200.0f;
constexpr int32_t PATTERN_LOCK_COL_COUNT = 3;
constexpr int32_t RADIUS_TO_DIAMETER = 2;
} // namespace
class PatternLockPatternTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    void Create(const std::function<void(PatternLockModelNG)>& callback);

    RefPtr<FrameNode> frameNode_;
    RefPtr<PatternLockPattern> pattern_;
    RefPtr<PatternLockEventHub> eventHub_;
    RefPtr<PatternLockLayoutProperty> layoutProperty_;
    RefPtr<PatternLockPaintProperty> paintProperty_;
};

void PatternLockPatternTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_SCROLL_BAR);
    auto scrollBarTheme = ScrollBarTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollBarTheme));
    auto patternLockThemeConstants = CreateThemeConstants(THEME_PATTERN_PATTERN_LOCK);
    auto patternLockTheme = V2::PatternLockTheme::Builder().Build(patternLockThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(V2::PatternLockTheme::TypeId())).WillRepeatedly(Return(patternLockTheme));
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void PatternLockPatternTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void PatternLockPatternTestNg::SetUp() {}

void PatternLockPatternTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
}

void PatternLockPatternTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<PatternLockPattern>();
    eventHub_ = frameNode_->GetEventHub<PatternLockEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<PatternLockLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<PatternLockPaintProperty>();
}

void PatternLockPatternTestNg::Create(const std::function<void(PatternLockModelNG)>& callback)
{
    PatternLockModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(PATTERNLOCK_WIDTH));
    ViewAbstract::SetHeight(CalcLength(PATTERNLOCK_HEIGHT));
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushUITasks(frameNode_);
}

/**
* @tc.name: PatternLockPatternTest001
* @tc.desc: Test PatternLock OnTouchDown.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest001, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();

    /**
    * @tc.steps: step3. Set PatternLock pattern variable and call OnTouchDown
    * @tc.expected: step3. Check the PatternLock pattern value
    */
    float offsetX = 1.0f;
    float offsetY = 1.0f;
    Offset offset(offsetX, offsetY);

    pattern_->autoReset_ = true;
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    TouchLocationInfo locationInfo(0);
    locationInfo.SetLocalLocation(offset);
    pattern_->isMoveEventValid_ = true;
    pattern_->OnTouchDown(locationInfo);
    EXPECT_EQ(pattern_->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern_->cellCenter_.GetY(), offset.GetY());
}

/**
* @tc.name: PatternLockPatternTest002
* @tc.desc: Test PatternLock OnTouchUp.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest002, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();

    /**
    * @tc.steps: step3. Set PatternLock pattern variable and call OnTouchUp
    * @tc.expected: step3. Check the PatternLock pattern value
    */
    pattern_->autoReset_ = false;
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->patternLockModifier_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->patternLockModifier_->choosePoint_.push_back(PatternLockCell(2, 2));
    pattern_->isMoveEventValid_ = true;
    pattern_->OnTouchUp();
    EXPECT_FALSE(pattern_->isMoveEventValid_);
}

/**
* @tc.name: PatternLockPatternTest003
* @tc.desc: Test PatternLock HandleTouchEvent.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest003, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();

    /**
    * @tc.steps: step3. Set PatternLock pattern variable and call HandleTouchEvent
    * @tc.expected: step3. Check the PatternLock pattern value
    */
    float offsetX = 2.0f;
    float offsetY = 2.0f;
    Offset offset(offsetX, offsetY);
    TouchLocationInfo locationInfoTouchDown(0);
    locationInfoTouchDown.SetLocalLocation(offset);
    locationInfoTouchDown.SetTouchType(TouchType::DOWN);
    TouchEventInfo touchEventInfoTouchDown("onTouchDown");
    touchEventInfoTouchDown.AddChangedTouchLocationInfo(std::move(locationInfoTouchDown));
    pattern_->HandleTouchEvent(touchEventInfoTouchDown);
    EXPECT_EQ(pattern_->fingerId_, 0);
    EXPECT_EQ(pattern_->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern_->cellCenter_.GetY(), offset.GetY());
    pattern_->cellCenter_.Reset();

    pattern_->isMoveEventValid_ = true;
    TouchLocationInfo locationInfoTouchUnkown(0);
    locationInfoTouchUnkown.SetLocalLocation(offset);
    locationInfoTouchUnkown.SetTouchType(TouchType::UNKNOWN);
    TouchEventInfo touchEventInfoTouchUnkown("onTouchUnkown");
    touchEventInfoTouchUnkown.AddChangedTouchLocationInfo(std::move(locationInfoTouchUnkown));
    pattern_->HandleTouchEvent(touchEventInfoTouchUnkown);

    pattern_->isMoveEventValid_ = true;
    TouchLocationInfo locationInfoTouchMove(0);
    locationInfoTouchMove.SetLocalLocation(offset);
    locationInfoTouchMove.SetTouchType(TouchType::MOVE);
    TouchEventInfo touchEventInfoTouchMove("onTouchMove");
    touchEventInfoTouchMove.AddChangedTouchLocationInfo(std::move(locationInfoTouchMove));
    pattern_->HandleTouchEvent(touchEventInfoTouchMove);
    EXPECT_EQ(pattern_->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern_->cellCenter_.GetY(), offset.GetY());
    pattern_->cellCenter_.Reset();
}

/**
* @tc.name: PatternLockPatternTest004
* @tc.desc: Test PatternLock HandleFocusEvent, HandleBlurEvent and GetInnerFocusPaintRect.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest004, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    auto focushub = frameNode_->GetFocusHub();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    patternlockTheme->hotSpotCircleRadius_ = HOTSPOT_CIRCLE_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));
    /**
    * @tc.steps: step3. Set PatternLock pattern variable and Init FocusHub.
    */
    pattern_->isMoveEventValid_ = false;
    pattern_->choosePoint_.push_back(PatternLockCell(1, 2));
    pattern_->cellCenter_ = OffsetF(2.0f, 2.0f);
    pattern_->currentPoint_ = { 0, 0 };
    pattern_->InitFocusEvent();
    /**
    * @tc.steps: step4. Call HandleFocusEvent function.
    */
    ASSERT_NE(focushub->onFocusInternal_, nullptr);
    focushub->onFocusInternal_(focushub->focusReason_);
    EXPECT_TRUE(pattern_->isMoveEventValid_);
    EXPECT_TRUE(pattern_->choosePoint_.empty());
    EXPECT_EQ(pattern_->cellCenter_, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(pattern_->currentPoint_, std::make_pair(1, 1));
    /**
    * @tc.steps: step5. Call HandleBlurEvent function.
    */
    ASSERT_NE(focushub->onBlurInternal_, nullptr);
    focushub->onBlurInternal_();
    EXPECT_FALSE(pattern_->isMoveEventValid_);
    /**
    * @tc.steps: step6. Call GetInnerFocusPaintRect function.
    */
    ASSERT_NE(focushub->getInnerFocusRectFunc_, nullptr);
    RoundRect focusRectInner;
    focushub->getInnerFocusRectFunc_(focusRectInner);
    EXPECT_FALSE(focusRectInner.radius_.data_.empty());
}

/**
* @tc.name: PatternLockPatternTest005
* @tc.desc: Test patternlock size change
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest005, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
    * @tc.steps: step1. OnTouchDown a point
    * @tc.expected: cellCenter_ is relative to patternlock
    */
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_);
    mockRenderContext->paintRect_ = RectF(40, 0, PATTERNLOCK_WIDTH, PATTERNLOCK_HEIGHT);

    TouchLocationInfo locationInfo(0);
    locationInfo.SetLocalLocation(Offset(100, 100));
    pattern_->OnTouchDown(locationInfo);
    EXPECT_TRUE(IsEqual(pattern_->cellCenter_, OffsetF(100, 100)));

    /**
    * @tc.steps: step2. Reduce patternloack size, call OnTouchMove
    * @tc.expected: cellCenter_ will change with patternlock
    */
    float width = 200.f;
    float height = 200.f;
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(width));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(height));
    FlushUITasks(frameNode_);
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameRect().Width(), width));
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameRect().Height(), height));

    mockRenderContext->paintRect_ = RectF(90, 0, width, height);
    locationInfo.SetLocalLocation(Offset(200, 200));
    pattern_->OnTouchMove(locationInfo);
    EXPECT_TRUE(IsEqual(pattern_->cellCenter_, OffsetF(200, 200)));
    pattern_->OnTouchUp();
}

/**
* @tc.name: PatternLockPatternTest006
* @tc.desc: Test PatternLock pattern method OnTouchMove.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest006, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
    * @tc.steps: step3. Set PatternLock pattern variable and call OnTouchMove
    * @tc.expected: step3. Check the PatternLock pattern value
    */
    float offsetX = 2.0f;
    float offsetY = 2.0f;
    Offset offset(offsetX, offsetY);
    pattern_->isMoveEventValid_ = false;
    TouchLocationInfo locationInfo(0);
    locationInfo.SetTouchType(TouchType::MOVE);
    locationInfo.SetLocalLocation(offset);
    pattern_->OnTouchMove(locationInfo);
    EXPECT_EQ(pattern_->cellCenter_.GetX(), .0f);
    EXPECT_EQ(pattern_->cellCenter_.GetY(), .0f);
    pattern_->isMoveEventValid_ = true;
    pattern_->OnTouchMove(locationInfo);
    EXPECT_EQ(pattern_->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern_->cellCenter_.GetY(), offset.GetY());
}

/**
* @tc.name: PatternLockPatternTest007
* @tc.desc: Test PatternLock in scrollNode
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest007, TestSize.Level1)
{
    ScrollModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT + 200));
        PaddingProperty padding;
        padding.top = CalcLength(200);
        ViewAbstract::SetPadding(padding);
        {
            PatternLockModelNG patternLockModelNG;
            patternLockModelNG.Create();
            ViewAbstract::SetWidth(CalcLength(PATTERNLOCK_WIDTH));
            ViewAbstract::SetHeight(CalcLength(PATTERNLOCK_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    auto scrollNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    FlushUITasks(scrollNode);

    /**
    * @tc.steps: step1. because colNode padding, patternLockNode offsetY is 200
    */
    auto colNode = GetChildFrameNode(scrollNode, 0);
    auto patternLockNode = GetChildFrameNode(colNode, 0);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    auto patternLockPattern = patternLockNode->GetPattern<PatternLockPattern>();
    EXPECT_TRUE(IsEqual(patternLockNode->GetGeometryNode()->GetFrameOffset(), OffsetF(40, 200)));

    /**
    * @tc.steps: step2. Call OnTouchDown
    * @tc.expected: cellCenter_ is equal to locationInfo
    */
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(patternLockNode->renderContext_);
    mockRenderContext->rect_ = RectF(40, 200, PATTERNLOCK_WIDTH, PATTERNLOCK_HEIGHT);

    TouchLocationInfo locationInfo(0);
    locationInfo.SetLocalLocation(Offset(100, 100));
    patternLockPattern->OnTouchDown(locationInfo);
    EXPECT_TRUE(IsEqual(patternLockPattern->cellCenter_, OffsetF(100, 100)));

    locationInfo.SetLocalLocation(Offset(200, 200));
    patternLockPattern->OnTouchMove(locationInfo);
    EXPECT_TRUE(IsEqual(patternLockPattern->cellCenter_, OffsetF(200, 200)));
    patternLockPattern->OnTouchUp();
}

/**
* @tc.name: PatternLockPatternTest008
* @tc.desc: Test PatternLock OnFocusClick.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest008, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
    * @tc.case: case1: CheckAutoReset is false.
    */
    pattern_->autoReset_ = false;
    pattern_->choosePoint_ = { PatternLockCell(1, 2) };
    pattern_->isMoveEventValid_ = false;
    EXPECT_FALSE(pattern_->CheckAutoReset());
    /**
    * @tc.case: case2: CheckAutoReset is true and isMoveEventValid_ is false.
    */
    pattern_->autoReset_ = true;
    pattern_->currentPoint_ = std::make_pair(1, 1);
    pattern_->OnFocusClick();
    EXPECT_TRUE(pattern_->isMoveEventValid_);
    EXPECT_FALSE(pattern_->choosePoint_.empty());
    /**
    * @tc.case: case3: CheckAutoReset is true, isMoveEventValid_ is false current point is checked.
    */
    pattern_->OnFocusClick();
    EXPECT_TRUE(pattern_->isMoveEventValid_);
}

/**
* @tc.name: PatternLockPatternTest009
* @tc.desc: Test PatternLock CreateNodePaintMethod.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest009, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
    * @tc.steps: step1. call CreateNodePaintMethod.
    * @tc.expected: step1. Check the cellCenter_ value.
    */
    pattern_->screenTouchPoint_ = OffsetF(0.0f, 0.0f);
    auto paintMethod = AceType::DynamicCast<PatternLockPaintMethod>(pattern_->CreateNodePaintMethod());
    EXPECT_EQ(paintMethod->cellCenter_, OffsetF(0.0f, 0.0f));
}

/**
* @tc.name: PatternLockPatternTest010
* @tc.desc: Test PatternLock CalculateCellCenter and GetLastChoosePointOffset.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest010, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
    * @tc.steps: step1. call CalculateCellCenter.
    * @tc.expected: step1. Check the cellCenter_ value.
    */
    pattern_->screenTouchPoint_ = OffsetF(0.0f, 0.0f);
    pattern_->CalculateCellCenter();
    EXPECT_EQ(pattern_->cellCenter_, OffsetF(0.0f, 0.0f));

    /**
    * @tc.steps: step2. call CalculateCellCenter.
    * @tc.expected: step2. Check the PatternLock cellCenter_ value.
    */
    pattern_->cellCenter_ = OffsetF();
    pattern_->isOnKeyEventState_ = true;
    pattern_->CalculateCellCenter();
    EXPECT_EQ(pattern_->cellCenter_, OffsetF());

    /**
    * @tc.steps: step3. call CalculateCellCenter
    * @tc.expected: step3. Check the PatternLock cellCenter_ value.
    */
    auto geometryNode = frameNode_->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(CONTENT_SIZE_FLOAT, CONTENT_SIZE_FLOAT));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_FLOAT, CONTENT_OFFSET_FLOAT));

    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->CalculateCellCenter();
    auto calculateOffsetResult = CONTENT_OFFSET_FLOAT + CONTENT_SIZE_FLOAT / PATTERN_LOCK_COL_COUNT /
                                                            RADIUS_TO_DIAMETER * (RADIUS_TO_DIAMETER - 1);
    EXPECT_EQ(pattern_->cellCenter_, OffsetF(calculateOffsetResult, calculateOffsetResult));
}

/**
* @tc.name: PatternLockPatternTest011
* @tc.desc: Test PatternLock pattern method HandleReset.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest011, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();

    /**
    * @tc.steps: step1. call HandleReset
    * @tc.expected: step1. Check the PatternLock pattern cellCenter_
    */
    pattern_->isMoveEventValid_ = true;
    pattern_->choosePoint_.push_back(PatternLockCell(1, 2));
    pattern_->cellCenter_ = OffsetF(0.0f, 0.0f);
    pattern_->HandleReset();
    EXPECT_TRUE(pattern_->choosePoint_.empty());
    EXPECT_EQ(pattern_->cellCenter_, OffsetF(0.0f, 0.0f));

    /**
    * @tc.steps: step2. PatternLock Init PatternLockController.
    */
    pattern_->InitPatternLockController();
    ASSERT_NE(pattern_->patternLockController_->resetImpl_, nullptr);
    pattern_->patternLockController_->resetImpl_();
    EXPECT_TRUE(pattern_->choosePoint_.empty());
}

/**
* @tc.name: PatternLockPatternTest012
* @tc.desc: Test PatternLock InitTouchEvent.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest012, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
    * @tc.steps: step1. Set PatternLock pattern variable and call InitTouchEvent
    * @tc.expected: step1. Check the PatternLock pattern
    */
    auto gestureHub = frameNode_->GetOrCreateGestureEventHub();
    pattern_->InitTouchEvent(gestureHub, pattern_->touchDownListener_);
    ASSERT_NE(pattern_->touchDownListener_, nullptr);
    auto touchEvent = gestureHub->touchEventActuator_->touchEvents_.back();
    ASSERT_NE(touchEvent, nullptr);
    auto info = TouchEventInfo("");
    touchEvent->callback_(info);
    pattern_->InitTouchEvent(gestureHub, pattern_->touchDownListener_);
    EXPECT_EQ(gestureHub->touchEventActuator_->touchEvents_.back(), touchEvent);
}

/**
* @tc.name: PatternLockPatternTest013
* @tc.desc: Test PatternLock CheckAutoReset.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest013, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
    * @tc.steps: step1. call CheckAutoReset
    * @tc.expected: step1. Check the return value of CheckAutoReset
    */
    bool result1 = pattern_->CheckAutoReset();
    EXPECT_TRUE(result1);
    auto paintProperty_ = frameNode_->GetPaintProperty<PatternLockPaintProperty>();
    paintProperty_->Reset();
    bool result2 = pattern_->CheckAutoReset();
    EXPECT_TRUE(result2);
    pattern_->autoReset_ = false;
    bool result3 = pattern_->CheckAutoReset();
    EXPECT_TRUE(result3);
}

/**
* @tc.name: PatternLockPatternTest014
* @tc.desc: Test PatternLock pattern method HandleHoverEvent and HandleMouseEvent.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest014, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    frameNode_->GetGeometryNode()->SetContentSize(SizeF(CONTENT_SIZE_FLOAT, CONTENT_SIZE_FLOAT));
    frameNode_->GetGeometryNode()->SetContentOffset(OffsetF(CONTENT_OFFSET_FLOAT, CONTENT_OFFSET_FLOAT));
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputEventHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputEventHub);
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    auto paintProperty_ = frameNode_->GetPaintProperty<PatternLockPaintProperty>();
    paintProperty_->UpdateCircleRadius(Dimension(CIRCLE_RADIUS_FLOAT));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    patternlockTheme->hotSpotCircleRadius_ = HOTSPOT_CIRCLE_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));

    pattern_->InitMouseEvent();
    ASSERT_FALSE(inputEventHub->hoverEventActuator_->inputEvents_.empty());
    ASSERT_FALSE(inputEventHub->mouseEventActuator_->inputEvents_.empty());
    /**
    * @tc.steps: step1. Call HandleHoverEvent function.
    */
    for (const auto& hoverCallback : inputEventHub->hoverEventActuator_->inputEvents_) {
        ASSERT_NE(hoverCallback, nullptr);
        (*hoverCallback)(false);
    }
    EXPECT_FALSE(pattern_->patternLockModifier_->isHover_->Get());
    /**
    * @tc.steps: step2. Call HandleMouseEvent function and hover not on point.
    */
    auto info = MouseInfo();
    info.SetLocalLocation(Offset(0.0f, 0.0f));
    for (const auto& mouseCallback : inputEventHub->mouseEventActuator_->inputEvents_) {
        ASSERT_NE(mouseCallback, nullptr);
        (*mouseCallback)(info);
    }
    EXPECT_EQ(pattern_->patternLockModifier_->hoverIndex_->Get(), -1);
    /**
    * @tc.steps: step3. Call HandleMouseEvent function and hover on point.
    */
    info.SetLocalLocation(Offset(FIRST_POINT_CHECK_FLOAT, FIRST_POINT_CHECK_FLOAT));
    for (const auto& mouseCallback : inputEventHub->mouseEventActuator_->inputEvents_) {
        ASSERT_NE(mouseCallback, nullptr);
        (*mouseCallback)(info);
    }
    EXPECT_EQ(pattern_->patternLockModifier_->hoverIndex_->Get(), 0);
}

/**
* @tc.name: PatternLockPatternTest015
* @tc.desc: Test PatternLock pattern method AddPassPoint.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest015, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();

    /**
    * @tc.steps: step1: choosePoint_ is empty.
    */
    EXPECT_TRUE(pattern_->choosePoint_.empty());
    /**
    * @tc.steps: step2: choosePoint_ is not empty.
    */
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 1);
    /**
    * @tc.steps: step3: lastPoint(1, 2), add Point(2, 2), no passPoint.
    */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(2, 2));
    pattern_->AddPassPoint(2, 2);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 2);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 2);
    /**
    * @tc.steps: step4: lastPoint(0, 2), add Point(2, 2), passPoint(1, 2)
    */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(0, 2));
    pattern_->AddPassPoint(2, 2);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 2);
    EXPECT_EQ(pattern_->choosePoint_.size(), 2);
    /**
    * @tc.steps: step5: lastPoint(2, 2), add Point(0, 0), passPoint(1, 1)
    */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(2, 2));
    pattern_->AddPassPoint(0, 0);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 1);
    EXPECT_EQ(pattern_->choosePoint_.size(), 2);
}

/**
* @tc.name: PatternLockPatternTest016
* @tc.desc: Test PatternLock HandleFocusEvent, HandleBlurEvent and GetInnerFocusPaintRect.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest016, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    auto focushub = frameNode_->GetFocusHub();
    pattern_->InitFocusEvent();
    ASSERT_NE(focushub->onKeyEventsInternal_[OnKeyEventType::DEFAULT], nullptr);
    /**
    * @tc.steps: step1. Call OnKeyEvent function.
    */
    auto event = KeyEvent();
    /**
    * @tc.case: case1: KeyAction is DOWN, KeyCode is KEY_DPAD_DOWN and current point is last point.
    */
    pattern_->currentPoint_ = { 3, 3 };
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    /**
    * @tc.case: case2: KeyAction is UNKNOWN.
    */
    event.action = KeyAction::UNKNOWN;
    EXPECT_FALSE(focushub->onKeyEventsInternal_[OnKeyEventType::DEFAULT](event));
    /**
    * @tc.case: case3: KeyAction is DOWN, KeyCode is KEY_DPAD_RIGHT and current point is last point.
    */
    pattern_->currentPoint_ = { 3, 3 };
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    /**
    * @tc.case: case4: KeyAction is DOWN and KeyCode is illegal.
    */
    event.code = KeyCode::KEY_FORWARD_DEL;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    /**
    * @tc.case: case5: KeyAction is DOWN, KeyCode is KEY_ENTER and isMoveEventValid_ is true.
    */
    event.code = KeyCode::KEY_ENTER;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    /**
    * @tc.case: case6: KeyAction is DOWN, KeyCode is KEY_DPAD_UP and current point is first point.
    */
    event.code = KeyCode::KEY_DPAD_UP;
    pattern_->currentPoint_ = { 1, 1 };
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    /**
    * @tc.case: case7: KeyAction is DOWN, KeyCode is KEY_DPAD_LEFT and current point is last point.
    */
    pattern_->currentPoint_ = { 3, 3 };
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
}

/**
* @tc.name: PatternLockPatternTest017
* @tc.desc: Test PatternLock HandleFocusEvent, HandleBlurEvent and GetInnerFocusPaintRect.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest017, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    auto focushub = frameNode_->GetFocusHub();
    pattern_->InitFocusEvent();
    ASSERT_NE(focushub->onKeyEventsInternal_[OnKeyEventType::DEFAULT], nullptr);
    /**
    * @tc.steps: step1. Call OnKeyEvent function.
    */
    auto event = KeyEvent();
    /**
    * @tc.case: case1: KeyAction is DOWN and KeyCode is KEY_SPACE.
    */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_SPACE;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
    * @tc.case: case2: KeyAction is DOWN, KeyCode is KEY_DPAD_UP and current point is last point.
    */
    pattern_->currentPoint_ = { 3, 3 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
    * @tc.case: case3: KeyAction is DOWN, KeyCode is KEY_ENTER and isMoveEventValid_ is false.
    */
    EXPECT_TRUE(pattern_->OnKeyEvent(event));

    /**
    * @tc.case: case4: KeyAction is DOWN, KeyCode is KEY_DPAD_LEFT and current point is first point.
    */
    event.code = KeyCode::KEY_DPAD_LEFT;
    pattern_->currentPoint_ = { 1, 1 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
    * @tc.case: case5: KeyAction is DOWN, KeyCode is KEY_DPAD_DOWN and current point is first point.
    */
    event.code = KeyCode::KEY_DPAD_DOWN;
    pattern_->currentPoint_ = { 1, 1 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
    * @tc.case: case6: KeyAction is DOWN, KeyCode is KEY_MOVE_HOME and current point is last point.
    */
    event.code = KeyCode::KEY_MOVE_HOME;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    
    /**
    * @tc.case: case7: KeyAction is DOWN, KeyCode is KEY_DPAD_RIGHT and current point is first point.
    */
    event.code = KeyCode::KEY_DPAD_RIGHT;
    pattern_->currentPoint_ = { 1, 1 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
}

/**
* @tc.name: PatternLockPatternTest018
* @tc.desc: Test PatternLock CheckChoosePoint.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest018, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
    * @tc.steps: step1. Set PatternLock pattern variable and call CheckChoosePoint
    * @tc.expected: step1. Check the return value of PatternLock pattern method CheckChoosePoint
    */
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->choosePoint_.push_back(PatternLockCell(1, 2));
    auto result1 = pattern_->CheckChoosePoint(1, 2);
    EXPECT_TRUE(result1);
    auto result2 = pattern_->CheckChoosePoint(2, 2);
    EXPECT_FALSE(result2);
}

/**
* @tc.name: PatternLockPatternTest019
* @tc.desc: Test PatternLock pattern method AddChoosePoint.
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest019, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    frameNode_->GetGeometryNode()->SetContentSize(SizeF(300.0f, 300.0f));
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    patternlockTheme->hotSpotCircleRadius_ = HOTSPOT_CIRCLE_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));

    /**
    * @tc.cases: when distance is unvalid, Point(x, y) will not AddChoosePoint.
    */
    float offsetX = 75.0f;
    float offsetY = 75.0f;
    OffsetF offset(offsetX, offsetY);
    bool result1 = pattern_->AddChoosePoint(offset, 1, 1);
    EXPECT_FALSE(result1);
    auto paintProperty_ = frameNode_->GetPaintProperty<PatternLockPaintProperty>();
    paintProperty_->UpdateCircleRadius(CIRCLE_RADIUS);
    bool result2 = pattern_->AddChoosePoint(offset, 1, 1);
    EXPECT_FALSE(result2);

    /**
    * @tc.cases: when distance is valid, Point(x, y) will AddChoosePoint.
    */
    paintProperty_->UpdateCircleRadius(Dimension(200.0));
    EXPECT_EQ(pattern_->choosePoint_.size(), 0);
    EXPECT_FALSE(pattern_->CheckChoosePoint(1, 1));
    bool result3 = pattern_->AddChoosePoint(offset, 1, 1);
    EXPECT_EQ(pattern_->choosePoint_.size(), 0);
    EXPECT_FALSE(result3);

    EXPECT_FALSE(pattern_->CheckChoosePoint(1, 1));
    bool result4 = pattern_->AddChoosePoint(offset, 1, 1);
    EXPECT_EQ(pattern_->choosePoint_.size(), 0);
    EXPECT_FALSE(result4);

    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(400.f, 400.f));
    offsetX = 200.f;
    offsetY = 200.f;
    offset.SetX(offsetX);
    offset.SetY(offsetY);
    EXPECT_FALSE(pattern_->CheckChoosePoint(2, 2));
    bool result5 = pattern_->AddChoosePoint(offset, 2, 2);
    EXPECT_EQ(pattern_->choosePoint_.size(), 0);
    EXPECT_FALSE(result5);
}

/**
* @tc.name: PatternLockPatternTest020
* @tc.desc: Test PatternLockAccessibility .
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest020, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    /**
    * @tc.case: case1 InitVirtualNode .
    */
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    pattern_->CreateNodePaintMethod();
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->accessibilityPropertyVec_.size() > 0);
    /**
    * @tc.case: case2 HandleAccessibilityHoverEvent 1.
    */
    AccessibilityHoverInfo info;
    info.SetActionType(AccessibilityHoverAction::HOVER_MOVE);
    pattern_->HandleAccessibilityHoverEvent(true, info);
    EXPECT_TRUE(pattern_->accessibilityPropertyVec_[0]->GetAccessibilityLevel() ==
        AccessibilityProperty::Level::YES_STR);
    /**
    * @tc.case: case3 HandleTextOnAccessibilityFocusCallback 1.
    */
    pattern_->HandleTextOnAccessibilityFocusCallback(0, 0);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    EXPECT_TRUE(accessibilityProperty->GetAccessibilityLevel() == AccessibilityProperty::Level::NO_STR);
    /**
    * @tc.case: case4 HandleTextOnAccessibilityFocusCallback 2.
    */
    pattern_->HandleTextOnAccessibilityFocusCallback(0, 1);
    pattern_->HandleTextOnAccessibilityFocusCallback(0, 2);
    pattern_->HandleTextOnAccessibilityFocusCallback(1, 0);
    pattern_->HandleTextOnAccessibilityFocusCallback(1, 1);
    pattern_->HandleTextOnAccessibilityFocusCallback(1, 2);
    pattern_->HandleTextOnAccessibilityFocusCallback(2, 0);
    pattern_->HandleTextOnAccessibilityFocusCallback(2, 1);
    pattern_->HandleTextOnAccessibilityFocusCallback(2, 2);
    EXPECT_TRUE(pattern_->choosePoint_.size() == 9);
    EXPECT_TRUE(pattern_->choosePoint_[0].GetColumn() == 0);
    EXPECT_TRUE(pattern_->choosePoint_[0].GetRow() == 0);
    EXPECT_TRUE(pattern_->choosePoint_[3].GetColumn() == 1);
    EXPECT_TRUE(pattern_->choosePoint_[3].GetRow() == 0);
    EXPECT_TRUE(pattern_->choosePoint_[8].GetColumn() == 2);
    EXPECT_TRUE(pattern_->choosePoint_[8].GetRow() == 2);
    /**
    * @tc.case: case5 HandleAccessibilityHoverEvent 2.
    */
    info.SetActionType(AccessibilityHoverAction::HOVER_EXIT);
    pattern_->HandleAccessibilityHoverEvent(true, info);
    EXPECT_FALSE(pattern_->accessibilityPropertyVec_[0]->GetAccessibilityLevel() ==
        AccessibilityProperty::Level::NO_STR);
    EXPECT_FALSE(accessibilityProperty->GetAccessibilityLevel() == AccessibilityProperty::Level::YES_STR);
}

/**
* @tc.name: PatternLockPatternTest021
* @tc.desc: Test PatternLockAccessibility .
* @tc.type: FUNC
*/
HWTEST_F(PatternLockPatternTestNg, PatternLockPatternTest021, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {
        model.SetCircleRadius(CIRCLE_RADIUS);
        model.SetRegularColor(REGULAR_COLOR);
        model.SetSelectedColor(SELECTED_COLOR);
        model.SetActiveColor(ACTIVE_COLOR);
        model.SetPathColor(PATH_COLOR);
        model.SetStrokeWidth(PATH_STROKE_WIDTH);
        model.SetSideLength(SIDE_LENGTH);
        model.SetActiveCircleColor(ACTIVE_CIRCLE_COLOR);
        model.SetActiveCircleRadius(ACTIVE_CIRCLE_RADIUS);
        model.SetEnableWaveEffect(false);
    });
    /**
    * @tc.case: case1 InitVirtualNode .
    */
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    pattern_->textAccessibilityNodeVec_={};
    pattern_->CreateNodePaintMethod();
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->textAccessibilityNodeVec_.size() == 0);
}
}
}