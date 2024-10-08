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
    const auto ATTRIBUTE_MARK_NAME = "mark";
    const auto ATTRIBUTE_OPTIONS_NAME = "options";
    const auto ATTRIBUTE_OPTIONS_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_SELECT_NAME = "select";
    const auto ATTRIBUTE_SELECT_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_SELECTED_COLOR_NAME = "selectedColor";
    const auto ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_SHAPE_NAME = "shape";
    const auto ATTRIBUTE_SHAPE_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_UNSELECTED_COLOR_NAME = "unselectedColor";
    const auto ATTRIBUTE_UNSELECTED_COLOR_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_MARK_STROKE_COLOR_NAME = "strokeColor";
    const auto ATTRIBUTE_MARK_STROKE_COLOR_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_MARK_SIZE_NAME = "size";
    const auto ATTRIBUTE_MARK_SIZE_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_MARK_STROKE_WIDTH_NAME = "strokeWidth";
    const auto ATTRIBUTE_MARK_STROKE_WIDTH_DEFAULT_VALUE = "";
} // namespace

class CheckboxModifierTest : public ModifierTestBase<GENERATED_ArkUICheckboxModifier, &GENERATED_ArkUINodeModifiers::getCheckboxModifier, GENERATED_ARKUI_CHECKBOX> {
};


/*
 * @tc.name: setCheckboxOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setCheckboxOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTIONS_DEFAULT_VALUE);
}

// Valid values for attribute 'options' of method 'setCheckboxOptions'
static std::vector<std::tuple<std::string, Opt_CheckboxOptions, std::string>> setCheckboxOptionsOptionsValidValues = {
};

/*
 * @tc.name: setCheckboxOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
/*HWTEST_F(CheckboxModifierTest, setCheckboxOptionsTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_CheckboxOptions realInputValue = {.tag = ARK_TAG_OBJECT, .value = {}};
    Ark_CheckboxOptions& inputValueOptions = realInputValue.value;
    Ark_CheckboxOptions initValueOptions;

    // Initial setup
    // TODO: Add processing for substructures!

    // Verifying attribute's  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setCheckboxOptionsOptionsValidValues) {
        inputValueOptions = std::get<1>(value);
        modifier_->setCheckboxOptions(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTIONS_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}*/

// Invalid values for attribute 'options' of method 'setCheckboxOptions'
static std::vector<std::tuple<std::string, Opt_CheckboxOptions>> setCheckboxOptionsOptionsInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_CheckboxOptions>(Ark_Empty())},
};

/*
 * @tc.name: setCheckboxOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
/*HWTEST_F(CheckboxModifierTest, setCheckboxOptionsTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_CheckboxOptions realInputValue = {.tag = ARK_TAG_OBJECT, .value = {}};
    Ark_CheckboxOptions& inputValueOptions = realInputValue.value;
    Ark_CheckboxOptions initValueOptions;

    // Initial setup
    // TODO: Add processing for substructures!

    // Verifying attribute's  values
    for (auto&& value: setCheckboxOptionsOptionsInvalidValues) {
        inputValueOptions = initValueOptions;
        modifier_->setCheckboxOptions(node_, &realInputValue);
        inputValueOptions = std::get<1>(value);
        modifier_->setCheckboxOptions(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OPTIONS_NAME);
        expectedStr = ATTRIBUTE_OPTIONS_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}*/

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
    {"ARK_CHECK_BOX_SHAPE_CIRCLE", Converter::ArkValue<enum Ark_CheckBoxShape>(ARK_CHECK_BOX_SHAPE_CIRCLE), "CheckBoxShape.CIRCLE"},
    {"ARK_CHECK_BOX_SHAPE_ROUNDED_SQUARE", Converter::ArkValue<enum Ark_CheckBoxShape>(ARK_CHECK_BOX_SHAPE_ROUNDED_SQUARE), "CheckBoxShape.ROUNDED_SQUARE"},
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
    enum Ark_CheckBoxShape inputValueShape;
    enum Ark_CheckBoxShape initValueShape;

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
    {"static_cast<enum Ark_CheckBoxShape>(-1)", Converter::ArkValue<enum Ark_CheckBoxShape>(static_cast<enum Ark_CheckBoxShape>(-1))},
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

/*
 * @tc.name: setMarkTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, setMarkTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultMark = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARK_STROKE_COLOR_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARK_SIZE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARK_STROKE_WIDTH_DEFAULT_VALUE);
}

// Valid values for attribute 'strokeColor' of method 'mark'
static std::vector<std::tuple<std::string, Opt_ResourceColor, std::string>> markStrokeColorValidValues = {
    {"\"#123456\"", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#123456"), "#FF123456"},
    {"0x11223344", Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0x11223344), "#11223344"},
    {"-1", Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(-1), "#FFFFFFFF"},
};

// Valid values for attribute 'size' of method 'mark'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> markSizeValidValues = {
};

// Valid values for attribute 'strokeWidth' of method 'mark'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> markStrokeWidthValidValues = {
};

/*
 * @tc.name: setMarkTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
/*HWTEST_F(CheckboxModifierTest, setMarkTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultMark;
    std::string resultStr;
    std::string expectedStr;
    Ark_MarkStyle inputValueMark;
    Ark_MarkStyle initValueMark;

    // Initial setup
    initValueMark.strokeColor = std::get<1>(markStrokeColorValidValues[0]);
    initValueMark.size = std::get<1>(markSizeValidValues[0]);
    initValueMark.strokeWidth = std::get<1>(markStrokeWidthValidValues[0]);

    // Verifying attribute's 'strokeColor'  values
    inputValueMark = initValueMark;
    for (auto&& value: markStrokeColorValidValues) {
        inputValueMark.strokeColor = std::get<1>(value);
        modifier_->setMark(node_, &inputValueMark);
        jsonValue = GetJsonValue(node_);
        resultMark = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_NAME);
        resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'size'  values
    inputValueMark = initValueMark;
    for (auto&& value: markSizeValidValues) {
        inputValueMark.size = std::get<1>(value);
        modifier_->setMark(node_, &inputValueMark);
        jsonValue = GetJsonValue(node_);
        resultMark = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_NAME);
        resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_SIZE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'strokeWidth'  values
    inputValueMark = initValueMark;
    for (auto&& value: markStrokeWidthValidValues) {
        inputValueMark.strokeWidth = std::get<1>(value);
        modifier_->setMark(node_, &inputValueMark);
        jsonValue = GetJsonValue(node_);
        resultMark = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_NAME);
        resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}*/

// Invalid values for attribute 'strokeColor' of method 'mark'
/*static std::vector<std::tuple<std::string, Opt_ResourceColor>> markStrokeColorInvalidValues = {
    {"Ark_Empty()", Converter::ArkUnion<Opt_ResourceColor>(Ark_Empty())},
    {"nullptr", Converter::ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr)},
};

// Invalid values for attribute 'size' of method 'mark'
static std::vector<std::tuple<std::string, Opt_Length>> markSizeInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Length>(Ark_Empty())},
};

// Invalid values for attribute 'strokeWidth' of method 'mark'
static std::vector<std::tuple<std::string, Opt_Length>> markStrokeWidthInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Length>(Ark_Empty())},
};*/

/*
 * @tc.name: setMarkTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
/*HWTEST_F(CheckboxModifierTest, setMarkTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultMark;
    std::string resultStr;
    std::string expectedStr;
    Ark_MarkStyle inputValueMark;
    Ark_MarkStyle initValueMark;

    // Initial setup
    initValueMark.strokeColor = std::get<1>(markStrokeColorValidValues[0]);
    initValueMark.size = std::get<1>(markSizeValidValues[0]);
    initValueMark.strokeWidth = std::get<1>(markStrokeWidthValidValues[0]);

    // Verifying attribute's 'strokeColor'  values
    for (auto&& value: markStrokeColorInvalidValues) {
        inputValueMark = initValueMark;
        modifier_->setMark(node_, &inputValueMark);
        inputValueMark.strokeColor = std::get<1>(value);
        modifier_->setMark(node_, &inputValueMark);
        jsonValue = GetJsonValue(node_);
        resultMark = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_NAME);
        resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_COLOR_NAME);
        expectedStr = ATTRIBUTE_MARK_STROKE_COLOR_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'size'  values
    for (auto&& value: markSizeInvalidValues) {
        inputValueMark = initValueMark;
        modifier_->setMark(node_, &inputValueMark);
        inputValueMark.size = std::get<1>(value);
        modifier_->setMark(node_, &inputValueMark);
        jsonValue = GetJsonValue(node_);
        resultMark = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_NAME);
        resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_SIZE_NAME);
        expectedStr = ATTRIBUTE_MARK_SIZE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'strokeWidth'  values
    for (auto&& value: markStrokeWidthInvalidValues) {
        inputValueMark = initValueMark;
        modifier_->setMark(node_, &inputValueMark);
        inputValueMark.strokeWidth = std::get<1>(value);
        modifier_->setMark(node_, &inputValueMark);
        jsonValue = GetJsonValue(node_);
        resultMark = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_NAME);
        resultStr = GetAttrValue<std::string>(resultMark, ATTRIBUTE_MARK_STROKE_WIDTH_NAME);
        expectedStr = ATTRIBUTE_MARK_STROKE_WIDTH_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}*/

/*
 * @tc.name: DISABLED_setOnChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, DISABLED_setOnChangeTest, TestSize.Level1)
{
    // TODO: Implement callback tests!
}

/*
 * @tc.name: DISABLED_setContentModifierTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxModifierTest, DISABLED_setContentModifierTest, TestSize.Level1)
{
    // TODO: CustomObjects is not implemented yet!
}
} // namespace OHOS::Ace::NG
