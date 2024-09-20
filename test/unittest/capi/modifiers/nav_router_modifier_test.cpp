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
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    //const auto ATTRIBUTE_NAME_NAME = "name";
    //const auto ATTRIBUTE_NAME_DEFAULT_VALUE = "!NOT-DEFINED!";
    //const auto ATTRIBUTE_PARAM_NAME = "param";
    //const auto ATTRIBUTE_PARAM_DEFAULT_VALUE = "!NOT-DEFINED!";
    const auto ATTRIBUTE_MODE_MODE_NAME = "modeMode";
    const auto ATTRIBUTE_MODE_MODE_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace

class NavRouterModifierTest : public ModifierTestBase<GENERATED_ArkUINavRouterModifier, &GENERATED_ArkUINodeModifiers::getNavRouterModifier, GENERATED_ARKUI_NAV_ROUTER> {
    public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp(MockPipelineContext::GetCurrent());
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

//     name: Ark_String [false]
//     param: Ark_CustomObject [true]

// /*
//  * @tc.name: setNavRouterOptionsTestDefaultValues
//  * @tc.desc:
//  * @tc.type: FUNC
//  */
// HWTEST_F(NavRouterModifierTest, setNavRouterOptionsTestDefaultValues, TestSize.Level1)
// {
//     std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
//     std::string resultStr;

//     resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAME_NAME);
//     EXPECT_EQ(resultStr, ATTRIBUTE_NAME_DEFAULT_VALUE);

//     resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PARAM_NAME);
//     EXPECT_EQ(resultStr, ATTRIBUTE_PARAM_DEFAULT_VALUE);
// }

// /*
//  * @tc.name: setNavRouterOptionsTestValidValues
//  * @tc.desc:
//  * @tc.type: FUNC
//  */
// HWTEST_F(NavRouterModifierTest, setNavRouterOptionsTestValidValues, TestSize.Level1)
// {
//     std::unique_ptr<JsonValue> jsonValue;
//     std::string resultStr;
//     Ark_RouteInfo inputValueOptions;

//     // Inital setup
//     inputValueOptions.name = Converter::ArkValue<Ark_String>("");
//     // TODO: Valid values are not defined for attribute 'param' of type 'Ark_CustomObject'

//     // Test
//     modifier_->setNavRouterOptions(node_, &inputValueOptions);

//     // Initial verification
//     jsonValue = GetJsonValue(node_);
//     resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAME_NAME);
//     EXPECT_EQ(resultStr, "");
//     resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PARAM_NAME);
//     EXPECT_EQ(resultStr, "!NOT-DEFINED!");

//     // Verifying attribute's 'name' other values
//     inputValueOptions.name = Converter::ArkValue<Ark_String>("abc");
//     modifier_->setNavRouterOptions(node_, &inputValueOptions);
//     jsonValue = GetJsonValue(node_);
//     resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAME_NAME);
//     EXPECT_EQ(resultStr, "abc");

// }

/*
 * @tc.name: setNavRouterOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavRouterModifierTest, setNavRouterOptionsTestInvalidValues, TestSize.Level1)
{
}

/*
 * @tc.name: DISABLED_setOnStateChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavRouterModifierTest, DISABLED_setOnStateChangeTest, TestSize.Level1)
{
    // TODO: Implement callback tests!
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
    enum Ark_NavRouteMode inputValueModeMode;

    // Inital setup
    inputValueModeMode = Converter::ArkValue<Ark_NavRouteMode>(ARK_NAV_ROUTE_MODE_PUSH_WITH_RECREATE);

    // Test
    modifier_->setMode(node_, inputValueModeMode);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_MODE_NAME);
    EXPECT_EQ(resultStr, "PUSH_WITH_RECREATE");

    // Verifying attribute's other values
    inputValueModeMode = Converter::ArkValue<Ark_NavRouteMode>(ARK_NAV_ROUTE_MODE_PUSH);
    modifier_->setMode(node_, inputValueModeMode);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_MODE_NAME);
    EXPECT_EQ(resultStr, "PUSH");

    inputValueModeMode = Converter::ArkValue<Ark_NavRouteMode>(ARK_NAV_ROUTE_MODE_REPLACE);
    modifier_->setMode(node_, inputValueModeMode);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_MODE_NAME);
    EXPECT_EQ(resultStr, "REPLACE");

}

/*
 * @tc.name: setModeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavRouterModifierTest, setModeTestInvalidValues, TestSize.Level1)
{
}
} // namespace OHOS::Ace::NG
