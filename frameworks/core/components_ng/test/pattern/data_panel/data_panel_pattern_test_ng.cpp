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
#include "gtest/internal/gtest-internal.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::vector<double> VALUES = { 1.0, 2.0, 3.0, 4.0 };
const double MAX = 200.0;
const size_t TYPECYCLE = 0;
const bool CLOSE_EFFECT = true;
const Dimension WIDTH = 50.0_vp;
const Dimension HEIGHT = 50.0_vp;
const float MAX_WIDTH = 400.0f;
const float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
const float NEGATIVE_NUMBER = -100;
} // namespace

class DataPanelPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

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
    dataPanel.Create(VALUES, MAX, TYPECYCLE);
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
     * @tc.steps: step3. get value from gaugePaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(dataPanelPaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(dataPanelPaintProperty->GetValuesValue(), VALUES);
    EXPECT_EQ(dataPanelPaintProperty->GetDataPanelTypeValue(), TYPECYCLE);
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
    dataPanel.Create(VALUES, MAX, TYPECYCLE);
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
    dataPanel.Create(VALUES, MAX, TYPECYCLE);
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
    //     corresponding ets code:
    //         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }})
    */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    auto dataPanelDefaultSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value();
    EXPECT_EQ(dataPanelDefaultSize, MAX_SIZE);

    /**
    //     corresponding ets code:
    //         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).width(50).height(50)
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
    //     corresponding ets code:
    //         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).height(-100)
    */
    LayoutConstraintF layoutConstraintHeightUnvalid;
    layoutConstraintHeightUnvalid.maxSize = MAX_SIZE;
    layoutConstraintHeightUnvalid.selfIdealSize.SetHeight(NEGATIVE_NUMBER);
    dataPanelSize = dataPanelLayoutAlgorithm->MeasureContent(layoutConstraintHeightUnvalid, &layoutWrapper).value();
    EXPECT_EQ(dataPanelSize, SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
    //     corresponding ets code:
    //         DataPanel({ { values: this.values, max: 100, type: DataPanelType.Line }}).width(-100)
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
    dataPanel.Create(VALUES, MAX, TYPECYCLE);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    bool isAtomicNode = frameNode->IsAtomicNode();
    EXPECT_TRUE(isAtomicNode);
}

} // namespace OHOS::Ace::NG
