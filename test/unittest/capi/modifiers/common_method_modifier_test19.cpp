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
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const auto PROP_NAME_MASK = "mask";
const auto PROP_NAME_SHAPE = "shape";
const auto EMPTY_JSON = "{}";
const auto SHAPE_TYPE_RECT = "Rect";
const auto SHAPE_TYPE_ELLIPSE = "Ellipse";
const auto SHAPE_TYPE_CIRCLE = "Circle";
const auto SHAPE_TYPE_PATH = "Path";
const auto FOCUS_DRAW_LEVEL_TOP = 1;
const auto FOCUS_DRAW_LEVEL_SELF = 0;
const auto MIN_RATIO = 0.0f;
const auto MAX_RATIO = 1.0f;
const auto EXPECTED_RATIO = 0.7f;
const auto EXPECTED_PERIOD = 250;
const auto DEFAULT_PERIOD = 1000;
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
    RefPtr<MockRenderContext> GetMockRenderContext()
    {
        if (auto fnode = reinterpret_cast<FrameNode *>(node_); fnode) {
            return AceType::DynamicCast<MockRenderContext>(fnode->GetRenderContext());
        }
        return nullptr;
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
HWTEST_F(CommonMethodModifierTest19, TabStopTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTabStop, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    using TestStep = std::tuple<Ark_Boolean, bool>;
    static const std::vector<TestStep> testPlan = {
        {Converter::ArkValue<Ark_Boolean>(false), false}, {Converter::ArkValue<Ark_Boolean>(true), true}};

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setTabStop(node_, inputValue);
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
HWTEST_F(CommonMethodModifierTest19, AccessibilityNextFocusIdTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityNextFocusId, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    using TestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<TestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("id1"), "id1"}, {Converter::ArkValue<Ark_String>("id2"), "id2"}};

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

    bool isFocus = true;
    modifier_->setAccessibilityDefaultFocus(node_, isFocus);
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
HWTEST_F(CommonMethodModifierTest19, AccessibilityUseSamePageTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityUseSamePage, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    using TestStep = std::tuple<Ark_AccessibilitySamePageMode, std::string>;
    static const std::vector<TestStep> testPlan = {
        {ARK_ACCESSIBILITY_SAME_PAGE_MODE_FULL_SILENT, "fullsilent"},
        {ARK_ACCESSIBILITY_SAME_PAGE_MODE_SEMI_SILENT, "semisilent"}};

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityUseSamePage(node_, inputValue);
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
    auto invalidValue = static_cast<Ark_AccessibilitySamePageMode>(-1);

    modifier_->setAccessibilityUseSamePage(node_, invalidValue);
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
HWTEST_F(CommonMethodModifierTest19, AccessibilityRoleTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityRole, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->HasAccessibilityCustomRole());

    for (auto [inputValue, expectedValue]: ACCESSIBILITY_ROLE_MAP) {
        modifier_->setAccessibilityRole(node_, inputValue);
        EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
        EXPECT_EQ(accessibilityProperty->GetAccessibilityCustomRole(), expectedValue);
    }
}

/*
* @tc.name: AccessibilityRoleTestInvalidValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(CommonMethodModifierTest19, AccessibilityRoleTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityRole, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto expectedValue = "";
    auto invalidValue = static_cast<Ark_AccessibilityRoleType>(-1);

    EXPECT_FALSE(accessibilityProperty->HasAccessibilityCustomRole());
    modifier_->setAccessibilityRole(node_, invalidValue);
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
    EXPECT_EQ(accessibilityProperty->GetAccessibilityCustomRole(), expectedValue);
}

/*
 * @tc.name: SetOnKeyEventDispatchTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, SetOnKeyEventDispatchTest, TestSize.Level1)
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
    modifier_->setOnKeyEventDispatch(node_, &arkCallback);

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
 * @tc.name: SetOnHoverMoveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, SetOnHoverMoveTest, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setOnHoverMove);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    static const std::string expectedType = "onHover";
    static const int expectedResId = 123;

    struct CheckEvent {
        int32_t nodeId;
        SourceType deviceType;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onHoverMoveFunc = [](Ark_VMContext, const Ark_Int32 resourceId,
            const Ark_HoverEvent peer) {
        ASSERT_NE(peer, nullptr);
        auto hoverEventInfo = peer->GetEventInfo();
        ASSERT_NE(hoverEventInfo, nullptr);
        EXPECT_EQ(hoverEventInfo->GetType(), expectedType);
        checkEvent = {
            .nodeId = resourceId,
            .deviceType = hoverEventInfo->GetSourceDevice()
        };
    };

    auto callbackValue =
        Converter::ArkValue<Callback_HoverEvent_Void>(onHoverMoveFunc, expectedResId);

    auto test = [this, &callbackValue, eventHub, frameNode](SourceType type) {
        checkEvent = std::nullopt;
        modifier_->setOnHoverMove(node_, &callbackValue);
        ASSERT_FALSE(checkEvent.has_value());
        auto inputEventHub = eventHub->GetInputEventHub();
        ASSERT_NE(inputEventHub, nullptr);

        OffsetF offset;
        TouchTestResult result;
        inputEventHub->ProcessPenHoverTestHit(offset, result);
        for (const auto& resultData : result) {
            auto hoverResult = AceType::DynamicCast<HoverEventTarget>(resultData);
            ASSERT_NE(hoverResult, nullptr);
            TouchEvent touchEvent;
            touchEvent.sourceType = type;
            hoverResult->HandlePenHoverMoveEvent(touchEvent);
        }
        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, expectedResId);
        EXPECT_EQ(checkEvent->deviceType, type);
    };
    test(SourceType::MOUSE);
    test(SourceType::JOYSTICK);
}

/*
 * @tc.name: setOnAxisEventTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setOnAxisEventTest, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setOnAxisEvent);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    AxisInfo eventInfo;
    static const std::string expectedType = "onAxis";
    static const int expectedResId = 123;

    struct CheckEvent {
        int32_t nodeId;
        AxisAction action;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onAxisCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_AxisEvent peer) {
        ASSERT_TRUE(peer);
        auto eventInfo =  peer->GetEventInfo();
        ASSERT_TRUE(eventInfo);
        EXPECT_EQ(eventInfo->GetType(), expectedType);
        checkEvent = {
            .nodeId = resourceId,
            .action = eventInfo->GetAction()
        };
    };

    auto callback =  Converter::ArkValue<Callback_AxisEvent_Void>(onAxisCallback, expectedResId);
    modifier_->setOnAxisEvent(node_, &callback);
    ASSERT_FALSE(checkEvent.has_value());
    auto inputEventHub = eventHub->GetInputEventHub();
    ASSERT_NE(inputEventHub, nullptr);
    OffsetF offset;
    AxisTestResult result;
    inputEventHub->ProcessAxisTestHit(offset, result);

    for (const auto& resultData : result) {
        auto axisResult = AceType::DynamicCast<AxisEventTarget>(resultData);
        ASSERT_NE(axisResult, nullptr);
        AxisEvent axisEvent;
        axisEvent.action = AxisAction::UPDATE;
        axisResult->HandleAxisEvent(axisEvent);
    }
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, expectedResId);
    EXPECT_EQ(checkEvent->action, AxisAction::UPDATE);
}

/*
 * @tc.name: setBackgroundBlurStyle1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setBackgroundBlurStyle1TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBackgroundBlurStyle1, nullptr);

    const BlurStyleOption expected {
        .blurStyle = BlurStyle::BACKGROUND_REGULAR,
        .colorMode = ThemeColorMode::DARK,
        .scale = 0.123,
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .blurOption = {.grayscale = {20, 30}},
        .policy = BlurStyleActivePolicy::ALWAYS_ACTIVE,
        .blurType = BlurType::WITHIN_WINDOW,
        .inactiveColor = Color(0xFF00FFFF),
    };
    auto styleValid = ARK_BLUR_STYLE_BACKGROUND_REGULAR;
    auto inputStyleValid = Converter::ArkValue<Opt_BlurStyle>(styleValid);
    auto inputOptionValid = Converter::ArkValue<Opt_BackgroundBlurStyleOptions>(
        Ark_BackgroundBlurStyleOptions {
            .colorMode  = Converter::ArkValue<Opt_ThemeColorMode>(ARK_THEME_COLOR_MODE_DARK),
            .adaptiveColor = Converter::ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
            .scale = Converter::ArkValue<Opt_Number>(0.123f),
            .blurOptions = Converter::ArkValue<Opt_BlurOptions>(Ark_BlurOptions{
                .grayscale = {Converter::ArkValue<Ark_Number>(20), Converter::ArkValue<Ark_Number>(30)}
            }),
            .policy =
                Converter::ArkValue<Opt_BlurStyleActivePolicy>(ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE),
            .inactiveColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>("65535"),
        }
    );
    modifier_->setBackgroundBlurStyle1(node_, &inputStyleValid, &inputOptionValid);

    auto renderMock = GetMockRenderContext();
    ASSERT_NE(renderMock, nullptr);
    ASSERT_TRUE(renderMock->GetBackBlurStyle().has_value());
    EXPECT_EQ(renderMock->GetBackBlurStyle().value(), expected);
}

/*
 * @tc.name: setBackgroundBlurStyleTest1InvalidValues1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setBackgroundBlurStyle1TestInvalidValues1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBackgroundBlurStyle1, nullptr);
    const BlurStyleOption expected;
    modifier_->setBackgroundBlurStyle1(node_, nullptr, nullptr);
    auto renderMock = GetMockRenderContext();
    ASSERT_NE(renderMock, nullptr);
    ASSERT_TRUE(renderMock->GetBackBlurStyle().has_value());
    EXPECT_EQ(renderMock->GetBackBlurStyle().value(), expected);
}

/*
 * @tc.name: setBackgroundBlurStyleTest1InvalidValues2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setBackgroundBlurStyle1TestInvalidValues2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBackgroundBlurStyle1, nullptr);
    const BlurStyleOption expected {
        .blurStyle = BlurStyle::BACKGROUND_REGULAR,
    };
    auto styleValid = ARK_BLUR_STYLE_BACKGROUND_REGULAR;
    auto inputStyleValid = Converter::ArkValue<Opt_BlurStyle>(styleValid);
    modifier_->setBackgroundBlurStyle1(node_, &inputStyleValid, nullptr);
    auto renderMock = GetMockRenderContext();
    ASSERT_NE(renderMock, nullptr);
    ASSERT_TRUE(renderMock->GetBackBlurStyle().has_value());
    EXPECT_EQ(renderMock->GetBackBlurStyle().value(), expected);
}

/*
 * @tc.name: setBackgroundBlurStyleTest1InvalidValues3
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setBackgroundBlurStyle1TestInvalidValues3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBackgroundBlurStyle1, nullptr);
    const BlurStyleOption expected {
        .colorMode = ThemeColorMode::DARK,
        .scale = 0.123,
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .blurOption = {.grayscale = {20, 30}},
        .policy = BlurStyleActivePolicy::ALWAYS_ACTIVE,
        .blurType = BlurType::WITHIN_WINDOW,
        .inactiveColor = Color(0xFF00FFFF),
    };
    auto inputOptionValid = Converter::ArkValue<Opt_BackgroundBlurStyleOptions>(
        Ark_BackgroundBlurStyleOptions {
            .colorMode  = Converter::ArkValue<Opt_ThemeColorMode>(ARK_THEME_COLOR_MODE_DARK),
            .adaptiveColor = Converter::ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
            .scale = Converter::ArkValue<Opt_Number>(0.123f),
            .blurOptions = Converter::ArkValue<Opt_BlurOptions>(Ark_BlurOptions{
                .grayscale = {Converter::ArkValue<Ark_Number>(20), Converter::ArkValue<Ark_Number>(30)}
            }),
            .policy =
                Converter::ArkValue<Opt_BlurStyleActivePolicy>(ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE),
            .inactiveColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>("65535"),
        }
    );
    modifier_->setBackgroundBlurStyle1(node_, nullptr, &inputOptionValid);
    auto renderMock = GetMockRenderContext();
    ASSERT_NE(renderMock, nullptr);
    ASSERT_TRUE(renderMock->GetBackBlurStyle().has_value());
    EXPECT_EQ(renderMock->GetBackBlurStyle().value(), expected);
}

/*
 * @tc.name: setBackgroundBlurStyleTest1InvalidValues4
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setBackgroundBlurStyle1TestInvalidValues4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBackgroundBlurStyle1, nullptr);
    const BlurStyleOption expected;
    auto inputStyleInvalid = Converter::ArkValue<Opt_BlurStyle>();
    auto inputOptionInvalid = Converter::ArkValue<Opt_BackgroundBlurStyleOptions>();
    modifier_->setBackgroundBlurStyle1(node_, &inputStyleInvalid, &inputOptionInvalid);
    auto renderMock = GetMockRenderContext();
    ASSERT_NE(renderMock, nullptr);
    ASSERT_TRUE(renderMock->GetBackBlurStyle().has_value());
    EXPECT_EQ(renderMock->GetBackBlurStyle().value(), expected);
}

/*
 * @tc.name: setBackgroundBlurStyleTest1InvalidValues5
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setBackgroundBlurStyle1TestInvalidValues5, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBackgroundBlurStyle1, nullptr);
    const BlurStyleOption expected {
        .blurStyle = BlurStyle::BACKGROUND_REGULAR,
    };
    auto styleValid = ARK_BLUR_STYLE_BACKGROUND_REGULAR;
    auto inputStyleValid = Converter::ArkValue<Opt_BlurStyle>(styleValid);
    auto inputOptionInvalid = Converter::ArkValue<Opt_BackgroundBlurStyleOptions>();
    modifier_->setBackgroundBlurStyle1(node_, &inputStyleValid, &inputOptionInvalid);
    auto renderMock = GetMockRenderContext();
    ASSERT_NE(renderMock, nullptr);
    ASSERT_TRUE(renderMock->GetBackBlurStyle().has_value());
    EXPECT_EQ(renderMock->GetBackBlurStyle().value(), expected);
}

/*
 * @tc.name: setBackgroundBlurStyleTest1InvalidValues6
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setBackgroundBlurStyle1TestInvalidValues6, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBackgroundBlurStyle1, nullptr);
    const BlurStyleOption expected {
        .colorMode = ThemeColorMode::DARK,
        .scale = 0.123,
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .blurOption = {.grayscale = {20, 30}},
        .policy = BlurStyleActivePolicy::ALWAYS_ACTIVE,
        .blurType = BlurType::WITHIN_WINDOW,
        .inactiveColor = Color(0xFF00FFFF),
    };
    auto inputOptionValid = Converter::ArkValue<Opt_BackgroundBlurStyleOptions>(
        Ark_BackgroundBlurStyleOptions {
            .colorMode  = Converter::ArkValue<Opt_ThemeColorMode>(ARK_THEME_COLOR_MODE_DARK),
            .adaptiveColor = Converter::ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
            .scale = Converter::ArkValue<Opt_Number>(0.123f),
            .blurOptions = Converter::ArkValue<Opt_BlurOptions>(Ark_BlurOptions{
                .grayscale = {Converter::ArkValue<Ark_Number>(20), Converter::ArkValue<Ark_Number>(30)}
            }),
            .policy =
                Converter::ArkValue<Opt_BlurStyleActivePolicy>(ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE),
            .inactiveColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>("65535"),
        }
    );
    auto inputStyleInvalid = Converter::ArkValue<Opt_BlurStyle>();
    modifier_->setBackgroundBlurStyle1(node_, &inputStyleInvalid, &inputOptionValid);
    auto renderMock = GetMockRenderContext();
    ASSERT_NE(renderMock, nullptr);
    ASSERT_TRUE(renderMock->GetBackBlurStyle().has_value());
    EXPECT_EQ(renderMock->GetBackBlurStyle().value(), expected);
}

/*
 * @tc.name: setMaskShape1TestValidValues1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setMaskShape1TestValidValues1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaskShape1, nullptr);
    Ark_RectShape peer = PeerUtils::CreatePeer<RectShapePeer>();
    ASSERT_NE(peer, nullptr);
    peer->shape = Referenced::MakeRefPtr<ShapeRect>();
    auto maskShape = Converter::ArkUnion<Ark_Union_CircleShape_EllipseShape_PathShape_RectShape, Ark_RectShape>(peer);
    auto optMaskShape = Converter::ArkValue<Opt_Union_CircleShape_EllipseShape_PathShape_RectShape>(maskShape);
    modifier_->setMaskShape1(node_, &optMaskShape);
    auto jsonValue = GetJsonValue(node_);
    auto maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    auto shapeType = GetAttrValue<std::string>(maskObject, PROP_NAME_SHAPE);
    EXPECT_EQ(shapeType, SHAPE_TYPE_RECT);
    PeerUtils::DestroyPeer(peer);
}

/*
 * @tc.name: setMaskShape1TestValidValues2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setMaskShape1TestValidValues2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaskShape1, nullptr);
    Ark_EllipseShape peer = PeerUtils::CreatePeer<EllipseShapePeer>();
    ASSERT_NE(peer, nullptr);
    peer->shape = Referenced::MakeRefPtr<Ellipse>();
    auto maskShape =
        Converter::ArkUnion<Ark_Union_CircleShape_EllipseShape_PathShape_RectShape, Ark_EllipseShape>(peer);
    auto optMaskShape = Converter::ArkValue<Opt_Union_CircleShape_EllipseShape_PathShape_RectShape>(maskShape);
    modifier_->setMaskShape1(node_, &optMaskShape);
    auto jsonValue = GetJsonValue(node_);
    auto maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    auto shapeType = GetAttrValue<std::string>(maskObject, PROP_NAME_SHAPE);
    EXPECT_EQ(shapeType, SHAPE_TYPE_ELLIPSE);
    PeerUtils::DestroyPeer(peer);
}

/*
 * @tc.name: setMaskShape1TestValidValues3
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setMaskShape1TestValidValues3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaskShape1, nullptr);
    Ark_CircleShape peer = PeerUtils::CreatePeer<CircleShapePeer>();
    ASSERT_NE(peer, nullptr);
    peer->shape = Referenced::MakeRefPtr<Circle>();
    auto maskShape =
        Converter::ArkUnion<Ark_Union_CircleShape_EllipseShape_PathShape_RectShape, Ark_CircleShape>(peer);
    auto optMaskShape = Converter::ArkValue<Opt_Union_CircleShape_EllipseShape_PathShape_RectShape>(maskShape);
    modifier_->setMaskShape1(node_, &optMaskShape);
    auto jsonValue = GetJsonValue(node_);
    auto maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    auto shapeType = GetAttrValue<std::string>(maskObject, PROP_NAME_SHAPE);
    EXPECT_EQ(shapeType, SHAPE_TYPE_CIRCLE);
    PeerUtils::DestroyPeer(peer);
}

/*
 * @tc.name: setMaskShape1TestValidValues4
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setMaskShape1TestValidValues4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaskShape1, nullptr);
    Ark_PathShape peer = PeerUtils::CreatePeer<PathShapePeer>();
    ASSERT_NE(peer, nullptr);
    peer->shape = Referenced::MakeRefPtr<Path>();
    auto maskShape =
        Converter::ArkUnion<Ark_Union_CircleShape_EllipseShape_PathShape_RectShape, Ark_PathShape>(peer);
    auto optMaskShape = Converter::ArkValue<Opt_Union_CircleShape_EllipseShape_PathShape_RectShape>(maskShape);
    modifier_->setMaskShape1(node_, &optMaskShape);
    auto jsonValue = GetJsonValue(node_);
    auto maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    auto shapeType = GetAttrValue<std::string>(maskObject, PROP_NAME_SHAPE);
    EXPECT_EQ(shapeType, SHAPE_TYPE_PATH);
    PeerUtils::DestroyPeer(peer);
}

/*
 * @tc.name: setMaskShape1TestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setMaskShape1TestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaskShape1, nullptr);
    auto optMaskShape = Converter::ArkValue<Opt_Union_CircleShape_EllipseShape_PathShape_RectShape>();
    modifier_->setMaskShape1(node_, &optMaskShape);
    auto jsonValue = GetJsonValue(node_);
    auto maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    EXPECT_EQ(maskObject->ToString(), EMPTY_JSON);

    modifier_->setMaskShape1(node_, nullptr);
    jsonValue = GetJsonValue(node_);
    maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    EXPECT_EQ(maskObject->ToString(), EMPTY_JSON);

    Ark_PathShape peer = PeerUtils::CreatePeer<PathShapePeer>();
    ASSERT_NE(peer, nullptr);
    peer->shape = Referenced::MakeRefPtr<Path>();
    auto maskShape = Converter::ArkUnion<Ark_Union_CircleShape_EllipseShape_PathShape_RectShape, Ark_PathShape>(peer);
    optMaskShape = Converter::ArkValue<Opt_Union_CircleShape_EllipseShape_PathShape_RectShape>(maskShape);
    modifier_->setMaskShape1(nullptr, &optMaskShape);
    jsonValue = GetJsonValue(node_);
    maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    EXPECT_EQ(maskObject->ToString(), EMPTY_JSON);

    modifier_->setMaskShape1(nullptr, nullptr);
    jsonValue = GetJsonValue(node_);
    maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    EXPECT_EQ(maskObject->ToString(), EMPTY_JSON);
}

/*
 * @tc.name: setMaskShapeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setMaskShapeTestDefaultValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaskShape1, nullptr);
    auto jsonValue = GetJsonValue(node_);
    auto maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    EXPECT_EQ(maskObject->ToString(), EMPTY_JSON);
}

/*
 * @tc.name: setMaskShape0TestValidValues1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setMaskShape0TestValidValues1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaskShape1, nullptr);
    Ark_RectShape peer = PeerUtils::CreatePeer<RectShapePeer>();
    ASSERT_NE(peer, nullptr);
    peer->shape = Referenced::MakeRefPtr<ShapeRect>();
    auto maskShape = Converter::ArkUnion<Ark_Union_CircleShape_EllipseShape_PathShape_RectShape, Ark_RectShape>(peer);
    modifier_->setMaskShape0(node_, &maskShape);
    auto jsonValue = GetJsonValue(node_);
    auto maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    auto shapeType = GetAttrValue<std::string>(maskObject, PROP_NAME_SHAPE);
    EXPECT_EQ(shapeType, SHAPE_TYPE_RECT);
    PeerUtils::DestroyPeer(peer);
}

/*
 * @tc.name: setMaskShape0TestValidValues2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setMaskShape0TestValidValues2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaskShape1, nullptr);
    Ark_EllipseShape peer = PeerUtils::CreatePeer<EllipseShapePeer>();
    ASSERT_NE(peer, nullptr);
    peer->shape = Referenced::MakeRefPtr<Ellipse>();
    auto maskShape =
        Converter::ArkUnion<Ark_Union_CircleShape_EllipseShape_PathShape_RectShape, Ark_EllipseShape>(peer);
    modifier_->setMaskShape0(node_, &maskShape);
    auto jsonValue = GetJsonValue(node_);
    auto maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    auto shapeType = GetAttrValue<std::string>(maskObject, PROP_NAME_SHAPE);
    EXPECT_EQ(shapeType, SHAPE_TYPE_ELLIPSE);
    PeerUtils::DestroyPeer(peer);
}

/*
 * @tc.name: setMaskShape0TestValidValues3
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setMaskShape0TestValidValues3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaskShape1, nullptr);
    Ark_CircleShape peer = PeerUtils::CreatePeer<CircleShapePeer>();
    ASSERT_NE(peer, nullptr);
    peer->shape = Referenced::MakeRefPtr<Circle>();
    auto maskShape =
        Converter::ArkUnion<Ark_Union_CircleShape_EllipseShape_PathShape_RectShape, Ark_CircleShape>(peer);
    modifier_->setMaskShape0(node_, &maskShape);
    auto jsonValue = GetJsonValue(node_);
    auto maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    auto shapeType = GetAttrValue<std::string>(maskObject, PROP_NAME_SHAPE);
    EXPECT_EQ(shapeType, SHAPE_TYPE_CIRCLE);
    PeerUtils::DestroyPeer(peer);
}

/*
 * @tc.name: setMaskShape0TestValidValues4
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setMaskShape0TestValidValues4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaskShape1, nullptr);
    Ark_PathShape peer = PeerUtils::CreatePeer<PathShapePeer>();
    ASSERT_NE(peer, nullptr);
    peer->shape = Referenced::MakeRefPtr<Path>();
    auto maskShape =
        Converter::ArkUnion<Ark_Union_CircleShape_EllipseShape_PathShape_RectShape, Ark_PathShape>(peer);
    modifier_->setMaskShape0(node_, &maskShape);
    auto jsonValue = GetJsonValue(node_);
    auto maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    auto shapeType = GetAttrValue<std::string>(maskObject, PROP_NAME_SHAPE);
    EXPECT_EQ(shapeType, SHAPE_TYPE_PATH);
    PeerUtils::DestroyPeer(peer);
}

/*
 * @tc.name: setMaskShape0TestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setMaskShape0TestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaskShape1, nullptr);

    modifier_->setMaskShape0(node_, nullptr);
    auto jsonValue = GetJsonValue(node_);
    auto maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    EXPECT_EQ(maskObject->ToString(), EMPTY_JSON);

    Ark_PathShape peer = PeerUtils::CreatePeer<PathShapePeer>();
    ASSERT_NE(peer, nullptr);
    peer->shape = Referenced::MakeRefPtr<Path>();
    auto maskShape = Converter::ArkUnion<Ark_Union_CircleShape_EllipseShape_PathShape_RectShape, Ark_PathShape>(peer);
    modifier_->setMaskShape0(nullptr, &maskShape);
    jsonValue = GetJsonValue(node_);
    maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    EXPECT_EQ(maskObject->ToString(), EMPTY_JSON);
    PeerUtils::DestroyPeer(peer);

    modifier_->setMaskShape0(nullptr, nullptr);
    jsonValue = GetJsonValue(node_);
    maskObject = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME_MASK);
    EXPECT_EQ(maskObject->ToString(), EMPTY_JSON);
}

/*
 * @tc.name: setAccessibilityScrollTriggerableTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setAccessibilityScrollTriggerableTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityScrollTriggerable, nullptr);
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->HasUserScrollTriggerable());
    EXPECT_TRUE(accessibilityProperty->IsUserScrollTriggerable());
    modifier_->setAccessibilityScrollTriggerable(node_, Converter::ArkValue<Ark_Boolean>(false));
    EXPECT_FALSE(accessibilityProperty->IsUserScrollTriggerable());
    modifier_->setAccessibilityScrollTriggerable(node_, Converter::ArkValue<Ark_Boolean>(true));
    EXPECT_TRUE(accessibilityProperty->IsUserScrollTriggerable());
}

/*
 * @tc.name: setAccessibilityFocusDrawLevelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setAccessibilityFocusDrawLevelTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityFocusDrawLevel, nullptr);
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetFocusDrawLevel(), FOCUS_DRAW_LEVEL_SELF);
    modifier_->setAccessibilityFocusDrawLevel(node_, ARK_FOCUS_DRAW_LEVEL_TOP);
    EXPECT_EQ(accessibilityProperty->GetFocusDrawLevel(), FOCUS_DRAW_LEVEL_TOP);
    modifier_->setAccessibilityFocusDrawLevel(node_, ARK_FOCUS_DRAW_LEVEL_SELF);
    EXPECT_EQ(accessibilityProperty->GetFocusDrawLevel(), FOCUS_DRAW_LEVEL_SELF);
}

/*
 * @tc.name: setOnVisibleAreaApproximateChangeTest1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setOnVisibleAreaApproximateChangeTest1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnVisibleAreaApproximateChange, nullptr);
    struct CheckEvent {
        int32_t nodeId;
        bool isExpanding;
        float currentRatio;
    };
    static std::vector<CheckEvent> checkEvent;
    void (*checkCallback)(const Ark_Int32, const Ark_Boolean, const Ark_Number) =
        [](const Ark_Int32 resourceId, const Ark_Boolean isExpanding, const Ark_Number currentRatio) {
            checkEvent.push_back({
                .nodeId = resourceId,
                .isExpanding = Converter::Convert<bool>(isExpanding),
                .currentRatio = Converter::Convert<float>(currentRatio)
            });
        };
    const int32_t contextId = 123;
    auto arkfunc = Converter::ArkValue<VisibleAreaChangeCallback>(checkCallback, contextId);
    auto func = Converter::ArkValue<Opt_VisibleAreaChangeCallback>(arkfunc);

    std::vector<float> ratioVec;
    ratioVec.push_back(0.5f);
    ratioVec.push_back(-0.5f);
    ratioVec.push_back(1.5f);
    Converter::ArkArrayHolder<Array_Number> vecHolder(ratioVec);
    Ark_VisibleAreaEventOptions option;
    option.ratios = vecHolder.ArkValue();
    option.expectedUpdateInterval = Converter::ArkValue<Opt_Number>(EXPECTED_PERIOD);

    EXPECT_EQ(checkEvent.size(), 0);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    auto cbInfoIni = eventHub->GetThrottledVisibleAreaCallback();
    EXPECT_EQ(cbInfoIni.callback, nullptr);
    modifier_->setOnVisibleAreaApproximateChange(node_, &option, &func);
    auto cbInfo = eventHub->GetThrottledVisibleAreaCallback();
    EXPECT_EQ(static_cast<int32_t>(cbInfo.period), EXPECTED_PERIOD);
    ASSERT_NE(cbInfo.callback, nullptr);
    cbInfo.callback(false, EXPECTED_RATIO);
    EXPECT_EQ(checkEvent.size(), 1);
    EXPECT_EQ(checkEvent[0].nodeId, contextId);
    EXPECT_EQ(checkEvent[0].isExpanding, false);
    EXPECT_EQ(checkEvent[0].currentRatio, EXPECTED_RATIO);
    auto ratios = eventHub->GetThrottledVisibleAreaRatios();
    EXPECT_EQ(ratios.size(), ratioVec.size());
    EXPECT_EQ(ratios[0], ratioVec[0]);
    EXPECT_EQ(ratios[1], MIN_RATIO);
    EXPECT_EQ(ratios[2], MAX_RATIO);
}

/*
 * @tc.name: setOnVisibleAreaApproximateChangeTest2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest19, setOnVisibleAreaApproximateChangeTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnVisibleAreaApproximateChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    auto func = Converter::ArkValue<Opt_VisibleAreaChangeCallback>();
    std::vector<float> ratioVec;
    ratioVec.push_back(0.5f);
    Converter::ArkArrayHolder<Array_Number> vecHolder(ratioVec);
    Ark_VisibleAreaEventOptions option;
    option.ratios = vecHolder.ArkValue();
    option.expectedUpdateInterval = Converter::ArkValue<Opt_Number>();
    auto cbInfoIni = eventHub->GetThrottledVisibleAreaCallback();
    EXPECT_EQ(cbInfoIni.callback, nullptr);
    EXPECT_EQ(static_cast<int32_t>(cbInfoIni.period), 0);
    modifier_->setOnVisibleAreaApproximateChange(node_, &option, &func);
    auto cbInfo = eventHub->GetThrottledVisibleAreaCallback();
    EXPECT_EQ(cbInfo.callback, nullptr);
    EXPECT_EQ(static_cast<int32_t>(cbInfo.period), 0);

    void (*emptyCallback)(const Ark_Int32, const Ark_Boolean, const Ark_Number) =
    [](const Ark_Int32 resourceId, const Ark_Boolean isExpanding, const Ark_Number currentRatio) {
    };
    const int32_t contextId = 123;
    auto arkEmptyfunc = Converter::ArkValue<VisibleAreaChangeCallback>(emptyCallback, contextId);
    auto emptyFunc = Converter::ArkValue<Opt_VisibleAreaChangeCallback>(arkEmptyfunc);
    modifier_->setOnVisibleAreaApproximateChange(node_, &option, &emptyFunc);
    auto cbInfo2 = eventHub->GetThrottledVisibleAreaCallback();
    EXPECT_NE(cbInfo2.callback, nullptr);
    EXPECT_EQ(static_cast<int32_t>(cbInfo2.period), DEFAULT_PERIOD);
}

} // namespace OHOS::Ace::NG