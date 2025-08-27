/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "progress_test_ng.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_container.h"

namespace OHOS::Ace::NG {
namespace {
DirtySwapConfig config;
ProgressModelNG progressModel;
RefPtr<ProgressTheme> progressTheme;
RefPtr<ProgressTheme> progressThemeWrapper;
RefPtr<MockThemeManager> themeManager;

void InitCanvas(Testing::MockCanvas& canvas)
{
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));
}
} // namespace

void ProgressTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    testing::FLAGS_gmock_verbose = "error";
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_PROGRESS);
    progressTheme = ProgressTheme::Builder().Build(themeConstants);
    progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->trackThickness_ = TEST_PROGRESS_THICKNESS;
    progressTheme->scaleLength_ = TEST_PROGRESS_STROKE_WIDTH;
    progressTheme->ringDiameter_ = TEST_PROGRESS_DEFAULT_DIAMETER;
    progressTheme->trackBgColor_ = BG_COLOR;
    progressTheme->trackSelectedColor_ = FRONT_COLOR;
    progressTheme->scaleNumber_ = SCALE_COUNT;
    progressTheme->scaleWidth_ = TEST_PROGRESS_SCALE_WIDTH;
    progressThemeWrapper = ProgressThemeWrapper::WrapperBuilder().Build(themeConstants);
    progressThemeWrapper->trackThickness_ = TEST_PROGRESS_THICKNESS;
    progressThemeWrapper->scaleLength_ = TEST_PROGRESS_STROKE_WIDTH;
    progressThemeWrapper->ringDiameter_ = TEST_PROGRESS_DEFAULT_DIAMETER;
    progressThemeWrapper->trackBgColor_ = BG_COLOR;
    progressThemeWrapper->trackSelectedColor_ = FRONT_COLOR;
    progressThemeWrapper->scaleNumber_ = SCALE_COUNT;
    progressThemeWrapper->scaleWidth_ = TEST_PROGRESS_SCALE_WIDTH;
}

void ProgressTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    progressTheme = nullptr;
    themeManager = nullptr;
}

void ProgressTestNg::SetUp()
{
    MockContainer::SetUp();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(progressThemeWrapper));
}

void ProgressTestNg::TearDown()
{
    RemoveFromStageNode();
    MockContainer::TearDown();
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    ClearOldNodes();  // Each testcase will create new node at begin
}

void ProgressTestNg::GetProgress()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ProgressPattern>();
    eventHub_ = frameNode_->GetEventHub<EventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ProgressLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ProgressAccessibilityProperty>();
}

ProgressModelNG ProgressTestNg::CreateProgress(double value, double max, NG::ProgressType type)
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ProgressModelNG model;
    model.Create(0.0, value, 0.0, max, type);
    ViewAbstract::SetWidth(CalcLength(PROGRESS_COMPONENT_WIDTH));
    ViewAbstract::SetHeight(CalcLength(PROGRESS_COMPONENT_HEIGHT));
    GetProgress();
    return model;
}

RefPtr<ProgressModifier> ProgressTestNg::CreateProgressModifier()
{
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS_2, 100.0, PROGRESS_TYPE_CAPSULE);
    auto progressNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    CHECK_NULL_RETURN(progressNode, nullptr);
    FrameNode* frameNode = Referenced::RawPtr(progressNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto progressPattern = progressNode->GetPattern<ProgressPattern>();
    CHECK_NULL_RETURN(progressPattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    progressPattern->progressModifier_ = AceType::MakeRefPtr<ProgressModifier>(frameNode_);
    return progressPattern->progressModifier_;
}

/**
 * @tc.name: ProgressCreate001
 * @tc.desc: Test all the pattern of progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressCreate001, TestSize.Level0)
{
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone();
    RefPtr<ProgressLayoutAlgorithm> progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, nullptr, nullptr);
    pattern_->OnAttachToFrameNode();
    bool skipMeasures[2] = { false, true };
    for (int32_t i = 0; i < 2; ++i) {
        for (int32_t j = 0; j < 2; ++j) {
            config.skipMeasure = skipMeasures[i];
            auto layoutAlgorithmWrapper =
                AceType::MakeRefPtr<LayoutAlgorithmWrapper>(progressLayoutAlgorithm, skipMeasures[i]);
            layoutWrapperNode->SetLayoutAlgorithm(layoutAlgorithmWrapper);
            layoutWrapperNode->skipMeasureContent_ = skipMeasures[j];
            auto isSwap = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapperNode, config);
            EXPECT_EQ(isSwap, !(skipMeasures[i] || skipMeasures[j]));
        }
    }
}

/**
 * @tc.name: ProgressLayoutAlgorithm001
 * @tc.desc: Test ProgressLayoutAlgorithm without theme.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressLayoutAlgorithm001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone();

    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to progress frameNode_ layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);

    /**
     * @tc.steps: step5. do linear progress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(nullptr));
    auto progressPattern = frameNode_->GetPattern();
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);

    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_LINEAR);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), DEFAULT_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), DEFAULT_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_HEIGHT);
}

/**
 * @tc.name: ProgressLayoutAlgorithm002
 * @tc.desc: Test ProgressLayoutAlgorithm strokeWidth and RingDiameter with theme.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressLayoutAlgorithm002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create progress layout property and ProgressLayoutAlgorithm.
     */
    auto layoutProperty_ = AceType::MakeRefPtr<ProgressLayoutProperty>();
    layoutProperty_->UpdateType(PROGRESS_TYPE_SCALE);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, layoutProperty_);
    /**
     * @tc.steps: step2. get strokeWidth from theme, and return width and height according to RingDiameter.
     */
    auto progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->trackThickness_ = TEST_PROGRESS_STROKE_WIDTH;
    progressTheme->ringDiameter_ = DEFAULT_RING_DIAMETER;
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_EQ(size, std::nullopt);
}

/**
 * @tc.name: LinearProgressCreator001
 * @tc.desc: Test all the properties of linear progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, LinearProgressCreator001, TestSize.Level0)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    model.SetStrokeWidth(STROKE_WIDTH);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    CreateDone();
    auto json = JsonUtil::Create(true);
    paintProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to progress frameNode_ layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);

    /**
     * @tc.steps: step5. do linear progress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    auto progressPattern = frameNode_->GetPattern();
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_LINEAR);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_MAXSIZE_WIDTH);

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);

    contentConstraint.selfIdealSize.SetWidth(LARG_PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(LARG_PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), LARG_PROGRESS_COMPONENT_WIDTH);
}

/**
 * @tc.name: LinearProgressCreator002
 * @tc.desc: Test all the properties of linear progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, LinearProgressCreator002, TestSize.Level0)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    model.SetStrokeWidth(LARG_STROKE_WIDTH);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    CreateDone();

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to progress frameNode_ layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);

    /**
     * @tc.steps: step5. do linear progress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    auto progressPattern = frameNode_->GetPattern();
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_LINEAR);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), LARG_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), LARG_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_MAXSIZE_WIDTH);

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size.value(), SizeF(PROGRESS_COMPONENT_WIDTH, PROGRESS_COMPONENT_HEIGHT));
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), LARG_STROKE_WIDTH.ConvertToPx());
}

/**
 * @tc.name: RingProgressCreator001
 * @tc.desc: Test all the properties of ring progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, RingProgressCreator001, TestSize.Level1)
{
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    gradient.AddColor(gradientColorStart);

    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    model.SetStrokeWidth(STROKE_WIDTH);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    model.SetPaintShadow(true);
    model.SetProgressStatus(ProgressStatus::PROGRESSING);
    model.SetGradientColor(gradient);
    CreateDone();

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    /**
     * @tc.steps: step4. add layoutWrapper to progress frameNode_ layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);
    /**
     * @tc.steps: step5. do ring progress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    auto json = JsonUtil::Create(true);
    paintProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_RING);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), DEFAULT_RING_DIAMETER.ConvertToPx());
    EXPECT_EQ(size->Width(), DEFAULT_RING_DIAMETER.ConvertToPx());

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_WIDTH);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);

    LayoutConstraintF contentConstraint2;
    contentConstraint2.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint2.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    contentConstraint2.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint2, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_HEIGHT);

    contentConstraint2.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint2, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);
}

/**
 * @tc.name: ScaleProgressFrameNodeCreator001
 * @tc.desc: Test all the properties of scale progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ScaleProgressFrameNodeCreator001, TestSize.Level0)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_SCALE);
    model.SetStrokeWidth(STROKE_WIDTH);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    model.SetScaleWidth(SCALE_WIDTH);
    model.SetScaleCount(SCALE_COUNT);
    model.SetBorderColor(BORDER_COLOR);
    CreateDone();

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to progress frameNode_ layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);

    /**
     * @tc.steps: step5. do ring progress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_SCALE);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), TEST_PROGRESS_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);
}

/**
 * @tc.name: CapsuleProgressCreator001
 * @tc.desc: Test all the properties of Capsule type progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, CapsuleProgressCreator001, TestSize.Level0)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    model.SetStrokeWidth(STROKE_WIDTH);
    CreateDone();

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to progress frameNode_ layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);

    /**
     * @tc.steps: step5. do capsule progress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    auto progressPattern = frameNode_->GetPattern();
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_CAPSULE);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), DEFAULT_CAPSULE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_MAXSIZE_WIDTH);

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size->Height(), DEFAULT_CAPSULE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);

    LayoutConstraintF contentConstraint2;
    contentConstraint2.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint2.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    contentConstraint2.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint2, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_MAXSIZE_WIDTH);
}

/**
 * @tc.name: ProgressPaintProperty001
 * @tc.desc: Test progress_paint_property.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPaintProperty001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(PROGRESS_MODEL_NG_MIN, PROGRESS_MODEL_NG_VALUE, PROGRESS_MODEL_NG_CACHEDVALUE,
        PROGRESS_MODEL_NG_MAX, PROGRESS_TYPE_LINEAR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. Create the paintProperty_.Call function .
     * @tc.expected: step2. Check the property after Clone and Reset.
     */
    RefPtr<ProgressPaintProperty> progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    progressPaintProperty->Clone();
    auto cloneMaxValue = progressPaintProperty->GetMaxValue();
    EXPECT_EQ(cloneMaxValue, PROGRESS_MODEL_NG_MAX);
    progressPaintProperty->Reset();
    auto resetMaxValue = progressPaintProperty->GetMaxValue();
    EXPECT_NE(resetMaxValue, PROGRESS_MODEL_NG_MAX);
}

/**
 * @tc.name: ProgressMaskPropertyTestNg001
 * @tc.desc: Test progress mask property
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressMaskPropertyTestNg001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create the ProgressMaskProperty.Set the properties of ProgressMaskProperty.
     * @tc.expected: step1. Check the properties were set successfully.
     */
    ProgressMaskProperty progressMaskProperty;
    progressMaskProperty.SetValue(VALUE_OF_SET_VALUE);
    auto progressMaskValue = progressMaskProperty.GetValue();
    EXPECT_EQ(progressMaskValue, VALUE_OF_SET_VALUE);
    progressMaskProperty.SetMaxValue(VALUE_OF_SET_VALUE);
    auto progressMaskMaxValue = progressMaskProperty.GetMaxValue();
    EXPECT_EQ(progressMaskMaxValue, VALUE_OF_SET_VALUE);
    progressMaskProperty.SetColor(TEST_COLOR);
    auto progressMaskColor = progressMaskProperty.GetColor();
    EXPECT_EQ(progressMaskColor, TEST_COLOR);
    progressMaskProperty.SetEnableBreathe(false);
    auto progressMaskEnableBreathe = progressMaskProperty.GetEnableBreathe();
    EXPECT_FALSE(progressMaskEnableBreathe);
}

/**
 * @tc.name: ProgressAccessibilityPropertyTestNg001
 * @tc.desc: Test the RangeInfo Property of progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressAccessibilityPropertyTestNg001, TestSize.Level0)
{
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone();
    paintProperty_->UpdateMaxValue(MAX_VALUE_OF_PROGRESS);
    paintProperty_->UpdateValue(VALUE_OF_PROGRESS);
    EXPECT_TRUE(accessibilityProperty_->HasRange());
    EXPECT_EQ(accessibilityProperty_->GetAccessibilityValue().min, 0);
    EXPECT_EQ(accessibilityProperty_->GetAccessibilityValue().max, MAX_VALUE_OF_PROGRESS);
    EXPECT_EQ(accessibilityProperty_->GetAccessibilityValue().current, VALUE_OF_PROGRESS);
}

/**
 * @tc.name: ProgressAccessibilityPropertyTestNg002
 * @tc.desc: Test the GetText Property of progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressAccessibilityPropertyTestNg002, TestSize.Level0)
{
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone();
    paintProperty_->UpdateValue(VALUE_OF_PROGRESS);
    EXPECT_EQ(accessibilityProperty_->GetText(), std::to_string(VALUE_OF_PROGRESS));
}

/**
 * @tc.name: ProgressPattern001
 * @tc.desc: Test the TouchEvent of progress, TouchType is DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPattern001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create capsule progress and set add touchEvent.
     * @tc.expected: step1. Check the touchEvent is enable.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    model.SetBackgroundColor(Color::BLUE);
    CreateDone();
    eventHub_->SetEnabled(false);
    pattern_->OnModifyDone();
    TouchEventInfo info("touch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    pattern_->touchListener_->GetTouchEventCallback()(info);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(PROGRESS_COMPONENT_MAXSIZE_WIDTH, PROGRESS_COMPONENT_MAXSIZE_HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));
    frameNode_->SetGeometryNode(geometryNode);
    RoundRect focusRect;
    pattern_->GetInnerFocusPaintRect(focusRect);
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
        PROGRESS_COMPONENT_MAXSIZE_WIDTH * 0.5 + DEFAULT_SPACE.ConvertToPx());
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y,
        PROGRESS_COMPONENT_MAXSIZE_WIDTH * 0.5 + DEFAULT_SPACE.ConvertToPx());
    EXPECT_FALSE(eventHub_->IsEnabled());

    /**
     * @tc.steps: step2. Create linear progress and set remove touchEvent.
     * @tc.expected: step2. Check the touchEvent is removed.
     */
    model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    model.SetBackgroundColor(Color::BLUE);
    CreateDone();
    auto touchCallback = [](TouchEventInfo& info) {};
    pattern_->touchListener_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    pattern_->OnModifyDone();
    ASSERT_EQ(pattern_->touchListener_, nullptr);
}

/**
 * @tc.name: ProgressPattern002
 * @tc.desc: Test the TouchEvent of progress, TouchType is UP.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPattern002, TestSize.Level0)
{
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    model.SetBackgroundColor(Color::BLUE);
    CreateDone();
    pattern_->OnModifyDone();
    TouchEventInfo info("touch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    pattern_->touchListener_->GetTouchEventCallback()(info);
    EXPECT_TRUE(eventHub_->IsEnabled());
}

/**
 * @tc.name: ProgressPattern003
 * @tc.desc: Test the TouchEvent of progress, TouchType is CANCEL.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPattern003, TestSize.Level0)
{
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    model.SetBackgroundColor(Color::BLUE);
    CreateDone();
    pattern_->OnModifyDone();
    TouchEventInfo info("touch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::CANCEL);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    pattern_->touchListener_->GetTouchEventCallback()(info);
    EXPECT_TRUE(eventHub_->IsEnabled());
}

/**
 * @tc.name: ProgressPattern004
 * @tc.desc: Test ToJsonValue of ring progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPattern004, TestSize.Level0)
{
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    /**
     * @tc.steps: step1. create testProperty and set properties of ring progress.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    model.SetPaintShadow(true);
    model.SetProgressStatus(ProgressStatus::PROGRESSING);
    model.SetGradientColor(gradient);
    CreateDone();
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    paintProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);

    model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    model.SetProgressStatus(ProgressStatus::LOADING);
    CreateDone();
    pattern_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: CapsuleProgressMeasure001
 * @tc.desc: Test the measure of Capsule type progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, CapsuleProgressMeasure001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    CreateDone();

    /**
     * @tc.steps: step2. Create the progressLayoutAlgorithm.
     * @tc.expected: step2. Check the progressLayoutAlgorithm created successfully.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();

    /**
     * @tc.steps: step3. Call the function MeasureContent.
     * @tc.expected: step3. Check the result of MeasureContent.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(100, 50));
    RefPtr<LayoutWrapperNode> textWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode, textNode->GetLayoutProperty());
    layoutWrapper.AppendChild(textWrapper);
    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);
}

/**
 * @tc.name: CapsuleProgressMeasure002
 * @tc.desc: Test the measure of Capsule type progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, CapsuleProgressMeasure002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    CreateDone();

    /**
     * @tc.steps: step2. Create the progressLayoutAlgorithm.
     * @tc.expected: step2. Check the progressLayoutAlgorithm created successfully.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();

    /**
     * @tc.steps: step3. Call the function MeasureContent.
     * @tc.expected: step3. Check the result of MeasureContent.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(500, 100));
    RefPtr<LayoutWrapperNode> textWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode, textNode->GetLayoutProperty());
    layoutWrapper.AppendChild(textWrapper);
    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);
}
/**
 * @tc.name: CapsuleProgressMeasure003
 * @tc.desc: Test all the properties of Capsule type progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, CapsuleProgressMeasure003, TestSize.Level0)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    model.SetStrokeWidth(STROKE_WIDTH);
    CreateDone();

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to progress frameNode_ layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);

    /**
     * @tc.steps: step5. do capsule progress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    auto progressPattern = frameNode_->GetPattern();
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_CAPSULE);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), DEFAULT_CAPSULE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_MAXSIZE_WIDTH);

    LayoutConstraintF contentConstraintChild;
    contentConstraintChild.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    auto childsize = progressLayoutAlgorithm->MeasureContent(contentConstraintChild, &layoutWrapper);
    ASSERT_NE(childsize, std::nullopt);
    EXPECT_EQ(childsize->Height(), size->Height());
    EXPECT_EQ(childsize->Width(), size->Width());
}

/**
 * @tc.name: ProgressSetValue002
 * @tc.desc: Test function about setting value.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressSetValue002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create Progress when Version is VERSION_NINE.
     * @tc.expected: step1. Check the paintProperty value.
     */
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS_2, 100.0, PROGRESS_TYPE_CAPSULE);
    model.SetStrokeWidth(LARG_STROKE_WIDTH);
    model.SetStrokeRadius(LARG_STROKE_WIDTH / 5.0);
    model.SetShowText(true);
    CreateDone();
    EXPECT_FALSE(paintProperty_->HasColor());
    EXPECT_FALSE(paintProperty_->HasBackgroundColor());
    EXPECT_FALSE(paintProperty_->HasBorderColor());

    /**
     * @tc.steps: step2. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step2. Check the ProgressModifier property value.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
    model = CreateProgress(VALUE_OF_PROGRESS_2, 100.0, PROGRESS_TYPE_CAPSULE);
    model.SetStrokeWidth(LARG_STROKE_WIDTH);
    model.SetStrokeRadius(LARG_STROKE_WIDTH / 5.0);
    model.SetShowText(true);
    CreateDone();
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto* stack = ViewStackProcessor::GetInstance();
    stack->Push(frameNode_);
    pattern_->SetTextFromUser(true);
    progressModel.SetValue(10.0);
    EXPECT_DOUBLE_EQ(paintProperty_->GetValueValue(0.0), 10.0);

    pattern_->SetTextFromUser(false);
    progressModel.SetValue(10.0);
    EXPECT_EQ(textLayoutProperty->GetContentValue(u""), u"10%");
    EXPECT_EQ(paintProperty_->GetTextValue(""), "10%");
    progressModel.SetTextDefaultStyle(textNode, VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS);
    EXPECT_EQ(StringUtils::Str8ToStr16(paintProperty_->GetTextValue("")), textLayoutProperty->GetContentValue(u""));

    paintProperty_->UpdateEnableShowText(false);
    progressModel.SetValue(20.0);
    EXPECT_EQ(textLayoutProperty->GetContentValue(u""), u"");
    EXPECT_EQ(paintProperty_->GetTextValue(""), "");
    progressModel.SetTextDefaultStyle(textNode, VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS);
    EXPECT_EQ(StringUtils::Str8ToStr16(paintProperty_->GetTextValue("")), textLayoutProperty->GetContentValue(u""));
}

/**
 * @tc.name: ProgressPattern005
 * @tc.desc: Test the TouchEvent of progress, TouchType is CANCEL.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPattern005, TestSize.Level0)
{
    /**
     * @tc.steps:  Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1.  Check the ProgressModifier property value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, 101.0, PROGRESS_TYPE_CAPSULE);
    model.SetStrokeWidth(LARG_STROKE_WIDTH);
    model.SetStrokeRadius(0.0_vp);
    model.SetShowText(true);
    model.SetBackgroundColor(Color::GRAY);
    CreateDone();

    /**
     * @tc.steps: step2. set ProgressModifier property.
     * @tc.expected: step2. Check the ProgressModifier property value.
     */
    TouchEventInfo info("touch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::UNKNOWN);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    pattern_->touchListener_->GetTouchEventCallback()(info);

    auto json = JsonUtil::Create(true);
    std::vector<std::string> defaultFamily = { "Sans" };
    std::vector<std::string> fontFamilyVector = paintProperty_->GetFontFamilyValue(defaultFamily);
    fontFamilyVector.push_back("test");
    paintProperty_->UpdateFontFamily(fontFamilyVector);
    paintProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);

    paintProperty_->UpdateProgressType(PROGRESS_TYPE_LINEAR);
    layoutProperty_->UpdateType(PROGRESS_TYPE_LINEAR);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->touchListener_, nullptr);
}

/**
 * @tc.name: ProgressLayoutAlgorithm003
 * @tc.desc: Test ProgressLayoutAlgorithm without theme.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressLayoutAlgorithm003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_MOON);
    CreateDone();

    /**
     * @tc.steps: step2. Create the progressLayoutAlgorithm.
     * @tc.expected: step2. Check the progressLayoutAlgorithm created successfully.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.percentReference.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);

    /**
     * @tc.steps: step3. Call the function MeasureContent.
     * @tc.expected: step3. Check the result of MeasureContent.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(nullptr));
    auto layoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->GetType(), PROGRESS_TYPE_MOON);
    EXPECT_EQ(layoutAlgorithm->GetStrokeWidth(), DEFAULT_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);
}

/**
 * @tc.name: ProgressLayoutAlgorithm004
 * @tc.desc: Test ProgressLayoutAlgorithm without theme.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressLayoutAlgorithm004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    CreateDone();

    /**
     * @tc.steps: step2. Create the progressLayoutAlgorithm.
     * @tc.expected: step2. Check the progressLayoutAlgorithm created successfully.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(nullptr));
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);
    auto layoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();

    /**
     * @tc.steps: step3. Call the function MeasureContent.
     * @tc.expected: step3. Check the result of MeasureContent.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    std::vector<ProgressType> typeVec = { PROGRESS_TYPE_CAPSULE, PROGRESS_TYPE_MOON, PROGRESS_TYPE_RING,
        PROGRESS_TYPE_SCALE, PROGRESS_TYPE_LINEAR };

    for (const auto& it : typeVec) {
        layoutProperty_->UpdateType(it);
        auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
        EXPECT_EQ(layoutAlgorithm->GetType(), it);
        EXPECT_EQ(layoutAlgorithm->GetStrokeWidth(), DEFAULT_STROKE_WIDTH.ConvertToPx());
        EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
        EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);
    }

    contentConstraint.Reset();
    layoutProperty_->UpdateType(PROGRESS_TYPE_CAPSULE);
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->GetType(), PROGRESS_TYPE_CAPSULE);
    EXPECT_EQ(layoutAlgorithm->GetStrokeWidth(), DEFAULT_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), DEFAULT_RING_DIAMETER.ConvertToPx());
    EXPECT_EQ(size->Width(), DEFAULT_RING_DIAMETER.ConvertToPx());
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
}

/**
 * @tc.name: ProgressLayoutAlgorithm005
 * @tc.desc: Test ProgressLayoutAlgorithm without theme.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressLayoutAlgorithm005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    CreateDone();

    /**
     * @tc.steps: step2. Create the progressLayoutAlgorithm.
     * @tc.expected: step2. Check the progressLayoutAlgorithm created successfully.
     */
    LayoutWrapperNode layoutWrapper(frameNode_, nullptr, layoutProperty_);
    auto layoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();

    /**
     * @tc.steps: step3. Call the function MeasureContent.
     * @tc.expected: step3. Check the result of MeasureContent.
     */
    LayoutConstraintF contentConstraint;
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->GetType(), PROGRESS_TYPE_RING);
    EXPECT_EQ(layoutAlgorithm->GetStrokeWidth(), TEST_PROGRESS_THICKNESS.ConvertToPx());
    EXPECT_EQ(size->Height(), TEST_PROGRESS_DEFAULT_DIAMETER.ConvertToPx());
    EXPECT_EQ(size->Width(), TEST_PROGRESS_DEFAULT_DIAMETER.ConvertToPx());

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->GetStrokeWidth(), TEST_PROGRESS_THICKNESS.ConvertToPx());
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_WIDTH);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);

    contentConstraint.Reset();
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    layoutProperty_->UpdateType(PROGRESS_TYPE_SCALE);
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->GetType(), PROGRESS_TYPE_SCALE);
    EXPECT_EQ(layoutAlgorithm->GetStrokeWidth(), TEST_PROGRESS_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_HEIGHT);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
}

/**
 * @tc.name: ProgressPatternTest000
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternTest000, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Init Progress node
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone();
    auto node = [](ProgressConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.value_, VALUE_OF_PROGRESS);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern_->SetBuilderFunc(node);
    pattern_->BuildContentModifierNode();
}

/**
 * @tc.name: ProgressPrivacySensitiveTest001
 * @tc.desc: Test ProgressPrivacySensitive change.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPrivacySensitiveTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(5.0, 10.0, 10.0, 20.0, PROGRESS_TYPE_CAPSULE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    ASSERT_NE(textHost, nullptr);
    auto textPattern = textHost->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. change privacy sensitive and check status.
     */
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    pattern->OnSensitiveStyleChange(false);
    EXPECT_EQ(progressPaintProperty->GetIsSensitive().value_or(false), false);
    EXPECT_EQ(textPattern->IsSensitiveEnable(), false);
    pattern->OnSensitiveStyleChange(true);
    EXPECT_EQ(progressPaintProperty->GetIsSensitive().value_or(false), true);
    EXPECT_EQ(textPattern->IsSensitiveEnable(), true);
}

/**
 * @tc.name: ProgressIsRightToLeftTest001
 * @tc.desc: Test Progress OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressIsRightToLeftTest001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<ProgressPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->progressModifier_ = AceType::MakeRefPtr<ProgressModifier>(frameNode_);
    auto modifier = pattern->progressModifier_;
    EXPECT_FALSE(modifier == nullptr);
    /**
     * @tc.steps: step1. set to RightToLeft mode, call OnLanguageConfigurationUpdate, then get current isRightToLeft_.
     * @tc.expected: check whether the isRightToLeft_ is correct.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    pattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(modifier->isRightToLeft_->Get(), true);

    /**
     * @tc.steps: step2. set to LeftToRight mode, call OnLanguageConfigurationUpdate, then get current isRightToLeft_.
     * @tc.expected: check whether the isRightToLeft_ is correct.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    pattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(modifier->isRightToLeft_->Get(), false);
}

/**
 * @tc.name: ProgressBorderRadiusTest001
 * @tc.desc: Test function border radius setting value.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressBorderRadiusTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create the progress model.
     * @tc.expected: step1. Check the progress model.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS_2, 100.0, PROGRESS_TYPE_CAPSULE);
    auto progressNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(progressNode, nullptr);
    FrameNode* frameNode = Referenced::RawPtr(progressNode);
    CHECK_NULL_VOID(frameNode);
    auto progressPattern = progressNode->GetPattern<ProgressPattern>();
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPattern, nullptr);
    // call UpdateProgressItemChildren
    progressPattern->OnModifyDone();

    /**
     * @tc.steps: step2. Set borderRadiu value.
     * @tc.expected: step2. Check the borderRadiu value.
     */
    CalcDimension borderRadius = CalcDimension(10.0, DimensionUnit::VP);
    model.SetBorderRadius(borderRadius);
    progressPattern->OnModifyDone();
    auto borderRadiusRet = paintProperty->GetBorderRadiusValue(Dimension(1.0f, DimensionUnit::PX));
    EXPECT_EQ(borderRadiusRet.Value(), 1.0f);

    /**
     * @tc.steps: step3. Reset borderRadiu value.
     * @tc.expected: step3. Check the borderRadiu value.
     */
    model.ResetBorderRadius();
    progressPattern->OnModifyDone();
    borderRadiusRet = paintProperty->GetBorderRadiusValue(Dimension(1.0f, DimensionUnit::PX));
    EXPECT_EQ(borderRadiusRet.Value(), 1.0f);

    /**
     * @tc.steps: step4. Set borderRadiu value.
     * @tc.expected: step4. Check the borderRadiu value.
     */
    borderRadius = CalcDimension(20.0, DimensionUnit::VP);
    model.SetBorderRadius(frameNode, borderRadius);
    progressPattern->OnModifyDone();
    borderRadiusRet = paintProperty->GetBorderRadiusValue(Dimension(1.0f, DimensionUnit::PX));
    EXPECT_EQ(borderRadiusRet.Value(), 20.0f);

    /**
     * @tc.steps: step5. Reset borderRadiu value.
     * @tc.expected: step5. Check the borderRadiu value.
     */
    model.ResetBorderRadius(frameNode);
    progressPattern->OnModifyDone();
    borderRadiusRet = paintProperty->GetBorderRadiusValue(Dimension(1.0f, DimensionUnit::PX));
    EXPECT_EQ(borderRadiusRet.Value(), 1.0f);
}

/**
 * @tc.name: ProgressBorderRadiusTest002
 * @tc.desc: Test function border radius setting different units.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressBorderRadiusTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the progress model.
     * @tc.expected: step1. Check the progress model.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS_2, 100.0, PROGRESS_TYPE_CAPSULE);
    auto progressNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(progressNode, nullptr);
    FrameNode* frameNode = Referenced::RawPtr(progressNode);
    CHECK_NULL_VOID(frameNode);
    auto progressPattern = progressNode->GetPattern<ProgressPattern>();
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPattern, nullptr);
    // call UpdateProgressItemChildren
    progressPattern->OnModifyDone();

    /**
     * @tc.steps: step2. Set borderRadiu unit as vp.
     * @tc.expected: step2. Check the borderRadiu value and unit.
     */
    auto borderRadius = CalcDimension(20.0, DimensionUnit::VP);
    model.SetBorderRadius(frameNode, borderRadius);
    progressPattern->OnModifyDone();
    auto borderRadiusRet = paintProperty->GetBorderRadiusValue(Dimension(1.0f, DimensionUnit::PX));
    EXPECT_EQ(borderRadiusRet.Value(), 20.0f);
    EXPECT_EQ(borderRadiusRet.Unit(), DimensionUnit::VP);

    /**
     * @tc.steps: step3. Set borderRadiu unit as px.
     * @tc.expected: step3. Check the borderRadiu value and unit.
     */
    borderRadius = CalcDimension(20.0, DimensionUnit::PX);
    model.SetBorderRadius(frameNode, borderRadius);
    progressPattern->OnModifyDone();
    borderRadiusRet = paintProperty->GetBorderRadiusValue(Dimension(1.0f, DimensionUnit::PX));
    EXPECT_EQ(borderRadiusRet.Value(), 20.0f);
    EXPECT_EQ(borderRadiusRet.Unit(), DimensionUnit::PX);

    /**
     * @tc.steps: step4. Set borderRadiu unit as fp.
     * @tc.expected: step4. Check the borderRadiu value and unit.
     */
    borderRadius = CalcDimension(20.0, DimensionUnit::FP);
    model.SetBorderRadius(frameNode, borderRadius);
    progressPattern->OnModifyDone();
    borderRadiusRet = paintProperty->GetBorderRadiusValue(Dimension(1.0f, DimensionUnit::PX));
    EXPECT_EQ(borderRadiusRet.Value(), 20.0f);
    EXPECT_EQ(borderRadiusRet.Unit(), DimensionUnit::FP);

    /**
     * @tc.steps: step5. Set borderRadiu unit as lpx.
     * @tc.expected: step5. Check the borderRadiu value and unit.
     */
    borderRadius = CalcDimension(20.0, DimensionUnit::LPX);
    model.SetBorderRadius(frameNode, borderRadius);
    progressPattern->OnModifyDone();
    borderRadiusRet = paintProperty->GetBorderRadiusValue(Dimension(1.0f, DimensionUnit::PX));
    EXPECT_EQ(borderRadiusRet.Value(), 20.0f);
    EXPECT_EQ(borderRadiusRet.Unit(), DimensionUnit::LPX);
}

/**
 * @tc.name: ProgressBorderRadiusTest003
 * @tc.desc: Test function RightToLeft border radius.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressBorderRadiusTest003, TestSize.Level1)
{
    int32_t backupApiVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    /**
     * @tc.steps: step1. Create the progress modifier.
     */
    auto progressModifier = CreateProgressModifier();
    ASSERT_NE(progressModifier, nullptr);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    InitCanvas(canvas);
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };

    // set ProgressType CAPSULE
    progressModifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));
    // set ProgressType CAPSULE(Width < Height)
    SizeF progressContentSize(50.0f, 100.0f);
    progressModifier->SetContentSize(progressContentSize);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    pattern_->OnLanguageConfigurationUpdate();

    // radius < Width/2
    progressModifier->SetCapsuleBorderRadius(20.0f);
    progressModifier->onDraw(context);
    auto borderRadiusRet = progressModifier->capsuleBorderRadius_->Get();
    EXPECT_EQ(borderRadiusRet, 20.0f);
    progressModifier->value_->Set(90.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->value_->Get(), 90.0f);

    // radius > Width/2
    progressModifier->SetCapsuleBorderRadius(50.0f);
    progressModifier->onDraw(context);
    borderRadiusRet = progressModifier->capsuleBorderRadius_->Get();
    EXPECT_EQ(borderRadiusRet, 50.0f);

    progressModifier->value_->Set(90.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->value_->Get(), 90.0f);

    // set ProgressType CAPSULE(Width > Height)
    progressModifier->SetContentSize(SizeF(100.0f, 50.0f));
    progressModifier->SetCapsuleBorderRadius(20.0f);
    progressModifier->value_->Set(10.0f);
    progressModifier->onDraw(context);

    progressModifier->value_->Set(90.0f);
    progressModifier->onDraw(context);

    progressModifier->isRightToLeft_->Set(true);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->value_->Get(), 90.0f);

    progressModifier->value_->Set(10.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->value_->Get(), 10.0f);

    Container::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ProgressModelTest001
 * @tc.desc: Test ResetColor and ResetBackgroundColor of linear progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelTest001, TestSize.Level0)
{
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    RefPtr<ProgressPaintProperty> paintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    modelNg.SetColor(FRONT_COLOR);
    modelNg.SetBackgroundColor(BG_COLOR);
    EXPECT_EQ(paintProperty->GetColorValue(), FRONT_COLOR);
    EXPECT_EQ(paintProperty->GetBackgroundColorValue(), BG_COLOR);
    modelNg.ResetColor();
    modelNg.ResetBackgroundColor();
    EXPECT_EQ(paintProperty->HasColor(), false);
    EXPECT_EQ(paintProperty->HasBackgroundColor(), false);
}

/**
 * @tc.name: ProgressModelTest002
 * @tc.desc: Test ResetGradientColor and ResetBackgroundColor of ring progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelTest002, TestSize.Level0)
{
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    RefPtr<ProgressPaintProperty> paintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    modelNg.SetGradientColor(gradient);
    modelNg.SetBackgroundColor(BG_COLOR);
    EXPECT_EQ(paintProperty->GetGradientColorValue(), gradient);
    EXPECT_EQ(paintProperty->GetBackgroundColorValue(), BG_COLOR);
    modelNg.ResetGradientColor();
    modelNg.ResetBackgroundColor();
    EXPECT_EQ(paintProperty->HasGradientColor(), false);
    EXPECT_EQ(paintProperty->HasBackgroundColor(), false);
}

/**
 * @tc.name: ProgressModelTest003
 * @tc.desc: Test Reset fuction of capsule progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelTest003, TestSize.Level0)
{
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    RefPtr<ProgressPaintProperty> paintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    modelNg.SetColor(FRONT_COLOR);
    modelNg.SetBorderColor(BORDER_COLOR);
    modelNg.SetBackgroundColor(BG_COLOR);
    modelNg.SetFontColor(FRONT_COLOR);
    EXPECT_EQ(paintProperty->GetColorValue(), FRONT_COLOR);
    EXPECT_EQ(paintProperty->GetBorderColorValue(), BORDER_COLOR);
    EXPECT_EQ(paintProperty->GetBackgroundColorValue(), BG_COLOR);
    EXPECT_EQ(paintProperty->GetTextColorValue(BG_COLOR), FRONT_COLOR);
    modelNg.ResetColor();
    modelNg.ResetBorderColor();
    modelNg.ResetBackgroundColor();
    modelNg.ResetFontColor();
    EXPECT_EQ(paintProperty->HasColor(), false);
    EXPECT_EQ(paintProperty->HasBorderColor(), false);
    EXPECT_EQ(paintProperty->HasBackgroundColor(), false);
    EXPECT_EQ(paintProperty->HasTextColor(), false);
}

/**
 * @tc.name: ProgressModelTest004
 * @tc.desc: Test ResetColor and ResetBackgroundColor of linear progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelTest004, TestSize.Level0)
{
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ProgressPaintProperty> paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    modelNg.SetColor(frameNode, FRONT_COLOR);
    modelNg.SetBackgroundColor(frameNode, BG_COLOR);
    EXPECT_EQ(paintProperty->GetColorValue(), FRONT_COLOR);
    EXPECT_EQ(paintProperty->GetBackgroundColorValue(), BG_COLOR);
    modelNg.ResetColor(frameNode);
    modelNg.ResetBackgroundColor(frameNode);
    EXPECT_EQ(paintProperty->HasColor(), false);
    EXPECT_EQ(paintProperty->HasBackgroundColor(), false);
}

/**
 * @tc.name: ProgressModelTest005
 * @tc.desc: Test ResetGradientColor and ResetBackgroundColor of ring progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelTest005, TestSize.Level0)
{
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ProgressPaintProperty> paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    modelNg.SetGradientColor(frameNode, gradient);
    modelNg.SetBackgroundColor(frameNode, BG_COLOR);
    EXPECT_EQ(paintProperty->GetGradientColorValue(), gradient);
    EXPECT_EQ(paintProperty->GetBackgroundColorValue(), BG_COLOR);
    modelNg.ResetGradientColor(frameNode);
    modelNg.ResetBackgroundColor(frameNode);
    EXPECT_EQ(paintProperty->HasGradientColor(), false);
    EXPECT_EQ(paintProperty->HasBackgroundColor(), false);
}

/**
 * @tc.name: ProgressPatternTest001
 * @tc.desc: Test OnThemeScopeUpdate fuction of progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternTest001, TestSize.Level0)
{
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    RefPtr<ProgressPattern> pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ProgressPaintProperty> paintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    modelNg.SetColor(FRONT_COLOR);
    modelNg.SetBackgroundColor(BG_COLOR);
    EXPECT_FALSE(pattern->OnThemeScopeUpdate(frameNode_->GetThemeScopeId()));

    modelNg.ResetColor();
    EXPECT_TRUE(pattern->OnThemeScopeUpdate(frameNode_->GetThemeScopeId()));

    modelNg.SetColor(FRONT_COLOR);
    modelNg.ResetBackgroundColor();
    EXPECT_TRUE(pattern->OnThemeScopeUpdate(frameNode_->GetThemeScopeId()));
}

/**
 * @tc.name: ProgressPatternTest002
 * @tc.desc: Test OnThemeScopeUpdate fuction of progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternTest002, TestSize.Level0)
{
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    RefPtr<ProgressPattern> pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ProgressPaintProperty> paintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    modelNg.SetColor(FRONT_COLOR);
    modelNg.SetBackgroundColor(BG_COLOR);
    EXPECT_FALSE(pattern->OnThemeScopeUpdate(frameNode_->GetThemeScopeId()));

    modelNg.ResetColor();
    EXPECT_FALSE(pattern->OnThemeScopeUpdate(frameNode_->GetThemeScopeId()));

    modelNg.SetColor(FRONT_COLOR);
    modelNg.ResetBackgroundColor();
    EXPECT_TRUE(pattern->OnThemeScopeUpdate(frameNode_->GetThemeScopeId()));
}

/**
 * @tc.name: ProgressPatternTest003
 * @tc.desc: Test OnThemeScopeUpdate fuction of progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternTest003, TestSize.Level0)
{
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    RefPtr<ProgressPattern> pattern = frameNode_->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ProgressPaintProperty> paintProperty = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    modelNg.SetColor(FRONT_COLOR);
    modelNg.SetBackgroundColor(BG_COLOR);
    modelNg.SetBorderColor(BORDER_COLOR);
    EXPECT_FALSE(pattern->OnThemeScopeUpdate(frameNode_->GetThemeScopeId()));

    modelNg.ResetColor();
    EXPECT_TRUE(pattern->OnThemeScopeUpdate(frameNode_->GetThemeScopeId()));

    modelNg.SetColor(FRONT_COLOR);
    modelNg.ResetBackgroundColor();
    EXPECT_TRUE(pattern->OnThemeScopeUpdate(frameNode_->GetThemeScopeId()));

    modelNg.SetBackgroundColor(BG_COLOR);
    modelNg.ResetBorderColor();
    EXPECT_TRUE(pattern->OnThemeScopeUpdate(frameNode_->GetThemeScopeId()));
}

/**
 * @tc.name: ProgressThemeWrapperTest001
 * @tc.desc: Test Builder fuction of ProgressThemeWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressThemeWrapperTest001, TestSize.Level0)
{
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_PROGRESS);
    ASSERT_NE(themeConstants, nullptr);
    auto progressThemeWrapper = ProgressThemeWrapper::WrapperBuilder().BuildWrapper(themeConstants);
    EXPECT_NE(progressThemeWrapper, nullptr);
    auto progressTheme = AceType::DynamicCast<ProgressTheme>(progressThemeWrapper);
    ASSERT_NE(progressTheme, nullptr);

    std::vector<Color> colors;
    TestProperty testProperty;
    colors.reserve(TokenColors::TOTAL_NUMBER);
    for (int i = 0; i < TokenColors::TOTAL_NUMBER; i++) {
        colors.push_back(Color(testProperty.colors_[i]));
    }
    auto themeColors = AceType::MakeRefPtr<TokenColors>();
    themeColors->SetColors(std::move(colors));
    testProperty.tokenColors_ = themeColors;
    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(TOKEN_THEME_ID);

    EXPECT_NE(progressTheme->GetLoadingColor(), colors[TokenColors::ICON_SECONDARY]);
    EXPECT_NE(progressTheme->GetCapsuleBgColor(), colors[TokenColors::COMP_BACKGROUND_TERTIARY]);
    EXPECT_NE(progressTheme->GetRingProgressBgColor(), colors[TokenColors::COMP_BACKGROUND_TERTIARY]);
    EXPECT_NE(progressTheme->GetTrackBgColor(), colors[TokenColors::COMP_BACKGROUND_TERTIARY]);
    EXPECT_NE(progressTheme->GetCapsuleSelectColor(), colors[TokenColors::COMP_EMPHASIZE_SECONDARY]);
    EXPECT_NE(progressTheme->GetTrackSelectedColor(), colors[TokenColors::BACKGROUND_EMPHASIZE]);
    EXPECT_NE(progressTheme->GetBorderColor(), colors[TokenColors::COMP_EMPHASIZE_SECONDARY]);

    tokenTheme->SetColors(testProperty.tokenColors_);
    ASSERT_NE(tokenTheme, nullptr);
    progressThemeWrapper->ApplyTokenTheme(*tokenTheme);
    EXPECT_EQ(progressTheme->GetLoadingColor(), colors[TokenColors::ICON_SECONDARY]);
    EXPECT_EQ(progressTheme->GetCapsuleBgColor(), colors[TokenColors::COMP_BACKGROUND_TERTIARY]);
    EXPECT_EQ(progressTheme->GetRingProgressBgColor(), colors[TokenColors::COMP_BACKGROUND_TERTIARY]);
    EXPECT_EQ(progressTheme->GetTrackBgColor(), colors[TokenColors::COMP_BACKGROUND_TERTIARY]);
    EXPECT_EQ(progressTheme->GetCapsuleSelectColor(), colors[TokenColors::COMP_EMPHASIZE_SECONDARY]);
    EXPECT_EQ(progressTheme->GetTrackSelectedColor(), colors[TokenColors::BACKGROUND_EMPHASIZE]);
    EXPECT_EQ(progressTheme->GetBorderColor(), colors[TokenColors::COMP_EMPHASIZE_SECONDARY]);
}

/**
 * @tc.name: ProgressPatternUpdateColorTest001
 * @tc.desc: Test UpdateColor function with first load scenario.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternUpdateColorTest001, TestSize.Level0)
{
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    
    Color testColor(Color::RED);
    pattern->UpdateColor(testColor, true);
    
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetColorValue(), testColor);
}

/**
 * @tc.name: ProgressPatternUpdateColorTest002
 * @tc.desc: Test UpdateColor function with first load scenario.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternUpdateColorTest002, TestSize.Level0)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    Color testColor(Color::BLACK);
    pattern->UpdateColor(testColor, true);

    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetColorValue(), testColor);
}

/**
 * @tc.name: ProgressPatternUpdateColorTest003
 * @tc.desc: Test UpdateColor function without first load or system color change.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternUpdateColorTest003, TestSize.Level0)
{
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    Color initialColor(Color::GREEN);
    pattern->UpdateColor(initialColor, true);
    Color newColor(Color::BLUE);
    pattern->UpdateColor(newColor, false);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetColorValue(), initialColor);
}

/**
 * @tc.name: ProgressPatternUpdateGradientColorTest001
 * @tc.desc: Test UpdateGradientColor function with first load scenario.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternUpdateGradientColorTest001, TestSize.Level0)
{
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradient.AddColor(gradientColorEnd);
    gradient.AddColor(gradientColorStart);
    
    pattern->UpdateGradientColor(gradient, true);
    
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetGradientColorValue(), gradient);
}

/**
 * @tc.name: ProgressModelNGSetBorderWidth
 * @tc.desc: Test ProgressModelNG SetBorderWidth
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetBorderWidth, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);

    /**
     * @tc.case: case1 call to  SetBorderWidth with no framenode.
     * @tc.expected: it should be as we set.
     */
    Dimension tmpWith = 10.0_vp;
    model.SetBorderWidth(tmpWith);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetBorderWidth().value(), tmpWith);

    /**
     * @tc.case: case2 call to  static function SetBorderWidth.
     * @tc.expected: it should be as we set.
     */
    ProgressModelNG::SetBorderWidth(Referenced::RawPtr(frameNode), STROKE_WIDTH);
    EXPECT_EQ(paintProperty->GetBorderWidth().value(), STROKE_WIDTH);
}

/**
 * @tc.name: ProgressModelNGSetSweepingEffect
 * @tc.desc: Test ProgressModelNG SetSweepingEffect
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetSweepingEffect, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);

    /**
     * @tc.case: case1 call to  SetSweepingEffect with no framenode.
     * @tc.expected: it should be as we set.
     */
    bool enableScanEffect = true;
    model.SetSweepingEffect(enableScanEffect);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetEnableScanEffect().value(), true);

    /**
     * @tc.case: case2 call to  static function SetSweepingEffect.
     * @tc.expected: it should be as we set.
     */
    enableScanEffect = false;
    ProgressModelNG::SetSweepingEffect(Referenced::RawPtr(frameNode), enableScanEffect);
    EXPECT_EQ(paintProperty->GetEnableScanEffect().value(), false);
}

/**
 * @tc.name: ProgressModelNGSetFontSize
 * @tc.desc: Test ProgressModelNG SetFontSize
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetFontSize, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    /**
     * @tc.case: case1 call to  SetFontSize with no framenode.
     * @tc.expected: it should be as we set.
     */
    Dimension defaultSize = 10.0_vp;
    model.SetFontSize(defaultSize);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetTextSize().value(), defaultSize);

    /**
     * @tc.case: case1 call to  static function SetFontSize.
     * @tc.expected: it should be as we set.
     */
    defaultSize = 6.66_vp;
    ProgressModelNG::SetFontSize(Referenced::RawPtr(frameNode), defaultSize);
    EXPECT_EQ(paintProperty->GetTextSize().value(), defaultSize);
}

/**
 * @tc.name: ProgressModelNGSetFontColor
 * @tc.desc: Test ProgressModelNG SetFontColor
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetFontColor, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);

    /**
     * @tc.case: case1 call to  SetFontColor with no framenode.
     * @tc.expected: it should be as we set.
     */
    Color fontColor = Color(0xffc0c0c1);
    model.SetFontColor(fontColor);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetTextColor().value(), fontColor);

    /**
     * @tc.case: case1 call to  static function SetFontColor.
     * @tc.expected: it should be as we set.
     */
    fontColor = Color(0xffc0c0c0);
    ProgressModelNG::SetFontColor(Referenced::RawPtr(frameNode), fontColor);
    EXPECT_EQ(paintProperty->GetTextColor().value(), fontColor);
}

/**
 * @tc.name: ProgressModelNGSetFontWeight
 * @tc.desc: Test ProgressModelNG SetFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetFontWeight, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);

    /**
     * @tc.case: case1 call to  SetFontWeight with no framenode.
     * @tc.expected: it should be as we set.
     */
    model.SetFontWeight(FontWeight::LIGHTER);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetFontWeight().value(), FontWeight::LIGHTER);

    /**
     * @tc.case: case1 call to  static function SetFontWeight.
     * @tc.expected: it should be as we set.
     */
    ProgressModelNG::SetFontWeight(Referenced::RawPtr(frameNode), FontWeight::BOLD);
    EXPECT_EQ(paintProperty->GetFontWeight().value(), FontWeight::BOLD);
}

/**
 * @tc.name: ProgressModelNGSetFontFamily
 * @tc.desc: Test ProgressModelNG SetFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetFontFamily, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);

    /**
     * @tc.case: case1 call to  SetFontFamily with no framenode.
     * @tc.expected: it should be as we set.
     */
    const std::vector<std::string> fontFamily2 = { "serif", "scans" };
    model.SetFontFamily(fontFamily2);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetFontFamily().value(), fontFamily2);

    /**
     * @tc.case: case1 call to  static function SetFontFamily.
     * @tc.expected: it should be as we set.
     */
    const std::vector<std::string> fontFamily = { "serif" };
    ProgressModelNG::SetFontFamily(Referenced::RawPtr(frameNode), fontFamily);
    EXPECT_EQ(paintProperty->GetFontFamily().value(), fontFamily);
}

/**
 * @tc.name: ProgressModelNGSetItalicFontStyle
 * @tc.desc: Test ProgressModelNG SetItalicFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetItalicFontStyle, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);

    /**
     * @tc.case: case1 call to  SetItalicFontStyle with no framenode.
     * @tc.expected: it should be as we set.
     */
    model.SetItalicFontStyle(Ace::FontStyle::NORMAL);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetItalicFontStyle(), Ace::FontStyle::NORMAL);

    /**
     * @tc.case: case1 call to  static function SetItalicFontStyle.
     * @tc.expected: it should be as we set.
     */
    ProgressModelNG::SetItalicFontStyle(Referenced::RawPtr(frameNode), Ace::FontStyle::ITALIC);
    EXPECT_EQ(paintProperty->GetItalicFontStyle(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: ProgressModelNGSetRingSweepingEffect
 * @tc.desc: Test ProgressModelNG SetRingSweepingEffect
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetRingSweepingEffect, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);

    /**
     * @tc.case: case1 call to  SetRingSweepingEffect with no framenode.
     * @tc.expected: it should be as we set.
     */
    bool enableRingSweepingEffect = true;
    model.SetRingSweepingEffect(enableRingSweepingEffect);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetEnableRingScanEffect().value(), true);

    /**
     * @tc.case: case2 call to  static function SetRingSweepingEffect.
     * @tc.expected: it should be as we set.
     */
    enableRingSweepingEffect = false;
    ProgressModelNG::SetRingSweepingEffect(Referenced::RawPtr(frameNode), enableRingSweepingEffect);
    EXPECT_EQ(paintProperty->GetEnableRingScanEffect().value(), false);
}

/**
 * @tc.name: ProgressModelNGSetLinearSweepingEffect
 * @tc.desc: Test ProgressModelNG SetLinearSweepingEffect
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetLinearSweepingEffect, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);

    /**
     * @tc.case: case1 call to  SetLinearSweepingEffect with no framenode.
     * @tc.expected: it should be as we set.
     */
    bool enableLinearScanEffect = true;
    model.SetLinearSweepingEffect(enableLinearScanEffect);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetEnableLinearScanEffect().value(), true);

    /**
     * @tc.case: case2 call to  static function SetLinearSweepingEffect.
     * @tc.expected: it should be as we set.
     */
    enableLinearScanEffect = false;
    ProgressModelNG::SetLinearSweepingEffect(Referenced::RawPtr(frameNode), enableLinearScanEffect);
    EXPECT_EQ(paintProperty->GetEnableLinearScanEffect().value(), false);
}

/**
 * @tc.name: ProgressModelNGSetSmoothEffect
 * @tc.desc: Test ProgressModelNG SetSmoothEffect
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetSmoothEffect, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);

    /**
     * @tc.case: case1 call to  enableSmoothEffect with no framenode.
     * @tc.expected: it should be as we set.
     */
    bool enableSmoothEffect = true;
    model.SetSmoothEffect(enableSmoothEffect);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetEnableSmoothEffect().value(), true);

    /**
     * @tc.case: case2 call to  static function enableSmoothEffect.
     * @tc.expected: it should be as we set.
     */
    enableSmoothEffect = false;
    ProgressModelNG::SetSmoothEffect(Referenced::RawPtr(frameNode), enableSmoothEffect);
    EXPECT_EQ(paintProperty->GetEnableSmoothEffect().value(), false);
}

/**
 * @tc.name: ProgressModelNGSetBackgroundColor
 * @tc.desc: Test ProgressModelNG SetBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetBackgroundColor, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);

    /**
     * @tc.case: case1 call to  SetBackgroundColor with no framenode.
     * @tc.expected: it should be as we set.
     */
    Color backgroundColorColor = Color(0xffc0c0c1);
    model.SetBackgroundColor(backgroundColorColor);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetBackgroundColor().value(), backgroundColorColor);

    /**
     * @tc.case: case1 call to  static function SetBackgroundColor.
     * @tc.expected: it should be as we set.
     */
    backgroundColorColor = Color(0xffc0c0c0);
    ProgressModelNG::SetBackgroundColor(Referenced::RawPtr(frameNode), backgroundColorColor);
    EXPECT_EQ(paintProperty->GetBackgroundColor().value(), backgroundColorColor);
}

/**
 * @tc.name: ProgressModelNGSetText001
 * @tc.desc: Test ProgressModelNG SetText
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetText, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance and update property.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS_2, 100.0, PROGRESS_TYPE_CAPSULE);
    model.SetStrokeWidth(LARG_STROKE_WIDTH);
    model.SetStrokeRadius(LARG_STROKE_WIDTH / 5.0);
    model.SetShowText(true);
    CreateDone();
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto* stack = ViewStackProcessor::GetInstance();
    stack->Push(frameNode_);

    /**
     * @tc.case: case1 call to  static function SetText.
     * @tc.expected: it should be as we set.
     */
    std::string text = "hellow world";
    ProgressModelNG::SetText(Referenced::RawPtr(frameNode_), text);
    EXPECT_EQ(paintProperty_->GetText().value(), text);
}

/**
 * @tc.name: ProgressModelNGSetText002
 * @tc.desc: Test function about setting value.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetText002, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance and update property.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS_2, 100.0, PROGRESS_TYPE_CAPSULE);
    model.SetStrokeWidth(LARG_STROKE_WIDTH);
    model.SetStrokeRadius(LARG_STROKE_WIDTH / 5.0);
    model.SetShowText(true);
    CreateDone();
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto* stack = ViewStackProcessor::GetInstance();
    stack->Push(frameNode_);
    pattern_->SetTextFromUser(true);
    progressModel.SetValue(10.0);
    paintProperty_->UpdateMaxValue(100);
    paintProperty_->UpdateValue(50);
    paintProperty_->UpdateEnableShowText(true);

    /**
     * @tc.case: step2 call to  static function SetText and text value is null.
     * @tc.expected: it should be 50%.
     */
    ProgressModelNG::SetText(Referenced::RawPtr(frameNode_), std::nullopt);
    EXPECT_EQ(paintProperty_->GetTextValue(""), "50%");
    EXPECT_DOUBLE_EQ(paintProperty_->GetValueValue(0.0), 50);
}

/**
 * @tc.name: ProgressPatternOnColorConfigurationUpdateTest001
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternOnColorConfigurationUpdateTest001, TestSize.Level0)
{
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = false;
    pattern->OnColorConfigurationUpdate();
    g_isConfigChangePerform = true;
    pattern->OnColorConfigurationUpdate();
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->ResetGradientColorSetByUser();
    paintProperty->ResetCapsuleStyleSetByUser();
    paintProperty->ResetCapsuleStyleFontColorSetByUser();
    paintProperty->UpdateProgressType(ProgressType::LINEAR);
    pattern->OnColorConfigurationUpdate();
    paintProperty->UpdateGradientColorSetByUser(true);
    paintProperty->UpdateCapsuleStyleSetByUser(true);
    paintProperty->UpdateCapsuleStyleFontColorSetByUser(true);
    pattern->OnColorConfigurationUpdate();
    paintProperty->UpdateCapsuleStyleFontColorSetByUser(false);
    pattern->OnColorConfigurationUpdate();

    paintProperty->UpdateGradientColorSetByUser(false);
    paintProperty->UpdateCapsuleStyleSetByUser(false);
    paintProperty->UpdateProgressType(ProgressType::CAPSULE);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipeline = host->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<ProgressTheme>();
    ASSERT_NE(theme, nullptr);
    Color testColor = theme->GetCapsuleParseFailedSelectColor();
    pattern->OnColorConfigurationUpdate();
    paintProperty->UpdateCapsuleStyleFontColorSetByUser(true);
    pattern->OnColorConfigurationUpdate();
    EXPECT_EQ(paintProperty->GetColor(), testColor);
}

/**
 * @tc.name: ProgressPatternCreateWithResourceObjTest001
 * @tc.desc: Test model ng  CreateWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternCreateWithResourceObjTest001, TestSize.Level0)
{
    int32_t backupApiVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    ASSERT_NE(resObj, nullptr);

    for (int i = static_cast<int>(JsProgressResourceType::COLOR); i <= static_cast<int>(JsProgressResourceType::Text);
         ++i) {
        auto jsResourceType = static_cast<JsProgressResourceType>(i);
        modelNg.CreateWithResourceObj(jsResourceType, resObj);
    }
    modelNg.CreateWithResourceObj(static_cast<JsProgressResourceType>(100), resObj);
    modelNg.SetCapsuleStyleFontColor(true);
    modelNg.SetCapsuleStyle(true);
    modelNg.SetGradientColorByUser(true);

    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);

    paintProperty->UpdateProgressType(ProgressType::CAPSULE);
    pattern->OnColorModeChange(colorMode);
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHT));
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHT));
    paintProperty->UpdateProgressType(ProgressType::LINEAR);
    pattern->OnColorModeChange(colorMode);
    paintProperty->UpdateProgressType(ProgressType::RING);
    pattern->OnColorModeChange(colorMode);

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<ProgressTheme>();
    Color testColor = theme->GetBorderColor();
    EXPECT_EQ(paintProperty->GetBorderColor(), testColor);
    EXPECT_TRUE(paintProperty->GetCapsuleStyleSetByUser());
    EXPECT_TRUE(paintProperty->GetGradientColorSetByUser());
    EXPECT_TRUE(paintProperty->GetCapsuleStyleFontColorSetByUser());
    Container::Current()->SetApiTargetVersion(backupApiVersion);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
}

/**
 * @tc.name: ProgressPatternCreateWithResourceObjTest002
 * @tc.desc: Test model ng  CreateWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternCreateWithResourceObjTest002, TestSize.Level0)
{
    ProgressModelNG modelNg = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);

    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    std::vector<ResourceObjectParams> resObjParamsList;
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObjWithId =
        AceType::MakeRefPtr<ResourceObject>(100000, 10003, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObjWithDimensionId =
        AceType::MakeRefPtr<ResourceObject>(100000, 10007, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObjId =
        AceType::MakeRefPtr<ResourceObject>(-1, 100001, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObjBoolId =
        AceType::MakeRefPtr<ResourceObject>(100000, 10005, resObjParamsList, "com.example.test", "entry", 100000);
    for (int i = static_cast<int>(JsProgressResourceType::LSStrokeWidth);
         i <= static_cast<int>(JsProgressResourceType::Text); ++i) {
        auto jsResourceType = static_cast<JsProgressResourceType>(i);
        modelNg.CreateWithResourceObj(jsResourceType, resObjWithDimensionId);
    }
    modelNg.CreateWithResourceObj(JsProgressResourceType::COLOR, resObjId);
    modelNg.CreateWithResourceObj(JsProgressResourceType::RingStatus, resObjWithId);
    modelNg.CreateWithResourceObj(JsProgressResourceType::FontWeight, resObjWithId);
    modelNg.CreateWithResourceObj(JsProgressResourceType::Text, resObjWithId);
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    for (int i = static_cast<int>(JsProgressResourceType::LSStrokeWidth);
         i <= static_cast<int>(JsProgressResourceType::Text); ++i) {
        auto jsResourceType = static_cast<JsProgressResourceType>(i);
        modelNg.CreateWithResourceObj(jsResourceType, resObjBoolId);
    }

    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    paintProperty->UpdateProgressType(ProgressType::CAPSULE);
    pattern->OnColorModeChange(colorMode);

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<ProgressTheme>();
    Color testColor = theme->GetBorderColor();
    EXPECT_EQ(paintProperty->GetBorderColor(), testColor);
}

/**
 * @tc.name: ProgressModelNGSetCapsuleStyle
 * @tc.desc: Test ProgressModelNG SetCapsuleStyle &&  SetCapsuleStyleFontColor
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelNGSetCapsuleStyle, TestSize.Level0)
{
    /**
     * @tc.step: step1. create instance.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);

    /**
     * @tc.case: case1 call to  SetCapsuleStyle SetCapsuleStyleFontColor  with  framenode.
     * @tc.expected: it should be as we set.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    ProgressModelNG::SetCapsuleStyle(Referenced::RawPtr(frameNode), true);
    ProgressModelNG::SetCapsuleStyleFontColor(Referenced::RawPtr(frameNode), true);
    EXPECT_TRUE(paintProperty->GetCapsuleStyleSetByUser());
    EXPECT_TRUE(paintProperty->GetCapsuleStyleFontColorSetByUser());
}
} // namespace OHOS::Ace::NG
