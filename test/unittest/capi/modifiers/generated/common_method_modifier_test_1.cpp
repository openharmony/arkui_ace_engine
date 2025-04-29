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
 * @tc.name: setChainWeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, DISABLED_setChainWeightTestDefaultValues, TestSize.Level1)
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
    Ark_ChainWeightOptions initValueChainWeight;

    // Initial setup
    initValueChainWeight.horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueChainWeight.vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueChainWeight](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_ChainWeightOptions inputValueChainWeight = initValueChainWeight;

        inputValueChainWeight.horizontal = value;
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
HWTEST_P(CommonMethodModifierTest, DISABLED_setChainWeightTestChainWeightHorizontalInvalidValues, TestSize.Level1)
{
    Ark_ChainWeightOptions initValueChainWeight;

    // Initial setup
    initValueChainWeight.horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueChainWeight.vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueChainWeight](const std::string& input, const Opt_Number& value) {
        Ark_ChainWeightOptions inputValueChainWeight = initValueChainWeight;

        modifier_->setChainWeight(node_, &inputValueChainWeight);
        inputValueChainWeight.horizontal = value;
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
    Ark_ChainWeightOptions initValueChainWeight;

    // Initial setup
    initValueChainWeight.horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueChainWeight.vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueChainWeight](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_ChainWeightOptions inputValueChainWeight = initValueChainWeight;

        inputValueChainWeight.vertical = value;
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
HWTEST_P(CommonMethodModifierTest, DISABLED_setChainWeightTestChainWeightVerticalInvalidValues, TestSize.Level1)
{
    Ark_ChainWeightOptions initValueChainWeight;

    // Initial setup
    initValueChainWeight.horizontal =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueChainWeight.vertical =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueChainWeight](const std::string& input, const Opt_Number& value) {
        Ark_ChainWeightOptions inputValueChainWeight = initValueChainWeight;

        modifier_->setChainWeight(node_, &inputValueChainWeight);
        inputValueChainWeight.vertical = value;
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
 * @tc.name: setMotionBlur0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setMotionBlur0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultMotionBlur =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MOTION_BLUR_NAME);
    std::unique_ptr<JsonValue> resultAnchor =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultMotionBlur, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultMotionBlur, ATTRIBUTE_MOTION_BLUR_I_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MOTION_BLUR_I_RADIUS_DEFAULT_VALUE) <<
        "Default value for attribute 'motionBlur.radius'";

    resultStr = GetAttrValue<std::string>(resultAnchor, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_X_DEFAULT_VALUE) <<
        "Default value for attribute 'motionBlur.anchor.x'";

    resultStr = GetAttrValue<std::string>(resultAnchor, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_Y_DEFAULT_VALUE) <<
        "Default value for attribute 'motionBlur.anchor.y'";
}

/*
 * @tc.name: setMotionBlur0TestMotionBlurRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setMotionBlur0TestMotionBlurRadiusValidValues, TestSize.Level1)
{
    Ark_MotionBlurOptions initValueMotionBlur;

    // Initial setup
    initValueMotionBlur.radius = std::get<1>(Fixtures::testFixtureMotionBlurRadiusNumberValidValues[0]);
    initValueMotionBlur.anchor.x = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);
    initValueMotionBlur.anchor.y = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);

    auto checkValue = [this, &initValueMotionBlur](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_MotionBlurOptions inputValueMotionBlur = initValueMotionBlur;

        inputValueMotionBlur.radius = value;
        modifier_->setMotionBlur0(node_, &inputValueMotionBlur);
        auto jsonValue = GetJsonValue(node_);
        auto resultMotionBlur = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MOTION_BLUR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMotionBlur, ATTRIBUTE_MOTION_BLUR_I_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMotionBlur0, attribute: motionBlur.radius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMotionBlurRadiusNumberValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setMotionBlur0TestMotionBlurAnchorXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setMotionBlur0TestMotionBlurAnchorXValidValues, TestSize.Level1)
{
    Ark_MotionBlurOptions initValueMotionBlur;

    // Initial setup
    initValueMotionBlur.radius = std::get<1>(Fixtures::testFixtureMotionBlurRadiusNumberValidValues[0]);
    initValueMotionBlur.anchor.x = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);
    initValueMotionBlur.anchor.y = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);

    auto checkValue = [this, &initValueMotionBlur](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_MotionBlurOptions inputValueMotionBlur = initValueMotionBlur;

        inputValueMotionBlur.anchor.x = value;
        modifier_->setMotionBlur0(node_, &inputValueMotionBlur);
        auto jsonValue = GetJsonValue(node_);
        auto resultMotionBlur = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MOTION_BLUR_NAME);
        auto resultAnchor =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultMotionBlur, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultAnchor, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMotionBlur0, attribute: motionBlur.anchor.x";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMotionBlurAnchorNumberValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setMotionBlur0TestMotionBlurAnchorYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setMotionBlur0TestMotionBlurAnchorYValidValues, TestSize.Level1)
{
    Ark_MotionBlurOptions initValueMotionBlur;

    // Initial setup
    initValueMotionBlur.radius = std::get<1>(Fixtures::testFixtureMotionBlurRadiusNumberValidValues[0]);
    initValueMotionBlur.anchor.x = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);
    initValueMotionBlur.anchor.y = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);

    auto checkValue = [this, &initValueMotionBlur](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_MotionBlurOptions inputValueMotionBlur = initValueMotionBlur;

        inputValueMotionBlur.anchor.y = value;
        modifier_->setMotionBlur0(node_, &inputValueMotionBlur);
        auto jsonValue = GetJsonValue(node_);
        auto resultMotionBlur = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MOTION_BLUR_NAME);
        auto resultAnchor =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultMotionBlur, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultAnchor, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMotionBlur0, attribute: motionBlur.anchor.y";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMotionBlurAnchorNumberValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setMotionBlur1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setMotionBlur1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultMotionBlur =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MOTION_BLUR_NAME);
    std::unique_ptr<JsonValue> resultAnchor =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultMotionBlur, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultMotionBlur, ATTRIBUTE_MOTION_BLUR_I_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MOTION_BLUR_I_RADIUS_DEFAULT_VALUE) <<
        "Default value for attribute 'motionBlur.radius'";

    resultStr = GetAttrValue<std::string>(resultAnchor, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_X_DEFAULT_VALUE) <<
        "Default value for attribute 'motionBlur.anchor.x'";

    resultStr = GetAttrValue<std::string>(resultAnchor, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_Y_DEFAULT_VALUE) <<
        "Default value for attribute 'motionBlur.anchor.y'";
}

/*
 * @tc.name: setMotionBlur1TestMotionBlurRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setMotionBlur1TestMotionBlurRadiusValidValues, TestSize.Level1)
{
    Opt_MotionBlurOptions initValueMotionBlur;

    // Initial setup
    WriteTo(initValueMotionBlur).radius = std::get<1>(Fixtures::testFixtureMotionBlurRadiusNumberValidValues[0]);
    WriteTo(initValueMotionBlur).anchor.x = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);
    WriteTo(initValueMotionBlur).anchor.y = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);

    auto checkValue = [this, &initValueMotionBlur](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Opt_MotionBlurOptions inputValueMotionBlur = initValueMotionBlur;

        WriteTo(inputValueMotionBlur).radius = value;
        modifier_->setMotionBlur1(node_, &inputValueMotionBlur);
        auto jsonValue = GetJsonValue(node_);
        auto resultMotionBlur = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MOTION_BLUR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMotionBlur, ATTRIBUTE_MOTION_BLUR_I_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMotionBlur1, attribute: motionBlur.radius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMotionBlurRadiusNumberValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setMotionBlur1TestMotionBlurAnchorXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setMotionBlur1TestMotionBlurAnchorXValidValues, TestSize.Level1)
{
    Opt_MotionBlurOptions initValueMotionBlur;

    // Initial setup
    WriteTo(initValueMotionBlur).radius = std::get<1>(Fixtures::testFixtureMotionBlurRadiusNumberValidValues[0]);
    WriteTo(initValueMotionBlur).anchor.x = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);
    WriteTo(initValueMotionBlur).anchor.y = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);

    auto checkValue = [this, &initValueMotionBlur](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Opt_MotionBlurOptions inputValueMotionBlur = initValueMotionBlur;

        WriteTo(inputValueMotionBlur).anchor.x = value;
        modifier_->setMotionBlur1(node_, &inputValueMotionBlur);
        auto jsonValue = GetJsonValue(node_);
        auto resultMotionBlur = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MOTION_BLUR_NAME);
        auto resultAnchor =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultMotionBlur, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultAnchor, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMotionBlur1, attribute: motionBlur.anchor.x";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMotionBlurAnchorNumberValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setMotionBlur1TestMotionBlurAnchorYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setMotionBlur1TestMotionBlurAnchorYValidValues, TestSize.Level1)
{
    Opt_MotionBlurOptions initValueMotionBlur;

    // Initial setup
    WriteTo(initValueMotionBlur).radius = std::get<1>(Fixtures::testFixtureMotionBlurRadiusNumberValidValues[0]);
    WriteTo(initValueMotionBlur).anchor.x = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);
    WriteTo(initValueMotionBlur).anchor.y = std::get<1>(Fixtures::testFixtureMotionBlurAnchorNumberValidValues[0]);

    auto checkValue = [this, &initValueMotionBlur](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Opt_MotionBlurOptions inputValueMotionBlur = initValueMotionBlur;

        WriteTo(inputValueMotionBlur).anchor.y = value;
        modifier_->setMotionBlur1(node_, &inputValueMotionBlur);
        auto jsonValue = GetJsonValue(node_);
        auto resultMotionBlur = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MOTION_BLUR_NAME);
        auto resultAnchor =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultMotionBlur, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultAnchor, ATTRIBUTE_MOTION_BLUR_I_ANCHOR_I_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMotionBlur1, attribute: motionBlur.anchor.y";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMotionBlurAnchorNumberValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setRotate0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestDefaultValues, TestSize.Level1)
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
 * @tc.name: setRotate0TestRotateXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotateXValidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        inputValueRotate.x = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRotate0, attribute: rotate.x";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotate0TestRotateXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotateXInvalidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate0(node_, &inputValueRotate);
        inputValueRotate.x = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate0, attribute: rotate.x";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotate0TestRotateYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotateYValidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        inputValueRotate.y = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRotate0, attribute: rotate.y";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotate0TestRotateYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotateYInvalidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate0(node_, &inputValueRotate);
        inputValueRotate.y = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate0, attribute: rotate.y";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotate0TestRotateZValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotateZValidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        inputValueRotate.z = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Z_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRotate0, attribute: rotate.z";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotate0TestRotateZInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotateZInvalidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate0(node_, &inputValueRotate);
        inputValueRotate.z = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Z_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_Z_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate0, attribute: rotate.z";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotate0TestRotateCenterXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotateCenterXValidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        inputValueRotate.centerX = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRotate0, attribute: rotate.centerX";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonPercValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setRotate0TestRotateCenterXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotateCenterXInvalidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Union_Number_String& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate0(node_, &inputValueRotate);
        inputValueRotate.centerX = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_CENTER_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate0, attribute: rotate.centerX";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonPercInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String>());
}

/*
 * @tc.name: setRotate0TestRotateCenterYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotateCenterYValidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        inputValueRotate.centerY = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRotate0, attribute: rotate.centerY";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonPercValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setRotate0TestRotateCenterYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotateCenterYInvalidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Union_Number_String& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate0(node_, &inputValueRotate);
        inputValueRotate.centerY = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_CENTER_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate0, attribute: rotate.centerY";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonPercInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String>());
}

/*
 * @tc.name: setRotate0TestRotatePerspectiveValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotatePerspectiveValidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        inputValueRotate.perspective = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_PERSPECTIVE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRotate0, attribute: rotate.perspective";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotate0TestRotatePerspectiveInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotatePerspectiveInvalidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate0(node_, &inputValueRotate);
        inputValueRotate.perspective = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_PERSPECTIVE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_PERSPECTIVE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate0, attribute: rotate.perspective";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotate0TestRotateAngleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate0TestRotateAngleInvalidValues, TestSize.Level1)
{
    Ark_RotateOptions initValueRotate;

    // Initial setup
    initValueRotate.x = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.y = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.z = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.centerX =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerY =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    initValueRotate.centerZ = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueRotate.perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    initValueRotate.angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Ark_Union_Number_String& value) {
        Ark_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate0(node_, &inputValueRotate);
        inputValueRotate.angle = value;
        modifier_->setRotate0(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_ANGLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_ANGLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate0, attribute: rotate.angle";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setRotate1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestDefaultValues, TestSize.Level1)
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
 * @tc.name: setRotate1TestRotateXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotateXValidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).x = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRotate1, attribute: rotate.x";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotate1TestRotateXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotateXInvalidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate1(node_, &inputValueRotate);
        WriteTo(inputValueRotate).x = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate1, attribute: rotate.x";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotate1TestRotateYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotateYValidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).y = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRotate1, attribute: rotate.y";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotate1TestRotateYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotateYInvalidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate1(node_, &inputValueRotate);
        WriteTo(inputValueRotate).y = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate1, attribute: rotate.y";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotate1TestRotateZValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotateZValidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).z = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Z_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRotate1, attribute: rotate.z";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotate1TestRotateZInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotateZInvalidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate1(node_, &inputValueRotate);
        WriteTo(inputValueRotate).z = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_Z_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_Z_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate1, attribute: rotate.z";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotate1TestRotateCenterXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotateCenterXValidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).centerX = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRotate1, attribute: rotate.centerX";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonPercValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setRotate1TestRotateCenterXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotateCenterXInvalidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Union_Number_String& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate1(node_, &inputValueRotate);
        WriteTo(inputValueRotate).centerX = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_CENTER_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate1, attribute: rotate.centerX";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonPercInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String>());
}

/*
 * @tc.name: setRotate1TestRotateCenterYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotateCenterYValidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).centerY = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRotate1, attribute: rotate.centerY";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonPercValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setRotate1TestRotateCenterYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotateCenterYInvalidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Union_Number_String& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate1(node_, &inputValueRotate);
        WriteTo(inputValueRotate).centerY = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_CENTER_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_CENTER_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate1, attribute: rotate.centerY";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonPercInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String>());
}

/*
 * @tc.name: setRotate1TestRotatePerspectiveValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotatePerspectiveValidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        WriteTo(inputValueRotate).perspective = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_PERSPECTIVE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRotate1, attribute: rotate.perspective";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setRotate1TestRotatePerspectiveInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotatePerspectiveInvalidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Opt_Number& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate1(node_, &inputValueRotate);
        WriteTo(inputValueRotate).perspective = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_PERSPECTIVE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_PERSPECTIVE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate1, attribute: rotate.perspective";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setRotate1TestRotateAngleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setRotate1TestRotateAngleInvalidValues, TestSize.Level1)
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
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteTo(initValueRotate).perspective =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));
    WriteTo(initValueRotate).angle = ArkUnion<Ark_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberFloatAnythingValidValues[0]));

    auto checkValue = [this, &initValueRotate](const std::string& input, const Ark_Union_Number_String& value) {
        Opt_RotateOptions inputValueRotate = initValueRotate;

        modifier_->setRotate1(node_, &inputValueRotate);
        WriteTo(inputValueRotate).angle = value;
        modifier_->setRotate1(node_, &inputValueRotate);
        auto jsonValue = GetJsonValue(node_);
        auto resultRotate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ROTATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultRotate, ATTRIBUTE_ROTATE_I_ANGLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROTATE_I_ANGLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRotate1, attribute: rotate.angle";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String, Ark_Empty>(nullptr));
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
 * @tc.name: setUseSizeTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setUseSizeTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultUseSizeType =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_USE_SIZE_TYPE_NAME);
    std::unique_ptr<JsonValue> resultXs =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultUseSizeType, ATTRIBUTE_USE_SIZE_TYPE_I_XS_NAME);
    std::unique_ptr<JsonValue> resultSm =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultUseSizeType, ATTRIBUTE_USE_SIZE_TYPE_I_SM_NAME);
    std::unique_ptr<JsonValue> resultMd =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultUseSizeType, ATTRIBUTE_USE_SIZE_TYPE_I_MD_NAME);
    std::unique_ptr<JsonValue> resultLg =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultUseSizeType, ATTRIBUTE_USE_SIZE_TYPE_I_LG_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultXs, ATTRIBUTE_USE_SIZE_TYPE_I_XS_I_SPAN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_USE_SIZE_TYPE_I_XS_I_SPAN_DEFAULT_VALUE) <<
        "Default value for attribute 'useSizeType.xs.Literal_Number_offset_span.span'";

    resultStr = GetAttrValue<std::string>(resultXs, ATTRIBUTE_USE_SIZE_TYPE_I_XS_I_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_USE_SIZE_TYPE_I_XS_I_OFFSET_DEFAULT_VALUE) <<
        "Default value for attribute 'useSizeType.xs.Literal_Number_offset_span.offset'";

    resultStr = GetAttrValue<std::string>(resultSm, ATTRIBUTE_USE_SIZE_TYPE_I_SM_I_SPAN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_USE_SIZE_TYPE_I_SM_I_SPAN_DEFAULT_VALUE) <<
        "Default value for attribute 'useSizeType.sm.Literal_Number_offset_span.span'";

    resultStr = GetAttrValue<std::string>(resultSm, ATTRIBUTE_USE_SIZE_TYPE_I_SM_I_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_USE_SIZE_TYPE_I_SM_I_OFFSET_DEFAULT_VALUE) <<
        "Default value for attribute 'useSizeType.sm.Literal_Number_offset_span.offset'";

    resultStr = GetAttrValue<std::string>(resultMd, ATTRIBUTE_USE_SIZE_TYPE_I_MD_I_SPAN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_USE_SIZE_TYPE_I_MD_I_SPAN_DEFAULT_VALUE) <<
        "Default value for attribute 'useSizeType.md.Literal_Number_offset_span.span'";

    resultStr = GetAttrValue<std::string>(resultMd, ATTRIBUTE_USE_SIZE_TYPE_I_MD_I_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_USE_SIZE_TYPE_I_MD_I_OFFSET_DEFAULT_VALUE) <<
        "Default value for attribute 'useSizeType.md.Literal_Number_offset_span.offset'";

    resultStr = GetAttrValue<std::string>(resultLg, ATTRIBUTE_USE_SIZE_TYPE_I_LG_I_SPAN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_USE_SIZE_TYPE_I_LG_I_SPAN_DEFAULT_VALUE) <<
        "Default value for attribute 'useSizeType.lg.Literal_Number_offset_span.span'";

    resultStr = GetAttrValue<std::string>(resultLg, ATTRIBUTE_USE_SIZE_TYPE_I_LG_I_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_USE_SIZE_TYPE_I_LG_I_OFFSET_DEFAULT_VALUE) <<
        "Default value for attribute 'useSizeType.lg.Literal_Number_offset_span.offset'";
}

/*
 * @tc.name: setUseSizeTypeTestUseSizeTypeSmLiteral_Number_offset_spanSpanValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(
    CommonMethodModifierTest, setUseSizeTypeTestUseSizeTypeSmLiteral_Number_offset_spanSpanValidValues, TestSize.Level1)
{
    Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs initValueUseSizeType;

    // Initial setup
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueUseSizeType](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs inputValueUseSizeType = initValueUseSizeType;

        WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(inputValueUseSizeType.sm)).span = value;
        modifier_->setUseSizeType(node_, &inputValueUseSizeType);
        auto jsonValue = GetJsonValue(node_);
        auto resultUseSizeType = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_USE_SIZE_TYPE_NAME);
        auto resultSm = GetAttrValue<std::unique_ptr<JsonValue>>(resultUseSizeType, ATTRIBUTE_USE_SIZE_TYPE_I_SM_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSm, ATTRIBUTE_USE_SIZE_TYPE_I_SM_I_SPAN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setUseSizeType, attribute: useSizeType.sm.Literal_Number_offset_span.span";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setUseSizeTypeTestUseSizeTypeSmLiteral_Number_offset_spanOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setUseSizeTypeTestUseSizeTypeSmLiteral_Number_offset_spanOffsetValidValues,
    TestSize.Level1)
{
    Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs initValueUseSizeType;

    // Initial setup
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueUseSizeType](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs inputValueUseSizeType = initValueUseSizeType;

        WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(inputValueUseSizeType.sm)).offset = value;
        modifier_->setUseSizeType(node_, &inputValueUseSizeType);
        auto jsonValue = GetJsonValue(node_);
        auto resultUseSizeType = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_USE_SIZE_TYPE_NAME);
        auto resultSm = GetAttrValue<std::unique_ptr<JsonValue>>(resultUseSizeType, ATTRIBUTE_USE_SIZE_TYPE_I_SM_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSm, ATTRIBUTE_USE_SIZE_TYPE_I_SM_I_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setUseSizeType, attribute: useSizeType.sm.Literal_Number_offset_span.offset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setUseSizeTypeTestUseSizeTypeMdLiteral_Number_offset_spanSpanValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(
    CommonMethodModifierTest, setUseSizeTypeTestUseSizeTypeMdLiteral_Number_offset_spanSpanValidValues, TestSize.Level1)
{
    Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs initValueUseSizeType;

    // Initial setup
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueUseSizeType](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs inputValueUseSizeType = initValueUseSizeType;

        WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(inputValueUseSizeType.md)).span = value;
        modifier_->setUseSizeType(node_, &inputValueUseSizeType);
        auto jsonValue = GetJsonValue(node_);
        auto resultUseSizeType = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_USE_SIZE_TYPE_NAME);
        auto resultMd = GetAttrValue<std::unique_ptr<JsonValue>>(resultUseSizeType, ATTRIBUTE_USE_SIZE_TYPE_I_MD_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMd, ATTRIBUTE_USE_SIZE_TYPE_I_MD_I_SPAN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setUseSizeType, attribute: useSizeType.md.Literal_Number_offset_span.span";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setUseSizeTypeTestUseSizeTypeMdLiteral_Number_offset_spanOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setUseSizeTypeTestUseSizeTypeMdLiteral_Number_offset_spanOffsetValidValues,
    TestSize.Level1)
{
    Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs initValueUseSizeType;

    // Initial setup
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueUseSizeType](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs inputValueUseSizeType = initValueUseSizeType;

        WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(inputValueUseSizeType.md)).offset = value;
        modifier_->setUseSizeType(node_, &inputValueUseSizeType);
        auto jsonValue = GetJsonValue(node_);
        auto resultUseSizeType = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_USE_SIZE_TYPE_NAME);
        auto resultMd = GetAttrValue<std::unique_ptr<JsonValue>>(resultUseSizeType, ATTRIBUTE_USE_SIZE_TYPE_I_MD_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMd, ATTRIBUTE_USE_SIZE_TYPE_I_MD_I_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setUseSizeType, attribute: useSizeType.md.Literal_Number_offset_span.offset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setUseSizeTypeTestUseSizeTypeLgLiteral_Number_offset_spanSpanValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(
    CommonMethodModifierTest, setUseSizeTypeTestUseSizeTypeLgLiteral_Number_offset_spanSpanValidValues, TestSize.Level1)
{
    Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs initValueUseSizeType;

    // Initial setup
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueUseSizeType](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs inputValueUseSizeType = initValueUseSizeType;

        WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(inputValueUseSizeType.lg)).span = value;
        modifier_->setUseSizeType(node_, &inputValueUseSizeType);
        auto jsonValue = GetJsonValue(node_);
        auto resultUseSizeType = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_USE_SIZE_TYPE_NAME);
        auto resultLg = GetAttrValue<std::unique_ptr<JsonValue>>(resultUseSizeType, ATTRIBUTE_USE_SIZE_TYPE_I_LG_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLg, ATTRIBUTE_USE_SIZE_TYPE_I_LG_I_SPAN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setUseSizeType, attribute: useSizeType.lg.Literal_Number_offset_span.span";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setUseSizeTypeTestUseSizeTypeLgLiteral_Number_offset_spanOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(CommonMethodModifierTest, setUseSizeTypeTestUseSizeTypeLgLiteral_Number_offset_spanOffsetValidValues,
    TestSize.Level1)
{
    Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs initValueUseSizeType;

    // Initial setup
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.xs)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.sm)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.md)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).span =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);
    WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(initValueUseSizeType.lg)).offset =
        std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueUseSizeType](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs inputValueUseSizeType = initValueUseSizeType;

        WriteToUnion<Ark_Literal_Number_offset_span>(WriteTo(inputValueUseSizeType.lg)).offset = value;
        modifier_->setUseSizeType(node_, &inputValueUseSizeType);
        auto jsonValue = GetJsonValue(node_);
        auto resultUseSizeType = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_USE_SIZE_TYPE_NAME);
        auto resultLg = GetAttrValue<std::unique_ptr<JsonValue>>(resultUseSizeType, ATTRIBUTE_USE_SIZE_TYPE_I_LG_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLg, ATTRIBUTE_USE_SIZE_TYPE_I_LG_I_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setUseSizeType, attribute: useSizeType.lg.Literal_Number_offset_span.offset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, value);
    }
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

} // namespace OHOS::Ace::NG
