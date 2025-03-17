/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_INSPECTOR_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_INSPECTOR_CONSTANTS_H

#include <cstdint>
#include <string>
#include <unordered_map>

#include "base/utils/macros.h"

namespace OHOS::Ace::V2 {

ACE_EXPORT extern const char ATTRS_COMMON_WIDTH[];
ACE_EXPORT extern const char ATTRS_COMMON_HEIGHT[];
ACE_EXPORT extern const char ATTRS_COMMON_PADDING[];
ACE_EXPORT extern const char ATTRS_COMMON_MARGIN[];
ACE_EXPORT extern const char ATTRS_COMMON_LAYOUT_PRIORITY[];
ACE_EXPORT extern const char ATTRS_COMMON_LAYOUT_WEIGHT[];
// position
ACE_EXPORT extern const char ATTRS_COMMON_ALIGN[];
ACE_EXPORT extern const char ATTRS_COMMON_DIRECTION[];
ACE_EXPORT extern const char ATTRS_COMMON_POSITION[];
ACE_EXPORT extern const char ATTRS_COMMON_OFFSET[];
ACE_EXPORT extern const char ATTRS_COMMON_USE_ALIGN[];
// layout
ACE_EXPORT extern const char ATTRS_COMMON_RELATE_PARENT[];
ACE_EXPORT extern const char ATTRS_COMMON_ASPECT_RATIO[];
ACE_EXPORT extern const char ATTRS_COMMON_DISPLAY_PRIORITY[];
// border
ACE_EXPORT extern const char ATTRS_COMMON_BORDER[];
// background
ACE_EXPORT extern const char ATTRS_COMMON_BACKGROUND_COLOR[];
// opacity
ACE_EXPORT extern const char ATTRS_COMMON_OPACITY[];
// visibility
ACE_EXPORT extern const char ATTRS_COMMON_VISIBILITY[];
// enable
ACE_EXPORT extern const char ATTRS_COMMON_ENABLE[];
// zindex
ACE_EXPORT extern const char ATTRS_COMMON_ZINDEX[];

// root view
ACE_EXPORT extern const char ROOT_ETS_TAG[];
// stage view
ACE_EXPORT extern const char STAGE_ETS_TAG[];
// page view
ACE_EXPORT extern const char PAGE_ETS_TAG[];
// overlay view
ACE_EXPORT extern const char OVERLAY_ETS_TAG[];
ACE_EXPORT extern const char ORDER_OVERLAY_ETS_TAG[];
// container modal view (title bar)
ACE_EXPORT extern const char CONTAINER_MODAL_ETS_TAG[];

ACE_EXPORT extern const char ATOMIC_SERVICE_ETS_TAG[];
ACE_EXPORT extern const char APP_BAR_ETS_TAG[];
// js custom view
ACE_EXPORT extern const char JS_VIEW_ETS_TAG[];
ACE_EXPORT extern const char JS_VIEW_COMPONENT_TAG[];
// js lazy foreach node
ACE_EXPORT extern const char JS_LAZY_FOR_EACH_ETS_TAG[];
// js lazy foreach node
ACE_EXPORT extern const char JS_FOR_EACH_ETS_TAG[];
// js lazy foreach node
ACE_EXPORT extern const char JS_SYNTAX_ITEM_ETS_TAG[];
// js repeat node
ACE_EXPORT extern const char JS_REPEAT_ETS_TAG[];
// js if else node
ACE_EXPORT extern const char JS_IF_ELSE_ETS_TAG[];
// js with theme node
ACE_EXPORT extern const char JS_WITH_THEME_ETS_TAG[];
// js node slot node
ACE_EXPORT extern const char JS_NODE_SLOT_ETS_TAG[];
// js toast node
ACE_EXPORT extern const char TOAST_ETS_TAG[];

// column
ACE_EXPORT extern const char COLUMN_COMPONENT_TAG[];
ACE_FORCE_EXPORT extern const char COLUMN_ETS_TAG[];
ACE_EXPORT extern const char COLUMN_ATTRS_ALIGN_ITEMS[];

// panel bar
ACE_EXPORT extern const char DRAG_BAR_COMPONENT_TAG[];
ACE_EXPORT extern const char DRAG_BAR_ETS_TAG[];

// text
ACE_EXPORT extern const char TEXT_COMPONENT_TAG[];
ACE_EXPORT extern const char TEXT_ETS_TAG[];
ACE_EXPORT extern const char TEXT_ATTRS_OVER_FLOW[];
ACE_EXPORT extern const char TEXT_ATTRS_MAX_LINES[];

// rich editor
ACE_EXPORT extern const char RICH_EDITOR_ETS_TAG[];
ACE_EXPORT extern const char RICH_EDITOR_DRAG_ETS_TAG[];

// stack
ACE_EXPORT extern const char STACK_COMPONENT_TAG[];
ACE_EXPORT extern const char STACK_ETS_TAG[];

// folderStack
ACE_EXPORT extern const char FOLDER_STACK_COMPONENT_TAG[];
ACE_EXPORT extern const char FOLDER_STACK_ETS_TAG[];
ACE_EXPORT extern const char HOVER_STACK_ETS_TAG[];
ACE_EXPORT extern const char CONTROL_PARTS_STACK_ETS_TAG[];

// swiper
ACE_EXPORT extern const char SWIPER_COMPONENT_TAG[];
ACE_EXPORT extern const char SWIPER_ETS_TAG[];
ACE_EXPORT extern const char SWIPER_INDICATOR_ETS_TAG[];
ACE_EXPORT extern const char SWIPER_LEFT_ARROW_ETS_TAG[];
ACE_EXPORT extern const char SWIPER_RIGHT_ARROW_ETS_TAG[];
ACE_EXPORT extern const char SWIPER_LEFT_CAPTURE_ETS_TAG[];
ACE_EXPORT extern const char SWIPER_RIGHT_CAPTURE_ETS_TAG[];

// indicator
ACE_EXPORT extern const char INDICATOR_COMPONENT_TAG[];
ACE_EXPORT extern const char INDICATOR_ETS_TAG[];

// tabs
ACE_EXPORT extern const char TABS_COMPONENT_TAG[];
ACE_EXPORT extern const char TABS_ETS_TAG[];

// tab content item
ACE_EXPORT extern const char TAB_CONTENT_ITEM_COMPONENT_TAG[];
ACE_EXPORT extern const char TAB_CONTENT_ITEM_ETS_TAG[];

// tab bar
ACE_EXPORT extern const char TAB_BAR_COMPONENT_TAG[];
ACE_EXPORT extern const char TAB_BAR_ETS_TAG[];

// navigation view
ACE_EXPORT extern const char NAVIGATION_VIEW_COMPONENT_TAG[];
ACE_EXPORT extern const char NAVIGATION_VIEW_ETS_TAG[];
ACE_EXPORT extern const char BAR_ITEM_ETS_TAG[];
ACE_EXPORT extern const char TITLE_BAR_ETS_TAG[];
ACE_EXPORT extern const char NAVIGATION_CONTENT_ETS_TAG[];
ACE_EXPORT extern const char TOOL_BAR_ETS_TAG[];
ACE_EXPORT extern const char NAVIGATION_MENU_ETS_TAG[];
ACE_EXPORT extern const char BACK_BUTTON_ETS_TAG[];
ACE_EXPORT extern const char BACK_BUTTON_IMAGE_ETS_TAG[];
ACE_EXPORT extern const char NAVBAR_CONTENT_ETS_TAG[];
ACE_EXPORT extern const char NAVBAR_ETS_TAG[];

// navRouter view
ACE_EXPORT extern const char NAVROUTER_VIEW_ETS_TAG[];

// navDestination view
ACE_EXPORT extern const char NAVDESTINATION_VIEW_ETS_TAG[];
ACE_EXPORT extern const char NAVDESTINATION_TITLE_BAR_ETS_TAG[];
ACE_EXPORT extern const char NAVDESTINATION_CONTENT_ETS_TAG[];

// navigation title view
ACE_EXPORT extern const char NAVIGATION_TITLE_COMPONENT_TAG[];

// navigation menus view
ACE_EXPORT extern const char NAVIGATION_MENUS_COMPONENT_TAG[];

// row split
ACE_EXPORT extern const char ROW_SPLIT_COMPONENT_TAG[];
ACE_EXPORT extern const char ROW_SPLIT_ETS_TAG[];

// column split
ACE_EXPORT extern const char COLUMN_SPLIT_COMPONENT_TAG[];
ACE_EXPORT extern const char COLUMN_SPLIT_ETS_TAG[];

// counter
ACE_EXPORT extern const char COUNTER_COMPONENT_TAG[];
ACE_EXPORT extern const char COUNTER_ETS_TAG[];

// flex
ACE_EXPORT extern const char FLEX_COMPONENT_TAG[];
ACE_EXPORT extern const char FLEX_ETS_TAG[];
ACE_EXPORT extern const char WRAP_COMPONENT_TAG[];
ACE_EXPORT extern const char WRAP_ETS_TAG[];

// grid
ACE_EXPORT extern const char GRID_COMPONENT_TAG[];
ACE_EXPORT extern const char GRID_ETS_TAG[];

// grid-item
ACE_EXPORT extern const char GRID_ITEM_COMPONENT_TAG[];
ACE_EXPORT extern const char GRID_ITEM_ETS_TAG[];

// waterFlow
ACE_EXPORT extern const char WATERFLOW_COMPONENT_TAG[];
ACE_EXPORT extern const char WATERFLOW_ETS_TAG[];

// flow-item
ACE_EXPORT extern const char FLOW_ITEM_COMPONENT_TAG[];
ACE_EXPORT extern const char FLOW_ITEM_ETS_TAG[];

// list
ACE_EXPORT extern const char LIST_COMPONENT_TAG[];
ACE_EXPORT extern const char LIST_ETS_TAG[];

// list-item
ACE_EXPORT extern const char LIST_ITEM_COMPONENT_TAG[];
ACE_EXPORT extern const char LIST_ITEM_ETS_TAG[];

// list-item
ACE_EXPORT extern const char LIST_ITEM_GROUP_COMPONENT_TAG[];
ACE_EXPORT extern const char LIST_ITEM_GROUP_ETS_TAG[];

// navigator
ACE_EXPORT extern const char NAVIGATOR_COMPONENT_TAG[];
ACE_EXPORT extern const char NAVIGATOR_ETS_TAG[];

// panel
ACE_EXPORT extern const char PANEL_COMPONENT_TAG[];
ACE_EXPORT extern const char PANEL_ETS_TAG[];
ACE_EXPORT extern const char PANEL_CLOSE_ICON_ETS_TAG[];

// pattern-lock
ACE_EXPORT extern const char PATTERN_LOCK_COMPONENT_TAG[];
ACE_FORCE_EXPORT extern const char PATTERN_LOCK_ETS_TAG[];

// row
ACE_EXPORT extern const char ROW_COMPONENT_TAG[];
ACE_EXPORT extern const char ROW_ETS_TAG[];

// rect
ACE_EXPORT extern const char RECT_ETS_TAG[];

// line
ACE_EXPORT extern const char LINE_ETS_TAG[];

// circle
ACE_EXPORT extern const char CIRCLE_ETS_TAG[];

// ellipse
ACE_EXPORT extern const char ELLIPSE_ETS_TAG[];

// path
ACE_EXPORT extern const char PATH_ETS_TAG[];

// polygon
ACE_EXPORT extern const char POLYGON_ETS_TAG[];

// polyline
ACE_EXPORT extern const char POLYLINE_ETS_TAG[];

// shape
ACE_EXPORT extern const char SHAPE_COMPONENT_TAG[];
ACE_EXPORT extern const char SHAPE_ETS_TAG[];

// shape container
ACE_EXPORT extern const char SHAPE_CONTAINER_COMPONENT_TAG[];
ACE_EXPORT extern const char SHAPE_CONTAINER_ETS_TAG[];

// imageAnimator
ACE_EXPORT extern const char IMAGE_ANIMATOR_COMPONENT_TAG[];
ACE_EXPORT extern const char IMAGE_ANIMATOR_ETS_TAG[];

// image
ACE_EXPORT extern const char IMAGE_COMPONENT_TAG[];
ACE_FORCE_EXPORT extern const char IMAGE_ETS_TAG[];

// qrcode
ACE_EXPORT extern const char QRCODE_COMPONENT_TAG[];
ACE_FORCE_EXPORT extern const char QRCODE_ETS_TAG[];

// span
ACE_EXPORT extern const char SPAN_COMPONENT_TAG[];
ACE_EXPORT extern const char SPAN_ETS_TAG[];

// symbol span
ACE_EXPORT extern const char SYMBOL_SPAN_COMPONENT_TAG[];
ACE_EXPORT extern const char SYMBOL_SPAN_ETS_TAG[];

// image span
ACE_EXPORT extern const char IMAGE_SPAN_COMPONENT_TAG[];
ACE_EXPORT extern const char IMAGE_SPAN_ETS_TAG[];

// placeholder span
ACE_EXPORT extern const char PLACEHOLDER_SPAN_COMPONENT_TAG[];
ACE_EXPORT extern const char PLACEHOLDER_SPAN_ETS_TAG[];

// text
ACE_EXPORT extern const char TEXT_COMPONENT_TAG[];
ACE_EXPORT extern const char TEXT_ETS_TAG[];

// blank
ACE_EXPORT extern const char BOX_COMPONENT_TAG[];
ACE_EXPORT extern const char BLANK_ETS_TAG[];

// button
ACE_EXPORT extern const char BUTTON_COMPONENT_TAG[];
ACE_EXPORT extern const char BUTTON_ETS_TAG[];

// recycle
ACE_EXPORT extern const char RECYCLE_VIEW_ETS_TAG[];

// common
ACE_EXPORT extern const char COMMON_VIEW_ETS_TAG[];
// option
ACE_EXPORT extern const char OPTION_COMPONENT_TAG[];
ACE_EXPORT extern const char OPTION_ETS_TAG[];

// divider
ACE_EXPORT extern const char DIVIDER_COMPONENT_TAG[];
ACE_EXPORT extern const char DIVIDER_ETS_TAG[];

// checkbox
ACE_EXPORT extern const char CHECKBOX_COMPONENT_TAG[];
ACE_EXPORT extern const char CHECKBOX_ETS_TAG[];
ACE_EXPORT extern const char CHECK_BOX_COMPONENT_TAG[];
ACE_EXPORT extern const char CHECK_BOX_ETS_TAG[];

// switch
ACE_EXPORT extern const char SWITCH_COMPONENT_TAG[];
ACE_EXPORT extern const char SWITCH_ETS_TAG[];

// toggle
ACE_EXPORT extern const char TOGGLE_COMPONENT_TAG[];
ACE_EXPORT extern const char TOGGLE_ETS_TAG[];

// scroll
ACE_EXPORT extern const char SCROLL_COMPONENT_TAG[];
ACE_EXPORT extern const char SCROLL_ETS_TAG[];

// calendar
ACE_EXPORT extern const char CALENDAR_COMPONENT_TAG[];
ACE_EXPORT extern const char CALENDAR_ETS_TAG[];

// calendarPicker
ACE_EXPORT extern const char CALENDAR_PICKER_COMPONENT_TAG[];
ACE_EXPORT extern const char CALENDAR_PICKER_ETS_TAG[];

// badge
ACE_EXPORT extern const char BADGE_COMPONENT_TAG[];
ACE_EXPORT extern const char BADGE_ETS_TAG[];

// search
ACE_EXPORT extern const char SEARCH_COMPONENT_TAG[];
ACE_EXPORT extern const char SEARCH_ETS_TAG[];
extern const char SEARCH_Field_ETS_TAG[];

// formComponent
ACE_EXPORT extern const char FORM_COMPONENT_TAG[];
ACE_EXPORT extern const char FORM_ETS_TAG[];

// formLink
ACE_EXPORT extern const char FORM_LINK_TAG[];
ACE_EXPORT extern const char FORM_LINK_ETS_TAG[];

// formButton
#ifdef FORM_BUTTON_COMPONENT_SUPPORT
ACE_EXPORT extern const char FORM_BUTTON_TAG[];
ACE_EXPORT extern const char FORM_BUTTON_ETS_TAG[];
#endif

// PluginComponent
ACE_EXPORT extern const char PLUGIN_COMPONENT_TAG[];
ACE_EXPORT extern const char PLUGIN_ETS_TAG[];

// video
ACE_EXPORT extern const char VIDEO_COMPONENT_TAG[];
ACE_EXPORT extern const char VIDEO_ETS_TAG[];

// AlphabetIndexer
ACE_EXPORT extern const char INDEXER_COMPONENT_TAG[];
ACE_EXPORT extern const char INDEXER_ETS_TAG[];

// slider
ACE_EXPORT extern const char SLIDER_COMPONENT_TAG[];
ACE_EXPORT extern const char SLIDER_ETS_TAG[];

// rating
ACE_EXPORT extern const char RATING_COMPONENT_TAG[];
ACE_EXPORT extern const char RATING_ETS_TAG[];

// progress
ACE_EXPORT extern const char PROGRESS_COMPONENT_TAG[];
ACE_EXPORT extern const char PROGRESS_ETS_TAG[];

// datapanel
ACE_EXPORT extern const char DATA_PANEL_COMPONENT_TAG[];
ACE_EXPORT extern const char DATA_PANEL_ETS_TAG[];

// sheet
ACE_EXPORT extern const char SHEET_COMPONENT_TAG[];
ACE_EXPORT extern const char SHEET_ETS_TAG[];
ACE_EXPORT extern const char SHEET_MASK_TAG[];
ACE_EXPORT extern const char SHEET_PAGE_TAG[];
ACE_EXPORT extern const char SHEET_WRAPPER_TAG[];

// full screen modal
ACE_EXPORT extern const char MODAL_PAGE_TAG[];

// hyperlink
ACE_EXPORT extern const char HYPERLINK_COMPONENT_TAG[];
ACE_EXPORT extern const char HYPERLINK_ETS_TAG[];

// stepper
ACE_EXPORT extern const char STEPPER_COMPONENT_TAG[];
ACE_EXPORT extern const char STEPPER_ETS_TAG[];

// stepperItem
ACE_EXPORT extern const char STEPPER_ITEM_COMPONENT_TAG[];
ACE_EXPORT extern const char STEPPER_ITEM_ETS_TAG[];

// scrollBar
ACE_EXPORT extern const char SCROLL_BAR_COMPONENT_TAG[];
ACE_EXPORT extern const char SCROLL_BAR_ETS_TAG[];

ACE_EXPORT extern const std::unordered_map<std::string, std::string> COMPONENT_TAG_TO_ETS_TAG_MAP;
// refresh
ACE_EXPORT extern const char REFRESH_COMPONENT_TAG[];
ACE_EXPORT extern const char REFRESH_ETS_TAG[];

// datePicker
ACE_EXPORT extern const char DATE_PICKER_COMPONENT_TAG[];
ACE_EXPORT extern const char DATE_PICKER_ETS_TAG[];
ACE_EXPORT extern const char TIME_PICKER_COMPONENT_TAG[];
ACE_EXPORT extern const char TIME_PICKER_ETS_TAG[];

// Radio
ACE_EXPORT extern const char RADIO_COMPONENT_TAG[];
ACE_EXPORT extern const char RADIO_ETS_TAG[];

// gauge
ACE_EXPORT extern const char GAUGE_COMPONENT_TAG[];
ACE_EXPORT extern const char GAUGE_ETS_TAG[];
ACE_EXPORT extern const char GAUGE_DESCRIPTION_TAG[];
ACE_EXPORT extern const char GAUGE_INDICATOR_TAG[];

// gridContainer
ACE_EXPORT extern const char GRIDCONTAINER_COMPONENT_TAG[];
ACE_EXPORT extern const char GRIDCONTAINER_ETS_TAG[];

// gridCol
ACE_EXPORT extern const char GRID_COL_COMPONENT_TAG[];
ACE_EXPORT extern const char GRID_COL_ETS_TAG[];

// gridRow
ACE_EXPORT extern const char GRID_ROW_COMPONENT_TAG[];
ACE_EXPORT extern const char GRID_ROW_ETS_TAG[];

// relativeContainer
ACE_EXPORT extern const char RELATIVE_CONTAINER_COMPONENT_TAG[];
ACE_FORCE_EXPORT extern const char RELATIVE_CONTAINER_ETS_TAG[];

// menu
ACE_EXPORT extern const char MENU_COMPONENT_TAG[];
ACE_EXPORT extern const char MENU_TAG[];
ACE_EXPORT extern const char MENU_ETS_TAG[];
ACE_EXPORT extern const char MENU_ITEM_ETS_TAG[];
ACE_EXPORT extern const char MENU_ITEM_GROUP_ETS_TAG[];
ACE_EXPORT extern const char MENU_WRAPPER_ETS_TAG[];
ACE_EXPORT extern const char MENU_PREVIEW_ETS_TAG[];
ACE_EXPORT extern const char MENU_DIVIDER_TAG[];

// textarea
ACE_EXPORT extern const char TEXTAREA_COMPONENT_TAG[];
ACE_EXPORT extern const char TEXTAREA_ETS_TAG[];

// textdrag
ACE_EXPORT extern const char TEXTDRAG_ETS_TAG[];

// textinput
ACE_EXPORT extern const char TEXTINPUT_COMPONENT_TAG[];
ACE_EXPORT extern const char TEXTINPUT_ETS_TAG[];

// texttimer
ACE_EXPORT extern const char TEXTTIMER_COMPONENT_TAG[];
ACE_EXPORT extern const char TEXTTIMER_ETS_TAG[];

// select
ACE_EXPORT extern const char SELECT_COMPONENT_TAG[];
ACE_EXPORT extern const char SELECT_ETS_TAG[];

// select_popup
ACE_EXPORT extern const char SELECT_POPUP_COMPONENT_TAG[];
ACE_EXPORT extern const char SELECT_POPUP_ETS_TAG[];

// marquee
ACE_EXPORT extern const char MARQUEE_COMPONENT_TAG[];
ACE_EXPORT extern const char MARQUEE_ETS_TAG[];

// textclock
ACE_EXPORT extern const char TEXTCLOCK_COMPONENT_TAG[];
ACE_EXPORT extern const char TEXTCLOCK_ETS_TAG[];

// textpicker
ACE_EXPORT extern const char TEXT_PICKER_COMPONENT_TAG[];
ACE_EXPORT extern const char TEXT_PICKER_ETS_TAG[];

// pickertextdialog
ACE_EXPORT extern const char PICKER_TEXT_DIALOG_COMPONENT_TAG[];
ACE_EXPORT extern const char PICKER_TEXT_DIALOG_ETS_TAG[];

// canvas
ACE_EXPORT extern const char CANVAS_COMPONENT_TAG[];
ACE_EXPORT extern const char CANVAS_ETS_TAG[];

// ActionSheet
ACE_EXPORT extern const char ACTION_SHEET_DIALOG_COMPONENT_TAG[];
ACE_EXPORT extern const char ACTION_SHEET_DIALOG_ETS_TAG[];

// AlertDialog
ACE_EXPORT extern const char ALERT_DIALOG_COMPONENT_TAG[];
ACE_EXPORT extern const char ALERT_DIALOG_ETS_TAG[];

// CustomDialog
ACE_EXPORT extern const char CUSTOM_DIALOG_COMPONENT_TAG[];
ACE_EXPORT extern const char CUSTOM_DIALOG_ETS_TAG[];

// datePickerdialog
ACE_EXPORT extern const char DATE_PICKER_DIALOG_COMPONENT_TAG[];
ACE_EXPORT extern const char DATE_PICKER_DIALOG_ETS_TAG[];

// Normal dialog
ACE_EXPORT extern const char DIALOG_COMPONENT_TAG[];
ACE_EXPORT extern const char DIALOG_ETS_TAG[];

// sideBar
ACE_EXPORT extern const char SIDE_BAR_COMPONENT_TAG[];
ACE_EXPORT extern const char SIDE_BAR_ETS_TAG[];

// loadingProgress
ACE_EXPORT extern const char LOADING_PROGRESS_COMPONENT_TAG[];
ACE_EXPORT extern const char LOADING_PROGRESS_ETS_TAG[];

// checkboxGroup
ACE_EXPORT extern const char CHECKBOXGROUP_COMPONENT_TAG[];
ACE_EXPORT extern const char CHECKBOXGROUP_ETS_TAG[];

// timePickerdialog
ACE_EXPORT extern const char TIME_PICKER_DIALOG_COMPONENT_TAG[];
ACE_EXPORT extern const char TIME_PICKER_DIALOG_ETS_TAG[];

// web
ACE_EXPORT extern const char WEB_COMPONENT_TAG[];
ACE_EXPORT extern const char WEB_ETS_TAG[];
ACE_EXPORT extern const char WEB_CORE_TAG[];

// richText
ACE_EXPORT extern const char RICH_TEXT_COMPONENT_TAG[];
ACE_EXPORT extern const char RICH_TEXT_ETS_TAG[];

// xcomponent
ACE_EXPORT extern const char XCOMPONENT_TAG[];
ACE_EXPORT extern const char XCOMPONENT_ETS_TAG[];

// ability_component
ACE_EXPORT extern const char ABILITY_COMPONENT_ETS_TAG[];
// Popup
ACE_EXPORT extern const char POPUP_ETS_TAG[];

// remote window
ACE_EXPORT extern const char REMOTE_WINDOW_ETS_TAG[];

// effect view
ACE_EXPORT extern const char EFFECT_COMPONENT_ETS_TAG[];

// button
ACE_EXPORT extern const char MODEL_COMPONENT_TAG[];
ACE_EXPORT extern const char MODEL_ETS_TAG[];

// window scene
ACE_EXPORT extern const char ROOT_SCENE_ETS_TAG[];
ACE_EXPORT extern const char SCREEN_ETS_TAG[];
ACE_EXPORT extern const char WINDOW_SCENE_ETS_TAG[];

// ui_extension_component
ACE_EXPORT extern const char UI_EXTENSION_COMPONENT_TAG[];
ACE_EXPORT extern const char UI_EXTENSION_SURFACE_TAG[];
ACE_EXPORT extern const char UI_EXTENSION_COMPONENT_ETS_TAG[];

// embedded_component
ACE_EXPORT extern const char EMBEDDED_COMPONENT_TAG[];
ACE_EXPORT extern const char EMBEDDED_COMPONENT_ETS_TAG[];

// LocationButton
ACE_EXPORT extern const char LOCATION_BUTTON_COMPONENT_TAG[];
ACE_EXPORT extern const char LOCATION_BUTTON_ETS_TAG[];

// PasteButton
ACE_EXPORT extern const char PASTE_BUTTON_COMPONENT_TAG[];
ACE_EXPORT extern const char PASTE_BUTTON_ETS_TAG[];

// SaveButton
ACE_EXPORT extern const char SAVE_BUTTON_COMPONENT_TAG[];
ACE_EXPORT extern const char SAVE_BUTTON_ETS_TAG[];

// Keyboard
ACE_EXPORT extern const char KEYBOARD_ETS_TAG[];
// Particle
ACE_EXPORT extern const char PARTICLE_COMPONENT_TAG[];
ACE_EXPORT extern const char PARTICLE_ETS_TAG[];

// SelectOverlay
ACE_EXPORT extern const char SELECT_OVERLAY_ETS_TAG[];

// Symbol
ACE_EXPORT extern const char SYMBOL_COMPONENT_TAG[];
ACE_EXPORT extern const char SYMBOL_ETS_TAG[];

// IsolatedComponent
ACE_EXPORT extern const char ISOLATED_COMPONENT_TAG[];
ACE_EXPORT extern const char ISOLATED_COMPONENT_ETS_TAG[];

// DynamicComponent
ACE_EXPORT extern const char DYNAMIC_COMPONENT_TAG[];
ACE_EXPORT extern const char DYNAMIC_COMPONENT_ETS_TAG[];

// ContainerSpan
ACE_EXPORT extern const char CONTAINER_SPAN_COMPONENT_TAG[];
ACE_EXPORT extern const char CONTAINER_SPAN_ETS_TAG[];

//RenderNode
ACE_EXPORT extern const char RENDER_NODE_ETS_TAG[];

//NodeContainer
ACE_EXPORT extern const char NODE_CONTAINER_ETS_TAG[];

//CustomFrameNode
ACE_EXPORT extern const char CUSTOM_FRAME_NODE_ETS_TAG[];

// MovingPhoto
ACE_EXPORT extern const char MOVING_PHOTO_COMPONENT_TAG[];
ACE_FORCE_EXPORT extern const char MOVING_PHOTO_ETS_TAG[];

// CustomSpanNode
ACE_EXPORT extern const char CUSTOM_SPAN_NODE_ETS_TAG[];

// LinearIndicator
ACE_EXPORT extern const char LINEARINDICATOR_COMPONENT_TAG[];
ACE_EXPORT extern const char LINEARINDICATOR_ETS_TAG[];

// ArcList
ACE_EXPORT extern const char ARC_LIST_COMPONENT_TAG[];
ACE_EXPORT extern const char ARC_LIST_ETS_TAG[];

// ArcListItem
ACE_EXPORT extern const char ARC_LIST_ITEM_COMPONENT_TAG[];
ACE_EXPORT extern const char ARC_LIST_ITEM_ETS_TAG[];

// ArcScrollBar
ACE_EXPORT extern const char ARC_SCROLL_BAR_COMPONENT_TAG[];
ACE_EXPORT extern const char ARC_SCROLL_BAR_ETS_TAG[];

// ArcAlphabetIndexer
ACE_EXPORT extern const char ARC_INDEXER_COMPONENT_TAG[];
ACE_EXPORT extern const char ARC_INDEXER_ETS_TAG[];

// Magnifier
ACE_EXPORT extern const char MAGNIFIER_TAG[];

// AccessibilityFocusPaintNode
ACE_EXPORT extern const char ACCESSIBILITY_FOCUS_PAINT_NODE_TAG[];

// LazyVGridLayout
ACE_EXPORT extern const char LAZY_V_GRID_LAYOUT_ETS_TAG[];
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_INSPECTOR_CONSTANTS_H
