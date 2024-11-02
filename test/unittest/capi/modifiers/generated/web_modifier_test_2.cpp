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

#include "web_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Web;
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
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_START_DEFAULT_VALUE)
        << "Default value for attribute 'javaScriptOnDocumentStart'";
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
    EXPECT_EQ(resultStr, ATTRIBUTE_JAVA_SCRIPT_ON_DOCUMENT_END_DEFAULT_VALUE)
        << "Default value for attribute 'javaScriptOnDocumentEnd'";
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
                          const std::string& input, const Ark_WebLayoutMode& value, const std::string& expectedStr) {
        Ark_WebLayoutMode inputValueLayoutMode = initValueLayoutMode;

        inputValueLayoutMode = value;
        modifier_->setLayoutMode(node_, inputValueLayoutMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setLayoutMode, attribute: layoutMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumWebLayoutModeValidValues) {
        checkValue(input, value, expected);
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
        EXPECT_EQ(resultStr, ATTRIBUTE_LAYOUT_MODE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setLayoutMode, attribute: layoutMode";
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
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollForward'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollBackward'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollUp'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollDown'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollRight'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_DEFAULT_VALUE)
        << "Default value for attribute 'nestedScroll..scrollLeft'";
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollForwardValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollScrollForwardValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Ark_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollForward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollForward";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollForwardInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollScrollForwardInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Ark_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollForward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollForward";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollBackwardValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollScrollBackwardValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Ark_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollBackward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollBackward";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollBackwardInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, DISABLED_setNestedScrollTestNestedScrollScrollBackwardInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Ark_NestedScrollMode& value) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        WriteToUnion<Ark_NestedScrollOptions>(inputValueNestedScroll).scrollBackward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollBackward";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollUpValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollUpValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Opt_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollUp = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollUp";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, ArkValue<Opt_NestedScrollMode>(value), expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollUpInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollUpInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
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
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_UP_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollUp";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollDownValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollDownValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Opt_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollDown = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollDown";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, ArkValue<Opt_NestedScrollMode>(value), expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollDownInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollDownInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
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
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_DOWN_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollDown";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollRightValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Opt_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollRight = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollRight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, ArkValue<Opt_NestedScrollMode>(value), expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollRightInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
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
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_RIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollRight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, ArkValue<Opt_NestedScrollMode>(value));
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollLeftValidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollUp =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollDown =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollRight =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));
    WriteToUnion<Ark_NestedScrollOptionsExt>(initValueNestedScroll).scrollLeft =
        ArkValue<Opt_NestedScrollMode>(std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]));

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const Opt_NestedScrollMode& value, const std::string& expectedStr) {
        Ark_Union_NestedScrollOptions_NestedScrollOptionsExt inputValueNestedScroll = initValueNestedScroll;

        WriteToUnion<Ark_NestedScrollOptionsExt>(inputValueNestedScroll).scrollLeft = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollLeft";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, ArkValue<Opt_NestedScrollMode>(value), expected);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setNestedScrollTestNestedScrollScrollLeftInvalidValues, TestSize.Level1)
{
    Ark_Union_NestedScrollOptions_NestedScrollOptionsExt initValueNestedScroll;

    // Initial setup
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollForward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    WriteToUnion<Ark_NestedScrollOptions>(initValueNestedScroll).scrollBackward =
        std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
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
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_LEFT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll..scrollLeft";
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
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_NATIVE_EMBED_MODE_DEFAULT_VALUE)
        << "Default value for attribute 'enableNativeEmbedMode'";
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
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueEnableNativeEmbedMode = initValueEnableNativeEmbedMode;

        inputValueEnableNativeEmbedMode = value;
        modifier_->setEnableNativeEmbedMode(node_, inputValueEnableNativeEmbedMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_EMBED_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEnableNativeEmbedMode, attribute: enableNativeEmbedMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
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
    EXPECT_EQ(resultStr, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TAG_DEFAULT_VALUE)
        << "Default value for attribute 'registerNativeEmbedRule.tag'";

    resultStr =
        GetAttrValue<std::string>(resultRegisterNativeEmbedRule, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TYPE_DEFAULT_VALUE)
        << "Default value for attribute 'registerNativeEmbedRule.type'";
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
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueTag = initValueTag;
        Ark_String inputValueType = initValueType;

        inputValueTag = value;
        modifier_->setRegisterNativeEmbedRule(node_, &inputValueTag, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultRegisterNativeEmbedRule =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRegisterNativeEmbedRule, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TAG_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setRegisterNativeEmbedRule, attribute: registerNativeEmbedRule.tag";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
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
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueTag = initValueTag;
        Ark_String inputValueType = initValueType;

        inputValueType = value;
        modifier_->setRegisterNativeEmbedRule(node_, &inputValueTag, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultRegisterNativeEmbedRule =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultRegisterNativeEmbedRule, ATTRIBUTE_REGISTER_NATIVE_EMBED_RULE_I_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setRegisterNativeEmbedRule, attribute: registerNativeEmbedRule.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
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
                          const std::string& input, const Ark_CopyOptions& value, const std::string& expectedStr) {
        Ark_CopyOptions inputValueCopyOptions = initValueCopyOptions;

        inputValueCopyOptions = value;
        modifier_->setCopyOptions(node_, inputValueCopyOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTIONS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCopyOptions, attribute: copyOptions";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCopyOptionsValidValues) {
        checkValue(input, value, expected);
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
        EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTIONS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCopyOptions, attribute: copyOptions";
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
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueTextAutosizing = initValueTextAutosizing;

        inputValueTextAutosizing = value;
        modifier_->setTextAutosizing(node_, inputValueTextAutosizing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_AUTOSIZING_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextAutosizing, attribute: textAutosizing";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
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
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_ENABLE_DEFAULT_VALUE)
        << "Default value for attribute 'enableNativeMediaPlayer.enable'";

    resultStr = GetAttrValue<std::string>(
        resultEnableNativeMediaPlayer, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_SHOULD_OVERLAY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_SHOULD_OVERLAY_DEFAULT_VALUE)
        << "Default value for attribute 'enableNativeMediaPlayer.shouldOverlay'";
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
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_NativeMediaPlayerConfig inputValueEnableNativeMediaPlayer = initValueEnableNativeMediaPlayer;

        inputValueEnableNativeMediaPlayer.enable = value;
        modifier_->setEnableNativeMediaPlayer(node_, &inputValueEnableNativeMediaPlayer);
        auto jsonValue = GetJsonValue(node_);
        auto resultEnableNativeMediaPlayer =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultEnableNativeMediaPlayer, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_ENABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setEnableNativeMediaPlayer, attribute: enableNativeMediaPlayer.enable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
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
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_NativeMediaPlayerConfig inputValueEnableNativeMediaPlayer = initValueEnableNativeMediaPlayer;

        inputValueEnableNativeMediaPlayer.shouldOverlay = value;
        modifier_->setEnableNativeMediaPlayer(node_, &inputValueEnableNativeMediaPlayer);
        auto jsonValue = GetJsonValue(node_);
        auto resultEnableNativeMediaPlayer =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultEnableNativeMediaPlayer, ATTRIBUTE_ENABLE_NATIVE_MEDIA_PLAYER_I_SHOULD_OVERLAY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setEnableNativeMediaPlayer, attribute: enableNativeMediaPlayer.shouldOverlay";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setEnableSmoothDragResizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableSmoothDragResizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_SMOOTH_DRAG_RESIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_SMOOTH_DRAG_RESIZE_DEFAULT_VALUE)
        << "Default value for attribute 'enableSmoothDragResize'";
}

/*
 * @tc.name: setEnableSmoothDragResizeTestEnableSmoothDragResizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebModifierTest, setEnableSmoothDragResizeTestEnableSmoothDragResizeValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableSmoothDragResize;

    // Initial setup
    initValueEnableSmoothDragResize = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableSmoothDragResize](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueEnableSmoothDragResize = initValueEnableSmoothDragResize;

        inputValueEnableSmoothDragResize = value;
        modifier_->setEnableSmoothDragResize(node_, inputValueEnableSmoothDragResize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_SMOOTH_DRAG_RESIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEnableSmoothDragResize, attribute: enableSmoothDragResize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
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
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTION_MENU_OPTIONS_DEFAULT_VALUE)
        << "Default value for attribute 'selectionMenuOptions'";
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
    EXPECT_EQ(resultStr, ATTRIBUTE_KEYBOARD_AVOID_MODE_DEFAULT_VALUE)
        << "Default value for attribute 'keyboardAvoidMode'";
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

    auto checkValue = [this, &initValueKeyboardAvoidMode](const std::string& input,
                          const Ark_WebKeyboardAvoidMode& value, const std::string& expectedStr) {
        Ark_WebKeyboardAvoidMode inputValueKeyboardAvoidMode = initValueKeyboardAvoidMode;

        inputValueKeyboardAvoidMode = value;
        modifier_->setKeyboardAvoidMode(node_, inputValueKeyboardAvoidMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_AVOID_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setKeyboardAvoidMode, attribute: keyboardAvoidMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumWebKeyboardAvoidModeValidValues) {
        checkValue(input, value, expected);
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
        EXPECT_EQ(resultStr, ATTRIBUTE_KEYBOARD_AVOID_MODE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setKeyboardAvoidMode, attribute: keyboardAvoidMode";
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
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE)
        << "Default value for attribute 'enableHapticFeedback'";
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
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueEnableHapticFeedback = initValueEnableHapticFeedback;

        inputValueEnableHapticFeedback = value;
        modifier_->setEnableHapticFeedback(node_, inputValueEnableHapticFeedback);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEnableHapticFeedback, attribute: enableHapticFeedback";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}
} // namespace OHOS::Ace::NG
