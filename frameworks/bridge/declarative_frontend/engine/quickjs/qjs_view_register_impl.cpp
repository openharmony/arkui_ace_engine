/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include <cstdint>

#include "base/log/log.h"
#include "bridge/declarative_frontend/interfaces/profiler/js_profiler.h"
#include "bridge/declarative_frontend/jsview/js_canvas_image_data.h"
#include "core/components_v2/inspector/inspector.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_view_register.h"
#include "frameworks/bridge/declarative_frontend/jsview/action_sheet/js_action_sheet.h"
#include "frameworks/bridge/declarative_frontend/jsview/dialog/js_alert_dialog.h"
#include "frameworks/bridge/declarative_frontend/jsview/dialog/js_custom_dialog_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_ability_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_ability_component_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_animator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_badge.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_blank.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_button.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_calendar.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_calendar_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_col.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_row.h"
#ifndef WEARABLE_PRODUCT
#include "frameworks/bridge/declarative_frontend/jsview/js_camera.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_canvas.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_canvas_gradient.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_canvas_path.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_checkbox.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_checkboxgroup.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_circle.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_clipboard.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_column.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_column_split.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_common_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_counter.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_data_panel.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_datepicker.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_distributed.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_divider.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_ellipse.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_environment.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_flex_impl.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_foreach.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_hyperlink.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_offscreen_rendering_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_path2d.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_render_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rendering_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rendering_context_settings.h"
#ifndef WEARABLE_PRODUCT
#include "frameworks/bridge/declarative_frontend/jsview/js_form.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_gauge.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_gesture.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_container.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_if_else.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image_animator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_indexer.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_line.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list_item_group.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_loading_progress.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_marquee.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigation.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_page_transition.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_path.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_pattern_lock.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_persistent.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_polygon.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_polyline.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_progress.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_qrcode.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_radio.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rect.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_refresh.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_relative_container.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_row.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_row_split.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_scroll.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_scroller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_search.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_select.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_sheet.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_side_bar.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_slider.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_sliding_panel.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_span.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_stack.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_stepper.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_stepper_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_swiper.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tab_content.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tabs.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tabs_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text_clock.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textarea.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textinput.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textpicker.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_texttimer.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_toggle.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_touch_handler.h"
#ifndef WEARABLE_PRODUCT
#include "frameworks/bridge/declarative_frontend/jsview/js_piece.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rating.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_remote_window.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_video.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_video_controller.h"
#ifdef WEB_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_richtext.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_web.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_web_controller.h"
#endif
#endif
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_plugin.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_local_storage.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_stack_processor.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_water_flow.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_water_flow_item.h"
#ifdef XCOMPONENT_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/menu/js_context_menu.h"
#include "frameworks/bridge/declarative_frontend/jsview/scroll_bar/js_scroll_bar.h"
#include "frameworks/bridge/declarative_frontend/sharedata/js_share_data.h"

namespace OHOS::Ace::Framework {

JSValue JsGetInspectorTree(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    if (ctx == nullptr) {
        return JS_UNDEFINED;
    }

    QJSContext::Scope scope(ctx);
    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }

    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        return JS_ThrowSyntaxError(ctx, "pipeline is null");
    }

    auto nodeInfos = V2::Inspector::GetInspectorTree(pipelineContext);
    JSValue result = JS_NewString(ctx, nodeInfos.c_str());
    return result;
}

JSValue JsGetInspectorByKey(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    QJSContext::Scope scope(ctx);
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one or two arguments");
    }
    if (!JS_IsString(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be string");
    }

    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }

    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        return JS_ThrowSyntaxError(ctx, "pipeline is null");
    }
    ScopedString targetString(ctx, argv[0]);
    std::string key = targetString.get();
    auto resultStr = V2::Inspector::GetInspectorNodeByKey(pipelineContext, key);
    JSValue result = JS_NewString(ctx, resultStr.c_str());
    return result;
}

JSValue JsSendEventByKey(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    if (argc != 3) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have 3 arguments");
    }

    QJSContext::Scope scp(ctx);
    if (!JS_IsString(argv[0]) || !JS_IsString(argv[2])) {
        return JS_ThrowSyntaxError(ctx, "parameter 'key' and 'params' must be string");
    }
    if (!JS_IsNumber(argv[1])) {
        return JS_ThrowSyntaxError(ctx, "parameter action must be number");
    }

    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        return JS_ThrowSyntaxError(ctx, "pipeline is null");
    }

    ScopedString targetString(ctx, argv[0]);
    std::string key = targetString.get();
    ScopedString valueString(ctx, argv[1]);
    auto action = StringToInt(valueString.get());
    ScopedString targetParam(ctx, argv[2]);
    std::string params = targetParam.get();

    auto result = V2::Inspector::SendEventByKey(pipelineContext, key, action, params);
    return JS_NewBool(ctx, result);
}

static V2::JsKeyEvent GetKeyEventFromJS(JSContext* ctx, JSValue value)
{
    V2::JsKeyEvent event;
    auto jsType = JS_GetPropertyStr(ctx, value, "type");
    auto type = static_cast<int32_t>(KeyAction::UNKNOWN);
    JS_ToInt32(ctx, &type, jsType);
    event.action = static_cast<KeyAction>(type);

    auto jsKeyCode = JS_GetPropertyStr(ctx, value, "keyCode");
    auto code = static_cast<int32_t>(KeyCode::KEY_UNKNOWN);
    JS_ToInt32(ctx, &code, jsKeyCode);
    event.code = static_cast<KeyCode>(code);

    auto jsKeySource = JS_GetPropertyStr(ctx, value, "keySource");
    JS_ToInt32(ctx, &event.sourceDevice, jsKeySource);

    auto jsDeviceId = JS_GetPropertyStr(ctx, value, "deviceId");
    JS_ToInt32(ctx, &event.deviceId, jsDeviceId);

    auto jsMetaKey = JS_GetPropertyStr(ctx, value, "metaKey");
    JS_ToInt32(ctx, &event.metaKey, jsMetaKey);

    auto jsTimestamp = JS_GetPropertyStr(ctx, value, "timestamp");
    JS_ToInt64(ctx, &event.timeStamp, jsTimestamp);

    return event;
}

JSValue JsSendKeyEvent(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have 1 arguments");
    }

    if (!JS_IsObject(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be object");
    }

    QJSContext::Scope scp(ctx);
    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        return JS_ThrowSyntaxError(ctx, "pipeline is null");
    }
    auto keyEvent = GetKeyEventFromJS(ctx, argv[0]);
    auto result = V2::Inspector::SendKeyEvent(pipelineContext, keyEvent);
    return JS_NewBool(ctx, result);
}

void JsBindViews(BindingTarget globalObj)
{
    JSViewAbstract::JSBind();
    JSContainerBase::JSBind();
    JSShapeAbstract::JSBind();
    JSView::JSBind(globalObj);
    JSAnimator::JSBind(globalObj);
    JSText::JSBind(globalObj);
    JSDatePicker::JSBind(globalObj);
    JSDatePickerDialog::JSBind(globalObj);
    JSTimePicker::JSBind(globalObj);
    JSTimePickerDialog::JSBind(globalObj);
    JSSpan::JSBind(globalObj);
    JSButton::JSBind(globalObj);
    JSCanvas::JSBind(globalObj);
    JSLazyForEach::JSBind(globalObj);
    JSList::JSBind(globalObj);
    JSListItem::JSBind(globalObj);
    JSListItemGroup::JSBind(globalObj);
    JSLoadingProgress::JSBind(globalObj);
    JSImage::JSBind(globalObj);
    JSImageAnimator::JSBind(globalObj);
    JSColumn::JSBind(globalObj);
    JSCounter::JSBind(globalObj);
    JSRow::JSBind(globalObj);
    JSGrid::JSBind(globalObj);
    JSGridItem::JSBind(globalObj);
    JSStack::JSBind(globalObj);
    JSStepper::JSBind(globalObj);
    JSStepperItem::JSBind(globalObj);
    JSForEach::JSBind(globalObj);
    JSDivider::JSBind(globalObj);
    JSProgress::JSBind(globalObj);
    JSSwiper::JSBind(globalObj);
    JSSwiperController::JSBind(globalObj);
    JSTextTimer::JSBind(globalObj);
    JSTextTimerController::JSBind(globalObj);
    JSSlidingPanel::JSBind(globalObj);
    JSNavigation::JSBind(globalObj);
    JSNavigator::JSBind(globalObj);
    JSColumnSplit::JSBind(globalObj);
    JSIfElse::JSBind(globalObj);
    JSEnvironment::JSBind(globalObj);
    JSViewContext::JSBind(globalObj);
    JSViewStackProcessor::JSBind(globalObj);
    JSLocalStorage::JSBind(globalObj);
    JSFlexImpl::JSBind(globalObj);
    JSScroll::JSBind(globalObj);
    JSScroller::JSBind(globalObj);
    JSScrollBar::JSBind(globalObj);
    JSToggle::JSBind(globalObj);
    JSGridRow::JSBind(globalObj);
    JSGridCol::JSBind(globalObj);
    JSSideBar::JSBind(globalObj);
    JSSlider::JSBind(globalObj);
    JSTextPicker::JSBind(globalObj);
    JSBlank::JSBind(globalObj);
    JSCalendar::JSBind(globalObj);
    JSPersistent::JSBind(globalObj);
    JSDistributed::JSBind(globalObj);
    JSRadio::JSBind(globalObj);
    JSCalendarController::JSBind(globalObj);
    JSRenderingContext::JSBind(globalObj);
    JSOffscreenRenderingContext::JSBind(globalObj);
    JSCanvasGradient::JSBind(globalObj);
    JSRenderImage::JSBind(globalObj);
    JSCanvasImageData::JSBind(globalObj);
    JSPath2D::JSBind(globalObj);
    JSRenderingContextSettings::JSBind(globalObj);
    JSQRCode::JSBind(globalObj);
    JSDataPanel::JSBind(globalObj);
    JSBadge::JSBind(globalObj);
    JSTextArea::JSBind(globalObj);
    JSTextAreaController::JSBind(globalObj);
    JSTextInput::JSBind(globalObj);
    JSTextInputController::JSBind(globalObj);
    JSTextClock::JSBind(globalObj);
    JSTextClockController::JSBind(globalObj);
    JSMarquee::JSBind(globalObj);
#ifdef PLUGIN_COMPONENT_SUPPORTED
    JSPlugin::JSBind(globalObj);
#endif
    JSSheet::JSBind(globalObj);
#ifdef FORM_SUPPORTED
    JSForm::JSBind(globalObj);
#endif
    JSRect::JSBind(globalObj);
    JSShape::JSBind(globalObj);
    JSSearch::JSBind(globalObj);
    JSSearchController::JSBind(globalObj);
    JSSelect::JSBind(globalObj);
    JSPath::JSBind(globalObj);
    JSCircle::JSBind(globalObj);
    JSLine::JSBind(globalObj);
    JSPolygon::JSBind(globalObj);
    JSPolyline::JSBind(globalObj);
    JSEllipse::JSBind(globalObj);
#ifdef REMOTE_WINDOW_SUPPORTED
    JSRemoteWindow::JSBind(globalObj);
#endif
#ifndef WEARABLE_PRODUCT
    JSPiece::JSBind(globalObj);
    JSRating::JSBind(globalObj);
    JSRefresh::JSBind(globalObj);
    JSCamera::JSBind(globalObj);
    JSVideo::JSBind(globalObj);
    JSVideoController::JSBind(globalObj);
#ifdef WEB_SUPPORTED
    JSRichText::JSBind(globalObj);
    JSWeb::JSBind(globalObj);
    JSWebController::JSBind(globalObj);
#endif
#endif
#ifdef XCOMPONENT_SUPPORTED
    JSXComponent::JSBind(globalObj);
    JSXComponentController::JSBind(globalObj);
#endif
    JSTabs::JSBind(globalObj);
    JSTabContent::JSBind(globalObj);
    JSTabsController::JSBind(globalObj);

    JSTouchHandler::JSBind(globalObj);
    JSGesture::JSBind(globalObj);
    JSPanGestureOption::JSBind(globalObj);
    JSPageTransition::JSBind(globalObj);
    JSRowSplit::JSBind(globalObj);
    JSColumnSplit::JSBind(globalObj);
    JSGridContainer::JSBind(globalObj);
    JSIndexer::JSBind(globalObj);
    JSGauge::JSBind(globalObj);
    JSHyperlink::JSBind(globalObj);
    JSClipboard::JSBind(globalObj);
    JSPatternLock::JSBind(globalObj);
    JSPatternLockController::JSBind(globalObj);
    JSTextPickerDialog::JSBind(globalObj);
    JSCheckbox::JSBind(globalObj);
    JSCheckboxGroup::JSBind(globalObj);
    JSWaterFlow::JSBind(globalObj);
    JSWaterFlowItem::JSBind(globalObj);
    JSRelativeContainer::JSBind(globalObj);
    JSCommonView::JSBind(globalObj);
    JSActionSheet::JSBind(globalObj);
    JSAlertDialog::JSBind(globalObj);
    JSContextMenu::JSBind(globalObj);
#ifdef ABILITY_COMPONENT_SUPPORTED
    JSAbilityComponent::JSBind(globalObj);
    JSAbilityComponentController::JSBind(globalObj);
#endif
    JSCustomDialogController::JSBind(globalObj);
    JSShareData::JSBind(globalObj);

    JsDragFunction::JSBind(globalObj);

    JSProfiler::JSBind(globalObj);
}

void CreatePageRoot(RefPtr<JsAcePage>& page, JSView* view)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto pageRootNode = view->CreateUINode();
        page->SetRootNode(pageRootNode);
    } else {
        auto rootComponent = view->CreateComponent();
        std::list<RefPtr<Component>> stackChildren;
        stackChildren.emplace_back(rootComponent);
        auto rootStackComponent = AceType::MakeRefPtr<StackComponent>(
            Alignment::TOP_LEFT, StackFit::INHERIT, Overflow::OBSERVABLE, stackChildren);
        rootStackComponent->SetMainStackSize(MainStackSize::MAX);
        auto rootComposed = AceType::MakeRefPtr<ComposedComponent>("0", "root");
        rootComposed->SetChild(rootStackComponent);
        page->SetRootComponent(rootComposed);
        page->SetPageTransition(view->BuildPageTransitionComponent());
    }
}

} // namespace OHOS::Ace::Framework
