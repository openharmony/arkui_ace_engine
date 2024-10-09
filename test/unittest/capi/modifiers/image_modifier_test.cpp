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
#include <tuple>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_FILL_COLOR_NAME = "fillColor";
    const auto ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto ATTRIBUTE_AUTO_RESIZE_NAME = "autoResize";
    const auto ATTRIBUTE_AUTO_RESIZE_DEFAULT_VALUE = "false";
} // namespace

inline constexpr auto COLORS_RES_0_STR = "COLORS_RES_0_STR";

enum ResID {
    COLORS_RES_0_ID,
};

// Valid values for attribute 'fillColor' of method 'fillColor'
std::vector<std::tuple<ResID, std::string, ResRawValue>> resourceInitTable = {
    { COLORS_RES_0_ID, COLORS_RES_0_STR, Color(0xA1FAC0DE) },
};

class ImageModifierTest : public ModifierTestBase<GENERATED_ArkUIImageModifier, &GENERATED_ArkUINodeModifiers::getImageModifier, GENERATED_ARKUI_IMAGE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();    
        for (auto&& res : resourceInitTable) {
            AddResource(std::get<0>(res), std::get<2>(res)); // 2 - index of resource
            AddResource(std::get<1>(res), std::get<2>(res)); // 2 - index of resource
        }
    }
};
/*
 * @tc.name: setFillColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setFillColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE);
}

// Fixture 'ColorsStr' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureColorsStrValidValues = {
    { "\"#123\"", Converter::ArkValue<Ark_String>("#123"), "#FF112233" },
    { "\"#11223344\"", Converter::ArkValue<Ark_String>("#11223344"), "#11223344" },
    { "\"#123456\"", Converter::ArkValue<Ark_String>("#123456"), "#FF123456" },
    { "\"65535\"", Converter::ArkValue<Ark_String>("65535"), "#FF00FFFF" },
};

std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureColorsStrInvalidValues = {
    { "\"invalid\"", Converter::ArkValue<Ark_String>("invalid"), ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE },
    { "\"\"", Converter::ArkValue<Ark_String>(""), "#00000000" },
};

// Fixture 'ColorsNum' for type 'Ark_Number'
std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureColorsNumValidValues = {
    { "0", Converter::ArkValue<Ark_Number>(0), "#00000000" },
    { "1", Converter::ArkValue<Ark_Number>(1), "#FF000001" },
    { "65535", Converter::ArkValue<Ark_Number>(65535), "#FF00FFFF" },
    { "-1", Converter::ArkValue<Ark_Number>(-1), "#FFFFFFFF" },
    { "0xBE7AC0DE", Converter::ArkValue<Ark_Number>(0xBE7AC0DE), "#BE7AC0DE" },
};

// Fixture 'ColorsRes' for type 'Ark_Resource'
std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureColorsResValidValues = {
    { "ResId:COLORS_RES_0_ID", CreateResource(COLORS_RES_0_ID, NodeModifier::ResourceType::COLOR), "#A1FAC0DE" },
    { "ResName:COLORS_RES_0_STR", CreateResource(COLORS_RES_0_STR, NodeModifier::ResourceType::COLOR), "#A1FAC0DE" },
};

// Fixture 'ColorsEnum' for type 'Ark_Color'
std::vector<std::tuple<std::string, Ark_Color, std::string>> testFixtureColorsEnumValidValues = {
    { "ARK_COLOR_WHITE", Converter::ArkValue<Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
    { "ARK_COLOR_BLACK", Converter::ArkValue<Ark_Color>(ARK_COLOR_BLACK), "#FF000000" },
    { "ARK_COLOR_BLUE", Converter::ArkValue<Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { "ARK_COLOR_BROWN", Converter::ArkValue<Ark_Color>(ARK_COLOR_BROWN), "#FFA52A2A" },
    { "ARK_COLOR_GRAY", Converter::ArkValue<Ark_Color>(ARK_COLOR_GRAY), "#FF808080" },
    { "ARK_COLOR_GREEN", Converter::ArkValue<Ark_Color>(ARK_COLOR_GREEN), "#FF008000" },
    { "ARK_COLOR_GREY", Converter::ArkValue<Ark_Color>(ARK_COLOR_GREY), "#FF808080" },
    { "ARK_COLOR_ORANGE", Converter::ArkValue<Ark_Color>(ARK_COLOR_ORANGE), "#FFFFA500" },
    { "ARK_COLOR_PINK", Converter::ArkValue<Ark_Color>(ARK_COLOR_PINK), "#FFFFC0CB" },
    { "ARK_COLOR_RED", Converter::ArkValue<Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
    { "ARK_COLOR_YELLOW", Converter::ArkValue<Ark_Color>(ARK_COLOR_YELLOW), "#FFFFFF00" },
    { "ARK_COLOR_TRANSPARENT", Converter::ArkValue<Ark_Color>(ARK_COLOR_TRANSPARENT), "#00000000" },
};

std::vector<std::tuple<std::string, Ark_Color>> testFixtureColorsEnumInvalidValues = {
    { "static_cast<Ark_Color>(-1)", Converter::ArkValue<Ark_Color>(static_cast<Ark_Color>(-1)) },
    { "static_cast<Ark_Color>(INT_MAX)", Converter::ArkValue<Ark_Color>(static_cast<Ark_Color>(INT_MAX)) },
};
/*
 * @tc.name: setFillColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setFillColorTestValidValues, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input, const ResourceColor& value, const std::string& expectedStr) {
        modifier_->setFillColor(node_, &value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << input;
    };

    for (auto&& value : testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_String>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : testFixtureColorsStrInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_String>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : testFixtureColorsNumValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_Number>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : testFixtureColorsResValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_Resource>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : testFixtureColorsEnumValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_Color>(std::get<1>(value)), std::get<2>(value));
    }
    for (auto&& value : testFixtureColorsEnumInvalidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_Color>(std::get<1>(value)), ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setAutoResizeTestDefaultValues
 * @tc.desc: 
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setAutoResizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_RESIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_RESIZE_DEFAULT_VALUE);
}

// Valid values for attribute 'autoResize' of method 'autoResize'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> autoResizeAutoResizeValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setAutoResizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setAutoResizeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueAutoResize;
    Ark_Boolean initValueAutoResize;

    // Initial setup
    initValueAutoResize = std::get<1>(autoResizeAutoResizeValidValues[0]);

    // Verifying attribute's  values
    inputValueAutoResize = initValueAutoResize;
    for (auto&& value: autoResizeAutoResizeValidValues) {
        inputValueAutoResize = std::get<1>(value);
        modifier_->setAutoResize(node_, inputValueAutoResize);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_RESIZE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: DISABLED_setOnErrorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setOnErrorTest, TestSize.Level1)
{
    // TODO: Implement callback tests!
}

/*
 * @tc.name: DISABLED_setOnFinishTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setOnFinishTest, TestSize.Level1)
{
    // TODO: Implement callback tests!
}
} // namespace OHOS::Ace::NG
