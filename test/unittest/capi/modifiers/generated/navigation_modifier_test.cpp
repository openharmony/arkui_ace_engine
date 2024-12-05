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
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_TITLE_NAME = "title";
const auto ATTRIBUTE_TITLE_I_VALUE_NAME = "value";
const auto ATTRIBUTE_TITLE_I_OPTIONS_NAME = "options";
const auto ATTRIBUTE_TOOLBAR_CONFIGURATION_NAME = "toolbarConfiguration";
const auto ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_NAME = "options";
const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_NAME = "ignoreLayoutSafeArea";
const auto ATTRIBUTE_PATH_INFOS_NAME = "pathInfos";
const auto ATTRIBUTE_PATH_INFOS_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_NAV_BAR_WIDTH_NAME = "navBarWidth";
const auto ATTRIBUTE_NAV_BAR_WIDTH_DEFAULT_VALUE = "240.00vp";
const auto ATTRIBUTE_NAV_BAR_POSITION_NAME = "navBarPosition";
const auto ATTRIBUTE_NAV_BAR_POSITION_DEFAULT_VALUE = "NavBarPosition.Start";
const auto ATTRIBUTE_NAV_BAR_WIDTH_RANGE_NAME = "navBarWidthRange";
const auto ATTRIBUTE_NAV_BAR_WIDTH_RANGE_DEFAULT_VALUE = "240.00vp, 432.00vp";
const auto ATTRIBUTE_MIN_CONTENT_WIDTH_NAME = "minContentWidth";
const auto ATTRIBUTE_MIN_CONTENT_WIDTH_DEFAULT_VALUE = "360.00vp";
const auto ATTRIBUTE_MODE_NAME = "mode";
const auto ATTRIBUTE_MODE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_BACK_BUTTON_ICON_NAME = "backButtonIcon";
const auto ATTRIBUTE_BACK_BUTTON_ICON_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_HIDE_NAV_BAR_NAME = "hideNavBar";
const auto ATTRIBUTE_HIDE_NAV_BAR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SUB_TITLE_NAME = "subTitle";
const auto ATTRIBUTE_SUB_TITLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_HIDE_TITLE_BAR_NAME = "hideTitleBar";
const auto ATTRIBUTE_HIDE_TITLE_BAR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_HIDE_TITLE_BAR_I_HIDE_NAME = "hide";
const auto ATTRIBUTE_HIDE_TITLE_BAR_I_HIDE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_HIDE_TITLE_BAR_I_ANIMATED_NAME = "animated";
const auto ATTRIBUTE_HIDE_TITLE_BAR_I_ANIMATED_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_HIDE_BACK_BUTTON_NAME = "hideBackButton";
const auto ATTRIBUTE_HIDE_BACK_BUTTON_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_MODE_NAME = "titleMode";
const auto ATTRIBUTE_TITLE_MODE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_MENUS_NAME = "menus";
const auto ATTRIBUTE_MENUS_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TOOL_BAR_NAME = "toolBar";
const auto ATTRIBUTE_TOOL_BAR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_HIDE_TOOL_BAR_NAME = "hideToolBar";
const auto ATTRIBUTE_HIDE_TOOL_BAR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_HIDE_TOOL_BAR_I_HIDE_NAME = "hide";
const auto ATTRIBUTE_HIDE_TOOL_BAR_I_HIDE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_HIDE_TOOL_BAR_I_ANIMATED_NAME = "animated";
const auto ATTRIBUTE_HIDE_TOOL_BAR_I_ANIMATED_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_RECOVERABLE_NAME = "recoverable";
const auto ATTRIBUTE_RECOVERABLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ENABLE_DRAG_BAR_NAME = "enableDragBar";
const auto ATTRIBUTE_ENABLE_DRAG_BAR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_I_VALUE_I_MAIN_NAME = "main";
const auto ATTRIBUTE_TITLE_I_VALUE_I_MAIN_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_I_VALUE_I_SUB_NAME = "sub";
const auto ATTRIBUTE_TITLE_I_VALUE_I_SUB_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_I_VALUE_I_HEIGHT_NAME = "height";
const auto ATTRIBUTE_TITLE_I_VALUE_I_HEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_BACKGROUND_COLOR_NAME = "backgroundColor";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_BACKGROUND_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_BACKGROUND_BLUR_STYLE_NAME = "backgroundBlurStyle";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_BACKGROUND_BLUR_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_BAR_STYLE_NAME = "barStyle";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_BAR_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_PADDING_START_NAME = "paddingStart";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_PADDING_START_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_PADDING_END_NAME = "paddingEnd";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_PADDING_END_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_MAIN_TITLE_MODIFIER_NAME = "mainTitleModifier";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_MAIN_TITLE_MODIFIER_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_SUB_TITLE_MODIFIER_NAME = "subTitleModifier";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_SUB_TITLE_MODIFIER_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_ENABLE_HOVER_MODE_NAME = "enableHoverMode";
const auto ATTRIBUTE_TITLE_I_OPTIONS_I_ENABLE_HOVER_MODE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TOOLBAR_CONFIGURATION_I_VALUE_NAME = "value";
const auto ATTRIBUTE_TOOLBAR_CONFIGURATION_I_VALUE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BACKGROUND_COLOR_NAME = "backgroundColor";
const auto ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BACKGROUND_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BACKGROUND_BLUR_STYLE_NAME = "backgroundBlurStyle";
const auto ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BACKGROUND_BLUR_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BAR_STYLE_NAME = "barStyle";
const auto ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BAR_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_NAME = "types";
const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_EDGES_NAME = "edges";
const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_EDGES_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace

class NavigationModifierTest : public ModifierTestBase<GENERATED_ArkUINavigationModifier,
                                   &GENERATED_ArkUINodeModifiers::getNavigationModifier, GENERATED_ARKUI_NAVIGATION> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setNavigationOptions1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setNavigationOptions1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PATH_INFOS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PATH_INFOS_DEFAULT_VALUE) << "Default value for attribute 'pathInfos'";
}

/*
 * @tc.name: setNavigationOptions1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setNavigationOptions1TestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setNavBarWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAV_BAR_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NAV_BAR_WIDTH_DEFAULT_VALUE) << "Default value for attribute 'navBarWidth'";
}

/*
 * @tc.name: setNavBarWidthTestNavBarWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthTestNavBarWidthValidValues, TestSize.Level1)
{
    Ark_Length initValueNavBarWidth;

    // Initial setup
    initValueNavBarWidth = std::get<1>(Fixtures::testFixtureLengthPositiveValidValues[0]);

    auto checkValue = [this, &initValueNavBarWidth](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_Length inputValueNavBarWidth = initValueNavBarWidth;

        inputValueNavBarWidth = value;
        modifier_->setNavBarWidth(node_, &inputValueNavBarWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAV_BAR_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setNavBarWidth, attribute: navBarWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthPositiveValidValues) {
        checkValue(input, expected, value);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthResPositiveValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setNavBarWidthTestNavBarWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthTestNavBarWidthInvalidValues, TestSize.Level1)
{
    Ark_Length initValueNavBarWidth;

    // Initial setup
    initValueNavBarWidth = std::get<1>(Fixtures::testFixtureLengthPositiveValidValues[0]);

    auto checkValue = [this, &initValueNavBarWidth](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueNavBarWidth = initValueNavBarWidth;

        modifier_->setNavBarWidth(node_, &inputValueNavBarWidth);
        inputValueNavBarWidth = value;
        modifier_->setNavBarWidth(node_, &inputValueNavBarWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAV_BAR_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NAV_BAR_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setNavBarWidth, attribute: navBarWidth";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthPositiveInvalidValues) {
        checkValue(input, value);
    }
    for (auto& [input, value] : Fixtures::testFixtureLengthResPositiveInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNavBarPositionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarPositionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAV_BAR_POSITION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NAV_BAR_POSITION_DEFAULT_VALUE) << "Default value for attribute 'navBarPosition'";
}

/*
 * @tc.name: setNavBarPositionTestNavBarPositionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarPositionTestNavBarPositionValidValues, TestSize.Level1)
{
    Ark_NavBarPosition initValueNavBarPosition;

    // Initial setup
    initValueNavBarPosition = std::get<1>(Fixtures::testFixtureEnumNavBarPositionValidValues[0]);

    auto checkValue = [this, &initValueNavBarPosition](
                          const std::string& input, const std::string& expectedStr, const Ark_NavBarPosition& value) {
        Ark_NavBarPosition inputValueNavBarPosition = initValueNavBarPosition;

        inputValueNavBarPosition = value;
        modifier_->setNavBarPosition(node_, inputValueNavBarPosition);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAV_BAR_POSITION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setNavBarPosition, attribute: navBarPosition";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNavBarPositionValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setNavBarPositionTestNavBarPositionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarPositionTestNavBarPositionInvalidValues, TestSize.Level1)
{
    Ark_NavBarPosition initValueNavBarPosition;

    // Initial setup
    initValueNavBarPosition = std::get<1>(Fixtures::testFixtureEnumNavBarPositionValidValues[0]);

    auto checkValue = [this, &initValueNavBarPosition](const std::string& input, const Ark_NavBarPosition& value) {
        Ark_NavBarPosition inputValueNavBarPosition = initValueNavBarPosition;

        modifier_->setNavBarPosition(node_, inputValueNavBarPosition);
        inputValueNavBarPosition = value;
        modifier_->setNavBarPosition(node_, inputValueNavBarPosition);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAV_BAR_POSITION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NAV_BAR_POSITION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setNavBarPosition, attribute: navBarPosition";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNavBarPositionInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNavBarWidthRangeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthRangeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAV_BAR_WIDTH_RANGE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NAV_BAR_WIDTH_RANGE_DEFAULT_VALUE) <<
        "Default value for attribute 'navBarWidthRange'";
}

/*
 * @tc.name: setNavBarWidthRangeTestNavBarWidthRangeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthRangeTestNavBarWidthRangeValidValues, TestSize.Level1)
{
    Ark_Tuple_Dimension_Dimension initValueNavBarWidthRange;

    // Initial setup
    initValueNavBarWidthRange = std::get<1>(Fixtures::testFixtureFixtureNavBarWidthRangeValidValues[0]);

    auto checkValue = [this, &initValueNavBarWidthRange](const std::string& input, const std::string& expectedStr,
                          const Ark_Tuple_Dimension_Dimension& value) {
        Ark_Tuple_Dimension_Dimension inputValueNavBarWidthRange = initValueNavBarWidthRange;

        inputValueNavBarWidthRange = value;
        modifier_->setNavBarWidthRange(node_, &inputValueNavBarWidthRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAV_BAR_WIDTH_RANGE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setNavBarWidthRange, attribute: navBarWidthRange";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFixtureNavBarWidthRangeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setNavBarWidthRangeTestNavBarWidthRangeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthRangeTestNavBarWidthRangeInvalidValues, TestSize.Level1)
{
    Ark_Tuple_Dimension_Dimension initValueNavBarWidthRange;

    // Initial setup
    initValueNavBarWidthRange = std::get<1>(Fixtures::testFixtureFixtureNavBarWidthRangeValidValues[0]);

    auto checkValue = [this, &initValueNavBarWidthRange](
                          const std::string& input, const Ark_Tuple_Dimension_Dimension& value) {
        Ark_Tuple_Dimension_Dimension inputValueNavBarWidthRange = initValueNavBarWidthRange;

        modifier_->setNavBarWidthRange(node_, &inputValueNavBarWidthRange);
        inputValueNavBarWidthRange = value;
        modifier_->setNavBarWidthRange(node_, &inputValueNavBarWidthRange);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NAV_BAR_WIDTH_RANGE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NAV_BAR_WIDTH_RANGE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setNavBarWidthRange, attribute: navBarWidthRange";
    };

    for (auto& [input, value] : Fixtures::testFixtureFixtureNavBarWidthRangeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setMinContentWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setMinContentWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_CONTENT_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_CONTENT_WIDTH_DEFAULT_VALUE) << "Default value for attribute 'minContentWidth'";
}

/*
 * @tc.name: setMinContentWidthTestMinContentWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setMinContentWidthTestMinContentWidthValidValues, TestSize.Level1)
{
    Ark_Length initValueMinContentWidth;

    // Initial setup
    initValueMinContentWidth = std::get<1>(Fixtures::testFixtureLengthPositiveValidValues[0]);

    auto checkValue = [this, &initValueMinContentWidth](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_Length inputValueMinContentWidth = initValueMinContentWidth;

        inputValueMinContentWidth = value;
        modifier_->setMinContentWidth(node_, &inputValueMinContentWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_CONTENT_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinContentWidth, attribute: minContentWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthPositiveValidValues) {
        checkValue(input, expected, value);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthResPositiveValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setMinContentWidthTestMinContentWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setMinContentWidthTestMinContentWidthInvalidValues, TestSize.Level1)
{
    Ark_Length initValueMinContentWidth;

    // Initial setup
    initValueMinContentWidth = std::get<1>(Fixtures::testFixtureLengthPositiveValidValues[0]);

    auto checkValue = [this, &initValueMinContentWidth](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueMinContentWidth = initValueMinContentWidth;

        modifier_->setMinContentWidth(node_, &inputValueMinContentWidth);
        inputValueMinContentWidth = value;
        modifier_->setMinContentWidth(node_, &inputValueMinContentWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_CONTENT_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_CONTENT_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMinContentWidth, attribute: minContentWidth";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthPositiveInvalidValues) {
        checkValue(input, value);
    }
    for (auto& [input, value] : Fixtures::testFixtureLengthResPositiveInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MODE_DEFAULT_VALUE) << "Default value for attribute 'mode'";
}

/*
 * @tc.name: setModeTestModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setModeTestModeValidValues, TestSize.Level1)
{
    Ark_NavigationMode initValueMode;

    // Initial setup
    initValueMode = std::get<1>(Fixtures::testFixtureEnumNavigationModeValidValues[0]);

    auto checkValue = [this, &initValueMode](
                          const std::string& input, const std::string& expectedStr, const Ark_NavigationMode& value) {
        Ark_NavigationMode inputValueMode = initValueMode;

        inputValueMode = value;
        modifier_->setMode(node_, inputValueMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setMode, attribute: mode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNavigationModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setModeTestModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setModeTestModeInvalidValues, TestSize.Level1)
{
    Ark_NavigationMode initValueMode;

    // Initial setup
    initValueMode = std::get<1>(Fixtures::testFixtureEnumNavigationModeValidValues[0]);

    auto checkValue = [this, &initValueMode](const std::string& input, const Ark_NavigationMode& value) {
        Ark_NavigationMode inputValueMode = initValueMode;

        modifier_->setMode(node_, inputValueMode);
        inputValueMode = value;
        modifier_->setMode(node_, inputValueMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMode, attribute: mode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNavigationModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setBackButtonIconTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setBackButtonIconTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACK_BUTTON_ICON_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BACK_BUTTON_ICON_DEFAULT_VALUE) << "Default value for attribute 'backButtonIcon'";
}

/*
 * @tc.name: setBackButtonIconTestBackButtonIconValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setBackButtonIconTestBackButtonIconValidValues, TestSize.Level1)
{
    Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier initValueBackButtonIcon;

    // Initial setup
    initValueBackButtonIcon = ArkUnion<Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier, Ark_String>(
        std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueBackButtonIcon](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier& value) {
        Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier inputValueBackButtonIcon = initValueBackButtonIcon;

        inputValueBackButtonIcon = value;
        modifier_->setBackButtonIcon(node_, &inputValueBackButtonIcon);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACK_BUTTON_ICON_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBackButtonIcon, attribute: backButtonIcon";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(
            input, expected, ArkUnion<Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier, Ark_String>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setBackButtonIconTestBackButtonIconInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setBackButtonIconTestBackButtonIconInvalidValues, TestSize.Level1)
{
    Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier initValueBackButtonIcon;

    // Initial setup
    initValueBackButtonIcon = ArkUnion<Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier, Ark_String>(
        std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueBackButtonIcon](const std::string& input,
                          const Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier& value) {
        Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier inputValueBackButtonIcon = initValueBackButtonIcon;

        modifier_->setBackButtonIcon(node_, &inputValueBackButtonIcon);
        inputValueBackButtonIcon = value;
        modifier_->setBackButtonIcon(node_, &inputValueBackButtonIcon);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BACK_BUTTON_ICON_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BACK_BUTTON_ICON_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBackButtonIcon, attribute: backButtonIcon";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setHideNavBarTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideNavBarTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_NAV_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HIDE_NAV_BAR_DEFAULT_VALUE) << "Default value for attribute 'hideNavBar'";
}

/*
 * @tc.name: setHideNavBarTestHideNavBarValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideNavBarTestHideNavBarValidValues, TestSize.Level1)
{
    Ark_Boolean initValueHideNavBar;

    // Initial setup
    initValueHideNavBar = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueHideNavBar](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueHideNavBar = initValueHideNavBar;

        inputValueHideNavBar = value;
        modifier_->setHideNavBar(node_, inputValueHideNavBar);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_NAV_BAR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHideNavBar, attribute: hideNavBar";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setSubTitleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setSubTitleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SUB_TITLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SUB_TITLE_DEFAULT_VALUE) << "Default value for attribute 'subTitle'";
}

/*
 * @tc.name: setSubTitleTestSubTitleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setSubTitleTestSubTitleValidValues, TestSize.Level1)
{
    Ark_String initValueSubTitle;

    // Initial setup
    initValueSubTitle = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueSubTitle](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValueSubTitle = initValueSubTitle;

        inputValueSubTitle = value;
        modifier_->setSubTitle(node_, &inputValueSubTitle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SUB_TITLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSubTitle, attribute: subTitle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setHideTitleBar0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideTitleBar0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HIDE_TITLE_BAR_DEFAULT_VALUE) << "Default value for attribute 'hideTitleBar'";
}

/*
 * @tc.name: setHideTitleBar0TestHideTitleBarValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideTitleBar0TestHideTitleBarValidValues, TestSize.Level1)
{
    Ark_Boolean initValueHideTitleBar;

    // Initial setup
    initValueHideTitleBar = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueHideTitleBar](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueHideTitleBar = initValueHideTitleBar;

        inputValueHideTitleBar = value;
        modifier_->setHideTitleBar0(node_, inputValueHideTitleBar);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHideTitleBar0, attribute: hideTitleBar";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setHideTitleBar1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideTitleBar1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultHideTitleBar =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultHideTitleBar, ATTRIBUTE_HIDE_TITLE_BAR_I_HIDE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HIDE_TITLE_BAR_I_HIDE_DEFAULT_VALUE) <<
        "Default value for attribute 'hideTitleBar.hide'";

    resultStr = GetAttrValue<std::string>(resultHideTitleBar, ATTRIBUTE_HIDE_TITLE_BAR_I_ANIMATED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HIDE_TITLE_BAR_I_ANIMATED_DEFAULT_VALUE) <<
        "Default value for attribute 'hideTitleBar.animated'";
}

/*
 * @tc.name: setHideTitleBar1TestHideTitleBarHideValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideTitleBar1TestHideTitleBarHideValidValues, TestSize.Level1)
{
    Ark_Boolean initValueHide;
    Ark_Boolean initValueAnimated;

    // Initial setup
    initValueHide = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueAnimated = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueHide, &initValueAnimated](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueHide = initValueHide;
        Ark_Boolean inputValueAnimated = initValueAnimated;

        inputValueHide = value;
        modifier_->setHideTitleBar1(node_, inputValueHide, inputValueAnimated);
        auto jsonValue = GetJsonValue(node_);
        auto resultHideTitleBar = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultHideTitleBar, ATTRIBUTE_HIDE_TITLE_BAR_I_HIDE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHideTitleBar1, attribute: hideTitleBar.hide";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setHideTitleBar1TestHideTitleBarAnimatedValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideTitleBar1TestHideTitleBarAnimatedValidValues, TestSize.Level1)
{
    Ark_Boolean initValueHide;
    Ark_Boolean initValueAnimated;

    // Initial setup
    initValueHide = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueAnimated = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueHide, &initValueAnimated](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueHide = initValueHide;
        Ark_Boolean inputValueAnimated = initValueAnimated;

        inputValueAnimated = value;
        modifier_->setHideTitleBar1(node_, inputValueHide, inputValueAnimated);
        auto jsonValue = GetJsonValue(node_);
        auto resultHideTitleBar = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultHideTitleBar, ATTRIBUTE_HIDE_TITLE_BAR_I_ANIMATED_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHideTitleBar1, attribute: hideTitleBar.animated";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setHideBackButtonTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideBackButtonTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_BACK_BUTTON_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HIDE_BACK_BUTTON_DEFAULT_VALUE) << "Default value for attribute 'hideBackButton'";
}

/*
 * @tc.name: setHideBackButtonTestHideBackButtonValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideBackButtonTestHideBackButtonValidValues, TestSize.Level1)
{
    Ark_Boolean initValueHideBackButton;

    // Initial setup
    initValueHideBackButton = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueHideBackButton](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueHideBackButton = initValueHideBackButton;

        inputValueHideBackButton = value;
        modifier_->setHideBackButton(node_, inputValueHideBackButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_BACK_BUTTON_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHideBackButton, attribute: hideBackButton";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setTitleModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setTitleModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TITLE_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_MODE_DEFAULT_VALUE) << "Default value for attribute 'titleMode'";
}

/*
 * @tc.name: setTitleModeTestTitleModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setTitleModeTestTitleModeValidValues, TestSize.Level1)
{
    Ark_NavigationTitleMode initValueTitleMode;

    // Initial setup
    initValueTitleMode = std::get<1>(Fixtures::testFixtureEnumNavigationTitleModeValidValues[0]);

    auto checkValue = [this, &initValueTitleMode](const std::string& input, const std::string& expectedStr,
                          const Ark_NavigationTitleMode& value) {
        Ark_NavigationTitleMode inputValueTitleMode = initValueTitleMode;

        inputValueTitleMode = value;
        modifier_->setTitleMode(node_, inputValueTitleMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TITLE_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTitleMode, attribute: titleMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNavigationTitleModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setTitleModeTestTitleModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setTitleModeTestTitleModeInvalidValues, TestSize.Level1)
{
    Ark_NavigationTitleMode initValueTitleMode;

    // Initial setup
    initValueTitleMode = std::get<1>(Fixtures::testFixtureEnumNavigationTitleModeValidValues[0]);

    auto checkValue = [this, &initValueTitleMode](const std::string& input, const Ark_NavigationTitleMode& value) {
        Ark_NavigationTitleMode inputValueTitleMode = initValueTitleMode;

        modifier_->setTitleMode(node_, inputValueTitleMode);
        inputValueTitleMode = value;
        modifier_->setTitleMode(node_, inputValueTitleMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TITLE_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTitleMode, attribute: titleMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNavigationTitleModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setMenusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setMenusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MENUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MENUS_DEFAULT_VALUE) << "Default value for attribute 'menus'";
}

/*
 * @tc.name: setMenusTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setMenusTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setToolBarTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setToolBarTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TOOL_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TOOL_BAR_DEFAULT_VALUE) << "Default value for attribute 'toolBar'";
}

/*
 * @tc.name: setToolBarTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setToolBarTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setHideToolBar0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideToolBar0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_TOOL_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HIDE_TOOL_BAR_DEFAULT_VALUE) << "Default value for attribute 'hideToolBar'";
}

/*
 * @tc.name: setHideToolBar0TestHideToolBarValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideToolBar0TestHideToolBarValidValues, TestSize.Level1)
{
    Ark_Boolean initValueHideToolBar;

    // Initial setup
    initValueHideToolBar = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueHideToolBar](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueHideToolBar = initValueHideToolBar;

        inputValueHideToolBar = value;
        modifier_->setHideToolBar0(node_, inputValueHideToolBar);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_TOOL_BAR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHideToolBar0, attribute: hideToolBar";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setHideToolBar1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideToolBar1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultHideToolBar =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_HIDE_TOOL_BAR_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultHideToolBar, ATTRIBUTE_HIDE_TOOL_BAR_I_HIDE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HIDE_TOOL_BAR_I_HIDE_DEFAULT_VALUE) <<
        "Default value for attribute 'hideToolBar.hide'";

    resultStr = GetAttrValue<std::string>(resultHideToolBar, ATTRIBUTE_HIDE_TOOL_BAR_I_ANIMATED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HIDE_TOOL_BAR_I_ANIMATED_DEFAULT_VALUE) <<
        "Default value for attribute 'hideToolBar.animated'";
}

/*
 * @tc.name: setHideToolBar1TestHideToolBarHideValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideToolBar1TestHideToolBarHideValidValues, TestSize.Level1)
{
    Ark_Boolean initValueHide;
    Ark_Boolean initValueAnimated;

    // Initial setup
    initValueHide = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueAnimated = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueHide, &initValueAnimated](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueHide = initValueHide;
        Ark_Boolean inputValueAnimated = initValueAnimated;

        inputValueHide = value;
        modifier_->setHideToolBar1(node_, inputValueHide, inputValueAnimated);
        auto jsonValue = GetJsonValue(node_);
        auto resultHideToolBar = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_HIDE_TOOL_BAR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultHideToolBar, ATTRIBUTE_HIDE_TOOL_BAR_I_HIDE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHideToolBar1, attribute: hideToolBar.hide";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setHideToolBar1TestHideToolBarAnimatedValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideToolBar1TestHideToolBarAnimatedValidValues, TestSize.Level1)
{
    Ark_Boolean initValueHide;
    Ark_Boolean initValueAnimated;

    // Initial setup
    initValueHide = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    initValueAnimated = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueHide, &initValueAnimated](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueHide = initValueHide;
        Ark_Boolean inputValueAnimated = initValueAnimated;

        inputValueAnimated = value;
        modifier_->setHideToolBar1(node_, inputValueHide, inputValueAnimated);
        auto jsonValue = GetJsonValue(node_);
        auto resultHideToolBar = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_HIDE_TOOL_BAR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultHideToolBar, ATTRIBUTE_HIDE_TOOL_BAR_I_ANIMATED_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHideToolBar1, attribute: hideToolBar.animated";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setRecoverableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setRecoverableTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RECOVERABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RECOVERABLE_DEFAULT_VALUE) << "Default value for attribute 'recoverable'";
}

/*
 * @tc.name: setRecoverableTestRecoverableValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setRecoverableTestRecoverableValidValues, TestSize.Level1)
{
    Opt_Boolean initValueRecoverable;

    // Initial setup
    initValueRecoverable = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueRecoverable](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueRecoverable = initValueRecoverable;

        inputValueRecoverable = value;
        modifier_->setRecoverable(node_, &inputValueRecoverable);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RECOVERABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRecoverable, attribute: recoverable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setRecoverableTestRecoverableInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setRecoverableTestRecoverableInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueRecoverable;

    // Initial setup
    initValueRecoverable = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueRecoverable](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueRecoverable = initValueRecoverable;

        modifier_->setRecoverable(node_, &inputValueRecoverable);
        inputValueRecoverable = value;
        modifier_->setRecoverable(node_, &inputValueRecoverable);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RECOVERABLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RECOVERABLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRecoverable, attribute: recoverable";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setEnableDragBarTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setEnableDragBarTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DRAG_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_DRAG_BAR_DEFAULT_VALUE) << "Default value for attribute 'enableDragBar'";
}

/*
 * @tc.name: setEnableDragBarTestEnableDragBarValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setEnableDragBarTestEnableDragBarValidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableDragBar;

    // Initial setup
    initValueEnableDragBar = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableDragBar](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableDragBar = initValueEnableDragBar;

        inputValueEnableDragBar = value;
        modifier_->setEnableDragBar(node_, &inputValueEnableDragBar);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DRAG_BAR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableDragBar, attribute: enableDragBar";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setEnableDragBarTestEnableDragBarInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setEnableDragBarTestEnableDragBarInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableDragBar;

    // Initial setup
    initValueEnableDragBar = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableDragBar](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableDragBar = initValueEnableDragBar;

        modifier_->setEnableDragBar(node_, &inputValueEnableDragBar);
        inputValueEnableDragBar = value;
        modifier_->setEnableDragBar(node_, &inputValueEnableDragBar);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DRAG_BAR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_DRAG_BAR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnableDragBar, attribute: enableDragBar";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setTitleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setTitleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTitle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TITLE_NAME);
    std::unique_ptr<JsonValue> resultValue =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultTitle, ATTRIBUTE_TITLE_I_VALUE_NAME);
    std::unique_ptr<JsonValue> resultOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultTitle, ATTRIBUTE_TITLE_I_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_TITLE_I_VALUE_I_MAIN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_I_VALUE_I_MAIN_DEFAULT_VALUE) <<
        "Default value for attribute 'title.value.NavigationCommonTitle.main'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_TITLE_I_VALUE_I_SUB_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_I_VALUE_I_SUB_DEFAULT_VALUE) <<
        "Default value for attribute 'title.value.NavigationCommonTitle.sub'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_TITLE_I_VALUE_I_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_I_VALUE_I_HEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'title.value.NavigationCustomTitle.height'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_TITLE_I_OPTIONS_I_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_I_OPTIONS_I_BACKGROUND_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'title.options.backgroundColor'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_TITLE_I_OPTIONS_I_BACKGROUND_BLUR_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_I_OPTIONS_I_BACKGROUND_BLUR_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'title.options.backgroundBlurStyle'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_TITLE_I_OPTIONS_I_BAR_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_I_OPTIONS_I_BAR_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'title.options.barStyle'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_TITLE_I_OPTIONS_I_PADDING_START_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_I_OPTIONS_I_PADDING_START_DEFAULT_VALUE) <<
        "Default value for attribute 'title.options.paddingStart'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_TITLE_I_OPTIONS_I_PADDING_END_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_I_OPTIONS_I_PADDING_END_DEFAULT_VALUE) <<
        "Default value for attribute 'title.options.paddingEnd'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_TITLE_I_OPTIONS_I_MAIN_TITLE_MODIFIER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_I_OPTIONS_I_MAIN_TITLE_MODIFIER_DEFAULT_VALUE) <<
        "Default value for attribute 'title.options.mainTitleModifier'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_TITLE_I_OPTIONS_I_SUB_TITLE_MODIFIER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_I_OPTIONS_I_SUB_TITLE_MODIFIER_DEFAULT_VALUE) <<
        "Default value for attribute 'title.options.subTitleModifier'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_TITLE_I_OPTIONS_I_ENABLE_HOVER_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TITLE_I_OPTIONS_I_ENABLE_HOVER_MODE_DEFAULT_VALUE) <<
        "Default value for attribute 'title.options.enableHoverMode'";
}

/*
 * @tc.name: setTitleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setTitleTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setToolbarConfigurationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setToolbarConfigurationTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultToolbarConfiguration =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TOOLBAR_CONFIGURATION_NAME);
    std::unique_ptr<JsonValue> resultOptions = GetAttrValue<std::unique_ptr<JsonValue>>(
        resultToolbarConfiguration, ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultToolbarConfiguration, ATTRIBUTE_TOOLBAR_CONFIGURATION_I_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TOOLBAR_CONFIGURATION_I_VALUE_DEFAULT_VALUE) <<
        "Default value for attribute 'toolbarConfiguration.value'";

    resultStr =
        GetAttrValue<std::string>(resultOptions, ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BACKGROUND_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'toolbarConfiguration.options.backgroundColor'";

    resultStr = GetAttrValue<std::string>(
        resultOptions, ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BACKGROUND_BLUR_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BACKGROUND_BLUR_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'toolbarConfiguration.options.backgroundBlurStyle'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BAR_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TOOLBAR_CONFIGURATION_I_OPTIONS_I_BAR_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'toolbarConfiguration.options.barStyle'";
}

/*
 * @tc.name: setToolbarConfigurationTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setToolbarConfigurationTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setIgnoreLayoutSafeAreaTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setIgnoreLayoutSafeAreaTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultIgnoreLayoutSafeArea =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultIgnoreLayoutSafeArea, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_DEFAULT_VALUE) <<
        "Default value for attribute 'ignoreLayoutSafeArea.types'";

    resultStr = GetAttrValue<std::string>(resultIgnoreLayoutSafeArea, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_EDGES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_EDGES_DEFAULT_VALUE) <<
        "Default value for attribute 'ignoreLayoutSafeArea.edges'";
}

/*
 * @tc.name: setIgnoreLayoutSafeAreaTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setIgnoreLayoutSafeAreaTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}
} // namespace OHOS::Ace::NG
