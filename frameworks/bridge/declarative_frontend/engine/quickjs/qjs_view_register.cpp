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

#include "base/log/log.h"
#include "core/components/common/layout/constants.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine_instance.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_animation.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_button.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_column.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_divider.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_foreach.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_grid_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigator.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_row.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_sliding_panel.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_stack.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_swiper.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_touch_handler.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

static std::unordered_map<ViewId, JSViewAbstract*> g_viewMapById = {};

static JSValue JsLoadDocument(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("Load Document");

    if ((argc != 1) || (!JS_IsObject(argv[0]))) {
        return JS_ThrowSyntaxError(ctx, "loadDocument expects a single object as parameter");
    }

    QjsHandleScope sc(ctx);
    QJSContext::Scope scope(ctx);

    // JS_DupValue on arg[0]. And release when done. Otherwise it will get GC-d as soon as this function exits.
    // Store jsView in page, so when page is unloaded a call to JS_FreeValue is made to release it
    JSValue jsView = JS_DupValue(ctx, argv[0]);

    JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(jsView));
    if (!view) {
        return JS_ThrowReferenceError(ctx, "loadDocument: argument provided is not a View!");
    }

    auto page = QJSDeclarativeEngineInstance::GetRunningPage(ctx);
    LOGD("Load Document setting root view");
    page->SetRootComponent(view->CreateComponent());

    // We are done, tell to the JSAgePage
    page->SetPageCreated();

    return JS_UNDEFINED;
}

static JSValue JsDumpMemoryStats(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
#ifdef ACE_DEBUG
    QJSContext::Scope scope(ctx);

    QjsUtils::JsDumpMemoryStats(ctx);
    if (argc > 0) {
        LOGI("ACE Declarative JS Memory dump: %s ========================", ScopedString(argv[0]).get());
    } else {
        LOGI("ACE Declarative JS Memory dump: %s ========================", "unknown");
    }
    LOGI("View (cust. Component): %5d ", QJSKlass<JSView<JSView>>::NumberOfInstances());
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

JSValue JsAddViewById(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("js_add_view_by_id");
    if (argc != 2) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have 1 arguments");
    }

    QJSContext::Scope scp(ctx);

    if (JS_IsNumber(argv[0]) && JS_IsObject(argv[1])) {
        ViewId viewId = __detail__::FromJSValue<uint32_t>(argv[0]);
        JSViewAbstract* view = static_cast<JSViewAbstract*>(UnwrapAny(argv[1]));
        g_viewMapById.emplace(viewId, view);
    } else {
        return JS_ThrowSyntaxError(ctx, "addViewById, invalid arguments!");
    }

    return JS_UNDEFINED;
}

JSValue JsRemoveViewById(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("js_remove_view_by_id");
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have 1 arguments");
    }

    QJSContext::Scope scp(ctx);

    if (JS_IsNumber(argv[0])) {
        ViewId viewId = __detail__::FromJSValue<uint32_t>(argv[0]);
        g_viewMapById.erase(viewId);
    } else {
        return JS_ThrowSyntaxError(ctx, "removeViewById, invalid arguments!");
    }

    return JS_UNDEFINED;
}

JSValue JsMarkViewNeedUpdateById(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("js_mark_view_need_update_by_id");
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have 1 arguments");
    }

    QJSContext::Scope scp(ctx);

    if (JS_IsNumber(argv[0])) {
        ViewId viewId = __detail__::FromJSValue<uint32_t>(argv[0]);
        auto itr = g_viewMapById.find(viewId);
        if (itr != g_viewMapById.end()) {
            LOGD("markViewNeedUpdateById, View(%d)", viewId);
            itr->second->MarkNeedUpdate();
        } else {
            LOGE("markViewNeedUpdateById, stale view do not exist!");
        }
    } else {
        return JS_ThrowSyntaxError(ctx, "markViewNeedUpdateById, invalid arguments!");
    }

    return JS_UNDEFINED;
}

void JsRegisterViews(BindingTarget global)
{
    JSContext* ctx = QJSContext::current();

    QjsUtils::DefineGlobalFunction(ctx, JsLoadDocument, "loadDocument", 1);
    QjsUtils::DefineGlobalFunction(ctx, JsDumpMemoryStats, "dumpMemoryStats", 1);
    QjsUtils::DefineGlobalFunction(ctx, JsAddViewById, "addViewById", 1);
    QjsUtils::DefineGlobalFunction(ctx, JsRemoveViewById, "removeViewById", 1);
    QjsUtils::DefineGlobalFunction(ctx, JsMarkViewNeedUpdateById, "markViewNeedUpdateById", 1);

    JSViewAbstract::JSBind();
    JSText::JSBind(global);
    JSButton::JSBind(global);
    JSImage::JSBind(global);
    JSColumn::JSBind(global);
    JSRow::JSBind(global);
    JSList::JSBind(global);
    JSListItem::JSBind(global);
    JSView::JSBind(global);
    JSStack::JSBind(global);
    JSForEach::JSBind(global);
    JSGrid::JSBind(global);
    JSGridItem::JSBind(global);
    JSDivider::JSBind(global);
    JSSwiper::JSBind(global);
    JSSlidingPanel::JSBind(global);
    JSTouchHandler::JSBind(global);
    JSNavigator::JSBind(global);
    JSAnimation::JSBind(global);

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
    buttonType.Constant("Capsule", (int)ButtonType::CAPSULE);
    buttonType.Constant("Circle", (int)ButtonType::CIRCLE);

    JS_SetPropertyStr(ctx, global, "MainAxisAlign", *mainAxisAlign);
    JS_SetPropertyStr(ctx, global, "CrossAxisAlign", *crossAxisAlign);
    JS_SetPropertyStr(ctx, global, "Direction", *direction);
    JS_SetPropertyStr(ctx, global, "StackFit", *stackFit);
    JS_SetPropertyStr(ctx, global, "Align", *alignment);
    JS_SetPropertyStr(ctx, global, "Overflow", *overflow);
    JS_SetPropertyStr(ctx, global, "ButtonType", *buttonType);

    LOGD("View classes and jsCreateDocuemnt, registerObservableObject functions registered.");
}

void RemoveViewById(ViewId viewId)
{
    LOGD("js_view_register -> removeViewById(%d)", viewId);
    g_viewMapById.erase(viewId);
}

} // namespace OHOS::Ace::Framework
