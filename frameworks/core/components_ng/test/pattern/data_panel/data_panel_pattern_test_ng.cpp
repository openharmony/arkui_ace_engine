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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::vector<double> VALUES = { 1.0, 2.0, 3.0, 4.0 };
constexpr double MAX = 200.0;
constexpr size_t TYPE_CYCLE = 0;
constexpr size_t TYPE_LINE = 1;
constexpr bool CLOSE_EFFECT = true;
constexpr Dimension WIDTH = 50.0_vp;
constexpr Dimension HEIGHT = 50.0_vp;
constexpr float MAX_WIDTH = 400.0f;
constexpr float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float NEGATIVE_NUMBER = -100;
constexpr bool SKIP_MEASURE = true;
constexpr bool NO_SKIP_MEASURE = false;
const Color TRUE_COLOR = Color(0x00000000);
const Color ERROR_COLOR = Color();
constexpr double DEFAULT_SHADOW_VALUE = 5.0;
} // namespace

class DataPanelPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void GradientColorSet(std::vector<Gradient>& valueColors, const int& length);
};

void DataPanelPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void DataPanelPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void DataPanelPropertyTestNg::GradientColorSet(std::vector<Gradient>& valueColors, const int& length)
{
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetColor(Color(0x00000000));
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetColor(Color(0x000000FF));
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
HWTEST_F(DataPanelPropertyTestNg, DataPanelLayoutPropertyTest001, TestSize.Level1)
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
HWTEST_F(DataPanelPropertyTestNg, DataPanelLayoutPropertyTest002, TestSize.Level1)
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
HWTEST_F(DataPanelPropertyTestNg, DataPanelMeasureTest003, TestSize.Level1)
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
     * @tc.steps: step2. Create LayoutWrapper and set dataPanelLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    auto dataPanelDefaultSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value();
    EXPECT_EQ(dataPanelDefaultSize, MAX_SIZE);

    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).width(50).height(50)
     */
    LayoutConstraintF layoutConstraintVaildSize;
    layoutConstraintVaildSize.maxSize = MAX_SIZE;
    layoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    auto dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintVaildSize, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));

    LayoutConstraintF layoutConstraintHeight;
    layoutConstraintHeight.maxSize = MAX_SIZE;
    layoutConstraintHeight.selfIdealSize.SetHeight(HEIGHT.ConvertToPx());
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeight, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_WIDTH, HEIGHT.ConvertToPx()));

    LayoutConstraintF layoutConstraintWidth;
    layoutConstraintWidth.maxSize = MAX_SIZE;
    layoutConstraintWidth.selfIdealSize.SetWidth(WIDTH.ConvertToPx());
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintWidth, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(WIDTH.ConvertToPx(), MAX_HEIGHT));

    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).height(-100)
     */
    LayoutConstraintF layoutConstraintHeightUnvalid;
    layoutConstraintHeightUnvalid.maxSize = MAX_SIZE;
    layoutConstraintHeightUnvalid.selfIdealSize.SetHeight(NEGATIVE_NUMBER);
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeightUnvalid, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
     *     corresponding ets code:
     *         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).width(-100)
     */
    LayoutConstraintF layoutConstraintWidthUnvalid;
    layoutConstraintWidthUnvalid.maxSize = MAX_SIZE;
    layoutConstraintWidthUnvalid.selfIdealSize.SetWidth(NEGATIVE_NUMBER);
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeightUnvalid, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_WIDTH, MAX_HEIGHT));
}

/**
 * @tc.name: DataPanelPatternTest004
 * @tc.desc: Test DataPanel isAtomicNode
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPropertyTestNg, DataPanelPatternTest004, TestSize.Level1)
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
HWTEST_F(DataPanelPropertyTestNg, DataPanelPatternTest005, TestSize.Level1)
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
HWTEST_F(DataPanelPropertyTestNg, DataPanelPatternTest006, TestSize.Level1)
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
HWTEST_F(DataPanelPropertyTestNg, DataPanelPatternTest007, TestSize.Level1)
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
     * @tc.steps: step2. Create LayoutWrapper and set dataPanelLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    auto dataPanelDefaultSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value();
    EXPECT_EQ(dataPanelDefaultSize, MAX_SIZE);
}

/**
 * @tc.name: DataPanelTest008
 * @tc.desc: Test dataPanel pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPropertyTestNg, DataPanelPaintPropertyTest005, TestSize.Level1)
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
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
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
     *     case 1: LayoutWrapper::SkipMeasureContent = true , skipMeasure = true;
     */
    bool first_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(first_case);

    /**
     *     case 2: LayoutWrapper::SkipMeasureContent = true , skipMeasure = true;
     */
    bool second_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_FALSE(second_case);

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(dataPanelLayoutAlgorithm, NO_SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     *     case 3: LayoutWrapper::SkipMeasureContent = false , skipMeasure = true;
     */
    bool third_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(third_case);

    /**
     *     case 4: LayoutWrapper::SkipMeasureContent = false , skipMeasure = false;
     */
    bool forth_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(forth_case);
}

/**
 * @tc.name: DataPanelTest009
 * @tc.desc: Test DataPanel PaintMethod SetTrackBackground
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelPropertyTestNg, DataPanelPaintPropertyTest006, TestSize.Level1)
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
HWTEST_F(DataPanelPropertyTestNg, DataPanelPaintPropertyTest007, TestSize.Level1)
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
HWTEST_F(DataPanelPropertyTestNg, DataPanelPaintPropertyTest008, TestSize.Level1)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_CYCLE);
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetColor(Color(0x00000000));
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetColor(Color(0x00000000));
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
HWTEST_F(DataPanelPropertyTestNg, DataPanelPaintPropertyTest009, TestSize.Level1)
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
HWTEST_F(DataPanelPropertyTestNg, DataPanelPaintPropertyTest010, TestSize.Level1)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_CYCLE);
    int length = 3;
    std::vector<Gradient> valueColors;
    GradientColorSet(valueColors, length);
    DataPanelShadow shadowOption { DEFAULT_SHADOW_VALUE, DEFAULT_SHADOW_VALUE, DEFAULT_SHADOW_VALUE, valueColors };
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
    DataPanelShadow shadowOption2 { -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE, valueColors2 };
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
    DataPanelShadow shadowOption3 { -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE, valueColors3 };
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
    DataPanelShadow shadowOption4 { 0.0, 0.0, 0.0, valueColors4 };
    dataPanelModelNG4.SetShadowOption(shadowOption4);
    auto frameNode4 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode4, nullptr);
    auto dataPanelPaintProperty4 = frameNode4->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty4, nullptr);
    EXPECT_EQ(dataPanelPaintProperty4->GetShadowOptionValue(), shadowOption4);
}
} // namespace OHOS::Ace::NG
