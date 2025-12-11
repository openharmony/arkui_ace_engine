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

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_MIN_NAME = "min";
const auto ATTRIBUTE_MIN_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_COLOR_NAME = "color";
const auto ATTRIBUTE_COLOR_DEFAULT_VALUE = "#00000000";
} // namespace

class BlankModifierTest : public ModifierTestBase<GENERATED_ArkUIBlankModifier,
                              &GENERATED_ArkUINodeModifiers::getBlankModifier, GENERATED_ARKUI_BLANK> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setBlankOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BlankModifierTest, setBlankOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_DEFAULT_VALUE) << "Default value for attribute 'min'";
}

/*
 * @tc.name: setBlankOptionsTestMinValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BlankModifierTest, setBlankOptionsTestMinValidValues, TestSize.Level1)
{
    Opt_Union_Number_String initValueMin;

    // Initial setup
    initValueMin = ArkUnion<Opt_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMin](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_String& value) {
        Opt_Union_Number_String inputValueMin = initValueMin;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueMin = value;
        modifier_->setBlankOptions(node, &inputValueMin);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setBlankOptions, attribute: min";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setBlankOptionsTestMinInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BlankModifierTest, DISABLED_setBlankOptionsTestMinInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_String initValueMin;

    // Initial setup
    initValueMin = ArkUnion<Opt_Union_Number_String, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMin](const std::string& input, const Opt_Union_Number_String& value) {
        Opt_Union_Number_String inputValueMin = initValueMin;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueMin = value;
        modifier_->setBlankOptions(node, &inputValueMin);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBlankOptions, attribute: min";
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
 * @tc.name: setColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BlankModifierTest, setColorTestDefaultValues, TestSize.Level1)
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
HWTEST_F(BlankModifierTest, DISABLED_setColorTestColorValidValues, TestSize.Level1)
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
 * @tc.name: setColorTestColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BlankModifierTest, DISABLED_setColorTestColorInvalidValues, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
