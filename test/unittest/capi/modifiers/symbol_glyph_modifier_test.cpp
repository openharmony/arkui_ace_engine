/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
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
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "16.00fp";
const auto ATTRIBUTE_SYMBOL_COLOR_LIST_NAME = "symbolColorList";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_EFFECT_STRATEGY_NAME = "effectStrategy";
const auto ATTRIBUTE_EFFECT_STRATEGY_DEFAULT_VALUE = "SymbolEffectStrategy.NONE";
const auto ATTRIBUTE_RENDERING_STRATEGY_NAME = "renderingStrategy";
const auto ATTRIBUTE_RENDERING_STRATEGY_DEFAULT_VALUE = "SymbolRenderingStrategy.SINGLE";
} // namespace

class SymbolGlyphModifierTest
    : public ModifierTestBase<GENERATED_ArkUISymbolGlyphModifier, &GENERATED_ArkUINodeModifiers::getSymbolGlyphModifier,
          GENERATED_ARKUI_SYMBOL_GLYPH> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

/**
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc: fontSize default
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto size = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
    EXPECT_EQ(size, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
}

/**
 * @tc.name: setFontSizeTestFontSizeValidValues
 * @tc.desc: fontSize valid
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setFontSizeTestFontSizeValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string expectedStr;
    typedef std::pair<Ark_Union_Number_String_Resource, std::string> UnionNumStrResTestStep;
    static const std::vector<UnionNumStrResTestStep> testFontSizeValid = {
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(1.0f),  "1.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(2.45f), "2.45vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(5.0_px), "5.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(22.35_px), "22.35vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(7.0_vp), "7.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(1.65_vp), "1.65vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(65.0_fp), "65.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(4.3_fp), "4.30vp" },
    };

    for (const auto &[value, expectValue]: testFontSizeValid) {
        modifier_->setFontSize(node_, &value);
        jsonValue = GetJsonValue(node_);
        auto size = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(size, expectValue);
    }
}

/**
 * @tc.name: setFontSizeTestFontSizeInvalidValues
 * @tc.desc: fontSize invalid
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string expectedStr;
    typedef std::pair<Ark_Union_Number_String_Resource, std::string> UnionNumStrResTestStep;
    static const std::vector<UnionNumStrResTestStep> testFontSizeInvalid = {
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(-0.1f), "16.00fp"},
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(-5.0_px), "16.00fp" },
    };
    for (const auto &[value, expectValue]: testFontSizeInvalid) {
        modifier_->setFontSize(node_, &value);
        jsonValue = GetJsonValue(node_);
        auto size = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(size, expectValue);
    }
}

/*
 * @tc.name: setFontWeightTestDefaultValues
 * @tc.desc: fontWeight default
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setFontWeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) << "Default value for attribute 'fontWeight'";
}

using  ArkFontWeightTest = std::pair<Ark_Union_Number_FontWeight_String, std::string>;
namespace Converter {
const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_LIGHTER),
        "FontWeight.Lighter" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_NORMAL),
        "FontWeight.Normal" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_REGULAR),
        "FontWeight.Regular" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_MEDIUM),
        "FontWeight.Medium" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_BOLD),
        "FontWeight.Bold" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_BOLDER),
        "FontWeight.Bolder" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(100)), "100" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(200)), "200" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(300)), "300" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(400)), "400" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(500)), "500" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(600)), "600" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(700)), "700" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(800)), "800" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(900)), "900" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("lighter")), "FontWeight.Lighter" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("normal")), "FontWeight.Normal" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("regular")), "FontWeight.Regular" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("medium")), "FontWeight.Medium" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("bold")), "FontWeight.Bold" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("bolder")), "FontWeight.Bolder" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("100")), "100" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("200")), "200" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("300")), "300" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("400")), "400" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("500")), "500" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("600")), "600" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("700")), "700" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("800")), "800" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("900")), "900" },
  };
}

/**
 * @tc.name: setFontWeightTestValidValues
 * @tc.desc: fontWeight valid
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setFontWeightTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight, nullptr);
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;
    for (const auto &[weight, expectValue] : Converter::FONT_WEIGHT_TEST_PLAN) {
        modifier_->setFontWeight(node_, &weight);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(result, expectValue);
    }
}

/**
 * @tc.name: setFontWeightTestInvalidValues
 * @tc.desc: fontWeight invalid
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setFontWeightTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight, nullptr);
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;

    const std::vector<ArkFontWeightTest> testPlan = {
        { Converter::ArkUnion<Ark_Union_Number_FontWeight_String,
            Ark_Number>(Converter::ArkValue<Ark_Number>(1000)), "FontWeight.Normal" },
        { Converter::ArkUnion<Ark_Union_Number_FontWeight_String,
            Ark_String>(Converter::ArkValue<Ark_String>("1000")), "FontWeight.Normal" },
    };
    for (const auto &[weight, expectValue] : testPlan) {
        modifier_->setFontWeight(node_, &weight);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(result, expectValue);
    }
}

/*
 * @tc.name: setEffectStrategyTestDefaultValues
 * @tc.desc: effectStrategy default
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setEffectStrategyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EFFECT_STRATEGY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_EFFECT_STRATEGY_DEFAULT_VALUE) << "Default value for attribute 'effectStrategy'";
}

// Valid values for attribute 'effectStrategy'
static std::vector<std::tuple<std::string, enum Ark_SymbolEffectStrategy, std::string>>
    effectStrategyValidValues = {
    {"ARK_SYMBOL_EFFECT_STRATEGY_NONE",
        Converter::ArkValue<enum Ark_SymbolEffectStrategy>(ARK_SYMBOL_EFFECT_STRATEGY_NONE),
        "SymbolEffectStrategy.NONE"},
    {"ARK_SYMBOL_EFFECT_STRATEGY_SCALE",
        Converter::ArkValue<enum Ark_SymbolEffectStrategy>(ARK_SYMBOL_EFFECT_STRATEGY_SCALE),
        "SymbolEffectStrategy.SCALE"},
    {"ARK_SYMBOL_EFFECT_STRATEGY_HIERARCHICAL",
        Converter::ArkValue<enum Ark_SymbolEffectStrategy>(ARK_SYMBOL_EFFECT_STRATEGY_HIERARCHICAL),
        "SymbolEffectStrategy.HIERARCHICAL"},
};

/*
 * @tc.name: setEffectStrategytTestValidValues
 * @tc.desc: effectStrategy valid
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setEffectStrategytTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SymbolEffectStrategy inputValueEffectStrategy;

    // Verifying attribute's values
    inputValueEffectStrategy = std::get<1>(effectStrategyValidValues[0]);
    for (auto&& value: effectStrategyValidValues) {
        inputValueEffectStrategy = std::get<1>(value);
        modifier_->setEffectStrategy(node_, inputValueEffectStrategy);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EFFECT_STRATEGY_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'effectStrategy'
static std::vector<std::tuple<std::string, enum Ark_SymbolEffectStrategy, std::string>>
    effectStrategyInvalidValues = {
    {"-1", Converter::ArkValue<enum Ark_SymbolEffectStrategy>(static_cast<Ark_SymbolEffectStrategy>(-1)),
        "SymbolEffectStrategy.NONE"},
    {"3", Converter::ArkValue<enum Ark_SymbolEffectStrategy>(static_cast<Ark_SymbolEffectStrategy>(3)),
        "SymbolEffectStrategy.NONE"},
};

/*
 * @tc.name: setEffectStrategytTestInvalidValues
 * @tc.desc: effectStrategy invalid
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setEffectStrategytTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SymbolEffectStrategy inputValueEffectStrategy;

    // Verifying attribute's values
    inputValueEffectStrategy = std::get<1>(effectStrategyInvalidValues[0]);
    for (auto&& value: effectStrategyInvalidValues) {
        inputValueEffectStrategy = std::get<1>(value);
        modifier_->setEffectStrategy(node_, inputValueEffectStrategy);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EFFECT_STRATEGY_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setRenderingStrategyTestDefaultValues
 * @tc.desc: renderingStrategy default
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setRenderingStrategyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDERING_STRATEGY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RENDERING_STRATEGY_DEFAULT_VALUE)
        << "Default value for attribute 'renderingStrategy'";
}

// Valid values for attribute 'renderingStrategy' of method 'renderingStrategy'
static std::vector<std::tuple<std::string, enum Ark_SymbolRenderingStrategy, std::string>>
    renderingStrategyValidValues = {
    {"ARK_SYMBOL_RENDERING_STRATEGY_SINGLE",
        Converter::ArkValue<enum Ark_SymbolRenderingStrategy>(ARK_SYMBOL_RENDERING_STRATEGY_SINGLE),
        "SymbolRenderingStrategy.SINGLE"},
    {"ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_COLOR",
        Converter::ArkValue<enum Ark_SymbolRenderingStrategy>(ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_COLOR),
        "SymbolRenderingStrategy.MULTIPLE_COLOR"},
    {"ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_OPACITY",
        Converter::ArkValue<enum Ark_SymbolRenderingStrategy>(ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_OPACITY),
        "SymbolRenderingStrategy.MULTIPLE_OPACITY"},
};

/*
 * @tc.name: setRenderingStrategytTestValidValues
 * @tc.desc: renderingStrategy valid
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setRenderingStrategytTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SymbolRenderingStrategy inputValueRenderingStrategy;

    // Verifying attribute's values
    inputValueRenderingStrategy = std::get<1>(renderingStrategyValidValues[0]);
    for (auto&& value: renderingStrategyValidValues) {
        inputValueRenderingStrategy = std::get<1>(value);
        modifier_->setRenderingStrategy(node_, inputValueRenderingStrategy);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDERING_STRATEGY_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'renderingStrategy' of method 'renderingStrategy'
static std::vector<std::tuple<std::string, enum Ark_SymbolRenderingStrategy, std::string>>
    renderingStrategyInvalidValues = {
    {"-1", Converter::ArkValue<enum Ark_SymbolRenderingStrategy>(static_cast<Ark_SymbolRenderingStrategy>(-1)),
        "SymbolRenderingStrategy.SINGLE"},
    {"3", Converter::ArkValue<enum Ark_SymbolRenderingStrategy>(static_cast<Ark_SymbolRenderingStrategy>(3)),
        "SymbolRenderingStrategy.SINGLE"},
};

/*
 * @tc.name: setRenderingStrategytTestInvalidValues
 * @tc.desc: renderingStrategy valid
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setRenderingStrategyTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SymbolRenderingStrategy inputValueRenderingStrategy;

    // Verifying attribute's values
    inputValueRenderingStrategy = std::get<1>(renderingStrategyInvalidValues[0]);
    for (auto&& value: renderingStrategyInvalidValues) {
        inputValueRenderingStrategy = std::get<1>(value);
        modifier_->setRenderingStrategy(node_, inputValueRenderingStrategy);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDERING_STRATEGY_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc: fontColor default
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) << "Default value for attribute 'fontColor'";
}

static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>> symbolColorValues = {
    { "ARK_COLOR_BLUE", Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "\"#FF0000FF\"" },
    { "ARK_COLOR_RED", Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_RED), "\"#FFFF0000\"" },
    { "ARK_COLOR_PINK", Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_PINK), "\"#FFFFC0CB\"" },
};

/**
 * @tc.name: setFontColorTest
 * @tc.desc: fontColor valid
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setFontColorTest, TestSize.Level1)
{    
    std::unique_ptr<JsonValue> jsonValue;
    std::string expectedStr;
    std::string resultStr;
    Ark_ResourceColor fontColor;
    Array_ResourceColor colorArray;

    for (int i = 0; i < symbolColorValues.size(); i++) {
        colorArray.length = 1;
        fontColor = std::get<1>(symbolColorValues[i]);
        colorArray.array = &fontColor;

        modifier_->setFontColor(node_, &colorArray);
        jsonValue = GetJsonValue(node_);
        auto attrValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SYMBOL_COLOR_LIST_NAME);
        auto resultJson = attrValue.get();

        resultStr = resultJson->GetArrayItem(0)->ToString();
        expectedStr = std::get<2>(symbolColorValues[i]);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(symbolColorValues[i]);
    }
}

} // namespace OHOS::Ace::NG
