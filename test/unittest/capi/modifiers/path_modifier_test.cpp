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
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_COMMANDS_NAME = "commands";
    const auto ATTRIBUTE_COMMANDS_DEFAULT_VALUE = "";
    const auto PATH_CMD = "M150 0 L300 300 L0 300 Z";

    const auto ATTRIBUTE_WIDTH_NAME = "width";
    const auto ATTRIBUTE_WIDTH_DEFAULT_VALUE = "0.00vp";

    const auto ATTRIBUTE_HEIGHT_NAME = "height";
    const auto ATTRIBUTE_HEIGHT_DEFAULT_VALUE = "0.00vp";
} // namespace

class PathModifierTest : public ModifierTestBase<GENERATED_ArkUIPathModifier,
    &GENERATED_ArkUINodeModifiers::getPathModifier, GENERATED_ARKUI_PATH> {
};

/*
 * @tc.name: setPathOptionsTestSizeDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PathModifierTest, setPathOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COMMANDS_DEFAULT_VALUE);
}

/*
 * @tc.name: setPathOptionsTestSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PathModifierTest, setPathOptionsTestSizeValidValues, TestSize.Level1)
{
    using OneTestStep = std::pair<Opt_Union_Number_String, std::string>;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(1), "1.00vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(0), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(2.45f), "2.45vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("5px"), "5.00px" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("22.35px"), "22.35px" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("7vp"), "7.00vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("1.65vp"), "1.65vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("65fp"), "65.00fp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("4.3fp"), "4.30fp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("11lpx"), "11.00lpx" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("0.5lpx"), "0.50lpx" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("3"), "3.00vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("10.65"), "10.65vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("23%"), "23.00%" },
    };

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Opt_PathOptions realInputValue = Converter::ArkValue<Opt_PathOptions>(Ark_PathOptions{});
    Ark_PathOptions& inputValueOptions = realInputValue.value;

    for (const auto &[arkValue, expected]: testPlan) {
        inputValueOptions.width = arkValue;
        inputValueOptions.height = arkValue;

        modifier_->setPathOptions(node_, &realInputValue);

        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expected);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setPathOptionsTestSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PathModifierTest, setPathOptionsTestSizeInvalidValues, TestSize.Level1)
{
    using OneTestStep = std::pair<Opt_Union_Number_String, std::string>;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(-1), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("invalid value"), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(-3.56f), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-8px"), "0.00px" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-21vp"), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-15.6px"), "0.00px" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-8.6vp"), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-32fp"), "0.00fp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-22lpx"), "0.00lpx" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-9.99fp"), "0.00fp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-1.23lpx"), "0.00lpx" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-6"), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(INT_MIN), "0.00vp" },
        { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-16.2"), "0.00vp" },
    };

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Opt_PathOptions realInputValue = Converter::ArkValue<Opt_PathOptions>(Ark_PathOptions{});
    Ark_PathOptions& inputValueOptions = realInputValue.value;

    for (auto &[arkValue, expected]: testPlan) {
        inputValueOptions.width = arkValue;
        inputValueOptions.height = arkValue;

        modifier_->setPathOptions(node_, &realInputValue);

        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expected);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setCommandsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PathModifierTest, setPathOptionsTestCmdValid, TestSize.Level1)
{
    std::string resultStr;
    Opt_PathOptions realInputValue = Converter::ArkValue<Opt_PathOptions>(Ark_PathOptions{});
    Ark_PathOptions& inputValueOptions = realInputValue.value;

    // Initial setup/verification
    inputValueOptions.commands = Converter::ArkValue<Opt_String>(PATH_CMD);
    modifier_->setPathOptions(node_, &realInputValue);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, PATH_CMD);

    // Verifying attribute's other values
    inputValueOptions.commands =  Converter::ArkValue<Opt_String>("abc");
    modifier_->setPathOptions(node_, &realInputValue);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, "abc");
}

/*
 * @tc.name: setCommandsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PathModifierTest, setPathOptionsTestCmdInvalid, TestSize.Level1)
{
    std::string resultStr;
    Opt_PathOptions realInputValue = Converter::ArkValue<Opt_PathOptions>(Ark_PathOptions{});
    Ark_PathOptions& inputValueOptions = realInputValue.value;

    // Verifying attribute's valid values
    inputValueOptions.commands = Converter::ArkValue<Opt_String>(PATH_CMD);
    modifier_->setPathOptions(node_, &realInputValue);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, PATH_CMD);

    // Verifying attribute's undefined value
    inputValueOptions.commands = Converter::ArkValue<Opt_String>();
    modifier_->setPathOptions(node_, &realInputValue);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, PATH_CMD); // nothing changes due to nothing optional value

    // Verifying attribute's valid values
    inputValueOptions.commands = Converter::ArkValue<Opt_String>(PATH_CMD);
    modifier_->setPathOptions(node_, &realInputValue);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, PATH_CMD);

    // Verifying attribute's empty values
    inputValueOptions.commands = Converter::ArkValue<Opt_String>("");
    modifier_->setPathOptions(node_, &realInputValue);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COMMANDS_DEFAULT_VALUE); // reset value
}

/*
 * @tc.name: setCommandsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PathModifierTest, setCommandsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COMMANDS_DEFAULT_VALUE);
}

/*
 * @tc.name: setCommandsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PathModifierTest, setCommandsTestValidValues, TestSize.Level1)
{
    Opt_String inputValueCommands;
    std::string resultStr;

    // Initial setup/verification
    inputValueCommands = Converter::ArkValue<Opt_String>(PATH_CMD);
    modifier_->setCommands(node_, &inputValueCommands);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, PATH_CMD);

    // Verifying attribute's other values
    inputValueCommands = Converter::ArkValue<Opt_String>("abc");
    modifier_->setCommands(node_, &inputValueCommands);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, "abc");
}

/*
 * @tc.name: setCommandsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PathModifierTest, setCommandsTestInvalidValues, TestSize.Level1)
{
    Opt_String inputValueCommands;
    std::string resultStr;

    // Verifying attribute's valid values
    inputValueCommands = Converter::ArkValue<Opt_String>(PATH_CMD);
    modifier_->setCommands(node_, &inputValueCommands);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, PATH_CMD);

    // Verifying attribute's nullptr value
    modifier_->setCommands(node_, nullptr);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COMMANDS_DEFAULT_VALUE); // reset value

    // Verifying attribute's valid values
    inputValueCommands = Converter::ArkValue<Opt_String>(PATH_CMD);
    modifier_->setCommands(node_, &inputValueCommands);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, PATH_CMD);

    // Verifying attribute's empty values
    inputValueCommands = Converter::ArkValue<Opt_String>("");
    modifier_->setCommands(node_, &inputValueCommands);
    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_COMMANDS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COMMANDS_DEFAULT_VALUE); // reset value
}
} // namespace OHOS::Ace::NG
