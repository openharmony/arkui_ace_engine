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

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"

#include "core/components/gesture_listener/gesture_listener_component.h"
#include "core/gestures/click_recognizer.h"
#include "core/pipeline/base/single_child.h"

namespace OHOS::Ace::Framework {
JSInteractableView::~JSInteractableView()
{
    LOGD("Destroy: JSInteractableView");
}

std::vector<RefPtr<OHOS::Ace::SingleChild>> JSInteractableView::CreateComponents()
{
    std::vector<RefPtr<OHOS::Ace::SingleChild>> result;
    if (jsOnTouchFunc_) {
        auto onTouchId = EventMarker(
            [func = std::move(jsOnTouchFunc_)](const BaseEventInfo* info) {
                const TouchCallBackInfo* touchInfo = static_cast<const TouchCallBackInfo*>(info);
                if (!touchInfo) {
                    LOGE("Error processing event. Not an instance of TouchCallBackInfo");
                    return;
                }
                func->execute(*touchInfo);
            },
            "onTouch", 0);
        auto touchComponent = AceType::MakeRefPtr<OHOS::Ace::TouchListenerComponent>();
        touchComponent->SetOnTouchId(onTouchId);
        result.emplace_back(touchComponent);
    }
    if (panHandler_) {
        result.emplace_back(panHandler_->CreateComponent());
    }
    if (onClickFunc_) {
        auto onClickId = EventMarker([func = std::move(onClickFunc_)](const BaseEventInfo* info) {
            LOGD("About to call onclick method on js");
#ifdef USE_QUICKJS_ENGINE
            func->execute();
#elif USE_V8_ENGINE
            auto clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
            func->execute(*clickInfo);
#endif
        });
        auto clickHandler = AceType::MakeRefPtr<OHOS::Ace::GestureListenerComponent>();
        clickHandler->SetOnClickId(onClickId);
        result.emplace_back(std::move(clickHandler));
    }
    return result;
}

void JSInteractableView::SetTouchHandler(JSTouchHandler* touchHandler)
{
    LOGD("JSInteractableView setTouchHandler");
    touchHandler_ = touchHandler;
}

void JSInteractableView::SetPanHandler(JSPanHandler* panHandler)
{
    LOGD("JSInteractableView setPanHandler");
    panHandler_ = panHandler;
}

void JSInteractableView::SetClickHandler(RefPtr<ClickFunction>& clickHandler)
{
    onClickFunc_ = clickHandler;
}

#ifdef USE_QUICKJS_ENGINE
void JSInteractableView::AttachJSTouchHandler(JSValueConst jsHandler)
{
    jsHandler_ = jsHandler;
}

void JSInteractableView::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSInteractableView => MarkGC: Mark value for GC start");
    if (!JS_IsNull(jsHandler_)) {
        JS_MarkValue(rt, jsHandler_, markFunc);
    }
    LOGD("JSInteractableView => MarkGC: Mark value for GC end");
}

void JSInteractableView::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSInteractableView => release start");
    if (!JS_IsNull(jsHandler_)) {
        JS_FreeValueRT(rt, jsHandler_);
    }

    LOGD("JSInteractableView => release end");
}

JSValue JSInteractableView::JsOnTouch(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv)
{
    if ((argc != 1) || !JS_IsObject(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "touch() expects a TouchHandler object as parameter. Throwing exception.");
    }

    JSTouchHandler* handler = Unwrap<JSTouchHandler>(argv[0]);
    if (!handler) {
        return JS_ThrowSyntaxError(ctx, "touch() expects a TouchHandler object as parameter. Throwing exception.");
    }

    SetTouchHandler(handler);
    AttachJSTouchHandler(JS_DupValue(ctx, argv[0]));
    return JS_DupValue(ctx, this_value); // chaining
}

JSValue JSInteractableView::JsOnClick(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv)
{
    if ((argc != 1) || !JS_IsFunction(ctx, argv[0])) {
        LOGE("onCick expects a function as parameter. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "onClick() expect a function parameter. Throwing exception");
    }

    QJSContext::Scope scope(ctx);

    // Dup and Free shoulj happen inside the QJSClickFunction
    RefPtr<QJSClickFunction> clickHandler = AceType::MakeRefPtr<QJSClickFunction>(ctx, JS_DupValue(ctx, argv[0]));
    SetClickHandler(clickHandler);
    return JS_DupValue(ctx, this_value); // for call chaining
}

#endif

#ifdef USE_V8_ENGINE
void JSInteractableView::JsOnTouch(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    if (args.Length() > 0 && args[0]->IsFunction()) {
        v8::Local<v8::Function> jsFunction = v8::Local<v8::Function>::Cast(args[0]);
        jsOnTouchFunc_ = AceType::MakeRefPtr<V8TouchFunction>(jsFunction);
    }
    args.GetReturnValue().Set(args.This());
}

void JSInteractableView::JsOnPan(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    LOGD("JSInteractableView JsOnPan");
    if (args[0]->IsObject()) {
        v8::Local<v8::Object> obj = args[0]->ToObject(context).ToLocalChecked();
        JSPanHandler* handler = static_cast<JSPanHandler*>(obj->GetAlignedPointerFromInternalField(0));
        SetPanHandler(handler);
    }
    args.GetReturnValue().Set(args.This());
}

void JSInteractableView::JsOnClick(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    LOGD("JSInteractableView JsOnClick");
    if (info[0]->IsFunction()) {
        v8::Local<v8::Function> clickFunction = v8::Local<v8::Function>::Cast(info[0]);
        RefPtr<V8ClickFunction> jsOnClickFunc = AceType::MakeRefPtr<V8ClickFunction>(clickFunction);
        SetClickHandler(jsOnClickFunc);
    }
    info.GetReturnValue().Set(info.This());
}
#endif
} // namespace OHOS::Ace::Framework
