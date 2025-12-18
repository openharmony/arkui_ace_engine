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

#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_FONT_NAME = "font";
const auto ATTRIBUTE_DECORATION_NAME = "decoration";
const auto ATTRIBUTE_TEXT_SHADOW_NAME = "textShadow";
const auto ATTRIBUTE_CONTENT_NAME = "content";
const auto ATTRIBUTE_CONTENT_DEFAULT_VALUE = "";
const auto ATTRIBUTE_FONT_I_SIZE_NAME = "size";
const auto ATTRIBUTE_FONT_I_SIZE_DEFAULT_VALUE = "14.00px";
const auto ATTRIBUTE_FONT_I_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_FONT_I_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_FONT_I_FAMILY_NAME = "family";
const auto ATTRIBUTE_FONT_I_FAMILY_DEFAULT_VALUE = "Harmony"
                                                   "OS Sans";
const auto ATTRIBUTE_FONT_I_STYLE_NAME = "style";
const auto ATTRIBUTE_FONT_I_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "14.00px";
const auto ATTRIBUTE_FONT_STYLE_NAME = "fontStyle";
const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_FONT_FAMILY_NAME = "fontFamily";
const auto ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE = "Harmony"
                                                 "OS Sans";
const auto ATTRIBUTE_DECORATION_I_TYPE_NAME = "type";
const auto ATTRIBUTE_DECORATION_I_TYPE_DEFAULT_VALUE = "TextDecorationType.None";
const auto ATTRIBUTE_DECORATION_I_COLOR_NAME = "color";
const auto ATTRIBUTE_DECORATION_I_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_DECORATION_I_STYLE_NAME = "style";
const auto ATTRIBUTE_DECORATION_I_STYLE_DEFAULT_VALUE = "TextDecorationStyle.SOLID";
const auto ATTRIBUTE_TEXT_CASE_NAME = "textCase";
const auto ATTRIBUTE_TEXT_CASE_DEFAULT_VALUE = "TextCase.Normal";
const auto ATTRIBUTE_LINE_HEIGHT_NAME = "lineHeight";
const auto ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME = "radius";
const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE = "0.0";
const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME = "type";
const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE = "ShadowType.COLOR";
const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME = "color";
const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME = "offsetX";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE = "0.0";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME = "offsetY";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE = "0.0";
const auto ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME = "fill";
const auto ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE = "false";
} // namespace

class SpanModifierTest : public ModifierTestBase<GENERATED_ArkUISpanModifier,
                             &GENERATED_ArkUINodeModifiers::getSpanModifier, GENERATED_ARKUI_SPAN> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
    void SetUp() override
    {
        ModifierTestBase::SetUp();
        static auto node = TextModelNG::CreateFrameNode(0, u"");
        static auto pattern = AceType::MakeRefPtr<TextPattern>();
        pattern->AttachToFrameNode(node);
        reinterpret_cast<SpanNode*>(node_)->GetSpanItem()->SetTextPattern(pattern);
    }
};

/*
 * @tc.name: setSpanOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setSpanOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE) << "Default value for attribute 'content'";
}

/*
 * @tc.name: setSpanOptionsTestContentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setSpanOptionsTestContentValidValues, TestSize.Level1)
{
    Ark_Union_String_Resource initValueContent;

    // Initial setup
    initValueContent =
        ArkUnion<Ark_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueContent](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_String_Resource& value) {
        Ark_Union_String_Resource inputValueContent = initValueContent;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueContent = value;
        modifier_->setSpanOptions(node, &inputValueContent);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSpanOptions, attribute: content";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_String_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setSpanOptionsTestContentInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setSpanOptionsTestContentInvalidValues, TestSize.Level1)
{
    Ark_Union_String_Resource initValueContent;

    // Initial setup
    initValueContent =
        ArkUnion<Ark_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueContent](const std::string& input, const Ark_Union_String_Resource& value) {
        Ark_Union_String_Resource inputValueContent = initValueContent;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueContent = value;
        modifier_->setSpanOptions(node, &inputValueContent);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSpanOptions, attribute: content";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_String_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setFontTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_SIZE_DEFAULT_VALUE) << "Default value for attribute 'font.size'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_WEIGHT_DEFAULT_VALUE) << "Default value for attribute 'font.weight'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FAMILY_DEFAULT_VALUE) << "Default value for attribute 'font.family'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_STYLE_DEFAULT_VALUE) << "Default value for attribute 'font.style'";
}

/*
 * @tc.name: setFontTestFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setFontTestFontSizeValidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).size = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont, attribute: font.size";
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
 * @tc.name: setFontTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setFontTestFontSizeInvalidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_Length& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;

        modifier_->setFont(node_, &inputValueFont);
        WriteTo(inputValueFont).size = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.size";
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
 * @tc.name: setFontTestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setFontTestFontWeightValidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_FontWeight_Number_String& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).weight = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont, attribute: font.weight";
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
 * @tc.name: setFontTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setFontTestFontWeightInvalidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;

        modifier_->setFont(node_, &inputValueFont);
        WriteTo(inputValueFont).weight = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.weight";
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
 * @tc.name: setFontTestFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, DISABLED_setFontTestFontFamilyValidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).family = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont, attribute: font.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontTestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setFontTestFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;

        modifier_->setFont(node_, &inputValueFont);
        WriteTo(inputValueFont).family = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.family";
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
 * @tc.name: setFontTestFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setFontTestFontStyleValidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;

        WriteTo(inputValueFont).style = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont, attribute: font.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFontTestFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setFontTestFontStyleInvalidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFont](const std::string& input, const Opt_FontStyle& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;

        modifier_->setFont(node_, &inputValueFont);
        WriteTo(inputValueFont).style = value;
        modifier_->setFont(node_, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SpanModifierTest, DISABLED_setFontColorTestFontColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
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
HWTEST_F(SpanModifierTest, setFontColorTestFontColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
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
HWTEST_F(SpanModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SpanModifierTest, DISABLED_setFontSizeTestFontSizeValidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueFontSize;

    // Initial setup
    initValueFontSize = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_F64_String_Resource& value) {
        Opt_Union_F64_String_Resource inputValueFontSize = initValueFontSize;

        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontSizeTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, DISABLED_setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueFontSize;

    // Initial setup
    initValueFontSize = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](
                          const std::string& input, const Opt_Union_F64_String_Resource& value) {
        Opt_Union_F64_String_Resource inputValueFontSize = initValueFontSize;

        modifier_->setFontSize(node_, &inputValueFontSize);
        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_F64_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_F64_String_Resource>());
}

/*
 * @tc.name: setFontStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SpanModifierTest, setFontStyleTestFontStyleValidValues, TestSize.Level1)
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
HWTEST_F(SpanModifierTest, setFontStyleTestFontStyleInvalidValues, TestSize.Level1)
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
 * @tc.name: setFontFamilyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setFontFamilyTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SpanModifierTest, DISABLED_setFontFamilyTestFontFamilyValidValues, TestSize.Level1)
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
HWTEST_F(SpanModifierTest, setFontFamilyTestFontFamilyInvalidValues, TestSize.Level1)
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
 * @tc.name: setDecorationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setDecorationTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SpanModifierTest, setDecorationTestDecorationTypeValidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
HWTEST_F(SpanModifierTest, setDecorationTestDecorationTypeInvalidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
HWTEST_F(SpanModifierTest, DISABLED_setDecorationTestDecorationColorValidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
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
HWTEST_F(SpanModifierTest, setDecorationTestDecorationColorInvalidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
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
HWTEST_F(SpanModifierTest, setDecorationTestDecorationStyleValidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
HWTEST_F(SpanModifierTest, setDecorationTestDecorationStyleInvalidValues, TestSize.Level1)
{
    Opt_DecorationStyleInterface initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
 * @tc.name: setTextCaseTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setTextCaseTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SpanModifierTest, setTextCaseTestTextCaseValidValues, TestSize.Level1)
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
HWTEST_F(SpanModifierTest, setTextCaseTestTextCaseInvalidValues, TestSize.Level1)
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
 * @tc.name: setLineHeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setLineHeightTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SpanModifierTest, setLineHeightTestLineHeightValidValues, TestSize.Level1)
{
    Opt_Length initValueLineHeight;

    // Initial setup
    initValueLineHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueLineHeight](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueLineHeight = initValueLineHeight;

        inputValueLineHeight = value;
        modifier_->setLineHeight(node_, &inputValueLineHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLineHeight, attribute: lineHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setLineHeightTestLineHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, setLineHeightTestLineHeightInvalidValues, TestSize.Level1)
{
    Opt_Length initValueLineHeight;

    // Initial setup
    initValueLineHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueLineHeight](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueLineHeight = initValueLineHeight;

        modifier_->setLineHeight(node_, &inputValueLineHeight);
        inputValueLineHeight = value;
        modifier_->setLineHeight(node_, &inputValueLineHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLineHeight, attribute: lineHeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setTextShadowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsRadiusValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
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

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsRadiusInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
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

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsTypeValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
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

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumShadowTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ShadowType>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsTypeInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
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

    for (auto& [input, value] : Fixtures::testFixtureEnumShadowTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ShadowType>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsColorValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).color = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumColorValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
                Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureEnumColoringStrategyValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(
                value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_String>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsColorInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
        const std::string& input,
        const Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy& value) {
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

    for (auto& [input, value] : Fixtures::testFixtureEnumColorInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    for (auto& [input, value] : Fixtures::testFixtureEnumColoringStrategyInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_ColoringStrategy>(value));
    }
    // Check invalid union
    checkValue("invalid union",
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsOffsetXValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
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

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsOffsetXInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
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

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
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
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsOffsetYValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(
            Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(
            Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(
            Fixtures::testFixtureNumberAnythingValidValues[0]));
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

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsOffsetYInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(
            Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(
            Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(
            Fixtures::testFixtureNumberAnythingValidValues[0]));
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

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
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
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsFillValidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
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
HWTEST_F(SpanModifierTest, DISABLED_setTextShadowTestTextShadowShadowOptionsFillInvalidValues, TestSize.Level1)
{
    Opt_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(WriteTo(initValueTextShadow)).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
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
} // namespace OHOS::Ace::NG
