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

#include "image_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Image;
/*
 * @tc.name: setOrientationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setOrientationTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ORIENTATION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ORIENTATION_DEFAULT_VALUE) << "Default value for attribute 'orientation'";
}

/*
 * @tc.name: setOrientationTestOrientationValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setOrientationTestOrientationValidValues, TestSize.Level1)
{
    Ark_ImageRotateOrientation initValueOrientation;

    // Initial setup
    initValueOrientation = std::get<1>(Fixtures::testFixtureEnumImageRotateOrientationValidValues[0]);

    auto checkValue = [this, &initValueOrientation](const std::string& input, const std::string& expectedStr,
                          const Ark_ImageRotateOrientation& value) {
        Ark_ImageRotateOrientation inputValueOrientation = initValueOrientation;

        inputValueOrientation = value;
        modifier_->setOrientation(node_, inputValueOrientation);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ORIENTATION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOrientation, attribute: orientation";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumImageRotateOrientationValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setOrientationTestOrientationInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setOrientationTestOrientationInvalidValues, TestSize.Level1)
{
    Ark_ImageRotateOrientation initValueOrientation;

    // Initial setup
    initValueOrientation = std::get<1>(Fixtures::testFixtureEnumImageRotateOrientationValidValues[0]);

    auto checkValue = [this, &initValueOrientation](const std::string& input, const Ark_ImageRotateOrientation& value) {
        Ark_ImageRotateOrientation inputValueOrientation = initValueOrientation;

        modifier_->setOrientation(node_, inputValueOrientation);
        inputValueOrientation = value;
        modifier_->setOrientation(node_, inputValueOrientation);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ORIENTATION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ORIENTATION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setOrientation, attribute: orientation";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumImageRotateOrientationInvalidValues) {
        checkValue(input, value);
    }
}
} // namespace OHOS::Ace::NG
