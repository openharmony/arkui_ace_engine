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
#include "core/components/checkable/checkable_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
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
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr int BIG_INT = 100000000;
constexpr int NEGATIVE_BIG_INT = -100000000;
constexpr int CHILD_NODE_ID = 100;
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
} // namespace OHOS::Ace::NG