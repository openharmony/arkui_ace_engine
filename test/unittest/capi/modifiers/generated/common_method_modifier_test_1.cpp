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
INSTANTIATE_TEST_SUITE_P(Tests, CommonMethodModifierTest, testing::Range(0, 1));

/*
 * @tc.name: setWidthTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setWidthTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setHeightTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setHeightTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setDrawModifierTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setDrawModifierTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setResponseRegionTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setResponseRegionTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setMouseResponseRegionTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setMouseResponseRegionTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setSizeTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setSizeTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setConstraintSizeTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setConstraintSizeTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setHitTestBehaviorTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setHitTestBehaviorTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setLayoutWeightTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setLayoutWeightTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setChainWeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setChainWeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultChainWeight =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CHAIN_WEIGHT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultChainWeight, ATTRIBUTE_CHAIN_WEIGHT_I_HORIZONTAL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CHAIN_WEIGHT_I_HORIZONTAL_DEFAULT_VALUE) <<
        "Default value for attribute 'chainWeight.horizontal'";

    resultStr = GetAttrValue<std::string>(resultChainWeight, ATTRIBUTE_CHAIN_WEIGHT_I_VERTICAL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CHAIN_WEIGHT_I_VERTICAL_DEFAULT_VALUE) <<
        "Default value for attribute 'chainWeight.vertical'";
}

/*
 * @tc.name: setChainWeightTestChainWeightHorizontalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setChainWeightTestChainWeightHorizontalValidValues, TestSize.Level1)
{
    Opt_ChainWeightOptions initValueChainWeight;

    // Initial setup
    WriteTo(initValueChainWeight).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueChainWeight).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueChainWeight](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_ChainWeightOptions inputValueChainWeight = initValueChainWeight;

        WriteTo(inputValueChainWeight).horizontal = value;
        modifier_->setChainWeight(node_, &inputValueChainWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultChainWeight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CHAIN_WEIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultChainWeight, ATTRIBUTE_CHAIN_WEIGHT_I_HORIZONTAL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setChainWeight, attribute: chainWeight.horizontal";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setChainWeightTestChainWeightHorizontalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setChainWeightTestChainWeightHorizontalInvalidValues, TestSize.Level1)
{
    Opt_ChainWeightOptions initValueChainWeight;

    // Initial setup
    WriteTo(initValueChainWeight).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueChainWeight).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueChainWeight](const std::string& input, const Opt_Number& value) {
        Opt_ChainWeightOptions inputValueChainWeight = initValueChainWeight;

        modifier_->setChainWeight(node_, &inputValueChainWeight);
        WriteTo(inputValueChainWeight).horizontal = value;
        modifier_->setChainWeight(node_, &inputValueChainWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultChainWeight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CHAIN_WEIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultChainWeight, ATTRIBUTE_CHAIN_WEIGHT_I_HORIZONTAL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CHAIN_WEIGHT_I_HORIZONTAL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setChainWeight, attribute: chainWeight.horizontal";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setChainWeightTestChainWeightVerticalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setChainWeightTestChainWeightVerticalValidValues, TestSize.Level1)
{
    Opt_ChainWeightOptions initValueChainWeight;

    // Initial setup
    WriteTo(initValueChainWeight).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueChainWeight).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueChainWeight](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_ChainWeightOptions inputValueChainWeight = initValueChainWeight;

        WriteTo(inputValueChainWeight).vertical = value;
        modifier_->setChainWeight(node_, &inputValueChainWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultChainWeight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CHAIN_WEIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultChainWeight, ATTRIBUTE_CHAIN_WEIGHT_I_VERTICAL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setChainWeight, attribute: chainWeight.vertical";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setChainWeightTestChainWeightVerticalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setChainWeightTestChainWeightVerticalInvalidValues, TestSize.Level1)
{
    Opt_ChainWeightOptions initValueChainWeight;

    // Initial setup
    WriteTo(initValueChainWeight).horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueChainWeight).vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueChainWeight](const std::string& input, const Opt_Number& value) {
        Opt_ChainWeightOptions inputValueChainWeight = initValueChainWeight;

        modifier_->setChainWeight(node_, &inputValueChainWeight);
        WriteTo(inputValueChainWeight).vertical = value;
        modifier_->setChainWeight(node_, &inputValueChainWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultChainWeight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CHAIN_WEIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultChainWeight, ATTRIBUTE_CHAIN_WEIGHT_I_VERTICAL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CHAIN_WEIGHT_I_VERTICAL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setChainWeight, attribute: chainWeight.vertical";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setPaddingTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setPaddingTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setSafeAreaPaddingTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setSafeAreaPaddingTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setMarginTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setMarginTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBackgroundColorTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackgroundColorTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setPixelRoundTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setPixelRoundTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBackgroundImageSizeTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackgroundImageSizeTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBackgroundImagePositionTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackgroundImagePositionTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBackgroundEffect0TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackgroundEffect0TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBackgroundImageResizableTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackgroundImageResizableTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setForegroundEffectTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setForegroundEffectTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBackgroundFilterTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBackgroundFilterTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setForegroundFilterTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setForegroundFilterTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setCompositingFilterTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setCompositingFilterTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setOpacityTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setOpacityTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBorderTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBorderTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBorderStyleTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBorderStyleTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBorderWidthTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBorderWidthTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBorderColorTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBorderColorTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBorderRadiusTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBorderRadiusTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBorderImageTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBorderImageTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setOutlineTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setOutlineTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setOutlineStyleTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setOutlineStyleTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setOutlineWidthTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setOutlineWidthTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setOutlineColorTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setOutlineColorTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setOutlineRadiusTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setOutlineRadiusTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setForegroundColorTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setForegroundColorTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setHoverEffectTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setHoverEffectTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setFocusableTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setFocusableTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setNextFocusTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setNextFocusTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setTabStopTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setTabStopTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

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
    Opt_Number initValueTabIndex;

    // Initial setup
    initValueTabIndex = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]));

    auto checkValue = [this, &initValueTabIndex](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueTabIndex = initValueTabIndex;

        inputValueTabIndex = value;
        modifier_->setTabIndex(node_, &inputValueTabIndex);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TAB_INDEX_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTabIndex, attribute: tabIndex";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberIntFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setTabIndexTestTabIndexInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setTabIndexTestTabIndexInvalidValues, TestSize.Level1)
{
    Opt_Number initValueTabIndex;

    // Initial setup
    initValueTabIndex = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberIntFloorValidValues[0]));

    auto checkValue = [this, &initValueTabIndex](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueTabIndex = initValueTabIndex;

        modifier_->setTabIndex(node_, &inputValueTabIndex);
        inputValueTabIndex = value;
        modifier_->setTabIndex(node_, &inputValueTabIndex);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TAB_INDEX_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TAB_INDEX_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTabIndex, attribute: tabIndex";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
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
    Opt_Boolean initValueDefaultFocus;

    // Initial setup
    initValueDefaultFocus = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueDefaultFocus](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueDefaultFocus = initValueDefaultFocus;

        inputValueDefaultFocus = value;
        modifier_->setDefaultFocus(node_, &inputValueDefaultFocus);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_FOCUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDefaultFocus, attribute: defaultFocus";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setDefaultFocusTestDefaultFocusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setDefaultFocusTestDefaultFocusInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueDefaultFocus;

    // Initial setup
    initValueDefaultFocus = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueDefaultFocus](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueDefaultFocus = initValueDefaultFocus;

        modifier_->setDefaultFocus(node_, &inputValueDefaultFocus);
        inputValueDefaultFocus = value;
        modifier_->setDefaultFocus(node_, &inputValueDefaultFocus);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DEFAULT_FOCUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DEFAULT_FOCUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDefaultFocus, attribute: defaultFocus";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
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
    Opt_Boolean initValueGroupDefaultFocus;

    // Initial setup
    initValueGroupDefaultFocus = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueGroupDefaultFocus](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueGroupDefaultFocus = initValueGroupDefaultFocus;

        inputValueGroupDefaultFocus = value;
        modifier_->setGroupDefaultFocus(node_, &inputValueGroupDefaultFocus);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GROUP_DEFAULT_FOCUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setGroupDefaultFocus, attribute: groupDefaultFocus";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setGroupDefaultFocusTestGroupDefaultFocusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setGroupDefaultFocusTestGroupDefaultFocusInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueGroupDefaultFocus;

    // Initial setup
    initValueGroupDefaultFocus = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueGroupDefaultFocus](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueGroupDefaultFocus = initValueGroupDefaultFocus;

        modifier_->setGroupDefaultFocus(node_, &inputValueGroupDefaultFocus);
        inputValueGroupDefaultFocus = value;
        modifier_->setGroupDefaultFocus(node_, &inputValueGroupDefaultFocus);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GROUP_DEFAULT_FOCUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_GROUP_DEFAULT_FOCUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setGroupDefaultFocus, attribute: groupDefaultFocus";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
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
    Opt_Boolean initValueFocusOnTouch;

    // Initial setup
    initValueFocusOnTouch = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFocusOnTouch](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueFocusOnTouch = initValueFocusOnTouch;

        inputValueFocusOnTouch = value;
        modifier_->setFocusOnTouch(node_, &inputValueFocusOnTouch);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_ON_TOUCH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFocusOnTouch, attribute: focusOnTouch";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setFocusOnTouchTestFocusOnTouchInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setFocusOnTouchTestFocusOnTouchInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueFocusOnTouch;

    // Initial setup
    initValueFocusOnTouch = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFocusOnTouch](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueFocusOnTouch = initValueFocusOnTouch;

        modifier_->setFocusOnTouch(node_, &inputValueFocusOnTouch);
        inputValueFocusOnTouch = value;
        modifier_->setFocusOnTouch(node_, &inputValueFocusOnTouch);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_ON_TOUCH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_ON_TOUCH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFocusOnTouch, attribute: focusOnTouch";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setFocusBoxTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setFocusBoxTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAnimationTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAnimationTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setTransition0TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setTransition0TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setMotionBlurTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setMotionBlurTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBrightnessTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setBrightnessTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setContrastTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setContrastTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setGrayscaleTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setGrayscaleTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setColorBlendTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setColorBlendTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setSaturateTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setSaturateTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setSepiaTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setSepiaTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setInvertTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setInvertTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setHueRotateTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setHueRotateTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setUseShadowBatchingTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setUseShadowBatchingTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setUseEffect0TestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setUseEffect0TestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setRenderGroupTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setRenderGroupTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setFreezeTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setFreezeTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setTranslateTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setTranslateTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setScaleTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setScaleTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setRotateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultRotate =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_X_DEFAULT_VALUE) << "Default value for attribute 'rotate.x'";

    resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_Y_DEFAULT_VALUE) << "Default value for attribute 'rotate.y'";

    resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Z_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_Z_DEFAULT_VALUE) << "Default value for attribute 'rotate.z'";

    resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_CENTER_X_DEFAULT_VALUE) << "Default value for attribute 'rotate.centerX'";

    resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_CENTER_Y_DEFAULT_VALUE) << "Default value for attribute 'rotate.centerY'";

    resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_Z_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_CENTER_Z_DEFAULT_VALUE) << "Default value for attribute 'rotate.centerZ'";

    resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_PERSPECTIVE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_PERSPECTIVE_DEFAULT_VALUE) <<
        "Default value for attribute 'rotate.perspective'";

    resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_ANGLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_ANGLE_DEFAULT_VALUE) << "Default value for attribute 'rotate.angle'";
}

/*
 * @tc.name: setRotateTestRotateXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotateXValidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).x = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRotate, attribute: rotate.x";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotateTestRotateXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotateXInvalidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate(node_, &inputValueRotate);
        WriteTo(inputValueRotate).x = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.x";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotateTestRotateYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotateYValidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).y = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRotate, attribute: rotate.y";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotateTestRotateYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotateYInvalidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate(node_, &inputValueRotate);
        WriteTo(inputValueRotate).y = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.y";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotateTestRotateZValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotateZValidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).z = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Z_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRotate, attribute: rotate.z";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotateTestRotateZInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotateZInvalidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate(node_, &inputValueRotate);
        WriteTo(inputValueRotate).z = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Z_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_Z_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.z";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotateTestRotateCenterXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotateCenterXValidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).centerX = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.centerX";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setRotateTestRotateCenterXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setRotateTestRotateCenterXInvalidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Union_Number_String& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate(node_, &inputValueRotate);
        WriteTo(inputValueRotate).centerX = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_CENTER_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.centerX";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String>());
}

/*
 * @tc.name: setRotateTestRotateCenterYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotateCenterYValidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).centerY = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.centerY";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setRotateTestRotateCenterYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setRotateTestRotateCenterYInvalidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Union_Number_String& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate(node_, &inputValueRotate);
        WriteTo(inputValueRotate).centerY = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_CENTER_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.centerY";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String>());
}

/*
 * @tc.name: setRotateTestRotateCenterZValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setRotateTestRotateCenterZValidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).centerZ = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_Z_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.centerZ";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotateTestRotateCenterZInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setRotateTestRotateCenterZInvalidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate(node_, &inputValueRotate);
        WriteTo(inputValueRotate).centerZ = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_Z_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_CENTER_Z_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.centerZ";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotateTestRotatePerspectiveValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotatePerspectiveValidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).perspective = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_PERSPECTIVE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.perspective";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotateTestRotatePerspectiveInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotatePerspectiveInvalidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate(node_, &inputValueRotate);
        WriteTo(inputValueRotate).perspective = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_PERSPECTIVE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_PERSPECTIVE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.perspective";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotateTestRotateAngleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotateAngleValidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_String& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).angle = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_ANGLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.angle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringFloatAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setRotateTestRotateAngleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotateTestRotateAngleInvalidValues, TestSize.Level1)
{
    Opt_RotateOptions initValueRotate;

    // Initial setup
    WriteTo(initValueRotate).x =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).y =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).z =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).centerZ =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Ark_Union_Number_String& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate(node_, &inputValueRotate);
        WriteTo(inputValueRotate).angle = value;
        modifier_->setRotate(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_ANGLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_ANGLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate, attribute: rotate.angle";
    };

    for (auto& [input, value] : Fixtures::testFixtureStringFloatAnythingInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTransformTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setTransformTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setVisibilityTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setVisibilityTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
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
    Opt_Number initValueFlexGrow;

    // Initial setup
    initValueFlexGrow = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueFlexGrow](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueFlexGrow = initValueFlexGrow;

        inputValueFlexGrow = value;
        modifier_->setFlexGrow(node_, &inputValueFlexGrow);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_GROW_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFlexGrow, attribute: flexGrow";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setFlexGrowTestFlexGrowInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setFlexGrowTestFlexGrowInvalidValues, TestSize.Level1)
{
    Opt_Number initValueFlexGrow;

    // Initial setup
    initValueFlexGrow = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueFlexGrow](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueFlexGrow = initValueFlexGrow;

        modifier_->setFlexGrow(node_, &inputValueFlexGrow);
        inputValueFlexGrow = value;
        modifier_->setFlexGrow(node_, &inputValueFlexGrow);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_GROW_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FLEX_GROW_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFlexGrow, attribute: flexGrow";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
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
    Opt_Number initValueFlexShrink;

    // Initial setup
    initValueFlexShrink = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueFlexShrink](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueFlexShrink = initValueFlexShrink;

        inputValueFlexShrink = value;
        modifier_->setFlexShrink(node_, &inputValueFlexShrink);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_SHRINK_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFlexShrink, attribute: flexShrink";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setFlexShrinkTestFlexShrinkInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setFlexShrinkTestFlexShrinkInvalidValues, TestSize.Level1)
{
    Opt_Number initValueFlexShrink;

    // Initial setup
    initValueFlexShrink = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueFlexShrink](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueFlexShrink = initValueFlexShrink;

        modifier_->setFlexShrink(node_, &inputValueFlexShrink);
        inputValueFlexShrink = value;
        modifier_->setFlexShrink(node_, &inputValueFlexShrink);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_SHRINK_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FLEX_SHRINK_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFlexShrink, attribute: flexShrink";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
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
    Opt_Union_Number_String initValueFlexBasis;

    // Initial setup
    initValueFlexBasis = ArkUnion<Opt_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFlexBasis](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String& value) {
        Opt_Union_Number_String inputValueFlexBasis = initValueFlexBasis;

        inputValueFlexBasis = value;
        modifier_->setFlexBasis(node_, &inputValueFlexBasis);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_BASIS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFlexBasis, attribute: flexBasis";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setFlexBasisTestFlexBasisInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setFlexBasisTestFlexBasisInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_String initValueFlexBasis;

    // Initial setup
    initValueFlexBasis = ArkUnion<Opt_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFlexBasis](const std::string& input, const Opt_Union_Number_String& value) {
        Opt_Union_Number_String inputValueFlexBasis = initValueFlexBasis;

        modifier_->setFlexBasis(node_, &inputValueFlexBasis);
        inputValueFlexBasis = value;
        modifier_->setFlexBasis(node_, &inputValueFlexBasis);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FLEX_BASIS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FLEX_BASIS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFlexBasis, attribute: flexBasis";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String>());
}

/*
 * @tc.name: setAlignSelfTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAlignSelfTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setDisplayPriorityTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setDisplayPriorityTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setZIndexTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setZIndexTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setDirectionTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setDirectionTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setAlignTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setAlignTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setPositionTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setPositionTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
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
}

/*
 * @tc.name: setMarkAnchorTestMarkAnchorPositionXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setMarkAnchorTestMarkAnchorPositionXValidValues, TestSize.Level1)
{
    Opt_Union_Position_LocalizedPosition initValueMarkAnchor;

    // Initial setup
    WriteToUnion<Ark_Position>(WriteTo(initValueMarkAnchor)).x =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteToUnion<Ark_Position>(WriteTo(initValueMarkAnchor)).y =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueMarkAnchor](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Union_Position_LocalizedPosition inputValueMarkAnchor = initValueMarkAnchor;

        WriteToUnion<Ark_Position>(WriteTo(inputValueMarkAnchor)).x = value;
        modifier_->setMarkAnchor(node_, &inputValueMarkAnchor);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarkAnchor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_I_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMarkAnchor, attribute: markAnchor.Position.x";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setMarkAnchorTestMarkAnchorPositionXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setMarkAnchorTestMarkAnchorPositionXInvalidValues, TestSize.Level1)
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
        WriteToUnion<Ark_Position>(WriteTo(inputValueMarkAnchor)).x = value;
        modifier_->setMarkAnchor(node_, &inputValueMarkAnchor);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarkAnchor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_I_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MARK_ANCHOR_I_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMarkAnchor, attribute: markAnchor.Position.x";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setMarkAnchorTestMarkAnchorPositionYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setMarkAnchorTestMarkAnchorPositionYValidValues, TestSize.Level1)
{
    Opt_Union_Position_LocalizedPosition initValueMarkAnchor;

    // Initial setup
    WriteToUnion<Ark_Position>(WriteTo(initValueMarkAnchor)).x =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteToUnion<Ark_Position>(WriteTo(initValueMarkAnchor)).y =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueMarkAnchor](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Union_Position_LocalizedPosition inputValueMarkAnchor = initValueMarkAnchor;

        WriteToUnion<Ark_Position>(WriteTo(inputValueMarkAnchor)).y = value;
        modifier_->setMarkAnchor(node_, &inputValueMarkAnchor);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarkAnchor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_I_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMarkAnchor, attribute: markAnchor.Position.y";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

} // namespace OHOS::Ace::NG
