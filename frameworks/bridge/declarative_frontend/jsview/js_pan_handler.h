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

#ifndef FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_PAN_HANDLER_H
#define FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_PAN_HANDLER_H

#include "core/components/gesture_listener/gesture_listener_component.h"
#include "core/event/ace_event_handler.h"
#ifdef USE_QUICKJS_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_touch_function.h"
#endif

#ifdef USE_V8_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_pan_function.h"
#endif

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class JSPanHandler {
private:
    enum class PanEvent { START, UPDATE, END, CANCEL };

private:
    RefPtr<OHOS::Ace::Component> component_;
#ifdef USE_QUICKJS_ENGINE
    RefPtr<QJSTouchFunction> jsOnStartFunc_;
    RefPtr<QJSTouchFunction> jsOnUpdateFunc_;
    RefPtr<QJSTouchFunction> jsOnEndFunc_;
    RefPtr<QJSTouchFunction> jsOnCancelFunc_;
#elif USE_V8_ENGINE
    RefPtr<V8PanFunction> jsOnStartFunc_;
    RefPtr<V8PanFunction> jsOnUpdateFunc_;
    RefPtr<V8PanFunction> jsOnEndFunc_;
    RefPtr<V8PanFunction> jsOnCancelFunc_;
#endif

public:
    JSPanHandler() = default;
    virtual ~JSPanHandler()
    {
        LOGD("Destroy: JSPanHandler");
    }

    virtual RefPtr<OHOS::Ace::SingleChild> CreateComponent();

    static void JSBind(BindingTarget globalObj);

#ifdef USE_QUICKJS_ENGINE
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc);
    virtual void ReleaseRT(JSRuntime* rt);

    JSValue JsHandlerOnTouch(PanEvent action, JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv);
    JSValue JsHandlerOnDown(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv);
    JSValue JsHandlerOnUp(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv);
    JSValue JsHandlerOnMove(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv);
    JSValue JsHandlerOnCancel(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv);

    static void QjsDestructor(JSRuntime* rt, JSPanHandler* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#elif USE_V8_ENGINE
    void JsHandlerOnPan(PanEvent action, const v8::FunctionCallbackInfo<v8::Value>& args);
    void JsHandlerOnStart(const v8::FunctionCallbackInfo<v8::Value>& args);
    void JsHandlerOnUpdate(const v8::FunctionCallbackInfo<v8::Value>& args);
    void JsHandlerOnEnd(const v8::FunctionCallbackInfo<v8::Value>& args);
    void JsHandlerOnCancel(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif

}; // JSPanHandler

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_PAN_HANDLER_H
