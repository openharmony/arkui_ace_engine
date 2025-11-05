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
#include "core/accessibility/static/accessibility_static_utils.h"

#include <unordered_map>
#include <vector>

#include "ui/focus/focus_constants.h"

namespace OHOS::Ace {
const std::unordered_map<AccessibilityRoleType, std::string> accessibilityRoleMap {
    { AccessibilityRoleType::ACTION_SHEET, "actionsheet" }, { AccessibilityRoleType::ALERT_DIALOG, "alertdialog" },
    { AccessibilityRoleType::INDEXER_COMPONENT, "alphabetindexer" },
    { AccessibilityRoleType::BADGE_COMPONENT, "badge" }, { AccessibilityRoleType::BLANK, "blank" },
    { AccessibilityRoleType::BUTTON, "button" }, { AccessibilityRoleType::BACK_BUTTON, "backbutton" },
    { AccessibilityRoleType::SHEET_DRAG_BAR, "sheetdragbar" },
    { AccessibilityRoleType::CALENDAR_PICKER, "calendarpicker" }, { AccessibilityRoleType::CALENDAR, "calendar" },
    { AccessibilityRoleType::CANVAS, "canvas" }, { AccessibilityRoleType::CANVAS_GRADIENT, "canvasgradient" },
    { AccessibilityRoleType::CANVAS_PATTERN, "canvaspattern" }, { AccessibilityRoleType::CHECKBOX, "checkbox" },
    { AccessibilityRoleType::CHECKBOX_GROUP, "checkboxgroup" }, { AccessibilityRoleType::CIRCLE, "circle" },
    { AccessibilityRoleType::COLUMN_SPLIT, "columnsplit" }, { AccessibilityRoleType::COLUMN, "column" },
    { AccessibilityRoleType::CANVAS_RENDERING_CONTEXT_2D, "canvasrenderingcontext2d" },
    { AccessibilityRoleType::CHART, "chart" }, { AccessibilityRoleType::COUNTER, "counter" },
    { AccessibilityRoleType::CONTAINER_MODAL, "containermodal" }, { AccessibilityRoleType::DATA_PANEL, "datapanel" },
    { AccessibilityRoleType::DATE_PICKER, "datepicker" }, { AccessibilityRoleType::DIALOG, "dialog" },
    { AccessibilityRoleType::DIVIDER, "divider" }, { AccessibilityRoleType::DRAG_BAR, "dragbar" },
    { AccessibilityRoleType::EFFECT_COMPONENT, "effectcomponent" }, { AccessibilityRoleType::ELLIPSE, "ellipse" },
    { AccessibilityRoleType::FLEX, "flex" }, { AccessibilityRoleType::FLOW_ITEM, "flowitem" },
    { AccessibilityRoleType::FORM_COMPONENT, "formcomponent" }, { AccessibilityRoleType::FORM_LINK, "formlink" },
    { AccessibilityRoleType::GAUGE, "gauge" }, { AccessibilityRoleType::GRID, "grid" },
    { AccessibilityRoleType::GRID_COL, "gridcol" }, { AccessibilityRoleType::GRID_CONTAINER, "gridcontainer" },
    { AccessibilityRoleType::GRID_ITEM, "griditem" }, { AccessibilityRoleType::GRID_ROW, "grid-row" },
    { AccessibilityRoleType::HYPERLINK, "hyperlink" }, { AccessibilityRoleType::IMAGE, "image" },
    { AccessibilityRoleType::IMAGE_ANIMATOR, "imageanimator" },
    { AccessibilityRoleType::ROLE_IMAGE_BITMAP, "imagebitmap" }, { AccessibilityRoleType::IMAGE_DATA, "imagedata" },
    { AccessibilityRoleType::IMAGE_SPAN, "imagespan" }, { AccessibilityRoleType::LABEL, "label" },
    { AccessibilityRoleType::LINE, "line" }, { AccessibilityRoleType::LIST, "list" },
    { AccessibilityRoleType::LIST_ITEM, "listitem" }, { AccessibilityRoleType::LIST_ITEM_GROUP, "listitemgroup" },
    { AccessibilityRoleType::LOADING_PROGRESS, "loadingprogress" }, { AccessibilityRoleType::MARQUEE, "marquee" },
    { AccessibilityRoleType::MATRIX2D, "matrix2d" }, { AccessibilityRoleType::MENU, "menu" },
    { AccessibilityRoleType::MENU_ITEM, "menuitem" }, { AccessibilityRoleType::MENU_ITEM_GROUP, "menuitemgroup" },
    { AccessibilityRoleType::NAV_DESTINATION, "navdestination" }, { AccessibilityRoleType::NAV_ROUTER, "navrouter" },
    { AccessibilityRoleType::NAVIGATION, "navigation" }, { AccessibilityRoleType::NAVIGATION_BAR, "navigation-bar" },
    { AccessibilityRoleType::NAVIGATION_MENU, "navigation-menu" }, { AccessibilityRoleType::NAVIGATOR, "navigator" },
    { AccessibilityRoleType::OFFSCREEN_CANVAS, "offscreencanvas" },
    { AccessibilityRoleType::OFFSCREEN_CANVAS_RENDERING_CONTEXT2D, "offscreencanvasrenderingcontext2d" },
    { AccessibilityRoleType::OPTION, "option" }, { AccessibilityRoleType::PANEL, "panel" },
    { AccessibilityRoleType::PAPER_PAGE, "paperpage" }, { AccessibilityRoleType::PATH, "path" },
    { AccessibilityRoleType::PATH2D, "path2d" }, { AccessibilityRoleType::PATTERN_LOCK, "patternlock" },
    { AccessibilityRoleType::PICKER, "picker" }, { AccessibilityRoleType::PICKER_VIEW, "picker-view" },
    { AccessibilityRoleType::PLUGIN_COMPONENT, "plugincomponent" }, { AccessibilityRoleType::POLYGON, "polygon" },
    { AccessibilityRoleType::POLYLINE, "polyline" }, { AccessibilityRoleType::POPUP, "popup" },
    { AccessibilityRoleType::PROGRESS, "progress" }, { AccessibilityRoleType::QRCODE, "qrcode" },
    { AccessibilityRoleType::RADIO, "radio" }, { AccessibilityRoleType::RATING, "rating" },
    { AccessibilityRoleType::RECT, "rect" }, { AccessibilityRoleType::REFRESH, "refresh" },
    { AccessibilityRoleType::RELATIVE_CONTAINER, "relativecontainer" },
    { AccessibilityRoleType::REMOTE_WINDOW, "remotewindow" }, { AccessibilityRoleType::RICH_EDITOR, "richeditor" },
    { AccessibilityRoleType::RICH_TEXT, "richtext" }, { AccessibilityRoleType::ROLE_PAGER, "rolepager" },
    { AccessibilityRoleType::ROW, "row" }, { AccessibilityRoleType::ROW_SPLIT, "rowsplit" },
    { AccessibilityRoleType::SCROLL, "scroll" }, { AccessibilityRoleType::SCROLL_BAR, "scrollbar" },
    { AccessibilityRoleType::SEARCH, "search" }, { AccessibilityRoleType::SEARCH_FIELD, "searchfield" },
    { AccessibilityRoleType::SELECT, "select" }, { AccessibilityRoleType::SHAPE, "shape" },
    { AccessibilityRoleType::SIDEBAR_CONTAINER, "sidebarcontainer" }, { AccessibilityRoleType::SLIDER, "slider" },
    { AccessibilityRoleType::SPAN, "span" }, { AccessibilityRoleType::STACK, "stack" },
    { AccessibilityRoleType::STEPPER, "stepper" }, { AccessibilityRoleType::STEPPER_ITEM, "stepperitem" },
    { AccessibilityRoleType::SWIPER, "swiper" }, { AccessibilityRoleType::SWIPER_INDICATOR, "swiperindicator" },
    { AccessibilityRoleType::SWITCH, "switch" }, { AccessibilityRoleType::SYMBOL_GLYPH, "symbolglyph" },
    { AccessibilityRoleType::TAB_CONTENT, "tabcontent" }, { AccessibilityRoleType::TAB_BAR, "tab-bar" },
    { AccessibilityRoleType::TABS, "tabs" }, { AccessibilityRoleType::TEXT, "text" },
    { AccessibilityRoleType::TEXT_CLOCK, "textclock" }, { AccessibilityRoleType::TEXT_ENTRY, "textentry" },
    { AccessibilityRoleType::TEXT_INPUT, "textinput" }, { AccessibilityRoleType::TEXT_PICKER, "textpicker" },
    { AccessibilityRoleType::TEXT_TIMER, "texttimer" }, { AccessibilityRoleType::TEXT_AREA, "textarea" },
    { AccessibilityRoleType::TEXT_FIELD, "textfield" }, { AccessibilityRoleType::TIME_PICKER, "timepicker" },
    { AccessibilityRoleType::TITLE_BAR, "titlebar" }, { AccessibilityRoleType::TOGGLER, "toggler" },
    { AccessibilityRoleType::UI_EXTENSION_COMPONENT, "uiextensioncomponent" },
    { AccessibilityRoleType::VIDEO, "video" }, { AccessibilityRoleType::WATER_FLOW, "waterflow" },
    { AccessibilityRoleType::WEB, "web" }, { AccessibilityRoleType::XCOMPONENT, "xcomponent" },
    { AccessibilityRoleType::ROLE_NONE, "NULL" }
};

const std::vector<AccessibilitySamePageMode> PAGE_MODE_TYPE = { AccessibilitySamePageMode::SEMI_SILENT,
    AccessibilitySamePageMode::FULL_SILENT };

const std::vector<FocusDrawLevel> FOCUS_DRAW_LEVEL = { FocusDrawLevel::SELF, FocusDrawLevel::TOP };

std::string AccessibilityStaticUtils::GetRoleByType(AccessibilityRoleType roleType)
{
    auto it = accessibilityRoleMap.find(roleType);
    if (it != accessibilityRoleMap.end()) {
        return it->second;
    }
    return "";
}

std::string AccessibilityStaticUtils::GetPageModeType(int32_t pageModeType)
{
    if (pageModeType >= 0 && pageModeType < static_cast<int32_t>(PAGE_MODE_TYPE.size())) {
        auto pageMode = static_cast<bool>(PAGE_MODE_TYPE[pageModeType]) ? "FULL_SILENT" : "SEMI_SILENT";
        return pageMode;
    }
    return "";
}

int32_t AccessibilityStaticUtils::GetFocusDrawLevel(int32_t inputValue)
{
    if (inputValue >= 0 && inputValue < static_cast<int32_t>(FOCUS_DRAW_LEVEL.size())) {
        return inputValue;
    }
    return -1;
}
}  // namespace OHOS::Ace
