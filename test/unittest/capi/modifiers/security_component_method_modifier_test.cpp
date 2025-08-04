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

#include "security_component_method_modifier_test.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace TestConst::SecurityComponentMethod;

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
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    { "-40.5f", ArkValue<Opt_Length>(-40.5f), "-40.50vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Opt_Length>(FLOAT_RES_0_ID),
        "70.50px"
    }
};

// Valid values for attribute 'y' of position
std::vector<std::tuple<std::string, Opt_Length, std::string>> positionYValidValues = {
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    { "-40.5f", ArkValue<Opt_Length>(-40.5f), "-40.50vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Opt_Length>(FLOAT_RES_0_ID),
        "70.50px"
    }
};

// Valid values for attribute 'width'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> widthValidValues = {
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Opt_Length>(FLOAT_RES_0_ID),
        "70.50px"
    }
};

static std::vector<std::tuple<std::string, Opt_Length>> widthInvalidValues = {
    {"-10", Converter::ArkValue<Opt_Length>(-10.f)},
};

static std::vector<std::tuple<std::string, Opt_Dimension, std::string>> widthValidValuesDim = {
    { "60.25f", ArkValue<Opt_Dimension>(60.25f), "60.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Opt_Dimension>(FLOAT_RES_0_ID),
        "70.50px"
    }
};

static std::vector<std::tuple<std::string, Opt_Union_Dimension_BorderRadiuses,
    std::string>> borderRadiusValidValues = {
    { "60.25f", ArkUnion<Opt_Union_Dimension_BorderRadiuses, Ark_Dimension>(60.25f), "60.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkUnion<Opt_Union_Dimension_BorderRadiuses, Ark_Dimension>(FLOAT_RES_0_ID),
        "70.50px"
    }
};

static std::vector<std::tuple<std::string, Opt_Dimension>> widthInvalidValuesDim = {
    {"-10", Converter::ArkValue<Opt_Dimension>(-10.f)},
};

static std::vector<std::tuple<std::string,
    Opt_Union_Dimension_BorderRadiuses>> borderRadiusInvalidValuesDim = {
    {"-10", Converter::ArkUnion<Opt_Union_Dimension_BorderRadiuses, Ark_Dimension>(-10.f)},
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
static std::vector<std::tuple<std::string, Opt_Dimension, std::string>> iconSizeIconSizeValidValues = {
    { "60.25f", ArkValue<Opt_Dimension>(60.25f), "60.25vp" },
    { "ResId:FLOAT_RES_0_ID", Converter::ArkValue<Opt_Dimension>(FLOAT_RES_0_ID), "70.50px" }
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
    Opt_Dimension inputValueIconSize;
    Opt_Dimension initValueIconSize;

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
static std::vector<std::tuple<std::string, Opt_Dimension>> iconSizeInvalidValues = {
    { "-15", ArkValue<Opt_Dimension>(-15.f) },
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
    Opt_Dimension inputValueIconSize;
    Opt_Dimension initValueIconSize;
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
    Opt_SecurityComponentLayoutDirection,
    SecurityComponentLayoutDirection
>;
static std::vector<ValidValuesStep> layoutDirectionLayoutDirectionValidValues = {
    {
        "ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_HORIZONTAL",
        ArkValue<Opt_SecurityComponentLayoutDirection>(ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_HORIZONTAL),
        SecurityComponentLayoutDirection::HORIZONTAL
    },
    {
        "ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_VERTICAL",
        ArkValue<Opt_SecurityComponentLayoutDirection>(ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_VERTICAL),
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
    Opt_SecurityComponentLayoutDirection inputValueLayoutDirection;
    Opt_SecurityComponentLayoutDirection initValueLayoutDirection;

    // Initial setup
    initValueLayoutDirection = std::get<1>(layoutDirectionLayoutDirectionValidValues[0]);

    // Verifying attribute's  values
    inputValueLayoutDirection = initValueLayoutDirection;
    for (auto&& value: layoutDirectionLayoutDirectionValidValues) {
        inputValueLayoutDirection = std::get<1>(value);
        modifier_->setLayoutDirection(node_, &inputValueLayoutDirection);
        jsonValue = GetJsonValue(node_);
        result = jsonValue->GetInt(ATTRIBUTE_LAYOUT_DIRECTION_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(std::get<2>(value));
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'layoutDirection' of method 'layoutDirection'
using InvalidValuesStep = std::tuple<std::string, Opt_SecurityComponentLayoutDirection>;
static std::vector<InvalidValuesStep> layoutDirectionLayoutDirectionInvalidValues = {
    {
        "static_cast<Ark_SecurityComponentLayoutDirection>(-1)",
        ArkValue<Opt_SecurityComponentLayoutDirection>(static_cast<Ark_SecurityComponentLayoutDirection>(-1))
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
    Opt_SecurityComponentLayoutDirection inputValueLayoutDirection;
    Opt_SecurityComponentLayoutDirection initValueLayoutDirection;

    // Initial setup
    initValueLayoutDirection = std::get<1>(layoutDirectionLayoutDirectionValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: layoutDirectionLayoutDirectionInvalidValues) {
        inputValueLayoutDirection = initValueLayoutDirection;
        modifier_->setLayoutDirection(node_, &inputValueLayoutDirection);
        inputValueLayoutDirection = std::get<1>(value);
        modifier_->setLayoutDirection(node_, &inputValueLayoutDirection);
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
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setPositionTestValidValues, TestSize.Level1)
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
        auto position = ArkValue<Opt_Position>(inputValuePosition);
        modifier_->setPosition(node_, &position);
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
        auto position = ArkValue<Opt_Position>(inputValuePosition);
        modifier_->setPosition(node_, &position);
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
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setPositionTestInvalidValues, TestSize.Level1)
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
        auto position = ArkValue<Opt_Position>(inputValuePosition);
        modifier_->setPosition(node_, &position);
        OnModifyDone();
        inputValuePosition.x = std::get<1>(value);
        position = ArkValue<Opt_Position>(inputValuePosition);
        modifier_->setPosition(node_, &position);
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
        auto position = ArkValue<Opt_Position>(inputValuePosition);
        modifier_->setPosition(node_, &position);
        OnModifyDone();
        inputValuePosition.y = std::get<1>(value);
        position = ArkValue<Opt_Position>(inputValuePosition);
        modifier_->setPosition(node_, &position);
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
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setMarkAnchorTestValidValues, TestSize.Level1)
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
        auto markAnchor = ArkValue<Opt_Position>(inputValueMarkAnchor);
        modifier_->setMarkAnchor(node_, &markAnchor);
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
        auto markAnchor = ArkValue<Opt_Position>(inputValueMarkAnchor);
        modifier_->setMarkAnchor(node_, &markAnchor);
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
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setMarkAnchorTestInvalidValues, TestSize.Level1)
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
        auto markAnchor = ArkValue<Opt_Position>(inputValueMarkAnchor);
        modifier_->setMarkAnchor(node_, &markAnchor);
        inputValueMarkAnchor.x = std::get<1>(value);
        markAnchor = ArkValue<Opt_Position>(inputValueMarkAnchor);
        modifier_->setMarkAnchor(node_, &markAnchor);
        jsonValue = GetJsonValue(node_);
        resultMarkAnchor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
        resultStr = GetAttrValue<std::string>(resultMarkAnchor, ATTRIBUTE_MARK_ANCHOR_X_NAME);
        expectedStr = ATTRIBUTE_MARK_ANCHOR_X_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'y'  values
    for (auto&& value: positionYInvalidValues) {
        inputValueMarkAnchor = initValueMarkAnchor;
        auto markAnchor = ArkValue<Opt_Position>(inputValueMarkAnchor);
        modifier_->setMarkAnchor(node_, &markAnchor);
        inputValueMarkAnchor.y = std::get<1>(value);
        markAnchor = ArkValue<Opt_Position>(inputValueMarkAnchor);
        modifier_->setMarkAnchor(node_, &markAnchor);
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
static std::vector<std::tuple<std::string, Opt_Dimension, std::string>> fontSizeFontSizeValidValues = {
    { "22.25", ArkValue<Opt_Dimension>(22.25f), "22.25vp" },
    { "ResId:FLOAT_RES_1_ID", Converter::ArkValue<Opt_Dimension>(FLOAT_RES_1_ID), "19.50fp" }
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
    Opt_Dimension inputValueFontSize;

    // Verifying attribute's  values
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
static std::vector<std::tuple<std::string, Opt_Dimension>> fontSizeInvalidValues = {
    { "-15", ArkValue<Opt_Dimension>(-15.f) },
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
    Opt_Dimension inputValueFontSize;
    Opt_Dimension initValueFontSize;
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
 * @tc.name: setFontStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    int result;

    result = GetAttrValue<int>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
    EXPECT_EQ(result, static_cast<int>(ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE));
}

// Valid values for attribute 'fontStyle' of method 'fontStyle'
static std::vector<std::tuple<std::string, Ark_FontStyle, Ace::FontStyle>> fontStyleFontStyleValidValues = {
    {"ARK_FONT_STYLE_NORMAL", Converter::ArkValue<Ark_FontStyle>(ARK_FONT_STYLE_NORMAL), Ace::FontStyle::NORMAL},
    {"ARK_FONT_STYLE_ITALIC", Converter::ArkValue<Ark_FontStyle>(ARK_FONT_STYLE_ITALIC), Ace::FontStyle::ITALIC},
    {"ARK_FONT_STYLE_NORMAL", Converter::ArkValue<Ark_FontStyle>(ARK_FONT_STYLE_NORMAL), Ace::FontStyle::NORMAL},
};

/*
 * @tc.name: setFontStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontStyleTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int result;
    int expected;
    Ark_FontStyle inputValueFontStyle;
    Ark_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = std::get<1>(fontStyleFontStyleValidValues[0]);

    // Verifying attribute's  values
    inputValueFontStyle = initValueFontStyle;
    for (auto&& value: fontStyleFontStyleValidValues) {
        inputValueFontStyle = std::get<1>(value);
        auto convValue = ArkValue<Opt_FontStyle>(inputValueFontStyle);
        modifier_->setFontStyle(node_, &convValue);
        OnModifyDone();
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<int>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        expected = static_cast<int>(std::get<2>(value));
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'fontStyle' of method 'fontStyle'
static std::vector<std::tuple<std::string, Ark_FontStyle>> fontStyleFontStyleInvalidValues = {
    {"static_cast<Ark_FontStyle>(-1)", Converter::ArkValue<Ark_FontStyle>(static_cast<Ark_FontStyle>(-1))},
};

/*
 * @tc.name: setFontStyleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontStyleTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int result;
    int expected;
    Ark_FontStyle inputValueFontStyle;
    Ark_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = std::get<1>(fontStyleFontStyleValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: fontStyleFontStyleInvalidValues) {
        inputValueFontStyle = initValueFontStyle;
        auto convValue = ArkValue<Opt_FontStyle>(inputValueFontStyle);
        modifier_->setFontStyle(node_, &convValue);
        OnModifyDone();
        inputValueFontStyle = std::get<1>(value);
        convValue = ArkValue<Opt_FontStyle>(inputValueFontStyle);
        modifier_->setFontStyle(node_, &convValue);
        OnModifyDone();
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<int>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        expected = static_cast<int>(ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE);
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setFontWeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontWeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE);
}

using FontWeightT = Opt_Union_I32_FontWeight_String;
static std::vector<std::tuple<std::string, FontWeightT, std::string>> fontWeightValidValues = {
    { "ARK_FONT_WEIGHT_BOLD", ArkUnion<FontWeightT, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD), "FontWeight.Bold" },
    { "ARK_FONT_WEIGHT_REGULAR", ArkUnion<FontWeightT, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR), "FontWeight.Regular" },
    { "100", ArkUnion<FontWeightT, Ark_Int32>(100), "100" },
    { "700", ArkUnion<FontWeightT, Ark_String>("700"), "700" },
    { "bold", ArkUnion<FontWeightT, Ark_String>("bold"), "FontWeight.Bold" },
};

/*
 * @tc.name: setFontWeightTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontWeightTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    FontWeightT inputValueFontWeight;
    FontWeightT initValueFontWeight;

    // Initial setup
    initValueFontWeight = std::get<1>(fontWeightValidValues[0]);

    // Verifying attribute's  values
    inputValueFontWeight = initValueFontWeight;
    for (auto&& value: fontWeightValidValues) {
        inputValueFontWeight = std::get<1>(value);
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        OnModifyDone();
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, FontWeightT>> fontWeightInvalidValues = {
    { "-111", ArkUnion<FontWeightT, Ark_Int32>(-111) },
    { "InvalidData!", ArkUnion<FontWeightT, Ark_String>("InvalidData!") },
    { "invalid union", ArkUnion<FontWeightT, Ark_Empty>(nullptr) },
};

/*
 * @tc.name: setFontWeightTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontWeightTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    FontWeightT inputValueFontWeight;
    FontWeightT initValueFontWeight;

    // Initial setup
    initValueFontWeight = std::get<1>(fontWeightValidValues[0]);
    expectedStr = std::get<2>(fontWeightValidValues[0]); // invalid value should be ignored

    // Verifying attribute's  values
    for (auto&& value: fontWeightInvalidValues) {
        inputValueFontWeight = initValueFontWeight;
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        OnModifyDone();
        inputValueFontWeight = std::get<1>(value);
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        OnModifyDone();
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
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
        auto convValue = ArkValue<Opt_ResourceColor>(inputValueFontColor);
        modifier_->setFontColor(node_, &convValue);
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
        auto convValue = ArkValue<Opt_ResourceColor>(inputValueFontColor);
        modifier_->setFontColor(node_, &convValue);
        OnModifyDone();
        inputValueFontColor = value;
        convValue = ArkValue<Opt_ResourceColor>(inputValueFontColor);
        modifier_->setFontColor(node_, &convValue);
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
        auto convValue = ArkValue<Opt_ResourceColor>(inputValueIconColor);
        modifier_->setIconColor(node_, &convValue);
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
        auto convValue = ArkValue<Opt_ResourceColor>(inputValueIconColor);
        modifier_->setIconColor(node_, &convValue);
        OnModifyDone();
        inputValueIconColor = value;
        convValue = ArkValue<Opt_ResourceColor>(inputValueIconColor);
        modifier_->setIconColor(node_, &convValue);
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
HWTEST_F(SecurityComponentMethodModifierTest, setBackgroundColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetPatternJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BACKGROUND_COLOR_DEFAULT_VALUE);
}

// Fixture 'ColorsStr' for type 'Ark_String'
// Expect that low values of alpha will be changed to 0xFF
std::vector<std::tuple<std::string, Ark_String, std::string>> backgroundColorStrValidValues = {
    { "\"#123\"", Converter::ArkValue<Ark_String>("#123"), "#FF112233" },
    { "\"#11223344\"", Converter::ArkValue<Ark_String>("#11223344"), "#FF223344" },
    { "\"#123456\"", Converter::ArkValue<Ark_String>("#123456"), "#FF123456" },
    { "\"65535\"", Converter::ArkValue<Ark_String>("65535"), "#FF00FFFF" },
};

// Fixture 'ColorsNum' for type 'Ark_Number'
// Expect that low values of alpha will be changed to 0xFF
std::vector<std::tuple<std::string, Ark_Number, std::string>> backgroundColorNumValidValues = {
    { "0", Converter::ArkValue<Ark_Number>(0), "#FF000000" },
    { "1", Converter::ArkValue<Ark_Number>(1), "#FF000001" },
    { "65535", Converter::ArkValue<Ark_Number>(65535), "#FF00FFFF" },
    { "-1", Converter::ArkValue<Ark_Number>(-1), "#FFFFFFFF" },
    { "0xBE7AC0DE", Converter::ArkValue<Ark_Number>(0xBE7AC0DE), "#BE7AC0DE" },
};

// Fixture 'ColorsEnum' for type 'Ark_Color'
// Expect that low values of alpha will be changed to 0xFF
std::vector<std::tuple<std::string, Ark_Color, std::string>> backgroundColorEnumValidValues = {
    { "ARK_COLOR_WHITE", Converter::ArkValue<Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
    { "ARK_COLOR_BLACK", Converter::ArkValue<Ark_Color>(ARK_COLOR_BLACK), "#FF000000" },
    { "ARK_COLOR_BLUE", Converter::ArkValue<Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { "ARK_COLOR_BROWN", Converter::ArkValue<Ark_Color>(ARK_COLOR_BROWN), "#FFA52A2A" },
    { "ARK_COLOR_GRAY", Converter::ArkValue<Ark_Color>(ARK_COLOR_GRAY), "#FF808080" },
    { "ARK_COLOR_GREEN", Converter::ArkValue<Ark_Color>(ARK_COLOR_GREEN), "#FF008000" },
    { "ARK_COLOR_GREY", Converter::ArkValue<Ark_Color>(ARK_COLOR_GREY), "#FF808080" },
    { "ARK_COLOR_ORANGE", Converter::ArkValue<Ark_Color>(ARK_COLOR_ORANGE), "#FFFFA500" },
    { "ARK_COLOR_PINK", Converter::ArkValue<Ark_Color>(ARK_COLOR_PINK), "#FFFFC0CB" },
    { "ARK_COLOR_RED", Converter::ArkValue<Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
    { "ARK_COLOR_YELLOW", Converter::ArkValue<Ark_Color>(ARK_COLOR_YELLOW), "#FFFFFF00" },
    { "ARK_COLOR_TRANSPARENT", Converter::ArkValue<Ark_Color>(ARK_COLOR_TRANSPARENT), "#FF000000" },
};

/*
 * @tc.name: setBackgroundColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBackgroundColorTestValidValues, TestSize.Level1)
{
    Ark_ResourceColor inputValueBackgroundColor;

    auto checkValue = [this, &inputValueBackgroundColor](const std::string& input, const Ark_ResourceColor& value,
        const std::string& expectedStr)
    {
        inputValueBackgroundColor = value;
        auto convValue = ArkValue<Opt_ResourceColor>(inputValueBackgroundColor);
        modifier_->setBackgroundColor(node_, &convValue);
        OnModifyDone();
        auto jsonValue = GetPatternJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << input;
    };

    for (const auto &[input, value, expectedStr]: backgroundColorStrValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_String>(value), expectedStr);
    }
    for (const auto &[input, value, expectedStr]: backgroundColorNumValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(value), expectedStr);
    }
    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(value), expectedStr);
    }
    for (const auto &[input, value, expectedStr]: backgroundColorEnumValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(value), expectedStr);
    }
}

/*
 * @tc.name: setBackgroundColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBackgroundColorTestInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueBackgroundColor;
    std::string expectedStr;

    // Initial setup
    initValueBackgroundColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    expectedStr = std::get<2>(Fixtures::testFixtureColorsStrValidValues[0]); // invalid value should be ignored

    auto checkValue = [this, &initValueBackgroundColor, &expectedStr](const std::string& input,
        const Ark_ResourceColor& value)
    {
        Ark_ResourceColor inputValueBackgroundColor = initValueBackgroundColor;
        auto convValue = ArkValue<Opt_ResourceColor>(inputValueBackgroundColor);
        modifier_->setBackgroundColor(node_, &convValue);
        OnModifyDone();
        inputValueBackgroundColor = value;
        convValue = ArkValue<Opt_ResourceColor>(inputValueBackgroundColor);
        modifier_->setBackgroundColor(node_, &convValue);
        OnModifyDone();
        auto jsonValue = GetPatternJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACKGROUND_COLOR_NAME);
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
 * @tc.name: setBorderStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetPatternJsonValue(node_);
    int result;

    result = GetAttrValue<int>(jsonValue, ATTRIBUTE_BORDER_STYLE_NAME);
    EXPECT_EQ(result, static_cast<int>(ATTRIBUTE_BORDER_STYLE_DEFAULT_VALUE));
}

// Valid values for attribute 'borderStyle' of method 'borderStyle'
static std::vector<std::tuple<std::string, Ark_BorderStyle, BorderStyle>> borderStyleBorderStyleValidValues = {
    {
        "ARK_BORDER_STYLE_DOTTED",
        ARK_BORDER_STYLE_DOTTED,
        BorderStyle::DOTTED
    },
    {
        "ARK_BORDER_STYLE_DASHED",
        ARK_BORDER_STYLE_DASHED,
        BorderStyle::DASHED
    },
    {
        "ARK_BORDER_STYLE_SOLID",
        ARK_BORDER_STYLE_SOLID,
        BorderStyle::SOLID
    },
};

/*
 * @tc.name: setBorderStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderStyleTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int result;
    int expected;
    Ark_BorderStyle inputValueBorderStyle;
    Ark_BorderStyle initValueBorderStyle;

    // Initial setup
    initValueBorderStyle = std::get<1>(borderStyleBorderStyleValidValues[0]);

    // Verifying attribute's  values
    inputValueBorderStyle = initValueBorderStyle;
    for (auto&& value: borderStyleBorderStyleValidValues) {
        inputValueBorderStyle = std::get<1>(value);
        auto convValue = ArkValue<Opt_BorderStyle>(inputValueBorderStyle);
        modifier_->setBorderStyle(node_, &convValue);
        OnModifyDone();
        jsonValue = GetPatternJsonValue(node_);
        result = GetAttrValue<int>(jsonValue, ATTRIBUTE_BORDER_STYLE_NAME);
        expected = static_cast<int>(std::get<2>(value));
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'borderStyle' of method 'borderStyle'
static std::vector<std::tuple<std::string, Ark_BorderStyle>> borderStyleBorderStyleInvalidValues = {
    {
        "static_cast<Ark_BorderStyle>(-1)",
        Converter::ArkValue<Ark_BorderStyle>(static_cast<Ark_BorderStyle>(-1))
    },
};

/*
 * @tc.name: setBorderStyleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderStyleTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int result;
    int expected;
    Ark_BorderStyle inputValueBorderStyle;
    Ark_BorderStyle initValueBorderStyle;

    // Initial setup
    initValueBorderStyle = std::get<1>(borderStyleBorderStyleValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: borderStyleBorderStyleInvalidValues) {
        inputValueBorderStyle = initValueBorderStyle;
        auto convValue = ArkValue<Opt_BorderStyle>(inputValueBorderStyle);
        modifier_->setBorderStyle(node_, &convValue);
        OnModifyDone();
        inputValueBorderStyle = std::get<1>(value);
        convValue = ArkValue<Opt_BorderStyle>(inputValueBorderStyle);
        modifier_->setBorderStyle(node_, &convValue);
        OnModifyDone();
        jsonValue = GetPatternJsonValue(node_);
        result = GetAttrValue<int>(jsonValue, ATTRIBUTE_BORDER_STYLE_NAME);
        expected = static_cast<int>(ATTRIBUTE_BORDER_STYLE_DEFAULT_VALUE);
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBorderWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetPatternJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BORDER_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BORDER_WIDTH_DEFAULT_VALUE);
}

/*
 * @tc.name: setBorderWidthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderWidthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Dimension inputValueBorderWidth;
    Opt_Dimension initValueBorderWidth;

    // Initial setup
    initValueBorderWidth = std::get<1>(widthValidValuesDim[0]);

    // Verifying attribute's  values
    inputValueBorderWidth = initValueBorderWidth;
    for (auto&& value: widthValidValuesDim) {
        inputValueBorderWidth = std::get<1>(value);
        modifier_->setBorderWidth(node_, &inputValueBorderWidth);
        OnModifyDone();
        jsonValue = GetPatternJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BORDER_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBorderWidthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderWidthTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Dimension inputValueBorderWidth;
    Opt_Dimension initValueBorderWidth;

    // Initial setup
    initValueBorderWidth = std::get<1>(widthValidValuesDim[0]);
    expectedStr = std::get<2>(widthValidValuesDim[0]);

    inputValueBorderWidth = initValueBorderWidth;
    for (auto&& value: widthInvalidValuesDim) {
        inputValueBorderWidth = initValueBorderWidth;
        modifier_->setBorderWidth(node_, &inputValueBorderWidth);
        OnModifyDone();
        inputValueBorderWidth = std::get<1>(value);
        modifier_->setBorderWidth(node_, &inputValueBorderWidth);
        OnModifyDone();
        jsonValue = GetPatternJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BORDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBorderColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetPatternJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BORDER_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BORDER_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setBorderColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderColorTestValidValues, TestSize.Level1)
{
    Ark_ResourceColor inputValueBorderColor;

    auto checkValue = [this, &inputValueBorderColor](const std::string& input, const Ark_ResourceColor& value,
        const std::string& expectedStr)
    {
        inputValueBorderColor = value;
        auto convValue = ArkValue<Opt_ResourceColor>(inputValueBorderColor);
        modifier_->setBorderColor(node_, &convValue);
        OnModifyDone();
        auto jsonValue = GetPatternJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BORDER_COLOR_NAME);
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
 * @tc.name: setBorderColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderColorTestInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueBorderColor;
    std::string expectedStr;

    // Initial setup
    initValueBorderColor =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(Fixtures::testFixtureColorsStrValidValues[0]));
    expectedStr = std::get<2>(Fixtures::testFixtureColorsStrValidValues[0]); // invalid value should be ignored

    auto checkValue = [this, &initValueBorderColor, &expectedStr](const std::string& input,
        const Ark_ResourceColor& value)
    {
        Ark_ResourceColor inputValueBorderColor = initValueBorderColor;
        auto convValue = ArkValue<Opt_ResourceColor>(inputValueBorderColor);
        modifier_->setBorderColor(node_, &convValue);
        OnModifyDone();
        inputValueBorderColor = value;
        convValue = ArkValue<Opt_ResourceColor>(inputValueBorderColor);
        modifier_->setBorderColor(node_, &convValue);
        OnModifyDone();
        auto jsonValue = GetPatternJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BORDER_COLOR_NAME);
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
 * @tc.name: setBorderRadiusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadiusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetPatternJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BORDER_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BORDER_RADIUS_DEFAULT_VALUE);
}

/*
 * @tc.name: setBorderRadiusTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadiusTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Union_Dimension_BorderRadiuses inputValueBorderRadius;
    Opt_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    initValueBorderRadius = std::get<1>(borderRadiusValidValues[0]);

    // Verifying attribute's  values
    inputValueBorderRadius = initValueBorderRadius;
    for (auto&& value: borderRadiusValidValues) {
        inputValueBorderRadius = std::get<1>(value);
        modifier_->setBorderRadius(node_, &inputValueBorderRadius);
        OnModifyDone();
        jsonValue = GetPatternJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BORDER_RADIUS_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setBorderRadiusTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadiusTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Union_Dimension_BorderRadiuses inputValueBorderRadius;
    Opt_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    initValueBorderRadius = std::get<1>(borderRadiusValidValues[0]);
    expectedStr = std::get<2>(borderRadiusValidValues[0]);

    inputValueBorderRadius = initValueBorderRadius;
    for (auto&& value: borderRadiusInvalidValuesDim) {
        inputValueBorderRadius = initValueBorderRadius;
        modifier_->setBorderRadius(node_, &inputValueBorderRadius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_NE(layoutProperty, nullptr);
        std::optional<BorderRadiusProperty> resultBorderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(resultBorderRadius.has_value());
        ASSERT_TRUE(resultBorderRadius->radiusTopLeft.has_value());
        EXPECT_EQ(resultBorderRadius->radiusTopLeft.value().ToString(), expectedStr);

        inputValueBorderRadius = std::get<1>(value);
        modifier_->setBorderRadius(node_, &inputValueBorderRadius);
        layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_NE(layoutProperty, nullptr);
        resultBorderRadius = layoutProperty->GetBackgroundBorderRadius();
        if (resultBorderRadius.has_value()) {
            EXPECT_FALSE(resultBorderRadius->radiusTopLeft.has_value());
            EXPECT_FALSE(resultBorderRadius->radiusTopRight.has_value());
            EXPECT_FALSE(resultBorderRadius->radiusBottomRight.has_value());
            EXPECT_FALSE(resultBorderRadius->radiusBottomLeft.has_value());
        }
    }
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
static std::vector<std::tuple<std::string, Opt_Dimension, std::string>> textIconSpaceTextIconSpaceValidValues = {
    { "60.25f", ArkValue<Opt_Dimension>(60.25f), "60.25vp" },
    { "ResId:FLOAT_RES_0_ID", Converter::ArkValue<Opt_Dimension>(FLOAT_RES_0_ID), "70.50px" }
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
    Opt_Dimension inputValueTextIconSpace;
    Opt_Dimension initValueTextIconSpace;

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
static std::vector<std::tuple<std::string, Opt_Dimension>> textIconSpaceInvalidValues = {
    { "-15", ArkValue<Opt_Dimension>(-15.f) },
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
    Opt_Dimension inputValueTextIconSpace;
    Opt_Dimension initValueTextIconSpace;

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
 * @tc.name: setKeyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setKeyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_KEY_DEFAULT_VALUE);
}

// Valid values for attribute 'key' of method 'key'
static std::vector<std::tuple<std::string, Ark_String, std::string>> keyKeyValidValues = {
    {"\"\"", Converter::ArkValue<Ark_String>(""), ""},
    {"\"abc\"", Converter::ArkValue<Ark_String>("abc"), "abc"},
};

/*
 * @tc.name: setKeyTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setKeyTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_String inputValueKey;
    Ark_String initValueKey;

    // Initial setup
    initValueKey = std::get<1>(keyKeyValidValues[0]);

    // Verifying attribute's  values
    inputValueKey = initValueKey;
    for (auto&& value: keyKeyValidValues) {
        inputValueKey = std::get<1>(value);
        auto convValue = ArkValue<Opt_String>(inputValueKey);
        modifier_->setKey(node_, &convValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEY_NAME);
        expectedStr = std::get<2>(value);
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
    Opt_Length inputValueWidth;
    Opt_Length initValueWidth;

    // Initial setup
    initValueWidth = std::get<1>(widthValidValues[0]);

    // Verifying attribute's  values
    inputValueWidth = initValueWidth;
    for (auto&& value: widthValidValues) {
        inputValueWidth = std::get<1>(value);
        modifier_->setWidth(node_, &inputValueWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setWidthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setWidthTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Length inputValueWidth;
    Opt_Length initValueWidth;

    // Initial setup
    initValueWidth = std::get<1>(widthValidValues[0]);

    inputValueWidth = initValueWidth;
    for (auto&& value: widthInvalidValues) {
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
    { "60.25f", ArkValue<Ark_Length>(60.25f), "60.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Ark_Length>(FLOAT_RES_0_ID),
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
        auto convValue = ArkValue<Opt_Length>(inputValueHeight);
        modifier_->setHeight(node_, &convValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, Ark_Length>> heightHeightInvalidValues = {
    {"-10", Converter::ArkValue<Ark_Length>(-10.)},
};

/*
 * @tc.name: setHeightTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setHeightTestInvalidValues, TestSize.Level1)
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
        auto convValue = ArkValue<Opt_Length>(inputValueHeight);
        modifier_->setHeight(node_, &convValue);
        inputValueHeight = std::get<1>(value);
        convValue = ArkValue<Opt_Length>(inputValueHeight);
        modifier_->setHeight(node_, &convValue);
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
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Opt_Length>(FLOAT_RES_0_ID),
        "70.50px"
    }
};

// Valid values for attribute 'height' of method 'size'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> sizeHeightValidValues = {
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Opt_Length>(FLOAT_RES_0_ID),
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
        auto convValue = ArkValue<Opt_SizeOptions>(inputValueSize);
        modifier_->setSize(node_, &convValue);
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
        auto convValue = ArkValue<Opt_SizeOptions>(inputValueSize);
        modifier_->setSize(node_, &convValue);
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
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setSizeTestInvalidValues, TestSize.Level1)
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
    expectedStrWidth = "0.00vp";
    expectedStrHeight = expectedStrWidth;

    // Verifying attribute's 'width'  values
    for (auto&& value: sizeWidthInvalidValues) {
        inputValueSize = initValueSize;
        auto convValue = ArkValue<Opt_SizeOptions>(inputValueSize);
        modifier_->setSize(node_, &convValue);
        inputValueSize.width = std::get<1>(value);
        convValue = ArkValue<Opt_SizeOptions>(inputValueSize);
        modifier_->setSize(node_, &convValue);
        jsonValue = GetJsonValue(node_);
        resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStrWidth) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'height'  values
    for (auto&& value: sizeHeightInvalidValues) {
        inputValueSize = initValueSize;
        auto convValue = ArkValue<Opt_SizeOptions>(inputValueSize);
        modifier_->setSize(node_, &convValue);
        inputValueSize.height = std::get<1>(value);
        convValue = ArkValue<Opt_SizeOptions>(inputValueSize);
        modifier_->setSize(node_, &convValue);
        jsonValue = GetJsonValue(node_);
        resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStrHeight) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'width' of method 'size'
static std::vector<std::tuple<std::string, Opt_Length>> sizeWidthInvalidValuesReset = {
    {"-10", Converter::ArkValue<Opt_Length>(-10.)},
};

// Invalid values for attribute 'height' of method 'size'
static std::vector<std::tuple<std::string, Opt_Length>> sizeHeightInvalidValuesReset = {
    {"-10", Converter::ArkValue<Opt_Length>(-10.)},
};

/*
 * @tc.name: setSizeTestInvalidValuesReset
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setSizeTestInvalidValuesReset, TestSize.Level1)
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
        auto convValue = ArkValue<Opt_SizeOptions>(inputValueSize);
        modifier_->setSize(node_, &convValue);
        inputValueSize.width = std::get<1>(value);
        convValue = ArkValue<Opt_SizeOptions>(inputValueSize);
        modifier_->setSize(node_, &convValue);
        jsonValue = GetJsonValue(node_);
        resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStrWidth) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'height'  values
    for (auto&& value: sizeHeightInvalidValuesReset) {
        inputValueSize = initValueSize;
        auto convValue = ArkValue<Opt_SizeOptions>(inputValueSize);
        modifier_->setSize(node_, &convValue);
        inputValueSize.height = std::get<1>(value);
        convValue = ArkValue<Opt_SizeOptions>(inputValueSize);
        modifier_->setSize(node_, &convValue);
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
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    { "0.f", ArkValue<Opt_Length>(0.f), "0.00vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Opt_Length>(FLOAT_RES_0_ID),
        "70.50px"
    }
};

// Valid values for attribute 'maxWidth' of method 'constraintSize'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> constraintSizeMaxWidthValidValues = {
    { "600.25f", ArkValue<Opt_Length>(600.25f), "600.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Opt_Length>(FLOAT_RES_0_ID),
        "70.50px"
    }
};

// Valid values for attribute 'minHeight' of method 'constraintSize'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> constraintSizeMinHeightValidValues = {
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    { "0.f", ArkValue<Opt_Length>(0.f), "0.00vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Opt_Length>(FLOAT_RES_0_ID),
        "70.50px"
    }
};

// Valid values for attribute 'maxHeight' of method 'constraintSize'
static std::vector<std::tuple<std::string, Opt_Length, std::string>> constraintSizeMaxHeightValidValues = {
    { "600.25f", ArkValue<Opt_Length>(600.25f), "600.25vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Opt_Length>(FLOAT_RES_0_ID),
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
        auto convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
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
        auto convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
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
        auto convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
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
        auto convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
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
        auto convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
        inputValueConstraintSize.minWidth = std::get<1>(value);
        convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
        jsonValue = GetJsonValue(node_);
        resultConstraintSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MIN_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStrMinWidth) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'maxWidth'  values
    for (auto&& value: constraintSizeMaxWidthInvalidValues) {
        inputValueConstraintSize = initValueConstraintSize;
        auto convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
        inputValueConstraintSize.maxWidth = std::get<1>(value);
        convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
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
        auto convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
        inputValueConstraintSize.minHeight = std::get<1>(value);
        convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
        jsonValue = GetJsonValue(node_);
        resultConstraintSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MIN_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStrMinHeight) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'maxHeight'  values
    for (auto&& value: constraintSizeMaxHeightInvalidValues) {
        inputValueConstraintSize = initValueConstraintSize;
        auto convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
        inputValueConstraintSize.maxHeight = std::get<1>(value);
        convValue = ArkValue<Opt_ConstraintSizeOptions>(inputValueConstraintSize);
        modifier_->setConstraintSize(node_, &convValue);
        jsonValue = GetJsonValue(node_);
        resultConstraintSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
        resultStr = GetAttrValue<std::string>(resultConstraintSize, ATTRIBUTE_CONSTRAINT_SIZE_MAX_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStrMaxHeight) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPaddingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setPaddingTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetPatternJsonValue(node_);
    std::unique_ptr<JsonValue> resultPadding =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PADDING_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_LEFT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PADDING_LEFT_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_RIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PADDING_RIGHT_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_TOP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PADDING_TOP_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_BOTTOM_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PADDING_BOTTOM_DEFAULT_VALUE);
}

std::vector<std::tuple<std::string, Ark_Dimension, std::string>> paddingValidValues = {
    { "60.25f", ArkValue<Ark_Dimension>(60.25f), "60.25vp" },
    { "-40.5f", ArkValue<Ark_Dimension>(-40.5f), "-40.50vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Ark_Dimension>(FLOAT_RES_0_ID),
        "70.50px"
    }
};

/*
 * @tc.name: setPaddingTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setPaddingTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultPadding;
    std::string resultStrLeft;
    std::string resultStrRight;
    std::string resultStrTop;
    std::string resultStrBottom;
    std::string expectedStr;
    Ark_Dimension inputValuePadding;

    for (auto&& value: paddingValidValues) {
        inputValuePadding = std::get<1>(value);
        auto unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Dimension>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();
        jsonValue = GetPatternJsonValue(node_);
        resultPadding = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PADDING_NAME);
        resultStrLeft = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_LEFT_NAME);
        resultStrRight = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_RIGHT_NAME);
        resultStrTop = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_TOP_NAME);
        resultStrBottom = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_BOTTOM_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStrLeft, expectedStr) << "Passed value is: " << std::get<0>(value);
        EXPECT_EQ(resultStrRight, expectedStr) << "Passed value is: " << std::get<0>(value);
        EXPECT_EQ(resultStrTop, expectedStr) << "Passed value is: " << std::get<0>(value);
        EXPECT_EQ(resultStrBottom, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

std::vector<std::tuple<std::string, Opt_Length, std::string>> optPaddingValidValues = {
    { "60.25f", ArkValue<Opt_Length>(60.25f), "60.25vp" },
    { "-40.5f", ArkValue<Opt_Length>(-40.5f), "-40.50vp" },
    {
        "ResId:FLOAT_RES_0_ID",
        Converter::ArkValue<Opt_Length>(FLOAT_RES_0_ID),
        "70.50px"
    }
};

/*
 * @tc.name: setPaddingTestLeftRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setPaddingTestLeftRightValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultPadding;
    std::string resultStr;
    std::string expectedStr;
    Ark_Padding inputValuePadding;
    Ark_Padding initValuePadding;

    // Initial setup
    initValuePadding.left = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.right = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.top = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.bottom = std::get<1>(optPaddingValidValues[0]);

    inputValuePadding = initValuePadding;
    for (auto&& value: optPaddingValidValues) {
        inputValuePadding.left = std::get<1>(value);
        auto unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();
        jsonValue = GetPatternJsonValue(node_);
        resultPadding = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PADDING_NAME);
        resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_LEFT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    inputValuePadding = initValuePadding;
    for (auto&& value: optPaddingValidValues) {
        inputValuePadding.right = std::get<1>(value);
        auto unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();
        jsonValue = GetPatternJsonValue(node_);
        resultPadding = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PADDING_NAME);
        resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_RIGHT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPaddingTestTopBottomValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setPaddingTestTopBottomValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultPadding;
    std::string resultStr;
    std::string expectedStr;
    Ark_Padding inputValuePadding;
    Ark_Padding initValuePadding;

    // Initial setup
    initValuePadding.left = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.right = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.top = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.bottom = std::get<1>(optPaddingValidValues[0]);

    inputValuePadding = initValuePadding;
    for (auto&& value: optPaddingValidValues) {
        inputValuePadding.top = std::get<1>(value);
        auto unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();
        jsonValue = GetPatternJsonValue(node_);
        resultPadding = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PADDING_NAME);
        resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_TOP_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    inputValuePadding = initValuePadding;
    for (auto&& value: optPaddingValidValues) {
        inputValuePadding.bottom = std::get<1>(value);
        auto unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();
        jsonValue = GetPatternJsonValue(node_);
        resultPadding = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PADDING_NAME);
        resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_BOTTOM_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPaddingTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setPaddingTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultPadding;
    std::string resultStrLeft;
    std::string resultStrRight;
    std::string resultStrTop;
    std::string resultStrBottom;
    std::string expectedStrLeft;
    std::string expectedStrRight;
    std::string expectedStrTop;
    std::string expectedStrBottom;
    Ark_Dimension inputValuePadding;
    Ark_Dimension initValuePadding;
    Opt_Union_Padding_Dimension unionValue;

    // Initial setup
    initValuePadding = std::get<1>(paddingValidValues[0]);

    inputValuePadding = initValuePadding;
    unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Dimension>(inputValuePadding);
    modifier_->setPadding(node_, &unionValue);
    OnModifyDone();

    unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Empty>(nullptr);
    modifier_->setPadding(node_, &unionValue);
    OnModifyDone();

    jsonValue = GetPatternJsonValue(node_);
    resultPadding = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PADDING_NAME);
    resultStrLeft = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_LEFT_NAME);
    resultStrRight = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_RIGHT_NAME);
    resultStrTop = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_TOP_NAME);
    resultStrBottom = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_BOTTOM_NAME);
    expectedStrLeft = ATTRIBUTE_PADDING_LEFT_DEFAULT_VALUE;
    expectedStrRight = ATTRIBUTE_PADDING_RIGHT_DEFAULT_VALUE;
    expectedStrTop = ATTRIBUTE_PADDING_TOP_DEFAULT_VALUE;
    expectedStrBottom = ATTRIBUTE_PADDING_BOTTOM_DEFAULT_VALUE;
    std::string message = "Passed value is: invalid union";
    EXPECT_EQ(resultStrLeft, expectedStrLeft) << message;
    EXPECT_EQ(resultStrRight, expectedStrRight) << message;
    EXPECT_EQ(resultStrTop, expectedStrTop) << message;
    EXPECT_EQ(resultStrBottom, expectedStrBottom) << message;
}

std::vector<std::tuple<std::string, Opt_Length>> optPaddingInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Length>(Ark_Empty())},
};

/*
 * @tc.name: setPaddingTestLeftRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setPaddingTestLeftRightInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultPadding;
    std::string resultStr;
    std::string expectedStr;
    Ark_Padding inputValuePadding;
    Ark_Padding initValuePadding;
    Opt_Union_Padding_Dimension unionValue;

    // Initial setup
    initValuePadding.left = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.right = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.top = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.bottom = std::get<1>(optPaddingValidValues[0]);

    inputValuePadding = initValuePadding;
    for (auto&& value: optPaddingInvalidValues) {
        inputValuePadding.left = initValuePadding.left;
        unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();

        inputValuePadding.left = std::get<1>(value);
        unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();

        jsonValue = GetPatternJsonValue(node_);
        resultPadding = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PADDING_NAME);
        resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_LEFT_NAME);
        expectedStr = ATTRIBUTE_PADDING_LEFT_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    inputValuePadding = initValuePadding;
    for (auto&& value: optPaddingInvalidValues) {
        inputValuePadding.right = initValuePadding.right;
        unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();

        inputValuePadding.right = std::get<1>(value);
        unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();

        jsonValue = GetPatternJsonValue(node_);
        resultPadding = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PADDING_NAME);
        resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_RIGHT_NAME);
        expectedStr = ATTRIBUTE_PADDING_RIGHT_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPaddingTestTopBottomInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setPaddingTestTopBottomInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultPadding;
    std::string resultStr;
    std::string expectedStr;
    Ark_Padding inputValuePadding;
    Ark_Padding initValuePadding;
    Opt_Union_Padding_Dimension unionValue;

    // Initial setup
    initValuePadding.left = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.right = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.top = std::get<1>(optPaddingValidValues[0]);
    initValuePadding.bottom = std::get<1>(optPaddingValidValues[0]);

    inputValuePadding = initValuePadding;
    for (auto&& value: optPaddingInvalidValues) {
        inputValuePadding.top = initValuePadding.top;
        unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();

        inputValuePadding.top = std::get<1>(value);
        unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();

        jsonValue = GetPatternJsonValue(node_);
        resultPadding = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PADDING_NAME);
        resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_TOP_NAME);
        expectedStr = ATTRIBUTE_PADDING_TOP_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    inputValuePadding = initValuePadding;
    for (auto&& value: optPaddingInvalidValues) {
        inputValuePadding.bottom = initValuePadding.bottom;
        unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();

        inputValuePadding.bottom = std::get<1>(value);
        unionValue = ArkUnion<Opt_Union_Padding_Dimension, Ark_Padding>(inputValuePadding);
        modifier_->setPadding(node_, &unionValue);
        OnModifyDone();

        jsonValue = GetPatternJsonValue(node_);
        resultPadding = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PADDING_NAME);
        resultStr = GetAttrValue<std::string>(resultPadding, ATTRIBUTE_PADDING_BOTTOM_NAME);
        expectedStr = ATTRIBUTE_PADDING_BOTTOM_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setFontFamilyTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontFamilyTestValidValues, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input, const Ark_Union_String_Resource& value,
        const std::string& expectedStr)
    {
        auto convValue = ArkValue<Opt_Union_String_Resource>(value);
        modifier_->setFontFamily(node_, &convValue);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        ASSERT_TRUE(layoutProperty->HasFontFamily()) <<
            "Input value is: " << input << ", method: setFontFamily";
        auto resultStr = GetFontFamilyInJson(layoutProperty->GetFontFamilyValue());
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontFamily";
    };

    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(value), expectedStr);
    }

    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_Union_String_Resource, Ark_Resource>(value), expectedStr);
    }
}

/*
 * @tc.name: setFontFamilyTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setFontFamilyTestInvalidValues, TestSize.Level1)
{
    Ark_Union_String_Resource initValueFontFamily;

    // Initial setup
    initValueFontFamily = ArkUnion<Ark_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](const std::string& input, const Ark_Union_String_Resource& value) {
        Ark_Union_String_Resource inputValueFontFamily = initValueFontFamily;
        auto convValue = ArkValue<Opt_Union_String_Resource>(inputValueFontFamily);
        modifier_->setFontFamily(node_, &convValue);
        inputValueFontFamily = value;
        convValue = ArkValue<Opt_Union_String_Resource>(inputValueFontFamily);
        modifier_->setFontFamily(node_, &convValue);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        EXPECT_FALSE(layoutProperty->HasFontFamily()) <<
            "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFamilyResourceInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontFamilyStringInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_String_Resource, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_String_Resource, Ark_Empty>(nullptr));
}
} // namespace OHOS::Ace::NG
