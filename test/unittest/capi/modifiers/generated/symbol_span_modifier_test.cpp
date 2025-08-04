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
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "14.00px";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_EFFECT_STRATEGY_NAME = "effectStrategy";
const auto ATTRIBUTE_EFFECT_STRATEGY_DEFAULT_VALUE = "SymbolEffectStrategy.NONE";
const auto ATTRIBUTE_RENDERING_STRATEGY_NAME = "renderingStrategy";
const auto ATTRIBUTE_RENDERING_STRATEGY_DEFAULT_VALUE = "SymbolRenderingStrategy.SINGLE";
} // namespace

class SymbolSpanModifierTest : public ModifierTestBase<GENERATED_ArkUISymbolSpanModifier,
                                   &GENERATED_ArkUINodeModifiers::getSymbolSpanModifier, GENERATED_ARKUI_SYMBOL_SPAN> {
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
 * @tc.name: setSymbolSpanOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, DISABLED_setSymbolSpanOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) << "Default value for attribute 'value'";
}

/*
 * @tc.name: setSymbolSpanOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, DISABLED_setSymbolSpanOptionsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SymbolSpanModifierTest, setFontSizeTestFontSizeValidValues, TestSize.Level1)
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
HWTEST_F(SymbolSpanModifierTest, setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
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
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) << "Default value for attribute 'fontColor'";
}

/*
 * @tc.name: setFontColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, DISABLED_setFontColorTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setFontWeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setFontWeightTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SymbolSpanModifierTest, setFontWeightTestFontWeightValidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_FontWeight_String& value) {
        Opt_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;

        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontWeightTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setFontWeightTestFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](
                          const std::string& input, const Opt_Union_Number_FontWeight_String& value) {
        Opt_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;

        modifier_->setFontWeight(node_, &inputValueFontWeight);
        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_FontWeight_String>());
}

/*
 * @tc.name: setEffectStrategyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setEffectStrategyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EFFECT_STRATEGY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_EFFECT_STRATEGY_DEFAULT_VALUE) << "Default value for attribute 'effectStrategy'";
}

/*
 * @tc.name: setEffectStrategyTestEffectStrategyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setEffectStrategyTestEffectStrategyValidValues, TestSize.Level1)
{
    Opt_SymbolEffectStrategy initValueEffectStrategy;

    // Initial setup
    initValueEffectStrategy =
        ArkValue<Opt_SymbolEffectStrategy>(std::get<1>(Fixtures::testFixtureEnumSymbolEffectStrategyValidValues[0]));

    auto checkValue = [this, &initValueEffectStrategy](const std::string& input, const std::string& expectedStr,
                          const Opt_SymbolEffectStrategy& value) {
        Opt_SymbolEffectStrategy inputValueEffectStrategy = initValueEffectStrategy;

        inputValueEffectStrategy = value;
        modifier_->setEffectStrategy(node_, &inputValueEffectStrategy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EFFECT_STRATEGY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEffectStrategy, attribute: effectStrategy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumSymbolEffectStrategyValidValues) {
        checkValue(input, expected, ArkValue<Opt_SymbolEffectStrategy>(value));
    }
}

/*
 * @tc.name: setEffectStrategyTestEffectStrategyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setEffectStrategyTestEffectStrategyInvalidValues, TestSize.Level1)
{
    Opt_SymbolEffectStrategy initValueEffectStrategy;

    // Initial setup
    initValueEffectStrategy =
        ArkValue<Opt_SymbolEffectStrategy>(std::get<1>(Fixtures::testFixtureEnumSymbolEffectStrategyValidValues[0]));

    auto checkValue = [this, &initValueEffectStrategy](
                          const std::string& input, const Opt_SymbolEffectStrategy& value) {
        Opt_SymbolEffectStrategy inputValueEffectStrategy = initValueEffectStrategy;

        modifier_->setEffectStrategy(node_, &inputValueEffectStrategy);
        inputValueEffectStrategy = value;
        modifier_->setEffectStrategy(node_, &inputValueEffectStrategy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EFFECT_STRATEGY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_EFFECT_STRATEGY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEffectStrategy, attribute: effectStrategy";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumSymbolEffectStrategyInvalidValues) {
        checkValue(input, ArkValue<Opt_SymbolEffectStrategy>(value));
    }
}

/*
 * @tc.name: setRenderingStrategyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setRenderingStrategyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDERING_STRATEGY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RENDERING_STRATEGY_DEFAULT_VALUE) <<
        "Default value for attribute 'renderingStrategy'";
}

/*
 * @tc.name: setRenderingStrategyTestRenderingStrategyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setRenderingStrategyTestRenderingStrategyValidValues, TestSize.Level1)
{
    Opt_SymbolRenderingStrategy initValueRenderingStrategy;

    // Initial setup
    initValueRenderingStrategy = ArkValue<Opt_SymbolRenderingStrategy>(
        std::get<1>(Fixtures::testFixtureEnumSymbolRenderingStrategyValidValues[0]));

    auto checkValue = [this, &initValueRenderingStrategy](const std::string& input, const std::string& expectedStr,
                          const Opt_SymbolRenderingStrategy& value) {
        Opt_SymbolRenderingStrategy inputValueRenderingStrategy = initValueRenderingStrategy;

        inputValueRenderingStrategy = value;
        modifier_->setRenderingStrategy(node_, &inputValueRenderingStrategy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDERING_STRATEGY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRenderingStrategy, attribute: renderingStrategy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumSymbolRenderingStrategyValidValues) {
        checkValue(input, expected, ArkValue<Opt_SymbolRenderingStrategy>(value));
    }
}

/*
 * @tc.name: setRenderingStrategyTestRenderingStrategyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setRenderingStrategyTestRenderingStrategyInvalidValues, TestSize.Level1)
{
    Opt_SymbolRenderingStrategy initValueRenderingStrategy;

    // Initial setup
    initValueRenderingStrategy = ArkValue<Opt_SymbolRenderingStrategy>(
        std::get<1>(Fixtures::testFixtureEnumSymbolRenderingStrategyValidValues[0]));

    auto checkValue = [this, &initValueRenderingStrategy](
                          const std::string& input, const Opt_SymbolRenderingStrategy& value) {
        Opt_SymbolRenderingStrategy inputValueRenderingStrategy = initValueRenderingStrategy;

        modifier_->setRenderingStrategy(node_, &inputValueRenderingStrategy);
        inputValueRenderingStrategy = value;
        modifier_->setRenderingStrategy(node_, &inputValueRenderingStrategy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDERING_STRATEGY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RENDERING_STRATEGY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRenderingStrategy, attribute: renderingStrategy";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumSymbolRenderingStrategyInvalidValues) {
        checkValue(input, ArkValue<Opt_SymbolRenderingStrategy>(value));
    }
}
} // namespace OHOS::Ace::NG
