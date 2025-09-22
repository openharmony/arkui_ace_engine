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

#include "core/components/qrcode/qrcode_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_COLOR_NAME = "color";
const auto ATTRIBUTE_COLOR_DEFAULT_VALUE = "#FF182431";
const auto ATTRIBUTE_BACKGROUND_COLOR_NAME = "backgroundColor";
const auto ATTRIBUTE_BACKGROUND_COLOR_DEFAULT_VALUE = "#FFFFFFFF";
const auto ATTRIBUTE_CONTENT_OPACITY_NAME = "contentOpacity";
const auto ATTRIBUTE_CONTENT_OPACITY_DEFAULT_VALUE = "1.000000";
} // namespace

class QRCodeModifierTest : public ModifierTestBase<GENERATED_ArkUIQRCodeModifier,
                               &GENERATED_ArkUINodeModifiers::getQRCodeModifier, GENERATED_ARKUI_QRCODE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<QrcodeTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setQRCodeOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, setQRCodeOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) << "Default value for attribute 'value'";
}

/*
 * @tc.name: setQRCodeOptionsTestValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, setQRCodeOptionsTestValueValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueValue;

    // Initial setup
    initValueValue = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueValue](
                          const std::string& input, const std::string& expectedStr, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue = value;
        modifier_->setQRCodeOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setQRCodeOptions, attribute: value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setQRCodeOptionsTestValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, setQRCodeOptionsTestValueInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueValue;

    // Initial setup
    initValueValue = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueValue](const std::string& input, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue = value;
        modifier_->setQRCodeOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setQRCodeOptions, attribute: value";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, DISABLED_setColorTestDefaultValues, TestSize.Level1)
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
HWTEST_F(QRCodeModifierTest, DISABLED_setColorTestColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueColor;

    // Initial setup
    initValueColor = ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueColor = initValueColor;

        inputValueColor = value;
        modifier_->setColor(node_, &inputValueColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setColor, attribute: color";
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
 * @tc.name: setColorTestColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, DISABLED_setColorTestColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueColor;

    // Initial setup
    initValueColor = ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueColor = initValueColor;

        modifier_->setColor(node_, &inputValueColor);
        inputValueColor = value;
        modifier_->setColor(node_, &inputValueColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setColor, attribute: color";
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
 * @tc.name: setBackgroundColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, DISABLED_setBackgroundColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BACKGROUND_COLOR_DEFAULT_VALUE) << "Default value for attribute 'backgroundColor'";
}

/*
 * @tc.name: setBackgroundColorTestBackgroundColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, DISABLED_setBackgroundColorTestBackgroundColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueBackgroundColor;

    // Initial setup
    initValueBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueBackgroundColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueBackgroundColor = initValueBackgroundColor;

        inputValueBackgroundColor = value;
        modifier_->setBackgroundColor(node_, &inputValueBackgroundColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBackgroundColor, attribute: backgroundColor";
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
 * @tc.name: setBackgroundColorTestBackgroundColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, DISABLED_setBackgroundColorTestBackgroundColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueBackgroundColor;

    // Initial setup
    initValueBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueBackgroundColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueBackgroundColor = initValueBackgroundColor;

        modifier_->setBackgroundColor(node_, &inputValueBackgroundColor);
        inputValueBackgroundColor = value;
        modifier_->setBackgroundColor(node_, &inputValueBackgroundColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BACKGROUND_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBackgroundColor, attribute: backgroundColor";
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
 * @tc.name: setContentOpacityTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, DISABLED_setContentOpacityTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_OPACITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_OPACITY_DEFAULT_VALUE) << "Default value for attribute 'contentOpacity'";
}

/*
 * @tc.name: setContentOpacityTestContentOpacityValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, DISABLED_setContentOpacityTestContentOpacityValidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueContentOpacity;

    // Initial setup
    initValueContentOpacity =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureOpacityValidValues[0]));

    auto checkValue = [this, &initValueContentOpacity](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueContentOpacity = initValueContentOpacity;

        inputValueContentOpacity = value;
        modifier_->setContentOpacity(node_, &inputValueContentOpacity);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_OPACITY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setContentOpacity, attribute: contentOpacity";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureOpacityValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureOpacityResourceValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setContentOpacityTestContentOpacityInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, DISABLED_setContentOpacityTestContentOpacityInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueContentOpacity;

    // Initial setup
    initValueContentOpacity =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureOpacityValidValues[0]));

    auto checkValue = [this, &initValueContentOpacity](
                          const std::string& input, const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueContentOpacity = initValueContentOpacity;

        modifier_->setContentOpacity(node_, &inputValueContentOpacity);
        inputValueContentOpacity = value;
        modifier_->setContentOpacity(node_, &inputValueContentOpacity);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_OPACITY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_OPACITY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setContentOpacity, attribute: contentOpacity";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}
} // namespace OHOS::Ace::NG
