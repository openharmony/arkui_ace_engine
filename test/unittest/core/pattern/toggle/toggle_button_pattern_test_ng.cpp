/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/json/json_util.h"
#include "core/components/button/button_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr bool IS_OFF = false;
const char TOGGLE_ETS_TAG[] = "Toggle";
constexpr int32_t DEFAULT_BUILDER_ID = -1;
// Injection command JSON payloads consumed by ParseCommand / OnInjectionEvent.
const std::string INJECTION_CMD_ON = R"({"cmd":"onToggleChange","params":{"isOn":true}})";
const std::string INJECTION_CMD_OFF = R"({"cmd":"onToggleChange","params":{"isOn":false}})";
const std::string INJECTION_CMD_BAD_FORMAT = "invalid_json_string";
const std::string INJECTION_CMD_WRONG_CMD = R"({"cmd":"other","params":{"isOn":true}})";
const std::string INJECTION_CMD_MISSING_PARAM = R"({"cmd":"onToggleChange","params":{}})";
const std::string INJECTION_CMD_NON_BOOL = R"({"cmd":"onToggleChange","params":{"isOn":"yes"}})";
} // namespace

class ToggleButtonPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static RefPtr<FrameNode> CreateToggleButton(bool isOn);
    static RefPtr<ToggleButtonPattern> GetPattern(const RefPtr<FrameNode>& node);
};

void ToggleButtonPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ButtonTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ButtonTheme>()));
}

void ToggleButtonPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> ToggleButtonPatternTestNg::CreateToggleButton(bool isOn)
{
    ToggleButtonModelNG toggleButtonModelNG;
    toggleButtonModelNG.Create(TOGGLE_ETS_TAG);
    toggleButtonModelNG.SetIsOn(isOn);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    if (frameNode) {
        frameNode->MarkModifyDone();
    }
    return frameNode;
}

RefPtr<ToggleButtonPattern> ToggleButtonPatternTestNg::GetPattern(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    return AceType::DynamicCast<ToggleButtonPattern>(node->GetPattern());
}

// ============================================================
// MarkIsSelected tests
// ============================================================

/**
 * @tc.name: ToggleButton_MarkIsSelected_On
 * @tc.desc: Test MarkIsSelected flips the toggle on when it is currently off.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_MarkIsSelected_On, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->isOn_.value_or(IS_OFF));
    // Selecting when currently off flips the state to on.
    pattern->MarkIsSelected(IS_ON);
    EXPECT_TRUE(pattern->isOn_.value_or(IS_OFF));
}

/**
 * @tc.name: ToggleButton_MarkIsSelected_Off
 * @tc.desc: Test MarkIsSelected flips the toggle off when it is currently on.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_MarkIsSelected_Off, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_ON);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->isOn_.value_or(IS_OFF));
    // Clearing selection when currently on flips the state to off.
    pattern->MarkIsSelected(IS_OFF);
    EXPECT_FALSE(pattern->isOn_.value_or(IS_OFF));
}

/**
 * @tc.name: ToggleButton_MarkIsSelected_SameState_NoEvent
 * @tc.desc: Test MarkIsSelected takes the early-return branch and does not fire the change event
 *           when the target state equals the current state.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_MarkIsSelected_SameState_NoEvent, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_ON);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    bool eventFired = false;
    auto eventHub = pattern->GetEventHub<ToggleButtonEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnChange([&eventFired](const bool) { eventFired = true; });
    // Already on; selecting on again hits the early-return branch, so no event is fired.
    pattern->MarkIsSelected(IS_ON);
    EXPECT_FALSE(eventFired);
    // A real state change (on -> off) does fire the registered change event.
    pattern->MarkIsSelected(IS_OFF);
    EXPECT_TRUE(eventFired);
}

// ============================================================
// SetButtonPress tests
// ============================================================

/**
 * @tc.name: ToggleButton_SetButtonPress_Enabled
 * @tc.desc: Test SetButtonPress updates the IsOn paint property when the toggle is enabled.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_SetButtonPress_Enabled, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = node->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_FALSE(paintProperty->GetIsOnValue(IS_OFF));
    pattern->SetButtonPress(IS_ON);
    EXPECT_TRUE(paintProperty->GetIsOnValue(IS_OFF));
}

/**
 * @tc.name: ToggleButton_SetButtonPress_Disabled
 * @tc.desc: Test SetButtonPress returns early and leaves IsOn unchanged when the toggle is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_SetButtonPress_Disabled, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    auto eventHub = node->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(IS_OFF);
    auto paintProperty = node->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    // Disabled: the early-return branch keeps IsOn unchanged.
    pattern->SetButtonPress(IS_ON);
    EXPECT_FALSE(paintProperty->GetIsOnValue(IS_OFF));
}

// ============================================================
// OnInjectionEvent / ParseCommand tests
// ============================================================

/**
 * @tc.name: ToggleButton_OnInjectionEvent_Valid
 * @tc.desc: Test OnInjectionEvent applies a well-formed on command and reports success.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_OnInjectionEvent_Valid, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->OnInjectionEvent(INJECTION_CMD_ON), RET_SUCCESS);
    auto paintProperty = node->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->GetIsOnValue(IS_OFF));
}

/**
 * @tc.name: ToggleButton_OnInjectionEvent_BadFormat
 * @tc.desc: Test OnInjectionEvent rejects a malformed command with RET_FAILED.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_OnInjectionEvent_BadFormat, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->OnInjectionEvent(INJECTION_CMD_BAD_FORMAT), RET_FAILED);
}

/**
 * @tc.name: ToggleButton_OnInjectionEvent_WrongCmd
 * @tc.desc: Test OnInjectionEvent rejects a command whose cmd field is not onToggleChange.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_OnInjectionEvent_WrongCmd, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->OnInjectionEvent(INJECTION_CMD_WRONG_CMD), RET_FAILED);
}

/**
 * @tc.name: ToggleButton_OnInjectionEvent_ReadOnly
 * @tc.desc: Test OnInjectionEvent rejects the command when the toggle is disabled (read-only).
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_OnInjectionEvent_ReadOnly, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    auto eventHub = node->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(IS_OFF);
    EXPECT_EQ(pattern->OnInjectionEvent(INJECTION_CMD_ON), RET_FAILED);
}

/**
 * @tc.name: ToggleButton_ParseCommand_Valid
 * @tc.desc: Test ParseCommand parses a well-formed command and extracts the isOn flag.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_ParseCommand_Valid, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    bool isOn = IS_OFF;
    EXPECT_TRUE(pattern->ParseCommand(INJECTION_CMD_ON, isOn));
    EXPECT_TRUE(isOn);
}

/**
 * @tc.name: ToggleButton_ParseCommand_Invalid
 * @tc.desc: Test ParseCommand rejects malformed and incomplete commands.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_ParseCommand_Invalid, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    bool isOn = IS_OFF;
    // Malformed JSON, wrong cmd, missing param, and non-bool param are all rejected.
    EXPECT_FALSE(pattern->ParseCommand(INJECTION_CMD_BAD_FORMAT, isOn));
    EXPECT_FALSE(pattern->ParseCommand(INJECTION_CMD_WRONG_CMD, isOn));
    EXPECT_FALSE(pattern->ParseCommand(INJECTION_CMD_MISSING_PARAM, isOn));
    EXPECT_FALSE(pattern->ParseCommand(INJECTION_CMD_NON_BOOL, isOn));
}

// ============================================================
// ProvideRestoreInfo / OnRestoreInfo tests
// ============================================================

/**
 * @tc.name: ToggleButton_ProvideRestoreInfo_On
 * @tc.desc: Test ProvideRestoreInfo serializes the on state as {"IsOn":true}.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_ProvideRestoreInfo_On, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_ON);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->ProvideRestoreInfo(), R"({"IsOn":true})");
}

/**
 * @tc.name: ToggleButton_ProvideRestoreInfo_Off
 * @tc.desc: Test ProvideRestoreInfo serializes the off state as {"IsOn":false}.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_ProvideRestoreInfo_Off, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->ProvideRestoreInfo(), R"({"IsOn":false})");
}

/**
 * @tc.name: ToggleButton_OnRestoreInfo_RoundTrip
 * @tc.desc: Test OnRestoreInfo applies a valid restore info and flips IsOn to true.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_OnRestoreInfo_RoundTrip, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    pattern->OnRestoreInfo(R"({"IsOn":true})");
    auto paintProperty = node->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->GetIsOnValue(IS_OFF));
}

/**
 * @tc.name: ToggleButton_OnRestoreInfo_InvalidJson
 * @tc.desc: Test OnRestoreInfo ignores malformed restore info and leaves IsOn unchanged.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_OnRestoreInfo_InvalidJson, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = node->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    pattern->OnRestoreInfo("invalid");
    EXPECT_FALSE(paintProperty->GetIsOnValue(IS_OFF));
}

// ============================================================
// ToTreeJson / GetBuilderId tests
// ============================================================

/**
 * @tc.name: ToggleButton_ToTreeJson_Checked
 * @tc.desc: Test ToTreeJson emits the checked flag as "true" when the toggle is on.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_ToTreeJson_Checked, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_ON);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    InspectorConfig config;
    pattern->ToTreeJson(json, config);
    EXPECT_EQ(json->GetValue(TreeKey::CHECKED)->GetString(), "true");
}

/**
 * @tc.name: ToggleButton_ToTreeJson_Unchecked
 * @tc.desc: Test ToTreeJson emits the checked flag as "false" when the on-state is not initialized.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_ToTreeJson_Unchecked, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    // ToTreeJson reads the optional isOn_ in a boolean context, so it reports "false" only when
    // the on-state is disengaged. Reset it to exercise that branch.
    pattern->isOn_ = std::nullopt;
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    InspectorConfig config;
    pattern->ToTreeJson(json, config);
    EXPECT_EQ(json->GetValue(TreeKey::CHECKED)->GetString(), "false");
}

/**
 * @tc.name: ToggleButton_GetBuilderId_Default
 * @tc.desc: Test GetBuilderId returns the default invalid id when no content modifier is attached.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButton_GetBuilderId_Default, TestSize.Level1)
{
    auto node = CreateToggleButton(IS_ON);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    // No builder has been attached, so the builder id stays at its default value.
    EXPECT_EQ(pattern->GetBuilderId(), DEFAULT_BUILDER_ID);
}
} // namespace OHOS::Ace::NG
