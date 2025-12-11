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
#include "core/interfaces/native/utility/converter.h"

#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_NAME_NAME = "name";
    const auto ATTRIBUTE_NAME_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_PARAM_NAME = "param";
    const auto ATTRIBUTE_PARAM_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_MODE_MODE_NAME = "mode";
    const auto ATTRIBUTE_MODE_MODE_DEFAULT_VALUE = "NavRouteMode.PUSH_WITH_RECREATE";
} // namespace

class NavRouterModifierTest : public ModifierTestBase<GENERATED_ArkUINavRouterModifier,
    &GENERATED_ArkUINodeModifiers::getNavRouterModifier, GENERATED_ARKUI_NAV_ROUTER> {
    public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

/*
 * @tc.name: setNavRouterOptions0Test
 * @tc.desc: check set name and params in the constructor
 * DISABLED because set RouteInfo for NavRouter not implemented on the ace_engine side
 * @tc.type: FUNC
 */
HWTEST_F(NavRouterModifierTest, DISABLED_setNavRouterOptions0Test, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    modifier_->setNavRouterOptions0(node_);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAME_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NAME_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PARAM_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PARAM_DEFAULT_VALUE);
}

/*
 * @tc.name: setNavRouterOptions1TestDefaultValues
 * @tc.desc: check set name and params in the constructor
 * DISABLED because set RouteInfo for NavRouter not implemented on the ace_engine side
 * @tc.type: FUNC
 */
HWTEST_F(NavRouterModifierTest, DISABLED_setNavRouterOptions1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAME_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NAME_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PARAM_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PARAM_DEFAULT_VALUE);
}

/*
 * @tc.name: setNavRouterOptions1TestValidValues
 * @tc.desc: check set name and params in the constructor
 * DISABLED because set RouteInfo for NavRouter not implemented on the ace_engine side
 * @tc.type: FUNC
 */
HWTEST_F(NavRouterModifierTest, DISABLED_setNavRouterOptions1TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_RouteInfo inputValueOptions;

    // Initial setup
    inputValueOptions.name = Converter::ArkValue<Ark_String>("");
    // Valid values are not defined for attribute 'param' of type 'Ark_CustomObject'

    // Test
    modifier_->setNavRouterOptions1(node_, &inputValueOptions);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAME_NAME);
    EXPECT_EQ(resultStr, "");
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PARAM_NAME);
    EXPECT_EQ(resultStr, "");

    // Verifying attribute's 'name' other values
    inputValueOptions.name = Converter::ArkValue<Ark_String>("abc");
    modifier_->setNavRouterOptions1(node_, &inputValueOptions);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAME_NAME);
    EXPECT_EQ(resultStr, "abc");
}

/*
 * @tc.name: setNavRouterOptions1TestInvalidValues
 * @tc.desc: check set name and params in the constructor
 * DISABLED because set RouteInfo for NavRouter not implemented on the ace_engine side
 * @tc.type: FUNC
 */
HWTEST_F(NavRouterModifierTest, DISABLED_setNavRouterOptions1TestInvalidValues, TestSize.Level1)
{
    FAIL() << "Test is not implemented yet";
}

/*
 * @tc.name: setOnStateChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavRouterModifierTest, DISABLED_setOnStateChangeTest, TestSize.Level1)
{
    FAIL() << "Test is not implemented yet";
}

/*
 * @tc.name: setModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavRouterModifierTest, setModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MODE_MODE_DEFAULT_VALUE);
}

/*
 * @tc.name: setModeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavRouterModifierTest, setModeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    auto inputValueModeMode = ARK_NAV_ROUTE_MODE_PUSH_WITH_RECREATE;

    // Test
    auto optInputValueModeMode = Converter::ArkValue<Opt_NavRouteMode>(inputValueModeMode);
    modifier_->setMode(node_, &optInputValueModeMode);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_MODE_NAME);
    EXPECT_EQ(resultStr, "NavRouteMode.PUSH_WITH_RECREATE");

    // Verifying attribute's other values
    inputValueModeMode = ARK_NAV_ROUTE_MODE_PUSH;
    optInputValueModeMode = Converter::ArkValue<Opt_NavRouteMode>(inputValueModeMode);
    modifier_->setMode(node_, &optInputValueModeMode);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_MODE_NAME);
    EXPECT_EQ(resultStr, "NavRouteMode.PUSH");

    inputValueModeMode = ARK_NAV_ROUTE_MODE_REPLACE;
    optInputValueModeMode = Converter::ArkValue<Opt_NavRouteMode>(inputValueModeMode);
    modifier_->setMode(node_, &optInputValueModeMode);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_MODE_NAME);
    EXPECT_EQ(resultStr, "NavRouteMode.REPLACE");
}

/*
 * @tc.name: setModeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavRouterModifierTest, setModeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    // Initial setup
    auto inputValueModeMode = static_cast<Ark_NavRouteMode>(3);

    // Test
    auto optInputValueModeMode = Converter::ArkValue<Opt_NavRouteMode>(inputValueModeMode);
    modifier_->setMode(node_, &optInputValueModeMode);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_MODE_NAME);
    EXPECT_EQ(resultStr, "NavRouteMode.PUSH_WITH_RECREATE");
}
} // namespace OHOS::Ace::NG
