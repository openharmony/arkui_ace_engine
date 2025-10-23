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
 * @tc.name: setMarkAnchorTestMarkAnchorPositionYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setMarkAnchorTestMarkAnchorPositionYInvalidValues, TestSize.Level1)
{
    Opt_Union_Position_LocalizedPosition initValueMarkAnchor;

    // Initial setup
    WriteToUnion<Ark_Position>(WriteTo(initValueMarkAnchor)).x =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteToUnion<Ark_Position>(WriteTo(initValueMarkAnchor)).y =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueMarkAnchor](const std::string& input, const Opt_Length& value) {
        Opt_Union_Position_LocalizedPosition inputValueMarkAnchor = initValueMarkAnchor;

        modifier_->setMarkAnchor(node_, &inputValueMarkAnchor);
        WriteToUnion<Ark_Position>(WriteTo(inputValueMarkAnchor)).y = value;
        modifier_->setMarkAnchor(node_, &inputValueMarkAnchor);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarkAnchor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_I_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MARK_ANCHOR_I_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMarkAnchor, attribute: markAnchor.Position.y";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setOffsetTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setOffsetTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setEnabledTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setEnabledTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

void valueCheckResult(std::unique_ptr<JsonValue>& resultStart, std::unique_ptr<JsonValue>& resultEnd,
                      std::unique_ptr<JsonValue>& resultMiddle, std::unique_ptr<JsonValue>& resultTop,
                      std::unique_ptr<JsonValue>& resultBottom, std::unique_ptr<JsonValue>& resultCenter,
                      std::unique_ptr<JsonValue> resultBias)
{
    std::string resultStr;
    auto valueCheck = [&resultStr](std::unique_ptr<JsonValue>& jsonValue, const std::string& attrName,
        const std::string& expectedStr, const std::string& errMsg,) {
        resultStr = GetAttrValue<std::string>(jsonValue, attrName);
        EXPECT_EQ(resultStr, expectedStr) << errMsg;
    };
    valueCheck(resultStart, ATTRIBUTE_ALIGN_RULES_I_START_I_ANCHOR_NAME,
        ATTRIBUTE_ALIGN_RULES_I_START_I_ANCHOR_DEFAULT_VALUE, "Default value for attribute 'alignRules.start.anchor'");
    valueCheck(resultStart, ATTRIBUTE_ALIGN_RULES_I_START_I_ALIGN_NAME,
        ATTRIBUTE_ALIGN_RULES_I_START_I_ALIGN_DEFAULT_VALUE, "Default value for attribute 'alignRules.start.align'");
    valueCheck(resultEnd, ATTRIBUTE_ALIGN_RULES_I_END_I_ANCHOR_NAME,
        ATTRIBUTE_ALIGN_RULES_I_END_I_ANCHOR_DEFAULT_VALUE, "Default value for attribute 'alignRules.end.anchor'");
    valueCheck(resultEnd, ATTRIBUTE_ALIGN_RULES_I_END_I_ALIGN_NAME,
        ATTRIBUTE_ALIGN_RULES_I_END_I_ALIGN_DEFAULT_VALUE, "Default value for attribute 'alignRules.end.align'");
    valueCheck(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_NAME,
        ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ANCHOR_DEFAULT_VALUE,
        "Default value for attribute 'alignRules.middle.anchor'");
    valueCheck(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_NAME,
        ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_DEFAULT_VALUE, "Default value for attribute 'alignRules.middle.align'");
    valueCheck(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_NAME,
        ATTRIBUTE_ALIGN_RULES_I_TOP_I_ANCHOR_DEFAULT_VALUE, "Default value for attribute 'alignRules.top.anchor'");
    valueCheck(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_NAME,
        ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_DEFAULT_VALUE, "Default value for attribute 'alignRules.top.align'");
    valueCheck(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_NAME,
        ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ANCHOR_DEFAULT_VALUE,
        "Default value for attribute 'alignRules.bottom.anchor'");
    valueCheck(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_NAME,
        ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_DEFAULT_VALUE, "Default value for attribute 'alignRules.bottom.align'");
    valueCheck(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_NAME,
        ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ANCHOR_DEFAULT_VALUE,
        "Default value for attribute 'alignRules.center.anchor'");
    valueCheck(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_NAME,
        ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_DEFAULT_VALUE, "Default value for attribute 'alignRules.center.align'");
    valueCheck(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_NAME,
        ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_DEFAULT_VALUE,
        "Default value for attribute 'alignRules.bias.horizontal'");
    valueCheck(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_NAME,
        ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_DEFAULT_VALUE,
        "Default value for attribute 'alignRules.bias.vertical'");
}

/*
 * @tc.name: setAlignRules1TestDefaultValues
 * @tc.desc: Test of setAlignRules1 modifier
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestDefaultValues, TestSize.Level1)
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
    valueCheckResult(resultStart, resultEnd, resultMiddle, resultTop, resultBottom, resultCenter, resultBias);
}

/*
 * @tc.name: setAlignRules1TestAlignRulesStartAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAlignRules1TestAlignRulesStartAnchorValidValues, TestSize.Level1)
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

        WriteTo(WriteTo(inputValueAlignRules).start).anchor = value;
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
HWTEST_P(CommonMethodModifierTest, DISABLED_setAlignRules1TestAlignRulesStartAlignValidValues, TestSize.Level1)
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
                          const std::string& input, const std::string& expectedStr, const Ark_HorizontalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(WriteTo(inputValueAlignRules).start).align = value;
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
 * @tc.name: setAlignRules1TestAlignRulesStartAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesStartAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_HorizontalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(WriteTo(inputValueAlignRules).start).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultStart =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_START_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStart, ATTRIBUTE_ALIGN_RULES_I_START_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_START_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.start.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumHorizontalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesEndAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAlignRules1TestAlignRulesEndAnchorValidValues, TestSize.Level1)
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

        WriteTo(WriteTo(inputValueAlignRules).end).anchor = value;
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
HWTEST_P(CommonMethodModifierTest, DISABLED_setAlignRules1TestAlignRulesEndAlignValidValues, TestSize.Level1)
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
                          const std::string& input, const std::string& expectedStr, const Ark_HorizontalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(WriteTo(inputValueAlignRules).end).align = value;
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
 * @tc.name: setAlignRules1TestAlignRulesEndAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesEndAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_HorizontalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(WriteTo(inputValueAlignRules).end).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultEnd = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_END_NAME);
        auto resultStr = GetAttrValue<std::string>(resultEnd, ATTRIBUTE_ALIGN_RULES_I_END_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_END_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.end.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumHorizontalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesMiddleAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesMiddleAnchorValidValues, TestSize.Level1)
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

        WriteTo(WriteTo(inputValueAlignRules).middle).anchor = value;
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
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesMiddleAlignValidValues, TestSize.Level1)
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
                          const std::string& input, const std::string& expectedStr, const Ark_HorizontalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        WriteTo(WriteTo(inputValueAlignRules).middle).align = value;
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
 * @tc.name: setAlignRules1TestAlignRulesMiddleAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesMiddleAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_HorizontalAlign& value) {
        Opt_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(WriteTo(inputValueAlignRules).middle).align = value;
        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultMiddle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules1, attribute: alignRules.middle.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumHorizontalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules1TestAlignRulesTopAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesTopAnchorValidValues, TestSize.Level1)
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

        WriteTo(WriteTo(inputValueAlignRules).top).anchor = value;
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
 * @tc.name: setAspectRatioTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAspectRatioTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setClickEffectTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setClickEffectTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAllowDropTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAllowDropTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setDraggableTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setDraggableTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setDragPreview0TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setDragPreview0TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setLinearGradientTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setLinearGradientTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setSweepGradientTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setSweepGradientTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setRadialGradientTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setRadialGradientTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setMotionPathTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setMotionPathTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setShadowTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setShadowTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setClipTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setClipTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setClipShapeTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setClipShapeTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setMaskTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setMaskTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setMaskShapeTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setMaskShapeTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setKeyTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setKeyTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setIdTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setIdTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setGeometryTransition0TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setGeometryTransition0TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setRestoreIdTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setRestoreIdTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setSphericalEffectTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setSphericalEffectTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setLightUpEffectTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setLightUpEffectTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setPixelStretchEffectTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setPixelStretchEffectTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityGroup0TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityGroup0TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityText0TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityText0TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityNextFocusIdTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityNextFocusIdTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityDefaultFocusTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityDefaultFocusTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityUseSamePageTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityUseSamePageTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityScrollTriggerableTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityScrollTriggerableTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityText1TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityText1TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityRoleTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityRoleTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityTextHintTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityTextHintTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityDescription0TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityDescription0TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityDescription1TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityDescription1TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityLevelTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityLevelTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityCheckedTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityCheckedTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilitySelectedTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilitySelectedTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setObscuredTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setObscuredTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setReuseIdTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setReuseIdTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
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
 * @tc.name: setBackgroundBrightnessTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackgroundBrightnessTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setMonopolizeEventsTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setMonopolizeEventsTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityFocusDrawLevelTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityFocusDrawLevelTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setCustomPropertyTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setCustomPropertyTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setExpandSafeAreaTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setExpandSafeAreaTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBackgroundImage0TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackgroundImage0TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBackgroundImage1TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackgroundImage1TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBackgroundBlurStyleTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackgroundBlurStyleTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBackgroundEffect1TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackgroundEffect1TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setForegroundBlurStyleTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setForegroundBlurStyleTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setFocusScopeIdTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setFocusScopeIdTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
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

/*
 * @tc.name: setTransition1TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setTransition1TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setGestureTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setGestureTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setPriorityGestureTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setPriorityGestureTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setParallelGestureTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setParallelGestureTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBlurTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBlurTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setLinearGradientBlurTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setLinearGradientBlurTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setUseEffect1TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setUseEffect1TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBackdropBlurTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackdropBlurTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setSharedTransitionTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setSharedTransitionTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setChainModeTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setChainModeTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setDragPreview1TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setDragPreview1TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setDragPreviewOptionsTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setDragPreviewOptionsTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setOverlayTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setOverlayTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBlendModeTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBlendModeTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAdvancedBlendModeTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAdvancedBlendModeTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setGeometryTransition1TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setGeometryTransition1TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBindTipsTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBindTipsTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBindPopupTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBindPopupTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBindMenu0TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBindMenu0TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBindMenu1TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBindMenu1TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAccessibilityGroup1TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAccessibilityGroup1TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}
} // namespace OHOS::Ace::NG
