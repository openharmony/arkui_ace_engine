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
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct CreateProperty {
    std::optional<double> maxValue;
    std::optional<double> value;
    std::optional<ProgressType> progressType;
};

struct TestProperty {
    std::optional<double> value;
    std::optional<Dimension> strokeWidth;
    std::optional<Dimension> scaleWidth;
    std::optional<int32_t> scaleCount;
    std::optional<Color> frontColor;
    std::optional<Color> bgColor;
    std::optional<Color> borderColor;
    std::optional<Dimension> borderWidth;
    std::optional<bool> sweepEffect;
    std::optional<Color> fontColor;
    std::optional<Dimension> fontSize;
    std::optional<std::optional<std::string>> content;
    std::optional<FontWeight> fontWeight;
    std::optional<std::vector<std::string>> fontFamily;
    std::optional<Ace::FontStyle> fontStyle;
    std::optional<bool> paintShadow;
    std::optional<ProgressStatus> progressStatus;
    std::optional<Gradient> gradient;
    std::optional<bool> ringSweepEffect;
    std::optional<bool> linearSweepEffect;
    std::optional<bool> showText;
};

namespace {
constexpr double MAX_VALUE_OF_PROGRESS = 120.0;
constexpr double PROGRESS_MODLE_NG_CACHEDVALUE = 10.0;
constexpr double PROGRESS_MODLE_NG_MAX = 20.0;
constexpr double PROGRESS_MODLE_NG_MIN = 5.0;
constexpr double PROGRESS_MODLE_NG_VALUE = 10.0;
constexpr double VALUE_OF_PROGRESS = 20.0;
constexpr double VALUE_OF_PROGRESS_2 = 40.0;
constexpr ProgressType PROGRESS_TYPE_LINEAR = ProgressType::LINEAR;
constexpr ProgressType PROGRESS_TYPE_RING = ProgressType::RING;
constexpr ProgressType PROGRESS_TYPE_SCALE = ProgressType::SCALE;
constexpr ProgressType PROGRESS_TYPE_MOON = ProgressType::MOON;
constexpr ProgressType PROGRESS_TYPE_CAPSULE = ProgressType::CAPSULE;
constexpr ProgressType PROGRESS_TYPE_CIRCLE = ProgressType::CIRCLE;
constexpr Dimension STORKE_WIDTH = 10.0_vp;
constexpr Dimension LARG_STORKE_WIDTH = 500.0_vp;
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
constexpr float NUMBER_OF_TWO = 2.0f;
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
constexpr Dimension DEFALT_RING_DIAMETER = 72.0_vp;
constexpr Dimension DEFALT_CAPSULE_WIDTH = 28.0_vp;
constexpr Dimension TEST_PROGRERSS_THICKNESS = 4.0_vp;
constexpr Dimension TEST_PROGRESS_STROKE_WIDTH = 10.0_vp;
constexpr Dimension TEST_PROGRESS_DEFAULT_WIDTH = 300.0_vp;
constexpr Dimension TEST_PROGRESS_DEFAULT_DIAMETER = 72.0_vp;
constexpr Dimension TEST_PROGRESS_SCALE_WIDTH = 2.0_vp;
constexpr Dimension DEFALUT_STROKE_WIDTH = 2.0_vp;
const Color TEST_COLOR = Color::BLUE;
const LinearColor TEST_LINEARCOLOR = LinearColor(TEST_COLOR);
constexpr float VALUE_OF_SET_VALUE = 10.0f;
constexpr Dimension BORDER_WIDTH = 2.0_vp;
constexpr Dimension FONT_SIZE = 12.0_vp;
const std::string FONT_CONTEXT = "start";
const FontWeight FONT_WEIGHT = FontWeight::BOLDER;
const std::vector<std::string> FONT_FAMILY = { "serif" };
constexpr Dimension DEFALUT_SPACE = 4.0_vp;

CreateProperty creatProperty;
DirtySwapConfig config;
ProgressModelNG progressModel;
RefPtr<ProgressTheme> progressTheme;
RefPtr<MockThemeManager> themeManager;
} // namespace

class ProgressTestNg : public testing::Test {
public:
    void CheckValue(const RefPtr<FrameNode>& frameNode, const TestProperty& testProperty);
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}

protected:
    RefPtr<FrameNode> CreateProgressParagraph(const TestProperty& testProperty);
};

void ProgressTestNg::SetUpTestCase()
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

void ProgressTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
    progressTheme = nullptr;
    themeManager = nullptr;
}

RefPtr<FrameNode> ProgressTestNg::CreateProgressParagraph(const TestProperty& testProperty)
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

    if (testProperty.borderColor.has_value()) {
        progressModel.SetBorderColor(testProperty.borderColor.value());
    }

    if (testProperty.borderWidth.has_value()) {
        progressModel.SetBorderWidth(testProperty.borderWidth.value());
    }

    if (testProperty.sweepEffect.has_value()) {
        progressModel.SetSweepingEffect(testProperty.sweepEffect.value());
    }

    if (testProperty.fontColor.has_value()) {
        progressModel.SetFontColor(testProperty.fontColor.value());
    }

    if (testProperty.fontSize.has_value()) {
        progressModel.SetFontSize(testProperty.fontSize.value());
    }

    if (testProperty.content.has_value()) {
        progressModel.SetText(testProperty.content.value());
    } else {
        progressModel.SetText(std::nullopt);
    }

    if (testProperty.fontWeight.has_value()) {
        progressModel.SetFontWeight(testProperty.fontWeight.value());
    }

    if (testProperty.fontFamily.has_value()) {
        progressModel.SetFontFamily(testProperty.fontFamily.value());
    }

    if (testProperty.fontStyle.has_value()) {
        progressModel.SetItalicFontStyle(testProperty.fontStyle.value());
    }

    if (testProperty.paintShadow.has_value()) {
        progressModel.SetPaintShadow(testProperty.paintShadow.value());
    }

    if (testProperty.progressStatus.has_value()) {
        progressModel.SetProgressStatus(testProperty.progressStatus.value());
    }

    if (testProperty.gradient.has_value()) {
        progressModel.SetGradientColor(testProperty.gradient.value());
    }

    if (testProperty.ringSweepEffect.has_value()) {
        progressModel.SetRingSweepingEffect(testProperty.ringSweepEffect.value());
    }

    if (testProperty.linearSweepEffect.has_value()) {
        progressModel.SetLinearSweepingEffect(testProperty.linearSweepEffect.value());
    }

    if (testProperty.showText.has_value()) {
        progressModel.SetShowText(testProperty.showText.value());
    }

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    return frameNode;
}

void ProgressTestNg::CheckValue(const RefPtr<FrameNode>& frameNode, const TestProperty& testProperty)
{
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    ASSERT_NE(progressLayoutProperty, nullptr);
    RefPtr<ProgressPaintProperty> progresspaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progresspaintProperty, nullptr);

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

    if (testProperty.borderColor.has_value() && progressLayoutProperty->GetType() == PROGRESS_TYPE_CAPSULE) {
        EXPECT_EQ(progresspaintProperty->GetBorderColor(), testProperty.borderColor.value());
    }

    if (testProperty.sweepEffect.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetEnableScanEffect(), testProperty.sweepEffect.value());
    }

    if (testProperty.fontColor.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetTextColor(), testProperty.fontColor.value());
    }

    if (testProperty.fontSize.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetTextSize(), testProperty.fontSize.value());
    }

    if (testProperty.content.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetText(), testProperty.content.value());
    }

    if (testProperty.paintShadow.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetPaintShadow(), testProperty.paintShadow.value());
    }

    if (testProperty.progressStatus.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetProgressStatus(), testProperty.progressStatus.value());
    }

    if (testProperty.gradient.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetGradientColor(), testProperty.gradient.value());
    }

    if (testProperty.ringSweepEffect.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetEnableRingScanEffect(), testProperty.ringSweepEffect.value());
    }

    if (testProperty.linearSweepEffect.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetEnableLinearScanEffect(), testProperty.linearSweepEffect.value());
    }

    if (testProperty.showText.has_value()) {
        EXPECT_EQ(progresspaintProperty->GetEnableShowText(), testProperty.showText.value());
    }
}

/**
 * @tc.name: ProgressCreate001
 * @tc.desc: Test all the pattern of progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressCreate001, TestSize.Level1)
{
    TestProperty testProperty;
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_LINEAR);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<ProgressLayoutAlgorithm> progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, nullptr, nullptr);
    ASSERT_NE(layoutWrapper, nullptr);
    auto progressPaintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(progressPaintMethod, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
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
HWTEST_F(ProgressTestNg, ProgressSetVlaue001, TestSize.Level1)
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
HWTEST_F(ProgressTestNg, ProgressLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of linear progress.
     */
    TestProperty testProperty;
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_LINEAR);

    /**
     * @tc.steps: step2. create progress frameNode and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode success and progress properties equals expected value.
     */
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    ASSERT_NE(progressLayoutProperty, nullptr);

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
    ASSERT_NE(progressPattern, nullptr);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    ASSERT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);

    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_LINEAR);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), DEFALUT_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), DEFALUT_STROKE_WIDTH.ConvertToPx());
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
    auto progressLayoutProperty = AceType::MakeRefPtr<ProgressLayoutProperty>();
    ASSERT_NE(progressLayoutProperty, nullptr);
    progressLayoutProperty->UpdateType(PROGRESS_TYPE_SCALE);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    ASSERT_NE(progressLayoutProperty, nullptr);
    LayoutWrapper layoutWrapper(nullptr, nullptr, progressLayoutProperty);
    /**
     * @tc.steps: step2. get strokeWidth from theme, and return width and height according to RingDiameter.
     */
    auto progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->trackThickness_ = TEST_PROGRESS_STROKE_WIDTH;
    progressTheme->ringDiameter_ = DEFALT_RING_DIAMETER;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    auto size = progressLayoutAlgorithm->MeasureContent(LayoutConstraintF(), &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_SCALE);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), TEST_PROGRESS_STROKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), DEFALT_RING_DIAMETER.ConvertToPx());
    EXPECT_EQ(size->Width(), DEFALT_RING_DIAMETER.ConvertToPx());
}

/**
 * @tc.name: LinearProgressCreator001
 * @tc.desc: Test all the properties of linear progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, LinearProgressCreator001, TestSize.Level1)
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
     * @tc.steps: step2. create progress frameNode and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode success and progress properties equals expected value.
     */
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    ASSERT_NE(progressLayoutProperty, nullptr);
    RefPtr<ProgressPaintProperty> progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
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
    ASSERT_NE(progressPattern, nullptr);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    ASSERT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_LINEAR);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), TEST_PROGRESS_DEFAULT_WIDTH.ConvertToPx());

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);

    contentConstraint.selfIdealSize.SetWidth(LARG_PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(LARG_PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    EXPECT_EQ(size->Width(), STORKE_WIDTH.ConvertToPx());
}

/**
 * @tc.name: LinearProgressCreator002
 * @tc.desc: Test all the properties of linear progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, LinearProgressCreator002, TestSize.Level1)
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
     * @tc.steps: step2. create progress frameNode and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode success and progress properties equals expected value.
     */
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    ASSERT_NE(progressLayoutProperty, nullptr);

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
    ASSERT_NE(progressPattern, nullptr);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    ASSERT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_LINEAR);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), LARG_STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), LARG_STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), TEST_PROGRESS_DEFAULT_WIDTH.ConvertToPx());

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size.value(), SizeF(PROGRESS_COMPONENT_WIDTH, PROGRESS_COMPONENT_HEIGHT));
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), LARG_STORKE_WIDTH.ConvertToPx());
}

/**
 * @tc.name: RingProgressCreator001
 * @tc.desc: Test all the properties of ring progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, RingProgressCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of ring progress.
     */
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_RING);
    TestProperty testProperty;
    testProperty.strokeWidth = std::make_optional(STORKE_WIDTH);
    testProperty.frontColor = std::make_optional(FRONT_COLOR);
    testProperty.bgColor = std::make_optional(BG_COLOR);
    Gradient gradient;
    GradientColor gradientColorEnd;
    GradientColor gradientColorStart;
    gradientColorEnd.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorStart.SetLinearColor(LinearColor(Color::WHITE));
    gradientColorEnd.SetDimension(Dimension(0.0));
    gradientColorStart.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    gradient.AddColor(gradientColorStart);
    testProperty.paintShadow = std::make_optional(true);
    testProperty.progressStatus = std::make_optional(ProgressStatus::PROGRESSING);
    testProperty.gradient = std::make_optional(gradient);

    /**
     * @tc.steps: step2. create progress frameNode and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode success and progress properties equals expected value.
     */
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    ASSERT_NE(progressLayoutProperty, nullptr);
    RefPtr<ProgressPaintProperty> progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
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
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    ASSERT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_RING);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), DEFALT_RING_DIAMETER.ConvertToPx());
    EXPECT_EQ(size->Width(), DEFALT_RING_DIAMETER.ConvertToPx());

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_WIDTH);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);

    LayoutConstraintF contentConstraint2;
    contentConstraint2.maxSize.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint2.maxSize.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
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
     * @tc.steps: step1. create testProperty and set properties of Scale progress.
     */
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_SCALE);

    TestProperty testProperty;
    testProperty.strokeWidth = std::make_optional(STORKE_WIDTH);
    testProperty.scaleWidth = std::make_optional(SCALE_WIDTH);
    testProperty.scaleCount = std::make_optional(SCALE_COUNT);
    testProperty.frontColor = std::make_optional(FRONT_COLOR);
    testProperty.bgColor = std::make_optional(BG_COLOR);
    testProperty.borderColor = std::make_optional(BORDER_COLOR);
    /**
     * @tc.steps: step2. create progress frameNode and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode success and progress properties equals expected value.
     */
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    ASSERT_NE(progressLayoutProperty, nullptr);

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
    ASSERT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
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
HWTEST_F(ProgressTestNg, ProgressFrameNodeCreator004, TestSize.Level1)
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
HWTEST_F(ProgressTestNg, CapulseProgressCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of ring progress.
     */
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_CAPSULE);

    TestProperty testProperty;
    testProperty.strokeWidth = std::make_optional(STORKE_WIDTH);

    /**
     * @tc.steps: step2. create progress frameNode and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode success and progress properties equals expected value.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    ASSERT_NE(progressLayoutProperty, nullptr);

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
    ASSERT_NE(progressPattern, nullptr);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    ASSERT_NE(progressLayoutAlgorithm, nullptr);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(progressLayoutAlgorithm->GetType(), PROGRESS_TYPE_CAPSULE);
    EXPECT_EQ(progressLayoutAlgorithm->GetStrokeWidth(), STORKE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Height(), DEFALT_CAPSULE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), DEFALT_CAPSULE_WIDTH.ConvertToPx());

    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size->Height(), DEFALT_CAPSULE_WIDTH.ConvertToPx());
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);

    LayoutConstraintF contentConstraint2;
    contentConstraint2.maxSize.SetWidth(PROGRESS_COMPONENT_MAXSIZE_WIDTH);
    contentConstraint2.maxSize.SetHeight(PROGRESS_COMPONENT_MAXSIZE_HEIGHT);
    contentConstraint2.selfIdealSize.SetHeight(PROGRESS_COMPONENT_HEIGHT);
    size = progressLayoutAlgorithm->MeasureContent(contentConstraint2, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size->Height(), PROGRESS_COMPONENT_HEIGHT);
    EXPECT_EQ(size->Width(), DEFALT_CAPSULE_WIDTH.ConvertToPx());
}

/**
 * @tc.name: GetContentDrawFunction
 * @tc.desc: Test the funtion GetContentDrawFunction in ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, GetContentDrawFunction, TestSize.Level1)
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
         * @tc.steps: step2. create progress frameNode and check the progress properties with expected value .
         * @tc.expected: step2. get frameNode success and progress properties equals expected value.
         */
        RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
        CheckValue(frameNode, testProperty);
        RefPtr<ProgressPaintProperty> progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
        ASSERT_NE(progressPaintProperty, nullptr);

        /**
         * @tc.steps: step3. create GeometryNode and PaintWrapper, ProgressPaintMethod.
         */
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        geometryNode->SetContentSize(SizeF(PROGRESS_COMPONENT_MAXSIZE_WIDTH, PROGRESS_COMPONENT_MAXSIZE_HEIGHT));
        geometryNode->SetContentOffset(OffsetF(0, 0));
        RefPtr<PaintWrapper> paintWrapper =
            AceType::MakeRefPtr<PaintWrapper>(RenderContext::Create(), geometryNode, progressPaintProperty);
        auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
        auto progressPaintMethod = AceType::MakeRefPtr<ProgressPaintMethod>(
            progressType[i], LARG_STORKE_WIDTH.ConvertToPx(), progressModifier);
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
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AtLeast(1));
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
     * @tc.steps: step1. Create the frameNode.
     * @tc.expected: step1. Check the frameNode was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(5.0, 10.0, 10.0, 20.0, PROGRESS_TYPE_LINEAR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the progressPaintProperty.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateColor(TEST_COLOR);
    progressPaintProperty->UpdateBackgroundColor(TEST_COLOR);
    progressPaintProperty->UpdateBorderColor(TEST_COLOR);
    progressPaintProperty->UpdateMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    progressPaintProperty->UpdateValue(PROGRESS_MODIFIER_VALUE);
    progressPaintProperty->UpdateScaleCount(SCALE_COUNT);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, progressPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);

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
    ASSERT_NE(getModifier, nullptr);
    auto getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
    ASSERT_NE(getProgressModifier, nullptr);
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
     * @tc.steps: step1. Create the frameNode.
     * @tc.expected: step1. Check the frameNode was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(PROGRESS_MODLE_NG_MIN, PROGRESS_MODLE_NG_VALUE, PROGRESS_MODLE_NG_CACHEDVALUE,
        PROGRESS_MODLE_NG_MAX, PROGRESS_TYPE_LINEAR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create the progressPaintProperty.Call function .
     * @tc.expected: step2. Check the property after Clone and Reset.
     */
    RefPtr<ProgressPaintProperty> progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    progressPaintProperty->Clone();
    auto cloneMaxValue = progressPaintProperty->GetMaxValue();
    EXPECT_EQ(cloneMaxValue, PROGRESS_MODLE_NG_MAX);
    progressPaintProperty->Reset();
    auto resetMaxValue = progressPaintProperty->GetMaxValue();
    EXPECT_NE(resetMaxValue, PROGRESS_MODLE_NG_MAX);
}

/**
 * @tc.name: progressMaskPropertyTestNg001
 * @tc.desc: Test progress mask property
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, progressMaskPropertyTestNg001, TestSize.Level1)
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
}

/**
 * @tc.name: ProgressAccessibilityPropertyTestNg001
 * @tc.desc: Test the RangeInfo Property of progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressAccessibilityPropertyTestNg001, TestSize.Level1)
{
    TestProperty testProperty;
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_LINEAR);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(MAX_VALUE_OF_PROGRESS);
    progressPaintProperty->UpdateValue(VALUE_OF_PROGRESS);
    auto accessibilityProp = frameNode->GetAccessibilityProperty<ProgressAccessibilityProperty>();
    ASSERT_NE(accessibilityProp, nullptr);
    EXPECT_TRUE(accessibilityProp->HasRange());
    EXPECT_EQ(accessibilityProp->GetAccessibilityValue().min, 0);
    EXPECT_EQ(accessibilityProp->GetAccessibilityValue().max, MAX_VALUE_OF_PROGRESS);
    EXPECT_EQ(accessibilityProp->GetAccessibilityValue().current, VALUE_OF_PROGRESS);
}

/**
 * @tc.name: ProgressAccessibilityPropertyTestNg002
 * @tc.desc: Test the GetText Property of progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressAccessibilityPropertyTestNg002, TestSize.Level1)
{
    TestProperty testProperty;
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_LINEAR);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    auto progressPaintProperty = frameNode->GetPaintProperty<NG::ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateValue(VALUE_OF_PROGRESS);
    auto accessibilityProp = frameNode->GetAccessibilityProperty<ProgressAccessibilityProperty>();
    ASSERT_NE(accessibilityProp, nullptr);
    EXPECT_EQ(accessibilityProp->GetText(), std::to_string(VALUE_OF_PROGRESS));
}

/**
 * @tc.name: ProgressModelTest001
 * @tc.desc: Test set some value.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressModelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of Capsule progress.
     */
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_CAPSULE);
    TestProperty testProperty;
    testProperty.borderColor = std::make_optional(Color::BLUE);
    testProperty.borderWidth = std::make_optional(BORDER_WIDTH);
    testProperty.sweepEffect = std::make_optional(true);
    testProperty.fontColor = std::make_optional(Color::BLUE);
    testProperty.fontSize = std::make_optional(FONT_SIZE);
    testProperty.content = std::make_optional(FONT_CONTEXT);
    testProperty.fontWeight = std::make_optional(FONT_WEIGHT);
    testProperty.fontFamily = std::make_optional(FONT_FAMILY);
    testProperty.fontStyle = std::make_optional(Ace::FontStyle::ITALIC);
    testProperty.ringSweepEffect = std::make_optional(true);
    testProperty.linearSweepEffect = std::make_optional(true);
    testProperty.showText = std::make_optional(true);

    /**
     * @tc.steps: step2. create progress frameNode and check the progress properties with expected value .
     * @tc.expected: step2. get frameNode success and progress properties equals expected value.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
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
    TestProperty testProperty;
    testProperty.bgColor = std::make_optional(Color::BLUE);
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_CAPSULE);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    auto progressEvent = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(progressEvent, nullptr);
    progressEvent->SetEnabled(false);
    pattern->OnModifyDone();
    TouchEventInfo info("touch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    pattern->touchListener_->GetTouchEventCallback()(info);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(PROGRESS_COMPONENT_MAXSIZE_WIDTH, PROGRESS_COMPONENT_MAXSIZE_HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));
    frameNode->SetGeometryNode(geometryNode);
    RoundRect focusRect;
    pattern->GetInnerFocusPaintRect(focusRect);
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
        PROGRESS_COMPONENT_MAXSIZE_WIDTH * 0.5 + DEFALUT_SPACE.ConvertToPx());
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y,
        PROGRESS_COMPONENT_MAXSIZE_WIDTH * 0.5 + DEFALUT_SPACE.ConvertToPx());
    EXPECT_FALSE(progressEvent->IsEnabled());

    /**
     * @tc.steps: step2. Create linear progress and set remove touchEvent.
     * @tc.expected: step2. Check the touchEvent is removed.
     */
    testProperty.bgColor = std::make_optional(Color::BLUE);
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_LINEAR);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);
    pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    progressEvent = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(progressEvent, nullptr);
    auto touchCallback = [](TouchEventInfo& info) {};
    pattern->touchListener_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    pattern->OnModifyDone();
    ASSERT_EQ(pattern->touchListener_, nullptr);
}

/**
 * @tc.name: ProgressPattern002
 * @tc.desc: Test the TouchEvent of progress, TouchType is UP.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPattern002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.bgColor = std::make_optional(Color::BLUE);
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_CAPSULE);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    auto progressEvent = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(progressEvent, nullptr);
    pattern->OnModifyDone();
    TouchEventInfo info("touch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    pattern->touchListener_->GetTouchEventCallback()(info);
    EXPECT_TRUE(progressEvent->IsEnabled());
}

/**
 * @tc.name: ProgressPattern003
 * @tc.desc: Test the TouchEvent of progress, TouchType is CANCEL.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPattern003, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.bgColor = std::make_optional(Color::BLUE);
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_CAPSULE);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    auto progressEvent = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(progressEvent, nullptr);
    pattern->OnModifyDone();
    TouchEventInfo info("touch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::CANCEL);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    pattern->touchListener_->GetTouchEventCallback()(info);
    EXPECT_TRUE(progressEvent->IsEnabled());
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
    TestProperty testProperty;
    testProperty.paintShadow = std::make_optional(true);
    testProperty.progressStatus = std::make_optional(ProgressStatus::PROGRESSING);
    testProperty.gradient = std::make_optional(gradient);
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_RING);
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);

    auto pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ProgressPaintProperty> progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->ToJsonValue(json);
    progressPaintProperty->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    testProperty.progressStatus = std::make_optional(ProgressStatus::LOADING);
    frameNode = CreateProgressParagraph(testProperty);
    pattern = frameNode->GetPattern<ProgressPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: CapulseProgressMeasure001
 * @tc.desc: Test the measure of Capulse type progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, CapulseProgressMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode.
     * @tc.expected: step1. Check the frameNode was created successfully.
     */
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_CAPSULE);

    TestProperty testProperty;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);

    /**
     * @tc.steps: step2. Create the progressLayoutAlgorithm.
     * @tc.expected: step2. Check the progressLayoutAlgorithm created successfully.
     */
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    ASSERT_NE(progressLayoutProperty, nullptr);
    LayoutConstraintF contentConstraint;
    LayoutWrapper layoutWrapper(frameNode, nullptr, progressLayoutProperty);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    ASSERT_NE(progressLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. Call the function MeasureContent.
     * @tc.expected: step3. Check the result of MeasureContent.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    ASSERT_NE(textNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 50));
    RefPtr<LayoutWrapper> textWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textNode, geometryNode, textNode->GetLayoutProperty());
    ASSERT_NE(textWrapper, nullptr);
    layoutWrapper.AppendChild(textWrapper);
    contentConstraint.selfIdealSize.SetWidth(PROGRESS_COMPONENT_WIDTH);
    auto size = progressLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(size->Width(), PROGRESS_COMPONENT_WIDTH);
}

/**
 * @tc.name: CapulseProgressMeasure002
 * @tc.desc: Test the measure of Capulse type progress.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, CapulseProgressMeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode.
     * @tc.expected: step1. Check the frameNode was created successfully.
     */
    creatProperty.progressType = std::make_optional(PROGRESS_TYPE_CAPSULE);

    TestProperty testProperty;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
    RefPtr<FrameNode> frameNode = CreateProgressParagraph(testProperty);
    CheckValue(frameNode, testProperty);

    /**
     * @tc.steps: step2. Create the progressLayoutAlgorithm.
     * @tc.expected: step2. Check the progressLayoutAlgorithm created successfully.
     */
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ProgressLayoutProperty> progressLayoutProperty =
        AceType::DynamicCast<ProgressLayoutProperty>(layoutProperty);
    ASSERT_NE(progressLayoutProperty, nullptr);
    LayoutConstraintF contentConstraint;
    LayoutWrapper layoutWrapper(frameNode, nullptr, progressLayoutProperty);
    auto progressLayoutAlgorithm = AceType::MakeRefPtr<ProgressLayoutAlgorithm>();
    ASSERT_NE(progressLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. Call the function MeasureContent.
     * @tc.expected: step3. Check the result of MeasureContent.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    ASSERT_NE(textNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(500, 100));
    RefPtr<LayoutWrapper> textWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textNode, geometryNode, textNode->GetLayoutProperty());
    ASSERT_NE(textWrapper, nullptr);
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
     * @tc.steps: step1. Create the frameNode.
     * @tc.expected: step1. Check the frameNode was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(5.0, 0.0, 10.0, 20.0, PROGRESS_TYPE_CAPSULE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the progressPaintProperty.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateMaxValue(100.0);
    progressPaintProperty->UpdateValue(0.0);
    progressPaintProperty->UpdateBorderWidth(0.0_vp);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, progressPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: step3. Create ProgressPaintMethod. Call the function UpdateContentModifier and GetContentModifier.
     * @tc.expected: step3. Check the properties update before.
     */
    auto progressModifier = AceType::MakeRefPtr<ProgressModifier>();
    ProgressPaintMethod progressPaintMethod(PROGRESS_TYPE_CAPSULE, PROGRESS_STROKE_WIDTH, progressModifier);
    progressPaintMethod.progressType_ = PROGRESS_TYPE_CAPSULE;
    progressPaintMethod.UpdateContentModifier(paintWrapper);

    progressPaintProperty->UpdateValue(10.0);
    progressPaintProperty->UpdateBorderWidth(300.0_vp);
    progressPaintProperty->UpdateEnableScanEffect(true);
    progressPaintProperty->UpdateBorderWidth(2.0_vp);
    SizeF progressContentSize(300.0f, 50.0f);
    progressModifier->SetContentSize(progressContentSize);
    progressPaintMethod.UpdateContentModifier(paintWrapper);

    SizeF progressContentSize1(50.0f, 300.0f);
    progressModifier->SetContentSize(progressContentSize1);
    progressPaintMethod.UpdateContentModifier(paintWrapper);

    auto getModifier = progressPaintMethod.GetContentModifier(paintWrapper);
    ASSERT_NE(getModifier, nullptr);
    auto getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
    ASSERT_NE(getProgressModifier, nullptr);
}

/**
 * @tc.name: ProgressPaintMethod003
 * @tc.desc: Test ProgressPaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ProgressTestNg, ProgressPaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the frameNode.
     * @tc.expected: step1. Check the frameNode was created successfully.
     */
    ProgressModelNG progressModelNG;
    progressModelNG.Create(5.0, 10.0, 10.0, 20.0, PROGRESS_TYPE_RING);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create the GeometryNode and PaintWrapper.Set the progressPaintProperty.
     * @tc.expected: step2. Check the GeometryNode and PaintWrapper were created successfully.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto progressPaintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(progressPaintProperty, nullptr);
    progressPaintProperty->UpdateItalicFontStyle(Ace::FontStyle::ITALIC);
    progressPaintProperty->UpdateMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    progressPaintProperty->UpdateValue(PROGRESS_MODIFIER_VALUE);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, progressPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);

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
    ASSERT_NE(getModifier, nullptr);
    auto getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
    ASSERT_NE(getProgressModifier, nullptr);
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

    progressPaintProperty->UpdateGradientColor(gradient);
    progressPaintProperty->UpdateItalicFontStyle(Ace::FontStyle::NORMAL);
    progressPaintProperty->UpdateMaxValue(PROGRESS_MODIFIER_MAX_VALUE);
    progressPaintProperty->UpdateValue(PROGRESS_MODIFIER_VALUE);
    progressPaintMethod.progressType_ = PROGRESS_TYPE_RING;
    progressPaintMethod.UpdateContentModifier(paintWrapper);
    getModifier = progressPaintMethod.GetContentModifier(paintWrapper);
    ASSERT_NE(getModifier, nullptr);
    getProgressModifier = AceType::DynamicCast<ProgressModifier>(getModifier);
    ASSERT_NE(getProgressModifier, nullptr);
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
     * @tc.expected: step3. The sweepingDate_ is not zero.
     */
    value = 70.0f;
    progressModifier->sweepingDate_->Set(0.0f);
    progressModifier->isSweeping_ = true;
    progressModifier->sweepingDateBackup_ = 10000.0f;
    progressModifier->SetValue(value);
    progressModifier->onDraw(context);
    EXPECT_EQ(progressModifier->progressType_->Get(), static_cast<int32_t>(PROGRESS_TYPE_RING));
    EXPECT_NE(progressModifier->sweepingDate_->Get(), 0.0f);

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
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));

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
     * @tc.expected: step4. Start sweeping.
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
    EXPECT_NE(progressModifier->sweepingDate_->Get(), 0);

    /**
     * @tc.steps: step4. Set invisible.
     * @tc.expected: step4. The sweeping animation is stopped.
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
     * @tc.steps: step5. Set value while invisible.
     * @tc.expected: step5. The value is set but the sweepingDate is not set.
     */
    value = 10.0f;
    progressModifier->SetValue(value);
    EXPECT_EQ(progressModifier->value_->Get(), 10.0f);
    EXPECT_EQ(progressModifier->sweepingDate_->Get(), 0.0f);
}
} // namespace OHOS::Ace::NG
