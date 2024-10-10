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
#include "generated/test_fixtures.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_FILL_COLOR_NAME = "fillColor";
    const auto ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE = "#FF000000";
    // const auto OPACITY_COLOR = "#FF000000";
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

    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_String>(std::get<1>(value)), std::get<2>(value));
    }
    // for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
    //     checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_String>(std::get<1>(value)), OPACITY_COLOR);
    // }
    // for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
    //     checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_Number>(std::get<1>(value)), std::get<2>(value));
    // }
    // for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
    //     checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_Resource>(std::get<1>(value)), std::get<2>(value));
    // }
    // for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
    //     checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_Color>(std::get<1>(value)), std::get<2>(value));
    // }
    // for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
    //     checkValue(std::get<0>(value), Converter::ArkUnion<ResourceColor, Ark_Color>(std::get<1>(value)), ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE);
    // }
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
