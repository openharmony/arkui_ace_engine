/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "base/i18n/localization.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "frameworks/bridge/card_frontend/card_frontend_declarative.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_object_template.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_view_register.h"
#include "frameworks/bridge/declarative_frontend/frontend_delegate_declarative.h"
#include "frameworks/bridge/declarative_frontend/jsview/action_sheet/js_action_sheet.h"
#include "frameworks/bridge/declarative_frontend/jsview/dialog/js_alert_dialog.h"
#include "frameworks/bridge/declarative_frontend/jsview/dialog/js_custom_dialog_controller.h"
#ifdef ABILITY_COMPONENT_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_ability_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_ability_component_controller.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_animator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_badge.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_blank.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_button.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_calendar.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_calendar_controller.h"
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
#ifdef FORM_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_form.h"
#endif
#ifdef WEB_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_richtext.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_web.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_web_controller.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_gauge.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_gesture.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_container.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_hyperlink.h"
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
#include "frameworks/bridge/declarative_frontend/jsview/js_local_storage.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_marquee.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navdestination.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigation.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navrouter.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_pan_handler.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_path.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_path2d.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_pattern_lock.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_persistent.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_polygon.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_polyline.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_progress.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_qrcode.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_relative_container.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_slider.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textpicker.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_toggle.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_plugin.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_offscreen_canvas.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_offscreen_rendering_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_page_transition.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_radio.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rect.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_refresh.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_render_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rendering_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rendering_context_settings.h"
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
#include "frameworks/bridge/declarative_frontend/jsview/js_texttimer.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_touch_handler.h"
#ifdef REMOTE_WINDOW_SUPPORTED
#include "frameworks/bridge/declarative_frontend/jsview/js_remote_window.h"
#endif
#ifndef WEARABLE_PRODUCT
#include "frameworks/bridge/declarative_frontend/jsview/js_piece.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rating.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_video.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_video_controller.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_col.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_row.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_measure_layout.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_stack_processor.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_water_flow.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_water_flow_item.h"

#if defined(XCOMPONENT_SUPPORTED)
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#endif

#include "frameworks/bridge/declarative_frontend/interfaces/profiler/js_profiler.h"
#include "frameworks/bridge/declarative_frontend/jsview/menu/js_context_menu.h"
#include "frameworks/bridge/declarative_frontend/jsview/scroll_bar/js_scroll_bar.h"
#include "frameworks/bridge/declarative_frontend/sharedata/js_share_data.h"

#if defined(PREVIEW)
#include "frameworks/bridge/declarative_frontend/jsview/js_previewer_mock.h"
#endif

namespace OHOS::Ace::Framework {

void UpdateRootComponent(const panda::Local<panda::ObjectRef>& obj)
{
    auto* view = static_cast<JSView*>(obj->GetNativePointerField(0));
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        LOGE("loadDocument: argument provided is not a View!");
        return;
    }

    auto container = Container::Current();
    if (!container) {
        LOGE("loadDocument: Container is null");
        return;
    }
    if (container->IsUseNewPipeline()) {
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
            auto frontEnd = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
            CHECK_NULL_VOID(frontEnd);
            auto pageRouterManager = frontEnd->GetPageRouterManager();
            CHECK_NULL_VOID(pageRouterManager);
            pageNode = pageRouterManager->GetCurrentPageNode();
            CHECK_NULL_VOID(pageNode);
        }
        Container::SetCurrentUsePartialUpdate(!view->isFullUpdate());
        if (!pageNode->GetChildren().empty()) {
            LOGW("the page has already add node, clean");
            auto oldChild = AceType::DynamicCast<NG::CustomNode>(pageNode->GetChildren().front());
            if (oldChild) {
                oldChild->Reset();
            }
            pageNode->Clean();
        }
        auto pageRootNode = AceType::DynamicCast<NG::UINode>(view->CreateViewNode());
        CHECK_NULL_VOID(pageRootNode);
        pageRootNode->MountToParent(pageNode);
        // update page life cycle function.
        auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
        CHECK_NULL_VOID(pagePattern);
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
        return;
    }

    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    auto page = JsiDeclarativeEngineInstance::GetStagingPage(Container::CurrentId());
    JsiDeclarativeEngineInstance::RootViewHandle(obj);

    LOGI("Load Document setting root view, page[%{public}d]", page->GetPageId());
    Container::SetCurrentUsePartialUpdate(!view->isFullUpdate());
    LOGD("Loading page root component: Setting pipeline to use %{public}s.",
        view->isFullUpdate() ? "Full Update" : "Partial Update");
    auto rootComponent = AceType::DynamicCast<Component>(view->CreateViewNode());
    std::list<RefPtr<Component>> stackChildren;
    stackChildren.emplace_back(rootComponent);
    auto rootStackComponent = AceType::MakeRefPtr<StackComponent>(
        Alignment::TOP_LEFT, StackFit::INHERIT, Overflow::OBSERVABLE, stackChildren);
    rootStackComponent->SetMainStackSize(MainStackSize::MAX);
    auto rootComposed = AceType::MakeRefPtr<ComposedComponent>("0", "root");
    rootComposed->SetChild(rootStackComponent);
    page->SetRootComponent(rootComposed);
    auto pageTransitionComponent = ViewStackProcessor::GetInstance()->GetPageTransitionComponent();
    ViewStackProcessor::GetInstance()->ClearPageTransitionComponent();
    page->SetPageTransition(pageTransitionComponent);

    // We are done, tell to the JSAgePage
    page->SetPageCreated();
    auto weak = Referenced::WeakClaim(view);
    page->SetDeclarativeOnPageAppearCallback([weak]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnShow();
        }
    });
    page->SetDeclarativeOnPageDisAppearCallback([weak]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnHide();
        }
    });
    page->SetDeclarativeOnBackPressCallback([weak]() {
        auto view = weak.Upgrade();
        if (view) {
            return view->FireOnBackPress();
        }
        return false;
    });
    page->SetDeclarativeOnPageRefreshCallback([weak]() {
        auto view = weak.Upgrade();
        if (view) {
            view->MarkNeedUpdate();
        }
    });
    page->SetDeclarativeOnUpdateWithValueParamsCallback([weak](const std::string& params) {
        auto view = weak.Upgrade();
        if (view && !params.empty()) {
            view->ExecuteUpdateWithValueParams(params);
        }
    });
}

static const std::unordered_map<std::string, std::function<void(BindingTarget)>> bindFuncs = {
    { "Flex", JSFlexImpl::JSBind },
    { "Text", JSText::JSBind },
    { "Animator", JSAnimator::JSBind },
    { "SpringProp", JSAnimator::JSBind },
    { "SpringMotion", JSAnimator::JSBind },
    { "ScrollMotion", JSAnimator::JSBind },
    { "Animator", JSAnimator::JSBind },
    { "Span", JSSpan::JSBind },
    { "Button", JSButton::JSBind },
    { "Canvas", JSCanvas::JSBind },
    { "OffscreenCanvas", JSOffscreenCanvas::JSBind },
    { "LazyForEach", JSLazyForEach::JSBind },
    { "List", JSList::JSBind },
    { "ListItem", JSListItem::JSBind },
    { "ListItemGroup", JSListItemGroup::JSBind },
    { "LoadingProgress", JSLoadingProgress::JSBind },
    { "Image", JSImage::JSBind },
    { "ImageAnimator", JSImageAnimator::JSBind },
    { "Counter", JSCounter::JSBind },
    { "Progress", JSProgress::JSBind },
    { "Column", JSColumn::JSBind },
    { "Row", JSRow::JSBind },
    { "Grid", JSGrid::JSBind },
    { "GridItem", JSGridItem::JSBind },
    { "GridContainer", JSGridContainer::JSBind },
    { "Slider", JSSlider::JSBind },
    { "Stack", JSStack::JSBind },
    { "ForEach", JSForEach::JSBind },
    { "Divider", JSDivider::JSBind },
    { "Swiper", JSSwiper::JSBind },
    { "Panel", JSSlidingPanel::JSBind },
    { "NavDestination", JSNavDestination::JSBind },
    { "Navigation", JSNavigation::JSBind },
    { "Navigator", JSNavigator::JSBind },
    { "NavRouter", JSNavRouter::JSBind },
    { "ColumnSplit", JSColumnSplit::JSBind },
    { "If", JSIfElse::JSBind },
    { "Scroll", JSScroll::JSBind },
    { "ScrollBar", JSScrollBar::JSBind },
    { "GridRow", JSGridRow::JSBind },
    { "GridCol", JSGridCol::JSBind },
    { "Stepper", JSStepper::JSBind },
    { "StepperItem", JSStepperItem::JSBind },
    { "Toggle", JSToggle::JSBind },
    { "Blank", JSBlank::JSBind },
    { "Calendar", JSCalendar::JSBind },
    { "Rect", JSRect::JSBind },
    { "Shape", JSShape::JSBind },
    { "Path", JSPath::JSBind },
    { "Circle", JSCircle::JSBind },
    { "Line", JSLine::JSBind },
    { "Polygon", JSPolygon::JSBind },
    { "Polyline", JSPolyline::JSBind },
    { "Ellipse", JSEllipse::JSBind },
    { "Tabs", JSTabs::JSBind },
    { "TabContent", JSTabContent::JSBind },
    { "TextPicker", JSTextPicker::JSBind },
    { "TimePicker", JSTimePicker::JSBind },
    { "TextPickerDialog", JSTextPickerDialog::JSBind },
    { "TimePickerDialog", JSTimePickerDialog::JSBind },
    { "DatePicker", JSDatePicker::JSBind },
    { "DatePickerDialog", JSDatePickerDialog::JSBind },
    { "PageTransitionEnter", JSPageTransition::JSBind },
    { "PageTransitionExit", JSPageTransition::JSBind },
    { "RowSplit", JSRowSplit::JSBind },
    { "ColumnSplit", JSColumnSplit::JSBind },
    { "AlphabetIndexer", JSIndexer::JSBind },
    { "Hyperlink", JSHyperlink::JSBind },
    { "Radio", JSRadio::JSBind },
    { "ActionSheet", JSActionSheet::JSBind },
    { "AlertDialog", JSAlertDialog::JSBind },
    { "ContextMenu", JSContextMenu::JSBind },
#ifdef ABILITY_COMPONENT_SUPPORTED
    { "AbilityComponent", JSAbilityComponent::JSBind },
#endif
    { "TextArea", JSTextArea::JSBind },
    { "TextInput", JSTextInput::JSBind },
    { "TextClock", JSTextClock::JSBind },
    { "SideBarContainer", JSSideBar::JSBind },
    { "QRCode", JSQRCode::JSBind },
#ifdef FORM_SUPPORTED
    { "FormComponent", JSForm::JSBind },
#endif
#ifdef PLUGIN_COMPONENT_SUPPORTED
    { "PluginComponent", JSPlugin::JSBind },
#endif
#ifdef WEB_SUPPORTED
    { "RichText", JSRichText::JSBind },
    { "Web", JSWeb::JSBind },
    { "WebController", JSWebController::JSBind },
#endif
#ifdef REMOTE_WINDOW_SUPPORTED
    { "RemoteWindow", JSRemoteWindow::JSBind },
#endif
#ifndef WEARABLE_PRODUCT
    { "Camera", JSCamera::JSBind },
    { "Piece", JSPiece::JSBind },
    { "Rating", JSRating::JSBind },
    { "Video", JSVideo::JSBind },
#endif
#if defined(XCOMPONENT_SUPPORTED)
    { "XComponent", JSXComponent::JSBind },
    { "XComponentController", JSXComponentController::JSBind },
#endif
    { "DataPanel", JSDataPanel::JSBind },
    { "Badge", JSBadge::JSBind },
    { "Gauge", JSGauge::JSBind },
    { "Marquee", JSMarquee::JSBind },
    { "Gesture", JSGesture::JSBind },
    { "TapGesture", JSGesture::JSBind },
    { "LongPressGesture", JSGesture::JSBind },
    { "PanGesture", JSGesture::JSBind },
    { "SwipeGesture", JSGesture::JSBind },
    { "PinchGesture", JSGesture::JSBind },
    { "RotationGesture", JSGesture::JSBind },
    { "GestureGroup", JSGesture::JSBind },
    { "PanGestureOption", JSPanGestureOption::JSBind },
    { "PanGestureOptions", JSPanGestureOption::JSBind },
    { "CustomDialogController", JSCustomDialogController::JSBind },
    { "Scroller", JSScroller::JSBind },
    { "SwiperController", JSSwiperController::JSBind },
    { "TabsController", JSTabsController::JSBind },
    { "CalendarController", JSCalendarController::JSBind },
#ifdef ABILITY_COMPONENT_SUPPORTED
    { "AbilityController", JSAbilityComponentController::JSBind },
#endif
    { "CanvasRenderingContext2D", JSRenderingContext::JSBind },
    { "OffscreenCanvasRenderingContext2D", JSOffscreenRenderingContext::JSBind },
    { "CanvasGradient", JSCanvasGradient::JSBind },
    { "ImageBitmap", JSRenderImage::JSBind },
    { "ImageData", JSCanvasImageData::JSBind },
    { "Path2D", JSPath2D::JSBind },
    { "RenderingContextSettings", JSRenderingContextSettings::JSBind },
    { "VideoController", JSVideoController::JSBind },
    { "Search", JSSearch::JSBind },
    { "Select", JSSelect::JSBind },
    { "SearchController", JSSearchController::JSBind },
    { "TextClockController", JSTextClockController::JSBind },
    { "Sheet", JSSheet::JSBind },
    { "JSClipboard", JSClipboard::JSBind },
    { "PatternLock", JSPatternLock::JSBind },
    { "PatternLockController", JSPatternLockController::JSBind },
    { "TextTimer", JSTextTimer::JSBind },
    { "TextAreaController", JSTextAreaController::JSBind },
    { "TextInputController", JSTextInputController::JSBind },
    { "TextTimerController", JSTextTimerController::JSBind },
    { "Checkbox", JSCheckbox::JSBind },
    { "CheckboxGroup", JSCheckboxGroup::JSBind },
    { "Refresh", JSRefresh::JSBind },
    { "WaterFlow", JSWaterFlow::JSBind },
    { "FlowItem", JSWaterFlowItem::JSBind },
    { "RelativeContainer", JSRelativeContainer::JSBind },
    { "__Common__", JSCommonView::JSBind },
#ifdef PREVIEW
    { "FormComponent", JSForm::JSBind },
    { "XComponent", JSXComponent::JSBind },
    { "XComponentController", JSXComponentController::JSBind },
    { "RichText", JSRichText::JSBind },
    { "Web", JSWeb::JSBind },
    { "WebController", JSWebController::JSBind },
#endif
};

void RegisterAllModule(BindingTarget globalObj)
{
    JSColumn::JSBind(globalObj);
    JSCommonView::JSBind(globalObj);
    JSSwiperController::JSBind(globalObj);
    JSTabsController::JSBind(globalObj);
    JSScroller::JSBind(globalObj);
    JSCalendarController::JSBind(globalObj);
    JSRenderingContext::JSBind(globalObj);
    JSOffscreenRenderingContext::JSBind(globalObj);
    JSCanvasGradient::JSBind(globalObj);
    JSRenderImage::JSBind(globalObj);
    JSCanvasImageData::JSBind(globalObj);
    JSPath2D::JSBind(globalObj);
    JSRenderingContextSettings::JSBind(globalObj);
#ifdef ABILITY_COMPONENT_SUPPORTED
    JSAbilityComponentController::JSBind(globalObj);
#endif
    JSVideoController::JSBind(globalObj);
    JSTextInputController::JSBind(globalObj);
    JSTextAreaController::JSBind(globalObj);
    JSSearchController::JSBind(globalObj);
    JSTextClockController::JSBind(globalObj);
    JSTextTimerController::JSBind(globalObj);
#ifdef WEB_SUPPORTED
    JSWebController::JSBind(globalObj);
#endif
    for (auto& iter : bindFuncs) {
        iter.second(globalObj);
    }
}

void RegisterModuleByName(BindingTarget globalObj, std::string moduleName)
{
    auto func = bindFuncs.find(moduleName);
    if (func == bindFuncs.end()) {
        LOGW("Component not exist, name: %{public}s", moduleName.c_str());
        return;
    }
    if ((*func).first == "Swiper") {
        JSSwiperController::JSBind(globalObj);
    } else if ((*func).first == "Tabs") {
        JSTabsController::JSBind(globalObj);
    } else if ((*func).first == "Calendar") {
        JSCalendarController::JSBind(globalObj);
    } else if ((*func).first == "AbilityComponent") {
#ifdef ABILITY_COMPONENT_SUPPORTED
        JSAbilityComponentController::JSBind(globalObj);
#endif
    } else if ((*func).first == "Video") {
        JSVideoController::JSBind(globalObj);
    } else if ((*func).first == "Grid") {
        JSColumn::JSBind(globalObj);
    } else if ((*func).first == "TextTimer") {
        JSTextTimerController::JSBind(globalObj);
    } else if ((*func).first == "TextInput") {
        JSTextInputController::JSBind(globalObj);
    } else if ((*func).first == "TextClock") {
        JSTextClockController::JSBind(globalObj);
    } else if ((*func).first == "TextArea") {
        JSTextAreaController::JSBind(globalObj);
    } else if ((*func).first == "Search") {
        JSSearchController::JSBind(globalObj);
    } else if ((*func).first == "Web") {
#ifdef WEB_SUPPORTED
        JSWebController::JSBind(globalObj);
#endif
    }

    (*func).second(globalObj);
}

void JsRegisterModules(BindingTarget globalObj, std::string modules)
{
    std::stringstream input(modules);
    std::string moduleName;
    while (std::getline(input, moduleName, ',')) {
        RegisterModuleByName(globalObj, moduleName);
    }
    JSRenderingContext::JSBind(globalObj);
    JSOffscreenRenderingContext::JSBind(globalObj);
    JSCanvasGradient::JSBind(globalObj);
    JSRenderImage::JSBind(globalObj);
    JSCanvasImageData::JSBind(globalObj);
    JSPath2D::JSBind(globalObj);
    JSRenderingContextSettings::JSBind(globalObj);
}

void JsBindViews(BindingTarget globalObj)
{
    JSViewAbstract::JSBind();
    JSContainerBase::JSBind();
    JSShapeAbstract::JSBind();
    JSView::JSBind(globalObj);
    JSLocalStorage::JSBind(globalObj);

    JSEnvironment::JSBind(globalObj);
    JSViewContext::JSBind(globalObj);
    JSViewStackProcessor::JSBind(globalObj);
    JSTouchHandler::JSBind(globalObj);
    JSPanHandler::JSBind(globalObj);
    JSGesture::JSBind(globalObj);
    JSPanGestureOption::JSBind(globalObj);
    JsDragFunction::JSBind(globalObj);
    JSCustomDialogController::JSBind(globalObj);
    JSShareData::JSBind(globalObj);
    JSPersistent::JSBind(globalObj);
    JSDistributed::JSBind(globalObj);
    JSScroller::JSBind(globalObj);

    JSProfiler::JSBind(globalObj);

    auto delegate = JsGetFrontendDelegate();
    std::string jsModules;
    if (delegate && delegate->GetAssetContent("component_collection.txt", jsModules)) {
        LOGI("JsRegisterViews register collection modules");
        JsRegisterModules(globalObj, jsModules);
    } else {
        LOGI("JsRegisterViews register all modules");
        RegisterAllModule(globalObj);
    }
}

} // namespace OHOS::Ace::Framework
