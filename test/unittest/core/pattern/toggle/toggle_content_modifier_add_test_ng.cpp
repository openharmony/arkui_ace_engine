/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#define private public
#define protected public
#include "base/geometry/dimension.h"
#include "base/json/json_util.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/manager/focus/focus_manager.h"
#include "core/components_ng/pattern/button/toggle_button_event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/checkbox/checkbox_event_hub.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/switch_paint_method.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "interfaces/inner_api/ui_session/param_config.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr int BIG_INT = 100000000;
constexpr int NEGATIVE_BIG_INT = -100000000;
constexpr int CHILD_NODE_ID = 100;
constexpr float ZERO_FLOAT = 0.0f;
constexpr float ONE_FLOAT = 1.0f;
constexpr float TWO_FLOAT = 2.0f;
constexpr float TEN_FLOAT = 10.0f;
constexpr float THIRTY_FLOAT = 30.0f;
constexpr float FORTY_FLOAT = 40.0f;
constexpr float FIFTY_FLOAT = 50.0f;
constexpr double ONE_DOUBLE = 1.0;
constexpr double TWO_DOUBLE = 2.0;
constexpr Color SELECTED_COLOR = Color(0XFFFF0000);
constexpr Color SWITCH_POINT_COLOR = Color(0XFFFFFF00);
const std::vector<NG::ToggleType> TOGGLE_TYPE = { ToggleType::CHECKBOX, ToggleType::BUTTON, ToggleType::SWITCH };
} // namespace

class ToggleContentModifierAddTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static PaddingPropertyF CreatePadding(Dimension length);
};

void ToggleContentModifierAddTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void ToggleContentModifierAddTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

PaddingPropertyF ToggleContentModifierAddTestNg::CreatePadding(Dimension length)
{
    PaddingPropertyF padding;
    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    return padding;
}

/**
 * @tc.name: ToggleContentModifierAddTestNg001
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    pattern->SetButtonPress(BIG_INT);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasIsOn()) {
        isOn = switchPaintProperty->GetIsOnValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, IS_ON);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg002
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    pattern->SetCheckBoxSelect(IS_ON);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasCheckBoxSelect()) {
        isOn = switchPaintProperty->GetCheckBoxSelectValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, IS_ON);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg003
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    pattern->SetCheckBoxSelect(false);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasCheckBoxSelect()) {
        isOn = switchPaintProperty->GetCheckBoxSelectValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, false);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg004
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    pattern->SetCheckBoxSelect(0);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasCheckBoxSelect()) {
        isOn = switchPaintProperty->GetCheckBoxSelectValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, false);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg005
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    pattern->SetCheckBoxSelect(NEGATIVE_BIG_INT);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasCheckBoxSelect()) {
        isOn = switchPaintProperty->GetCheckBoxSelectValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, IS_ON);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg006
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set ToggleConfiguration
     */
    pattern->SetCheckBoxSelect(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", 0, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ(0, buildNode->GetId());
}

/**
 * @tc.name: ToggleContentModifierAddTestNg007
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set ToggleConfiguration
     */
    pattern->SetCheckBoxSelect(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", BIG_INT, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ(BIG_INT, buildNode->GetId());
}

/**
 * @tc.name: ToggleContentModifierAddTestNg008
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set ToggleConfiguration
     */
    pattern->SetCheckBoxSelect(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", NEGATIVE_BIG_INT, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ(NEGATIVE_BIG_INT, buildNode->GetId());
}

/**
 * @tc.name: ToggleContentModifierAddTestNg009
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set ToggleConfiguration
     */
    pattern->SetCheckBoxSelect(IS_ON);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", NEGATIVE_BIG_INT, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ(NEGATIVE_BIG_INT, buildNode->GetId());
}

/**
 * @tc.name: ToggleContentModifierAddTestNg010
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set ToggleConfiguration
     */
    pattern->SetCheckBoxSelect(1);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", NEGATIVE_BIG_INT, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ(NEGATIVE_BIG_INT, buildNode->GetId());
}

/**
 * @tc.name: ToggleContentModifierAddTestNg011
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init CheckBox node
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set ToggleConfiguration
     */
    pattern->SetCheckBoxSelect(BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", NEGATIVE_BIG_INT, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test GetContentModifierNode
     */
    auto buildNode = pattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the CheckBox child id
     */
    EXPECT_EQ(NEGATIVE_BIG_INT, buildNode->GetId());
}

/**
 * @tc.name: ToggleContentModifierAddTestNg012
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Toggle node
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set toggleConfiguration
     */
    pattern->SetCheckBoxSelect(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    toggleModelNG.SetBuilderFunc(AceType::RawPtr(frameNode), node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierAddTestNg013
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Toggle node
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set toggleConfiguration
     */
    pattern->SetButtonPress(IS_ON);
    auto eventHub = frameNode->GetEventHub<NG::ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    toggleModelNG.SetBuilderFunc(AceType::RawPtr(frameNode), node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierAddTestNg014
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Toggle node
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set toggleConfiguration
     */
    pattern->SetSwitchIsOn(IS_ON);
    auto eventHub = frameNode->GetEventHub<NG::SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    toggleModelNG.SetBuilderFunc(AceType::RawPtr(frameNode), node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierAddTestNg015
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    toggleModelNG.SetChangeValue(AceType::RawPtr(frameNode), -1);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasCheckBoxSelect()) {
        isOn = switchPaintProperty->GetCheckBoxSelectValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, IS_ON);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg016
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    toggleModelNG.SetChangeValue(AceType::RawPtr(frameNode), IS_ON);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasIsOn()) {
        isOn = switchPaintProperty->GetIsOnValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, IS_ON);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg017
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get parament to pattern SwitchIsOn
     */
    toggleModelNG.SetChangeValue(AceType::RawPtr(frameNode), IS_ON);
    /**
     * @tc.steps: step3.get paint property.
     * @tc.expected: check the switch property value.
     */
    auto switchPaintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);
    bool isOn = false;
    if (switchPaintProperty->HasIsOn()) {
        isOn = switchPaintProperty->GetIsOnValue();
    } else {
        isOn = false;
    }
    EXPECT_EQ(isOn, IS_ON);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg018
 * @tc.desc: Test event function of toggle with checkbox.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto checkBoxFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(checkBoxFrameNode, nullptr);
    EXPECT_EQ(checkBoxFrameNode->GetTag(), V2::CHECKBOX_ETS_TAG);
    toggleModelNG.SetSelectedColor(AceType::RawPtr(checkBoxFrameNode), SELECTED_COLOR);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(AceType::RawPtr(checkBoxFrameNode), onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto pattern = AceType::DynamicCast<CheckBoxPattern>(checkBoxFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetCheckBoxSelect(), IS_ON);
    EXPECT_EQ(paintProperty->GetCheckBoxSelectedColor(), SELECTED_COLOR);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg019
 * @tc.desc: Test event function of toggle with button.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(buttonFrameNode, nullptr);
    EXPECT_EQ(buttonFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    toggleModelNG.SetSelectedColor(AceType::RawPtr(buttonFrameNode), SELECTED_COLOR);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(AceType::RawPtr(buttonFrameNode), onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto paintProperty = buttonFrameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetIsOn(), IS_ON);
    EXPECT_EQ(paintProperty->GetSelectedColor(), SELECTED_COLOR);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg020
 * @tc.desc: Test event function of toggle with switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    EXPECT_EQ(switchFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    toggleModelNG.SetSelectedColor(AceType::RawPtr(switchFrameNode), SELECTED_COLOR);
    toggleModelNG.SetSwitchPointColor(SWITCH_POINT_COLOR);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(AceType::RawPtr(switchFrameNode), onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto eventHub = switchFrameNode->GetEventHub<SwitchEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(stateChange, true);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg021
 * @tc.desc: Test SetHoverEffect of toggle with HoverEffectType OPACITY.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    toggleModelNG.SetHoverEffect(HoverEffectType::OPACITY);
    auto switchPattern = frameNode->GetPattern<SwitchPattern>();
    EXPECT_TRUE(switchPattern->showHoverEffect_);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg022
 * @tc.desc: Test SetHoverEffect of toggle with HoverEffectType BOARD.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    toggleModelNG.SetHoverEffect(HoverEffectType::BOARD);
    auto switchPattern = frameNode->GetPattern<SwitchPattern>();
    EXPECT_TRUE(switchPattern->showHoverEffect_);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg023
 * @tc.desc: Test SetHoverEffect of toggle when pattern is null.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    auto pattern = frameNode->pattern_;
    frameNode->pattern_ = nullptr;
    toggleModelNG.SetHoverEffect(HoverEffectType::OPACITY);
    frameNode->pattern_ = pattern;
}

/**
 * @tc.name: ToggleContentModifierAddTestNg024
 * @tc.desc: Test SetHoverEffect of toggle with HoverEffectType OPACITY.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    toggleModelNG.SetHoverEffect(frameNode, HoverEffectType::OPACITY);
    auto switchPattern = frameNode->GetPattern<SwitchPattern>();
    EXPECT_TRUE(switchPattern->showHoverEffect_);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg025
 * @tc.desc: Test SetHoverEffect of toggle with HoverEffectType BOARD.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    toggleModelNG.SetHoverEffect(frameNode, HoverEffectType::BOARD);
    auto switchPattern = frameNode->GetPattern<SwitchPattern>();
    EXPECT_TRUE(switchPattern->showHoverEffect_);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg026
 * @tc.desc: Test SetHoverEffect of toggle when pattern is null.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    auto pattern = frameNode->pattern_;
    frameNode->pattern_ = nullptr;
    toggleModelNG.SetHoverEffect(frameNode, HoverEffectType::OPACITY);
    frameNode->pattern_ = pattern;
}

/**
 * @tc.name: ToggleContentModifierAddTestNg027
 * @tc.desc: Test SetPointRadius of toggle.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    toggleModelNG.SetPointRadius(AceType::RawPtr(switchFrameNode), Dimension(10));

    /**
     * @tc.steps: step2.get switch property and check whether the property value is correct.
     */
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetPointRadius(), Dimension(10));
}

/**
 * @tc.name: ToggleContentModifierAddTestNg028
 * @tc.desc: Test ResetPointRadius of toggle.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    toggleModelNG.ResetPointRadius(AceType::RawPtr(switchFrameNode));
    toggleModelNG.ResetTrackBorderRadius();

    /**
     * @tc.steps: step2.get switch property and check whether the property value is correct.
     */
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_FALSE(paintProperty->GetPointRadius().has_value());
    EXPECT_FALSE(paintProperty->GetTrackBorderRadius().has_value());
}

/**
 * @tc.name: ToggleContentModifierAddTestNg029
 * @tc.desc: Test SetSelectedColor of toggle with checkbox.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    std::optional<Color> selectedColor = std::optional<Color>();

    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto checkBoxFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(checkBoxFrameNode, nullptr);
    EXPECT_EQ(checkBoxFrameNode->GetTag(), V2::CHECKBOX_ETS_TAG);
    toggleModelNG.SetSelectedColor(AceType::RawPtr(checkBoxFrameNode), selectedColor);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(AceType::RawPtr(checkBoxFrameNode), onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto pattern = AceType::DynamicCast<CheckBoxPattern>(checkBoxFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetCheckBoxSelect(), IS_ON);
    EXPECT_EQ(paintProperty->GetCheckBoxSelectedColor(), selectedColor);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg030
 * @tc.desc: Test event function of toggle with button.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    std::optional<Color> selectedColor = std::optional<Color>();

    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(buttonFrameNode, nullptr);
    EXPECT_EQ(buttonFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    toggleModelNG.SetSelectedColor(AceType::RawPtr(buttonFrameNode), selectedColor);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(AceType::RawPtr(buttonFrameNode), onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto paintProperty = buttonFrameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetIsOn(), IS_ON);
    EXPECT_EQ(paintProperty->GetSelectedColor(), selectedColor);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg031
 * @tc.desc: Test event function of toggle with switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    std::optional<Color> selectedColor = std::optional<Color>();

    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    EXPECT_EQ(switchFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    toggleModelNG.SetSelectedColor(AceType::RawPtr(switchFrameNode), selectedColor);
    toggleModelNG.SetSwitchPointColor(AceType::RawPtr(switchFrameNode), SWITCH_POINT_COLOR);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(AceType::RawPtr(switchFrameNode), onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetIsOn(), IS_ON);
    EXPECT_EQ(paintProperty->GetSelectedColor(), selectedColor);
    EXPECT_EQ(paintProperty->GetSwitchPointColor(), SWITCH_POINT_COLOR);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg032
 * @tc.desc: Test SetPointRadius of toggle.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    switchFrameNode->paintProperty_ = nullptr;
    toggleModelNG.SetPointRadius(AceType::RawPtr(switchFrameNode), Dimension(10));

    /**
     * @tc.steps: step2.get switch property and check whether the property value is correct.
     */
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_EQ(paintProperty, nullptr);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg033
 * @tc.desc: Test ResetPointRadius of toggle.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    switchFrameNode->paintProperty_ = nullptr;
    toggleModelNG.ResetPointRadius(AceType::RawPtr(switchFrameNode));
    toggleModelNG.ResetTrackBorderRadius();

    /**
     * @tc.steps: step2.get switch property and check whether the property value is correct.
     */
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_EQ(paintProperty, nullptr);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg034
 * @tc.desc: Test event function of toggle with switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);
    EXPECT_EQ(switchFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    switchFrameNode->paintProperty_ = nullptr;
    toggleModelNG.SetSelectedColor(AceType::RawPtr(switchFrameNode), SELECTED_COLOR);
    toggleModelNG.SetSwitchPointColor(AceType::RawPtr(switchFrameNode), SWITCH_POINT_COLOR);

    /**
     * @tc.steps: step2. get the paintProperty.
     * @tc.expected: step2. check whether the value is correct.
     */
    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_EQ(paintProperty, nullptr);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg035
 * @tc.desc: Test CalcActualWidth
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg035, TestSize.Level1)
{
    SizeF size;
    OffsetF offset;
    Color boardColor;
    Color pointColor;
    SwitchModifier switchModifier(size, offset, ZERO_FLOAT, IS_ON, boardColor, pointColor, ZERO_FLOAT);
    EXPECT_EQ(switchModifier.CalcActualWidth(ONE_FLOAT, TWO_FLOAT, ONE_DOUBLE, TWO_DOUBLE), 3);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg036
 * @tc.desc: Test Switch InitDefaultMargin.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);
    /**
     * @tc.steps: step2. make builderFunc
     */
    auto buildFunc = [](ToggleConfiguration config) -> RefPtr<FrameNode> { return nullptr; };
    /**
     * @tc.steps: step3. set builder func and call InitDefaultMargin.
     * @tc.expected: step3. margin property is null.
     */
    toggleModelNG.SetIsUserSetMargin(true);
    switchPattern->SetBuilderFunc(buildFunc);
    switchPattern->InitDefaultMargin();
    auto layoutProperty = switchFrameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty->GetMarginProperty(), nullptr);
    /**
     * @tc.steps: step4. clear builderFunc and call InitDefaultMargin.
     * @tc.expected: step4. margin property is not null.
     */
    toggleModelNG.SetIsUserSetMargin(false);
    switchPattern->InitDefaultMargin();
    EXPECT_NE(layoutProperty->GetMarginProperty(), nullptr);
    switchPattern->SetBuilderFunc(nullptr);
    switchPattern->InitDefaultMargin();
    EXPECT_NE(layoutProperty->GetMarginProperty(), nullptr);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg037
 * @tc.desc: Test Checkbox InitDefaultMargin.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::CHECKBOX, IS_ON);
    auto checkboxFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(checkboxFrameNode, nullptr);
    auto checkboxPattern = checkboxFrameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkboxPattern, nullptr);
    /**
     * @tc.steps: step2. make builderFunc
     */
    auto buildFunc = [](ToggleConfiguration config) -> RefPtr<FrameNode> { return nullptr; };
    /**
     * @tc.steps: step3. set builder func and call InitDefaultMargin.
     * @tc.expected: step3. margin property is null.
     */
    toggleModelNG.SetIsUserSetMargin(true);
    checkboxPattern->SetToggleBuilderFunc(buildFunc);
    checkboxPattern->InitDefaultMargin();
    auto layoutProperty = checkboxFrameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty->GetMarginProperty(), nullptr);
    /**
     * @tc.steps: step4. clear builderFunc and call InitDefaultMargin.
     * @tc.expected: step4. margin property is not null.
     */
    toggleModelNG.SetIsUserSetMargin(false);
    checkboxPattern->InitDefaultMargin();
    EXPECT_NE(layoutProperty->GetMarginProperty(), nullptr);
    checkboxPattern->SetToggleBuilderFunc(nullptr);
    checkboxPattern->InitDefaultMargin();
    EXPECT_NE(layoutProperty->GetMarginProperty(), nullptr);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg038
 * @tc.desc: Test FixPointOffset.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg038, TestSize.Level1)
{
    SwitchModifier switchModifier(SizeF(), OffsetF(), 0.0, false, Color::RED, Color::RED, ZERO_FLOAT);
    switchModifier.isSizeChange_ = true;
    switchModifier.actualSize_.width_ = FIFTY_FLOAT;
    switchModifier.actualSize_.height_ = FORTY_FLOAT;
    float pointOffset = FIFTY_FLOAT;
    switchModifier.pointOffset_->Set(pointOffset);
    switchModifier.FixPointOffset();
    EXPECT_EQ(switchModifier.pointOffset_->Get(), FIFTY_FLOAT - FORTY_FLOAT / 2.0f);
}

/**
 * @tc.name: ToggleContentModifierAddTestNg039
 * @tc.desc: Test FixPointOffset.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, ToggleContentModifierAddTestNg039, TestSize.Level1)
{
    SwitchModifier switchModifier(SizeF(), OffsetF(), 0.0, false, Color::RED, Color::RED, ZERO_FLOAT);
    switchModifier.isSizeChange_ = true;
    switchModifier.actualSize_.width_ = FORTY_FLOAT;
    switchModifier.actualSize_.height_ = FIFTY_FLOAT;
    switchModifier.actualTrackRadius_ = THIRTY_FLOAT;
    float pointOffset = FIFTY_FLOAT;
    switchModifier.pointOffset_->Set(pointOffset);
    switchModifier.FixPointOffset();
    EXPECT_EQ(switchModifier.pointOffset_->Get(), TEN_FLOAT);
    switchModifier.isSizeChange_ = true;
    pointOffset = TWO_FLOAT;
    switchModifier.pointOffset_->Set(pointOffset);
    switchModifier.FixPointOffset();
    EXPECT_FALSE(switchModifier.isSizeChange_);
}

/**
 * @tc.name: HandleBlurEvent001
 * @tc.desc: Test SwitchPattern HandleBlurEvent resets focus state
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, HandleBlurEvent001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    switchPattern->touchHoverType_ = TouchHoverAnimationType::FOCUS;
    switchPattern->HandleBlurEvent();
    EXPECT_EQ(switchPattern->touchHoverType_, TouchHoverAnimationType::NONE);
}

/**
 * @tc.name: HandleFocusEvent001
 * @tc.desc: Test SwitchPattern HandleFocusEvent when focusActive is true
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, HandleFocusEvent001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    // Ensure focusManager_ is initialized so GetIsFocusActive can return true
    auto pipeline = switchFrameNode->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->SetIsFocusActive(true);

    switchPattern->touchHoverType_ = TouchHoverAnimationType::NONE;
    switchPattern->HandleFocusEvent();
    EXPECT_EQ(switchPattern->touchHoverType_, TouchHoverAnimationType::FOCUS);
}

/**
 * @tc.name: HandleFocusEvent002
 * @tc.desc: Test SwitchPattern HandleFocusEvent when focusActive is false
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, HandleFocusEvent002, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    auto pipeline = switchFrameNode->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->SetIsFocusActive(false);

    switchPattern->touchHoverType_ = TouchHoverAnimationType::NONE;
    switchPattern->HandleFocusEvent();
    // When focusActive is false, OnIsFocusActiveUpdate is not called, type stays NONE
    EXPECT_EQ(switchPattern->touchHoverType_, TouchHoverAnimationType::NONE);
}

/**
 * @tc.name: AddIsFocusActiveUpdateEvent001
 * @tc.desc: Test SwitchPattern AddIsFocusActiveUpdateEvent creates callback when null
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, AddIsFocusActiveUpdateEvent001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    switchPattern->isFocusActiveUpdateEvent_ = nullptr;
    switchPattern->AddIsFocusActiveUpdateEvent();
    EXPECT_TRUE(switchPattern->isFocusActiveUpdateEvent_ != nullptr);
}

/**
 * @tc.name: AddIsFocusActiveUpdateEvent002
 * @tc.desc: Test SwitchPattern AddIsFocusActiveUpdateEvent preserves existing callback
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, AddIsFocusActiveUpdateEvent002, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    std::function<void(bool)> existingCallback = [](bool) {};
    switchPattern->isFocusActiveUpdateEvent_ = existingCallback;
    switchPattern->AddIsFocusActiveUpdateEvent();
    // Should not overwrite existing callback
    EXPECT_TRUE(switchPattern->isFocusActiveUpdateEvent_ != nullptr);
}

/**
 * @tc.name: OnIsFocusActiveUpdate001
 * @tc.desc: Test SwitchPattern OnIsFocusActiveUpdate when isFocusActive is true
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, OnIsFocusActiveUpdate001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    switchPattern->OnIsFocusActiveUpdate(true);
    EXPECT_EQ(switchPattern->touchHoverType_, TouchHoverAnimationType::FOCUS);
}

/**
 * @tc.name: OnIsFocusActiveUpdate002
 * @tc.desc: Test SwitchPattern OnIsFocusActiveUpdate when isFocusActive is false
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, OnIsFocusActiveUpdate002, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    switchPattern->OnIsFocusActiveUpdate(false);
    EXPECT_EQ(switchPattern->touchHoverType_, TouchHoverAnimationType::NONE);
}

/**
 * @tc.name: UpdateColorWhenIsOn001
 * @tc.desc: Test UpdateColorWhenIsOn when isOn is true and selectedColor matches theme
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, UpdateColorWhenIsOn001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    switchPattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    ASSERT_NE(switchPattern->paintMethod_, nullptr);
    switchPattern->switchTheme_ = AceType::MakeRefPtr<SwitchTheme>();
    ASSERT_NE(switchPattern->switchTheme_, nullptr);

    Color activeColor = switchPattern->switchTheme_->GetActiveColor();
    paintProperty->UpdateSelectedColor(activeColor);
    switchPattern->UpdateColorWhenIsOn(true);
    EXPECT_TRUE(paintProperty->HasSelectedColor());
}

/**
 * @tc.name: UpdateColorWhenIsOn002
 * @tc.desc: Test UpdateColorWhenIsOn when isOn is false and unselectedColor matches theme
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, UpdateColorWhenIsOn002, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    switchPattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    ASSERT_NE(switchPattern->paintMethod_, nullptr);
    switchPattern->switchTheme_ = AceType::MakeRefPtr<SwitchTheme>();
    ASSERT_NE(switchPattern->switchTheme_, nullptr);

    Color inactiveColor = switchPattern->switchTheme_->GetInactiveColor();
    paintProperty->UpdateUnselectedColor(inactiveColor);
    switchPattern->isFocus_ = false;
    switchPattern->UpdateColorWhenIsOn(false);
    EXPECT_TRUE(paintProperty->HasUnselectedColor());
}

/**
 * @tc.name: UpdateColorWhenIsOn003
 * @tc.desc: Test UpdateColorWhenIsOn when isOn is false, isFocus_ is true, and unselectedColor matches theme
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, UpdateColorWhenIsOn003, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    switchPattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    ASSERT_NE(switchPattern->paintMethod_, nullptr);
    switchPattern->switchTheme_ = AceType::MakeRefPtr<SwitchTheme>();
    ASSERT_NE(switchPattern->switchTheme_, nullptr);

    Color inactiveColor = switchPattern->switchTheme_->GetInactiveColor();
    paintProperty->UpdateUnselectedColor(inactiveColor);
    switchPattern->isFocus_ = true;
    switchPattern->UpdateColorWhenIsOn(false);
    EXPECT_TRUE(paintProperty->HasUnselectedColor());
}

/**
 * @tc.name: UpdateColorWhenIsOn004
 * @tc.desc: Test UpdateColorWhenIsOn when isOn is true but selectedColor does not match theme
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, UpdateColorWhenIsOn004, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    switchPattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    ASSERT_NE(switchPattern->paintMethod_, nullptr);
    switchPattern->switchTheme_ = AceType::MakeRefPtr<SwitchTheme>();
    ASSERT_NE(switchPattern->switchTheme_, nullptr);

    // Set a different selected color that doesn't match theme active color
    paintProperty->UpdateSelectedColor(Color::RED);
    Color prevColor = paintProperty->GetSelectedColor().value();
    switchPattern->UpdateColorWhenIsOn(true);
    // Color should not be updated since it doesn't match theme active color
    EXPECT_EQ(paintProperty->GetSelectedColor().value(), prevColor);
}

/**
 * @tc.name: UpdateColorWhenIsOn005
 * @tc.desc: Test UpdateColorWhenIsOn when isOn is false and unselectedColor does not match theme
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, UpdateColorWhenIsOn005, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    switchPattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    ASSERT_NE(switchPattern->paintMethod_, nullptr);
    switchPattern->switchTheme_ = AceType::MakeRefPtr<SwitchTheme>();
    ASSERT_NE(switchPattern->switchTheme_, nullptr);

    // Set a different unselected color that doesn't match theme inactive color
    paintProperty->UpdateUnselectedColor(Color::GREEN);
    Color prevColor = paintProperty->GetUnselectedColor().value();
    switchPattern->isFocus_ = false;
    switchPattern->UpdateColorWhenIsOn(false);
    // Color should not be updated since it doesn't match theme inactive color
    EXPECT_EQ(paintProperty->GetUnselectedColor().value(), prevColor);
}

/**
 * @tc.name: GetInnerFocusPaintRect001
 * @tc.desc: Test GetInnerFocusPaintRect when pointRadius * 2 > height
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, GetInnerFocusPaintRect001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    switchPattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    ASSERT_NE(switchPattern->paintMethod_, nullptr);
    auto switchModifier = AceType::MakeRefPtr<SwitchModifier>(
        SizeF(FORTY_FLOAT, THIRTY_FLOAT), OffsetF(ZERO_FLOAT, ZERO_FLOAT), ZERO_FLOAT, true,
        Color::WHITE, Color::WHITE, ZERO_FLOAT);
    ASSERT_NE(switchModifier, nullptr);
    switchPattern->paintMethod_->switchModifier_ = switchModifier;

    // pointRadius * 2 > height_ branch
    constexpr float TEST_HEIGHT = 20.0f;
    constexpr float TEST_WIDTH = 60.0f;
    constexpr float TEST_POINT_RADIUS = 15.0f;
    constexpr float TEST_TRACK_RADIUS = 10.0f;
    switchPattern->height_ = TEST_HEIGHT;
    switchPattern->width_ = TEST_WIDTH;
    switchPattern->offset_ = OffsetF(ZERO_FLOAT, ZERO_FLOAT);
    switchModifier->pointRadius_ = TEST_POINT_RADIUS;
    switchModifier->SetActualTrackRadius(TEST_TRACK_RADIUS);

    RoundRect paintRect;
    EXPECT_NO_FATAL_FAILURE(switchPattern->GetInnerFocusPaintRect(paintRect));
}

/**
 * @tc.name: GetInnerFocusPaintRect002
 * @tc.desc: Test GetInnerFocusPaintRect when pointRadius * 2 <= height and trackRadius != SWITCH_ERROR_RADIUS
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, GetInnerFocusPaintRect002, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    switchPattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    ASSERT_NE(switchPattern->paintMethod_, nullptr);
    auto switchModifier = AceType::MakeRefPtr<SwitchModifier>(
        SizeF(FORTY_FLOAT, THIRTY_FLOAT), OffsetF(ZERO_FLOAT, ZERO_FLOAT), ZERO_FLOAT, true,
        Color::WHITE, Color::WHITE, ZERO_FLOAT);
    ASSERT_NE(switchModifier, nullptr);
    switchPattern->paintMethod_->switchModifier_ = switchModifier;

    // pointRadius * 2 <= height_ branch, trackRadius != SWITCH_ERROR_RADIUS
    constexpr float TEST_HEIGHT = 50.0f;
    constexpr float TEST_WIDTH = 80.0f;
    constexpr float TEST_POINT_RADIUS = 10.0f;
    constexpr float TEST_TRACK_RADIUS = 25.0f;
    switchPattern->height_ = TEST_HEIGHT;
    switchPattern->width_ = TEST_WIDTH;
    switchPattern->offset_ = OffsetF(ZERO_FLOAT, ZERO_FLOAT);
    switchModifier->pointRadius_ = TEST_POINT_RADIUS;
    switchModifier->SetActualTrackRadius(TEST_TRACK_RADIUS);

    RoundRect paintRect;
    EXPECT_NO_FATAL_FAILURE(switchPattern->GetInnerFocusPaintRect(paintRect));
}

/**
 * @tc.name: GetInnerFocusPaintRect003
 * @tc.desc: Test GetInnerFocusPaintRect when pointRadius * 2 > height and width < height
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, GetInnerFocusPaintRect003, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    switchPattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    ASSERT_NE(switchPattern->paintMethod_, nullptr);
    auto switchModifier = AceType::MakeRefPtr<SwitchModifier>(
        SizeF(FORTY_FLOAT, THIRTY_FLOAT), OffsetF(ZERO_FLOAT, ZERO_FLOAT), ZERO_FLOAT, true,
        Color::WHITE, Color::WHITE, ZERO_FLOAT);
    ASSERT_NE(switchModifier, nullptr);
    switchPattern->paintMethod_->switchModifier_ = switchModifier;

    // pointRadius * 2 > height_ and width_ < height_ sub-branch
    constexpr float TEST_HEIGHT = 20.0f;
    constexpr float TEST_WIDTH = 15.0f;
    constexpr float TEST_POINT_RADIUS = 15.0f;
    constexpr float TEST_TRACK_RADIUS = 10.0f;
    switchPattern->height_ = TEST_HEIGHT;
    switchPattern->width_ = TEST_WIDTH;
    switchPattern->offset_ = OffsetF(ZERO_FLOAT, ZERO_FLOAT);
    switchModifier->pointRadius_ = TEST_POINT_RADIUS;
    switchModifier->SetActualTrackRadius(TEST_TRACK_RADIUS);

    RoundRect paintRect;
    EXPECT_NO_FATAL_FAILURE(switchPattern->GetInnerFocusPaintRect(paintRect));
}

/**
 * @tc.name: GetInnerFocusPaintRect004
 * @tc.desc: Test GetInnerFocusPaintRect when pointRadius * 2 <= height and width < height and pointRadius > trackRadius
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, GetInnerFocusPaintRect004, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    switchPattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    ASSERT_NE(switchPattern->paintMethod_, nullptr);
    auto switchModifier = AceType::MakeRefPtr<SwitchModifier>(
        SizeF(FORTY_FLOAT, THIRTY_FLOAT), OffsetF(ZERO_FLOAT, ZERO_FLOAT), ZERO_FLOAT, true,
        Color::WHITE, Color::WHITE, ZERO_FLOAT);
    ASSERT_NE(switchModifier, nullptr);
    switchPattern->paintMethod_->switchModifier_ = switchModifier;

    // pointRadius * 2 <= height_, width_ < height_ and pointRadius > trackRadius
    constexpr float TEST_HEIGHT = 50.0f;
    constexpr float TEST_WIDTH = 30.0f;
    constexpr float TEST_POINT_RADIUS = 20.0f;
    constexpr float TEST_TRACK_RADIUS = 10.0f;
    switchPattern->height_ = TEST_HEIGHT;
    switchPattern->width_ = TEST_WIDTH;
    switchPattern->offset_ = OffsetF(ZERO_FLOAT, ZERO_FLOAT);
    switchModifier->pointRadius_ = TEST_POINT_RADIUS;
    switchModifier->SetActualTrackRadius(TEST_TRACK_RADIUS);

    RoundRect paintRect;
    EXPECT_NO_FATAL_FAILURE(switchPattern->GetInnerFocusPaintRect(paintRect));
}

/**
 * @tc.name: GetInnerFocusPaintRect005
 * @tc.desc: Test GetInnerFocusPaintRect when trackRadius == SWITCH_ERROR_RADIUS
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, GetInnerFocusPaintRect005, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    switchPattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    ASSERT_NE(switchPattern->paintMethod_, nullptr);
    auto switchModifier = AceType::MakeRefPtr<SwitchModifier>(
        SizeF(FORTY_FLOAT, THIRTY_FLOAT), OffsetF(ZERO_FLOAT, ZERO_FLOAT), ZERO_FLOAT, true,
        Color::WHITE, Color::WHITE, ZERO_FLOAT);
    ASSERT_NE(switchModifier, nullptr);
    switchPattern->paintMethod_->switchModifier_ = switchModifier;

    // trackRadius == SWITCH_ERROR_RADIUS branch
    constexpr float TEST_HEIGHT = 50.0f;
    constexpr float TEST_WIDTH = 80.0f;
    constexpr float TEST_POINT_RADIUS = 10.0f;
    switchPattern->height_ = TEST_HEIGHT;
    switchPattern->width_ = TEST_WIDTH;
    switchPattern->offset_ = OffsetF(ZERO_FLOAT, ZERO_FLOAT);
    switchModifier->pointRadius_ = TEST_POINT_RADIUS;
    switchModifier->SetActualTrackRadius(SWITCH_ERROR_RADIUS);

    RoundRect paintRect;
    EXPECT_NO_FATAL_FAILURE(switchPattern->GetInnerFocusPaintRect(paintRect));
}

/**
 * @tc.name: DumpSimplifyInfoOnlyForParamConfig001
 * @tc.desc: Test DumpSimplifyInfoOnlyForParamConfig when isOn is true and interactionInfo is true
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, DumpSimplifyInfoOnlyForParamConfig001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(true);

    auto json = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    config.interactionInfo = true;
    switchPattern->DumpSimplifyInfoOnlyForParamConfig(json, config);
    EXPECT_NE(json->GetString("isOn"), "");
}

/**
 * @tc.name: DumpSimplifyInfoOnlyForParamConfig002
 * @tc.desc: Test DumpSimplifyInfoOnlyForParamConfig when isOn is false
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, DumpSimplifyInfoOnlyForParamConfig002, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(false);

    auto json = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    config.interactionInfo = true;
    switchPattern->DumpSimplifyInfoOnlyForParamConfig(json, config);
    EXPECT_NE(json->GetString("isOn"), "");
}

/**
 * @tc.name: DumpSimplifyInfoOnlyForParamConfig003
 * @tc.desc: Test DumpSimplifyInfoOnlyForParamConfig when interactionInfo is false
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, DumpSimplifyInfoOnlyForParamConfig003, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(true);

    auto json = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    config.interactionInfo = false;
    switchPattern->DumpSimplifyInfoOnlyForParamConfig(json, config);
    // When interactionInfo is false, isOn should not be written even if HasIsOn is true
    EXPECT_EQ(json->GetString("isOn"), "");
}

/**
 * @tc.name: DumpSimplifyInfoOnlyForParamConfig004
 * @tc.desc: Test DumpSimplifyInfoOnlyForParamConfig when HasIsOn is false
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierAddTestNg, DumpSimplifyInfoOnlyForParamConfig004, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    auto switchPattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);

    auto paintProperty = switchFrameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    // Reset IsOn so HasIsOn returns false (Create sets it by default)
    paintProperty->ResetIsOn();

    auto json = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    config.interactionInfo = true;
    switchPattern->DumpSimplifyInfoOnlyForParamConfig(json, config);
    // When HasIsOn is false, isOn should not be written
    EXPECT_EQ(json->GetString("isOn"), "");
}
} // namespace OHOS::Ace::NG
