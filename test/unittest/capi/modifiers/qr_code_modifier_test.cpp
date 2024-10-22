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
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "generated/test_fixtures.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_COLOR_NAME = "color";
    const auto ATTRIBUTE_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
    const auto ATTRIBUTE_BACKGROUND_COLOR_NAME = "backgroundColor";
    const auto ATTRIBUTE_BACKGROUND_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace

class QRCodeModifierTest : public ModifierTestBase<GENERATED_ArkUIQRCodeModifier, &GENERATED_ArkUINodeModifiers::getQRCodeModifier, GENERATED_ARKUI_QRCODE> {
};

// TODO: Process non-options argument in setOptions function

/*
 * @tc.name: setColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, setColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'color' of method 'color'
static std::vector<std::tuple<std::string, ResourceColor, std::string>> colorColorValidValues = {
};

/*
 * @tc.name: setColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, setColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    ResourceColor inputValueColor;
    ResourceColor initValueColor;

    // Initial setup
    initValueColor = std::get<1>(colorColorValidValues[0]);

    // Verifying attribute's  values
    inputValueColor = initValueColor;
    for (auto&& value: colorColorValidValues) {
        inputValueColor = std::get<1>(value);
        modifier_->setColor(node_, &inputValueColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, setColorTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    ResourceColor inputValueColor;
    ResourceColor initValueColor;

    // Initial setup
    initValueColor = std::get<1>(colorColorValidValues[0]);
}

/*
 * @tc.name: setBackgroundColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, setBackgroundColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BACKGROUND_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'backgroundColor' of method 'backgroundColor'
static std::vector<std::tuple<std::string, ResourceColor, std::string>> backgroundColorBackgroundColorValidValues = {
};

/*
 * @tc.name: setBackgroundColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, setBackgroundColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    ResourceColor inputValueBackgroundColor;
    ResourceColor initValueBackgroundColor;

    // Initial setup
    initValueBackgroundColor = std::get<1>(backgroundColorBackgroundColorValidValues[0]);

    // Verifying attribute's  values
    inputValueBackgroundColor = initValueBackgroundColor;
    for (auto&& value: backgroundColorBackgroundColorValidValues) {
        inputValueBackgroundColor = std::get<1>(value);
        modifier_->setBackgroundColor(node_, &inputValueBackgroundColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACKGROUND_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBackgroundColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeModifierTest, setBackgroundColorTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    ResourceColor inputValueBackgroundColor;
    ResourceColor initValueBackgroundColor;

    // Initial setup
    initValueBackgroundColor = std::get<1>(backgroundColorBackgroundColorValidValues[0]);
}
} // namespace OHOS::Ace::NG
