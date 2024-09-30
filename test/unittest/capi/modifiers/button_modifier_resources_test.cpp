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
    const auto ATTRIBUTE_LABEL_NAME("label");
    const auto ATTRIBUTE_TYPE_NAME("type");
    const auto ATTRIBUTE_ROLE_NAME("role");
    const auto ATTRIBUTE_STATE_EFFECT_NAME("stateEffect");
    const auto ATTRIBUTE_CONTROL_SIZE_NAME("controlSize");
    const auto ATTRIBUTE_BUTTON_STYLE_NAME("buttonStyle");
    const auto ATTRIBUTE_FONT_COLOR_NAME("fontColor");
    const auto ATTRIBUTE_FONT_SIZE_NAME("fontSize");
    const auto ATTRIBUTE_FONT_FAMILY_NAME("fontFamily");
    const auto ATTRIBUTE_LABEL_STYLE_NAME = "labelStyle";
    const auto ATTRIBUTE_LABEL_STYLE_FONT_NAME = "font";
    const auto ATTRIBUTE_LABEL_STYLE_FONT_FAMILY_NAME("family");

    using ButtonLabelResourceTest = std::tuple<ResourceStr, std::string>;

    // resource names and id
    const auto RES_NAME = NamedResourceId{"aa.bb.cc", NodeModifier::ResourceType::STRING};
    const auto RES_ID = IntResourceId{11111, NodeModifier::ResourceType::STRING};

    const auto RES_COLOR_NAME = "color_name";
    const auto RES_COLOR_ARK_NAME = Converter::ArkValue<Ark_String>(RES_COLOR_NAME);
    const auto RES_COLOR_ID = 123456;

    const auto RES_DIMENSION_ID = 654321;

    const auto RES_FAMILY_NAME = "family_resource";
    const auto RES_FAMILY_ARK_NAME = Converter::ArkValue<Ark_String>(RES_FAMILY_NAME);
    const auto RES_FAMILY_ID = 22222;

    // resource values
    const auto RESOURCE_BY_STRING = "ResourceByString";
    const auto RESOURCE_BY_NUMBER = "ResourceByNumber";

    const auto COLOR_BY_STRING = Color(0xFF123456);
    const auto COLOR_BY_NUMBER = Color(0xFF654321);

    const auto DIMENSION_BY_NUMBER = Dimension(5, DimensionUnit::VP);

    const auto FAMILY_BY_STRING = "first";
    const auto FAMILY_BY_NUMBER = "second";

    const std::vector<ButtonLabelResourceTest> BUTTON_LABEL_RESOURCES_TEST_PLAN = {
        { CreateResourceUnion<ResourceStr>(RES_NAME), RESOURCE_BY_STRING },
        { CreateResourceUnion<ResourceStr>(RES_ID), RESOURCE_BY_NUMBER },
        { CreateResourceUnion<ResourceStr>(-1), RESOURCE_BY_NUMBER },
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
HWTEST_F(ButtonModifierResourcesTest, SetButtonOptions2TestLabelResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    ResourceStr label;
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

    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkResource(const_cast<Ark_String*>(&RES_COLOR_ARK_NAME),
            -1, NodeModifier::ResourceType::COLOR)), COLOR_BY_STRING.ColorToString() },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkResource(nullptr,
            RES_COLOR_ID, NodeModifier::ResourceType::COLOR)), COLOR_BY_NUMBER.ColorToString() },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkResource(nullptr,
            -1, NodeModifier::ResourceType::COLOR)), "#FFFF0000" }, // this color is default in the themeConstants
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        modifier_->setFontColor(node_, &arkResColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setFontSizeTestResources
 * @tc.desc: check setFontSize from resource
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierResourcesTest, setFontSizeTestResources, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;

    using OneTestStep = std::pair<Ark_Length, std::string>;
    const std::vector<OneTestStep> testPlan = {
        { { .type = ARK_TAG_RESOURCE, .resource = RES_DIMENSION_ID }, "5.00vp" },
        { { .type = ARK_TAG_RESOURCE, .resource = -1 }, "10.00px" }
    };

    for (const auto &[arkLength, expected]: testPlan) {
        modifier_->setFontSize(node_, &arkLength);
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

    using ResourceTest = std::tuple<Union_String_Resource, std::string>;
    const std::vector<ResourceTest> testPlan = {
        { Converter::ArkUnion<Union_String_Resource, Ark_Resource>(
            ArkResource(const_cast<Ark_String*>(&RES_FAMILY_ARK_NAME),
            -1, NodeModifier::ResourceType::STRARRAY)),
            FAMILY_BY_STRING },
        { Converter::ArkUnion<Union_String_Resource, Ark_Resource>(ArkResource(nullptr, RES_FAMILY_ID,
            NodeModifier::ResourceType::STRARRAY)),
            FAMILY_BY_NUMBER },
    };

    for (const auto& [family, expectValue] : testPlan) {
        modifier_->setFontFamily(node_, &family);
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
    Ark_LabelStyle inputValueLabelStyle;

    using ResourceTest = std::tuple<Opt_Union_String_Resource, std::string>;
    const std::vector<ResourceTest> testPlan = {
        { Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
            ArkResource(const_cast<Ark_String*>(&RES_FAMILY_ARK_NAME),
            -1, NodeModifier::ResourceType::STRARRAY)),
            FAMILY_BY_STRING },
        { Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(ArkResource(nullptr, RES_FAMILY_ID,
            NodeModifier::ResourceType::STRARRAY)),
            FAMILY_BY_NUMBER },
        { Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(ArkResource(nullptr, -1,
            NodeModifier::ResourceType::STRARRAY)),
            FAMILY_BY_NUMBER }
    };

    for (const auto& [family, expectValue] : testPlan) {
        fontLabel.family = family;
        inputValueLabelStyle.font = ArkValue<Opt_Font>(fontLabel);
        modifier_->setLabelStyle(node_, &inputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        auto resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto font = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_FONT_NAME);
        auto familyString = GetAttrValue<std::string>(font, ATTRIBUTE_LABEL_STYLE_FONT_FAMILY_NAME);
        EXPECT_EQ(familyString, expectValue);
    }
}
} // namespace OHOS::Ace::NG
