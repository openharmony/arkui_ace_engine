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

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_accessibility_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

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
const NG::PaddingProperty newArgs = NG::PaddingProperty();
const bool SELECTED = true;
const Color SELECTED_COLOR = Color::BLUE;
const Color BOARD_COLOR = Color::BLUE;
const Color CHECK_COLOR = Color::WHITE;
const Color BORDER_COLOR = Color::GRAY;
const Color SHADOW_COLOR = Color::BLUE;
const Color UNSELECTED_COLOR = Color::RED;
const Color CHECK_MARK_COLOR = Color::GREEN;
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
constexpr Dimension CHECK_MARK_SIZE = Dimension(10.0);
constexpr Dimension CHECK_MARK_SIZE_INCORRECT_VALUE = Dimension(-1.0);
constexpr Dimension CHECK_MARK_WIDTH = Dimension(5.0);
const bool SELECT_STATE = true;
RefPtr<PipelineContext> pipeline = nullptr;
} // namespace

class CheckBoxTestNG : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void CheckBoxTestNG::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));

    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineBase::GetCurrent()->stageManager_ = stageManager;
}

void CheckBoxTestNG::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: CheckBoxPaintPropertyTest001
 * @tc.desc: Set CheckBox value into CheckBoxPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    bool flag = false;

    /**
     * @tc.steps: step2. Set parameters to CheckBox property
     */
    checkBoxModelNG.SetSelect(SELECTED);
    checkBoxModelNG.SetSelectedColor(SELECTED_COLOR);
    checkBoxModelNG.SetWidth(WIDTH);
    checkBoxModelNG.SetHeight(HEIGHT);
    checkBoxModelNG.SetPadding(PADDING, newArgs, flag);

    /**
     * @tc.steps: step3. Get paint property and get CheckBox property
     * @tc.expected: Check the CheckBox property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelect(), SELECTED);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelectedColor(), SELECTED_COLOR);
}

/**
 * @tc.name: CheckBoxPaintPropertyTest002
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPaintPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    bool flag = false;

    /**
     * @tc.steps: step2. Set parameters to CheckBox property
     */
    checkBoxModelNG.SetSelect(SELECTED);
    checkBoxModelNG.SetSelectedColor(SELECTED_COLOR);
    checkBoxModelNG.SetWidth(WIDTH);
    checkBoxModelNG.SetHeight(HEIGHT);
    checkBoxModelNG.SetPadding(PADDING, newArgs, flag);

    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the CheckBox property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    auto json = JsonUtil::Create(true);
    checkBoxPaintProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("isOn"), "true");
}

/**
 * @tc.name: CheckBoxEventHubPropertyTest002
 * @tc.desc: Set CheckBox value into CheckBoxEventHub and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxEventHubPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Get CheckBox event hub and get property
     * @tc.expected: Check the CheckBox property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->GetName(), NAME);
    EXPECT_EQ(eventHub->GetGroupName(), GROUP_NAME);
}

/**
 * @tc.name: CheckBoxEventTest003
 * @tc.desc: Test CheckBox onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Init change result and onChange function
     */
    bool isSelected = false;
    auto onChange = [&isSelected](bool select) { isSelected = select; };
    checkBoxModelNG.SetOnChange(onChange);

    /**
     * @tc.steps: step3. Get event hub and call UpdateChangeEvent function
     * @tc.expected: Check the event result value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(isSelected, true);
}

/**
 * @tc.name: CheckBoxPatternTest004
 * @tc.desc: Test CheckBox onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Test CheckBox onModifyDone method
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetPreGroup(GROUP_NAME);
    frameNode->MarkModifyDone();
    pattern->SetPreGroup(GROUP_NAME_CHANGE);
    frameNode->MarkModifyDone();
}

/**
 * @tc.name: CheckBoxMeasureTest005
 * @tc.desc: Test CheckBox Measure.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxMeasureTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set checkBoxLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto checkBoxPattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxLayoutAlgorithm = checkBoxPattern->CreateLayoutAlgorithm();
    ASSERT_NE(checkBoxLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(checkBoxLayoutAlgorithm));

    /**
     * @tc.steps: step3. Test CheckBox Measure method
     * @tc.expected: Check the CheckBox frame size and frame offset value
     */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    checkBoxLayoutAlgorithm->Measure(&layoutWrapper);
    // Test the size set by codes.
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: CheckBoxPatternTest006
 * @tc.desc: Test CheckBox pattern method OnTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Get CheckBox pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBox pattern variable and call OnTouchUp
     * @tc.expected: Check the CheckBox pattern value
     */
    pattern->isTouch_ = true;
    pattern->isHover_ = false;
    pattern->OnTouchUp();
    EXPECT_EQ(pattern->isTouch_, false);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::NONE);
    pattern->isHover_ = true;
    pattern->OnTouchUp();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::PRESS_TO_HOVER);
}

/**
 * @tc.name: CheckBoxPatternTest007
 * @tc.desc: Test CheckBox pattern method OnTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Get CheckBox pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBox pattern variable and call OnTouchDown
     * @tc.expected: Check the CheckBox pattern value
     */
    pattern->isTouch_ = false;
    pattern->isHover_ = false;
    pattern->OnTouchDown();
    EXPECT_EQ(pattern->isTouch_, true);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::PRESS);
    pattern->isHover_ = true;
    pattern->OnTouchDown();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::HOVER_TO_PRESS);
}

/**
 * @tc.name: CheckBoxPatternTest008
 * @tc.desc: Test CheckBox pattern method OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Get CheckBox pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBox paint property variable and call OnClick
     * @tc.expected: Check the CheckBox paint property value
     */
    pattern->OnClick();
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    auto select1 = checkBoxPaintProperty->GetCheckBoxSelectValue();
    EXPECT_EQ(select1, true);
    pattern->OnClick();
    auto select2 = checkBoxPaintProperty->GetCheckBoxSelectValue();
    EXPECT_EQ(select2, false);
}

/**
 * @tc.name: CheckBoxPatternTest009
 * @tc.desc: Test CheckBox pattern method HandleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Get CheckBox pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBox pattern variable and call HandleMouseEvent
     * @tc.expected: Check the CheckBox pattern value
     */
    pattern->isTouch_ = true;
    pattern->isHover_ = false;
    pattern->HandleMouseEvent(true);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::HOVER);
    EXPECT_EQ(pattern->isTouch_, true);
    pattern->HandleMouseEvent(false);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::NONE);
}

/**
 * @tc.name: CheckBoxPatternTest010
 * @tc.desc: Test CheckBox pattern Init methods.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Get CheckBox pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBox pattern variable and call Init methods
     * @tc.expected: Check the CheckBox pattern value
     */
    // InitMouseEvent()
    pattern->InitMouseEvent();
    ASSERT_NE(pattern->mouseEvent_, nullptr);
    pattern->InitMouseEvent();
    pattern->mouseEvent_->GetOnHoverEventFunc()(true);
    // InitTouchEvent()
    pattern->InitTouchEvent();
    ASSERT_NE(pattern->touchListener_, nullptr);
    pattern->InitTouchEvent();
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    pattern->touchListener_->GetTouchEventCallback()(info);
    TouchLocationInfo touchInfo2(2);
    touchInfo2.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(touchInfo2));
    pattern->touchListener_->GetTouchEventCallback()(info);
    TouchLocationInfo touchInfo3(3);
    touchInfo2.SetTouchType(TouchType::CANCEL);
    info.AddTouchLocationInfo(std::move(touchInfo3));
    pattern->touchListener_->GetTouchEventCallback()(info);
    // InitClickEvent()
    pattern->InitClickEvent();
    ASSERT_NE(pattern->clickListener_, nullptr);
    pattern->InitClickEvent();
}

/**
 * @tc.name: CheckBoxPatternTest011
 * @tc.desc: Test CheckBox pattern Update methods.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Get CheckBox pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBox pattern variable and call Init methods
     * @tc.expected: Check the CheckBox pattern value
     */
    // UpdateUIStatus(bool check)
    pattern->uiStatus_ = UIStatus::ON_TO_OFF;
    pattern->UpdateUIStatus(true);
    EXPECT_EQ(pattern->uiStatus_, UIStatus::OFF_TO_ON);
    // UpdateUnSelect()
    pattern->uiStatus_ = UIStatus::ON_TO_OFF;
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    pattern->UpdateUnSelect();
    EXPECT_EQ(pattern->uiStatus_, UIStatus::ON_TO_OFF);
    checkBoxPaintProperty->UpdateCheckBoxSelect(false);
    pattern->UpdateUnSelect();
    EXPECT_EQ(pattern->uiStatus_, UIStatus::UNSELECTED);
}

/**
 * @tc.name: CheckBoxEventHubPropertyTest012
 * @tc.desc: Set CheckBox value into CheckBoxEventHub and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxEventHubPropertyTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, std::nullopt, TAG);

    /**
     * @tc.steps: step2. Get CheckBox event hub and get property
     * @tc.expected: Check the CheckBox property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->GetName(), NAME);
    EXPECT_EQ(eventHub->GetGroupName(), "");
}

/**
 * @tc.name: CheckBoxEventHubPropertyTest013
 * @tc.desc: Set CheckBox value into CheckBoxEventHub and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxEventHubPropertyTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(std::nullopt, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Get CheckBox event hub and get property
     * @tc.expected: Check the CheckBox property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->GetName(), "");
    EXPECT_EQ(eventHub->GetGroupName(), GROUP_NAME);
}

/**
 * @tc.name: CheckBoxPatternTest014
 * @tc.desc: Test CheckBox onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest014, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto checkboxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkboxTheme));
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetPreGroup(GROUP_NAME);
    frameNode->MarkModifyDone();
    pattern->SetPreGroup(GROUP_NAME_CHANGE);
    frameNode->MarkModifyDone();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest015
 * @tc.desc: Test UpdateAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest015, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    checkBoxModelNG.SetSelect(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest016
 * @tc.desc: Test UpdateAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest016, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    checkBoxModelNG.SetSelect(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest017
 * @tc.desc: Test UpdateCheckBoxGroupStatus.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest017, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG1;
    checkBoxModelNG1.Create(NAME, GROUP_NAME, TAG);
    auto frameNode1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode1, nullptr);
    auto pattern1 = frameNode1->GetPattern<CheckBoxPattern>();
    EXPECT_NE(pattern1, nullptr);
    CheckBoxModelNG checkBoxModelNG2;
    checkBoxModelNG2.Create(NAME, GROUP_NAME, TAG);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode2, nullptr);
    CheckBoxModelNG checkBoxModelNG3;
    checkBoxModelNG3.Create(NAME, GROUP_NAME, TAG);
    auto frameNode3 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode3, nullptr);
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    auto groupFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(groupFrameNode, nullptr);

    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>> checkBoxGroupMap;
    checkBoxGroupMap[GROUP_NAME].push_back(frameNode1);
    checkBoxGroupMap[GROUP_NAME].push_back(frameNode2);
    checkBoxGroupMap[GROUP_NAME].push_back(frameNode3);
    checkBoxGroupMap[GROUP_NAME].push_back(groupFrameNode);
    bool isSelected = true;
    pattern1->UpdateCheckBoxGroupStatus(frameNode1, checkBoxGroupMap, isSelected);
    auto checkBoxPaintProperty1 = frameNode1->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(checkBoxPaintProperty1, nullptr);
    checkBoxPaintProperty1->UpdateCheckBoxSelect(true);
    auto checkBoxPaintProperty2 = frameNode2->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(checkBoxPaintProperty2, nullptr);
    checkBoxPaintProperty2->UpdateCheckBoxSelect(false);
    pattern1->UpdateCheckBoxGroupStatus(frameNode1, checkBoxGroupMap, isSelected);
    isSelected = false;
    pattern1->UpdateCheckBoxGroupStatus(frameNode1, checkBoxGroupMap, isSelected);
    checkBoxPaintProperty2->UpdateCheckBoxSelect(true);
    auto checkBoxPaintProperty3 = frameNode3->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(checkBoxPaintProperty3, nullptr);
    checkBoxPaintProperty3->UpdateCheckBoxSelect(true);
    isSelected = true;
    pattern1->UpdateCheckBoxGroupStatus(frameNode1, checkBoxGroupMap, isSelected);
}

/**
 * @tc.name: CheckBoxPatternTest018
 * @tc.desc: Test CheckBoxGroupIsTrue.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest018, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG1;
    checkBoxModelNG1.Create(NAME, GROUP_NAME, TAG);
    auto frameNode1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode1, nullptr);
    auto pattern1 = frameNode1->GetPattern<CheckBoxPattern>();
    EXPECT_NE(pattern1, nullptr);
    pattern1->CheckBoxGroupIsTrue();
}

/**
 * @tc.name: CheckBoxPatternTest019
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest019, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<EventHub> eventHub = AccessibilityManager::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AccessibilityManager::MakeRefPtr<FocusHub>(eventHub, FocusType::DISABLE, false);
    pattern->InitOnKeyEvent(focusHub);
    RoundRect paintRect;
    pattern->GetInnerFocusPaintRect(paintRect);
}

/**
 * @tc.name: CheckBoxPatternTest020
 * @tc.desc: Set unSelectedColor into CheckBoxPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest020, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    checkBoxModelNG.SetUnSelectedColor(UNSELECTED_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxUnSelectedColor(), UNSELECTED_COLOR);
}

/**
 * @tc.name: CheckBoxPatternTest021
 * @tc.desc: Set checkMarkColor into CheckBoxPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest021, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    checkBoxModelNG.SetCheckMarkColor(CHECK_MARK_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxCheckMarkColor(), CHECK_MARK_COLOR);
}

/**
 * @tc.name: CheckBoxPatternTest022
 * @tc.desc: Set checkMarkSize into CheckBoxPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest022, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    checkBoxModelNG.SetCheckMarkSize(CHECK_MARK_SIZE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxCheckMarkSize(), CHECK_MARK_SIZE);
}

/**
 * @tc.name: CheckBoxPatternTest023
 * @tc.desc: Set checkMarkWidth into CheckBoxPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest023, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    checkBoxModelNG.SetCheckMarkWidth(CHECK_MARK_WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxCheckMarkWidth(), CHECK_MARK_WIDTH);
}

/**
 * @tc.name: CheckBoxMeasureTest024
 * @tc.desc: Test CheckBox MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxMeasureTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set checkBoxLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto checkBoxPattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxLayoutAlgorithm =
        AceType::DynamicCast<CheckBoxLayoutAlgorithm>(checkBoxPattern->CreateLayoutAlgorithm());
    ASSERT_NE(checkBoxLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(checkBoxLayoutAlgorithm));

    /**
     * @tc.steps: step3. Test CheckBox Measure method
     * @tc.expected: Check the CheckBox frame size and frame offset value
     */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto size = checkBoxLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    // Test the size set by codes.
    EXPECT_EQ(size, SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    /**
     * Only set width
     */
    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetWidth(WIDTH.ConvertToPx());
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize2);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto size2 = checkBoxLayoutAlgorithm->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_EQ(size2->Width(), WIDTH.ConvertToPx());
    /**
     * Only set height
     */
    LayoutConstraintF layoutConstraintSize3;
    layoutConstraintSize3.selfIdealSize.SetHeight(HEIGHT.ConvertToPx());
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize3);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto size3 = checkBoxLayoutAlgorithm->MeasureContent(layoutConstraintSize3, &layoutWrapper);
    EXPECT_EQ(size3->Height(), HEIGHT.ConvertToPx());
    /**
     * Do not set width and height
     */
    LayoutConstraintF layoutConstraintSize4;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize4);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    checkBoxLayoutAlgorithm->MeasureContent(layoutConstraintSize4, &layoutWrapper);
}

/**
 * @tc.name: CheckBoxPatternTest025
 * @tc.desc: Test CheckBox OnModifyDone default margin.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest025, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto checkBoxPattern = frameNode->GetPattern<CheckBoxPattern>();
    EXPECT_NE(checkBoxPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));

    MarginProperty margin;
    margin.left = CalcLength(CHECK_MARK_SIZE.ConvertToPx());
    layoutProperty->UpdateMargin(margin); // GetMarginProperty

    checkBoxPattern->OnModifyDone();
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(CHECK_MARK_SIZE.ConvertToPx()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(),
        CalcLength(checkBoxTheme->GetHotZoneHorizontalPadding().Value()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->top.value(),
        CalcLength(checkBoxTheme->GetHotZoneVerticalPadding().Value()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->bottom.value(),
        CalcLength(checkBoxTheme->GetHotZoneVerticalPadding().Value()));

    MarginProperty margin1;
    margin1.right = CalcLength(CHECK_MARK_SIZE.ConvertToPx());
    layoutProperty->UpdateMargin(margin1); // GetMarginProperty

    checkBoxPattern->OnModifyDone();
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(),
        CalcLength(checkBoxTheme->GetHotZoneHorizontalPadding().Value()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(CHECK_MARK_SIZE.ConvertToPx()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->top.value(),
        CalcLength(checkBoxTheme->GetHotZoneVerticalPadding().Value()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->bottom.value(),
        CalcLength(checkBoxTheme->GetHotZoneVerticalPadding().Value()));
}

/**
 * @tc.name: CheckBoxPatternTest026
 * @tc.desc: Test CheckBox click event callback.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest026, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    /**
     * fire click event
     */
    gesture->ActClick();
}

/**
 * @tc.name: CheckBoxPatternTest027
 * @tc.desc: Test CheckBox AddHotZoneRect RemoveLastHotZoneRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest027, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    OffsetF offsetF(0.0f, 0.0f);
    SizeF sizeF(80.0f, 20.0f);
    geometryNode->SetContentOffset(offsetF);
    geometryNode->SetContentSize(sizeF);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<CheckBoxLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    bool result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(result);
    /**
     * cover method AddHotZoneRect
     */
    pattern->AddHotZoneRect();
    EXPECT_EQ(pattern->hotZoneOffset_.GetX(), 0.0f);
    EXPECT_EQ(pattern->hotZoneSize_.Width(), 80.0f);
    /**
     * cover method RemoveLastHotZoneRect
     */
    int count = frameNode->GetOrCreateGestureEventHub()->responseRegion_.size();
    for (size_t i = 0; i < count; i++) {
        pattern->RemoveLastHotZoneRect();
    }
    EXPECT_EQ(frameNode->GetOrCreateGestureEventHub()->isResponseRegion_, false);
}

/**
 * @tc.name: CheckBoxPatternTest028
 * @tc.desc: Test CheckBox InitOnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest028, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    /**
     * test event.action != KeyAction::DOWN
     */
    KeyEvent keyEventOne(KeyCode::KEY_A, KeyAction::UP);
    eventHub->ProcessOnKeyEventInternal(keyEventOne);
    /**
     * test event.action == KeyAction::DOWN and event.code != KeyCode::KEY_ENTER
     */
    KeyEvent keyEventTwo(KeyCode::KEY_A, KeyAction::DOWN);
    eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    /**
     * test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_ENTER
     */
    KeyEvent keyEventThr(KeyCode::KEY_ENTER, KeyAction::DOWN);
    eventHub->ProcessOnKeyEventInternal(keyEventThr);
}

/**
 * @tc.name: CheckBoxPatternTest029
 * @tc.desc: Test CheckBox GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest029, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
}

/**
 * @tc.name: CheckBoxPatternTest030
 * @tc.desc: Test CheckBox onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Test CheckBox onModifyDone method
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxSelect(SELECT_STATE);
    pattern->SetPreGroup(GROUP_NAME);
    frameNode->MarkModifyDone();
    pattern->SetPreGroup(GROUP_NAME_CHANGE);
    frameNode->MarkModifyDone();
}

/**
 * @tc.name: CheckBoxPaintMethodTest001
 * @tc.desc: Test CheckBox PaintMethod PaintCheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPaintMethodTest001, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    /**
     * @tc.case: case. CheckBoxPaintMethod's PaintCheckBox will be called.
     */
    auto checkBoxModifier =
        AceType::MakeRefPtr<CheckBoxModifier>(false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR);
    CheckBoxPaintMethod checkBoxPaintMethod(checkBoxModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(3);
    checkBoxPaintMethod.checkboxModifier_->PaintCheckBox(canvas, CONTENT_OFFSET, CONTENT_SIZE);
    /**
     * @tc.case: case. CheckBoxPaintMethod's PaintCheckBox code when !enabled_->Get()
     */
    checkBoxPaintMethod.checkboxModifier_->enabled_->Set(false);
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(3);
    checkBoxPaintMethod.checkboxModifier_->PaintCheckBox(canvas, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxPaintMethodTest002
 * @tc.desc: Test checkbox method UpdateContentModifier will update value into modifier.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPaintMethodTest002, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);

    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    if (checkBoxPaintProperty) {
        checkBoxPaintProperty->UpdateCheckBoxSelect(SELECT_STATE);
        checkBoxPaintProperty->UpdateCheckBoxSelectedColor(SELECTED_COLOR);
        checkBoxPaintProperty->UpdateCheckBoxUnSelectedColor(UNSELECTED_COLOR);
        checkBoxPaintProperty->UpdateCheckBoxCheckMarkColor(CHECK_MARK_COLOR);
        checkBoxPaintProperty->UpdateCheckBoxCheckMarkSize(CHECK_MARK_SIZE);
        checkBoxPaintProperty->UpdateCheckBoxCheckMarkWidth(CHECK_MARK_WIDTH);
    }

    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    auto checkboxModifier =
        AceType::MakeRefPtr<CheckBoxModifier>(false, Color::BLUE, Color::BLACK, Color::BLACK, Color::GRAY);
    ASSERT_NE(checkboxModifier, nullptr);
    CheckBoxPaintMethod checkBoxPaintMethod(checkboxModifier);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(checkBoxPaintMethod.checkboxModifier_->isSelect_->Get(), SELECT_STATE);
    EXPECT_EQ(checkBoxPaintMethod.checkboxModifier_->userActiveColor_, SELECTED_COLOR);
    EXPECT_EQ(checkBoxPaintMethod.checkboxModifier_->inactiveColor_, UNSELECTED_COLOR);
    EXPECT_EQ(checkBoxPaintMethod.checkboxModifier_->pointColor_, CHECK_MARK_COLOR);
    EXPECT_EQ(
        checkBoxPaintMethod.checkboxModifier_->strokeSize_->Get(), static_cast<float>(CHECK_MARK_SIZE.ConvertToPx()));
    auto checkStroke = static_cast<float>(CHECK_MARK_SIZE.ConvertToPx() * 0.25);
    EXPECT_EQ(checkBoxPaintMethod.checkboxModifier_->checkStroke_->Get(), checkStroke);
}

/**
 * @tc.name: CheckBoxPaintMethodTest003
 * @tc.desc: Test checkbox method UpdateContentModifier will update incorrect value into modifier.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPaintMethodTest003, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);

    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    if (checkBoxPaintProperty) {
        checkBoxPaintProperty->UpdateCheckBoxCheckMarkSize(CHECK_MARK_SIZE_INCORRECT_VALUE);
    }

    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    auto checkboxModifier =
        AceType::MakeRefPtr<CheckBoxModifier>(false, Color::BLUE, Color::BLACK, Color::BLACK, Color::GRAY);
    ASSERT_NE(checkboxModifier, nullptr);
    CheckBoxPaintMethod checkBoxPaintMethod(checkboxModifier);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(checkBoxPaintMethod.checkboxModifier_->strokeSize_->Get(), static_cast<float>(CONTENT_SIZE.Width()));
}

/**
 * @tc.name: CheckBoxPaintMethodTest004
 * @tc.desc: Test CheckBox PaintMethod PaintCheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPaintMethodTest004, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    /**
     * @tc.case: case. CheckBoxPaintMethod's PaintCheckBox will be called.
     */
    auto checkBoxModifier =
        AceType::MakeRefPtr<CheckBoxModifier>(false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR);
    checkBoxModifier->SetStrokeSize(10);
    CheckBoxPaintMethod checkBoxPaintMethod(checkBoxModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(3);
    checkBoxPaintMethod.checkboxModifier_->PaintCheckBox(canvas, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxPaintMethodTest005
 * @tc.desc: Test CheckBox UpdateAnimatableProperty and SetBoardColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPaintMethodTest005, TestSize.Level1)
{
    auto checkboxModifier =
        AceType::MakeRefPtr<CheckBoxModifier>(false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR);
    checkboxModifier->hoverColor_ = Color::RED;
    checkboxModifier->clickEffectColor_ = Color::BLUE;
    checkboxModifier->touchHoverType_ = TouchHoverAnimationType::HOVER;
    checkboxModifier->UpdateAnimatableProperty();
    checkboxModifier->animateTouchHoverColor_ =
        AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    checkboxModifier->touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    checkboxModifier->UpdateAnimatableProperty();
    EXPECT_EQ(checkboxModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED));
    checkboxModifier->touchHoverType_ = TouchHoverAnimationType::NONE;
    checkboxModifier->UpdateAnimatableProperty();
    EXPECT_EQ(checkboxModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED.BlendOpacity(0)));
    checkboxModifier->touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    checkboxModifier->UpdateAnimatableProperty();
    EXPECT_EQ(checkboxModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
    checkboxModifier->touchHoverType_ = TouchHoverAnimationType::PRESS;
    checkboxModifier->UpdateAnimatableProperty();
    EXPECT_EQ(checkboxModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
}

/**
 * @tc.name: CheckBoxAccessibilityPropertyTestNg001
 * @tc.desc: Test the IsCheckable property of CheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxAccessibilityPropertyTestNg001, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<CheckBoxAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->IsCheckable());
}

/**
 * @tc.name: CheckBoxAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsChecked property of CheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxAccessibilityPropertyTestNg002, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateCheckBoxSelect(true);

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<CheckBoxAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->IsChecked());

    paintProperty->UpdateCheckBoxSelect(false);
    EXPECT_FALSE(accessibilityProperty->IsChecked());
}

/**
 * @tc.name: CheckBoxAccessibilityPropertyTestNg003
 * @tc.desc: Test the GetText property of CheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxAccessibilityPropertyTestNg003, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<CheckBoxAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), NAME);
}

/**
 * @tc.name: CheckBoxUpdateChangeEventTest001
 * @tc.desc: Test CheckBox onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxUpdateChangeEventTest001, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    bool isSelected = false;
    auto changeEvent = [&isSelected](bool select) { isSelected = select; };
    checkBoxModelNG.SetChangeEvent(changeEvent);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(isSelected, true);
}

/**
 * @tc.name: CheckBoxPatternTest031
 * @tc.desc: cover CheckBoxGroupIsTrue.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(1);
    CheckBoxModelNG checkBoxModelNG1;
    checkBoxModelNG1.Create(NAME, GROUP_NAME, TAG);
    auto frameNode1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode1, nullptr);
    auto pattern1 = frameNode1->GetPattern<CheckBoxPattern>();
    EXPECT_NE(pattern1, nullptr);
    auto paintProperty = frameNode1->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    paintProperty->UpdateCheckBoxSelect(true);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(2);
    CheckBoxModelNG checkBoxModelNG2;
    checkBoxModelNG2.Create(NAME, GROUP_NAME, TAG);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode2, nullptr);
    auto paintProperty2 = frameNode2->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(paintProperty2, nullptr);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(3);
    CheckBoxModelNG checkBoxModelNG3;
    checkBoxModelNG3.Create(NAME, GROUP_NAME, TAG);
    auto frameNode3 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode3, nullptr);
    auto paintProperty3 = frameNode3->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(paintProperty3, nullptr);
    /**
     * @tc.steps: step2. Init CheckBoxGroup node
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(4);
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    auto groupFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(groupFrameNode, nullptr);
    auto groupPaintProperty = groupFrameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    EXPECT_NE(groupPaintProperty, nullptr);

    pattern1->CheckBoxGroupIsTrue();
    /**
     * cover branch groupPaintProperty->GetIsCheckBoxCallbackDealed()
     */
    pattern1->CheckBoxGroupIsTrue();
    /**
     * test branch allSelectIsNull and no CheckBoxGroupSelect
     */
    paintProperty->ResetCheckBoxSelect();
    paintProperty2->ResetCheckBoxSelect();
    paintProperty3->ResetCheckBoxSelect();
    groupPaintProperty->isCheckBoxCallbackDealed_ = false;
    pattern1->CheckBoxGroupIsTrue();
    /**
     * test branch allSelectIsNull
     */
    paintProperty->ResetCheckBoxSelect();
    paintProperty2->ResetCheckBoxSelect();
    paintProperty3->ResetCheckBoxSelect();
    groupPaintProperty->UpdateCheckBoxGroupSelect(true);
    groupPaintProperty->isCheckBoxCallbackDealed_ = false;
    pattern1->CheckBoxGroupIsTrue();
}

/**
 * @tc.name: CheckBoxPatternTest032
 * @tc.desc: cover pipelineContext BuildFinishCallBack.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    /**
     * @tc.steps: step2. use method FlushBuildFinishCallbacks to callback.
     */
    MockPipelineBase::GetCurrent()->FlushBuildFinishCallbacks();
}

/**
 * @tc.name: CheckBoxPaintMethodTest006
 * @tc.desc: Test CheckBox PaintMethod DrawCheck.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPaintMethodTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    /**
     * @tc.steps: step2. use DrawCheck to draw checkbox.
     * @tc.expected: DrawCheck successfully.
     */
    auto checkBoxModifier =
        AceType::MakeRefPtr<CheckBoxModifier>(false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR);
    CheckBoxPaintMethod checkBoxPaintMethod(checkBoxModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    RSPen pen;
    RSPen shadowPen = RSPen(pen);
    checkBoxPaintMethod.checkboxModifier_->checkStroke_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(2.0f);
    checkBoxPaintMethod.checkboxModifier_->strokeSize_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(2.0f);
    checkBoxPaintMethod.checkboxModifier_->DrawCheck(canvas, CONTENT_OFFSET, pen, shadowPen, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxPatternTest033
 * @tc.desc: Test the distributed capability of CheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get pattern .
     * @tc.expected: function ProvideRestoreInfo is called.
     */
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto checkBoxPaintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxSelect(true);
    std::string ret = pattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"isOn":true})");

    /**
     * @tc.steps: step3. function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"isOn":true})";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_TRUE(checkBoxPaintProperty->GetCheckBoxSelectValue(false));
    restoreInfo_ = "invalid_json_string";
    pattern->OnRestoreInfo(restoreInfo_);
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_TRUE(checkBoxPaintProperty->GetCheckBoxSelectValue(false));
}
} // namespace OHOS::Ace::NG
