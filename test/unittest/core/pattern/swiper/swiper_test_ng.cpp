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

#include "swiper_test_ng.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/button/button_theme.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"

namespace OHOS::Ace::NG {
void SwiperTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
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
    eventHub_ = frameNode_->GetEventHub<SwiperEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    controller_ = pattern_->GetSwiperController();
}

RefPtr<PaintWrapper> SwiperTestNg::CreateSwiperDone()
{
    auto paintWrapper = CreateDone();
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
    return paintWrapper;
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

void SwiperTestNg::CreateDefaultSwiper()
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    FlushLayoutTask(frameNode_);
}

void SwiperTestNg::ShowPrevious()
{
    controller_->ShowPrevious();
    FlushLayoutTask(frameNode_);
}

void SwiperTestNg::ChangeIndex(int32_t index)
{
    controller_->ChangeIndex(index, false);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    CreateWithArrow();
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = true;
    config.skipLayout = true;

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
            pattern_->isInit_ = false;
            if (i == 1) {
                config.skipLayout = false;
                continue;
            }
            config.skipLayout = true;
        }
        config.skipMeasure = false;
    }
    struct SwiperItemInfo swiperItemInfo1;
    struct SwiperItemInfo swiperItemInfo2;
    struct SwiperItemInfo swiperItemInfo3;
    struct SwiperItemInfo swiperItemInfo4;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo2.startPos = 1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo3.startPos = -1.0f;
    swiperItemInfo3.endPos = 0.0f;
    swiperItemInfo4.startPos = 1.0f;
    swiperItemInfo4.endPos = 1.0f;

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    dirty->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm);
    dirty->layoutAlgorithm_->layoutAlgorithm_ = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    ASSERT_NE(dirty->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm()), nullptr);
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(3, swiperItemInfo3));
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(4, swiperItemInfo4));
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    pattern_->indicatorDoingAnimation_ = false;
    pattern_->jumpIndex_ = 1;

    for (int i = 0; i <= 1; i++) {
        pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
        pattern_->indicatorDoingAnimation_ = true;
        pattern_->targetIndex_ = 1;
        AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
            ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    }

    AceType::DynamicCast<SwiperPaintProperty>(frameNode_->paintProperty_)->UpdateEdgeEffect(EdgeEffect::SPRING);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
            if (i == 1) {
                AceType::DynamicCast<SwiperPaintProperty>(frameNode_->paintProperty_)
                    ->UpdateEdgeEffect(EdgeEffect::FADE);
                continue;
            }
            AceType::DynamicCast<SwiperPaintProperty>(frameNode_->paintProperty_)->UpdateEdgeEffect(EdgeEffect::SPRING);
        }
        AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->layoutProperty_)->padding_ =
            std::make_unique<PaddingProperty>();
    }
}

/**
 * @tc.name: SwiperPatternGetRemainingOffset001
 * @tc.desc: GetRemainingOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetRemainingOffset001, TestSize.Level1)
{
    CreateDefaultSwiper();
    layoutProperty_->UpdateLoop(true);
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));

    /**
     * @tc.steps: step2. call GetRemainingOffset.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetDistanceToEdge();
            if (i == 1) {
                pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
                continue;
            }
            pattern_->itemPosition_.clear();
        }
        layoutProperty_->UpdateLoop(false);
    }
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->GetDistanceToEdge();
}

/**
 * @tc.name: SwiperPatternCalculateDisplayCount001
 * @tc.desc: CalculateDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCalculateDisplayCount001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);

    /**
     * @tc.steps: step2. call CalculateDisplayCount.
     * @tc.expected: Related function runs ok.
     */
    pattern_->CalculateDisplayCount();
}

/**
 * @tc.name: SwiperPatternOnTouchTestHit001
 * @tc.desc: OnTouchTestHit
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTouchTestHit001, TestSize.Level1)
{
    CreateDefaultSwiper();

    /**
     * @tc.steps: step2. call OnTouchTestHit.
     * @tc.expected: Related function runs ok.
     */
    CommonFunc callback = [] {};
    pattern_->isTouchDown_ = false;
    pattern_->swiperController_->SetRemoveTabBarEventCallback(callback);
    pattern_->OnTouchTestHit(SourceType::TOUCH);
    EXPECT_NE(pattern_->swiperController_->GetRemoveTabBarEventCallback(), nullptr);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    CreateWithArrow();
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = false;
    config.skipLayout = false;

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function runs ok.
     */
    TurnPageRateFunc callback = [](const int32_t i, float f) {};
    pattern_->swiperController_->SetTurnPageRateCallback(callback);
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    dirty->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm);
    dirty->layoutAlgorithm_->layoutAlgorithm_ = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    ASSERT_NE(dirty->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm()), nullptr);
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->isDragging_ = true;
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_NE(pattern_->swiperController_->GetTurnPageRateCallback(), nullptr);
}

/**
 * @tc.name: SwiperPatternGetDisplayCount002
 * @tc.desc: GetDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetDisplayCount002, TestSize.Level1)
{
    CreateDefaultSwiper();
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(720.f, 1200.f));
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty_->UpdateContentConstraint();

    /**
     * @tc.steps: step2. Set the FrameSize of the model.
     */
    frameNode_->GetGeometryNode()->SetFrameSize(SizeF(720.f, 1136.f));
    Dimension SWIPER_MINSIZE = 50.0_vp;

    for (int i = 0; i < 4; i++) {
        /**
         * @tc.steps: step3. Update the MinSize of one swiper item.
         * @tc.expected: Related function runs ok.
         */
        layoutProperty_->UpdateMinSize(SWIPER_MINSIZE);
        EXPECT_EQ(layoutProperty_->GetMinSize().value_or(Dimension(0.0, DimensionUnit::VP)), SWIPER_MINSIZE);

        /**
         * @tc.steps: step4. Call GetDisplayCount.
         * @tc.expected: The return value is correct.
         */
        float displayCount = static_cast<int32_t>(
            floor((SizeF(720.f, 1136.f).Width() - 2 * 16.f + 16.f) / (SWIPER_MINSIZE.ConvertToPx() + 16.f)));
        displayCount = displayCount > 0 ? displayCount : 1;
        displayCount = displayCount > pattern_->TotalCount() ? pattern_->TotalCount() : displayCount;
        EXPECT_EQ(pattern_->GetDisplayCount(), displayCount);

        constexpr Dimension delta = 200.0_vp;
        SWIPER_MINSIZE += delta;
    }
}

/**
 * @tc.name: SwiperPatternGetFirstItemInfoInVisibleArea001
 * @tc.desc: GetFirstItemInfoInVisibleArea
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetFirstItemInfoInVisibleArea001, TestSize.Level1)
{
    CreateDefaultSwiper();
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    }, swiperItemInfo2 { -0.1f, -0.2f }, swiperItemInfo3 { -0.1f, 0.2f }, swiperItemInfo4 { 0.1f, -0.2f };
    pattern_->itemPosition_.clear();
    auto dimension = Dimension(1);

    /**
     * @tc.steps: step2. call GetFirstItemInfoInVisibleArea.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetFirstItemInfoInVisibleArea();
            if (i == 1) {
                break;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
            pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
            pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo3));
            pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo4));
            layoutProperty_->UpdatePrevMargin(dimension);
            layoutProperty_->layoutConstraint_->scaleProperty = ScaleProperty { 1.0f, 1.0f, 1.0f };
        }
        layoutProperty_->ResetPrevMargin();
        layoutProperty_->layoutConstraint_->scaleProperty = ScaleProperty { 0.0f, 0.0f, 0.0f };
    }
}

/**
 * @tc.name: SwiperPatternGetSecondItemInfoInVisibleArea001
 * @tc.desc: GetSecondItemInfoInVisibleArea
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetSecondItemInfoInVisibleArea001, TestSize.Level1)
{
    CreateDefaultSwiper();
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    }, swiperItemInfo2 { -0.1f, -0.2f }, swiperItemInfo3 { -0.1f, 0.2f }, swiperItemInfo4 { 0.1f, -0.2f };
    pattern_->itemPosition_.clear();
    auto dimension = Dimension(1);

    /**
     * @tc.steps: step2. call GetSecondItemInfoInVisibleArea.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetSecondItemInfoInVisibleArea();
            if (i == 1) {
                break;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
            pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
            pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo3));
            pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo4));
            layoutProperty_->UpdatePrevMargin(dimension);
            layoutProperty_->layoutConstraint_->scaleProperty = ScaleProperty { 1.0f, 1.0f, 1.0f };
        }
        layoutProperty_->ResetPrevMargin();
        layoutProperty_->layoutConstraint_->scaleProperty = ScaleProperty { 0.0f, 0.0f, 0.0f };
    }
    pattern_->itemPosition_.erase(2);
    pattern_->GetSecondItemInfoInVisibleArea();
}

/**
 * @tc.name: PostTranslateTask001
 * @tc.desc: PostTranslateTask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PostTranslateTask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call PostTranslateTask
     * @tc.expected: Swipe to next
     */
    CreateDefaultSwiper();
    pattern_->PostTranslateTask(DEFAULT_INTERVAL);
    EXPECT_EQ(pattern_->targetIndex_, 1);
}

/**
 * @tc.name: PostTranslateTask002
 * @tc.desc: PostTranslateTask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PostTranslateTask002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. loop is false, index is last item index
     * @tc.expected: Can not swipe to next
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetIndex(2);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Call PostTranslateTask
     * @tc.expected: Can swipe to next
     */
    pattern_->PostTranslateTask(DEFAULT_INTERVAL);
    EXPECT_EQ(pattern_->targetIndex_, 3);

    /**
     * @tc.steps: step3. Swipe to last item and call PostTranslateTask
     * @tc.expected: Can not swipe to next
     */
    ChangeIndex(3);
    pattern_->PostTranslateTask(DEFAULT_INTERVAL);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());
}

/**
 * @tc.name: PostTranslateTask003
 * @tc.desc: PostTranslateTask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PostTranslateTask003, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperDone();
    pattern_->itemPosition_.clear();
    pattern_->PostTranslateTask(DEFAULT_INTERVAL);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());

    layoutProperty_->UpdateDisplayCount(0);
    pattern_->PostTranslateTask(DEFAULT_INTERVAL);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());
}

/**
 * @tc.name: SwiperPatternRegisterVisibleAreaChange001
 * @tc.desc: RegisterVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternRegisterVisibleAreaChange001, TestSize.Level1)
{
    CreateDefaultSwiper();

    /**
     * @tc.steps: step2. call RegisterVisibleAreaChange.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->RegisterVisibleAreaChange();
            if (i == 1) {
                pattern_->hasVisibleChangeRegistered_ = false;
            }
            pattern_->hasVisibleChangeRegistered_ = true;
        }
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    }

    pattern_->isWindowShow_ = false;
    for (int i = 0; i <= 1; i++) {
        pattern_->RegisterVisibleAreaChange();
        pattern_->isWindowShow_ = true;
        pattern_->isVisibleArea_ = true;
        pattern_->isVisible_ = true;
    }
}

/**
 * @tc.name: SwiperPatternOnTranslateFinish001
 * @tc.desc: OnTranslateFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTranslateFinish001, TestSize.Level1)
{
    CreateWithArrow();
    int32_t nextIndex = 1;
    bool restartAutoPlay = true;
    bool forceStop = true;

    /**
     * @tc.steps: step2. call OnTranslateFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnTranslateFinish(nextIndex, restartAutoPlay, pattern_->isFinishAnimation_, forceStop);
            if (i == 1) {
                pattern_->isFinishAnimation_ = false;
                continue;
            }
            pattern_->isFinishAnimation_ = true;
            frameNode_->AddChild(indicatorNode_);
            pattern_->isVisible_ = false;
        }
        frameNode_->AddChild(leftArrowNode_);
        frameNode_->AddChild(indicatorNode_);
        forceStop = false;
        pattern_->isVisible_ = true;
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
        layoutProperty_->UpdateLoop(true);
    }
}

/**
 * @tc.name: SwiperPatternGetCustomPropertyOffset001
 * @tc.desc: GetCustomPropertyOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetCustomPropertyOffset001, TestSize.Level1)
{
    CreateDefaultSwiper();
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->ResetPrevMargin();

    /**
     * @tc.steps: step2. call GetCustomPropertyOffset.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetCustomPropertyOffset();
            if (i == 1) {
                break;
            }
            layoutProperty_->UpdateDirection(Axis::VERTICAL);
            layoutProperty_->UpdatePrevMargin(Dimension(0));
        }
        layoutProperty_->UpdatePrevMargin(Dimension(1));
    }
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
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->ComputeNextIndexByVelocity(velocity, true), 0);
    velocity = -781.0f;
    EXPECT_EQ(pattern_->ComputeNextIndexByVelocity(velocity, false), 1);
    pattern_->SwipeToWithoutAnimation(0);
    FlushLayoutTask(frameNode_);
    pattern_->UpdateCurrentOffset(-241.0f);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->ComputeNextIndexByVelocity(velocity, true), 1);
    velocity = -780.0f;
    EXPECT_EQ(pattern_->ComputeNextIndexByVelocity(velocity, false), 1);
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->UpdateCurrentOffset(10.f);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 10.f);
}

/**
 * @tc.name: UpdateCurrentOffset002
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateCurrentOffset002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::SPRING);
    pattern_->isTouchPad_ = true;
    pattern_->childScrolling_ = true;
    pattern_->UpdateCurrentOffset(10.f);
    FlushLayoutTask(frameNode_);
    EXPECT_GT(GetChildX(frameNode_, 0), 0.f);
    EXPECT_LT(GetChildX(frameNode_, 0), 10.f);

    float preOffset = GetChildX(frameNode_, 0);
    pattern_->UpdateCurrentOffset(-20.f);
    FlushLayoutTask(frameNode_);
    EXPECT_LT(GetChildX(frameNode_, 0), preOffset);
    EXPECT_GT(GetChildX(frameNode_, 0), -20.f);
}

/**
 * @tc.name: UpdateCurrentOffset003
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateCurrentOffset003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetEdgeEffect(EdgeEffect::FADE);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::FADE);
    pattern_->childScrolling_ = true;
    pattern_->UpdateCurrentOffset(10.f);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.f);

    pattern_->UpdateCurrentOffset(-20.f);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), -20.f);
}

/**
 * @tc.name: UpdateCurrentOffset004
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateCurrentOffset004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetEdgeEffect(EdgeEffect::NONE);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::NONE);
    pattern_->childScrolling_ = true;
    pattern_->UpdateCurrentOffset(10.f);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.f);

    pattern_->UpdateCurrentOffset(-20.f);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), -20.f);
}

/**
 * @tc.name: UpdateCurrentOffset005
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateCurrentOffset005, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperDone();
    pattern_->UpdateCurrentOffset(10.f);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->currentOffset_, 0.f);
}

/**
 * @tc.name: SwiperPatternBeforeCreateLayoutWrapper001
 * @tc.desc: BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternBeforeCreateLayoutWrapper001, TestSize.Level1)
{
    CreateWithArrow();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);

    /**
     * @tc.steps: step2. call BeforeCreateLayoutWrapper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->BeforeCreateLayoutWrapper();
            if (i == 1) {
                frameNode_->AddChild(leftArrowNode_);
                continue;
            }
            pattern_->rightButtonId_.reset();
            pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
        }
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(0);
    }

    frameNode_->AddChild(rightArrowNode_);
    pattern_->currentIndex_ = 0;
    pattern_->oldIndex_ = 0;
    for (int i = 0; i <= 1; i++) {
        pattern_->BeforeCreateLayoutWrapper();
        pattern_->currentIndex_ = 1;
    }
    pattern_->jumpIndex_.reset();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->BeforeCreateLayoutWrapper();
                if (i == 1 && j == 0) {
                    pattern_->jumpIndex_ = 0;
                    continue;
                }
                if (i == 1 && j == 1) {
                    pattern_->jumpIndex_ = 10;
                    continue;
                }
                pattern_->jumpIndex_ = -1;
                pattern_->usePropertyAnimation_ = true;
            }
            pattern_->jumpIndex_ = 10;
            pattern_->rightButtonId_.reset();
            pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
            frameNode_->AddChild(leftArrowNode_);
            frameNode_->AddChild(rightArrowNode_);
        }
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
        pattern_->jumpIndex_ = -1;
    }
}

/**
 * @tc.name: SwiperPatternIsVisibleChildrenSizeLessThanSwiper001
 * @tc.desc: IsVisibleChildrenSizeLessThanSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternIsVisibleChildrenSizeLessThanSwiper001, TestSize.Level1)
{
    CreateWithArrow();
    layoutProperty_->UpdateDisplayCount(5);
    pattern_->IsVisibleChildrenSizeLessThanSwiper();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    pattern_->itemPosition_.clear();
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);
    EXPECT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 0);

    /**
     * @tc.steps: step2. call IsVisibleChildrenSizeLessThanSwiper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->IsVisibleChildrenSizeLessThanSwiper();
            if (i == 1) {
                pattern_->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
        }
        pattern_->itemPosition_.clear();
        pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 1 }));
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->IsVisibleChildrenSizeLessThanSwiper();
            pattern_->itemPosition_.clear();
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
        }
    }
}

/**
 * @tc.name: SwiperPatternGetLastItemInfoInVisibleArea001
 * @tc.desc: GetLastItemInfoInVisibleArea
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetLastItemInfoInVisibleArea001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call GetLastItemInfoInVisibleArea.
     * @tc.expected: Related function runs ok.
     */
    pattern_->GetLastItemInfoInVisibleArea();
}

/**
 * @tc.name: SwiperPatternBeforeCreateLayoutWrapper002
 * @tc.desc: BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternBeforeCreateLayoutWrapper002, TestSize.Level1)
{
    CreateDefaultSwiper();

    /**
     * @tc.steps: step2. call BeforeCreateLayoutWrapper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->BeforeCreateLayoutWrapper();
            if (i == 1) {
                pattern_->mainSizeIsMeasured_ = false;
                continue;
            }
            pattern_->mainSizeIsMeasured_ = true;
        }
    }
}

/**
 * @tc.name: SwiperPatternBeforeCreateLayoutWrapper003
 * @tc.desc: BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternBeforeCreateLayoutWrapper003, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->itemPosition_.clear();
    pattern_->isVoluntarilyClear_ = false;

    /**
     * @tc.steps: step2. call BeforeCreateLayoutWrapper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->BeforeCreateLayoutWrapper();
        pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    }
}

/**
 * @tc.name: SwiperPatternIsVisibleChildrenSizeLessThanSwiper002
 * @tc.desc: IsVisibleChildrenSizeLessThanSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternIsVisibleChildrenSizeLessThanSwiper002, TestSize.Level1)
{
    CreateWithArrow();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    pattern_->itemPosition_.clear();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 3 }));

    /**
     * @tc.steps: step2. call IsVisibleChildrenSizeLessThanSwiper.
     * @tc.expected: Related function runs ok.
     */
    pattern_->IsVisibleChildrenSizeLessThanSwiper();
}

/**
 * @tc.name: SwiperPatternOnTouchTestHit002
 * @tc.desc: OnTouchTestHit
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTouchTestHit002, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto hitTestType = SourceType::MOUSE;

    /**
     * @tc.steps: step2. call OnTouchTestHit.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->OnTouchTestHit(hitTestType);
        pattern_->isTouchDown_ = true;
    }
}

/**
 * @tc.name: SwiperModelNGSetDisplayCount001
 * @tc.desc: Test SetDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNGSetDisplayCount001, TestSize.Level1)
{
    SwiperModelNG mode;
    auto controller = mode.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    ASSERT_NE(controller, nullptr);
    int32_t displayCount = 0;

    /**
     * @tc.steps: step3. call SetDisplayCount.
     * @tc.expected: the related function runs ok.
     */
    mode.SetDisplayCount(displayCount);
}

/**
 * @tc.name: SwiperOnLoopChange001
 * @tc.desc: Swiper OnLoopChange.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperOnLoopChange001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->preLoop_ = true;
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->ResetPrevMargin();
    layoutProperty_->ResetNextMargin();

    /**
     * @tc.steps: step2. call OnLoopChange.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnLoopChange();
            if (i == 1) {
                layoutProperty_->ResetPrevMargin();
                continue;
            }
            layoutProperty_->UpdatePrevMargin(Dimension(1));
        }
        layoutProperty_->UpdateNextMargin(Dimension(1));
    }
}

/**
 * @tc.name: SwiperPatternOnTranslateFinish002
 * @tc.desc: OnTranslateFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTranslateFinish002, TestSize.Level1)
{
    CreateWithArrow();
    int32_t nextIndex = 1;
    bool restartAutoPlay = true;
    bool forceStop = true;
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->currentIndex_ = 1;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    pattern_->isVisible_ = true;
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    pattern_->isIndicatorLongPress_ = false;
    EXPECT_EQ(frameNode_->GetChildren().size(), 7);

    /**
     * @tc.steps: step2. call OnTranslateFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnTranslateFinish(nextIndex, restartAutoPlay, pattern_->isFinishAnimation_, forceStop);
            if (i == 1) {
                pattern_->isUserFinish_ = true;
                continue;
            }
            pattern_->isUserFinish_ = false;
        }
        pattern_->isVisible_ = false;
    }
}

/**
 * @tc.name: SwiperPatternOnModifyDone002
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnModifyDone002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<SwiperPattern> indicatorPattern = frameNode_->GetPattern<SwiperPattern>();
    indicatorPattern->OnModifyDone();
    indicatorPattern->swiperController_->removeSwiperEventCallback_();
    indicatorPattern->swiperController_->addSwiperEventCallback_();
    pattern_->OnAfterModifyDone();
    EXPECT_NE(indicatorPattern, nullptr);
}

/**
 * @tc.name: SwiperPatternRegisterVisibleAreaChange002
 * @tc.desc: RegisterVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternRegisterVisibleAreaChange002, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto pipeline = frameNode_->GetContextRefPtr();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. call RegisterVisibleAreaChange.
     * @tc.expected: Related function runs ok.
     */
    pattern_->hasVisibleChangeRegistered_ = false;
    paintProperty_->UpdateAutoPlay(true);
    pattern_->RegisterVisibleAreaChange();
    EXPECT_TRUE(pattern_->hasVisibleChangeRegistered_);
    pattern_->isWindowShow_ = false;
    pattern_->hasVisibleChangeRegistered_ = false;
    paintProperty_->UpdateAutoPlay(true);
    pattern_->RegisterVisibleAreaChange();
    EXPECT_TRUE(pattern_->hasVisibleChangeRegistered_);
}

/**
 * @tc.name: SwiperPatternInitSurfaceChangedCallback001
 * @tc.desc: InitSurfaceChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitSurfaceChangedCallback001, TestSize.Level1)
{
    CreateDefaultSwiper();
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
 * @tc.name: SwiperPatternMarkDirtyNodeSelf001
 * @tc.desc: MarkDirtyNodeSelf
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternMarkDirtyNodeSelf001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);

    /**
     * @tc.steps: step2. call MarkDirtyNodeSelf.
     * @tc.expected: Related function is called.
     */
    pattern_->crossMatchChild_ = true;
    pattern_->MarkDirtyNodeSelf();
    EXPECT_TRUE(pattern_->crossMatchChild_);
    pattern_->crossMatchChild_ = false;
    pattern_->MarkDirtyNodeSelf();
    EXPECT_FALSE(pattern_->crossMatchChild_);
}

/**
 * @tc.name: SwiperPatternOnWindowHide001
 * @tc.desc: MarkDirtyNodeSelf
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnWindowHide001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);

    /**
     * @tc.steps: step2. call MarkDirtyNodeSelf.
     * @tc.expected: Related function is called.
     */
    pattern_->isDragging_ = true;
    pattern_->OnWindowHide();
    EXPECT_FALSE(pattern_->isDragging_);
    pattern_->isDragging_ = false;
    pattern_->OnWindowHide();
    EXPECT_FALSE(pattern_->isDragging_);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap003
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    CreateWithArrow();
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = true;
    config.skipLayout = false;
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function runs ok.
     */
    paintProperty_->GetAutoPlay().emplace(false);
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    config.skipMeasure = false;
    paintProperty_->GetAutoPlay().emplace(false);
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    paintProperty_->GetAutoPlay().emplace(true);
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    paintProperty_->GetAutoPlay().emplace(true);
    config.skipMeasure = false;
    config.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
}

/**
 * @tc.name: CalculateGestureState001
 * @tc.desc: test Swiper indicator gesture state
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalculateGestureState001, TestSize.Level1)
{
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
    EXPECT_EQ(pattern_->TotalCount(), 4);

    auto turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    auto currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, 0.0f);
    EXPECT_EQ(currentFirstIndex, 0);

    pattern_->UpdateCurrentOffset(240.0f);
    FlushLayoutTask(frameNode_);
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.5f);
    EXPECT_EQ(currentFirstIndex, -1);

    pattern_->UpdateCurrentOffset(120.0f);
    FlushLayoutTask(frameNode_);
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.25f);
    EXPECT_EQ(currentFirstIndex, -1);

    pattern_->ChangeIndex(3, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->currentFirstIndex_, 3);

    pattern_->UpdateCurrentOffset(-240.0f);
    FlushLayoutTask(frameNode_);
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.5f);
    EXPECT_EQ(currentFirstIndex, 3);

    pattern_->ChangeIndex(0, false);
    FlushLayoutTask(frameNode_);
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
    FlushLayoutTask(frameNode_);
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.5f);
    EXPECT_EQ(currentFirstIndex, 0);

    pattern_->UpdateCurrentOffset(-120.0f);
    FlushLayoutTask(frameNode_);
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, 0.0f);
    EXPECT_EQ(currentFirstIndex, 1);

    pattern_->UpdateCurrentOffset(-120.0f);
    FlushLayoutTask(frameNode_);
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.5f);
    EXPECT_EQ(currentFirstIndex, 1);

    pattern_->UpdateCurrentOffset(480.0f);
    FlushLayoutTask(frameNode_);
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, -0.5f);
    EXPECT_EQ(currentFirstIndex, -1);

    pattern_->UpdateCurrentOffset(120.0f);
    FlushLayoutTask(frameNode_);
    turnPageRate = pattern_->CalcCurrentPageStatus(0.0f).first;
    currentFirstIndex = pattern_->CalcCurrentPageStatus(0.0f).second;
    EXPECT_EQ(turnPageRate, 0.0f);
    EXPECT_EQ(currentFirstIndex, -1);

    pattern_->ChangeIndex(5, false);
    FlushLayoutTask(frameNode_);
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
 * @tc.name: ResetDisplayCount001
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ResetDisplayCount001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step3.1. Test SetIndex function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetIndex(1);
    EXPECT_EQ(layoutProperty->GetIndex(), 1);

    /**
     * @tc.steps: step3.1. Test SetIndex function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetDisplayCount(10);
    model.ResetDisplayCount();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto uiNode = AceType::DynamicCast<FrameNode>(element);
    pattern = uiNode->GetPattern<SwiperPattern>();
    EXPECT_NE(pattern->GetDisplayCount(), 10);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithArrow();
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = false;
    config.skipLayout = false;

    TurnPageRateFunc callback = [](const int32_t i, float f) {};
    pattern_->swiperController_->SetTurnPageRateCallback(callback);
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    dirty->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm);
    dirty->layoutAlgorithm_->layoutAlgorithm_ = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    ASSERT_NE(dirty->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm()), nullptr);
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->isDragging_ = true;
    pattern_->windowSizeChangeReason_ = WindowSizeChangeReason::ROTATION;
    /**
     * @tc.steps: step2. Calling the OnDirtyLayoutWrapperSwap interface
     * @tc.expected: Pattern_ -> WindowSizeChangeReason_ Not equal to WindowSizeChangeReason::ROTATION
     */
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_NE(pattern_->windowSizeChangeReason_, WindowSizeChangeReason::ROTATION);
}

/**
 * @tc.name: SwiperProcessDelta001
 * @tc.desc: Test for SwiperPattern::ProcessDelta.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperProcessDelta001, TestSize.Level1)
{
    float mainSize = 50.0f;
    float delta = 5.0f;
    float deltaSum = 46.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, 4.0f);

    delta = -10.0f;
    deltaSum = 50.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, -10.0f);

    delta = -10.0f;
    deltaSum = -40.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, -10.0f);

    delta = -10.0f;
    deltaSum = -50.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, 0.0f);

    delta = -50.0f;
    deltaSum = -50.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, 0.0f);

    delta = 1.0f;
    deltaSum = -50.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, 1.0f);
}

/**
 * @tc.name: AdjustCurrentIndexOnSwipePage001
 * @tc.desc: Test SwiperPattern AdjustCurrentIndexOnSwipePage
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAdjustCurrentIndexOnSwipePage001, TestSize.Level1)
{
    CreateDefaultSwiper();
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
 * @tc.name: AdjustCurrentIndexWithTotalCountChange001
 * @tc.desc: Test SwiperPattern AdjustCurrentIndexWithTotalCountChange001
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AdjustCurrentIndexWithTotalCountChange001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, ITEM_NUMBER);
    /**
     * @tc.steps: step1. turn page to last, let index change to -1.
     */
    ShowPrevious();
    EXPECT_EQ(pattern_->currentIndex_, -1);
    /**
     * @tc.steps: step2. add child, let totalCount increase.
     */
    RefPtr<FrameNode> testNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    frameNode_->AddChild(testNode, pattern_->TotalCount() - 1);
    EXPECT_EQ(pattern_->oldChildrenSize_.value(), ITEM_NUMBER);
    EXPECT_EQ(pattern_->TotalCount(), ITEM_NUMBER + 1);
    pattern_->BeforeCreateLayoutWrapper();
    /**
     * @tc.steps: step3. index will need not to be changed.
     */
    EXPECT_EQ(pattern_->currentIndex_, pattern_->oldChildrenSize_.value() - 1);
}

/**
 * @tc.name: AdjustCurrentIndexWithTotalCountChange002
 * @tc.desc: Test SwiperPattern AdjustCurrentIndexWithTotalCountChange002
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AdjustCurrentIndexWithTotalCountChange002, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, ITEM_NUMBER);
    /**
     * @tc.steps: step1. turn page to last, let index change to -1.
     */
    ShowPrevious();
    EXPECT_EQ(pattern_->currentIndex_, -1);
    /**
     * @tc.steps: step2. add child, let totalCount decrease.
     */
    RefPtr<FrameNode> testNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    frameNode_->RemoveChildAtIndex(0);
    EXPECT_EQ(pattern_->oldChildrenSize_.value(), ITEM_NUMBER);
    EXPECT_EQ(pattern_->TotalCount(), ITEM_NUMBER - 1);
    pattern_->BeforeCreateLayoutWrapper();
    /**
     * @tc.steps: step3. index will need to be changed to 0.
     */
    EXPECT_EQ(pattern_->currentIndex_, 0);
}

/**
 * @tc.name: ComputeSwipePageNextIndex001
 * @tc.desc: Test SwiperPattern ComputeSwipePageNextIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternComputeSwipePageNextIndex001, TestSize.Level1)
{
    CreateDefaultSwiper();
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
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 0);

    pattern_->currentIndex_ = 3;
    dragVelocity = -500.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);
}

void SwiperTestNg::InitCaptureTest()
{
    CreateDefaultSwiper();
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
    FlushLayoutTask(frameNode_);
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
    FlushLayoutTask(frameNode_);
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
    FlushLayoutTask(frameNode_);
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
    FlushLayoutTask(frameNode_);
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
    FlushLayoutTask(frameNode_);
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
    FlushLayoutTask(frameNode_);
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
 * @tc.name: FadeOverScroll001
 * @tc.desc: Test SwiperPattern FadeOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FadeOverScroll001, TestSize.Level1)
{
    CreateDefaultSwiper();
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(720.f, 1200.f));
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty_->UpdateContentConstraint();
    /**
     * @tc.steps: step1. set data.
     */
    struct SwiperItemInfo swiperItemInfo1;
    struct SwiperItemInfo swiperItemInfo2;
    struct SwiperItemInfo swiperItemInfo3;
    struct SwiperItemInfo swiperItemInfo4;
    pattern_->itemPosition_.clear();
    swiperItemInfo1.startPos = 0.0f;
    swiperItemInfo1.endPos = 180.0f;
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    swiperItemInfo2.startPos = 180.0f;
    swiperItemInfo2.endPos = 360.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo2));
    swiperItemInfo3.startPos = 360.0f;
    swiperItemInfo3.endPos = 540.0f;
    pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo3));
    swiperItemInfo4.startPos = 540.0f;
    swiperItemInfo4.endPos = 720.0f;
    pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo4));
    layoutProperty_->UpdateDisplayCount(4);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);
    EXPECT_FALSE(pattern_->IsLoop());
    EXPECT_FALSE(pattern_->itemPosition_.empty());
    /**
     * @tc.steps: step2. call no mirror func.
     */
    EXPECT_FALSE(pattern_->IsOutOfBoundary(0.0f));
    layoutProperty_->UpdateLoop(false);
    EXPECT_TRUE(pattern_->IsOutOfBoundary(10.0f));

    float offset = 0.0f;
    EXPECT_FALSE(pattern_->FadeOverScroll(offset));
    offset = 10.0f;
    EXPECT_FALSE(pattern_->IsVisibleChildrenSizeLessThanSwiper());
    EXPECT_TRUE(pattern_->FadeOverScroll(offset));
    /**
     * @tc.steps: step3. call mirror func.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    pattern_->fadeOffset_ = 0.0f;
    offset = 0.0f;
    EXPECT_FALSE(pattern_->FadeOverScroll(offset));
    EXPECT_FALSE(pattern_->IsVisibleChildrenSizeLessThanSwiper());
    offset = -10.0f;
    EXPECT_TRUE(pattern_->FadeOverScroll(offset));
}

/**
 * @tc.name: IsOutOfStart001
 * @tc.desc: Test SwiperPattern IsOutOfStart
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, IsOutOfStart001, TestSize.Level1)
{
    CreateDefaultSwiper();
    float offset = 10.0f;
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdateDisplayCount(4);
    auto totalCount = pattern_->TotalCount();
    pattern_->currentIndex_ = 0;
    EXPECT_EQ(totalCount, 4);
    EXPECT_FALSE(pattern_->itemPosition_.empty());
    /**
     * @tc.steps: step1. call no mirror func.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    offset = 10.0f;
    EXPECT_TRUE(pattern_->IsOutOfStart(offset));
    /**
     * @tc.steps: step2. call mirror func.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    offset = -10.0f;
    EXPECT_TRUE(pattern_->IsOutOfStart(offset));
}

/**
 * @tc.name: GetCustomPropertyTargetOffset001
 * @tc.desc: Test SwiperPattern GetCustomPropertyTargetOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, GetCustomPropertyTargetOffset001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto paddingAndBorder = layoutProperty_->CreatePaddingAndBorder();
    auto paddingAndBorderValue = paddingAndBorder.top.value_or(0.0) + pattern_->tabsPaddingAndBorder_.top.value_or(0.0);
    layoutProperty_->UpdatePrevMargin(Dimension(10));
    float offset = Dimension(paddingAndBorderValue - 10.0f, DimensionUnit::PX).ConvertToVp();
    /**
     * @tc.steps: step1. call no mirror func.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    offset = Dimension(paddingAndBorderValue + 10.0f, DimensionUnit::PX).ConvertToVp();
    EXPECT_EQ(pattern_->GetCustomPropertyTargetOffset(), offset);
    /**
     * @tc.steps: step2. call mirror func.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    offset = Dimension(paddingAndBorderValue - 10.0f, DimensionUnit::PX).ConvertToVp();
    EXPECT_EQ(pattern_->GetCustomPropertyTargetOffset(), offset);
}

/**
 * @tc.name: IsOutOfBoundary001
 * @tc.desc: Test SwiperPattern IsOutOfBoundary
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, IsOutOfBoundary001, TestSize.Level1)
{
    CreateDefaultSwiper();
    layoutProperty_->UpdateLoop(false);
    EXPECT_FALSE(pattern_->itemPosition_.empty());
    /**
     * @tc.steps: step1. call no mirror func.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    EXPECT_TRUE(pattern_->IsOutOfBoundary(10.0f));
    /**
     * @tc.steps: step2. call mirror func.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_TRUE(pattern_->IsOutOfBoundary(-10.0f));
}

/**
 * @tc.name: CheckTargetIndex001
 * @tc.desc: Test SwiperPattern CheckTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CheckTargetIndexheckTargetIndex001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);
    layoutProperty_->UpdateDisplayCount(4);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    EXPECT_TRUE(pattern_->IsAutoLinear());
    pattern_->currentIndex_ = 1;
    int32_t targetIndex = 0;
    EXPECT_TRUE(pattern_->GetLoopIndex(targetIndex) != pattern_->GetLoopIndex(pattern_->currentIndex_));
    auto currentFrameNode = pattern_->GetCurrentFrameNode(pattern_->GetLoopIndex(targetIndex));
    EXPECT_NE(currentFrameNode, nullptr);
    auto swiperLayoutProperty = currentFrameNode->GetLayoutProperty<LayoutProperty>();
    EXPECT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateVisibility(VisibleType::GONE);
    /**
     * @tc.steps: step1. call no mirror func.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    EXPECT_EQ(pattern_->CheckTargetIndex(targetIndex, true), targetIndex + 1);
    EXPECT_EQ(pattern_->CheckTargetIndex(targetIndex, false), targetIndex - 1);
    /**
     * @tc.steps: step2. call mirror func.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_EQ(pattern_->CheckTargetIndex(targetIndex, true), targetIndex - 1);
    EXPECT_EQ(pattern_->CheckTargetIndex(targetIndex, false), targetIndex + 1);
}

/**
 * @tc.name: SwiperSetFrameRateTest001
 * @tc.desc: Test SetFrameRate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperSetFrameRateTest001, TestSize.Level1)
{
    CreateDefaultSwiper();
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
} // namespace OHOS::Ace::NG
