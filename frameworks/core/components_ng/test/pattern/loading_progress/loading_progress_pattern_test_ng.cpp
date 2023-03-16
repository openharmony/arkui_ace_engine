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
#include "core/components_ng/pattern/loading_progress/loading_progress_base.h"

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_layout_algorithm.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_layout_property.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Color COLOR_DEFUALT = Color::RED;
} // namespace

class LoadingProgressPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateLoadingProgressNode(const Color& color);
};

void LoadingProgressPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void LoadingProgressPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> LoadingProgressPatternTestNg::CreateLoadingProgressNode(const Color& color)
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
HWTEST_F(LoadingProgressPatternTestNg, LoadingProgressFrameNodeCreator001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFUALT);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LoadingProgressPaintProperty> renderProperty = frameNode->GetPaintProperty<LoadingProgressPaintProperty>();
    EXPECT_NE(renderProperty, nullptr);
    EXPECT_EQ(renderProperty->GetColorValue(), COLOR_DEFUALT);
}

/**
 * @tc.name: LoadingProgressLayoutAlgorithm001
 * @tc.desc: Test MeasureContent function of loadingProgressNode.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressPatternTestNg, LoadingProgressLayoutAlgorithm001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFUALT);
    EXPECT_NE(frameNode, nullptr);
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
    layoutConstraint.maxSize = SizeF(MAXSIZE_WIDTH, MAXSIZE_HEIGHT);
    auto size1 = layoutAlgorithm.MeasureContent(layoutConstraint, nullptr);
    EXPECT_FALSE(size1 == std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(MAXSIZE_WIDTH, MAXSIZE_HEIGHT));
    /**
     * @tc.cases: case2. When father selfIdealSize is valid, LoadingProgressLayoutAlgorithm will calculate
     *                   contentSize with maxSize LayoutConstraint and selfIdealSize.
     */
    layoutConstraint.selfIdealSize.width_ = SELFSIZE_WIDTH;
    layoutConstraint.selfIdealSize.height_ = SELFSIZE_HEIGHT;
    auto size2 = layoutAlgorithm.MeasureContent(layoutConstraint, nullptr);
    EXPECT_FALSE(size2 == std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(fmin(SELFSIZE_WIDTH, MAXSIZE_WIDTH), fmin(SELFSIZE_HEIGHT, MAXSIZE_HEIGHT)));
}

/**
 * @tc.name: LoadingProgressPatternTest001
 * @tc.desc: Test Pattern OnDirtyLayoutWrapperSwap function of loadingProgress.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressPatternTestNg, LoadingProgressPatternTest001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFUALT);
    EXPECT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    EXPECT_TRUE(loadingProgressPattern != nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(nullptr, nullptr, nullptr);
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
 * @tc.name: LoadingProgressPaintMethodTest001
 * @tc.desc: Test LoadingProgressPaintMethod function of loadingProgress.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressPatternTestNg, LoadingProgressPaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paintMethod.
     */
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFUALT);
    EXPECT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    EXPECT_TRUE(loadingProgressPattern != nullptr);
    auto paintMethod =
        AceType::DynamicCast<LoadingProgressPaintMethod>(loadingProgressPattern->CreateNodePaintMethod());
    EXPECT_TRUE(paintMethod != nullptr);
    EXPECT_TRUE(loadingProgressPattern->CreateNodePaintMethod() != nullptr);
    /**
     * @tc.steps: step2. test create PaintWrapper and ProgressTheme.
     */
    PaintWrapper paintWrapper(nullptr, nullptr, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->loadingColor_ = COLOR_DEFUALT;
    /**
     * @tc.steps: step3. test UpdateContentModifier function.
     * @tc.cases: case1. PaintWrapper has no loadingProgressPaintProperty and modifier will use default Color.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(progressTheme));
    paintMethod->UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(paintMethod->color_, Color::BLUE);
    /**
     * @tc.cases: case2. LoadingProgressPaintProperty has no Color property and modifier will use Theme Color.
     */
    auto loadingProgressPaintProperty = loadingProgressPattern->GetPaintProperty<LoadingProgressPaintProperty>();
    EXPECT_TRUE(loadingProgressPaintProperty != nullptr);
    PaintWrapper paintWrapper2(nullptr, nullptr, loadingProgressPaintProperty);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(progressTheme));
    paintMethod->UpdateContentModifier(&paintWrapper2);
    EXPECT_EQ(paintMethod->color_, COLOR_DEFUALT);
}

/**
 * @tc.name: LoadingProgressModifierTest001
 * @tc.desc: Test LoadingProgressModifier DrawRing function.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressPatternTestNg, LoadingProgressModifierTest001, TestSize.Level1)
{
    LoadingProgressModifier loadingProgressModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context = { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    RingParam ringParam;
    loadingProgressModifier.DrawRing(context, ringParam);
}

/**
 * @tc.name: LoadingProgressModifierTest002
 * @tc.desc: Test LoadingProgressModifier DrawOrbit function.
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressPatternTestNg, LoadingProgressModifierTest002, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
