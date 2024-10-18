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

#include "core/interfaces/native/node/alphabet_indexer_modifier.h"
#include "core/interfaces/native/node/badge_modifier.h"
#include "core/interfaces/native/node/blank_modifier.h"
#include "core/interfaces/native/node/button_modifier.h"
#include "core/interfaces/native/node/calendar_picker_modifier.h"
#include "core/interfaces/native/node/checkboxgroup_modifier.h"
#include "core/interfaces/native/node/column_modifier.h"
#include "core/interfaces/native/node/column_split_modifier.h"
#include "core/interfaces/native/node/common_shape_modifier.h"
#include "core/interfaces/native/node/counter_modifier.h"
#include "core/interfaces/native/node/data_panel_modifier.h"
#include "core/interfaces/native/node/divider_modifier.h"
#include "core/interfaces/native/node/flex_modifier.h"
#include "core/interfaces/native/node/frame_node_modifier.h"
#include "core/interfaces/native/node/gauge_modifier.h"
#include "core/interfaces/native/node/grid_col_modifier.h"
#include "core/interfaces/native/node/grid_item_modifier.h"
#include "core/interfaces/native/node/grid_modifier.h"
#include "core/interfaces/native/node/grid_row_modifier.h"
#include "core/interfaces/native/node/hyperlink_modifier.h"
#include "core/interfaces/native/node/image_animator_modifier.h"
#include "core/interfaces/native/node/line_modifier.h"
#include "core/interfaces/native/node/node_list_item_modifier.h"
#include "core/interfaces/native/node/marquee_modifier.h"
#include "core/interfaces/native/node/menu_item_modifier.h"
#include "core/interfaces/native/node/menu_modifier.h"
#include "core/interfaces/native/node/nav_destination_modifier.h"
#include "core/interfaces/native/node/nav_router_modifier.h"
#include "core/interfaces/native/node/navigation_modifier.h"
#include "core/interfaces/native/node/navigator_modifier.h"
#include "core/interfaces/native/node/node_checkbox_modifier.h"
#include "core/interfaces/native/node/node_common_modifier.h"
#include "core/interfaces/native/node/node_container_modifier.h"
#include "core/interfaces/native/node/node_content_modifier.h"
#include "core/interfaces/native/node/node_date_picker_modifier.h"
#include "core/interfaces/native/node/node_gesture_modifier.h"
#include "core/interfaces/native/node/node_image_modifier.h"
#include "core/interfaces/native/node/node_image_span_modifier.h"
#include "core/interfaces/native/node/node_list_item_group_modifier.h"
#include "core/interfaces/native/node/node_list_modifier.h"
#include "core/interfaces/native/node/node_loading_progress_modifier.h"
#include "core/interfaces/native/node/node_refresh_modifier.h"
#include "core/interfaces/native/node/node_relative_container_modifier.h"
#include "core/interfaces/native/node/node_scroll_modifier.h"
#include "core/interfaces/native/node/node_slider_modifier.h"
#include "core/interfaces/native/node/node_span_modifier.h"
#include "core/interfaces/native/node/node_stack_modifier.h"
#include "core/interfaces/native/node/node_folder_stack_modifier.h"
#include "core/interfaces/native/node/node_swiper_modifier.h"
#include "core/interfaces/native/node/node_text_area_modifier.h"
#include "core/interfaces/native/node/node_text_input_modifier.h"
#include "core/interfaces/native/node/node_text_modifier.h"
#include "core/interfaces/native/node/node_textpicker_modifier.h"
#include "core/interfaces/native/node/node_timepicker_modifier.h"
#include "core/interfaces/native/node/node_toggle_modifier.h"
#include "core/interfaces/native/node/panel_modifier.h"
#include "core/interfaces/native/node/particle_modifier.h"
#include "core/interfaces/native/node/path_modifier.h"
#include "core/interfaces/native/node/pattern_lock_modifier.h"
#include "core/interfaces/native/node/polygon_modifier.h"
#include "core/interfaces/native/node/polyline_modifier.h"
#include "core/interfaces/native/node/progress_modifier.h"
#include "core/interfaces/native/node/qrcode_modifier.h"
#include "core/interfaces/native/node/radio_modifier.h"
#include "core/interfaces/native/node/rating_modifier.h"
#include "core/interfaces/native/node/rect_modifier.h"
#include "core/interfaces/native/node/render_node_modifier.h"
#include "core/interfaces/native/node/rich_editor_modifier.h"
#include "core/interfaces/native/node/row_modifier.h"
#include "core/interfaces/native/node/row_split_modifier.h"
#include "core/interfaces/native/node/scroller_modifier.h"
#include "core/interfaces/native/node/search_modifier.h"
#include "core/interfaces/native/node/select_modifier.h"
#include "core/interfaces/native/node/swiper_controller_modifier.h"
#include "core/interfaces/native/node/rich_editor_modifier.h"
#include "core/interfaces/native/node/shape_modifier.h"
#include "core/interfaces/native/node/side_bar_container_modifier.h"
#include "core/interfaces/native/node/stepper_item_modifier.h"
#include "core/interfaces/native/node/flex_modifier.h"
#include "core/interfaces/native/node/node_gesture_modifier.h"
#include "core/interfaces/native/node/node_refresh_modifier.h"
#include "core/interfaces/native/node/node_symbol_glyph_modifier.h"
#include "core/interfaces/native/node/node_symbol_span_modifier.h"
#include "core/interfaces/native/node/tab_content_modifier.h"
#include "core/interfaces/native/node/tabs_modifier.h"
#include "core/interfaces/native/node/text_clock_modifier.h"
#include "core/interfaces/native/node/text_timer_modifier.h"
#include "core/interfaces/native/node/video_modifier.h"
#include "core/interfaces/native/node/water_flow_modifier.h"
#include "core/interfaces/native/node/node_container_span_modifier.h"
#include "core/interfaces/native/node/node_scroll_bar_modifier.h"
#include "core/interfaces/native/node/linear_indicator_modifier.h"

#ifdef MODEL_COMPONENT_SUPPORTED
#include "core/interfaces/native/node/node_component3d_modifier.h"
#endif

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
    NodeModifier::GetFolderStackModifier,
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
    NodeModifier::GetScrollBarModifier, // ScrollBarModifier
    NodeModifier::GetScrollerModifier,
    NodeModifier::GetTabContentModifier,
    nullptr, // TabsControllerModifier
    NodeModifier::GetSwiperControllerModifier,
    NodeModifier::GetGestureModifier, // GestureModifier
    NodeModifier::GetBadgeModifier, // BadgeModifier
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
    NodeModifier::GetRelativeContainerModifier, // RelativeContainerModifier
    NodeModifier::GetParticleModifier,
    NodeModifier::GetNodeContentModifier,
    NodeModifier::GetSymbolGlyphModifier,
    NodeModifier::GetSymbolSpanModifier,

#ifdef MODEL_COMPONENT_SUPPORTED
    NodeModifier::GetComponent3DModifier,
#else
    nullptr,
#endif

    NodeModifier::GetContainerSpanModifier,
    NodeModifier::GetLinearIndicatorModifier,
};
} // namespace

} // namespace OHOS::Ace::NG

extern "C" {

const ArkUINodeModifiers* GetArkUINodeModifiers()
{
    return &OHOS::Ace::NG::impl;
}

const CJUINodeModifiers* GetCJUINodeModifiers()
{
    static CJUINodeModifiers modifiers {
    ARKUI_NODE_MODIFIERS_API_VERSION,
    OHOS::Ace::NG::NodeModifier::GetCJUICommonModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUICheckboxGroupModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUICounterModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIRowModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIRowSplitModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUITextModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIButtonModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIToggleModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIImageSpanModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIBlankModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUISearchModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUISelectModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIRadioModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUICheckboxModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUITimepickerModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUITextPickerModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIRatingModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUISliderModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIDividerModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIStackModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIFolderStackModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUINavDestinationModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIGridModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIGridColModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIGridRowModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIPanelModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUITextAreaModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUINavigationModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIColumnModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIRichEditorModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIImageModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIVideoModifier,
    nullptr,
    nullptr,
    OHOS::Ace::NG::NodeModifier::GetCJUINavRouterModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUINodeContainerModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIPatternLockModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIColumnSplitModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUILineModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIPathModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIPolygonModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIPolylineModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUISpanModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIImageAnimatorModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUISideBarContainerModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUICalendarPickerModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUITextInputModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUITabsModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIStepperItemModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIHyperlinkModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIMarqueeModifier,
    nullptr,
    OHOS::Ace::NG::NodeModifier::GetCJUIMenuModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIDatePickerModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIWaterFlowModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIAlphabetIndexerModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIDataPanelModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIGaugeModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIScrollModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIGridItemModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIProgressModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUICommonShapeModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIShapeModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIRectModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUISwiperModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIListItemModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIListModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIListItemGroupModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIQRCodeModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUILoadingProgressModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUITextClockModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUITextTimerModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIRenderNodeModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIFrameNodeModifier,

#ifdef PLUGIN_COMPONENT_SUPPORTED
    OHOS::Ace::NG::NodeModifier::GetCJUIPluginModifier,
#else
    nullptr,
#endif

#ifdef XCOMPONENT_SUPPORTED
    OHOS::Ace::NG::NodeModifier::GetCJUIXComponentModifier,
#else
    nullptr,
#endif

    OHOS::Ace::NG::NodeModifier::GetCJUIStateModifier,

#ifdef FORM_SUPPORTED
    OHOS::Ace::NG::NodeModifier::GetCJUIFormComponentModifier,
#else
    nullptr,
#endif
    OHOS::Ace::NG::NodeModifier::GetCJUIFlexModifier, // FlexModifier
    OHOS::Ace::NG::NodeModifier::GetCJUIScrollBarModifier, // ScrollBarModifier
    OHOS::Ace::NG::NodeModifier::GetCJUIScrollerModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUITabContentModifier,
    nullptr, // TabsControllerModifier
    OHOS::Ace::NG::NodeModifier::GetCJUISwiperControllerModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIGestureModifier, // GestureModifier
    nullptr, // BadgeModifier
    nullptr, // WebModifier
    OHOS::Ace::NG::NodeModifier::GetCJUIRefreshModifier, // RefreshModifier
    nullptr, // MenuItemGroupModifier
    nullptr, // SearchControllerModifier
    nullptr, // SideBarModifier
    nullptr, // PatternLockControllerModifier
    nullptr, // TextTimerControllerModifier
    nullptr, // TextClockControllerModifier
    nullptr, // RichEditorControllerModifier
    nullptr, // TextAreaControllerModifier
    OHOS::Ace::NG::NodeModifier::GetCJUIRelativeContainerModifier, // RelativeContainerModifier
    OHOS::Ace::NG::NodeModifier::GetCJUINodeContentModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUIParticleModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUISymbolGlyphModifier,
    OHOS::Ace::NG::NodeModifier::GetCJUISymbolSpanModifier,

#ifdef MODEL_COMPONENT_SUPPORTED
    OHOS::Ace::NG::NodeModifier::GetCJUIComponent3DModifier,
#else
    nullptr,
#endif

    OHOS::Ace::NG::NodeModifier::GetCJUIContainerSpanModifier,
    };
    return &modifiers;
}
}
