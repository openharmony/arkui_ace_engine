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

#include <iostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "gtest/internal/gtest-port.h"

#define private public
#include "core/components/theme/theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/slider/slider_paint_method.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_ng/pattern/slider/slider_style.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float VALUE = 50.0f;
constexpr float STEP = 10.0f;
constexpr float MIN = 0.0f;
constexpr float MAX = 100.0f;
const SliderModel::SliderMode TEST_SLIDERMODE = SliderModel::SliderMode::INSET;
const Axis TEST_AXIS = Axis::HORIZONTAL;
constexpr bool BOOL_VAULE = true;
const Color TEST_COLOR = Color::BLUE;
constexpr float MIN_LABEL = 10.0f;
constexpr float MAX_LABEL = 20.0f;
constexpr Dimension WIDTH = 50.0_vp;
constexpr Dimension HEIGHT = 50.0_vp;
constexpr float MAX_WIDTH = 500.0f;
constexpr float MAX_HEIGHT = 500.0f;
constexpr bool SKIP_MEASURE = true;
constexpr bool NO_SKIP_MEASURE = false;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
const Alignment ALIGNMENT = Alignment::BOTTOM_RIGHT;
} // namespace
class SliderPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SliderPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SliderPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: SliderPatternTestNg001
 * @tc.desc: Test Slider PaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from sliderPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
}

/**
 * @tc.name: SliderPatternTestNg002
 * @tc.desc: Test Slider Set Func
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderMode(TEST_SLIDERMODE);
    sliderModelNG.SetDirection(TEST_AXIS);
    sliderModelNG.SetReverse(BOOL_VAULE);
    sliderModelNG.SetBlockColor(TEST_COLOR);
    sliderModelNG.SetTrackBackgroundColor(TEST_COLOR);
    sliderModelNG.SetSelectColor(TEST_COLOR);
    sliderModelNG.SetMinLabel(MIN_LABEL);
    sliderModelNG.SetMaxLabel(MAX_LABEL);
    sliderModelNG.SetShowSteps(BOOL_VAULE);
    sliderModelNG.SetThickness(WIDTH);
    std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
    sliderModelNG.SetOnChange(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX_LABEL);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN_LABEL);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
    EXPECT_EQ(sliderPaintProperty->GetReverse(), BOOL_VAULE);
    EXPECT_EQ(sliderPaintProperty->GetDirection(), TEST_AXIS);
    EXPECT_EQ(sliderPaintProperty->GetBlockColor(), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetTrackBackgroundColor(), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetSelectColor(), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetShowSteps(), BOOL_VAULE);
}

/**
 * @tc.name: SliderPatternTestNg003
 * @tc.desc: Test Slider MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get layoutWrapper and setLayoutAlgorithm.
     * @tc.expected: step2. check sliderLayoutAlgorithm is not null.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    EXPECT_NE(sliderPattern, nullptr);
    auto sliderLayoutAlgorithm = sliderPattern->CreateLayoutAlgorithm();
    EXPECT_NE(sliderLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm));
    /**
     * @tc.steps: step3. compare sliderSize with expected value.
     * @tc.expected: step3. sliderSize is the same with expected value.
     */
    /**
     *     corresponding ets code:
     *          Row.Width(500).Height(500) {
     *         Slider({ { value: 50, min: 0, max: 100 }}).width(50).height(50)
     *     }
     */
    LayoutConstraintF layoutConstraintSizevalid;
    layoutConstraintSizevalid.maxSize = MAX_SIZE;
    layoutConstraintSizevalid.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SliderPatternTestNg004
 * @tc.desc: Test Slider Create
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from sliderPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
}

/**
 * @tc.name: SliderPatternTestNg005
 * @tc.desc: Test slider pattern OnDirtyLayoutWrapperSwap function..
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create slider frameNode, get sliderPattern and sliderWrapper.
     * @tc.expected: step2. get sliderPattern success.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::DynamicCast<SliderPattern>(frameNode->GetPattern());
    EXPECT_NE(sliderPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. call sliderPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    RefPtr<SliderLayoutAlgorithm> sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     * @tc.steps: step4. call sliderPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step4. OnDirtyLayoutWrapperSwap success and result correct.
     */

    /**
     *     case 1: LayoutWrapper::SkipMeasureContent = true , skipMeasure = true;
     */
    bool first_case = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(first_case);

    /**
     *     case 2: LayoutWrapper::SkipMeasureContent = true , skipMeasure = true;
     */
    bool second_case = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_FALSE(second_case);

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, NO_SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     *     case 3: LayoutWrapper::SkipMeasureContent = false , skipMeasure = true;
     */
    bool third_case = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(third_case);

    /**
     *     case 4: LayoutWrapper::SkipMeasureContent = false , skipMeasure = false;
     */
    bool forth_case = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_FALSE(forth_case);
}

/**
 * @tc.name: SliderPatternTestNg006
 * @tc.desc: Test Slider OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datapnel and set effct.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create dataPanel frameNode, get dataPanelPattern and dataPanelWrapper.
     * @tc.expected: step2. get dataPanelPattern success.
     */
    RefPtr<SliderPattern> dataPanelPattern = AceType::DynamicCast<SliderPattern>(frameNode->GetPattern());
    auto layoutProperty = frameNode->GetLayoutProperty();
    dataPanelPattern->OnModifyDone();
    layoutProperty->UpdateAlignment(ALIGNMENT);
    dataPanelPattern->OnModifyDone();
    EXPECT_NE(ALIGNMENT, layoutProperty->GetPositionProperty()->GetAlignmentValue());
}
} // namespace OHOS::Ace::NG
