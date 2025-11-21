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
#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_model_data.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"

#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
const auto ATTRIBUTE_NAV_BAR_WIDTH_NAME = "navBarWidth";
const auto ATTRIBUTE_NAV_BAR_WIDTH_DEFAULT_VALUE = "240.00vp";
const auto ATTRIBUTE_NAV_BAR_POSITION_NAME = "navBarPosition";
const auto ATTRIBUTE_NAV_BAR_POSITION_DEFAULT_VALUE = "NavBarPosition.Start";
const auto ATTRIBUTE_NAV_BAR_WIDTH_RANGE_NAME = "navBarWidthRange";
const auto ATTRIBUTE_NAV_BAR_WIDTH_RANGE_DEFAULT_VALUE = "240.00vp, 432.00vp";
const auto ATTRIBUTE_MIN_CONTENT_WIDTH_NAME = "minContentWidth";
const auto ATTRIBUTE_MIN_CONTENT_WIDTH_DEFAULT_VALUE = "360.00vp";
const auto ATTRIBUTE_MODE_NAME = "mode";
const auto ATTRIBUTE_MODE_DEFAULT_VALUE = "NavigationMode.AUTO";
const auto ATTRIBUTE_HIDE_NAV_BAR_NAME = "hideNavBar";
const auto ATTRIBUTE_HIDE_NAV_BAR_DEFAULT_VALUE = false;
const auto ATTRIBUTE_SUBTITLE_NAME = "subtitle";
const auto ATTRIBUTE_SUBTITLE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_HIDE_TITLE_BAR_NAME = "hideTitleBar";
const auto ATTRIBUTE_HIDE_TITLE_BAR_DEFAULT_VALUE = false;
const auto ATTRIBUTE_IS_ANIMATED_TITLE_BAR_NAME = "isAnimatedTitleBar";
const auto ATTRIBUTE_IS_ANIMATED_TITLE_BAR_DEFAULT_VALUE = false;
const auto ATTRIBUTE_HIDE_BACK_BUTTON_NAME = "hideBackButton";
const auto ATTRIBUTE_HIDE_BACK_BUTTON_DEFAULT_VALUE = false;
const auto ATTRIBUTE_TITLE_MODE_NAME = "titleMode";
const auto ATTRIBUTE_TITLE_MODE_DEFAULT_VALUE = "NavigationTitleMode.Free";
const auto ATTRIBUTE_HIDE_TOOL_BAR_NAME = "hideToolBar";
const auto ATTRIBUTE_HIDE_TOOL_BAR_DEFAULT_VALUE = false;
const auto ATTRIBUTE_RECOVERABLE_NAME = "recoverable";
const auto ATTRIBUTE_RECOVERABLE_DEFAULT_VALUE = false;
const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_NAME = "ignoreLayoutSafeAreaTypes";
const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_DEFAULT_VALUE = "SAFE_AREA_TYPE_NONE";
const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_EDGES_NAME = "ignoreLayoutSafeAreaEdges";
const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_EDGES_DEFAULT_VALUE = "SAFE_AREA_Edge_NONE";
const auto ATTRIBUTE_MENUS_NAME = "menus";
const auto ATTRIBUTE_MENUS_DEFAULT_VALUE = "";
const auto MENU_ITEM_COUNT = 3.0;
} // namespace

class NavigationModifierTest : public ModifierTestBase<GENERATED_ArkUINavigationModifier,
    &GENERATED_ArkUINodeModifiers::getNavigationModifier, GENERATED_ARKUI_NAVIGATION> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = SetupThemeStyle(THEME_PATTERN_NAVIGATION_BAR);
        themeStyle->SetAttr("navigation_bar_most_menu_item_count_in_bar", { .value = MENU_ITEM_COUNT });
        SetupTheme<NavigationBarTheme>();
    }
};

/*
 * @tc.name: setNavBarWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_WIDTH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_NAV_BAR_WIDTH_DEFAULT_VALUE);
}

/*
 * @tc.name: setNavBarWidthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthTestValidValues, TestSize.Level1)
{
    std::string strResult;

    typedef std::pair<Ark_Length, std::string> OneTestStep;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1.), "1.00px" },
        { Converter::ArkValue<Ark_Length>(2.45), "2.45vp" },
        { Converter::ArkValue<Ark_Length>("5.0px"), "5.00px" },
        { Converter::ArkValue<Ark_Length>("22.35px"), "22.35px" },
        { Converter::ArkValue<Ark_Length>("7.0vp"), "7.00vp" },
        { Converter::ArkValue<Ark_Length>("1.65vp"), "1.65vp" },
        { Converter::ArkValue<Ark_Length>("65.0fp"), "65.00fp" },
        { Converter::ArkValue<Ark_Length>("4.3fp"), "4.30fp" },
        { Converter::ArkValue<Ark_Length>("23.00%"), "23.00%" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        modifier_->setNavBarWidth(node_, &arkLength);
        strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_WIDTH_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: DISABLED_setNavBarWidthTestValidResourceValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setNavBarWidthTestValidResourceValues, TestSize.Level1)
{
    // implement after Resource supporting
}

/*
 * @tc.name: setNavBarWidthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthTestInvalidValues, TestSize.Level1)
{
    std::string strResult;

    typedef Ark_Length OneTestStep;
    const std::vector<OneTestStep> testPlan = {
        Converter::ArkValue<Ark_Length>(-1.),
        Converter::ArkValue<Ark_Length>(-3.56),
        Converter::ArkValue<Ark_Length>(0.),
        Converter::ArkValue<Ark_Length>("-8.0px"),
        Converter::ArkValue<Ark_Length>("-15.6px"),
        Converter::ArkValue<Ark_Length>("-21.0vp"),
        Converter::ArkValue<Ark_Length>("-8.6vp"),
        Converter::ArkValue<Ark_Length>("-32.0fp"),
        Converter::ArkValue<Ark_Length>("-9.99fp"),
    };

    for (auto arkLength: testPlan) {
        modifier_->setNavBarWidth(node_, &arkLength);
        strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_NAV_BAR_WIDTH_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: DISABLED_setNavBarWidthTestInvalidResourceValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setNavBarWidthTestInvalidResourceValues, TestSize.Level1)
{
    // implement after Resource supporting
}

/*
 * @tc.name: setNavBarPositionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarPositionTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_POSITION_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_NAV_BAR_POSITION_DEFAULT_VALUE);
}

/*
 * @tc.name: setNavBarPositionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarPositionTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_NavBarPosition inputValue;

    // check NavBarPosition End value
    inputValue = ARK_NAV_BAR_POSITION_END;
    modifier_->setNavBarPosition(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_POSITION_NAME);
    EXPECT_EQ(strResult, "NavBarPosition.End");

    // check NavBarPosition Start value
    inputValue = ARK_NAV_BAR_POSITION_START;
    modifier_->setNavBarPosition(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_POSITION_NAME);
    EXPECT_EQ(strResult, "NavBarPosition.Start");
}

/*
 * @tc.name: setNavBarPositionTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarPositionTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_NavBarPosition inputValue;

    // check value less then possible range
    inputValue = static_cast<Ark_NavBarPosition>(-1);
    modifier_->setNavBarPosition(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_POSITION_NAME);
    EXPECT_EQ(strResult, "NavBarPosition.Start");

    // check value more then possible range
    inputValue = static_cast<Ark_NavBarPosition>(2);
    modifier_->setNavBarPosition(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_POSITION_NAME);
    EXPECT_EQ(strResult, "NavBarPosition.Start");
}

/*
 * @tc.name: setNavBarWidthRangeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthRangeTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_WIDTH_RANGE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_NAV_BAR_WIDTH_RANGE_DEFAULT_VALUE);
}

/*
 * @tc.name: setNavBarWidthRangeTestValidMinValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthRangeTestValidMinValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Tuple_Dimension_Dimension inputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1.), "1.00px, 432.00vp" },
        { Converter::ArkValue<Ark_Length>(2.45), "2.45vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("5.0px"), "5.00px, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("22.35px"), "22.35px, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("7.0vp"), "7.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("1.65vp"), "1.65vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("65.0fp"), "65.00fp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("4.3fp"), "4.30fp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("23.00%"), "23.00%, 432.00vp" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        inputValue.value0 = arkLength;
        inputValue.value1 = Converter::ArkValue<Ark_Length>(0.);
        modifier_->setNavBarWidthRange(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_WIDTH_RANGE_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setNavBarWidthRangeTestValidMaxValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthRangeTestValidMaxValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Tuple_Dimension_Dimension inputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1.), "240.00vp, 1.00px" },
        { Converter::ArkValue<Ark_Length>(2.45), "240.00vp, 2.45vp" },
        { Converter::ArkValue<Ark_Length>("5.0px"), "240.00vp, 5.00px" },
        { Converter::ArkValue<Ark_Length>("22.35px"), "240.00vp, 22.35px" },
        { Converter::ArkValue<Ark_Length>("7.0vp"), "240.00vp, 7.00vp" },
        { Converter::ArkValue<Ark_Length>("1.65vp"), "240.00vp, 1.65vp" },
        { Converter::ArkValue<Ark_Length>("65.0fp"), "240.00vp, 65.00fp" },
        { Converter::ArkValue<Ark_Length>("4.3fp"), "240.00vp, 4.30fp" },
        { Converter::ArkValue<Ark_Length>("23.00%"), "240.00vp, 23.00%" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        inputValue.value0 = Converter::ArkValue<Ark_Length>(0.);
        inputValue.value1 = arkLength;
        modifier_->setNavBarWidthRange(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_WIDTH_RANGE_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: DISABLED_setNavBarWidthRangeTestValidResourceValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setNavBarWidthRangeTestValidResourceValues, TestSize.Level1)
{
    // implement after Resource supporting
}

/*
 * @tc.name: setNavBarWidthRangeTestInvalidMinValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthRangeTestInvalidMinValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Tuple_Dimension_Dimension inputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(-1.), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>(-3.56), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-8.0px"), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-15.6px"), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-21.0vp"), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-8.6vp"), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-32.0fp"), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-9.99_fp"), "240.00vp, 432.00vp" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        inputValue.value0 = arkLength;
        inputValue.value1 = Converter::ArkValue<Ark_Length>(0.);
        modifier_->setNavBarWidthRange(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_WIDTH_RANGE_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setNavBarWidthRangeTestInvalidMaxValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavBarWidthRangeTestInvalidMaxValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Tuple_Dimension_Dimension inputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(-1.), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>(-3.56), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-8.0px"), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-15.6px"), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-21.0vp"), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-8.6vp"), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-32.0fp"), "240.00vp, 432.00vp" },
        { Converter::ArkValue<Ark_Length>("-9.99fp"), "240.00vp, 432.00vp" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        inputValue.value0 = Converter::ArkValue<Ark_Length>(0.);
        inputValue.value1 = arkLength;
        modifier_->setNavBarWidthRange(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_NAV_BAR_WIDTH_RANGE_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: DISABLED_setNavBarWidthRangeTestValidResourceValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setNavBarWidthRangeTestInvalidResourceValues, TestSize.Level1)
{
    // implement after Resource supporting
}

/*
 * @tc.name: setMinContentWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setMinContentWidthTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_MIN_CONTENT_WIDTH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_MIN_CONTENT_WIDTH_DEFAULT_VALUE);
}

/*
 * @tc.name: setMinContentWidthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setMinContentWidthTestValidValues, TestSize.Level1)
{
    std::string strResult;
    typedef std::pair<Ark_Length, std::string> OneTestStep;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1.), "1.00px" },
        { Converter::ArkValue<Ark_Length>(2.45), "2.45vp" },
        { Converter::ArkValue<Ark_Length>("5.0px"), "5.00px" },
        { Converter::ArkValue<Ark_Length>("22.35px"), "22.35px" },
        { Converter::ArkValue<Ark_Length>("7.0vp"), "7.00vp" },
        { Converter::ArkValue<Ark_Length>("1.65vp"), "1.65vp" },
        { Converter::ArkValue<Ark_Length>("65.0fp"), "65.00fp" },
        { Converter::ArkValue<Ark_Length>("4.3fp"), "4.30fp" },
        { Converter::ArkValue<Ark_Length>("23.00%"), "23.00%" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        modifier_->setMinContentWidth(node_, &arkLength);
        strResult = GetStringAttribute(node_, ATTRIBUTE_MIN_CONTENT_WIDTH_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: DISABLED_MinContentWidthTestValidResourceValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_MinContentWidthTestValidResourceValues, TestSize.Level1)
{
    // implement after Resource supporting
}

/*
 * @tc.name: setMinContentWidthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setMinContentWidthTestInvalidValues, TestSize.Level1)
{
    std::string strResult;

    typedef Ark_Length OneTestStep;
    const std::vector<OneTestStep> testPlan = {
        Converter::ArkValue<Ark_Length>(-1.),
        Converter::ArkValue<Ark_Length>(-3.56),
        Converter::ArkValue<Ark_Length>(0.),
        Converter::ArkValue<Ark_Length>("-8.0px"),
        Converter::ArkValue<Ark_Length>("-15.6px"),
        Converter::ArkValue<Ark_Length>("-21.0vp"),
        Converter::ArkValue<Ark_Length>("-8.6vp"),
        Converter::ArkValue<Ark_Length>("-32.0fp"),
        Converter::ArkValue<Ark_Length>("-9.99fp"),
    };

    for (auto arkLength: testPlan) {
        modifier_->setMinContentWidth(node_, &arkLength);
        strResult = GetStringAttribute(node_, ATTRIBUTE_MIN_CONTENT_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_MIN_CONTENT_WIDTH_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setModeTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_MODE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_MODE_DEFAULT_VALUE);
}

/*
 * @tc.name: setModeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setModeTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_NavigationMode inputValue;

    // Stack test
    inputValue = ARK_NAVIGATION_MODE_STACK;
    modifier_->setMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_MODE_NAME);
    EXPECT_EQ(strResult, "NavigationMode.STACK");

    // Split test
    inputValue = ARK_NAVIGATION_MODE_SPLIT;
    modifier_->setMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_MODE_NAME);
    EXPECT_EQ(strResult, "NavigationMode.SPLIT");

    // Auto test
    inputValue = ARK_NAVIGATION_MODE_AUTO;
    modifier_->setMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_MODE_NAME);
    EXPECT_EQ(strResult, "NavigationMode.AUTO");
}

/*
 * @tc.name: setModeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setModeTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_NavigationMode inputValue;

    // less than possible range
    inputValue = static_cast<Ark_NavigationMode>(-1);
    modifier_->setMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_MODE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_MODE_DEFAULT_VALUE);

    // more than possible range
    inputValue = static_cast<Ark_NavigationMode>(3);
    modifier_->setMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_MODE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_MODE_DEFAULT_VALUE);
}

/*
 * @tc.name: setHideNavBarTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideNavBarTestDefaultValues, TestSize.Level1)
{
    bool boolResult;
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_NAV_BAR_NAME);
    EXPECT_EQ(boolResult, ATTRIBUTE_HIDE_NAV_BAR_DEFAULT_VALUE);
}

/*
 * @tc.name: setHideNavBarTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideNavBarTestValidValues, TestSize.Level1)
{
    bool boolResult;
    Ark_Boolean inputValue;

    // check true
    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setHideNavBar(node_, inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_NAV_BAR_NAME);
    EXPECT_EQ(boolResult, true);

    // check false
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setHideNavBar(node_, inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_NAV_BAR_NAME);
    EXPECT_EQ(boolResult, false);
}

/*
 * @tc.name: setSubTitleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setSubTitleTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_SUBTITLE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SUBTITLE_DEFAULT_VALUE);
}

/*
 * @tc.name: setSubTitleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setSubTitleTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_String inputValue;

    inputValue = Converter::ArkValue<Ark_String>("subTitle test");
    modifier_->setSubTitle(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SUBTITLE_NAME);
    EXPECT_EQ(strResult, "subTitle test");

    inputValue = Converter::ArkValue<Ark_String>("another subtitle");
    modifier_->setSubTitle(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SUBTITLE_NAME);
    EXPECT_EQ(strResult, "another subtitle");
}

/*
 * @tc.name: setSubTitleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setSubTitleTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    modifier_->setSubTitle(node_, nullptr);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SUBTITLE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SUBTITLE_DEFAULT_VALUE);
}

/*
 * @tc.name: setHideTitleBar0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideTitleBar0TestDefaultValues, TestSize.Level1)
{
    bool boolResult;
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
    EXPECT_EQ(boolResult, ATTRIBUTE_HIDE_TITLE_BAR_DEFAULT_VALUE);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_IS_ANIMATED_TITLE_BAR_NAME);
    EXPECT_EQ(boolResult, ATTRIBUTE_IS_ANIMATED_TITLE_BAR_DEFAULT_VALUE);
}

/*
 * @tc.name: setHideTitleBar0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideTitleBar0TestValidValues, TestSize.Level1)
{
    bool boolResult;
    Ark_Boolean inputValue;

    // true
    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setHideTitleBar0(node_, inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
    EXPECT_EQ(boolResult, true);

    // false
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setHideTitleBar0(node_, inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
    EXPECT_EQ(boolResult, false);
}

/*
 * @tc.name: DISABLED_setHideTitleBar1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideTitleBar1TestDefaultValues, TestSize.Level1)
{
    // create test when HideTitleBar1Impl implemented
}

/*
 * @tc.name: DISABLED_setHideTitleBar1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideTitleBar1TestValidValues, TestSize.Level1)
{
    // create test when HideTitleBar1Impl implemented
}

/*
 * @tc.name: setHideBackButtonTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideBackButtonTestDefaultValues, TestSize.Level1)
{
    bool boolResult;
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_BACK_BUTTON_NAME);
    EXPECT_EQ(boolResult, ATTRIBUTE_HIDE_BACK_BUTTON_DEFAULT_VALUE);
}

/*
 * @tc.name: setHideBackButtonTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideBackButtonTestValidValues, TestSize.Level1)
{
    bool boolResult;
    Ark_Boolean inputValue;

    // true
    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setHideBackButton(node_, inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_BACK_BUTTON_NAME);
    EXPECT_EQ(boolResult, true);

    // false
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setHideBackButton(node_, inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_BACK_BUTTON_NAME);
    EXPECT_EQ(boolResult, false);
}

/*
 * @tc.name: setTitleModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setTitleModeTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_TITLE_MODE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_TITLE_MODE_DEFAULT_VALUE);
}

/*
 * @tc.name: setTitleModeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setTitleModeTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_NavigationTitleMode inputValue;

    // Full
    inputValue = ARK_NAVIGATION_TITLE_MODE_FULL;
    modifier_->setTitleMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_TITLE_MODE_NAME);
    EXPECT_EQ(strResult, "NavigationTitleMode.Full");

    // Mini
    inputValue = ARK_NAVIGATION_TITLE_MODE_MINI;
    modifier_->setTitleMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_TITLE_MODE_NAME);
    EXPECT_EQ(strResult, "NavigationTitleMode.Mini");

    // Free
    inputValue = ARK_NAVIGATION_TITLE_MODE_FREE;
    modifier_->setTitleMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_TITLE_MODE_NAME);
    EXPECT_EQ(strResult, "NavigationTitleMode.Free");
}

/*
 * @tc.name: setTitleModeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setTitleModeTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_NavigationTitleMode inputValue;

    // less than possible range
    inputValue = static_cast<Ark_NavigationTitleMode>(-1);
    modifier_->setTitleMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_TITLE_MODE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_TITLE_MODE_DEFAULT_VALUE);

    // more than possible range
    inputValue = static_cast<Ark_NavigationTitleMode>(3);
    modifier_->setTitleMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_TITLE_MODE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_TITLE_MODE_DEFAULT_VALUE);
}

/*
 * @tc.name: setHideToolBar0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideToolBar0TestDefaultValues, TestSize.Level1)
{
    bool boolResult;
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_TOOL_BAR_NAME);
    EXPECT_EQ(boolResult, ATTRIBUTE_HIDE_TOOL_BAR_DEFAULT_VALUE);
}

/*
 * @tc.name: setHideToolBar0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setHideToolBar0TestValidValues, TestSize.Level1)
{
    bool boolResult;
    Ark_Boolean inputValue;

    // Initial setup
    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setHideToolBar0(node_, inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_TOOL_BAR_NAME);
    EXPECT_EQ(boolResult, true);

    // Verifying attribute's other values
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setHideToolBar0(node_, inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_HIDE_TOOL_BAR_NAME);
    EXPECT_EQ(boolResult, false);
}

/*
 * @tc.name: DISABLED_setHideToolBar1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideToolBar1TestDefaultValues, TestSize.Level1)
{
    // create test when HideToolBar1Impl implemented
}

/*
 * @tc.name: DISABLED_setHideToolBar1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, DISABLED_setHideToolBar1TestValidValues, TestSize.Level1)
{
    // create test when HideToolBar1Impl implemented
}

/*
 * @tc.name: setOnNavBarStateChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setOnNavBarStateChangeTest, TestSize.Level1)
{
    Callback_Boolean_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool isVisible;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    modifier_->setOnNavBarStateChange(node_, &func);

    // check true value
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireNavBarStateChangeEvent(true);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->isVisible, true);

    // check false value
    eventHub->FireNavBarStateChangeEvent(false);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->isVisible, false);
}

/*
 * @tc.name: setOnNavigationModeChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setOnNavigationModeChangeTest, TestSize.Level1)
{
    Callback_NavigationMode_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        Ark_NavigationMode mode;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    modifier_->setOnNavigationModeChange(node_, &func);

    // check Split value
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireNavigationModeChangeEvent(NavigationMode::SPLIT);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->mode, ARK_NAVIGATION_MODE_SPLIT);

    // check Stack value
    eventHub->FireNavigationModeChangeEvent(NavigationMode::STACK);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->mode, ARK_NAVIGATION_MODE_STACK);

    // check Auto value
    eventHub->FireNavigationModeChangeEvent(NavigationMode::AUTO);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->mode, ARK_NAVIGATION_MODE_AUTO);
}

/*
 * @tc.name: setRecoverableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setRecoverableTestDefaultValues, TestSize.Level1)
{
    bool boolResult;
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_RECOVERABLE_NAME);
    EXPECT_EQ(boolResult, ATTRIBUTE_RECOVERABLE_DEFAULT_VALUE);
}

/*
 * @tc.name: setRecoverableTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setRecoverableTestValidValues, TestSize.Level1)
{
    bool boolResult;
    Opt_Boolean inputValue;

    // Initial setup
    inputValue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setRecoverable(node_, &inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_RECOVERABLE_NAME);
    EXPECT_EQ(boolResult, true);

    // Verifying attribute's other values
    inputValue = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setRecoverable(node_, &inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_RECOVERABLE_NAME);
    EXPECT_EQ(boolResult, false);
}

/*
 * @tc.name: setRecoverableTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setRecoverableTestInvalidValues, TestSize.Level1)
{
    bool boolResult;
    Opt_Boolean inputValue;

    // Initial setup
    inputValue = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    modifier_->setRecoverable(node_, &inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_RECOVERABLE_NAME);
    EXPECT_EQ(boolResult, ATTRIBUTE_RECOVERABLE_DEFAULT_VALUE);
}

/*
 * @tc.name: DISABLED_setIgnoreLayoutSafeAreaDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 *
 * DISABLED due to nothing values in the json
 */
HWTEST_F(NavigationModifierTest, DISABLED_setIgnoreLayoutSafeAreaDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_DEFAULT_VALUE) <<
        "Default value for attribute 'ignoreLayoutSafeAreaTypes'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_EDGES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_EDGES_DEFAULT_VALUE) <<
        "Default value for attribute 'ignoreLayoutSafeAreaEdges'";
}

/*
 * @tc.name: DISABLED_setIgnoreLayoutSafeAreaType
 * @tc.desc:
 * @tc.type: FUNC
 *
 * DISABLED due to nothing values in the json
 */
HWTEST_F(NavigationModifierTest, DISABLED_setIgnoreLayoutSafeAreaType, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    ASSERT_NE(modifier_->setIgnoreLayoutSafeArea, nullptr);

    std::initializer_list<Ark_LayoutSafeAreaType> indexList = {ARK_LAYOUT_SAFE_AREA_TYPE_SYSTEM};
    Converter::ArkArrayHolder<Array_LayoutSafeAreaType> holderTypes(indexList);
    auto arkTypeValid = holderTypes.OptValue<Opt_Array_LayoutSafeAreaType>();
    auto arkTypeEmpty = Converter::ArkValue<Opt_Array_LayoutSafeAreaType>(Ark_Empty());

    modifier_->setIgnoreLayoutSafeArea(node_, &arkTypeValid, nullptr);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_NAME);
    EXPECT_EQ(resultStr, "SAFE_AREA_TYPE_SYSTEM");

    modifier_->setIgnoreLayoutSafeArea(node_, &arkTypeEmpty, nullptr);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_NAME);
    EXPECT_EQ(resultStr, "SAFE_AREA_TYPE_NONE");

    modifier_->setIgnoreLayoutSafeArea(node_, &arkTypeValid, nullptr);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_NAME);
    EXPECT_EQ(resultStr, "SAFE_AREA_TYPE_SYSTEM");

    modifier_->setIgnoreLayoutSafeArea(node_, nullptr, nullptr);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_I_TYPES_NAME);
    EXPECT_EQ(resultStr, "SAFE_AREA_TYPE_NONE");
}

/*
 * @tc.name: DISABLED_setMenusTestDefault
 * @tc.desc:
 * @tc.type: FUNC
 *
 * DISABLED due to nothing values in the json
 */
HWTEST_F(NavigationModifierTest, DISABLED_setMenusTestDefault, TestSize.Level1)
{
    auto resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_MENUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MENUS_DEFAULT_VALUE);
}

/*
 * @tc.name: DISABLED_setMenusTest
 * @tc.desc:
 * @tc.type: FUNC
 *
 * DISABLED due to nothing values in the json
 */
HWTEST_F(NavigationModifierTest, DISABLED_setMenusTest, TestSize.Level1)
{
    using namespace Converter;
    std::string resultStr;

    ASSERT_NE(modifier_->setMenus, nullptr);

    Ark_NavigationMenuItem oneItem {
        .value = ArkUnion<Ark_Union_String_Resource, Ark_String>(std::string()),
        .icon = ArkUnion<Opt_Union_String_Resource, Ark_String>("iconPath"),
        .symbolIcon = ArkValue<Opt_CustomObject>(),
        .isEnabled = ArkValue<Opt_Boolean>(true),
        .action = ArkValue<Opt_Callback_Void>()
    };
    ArkArrayHolder<Array_NavigationMenuItem> holderItems({oneItem});

    auto arkItems =
        ArkUnion<Ark_Union_Array_NavigationMenuItem_CustomBuilder, Array_NavigationMenuItem>(holderItems.ArkValue());
    modifier_->setMenus(node_, &arkItems);

    // trigger the menu building
    auto fnode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(fnode, nullptr);
    fnode->MarkModifyDone();

    resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_MENUS_NAME);
    EXPECT_EQ(resultStr, "{\"items\":[[\"iconPath\",\"\"]]}");
}
/**
 * @tc.name: onTitleModeChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, onTitleModeChangeTest, TestSize.Level1)
{
    const int32_t contextId = 123;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<Ark_NavigationTitleMode> checkInvoke;
    auto checkFunc =
        [](const Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode) { checkInvoke = titleMode; };
    auto arkCallback = Converter::ArkValue<Callback_NavigationTitleMode_Void>(checkFunc, contextId);
    modifier_->setOnTitleModeChange(node_, &arkCallback);

    checkInvoke.reset();
    NavigationTitleModeChangeEvent changeTitleModeMini(true);
    eventHub->FireChangeEvent(&changeTitleModeMini);
    ASSERT_TRUE(checkInvoke.has_value());
    EXPECT_EQ(*checkInvoke, ARK_NAVIGATION_TITLE_MODE_MINI);

    checkInvoke.reset();
    NavigationTitleModeChangeEvent changeTitleModeFull(false);
    eventHub->FireChangeEvent(&changeTitleModeFull);
    ASSERT_TRUE(checkInvoke.has_value());
    EXPECT_EQ(*checkInvoke, ARK_NAVIGATION_TITLE_MODE_FULL);
}

/**
 * @tc.name: setNavigationOptions1Test
 * @tc.desc: Check the functionality of NavigationInterfaceModifier::SetNavigationOptions1Impl
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavigationOptions1Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setNavigationOptions1, nullptr);

    auto navigationNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setNavigationOptions1(node_, nullptr);
    Ark_Materialized navPathStackUndef {nullptr};
    modifier_->setNavigationOptions1(node_, &navPathStackUndef);

    // get accessor, construct, finalyzer
    const GENERATED_ArkUIAccessors *accessors
        = fullAPI_ ? fullAPI_->getAccessors() : nullptr;
    const GENERATED_ArkUINavPathStackAccessor *accessorNavPathStack
        = accessors && accessors->getNavPathStackAccessor ? (*accessors->getNavPathStackAccessor)() : nullptr;
    ASSERT_NE(accessorNavPathStack, nullptr);
    ASSERT_NE(accessorNavPathStack->construct, nullptr);
    ASSERT_NE(accessorNavPathStack->getFinalizer, nullptr);
    auto finalyzer = reinterpret_cast<void (*)(NavPathStackPeer *)>(accessorNavPathStack->getFinalizer());
    ASSERT_NE(finalyzer, nullptr);

    // create the NavPathStack peer and attach it to modifier
    auto navPathStackPeer = (*accessorNavPathStack->construct)();
    Ark_Materialized navPathStackValid = { reinterpret_cast<Ark_NativePointer>(navPathStackPeer) };
    modifier_->setNavigationOptions1(node_, &navPathStackValid);

    EXPECT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    Ark_NavPathInfo arkNavPathInfo {
        .name = Converter::ArkValue<Ark_String>("PageA"),
        .param = Converter::ArkValue<Opt_CustomObject>(),
        .onPop = Converter::ArkValue<Opt_Callback_PopInfo_Void>(),
        .isEntry = Converter::ArkValue<Opt_Boolean>()
    };
    ASSERT_NE(accessorNavPathStack->pushPath0, nullptr);
    accessorNavPathStack->pushPath0(navPathStackPeer, &arkNavPathInfo, nullptr);
    EXPECT_TRUE(navigationPattern->NeedSyncWithJsStackMarked());

    // detach NavPathStack and destroy it
    modifier_->setNavigationOptions1(node_, &navPathStackUndef);
    (*finalyzer)(navPathStackPeer);

    navigationPattern = nullptr;
    navigationNode = nullptr;
}

/**
 * @tc.name: setNavDestinationTest
 * @tc.desc: Check the functionality of NavigationInterfaceModifier::SetNavDestinationImpl
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModifierTest, setNavDestinationTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setNavigationOptions1, nullptr);
    ASSERT_NE(modifier_->setNavDestination, nullptr);

    static const int32_t expectedRes = 123;

    auto navigationNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setNavigationOptions1(node_, nullptr);
    Ark_Materialized navPathStackUndef {nullptr};
    modifier_->setNavigationOptions1(node_, &navPathStackUndef);

    // get accessor, construct, finalyzer
    const GENERATED_ArkUIAccessors *accessors
        = fullAPI_ ? fullAPI_->getAccessors() : nullptr;
    const GENERATED_ArkUINavPathStackAccessor *accessorNavPathStack
        = accessors && accessors->getNavPathStackAccessor ? (*accessors->getNavPathStackAccessor)() : nullptr;
    ASSERT_NE(accessorNavPathStack, nullptr);
    ASSERT_NE(accessorNavPathStack->construct, nullptr);
    ASSERT_NE(accessorNavPathStack->getFinalizer, nullptr);
    auto finalyzer = reinterpret_cast<void (*)(NavPathStackPeer *)>(accessorNavPathStack->getFinalizer());
    ASSERT_NE(finalyzer, nullptr);

    // create the NavPathStack peer and attach it to modifier
    auto navPathStackPeer = (*accessorNavPathStack->construct)();
    Ark_Materialized navPathStackValid = { reinterpret_cast<Ark_NativePointer>(navPathStackPeer) };
    modifier_->setNavigationOptions1(node_, &navPathStackValid);

    static bool wasInvoked = false;
    auto buildFunc = [](Ark_Int32 resourceId, const Ark_String name, const Ark_CustomObject param) {
        EXPECT_EQ(expectedRes, resourceId);
        wasInvoked = true;
    };

    auto arkBuildFunc = Converter::ArkValue<Callback_String_Unknown_Void>(buildFunc, expectedRes);
    modifier_->setNavDestination(node_, &arkBuildFunc);

    EXPECT_FALSE(wasInvoked);
    Ark_NavPathInfo arkNavPathInfo {
        .name = Converter::ArkValue<Ark_String>("PageA"),
        .param = Converter::ArkValue<Opt_CustomObject>(),
        .onPop = Converter::ArkValue<Opt_Callback_PopInfo_Void>(),
        .isEntry = Converter::ArkValue<Opt_Boolean>()
    };
    ASSERT_NE(accessorNavPathStack->pushPath0, nullptr);
    accessorNavPathStack->pushPath0(navPathStackPeer, &arkNavPathInfo, nullptr);

    MockPipelineContext::GetCurrent()->FlushBuild();
    EXPECT_TRUE(wasInvoked);

    // detach NavPathStack and destroy it
    modifier_->setNavigationOptions1(node_, &navPathStackUndef);
    (*finalyzer)(navPathStackPeer);

    navigationPattern = nullptr;
    navigationNode = nullptr;
}
} // namespace OHOS::Ace::NG
