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

#include <cstddef>
#include <memory>
#include <optional>

#include "gtest/gtest.h"

#include "base/memory/referenced.h"
#define private public
#define protected public

#include "base/memory/ace_type.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct CreateProperty {
    std::optional<double> maxValue = std::nullopt;
    std::optional<double> value = std::nullopt;
    std::optional<ProgressType> progressType = std::nullopt;
};

struct TestProperty {
    std::optional<double> value = std::nullopt;
    std::optional<Dimension> strokeWidth = std::nullopt;
    std::optional<Dimension> scaleWidth = std::nullopt;
    std::optional<int32_t> scaleCount = std::nullopt;
    std::optional<Color> frontColor = std::nullopt;
    std::optional<Color> bgColor = std::nullopt;
};

namespace {
constexpr double MAX_VALUE_OF_PROGRESS = 120.0;
constexpr double VALUE_OF_PROGRESS = 20.0;
constexpr double VALUE_OF_PROGRESS_2 = 40.0;
constexpr ProgressType PROGRESS_TYPE_LINEAR = ProgressType::LINEAR;
constexpr ProgressType PROGRESS_TYPE_RING = ProgressType::RING;
constexpr ProgressType PROGRESS_TYPE_SCALE = ProgressType::SCALE;
constexpr ProgressType PROGRESS_TYPE_MOON = ProgressType::MOON;
constexpr ProgressType PROGRESS_TYPE_CAPSULE = ProgressType::CAPSULE;
constexpr Dimension STORKE_WIDTH = 10.0_vp;
constexpr Dimension LARG_STORKE_WIDTH = 500.0_vp;
constexpr Dimension SCALE_WIDTH = 10.0_vp;
constexpr int32_t SCALE_COUNT = 120;
constexpr int32_t TYPE_OF_PROGRESS = 5;
constexpr Color FRONT_COLOR = Color(0xff0000ff);
constexpr Color BG_COLOR = Color(0xffc0c0c0);
constexpr float PROGRESS_COMPONENT_MAXSIZE_WIDTH = 720.0f;
constexpr float PROGRESS_COMPONENT_MAXSIZE_HEIGHT = 1400.0f;
constexpr float PROGRESS_COMPONENT_WIDTH = 200.0f;
constexpr float LARG_PROGRESS_COMPONENT_WIDTH = 2000.0f;
constexpr float PROGRESS_COMPONENT_HEIGHT = 200.0f;
constexpr float LARG_PROGRESS_COMPONENT_HEIGHT = 2000.0f;
constexpr float NUMBER_OF_TWO = 2.0f;
constexpr Dimension DEFALT_RING_DIAMETER = 72.0_vp;
constexpr Dimension TEST_PROGRERSS_THICKNESS = 4.0_vp;
constexpr Dimension TEST_PROGRESS_STROKE_WIDTH = 10.0_vp;
constexpr Dimension TEST_PROGRESS_DEFAULT_WIDTH = 300.0_vp;
constexpr Dimension TEST_PROGRESS_DEFAULT_DIAMETER = 72.0_vp;
constexpr Dimension TEST_PROGRESS_SCALE_WIDTH = 2.0_vp;
constexpr Dimension DEFALUT_STROKE_WIDTH = 2.0_vp;

CreateProperty creatProperty;
DirtySwapConfig config;
ProgressModelNG progressModel;
RefPtr<ProgressTheme> progressTheme;
RefPtr<MockThemeManager> themeManager;
} // namespace

class ProgressPatternTestNg : public testing::Test {
public:
    void CheckValue(const RefPtr<FrameNode>& frameNode, const TestProperty& testProperty);
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}

protected:
    RefPtr<FrameNode> CreateProgressParagraph(const TestProperty& testProperty);
};

void ProgressPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    creatProperty.maxValue = std::make_optional(MAX_VALUE_OF_PROGRESS);
    creatProperty.value = std::make_optional(VALUE_OF_PROGRESS);
    themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->trackThickness_ = TEST_PROGRERSS_THICKNESS;
    progressTheme->scaleLength_ = TEST_PROGRESS_STROKE_WIDTH;
    progressTheme->trackWidth_ = TEST_PROGRESS_DEFAULT_WIDTH;
    progressTheme->ringDiameter_ = TEST_PROGRESS_DEFAULT_DIAMETER;
    progressTheme->trackBgColor_ = BG_COLOR;
    progressTheme->trackSelectedColor_ = FRONT_COLOR;
    progressTheme->scaleNumber_ = SCALE_COUNT;
    progressTheme->scaleWidth_ = TEST_PROGRESS_SCALE_WIDTH;
}

void ProgressPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
    progressTheme = nullptr;
    themeManager = nullptr;
}

RefPtr<FrameNode> ProgressPatternTestNg::CreateProgressParagraph(const TestProperty& testProperty)
{
    progressModel.Create(
        0.0, creatProperty.value.value(), 0.0, creatProperty.maxValue.value(), creatProperty.progressType.value());

    if (testProperty.value.has_value()) {
        progressModel.SetValue(testProperty.value.value());
    }

    if (testProperty.strokeWidth.has_value()) {
        progressModel.SetStrokeWidth(testProperty.strokeWidth.value());
    }

    if (testProperty.scaleWidth.has_value()) {
        progressModel.SetScaleWidth(testProperty.scaleWidth.value());
    }

    if (testProperty.scaleCount.has_value()) {
        progressModel.SetScaleCount(testProperty.scaleCount.value());
    }

    if (testProperty.frontColor.has_value()) {
        progressModel.SetColor(testProperty.frontColor.value());
    }

    if (testProperty.bgColor.has_value()) {
        progressModel.SetBackgroundColor(testProperty.bgColor.value());
    }

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    return frameNode;
}

void ProgressPatternTestNg::CheckValue(const RefPtr<FrameNode>& frameNode, const TestProperty& testProperty)
{
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    EXPECT_NE(progressLayoutProperty, nullptr);
    RefPtr<ProgressPaintProperty> progresspaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    EXPECT_NE(progresspaintProperty, nullptr);

    EXPECT_EQ(progresspaintProperty->GetMaxValue(), creatProperty.maxValue.value());
    EXPECT_EQ(progressLayoutProperty->GetType(), creatProperty.progressType.value());

    if (testProperty.value.has_value()) {
        if (testProperty.value.value() <= creatProperty.maxValue.value()) {
            EXPECT_EQ(progresspaintProperty->GetValue(), testProperty.value.value());
        } else {
            EXPECT_EQ(progresspaintProperty->GetValue(), creatProperty.maxValue.value());
        }
    } else {
        EXPECT_EQ(progresspaintProperty->GetValue(), creatProperty.value.value());
    }

    if (testProperty.strokeWidth.has_value()) {
        EXPECT_EQ(progressLayoutProperty->GetStrokeWidth(), testProperty.strokeWidth.value());
    }

    if (testProperty.scaleWidth.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetScaleWidth(), testProperty.scaleWidth.value());
    }

    if (testProperty.scaleCount.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetScaleCount(), testProperty.scaleCount.value());
    }

    if (testProperty.frontColor.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetColor(), testProperty.frontColor.value());
    }

    if (testProperty.bgColor.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetBackgroundColor(), testProperty.bgColor.value());
    }
}

/**
 * @tc.name: ProgressCreate001
 * @tc.desc: Test all the pattern of progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressPatternTestNg, ProgressCreate001, TestSize.Level1)
{
    TestProperty testProperty;
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_LINEAR);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<ProgressLayoutAlgorithm> progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, nullptr, nullptr);
    EXPECT_NE(layoutWrapper, nullptr);
    auto progressPaintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(progressPaintMethod, nullptr);
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();
    bool skipMeasures[2] = { false, true };
    for (int32_t i = 0; i < 2; ++i) {
        for (int32_t j = 0; j < 2; ++j) {
            config.skipMeasure = skipMeasures[i];
            auto layoutAlgorithmWrapper =
                AceType::MakeRefPtr<LayoutAlgorithmWrapper>(progressLayoutAlgorithm, skipMeasures[i]);
            layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
            layoutWrapper->skipMeasureContent_ = skipMeasures[j];
            auto isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
            EXPECT_EQ(isSwap, !(skipMeasures[i] || skipMeasures[j]));
        }
    }
}

/**
 * @tc.name: ProgressSetVlaue001
 * @tc.desc: Test functhion about setting value.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressPatternTestNg, ProgressSetVlaue001, TestSize.Level1)
{
    TestProperty testProperty;
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_LINEAR);
    testProperty.value = std::make_optional(VALUE_OF_PROGRESS_2);

    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);

    testProperty.value = std::make_optional(MAX_VALUE_OF_PROGRESS * NUMBER_OF_TWO);
    frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
}

/**
 * @tc.name: ProgressLayoutAlgorithm001
 * @tc.desc: Test ProgressLayoutAlgorithm without theme.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressPatternTestNg, ProgressLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    TestProperty testProperty;
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_LINEAR);

    /**
     * @tc.steps: step2. create progress frameNode and check the proregss properties with expected value .
     * @tc.expected: step2. get frameNode success and proregss properties equals expected value.
     */
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    EXPECT_NE(progressLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.maxSize.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to porgress frameNode layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapper layoutWrapper(frameNode, nullptr, progressLayoutProperty);

    /**
     * @tc.steps: step5. do linear porgress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(nullptr));
    auto progressPattern = frameNode->GetPattern();
    EXPECT_NE(progressPattern, nullptr);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    EXPECT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);

    EXPECT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_LINEAR);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), DEFALUT_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_WIDTH);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_HEIGHT);
}

/**
 * @tc.name: LinearProgressCreator001
 * @tc.desc: Test all the properties of linear progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressPatternTestNg, LinearProgressCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    TestProperty testProperty;
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_LINEAR);
    testProperty.strokeWidth = std::make_optional(STORKE_WIDTH);
    testProperty.frontColor = std::make_optional(FRONT_COLOR);
    testProperty.bgColor = std::make_optional(BG_COLOR);

    /**
     * @tc.steps: step2. create progress frameNode and check the proregss properties with expected value .
     * @tc.expected: step2. get frameNode success and proregss properties equals expected value.
     */
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    EXPECT_NE(progressLayoutProperty, nullptr);
    RefPtr<ProgressPaintProperty> progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    EXPECT_NE(progressPaintProperty, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    progressPaintProperty->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.maxSize.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to porgress frameNode layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapper layoutWrapper(frameNode, nullptr, progressLayoutProperty);

    /**
     * @tc.steps: step5. do linear porgress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    auto progressPattern = frameNode->GetPattern();
    EXPECT_NE(progressPattern, nullptr);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    EXPECT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_LINEAR);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), STORKE_WIDTH.ConvertToPx() * NUMBER_OF_TWO);
    EXPECT_EQ(size->Width(), TEST_PROGRESS_DEFAULT_WIDTH.ConvertToPx());

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);

    contentConstraint.selfIdealSize.SetWidth(LARG_PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(LARG_PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_MAXSIZE_WIDTH);
}

/**
 * @tc.name: LinearProgressCreator002
 * @tc.desc: Test all the properties of linear progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressPatternTestNg, LinearProgressCreator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    TestProperty testProperty;
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_LINEAR);
    testProperty.strokeWidth = std::make_optional(LARG_STORKE_WIDTH);
    testProperty.frontColor = std::make_optional(FRONT_COLOR);
    testProperty.bgColor = std::make_optional(BG_COLOR);

    /**
     * @tc.steps: step2. create progress frameNode and check the proregss properties with expected value .
     * @tc.expected: step2. get frameNode success and proregss properties equals expected value.
     */
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    EXPECT_NE(progressLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.maxSize.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to porgress frameNode layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapper layoutWrapper(frameNode, nullptr, progressLayoutProperty);

    /**
     * @tc.steps: step5. do linear porgress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    auto progressPattern = frameNode->GetPattern();
    EXPECT_NE(progressPattern, nullptr);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    EXPECT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_LINEAR);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), TEST_PROGRESS_DEFAULT_WIDTH.ConvertToPx() / NUMBER_OF_TWO);
    EXPECT_EQ(size->Height(), LARG_STORKE_WIDTH.ConvertToPx() * NUMBER_OF_TWO);
    EXPECT_EQ(size->Width(), TEST_PROGRESS_DEFAULT_WIDTH.ConvertToPx());

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), PROGRESS_COMPONENT_HEIGHT / NUMBER_OF_TWO);

    contentConstraint.selfIdealSize.SetWidth(LARG_PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(LARG_PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), PROGRESS_COMPONENT_MAXSIZE_WIDTH / NUMBER_OF_TWO);
}

/**
 * @tc.name: RingProgressCreator001
 * @tc.desc: Test all the properties of ring progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressPatternTestNg, RingProgressCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of ring progress.
     */
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_RING);

    TestProperty testProperty;
    testProperty.strokeWidth = std::make_optional(STORKE_WIDTH);
    testProperty.frontColor = std::make_optional(FRONT_COLOR);
    testProperty.bgColor = std::make_optional(BG_COLOR);

    /**
     * @tc.steps: step2. create progress frameNode and check the proregss properties with expected value .
     * @tc.expected: step2. get frameNode success and proregss properties equals expected value.
     */
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    EXPECT_NE(progressLayoutProperty, nullptr);
    RefPtr<ProgressPaintProperty> progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    EXPECT_NE(progressPaintProperty, nullptr);

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.maxSize.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to porgress frameNode layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapper layoutWrapper(frameNode, nullptr, progressLayoutProperty);

    /**
     * @tc.steps: step5. do ring porgress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    progressPaintProperty->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
    auto progressPattern = frameNode->GetPattern();
    EXPECT_NE(progressPattern, nullptr);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    EXPECT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_RING);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), DEFALT_RING_DIAMETER.ConvertToPx());
    EXPECT_EQ(size->Width(), DEFALT_RING_DIAMETER.ConvertToPx());

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_WIDTH);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);

    LayoutConstraintF contentConstraint2;
    contentConstraint2.maxSize.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint2.maxSize.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    contentConstraint2.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint2, &layoutWrapper);
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_HEIGHT);

    contentConstraint2.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint2, &layoutWrapper);
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);
}

/**
 * @tc.name: ScaleProgressFrameNodeCreator001
 * @tc.desc: Test all the properties of scale progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressPatternTestNg, ScaleProgressFrameNodeCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of Scale progress.
     */
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_SCALE);

    TestProperty testProperty;
    testProperty.strokeWidth = std::make_optional(STORKE_WIDTH);
    testProperty.scaleWidth = std::make_optional(SCALE_WIDTH);
    testProperty.scaleCount = std::make_optional(SCALE_COUNT);
    testProperty.frontColor = std::make_optional(FRONT_COLOR);
    testProperty.bgColor = std::make_optional(BG_COLOR);

    /**
     * @tc.steps: step2. create progress frameNode and check the proregss properties with expected value .
     * @tc.expected: step2. get frameNode success and proregss properties equals expected value.
     */
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    EXPECT_NE(progressLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.maxSize.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to porgress frameNode layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapper layoutWrapper(frameNode, nullptr, progressLayoutProperty);

    /**
     * @tc.steps: step5. do ring porgress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    EXPECT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_SCALE);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), TEST_PROGRESS_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);
}

/**
 * @tc.name: ProgressFrameNodeCreator004
 * @tc.desc: Test all the properties of moon type progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressPatternTestNg, ProgressFrameNodeCreator004, TestSize.Level1)
{
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_MOON);

    TestProperty testProperty;
    testProperty.value = std::make_optional(VALUE_OF_PROGRESS_2);

    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
}

/**
 * @tc.name: CapulseProgressCreator001
 * @tc.desc: Test all the properties of Capulse type progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressPatternTestNg, CapulseProgressCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of ring progress.
     */
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_CAPSULE);

    TestProperty testProperty;
    testProperty.strokeWidth = std::make_optional(STORKE_WIDTH);

    /**
     * @tc.steps: step2. create progress frameNode and check the proregss properties with expected value .
     * @tc.expected: step2. get frameNode success and proregss properties equals expected value.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    EXPECT_NE(progressLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. create contentConstraint.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint.maxSize.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);

    /**
     * @tc.steps: step4. add layoutWrapper to porgress frameNode layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    LayoutWrapper layoutWrapper(frameNode, nullptr, progressLayoutProperty);

    /**
     * @tc.steps: step5. do capsule porgress LayoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    auto progressPattern = frameNode->GetPattern();
    EXPECT_NE(progressPattern, nullptr);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    EXPECT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_CAPSULE);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), DEFALT_RING_DIAMETER.ConvertToPx());
    EXPECT_EQ(size->Width(), DEFALT_RING_DIAMETER.ConvertToPx());

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(size->Height(), DEFALT_RING_DIAMETER.ConvertToPx());
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);

    LayoutConstraintF contentConstraint2;
    contentConstraint2.maxSize.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint2.maxSize.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    contentConstraint2.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint2, &layoutWrapper);
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), DEFALT_RING_DIAMETER.ConvertToPx());
}

/**
 * @tc.name: GetContentDrawFunction
 * @tc.desc: Test the funtion GetContentDrawFunction in ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressPatternTestNg, GetContentDrawFunction, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.strokeWidth = std::make_optional(LARG_STORKE_WIDTH);
    testProperty.scaleCount = std::make_optional(SCALE_COUNT);
    testProperty.scaleWidth = std::make_optional(SCALE_WIDTH);
    ProgressType progressType[TYPE_OF_PROGRESS] = { PROGRESS_TYPE_LINEAR, PROGRESS_TYPE_RING, PROGRESS_TYPE_SCALE,
        PROGRESS_TYPE_MOON, PROGRESS_TYPE_CAPSULE };
    for (int32_t i = 0; i < TYPE_OF_PROGRESS; i++) {
        /**
         * @tc.steps: step1. create testProperty and set properties of progress.
         */
        creatProperty.progressType = std::make_optional(progressType[i]);

        /**
         * @tc.steps: step2. create progress frameNode and check the proregss properties with expected value .
         * @tc.expected: step2. get frameNode success and proregss properties equals expected value.
         */
        RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
        CheckValue(frameNode, testProperty);
        RefPtr<ProgressPaintProperty> progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
        EXPECT_NE(progressPaintProperty, nullptr);

        /**
         * @tc.steps: step3. create GeometryNode and PaintWrapper, ProgressPaintMethod.
         */
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        geometryNode->SetContentSize(SizeF(PROGRESS_COMPONENT_MAXSIZE_WIDTH, PROGRESS_COMPONENT_MAXSIZE_HEIGHT));
        geometryNode->SetContentOffset(OffsetF(0, 0));
        RefPtr<PaintWrapper> paintWrapper =
            AceType::MakeRefPtr<PaintWrapper>(RenderContext::Create(), geometryNode, progressPaintProperty);
        auto progressPaintMethod =
            AceType::MakeRefPtr<ProgressPaintMethod>(progressType[i], LARG_STORKE_WIDTH.ConvertToPx());

        /**
         * @tc.steps: step4. call the function named GetContentDrawFunction in ProgressPaintMethod.
         */
        auto cnvasDrawFunction = progressPaintMethod->GetContentDrawFunction(AceType::RawPtr(paintWrapper));
        EXPECT_NE(cnvasDrawFunction, nullptr);

        geometryNode->SetContentSize(SizeF(PROGRESS_COMPONENT_MAXSIZE_HEIGHT, PROGRESS_COMPONENT_MAXSIZE_WIDTH));
        cnvasDrawFunction = progressPaintMethod->GetContentDrawFunction(AceType::RawPtr(paintWrapper));
        EXPECT_NE(cnvasDrawFunction, nullptr);
    }
}

/**
 * @tc.name: ProgressPaintLinear001
 * @tc.desc: Test ProgressPaintMethod about all type.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressPatternTestNg, ProgressPaintLinear001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties.
     */
    TestProperty testProperty;
    testProperty.strokeWidth = std::make_optional(LARG_STORKE_WIDTH);
    testProperty.scaleCount = std::make_optional(SCALE_COUNT);
    testProperty.scaleWidth = std::make_optional(SCALE_WIDTH);
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_LINEAR);

    /**
     * @tc.steps: step2. create progress frameNode and check the proregss properties with expected value .
     * @tc.expected: step2. get frameNode success and proregss properties equals expected value.
     */
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<ProgressPaintProperty> progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    EXPECT_NE(progressPaintProperty, nullptr);

    /**
     * @tc.steps: step3. create GeometryNode and PaintWrapper, ProgressPaintMethod.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    SizeF contentSize(PROGRESS_COMPONENT_MAXSIZE_WIDTH, PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    OffsetF contentOffset(0, 0);
    RefPtr<PaintWrapper> paintWrapper =
        AceType::MakeRefPtr<PaintWrapper>(RenderContext::Create(), geometryNode, progressPaintProperty);
    auto progressPaintMethod =
        AceType::MakeRefPtr<ProgressPaintMethod>(PROGRESS_TYPE_LINEAR, LARG_STORKE_WIDTH.ConvertToPx());
    RSCanvas canvas;

    /**
     * @tc.steps: step4. call the function named Paint in ProgressPaintMethod when width is lager than hight.
     */
    progressPaintMethod->PaintLinear(canvas, contentOffset, contentSize);
    progressPaintMethod->PaintRing(canvas, contentOffset, contentSize);
    progressPaintMethod->PaintScaleRing(canvas, contentOffset, contentSize);
    progressPaintMethod->PaintMoon(canvas, contentOffset, contentSize);
    progressPaintMethod->PaintCapsule(canvas, contentOffset, contentSize);
    progressPaintMethod->PaintVerticalCapsule(canvas, contentOffset, contentSize);

    /**
     * @tc.steps: step5. call the function named Paint in ProgressPaintMethod when value has been set as 50.
     */
    progressPaintMethod->value_ = MAX_VALUE_OF_PROGRESS / NUMBER_OF_TWO;
    progressPaintMethod->PaintVerticalCapsule(canvas, contentOffset, contentSize);

    /**
     * @tc.steps: step5. call the function named Paint in ProgressPaintMethod when value has been set as 80.
     */
    progressPaintMethod->value_ = MAX_VALUE_OF_PROGRESS - VALUE_OF_PROGRESS;
    progressPaintMethod->PaintLinear(canvas, contentOffset, contentSize);
    progressPaintMethod->PaintMoon(canvas, contentOffset, contentSize);
    progressPaintMethod->PaintCapsule(canvas, contentOffset, contentSize);
    progressPaintMethod->PaintVerticalCapsule(canvas, contentOffset, contentSize);

    /**
     * @tc.steps: step5. call the function named Paint in ProgressPaintMethod when width is less than hight.
     */
    contentSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    contentSize.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    progressPaintMethod->PaintLinear(canvas, contentOffset, contentSize);

    progressPaintMethod->value_ = VALUE_OF_PROGRESS;
    progressPaintMethod->PaintLinear(canvas, contentOffset, contentSize);

    progressPaintMethod->value_ = MAX_VALUE_OF_PROGRESS / NUMBER_OF_TWO;
    progressPaintMethod->PaintCapsule(canvas, contentOffset, contentSize);

    progressPaintMethod->scaleWidth_ = SCALE_WIDTH.ConvertToPx() * NUMBER_OF_TWO;
    progressPaintMethod->PaintScaleRing(canvas, contentOffset, contentSize);
}
} // namespace OHOS::Ace::NG
