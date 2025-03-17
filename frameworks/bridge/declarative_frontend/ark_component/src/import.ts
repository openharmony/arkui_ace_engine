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

/// <reference path="./ArkClassMock.ts" />

/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/ability_component.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/action_sheet.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/alert_dialog.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/alphabet_indexer.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/animator.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/badge.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/blank.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/button.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/calendar.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/calendar_picker.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/canvas.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/checkbox.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/checkboxgroup.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/circle.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/column.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/column_split.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/common.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/common_ts_ets_api.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/container_span.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/component3d.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/context_menu.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/counter.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/custom_dialog_controller.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/data_panel.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/date_picker.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/divider.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/effect_component.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/ellipse.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/enums.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/flex.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/flow_item.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/form_component.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/form_link.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/for_each.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/gauge.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/gesture.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/grid.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/gridItem.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/grid_col.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/grid_container.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/grid_row.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/hyperlink.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/image.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/image_animator.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/image_span.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/index-full.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/lazy_for_each.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/lazy_grid_layout.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/line.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/list.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/list_item.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/list_item_group.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/loading_progress.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/location_button.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/marquee.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/matrix2d.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/menu.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/menu_item.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/menu_item_group.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/navigation.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/navigator.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/nav_destination.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/nav_router.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/page_transition.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/panel.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/particle.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/paste_button.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/path.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/pattern_lock.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/plugin_component.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/polygon.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/polyline.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/progress.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/qrcode.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/radio.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/rating.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/rect.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/refresh.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/relative_container.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/remote_window.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/rich_editor.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/rich_text.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/root_scene.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/row.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/row_split.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/save_button.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/screen.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/scroll.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/scroll_bar.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/search.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/security_component.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/select.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/shape.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/sidebar.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/slider.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/span.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/stack.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/state_management.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/stepper.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/stepper_item.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/swiper.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/symbolglyph.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/symbol_span.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/tabs.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/tab_content.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/text.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/text_area.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/text_clock.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/text_input.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/text_picker.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/text_timer.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/time_picker.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/toggle.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/ui_extension_component.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/units.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/video.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/water_flow.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/web.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/window_scene.d.ts" />
/// <reference path="../../../../../../../../out/sdk/ohos-sdk/windows/ets/component/xcomponent.d.ts" />