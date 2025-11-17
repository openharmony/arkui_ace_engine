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

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_ALIGN_RULES_NAME = "alignRules";
const auto ATTRIBUTE_ALIGN_RULES_I_LEFT_NAME = "left";
const auto ATTRIBUTE_ALIGN_RULES_I_RIGHT_NAME = "right";
const auto ATTRIBUTE_ALIGN_RULES_I_MIDDLE_NAME = "middle";
const auto ATTRIBUTE_ALIGN_RULES_I_TOP_NAME = "top";
const auto ATTRIBUTE_ALIGN_RULES_I_BOTTOM_NAME = "bottom";
const auto ATTRIBUTE_ALIGN_RULES_I_CENTER_NAME = "center";
const auto ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME = "bias";
const auto ATTRIBUTE_ALIGN_RULES_I_START_NAME = "start";
const auto ATTRIBUTE_ALIGN_RULES_I_END_NAME = "end";
const auto ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ANCHOR_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ALIGN_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ANCHOR_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ALIGN_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_NAME = "horizontal";
const auto ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_DEFAULT_VALUE = "0.5";
const auto ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_NAME = "vertical";
const auto ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_DEFAULT_VALUE = "0.5";
const auto ATTRIBUTE_ALIGN_RULES_I_START_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_START_I_ANCHOR_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_START_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_START_I_ALIGN_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_END_I_ANCHOR_NAME = "anchor";
const auto ATTRIBUTE_ALIGN_RULES_I_END_I_ANCHOR_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALIGN_RULES_I_END_I_ALIGN_NAME = "align";
const auto ATTRIBUTE_ALIGN_RULES_I_END_I_ALIGN_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ID_NAME = "id";
const auto ATTRIBUTE_ID_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ENABLED_NAME = "enabled";
const auto ATTRIBUTE_ENABLED_DEFAULT_VALUE = "true";
} // namespace

class SecurityComponentMethodModifierTest
    : public ModifierTestBase<GENERATED_ArkUISecurityComponentMethodModifier,
          &GENERATED_ArkUINodeModifiers::getSecurityComponentMethodModifier, GENERATED_ARKUI_SECURITY_COMPONENT_METHOD>,
      public testing::WithParamInterface<int> {
public:
    void* CreateNodeImpl() override
    {
        typedef void* (*ConstructFunc)(Ark_Int32, Ark_Int32);
        const ConstructFunc constructors[] = {
            nodeModifiers_->getSaveButtonModifier()->construct,
        };
        if (GetParam() < std::size(constructors)) {
            return constructors[GetParam()](GetId(), 0);
        }
        return nullptr;
    }

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

INSTANTIATE_TEST_SUITE_P(Tests, SecurityComponentMethodModifierTest, testing::Range(0, 1));

/*
 * @tc.name: setAlignRules0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultAlignRules =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
    std::unique_ptr<JsonValue> resultLeft =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_LEFT_NAME);
    std::unique_ptr<JsonValue> resultRight =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_RIGHT_NAME);
    std::unique_ptr<JsonValue> resultMiddle =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_NAME);
    std::unique_ptr<JsonValue> resultTop =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_TOP_NAME);
    std::unique_ptr<JsonValue> resultBottom =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_NAME);
    std::unique_ptr<JsonValue> resultCenter =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_CENTER_NAME);
    std::unique_ptr<JsonValue> resultBias =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultLeft, ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.left.anchor'";

    resultStr = GetAttrValue<std::string>(resultLeft, ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.left.align'";

    resultStr = GetAttrValue<std::string>(resultRight, ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.right.anchor'";

    resultStr = GetAttrValue<std::string>(resultRight, ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.right.align'";

    resultStr = GetAttrValue<std::string>(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.middle.anchor'";

    resultStr = GetAttrValue<std::string>(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.middle.align'";

    resultStr = GetAttrValue<std::string>(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.top.anchor'";

    resultStr = GetAttrValue<std::string>(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.top.align'";

    resultStr = GetAttrValue<std::string>(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.bottom.anchor'";

    resultStr = GetAttrValue<std::string>(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.bottom.align'";

    resultStr = GetAttrValue<std::string>(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.center.anchor'";

    resultStr = GetAttrValue<std::string>(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.center.align'";

    resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.bias.horizontal'";

    resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.bias.vertical'";
}

/*
 * @tc.name: setAlignRules0TestAlignRulesLeftAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesLeftAnchorValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.left).anchor = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultLeft = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_LEFT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLeft, ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.left.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesLeftAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesLeftAlignValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_HorizontalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.left).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultLeft = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_LEFT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLeft, ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.left.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumHorizontalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesRightAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesRightAnchorValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.right).anchor = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultRight =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_RIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRight, ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.right.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesRightAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesRightAlignValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_HorizontalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.right).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultRight =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_RIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRight, ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.right.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumHorizontalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesMiddleAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesMiddleAnchorValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.middle).anchor = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultMiddle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.middle.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesMiddleAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesMiddleAlignValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_HorizontalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.middle).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultMiddle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.middle.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumHorizontalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesTopAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesTopAnchorValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.top).anchor = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultTop = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_TOP_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.top.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesTopAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesTopAlignValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_VerticalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.top).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultTop = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_TOP_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.top.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumVerticalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesBottomAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesBottomAnchorValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.bottom).anchor = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBottom =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.bottom.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesBottomAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesBottomAlignValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_VerticalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.bottom).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBottom =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.bottom.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumVerticalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesCenterAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesCenterAnchorValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.center).anchor = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultCenter =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_CENTER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.center.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesCenterAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesCenterAlignValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_VerticalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.center).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultCenter =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_CENTER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.center.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumVerticalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesBiasHorizontalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesBiasHorizontalValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.bias).horizontal = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.bias.horizontal";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesBiasVerticalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules0TestAlignRulesBiasVerticalValidValues, TestSize.Level1)
{
    Ark_AlignRuleOption initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.left).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.left).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.right).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.right).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.bias).vertical = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.bias.vertical";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setAlignRules1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultAlignRules =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
    std::unique_ptr<JsonValue> resultStart =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_START_NAME);
    std::unique_ptr<JsonValue> resultEnd =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_END_NAME);
    std::unique_ptr<JsonValue> resultMiddle =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_NAME);
    std::unique_ptr<JsonValue> resultTop =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_TOP_NAME);
    std::unique_ptr<JsonValue> resultBottom =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_NAME);
    std::unique_ptr<JsonValue> resultCenter =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_CENTER_NAME);
    std::unique_ptr<JsonValue> resultBias =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultStart, ATTRIBUTE_ALIGN_RULES_I_START_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_START_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.start.anchor'";

    resultStr = GetAttrValue<std::string>(resultStart, ATTRIBUTE_ALIGN_RULES_I_START_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_START_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.start.align'";

    resultStr = GetAttrValue<std::string>(resultEnd, ATTRIBUTE_ALIGN_RULES_I_END_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_END_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.end.anchor'";

    resultStr = GetAttrValue<std::string>(resultEnd, ATTRIBUTE_ALIGN_RULES_I_END_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_END_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.end.align'";

    resultStr = GetAttrValue<std::string>(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.middle.anchor'";

    resultStr = GetAttrValue<std::string>(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.middle.align'";

    resultStr = GetAttrValue<std::string>(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.top.anchor'";

    resultStr = GetAttrValue<std::string>(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.top.align'";

    resultStr = GetAttrValue<std::string>(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.bottom.anchor'";

    resultStr = GetAttrValue<std::string>(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.bottom.align'";

    resultStr = GetAttrValue<std::string>(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.center.anchor'";

    resultStr = GetAttrValue<std::string>(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.center.align'";

    resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.bias.horizontal'";

    resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_DEFAULT_VALUE) <<
        "Default value for attribute 'alignRules.bias.vertical'";
}

/*
 * @tc.name: setAlignRules1TestAlignRulesStartAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesStartAnchorValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.start).anchor = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultStart =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_START_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStart, ATTRIBUTE_ALIGN_RULES_I_START_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.start.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesStartAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesStartAlignValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_HorizontalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.start).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultStart =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_START_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStart, ATTRIBUTE_ALIGN_RULES_I_START_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.start.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumHorizontalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesEndAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesEndAnchorValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.end).anchor = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultEnd = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_END_NAME);
        auto resultStr = GetAttrValue<std::string>(resultEnd, ATTRIBUTE_ALIGN_RULES_I_END_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.end.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesEndAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesEndAlignValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_HorizontalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.end).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultEnd = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_END_NAME);
        auto resultStr = GetAttrValue<std::string>(resultEnd, ATTRIBUTE_ALIGN_RULES_I_END_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.end.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumHorizontalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesMiddleAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesMiddleAnchorValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.middle).anchor = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultMiddle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.middle.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesMiddleAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesMiddleAlignValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_HorizontalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.middle).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultMiddle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.middle.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumHorizontalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesTopAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesTopAnchorValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.top).anchor = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultTop = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_TOP_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.top.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesTopAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesTopAlignValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_VerticalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.top).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultTop = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_TOP_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.top.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumVerticalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesBottomAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesBottomAnchorValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.bottom).anchor = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBottom =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.bottom.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesBottomAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesBottomAlignValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_VerticalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.bottom).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBottom =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.bottom.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumVerticalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesCenterAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesCenterAnchorValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.center).anchor = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultCenter =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_CENTER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.center.anchor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesCenterAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesCenterAlignValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_VerticalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.center).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultCenter =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_CENTER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.center.align";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumVerticalAlignValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesBiasHorizontalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesBiasHorizontalValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.bias).horizontal = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.bias.horizontal";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesBiasVerticalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setAlignRules1TestAlignRulesBiasVerticalValidValues, TestSize.Level1)
{
    Ark_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(initValueAlignRules.start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.start).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.end).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.middle).align = std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(initValueAlignRules.top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.bottom).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(initValueAlignRules.center).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(initValueAlignRules.bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueAlignRules.bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(inputValueAlignRules.bias).vertical = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.bias.vertical";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setIdTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setIdTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ID_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ID_DEFAULT_VALUE) << "Default value for attribute 'id'";
}

/*
 * @tc.name: setIdTestIdValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setIdTestIdValidValues, TestSize.Level1)
{
    Ark_String initValueId;

    // Initial setup
    initValueId = std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]);

    auto checkValue = [this, &initValueId](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValueId = initValueId;

        inputValueId = value;
        modifier_->setId(node_, &inputValueId);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ID_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setId, attribute: id";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringNoEmptyValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setEnabledTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setEnabledTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLED_DEFAULT_VALUE) << "Default value for attribute 'enabled'";
}

/*
 * @tc.name: setEnabledTestEnabledValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(SecurityComponentMethodModifierTest, setEnabledTestEnabledValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnabled;

    // Initial setup
    initValueEnabled = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnabled](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueEnabled = initValueEnabled;

        inputValueEnabled = value;
        modifier_->setEnabled(node_, inputValueEnabled);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLED_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setEnabled, attribute: enabled";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}
} // namespace OHOS::Ace::NG
