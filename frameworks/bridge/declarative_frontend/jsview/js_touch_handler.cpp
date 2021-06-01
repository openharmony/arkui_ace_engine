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

#include "frameworks/bridge/declarative_frontend/jsview/js_touch_handler.h"

namespace OHOS::Ace::Framework {

RefPtr<OHOS::Ace::SingleChild> JSTouchHandler::CreateComponent()
{
    LOGD("JSTouchHandler wrapComponent");
    auto touchComponent = AceType::MakeRefPtr<OHOS::Ace::TouchListenerComponent>();
    return touchComponent;
}

#ifdef USE_QUICKJS_ENGINE
void JSTouchHandler::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSTouchHandler => MarkGC: start");
    LOGD("JSTouchHandler => MarkGC: end");
}

void JSTouchHandler::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSTouchHandler => release: start");
    LOGD("JSTouchHandler => release: end");
}

// STATIC

JSValue JSTouchHandler::JsHandlerOnTouch(
    TouchEvent action, JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv)
{
    if ((argc != 1) || !JS_IsFunction(ctx, argv[0])) {
        LOGE("onCick expects a function as parameter. Throwing exception.");
        return JS_EXCEPTION;
    }

    QJSContext::Scope scope(ctx);
    // Dup and Free shoulj happen inside the QJSTouchFunction
    RefPtr<QJSTouchFunction> handlerFunc = AceType::MakeRefPtr<QJSTouchFunction>(ctx, JS_DupValue(ctx, argv[0]));

    // TODO: Release previously allocated functions here
    switch (action) {
        case TouchEvent::DOWN:
            jsOnDownFunc_ = handlerFunc;
            break;
        case TouchEvent::UP:
            jsOnUpFunc_ = handlerFunc;
            break;
        case TouchEvent::MOVE:
            jsOnMoveFunc_ = handlerFunc;
            break;
        case TouchEvent::CANCEL:
            jsOnCancelFunc_ = handlerFunc;
            break;
    }
    return JS_DupValue(ctx, jsObj); // for call chaining
}

JSValue JSTouchHandler::JsHandlerOnDown(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv)
{
    return JSTouchHandler::JsHandlerOnTouch(TouchEvent::DOWN, ctx, jsObj, argc, argv);
}

JSValue JSTouchHandler::JsHandlerOnUp(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv)
{
    return JSTouchHandler::JsHandlerOnTouch(TouchEvent::UP, ctx, jsObj, argc, argv);
}

JSValue JSTouchHandler::JsHandlerOnMove(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv)
{
    return JSTouchHandler::JsHandlerOnTouch(TouchEvent::MOVE, ctx, jsObj, argc, argv);
}

JSValue JSTouchHandler::JsHandlerOnCancel(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv)
{
    return JSTouchHandler::JsHandlerOnTouch(TouchEvent::CANCEL, ctx, jsObj, argc, argv);
}

// STATIC

void JSTouchHandler::QjsDestructor(JSRuntime* rt, JSTouchHandler* handler)
{
    LOGD("JSTouchHandler(QjsDestructor) start");

    if (!handler)
        return;

    handler->ReleaseRT(rt);
    delete handler;
    LOGD("JSTouchHandler(QjsDestructor) end");
}

void JSTouchHandler::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSTouchHandler(QjsGcMark) start");

    JSTouchHandler* handler = Unwrap<JSTouchHandler>(val);
    if (!handler)
        return;

    handler->MarkGC(rt, markFunc);
    LOGD("JSTouchHandler(QjsGcMark) end");
}
#endif

#ifdef USE_V8_ENGINE

void JSTouchHandler::JsHandlerOnTouch(TouchEvent action, const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    LOGD("JSTouchHandler JsHandlerOnTouch");
    if (args[0]->IsFunction()) {
        v8::Local<v8::Function> jsFunction = v8::Local<v8::Function>::Cast(args[0]);
        RefPtr<V8TouchFunction> handlerFunc = AceType::MakeRefPtr<V8TouchFunction>(jsFunction);
        switch (action) {
            case TouchEvent::DOWN:
                jsOnDownFunc_ = handlerFunc;
                break;
            case TouchEvent::UP:
                jsOnUpFunc_ = handlerFunc;
                break;
            case TouchEvent::MOVE:
                jsOnMoveFunc_ = handlerFunc;
                break;
            case TouchEvent::CANCEL:
                jsOnCancelFunc_ = handlerFunc;
                break;
        }
    }
    args.GetReturnValue().Set(args.This());
}

void JSTouchHandler::JsHandlerOnDown(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSTouchHandler::JsHandlerOnTouch(TouchEvent::DOWN, args);
}

void JSTouchHandler::JsHandlerOnUp(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSTouchHandler::JsHandlerOnTouch(TouchEvent::UP, args);
}

void JSTouchHandler::JsHandlerOnMove(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSTouchHandler::JsHandlerOnTouch(TouchEvent::MOVE, args);
}

void JSTouchHandler::JsHandlerOnCancel(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSTouchHandler::JsHandlerOnTouch(TouchEvent::CANCEL, args);
}

#endif
void JSTouchHandler::JSBind(BindingTarget globalObj)
{
    JSClass<JSTouchHandler>::Declare("TouchHandler");
    JSClass<JSTouchHandler>::CustomMethod("onDown", &JSTouchHandler::JsHandlerOnDown);
    JSClass<JSTouchHandler>::CustomMethod("onUp", &JSTouchHandler::JsHandlerOnUp);
    JSClass<JSTouchHandler>::CustomMethod("onMove", &JSTouchHandler::JsHandlerOnMove);
    JSClass<JSTouchHandler>::CustomMethod("onCancel", &JSTouchHandler::JsHandlerOnCancel);
    JSClass<JSTouchHandler>::Bind<>(globalObj);
}
}; // namespace OHOS::Ace::Framework
