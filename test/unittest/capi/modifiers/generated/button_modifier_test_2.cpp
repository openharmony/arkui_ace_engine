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

#include "button_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Button;
/*
 * @tc.name: setLabelStyleTestLabelStyleFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleFontSizeInvalidValues, TestSize.Level1)
{
    Ark_LabelStyle initValueLabelStyle;

    // Initial setup
    initValueLabelStyle.overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    initValueLabelStyle.maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    initValueLabelStyle.minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(initValueLabelStyle.font).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueLabelStyle.font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueLabelStyle.font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueLabelStyle.font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const Opt_Length& value) {
        Ark_LabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(inputValueLabelStyle.font).size = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
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
    Ark_LabelStyle initValueLabelStyle;

    // Initial setup
    initValueLabelStyle.overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    initValueLabelStyle.maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    initValueLabelStyle.minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(initValueLabelStyle.font).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueLabelStyle.font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueLabelStyle.font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueLabelStyle.font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input,
                          const Opt_Union_FontWeight_Number_String& value, const std::string& expectedStr) {
        Ark_LabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(inputValueLabelStyle.font).weight = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.weight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleFontWeightInvalidValues, TestSize.Level1)
{
    Ark_LabelStyle initValueLabelStyle;

    // Initial setup
    initValueLabelStyle.overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    initValueLabelStyle.maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    initValueLabelStyle.minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(initValueLabelStyle.font).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueLabelStyle.font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueLabelStyle.font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueLabelStyle.font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Ark_LabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(inputValueLabelStyle.font).weight = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_WEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.weight";
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
    Ark_LabelStyle initValueLabelStyle;

    // Initial setup
    initValueLabelStyle.overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    initValueLabelStyle.maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    initValueLabelStyle.minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(initValueLabelStyle.font).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueLabelStyle.font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueLabelStyle.font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueLabelStyle.font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const Opt_Union_String_Resource& value,
                          const std::string& expectedStr) {
        Ark_LabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(inputValueLabelStyle.font).family = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleFontFamilyInvalidValues, TestSize.Level1)
{
    Ark_LabelStyle initValueLabelStyle;

    // Initial setup
    initValueLabelStyle.overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    initValueLabelStyle.maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    initValueLabelStyle.minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(initValueLabelStyle.font).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueLabelStyle.font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueLabelStyle.font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueLabelStyle.font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const Opt_Union_String_Resource& value) {
        Ark_LabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(inputValueLabelStyle.font).family = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_FAMILY_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.family";
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
    Ark_LabelStyle initValueLabelStyle;

    // Initial setup
    initValueLabelStyle.overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    initValueLabelStyle.maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    initValueLabelStyle.minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(initValueLabelStyle.font).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueLabelStyle.font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueLabelStyle.font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueLabelStyle.font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](
                          const std::string& input, const Opt_FontStyle& value, const std::string& expectedStr) {
        Ark_LabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(inputValueLabelStyle.font).style = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value), expected);
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleFontStyleInvalidValues, TestSize.Level1)
{
    Ark_LabelStyle initValueLabelStyle;

    // Initial setup
    initValueLabelStyle.overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    initValueLabelStyle.maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    initValueLabelStyle.minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    initValueLabelStyle.heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(initValueLabelStyle.font).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueLabelStyle.font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueLabelStyle.font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueLabelStyle.font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const Opt_FontStyle& value) {
        Ark_LabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(inputValueLabelStyle.font).style = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_STYLE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.font.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}
} // namespace OHOS::Ace::NG
