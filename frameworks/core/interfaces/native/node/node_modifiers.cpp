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
#include "core/interfaces/native/node/node_api.h"

#include "core/interfaces/native/node/node_common_modifier.h"
#include "core/interfaces/native/node/node_date_picker_modifier.h"
#include "core/interfaces/native/node/node_image_span_modifier.h"
#include "core/interfaces/native/node/node_image_modifier.h"
#include "core/interfaces/native/node/node_list_modifier.h"
#include "core/interfaces/native/node/node_list_item_group_modifier.h"
#include "core/interfaces/native/node/node_loading_progress_modifier.h"
#include "core/interfaces/native/node/node_scroll_modifier.h"
#include "core/interfaces/native/node/node_span_modifier.h"
#include "core/interfaces/native/node/node_stack_modifier.h"
#include "core/interfaces/native/node/node_text_input_modifier.h"
#include "core/interfaces/native/node/node_text_area_modifier.h"
#include "core/interfaces/native/node/node_textpicker_modifier.h"
#include "core/interfaces/native/node/node_text_modifier.h"
#include "core/interfaces/native/node/node_timepicker_modifier.h"
#include "core/interfaces/native/node/node_toggle_modifier.h"
#include "core/interfaces/native/node/node_swiper_modifier.h"
#include "core/interfaces/native/node/node_checkbox_modifier.h"
#include "core/interfaces/native/node/node_slider_modifier.h"

#include "core/interfaces/native/node/alphabet_indexer_modifier.h"
#include "core/interfaces/native/node/checkboxgroup_modifier.h"
#include "core/interfaces/native/node/calendar_picker_modifier.h"
#include "core/interfaces/native/node/column_modifier.h"
#include "core/interfaces/native/node/blank_modifier.h"
#include "core/interfaces/native/node/column_split_modifier.h"
#include "core/interfaces/native/node/grid_modifier.h"
#include "core/interfaces/native/node/grid_col_modifier.h"
#include "core/interfaces/native/node/grid_item_modifier.h"
#include "core/interfaces/native/node/button_modifier.h"
#include "core/interfaces/native/node/row_split_modifier.h"
#include "core/interfaces/native/node/common_shape_modifier.h"
#include "core/interfaces/native/node/data_panel_modifier.h"
#include "core/interfaces/native/node/counter_modifier.h"
#include "core/interfaces/native/node/divider_modifier.h"
#include "core/interfaces/native/node/gauge_modifier.h"
#include "core/interfaces/native/node/line_modifier.h"
#include "core/interfaces/native/node/hyperlink_modifier.h"
#include "core/interfaces/native/node/row_modifier.h"
#include "core/interfaces/native/node/grid_row_modifier.h"
#include "core/interfaces/native/node/image_animator_modifier.h"
#include "core/interfaces/native/node/list_item_modifier.h"
#include "core/interfaces/native/node/nav_router_modifier.h"
#include "core/interfaces/native/node/nav_destination_modifier.h"
#include "core/interfaces/native/node/marquee_modifier.h"
#include "core/interfaces/native/node/menu_modifier.h"
#include "core/interfaces/native/node/node_container_modifier.h"
#include "core/interfaces/native/node/menu_item_modifier.h"
#include "core/interfaces/native/node/navigator_modifier.h"
#include "core/interfaces/native/node/panel_modifier.h"
#include "core/interfaces/native/node/navigation_modifier.h"
#include "core/interfaces/native/node/particle_modifier.h"
#include "core/interfaces/native/node/path_modifier.h"
#include "core/interfaces/native/node/pattern_lock_modifier.h"
#include "core/interfaces/native/node/polygon_modifier.h"
#include "core/interfaces/native/node/polyline_modifier.h"
#include "core/interfaces/native/node/progress_modifier.h"
#include "core/interfaces/native/node/rating_modifier.h"
#include "core/interfaces/native/node/qrcode_modifier.h"
#include "core/interfaces/native/node/radio_modifier.h"
#include "core/interfaces/native/node/render_node_modifier.h"
#include "core/interfaces/native/node/frame_node_modifier.h"
#include "core/interfaces/native/node/video_modifier.h"
#include "core/interfaces/native/node/water_flow_modifier.h"
#include "core/interfaces/native/node/text_clock_modifier.h"
#include "core/interfaces/native/node/text_timer_modifier.h"
#include "core/interfaces/native/node/tabs_modifier.h"
#include "core/interfaces/native/node/search_modifier.h"
#include "core/interfaces/native/node/select_modifier.h"
#include "core/interfaces/native/node/rich_editor_modifier.h"
#include "core/interfaces/native/node/shape_modifier.h"
#include "core/interfaces/native/node/rect_modifier.h"
#include "core/interfaces/native/node/side_bar_container_modifier.h"
#include "core/interfaces/native/node/stepper_item_modifier.h"
#include "core/interfaces/native/node/flex_modifier.h"
#include "core/interfaces/native/node/node_gesture_modifier.h"
#include "core/interfaces/native/node/node_refresh_modifier.h"
#include "core/interfaces/native/node/node_symbol_glyph_modifier.h"

#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/interfaces/native/node/plugin_modifier.h"
#endif

#ifdef XCOMPONENT_SUPPORTED
#include "core/interfaces/native/node/node_xcomponent_modifier.h"
#endif

#ifdef FORM_SUPPORTED
#include "core/interfaces/native/node/form_component_modifier.h"
#endif

namespace OHOS::Ace::NG {
namespace {
const ArkUINodeModifiers impl = {
    ARKUI_NODE_MODIFIERS_API_VERSION,
    NodeModifier::GetCommonModifier,
    NodeModifier::GetCheckboxGroupModifier,
    NodeModifier::GetCounterModifier,
    NodeModifier::GetRowModifier,
    NodeModifier::GetRowSplitModifier,
    NodeModifier::GetTextModifier,
    NodeModifier::GetButtonModifier,
    NodeModifier::GetToggleModifier,
    NodeModifier::GetImageSpanModifier,
    NodeModifier::GetBlankModifier,
    NodeModifier::GetSearchModifier,
    NodeModifier::GetSelectModifier,
    NodeModifier::GetRadioModifier,
    NodeModifier::GetCheckboxModifier,
    NodeModifier::GetTimepickerModifier,
    NodeModifier::GetTextPickerModifier,
    NodeModifier::GetRatingModifier,
    NodeModifier::GetSliderModifier,
    NodeModifier::GetDividerModifier,
    NodeModifier::GetStackModifier,
    NodeModifier::GetNavDestinationModifier,
    NodeModifier::GetGridModifier,
    NodeModifier::GetGridColModifier,
    NodeModifier::GetGridRowModifier,
    NodeModifier::GetPanelModifier,
    NodeModifier::GetTextAreaModifier,
    NodeModifier::GetNavigationModifier,
    NodeModifier::GetColumnModifier,
    NodeModifier::GetRichEditorModifier,
    NodeModifier::GetImageModifier,
    NodeModifier::GetVideoModifier,
    nullptr,
    NodeModifier::GetNavigatorModifier,
    NodeModifier::GetNavRouterModifier,
    NodeModifier::GetNodeContainerModifier,
    NodeModifier::GetPatternLockModifier,
    NodeModifier::GetColumnSplitModifier,
    NodeModifier::GetLineModifier,
    NodeModifier::GetPathModifier,
    NodeModifier::GetPolygonModifier,
    NodeModifier::GetPolylineModifier,
    NodeModifier::GetSpanModifier,
    NodeModifier::GetImageAnimatorModifier,
    NodeModifier::GetSideBarContainerModifier,
    NodeModifier::GetCalendarPickerModifier,
    NodeModifier::GetTextInputModifier,
    NodeModifier::GetTabsModifier,
    NodeModifier::GetStepperItemModifier,
    NodeModifier::GetHyperlinkModifier,
    NodeModifier::GetMarqueeModifier,
    NodeModifier::GetMenuItemModifier,
    NodeModifier::GetMenuModifier,
    NodeModifier::GetDatePickerModifier,
    NodeModifier::GetWaterFlowModifier,
    NodeModifier::GetAlphabetIndexerModifier,
    NodeModifier::GetDataPanelModifier,
    NodeModifier::GetGaugeModifier,
    NodeModifier::GetScrollModifier,
    NodeModifier::GetGridItemModifier,
    NodeModifier::GetProgressModifier,
    NodeModifier::GetCommonShapeModifier,
    NodeModifier::GetShapeModifier,
    NodeModifier::GetRectModifier,
    NodeModifier::GetSwiperModifier,
    NodeModifier::GetListItemModifier,
    NodeModifier::GetListModifier,
    NodeModifier::GetListItemGroupModifier,
    NodeModifier::GetQRCodeModifier,
    NodeModifier::GetLoadingProgressModifier,
    NodeModifier::GetTextClockModifier,
    NodeModifier::GetTextTimerModifier,
    NodeModifier::GetSymbolGlyphModifier,
    NodeModifier::GetRenderNodeModifier,
    NodeModifier::GetFrameNodeModifier,

#ifdef PLUGIN_COMPONENT_SUPPORTED
    NodeModifier::GetPluginModifier,
#else
    nullptr,
#endif

#ifdef XCOMPONENT_SUPPORTED
    NodeModifier::GetXComponentModifier,
#else
    nullptr,
#endif

    NodeModifier::GetUIStateModifier,

#ifdef FORM_SUPPORTED
    NodeModifier::GetFormComponentModifier,
#else
    nullptr,
#endif
    NodeModifier::GetFlexModifier, // FlexModifier
    nullptr, // ScrollBarModifier
    nullptr, // ScrollerModifier
    nullptr, // TabContentModifier
    nullptr, // TabsControllerModifier
    nullptr, // SwiperControllerModifier
    NodeModifier::GetGestureModifier, // GestureModifier
    nullptr, // BadgeModifier
    nullptr, // WebModifier
    NodeModifier::GetRefreshModifier, // RefreshModifier
    nullptr, // MenuItemGroupModifier
    nullptr, // SearchControllerModifier
    nullptr, // SideBarModifier
    nullptr, // PatternLockControllerModifier
    nullptr, // TextTimerControllerModifier
    nullptr, // TextClockControllerModifier
    nullptr, // RichEditorControllerModifier
    nullptr, // TextAreaControllerModifier
    NodeModifier::GetParticleModifier
};

} // namespace

} // namespace OHOS::Ace::NG

extern "C" {

const ArkUINodeModifiers* GetArkUINodeModifiers()
{
    return &OHOS::Ace::NG::impl;
}
}
