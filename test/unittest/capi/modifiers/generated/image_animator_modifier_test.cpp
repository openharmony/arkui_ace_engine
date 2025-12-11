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

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
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
const auto ATTRIBUTE_ITERATIONS_DEFAULT_VALUE = "1";
const auto ATTRIBUTE_MONITOR_INVISIBLE_AREA_NAME = "monitorInvisibleArea";
const auto ATTRIBUTE_MONITOR_INVISIBLE_AREA_DEFAULT_VALUE = "false";
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
 * @tc.name: setImagesTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, DISABLED_setImagesTestPlaceholder, TestSize.Level1)
{
    FAIL() << "This is placeholder to have disabled test";
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
    Opt_AnimationStatus initValueState;

    // Initial setup
    initValueState = ArkValue<Opt_AnimationStatus>(std::get<1>(Fixtures::testFixtureEnumAnimationStatusValidValues[0]));

    auto checkValue = [this, &initValueState](
                          const std::string& input, const std::string& expectedStr, const Opt_AnimationStatus& value) {
        Opt_AnimationStatus inputValueState = initValueState;

        inputValueState = value;
        modifier_->setState(node_, &inputValueState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setState, attribute: state";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumAnimationStatusValidValues) {
        checkValue(input, expected, ArkValue<Opt_AnimationStatus>(value));
    }
}

/*
 * @tc.name: setStateTestStateInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setStateTestStateInvalidValues, TestSize.Level1)
{
    Opt_AnimationStatus initValueState;

    // Initial setup
    initValueState = ArkValue<Opt_AnimationStatus>(std::get<1>(Fixtures::testFixtureEnumAnimationStatusValidValues[0]));

    auto checkValue = [this, &initValueState](const std::string& input, const Opt_AnimationStatus& value) {
        Opt_AnimationStatus inputValueState = initValueState;

        modifier_->setState(node_, &inputValueState);
        inputValueState = value;
        modifier_->setState(node_, &inputValueState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STATE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setState, attribute: state";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumAnimationStatusInvalidValues) {
        checkValue(input, ArkValue<Opt_AnimationStatus>(value));
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
    Opt_Number initValueDuration;

    // Initial setup
    initValueDuration = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));

    auto checkValue = [this, &initValueDuration](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueDuration = initValueDuration;

        inputValueDuration = value;
        modifier_->setDuration(node_, &inputValueDuration);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DURATION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDuration, attribute: duration";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setDurationTestDurationInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setDurationTestDurationInvalidValues, TestSize.Level1)
{
    Opt_Number initValueDuration;

    // Initial setup
    initValueDuration = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));

    auto checkValue = [this, &initValueDuration](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueDuration = initValueDuration;

        modifier_->setDuration(node_, &inputValueDuration);
        inputValueDuration = value;
        modifier_->setDuration(node_, &inputValueDuration);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DURATION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DURATION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDuration, attribute: duration";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberNonNegIntFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
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
    Opt_Boolean initValueReverse;

    // Initial setup
    initValueReverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueReverse](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueReverse = initValueReverse;

        inputValueReverse = value;
        modifier_->setReverse(node_, &inputValueReverse);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REVERSE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setReverse, attribute: reverse";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setReverseTestReverseInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, DISABLED_setReverseTestReverseInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueReverse;

    // Initial setup
    initValueReverse = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueReverse](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueReverse = initValueReverse;

        modifier_->setReverse(node_, &inputValueReverse);
        inputValueReverse = value;
        modifier_->setReverse(node_, &inputValueReverse);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REVERSE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_REVERSE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setReverse, attribute: reverse";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
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
    Opt_Boolean initValueFixedSize;

    // Initial setup
    initValueFixedSize = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFixedSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueFixedSize = initValueFixedSize;

        inputValueFixedSize = value;
        modifier_->setFixedSize(node_, &inputValueFixedSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FIXED_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFixedSize, attribute: fixedSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setFixedSizeTestFixedSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setFixedSizeTestFixedSizeInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueFixedSize;

    // Initial setup
    initValueFixedSize = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFixedSize](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueFixedSize = initValueFixedSize;

        modifier_->setFixedSize(node_, &inputValueFixedSize);
        inputValueFixedSize = value;
        modifier_->setFixedSize(node_, &inputValueFixedSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FIXED_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FIXED_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFixedSize, attribute: fixedSize";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
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
    Opt_FillMode initValueFillMode;

    // Initial setup
    initValueFillMode = ArkValue<Opt_FillMode>(std::get<1>(Fixtures::testFixtureEnumFillModeValidValues[0]));

    auto checkValue = [this, &initValueFillMode](
                          const std::string& input, const std::string& expectedStr, const Opt_FillMode& value) {
        Opt_FillMode inputValueFillMode = initValueFillMode;

        inputValueFillMode = value;
        modifier_->setFillMode(node_, &inputValueFillMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFillMode, attribute: fillMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFillModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_FillMode>(value));
    }
}

/*
 * @tc.name: setFillModeTestFillModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setFillModeTestFillModeInvalidValues, TestSize.Level1)
{
    Opt_FillMode initValueFillMode;

    // Initial setup
    initValueFillMode = ArkValue<Opt_FillMode>(std::get<1>(Fixtures::testFixtureEnumFillModeValidValues[0]));

    auto checkValue = [this, &initValueFillMode](const std::string& input, const Opt_FillMode& value) {
        Opt_FillMode inputValueFillMode = initValueFillMode;

        modifier_->setFillMode(node_, &inputValueFillMode);
        inputValueFillMode = value;
        modifier_->setFillMode(node_, &inputValueFillMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FILL_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFillMode, attribute: fillMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFillModeInvalidValues) {
        checkValue(input, ArkValue<Opt_FillMode>(value));
    }
}

/*
 * @tc.name: setIterationsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setIterationsTestDefaultValues, TestSize.Level1)
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
    Opt_Number initValueIterations;

    // Initial setup
    initValueIterations = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));

    auto checkValue = [this, &initValueIterations](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueIterations = initValueIterations;

        inputValueIterations = value;
        modifier_->setIterations(node_, &inputValueIterations);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ITERATIONS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setIterations, attribute: iterations";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberPosIntFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setIterationsTestIterationsInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setIterationsTestIterationsInvalidValues, TestSize.Level1)
{
    Opt_Number initValueIterations;

    // Initial setup
    initValueIterations = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));

    auto checkValue = [this, &initValueIterations](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueIterations = initValueIterations;

        modifier_->setIterations(node_, &inputValueIterations);
        inputValueIterations = value;
        modifier_->setIterations(node_, &inputValueIterations);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ITERATIONS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ITERATIONS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setIterations, attribute: iterations";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberPosIntFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setMonitorInvisibleAreaTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setMonitorInvisibleAreaTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MONITOR_INVISIBLE_AREA_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MONITOR_INVISIBLE_AREA_DEFAULT_VALUE) <<
        "Default value for attribute 'monitorInvisibleArea'";
}

/*
 * @tc.name: setMonitorInvisibleAreaTestMonitorInvisibleAreaValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModifierTest, setMonitorInvisibleAreaTestMonitorInvisibleAreaValidValues, TestSize.Level1)
{
    Opt_Boolean initValueMonitorInvisibleArea;

    // Initial setup
    initValueMonitorInvisibleArea = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueMonitorInvisibleArea](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueMonitorInvisibleArea = initValueMonitorInvisibleArea;

        inputValueMonitorInvisibleArea = value;
        modifier_->setMonitorInvisibleArea(node_, &inputValueMonitorInvisibleArea);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MONITOR_INVISIBLE_AREA_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMonitorInvisibleArea, attribute: monitorInvisibleArea";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setMonitorInvisibleAreaTestMonitorInvisibleAreaInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    ImageAnimatorModifierTest, DISABLED_setMonitorInvisibleAreaTestMonitorInvisibleAreaInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueMonitorInvisibleArea;

    // Initial setup
    initValueMonitorInvisibleArea = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueMonitorInvisibleArea](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueMonitorInvisibleArea = initValueMonitorInvisibleArea;

        modifier_->setMonitorInvisibleArea(node_, &inputValueMonitorInvisibleArea);
        inputValueMonitorInvisibleArea = value;
        modifier_->setMonitorInvisibleArea(node_, &inputValueMonitorInvisibleArea);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MONITOR_INVISIBLE_AREA_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MONITOR_INVISIBLE_AREA_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMonitorInvisibleArea, attribute: monitorInvisibleArea";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}
} // namespace OHOS::Ace::NG
