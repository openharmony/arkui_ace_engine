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
const NG::PaddingProperty newArgs = NG::PaddingProperty();
const bool SELECTED = true;
const Color BOARD_COLOR = Color::BLUE;
const Color CHECK_COLOR = Color::WHITE;
const Color BORDER_COLOR = Color::GRAY;
const Color SHADOW_COLOR = Color::BLUE;
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const SizeF CONTENT_SIZE2 = SizeF(-7000.0, 400.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
constexpr Dimension CHECK_MARK_SIZE = Dimension(10.0);
const int32_t VERSION_TWELVE = 12;
RefPtr<PipelineContext> pipeline = nullptr;
const SizeF TEST_SIZE_0 = SizeF(0.0f, 0.0f);
const SizeF TEST_SIZE_100_200 = SizeF(100.0f, 200.0f);
const SizeF TEST_SIZE_100 = SizeF(100.0f, 100.0f);
const SizeF TEST_SIZE_200 = SizeF(200.0f, 200.0f);
const SizeF TEST_SIZE_50 = SizeF(50.0f, 50.0f);
const SizeF TEST_SIZE_60 = SizeF(60.0f, 60.0f);
constexpr float TEST_WIDTH_50 = 50.0f;
constexpr float TEST_HEIGHT_60 = 60.0f;
} // namespace

class CheckBoxTwoTestNG : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    CheckboxBuilderFunc CheckboxBuilder();
};

void CheckBoxTwoTestNG::SetUpTestSuite()
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

void CheckBoxTwoTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

CheckboxBuilderFunc CheckBoxTwoTestNG::CheckboxBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}

/**
 * @tc.name: CheckBoxPatternTest0119
 * @tc.desc: Test CheckBoxGroupIsTrue.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0119, TestSize.Level1)
{
    /*
     * @tc.steps: step1. create checkBoxFrameNode and some parameters.
     */
    auto checkBoxFrameNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<CheckBoxPattern>());
    auto paintPropertyTemp = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    paintPropertyTemp->UpdateCheckBoxSelect(false);
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
    groupManager->AddCheckBoxGroup(GROUP_NAME, frameNode2);
    auto groupPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    groupPaintProperty->isCheckBoxCallbackDealed_ = false;
    frameNode2->paintProperty_ = groupPaintProperty;
    auto frameNode3 = AceType::MakeRefPtr<FrameNode>("test3", 3, AceType::MakeRefPtr<Pattern>());
    auto paintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    paintProperty->UpdateCheckBoxSelect(false);
    frameNode3->paintProperty_ = paintProperty;
    groupManager->AddCheckBoxToGroup(GROUP_NAME, frameNode3);
    ElementRegister::GetInstance()->AddReferenced(2, frameNode2);
    ElementRegister::GetInstance()->AddReferenced(3, frameNode3);

    /*
     * @tc.steps: step5. call CheckBoxGroupIsTrue
     * @tc.expected: selectdStatus is NONE
     */
    checkBoxPattern->CheckBoxGroupIsTrue();
    EXPECT_EQ(groupPaintProperty->GetSelectStatus(), CheckBoxGroupPaintProperty::SelectStatus::NONE);
    EXPECT_TRUE(groupPaintProperty->isCheckBoxCallbackDealed_);
}

/**
 * @tc.name: CheckBoxPatternTest0120
 * @tc.desc: Test CheckBoxGroupIsTrue.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0120, TestSize.Level1)
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
    groupPaintProperty->isCheckBoxCallbackDealed_ = false;
    frameNode2->paintProperty_ = groupPaintProperty;
    groupManager->AddCheckBoxGroup(GROUP_NAME, frameNode2);
    auto frameNode3 = AceType::MakeRefPtr<FrameNode>("test3", 3, AceType::MakeRefPtr<CheckBoxPattern>());
    auto paintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    paintProperty->ResetCheckBoxSelect();
    frameNode3->paintProperty_ = paintProperty;
    groupManager->AddCheckBoxToGroup(GROUP_NAME, frameNode3);
    ElementRegister::GetInstance()->AddReferenced(2, frameNode2);
    ElementRegister::GetInstance()->AddReferenced(3, frameNode3);
    ElementRegister::GetInstance()->AddReferenced(4, nullptr);

    /*
     * @tc.steps: step5. call CheckBoxGroupIsTrue,
     * @tc.expected: groupPaintProperty.GetIsCheckBoxCallbackDealed() is true and exit error
     */
    checkBoxPattern->CheckBoxGroupIsTrue();
    EXPECT_TRUE(groupPaintProperty->GetIsCheckBoxCallbackDealed());

    /*
     * @tc.steps: step6. set CheckBoxGroupSelect is true
     * @tc.expected: lastSelect_ is NONE
     */
    paintProperty->ResetCheckBoxSelect();
    groupPaintProperty->isCheckBoxCallbackDealed_ = false;
    groupPaintProperty->UpdateCheckBoxGroupSelect(true);
    checkBoxPattern->CheckBoxGroupIsTrue();
    auto checkBoxPattern3 = frameNode3->GetPattern<CheckBoxPattern>();
    EXPECT_TRUE(checkBoxPattern3->lastSelect_);
}

/**
 * @tc.name: CheckBoxPatternTest0121
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0121, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern checkBoxSelect
     */
    pattern->SetCheckBoxSelect(SELECTED);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the CheckBox property value
     */
   
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    EXPECT_EQ(isSelected, SELECTED);
}

/**
 * @tc.name: CheckBoxPatternTest0122
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0122, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern checkBoxSelect
     */
    pattern->SetCheckBoxSelect(false);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the CheckBox property value
     */
   
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    EXPECT_EQ(isSelected, false);
}

/**
 * @tc.name: CheckBoxPatternTest0123
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0123, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetCheckBoxSelect(SELECTED);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.selected_);
                return nullptr;
            };
    
    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: CheckBoxPatternTest0124
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0124, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetCheckBoxSelect(false);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);

    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(false, config.selected_);
                return nullptr;
            };
    
    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: CheckBoxPatternTest0125
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0125, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create("", GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetCheckBoxSelect(false);

    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ("", config.name_);
                EXPECT_EQ(false, config.selected_);
                return nullptr;
            };
    
    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: CheckBoxPatternTest0126
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0126, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create("", GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetCheckBoxSelect(false);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(false, config.selected_);
                return nullptr;
            };
    
    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: CheckBoxPatternTest0127
 * @tc.desc: CheckBox test SetBuilder.
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0127, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->builder_, nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest0128
 * @tc.desc: Test UpdateIndicator.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0128, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
   
    /**
     * @tc.steps: step3. call UpdateIndicator
     * @tc.expected: test GetFirstChild is not null
     */
    pattern->OnModifyDone();
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->FlushBuildFinishCallbacks();
    pattern->UpdateIndicator();
    auto host = pattern->GetHost();
    ASSERT_NE(host->GetFirstChild(), nullptr);
}

/**
 * @tc.name: CheckBoxPatternTest0129
 * @tc.desc: Test StartCustomNodeAnimation when select is true.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0129, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->FlushBuildFinishCallbacks();
    pattern->StartCustomNodeAnimation(true);
    auto host = pattern->GetHost();
    auto childNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    ASSERT_NE(childNode, nullptr);
    ASSERT_NE(childNode->GetRenderContext(), nullptr);
    EXPECT_EQ(childNode->GetRenderContext()->GetOpacityValue(), 1);
}

/**
 * @tc.name: CheckBoxPatternTest0130
 * @tc.desc: Test StartCustomNodeAnimation when select is false.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0130, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);

    auto checkBoxFunc = CheckboxBuilder();
    checkBoxModelNG.SetBuilder(checkBoxFunc);
    /**
     * @tc.steps: step2. Get CheckBox pattern object and get
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->FlushBuildFinishCallbacks();
    pattern->StartCustomNodeAnimation(false);
    auto host = pattern->GetHost();
    auto childNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    ASSERT_NE(childNode, nullptr);
    ASSERT_NE(childNode->GetRenderContext(), nullptr);
    EXPECT_EQ(childNode->GetRenderContext()->GetOpacityValue(), 0);
}

/**
 * @tc.name: CheckBoxNGTest0131
 * @tc.desc: Test SetCheckBoxName func.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxNGTest0131, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    auto frameNode = CheckBoxModelNG::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. SetCheckBoxName testName and testGroupName
     */
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    CheckBoxModelNG::SetCheckboxName(node, "testName");
    CheckBoxModelNG::SetCheckboxGroup(node, "testGroupName");

    /**
     * @tc.steps: step3. assert Name and GroupName
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->GetName(), "testName");
    EXPECT_EQ(eventHub->GetGroupName(), "testGroupName");
}

/**
 * @tc.name: CheckBoxNGTest0132
 * @tc.desc: Test retrieval of name and groupName.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxNGTest0132, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    auto frameNode = CheckBoxModelNG::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. SetCheckBoxName testName and testGroupName
     */
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    CheckBoxModelNG::SetCheckboxName(node, NAME);
    CheckBoxModelNG::SetCheckboxGroup(node, GROUP_NAME);
    /**
     * @tc.steps: step3. assert Name and GroupName
     */
    EXPECT_EQ(CheckBoxModelNG::GetCheckboxName(node), NAME);
    EXPECT_EQ(CheckBoxModelNG::GetCheckboxGroup(node), GROUP_NAME);
}

/**
 * @tc.name: CheckBoxPatternTest0134
 * @tc.desc: Test CheckBox theme.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest0134, TestSize.Level1)
{
    /**
     * @tc.steps: create frameNode
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: create mock theme manager, set checkbox theme
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetThemeManager(themeManager);
    auto checkboxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkboxTheme));

    /**
     * @tc.steps: call checkBoxTheme the GetHoverPaddingSize
     */
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipelineBase = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineBase, nullptr);
    auto checkBoxTheme = pipelineBase->GetTheme<CheckboxTheme>();
    ASSERT_NE(checkBoxTheme, nullptr);
    checkBoxTheme->hoverPaddingSize_ = CHECK_MARK_SIZE;
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    EXPECT_EQ(checkBoxTheme->GetHoverPaddingSize(), CHECK_MARK_SIZE);
}

/**
 * @tc.name: CheckBoxPaintMethodTest0135
 * @tc.desc: Test CheckBox PaintMethod PaintCheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPaintMethodTest0135, TestSize.Level1)
{
    /**
     * @tc.steps: step1. MockContainer.apiTargetVersion_ = VERSION_TWELVE.
     */
    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(VERSION_TWELVE);

    /**
     * @tc.steps: step2. create GeometryNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    /**
     * @tc.steps: step3. Create checkBoxModifier and call PaintCheckBox.
     * @tc.expected: step3. expect DrawRoundRect call at least 1.
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
    MockContainer::TearDown();
}

/**
 * @tc.name: CheckBoxMeasureTest136
 * @tc.desc: Test CheckBox MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxMeasureTest136, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node.
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
     * @tc.steps: step3. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step3. switchSize is equal to TEST_SIZE_100.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ret = checkBoxLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_100);
}

/**
 * @tc.name: CheckBoxLayoutPolicyIsMatchParentTest137
 * @tc.desc: Test Checkbox LayoutPolicyIsMatchParent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxLayoutPolicyIsMatchParentTest137, TestSize.Level1)
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
     * @tc.steps: step3. call LayoutPolicyIsMatchParent function.
     * @tc.expected: step3. switchSize is equal to TEST_SIZE_0.
     */
    LayoutConstraintF contentConstraint;
    auto layoutPolicy = checkBoxLayoutAlgorithm->GetLayoutPolicy(&layoutWrapper);
    auto ret = checkBoxLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_0);

    /**
     * @tc.steps: step4. set layoutPolicy->widthLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step4. ret is equal to TEST_SIZE_100.
     */
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    ret = checkBoxLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_100);

    /**
     * @tc.steps: step5. set selfIdealSize.height_ to TEST_HEIGHT_60.
     * @tc.expected: step5. ret is equal to TEST_SIZE_60.
     */
    contentConstraint.selfIdealSize.SetHeight(TEST_HEIGHT_60);
    ret = checkBoxLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_60);

    /**
     * @tc.steps: step6. set layoutPolicy->heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step6. ret is equal to TEST_SIZE_200.
     */
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicy->heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    ret = checkBoxLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step7. set selfIdealSize.width_ to TEST_WIDTH_50.
     * @tc.expected: step7. ret is equal to TEST_SIZE_50.
     */
    contentConstraint.selfIdealSize.SetWidth(TEST_WIDTH_50);
    ret = checkBoxLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_50);

    /**
     * @tc.steps: step8. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step8. ret is equal to TEST_SIZE_100.
     */
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicy->heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    ret = checkBoxLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_100);
}

/**
 * @tc.name: CreateWithColorResourceObj
 * @tc.desc: Test CheckBox CreateWithColorResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, CreateWithColorResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBox frame node.
     * @tc.expected: step1. Frame node is not null.
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create color resource object and verify resource manager.
     * @tc.expected: step2. Resource is added to manager.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    checkBoxModelNG.CreateWithColorResourceObj(resObj, CheckBoxColorType::SELECTED_COLOR);

    std::string key = "checkbox" + CheckBoxModelNG::ColorTypeToString(CheckBoxColorType::SELECTED_COLOR);
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
    checkBoxModelNG.CreateWithColorResourceObj(resObjWithParams, CheckBoxColorType::UN_SELECTED_COLOR);
    key = "checkbox" + CheckBoxModelNG::ColorTypeToString(CheckBoxColorType::UN_SELECTED_COLOR);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);
}

/**
 * @tc.name: ColorTypeToString
 * @tc.desc: test ColorTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, ColorTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test color type to string conversion.
     * @tc.expected: step1. Conversion returns correct string values.
     */
    std::vector<std::pair<CheckBoxColorType, std::string>> types = {
        { CheckBoxColorType::SELECTED_COLOR, "SelectedColor" },
        { CheckBoxColorType::UN_SELECTED_COLOR, "UnSelectedColor" },
        { static_cast<CheckBoxColorType>(2), "Unknown" } };
    for (const auto& [type, val] : types) {
        auto ret = CheckBoxModelNG::ColorTypeToString(type);
        EXPECT_EQ(val, ret);
    }
}

/**
 * @tc.name: UpdateComponentColor
 * @tc.desc: Test CheckBox UpdateComponentColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, UpdateComponentColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBox frame node and get necessary properties.
     * @tc.expected: step1. Frame node and properties are not null.
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step2. Update component color with different types.
     * @tc.expected: step2. Color properties are updated correctly.
     */
    checkBoxModelNG.UpdateComponentColor(frameNode, static_cast<CheckBoxColorType>(2), Color::RED);
    auto ret = paintProperty->GetCheckBoxSelectedColor();
    EXPECT_FALSE(ret.has_value());
    checkBoxModelNG.UpdateComponentColor(frameNode, CheckBoxColorType::SELECTED_COLOR, Color::RED);
    ret = paintProperty->GetCheckBoxSelectedColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);
    checkBoxModelNG.UpdateComponentColor(frameNode, CheckBoxColorType::UN_SELECTED_COLOR, Color::RED);
    ret = paintProperty->GetCheckBoxUnSelectedColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);
}

/**
 * @tc.name: ResetComponentColor
 * @tc.desc: Test CheckBox ResetComponentColor.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxTwoTestNG, ResetComponentColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CheckBox frame node and get necessary properties.
     * @tc.expected: step1. Frame node and properties are not null.
     */
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto theme = pipelineContext->GetTheme<CheckboxTheme>();
    ASSERT_NE(theme, nullptr);

    /**
     * @tc.steps: step2. Reset component color with different types.
     * @tc.expected: step2. Color properties are reset to theme values.
     */
    checkBoxModelNG.ResetComponentColor(frameNode, static_cast<CheckBoxColorType>(2));
    auto ret = paintProperty->GetCheckBoxSelectedColor();
    EXPECT_FALSE(ret.has_value());
    checkBoxModelNG.ResetComponentColor(frameNode, CheckBoxColorType::SELECTED_COLOR);
    ret = paintProperty->GetCheckBoxSelectedColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), theme->GetActiveColor());
    checkBoxModelNG.ResetComponentColor(frameNode, CheckBoxColorType::UN_SELECTED_COLOR);
    ret = paintProperty->GetCheckBoxUnSelectedColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), theme->GetInactiveColor());
}

/**
 * @tc.name: CheckBoxPatternTest034
 * @tc.desc: CheckBox test Select and ClearSelection.
 */
HWTEST_F(CheckBoxTwoTestNG, CheckBoxPatternTest034, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->lastSelect_ = false;
    pattern->SetAccessibilityAction();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<CheckBoxAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->ActActionSelect());

    bool isSelected = true;
    pattern->lastSelect_ = false;
    pattern->MarkIsSelected(isSelected);
    EXPECT_TRUE(accessibilityProperty->ActActionClearSelection());
}
} // namespace OHOS::Ace::NG
