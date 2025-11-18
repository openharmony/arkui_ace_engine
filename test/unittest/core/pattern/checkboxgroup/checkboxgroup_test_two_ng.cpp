/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/layout/layout_wrapper_node.h"
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
const SizeF TEST_SIZE_40 = SizeF(40.0f, 40.0f);
const SizeF TEST_SIZE_50 = SizeF(50.0f, 50.0f);
const SizeF TEST_SIZE_60 = SizeF(60.0f, 60.0f);
constexpr float TEST_WIDTH_50 = 50.0f;
constexpr float TEST_HEIGHT_60 = 60.0f;
constexpr float TEST_HORIZONPADDING = 5.0f;
} // namespace

class CheckBoxGroupTwoTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CheckBoxGroupTwoTestNG::SetUpTestCase()
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
void CheckBoxGroupTwoTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}
void CheckBoxGroupTwoTestNG::SetUp() {}
void CheckBoxGroupTwoTestNG::TearDown() {}
CheckBoxGroupModifier::Parameters CheckBoxGroupCreateDefModifierParamTwo()
{
    CheckBoxGroupModifier::Parameters parameters = { BORDER_WIDTH, BORDER_RADIUS, CHECK_STROKE, CHECKMARK_PAINTSIZE,
        HOVER_DURATION, HOVER_TO_TOUCH_DURATION, POINT_COLOR, ACTIVE_COLOR, INACTIVE_COLOR, SHADOW_COLOR,
        CLICK_EFFECT_COLOR, HOVER_COLOR, INACTIVE_POINT_COLOR, HOVER_RADIUS, HORIZONTAL_PADDING, VERTICAL_PADDING,
        SHADOW_WIDTH_FORUPDATE, UIStatus::UNSELECTED, PADDING_SIZE, PADDING_SIZE, false,
        CheckBoxGroupPaintProperty::SelectStatus::NONE };

    return parameters;
}

/**
 * @tc.name: CheckBoxGroupModifierTest001
 * @tc.desc: Test CheckBoxGroupModifier PaintCheckBox method in different situation.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupModifier.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParamTwo();
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupModifierTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupModifier.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParamTwo();
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupModifierTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupModifier.
     * @tc.expected: Create successfully.
     */
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParamTwo();
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupLayoutAlgorithmTest001, TestSize.Level1)
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
 * @tc.name: CheckBoxGroupAccessibilityPropertyTestNg003
 * @tc.desc: Test GetCollectionItemCounts property of CheckBoxGroup.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupAccessibilityPropertyTestNg003, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxUpdateChangeEventTest001, TestSize.Level1)
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
 * @tc.name: CheckBoxGroupPatternTest024
 * @tc.desc: Test CheckBoxGroupPattern UpdateCheckBoxStatus.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupPatternTest024, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupPatternTest025, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, OnColorConfigurationUpdate001, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupPatternTest026, TestSize.Level1)
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
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParamTwo();
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupPatternTest027, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupPaintPropertyTest028, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupPaintPropertyTest029, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupPatternTest030, TestSize.Level1)
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

    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParamTwo();
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupNGTest031, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupNGTest032, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupNGTest033, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupNGTest034, TestSize.Level1)
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
    CheckBoxGroupModifier::Parameters parameters = CheckBoxGroupCreateDefModifierParamTwo();
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupMeasureContentTest001, TestSize.Level1)
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
 * @tc.name: CheckBoxGroupMeasureContentTest002
 * @tc.desc: Test CheckBoxGroup MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupMeasureContentTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupLayoutAlgorithm.
     * @tc.expected: Create successfully.
     */
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(nullptr, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
    auto checkBoxGroupLayoutAlgorithm = AceType::MakeRefPtr<CheckBoxGroupLayoutAlgorithm>();
    ASSERT_NE(checkBoxGroupLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: ret is equal to TEST_SIZE_100.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_50);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_HEIGHT_60;
    checkBoxGroupLayoutAlgorithm->horizontalPadding_ = TEST_HORIZONPADDING;
    auto ret = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_50);

    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_WIDTH_50;
    checkBoxGroupLayoutAlgorithm->defaultHeight_ = TEST_HEIGHT_60;
    ret = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_100_200);
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_WIDTH_50;
    checkBoxGroupLayoutAlgorithm->defaultHeight_ = TEST_HEIGHT_60;
    ret = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);
}

/**
 * @tc.name: CheckBoxGroupMeasureContentTest003
 * @tc.desc: Test CheckBoxGroup MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupMeasureContentTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupLayoutAlgorithm.
     * @tc.expected: Create successfully.
     */
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(nullptr, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
    auto checkBoxGroupLayoutAlgorithm = AceType::MakeRefPtr<CheckBoxGroupLayoutAlgorithm>();
    ASSERT_NE(checkBoxGroupLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: ret is equal to TEST_SIZE_100.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_50);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_HEIGHT_60;
    checkBoxGroupLayoutAlgorithm->horizontalPadding_ = TEST_HORIZONPADDING;
    auto ret = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_50);

    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_100_200);
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_WIDTH_50;
    checkBoxGroupLayoutAlgorithm->defaultHeight_ = TEST_HEIGHT_60;
    ret = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_WIDTH_50;
    checkBoxGroupLayoutAlgorithm->defaultHeight_ = TEST_HEIGHT_60;
    ret = checkBoxGroupLayoutAlgorithm->LayoutPolicyIsFixAtIdelSize(contentConstraint, layoutPolicyProperty);
    EXPECT_NE(ret, TEST_SIZE_200);
}

/**
 * @tc.name: CheckBoxGroupMeasureContentTest004
 * @tc.desc: Test CheckBoxGroup MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupMeasureContentTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupLayoutAlgorithm.
     * @tc.expected: Create successfully.
     */
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(nullptr, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
    auto checkBoxGroupLayoutAlgorithm = AceType::MakeRefPtr<CheckBoxGroupLayoutAlgorithm>();
    ASSERT_NE(checkBoxGroupLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. set widthLayoutPolicy_ and heightLayoutPolicy_ to WRAP_CONTENT.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_HEIGHT_60;
    checkBoxGroupLayoutAlgorithm->horizontalPadding_ = TEST_HORIZONPADDING;
    auto ret = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_WIDTH_50;
    checkBoxGroupLayoutAlgorithm->defaultHeight_ = TEST_HEIGHT_60;
    ret = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_60);
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_WIDTH_50;
    checkBoxGroupLayoutAlgorithm->defaultHeight_ = TEST_HEIGHT_60;
    ret = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);
}

/**
 * @tc.name: CheckBoxGroupMeasureContentTest005
 * @tc.desc: Test CheckBoxGroup MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupMeasureContentTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBoxGroupLayoutAlgorithm.
     * @tc.expected: Create successfully.
     */
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(nullptr, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
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
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_HEIGHT_60;
    checkBoxGroupLayoutAlgorithm->horizontalPadding_ = TEST_HORIZONPADDING;
    auto ret = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_60);
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_WIDTH_50;
    checkBoxGroupLayoutAlgorithm->defaultHeight_ = TEST_HEIGHT_60;
    ret = checkBoxGroupLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    checkBoxGroupLayoutAlgorithm->defaultWidth_ = TEST_WIDTH_50;
    checkBoxGroupLayoutAlgorithm->defaultHeight_ = TEST_HEIGHT_60;
    ret = checkBoxGroupLayoutAlgorithm->LayoutPolicyIsFixAtIdelSize(contentConstraint, layoutPolicyProperty);
    EXPECT_NE(ret, TEST_SIZE_200);
}

/**
 * @tc.name: CheckBoxGroupLayoutPolicyIsMatchParentTest001
 * @tc.desc: Test CheckBoxGroup LayoutPolicyIsMatchParent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupLayoutPolicyIsMatchParentTest001, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, CheckBoxGroupEventTest003, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, ColorTypeToString, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, CreateWithColorResourceObj, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, UpdateComponentColor, TestSize.Level1)
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
HWTEST_F(CheckBoxGroupTwoTestNG, ResetComponentColor, TestSize.Level1)
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