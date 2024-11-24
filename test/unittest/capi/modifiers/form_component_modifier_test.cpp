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
#include "generated/type_helpers.h"

#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;

namespace  {

const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_SIZE_NAME = "size";
const auto ATTRIBUTE_VALUE_I_ID_NAME = "id";
const auto ATTRIBUTE_VALUE_I_ID_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_VALUE_I_NAME_NAME = "name";
const auto ATTRIBUTE_VALUE_I_NAME_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_BUNDLE_NAME = "bundle";
const auto ATTRIBUTE_VALUE_I_BUNDLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_ABILITY_NAME = "ability";
const auto ATTRIBUTE_VALUE_I_ABILITY_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_MODULE_NAME = "module";
const auto ATTRIBUTE_VALUE_I_MODULE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_DIMENSION_NAME = "dimension";
const auto ATTRIBUTE_VALUE_I_DIMENSION_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_TEMPORARY_NAME = "temporary";
const auto ATTRIBUTE_VALUE_I_TEMPORARY_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_RENDERING_MODE_NAME = "renderingMode";
const auto ATTRIBUTE_VALUE_I_RENDERING_MODE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_VALUE_I_SHAPE_NAME = "shape";
const auto ATTRIBUTE_VALUE_I_SHAPE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SIZE_I_WIDTH_NAME = "width";
const auto ATTRIBUTE_SIZE_I_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_SIZE_I_HEIGHT_NAME = "height";
const auto ATTRIBUTE_SIZE_I_HEIGHT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_MODULE_NAME_NAME = "moduleName";
const auto ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_DIMENSION_NAME = "dimension";
const auto ATTRIBUTE_DIMENSION_DEFAULT_VALUE = "2";
const auto ATTRIBUTE_ALLOW_UPDATE_NAME = "allowUpdate";
const auto ATTRIBUTE_ALLOW_UPDATE_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_VISIBILITY_NAME = "visibility";
const auto ATTRIBUTE_VISIBILITY_DEFAULT_VALUE = "VISIBLE";

std::vector<std::tuple<std::string, Ark_FormDimension, std::string>> testFixtureEnumFormDimensionValidValues = {
    { "ARK_FORM_DIMENSION_DIMENSION_1_2", ARK_FORM_DIMENSION_DIMENSION_1_2, "1" },
    { "ARK_FORM_DIMENSION_DIMENSION_2_2", ARK_FORM_DIMENSION_DIMENSION_2_2, "2" },
    { "ARK_FORM_DIMENSION_DIMENSION_2_4", ARK_FORM_DIMENSION_DIMENSION_2_4, "3" },
    { "ARK_FORM_DIMENSION_DIMENSION_4_4", ARK_FORM_DIMENSION_DIMENSION_4_4, "4" },
    { "ARK_FORM_DIMENSION_DIMENSION_2_1", ARK_FORM_DIMENSION_DIMENSION_2_1, "5" },
    { "ARK_FORM_DIMENSION_DIMENSION_1_1", ARK_FORM_DIMENSION_DIMENSION_1_1, "6" },
    { "ARK_FORM_DIMENSION_DIMENSION_6_4", ARK_FORM_DIMENSION_DIMENSION_6_4, "7" },
};

std::vector<std::tuple<std::string, Ark_FormDimension>> testFixtureEnumFormDimensionInvalidValues = {
    { "-1", static_cast<Ark_FormDimension>(-1) },
    { "INT_MAX", static_cast<Ark_FormDimension>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_FormRenderingMode, std::string>> testFixtureEnumFormRenderingModeValidValues = {
    { "ARK_FORM_RENDERING_MODE_FULL_COLOR", ARK_FORM_RENDERING_MODE_FULL_COLOR, "FormRenderingMode.FULL_COLOR" },
    { "ARK_FORM_RENDERING_MODE_SINGLE_COLOR", ARK_FORM_RENDERING_MODE_SINGLE_COLOR, "FormRenderingMode.SINGLE_COLOR" },
};

std::vector<std::tuple<std::string, Ark_FormRenderingMode>> testFixtureEnumFormRenderingModeInvalidValues = {
    { "-1", static_cast<Ark_FormRenderingMode>(-1) },
    { "INT_MAX", static_cast<Ark_FormRenderingMode>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_FormShape, std::string>> testFixtureEnumFormShapeValidValues = {
    { "ARK_FORM_SHAPE_RECT", ARK_FORM_SHAPE_RECT, "FormShape.RECT" },
    { "ARK_FORM_SHAPE_CIRCLE", ARK_FORM_SHAPE_CIRCLE, "FormShape.CIRCLE" },
};

std::vector<std::tuple<std::string, Ark_FormShape>> testFixtureEnumFormShapeInvalidValues = {
    { "-1", static_cast<Ark_FormShape>(-1) },
    { "INT_MAX", static_cast<Ark_FormShape>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_Visibility, std::string>> testFixtureEnumFormVisibilityValidValues = {
    { "ARK_VISIBILITY_VISIBLE", ARK_VISIBILITY_VISIBLE, "Visibility.Visible" },
    { "ARK_VISIBILITY_HIDDEN", ARK_VISIBILITY_HIDDEN, "Visibility.Hidden" },
    { "ARK_VISIBILITY_NONE", ARK_VISIBILITY_NONE, "Visibility.None" },
};

std::vector<std::tuple<std::string, Ark_Visibility>> testFixtureEnumFormVisibilityInvalidValues = {
    { "-1", static_cast<Ark_Visibility>(-1) },
    { "INT_MAX", static_cast<Ark_Visibility>(INT_MAX) },
};


    // test!!!
        std::ofstream out2("test_json_output.txt");    


} // namespace

class FormComponentModifierTest : public ModifierTestBase<GENERATED_ArkUIFormComponentModifier,
    &GENERATED_ArkUINodeModifiers::getFormComponentModifier, GENERATED_ARKUI_FORM_COMPONENT> {

    void SetUp(void) override
    {
        ModifierTestBase::SetUp();
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        frameNode->MarkModifyDone();
    }
};

/*
 * @tc.name: setFormComponentOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_ID_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_ID_DEFAULT_VALUE) << "Default value for attribute 'value.id'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_NAME_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_NAME_DEFAULT_VALUE) << "Default value for attribute 'value.name'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_BUNDLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_BUNDLE_DEFAULT_VALUE) << "Default value for attribute 'value.bundle'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_ABILITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_ABILITY_DEFAULT_VALUE) << "Default value for attribute 'value.ability'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_MODULE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_MODULE_DEFAULT_VALUE) << "Default value for attribute 'value.module'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_DIMENSION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_DIMENSION_DEFAULT_VALUE) << "Default value for attribute 'value.dimension'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_TEMPORARY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_TEMPORARY_DEFAULT_VALUE) << "Default value for attribute 'value.temporary'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_RENDERING_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_RENDERING_MODE_DEFAULT_VALUE) <<
        "Default value for attribute 'value.renderingMode'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_SHAPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_SHAPE_DEFAULT_VALUE) << "Default value for attribute 'value.shape'";
}

/*
 * @tc.name: setFormComponentOptionsTestValueIdValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueIdValidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](const std::string& input, const Ark_Union_Number_String& value,
                          const std::string& expectedStr) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.id = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_ID_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.id";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFormComponentOptionsTestValueIdInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueIdInvalidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](const std::string& input, const Ark_Union_Number_String& value) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.id = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_ID_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_ID_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.id";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFormComponentOptionsTestValueNameValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueNameValidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.name = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_NAME_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.name";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFormComponentOptionsTestValueBundleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueBundleValidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.bundle = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_BUNDLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.bundle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFormComponentOptionsTestValueAbilityValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueAbilityValidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.ability = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_ABILITY_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.ability";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFormComponentOptionsTestValueModuleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueModuleValidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.module = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_MODULE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.module";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFormComponentOptionsTestValueDimensionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueDimensionValidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](
                          const std::string& input, const Opt_FormDimension& value, const std::string& expectedStr) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.dimension = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_DIMENSION_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.dimension";
    };

    for (auto& [input, value, expected] : testFixtureEnumFormDimensionValidValues) {
        checkValue(input, ArkValue<Opt_FormDimension>(value), expected);
    }
}

/*
 * @tc.name: setFormComponentOptionsTestValueDimensionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueDimensionInvalidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](const std::string& input, const Opt_FormDimension& value) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.dimension = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_DIMENSION_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_DIMENSION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.dimension";
    };

    for (auto& [input, value] : testFixtureEnumFormDimensionInvalidValues) {
        checkValue(input, ArkValue<Opt_FormDimension>(value));
    }
}

/*
 * @tc.name: setFormComponentOptionsTestValueTemporaryValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueTemporaryValidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.temporary = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_TEMPORARY_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.temporary";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, ArkValue<Opt_Boolean>(value), expected);
    }
}

/*
 * @tc.name: setFormComponentOptionsTestValueTemporaryInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueTemporaryInvalidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](const std::string& input, const Opt_Boolean& value) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.temporary = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_TEMPORARY_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_TEMPORARY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.temporary";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setFormComponentOptionsTestValueRenderingModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueRenderingModeValidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](const std::string& input, const Opt_FormRenderingMode& value,
                          const std::string& expectedStr) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.renderingMode = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_RENDERING_MODE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.renderingMode";
    };

    for (auto& [input, value, expected] : testFixtureEnumFormRenderingModeValidValues) {
        checkValue(input, ArkValue<Opt_FormRenderingMode>(value), expected);
    }
}

/*
 * @tc.name: setFormComponentOptionsTestValueRenderingModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueRenderingModeInvalidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](const std::string& input, const Opt_FormRenderingMode& value) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.renderingMode = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_RENDERING_MODE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_RENDERING_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.renderingMode";
    };

    for (auto& [input, value] : testFixtureEnumFormRenderingModeInvalidValues) {
        checkValue(input, ArkValue<Opt_FormRenderingMode>(value));
    }
}

/*
 * @tc.name: setFormComponentOptionsTestValueShapeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueShapeValidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](
                          const std::string& input, const Opt_FormShape& value, const std::string& expectedStr) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.shape = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_SHAPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.shape";
    };

    for (auto& [input, value, expected] : testFixtureEnumFormShapeValidValues) {
        checkValue(input, ArkValue<Opt_FormShape>(value), expected);
    }
}

/*
 * @tc.name: setFormComponentOptionsTestValueShapeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsTestValueShapeInvalidValues, TestSize.Level1)
{
    Ark_FormInfo initValueValue;

    // Initial setup
    initValueValue.id =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueValue.name = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.bundle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.ability = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.module = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueValue.dimension =
        ArkValue<Opt_FormDimension>(std::get<1>(testFixtureEnumFormDimensionValidValues[0]));
    initValueValue.temporary = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueValue.renderingMode =
        ArkValue<Opt_FormRenderingMode>(std::get<1>(testFixtureEnumFormRenderingModeValidValues[0]));
    initValueValue.shape = ArkValue<Opt_FormShape>(std::get<1>(testFixtureEnumFormShapeValidValues[0]));

    auto checkValue = [this, &initValueValue](const std::string& input, const Opt_FormShape& value) {
        Ark_FormInfo inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue.shape = value;
        modifier_->setFormComponentOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_SHAPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_SHAPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: value.shape";
    };

    for (auto& [input, value] : testFixtureEnumFormShapeInvalidValues) {
        checkValue(input, ArkValue<Opt_FormShape>(value));
    }
}

/*
 * @tc.name: setSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
    std::string resultStr;


    // test!!!
        out2 << "\ntest_json_set_size_default.txt === \n";
        auto resultStr2 = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_WIDTH_NAME);
        auto resultStr3 = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_HEIGHT_NAME);
        out2 << "size.width: " << resultStr2.c_str() << " " << ATTRIBUTE_SIZE_I_WIDTH_DEFAULT_VALUE << " ";
        out2 << "size.height: " << resultStr3.c_str() << " " << ATTRIBUTE_SIZE_I_HEIGHT_DEFAULT_VALUE << std::endl;
        out2 << "   " << jsonValue->ToString().c_str();
    // test!!!

    

    resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SIZE_I_WIDTH_DEFAULT_VALUE) << "Default value for attribute 'size.width'";

    resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SIZE_I_HEIGHT_DEFAULT_VALUE) << "Default value for attribute 'size.height'";
}

/*
 * @tc.name: setSizeTestSizeWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setSizeTestSizeWidthValidValues, TestSize.Level1)
{
    Ark_Literal_Number_height_width initValueSize;

    // Initial setup
    initValueSize.width = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    initValueSize.height = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueSize](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Literal_Number_height_width inputValueSize = initValueSize;

        inputValueSize.width = value;
        modifier_->setSize(node_, &inputValueSize);
        auto jsonValue = GetJsonValue(node_);


    // test!!!
        auto resultSize2 = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        auto resultStr2 = GetAttrValue<std::string>(resultSize2, ATTRIBUTE_SIZE_I_WIDTH_NAME);
        out2 << "\nsize.width: " << input.c_str() << " read: " << resultStr2.c_str()  <<  " expected: " << expectedStr.c_str() << std::endl;
        out2 << "   " << jsonValue->ToString().c_str();
    // test!!!


        auto resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setSize, attribute: size.width";
    };

    // test!!!
        out2 << "\n\ntest_json_set_size_width_valid.txt";    
    // test!!!

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setSizeTestSizeHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setSizeTestSizeHeightValidValues, TestSize.Level1)
{
    Ark_Literal_Number_height_width initValueSize;

    // Initial setup
    initValueSize.width = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    initValueSize.height = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueSize](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Literal_Number_height_width inputValueSize = initValueSize;

        inputValueSize.height = value;
        modifier_->setSize(node_, &inputValueSize);
        auto jsonValue = GetJsonValue(node_);


    // test!!!
        auto resultSize2 = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        auto resultStr2 = GetAttrValue<std::string>(resultSize2, ATTRIBUTE_SIZE_I_HEIGHT_NAME);
        out2 << "\nsize.height: " << input.c_str() << " read: " << resultStr2.c_str()  <<  " expected: " << expectedStr.c_str() << std::endl;
        out2 << "   " << jsonValue->ToString().c_str();
    // test!!!


        auto resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setSize, attribute: size.height";
    };

    // test!!!
        out2 << "\n\ntest_json_set_size_height_valid.txt";    
    // test!!!
    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setModuleNameTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setModuleNameTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    // test!!!
    out2 << "\n\ntest_json_module_name_default.txt";
    auto resultStr2 = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODULE_NAME_NAME);
    out2 << "\nmoduleName: " << resultStr2.c_str() << " expected: " << ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE << std::endl;
    out2 << jsonValue->ToString().c_str();
    // test!!!


    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODULE_NAME_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE) << "Default value for attribute 'moduleName'";
}

/*
 * @tc.name: setModuleNameTestModuleNameValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setModuleNameTestModuleNameValidValues, TestSize.Level1)
{
    Ark_String initValueModuleName;

    // Initial setup
    initValueModuleName = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueModuleName](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueModuleName = initValueModuleName;

        inputValueModuleName = value;
        modifier_->setModuleName(node_, &inputValueModuleName);
        auto jsonValue = GetJsonValue(node_);

        // test!!!
        auto resultStr2 = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODULE_NAME_NAME);
        out2 << "\nmoduleName: " << input.c_str() << " read: " << resultStr2.c_str()  <<  " expected: " << expectedStr.c_str() << std::endl;
        out2 << jsonValue->ToString().c_str();
        // test!!!

        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODULE_NAME_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setModuleName, attribute: moduleName";
    };


    // test!!!
        out2 << "\n\ntest_json_module_name_valid.txt";
    // test!!!

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDimensionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setDimensionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    // test!!!
        out2 << "\n\ntest_json_dimension_default.txt";
        auto resultStr2 = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIMENSION_NAME);
        out2 << "\ndimension: " << resultStr2.c_str() << " expected: " << ATTRIBUTE_DIMENSION_DEFAULT_VALUE << std::endl;
        out2 << jsonValue->ToString().c_str();
    // test!!!

        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIMENSION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DIMENSION_DEFAULT_VALUE) << "Default value for attribute 'dimension'";
}

/*
 * @tc.name: setDimensionTestDimensionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setDimensionTestDimensionValidValues, TestSize.Level1)
{
    Ark_FormDimension initValueDimension;

    // Initial setup
    initValueDimension = std::get<1>(testFixtureEnumFormDimensionValidValues[0]);

    auto checkValue = [this, &initValueDimension](
                          const std::string& input, const Ark_FormDimension& value, const std::string& expectedStr) {
        Ark_FormDimension inputValueDimension = initValueDimension;

        inputValueDimension = value;
        modifier_->setDimension(node_, inputValueDimension);
        auto jsonValue = GetJsonValue(node_);


    // test!!!
        auto resultStr2 = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIMENSION_NAME);
        out2 << "\ndimension: " << input.c_str() << " read: " << resultStr2.c_str()  <<  " expected: " << expectedStr.c_str() << std::endl;   
        out2 << jsonValue->ToString().c_str();
    // test!!!



        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIMENSION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDimension, attribute: dimension";
    };
    

    // test!!!
    out2 << "\n\ntest_json_dimension_valid.txt"; 
    // test!!!
       


    for (auto& [input, value, expected] : testFixtureEnumFormDimensionValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDimensionTestDimensionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setDimensionTestDimensionInvalidValues, TestSize.Level1)
{
    Ark_FormDimension initValueDimension;

    // Initial setup
    initValueDimension = std::get<1>(testFixtureEnumFormDimensionValidValues[0]);

    auto checkValue = [this, &initValueDimension](const std::string& input, const Ark_FormDimension& value) {
        Ark_FormDimension inputValueDimension = initValueDimension;

        modifier_->setDimension(node_, inputValueDimension);
        inputValueDimension = value;
        modifier_->setDimension(node_, inputValueDimension);
        auto jsonValue = GetJsonValue(node_);


        // test!!!
        auto resultStr2 = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIMENSION_NAME);
        out2 << "\ndimension: " << input.c_str() << " read: " << resultStr2.c_str() <<  " expected: " << ATTRIBUTE_DIMENSION_DEFAULT_VALUE << std::endl;
        out2 << jsonValue->ToString().c_str();
        // test!!!


        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIMENSION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DIMENSION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDimension, attribute: dimension";
    };


        // test!!!
        out2 << "\n\ntest_json_dimension_invalid.txt";
        // test!!!


    for (auto& [input, value] : testFixtureEnumFormDimensionInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setAllowUpdateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setAllowUpdateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;


    // test!!!
    out2 << "\n\ntest_json_allow_update_default.txt"; 
    auto resultStr2 = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_UPDATE_NAME);
    out2 << "\nallowUpdate: " << resultStr2.c_str() << " expected: " << ATTRIBUTE_ALLOW_UPDATE_DEFAULT_VALUE << std::endl;
    out2 << jsonValue->ToString().c_str();
    // test!!!



    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_UPDATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALLOW_UPDATE_DEFAULT_VALUE) << "Default value for attribute 'allowUpdate'";
}

/*
 * @tc.name: setAllowUpdateTestAllowUpdateValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setAllowUpdateTestAllowUpdateValidValues, TestSize.Level1)
{
    Ark_Boolean initValueAllowUpdate;

    // Initial setup
    initValueAllowUpdate = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueAllowUpdate](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueAllowUpdate = initValueAllowUpdate;

        inputValueAllowUpdate = value;
        modifier_->setAllowUpdate(node_, inputValueAllowUpdate);
        auto jsonValue = GetJsonValue(node_);


        // test!!!
        auto resultStr2 = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_UPDATE_NAME);
        out2 << "\nallowUpdate: " << input.c_str() << " read: " << resultStr2.c_str()  <<  " expected: " << expectedStr.c_str() << std::endl;
        out2 << jsonValue->ToString().c_str();
        // test!!!


        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_UPDATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAllowUpdate, attribute: allowUpdate";
    };


        // test!!!
        out2 << "\n\ntest_json_allow_update_valid.txt";
        // test!!!



    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setVisibilityTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setVisibilityTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;


    // test!!!
        out2 << "\n\ntest_json_visibility_default.txt"; 
        auto  resultStr2 = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VISIBILITY_NAME);
        out2 << "\nvisibility: " << resultStr2.c_str() << " expected: " << ATTRIBUTE_VISIBILITY_DEFAULT_VALUE << std::endl;
        out2 << jsonValue->ToString().c_str();
    // test!!!


    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VISIBILITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VISIBILITY_DEFAULT_VALUE) << "Default value for attribute 'visibility'";
}

/*
 * @tc.name: setVisibilityTestVisibilityValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setVisibilityTestVisibilityValidValues, TestSize.Level1)
{
    Ark_Visibility initValueVisibility;

    // Initial setup
    initValueVisibility = std::get<1>(testFixtureEnumFormVisibilityValidValues[0]);

    auto checkValue = [this, &initValueVisibility](
                          const std::string& input, const Ark_Visibility& value, const std::string& expectedStr) {
        Ark_Visibility inputValueVisibility = initValueVisibility;

        inputValueVisibility = value;
        modifier_->setVisibility(node_, inputValueVisibility);
        auto jsonValue = GetJsonValue(node_);


    // test!!!
        auto resultStr2 = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VISIBILITY_NAME);
        out2 << "\nvisibility: " << input.c_str() << " read: " << resultStr2.c_str()  <<  " expected: " << expectedStr.c_str() << std::endl;
        out2 << jsonValue->ToString().c_str();
    // test!!!



        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VISIBILITY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setVisibility, attribute: visibility";
    };



    // test!!!
        out2 << "\n\ntest_json_visibility_valid.txt"; 
    // test!!!


    for (auto& [input, value, expected] : testFixtureEnumFormVisibilityValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setVisibilityTestVisibilityInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setVisibilityTestVisibilityInvalidValues, TestSize.Level1)
{
    Ark_Visibility initValueVisibility;

    // Initial setup
    initValueVisibility = std::get<1>(testFixtureEnumFormVisibilityValidValues[0]);

    auto checkValue = [this, &initValueVisibility](const std::string& input, const Ark_Visibility& value) {
        Ark_Visibility inputValueVisibility = initValueVisibility;

        modifier_->setVisibility(node_, inputValueVisibility);
        inputValueVisibility = value;
        modifier_->setVisibility(node_, inputValueVisibility);
        auto jsonValue = GetJsonValue(node_);


    // test!!!
        auto resultStr2 = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VISIBILITY_NAME);
        out2 << "\nvisibility: " << input.c_str() << " expected: " << ATTRIBUTE_VISIBILITY_DEFAULT_VALUE << std::endl;
        out2 << jsonValue->ToString().c_str();
    // test!!!


        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VISIBILITY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_VISIBILITY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setVisibility, attribute: visibility";
    };


    // test!!!
        out2 << "\n\ntest_json_visibility_invalid.txt";
    // test!!!


    for (auto& [input, value] : testFixtureEnumFormVisibilityInvalidValues) {
        checkValue(input, value);
    }
}
} // namespace OHOS::Ace::NG
