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

#include <cmath>
#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

#include "gtest/gtest.h"

#include "base/memory/referenced.h"
#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"

#include "base/memory/ace_type.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/render/render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

namespace OHOS::Ace::NG {
namespace {
using namespace testing;
using namespace testing::ext;
const InspectorFilter filter;
constexpr double MAX_VALUE_OF_PROGRESS = 120.0;
constexpr double PROGRESS_MODEL_NG_CACHEDVALUE = 10.0;
constexpr double PROGRESS_MODEL_NG_MAX = 20.0;
constexpr double PROGRESS_MODEL_NG_MIN = 5.0;
constexpr double PROGRESS_MODEL_NG_VALUE = 10.0;
constexpr double VALUE_OF_PROGRESS = 20.0;
constexpr double VALUE_OF_PROGRESS_2 = 40.0;
constexpr ProgressType PROGRESS_TYPE_LINEAR = ProgressType::LINEAR;
constexpr ProgressType PROGRESS_TYPE_RING = ProgressType::RING;
constexpr ProgressType PROGRESS_TYPE_SCALE = ProgressType::SCALE;
constexpr ProgressType PROGRESS_TYPE_MOON = ProgressType::MOON;
constexpr ProgressType PROGRESS_TYPE_CAPSULE = ProgressType::CAPSULE;
constexpr ProgressType PROGRESS_TYPE_CIRCLE = ProgressType::CIRCLE;
constexpr Dimension STROKE_WIDTH = 10.0_vp;
constexpr Dimension LARG_STROKE_WIDTH = 500.0_vp;
constexpr Dimension SCALE_WIDTH = 10.0_vp;
constexpr int32_t SCALE_COUNT = 120;
constexpr int32_t TYPE_OF_PROGRESS = 5;
constexpr Color FRONT_COLOR = Color(0xff0000ff);
constexpr Color BG_COLOR = Color(0xffc0c0c0);
constexpr Color BORDER_COLOR = Color(0xffc0c0c0);
constexpr float PROGRESS_COMPONENT_MAXSIZE_WIDTH = 720.0f;
constexpr float PROGRESS_COMPONENT_MAXSIZE_HEIGHT = 1400.0f;
constexpr float PROGRESS_COMPONENT_WIDTH = 200.0f;
constexpr float LARG_PROGRESS_COMPONENT_WIDTH = 2000.0f;
constexpr float PROGRESS_COMPONENT_HEIGHT = 200.0f;
constexpr float LARG_PROGRESS_COMPONENT_HEIGHT = 2000.0f;
constexpr float PROGRESS_STROKE_WIDTH = 10.0f;
constexpr float PROGRESS_LARGE_STROKE_WIDTH = 200.0f;
constexpr float PROGRESS_MODIFIER_VALUE = 100.0f;
constexpr float PROGRESS_MODIFIER_LARGE_VALUE = 200.0f;
constexpr float PROGRESS_MODIFIER_MAX_VALUE = 10000.0f;
constexpr float CONTEXT_WIDTH = 100.0f;
constexpr float CONTEXT_HEIGHT = 100.0f;
constexpr float CONTEXT_LARGE_HEIGHT = 200.0f;
constexpr float CONTEXT_HUGE_WIDTH = 20000.0f;
constexpr float CONTEXT_HUGE_HEIGHT = 20000.0f;
constexpr Dimension DEFAULT_RING_DIAMETER = 72.0_vp;
constexpr Dimension DEFAULT_CAPSULE_WIDTH = 28.0_vp;
constexpr Dimension TEST_PROGRESS_THICKNESS = 4.0_vp;
constexpr Dimension TEST_PROGRESS_STROKE_WIDTH = 10.0_vp;
constexpr Dimension TEST_PROGRESS_DEFAULT_DIAMETER = 72.0_vp;
constexpr Dimension TEST_PROGRESS_SCALE_WIDTH = 2.0_vp;
constexpr Dimension DEFAULT_STROKE_WIDTH = 2.0_vp;
const Color TEST_COLOR = Color::BLUE;
const LinearColor TEST_LINEARCOLOR = LinearColor(TEST_COLOR);
constexpr float VALUE_OF_SET_VALUE = 10.0f;
const std::vector<std::string> FONT_FAMILY = { "serif" };
constexpr Dimension DEFAULT_SPACE = 3.0_vp;

DirtySwapConfig config;
ProgressModelNG progressModel;
RefPtr<ProgressTheme> progressTheme;
RefPtr<MockThemeManager> themeManager;
} // namespace

class ProgressTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetProgress();
    ProgressModelNG CreateProgress(double value, double max, NG::ProgressType type);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ProgressPattern> pattern_;
    RefPtr<EventHub> eventHub_;
    RefPtr<ProgressLayoutProperty> layoutProperty_;
    RefPtr<ProgressPaintProperty> paintProperty_;
    RefPtr<ProgressAccessibilityProperty> accessibilityProperty_;
};

void ProgressTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->trackThickness_ = TEST_PROGRESS_THICKNESS;
    progressTheme->scaleLength_ = TEST_PROGRESS_STROKE_WIDTH;
    progressTheme->ringDiameter_ = TEST_PROGRESS_DEFAULT_DIAMETER;
    progressTheme->trackBgColor_ = BG_COLOR;
    progressTheme->trackSelectedColor_ = FRONT_COLOR;
    progressTheme->scaleNumber_ = SCALE_COUNT;
    progressTheme->scaleWidth_ = TEST_PROGRESS_SCALE_WIDTH;
}

void ProgressTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    progressTheme = nullptr;
    themeManager = nullptr;
}

void ProgressTestNg::SetUp()
{
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
}

void ProgressTestNg::TearDown()
{
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

/**
 * @tc.name: ProgressCreate001
 * @tc.desc: Test all the pattern of progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressCreate001, TestSize.Level1)
{
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
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
HWTEST_F(ProgressTestNg, ProgressLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);

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
HWTEST_F(ProgressTestNg, ProgressLayoutAlgorithm002, TestSize.Level1)
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
HWTEST_F(ProgressTestNg, LinearProgressCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    model.SetStrokeWidth(STROKE_WIDTH);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    CreateDone(frameNode_);
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
HWTEST_F(ProgressTestNg, LinearProgressCreator002, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    model.SetStrokeWidth(LARG_STROKE_WIDTH);
    model.SetColor(FRONT_COLOR);
    model.SetBackgroundColor(BG_COLOR);
    CreateDone(frameNode_);

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
    CreateDone(frameNode_);

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
HWTEST_F(ProgressTestNg, ScaleProgressFrameNodeCreator001, TestSize.Level1)
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
    CreateDone(frameNode_);

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
HWTEST_F(ProgressTestNg, CapsuleProgressCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    model.SetStrokeWidth(STROKE_WIDTH);
    CreateDone(frameNode_);

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
 * @tc.name: GetContentDrawFunction
 * @tc.desc: Test the function GetContentDrawFunction in ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, GetContentDrawFunction, TestSize.Level1)
{
    ProgressType progressType[TYPE_OF_PROGRESS] = { PROGRESS_TYPE_LINEAR, PROGRESS_TYPE_RING, PROGRESS_TYPE_SCALE,
        PROGRESS_TYPE_MOON, PROGRESS_TYPE_CAPSULE };
    for (int32_t i = 0; i < TYPE_OF_PROGRESS; i++) {
        /**
         * @tc.steps: step2. create progress frameNode_ and check the progress properties with expected value .
         * @tc.expected: step2. get frameNode_ success and progress properties equals expected value.
         */
        ClearOldNodes();
        ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, progressType[i]);
        model.SetStrokeWidth(LARG_STROKE_WIDTH);
        model.SetScaleWidth(SCALE_WIDTH);
        model.SetScaleCount(SCALE_COUNT);
        CreateDone(frameNode_);

        /**
         * @tc.steps: step3. create GeometryNode and PaintWrapper, ProgressPaintMethod.
         */
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        geometryNode->SetContentSize(SizeF(PROGRESS_COMPONENT_MAXSIZE_WIDTH, PROGRESS_COMPONENT_MAXSIZE_HEIGHT));
        geometryNode->SetContentOffset(OffsetF(0, 0));
        RefPtr<PaintWrapper> paintWrapper =
            AceType::MakeRefPtr<PaintWrapper>(RenderContext::Create(), geometryNode, paintProperty_);
        auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
        auto progressPaintMethod = AceType::MakeRefPtr<ProgressPaintMethod>(
            progressType[i], LARG_STROKE_WIDTH.ConvertToPx(), progressModifier);
        EXPECT_NE(progressPaintMethod, nullptr);
        EXPECT_NE(progressPaintMethod->progressModifier_, nullptr);
    }
}

/**
 * @tc.name: ProgressModifier001
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    ProgressModifier progressModifier;
    progressModifier.SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier.SetColor(linearColor);
    EXPECT_EQ(progressModifier.color_->Get(), linearColor);
    progressModifier.SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier.bgColor_->Get(), linearColor);
    progressModifier.SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier.borderColor_->Get(), linearColor);
    progressModifier.SetRingProgressColor(gradient);
    progressModifier.SetPaintShadow(true);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.value_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleCount(SCALE_COUNT);
    EXPECT_EQ(progressModifier.scaleCount_->Get(), SCALE_COUNT);
    OffsetF offset(0, 0);
    progressModifier.SetContentOffset(offset);
    EXPECT_EQ(progressModifier.offset_->Get(), offset);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));

    progressModifier.SetProgressType(PROGRESS_TYPE_LINEAR);
    SizeF ContentSize(CONTEXT_WIDTH, CONTEXT_HEIGHT);

    // set ProgressType LINEAR(Width >= Height)
    progressModifier.SetContentSize(ContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
    EXPECT_EQ(progressModifier.contentSize_->Get(), ContentSize);

    // set ProgressType LINEAR(Width < Height)
    SizeF secondContentSize(CONTEXT_WIDTH, CONTEXT_LARGE_HEIGHT);
    progressModifier.SetContentSize(secondContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
    EXPECT_EQ(progressModifier.contentSize_->Get(), secondContentSize);

    // set ProgressType RING
    progressModifier.SetStrokeWidth(PROGRESS_LARGE_STROKE_WIDTH);
    progressModifier.SetProgressType(PROGRESS_TYPE_RING);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    EXPECT_EQ(progressModifier.strokeWidth_->Get(), PROGRESS_LARGE_STROKE_WIDTH);
}

/**
 * @tc.name: ProgressModifier002
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    ProgressModifier progressModifier;
    progressModifier.SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier.SetColor(linearColor);
    EXPECT_EQ(progressModifier.color_->Get(), linearColor);
    progressModifier.SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier.bgColor_->Get(), linearColor);
    progressModifier.SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier.borderColor_->Get(), linearColor);
    progressModifier.SetRingProgressColor(gradient);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.value_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleCount(SCALE_COUNT);
    EXPECT_EQ(progressModifier.scaleCount_->Get(), SCALE_COUNT);
    OffsetF offset(0, 0);
    progressModifier.SetContentOffset(offset);
    EXPECT_EQ(progressModifier.offset_->Get(), offset);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    // set ProgressType SCALE
    progressModifier.SetProgressType(PROGRESS_TYPE_SCALE);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_SCALE));

    // set ProgressType SCALE SetScaleWidth 0
    progressModifier.SetScaleWidth(0);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.scaleWidth_->Get(), 0);

    // set ProgressType MOON
    progressModifier.SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    progressModifier.SetProgressType(PROGRESS_TYPE_MOON);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_MOON));
    EXPECT_EQ(progressModifier.strokeWidth_->Get(), PROGRESS_STROKE_WIDTH);

    // set ProgressType MOON(angle <=FLOAT_ZERO_FIVE)
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
}

/**
 * @tc.name: ProgressModifier003
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    ProgressModifier progressModifier;
    progressModifier.SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier.SetColor(linearColor);
    EXPECT_EQ(progressModifier.color_->Get(), linearColor);
    progressModifier.SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier.bgColor_->Get(), linearColor);
    progressModifier.SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier.borderColor_->Get(), linearColor);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.value_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleCount(SCALE_COUNT);
    EXPECT_EQ(progressModifier.scaleCount_->Get(), SCALE_COUNT);
    OffsetF offset(0, 0);
    progressModifier.SetContentOffset(offset);
    EXPECT_EQ(progressModifier.offset_->Get(), offset);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
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

    // set ProgressType CAPSULE(Width >= Height)
    progressModifier.SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));

    // set ProgressType CAPSULE(Width >= Height, progressWidth < radius)
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);

    // set ProgressType CAPSULE(Width >= Height, else)
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_LARGE_VALUE);
    SizeF thirdContentSize(CONTEXT_HUGE_WIDTH, CONTEXT_HEIGHT);
    progressModifier.SetContentSize(thirdContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_LARGE_VALUE);
    EXPECT_EQ(progressModifier.contentSize_->Get(), thirdContentSize);

    // set ProgressType CAPSULE(Width < Height)
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_VALUE);
    SizeF secondContentSize(CONTEXT_WIDTH, CONTEXT_LARGE_HEIGHT);
    progressModifier.SetContentSize(secondContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.contentSize_->Get(), secondContentSize);
}

/**
 * @tc.name: ProgressModifier004
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    ProgressModifier progressModifier;
    progressModifier.SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier.SetColor(linearColor);
    EXPECT_EQ(progressModifier.color_->Get(), linearColor);
    progressModifier.SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier.bgColor_->Get(), linearColor);
    progressModifier.SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier.borderColor_->Get(), linearColor);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.value_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier.scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier.SetScaleCount(SCALE_COUNT);
    EXPECT_EQ(progressModifier.scaleCount_->Get(), SCALE_COUNT);
    OffsetF offset(0, 0);
    progressModifier.SetContentOffset(offset);
    EXPECT_EQ(progressModifier.offset_->Get(), offset);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
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

    // set ProgressType CAPSULE(Width < Height,progressWidth < radius)
    progressModifier.SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    SizeF secondContentSize(CONTEXT_WIDTH, CONTEXT_LARGE_HEIGHT);
    progressModifier.SetContentSize(secondContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
    EXPECT_EQ(progressModifier.contentSize_->Get(), secondContentSize);

    // set ProgressType CAPSULE(Width < Height,progressWidth > radius)
    progressModifier.SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    progressModifier.SetBorderWidth(CONTEXT_WIDTH);
    progressModifier.SetContentSize(secondContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
    EXPECT_EQ(progressModifier.contentSize_->Get(), secondContentSize);

    // set ProgressType CAPSULE(Width < Height,else)
    progressModifier.SetMaxValue(PROGRESS_MODIFIER_LARGE_VALUE);
    SizeF fourthContentSize(CONTEXT_WIDTH, CONTEXT_HUGE_HEIGHT);
    progressModifier.SetContentSize(fourthContentSize);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.maxValue_->Get(), PROGRESS_MODIFIER_LARGE_VALUE);
    EXPECT_EQ(progressModifier.contentSize_->Get(), fourthContentSize);

    // set ProgressType CIRCLE
    progressModifier.SetProgressType(PROGRESS_TYPE_CIRCLE);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CIRCLE));
}

/**
 * @tc.name: ProgressPaintMethod001
 * @tc.desc: Test ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(5.0, 10.0, 10.0, 20.0, PROGRESS_TYPE_LINEAR);
    auto frameNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the paintProperty_.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty_ = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    paintProperty_->UpdateColor(TEST_COLOR);
    paintProperty_->UpdateBackgroundColor(TEST_COLOR);
    paintProperty_->UpdateBorderColor(TEST_COLOR);
    paintProperty_->UpdateMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    paintProperty_->UpdateValue(PROGRESS_MODIFIER_VALUE);
    paintProperty_->UpdateScaleCount(SCALE_COUNT);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty_);

    /**
     * @tc.steps: step3. Create ProgressPaintMethod. Call the function UpdateContentModifier and GetContentModifier.
     * @tc.expected: step3. Check the properties update before.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    ProgressPaintMethod progressPaintMethod(PROGRESS_TYPE_LINEAR, PROGRESS_STROKE_WIDTH, progressModifier);
    // progressType_ = PROGRESS_TYPE_LINEAR
    progressPaintMethod.progressType_ = PROGRESS_TYPE_LINEAR;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    // progressType_ = PROGRESS_TYPE_MOON
    progressPaintMethod.progressType_ = PROGRESS_TYPE_MOON;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    // progressType_ = PROGRESS_TYPE_RING
    progressPaintMethod.progressType_ = PROGRESS_TYPE_RING;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    auto getModifier = progressPaintMethod.GetContentModifier(paintWrapper);
    auto getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
    EXPECT_EQ(getProgressModifier->color_->Get(), TEST_LINEARCOLOR);
    EXPECT_EQ(getProgressModifier->bgColor_->Get(), TEST_LINEARCOLOR);
    EXPECT_EQ(getProgressModifier->borderColor_->Get(), TEST_LINEARCOLOR);
    EXPECT_EQ(getProgressModifier->scaleCount_->Get(), SCALE_COUNT);
    EXPECT_EQ(getProgressModifier->maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
    EXPECT_EQ(getProgressModifier->value_->Get(), PROGRESS_MODIFIER_VALUE);
    delete paintWrapper;
}

/**
 * @tc.name: ProgressPaintProperty001
 * @tc.desc: Test progress_paint_property.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPaintProperty001, TestSize.Level1)
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
HWTEST_F(ProgressTestNg, ProgressMaskPropertyTestNg001, TestSize.Level1)
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
HWTEST_F(ProgressTestNg, ProgressAccessibilityPropertyTestNg001, TestSize.Level1)
{
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
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
HWTEST_F(ProgressTestNg, ProgressAccessibilityPropertyTestNg002, TestSize.Level1)
{
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
    paintProperty_->UpdateValue(VALUE_OF_PROGRESS);
    EXPECT_EQ(accessibilityProperty_->GetText(), std::to_string(VALUE_OF_PROGRESS));
}

/**
 * @tc.name: ProgressPattern001
 * @tc.desc: Test the TouchEvent of progress, TouchType is DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPattern001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create capsule progress and set add touchEvent.
     * @tc.expected: step1. Check the touchEvent is enable.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    model.SetBackgroundColor(Color::BLUE);
    CreateDone(frameNode_);
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
    CreateDone(frameNode_);
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
HWTEST_F(ProgressTestNg, ProgressPattern002, TestSize.Level1)
{
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    model.SetBackgroundColor(Color::BLUE);
    CreateDone(frameNode_);
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
HWTEST_F(ProgressTestNg, ProgressPattern003, TestSize.Level1)
{
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    model.SetBackgroundColor(Color::BLUE);
    CreateDone(frameNode_);
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
HWTEST_F(ProgressTestNg, ProgressPattern004, TestSize.Level1)
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
    CreateDone(frameNode_);
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    paintProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);

    model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    model.SetProgressStatus(ProgressStatus::LOADING);
    CreateDone(frameNode_);
    pattern_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: CapsuleProgressMeasure001
 * @tc.desc: Test the measure of Capsule type progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, CapsuleProgressMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    CreateDone(frameNode_);

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
HWTEST_F(ProgressTestNg, CapsuleProgressMeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    CreateDone(frameNode_);

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
 * @tc.name: ProgressPaintMethod002
 * @tc.desc: Test ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(5.0, 0.0, 10.0, 20.0, PROGRESS_TYPE_CAPSULE);
    auto frameNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the paintProperty_.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty_ = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    paintProperty_->UpdateMaxValue(100.0);
    paintProperty_->UpdateValue(0.0);
    paintProperty_->UpdateBorderWidth(0.0_vp);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty_);

    /**
     * @tc.steps: step3. Create ProgressPaintMethod. Call the function UpdateContentModifier and GetContentModifier.
     * @tc.expected: step3. Check the properties update before.
     */
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    ProgressPaintMethod progressPaintMethod(PROGRESS_TYPE_CAPSULE, PROGRESS_STROKE_WIDTH, progressModifier);
    progressPaintMethod.progressType_ = PROGRESS_TYPE_CAPSULE;
    progressPaintMethod.UpdateContentModifier(paintWrapper);

    paintProperty_->UpdateValue(10.0);
    paintProperty_->UpdateBorderWidth(300.0_vp);
    paintProperty_->UpdateEnableScanEffect(true);
    paintProperty_->UpdateBorderWidth(2.0_vp);
    SizeF progressContentSize(300.0f, 50.0f);
    progressModifier->SetContentSize(progressContentSize);
    progressPaintMethod.UpdateContentModifier(paintWrapper);

    SizeF progressContentSize1(50.0f, 300.0f);
    progressModifier->SetContentSize(progressContentSize1);
    progressPaintMethod.UpdateContentModifier(paintWrapper);

    auto getModifier = progressPaintMethod.GetContentModifier(paintWrapper);
    auto getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
}

/**
 * @tc.name: ProgressPaintMethod003
 * @tc.desc: Test ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(5.0, 10.0, 10.0, 20.0, PROGRESS_TYPE_RING);
    auto frameNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the paintProperty_.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty_ = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    paintProperty_->UpdateItalicFontStyle(Ace::FontStyle::ITALIC);
    paintProperty_->UpdateMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    paintProperty_->UpdateValue(PROGRESS_MODIFIER_VALUE);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty_);

    /**
     * @tc.steps: step3. Create ProgressPaintMethod. Call the function UpdateContentModifier and GetContentModifier.
     * @tc.expected: step3. Check the properties update before.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    ProgressPaintMethod progressPaintMethod(PROGRESS_TYPE_LINEAR, PROGRESS_STROKE_WIDTH, progressModifier);
    progressPaintMethod.progressType_ = PROGRESS_TYPE_RING;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    auto getModifier = progressPaintMethod.GetContentModifier(paintWrapper);
    auto getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
    EXPECT_TRUE(getProgressModifier->isItalic_->Get());
    EXPECT_EQ(getProgressModifier->maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
    EXPECT_EQ(getProgressModifier->value_->Get(), PROGRESS_MODIFIER_VALUE);

    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    paintProperty_->UpdateGradientColor(gradient);
    paintProperty_->UpdateItalicFontStyle(Ace::FontStyle::NORMAL);
    paintProperty_->UpdateMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    paintProperty_->UpdateValue(PROGRESS_MODIFIER_VALUE);
    progressPaintMethod.progressType_ = PROGRESS_TYPE_RING;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    getModifier = progressPaintMethod.GetContentModifier(paintWrapper);
    getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
    EXPECT_FALSE(getProgressModifier->isItalic_->Get());
    EXPECT_EQ(getProgressModifier->maxValue_->Get(), PROGRESS_MODIFIER_MAX_VALUE);
    EXPECT_EQ(getProgressModifier->value_->Get(), PROGRESS_MODIFIER_VALUE);
    delete paintWrapper;
}

/**
 * @tc.name: CapsuleProgressModifier001
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, CapsuleProgressModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    ProgressModifier progressModifier;
    LinearColor linearColor;
    progressModifier.SetColor(linearColor);
    EXPECT_EQ(progressModifier.color_->Get(), linearColor);
    progressModifier.SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier.bgColor_->Get(), linearColor);
    progressModifier.SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier.borderColor_->Get(), linearColor);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100, 100 };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    progressModifier.SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier.SetMaxValue(100.0);
    progressModifier.SetValue(20.0);
    SizeF progressContentSize(200.0, 100.0);
    progressModifier.SetContentSize(progressContentSize);
    progressModifier.SetBorderWidth(2.0);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));
    EXPECT_EQ(progressModifier.capsuleBorderWidth_->Get(), 2.0);

    progressModifier.SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier.SetContentSize(progressContentSize);
    progressModifier.SetBorderWidth(100.0);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));
    EXPECT_EQ(progressModifier.capsuleBorderWidth_->Get(), 100.0);

    SizeF progressContentSize2(100.0, 200.0);
    progressModifier.SetMaxValue(100.0);
    progressModifier.SetValue(20.0);
    progressModifier.SetBorderWidth(2.0);
    progressModifier.SetContentSize(progressContentSize2);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.contentSize_->Get(), progressContentSize2);

    progressModifier.SetContentSize(progressContentSize2);
    progressModifier.SetMaxValue(100.0);
    progressModifier.SetValue(20.0);
    progressModifier.SetBorderWidth(2.0);
    progressModifier.onDraw(context);
    EXPECT_EQ(progressModifier.contentSize_->Get(), progressContentSize2);
}

/**
 * @tc.name: CapsuleProgressModifier002
 * @tc.desc: Test the sweep animation of the capsule progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, CapsuleProgressModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    LinearColor linearColor;
    progressModifier->SetColor(linearColor);
    EXPECT_EQ(progressModifier->color_->Get(), linearColor);
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier->borderColor_->Get(), linearColor);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100, 100 };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));

    /**
     * @tc.steps: step2. Set value while sweeping.
     * @tc.expected: step2. The sweeping date updated successfully.
     */
    progressModifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    progressModifier->SetMaxValue(100.0);
    progressModifier->SetSweepEffect(true);
    SizeF progressContentSize(200.0, 100.0);
    progressModifier->SetContentSize(progressContentSize);
    progressModifier->SetBorderWidth(2.0);
    progressModifier->isSweeping_ = true;
    progressModifier->sweepingDateBackup_ = 1000.0f;
    progressModifier->SetValue(20.0);
    progressModifier->onDraw(context);
    EXPECT_NE(progressModifier->sweepingDate_, 0.0f);
}

/**
 * @tc.name: RingProgressModifier001
 * @tc.desc: Test the loading and sweeping animation of the ring progress can be started and stoped.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, RingProgressModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    progressModifier->SetVisible(true);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->SetProgressStatus(ProgressStatus::PROGRESSING);
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    progressModifier->SetRingSweepEffect(true);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    EXPECT_EQ(progressModifier->strokeWidth_->Get(), PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier->SetColor(linearColor);
    EXPECT_EQ(progressModifier->color_->Get(), linearColor);
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetRingProgressColor(gradient);
    progressModifier->SetPaintShadow(true);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->SetSmoothEffect(false);
    EXPECT_EQ(progressModifier->smoothEffect_->Get(), false);
    float value = 50.0f;
    progressModifier->SetValue(value);
    EXPECT_EQ(progressModifier->value_->Get(), value);
    OffsetF offset(0, 0);
    progressModifier->SetContentOffset(offset);
    EXPECT_EQ(progressModifier->offset_->Get(), offset);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    value = 60.0f;
    SizeF ContentSize(CONTEXT_WIDTH, CONTEXT_HEIGHT);
    progressModifier->SetContentSize(ContentSize);
    progressModifier->isSweeping_ = false;
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->isSweeping_, true);

    /**
     * @tc.steps: step3. In sweeping, set value.
     * @tc.expected: step3. The dateUpdated_ is true.
     */
    value = 70.0f;
    progressModifier->sweepingDate_->Set(0.0f);
    progressModifier->isSweeping_ = true;
    progressModifier->sweepingDateBackup_ = 10000.0f;
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    EXPECT_TRUE(progressModifier->dateUpdated_);

    /**
     * @tc.steps: step4. In sweeping, set value to 0.
     * @tc.expected: step4. The sweeping animation is stopped.
     */
    value = 0.0f;
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    EXPECT_EQ(progressModifier->isSweeping_, false);

    /**
     * @tc.steps: step5. Set progress status to LOADING.
     * @tc.expected: step5. The loading animation is started.
     */
    progressModifier->SetProgressStatus(ProgressStatus::LOADING);
    EXPECT_EQ(progressModifier->isLoading_, true);

    /**
     * @tc.steps: step6. Set the progress invisible.
     * @tc.expected: step6. The loading animation is stopped.
     */
    progressModifier->SetVisible(false);
    EXPECT_EQ(progressModifier->isLoading_, false);
}

/**
 * @tc.name: RingProgressModifier003
 * @tc.desc: Test sets the value in the LOADING state.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, RingProgressModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier->borderColor_->Get(), linearColor);
    progressModifier->SetRingProgressColor(gradient);
    progressModifier->SetPaintShadow(true);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->SetValue(50.0f);
    EXPECT_EQ(progressModifier->value_->Get(), 50.0f);
    progressModifier->SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);

    /**
     * @tc.steps: step2. Sets value in the LOADING state.
     * @tc.expected: step2. Value is not changed.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));

    SizeF ContentSize(CONTEXT_WIDTH, CONTEXT_HEIGHT);
    progressModifier->isLoading_ = true;
    progressModifier->SetContentSize(ContentSize);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));

    progressModifier->SetValue(20.0f);
    EXPECT_EQ(progressModifier->value_->Get(), 50.0f);
}

/**
 * @tc.name: RingProgressModifier004
 * @tc.desc: Test clip path during sweeping.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, RingProgressModifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorEnd);
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorStart);

    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier->borderColor_->Get(), linearColor);
    progressModifier->SetRingProgressColor(gradient);
    progressModifier->SetPaintShadow(true);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->SetValue(50.0f);
    EXPECT_EQ(progressModifier->value_->Get(), 50.0f);
    progressModifier->SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));

    // Set sweepingDate_ = 0.
    SizeF ContentSize(CONTEXT_WIDTH, CONTEXT_HEIGHT);
    progressModifier->SetContentSize(ContentSize);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->isLoading_ = false;
    progressModifier->sweepingDate_->Set(0.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    progressModifier->SetValue(80.0f);
    progressModifier->isLoading_ = false;
    progressModifier->sweepingDate_->Set(0.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));

    // Set sweepingDate_ = 200.
    progressModifier->isLoading_ = false;
    progressModifier->sweepingDate_->Set(200.0f);
    progressModifier->SetContentSize(ContentSize);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));

    // Set sweepingDate_ = 405.
    progressModifier->SetContentSize(ContentSize);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->isLoading_ = false;
    progressModifier->sweepingDate_->Set(405.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
}

/**
 * @tc.name: RingProgressModifier005
 * @tc.desc: Test the modifier while drawing ring progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, RingProgressModifier005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    Gradient gradient;
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    SizeF contentSize(CONTEXT_WIDTH, CONTEXT_HEIGHT);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetVisible(true);
    progressModifier->SetProgressType(PROGRESS_TYPE_RING);
    progressModifier->SetProgressStatus(ProgressStatus::PROGRESSING);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    LinearColor linearColor;
    progressModifier->SetColor(linearColor);
    EXPECT_EQ(progressModifier->color_->Get(), linearColor);
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetRingProgressColor(gradient);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->SetValue(50.0f);
    EXPECT_EQ(progressModifier->value_->Get(), 50.0f);
    OffsetF offset(0, 0);
    progressModifier->SetContentOffset(offset);
    EXPECT_EQ(progressModifier->offset_->Get(), offset);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Disable shadow and make stroke width smaller than the radius, then call function onDraw.
     * @tc.expected: step2. Draw ring progress without shadow.
     */
    progressModifier->SetPaintShadow(false);
    contentSize.SetWidth(CONTEXT_WIDTH);
    contentSize.SetHeight(CONTEXT_WIDTH);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetStrokeWidth(50.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->contentSize_->Get(), contentSize);

    /**
     * @tc.steps: step3. Disable shadow and make stroke width equal to the radius, then call function onDraw.
     * @tc.expected: step3. Draw ring progress without shadow.
     */
    progressModifier->SetPaintShadow(false);
    contentSize.SetWidth(CONTEXT_WIDTH);
    contentSize.SetHeight(CONTEXT_WIDTH);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetStrokeWidth(CONTEXT_WIDTH);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->contentSize_->Get(), contentSize);

    /**
     * @tc.steps: step4. Enable shadow and make stroke width smaller than the radius, then call function onDraw.
     * @tc.expected: step4. Draw ring progress with shadow.
     */
    progressModifier->SetPaintShadow(true);
    contentSize.SetWidth(CONTEXT_WIDTH);
    contentSize.SetHeight(CONTEXT_WIDTH);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetStrokeWidth(50.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->contentSize_->Get(), contentSize);

    /**
     * @tc.steps: step5. Enable shadow and make stroke width close to the radius, then call function onDraw.
     * @tc.expected: step5. Draw ring progress with shadow.
     */
    progressModifier->SetPaintShadow(true);
    contentSize.SetWidth(CONTEXT_WIDTH);
    contentSize.SetHeight(CONTEXT_WIDTH);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetStrokeWidth(CONTEXT_WIDTH - 5.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->contentSize_->Get(), contentSize);

    /**
     * @tc.steps: step6. Enable shadow and make radius equal to 10.0, then call function onDraw.
     * @tc.expected: step6. Draw ring progress without shadow.
     */
    progressModifier->SetPaintShadow(true);
    contentSize.SetWidth(20.0f);
    contentSize.SetHeight(20.0f);
    progressModifier->SetContentSize(contentSize);
    progressModifier->SetStrokeWidth(1.0f);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->contentSize_->Get(), contentSize);
}

/**
 * @tc.name: LinearProgressModifier001
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, LinearProgressModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    float value = 50.0f;
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    progressModifier->SetStrokeWidth(PROGRESS_STROKE_WIDTH);
    LinearColor linearColor;
    progressModifier->SetLinearSweepEffect(true);
    progressModifier->SetBackgroundColor(linearColor);
    EXPECT_EQ(progressModifier->bgColor_->Get(), linearColor);
    progressModifier->SetBorderColor(linearColor);
    EXPECT_EQ(progressModifier->borderColor_->Get(), linearColor);
    progressModifier->SetMaxValue(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->maxValue_->Get(), PROGRESS_MODIFIER_VALUE);
    progressModifier->SetValue(value);
    EXPECT_EQ(progressModifier->value_->Get(), value);
    progressModifier->SetScaleWidth(PROGRESS_MODIFIER_VALUE);
    EXPECT_EQ(progressModifier->scaleWidth_->Get(), PROGRESS_MODIFIER_VALUE);

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));

    /**
     * @tc.steps: step3. Set value for the horizontal linear progress.
     * @tc.expected: step3. The sweeping animation is started.
     */
    SizeF ContentSize2(200.0f, 100.0f);
    progressModifier->SetContentSize(ContentSize2);
    progressModifier->SetVisible(true);
    progressModifier->isSweeping_ = false;
    progressModifier->SetProgressType(PROGRESS_TYPE_LINEAR);
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
    EXPECT_EQ(progressModifier->isSweeping_, true);

    /**
     * @tc.steps: step4. Set value for the vertical linear progress.
     * @tc.expected: step4. The dateUpdated_ is true.
     */
    SizeF ContentSize3(50.0f, 100.0f);
    progressModifier->SetContentSize(ContentSize3);
    progressModifier->sweepingDate_->Set(0.0f);
    progressModifier->isSweeping_ = true;
    progressModifier->sweepingDateBackup_ = 10000.0f;
    progressModifier->SetProgressType(PROGRESS_TYPE_LINEAR);
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
    EXPECT_TRUE(progressModifier->dateUpdated_);

    /**
     * @tc.steps: step5. Set invisible.
     * @tc.expected: step5. The sweeping animation is stopped.
     */
    value = 0.0f;
    progressModifier->SetContentSize(ContentSize3);
    progressModifier->SetProgressType(PROGRESS_TYPE_LINEAR);
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    progressModifier->isSweeping_ = true;
    progressModifier->SetVisible(false);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));
    EXPECT_EQ(progressModifier->isSweeping_, false);
    EXPECT_EQ(progressModifier->isVisible_, false);

    /**
     * @tc.steps: step6. Set value while invisible.
     * @tc.expected: step6. The value is set but the sweepingDate is not set.
     */
    value = 10.0f;
    progressModifier->SetValue(value);
    EXPECT_EQ(progressModifier->value_->Get(), 10.0f);
    EXPECT_EQ(progressModifier->sweepingDate_->Get(), 0.0f);
}

/**
 * @tc.name: ProgressSetValue002
 * @tc.desc: Test function about setting value.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressSetValue002, TestSize.Level1)
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
    CreateDone(frameNode_);
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
    CreateDone(frameNode_);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto* stack = ViewStackProcessor::GetInstance();
    stack->Push(frameNode_);
    pattern_->SetTextFromUser(true);
    progressModel.SetValue(10.0);
    EXPECT_DOUBLE_EQ(paintProperty_->GetValueValue(0.0), 10.0);

    pattern_->SetTextFromUser(false);
    progressModel.SetValue(10.0);
    EXPECT_EQ(textLayoutProperty->GetContentValue(""), "10%");
    EXPECT_EQ(paintProperty_->GetTextValue(""), "10%");
    progressModel.SetTextDefaultStyle(textNode, VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS);
    EXPECT_EQ(paintProperty_->GetTextValue(""), textLayoutProperty->GetContentValue(""));

    paintProperty_->UpdateEnableShowText(false);
    progressModel.SetValue(20.0);
    EXPECT_EQ(textLayoutProperty->GetContentValue(""), "");
    EXPECT_EQ(paintProperty_->GetTextValue(""), "");
    progressModel.SetTextDefaultStyle(textNode, VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS);
    EXPECT_EQ(paintProperty_->GetTextValue(""), textLayoutProperty->GetContentValue(""));
}

/**
 * @tc.name: ProgressPattern005
 * @tc.desc: Test the TouchEvent of progress, TouchType is CANCEL.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPattern005, TestSize.Level1)
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
    CreateDone(frameNode_);

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
 * @tc.name: ProgressPaintMethod004
 * @tc.desc: Test ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPaintMethod004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode_.
     * @tc.expected: step1. Check the frameNode_ was created successfully.
     */
    ProgressModelNG model = CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_MOON);
    model.SetStrokeWidth(LARG_STROKE_WIDTH);
    model.SetShowText(true);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the paintProperty_.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty_ = frameNode_->GetPaintProperty<ProgressPaintProperty>();
    paintProperty_->UpdateColor(TEST_COLOR);
    paintProperty_->UpdateBackgroundColor(TEST_COLOR);
    paintProperty_->UpdateBorderColor(TEST_COLOR);
    paintProperty_->UpdateMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    paintProperty_->UpdateValue(PROGRESS_MODIFIER_VALUE);
    paintProperty_->UpdateScaleCount(SCALE_COUNT);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty_);
    paintWrapper->geometryNode_->SetContentSize(SizeF(16.f, 16.f));

    /**
     * @tc.steps: step3. Create ProgressPaintMethod. Call the function UpdateContentModifier and GetContentModifier.
     * @tc.expected: step3. Check the properties update before.
     */
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    ProgressPaintMethod progressPaintMethod(PROGRESS_TYPE_LINEAR, PROGRESS_STROKE_WIDTH, progressModifier);
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_FLOAT_EQ(progressPaintMethod.strokeWidth_, PROGRESS_STROKE_WIDTH);

    progressPaintMethod.progressType_ = PROGRESS_TYPE_SCALE;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_FLOAT_EQ(progressPaintMethod.strokeWidth_, 4.f);

    paintWrapper->geometryNode_->SetContentSize(SizeF(30.f, 30.f));
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_FLOAT_EQ(progressPaintMethod.strokeWidth_, 4.f);

    progressPaintMethod.progressType_ = PROGRESS_TYPE_CIRCLE;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_FLOAT_EQ(progressPaintMethod.strokeWidth_, 4.f);
    delete paintWrapper;
}

/**
 * @tc.name: ProgressLayoutAlgorithm003
 * @tc.desc: Test ProgressLayoutAlgorithm without theme.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressLayoutAlgorithm003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_MOON);
    CreateDone(frameNode_);

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
HWTEST_F(ProgressTestNg, ProgressLayoutAlgorithm004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_CAPSULE);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. Create the progressLayoutAlgorithm.
     * @tc.expected: step2. Check the progressLayoutAlgorithm created successfully.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(nullptr));
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
HWTEST_F(ProgressTestNg, ProgressLayoutAlgorithm005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_RING);
    CreateDone(frameNode_);

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
 * @tc.name: ProgressModifier005
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModifier005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    auto modifier = AceType::MakeRefPtr<ProgressModifier>();

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));

    modifier->SetProgressType(PROGRESS_TYPE_SCALE);
    auto contentSize = SizeF(100.0f, 100.0f);
    modifier->SetContentSize(contentSize);
    modifier->onDraw(context);
    EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_SCALE));

    modifier->SetStrokeWidth(CONTEXT_WIDTH);
    modifier->SetScaleWidth(3.f);
    modifier->onDraw(context);
    EXPECT_EQ(modifier->scaleWidth_->Get(), 3.f);
    EXPECT_EQ(modifier->strokeWidth_->Get(), CONTEXT_WIDTH);

    modifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    std::vector<float> valueVector = { 0.f, 50.f, 100.f };
    std::vector<SizeF> contentSizeVector = { SizeF(100.0f, 100.0f), SizeF(50.0f, 100.0f) };
    for (auto i : contentSizeVector) {
        modifier->SetContentSize(i);
        for (auto it : valueVector) {
            modifier->SetValue(it);
            modifier->onDraw(context);
            EXPECT_EQ(modifier->value_->Get(), it);
            EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));
        }
        EXPECT_EQ(modifier->contentSize_->Get(), i);
    }
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
}

/**
 * @tc.name: ProgressModifier006
 * @tc.desc: Test ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModifier006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto modifier = AceType::MakeRefPtr<ProgressModifier>();

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));

    modifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    std::vector<float> valueVector = { 0.f, 50.f, 100.f };
    std::vector<SizeF> contentSizeVector = { SizeF(100.0f, 100.0f), SizeF(50.0f, 100.0f) };
    for (auto i : contentSizeVector) {
        modifier->SetContentSize(i);
        for (auto it : valueVector) {
            modifier->SetValue(it);
            modifier->onDraw(context);
            EXPECT_EQ(modifier->value_->Get(), it);
            EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));
        }
        EXPECT_EQ(modifier->contentSize_->Get(), i);
    }

    std::vector<ProgressType> typeVector = { PROGRESS_TYPE_LINEAR, PROGRESS_TYPE_RING };
    for (auto it : typeVector) {
        modifier->SetProgressType(it);
        modifier->SetMaxValue(0.f);
        modifier->onDraw(context);
        EXPECT_FLOAT_EQ(modifier->maxValue_->Get(), 0.f);
        modifier->SetValue(0.f);
        modifier->onDraw(context);
        EXPECT_FLOAT_EQ(modifier->value_->Get(), 0.f);
        EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(it));
    }
}

/**
 * @tc.name: ProgressModifier007
 * @tc.desc: Test PROGRESS_TYPE_CAPSULE ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModifier007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto modifier = AceType::MakeRefPtr<ProgressModifier>();
    modifier->SetProgressType(PROGRESS_TYPE_CAPSULE);
    auto contentSize = SizeF(100.0f, 100.0f);
    modifier->SetContentSize(contentSize);
    EXPECT_EQ(modifier->contentSize_->Get(), contentSize);
    EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_CAPSULE));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    modifier->SetSweepEffect(true);
    modifier->dateUpdated_ = true;
    modifier->SetValue(10.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 10.f);
    EXPECT_EQ(modifier->sweepEffect_->Get(), true);
    EXPECT_EQ(modifier->isSweeping_, true);
    EXPECT_EQ(modifier->dateUpdated_, false);

    modifier->SetVisible(false);
    modifier->SetSweepEffect(true);
    modifier->SetProgressStatus(ProgressStatus::LOADING);
    modifier->StartCapsuleSweepingAnimationImpl(1.f, 1.f);
    modifier->StartContinuousSweepingAnimation(0.f, 1.f, 1.f);
    EXPECT_EQ(modifier->isVisible_, false);
    EXPECT_EQ(modifier->isSweeping_, false);
    EXPECT_FLOAT_EQ(modifier->sweepingDate_->Get(), 0.f);
    EXPECT_EQ(modifier->sweepEffect_->Get(), true);
    EXPECT_EQ(modifier->progressStatus_->Get(), static_cast<int32_t>(ProgressStatus::LOADING));

    modifier->SetVisible(true);
    modifier->SetProgressType(PROGRESS_TYPE_SCALE);
    modifier->StartContinuousSweepingAnimation(0.f, 1.f, 1.f);
    EXPECT_EQ(modifier->isVisible_, true);
    EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_SCALE));
}

/**
 * @tc.name: ProgressModifier008
 * @tc.desc: Test PROGRESS_TYPE_RING ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModifier008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto modifier = AceType::MakeRefPtr<ProgressModifier>();
    modifier->SetProgressType(PROGRESS_TYPE_RING);
    auto contentSize = SizeF(100.0f, 100.0f);
    modifier->SetContentSize(contentSize);
    EXPECT_EQ(modifier->contentSize_->Get(), contentSize);
    EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    modifier->SetRingSweepEffect(true);
    modifier->dateUpdated_ = true;
    modifier->SetValue(10.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 10.f);
    EXPECT_EQ(modifier->ringSweepEffect_->Get(), true);
    EXPECT_EQ(modifier->isSweeping_, true);
    EXPECT_EQ(modifier->dateUpdated_, false);

    modifier->StartRingLoadingAnimation();
    EXPECT_EQ(modifier->isLoading_, false);
    EXPECT_FLOAT_EQ(modifier->trailingHeadDate_->Get(), 0.f);
    EXPECT_FLOAT_EQ(modifier->trailingTailDate_->Get(), 0.f);

    modifier->SetValue(-10.f);
    modifier->StartRingLoadingAnimation();
    EXPECT_EQ(modifier->isLoading_, false);
    EXPECT_FLOAT_EQ(modifier->trailingHeadDate_->Get(), 0.f);
    EXPECT_FLOAT_EQ(modifier->trailingTailDate_->Get(), 0.f);

    modifier->SetValue(100.f);
    modifier->StartRingSweepingAnimation(100.f);
    modifier->StartContinuousSweepingAnimation(0.f, 1.f, 1.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 100.f);

    modifier->SetVisible(false);
    modifier->StartRingLoadingAnimation();
    modifier->StartRingSweepingAnimation(100.f);
    EXPECT_EQ(modifier->isVisible_, false);

    modifier->isLoading_ = true;
    modifier->StartRingLoadingAnimation();
    EXPECT_EQ(modifier->isLoading_, true);
}

/**
 * @tc.name: ProgressModifier009
 * @tc.desc: Test PROGRESS_TYPE_LINEAR ProgressModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModifier009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ProgressModifier and set ProgressModifier property.
     * @tc.expected: step1. Check the ProgressModifier property value.
     */
    auto modifier = AceType::MakeRefPtr<ProgressModifier>();
    modifier->SetProgressType(PROGRESS_TYPE_LINEAR);
    auto contentSize = SizeF(100.0f, 100.0f);
    modifier->SetContentSize(contentSize);
    EXPECT_EQ(modifier->contentSize_->Get(), contentSize);
    EXPECT_EQ(modifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_LINEAR));

    /**
     * @tc.steps: step2. Set different properties, call function onDraw.
     * @tc.expected: step2. Set the properties success.
     */
    modifier->SetLinearSweepEffect(true);
    modifier->dateUpdated_ = true;
    modifier->SetValue(10.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 10.f);
    EXPECT_EQ(modifier->linearSweepEffect_->Get(), true);
    EXPECT_EQ(modifier->isSweeping_, true);
    EXPECT_EQ(modifier->dateUpdated_, false);

    modifier->SetValue(0.f);
    modifier->StartLinearSweepingAnimation(0.f);
    modifier->dateUpdated_ = true;
    modifier->StartContinuousSweepingAnimation(0.f, 1.f, 1.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 0.f);
    EXPECT_EQ(modifier->isSweeping_, true);
    EXPECT_EQ(modifier->dateUpdated_, false);

    modifier->SetValue(100.f);
    modifier->StartLinearSweepingAnimation(100.f);
    modifier->StartContinuousSweepingAnimation(0.f, 1.f, 1.f);
    EXPECT_FLOAT_EQ(modifier->value_->Get(), 100.f);

    modifier->SetVisible(false);
    modifier->StartLinearSweepingAnimation(100.f);
    EXPECT_EQ(modifier->isVisible_, false);
}

/**
 * @tc.name: ProgressPatternTest000
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPatternTest000, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Progress node
     */
    CreateProgress(VALUE_OF_PROGRESS, MAX_VALUE_OF_PROGRESS, PROGRESS_TYPE_LINEAR);
    CreateDone(frameNode_);
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
HWTEST_F(ProgressTestNg, ProgressPrivacySensitiveTest001, TestSize.Level1)
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
    EXPECT_EQ(textPattern->IsSensitiveEnalbe(), false);
    pattern->OnSensitiveStyleChange(true);
    EXPECT_EQ(progressPaintProperty->GetIsSensitive().value_or(false), true);
    EXPECT_EQ(textPattern->IsSensitiveEnalbe(), true);
}
} // namespace OHOS::Ace::NG
