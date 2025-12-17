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

#include "button_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Button;

/*
 * @tc.name: setButtonOptions1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) << "Default value for attribute 'options.type'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE) << "Default value for attribute 'options.stateEffect'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE) << "Default value for attribute 'options.buttonStyle'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE) << "Default value for attribute 'options.controlSize'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROLE_DEFAULT_VALUE) << "Default value for attribute 'options.role'";
}

/*
 * @tc.name: setButtonOptions1TestOptionsTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions1TestOptionsTypeValidValues, TestSize.Level1)
{
    Ark_ButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.type = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    initValueOptions.stateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueOptions.buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    initValueOptions.controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    initValueOptions.role = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ButtonType& value) {
        Ark_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.type = value;
        modifier_->setButtonOptions1(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonOptions1, attribute: options.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumButtonTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ButtonType>(value));
    }
}

/*
 * @tc.name: setButtonOptions1TestOptionsTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions1TestOptionsTypeInvalidValues, TestSize.Level1)
{
    Ark_ButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.type = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    initValueOptions.stateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueOptions.buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    initValueOptions.controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    initValueOptions.role = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_ButtonType& value) {
        Ark_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.type = value;
        modifier_->setButtonOptions1(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonOptions1, attribute: options.type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumButtonTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ButtonType>(value));
    }
}

/*
 * @tc.name: setButtonOptions1TestOptionsStateEffectValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions1TestOptionsStateEffectValidValues, TestSize.Level1)
{
    Ark_ButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.type = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    initValueOptions.stateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueOptions.buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    initValueOptions.controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    initValueOptions.role = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Ark_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.stateEffect = value;
        modifier_->setButtonOptions1(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonOptions1, attribute: options.stateEffect";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setButtonOptions1TestOptionsStateEffectInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions1TestOptionsStateEffectInvalidValues, TestSize.Level1)
{
    Ark_ButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.type = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    initValueOptions.stateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueOptions.buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    initValueOptions.controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    initValueOptions.role = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Ark_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.stateEffect = value;
        modifier_->setButtonOptions1(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonOptions1, attribute: options.stateEffect";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setButtonOptions1TestOptionsButtonStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions1TestOptionsButtonStyleValidValues, TestSize.Level1)
{
    Ark_ButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.type = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    initValueOptions.stateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueOptions.buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    initValueOptions.controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    initValueOptions.role = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ButtonStyleMode& value) {
        Ark_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.buttonStyle = value;
        modifier_->setButtonOptions1(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonOptions1, attribute: options.buttonStyle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumButtonStyleModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ButtonStyleMode>(value));
    }
}

/*
 * @tc.name: setButtonOptions1TestOptionsButtonStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions1TestOptionsButtonStyleInvalidValues, TestSize.Level1)
{
    Ark_ButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.type = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    initValueOptions.stateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueOptions.buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    initValueOptions.controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    initValueOptions.role = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_ButtonStyleMode& value) {
        Ark_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.buttonStyle = value;
        modifier_->setButtonOptions1(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonOptions1, attribute: options.buttonStyle";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumButtonStyleModeInvalidValues) {
        checkValue(input, ArkValue<Opt_ButtonStyleMode>(value));
    }
}

/*
 * @tc.name: setButtonOptions1TestOptionsControlSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions1TestOptionsControlSizeValidValues, TestSize.Level1)
{
    Ark_ButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.type = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    initValueOptions.stateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueOptions.buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    initValueOptions.controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    initValueOptions.role = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ControlSize& value) {
        Ark_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.controlSize = value;
        modifier_->setButtonOptions1(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonOptions1, attribute: options.controlSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumControlSizeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ControlSize>(value));
    }
}

/*
 * @tc.name: setButtonOptions1TestOptionsControlSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions1TestOptionsControlSizeInvalidValues, TestSize.Level1)
{
    Ark_ButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.type = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    initValueOptions.stateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueOptions.buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    initValueOptions.controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    initValueOptions.role = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_ControlSize& value) {
        Ark_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.controlSize = value;
        modifier_->setButtonOptions1(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonOptions1, attribute: options.controlSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumControlSizeInvalidValues) {
        checkValue(input, ArkValue<Opt_ControlSize>(value));
    }
}

/*
 * @tc.name: setButtonOptions1TestOptionsRoleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions1TestOptionsRoleValidValues, TestSize.Level1)
{
    Ark_ButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.type = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    initValueOptions.stateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueOptions.buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    initValueOptions.controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    initValueOptions.role = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ButtonRole& value) {
        Ark_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.role = value;
        modifier_->setButtonOptions1(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonOptions1, attribute: options.role";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumButtonRoleValidValues) {
        checkValue(input, expected, ArkValue<Opt_ButtonRole>(value));
    }
}

/*
 * @tc.name: setButtonOptions1TestOptionsRoleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions1TestOptionsRoleInvalidValues, TestSize.Level1)
{
    Ark_ButtonOptions initValueOptions;

    // Initial setup
    initValueOptions.type = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    initValueOptions.stateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    initValueOptions.buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    initValueOptions.controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    initValueOptions.role = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_ButtonRole& value) {
        Ark_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.role = value;
        modifier_->setButtonOptions1(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonOptions1, attribute: options.role";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumButtonRoleInvalidValues) {
        checkValue(input, ArkValue<Opt_ButtonRole>(value));
    }
}

/*
 * @tc.name: setButtonOptions2TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_DEFAULT_VALUE) << "Default value for attribute 'label'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) << "Default value for attribute 'options.type'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE) << "Default value for attribute 'options.stateEffect'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE) << "Default value for attribute 'options.buttonStyle'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE) << "Default value for attribute 'options.controlSize'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROLE_DEFAULT_VALUE) << "Default value for attribute 'options.role'";
}

/*
 * @tc.name: setButtonOptions2TestLabelValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestLabelValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueLabel = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: label";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setButtonOptions2TestLabelInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestLabelInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](
                          const std::string& input, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueLabel = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: label";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setButtonOptions2TestOptionsTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestOptionsTypeValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ButtonType& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).type = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: options.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumButtonTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ButtonType>(value));
    }
}

/*
 * @tc.name: setButtonOptions2TestOptionsTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestOptionsTypeInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](
                          const std::string& input, const Opt_ButtonType& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).type = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: options.type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumButtonTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ButtonType>(value));
    }
}

/*
 * @tc.name: setButtonOptions2TestOptionsStateEffectValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestOptionsStateEffectValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).stateEffect = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: options.stateEffect";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setButtonOptions2TestOptionsStateEffectInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestOptionsStateEffectInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).stateEffect = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: options.stateEffect";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setButtonOptions2TestOptionsButtonStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestOptionsButtonStyleValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ButtonStyleMode& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).buttonStyle = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: options.buttonStyle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumButtonStyleModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ButtonStyleMode>(value));
    }
}

/*
 * @tc.name: setButtonOptions2TestOptionsButtonStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestOptionsButtonStyleInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](
                          const std::string& input, const Opt_ButtonStyleMode& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).buttonStyle = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: options.buttonStyle";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumButtonStyleModeInvalidValues) {
        checkValue(input, ArkValue<Opt_ButtonStyleMode>(value));
    }
}

/*
 * @tc.name: setButtonOptions2TestOptionsControlSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestOptionsControlSizeValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ControlSize& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).controlSize = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: options.controlSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumControlSizeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ControlSize>(value));
    }
}

/*
 * @tc.name: setButtonOptions2TestOptionsControlSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestOptionsControlSizeInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](
                          const std::string& input, const Opt_ControlSize& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).controlSize = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: options.controlSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumControlSizeInvalidValues) {
        checkValue(input, ArkValue<Opt_ControlSize>(value));
    }
}

/*
 * @tc.name: setButtonOptions2TestOptionsRoleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestOptionsRoleValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ButtonRole& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).role = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: options.role";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumButtonRoleValidValues) {
        checkValue(input, expected, ArkValue<Opt_ButtonRole>(value));
    }
}

/*
 * @tc.name: setButtonOptions2TestOptionsRoleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptions2TestOptionsRoleInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueLabel;
    Opt_ButtonOptions initValueOptions;

    // Initial setup
    initValueLabel = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(initValueOptions).type =
        ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));
    WriteTo(initValueOptions).stateEffect =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).buttonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));
    WriteTo(initValueOptions).controlSize =
        ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));
    WriteTo(initValueOptions).role =
        ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueLabel, &initValueOptions](
                          const std::string& input, const Opt_ButtonRole& value) {
        Ark_ResourceStr inputValueLabel = initValueLabel;
        Opt_ButtonOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).role = value;
        modifier_->setButtonOptions2(node, &inputValueLabel, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonOptions2, attribute: options.role";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumButtonRoleInvalidValues) {
        checkValue(input, ArkValue<Opt_ButtonRole>(value));
    }
}

/*
 * @tc.name: setTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) << "Default value for attribute 'type'";
}

/*
 * @tc.name: setTypeTestTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setTypeTestTypeValidValues, TestSize.Level1)
{
    Opt_ButtonType initValueType;

    // Initial setup
    initValueType = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));

    auto checkValue = [this, &initValueType](
                          const std::string& input, const std::string& expectedStr, const Opt_ButtonType& value) {
        Opt_ButtonType inputValueType = initValueType;

        inputValueType = value;
        modifier_->setType(node_, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setType, attribute: type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumButtonTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ButtonType>(value));
    }
}

/*
 * @tc.name: setTypeTestTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setTypeTestTypeInvalidValues, TestSize.Level1)
{
    Opt_ButtonType initValueType;

    // Initial setup
    initValueType = ArkValue<Opt_ButtonType>(std::get<1>(Fixtures::testFixtureEnumButtonTypeValidValues[0]));

    auto checkValue = [this, &initValueType](const std::string& input, const Opt_ButtonType& value) {
        Opt_ButtonType inputValueType = initValueType;

        modifier_->setType(node_, &inputValueType);
        inputValueType = value;
        modifier_->setType(node_, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setType, attribute: type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumButtonTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ButtonType>(value));
    }
}

/*
 * @tc.name: setStateEffectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setStateEffectTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE) << "Default value for attribute 'stateEffect'";
}

/*
 * @tc.name: setStateEffectTestStateEffectValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setStateEffectTestStateEffectValidValues, TestSize.Level1)
{
    Opt_Boolean initValueStateEffect;

    // Initial setup
    initValueStateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStateEffect](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueStateEffect = initValueStateEffect;

        inputValueStateEffect = value;
        modifier_->setStateEffect(node_, &inputValueStateEffect);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStateEffect, attribute: stateEffect";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setStateEffectTestStateEffectInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setStateEffectTestStateEffectInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueStateEffect;

    // Initial setup
    initValueStateEffect = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStateEffect](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueStateEffect = initValueStateEffect;

        modifier_->setStateEffect(node_, &inputValueStateEffect);
        inputValueStateEffect = value;
        modifier_->setStateEffect(node_, &inputValueStateEffect);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStateEffect, attribute: stateEffect";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setButtonStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE) << "Default value for attribute 'buttonStyle'";
}

/*
 * @tc.name: setButtonStyleTestButtonStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonStyleTestButtonStyleValidValues, TestSize.Level1)
{
    Opt_ButtonStyleMode initValueButtonStyle;

    // Initial setup
    initValueButtonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));

    auto checkValue = [this, &initValueButtonStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_ButtonStyleMode& value) {
        Opt_ButtonStyleMode inputValueButtonStyle = initValueButtonStyle;

        inputValueButtonStyle = value;
        modifier_->setButtonStyle(node_, &inputValueButtonStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setButtonStyle, attribute: buttonStyle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumButtonStyleModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ButtonStyleMode>(value));
    }
}

/*
 * @tc.name: setButtonStyleTestButtonStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonStyleTestButtonStyleInvalidValues, TestSize.Level1)
{
    Opt_ButtonStyleMode initValueButtonStyle;

    // Initial setup
    initValueButtonStyle =
        ArkValue<Opt_ButtonStyleMode>(std::get<1>(Fixtures::testFixtureEnumButtonStyleModeValidValues[0]));

    auto checkValue = [this, &initValueButtonStyle](const std::string& input, const Opt_ButtonStyleMode& value) {
        Opt_ButtonStyleMode inputValueButtonStyle = initValueButtonStyle;

        modifier_->setButtonStyle(node_, &inputValueButtonStyle);
        inputValueButtonStyle = value;
        modifier_->setButtonStyle(node_, &inputValueButtonStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setButtonStyle, attribute: buttonStyle";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumButtonStyleModeInvalidValues) {
        checkValue(input, ArkValue<Opt_ButtonStyleMode>(value));
    }
}

/*
 * @tc.name: setControlSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setControlSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE) << "Default value for attribute 'controlSize'";
}

/*
 * @tc.name: setControlSizeTestControlSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setControlSizeTestControlSizeValidValues, TestSize.Level1)
{
    Opt_ControlSize initValueControlSize;

    // Initial setup
    initValueControlSize = ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));

    auto checkValue = [this, &initValueControlSize](
                          const std::string& input, const std::string& expectedStr, const Opt_ControlSize& value) {
        Opt_ControlSize inputValueControlSize = initValueControlSize;

        inputValueControlSize = value;
        modifier_->setControlSize(node_, &inputValueControlSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setControlSize, attribute: controlSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumControlSizeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ControlSize>(value));
    }
}

/*
 * @tc.name: setControlSizeTestControlSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setControlSizeTestControlSizeInvalidValues, TestSize.Level1)
{
    Opt_ControlSize initValueControlSize;

    // Initial setup
    initValueControlSize = ArkValue<Opt_ControlSize>(std::get<1>(Fixtures::testFixtureEnumControlSizeValidValues[0]));

    auto checkValue = [this, &initValueControlSize](const std::string& input, const Opt_ControlSize& value) {
        Opt_ControlSize inputValueControlSize = initValueControlSize;

        modifier_->setControlSize(node_, &inputValueControlSize);
        inputValueControlSize = value;
        modifier_->setControlSize(node_, &inputValueControlSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setControlSize, attribute: controlSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumControlSizeInvalidValues) {
        checkValue(input, ArkValue<Opt_ControlSize>(value));
    }
}

/*
 * @tc.name: setRoleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setRoleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROLE_DEFAULT_VALUE) << "Default value for attribute 'role'";
}

/*
 * @tc.name: setRoleTestRoleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setRoleTestRoleValidValues, TestSize.Level1)
{
    Opt_ButtonRole initValueRole;

    // Initial setup
    initValueRole = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueRole](
                          const std::string& input, const std::string& expectedStr, const Opt_ButtonRole& value) {
        Opt_ButtonRole inputValueRole = initValueRole;

        inputValueRole = value;
        modifier_->setRole(node_, &inputValueRole);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRole, attribute: role";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumButtonRoleValidValues) {
        checkValue(input, expected, ArkValue<Opt_ButtonRole>(value));
    }
}

/*
 * @tc.name: setRoleTestRoleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setRoleTestRoleInvalidValues, TestSize.Level1)
{
    Opt_ButtonRole initValueRole;

    // Initial setup
    initValueRole = ArkValue<Opt_ButtonRole>(std::get<1>(Fixtures::testFixtureEnumButtonRoleValidValues[0]));

    auto checkValue = [this, &initValueRole](const std::string& input, const Opt_ButtonRole& value) {
        Opt_ButtonRole inputValueRole = initValueRole;

        modifier_->setRole(node_, &inputValueRole);
        inputValueRole = value;
        modifier_->setRole(node_, &inputValueRole);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRole, attribute: role";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumButtonRoleInvalidValues) {
        checkValue(input, ArkValue<Opt_ButtonRole>(value));
    }
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) << "Default value for attribute 'fontColor'";
}

/*
 * @tc.name: setFontColorTestFontColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontColorTestFontColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFontColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueFontColor = initValueFontColor;

        inputValueFontColor = value;
        modifier_->setFontColor(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontColor, attribute: fontColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontColorTestFontColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontColorTestFontColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFontColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueFontColor = initValueFontColor;

        modifier_->setFontColor(node_, &inputValueFontColor);
        inputValueFontColor = value;
        modifier_->setFontColor(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontColor, attribute: fontColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'fontSize'";
}

/*
 * @tc.name: setFontSizeTestFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setFontSizeTestFontSizeValidValues, TestSize.Level1)
{
    Opt_Length initValueFontSize;

    // Initial setup
    initValueFontSize =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueFontSize = initValueFontSize;

        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontSizeTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Length initValueFontSize;

    // Initial setup
    initValueFontSize =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueFontSize](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueFontSize = initValueFontSize;

        modifier_->setFontSize(node_, &inputValueFontSize);
        inputValueFontSize = value;
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setFontWeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setFontWeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) << "Default value for attribute 'fontWeight'";
}

/*
 * @tc.name: setFontWeightTestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontWeightTestFontWeightValidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_FontWeight_String& value) {
        Opt_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;

        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontWeightTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontWeightTestFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_String initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](
                          const std::string& input, const Opt_Union_Number_FontWeight_String& value) {
        Opt_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;

        modifier_->setFontWeight(node_, &inputValueFontWeight);
        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_FontWeight_String>());
}

/*
 * @tc.name: setFontStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE) << "Default value for attribute 'fontStyle'";
}

/*
 * @tc.name: setFontStyleTestFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontStyleTestFontStyleValidValues, TestSize.Level1)
{
    Opt_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFontStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_FontStyle inputValueFontStyle = initValueFontStyle;

        inputValueFontStyle = value;
        modifier_->setFontStyle(node_, &inputValueFontStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontStyle, attribute: fontStyle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFontStyleTestFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontStyleTestFontStyleInvalidValues, TestSize.Level1)
{
    Opt_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFontStyle](const std::string& input, const Opt_FontStyle& value) {
        Opt_FontStyle inputValueFontStyle = initValueFontStyle;

        modifier_->setFontStyle(node_, &inputValueFontStyle);
        inputValueFontStyle = value;
        modifier_->setFontStyle(node_, &inputValueFontStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontStyle, attribute: fontStyle";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFontFamilyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontFamilyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE) << "Default value for attribute 'fontFamily'";
}

/*
 * @tc.name: setFontFamilyTestFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setFontFamilyTestFontFamilyValidValues, TestSize.Level1)
{
    Opt_Union_String_Resource initValueFontFamily;

    // Initial setup
    initValueFontFamily = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_Union_String_Resource inputValueFontFamily = initValueFontFamily;

        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontFamilyTestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontFamilyTestFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_Union_String_Resource initValueFontFamily;

    // Initial setup
    initValueFontFamily = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_Union_String_Resource inputValueFontFamily = initValueFontFamily;

        modifier_->setFontFamily(node_, &inputValueFontFamily);
        inputValueFontFamily = value;
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFamilyResourceInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontFamilyStringInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setLabelStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setLabelStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultLabelStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
    std::unique_ptr<JsonValue> resultFont =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_FONT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_OVERFLOW_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_OVERFLOW_DEFAULT_VALUE) <<
        "Default value for attribute 'labelStyle.overflow'";

    resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_MAX_LINES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_MAX_LINES_DEFAULT_VALUE) <<
        "Default value for attribute 'labelStyle.maxLines'";

    resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_MIN_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_MIN_FONT_SIZE_DEFAULT_VALUE) <<
        "Default value for attribute 'labelStyle.minFontSize'";

    resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_MAX_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_MAX_FONT_SIZE_DEFAULT_VALUE) <<
        "Default value for attribute 'labelStyle.maxFontSize'";

    resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_HEIGHT_ADAPTIVE_POLICY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE) <<
        "Default value for attribute 'labelStyle.heightAdaptivePolicy'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_SIZE_DEFAULT_VALUE) <<
        "Default value for attribute 'labelStyle.font.size'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_WEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'labelStyle.font.weight'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_FAMILY_DEFAULT_VALUE) <<
        "Default value for attribute 'labelStyle.font.family'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_LABEL_STYLE_I_FONT_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_FONT_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'labelStyle.font.style'";
}

/*
 * @tc.name: setLabelStyleTestLabelStyleOverflowValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setLabelStyleTestLabelStyleOverflowValidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_TextOverflow& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(inputValueLabelStyle).overflow = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_OVERFLOW_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.overflow";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextOverflowValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextOverflow>(value));
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleOverflowInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setLabelStyleTestLabelStyleOverflowInvalidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const Opt_TextOverflow& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(inputValueLabelStyle).overflow = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_OVERFLOW_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_OVERFLOW_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.overflow";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextOverflowInvalidValues) {
        checkValue(input, ArkValue<Opt_TextOverflow>(value));
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleMaxLinesValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleMaxLinesValidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(inputValueLabelStyle).maxLines = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_MAX_LINES_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.maxLines";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberPosIntFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleMaxLinesInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleMaxLinesInvalidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const Opt_Number& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(inputValueLabelStyle).maxLines = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_MAX_LINES_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_MAX_LINES_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.maxLines";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberPosIntFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setLabelStyleTestLabelStyleMinFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleMinFontSizeValidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_ResourceStr& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(inputValueLabelStyle).minFontSize = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_MIN_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.minFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_Number_ResourceStr, Ark_ResourceStr>(ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_Number_ResourceStr, Ark_ResourceStr>(ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleMinFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleMinFontSizeInvalidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](
                          const std::string& input, const Opt_Union_Number_ResourceStr& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(inputValueLabelStyle).minFontSize = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_MIN_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_MIN_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.minFontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input,
            ArkUnion<Opt_Union_Number_ResourceStr, Ark_ResourceStr>(ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input,
            ArkUnion<Opt_Union_Number_ResourceStr, Ark_ResourceStr>(ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_ResourceStr>());
}

/*
 * @tc.name: setLabelStyleTestLabelStyleMaxFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleMaxFontSizeValidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_ResourceStr& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(inputValueLabelStyle).maxFontSize = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_MAX_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.maxFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_Number_ResourceStr, Ark_ResourceStr>(ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_Number_ResourceStr, Ark_ResourceStr>(ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleMaxFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleMaxFontSizeInvalidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](
                          const std::string& input, const Opt_Union_Number_ResourceStr& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(inputValueLabelStyle).maxFontSize = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_MAX_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_MAX_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.maxFontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input,
            ArkUnion<Opt_Union_Number_ResourceStr, Ark_ResourceStr>(ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input,
            ArkUnion<Opt_Union_Number_ResourceStr, Ark_ResourceStr>(ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_ResourceStr>());
}

/*
 * @tc.name: setLabelStyleTestLabelStyleHeightAdaptivePolicyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleHeightAdaptivePolicyValidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](const std::string& input, const std::string& expectedStr,
                          const Opt_TextHeightAdaptivePolicy& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        WriteTo(inputValueLabelStyle).heightAdaptivePolicy = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_HEIGHT_ADAPTIVE_POLICY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.heightAdaptivePolicy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextHeightAdaptivePolicy>(value));
    }
}

/*
 * @tc.name: setLabelStyleTestLabelStyleHeightAdaptivePolicyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestLabelStyleHeightAdaptivePolicyInvalidValues, TestSize.Level1)
{
    Opt_ButtonLabelStyle initValueLabelStyle;

    // Initial setup
    WriteTo(initValueLabelStyle).overflow =
        ArkValue<Opt_TextOverflow>(std::get<1>(Fixtures::testFixtureEnumTextOverflowValidValues[0]));
    WriteTo(initValueLabelStyle).maxLines =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteTo(initValueLabelStyle).minFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).maxFontSize = ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueLabelStyle).heightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(WriteTo(initValueLabelStyle).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueLabelStyle](
                          const std::string& input, const Opt_TextHeightAdaptivePolicy& value) {
        Opt_ButtonLabelStyle inputValueLabelStyle = initValueLabelStyle;

        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        WriteTo(inputValueLabelStyle).heightAdaptivePolicy = value;
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_I_HEIGHT_ADAPTIVE_POLICY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LABEL_STYLE_I_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLabelStyle, attribute: labelStyle.heightAdaptivePolicy";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyInvalidValues) {
        checkValue(input, ArkValue<Opt_TextHeightAdaptivePolicy>(value));
    }
}

} // namespace OHOS::Ace::NG
