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

#include "frameworks/bridge/declarative_frontend/jsview/js_pan_handler.h"

namespace OHOS::Ace::Framework {

RefPtr<OHOS::Ace::SingleChild> JSPanHandler::CreateComponent()
{
    LOGD("JSPanHandler wrapComponent");
    auto gestureComponent = AceType::MakeRefPtr<OHOS::Ace::GestureListenerComponent>();

    if (jsOnStartFunc_) {
        auto dragStartId = EventMarker(
            [func = std::move(jsOnStartFunc_)](const BaseEventInfo* info) {
                const DragStartInfo* dragStartInfo = static_cast<const DragStartInfo*>(info);

                if (!dragStartInfo) {
                    LOGE("Error processing event. Not an instance of DragStartInfo");
                    return;
                }
                func->execute(*dragStartInfo);
            },
            "dragStart", 0);
        gestureComponent->SetOnVerticalDragStartId(dragStartId);
    }

    if (jsOnUpdateFunc_) {
        auto dragUpdateId = EventMarker(
            [func = std::move(jsOnUpdateFunc_)](const BaseEventInfo* info) {
                const DragUpdateInfo* dragUpdateInfo = static_cast<const DragUpdateInfo*>(info);

                if (!dragUpdateInfo) {
                    LOGE("Error processing event. Not an instance of DragUpdateInfo");
                    return;
                }
                func->execute(*dragUpdateInfo);
            },
            "dragUpdate", 0);
        gestureComponent->SetOnVerticalDragUpdateId(dragUpdateId);
    }

    if (jsOnEndFunc_) {
        auto dragEndId = EventMarker(
            [func = std::move(jsOnEndFunc_)](const BaseEventInfo* info) {
                const DragEndInfo* dragEndInfo = static_cast<const DragEndInfo*>(info);

                if (!dragEndInfo) {
                    LOGE("Error processing event. Not an instance of DragEndInfo");
                    return;
                }
                func->execute(*dragEndInfo);
            },
            "dragEnd", 0);
        gestureComponent->SetOnVerticalDragEndId(dragEndId);
    }

    if (jsOnCancelFunc_) {
        auto dragCancelId = EventMarker(
            [func = std::move(jsOnCancelFunc_)](const BaseEventInfo* info) { func->execute(); }, "dragCancel", 0);
        gestureComponent->SetOnVerticalDragCancelId(dragCancelId);
    }

    return gestureComponent;
}

#ifdef USE_QUICKJS_ENGINE
void JSPanHandler::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSPanHandler => MarkGC: start");
    LOGD("JSPanHandler => MarkGC: end");
}

void JSPanHandler::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSPanHandler => release: start");
    LOGD("JSPanHandler => release: end");
}

// STATIC

JSValue JSPanHandler::JsHandlerOnTouch(
    PanEvent action, JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv)
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
        case PanEvent::DOWN:
            jsOnStartFunc_ = handlerFunc;
            break;
        case TouchEvent::UP:
            jsOnUpdateFunc_ = handlerFunc;
            break;
        case TouchEvent::MOVE:
            jsOnEndFunc_ = handlerFunc;
            break;
        case TouchEvent::CANCEL:
            jsOnCancelFunc_ = handlerFunc;
            break;
    }
    return JS_DupValue(ctx, jsObj); // for call chaining
}

JSValue JSPanHandler::JsHandlerOnDown(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv)
{
    return JSPanHandler::JsHandlerOnTouch(TouchEvent::DOWN, ctx, jsObj, argc, argv);
}

JSValue JSPanHandler::JsHandlerOnUp(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv)
{
    return JSPanHandler::JsHandlerOnTouch(PanEvent::UP, ctx, jsObj, argc, argv);
}

JSValue JSPanHandler::JsHandlerOnMove(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv)
{
    return JSPanHandler::JsHandlerOnTouch(PanEvent::MOVE, ctx, jsObj, argc, argv);
}

JSValue JSPanHandler::JsHandlerOnCancel(JSContext* ctx, JSValueConst jsObj, int argc, JSValueConst* argv)
{
    return JSPanHandler::JsHandlerOnTouch(PanEvent::CANCEL, ctx, jsObj, argc, argv);
}

// STATIC

void JSPanHandler::QjsDestructor(JSRuntime* rt, JSPanHandler* handler)
{
    LOGD("JSPanHandler(QjsDestructor) start");

    if (!handler)
        return;

    handler->ReleaseRT(rt);
    delete handler;
    LOGD("JSPanHandler(QjsDestructor) end");
}

void JSPanHandler::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSPanHandler(QjsGcMark) start");

    JSPanHandler* handler = Unwrap<JSPanHandler>(val);
    if (!handler)
        return;

    handler->MarkGC(rt, markFunc);
    LOGD("JSPanHandler(QjsGcMark) end");
}
#endif

#ifdef USE_V8_ENGINE

void JSPanHandler::JsHandlerOnPan(PanEvent action, const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    LOGD("JSPanHandler JsHandlerOnPan");
    if (args[0]->IsFunction()) {
        v8::Local<v8::Function> jsFunction = v8::Local<v8::Function>::Cast(args[0]);
        RefPtr<V8PanFunction> handlerFunc = AceType::MakeRefPtr<V8PanFunction>(jsFunction);
        switch (action) {
            case PanEvent::START:
                jsOnStartFunc_ = handlerFunc;
                break;
            case PanEvent::UPDATE:
                jsOnUpdateFunc_ = handlerFunc;
                break;
            case PanEvent::END:
                jsOnEndFunc_ = handlerFunc;
                break;
            case PanEvent::CANCEL:
                jsOnCancelFunc_ = handlerFunc;
                break;
        }
    }
    args.GetReturnValue().Set(args.This());
}

void JSPanHandler::JsHandlerOnStart(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSPanHandler::JsHandlerOnPan(PanEvent::START, args);
}

void JSPanHandler::JsHandlerOnUpdate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSPanHandler::JsHandlerOnPan(PanEvent::UPDATE, args);
}

void JSPanHandler::JsHandlerOnEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSPanHandler::JsHandlerOnPan(PanEvent::END, args);
}

void JSPanHandler::JsHandlerOnCancel(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSPanHandler::JsHandlerOnPan(PanEvent::CANCEL, args);
}

#endif
void JSPanHandler::JSBind(BindingTarget globalObj)
{
    JSClass<JSPanHandler>::Declare("PanHandler");
    JSClass<JSPanHandler>::CustomMethod("onStart", &JSPanHandler::JsHandlerOnStart);
    JSClass<JSPanHandler>::CustomMethod("onUpdate", &JSPanHandler::JsHandlerOnUpdate);
    JSClass<JSPanHandler>::CustomMethod("onEnd", &JSPanHandler::JsHandlerOnEnd);
    JSClass<JSPanHandler>::CustomMethod("onCancel", &JSPanHandler::JsHandlerOnCancel);
    JSClass<JSPanHandler>::Bind<>(globalObj);
}
}; // namespace OHOS::Ace::Framework
