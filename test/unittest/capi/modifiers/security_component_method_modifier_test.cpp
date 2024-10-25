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

#include "generated/test_fixtures.h"
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
    const auto ATTRIBUTE_POSITION_NAME = "position";
    const auto ATTRIBUTE_MARK_ANCHOR_NAME = "markAnchor";
    const auto ATTRIBUTE_SIZE_NAME = "size";
    const auto ATTRIBUTE_CONSTRAINT_SIZE_NAME = "constraintSize";
    const auto ATTRIBUTE_ICON_SIZE_NAME = "iconSize";
    const auto ATTRIBUTE_ICON_SIZE_DEFAULT_VALUE = "16.00vp";
    const auto ATTRIBUTE_LAYOUT_DIRECTION_NAME = "layoutDirection";
    const auto ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE = SecurityComponentLayoutDirection::HORIZONTAL;
    const auto ATTRIBUTE_POSITION_X_NAME = "x";
    const auto ATTRIBUTE_POSITION_X_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_POSITION_Y_NAME = "y";
    const auto ATTRIBUTE_POSITION_Y_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
    const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "16.00fp";
    const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
    const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FFFFFFA0";
    const auto ATTRIBUTE_ICON_COLOR_NAME = "iconColor";
    const auto ATTRIBUTE_ICON_COLOR_DEFAULT_VALUE = "#FFFFFFA1";
    const auto ATTRIBUTE_TEXT_ICON_SPACE_NAME = "textIconSpace";
    const auto ATTRIBUTE_TEXT_ICON_SPACE_DEFAULT_VALUE = "4vp";
    const auto ATTRIBUTE_WIDTH_NAME = "width";
    const auto ATTRIBUTE_WIDTH_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_HEIGHT_NAME = "height";
    const auto ATTRIBUTE_HEIGHT_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_CONSTRAINT_SIZE_MIN_WIDTH_NAME = "minWidth";
    const auto ATTRIBUTE_CONSTRAINT_SIZE_MIN_WIDTH_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_CONSTRAINT_SIZE_MAX_WIDTH_NAME = "maxWidth";
    const auto ATTRIBUTE_CONSTRAINT_SIZE_MAX_WIDTH_DEFAULT_VALUE = "Infinityvp";
    const auto ATTRIBUTE_CONSTRAINT_SIZE_MIN_HEIGHT_NAME = "minHeight";
    const auto ATTRIBUTE_CONSTRAINT_SIZE_MIN_HEIGHT_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_CONSTRAINT_SIZE_MAX_HEIGHT_NAME = "maxHeight";
    const auto ATTRIBUTE_CONSTRAINT_SIZE_MAX_HEIGHT_DEFAULT_VALUE = "Infinityvp";

    const auto ATTRIBUTE_MARK_ANCHOR_X_NAME = "x";
    const auto ATTRIBUTE_MARK_ANCHOR_X_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_MARK_ANCHOR_Y_NAME = "y";
    const auto ATTRIBUTE_MARK_ANCHOR_Y_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_SIZE_HEIGHT_NAME = "height";
    const auto ATTRIBUTE_SIZE_HEIGHT_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_SIZE_WIDTH_NAME = "width";
    const auto ATTRIBUTE_SIZE_WIDTH_DEFAULT_VALUE = "0.00vp";

    const auto THEME_BACKGROUND_COLOR = Color(0xFFFFFFA2);
    const auto THEME_FONT_COLOR = Color(0xFFFFFFA0);
    const auto THEME_FONT_SIZE = Dimension(16., DimensionUnit::FP);
    const auto THEME_ICON_COLOR = Color(0xFFFFFFA1);
    const auto THEME_ICON_SIZE = Dimension(16., DimensionUnit::VP);
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

    // Invalid values for attribute 'x' of position
    std::vector<std::tuple<std::string, Opt_Length>> positionXInvalidValues = {
        {"Ark_Empty()", Converter::ArkValue<Opt_Length>(Ark_Empty())},
    };

    // Invalid values for attribute 'y' of position
    std::vector<std::tuple<std::string, Opt_Length>> positionYInvalidValues = {
        {"Ark_Empty()", Converter::ArkValue<Opt_Length>(Ark_Empty())},
    };

    // Valid values for attribute 'x' of position
    std::vector<std::tuple<std::string, Opt_Length, std::string>> positionXValidValues = {
        { "23", ArkValue<Opt_Length>(23), "23.00px" },
        { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
        { "-40.5f", ArkValue<Opt_Length>(-40.5f), "-40.50vp" },
        {
            "ResId:FLOAT_RES_0_ID",
            { .tag = ARK_TAG_RESOURCE, .value = { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID }},
            "70.50px"
        }
    };

    // Valid values for attribute 'y' of position
    std::vector<std::tuple<std::string, Opt_Length, std::string>> positionYValidValues = {
        { "23", ArkValue<Opt_Length>(23), "23.00px" },
        { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
        { "-40.5f", ArkValue<Opt_Length>(-40.5f), "-40.50vp" },
        {
            "ResId:FLOAT_RES_0_ID",
            { .tag = ARK_TAG_RESOURCE, .value = { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID }},
            "70.50px"
        }
    };
} // namespace

class SecurityComponentMethodModifierTest : public ModifierTestBase<GENERATED_ArkUISecurityComponentMethodModifier,
    &GENERATED_ArkUINodeModifiers::getSecurityComponentMethodModifier, GENERATED_ARKUI_SAVE_BUTTON> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(
            static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = SetupThemeStyle(THEME_PATTERN_SECURITY_COMPONENT);
        themeStyle->SetAttr("background_color", { .value = THEME_BACKGROUND_COLOR });
        themeStyle->SetAttr("icon_color", { .value = THEME_ICON_COLOR });
        themeStyle->SetAttr("icon_size", { .value = THEME_ICON_SIZE });
        themeStyle->SetAttr("font_color", { .value = THEME_FONT_COLOR });
        themeStyle->SetAttr("font_size", { .value = THEME_FONT_SIZE });
        themeStyle->SetAttr("text_icon_pading", { .value = THEME_TEXT_ICON_SPACE });

        SetupTheme<SecurityComponentTheme>();

        AddResource(FLOAT_RES_0_ID, FLOAT_RES_0_STORED_VALUE);
        AddResource(FLOAT_RES_1_ID, FLOAT_RES_1_STORED_VALUE);

        for (const auto &[resId, resName, value] : Fixtures::resourceInitTable) {
            AddResource(resId, value);
            AddResource(resName, value);
        }
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
 * @tc.name: setPositionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setPositionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultPosition =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POSITION_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultPosition, ATTRIBUTE_POSITION_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POSITION_X_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultPosition, ATTRIBUTE_POSITION_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POSITION_Y_DEFAULT_VALUE);
}

/*
 * @tc.name: setPositionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setPositionTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultPosition;
    std::string resultStr;
    std::string expectedStr;
    Ark_Position inputValuePosition;
    Ark_Position initValuePosition;

    // Initial setup
    initValuePosition.x = std::get<1>(positionXValidValues[0]);
    initValuePosition.y = std::get<1>(positionYValidValues[0]);

    // Verifying attribute's 'x'  values
    inputValuePosition = initValuePosition;
    for (auto&& value: positionXValidValues) {
        inputValuePosition.x = std::get<1>(value);
        modifier_->setPosition(node_, &inputValuePosition);
        OnModifyDone();
        jsonValue = GetJsonValue(node_);
        resultPosition = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POSITION_NAME);
        resultStr = GetAttrValue<std::string>(resultPosition, ATTRIBUTE_POSITION_X_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'y'  values
    inputValuePosition = initValuePosition;
    for (auto&& value: positionYValidValues) {
        inputValuePosition.y = std::get<1>(value);
        modifier_->setPosition(node_, &inputValuePosition);
        OnModifyDone();
        jsonValue = GetJsonValue(node_);
        resultPosition = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POSITION_NAME);
        resultStr = GetAttrValue<std::string>(resultPosition, ATTRIBUTE_POSITION_Y_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPositionTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setPositionTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultPosition;
    std::string resultStr;
    std::string expectedStr;
    Ark_Position inputValuePosition;
    Ark_Position initValuePosition;

    // Initial setup
    initValuePosition.x = std::get<1>(positionXValidValues[0]);
    initValuePosition.y = std::get<1>(positionYValidValues[0]);

    // Verifying attribute's 'x'  values
    for (auto&& value: positionXInvalidValues) {
        inputValuePosition = initValuePosition;
        modifier_->setPosition(node_, &inputValuePosition);
        OnModifyDone();
        inputValuePosition.x = std::get<1>(value);
        modifier_->setPosition(node_, &inputValuePosition);
        OnModifyDone();
        jsonValue = GetJsonValue(node_);
        resultPosition = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POSITION_NAME);
        resultStr = GetAttrValue<std::string>(resultPosition, ATTRIBUTE_POSITION_X_NAME);
        expectedStr = ATTRIBUTE_POSITION_X_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'y'  values
    for (auto&& value: positionYInvalidValues) {
        inputValuePosition = initValuePosition;
        modifier_->setPosition(node_, &inputValuePosition);
        OnModifyDone();
        inputValuePosition.y = std::get<1>(value);
        modifier_->setPosition(node_, &inputValuePosition);
        OnModifyDone();
        jsonValue = GetJsonValue(node_);
        resultPosition = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POSITION_NAME);
        resultStr = GetAttrValue<std::string>(resultPosition, ATTRIBUTE_POSITION_Y_NAME);
        expectedStr = ATTRIBUTE_POSITION_Y_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setMarkAnchorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setMarkAnchorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultMarkAnchor =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARK_ANCHOR_X_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARK_ANCHOR_Y_DEFAULT_VALUE);
}

/*
 * @tc.name: setMarkAnchorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMarkAnchorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultMarkAnchor;
    std::string resultStr;
    std::string expectedStr;
    Ark_Position inputValueMarkAnchor;
    Ark_Position initValueMarkAnchor;

    // Initial setup
    initValueMarkAnchor.x = std::get<1>(positionXValidValues[0]);
    initValueMarkAnchor.y = std::get<1>(positionYValidValues[0]);

    // Verifying attribute's 'x'  values
    inputValueMarkAnchor = initValueMarkAnchor;
    for (auto&& value: positionXValidValues) {
        inputValueMarkAnchor.x = std::get<1>(value);
        modifier_->setMarkAnchor(node_, &inputValueMarkAnchor);
        jsonValue = GetJsonValue(node_);
        resultMarkAnchor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
        resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_X_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'y'  values
    inputValueMarkAnchor = initValueMarkAnchor;
    for (auto&& value: positionYValidValues) {
        inputValueMarkAnchor.y = std::get<1>(value);
        modifier_->setMarkAnchor(node_, &inputValueMarkAnchor);
        jsonValue = GetJsonValue(node_);
        resultMarkAnchor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
        resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_Y_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setMarkAnchorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMarkAnchorTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultMarkAnchor;
    std::string resultStr;
    std::string expectedStr;
    Ark_Position inputValueMarkAnchor;
    Ark_Position initValueMarkAnchor;

    // Initial setup
    initValueMarkAnchor.x = std::get<1>(positionXValidValues[0]);
    initValueMarkAnchor.y = std::get<1>(positionYValidValues[0]);

    // Verifying attribute's 'x'  values
    for (auto&& value: positionXInvalidValues) {
        inputValueMarkAnchor = initValueMarkAnchor;
        modifier_->setMarkAnchor(node_, &inputValueMarkAnchor);
        inputValueMarkAnchor.x = std::get<1>(value);
        modifier_->setMarkAnchor(node_, &inputValueMarkAnchor);
        jsonValue = GetJsonValue(node_);
        resultMarkAnchor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
        resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_X_NAME);
        expectedStr = ATTRIBUTE_MARK_ANCHOR_X_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'y'  values
    for (auto&& value: positionYInvalidValues) {
        inputValueMarkAnchor = initValueMarkAnchor;
        modifier_->setMarkAnchor(node_, &inputValueMarkAnchor);
        inputValueMarkAnchor.y = std::get<1>(value);
        modifier_->setMarkAnchor(node_, &inputValueMarkAnchor);
        jsonValue = GetJsonValue(node_);
        resultMarkAnchor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
        resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_Y_NAME);
        expectedStr = ATTRIBUTE_MARK_ANCHOR_Y_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
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
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setFontColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontColorTestValidValues, TestSize.Level1)
{
    Ark_ResourceColor inputValueFontColor;

    auto checkValue = [this, &inputValueFontColor](const std::string& input, const Ark_ResourceColor& value,
        const std::string& expectedStr)
    {
        inputValueFontColor = value;
        modifier_->setFontColor(node_, &inputValueFontColor);
        OnModifyDone();
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << input;
    };

    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_String>(value), expectedStr);
    }
    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(value), expectedStr);
    }
    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(value), expectedStr);
    }
    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(value), expectedStr);
    }
}

/*
 * @tc.name: setFontColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontColorTestInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueFontColor;
    std::string expectedStr;

    // Initial setup
    initValueFontColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    expectedStr = std::get<2>(Fixtures::testFixtureColorsStrValidValues[0]); // invalid value should be ignored

    auto checkValue = [this, &initValueFontColor, &expectedStr](const std::string& input,
        const Ark_ResourceColor& value)
    {
        Ark_ResourceColor inputValueFontColor = initValueFontColor;
        modifier_->setFontColor(node_, &inputValueFontColor);
        OnModifyDone();
        inputValueFontColor = value;
        modifier_->setFontColor(node_, &inputValueFontColor);
        OnModifyDone();
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << input;
    };

    for (const auto &[input, value]: Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (const auto &[input, value]: Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }

    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setIconColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setIconColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ICON_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ICON_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setIconColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setIconColorTestValidValues, TestSize.Level1)
{
    Ark_ResourceColor inputValueIconColor;

    auto checkValue = [this, &inputValueIconColor](const std::string& input, const Ark_ResourceColor& value,
        const std::string& expectedStr)
    {
        inputValueIconColor = value;
        modifier_->setIconColor(node_, &inputValueIconColor);
        OnModifyDone();
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ICON_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << input;
    };

    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_String>(value), expectedStr);
    }
    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(value), expectedStr);
    }
    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(value), expectedStr);
    }
    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(value), expectedStr);
    }
}

/*
 * @tc.name: setIconColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setIconColorTestInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueIconColor;
    std::string expectedStr;

    // Initial setup
    initValueIconColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    expectedStr = std::get<2>(Fixtures::testFixtureColorsStrValidValues[0]); // invalid value should be ignored

    auto checkValue = [this, &initValueIconColor, &expectedStr](const std::string& input,
        const Ark_ResourceColor& value)
    {
        Ark_ResourceColor inputValueIconColor = initValueIconColor;
        modifier_->setIconColor(node_, &inputValueIconColor);
        OnModifyDone();
        inputValueIconColor = value;
        modifier_->setIconColor(node_, &inputValueIconColor);
        OnModifyDone();
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ICON_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << input;
    };

    for (const auto &[input, value]: Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (const auto &[input, value]: Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }

    // Check invalid union
    checkValue("invalid union", Converter::ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setBackgroundColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBackgroundColorTestDefaultValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setBackgroundColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBackgroundColorTestValidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setBackgroundColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBackgroundColorTestInvalidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
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
 * @tc.name: setBorderColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBorderColorTestDefaultValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setBorderColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBorderColorTestValidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setBorderColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBorderColorTestInvalidValues, TestSize.Level1)
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

/*
 * @tc.name: setWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
}

// Valid values for attribute 'width' of method 'width'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> widthWidthValidValues = {
    { "23", ArkValue<Ark_Length>(23), "23.00px" },
    { "60.25f", ArkValue<Ark_Length>(60.25f), "60.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID },
        "70.50px"
    }
};

/*
 * @tc.name: setWidthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setWidthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueWidth;
    Ark_Length initValueWidth;

    // Initial setup
    initValueWidth = std::get<1>(widthWidthValidValues[0]);

    // Verifying attribute's  values
    inputValueWidth = initValueWidth;
    for (auto&& value: widthWidthValidValues) {
        inputValueWidth = std::get<1>(value);
        modifier_->setWidth(node_, &inputValueWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, Ark_Length>> widthWidthInvalidValues = {
    {"-10", Converter::ArkValue<Ark_Length>(-10)},
};

/*
 * @tc.name: setWidthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setWidthTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueWidth;
    Ark_Length initValueWidth;

    // Initial setup
    initValueWidth = std::get<1>(widthWidthValidValues[0]);

    inputValueWidth = initValueWidth;
    for (auto&& value: widthWidthInvalidValues) {
        inputValueWidth = initValueWidth;
        modifier_->setWidth(node_, &inputValueWidth);
        inputValueWidth = std::get<1>(value);
        modifier_->setWidth(node_, &inputValueWidth);
        jsonValue = GetJsonValue(node_);
        expectedStr = ATTRIBUTE_WIDTH_DEFAULT_VALUE;
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setHeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setHeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
}

// Valid values for attribute 'height' of method 'height'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> heightHeightValidValues = {
    { "23", ArkValue<Ark_Length>(23), "23.00px" },
    { "60.25f", ArkValue<Ark_Length>(60.25f), "60.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID },
        "70.50px"
    }
};

/*
 * @tc.name: setHeightTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setHeightTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueHeight;
    Ark_Length initValueHeight;

    // Initial setup
    initValueHeight = std::get<1>(heightHeightValidValues[0]);

    // Verifying attribute's  values
    inputValueHeight = initValueHeight;
    for (auto&& value: heightHeightValidValues) {
        inputValueHeight = std::get<1>(value);
        modifier_->setHeight(node_, &inputValueHeight);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, Ark_Length>> heightHeightInvalidValues = {
    {"-10", Converter::ArkValue<Ark_Length>(-10)},
};

/*
 * @tc.name: setHeightTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setHeightTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueHeight;
    Ark_Length initValueHeight;

    // Initial setup
    initValueHeight = std::get<1>(heightHeightValidValues[0]);

    inputValueHeight = initValueHeight;
    for (auto&& value: heightHeightInvalidValues) {
        inputValueHeight = initValueHeight;
        modifier_->setHeight(node_, &inputValueHeight);
        inputValueHeight = std::get<1>(value);
        modifier_->setHeight(node_, &inputValueHeight);
        jsonValue = GetJsonValue(node_);
        expectedStr = ATTRIBUTE_HEIGHT_DEFAULT_VALUE;
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}/*
 * @tc.name: setSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SIZE_WIDTH_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SIZE_HEIGHT_DEFAULT_VALUE);
}

// Valid values for attribute 'width' of method 'size'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> sizeWidthValidValues = {
    { "23", ArkValue<Opt_Length>(23), "23.00px" },
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        { .tag = ARK_TAG_RESOURCE, .value = { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID }},
        "70.50px"
    }
};

// Valid values for attribute 'height' of method 'size'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> sizeHeightValidValues = {
    { "23", ArkValue<Opt_Length>(23), "23.00px" },
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        { .tag = ARK_TAG_RESOURCE, .value = { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID }},
        "70.50px"
    }
};

/*
 * @tc.name: setSizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setSizeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultSize;
    std::string resultStr;
    std::string expectedStr;
    Ark_SizeOptions inputValueSize;
    Ark_SizeOptions initValueSize;

    // Initial setup
    initValueSize.width = std::get<1>(sizeWidthValidValues[0]);
    initValueSize.height = std::get<1>(sizeHeightValidValues[0]);

    // Verifying attribute's 'width'  values
    inputValueSize = initValueSize;
    for (auto&& value: sizeWidthValidValues) {
        inputValueSize.width = std::get<1>(value);
        modifier_->setSize(node_, &inputValueSize);
        jsonValue = GetJsonValue(node_);
        resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'height'  values
    inputValueSize = initValueSize;
    for (auto&& value: sizeHeightValidValues) {
        inputValueSize.height = std::get<1>(value);
        modifier_->setSize(node_, &inputValueSize);
        jsonValue = GetJsonValue(node_);
        resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_HEIGHT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'width' of method 'size'
static std::vector<std::tuple<std::string, Opt_Length>> sizeWidthInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Length>(Ark_Empty())},
};

// Invalid values for attribute 'height' of method 'size'
static std::vector<std::tuple<std::string, Opt_Length>> sizeHeightInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Length>(Ark_Empty())},
};

/*
 * @tc.name: setSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setSizeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultSize;
    std::string resultStr;
    std::string expectedStrWidth;
    std::string expectedStrHeight;
    Ark_SizeOptions inputValueSize;
    Ark_SizeOptions initValueSize;

    // Initial setup
    initValueSize.width = std::get<1>(sizeWidthValidValues[0]);
    initValueSize.height = std::get<1>(sizeHeightValidValues[0]);
    expectedStrWidth = std::get<2>(sizeWidthValidValues[0]);
    expectedStrHeight = std::get<2>(sizeHeightValidValues[0]);

    // Verifying attribute's 'width'  values
    for (auto&& value: sizeWidthInvalidValues) {
        inputValueSize = initValueSize;
        modifier_->setSize(node_, &inputValueSize);
        inputValueSize.width = std::get<1>(value);
        modifier_->setSize(node_, &inputValueSize);
        jsonValue = GetJsonValue(node_);
        resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStrWidth) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'height'  values
    for (auto&& value: sizeHeightInvalidValues) {
        inputValueSize = initValueSize;
        modifier_->setSize(node_, &inputValueSize);
        inputValueSize.height = std::get<1>(value);
        modifier_->setSize(node_, &inputValueSize);
        jsonValue = GetJsonValue(node_);
        resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStrHeight) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'width' of method 'size'
static std::vector<std::tuple<std::string, Opt_Length>> sizeWidthInvalidValuesReset = {
    {"-10", Converter::ArkValue<Opt_Length>(-10)},
};

// Invalid values for attribute 'height' of method 'size'
static std::vector<std::tuple<std::string, Opt_Length>> sizeHeightInvalidValuesReset = {
    {"-10", Converter::ArkValue<Opt_Length>(-10)},
};

/*
 * @tc.name: setSizeTestInvalidValuesReset
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setSizeTestInvalidValuesReset, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultSize;
    std::string resultStr;
    std::string expectedStrWidth;
    std::string expectedStrHeight;
    Ark_SizeOptions inputValueSize;
    Ark_SizeOptions initValueSize;

    // Initial setup
    initValueSize.width = std::get<1>(sizeWidthValidValues[0]);
    initValueSize.height = std::get<1>(sizeHeightValidValues[0]);
    expectedStrWidth = ATTRIBUTE_SIZE_WIDTH_DEFAULT_VALUE;
    expectedStrHeight = ATTRIBUTE_SIZE_HEIGHT_DEFAULT_VALUE;

    // Verifying attribute's 'width'  values
    for (auto&& value: sizeWidthInvalidValuesReset) {
        inputValueSize = initValueSize;
        modifier_->setSize(node_, &inputValueSize);
        inputValueSize.width = std::get<1>(value);
        modifier_->setSize(node_, &inputValueSize);
        jsonValue = GetJsonValue(node_);
        resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStrWidth) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'height'  values
    for (auto&& value: sizeHeightInvalidValuesReset) {
        inputValueSize = initValueSize;
        modifier_->setSize(node_, &inputValueSize);
        inputValueSize.height = std::get<1>(value);
        modifier_->setSize(node_, &inputValueSize);
        jsonValue = GetJsonValue(node_);
        resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStrHeight) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setConstraintSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setConstraintSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultConstraintSize =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MIN_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONSTRAINT_SIZE_MIN_WIDTH_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MAX_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONSTRAINT_SIZE_MAX_WIDTH_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MIN_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONSTRAINT_SIZE_MIN_HEIGHT_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MAX_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONSTRAINT_SIZE_MAX_HEIGHT_DEFAULT_VALUE);
}

// Valid values for attribute 'minWidth' of method 'constraintSize'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> constraintSizeMinWidthValidValues = {
    { "23", ArkValue<Opt_Length>(23), "23.00px" },
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    { "0.f", ArkValue<Opt_Length>(0.f), "0.00vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        { .tag = ARK_TAG_RESOURCE, .value = { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID }},
        "70.50px"
    }
};

// Valid values for attribute 'maxWidth' of method 'constraintSize'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> constraintSizeMaxWidthValidValues = {
    { "230", ArkValue<Opt_Length>(230), "230.00px" },
    { "600.25f", ArkValue<Opt_Length>(600.25f), "600.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        { .tag = ARK_TAG_RESOURCE, .value = { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID }},
        "70.50px"
    }
};

// Valid values for attribute 'minHeight' of method 'constraintSize'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> constraintSizeMinHeightValidValues = {
    { "23", ArkValue<Opt_Length>(23), "23.00px" },
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    { "0.f", ArkValue<Opt_Length>(0.f), "0.00vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        { .tag = ARK_TAG_RESOURCE, .value = { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID }},
        "70.50px"
    }
};

// Valid values for attribute 'maxHeight' of method 'constraintSize'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> constraintSizeMaxHeightValidValues = {
    { "230", ArkValue<Opt_Length>(230), "230.00px" },
    { "600.25f", ArkValue<Opt_Length>(600.25f), "600.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        { .tag = ARK_TAG_RESOURCE, .value = { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID }},
        "70.50px"
    }
};

/*
 * @tc.name: setConstraintSizeTestValidWidthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setConstraintSizeTestValidWidthValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultConstraintSize;
    std::string resultStr;
    std::string expectedStr;
    Ark_ConstraintSizeOptions inputValueConstraintSize;
    Ark_ConstraintSizeOptions initValueConstraintSize;

    // Initial setup
    initValueConstraintSize.minWidth = std::get<1>(constraintSizeMinWidthValidValues[0]);
    initValueConstraintSize.maxWidth = std::get<1>(constraintSizeMaxWidthValidValues[0]);
    initValueConstraintSize.minHeight = std::get<1>(constraintSizeMinHeightValidValues[0]);
    initValueConstraintSize.maxHeight = std::get<1>(constraintSizeMaxHeightValidValues[0]);

    // Verifying attribute's 'minWidth'  values
    inputValueConstraintSize = initValueConstraintSize;
    for (auto&& value: constraintSizeMinWidthValidValues) {
        inputValueConstraintSize.minWidth = std::get<1>(value);
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        jsonValue = GetJsonValue(node_);
        resultConstraintSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MIN_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'maxWidth'  values
    inputValueConstraintSize = initValueConstraintSize;
    for (auto&& value: constraintSizeMaxWidthValidValues) {
        inputValueConstraintSize.maxWidth = std::get<1>(value);
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        jsonValue = GetJsonValue(node_);
        resultConstraintSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MAX_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setConstraintSizeTestValidHeightValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setConstraintSizeTestValidHeightValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultConstraintSize;
    std::string resultStr;
    std::string expectedStr;
    Ark_ConstraintSizeOptions inputValueConstraintSize;
    Ark_ConstraintSizeOptions initValueConstraintSize;

    // Initial setup
    initValueConstraintSize.minWidth = std::get<1>(constraintSizeMinWidthValidValues[0]);
    initValueConstraintSize.maxWidth = std::get<1>(constraintSizeMaxWidthValidValues[0]);
    initValueConstraintSize.minHeight = std::get<1>(constraintSizeMinHeightValidValues[0]);
    initValueConstraintSize.maxHeight = std::get<1>(constraintSizeMaxHeightValidValues[0]);

    // Verifying attribute's 'minHeight'  values
    inputValueConstraintSize = initValueConstraintSize;
    for (auto&& value: constraintSizeMinHeightValidValues) {
        inputValueConstraintSize.minHeight = std::get<1>(value);
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        jsonValue = GetJsonValue(node_);
        resultConstraintSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MIN_HEIGHT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'maxHeight'  values
    inputValueConstraintSize = initValueConstraintSize;
    for (auto&& value: constraintSizeMaxHeightValidValues) {
        inputValueConstraintSize.maxHeight = std::get<1>(value);
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        jsonValue = GetJsonValue(node_);
        resultConstraintSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MAX_HEIGHT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'minWidth' of method 'constraintSize'
static std::vector<std::tuple<std::string, Opt_Length>> constraintSizeMinWidthInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Length>(Ark_Empty())},
};

// Invalid values for attribute 'maxWidth' of method 'constraintSize'
static std::vector<std::tuple<std::string, Opt_Length>> constraintSizeMaxWidthInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Length>(Ark_Empty())},
};

// Invalid values for attribute 'minHeight' of method 'constraintSize'
static std::vector<std::tuple<std::string, Opt_Length>> constraintSizeMinHeightInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Length>(Ark_Empty())},
};

// Invalid values for attribute 'maxHeight' of method 'constraintSize'
static std::vector<std::tuple<std::string, Opt_Length>> constraintSizeMaxHeightInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Length>(Ark_Empty())},
};

/*
 * @tc.name: setConstraintSizeTestInvalidWidthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setConstraintSizeTestInvalidWidthValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultConstraintSize;
    std::string resultStr;
    std::string expectedStrMinWidth;
    std::string expectedStrMaxWidth;
    std::string expectedStrMinHeight;
    std::string expectedStrMaxHeight;
    Ark_ConstraintSizeOptions inputValueConstraintSize;
    Ark_ConstraintSizeOptions initValueConstraintSize;

    // Initial setup
    initValueConstraintSize.minWidth = std::get<1>(constraintSizeMinWidthValidValues[0]);
    initValueConstraintSize.maxWidth = std::get<1>(constraintSizeMaxWidthValidValues[0]);
    initValueConstraintSize.minHeight = std::get<1>(constraintSizeMinHeightValidValues[0]);
    initValueConstraintSize.maxHeight = std::get<1>(constraintSizeMaxHeightValidValues[0]);
    expectedStrMinWidth = std::get<2>(constraintSizeMinWidthValidValues[0]);
    expectedStrMaxWidth = std::get<2>(constraintSizeMaxWidthValidValues[0]);

    // Verifying attribute's 'minWidth'  values
    for (auto&& value: constraintSizeMinWidthInvalidValues) {
        inputValueConstraintSize = initValueConstraintSize;
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        inputValueConstraintSize.minWidth = std::get<1>(value);
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        jsonValue = GetJsonValue(node_);
        resultConstraintSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MIN_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStrMinWidth) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'maxWidth'  values
    for (auto&& value: constraintSizeMaxWidthInvalidValues) {
        inputValueConstraintSize = initValueConstraintSize;
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        inputValueConstraintSize.maxWidth = std::get<1>(value);
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        jsonValue = GetJsonValue(node_);
        resultConstraintSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MAX_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStrMaxWidth) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setConstraintSizeTestInvalidHeightValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setConstraintSizeTestInvalidHeightValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultConstraintSize;
    std::string resultStr;
    std::string expectedStrMinWidth;
    std::string expectedStrMaxWidth;
    std::string expectedStrMinHeight;
    std::string expectedStrMaxHeight;
    Ark_ConstraintSizeOptions inputValueConstraintSize;
    Ark_ConstraintSizeOptions initValueConstraintSize;

    // Initial setup
    initValueConstraintSize.minWidth = std::get<1>(constraintSizeMinWidthValidValues[0]);
    initValueConstraintSize.maxWidth = std::get<1>(constraintSizeMaxWidthValidValues[0]);
    initValueConstraintSize.minHeight = std::get<1>(constraintSizeMinHeightValidValues[0]);
    initValueConstraintSize.maxHeight = std::get<1>(constraintSizeMaxHeightValidValues[0]);
    expectedStrMinHeight = std::get<2>(constraintSizeMinHeightValidValues[0]);
    expectedStrMaxHeight = std::get<2>(constraintSizeMaxHeightValidValues[0]);

    // Verifying attribute's 'minHeight'  values
    for (auto&& value: constraintSizeMinHeightInvalidValues) {
        inputValueConstraintSize = initValueConstraintSize;
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        inputValueConstraintSize.minHeight = std::get<1>(value);
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        jsonValue = GetJsonValue(node_);
        resultConstraintSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MIN_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStrMinHeight) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'maxHeight'  values
    for (auto&& value: constraintSizeMaxHeightInvalidValues) {
        inputValueConstraintSize = initValueConstraintSize;
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        inputValueConstraintSize.maxHeight = std::get<1>(value);
        modifier_->setConstraintSize(node_, &inputValueConstraintSize);
        jsonValue = GetJsonValue(node_);
        resultConstraintSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MAX_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStrMaxHeight) << "Passed value is: " << std::get<0>(value);
    }
}

} // namespace OHOS::Ace::NG