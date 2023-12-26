/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_blank_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_button_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_checkbox_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_checkboxgroup_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_column_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_column_split_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_common_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_counter_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_date_picker_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_divider_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_grid_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_grid_col_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_grid_item_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_grid_row_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_hyperlink_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_image_animator_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_image_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_image_span_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_list_item_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_menu_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_menu_item_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_nav_destination_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_nav_router_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_navigation_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_navigator_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_node_container_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_panel_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_pattern_lock_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_progress_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_render_node_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_text_area_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_text_input_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_swiper_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_text_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_toggle_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_radio_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_rating_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_rich_editor_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_row_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_row_split_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_search_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_select_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_slider_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_span_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_stack_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_stepper_item_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_tabs_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_textpicker_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_timepicker_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_video_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_line_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_path_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_polygon_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_polyline_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_qrcode_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_water_flow_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_side_bar_container_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_marquee_modifier.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/pipeline/base/element_register.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_calendar_picker_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_alphabet_indexer_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_data_panel_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_gauge_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_scroll_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_common_shape_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_shape_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_rect_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_list_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_list_item_group_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_text_timer_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_loading_progress_modifier.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_text_clock_modifier.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_plugin_modifier.h"
#endif
#ifdef XCOMPONENT_SUPPORTED
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_xcomponent_modifier.h"
#endif
#ifdef FORM_SUPPORTED
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_form_component_modifier.h"
#endif

using namespace OHOS::Ace::NG;

NodeHandle GetFrameNodeById(int nodeId)
{
    auto node = OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(nodeId);
    return OHOS::Ace::AceType::RawPtr(node);
}

int64_t GetUIState(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, 0);
    return eventHub->GetCurrentUIState();
}

void SetSupportedUIState(NodeHandle node, uint64_t state)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->AddSupportedState(static_cast<uint64_t>(state));
}

static struct ArkUINodeAPI impl = {
    GetFrameNodeById,
    GetUIState,
    SetSupportedUIState,
    GetCommonModifier,
    GetCheckboxGroupModifier,
    GetCounterModifier,
    GetRowModifier,
    GetRowSplitModifier,
    GetTextModifier,
    GetButtonModifier,
    GetToggleModifier,
    GetImageSpanModifier,
    GetBlankModifier,
    GetSearchModifier,
    GetSelectModifier,
    GetRadioModifier,
    GetCheckboxModifier,
    GetTimepickerModifier,
    GetTextpickerModifier,
    GetRatingModifier,
    GetSliderModifier,
    GetDividerModifier,
    GetStackModifier,
    GetNavDestinationModifier,
    GetGridModifier,
    GetGridColModifier,
    GetGridRowModifier,
    GetPanelModifier,
    GetTextAreaModifier,
    GetNavigationModifier,
    GetColumnModifier,
    GetRichEditorModifier,
    GetImageModifier,
    GetVideoModifier,
    GetNavigatorModifier,
    GetNavRouterModifier,
    GetNodeContainerModifier,
    GetPatternLockModifier,
    GetColumnSplitModifier,
    GetLineModifier,
    GetPathModifier,
    GetPolygonModifier,
    GetPolylineModifier,
    GetSpanModifier,
    GetImageAnimatorModifier,
    GetSideBarContainerModifier,
    GetCalendarPickerModifier,
    GetTextInputModifier,
    GetTabsModifier,
    GetStepperItemModifier,
    GetHyperlinkModifier,
    GetMarqueeModifier,
    GetMenuItemModifier,
    GetMenuModifier,
    GetDatePickerModifier,
    GetWaterFlowModifier,
    GetAlphabetIndexerModifier,
    GetDataPanelModifier,
    GetGaugeModifier,
    GetScrollModifier,
    GetGridItemModifier,
    GetProgressModifier,
    GetCommonShapeModifier,
    GetShapeModifier,
    GetRectModifier,
    GetSwiperModifier,
    GetListItemModifier,
    GetListModifier,
    GetListItemGroupModifier,
    GetQRCodeModifier,
    GetLoadingProgressModifier,
    GetTextClockModifier,
    GetTextTimerModifier,
    GetRenderNodeModifier,

#ifdef PLUGIN_COMPONENT_SUPPORTED
    GetPluginModifier,
#endif
#ifdef XCOMPONENT_SUPPORTED
    GetXComponentModifier,
#endif
#ifdef FORM_SUPPORTED
    GetFormComponentModifier,
#endif
};

ArkUINodeAPI* GetArkUIInternalNodeAPI()
{
    return &impl;
}

extern "C" ACE_FORCE_EXPORT ArkUINodeAPI* GetArkUINodeAPI()
{
    return &impl;
}
