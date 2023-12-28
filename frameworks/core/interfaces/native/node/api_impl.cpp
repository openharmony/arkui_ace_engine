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
#include "core/interfaces/native/node/api.h"
#include "core/interfaces/native/node/blank_modifier.h"
#include "core/interfaces/native/node/button_modifier.h"
#include "core/interfaces/native/node/checkbox_modifier.h"
#include "core/interfaces/native/node/checkboxgroup_modifier.h"
#include "core/interfaces/native/node/column_modifier.h"
#include "core/interfaces/native/node/column_split_modifier.h"
#include "core/interfaces/native/node/common_modifier.h"
#include "core/interfaces/native/node/counter_modifier.h"
#include "core/interfaces/native/node/date_picker_modifier.h"
#include "core/interfaces/native/node/divider_modifier.h"
#include "core/interfaces/native/node/grid_modifier.h"
#include "core/interfaces/native/node/grid_col_modifier.h"
#include "core/interfaces/native/node/grid_item_modifier.h"
#include "core/interfaces/native/node/grid_row_modifier.h"
#include "core/interfaces/native/node/hyperlink_modifier.h"
#include "core/interfaces/native/node/image_animator_modifier.h"
#include "core/interfaces/native/node/image_modifier.h"
#include "core/interfaces/native/node/image_span_modifier.h"
#include "core/interfaces/native/node/list_item_modifier.h"
#include "core/interfaces/native/node/menu_modifier.h"
#include "core/interfaces/native/node/menu_item_modifier.h"
#include "core/interfaces/native/node/nav_destination_modifier.h"
#include "core/interfaces/native/node/nav_router_modifier.h"
#include "core/interfaces/native/node/navigation_modifier.h"
#include "core/interfaces/native/node/navigator_modifier.h"
#include "core/interfaces/native/node/node_container_modifier.h"
#include "core/interfaces/native/node/panel_modifier.h"
#include "core/interfaces/native/node/pattern_lock_modifier.h"
#include "core/interfaces/native/node/progress_modifier.h"
#include "core/interfaces/native/node/render_node_modifier.h"
#include "core/interfaces/native/node/text_area_modifier.h"
#include "core/interfaces/native/node/text_input_modifier.h"
#include "core/interfaces/native/node/swiper_modifier.h"
#include "core/interfaces/native/node/text_modifier.h"
#include "core/interfaces/native/node/toggle_modifier.h"
#include "core/interfaces/native/node/radio_modifier.h"
#include "core/interfaces/native/node/rating_modifier.h"
#include "core/interfaces/native/node/rich_editor_modifier.h"
#include "core/interfaces/native/node/row_modifier.h"
#include "core/interfaces/native/node/row_split_modifier.h"
#include "core/interfaces/native/node/search_modifier.h"
#include "core/interfaces/native/node/select_modifier.h"
#include "core/interfaces/native/node/slider_modifier.h"
#include "core/interfaces/native/node/span_modifier.h"
#include "core/interfaces/native/node/stack_modifier.h"
#include "core/interfaces/native/node/stepper_item_modifier.h"
#include "core/interfaces/native/node/tabs_modifier.h"
#include "core/interfaces/native/node/textpicker_modifier.h"
#include "core/interfaces/native/node/timepicker_modifier.h"
#include "core/interfaces/native/node/video_modifier.h"
#include "core/interfaces/native/node/line_modifier.h"
#include "core/interfaces/native/node/path_modifier.h"
#include "core/interfaces/native/node/polygon_modifier.h"
#include "core/interfaces/native/node/polyline_modifier.h"
#include "core/interfaces/native/node/qrcode_modifier.h"
#include "core/interfaces/native/node/water_flow_modifier.h"
#include "core/interfaces/native/node/side_bar_container_modifier.h"
#include "core/interfaces/native/node/marquee_modifier.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/pipeline/base/element_register.h"
#include "core/interfaces/native/node/calendar_picker_modifier.h"
#include "core/interfaces/native/node/alphabet_indexer_modifier.h"
#include "core/interfaces/native/node/data_panel_modifier.h"
#include "core/interfaces/native/node/gauge_modifier.h"
#include "core/interfaces/native/node/scroll_modifier.h"
#include "core/interfaces/native/node/common_shape_modifier.h"
#include "core/interfaces/native/node/shape_modifier.h"
#include "core/interfaces/native/node/rect_modifier.h"
#include "core/interfaces/native/node/list_modifier.h"
#include "core/interfaces/native/node/list_item_group_modifier.h"
#include "core/interfaces/native/node/text_timer_modifier.h"
#include "core/interfaces/native/node/loading_progress_modifier.h"
#include "core/interfaces/native/node/text_clock_modifier.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/interfaces/native/node/plugin_modifier.h"
#endif
#ifdef XCOMPONENT_SUPPORTED
#include "core/interfaces/native/node/xcomponent_modifier.h"
#endif
#ifdef FORM_SUPPORTED
#include "core/interfaces/native/node/form_component_modifier.h"
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
