/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "swiper_test_ng.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/button/button_theme.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
void SwiperTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_SWIPER);
    auto swiperIndicatorTheme = SwiperIndicatorTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(SwiperIndicatorTheme::TypeId())).WillRepeatedly(Return(swiperIndicatorTheme));
    swiperIndicatorTheme->color_ = Color::FromString("#182431");
    swiperIndicatorTheme->selectedColor_ = Color::FromString("#007DFF");
    swiperIndicatorTheme->hoverArrowBackgroundColor_ = HOVER_ARROW_COLOR;
    swiperIndicatorTheme->clickArrowBackgroundColor_ = CLICK_ARROW_COLOR;
    swiperIndicatorTheme->arrowDisabledAlpha_ = ARROW_DISABLED_ALPHA;
    swiperIndicatorTheme->size_ = Dimension(6.f);
    TextStyle textStyle;
    textStyle.SetTextColor(INDICATOR_TEXT_FONT_COLOR);
    textStyle.SetFontSize(INDICATOR_TEXT_FONT_SIZE);
    textStyle.SetFontWeight(INDICATOR_TEXT_FONT_WEIGHT);
    swiperIndicatorTheme->digitalIndicatorTextStyle_ = textStyle;
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::SetUp();
}

void SwiperTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockContainer::TearDown();
}

void SwiperTestNg::SetUp() {}

void SwiperTestNg::TearDown()
{
    RemoveFromStageNode();
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    controller_ = nullptr;
    indicatorNode_ = nullptr;
    leftArrowNode_ = nullptr;
    rightArrowNode_ = nullptr;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
}

void SwiperTestNg::GetSwiper()
{
    frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    pattern_ = frameNode_->GetPattern<SwiperPattern>();
    eventHub_ = frameNode_->GetOrCreateEventHub<SwiperEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    controller_ = pattern_->GetSwiperController();
}

void SwiperTestNg::CreateSwiperDone()
{
    CreateDone();
    int index = pattern_->RealTotalCount();
    if (pattern_->IsShowIndicator() && pattern_->HasIndicatorNode()) {
        indicatorNode_ = GetChildFrameNode(frameNode_, index);
        index += 1;
    }
    if (pattern_->HasLeftButtonNode()) {
        leftArrowNode_ = GetChildFrameNode(frameNode_, index);
        index += 1;
    }
    if (pattern_->HasRightButtonNode()) {
        rightArrowNode_ = GetChildFrameNode(frameNode_, index);
    }
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_);
    mockRenderContext->paintRect_ = RectF(0.f, 0.f, SWIPER_WIDTH, SWIPER_HEIGHT);
}

SwiperModelNG SwiperTestNg::CreateSwiper()
{
    SwiperModelNG model;
    model.Create();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    GetSwiper();
    return model;
}

SwiperModelNG SwiperTestNg::CreateArcSwiper()
{
    SwiperModelNG model;
    model.Create(true);
    model.SetIndicatorType(SwiperIndicatorType::ARC_DOT);
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    GetSwiper();
    return model;
}

void SwiperTestNg::CreateSwiperItems(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        ButtonModelNG buttonModelNG;
        buttonModelNG.CreateWithLabel("label");
        ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void SwiperTestNg::CreateItemWithSize(float width, float height)
{
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel("label");
    ViewAbstract::SetWidth(CalcLength(width));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewStackProcessor::GetInstance()->Pop();
}

void SwiperTestNg::CreateWithArrow()
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();
}

void SwiperTestNg::ShowNext()
{
    controller_->ShowNext();
    FlushUITasks();
}

void SwiperTestNg::ShowPrevious()
{
    controller_->ShowPrevious();
    FlushUITasks();
}

void SwiperTestNg::ChangeIndex(int32_t index, bool useAnimation)
{
    controller_->ChangeIndex(index, useAnimation);
    FlushUITasks();
}

void SwiperTestNg::ChangeIndex(int32_t index, SwiperAnimationMode mode)
{
    controller_->ChangeIndex(index, mode);
    FlushUITasks();
}

void SwiperTestNg::SwipeTo(int32_t index)
{
    controller_->SwipeTo(index);
    FlushUITasks();
}

void SwiperTestNg::SwipeToWithoutAnimation(int32_t index)
{
    controller_->SwipeToWithoutAnimation(index);
    FlushUITasks();
}

void SwiperTestNg::RemoveSwiperItem(int32_t index)
{
    frameNode_->RemoveChildAtIndex(index);
    FlushUITasks();
}

void SwiperTestNg::AddSwiperItem(int32_t slot)
{
    RefPtr<FrameNode> testNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    frameNode_->AddChild(testNode, slot);
    FlushUITasks();
}

AssertionResult SwiperTestNg::DigitText(std::u16string expectDigit)
{
    auto currentIndexNode = AceType::DynamicCast<FrameNode>(indicatorNode_->GetFirstChild());
    auto totalCountNode = AceType::DynamicCast<FrameNode>(indicatorNode_->GetLastChild());
    auto currentIndexText = currentIndexNode->GetLayoutProperty<TextLayoutProperty>();
    auto totalCountText = totalCountNode->GetLayoutProperty<TextLayoutProperty>();
    std::u16string actualDigit = currentIndexText->GetContentValue() + totalCountText->GetContentValue();
    if (actualDigit == expectDigit) {
        return AssertionSuccess();
    }
    return AssertionFailure() << "Actual: " << UtfUtils::Str16ToStr8(actualDigit)
                              << " Expected: " << UtfUtils::Str16ToStr8(expectDigit);
}

AssertionResult SwiperTestNg::CurrentIndex(int32_t expectIndex)
{
    if (pattern_->GetCurrentIndex() != expectIndex) {
        return IsEqual(pattern_->GetCurrentIndex(), expectIndex);
    }
    if (!GetChildFrameNode(frameNode_, expectIndex)) {
        return AssertionFailure() << "There is no item at expectIndex: " << expectIndex;
    }
    if (!GetChildFrameNode(frameNode_, expectIndex)->IsActive()) {
        return AssertionFailure() << "The expectIndex item is not active";
    }
    if (GetChildFrameNode(frameNode_, expectIndex)->GetLayoutProperty()->GetVisibility() != VisibleType::GONE) {
        if (NearZero(GetChildWidth(frameNode_, expectIndex))) {
            return AssertionFailure() << "The expectIndex item width is 0";
        }
        if (NearZero(GetChildHeight(frameNode_, expectIndex))) {
            return AssertionFailure() << "The expectIndex item height is 0";
        }
    }
    return AssertionSuccess();
}

/**
 * @tc.name: SwiperPatternComputeNextIndexByVelocity001
 * @tc.desc: ComputeNextIndexByVelocity
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternComputeNextIndexByVelocity001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetItemSpace(100.0_px);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->currentIndex_, 0);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_TEN);
    float velocity = -1201.0f;
    EXPECT_EQ(pattern_->ComputeNextIndexByVelocity(velocity, false), 1);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_ELEVEN);
    velocity = -781.0f;
    EXPECT_EQ(pattern_->ComputeNextIndexByVelocity(velocity, false), 1);
    velocity = -780.0f;
    EXPECT_EQ(pattern_->ComputeNextIndexByVelocity(velocity, false), 0);
    pattern_->UpdateCurrentOffset(239.0f);
    FlushUITasks();
    EXPECT_EQ(pattern_->ComputeNextIndexByVelocity(velocity, true), 0);
    velocity = -781.0f;
    EXPECT_EQ(pattern_->ComputeNextIndexByVelocity(velocity, false), 1);
    ChangeIndex(0, false);
    pattern_->UpdateCurrentOffset(-241.0f);
    FlushUITasks();
    EXPECT_EQ(pattern_->ComputeNextIndexByVelocity(velocity, true), 1);
    velocity = -780.0f;
    EXPECT_EQ(pattern_->ComputeNextIndexByVelocity(velocity, false), 1);
}

/**
 * @tc.name: SwiperPatternInitSurfaceChangedCallback001
 * @tc.desc: InitSurfaceChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitSurfaceChangedCallback001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);
    auto leftArrowNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrowNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });

    /**
     * @tc.steps: step2. call InitSurfaceChangedCallback and then callback.
     * @tc.expected: Related function is called.
     */
    auto pipeline = frameNode_->GetContextRefPtr();
    pattern_->surfaceChangedCallbackId_.emplace(1);
    pattern_->InitSurfaceChangedCallback();
    pipeline->callbackId_ = 0;
    pattern_->surfaceChangedCallbackId_.reset();
    EXPECT_FALSE(pattern_->HasSurfaceChangedCallback());
    pipeline->surfaceChangedCallbackMap_.clear();
    pattern_->InitSurfaceChangedCallback();
    auto callbackmapnumber = pipeline->callbackId_;
    EXPECT_EQ(callbackmapnumber, 1);
    auto testFunction = pipeline->surfaceChangedCallbackMap_[1];
    testFunction(1, 1, 1, 1, WindowSizeChangeReason::CUSTOM_ANIMATION);
    auto callbacknumber = pattern_->surfaceChangedCallbackId_;
    EXPECT_EQ(callbacknumber, 1);

    /**
     * @tc.steps: step3. call InitSurfaceChangedCallback and then callback in different conditions.
     * @tc.expected: Related function is called.
     */
    pipeline->callbackId_ = 0;
    pattern_->surfaceChangedCallbackId_.reset();
    EXPECT_FALSE(pattern_->HasSurfaceChangedCallback());
    pipeline->surfaceChangedCallbackMap_.clear();
    pattern_->InitSurfaceChangedCallback();
    auto callbackmapnumber2 = pipeline->callbackId_;
    EXPECT_EQ(callbackmapnumber2, 1);
    auto testFunction2 = pipeline->surfaceChangedCallbackMap_[1];
    testFunction2(1, 1, 1, 1, WindowSizeChangeReason::UNDEFINED);
    EXPECT_EQ(pattern_->surfaceChangedCallbackId_, 1);
    testFunction2(1, 1, 1, 1, WindowSizeChangeReason::ROTATION);
    EXPECT_EQ(pattern_->windowSizeChangeReason_, WindowSizeChangeReason::ROTATION);

    auto childswiperNode1 = FrameNode::CreateFrameNode("childswiper", 1, AceType::MakeRefPtr<SwiperPattern>(), false);
    childswiperNode1->MountToParent(frameNode_);
    auto childswiperNode2 =
        FrameNode::CreateFrameNode(V2::JS_LAZY_FOR_EACH_ETS_TAG, 2, AceType::MakeRefPtr<SwiperPattern>(), false);
    childswiperNode2->MountToParent(frameNode_);
    pipeline->callbackId_ = 0;
    pattern_->surfaceChangedCallbackId_.reset();
    EXPECT_FALSE(pattern_->HasSurfaceChangedCallback());
    pipeline->surfaceChangedCallbackMap_.clear();
    pattern_->InitSurfaceChangedCallback();
    auto callbackmapnumber3 = pipeline->callbackId_;
    EXPECT_EQ(callbackmapnumber3, 1);
    auto testFunction3 = pipeline->surfaceChangedCallbackMap_[1];
    testFunction3(1, 1, 1, 1, WindowSizeChangeReason::CUSTOM_ANIMATION);
    auto callbacknumber3 = pattern_->surfaceChangedCallbackId_;
    EXPECT_EQ(callbacknumber3, 1);
}

/**
 * @tc.name: CalculateGestureState001
 * @tc.desc: test Swiper indicator gesture state
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalculateGestureState001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_NONE;
    pattern_->CalculateGestureState(1.0f, 0.0f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_RELEASE_LEFT);

    pattern_->gestureState_ = GestureState::GESTURE_STATE_NONE;
    pattern_->CalculateGestureState(-1.0f, 0.0f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_RELEASE_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->turnPageRate_ = -1.0f;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_NONE;
    pattern_->CalculateGestureState(0.0f, -1.1f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 1;
    pattern_->turnPageRate_ = -1.0f;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_NONE;
    pattern_->CalculateGestureState(0.0f, -1.1f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->turnPageRate_ = -1.0f;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_NONE;
    pattern_->CalculateGestureState(0.0f, -0.9f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);
}

/**
 * @tc.name: CalculateGestureState002
 * @tc.desc: test Swiper indicator gesture state
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalculateGestureState002, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->CalculateGestureState(1.0f, 0.0f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_RELEASE_LEFT);

    pattern_->CalculateGestureState(-1.0f, 0.0f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_RELEASE_RIGHT);

    pattern_->isTouchDown_ = true;
    pattern_->currentFirstIndex_ = -1;
    pattern_->currentIndex_ = 0;
    pattern_->mainDeltaSum_ = 1.0f;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureState(0.0f, -1.1f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = -1;
    pattern_->currentIndex_ = 0;
    pattern_->CalculateGestureState(0.0f, -1.1f, 3);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->mainDeltaSum_ = -1.0f;
    pattern_->CalculateGestureState(0.0f, -1.1f, 3);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureState(0.0f, -1.1f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 1;
    pattern_->mainDeltaSum_ = 1.0f;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureState(0.0f, -0.9f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 1;
    pattern_->mainDeltaSum_ = 1.0f;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureState(0.0f, -0.9f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 3;
    pattern_->currentIndex_ = 3;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureState(0.0f, -0.9f, 3);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);
}

/**
 * @tc.name: CalculateGestureState003
 * @tc.desc: test Swiper indicator gesture state when displayCount > 1
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalculateGestureState003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems(6);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 6);

    pattern_->isTouchDown_ = true;
    pattern_->currentFirstIndex_ = -1;
    pattern_->currentIndex_ = 0;
    pattern_->mainDeltaSum_ = 1.0f;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureState(0.0f, -1.1f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = -1;
    pattern_->currentIndex_ = 0;
    pattern_->CalculateGestureState(0.0f, -1.1f, 5);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->mainDeltaSum_ = -1.0f;
    pattern_->CalculateGestureState(0.0f, -1.1f, 5);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureState(0.0f, -1.1f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 2;
    pattern_->mainDeltaSum_ = 1.0f;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureState(0.0f, -0.9f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 1;
    pattern_->mainDeltaSum_ = 1.0f;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureState(0.0f, -0.9f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 5;
    pattern_->currentIndex_ = 5;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureState(0.0f, -0.9f, 5);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);
}

/**
 * @tc.name: CalculateGestureState004
 * @tc.desc: test Swiper indicator gesture state when loop = false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalculateGestureState004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->mainDeltaSum_ = 1.0f;
    pattern_->CalculateGestureState(0.0f, -1.1f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 3;
    pattern_->currentIndex_ = 3;
    pattern_->mainDeltaSum_ = -1.0f;
    pattern_->CalculateGestureState(0.0f, -1.1f, 3);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);
}

/**
 * @tc.name: CalculateGestureStateOnRTL001
 * @tc.desc: test Swiper indicator gesture state on RTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalculateGestureStateOnRTL001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);

    pattern_->CalculateGestureStateOnRTL(1.0f, 0.0f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_RELEASE_LEFT);

    pattern_->CalculateGestureStateOnRTL(-1.0f, 0.0f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_RELEASE_RIGHT);

    pattern_->isTouchDown_ = true;
    pattern_->currentFirstIndex_ = -1;
    pattern_->currentIndex_ = 0;
    pattern_->mainDeltaSum_ = 1.0f;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureStateOnRTL(0.0f, -1.1f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);
    pattern_->CalculateGestureStateOnRTL(0.0f, -1.1f, 3);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->mainDeltaSum_ = -1.0f;
    pattern_->CalculateGestureStateOnRTL(0.0f, -1.1f, 3);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureStateOnRTL(0.0f, -1.1f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 1;
    pattern_->mainDeltaSum_ = -1.0f;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureStateOnRTL(0.0f, -0.9f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureStateOnRTL(0.0f, -0.9f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);

    pattern_->currentFirstIndex_ = 3;
    pattern_->currentIndex_ = 3;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureStateOnRTL(0.0f, -0.9f, 3);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);
}

/**
 * @tc.name: CalculateGestureStateOnRTL002
 * @tc.desc: test Swiper indicator gesture state on RTL and displayCount > 1
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalculateGestureStateOnRTL002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems(6);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 6);

    pattern_->isTouchDown_ = true;
    pattern_->currentFirstIndex_ = -1;
    pattern_->currentIndex_ = 0;
    pattern_->mainDeltaSum_ = -1.0f;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureStateOnRTL(0.0f, -1.1f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);
    pattern_->CalculateGestureStateOnRTL(0.0f, -1.1f, 5);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->mainDeltaSum_ = 1.0f;
    pattern_->CalculateGestureStateOnRTL(0.0f, -1.1f, 5);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);
    pattern_->CalculateGestureStateOnRTL(0.0f, -1.1f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 2;
    pattern_->mainDeltaSum_ = -1.0f;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureStateOnRTL(0.0f, -0.9f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 1;
    pattern_->mainDeltaSum_ = -1.0f;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureStateOnRTL(0.0f, -0.9f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);

    pattern_->currentFirstIndex_ = 5;
    pattern_->currentIndex_ = 5;
    pattern_->needTurn_ = false;
    pattern_->CalculateGestureStateOnRTL(0.0f, -0.9f, 5);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);
}

/**
 * @tc.name: CalculateGestureStateOnRTL003
 * @tc.desc: test Swiper indicator gesture state on RTL and loop = false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalculateGestureStateOnRTL003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->mainDeltaSum_ = -1.0f;
    pattern_->CalculateGestureStateOnRTL(0.0f, -1.1f, 0);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 3;
    pattern_->currentIndex_ = 3;
    pattern_->mainDeltaSum_ = 1.0f;
    pattern_->CalculateGestureStateOnRTL(0.0f, -1.1f, 3);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);
}

/**
 * @tc.name: HandleTouchBottomLoop001
 * @tc.desc: test Swiper indicator touch bottom loop state
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, HandleTouchBottomLoop001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);

    pattern_->currentFirstIndex_ = 3;
    pattern_->currentIndex_ = 3;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: HandleTouchBottomLoop002
 * @tc.desc: test Swiper indicator touch bottom loop state
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, HandleTouchBottomLoop002, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);

    pattern_->currentFirstIndex_ = -1;
    pattern_->currentIndex_ = 0;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
    pattern_->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);

    pattern_->currentFirstIndex_ = 4;
    pattern_->currentIndex_ = 3;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
}

/**
 * @tc.name: HandleTouchBottomLoopOnRTL001
 * @tc.desc: test Swiper indicator touch bottom loop state on RTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, HandleTouchBottomLoopOnRTL001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);

    pattern_->currentFirstIndex_ = 3;
    pattern_->currentIndex_ = 3;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: HandleTouchBottomLoopOnRTL002
 * @tc.desc: test Swiper indicator touch bottom loop state on RTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, HandleTouchBottomLoopOnRTL002, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);

    pattern_->currentFirstIndex_ = -1;
    pattern_->currentIndex_ = 0;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
    pattern_->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);

    pattern_->currentFirstIndex_ = 4;
    pattern_->currentIndex_ = 3;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    pattern_->HandleTouchBottomLoopOnRTL();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: CalcCurrentPageStatus001
 * @tc.desc: test turn page rate and current index for Swiper indicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalcCurrentPageStatus001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);

    auto turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    auto currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, 0.0f);
    EXPECT_EQ(currentFirstIndex, 0);

    pattern_->UpdateCurrentOffset(240.0f);
    FlushUITasks();
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.5f);
    EXPECT_EQ(currentFirstIndex, -1);

    pattern_->UpdateCurrentOffset(120.0f);
    FlushUITasks();
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.25f);
    EXPECT_EQ(currentFirstIndex, -1);

    pattern_->ChangeIndex(3, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentFirstIndex_, 3);

    pattern_->UpdateCurrentOffset(-240.0f);
    FlushUITasks();
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.5f);
    EXPECT_EQ(currentFirstIndex, 3);

    pattern_->ChangeIndex(0, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentFirstIndex_, 0);

    pattern_->itemPosition_[-1] = { -480.0f, 0.0f };
    pattern_->itemPosition_[1] = { 480.0f, 960.0f };

    turnPageRate = pattern_->CalcCurrentPageStatus(-480.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(-480.0f).second;
    EXPECT_EQ(turnPageRate, 0.0f);
    EXPECT_EQ(currentFirstIndex, 1);

    turnPageRate = pattern_->CalcCurrentPageStatus(480.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(480.0f).second;
    EXPECT_EQ(turnPageRate, 0.0f);
    EXPECT_EQ(currentFirstIndex, -1);
}

/**
 * @tc.name: CalcCurrentPageStatus002
 * @tc.desc: test turn page rate and current index for Swiper indicator when displayCount > 1
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalcCurrentPageStatus002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems(6);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 6);

    auto turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    auto currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, 0.0f);
    EXPECT_EQ(currentFirstIndex, 0);

    pattern_->UpdateCurrentOffset(-120.0f);
    FlushUITasks();
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.5f);
    EXPECT_EQ(currentFirstIndex, 0);

    pattern_->UpdateCurrentOffset(-120.0f);
    FlushUITasks();
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, 0.0f);
    EXPECT_EQ(currentFirstIndex, 1);

    pattern_->UpdateCurrentOffset(-120.0f);
    FlushUITasks();
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.5f);
    EXPECT_EQ(currentFirstIndex, 1);

    pattern_->UpdateCurrentOffset(480.0f);
    FlushUITasks();
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.5f);
    EXPECT_EQ(currentFirstIndex, -1);

    pattern_->UpdateCurrentOffset(120.0f);
    FlushUITasks();
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, 0.0f);
    EXPECT_EQ(currentFirstIndex, -1);

    pattern_->ChangeIndex(5, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentFirstIndex_, 5);

    pattern_->itemPosition_[4] = { -240.0f, 0.0f };

    turnPageRate = pattern_->CalcCurrentPageStatus(-240.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(-240.0f).second;
    EXPECT_EQ(turnPageRate, 0.0f);
    EXPECT_EQ(currentFirstIndex, 6);

    turnPageRate = pattern_->CalcCurrentPageStatus(240.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(240.0f).second;
    EXPECT_EQ(turnPageRate, 0.0f);
    EXPECT_EQ(currentFirstIndex, 4);
}

/**
 * @tc.name: AdjustCurrentIndexOnSwipePage001
 * @tc.desc: Test SwiperPattern AdjustCurrentIndexOnSwipePage
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAdjustCurrentIndexOnSwipePage001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateDisplayCount(3);
    pattern_->needAdjustIndex_ = true;
    layoutProperty_->UpdateIndex(1);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(layoutProperty_->GetIndex().value(), 0);
    EXPECT_FALSE(pattern_->needAdjustIndex_);

    layoutProperty_->UpdateIndex(5);
    pattern_->needAdjustIndex_ = true;
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(layoutProperty_->GetIndex().value(), 3);

    layoutProperty_->UpdateIndex(6);
    pattern_->needAdjustIndex_ = true;
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(layoutProperty_->GetIndex().value(), 0);

    layoutProperty_->UpdateIndex(3);
    pattern_->needAdjustIndex_ = true;
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(layoutProperty_->GetIndex().value(), 3);

    layoutProperty_->UpdateDisplayCount(6);
    layoutProperty_->UpdateIndex(3);
    pattern_->needAdjustIndex_ = true;
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(layoutProperty_->GetIndex().value(), 0);

    layoutProperty_->UpdateDisplayCount(10);
    layoutProperty_->UpdateIndex(3);
    pattern_->needAdjustIndex_ = true;
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(layoutProperty_->GetIndex().value(), 0);
}

/**
 * @tc.name: ChangeItemsCount001
 * @tc.desc: Test Add/Remove swiper item, the currentIndex is correct
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ChangeItemsCount001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), ITEM_NUMBER);

    /**
     * @tc.steps: step1. Change index and add child
     * @tc.expected: The currentIndex would changed to be >= 0
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(3));

    AddSwiperItem(pattern_->TotalCount() - 1);
    EXPECT_EQ(pattern_->TotalCount(), ITEM_NUMBER + 1);
    EXPECT_TRUE(CurrentIndex(3));

    /**
     * @tc.steps: step2. Change index and remove child
     * @tc.expected: The currentIndex would changed to be 0
     */
    ShowNext();
    EXPECT_TRUE(CurrentIndex(4));
    ShowNext();
    EXPECT_TRUE(CurrentIndex(0));

    RemoveSwiperItem(0);
    EXPECT_EQ(pattern_->TotalCount(), ITEM_NUMBER);
    EXPECT_TRUE(CurrentIndex(0));
}

/**
 * @tc.name: ChangeItemsCount002
 * @tc.desc: Test Add/Remove swiper item when DIGIT
 * @tc.desc: The indicator text and currentIndex are correct
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ChangeItemsCount002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    model.SetDisplayCount(2);
    CreateSwiperItems(6);
    CreateSwiperDone();
    EXPECT_TRUE(DigitText(u"1/6"));

    /**
     * @tc.steps: step1. Change index and remove child
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(5));
    EXPECT_TRUE(DigitText(u"6/6"));

    RemoveSwiperItem(0);
    EXPECT_TRUE(CurrentIndex(0));
    EXPECT_TRUE(DigitText(u"1/5"));

    /**
     * @tc.steps: step2. Remove child again
     * @tc.expected: The currentIndex changed to be 0 because page not existed
     */
    RemoveSwiperItem(0);
    EXPECT_TRUE(CurrentIndex(0));
    EXPECT_TRUE(DigitText(u"1/4"));

    /**
     * @tc.steps: step3. Change index and add child
     * @tc.expected: The currentIndex would changed to be >= 0
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(3));
    EXPECT_TRUE(DigitText(u"4/4"));

    AddSwiperItem(pattern_->TotalCount() - 1);
    EXPECT_TRUE(CurrentIndex(3));
    EXPECT_TRUE(DigitText(u"4/5"));

    /**
     * @tc.steps: step4. Add child again
     * @tc.expected: The currentIndex would not changed
     */
    AddSwiperItem(pattern_->TotalCount() - 1);
    EXPECT_TRUE(CurrentIndex(3));
    EXPECT_TRUE(DigitText(u"4/6"));
}

/**
 * @tc.name: ChangeItemsCount003
 * @tc.desc: Test Add/Remove swiper item when DIGIT/SwipeByGroup
 * @tc.desc: The indicator text and currentIndex are correct
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ChangeItemsCount003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems(6);
    CreateSwiperDone();
    EXPECT_TRUE(DigitText(u"1/6"));

    /**
     * @tc.steps: step1. Change index and remove child
     * @tc.expected: The currentIndex would not changed because page existed
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(4));
    EXPECT_TRUE(DigitText(u"5/6"));

    RemoveSwiperItem(0);
    EXPECT_TRUE(CurrentIndex(4));
    EXPECT_TRUE(DigitText(u"5/5"));

    /**
     * @tc.steps: step2. Remove child again
     * @tc.expected: The currentIndex changed to be 0 because page not existed
     */
    RemoveSwiperItem(0);
    EXPECT_TRUE(CurrentIndex(0));
    EXPECT_TRUE(DigitText(u"1/4"));

    /**
     * @tc.steps: step3. Change index and add child
     * @tc.expected: The currentIndex would changed to be >= 0
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(2));
    EXPECT_TRUE(DigitText(u"3/4"));

    AddSwiperItem(pattern_->TotalCount() - 1);
    EXPECT_TRUE(CurrentIndex(2));
    EXPECT_TRUE(DigitText(u"3/5"));

    /**
     * @tc.steps: step4. Add child again
     * @tc.expected: The currentIndex would not changed
     */
    AddSwiperItem(pattern_->TotalCount() - 1);
    EXPECT_TRUE(CurrentIndex(2));
    EXPECT_TRUE(DigitText(u"3/6"));
}

/**
 * @tc.name: ComputeSwipePageNextIndex001
 * @tc.desc: Test SwiperPattern ComputeSwipePageNextIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternComputeSwipePageNextIndex001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdateLoop(true);
    pattern_->currentIndex_ = 3;
    float dragVelocity = 500.0f;
    pattern_->contentMainSize_ = 0.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);

    pattern_->contentMainSize_ = 500.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);

    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -200.0f;
    swiperItemInfo1.endPos = 0.0f;
    pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo1));
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = 0.0f;
    swiperItemInfo2.endPos = 200.0f;
    pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo2));
    struct SwiperItemInfo swiperItemInfo3;
    swiperItemInfo3.startPos = 200.0f;
    swiperItemInfo3.endPos = 400.0f;
    pattern_->itemPosition_.emplace(std::make_pair(5, swiperItemInfo3));
    pattern_->contentMainSize_ = 600.0f;
    dragVelocity = -500.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);

    dragVelocity = -781.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);

    pattern_->itemPosition_.clear();
    swiperItemInfo1.startPos = -301.0f;
    swiperItemInfo1.endPos = -101.0f;
    pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo1));
    swiperItemInfo2.startPos = -101.0f;
    swiperItemInfo2.endPos = 99.0f;
    pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo2));
    swiperItemInfo3.startPos = 99.0f;
    swiperItemInfo3.endPos = 299.0f;
    pattern_->itemPosition_.emplace(std::make_pair(5, swiperItemInfo3));
    dragVelocity = -500.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 6);

    dragVelocity = -781.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 6);

    pattern_->itemPosition_.clear();
    swiperItemInfo1.startPos = -200.0f;
    swiperItemInfo1.endPos = 0.0f;
    pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo1));
    swiperItemInfo2.startPos = 0.0f;
    swiperItemInfo2.endPos = 200.0f;
    pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo2));
    swiperItemInfo3.startPos = 200.0f;
    swiperItemInfo3.endPos = 400.0f;
    pattern_->itemPosition_.emplace(std::make_pair(5, swiperItemInfo3));
    dragVelocity = -781.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 6);

    layoutProperty_->UpdateLoop(false);
    pattern_->currentIndex_ = 0;
    dragVelocity = 500.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);

    pattern_->currentIndex_ = 3;
    dragVelocity = -500.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);
}

void SwiperTestNg::InitCaptureTest()
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(CAPTURE_MARGIN_SIZE));
    layoutProperty_->UpdateNextMargin(Dimension(CAPTURE_MARGIN_SIZE));
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->hasCachedCapture_);
}

/**
 * @tc.name: SwipeInitCapture001
 * @tc.desc: Test SwiperPattern InitCapture
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwipeInitCapture001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper witch need the capture
     */
    InitCaptureTest();
    EXPECT_TRUE(pattern_->leftCaptureId_.has_value());
    EXPECT_TRUE(pattern_->rightCaptureId_.has_value());

    layoutProperty_->UpdatePrevMargin(Dimension(0));
    layoutProperty_->UpdateNextMargin(Dimension(CAPTURE_MARGIN_SIZE));
    EXPECT_TRUE(pattern_->hasCachedCapture_);

    layoutProperty_->UpdatePrevMargin(Dimension(CAPTURE_MARGIN_SIZE));
    layoutProperty_->UpdateNextMargin(Dimension(0));
    EXPECT_TRUE(pattern_->hasCachedCapture_);
    /**
     * @tc.steps: step2. Create swiper witch does not need the capture
     */
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    layoutProperty_->ResetDisplayCount();
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->hasCachedCapture_);
    EXPECT_FALSE(pattern_->leftCaptureId_.has_value());
    EXPECT_FALSE(pattern_->rightCaptureId_.has_value());

    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdateLoop(false);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->hasCachedCapture_);

    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(4);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->hasCachedCapture_);

    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(0));
    layoutProperty_->UpdateNextMargin(Dimension(0));
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->hasCachedCapture_);
}

/**
 * @tc.name: SwipeCaptureLayoutInfo001
 * @tc.desc: Test check measure and layout info
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwipeCaptureLayoutInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper witch need the capture
     */
    InitCaptureTest();
    /**
     * @tc.steps: step2. check layout info with Axis::VERTICAL
     */
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    pattern_->OnModifyDone();
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(pattern_->leftCaptureIndex_, 3);
    auto leftCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetLeftCaptureId())));
    EXPECT_NE(leftCaptureNode, nullptr);
    if (leftCaptureNode) {
        auto size = leftCaptureNode->GetGeometryNode()->GetFrameRect();
        EXPECT_EQ(size.Width(), SWIPER_WIDTH);
        EXPECT_EQ(size.Height(), (SWIPER_HEIGHT - CAPTURE_MARGIN_SIZE * 2) / 3);
        auto offset = leftCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), 0.0f);
        EXPECT_EQ(offset.GetY(), CAPTURE_MARGIN_SIZE - size.Height());
    }
    /**
     * @tc.steps: step3. check layout info with Axis::HORIZONTAL
     * 3'|3' 0 1 2 3|3
     */
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(pattern_->leftCaptureIndex_, 3);
    leftCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetLeftCaptureId())));
    EXPECT_NE(leftCaptureNode, nullptr);
    float itemWidth = 0.0f;
    if (leftCaptureNode) {
        auto size = leftCaptureNode->GetGeometryNode()->GetFrameRect();
        EXPECT_EQ(size.Width(), (SWIPER_WIDTH - CAPTURE_MARGIN_SIZE * 2) / 3);
        EXPECT_EQ(size.Height(), SWIPER_HEIGHT);
        itemWidth = size.Width();
        auto offset = leftCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), CAPTURE_MARGIN_SIZE - size.Width());
        EXPECT_EQ(offset.GetY(), 0.0f);
    }

    /**
     * @tc.steps: step4. capture in left, delta swipe to right
     * 3'|3' 0 1 2 3|3 to 2'|2' 3 0 1 2|2
     */
    pattern_->currentDelta_ = -itemWidth;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(pattern_->leftCaptureIndex_, 2);
    leftCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetLeftCaptureId())));
    EXPECT_NE(leftCaptureNode, nullptr);
    if (leftCaptureNode) {
        auto size = leftCaptureNode->GetGeometryNode()->GetFrameRect();
        auto offset = leftCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), CAPTURE_MARGIN_SIZE - size.Width());
    }

    /**
     * @tc.steps: step5. capture in left, delta swipe to left
     * 2'|2' 3 0 1 2|2 to 3|3 0 1 2 3'|3'
     */
    pattern_->currentDelta_ = itemWidth;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(pattern_->rightCaptureIndex_, 3);
    auto rightCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetRightCaptureId())));
    EXPECT_NE(rightCaptureNode, nullptr);
    if (rightCaptureNode) {
        auto size = rightCaptureNode->GetGeometryNode()->GetFrameRect();
        EXPECT_EQ(size.Width(), (SWIPER_WIDTH - CAPTURE_MARGIN_SIZE * 2) / 3);
        EXPECT_EQ(size.Height(), SWIPER_HEIGHT);
        auto offset = rightCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), SWIPER_WIDTH - CAPTURE_MARGIN_SIZE);
        EXPECT_EQ(offset.GetY(), 0.0f);
    }

    /**
     * @tc.steps: step6. capture in right, delta swipe to left
     * 3|3 0 1 2 3'|3' to 0|0 1 2 3 0'|0'
     */
    pattern_->currentDelta_ = itemWidth;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(pattern_->rightCaptureIndex_, 0);
    rightCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetRightCaptureId())));
    EXPECT_NE(rightCaptureNode, nullptr);
    if (rightCaptureNode) {
        auto offset = rightCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), SWIPER_WIDTH - CAPTURE_MARGIN_SIZE);
    }

    /**
     * @tc.steps: step7. capture in right, delta swipe to right
     * 0|0 1 2 3 0'|0' to 3'|3' 0 1 2 3|3
     */
    pattern_->currentDelta_ = -itemWidth;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(pattern_->leftCaptureIndex_, 3);
    leftCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetLeftCaptureId())));
    EXPECT_NE(leftCaptureNode, nullptr);
    if (leftCaptureNode) {
        auto size = leftCaptureNode->GetGeometryNode()->GetFrameRect();
        auto offset = leftCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), CAPTURE_MARGIN_SIZE - size.Width());
    }
}

/**
 * @tc.name: SwiperSetFrameRateTest001
 * @tc.desc: Test SetFrameRate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperSetFrameRateTest001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    int32_t expectedRate = 60;
    auto frameRateRange = AceType::MakeRefPtr<FrameRateRange>(0, 120, expectedRate);
    pattern_->SetFrameRateRange(frameRateRange, SwiperDynamicSyncSceneType::GESTURE);
    auto frameRateManager = MockPipelineContext::GetCurrentContext()->GetFrameRateManager();
    int32_t nodeId = frameNode_->GetId();
    frameRateManager->AddNodeRate(nodeId, 1);
    frameRateManager->isRateChanged_ = false;
    pattern_->UpdateNodeRate();
    auto iter = frameRateManager->nodeRateMap_.find(nodeId);
    EXPECT_EQ(iter->second, expectedRate);
    EXPECT_TRUE(frameRateManager->isRateChanged_);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ToJsonValue001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("nestedScroll"), "SwiperNestedScrollMode.SELF_ONLY");
    EXPECT_EQ(json->GetInt("currentIndex"), 0);
    EXPECT_EQ(json->GetDouble("currentOffset"), 0);
    EXPECT_EQ(json->GetInt("uiCastJumpIndex"), -1);
    EXPECT_EQ(json->GetString("indicator"), "");

    pattern_->indicatorIsBoolean_ = false;
    pattern_->ToJsonValue(json, filter);
    EXPECT_NE(json->GetString("indicator"), "");
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    pattern_->ToJsonValue(json, filter);
    EXPECT_NE(json->GetString("indicator"), "");

    json->Replace("uiCastJumpIndex", -1);
    pattern_->FromJson(json);
    EXPECT_FALSE(pattern_->jumpIndex_.has_value());
    json->Replace("uiCastJumpIndex", 2);
    pattern_->FromJson(json);
    EXPECT_EQ(pattern_->jumpIndex_, 2);
    json->Replace("currentOffset", -100.0f);
    pattern_->FromJson(json);
    EXPECT_EQ(pattern_->currentDelta_, 100.0f);
}

/**
+ * @tc.name: WearableSwiperOnModifyDone001
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, WearableSwiperOnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<SwiperPattern> indicatorPattern = frameNode_->GetPattern<SwiperPattern>();
    EXPECT_NE(indicatorPattern, nullptr);
    indicatorPattern->GetArcDotIndicatorStyle();

    /**
     * @tc.steps: step2. call UpdateContentModifier.
     */
    indicatorPattern->OnModifyDone();
    indicatorPattern->swiperController_->removeSwiperEventCallback_();
    indicatorPattern->swiperController_->addSwiperEventCallback_();
    indicatorPattern->OnAfterModifyDone();
    EXPECT_EQ(indicatorPattern->lastSwiperIndicatorType_, SwiperIndicatorType::ARC_DOT);
}

/**
+ * @tc.name: SwiperPattern_OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPattern_OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto swiperPaintProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    RefPtr<LayoutWrapper> dirty = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, swiperPaintProperty);
    DirtySwapConfig config;
    auto result = swiperPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(result);
}

/**
+ * @tc.name: SwiperPattern_OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPattern_OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto swiperPaintProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    RefPtr<LayoutWrapper> dirty = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, swiperPaintProperty);
    DirtySwapConfig config;
    config.skipLayout = true;
    config.skipMeasure = true;
    auto result = swiperPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(result);
}

/**
+ * @tc.name: SwiperPattern_OnDirtyLayoutWrapperSwap003
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPattern_OnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->isInit_ = false;
    swiperPattern->currentIndex_ = 2;
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto swiperPaintProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    RefPtr<LayoutWrapper> dirty = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, swiperPaintProperty);
    DirtySwapConfig config;
    config.skipLayout = true;
    config.skipMeasure = true;
    swiperPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_EQ(swiperPattern->oldIndex_, 2);
}

/**
 * @tc.name: OnModifyDone_StopAndResetSpringAnimation
 * @tc.desc: Test SwiperPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, OnModifyDone_StopAndResetSpringAnimation, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->nodeId_ = 2;
    RefPtr<SwiperEventHub> swiperEventHub = AceType::MakeRefPtr<SwiperEventHub>();
    WeakPtr<EventHub> eventHub = swiperEventHub;
    RefPtr<GestureEventHub> gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    swiperEventHub->gestureEventHub_ = gestureEventHub;
    frameNode->eventHub_ = swiperEventHub;
    swiperLayoutProperty->propIndex_ = 2;
    frameNode->layoutProperty_ = swiperLayoutProperty;
    swiperPattern->frameNode_ = frameNode;
    swiperPattern->currentIndex_ = 3;
    swiperPattern->isTouchDownSpringAnimation_ = false;
    swiperPattern->springAnimationIsRunning_ = true;
    swiperPattern->isBindIndicator_ = true;
    swiperPattern->currentDelta_ = 2.0f;
    swiperPattern->OnModifyDone();
    EXPECT_EQ(swiperPattern->currentDelta_, 0.0f);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap_GetJumpIndex
 * @tc.desc: Test SwiperPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, OnDirtyLayoutWrapperSwap_GetJumpIndex, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    RefPtr<SwiperPaintProperty> swiperPaintProperty = AceType::MakeRefPtr<SwiperPaintProperty>();
    RefPtr<SwiperLayoutAlgorithm> swiperLayoutAlgorithm = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    swiperLayoutAlgorithm->jumpIndex_ = 3;
    swiperPaintProperty->UpdateAutoPlay(true);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.clear();
    frameNode->layoutProperty_ = swiperLayoutProperty;
    frameNode->paintProperty_ = swiperPaintProperty;
    swiperPattern->frameNode_ = frameNode;
    RefPtr<SwiperIndicatorLayoutProperty> swiperIndicatorLayoutProperty =
        AceType::MakeRefPtr<SwiperIndicatorLayoutProperty>();
    swiperPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, swiperLayoutProperty);
    layoutWrapper->hostNode_ = frameNode;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm);
    layoutAlgorithmWrapper->layoutAlgorithm_ = swiperLayoutAlgorithm;
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;
    SwiperItemInfo itemInfo;
    itemInfo.startPos = 2.0f;
    itemInfo.endPos = 8.0f;
    swiperPattern->itemPosition_.clear();
    swiperPattern->itemPosition_[0] = itemInfo;
    DirtySwapConfig config;
    config.skipLayout = false;
    config.skipMeasure = false;
    swiperPattern->isDragging_ = true;
    swiperPattern->isInit_ = false;
    swiperPattern->isUserFinish_ = false;
    swiperPattern->currentIndex_ = 3;
    swiperPattern->targetIndex_.reset();
    swiperPattern->jumpIndex_.reset();
    swiperPattern->currentIndexOffset_ = 2.0f;
    swiperPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(swiperPattern->currentIndexOffset_, 0.0f);
}

/**
 * @tc.name: OnInjectionEventTest001
 * @tc.desc: test OnInjectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, OnInjectionEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    int32_t currentIndex = 3;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (swiperInfo != nullptr) {
            currentIndex = swiperInfo->GetIndex();
        }
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnChange(std::move(onChange));
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    std::string command = R"({"cmd":"changeIndex","params":{"index":2}})";
    pattern->OnInjectionEvent(command);
    EXPECT_EQ(currentIndex, 2);
    command = R"({"cmd":"changeIndex","params":{"index":100}})";
    pattern->OnInjectionEvent(command);
    EXPECT_EQ(currentIndex, 0);
    command = R"({"cmd":"changeIndex","params":{"index":-10}})";
    EXPECT_EQ(currentIndex, 0);
    pattern->OnInjectionEvent(command);
}

/**
 * @tc.name: SwipeAutoLinearIsOutOfBoundary001
 * @tc.desc: Test SwiperPattern AutoLinearIsOutOfBoundary test
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwipeAutoLinearIsOutOfBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with SwiperDisplayMode::AUTO_LINEAR
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    model.SetLoop(false);
    CreateItemWithSize(SWIPER_WIDTH, SWIPER_HEIGHT);
    CreateSwiperDone();
    EXPECT_FALSE(pattern_->itemPosition_.empty());
    EXPECT_FALSE(pattern_->itemPosition_.size() < pattern_->TotalCount());
    EXPECT_FALSE(pattern_->AutoLinearIsOutOfBoundary(0.f));
}

/**
+ * @tc.name: BuildAxisInfo001
 * @tc.desc: Test BuildAxisInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildAxisInfo001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->direction_ = Axis::NONE;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildAxisInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "NONE");
}

/**
+ * @tc.name: BuildAxisInfo002
 * @tc.desc: Test BuildAxisInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildAxisInfo002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->direction_ = Axis::HORIZONTAL;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildAxisInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "HORIZONTAL");
}

/**
+ * @tc.name: BuildAxisInfo003
 * @tc.desc: Test BuildAxisInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildAxisInfo003, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->direction_ = Axis::FREE;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildAxisInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "FREE");
}

/**
+ * @tc.name: BuildAxisInfo004
 * @tc.desc: Test BuildAxisInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildAxisInfo004, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->direction_ = Axis::VERTICAL;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildAxisInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "VERTICAL");
}

/**
+ * @tc.name: BuildAxisInfo005
 * @tc.desc: Test BuildAxisInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildAxisInfo005, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto direct = 5;
    swiperPattern->direction_ = (Axis)direct;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildAxisInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "");
}

/**
+ * @tc.name: BuildItemPositionInfo001
 * @tc.desc: Test BuildItemPositionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildItemPositionInfo001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, swiperPattern);
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, swiperPattern);
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    swiperPattern->itemPosition_ = itemPosition;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildItemPositionInfo(json);
    EXPECT_TRUE(json->GetValue("itemPosition"));
}

/**
+ * @tc.name: BuildItemPositionInfo002
 * @tc.desc: Test BuildItemPositionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildItemPositionInfo002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    swiperPattern->itemPosition_ = itemPosition;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildItemPositionInfo(json);
    EXPECT_EQ(json->GetString("itemPosition"), "");
}

/**
+ * @tc.name: BuildItemPositionInfo003
 * @tc.desc: Test BuildItemPositionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildItemPositionInfo003, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPositionInAnimation;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPositionInAnimation.insert(std::make_pair(0, item1));
    itemPositionInAnimation.insert(std::make_pair(1, item2));
    swiperPattern->itemPositionInAnimation_ = itemPositionInAnimation;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildItemPositionInfo(json);
    EXPECT_TRUE(json->GetValue("itemPositionInAnimation"));
}

/**
+ * @tc.name: BuildItemPositionInfo004
 * @tc.desc: Test BuildItemPositionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildItemPositionInfo004, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPositionInAnimation;
    swiperPattern->itemPositionInAnimation_ = itemPositionInAnimation;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildAxisInfo(json);
    EXPECT_EQ(json->GetString("itemPositionInAnimation"), "");
}

/**
+ * @tc.name: BuildIndicatorTypeInfo001
 * @tc.desc: Test BuildIndicatorTypeInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildIndicatorTypeInfo001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->lastSwiperIndicatorType_ = SwiperIndicatorType::DOT;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildIndicatorTypeInfo(json);
    EXPECT_EQ(json->GetString("SwiperIndicatorType"), "DOT");
}

/**
+ * @tc.name: BuildIndicatorTypeInfo002
 * @tc.desc: Test BuildIndicatorTypeInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildIndicatorTypeInfo002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->lastSwiperIndicatorType_ = SwiperIndicatorType::DIGIT;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildIndicatorTypeInfo(json);
    EXPECT_EQ(json->GetString("SwiperIndicatorType"), "DIGIT");
}

/**
+ * @tc.name: BuildIndicatorTypeInfo003
 * @tc.desc: Test BuildIndicatorTypeInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildIndicatorTypeInfo003, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto lastSwiperIndicatorType = 5;
    swiperPattern->lastSwiperIndicatorType_ = (SwiperIndicatorType)lastSwiperIndicatorType;
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildIndicatorTypeInfo(json);
    EXPECT_EQ(json->GetString("SwiperIndicatorType"), "");
}

/**
+ * @tc.name: BuildIndicatorTypeInfo004
 * @tc.desc: Test BuildIndicatorTypeInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildIndicatorTypeInfo004, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto json = JsonUtil::Create(true);
    swiperPattern->BuildIndicatorTypeInfo(json);
    EXPECT_EQ(json->GetString("lastSwiperIndicatorType"), "null");
}

/**
 * @tc.name: BuildPanDirectionInfo001
 * @tc.desc: Test BuildPanDirectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildPanDirectionInfo001, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto json = JsonUtil::Create(true);
    swiperPattern->panDirection_.type = PanDirection::NONE;
    swiperPattern->BuildPanDirectionInfo(json);
    EXPECT_EQ(json->GetString("PanDirection"), "NONE");
}

/**
 * @tc.name: BuildPanDirectionInfo002
 * @tc.desc: Test BuildPanDirectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildPanDirectionInfo002, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto json = JsonUtil::Create(true);
    swiperPattern->panDirection_.type = PanDirection::LEFT;
    swiperPattern->BuildPanDirectionInfo(json);
    EXPECT_EQ(json->GetString("PanDirection"), "LEFT");
}

/**
 * @tc.name: BuildPanDirectionInfo003
 * @tc.desc: Test BuildPanDirectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildPanDirectionInfo003, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto json = JsonUtil::Create(true);
    swiperPattern->panDirection_.type = PanDirection::RIGHT;
    swiperPattern->BuildPanDirectionInfo(json);
    EXPECT_EQ(json->GetString("PanDirection"), "RIGHT");
}

/**
 * @tc.name: BuildPanDirectionInfo004
 * @tc.desc: Test BuildPanDirectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildPanDirectionInfo004, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto json = JsonUtil::Create(true);
    swiperPattern->panDirection_.type = PanDirection::HORIZONTAL;
    swiperPattern->BuildPanDirectionInfo(json);
    EXPECT_EQ(json->GetString("PanDirection"), "HORIZONTAL");
}

/**
 * @tc.name: BuildPanDirectionInfo005
 * @tc.desc: Test BuildPanDirectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildPanDirectionInfo005, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto json = JsonUtil::Create(true);
    swiperPattern->panDirection_.type = PanDirection::UP;
    swiperPattern->BuildPanDirectionInfo(json);
    EXPECT_EQ(json->GetString("PanDirection"), "UP");
}

/**
 * @tc.name: BuildPanDirectionInfo006
 * @tc.desc: Test BuildPanDirectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildPanDirectionInfo006, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto json = JsonUtil::Create(true);
    swiperPattern->panDirection_.type = PanDirection::DOWN;
    swiperPattern->BuildPanDirectionInfo(json);
    EXPECT_EQ(json->GetString("PanDirection"), "DOWN");
}

/**
 * @tc.name: BuildPanDirectionInfo007
 * @tc.desc: Test BuildPanDirectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildPanDirectionInfo007, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto json = JsonUtil::Create(true);
    swiperPattern->panDirection_.type = PanDirection::VERTICAL;
    swiperPattern->BuildPanDirectionInfo(json);
    EXPECT_EQ(json->GetString("PanDirection"), "VERTICAL");
}

/**
 * @tc.name: BuildPanDirectionInfo008
 * @tc.desc: Test BuildPanDirectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildPanDirectionInfo008, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto json = JsonUtil::Create(true);
    swiperPattern->panDirection_.type = PanDirection::ALL;
    swiperPattern->BuildPanDirectionInfo(json);
    EXPECT_EQ(json->GetString("PanDirection"), "ALL");
}

/**
 * @tc.name: BuildPanDirectionInfo009
 * @tc.desc: Test BuildPanDirectionInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, BuildPanDirectionInfo009, TestSize.Level1)
{
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto json = JsonUtil::Create(true);
    uint32_t type = 10;
    swiperPattern->panDirection_.type = type;
    swiperPattern->BuildPanDirectionInfo(json);
    EXPECT_EQ(json->GetString("PanDirection"), "");
}

/**
 * @tc.name: CustomAnimationHandleDragEnd001
 * @tc.desc: Test SwiperPattern HandleDragEnd on custom animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CustomAnimationHandleDragEnd001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperContentAnimatedTransition transitionInfo;
    transitionInfo.timeout = 0;
    transitionInfo.transition = [](const RefPtr<SwiperContentTransitionProxy>& proxy) {};
    model.SetCustomContentTransition(transitionInfo);
    auto onContentDidScroll = [](int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {};
    model.SetOnContentDidScroll(std::move(onContentDidScroll));
    CreateSwiperItems();
    CreateSwiperDone();
    pattern_->contentMainSize_ = SWIPER_WIDTH;
    EXPECT_TRUE(pattern_->SupportSwiperCustomAnimation());

    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::TOUCHPAD);
    info.SetGlobalLocation(Offset(100.f, 100.f));
    info.SetMainDelta(100.0f);
    info.SetMainVelocity(2000.f);

    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_FALSE(pattern_->itemPosition_.empty());
    auto offset = pattern_->itemPosition_[0].startPos;
    EXPECT_EQ(offset, 100.0f);

    pattern_->HandleDragEnd(2000.f, 0.0f);
    FlushUITasks();
    EXPECT_FALSE(pattern_->itemPosition_.empty());

    offset = pattern_->itemPosition_[0].startPos;
    EXPECT_EQ(offset, 100.0f);
}

/**
 * @tc.name: CheckTargetPositon001
 * @tc.desc: Test SwiperPattern CheckTargetPositon
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CheckTargetPositon001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    /**
     * @tc.steps: step2. Change contentMainSize_ to a value different from contentMainSizeBeforeAni_
     */
    pattern_->contentMainSizeBeforeAni_ = pattern_->contentMainSize_ * 2;
    pattern_->targetIndex_ = 1;
    float offset = 0.f;
    /**
     * @tc.steps: step3. The offset will be adjusted
     */
    pattern_->CheckTargetPositon(offset);
    EXPECT_EQ(offset, -pattern_->itemPosition_[1].startPos);
}
} // namespace OHOS::Ace::NG
