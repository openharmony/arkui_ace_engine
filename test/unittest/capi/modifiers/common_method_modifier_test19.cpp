/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
static const std::unordered_map<Ark_AccessibilityRoleType, std::string> ACCESSIBILITY_ROLE_MAP {
    { ARK_ACCESSIBILITY_ROLE_TYPE_ACTION_SHEET, "actionsheet" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_ALERT_DIALOG, "alertdialog" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_INDEXER_COMPONENT, "alphabetindexer" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_BADGE_COMPONENT, "badge" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_BLANK, "blank" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_BUTTON, "button" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_BACK_BUTTON, "backbutton" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SHEET_DRAG_BAR, "sheetdragbar" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_CALENDAR_PICKER, "calendarpicker" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_CALENDAR, "calendar" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_CANVAS, "canvas" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_CANVAS_GRADIENT, "canvasgradient" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_CANVAS_PATTERN, "canvaspattern" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_CHECKBOX, "checkbox" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_CHECKBOX_GROUP, "checkboxgroup" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_CIRCLE, "circle" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_COLUMN_SPLIT, "columnsplit" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_COLUMN, "column" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_CANVAS_RENDERING_CONTEXT_2D, "canvasrenderingcontext2d" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_CHART, "chart" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_COUNTER, "counter" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_CONTAINER_MODAL, "containermodal" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_DATA_PANEL, "datapanel" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_DATE_PICKER, "datepicker" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_DIALOG, "dialog" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_DIVIDER, "divider" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_DRAG_BAR, "dragbar" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_EFFECT_COMPONENT, "effectcomponent" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_ELLIPSE, "ellipse" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_FLEX, "flex" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_FLOW_ITEM, "flowitem" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_FORM_COMPONENT, "formcomponent" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_FORM_LINK, "formlink" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_GAUGE, "gauge" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_GRID, "grid" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_GRID_COL, "gridcol" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_GRID_CONTAINER, "gridcontainer" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_GRID_ITEM, "griditem" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_GRID_ROW, "grid-row" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_HYPERLINK, "hyperlink" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_IMAGE, "image" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_IMAGE_ANIMATOR, "imageanimator" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_IMAGE_BITMAP, "imagebitmap" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_IMAGE_DATA, "imagedata" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_IMAGE_SPAN, "imagespan" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_LABEL, "label" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_LINE, "line" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_LIST, "list" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_LIST_ITEM, "listitem" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_LIST_ITEM_GROUP, "listitemgroup" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_LOADING_PROGRESS, "loadingprogress" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_MARQUEE, "marquee" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_MATRIX2D, "matrix2d" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_MENU, "menu" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_MENU_ITEM, "menuitem" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_MENU_ITEM_GROUP, "menuitemgroup" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_NAV_DESTINATION, "navdestination" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_NAV_ROUTER, "navrouter" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_NAVIGATION, "navigation" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_NAVIGATION_BAR, "navigation-bar" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_NAVIGATION_MENU, "navigation-menu" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_NAVIGATOR, "navigator" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_OFFSCREEN_CANVAS, "offscreencanvas" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_OFFSCREEN_CANVAS_RENDERING_CONTEXT2D, "offscreencanvasrenderingcontext2d" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_OPTION, "option" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_PANEL, "panel" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_PAPER_PAGE, "paperpage" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_PATH, "path" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_PATH2D, "path2d" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_PATTERN_LOCK, "patternlock" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_PICKER, "picker" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_PICKER_VIEW, "picker-view" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_PLUGIN_COMPONENT, "plugincomponent" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_POLYGON, "polygon" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_POLYLINE, "polyline" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_POPUP, "popup" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_PROGRESS, "progress" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_QRCODE, "qrcode" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_RADIO, "radio" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_RATING, "rating" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_RECT, "rect" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_REFRESH, "refresh" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_RELATIVE_CONTAINER, "relativecontainer" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_REMOTE_WINDOW, "remotewindow" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_RICH_EDITOR, "richeditor" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_RICH_TEXT, "richtext" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_ROLE_PAGER, "rolepager" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_ROW, "row" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_ROW_SPLIT, "rowsplit" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SCROLL, "scroll" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SCROLL_BAR, "scrollbar" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SEARCH, "search" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SEARCH_FIELD, "searchfield" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SELECT, "select" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SHAPE, "shape" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SIDEBAR_CONTAINER, "sidebarcontainer" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SLIDER, "slider" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SPAN, "span" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_STACK, "stack" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_STEPPER, "stepper" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_STEPPER_ITEM, "stepperitem" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SWIPER, "swiper" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SWIPER_INDICATOR, "swiperindicator" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SWITCH, "switch" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_SYMBOL_GLYPH, "symbolglyph" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TAB_CONTENT, "tabcontent" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TAB_BAR, "tab-bar" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TABS, "tabs" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TEXT, "text" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TEXT_CLOCK, "textclock" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TEXT_ENTRY, "textentry" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TEXT_INPUT, "textinput" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TEXT_PICKER, "textpicker" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TEXT_TIMER, "texttimer" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TEXT_AREA, "textarea" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TEXT_FIELD, "textfield" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TIME_PICKER, "timepicker" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TITLE_BAR, "titlebar" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_TOGGLER, "toggler" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_UI_EXTENSION_COMPONENT, "uiextensioncomponent" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_VIDEO, "video" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_WATER_FLOW, "waterflow" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_WEB, "web" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_XCOMPONENT, "xcomponent" },
    { ARK_ACCESSIBILITY_ROLE_TYPE_ROLE_NONE, "NULL" }
};

struct SetFocusData {
    std::optional<std::string> forward;
    std::optional<std::string> backward;
    std::optional<std::string> up;
    std::optional<std::string> down;
    std::optional<std::string> left;
    std::optional<std::string> right;
};
} // namespace

namespace Converter {

void AssignArkValue(Ark_FocusMovement& dst, const SetFocusData& src, ConvContext *ctx)
{
    dst.forward = Converter::ArkValue<Opt_String>(src.forward, ctx);
    dst.backward = Converter::ArkValue<Opt_String>(src.backward, ctx);
    dst.up = Converter::ArkValue<Opt_String>(src.up, ctx);
    dst.down = Converter::ArkValue<Opt_String>(src.down, ctx);
    dst.left = Converter::ArkValue<Opt_String>(src.left, ctx);
    dst.right = Converter::ArkValue<Opt_String>(src.right, ctx);
}

} // namespace Converter

namespace GeneratedModifier {
    const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor();
    const GENERATED_ArkUIKeyEventAccessor* GetKeyEventAccessor();
}

class CommonMethodModifierTest19 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<SheetTheme>();
    }
    void* CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }
};

/*
* @tc.name: TabStopTestDefaultValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, TabStopTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    const bool defaultValue = false;
    EXPECT_EQ(focusHub->IsTabStop(), defaultValue);
}

/*
* @tc.name: TabStopTestValidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, DISABLED_TabStopTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTabStop, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    using TestStep = std::tuple<Opt_Boolean, bool>;
    static const std::vector<TestStep> testPlan = {
        {Converter::ArkValue<Opt_Boolean>(false), false}, {Converter::ArkValue<Opt_Boolean>(true), true}};

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setTabStop(node_, &inputValue);
        EXPECT_EQ(focusHub->IsTabStop(), expectedValue);
    }
}

/*
* @tc.name: AccessibilityNextFocusIdTestDefaultValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, AccessibilityNextFocusIdTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    const std::string defaultValue = "";
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), defaultValue);
}

/*
* @tc.name: AccessibilityNextFocusIdTestValidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, DISABLED_AccessibilityNextFocusIdTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityNextFocusId, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    using TestStep = std::tuple<Opt_String, std::string>;
    static const std::vector<TestStep> testPlan = {
        {Converter::ArkValue<Opt_String>("id1"), "id1"}, {Converter::ArkValue<Opt_String>("id2"), "id2"}};

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityNextFocusId(node_, &inputValue);
        EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), expectedValue);
    }
}

/*
* @tc.name: AccessibilityDefaultFocusTestDefaultValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, DISABLED_AccessibilityDefaultFocusTestDefaultValues, TestSize.Level1)
{
    LOGE("AccessibilityManager::SendFrameNodeToAccessibility(...) is empty body");
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
}

/*
* @tc.name: AccessibilityDefaultFocusTestValidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, DISABLED_AccessibilityDefaultFocusTestValidValues, TestSize.Level1)
{
    LOGE("AccessibilityManager::SendFrameNodeToAccessibility(...) is empty body");
    ASSERT_NE(modifier_->setAccessibilityDefaultFocus, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    // test/mock/core/pipeline/mock_pipeline_context.cpp
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    ASSERT_NE(accessibilityManager, nullptr);

    auto isFocus = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setAccessibilityDefaultFocus(node_, &isFocus);
}

/*
* @tc.name: AccessibilityUseSamePageTestDefaultValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, AccessibilityUseSamePageTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const std::string defaultValue = "";
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->HasAccessibilitySamePage(), false);
    EXPECT_EQ(accessibilityProperty->GetAccessibilitySamePage(), defaultValue);
}

/*
* @tc.name: AccessibilityUseSamePageTestValidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, DISABLED_AccessibilityUseSamePageTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityUseSamePage, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    using TestStep = std::tuple<Opt_AccessibilitySamePageMode, std::string>;
    static const std::vector<TestStep> testPlan = {
        {Converter::ArkValue<Opt_AccessibilitySamePageMode>(ARK_ACCESSIBILITY_SAME_PAGE_MODE_FULL_SILENT),
            "FULL_SILENT"},
        {Converter::ArkValue<Opt_AccessibilitySamePageMode>(ARK_ACCESSIBILITY_SAME_PAGE_MODE_SEMI_SILENT),
            "SEMI_SILENT"}};

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityUseSamePage(node_, &inputValue);
        EXPECT_TRUE(accessibilityProperty->HasAccessibilitySamePage());
        EXPECT_EQ(accessibilityProperty->GetAccessibilitySamePage(), expectedValue);
    }
}

/*
* @tc.name: AccessibilityUseSamePageTestInvalidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, AccessibilityUseSamePageTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityUseSamePage, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto expectedValue = "";
    auto invalidValue = Converter::ArkValue<Opt_AccessibilitySamePageMode>(
        static_cast<Ark_AccessibilitySamePageMode>(-1));
    modifier_->setAccessibilityUseSamePage(node_, &invalidValue);
    EXPECT_FALSE(accessibilityProperty->HasAccessibilitySamePage());
    EXPECT_EQ(accessibilityProperty->GetAccessibilitySamePage(), expectedValue);
}

/*
* @tc.name: AccessibilityRoleTestDefaultValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, AccessibilityRoleTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const std::string defaultValue = "";
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->HasAccessibilityCustomRole(), false);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityCustomRole(), defaultValue);
}

/*
* @tc.name: AccessibilityRoleTestValidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, DISABLED_AccessibilityRoleTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityRole, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->HasAccessibilityCustomRole());
    Opt_AccessibilityRoleType optInputValue;
    for (auto [inputValue, expectedValue]: ACCESSIBILITY_ROLE_MAP) {
        optInputValue = Converter::ArkValue<Opt_AccessibilityRoleType>(inputValue);
        modifier_->setAccessibilityRole(node_, &optInputValue);
        EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
        EXPECT_EQ(accessibilityProperty->GetAccessibilityCustomRole(), expectedValue);
    }
}

/*
* @tc.name: AccessibilityRoleTestInvalidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, DISABLED_AccessibilityRoleTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityRole, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto expectedValue = "";
    auto invalidValue = Converter::ArkValue<Opt_AccessibilityRoleType>(static_cast<Ark_AccessibilityRoleType>(-1));

    EXPECT_FALSE(accessibilityProperty->HasAccessibilityCustomRole());
    modifier_->setAccessibilityRole(node_, &invalidValue);
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
    EXPECT_EQ(accessibilityProperty->GetAccessibilityCustomRole(), expectedValue);
}

/*
 * @tc.name: SetOnKeyEventDispatchTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, DISABLED_SetOnKeyEventDispatchTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnKeyEventDispatch, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    struct CheckEvent {
        int32_t resourceId = -1;
        KeyCode code = KeyCode::KEY_UNKNOWN;
    };
    static const int32_t expectedResId = 123;
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_KeyEvent parameter, const Callback_Boolean_Void continuation) {
        auto peer = parameter;
        ASSERT_NE(peer, nullptr);
        auto accessor = GeneratedModifier::GetKeyEventAccessor();
        auto info = peer->GetEventInfo();
        ASSERT_NE(info, nullptr);
        checkEvent = {
            .resourceId = resourceId,
            .code = info->GetKeyCode()
        };
        accessor->destroyPeer(peer);
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_Boolean>(true));
    };

    auto arkCallback = Converter::ArkValue<Callback_KeyEvent_Boolean>(nullptr, checkCallback, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_Callback_KeyEvent_Boolean>(arkCallback);
    modifier_->setOnKeyEventDispatch(node_, &optCallback);

    auto callOnKeyEvent = focusHub->GetOnKeyEventDispatchCallback();
    ASSERT_NE(callOnKeyEvent, nullptr);
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_FN;
    auto eventInfo = KeyEventInfo(keyEvent);
    EXPECT_FALSE(checkEvent.has_value());
    auto result = callOnKeyEvent(eventInfo);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, expectedResId);
    EXPECT_TRUE(result);
    EXPECT_EQ(checkEvent->code, keyEvent.code);
}

/*
* @tc.name: NextFocusTest
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, NextFocusTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setNextFocus, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    using TestStep = std::pair<SetFocusData, std::map<FocusIntension, std::string>>;
    static const std::vector<TestStep> testPlan = {
        { {"forward", "backward", "up", "down", "left", "right"},
            { {FocusIntension::TAB, "forward"},
                {FocusIntension::SHIFT_TAB, "backward"},
                {FocusIntension::UP, "up"},
                {FocusIntension::DOWN, "down"},
                {FocusIntension::LEFT, "left"},
                {FocusIntension::RIGHT, "right"} }
        },
        { {std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt},
        { {FocusIntension::TAB, ""},
            {FocusIntension::SHIFT_TAB, ""},
            {FocusIntension::UP, ""},
            {FocusIntension::DOWN, ""},
            {FocusIntension::LEFT, ""},
            {FocusIntension::RIGHT, ""} }
        },
        { {"forward", "backward", std::nullopt, std::nullopt, std::nullopt, std::nullopt},
        { {FocusIntension::TAB, "forward"},
            {FocusIntension::SHIFT_TAB, "backward"},
            {FocusIntension::UP, ""},
            {FocusIntension::DOWN, ""},
            {FocusIntension::LEFT, ""},
            {FocusIntension::RIGHT, ""} }
        },
        { {std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, "right"},
        { {FocusIntension::TAB, ""},
            {FocusIntension::SHIFT_TAB, ""},
            {FocusIntension::UP, ""},
            {FocusIntension::DOWN, ""},
            {FocusIntension::LEFT, ""},
            {FocusIntension::RIGHT, "right"} }
        },
     };

    for (auto [value, expectedMap]: testPlan) {
        auto inputValue = Converter::ArkValue<Opt_FocusMovement>(value, Converter::FC);
        modifier_->setNextFocus(node_, &inputValue);
        for (const auto& expectedValue : expectedMap) {
            EXPECT_EQ(std::get<std::string>(focusHub->GetNextFocus(static_cast<int32_t>(expectedValue.first))),
            expectedValue.second);
        }
    }
}

/*
 * @tc.name: bindMenu0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, DISABLED_bindMenu0Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindMenu0, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    Ark_MenuOptions arkOptions;
    Opt_MenuOptions optOptions;
    arkOptions.enableArrow = Converter::ArkValue<Opt_Boolean>(true);
    optOptions = Converter::ArkValue<Opt_MenuOptions>(arkOptions);
    int callsCount = 0;
    CustomNodeBuilderTestHelper<CommonMethodModifierTest19> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    auto unionCustomNodeBuilderValue = Converter::ArkUnion<Opt_Union_Array_MenuElement_CustomBuilder,
        CustomNodeBuilder>(builder);

    modifier_->setBindMenu0(node_, &unionCustomNodeBuilderValue, &optOptions);
    EXPECT_EQ(builderHelper.GetCallsCountAsync(), ++callsCount);
}

/*
 * @tc.name: bindMenu1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, DISABLED_bindMenu1Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindMenu1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    Ark_MenuOptions arkOptions;
    Opt_MenuOptions optOptions;
    arkOptions.enableArrow = Converter::ArkValue<Opt_Boolean>(true);
    optOptions = Converter::ArkValue<Opt_MenuOptions>(arkOptions);
    int callsCount = 0;
    CustomNodeBuilderTestHelper<CommonMethodModifierTest19> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    auto unionCustomNodeBuilderValue =
        Converter::ArkUnion<Opt_Union_Array_MenuElement_CustomBuilder, CustomNodeBuilder>(builder);

    auto show = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setBindMenu1(node_, &show, &unionCustomNodeBuilderValue, &optOptions);
    EXPECT_EQ(builderHelper.GetCallsCountAsync(), ++callsCount);
}

} // namespace OHOS::Ace::NG

