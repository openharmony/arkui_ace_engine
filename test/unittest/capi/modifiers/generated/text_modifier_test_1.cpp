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

#include "text_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Text;

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) << "Default value for attribute 'fontColor'";
}

/*
 * @tc.name: setFontColorTestFontColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontColorTestFontColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFontColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueFontColor = initValueFontColor;

        inputValueFontColor = value;
        modifier_->setFontColor(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontColor, attribute: fontColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontColorTestFontColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontColorTestFontColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFontColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueFontColor = initValueFontColor;

        modifier_->setFontColor(node_, &inputValueFontColor);
        inputValueFontColor = value;
        modifier_->setFontColor(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontColor, attribute: fontColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'fontSize'";
}

/*
 * @tc.name: setFontSizeTestFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontSizeTestFontSizeValidValues, TestSize.Level1)
{
    Opt_Union_Number_String_Resource initValueFontSize;

    // Initial setup
    initValueFontSize = ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String_Resource& value) {
        Opt_Union_Number_String_Resource inputValueFontSize = initValueFontSize;

        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontSizeTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_String_Resource initValueFontSize;

    // Initial setup
    initValueFontSize = ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](
                          const std::string& input, const Opt_Union_Number_String_Resource& value) {
        Opt_Union_Number_String_Resource inputValueFontSize = initValueFontSize;

        modifier_->setFontSize(node_, &inputValueFontSize);
        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String_Resource>());
}

/*
 * @tc.name: setMinFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMinFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'minFontSize'";
}

/*
 * @tc.name: setMinFontSizeTestMinFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMinFontSizeTestMinFontSizeValidValues, TestSize.Level1)
{
    Opt_Union_Number_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String_Resource& value) {
        Opt_Union_Number_String_Resource inputValueMinFontSize = initValueMinFontSize;

        inputValueMinFontSize = value;
        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setMinFontSizeTestMinFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMinFontSizeTestMinFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](
                          const std::string& input, const Opt_Union_Number_String_Resource& value) {
        Opt_Union_Number_String_Resource inputValueMinFontSize = initValueMinFontSize;

        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        inputValueMinFontSize = value;
        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String_Resource>());
}

/*
 * @tc.name: setMaxFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'maxFontSize'";
}

/*
 * @tc.name: setMaxFontSizeTestMaxFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxFontSizeTestMaxFontSizeValidValues, TestSize.Level1)
{
    Opt_Union_Number_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String_Resource& value) {
        Opt_Union_Number_String_Resource inputValueMaxFontSize = initValueMaxFontSize;

        inputValueMaxFontSize = value;
        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxFontSize, attribute: maxFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setMaxFontSizeTestMaxFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxFontSizeTestMaxFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](
                          const std::string& input, const Opt_Union_Number_String_Resource& value) {
        Opt_Union_Number_String_Resource inputValueMaxFontSize = initValueMaxFontSize;

        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        inputValueMaxFontSize = value;
        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxFontSize, attribute: maxFontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String_Resource>());
}

/*
 * @tc.name: setMinFontScaleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMinFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'minFontScale'";
}

/*
 * @tc.name: setMinFontScaleTestMinFontScaleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMinFontScaleTestMinFontScaleValidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMinFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueMinFontScale = initValueMinFontScale;

        inputValueMinFontScale = value;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMinFontScaleNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureMinFontScaleResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setMinFontScaleTestMinFontScaleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMinFontScaleTestMinFontScaleInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMinFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueMinFontScale = initValueMinFontScale;

        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        inputValueMinFontScale = value;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setMaxFontScaleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'maxFontScale'";
}

/*
 * @tc.name: setMaxFontScaleTestMaxFontScaleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMaxFontScaleTestMaxFontScaleValidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMaxFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueMaxFontScale = initValueMaxFontScale;

        inputValueMaxFontScale = value;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMaxFontScaleNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureMaxFontScaleResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setMaxFontScaleTestMaxFontScaleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxFontScaleTestMaxFontScaleInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMaxFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueMaxFontScale = initValueMaxFontScale;

        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        inputValueMaxFontScale = value;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setFontStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE) << "Default value for attribute 'fontStyle'";
}

/*
 * @tc.name: setFontStyleTestFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontStyleTestFontStyleValidValues, TestSize.Level1)
{
    Opt_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFontStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_FontStyle inputValueFontStyle = initValueFontStyle;

        inputValueFontStyle = value;
        modifier_->setFontStyle(node_, &inputValueFontStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontStyle, attribute: fontStyle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFontStyleTestFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontStyleTestFontStyleInvalidValues, TestSize.Level1)
{
    Opt_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFontStyle](const std::string& input, const Opt_FontStyle& value) {
        Opt_FontStyle inputValueFontStyle = initValueFontStyle;

        modifier_->setFontStyle(node_, &inputValueFontStyle);
        inputValueFontStyle = value;
        modifier_->setFontStyle(node_, &inputValueFontStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontStyle, attribute: fontStyle";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setTextAlignTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextAlignTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_ALIGN_DEFAULT_VALUE) << "Default value for attribute 'textAlign'";
}

/*
 * @tc.name: setTextAlignTestTextAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextAlignTestTextAlignValidValues, TestSize.Level1)
{
    Opt_TextAlign initValueTextAlign;

    // Initial setup
    initValueTextAlign = ArkValue<Opt_TextAlign>(std::get<1>(Fixtures::testFixtureTextAlignTypeValidValues[0]));

    auto checkValue = [this, &initValueTextAlign](
                          const std::string& input, const std::string& expectedStr, const Opt_TextAlign& value) {
        Opt_TextAlign inputValueTextAlign = initValueTextAlign;

        inputValueTextAlign = value;
        modifier_->setTextAlign(node_, &inputValueTextAlign);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextAlign, attribute: textAlign";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextAlignTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextAlign>(value));
    }
}

/*
 * @tc.name: setTextAlignTestTextAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextAlignTestTextAlignInvalidValues, TestSize.Level1)
{
    Opt_TextAlign initValueTextAlign;

    // Initial setup
    initValueTextAlign = ArkValue<Opt_TextAlign>(std::get<1>(Fixtures::testFixtureTextAlignTypeValidValues[0]));

    auto checkValue = [this, &initValueTextAlign](const std::string& input, const Opt_TextAlign& value) {
        Opt_TextAlign inputValueTextAlign = initValueTextAlign;

        modifier_->setTextAlign(node_, &inputValueTextAlign);
        inputValueTextAlign = value;
        modifier_->setTextAlign(node_, &inputValueTextAlign);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextAlign, attribute: textAlign";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextAlignTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_TextAlign>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_TextAlign>());
}

/*
 * @tc.name: setLineHeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLineHeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE) << "Default value for attribute 'lineHeight'";
}

/*
 * @tc.name: setLineHeightTestLineHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLineHeightTestLineHeightValidValues, TestSize.Level1)
{
    Opt_Union_Number_String_Resource initValueLineHeight;

    // Initial setup
    initValueLineHeight = ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueLineHeight](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String_Resource& value) {
        Opt_Union_Number_String_Resource inputValueLineHeight = initValueLineHeight;

        inputValueLineHeight = value;
        modifier_->setLineHeight(node_, &inputValueLineHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLineHeight, attribute: lineHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setLineHeightTestLineHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLineHeightTestLineHeightInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_String_Resource initValueLineHeight;

    // Initial setup
    initValueLineHeight = ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueLineHeight](
                          const std::string& input, const Opt_Union_Number_String_Resource& value) {
        Opt_Union_Number_String_Resource inputValueLineHeight = initValueLineHeight;

        modifier_->setLineHeight(node_, &inputValueLineHeight);
        inputValueLineHeight = value;
        modifier_->setLineHeight(node_, &inputValueLineHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLineHeight, attribute: lineHeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String_Resource>());
}

/*
 * @tc.name: setTextOverflowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextOverflowTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTextOverflow =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultTextOverflow, ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_DEFAULT_VALUE) <<
        "Default value for attribute 'textOverflow.overflow'";
}

/*
 * @tc.name: setTextOverflowTestTextOverflowOverflowValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextOverflowTestTextOverflowOverflowValidValues, TestSize.Level1)
{
    Opt_TextOverflowOptions initValueTextOverflow;

    // Initial setup
    WriteTo(initValueTextOverflow).overflow = std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]);

    auto checkValue = [this, &initValueTextOverflow](
                          const std::string& input, const std::string& expectedStr, const Ark_TextOverflow& value) {
        Opt_TextOverflowOptions inputValueTextOverflow = initValueTextOverflow;

        WriteTo(inputValueTextOverflow).overflow = value;
        modifier_->setTextOverflow(node_, &inputValueTextOverflow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextOverflow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextOverflow, ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextOverflow, attribute: textOverflow.overflow";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextOverflowValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setTextOverflowTestTextOverflowOverflowInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextOverflowTestTextOverflowOverflowInvalidValues, TestSize.Level1)
{
    Opt_TextOverflowOptions initValueTextOverflow;

    // Initial setup
    WriteTo(initValueTextOverflow).overflow = std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]);

    auto checkValue = [this, &initValueTextOverflow](const std::string& input, const Ark_TextOverflow& value) {
        Opt_TextOverflowOptions inputValueTextOverflow = initValueTextOverflow;

        modifier_->setTextOverflow(node_, &inputValueTextOverflow);
        WriteTo(inputValueTextOverflow).overflow = value;
        modifier_->setTextOverflow(node_, &inputValueTextOverflow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextOverflow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextOverflow, ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_OVERFLOW_I_OVERFLOW_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextOverflow, attribute: textOverflow.overflow";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextOverflowInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setFontFamilyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontFamilyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE) << "Default value for attribute 'fontFamily'";
}

/*
 * @tc.name: setFontFamilyTestFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontFamilyTestFontFamilyValidValues, TestSize.Level1)
{
    Opt_Union_String_Resource initValueFontFamily;

    // Initial setup
    initValueFontFamily = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_Union_String_Resource inputValueFontFamily = initValueFontFamily;

        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontFamilyTestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontFamilyTestFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_Union_String_Resource initValueFontFamily;

    // Initial setup
    initValueFontFamily = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_Union_String_Resource inputValueFontFamily = initValueFontFamily;

        modifier_->setFontFamily(node_, &inputValueFontFamily);
        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFamilyResourceInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontFamilyStringInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setMaxLinesTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxLinesTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LINES_DEFAULT_VALUE) << "Default value for attribute 'maxLines'";
}

/*
 * @tc.name: setMaxLinesTestMaxLinesValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMaxLinesTestMaxLinesValidValues, TestSize.Level1)
{
    Opt_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));

    auto checkValue = [this, &initValueMaxLines](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueMaxLines = initValueMaxLines;

        inputValueMaxLines = value;
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberPosIntFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setMaxLinesTestMaxLinesInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMaxLinesTestMaxLinesInvalidValues, TestSize.Level1)
{
    Opt_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));

    auto checkValue = [this, &initValueMaxLines](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueMaxLines = initValueMaxLines;

        modifier_->setMaxLines(node_, &inputValueMaxLines);
        inputValueMaxLines = value;
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LINES_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberPosIntFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setDecorationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDecorationTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultDecoration =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_TYPE_DEFAULT_VALUE) << "Default value for attribute 'decoration.type'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'decoration.color'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'decoration.style'";
}

/*
 * @tc.name: setDecorationTestDecorationTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDecorationTestDecorationTypeValidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const std::string& expectedStr,
                          const Ark_TextDecorationType& value) {
        Opt_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        WriteTo(inputValueDecoration).type = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextDecorationTypeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setDecorationTestDecorationTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDecorationTestDecorationTypeInvalidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Ark_TextDecorationType& value) {
        Opt_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        WriteTo(inputValueDecoration).type = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextDecorationTypeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setDecorationTestDecorationColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setDecorationTestDecorationColorValidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        WriteTo(inputValueDecoration).color = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setDecorationTestDecorationColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDecorationTestDecorationColorInvalidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Opt_ResourceColor& value) {
        Opt_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        WriteTo(inputValueDecoration).color = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setDecorationTestDecorationStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDecorationTestDecorationStyleValidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const std::string& expectedStr,
                          const Opt_TextDecorationStyle& value) {
        Opt_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        WriteTo(inputValueDecoration).style = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextDecorationStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextDecorationStyle>(value));
    }
}

/*
 * @tc.name: setDecorationTestDecorationStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDecorationTestDecorationStyleInvalidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Opt_TextDecorationStyle& value) {
        Opt_DecorationStyleInterface inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        WriteTo(inputValueDecoration).style = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextDecorationStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_TextDecorationStyle>(value));
    }
}

/*
 * @tc.name: setLetterSpacingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLetterSpacingTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LETTER_SPACING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LETTER_SPACING_DEFAULT_VALUE) << "Default value for attribute 'letterSpacing'";
}

/*
 * @tc.name: setLetterSpacingTestLetterSpacingValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setLetterSpacingTestLetterSpacingValidValues, TestSize.Level1)
{
    Opt_Union_Number_String initValueLetterSpacing;

    // Initial setup
    initValueLetterSpacing =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueLetterSpacing](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String& value) {
        Opt_Union_Number_String inputValueLetterSpacing = initValueLetterSpacing;

        inputValueLetterSpacing = value;
        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LETTER_SPACING_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLetterSpacing, attribute: letterSpacing";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonPercValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setLetterSpacingTestLetterSpacingInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLetterSpacingTestLetterSpacingInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_String initValueLetterSpacing;

    // Initial setup
    initValueLetterSpacing =
        ArkUnion<Opt_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueLetterSpacing](const std::string& input, const Opt_Union_Number_String& value) {
        Opt_Union_Number_String inputValueLetterSpacing = initValueLetterSpacing;

        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        inputValueLetterSpacing = value;
        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LETTER_SPACING_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LETTER_SPACING_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLetterSpacing, attribute: letterSpacing";
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
 * @tc.name: setTextCaseTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextCaseTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_CASE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_CASE_DEFAULT_VALUE) << "Default value for attribute 'textCase'";
}

/*
 * @tc.name: setTextCaseTestTextCaseValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextCaseTestTextCaseValidValues, TestSize.Level1)
{
    Opt_TextCase initValueTextCase;

    // Initial setup
    initValueTextCase = ArkValue<Opt_TextCase>(std::get<1>(Fixtures::testFixtureEnumTextCaseValidValues[0]));

    auto checkValue = [this, &initValueTextCase](
                          const std::string& input, const std::string& expectedStr, const Opt_TextCase& value) {
        Opt_TextCase inputValueTextCase = initValueTextCase;

        inputValueTextCase = value;
        modifier_->setTextCase(node_, &inputValueTextCase);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_CASE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextCase, attribute: textCase";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextCaseValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextCase>(value));
    }
}

/*
 * @tc.name: setTextCaseTestTextCaseInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextCaseTestTextCaseInvalidValues, TestSize.Level1)
{
    Opt_TextCase initValueTextCase;

    // Initial setup
    initValueTextCase = ArkValue<Opt_TextCase>(std::get<1>(Fixtures::testFixtureEnumTextCaseValidValues[0]));

    auto checkValue = [this, &initValueTextCase](const std::string& input, const Opt_TextCase& value) {
        Opt_TextCase inputValueTextCase = initValueTextCase;

        modifier_->setTextCase(node_, &inputValueTextCase);
        inputValueTextCase = value;
        modifier_->setTextCase(node_, &inputValueTextCase);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_CASE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_CASE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextCase, attribute: textCase";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextCaseInvalidValues) {
        checkValue(input, ArkValue<Opt_TextCase>(value));
    }
}

/*
 * @tc.name: setBaselineOffsetTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setBaselineOffsetTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BASELINE_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BASELINE_OFFSET_DEFAULT_VALUE) << "Default value for attribute 'baselineOffset'";
}

/*
 * @tc.name: setBaselineOffsetTestBaselineOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setBaselineOffsetTestBaselineOffsetValidValues, TestSize.Level1)
{
    Opt_Union_Number_String initValueBaselineOffset;

    // Initial setup
    initValueBaselineOffset = ArkUnion<Opt_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureBaselineOffsetNumValidValues[0]));

    auto checkValue = [this, &initValueBaselineOffset](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String& value) {
        Opt_Union_Number_String inputValueBaselineOffset = initValueBaselineOffset;

        inputValueBaselineOffset = value;
        modifier_->setBaselineOffset(node_, &inputValueBaselineOffset);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BASELINE_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBaselineOffset, attribute: baselineOffset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBaselineOffsetNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureBaselineOffsetStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setBaselineOffsetTestBaselineOffsetInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setBaselineOffsetTestBaselineOffsetInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_String initValueBaselineOffset;

    // Initial setup
    initValueBaselineOffset = ArkUnion<Opt_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureBaselineOffsetNumValidValues[0]));

    auto checkValue = [this, &initValueBaselineOffset](const std::string& input, const Opt_Union_Number_String& value) {
        Opt_Union_Number_String inputValueBaselineOffset = initValueBaselineOffset;

        modifier_->setBaselineOffset(node_, &inputValueBaselineOffset);
        inputValueBaselineOffset = value;
        modifier_->setBaselineOffset(node_, &inputValueBaselineOffset);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BASELINE_OFFSET_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BASELINE_OFFSET_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBaselineOffset, attribute: baselineOffset";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_String>());
}

/*
 * @tc.name: setCopyOptionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setCopyOptionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE) << "Default value for attribute 'copyOption'";
}

/*
 * @tc.name: setCopyOptionTestCopyOptionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setCopyOptionTestCopyOptionValidValues, TestSize.Level1)
{
    Opt_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = ArkValue<Opt_CopyOptions>(std::get<1>(Fixtures::testFixtureCopyOptionsValidValues[0]));

    auto checkValue = [this, &initValueCopyOption](
                          const std::string& input, const std::string& expectedStr, const Opt_CopyOptions& value) {
        Opt_CopyOptions inputValueCopyOption = initValueCopyOption;

        inputValueCopyOption = value;
        modifier_->setCopyOption(node_, &inputValueCopyOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCopyOption, attribute: copyOption";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureCopyOptionsValidValues) {
        checkValue(input, expected, ArkValue<Opt_CopyOptions>(value));
    }
}

/*
 * @tc.name: setCopyOptionTestCopyOptionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setCopyOptionTestCopyOptionInvalidValues, TestSize.Level1)
{
    Opt_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = ArkValue<Opt_CopyOptions>(std::get<1>(Fixtures::testFixtureCopyOptionsValidValues[0]));

    auto checkValue = [this, &initValueCopyOption](const std::string& input, const Opt_CopyOptions& value) {
        Opt_CopyOptions inputValueCopyOption = initValueCopyOption;

        modifier_->setCopyOption(node_, &inputValueCopyOption);
        inputValueCopyOption = value;
        modifier_->setCopyOption(node_, &inputValueCopyOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCopyOption, attribute: copyOption";
    };

    for (auto& [input, value] : Fixtures::testFixtureCopyOptionsInvalidValues) {
        checkValue(input, ArkValue<Opt_CopyOptions>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_CopyOptions>());
}

/*
 * @tc.name: setDraggableTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setDraggableTestPlaceholder, TestSize.Level1)
{
    FAIL() << "This is placeholder to have disabled test";
}

/*
 * @tc.name: setTextShadowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTextShadow =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.radius'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.type'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.color'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.offsetX'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.offsetY'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow.ShadowOptions.fill'";
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextShadowTestTextShadowShadowOptionsRadiusValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).radius = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.radius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowRadiusNumberValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowRadiusResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextShadowTestTextShadowShadowOptionsRadiusInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Ark_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).radius = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.radius";
    };

    for (auto& [input, value] : Fixtures::testFixtureShadowRadiusNumberInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureShadowRadiusResInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextShadowTestTextShadowShadowOptionsTypeValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const std::string& expectedStr, const Opt_ShadowType& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).type = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ShadowType>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextShadowTestTextShadowShadowOptionsTypeInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_ShadowType& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).type = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.type";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ShadowType>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextShadowTestTextShadowShadowOptionsColorValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Color_String_Resource_ColoringStrategy& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).color = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDummyColoringStrategyValidValues) {
        checkValue(
            input, expected, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextShadowTestTextShadowShadowOptionsColorInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const Opt_Union_Color_String_Resource_ColoringStrategy& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).color = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Color_String_Resource_ColoringStrategy>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetXValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetX = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetX";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetNumberValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetXInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetX = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetX";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetYValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetY = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetY";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetNumberValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetYInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetY = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetY";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsFillValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsFillValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).fill = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.fill";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsFillInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsFillInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Boolean& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).fill = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.fill";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setHeightAdaptivePolicyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setHeightAdaptivePolicyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE) <<
        "Default value for attribute 'heightAdaptivePolicy'";
}

/*
 * @tc.name: setHeightAdaptivePolicyTestHeightAdaptivePolicyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setHeightAdaptivePolicyTestHeightAdaptivePolicyValidValues, TestSize.Level1)
{
    Opt_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));

    auto checkValue = [this, &initValueHeightAdaptivePolicy](const std::string& input, const std::string& expectedStr,
                          const Opt_TextHeightAdaptivePolicy& value) {
        Opt_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;

        inputValueHeightAdaptivePolicy = value;
        modifier_->setHeightAdaptivePolicy(node_, &inputValueHeightAdaptivePolicy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHeightAdaptivePolicy, attribute: heightAdaptivePolicy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextHeightAdaptivePolicy>(value));
    }
}

/*
 * @tc.name: setHeightAdaptivePolicyTestHeightAdaptivePolicyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setHeightAdaptivePolicyTestHeightAdaptivePolicyInvalidValues, TestSize.Level1)
{
    Opt_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));

    auto checkValue = [this, &initValueHeightAdaptivePolicy](
                          const std::string& input, const Opt_TextHeightAdaptivePolicy& value) {
        Opt_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;

        modifier_->setHeightAdaptivePolicy(node_, &inputValueHeightAdaptivePolicy);
        inputValueHeightAdaptivePolicy = value;
        modifier_->setHeightAdaptivePolicy(node_, &inputValueHeightAdaptivePolicy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setHeightAdaptivePolicy, attribute: heightAdaptivePolicy";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyInvalidValues) {
        checkValue(input, ArkValue<Opt_TextHeightAdaptivePolicy>(value));
    }
}

/*
 * @tc.name: setTextIndentTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextIndentTestPlaceholder, TestSize.Level1)
{
    FAIL() << "This is placeholder to have disabled test";
}

/*
 * @tc.name: setWordBreakTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setWordBreakTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WORD_BREAK_DEFAULT_VALUE) << "Default value for attribute 'wordBreak'";
}

} // namespace OHOS::Ace::NG
