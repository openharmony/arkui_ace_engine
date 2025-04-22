/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
const std::vector<NG::ToggleType> TOGGLE_TYPE = { ToggleType::CHECKBOX, ToggleType::BUTTON, ToggleType::SWITCH };
} // namespace

class ToggleContentModifierTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static PaddingPropertyF CreatePadding(Dimension length);
};

void ToggleContentModifierTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void ToggleContentModifierTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

PaddingPropertyF ToggleContentModifierTestNg::CreatePadding(Dimension length)
{
    PaddingPropertyF padding;
    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    return padding;
}

/**
 * @tc.name: ToggleContentModifierTest001
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest001, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
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
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest002
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest002, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(false, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest003
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest003, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);
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
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest004
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest004, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(false, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest005
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest005, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(-1);
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
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest006
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest006, TestSize.Level1)
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
    pattern->SetSwitchIsOn(1);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
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
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest007
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest007, TestSize.Level1)
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
    pattern->SetSwitchIsOn(0);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(false, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest008
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest008, TestSize.Level1)
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
    pattern->SetSwitchIsOn(-1);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
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
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest009
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest009, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest010
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest010, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(false, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest011
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest011, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest012
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest012, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(false, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest013
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest013, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(-1);
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest014
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest014, TestSize.Level1)
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
    pattern->SetButtonPress(1);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest015
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest015, TestSize.Level1)
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
    pattern->SetButtonPress(0);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(false, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest016
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest016, TestSize.Level1)
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
    pattern->SetButtonPress(-1);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest017
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest017, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(IS_ON);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest018
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest018, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(IS_ON);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(false, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest019
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest019, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(IS_ON);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest020
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest020, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(IS_ON);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_ON, config.isOn_);
                EXPECT_EQ(false, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest021
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest021, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(IS_ON);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(-1);
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest022
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest022, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(1);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest023
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest023, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(0);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ToggleConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(false, config.isOn_);
                EXPECT_EQ(IS_ON, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest024
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest024, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(-1);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest025
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest025, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(BIG_INT);
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
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest026
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest026, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
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
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest027
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest027, TestSize.Level1)
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
    pattern->SetSwitchIsOn(BIG_INT);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
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
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest028
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest028, TestSize.Level1)
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
    pattern->SetSwitchIsOn(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::SwitchEventHub>();
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
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest029
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest029, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(IS_ON);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(BIG_INT);
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest030
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest030, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(IS_ON);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest031
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest031, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(BIG_INT);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest032
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest032, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest033
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest033, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(BIG_INT);
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest034
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest034, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest035
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest035, TestSize.Level1)
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
    pattern->SetButtonPress(BIG_INT);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest036
 * @tc.desc: SetToggleBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest036, TestSize.Level1)
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
    pattern->SetButtonPress(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::ToggleButtonEventHub>();
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
    pattern->SetToggleBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: ToggleContentModifierTest037
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest037, TestSize.Level1)
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
    pattern->SetSwitchIsOn(IS_ON);
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
 * @tc.name: ToggleContentModifierTest038
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest038, TestSize.Level1)
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
    pattern->SetSwitchIsOn(false);
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
    EXPECT_EQ(isOn, false);
}

/**
 * @tc.name: ToggleContentModifierTest039
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest039, TestSize.Level1)
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
    pattern->SetSwitchIsOn(0);
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
    EXPECT_EQ(isOn, false);
}

/**
 * @tc.name: ToggleContentModifierTest041
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest041, TestSize.Level1)
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
    pattern->SetSwitchIsOn(-1);
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
 * @tc.name: ToggleContentModifierTest042
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest042, TestSize.Level1)
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
    pattern->SetSwitchIsOn(BIG_INT);
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
 * @tc.name: ToggleContentModifierTest043
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest043, TestSize.Level1)
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
    pattern->SetSwitchIsOn(NEGATIVE_BIG_INT);
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
 * @tc.name: ToggleContentModifierTest044
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest044, TestSize.Level1)
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
    pattern->SetButtonPress(IS_ON);
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
 * @tc.name: ToggleContentModifierTest045
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest045, TestSize.Level1)
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
    pattern->SetButtonPress(false);
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
    EXPECT_EQ(isOn, false);
}

/**
 * @tc.name: ToggleContentModifierTest046
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest046, TestSize.Level1)
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
    pattern->SetButtonPress(0);
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
    EXPECT_EQ(isOn, false);
}

/**
 * @tc.name: ToggleContentModifierTest048
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest048, TestSize.Level1)
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
    pattern->SetButtonPress(-1);
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
 * @tc.name: ToggleContentModifierTest050
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest050, TestSize.Level1)
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
    pattern->SetButtonPress(NEGATIVE_BIG_INT);
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
 * @tc.name: ToggleContentModifierTest051
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest051, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(BIG_INT);
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
 * @tc.name: ToggleContentModifierTest053
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleContentModifierTestNg, ToggleContentModifierTest053, TestSize.Level1)
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
    pattern->SetCheckBoxSelect(-1);
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
} // namespace OHOS::Ace::NG