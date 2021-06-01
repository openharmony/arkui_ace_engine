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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TOUCH_HANDLER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TOUCH_HANDLER_H

#include "core/components/touch_listener/touch_listener_component.h"
#include "core/event/ace_event_handler.h"
#ifdef USE_QUICKJS_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_touch_function.h"
#endif

#ifdef USE_V8_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_touch_function.h"
#endif

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class JSTouchHandler {
private:
    enum TouchEvent { DOWN, UP, MOVE, CANCEL };

private:
    RefPtr<OHOS::Ace::Component> component_;
#ifdef USE_QUICKJS_ENGINE
    RefPtr<QJSTouchFunction> jsOnDownFunc_;
    RefPtr<QJSTouchFunction> jsOnUpFunc_;
    RefPtr<QJSTouchFunction> jsOnMoveFunc_;
    RefPtr<QJSTouchFunction> jsOnCancelFunc_;
#elif USE_V8_ENGINE
    RefPtr<V8TouchFunction> jsOnDownFunc_;
    RefPtr<V8TouchFunction> jsOnUpFunc_;
    RefPtr<V8TouchFunction> jsOnMoveFunc_;
    RefPtr<V8TouchFunction> jsOnCancelFunc_;
#endif

public:
    JSTouchHandler() = default;
    virtual ~JSTouchHandler()
    {
        LOGD("Destroy: JSTouchHandler");
    }

    virtual RefPtr<OHOS::Ace::SingleChild> CreateComponent();

    static void JSBind(BindingTarget globalObj);

#ifdef USE_QUICKJS_ENGINE
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc);
    virtual void ReleaseRT(JSRuntime* rt);

    JSValue JsHandlerOnTouch(TouchEvent action, JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv);
    JSValue JsHandlerOnDown(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv);
    JSValue JsHandlerOnUp(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv);
    JSValue JsHandlerOnMove(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv);
    JSValue JsHandlerOnCancel(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv);

    static void QjsDestructor(JSRuntime* rt, JSTouchHandler* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#elif USE_V8_ENGINE
    void JsHandlerOnTouch(TouchEvent action, const v8::FunctionCallbackInfo<v8::Value>& args);
    void JsHandlerOnDown(const v8::FunctionCallbackInfo<v8::Value>& args);
    void JsHandlerOnUp(const v8::FunctionCallbackInfo<v8::Value>& args);
    void JsHandlerOnMove(const v8::FunctionCallbackInfo<v8::Value>& args);
    void JsHandlerOnCancel(const v8::FunctionCallbackInfo<v8::Value>& args);

#endif

}; // JSTouchHandler

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TOUCH_HANDLER_H
