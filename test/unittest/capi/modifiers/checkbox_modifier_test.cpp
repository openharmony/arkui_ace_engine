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
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_SELECT_NAME = "select";
    const auto ATTRIBUTE_SELECT_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_SELECTED_COLOR_NAME = "selectedColor";
    const auto ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto ATTRIBUTE_SHAPE_NAME = "shape";
    const auto ATTRIBUTE_SHAPE_DEFAULT_VALUE = "CheckBoxShape.CIRCLE";
    const auto ATTRIBUTE_UNSELECTED_COLOR_NAME = "unselectedColor";
    const auto ATTRIBUTE_UNSELECTED_COLOR_DEFAULT_VALUE = "#FF000000";
} // namespace

class CheckboxModifierTest : public ModifierTestBase<GENERATED_ArkUICheckboxModifier,
    &GENERATED_ArkUINodeModifiers::getCheckboxModifier, GENERATED_ARKUI_CHECKBOX> {
};

/*
 * @tc.name: setSelectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setSelectTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECT_DEFAULT_VALUE);
}

// Valid values for attribute 'select' of method 'select'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> selectSelectValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setSelectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setSelectTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueSelect;
    Ark_Boolean initValueSelect;

    // Initial setup
    initValueSelect = std::get<1>(selectSelectValidValues[0]);

    // Verifying attribute's  values
    inputValueSelect = initValueSelect;
    for (auto&& value: selectSelectValidValues) {
        inputValueSelect = std::get<1>(value);
        modifier_->setSelect(node_, inputValueSelect);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setSelectedColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setSelectedColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'selectedColor' of method 'selectedColor'
static std::vector<std::tuple<std::string, ResourceColor, std::string>> selectedColorSelectedColorValidValues = {
    { "blue", Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { "red", Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
};

/*
 * @tc.name: setSelectedColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setSelectedColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    ResourceColor inputValueSelectedColor;
    ResourceColor initValueSelectedColor;

    // Initial setup
    initValueSelectedColor = std::get<1>(selectedColorSelectedColorValidValues[0]);
    modifier_->setSelect(node_, Converter::ArkValue<Ark_Boolean>(true));

    // Verifying attribute's  values
    inputValueSelectedColor = initValueSelectedColor;
    for (auto&& value: selectedColorSelectedColorValidValues) {
        inputValueSelectedColor = std::get<1>(value);
        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setSelectedColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setSelectedColorTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    ResourceColor initValueSelectedColor;

    // Initial setup
    initValueSelectedColor = std::get<1>(selectedColorSelectedColorValidValues[0]);
}

/*
 * @tc.name: setShapeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setShapeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHAPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHAPE_DEFAULT_VALUE);
}

// Valid values for attribute 'shape' of method 'shape'
static std::vector<std::tuple<std::string, enum Ark_CheckBoxShape, std::string>> shapeShapeValidValues = {
    {"ARK_CHECK_BOX_SHAPE_CIRCLE",
        Converter::ArkValue<enum Ark_CheckBoxShape>(ARK_CHECK_BOX_SHAPE_CIRCLE),
        "CheckBoxShape.CIRCLE"},
    {"ARK_CHECK_BOX_SHAPE_ROUNDED_SQUARE",
        Converter::ArkValue<enum Ark_CheckBoxShape>(ARK_CHECK_BOX_SHAPE_ROUNDED_SQUARE),
        "CheckBoxShape.ROUNDED_SQUARE"},
};

/*
 * @tc.name: setShapeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setShapeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_CheckBoxShape inputValueShape;
    Ark_CheckBoxShape initValueShape;

    // Initial setup
    initValueShape = std::get<1>(shapeShapeValidValues[0]);

    // Verifying attribute's  values
    inputValueShape = initValueShape;
    for (auto&& value: shapeShapeValidValues) {
        inputValueShape = std::get<1>(value);
        modifier_->setShape(node_, inputValueShape);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHAPE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'shape' of method 'shape'
static std::vector<std::tuple<std::string, enum Ark_CheckBoxShape>> shapeShapeInvalidValues = {
    {"static_cast<enum Ark_CheckBoxShape>(-1)",
        Converter::ArkValue<enum Ark_CheckBoxShape>(static_cast<enum Ark_CheckBoxShape>(-1))},
};

/*
 * @tc.name: setShapeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setShapeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    enum Ark_CheckBoxShape inputValueShape;
    enum Ark_CheckBoxShape initValueShape;

    // Initial setup
    initValueShape = std::get<1>(shapeShapeValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: shapeShapeInvalidValues) {
        inputValueShape = initValueShape;
        modifier_->setShape(node_, inputValueShape);
        inputValueShape = std::get<1>(value);
        modifier_->setShape(node_, inputValueShape);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHAPE_NAME);
        expectedStr = ATTRIBUTE_SHAPE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setUnselectedColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setUnselectedColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNSELECTED_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_UNSELECTED_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'unselectedColor' of method 'unselectedColor'
static std::vector<std::tuple<std::string, ResourceColor, std::string>> unselectedColorUnselectedColorValidValues = {
};

/*
 * @tc.name: setUnselectedColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setUnselectedColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    ResourceColor inputValueUnselectedColor;
    ResourceColor initValueUnselectedColor;

    // Initial setup
    initValueUnselectedColor = std::get<1>(unselectedColorUnselectedColorValidValues[0]);

    // Verifying attribute's  values
    inputValueUnselectedColor = initValueUnselectedColor;
    for (auto&& value: unselectedColorUnselectedColorValidValues) {
        inputValueUnselectedColor = std::get<1>(value);
        modifier_->setUnselectedColor(node_, &inputValueUnselectedColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNSELECTED_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setUnselectedColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setUnselectedColorTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    ResourceColor initValueUnselectedColor;

    // Initial setup
    initValueUnselectedColor = std::get<1>(unselectedColorUnselectedColorValidValues[0]);
}

} // namespace OHOS::Ace::NG
