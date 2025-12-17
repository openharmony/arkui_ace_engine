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

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/unittest/capi/modifiers/generated/test_fixtures.h"
#include "test/unittest/capi/modifiers/generated/type_helpers.h"

#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components/text/text_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_ADDRESS_NAME = "address";
const auto ATTRIBUTE_ADDRESS_DEFAULT_VALUE = "";
const auto ATTRIBUTE_CONTENT_NAME = "content";
const auto ATTRIBUTE_CONTENT_DEFAULT_VALUE = "";
const auto ATTRIBUTE_COLOR_NAME = "color";
const auto ATTRIBUTE_COLOR_DEFAULT_VALUE = "#FF007DFF";
} // namespace

class HyperlinkModifierTest : public ModifierTestBase<GENERATED_ArkUIHyperlinkModifier,
                                  &GENERATED_ArkUINodeModifiers::getHyperlinkModifier, GENERATED_ARKUI_HYPERLINK> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<TextTheme>();
        SetupThemeStyle(THEME_PATTERN_HYPERLINK);
        SetupTheme<HyperlinkTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setHyperlinkOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkModifierTest, setHyperlinkOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ADDRESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ADDRESS_DEFAULT_VALUE) << "Default value for attribute 'address'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_DEFAULT_VALUE) << "Default value for attribute 'content'";
}

/*
 * @tc.name: setHyperlinkOptionsTestAddressValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkModifierTest, setHyperlinkOptionsTestAddressValidValues, TestSize.Level1)
{
    // Initial setup
    auto initValueAddress =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));
    auto initValueContent =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueAddress, &initValueContent](const std::string& input,
                          const Opt_Union_String_Resource& value, const std::string& expectedStr) {
        Opt_Union_String_Resource inputValueAddress = initValueAddress;
        Opt_Union_String_Resource inputValueContent = initValueContent;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueAddress = value;
        modifier_->setHyperlinkOptions(node, &inputValueAddress, &inputValueContent);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ADDRESS_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setHyperlinkOptions, attribute: address";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringNoEmptyValidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_String>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResNoEmptyValidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value), expected);
    }
}

/*
 * @tc.name: setHyperlinkOptionsTestAddressInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkModifierTest, setHyperlinkOptionsTestAddressInvalidValues, TestSize.Level1)
{
    // Initial setup
    auto initValueAddress =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));
    auto initValueContent =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueAddress, &initValueContent](
                          const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_Union_String_Resource inputValueAddress = initValueAddress;
        Opt_Union_String_Resource inputValueContent = initValueContent;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueAddress = value;
        modifier_->setHyperlinkOptions(node, &inputValueAddress, &inputValueContent);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ADDRESS_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_ADDRESS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setHyperlinkOptions, attribute: address";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    checkValue("undefined", ArkUnion<Opt_Union_String_Resource>(Ark_Empty()));
}

/*
 * @tc.name: setHyperlinkOptionsTestContentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkModifierTest, setHyperlinkOptionsTestContentValidValues, TestSize.Level1)
{
    // Initial setup
    auto initValueAddress =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));
    auto initValueContent =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueAddress, &initValueContent](const std::string& input,
                          const Opt_Union_String_Resource& value, const std::string& expectedStr) {
        Opt_Union_String_Resource inputValueAddress = initValueAddress;
        Opt_Union_String_Resource inputValueContent = initValueContent;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueContent = value;
        modifier_->setHyperlinkOptions(node, &inputValueAddress, &inputValueContent);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setHyperlinkOptions, attribute: content";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_String>(value), expected.empty() ?
            std::get<2>(Fixtures::testFixtureStringNoEmptyValidValues[0]) : expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value), expected.empty() ?
            std::get<2>(Fixtures::testFixtureStringNoEmptyValidValues[0]) : expected
        );
    }
}

/*
 * @tc.name: setHyperlinkOptionsTestContentInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkModifierTest, setHyperlinkOptionsTestContentInvalidValues, TestSize.Level1)
{
    // Initial setup
    auto initValueAddress =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));
    auto initValueContent =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueAddress, &initValueContent](
                          const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_Union_String_Resource inputValueAddress = initValueAddress;
        Opt_Union_String_Resource inputValueContent = initValueContent;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueContent = value;
        modifier_->setHyperlinkOptions(node, &inputValueAddress, &inputValueContent);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, std::get<2>(Fixtures::testFixtureStringNoEmptyValidValues[0]))
            << "Input value is: " << input << ", method: setHyperlinkOptions, attribute: content";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkModifierTest, DISABLED_setColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COLOR_DEFAULT_VALUE) << "Default value for attribute 'color'";
}

/*
 * @tc.name: setColorTestColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkModifierTest, DISABLED_setColorTestColorValidValues, TestSize.Level1)
{
    Opt_Union_arkui_component_enums_Color_I32_String_Resource initValueColor;

    // Initial setup
    initValueColor =
        ArkUnion<Opt_Union_arkui_component_enums_Color_I32_String_Resource, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueColor](const std::string& input,
                          const Opt_Union_arkui_component_enums_Color_I32_String_Resource& value,
                          const std::string& expectedStr) {
        Opt_Union_arkui_component_enums_Color_I32_String_Resource inputValueColor = initValueColor;

        inputValueColor = value;
        auto optInputValueColor = Converter::ArkValue<Opt_Union_arkui_component_enums_Color_I32_String_Resource>(
            inputValueColor);
        modifier_->setColor(node_, &optInputValueColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setColor, attribute: color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input,
            ArkUnion<Opt_Union_arkui_component_enums_Color_I32_String_Resource, Ark_arkui_component_enums_Color>(
                value), expected);
    }
#ifdef WRONG_FIX
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(
            input, ArkUnion<Opt_Union_arkui_component_enums_Color_I32_String_Resource, Ark_Int32>(value), expected);
    }
#endif
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(
            input, ArkUnion<Opt_Union_arkui_component_enums_Color_I32_String_Resource, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(
            input, ArkUnion<Opt_Union_arkui_component_enums_Color_I32_String_Resource, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setColorTestColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HyperlinkModifierTest, DISABLED_setColorTestColorInvalidValues, TestSize.Level1)
{
    Opt_Union_arkui_component_enums_Color_I32_String_Resource initValueColor;

    // Initial setup
    initValueColor =
        ArkUnion<Opt_Union_arkui_component_enums_Color_I32_String_Resource, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueColor](
        const std::string& input, const Opt_Union_arkui_component_enums_Color_I32_String_Resource& value) {
        Opt_Union_arkui_component_enums_Color_I32_String_Resource inputValueColor = initValueColor;

        auto optInputValueColor = Converter::ArkValue<Opt_Union_arkui_component_enums_Color_I32_String_Resource>(
            inputValueColor);
        modifier_->setColor(node_, &optInputValueColor);
        inputValueColor = value;
        optInputValueColor = Converter::ArkValue<Opt_Union_arkui_component_enums_Color_I32_String_Resource>(
            inputValueColor);
        modifier_->setColor(node_, &optInputValueColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setColor, attribute: color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_arkui_component_enums_Color_I32_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input,
            ArkUnion<Opt_Union_arkui_component_enums_Color_I32_String_Resource, Ark_arkui_component_enums_Color>(
                value));
    }
    // Check invalid union
    checkValue("invalid union",
        ArkUnion<Opt_Union_arkui_component_enums_Color_I32_String_Resource, Ark_Empty>(nullptr));
}
} // namespace OHOS::Ace::NG
