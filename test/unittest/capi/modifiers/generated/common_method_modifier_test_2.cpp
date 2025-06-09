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

#include "common_method_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::CommonMethod;
/*
 * @tc.name: setAlignRules1TestAlignRulesTopAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesTopAlignValidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_VerticalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(WriteTo(inputValueAlignRules).top).align = value;
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
 * @tc.name: setAlignRules1TestAlignRulesTopAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesTopAlignInvalidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_VerticalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(WriteTo(inputValueAlignRules).top).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultTop = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_TOP_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.top.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumVerticalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesBottomAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBottomAnchorValidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(WriteTo(inputValueAlignRules).bottom).anchor = value;
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
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBottomAlignValidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_VerticalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(WriteTo(inputValueAlignRules).bottom).align = value;
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
 * @tc.name: setAlignRules1TestAlignRulesBottomAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBottomAlignInvalidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_VerticalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(WriteTo(inputValueAlignRules).bottom).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBottom =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.bottom.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumVerticalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesCenterAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesCenterAnchorValidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(WriteTo(inputValueAlignRules).center).anchor = value;
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
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesCenterAlignValidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Ark_VerticalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(WriteTo(inputValueAlignRules).center).align = value;
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
 * @tc.name: setAlignRules1TestAlignRulesCenterAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesCenterAlignInvalidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_VerticalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(WriteTo(inputValueAlignRules).center).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultCenter =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_CENTER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.center.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumVerticalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesBiasHorizontalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBiasHorizontalValidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(WriteTo(inputValueAlignRules).bias).horizontal = value;
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
 * @tc.name: setAlignRules1TestAlignRulesBiasHorizontalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBiasHorizontalInvalidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Opt_Number& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(WriteTo(inputValueAlignRules).bias).horizontal = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.bias.horizontal";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setAlignRules1TestAlignRulesBiasVerticalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBiasVerticalValidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(WriteTo(inputValueAlignRules).bias).vertical = value;
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
 * @tc.name: setAlignRules1TestAlignRulesBiasVerticalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBiasVerticalInvalidValues, TestSize.Level1)
{
    Opt_LocalizedAlignRuleOptions initValueAlignRules;

    // Initial setup
    WriteTo(WriteTo(initValueAlignRules).start).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).start).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).end).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).middle).align =
        std::get<1>(Fixtures::testFixtureEnumHorizontalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).top).align = std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bottom).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).anchor = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).center).align =
        std::get<1>(Fixtures::testFixtureEnumVerticalAlignValidValues[0]);
    WriteTo(WriteTo(initValueAlignRules).bias).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(WriteTo(initValueAlignRules).bias).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Opt_Number& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(WriteTo(inputValueAlignRules).bias).vertical = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.bias.vertical";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRenderFitTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRenderFitTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_FIT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RENDER_FIT_DEFAULT_VALUE) << "Default value for attribute 'renderFit'";
}

/*
 * @tc.name: setRenderFitTestRenderFitValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRenderFitTestRenderFitValidValues, TestSize.Level1)
{
    Opt_RenderFit initValueRenderFit;

    // Initial setup
    initValueRenderFit = ArkValue<Opt_RenderFit>(std::get<1>(Fixtures::testFixtureEnumRenderFitValidValues[0]));

    auto checkValue = [this, &initValueRenderFit](
                          const std::string& input, const std::string& expectedStr, const Opt_RenderFit& value) {
        Opt_RenderFit inputValueRenderFit = initValueRenderFit;

        inputValueRenderFit = value;
        modifier_->setRenderFit(node_, &inputValueRenderFit);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_FIT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRenderFit, attribute: renderFit";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumRenderFitValidValues) {
        checkValue(input, expected, ArkValue<Opt_RenderFit>(value));
    }
}

/*
 * @tc.name: setRenderFitTestRenderFitInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRenderFitTestRenderFitInvalidValues, TestSize.Level1)
{
    Opt_RenderFit initValueRenderFit;

    // Initial setup
    initValueRenderFit = ArkValue<Opt_RenderFit>(std::get<1>(Fixtures::testFixtureEnumRenderFitValidValues[0]));

    auto checkValue = [this, &initValueRenderFit](const std::string& input, const Opt_RenderFit& value) {
        Opt_RenderFit inputValueRenderFit = initValueRenderFit;

        modifier_->setRenderFit(node_, &inputValueRenderFit);
        inputValueRenderFit = value;
        modifier_->setRenderFit(node_, &inputValueRenderFit);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_FIT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RENDER_FIT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRenderFit, attribute: renderFit";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumRenderFitInvalidValues) {
        checkValue(input, ArkValue<Opt_RenderFit>(value));
    }
}

/*
 * @tc.name: setFocusScopePriorityTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFocusScopePriorityTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_ID_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_SCOPE_ID_DEFAULT_VALUE) << "Default value for attribute 'focusScopeId'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_PRIORITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_SCOPE_PRIORITY_DEFAULT_VALUE) <<
        "Default value for attribute 'focusScopePriority'";
}

/*
 * @tc.name: setFocusScopePriorityTestFocusScopeIdValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFocusScopePriorityTestFocusScopeIdValidValues, TestSize.Level1)
{
    Opt_String initValueFocusScopeId;
    Opt_FocusPriority initValueFocusScopePriority;

    // Initial setup
    initValueFocusScopeId = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFocusScopePriority =
        ArkValue<Opt_FocusPriority>(std::get<1>(Fixtures::testFixtureEnumFocusPriorityValidValues[0]));

    auto checkValue = [this, &initValueFocusScopeId, &initValueFocusScopePriority](
                          const std::string& input, const std::string& expectedStr, const Opt_String& value) {
        Opt_String inputValueFocusScopeId = initValueFocusScopeId;
        Opt_FocusPriority inputValueFocusScopePriority = initValueFocusScopePriority;

        inputValueFocusScopeId = value;
        modifier_->setFocusScopePriority(node_, &inputValueFocusScopeId, &inputValueFocusScopePriority);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_ID_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFocusScopePriority, attribute: focusScopeId";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkValue<Opt_String>(value));
    }
}

/*
 * @tc.name: setFocusScopePriorityTestFocusScopeIdInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setFocusScopePriorityTestFocusScopeIdInvalidValues, TestSize.Level1)
{
    Opt_String initValueFocusScopeId;
    Opt_FocusPriority initValueFocusScopePriority;

    // Initial setup
    initValueFocusScopeId = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFocusScopePriority =
        ArkValue<Opt_FocusPriority>(std::get<1>(Fixtures::testFixtureEnumFocusPriorityValidValues[0]));

    auto checkValue = [this, &initValueFocusScopeId, &initValueFocusScopePriority](
                          const std::string& input, const Opt_String& value) {
        Opt_String inputValueFocusScopeId = initValueFocusScopeId;
        Opt_FocusPriority inputValueFocusScopePriority = initValueFocusScopePriority;

        modifier_->setFocusScopePriority(node_, &inputValueFocusScopeId, &inputValueFocusScopePriority);
        inputValueFocusScopeId = value;
        modifier_->setFocusScopePriority(node_, &inputValueFocusScopeId, &inputValueFocusScopePriority);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_ID_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_SCOPE_ID_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFocusScopePriority, attribute: focusScopeId";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_String>());
}

/*
 * @tc.name: setFocusScopePriorityTestFocusScopePriorityValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFocusScopePriorityTestFocusScopePriorityValidValues, TestSize.Level1)
{
    Opt_String initValueFocusScopeId;
    Opt_FocusPriority initValueFocusScopePriority;

    // Initial setup
    initValueFocusScopeId = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFocusScopePriority =
        ArkValue<Opt_FocusPriority>(std::get<1>(Fixtures::testFixtureEnumFocusPriorityValidValues[0]));

    auto checkValue = [this, &initValueFocusScopeId, &initValueFocusScopePriority](
                          const std::string& input, const std::string& expectedStr, const Opt_FocusPriority& value) {
        Opt_String inputValueFocusScopeId = initValueFocusScopeId;
        Opt_FocusPriority inputValueFocusScopePriority = initValueFocusScopePriority;

        inputValueFocusScopePriority = value;
        modifier_->setFocusScopePriority(node_, &inputValueFocusScopeId, &inputValueFocusScopePriority);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_PRIORITY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFocusScopePriority, attribute: focusScopePriority";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFocusPriorityValidValues) {
        checkValue(input, expected, ArkValue<Opt_FocusPriority>(value));
    }
}

/*
 * @tc.name: setFocusScopePriorityTestFocusScopePriorityInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFocusScopePriorityTestFocusScopePriorityInvalidValues, TestSize.Level1)
{
    Opt_String initValueFocusScopeId;
    Opt_FocusPriority initValueFocusScopePriority;

    // Initial setup
    initValueFocusScopeId = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    initValueFocusScopePriority =
        ArkValue<Opt_FocusPriority>(std::get<1>(Fixtures::testFixtureEnumFocusPriorityValidValues[0]));

    auto checkValue = [this, &initValueFocusScopeId, &initValueFocusScopePriority](
                          const std::string& input, const Opt_FocusPriority& value) {
        Opt_String inputValueFocusScopeId = initValueFocusScopeId;
        Opt_FocusPriority inputValueFocusScopePriority = initValueFocusScopePriority;

        modifier_->setFocusScopePriority(node_, &inputValueFocusScopeId, &inputValueFocusScopePriority);
        inputValueFocusScopePriority = value;
        modifier_->setFocusScopePriority(node_, &inputValueFocusScopeId, &inputValueFocusScopePriority);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_PRIORITY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_SCOPE_PRIORITY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFocusScopePriority, attribute: focusScopePriority";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFocusPriorityInvalidValues) {
        checkValue(input, ArkValue<Opt_FocusPriority>(value));
    }
}
} // namespace OHOS::Ace::NG
