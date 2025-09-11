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
#include <optional>
#include <string>
#include <utility>

#include "gtest/gtest.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_model.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_method.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/radio/radio_modifier.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/render/drawing_mock.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/render_node.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;
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
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
constexpr float COMPONENT_WIDTH = 200.0;
constexpr float COMPONENT_HEIGHT = 210.0;
constexpr float BORDER_RADIUS = 100.0;
constexpr float CHECK_STROKE = 200.0;
constexpr float CHECK_MARK_SIZEF = 50.0;
constexpr float CHECK_MARK_WIDTHF = 5.0;
constexpr float CHECKMARK_PAINTSIZE = 400.0;
constexpr float HOVER_DURATION = 250.0;
constexpr float HOVER_TO_TOUCH_DURATION = 100.0;
constexpr double BORDER_WIDTH = 300.0;
constexpr Dimension CHECK_MARK_SIZE = Dimension(CHECK_MARK_SIZEF);
constexpr Dimension NEGATIVE_CHECK_MARK_SIZE = Dimension(-CHECK_MARK_SIZEF);
constexpr Dimension CHECK_MARK_WIDTH = Dimension(CHECK_MARK_WIDTHF);
const Color POINT_COLOR = Color::BLUE;
const Color ACTIVE_COLOR = Color::BLACK;
const Color INACTIVE_COLOR = Color::GREEN;
const Color SHADOW_COLOR = Color::RED;
const Color CLICK_EFFECT_COLOR = Color::WHITE;
const Color HOVER_COLOR = Color::GRAY;
const Color INACTIVE_POINT_COLOR = Color::TRANSPARENT;
const Color UNSELECTED_COLOR = Color::RED;
const Color CHECK_MARK_COLOR = Color::GREEN;
constexpr Dimension HOVER_RADIUS = Dimension(3.0);
constexpr Dimension HORIZONTAL_PADDING = Dimension(5.0);
constexpr Dimension VERTICAL_PADDING = Dimension(4.0);
constexpr Dimension SHADOW_WIDTH_FORUPDATE = Dimension(6.0);
constexpr float CHECKBOX_GROUP_LENGTH_ZERO = 0.0f;
constexpr Dimension PADDING_SIZE = Dimension(2.0);
const int32_t VERSION_TWELVE = 12;
const SizeF TEST_SIZE_0 = SizeF(0.0f, 0.0f);
const SizeF TEST_SIZE_100_200 = SizeF(100.0f, 200.0f);
const SizeF TEST_SIZE_100 = SizeF(100.0f, 100.0f);
const SizeF TEST_SIZE_200 = SizeF(200.0f, 200.0f);
const SizeF TEST_SIZE_50 = SizeF(50.0f, 50.0f);
const SizeF TEST_SIZE_60 = SizeF(60.0f, 60.0f);
constexpr float TEST_WIDTH_50 = 50.0f;
constexpr float TEST_HEIGHT_60 = 60.0f;
} // namespace

class CheckBoxGroupTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CheckBoxGroupTestNG::SetUpTestCase()
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
void CheckBoxGroupTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}
void CheckBoxGroupTestNG::SetUp() {}
void CheckBoxGroupTestNG::TearDown() {}
CheckBoxGroupModifier::Parameters CheckBoxGroupCreateDefModifierParam()
{
    CheckBoxGroupModifier::Parameters parameters = { BORDER_WIDTH, BORDER_RADIUS, CHECK_STROKE, CHECKMARK_PAINTSIZE,
        HOVER_DURATION, HOVER_TO_TOUCH_DURATION, POINT_COLOR, ACTIVE_COLOR, INACTIVE_COLOR, SHADOW_COLOR,
        CLICK_EFFECT_COLOR, HOVER_COLOR, INACTIVE_POINT_COLOR, HOVER_RADIUS, HORIZONTAL_PADDING, VERTICAL_PADDING,
        SHADOW_WIDTH_FORUPDATE, UIStatus::UNSELECTED, PADDING_SIZE, PADDING_SIZE, false,
        CheckBoxGroupPaintProperty::SelectStatus::NONE };

    return parameters;
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test CheckBoxGroup OnModifyDone001.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, OnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. call the OnModifyDone function of the checkboxgroup pattern
     * @tc.expected: the margin property meetings expectations
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetMarginProperty());
    pattern->OnModifyDone();
    EXPECT_TRUE(layoutProperty->GetMarginProperty());
    pattern->OnModifyDone();
    EXPECT_TRUE(layoutProperty->GetMarginProperty());
}

/**
 * @tc.name: UpdateUIStatus001.
 * @tc.desc: Test CheckBoxGroup UpdateUIStatus001.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, UpdateUIStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. call the UpdateUIStatus function of the checkboxgroup pattern.
     * @tc.expected: the UpdateUIStatus meetings expectations.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
    pattern->UpdateUIStatus(false);
    EXPECT_EQ(pattern->uiStatus_, UIStatus::PART_TO_OFF);
    pattern->UpdateUIStatus(true);
    EXPECT_EQ(pattern->uiStatus_, UIStatus::PART_TO_ON);
    paintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
    pattern->UpdateUIStatus(false);
    EXPECT_EQ(pattern->uiStatus_, UIStatus::ON_TO_OFF);
    pattern->UpdateUIStatus(true);
    EXPECT_EQ(pattern->uiStatus_, UIStatus::OFF_TO_ON);
}

/**
 * @tc.name: OnAfterModifyDone001
 * @tc.desc: Test CheckBoxGroup OnAfterModifyDone001.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, OnAfterModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. call the OnAfterModifyDone function of the checkboxgroup pattern.
     * @tc.expected: the inspectorId property meetings expectations.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAfterModifyDone();
    auto inspectorId = frameNode->GetInspectorId().value_or("");
    EXPECT_TRUE(inspectorId.empty());
    frameNode->UpdateInspectorId("test");
    pattern->OnAfterModifyDone();
    EXPECT_FALSE(frameNode->GetInspectorIdValue().empty());
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    pattern->initSelected_ = true;
    pattern->OnAfterModifyDone();
    EXPECT_TRUE(pattern->initSelected_);
}

/**
 * @tc.name: UpdateGroupCheckStatus001
 * @tc.desc: Test CheckBoxGroup UpdateGroupCheckStatus001.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, UpdateGroupCheckStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. call the OnAfterModifyDone function of the checkboxgroup pattern.
     * @tc.expected: the initSelected_ property meetings expectations.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    bool select = true;
    pattern->UpdateGroupCheckStatus(frameNode, select);
    select = false;
    pattern->UpdateGroupCheckStatus(frameNode, select);
}

/**
 * @tc.name: InitOnKeyEvent001
 * @tc.desc: Test checkboxgroup clickCallback of InitOnKeyEvent001.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, InitOnKeyEvent001, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());
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
 * @tc.name: CheckBoxGroupPaintPropertyTest001
 * @tc.desc: Set CheckBoxGroup value into CheckBoxGroupPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    bool flag = false;

    /**
     * @tc.steps: step2. Set parameters to CheckBoxGroup property
     */
    checkBoxGroupModelNG.SetSelectAll(SELECTED);
    checkBoxGroupModelNG.SetSelectedColor(SELECTED_COLOR);
    checkBoxGroupModelNG.SetWidth(WIDTH);
    checkBoxGroupModelNG.SetHeight(HEIGHT);
    checkBoxGroupModelNG.SetPadding(PADDING, newArgs, flag);

    /**
     * @tc.steps: step3. Get paint property and get CheckBoxGroup property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetGroupName(GROUP_NAME);
    EXPECT_EQ(eventHub->GetGroupName(), GROUP_NAME);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupSelect(), SELECTED);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupSelectedColor(), SELECTED_COLOR);
}

/**
 * @tc.name: CheckBoxGroupPaintPropertyTest002
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintPropertyTest002, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkboxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkboxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkboxTheme));
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    bool flag = false;

    /**
     * @tc.steps: step2. Set parameters to CheckBoxGroup property
     */
    checkBoxGroupModelNG.SetSelectAll(SELECTED);
    checkBoxGroupModelNG.SetSelectedColor(SELECTED_COLOR);
    checkBoxGroupModelNG.SetWidth(WIDTH);
    checkBoxGroupModelNG.SetHeight(HEIGHT);
    checkBoxGroupModelNG.SetPadding(PADDING, newArgs, flag);

    /**
     * @tc.steps: step3. Get paint property and get CheckBoxGroup property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetGroupName(GROUP_NAME);
    EXPECT_EQ(eventHub->GetGroupName(), GROUP_NAME);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupSelect(), SELECTED);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupSelectedColor(), SELECTED_COLOR);
    auto json = JsonUtil::Create(true);
    checkBoxPaintProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("selectAll"), "true");
}

/**
 * @tc.name: CheckBoxGroupEventTest002
 * @tc.desc: Test CheckBoxGroup onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG checkBoxGroup;
    checkBoxGroup.Create(GROUP_NAME);

    /**
     * @tc.steps: step2. Init change result and onChange function
     */
    std::vector<std::string> vec;
    int status = 0;
    CheckboxGroupResult groupResult(
        std::vector<std::string> { NAME }, int(CheckBoxGroupPaintProperty::SelectStatus::ALL));
    auto onChange = [&vec, &status](const BaseEventInfo* groupResult) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(groupResult);
        vec = eventInfo->GetNameList();
        status = eventInfo->GetStatus();
    };

    /**
     * @tc.steps: step3. Get event hub and call UpdateChangeEvent function
     * @tc.expected: Check the event result value
     */
    checkBoxGroup.SetOnChange(onChange);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->UpdateChangeEvent(&groupResult);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec.front(), NAME);
    EXPECT_EQ(status, int(CheckBoxGroupPaintProperty::SelectStatus::ALL));
}

/**
 * @tc.name: CheckBoxGroupPatternTest003
 * @tc.desc: Test CheckBoxGroup onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);

    /**
     * @tc.steps: step2. Test CheckBoxGroup onModifyDone method
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetPreGroup(GROUP_NAME);
    frameNode->MarkModifyDone();
    pattern->SetPreGroup(GROUP_NAME_CHANGE);
    frameNode->MarkModifyDone();
}

/**
 * @tc.name: CheckBoxGroupMeasureTest004
 * @tc.desc: Test CheckBoxGroup Measure.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupMeasureTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode and set CheckBoxGroupLayoutAlgorithm.
     */
    // Create LayoutWrapperNode and set CheckBoxGroupLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto checkBoxGroupPattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(checkBoxGroupPattern, nullptr);
    auto checkBoxGroupLayoutAlgorithm = checkBoxGroupPattern->CreateLayoutAlgorithm();
    ASSERT_NE(checkBoxGroupLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(checkBoxGroupLayoutAlgorithm));

    /**
     * @tc.steps: step3. Test CheckBoxGroup Measure method
     * @tc.expected: Check the CheckBoxGroup frame size and frame offset value
     */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    checkBoxGroupLayoutAlgorithm->Measure(&layoutWrapper);
    // Test the size set by codes.
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: CheckBoxGroupPatternTest005
 * @tc.desc: Test CheckBoxGroup pattern method OnTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);

    /**
     * @tc.steps: step2. Get CheckBoxGroup pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBoxGroup pattern variable and call OnTouchUp
     * @tc.expected: Check the CheckBoxGroup pattern value
     */
    pattern->isHover_ = false;
    pattern->OnTouchUp();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::NONE);
    pattern->isHover_ = true;
    pattern->OnTouchUp();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::PRESS_TO_HOVER);
}

/**
 * @tc.name: CheckBoxGroupPatternTest006
 * @tc.desc: Test CheckBoxGroup pattern method OnTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);

    /**
     * @tc.steps: step2. Get CheckBoxGroup pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBoxGroup pattern variable and call OnTouchDown
     * @tc.expected: Check the CheckBoxGroup pattern value
     */
    pattern->isHover_ = false;
    pattern->OnTouchDown();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::PRESS);
    pattern->isHover_ = true;
    pattern->OnTouchDown();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::HOVER_TO_PRESS);
}

/**
 * @tc.name: CheckBoxGroupPatternTest007
 * @tc.desc: Test CheckBoxGroup pattern method OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);

    /**
     * @tc.steps: step2. Get CheckBoxGroup pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBoxGroup paint property variable and call OnClick
     * @tc.expected: Check the CheckBoxGroup paint property value
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto group = eventHub->GetGroupName();
    pattern->SetPreGroup(group);
    checkBoxPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
    pattern->OnClick();
    auto select1 = checkBoxPaintProperty->GetCheckBoxGroupSelect();
    EXPECT_TRUE(select1.has_value());
    checkBoxPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
    pattern->OnClick();
    auto select2 = checkBoxPaintProperty->GetCheckBoxGroupSelect();
    EXPECT_TRUE(select2.has_value());
}

/**
 * @tc.name: CheckBoxGroupPatternTest008
 * @tc.desc: Test CheckBoxGroup pattern method HandleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);

    /**
     * @tc.steps: step2. Get CheckBoxGroup pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBoxGroup pattern variable and call HandleMouseEvent
     * @tc.expected: Check the CheckBoxGroup pattern value
     */
    pattern->isHover_ = false;
    pattern->HandleMouseEvent(true);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::HOVER);
    pattern->HandleMouseEvent(false);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::NONE);
}

/**
 * @tc.name: CheckBoxGroupPatternTest009
 * @tc.desc: Test CheckBoxGroup pattern Init methods.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);

    /**
     * @tc.steps: step2. Get CheckBoxGroup pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBoxGroup pattern variable and call Init methods
     * @tc.expected: Check the CheckBoxGroup pattern value
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
 * @tc.name: CheckBoxGroupPatternTest010
 * @tc.desc: Test CheckBoxGroup pattern Update methods.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);

    /**
     * @tc.steps: step2. Get CheckBoxGroup pattern object
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBoxGroup pattern variable and call Init methods
     * @tc.expected: Check the CheckBoxGroup pattern value
     */
    // UpdateUIStatus(bool check)
    pattern->uiStatus_ = UIStatus::ON_TO_OFF;
    pattern->UpdateUIStatus(true);
    EXPECT_EQ(pattern->uiStatus_, UIStatus::OFF_TO_ON);
    // UpdateUnSelect()
    pattern->uiStatus_ = UIStatus::ON_TO_OFF;
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
    pattern->UpdateUnSelect();
    EXPECT_EQ(pattern->uiStatus_, UIStatus::ON_TO_OFF);
    checkBoxPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::NONE);
    pattern->UpdateUnSelect();
    EXPECT_EQ(pattern->uiStatus_, UIStatus::UNSELECTED);
}

/**
 * @tc.name: CheckBoxGroupPatternTest011
 * @tc.desc: Test CheckBoxGroup onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest011, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkboxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkboxTheme));
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetPreGroup(GROUP_NAME);
    frameNode->MarkModifyDone();
    pattern->SetPreGroup(GROUP_NAME_CHANGE);
    frameNode->MarkModifyDone();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: CheckBoxGroupPatternTest012
 * @tc.desc: Test UpdateCheckBoxStatus.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest012, TestSize.Level1)
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
    auto pattern = groupFrameNode->GetPattern<CheckBoxGroupPattern>();
    EXPECT_NE(pattern, nullptr);

    groupManager->AddCheckBoxToGroup(GROUP_NAME, frameNode1);
    groupManager->AddCheckBoxToGroup(GROUP_NAME, frameNode2);
    groupManager->AddCheckBoxToGroup(GROUP_NAME, frameNode3);
    groupManager->AddCheckBoxGroup(GROUP_NAME, groupFrameNode);
    bool isSelected = true;
    pattern->UpdateCheckBoxStatus(groupFrameNode, isSelected);
    auto checkBoxPaintProperty1 = frameNode1->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(checkBoxPaintProperty1, nullptr);
    checkBoxPaintProperty1->UpdateCheckBoxSelect(true);
    auto checkBoxPaintProperty2 = frameNode2->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(checkBoxPaintProperty2, nullptr);
    checkBoxPaintProperty2->UpdateCheckBoxSelect(false);
    pattern->UpdateCheckBoxStatus(groupFrameNode, isSelected);
    isSelected = false;
    pattern->UpdateCheckBoxStatus(groupFrameNode, isSelected);
    checkBoxPaintProperty2->UpdateCheckBoxSelect(true);
    auto checkBoxPaintProperty3 = frameNode3->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(checkBoxPaintProperty3, nullptr);
    checkBoxPaintProperty3->UpdateCheckBoxSelect(true);
    isSelected = true;
    pattern->UpdateCheckBoxStatus(groupFrameNode, isSelected);
}

/**
 * @tc.name: CheckBoxGroupPatternTest013
 * @tc.desc: Test UpdateRepeatedGroupStatus.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest013, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    auto groupFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(groupFrameNode, nullptr);
    auto pattern = groupFrameNode->GetPattern<CheckBoxGroupPattern>();
    EXPECT_NE(pattern, nullptr);
    bool isSelected = true;
    pattern->UpdateRepeatedGroupStatus(groupFrameNode, isSelected);
    auto paintProperty = groupFrameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetSelectStatus(), CheckBoxGroupPaintProperty::SelectStatus::ALL);
    isSelected = false;
    pattern->UpdateRepeatedGroupStatus(groupFrameNode, isSelected);
    EXPECT_EQ(paintProperty->GetSelectStatus(), CheckBoxGroupPaintProperty::SelectStatus::NONE);
}

/**
 * @tc.name: CheckBoxGroupPatternTest014
 * @tc.desc: Test GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxPatternTest014, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxModelNG;
    checkBoxModelNG.Create(GROUP_NAME);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<EventHub> eventHub = AccessibilityManager::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AccessibilityManager::MakeRefPtr<FocusHub>(
        AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(eventHub)), FocusType::DISABLE, false);
    pattern->InitOnKeyEvent(focusHub);
    RoundRect paintRect;
    pattern->GetInnerFocusPaintRect(paintRect);
}

/**
 * @tc.name: CheckBoxGroupPatternTest017
 * @tc.desc: Test SetUnSelectedColor, SetCheckMarkColor, SetCheckMarkSize, SetCheckMarkWidth.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. Set parameters to CheckBoxGroup property
     */
    Color unselected = Color::BLACK;

    checkBoxGroupModelNG.SetUnSelectedColor(unselected);
    checkBoxGroupModelNG.SetCheckMarkColor(unselected);
    checkBoxGroupModelNG.SetCheckMarkSize(CHECK_MARK_SIZE);
    checkBoxGroupModelNG.SetCheckMarkWidth(CHECK_MARK_WIDTH);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetGroupName(GROUP_NAME);
    EXPECT_EQ(eventHub->GetGroupName(), GROUP_NAME);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupUnSelectedColor(), unselected);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupCheckMarkColor(), unselected);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupCheckMarkSize(), CHECK_MARK_SIZE);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupCheckMarkWidth(), CHECK_MARK_WIDTH);
}

/**
 * @tc.name: CheckBoxGroupPatternTest017
 * @tc.desc: Set unSelectedColor into CheckBoxGroupPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest018, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    checkBoxGroupModelNG.SetUnSelectedColor(UNSELECTED_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupUnSelectedColor(), UNSELECTED_COLOR);
}

/**
 * @tc.name: CheckBoxGroupPatternTest018
 * @tc.desc: Set checkMarkColor into CheckBoxGroupPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest019, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    checkBoxGroupModelNG.SetCheckMarkColor(CHECK_MARK_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupCheckMarkColor(), CHECK_MARK_COLOR);
}

/**
 * @tc.name: CheckBoxGroupPatternTest019
 * @tc.desc: Set checkMarkSize into CheckBoxGroupPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest020, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    checkBoxGroupModelNG.SetCheckMarkSize(CHECK_MARK_SIZE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupCheckMarkSize(), CHECK_MARK_SIZE);
}

/**
 * @tc.name: CheckBoxGroupPatternTest020
 * @tc.desc: Set checkMarkWidth into CheckBoxGroupPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest021, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    checkBoxGroupModelNG.SetCheckMarkWidth(CHECK_MARK_WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupCheckMarkWidth(), CHECK_MARK_WIDTH);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest001
 * @tc.desc: Test CheckBoxGroup Modifier DrawTouchAndHoverBoard.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintMethodTest001, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxGroupSelectedStyle(CheckBoxStyle::SQUARE_STYLE);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    /**
     *  @tc.case: case. When isTouch is true, CheckBoxGroupModifier will call DrawTouchBoard.
     */
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier_ = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier_);
    auto modifier_ = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier_, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    Testing::MockCanvas canvas;
    SizeF size;
    OffsetF offset;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    checkBoxGroupModifier_->DrawTouchAndHoverBoard(canvas, size, offset);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest004
 * @tc.desc: Test CheckBoxGroup Modifier paintCheckBox when enabled_ == false..
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintMethodTest004, TestSize.Level1)
{
    /**
     * @tc.case: case1. When uiStatus_ == UIStatus::OFF_TO_ON and enabled_ == false.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier_ = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    checkBoxGroupModifier_->uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(UIStatus::OFF_TO_ON));
    checkBoxGroupModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier_);
    auto modifier_ = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier_, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    DrawingContext context { canvas, COMPONENT_WIDTH, COMPONENT_HEIGHT };
    checkBoxGroupModifier_->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest005
 * @tc.desc: Test CheckBoxGroup Modifier will paintCheckBox when UIStatus is ON_TO_OFF.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintMethodTest005, TestSize.Level1)
{
    /**
     * @tc.case: case1. When uiStatus_ == UIStatus::ON_TO_OFF and enabled_ == true.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier_ = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    checkBoxGroupModifier_->uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(UIStatus::ON_TO_OFF));
    checkBoxGroupModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier_);
    auto modifier_ = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier_, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    DrawingContext context { canvas, COMPONENT_WIDTH, COMPONENT_HEIGHT };
    checkBoxGroupModifier_->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest006
 * @tc.desc: Test CheckBoxGroup  Modifier will paintCheckBox when UIStatus is UNSELECTED.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintMethodTest006, TestSize.Level1)
{
    /**
     * @tc.case: case1. When uiStatus_ == UIStatus::UNSELECTED and enabled_ == true.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier_ = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    checkBoxGroupModifier_->uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(UIStatus::UNSELECTED));
    checkBoxGroupModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier_);
    auto modifier_ = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier_, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    DrawingContext context { canvas, COMPONENT_WIDTH, COMPONENT_HEIGHT };
    checkBoxGroupModifier_->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest007
 * @tc.desc: Test CheckBoxGroup Modifier PaintCheckBox PaintCheckBoxGroupPartStatus.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintMethodTest007, TestSize.Level1)
{
    /**
     * @tc.case: case1. When status == CheckBoxGroupPaintProperty::SelectStatus::PART and enabled_ == true.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier_ = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    checkBoxGroupModifier_->status_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int>(CheckBoxGroupPaintProperty::SelectStatus::PART));
    checkBoxGroupModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier_);
    auto modifier_ = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier_, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    DrawingContext context { canvas, COMPONENT_WIDTH, COMPONENT_HEIGHT };
    checkBoxGroupModifier_->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest008
 * @tc.desc: Test CheckBoxGroup Modifier  paintCheckBox when UIStatus is PART_TO_OFF.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintMethodTest008, TestSize.Level1)
{
    /**
     * @tc.case: case1. When uiStatus_ == UIStatus::PART_TO_OFF and enabled_ == false.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier_ = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    checkBoxGroupModifier_->uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(UIStatus::PART_TO_OFF));
    checkBoxGroupModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier_);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    DrawingContext context { canvas, COMPONENT_WIDTH, COMPONENT_HEIGHT };
    checkBoxGroupModifier_->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest009
 * @tc.desc: Test checkBoxPaintMethod  UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintMethodTest009, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(COMPONENT_WIDTH, COMPONENT_WIDTH));
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier_ = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    checkBoxGroupModifier_->uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(UIStatus::FOCUS));
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier_);
    checkBoxPaintProperty->UpdateCheckBoxGroupSelectedColor(ACTIVE_COLOR);
    checkBoxPaintProperty->UpdateCheckBoxGroupUnSelectedColor(INACTIVE_COLOR);
    checkBoxPaintProperty->UpdateCheckBoxGroupCheckMarkColor(POINT_COLOR);
    checkBoxPaintProperty->UpdateCheckBoxGroupCheckMarkSize(NEGATIVE_CHECK_MARK_SIZE);
    checkBoxPaintProperty->UpdateCheckBoxGroupCheckMarkWidth(CHECK_MARK_WIDTH);
    /**
     * @tc.expected: step1. Check the CheckBoxGroup property value.
     */
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(checkBoxGroupModifier_->activeColor_->Get(), LinearColor(ACTIVE_COLOR));
    EXPECT_EQ(checkBoxGroupModifier_->inactiveColor_->Get(), LinearColor(INACTIVE_COLOR));
    EXPECT_EQ(checkBoxGroupModifier_->pointColor_->Get(), LinearColor(POINT_COLOR));
    EXPECT_EQ(checkBoxGroupModifier_->checkMarkPaintSize_->Get(), COMPONENT_WIDTH);
    EXPECT_EQ(checkBoxGroupModifier_->checkStroke_->Get(), CHECK_MARK_WIDTHF);
    /**
     * @tc.expected: step2.Test GetCheckBoxGroupCheckMarkSizeValue().ConvertToPx() >= 0.
     */
    checkBoxPaintProperty->UpdateCheckBoxGroupCheckMarkSize(CHECK_MARK_SIZE);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(checkBoxGroupModifier_->checkMarkPaintSize_->Get(), CHECK_MARK_SIZEF);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest010
 * @tc.desc: Test CheckBoxGroupPattern UpdateModifierParam.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintMethodTest010, TestSize.Level1)
{
    const std::optional<std::string> groupName;
    CheckBoxGroupModelNG checkboxGroupModel;
    checkboxGroupModel.Create(groupName);
    auto groupFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(groupFrameNode, nullptr);
    auto checkBoxPaintProperty = groupFrameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxGroupSelectedColor(ACTIVE_COLOR);
    checkBoxPaintProperty->UpdateCheckBoxGroupUnSelectedColor(INACTIVE_COLOR);
    checkBoxPaintProperty->UpdateCheckBoxGroupCheckMarkColor(POINT_COLOR);
    checkBoxPaintProperty->UpdateCheckBoxGroupCheckMarkSize(CHECK_MARK_SIZE);
    checkBoxPaintProperty->UpdateCheckBoxGroupCheckMarkWidth(CHECK_MARK_WIDTH);
    auto pattern = groupFrameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    auto modifier_ = pattern->checkBoxGroupModifier_;
    ASSERT_NE(modifier_, nullptr);
    EXPECT_EQ(modifier_->activeColor_->Get(), LinearColor(ACTIVE_COLOR));
    EXPECT_EQ(modifier_->inactiveColor_->Get(), LinearColor(INACTIVE_COLOR));
    EXPECT_EQ(modifier_->pointColor_->Get(), LinearColor(POINT_COLOR));
    EXPECT_EQ(modifier_->checkMarkPaintSize_->Get(), CHECK_MARK_SIZEF);
    EXPECT_EQ(modifier_->checkStroke_->Get(), CHECK_MARK_WIDTHF);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest011
 * @tc.desc:  Test CheckBoxGroupModifier  paintCheckBox when enabled_ == false.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintMethodTest011, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier_ = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    checkBoxGroupModifier_->uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(UIStatus::ON_TO_OFF));
    checkBoxGroupModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier_);
    auto modifier_ = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier_, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    DrawingContext context { canvas, COMPONENT_WIDTH, COMPONENT_HEIGHT };
    checkBoxGroupModifier_->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest012
 * @tc.desc:  Test CheckBoxGroupModifier PaintCheckBox when enabled_ == false.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintMethodTest012, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier_ = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    checkBoxGroupModifier_->uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(UIStatus::UNSELECTED));
    checkBoxGroupModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(checkBoxGroupModifier_);
    auto modifier_ = checkBoxPaintMethod.GetContentModifier(&paintWrapper);
    ASSERT_NE(modifier_, nullptr);
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    DrawingContext context { canvas, COMPONENT_WIDTH, COMPONENT_HEIGHT };
    checkBoxGroupModifier_->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest013
 * @tc.desc: Test CheckBoxGroup UpdateAnimatableProperty and SetBoardColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintMethodTest013, TestSize.Level1)
{
    const std::optional<std::string> groupName;
    CheckBoxGroupModelNG checkboxGroupModel;
    checkboxGroupModel.Create(groupName);
    auto groupFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(groupFrameNode, nullptr);
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier_ = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    checkBoxGroupModifier_->hoverColor_ = Color::RED;
    checkBoxGroupModifier_->clickEffectColor_ = Color::BLUE;
    checkBoxGroupModifier_->touchHoverType_ = TouchHoverAnimationType::HOVER;
    checkBoxGroupModifier_->UpdateAnimatableProperty(groupFrameNode);
    checkBoxGroupModifier_->animateTouchHoverColor_ =
        AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    checkBoxGroupModifier_->touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    checkBoxGroupModifier_->UpdateAnimatableProperty(groupFrameNode);
    EXPECT_EQ(checkBoxGroupModifier_->animateTouchHoverColor_->Get(), LinearColor(Color::RED));
    checkBoxGroupModifier_->touchHoverType_ = TouchHoverAnimationType::NONE;
    checkBoxGroupModifier_->UpdateAnimatableProperty(groupFrameNode);
    EXPECT_EQ(checkBoxGroupModifier_->animateTouchHoverColor_->Get(), LinearColor(Color::RED.BlendOpacity(0)));
    checkBoxGroupModifier_->touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    checkBoxGroupModifier_->UpdateAnimatableProperty(groupFrameNode);
    EXPECT_EQ(checkBoxGroupModifier_->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
    checkBoxGroupModifier_->touchHoverType_ = TouchHoverAnimationType::PRESS;
    checkBoxGroupModifier_->UpdateAnimatableProperty(groupFrameNode);
    EXPECT_EQ(checkBoxGroupModifier_->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
}

/**
 * @tc.name: CheckBoxGroupAccessibilityPropertyTestNg001
 * @tc.desc: Test Text property of CheckBoxGroup.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupAccessibilityPropertyTestNg001, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetGroupName(GROUP_NAME);

    auto accessibility = frameNode->GetAccessibilityProperty<CheckBoxGroupAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_EQ(accessibility->GetText(), GROUP_NAME);
}

/**
 * @tc.name: CheckBoxGroupAccessibilityPropertyTestNg002
 * @tc.desc: Test IsCheckable and IsChecked properties of CheckBoxGroup.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupAccessibilityPropertyTestNg002, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto accessibility = frameNode->GetAccessibilityProperty<CheckBoxGroupAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsCheckable());

    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
    EXPECT_TRUE(accessibility->IsChecked());
    checkBoxPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
    EXPECT_FALSE(accessibility->IsChecked());
    checkBoxPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::NONE);
    EXPECT_FALSE(accessibility->IsChecked());
}

/**
 * @tc.name: CheckBoxGroupAccessibilityPropertyTestNg003
 * @tc.desc: Test GetCollectionItemCounts property of CheckBoxGroup.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupAccessibilityPropertyTestNg003, TestSize.Level1)
{
    auto groupFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::CHECKBOXGROUP_ETS_TAG, 1, []() { return AceType::MakeRefPtr<CheckBoxGroupPattern>(); });
    EXPECT_NE(groupFrameNode, nullptr);
    auto eventHub = groupFrameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    eventHub->SetGroupName(GROUP_NAME);
    groupFrameNode->MarkModifyDone();

    auto accessibility = groupFrameNode->GetAccessibilityProperty<CheckBoxGroupAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_EQ(accessibility->GetCollectionItemCounts(), 0);
}

/**
 * @tc.name: CheckBoxUpdateChangeEventTest001
 * @tc.desc: Test CheckBoxGroup onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxUpdateChangeEventTest001, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroup;
    checkBoxGroup.Create(GROUP_NAME);
    std::vector<std::string> vec;
    int status = 0;
    CheckboxGroupResult groupResult(
        std::vector<std::string> { NAME }, int(CheckBoxGroupPaintProperty::SelectStatus::ALL));
    auto changeEvent = [&vec, &status](const BaseEventInfo* groupResult) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(groupResult);
        vec = eventInfo->GetNameList();
        status = eventInfo->GetStatus();
    };

    checkBoxGroup.SetChangeEvent(changeEvent);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->UpdateChangeEvent(&groupResult);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec.front(), NAME);
    EXPECT_EQ(status, int(CheckBoxGroupPaintProperty::SelectStatus::ALL));
}

/**
 * @tc.name: CheckBoxGroupModifierTest001
 * @tc.desc: Test CheckBoxGroupModifier PaintCheckBox method in different situation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupModifier.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    ASSERT_NE(checkBoxGroupModifier, nullptr);
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, COMPONENT_WIDTH, COMPONENT_HEIGHT };

    /**
     * @tc.steps: step2. Call PaintCheckBox method.
     * @tc.expected: Call method successfully.
     */
    checkBoxGroupModifier->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
    checkBoxGroupModifier->SetEnabled(false);
    checkBoxGroupModifier->SetCheckMarkPaintSize(CHECKBOX_GROUP_LENGTH_ZERO);
    checkBoxGroupModifier->SetCheckStroke(CHECKBOX_GROUP_LENGTH_ZERO);
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    checkBoxGroupModifier->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
    checkBoxGroupModifier->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::ALL);
    checkBoxGroupModifier->SetUiStatus(UIStatus::OFF_TO_ON);
    checkBoxGroupModifier->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
    checkBoxGroupModifier->SetEnabled(true);
    checkBoxGroupModifier->SetUiStatus(UIStatus::PART_TO_ON);
    checkBoxGroupModifier->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
    checkBoxGroupModifier->SetEnabled(false);
    checkBoxGroupModifier->SetUiStatus(UIStatus::ON_TO_OFF);
    checkBoxGroupModifier->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxGroupModifierTest002
 * @tc.desc: Test CheckBoxGroupModifier DrawCheck method in different situation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupModifierTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupModifier.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    ASSERT_NE(checkBoxGroupModifier, nullptr);

    /**
     * @tc.steps: step2. Call DrawCheck method.
     * @tc.expected: Call successfully once while checkMarkPaintSize_ and checkStroke_ both equal to 0.
     */
    Testing::MockCanvas canvas;
    RSPen rsPen;
    RSPen shadowPen;
    EXPECT_CALL(canvas, AttachPen(_)).Times(2).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(2);
    checkBoxGroupModifier->SetCheckMarkPaintSize(CHECKBOX_GROUP_LENGTH_ZERO);
    checkBoxGroupModifier->SetCheckStroke(CHECKBOX_GROUP_LENGTH_ZERO);
    checkBoxGroupModifier->DrawCheck(canvas, CONTENT_OFFSET, rsPen, shadowPen, CONTENT_SIZE);
    checkBoxGroupModifier->SetCheckMarkPaintSize(CHECKBOX_GROUP_LENGTH_ZERO + 1.0);
    checkBoxGroupModifier->DrawCheck(canvas, CONTENT_OFFSET, rsPen, shadowPen, CONTENT_SIZE);
    checkBoxGroupModifier->SetCheckMarkPaintSize(CHECKBOX_GROUP_LENGTH_ZERO);
    checkBoxGroupModifier->SetCheckStroke(CHECKBOX_GROUP_LENGTH_ZERO + 1);
    checkBoxGroupModifier->DrawCheck(canvas, CONTENT_OFFSET, rsPen, shadowPen, CONTENT_SIZE);
    checkBoxGroupModifier->SetCheckMarkPaintSize(CHECKBOX_GROUP_LENGTH_ZERO + 1.0);
    checkBoxGroupModifier->DrawCheck(canvas, CONTENT_OFFSET, rsPen, shadowPen, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxGroupModifierTest003
 * @tc.desc: Test CheckBoxGroupModifier DrawPart method in different situation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupModifierTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupModifier.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    ASSERT_NE(checkBoxGroupModifier, nullptr);

    /**
     * @tc.steps: step2. Call DrawPart method.
     * @tc.expected: Call successfully once while checkMarkPaintSize_ and checkStroke_ both equal to 0.
     */
    Testing::MockCanvas canvas;
    RSPen rsPen;
    EXPECT_CALL(canvas, AttachPen(_)).Times(2).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(2);
    checkBoxGroupModifier->SetCheckMarkPaintSize(CHECKBOX_GROUP_LENGTH_ZERO);
    checkBoxGroupModifier->SetCheckStroke(CHECKBOX_GROUP_LENGTH_ZERO);
    checkBoxGroupModifier->DrawPart(canvas, CONTENT_OFFSET, rsPen, CONTENT_SIZE);
    checkBoxGroupModifier->SetCheckMarkPaintSize(CHECKBOX_GROUP_LENGTH_ZERO + 1.0);
    checkBoxGroupModifier->DrawPart(canvas, CONTENT_OFFSET, rsPen, CONTENT_SIZE);
    checkBoxGroupModifier->SetCheckMarkPaintSize(CHECKBOX_GROUP_LENGTH_ZERO);
    checkBoxGroupModifier->SetCheckStroke(CHECKBOX_GROUP_LENGTH_ZERO + 1);
    checkBoxGroupModifier->DrawPart(canvas, CONTENT_OFFSET, rsPen, CONTENT_SIZE);
    checkBoxGroupModifier->SetCheckMarkPaintSize(CHECKBOX_GROUP_LENGTH_ZERO + 1.0);
    checkBoxGroupModifier->DrawPart(canvas, CONTENT_OFFSET, rsPen, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest001
 * @tc.desc: Test CheckBoxGroupLayoutAlgorithm MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupLayoutAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupLayoutAlgorithm.
     * @tc.expected: Create successfully.
     */
    std::optional<float> nullLength;
    OptionalSizeF optionalSizeF(nullLength, nullLength);
    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize = optionalSizeF;
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, geometryNode, AccessibilityManager::MakeRefPtr<LayoutProperty>());
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkboxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    checkboxTheme->defaultWidth_ = Dimension(COMPONENT_WIDTH);
    checkboxTheme->defaultHeight_ = Dimension(COMPONENT_WIDTH);
    checkboxTheme->hotZoneHorizontalPadding_ = Dimension(COMPONENT_WIDTH / 4);
    checkboxTheme->hotZoneVerticalPadding_ = Dimension(COMPONENT_WIDTH / 4);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkboxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkboxTheme));
    auto checkBoxGroupLayoutAlgorithm = AceType::MakeRefPtr<CheckBoxGroupLayoutAlgorithm>();
    ASSERT_NE(checkBoxGroupLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. Call method wile the width and height of contentConstraint are both null.
     * @tc.expected: Return sizeF base on default width and height.
     */
    auto size = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_FLOAT_EQ(size->Width(), COMPONENT_WIDTH / 2);
    EXPECT_FLOAT_EQ(size->Height(), COMPONENT_WIDTH / 2);
    checkboxTheme->defaultHeight_ = Dimension(COMPONENT_HEIGHT);
    size = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_FLOAT_EQ(size->Width(), COMPONENT_WIDTH / 2);
    EXPECT_FLOAT_EQ(size->Height(), COMPONENT_WIDTH / 2);

    /**
     * @tc.steps: step3. Call method wile the width of contentConstraint is null.
     * @tc.expected: Return sizeF base on height of contentConstraint.
     */
    contentConstraint.selfIdealSize.SetHeight(std::make_optional<float>(-1));
    size = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_FLOAT_EQ(size->Width(), COMPONENT_WIDTH / 2);
    EXPECT_FLOAT_EQ(size->Height(), COMPONENT_WIDTH / 2);
    contentConstraint.selfIdealSize.SetHeight(BORDER_RADIUS);
    size = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_FLOAT_EQ(size->Width(), BORDER_RADIUS);
    EXPECT_FLOAT_EQ(size->Height(), BORDER_RADIUS);

    /**
     * @tc.steps: step4. Call method wile the height of contentConstraint is null.
     * @tc.expected: Return sizeF base on width of contentConstraint.
     */
    contentConstraint.selfIdealSize.SetWidth(std::make_optional<float>(-1));
    contentConstraint.selfIdealSize.SetHeight(nullLength);
    size = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_FLOAT_EQ(size->Width(), COMPONENT_WIDTH / 2);
    EXPECT_FLOAT_EQ(size->Height(), COMPONENT_WIDTH / 2);
    contentConstraint.selfIdealSize.SetWidth(BORDER_WIDTH);
    size = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_FLOAT_EQ(size->Width(), BORDER_WIDTH);
    EXPECT_FLOAT_EQ(size->Height(), BORDER_WIDTH);

    /**
     * @tc.steps: step5. Call method wile contentConstraint is totally available.
     * @tc.expected: Return sizeF base on the width and height of contentConstraint.
     */
    contentConstraint.selfIdealSize.SetWidth(std::make_optional<float>(-1));
    contentConstraint.selfIdealSize.SetHeight(std::make_optional<float>(-1));
    size = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_FLOAT_EQ(size->Width(), COMPONENT_WIDTH / 2);
    EXPECT_FLOAT_EQ(size->Height(), COMPONENT_WIDTH / 2);
    contentConstraint.selfIdealSize.SetWidth(BORDER_WIDTH);
    contentConstraint.selfIdealSize.SetHeight(BORDER_RADIUS);
    size = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_FLOAT_EQ(size->Width(), BORDER_RADIUS);
    EXPECT_FLOAT_EQ(size->Height(), BORDER_RADIUS);
}

/**
 * @tc.name: CheckBoxGroupPatternTest022
 * @tc.desc: Test CheckBoxGroupPattern MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupPattern.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxGroupPattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(checkBoxGroupPattern, nullptr);

    /**
     * @tc.steps: step2. Call touchCallback with different touchType.
     * @tc.expected: TouchCallback works correctly.
     */
    checkBoxGroupPattern->InitTouchEvent();
    ASSERT_NE(checkBoxGroupPattern->touchListener_, nullptr);
    checkBoxGroupPattern->InitTouchEvent();
    auto touchCallback = checkBoxGroupPattern->touchListener_->GetTouchEventCallback();
    TouchLocationInfo touchLocationInfo(-1);
    touchLocationInfo.SetTouchType(TouchType::UP);
    TouchEventInfo touchEventInfo(NAME);
    touchEventInfo.touches_.clear();
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchCallback(touchEventInfo);
    EXPECT_EQ(checkBoxGroupPattern->touchHoverType_, TouchHoverAnimationType::NONE);
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    checkBoxGroupPattern->isHover_ = true;
    touchCallback(touchEventInfo);
    EXPECT_EQ(checkBoxGroupPattern->touchHoverType_, TouchHoverAnimationType::PRESS_TO_HOVER);
}

/**
 * @tc.name: CheckBoxGroupPatternTest023
 * @tc.desc: Test CheckBoxGroupPattern UpdateState.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupPattern.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto checkBoxGroupPattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(checkBoxGroupPattern, nullptr);

    /**
     * @tc.steps: step2. Call method while checkBoxGroup hasn't preGroup.
     * @tc.expected: SelectStatus and uiStatus set correctly.
     */
    checkBoxGroupPattern->preGroup_.reset();
    paintProperty->UpdateCheckBoxGroupSelect(true);
    checkBoxGroupPattern->isFirstCreated_ = false;
    checkBoxGroupPattern->UpdateState();
    EXPECT_EQ(paintProperty->GetSelectStatus(), CheckBoxGroupPaintProperty::SelectStatus::ALL);
    EXPECT_EQ(checkBoxGroupPattern->uiStatus_, UIStatus::OFF_TO_ON);

    /**
     * @tc.steps: step3. Call method while clicked requires processing.
     * @tc.expected: Change selectAll to false dynamically.
     */
    checkBoxGroupPattern->preGroup_ = std::make_optional<std::string>(NAME);
    eventHub->SetGroupName(NAME);
    checkBoxGroupPattern->updateFlag_ = true;
    checkBoxGroupPattern->SetIsAddToMap(true);
    checkBoxGroupPattern->UpdateState();
    EXPECT_EQ(paintProperty->GetSelectStatus(), CheckBoxGroupPaintProperty::SelectStatus::ALL);
    EXPECT_FALSE(checkBoxGroupPattern->updateFlag_);
    paintProperty->UpdateCheckBoxGroupSelect(true);
    checkBoxGroupPattern->SetIsAddToMap(false);
    checkBoxGroupPattern->UpdateState();
    EXPECT_EQ(paintProperty->GetSelectStatus(), CheckBoxGroupPaintProperty::SelectStatus::ALL);
    EXPECT_FALSE(checkBoxGroupPattern->updateFlag_);

    paintProperty->UpdateCheckBoxGroupSelect(false);
    checkBoxGroupPattern->UpdateState();
    EXPECT_FALSE(checkBoxGroupPattern->updateFlag_);
}

/**
 * @tc.name: CheckBoxGroupPatternTest024
 * @tc.desc: Test CheckBoxGroupPattern UpdateCheckBoxStatus.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest024, TestSize.Level1)
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
    /**
     * @tc.steps: step1. Create CheckBoxGroupPattern.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxGroupPattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(checkBoxGroupPattern, nullptr);

    /**
     * @tc.steps: step2. Create frameNode list as parameter and call method.
     * @tc.expected: Unavailable frameNode is skipped.
     */
    auto group = NAME;
    std::list<WeakPtr<FrameNode>> list;
    Ace::RefPtr<FrameNode> frameNode1 = nullptr;
    auto frameNode2 = FrameNode::GetOrCreateFrameNode(
        V2::CHECKBOXGROUP_ETS_TAG, 1, []() { return AceType::MakeRefPtr<CheckBoxGroupPattern>(); });
    auto frameNode3 = FrameNode::GetOrCreateFrameNode(
        V2::CHECK_BOX_ETS_TAG, 2, []() { return AceType::MakeRefPtr<CheckBoxPattern>(); });
    auto paintProperty = frameNode3->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->ResetCheckBoxSelect();
    auto checkBoxPattern = frameNode3->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    checkBoxPattern->SetLastSelect(true);
    groupManager->AddCheckBoxGroup(GROUP_NAME, frameNode1);
    groupManager->AddCheckBoxGroup(GROUP_NAME, frameNode2);
    groupManager->AddCheckBoxGroup(GROUP_NAME, frameNode3);
    checkBoxGroupPattern->UpdateCheckBoxStatus(frameNode, false);
    EXPECT_TRUE(checkBoxPattern->lastSelect_);
}

/**
 * @tc.name: CheckBoxGroupPatternTest025
 * @tc.desc: Test CheckBoxGroupPattern InitOnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupPattern.
     * @tc.expected: Create successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkboxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    checkboxTheme->focusRadius_ = Dimension(BORDER_RADIUS);
    checkboxTheme->focusPaintPadding_ = Dimension(COMPONENT_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkboxTheme));
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxGroupPattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(checkBoxGroupPattern, nullptr);

    /**
     * @tc.steps: step2. Get onKeyEventCallback and getInnerPaintRectCallback.
     * @tc.expected: Get successfully.
     */
    RefPtr<EventHub> eventHub = AccessibilityManager::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AccessibilityManager::MakeRefPtr<FocusHub>(
        AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(eventHub)), FocusType::DISABLE, false);
    checkBoxGroupPattern->InitOnKeyEvent(focusHub);
    auto getInnerPaintRectCallback = focusHub->getInnerFocusRectFunc_;

    /**
     * @tc.steps: step3. Test onKeyEventCallback and getInnerPaintRectCallback.
     * @tc.expected: Callbacks works correctly.
     */
    KeyEvent keyEvent(KeyCode::KEY_FOCUS, KeyAction::CLICK);
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    keyEvent.action = KeyAction::DOWN;
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    keyEvent.code = KeyCode::KEY_ENTER;
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEvent));

    checkBoxGroupPattern->offset_ = OffsetF(COMPONENT_HEIGHT, COMPONENT_HEIGHT);
    checkBoxGroupPattern->size_ = SizeF(BORDER_RADIUS, BORDER_RADIUS);
    RoundRect paintRect;
    getInnerPaintRectCallback(paintRect);
    EXPECT_FLOAT_EQ(paintRect.GetRect().GetX(), COMPONENT_HEIGHT - COMPONENT_WIDTH);
    EXPECT_FLOAT_EQ(paintRect.GetRect().GetY(), COMPONENT_HEIGHT - COMPONENT_WIDTH);
    EXPECT_FLOAT_EQ(paintRect.GetRect().Width(), BORDER_RADIUS + COMPONENT_WIDTH * 2);
    EXPECT_FLOAT_EQ(paintRect.GetRect().Height(), BORDER_RADIUS + COMPONENT_WIDTH * 2);
    EXPECT_FLOAT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x, BORDER_RADIUS);
    EXPECT_FLOAT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y, BORDER_RADIUS);
    EXPECT_FLOAT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).x, BORDER_RADIUS);
    EXPECT_FLOAT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).y, BORDER_RADIUS);
    EXPECT_FLOAT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).x, BORDER_RADIUS);
    EXPECT_FLOAT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).y, BORDER_RADIUS);
    EXPECT_FLOAT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).x, BORDER_RADIUS);
    EXPECT_FLOAT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).y, BORDER_RADIUS);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test on color configuration update.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, OnColorConfigurationUpdate001, TestSize.Level1)
{
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxGroupPattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(checkBoxGroupPattern, nullptr);
    auto checkBoxGroupPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxGroupPaintProperty, nullptr);
    checkBoxGroupPaintProperty->UpdateCheckBoxGroupSelectedColor(Color::BLACK);
    checkBoxGroupPaintProperty->UpdateCheckBoxGroupSelectedColorFlagByUser(true);
    checkBoxGroupPaintProperty->UpdateCheckBoxGroupUnSelectedColor(Color::BLACK);
    checkBoxGroupPaintProperty->UpdateCheckBoxGroupUnSelectedColorFlagByUser(true);
    checkBoxGroupPaintProperty->UpdateCheckBoxGroupCheckMarkColor(Color::BLACK);
    checkBoxGroupPaintProperty->UpdateCheckBoxGroupCheckMarkColorFlagByUser(true);
    checkBoxGroupPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(checkBoxGroupPaintProperty->GetCheckBoxGroupSelectedColor(), Color::BLACK);
    EXPECT_EQ(checkBoxGroupPaintProperty->GetCheckBoxGroupUnSelectedColor(), Color::BLACK);
    EXPECT_EQ(checkBoxGroupPaintProperty->GetCheckBoxGroupCheckMarkColor(), Color::BLACK);
}

/**
 * @tc.name: CheckBoxGroupPatternTest026
 * @tc.desc: Test CheckBoxGroupPattern UpdateModifierParam.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupPattern.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto checkBoxGroupPattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(checkBoxGroupPattern, nullptr);

    /**
     * @tc.steps: step2. Call method while properties are unavailable.
     * @tc.expected: ModifierParam isn't updated.
     */
    paintProperty->ResetCheckBoxGroupSelectedColor();
    paintProperty->ResetCheckBoxGroupUnSelectedColor();
    paintProperty->ResetCheckBoxGroupCheckMarkColor();
    paintProperty->ResetCheckBoxGroupCheckMarkSize();
    paintProperty->ResetCheckBoxGroupCheckMarkWidth();
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    checkBoxGroupPattern->UpdateModifierParam(parameters);
    paintProperty->UpdateCheckBoxGroupCheckMarkSize(Dimension(-1.0));
    geometryNode->SetContentSize(SizeF(COMPONENT_WIDTH, COMPONENT_HEIGHT));
    checkBoxGroupPattern->UpdateModifierParam(parameters);
    EXPECT_FLOAT_EQ(parameters.checkMarkPaintSize, COMPONENT_WIDTH);
}

/**
 * @tc.name: CheckBoxGroupPatternTest027
 * @tc.desc: CheckBoxGroup test Select and ClearSelection.
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest027, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    checkBoxGroupModelNG.SetSelectAll(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->updateFlag_ = false;
    pattern->SetAccessibilityAction();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<CheckBoxGroupAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->ActActionSelect());

    bool isSelected = true;
    pattern->updateFlag_ = false;
    pattern->MarkIsSelected(isSelected);
    EXPECT_TRUE(accessibilityProperty->ActActionClearSelection());
}

/**
 * @tc.name: CheckBoxGroupPaintPropertyTest028
 * @tc.desc: Set CheckBoxGroup style value into CheckBoxGroupPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintPropertyTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. Set parameters to CheckBoxGroup property
     */
    checkBoxGroupModelNG.SetCheckboxGroupStyle(CheckBoxStyle::SQUARE_STYLE);
    /**
     * @tc.steps: step3. Get paint property and get CheckBoxGroup property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->HasCheckBoxGroupSelectedStyle(), true);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxGroupSelectedStyleValue(), CheckBoxStyle::SQUARE_STYLE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPaintPropertyTest029
 * @tc.desc: Verify ToJsonValue of shape.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPaintPropertyTest029, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(std::optional<string>());

    /**
     * @tc.steps: step2. Set parameters to CheckBoxGroup property
     */
    checkBoxGroupModelNG.SetCheckboxGroupStyle(CheckBoxStyle::SQUARE_STYLE);
    /**
     * @tc.steps: step3. Get paint property and get CheckBoxGroup property
     * @tc.expected: Check the CheckBoxGroup property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    auto json = JsonUtil::Create(true);
    checkBoxPaintProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("checkboxShape"), "1");
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupPatternTest030
 * @tc.desc: Test OnAfterModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupPatternTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBoxGroup node
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CheckBoxModelNG checkboxModelNG;
    checkboxModelNG.Create(NAME, GROUP_NAME, TAG);
    checkboxModelNG.SetCheckboxStyle(CheckBoxStyle::CIRCULAR_STYLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    CheckBoxGroupModelNG checkboxGroupModelNG;
    checkboxGroupModelNG.Create(GROUP_NAME);
    checkboxGroupModelNG.SetCheckboxGroupStyle(CheckBoxStyle::SQUARE_STYLE);
    auto groupFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(groupFrameNode, nullptr);
    auto pattern = groupFrameNode->GetPattern<CheckBoxGroupPattern>();
    EXPECT_NE(pattern, nullptr);

    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    EXPECT_NE(checkBoxGroupModifier, nullptr);
    pattern->UpdateCheckBoxStyle();
    /**
     * @tc.steps: step2. Get paint property and get CheckBoxGroup and CheckBox property
     * @tc.expected: Check the CheckBoxGroup and CheckBox property value
     */
    auto groupPaintProperty = groupFrameNode->GetPaintProperty<CheckBoxGroupPaintProperty>();
    EXPECT_NE(groupPaintProperty, nullptr);
    EXPECT_EQ(groupPaintProperty->GetCheckBoxGroupSelectedStyleValue(), CheckBoxStyle::SQUARE_STYLE);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelectedStyleValue(), CheckBoxStyle::CIRCULAR_STYLE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupNGTest031
 * @tc.desc: Test SetCheckBoxName func.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupNGTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    auto frameNode = CheckBoxGroupModelNG::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. SetCheckBoxName GroupName
     */
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    CheckBoxGroupModelNG::SetCheckboxGroupName(node, "testGroupName");

    /**
     * @tc.steps: step3. assert GroupName
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->GetGroupName(), "testGroupName");
}

/**
 * @tc.name: CheckBoxGroupNGTest032
 * @tc.desc: Test retrieval of group、selectall、selectedcolor、unselectedcoulor、mark and shape values.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupNGTest032, TestSize.Level1)
{
    auto frameNode = CheckBoxGroupModelNG::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    CheckBoxGroupModelNG::SetCheckboxGroupName(node, GROUP_NAME);
    EXPECT_EQ(CheckBoxGroupModelNG::GetCheckboxGroupName(node), GROUP_NAME);

    CheckBoxGroupModelNG::SetSelectAll(node, SELECTED);
    EXPECT_EQ(CheckBoxGroupModelNG::GetSelect(node), SELECTED);

    CheckBoxGroupModelNG::SetSelectedColor(node, SELECTED_COLOR);
    EXPECT_EQ(CheckBoxGroupModelNG::GetSelectedColor(node), SELECTED_COLOR);

    CheckBoxGroupModelNG::SetUnSelectedColor(node, UNSELECTED_COLOR);
    EXPECT_EQ(CheckBoxGroupModelNG::GetUnSelectedColor(node), UNSELECTED_COLOR);

    CheckBoxGroupModelNG::SetCheckMarkColor(node, CHECK_MARK_COLOR);
    EXPECT_EQ(CheckBoxGroupModelNG::GetCheckMarkColor(node), CHECK_MARK_COLOR);

    CheckBoxGroupModelNG::SetCheckMarkSize(node, CHECK_MARK_SIZE);
    EXPECT_EQ(CheckBoxGroupModelNG::GetCheckMarkSize(node), CHECK_MARK_SIZE);

    CheckBoxGroupModelNG::SetCheckMarkWidth(node, CHECK_MARK_WIDTH);
    EXPECT_EQ(CheckBoxGroupModelNG::GetCheckMarkWidth(node), CHECK_MARK_WIDTH);

    CheckBoxGroupModelNG::SetCheckboxGroupStyle(node, CheckBoxStyle::SQUARE_STYLE);
    EXPECT_EQ(CheckBoxGroupModelNG::GetCheckboxGroupStyle(node),  CheckBoxStyle::SQUARE_STYLE);
}

/**
 * @tc.name: CheckBoxGroupNGTest033
 * @tc.desc: Test CheckBoxGroupPattern InitOnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupNGTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupPattern.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModelNG CheckBoxGroupModelNG;
    CheckBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxGroupPattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(checkBoxGroupPattern, nullptr);

    /**
     * @tc.steps: step2. Get onKeyEventCallback.
     * @tc.expected: Get successfully.
     */
    RefPtr<EventHub> eventHub = AccessibilityManager::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AccessibilityManager::MakeRefPtr<FocusHub>(
        AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(eventHub)), FocusType::DISABLE, false);
    checkBoxGroupPattern->InitOnKeyEvent(focusHub);

    /**
     * test event.action != KeyAction::DOWN
     */
    KeyEvent keyEventOne(KeyCode::KEY_FUNCTION, KeyAction::UP);
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEventOne));
    /**
     * test event.action == KeyAction::DOWN and event.code != KeyCode::KEY_FUNCTION
     */
    KeyEvent keyEventTwo(KeyCode::KEY_A, KeyAction::DOWN);
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEventTwo));
    /**
     * test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_FUNCTION
     */
    KeyEvent keyEventThr(KeyCode::KEY_FUNCTION, KeyAction::DOWN);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEventThr));
}

/**
 * @tc.name: CheckBoxGroupNGTest034
 * @tc.desc: Test CheckBoxGroupModifier PaintCheckBox method in different situation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupNGTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. MockContainer.apiTargetVersion_ = VERSION_TWELVE.
     */
    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(VERSION_TWELVE);

    /**
     * @tc.steps: step2. Create CheckBoxGroupModifier.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParam();
    auto checkBoxGroupModifier = AceType::MakeRefPtr<CheckBoxGroupModifier>(parameters);
    ASSERT_NE(checkBoxGroupModifier, nullptr);
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, COMPONENT_WIDTH, COMPONENT_HEIGHT };

    /**
     * @tc.steps: step3. Call PaintCheckBox method.
     * @tc.expected: Call method successfully.
     */
    checkBoxGroupModifier->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
    checkBoxGroupModifier->SetEnabled(false);
    checkBoxGroupModifier->SetCheckStroke(CHECKBOX_GROUP_LENGTH_ZERO);
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    checkBoxGroupModifier->PaintCheckBox(context, CONTENT_OFFSET, CONTENT_SIZE);
    MockContainer::TearDown();
}

/**
 * @tc.name: CheckBoxGroupMeasureContentTest001
 * @tc.desc: Test CheckBoxGroup MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupMeasureContentTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupLayoutAlgorithm.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, geometryNode, AccessibilityManager::MakeRefPtr<LayoutProperty>());
    auto checkBoxGroupLayoutAlgorithm = AceType::MakeRefPtr<CheckBoxGroupLayoutAlgorithm>();
    ASSERT_NE(checkBoxGroupLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: ret is equal to TEST_SIZE_100.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ret = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_100);
}

/**
 * @tc.name: CheckBoxGroupLayoutPolicyIsMatchParentTest001
 * @tc.desc: Test CheckBoxGroup LayoutPolicyIsMatchParent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupLayoutPolicyIsMatchParentTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupLayoutAlgorithm.
     * @tc.expected: step1. Create successfully.
     */
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(nullptr, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
    auto checkBoxGroupLayoutAlgorithm = AceType::MakeRefPtr<CheckBoxGroupLayoutAlgorithm>();
    ASSERT_NE(checkBoxGroupLayoutAlgorithm, nullptr);
    auto layoutPolicy = checkBoxGroupLayoutAlgorithm->GetLayoutPolicy(&layoutWrapper);

    /**
     * @tc.steps: step2. call LayoutPolicyIsMatchParent function.
     * @tc.expected: step2. ret is equal to TEST_SIZE_0.
     */
    LayoutConstraintF contentConstraint;
    auto ret = checkBoxGroupLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_0);

    /**
     * @tc.steps: step3. set layoutPolicy->widthLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step3. ret is equal to TEST_SIZE_100.
     */
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    ret = checkBoxGroupLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_100);

    /**
     * @tc.steps: step4. set selfIdealSize.height_ to TEST_HEIGHT_60.
     * @tc.expected: step4. ret is equal to TEST_SIZE_60.
     */
    contentConstraint.selfIdealSize.SetHeight(TEST_HEIGHT_60);
    ret = checkBoxGroupLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_60);

    /**
     * @tc.steps: step5. set layoutPolicy->heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step5. ret is equal to TEST_SIZE_200.
     */
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicy->heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    ret = checkBoxGroupLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step6. set selfIdealSize.width_ to TEST_WIDTH_50.
     * @tc.expected: step6. ret is equal to TEST_SIZE_50.
     */
    contentConstraint.selfIdealSize.SetWidth(TEST_WIDTH_50);
    ret = checkBoxGroupLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_50);

    /**
     * @tc.steps: step7. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step7. ret is equal to TEST_SIZE_100.
     */
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicy->heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    ret = checkBoxGroupLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_100);
}

/**
 * @tc.name: CheckBoxGroupEventTest003
 * @tc.desc: Test CheckBoxGroup onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CheckBoxGroupEventTest003, TestSize.Level1)
{
    auto frameNode = CheckBoxGroupModelNG::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    bool isSelected = false;
    auto onChange = [&isSelected](bool select) { isSelected = select; };
    CheckBoxGroupModelNG::SetOnChange(node, onChange);

    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    CheckboxGroupResult groupResult(
        std::vector<std::string> {}, int(CheckBoxGroupPaintProperty::SelectStatus::ALL));
    eventHub->UpdateChangeEvent(&groupResult);
    EXPECT_EQ(isSelected, true);
}

/**
 * @tc.name: ColorTypeToString
 * @tc.desc: test ColorTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, ColorTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test color type to string conversion.
     * @tc.expected: step1. Conversion returns correct string values.
     */
    std::vector<std::pair<CheckBoxGroupColorType, std::string>> types = {
        { CheckBoxGroupColorType::SELECTED_COLOR, "SelectedColor" },
        { CheckBoxGroupColorType::UN_SELECTED_COLOR, "UnSelectedColor" },
        { static_cast<CheckBoxGroupColorType>(2), "Unknown" } };
    for (const auto& [type, val] : types) {
        auto ret = CheckBoxGroupModelNG::ColorTypeToString(type);
        EXPECT_EQ(val, ret);
    }
}

/**
 * @tc.name: CreateWithColorResourceObj
 * @tc.desc: Test CreateWithColorResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, CreateWithColorResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroup frame node.
     * @tc.expected: step1. Frame node is not null.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create color resource object and verify resource manager.
     * @tc.expected: step2. Resource is added to manager.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    checkBoxGroupModelNG.CreateWithColorResourceObj(resObj, CheckBoxGroupColorType::SELECTED_COLOR);

    std::string key = "checkboxgroup" + CheckBoxGroupModelNG::ColorTypeToString(CheckBoxGroupColorType::SELECTED_COLOR);
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);

    /**
     * @tc.steps: step3. Create another color resource object with parameters.
     * @tc.expected: step3. Resource is added to manager.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(1, 10001, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    checkBoxGroupModelNG.CreateWithColorResourceObj(resObjWithParams, CheckBoxGroupColorType::UN_SELECTED_COLOR);
    key = "checkboxgroup" + CheckBoxGroupModelNG::ColorTypeToString(CheckBoxGroupColorType::UN_SELECTED_COLOR);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);
}

/**
 * @tc.name: UpdateComponentColor
 * @tc.desc: Test UpdateComponentColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, UpdateComponentColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroup frame node and get necessary properties.
     * @tc.expected: step1. Frame node and properties are not null.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step2. Update component color with different types.
     * @tc.expected: step2. Color properties are updated correctly.
     */
    checkBoxGroupModelNG.UpdateComponentColor(frameNode, static_cast<CheckBoxGroupColorType>(2), Color::RED);
    auto ret = paintProperty->GetCheckBoxGroupSelectedColor();
    EXPECT_FALSE(ret.has_value());
    checkBoxGroupModelNG.UpdateComponentColor(frameNode, CheckBoxGroupColorType::SELECTED_COLOR, Color::RED);
    ret = paintProperty->GetCheckBoxGroupSelectedColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);
    checkBoxGroupModelNG.UpdateComponentColor(frameNode, CheckBoxGroupColorType::UN_SELECTED_COLOR, Color::RED);
    ret = paintProperty->GetCheckBoxGroupUnSelectedColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);
}

/**
 * @tc.name: ResetComponentColor
 * @tc.desc: Test ResetComponentColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTestNG, ResetComponentColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroup frame node and get necessary properties.
     * @tc.expected: step1. Frame node and properties are not null.
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(GROUP_NAME);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxGroupPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto theme = pipelineContext->GetTheme<CheckboxTheme>();
    ASSERT_NE(theme, nullptr);

    /**
     * @tc.steps: step2. Reset component color with different types.
     * @tc.expected: step2. Color properties are reset to theme values.
     */
    checkBoxGroupModelNG.ResetComponentColor(frameNode, static_cast<CheckBoxGroupColorType>(2));
    auto ret = paintProperty->GetCheckBoxGroupSelectedColor();
    EXPECT_FALSE(ret.has_value());
    checkBoxGroupModelNG.ResetComponentColor(frameNode, CheckBoxGroupColorType::SELECTED_COLOR);
    ret = paintProperty->GetCheckBoxGroupSelectedColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), theme->GetActiveColor());
    checkBoxGroupModelNG.ResetComponentColor(frameNode, CheckBoxGroupColorType::UN_SELECTED_COLOR);
    ret = paintProperty->GetCheckBoxGroupUnSelectedColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), theme->GetInactiveColor());
}
} // namespace OHOS::Ace::NG
