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

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string NAME = "radio";
const std::string GROUP_NAME = "radioGroup";
const std::string GROUP_NAME_CHANGE = "radioGroupChange";
const Dimension WIDTH = 50.0_vp;
const Dimension HEIGHT = 50.0_vp;
const NG::PaddingPropertyF PADDING = NG::PaddingPropertyF();
const bool CHECKED = true;
} // namespace

class RadioPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void RadioPropertyTestNg::SetUpTestCase() {}
void RadioPropertyTestNg::TearDownTestCase() {}
void RadioPropertyTestNg::SetUp() {}
void RadioPropertyTestNg::TearDown() {}

/**
 * @tc.name: RadioPaintPropertyTest001
 * @tc.desc: Set Radio value into RadioPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPropertyTestNg, RadioPaintPropertyTest001, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(CHECKED);
    radioModelNG.SetWidth(WIDTH);
    radioModelNG.SetHeight(HEIGHT);
    radioModelNG.SetPadding(PADDING);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    EXPECT_FALSE(radioPaintProperty == nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioCheck(), CHECKED);
}

/**
 * @tc.name: RadioEventHubPropertyTest002
 * @tc.desc: Set Radio value into RadioEventHub and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPropertyTestNg, RadioEventHubPropertyTest002, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    EXPECT_EQ(eventHub->GetValue(), NAME);
    EXPECT_EQ(eventHub->GetGroup(), GROUP_NAME);
}

/**
 * @tc.name: RadioEventTest003
 * @tc.desc: Test Radio onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPropertyTestNg, RadioEventTest003, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    bool isChecked = false;
    auto onChange = [&isChecked](bool select) { isChecked = select; };
    radioModelNG.SetOnChange(onChange);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioPatternTest004
 * @tc.desc: Test Radio onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPropertyTestNg, RadioPatternTest004, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    EXPECT_FALSE(pattern == nullptr);
    pattern->SetPreGroup(GROUP_NAME);
    frameNode->MarkModifyDone();
    pattern->SetPreGroup(GROUP_NAME_CHANGE);
    frameNode->MarkModifyDone();
}

/**
 * @tc.name: RadioMeasureTest005
 * @tc.desc: Test Radio Measure.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPropertyTestNg, RadioMeasureTest005, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    // Create LayoutWrapper and set radioLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto radioPattern = frameNode->GetPattern<RadioPattern>();
    EXPECT_FALSE(radioPattern == nullptr);
    auto radioLayoutAlgorithm = radioPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(radioLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(radioLayoutAlgorithm));
    // Radio without setting height and width.
    const LayoutConstraintF layoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    // Calculate the size and offset.
    radioLayoutAlgorithm->Measure(&layoutWrapper);
    radioLayoutAlgorithm->Layout(&layoutWrapper);
    // Test the default size set in theme and the offset.
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->FlushBuild();
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(),
        SizeF(radioTheme->GetHeight().ConvertToPx(), radioTheme->GetWidth().ConvertToPx()));
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameOffset(), OffsetF(0.0, 0.0));

    /**
    //     corresponding ets code:
    //         Radio({ value: 'radio', group: 'radioGroup' }).width(50).height(50)
    */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    radioLayoutAlgorithm->Measure(&layoutWrapper);
    // Test the size set by codes.
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
}

} // namespace OHOS::Ace::NG