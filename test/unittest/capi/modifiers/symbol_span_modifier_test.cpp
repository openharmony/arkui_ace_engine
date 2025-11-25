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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

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
const auto ATTRIBUTE_UNICODE_NAME = "unicode";
const auto ATTRIBUTE_UNICODE_NAME_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_SYMBOL_COLOR_NAME = "SymbolColor";

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
        EXPECT_EQ(resultStr, expectedStr) <<
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
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNICODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_UNICODE_NAME_DEFAULT_VALUE) << "Default value for attribute 'value.id'";
}

static const std::vector<std::pair<Ark_ResourceColor, std::string>> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
};

/*
 * @tc.name: setResizeableTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolSpanModifierTest, DISABLED_setFontColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
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
    EXPECT_EQ(resultStr, symbolColorStr) << "Passed value is: " << symbolColorStr;
}

} // namespace OHOS::Ace::NG
