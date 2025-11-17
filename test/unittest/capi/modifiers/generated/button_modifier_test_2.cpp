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

#include "button_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Button;
/*
 * @tc.name: setLabelStyleTestLabelStyleFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setLabelStyleTestLabelStyleFontSizeValidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(WriteTo(inputValueLabelStyle).font).size = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleFontSizeInvalidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const Opt_Length& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(WriteTo(inputValueLabelStyle).font).size = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setLabelStyleTestLabelStyleFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleFontWeightValidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_FontWeight_Number_String& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(WriteTo(inputValueLabelStyle).font).weight = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.weight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleFontWeightInvalidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(WriteTo(inputValueLabelStyle).font).weight = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.weight";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_FontWeight_Number_String>());
}

/*
 * @tc.name: setLabelStyleTestLabelStyleFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setLabelStyleTestLabelStyleFontFamilyValidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(WriteTo(inputValueLabelStyle).font).family = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(WriteTo(inputValueLabelStyle).font).family = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.family";
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
 * @tc.name: setLabelStyleTestLabelStyleFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleFontStyleValidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(WriteTo(inputValueLabelStyle).font).style = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleFontStyleInvalidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const Opt_FontStyle& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(WriteTo(inputValueLabelStyle).font).style = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setMinFontScaleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setMinFontScaleTestDefaultValues, TestSize.Level1)
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
HWTEST_F(ButtonModifierTest, DISABLED_setMinFontScaleTestMinFontScaleValidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

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

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setMinFontScaleTestMinFontScaleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setMinFontScaleTestMinFontScaleInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

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

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
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
HWTEST_F(ButtonModifierTest, DISABLED_setMaxFontScaleTestDefaultValues, TestSize.Level1)
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
HWTEST_F(ButtonModifierTest, DISABLED_setMaxFontScaleTestMaxFontScaleValidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

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

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setMaxFontScaleTestMaxFontScaleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setMaxFontScaleTestMaxFontScaleInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

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

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}
} // namespace OHOS::Ace::NG
