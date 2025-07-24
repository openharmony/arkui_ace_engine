/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "web_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Web;
/*
 * @tc.name: setPinchSmoothTestPinchSmoothValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setPinchSmoothTestPinchSmoothValidValues, TestSize.Level1)
{
    Ark_Boolean initValuePinchSmooth;

    // Initial setup
    initValuePinchSmooth = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValuePinchSmooth](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValuePinchSmooth = initValuePinchSmooth;

        inputValuePinchSmooth = value;
        modifier_->setPinchSmooth(node_, inputValuePinchSmooth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PINCH_SMOOTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPinchSmooth, attribute: pinchSmooth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAllowWindowOpenMethodTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setAllowWindowOpenMethodTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_WINDOW_OPEN_METHOD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALLOW_WINDOW_OPEN_METHOD_DEFAULT_VALUE) <<
        "Default value for attribute 'allowWindowOpenMethod'";
}

/*
 * @tc.name: setAllowWindowOpenMethodTestAllowWindowOpenMethodValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setAllowWindowOpenMethodTestAllowWindowOpenMethodValidValues, TestSize.Level1)
{
    Ark_Boolean initValueAllowWindowOpenMethod;

    // Initial setup
    initValueAllowWindowOpenMethod = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueAllowWindowOpenMethod](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueAllowWindowOpenMethod = initValueAllowWindowOpenMethod;

        inputValueAllowWindowOpenMethod = value;
        modifier_->setAllowWindowOpenMethod(node_, inputValueAllowWindowOpenMethod);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_WINDOW_OPEN_METHOD_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAllowWindowOpenMethod, attribute: allowWindowOpenMethod";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setJavaScriptOnDocumentStartTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setJavaScriptOnDocumentStartTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_START_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_START_DEFAULT_VALUE) <<
        "Default value for attribute 'javaScriptOnDocumentStart'";
}

/*
 * @tc.name: setJavaScriptOnDocumentStartTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setJavaScriptOnDocumentStartTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setJavaScriptOnDocumentEndTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setJavaScriptOnDocumentEndTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_END_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_END_DEFAULT_VALUE) <<
        "Default value for attribute 'javaScriptOnDocumentEnd'";
}

/*
 * @tc.name: setJavaScriptOnDocumentEndTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setJavaScriptOnDocumentEndTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setLayoutModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setLayoutModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LAYOUT_MODE_DEFAULT_VALUE) << "Default value for attribute 'layoutMode'";
}

/*
 * @tc.name: setLayoutModeTestLayoutModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setLayoutModeTestLayoutModeValidValues, TestSize.Level1)
{
    Ark_WebLayoutMode initValueLayoutMode;

    // Initial setup
    initValueLayoutMode = std::get<1>(Fixtures::testFixtureEnumWebLayoutModeValidValues[0]);

    auto checkValue = [this, &initValueLayoutMode](
                          const std::string& input, const std::string& expectedStr, const Ark_WebLayoutMode& value) {
        Ark_WebLayoutMode inputValueLayoutMode = initValueLayoutMode;

        inputValueLayoutMode = value;
        modifier_->setLayoutMode(node_, inputValueLayoutMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLayoutMode, attribute: layoutMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumWebLayoutModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setLayoutModeTestLayoutModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setLayoutModeTestLayoutModeInvalidValues, TestSize.Level1)
{
    Ark_WebLayoutMode initValueLayoutMode;

    // Initial setup
    initValueLayoutMode = std::get<1>(Fixtures::testFixtureEnumWebLayoutModeValidValues[0]);

    auto checkValue = [this, &initValueLayoutMode](const std::string& input, const Ark_WebLayoutMode& value) {
        Ark_WebLayoutMode inputValueLayoutMode = initValueLayoutMode;

        modifier_->setLayoutMode(node_, inputValueLayoutMode);
        inputValueLayoutMode = value;
        modifier_->setLayoutMode(node_, inputValueLayoutMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LAYOUT_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLayoutMode, attribute: layoutMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumWebLayoutModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNestedScrollTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultNestedScroll =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE) <<
        "Default value for attribute 'nestedScroll.NestedScrollOptions.scrollForward'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE) <<
        "Default value for attribute 'nestedScroll.NestedScrollOptions.scrollBackward'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_DEFAULT_VALUE) <<
        "Default value for attribute 'nestedScroll.NestedScrollOptionsExt.scrollUp'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_DEFAULT_VALUE) <<
        "Default value for attribute 'nestedScroll.NestedScrollOptionsExt.scrollDown'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'nestedScroll.NestedScrollOptionsExt.scrollRight'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_DEFAULT_VALUE) <<
        "Default value for attribute 'nestedScroll.NestedScrollOptionsExt.scrollLeft'";
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsScrollForwardValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollNestedScrollOptionsScrollForwardValidValues,
    TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const std::string& expectedStr, const Ark_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollForward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptions.scrollForward";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsScrollForwardInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollNestedScrollOptionsScrollForwardInvalidValues,
    TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Ark_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollForward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptions.scrollForward";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsScrollBackwardValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollNestedScrollOptionsScrollBackwardValidValues,
    TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const std::string& expectedStr, const Ark_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollBackward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptions.scrollBackward";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsScrollBackwardInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollNestedScrollOptionsScrollBackwardInvalidValues,
    TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Ark_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollBackward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptions.scrollBackward";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollUpValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollUpValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const std::string& expectedStr, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollUp = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptionsExt.scrollUp";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollUpInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollUpInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollUp = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptionsExt.scrollUp";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollDownValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollDownValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const std::string& expectedStr, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollDown = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptionsExt.scrollDown";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollDownInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollDownInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollDown = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptionsExt.scrollDown";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollRightValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const std::string& expectedStr, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollRight = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptionsExt.scrollRight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    WebModifierTest, setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollRightInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollRight = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptionsExt.scrollRight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollLeftValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const std::string& expectedStr, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollLeft = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptionsExt.scrollLeft";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollNestedScrollOptionsExtScrollLeftInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Opt_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollLeft = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setNestedScroll, attribute: nestedScroll.NestedScrollOptionsExt.scrollLeft";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setEnableNativeEmbedModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableNativeEmbedModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_EMBED_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_NATIVE_EMBED_MODE_DEFAULT_VALUE) <<
        "Default value for attribute 'enableNativeEmbedMode'";
}

/*
 * @tc.name: setEnableNativeEmbedModeTestEnableNativeEmbedModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableNativeEmbedModeTestEnableNativeEmbedModeValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableNativeEmbedMode;

    // Initial setup
    initValueEnableNativeEmbedMode = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableNativeEmbedMode](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueEnableNativeEmbedMode = initValueEnableNativeEmbedMode;

        inputValueEnableNativeEmbedMode = value;
        modifier_->setEnableNativeEmbedMode(node_, inputValueEnableNativeEmbedMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_EMBED_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableNativeEmbedMode, attribute: enableNativeEmbedMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setCopyOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setCopyOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTIONS_DEFAULT_VALUE) << "Default value for attribute 'copyOptions'";
}

/*
 * @tc.name: setCopyOptionsTestCopyOptionsValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setCopyOptionsTestCopyOptionsValidValues, TestSize.Level1)
{
    Ark_CopyOptions initValueCopyOptions;

    // Initial setup
    initValueCopyOptions = std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]);

    auto checkValue = [this, &initValueCopyOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_CopyOptions& value) {
        Ark_CopyOptions inputValueCopyOptions = initValueCopyOptions;

        inputValueCopyOptions = value;
        modifier_->setCopyOptions(node_, inputValueCopyOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCopyOptions, attribute: copyOptions";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCopyOptionsValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setCopyOptionsTestCopyOptionsInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setCopyOptionsTestCopyOptionsInvalidValues, TestSize.Level1)
{
    Ark_CopyOptions initValueCopyOptions;

    // Initial setup
    initValueCopyOptions = std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]);

    auto checkValue = [this, &initValueCopyOptions](const std::string& input, const Ark_CopyOptions& value) {
        Ark_CopyOptions inputValueCopyOptions = initValueCopyOptions;

        modifier_->setCopyOptions(node_, inputValueCopyOptions);
        inputValueCopyOptions = value;
        modifier_->setCopyOptions(node_, inputValueCopyOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTIONS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCopyOptions, attribute: copyOptions";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumCopyOptionsInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setTextAutosizingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setTextAutosizingTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_AUTOSIZING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_AUTOSIZING_DEFAULT_VALUE) << "Default value for attribute 'textAutosizing'";
}

/*
 * @tc.name: setTextAutosizingTestTextAutosizingValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setTextAutosizingTestTextAutosizingValidValues, TestSize.Level1)
{
    Ark_Boolean initValueTextAutosizing;

    // Initial setup
    initValueTextAutosizing = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueTextAutosizing](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueTextAutosizing = initValueTextAutosizing;

        inputValueTextAutosizing = value;
        modifier_->setTextAutosizing(node_, inputValueTextAutosizing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_AUTOSIZING_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextAutosizing, attribute: textAutosizing";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setEnableNativeMediaPlayerTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableNativeMediaPlayerTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultEnableNativeMediaPlayer =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_NAME);
    std::string resultStr;

    resultStr =
        GetAttrValue<std::string>(resultEnableNativeMediaPlayer, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_ENABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_ENABLE_DEFAULT_VALUE) <<
        "Default value for attribute 'enableNativeMediaPlayer.enable'";

    resultStr = GetAttrValue<std::string>(
        resultEnableNativeMediaPlayer, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_SHOULD_OVERLAY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_SHOULD_OVERLAY_DEFAULT_VALUE) <<
        "Default value for attribute 'enableNativeMediaPlayer.shouldOverlay'";
}

/*
 * @tc.name: setEnableNativeMediaPlayerTestEnableNativeMediaPlayerEnableValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableNativeMediaPlayerTestEnableNativeMediaPlayerEnableValidValues, TestSize.Level1)
{
    Ark_NativeMediaPlayerConfig initValueEnableNativeMediaPlayer;

    // Initial setup
    initValueEnableNativeMediaPlayer.enable = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueEnableNativeMediaPlayer.shouldOverlay = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableNativeMediaPlayer](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_NativeMediaPlayerConfig inputValueEnableNativeMediaPlayer = initValueEnableNativeMediaPlayer;

        inputValueEnableNativeMediaPlayer.enable = value;
        modifier_->setEnableNativeMediaPlayer(node_, &inputValueEnableNativeMediaPlayer);
        auto jsonValue = GetJsonValue(node_);
        auto resultEnableNativeMediaPlayer =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultEnableNativeMediaPlayer, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_ENABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setEnableNativeMediaPlayer, attribute: enableNativeMediaPlayer.enable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setEnableNativeMediaPlayerTestEnableNativeMediaPlayerShouldOverlayValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    WebModifierTest, setEnableNativeMediaPlayerTestEnableNativeMediaPlayerShouldOverlayValidValues, TestSize.Level1)
{
    Ark_NativeMediaPlayerConfig initValueEnableNativeMediaPlayer;

    // Initial setup
    initValueEnableNativeMediaPlayer.enable = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueEnableNativeMediaPlayer.shouldOverlay = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableNativeMediaPlayer](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_NativeMediaPlayerConfig inputValueEnableNativeMediaPlayer = initValueEnableNativeMediaPlayer;

        inputValueEnableNativeMediaPlayer.shouldOverlay = value;
        modifier_->setEnableNativeMediaPlayer(node_, &inputValueEnableNativeMediaPlayer);
        auto jsonValue = GetJsonValue(node_);
        auto resultEnableNativeMediaPlayer =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultEnableNativeMediaPlayer, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_SHOULD_OVERLAY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setEnableNativeMediaPlayer, attribute: enableNativeMediaPlayer.shouldOverlay";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setSelectionMenuOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setSelectionMenuOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTION_MENU_OPTIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTION_MENU_OPTIONS_DEFAULT_VALUE) <<
        "Default value for attribute 'selectionMenuOptions'";
}

/*
 * @tc.name: setSelectionMenuOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setSelectionMenuOptionsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setKeyboardAvoidModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setKeyboardAvoidModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_AVOID_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_KEYBOARD_AVOID_MODE_DEFAULT_VALUE) <<
        "Default value for attribute 'keyboardAvoidMode'";
}

/*
 * @tc.name: setKeyboardAvoidModeTestKeyboardAvoidModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setKeyboardAvoidModeTestKeyboardAvoidModeValidValues, TestSize.Level1)
{
    Ark_WebKeyboardAvoidMode initValueKeyboardAvoidMode;

    // Initial setup
    initValueKeyboardAvoidMode = std::get<1>(Fixtures::testFixtureEnumWebKeyboardAvoidModeValidValues[0]);

    auto checkValue = [this, &initValueKeyboardAvoidMode](const std::string& input, const std::string& expectedStr,
                          const Ark_WebKeyboardAvoidMode& value) {
        Ark_WebKeyboardAvoidMode inputValueKeyboardAvoidMode = initValueKeyboardAvoidMode;

        inputValueKeyboardAvoidMode = value;
        modifier_->setKeyboardAvoidMode(node_, inputValueKeyboardAvoidMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_AVOID_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setKeyboardAvoidMode, attribute: keyboardAvoidMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumWebKeyboardAvoidModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setKeyboardAvoidModeTestKeyboardAvoidModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setKeyboardAvoidModeTestKeyboardAvoidModeInvalidValues, TestSize.Level1)
{
    Ark_WebKeyboardAvoidMode initValueKeyboardAvoidMode;

    // Initial setup
    initValueKeyboardAvoidMode = std::get<1>(Fixtures::testFixtureEnumWebKeyboardAvoidModeValidValues[0]);

    auto checkValue = [this, &initValueKeyboardAvoidMode](
                          const std::string& input, const Ark_WebKeyboardAvoidMode& value) {
        Ark_WebKeyboardAvoidMode inputValueKeyboardAvoidMode = initValueKeyboardAvoidMode;

        modifier_->setKeyboardAvoidMode(node_, inputValueKeyboardAvoidMode);
        inputValueKeyboardAvoidMode = value;
        modifier_->setKeyboardAvoidMode(node_, inputValueKeyboardAvoidMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_AVOID_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_KEYBOARD_AVOID_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setKeyboardAvoidMode, attribute: keyboardAvoidMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumWebKeyboardAvoidModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setEnableHapticFeedbackTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableHapticFeedbackTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE) <<
        "Default value for attribute 'enableHapticFeedback'";
}

/*
 * @tc.name: setEnableHapticFeedbackTestEnableHapticFeedbackValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableHapticFeedback;

    // Initial setup
    initValueEnableHapticFeedback = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableHapticFeedback](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueEnableHapticFeedback = initValueEnableHapticFeedback;

        inputValueEnableHapticFeedback = value;
        modifier_->setEnableHapticFeedback(node_, inputValueEnableHapticFeedback);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableHapticFeedback, attribute: enableHapticFeedback";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setOptimizeParserBudgetTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setOptimizeParserBudgetTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTIMIZE_PARSER_BUDGET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTIMIZE_PARSER_BUDGET_DEFAULT_VALUE) <<
        "Default value for attribute 'optimizeParserBudget'";
}

/*
 * @tc.name: setOptimizeParserBudgetTestOptimizeParserBudgetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setOptimizeParserBudgetTestOptimizeParserBudgetValidValues, TestSize.Level1)
{
    Ark_Boolean initValueOptimizeParserBudget;

    // Initial setup
    initValueOptimizeParserBudget = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueOptimizeParserBudget](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueOptimizeParserBudget = initValueOptimizeParserBudget;

        inputValueOptimizeParserBudget = value;
        modifier_->setOptimizeParserBudget(node_, inputValueOptimizeParserBudget);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTIMIZE_PARSER_BUDGET_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOptimizeParserBudget, attribute: optimizeParserBudget";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setEnableFollowSystemFontWeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setEnableFollowSystemFontWeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_FOLLOW_SYSTEM_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_FOLLOW_SYSTEM_FONT_WEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'enableFollowSystemFontWeight'";
}

/*
 * @tc.name: setEnableFollowSystemFontWeightTestEnableFollowSystemFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setEnableFollowSystemFontWeightTestEnableFollowSystemFontWeightValidValues,
    TestSize.Level1)
{
    Ark_Boolean initValueEnableFollowSystemFontWeight;

    // Initial setup
    initValueEnableFollowSystemFontWeight = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableFollowSystemFontWeight](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueEnableFollowSystemFontWeight = initValueEnableFollowSystemFontWeight;

        inputValueEnableFollowSystemFontWeight = value;
        modifier_->setEnableFollowSystemFontWeight(node_, inputValueEnableFollowSystemFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_FOLLOW_SYSTEM_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setEnableFollowSystemFontWeight, attribute: enableFollowSystemFontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setEnableWebAVSessionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setEnableWebAVSessionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_WEB_AVSESSION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_WEB_AVSESSION_DEFAULT_VALUE) <<
        "Default value for attribute 'enableWebAVSession'";
}

/*
 * @tc.name: setEnableWebAVSessionTestEnableWebAVSessionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setEnableWebAVSessionTestEnableWebAVSessionValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableWebAVSession;

    // Initial setup
    initValueEnableWebAVSession = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableWebAVSession](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueEnableWebAVSession = initValueEnableWebAVSession;

        inputValueEnableWebAVSession = value;
        modifier_->setEnableWebAVSession(node_, inputValueEnableWebAVSession);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_WEB_AVSESSION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableWebAVSession, attribute: enableWebAVSession";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setRunJavaScriptOnDocumentStartTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setRunJavaScriptOnDocumentStartTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RUN_JAVA_SCRIPT_ON_DOCUMENT_START_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RUN_JAVA_SCRIPT_ON_DOCUMENT_START_DEFAULT_VALUE) <<
        "Default value for attribute 'runJavaScriptOnDocumentStart'";
}

/*
 * @tc.name: setRunJavaScriptOnDocumentStartTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setRunJavaScriptOnDocumentStartTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setRunJavaScriptOnDocumentEndTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setRunJavaScriptOnDocumentEndTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RUN_JAVA_SCRIPT_ON_DOCUMENT_END_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RUN_JAVA_SCRIPT_ON_DOCUMENT_END_DEFAULT_VALUE) <<
        "Default value for attribute 'runJavaScriptOnDocumentEnd'";
}

/*
 * @tc.name: setRunJavaScriptOnDocumentEndTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setRunJavaScriptOnDocumentEndTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setRunJavaScriptOnHeadEndTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setRunJavaScriptOnHeadEndTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RUN_JAVA_SCRIPT_ON_HEAD_END_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RUN_JAVA_SCRIPT_ON_HEAD_END_DEFAULT_VALUE) <<
        "Default value for attribute 'runJavaScriptOnHeadEnd'";
}

/*
 * @tc.name: setRunJavaScriptOnHeadEndTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setRunJavaScriptOnHeadEndTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setNativeEmbedOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNativeEmbedOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultNativeEmbedOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NATIVE_EMBED_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(
        resultNativeEmbedOptions, ATTRIBUTE_NATIVE_EMBED_OPTIONS_I_SUPPORT_DEFAULT_INTRINSIC_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NATIVE_EMBED_OPTIONS_I_SUPPORT_DEFAULT_INTRINSIC_SIZE_DEFAULT_VALUE) <<
        "Default value for attribute 'nativeEmbedOptions.supportDefaultIntrinsicSize'";
}

/*
 * @tc.name: setNativeEmbedOptionsTestNativeEmbedOptionsSupportDefaultIntrinsicSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNativeEmbedOptionsTestNativeEmbedOptionsSupportDefaultIntrinsicSizeValidValues,
    TestSize.Level1)
{
    Opt_EmbedOptions initValueNativeEmbedOptions;

    // Initial setup
    WriteTo(initValueNativeEmbedOptions).supportDefaultIntrinsicSize =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueNativeEmbedOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_EmbedOptions inputValueNativeEmbedOptions = initValueNativeEmbedOptions;

        WriteTo(inputValueNativeEmbedOptions).supportDefaultIntrinsicSize = value;
        modifier_->setNativeEmbedOptions(node_, &inputValueNativeEmbedOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultNativeEmbedOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NATIVE_EMBED_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultNativeEmbedOptions, ATTRIBUTE_NATIVE_EMBED_OPTIONS_I_SUPPORT_DEFAULT_INTRINSIC_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setNativeEmbedOptions, attribute: nativeEmbedOptions.supportDefaultIntrinsicSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setNativeEmbedOptionsTestNativeEmbedOptionsSupportDefaultIntrinsicSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNativeEmbedOptionsTestNativeEmbedOptionsSupportDefaultIntrinsicSizeInvalidValues,
    TestSize.Level1)
{
    Opt_EmbedOptions initValueNativeEmbedOptions;

    // Initial setup
    WriteTo(initValueNativeEmbedOptions).supportDefaultIntrinsicSize =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueNativeEmbedOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_EmbedOptions inputValueNativeEmbedOptions = initValueNativeEmbedOptions;

        modifier_->setNativeEmbedOptions(node_, &inputValueNativeEmbedOptions);
        WriteTo(inputValueNativeEmbedOptions).supportDefaultIntrinsicSize = value;
        modifier_->setNativeEmbedOptions(node_, &inputValueNativeEmbedOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultNativeEmbedOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NATIVE_EMBED_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultNativeEmbedOptions, ATTRIBUTE_NATIVE_EMBED_OPTIONS_I_SUPPORT_DEFAULT_INTRINSIC_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NATIVE_EMBED_OPTIONS_I_SUPPORT_DEFAULT_INTRINSIC_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setNativeEmbedOptions, attribute: nativeEmbedOptions.supportDefaultIntrinsicSize";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setRegisterNativeEmbedRuleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setRegisterNativeEmbedRuleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultRegisterNativeEmbedRule =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_NAME);
    std::string resultStr;

    resultStr =
        GetAttrValue<std::string>(resultRegisterNativeEmbedRule, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TAG_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TAG_DEFAULT_VALUE) <<
        "Default value for attribute 'registerNativeEmbedRule.tag'";

    resultStr =
        GetAttrValue<std::string>(resultRegisterNativeEmbedRule, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TYPE_DEFAULT_VALUE) <<
        "Default value for attribute 'registerNativeEmbedRule.type'";
}

/*
 * @tc.name: setRegisterNativeEmbedRuleTestRegisterNativeEmbedRuleTagValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setRegisterNativeEmbedRuleTestRegisterNativeEmbedRuleTagValidValues, TestSize.Level1)
{
    Ark_String initValueTag;
    Ark_String initValueType;

    // Initial setup
    initValueTag = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueType = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueTag, &initValueType](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValueTag = initValueTag;
        Ark_String inputValueType = initValueType;

        inputValueTag = value;
        modifier_->setRegisterNativeEmbedRule(node_, &inputValueTag, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultRegisterNativeEmbedRule =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRegisterNativeEmbedRule, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TAG_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setRegisterNativeEmbedRule, attribute: registerNativeEmbedRule.tag";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setRegisterNativeEmbedRuleTestRegisterNativeEmbedRuleTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setRegisterNativeEmbedRuleTestRegisterNativeEmbedRuleTypeValidValues, TestSize.Level1)
{
    Ark_String initValueTag;
    Ark_String initValueType;

    // Initial setup
    initValueTag = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueType = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueTag, &initValueType](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValueTag = initValueTag;
        Ark_String inputValueType = initValueType;

        inputValueType = value;
        modifier_->setRegisterNativeEmbedRule(node_, &inputValueTag, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultRegisterNativeEmbedRule =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRegisterNativeEmbedRule, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setRegisterNativeEmbedRule, attribute: registerNativeEmbedRule.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}
} // namespace OHOS::Ace::NG
