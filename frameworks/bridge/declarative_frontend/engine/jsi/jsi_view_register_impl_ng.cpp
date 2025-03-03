/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "base/geometry/ng/size_t.h"
#include "bridge/declarative_frontend/jsview/js_base_node.h"
#include "bridge/declarative_frontend/jsview/js_content_slot.h"
#include "bridge/declarative_frontend/jsview/js_dynamic_component.h"
#include "bridge/declarative_frontend/jsview/js_isolated_component.h"
#include "bridge/declarative_frontend/jsview/js_layout_manager.h"
#include "bridge/declarative_frontend/jsview/js_mock.h"
#include "bridge/declarative_frontend/jsview/js_node_container.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"
#include "frameworks/bridge/declarative_frontend/ark_theme/theme_apply/js_with_theme.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_gesture_recognizer.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_should_built_in_recognizer_parallel_with_function.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_object_template.h"
#include "frameworks/bridge/declarative_frontend/jsview/action_sheet/js_action_sheet.h"
#include "frameworks/bridge/declarative_frontend/jsview/canvas/js_canvas.h"
#include "frameworks/bridge/declarative_frontend/jsview/canvas/js_canvas_pattern.h"
#include "frameworks/bridge/declarative_frontend/jsview/canvas/js_offscreen_canvas.h"
#include "frameworks/bridge/declarative_frontend/jsview/canvas/js_rendering_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/dialog/js_custom_dialog_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_animator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_badge.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_blank.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_button.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_calendar.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_calendar_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_calendar_picker.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_checkbox.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_checkboxgroup.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_circle.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_circle_shape.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_clipboard.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_column_split.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_common_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_span.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_counter.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_data_panel.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_datepicker.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_divider.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_dump_log.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_ellipse.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_ellipse_shape.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_environment.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_flex_impl.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_foreach.h"
#ifdef FORM_BUTTON_COMPONENT_SUPPORT
#include "frameworks/bridge/declarative_frontend/jsview/js_form_button.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_form_link.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_gauge.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_col.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_container.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_row.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_hyperlink.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_if_else.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image_animator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image_span.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_indexer.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_keyboard_avoid.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_line.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list_item_group.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_loading_progress.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_local_storage.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_marquee.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_menu.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_menu_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_menu_item_group.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_nav_path_stack.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navdestination.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigation.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navrouter.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_page_transition.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_path.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_path_shape.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_persistent.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_polygon.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_polyline.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_progress.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_radio.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rating.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rect.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rect_shape.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_recycle_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_refresh.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_repeat.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_repeat_virtual_scroll.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_repeat_virtual_scroll_2.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_row.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_row_split.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_scope_util.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_scroll.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_search.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_select.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_side_bar.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_slider.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_sliding_panel.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_span.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_state_mgmt_profiler.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_stepper.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_stepper_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_swiper.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_symbol.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_symbol_span.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tab_content.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tabs.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tabs_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text_clock.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textarea.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textfield.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textinput.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textpicker.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_texttimer.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_toggle.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_stack_processor.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_water_flow.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_water_flow_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/scroll_bar/js_scroll_bar.h"
#include "frameworks/bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_app_bar_view.h"
#include "frameworks/bridge/declarative_frontend/style_string/js_span_string.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_modal_view.h"

#ifdef USE_COMPONENTS_LIB
#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_value.h"
#else
#include "frameworks/bridge/declarative_frontend/jsview/js_pattern_lock.h"
#ifdef QRCODEGEN_SUPPORT
#include "frameworks/bridge/declarative_frontend/jsview/js_qrcode.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_relative_container.h"
#endif

#ifdef VIDEO_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_video.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_video_controller.h"
#endif
#ifdef WINDOW_SCENE_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_embedded_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_security_ui_extension.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_ui_extension.h"
#endif
#ifdef ABILITY_COMPONENT_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_ability_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_ability_component_controller.h"
#endif
#ifdef FORM_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_form.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_form_menu_item.h"
#endif
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_plugin.h"
#endif
#ifdef WEB_SUPPORTED
#include "bridge/declarative_frontend/jsview/js_web.h"
#include "bridge/declarative_frontend/jsview/js_web_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_richtext.h"
#endif
#ifdef REMOTE_WINDOW_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_remote_window.h"
#endif
#if defined(XCOMPONENT_SUPPORTED)
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#endif
#if defined(MODEL_COMPONENT_SUPPORTED)
#include "frameworks/bridge/declarative_frontend/jsview/js_sceneview.h"
#endif
#if defined(WINDOW_SCENE_SUPPORTED)
#include "frameworks/bridge/declarative_frontend/jsview/window_scene/js_root_scene.h"
#include "frameworks/bridge/declarative_frontend/jsview/window_scene/js_screen.h"
#include "frameworks/bridge/declarative_frontend/jsview/window_scene/js_window_scene.h"
#endif
#include "bridge/declarative_frontend/interfaces/profiler/js_profiler.h"
#include "bridge/declarative_frontend/jsview/js_location_button.h"
#include "bridge/declarative_frontend/jsview/js_paste_button.h"
#include "bridge/declarative_frontend/jsview/js_richeditor.h"
#include "bridge/declarative_frontend/jsview/js_save_button.h"
#include "bridge/declarative_frontend/jsview/menu/js_context_menu.h"
#include "bridge/declarative_frontend/sharedata/js_share_data.h"
#include "bridge/declarative_frontend/jsview/text_menu/js_text_menu.h"
#ifdef EFFECT_COMPONENT_SUPPORTED
#include "bridge/declarative_frontend/jsview/js_effect_component.h"
#endif

namespace OHOS::Ace::Framework {


void CleanPageNode(const RefPtr<NG::FrameNode>& pageNode)
{
    if (pageNode->GetChildren().empty()) {
        return;
    }

    auto oldChild = AceType::DynamicCast<NG::CustomNode>(pageNode->GetChildren().front());
    if (oldChild) {
#ifdef PLUGIN_COMPONENT_SUPPORTED
        if (Container::CurrentId() >= MIN_PLUGIN_SUBCONTAINER_ID) {
            oldChild->FireOnDisappear();
        }
#endif
        oldChild->Reset();
    }
    pageNode->Clean();
}

void UpdateRootComponent(const EcmaVM* vm, const panda::Local<panda::ObjectRef>& obj)
{
    auto* view = JsiObjectTemplate::GetNativeView(obj, vm);
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        return;
    }

    auto container = Container::Current();
    if (!container) {
        return;
    }

    RefPtr<NG::FrameNode> pageNode;
#ifdef PLUGIN_COMPONENT_SUPPORTED
    if (Container::CurrentId() >= MIN_PLUGIN_SUBCONTAINER_ID) {
        auto pluginContainer = PluginManager::GetInstance().GetPluginSubContainer(Container::CurrentId());
        CHECK_NULL_VOID(pluginContainer);
        pageNode = pluginContainer->GetPluginNode().Upgrade();
        CHECK_NULL_VOID(pageNode);
    } else
#endif
    {
        auto frontEnd = AceType::DynamicCast<DeclarativeFrontendNG>(container->GetFrontend());
        CHECK_NULL_VOID(frontEnd);
        auto pageRouterManager = frontEnd->GetPageRouterManager();
        CHECK_NULL_VOID(pageRouterManager);
        pageNode = pageRouterManager->GetCurrentPageNode();
        CHECK_NULL_VOID(pageNode);
    }
    Container::SetCurrentUsePartialUpdate(!view->isFullUpdate());
    CleanPageNode(pageNode);
    auto pageRootNode = AceType::DynamicCast<NG::UINode>(view->CreateViewNode());
    CHECK_NULL_VOID(pageRootNode);
    pageRootNode->MountToParent(pageNode);
    // update page life cycle function.
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    // Register RenderDone callback to jsView so that js view can notify pagePattern the render function has been
    // finish. The onPageShow life cycle must be after the InitialRender function execution.
    view->RegisterRenderDoneCallback([weak = AceType::WeakClaim(AceType::RawPtr(pagePattern))]() {
        auto pagePattern = weak.Upgrade();
        CHECK_NULL_VOID(pagePattern);
        pagePattern->MarkRenderDone();
    });
    pagePattern->SetOnPageShow([weak = Referenced::WeakClaim(view)]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnShow();
        }
    });
    pagePattern->SetOnPageHide([weak = Referenced::WeakClaim(view)]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnHide();
        }
    });
    pagePattern->SetOnBackPressed([weak = Referenced::WeakClaim(view)]() {
        auto view = weak.Upgrade();
        if (view) {
            return view->FireOnBackPress();
        }
        return false;
    });
    auto customNode = AceType::DynamicCast<NG::CustomNodeBase>(pageRootNode);
    pagePattern->SetPageTransitionFunc(
        [weakCustom = WeakPtr<NG::CustomNodeBase>(customNode), weakPage = WeakPtr<NG::FrameNode>(pageNode)]() {
            auto custom = weakCustom.Upgrade();
            auto page = weakPage.Upgrade();
            if (custom && page) {
                NG::ScopedViewStackProcessor scopedViewStackProcessor;
                NG::ViewStackProcessor::GetInstance()->SetPageNode(page);
                custom->CallPageTransitionFunction();
                NG::ViewStackProcessor::GetInstance()->SetPageNode(nullptr);
            }
        });
}

#ifdef USE_COMPONENTS_LIB
void JSBindLibs(const std::string& moduleName, const std::string& exportModuleName, bool isController = false)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    std::shared_ptr<JsValue> global = runtime->GetGlobal();
    std::shared_ptr<JsValue> requireNapiFunc = global->GetProperty(runtime, "requireNapi");
    std::vector<std::shared_ptr<JsValue>> argv = { runtime->NewString(moduleName) };
    std::shared_ptr<JsValue> napiObj = requireNapiFunc->Call(runtime, global, argv, argv.size());
    if (napiObj && !napiObj->IsUndefined(runtime)) {
        if (isController) {
            global->SetProperty(runtime, exportModuleName, napiObj->GetProperty(runtime, exportModuleName));
        } else {
            global->SetProperty(runtime, exportModuleName, napiObj);
        }
    }
}
#endif

void JsUINodeRegisterCleanUp(BindingTarget globalObj)
{
    // globalObj is panda::Local<panda::ObjectRef>
    const auto globalObject = JSRef<JSObject>::Make(globalObj);

    const JSRef<JSVal> cleanUpIdleTask = globalObject->GetProperty("uiNodeCleanUpIdleTask");
    if (cleanUpIdleTask->IsFunction()) {
        const auto globalFunc = JSRef<JSFunc>::Cast(cleanUpIdleTask);
        const std::function<void(void)> callback = [jsFunc = globalFunc, globalObject = globalObject]() {
            jsFunc->Call(globalObject);
        };
        ElementRegister::GetInstance()->RegisterJSCleanUpIdleTaskFunc(callback);
    }
}

void JsBindViews(BindingTarget globalObj, void* nativeEngine)
{
    JSViewAbstract::JSBind(globalObj);
    JSViewStackProcessor::JSBind(globalObj);
    JSContainerBase::JSBind(globalObj);
    JSScrollableBase::JSBind(globalObj);
    JSView::JSBind(globalObj);
    JSShapeAbstract::JSBind(globalObj);
    JSText::JSBind(globalObj);
    JSTextController::JSBind(globalObj);
    JSColumn::JSBind(globalObj);
    JSRow::JSBind(globalObj);
    JSStack::JSBind(globalObj);
    JSImage::JSBind(globalObj);
    JSLazyForEach::JSBind(globalObj);
    JSList::JSBind(globalObj);
    JSListItem::JSBind(globalObj);
    JSLocalStorage::JSBind(globalObj);
    JSStateMgmtProfiler::JSBind(globalObj);
    JSPersistent::JSBind(globalObj);
    JSEnvironment::JSBind(globalObj);
    JSFlexImpl::JSBind(globalObj);
    JSSpan::JSBind(globalObj);
    JSNativeCustomSpan::JSBind(globalObj);
    JSSpanString::JSBind(globalObj);
    JSMutableSpanString::JSBind(globalObj);
    JSFontSpan::JSBind(globalObj);
    JSDecorationSpan::JSBind(globalObj);
    JSBaselineOffsetSpan::JSBind(globalObj);
    JSLetterSpacingSpan::JSBind(globalObj);
    JSGestureSpan::JSBind(globalObj);
    JSTextShadowSpan::JSBind(globalObj);
    JSBackgroundColorSpan::JSBind(globalObj);
    JSImageAttachment::JSBind(globalObj);
    JSParagraphStyleSpan::JSBind(globalObj);
    JSLineHeightSpan::JSBind(globalObj);
    JSUrlSpan::JSBind(globalObj);
    JSTabs::JSBind(globalObj);
    JSTabContent::JSBind(globalObj);
    JSTabsController::JSBind(globalObj);
#ifndef ARKUI_WEARABLE
    JSCalendarPicker::JSBind(globalObj);
    JSCalendarPickerDialog::JSBind(globalObj);
#endif
    JSForEach::JSBind(globalObj);
    JSRepeat::JSBind(globalObj);
    JSRepeatVirtualScroll::JSBind(globalObj);
    JSIfElse::JSBind(globalObj);
    JSDivider::JSBind(globalObj);
    JSScroll::JSBind(globalObj);
    JSNavigator::JSBind(globalObj);
    JSToggle::JSBind(globalObj);
    JSCounter::JSBind(globalObj);
    JSScopeUtil::JSBind(globalObj);
    JSWithTheme::JSBind(globalObj);
    JSRichEditor::JSBind(globalObj);
    JSRichEditorController::JSBind(globalObj);
    JSRichEditorStyledStringController::JSBind(globalObj);
    JSLayoutManager::JSBind(globalObj);
    JSContainerModal::JSBind(globalObj);
    JSAppBar::JSBind(globalObj);
#ifdef VIDEO_SUPPORTED
    JSVideo::JSBind(globalObj);
    JSVideoController::JSBind(globalObj);
#endif
#ifdef ABILITY_COMPONENT_SUPPORTED
    JSAbilityComponent::JSBind(globalObj);
    JSAbilityComponentController::JSBind(globalObj);
#endif
#ifdef FORM_SUPPORTED
    JSForm::JSBind(globalObj);
    JSFormMenuItem::JSBind(globalObj);
#endif
#ifdef PLUGIN_COMPONENT_SUPPORTED
    JSPlugin::JSBind(globalObj);
#endif
#ifdef WEB_SUPPORTED
    JSRichText::JSBind(globalObj);
    JSWeb::JSBind(globalObj);
#endif
#ifdef REMOTE_WINDOW_SUPPORTED
    JSRemoteWindow::JSBind(globalObj);
#endif
#if defined(XCOMPONENT_SUPPORTED)
    JSXComponent::JSBind(globalObj);
    JSXComponentController::JSBind(globalObj);
#endif
#if defined(MODEL_COMPONENT_SUPPORTED)
    JSSceneView::JSBind(globalObj);
#endif
#if defined(WINDOW_SCENE_SUPPORTED)
    JSEmbeddedComponent::JSBind(globalObj);
    JSWindowScene::JSBind(globalObj);
    JSRootScene::JSBind(globalObj);
    JSScreen::JSBind(globalObj);
    JSSecurityUIExtensionProxy::JSBind(globalObj);
    JSSecurityUIExtension::JSBind(globalObj);
    JSUIExtension::JSBind(globalObj);
    JSUIExtensionProxy::JSBind(globalObj);
#if defined(DYNAMIC_COMPONENT_SUPPORT)
    JSDynamicComponent::JSBind(globalObj);
    JSIsolatedComponent::JSBind(globalObj);
#endif
#endif
    JSRating::JSBind(globalObj);
    JSGrid::JSBind(globalObj);
    JSGridItem::JSBind(globalObj);
    JSSwiper::JSBind(globalObj);
    JSImageSpan::JSBind(globalObj);
    JSScroller::JSBind(globalObj);
    JSListScroller::JSBind(globalObj);
    JSScrollBar::JSBind(globalObj);
    JSButton::JSBind(globalObj);
    JSRadio::JSBind(globalObj);
    JSRectShape::JSBind(globalObj);
    JSEllipseShape::JSBind(globalObj);
    JSCircleShape::JSBind(globalObj);
    JSPathShape::JSBind(globalObj);
    JSRect::JSBind(globalObj);
    JSAnimator::JSBind(globalObj);
    JSCanvas::JSBind(globalObj);
    JSOffscreenCanvas::JSBind(globalObj, nativeEngine);
    JSListItemGroup::JSBind(globalObj);
    JSLoadingProgress::JSBind(globalObj);
    JSImageAnimator::JSBind(globalObj);
    JSProgress::JSBind(globalObj);
    JSGridContainer::JSBind(globalObj);
    JSSlider::JSBind(globalObj);
    JSGridRow::JSBind(globalObj);
    JSGridCol::JSBind(globalObj);
#ifndef ARKUI_WEARABLE
    JSStepper::JSBind(globalObj);
    JSStepperItem::JSBind(globalObj);
    JSSideBar::JSBind(globalObj);
#endif
    JSBlank::JSBind(globalObj);
    JSCalendar::JSBind(globalObj);
    JSShape::JSBind(globalObj);
    JSPath::JSBind(globalObj);
    JSCircle::JSBind(globalObj);
    JSLine::JSBind(globalObj);
    JSPolygon::JSBind(globalObj);
    JSPolyline::JSBind(globalObj);
    JSEllipse::JSBind(globalObj);
    JSTextPicker::JSBind(globalObj);
    JSTimePicker::JSBind(globalObj);
    JSDatePicker::JSBind(globalObj);
    JSPageTransition::JSBind(globalObj);
#ifndef ARKUI_WEARABLE
    JSTextPickerDialog::JSBind(globalObj);
    JSTimePickerDialog::JSBind(globalObj);
    JSDatePickerDialog::JSBind(globalObj);
    JSRowSplit::JSBind(globalObj);
    JSColumnSplit::JSBind(globalObj);
#endif
    JSIndexer::JSBind(globalObj);
    JSHyperlink::JSBind(globalObj);
    JSActionSheet::JSBind(globalObj);
    JSAlertDialog::JSBind(globalObj);
    JSTextArea::JSBind(globalObj);
    JSTextInput::JSBind(globalObj);
    JSTextClock::JSBind(globalObj);
    JSDataPanel::JSBind(globalObj);
    JSBadge::JSBind(globalObj);
    JSGauge::JSBind(globalObj);
    JSMarquee::JSBind(globalObj);
    JSMenu::JSBind(globalObj);
    JSMenuItem::JSBind(globalObj);
    JSMenuItemGroup::JSBind(globalObj);
    JSGesture::JSBind(globalObj);
    JSPanGestureOption::JSBind(globalObj);
    JSSwiperController::JSBind(globalObj);
    JSCalendarController::JSBind(globalObj);
    JSCanvasGradient::JSBind(globalObj);
    JSRenderImage::JSBind(globalObj, nativeEngine);
    JSCanvasImageData::JSBind(globalObj);
    JSRenderingContextSettings::JSBind(globalObj);
    JSMatrix2d::JSBind(globalObj);
    JSSearch::JSBind(globalObj);
#ifndef ARKUI_WEARABLE
    JSSelect::JSBind(globalObj);
#endif
    JSSearchController::JSBind(globalObj);
    JSTextClockController::JSBind(globalObj);
    JSClipboard::JSBind(globalObj);
    JSTextTimer::JSBind(globalObj);
    JSTextAreaController::JSBind(globalObj);
    JSTextInputController::JSBind(globalObj);
    JSTextTimerController::JSBind(globalObj);
    JSCheckbox::JSBind(globalObj);
    JSCheckboxGroup::JSBind(globalObj);
    JSRefresh::JSBind(globalObj);
#ifndef ARKUI_WEARABLE
    JSWaterFlow::JSBind(globalObj);
    JSWaterFlowItem::JSBind(globalObj);
#endif
    JSCommonView::JSBind(globalObj);
    JSRecycleView::JSBind(globalObj);
    JSLinearGradient::JSBind(globalObj);
    JSNavigation::JSBind(globalObj);
    JSNavPathStack::JSBind(globalObj);
    JSTextField::JSBind(globalObj);
    JSCustomDialogController::JSBind(globalObj);
    JSNavDestination::JSBind(globalObj);
    JSNavRouter::JSBind(globalObj);
    JSViewContext::JSBind(globalObj);
    JSSlidingPanel::JSBind(globalObj);
    JSCanvasPattern::JSBind(globalObj);
    JSRenderingContext::JSBind(globalObj);
    JSOffscreenRenderingContext::JSBind(globalObj);
    JSPath2D::JSBind(globalObj);
    JSDumpLog::JSBind(globalObj);
    JSDumpRegister::JSBind(globalObj);
    JSKeyboardAvoid::JSBind(globalObj);
    JSSymbol::JSBind(globalObj);
    JSSymbolSpan::JSBind(globalObj);
    JSContainerSpan::JSBind(globalObj);
    JsDragFunction::JSBind(globalObj);
#ifdef USE_COMPONENTS_LIB
#ifdef QRCODEGEN_SUPPORT
    JSBindLibs("arkui.qrcode", "QRCode");
#endif
    JSBindLibs("arkui.relativeContainer", "RelativeContainer");
    JSBindLibs("arkui.patternlock", "PatternLock");
    JSBindLibs("arkui.patternlockcontroller", "PatternLockController", true);
#else
#ifdef QRCODEGEN_SUPPORT
    JSQRCode::JSBind(globalObj);
#endif
    JSRelativeContainer::JSBind(globalObj);
    JSPatternLock::JSBind(globalObj);
    JSPatternLockController::JSBind(globalObj);
#endif
    // add missing binds to ng build
#ifndef CROSS_PLATFORM
    JSCalendarPicker::JSBind(globalObj);
    JSContextMenu::JSBind(globalObj);
    JSTextMenu::JSBind(globalObj);
#ifdef EFFECT_COMPONENT_SUPPORTED
    JSEffectComponent::JSBind(globalObj);
#endif
    JSFormLink::JSBind(globalObj);
#ifdef FORM_BUTTON_COMPONENT_SUPPORT
    JSFormButton::JSBind(globalObj);
#endif
    JSLocationButton::JSBind(globalObj);
    JSPasteButton::JSBind(globalObj);
    JSProfiler::JSBind(globalObj);
    JSSaveButton::JSBind(globalObj);
    JSShareData::JSBind(globalObj);
#ifdef WEB_SUPPORTED
    JSWeb::JSBind(globalObj);
    JSWebController::JSBind(globalObj);
#endif
#endif
    JSNodeContainer::JSBind(globalObj);
    JSBaseNode::JSBind(globalObj);
    JSContentSlot::JSBind(globalObj);
    JSNodeContent::JSBind(globalObj);
    JSGestureRecognizer::JSBind(globalObj);
    JSEventTargetInfo::JSBind(globalObj);
    JSScrollableTargetInfo::JSBind(globalObj);
    JSPanRecognizer::JSBind(globalObj);
    JSTapRecognizer::JSBind(globalObj);
    JSLongPressRecognizer::JSBind(globalObj);
    JSSwipeRecognizer::JSBind(globalObj);
    JSPinchRecognizer::JSBind(globalObj);
    JSRotationRecognizer::JSBind(globalObj);
}

void JsBindWorkerViews(BindingTarget globalObj, void* nativeEngine)
{
    JSCanvasGradient::JSBind(globalObj);
    JSCanvasPattern::JSBind(globalObj);
    JSMatrix2d::JSBind(globalObj);
    JSOffscreenCanvas::JSBind(globalObj, nativeEngine);
    JSOffscreenRenderingContext::JSBind(globalObj);
    JSRenderingContextSettings::JSBind(globalObj);
    JSRenderImage::JSBind(globalObj, nativeEngine);
    JSPath2D::JSBind(globalObj);
    JSCanvasImageData::JSBind(globalObj);
    JSMock::JSBind(globalObj);
}

} // namespace OHOS::Ace::Framework
