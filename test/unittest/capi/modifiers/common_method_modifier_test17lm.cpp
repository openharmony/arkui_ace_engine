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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace GeneratedModifier {
    const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor();
    const GENERATED_ArkUIKeyEventAccessor* GetKeyEventAccessor();
}

class CommonMethodModifierTest17lm : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<SheetTheme>();
    }
    void* CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }
};

/*
* @tc.name: TabStopTestDefaultValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest17lm, TabStopTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    const bool defaultValue = false;
    EXPECT_EQ(focusHub->IsTabStop(), defaultValue);
}

/*
* @tc.name: TabStopTestValidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest17lm, TabStopTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTabStop, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    using TestStep = std::tuple<Ark_Boolean, bool>;
    static const std::vector<TestStep> testPlan = {
        {Converter::ArkValue<Ark_Boolean>(false), false}, {Converter::ArkValue<Ark_Boolean>(true), true}};

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setTabStop(node_, inputValue);
        EXPECT_EQ(focusHub->IsTabStop(), expectedValue);
    }
}

/*
* @tc.name: AccessibilityNextFocusIdTestDefaultValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest17lm, AccessibilityNextFocusIdTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    const std::string defaultValue = "";
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), defaultValue);
}

/*
* @tc.name: AccessibilityNextFocusIdTestValidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest17lm, AccessibilityNextFocusIdTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityNextFocusId, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    using TestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<TestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("id1"), "id1"}, {Converter::ArkValue<Ark_String>("id2"), "id2"}};

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityNextFocusId(node_, &inputValue);
        EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), expectedValue);
    }
}

// /*
// * @tc.name: AccessibilityDefaultFocusTestDefaultValues
// * @tc.desc:
// * @tc.type: FUNC
// */
HWTEST_F(CommonMethodModifierTest17lm, DISABLED_AccessibilityDefaultFocusTestDefaultValues, TestSize.Level1)
{
    LOGE("AccessibilityManager::SendFrameNodeToAccessibility(...) is empty body");
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
}

/*
* @tc.name: AccessibilityDefaultFocusTestValidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest17lm, DISABLED_AccessibilityDefaultFocusTestValidValues, TestSize.Level1)
{
    LOGE("AccessibilityManager::SendFrameNodeToAccessibility(...) is empty body");
    ASSERT_NE(modifier_->setAccessibilityDefaultFocus, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    // test/mock/core/pipeline/mock_pipeline_context.cpp
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    ASSERT_NE(accessibilityManager, nullptr);

    bool isFocus = true;
    modifier_->setAccessibilityDefaultFocus(node_, isFocus);
    // auto defaultFocusList = accessibilityManager->GetDefaultFocusList();
    // std::cout << "test defaultFocusList: "  << std::hex << defaultFocusList.size() << std::endl;
    // EXPECT_EQ(defaultFocusList.empty(), false);
    // EXPECT_EQ(defaultFocusList[0], node_);
}

/*
* @tc.name: AccessibilityUseSamePageTestDefaultValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest17lm, AccessibilityUseSamePageTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const std::string defaultValue = "";
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->HasAccessibilitySamePage(), false);
    EXPECT_EQ(accessibilityProperty->GetAccessibilitySamePage(), defaultValue);
}

/*
* @tc.name: AccessibilityUseSamePageTestValidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest17lm, AccessibilityUseSamePageTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityUseSamePage, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    using TestStep = std::tuple<Ark_AccessibilitySamePageMode, std::string>;
    static const std::vector<TestStep> testPlan = {
        {ARK_ACCESSIBILITY_SAME_PAGE_MODE_FULL_SILENT, "FULL_SILENT"},
        {ARK_ACCESSIBILITY_SAME_PAGE_MODE_SEMI_SILENT, "SEMI_SILENT"}};

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityUseSamePage(node_, inputValue);
        EXPECT_TRUE(accessibilityProperty->HasAccessibilitySamePage());
        EXPECT_EQ(accessibilityProperty->GetAccessibilitySamePage(), expectedValue);
    }
}

/*
* @tc.name: AccessibilityUseSamePageTestInvalidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest17lm, AccessibilityUseSamePageTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityUseSamePage, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto expectedValue = "";
    auto invalidValue = static_cast<Ark_AccessibilitySamePageMode>(-1);

    modifier_->setAccessibilityUseSamePage(node_, invalidValue);
    EXPECT_FALSE(accessibilityProperty->HasAccessibilitySamePage());
    EXPECT_EQ(accessibilityProperty->GetAccessibilitySamePage(), expectedValue);
}

/*
* @tc.name: AccessibilityRoleTestDefaultValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest17lm, AccessibilityRoleTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const std::string defaultValue = "";
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->HasAccessibilityCustomRole(), false);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityCustomRole(), defaultValue);
}

/*
* @tc.name: AccessibilityRoleTestValidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest17lm, AccessibilityRoleTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityRole, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    using TestStep = std::tuple<Ark_AccessibilityRoleType, std::string>;
    static const std::vector<TestStep> testPlan = {
        {Ark_AccessibilityRoleType::ARK_ACCESSIBILITY_ROLE_TYPE_ACTION_SHEET, "ACTION_SHEET"},
        {Ark_AccessibilityRoleType::ARK_ACCESSIBILITY_ROLE_TYPE_ALERT_DIALOG, "ALERT_DIALOG"}};

    EXPECT_FALSE(accessibilityProperty->HasAccessibilityCustomRole());

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityRole(node_, inputValue);
        EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
        EXPECT_EQ(accessibilityProperty->GetAccessibilityCustomRole(), expectedValue);
    }
}

/*
* @tc.name: AccessibilityRoleTestInvalidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest17lm, AccessibilityRoleTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityRole, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto expectedValue = "";
    auto invalidValue = static_cast<Ark_AccessibilityRoleType>(-1);

    EXPECT_FALSE(accessibilityProperty->HasAccessibilityCustomRole());
    modifier_->setAccessibilityRole(node_, invalidValue);
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
    EXPECT_EQ(accessibilityProperty->GetAccessibilityCustomRole(), expectedValue);
}

/*
 * @tc.name: SetOnKeyEventDispatchTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17lm, SetOnKeyEventDispatchTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnKeyEventDispatch, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    struct CheckEvent {
        int32_t resourceId = -1;
        KeyCode code = KeyCode::KEY_UNKNOWN;
    };
    static const int32_t expectedResId = 123;
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_KeyEvent parameter, const Callback_Boolean_Void continuation) {
        auto peer = parameter;
        ASSERT_NE(peer, nullptr);
        auto accessor = GeneratedModifier::GetKeyEventAccessor();
        auto info = peer->GetEventInfo();
        ASSERT_NE(info, nullptr);
        checkEvent = {
            .resourceId = resourceId,
            .code = info->GetKeyCode()
        };
        accessor->destroyPeer(peer);
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_Boolean>(true));
    };

    auto arkCallback = Converter::ArkValue<Callback_KeyEvent_Boolean>(nullptr, checkCallback, expectedResId);
    modifier_->setOnKeyEventDispatch(node_, &arkCallback);

    auto callOnKeyEvent = focusHub->GetOnKeyEventDispatchCallback();
    ASSERT_NE(callOnKeyEvent, nullptr);
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_FN;
    auto eventInfo = KeyEventInfo(keyEvent);
    EXPECT_FALSE(checkEvent.has_value());
    auto result = callOnKeyEvent(eventInfo);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, expectedResId);
    EXPECT_TRUE(result);
    EXPECT_EQ(checkEvent->code, keyEvent.code);
}
} // namespace OHOS::Ace::NG