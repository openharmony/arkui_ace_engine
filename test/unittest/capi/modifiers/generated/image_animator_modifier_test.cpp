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
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_IMAGES_NAME = "images";
const auto ATTRIBUTE_IMAGES_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STATE_NAME = "state";
const auto ATTRIBUTE_STATE_DEFAULT_VALUE = "AnimationStatus.Initial";
const auto ATTRIBUTE_DURATION_NAME = "duration";
const auto ATTRIBUTE_DURATION_DEFAULT_VALUE = "1000";
const auto ATTRIBUTE_REVERSE_NAME = "reverse";
const auto ATTRIBUTE_REVERSE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_FIXED_SIZE_NAME = "fixedSize";
const auto ATTRIBUTE_FIXED_SIZE_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_FILL_MODE_NAME = "fillMode";
const auto ATTRIBUTE_FILL_MODE_DEFAULT_VALUE = "FillMode.Forwards";
const auto ATTRIBUTE_ITERATIONS_NAME = "iterations";
const auto ATTRIBUTE_ITERATIONS_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace

class ImageAnimatorModifierTest
    : public ModifierTestBase<GENERATED_ArkUIImageAnimatorModifier,
          &GENERATED_ArkUINodeModifiers::getImageAnimatorModifier, GENERATED_ARKUI_IMAGE_ANIMATOR> {
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
 * @tc.name: setImagesTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, DISABLED_setImagesTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IMAGES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IMAGES_DEFAULT_VALUE) << "Default value for attribute 'images'";
}

/*
 * @tc.name: setImagesTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, DISABLED_setImagesTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setStateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setStateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STATE_DEFAULT_VALUE) << "Default value for attribute 'state'";
}

/*
 * @tc.name: setStateTestStateValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setStateTestStateValidValues, TestSize.Level1)
{
    Ark_AnimationStatus initValueState;

    // Initial setup
    initValueState = std::get<1>(Fixtures::testFixtureEnumAnimationStatusValidValues[0]);

    auto checkValue = [this, &initValueState](
                          const std::string& input, const std::string& expectedStr, const Ark_AnimationStatus& value) {
        Ark_AnimationStatus inputValueState = initValueState;

        inputValueState = value;
        modifier_->setState(node_, inputValueState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setState, attribute: state";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumAnimationStatusValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setStateTestStateInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setStateTestStateInvalidValues, TestSize.Level1)
{
    Ark_AnimationStatus initValueState;

    // Initial setup
    initValueState = std::get<1>(Fixtures::testFixtureEnumAnimationStatusValidValues[0]);

    auto checkValue = [this, &initValueState](const std::string& input, const Ark_AnimationStatus& value) {
        Ark_AnimationStatus inputValueState = initValueState;

        modifier_->setState(node_, inputValueState);
        inputValueState = value;
        modifier_->setState(node_, inputValueState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STATE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setState, attribute: state";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumAnimationStatusInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setDurationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setDurationTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DURATION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DURATION_DEFAULT_VALUE) << "Default value for attribute 'duration'";
}

/*
 * @tc.name: setDurationTestDurationValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setDurationTestDurationValidValues, TestSize.Level1)
{
    Ark_Number initValueDuration;

    // Initial setup
    initValueDuration = std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueDuration](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueDuration = initValueDuration;

        inputValueDuration = value;
        modifier_->setDuration(node_, &inputValueDuration);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DURATION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDuration, attribute: duration";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setDurationTestDurationInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setDurationTestDurationInvalidValues, TestSize.Level1)
{
    Ark_Number initValueDuration;

    // Initial setup
    initValueDuration = std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueDuration](const std::string& input, const Ark_Number& value) {
        Ark_Number inputValueDuration = initValueDuration;

        modifier_->setDuration(node_, &inputValueDuration);
        inputValueDuration = value;
        modifier_->setDuration(node_, &inputValueDuration);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DURATION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DURATION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDuration, attribute: duration";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberNonNegIntFloorInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setReverseTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setReverseTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REVERSE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_REVERSE_DEFAULT_VALUE) << "Default value for attribute 'reverse'";
}

/*
 * @tc.name: setReverseTestReverseValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setReverseTestReverseValidValues, TestSize.Level1)
{
    Ark_Boolean initValueReverse;

    // Initial setup
    initValueReverse = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueReverse](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueReverse = initValueReverse;

        inputValueReverse = value;
        modifier_->setReverse(node_, inputValueReverse);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REVERSE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setReverse, attribute: reverse";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setFixedSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setFixedSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FIXED_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FIXED_SIZE_DEFAULT_VALUE) << "Default value for attribute 'fixedSize'";
}

/*
 * @tc.name: setFixedSizeTestFixedSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setFixedSizeTestFixedSizeValidValues, TestSize.Level1)
{
    Ark_Boolean initValueFixedSize;

    // Initial setup
    initValueFixedSize = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueFixedSize](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueFixedSize = initValueFixedSize;

        inputValueFixedSize = value;
        modifier_->setFixedSize(node_, inputValueFixedSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FIXED_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFixedSize, attribute: fixedSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setFillModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setFillModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FILL_MODE_DEFAULT_VALUE) << "Default value for attribute 'fillMode'";
}

/*
 * @tc.name: setFillModeTestFillModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setFillModeTestFillModeValidValues, TestSize.Level1)
{
    Ark_FillMode initValueFillMode;

    // Initial setup
    initValueFillMode = std::get<1>(Fixtures::testFixtureEnumFillModeValidValues[0]);

    auto checkValue = [this, &initValueFillMode](
                          const std::string& input, const std::string& expectedStr, const Ark_FillMode& value) {
        Ark_FillMode inputValueFillMode = initValueFillMode;

        inputValueFillMode = value;
        modifier_->setFillMode(node_, inputValueFillMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFillMode, attribute: fillMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFillModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setFillModeTestFillModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setFillModeTestFillModeInvalidValues, TestSize.Level1)
{
    Ark_FillMode initValueFillMode;

    // Initial setup
    initValueFillMode = std::get<1>(Fixtures::testFixtureEnumFillModeValidValues[0]);

    auto checkValue = [this, &initValueFillMode](const std::string& input, const Ark_FillMode& value) {
        Ark_FillMode inputValueFillMode = initValueFillMode;

        modifier_->setFillMode(node_, inputValueFillMode);
        inputValueFillMode = value;
        modifier_->setFillMode(node_, inputValueFillMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FILL_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFillMode, attribute: fillMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFillModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setIterationsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, DISABLED_setIterationsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ITERATIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ITERATIONS_DEFAULT_VALUE) << "Default value for attribute 'iterations'";
}

/*
 * @tc.name: setIterationsTestIterationsValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, DISABLED_setIterationsTestIterationsValidValues, TestSize.Level1)
{
    Ark_Number initValueIterations;

    // Initial setup
    initValueIterations = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueIterations](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueIterations = initValueIterations;

        inputValueIterations = value;
        modifier_->setIterations(node_, &inputValueIterations);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ITERATIONS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setIterations, attribute: iterations";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, value);
    }
}
} // namespace OHOS::Ace::NG
