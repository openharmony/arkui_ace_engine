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
#include "core/interfaces/native/implementation/symbol_effect_peer.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
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
const auto ATTRIBUTE_UNICODE_NAME = "unicode";
const auto ATTRIBUTE_UNICODE_NAME_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_MIN_FONT_SCALE_NAME = "minFontScale";
const auto ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE = "0.850000";
const auto ATTRIBUTE_MAX_FONT_SCALE_NAME = "maxFontScale";
const auto ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE = "3.200000";

enum ResIntegerID {
    INT_RES_0_ID,
    INT_RES_1_ID,
    INT_RES_2_ID,
    INT_RES_3_ID,
    INT_RES_4_ID,
    INT_RES_5_ID,
};

constexpr auto INT_RES_0_STR = "INTEGER_RES_0_STR";
constexpr auto INT_RES_1_STR = "INTEGER_RES_1_STR";
constexpr auto INT_RES_2_STR = "INTEGER_RES_2_STR";
constexpr auto INT_RES_3_STR = "INTEGER_RES_3_STR";
constexpr auto INT_RES_4_STR = "INTEGER_RES_4_STR";
constexpr auto INT_RES_5_STR = "INTEGER_RES_5_STR";

std::vector<std::tuple<ResIntegerID, std::string, OHOS::Ace::ResRawValue>> resourceInitTable = {
    { INT_RES_0_ID, INT_RES_0_STR, 1 },
    { INT_RES_1_ID, INT_RES_1_STR, 12 },
    { INT_RES_2_ID, INT_RES_2_STR, 123 },
    { INT_RES_3_ID, INT_RES_3_STR, 1234},
    { INT_RES_4_ID, INT_RES_4_STR, 12345 },
    { INT_RES_5_ID, INT_RES_5_STR, 123456 },
};

} // namespace

class SymbolGlyphModifierTest
    : public ModifierTestBase<GENERATED_ArkUISymbolGlyphModifier, &GENERATED_ArkUINodeModifiers::getSymbolGlyphModifier,
          GENERATED_ARKUI_SYMBOL_GLYPH> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        for (auto& [id, strid, res] : resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/**
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc: fontSize default
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, DISABLED_setFontSizeTestDefaultValues, TestSize.Level1)
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
HWTEST_F(SymbolGlyphModifierTest, DISABLED_setFontSizeTestFontSizeValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string expectedStr;
    typedef std::pair<Opt_Union_F64_String_Resource, std::string> UnionNumStrResTestStep;
    const std::vector<UnionNumStrResTestStep> testFontSizeValid = {
        { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(1.0f),  "1.00vp" },
        { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(2.45f), "2.45vp" },
        { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("5.0px"), "5.00vp" },
        { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("22.35px"), "22.35vp" },
        { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("7.0vp"), "7.00vp" },
        { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("1.65vp"), "1.65vp" },
        { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("65.0fp"), "65.00vp" },
        { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("4.3fp"), "4.30vp" },
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
HWTEST_F(SymbolGlyphModifierTest, DISABLED_setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string expectedStr;
    typedef std::pair<Opt_Union_F64_String_Resource, std::string> UnionNumStrResTestStep;
    const std::vector<UnionNumStrResTestStep> testFontSizeInvalid = {
        { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(-0.1f), "16.00fp"},
        { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("-5.0px"), "16.00fp" },
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

using  ArkFontWeightTest = std::pair<Opt_Union_I32_FontWeight_String, std::string>;
namespace Converter {
const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_LIGHTER), "FontWeight.Lighter" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_NORMAL), "FontWeight.Normal" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR), "FontWeight.Regular" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_MEDIUM), "FontWeight.Medium" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD), "FontWeight.Bold" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLDER), "FontWeight.Bolder" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(100), "100" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(200), "200" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(300), "300" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(400), "400" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(500), "500" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(600), "600" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(700), "700" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(800), "800" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(900), "900" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("lighter"), "FontWeight.Lighter" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("normal"), "FontWeight.Normal" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("regular"), "FontWeight.Regular" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("medium"), "FontWeight.Medium" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("bold"), "FontWeight.Bold" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("bolder"), "FontWeight.Bolder" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("100"), "100" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("200"), "200" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("300"), "300" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("400"), "400" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("500"), "500" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("600"), "600" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("700"), "700" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("800"), "800" },
    { ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("900"), "900" },
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
        { Converter::ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(1000), "FontWeight.Normal" },
        { Converter::ArkUnion<Opt_Union_I32_FontWeight_String, Ark_String>("1000"), "FontWeight.Normal" },
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
static std::vector<std::tuple<std::string, Ark_SymbolEffectStrategy, std::string>>
    effectStrategyValidValues = {
    {"ARK_SYMBOL_EFFECT_STRATEGY_NONE", ARK_SYMBOL_EFFECT_STRATEGY_NONE, "SymbolEffectStrategy.NONE"},
    {"ARK_SYMBOL_EFFECT_STRATEGY_SCALE", ARK_SYMBOL_EFFECT_STRATEGY_SCALE, "SymbolEffectStrategy.SCALE"},
    {"ARK_SYMBOL_EFFECT_STRATEGY_HIERARCHICAL", ARK_SYMBOL_EFFECT_STRATEGY_HIERARCHICAL,
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
    auto inputValueEffectStrategy = Converter::ArkValue<Opt_SymbolEffectStrategy>(
        std::get<1>(effectStrategyValidValues[0]));

    // Verifying attribute's values
    for (auto&& value: effectStrategyValidValues) {
        inputValueEffectStrategy = Converter::ArkValue<Opt_SymbolEffectStrategy>(std::get<1>(value));
        modifier_->setEffectStrategy(node_, &inputValueEffectStrategy);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EFFECT_STRATEGY_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'effectStrategy'
static std::vector<std::tuple<std::string, Ark_SymbolEffectStrategy, std::string>>
    effectStrategyInvalidValues = {
    {"-1", Converter::ArkValue<Ark_SymbolEffectStrategy>(static_cast<Ark_SymbolEffectStrategy>(-1)),
        "SymbolEffectStrategy.NONE"},
    {"3", Converter::ArkValue<Ark_SymbolEffectStrategy>(static_cast<Ark_SymbolEffectStrategy>(3)),
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
    auto inputValueEffectStrategy = Converter::ArkValue<Opt_SymbolEffectStrategy>(
        std::get<1>(effectStrategyInvalidValues[0]));

    // Verifying attribute's values
    for (auto&& value: effectStrategyInvalidValues) {
        inputValueEffectStrategy = Converter::ArkValue<Opt_SymbolEffectStrategy>(std::get<1>(value));
        modifier_->setEffectStrategy(node_, &inputValueEffectStrategy);
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
    EXPECT_EQ(resultStr, ATTRIBUTE_RENDERING_STRATEGY_DEFAULT_VALUE) <<
        "Default value for attribute 'renderingStrategy'";
}

// Valid values for attribute 'renderingStrategy' of method 'renderingStrategy'
static std::vector<std::tuple<std::string, Ark_SymbolRenderingStrategy, std::string>>
    renderingStrategyValidValues = {
    {"ARK_SYMBOL_RENDERING_STRATEGY_SINGLE",
        Converter::ArkValue<Ark_SymbolRenderingStrategy>(ARK_SYMBOL_RENDERING_STRATEGY_SINGLE),
        "SymbolRenderingStrategy.SINGLE"},
    {"ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_COLOR",
        Converter::ArkValue<Ark_SymbolRenderingStrategy>(ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_COLOR),
        "SymbolRenderingStrategy.MULTIPLE_COLOR"},
    {"ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_OPACITY",
        Converter::ArkValue<Ark_SymbolRenderingStrategy>(ARK_SYMBOL_RENDERING_STRATEGY_MULTIPLE_OPACITY),
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
    auto inputValueRenderingStrategy = Converter::ArkValue<Opt_SymbolRenderingStrategy>(
        std::get<1>(renderingStrategyValidValues[0]));

    // Verifying attribute's values
    for (auto&& value: renderingStrategyValidValues) {
        inputValueRenderingStrategy = Converter::ArkValue<Opt_SymbolRenderingStrategy>(std::get<1>(value));
        modifier_->setRenderingStrategy(node_, &inputValueRenderingStrategy);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDERING_STRATEGY_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'renderingStrategy' of method 'renderingStrategy'
static std::vector<std::tuple<std::string, Ark_SymbolRenderingStrategy, std::string>>
    renderingStrategyInvalidValues = {
    {"-1", static_cast<Ark_SymbolRenderingStrategy>(-1), "SymbolRenderingStrategy.SINGLE"},
    {"3", static_cast<Ark_SymbolRenderingStrategy>(3), "SymbolRenderingStrategy.SINGLE"},
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
    auto inputValueRenderingStrategy = Converter::ArkValue<Opt_SymbolRenderingStrategy>(
        std::get<1>(renderingStrategyInvalidValues[0]));

    // Verifying attribute's values
    for (auto&& value: renderingStrategyInvalidValues) {
        inputValueRenderingStrategy = Converter::ArkValue<Opt_SymbolRenderingStrategy>(std::get<1>(value));
        modifier_->setRenderingStrategy(node_, &inputValueRenderingStrategy);
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

static std::vector<std::tuple<std::string, std::string>> fontColorVectorValues = {
    {"ARK_COLOR_BLUE", "\"#FF0000FF\""},
    {"0x123456", "\"#FF123456\""},
    {"#11223344", "\"#11223344\""},
    {"65535", "\"#FF00FFFF\""},
};

static std::vector<Ark_ResourceColor> fontColorVector = {
    Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE),
    Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456),
    Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"),
    Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"),
};

/**
 * @tc.name: setFontColorTest
 * @tc.desc: fontColor valid
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, DISABLED_setFontColorTest, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string expectedStr;
    std::string resultStr;

    Converter::ArkArrayHolder<Array_ResourceColor> vecHolder(fontColorVector);
    Array_ResourceColor colorArray = vecHolder.ArkValue();
    auto arkColorArray = Converter::ArkValue<Opt_Array_ResourceColor>(colorArray);
    modifier_->setFontColor(node_, &arkColorArray);

    jsonValue = GetJsonValue(node_);
    auto attrValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SYMBOL_COLOR_LIST_NAME);
    auto resultJson = attrValue.get();

    for (int i = 0; i < fontColorVector.size(); i++) {
        resultStr = resultJson->GetArrayItem(i)->ToString();
        expectedStr = std::get<1>(fontColorVectorValues[i]);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(fontColorVectorValues[i]);
    }
}

/*
 * @tc.name: setSymbolGlyphOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, DISABLED_setSymbolGlyphOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNICODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_UNICODE_NAME_DEFAULT_VALUE) << "Default value for attribute 'value.id'";
}

// Fixture 'StringRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testSymbolGlyphOptionsResValidValues = {
    { "ResId:STRING_RES_0_ID", CreateResource(INT_RES_0_STR, ResourceType::INTEGER), "1" },
    { "ResName:STRING_RES_0_STR", CreateResource(INT_RES_1_STR, ResourceType::INTEGER), "12" },
    { "ResId:STRING_RES_1_ID", CreateResource(INT_RES_2_STR, ResourceType::INTEGER), "123" },
    { "ResName:STRING_RES_1_STR", CreateResource(INT_RES_3_STR, ResourceType::INTEGER), "1234" },
    { "ResId:STRING_RES_2_ID", CreateResource(INT_RES_4_STR, ResourceType::INTEGER), "12345" },
    { "ResName:STRING_RES_2_STR", CreateResource(INT_RES_5_STR, ResourceType::INTEGER), "123456" },
};

/*
 * @tc.name: setSymbolGlyphOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, DISABLED_setSymbolGlyphOptionsTestValidValues, TestSize.Level1)
{
    Ark_Resource initValueContent;

    // Initial setup
    initValueContent = std::get<1>(testSymbolGlyphOptionsResValidValues[0]);

    auto checkValue = [this, &initValueContent](const std::string& input, const Ark_Resource& value,
                          const std::string& expectedStr) {
        Opt_Resource inputValueContent;
        inputValueContent.value = initValueContent;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueContent.value = value;
        modifier_->setSymbolGlyphOptions(node, &inputValueContent);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNICODE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setGlyphOptions, attribute: content";
    };

    for (auto& [input, value, expected] : testSymbolGlyphOptionsResValidValues) {
        checkValue(input, value, expected);
    }
}

std::vector<std::tuple<std::string, OHOS::Ace::ScopeType, std::string>> testSymbolGlyphSymbolEffectScope = {
    { "ScopeType::LAYER", OHOS::Ace::ScopeType::LAYER, "0" },
    { "ScopeType::WHOLE", OHOS::Ace::ScopeType::WHOLE, "1" },
};

HWTEST_F(SymbolGlyphModifierTest, setSymbolEffect0TestScaleScope, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input, const OHOS::Ace::ScopeType& value,
        const std::string& expectedStr) {
        auto peer = static_cast<SymbolEffectPeer*>(
            PeerUtils::CreatePeer<ScaleSymbolEffectPeer>(value, CommonSubType::DOWN));
        auto arkPeer = Converter::ArkValue<Opt_SymbolEffect>(peer);
        modifier_->setSymbolEffect0(node_, &arkPeer);
        auto jsonValue = GetJsonValue(node_);
        auto symbolEffect = GetAttrValue<std::string>(jsonValue, "symbolEffect");
        auto resultStr = GetAttrValue<std::string>(symbolEffect, "scopeType");
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSymbolEffect, attribute: symbolEffect.scope";
    };

    for (auto& [input, value, expected] : testSymbolGlyphSymbolEffectScope) {
        checkValue(input, value, expected);
    }
}

std::vector<std::tuple<std::string, CommonSubType, std::string>> testSymbolGlyphSymbolEffectDirection = {
    { "CommonSubType::DOWN", CommonSubType::DOWN, "0" },
    { "CommonSubType::UP", CommonSubType::UP, "1" },
};

HWTEST_F(SymbolGlyphModifierTest, setSymbolEffect0TestScaleDirection, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input, const CommonSubType& value,
        const std::string& expectedStr) {
        auto peer = static_cast<SymbolEffectPeer*>(
            PeerUtils::CreatePeer<ScaleSymbolEffectPeer>(OHOS::Ace::ScopeType::LAYER, value));
        auto arkPeer = Converter::ArkValue<Opt_SymbolEffect>(peer);
        modifier_->setSymbolEffect0(node_, &arkPeer);
        auto jsonValue = GetJsonValue(node_);
        auto symbolEffect = GetAttrValue<std::string>(jsonValue, "symbolEffect");
        auto resultStr = GetAttrValue<std::string>(symbolEffect, "commonSubType");
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSymbolEffect, attribute: symbolEffect.direction";
    };

    for (auto& [input, value, expected] : testSymbolGlyphSymbolEffectDirection) {
        checkValue(input, value, expected);
    }
}

HWTEST_F(SymbolGlyphModifierTest, setSymbolEffect0TestReplaceScope, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input, const OHOS::Ace::ScopeType& value,
        const std::string& expectedStr) {
        auto peer = static_cast<SymbolEffectPeer*>(
            PeerUtils::CreatePeer<ReplaceSymbolEffectPeer>(value));
        auto arkPeer = Converter::ArkValue<Opt_SymbolEffect>(peer);
        modifier_->setSymbolEffect0(node_, &arkPeer);
        auto jsonValue = GetJsonValue(node_);
        auto symbolEffect = GetAttrValue<std::string>(jsonValue, "symbolEffect");
        auto resultStr = GetAttrValue<std::string>(symbolEffect, "scopeType");
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSymbolEffect, attribute: symbolEffect.scope";
    };

    for (auto& [input, value, expected] : testSymbolGlyphSymbolEffectScope) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setMinFontScaleDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setMinFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'minFontScale'";
}

/*
 * @tc.name: setMinFontScaleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setMinFontScaleTestValidValues, TestSize.Level1)
{
    std::vector<std::tuple<std::string, double, std::string>> testFixtureMinFontScaleNumValidValues = {
        { "0.1", 0.1, "0.100000" },
        { "0.89", 0.89, "0.890000" },
        { "1", 1, "1.000000" },
    };

    auto checkValue = [this](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_F64_Resource& value) {
        modifier_->setMinFontScale(node_, &value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };
    for (auto& [input, value, expected] : testFixtureMinFontScaleNumValidValues) {
        checkValue(input, expected, Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(value));
    }
}

/*
 * @tc.name: setMinFontScaleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, DISABLED_setMinFontScaleTestInvalidValues, TestSize.Level1)
{
    std::vector<std::tuple<std::string, double, std::string>> testFixtureMinFontScaleNumInvalidValues = {
        { "-1.01", -1.01, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE },
        { "2.89", 2.89, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE },
        { "-1", -1, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE },
    };

    // Initial setup
    auto initValue = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(1);
    auto checkValue = [this, &initValue](const std::string& input, const std::string& expectedStr,
                                                     const Opt_Union_F64_Resource& value) {
        auto inputValueMinFontScale = initValue;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        inputValueMinFontScale = value;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };
    for (auto& [input, value, expected] : testFixtureMinFontScaleNumInvalidValues) {
        checkValue(input, expected, Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(value));
    }
}

/*
 * @tc.name: setMaxFontScaleDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setMaxFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'maxFontScale'";
}

/*
 * @tc.name: setMaxFontScaleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, setMaxFontScaleTestValidValues, TestSize.Level1)
{
    std::vector<std::tuple<std::string, double, std::string>> testFixtureMaxFontScaleNumValidValues = {
        { "1", 1, "1.000000" },
        { "1.5", 1.5, "1.500000" },
        { "1.99", 1.99, "1.990000" },
    };
    auto checkValue = [this](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_F64_Resource& value) {
        modifier_->setMaxFontScale(node_, &value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };
    for (auto& [input, value, expected] : testFixtureMaxFontScaleNumValidValues) {
        checkValue(input, expected, Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(value));
    }
}

/*
 * @tc.name: setMaxFontScaleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolGlyphModifierTest, DISABLED_setMaxFontScaleTestInvalidValues, TestSize.Level1)
{
    std::vector<std::tuple<std::string, double, std::string>> testFixtureMaxFontScaleNumInvalidValues = {
        { "0.1", 0.1, "ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE" },
        { "-1.5", -1.5, "ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE" },
        { "-0.99", -0.99, "ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE" },
    };

    // Initial setup
    auto initValue = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(1);
    auto checkValue = [this, &initValue](const std::string& input, const std::string& expectedStr,
                                                     const Opt_Union_F64_Resource& value) {
        auto inputValueMaxFontScale = initValue;

        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        inputValueMaxFontScale = value;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };
    for (auto& [input, value, expected] : testFixtureMaxFontScaleNumInvalidValues) {
        checkValue(input, expected, Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(value));
    }
}

} // namespace OHOS::Ace::NG
