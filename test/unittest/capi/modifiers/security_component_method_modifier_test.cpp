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
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace Converter;

namespace  {
    const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
    const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "16.00fp";
    const auto ATTRIBUTE_ICON_SIZE_NAME = "iconSize";
    const auto ATTRIBUTE_ICON_SIZE_DEFAULT_VALUE = "16.00vp";
    const auto ATTRIBUTE_LAYOUT_DIRECTION_NAME = "layoutDirection";
    const auto ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE = SecurityComponentLayoutDirection::HORIZONTAL;
    const auto ATTRIBUTE_TEXT_ICON_SPACE_NAME = "textIconSpace";
    const auto ATTRIBUTE_TEXT_ICON_SPACE_DEFAULT_VALUE = "4vp";

    const auto THEME_ICON_SIZE = Dimension(16., DimensionUnit::VP);
    const auto THEME_FONT_SIZE = Dimension(16., DimensionUnit::FP);
    const auto THEME_TEXT_ICON_SPACE = Dimension(4., DimensionUnit::VP);

    const auto DEFAULT_JSON_INT = -1;

    const uint32_t FLOAT_RES_0_ID = 100;
    const float FLOAT_RES_0_VALUE = 70.5f;
    const auto FLOAT_RES_0_STORED_VALUE = Dimension(FLOAT_RES_0_VALUE, DimensionUnit::PX);
    const Ark_Resource FLOAT_RES_0 = CreateResource(FLOAT_RES_0_ID, NodeModifier::ResourceType::FLOAT);

    const uint32_t FLOAT_RES_1_ID = 101;
    const float FLOAT_RES_1_VALUE = 19.5f;
    const auto FLOAT_RES_1_STORED_VALUE = Dimension(FLOAT_RES_1_VALUE, DimensionUnit::FP);
    const Ark_Resource FLOAT_RES_1 = CreateResource(FLOAT_RES_1_ID, NodeModifier::ResourceType::FLOAT);
} // namespace

class SecurityComponentMethodModifierTest : public ModifierTestBase<GENERATED_ArkUISecurityComponentMethodModifier,
    &GENERATED_ArkUINodeModifiers::getSecurityComponentMethodModifier, GENERATED_ARKUI_SAVE_BUTTON> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = SetupThemeStyle(THEME_PATTERN_SECURITY_COMPONENT);
        themeStyle->SetAttr("icon_size", { .value = THEME_ICON_SIZE });
        themeStyle->SetAttr("font_size", { .value = THEME_FONT_SIZE });
        themeStyle->SetAttr("text_icon_pading", { .value = THEME_TEXT_ICON_SPACE });

        SetupTheme<SecurityComponentTheme>();

        AddResource(FLOAT_RES_0_ID, FLOAT_RES_0_STORED_VALUE);
        AddResource(FLOAT_RES_1_ID, FLOAT_RES_1_STORED_VALUE);
    }

    void SetUp(void) override
    {
        ModifierTestBase::SetUp();

        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        SaveButtonModelNG::InitSaveButton(frameNode, SaveButtonStyle(), false);

        OnModifyDone();
    }

    void OnModifyDone()
    {
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto pattern = frameNode->GetPattern();
        ASSERT_TRUE(pattern);
        pattern->OnModifyDone();
    }
};

/*
 * @tc.name: setIconSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setIconSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ICON_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ICON_SIZE_DEFAULT_VALUE);
}

// Valid values for attribute 'iconSize' of method 'iconSize'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> iconSizeIconSizeValidValues = {
    { "123", ArkValue<Ark_Length>(123), "123.00px" },
    { "60.25f", ArkValue<Ark_Length>(60.25f), "60.25vp" },
    { "ResId:FLOAT_RES_0_ID", { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID }, "70.50px" }
};

/*
 * @tc.name: setIconSizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setIconSizeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueIconSize;
    Ark_Length initValueIconSize;

    // Initial setup
    initValueIconSize = std::get<1>(iconSizeIconSizeValidValues[0]);

    // Verifying attribute's  values
    inputValueIconSize = initValueIconSize;
    for (auto&& value: iconSizeIconSizeValidValues) {
        inputValueIconSize = std::get<1>(value);
        modifier_->setIconSize(node_, &inputValueIconSize);
        OnModifyDone();

        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ICON_SIZE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'iconSize'
static std::vector<std::tuple<std::string, Ark_Length>> iconSizeInvalidValues = {
    { "-15", ArkValue<Ark_Length>(-15) },
};

/*
 * @tc.name: setIconSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setIconSizeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueIconSize;
    Ark_Length initValueIconSize;
    std::string initValueStr;

    // Initial setup
    initValueIconSize = std::get<1>(iconSizeIconSizeValidValues[0]);
    initValueStr = std::get<2>(iconSizeIconSizeValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: iconSizeInvalidValues) {
        inputValueIconSize = initValueIconSize;
        modifier_->setIconSize(node_, &inputValueIconSize);
        OnModifyDone();

        inputValueIconSize = std::get<1>(value);
        modifier_->setIconSize(node_, &inputValueIconSize);
        OnModifyDone();

        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ICON_SIZE_NAME);
        expectedStr = initValueStr; // expect that invalid value should be ignored
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setLayoutDirectionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setLayoutDirectionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    int32_t result;

    result = jsonValue->GetInt(ATTRIBUTE_LAYOUT_DIRECTION_NAME, DEFAULT_JSON_INT);
    EXPECT_EQ(result, static_cast<int32_t>(ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE));
}

// Valid values for attribute 'layoutDirection' of method 'layoutDirection'
using ValidValuesStep = std::tuple<
    std::string,
    Ark_SecurityComponentLayoutDirection,
    SecurityComponentLayoutDirection
>;
static std::vector<ValidValuesStep> layoutDirectionLayoutDirectionValidValues = {
    {
        "ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_HORIZONTAL",
        ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_HORIZONTAL,
        SecurityComponentLayoutDirection::HORIZONTAL
    },
    {
        "ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_VERTICAL",
        ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_VERTICAL,
        SecurityComponentLayoutDirection::VERTICAL
    }
};

/*
 * @tc.name: setLayoutDirectionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setLayoutDirectionTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int32_t result;
    int32_t expected;
    Ark_SecurityComponentLayoutDirection inputValueLayoutDirection;
    Ark_SecurityComponentLayoutDirection initValueLayoutDirection;

    // Initial setup
    initValueLayoutDirection = std::get<1>(layoutDirectionLayoutDirectionValidValues[0]);

    // Verifying attribute's  values
    inputValueLayoutDirection = initValueLayoutDirection;
    for (auto&& value: layoutDirectionLayoutDirectionValidValues) {
        inputValueLayoutDirection = std::get<1>(value);
        modifier_->setLayoutDirection(node_, inputValueLayoutDirection);
        jsonValue = GetJsonValue(node_);
        result = jsonValue->GetInt(ATTRIBUTE_LAYOUT_DIRECTION_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(std::get<2>(value));
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'layoutDirection' of method 'layoutDirection'
using InvalidValuesStep = std::tuple<std::string, Ark_SecurityComponentLayoutDirection>;
static std::vector<InvalidValuesStep> layoutDirectionLayoutDirectionInvalidValues = {
    {
        "static_cast<Ark_SecurityComponentLayoutDirection>(-1)",
        static_cast<Ark_SecurityComponentLayoutDirection>(-1)
    },
};

/*
 * @tc.name: setLayoutDirectionTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setLayoutDirectionTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int32_t result;
    int32_t expected;
    Ark_SecurityComponentLayoutDirection inputValueLayoutDirection;
    Ark_SecurityComponentLayoutDirection initValueLayoutDirection;

    // Initial setup
    initValueLayoutDirection = std::get<1>(layoutDirectionLayoutDirectionValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: layoutDirectionLayoutDirectionInvalidValues) {
        inputValueLayoutDirection = initValueLayoutDirection;
        modifier_->setLayoutDirection(node_, inputValueLayoutDirection);
        inputValueLayoutDirection = std::get<1>(value);
        modifier_->setLayoutDirection(node_, inputValueLayoutDirection);
        jsonValue = GetJsonValue(node_);
        result = jsonValue->GetInt(ATTRIBUTE_LAYOUT_DIRECTION_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE);
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
}

// Valid values for attribute 'fontSize' of method 'fontSize'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> fontSizeFontSizeValidValues = {
    { "12", ArkValue<Ark_Length>(12), "12.00px" },
    { "22.25fp", ArkValue<Ark_Length>(22.25f), "22.25vp" },
    { "ResId:FLOAT_RES_1_ID", { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_1_ID }, "19.50fp" }
};

/*
 * @tc.name: setFontSizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontSizeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueFontSize;
    Ark_Length initValueFontSize;

    // Initial setup
    initValueFontSize = std::get<1>(fontSizeFontSizeValidValues[0]);

    // Verifying attribute's  values
    inputValueFontSize = initValueFontSize;
    for (auto&& value: fontSizeFontSizeValidValues) {
        inputValueFontSize = std::get<1>(value);
        modifier_->setFontSize(node_, &inputValueFontSize);
        OnModifyDone();

        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'fontSize'
static std::vector<std::tuple<std::string, Ark_Length>> fontSizeInvalidValues = {
    { "-15", ArkValue<Ark_Length>(-15) },
};

/*
 * @tc.name: setFontSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontSizeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueFontSize;
    Ark_Length initValueFontSize;
    std::string initValueStr;

    // Initial setup
    initValueFontSize = std::get<1>(fontSizeFontSizeValidValues[0]);
    initValueStr = std::get<2>(fontSizeFontSizeValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: fontSizeInvalidValues) {
        inputValueFontSize = initValueFontSize;
        modifier_->setFontSize(node_, &inputValueFontSize);
        OnModifyDone();

        inputValueFontSize = std::get<1>(value);
        modifier_->setFontSize(node_, &inputValueFontSize);
        OnModifyDone();

        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        expectedStr = initValueStr; // expect that invalid value should be ignored
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBorderStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBorderStyleTestDefaultValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setBorderStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBorderStyleTestValidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setBorderStyleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBorderStyleTestInvalidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setTextIconSpaceTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setTextIconSpaceTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ICON_SPACE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_ICON_SPACE_DEFAULT_VALUE);
}

// Valid values for attribute 'textIconSpace' of method 'textIconSpace'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> textIconSpaceTextIconSpaceValidValues = {
    { "23", ArkValue<Ark_Length>(23), "23.00px" },
    { "60.25f", ArkValue<Ark_Length>(60.25f), "60.25vp" },
    { "ResId:FLOAT_RES_0_ID", { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID }, "70.50px" }
};

/*
 * @tc.name: setTextIconSpaceTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setTextIconSpaceTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueTextIconSpace;
    Ark_Length initValueTextIconSpace;

    // Initial setup
    initValueTextIconSpace = std::get<1>(textIconSpaceTextIconSpaceValidValues[0]);

    // Verifying attribute's  values
    inputValueTextIconSpace = initValueTextIconSpace;
    for (auto&& value: textIconSpaceTextIconSpaceValidValues) {
        inputValueTextIconSpace = std::get<1>(value);
        modifier_->setTextIconSpace(node_, &inputValueTextIconSpace);
        OnModifyDone();
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ICON_SPACE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'textIconSpace'
static std::vector<std::tuple<std::string, Ark_Length>> textIconSpaceInvalidValues = {
    { "-15", ArkValue<Ark_Length>(-15) },
};

/*
 * @tc.name: setTextIconSpaceTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setTextIconSpaceTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueTextIconSpace;
    Ark_Length initValueTextIconSpace;

    // Initial setup
    initValueTextIconSpace = std::get<1>(textIconSpaceTextIconSpaceValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: textIconSpaceInvalidValues) {
        inputValueTextIconSpace = initValueTextIconSpace;
        modifier_->setTextIconSpace(node_, &inputValueTextIconSpace);
        OnModifyDone();

        inputValueTextIconSpace = std::get<1>(value);
        modifier_->setTextIconSpace(node_, &inputValueTextIconSpace);
        OnModifyDone();

        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_ICON_SPACE_NAME);
        expectedStr = ATTRIBUTE_TEXT_ICON_SPACE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

} // namespace OHOS::Ace::NG