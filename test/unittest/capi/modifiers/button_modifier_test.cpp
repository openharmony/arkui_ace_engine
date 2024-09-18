/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "node_api.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components/button/button_theme.h"

#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
    // attrs
    const auto ATTRIBUTE_TYPE_NAME("type");
    const auto ATTRIBUTE_ROLE_NAME("role");
    const auto ATTRIBUTE_STATE_EFFECT_NAME("stateEffect");
    const auto ATTRIBUTE_CONTROL_SIZE_NAME("controlSize");
    const auto ATTRIBUTE_BUTTON_STYLE_NAME("buttonStyle");

    // default values
    const auto ATTRIBUTE_TYPE_DEFAULT_VALUE("ButtonType.Capsule");
    const auto ATTRIBUTE_ROLE_DEFAULT_VALUE("ButtonRole.NORMAL");
    const auto ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE("true");
    const auto ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE("ControlSize.NORMAL");
    const auto ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE("ButtonStyleMode.EMPHASIZED");

    // typedefs
    using ButtonTypeTest = std::pair<Ark_ButtonType, std::string>;
    using ButtonRoleTest = std::pair<Ark_ButtonRole, std::string>;
    using ButtonControlSizeTest = std::pair<Ark_ControlSize, std::string>;
    using ButtonStyleModeTest = std::pair<Ark_ButtonStyleMode, std::string>;
    using BoolTest = std::pair<Ark_Boolean, std::string>;
    // test plans
    const std::vector<ButtonTypeTest> BUTTON_TYPE_TEST_PLAN = {
        { ARK_BUTTON_TYPE_NORMAL, "ButtonType.Normal" },
        { ARK_BUTTON_TYPE_CAPSULE, "ButtonType.Capsule" },
        { ARK_BUTTON_TYPE_CIRCLE, "ButtonType.Circle" },
        { ARK_BUTTON_TYPE_ROUNDED_RECTANGLE, "ButtonType.ROUNDED_RECTANGLE" },
        // Invalid values shouldn't change options
        { static_cast<Ark_ButtonType>(-100), "ButtonType.ROUNDED_RECTANGLE" },
        { static_cast<Ark_ButtonType>(100), "ButtonType.ROUNDED_RECTANGLE" }
    };
    const std::vector<ButtonRoleTest> BUTTON_ROLE_TEST_PLAN = {
        { ARK_BUTTON_ROLE_NORMAL, "ButtonRole.NORMAL" },
        { ARK_BUTTON_ROLE_ERROR, "ButtonRole.ERROR" },
        // Invalid values shouldn't change options
        { static_cast<Ark_ButtonRole>(-100), "ButtonRole.ERROR" },
        { static_cast<Ark_ButtonRole>(100), "ButtonRole.ERROR" }
    };
    const std::vector<ButtonControlSizeTest> BUTTON_CONTROL_SIZE_TEST_PLAN = {
        { ARK_CONTROL_SIZE_NORMAL, "ControlSize.NORMAL" },
        { ARK_CONTROL_SIZE_SMALL, "ControlSize.SMALL" },
        // Invalid values shouldn't change options
        { static_cast<Ark_ControlSize>(-100), "ControlSize.SMALL" },
        { static_cast<Ark_ControlSize>(100), "ControlSize.SMALL" }
    };
    const std::vector<ButtonStyleModeTest> BUTTON_STYLE_MODE_TEST_PLAN = {
        { ARK_BUTTON_STYLE_MODE_NORMAL, "ButtonStyleMode.NORMAL" },
        { ARK_BUTTON_STYLE_MODE_EMPHASIZED, "ButtonStyleMode.EMPHASIZED" },
        { ARK_BUTTON_STYLE_MODE_TEXTUAL, "ButtonStyleMode.TEXTUAL" },
        // Invalid values shouldn't change options
        { static_cast<Ark_ButtonStyleMode>(-100), "ButtonStyleMode.TEXTUAL" },
        { static_cast<Ark_ButtonStyleMode>(100), "ButtonStyleMode.TEXTUAL" }
    };
    const std::vector<BoolTest> BOOL_TEST_PLAN = {
        { false, "false" },
        { true, "true" },
        { 0, "false" },
        { -25, "true" },
        { 0, "false" },
        { 25, "true" },
        { false, "false" }
    };
} // namespace

class ButtonModifierTest : public ModifierTestBase<GENERATED_ArkUIButtonModifier,
    &GENERATED_ArkUINodeModifiers::getButtonModifier, GENERATED_ARKUI_BUTTON> {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();

        // assume using of test/mock/core/common/mock_theme_constants.cpp in build
        auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
        MockThemeStyle::GetInstance()->SetAttr("button_pattern", { .value = themeStyle });
        themeConstants->LoadTheme(0);

        // build default ButtonTheme
        ButtonTheme::Builder builder;
        auto buttonTheme = builder.Build(themeConstants);

        // create Theme Manager and provide return of ButtonTheme
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetThemeConstants(testing::_, testing::_))
            .WillRepeatedly(Return(themeConstants));
        EXPECT_CALL(*themeManager, GetTheme(testing::_))
            .WillRepeatedly(Return(buttonTheme));

        // setup Context with Theme Manager and Container
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/*
 * @tc.name: setButtonOptionsTestDefaultValues
 * @tc.desc: Check dafault options values
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROLE_DEFAULT_VALUE);
}

/**
 * @tc.name: SetButtonOptions0Test
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions0
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, SetButtonOptions0Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setButtonOptions0, nullptr);
    modifier_->setButtonOptions0(node_);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto type = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto stateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto controlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto buttonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto role = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);

    EXPECT_EQ(type, ATTRIBUTE_TYPE_DEFAULT_VALUE);
    EXPECT_EQ(stateEffect, ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE);
    EXPECT_EQ(controlSize, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE);
    EXPECT_EQ(buttonStyle, ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE);
    EXPECT_EQ(role, ATTRIBUTE_ROLE_DEFAULT_VALUE);
}
/*
 * @tc.name: SetButtonOptions1TestButtonType
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions1
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, SetButtonOptions1TestButtonType, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    // Test
    modifier_->setButtonOptions1(node_, &inputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto type : BUTTON_TYPE_TEST_PLAN) {
        inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(type.first);
        modifier_->setButtonOptions1(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        EXPECT_EQ(checkType, type.second);
    }
}
/*
 * @tc.name: SetButtonOptions1TestStateEffect
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions1
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, SetButtonOptions1TestStateEffect, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    // Test
    modifier_->setButtonOptions1(node_, &inputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto stateEffect : BOOL_TEST_PLAN) {
        inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(stateEffect.first);
        modifier_->setButtonOptions1(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
        EXPECT_EQ(checkStateEffect, stateEffect.second);
    }
}
/*
 * @tc.name: SetButtonOptions1TestButtonStyleMode
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions1
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, SetButtonOptions1ButtonTypeTestButtonStyleMode, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    // Test
    modifier_->setButtonOptions1(node_, &inputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto styleMode : BUTTON_STYLE_MODE_TEST_PLAN) {
        inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(styleMode.first);
        modifier_->setButtonOptions1(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
        EXPECT_EQ(checkButtonStyle, styleMode.second);
    }
}
/*
 * @tc.name: SetButtonOptions1TestControlSize
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions1
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, SetButtonOptions1TestControlSize, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    // Test
    modifier_->setButtonOptions1(node_, &inputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto controlSize : BUTTON_CONTROL_SIZE_TEST_PLAN) {
        inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(controlSize.first);
        modifier_->setButtonOptions1(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        EXPECT_EQ(checkControlSize, controlSize.second);
    }
}
/*
 * @tc.name: SetButtonOptions1TestButtonRole
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions1
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, SetButtonOptions1TestButtonRole, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    // Test
    modifier_->setButtonOptions1(node_, &inputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto role : BUTTON_ROLE_TEST_PLAN) {
        inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(role.first);
        modifier_->setButtonOptions1(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
        EXPECT_EQ(checkRole, role.second);
    }
}
} // namespace OHOS::Ace::NG
