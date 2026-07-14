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

#include "core/components_v2/inspector/inspector_composed_component.h"
#include "core/accessibility/accessibility_manager.h"

#include "base/utils/linear_map.h"
#include "compatible/components/component_loader.h"

#include "core/common/dynamic_module_helper.h"
#include "ui/base/utils/utils.h"
#include "core/components_v2/inspector/actionsheetdialog_composed_element.h"
#include "core/components_v2/inspector/alertdialog_composed_element.h"
#include "core/components_v2/inspector/blank_composed_element.h"
#include "core/components_v2/inspector/button_composed_element.h"
#include "core/components_v2/inspector/calendar_composed_element.h"
#include "core/components_v2/inspector/checkboxGroup_composed_element.h"
#include "core/components_v2/inspector/checkbox_composed_element.h"
#include "core/components_v2/inspector/column_composed_element.h"
#include "core/components_v2/inspector/column_split_composed_element.h"
#include "core/components_v2/inspector/counter_composed_element.h"
#include "core/components_v2/inspector/customdialog_composed_element.h"
#include "core/components_v2/inspector/data_panel_composed_element.h"
#include "core/components_v2/inspector/divider_composed_element.h"
#include "core/components_v2/inspector/flex_composed_element.h"
#include "core/components_v2/inspector/gauge_composed_element.h"
#include "core/components_v2/inspector/grid_composed_element.h"
#include "core/components_v2/inspector/grid_item_composed_element.h"
#include "core/components_v2/inspector/hyperlink_composed_element.h"
#include "core/components_v2/inspector/image_composed_element.h"
#include "core/components_v2/inspector/indexer_composed_element.h"
#include "core/components_v2/inspector/loading_progress_composed_element.h"
#include "core/components_v2/inspector/menu_composed_element.h"
#include "core/components_v2/inspector/navigation_composed_element.h"
#include "core/components_v2/inspector/navigation_title_composed_element.h"
#include "core/components_v2/inspector/navigator_composed_element.h"
#include "core/components_v2/inspector/panel_composed_element.h"
#include "core/components_v2/inspector/pattern_lock_composed_element.h"
#include "core/components_v2/inspector/progress_composed_element.h"
#include "core/components_v2/inspector/radio_composed_element.h"
#include "core/components_v2/inspector/relative_container_composed_element.h"
#include "core/components_v2/inspector/row_composed_element.h"
#include "core/components_v2/inspector/row_split_composed_element.h"
#include "core/components_v2/inspector/scroll_bar_composed_element.h"
#include "core/components_v2/inspector/scroll_composed_element.h"
#include "core/components_v2/inspector/select_composed_element.h"
#include "core/components_v2/inspector/shape_composed_element.h"
#include "core/components_v2/inspector/shape_container_composed_element.h"
#include "core/components_v2/inspector/sheet_composed_element.h"
#include "core/components_v2/inspector/side_bar_composed_element.h"
#include "core/components_v2/inspector/slider_composed_element.h"
#include "core/components_v2/inspector/span_composed_element.h"
#include "core/components_v2/inspector/stack_composed_element.h"
#include "core/components_v2/inspector/text_clock_composed_element.h"
#include "core/components_v2/inspector/text_composed_element.h"
#include "core/components_v2/inspector/texttimer_composed_element.h"
#include "core/components_v2/inspector/water_flow_composed_element.h"
#include "core/components_v2/inspector/water_flow_item_composed_element.h"
#include "core/components_v2/inspector/wrap_composed_element.h"

namespace OHOS::Ace::V2 {

namespace {

using CreateElementFunc = RefPtr<InspectorComposedElement>(*)(const std::string& id);
RefPtr<InspectorComposedElement> DynamicCreateInspectorElement(const std::string tag, const std::string& id)
{
    auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName(tag.c_str());
    return loader ? loader->CreateInspectorElement(id) : nullptr;
}

template<typename T>
RefPtr<InspectorComposedElement> MakeInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<T>(id);
}

static constexpr LinearMapNode<CreateElementFunc> CREATE_ELEMENT_MAP[] = {
    { ACTION_SHEET_DIALOG_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::ActionSheetDialogComposedElement>(id);
        } },
    { ALERT_DIALOG_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::AlertDialogComposedElement>(id);
        } },
    { BADGE_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_BADGE, id); } },
    { BOX_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::BlankComposedElement>(id);
        } },
    { BUTTON_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::ButtonComposedElement>(id);
        } },
    { CALENDAR_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::CalendarComposedElement>(id);
        } },
    { CANVAS_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::InspectorComposedElement>(id); } },
    { CHECKBOXGROUP_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::CheckboxGroupComposedElement>(id);
        } },
    { CHECKBOX_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::CheckboxComposedElement>(id);
        } },
    { CHECK_BOX_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::CheckboxComposedElement>(id);
        } },
    { COLUMN_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::ColumnComposedElement>(id);
        } },
    { COLUMN_SPLIT_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::ColumnSplitComposedElement>(id);
        } },
    { COUNTER_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::CounterComposedElement>(id);
        } },
    { CUSTOM_DIALOG_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::CustomDialogComposedElement>(id);
        } },
    { DATA_PANEL_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::DataPanelComposedElement>(id);
        } },
    { DATE_PICKER_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DATE_PICKER_COMPONENT_LOADER_TAG, id); } },
    { DATE_PICKER_DIALOG_COMPONENT_TAG,
        [](const std::string& id) {
            return DynamicCreateInspectorElement(DATE_PICKER_DIALOG_COMPONENT_LOADER_TAG, id);
        } },
    { DIALOG_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::InspectorComposedElement>(id); } },
    { DIVIDER_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::DividerComposedElement>(id);
        } },
    { FLEX_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::FlexComposedElement>(id);
        } },
    { FLOW_ITEM_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::WaterFlowItemComposedElement>(id);
        } },
    { FORM_COMPONENT_TAG, [](const std::string& id) { return AceType::MakeRefPtr<V2::InspectorComposedElement>(id); } },
    { GAUGE_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::GaugeComposedElement>(id);
        } },
    { GRIDCONTAINER_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_GRID_CONTAINER, id); } },
    { GRID_COL_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_GRID_COLUMN, id); } },
    { GRID_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::GridComposedElement>(id);
        } },
    { GRID_ITEM_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::GridItemComposedElement>(id);
        } },
    { GRID_ROW_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_GRID_ROW, id); } },
    { HYPERLINK_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::HyperlinkComposedElement>(id);
        } },
    { IMAGE_ANIMATOR_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_IMAGE_ANIMATOR, id); } },
    { IMAGE_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::ImageComposedElement>(id);
        } },
    { INDEXER_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::IndexerComposedElement>(id);
        } },
    { JS_VIEW_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::InspectorComposedElement>(id); } },
    { LIST_COMPONENT_TAG, [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_LIST, id); } },
    { LIST_ITEM_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_LIST_ITEM, id); } },
    { LIST_ITEM_GROUP_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_LIST_ITEM_GROUP, id); } },
    { LOADING_PROGRESS_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::LoadingProgressComposedElement>(id);
        } },
    { MARQUEE_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_MARQUEE, id); } },
    { MENU_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::MenuComposedElement>(id);
        } },
    { MOVING_PHOTO_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::InspectorComposedElement>(id); } },
    { NAVIGATION_MENUS_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_NAVIGATION_MENU, id); } },
    { NAVIGATION_TITLE_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::NavigationTitleComposedElement>(id);
        } },
    { NAVIGATION_VIEW_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::NavigationComposedElement>(id);
        } },
    { NAVIGATOR_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::NavigatorComposedElement>(id);
        } },
    { PANEL_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::PanelComposedElement>(id);
        } },
    { PATTERN_LOCK_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::PatternLockComposedElement>(id);
        } },
    { PICKER_TEXT_DIALOG_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(PICKER_TEXT_DIALOG_COMPONENT_LOADER_TAG, id); } },
    { PLUGIN_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::InspectorComposedElement>(id); } },
    { PROGRESS_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::ProgressComposedElement>(id);
        } },
    { QRCODE_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_QRCODE, id); } },
    { RADIO_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::RadioComposedElement>(id);
        } },
    { RATING_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_RATING, id); } },
    { REFRESH_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_REFRESH, id); } },
    { RELATIVE_CONTAINER_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::RelativeContainerComposedElement>(id);
        } },
    { RICH_TEXT_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::InspectorComposedElement>(id); } },
    { ROW_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::RowComposedElement>(id);
        } },
    { ROW_SPLIT_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::RowSplitComposedElement>(id);
        } },
    { SCROLL_BAR_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::ScrollBarComposedElement>(id);
        } },
    { SCROLL_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::ScrollComposedElement>(id);
        } },
    { SEARCH_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_SEARCH, id); } },
    { SELECT_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::SelectComposedElement>(id);
        } },
    { SHAPE_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::ShapeComposedElement>(id);
        } },
    { SHAPE_CONTAINER_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::ShapeContainerComposedElement>(id);
        } },
    { SHEET_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::SheetComposedElement>(id);
        } },
    { SIDE_BAR_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::SideBarComposedElement>(id);
        } },
    { SLIDER_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::SliderComposedElement>(id);
        } },
    { SPAN_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::SpanComposedElement>(id);
        } },
    { STACK_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::StackComposedElement>(id);
        } },
    { STEPPER_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_STEPPER, id); } },
    { STEPPER_ITEM_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_STEPPER_ITEM, id); } },
    { SWIPER_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(SWIPER_ETS_TAG, id); } },
    { SWITCH_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_SWITCH, id); } },
    { TABS_COMPONENT_TAG, [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_TABS, id); } },
    { TAB_CONTENT_ITEM_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_TAB_CONTENT, id); } },
    { TEXTAREA_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_TEXTAREA, id); } },
    { TEXTCLOCK_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::TextClockComposedElement>(id);
        } },
    { TEXTINPUT_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_INPUT, id); } },
    { TEXTTIMER_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::TextTimerComposedElement>(id);
        } },
    { TEXT_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::TextComposedElement>(id);
        } },
    { TEXT_PICKER_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(TEXT_PICKER_COMPONENT_LOADER_TAG, id); } },
    { TIME_PICKER_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(TIME_PICKER_COMPONENT_LOADER_TAG, id); } },
    { TIME_PICKER_DIALOG_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(TIME_PICKER_DIALOG_COMPONENT_LOADER_TAG, id); } },
    { TOGGLE_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_TOGGLE, id); } },
    { VIDEO_COMPONENT_TAG,
        [](const std::string& id) { return DynamicCreateInspectorElement(DOM_NODE_TAG_VIDEO, id); } },
    { WATERFLOW_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::WaterFlowComposedElement>(id);
        } },
    { WEB_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::InspectorComposedElement>(id); } },
    { WRAP_COMPONENT_TAG,
        [](const std::string& id) {
            return MakeInspectorElement<V2::WrapComposedElement>(id);
        } },
    { XCOMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::InspectorComposedElement>(id); } },
};

} // namespace

const std::unordered_map<std::string, std::string> COMPONENT_TAG_TO_ETS_TAG_MAP {
    { COLUMN_COMPONENT_TAG, COLUMN_ETS_TAG },
    { TEXT_COMPONENT_TAG, TEXT_ETS_TAG },
    { COLUMN_SPLIT_COMPONENT_TAG, COLUMN_SPLIT_ETS_TAG },
    { COUNTER_COMPONENT_TAG, COUNTER_ETS_TAG },
    { NAVIGATION_VIEW_COMPONENT_TAG, NAVIGATION_VIEW_ETS_TAG },
    { ROW_SPLIT_COMPONENT_TAG, ROW_SPLIT_ETS_TAG },
    { STACK_COMPONENT_TAG, STACK_ETS_TAG },
    { SWIPER_COMPONENT_TAG, SWIPER_ETS_TAG },
    { INDICATOR_COMPONENT_TAG, INDICATOR_ETS_TAG },
    { TAB_CONTENT_ITEM_COMPONENT_TAG, TAB_CONTENT_ITEM_ETS_TAG },
    { TABS_COMPONENT_TAG, TABS_ETS_TAG },
    { FLEX_COMPONENT_TAG, FLEX_ETS_TAG },
    { WRAP_COMPONENT_TAG, WRAP_ETS_TAG },
    { GRID_COMPONENT_TAG, GRID_ETS_TAG },
    { GRID_ITEM_COMPONENT_TAG, GRID_ITEM_ETS_TAG },
    { WATERFLOW_COMPONENT_TAG, WATERFLOW_ETS_TAG },
    { FLOW_ITEM_COMPONENT_TAG, FLOW_ITEM_ETS_TAG },
    { LIST_COMPONENT_TAG, LIST_ETS_TAG },
    { LIST_ITEM_COMPONENT_TAG, LIST_ITEM_ETS_TAG },
    { LIST_ITEM_GROUP_COMPONENT_TAG, LIST_ITEM_GROUP_ETS_TAG },
    { NAVIGATOR_COMPONENT_TAG, NAVIGATOR_ETS_TAG },
    { PANEL_COMPONENT_TAG, PANEL_ETS_TAG },
    { PATTERN_LOCK_COMPONENT_TAG, PATTERN_LOCK_ETS_TAG },
    { ROW_COMPONENT_TAG, ROW_ETS_TAG },
    { IMAGE_ANIMATOR_COMPONENT_TAG, IMAGE_ANIMATOR_ETS_TAG },
    { SHAPE_CONTAINER_COMPONENT_TAG, SHAPE_CONTAINER_ETS_TAG },
    { SHAPE_COMPONENT_TAG, SHAPE_ETS_TAG },
    { IMAGE_COMPONENT_TAG, IMAGE_ETS_TAG },
    { QRCODE_COMPONENT_TAG, QRCODE_ETS_TAG },
    { SPAN_COMPONENT_TAG, SPAN_ETS_TAG },
    { PLACEHOLDER_SPAN_COMPONENT_TAG, PLACEHOLDER_SPAN_ETS_TAG },
    { BOX_COMPONENT_TAG, BLANK_ETS_TAG },
    { BUTTON_COMPONENT_TAG, BUTTON_ETS_TAG },
    { DIVIDER_COMPONENT_TAG, DIVIDER_ETS_TAG },
    { CHECKBOX_COMPONENT_TAG, CHECKBOX_ETS_TAG },
    { CHECK_BOX_COMPONENT_TAG, CHECK_BOX_ETS_TAG },
    { SWITCH_COMPONENT_TAG, SWITCH_ETS_TAG },
    { TOGGLE_COMPONENT_TAG, TOGGLE_ETS_TAG },
    { SCROLL_COMPONENT_TAG, SCROLL_ETS_TAG },
    { CALENDAR_COMPONENT_TAG, CALENDAR_ETS_TAG },
    { CALENDAR_PICKER_COMPONENT_TAG, CALENDAR_PICKER_ETS_TAG },
    { BADGE_COMPONENT_TAG, BADGE_ETS_TAG },
    { SEARCH_COMPONENT_TAG, SEARCH_ETS_TAG },
    { FORM_COMPONENT_TAG, FORM_ETS_TAG },
    { PLUGIN_COMPONENT_TAG, PLUGIN_ETS_TAG },
    { VIDEO_COMPONENT_TAG, VIDEO_ETS_TAG },
    { INDEXER_COMPONENT_TAG, INDEXER_ETS_TAG },
    { SLIDER_COMPONENT_TAG, SLIDER_ETS_TAG },
    { RATING_COMPONENT_TAG, RATING_ETS_TAG },
    { PROGRESS_COMPONENT_TAG, PROGRESS_ETS_TAG },
    { DATA_PANEL_COMPONENT_TAG, DATA_PANEL_ETS_TAG },
    { SHEET_COMPONENT_TAG, SHEET_ETS_TAG },
    { HYPERLINK_COMPONENT_TAG, HYPERLINK_ETS_TAG },
    { STEPPER_COMPONENT_TAG, STEPPER_ETS_TAG },
    { STEPPER_ITEM_COMPONENT_TAG, STEPPER_ITEM_ETS_TAG },
    { SCROLL_BAR_COMPONENT_TAG, SCROLL_BAR_ETS_TAG },
    { REFRESH_COMPONENT_TAG, REFRESH_ETS_TAG },
    { DATE_PICKER_COMPONENT_TAG, DATE_PICKER_ETS_TAG },
    { TIME_PICKER_COMPONENT_TAG, TIME_PICKER_ETS_TAG },
    { RADIO_COMPONENT_TAG, RADIO_ETS_TAG },
    { GRIDCONTAINER_COMPONENT_TAG, GRIDCONTAINER_ETS_TAG },
    { GRID_COL_COMPONENT_TAG, GRID_COL_ETS_TAG },
    { GRID_ROW_COMPONENT_TAG, GRID_ROW_ETS_TAG },
    { MENU_COMPONENT_TAG, MENU_ETS_TAG },
    { MENU_TAG, MENU_ETS_TAG },
    { TEXTAREA_COMPONENT_TAG, TEXTAREA_ETS_TAG },
    { TEXTINPUT_COMPONENT_TAG, TEXTINPUT_ETS_TAG },
    { MARQUEE_COMPONENT_TAG, MARQUEE_ETS_TAG },
    { SELECT_COMPONENT_TAG, SELECT_ETS_TAG },
    { TEXTCLOCK_COMPONENT_TAG, TEXTCLOCK_ETS_TAG },
    { TEXTTIMER_COMPONENT_TAG, TEXTTIMER_ETS_TAG },
    { TEXT_PICKER_COMPONENT_TAG, TEXT_PICKER_ETS_TAG },
    { PICKER_TEXT_DIALOG_COMPONENT_TAG, PICKER_TEXT_DIALOG_ETS_TAG },
    { CANVAS_COMPONENT_TAG, CANVAS_ETS_TAG },
    { ACTION_SHEET_DIALOG_COMPONENT_TAG, ACTION_SHEET_DIALOG_ETS_TAG },
    { ALERT_DIALOG_COMPONENT_TAG, ALERT_DIALOG_ETS_TAG },
    { CUSTOM_DIALOG_COMPONENT_TAG, CUSTOM_DIALOG_ETS_TAG },
    { DATE_PICKER_DIALOG_COMPONENT_TAG, DATE_PICKER_DIALOG_ETS_TAG },
    { SIDE_BAR_COMPONENT_TAG, SIDE_BAR_ETS_TAG },
    { LOADING_PROGRESS_COMPONENT_TAG, LOADING_PROGRESS_ETS_TAG },
    { CHECKBOXGROUP_COMPONENT_TAG, CHECKBOXGROUP_ETS_TAG },
    { TIME_PICKER_DIALOG_COMPONENT_TAG, TIME_PICKER_DIALOG_ETS_TAG },
    { WEB_COMPONENT_TAG, WEB_ETS_TAG },
    { RICH_TEXT_COMPONENT_TAG, RICH_TEXT_ETS_TAG },
    { XCOMPONENT_TAG, XCOMPONENT_ETS_TAG },
    { JS_VIEW_COMPONENT_TAG, JS_VIEW_ETS_TAG },
    { RELATIVE_CONTAINER_COMPONENT_TAG, RELATIVE_CONTAINER_ETS_TAG },
    { UI_EXTENSION_COMPONENT_TAG, UI_EXTENSION_COMPONENT_ETS_TAG },
    { LOCATION_BUTTON_COMPONENT_TAG, LOCATION_BUTTON_ETS_TAG },
    { PASTE_BUTTON_COMPONENT_TAG, PASTE_BUTTON_ETS_TAG },
    { SAVE_BUTTON_COMPONENT_TAG, SAVE_BUTTON_ETS_TAG },
    { PARTICLE_COMPONENT_TAG, PARTICLE_ETS_TAG },
    { SYMBOL_COMPONENT_TAG, SYMBOL_ETS_TAG },
    { SYMBOL_SPAN_COMPONENT_TAG, SYMBOL_SPAN_ETS_TAG },
    { ISOLATED_COMPONENT_TAG, ISOLATED_COMPONENT_ETS_TAG },
    { CONTAINER_SPAN_COMPONENT_TAG, CONTAINER_SPAN_ETS_TAG },
    { EMBEDDED_COMPONENT_TAG, EMBEDDED_COMPONENT_ETS_TAG },
    { MOVING_PHOTO_COMPONENT_TAG, MOVING_PHOTO_ETS_TAG },
    { ARC_LIST_COMPONENT_TAG, ARC_LIST_ETS_TAG },
    { ARC_LIST_ITEM_COMPONENT_TAG, ARC_LIST_ITEM_ETS_TAG },
    { ARC_SCROLL_BAR_COMPONENT_TAG, ARC_SCROLL_BAR_ETS_TAG },
    { ARC_INDEXER_COMPONENT_TAG, ARC_INDEXER_ETS_TAG },
};

thread_local int32_t InspectorComposedComponent::composedElementId_ = 1;

RefPtr<Element> InspectorComposedComponent::CreateElement()
{
    auto index =
        BinarySearchFindIndex(CREATE_ELEMENT_MAP, ArraySize(CREATE_ELEMENT_MAP), GetName().c_str());
    if (index >= 0) {
        auto inspectorElement = CREATE_ELEMENT_MAP[index].value(id_);
        inspectorElement->SetInspectorTag(GetName());
        inspectorElement->SetDebugLine(GetDebugLine());
        inspectorElement->SetViewId(viewId_);
        inspectorElement->SetKey(GetInspectorKey());
        return inspectorElement;
    }
    return nullptr;
}

RefPtr<AccessibilityManager> InspectorComposedComponent::GetAccessibilityManager()
{
    auto container = OHOS::Ace::Container::Current();
    if (!container) {
        LOGE("container is nullptr");
        return nullptr;
    }
    auto front = container->GetFrontend();
    if (!front) {
        LOGE("front is nullptr");
        return nullptr;
    }
    auto accessibilityManager = front->GetAccessibilityManager();
    return accessibilityManager;
}

bool InspectorComposedComponent::HasInspectorFinished(const std::string& tag)
{
    auto index = BinarySearchFindIndex(CREATE_ELEMENT_MAP, ArraySize(CREATE_ELEMENT_MAP), tag.c_str());
    return index >= 0;
}

RefPtr<AccessibilityNode> InspectorComposedComponent::CreateAccessibilityNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex)
{
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("get AccessibilityManager failed");
        return nullptr;
    }

    auto node = accessibilityManager->CreateAccessibilityNode(
        InspectorComposedComponent::GetEtsTag(tag), nodeId, parentNodeId, itemIndex);
    return node;
}

std::string InspectorComposedComponent::GetEtsTag(const std::string& tag)
{
    auto iter = COMPONENT_TAG_TO_ETS_TAG_MAP.find(tag);
    if (iter == COMPONENT_TAG_TO_ETS_TAG_MAP.end()) {
        return tag;
    }
    return iter->second;
}

std::string InspectorComposedComponent::GenerateId()
{
    return std::to_string(composedElementId_++);
}

} // namespace OHOS::Ace::V2
