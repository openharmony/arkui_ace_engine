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
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_event_hub.h"
#include "core/components_ng/pattern/checkbox/checkbox_model.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr bool IS_OFF = false;
constexpr int32_t CHECKBOX_NODE_ID = 10001;
constexpr int32_t TEST_PAGE_ID = 7;
const std::string TEST_PRE_NAME = "optionA";
// Injection command JSON payloads consumed by CheckBox::ParseCommand.
const std::string CB_CMD_SELECT = R"({"cmd":"selectCheckBox","selectStatus":true})";
const std::string CB_CMD_UNSELECT = R"({"cmd":"selectCheckBox","selectStatus":false})";
const std::string CB_CMD_BAD = "invalid_json_string";
const std::string CB_CMD_WRONG = R"({"cmd":"other","selectStatus":true})";
const std::string CB_CMD_NO_STATUS = R"({"cmd":"selectCheckBox"})";
const std::string CB_CMD_NON_BOOL = R"({"cmd":"selectCheckBox","selectStatus":"yes"})";
} // namespace

class ToggleCheckboxPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static RefPtr<FrameNode> CreateCheckBox(bool select);
    static RefPtr<CheckBoxPattern> GetPattern(const RefPtr<FrameNode>& node);
};

void ToggleCheckboxPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
}

void ToggleCheckboxPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> ToggleCheckboxPatternTestNg::CreateCheckBox(bool select)
{
    auto node = FrameNode::CreateFrameNode(
        V2::CHECK_BOX_ETS_TAG, CHECKBOX_NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    if (node) {
        auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
        if (paintProperty) {
            paintProperty->UpdateCheckBoxSelect(select);
        }
    }
    return node;
}

RefPtr<CheckBoxPattern> ToggleCheckboxPatternTestNg::GetPattern(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    return AceType::DynamicCast<CheckBoxPattern>(node->GetPattern());
}

// ============================================================
// ParseCommand (static) tests
// ============================================================

/**
 * @tc.name: CheckBox_ParseCommand_BadFormat
 * @tc.desc: Test ParseCommand rejects malformed JSON with RET_FAILED.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_ParseCommand_BadFormat, TestSize.Level1)
{
    bool selectStatus = IS_OFF;
    EXPECT_EQ(CheckBoxPattern::ParseCommand(CB_CMD_BAD, selectStatus), RET_FAILED);
}

/**
 * @tc.name: CheckBox_ParseCommand_WrongCmd
 * @tc.desc: Test ParseCommand rejects a command whose cmd field is not selectCheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_ParseCommand_WrongCmd, TestSize.Level1)
{
    bool selectStatus = IS_OFF;
    EXPECT_EQ(CheckBoxPattern::ParseCommand(CB_CMD_WRONG, selectStatus), RET_FAILED);
}

/**
 * @tc.name: CheckBox_ParseCommand_MissingSelectStatus
 * @tc.desc: Test ParseCommand rejects a command that lacks the selectStatus field.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_ParseCommand_MissingSelectStatus, TestSize.Level1)
{
    bool selectStatus = IS_OFF;
    EXPECT_EQ(CheckBoxPattern::ParseCommand(CB_CMD_NO_STATUS, selectStatus), RET_FAILED);
}

/**
 * @tc.name: CheckBox_ParseCommand_NonBoolStatus
 * @tc.desc: Test ParseCommand rejects a command whose selectStatus field is not a boolean.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_ParseCommand_NonBoolStatus, TestSize.Level1)
{
    bool selectStatus = IS_OFF;
    EXPECT_EQ(CheckBoxPattern::ParseCommand(CB_CMD_NON_BOOL, selectStatus), RET_FAILED);
}

/**
 * @tc.name: CheckBox_ParseCommand_Select
 * @tc.desc: Test ParseCommand accepts a well-formed select command and extracts selectStatus true.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_ParseCommand_Select, TestSize.Level1)
{
    bool selectStatus = IS_OFF;
    EXPECT_EQ(CheckBoxPattern::ParseCommand(CB_CMD_SELECT, selectStatus), RET_SUCCESS);
    EXPECT_TRUE(selectStatus);
}

/**
 * @tc.name: CheckBox_ParseCommand_Unselect
 * @tc.desc: Test ParseCommand accepts a well-formed unselect command and extracts selectStatus false.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_ParseCommand_Unselect, TestSize.Level1)
{
    bool selectStatus = IS_ON;
    EXPECT_EQ(CheckBoxPattern::ParseCommand(CB_CMD_UNSELECT, selectStatus), RET_SUCCESS);
    EXPECT_FALSE(selectStatus);
}

// ============================================================
// ToTreeJson tests
// ============================================================

/**
 * @tc.name: CheckBox_ToTreeJson_Checked
 * @tc.desc: Test ToTreeJson emits the checked flag as "true" when the checkbox is selected.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_ToTreeJson_Checked, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_ON);
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
 * @tc.name: CheckBox_ToTreeJson_Unchecked
 * @tc.desc: Test ToTreeJson emits the checked flag as "false" when the checkbox is unselected.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_ToTreeJson_Unchecked, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    InspectorConfig config;
    pattern->ToTreeJson(json, config);
    EXPECT_EQ(json->GetValue(TreeKey::CHECKED)->GetString(), "false");
}

// ============================================================
// ProvideRestoreInfo / OnRestoreInfo tests
// ============================================================

/**
 * @tc.name: CheckBox_ProvideRestoreInfo_Selected
 * @tc.desc: Test ProvideRestoreInfo serializes the selected state as {"isOn":true}.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_ProvideRestoreInfo_Selected, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_ON);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->ProvideRestoreInfo(), R"({"isOn":true})");
}

/**
 * @tc.name: CheckBox_ProvideRestoreInfo_Unselected
 * @tc.desc: Test ProvideRestoreInfo serializes the unselected state as {"isOn":false}.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_ProvideRestoreInfo_Unselected, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->ProvideRestoreInfo(), R"({"isOn":false})");
}

/**
 * @tc.name: CheckBox_OnRestoreInfo_RoundTrip
 * @tc.desc: Test OnRestoreInfo applies valid restore info and flips CheckBoxSelect to true.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_OnRestoreInfo_RoundTrip, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    pattern->OnRestoreInfo(R"({"isOn":true})");
    auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->GetCheckBoxSelectValue(IS_OFF));
}

/**
 * @tc.name: CheckBox_OnRestoreInfo_InvalidJson
 * @tc.desc: Test OnRestoreInfo ignores malformed restore info and leaves CheckBoxSelect unchanged.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_OnRestoreInfo_InvalidJson, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    pattern->OnRestoreInfo("invalid");
    auto paintProperty = node->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_FALSE(paintProperty->GetCheckBoxSelectValue(IS_OFF));
}

// ============================================================
// Simple getter/setter and capability tests
// ============================================================

/**
 * @tc.name: CheckBox_SetOriginalCheckboxStyle_Get
 * @tc.desc: Test SetOriginalCheckboxStyle updates the value returned by GetOriginalCheckboxStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_SetOriginalCheckboxStyle_Get, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetOriginalCheckboxStyle(), OriginalCheckBoxStyle::CIRCULAR_STYLE);
    pattern->SetOriginalCheckboxStyle(OriginalCheckBoxStyle::SQUARE_STYLE);
    EXPECT_EQ(pattern->GetOriginalCheckboxStyle(), OriginalCheckBoxStyle::SQUARE_STYLE);
}

/**
 * @tc.name: CheckBox_SetPreName_GetPreName
 * @tc.desc: Test SetPreName updates the value returned by GetPreName.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_SetPreName_GetPreName, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->GetPreName().has_value());
    pattern->SetPreName(TEST_PRE_NAME);
    ASSERT_TRUE(pattern->GetPreName().has_value());
    EXPECT_EQ(pattern->GetPreName().value(), TEST_PRE_NAME);
}

/**
 * @tc.name: CheckBox_SetPrePageId_GetPrePageId
 * @tc.desc: Test SetPrePageId updates the value returned by GetPrePageId.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_SetPrePageId_GetPrePageId, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    pattern->SetPrePageId(TEST_PAGE_ID);
    EXPECT_EQ(pattern->GetPrePageId(), TEST_PAGE_ID);
}

/**
 * @tc.name: CheckBox_IsEnableMatchParent
 * @tc.desc: Test IsEnableMatchParent returns true so the checkbox can match its parent in layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_IsEnableMatchParent, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsEnableMatchParent());
}

/**
 * @tc.name: CheckBox_IsEnableFix
 * @tc.desc: Test IsEnableFix returns true so the checkbox supports fix-sized layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_IsEnableFix, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsEnableFix());
}

/**
 * @tc.name: CheckBox_SetLastSelect
 * @tc.desc: Test SetLastSelect updates the internal last-select flag.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_SetLastSelect, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->lastSelect_);
    pattern->SetLastSelect(IS_ON);
    EXPECT_TRUE(pattern->lastSelect_);
}

/**
 * @tc.name: CheckBox_SetIndicatorBuilder
 * @tc.desc: Test SetIndicatorBuilder stores the provided builder callback.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_SetIndicatorBuilder, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->builder_.has_value());
    std::optional<std::function<void()>> builder = []() {};
    pattern->SetIndicatorBuilder(builder);
    EXPECT_TRUE(pattern->builder_.has_value());
}

// ============================================================
// MarkIsSelected tests
// ============================================================

/**
 * @tc.name: CheckBox_MarkIsSelected_DifferentState
 * @tc.desc: Test MarkIsSelected updates lastSelect and fires events when the target differs from the current state.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_MarkIsSelected_DifferentState, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    // Default last-select is false; selecting true is a real state change.
    EXPECT_FALSE(pattern->lastSelect_);
    pattern->MarkIsSelected(IS_ON);
    EXPECT_TRUE(pattern->lastSelect_);
}

/**
 * @tc.name: CheckBox_MarkIsSelected_SameState_NoEvent
 * @tc.desc: Test MarkIsSelected takes the early-return branch and does not fire the change event
 *           when the target state equals the current state.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleCheckboxPatternTestNg, CheckBox_MarkIsSelected_SameState_NoEvent, TestSize.Level1)
{
    auto node = CreateCheckBox(IS_OFF);
    ASSERT_NE(node, nullptr);
    auto pattern = GetPattern(node);
    ASSERT_NE(pattern, nullptr);
    // Force the current state to selected so the next select is a no-op.
    pattern->SetLastSelect(IS_ON);
    bool eventFired = false;
    auto eventHub = pattern->GetEventHub<CheckBoxEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnChange([&eventFired](const bool) { eventFired = true; });
    // Already selected; selecting again hits the early-return branch, so no event is fired.
    pattern->MarkIsSelected(IS_ON);
    EXPECT_FALSE(eventFired);
    // A real state change (selected -> unselected) does fire the registered change event.
    pattern->MarkIsSelected(IS_OFF);
    EXPECT_TRUE(eventFired);
}
} // namespace OHOS::Ace::NG
