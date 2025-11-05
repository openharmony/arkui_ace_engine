/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/checkbox/checkbox_accessibility_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
using CheckboxBuilderFunc = std::optional<std::function<void()>>;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
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
const SizeF CONTENT_SIZE2 = SizeF(-7000.0, 400.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
constexpr Dimension CHECK_MARK_SIZE = Dimension(10.0);
constexpr Dimension CHECK_MARK_SIZE_INCORRECT_VALUE = Dimension(-1.0);
constexpr Dimension CHECK_MARK_WIDTH = Dimension(5.0);
constexpr int32_t MIRROR_FRAME_OFFSET_Y_ZERO = 0;
const bool SELECT_STATE = true;
RefPtr<PipelineContext> pipeline = nullptr;
const SizeF TEST_SIZE_0 = SizeF(0.0f, 0.0f);
const SizeF TEST_SIZE_100_200 = SizeF(100.0f, 200.0f);
const SizeF TEST_SIZE_100 = SizeF(100.0f, 100.0f);
const SizeF TEST_SIZE_200 = SizeF(200.0f, 200.0f);
const SizeF TEST_SIZE_50 = SizeF(50.0f, 50.0f);
const SizeF TEST_SIZE_60 = SizeF(60.0f, 60.0f);
} // namespace

class CheckBoxTestNG : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    CheckboxBuilderFunc CheckboxBuilder();
};

void CheckBoxTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));

    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void CheckBoxTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

CheckboxBuilderFunc CheckBoxTestNG::CheckboxBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
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
    checkBoxPaintProperty->ToJsonValue(json, filter);
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
     * @tc.steps: step2. Create LayoutWrapperNode and set checkBoxLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
    /*
     * @tc.steps: step1. create stageManager.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<CheckBoxPattern>());
    auto pageNode = AceType::MakeRefPtr<FrameNode>("STAGE", 0, AceType::MakeRefPtr<CheckBoxPattern>());
    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    pageNode->eventHub_ = pageEventHub;
    stageNode->AddChild(pageNode);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    pipelineContext->stageManager_ = stageManager;

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

    groupManager->AddCheckBoxToGroup(GROUP_NAME, frameNode1);
    groupManager->AddCheckBoxToGroup(GROUP_NAME, frameNode2);
    groupManager->AddCheckBoxToGroup(GROUP_NAME, frameNode3);
    groupManager->AddCheckBoxToGroup(GROUP_NAME, nullptr);
    groupManager->AddCheckBoxGroup(GROUP_NAME, groupFrameNode);

    auto list = groupManager->GetCheckboxList(GROUP_NAME);
    pattern1->UpdateCheckBoxGroupStatus(frameNode1, list);
    auto checkBoxPaintProperty1 = frameNode1->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(checkBoxPaintProperty1, nullptr);
    checkBoxPaintProperty1->UpdateCheckBoxSelect(true);
    auto checkBoxPaintProperty2 = frameNode2->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(checkBoxPaintProperty2, nullptr);
    checkBoxPaintProperty2->UpdateCheckBoxSelect(false);
    pattern1->UpdateCheckBoxGroupStatus(frameNode1, list);
    checkBoxPaintProperty2->UpdateCheckBoxSelect(true);
    auto checkBoxPaintProperty3 = frameNode3->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(checkBoxPaintProperty3, nullptr);
    checkBoxPaintProperty3->UpdateCheckBoxSelect(true);
    pattern1->UpdateCheckBoxGroupStatus(frameNode1, list);
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
    auto frameNode1 =ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<EventHub> eventHub = AccessibilityManager::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AccessibilityManager::MakeRefPtr<FocusHub>(
        AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(eventHub)), FocusType::DISABLE, false);
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
     * @tc.steps: step2. Create LayoutWrapperNode and set checkBoxLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
     * Only set width.
     */
    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetWidth(WIDTH.ConvertToPx());
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize2);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto size2 = checkBoxLayoutAlgorithm->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_EQ(size2->Width(), WIDTH.ConvertToPx());
    /**
     * Only set height.
     */
    LayoutConstraintF layoutConstraintSize3;
    layoutConstraintSize3.selfIdealSize.SetHeight(HEIGHT.ConvertToPx());
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize3);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto size3 = checkBoxLayoutAlgorithm->MeasureContent(layoutConstraintSize3, &layoutWrapper);
    EXPECT_EQ(size3->Height(), HEIGHT.ConvertToPx());
    /**
     * Do not set width and height.
     */
    LayoutConstraintF layoutConstraintSize4;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize4);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    checkBoxLayoutAlgorithm->MeasureContent(layoutConstraintSize4, &layoutWrapper);

    /**
     *  Set Border.
     */
    LayoutConstraintF layoutConstraintSize5;
    layoutConstraintSize5.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    BorderWidthProperty borderWidth = { 1.0_vp, 1.0_vp, 1.0_vp, 1.0_vp };
    layoutWrapper.GetLayoutProperty()->UpdateBorderWidth(borderWidth);
    auto size5 = checkBoxLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    // Test the size set by codes.
    EXPECT_EQ(size5, SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkBoxTheme));

    MarginProperty margin;
    margin.left = CalcLength(CHECK_MARK_SIZE.ConvertToPx());
    layoutProperty->UpdateMargin(margin); // GetMarginProperty

    checkBoxPattern->OnModifyDone();
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->FlushBuildFinishCallbacks();
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
    pipeline->FlushBuildFinishCallbacks();
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

    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
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
 * @tc.name: CheckBoxLayoutTest031
 * @tc.desc: Test CheckBox Layout.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxLayoutTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode and set checkBoxLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto checkBoxPattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxLayoutAlgorithm = checkBoxPattern->CreateLayoutAlgorithm();
    ASSERT_NE(checkBoxLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(checkBoxLayoutAlgorithm));

    /**
     * @tc.steps: step3. Test CheckBox Layout method
     * @tc.expected: Check the CheckBox frame offset value
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    checkBoxLayoutAlgorithm->Layout(&layoutWrapper);
    auto offsetVal = frameNode->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(offsetVal.GetY(), MIRROR_FRAME_OFFSET_Y_ZERO);
}

/**
 * @tc.name: CheckBoxLayoutTest032
 * @tc.desc: Test CheckBox pattern Init methods.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxLayoutTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Test CheckBox CheckBoxPattern::CreateNodePaintMethod method
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. Get paint property and get CheckBox property
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    /**
     * @tc.steps: step4. update parameters to CheckBox property
     */
    checkBoxPaintProperty->UpdateCheckBoxSelectedStyle(CheckBoxStyle::CIRCULAR_STYLE);
    /**
     * @tc.expected: Check the CheckBox property value
     */
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelectedStyleValue(), CheckBoxStyle::CIRCULAR_STYLE);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.case: case. CheckBoxPattern's CreateNodePaintMethod will be called.
     */
    auto paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_EQ(frameNode->GetCheckboxFlag(), true);
    EXPECT_NE(checkBoxPaintProperty->GetHost(), nullptr);
    EXPECT_NE(paintMethod, nullptr);
    /**
     * @tc.steps: step5. Set CheckBox pattern variable and call Init methods
     * @tc.expected: Check the CheckBox pattern value
     */
    pattern->InitFocusEvent();
    EXPECT_EQ(pattern->focusEventInitialized_, true);
    pattern->HandleFocusEvent();

    EXPECT_EQ(pattern->focusEventInitialized_, true);
    pattern->HandleBlurEvent();
}

/**
 * @tc.name: CheckBoxLayoutTest033
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxLayoutTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    /**
     * @tc.steps: step2. Test CheckBox CheckBoxPattern::CreateNodePaintMethod method
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. Get paint property and get CheckBox property
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    /**
     * @tc.steps: step4. update parameters to CheckBox property
     */
    checkBoxPaintProperty->UpdateCheckBoxSelectedStyle(CheckBoxStyle::CIRCULAR_STYLE);
    /**
     * @tc.expected: Check the CheckBox property value
     */
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelectedStyleValue(), CheckBoxStyle::CIRCULAR_STYLE);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    RefPtr<EventHub> eventHub = AccessibilityManager::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AccessibilityManager::MakeRefPtr<FocusHub>(AccessibilityManager::WeakClaim(
        AccessibilityManager::RawPtr(eventHub)), FocusType::DISABLE, false);
    pattern->InitOnKeyEvent(focusHub);
    RoundRect paintRect;
    /**
     * @tc.steps: step5. Check the IsSquareStyleBox when CIRCULAR_STYLE
     */
    ASSERT_NE(pattern, nullptr);
    pattern->GetInnerFocusPaintRect(paintRect);
    EXPECT_EQ(pattern->IsSquareStyleBox(), false);
    /**
     * @tc.steps: step6. Check the IsSquareStyleBox when SQUARE_STYLE
     */
    checkBoxPaintProperty->UpdateCheckBoxSelectedStyle(CheckBoxStyle::SQUARE_STYLE);
    pattern->GetInnerFocusPaintRect(paintRect);
    EXPECT_EQ(pattern->IsSquareStyleBox(), true);
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
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR, SizeF(), OffsetF(), 0.0, 0.0);
    CheckBoxPaintMethod checkBoxPaintMethod;
    checkBoxPaintMethod.checkboxModifier_ = checkBoxModifier;
    checkBoxPaintMethod.checkboxModifier_->SetCheckboxStyle(CheckBoxStyle::SQUARE_STYLE);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    checkBoxPaintMethod.checkboxModifier_->PaintCheckBox(canvas, CONTENT_OFFSET, CONTENT_SIZE);
    /**
     * @tc.case: case. CheckBoxPaintMethod's PaintCheckBox code when !enabled_->Get()
     */
    checkBoxPaintMethod.checkboxModifier_->SetCheckboxStyle(CheckBoxStyle::SQUARE_STYLE);
    checkBoxPaintMethod.checkboxModifier_->enabled_->Set(false);
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

    auto renderContext_ = AceType::MakeRefPtr<RenderContext>();
    renderContext_->host_ = std::move(frameNode);
    WeakPtr<RenderContext> renderContext = AceType::WeakClaim(AceType::RawPtr(renderContext_));
    PaintWrapper paintWrapper(renderContext, geometryNode, checkBoxPaintProperty);
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR, SizeF(), OffsetF(), 0.0, 0.0);
    ASSERT_NE(checkBoxModifier, nullptr);
    CheckBoxPaintMethod checkBoxPaintMethod;
    checkBoxPaintMethod.checkboxModifier_ = checkBoxModifier;;
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

    auto renderContext_ = AceType::MakeRefPtr<RenderContext>();
    renderContext_->host_ = std::move(frameNode);
    WeakPtr<RenderContext> renderContext = AceType::WeakClaim(AceType::RawPtr(renderContext_));
    PaintWrapper paintWrapper(renderContext, geometryNode, checkBoxPaintProperty);
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR, SizeF(), OffsetF(), 0.0, 0.0);
    ASSERT_NE(checkBoxModifier, nullptr);
    CheckBoxPaintMethod checkBoxPaintMethod;
    checkBoxPaintMethod.checkboxModifier_ = checkBoxModifier;;
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
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR, SizeF(), OffsetF(), 0.0, 0.0);
    checkBoxModifier->SetStrokeSize(10);
    CheckBoxPaintMethod checkBoxPaintMethod;
    checkBoxPaintMethod.checkboxModifier_ = checkBoxModifier;;
    checkBoxPaintMethod.checkboxModifier_->SetCheckboxStyle(CheckBoxStyle::SQUARE_STYLE);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    checkBoxPaintMethod.checkboxModifier_->PaintCheckBox(canvas, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxPaintMethodTest005
 * @tc.desc: Test CheckBox UpdateAnimatableProperty and SetBoardColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPaintMethodTest005, TestSize.Level1)
{
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR, SizeF(), OffsetF(), 0.0, 0.0);
    checkBoxModifier->hoverColor_ = Color::RED;
    checkBoxModifier->clickEffectColor_ = Color::BLUE;
    checkBoxModifier->touchHoverType_ = TouchHoverAnimationType::HOVER;
    checkBoxModifier->UpdateAnimatableProperty(true);
    checkBoxModifier->animateTouchHoverColor_ =
        AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    checkBoxModifier->touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    checkBoxModifier->UpdateAnimatableProperty(true);
    EXPECT_EQ(checkBoxModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED));
    checkBoxModifier->touchHoverType_ = TouchHoverAnimationType::NONE;
    checkBoxModifier->UpdateAnimatableProperty(true);
    EXPECT_EQ(checkBoxModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED.BlendOpacity(0)));
    checkBoxModifier->touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    checkBoxModifier->UpdateAnimatableProperty(true);
    EXPECT_EQ(checkBoxModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
    checkBoxModifier->touchHoverType_ = TouchHoverAnimationType::PRESS;
    checkBoxModifier->UpdateAnimatableProperty(true);
    EXPECT_EQ(checkBoxModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
}

/**
 * @tc.name: CheckBoxPatternTest0133
 * @tc.desc: Test CheckBox InitOnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTestNG, CheckBoxPatternTest0133, TestSize.Level1)
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
    KeyEvent keyEventOne(KeyCode::KEY_FUNCTION, KeyAction::UP);
    EXPECT_FALSE(eventHub->ProcessOnKeyEventInternal(keyEventOne));
    /**
     * test event.action == KeyAction::DOWN and event.code != KeyCode::KEY_FUNCTION
     */
    KeyEvent keyEventTwo(KeyCode::KEY_A, KeyAction::DOWN);
    EXPECT_FALSE(eventHub->ProcessOnKeyEventInternal(keyEventTwo));
    /**
     * test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_FUNCTION
     */
    KeyEvent keyEventThr(KeyCode::KEY_FUNCTION, KeyAction::DOWN);
    EXPECT_TRUE(eventHub->ProcessOnKeyEventInternal(keyEventThr));
}
} // namespace OHOS::Ace::NG
