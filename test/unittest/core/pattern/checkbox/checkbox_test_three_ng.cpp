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

#include "gtest/gtest.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
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
#include "ui/properties/ui_material.h"

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
const NG::PaddingProperty newArgs = NG::PaddingProperty();
const Color BOARD_COLOR = Color::BLUE;
const Color CHECK_COLOR = Color::WHITE;
const Color BORDER_COLOR = Color::GRAY;
const Color SHADOW_COLOR = Color::BLUE;
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const SizeF CONTENT_SIZE2 = SizeF(-7000.0, 400.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
constexpr Dimension CHECK_MARK_SIZE_INCORRECT_VALUE = Dimension(-1.0);
RefPtr<PipelineContext> pipeline = nullptr;
const SizeF TEST_SIZE_0 = SizeF(0.0f, 0.0f);
const SizeF TEST_SIZE_100_200 = SizeF(100.0f, 200.0f);
const SizeF TEST_SIZE_100 = SizeF(100.0f, 100.0f);
const SizeF TEST_SIZE_200 = SizeF(200.0f, 200.0f);
const SizeF TEST_SIZE_50 = SizeF(50.0f, 50.0f);
const SizeF TEST_SIZE_60 = SizeF(60.0f, 60.0f);
} // namespace

class CheckBoxThreeTestNG : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    CheckboxBuilderFunc CheckboxBuilder();
};

void CheckBoxThreeTestNG::SetUpTestSuite()
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

void CheckBoxThreeTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

CheckboxBuilderFunc CheckBoxThreeTestNG::CheckboxBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}


/**
 * @tc.name: CheckBoxAccessibilityPropertyTestNg001
 * @tc.desc: Test the IsCheckable property of CheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxAccessibilityPropertyTestNg001, TestSize.Level1)
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
HWTEST_F(CheckBoxThreeTestNG, CheckBoxAccessibilityPropertyTestNg002, TestSize.Level1)
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
HWTEST_F(CheckBoxThreeTestNG, CheckBoxAccessibilityPropertyTestNg003, TestSize.Level1)
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
HWTEST_F(CheckBoxThreeTestNG, CheckBoxUpdateChangeEventTest001, TestSize.Level1)
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
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPatternTest031, TestSize.Level1)
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
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPatternTest032, TestSize.Level1)
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
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
}

/**
 * @tc.name: CheckBoxPaintMethodTest006
 * @tc.desc: Test CheckBox PaintMethod DrawCheck.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPaintMethodTest006, TestSize.Level1)
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
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR, SizeF(), OffsetF(), 0.0, 0.0);
    CheckBoxPaintMethod checkBoxPaintMethod;
    checkBoxPaintMethod.checkboxModifier_ = checkBoxModifier;;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    RSPen pen;
    RSPen shadowPen = RSPen(pen);
    checkBoxPaintMethod.checkboxModifier_->checkStroke_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(2.0f);
    checkBoxPaintMethod.checkboxModifier_->strokeSize_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(2.0f);
    checkBoxPaintMethod.checkboxModifier_->DrawCheck(canvas, CONTENT_OFFSET, pen, shadowPen, CONTENT_SIZE);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test on color configuration update.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, OnColorConfigurationUpdate001, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    ASSERT_NE(checkBoxTheme, nullptr);
    checkBoxTheme->activeColor_ = Color::BLACK;
    checkBoxTheme->inactiveColor_ = Color::BLACK;
    checkBoxTheme->pointColor_ = Color::BLACK;
    pattern->OnColorConfigurationUpdate();
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelectedColor(), Color::BLACK);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxUnSelectedColor(), Color::BLACK);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxCheckMarkColor(), Color::BLACK);
}

/**
 * @tc.name: CheckBoxPatternTest033
 * @tc.desc: Test the distributed capability of CheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPatternTest033, TestSize.Level1)
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

/**
 * @tc.name: CheckBoxPaintPropertyTest003
 * @tc.desc: Set CheckBox value into CheckBoxPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPaintPropertyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Set parameters to CheckBox property
     */
    checkBoxModelNG.SetCheckboxStyle(CheckBoxStyle::CIRCULAR_STYLE);

    /**
     * @tc.steps: step3. Get paint property and get CheckBox property
     * @tc.expected: Check the CheckBox property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelectedStyle(), CheckBoxStyle::CIRCULAR_STYLE);
}

/**
 * @tc.name: CheckBoxPatternTest035
 * @tc.desc: Test CheckBox CheckBoxPattern::CreateNodePaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPatternTest035, TestSize.Level1)
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
}

/**
 * @tc.name: CheckBoxPaintMethodTest007
 * @tc.desc: Test CheckBox PaintMethod PaintCheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPaintMethodTest007, TestSize.Level1)
{
    /**
     * @tc.steps: create GeometryNode
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    /**
     * @tc.steps: create CheckBoxPaintProperty
     */
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    /**
     * @tc.steps: create PaintWrapper of CheckBoxPaintProperty
     */
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    /**
     *  @tc.steps: create CheckBoxModifier
     */
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR, SizeF(), OffsetF(), 0.0, 0.0);
    CheckBoxPaintMethod checkBoxPaintMethod;
    checkBoxPaintMethod.checkboxModifier_ = checkBoxModifier;;
    /**
     * @tc.steps: Set parameters to CheckBox property
     */
    checkBoxPaintMethod.checkboxModifier_->SetCheckboxStyle(CheckBoxStyle::CIRCULAR_STYLE);
    /**
     * @tc.case: case. CheckBoxPaintMethod's PaintCheckBox will be called.
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    checkBoxPaintMethod.checkboxModifier_->PaintCheckBox(canvas, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxPaintMethodTest008
 * @tc.desc: Test checkbox method UpdateContentModifier will update incorrect value into modifier.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPaintMethodTest008, TestSize.Level1)
{
    /**
     * @tc.steps: create GeometryNode
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    
    /**
     * @tc.steps: Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: Get paint property and get CheckBox property
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    if (checkBoxPaintProperty) {
        checkBoxPaintProperty->UpdateCheckBoxCheckMarkSize(CHECK_MARK_SIZE_INCORRECT_VALUE);
    }
    checkBoxPaintProperty->SetHost(frameNode);
    /**
     * @tc.steps: Get EventHub and Set hover effect
     */
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputEventHub = eventHub->GetOrCreateInputEventHub();
    inputEventHub->SetHoverEffect(HoverEffectType::UNKNOWN);
    
    /**
     * @tc.steps: create PaintWrapper of CheckBoxPaintProperty
     */
    auto renderContext_ = AceType::MakeRefPtr<RenderContext>();
    renderContext_->host_ = std::move(frameNode);
    WeakPtr<RenderContext> renderContext = AceType::WeakClaim(AceType::RawPtr(renderContext_));
    PaintWrapper paintWrapper(renderContext, geometryNode, checkBoxPaintProperty);
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR, SizeF(), OffsetF(), 0.0, 0.0);
    ASSERT_NE(checkBoxModifier, nullptr);
    /**
     * @tc.case: case. CheckBoxPaintMethod's UpdateContentModifier will be called.
     */
    CheckBoxPaintMethod checkBoxPaintMethod;
    checkBoxPaintMethod.checkboxModifier_ = checkBoxModifier;;
    checkBoxPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(checkBoxPaintMethod.checkboxModifier_->strokeSize_->Get(), static_cast<float>(CONTENT_SIZE.Width()));
    EXPECT_EQ(checkBoxPaintMethod.checkboxModifier_->hoverEffectType_, HoverEffectType::AUTO);
}

/**
 * @tc.name: CheckBoxPaintMethodTest009
 * @tc.desc: Test checkbox method CheckBoxPaintProperty::Clone() will update incorrect value into modifier.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPaintMethodTest009, TestSize.Level1)
{
    /**
     * @tc.steps: Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. Get paint property and get CheckBox property
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->SetHost(frameNode);
     /**
     * @tc.case: case. CheckBoxPaintProperty's Clone will be called.
     */
    auto cloneCheckBoxPaintProperty = checkBoxPaintProperty->Clone();
    EXPECT_NE(cloneCheckBoxPaintProperty, nullptr);
}

/**
 * @tc.name: CheckBoxPaintMethodTest010
 * @tc.desc: Test CheckBox PaintMethod PaintCheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPaintMethodTest010, TestSize.Level1)
{
    /**
     * @tc.steps: create GeometryNode
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    /**
     * @tc.steps: create CheckBoxPaintProperty
     */
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    /**
     * @tc.steps: create PaintWrapper of CheckBoxPaintProperty
     */
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    /**
     * @tc.steps: create CheckBoxModifier
     */
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR, SizeF(), OffsetF(), 0.0, 0.0);
    /**
     * @tc.steps: create CheckBoxPaintMethod
     */
    CheckBoxPaintMethod checkBoxPaintMethod;
    checkBoxPaintMethod.checkboxModifier_ = checkBoxModifier;;
    /**
     * @tc.steps: Set parameters to CheckBox property
     */
    checkBoxPaintMethod.checkboxModifier_->SetCheckboxStyle(CheckBoxStyle::CIRCULAR_STYLE);
    /**
     * @tc.case: case. CheckBoxPaintMethod's PaintCheckBox will be called.
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    checkBoxPaintMethod.checkboxModifier_->PaintCheckBox(canvas, CONTENT_OFFSET, CONTENT_SIZE2);
}

/**
 * @tc.name: CheckBoxPaintMethodTest011
 * @tc.desc: Test CheckBox PaintMethod PaintCheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPaintMethodTest011, TestSize.Level1)
{
    /**
     * @tc.steps: create GeometryNode
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    /**
     * @tc.steps: create CheckBoxPaintProperty
     */
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    /**
     * @tc.steps: create PaintWrapper of CheckBoxPaintProperty
     */
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    /**
     * @tc.steps: create CheckBoxModifier
     */
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        false, BOARD_COLOR, CHECK_COLOR, BORDER_COLOR, SHADOW_COLOR, SizeF(), OffsetF(), 0.0, 0.0);
    /**
     * @tc.steps: create CheckBoxPaintMethod
     */
    CheckBoxPaintMethod checkBoxPaintMethod;
    checkBoxPaintMethod.checkboxModifier_ = checkBoxModifier;;
    /**
     * @tc.steps: Set parameters to CheckBox property
     */
    checkBoxPaintMethod.checkboxModifier_->SetCheckboxStyle(CheckBoxStyle::CIRCULAR_STYLE);
    /**
     * @tc.case: case. CheckBoxPaintMethod's PaintCheckBox code when !enabled_->Get()
     */
    Testing::MockCanvas canvas;
    checkBoxPaintMethod.checkboxModifier_->enabled_->Set(false);
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    checkBoxPaintMethod.checkboxModifier_->PaintCheckBox(canvas, CONTENT_OFFSET, CONTENT_SIZE2);
}

/**
 * @tc.name: CheckBoxPaintMethodTest012
 * @tc.desc: Test CheckBox PaintMethod PaintCheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPaintMethodTest012, TestSize.Level1)
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
    checkBoxPaintMethod.checkboxModifier_->SetCheckboxStyle(CheckBoxStyle::CIRCULAR_STYLE);
    checkBoxPaintMethod.checkboxModifier_->SetIsSelect(false);
    checkBoxPaintMethod.checkboxModifier_->SetIsFocused(true);
    checkBoxPaintMethod.checkboxModifier_->SetHasUnselectedColor(false);
    checkBoxPaintMethod.checkboxModifier_->enabled_->Set(false);
    checkBoxPaintMethod.checkboxModifier_->PaintCheckBox(canvas, CONTENT_OFFSET, CONTENT_SIZE);
}

/**
 * @tc.name: CheckBoxPaintPropertyTest004
 * @tc.desc: Test CheckBoxPaintProperty's Reset.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPaintPropertyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    /**
     * @tc.steps: step2. Set parameters to CheckBox property
     */
    checkBoxModelNG.SetCheckboxStyle(CheckBoxStyle::CIRCULAR_STYLE);

    /**
     * @tc.steps: step3. Get paint property and get CheckBox property
     * @tc.expected: Check the CheckBox property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    /**
     * @tc.case: case. CheckBoxPaintProperty's reset will be called.
     */
    checkBoxPaintProperty->Reset();
    EXPECT_EQ(checkBoxPaintProperty->HasCheckBoxSelectedStyle(), false);
}

/**
 * @tc.name: CheckBoxPatternTest002
 * @tc.desc: CheckBox test Select and ClearSelection.
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    pattern->lastSelect_ = false;
    pattern->SetAccessibilityAction();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<CheckBoxAccessibilityProperty>();
    EXPECT_TRUE(accessibilityProperty->ActActionSelect());

    pattern->lastSelect_ = true;
    pattern->MarkIsSelected(true);
    EXPECT_TRUE(pattern->lastSelect_ == true);
}

HWTEST_F(CheckBoxThreeTestNG, OnAfterModifyDone003, TestSize.Level1)
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
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    EXPECT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Set CheckBox pattern variable and call Init methods
     * @tc.expected: GetTouchType is UP
     */
    pattern->InitMouseEvent();
    EXPECT_NE(pattern->mouseEvent_, nullptr);
    pattern->InitMouseEvent();
    pattern->mouseEvent_->GetOnHoverEventFunc()(true);
    pattern->InitTouchEvent();
    EXPECT_NE(pattern->touchListener_, nullptr);
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    pattern->touchListener_->GetTouchEventCallback()(info);
    pattern->InitTouchEvent();
    EXPECT_TRUE(touchInfo1.GetTouchType() == TouchType::UP);
}

HWTEST_F(CheckBoxThreeTestNG, OnAfterModifyDone0024, TestSize.Level1)
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
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    EXPECT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto stageManager = pipelineContext->GetStageManager();
    auto pageNode = stageManager->GetPageById(host->GetPageId());
    EXPECT_FALSE(pattern->lastSelect_);
}

HWTEST_F(CheckBoxThreeTestNG, OnAfterModifyDone009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pattern
     */
    auto checkBoxPattern = AceType::MakeRefPtr<CheckBoxPattern>();
    auto frameNode1 = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<CheckBoxPattern>());
    frameNode1->hostPageId_ = 10;
    checkBoxPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode1));
    checkBoxPattern->prePageId_ = 10;

    /**
     * @tc.steps: step2. create stageManager and child
     */
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("stageNode", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> child = AceType::MakeRefPtr<FrameNode>("child", 10, AceType::MakeRefPtr<Pattern>());
    child->hostPageId_ = 10;
    stageNode->AddChild(child);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_NE(stageManager, nullptr);
    stageManager->stageNode_ = stageNode;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->stageManager_ = stageManager;

    /**
     * @tc.steps: step3. Call CheckPageNode
     */
    checkBoxPattern->CheckPageNode();
    EXPECT_EQ(checkBoxPattern->GetPrePageId(), child->GetId());

    /**
     * @tc.steps: step4. set child nodeId != 10 and Call CheckPageNode
     * @tc.expected: prePageId_ is update with nodeId_
     */
    auto checkBoxEvent = AceType::MakeRefPtr<CheckBoxEventHub>();
    checkBoxEvent->SetGroupName(GROUP_NAME);
    frameNode1->eventHub_ = checkBoxEvent;
    child->eventHub_ = AceType::MakeRefPtr<NG::PageEventHub>();
    child->nodeId_ = 2;
    checkBoxPattern->CheckPageNode();
    EXPECT_EQ(checkBoxPattern->prePageId_, child->nodeId_);
}

HWTEST_F(CheckBoxThreeTestNG, OnAfterModifyDone0027, TestSize.Level1)
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
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnAfterModifyDone();
    auto host = pattern->GetHost();
    auto inspectorId = host->GetInspectorId().value_or("");
    EXPECT_TRUE(inspectorId.empty());

    host->UpdateInspectorId("test");
    pattern->OnAfterModifyDone();
    EXPECT_FALSE(host->GetInspectorIdValue().empty());
}

HWTEST_F(CheckBoxThreeTestNG, OnAfterModifyDone0062, TestSize.Level1)
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
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    EXPECT_NE(pattern, nullptr);

    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    FrameNode& ref = *stageNode;
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext->stageManager_, nullptr);
    auto child = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    pipelineContext->stageManager_->stageNode_ = frameNode;
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<PageEventHub>();
    EXPECT_NE(eventHub, nullptr);
    child->eventHub_ = eventHub;
    frameNode->AddChild(child);
    pattern->OnDetachFromFrameNode(&ref);
    EXPECT_NE(stageManager->stageNode_, nullptr);
}

HWTEST_F(CheckBoxThreeTestNG, OnAfterModifyDone0032, TestSize.Level1)
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
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    EXPECT_NE(pattern, nullptr);

    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_NE(stageManager, nullptr);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->stageManager_ = stageManager;
    EXPECT_NE(pipelineContext->stageManager_, nullptr);

    auto child = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    pipelineContext->stageManager_->stageNode_ = frameNode;
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<PageEventHub>();
    EXPECT_NE(eventHub, nullptr);

    child->eventHub_ = eventHub;
    frameNode->AddChild(child);
    pattern->preGroup_ = "";
    pattern->UpdateState();
    EXPECT_TRUE(pattern->preGroup_ != "");
}

/**
 * @tc.name: CheckBoxPatternTest0118
 * @tc.desc: Test CheckBoxGroupIsTrue.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxThreeTestNG, CheckBoxPatternTest0118, TestSize.Level1)
{
    /*
     * @tc.steps: step1. create checkBoxFrameNode and some parameters.
     */
    auto checkBoxFrameNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<CheckBoxPattern>());
    auto paintPropertyTemp = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    paintPropertyTemp->UpdateCheckBoxSelect(true);
    checkBoxFrameNode->paintProperty_ = paintPropertyTemp;
    auto checkBoxeventHub = AceType::MakeRefPtr<CheckBoxEventHub>();
    checkBoxeventHub->SetGroupName(GROUP_NAME);
    checkBoxFrameNode->eventHub_ = checkBoxeventHub;

    /*
     * @tc.steps: step2. create checkBoxPattern.
     */
    auto checkBoxPattern = AceType::MakeRefPtr<CheckBoxPattern>();
    checkBoxPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(checkBoxFrameNode));
    EXPECT_NE(checkBoxPattern->GetHost(), nullptr);

    /*
     * @tc.steps: step3. create stageManager.
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

    /*
     * @tc.steps: step4. create list with Children
     */
    auto checkBoxGroupPattern = AceType::MakeRefPtr<CheckBoxGroupPattern>();
    checkBoxPattern->groupManager_ = GroupManager::GetGroupManager();
    checkBoxGroupPattern->groupManager_ = GroupManager::GetGroupManager();
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>(V2::CHECKBOXGROUP_ETS_TAG, 2, checkBoxGroupPattern);
    auto groupPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    groupPaintProperty->isCheckBoxCallbackDealed_ = true;
    frameNode2->paintProperty_ = groupPaintProperty;
    groupManager->AddCheckBoxGroup(GROUP_NAME, frameNode2);
    auto frameNode3 = AceType::MakeRefPtr<FrameNode>("test3", 3, AceType::MakeRefPtr<Pattern>());
    auto paintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    paintProperty->UpdateCheckBoxSelect(true);
    frameNode3->paintProperty_ = paintProperty;
    groupManager->AddCheckBoxToGroup(GROUP_NAME, frameNode3);
    ElementRegister::GetInstance()->AddReferenced(2, frameNode2);
    ElementRegister::GetInstance()->AddReferenced(3, frameNode3);
    ElementRegister::GetInstance()->AddReferenced(4, nullptr);
    ElementRegister::GetInstance()->AddReferenced(5, checkBoxFrameNode);

    /*
     * @tc.steps: step5. call CheckBoxGroupIsTrue,
     * @tc.expected: groupPaintProperty.GetIsCheckBoxCallbackDealed() is true and exit error
     */
    checkBoxPattern->CheckBoxGroupIsTrue();
    EXPECT_TRUE(groupPaintProperty->GetIsCheckBoxCallbackDealed());

    /*
     * @tc.steps: step6. set isCheckBoxCallbackDealed_ is false and call CheckBoxGroupIsTrue
     * @tc.expected: selectdStatus is ALL
     */
    groupPaintProperty->isCheckBoxCallbackDealed_ = false;
    checkBoxPattern->CheckBoxGroupIsTrue();
    EXPECT_EQ(groupPaintProperty->GetSelectStatus(), CheckBoxGroupPaintProperty::SelectStatus::NONE);
    EXPECT_TRUE(groupPaintProperty->isCheckBoxCallbackDealed_);

    /*
     * @tc.steps: step7. set CheckBoxSelect is false and call CheckBoxGroupIsTrue
     * @tc.expected: selectdStatus is PART
     */
    groupPaintProperty->isCheckBoxCallbackDealed_ = false;
    paintPropertyTemp->UpdateCheckBoxSelect(false);
    checkBoxPattern->CheckBoxGroupIsTrue();
    EXPECT_EQ(groupPaintProperty->GetSelectStatus(), CheckBoxGroupPaintProperty::SelectStatus::NONE);
}
} // namespace OHOS::Ace::NG
