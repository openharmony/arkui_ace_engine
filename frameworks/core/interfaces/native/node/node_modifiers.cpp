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
#include "core/interfaces/native/node/lazy_grid_layout_modifier.h"
#include "core/interfaces/native/node/line_modifier.h"
#include "core/interfaces/native/node/linear_indicator_modifier.h"
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
#include "core/interfaces/native/node/node_container_span_modifier.h"
#include "core/interfaces/native/node/node_content_modifier.h"
#include "core/interfaces/native/node/node_custom_node_ext_modifier.h"
#include "core/interfaces/native/node/node_date_picker_modifier.h"
#include "core/interfaces/native/node/node_folder_stack_modifier.h"
#include "core/interfaces/native/node/node_gesture_modifier.h"
#include "core/interfaces/native/node/node_image_modifier.h"
#include "core/interfaces/native/node/node_image_span_modifier.h"
#include "core/interfaces/native/node/node_indicator_modifier.h"
#include "core/interfaces/native/node/node_list_item_group_modifier.h"
#include "core/interfaces/native/node/node_list_item_modifier.h"
#include "core/interfaces/native/node/node_list_modifier.h"
#include "core/interfaces/native/node/node_loading_progress_modifier.h"
#include "core/interfaces/native/node/node_refresh_modifier.h"
#include "core/interfaces/native/node/node_relative_container_modifier.h"
#include "core/interfaces/native/node/node_scroll_bar_modifier.h"
#include "core/interfaces/native/node/node_scroll_modifier.h"
#include "core/interfaces/native/node/node_slider_modifier.h"
#include "core/interfaces/native/node/node_span_modifier.h"
#include "core/interfaces/native/node/node_stack_modifier.h"
#include "core/interfaces/native/node/node_swiper_modifier.h"
#include "core/interfaces/native/node/node_symbol_glyph_modifier.h"
#include "core/interfaces/native/node/node_symbol_span_modifier.h"
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
#ifdef QRCODEGEN_SUPPORT
#include "core/interfaces/native/node/qrcode_modifier.h"
#endif
#include "core/interfaces/native/node/radio_modifier.h"
#include "core/interfaces/native/node/rating_modifier.h"
#include "core/interfaces/native/node/rect_modifier.h"
#include "core/interfaces/native/node/render_node_modifier.h"
#include "core/interfaces/native/node/rich_editor_modifier.h"
#include "core/interfaces/native/node/row_modifier.h"
#include "core/interfaces/native/node/row_split_modifier.h"
#include "core/interfaces/native/node/scrollable_modifier.h"
#include "core/interfaces/native/node/scroller_modifier.h"
#include "core/interfaces/native/node/search_modifier.h"
#include "core/interfaces/native/node/select_modifier.h"
#include "core/interfaces/native/node/shape_modifier.h"
#include "core/interfaces/native/node/side_bar_container_modifier.h"
#include "core/interfaces/native/node/stepper_item_modifier.h"
#include "core/interfaces/native/node/swiper_controller_modifier.h"
#include "core/interfaces/native/node/tab_content_modifier.h"
#include "core/interfaces/native/node/tabs_modifier.h"
#include "core/interfaces/native/node/text_clock_modifier.h"
#include "core/interfaces/native/node/text_timer_modifier.h"
#include "core/interfaces/native/node/theme_modifier.h"
#include "core/interfaces/native/node/video_modifier.h"
#include "core/interfaces/native/node/water_flow_modifier.h"

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

#ifdef WEB_SUPPORTED
#include "core/interfaces/native/node/web_modifier.h"
#endif

using namespace OHOS::Ace::NG;

#define MODIFIER_COUNTS 13
#define BLANK_LINES 6

extern "C" {
const ArkUINodeModifiers* GetArkUINodeModifiers()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static ArkUINodeModifiers impl = {
        .version = ARKUI_NODE_MODIFIERS_API_VERSION,
        .getCommonModifier = NodeModifier::GetCommonModifier,
        .getCheckboxGroupModifier = NodeModifier::GetCheckboxGroupModifier,
        .getCounterModifier = NodeModifier::GetCounterModifier,
        .getRowModifier = NodeModifier::GetRowModifier,
    #ifndef ARKUI_WEARABLE
        .getRowSplitModifier = NodeModifier::GetRowSplitModifier,
    #else
        .getRowSplitModifier = nullptr,
    #endif
        .getTextModifier = NodeModifier::GetTextModifier,
        .getButtonModifier = NodeModifier::GetButtonModifier,
        .getToggleModifier = NodeModifier::GetToggleModifier,
        .getImageSpanModifier = NodeModifier::GetImageSpanModifier,
        .getBlankModifier = NodeModifier::GetBlankModifier,
        .getSearchModifier = NodeModifier::GetSearchModifier,
    #ifndef ARKUI_WEARABLE
        .getSelectModifier = NodeModifier::GetSelectModifier,
    #else
        .getSelectModifier = nullptr,
    #endif
        .getRadioModifier = NodeModifier::GetRadioModifier,
        .getCheckboxModifier = NodeModifier::GetCheckboxModifier,
        .getTimepickerModifier = NodeModifier::GetTimepickerModifier,
        .getTextPickerModifier = NodeModifier::GetTextPickerModifier,
        .getRatingModifier = NodeModifier::GetRatingModifier,
        .getSliderModifier = NodeModifier::GetSliderModifier,
        .getDividerModifier = NodeModifier::GetDividerModifier,
        .getStackModifier = NodeModifier::GetStackModifier,
    #ifndef ARKUI_WEARABLE
        .getFolderStackModifier = NodeModifier::GetFolderStackModifier,
    #else
        .getFolderStackModifier = nullptr,
    #endif
        .getNavDestinationModifier = NodeModifier::GetNavDestinationModifier,
        .getGridModifier = NodeModifier::GetGridModifier,
        .getGridColModifier = NodeModifier::GetGridColModifier,
        .getGridRowModifier = NodeModifier::GetGridRowModifier,
        .getPanelModifier = NodeModifier::GetPanelModifier,
        .getTextAreaModifier = NodeModifier::GetTextAreaModifier,
        .getNavigationModifier = NodeModifier::GetNavigationModifier,
        .getColumnModifier = NodeModifier::GetColumnModifier,
        .getRichEditorModifier = NodeModifier::GetRichEditorModifier,
        .getImageModifier = NodeModifier::GetImageModifier,
        .getVideoModifier = NodeModifier::GetVideoModifier,
        .getVideoControllerModifier = nullptr,
        .getNavigatorModifier = NodeModifier::GetNavigatorModifier,
        .getNavRouterModifier = NodeModifier::GetNavRouterModifier,
        .getNodeContainerModifier = NodeModifier::GetNodeContainerModifier,
        .getPatternLockModifier = NodeModifier::GetPatternLockModifier,
    #ifndef ARKUI_WEARABLE
        .getColumnSplitModifier = NodeModifier::GetColumnSplitModifier,
    #else
        .getColumnSplitModifier = nullptr,
    #endif
        .getLineModifier = NodeModifier::GetLineModifier,
        .getPathModifier = NodeModifier::GetPathModifier,
        .getPolygonModifier = NodeModifier::GetPolygonModifier,
        .getPolylineModifier = NodeModifier::GetPolylineModifier,
        .getSpanModifier = NodeModifier::GetSpanModifier,
        .getImageAnimatorModifier = NodeModifier::GetImageAnimatorModifier,
        .getSideBarContainerModifier = NodeModifier::GetSideBarContainerModifier,
    #ifndef ARKUI_WEARABLE
        .getCalendarPickerModifier = NodeModifier::GetCalendarPickerModifier,
    #else
        .getCalendarPickerModifier = nullptr,
    #endif
        .getTextInputModifier = NodeModifier::GetTextInputModifier,
        .getTabsModifier = NodeModifier::GetTabsModifier,
    #ifndef ARKUI_WEARABLE
        .getStepperItemModifier = NodeModifier::GetStepperItemModifier,
    #else
        .getStepperItemModifier = nullptr,
    #endif
        .getHyperlinkModifier = NodeModifier::GetHyperlinkModifier,
        .getMarqueeModifier = NodeModifier::GetMarqueeModifier,
        .getMenuItemModifier = NodeModifier::GetMenuItemModifier,
        .getMenuModifier = NodeModifier::GetMenuModifier,
        .getDatePickerModifier = NodeModifier::GetDatePickerModifier,
    #ifndef ARKUI_WEARABLE
        .getWaterFlowModifier = NodeModifier::GetWaterFlowModifier,
    #else
        .getWaterFlowModifier = nullptr,
    #endif
        .getAlphabetIndexerModifier = NodeModifier::GetAlphabetIndexerModifier,
        .getDataPanelModifier = NodeModifier::GetDataPanelModifier,
        .getGaugeModifier = NodeModifier::GetGaugeModifier,
        .getScrollModifier = NodeModifier::GetScrollModifier,
        .getScrollableModifier = NodeModifier::GetScrollableModifier,
        .getGridItemModifier = NodeModifier::GetGridItemModifier,
        .getProgressModifier = NodeModifier::GetProgressModifier,
        .getCommonShapeModifier = NodeModifier::GetCommonShapeModifier,
        .getShapeModifier = NodeModifier::GetShapeModifier,
        .getRectModifier = NodeModifier::GetRectModifier,
        .getSwiperModifier = NodeModifier::GetSwiperModifier,
        .getListItemModifier = NodeModifier::GetListItemModifier,
        .getListModifier = NodeModifier::GetListModifier,
        .getListItemGroupModifier = NodeModifier::GetListItemGroupModifier,
    #ifdef QRCODEGEN_SUPPORT
        .getQRCodeModifier = NodeModifier::GetQRCodeModifier,
    #else
        .getQRCodeModifier = nullptr,
    #endif
        .getLoadingProgressModifier = NodeModifier::GetLoadingProgressModifier,
        .getTextClockModifier = NodeModifier::GetTextClockModifier,
        .getTextTimerModifier = NodeModifier::GetTextTimerModifier,
        .getRenderNodeModifier = NodeModifier::GetRenderNodeModifier,
        .getFrameNodeModifier = NodeModifier::GetFrameNodeModifier,
    #ifdef PLUGIN_COMPONENT_SUPPORTED
        .getPluginModifier = NodeModifier::GetPluginModifier,
    #else
        .getPluginModifier = nullptr,
    #endif
    #ifdef XCOMPONENT_SUPPORTED
        .getXComponentModifier = NodeModifier::GetXComponentModifier,
    #else
        .getXComponentModifier = nullptr,
    #endif
        .getUIStateModifier = NodeModifier::GetUIStateModifier,
    #ifdef FORM_SUPPORTED
        .getFormComponentModifier = NodeModifier::GetFormComponentModifier,
    #else
        .getFormComponentModifier = nullptr,
    #endif
        .getFlexModifier = NodeModifier::GetFlexModifier, // FlexModifier
        .getScrollBarModifier = NodeModifier::GetScrollBarModifier, // ScrollBarModifier
        .getScrollerModifier = NodeModifier::GetScrollerModifier,
        .getTabContentModifier = NodeModifier::GetTabContentModifier,
        .getTabsControllerModifier = nullptr, // TabsControllerModifier
        .getSwiperControllerModifier = NodeModifier::GetSwiperControllerModifier,
        .getGestureModifier = NodeModifier::GetGestureModifier, // GestureModifier
        .getBadgeModifier = NodeModifier::GetBadgeModifier, // BadgeModifier
    #ifdef WEB_SUPPORTED
        .getWebModifier = NodeModifier::GetWebModifier, // WebModifier
    #else
        .getWebModifier = nullptr, // WebModifier
    #endif
        .getRefreshModifier = NodeModifier::GetRefreshModifier, // RefreshModifier
        .getMenuItemGroupModifier = nullptr, // MenuItemGroupModifier
        .getSearchControllerModifier = nullptr, // SearchControllerModifier
        .getSideBarModifier = nullptr, // SideBarModifier
        .getPatternLockControllerModifier = nullptr, // PatternLockControllerModifier
        .getTextTimerControllerModifier = nullptr, // TextTimerControllerModifier
        .getTextClockControllerModifier = nullptr, // TextClockControllerModifier
        .getRichEditorControllerModifier = nullptr, // RichEditorControllerModifier
        .getTextAreaControllerModifier = nullptr, // TextAreaControllerModifier
        .getRelativeContainerModifier = NodeModifier::GetRelativeContainerModifier, // RelativeContainerModifier
        .getParticleModifier = NodeModifier::GetParticleModifier,
        .getNodeContentModifier = NodeModifier::GetNodeContentModifier,
        .getSymbolGlyphModifier = NodeModifier::GetSymbolGlyphModifier,
        .getSymbolSpanModifier = NodeModifier::GetSymbolSpanModifier,
    #ifdef MODEL_COMPONENT_SUPPORTED
        .getComponent3DModifier = NodeModifier::GetComponent3DModifier,
    #else
        .getComponent3DModifier = nullptr,
    #endif
        .getContainerSpanModifier = NodeModifier::GetContainerSpanModifier,
        .getCustomNodeExtModifier = nullptr,
        .getThemeModifier = NodeModifier::GetThemeModifier,
        .getLinearIndicatorModifier = NodeModifier::GetLinearIndicatorModifier,
        .getIndicatorComponentModifier = NodeModifier::GetIndicatorComponentModifier,
        .getLazyGridLayoutModifier = NodeModifier::GetLazyGridLayoutModifier,
    };
    CHECK_INITIALIZED_FIELDS_END(impl, MODIFIER_COUNTS, 0, 0); // don't move this line.
    return &impl;
}

const CJUINodeModifiers* GetCJUINodeModifiers()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static CJUINodeModifiers modifiers {
        .version = ARKUI_NODE_MODIFIERS_API_VERSION,
        .getCommonModifier = NodeModifier::GetCJUICommonModifier,
        .getCheckboxGroupModifier = NodeModifier::GetCJUICheckboxGroupModifier,
        .getCounterModifier = NodeModifier::GetCJUICounterModifier,
        .getRowModifier = NodeModifier::GetCJUIRowModifier,
    #ifndef ARKUI_WEARABLE
        .getRowSplitModifier = NodeModifier::GetCJUIRowSplitModifier,
    #else
        .getRowSplitModifier = nullptr,
    #endif
        .getTextModifier = NodeModifier::GetCJUITextModifier,
        .getButtonModifier = NodeModifier::GetCJUIButtonModifier,
        .getToggleModifier = NodeModifier::GetCJUIToggleModifier,
        .getImageSpanModifier = NodeModifier::GetCJUIImageSpanModifier,
        .getBlankModifier = NodeModifier::GetCJUIBlankModifier,
        .getSearchModifier = NodeModifier::GetCJUISearchModifier,
    #ifndef ARKUI_WEARABLE
        .getSelectModifier = NodeModifier::GetCJUISelectModifier,
    #else
        .getSelectModifier = nullptr,
    #endif
        .getRadioModifier = NodeModifier::GetCJUIRadioModifier,
        .getCheckboxModifier = NodeModifier::GetCJUICheckboxModifier,
        .getTimepickerModifier = NodeModifier::GetCJUITimepickerModifier,
        .getTextPickerModifier = NodeModifier::GetCJUITextPickerModifier,
        .getRatingModifier = NodeModifier::GetCJUIRatingModifier,
        .getSliderModifier = NodeModifier::GetCJUISliderModifier,
        .getDividerModifier = NodeModifier::GetCJUIDividerModifier,
        .getStackModifier = NodeModifier::GetCJUIStackModifier,
    #ifndef ARKUI_WEARABLE
        .getFolderStackModifier = NodeModifier::GetCJUIFolderStackModifier,
    #else
        .getFolderStackModifier = nullptr,
    #endif
        .getNavDestinationModifier = NodeModifier::GetCJUINavDestinationModifier,
        .getGridModifier = NodeModifier::GetCJUIGridModifier,
        .getGridColModifier = NodeModifier::GetCJUIGridColModifier,
        .getGridRowModifier = NodeModifier::GetCJUIGridRowModifier,
        .getPanelModifier = NodeModifier::GetCJUIPanelModifier,
        .getTextAreaModifier = NodeModifier::GetCJUITextAreaModifier,
        .getNavigationModifier = NodeModifier::GetCJUINavigationModifier,
        .getColumnModifier = NodeModifier::GetCJUIColumnModifier,
        .getRichEditorModifier = NodeModifier::GetCJUIRichEditorModifier,
        .getImageModifier = NodeModifier::GetCJUIImageModifier,
        .getVideoModifier = NodeModifier::GetCJUIVideoModifier,
        .getVideoControllerModifier = nullptr,
        .getNavigatorModifier = nullptr,
        .getNavRouterModifier = NodeModifier::GetCJUINavRouterModifier,
        .getNodeContainerModifier = NodeModifier::GetCJUINodeContainerModifier,
        .getPatternLockModifier = NodeModifier::GetCJUIPatternLockModifier,
    #ifndef ARKUI_WEARABLE
        .getColumnSplitModifier = NodeModifier::GetCJUIColumnSplitModifier,
    #else
        .getColumnSplitModifier = nullptr,
    #endif
        .getLineModifier = NodeModifier::GetCJUILineModifier,
        .getPathModifier = NodeModifier::GetCJUIPathModifier,
        .getPolygonModifier = NodeModifier::GetCJUIPolygonModifier,
        .getPolylineModifier = NodeModifier::GetCJUIPolylineModifier,
        .getSpanModifier = NodeModifier::GetCJUISpanModifier,
        .getImageAnimatorModifier = NodeModifier::GetCJUIImageAnimatorModifier,
        .getSideBarContainerModifier = NodeModifier::GetCJUISideBarContainerModifier,
    #ifndef ARKUI_WEARABLE
        .getCalendarPickerModifier = NodeModifier::GetCJUICalendarPickerModifier,
    #else
        .getCalendarPickerModifier = nullptr,
    #endif
        .getTextInputModifier = NodeModifier::GetCJUITextInputModifier,
        .getTabsModifier = NodeModifier::GetCJUITabsModifier,
    #ifndef ARKUI_WEARABLE
        .getStepperItemModifier = NodeModifier::GetCJUIStepperItemModifier,
    #else
        .getStepperItemModifier = nullptr,
    #endif
        .getHyperlinkModifier = NodeModifier::GetCJUIHyperlinkModifier,
        .getMarqueeModifier = NodeModifier::GetCJUIMarqueeModifier,
        .getMenuItemModifier = nullptr,
        .getMenuModifier = NodeModifier::GetCJUIMenuModifier,
        .getDatePickerModifier = NodeModifier::GetCJUIDatePickerModifier,
    #ifndef ARKUI_WEARABLE
        .getWaterFlowModifier = NodeModifier::GetCJUIWaterFlowModifier,
    #else
        .getWaterFlowModifier = nullptr,
    #endif
        .getAlphabetIndexerModifier = NodeModifier::GetCJUIAlphabetIndexerModifier,
        .getDataPanelModifier = NodeModifier::GetCJUIDataPanelModifier,
        .getGaugeModifier = NodeModifier::GetCJUIGaugeModifier,
        .getScrollModifier = NodeModifier::GetCJUIScrollModifier,
        .getGridItemModifier = NodeModifier::GetCJUIGridItemModifier,
        .getProgressModifier = NodeModifier::GetCJUIProgressModifier,
        .getCommonShapeModifier = NodeModifier::GetCJUICommonShapeModifier,
        .getShapeModifier = NodeModifier::GetCJUIShapeModifier,
        .getRectModifier = NodeModifier::GetCJUIRectModifier,
        .getSwiperModifier = NodeModifier::GetCJUISwiperModifier,
        .getListItemModifier = NodeModifier::GetCJUIListItemModifier,
        .getListModifier = NodeModifier::GetCJUIListModifier,
        .getListItemGroupModifier = NodeModifier::GetCJUIListItemGroupModifier,
    #ifdef QRCODEGEN_SUPPORT
        .getQRCodeModifier = NodeModifier::GetCJUIQRCodeModifier,
    #else
        .getQRCodeModifier = nullptr,
    #endif
        .getLoadingProgressModifier = NodeModifier::GetCJUILoadingProgressModifier,
        .getTextClockModifier = NodeModifier::GetCJUITextClockModifier,
        .getTextTimerModifier = NodeModifier::GetCJUITextTimerModifier,
        .getRenderNodeModifier = NodeModifier::GetCJUIRenderNodeModifier,
        .getFrameNodeModifier = NodeModifier::GetCJUIFrameNodeModifier,

    #ifdef PLUGIN_COMPONENT_SUPPORTED
        .getPluginModifier = NodeModifier::GetCJUIPluginModifier,
    #else
        .getPluginModifier = nullptr,
    #endif

    #ifdef XCOMPONENT_SUPPORTED
        .getXComponentModifier = NodeModifier::GetCJUIXComponentModifier,
    #else
        .getXComponentModifier = nullptr,
    #endif

        .getUIStateModifier = NodeModifier::GetCJUIStateModifier,

    #ifdef FORM_SUPPORTED
        .getFormComponentModifier = NodeModifier::GetCJUIFormComponentModifier,
    #else
        .getFormComponentModifier = nullptr,
    #endif
        .getFlexModifier = NodeModifier::GetCJUIFlexModifier, // FlexModifier
        .getScrollBarModifier = NodeModifier::GetCJUIScrollBarModifier, // ScrollBarModifier
        .getScrollerModifier = NodeModifier::GetCJUIScrollerModifier,
        .getTabContentModifier = NodeModifier::GetCJUITabContentModifier,
        .getTabsControllerModifier = nullptr, // TabsControllerModifier
        .getSwiperControllerModifier = NodeModifier::GetCJUISwiperControllerModifier,
        .getGestureModifier = NodeModifier::GetCJUIGestureModifier, // GestureModifier
        .getBadgeModifier = nullptr, // BadgeModifier
    #ifdef WEB_SUPPORTED
        .getWebModifier = NodeModifier::GetCJUIWebModifier, // WebModifier
    #else
        .getWebModifier = nullptr, // WebModifier
    #endif
        .getRefreshModifier = NodeModifier::GetCJUIRefreshModifier, // RefreshModifier
        .getMenuItemGroupModifier = nullptr, // MenuItemGroupModifier
        .getSearchControllerModifier = nullptr, // SearchControllerModifier
        .getSideBarModifier = nullptr, // SideBarModifier
        .getPatternLockControllerModifier = nullptr, // PatternLockControllerModifier
        .getTextTimerControllerModifier = nullptr, // TextTimerControllerModifier
        .getTextClockControllerModifier = nullptr, // TextClockControllerModifier
        .getRichEditorControllerModifier = nullptr, // RichEditorControllerModifier
        .getTextAreaControllerModifier = nullptr, // TextAreaControllerModifier
        .getRelativeContainerModifier = NodeModifier::GetCJUIRelativeContainerModifier, // RelativeContainerModifier
        .getNodeContentModifier = NodeModifier::GetCJUINodeContentModifier,
        .getParticleModifier = NodeModifier::GetCJUIParticleModifier,
        .getSymbolGlyphModifier = NodeModifier::GetCJUISymbolGlyphModifier,
        .getSymbolSpanModifier = NodeModifier::GetCJUISymbolSpanModifier,

    #ifdef MODEL_COMPONENT_SUPPORTED
        .getComponent3DModifier = NodeModifier::GetCJUIComponent3DModifier,
    #else
        .getComponent3DModifier = nullptr,
    #endif

        .getContainerSpanModifier = NodeModifier::GetCJUIContainerSpanModifier,
    };
    CHECK_INITIALIZED_FIELDS_END(modifiers, MODIFIER_COUNTS, BLANK_LINES, 0); // don't move this line
    return &modifiers;
}
}
