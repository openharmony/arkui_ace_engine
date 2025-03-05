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

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/components/progress/progress_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_COLOR_NAME = "color";
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_TOTAL_NAME = "total";
const auto ATTRIBUTE_TOTAL_DEFAULT_VALUE = "100.000000";
const auto ATTRIBUTE_STYLE_NAME = "style";
const auto ATTRIBUTE_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TYPE_NAME = "type";
const auto ATTRIBUTE_TYPE_DEFAULT_VALUE = "ProgressStyle.Linear";
const auto ATTRIBUTE_COLOR_I_ANGLE_NAME = "angle";
const auto ATTRIBUTE_COLOR_I_ANGLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_COLOR_I_DIRECTION_NAME = "direction";
const auto ATTRIBUTE_COLOR_I_DIRECTION_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_COLOR_I_COLORS_NAME = "colors";
const auto ATTRIBUTE_COLOR_I_COLORS_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_COLOR_I_REPEATING_NAME = "repeating";
const auto ATTRIBUTE_COLOR_I_REPEATING_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_NAME = "privacySensitive";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE = "false";
} // namespace

class ProgressModifierTest : public ModifierTestBase<GENERATED_ArkUIProgressModifier,
                                 &GENERATED_ArkUINodeModifiers::getProgressModifier, GENERATED_ARKUI_PROGRESS> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<ProgressTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setProgressOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setProgressOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) << "Default value for attribute 'options.value'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TOTAL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TOTAL_DEFAULT_VALUE) << "Default value for attribute 'options.total'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_DEFAULT_VALUE) << "Default value for attribute 'options.style'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) << "Default value for attribute 'options.type'";
}

/*
 * @tc.name: setProgressOptionsTestOptionsValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestOptionsValueValidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]));
    initValueOptions.style =
        ArkValue<Opt_ProgressStyle>(std::get<1>(Fixtures::testFixtureEnumProgressStyleValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.value = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatPositiveValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setProgressOptionsTestOptionsTotalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestOptionsTotalValidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]));
    initValueOptions.style =
        ArkValue<Opt_ProgressStyle>(std::get<1>(Fixtures::testFixtureEnumProgressStyleValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.total = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TOTAL_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.total";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatPositiveValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setProgressOptionsTestOptionsTotalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestOptionsTotalInvalidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]));
    initValueOptions.style =
        ArkValue<Opt_ProgressStyle>(std::get<1>(Fixtures::testFixtureEnumProgressStyleValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Number& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.total = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TOTAL_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_TOTAL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.total";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setProgressOptionsTestOptionsStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setProgressOptionsTestOptionsStyleValidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]));
    initValueOptions.style =
        ArkValue<Opt_ProgressStyle>(std::get<1>(Fixtures::testFixtureEnumProgressStyleValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ProgressStyle& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.style = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumProgressStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_ProgressStyle>(value));
    }
}

/*
 * @tc.name: setProgressOptionsTestOptionsStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setProgressOptionsTestOptionsStyleInvalidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]));
    initValueOptions.style =
        ArkValue<Opt_ProgressStyle>(std::get<1>(Fixtures::testFixtureEnumProgressStyleValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_ProgressStyle& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.style = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumProgressStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_ProgressStyle>(value));
    }
}

/*
 * @tc.name: setProgressOptionsTestOptionsTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestOptionsTypeValidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]));
    initValueOptions.style =
        ArkValue<Opt_ProgressStyle>(std::get<1>(Fixtures::testFixtureEnumProgressStyleValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ProgressType& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.type = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureProgressTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ProgressType>(value));
    }
}

/*
 * @tc.name: setProgressOptionsTestOptionsTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestOptionsTypeInvalidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]));
    initValueOptions.style =
        ArkValue<Opt_ProgressStyle>(std::get<1>(Fixtures::testFixtureEnumProgressStyleValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_ProgressType& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.type = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.type";
    };

    for (auto& [input, value] : Fixtures::testFixtureProgressTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ProgressType>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ProgressType>());
}

/*
 * @tc.name: setValueTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setValueTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) << "Default value for attribute 'value'";
}

/*
 * @tc.name: setValueTestValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setValueTestValueValidValues, TestSize.Level1)
{
    Ark_Number initValueValue;

    // Initial setup
    initValueValue = std::get<1>(Fixtures::testFixtureNumberFloatPositiveValidValues[0]);

    auto checkValue = [this, &initValueValue](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueValue = initValueValue;

        inputValueValue = value;
        modifier_->setValue(node_, &inputValueValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setValue, attribute: value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatPositiveValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_COLOR_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultColor, ATTRIBUTE_COLOR_I_ANGLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COLOR_I_ANGLE_DEFAULT_VALUE) <<
        "Default value for attribute 'color.LinearGradient_common.angle'";

    resultStr = GetAttrValue<std::string>(resultColor, ATTRIBUTE_COLOR_I_DIRECTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COLOR_I_DIRECTION_DEFAULT_VALUE) <<
        "Default value for attribute 'color.LinearGradient_common.direction'";

    resultStr = GetAttrValue<std::string>(resultColor, ATTRIBUTE_COLOR_I_COLORS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COLOR_I_COLORS_DEFAULT_VALUE) <<
        "Default value for attribute 'color.LinearGradient_common.colors'";

    resultStr = GetAttrValue<std::string>(resultColor, ATTRIBUTE_COLOR_I_REPEATING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COLOR_I_REPEATING_DEFAULT_VALUE) <<
        "Default value for attribute 'color.LinearGradient_common.repeating'";
}

/*
 * @tc.name: setColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setColorTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setPrivacySensitiveTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setPrivacySensitiveTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE) << "Default value for attribute 'privacySensitive'";
}

/*
 * @tc.name: setPrivacySensitiveTestPrivacySensitiveValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setPrivacySensitiveTestPrivacySensitiveValidValues, TestSize.Level1)
{
    Opt_Boolean initValuePrivacySensitive;

    // Initial setup
    initValuePrivacySensitive = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValuePrivacySensitive](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValuePrivacySensitive = initValuePrivacySensitive;

        inputValuePrivacySensitive = value;
        modifier_->setPrivacySensitive(node_, &inputValuePrivacySensitive);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPrivacySensitive, attribute: privacySensitive";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setPrivacySensitiveTestPrivacySensitiveInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setPrivacySensitiveTestPrivacySensitiveInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValuePrivacySensitive;

    // Initial setup
    initValuePrivacySensitive = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValuePrivacySensitive](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValuePrivacySensitive = initValuePrivacySensitive;

        modifier_->setPrivacySensitive(node_, &inputValuePrivacySensitive);
        inputValuePrivacySensitive = value;
        modifier_->setPrivacySensitive(node_, &inputValuePrivacySensitive);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPrivacySensitive, attribute: privacySensitive";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}
} // namespace OHOS::Ace::NG
