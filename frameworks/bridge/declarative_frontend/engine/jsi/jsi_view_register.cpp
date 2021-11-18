/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "base/i18n/localization.h"
#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_object_template.h"
#include "frameworks/bridge/declarative_frontend/frontend_delegate_declarative.h"
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
#include "frameworks/bridge/declarative_frontend/jsview/js_clipboard.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_hyperlink.h"
#ifndef WEARABLE_PRODUCT
#include "frameworks/bridge/declarative_frontend/jsview/js_camera.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_circle.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_column.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_column_split.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_counter.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_data_panel.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_datepicker.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_divider.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_ellipse.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_environment.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_flex_impl.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_foreach.h"
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
#include "frameworks/bridge/declarative_frontend/jsview/js_loading_progress.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_marquee.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigation_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_pan_handler.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_path.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_persistent.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_polygon.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_polyline.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_progress.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_slider.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textpicker.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_toggle.h"
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
#include "frameworks/bridge/declarative_frontend/jsview/js_qrcode.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_page_transition.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_radio.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rect.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_refresh.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_row.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_row_split.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_scroll.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_scroller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_search.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_sheet.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"
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
#include "frameworks/bridge/declarative_frontend/jsview/js_textarea.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_textinput.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_touch_handler.h"
#ifndef WEARABLE_PRODUCT
#include "frameworks/bridge/declarative_frontend/jsview/js_piece.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rating.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_video.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_video_controller.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/scroll_bar/js_scroll_bar.h"
#include "frameworks/bridge/declarative_frontend/sharedata/js_share_data.h"

namespace OHOS::Ace::Framework {

panda::Local<panda::JSValueRef> JsLoadDocument(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    LOGD("Load Document");
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    if (!args[0]->IsObject()) {
        LOGE("The arg is wrong, value must be object");
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::ObjectRef> obj = args[0]->ToObject(vm);
    JSView* view = static_cast<JSView*>(obj->GetNativePointerField(0));

    auto runtime = JsiDeclarativeEngineInstance::GetJsRuntime();
    auto page = JsiDeclarativeEngineInstance::GetStagingPage(runtime);
    JsiDeclarativeEngineInstance::RootViewHandle(runtime, obj);

    LOGD("Load Document setting root view");
    auto rootComponent = view->CreateComponent();
    rootComponent->SetInspectorId("-1");
    std::list<RefPtr<Component>> stackChildren;
    stackChildren.emplace_back(rootComponent);
    auto rootStackComponent = AceType::MakeRefPtr<StackComponent>(
        Alignment::TOP_LEFT, StackFit::INHERIT, Overflow::OBSERVABLE, stackChildren);
    rootStackComponent->SetMainStackSize(MainStackSize::MAX);
    auto rootComposed = AceType::MakeRefPtr<ComposedComponent>("0", "root");
    rootComposed->SetChild(rootStackComponent);
    page->SetRootComponent(rootComposed);

    page->SetPageTransition(view->BuildPageTransitionComponent());
    // We are done, tell to the JSAgePage
    page->SetPageCreated();
    page->SetDeclarativeOnPageAppearCallback([view]() { view->FireOnShow(); });
    page->SetDeclarativeOnPageDisAppearCallback([view]() { view->FireOnHide(); });
    page->SetDeclarativeOnBackPressCallback([view]() { return view->FireOnBackPress(); });
    page->SetDeclarativeOnPageRefreshCallback([view]() { view->MarkNeedUpdate(); });

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsDumpMemoryStats(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    LOGD("dumpMemoryStats: Not Implemented for ARK. UnSupported");
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsGetI18nResource(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    LOGD("JsGetI18nResource");
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    if (argc != 2 && argc != 1) {
        LOGE("The arg is wrong, it is supposed to have one or two arguments");
        return panda::JSValueRef::Undefined(vm);
    }
    if (!args[0]->IsString()) {
        LOGE("The arg is wrong, value must be string");
        return panda::JSValueRef::Undefined(vm);
    }

    std::vector<std::string> splitStr;
    std::string str = args[0]->ToString(vm)->ToString();
    StringUtils::SplitStr(str, ".", splitStr);
    if (splitStr.size() != 2) {
        LOGE("input string res value must can be splited by dot");
        return panda::JSValueRef::Undefined(vm);
    }

    auto targetStringKey = splitStr[0];
    auto targetStringKeyValue = splitStr[1];
    auto resultStrJson = JsiDeclarativeEngineInstance::GetI18nStringResource(targetStringKey, targetStringKeyValue);
    auto resultStr = resultStrJson->GetString();
    if (argc == 2) {
        panda::LocalScope scope(vm);
        if (args[1]->IsArray(vm)) {
            auto arrayVal = panda::Local<panda::ArrayRef>(args[1]);
            auto len = arrayVal->Length(vm);
            std::vector<std::string> arrayResult;
            for (int32_t i = 0; i < len; i++) {
                auto subItemVal = panda::ArrayRef::GetValueAt(vm, arrayVal, i);
                if (!subItemVal->IsString()) {
                    arrayResult.emplace_back(std::string());
                    continue;
                }
                auto itemVal = panda::Local<panda::StringRef>(subItemVal);
                arrayResult.emplace_back(itemVal->ToString());
            }
            ReplacePlaceHolderArray(resultStr, arrayResult);
        } else if (args[1]->IsObject()) {
            auto value = panda::JSON::Stringify(vm, args[1]);
            if (value->IsString()) {
                auto valueStr = panda::Local<panda::StringRef>(value);
                std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(valueStr->ToString());
                ReplacePlaceHolder(resultStr, argsPtr);
            }
        } else if (args[1]->IsNumber()) {
            double count = args[1]->ToNumber(vm)->Value();
            auto pluralChoice = Localization::GetInstance()->PluralRulesFormat(count);
            if (!pluralChoice.empty()) {
                resultStr = ParserPluralResource(resultStrJson, pluralChoice, str);
            }
        }
    }

    return panda::StringRef::NewFromUtf8(vm, resultStr.c_str());
}

panda::Local<panda::JSValueRef> JsGetMediaResource(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    LOGD("JsGetMediaResource");
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    if (!args[0]->IsString()) {
        LOGE("The arg is wrong, value must be string");
        return panda::JSValueRef::Undefined(vm);
    }

    std::string targetMediaFileName = args[0]->ToString(vm)->ToString();
    std::string filePath = JsiDeclarativeEngineInstance::GetMediaResource(targetMediaFileName);
    return panda::StringRef::NewFromUtf8(vm, filePath.c_str());
}

RefPtr<FrontendDelegate> JsGetFrontendDelegate()
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    if (!runtime) {
        return nullptr;
    }
    auto engineInstance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
    if (engineInstance == nullptr) {
        LOGE("engineInstance is null!");
        return nullptr;
    }
    return engineInstance->GetDelegate();
}

panda::Local<panda::JSValueRef> JsGetInspectorNodes(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    auto declarativeDelegate = AceType::DynamicCast<FrontendDelegateDeclarative>(JsGetFrontendDelegate());
    if (!declarativeDelegate) {
        LOGE("declarativeDelegate is null!");
        return panda::JSValueRef::Undefined(vm);
    }
    auto accessibilityManager = declarativeDelegate->GetJSAccessibilityManager();
    auto nodeInfos = accessibilityManager->DumpComposedElementsToJson();
    return panda::StringRef::NewFromUtf8(vm, nodeInfos->ToString().c_str());
}

panda::Local<panda::JSValueRef> JsGetInspectorNodeById(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    if (argc < 1 || !args[0]->IsNumber()) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    auto declarativeDelegate = OHOS::Ace::AceType::DynamicCast<FrontendDelegateDeclarative>(JsGetFrontendDelegate());
    if (!declarativeDelegate) {
        LOGE("declarativeDelegate is null!");
        return panda::JSValueRef::Undefined(vm);
    }
    auto accessibilityManager = declarativeDelegate->GetJSAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("accessibilityManager is null!");
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t intValue = args[0]->Int32Value(vm);
    auto nodeInfo = accessibilityManager->DumpComposedElementToJson(intValue);
    return panda::StringRef::NewFromUtf8(vm, nodeInfo->ToString().c_str());
}

panda::Local<panda::JSValueRef> Vp2Px(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    LOGD("Vp2Px");
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    if (!args[0]->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }

    double vpValue = args[0]->ToNumber(vm)->Value();
    double density = SystemProperties::GetResolution();
    double pxValue = vpValue * density;

    int32_t result = GreatOrEqual(pxValue, 0) ? (pxValue + 0.5) : (pxValue - 0.5);
    return panda::NumberRef::New(vm, result);
}

panda::Local<panda::JSValueRef> Px2Vp(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    LOGD("Px2Vp");
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    if (!args[0]->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }
    double density = SystemProperties::GetResolution();
    if (NearZero(density)) {
        LOGE("The density cannot be zero");
        return panda::JSValueRef::Undefined(vm);
    }

    double pxValue = args[0]->ToNumber(vm)->Value();
    double vpValue = pxValue / density;

    return panda::NumberRef::New(vm, vpValue);
}

panda::Local<panda::JSValueRef> Fp2Px(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    LOGD("Fp2Px");
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    if (!args[0]->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }

    double density = SystemProperties::GetResolution();
    double fpValue = args[0]->ToNumber(vm)->Value();

    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = pipelineContext->GetFontScale();
    double pxValue = fpValue * density * fontScale;

    int32_t result = GreatOrEqual(pxValue, 0) ? (pxValue + 0.5) : (pxValue - 0.5);
    return panda::NumberRef::New(vm, result);
}

panda::Local<panda::JSValueRef> Px2Fp(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    LOGD("Px2Fp");
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    if (!args[0]->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }
    double density = SystemProperties::GetResolution();
    if (NearZero(density)) {
        LOGE("The density cannot be zero");
        return panda::JSValueRef::Undefined(vm);
    }

    double pxValue = args[0]->ToNumber(vm)->Value();
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = pipelineContext->GetFontScale();
    double ratio = density * fontScale;
    double fpValue = pxValue / ratio;
    return panda::NumberRef::New(vm, fpValue);
}

panda::Local<panda::JSValueRef> Lpx2Px(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    LOGD("Lpx2Px");
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    if (!args[0]->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return panda::JSValueRef::Undefined(vm);
    }

    auto pipelineContext = container->GetPipelineContext();
    auto frontend = pipelineContext->GetFrontend();
    auto windowConfig = frontend->GetWindowConfig();
    double lpxValue = args[0]->ToNumber(vm)->Value();
    double pxValue = lpxValue * windowConfig.designWidthScale;

    int32_t result = GreatOrEqual(pxValue, 0) ? (pxValue + 0.5) : (pxValue - 0.5);
    return panda::NumberRef::New(vm, result);
}

panda::Local<panda::JSValueRef> Px2Lpx(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    LOGD("Px2Lpx");
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    if (!args[0]->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return panda::JSValueRef::Undefined(vm);
    }

    auto pipelineContext = container->GetPipelineContext();
    auto frontend = pipelineContext->GetFrontend();
    auto windowConfig = frontend->GetWindowConfig();
    double pxValue = args[0]->ToNumber(vm)->Value();
    double lpxValue = pxValue / windowConfig.designWidthScale;

    return panda::NumberRef::New(vm, lpxValue);
}

panda::Local<panda::JSValueRef> SetAppBackgroundColor(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> value,
    const panda::Local<panda::JSValueRef> args[], int32_t argc, void* data)
{
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Exception(vm);
    }
    if (!args[0]->IsString()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Exception(vm);
    }
    std::string backgroundColorStr = args[0]->ToString(vm)->ToString();
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return panda::JSValueRef::Exception(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext) {
        pipelineContext->SetRootBgColor(Color::FromString(backgroundColorStr));
    }
    return panda::JSValueRef::Undefined(vm);
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
    { "LazyForEach", JSLazyForEach::JSBind },
    { "List", JSList::JSBind },
    { "ListItem", JSListItem::JSBind },
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
    { "NavigationView", JSNavigationView::JSBind },
    { "Navigator", JSNavigator::JSBind },
    { "ColumnSplit", JSColumnSplit::JSBind },
    { "If", JSIfElse::JSBind },
    { "Scroll", JSScroll::JSBind },
    { "ScrollBar", JSScrollBar::JSBind },
    {"Stepper", JSStepper::JSBind },
    {"StepperItem", JSStepperItem::JSBind },
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
    { "DatePicker", JSDatePicker::JSBind },
    { "PageTransitionEnter", JSPageTransition::JSBind },
    { "PageTransitionExit", JSPageTransition::JSBind },
    { "RowSplit", JSRowSplit::JSBind },
    { "ColumnSplit", JSColumnSplit::JSBind },
    { "AlphabetIndexer", JSIndexer::JSBind },
    { "Hyperlink", JSHyperlink::JSBind },
    { "Radio", JSRadio::JSBind },
    { "ActionSheet", JSActionSheet::JSBind },
    { "AlertDialog", JSAlertDialog::JSBind },
    { "AbilityComponent", JSAbilityComponent::JSBind },
    { "TextArea", JSTextArea::JSBind },
    { "TextInput", JSTextInput::JSBind },
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    { "QRCode", JSQRCode::JSBind },
#ifdef FORM_SUPPORTED
    { "FormComponent", JSForm::JSBind },
#endif
#endif
#ifndef WEARABLE_PRODUCT
    { "Camera", JSCamera::JSBind },
    { "Piece", JSPiece::JSBind },
    { "Rating", JSRating::JSBind },
    { "Video", JSVideo::JSBind },
#endif
    { "DataPanel", JSDataPanel::JSBind },
    { "Badge", JSBadge::JSBind },
    { "Gauge", JSGauge::JSBind },
    { "Marquee", JSMarquee::JSBind },
    { "Gesture", JSGesture::JSBind },
    { "TapGesture", JSGesture::JSBind },
    { "LongPressGesture", JSGesture::JSBind },
    { "PanGesture", JSGesture::JSBind },
    { "PinchGesture", JSGesture::JSBind },
    { "RotationGesture", JSGesture::JSBind },
    { "GestureGroup", JSGesture::JSBind },
    { "PanGestureOption", JSPanGestureOption::JSBind },
    { "CustomDialogController", JSCustomDialogController::JSBind },
    { "Scroller", JSScroller::JSBind },
    { "SwiperController", JSSwiperController::JSBind },
    { "TabsController", JSTabsController::JSBind },
    { "CalendarController", JSCalendarController::JSBind },
    { "AbilityController", JSAbilityComponentController::JSBind },
    { "VideoController", JSVideoController::JSBind },
    { "Search", JSSearch::JSBind },
    { "Sheet", JSSheet::JSBind },
    { "JSClipboard", JSClipboard::JSBind }
};

void RegisterAllModule(BindingTarget globalObj)
{
    JSColumn::JSBind(globalObj);
    JSSwiperController::JSBind(globalObj);
    JSTabsController::JSBind(globalObj);
    JSScroller::JSBind(globalObj);
    JSCalendarController::JSBind(globalObj);
    JSAbilityComponentController::JSBind(globalObj);
    JSVideoController::JSBind(globalObj);
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
        JSAbilityComponentController::JSBind(globalObj);
    } else if ((*func).first == "Video") {
        JSVideoController::JSBind(globalObj);
    } else if ((*func).first == "Grid") {
        JSColumn::JSBind(globalObj);
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
}

void JsRegisterViews(BindingTarget globalObj)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "loadDocument"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsLoadDocument, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "dumpMemoryStats"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsDumpMemoryStats, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "$s"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetI18nResource, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "$m"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetMediaResource, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getInspectorNodes"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetInspectorNodes, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getInspectorNodeById"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetInspectorNodeById, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "vp2px"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Vp2Px, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "px2vp"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Vp, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "fp2px"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Fp2Px, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "px2fp"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Fp, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "lpx2px"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Lpx2Px, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "px2lpx"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Lpx, nullptr));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAppBgColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SetAppBackgroundColor, nullptr));

    JSViewAbstract::JSBind();
    JSContainerBase::JSBind();
    JSShapeAbstract::JSBind();
    JSView::JSBind(globalObj);

    JSEnvironment::JSBind(globalObj);
    JSViewContext::JSBind(globalObj);
    JSTouchHandler::JSBind(globalObj);
    JSPanHandler::JSBind(globalObj);
    JSGesture::JSBind(globalObj);
    JSPanGestureOption::JSBind(globalObj);
    JsDragFunction::JSBind(globalObj);
    JSCustomDialogController::JSBind(globalObj);
    JSShareData::JSBind(globalObj);
    JSPersistent::JSBind(globalObj);
    JSScroller::JSBind(globalObj);

    auto delegate = JsGetFrontendDelegate();
    std::string jsModules;
    if (delegate && delegate->GetAssetContent("component_collection.txt", jsModules)) {
        JsRegisterModules(globalObj, jsModules);
    } else {
        RegisterAllModule(globalObj);
    }

    JSObjectTemplate toggleType;
    toggleType.Constant("Checkbox", 0);
    toggleType.Constant("Switch", 1);
    toggleType.Constant("Button", 2);  // 2 means index of constant

    JSObjectTemplate refreshStatus;
    refreshStatus.Constant("Inactive", 0);
    refreshStatus.Constant("Drag", 1);
    refreshStatus.Constant("OverDrag", 2);
    refreshStatus.Constant("Refresh", 3); // 3 means index of constant
    refreshStatus.Constant("Done", 4); // 4 means index of constant

    JSObjectTemplate mainAxisAlign;
    mainAxisAlign.Constant("Start", 1);
    mainAxisAlign.Constant("Center", 2);  // 2 means index of constant
    mainAxisAlign.Constant("End", 3);  // 3 means index of constant
    mainAxisAlign.Constant("SpaceBetween", 6);  // 6 means index of constant
    mainAxisAlign.Constant("SpaceAround", 7);  // 7 means index of constant

    JSObjectTemplate crossAxisAlign;
    crossAxisAlign.Constant("Start", 1);

    crossAxisAlign.Constant("Center", 2);  // 2 means index of constant
    crossAxisAlign.Constant("End", 3);  // 3 means index of constant
    crossAxisAlign.Constant("Stretch", 4);  // 4 means index of constant

    JSObjectTemplate direction;
    direction.Constant("Horizontal", 0);
    direction.Constant("Vertical", 1);

    JSObjectTemplate loadingProgressStyle;
    loadingProgressStyle.Constant("Default", 1);
    loadingProgressStyle.Constant("Circular", 2);  // 2 means index of constant
    loadingProgressStyle.Constant("Orbital", 3);  // 3 means index of constant

    JSObjectTemplate progressStyle;
    progressStyle.Constant("Linear", 0);
    progressStyle.Constant("Capsule", 1);  // 1 means index of constant
    progressStyle.Constant("Eclipse", 2);  // 2 means index of constant
    progressStyle.Constant("Circular", 3);  // 3 means index of constant

    JSObjectTemplate stackFit;
    stackFit.Constant("Keep", 0);
    stackFit.Constant("Stretch", 1);
    stackFit.Constant("Inherit", 2);  // 2 means index of constant
    stackFit.Constant("FirstChild", 3);  // 3 means index of constant

    JSObjectTemplate overflow;
    overflow.Constant("Clip", 0);
    overflow.Constant("Observable", 1);

    JSObjectTemplate alignment;
    alignment.Constant("TopLeft", 0);
    alignment.Constant("TopCenter", 1);
    alignment.Constant("TopRight", 2);   // 2 means index of constant
    alignment.Constant("CenterLeft", 3);  // 3 means index of constant
    alignment.Constant("Center", 4);  // 4 means index of constant
    alignment.Constant("CenterRight", 5);  // 5 means index of constant
    alignment.Constant("BottomLeft", 6);  // 6 means index of constant
    alignment.Constant("BottomCenter", 7);  // 7 means index of constant
    alignment.Constant("BottomRight", 8);  // 8 means index of constant

    JSObjectTemplate sliderStyle;
    sliderStyle.Constant("OutSet", 0);
    sliderStyle.Constant("InSet", 1);

    JSObjectTemplate sliderChangeMode;
    sliderChangeMode.Constant("Begin", 0);
    sliderChangeMode.Constant("Moving", 1);
    sliderChangeMode.Constant("End", 2);  // 2 means index of constant

    JSObjectTemplate pickerStyle;
    pickerStyle.Constant("Inline", 0);
    pickerStyle.Constant("Block", 1);
    pickerStyle.Constant("Fade", 2);  // 2 means index of constant

    JSObjectTemplate buttonType;
    buttonType.Constant("Normal", (int)ButtonType::NORMAL);
    buttonType.Constant("Capsule", (int)ButtonType::CAPSULE);
    buttonType.Constant("Circle", (int)ButtonType::CIRCLE);
    buttonType.Constant("Arc", (int)ButtonType::ARC);

    JSObjectTemplate iconPosition;
    iconPosition.Constant("Start", 0);
    iconPosition.Constant("End", 1);

    JSObjectTemplate badgePosition;
    badgePosition.Constant("RightTop", 0);
    badgePosition.Constant("Right", 1);
    badgePosition.Constant("Left", 2); // 2 means index of constant

    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "MainAxisAlign"), *mainAxisAlign);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "CrossAxisAlign"), *crossAxisAlign);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Direction"), *direction);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "StackFit"), *stackFit);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Align"), *alignment);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Overflow"), *overflow);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "ButtonType"), *buttonType);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "LoadingProgressStyle"), *loadingProgressStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "ProgressStyle"), *progressStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "ToggleType"), *toggleType);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "RefreshStatus"), *refreshStatus);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "SliderStyle"), *sliderStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "SliderChangeMode"), *sliderChangeMode);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "IconPosition"), *iconPosition);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "PickerStyle"), *pickerStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "BadgePosition"), *badgePosition);
    LOGD("View classes and jsCreateDocuemnt, registerObservableObject functions registered.");
}

} // namespace OHOS::Ace::Framework
