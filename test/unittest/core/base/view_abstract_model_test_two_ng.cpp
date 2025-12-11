/*
 * Copyright (c) 2024 iSoftStone Information Technology (Group) Co.,Ltd.
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
#define protected public
#define private public

#include "test/mock/base/mock_subwindow.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

#undef private
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    ViewAbstractModelNG viewAbstractModelNG;
    RefPtr<MockTaskExecutor> MOCK_TASK_EXECUTOR;
    int32_t flag = 0;
    const std::string TEST_TEXT_HINT = "testTextHint";
    const std::string TEST_STATE_DESCRIPTION = "testStateDescription";
    constexpr size_t STATE_DESCRIPTION_MAX_SIZE = 1000;
    constexpr int32_t TEST_NODE_ID = 1;
    const std::string VALUE_TAB = "TAB";
}; // namespace

class ViewAbstractModelTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestCase();
};

void ViewAbstractModelTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void ViewAbstractModelTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: SetBackgroundOptions001
 * @tc.desc: Test the background options
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetBackgroundOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create main frame node and push into view abstract.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);

    /**
     * @tc.steps: step2. init theme, pipeline and container.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);

    /**
     * @tc.steps: step3. init background build func and alignment.
     * @tc.expected: background function is successfully set.
     */
    auto mainFrameNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    Alignment alignment = Alignment::CENTER;
    auto buildFunc = [mainFrameNode]() { flag++; };
    viewAbstractModelNG.SetBackground(std::move(buildFunc));
    auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(targetNode, nullptr);
    EXPECT_NE(targetNode->builderFunc_, nullptr);

    /**
     * @tc.steps: step4. update background alignment.
     * @tc.expected: background alignment is successfully set.
     */
    auto renderContext = targetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    alignment = Alignment::TOP_CENTER;
    viewAbstractModelNG.SetBackgroundAlign(alignment);
    auto backgroundAlign = renderContext->GetBackgroundAlign().value_or(Alignment::BOTTOM_CENTER);
    EXPECT_EQ(backgroundAlign, alignment);

    /**
     * @tc.steps: step5. update background color.
     * @tc.expected: background alignment is successfully set.
     */
    Color color = Color::BLUE;
    viewAbstractModelNG.SetCustomBackgroundColor(color);
    auto customBackgroundColor = renderContext->GetCustomBackgroundColor().value_or(Color::TRANSPARENT);
    EXPECT_EQ(customBackgroundColor.GetValue(), color.GetValue());

    /**
     * @tc.steps: step6. update background flags.
     * @tc.expected: background flags is successfully set.
     */
    viewAbstractModelNG.SetIsTransitionBackground(true);
    EXPECT_TRUE(renderContext->GetIsTransitionBackground().value_or(false));
    viewAbstractModelNG.SetIsBuilderBackground(true);
    EXPECT_TRUE(renderContext->GetBuilderBackgroundFlag().value_or(false));

    /**
     * @tc.steps: step7. update background ignoresLayoutSafeAreaEdges.
     * @tc.expected: background ignoresLayoutSafeAreaEdges is successfully set.
     */
    viewAbstractModelNG.SetBackgroundIgnoresLayoutSafeAreaEdges(NG::LAYOUT_SAFE_AREA_EDGE_ALL);
    auto layoutProp = targetNode->GetLayoutProperty();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_EQ(layoutProp->GetBackgroundIgnoresLayoutSafeAreaEdges(), NG::LAYOUT_SAFE_AREA_EDGE_ALL);
}

/**
 * @tc.name: SetAccessibilitySelected001
 * @tc.desc: Test the SetAccessibilitySelected
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilitySelected001, TestSize.Level1)
{
    bool selected = true;
    bool resetValue = true;
    std::string tag = "uiNode1";
    int32_t nodeId = 1;
    auto frameNode = FrameNode::CreateFrameNode(
        tag, nodeId, AceType::MakeRefPtr<Pattern>());
    NG::ViewStackProcessor::GetInstance()->elementsStack_.push(frameNode);
    viewAbstractModelNG.SetAccessibilitySelected(selected, resetValue);
    EXPECT_FALSE(NG::ViewStackProcessor::GetInstance()
                     ->GetMainFrameNode()
                     ->GetOrCreateAccessibilityProperty()
                     ->isSelected_.has_value());

    resetValue = false;
    viewAbstractModelNG.SetAccessibilitySelected(selected, resetValue);
    EXPECT_EQ(
        NG::ViewStackProcessor::GetInstance()->GetMainFrameNode()->GetOrCreateAccessibilityProperty()->isSelected_,
        selected);
}

/**
 * @tc.name: SetAccessibilityChecked001
 * @tc.desc: Test the SetAccessibilityChecked
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityChecked001, TestSize.Level1)
{
    bool checked = true;
    bool resetValue = true;
    std::string tag = "uiNode1";
    int32_t nodeId = 1;
    auto frameNode = FrameNode::CreateFrameNode(
        tag, nodeId, AceType::MakeRefPtr<Pattern>());
    NG::ViewStackProcessor::GetInstance()->elementsStack_.push(frameNode);
    viewAbstractModelNG.SetAccessibilityChecked(checked, resetValue);
    EXPECT_FALSE(NG::ViewStackProcessor::GetInstance()
                     ->GetMainFrameNode()
                     ->GetOrCreateAccessibilityProperty()
                     ->checkedType_.has_value());

    resetValue = false;
    viewAbstractModelNG.SetAccessibilityChecked(checked, resetValue);
    EXPECT_EQ(
        NG::ViewStackProcessor::GetInstance()->GetMainFrameNode()->GetOrCreateAccessibilityProperty()->checkedType_,
        checked);
}

/**
 * @tc.name: SetAccessibilityScrollTriggerable001
 * @tc.desc: Test the SetAccessibilityScrollTriggerable
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityScrollTriggerable001, TestSize.Level1)
{
    bool triggerable = true;
    bool resetValue = true;
    std::string tag = "uiNode1";
    int32_t nodeId = 1;
    auto frameNode = FrameNode::CreateFrameNode(
        tag, nodeId, AceType::MakeRefPtr<Pattern>());
    NG::ViewStackProcessor::GetInstance()->elementsStack_.push(frameNode);
    viewAbstractModelNG.SetAccessibilityScrollTriggerable(triggerable, resetValue);
    EXPECT_TRUE(NG::ViewStackProcessor::GetInstance()
                    ->GetMainFrameNode()
                    ->GetOrCreateAccessibilityProperty()
                    ->isUserScrollTriggerable_);

    resetValue = false;
    viewAbstractModelNG.SetAccessibilityScrollTriggerable(triggerable, resetValue);
    EXPECT_TRUE(NG::ViewStackProcessor::GetInstance()
                    ->GetMainFrameNode()
                    ->GetOrCreateAccessibilityProperty()
                    ->isUserScrollTriggerable_);
}

/**
 * @tc.name: SetAccessibilityRole001
 * @tc.desc: Test the SetAccessibilityRole
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityRole001, TestSize.Level1)
{
    std::string role = "testRole";
    bool resetValue = true;
    std::string tag = "uiNode1";
    int32_t nodeId = 1;
    auto frameNode = FrameNode::CreateFrameNode(
        tag, nodeId, AceType::MakeRefPtr<Pattern>());
    NG::ViewStackProcessor::GetInstance()->elementsStack_.push(frameNode);
    viewAbstractModelNG.SetAccessibilityRole(role, resetValue);
    EXPECT_EQ(NG::ViewStackProcessor::GetInstance()
                  ->GetMainFrameNode()
                  ->GetOrCreateAccessibilityProperty()
                  ->accessibilityCustomRole_,
        "");

    resetValue = false;
    viewAbstractModelNG.SetAccessibilityRole(role, resetValue);
    EXPECT_EQ(NG::ViewStackProcessor::GetInstance()
                  ->GetMainFrameNode()
                  ->GetOrCreateAccessibilityProperty()
                  ->accessibilityCustomRole_,
        role);
}

/**
 * @tc.name: SetAccessibilityUseSamePage001
 * @tc.desc: Test the SetAccessibilityUseSamePage
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityUseSamePage001, TestSize.Level1)
{
    std::string tag = "uiNode1";
    std::string pageMode = "pageMode";
    int32_t nodeId = 1;
    FrameNode frameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    frameNode.GetOrCreateAccessibilityProperty()->SetAccessibilitySamePage(pageMode);

    viewAbstractModelNG.SetAccessibilityUseSamePage(&frameNode, pageMode);
    EXPECT_EQ(frameNode.GetOrCreateAccessibilityProperty()->accessibilityUseSamePage_, pageMode);

    pageMode = "testMode";
    viewAbstractModelNG.SetAccessibilityUseSamePage(&frameNode, pageMode);
    EXPECT_EQ(frameNode.GetOrCreateAccessibilityProperty()->accessibilityUseSamePage_, pageMode);
}

/**
 * @tc.name: SetAccessibilitySelected002
 * @tc.desc: Test the SetAccessibilitySelected
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilitySelected002, TestSize.Level1)
{
    std::string tag = "uiNode1";
    bool selected = true;
    bool resetValue = true;
    int32_t nodeId = 1;
    FrameNode frameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    frameNode.GetOrCreateAccessibilityProperty()->SetUserSelected(selected);

    viewAbstractModelNG.SetAccessibilitySelected(&frameNode, selected, resetValue);
    EXPECT_EQ(frameNode.GetOrCreateAccessibilityProperty()->isSelected_.has_value(), false);

    resetValue = false;
    viewAbstractModelNG.SetAccessibilitySelected(&frameNode, selected, resetValue);
    EXPECT_EQ(frameNode.GetOrCreateAccessibilityProperty()->isSelected_, selected);
}

/**
 * @tc.name: SetAccessibilityChecked002
 * @tc.desc: Test the SetAccessibilityChecked
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityChecked002, TestSize.Level1)
{
    std::string tag = "uiNode1";
    bool checked = true;
    bool resetValue = true;
    int32_t nodeId = 1;
    FrameNode frameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());

    frameNode.GetOrCreateAccessibilityProperty()->SetUserCheckedType(checked);
    viewAbstractModelNG.SetAccessibilityChecked(&frameNode, checked, resetValue);
    EXPECT_EQ(frameNode.GetOrCreateAccessibilityProperty()->checkedType_.has_value(), false);

    resetValue = false;
    viewAbstractModelNG.SetAccessibilityChecked(&frameNode, checked, resetValue);
    EXPECT_EQ(frameNode.GetOrCreateAccessibilityProperty()->checkedType_, checked);
}

/**
 * @tc.name: SetAccessibilityScrollTriggerable002
 * @tc.desc: Test the SetAccessibilityScrollTriggerable
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityScrollTriggerable002, TestSize.Level1)
{
    std::string tag = "uiNode1";
    bool triggerable = false;
    bool resetValue = true;
    int32_t nodeId = 1;
    FrameNode frameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    frameNode.GetOrCreateAccessibilityProperty()->SetUserScrollTriggerable(triggerable);
    viewAbstractModelNG.SetAccessibilityScrollTriggerable(&frameNode, triggerable, resetValue);
    EXPECT_NE(frameNode.GetOrCreateAccessibilityProperty()->isUserScrollTriggerable_, triggerable);

    resetValue = false;
    viewAbstractModelNG.SetAccessibilityScrollTriggerable(&frameNode, triggerable, resetValue);
    EXPECT_EQ(frameNode.GetOrCreateAccessibilityProperty()->isUserScrollTriggerable_, triggerable);
}

/**
 * @tc.name: SetAccessibilityRole002
 * @tc.desc: Test the SetAccessibilityRole
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityRole002, TestSize.Level1)
{
    std::string tag = "uiNode1";
    std::string role = "testRole";
    bool resetValue = true;
    int32_t nodeId = 1;
    FrameNode frameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    frameNode.GetOrCreateAccessibilityProperty()->SetAccessibilityCustomRole(role);
    viewAbstractModelNG.SetAccessibilityRole(&frameNode, role, resetValue);
    EXPECT_NE(frameNode.GetOrCreateAccessibilityProperty()->accessibilityCustomRole_, role);

    resetValue = false;
    viewAbstractModelNG.SetAccessibilityRole(&frameNode, role, resetValue);
    EXPECT_EQ(frameNode.GetOrCreateAccessibilityProperty()->accessibilityCustomRole_, role);
}

/**
 * @tc.name: SetAccessibilityTextHint001
 * @tc.desc: Test the SetAccessibilityTextHint
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityTextHint001, TestSize.Level1)
{
    std::string tag = "uiNode1";
    int32_t nodeId = 1;
    FrameNode frameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto accessibilityProperty = frameNode.GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetAccessibilityTextHint(TEST_TEXT_HINT);

    viewAbstractModelNG.SetAccessibilityTextHint(&frameNode, "");
    EXPECT_EQ(accessibilityProperty->textTypeHint_, "");

    viewAbstractModelNG.SetAccessibilityTextHint(&frameNode, TEST_TEXT_HINT);
    EXPECT_EQ(accessibilityProperty->textTypeHint_, TEST_TEXT_HINT);
}

/**
 * @tc.name: SetAccessibilityGroupOptions001
 * @tc.desc: Test the SetAccessibilityGroupOptions when no value
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityGroupOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct framenode
     */
    std::string tag = "uiNode1";
    int32_t nodeId = 1;
    FrameNode frameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. construct accessibilityGroupOptions
     */
    AccessibilityGroupOptions accessibilityGroupOptions;
    accessibilityGroupOptions.accessibilityTextPreferred = true;
    accessibilityGroupOptions.stateControllerByType = AccessibilityRoleType::CALENDAR;
    accessibilityGroupOptions.stateControllerByInspector = "Test StateControllerByInspector";
    accessibilityGroupOptions.actionControllerByType = AccessibilityRoleType::BUTTON;
    accessibilityGroupOptions.actionControllerByInspector = "Test ActionControllerByInspector";

    /**
     * @tc.steps: step3. Test the SetAccessibilityGroupOptions
     */
    auto accessibilityProperty = frameNode.GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->accessibilityGroupOptions_.has_value());
    viewAbstractModelNG.SetAccessibilityGroupOptions(&frameNode, accessibilityGroupOptions);
    EXPECT_TRUE(accessibilityProperty->accessibilityGroupOptions_.has_value());
    AccessibilityGroupOptions valueAccessibilityGroupOptions =
        accessibilityProperty->accessibilityGroupOptions_.value();
    EXPECT_EQ(valueAccessibilityGroupOptions.accessibilityTextPreferred,
        accessibilityGroupOptions.accessibilityTextPreferred);
    EXPECT_EQ(valueAccessibilityGroupOptions.stateControllerByType,
        accessibilityGroupOptions.stateControllerByType);
    EXPECT_EQ(valueAccessibilityGroupOptions.stateControllerByInspector,
        accessibilityGroupOptions.stateControllerByInspector);
    EXPECT_EQ(valueAccessibilityGroupOptions.actionControllerByType,
        accessibilityGroupOptions.actionControllerByType);
    EXPECT_EQ(valueAccessibilityGroupOptions.actionControllerByInspector,
        accessibilityGroupOptions.actionControllerByInspector);
}

/**
 * @tc.name: SetAccessibilityGroupOptions002
 * @tc.desc: Test the SetAccessibilityGroupOptions when has value
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityGroupOptions002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct framenode
     */
    std::string tag = "uiNode1";
    int32_t nodeId = 1;
    FrameNode frameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. construct accessibilityGroupOptions
     */
    AccessibilityGroupOptions accessibilityGroupOptions1;
    accessibilityGroupOptions1.accessibilityTextPreferred = true;
    accessibilityGroupOptions1.stateControllerByType = AccessibilityRoleType::CALENDAR;
    accessibilityGroupOptions1.stateControllerByInspector = "Test StateControllerByInspector 1";
    accessibilityGroupOptions1.actionControllerByType = AccessibilityRoleType::BUTTON;
    accessibilityGroupOptions1.actionControllerByInspector = "Test ActionControllerByInspector 1";
    AccessibilityGroupOptions accessibilityGroupOptions2;
    accessibilityGroupOptions1.accessibilityTextPreferred = false;
    accessibilityGroupOptions1.stateControllerByType = AccessibilityRoleType::ACTION_SHEET;
    accessibilityGroupOptions1.stateControllerByInspector = "Test StateControllerByInspector 2";
    accessibilityGroupOptions1.actionControllerByType = AccessibilityRoleType::ALERT_DIALOG;
    accessibilityGroupOptions1.actionControllerByInspector = "Test ActionControllerByInspector 2";

    /**
     * @tc.steps: step3. Test the SetAccessibilityGroupOptions
     */
    auto accessibilityProperty = frameNode.GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->accessibilityGroupOptions_ = accessibilityGroupOptions1;
    EXPECT_TRUE(accessibilityProperty->accessibilityGroupOptions_.has_value());
    viewAbstractModelNG.SetAccessibilityGroupOptions(&frameNode, accessibilityGroupOptions2);
    EXPECT_TRUE(accessibilityProperty->accessibilityGroupOptions_.has_value());
    AccessibilityGroupOptions valueAccessibilityGroupOptions =
        accessibilityProperty->accessibilityGroupOptions_.value();
    EXPECT_EQ(valueAccessibilityGroupOptions.accessibilityTextPreferred,
        accessibilityGroupOptions2.accessibilityTextPreferred);
    EXPECT_EQ(valueAccessibilityGroupOptions.stateControllerByType,
        accessibilityGroupOptions2.stateControllerByType);
    EXPECT_EQ(valueAccessibilityGroupOptions.stateControllerByInspector,
        accessibilityGroupOptions2.stateControllerByInspector);
    EXPECT_EQ(valueAccessibilityGroupOptions.actionControllerByType,
        accessibilityGroupOptions2.actionControllerByType);
    EXPECT_EQ(valueAccessibilityGroupOptions.actionControllerByInspector,
        accessibilityGroupOptions2.actionControllerByInspector);
}

/**
 * @tc.name: SetAccessibilityStateDescription001
 * @tc.desc: Test the SetAccessibilitySelected
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityStateDescription001, TestSize.Level1)
{
    std::string tag = "uiNode1";
    int32_t nodeId = 1;
    auto frameNode = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    NG::ViewStackProcessor::GetInstance()->elementsStack_.push(frameNode);
    auto frameNodeMain = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNodeMain, nullptr);
    auto accessibilityProperty = frameNodeMain->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    EXPECT_EQ(accessibilityProperty->GetAccessibilityStateDescription(), "");
    viewAbstractModelNG.SetAccessibilityStateDescription(TEST_STATE_DESCRIPTION);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityStateDescription(), TEST_STATE_DESCRIPTION);
    auto strValue = std::string(1001, 'a');
    viewAbstractModelNG.SetAccessibilityStateDescription(strValue);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityStateDescription().size(), STATE_DESCRIPTION_MAX_SIZE);
}

/**
 * @tc.name: SetAccessibilityStateDescription002
 * @tc.desc: Test the SetAccessibilityStateDescription
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetAccessibilityStateDescription002, TestSize.Level1)
{
    std::string tag = "uiNode1";
    int32_t nodeId = 1;
    FrameNode frameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto accessibilityProperty = frameNode.GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    viewAbstractModelNG.SetAccessibilityStateDescription(&frameNode, "");
    EXPECT_EQ(accessibilityProperty->GetAccessibilityStateDescription(), "");
    viewAbstractModelNG.SetAccessibilityStateDescription(&frameNode, TEST_STATE_DESCRIPTION);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityStateDescription(), TEST_STATE_DESCRIPTION);
    auto strValue = std::string(1001, 'a');
    viewAbstractModelNG.SetAccessibilityStateDescription(&frameNode, strValue);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityStateDescription().size(), STATE_DESCRIPTION_MAX_SIZE);
}

/**
 * @tc.name: SetToolbarBuilder
 * @tc.desc: Test the SetToolbarBuilder
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetToolbarBuilder001, TestSize.Level1)
{
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);

    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPattern>());
    rootNode->AddChild(containerModalNode, 0);
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    viewAbstractModelNG.SetToolbarBuilder(nullptr);
    bool ret = mainNode->removeToolbarItemCallbacks_.size() > 0;
    EXPECT_FALSE(ret);
    rootNode->RemoveChild(containerModalNode);
}

/**
 * @tc.name: SetToolbarBuilder
 * @tc.desc: Test the SetToolbarBuilder
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, SetToolbarBuilder002, TestSize.Level1)
{
    auto pipeline = AceType::DynamicCast<PipelineContext>(MockPipelineContext::GetCurrent());
    auto rootNode = pipeline->rootNode_;
    ASSERT_NE(rootNode, nullptr);

    auto containerModalNode =
        FrameNode::CreateFrameNode("ContainerModal", 1, AceType::MakeRefPtr<ContainerModalPattern>());
    rootNode->AddChild(containerModalNode, 0);
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);

    auto builderFunc = []() -> RefPtr<UINode> {
        auto* stack = ViewStackProcessor::GetInstance();
        auto frameNode = FrameNode::GetOrCreateFrameNode(
            V2::TOOLBAR_ETS_TAG, 11, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
        if (stack) {
            stack->Push(frameNode);
        }
        return frameNode ? frameNode : nullptr;
    };
    viewAbstractModelNG.SetToolbarBuilder(std::move(builderFunc));
    bool ret = mainNode->removeToolbarItemCallbacks_.size() > 0;
    EXPECT_TRUE(ret);
    rootNode->RemoveChild(containerModalNode);
}

/**
 * @tc.name: BindContextMenuTest2
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, BindContextMenuTest2, TestSize.Level1)
{
    std::function<void()> buildFunc = nullptr;
    std::function<void()> previewBuildFunc = nullptr;
    MenuParam menuParam;
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::NORMAL_TYPE;
    menuParam.anchorPosition = {10, 20};
    viewAbstractModelNG.BindContextMenu(ResponseType::RIGHT_CLICK, buildFunc, menuParam, previewBuildFunc);
    EXPECT_NE(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);

    viewAbstractModelNG.BindContextMenu(ResponseType::LONG_PRESS, buildFunc, menuParam, previewBuildFunc);
    EXPECT_NE(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);
}

/**
 * @tc.name: BindMenuTest
 * @tc.desc: Test the BindMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, BindMenuTest, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);

    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    menuParam.setShow = true;
    menuParam.anchorPosition = {10, 20};
    menuParam.isShow = true;
    menuParam.isShowInSubWindow = true;
    buildFunc = []() { flag++; };
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    EXPECT_NE(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode(), nullptr);

    params.push_back(OptionParam());
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    EXPECT_NE(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode(), nullptr);
}

/**
 * @tc.name: BindDragWithContextMenuParamsTest003
 * @tc.desc: Verify IsNotNeedShowPreview returns correct result for different menu binding combinations.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, BindDragWithContextMenuParamsTest003, TestSize.Level1)
{
    std::string tag = "uiNode3";
    FrameNode frameNode(tag, TEST_NODE_ID, AceType::MakeRefPtr<Pattern>());
    auto gestureHub = frameNode.GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step1. Set isBindCustomMenu = true, isShow = true
     * @tc.expected: IsNotNeedShowPreview returns true
     */
    gestureHub->SetBindMenuStatus(true, true, MenuPreviewMode::IMAGE);
    auto bindStatus1 = gestureHub->GetBindMenuStatus();
    EXPECT_TRUE(bindStatus1.IsNotNeedShowPreview());

    /**
     * @tc.steps: step2. Set isBindCustomMenu = true, isShow = false
     * @tc.expected: IsNotNeedShowPreview returns false
     */
    gestureHub->SetBindMenuStatus(true, false, MenuPreviewMode::CUSTOM);
    auto bindStatus2 = gestureHub->GetBindMenuStatus();
    EXPECT_FALSE(bindStatus2.IsNotNeedShowPreview());

    /**
     * @tc.steps: step3. Set isBindLongPressMenu = true
     * @tc.expected: IsNotNeedShowPreview returns true
     */
    gestureHub->SetBindMenuStatus(false, false, MenuPreviewMode::CUSTOM);
    auto bindStatus3 = gestureHub->GetBindMenuStatus();
    EXPECT_TRUE(bindStatus3.IsNotNeedShowPreview());

    /**
     * @tc.steps: step4. Clear state and verify IsNotNeedShowPreview returns false
     * @tc.expected: IsNotNeedShowPreview returns false
     */
    gestureHub->SetBindMenuStatus(false, false, MenuPreviewMode::NONE);
    gestureHub->bindMenuStatus_.isBindCustomMenu = false;
    gestureHub->bindMenuStatus_.isBindLongPressMenu = false;
    auto bindStatus4 = gestureHub->GetBindMenuStatus();
    EXPECT_FALSE(bindStatus4.IsNotNeedShowPreview());
}

/**
 * @tc.name: CheckSkipMenuShowTest
 * @tc.desc: Test the CheckSkipMenuShow
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, CheckSkipMenuShowTest, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    /**
     * @tc.expected: CheckSkipMenuShow returns false
     */
    auto targetNode = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(targetNode, nullptr);
    EXPECT_FALSE(viewAbstractModelNG.CheckSkipMenuShow(targetNode));
}

/**
 * @tc.name: PopupTypeStrTest001
 * @tc.desc: Test the PopupTypeStr
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, PopupTypeStrTest001, TestSize.Level1)
{
    auto type = PopupType::POPUPTYPE_TEXTCOLOR;
    EXPECT_EQ(viewAbstractModelNG.PopupTypeStr(type), "TextColor");

    type = PopupType::POPUPTYPE_POPUPCOLOR;
    EXPECT_EQ(viewAbstractModelNG.PopupTypeStr(type), "PopupColor");

    type = PopupType::POPUPTYPE_MASKCOLOR;
    EXPECT_EQ(viewAbstractModelNG.PopupTypeStr(type), "MaskColor");
}

/**
 * @tc.name: BindDragWithContextMenuParamsTest001
 * @tc.desc: Test the BindDragWithContextMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, BindDragWithContextMenuParamsTest001, TestSize.Level1)
{
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ASSERT_NE(pageNode, nullptr);
    auto column = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(column, nullptr);
    auto navDestinaion = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavDestinationPattern>());
    ASSERT_NE(navDestinaion, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(targetNode, nullptr);
    targetNode->MountToParent(navDestinaion);
    targetNode->SetRootNodeId(1);
    navDestinaion->MountToParent(column);
    column->MountToParent(pageNode);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    /**
     * @tc.steps: step1. Set contextMenuRegisterType = CUSTOM_TYPE, menuBindType = RIGHT_CLICK
     * @tc.expected: isBindCustomMenu returns true
     */
    MenuParam menuParam;
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    viewAbstractModelNG.BindDragWithContextMenuParams(menuParam);
    EXPECT_EQ(targetNode->GetOrCreateGestureEventHub()->bindMenuStatus_.isBindCustomMenu, true);
}

/**
 * @tc.name: BindContextMenuTest001
 * @tc.desc: Test the BindContextMenu
 */
HWTEST_F(ViewAbstractModelTestTwoNg, BindContextMenuTest001, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);

    MenuParam menuParam;
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.isShow = false;
    menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    std::function<void()> buildFunc;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::RIGHT_CLICK;
    buildFunc = []() { flag++; };

    /**
     * @tc.steps: step1. Set isShow = false, menuBindType = RIGHT_CLICK
     * @tc.expected: subwindow is not nullptr
     */
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    EXPECT_NE(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);

    /**
     * @tc.steps: step1. Set isShow = true, menuBindType = RIGHT_CLICK
     * @tc.expected: subwindow is not nullptr
     */
    menuParam.isShow = true;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    EXPECT_NE(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);
}

/**
 * @tc.name: ResetKeyboardShortcutTest001
 * @tc.desc: Test the ResetKeyboardShortcutAll of View_Abstract for tab/Up arrow/Down arrow/Left arrow/Right arrow key.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestTwoNg, ResetKeyboardShortcutTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    /**
     * @tc.steps: step2. call SetKeyboardShortcut with tab and ModifierKey.
     * @tc.expected: add fail
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    viewAbstractModelNG.SetKeyboardShortcut(AceType::RawPtr(targetNode), VALUE_TAB, std::move(keys), nullptr);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();

    /**
     * @tc.steps: step3. call ResetKeyboardShortcutAll.
     * @tc.expected: add success
     */
    viewAbstractModelNG.ResetKeyboardShortcutAll(AceType::RawPtr(targetNode));
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
}
} // namespace OHOS::Ace::NG
