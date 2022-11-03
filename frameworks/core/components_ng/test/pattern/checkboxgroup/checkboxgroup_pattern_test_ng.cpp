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

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string NAME = "checkbox";
const std::string GROUP_NAME = "checkboxGroup";
const std::string GROUP_NAME_CHANGE = "checkboxGroupChange";
const std::string TAG = "CHECKBOX_TAG";
const Dimension WIDTH = 50.0_vp;
const Dimension HEIGHT = 50.0_vp;
const NG::PaddingPropertyF PADDING = NG::PaddingPropertyF();
const bool SELECTED = true;
const Color SELECTED_COLOR = Color::BLUE;
} // namespace

class CheckBoxGroupPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CheckBoxGroupPropertyTestNg::SetUpTestCase() {}
void CheckBoxGroupPropertyTestNg::TearDownTestCase() {}
void CheckBoxGroupPropertyTestNg::SetUp() {}
void CheckBoxGroupPropertyTestNg::TearDown() {}

/**
 * @tc.name: CheckBoxGroupPaintPropertyTest001
 * @tc.desc: Set CheckBoxGroup value into CheckBoxGroupPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPropertyTestNg, CheckBoxGroupPaintPropertyTest001, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    checkBoxGroupModelNG.SetSelectAll(SELECTED);
    checkBoxGroupModelNG.SetSelectedColor(SELECTED_COLOR);
    checkBoxGroupModelNG.SetWidth(WIDTH);
    checkBoxGroupModelNG.SetHeight(HEIGHT);
    checkBoxGroupModelNG.SetPadding(PADDING);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    EXPECT_EQ(eventHub->GetGroupName(), GROUP_NAME);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    EXPECT_FALSE(checkBoxPaintProperty == nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupSelect(), SELECTED);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupSelectedColor(), SELECTED_COLOR);
}

/**
 * @tc.name: CheckBoxGroupEventTest002
 * @tc.desc: Test CheckBox onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPropertyTestNg, CheckBoxGroupEventTest002, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroup;
    checkBoxGroup.Create(GROUP_NAME);
    std::vector<std::string> vec;
    int status = 0;
    CheckboxGroupResult groupResult(
        std::vector<std::string> { NAME }, int(CheckBoxGroupPaintProperty::SelectStatus::ALL));
    auto onChange = [&vec, &status](const BaseEventInfo* groupResult) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(groupResult);
        vec = eventInfo->GetNameList();
        status = eventInfo->GetStatus();
    };
    checkBoxGroup.SetOnChange(onChange);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    eventHub->UpdateChangeEvent(&groupResult);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec.front(), NAME);
    EXPECT_EQ(status, int(CheckBoxGroupPaintProperty::SelectStatus::ALL));
}

/**
 * @tc.name: CheckBoxGroupPatternTest004
 * @tc.desc: Test CheckBox onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPropertyTestNg, CheckBoxGroupPatternTest003, TestSize.Level1)
{
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    EXPECT_FALSE(pattern == nullptr);
    pattern->SetPreGroup(GROUP_NAME);
    frameNode->MarkModifyDone();
    pattern->SetPreGroup(GROUP_NAME_CHANGE);
    frameNode->MarkModifyDone();
}

/**
 * @tc.name: CheckBoxGroupMeasureTest005
 * @tc.desc: Test CheckBoxGroup Measure.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPropertyTestNg, CheckBoxGroupMeasureTest004, TestSize.Level1)
{
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    // Create LayoutWrapper and set CheckBoxGroupLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto checkBoxGroupPattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    EXPECT_FALSE(checkBoxGroupPattern == nullptr);
    auto checkBoxGroupLayoutAlgorithm = checkBoxGroupPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(checkBoxGroupLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(checkBoxGroupLayoutAlgorithm));
    // CheckBoxGroup without setting height and width.
    const LayoutConstraintF layoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    // Calculate the size and offset.
    checkBoxGroupLayoutAlgorithm->Measure(&layoutWrapper);
    checkBoxGroupLayoutAlgorithm->Layout(&layoutWrapper);
    // Test the default size set in theme and the offset.
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxGroupTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxGroupTheme);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(),
        SizeF(checkBoxGroupTheme->GetHeight().ConvertToPx(), checkBoxGroupTheme->GetWidth().ConvertToPx()));
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameOffset(), OffsetF(0.0, 0.0));
    /**
    //     corresponding ets code:
    //         CheckBoxGroup({ name: 'CheckBoxGroup', group: 'CheckBoxGroupGroup' }).width(50).height(50)
    */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    checkBoxGroupLayoutAlgorithm->Measure(&layoutWrapper);
    // Test the size set by codes.
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
}

} // namespace OHOS::Ace::NG