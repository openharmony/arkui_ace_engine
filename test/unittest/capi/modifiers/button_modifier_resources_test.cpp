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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components/button/button_theme.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
    // attrs
#ifdef WRONG_GEN
    const auto ATTRIBUTE_LABEL_NAME("label");
    const auto ATTRIBUTE_TYPE_NAME("type");
    const auto ATTRIBUTE_ROLE_NAME("role");
    const auto ATTRIBUTE_STATE_EFFECT_NAME("stateEffect");
    const auto ATTRIBUTE_CONTROL_SIZE_NAME("controlSize");
    const auto ATTRIBUTE_BUTTON_STYLE_NAME("buttonStyle");
#endif
    const auto ATTRIBUTE_FONT_COLOR_NAME("fontColor");
    const auto ATTRIBUTE_FONT_SIZE_NAME("fontSize");
    const auto ATTRIBUTE_FONT_FAMILY_NAME("fontFamily");
    const auto ATTRIBUTE_LABEL_STYLE_NAME = "labelStyle";
    const auto ATTRIBUTE_LABEL_STYLE_FONT_NAME = "font";
    const auto ATTRIBUTE_LABEL_STYLE_FONT_FAMILY_NAME("family");

    const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE("0.00px");

    using ButtonLabelResourceTest = std::tuple<Ark_ResourceStr, std::string>;

    // invalid id
    const auto INVALID_ID_STRING = IntResourceId{-1, ResourceType::STRING};
    const auto INVALID_ID_COLOR = IntResourceId{-1, ResourceType::COLOR};

    // resource names and id
    const auto RES_NAME = NamedResourceId{"aa.bb.cc", ResourceType::STRING};
    const auto RES_ID = IntResourceId{11111, ResourceType::STRING};

    const auto RES_COLOR_NAME = NamedResourceId{"color_name", ResourceType::COLOR};
    const auto RES_COLOR_ID = IntResourceId{123456, ResourceType::COLOR};

    const int64_t RES_DIMENSION_ID = 654321; // Ark_Length.Resource

    const auto RES_FAMILY_NAME = NamedResourceId{"family_resource", ResourceType::STRARRAY};
    const auto RES_FAMILY_ID = IntResourceId{22222, ResourceType::STRARRAY};

    // resource values
    const auto RESOURCE_BY_STRING = "ResourceByString";
    const auto RESOURCE_BY_NUMBER = "ResourceByNumber";

    const auto COLOR_BY_STRING = Color(0xFF123456);
    const auto COLOR_BY_NUMBER = Color(0xFF654321);

    const auto DIMENSION_BY_NUMBER = Dimension(5, DimensionUnit::VP);

    const auto FAMILY_BY_STRING = "first";
    const auto FAMILY_BY_NUMBER = "second";

    const std::vector<ButtonLabelResourceTest> BUTTON_LABEL_RESOURCES_TEST_PLAN = {
        { CreateResourceUnion<Ark_ResourceStr>(INVALID_ID_STRING), "" },
        { CreateResourceUnion<Ark_ResourceStr>(RES_NAME), RESOURCE_BY_STRING },
        { CreateResourceUnion<Ark_ResourceStr>(RES_ID), RESOURCE_BY_NUMBER },
    };
} // namespace

class ButtonModifierResourcesTest : public ModifierTestBase<GENERATED_ArkUIButtonModifier,
    &GENERATED_ArkUINodeModifiers::getButtonModifier, GENERATED_ARKUI_BUTTON> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<ButtonTheme>();

        // set test values to Theme Pattern as data for the Theme building
        AddResource(RES_ID, RESOURCE_BY_NUMBER);
        AddResource(RES_NAME, RESOURCE_BY_STRING);

        AddResource(RES_COLOR_ID, COLOR_BY_NUMBER);
        AddResource(RES_COLOR_NAME, COLOR_BY_STRING);

        AddResource(RES_DIMENSION_ID, DIMENSION_BY_NUMBER);

        AddResource(RES_FAMILY_ID, FAMILY_BY_NUMBER);
        AddResource(RES_FAMILY_NAME, FAMILY_BY_STRING);
    }
};

/*
 * @tc.name: SetButtonOptions2TestButtonRole
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions2
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierResourcesTest, DISABLED_SetButtonOptions2TestLabelResource, TestSize.Level1)
{
#ifdef WRONG_GEN
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    Ark_ResourceStr label;
    std::string expectValue;
    std::tie(label, expectValue) = BUTTON_LABEL_RESOURCES_TEST_PLAN.front();
    auto optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
    // Test
    modifier_->setButtonOptions2(node_, &label, &optInputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    auto checkLabel = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    EXPECT_EQ(checkLabel, expectValue);

    for (const auto& [label, expected] : BUTTON_LABEL_RESOURCES_TEST_PLAN) {
        modifier_->setButtonOptions2(node_, &label, &optInputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_NAME);
        EXPECT_EQ(resultStr, expected);
    }
#endif
}

/*
 * @tc.name: setFontColorTestResourceColorValues
 * @tc.desc: Check the functionality of ButtonModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierResourcesTest, setFontColorTestResourceColorValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    typedef std::pair<Opt_ResourceColor, std::string> OneTestStep;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_NAME)),
            COLOR_BY_STRING.ColorToString() },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(CreateResource(RES_COLOR_ID)),
            COLOR_BY_NUMBER.ColorToString() },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(CreateResource(INVALID_ID_COLOR)),
            "#FFFF0000" }
    };

    for (const auto &[optResColor, expected]: testPlan) {
        modifier_->setFontColor(node_, &optResColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setFontSizeTestResourcesValidResources
 * @tc.desc: check setFontSize from resource
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierResourcesTest, DISABLED_setFontSizeTestResourcesValidResources, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;

    using OneTestStep = std::pair<Opt_Length, std::string>;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_Length>(RES_DIMENSION_ID), "5.00vp" },
    };

    for (const auto &[optLength, expected]: testPlan) {
        modifier_->setFontSize(node_, &optLength);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(result, expected);
    }
}

/*
 * @tc.name: setFontSizeTestResourcesInvalidResources
 * @tc.desc: check setFontSize from resource
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierResourcesTest, setFontSizeTestResourcesInvalidResources, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;

    using OneTestStep = std::pair<Opt_Length, std::string>;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_Length>(static_cast<int64_t>(-1)), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
    };

    for (const auto &[optLength, expected]: testPlan) {
        modifier_->setFontSize(node_, &optLength);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(result, expected);
    }
}

/*
 * @tc.name: setFontFamilyTestResources
 * @tc.desc: Check the functionality of ButtonModifier.setFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierResourcesTest, setFontFamilyTestResources, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    using ResourceTest = std::tuple<Opt_Union_String_Resource, std::string>;
    const std::vector<ResourceTest> testPlan = {
        { Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_FAMILY_NAME)),
            FAMILY_BY_STRING },
        { Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_FAMILY_ID)),
            FAMILY_BY_NUMBER },
    };

    for (const auto& [optFamily, expectValue] : testPlan) {
        modifier_->setFontFamily(node_, &optFamily);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setLabelStyleTestResources
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierResourcesTest, setLabelStyleTestResources, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_Font fontLabel;
    Ark_ButtonLabelStyle inputValueLabelStyle;

    using ResourceTest = std::tuple<Opt_Union_String_Resource, std::string>;
    const std::vector<ResourceTest> testPlan = {
        { Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
            CreateResource(RES_FAMILY_NAME)),
            FAMILY_BY_STRING },
        { Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
            CreateResource(RES_FAMILY_ID)),
            FAMILY_BY_NUMBER },
    };

    for (const auto& [family, expectValue] : testPlan) {
        fontLabel.family = family;
        inputValueLabelStyle.font = ArkValue<Opt_Font>(fontLabel);
        auto optInputValueLabelStyle = ArkValue<Opt_ButtonLabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto font = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_FONT_NAME);
        auto familyString = GetAttrValue<std::string>(font, ATTRIBUTE_LABEL_STYLE_FONT_FAMILY_NAME);
        EXPECT_EQ(familyString, expectValue);
    }
}
} // namespace OHOS::Ace::NG
