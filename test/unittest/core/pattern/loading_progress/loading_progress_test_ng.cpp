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

#include "core/components_ng/pattern/loading_progress/loading_progress_base.h"

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_layout_algorithm.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_layout_property.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "core/components_ng/pattern/refresh/refresh_animation_state.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Color COLOR_DEFAULT = Color::RED;
} // namespace

class LoadingProgressTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateLoadingProgressNode(const Color& color);
};

void LoadingProgressTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void LoadingProgressTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> LoadingProgressTestNg::CreateLoadingProgressNode(const Color& color)
{
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    modelNg.SetColor(color);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: LoadingProgressFrameNodeCreator001
 * @tc.desc: Test all the property of loadingProgress.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressFrameNodeCreator001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LoadingProgressPaintProperty> renderProperty = frameNode->GetPaintProperty<LoadingProgressPaintProperty>();
    ASSERT_NE(renderProperty, nullptr);
    EXPECT_EQ(renderProperty->GetColorValue(), COLOR_DEFAULT);
}

/**
 * @tc.name: LoadingProgressLayoutAlgorithm001
 * @tc.desc: Test MeasureContent function of loadingProgressNode.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressLayoutAlgorithm001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    constexpr float MAXSIZE_WIDTH = 200.0f;
    constexpr float MAXSIZE_HEIGHT = 240.0f;
    constexpr float SELFSIZE_WIDTH = 100.0f;
    constexpr float SELFSIZE_HEIGHT = 300.0f;
    LoadingProgressLayoutAlgorithm layoutAlgorithm;
    /**
     * @tc.cases: case1. When father selfIdealSize doesn't exist, LoadingProgressLayoutAlgorithm will calculate
     *                   contentSize with maxSize LayoutConstraint.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference = SizeF(MAXSIZE_WIDTH, MAXSIZE_HEIGHT);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto size1 = layoutAlgorithm.MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_NE(size1, std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(MAXSIZE_WIDTH, MAXSIZE_WIDTH));
    /**
     * @tc.cases: case2. When father selfIdealSize is valid, LoadingProgressLayoutAlgorithm will calculate
     *                   contentSize with maxSize LayoutConstraint and selfIdealSize.
     */
    layoutConstraint.selfIdealSize.width_ = SELFSIZE_WIDTH;
    layoutConstraint.selfIdealSize.height_ = SELFSIZE_HEIGHT;
    auto size2 = layoutAlgorithm.MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_NE(size2, std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(SELFSIZE_WIDTH, SELFSIZE_WIDTH));
}

/**
 * @tc.name: LoadingProgressPatternTest001
 * @tc.desc: Test Pattern OnDirtyLayoutWrapperSwap function of loadingProgress.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressPatternTest001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    auto loadingProgressLayoutAlgorithm = AceType::MakeRefPtr<LoadingProgressLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(loadingProgressLayoutAlgorithm);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    EXPECT_TRUE(loadingProgressPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
    EXPECT_FALSE(loadingProgressPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false));
    layoutWrapper->skipMeasureContent_ = true;
    EXPECT_FALSE(loadingProgressPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, true));
    EXPECT_FALSE(loadingProgressPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true));
}

/**
 * @tc.name: LoadingProgressPatternTest002
 * @tc.desc: Test LoadingProgress in visible scene.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressPatternTest002, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    loadingProgressPattern->CreateNodePaintMethod();
    ASSERT_NE(loadingProgressPattern->loadingProgressModifier_, nullptr);
    auto layoutProperty = loadingProgressPattern->GetLayoutProperty<LoadingProgressLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isLoading_);
    layoutProperty->UpdateVisibility(VisibleType::GONE);
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    loadingProgressPattern->RegisterVisibleAreaChange();
    EXPECT_TRUE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    // Loading StartAnimation: isVisibleArea_ = true, isVisible_ = true, isShow_ = false, eableLoading_ = true
    loadingProgressPattern->OnWindowHide();
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    // Loading StartAnimation: isVisibleArea_ = false, isVisible_ = true, isShow_ = false, eableLoading_ = true
    loadingProgressPattern->isVisibleArea_ = false;
    loadingProgressPattern->StartAnimation();
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    // Loading StartAnimation: isVisibleArea_ = false, isVisible_ = true, isShow_ = true, eableLoading_ = true
    loadingProgressPattern->OnWindowShow();
    loadingProgressPattern->StartAnimation();
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    // Loading StartAnimation: isVisibleArea_ = false, isVisible_ = true, isShow_ = true, eableLoading_ = false
    loadingProgressPattern->enableLoading_ = false;
    loadingProgressPattern->StartAnimation();
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    // Loading StartAnimation: isVisibleArea_ = false, isVisible_ = true, isShow_ = false, eableLoading_ = false
    loadingProgressPattern->OnWindowHide();
    loadingProgressPattern->StartAnimation();
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
}

/**
 * @tc.name: LoadingProgressPatternTest003
 * @tc.desc: Test LoadingProgress enableLoading property.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test enableLoading property will be set in pattern successfully.
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    modelNg.SetEnableLoading(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto paintMethod =
        AceType::DynamicCast<LoadingProgressPaintMethod>(loadingProgressPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    ASSERT_NE(loadingProgressPattern->loadingProgressModifier_, nullptr);
    auto paintProperty = loadingProgressPattern->GetPaintProperty<LoadingProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->GetEnableLoading().value());
    loadingProgressPattern->OnModifyDone();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF());
    geometryNode->SetContentOffset(OffsetF());
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty);
    paintMethod->UpdateContentModifier(&paintWrapper);
    EXPECT_TRUE(loadingProgressPattern->enableLoading_);
    EXPECT_TRUE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    EXPECT_TRUE(loadingProgressPattern->loadingProgressModifier_->enableLoading_->Get());
    /**
     * @tc.steps: step2. when enableLoading property is false, loadingProgress will StopAnimation and not onDraw.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    modelNg.SetEnableLoading(false);
    loadingProgressPattern->OnModifyDone();
    EXPECT_FALSE(paintProperty->GetEnableLoading().value());
    EXPECT_FALSE(loadingProgressPattern->enableLoading_);
    PaintWrapper paintWrapper2(nullptr, geometryNode, paintProperty);
    paintMethod->UpdateContentModifier(&paintWrapper2);
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->enableLoading_->Get());
    Testing::MockCanvas rsCanvas;
    DrawingContext context = { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, Save()).Times(0);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(0);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).Times(0);
    EXPECT_CALL(rsCanvas, DetachBrush()).Times(0);
    EXPECT_CALL(rsCanvas, AttachPen(_)).Times(0);
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(0);
    EXPECT_CALL(rsCanvas, DetachPen()).Times(0);
    EXPECT_CALL(rsCanvas, Restore()).Times(0);
    loadingProgressPattern->loadingProgressModifier_->onDraw(context);
}

/**
 * @tc.name: LoadingProgressPatternTest004
 * @tc.desc: Test LoadingProgress StartAnimation will fail in some scene.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressPatternTest004, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    loadingProgressPattern->CreateNodePaintMethod();
    ASSERT_NE(loadingProgressPattern->loadingProgressModifier_, nullptr);
    // Loading StartAnimation: isVisibleArea_ = true, isVisible_ = false, isShow_ = false, eableLoading_ = false
    loadingProgressPattern->isVisible_ = false;
    loadingProgressPattern->OnWindowHide();
    loadingProgressPattern->enableLoading_ = false;
    loadingProgressPattern->StartAnimation();
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    // Loading StartAnimation: isVisibleArea_ = false, isVisible_ = false, isShow_ = false, eableLoading_ = false
    loadingProgressPattern->isVisibleArea_ = false;
    loadingProgressPattern->StartAnimation();
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    // Loading StartAnimation: isVisibleArea_ = false, isVisible_ = false, isShow_ = false, eableLoading_ = true
    loadingProgressPattern->enableLoading_ = true;
    loadingProgressPattern->StartAnimation();
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    // Loading StartAnimation: isVisibleArea_ = false, isVisible_ = false, isShow_ = true, eableLoading_ = true
    loadingProgressPattern->OnWindowShow();
    loadingProgressPattern->StartAnimation();
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    // Loading StartAnimation: isVisibleArea_ = true, isVisible_ = false, isShow_ = true, eableLoading_ = true
    loadingProgressPattern->isVisibleArea_ = true;
    loadingProgressPattern->StartAnimation();
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
    // Loading StartAnimation: isVisibleArea_ = true, isVisible_ = false, isShow_ = true, eableLoading_ = false
    loadingProgressPattern->enableLoading_ = false;
    loadingProgressPattern->StartAnimation();
    EXPECT_FALSE(loadingProgressPattern->loadingProgressModifier_->isVisible_);
}

/**
 * @tc.name: LoadingProgressPatternTest005
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode.
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    /**
     * @tc.steps: step2. get parament to enableloading
     */
    modelNg.SetEnableLoading(true);
    /**
     * @tc.steps: step3.
     * @tc.expected: check the switch property value.
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.enableloading_, true);
        return nullptr;
    };
    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressPaintMethodTest001
 * @tc.desc: Test LoadingProgressPaintMethod function of loadingProgress.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressPaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paintMethod.
     */
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto paintMethod =
        AceType::DynamicCast<LoadingProgressPaintMethod>(loadingProgressPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    ASSERT_NE(loadingProgressPattern->CreateNodePaintMethod(), nullptr);
    /**
     * @tc.steps: step2. test create PaintWrapper and ProgressTheme.
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF());
    geometryNode->SetContentOffset(OffsetF());
    PaintWrapper paintWrapper(renderContext, geometryNode, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->loadingColor_ = COLOR_DEFAULT;
    /**
     * @tc.cases: case1. LoadingProgressPaintProperty has no Color property and modifier will use Theme Color.
     */
    auto loadingProgressPaintProperty = loadingProgressPattern->GetPaintProperty<LoadingProgressPaintProperty>();
    EXPECT_TRUE(loadingProgressPaintProperty != nullptr);
    PaintWrapper paintWrapper1(renderContext, geometryNode, loadingProgressPaintProperty);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(progressTheme));
    paintMethod->UpdateContentModifier(&paintWrapper1);
    EXPECT_EQ(paintMethod->color_, COLOR_DEFAULT);
    /**
     * @tc.cases: case2. renderContext ForegroundColorStrategy and modifier will use foreground color flag
     */
    renderContext->UpdateForegroundColorStrategy(ForegroundColorStrategy());
    PaintWrapper paintWrapper3(renderContext, geometryNode, loadingProgressPaintProperty);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(progressTheme));
    paintMethod->UpdateContentModifier(&paintWrapper3);
    EXPECT_EQ(paintMethod->color_, Color::FOREGROUND);
    /**
     * test loadingState == REFRESH_STATE_FOLLOW_HAND
     */
    loadingProgressPaintProperty->UpdateRefreshAnimationState(RefreshAnimationState::FOLLOW_HAND);
    loadingProgressPaintProperty->UpdateRefreshSizeScaleRatio(-1.0f);
    paintMethod->loadingProgressModifier_->loadingProgressOwner_ = LoadingProgressOwner::REFRESH;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(progressTheme));
    paintMethod->UpdateContentModifier(&paintWrapper3);
    /**
     * test loadingState == REFRESH_STATE_FOLLOW_TO_RECYCLE
     */
    auto context = PipelineBase::GetCurrentContext();
    context->SetIsFormRender(true);
    loadingProgressPaintProperty->UpdateRefreshAnimationState(RefreshAnimationState::FOLLOW_TO_RECYCLE);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(progressTheme));
    paintMethod->UpdateContentModifier(&paintWrapper3);
    /**
     * test loadingState == REFRESH_STATE_RECYCLE
     */
    loadingProgressPaintProperty->UpdateRefreshAnimationState(RefreshAnimationState::FOLLOW_TO_RECYCLE);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(progressTheme));
    paintMethod->UpdateContentModifier(&paintWrapper3);
}

/**
 * @tc.name: LoadingProgressModifierTest001
 * @tc.desc: Test LoadingProgressModifier DrawRing function.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressModifierTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->loadingColor_ = COLOR_DEFAULT;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    LoadingProgressModifier loadingProgressModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context = { rsCanvas, 10.0f, 10.0f };
    RingParam ringParam;
    /**
     * @tc.cases: case1. ringColor == defaultColor.
     */
    loadingProgressModifier.SetColor(LinearColor(COLOR_DEFAULT));
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    loadingProgressModifier.DrawRing(context, ringParam);
    /**
     * @tc.cases: case2. ringColor != defaultColor.
     */
    loadingProgressModifier.SetColor(LinearColor(Color::BLUE));
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    loadingProgressModifier.DrawRing(context, ringParam);
}

/**
 * @tc.name: LoadingProgressModifierTest002
 * @tc.desc: Test LoadingProgressModifier DrawOrbit function.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressModifierTest002, TestSize.Level1)
{
    LoadingProgressModifier loadingProgressModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    /**
     * @tc.cases: case1. date > 0 && date < COUNT.
     */
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    CometParam cometParam;
    loadingProgressModifier.DrawOrbit(context, cometParam, 1.0f, 2.0f);
    /**
     * @tc.cases: case2. date > 0 && date >= COUNT.
     */
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    loadingProgressModifier.DrawOrbit(context, cometParam, 50.0f, 2.0f);
    /**
     * @tc.cases: case3. date <= 0.
     */
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    loadingProgressModifier.DrawOrbit(context, cometParam, .0f, 2.0f);
}

/**
 * @tc.name: LoadingProgressModifierTest003
 * @tc.desc: Test LoadingProgressModifier onDraw function.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressModifierTest003, TestSize.Level1)
{
    LoadingProgressModifier loadingProgressModifier;
    LinearColor color;
    loadingProgressModifier.SetColor(color);
    EXPECT_EQ(loadingProgressModifier.color_->Get(), color);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100.0f, 100.0f };
    /**
     * @tc.cases: case1. date > COUNT.
     */
    loadingProgressModifier.date_->Set(80.0f);

    EXPECT_CALL(rsCanvas, Save()).Times(2);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(2);
    loadingProgressModifier.onDraw(context);
    /**
     * @tc.cases: case1. date < COUNT.
     */
    loadingProgressModifier.date_->Set(0.0f);

    EXPECT_CALL(rsCanvas, Save()).Times(2);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(2);
    loadingProgressModifier.onDraw(context);
    /**
     * @tc.cases: case1. date == COUNT.
     */
    loadingProgressModifier.date_->Set(50.0f);

    EXPECT_CALL(rsCanvas, Save()).Times(2);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(2);
    loadingProgressModifier.onDraw(context);
}

/**
 * @tc.name: LoadingProgressModifierTest004
 * @tc.desc: Test LoadingProgressModifier onDraw function.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressModifierTest004, TestSize.Level1)
{
    LoadingProgressModifier loadingProgressModifier;
    LinearColor color;
    loadingProgressModifier.SetColor(color);
    EXPECT_EQ(loadingProgressModifier.color_->Get(), color);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100.0f, 100.0f };

    loadingProgressModifier.date_->Set(20.0f);
    loadingProgressModifier.cometTailLen_->Set(60.0f);

    EXPECT_CALL(rsCanvas, Save()).Times(2);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(2);
    loadingProgressModifier.onDraw(context);
}

/**
 * @tc.name: LoadingProgressModifierTest005
 * @tc.desc: Test LoadingProgressModifier StartTransToRecycleAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressModifierTest005, TestSize.Level1)
{
    LoadingProgressModifier loadingProgressModifier;
    LinearColor color;
    loadingProgressModifier.SetColor(color);
    EXPECT_EQ(loadingProgressModifier.color_->Get(), color);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100.0f, 100.0f };

    loadingProgressModifier.date_->Set(20.0f);
    loadingProgressModifier.cometTailLen_->Set(60.0f);

    EXPECT_CALL(rsCanvas, Save()).Times(2);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(2);
    loadingProgressModifier.onDraw(context);
    loadingProgressModifier.StartTransToRecycleAnimation();
    EXPECT_EQ(loadingProgressModifier.date_->Get(), 100.0f);
    EXPECT_EQ(loadingProgressModifier.cometSizeScale_->Get(), 0.825f);
    EXPECT_EQ(loadingProgressModifier.cometOpacity_->Get(), 0.7f);
}

/**
 * @tc.name: LoadingProgressModifierTest006
 * @tc.desc: Test LoadingProgressModifier DrawOrbit function.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressModifierTest006, TestSize.Level1)
{
    /**
     * @tc.step: step1. create LoadingProgressModifier instance.
     */
    LoadingProgressModifier loadingProgressModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100.0f, 100.0f };

    EXPECT_CALL(rsCanvas, Save()).Times(2);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(2);
    /**
     * @tc.step: step2. call SetColor method.
     * @tc.expected: loadingProgressModifier.color_ equal to Color::FOREGROUND.
     */
    LinearColor linearColor(0x00000001);
    loadingProgressModifier.SetColor(linearColor);
    EXPECT_EQ(loadingProgressModifier.color_->Get().GetValue(), Color::FOREGROUND.GetValue());
    loadingProgressModifier.onDraw(context);
}

/**
 * @tc.name: LoadingProgressModifierTest007
 * @tc.desc: Test LoadingProgressModifier DrawOrbit function.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressModifierTest007, TestSize.Level1)
{
    /**
     * @tc.step: step1. create LoadingProgressModifier instance.
     */
    LoadingProgressModifier loadingProgressModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100.0f, 100.0f };

    EXPECT_CALL(rsCanvas, Save()).Times(2);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(2);
    /**
     * @tc.step: step2. call SetColor method.
     * @tc.expected: loadingProgressModifier.color_ equal to LinearColor::WHITE.
     */
    loadingProgressModifier.SetColor(LinearColor::WHITE);
    EXPECT_EQ(loadingProgressModifier.color_->Get().GetValue(), LinearColor::WHITE.GetValue());
    loadingProgressModifier.onDraw(context);
}

/**
 * @tc.name: LoadingProgressModifierTest008
 * @tc.desc: Test LoadingProgressModifier StartTransToRecycleAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressModifierTest008, TestSize.Level1)
{
    /**
     * @tc.step: step1. set isFormRender_ is true.
     */
    MockPipelineContext::GetCurrent()->SetIsFormRender(true);
    /**
     * @tc.step: step2. create LoadingProgressModifier pointer.
     */
    auto loadingProgressModifier = AceType::MakeRefPtr<LoadingProgressModifier>();

    LinearColor color;
    loadingProgressModifier->SetColor(color);
    EXPECT_EQ(loadingProgressModifier->color_->Get(), color);
    Testing::MockCanvas rsCanvas;
    loadingProgressModifier->date_->Set(20.0f);
    loadingProgressModifier->cometTailLen_->Set(60.0f);
    /**
     * test context->IsFormRender() branch
    */
    loadingProgressModifier->StartTransToRecycleAnimation();
    /**
     * @tc.step: step2. reset date_, cometOpacity_, cometSizeScale_.
     * @tc.expected: date_, cometOpacity_, cometSizeScale_ all are nullptr.
     */
    loadingProgressModifier->date_.Reset();
    loadingProgressModifier->cometOpacity_.Reset();
    loadingProgressModifier->cometSizeScale_.Reset();
    EXPECT_EQ(loadingProgressModifier->date_, nullptr);
    EXPECT_EQ(loadingProgressModifier->cometOpacity_, nullptr);
    EXPECT_EQ(loadingProgressModifier->cometSizeScale_, nullptr);
    loadingProgressModifier->StartTransToRecycleAnimation();
}

/**
 * @tc.name: LoadingProgressModifierTest009
 * @tc.desc: Test LoadingProgressModifier StartRecycleCometAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressModifierTest009, TestSize.Level1)
{
    /**
     * @tc.step: step1. create LoadingProgressModifier pointer.
     */
    auto loadingProgressModifier = AceType::MakeRefPtr<LoadingProgressModifier>();
    /**
     * @tc.step: step2. reset cometSizeScale_.
     * @tc.expected: cometSizeScale_ is nullptr.
     */
    loadingProgressModifier->cometSizeScale_.Reset();
    EXPECT_EQ(loadingProgressModifier->cometSizeScale_, nullptr);
    loadingProgressModifier->StartRecycleCometAnimation();
}

/**
 * @tc.name: LoadingProgressModifierTest010
 * @tc.desc: Test LoadingProgressModifier DrawRing function. ColorMode = DARK
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressModifierTest010, TestSize.Level1)
{
    SystemProperties::SetColorMode(ColorMode::DARK);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->loadingColor_ = COLOR_DEFAULT;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    LoadingProgressModifier loadingProgressModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context = { rsCanvas, 10.0f, 10.0f };
    RingParam ringParam;
    /**
     * @tc.cases: case1. ringColor == defaultColor.
     */
    loadingProgressModifier.SetColor(LinearColor(COLOR_DEFAULT));
    EXPECT_CALL(rsCanvas, Save()).Times(2);
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(2);
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(2);
    loadingProgressModifier.DrawRing(context, ringParam);
    /**
     * @tc.cases: case2. ringColor != defaultColor.
     */
    loadingProgressModifier.SetColor(LinearColor(Color::BLUE));
    EXPECT_CALL(rsCanvas, Save()).Times(2);
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(2);
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(2);
    loadingProgressModifier.DrawRing(context, ringParam);
}

/**
 * @tc.name: LoadingProgressModifierTest011
 * @tc.desc: Test LoadingProgressModifier DrawOrbit function.ColorMode = DARK
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressTestNg, LoadingProgressModifierTest011, TestSize.Level1)
{
    SystemProperties::SetColorMode(ColorMode::DARK);
    LoadingProgressModifier loadingProgressModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    /**
     * @tc.cases: case1. date > 0 && date < COUNT.
     */
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    CometParam cometParam;
    loadingProgressModifier.DrawOrbit(context, cometParam, 1.0f, 2.0f);
    /**
     * @tc.cases: case2. date > 0 && date >= COUNT.
     */
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    loadingProgressModifier.DrawOrbit(context, cometParam, 50.0f, 2.0f);
    /**
     * @tc.cases: case3. date <= 0.
     */
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    loadingProgressModifier.DrawOrbit(context, cometParam, .0f, 2.0f);
}
} // namespace OHOS::Ace::NG
