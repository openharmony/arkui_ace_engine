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

#include "text_input_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::TextInput;

/*
 * @tc.name: setTextInputOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setTextInputOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_DEFAULT_VALUE) << "Default value for attribute 'options.placeholder'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_DEFAULT_VALUE) << "Default value for attribute 'options.text'";
}

/*
 * @tc.name: setTextInputOptionsTestOptionsPlaceholderValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextInputOptionsTestOptionsPlaceholderValidValues, TestSize.Level1)
{
    Opt_TextInputOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).placeholder =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).text =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Opt_TextInputOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).placeholder = value;
        modifier_->setTextInputOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextInputOptions, attribute: options.placeholder";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setTextInputOptionsTestOptionsPlaceholderInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextInputOptionsTestOptionsPlaceholderInvalidValues, TestSize.Level1)
{
    Opt_TextInputOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).placeholder =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).text =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_ResourceStr& value) {
        Opt_TextInputOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).placeholder = value;
        modifier_->setTextInputOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextInputOptions, attribute: options.placeholder";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceStr>());
}

/*
 * @tc.name: setTextInputOptionsTestOptionsTextValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextInputOptionsTestOptionsTextValidValues, TestSize.Level1)
{
    Opt_TextInputOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).placeholder =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).text =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_TextInputOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).text = value;
        modifier_->setTextInputOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextInputOptions, attribute: options.text";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setTextInputOptionsTestOptionsTextInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextInputOptionsTestOptionsTextInvalidValues, TestSize.Level1)
{
    Opt_TextInputOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).placeholder =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).text =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_TextInputOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).text = value;
        modifier_->setTextInputOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextInputOptions, attribute: options.text";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) << "Default value for attribute 'type'";
}

/*
 * @tc.name: setTypeTestTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setTypeTestTypeValidValues, TestSize.Level1)
{
    Opt_InputType initValueType;

    // Initial setup
    initValueType = ArkValue<Opt_InputType>(std::get<1>(Fixtures::testFixtureEnumInputTypeValidValues[0]));

    auto checkValue = [this, &initValueType](
                          const std::string& input, const std::string& expectedStr, const Opt_InputType& value) {
        Opt_InputType inputValueType = initValueType;

        inputValueType = value;
        modifier_->setType(node_, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setType, attribute: type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumInputTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_InputType>(value));
    }
}

/*
 * @tc.name: setTypeTestTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTypeTestTypeInvalidValues, TestSize.Level1)
{
    Opt_InputType initValueType;

    // Initial setup
    initValueType = ArkValue<Opt_InputType>(std::get<1>(Fixtures::testFixtureEnumInputTypeValidValues[0]));

    auto checkValue = [this, &initValueType](const std::string& input, const Opt_InputType& value) {
        Opt_InputType inputValueType = initValueType;

        modifier_->setType(node_, &inputValueType);
        inputValueType = value;
        modifier_->setType(node_, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setType, attribute: type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumInputTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_InputType>(value));
    }
}

/*
 * @tc.name: setContentTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setContentTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_TYPE_DEFAULT_VALUE) << "Default value for attribute 'contentType'";
}

/*
 * @tc.name: setContentTypeTestContentTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setContentTypeTestContentTypeValidValues, TestSize.Level1)
{
    Opt_ContentType initValueContentType;

    // Initial setup
    initValueContentType =
        ArkValue<Opt_ContentType>(std::get<1>(Fixtures::testFixtureTextInputContentTypeValidValues[0]));

    auto checkValue = [this, &initValueContentType](
                          const std::string& input, const std::string& expectedStr, const Opt_ContentType& value) {
        Opt_ContentType inputValueContentType = initValueContentType;

        inputValueContentType = value;
        modifier_->setContentType(node_, &inputValueContentType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setContentType, attribute: contentType";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputContentTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ContentType>(value));
    }
}

/*
 * @tc.name: setContentTypeTestContentTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setContentTypeTestContentTypeInvalidValues, TestSize.Level1)
{
    Opt_ContentType initValueContentType;

    // Initial setup
    initValueContentType =
        ArkValue<Opt_ContentType>(std::get<1>(Fixtures::testFixtureTextInputContentTypeValidValues[0]));

    auto checkValue = [this, &initValueContentType](const std::string& input, const Opt_ContentType& value) {
        Opt_ContentType inputValueContentType = initValueContentType;

        modifier_->setContentType(node_, &inputValueContentType);
        inputValueContentType = value;
        modifier_->setContentType(node_, &inputValueContentType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setContentType, attribute: contentType";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputContentTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ContentType>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ContentType>());
}

/*
 * @tc.name: setPlaceholderColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPlaceholderColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_COLOR_DEFAULT_VALUE) << "Default value for attribute 'placeholderColor'";
}

/*
 * @tc.name: setPlaceholderColorTestPlaceholderColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setPlaceholderColorTestPlaceholderColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValuePlaceholderColor;

    // Initial setup
    initValuePlaceholderColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValuePlaceholderColor = initValuePlaceholderColor;

        inputValuePlaceholderColor = value;
        modifier_->setPlaceholderColor(node_, &inputValuePlaceholderColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPlaceholderColor, attribute: placeholderColor";
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
 * @tc.name: setPlaceholderColorTestPlaceholderColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPlaceholderColorTestPlaceholderColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValuePlaceholderColor;

    // Initial setup
    initValuePlaceholderColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValuePlaceholderColor = initValuePlaceholderColor;

        modifier_->setPlaceholderColor(node_, &inputValuePlaceholderColor);
        inputValuePlaceholderColor = value;
        modifier_->setPlaceholderColor(node_, &inputValuePlaceholderColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPlaceholderColor, attribute: placeholderColor";
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
 * @tc.name: setTextOverflowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextOverflowTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_OVERFLOW_DEFAULT_VALUE) << "Default value for attribute 'textOverflow'";
}

/*
 * @tc.name: setTextOverflowTestTextOverflowValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setTextOverflowTestTextOverflowValidValues, TestSize.Level1)
{
    Opt_TextOverflow initValueTextOverflow;

    // Initial setup
    initValueTextOverflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));

    auto checkValue = [this, &initValueTextOverflow](
                          const std::string& input, const std::string& expectedStr, const Opt_TextOverflow& value) {
        Opt_TextOverflow inputValueTextOverflow = initValueTextOverflow;

        inputValueTextOverflow = value;
        modifier_->setTextOverflow(node_, &inputValueTextOverflow);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextOverflow, attribute: textOverflow";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextOverflowValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextOverflow>(value));
    }
}

/*
 * @tc.name: setTextOverflowTestTextOverflowInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setTextOverflowTestTextOverflowInvalidValues, TestSize.Level1)
{
    Opt_TextOverflow initValueTextOverflow;

    // Initial setup
    initValueTextOverflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));

    auto checkValue = [this, &initValueTextOverflow](const std::string& input, const Opt_TextOverflow& value) {
        Opt_TextOverflow inputValueTextOverflow = initValueTextOverflow;

        modifier_->setTextOverflow(node_, &inputValueTextOverflow);
        inputValueTextOverflow = value;
        modifier_->setTextOverflow(node_, &inputValueTextOverflow);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_OVERFLOW_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextOverflow, attribute: textOverflow";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextOverflowInvalidValues) {
        checkValue(input, ArkValue<Opt_TextOverflow>(value));
    }
}

/*
 * @tc.name: setTextIndentTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextIndentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_INDENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_INDENT_DEFAULT_VALUE) << "Default value for attribute 'textIndent'";
}

/*
 * @tc.name: setTextIndentTestTextIndentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextIndentTestTextIndentValidValues, TestSize.Level1)
{
    Opt_Dimension initValueTextIndent;

    // Initial setup
    initValueTextIndent =
        ArkUnion<Opt_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueTextIndent](
                          const std::string& input, const std::string& expectedStr, const Opt_Dimension& value) {
        Opt_Dimension inputValueTextIndent = initValueTextIndent;

        inputValueTextIndent = value;
        modifier_->setTextIndent(node_, &inputValueTextIndent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_INDENT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextIndent, attribute: textIndent";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Dimension, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Dimension, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Dimension, Ark_String>(value));
    }
}

/*
 * @tc.name: setTextIndentTestTextIndentInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextIndentTestTextIndentInvalidValues, TestSize.Level1)
{
    Opt_Dimension initValueTextIndent;

    // Initial setup
    initValueTextIndent =
        ArkUnion<Opt_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueTextIndent](const std::string& input, const Opt_Dimension& value) {
        Opt_Dimension inputValueTextIndent = initValueTextIndent;

        modifier_->setTextIndent(node_, &inputValueTextIndent);
        inputValueTextIndent = value;
        modifier_->setTextIndent(node_, &inputValueTextIndent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_INDENT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_INDENT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextIndent, attribute: textIndent";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Dimension, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Dimension>());
}

/*
 * @tc.name: setPlaceholderFontTestPlaceholderFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPlaceholderFontTestPlaceholderFontSizeValidValues, TestSize.Level1)
{
    Opt_Font initValuePlaceholderFont;

    // Initial setup
    WriteTo(initValuePlaceholderFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValuePlaceholderFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValuePlaceholderFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValuePlaceholderFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        WriteTo(inputValuePlaceholderFont).size = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.size";
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
 * @tc.name: setPlaceholderFontTestPlaceholderFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPlaceholderFontTestPlaceholderFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Font initValuePlaceholderFont;

    // Initial setup
    WriteTo(initValuePlaceholderFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValuePlaceholderFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValuePlaceholderFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValuePlaceholderFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](const std::string& input, const Opt_Length& value) {
        Opt_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        WriteTo(inputValuePlaceholderFont).size = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_FONT_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.size";
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
 * @tc.name: setPlaceholderFontTestPlaceholderFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPlaceholderFontTestPlaceholderFontStyleValidValues, TestSize.Level1)
{
    Opt_Font initValuePlaceholderFont;

    // Initial setup
    WriteTo(initValuePlaceholderFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValuePlaceholderFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValuePlaceholderFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValuePlaceholderFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        WriteTo(inputValuePlaceholderFont).style = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setPlaceholderFontTestPlaceholderFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPlaceholderFontTestPlaceholderFontStyleInvalidValues, TestSize.Level1)
{
    Opt_Font initValuePlaceholderFont;

    // Initial setup
    WriteTo(initValuePlaceholderFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValuePlaceholderFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValuePlaceholderFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValuePlaceholderFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValuePlaceholderFont](const std::string& input, const Opt_FontStyle& value) {
        Opt_Font inputValuePlaceholderFont = initValuePlaceholderFont;

        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        WriteTo(inputValuePlaceholderFont).style = value;
        modifier_->setPlaceholderFont(node_, &inputValuePlaceholderFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultPlaceholderFont =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PLACEHOLDER_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPlaceholderFont, ATTRIBUTE_PLACEHOLDER_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PLACEHOLDER_FONT_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPlaceholderFont, attribute: placeholderFont.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setEnterKeyTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnterKeyTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENTER_KEY_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENTER_KEY_TYPE_DEFAULT_VALUE) << "Default value for attribute 'enterKeyType'";
}

/*
 * @tc.name: setEnterKeyTypeTestEnterKeyTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setEnterKeyTypeTestEnterKeyTypeValidValues, TestSize.Level1)
{
    Opt_EnterKeyType initValueEnterKeyType;

    // Initial setup
    initValueEnterKeyType =
        ArkValue<Opt_EnterKeyType>(std::get<1>(Fixtures::testFixtureEnumEnterKeyTypeValidValues[0]));

    auto checkValue = [this, &initValueEnterKeyType](
                          const std::string& input, const std::string& expectedStr, const Opt_EnterKeyType& value) {
        Opt_EnterKeyType inputValueEnterKeyType = initValueEnterKeyType;

        inputValueEnterKeyType = value;
        modifier_->setEnterKeyType(node_, &inputValueEnterKeyType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENTER_KEY_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnterKeyType, attribute: enterKeyType";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumEnterKeyTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_EnterKeyType>(value));
    }
}

/*
 * @tc.name: setEnterKeyTypeTestEnterKeyTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnterKeyTypeTestEnterKeyTypeInvalidValues, TestSize.Level1)
{
    Opt_EnterKeyType initValueEnterKeyType;

    // Initial setup
    initValueEnterKeyType =
        ArkValue<Opt_EnterKeyType>(std::get<1>(Fixtures::testFixtureEnumEnterKeyTypeValidValues[0]));

    auto checkValue = [this, &initValueEnterKeyType](const std::string& input, const Opt_EnterKeyType& value) {
        Opt_EnterKeyType inputValueEnterKeyType = initValueEnterKeyType;

        modifier_->setEnterKeyType(node_, &inputValueEnterKeyType);
        inputValueEnterKeyType = value;
        modifier_->setEnterKeyType(node_, &inputValueEnterKeyType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENTER_KEY_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENTER_KEY_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnterKeyType, attribute: enterKeyType";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumEnterKeyTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_EnterKeyType>(value));
    }
}

/*
 * @tc.name: setCaretColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCaretColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CARET_COLOR_DEFAULT_VALUE) << "Default value for attribute 'caretColor'";
}

/*
 * @tc.name: setCaretColorTestCaretColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCaretColorTestCaretColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueCaretColor;

    // Initial setup
    initValueCaretColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueCaretColor = initValueCaretColor;

        inputValueCaretColor = value;
        modifier_->setCaretColor(node_, &inputValueCaretColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCaretColor, attribute: caretColor";
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
 * @tc.name: setCaretColorTestCaretColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCaretColorTestCaretColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueCaretColor;

    // Initial setup
    initValueCaretColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueCaretColor = initValueCaretColor;

        modifier_->setCaretColor(node_, &inputValueCaretColor);
        inputValueCaretColor = value;
        modifier_->setCaretColor(node_, &inputValueCaretColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CARET_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCaretColor, attribute: caretColor";
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
 * @tc.name: setMaxLengthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMaxLengthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LENGTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE) << "Default value for attribute 'maxLength'";
}

/*
 * @tc.name: setMaxLengthTestMaxLengthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMaxLengthTestMaxLengthValidValues, TestSize.Level1)
{
    Opt_Number initValueMaxLength;

    // Initial setup
    initValueMaxLength = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMaxLengthValidValues[0]));

    auto checkValue = [this, &initValueMaxLength](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueMaxLength = initValueMaxLength;

        inputValueMaxLength = value;
        modifier_->setMaxLength(node_, &inputValueMaxLength);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LENGTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxLength, attribute: maxLength";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextMaxLengthValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setMaxLengthTestMaxLengthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMaxLengthTestMaxLengthInvalidValues, TestSize.Level1)
{
    Opt_Number initValueMaxLength;

    // Initial setup
    initValueMaxLength = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMaxLengthValidValues[0]));

    auto checkValue = [this, &initValueMaxLength](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueMaxLength = initValueMaxLength;

        modifier_->setMaxLength(node_, &inputValueMaxLength);
        inputValueMaxLength = value;
        modifier_->setMaxLength(node_, &inputValueMaxLength);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LENGTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LENGTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxLength, attribute: maxLength";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextInputModifierTest, setFontColorTestFontColorValidValues, TestSize.Level1)
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
HWTEST_F(TextInputModifierTest, setFontColorTestFontColorInvalidValues, TestSize.Level1)
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
HWTEST_F(TextInputModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextInputModifierTest, setFontSizeTestFontSizeValidValues, TestSize.Level1)
{
    Opt_Length initValueFontSize;

    // Initial setup
    initValueFontSize =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueFontSize = initValueFontSize;

        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
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
 * @tc.name: setFontSizeTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Length initValueFontSize;

    // Initial setup
    initValueFontSize =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueFontSize = initValueFontSize;

        modifier_->setFontSize(node_, &inputValueFontSize);
        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
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
 * @tc.name: setFontStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextInputModifierTest, setFontStyleTestFontStyleValidValues, TestSize.Level1)
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
HWTEST_F(TextInputModifierTest, setFontStyleTestFontStyleInvalidValues, TestSize.Level1)
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
 * @tc.name: setFontWeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setFontWeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) << "Default value for attribute 'fontWeight'";
}

/*
 * @tc.name: setFontWeightTestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setFontWeightTestFontWeightValidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_ResourceStr initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_FontWeight_ResourceStr& value) {
        Opt_Union_Number_FontWeight_ResourceStr inputValueFontWeight = initValueFontWeight;

        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightResStringsValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
}

/*
 * @tc.name: setFontWeightTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setFontWeightTestFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_ResourceStr initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](
                          const std::string& input, const Opt_Union_Number_FontWeight_ResourceStr& value) {
        Opt_Union_Number_FontWeight_ResourceStr inputValueFontWeight = initValueFontWeight;

        modifier_->setFontWeight(node_, &inputValueFontWeight);
        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_ResourceStr>(
                              ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightResStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_ResourceStr>(
                              ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_FontWeight_ResourceStr>());
}

/*
 * @tc.name: setFontFamilyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontFamilyTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextInputModifierTest, DISABLED_setFontFamilyTestFontFamilyValidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueFontFamily;

    // Initial setup
    initValueFontFamily =
        ArkUnion<Opt_ResourceStr, Ark_Resource>(std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueFontFamily = initValueFontFamily;

        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontFamilyTestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontFamilyTestFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueFontFamily;

    // Initial setup
    initValueFontFamily =
        ArkUnion<Opt_ResourceStr, Ark_Resource>(std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](const std::string& input, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueFontFamily = initValueFontFamily;

        modifier_->setFontFamily(node_, &inputValueFontFamily);
        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFamilyResourceInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontFamilyStringInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceStr>());
}

/*
 * @tc.name: setCopyOptionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCopyOptionTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextInputModifierTest, DISABLED_setCopyOptionTestCopyOptionValidValues, TestSize.Level1)
{
    Opt_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = ArkValue<Opt_CopyOptions>(std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]));

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

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCopyOptionsValidValues) {
        checkValue(input, expected, ArkValue<Opt_CopyOptions>(value));
    }
}

/*
 * @tc.name: setCopyOptionTestCopyOptionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCopyOptionTestCopyOptionInvalidValues, TestSize.Level1)
{
    Opt_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = ArkValue<Opt_CopyOptions>(std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]));

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

    for (auto& [input, value] : Fixtures::testFixtureEnumCopyOptionsInvalidValues) {
        checkValue(input, ArkValue<Opt_CopyOptions>(value));
    }
}

/*
 * @tc.name: setShowPasswordIconTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowPasswordIconTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_ICON_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_PASSWORD_ICON_DEFAULT_VALUE) <<
        "Default value for attribute 'showPasswordIcon'";
}

/*
 * @tc.name: setShowPasswordIconTestShowPasswordIconValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowPasswordIconTestShowPasswordIconValidValues, TestSize.Level1)
{
    Opt_Boolean initValueShowPasswordIcon;

    // Initial setup
    initValueShowPasswordIcon = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueShowPasswordIcon](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueShowPasswordIcon = initValueShowPasswordIcon;

        inputValueShowPasswordIcon = value;
        modifier_->setShowPasswordIcon(node_, &inputValueShowPasswordIcon);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_ICON_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowPasswordIcon, attribute: showPasswordIcon";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setShowPasswordIconTestShowPasswordIconInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowPasswordIconTestShowPasswordIconInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueShowPasswordIcon;

    // Initial setup
    initValueShowPasswordIcon = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueShowPasswordIcon](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueShowPasswordIcon = initValueShowPasswordIcon;

        modifier_->setShowPasswordIcon(node_, &inputValueShowPasswordIcon);
        inputValueShowPasswordIcon = value;
        modifier_->setShowPasswordIcon(node_, &inputValueShowPasswordIcon);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_ICON_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_PASSWORD_ICON_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShowPasswordIcon, attribute: showPasswordIcon";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setTextAlignTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextAlignTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextInputModifierTest, DISABLED_setTextAlignTestTextAlignValidValues, TestSize.Level1)
{
    Opt_TextAlign initValueTextAlign;

    // Initial setup
    initValueTextAlign = ArkValue<Opt_TextAlign>(std::get<1>(Fixtures::testFixtureEnumTextAlignValidValues[0]));

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

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextAlignValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextAlign>(value));
    }
}

/*
 * @tc.name: setTextAlignTestTextAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextAlignTestTextAlignInvalidValues, TestSize.Level1)
{
    Opt_TextAlign initValueTextAlign;

    // Initial setup
    initValueTextAlign = ArkValue<Opt_TextAlign>(std::get<1>(Fixtures::testFixtureEnumTextAlignValidValues[0]));

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

    for (auto& [input, value] : Fixtures::testFixtureEnumTextAlignInvalidValues) {
        checkValue(input, ArkValue<Opt_TextAlign>(value));
    }
}

/*
 * @tc.name: setStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_DEFAULT_VALUE) << "Default value for attribute 'style'";
}

/*
 * @tc.name: setStyleTestStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setStyleTestStyleValidValues, TestSize.Level1)
{
    Opt_Union_TextInputStyle_TextContentStyle initValueStyle;

    // Initial setup
    initValueStyle = ArkUnion<Opt_Union_TextInputStyle_TextContentStyle, Ark_TextInputStyle>(
        std::get<1>(Fixtures::testFixtureEnumTextInputStyleValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_TextInputStyle_TextContentStyle& value) {
        Opt_Union_TextInputStyle_TextContentStyle inputValueStyle = initValueStyle;

        inputValueStyle = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setStyle, attribute: style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextInputStyleValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_TextInputStyle_TextContentStyle, Ark_TextInputStyle>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputTextContentStyleValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_TextInputStyle_TextContentStyle, Ark_TextContentStyle>(value));
    }
}

/*
 * @tc.name: setStyleTestStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setStyleTestStyleInvalidValues, TestSize.Level1)
{
    Opt_Union_TextInputStyle_TextContentStyle initValueStyle;

    // Initial setup
    initValueStyle = ArkUnion<Opt_Union_TextInputStyle_TextContentStyle, Ark_TextInputStyle>(
        std::get<1>(Fixtures::testFixtureEnumTextInputStyleValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const Opt_Union_TextInputStyle_TextContentStyle& value) {
        Opt_Union_TextInputStyle_TextContentStyle inputValueStyle = initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        inputValueStyle = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputTextContentStyleInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_TextInputStyle_TextContentStyle, Ark_TextContentStyle>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumTextInputStyleInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_TextInputStyle_TextContentStyle, Ark_TextInputStyle>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_TextInputStyle_TextContentStyle, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_TextInputStyle_TextContentStyle>());
}

/*
 * @tc.name: setCaretStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCaretStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultCaretStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CARET_STYLE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CARET_STYLE_I_WIDTH_DEFAULT_VALUE) <<
        "Default value for attribute 'caretStyle.width'";

    resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CARET_STYLE_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'caretStyle.color'";
}

/*
 * @tc.name: setCaretStyleTestCaretStyleWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCaretStyleTestCaretStyleWidthValidValues, TestSize.Level1)
{
    Opt_CaretStyle initValueCaretStyle;

    // Initial setup
    WriteTo(initValueCaretStyle).width =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueCaretStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_CaretStyle inputValueCaretStyle = initValueCaretStyle;

        WriteTo(inputValueCaretStyle).width = value;
        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CARET_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCaretStyle, attribute: caretStyle.width";
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
 * @tc.name: setCaretStyleTestCaretStyleWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCaretStyleTestCaretStyleWidthInvalidValues, TestSize.Level1)
{
    Opt_CaretStyle initValueCaretStyle;

    // Initial setup
    WriteTo(initValueCaretStyle).width =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueCaretStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretStyle](const std::string& input, const Opt_Length& value) {
        Opt_CaretStyle inputValueCaretStyle = initValueCaretStyle;

        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        WriteTo(inputValueCaretStyle).width = value;
        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CARET_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CARET_STYLE_I_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCaretStyle, attribute: caretStyle.width";
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
 * @tc.name: setCaretStyleTestCaretStyleColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCaretStyleTestCaretStyleColorValidValues, TestSize.Level1)
{
    Opt_CaretStyle initValueCaretStyle;

    // Initial setup
    WriteTo(initValueCaretStyle).width =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueCaretStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_CaretStyle inputValueCaretStyle = initValueCaretStyle;

        WriteTo(inputValueCaretStyle).color = value;
        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CARET_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCaretStyle, attribute: caretStyle.color";
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
 * @tc.name: setCaretStyleTestCaretStyleColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCaretStyleTestCaretStyleColorInvalidValues, TestSize.Level1)
{
    Opt_CaretStyle initValueCaretStyle;

    // Initial setup
    WriteTo(initValueCaretStyle).width =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueCaretStyle).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretStyle](const std::string& input, const Opt_ResourceColor& value) {
        Opt_CaretStyle inputValueCaretStyle = initValueCaretStyle;

        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        WriteTo(inputValueCaretStyle).color = value;
        modifier_->setCaretStyle(node_, &inputValueCaretStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CARET_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCaretStyle, ATTRIBUTE_CARET_STYLE_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CARET_STYLE_I_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCaretStyle, attribute: caretStyle.color";
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
 * @tc.name: setSelectedBackgroundColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectedBackgroundColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'selectedBackgroundColor'";
}

/*
 * @tc.name: setSelectedBackgroundColorTestSelectedBackgroundColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectedBackgroundColorTestSelectedBackgroundColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedBackgroundColor;

    // Initial setup
    initValueSelectedBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsAlpha20EnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedBackgroundColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedBackgroundColor = initValueSelectedBackgroundColor;

        inputValueSelectedBackgroundColor = value;
        modifier_->setSelectedBackgroundColor(node_, &inputValueSelectedBackgroundColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setSelectedBackgroundColor, attribute: selectedBackgroundColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsAlpha20EnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsAlpha20NumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsAlpha20ResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsAlpha20StrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setSelectedBackgroundColorTestSelectedBackgroundColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectedBackgroundColorTestSelectedBackgroundColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedBackgroundColor;

    // Initial setup
    initValueSelectedBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsAlpha20EnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedBackgroundColor](
                          const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedBackgroundColor = initValueSelectedBackgroundColor;

        modifier_->setSelectedBackgroundColor(node_, &inputValueSelectedBackgroundColor);
        inputValueSelectedBackgroundColor = value;
        modifier_->setSelectedBackgroundColor(node_, &inputValueSelectedBackgroundColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setSelectedBackgroundColor, attribute: selectedBackgroundColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsAlpha20EnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsAlpha20StrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setCaretPositionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCaretPositionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_POSITION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CARET_POSITION_DEFAULT_VALUE) << "Default value for attribute 'caretPosition'";
}

/*
 * @tc.name: setCaretPositionTestCaretPositionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCaretPositionTestCaretPositionValidValues, TestSize.Level1)
{
    Opt_Number initValueCaretPosition;

    // Initial setup
    initValueCaretPosition = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegValidValues[0]));

    auto checkValue = [this, &initValueCaretPosition](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueCaretPosition = initValueCaretPosition;

        inputValueCaretPosition = value;
        modifier_->setCaretPosition(node_, &inputValueCaretPosition);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_POSITION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCaretPosition, attribute: caretPosition";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setCaretPositionTestCaretPositionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCaretPositionTestCaretPositionInvalidValues, TestSize.Level1)
{
    Opt_Number initValueCaretPosition;

    // Initial setup
    initValueCaretPosition = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegValidValues[0]));

    auto checkValue = [this, &initValueCaretPosition](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueCaretPosition = initValueCaretPosition;

        modifier_->setCaretPosition(node_, &inputValueCaretPosition);
        inputValueCaretPosition = value;
        modifier_->setCaretPosition(node_, &inputValueCaretPosition);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_POSITION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CARET_POSITION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCaretPosition, attribute: caretPosition";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberNonNegInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setEnableKeyboardOnFocusTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setEnableKeyboardOnFocusTestPlaceholder, TestSize.Level1)
{
    FAIL() << "This is placeholder to have disabled test";
}

/*
 * @tc.name: setPasswordIconTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPasswordIconTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultPasswordIcon =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PASSWORD_ICON_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_I_ON_ICON_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PASSWORD_ICON_I_ON_ICON_SRC_DEFAULT_VALUE) <<
        "Default value for attribute 'passwordIcon.onIconSrc'";

    resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_I_OFF_ICON_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PASSWORD_ICON_I_OFF_ICON_SRC_DEFAULT_VALUE) <<
        "Default value for attribute 'passwordIcon.offIconSrc'";
}

/*
 * @tc.name: setPasswordIconTestPasswordIconOnIconSrcValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPasswordIconTestPasswordIconOnIconSrcValidValues, TestSize.Level1)
{
    Opt_PasswordIcon initValuePasswordIcon;

    // Initial setup
    WriteTo(initValuePasswordIcon).onIconSrc =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));
    WriteTo(initValuePasswordIcon).offIconSrc =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));

    auto checkValue = [this, &initValuePasswordIcon](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_PasswordIcon inputValuePasswordIcon = initValuePasswordIcon;

        WriteTo(inputValuePasswordIcon).onIconSrc = value;
        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        auto jsonValue = GetJsonValue(node_);
        auto resultPasswordIcon = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PASSWORD_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_I_ON_ICON_SRC_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPasswordIcon, attribute: passwordIcon.onIconSrc";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringNoEmptyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResNoEmptyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setPasswordIconTestPasswordIconOnIconSrcInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPasswordIconTestPasswordIconOnIconSrcInvalidValues, TestSize.Level1)
{
    Opt_PasswordIcon initValuePasswordIcon;

    // Initial setup
    WriteTo(initValuePasswordIcon).onIconSrc =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));
    WriteTo(initValuePasswordIcon).offIconSrc =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));

    auto checkValue = [this, &initValuePasswordIcon](const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_PasswordIcon inputValuePasswordIcon = initValuePasswordIcon;

        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        WriteTo(inputValuePasswordIcon).onIconSrc = value;
        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        auto jsonValue = GetJsonValue(node_);
        auto resultPasswordIcon = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PASSWORD_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_I_ON_ICON_SRC_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PASSWORD_ICON_I_ON_ICON_SRC_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPasswordIcon, attribute: passwordIcon.onIconSrc";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setPasswordIconTestPasswordIconOffIconSrcValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPasswordIconTestPasswordIconOffIconSrcValidValues, TestSize.Level1)
{
    Opt_PasswordIcon initValuePasswordIcon;

    // Initial setup
    WriteTo(initValuePasswordIcon).onIconSrc =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));
    WriteTo(initValuePasswordIcon).offIconSrc =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));

    auto checkValue = [this, &initValuePasswordIcon](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_PasswordIcon inputValuePasswordIcon = initValuePasswordIcon;

        WriteTo(inputValuePasswordIcon).offIconSrc = value;
        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        auto jsonValue = GetJsonValue(node_);
        auto resultPasswordIcon = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PASSWORD_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_I_OFF_ICON_SRC_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPasswordIcon, attribute: passwordIcon.offIconSrc";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringNoEmptyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResNoEmptyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
}

} // namespace OHOS::Ace::NG
