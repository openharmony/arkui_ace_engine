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
} // namespace OHOS::Ace::NG