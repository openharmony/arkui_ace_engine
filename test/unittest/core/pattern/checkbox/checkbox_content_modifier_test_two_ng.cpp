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

using namespace testing;
using namespace testing::ext;
using CheckboxBuilderFunc = std::optional<std::function<void()>>;

namespace OHOS::Ace::NG {
namespace {
const std::string NAME = "checkbox";
const std::string GROUP_NAME = "checkboxGroup";
const std::string TAG = "CHECKBOX_TAG";
const bool SELECTED = true;
const bool UNSELECTED = false;
constexpr int BIG_INT = 100000000;
constexpr int NEGATIVE_BIG_INT = -100000000;
constexpr int CHILD_NODE_ID = 100;
} // namespace

class CheckBoxContentModifierTwoTestNG : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    CheckboxBuilderFunc CheckboxBuilder();
};

void CheckBoxContentModifierTwoTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));

    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void CheckBoxContentModifierTwoTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

CheckboxBuilderFunc CheckBoxContentModifierTwoTestNG::CheckboxBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}

/**
 * @tc.name: CheckBoxContentModifierTest032
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest032, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    pattern->SetCheckBoxSelect(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.selected_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. change builder func nullptr
     */
    pattern->SetBuilderFunc(nullptr);
    pattern->FireBuilder();
    /**
     * @tc.steps: step7. Test UseContentModifier
     */
    auto isUsed = pattern->UseContentModifier();
    /**
     * @tc.expected: isUsed is false
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: CheckBoxContentModifierTest033
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest033, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    checkBoxModelNG.SetChangeValue(Referenced::RawPtr(frameNode), false);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, false);
}

/**
 * @tc.name: CheckBoxContentModifierTest034
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest034, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    checkBoxModelNG.SetChangeValue(Referenced::RawPtr(frameNode), true);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, true);
}

/**
 * @tc.name: CheckBoxContentModifierTest035
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest035, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    checkBoxModelNG.SetChangeValue(Referenced::RawPtr(frameNode), BIG_INT);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, true);
}

/**
 * @tc.name: CheckBoxContentModifierTest036
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest036, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    checkBoxModelNG.SetChangeValue(Referenced::RawPtr(frameNode), NEGATIVE_BIG_INT);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, true);
}

/**
 * @tc.name: CheckBoxContentModifierTest037
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest037, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    checkBoxModelNG.SetChangeValue(Referenced::RawPtr(frameNode), 0);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, false);
}

/**
 * @tc.name: CheckBoxContentModifierTest038
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest038, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    checkBoxModelNG.SetChangeValue(Referenced::RawPtr(frameNode), 1);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, true);
}

/**
 * @tc.name: CheckBoxContentModifierTest039
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest039, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    checkBoxModelNG.SetChangeValue(Referenced::RawPtr(frameNode), -1);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, true);
}

/**
 * @tc.name: CheckBoxContentModifierTest040
 * @tc.desc: Test SetCheckBoxSelect and get value
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest040, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(-1);
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
 * @tc.name: CheckBoxContentModifierTest041
 * @tc.desc: Test SetCheckBoxSelect and get value
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest041, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(BIG_INT);
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
 * @tc.name: CheckBoxContentModifierTest042
 * @tc.desc: Test SetCheckBoxSelect and get value
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest042, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(NEGATIVE_BIG_INT);
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
 * @tc.name: CheckBoxContentModifierTest043
 * @tc.desc: Test SetCheckBoxSelect and get value
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest043, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(0);
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
    EXPECT_EQ(isSelected, UNSELECTED);
}

/**
 * @tc.name: CheckBoxContentModifierTest044
 * @tc.desc: Test SetCheckBoxSelect and get value
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest044, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(1);
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
 * @tc.name: CheckBoxContentModifierTest045
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest045, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetCheckBoxSelect(true);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, true);
}

/**
 * @tc.name: CheckBoxContentModifierTest046
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest046, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetCheckBoxSelect(false);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, false);
}

/**
 * @tc.name: CheckBoxContentModifierTest047
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest047, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetCheckBoxSelect(0);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, false);
}

/**
 * @tc.name: CheckBoxContentModifierTest048
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest048, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetCheckBoxSelect(1);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, true);
}

/**
 * @tc.name: CheckBoxContentModifierTest049
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest049, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetCheckBoxSelect(BIG_INT);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, true);
}

/**
 * @tc.name: CheckBoxContentModifierTest050
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierTwoTestNG, CheckBoxContentModifierTest050, TestSize.Level1)
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
     * @tc.steps: step2. Set checkBoxConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetName(NAME);
    eventHub->SetEnabled(SELECTED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](CheckBoxConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.name_);
                EXPECT_EQ(SELECTED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to checkBoxModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetCheckBoxSelect(NEGATIVE_BIG_INT);
    /**
     * @tc.steps: step7. Get isSelected
     */
    auto checkBoxPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    bool isSelected = false;
    if (checkBoxPaintProperty->HasCheckBoxSelect()) {
        isSelected = checkBoxPaintProperty->GetCheckBoxSelectValue();
    } else {
        isSelected = false;
    }
    /**
     * @tc.expected: Check the CheckBox isSelected
     */
    EXPECT_EQ(isSelected, true);
}
} // namespace OHOS::Ace::NG
