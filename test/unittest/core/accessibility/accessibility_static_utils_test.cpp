/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "core/accessibility/static/accessibility_static_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class AccessibilityStaticUtilsTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

// ==================== GetRoleByType ====================

/**
 * @tc.name: GetRoleByTypeTest001
 * @tc.desc: Test GetRoleByType with common role types (BUTTON, TEXT, IMAGE).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest001, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::BUTTON), "button");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::TEXT), "text");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::IMAGE), "image");
}

/**
 * @tc.name: GetRoleByTypeTest002
 * @tc.desc: Test GetRoleByType with container types (COLUMN, ROW, STACK, FLEX).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest002, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::COLUMN), "column");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::ROW), "row");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::STACK), "stack");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::FLEX), "flex");
}

/**
 * @tc.name: GetRoleByTypeTest003
 * @tc.desc: Test GetRoleByType with list/grid types (LIST, LIST_ITEM, GRID, GRID_ITEM).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest003, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::LIST), "list");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::LIST_ITEM), "listitem");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::GRID), "grid");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::GRID_ITEM), "griditem");
}

/**
 * @tc.name: GetRoleByTypeTest004
 * @tc.desc: Test GetRoleByType with picker types (DATE_PICKER, TIME_PICKER, TEXT_PICKER).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest004, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::DATE_PICKER), "datepicker");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::TIME_PICKER), "timepicker");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::TEXT_PICKER), "textpicker");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::PICKER), "picker");
}

/**
 * @tc.name: GetRoleByTypeTest005
 * @tc.desc: Test GetRoleByType with navigation types (NAVIGATION, NAV_DESTINATION, NAV_ROUTER, NAVIGATOR).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest005, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::NAVIGATION), "navigation");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::NAV_DESTINATION), "navdestination");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::NAV_ROUTER), "navrouter");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::NAVIGATOR), "navigator");
}

/**
 * @tc.name: GetRoleByTypeTest006
 * @tc.desc: Test GetRoleByType with input types (TEXT_INPUT, TEXT_AREA, SEARCH, CHECKBOX, RADIO, SWITCH, SLIDER).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest006, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::TEXT_INPUT), "textinput");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::TEXT_AREA), "textarea");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::SEARCH), "search");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::CHECKBOX), "checkbox");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::RADIO), "radio");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::SWITCH), "switch");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::SLIDER), "slider");
}

/**
 * @tc.name: GetRoleByTypeTest007
 * @tc.desc: Test GetRoleByType with tabs/swiper types (TABS, TAB_CONTENT, TAB_BAR, SWIPER).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest007, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::TABS), "tabs");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::TAB_CONTENT), "tabcontent");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::TAB_BAR), "tab-bar");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::SWIPER), "swiper");
}

/**
 * @tc.name: GetRoleByTypeTest008
 * @tc.desc: Test GetRoleByType with canvas/media types (CANVAS, VIDEO, WEB, XCOMPONENT).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest008, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::CANVAS), "canvas");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::VIDEO), "video");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::WEB), "web");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::XCOMPONENT), "xcomponent");
}

/**
 * @tc.name: GetRoleByTypeTest009
 * @tc.desc: Test GetRoleByType with shape types (CIRCLE, ELLIPSE, LINE, PATH, RECT, POLYGON, POLYLINE, SHAPE).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest009, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::CIRCLE), "circle");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::ELLIPSE), "ellipse");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::LINE), "line");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::PATH), "path");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::RECT), "rect");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::POLYGON), "polygon");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::POLYLINE), "polyline");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::SHAPE), "shape");
}

/**
 * @tc.name: GetRoleByTypeTest010
 * @tc.desc: Test GetRoleByType with menu types (MENU, MENU_ITEM, MENU_ITEM_GROUP).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest010, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::MENU), "menu");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::MENU_ITEM), "menuitem");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::MENU_ITEM_GROUP), "menuitemgroup");
}

/**
 * @tc.name: GetRoleByTypeTest011
 * @tc.desc: Test GetRoleByType with remaining role types (SCROLL, PROGRESS, RATING, GAUGE, DIALOG, DIVIDER, etc.).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest011, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::SCROLL), "scroll");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::PROGRESS), "progress");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::RATING), "rating");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::GAUGE), "gauge");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::DIALOG), "dialog");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::DIVIDER), "divider");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::SELECT), "select");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::HYPERLINK), "hyperlink");
}

/**
 * @tc.name: GetRoleByTypeTest012
 * @tc.desc: Test GetRoleByType with dash-separated names (GRID_ROW, NAVIGATION_BAR, etc.).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTest, GetRoleByTypeTest012, TestSize.Level1)
{
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::GRID_ROW), "grid-row");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::NAVIGATION_BAR), "navigation-bar");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::NAVIGATION_MENU), "navigation-menu");
    EXPECT_EQ(AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType::PICKER_VIEW), "picker-view");
}
} // namespace OHOS::Ace
