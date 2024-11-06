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

#include "text_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Text;
/*
 * @tc.name: setLetterSpacingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLetterSpacingTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LETTER_SPACING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LETTER_SPACING_DEFAULT_VALUE) << "Default value for attribute 'letterSpacing'";
}

/*
 * @tc.name: setLetterSpacingTestLetterSpacingValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLetterSpacingTestLetterSpacingValidValues, TestSize.Level1)
{
    Ark_Union_Number_String initValueLetterSpacing;

    // Initial setup
    initValueLetterSpacing =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueLetterSpacing](const std::string& input, const Ark_Union_Number_String& value,
                          const std::string& expectedStr) {
        Ark_Union_Number_String inputValueLetterSpacing = initValueLetterSpacing;

        inputValueLetterSpacing = value;
        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LETTER_SPACING_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setLetterSpacing, attribute: letterSpacing";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setLetterSpacingTestLetterSpacingInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLetterSpacingTestLetterSpacingInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String initValueLetterSpacing;

    // Initial setup
    initValueLetterSpacing =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueLetterSpacing](const std::string& input, const Ark_Union_Number_String& value) {
        Ark_Union_Number_String inputValueLetterSpacing = initValueLetterSpacing;

        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        inputValueLetterSpacing = value;
        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LETTER_SPACING_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LETTER_SPACING_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setLetterSpacing, attribute: letterSpacing";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextCaseTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextCaseTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_CASE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_CASE_DEFAULT_VALUE) << "Default value for attribute 'textCase'";
}

/*
 * @tc.name: setTextCaseTestTextCaseValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextCaseTestTextCaseValidValues, TestSize.Level1)
{
    Ark_TextCase initValueTextCase;

    // Initial setup
    initValueTextCase = std::get<1>(Fixtures::testFixtureEnumTextCaseValidValues[0]);

    auto checkValue = [this, &initValueTextCase](
                          const std::string& input, const Ark_TextCase& value, const std::string& expectedStr) {
        Ark_TextCase inputValueTextCase = initValueTextCase;

        inputValueTextCase = value;
        modifier_->setTextCase(node_, inputValueTextCase);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_CASE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextCase, attribute: textCase";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextCaseValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setTextCaseTestTextCaseInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextCaseTestTextCaseInvalidValues, TestSize.Level1)
{
    Ark_TextCase initValueTextCase;

    // Initial setup
    initValueTextCase = std::get<1>(Fixtures::testFixtureEnumTextCaseValidValues[0]);

    auto checkValue = [this, &initValueTextCase](const std::string& input, const Ark_TextCase& value) {
        Ark_TextCase inputValueTextCase = initValueTextCase;

        modifier_->setTextCase(node_, inputValueTextCase);
        inputValueTextCase = value;
        modifier_->setTextCase(node_, inputValueTextCase);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_CASE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_CASE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextCase, attribute: textCase";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextCaseInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setBaselineOffsetTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setBaselineOffsetTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BASELINE_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BASELINE_OFFSET_DEFAULT_VALUE) << "Default value for attribute 'baselineOffset'";
}

/*
 * @tc.name: setBaselineOffsetTestBaselineOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setBaselineOffsetTestBaselineOffsetValidValues, TestSize.Level1)
{
    Ark_Union_Number_String initValueBaselineOffset;

    // Initial setup
    initValueBaselineOffset =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueBaselineOffset](const std::string& input, const Ark_Union_Number_String& value,
                          const std::string& expectedStr) {
        Ark_Union_Number_String inputValueBaselineOffset = initValueBaselineOffset;

        inputValueBaselineOffset = value;
        modifier_->setBaselineOffset(node_, &inputValueBaselineOffset);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BASELINE_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setBaselineOffset, attribute: baselineOffset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setBaselineOffsetTestBaselineOffsetInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setBaselineOffsetTestBaselineOffsetInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String initValueBaselineOffset;

    // Initial setup
    initValueBaselineOffset =
        ArkUnion<Ark_Union_Number_String, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueBaselineOffset](const std::string& input, const Ark_Union_Number_String& value) {
        Ark_Union_Number_String inputValueBaselineOffset = initValueBaselineOffset;

        modifier_->setBaselineOffset(node_, &inputValueBaselineOffset);
        inputValueBaselineOffset = value;
        modifier_->setBaselineOffset(node_, &inputValueBaselineOffset);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BASELINE_OFFSET_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BASELINE_OFFSET_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setBaselineOffset, attribute: baselineOffset";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setCopyOptionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setCopyOptionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE) << "Default value for attribute 'copyOption'";
}

/*
 * @tc.name: setCopyOptionTestCopyOptionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setCopyOptionTestCopyOptionValidValues, TestSize.Level1)
{
    Ark_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]);

    auto checkValue = [this, &initValueCopyOption](
                          const std::string& input, const Ark_CopyOptions& value, const std::string& expectedStr) {
        Ark_CopyOptions inputValueCopyOption = initValueCopyOption;

        inputValueCopyOption = value;
        modifier_->setCopyOption(node_, inputValueCopyOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCopyOption, attribute: copyOption";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCopyOptionsValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setCopyOptionTestCopyOptionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setCopyOptionTestCopyOptionInvalidValues, TestSize.Level1)
{
    Ark_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]);

    auto checkValue = [this, &initValueCopyOption](const std::string& input, const Ark_CopyOptions& value) {
        Ark_CopyOptions inputValueCopyOption = initValueCopyOption;

        modifier_->setCopyOption(node_, inputValueCopyOption);
        inputValueCopyOption = value;
        modifier_->setCopyOption(node_, inputValueCopyOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCopyOption, attribute: copyOption";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumCopyOptionsInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setDraggableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDraggableTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DRAGGABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE) << "Default value for attribute 'draggable'";
}

/*
 * @tc.name: setDraggableTestDraggableValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setDraggableTestDraggableValidValues, TestSize.Level1)
{
    Ark_Boolean initValueDraggable;

    // Initial setup
    initValueDraggable = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueDraggable](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueDraggable = initValueDraggable;

        inputValueDraggable = value;
        modifier_->setDraggable(node_, inputValueDraggable);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DRAGGABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDraggable, attribute: draggable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setTextShadowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTextShadow =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE)
        << "Default value for attribute 'textShadow..radius'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE)
        << "Default value for attribute 'textShadow..type'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'textShadow..color'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE)
        << "Default value for attribute 'textShadow..offsetX'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE)
        << "Default value for attribute 'textShadow..offsetY'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE)
        << "Default value for attribute 'textShadow..fill'";
}

/*
 * @tc.name: setTextShadowTestTextShadowRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowRadiusValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Ark_Union_Number_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).radius = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..radius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowRadiusInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Ark_Union_Number_Resource& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).radius = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..radius";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextShadowTestTextShadowTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowTypeValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const Opt_ShadowType& value, const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).type = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumShadowTypeValidValues) {
        checkValue(input, ArkValue<Opt_ShadowType>(value), expected);
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowTypeInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_ShadowType& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).type = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumShadowTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ShadowType>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowColorValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input,
                          const Opt_Union_Color_String_Resource_ColoringStrategy& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).color = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumColorValidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureEnumColoringStrategyValidValues) {
        checkValue(
            input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowColorInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const Opt_Union_Color_String_Resource_ColoringStrategy& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).color = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..color";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumColorInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    for (auto& [input, value] : Fixtures::testFixtureEnumColoringStrategyInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Color_String_Resource_ColoringStrategy>());
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowOffsetXValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetX = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetX";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowOffsetXInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetX = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetX";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowOffsetYValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetY = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetY";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value), expected);
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowOffsetYInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetY = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetY";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowFillValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowFillValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).fill = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..fill";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, ArkValue<Opt_Boolean>(value), expected);
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowFillInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextShadowTestTextShadowFillInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius =
        ArkUnion<Ark_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureEnumColorValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY =
        ArkUnion<Opt_Union_Number_Resource, Ark_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Boolean& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).fill = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..fill";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setHeightAdaptivePolicyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setHeightAdaptivePolicyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE)
        << "Default value for attribute 'heightAdaptivePolicy'";
}

/*
 * @tc.name: setHeightAdaptivePolicyTestHeightAdaptivePolicyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setHeightAdaptivePolicyTestHeightAdaptivePolicyValidValues, TestSize.Level1)
{
    Ark_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]);

    auto checkValue = [this, &initValueHeightAdaptivePolicy](const std::string& input,
                          const Ark_TextHeightAdaptivePolicy& value, const std::string& expectedStr) {
        Ark_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;

        inputValueHeightAdaptivePolicy = value;
        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setHeightAdaptivePolicy, attribute: heightAdaptivePolicy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setHeightAdaptivePolicyTestHeightAdaptivePolicyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setHeightAdaptivePolicyTestHeightAdaptivePolicyInvalidValues, TestSize.Level1)
{
    Ark_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]);

    auto checkValue = [this, &initValueHeightAdaptivePolicy](
                          const std::string& input, const Ark_TextHeightAdaptivePolicy& value) {
        Ark_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;

        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        inputValueHeightAdaptivePolicy = value;
        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setHeightAdaptivePolicy, attribute: heightAdaptivePolicy";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setTextIndentTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextIndentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_INDENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_INDENT_DEFAULT_VALUE) << "Default value for attribute 'textIndent'";
}

/*
 * @tc.name: setTextIndentTestTextIndentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextIndentTestTextIndentValidValues, TestSize.Level1)
{
    Ark_Length initValueTextIndent;

    // Initial setup
    initValueTextIndent = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);

    auto checkValue = [this, &initValueTextIndent](
                          const std::string& input, const Ark_Length& value, const std::string& expectedStr) {
        Ark_Length inputValueTextIndent = initValueTextIndent;

        inputValueTextIndent = value;
        modifier_->setTextIndent(node_, &inputValueTextIndent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_INDENT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextIndent, attribute: textIndent";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setTextIndentTestTextIndentInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setTextIndentTestTextIndentInvalidValues, TestSize.Level1)
{
    Ark_Length initValueTextIndent;

    // Initial setup
    initValueTextIndent = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);

    auto checkValue = [this, &initValueTextIndent](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueTextIndent = initValueTextIndent;

        modifier_->setTextIndent(node_, &inputValueTextIndent);
        inputValueTextIndent = value;
        modifier_->setTextIndent(node_, &inputValueTextIndent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_INDENT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_INDENT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextIndent, attribute: textIndent";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setWordBreakTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setWordBreakTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WORD_BREAK_DEFAULT_VALUE) << "Default value for attribute 'wordBreak'";
}

/*
 * @tc.name: setWordBreakTestWordBreakValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setWordBreakTestWordBreakValidValues, TestSize.Level1)
{
    Ark_WordBreak initValueWordBreak;

    // Initial setup
    initValueWordBreak = std::get<1>(Fixtures::testFixtureEnumWordBreakValidValues[0]);

    auto checkValue = [this, &initValueWordBreak](
                          const std::string& input, const Ark_WordBreak& value, const std::string& expectedStr) {
        Ark_WordBreak inputValueWordBreak = initValueWordBreak;

        inputValueWordBreak = value;
        modifier_->setWordBreak(node_, inputValueWordBreak);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWordBreak, attribute: wordBreak";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumWordBreakValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setWordBreakTestWordBreakInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setWordBreakTestWordBreakInvalidValues, TestSize.Level1)
{
    Ark_WordBreak initValueWordBreak;

    // Initial setup
    initValueWordBreak = std::get<1>(Fixtures::testFixtureEnumWordBreakValidValues[0]);

    auto checkValue = [this, &initValueWordBreak](const std::string& input, const Ark_WordBreak& value) {
        Ark_WordBreak inputValueWordBreak = initValueWordBreak;

        modifier_->setWordBreak(node_, inputValueWordBreak);
        inputValueWordBreak = value;
        modifier_->setWordBreak(node_, inputValueWordBreak);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WORD_BREAK_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWordBreak, attribute: wordBreak";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumWordBreakInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setLineBreakStrategyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLineBreakStrategyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_BREAK_STRATEGY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LINE_BREAK_STRATEGY_DEFAULT_VALUE)
        << "Default value for attribute 'lineBreakStrategy'";
}

/*
 * @tc.name: setLineBreakStrategyTestLineBreakStrategyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLineBreakStrategyTestLineBreakStrategyValidValues, TestSize.Level1)
{
    Ark_LineBreakStrategy initValueLineBreakStrategy;

    // Initial setup
    initValueLineBreakStrategy = std::get<1>(Fixtures::testFixtureEnumLineBreakStrategyValidValues[0]);

    auto checkValue = [this, &initValueLineBreakStrategy](const std::string& input, const Ark_LineBreakStrategy& value,
                          const std::string& expectedStr) {
        Ark_LineBreakStrategy inputValueLineBreakStrategy = initValueLineBreakStrategy;

        inputValueLineBreakStrategy = value;
        modifier_->setLineBreakStrategy(node_, inputValueLineBreakStrategy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_BREAK_STRATEGY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setLineBreakStrategy, attribute: lineBreakStrategy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumLineBreakStrategyValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setLineBreakStrategyTestLineBreakStrategyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setLineBreakStrategyTestLineBreakStrategyInvalidValues, TestSize.Level1)
{
    Ark_LineBreakStrategy initValueLineBreakStrategy;

    // Initial setup
    initValueLineBreakStrategy = std::get<1>(Fixtures::testFixtureEnumLineBreakStrategyValidValues[0]);

    auto checkValue = [this, &initValueLineBreakStrategy](
                          const std::string& input, const Ark_LineBreakStrategy& value) {
        Ark_LineBreakStrategy inputValueLineBreakStrategy = initValueLineBreakStrategy;

        modifier_->setLineBreakStrategy(node_, inputValueLineBreakStrategy);
        inputValueLineBreakStrategy = value;
        modifier_->setLineBreakStrategy(node_, inputValueLineBreakStrategy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_BREAK_STRATEGY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LINE_BREAK_STRATEGY_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setLineBreakStrategy, attribute: lineBreakStrategy";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumLineBreakStrategyInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setSelectionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setSelectionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultSelection =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTION_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultSelection, ATTRIBUTE_SELECTION_I_SELECTION_START_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTION_I_SELECTION_START_DEFAULT_VALUE)
        << "Default value for attribute 'selection.selectionStart'";

    resultStr = GetAttrValue<std::string>(resultSelection, ATTRIBUTE_SELECTION_I_SELECTION_END_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTION_I_SELECTION_END_DEFAULT_VALUE)
        << "Default value for attribute 'selection.selectionEnd'";
}

/*
 * @tc.name: setSelectionTestSelectionSelectionStartValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setSelectionTestSelectionSelectionStartValidValues, TestSize.Level1)
{
    Ark_Number initValueSelectionStart;
    Ark_Number initValueSelectionEnd;

    // Initial setup
    initValueSelectionStart = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    initValueSelectionEnd = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueSelectionStart, &initValueSelectionEnd](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueSelectionStart = initValueSelectionStart;
        Ark_Number inputValueSelectionEnd = initValueSelectionEnd;

        inputValueSelectionStart = value;
        modifier_->setSelection(node_, &inputValueSelectionStart, &inputValueSelectionEnd);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelection = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSelection, ATTRIBUTE_SELECTION_I_SELECTION_START_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSelection, attribute: selection.selectionStart";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setSelectionTestSelectionSelectionEndValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setSelectionTestSelectionSelectionEndValidValues, TestSize.Level1)
{
    Ark_Number initValueSelectionStart;
    Ark_Number initValueSelectionEnd;

    // Initial setup
    initValueSelectionStart = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    initValueSelectionEnd = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueSelectionStart, &initValueSelectionEnd](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueSelectionStart = initValueSelectionStart;
        Ark_Number inputValueSelectionEnd = initValueSelectionEnd;

        inputValueSelectionEnd = value;
        modifier_->setSelection(node_, &inputValueSelectionStart, &inputValueSelectionEnd);
        auto jsonValue = GetJsonValue(node_);
        auto resultSelection = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSelection, ATTRIBUTE_SELECTION_I_SELECTION_END_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setSelection, attribute: selection.selectionEnd";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setEllipsisModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setEllipsisModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ELLIPSIS_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ELLIPSIS_MODE_DEFAULT_VALUE) << "Default value for attribute 'ellipsisMode'";
}

/*
 * @tc.name: setEllipsisModeTestEllipsisModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setEllipsisModeTestEllipsisModeValidValues, TestSize.Level1)
{
    Ark_EllipsisMode initValueEllipsisMode;

    // Initial setup
    initValueEllipsisMode = std::get<1>(Fixtures::testFixtureEnumEllipsisModeValidValues[0]);

    auto checkValue = [this, &initValueEllipsisMode](
                          const std::string& input, const Ark_EllipsisMode& value, const std::string& expectedStr) {
        Ark_EllipsisMode inputValueEllipsisMode = initValueEllipsisMode;

        inputValueEllipsisMode = value;
        modifier_->setEllipsisMode(node_, inputValueEllipsisMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ELLIPSIS_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEllipsisMode, attribute: ellipsisMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumEllipsisModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setEllipsisModeTestEllipsisModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setEllipsisModeTestEllipsisModeInvalidValues, TestSize.Level1)
{
    Ark_EllipsisMode initValueEllipsisMode;

    // Initial setup
    initValueEllipsisMode = std::get<1>(Fixtures::testFixtureEnumEllipsisModeValidValues[0]);

    auto checkValue = [this, &initValueEllipsisMode](const std::string& input, const Ark_EllipsisMode& value) {
        Ark_EllipsisMode inputValueEllipsisMode = initValueEllipsisMode;

        modifier_->setEllipsisMode(node_, inputValueEllipsisMode);
        inputValueEllipsisMode = value;
        modifier_->setEllipsisMode(node_, inputValueEllipsisMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ELLIPSIS_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ELLIPSIS_MODE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setEllipsisMode, attribute: ellipsisMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumEllipsisModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setEnableDataDetectorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setEnableDataDetectorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_DATA_DETECTOR_DEFAULT_VALUE)
        << "Default value for attribute 'enableDataDetector'";
}

/*
 * @tc.name: setEnableDataDetectorTestEnableDataDetectorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setEnableDataDetectorTestEnableDataDetectorValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableDataDetector;

    // Initial setup
    initValueEnableDataDetector = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableDataDetector](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueEnableDataDetector = initValueEnableDataDetector;

        inputValueEnableDataDetector = value;
        modifier_->setEnableDataDetector(node_, inputValueEnableDataDetector);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEnableDataDetector, attribute: enableDataDetector";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDataDetectorConfigTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setDataDetectorConfigTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultDataDetectorConfig =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DATA_DETECTOR_CONFIG_NAME);
    std::unique_ptr<JsonValue> resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(
        resultDataDetectorConfig, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultDataDetectorConfig, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_TYPES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_TYPES_DEFAULT_VALUE)
        << "Default value for attribute 'dataDetectorConfig.types'";

    resultStr = GetAttrValue<std::string>(resultDataDetectorConfig, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'dataDetectorConfig.color'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_TYPE_DEFAULT_VALUE)
        << "Default value for attribute 'dataDetectorConfig.decoration.type'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'dataDetectorConfig.decoration.color'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_STYLE_DEFAULT_VALUE)
        << "Default value for attribute 'dataDetectorConfig.decoration.style'";
}

/*
 * @tc.name: setDataDetectorConfigTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setDataDetectorConfigTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setFontFeatureTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontFeatureTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE) << "Default value for attribute 'fontFeature'";
}

/*
 * @tc.name: setFontFeatureTestFontFeatureValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontFeatureTestFontFeatureValidValues, TestSize.Level1)
{
    Ark_String initValueFontFeature;

    // Initial setup
    initValueFontFeature = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueFontFeature](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueFontFeature = initValueFontFeature;

        inputValueFontFeature = value;
        modifier_->setFontFeature(node_, &inputValueFontFeature);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFontFeature, attribute: fontFeature";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setPrivacySensitiveTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setPrivacySensitiveTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE) << "Default value for attribute 'privacySensitive'";
}

/*
 * @tc.name: setPrivacySensitiveTestPrivacySensitiveValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setPrivacySensitiveTestPrivacySensitiveValidValues, TestSize.Level1)
{
    Ark_Boolean initValuePrivacySensitive;

    // Initial setup
    initValuePrivacySensitive = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValuePrivacySensitive](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValuePrivacySensitive = initValuePrivacySensitive;

        inputValuePrivacySensitive = value;
        modifier_->setPrivacySensitive(node_, inputValuePrivacySensitive);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setPrivacySensitive, attribute: privacySensitive";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setTextSelectableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextSelectableTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_SELECTABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SELECTABLE_DEFAULT_VALUE) << "Default value for attribute 'textSelectable'";
}

/*
 * @tc.name: setTextSelectableTestTextSelectableValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextSelectableTestTextSelectableValidValues, TestSize.Level1)
{
    Ark_TextSelectableMode initValueTextSelectable;

    // Initial setup
    initValueTextSelectable = std::get<1>(Fixtures::testFixtureTextSelectableModeValidValues[0]);

    auto checkValue = [this, &initValueTextSelectable](const std::string& input, const Ark_TextSelectableMode& value,
                          const std::string& expectedStr) {
        Ark_TextSelectableMode inputValueTextSelectable = initValueTextSelectable;

        inputValueTextSelectable = value;
        modifier_->setTextSelectable(node_, inputValueTextSelectable);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_SELECTABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTextSelectable, attribute: textSelectable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextSelectableModeValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setTextSelectableTestTextSelectableInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextSelectableTestTextSelectableInvalidValues, TestSize.Level1)
{
    Ark_TextSelectableMode initValueTextSelectable;

    // Initial setup
    initValueTextSelectable = std::get<1>(Fixtures::testFixtureTextSelectableModeValidValues[0]);

    auto checkValue = [this, &initValueTextSelectable](const std::string& input, const Ark_TextSelectableMode& value) {
        Ark_TextSelectableMode inputValueTextSelectable = initValueTextSelectable;

        modifier_->setTextSelectable(node_, inputValueTextSelectable);
        inputValueTextSelectable = value;
        modifier_->setTextSelectable(node_, inputValueTextSelectable);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_SELECTABLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SELECTABLE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTextSelectable, attribute: textSelectable";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextSelectableModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setHalfLeadingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setHalfLeadingTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HALF_LEADING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HALF_LEADING_DEFAULT_VALUE) << "Default value for attribute 'halfLeading'";
}

/*
 * @tc.name: setHalfLeadingTestHalfLeadingValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setHalfLeadingTestHalfLeadingValidValues, TestSize.Level1)
{
    Ark_Boolean initValueHalfLeading;

    // Initial setup
    initValueHalfLeading = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueHalfLeading](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueHalfLeading = initValueHalfLeading;

        inputValueHalfLeading = value;
        modifier_->setHalfLeading(node_, inputValueHalfLeading);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HALF_LEADING_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setHalfLeading, attribute: halfLeading";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setEnableHapticFeedbackTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setEnableHapticFeedbackTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE)
        << "Default value for attribute 'enableHapticFeedback'";
}

/*
 * @tc.name: setEnableHapticFeedbackTestEnableHapticFeedbackValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableHapticFeedback;

    // Initial setup
    initValueEnableHapticFeedback = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableHapticFeedback](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueEnableHapticFeedback = initValueEnableHapticFeedback;

        inputValueEnableHapticFeedback = value;
        modifier_->setEnableHapticFeedback(node_, inputValueEnableHapticFeedback);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setEnableHapticFeedback, attribute: enableHapticFeedback";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}
} // namespace OHOS::Ace::NG
