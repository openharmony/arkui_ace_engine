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

#include "bridge/card_frontend/card_frontend_declarative.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/functions/js_should_built_in_recognizer_parallel_with_function.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_extra_view_register.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_view_register.h"
#ifdef NG_BUILD
#include "bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#else
#include "bridge/declarative_frontend/frontend_delegate_declarative.h"
#endif
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_with_theme.h"
#include "bridge/declarative_frontend/interfaces/profiler/js_profiler.h"
#include "bridge/declarative_frontend/jsview/action_sheet/js_action_sheet.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_pattern.h"
#include "bridge/declarative_frontend/jsview/canvas/js_offscreen_canvas.h"
#include "bridge/declarative_frontend/jsview/canvas/js_rendering_context.h"
#include "bridge/declarative_frontend/jsview/dialog/js_custom_dialog_controller.h"
#include "bridge/declarative_frontend/jsview/js_animator.h"
#include "bridge/declarative_frontend/jsview/js_badge.h"
#include "bridge/declarative_frontend/jsview/js_base_node.h"
#include "bridge/declarative_frontend/jsview/js_blank.h"
#include "bridge/declarative_frontend/jsview/js_button.h"
#include "bridge/declarative_frontend/jsview/js_calendar.h"
#include "bridge/declarative_frontend/jsview/js_calendar_controller.h"
#include "bridge/declarative_frontend/jsview/js_calendar_picker.h"
#include "bridge/declarative_frontend/jsview/js_checkbox.h"
#include "bridge/declarative_frontend/jsview/js_checkboxgroup.h"
#include "bridge/declarative_frontend/jsview/js_circle.h"
#include "bridge/declarative_frontend/jsview/js_circle_shape.h"
#include "bridge/declarative_frontend/jsview/js_clipboard.h"
#include "bridge/declarative_frontend/jsview/js_column_split.h"
#include "bridge/declarative_frontend/jsview/js_common_view.h"
#include "bridge/declarative_frontend/jsview/js_container_span.h"
#include "bridge/declarative_frontend/jsview/js_content_slot.h"
#include "bridge/declarative_frontend/jsview/js_counter.h"
#include "bridge/declarative_frontend/jsview/js_data_panel.h"
#include "bridge/declarative_frontend/jsview/js_datepicker.h"
#include "bridge/declarative_frontend/jsview/js_divider.h"
#include "bridge/declarative_frontend/jsview/js_dynamic_component.h"
#include "bridge/declarative_frontend/jsview/js_ellipse.h"
#include "bridge/declarative_frontend/jsview/js_ellipse_shape.h"
#include "bridge/declarative_frontend/jsview/js_environment.h"
#include "bridge/declarative_frontend/jsview/js_flex_impl.h"
#include "bridge/declarative_frontend/jsview/js_folder_stack.h"
#include "bridge/declarative_frontend/jsview/js_foreach.h"
#ifdef FORM_BUTTON_COMPONENT_SUPPORT
#include "bridge/declarative_frontend/jsview/js_form_button.h"
#endif
#include "bridge/declarative_frontend/jsview/js_form_link.h"
#include "bridge/declarative_frontend/jsview/js_gauge.h"
#include "bridge/declarative_frontend/jsview/js_grid.h"
#include "bridge/declarative_frontend/jsview/js_grid_col.h"
#include "bridge/declarative_frontend/jsview/js_grid_container.h"
#include "bridge/declarative_frontend/jsview/js_grid_item.h"
#include "bridge/declarative_frontend/jsview/js_grid_row.h"
#include "bridge/declarative_frontend/jsview/js_hyperlink.h"
#include "bridge/declarative_frontend/jsview/js_if_else.h"
#include "bridge/declarative_frontend/jsview/js_image.h"
#include "bridge/declarative_frontend/jsview/js_image_animator.h"
#include "bridge/declarative_frontend/jsview/js_image_span.h"
#include "bridge/declarative_frontend/jsview/js_indexer.h"
#include "bridge/declarative_frontend/jsview/js_indicator.h"
#include "bridge/declarative_frontend/jsview/js_isolated_component.h"
#include "bridge/declarative_frontend/jsview/js_keyboard_avoid.h"
#include "bridge/declarative_frontend/jsview/js_layout_manager.h"
#include "bridge/declarative_frontend/jsview/js_lazy_foreach.h"
#include "bridge/declarative_frontend/jsview/js_lazy_grid.h"
#include "bridge/declarative_frontend/jsview/js_line.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "bridge/declarative_frontend/jsview/js_linear_indicator.h"
#include "bridge/declarative_frontend/jsview/js_linear_indicator_controller.h"
#include "bridge/declarative_frontend/jsview/js_list.h"
#include "bridge/declarative_frontend/jsview/js_list_item.h"
#include "bridge/declarative_frontend/jsview/js_list_item_group.h"
#include "bridge/declarative_frontend/jsview/js_loading_progress.h"
#include "bridge/declarative_frontend/jsview/js_local_storage.h"
#include "bridge/declarative_frontend/jsview/js_location_button.h"
#include "bridge/declarative_frontend/jsview/js_marquee.h"
#include "bridge/declarative_frontend/jsview/js_menu.h"
#include "bridge/declarative_frontend/jsview/js_menu_item.h"
#include "bridge/declarative_frontend/jsview/js_menu_item_group.h"
#include "bridge/declarative_frontend/jsview/js_mock.h"
#include "bridge/declarative_frontend/jsview/js_nav_path_stack.h"
#include "bridge/declarative_frontend/jsview/js_navdestination.h"
#include "bridge/declarative_frontend/jsview/js_navigation.h"
#include "bridge/declarative_frontend/jsview/js_navigator.h"
#include "bridge/declarative_frontend/jsview/js_navrouter.h"
#include "bridge/declarative_frontend/jsview/js_node_container.h"
#include "bridge/declarative_frontend/jsview/js_page_transition.h"
#include "bridge/declarative_frontend/jsview/js_particle.h"
#include "bridge/declarative_frontend/jsview/js_paste_button.h"
#include "bridge/declarative_frontend/jsview/js_path.h"
#include "bridge/declarative_frontend/jsview/js_path_shape.h"
#include "bridge/declarative_frontend/jsview/js_pattern_lock.h"
#include "bridge/declarative_frontend/jsview/js_persistent.h"
#include "bridge/declarative_frontend/jsview/js_polygon.h"
#include "bridge/declarative_frontend/jsview/js_polyline.h"
#include "bridge/declarative_frontend/jsview/js_progress.h"
#ifdef QRCODEGEN_SUPPORT
#include "bridge/declarative_frontend/jsview/js_qrcode.h"
#endif
#include "bridge/declarative_frontend/jsview/js_radio.h"
#include "bridge/declarative_frontend/jsview/js_rect.h"
#include "bridge/declarative_frontend/jsview/js_rect_shape.h"
#include "bridge/declarative_frontend/jsview/js_recycle_view.h"
#include "bridge/declarative_frontend/jsview/js_refresh.h"
#include "bridge/declarative_frontend/jsview/js_relative_container.h"
#include "bridge/declarative_frontend/jsview/js_repeat.h"
#include "bridge/declarative_frontend/jsview/js_repeat_virtual_scroll.h"
#include "bridge/declarative_frontend/jsview/js_repeat_virtual_scroll_2.h"
#include "bridge/declarative_frontend/jsview/js_richeditor.h"
#include "bridge/declarative_frontend/jsview/js_row.h"
#include "bridge/declarative_frontend/jsview/js_row_split.h"
#include "bridge/declarative_frontend/jsview/js_save_button.h"
#include "bridge/declarative_frontend/jsview/js_scope_util.h"
#include "bridge/declarative_frontend/jsview/js_scroll.h"
#include "bridge/declarative_frontend/jsview/js_search.h"
#include "bridge/declarative_frontend/jsview/js_select.h"
#include "bridge/declarative_frontend/jsview/js_shape.h"
#include "bridge/declarative_frontend/jsview/js_sheet.h"
#include "bridge/declarative_frontend/jsview/js_side_bar.h"
#include "bridge/declarative_frontend/jsview/js_slider.h"
#include "bridge/declarative_frontend/jsview/js_sliding_panel.h"
#include "bridge/declarative_frontend/jsview/js_span.h"
#include "bridge/declarative_frontend/jsview/js_state_mgmt_profiler.h"
#include "bridge/declarative_frontend/jsview/js_stepper.h"
#include "bridge/declarative_frontend/jsview/js_stepper_item.h"
#include "bridge/declarative_frontend/jsview/js_swiper.h"
#include "bridge/declarative_frontend/jsview/js_symbol.h"
#include "bridge/declarative_frontend/jsview/js_symbol_span.h"
#include "bridge/declarative_frontend/jsview/js_tab_content.h"
#include "bridge/declarative_frontend/jsview/js_tabs.h"
#include "bridge/declarative_frontend/jsview/js_tabs_controller.h"
#include "bridge/declarative_frontend/jsview/js_text.h"
#include "bridge/declarative_frontend/jsview/js_text_clock.h"
#include "bridge/declarative_frontend/jsview/js_textarea.h"
#include "bridge/declarative_frontend/jsview/js_textinput.h"
#include "bridge/declarative_frontend/jsview/js_textpicker.h"
#include "bridge/declarative_frontend/jsview/js_texttimer.h"
#include "bridge/declarative_frontend/jsview/js_toggle.h"
#include "bridge/declarative_frontend/jsview/js_toolbaritem.h"
#include "bridge/declarative_frontend/jsview/js_view_context.h"
#include "bridge/declarative_frontend/jsview/js_view_stack_processor.h"
#include "bridge/declarative_frontend/jsview/js_water_flow.h"
#include "bridge/declarative_frontend/jsview/js_water_flow_item.h"
#include "bridge/declarative_frontend/jsview/menu/js_context_menu.h"
#include "bridge/declarative_frontend/jsview/scroll_bar/js_scroll_bar.h"
#include "bridge/declarative_frontend/sharedata/js_share_data.h"
#include "bridge/declarative_frontend/style_string/js_span_string.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_object_template.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_app_bar_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_dump_log.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_modal_view.h"
#include "bridge/declarative_frontend/jsview/text_menu/js_text_menu.h"

#ifdef REMOTE_WINDOW_SUPPORTED
#include "bridge/declarative_frontend/jsview/js_remote_window.h"
#endif

#ifdef EFFECT_COMPONENT_SUPPORTED
#include "bridge/declarative_frontend/jsview/js_effect_component.h"
#endif

#ifndef WEARABLE_PRODUCT
#include "bridge/declarative_frontend/jsview/js_piece.h"
#include "bridge/declarative_frontend/jsview/js_rating.h"
#if defined(PLAYER_FRAMEWORK_EXISTS)
#ifdef VIDEO_SUPPORTED
#include "bridge/declarative_frontend/jsview/js_video.h"
#include "bridge/declarative_frontend/jsview/js_video_controller.h"
#endif
#endif
#endif

#if defined(XCOMPONENT_SUPPORTED)
#include "bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#endif

#if defined(PREVIEW)
#include "bridge/declarative_frontend/jsview/js_previewer_mock.h"
#endif

#ifdef ABILITY_COMPONENT_SUPPORTED
#include "bridge/declarative_frontend/jsview/js_ability_component.h"
#include "bridge/declarative_frontend/jsview/js_ability_component_controller.h"
#endif

#if defined(MODEL_COMPONENT_SUPPORTED)
#include "bridge/declarative_frontend/jsview/js_sceneview.h"
#endif

#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "bridge/declarative_frontend/jsview/js_plugin.h"
#include "core/common/plugin_manager.h"
#endif

#ifdef FORM_SUPPORTED
#include "bridge/declarative_frontend/jsview/js_form.h"
#include "bridge/declarative_frontend/jsview/js_form_menu_item.h"
#endif

#ifdef WEB_SUPPORTED
#include "bridge/declarative_frontend/jsview/js_richtext.h"
#include "bridge/declarative_frontend/jsview/js_web.h"
#include "bridge/declarative_frontend/jsview/js_web_controller.h"
#endif

#ifndef WEARABLE_PRODUCT
#if defined(CAMERA_FRAMEWORK_EXISTS) && defined(PLAYER_FRAMEWORK_EXISTS)
#include "bridge/declarative_frontend/jsview/js_camera.h"
#endif
#endif

#if defined(WINDOW_SCENE_SUPPORTED)
#include "bridge/declarative_frontend/jsview/js_embedded_component.h"
#include "bridge/declarative_frontend/jsview/js_security_ui_extension.h"
#include "bridge/declarative_frontend/jsview/js_ui_extension.h"
#include "bridge/declarative_frontend/jsview/window_scene/js_root_scene.h"
#include "bridge/declarative_frontend/jsview/window_scene/js_screen.h"
#include "bridge/declarative_frontend/jsview/window_scene/js_window_scene.h"
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
    if (container->IsUseNewPipeline()) {
        RefPtr<NG::FrameNode> pageNode;
#ifdef PLUGIN_COMPONENT_SUPPORTED
        std::function<void(const std::string&)> callback = [weak = Referenced::WeakClaim(view)](
                                                               const std::string& params) {
            auto view = weak.Upgrade();
            if (view && !params.empty()) {
                view->ExecuteInitiallyProvidedValue(params);
            }
        };
        if (view->isFullUpdate()) {
            callback = [weak = Referenced::WeakClaim(view)](const std::string& params) {
                auto view = weak.Upgrade();
                if (view && !params.empty()) {
                    view->ExecuteUpdateWithValueParams(params);
                }
            };
        }
        if (Container::CurrentId() >= MIN_PLUGIN_SUBCONTAINER_ID) {
            auto pluginContainer = PluginManager::GetInstance().GetPluginSubContainer(Container::CurrentId());
            CHECK_NULL_VOID(pluginContainer);
            pageNode = pluginContainer->GetPluginNode().Upgrade();
            CHECK_NULL_VOID(pageNode);
            pluginContainer->SetDeclarativeOnUpdateWithValueParamsCallback(std::move(callback));
        } else
#endif
        {
#ifdef NG_BUILD
            auto frontEnd = AceType::DynamicCast<DeclarativeFrontendNG>(container->GetFrontend());
#else
            auto frontEnd = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
#endif
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
        // root custom component
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
        pagePattern->SetOnNewParam([weak = Referenced::WeakClaim(view)](const std::string& newParam) {
            auto view = weak.Upgrade();
            if (view) {
                view->FireOnNewParam(newParam);
            }
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
        pagePattern->RegisterDumpInfoListener(
            [weakView = Referenced::WeakClaim(view)](const std::vector<std::string>& params) {
                auto view = weakView.Upgrade();
                if (view) {
                    view->OnDumpInfo(params);
                }
            });
        return;
    }

    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    auto page = JsiDeclarativeEngineInstance::GetStagingPage(Container::CurrentId());
    JsiDeclarativeEngineInstance::RootViewHandle(obj);

    Container::SetCurrentUsePartialUpdate(!view->isFullUpdate());
    LOGI("Loading page[%{public}d] root component: Setting pipeline to use %{public}s.", page->GetPageId(),
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

static const std::unordered_map<std::string, std::function<void(BindingTarget)>> formBindFuncs = {
    { "Flex", JSFlexImpl::JSBind },
    { "Text", JSText::JSBind },
    { "TextClock", JSTextClock::JSBind },
    { "TextClockController", JSTextClockController::JSBind },
    { "Animator", JSAnimator::JSBind },
    { "SpringProp", JSAnimator::JSBind },
    { "SpringMotion", JSAnimator::JSBind },
    { "ScrollMotion", JSAnimator::JSBind },
    { "Animator", JSAnimator::JSBind },
    { "Span", JSSpan::JSBind },
    { "NativeCustomSpan", JSNativeCustomSpan::JSBind },
    { "SpanString", JSSpanString::JSBind },
    { "MutableSpanString", JSMutableSpanString::JSBind },
    { "TextStyle", JSFontSpan::JSBind },
    { "DecorationStyle", JSDecorationSpan::JSBind },
    { "BaselineOffsetStyle", JSBaselineOffsetSpan::JSBind },
    { "LetterSpacingStyle", JSLetterSpacingSpan::JSBind },
    { "UrlStyle", JSUrlSpan::JSBind },
    { "NativeGestureStyle", JSGestureSpan::JSBind },
    { "TextShadowSpan", JSTextShadowSpan::JSBind },
    { "BackgroundColorStyle", JSBackgroundColorSpan::JSBind },
    { "ImageAttachment", JSImageAttachment::JSBind },
    { "ParagraphStyleSpan", JSParagraphStyleSpan::JSBind},
    { "LineHeightSpan", JSLineHeightSpan::JSBind},
    { "Button", JSButton::JSBind },
    { "Canvas", JSCanvas::JSBind },
    { "Matrix2D", JSMatrix2d::JSBind },
    { "CanvasPattern", JSCanvasPattern::JSBind },
    { "List", JSList::JSBind },
    { "ListItem", JSListItem::JSBind },
    { "LoadingProgress", JSLoadingProgress::JSBind },
    { "Image", JSImage::JSBind },
    { "Counter", JSCounter::JSBind },
    { "CalendarPicker", JSCalendarPicker::JSBind },
    { "Progress", JSProgress::JSBind },
    { "Column", JSColumn::JSBind },
    { "Row", JSRow::JSBind },
    { "Slider", JSSlider::JSBind },
    { "Stack", JSStack::JSBind },
#ifndef ARKUI_WEARABLE
    { "FolderStack", JSFolderStack::JSBind},
#endif
    { "ForEach", JSForEach::JSBind },
    { "Divider", JSDivider::JSBind },
    { "If", JSIfElse::JSBind },
    { "Scroll", JSScroll::JSBind },
    { "GridRow", JSGridRow::JSBind },
    { "GridCol", JSGridCol::JSBind },
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
    { "Radio", JSRadio::JSBind },
#ifdef QRCODEGEN_SUPPORT
    { "QRCode", JSQRCode::JSBind },
#endif
    { "Piece", JSPiece::JSBind },
    { "Rating", JSRating::JSBind },
    { "DataPanel", JSDataPanel::JSBind },
    { "Badge", JSBadge::JSBind },
    { "Gauge", JSGauge::JSBind },
    { "Marquee", JSMarquee::JSBind },
    { "Swiper", JSSwiper::JSBind },
    { "Indicator", JSIndicator::JSBind },
    { "SwiperController", JSSwiperController::JSBind },
    { "CalendarController", JSCalendarController::JSBind },
    { "CanvasRenderingContext2D", JSRenderingContext::JSBind },
    { "OffscreenCanvasRenderingContext2D", JSOffscreenRenderingContext::JSBind },
    { "CanvasGradient", JSCanvasGradient::JSBind },
    { "ImageData", JSCanvasImageData::JSBind },
    { "ImageAnimator", JSImageAnimator::JSBind },
    { "Path2D", JSPath2D::JSBind },
    { "RenderingContextSettings", JSRenderingContextSettings::JSBind },
    { "Sheet", JSSheet::JSBind },
    { "TextTimer", JSTextTimer::JSBind },
    { "TextTimerController", JSTextTimerController::JSBind },
    { "Checkbox", JSCheckbox::JSBind },
    { "CheckboxGroup", JSCheckboxGroup::JSBind },
    { "RelativeContainer", JSRelativeContainer::JSBind },
    { "__Common__", JSCommonView::JSBind },
    { "LinearGradient", JSLinearGradient::JSBind },
    { "FormLink", JSFormLink::JSBind },
#ifdef FORM_BUTTON_COMPONENT_SUPPORT
    { "FormButton", JSFormButton::JSBind },
#endif
    { "SymbolSpan", JSSymbolSpan::JSBind },
    { "DrawingRenderingContext", JSDrawingRenderingContext::JSBind },
};

static const std::unordered_map<std::string, std::function<void(BindingTarget)>> bindFuncs = {
    { "Flex", JSFlexImpl::JSBind },
    { "TextController", JSTextController::JSBind },
    { "Text", JSText::JSBind },
    { "Animator", JSAnimator::JSBind },
    { "SpringProp", JSAnimator::JSBind },
    { "SpringMotion", JSAnimator::JSBind },
    { "ScrollMotion", JSAnimator::JSBind },
    { "Animator", JSAnimator::JSBind },
    { "Span", JSSpan::JSBind },
    { "NativeCustomSpan", JSNativeCustomSpan::JSBind },
    { "SpanString", JSSpanString::JSBind },
    { "MutableSpanString", JSMutableSpanString::JSBind },
    { "TextStyle", JSFontSpan::JSBind },
    { "DecorationStyle", JSDecorationSpan::JSBind },
    { "BaselineOffsetStyle", JSBaselineOffsetSpan::JSBind },
    { "LetterSpacingStyle", JSLetterSpacingSpan::JSBind },
    { "UrlStyle", JSUrlSpan::JSBind },
    { "NativeGestureStyle", JSGestureSpan::JSBind },
    { "TextShadowSpan", JSTextShadowSpan::JSBind },
    { "BackgroundColorStyle", JSBackgroundColorSpan::JSBind },
    { "ImageAttachment", JSImageAttachment::JSBind },
    { "ParagraphStyleSpan", JSParagraphStyleSpan::JSBind},
    { "LineHeightSpan", JSLineHeightSpan::JSBind},
    { "Button", JSButton::JSBind },
    { "Canvas", JSCanvas::JSBind },
    { "LazyForEach", JSLazyForEach::JSBind },
    { "LazyVGridLayout", JSLazyVGridLayout::JSBind },
    { "List", JSList::JSBind },
    { "ListItem", JSListItem::JSBind },
    { "ListItemGroup", JSListItemGroup::JSBind },
    { "LoadingProgress", JSLoadingProgress::JSBind },
    { "Image", JSImage::JSBind },
    { "ImageAnimator", JSImageAnimator::JSBind },
    { "Counter", JSCounter::JSBind },
    { "CalendarPicker", JSCalendarPicker::JSBind },
    { "Progress", JSProgress::JSBind },
    { "Column", JSColumn::JSBind },
    { "Row", JSRow::JSBind },
    { "Grid", JSGrid::JSBind },
    { "GridItem", JSGridItem::JSBind },
    { "GridContainer", JSGridContainer::JSBind },
    { "Slider", JSSlider::JSBind },
    { "Stack", JSStack::JSBind },
#ifndef ARKUI_WEARABLE
    { "FolderStack", JSFolderStack::JSBind},
#endif
    { "ForEach", JSForEach::JSBind },
    { "Divider", JSDivider::JSBind },
    { "Swiper", JSSwiper::JSBind },
    { "Indicator", JSIndicator::JSBind },
    { "Panel", JSSlidingPanel::JSBind },
    { "RepeatNative", JSRepeat::JSBind },
    { "RepeatVirtualScrollNative", JSRepeatVirtualScroll::JSBind },
    { "RepeatVirtualScroll2Native", JSRepeatVirtualScroll2::JSBind },
    { "NavDestination", JSNavDestination::JSBind },
    { "Navigation", JSNavigation::JSBind },
    { "NativeNavPathStack", JSNavPathStack::JSBind },
    { "Navigator", JSNavigator::JSBind },
    { "NavRouter", JSNavRouter::JSBind },
    { "If", JSIfElse::JSBind },
    { "Scroll", JSScroll::JSBind },
    { "ScrollBar", JSScrollBar::JSBind },
    { "GridRow", JSGridRow::JSBind },
    { "GridCol", JSGridCol::JSBind },
#ifndef ARKUI_WEARABLE
    { "Stepper", JSStepper::JSBind },
    { "StepperItem", JSStepperItem::JSBind },
#endif
    { "Toggle", JSToggle::JSBind },
    { "ToolBarItem", JSToolBarItem::JSBind },
    { "Blank", JSBlank::JSBind },
    { "Calendar", JSCalendar::JSBind },
    { "CalendarPickerDialog", JSCalendarPickerDialog::JSBind },
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
#ifndef ARKUI_WEARABLE
    { "RowSplit", JSRowSplit::JSBind },
    { "ColumnSplit", JSColumnSplit::JSBind },
#endif
    { "AlphabetIndexer", JSIndexer::JSBind },
    { "Hyperlink", JSHyperlink::JSBind },
    { "Radio", JSRadio::JSBind },
    { "ActionSheet", JSActionSheet::JSBind },
    { "AlertDialog", JSAlertDialog::JSBind },
    { "ContextMenu", JSContextMenu::JSBind },
    { "FormLink", JSFormLink::JSBind },
#ifdef FORM_BUTTON_COMPONENT_SUPPORT
    { "FormButton", JSFormButton::JSBind },
#endif
    { "LocationButton", JSLocationButton::JSBind },
    { "PasteButton", JSPasteButton::JSBind },
    { "Particle", JSParticle::JSBind },
    { "SaveButton", JSSaveButton::JSBind },
    { "WithTheme", JSWithTheme::JSBind },
    { "__KeyboardAvoid__", JSKeyboardAvoid::JSBind },
    { "TextMenu", JSTextMenu::JSBind },
#ifdef ABILITY_COMPONENT_SUPPORTED
    { "AbilityComponent", JSAbilityComponent::JSBind },
#endif
    { "TextArea", JSTextArea::JSBind },
    { "TextInput", JSTextInput::JSBind },
    { "TextClock", JSTextClock::JSBind },
    { "SideBarContainer", JSSideBar::JSBind },
#ifdef QRCODEGEN_SUPPORT
    { "QRCode", JSQRCode::JSBind },
#endif
#ifdef FORM_SUPPORTED
    { "FormComponent", JSForm::JSBind },
    { "FormMenuItem", JSFormMenuItem::JSBind },
#endif
#ifdef PLUGIN_COMPONENT_SUPPORTED
    { "PluginComponent", JSPlugin::JSBind },
#endif
#ifdef WEB_SUPPORTED
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
    { "RichText", JSRichText::JSBind },
    { "WebController", JSWebController::JSBind },
#endif
    { "Web", JSWeb::JSBind },
#endif
#ifdef REMOTE_WINDOW_SUPPORTED
    { "RemoteWindow", JSRemoteWindow::JSBind },
#endif
#ifdef EFFECT_COMPONENT_SUPPORTED
    { "EffectComponent", JSEffectComponent::JSBind },
#endif
#ifndef WEARABLE_PRODUCT
#if defined(CAMERA_FRAMEWORK_EXISTS) && defined(PLAYER_FRAMEWORK_EXISTS)
    { "Camera", JSCamera::JSBind },
#endif
    { "Piece", JSPiece::JSBind },
    { "Rating", JSRating::JSBind },
#if defined(PLAYER_FRAMEWORK_EXISTS)
#ifdef VIDEO_SUPPORTED
    { "Video", JSVideo::JSBind },
#endif
#endif
#endif
#if defined(XCOMPONENT_SUPPORTED)
    { "XComponent", JSXComponent::JSBind },
    { "XComponentController", JSXComponentController::JSBind },
#endif
    { "DataPanel", JSDataPanel::JSBind },
    { "Badge", JSBadge::JSBind },
    { "Gauge", JSGauge::JSBind },
    { "Marquee", JSMarquee::JSBind },
    { "Menu", JSMenu::JSBind },
    { "MenuItem", JSMenuItem::JSBind },
    { "MenuItemGroup", JSMenuItemGroup::JSBind },
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
    { "NativeCustomDialogController", JSCustomDialogController::JSBind },
    { "Scroller", JSScroller::JSBind },
    { "ListScroller", JSListScroller::JSBind },
    { "SwiperController", JSSwiperController::JSBind },
    { "IndicatorController", JSIndicatorController::JSBind },
    { "TabsController", JSTabsController::JSBind },
    { "CalendarController", JSCalendarController::JSBind },
#ifdef ABILITY_COMPONENT_SUPPORTED
    { "AbilityController", JSAbilityComponentController::JSBind },
#endif
    { "CanvasRenderingContext2D", JSRenderingContext::JSBind },
    { "OffscreenCanvasRenderingContext2D", JSOffscreenRenderingContext::JSBind },
    { "CanvasGradient", JSCanvasGradient::JSBind },
    { "ImageData", JSCanvasImageData::JSBind },
    { "Path2D", JSPath2D::JSBind },
    { "RenderingContextSettings", JSRenderingContextSettings::JSBind },
    { "Matrix2D", JSMatrix2d::JSBind },
    { "CanvasPattern", JSCanvasPattern::JSBind },
    { "DrawingRenderingContext", JSDrawingRenderingContext::JSBind },
#if defined(PLAYER_FRAMEWORK_EXISTS)
#ifdef VIDEO_SUPPORTED
    { "VideoController", JSVideoController::JSBind },
#endif
#endif
    { "Search", JSSearch::JSBind },
#ifndef ARKUI_WEARABLE
    { "Select", JSSelect::JSBind },
#endif
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
    { "__Recycle__", JSRecycleView::JSBind },
    { "LinearGradient", JSLinearGradient::JSBind },
    { "ImageSpan", JSImageSpan::JSBind },
#ifdef PREVIEW
    { "FormComponent", JSForm::JSBind },
    { "XComponent", JSXComponent::JSBind },
    { "XComponentController", JSXComponentController::JSBind },
    { "RichText", JSRichText::JSBind },
    { "Web", JSWeb::JSBind },
    { "WebController", JSWebController::JSBind },
#if defined(PLAYER_FRAMEWORK_EXISTS)
    { "Video", JSVideo::JSBind },
    { "VideoController", JSVideoController::JSBind },
#endif
    { "PluginComponent", JSPlugin::JSBind },
    { "SecurityUIExtensionComponent", JSSecurityUIExtension::JSBind },
    { "UIExtensionComponent", JSUIExtension::JSBind },
#endif
#if defined(MODEL_COMPONENT_SUPPORTED)
    { "Component3D", JSSceneView::JSBind },
#endif
#if defined(WINDOW_SCENE_SUPPORTED)
    { "EmbeddedComponent", JSEmbeddedComponent::JSBind },
    { "RootScene", JSRootScene::JSBind },
    { "Screen", JSScreen::JSBind },
    { "SecurityUIExtensionComponent", JSSecurityUIExtension::JSBind },
    { "SecurityUIExtensionProxy", JSSecurityUIExtensionProxy::JSBind },
    { "UIExtensionComponent", JSUIExtension::JSBind },
    { "UIExtensionProxy", JSUIExtensionProxy::JSBind },
    { "WindowScene", JSWindowScene::JSBind },
#if defined(DYNAMIC_COMPONENT_SUPPORT)
    { "DynamicComponent", JSDynamicComponent::JSBind },
    { "IsolatedComponent", JSIsolatedComponent::JSBind },
#endif
#endif
    { "RichEditor", JSRichEditor::JSBind },
    { "RichEditorController", JSRichEditorController::JSBind },
    { "RichEditorStyledStringController", JSRichEditorStyledStringController::JSBind },
    { "LayoutManager", JSLayoutManager::JSBind },
    { "NodeContainer", JSNodeContainer::JSBind },
    { "__JSBaseNode__", JSBaseNode::JSBind },
    { "SymbolGlyph", JSSymbol::JSBind },
    { "SymbolSpan", JSSymbolSpan::JSBind },
    { "ContainerSpan",  JSContainerSpan::JSBind},
    { "__RectShape__", JSRectShape::JSBind },
    { "__CircleShape__", JSCircleShape::JSBind },
    { "__EllipseShape__", JSEllipseShape::JSBind },
    { "__PathShape__", JSPathShape::JSBind },
    { "ContentSlot", JSContentSlot::JSBind },
    { "ArkUINativeNodeContent", JSNodeContent::JSBind },
    { "GestureRecognizer", JSGestureRecognizer::JSBind },
    { "EventTargetInfo", JSEventTargetInfo::JSBind },
    { "ScrollableTargetInfo", JSScrollableTargetInfo::JSBind },
    { "PanRecognizer", JSPanRecognizer::JSBind },
    { "LinearIndicator", JSLinearIndicator::JSBind },
    { "LinearIndicatorController", JSLinearIndicatorController::JSBind },
    { "TapRecognizer", JSTapRecognizer::JSBind },
    { "LongPressRecognizer", JSLongPressRecognizer::JSBind },
    { "SwipeRecognizer", JSSwipeRecognizer::JSBind },
    { "PinchRecognizer", JSPinchRecognizer::JSBind },
    { "RotationRecognizer", JSRotationRecognizer::JSBind }
};

void RegisterBindFuncs(BindingTarget globalObj)
{
    auto container = Container::Current();
    if (container && container->IsDynamicRender() && !container->GetRegisterComponents().empty()) {
        for (auto& moudle : container->GetRegisterComponents()) {
            auto bindFunc = bindFuncs.find(moudle);
            if (bindFunc != bindFuncs.end()) {
                bindFunc->second(globalObj);
                continue;
            }
            if (!RegisterExtraViewByName(globalObj, moudle)) {
                LOGW("module not exist, name: %{public}s", moudle.c_str());
            }
        }
        return;
    }

    for (auto& iter : bindFuncs) {
        iter.second(globalObj);
    }
}

void RegisterAllModule(BindingTarget globalObj, void* nativeEngine)
{
    JSColumn::JSBind(globalObj);
    JSCommonView::JSBind(globalObj);
    JSSwiperController::JSBind(globalObj);
    JSIndicatorController::JSBind(globalObj);
    JSTabsController::JSBind(globalObj);
    JSScroller::JSBind(globalObj);
    JSListScroller::JSBind(globalObj);
    JSCalendarController::JSBind(globalObj);
    JSRenderingContext::JSBind(globalObj);
    JSOffscreenRenderingContext::JSBind(globalObj);
    JSCanvasGradient::JSBind(globalObj);
    JSRenderImage::JSBind(globalObj, nativeEngine);
    JSCanvasImageData::JSBind(globalObj);
    JSPath2D::JSBind(globalObj);
    JSRenderingContextSettings::JSBind(globalObj);
    JSOffscreenCanvas::JSBind(globalObj, nativeEngine);
#ifdef ABILITY_COMPONENT_SUPPORTED
    JSAbilityComponentController::JSBind(globalObj);
#endif
#if defined(PLAYER_FRAMEWORK_EXISTS)
#ifdef VIDEO_SUPPORTED
    JSVideoController::JSBind(globalObj);
#endif
#endif
    JSTextInputController::JSBind(globalObj);
    JSTextAreaController::JSBind(globalObj);
    JSSearchController::JSBind(globalObj);
    JSTextClockController::JSBind(globalObj);
    JSTextTimerController::JSBind(globalObj);
    JSLinearGradient::JSBind(globalObj);
#ifdef WEB_SUPPORTED
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
    JSWebController::JSBind(globalObj);
#endif
#endif
    JSRichEditorController::JSBind(globalObj);
    JSRichEditorStyledStringController::JSBind(globalObj);
    JSLayoutManager::JSBind(globalObj);
    JSTextController::JSBind(globalObj);
    JSNodeContainer::JSBind(globalObj);
    JSBaseNode::JSBind(globalObj);
    JSRectShape::JSBind(globalObj);
    JSCircleShape::JSBind(globalObj);
    JSEllipseShape::JSBind(globalObj);
    JSPathShape::JSBind(globalObj);

    RegisterBindFuncs(globalObj);
    RegisterExtraViews(globalObj);
}

void RegisterAllFormModule(BindingTarget globalObj, void* nativeEngine)
{
    JSColumn::JSBind(globalObj);
    JSCommonView::JSBind(globalObj);
    JSSwiperController::JSBind(globalObj);
    JSIndicatorController::JSBind(globalObj);
    JSScroller::JSBind(globalObj);
    JSListScroller::JSBind(globalObj);
    JSCalendarController::JSBind(globalObj);
    JSRenderingContext::JSBind(globalObj);
    JSOffscreenRenderingContext::JSBind(globalObj);
    JSCanvasGradient::JSBind(globalObj);
    JSRenderImage::JSBind(globalObj, nativeEngine);
    JSOffscreenCanvas::JSBind(globalObj, nativeEngine);
    JSCanvasImageData::JSBind(globalObj);
    JSPath2D::JSBind(globalObj);
    JSRenderingContextSettings::JSBind(globalObj);
    JSTextTimerController::JSBind(globalObj);
    JSLinearGradient::JSBind(globalObj);
    for (auto& iter : formBindFuncs) {
        iter.second(globalObj);
    }
    RegisterExtraViews(globalObj);
}

void RegisterFormModuleByName(BindingTarget globalObj, const std::string& module, void* nativeEngine)
{
    if (module == "ImageBitmap") {
        JSRenderImage::JSBind(globalObj, nativeEngine);
        return;
    }
    if (module == "OffscreenCanvas") {
        JSOffscreenCanvas::JSBind(globalObj, nativeEngine);
        return;
    }
    if (module == "Repeat") {
        JSRepeat::JSBind(globalObj);
        return;
    }
    auto func = bindFuncs.find(module);
    if (func == bindFuncs.end()) {
        RegisterExtraViewByName(globalObj, module);
        return;
    }
    if ((*func).first == "Swiper") {
        JSSwiperController::JSBind(globalObj);
    } else if ((*func).first == "Calendar") {
        JSCalendarController::JSBind(globalObj);
    } else if ((*func).first == "TextTimer") {
        JSTextTimerController::JSBind(globalObj);
    } else if ((*func).first == "TextClock") {
        JSTextClockController::JSBind(globalObj);
    } else if ((*func).first == "Canvas") {
        JSCanvasPattern::JSBind(globalObj);
        JSCanvasGradient::JSBind(globalObj);
        JSCanvasImageData::JSBind(globalObj);
        JSMatrix2d::JSBind(globalObj);
        JSRenderImage::JSBind(globalObj, nativeEngine);
    }

    (*func).second(globalObj);
}

void RegisterModuleByName(BindingTarget globalObj, std::string moduleName)
{
    auto func = bindFuncs.find(moduleName);
    if (func == bindFuncs.end()) {
        RegisterExtraViewByName(globalObj, moduleName);
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
#if defined(PLAYER_FRAMEWORK_EXISTS)
#ifdef VIDEO_SUPPORTED
        JSVideoController::JSBind(globalObj);
#endif
#endif
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
    } else if ((*func).first == V2::RICH_EDITOR_ETS_TAG) {
        JSRichEditorController::JSBind(globalObj);
        JSRichEditorStyledStringController::JSBind(globalObj);
        JSLayoutManager::JSBind(globalObj);
    } else if ((*func).first == V2::TEXT_ETS_TAG) {
        JSTextController::JSBind(globalObj);
    }

    (*func).second(globalObj);
}

void JsUINodeRegisterCleanUp(BindingTarget globalObj)
{
    // globalObj is panda::Local<panda::ObjectRef>
    const auto globalObject = JSRef<JSObject>::Make(globalObj);

    const JSRef<JSVal> cleanUpIdleTask = globalObject->GetProperty("uiNodeCleanUpIdleTask");
    if (cleanUpIdleTask->IsFunction()) {
        LOGI("CleanUpIdleTask is a valid function");
        const auto globalFunc = JSRef<JSFunc>::Cast(cleanUpIdleTask);
        const auto callback = [jsFunc = globalFunc, globalObject = globalObject](int64_t maxTimeInNs) {
            auto params = ConvertToJSValues(maxTimeInNs / 1e6);
            jsFunc->Call(globalObject, params.size(), params.data());
        };
        ElementRegister::GetInstance()->RegisterJSCleanUpIdleTaskFunc(callback);
    }
}

void JsRegisterModules(BindingTarget globalObj, std::string modules, void* nativeEngine)
{
    std::stringstream input(modules);
    std::string moduleName;
    while (std::getline(input, moduleName, ',')) {
        RegisterModuleByName(globalObj, moduleName);
    }
    JsUINodeRegisterCleanUp(globalObj);

    JSRenderingContext::JSBind(globalObj);
    JSOffscreenRenderingContext::JSBind(globalObj);
    JSCanvasGradient::JSBind(globalObj);
    JSRenderImage::JSBind(globalObj, nativeEngine);
    JSOffscreenCanvas::JSBind(globalObj, nativeEngine);
    JSCanvasImageData::JSBind(globalObj);
    JSPath2D::JSBind(globalObj);
    JSRenderingContextSettings::JSBind(globalObj);
}

void JsBindFormViews(
    BindingTarget globalObj, const std::unordered_set<std::string>& formModuleList, void* nativeEngine, bool isReload)
{
    if (!isReload) {
        JSViewAbstract::JSBind(globalObj);
        JSContainerBase::JSBind(globalObj);
        JSScrollableBase::JSBind(globalObj);
        JSShapeAbstract::JSBind(globalObj);
        JSView::JSBind(globalObj);
        JSDumpLog::JSBind(globalObj);
        JSDumpRegister::JSBind(globalObj);
        JSLocalStorage::JSBind(globalObj);
        JSStateMgmtProfiler::JSBind(globalObj);
        JSCustomDialogController::JSBind(globalObj);

        JSEnvironment::JSBind(globalObj);
        JSViewContext::JSBind(globalObj);
        JSViewStackProcessor::JSBind(globalObj);
        JSTouchHandler::JSBind(globalObj);
        JSPersistent::JSBind(globalObj);
        JSScroller::JSBind(globalObj);
        JSListScroller::JSBind(globalObj);

        JSProfiler::JSBind(globalObj);
        JSCommonView::JSBind(globalObj);
        JSLinearGradient::JSBind(globalObj);
        JSPath2D::JSBind(globalObj);
        JSOffscreenRenderingContext::JSBind(globalObj);
        JSRenderingContextSettings::JSBind(globalObj);
        JSRenderingContext::JSBind(globalObj);

        JSRectShape::JSBind(globalObj);
        JSCircleShape::JSBind(globalObj);
        JSEllipseShape::JSBind(globalObj);
        JSPathShape::JSBind(globalObj);
    }

    if (!formModuleList.empty()) {
        for (const std::string& module : formModuleList) {
            RegisterFormModuleByName(globalObj, module, nativeEngine);
        }
    } else {
        TAG_LOGI(AceLogTag::ACE_FORM, "register all form components, isReload:%{public}d", isReload);
        RegisterAllFormModule(globalObj, nativeEngine);
    }
}

void JsBindViews(BindingTarget globalObj, void* nativeEngine)
{
    JSViewAbstract::JSBind(globalObj);
    JSContainerBase::JSBind(globalObj);
    JSScrollableBase::JSBind(globalObj);
    JSShapeAbstract::JSBind(globalObj);
    JSView::JSBind(globalObj);
    JSDumpLog::JSBind(globalObj);
    JSDumpRegister::JSBind(globalObj);
    JSLocalStorage::JSBind(globalObj);
    JSStateMgmtProfiler::JSBind(globalObj);

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
    JSScroller::JSBind(globalObj);
    JSListScroller::JSBind(globalObj);

    JSProfiler::JSBind(globalObj);
    JSScopeUtil::JSBind(globalObj);
    JSContainerModal::JSBind(globalObj);
    JSAppBar::JSBind(globalObj);
    auto delegate = JsGetFrontendDelegate();
    std::string jsModules;
    if (delegate && delegate->GetAssetContent("component_collection.txt", jsModules)) {
        JsRegisterModules(globalObj, jsModules, nativeEngine);
    } else {
        RegisterAllModule(globalObj, nativeEngine);
    }
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
