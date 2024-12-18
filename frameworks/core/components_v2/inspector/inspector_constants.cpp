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

#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::V2 {
// common attrs
// dimension
const char ATTRS_COMMON_WIDTH[] = "width";
const char ATTRS_COMMON_HEIGHT[] = "height";
const char ATTRS_COMMON_PADDING[] = "padding";
const char ATTRS_COMMON_MARGIN[] = "margin";
const char ATTRS_COMMON_LAYOUT_PRIORITY[] = "layoutPriority";
const char ATTRS_COMMON_LAYOUT_WEIGHT[] = "layoutWeight";
// position
const char ATTRS_COMMON_ALIGN[] = "align";
const char ATTRS_COMMON_DIRECTION[] = "direction";
const char ATTRS_COMMON_POSITION[] = "position";
const char ATTRS_COMMON_OFFSET[] = "margin";
const char ATTRS_COMMON_USE_ALIGN[] = "useAlign";
// layout
const char ATTRS_COMMON_RELATE_PARENT[] = "relateParent";
const char ATTRS_COMMON_ASPECT_RATIO[] = "aspectRatio";
const char ATTRS_COMMON_DISPLAY_PRIORITY[] = "displayPriority";
// border
const char ATTRS_COMMON_BORDER[] = "border";
// background
const char ATTRS_COMMON_BACKGROUND_COLOR[] = "backgroundColor";
// opacity
const char ATTRS_COMMON_OPACITY[] = "opacity";
// visibility
const char ATTRS_COMMON_VISIBILITY[] = "visibility";
// enable
const char ATTRS_COMMON_ENABLE[] = "enable";
// zindex
const char ATTRS_COMMON_ZINDEX[] = "zIndex";

// root view
const char ROOT_ETS_TAG[] = "root";
// stage view
const char STAGE_ETS_TAG[] = "stage";
// overlay view
const char OVERLAY_ETS_TAG[] = "overlay";
// page view
const char PAGE_ETS_TAG[] = "page";
// container modal view (title bar)
const char CONTAINER_MODAL_ETS_TAG[] = "ContainerModal";

const char ATOMIC_SERVICE_ETS_TAG[] = "AtomicService";
const char APP_BAR_ETS_TAG[] = "AppBar";

// js custom view
const char JS_VIEW_ETS_TAG[] = "JsView";
const char JS_VIEW_COMPONENT_TAG[] = "ProxyComponent";
// js lazy foreach node
const char JS_LAZY_FOR_EACH_ETS_TAG[] = "LazyForEach";
// js lazy foreach node
const char JS_FOR_EACH_ETS_TAG[] = "ForEach";
// js lazy foreach node
const char JS_SYNTAX_ITEM_ETS_TAG[] = "SyntaxItem";
// js repeat node
const char JS_REPEAT_ETS_TAG[] = "Repeat";
// js if else node
const char JS_IF_ELSE_ETS_TAG[] = "IfElse";
// js node slot
const char JS_NODE_SLOT_ETS_TAG[] = "NodeSlot";

// toast view
const char TOAST_ETS_TAG[] = "Toast";

// column
const char COLUMN_COMPONENT_TAG[] = "ColumnComponent";
const char COLUMN_ETS_TAG[] = "Column";
const char COLUMN_ATTRS_ALIGN_ITEMS[] = "alignItems";

// panel bar
const char DRAG_BAR_COMPONENT_TAG[] = "DragBarComponent";
const char DRAG_BAR_ETS_TAG[] = "DragBar";

// text
const char TEXT_COMPONENT_TAG[] = "TextComponentV2";
const char TEXT_ETS_TAG[] = "Text";
const char TEXT_ATTRS_OVER_FLOW[] = "textOverflow";
const char TEXT_ATTRS_MAX_LINES[] = "maxLines";

// rich editor
const char RICH_EDITOR_ETS_TAG[] = "RichEditor";
const char RICH_EDITOR_DRAG_ETS_TAG[] = "RichEditorDRAG";

// stack
const char STACK_COMPONENT_TAG[] = "StackComponent";
const char STACK_ETS_TAG[] = "Stack";

// swiper
const char SWIPER_COMPONENT_TAG[] = "SwiperComponent";
const char SWIPER_ETS_TAG[] = "Swiper";
const char SWIPER_INDICATOR_ETS_TAG[] = "SwiperIndicator";
const char SWIPER_LEFT_ARROW_ETS_TAG[] = "LeftArrow";
const char SWIPER_RIGHT_ARROW_ETS_TAG[] = "RightArrow";
const char SWIPER_LEFT_CAPTURE_ETS_TAG[] = "SwiperLeftCapture";
const char SWIPER_RIGHT_CAPTURE_ETS_TAG[] = "SwiperRightCapture";

// tabs
const char TABS_COMPONENT_TAG[] = "TabsComponent";
const char TABS_ETS_TAG[] = "Tabs";

// tab content item
const char TAB_CONTENT_ITEM_COMPONENT_TAG[] = "TabContentItemComponent";
const char TAB_CONTENT_ITEM_ETS_TAG[] = "TabContent";

// tab bar
const char TAB_BAR_COMPONENT_TAG[] = "TabBarComponent";
const char TAB_BAR_ETS_TAG[] = "TabBar";

// navigation view
const char NAVIGATION_VIEW_COMPONENT_TAG[] = "NavigationContainerComponent";
const char NAVIGATION_VIEW_ETS_TAG[] = "Navigation";
const char BAR_ITEM_ETS_TAG[] = "BarItem";
const char TITLE_BAR_ETS_TAG[] = "TitleBar";
const char NAVIGATION_CONTENT_ETS_TAG[] = "NavigationContent";
const char TOOL_BAR_ETS_TAG[] = "ToolBar";
const char NAVIGATION_MENU_ETS_TAG[] = "NavigationMenu";
const char BACK_BUTTON_ETS_TAG[] = "BackButton";
const char BACK_BUTTON_IMAGE_ETS_TAG[] = "BackButtonImage";
const char NAVBAR_CONTENT_ETS_TAG[] = "NavBarContent";
const char NAVBAR_ETS_TAG[] = "NavBar";

// navRouter view
const char NAVROUTER_VIEW_ETS_TAG[] = "NavRouter";

// navDestination view
const char NAVDESTINATION_VIEW_ETS_TAG[] = "NavDestination";
const char NAVDESTINATION_TITLE_BAR_ETS_TAG[] = "NavDestinationTitleBar";
const char NAVDESTINATION_CONTENT_ETS_TAG[] = "NavDestinationContent";

// navigation title view
const char NAVIGATION_TITLE_COMPONENT_TAG[] = "NavigationTitle";

// navigation menus view
const char NAVIGATION_MENUS_COMPONENT_TAG[] = "NavigationMenus";

// row split
const char ROW_SPLIT_COMPONENT_TAG[] = "RowSplitComponent";
const char ROW_SPLIT_ETS_TAG[] = "RowSplit";

// column split
const char COLUMN_SPLIT_COMPONENT_TAG[] = "ColumnSplitComponent";
const char COLUMN_SPLIT_ETS_TAG[] = "ColumnSplit";

// counter
const char COUNTER_COMPONENT_TAG[] = "CounterComponent";
const char COUNTER_ETS_TAG[] = "Counter";

// flex
const char FLEX_COMPONENT_TAG[] = "FlexComponentV2";
const char FLEX_ETS_TAG[] = "Flex";
const char WRAP_COMPONENT_TAG[] = "WrapComponent";
const char WRAP_ETS_TAG[] = "Flex";

// folderStack
const char FOLDER_STACK_COMPONENT_TAG[] = "FolderStackComponent";
const char FOLDER_STACK_ETS_TAG[] = "Folder";
const char HOVER_STACK_ETS_TAG[] = "Hover";
const char CONTROL_PARTS_STACK_ETS_TAG[] = "ControlParts";

// grid
const char GRID_COMPONENT_TAG[] = "GridLayoutComponent";
const char GRID_ETS_TAG[] = "Grid";

// grid-item
const char GRID_ITEM_COMPONENT_TAG[] = "GridLayoutItemComponent";
const char GRID_ITEM_ETS_TAG[] = "GridItem";

// waterFlow
const char WATERFLOW_COMPONENT_TAG[] = "WaterFlowComponent";
const char WATERFLOW_ETS_TAG[] = "WaterFlow";

// flow-item
const char FLOW_ITEM_COMPONENT_TAG[] = "WaterFlowItemComponent";
const char FLOW_ITEM_ETS_TAG[] = "FlowItem";

// list
const char LIST_COMPONENT_TAG[] = "V2::ListComponent";
const char LIST_ETS_TAG[] = "List";

// list-item
const char LIST_ITEM_COMPONENT_TAG[] = "V2::ListItemComponent";
const char LIST_ITEM_ETS_TAG[] = "ListItem";

// list-item-group
const char LIST_ITEM_GROUP_COMPONENT_TAG[] = "V2::ListItemGroupComponent";
const char LIST_ITEM_GROUP_ETS_TAG[] = "ListItemGroup";

// navigator
const char NAVIGATOR_COMPONENT_TAG[] = "NavigatorComponent";
const char NAVIGATOR_ETS_TAG[] = "Navigator";

// panel
const char PANEL_COMPONENT_TAG[] = "SlidingPanelComponentV2";
const char PANEL_ETS_TAG[] = "Panel";
const char PANEL_CLOSE_ICON_ETS_TAG[] = "CloseIcon";

// pattern-lock
const char PATTERN_LOCK_COMPONENT_TAG[] = "PatternLockComponent";
const char PATTERN_LOCK_ETS_TAG[] = "PatternLock";

// row
const char ROW_COMPONENT_TAG[] = "RowComponent";
const char ROW_ETS_TAG[] = "Row";

// rect
const char RECT_ETS_TAG[] = "Rect";

// line
const char LINE_ETS_TAG[] = "Line";

// circle
const char CIRCLE_ETS_TAG[] = "Circle";

// ellipse
const char ELLIPSE_ETS_TAG[] = "Ellipse";

// path
const char PATH_ETS_TAG[] = "Path";

// polygon
const char POLYGON_ETS_TAG[] = "Polygon";

// polyline
const char POLYLINE_ETS_TAG[] = "Polyline";

// shape
const char SHAPE_COMPONENT_TAG[] = "ShapeComponent";
const char SHAPE_ETS_TAG[] = "Shape";

// shape container
const char SHAPE_CONTAINER_COMPONENT_TAG[] = "ShapeContainerComponent";
const char SHAPE_CONTAINER_ETS_TAG[] = "Shape";

// imageAnimator
const char IMAGE_ANIMATOR_COMPONENT_TAG[] = "ImageAnimator";
const char IMAGE_ANIMATOR_ETS_TAG[] = "ImageAnimator";

// image
const char IMAGE_COMPONENT_TAG[] = "ImageComponent";
const char IMAGE_ETS_TAG[] = "Image";

// qrcode
const char QRCODE_COMPONENT_TAG[] = "QrcodeComponent";
const char QRCODE_ETS_TAG[] = "QRCode";

// span
const char SPAN_COMPONENT_TAG[] = "TextSpanComponent";
const char SPAN_ETS_TAG[] = "Span";

// symbol span
const char SYMBOL_SPAN_COMPONENT_TAG[] = "SymbolSpanComponent";
const char SYMBOL_SPAN_ETS_TAG[] = "SymbolSpan";

// image span
const char IMAGE_SPAN_COMPONENT_TAG[] = "ImageSpanComponent";
const char IMAGE_SPAN_ETS_TAG[] = "ImageSpan";

// placeholder span
const char PLACEHOLDER_SPAN_COMPONENT_TAG[] = "PlaceholderSpanComponent";
const char PLACEHOLDER_SPAN_ETS_TAG[] = "PlaceholderSpan";

// blank
const char BOX_COMPONENT_TAG[] = "BoxComponent";
const char BLANK_ETS_TAG[] = "Blank";

// button
const char BUTTON_COMPONENT_TAG[] = "ButtonComponent";
const char BUTTON_ETS_TAG[] = "Button";

// recycle
const char RECYCLE_VIEW_ETS_TAG[] = "__Recycle__";

// common view
const char COMMON_VIEW_ETS_TAG[] = "__Common__";
// option
const char OPTION_COMPONENT_TAG[] = "OptionComponent";
const char OPTION_ETS_TAG[] = "Option";

// divider
const char DIVIDER_COMPONENT_TAG[] = "DividerComponent";
const char DIVIDER_ETS_TAG[] = "Divider";

// checkbox
const char CHECKBOX_COMPONENT_TAG[] = "CheckboxComponent";
const char CHECKBOX_ETS_TAG[] = "Toggle";
const char CHECK_BOX_COMPONENT_TAG[] = "Checkbox";
const char CHECK_BOX_ETS_TAG[] = "Checkbox";

// switch
const char SWITCH_COMPONENT_TAG[] = "SwitchComponent";
const char SWITCH_ETS_TAG[] = "Toggle";

// toggle
const char TOGGLE_COMPONENT_TAG[] = "ToggleComponent";
const char TOGGLE_ETS_TAG[] = "Toggle";

// scroll
const char SCROLL_COMPONENT_TAG[] = "ScrollComponent";
const char SCROLL_ETS_TAG[] = "Scroll";

// calendar
const char CALENDAR_COMPONENT_TAG[] = "calendar";
const char CALENDAR_ETS_TAG[] = "Calendar";

// calendarPicker
const char CALENDAR_PICKER_COMPONENT_TAG[] = "CalendarPickerComponent";
const char CALENDAR_PICKER_ETS_TAG[] = "CalendarPicker";

// badge
const char BADGE_COMPONENT_TAG[] = "BadgeComponent";
const char BADGE_ETS_TAG[] = "Badge";

// search
const char SEARCH_COMPONENT_TAG[] = "SearchComponent";
const char SEARCH_ETS_TAG[] = "Search";
const char SEARCH_Field_ETS_TAG[] = "SearchField";

// formComponent
const char FORM_COMPONENT_TAG[] = "FormComponent";
const char FORM_ETS_TAG[] = "FormComponent";

// formLink
const char FORM_LINK_TAG[] = "FormLink";
const char FORM_LINK_ETS_TAG[] = "FormLink";

// PluginComponent
const char PLUGIN_COMPONENT_TAG[] = "PluginComponent";
const char PLUGIN_ETS_TAG[] = "PluginComponent";

// video
const char VIDEO_COMPONENT_TAG[] = "VideoComponentV2";
const char VIDEO_ETS_TAG[] = "Video";

// AlphabetIndexer
const char INDEXER_COMPONENT_TAG[] = "IndexerComponent";
const char INDEXER_ETS_TAG[] = "AlphabetIndexer";

// slider
const char SLIDER_COMPONENT_TAG[] = "SliderComponent";
const char SLIDER_ETS_TAG[] = "Slider";

// rating
const char RATING_COMPONENT_TAG[] = "RatingComponent";
const char RATING_ETS_TAG[] = "Rating";

// progress
const char PROGRESS_COMPONENT_TAG[] = "ProgressComponent";
const char PROGRESS_ETS_TAG[] = "Progress";

// datapanel
const char DATA_PANEL_COMPONENT_TAG[] = "PercentageDataPanelComponent";
const char DATA_PANEL_ETS_TAG[] = "DataPanel";

// sheet
const char SHEET_COMPONENT_TAG[] = "SheetComponent";
const char SHEET_ETS_TAG[] = "Sheet";
const char SHEET_MASK_TAG[] = "SheetMask";
const char SHEET_PAGE_TAG[] = "SheetPage";
const char SHEET_WRAPPER_TAG[] = "SheetWrapper";

// full screen modal
const char MODAL_PAGE_TAG[] = "ModalPage";

// hyperlink
const char HYPERLINK_COMPONENT_TAG[] = "HyperlinkComponent";
const char HYPERLINK_ETS_TAG[] = "Hyperlink";

// stepper
const char STEPPER_COMPONENT_TAG[] = "StepperComponent";
const char STEPPER_ETS_TAG[] = "Stepper";

// stepperItem
const char STEPPER_ITEM_COMPONENT_TAG[] = "StepperItemComponentV2";
const char STEPPER_ITEM_ETS_TAG[] = "StepperItem";

// scrollbar
const char SCROLL_BAR_COMPONENT_TAG[] = "ScrollBarComponent";
const char SCROLL_BAR_ETS_TAG[] = "ScrollBar";

// refresh
const char REFRESH_COMPONENT_TAG[] = "RefreshComponent";
const char REFRESH_ETS_TAG[] = "Refresh";

// datePicker
const char DATE_PICKER_COMPONENT_TAG[] = "PickerDateComponent";
const char DATE_PICKER_ETS_TAG[] = "DatePicker";
const char TIME_PICKER_COMPONENT_TAG[] = "PickerTimeComponent";
const char TIME_PICKER_ETS_TAG[] = "TimePicker";

// Radio
const char RADIO_COMPONENT_TAG[] = "RadioComponent<VALUE_TYPE>";
const char RADIO_ETS_TAG[] = "Radio";

// gauge
const char GAUGE_COMPONENT_TAG[] = "Gauge";
const char GAUGE_ETS_TAG[] = "Gauge";
const char GAUGE_DESCRIPTION_TAG[] = "GaugeDescription";
const char GAUGE_INDICATOR_TAG[] = "GaugeIndicator";

// gridContainer
const char GRIDCONTAINER_COMPONENT_TAG[] = "GridContainer";
const char GRIDCONTAINER_ETS_TAG[] = "GridContainer";

// gridCol
const char GRID_COL_COMPONENT_TAG[] = "GridColComponent";
const char GRID_COL_ETS_TAG[] = "GridCol";

// gridRow
const char GRID_ROW_COMPONENT_TAG[] = "GridRowComponent";
const char GRID_ROW_ETS_TAG[] = "GridRow";

// relativeContainer
const char RELATIVE_CONTAINER_COMPONENT_TAG[] = "RelativeContainerComponent";
const char RELATIVE_CONTAINER_ETS_TAG[] = "RelativeContainer";

// menu
const char MENU_COMPONENT_TAG[] = "MenuComponent";
const char MENU_TAG[] = "menu";
const char MENU_ETS_TAG[] = "Menu";
const char MENU_ITEM_ETS_TAG[] = "MenuItem";
const char MENU_ITEM_GROUP_ETS_TAG[] = "MenuItemGroup";
const char MENU_WRAPPER_ETS_TAG[] = "MenuWrapper";
const char MENU_PREVIEW_ETS_TAG[] = "MenuPreview";

// textarea
const char TEXTAREA_COMPONENT_TAG[] = "TextFieldComponent";
const char TEXTAREA_ETS_TAG[] = "TextArea";

// textdrag
const char TEXTDRAG_ETS_TAG[] = "TextDrag";

// textinput
const char TEXTINPUT_COMPONENT_TAG[] = "TextInput";
const char TEXTINPUT_ETS_TAG[] = "TextInput";

// texttimer
const char TEXTTIMER_COMPONENT_TAG[] = "TextTimerComponent";
const char TEXTTIMER_ETS_TAG[] = "TextTimer";

// select
const char SELECT_COMPONENT_TAG[] = "SelectComponent";
const char SELECT_ETS_TAG[] = "Select";

// select_popup
const char SELECT_POPUP_COMPONENT_TAG[] = "SelectPopupComponent";
const char SELECT_POPUP_ETS_TAG[] = "SelectPopup";

// marquee
const char MARQUEE_COMPONENT_TAG[] = "MarqueeComponent";
const char MARQUEE_ETS_TAG[] = "Marquee";

// textclock
const char TEXTCLOCK_COMPONENT_TAG[] = "TextClockComponent";
const char TEXTCLOCK_ETS_TAG[] = "TextClock";

// textpicker
const char TEXT_PICKER_COMPONENT_TAG[] = "PickerTextComponent";
const char TEXT_PICKER_ETS_TAG[] = "TextPicker";

// pickertextdialog
const char PICKER_TEXT_DIALOG_COMPONENT_TAG[] = "pickerTextDialog";
const char PICKER_TEXT_DIALOG_ETS_TAG[] = "pickerTextDialog";

// canvas
const char CANVAS_COMPONENT_TAG[] = "CustomPaintComponent";
const char CANVAS_ETS_TAG[] = "Canvas";

// ActionSheet
const char ACTION_SHEET_DIALOG_COMPONENT_TAG[] = "ActionSheet";
const char ACTION_SHEET_DIALOG_ETS_TAG[] = "ActionSheet";

// AlertDialog
const char ALERT_DIALOG_COMPONENT_TAG[] = "AlertDialog";
const char ALERT_DIALOG_ETS_TAG[] = "AlertDialog";

// customdialog
const char CUSTOM_DIALOG_COMPONENT_TAG[] = "CustomDialog";
const char CUSTOM_DIALOG_ETS_TAG[] = "CustomDialog";

// datePickerdialog
const char DATE_PICKER_DIALOG_COMPONENT_TAG[] = "DatePickerDialog";
const char DATE_PICKER_DIALOG_ETS_TAG[] = "DatePickerDialog";

// Normal dialog
const char DIALOG_COMPONENT_TAG[] = "Dialog";
const char DIALOG_ETS_TAG[] = "Dialog";

// sideBar
const char SIDE_BAR_COMPONENT_TAG[] = "SideBarContainerComponent";
const char SIDE_BAR_ETS_TAG[] = "SideBarContainer";

// loadingProgress
const char LOADING_PROGRESS_COMPONENT_TAG[] = "LoadingProgressComponent";
const char LOADING_PROGRESS_ETS_TAG[] = "LoadingProgress";

// checkboxGroup
const char CHECKBOXGROUP_COMPONENT_TAG[] = "CheckboxGroupComponent";
const char CHECKBOXGROUP_ETS_TAG[] = "CheckboxGroup";

// timePickerdialog
const char TIME_PICKER_DIALOG_COMPONENT_TAG[] = "TimePickerDialog";
const char TIME_PICKER_DIALOG_ETS_TAG[] = "TimePickerDialog";

// web
const char WEB_COMPONENT_TAG[] = "WebComponent";
const char WEB_ETS_TAG[] = "Web";
const char WEB_CORE_TAG[] = "WebCore";

// richText
const char RICH_TEXT_COMPONENT_TAG[] = "RichTextComponent";
const char RICH_TEXT_ETS_TAG[] = "RichText";

// xcomponent
const char XCOMPONENT_TAG[] = "XComponentComponent";
const char XCOMPONENT_ETS_TAG[] = "XComponent";

// ability_component
const char ABILITY_COMPONENT_ETS_TAG[] = "AbilityComponent";
// Popup
const char POPUP_ETS_TAG[] = "Popup";

// remote window
const char REMOTE_WINDOW_ETS_TAG[] = "RemoteWindow";

// effect view
const char EFFECT_COMPONENT_ETS_TAG[] = "EffectComponent";

// Model
const char MODEL_COMPONENT_TAG[] = "Component3DComponent";
const char MODEL_ETS_TAG[] = "Component3D";

// window scene
ACE_EXPORT const char ROOT_SCENE_ETS_TAG[] = "RootScene";
ACE_EXPORT const char SCREEN_ETS_TAG[] = "Screen";
ACE_EXPORT const char WINDOW_SCENE_ETS_TAG[] = "WindowScene";

// ui_extension_component
const char UI_EXTENSION_COMPONENT_TAG[] = "UIExtensionComponent";
const char UI_EXTENSION_SURFACE_TAG[] = "UIExtensionSurface";
const char UI_EXTENSION_COMPONENT_ETS_TAG[] = "UIExtensionComponent";

// embedded_component
const char EMBEDDED_COMPONENT_TAG[] = "EmbeddedComponent";
const char EMBEDDED_COMPONENT_ETS_TAG[] = "EmbeddedComponent";

// LocationButton
const char LOCATION_BUTTON_COMPONENT_TAG[] = "LocationButtonComponent";
const char LOCATION_BUTTON_ETS_TAG[] = "LocationButton";

// PasteButton
const char PASTE_BUTTON_COMPONENT_TAG[] = "PasteButtonComponent";
const char PASTE_BUTTON_ETS_TAG[] = "PasteButton";

// SaveButton
const char SAVE_BUTTON_COMPONENT_TAG[] = "SaveButtonComponent";
const char SAVE_BUTTON_ETS_TAG[] = "SaveButton";

// Keyboard
const char KEYBOARD_ETS_TAG[] = "Keyboard";
// Particle
const char PARTICLE_COMPONENT_TAG[] = "ParticleComponent";
const char PARTICLE_ETS_TAG[] = "Particle";

// SelectOverlay
const char SELECT_OVERLAY_ETS_TAG[] = "SelectOverlay";

// Symbol
const char SYMBOL_COMPONENT_TAG[] = "SymbolGlyphComponent";
const char SYMBOL_ETS_TAG[] = "SymbolGlyph";

// IsolatedComponent
const char ISOLATED_COMPONENT_TAG[] = "IsolatedComponent";
const char ISOLATED_COMPONENT_ETS_TAG[] = "IsolatedComponent";

// ContainerSpan
const char CONTAINER_SPAN_COMPONENT_TAG[] = "ContainerSpanComponent";
const char CONTAINER_SPAN_ETS_TAG[] = "ContainerSpan";

//RenderNode
const char RENDER_NODE_ETS_TAG[] = "RenderNode";

//CustomFrameNode
const char CUSTOM_FRAME_NODE_ETS_TAG[] = "CustomFrameNode";

//NodeContainer
const char NODE_CONTAINER_ETS_TAG[] = "NodeContainer";

// MovingPhoto
const char MOVING_PHOTO_COMPONENT_TAG[] = "MovingPhotoComponent";
const char MOVING_PHOTO_ETS_TAG[] = "MovingPhoto";

// CustomSpanNode
const char CUSTOM_SPAN_NODE_ETS_TAG[] = "CustomSpanNode";
} // namespace OHOS::Ace::V2
