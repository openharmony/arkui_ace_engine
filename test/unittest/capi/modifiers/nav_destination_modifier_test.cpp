/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_MODE_NAME = "mode";
    const auto ATTRIBUTE_MODE_DEFAULT_VALUE = "NavDestinationMode::STANDARD";
    const auto ATTRIBUTE_HIDE_TITLE_BAR_NAME = "hideTitleBar";
    const auto ATTRIBUTE_HIDE_TITLE_BAR_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_IS_ANIMATED_TITLE_BAR_NAME = "isAnimatedTitleBar";
    const auto ATTRIBUTE_IS_ANIMATED_TITLE_BAR_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_RECOVERABLE_RECOVERABLE_NAME = "recoverable";
    const auto ATTRIBUTE_RECOVERABLE_RECOVERABLE_DEFAULT_VALUE = "true";
    const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_TYPES_NAME = "ignoreLayoutSafeAreaTypes";
    const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_TYPES_DEFAULT_VALUE = "SAFE_AREA_TYPE_NONE";
    const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_EDGES_NAME = "ignoreLayoutSafeAreaEdges";
    const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_EDGES_DEFAULT_VALUE = "SAFE_AREA_EDGE_NONE";
} // namespace

class NavDestinationModifierTest : public ModifierTestBase<GENERATED_ArkUINavDestinationModifier,
    &GENERATED_ArkUINodeModifiers::getNavDestinationModifier, GENERATED_ARKUI_NAV_DESTINATION> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

/*
 * @tc.name: setModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MODE_DEFAULT_VALUE);
}

// Valid values for attribute 'mode' of method 'mode'
static std::vector<std::tuple<std::string, Ark_NavDestinationMode, std::string>> modeModeValidValues = {
    {"ARK_NAV_DESTINATION_MODE_STANDARD",
     Converter::ArkValue<Ark_NavDestinationMode>(ARK_NAV_DESTINATION_MODE_STANDARD),
     "NavDestinationMode::STANDARD"},
    {"ARK_NAV_DESTINATION_MODE_DIALOG",
     Converter::ArkValue<Ark_NavDestinationMode>(ARK_NAV_DESTINATION_MODE_DIALOG),
     "NavDestinationMode::DIALOG"},
};

/*
 * @tc.name: setModeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setModeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_NavDestinationMode inputValueMode;
    Ark_NavDestinationMode initValueMode;

    // Initial setup
    initValueMode = std::get<1>(modeModeValidValues[0]);

    // Verifying attribute's  values
    inputValueMode = initValueMode;
    for (auto&& value: modeModeValidValues) {
        inputValueMode = std::get<1>(value);
        auto optInputValueMode = Converter::ArkValue<Opt_NavDestinationMode>(inputValueMode);
        modifier_->setMode(node_, &optInputValueMode);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setHideTitleBar0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, DISABLED_setHideTitleBar0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HIDE_TITLE_BAR_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_ANIMATED_TITLE_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IS_ANIMATED_TITLE_BAR_DEFAULT_VALUE);
}

//Valid values for attribute 'hideTitleBar' of method 'hideTitleBar'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> hideTitleBarHideTitleBarValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setHideTitleBar0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, DISABLED_setHideTitleBar0TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueHideTitleBar;
    Ark_Boolean initValueHideTitleBar;
    // Initial setup
    initValueHideTitleBar = std::get<1>(hideTitleBarHideTitleBarValidValues[0]);

    // Verifying attribute's  values
    inputValueHideTitleBar = initValueHideTitleBar;
    for (auto&& value: hideTitleBarHideTitleBarValidValues) {
        inputValueHideTitleBar = std::get<1>(value);
        auto optInputValueHideTitleBar = Converter::ArkValue<Opt_Boolean>(inputValueHideTitleBar);
        modifier_->setHideTitleBar0(node_, &optInputValueHideTitleBar);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

//Valid values for attribute 'animated' of method 'hideTitleBar'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> animatedHideTitleBarValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setHideTitleBar1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, DISABLED_setHideTitleBar1TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueHideTitleBar;
    Ark_Boolean initValueHideTitleBar;
    Ark_Boolean inputValueAnimated;
    Ark_Boolean initValueAnimated;
    // Initial setup
    initValueHideTitleBar = std::get<1>(hideTitleBarHideTitleBarValidValues[0]);
    initValueAnimated = std::get<1>(animatedHideTitleBarValidValues[0]);

    // Verifying attribute's  values
    inputValueHideTitleBar = initValueHideTitleBar;
    inputValueAnimated = initValueAnimated;
    for (auto&& value: hideTitleBarHideTitleBarValidValues) {
        inputValueHideTitleBar = std::get<1>(value);
        for (auto&& animated: animatedHideTitleBarValidValues) {
            inputValueAnimated = std::get<1>(animated);
            auto optInputValueHideTitleBar = Converter::ArkValue<Opt_Boolean>(inputValueHideTitleBar);
            auto optInputValueAnimated = Converter::ArkValue<Opt_Boolean>(inputValueAnimated);
            modifier_->setHideTitleBar1(node_, &optInputValueHideTitleBar, &optInputValueAnimated);
            jsonValue = GetJsonValue(node_);
            resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
            expectedStr = std::get<2>(value);
            EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
            resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_ANIMATED_TITLE_BAR_NAME);
            expectedStr = std::get<2>(animated);
            EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(animated);
        }
    }
}

/*
 * @tc.name: setOnShownTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, DISABLED_setOnShownTest, TestSize.Level1)
{
}

/*
 * @tc.name: setOnHiddenTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, DISABLED_setOnHiddenTest, TestSize.Level1)
{
}

/*
 * @tc.name: setOnWillAppearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, DISABLED_setOnWillAppearTest, TestSize.Level1)
{
}

/*
 * @tc.name: setOnWillDisappearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, DISABLED_setOnWillDisappearTest, TestSize.Level1)
{
}

/*
 * @tc.name: setOnWillShowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, DISABLED_setOnWillShowTest, TestSize.Level1)
{
}

/*
 * @tc.name: setOnWillHideTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, DISABLED_setOnWillHideTest, TestSize.Level1)
{
}

/*
 * @tc.name: setOnBackPressedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setOnBackPressedTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto navGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navGroupNode, nullptr);
    auto eventHub = navGroupNode->GetEventHub<NavDestinationEventHub>();

    static const Ark_Int32 expectedResId = 123;
    auto onBackPressed = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Callback_Boolean_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        Ark_Boolean param = Converter::ArkValue<Ark_Boolean>(true);
        CallbackHelper(cbReturn).InvokeSync(param);
    };
    auto arkFunc = Converter::ArkValue<Callback_Boolean>(nullptr, onBackPressed, expectedResId);
    auto optFunc = Converter::ArkValue<Opt_Callback_Boolean>(arkFunc);
    modifier_->setOnBackPressed(node_, &optFunc);
    auto called = eventHub->FireOnBackPressedEvent();
    EXPECT_TRUE(called);
}

/*
 * @tc.name: setRecoverableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setRecoverableTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RECOVERABLE_RECOVERABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RECOVERABLE_RECOVERABLE_DEFAULT_VALUE);
}

//Valid values for attribute 'recoverableRecoverable' of method 'recoverable'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> recoverableRecoverableRecoverableValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
};

/*
 * @tc.name: setRecoverableTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setRecoverableTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Boolean realInputValue = Converter::ArkValue<Opt_Boolean>(false);
    Opt_Boolean initValueRecoverableRecoverable;
    Opt_Boolean& inputValueRecoverableRecoverable = realInputValue;
    // Initial setup
    initValueRecoverableRecoverable = std::get<1>(recoverableRecoverableRecoverableValidValues[0]);

    // Verifying attribute's  values
    inputValueRecoverableRecoverable = initValueRecoverableRecoverable;
    for (auto&& value: recoverableRecoverableRecoverableValidValues) {
        inputValueRecoverableRecoverable = std::get<1>(value);
        modifier_->setRecoverable(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RECOVERABLE_RECOVERABLE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'recoverableRecoverable' of method 'recoverable'
static std::vector<std::tuple<std::string, Opt_Boolean>> recoverableRecoverableRecoverableInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Boolean>(Ark_Empty())},
};

/*
 * @tc.name: setRecoverableTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setRecoverableTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Boolean realInputValue = Converter::ArkValue<Opt_Boolean>(false);
    Opt_Boolean initValueRecoverableRecoverable;
    Opt_Boolean& inputValueRecoverableRecoverable = realInputValue;
    // Initial setup
    initValueRecoverableRecoverable = std::get<1>(recoverableRecoverableRecoverableValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: recoverableRecoverableRecoverableInvalidValues) {
        inputValueRecoverableRecoverable = initValueRecoverableRecoverable;
        modifier_->setRecoverable(node_, &realInputValue);
        inputValueRecoverableRecoverable = std::get<1>(value);
        modifier_->setRecoverable(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RECOVERABLE_RECOVERABLE_NAME);
        expectedStr = ATTRIBUTE_RECOVERABLE_RECOVERABLE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setIgnoreLayoutSafeAreaTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, DISABLED_setIgnoreLayoutSafeAreaTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_TYPES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_TYPES_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_EDGES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_EDGES_DEFAULT_VALUE);
}

/*
 * @tc.name: setIgnoreLayoutSafeAreaTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, DISABLED_setIgnoreLayoutSafeAreaTestValidValues, TestSize.Level1)
{
    std::string resultStr;
    std::string expectedStr;
    std::unique_ptr<JsonValue> jsonValue;

    Ark_LayoutSafeAreaType typeVal = ARK_LAYOUT_SAFE_AREA_TYPE_SYSTEM;
    Ark_LayoutSafeAreaEdge edgeVal = ARK_LAYOUT_SAFE_AREA_EDGE_TOP;

    Array_LayoutSafeAreaType initValueType = {.array = &typeVal, .length = 1};
    Array_LayoutSafeAreaEdge initValueEdge = {.array = &edgeVal, .length = 1};

    auto realInputValue0 = Converter::ArkValue<Opt_Array_LayoutSafeAreaType>(initValueType);
    auto realInputValue1 = Converter::ArkValue<Opt_Array_LayoutSafeAreaEdge>(initValueEdge);

    modifier_->setIgnoreLayoutSafeArea(node_, &realInputValue0, &realInputValue1);
    jsonValue = GetJsonValue(node_);

    expectedStr = "SAFE_AREA_TYPE_SYSTEM";
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_TYPES_NAME);
    EXPECT_EQ(resultStr, expectedStr);

    expectedStr = "SAFE_AREA_EDGE_TOP";
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_EDGES_NAME);
    EXPECT_EQ(resultStr, expectedStr);
}
} // namespace OHOS::Ace::NG
