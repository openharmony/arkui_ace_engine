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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/data_panel/data_panel_modifier.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline/base/constants.h"
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
    MockPipelineBase::SetUp();
}

void DataPanelTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
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
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest001, TestSize.Level1)
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
HWTEST_F(DataPanelTestNg, DataPanelLayoutPropertyTest002, TestSize.Level1)
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
    MockPipelineBase::GetCurrent()->SetRootSize(ROOT_WIDTH, ROOT_HEIGHT);
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
HWTEST_F(DataPanelTestNg, DataPanelPatternTest004, TestSize.Level1)
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
HWTEST_F(DataPanelTestNg, DataPanelPatternTest005, TestSize.Level1)
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
HWTEST_F(DataPanelTestNg, DataPanelPatternTest006, TestSize.Level1)
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
HWTEST_F(DataPanelTestNg, DataPanelPatternTest007, TestSize.Level1)
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
HWTEST_F(DataPanelTestNg, DataPanelPaintPropertyTest006, TestSize.Level1)
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
HWTEST_F(DataPanelTestNg, DataPanelPaintPropertyTest007, TestSize.Level1)
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
HWTEST_F(DataPanelTestNg, DataPanelPaintPropertyTest008, TestSize.Level1)
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
HWTEST_F(DataPanelTestNg, DataPanelPaintPropertyTest009, TestSize.Level1)
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
 * @tc.name: DataPanelPaintMethodTest001
 * @tc.desc: Test DataPanel PaintMethod PaintRainbowFilterMask
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataTheme));

    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    ArcData arcData;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));

    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetColor(START_COLOR);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetColor(END_COLOR);
    gradientColorEnd.SetDimension(Dimension(1.0));
    arcData.shadowColor = gradient;

    dataPanelModifier.PaintRainbowFilterMask(rsCanvas, arcData);
}

/**
 * @tc.name: DataPanelPaintMethodTest002
 * @tc.desc: Test DataPanel PaintMethod PaintProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataTheme));

    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    ArcData arcData;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));

    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetColor(START_COLOR);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetColor(END_COLOR);
    gradientColorEnd.SetDimension(Dimension(1.0));
    arcData.progressColors = gradient;

    dataPanelModifier.PaintProgress(rsCanvas, arcData);
}

/**
 * @tc.name: DataPanelPaintMethodTest003
 * @tc.desc: Test DataPanel PaintMethod PaintBackground
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest003, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataTheme));

    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.PaintBackground(rsCanvas, OFFSET, TOTAL_WIDTH, TOTAL_HEIGHT, SEGMENTWIDTH);
    dataPanelModifier.PaintBackground(rsCanvas, OFFSET, TOTAL_WIDTH, TOTAL_HEIGHT * 4, SEGMENTWIDTH);
}

/**
 * @tc.name: DataPanelPaintMethodTest004
 * @tc.desc: Test DataPanel PaintMethod PaintSpace
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest004, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataTheme));

    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));

    LinearData linearData;
    dataPanelModifier.PaintSpace(rsCanvas, linearData, SPACEWIDTH);
}

/**
 * @tc.name: DataPanelPaintMethodTest005
 * @tc.desc: Test DataPanel PaintMethod PaintColorSegment
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest005, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataTheme));

    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
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
}

/**
 * @tc.name: DataPanelPaintMethodTest006
 * @tc.desc: Test DataPanel PaintMethod PaintTrackBackground
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest006, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataTheme));

    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    ArcData arcData;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    dataPanelModifier.PaintTrackBackground(rsCanvas, arcData, START_COLOR);
}

/**
 * @tc.name: DataPanelPaintMethodTest007
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest007, TestSize.Level1)
{
    /**
     * case 1:defaultThickness >= radius
     * radius = -10.0f
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DataPanelTheme>()));

    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, -10.0f, -10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.PaintCircle(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintMethodTest08
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest008, TestSize.Level1)
{
    /**
     * case 2:defaultThickness < radius
     * radius = 50.0f
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<DataPanelTheme>()));

    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;

    DrawingContext context { rsCanvas, 50.0f, 50.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.PaintCircle(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintMethodTest09
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest009, TestSize.Level1)
{
    /**
     * case 3:maxValue > 0 and totalvalue < maxvalue
     * max = 100.0f Values = { 1.0f, 2.0f, 3.0f };
     * effect = false  totalvalue > 0
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(100.0f);
    dataPanelModifier.SetEffect(false);
    std::vector<double> VALUES = { 1.0f, 2.0f, 3.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintCircle(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintMethodTest10
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest010, TestSize.Level1)
{
    /**
     * case 4:maxValue < 0 and totalvalue > maxvalue
     * max = -100.0f Values = { 100.0f, 200.0f, 300.0f };
     * effect = true  totalvalue > 0
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(-100.0f);
    dataPanelModifier.SetEffect(true);
    std::vector<double> VALUES = { 100.0f, 200.0f, 300.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintCircle(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintMethodTest11
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest011, TestSize.Level1)
{
    /**
     * case 5:effect = true  totalvalue = 0
     * effect = true   values = { -10.0f, 10.0f } totalvalue = 0
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));

    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(100.0f);
    dataPanelModifier.SetEffect(true);
    std::vector<double> VALUES = { -10.0f, 10.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintCircle(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintMethodTest12
 * @tc.desc: Test DataPanel PaintMethod PaintCircle
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintMethodTest012, TestSize.Level1)
{
    /**
     * case 6:effect = false  totalvalue = 0
     * effect = false   values = { -10.0f, 10.0f } totalvalue = 0
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(100.0f);
    dataPanelModifier.SetEffect(false);
    std::vector<double> VALUES = { -10.0f, 10.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintCircle(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintLinearProgressTest001
 * @tc.desc: Test DataPanel PaintMethod PaintLineProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintLinearProgressTest001, TestSize.Level1)
{
    /**
     * case 1:sum of value = max ,max > 0
     * values ={10.0f,10.0f} max = 20.0f
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    dataPanelModifier.SetMax(20.0f);
    std::vector<double> VALUES = { 10.0f, 10.0f };
    dataPanelModifier.SetValues(VALUES);
    dataPanelModifier.PaintLinearProgress(context, OFFSET);
}

/**
 * @tc.name: DataPanelPaintLinearProgressTest002
 * @tc.desc: Test DataPanel PaintMethod PaintLineProgress
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPaintLinearProgressTest002, TestSize.Level1)
{
    /**
     * case 2:sum of value != max, max < 0
     * values ={-5.0f, 0.0f} max = -20.0f
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
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
HWTEST_F(DataPanelTestNg, DataPanelPaintLinearProgressTest003, TestSize.Level1)
{
    /**
     * case 3:one of value nearequael 0 and > 0
     * values ={ 0.0001f, 5.0f} max = 20.0f
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
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
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataPanelTheme = AceType::MakeRefPtr<DataPanelTheme>();
    dataPanelTheme->color = { { Color::WHITE, Color::BLACK }, { Color::WHITE, Color::BLACK },
        { Color::WHITE, Color::BLACK } };
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataPanelTheme));
    DataPanelModifier dataPanelModifier;
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
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
}

/**
 * @tc.name: DataPanelUpdateDateTest001
 * @tc.desc: Test DataPanel PaintMethod UpdateDate
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelUpdateDateTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(dataTheme));

    /**
     * @tc.cases: case. cover branch isEffect_.
     */
    DataPanelModifier dataPanelModifier;
    dataPanelModifier.isEffect_->Set(true);
    dataPanelModifier.date_->Set(0.0f);
    dataPanelModifier.UpdateDate();
    EXPECT_EQ(1.0f, dataPanelModifier.date_->Get());

    dataPanelModifier.isEffect_->Set(false);
    dataPanelModifier.date_->Set(0.0f);
    dataPanelModifier.UpdateDate();
    EXPECT_EQ(0.0f, dataPanelModifier.date_->Get());
}

/**
 * @tc.name: DataPanelOnDrawTest001
 * @tc.desc: Test DataPanel PaintMethod OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelOnDrawTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. statement dataPanelModifier.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto dataTheme = AceType::MakeRefPtr<DataPanelTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(dataTheme));
    DataPanelModifier dataPanelModifier;

    /**
     * @tc.steps: step2. construct context and call onDraw().
     * @tc.expected: call onDraw and result is expected.
     */
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };

    dataPanelModifier.onDraw(context);
    EXPECT_EQ(0, dataPanelModifier.dataPanelType_);

    dataPanelModifier.dataPanelType_ = 1;
    dataPanelModifier.onDraw(context);
    EXPECT_EQ(1, dataPanelModifier.dataPanelType_);
}

/**
 * @tc.name: UpdateContentModifier001
 * @tc.desc: Test DataPanel PaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, UpdateContentModifier001, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
