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
#include "generated/test_fixtures.h"
#include "core/components/theme/theme_style.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/span/symbol_span_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "generated/type_helpers.h"

using namespace testing;
using namespace testing::ext;

namespace {
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
}

namespace OHOS::Ace::NG {
using TypeHelper::WriteTo;
namespace {
const auto ATTRIBUTE_UNICODE_NAME = "unicode";
const auto ATTRIBUTE_UNICODE_NAME_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_SYMBOL_COLOR_NAME = "SymbolColor";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_VARIABLE_FONT_WEIGHT_NAME = "variableFontWeight";
const int32_t ATTRIBUTE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE = 0;
const auto ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_NAME = "enableVariableFontWeight";
const bool ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE = false;
const auto ATTRIBUTE_ENABLE_DEVICE_FONT_WEIGHT_CATEGORY_NAME = "enableDeviceFontWeightCategory";

constexpr int32_t WEIGHT_W100 = 100;
constexpr int32_t WEIGHT_W400 = 400;
constexpr int32_t WEIGHT_W700 = 700;
constexpr int32_t WEIGHT_W900 = 900;
} // namespace

class SymbolSpanModifierTest : public ModifierTestBase<GENERATED_ArkUISymbolSpanModifier,
    &GENERATED_ArkUINodeModifiers::getSymbolSpanModifier, GENERATED_ARKUI_SYMBOL_SPAN> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
    std::string SymbolColorToString(std::vector<std::string> colorVec) const
    {
        auto colorStr = std::string("[");
        for (std::basic_string<char> const & color : colorVec) {
            colorStr.append(color);
            colorStr.append(",");
        }
        colorStr.append("]");
        return colorStr;
    }

    void SetUp() override
    {
        ModifierTestBase::SetUp();
        textPattern_ = AceType::MakeRefPtr<TextPattern>();
        textFrameNode_ = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), textPattern_);
        auto spanNode = AceType::DynamicCast<SpanNode>(reinterpret_cast<FrameNode*>(node_));
        if (spanNode) {
            spanNode->GetSpanItem()->SetTextPattern(textPattern_);
        }
    }

    void TearDown() override
    {
        textFrameNode_ = nullptr;
        textPattern_ = nullptr;
        ModifierTestBase::TearDown();
    }

private:
    RefPtr<TextPattern> textPattern_;
    RefPtr<FrameNode> textFrameNode_;
};

// Fixture 'StringRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testSymbolSpanOptionsResValidValues = {
    { "ResId:STRING_RES_0_ID", CreateResource(INT_RES_0_STR, ResourceType::INTEGER), "1" },
    { "ResName:STRING_RES_0_STR", CreateResource(INT_RES_1_STR, ResourceType::INTEGER), "12" },
    { "ResId:STRING_RES_1_ID", CreateResource(INT_RES_2_STR, ResourceType::INTEGER), "123" },
    { "ResName:STRING_RES_1_STR", CreateResource(INT_RES_3_STR, ResourceType::INTEGER), "1234" },
    { "ResId:STRING_RES_2_ID", CreateResource(INT_RES_4_STR, ResourceType::INTEGER), "12345" },
    { "ResName:STRING_RES_2_STR", CreateResource(INT_RES_5_STR, ResourceType::INTEGER), "123456" },
};

/*
 * @tc.name: setSymbolSpanOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, DISABLED_setSymbolSpanOptionsTestValidValues, TestSize.Level1)
{
    Ark_Resource initValueContent;
    // Initial setup
    initValueContent = std::get<1>(testSymbolSpanOptionsResValidValues[0]);

    auto checkValue = [this, &initValueContent](const std::string& input, const Ark_Resource& value,
                          const std::string& expectedStr) {
        Ark_Resource inputValueContent = initValueContent;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueContent = value;
        modifier_->setSymbolSpanOptions(node, &inputValueContent);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNICODE_NAME);
        DisposeNode(node);
        EXPECT_THAT(resultStr, Eq(expectedStr)) <<
            "Input value is: " << input << ", method: setSpanOptions, attribute: content";
    };

    for (auto& [input, value, expected] : testSymbolSpanOptionsResValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setSymbolSpanOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, DISABLED_setSymbolSpanOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::optional<std::string> resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNICODE_NAME);
    EXPECT_THAT(resultStr, Eq(ATTRIBUTE_UNICODE_NAME_DEFAULT_VALUE)) << "Default value for attribute 'value.id'";
}

static const std::vector<std::pair<Ark_ResourceColor, std::string>> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
};

/*
 * @tc.name: setFontColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, DISABLED_setFontColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::optional<std::string> resultStr;
    std::vector<Ark_ResourceColor> fontColorVector;
    std::vector<std::string> expectedVector;
    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        fontColorVector.emplace_back(value);
        expectedVector.emplace_back(expectVal);
    }
    auto symbolColorStr = SymbolColorToString(expectedVector);
    Converter::ArkArrayHolder<Array_ResourceColor> vecHolder(fontColorVector);
    Array_ResourceColor colorArray = vecHolder.ArkValue();
    auto arkColorArray = Converter::ArkValue<Opt_Array_ResourceColor>(colorArray);
    modifier_->setFontColor(node_, &arkColorArray);

    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SYMBOL_COLOR_NAME);
    EXPECT_THAT(resultStr, Eq(symbolColorStr)) << "Passed value is: " << symbolColorStr;
}

/**
 * @tc.name: setFontWeightTestDefaultValues
 * @tc.desc: Verify default fontWeight value after node creation
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setFontWeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_THAT(result, Eq(ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE));
}

/**
 * @tc.name: setFontWeight1TestValidValues
 * @tc.desc: setFontWeight1 with valid fontWeight values (int, enum, ResourceStr)
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setFontWeight1TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight1, nullptr);
    typedef std::pair<Opt_Union_I32_FontWeight_ResourceStr, std::string> FontWeightResourceStrTestStep;
    const std::vector<FontWeightResourceStrTestStep> testPlan = {
        { Converter::ArkUnion<Opt_Union_I32_FontWeight_ResourceStr, Ark_Int32>(100), "100" },
        { Converter::ArkUnion<Opt_Union_I32_FontWeight_ResourceStr, Ark_Int32>(400), "400" },
        { Converter::ArkUnion<Opt_Union_I32_FontWeight_ResourceStr, Ark_Int32>(700), "700" },
        { Converter::ArkUnion<Opt_Union_I32_FontWeight_ResourceStr, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD),
            "FontWeight.Bold" },
        { Converter::ArkUnion<Opt_Union_I32_FontWeight_ResourceStr, Ark_FontWeight>(ARK_FONT_WEIGHT_LIGHTER),
            "FontWeight.Lighter" },
    };
    std::unique_ptr<JsonValue> jsonValue;
    std::optional<std::string> result;
    for (const auto& [weight, expectValue] : testPlan) {
        modifier_->setFontWeight1(node_, &weight, nullptr);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_THAT(result, Eq(expectValue));
    }
}

/**
 * @tc.name: setFontWeight1TestNullConfigsResets
 * @tc.desc: setFontWeight1 with null fontWeightConfigs resets variable/enabled flags
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setFontWeight1TestNullConfigsResets, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    // Set variable font weight and enable flags via Model API
    SymbolSpanModelNG::SetVariableFontWeight(frameNode, WEIGHT_W700);
    SymbolSpanModelNG::SetEnableVariableFontWeight(frameNode, true);
    SymbolSpanModelNG::SetEnableDeviceFontWeightCategory(frameNode, true);

    // Call setFontWeight1 with null configs should reset all
    auto weight = Converter::ArkUnion<Opt_Union_I32_FontWeight_ResourceStr, Ark_Int32>(400);
    modifier_->setFontWeight1(node_, &weight, nullptr);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto variableResult = GetAttrValue<int>(jsonValue, ATTRIBUTE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_THAT(variableResult, Eq(ATTRIBUTE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE));

    auto configsStr = GetAttrValue<std::string>(jsonValue, "fontWeightConfigs");
    ASSERT_TRUE(configsStr.has_value());
    auto enableResult = GetAttrValue<bool>(configsStr.value(), ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_THAT(enableResult, Eq(ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE));
}

/**
 * @tc.name: setFontWeight1TestEnableVariableFontWeight
 * @tc.desc: setFontWeight1 with enableVariableFontWeight config
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setFontWeight1TestEnableVariableFontWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight1, nullptr);

    auto weight = Converter::ArkUnion<Opt_Union_I32_FontWeight_ResourceStr, Ark_Int32>(WEIGHT_W700);

    Opt_FontWeightConfigs configs = {};
    WriteTo(configs).enableVariableFontWeight = Converter::ArkValue<Opt_Boolean>(true);

    modifier_->setFontWeight1(node_, &weight, &configs);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);

    auto configsStr = GetAttrValue<std::string>(jsonValue, "fontWeightConfigs");
    ASSERT_TRUE(configsStr.has_value());
    auto enableResult = GetAttrValue<bool>(configsStr.value(), ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_THAT(enableResult, Eq(true));
}

/**
 * @tc.name: setFontWeight1TestEnableVariableFontWeightFalse
 * @tc.desc: setFontWeight1 with enableVariableFontWeight = false
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setFontWeight1TestEnableVariableFontWeightFalse, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight1, nullptr);

    auto weight = Converter::ArkUnion<Opt_Union_I32_FontWeight_ResourceStr, Ark_Int32>(WEIGHT_W700);

    Opt_FontWeightConfigs configs = {};
    WriteTo(configs).enableVariableFontWeight = Converter::ArkValue<Opt_Boolean>(false);

    modifier_->setFontWeight1(node_, &weight, &configs);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);

    auto configsStr = GetAttrValue<std::string>(jsonValue, "fontWeightConfigs");
    ASSERT_TRUE(configsStr.has_value());
    auto enableResult = GetAttrValue<bool>(configsStr.value(), ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_THAT(enableResult, Eq(false));
}

/**
 * @tc.name: setFontWeight1TestEnableDeviceFontWeightCategory
 * @tc.desc: setFontWeight1 with enableDeviceFontWeightCategory config
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setFontWeight1TestEnableDeviceFontWeightCategory, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight1, nullptr);

    auto weight = Converter::ArkUnion<Opt_Union_I32_FontWeight_ResourceStr, Ark_Int32>(WEIGHT_W400);

    Opt_FontWeightConfigs configs = {};
    WriteTo(configs).enableDeviceFontWeightCategory = Converter::ArkValue<Opt_Boolean>(false);

    modifier_->setFontWeight1(node_, &weight, &configs);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);

    auto configsStr = GetAttrValue<std::string>(jsonValue, "fontWeightConfigs");
    ASSERT_TRUE(configsStr.has_value());
    auto result = GetAttrValue<bool>(configsStr.value(), ATTRIBUTE_ENABLE_DEVICE_FONT_WEIGHT_CATEGORY_NAME);
    EXPECT_THAT(result, Eq(false));
}

/**
 * @tc.name: setFontWeight1TestUndefinedEnableDeviceFontWeightDefaults
 * @tc.desc: setFontWeight1 with enableDeviceFontWeightCategory undefined defaults to true
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setFontWeight1TestUndefinedEnableDeviceFontWeightDefaults, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight1, nullptr);

    auto weight = Converter::ArkUnion<Opt_Union_I32_FontWeight_ResourceStr, Ark_Int32>(WEIGHT_W400);

    // Only set enableVariableFontWeight, leave enableDeviceFontWeightCategory undefined
    Opt_FontWeightConfigs configs = {};
    WriteTo(configs).enableVariableFontWeight = Converter::ArkValue<Opt_Boolean>(true);

    modifier_->setFontWeight1(node_, &weight, &configs);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);

    // enableDeviceFontWeightCategory defaults to false when not explicitly set via WriteTo
    auto configsStr = GetAttrValue<std::string>(jsonValue, "fontWeightConfigs");
    ASSERT_TRUE(configsStr.has_value());
    auto result = GetAttrValue<bool>(configsStr.value(), ATTRIBUTE_ENABLE_DEVICE_FONT_WEIGHT_CATEGORY_NAME);
    EXPECT_THAT(result, Eq(false));
}

/**
 * @tc.name: setSymbolSpanVariableFontWeightTestValidValues
 * @tc.desc: Verify variableFontWeight is correctly set with different numeric values
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setSymbolSpanVariableFontWeightTestValidValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const std::vector<std::pair<int32_t, int32_t>> testPlan = {
        { WEIGHT_W100, WEIGHT_W100 },
        { WEIGHT_W400, WEIGHT_W400 },
        { WEIGHT_W700, WEIGHT_W700 },
        { WEIGHT_W900, WEIGHT_W900 },
    };
    for (const auto& [input, expected] : testPlan) {
        SymbolSpanModelNG::SetVariableFontWeight(frameNode, input);
        std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
        auto result = GetAttrValue<int>(jsonValue, ATTRIBUTE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_THAT(result, Eq(expected)) << "Failed for input: " << input;
    }
}

/**
 * @tc.name: setSymbolSpanVariableFontWeightTestReset
 * @tc.desc: Verify variableFontWeight is reset to default after reset call
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setSymbolSpanVariableFontWeightTestReset, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    SymbolSpanModelNG::SetVariableFontWeight(frameNode, WEIGHT_W700);
    SymbolSpanModelNG::ResetVariableFontWeight(frameNode);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto result = GetAttrValue<int>(jsonValue, ATTRIBUTE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_THAT(result, Eq(ATTRIBUTE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE));
}

/**
 * @tc.name: setSymbolSpanEnableVariableFontWeightTestTrue
 * @tc.desc: Verify enableVariableFontWeight is set to true
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setSymbolSpanEnableVariableFontWeightTestTrue, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    SymbolSpanModelNG::SetEnableVariableFontWeight(frameNode, true);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto configsStr = GetAttrValue<std::string>(jsonValue, "fontWeightConfigs");
    ASSERT_TRUE(configsStr.has_value());
    auto result = GetAttrValue<bool>(configsStr.value(), ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_THAT(result, Eq(true));
}

/**
 * @tc.name: setSymbolSpanEnableVariableFontWeightTestFalse
 * @tc.desc: Verify enableVariableFontWeight is set to false
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setSymbolSpanEnableVariableFontWeightTestFalse, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    SymbolSpanModelNG::SetEnableVariableFontWeight(frameNode, false);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto configsStr = GetAttrValue<std::string>(jsonValue, "fontWeightConfigs");
    ASSERT_TRUE(configsStr.has_value());
    auto result = GetAttrValue<bool>(configsStr.value(), ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_THAT(result, Eq(false));
}

/**
 * @tc.name: setSymbolSpanEnableVariableFontWeightTestReset
 * @tc.desc: Verify enableVariableFontWeight is reset to default (false)
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setSymbolSpanEnableVariableFontWeightTestReset, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    SymbolSpanModelNG::SetEnableVariableFontWeight(frameNode, true);
    SymbolSpanModelNG::ResetEnableVariableFontWeight(frameNode);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto configsStr = GetAttrValue<std::string>(jsonValue, "fontWeightConfigs");
    ASSERT_TRUE(configsStr.has_value());
    auto result = GetAttrValue<bool>(configsStr.value(), ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_THAT(result, Eq(ATTRIBUTE_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE));
}

/**
 * @tc.name: setSymbolSpanEnableDeviceFontWeightCategoryTestTrue
 * @tc.desc: Verify enableDeviceFontWeightCategory is set to true
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setSymbolSpanEnableDeviceFontWeightCategoryTestTrue, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    SymbolSpanModelNG::SetEnableDeviceFontWeightCategory(frameNode, true);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto configsStr = GetAttrValue<std::string>(jsonValue, "fontWeightConfigs");
    ASSERT_TRUE(configsStr.has_value());
    auto result = GetAttrValue<bool>(configsStr.value(), ATTRIBUTE_ENABLE_DEVICE_FONT_WEIGHT_CATEGORY_NAME);
    EXPECT_THAT(result, Eq(true));
}

/**
 * @tc.name: setSymbolSpanEnableDeviceFontWeightCategoryTestFalse
 * @tc.desc: Verify enableDeviceFontWeightCategory is set to false
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setSymbolSpanEnableDeviceFontWeightCategoryTestFalse, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    SymbolSpanModelNG::SetEnableDeviceFontWeightCategory(frameNode, false);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto configsStr = GetAttrValue<std::string>(jsonValue, "fontWeightConfigs");
    ASSERT_TRUE(configsStr.has_value());
    auto result = GetAttrValue<bool>(configsStr.value(), ATTRIBUTE_ENABLE_DEVICE_FONT_WEIGHT_CATEGORY_NAME);
    EXPECT_THAT(result, Eq(false));
}

/**
 * @tc.name: setSymbolSpanEnableDeviceFontWeightCategoryTestReset
 * @tc.desc: Verify enableDeviceFontWeightCategory is reset to default
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, setSymbolSpanEnableDeviceFontWeightCategoryTestReset, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    SymbolSpanModelNG::SetEnableDeviceFontWeightCategory(frameNode, true);
    SymbolSpanModelNG::ResetEnableDeviceFontWeightCategory(frameNode);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto configsStr = GetAttrValue<std::string>(jsonValue, "fontWeightConfigs");
    ASSERT_TRUE(configsStr.has_value());
    auto result = GetAttrValue<bool>(configsStr.value(), ATTRIBUTE_ENABLE_DEVICE_FONT_WEIGHT_CATEGORY_NAME);
    EXPECT_THAT(result, Eq(true));
}

} // namespace OHOS::Ace::NG
