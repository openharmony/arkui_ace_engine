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
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_OPTIONS_NAME = "options";
    const auto ATTRIBUTE_OPTIONS_DEFAULT_VALUE = "!NOT-DEFINED!";
    const auto ATTRIBUTE_ACTIVE_NAME = "active";
    const auto ATTRIBUTE_ACTIVE_DEFAULT_VALUE = "!NOT-DEFINED!";
    const auto ATTRIBUTE_TYPE_NAME = "type";
    const auto ATTRIBUTE_TYPE_DEFAULT_VALUE = "!NOT-DEFINED!";
    const auto ATTRIBUTE_TARGET_NAME = "target";
    const auto ATTRIBUTE_TARGET_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace

class NavigatorModifierTest : public ModifierTestBase<GENERATED_ArkUINavigatorModifier,
    &GENERATED_ArkUINodeModifiers::getNavigatorModifier, GENERATED_ARKUI_NAVIGATOR> {
};

/*
 * @tc.name: setNavigatorOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorModifierTest, setNavigatorOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTIONS_DEFAULT_VALUE);
}

/*
 * @tc.name: setNavigatorOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorModifierTest, setNavigatorOptionsTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    // Opt_Type_NavigatorInterface_setNavigatorOptions_Arg0 realInputValue = {.tag = ARK_TAG_OBJECT, .value = {}};
    // Type_NavigatorInterface_setNavigatorOptions_Arg0& inputValueOptions = realInputValue.value;

    Type_NavigatorInterface_setNavigatorOptions_Arg0 inputValueOptions = {};
    auto realInputValue = Converter::ArkValue<Opt_Type_NavigatorInterface_setNavigatorOptions_Arg0>(inputValueOptions);

    // Inital setup
    // TODO: Valid values are not defined for attribute 'options' of type 'Opt_Type_NavigatorInterface_setNavigatorOptions_Arg0'

    // Test
    modifier_->setNavigatorOptions0(node_, &realInputValue);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTIONS_NAME);
    EXPECT_EQ(resultStr, "!NOT-DEFINED!");
}

/*
 * @tc.name: setNavigatorOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorModifierTest, setNavigatorOptionsTestInvalidValues, TestSize.Level1)
{
}

/*
 * @tc.name: setActiveTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorModifierTest, setActiveTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ACTIVE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ACTIVE_DEFAULT_VALUE);
}

/*
 * @tc.name: setActiveTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorModifierTest, setActiveTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_Boolean inputValueActive;

    // Inital setup
    inputValueActive = Converter::ArkValue<Ark_Boolean>(true);

    // Test
    modifier_->setActive(node_, inputValueActive);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ACTIVE_NAME);
    EXPECT_EQ(resultStr, "true");

    // Verifying attribute's other values
    inputValueActive = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setActive(node_, inputValueActive);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ACTIVE_NAME);
    EXPECT_EQ(resultStr, "false");
}

/*
 * @tc.name: setTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorModifierTest, setTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE);
}

/*
 * @tc.name: setTypeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorModifierTest, setTypeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_NavigationType inputValueType;

    // Inital setup
    inputValueType = ARK_NAVIGATION_TYPE_PUSH;

    // Test
    modifier_->setType(node_, inputValueType);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, "Push");

    // Verifying attribute's other values
    inputValueType = ARK_NAVIGATION_TYPE_BACK;
    modifier_->setType(node_, inputValueType);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, "Back");

    inputValueType = ARK_NAVIGATION_TYPE_REPLACE;
    modifier_->setType(node_, inputValueType);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, "Replace");

}

/*
 * @tc.name: setTypeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorModifierTest, setTypeTestInvalidValues, TestSize.Level1)
{
}

/*
 * @tc.name: setTargetTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorModifierTest, setTargetTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TARGET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TARGET_DEFAULT_VALUE);
}

/*
 * @tc.name: setTargetTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorModifierTest, setTargetTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_String inputValueTarget;

    // Inital setup
    inputValueTarget = Converter::ArkValue<Ark_String>("");

    // Test
    modifier_->setTarget(node_, &inputValueTarget);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TARGET_NAME);
    EXPECT_EQ(resultStr, "");

    // Verifying attribute's other values
    inputValueTarget = Converter::ArkValue<Ark_String>("abc");
    modifier_->setTarget(node_, &inputValueTarget);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TARGET_NAME);
    EXPECT_EQ(resultStr, "abc");
}

/*
 * @tc.name: DISABLED_setParamsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigatorModifierTest, DISABLED_setParamsTest, TestSize.Level1)
{
    // TODO: CustomObjects is not implemented yet!
}
} // namespace OHOS::Ace::NG
