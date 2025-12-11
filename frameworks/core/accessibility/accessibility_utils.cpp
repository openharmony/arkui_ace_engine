/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#define AVERAGE_BASE 2

#include "core/accessibility/accessibility_utils.h"
#include "ui/accessibility/accessibility_constants.h"
#include "frameworks/core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace {

const char ACCESSIBILITY_TAG_DIV[] = "div";
const char ACCESSIBILITY_TAG_CALENDAR[] = "calendar";
const char ACCESSIBILITY_TAG_TEXT[] = "text";
const char ACCESSIBILITY_TAG_PICKER[] = "picker";
const char ACCESSIBILITY_TAG_OPTION[] = "option";
const char ACCESSIBILITY_TAG_POPUP[] = "popup";
const char ACCESSIBILITY_TAG_PROGRESS[] = "progress";
const char ACCESSIBILITY_TAG_SELECT[] = "select";
const char ACCESSIBILITY_TAG_MENU[] = "menu";
const char ACCESSIBILITY_TAG_SLIDER[] = "slider";
const char ACCESSIBILITY_TAG_SPAN[] = "span";
const char ACCESSIBILITY_TAG_STACK[] = "stack";
const char ACCESSIBILITY_TAG_SWIPER[] = "swiper";
const char ACCESSIBILITY_TAG_SWITCH[] = "switch";
const char ACCESSIBILITY_TAG_TABS[] = "tabs";
const char ACCESSIBILITY_TAG_TAB_BAR[] = "tab-bar";
const char ACCESSIBILITY_TAG_TAB_CONTENT[] = "tab-content";
const char ACCESSIBILITY_TAG_REFRESH[] = "refresh";
const char ACCESSIBILITY_TAG_IMAGE[] = "image";
const char ACCESSIBILITY_TAG_LIST[] = "list";
const char ACCESSIBILITY_TAG_LIST_ITEM[] = "list-item";
const char ACCESSIBILITY_TAG_LIST_ITEM_GROUP[] = "list-item-group";
const char ACCESSIBILITY_TAG_VIDEO[] = "video";
const char ACCESSIBILITY_TAG_RATING[] = "rating";
const char ACCESSIBILITY_TAG_MARQUEE[] = "marquee";
const char ACCESSIBILITY_TAG_NAVIGATION_BAR[] = "navigation-bar";
const char ACCESSIBILITY_TAG_NAVIGATION_MENU[] = "navigation-menu";
const char ACCESSIBILITY_TAG_TEXTAREA[] = "textarea";
const char ACCESSIBILITY_TAG_INPUT[] = "input";
const char ACCESSIBILITY_TAG_LABEL[] = "label";
const char ACCESSIBILITY_TAG_DIVIDER[] = "divider";
const char ACCESSIBILITY_TAG_CANVAS[] = "canvas";
const char ACCESSIBILITY_TAG_BUTTON[] = "button";
const char ACCESSIBILITY_TAG_CHART[] = "chart";
const char ACCESSIBILITY_TAG_CLOCK[] = "clock";
const char ACCESSIBILITY_TAG_DIALOG[] = "dialog";
const char ACCESSIBILITY_TAG_SEARCH[] = "search";

const int32_t WEIGHTED_VALUE = 13;
const int32_t FOCUS_DIRECTION_UP = 1;
const int32_t FOCUS_DIRECTION_DOWN = 1 << 1;
const int32_t FOCUS_DIRECTION_LEFT = 1 << 2;
const int32_t FOCUS_DIRECTION_RIGHT = 1 << 3;
const int32_t FOCUS_DIRECTION_FORWARD = 1 << 4;
const int32_t FOCUS_DIRECTION_BACKWARD = 1 << 5;

static bool CheckRectBeam(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
        case FOCUS_DIRECTION_RIGHT:
            return nodeRect.Top() < itemRect.Bottom() && itemRect.Top() < nodeRect.Bottom();
        case FOCUS_DIRECTION_UP:
        case FOCUS_DIRECTION_DOWN:
            return nodeRect.Left() < itemRect.Right() && itemRect.Left() < nodeRect.Right();
        default:
            break;
    }
    return false;
}

static bool IsToDirectionOf(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            return nodeRect.Left() >= itemRect.Right();
        case FOCUS_DIRECTION_RIGHT:
            return nodeRect.Right() <= itemRect.Left();
        case FOCUS_DIRECTION_UP:
            return nodeRect.Top() >= itemRect.Bottom();
        case FOCUS_DIRECTION_DOWN:
            return nodeRect.Bottom() <= itemRect.Top();
        default:
            break;
    }
    return false;
}

static double MajorAxisDistanceToFarEdge(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    double distance = 0.0;
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            distance = nodeRect.Left() - itemRect.Left();
            break;
        case FOCUS_DIRECTION_RIGHT:
            distance = itemRect.Right() - nodeRect.Right();
            break;
        case FOCUS_DIRECTION_UP:
            distance = nodeRect.Top() - itemRect.Top();
            break;
        case FOCUS_DIRECTION_DOWN:
            distance = itemRect.Bottom() - nodeRect.Bottom();
            break;
        default:
            break;
    }

    return distance > 1.0 ? distance : 1.0;
}

static double MajorAxisDistance(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    double distance = 0.0;
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            distance = nodeRect.Left() - itemRect.Right();
            break;
        case FOCUS_DIRECTION_RIGHT:
            distance = itemRect.Left() - nodeRect.Right();
            break;
        case FOCUS_DIRECTION_UP:
            distance = nodeRect.Top() - itemRect.Bottom();
            break;
        case FOCUS_DIRECTION_DOWN:
            distance = itemRect.Top() - nodeRect.Bottom();
            break;
        default:
            break;
    }

    return distance > 0.0 ? distance : 0.0;
}

static double MinorAxisDistance(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    double distance = 0.0;
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
        case FOCUS_DIRECTION_RIGHT:
            distance = fabs((nodeRect.Top() + nodeRect.Bottom()) / AVERAGE_BASE -
                (itemRect.Top() + itemRect.Bottom()) / AVERAGE_BASE);
            break;
        case FOCUS_DIRECTION_UP:
        case FOCUS_DIRECTION_DOWN:
            distance = fabs((nodeRect.Left() + nodeRect.Right()) / AVERAGE_BASE -
                (itemRect.Left() + itemRect.Right()) / AVERAGE_BASE);
            break;
        default:
            break;
    }

    return distance > 0.0 ? distance : -distance;
}

static double GetWeightedDistanceFor(double majorAxisDistance, double minorAxisDistance)
{
    return WEIGHTED_VALUE * majorAxisDistance * majorAxisDistance + minorAxisDistance * minorAxisDistance;
}

static bool IsCandidateRect(const Rect& nodeRect, const Rect& itemRect, const int direction)
{
    switch (direction) {
        case FOCUS_DIRECTION_LEFT:
            return nodeRect.Left() > itemRect.Left() && nodeRect.Right() > itemRect.Right();
        case FOCUS_DIRECTION_RIGHT:
            return nodeRect.Left() < itemRect.Left() && nodeRect.Right() < itemRect.Right();
        case FOCUS_DIRECTION_UP:
            return nodeRect.Top() > itemRect.Top() && nodeRect.Bottom() > itemRect.Bottom();
        case FOCUS_DIRECTION_DOWN:
            return nodeRect.Top() < itemRect.Top() && nodeRect.Bottom() < itemRect.Bottom();
        default:
            break;
    }
    return false;
}

// Check whether rect1 is outright better than rect2.
static bool OutrightBetter(const Rect& nodeRect, const int direction, const Rect& Rect1, const Rect& Rect2)
{
    bool rect1InSrcBeam = CheckRectBeam(nodeRect, Rect1, direction);
    bool rect2InSrcBeam = CheckRectBeam(nodeRect, Rect2, direction);
    if (rect2InSrcBeam || !rect1InSrcBeam) {
        return false;
    }

    if (!IsToDirectionOf(nodeRect, Rect2, direction)) {
        return true;
    }

    // for direction left or right
    if (direction == FOCUS_DIRECTION_LEFT || direction == FOCUS_DIRECTION_RIGHT) {
        return true;
    }

    return (MajorAxisDistance(nodeRect, Rect1, direction) < MajorAxisDistanceToFarEdge(nodeRect, Rect2, direction));
}

bool CheckBetterRect(const Rect& nodeRect, const int direction, const Rect& itemRect, const Rect& tempBest)
{
    if (!IsCandidateRect(nodeRect, itemRect, direction)) {
        return false;
    }

    if (!IsCandidateRect(nodeRect, tempBest, direction)) {
        return true;
    }

    // now both of item and tempBest are all at the direction of node.
    if (OutrightBetter(nodeRect, direction, itemRect, tempBest)) {
        return true;
    }

    if (OutrightBetter(nodeRect, direction, tempBest, itemRect)) {
        return false;
    }

    // otherwise, do fudge-tastic comparison of the major and minor axis
    return (GetWeightedDistanceFor(
                MajorAxisDistance(nodeRect, itemRect, direction), MinorAxisDistance(nodeRect, itemRect, direction)) <
            GetWeightedDistanceFor(
                MajorAxisDistance(nodeRect, tempBest, direction), MinorAxisDistance(nodeRect, tempBest, direction)));
}

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

std::string AccessibilityUtils::GetRoleByType(AccessibilityRoleType roleType)
{
    auto it = accessibilityRoleMap.find(roleType);
    if (it != accessibilityRoleMap.end()) {
        return it->second;
    }
    return "";
}

const std::unordered_map<AccessibilityRoleType, std::string> accessibilityAceRoleMap {
    { AccessibilityRoleType::ACTION_SHEET, V2::ACTION_SHEET_DIALOG_ETS_TAG },
    { AccessibilityRoleType::ALERT_DIALOG, V2::ALERT_DIALOG_ETS_TAG },
    { AccessibilityRoleType::INDEXER_COMPONENT, V2::INDEXER_ETS_TAG },
    { AccessibilityRoleType::BADGE_COMPONENT, V2::BADGE_ETS_TAG },
    { AccessibilityRoleType::BLANK, V2::BLANK_ETS_TAG },
    { AccessibilityRoleType::BUTTON, V2::BUTTON_ETS_TAG },
    { AccessibilityRoleType::BACK_BUTTON, V2::BACK_BUTTON_ETS_TAG },
    { AccessibilityRoleType::SHEET_DRAG_BAR, "SheetDragBar" },
    { AccessibilityRoleType::CALENDAR_PICKER, V2::CALENDAR_PICKER_ETS_TAG },
    { AccessibilityRoleType::CALENDAR, V2::CALENDAR_ETS_TAG },
    { AccessibilityRoleType::CANVAS, V2::CANVAS_ETS_TAG },
    { AccessibilityRoleType::CANVAS_GRADIENT, "Canvasgradient" },
    { AccessibilityRoleType::CANVAS_PATTERN, "Canvaspattern" },
    { AccessibilityRoleType::CHECKBOX, V2::CHECK_BOX_ETS_TAG },
    { AccessibilityRoleType::CHECKBOX_GROUP, V2::CHECKBOXGROUP_ETS_TAG },
    { AccessibilityRoleType::CIRCLE, V2::CIRCLE_ETS_TAG },
    { AccessibilityRoleType::COLUMN_SPLIT, V2::COLUMN_SPLIT_ETS_TAG },
    { AccessibilityRoleType::COLUMN, V2::COLUMN_ETS_TAG },
    { AccessibilityRoleType::CANVAS_RENDERING_CONTEXT_2D, "CanvasRenderingContext2D" },
    { AccessibilityRoleType::CHART, "chart" },
    { AccessibilityRoleType::COUNTER, V2::COUNTER_ETS_TAG },
    { AccessibilityRoleType::CONTAINER_MODAL, V2::CONTAINER_MODAL_ETS_TAG },
    { AccessibilityRoleType::DATA_PANEL, V2::DATA_PANEL_ETS_TAG },
    { AccessibilityRoleType::DATE_PICKER, V2::DATE_PICKER_ETS_TAG },
    { AccessibilityRoleType::DIALOG, V2::DIALOG_ETS_TAG },
    { AccessibilityRoleType::DIVIDER, V2::DIVIDER_ETS_TAG },
    { AccessibilityRoleType::DRAG_BAR, V2::DRAG_BAR_ETS_TAG },
    { AccessibilityRoleType::EFFECT_COMPONENT, V2::EFFECT_COMPONENT_ETS_TAG },
    { AccessibilityRoleType::ELLIPSE, V2::ELLIPSE_ETS_TAG },
    { AccessibilityRoleType::FLEX, V2::FLEX_ETS_TAG },
    { AccessibilityRoleType::FLOW_ITEM, V2::FLOW_ITEM_ETS_TAG },
    { AccessibilityRoleType::FORM_COMPONENT, V2::FORM_ETS_TAG },
    { AccessibilityRoleType::FORM_LINK, V2::FORM_LINK_ETS_TAG },
    { AccessibilityRoleType::GAUGE, V2::GAUGE_ETS_TAG },
    { AccessibilityRoleType::GRID, V2::GRID_ETS_TAG },
    { AccessibilityRoleType::GRID_COL, V2::GRID_COL_ETS_TAG },
    { AccessibilityRoleType::GRID_CONTAINER, V2::GRIDCONTAINER_ETS_TAG },
    { AccessibilityRoleType::GRID_ITEM, V2::GRID_ITEM_ETS_TAG },
    { AccessibilityRoleType::GRID_ROW, V2::GRID_ROW_ETS_TAG },
    { AccessibilityRoleType::HYPERLINK, V2::HYPERLINK_ETS_TAG },
    { AccessibilityRoleType::IMAGE, V2::IMAGE_ETS_TAG },
    { AccessibilityRoleType::IMAGE_ANIMATOR, V2::IMAGE_ANIMATOR_ETS_TAG },
    { AccessibilityRoleType::ROLE_IMAGE_BITMAP, "ImageBitmap" },
    { AccessibilityRoleType::IMAGE_DATA, "ImageData" },
    { AccessibilityRoleType::IMAGE_SPAN, V2::IMAGE_SPAN_ETS_TAG },
    { AccessibilityRoleType::LABEL, "label" },
    { AccessibilityRoleType::LINE, V2::LINE_ETS_TAG },
    { AccessibilityRoleType::LIST, V2::LIST_ETS_TAG },
    { AccessibilityRoleType::LIST_ITEM, V2::LIST_ITEM_ETS_TAG },
    { AccessibilityRoleType::LIST_ITEM_GROUP, V2::LIST_ITEM_GROUP_ETS_TAG },
    { AccessibilityRoleType::LOADING_PROGRESS, V2::LOADING_PROGRESS_ETS_TAG },
    { AccessibilityRoleType::MARQUEE, V2::MARQUEE_ETS_TAG },
    { AccessibilityRoleType::MATRIX2D, "Matrix2D" },
    { AccessibilityRoleType::MENU, V2::MENU_ETS_TAG },
    { AccessibilityRoleType::MENU_ITEM, V2::MENU_ITEM_ETS_TAG },
    { AccessibilityRoleType::MENU_ITEM_GROUP, V2::MENU_ITEM_GROUP_ETS_TAG },
    { AccessibilityRoleType::NAV_DESTINATION, V2::NAVDESTINATION_VIEW_ETS_TAG },
    { AccessibilityRoleType::NAV_ROUTER, V2::NAVROUTER_VIEW_ETS_TAG },
    { AccessibilityRoleType::NAVIGATION, V2::NAVIGATION_VIEW_ETS_TAG },
    { AccessibilityRoleType::NAVIGATION_BAR, V2::NAVBAR_ETS_TAG },
    { AccessibilityRoleType::NAVIGATION_MENU, V2::NAVIGATION_MENU_ETS_TAG },
    { AccessibilityRoleType::NAVIGATOR, V2::NAVIGATOR_ETS_TAG },
    { AccessibilityRoleType::OFFSCREEN_CANVAS, "OffscreenCanvas" },
    { AccessibilityRoleType::OFFSCREEN_CANVAS_RENDERING_CONTEXT2D, "OffscreenCanvasRenderingContext2D" },
    { AccessibilityRoleType::OPTION, V2::OPTION_ETS_TAG },
    { AccessibilityRoleType::PANEL, V2::PANEL_ETS_TAG },
    { AccessibilityRoleType::PAPER_PAGE, "paperpage" },
    { AccessibilityRoleType::PATH, V2::PATH_ETS_TAG },
    { AccessibilityRoleType::PATH2D, "path2d" },
    { AccessibilityRoleType::PATTERN_LOCK, V2::PATTERN_LOCK_ETS_TAG },
    { AccessibilityRoleType::PICKER, "Picker" },
    { AccessibilityRoleType::PICKER_VIEW, "picker-view" },
    { AccessibilityRoleType::PLUGIN_COMPONENT, V2::PLUGIN_ETS_TAG },
    { AccessibilityRoleType::POLYGON, V2::POLYGON_ETS_TAG },
    { AccessibilityRoleType::POLYLINE, V2::POLYLINE_ETS_TAG },
    { AccessibilityRoleType::POPUP, V2::POPUP_ETS_TAG },
    { AccessibilityRoleType::PROGRESS, V2::PROGRESS_ETS_TAG },
    { AccessibilityRoleType::QRCODE, V2::QRCODE_ETS_TAG },
    { AccessibilityRoleType::RADIO, V2::RADIO_ETS_TAG },
    { AccessibilityRoleType::RATING, V2::RATING_ETS_TAG },
    { AccessibilityRoleType::RECT, V2::RECT_ETS_TAG },
    { AccessibilityRoleType::REFRESH, V2::REFRESH_ETS_TAG },
    { AccessibilityRoleType::RELATIVE_CONTAINER, V2::RELATIVE_CONTAINER_ETS_TAG },
    { AccessibilityRoleType::REMOTE_WINDOW, V2::REMOTE_WINDOW_ETS_TAG },
    { AccessibilityRoleType::RICH_EDITOR, V2::RICH_EDITOR_ETS_TAG },
    { AccessibilityRoleType::RICH_TEXT, V2::RICH_TEXT_ETS_TAG },
    { AccessibilityRoleType::ROLE_PAGER, "rolepager" },
    { AccessibilityRoleType::ROW, V2::ROW_ETS_TAG },
    { AccessibilityRoleType::ROW_SPLIT, V2::ROW_SPLIT_ETS_TAG },
    { AccessibilityRoleType::SCROLL, V2::SCROLL_ETS_TAG },
    { AccessibilityRoleType::SCROLL_BAR, V2::SCROLL_BAR_ETS_TAG },
    { AccessibilityRoleType::SEARCH, "search" },
    { AccessibilityRoleType::SEARCH_FIELD, "searchfield" },
    { AccessibilityRoleType::SELECT, "select" },
    { AccessibilityRoleType::SHAPE, "shape" },
    { AccessibilityRoleType::SIDEBAR_CONTAINER, "sidebarcontainer" },
    { AccessibilityRoleType::SLIDER, V2::SLIDER_ETS_TAG },
    { AccessibilityRoleType::SPAN, V2::SPAN_ETS_TAG },
    { AccessibilityRoleType::STACK, V2::STACK_ETS_TAG },
    { AccessibilityRoleType::STEPPER, V2::STEPPER_ETS_TAG },
    { AccessibilityRoleType::STEPPER_ITEM, V2::STEPPER_ITEM_ETS_TAG },
    { AccessibilityRoleType::SWIPER, V2::SWIPER_ETS_TAG },
    { AccessibilityRoleType::SWIPER_INDICATOR, V2::SWIPER_INDICATOR_ETS_TAG },
    { AccessibilityRoleType::SWITCH, "switch" },
    { AccessibilityRoleType::SYMBOL_GLYPH, V2::SYMBOL_ETS_TAG },
    { AccessibilityRoleType::TAB_CONTENT, V2::TAB_CONTENT_ITEM_ETS_TAG },
    { AccessibilityRoleType::TAB_BAR, V2::TAB_BAR_ETS_TAG },
    { AccessibilityRoleType::TABS, V2::TABS_ETS_TAG },
    { AccessibilityRoleType::TEXT, V2::TEXT_ETS_TAG },
    { AccessibilityRoleType::TEXT_CLOCK, V2::TEXTCLOCK_ETS_TAG },
    { AccessibilityRoleType::TEXT_ENTRY, "textentry" },
    { AccessibilityRoleType::TEXT_INPUT, V2::TEXTINPUT_ETS_TAG },
    { AccessibilityRoleType::TEXT_PICKER, V2::TEXT_PICKER_ETS_TAG },
    { AccessibilityRoleType::TEXT_TIMER, V2::TEXTTIMER_ETS_TAG },
    { AccessibilityRoleType::TEXT_AREA, V2::TEXTAREA_ETS_TAG },
    { AccessibilityRoleType::TEXT_FIELD, "TextField" },
    { AccessibilityRoleType::TIME_PICKER, V2::TIME_PICKER_ETS_TAG },
    { AccessibilityRoleType::TITLE_BAR, V2::TITLE_BAR_ETS_TAG },
    { AccessibilityRoleType::TOGGLER, V2::TOGGLE_ETS_TAG },
    { AccessibilityRoleType::UI_EXTENSION_COMPONENT, V2::UI_EXTENSION_COMPONENT_ETS_TAG },
    { AccessibilityRoleType::VIDEO, V2::VIDEO_ETS_TAG },
    { AccessibilityRoleType::WATER_FLOW, V2::WATERFLOW_ETS_TAG },
    { AccessibilityRoleType::WEB, V2::WEB_ETS_TAG },
    { AccessibilityRoleType::XCOMPONENT, V2::XCOMPONENT_ETS_TAG },
    { AccessibilityRoleType::ROLE_NONE, "NULL" }
};

std::string AccessibilityUtils::GetAceComponentTypeByRoleType(AccessibilityRoleType roleType)
{
    auto it = accessibilityAceRoleMap.find(roleType);
    if (it != accessibilityAceRoleMap.end()) {
        return it->second;
    }
    return "";
}
}  // namespace OHOS::Ace
