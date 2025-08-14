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
#include "gtest/internal/gtest-internal.h"

#define private public
#include "base/geometry/ng/offset_t.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/data_panel/data_panel_modifier.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/pipeline/base/constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::vector<double> VALUES = { 1.0, 2.0, 3.0, 4.0 };
constexpr double MAX = 200.0;
constexpr double MAX_DEFAULT = 100.0;
constexpr double MAX_ZERO_VALUE = 0.0;
constexpr double MAX_INFINITE_VALUE = 1000000.0;
const std::vector<double> SINGLE_VALUES = { 1.0 };
const std::vector<double> FULL_VALUES = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
const std::vector<double> LONG_VALUES = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
constexpr size_t TYPE_CYCLE = 0;
constexpr size_t TYPE_LINE = 1;
constexpr bool CLOSE_EFFECT = true;
constexpr bool CLOSE_EFFECT_OFF = false;
constexpr Dimension WIDTH = 50.0_vp;
constexpr Dimension HEIGHT = 50.0_vp;
constexpr float MAX_WIDTH = 400.0f;
constexpr float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float MAX_PERCENT_WIDTH = 200.0f;
constexpr float MAX_PERCENT_HEIGHT = 200.0f;
const SizeF MAX_PERCENT_SIZE(MAX_PERCENT_WIDTH, MAX_PERCENT_HEIGHT);
constexpr float MAX_INFINITE = 1000000.0f;
const SizeF MAX_INFINITE_SIZE(MAX_INFINITE, MAX_INFINITE);
constexpr float NEGATIVE_NUMBER = -100;
constexpr bool SKIP_MEASURE = true;
constexpr bool NO_SKIP_MEASURE = false;
const Color TRUE_COLOR = Color(0x00000000);
const Color ERROR_COLOR = Color();
constexpr double DEFAULT_SHADOW_VALUE = 5.0;

const Color START_COLOR = Color::BLUE;
const Color END_COLOR = Color::GREEN;
const OffsetF OFFSET = { 1.0f, 1.0f };
constexpr float TOTAL_HEIGHT = 10.0f;
constexpr float TOTAL_WIDTH = 100.0f;
constexpr float XSPACE = 10.0f;
constexpr float SEGMENTWIDTH = 20.0f;
constexpr float SPACEWIDTH = 5.0f;
constexpr float ROOT_WIDTH = 1000.0f;
constexpr float ROOT_HEIGHT = 1000.0f;
constexpr Dimension STROKE_WIDTH = 10.0_vp;
constexpr float DRAW_ANGLE = 355.0f;
constexpr float PERCENT_HALF = 0.5f;
} // namespace

class DataPanelTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void GradientColorSet(std::vector<Gradient>& valueColors, const int& length);
};

class DataPanelTheme : public Theme {
    DECLARE_ACE_TYPE(DataPanelTheme, Theme)
public:
    DataPanelTheme()
    {
        color.clear();
        for (size_t i = 0; i < MAX_COUNT; i++) {
            color.emplace_back(std::make_pair(Color::BLUE, Color::BLUE));
        }
    }
    ~DataPanelTheme() override = default;

    Dimension GetThickness() const
    {
        return 20.0_vp;
    }

    std::vector<std::pair<Color, Color>> GetColorsArray() const
    {
        return color;
    }

private:
    std::vector<std::pair<Color, Color>> color;
};

void DataPanelTestNg::SetUpTestCase()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataPanelTheme));
}

void DataPanelTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DataPanelTestNg::GradientColorSet(std::vector<Gradient>& valueColors, const int& length)
{
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor::WHITE);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor::BLACK);
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    for (int i = 0; i < length; i++) {
        valueColors.push_back(gradient);
    }
}

/**
 * @tc.name: DataPanelPatternTest001
 * @tc.desc: Test DataPanel Create
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPE_CYCLE);
}

/**
 * @tc.name: DataPanelPatternTest002
 * @tc.desc: Test DataPanel SetEffect
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and set effct.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_CYCLE);
    dataPanel.SetEffect(CLOSE_EFFECT);

    /**
     * @tc.steps: step2. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetEffectValue(), !CLOSE_EFFECT);
}

/**
 * @tc.name: DataPanelMeasureTest003
 * @tc.desc: Test DataPanel Measure.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelMeasureTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datapnel and get framenode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_CYCLE);
    dataPanel.SetEffect(!CLOSE_EFFECT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode and set dataPanelLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto dataPanelPattern = frameNode->GetPattern<DataPanelPattern>();
    EXPECT_NE(dataPanelPattern, nullptr);
    auto dataPanelLayoutAlgorithm = dataPanelPattern->CreateLayoutAlgorithm();
    EXPECT_NE(dataPanelLayoutAlgorithm, nullptr);
    dataPanelLayoutAlgorithm->Reset();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(dataPanelLayoutAlgorithm));

    /**
     * @tc.steps: step3. compare dataPanelSize with expected value.
     * @tc.expected: step3. dataPanelSize is the same with expected value.
     */
    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }})
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    layoutConstraint.percentReference = MAX_SIZE;
    auto dataPanelDefaultSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value();
    EXPECT_EQ(dataPanelDefaultSize, MAX_SIZE);

    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).width(50).height(50)
     */
    LayoutConstraintF layoutConstraintVaildSize;
    layoutConstraintVaildSize.maxSize = MAX_SIZE;
    layoutConstraint.percentReference = MAX_SIZE;
    layoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    auto dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintVaildSize, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));

    LayoutConstraintF layoutConstraintHeight;
    layoutConstraintHeight.maxSize = MAX_SIZE;
    layoutConstraintHeight.percentReference = MAX_SIZE;
    layoutConstraintHeight.selfIdealSize.SetHeight(HEIGHT.ConvertToPx());
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeight, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_WIDTH, HEIGHT.ConvertToPx()));

    LayoutConstraintF layoutConstraintWidth;
    layoutConstraintWidth.maxSize = MAX_SIZE;
    layoutConstraintWidth.percentReference = MAX_SIZE;
    layoutConstraintWidth.selfIdealSize.SetWidth(WIDTH.ConvertToPx());
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintWidth, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(WIDTH.ConvertToPx(), MAX_HEIGHT));

    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).height(-100)
     */
    LayoutConstraintF layoutConstraintHeightUnvalid;
    layoutConstraintHeightUnvalid.percentReference = MAX_SIZE;
    layoutConstraintHeightUnvalid.selfIdealSize.SetHeight(NEGATIVE_NUMBER);
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeightUnvalid, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).width(-100)
     */
    LayoutConstraintF layoutConstraintWidthUnvalid;
    layoutConstraintWidthUnvalid.percentReference = MAX_SIZE;
    layoutConstraintWidthUnvalid.selfIdealSize.SetWidth(NEGATIVE_NUMBER);
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeightUnvalid, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_WIDTH, MAX_HEIGHT));
}

/**
 * @tc.name: DataPanelMeasureTest004
 * @tc.desc: Test DataPanel Measure by percentReference instead of maxSize.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelMeasureTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datapanel and get framenode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_CYCLE);
    dataPanel.SetEffect(!CLOSE_EFFECT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode and set dataPanelLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto dataPanelPattern = frameNode->GetPattern<DataPanelPattern>();
    EXPECT_NE(dataPanelPattern, nullptr);
    auto dataPanelLayoutAlgorithm = dataPanelPattern->CreateLayoutAlgorithm();
    EXPECT_NE(dataPanelLayoutAlgorithm, nullptr);
    dataPanelLayoutAlgorithm->Reset();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(dataPanelLayoutAlgorithm));

    /**
     * @tc.steps: step3. compare dataPanelSize with expected value.
     * @tc.expected: step3. dataPanelSize is the same with expected value.
     */
    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }})
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    layoutConstraint.percentReference = MAX_PERCENT_SIZE;
    auto dataPanelDefaultSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value();
    EXPECT_EQ(dataPanelDefaultSize, MAX_PERCENT_SIZE);

    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).width(50).height(50)
     */
    LayoutConstraintF layoutConstraintVaildSize;
    layoutConstraintVaildSize.maxSize = MAX_SIZE;
    layoutConstraint.percentReference = MAX_PERCENT_SIZE;
    layoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    auto dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintVaildSize, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));

    /**
     * @tc.steps: step4. compare dataPanelSize with expected value.
     * @tc.expected: step4. dataPanelSize is the same with expected value.
     */
    LayoutConstraintF layoutConstraintHeight;
    layoutConstraintHeight.maxSize = MAX_SIZE;
    layoutConstraintHeight.percentReference = MAX_PERCENT_SIZE;
    layoutConstraintHeight.selfIdealSize.SetHeight(HEIGHT.ConvertToPx());
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeight, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_PERCENT_WIDTH, HEIGHT.ConvertToPx()));

    /**
     * @tc.steps: step5. compare dataPanelSize with expected value.
     * @tc.expected: step5. dataPanelSize is the same with expected value.
     */
    LayoutConstraintF layoutConstraintWidth;
    layoutConstraintWidth.maxSize = MAX_SIZE;
    layoutConstraintWidth.percentReference = MAX_PERCENT_SIZE;
    layoutConstraintWidth.selfIdealSize.SetWidth(WIDTH.ConvertToPx());
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintWidth, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(WIDTH.ConvertToPx(), MAX_PERCENT_HEIGHT));

    /**
     * @tc.steps: step6. compare dataPanelSize with expected value by infinite.
     * @tc.expected: step6. dataPanelSize is the same with expected value as root width and height.
     */
    MockPipelineContext::GetCurrent()->SetRootSize(ROOT_WIDTH, ROOT_HEIGHT);
    LayoutConstraintF layoutConstraintInfinite;
    layoutConstraintInfinite.percentReference = MAX_INFINITE_SIZE;
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintInfinite, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(ROOT_WIDTH, ROOT_HEIGHT));

    /**
     * @tc.steps: step7. compare dataPanelSize with expected value by infinite width.
     * @tc.expected: step7. dataPanelSize is the same with expected value as min width and height.
     */
    LayoutConstraintF layoutConstraintWidthInfinite;
    layoutConstraintWidthInfinite.percentReference = SizeF(MAX_INFINITE, MAX_HEIGHT);
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintWidthInfinite, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_HEIGHT, MAX_HEIGHT));
}

/**
 * @tc.name: DataPanelPatternTest004
 * @tc.desc: Test DataPanel isAtomicNode
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPatternTest004, TestSize.Level0)
{
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_CYCLE);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    bool isAtomicNode = frameNode->IsAtomicNode();
    EXPECT_TRUE(isAtomicNode);
}

/**
 * @tc.name: DataPanelTest005
 * @tc.desc: Test the line datapanel .
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPatternTest005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapanel model and initialize dataPanelType to LINE.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPE_LINE);
}

/**
 * @tc.name: DataPanelTest006
 * @tc.desc: Test the line datapanel .
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPatternTest006, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapanel model and initialize dataPanelType to LINE.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPE_LINE);
}

/**
 * @tc.name: DataPanelTest007
 * @tc.desc: Test the line datapanel .
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPatternTest007, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get framenode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_CYCLE);
    dataPanel.SetEffect(!CLOSE_EFFECT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode and set dataPanelLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto dataPanelPattern = frameNode->GetPattern<DataPanelPattern>();
    EXPECT_NE(dataPanelPattern, nullptr);
    auto dataPanelLayoutAlgorithm = dataPanelPattern->CreateLayoutAlgorithm();
    EXPECT_NE(dataPanelLayoutAlgorithm, nullptr);
    dataPanelLayoutAlgorithm->Reset();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(dataPanelLayoutAlgorithm));

    /**
     * @tc.steps: step3. compare dataPanelSize with expected value.
     * @tc.expected: step3. dataPanelSize is the same with expected value.
     */
    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }})
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    layoutConstraint.percentReference = MAX_SIZE;
    auto dataPanelDefaultSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value();
    EXPECT_EQ(dataPanelDefaultSize, MAX_SIZE);
}

/**
 * @tc.name: DataPanelTest008
 * @tc.desc: Test dataPanel pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintPropertyTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dataPanel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create dataPanel frameNode, get dataPanelPattern and dataPanelWrapper.
     * @tc.expected: step2. get dataPanelPattern success.
     */
    RefPtr<DataPanelPattern> dataPanelPattern = AceType::DynamicCast<DataPanelPattern>(frameNode->GetPattern());
    EXPECT_NE(dataPanelPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. call dataPanelPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    RefPtr<DataPanelLayoutAlgorithm> dataPanelLayoutAlgorithm = AceType::MakeRefPtr<DataPanelLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(dataPanelLayoutAlgorithm, SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     * @tc.steps: step4. call dataPanelPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step4. OnDirtyLayoutWrapperSwap success and result correct.
     */

    /**
     *     case 1: LayoutWrapperNode::SkipMeasureContent = true , skipMeasure = true;
     */
    bool first_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(first_case);

    /**
     *     case 2: LayoutWrapperNode::SkipMeasureContent = true , skipMeasure = true;
     */
    bool second_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_FALSE(second_case);

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(dataPanelLayoutAlgorithm, NO_SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     *     case 3: LayoutWrapperNode::SkipMeasureContent = false , skipMeasure = true;
     */
    bool third_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(third_case);

    /**
     *     case 4: LayoutWrapperNode::SkipMeasureContent = false , skipMeasure = false;
     */
    bool forth_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(forth_case);
}

/**
 * @tc.name: DataPanelTest009
 * @tc.desc: Test DataPanel PaintMethod SetTrackBackground
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintPropertyTest006, TestSize.Level0)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_CYCLE);
    dataPanelModelNG.SetTrackBackground(TRUE_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetTrackBackgroundValue(), TRUE_COLOR);

    DataPanelModelNG dataPanelModelNG2;
    dataPanelModelNG2.Create(VALUES, MAX, TYPE_CYCLE);
    dataPanelModelNG2.SetTrackBackground(ERROR_COLOR);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto dataPanelPaintProperty2 = frameNode2->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty2, nullptr);
    EXPECT_EQ(dataPanelPaintProperty2->GetTrackBackgroundValue(), ERROR_COLOR);
}

/**
 * @tc.name: DataPanelTest010
 * @tc.desc: Test DataPanel PaintMethod SetStrokeWidth
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintPropertyTest007, TestSize.Level0)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_CYCLE);
    Dimension strokeWidth = 50.0_vp;
    dataPanelModelNG.SetStrokeWidth(strokeWidth);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetStrokeWidthValue(), strokeWidth);

    // ErrorValue1
    DataPanelModelNG dataPanelModelNG2;
    dataPanelModelNG2.Create(VALUES, MAX, TYPE_CYCLE);
    Dimension strokeWidth2 = 0.0_vp;
    dataPanelModelNG2.SetStrokeWidth(strokeWidth2);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto dataPanelPaintProperty2 = frameNode2->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty2, nullptr);
    EXPECT_EQ(dataPanelPaintProperty2->GetStrokeWidthValue(), strokeWidth2);

    // ErrorValue2
    DataPanelModelNG dataPanelModelNG3;
    dataPanelModelNG3.Create(VALUES, MAX, TYPE_CYCLE);
    Dimension strokeWidth3 = 500.0_vp;
    dataPanelModelNG3.SetStrokeWidth(strokeWidth3);
    auto frameNode3 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode3, nullptr);
    auto dataPanelPaintProperty3 = frameNode3->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty3, nullptr);
    EXPECT_EQ(dataPanelPaintProperty3->GetStrokeWidthValue(), strokeWidth3);

    // ErrorValue3
    DataPanelModelNG dataPanelModelNG4;
    dataPanelModelNG4.Create(VALUES, MAX, TYPE_CYCLE);
    Dimension strokeWidth4 = -50.0_vp;
    dataPanelModelNG4.SetStrokeWidth(strokeWidth4);
    auto frameNode4 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode4, nullptr);
    auto dataPanelPaintProperty4 = frameNode4->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty4, nullptr);
    EXPECT_EQ(dataPanelPaintProperty4->GetStrokeWidthValue(), strokeWidth4);
}

/**
 * @tc.name: DataPanelTest011
 * @tc.desc: Test DataPanel PaintMethod SetValueColors Normal
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintPropertyTest008, TestSize.Level0)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_CYCLE);
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor::WHITE);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor::BLACK);
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    std::vector<Gradient> valueColors;
    // test Solid color when the valueColors >0 and valueColors <=9
    int length = 2;
    for (int i = 0; i < length; i++) {
        valueColors.push_back(gradient);
    }
    dataPanelModelNG.SetValueColors(valueColors);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetValueColorsValue(), valueColors);
}

/**
 * @tc.name: DataPanelTest012
 * @tc.desc: Test DataPanel PaintMethod SetValueColors Normal2
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintPropertyTest009, TestSize.Level0)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_CYCLE);
    int length = 2;
    std::vector<Gradient> valueColors;
    GradientColorSet(valueColors, length);
    // test Gradient  color when the valueColors >0 and valueColors <=9
    dataPanelModelNG.SetValueColors(valueColors);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetValueColorsValue(), valueColors);

    DataPanelModelNG dataPanelModelNG2;
    dataPanelModelNG2.Create(VALUES, MAX, TYPE_CYCLE);
    std::vector<Gradient> valueColors2;
    GradientColorSet(valueColors2, 0);
    // test Gradient  color when the valueColors = 0
    dataPanelModelNG2.SetValueColors(valueColors2);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto dataPanelPaintProperty2 = frameNode2->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty2, nullptr);
    EXPECT_EQ(dataPanelPaintProperty2->GetValueColorsValue(), valueColors2);

    DataPanelModelNG dataPanelModelNG3;
    dataPanelModelNG3.Create(VALUES, MAX, TYPE_CYCLE);
    int length2 = 11;
    std::vector<Gradient> valueColors3;
    GradientColorSet(valueColors3, length2);
    // test Gradient  color when the valueColors > 9
    dataPanelModelNG3.SetValueColors(valueColors3);
    auto frameNode3 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode3, nullptr);
    auto dataPanelPaintProperty3 = frameNode3->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty3, nullptr);
    EXPECT_EQ(dataPanelPaintProperty3->GetValueColorsValue(), valueColors3);
}

/**
 * @tc.name: DataPanelTest013
 * @tc.desc: Test DataPanel PaintMethod SetShadowOption
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintPropertyTest010, TestSize.Level1)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_CYCLE);
    int length = 3;
    std::vector<Gradient> valueColors;
    GradientColorSet(valueColors, length);
    DataPanelShadow shadowOption { true, DEFAULT_SHADOW_VALUE, DEFAULT_SHADOW_VALUE, DEFAULT_SHADOW_VALUE,
        valueColors };
    dataPanelModelNG.SetShadowOption(shadowOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetShadowOptionValue(), shadowOption);

    DataPanelModelNG dataPanelModelNG2;
    dataPanelModelNG2.Create(VALUES, MAX, TYPE_CYCLE);
    std::vector<Gradient> valueColors2;
    GradientColorSet(valueColors2, length);
    DataPanelShadow shadowOption2 { true, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE,
        valueColors2 };
    dataPanelModelNG2.SetShadowOption(shadowOption2);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto dataPanelPaintProperty2 = frameNode2->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty2, nullptr);
    EXPECT_EQ(dataPanelPaintProperty2->GetShadowOptionValue(), shadowOption2);

    DataPanelModelNG dataPanelModelNG3;
    dataPanelModelNG3.Create(VALUES, MAX, TYPE_CYCLE);
    int length2 = 12;
    std::vector<Gradient> valueColors3;
    GradientColorSet(valueColors3, length2);
    DataPanelShadow shadowOption3 { true, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE,
        valueColors3 };
    dataPanelModelNG3.SetShadowOption(shadowOption3);
    auto frameNode3 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode3, nullptr);
    auto dataPanelPaintProperty3 = frameNode3->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty3, nullptr);
    EXPECT_EQ(dataPanelPaintProperty3->GetShadowOptionValue(), shadowOption3);

    DataPanelModelNG dataPanelModelNG4;
    dataPanelModelNG4.Create(VALUES, MAX, TYPE_CYCLE);
    int length3 = 8;
    std::vector<Gradient> valueColors4;
    GradientColorSet(valueColors4, length3);
    DataPanelShadow shadowOption4 { true, 0.0, 0.0, 0.0, valueColors4 };
    dataPanelModelNG4.SetShadowOption(shadowOption4);
    auto frameNode4 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode4, nullptr);
    auto dataPanelPaintProperty4 = frameNode4->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty4, nullptr);
    EXPECT_EQ(dataPanelPaintProperty4->GetShadowOptionValue(), shadowOption4);
}

/**
 * @tc.name: DataPanelPaintProgressTest001
 * @tc.desc: Test DataPanel PaintMethod PaintProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintProgressTest001, TestSize.Level0)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataTheme));

    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    ArcData arcData;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));

    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetColor(START_COLOR);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetColor(END_COLOR);
    gradientColorEnd.SetDimension(Dimension(1.0));
    arcData.progressColors = gradient;
    RSPath path;
    RSPath endPath;

    dataPanelModifier.PaintProgress(rsCanvas, arcData, path, endPath, true);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));

    dataPanelModifier.PaintProgress(rsCanvas, arcData, path, endPath, false);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
}

/**
 * @tc.name: DataPanelPaintBackgroundTest001
 * @tc.desc: Test DataPanel PaintMethod PaintBackground
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintBackgroundTest001, TestSize.Level0)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataTheme));

    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AtLeast(1));
    dataPanelModifier.PaintBackground(rsCanvas, OFFSET, TOTAL_WIDTH, TOTAL_HEIGHT, SEGMENTWIDTH);
    dataPanelModifier.PaintBackground(rsCanvas, OFFSET, TOTAL_WIDTH, TOTAL_HEIGHT * 4, SEGMENTWIDTH);
}

/**
 * @tc.name: DataPanelPaintSpaceTest001
 * @tc.desc: Test DataPanel PaintMethod PaintSpace
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintSpaceTest001, TestSize.Level0)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataTheme));

    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).WillOnce(Return());
    EXPECT_CALL(rsCanvas, Scale(_, _)).WillOnce(Return());

    LinearData linearData;
    dataPanelModifier.PaintSpace(rsCanvas, linearData, SPACEWIDTH);
    
    /**
     * @tc.case: layout direction rtl
     */
    DataPanelModifier dataPanelModifierRtl(nullptr);
    dataPanelModifierRtl.SetIsRtl(true);
    dataPanelModifierRtl.PaintSpace(rsCanvas, linearData, SPACEWIDTH);
}

/**
 * @tc.name: DataPanelPaintColorSegmentTest001
 * @tc.desc: Test DataPanel PaintMethod PaintColorSegment
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintColorSegmentTest001, TestSize.Level0)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataTheme));

    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).WillOnce(Return());
    EXPECT_CALL(rsCanvas, Scale(_, _)).WillOnce(Return());
    LinearData linerData;
    linerData.offset = OFFSET;
    linerData.segmentWidth = SEGMENTWIDTH;
    linerData.xSegment = XSPACE;
    linerData.height = TOTAL_HEIGHT;
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetColor(START_COLOR);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetColor(END_COLOR);
    gradientColorEnd.SetDimension(Dimension(1.0));
    linerData.segmentColor = gradient;
    dataPanelModifier.PaintColorSegment(rsCanvas, linerData);
    
    /**
     * @tc.case: layout direction rtl
     */
    DataPanelModifier dataPanelModifierRtl(nullptr);
    dataPanelModifierRtl.SetIsRtl(true);
    dataPanelModifierRtl.PaintColorSegment(rsCanvas, linerData);
}

/**
 * @tc.name: DataPanelPaintTrackBackgroundTest001
 * @tc.desc: Test DataPanel PaintMethod PaintTrackBackground
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintTrackBackgroundTest001, TestSize.Level0)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataTheme));

    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    ArcData arcData;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    dataPanelModifier.PaintTrackBackground(rsCanvas, arcData, START_COLOR);
}

/**
 * @tc.name: DataPanelPaintCircleTest001
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintCircleTest001, TestSize.Level0)
{
    /**
     * case 1:defaultThickness >= radius
     * radius = -10.0f
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DataPanelTheme>()));

    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, -10.0f, -10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    dataPanelModifier.PaintCircle(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintCircleTest002
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintCircleTest002, TestSize.Level0)
{
    /**
     * case 2: totalvalue = 20
     *  values = { 10.0f, 10.0f } totalvalue = 20
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(100.0f);
    std::vector<double> VALUES = { 10.0f, 10.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintCircle(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintCircleTest003
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintCircleTest003, TestSize.Level1)
{
    /**
     * case 3:maxValue > 0 and one of value nearequael 0
     * max = 100.0f Values = { 0.001f, 20.0f };
     * isShadowVisible = true
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    dataPanelModifier.SetMax(100.0f);
    std::vector<double> VALUES = { 0.001f, 20.0f };
    dataPanelModifier.SetValues(VALUES);
    std::vector<Gradient> valueColors;
    // test Solid color when the valueColors >0 and valueColors <=9
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor::WHITE);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor::BLACK);
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    int length = 2;
    for (int i = 0; i < length; i++) {
        valueColors.push_back(gradient);
    }
    dataPanelModifier.SetShadowColors(valueColors, length);
    /**
     * @tc.cases: case. cover branch isShadowVisible is true.
     */
    dataPanelModifier.SetShadowVisible(true);
    /**
     * case1: effect = true.
     */
    dataPanelModifier.SetEffect(true);
    dataPanelModifier.PaintCircle(context, OFFSET);
    /**
     * case2: effect = false.
     */
    dataPanelModifier.SetEffect(false);
    dataPanelModifier.PaintCircle(context, OFFSET);
    /**
     * case3: isHasShadowValue = true.
     */
    dataPanelModifier.SetIsHasShadowValue(true);
    dataPanelModifier.PaintCircle(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintCircleTest004
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintCircleTest004, TestSize.Level0)
{
    /**
     * case 1: maxValue = 100, totalValue = 110
     *  values = { 100.0f, 10.0f } totalValue = 110
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    
    std::vector<Gradient> valueColors;
    // test Solid color when the valueColors >0 and valueColors <=9
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor::WHITE);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor::BLACK);
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    int length = 2;
    for (int i = 0; i < length; i++) {
        valueColors.push_back(gradient);
    }
    dataPanelModifier.SetShadowColors(valueColors, length);
    dataPanelModifier.SetShadowVisible(true);
    dataPanelModifier.SetEffect(true);
    dataPanelModifier.SetStrokeWidth(STROKE_WIDTH.ConvertToPx());
    dataPanelModifier.SetMax(100.0f);
    std::vector<double> VALUES = { 100.0f, 10.0f };
    dataPanelModifier.SetValues(VALUES);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    dataPanelModifier.PaintCircle(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintCircleTest005
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintCircleTest005, TestSize.Level0)
{
    /**
     * case 1: value1 nearZero, value2 nearMax
     *  values = { 0.0001f, 99.9f }
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    
    std::vector<Gradient> valueColors;
    // test Solid color when the valueColors >0 and valueColors <=9
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor::WHITE);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor::BLACK);
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    int length = 2;
    for (int i = 0; i < length; i++) {
        valueColors.push_back(gradient);
    }
    dataPanelModifier.SetShadowColors(valueColors, length);
    dataPanelModifier.SetShadowVisible(true);
    dataPanelModifier.SetEffect(true);
    dataPanelModifier.SetStrokeWidth(STROKE_WIDTH.ConvertToPx());
    dataPanelModifier.SetMax(100.0f);
    std::vector<double> VALUES = { 0.0001f, 99.9f };
    dataPanelModifier.SetValues(VALUES);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    dataPanelModifier.PaintCircle(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintLinearProgressTest001
 * @tc.desc: Test DataPanel PaintMethod PaintLineProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintLinearProgressTest001, TestSize.Level0)
{
    /**
     * case 1:sum of value = max ,max > 0
     * values ={10.0f,10.0f} max = 20.0f
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AtLeast(1));
    dataPanelModifier.SetMax(20.0f);
    std::vector<double> VALUES = { 10.0f, 10.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintLinearProgress(context, OFFSET);

    /**
     * @tc.cases: case. cover branch isShadowVisible is true.
     */
    dataPanelModifier.SetShadowVisible(true);
    /**
     * case1: effect = true.
     */
    dataPanelModifier.SetEffect(true);
    dataPanelModifier.PaintLinearProgress(context, OFFSET);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    /**
     * case2: effect = false.
     */
    dataPanelModifier.SetEffect(false);
    dataPanelModifier.PaintLinearProgress(context, OFFSET);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    /**
     * case3: isHasShadowValue = true.
     */
    dataPanelModifier.SetIsHasShadowValue(true);
    dataPanelModifier.PaintLinearProgress(context, OFFSET);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
}

/**
 * @tc.name: DataPanelPaintLinearProgressTest002
 * @tc.desc: Test DataPanel PaintMethod PaintLineProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintLinearProgressTest002, TestSize.Level0)
{
    /**
     * case 2:sum of value != max, max < 0
     * values ={-5.0f, 0.0f} max = -20.0f
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AtLeast(1));
    dataPanelModifier.SetMax(-20.0f);
    std::vector<double> VALUES = { -5.0f, 0.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintLinearProgress(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintLinearProgressTest003
 * @tc.desc: Test DataPanel PaintMethod PaintLineProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintLinearProgressTest003, TestSize.Level0)
{
    /**
     * case 3:one of value nearequael 0 and > 0
     * values ={ 0.0001f, 5.0f} max = 20.0f
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    dataPanelModifier.SetMax(20.0f);
    std::vector<double> VALUES = { 0.0001f, 5.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintLinearProgress(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintColorSegmentFilterMaskTest001
 * @tc.desc: Test DataPanel PaintMethod PaintColorSegmentFilterMask
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintColorSegmentFilterMaskTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Translate(_, _)).WillOnce(Return());
    EXPECT_CALL(rsCanvas, Scale(_, _)).WillOnce(Return());
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    dataPanelModifier.SetMax(20.0f);
    std::vector<double> VALUES = { 0.0001f, 5.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintLinearProgress(context, OFFSET);
    LinearData segmentLinearData;

    /**
     * @tc.cases: case. cover isEndData is true.
     */
    segmentLinearData.isEndData = true;
    segmentLinearData.offset = OFFSET;
    segmentLinearData.xSegment = 5.0;
    segmentLinearData.segmentWidth = 5.0;
    segmentLinearData.height = 5.0;
    dataPanelModifier.PaintColorSegmentFilterMask(rsCanvas, segmentLinearData);

    /**
     * @tc.cases: case. cover branch segmentLinearData isFirstData is true.
     */
    segmentLinearData.isFirstData = true;
    dataPanelModifier.PaintColorSegmentFilterMask(rsCanvas, segmentLinearData);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));

    /**
     * @tc.cases: case. cover branch segmentLinearData isEndData is true.
     */
    segmentLinearData.isFirstData = false;
    segmentLinearData.isEndData = true;
    dataPanelModifier.PaintColorSegmentFilterMask(rsCanvas, segmentLinearData);
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));

    /**
     * @tc.case: case. layout direction rtl
     */
    DataPanelModifier dataPanelModifierRtl(nullptr);
    dataPanelModifierRtl.SetIsRtl(true);
    dataPanelModifierRtl.PaintColorSegmentFilterMask(rsCanvas, segmentLinearData);
}

/**
 * @tc.name: DataPanelUpdateDateTest001
 * @tc.desc: Test DataPanel PaintMethod UpdateDate
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelUpdateDateTest001, TestSize.Level0)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataTheme));

    /**
     * @tc.cases: case. cover branch isEffect_.
     */
    DataPanelModifier dataPanelModifier(nullptr);
    dataPanelModifier.isEffect_->Set(true);
    dataPanelModifier.date_->Set(0.0f);
    dataPanelModifier.UpdateDate();
    EXPECT_EQ(1.0f, dataPanelModifier.date_->Get());

    dataPanelModifier.isEffect_->Set(false);
    dataPanelModifier.date_->Set(0.0f);
    dataPanelModifier.UpdateDate();
    EXPECT_EQ(1.0f, dataPanelModifier.date_->Get());
}

/**
 * @tc.name: DataPanelOnDrawTest001
 * @tc.desc: Test DataPanel PaintMethod OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelOnDrawTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. statement dataPanelModifier.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataTheme));
    DataPanelModifier dataPanelModifier(nullptr);

    /**
     * @tc.steps: step2. construct context and call onDraw().
     * @tc.expected: call onDraw and result is expected.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    DrawingContext context { rsCanvas, 10.0f, 10.0f };

    dataPanelModifier.onDraw(context);
    EXPECT_EQ(0, dataPanelModifier.dataPanelType_);

    dataPanelModifier.dataPanelType_ = 1;
    dataPanelModifier.onDraw(context);
    EXPECT_EQ(1, dataPanelModifier.dataPanelType_);
}

/**
 * @tc.name: DataPanelSortGradientColorsOffsetTest001
 * @tc.desc: Test DataPanel Modifier SortGradientColorsOffset
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelSortGradientColorsOffsetTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. statement dataPanelModifier.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataTheme));
    DataPanelModifier dataPanelModifier(nullptr);

    /**
     * @tc.steps: step2. Test positive sequence gradientColor.
     */
    Gradient gradient;
    GradientColor gradientColor1;
    gradientColor1.SetLinearColor(LinearColor::WHITE);
    gradientColor1.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColor1);
    GradientColor gradientColor2;
    gradientColor2.SetLinearColor(LinearColor::GRAY);
    gradientColor2.SetDimension(Dimension(0.5));
    gradient.AddColor(gradientColor2);
    GradientColor gradientColor3;
    gradientColor3.SetLinearColor(LinearColor::BLACK);
    gradientColor3.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColor3);
    auto result = dataPanelModifier.SortGradientColorsOffset(gradient).GetColors();
    auto color0 = result.at(0).GetLinearColor();
    EXPECT_EQ(color0, LinearColor::BLACK);
    auto color1 = result.at(1).GetLinearColor();
    EXPECT_EQ(color1, LinearColor::GRAY);
    auto color2 = result.at(2).GetLinearColor();
    EXPECT_EQ(color2, LinearColor::WHITE);
}

/**
 * @tc.name: DataPanelSortGradientColorsOffsetTest002
 * @tc.desc: Test DataPanel Modifier SortGradientColorsOffset
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelSortGradientColorsOffsetTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. statement dataPanelModifier.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataTheme));
    DataPanelModifier dataPanelModifier(nullptr);

    /**
     * @tc.steps: step2. Test Reverse GradientColor.
     */
    Gradient gradient;
    GradientColor gradientColor1;
    gradientColor1.SetLinearColor(LinearColor::WHITE);
    gradientColor1.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColor1);
    GradientColor gradientColor2;
    gradientColor2.SetLinearColor(LinearColor::GRAY);
    gradientColor2.SetDimension(Dimension(0.5));
    gradient.AddColor(gradientColor2);
    GradientColor gradientColor3;
    gradientColor3.SetLinearColor(LinearColor::BLACK);
    gradientColor3.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColor3);
    auto result = dataPanelModifier.SortGradientColorsOffset(gradient).GetColors();
    auto color0 = result.at(0).GetLinearColor();
    EXPECT_EQ(color0, LinearColor::WHITE);
    auto color1 = result.at(1).GetLinearColor();
    EXPECT_EQ(color1, LinearColor::GRAY);
    auto color2 = result.at(2).GetLinearColor();
    EXPECT_EQ(color2, LinearColor::BLACK);
}

/**
 * @tc.name: DataPanelShadowTest001
 * @tc.desc: Test DataPanel Modifier SortGradientColorsOffset
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelShadowTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. statement dataPanelModifier.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataTheme));
    DataPanelModifier dataPanelModifier(nullptr);

    /**
     * @tc.steps: step2. Test the setting of Shadow attribute.
     */
    std::vector<Gradient> valueColors;
    int length = 3;
    size_t shadowColorsLastLength = MAX_COUNT;
    GradientColorSet(valueColors, length);
    DataPanelShadow shadowOption { true, DEFAULT_SHADOW_VALUE, DEFAULT_SHADOW_VALUE, DEFAULT_SHADOW_VALUE,
        valueColors };
    dataPanelModifier.SetShadowVisible(shadowOption.isShadowVisible);
    dataPanelModifier.SetShadowRadius(shadowOption.radius);
    dataPanelModifier.SetShadowOffsetX(shadowOption.offsetX);
    dataPanelModifier.SetShadowOffsetY(shadowOption.offsetY);
    dataPanelModifier.SetShadowColors(shadowOption.colors, shadowColorsLastLength);
    EXPECT_EQ(dataPanelModifier.isShadowVisible_, true);
    EXPECT_EQ(dataPanelModifier.shadowRadiusFloat_->Get(), DEFAULT_SHADOW_VALUE);
    EXPECT_EQ(dataPanelModifier.shadowOffsetXFloat_->Get(), DEFAULT_SHADOW_VALUE);
    EXPECT_EQ(dataPanelModifier.shadowOffsetYFloat_->Get(), DEFAULT_SHADOW_VALUE);
    EXPECT_EQ(dataPanelModifier.shadowColorsLastLength_, MAX_COUNT);

    int length2 = 12;
    std::vector<Gradient> valueColors2;
    GradientColorSet(valueColors2, length2);
    DataPanelShadow shadowOption2 { true, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE,
        valueColors2 };
    dataPanelModifier.SetShadowVisible(shadowOption2.isShadowVisible);
    dataPanelModifier.SetShadowRadius(shadowOption2.radius);
    dataPanelModifier.SetShadowOffsetX(shadowOption2.offsetX);
    dataPanelModifier.SetShadowOffsetY(shadowOption2.offsetY);
    dataPanelModifier.SetShadowColors(shadowOption2.colors, shadowColorsLastLength);
    EXPECT_EQ(dataPanelModifier.isShadowVisible_, true);
    EXPECT_EQ(dataPanelModifier.shadowRadiusFloat_->Get(), -DEFAULT_SHADOW_VALUE);
    EXPECT_EQ(dataPanelModifier.shadowOffsetXFloat_->Get(), -DEFAULT_SHADOW_VALUE);
    EXPECT_EQ(dataPanelModifier.shadowOffsetYFloat_->Get(), -DEFAULT_SHADOW_VALUE);
    EXPECT_EQ(dataPanelModifier.shadowColorsLastLength_, MAX_COUNT);
}

/**
 * @tc.name: DataPanelUpdateContentModifierTest001
 * @tc.desc: Test DataPanel PaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelUpdateContentModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto dataPanelPattern = frameNode->GetPattern<DataPanelPattern>();
    EXPECT_NE(dataPanelPattern, nullptr);

    /**
     * @tc.steps: step2. construct paintWrapper and call UpdateContentModifier().
     * @tc.expected: call UpdateContentModifier and HasShadowOption is expected.
     */
    auto dataPanelPaintMethod = AceType::DynamicCast<DataPanelPaintMethod>(dataPanelPattern->CreateNodePaintMethod());
    ASSERT_NE(dataPanelPaintMethod, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    auto renderContext = frameNode->GetRenderContext();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, dataPanelPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    dataPanelPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_FALSE(dataPanelPaintProperty->HasShadowOption());

    /**
     * @tc.steps: step3. construct valueColors and call UpdateContentModifier().
     * @tc.expected: call UpdateContentModifier and HasValueColors is expected.
     */
    int length = 3;
    std::vector<Gradient> valueColors;
    GradientColorSet(valueColors, length);
    dataPanelPaintProperty->UpdateValueColors(valueColors);

    DataPanelShadow shadowOption { true, DEFAULT_SHADOW_VALUE, DEFAULT_SHADOW_VALUE, DEFAULT_SHADOW_VALUE,
        valueColors };
    dataPanel.SetShadowOption(shadowOption);
    dataPanelPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_TRUE(dataPanelPaintProperty->HasValueColors());

    /**
     * @tc.steps: step4. construct paintWrapper2 and call UpdateContentModifier().
     * @tc.expected: cover branch shadowOption colors size more than 0 and call UpdateContentModifier
     */
    DataPanelModelNG dataPanelModelNG2;
    dataPanelModelNG2.Create(VALUES, MAX, TYPE_CYCLE);
    std::vector<Gradient> valueColors2;
    GradientColorSet(valueColors2, length);
    DataPanelShadow shadowOption2 { true, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE,
        valueColors2 };
    dataPanelModelNG2.SetShadowOption(shadowOption2);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);

    auto renderContext2 = frameNode2->GetRenderContext();
    auto dataPanelPaintProperty2 = frameNode2->GetPaintProperty<DataPanelPaintProperty>();
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper2 = new PaintWrapper(renderContext2, geometryNode2, dataPanelPaintProperty2);
    ASSERT_NE(paintWrapper2, nullptr);
    dataPanelPaintMethod->UpdateContentModifier(paintWrapper2);
    EXPECT_EQ(dataPanelPaintProperty2->GetShadowOptionValue(), shadowOption2);
}

/**
 * @tc.name: DataPanelLineTypeBorderRadiusTest001
 * @tc.desc: Test line DataPanel's default Border Radius
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLineTypeBorderRadiusTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode, renderContext, pipeline and select theme.
     * @tc.expected: Objects are created successfully.
     */
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(settingApiVersion);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<OHOS::Ace::DataPanelTheme>();
    dataPanelTheme->defaultBorderRadius_ = Dimension(4.0, DimensionUnit::VP);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataPanelTheme));

    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step2. get border radius.
     * @tc.expected: the border radius is the same as the default setting.
     */
    Dimension defaultDimension = Dimension(8.0, DimensionUnit::VP);
    BorderRadiusProperty borderRadiusDefault = { defaultDimension, defaultDimension, defaultDimension,
        defaultDimension };
    auto getRadius = renderContext->GetBorderRadiusValue(borderRadiusDefault);

    EXPECT_TRUE(getRadius.radiusTopLeft.has_value());
    EXPECT_EQ(getRadius.radiusTopLeft.value().Value(), dataPanelTheme->GetDefaultBorderRadius().Value());
    EXPECT_EQ(getRadius.radiusTopLeft.value().Unit(), dataPanelTheme->GetDefaultBorderRadius().Unit());
    EXPECT_TRUE(getRadius.radiusTopRight.has_value());
    EXPECT_EQ(getRadius.radiusTopRight.value().Value(), dataPanelTheme->GetDefaultBorderRadius().Value());
    EXPECT_EQ(getRadius.radiusTopRight.value().Unit(), dataPanelTheme->GetDefaultBorderRadius().Unit());
    EXPECT_TRUE(getRadius.radiusBottomLeft.has_value());
    EXPECT_EQ(getRadius.radiusBottomLeft.value().Value(), dataPanelTheme->GetDefaultBorderRadius().Value());
    EXPECT_EQ(getRadius.radiusBottomLeft.value().Unit(), dataPanelTheme->GetDefaultBorderRadius().Unit());
    EXPECT_TRUE(getRadius.radiusBottomRight.has_value());
    EXPECT_EQ(getRadius.radiusBottomRight.value().Value(), dataPanelTheme->GetDefaultBorderRadius().Value());
    EXPECT_EQ(getRadius.radiusBottomRight.value().Unit(), dataPanelTheme->GetDefaultBorderRadius().Unit());
    Container::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: DataPanelLineTypeBorderRadiusTest002
 * @tc.desc: Test line DataPanel's Customized Border Radius
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLineTypeBorderRadiusTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode, renderContext, pipeline and select theme.
     * @tc.expected: Objects are created successfully.
     */
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(settingApiVersion);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<OHOS::Ace::DataPanelTheme>();
    dataPanelTheme->defaultBorderRadius_ = Dimension(4.0, DimensionUnit::VP);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataPanelTheme));

    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step2. get border radius.
     * @tc.expected: the border radius is the same as the customized setting.
     */
    Dimension setRadiusDimension = Dimension(10.0, DimensionUnit::VP);
    ViewAbstract::SetBorderRadius(setRadiusDimension);
    ViewAbstract::SetClipEdge(true);

    Dimension defaultDimension = Dimension(8.0, DimensionUnit::VP);
    BorderRadiusProperty borderRadiusDefault = { defaultDimension, defaultDimension, defaultDimension,
        defaultDimension };
    auto getRadius = renderContext->GetBorderRadiusValue(borderRadiusDefault);

    EXPECT_TRUE(getRadius.radiusTopLeft.has_value());
    auto tlRadius = getRadius.radiusTopLeft.value();
    EXPECT_EQ(tlRadius.Value(), setRadiusDimension.Value());
    EXPECT_EQ(tlRadius.Unit(), setRadiusDimension.Unit());
    EXPECT_TRUE(getRadius.radiusTopRight.has_value());
    auto trRadius = getRadius.radiusTopRight.value();
    EXPECT_EQ(trRadius.Value(), setRadiusDimension.Value());
    EXPECT_EQ(trRadius.Unit(), setRadiusDimension.Unit());
    EXPECT_TRUE(getRadius.radiusBottomLeft.has_value());
    auto blRadius = getRadius.radiusBottomLeft.value();
    EXPECT_EQ(blRadius.Value(), setRadiusDimension.Value());
    EXPECT_EQ(blRadius.Unit(), setRadiusDimension.Unit());
    EXPECT_TRUE(getRadius.radiusBottomRight.has_value());
    auto brRadius = getRadius.radiusBottomRight.value();
    EXPECT_EQ(brRadius.Value(), setRadiusDimension.Value());
    EXPECT_EQ(brRadius.Unit(), setRadiusDimension.Unit());
    Container::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: DataPanelPatternTest003
 * @tc.desc: Test DataPanel SetEffect
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and set effct.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_CYCLE);
    dataPanel.SetEffect(!CLOSE_EFFECT);

    /**
     * @tc.steps: step2. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetEffectValue(), CLOSE_EFFECT);
}

/**
 * @tc.name: DataPanelPatternTest004
 * @tc.desc: Test DataPanel Create when type is line
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPE_LINE);
}

/**
 * @tc.name: DataPanelPatternTest005
 * @tc.desc: Test DataPanel Create when values is longer than max length
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(LONG_VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), LONG_VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPE_CYCLE);
}

/**
 * @tc.name: DataPanelPatternTest006
 * @tc.desc: Test DataPanel Create when values has a single value
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest006, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(SINGLE_VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), SINGLE_VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPE_CYCLE);
}

/**
 * @tc.name: DataPanelPatternTest007
 * @tc.desc: Test DataPanel Create when values length is the maximum supported display length
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest007, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(FULL_VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), FULL_VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPE_CYCLE);
}

/**
 * @tc.name: DataPanelPatternTest008
 * @tc.desc: Test DataPanel Create when values length is 9
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest008, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(FULL_VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), FULL_VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPE_CYCLE);
}

/**
 * @tc.name: DataPanelPatternTest009
 * @tc.desc: Test DataPanel Create when max is default value
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest009, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX_DEFAULT, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX_DEFAULT);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPE_CYCLE);
}

/**
 * @tc.name: DataPanelPatternTest010
 * @tc.desc: Test DataPanel Create when max is a infinite value
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest0010, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX_INFINITE_VALUE, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX_INFINITE_VALUE);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPE_CYCLE);
}

/**
 * @tc.name: DataPanelPatternTest010
 * @tc.desc: Test DataPanel Create when max is a infinite value
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest0011, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX_ZERO_VALUE, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX_ZERO_VALUE);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPE_CYCLE);
}

/**
 * @tc.name: DataPanelPatternTest011
 * @tc.desc: Test DataPanel SetEffect
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest012, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and set effct.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_CYCLE);
    dataPanel.SetEffect(CLOSE_EFFECT_OFF);

    /**
     * @tc.steps: step2. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetEffectValue(), !CLOSE_EFFECT_OFF);
}

/**
 * @tc.name: DataPanelPatternTest013
 * @tc.desc: Test DataPanel SetEffect
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest013, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and set effct when type is line.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    dataPanel.SetEffect(CLOSE_EFFECT);

    /**
     * @tc.steps: step2. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetEffectValue(), !CLOSE_EFFECT);
}

/**
 * @tc.name: DataPanelPatternTest014
 * @tc.desc: Test DataPanel SetEffect
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest014, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create datapnel and set effct when type is line.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    dataPanel.SetEffect(CLOSE_EFFECT_OFF);

    /**
     * @tc.steps: step2. get value from dataPanelPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    EXPECT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetEffectValue(), !CLOSE_EFFECT_OFF);
}

/**
 * @tc.name: DataPanelMeasureTest005
 * @tc.desc: Test DataPanel Measure when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelMeasureTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datapnel and get framenode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    dataPanel.SetEffect(!CLOSE_EFFECT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode and set dataPanelLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto dataPanelPattern = frameNode->GetPattern<DataPanelPattern>();
    EXPECT_NE(dataPanelPattern, nullptr);
    auto dataPanelLayoutAlgorithm = dataPanelPattern->CreateLayoutAlgorithm();
    EXPECT_NE(dataPanelLayoutAlgorithm, nullptr);
    dataPanelLayoutAlgorithm->Reset();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(dataPanelLayoutAlgorithm));

    /**
     * @tc.steps: step3. compare dataPanelSize with expected value.
     * @tc.expected: step3. dataPanelSize is the same with expected value.
     */
    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }})
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    layoutConstraint.percentReference = MAX_SIZE;
    auto dataPanelDefaultSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value();
    EXPECT_EQ(dataPanelDefaultSize, MAX_SIZE);

    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).width(50).height(50)
     */
    LayoutConstraintF layoutConstraintVaildSize;
    layoutConstraintVaildSize.maxSize = MAX_SIZE;
    layoutConstraint.percentReference = MAX_SIZE;
    layoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    auto dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintVaildSize, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));

    LayoutConstraintF layoutConstraintHeight;
    layoutConstraintHeight.maxSize = MAX_SIZE;
    layoutConstraintHeight.percentReference = MAX_SIZE;
    layoutConstraintHeight.selfIdealSize.SetHeight(HEIGHT.ConvertToPx());
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeight, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_WIDTH, HEIGHT.ConvertToPx()));

    LayoutConstraintF layoutConstraintWidth;
    layoutConstraintWidth.maxSize = MAX_SIZE;
    layoutConstraintWidth.percentReference = MAX_SIZE;
    layoutConstraintWidth.selfIdealSize.SetWidth(WIDTH.ConvertToPx());
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintWidth, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(WIDTH.ConvertToPx(), MAX_HEIGHT));

    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).height(-100)
     */
    LayoutConstraintF layoutConstraintHeightUnvalid;
    layoutConstraintHeightUnvalid.percentReference = MAX_SIZE;
    layoutConstraintHeightUnvalid.selfIdealSize.SetHeight(NEGATIVE_NUMBER);
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeightUnvalid, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).width(-100)
     */
    LayoutConstraintF layoutConstraintWidthUnvalid;
    layoutConstraintWidthUnvalid.percentReference = MAX_SIZE;
    layoutConstraintWidthUnvalid.selfIdealSize.SetWidth(NEGATIVE_NUMBER);
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeightUnvalid, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_WIDTH, MAX_HEIGHT));
}

/**
 * @tc.name: DataPanelMeasureTest006
 * @tc.desc: Test DataPanel Measure by percentReference instead of maxSize when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelMeasureTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datapanel and get framenode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    dataPanel.SetEffect(!CLOSE_EFFECT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode and set dataPanelLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto dataPanelPattern = frameNode->GetPattern<DataPanelPattern>();
    EXPECT_NE(dataPanelPattern, nullptr);
    auto dataPanelLayoutAlgorithm = dataPanelPattern->CreateLayoutAlgorithm();
    EXPECT_NE(dataPanelLayoutAlgorithm, nullptr);
    dataPanelLayoutAlgorithm->Reset();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(dataPanelLayoutAlgorithm));

    /**
     * @tc.steps: step3. compare dataPanelSize with expected value.
     * @tc.expected: step3. dataPanelSize is the same with expected value.
     */
    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }})
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    layoutConstraint.percentReference = MAX_PERCENT_SIZE;
    auto dataPanelDefaultSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value();
    EXPECT_EQ(dataPanelDefaultSize, MAX_PERCENT_SIZE);

    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).width(50).height(50)
     */
    LayoutConstraintF layoutConstraintVaildSize;
    layoutConstraintVaildSize.maxSize = MAX_SIZE;
    layoutConstraint.percentReference = MAX_PERCENT_SIZE;
    layoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    auto dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintVaildSize, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));

    /**
     * @tc.steps: step4. compare dataPanelSize with expected value.
     * @tc.expected: step4. dataPanelSize is the same with expected value.
     */
    LayoutConstraintF layoutConstraintHeight;
    layoutConstraintHeight.maxSize = MAX_SIZE;
    layoutConstraintHeight.percentReference = MAX_PERCENT_SIZE;
    layoutConstraintHeight.selfIdealSize.SetHeight(HEIGHT.ConvertToPx());
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeight, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_PERCENT_WIDTH, HEIGHT.ConvertToPx()));

    /**
     * @tc.steps: step5. compare dataPanelSize with expected value.
     * @tc.expected: step5. dataPanelSize is the same with expected value.
     */
    LayoutConstraintF layoutConstraintWidth;
    layoutConstraintWidth.maxSize = MAX_SIZE;
    layoutConstraintWidth.percentReference = MAX_PERCENT_SIZE;
    layoutConstraintWidth.selfIdealSize.SetWidth(WIDTH.ConvertToPx());
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintWidth, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(WIDTH.ConvertToPx(), MAX_PERCENT_HEIGHT));

    /**
     * @tc.steps: step6. compare dataPanelSize with expected value by infinite.
     * @tc.expected: step6. dataPanelSize is the same with expected value as root width and height.
     */
    MockPipelineContext::GetCurrent()->SetRootSize(ROOT_WIDTH, ROOT_HEIGHT);
    LayoutConstraintF layoutConstraintInfinite;
    layoutConstraintInfinite.percentReference = MAX_INFINITE_SIZE;
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintInfinite, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(ROOT_WIDTH, ROOT_HEIGHT));

    /**
     * @tc.steps: step7. compare dataPanelSize with expected value by infinite width.
     * @tc.expected: step7. dataPanelSize is the same with expected value as min width and height.
     */
    LayoutConstraintF layoutConstraintWidthInfinite;
    layoutConstraintWidthInfinite.percentReference = SizeF(MAX_INFINITE, MAX_HEIGHT);
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintWidthInfinite, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_HEIGHT, MAX_HEIGHT));
}

/**
 * @tc.name: DataPanelGetPaintPathTest001
 * @tc.desc: Test DataPanel PaintMethod GetPaintPath
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelGetPaintPathTest001, TestSize.Level0)
{
    DataPanelModifier dataPanelModifier(nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 50.0f, 50.0f };
    // test Solid color when the valueColors >0 and valueColors <=9
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor::WHITE);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor::BLACK);
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);

    ArcData arcData;
    Offset center = Offset(context.width * PERCENT_HALF, context.height * PERCENT_HALF);
    arcData.center = center;
    arcData.thickness = STROKE_WIDTH.ConvertToPx();
    arcData.radius = WIDTH.ConvertToPx();
    arcData.lastAngle = MAX_ZERO_VALUE;
    arcData.drawAngle = DRAW_ANGLE;
    arcData.totalDrawAngle = DRAW_ANGLE;
    arcData.shadowColor = gradient;
    arcData.progressColors = gradient;
    RSPath path;
    RSPath endPath;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    dataPanelModifier.GetPaintPath(arcData, path, endPath);
    dataPanelModifier.PaintProgress(rsCanvas, arcData, path, endPath, true);
    dataPanelModifier.PaintProgress(rsCanvas, arcData, path, endPath, false);
}
} // namespace OHOS::Ace::NG