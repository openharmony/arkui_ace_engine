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
#include "core/components/common/layout/constants.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine_instance.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_alert_dialog.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_animator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_blank.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_button.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_calendar.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_calendar_controller.h"
#ifndef WEARABLE_PRODUCT
#include "frameworks/bridge/declarative_frontend/jsview/js_camera.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_circle.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_column.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_column_split.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_counter.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_divider.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_ellipse.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_environment.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_flex_impl.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_foreach.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_gesture.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_container.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_if_else.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image_animator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigation_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_path.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_persistent.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_toggle.h"
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
#include "frameworks/bridge/declarative_frontend/jsview/js_qrcode.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_page_transition.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_rect.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_row.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_row_split.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_scroll.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_scroller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_sliding_panel.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_span.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_stack.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_swiper.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tab_content.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tabs.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_touch_handler.h"
#ifndef WEARABLE_PRODUCT
#include "frameworks/bridge/declarative_frontend/jsview/js_video.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

static JSValue JsLoadDocument(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("Load Document");

    if ((argc != 1) || (!JS_IsObject(argv[0]))) {
        return JS_ThrowSyntaxError(ctx, "loadDocument expects a single object as parameter");
    }

    QJSHandleScope sc(ctx);
    QJSContext::Scope scope(ctx);

    // JS_DupValue on arg[0]. And release when done. Otherwise it will get GC-d as soon as this function exits.
    // Store jsView in page, so when page is unloaded a call to JS_FreeValue is made to release it
    JSValue jsView = JS_DupValue(ctx, argv[0]);

    JSView* view = static_cast<JSView*>(UnwrapAny(jsView));
    if (!view) {
        return JS_ThrowReferenceError(ctx, "loadDocument: argument provided is not a View!");
    }

    auto page = QJSDeclarativeEngineInstance::GetRunningPage(ctx);
    LOGD("Load Document setting root view");
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
    // We are done, tell to the JSAgePage
    page->SetPageCreated();

    return JS_UNDEFINED;
}

static JSValue JsDumpMemoryStats(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
#ifdef ACE_DEBUG
    QJSContext::Scope scope(ctx);

    QJSUtils::JsDumpMemoryStats(ctx);
    if (argc > 0) {
        LOGI("ACE Declarative JS Memory dump: %s ========================", ScopedString(argv[0]).get());
    } else {
        LOGI("ACE Declarative JS Memory dump: %s ========================", "unknown");
    }
    LOGI("View (cust. Component): %5d ", QJSKlass<JSView>::NumberOfInstances());
    LOGI("ForEach:                %5d ", QJSKlass<JSForEach>::NumberOfInstances());
    LOGI("Row:                    %5d ", QJSKlass<JSRow>::NumberOfInstances());
    LOGI("Column:                 %5d ", QJSKlass<JSColumn>::NumberOfInstances());
    LOGI("Text:                   %5d ", QJSKlass<JSText>::NumberOfInstances());
    LOGI("Image:                  %5d ", QJSKlass<JSImage>::NumberOfInstances());
    LOGI("Button:                 %5d ", QJSKlass<JSButton>::NumberOfInstances());
    LOGI("Grid:                   %5d ", QJSKlass<JSGrid>::NumberOfInstances());
    LOGI("GridItem:               %5d ", QJSKlass<JSGridItem>::NumberOfInstances());
    LOGI("List:                   %5d ", QJSKlass<JSList>::NumberOfInstances());
    LOGI("ListItem:               %5d ", QJSKlass<JSListItem>::NumberOfInstances());
#endif
    return JS_UNDEFINED;
}

JSValue JsGetI18nResource(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("JsGetI18nResource");
    if (argc != 2 && argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one or two arguments");
    }

    QJSContext::Scope scp(ctx);
    if (!JS_IsString(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be string");
    }

    std::vector<std::string> splitStr;
    ScopedString targetString(ctx, argv[0]);
    std::string str = targetString.get();
    StringUtils::SplitStr(str, ".", splitStr);
    if (splitStr.size() != 2) {
        return JS_ThrowSyntaxError(ctx, "input string res value must can be splited by dot");
    }

    auto targetStringKey = splitStr[0];
    auto targetStringKeyValue = splitStr[1];
    auto resultStrJson = QJSDeclarativeEngineInstance::GetI18nStringResource(targetStringKey, targetStringKeyValue);
    auto resultStr = resultStrJson->GetString();
    if (argc == 2) {
        if (JS_IsArray(ctx, argv[1])) {
            auto len = QJSUtils::JsGetArrayLength(ctx, argv[1]);
            std::vector<std::string> arrayResult;
            for (int32_t i = 0; i < len; i++) {
                JSValue subItemVal = JS_GetPropertyUint32(ctx, argv[1], i);
                if (!JS_IsString(subItemVal)) {
                    arrayResult.emplace_back(std::string());
                    JS_FreeValue(ctx, subItemVal);
                    continue;
                }

                ScopedString subScopedStr(ctx, subItemVal);
                arrayResult.emplace_back(subScopedStr.get());
            }

            ReplacePlaceHolderArray(resultStr, arrayResult);
        } else if (JS_IsObject(argv[1])) {
            std::unique_ptr<JsonValue> argsJson = JsonUtil::Create(true);
            JSPropertyEnum* pTab = nullptr;
            uint32_t len = 0;
            if (CheckAndGetJsProperty(ctx, argv[1], &pTab, &len)) {
                for (uint32_t i = 0; i < len; i++) {
                    auto key = JS_AtomToCString(ctx, pTab[i].atom);
                    if (key == nullptr) {
                        JS_FreeAtom(ctx, pTab[i].atom);
                        LOGW("key is null. Ignoring!");
                        continue;
                    }
                    JSValue value = JS_GetProperty(ctx, argv[1], pTab[i].atom);
                    if (JS_IsString(value)) {
                        ScopedString valStr(ctx, value);
                        argsJson->Put(key, valStr.get());
                    }
                }
                ReplacePlaceHolder(resultStr, argsJson);
            }
        } else if (JS_IsNumber(argv[1])) {
            ScopedString valueString(ctx, argv[1]);
            auto count = StringToDouble(valueString.get());
            auto pluralChoice = Localization::GetInstance()->PluralRulesFormat(count);
            if (!pluralChoice.empty()) {
                resultStr = ParserPluralResource(resultStrJson, pluralChoice, str);
            }
        }
    }

    JSValue result = JS_NewString(ctx, resultStr.c_str());
    return result;
}

JSValue JsGetMediaResource(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("JsGetMediaResource");
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one argument");
    }

    QJSContext::Scope scp(ctx);
    if (!JS_IsString(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be string");
    }

    ScopedString targetMediaFileJsName(ctx, argv[0]);
    std::string targetMediaFileName = targetMediaFileJsName.get();
    std::string filePath = QJSDeclarativeEngineInstance::GetMeidaResource(targetMediaFileName);
    JSValue result = JS_NewString(ctx, filePath.c_str());
    return result;
}

void JsRegisterViews(BindingTarget globalObj)
{
    JSContext* ctx = QJSContext::Current();

    QJSUtils::DefineGlobalFunction(ctx, JsLoadDocument, "loadDocument", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsDumpMemoryStats, "dumpMemoryStats", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsGetI18nResource, "$s", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsGetMediaResource, "$m", 1);

    JSViewAbstract::JSBind();
    JSContainerBase::JSBind();
    JSShapeAbstract::JSBind();
    JSView::JSBind(globalObj);
    JSAnimator::JSBind(globalObj);
    JSText::JSBind(globalObj);
    JSSpan::JSBind(globalObj);
    JSButton::JSBind(globalObj);
    JSLazyForEach::JSBind(globalObj);
    JSList::JSBind(globalObj);
    JSListItem::JSBind(globalObj);
    JSImage::JSBind(globalObj);
    JSImageAnimator::JSBind(globalObj);
    JSColumn::JSBind(globalObj);
    JSCounter::JSBind(globalObj);
    JSRow::JSBind(globalObj);
    JSGrid::JSBind(globalObj);
    JSGridItem::JSBind(globalObj);
    JSStack::JSBind(globalObj);
    JSForEach::JSBind(globalObj);
    JSDivider::JSBind(globalObj);
    JSSwiper::JSBind(globalObj);
    JSSwiperController::JSBind(globalObj);
    JSSlidingPanel::JSBind(globalObj);
    JSNavigationView::JSBind(globalObj);
    JSNavigator::JSBind(globalObj);
    JSColumnSplit::JSBind(globalObj);
    JSIfElse::JSBind(globalObj);
    JSEnvironment::JSBind(globalObj);
    JSViewContext::JSBind(globalObj);
    JSFlexImpl::JSBind(globalObj);
    JSScroll::JSBind(globalObj);
    JSScroller::JSBind(globalObj);
    JSToggle::JSBind(globalObj);
    JSBlank::JSBind(globalObj);
    JSCalendar::JSBind(globalObj);
    JSPersistent::JSBind(globalObj);
    JSCalendarController::JSBind(globalObj);
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    JSQRCode::JSBind(globalObj);
#endif
    JSRect::JSBind(globalObj);
    JSShape::JSBind(globalObj);
    JSPath::JSBind(globalObj);
    JSCircle::JSBind(globalObj);
    JSEllipse::JSBind(globalObj);
#ifndef WEARABLE_PRODUCT
    JSCamera::JSBind(globalObj);
    JSVideo::JSBind(globalObj);
#endif
    JSTabs::JSBind(globalObj);
    JSTabContent::JSBind(globalObj);

    JSTouchHandler::JSBind(globalObj);
    JSGesture::JSBind(globalObj);
    JSPageTransition::JSBind(globalObj);
    JSRowSplit::JSBind(globalObj);
    JSColumnSplit::JSBind(globalObj);
    JSGridContainer::JSBind(globalObj);

    JSObjectTemplate toggleType;
    toggleType.Constant("Checkbox", 0);
    toggleType.Constant("Switch", 1);
    toggleType.Constant("Button", 2);

    JSAlertDialog::JSBind(globalObj);

    JSObjectTemplate mainAxisAlign;
    mainAxisAlign.Constant("Start", 1);
    mainAxisAlign.Constant("Center", 2);
    mainAxisAlign.Constant("End", 3);
    mainAxisAlign.Constant("SpaceBetween", 6);
    mainAxisAlign.Constant("SpaceAround", 7);

    JSObjectTemplate crossAxisAlign;
    crossAxisAlign.Constant("Start", 1);

    crossAxisAlign.Constant("Center", 2);
    crossAxisAlign.Constant("End", 3);
    crossAxisAlign.Constant("Stretch", 4);

    JSObjectTemplate direction;
    direction.Constant("Horizontal", 0);
    direction.Constant("Vertical", 1);

    JSObjectTemplate stackFit;
    stackFit.Constant("Keep", 0);
    stackFit.Constant("Stretch", 1);
    stackFit.Constant("Inherit", 2);
    stackFit.Constant("FirstChild", 3);

    JSObjectTemplate overflow;
    overflow.Constant("Clip", 0);
    overflow.Constant("Observable", 1);

    JSObjectTemplate alignment;
    alignment.Constant("TopLeft", 0);
    alignment.Constant("TopCenter", 1);
    alignment.Constant("TopRight", 2);
    alignment.Constant("CenterLeft", 3);
    alignment.Constant("Center", 4);
    alignment.Constant("CenterRight", 5);
    alignment.Constant("BottomLeft", 6);
    alignment.Constant("BottomCenter", 7);
    alignment.Constant("BottomRight", 8);

    JSObjectTemplate buttonType;
    buttonType.Constant("Normal", (int)ButtonType::NORMAL);
    buttonType.Constant("Capsule", (int)ButtonType::CAPSULE);
    buttonType.Constant("Circle", (int)ButtonType::CIRCLE);
    buttonType.Constant("Arc", (int)ButtonType::ARC);

    JS_SetPropertyStr(ctx, globalObj, "MainAxisAlign", *mainAxisAlign);
    JS_SetPropertyStr(ctx, globalObj, "CrossAxisAlign", *crossAxisAlign);
    JS_SetPropertyStr(ctx, globalObj, "Direction", *direction);
    JS_SetPropertyStr(ctx, globalObj, "StackFit", *stackFit);
    JS_SetPropertyStr(ctx, globalObj, "Align", *alignment);
    JS_SetPropertyStr(ctx, globalObj, "Overflow", *overflow);
    JS_SetPropertyStr(ctx, globalObj, "ButtonType", *buttonType);

    LOGD("View classes and jsCreateDocuemnt, registerObservableObject functions registered.");
}

} // namespace OHOS::Ace::Framework
