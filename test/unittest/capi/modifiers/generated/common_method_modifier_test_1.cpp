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

#include "common_method_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::CommonMethod;
INSTANTIATE_TEST_SUITE_P(Tests, CommonMethodModifierTest, testing::Values(GENERATED_ARKUI_BLANK));

/*
 * @tc.name: setTabIndexTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setTabIndexTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TAB_INDEX_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TAB_INDEX_DEFAULT_VALUE) << "Default value for attribute 'tabIndex'";
}

/*
 * @tc.name: setTabIndexTestTabIndexValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setTabIndexTestTabIndexValidValues, TestSize.Level1)
{
    Ark_Number initValueTabIndex;

    // Initial setup
    initValueTabIndex = std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]);

    auto checkValue = [this, &initValueTabIndex](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueTabIndex = initValueTabIndex;

        inputValueTabIndex = value;
        modifier_->setTabIndex(node_, &inputValueTabIndex);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TAB_INDEX_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTabIndex, attribute: tabIndex";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberIntFloorValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setDefaultFocusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setDefaultFocusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_FOCUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DEFAULT_FOCUS_DEFAULT_VALUE) << "Default value for attribute 'defaultFocus'";
}

/*
 * @tc.name: setDefaultFocusTestDefaultFocusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setDefaultFocusTestDefaultFocusValidValues, TestSize.Level1)
{
    Ark_Boolean initValueDefaultFocus;

    // Initial setup
    initValueDefaultFocus = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueDefaultFocus](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueDefaultFocus = initValueDefaultFocus;

        inputValueDefaultFocus = value;
        modifier_->setDefaultFocus(node_, inputValueDefaultFocus);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_FOCUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDefaultFocus, attribute: defaultFocus";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setGroupDefaultFocusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setGroupDefaultFocusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GROUP_DEFAULT_FOCUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_GROUP_DEFAULT_FOCUS_DEFAULT_VALUE) <<
        "Default value for attribute 'groupDefaultFocus'";
}

/*
 * @tc.name: setGroupDefaultFocusTestGroupDefaultFocusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setGroupDefaultFocusTestGroupDefaultFocusValidValues, TestSize.Level1)
{
    Ark_Boolean initValueGroupDefaultFocus;

    // Initial setup
    initValueGroupDefaultFocus = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueGroupDefaultFocus](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueGroupDefaultFocus = initValueGroupDefaultFocus;

        inputValueGroupDefaultFocus = value;
        modifier_->setGroupDefaultFocus(node_, inputValueGroupDefaultFocus);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GROUP_DEFAULT_FOCUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setGroupDefaultFocus, attribute: groupDefaultFocus";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setFocusOnTouchTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFocusOnTouchTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_ON_TOUCH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_ON_TOUCH_DEFAULT_VALUE) << "Default value for attribute 'focusOnTouch'";
}

/*
 * @tc.name: setFocusOnTouchTestFocusOnTouchValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFocusOnTouchTestFocusOnTouchValidValues, TestSize.Level1)
{
    Ark_Boolean initValueFocusOnTouch;

    // Initial setup
    initValueFocusOnTouch = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueFocusOnTouch](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueFocusOnTouch = initValueFocusOnTouch;

        inputValueFocusOnTouch = value;
        modifier_->setFocusOnTouch(node_, inputValueFocusOnTouch);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_ON_TOUCH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFocusOnTouch, attribute: focusOnTouch";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setFlexGrowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFlexGrowTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_GROW_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FLEX_GROW_DEFAULT_VALUE) << "Default value for attribute 'flexGrow'";
}

/*
 * @tc.name: setFlexGrowTestFlexGrowValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFlexGrowTestFlexGrowValidValues, TestSize.Level1)
{
    Ark_Number initValueFlexGrow;

    // Initial setup
    initValueFlexGrow = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueFlexGrow](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueFlexGrow = initValueFlexGrow;

        inputValueFlexGrow = value;
        modifier_->setFlexGrow(node_, &inputValueFlexGrow);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_GROW_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFlexGrow, attribute: flexGrow";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setFlexShrinkTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFlexShrinkTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_SHRINK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FLEX_SHRINK_DEFAULT_VALUE) << "Default value for attribute 'flexShrink'";
}

/*
 * @tc.name: setFlexShrinkTestFlexShrinkValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFlexShrinkTestFlexShrinkValidValues, TestSize.Level1)
{
    Ark_Number initValueFlexShrink;

    // Initial setup
    initValueFlexShrink = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueFlexShrink](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueFlexShrink = initValueFlexShrink;

        inputValueFlexShrink = value;
        modifier_->setFlexShrink(node_, &inputValueFlexShrink);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_SHRINK_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFlexShrink, attribute: flexShrink";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setFlexBasisTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFlexBasisTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_BASIS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FLEX_BASIS_DEFAULT_VALUE) << "Default value for attribute 'flexBasis'";
}

/*
 * @tc.name: setFlexBasisTestFlexBasisValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFlexBasisTestFlexBasisValidValues, TestSize.Level1)
{
    Ark_Union_Number_String initValueFlexBasis;

    // Initial setup
    initValueFlexBasis = ArkUnion<Ark_Union_Number_String, Ark_String>(
        std::get<1>(Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueFlexBasis](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_String& value) {
        Ark_Union_Number_String inputValueFlexBasis = initValueFlexBasis;

        inputValueFlexBasis = value;
        modifier_->setFlexBasis(node_, &inputValueFlexBasis);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_BASIS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFlexBasis, attribute: flexBasis";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFlexBasisValidValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String, Ark_Number>(value));
    }
}

/*
 * @tc.name: setFlexBasisTestFlexBasisInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setFlexBasisTestFlexBasisInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String initValueFlexBasis;

    // Initial setup
    initValueFlexBasis = ArkUnion<Ark_Union_Number_String, Ark_String>(
        std::get<1>(Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueFlexBasis](const std::string& input, const Ark_Union_Number_String& value) {
        Ark_Union_Number_String inputValueFlexBasis = initValueFlexBasis;

        modifier_->setFlexBasis(node_, &inputValueFlexBasis);
        inputValueFlexBasis = value;
        modifier_->setFlexBasis(node_, &inputValueFlexBasis);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_BASIS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FLEX_BASIS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFlexBasis, attribute: flexBasis";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMarkAnchorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setMarkAnchorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultMarkAnchor =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_I_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARK_ANCHOR_I_X_DEFAULT_VALUE) <<
        "Default value for attribute 'markAnchor.Position.x'";

    resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_I_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARK_ANCHOR_I_Y_DEFAULT_VALUE) <<
        "Default value for attribute 'markAnchor.Position.y'";

    resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_I_START_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARK_ANCHOR_I_START_DEFAULT_VALUE) <<
        "Default value for attribute 'markAnchor.LocalizedPosition.start'";

    resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_I_TOP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARK_ANCHOR_I_TOP_DEFAULT_VALUE) <<
        "Default value for attribute 'markAnchor.LocalizedPosition.top'";
}

/*
 * @tc.name: setAlignRules0TestAlignRulesLeftAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesLeftAnchorValidValues, TestSize.Level1)
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
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesLeftAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules0TestAlignRulesLeftAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesLeftAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_HorizontalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.left).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultLeft = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_LEFT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLeft, ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_LEFT_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.left.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumHorizontalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesRightAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesRightAnchorValidValues, TestSize.Level1)
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
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesRightAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules0TestAlignRulesRightAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesRightAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_HorizontalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.right).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultRight =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_RIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRight, ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_RIGHT_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.right.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumHorizontalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesMiddleAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesMiddleAnchorValidValues, TestSize.Level1)
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
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesMiddleAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules0TestAlignRulesMiddleAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesMiddleAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_HorizontalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.middle).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultMiddle =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMiddle, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_MIDDLE_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.middle.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumHorizontalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesTopAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesTopAnchorValidValues, TestSize.Level1)
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
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesTopAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules0TestAlignRulesTopAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesTopAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_VerticalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.top).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultTop = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_TOP_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTop, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_TOP_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.top.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumVerticalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesBottomAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesBottomAnchorValidValues, TestSize.Level1)
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
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesBottomAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules0TestAlignRulesBottomAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesBottomAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_VerticalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.bottom).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBottom =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBottom, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BOTTOM_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.bottom.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumVerticalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesCenterAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesCenterAnchorValidValues, TestSize.Level1)
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
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesCenterAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules0TestAlignRulesCenterAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesCenterAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_VerticalAlign& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.center).align = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultCenter =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_CENTER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCenter, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_CENTER_I_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.center.align";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumVerticalAlignInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAlignRules0TestAlignRulesBiasHorizontalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesBiasHorizontalValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules0TestAlignRulesBiasHorizontalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesBiasHorizontalInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Opt_Number& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.bias).horizontal = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_HORIZONTAL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.bias.horizontal";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setAlignRules0TestAlignRulesBiasVerticalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesBiasVerticalValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules0TestAlignRulesBiasVerticalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules0TestAlignRulesBiasVerticalInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Opt_Number& value) {
        Ark_AlignRuleOption inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.bias).vertical = value;
        modifier_->setAlignRules0(node_, &inputValueAlignRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultAlignRules = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ALIGN_RULES_NAME);
        auto resultBias = GetAttrValue<std::unique_ptr<JsonValue>>(resultAlignRules, ATTRIBUTE_ALIGN_RULES_I_BIAS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultBias, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_RULES_I_BIAS_I_VERTICAL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignRules0, attribute: alignRules.bias.vertical";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setAlignRules1TestAlignRulesStartAnchorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesStartAnchorValidValues, TestSize.Level1)
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
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesStartAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules1TestAlignRulesStartAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesStartAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_HorizontalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.start).align = value;
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
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesEndAnchorValidValues, TestSize.Level1)
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
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesEndAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules1TestAlignRulesEndAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesEndAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_HorizontalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.end).align = value;
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
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesMiddleAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules1TestAlignRulesMiddleAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesMiddleAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_HorizontalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.middle).align = value;
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
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesTopAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules1TestAlignRulesTopAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesTopAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_VerticalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.top).align = value;
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
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBottomAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules1TestAlignRulesBottomAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesBottomAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_VerticalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.bottom).align = value;
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
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesCenterAlignValidValues, TestSize.Level1)
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
 * @tc.name: setAlignRules1TestAlignRulesCenterAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setAlignRules1TestAlignRulesCenterAlignInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueAlignRules](const std::string& input, const Ark_VerticalAlign& value) {
        Ark_LocalizedAlignRuleOptions inputValueAlignRules = initValueAlignRules;

        modifier_->setAlignRules1(node_, &inputValueAlignRules);
        WriteTo(inputValueAlignRules.center).align = value;
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

} // namespace OHOS::Ace::NG
