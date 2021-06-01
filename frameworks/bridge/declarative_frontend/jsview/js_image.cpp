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

#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"

#include "base/log/ace_trace.h"

namespace OHOS::Ace::Framework {

#ifdef USE_QUICKJS_ENGINE
JSValue LoadImageSuccEventToJSValue(const LoadImageSuccessEvent& eventInfo, JSContext* ctx)
{
    JSValue eventObj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, eventObj, "width", JS_NewFloat64(ctx, eventInfo.GetWidth()));
    JS_SetPropertyStr(ctx, eventObj, "height", JS_NewFloat64(ctx, eventInfo.GetHeight()));
    return eventObj;
}

JSValue LoadImageFailEventToJSValue(const LoadImageFailEvent& eventInfo, JSContext* ctx)
{
    return JS_NewObject(ctx);
}
#endif

#ifdef USE_V8_ENGINE
v8::Local<v8::Value> LoadImageSuccEventToJSValue(const LoadImageSuccessEvent& eventInfo, v8::Isolate* isolate)
{
    ACE_DCHECK(isolate);
    auto context = isolate->GetCurrentContext();
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "width").ToLocalChecked(),
           v8::Number::New(isolate, eventInfo.GetWidth()))
        .ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "height").ToLocalChecked(),
           v8::Number::New(isolate, eventInfo.GetHeight()))
        .ToChecked();
    return v8::Local<v8::Value>(obj);
}

v8::Local<v8::Value> LoadImageFailEventToJSValue(const LoadImageFailEvent& eventInfo, v8::Isolate* isolate)
{
    return v8::Local<v8::Value>(v8::Object::New(isolate));
}
#endif

JSImage::~JSImage()
{
    LOGD("Destroy: JSImage");
}

RefPtr<OHOS::Ace::Component> JSImage::CreateSpecializedComponent()
{
    LOGD("Create component: Image");
    auto imageComponent = AceType::MakeRefPtr<OHOS::Ace::ImageComponent>(src_);
    imageComponent->SetAlt(alt_);
    imageComponent->SetImageFit(objectFit_);
    imageComponent->SetMatchTextDirection(matchTextDirection_);
    imageComponent->SetFitMaxSize(!fitOriginalSize_);
    if (jsLoadSuccFunc_) {
        imageComponent->SetLoadSuccessEventId(
            EventMarker([func = std::move(jsLoadSuccFunc_)](const BaseEventInfo* info) {
                auto eventInfo = TypeInfoHelper::DynamicCast<LoadImageSuccessEvent>(info);
                func->execute(*eventInfo);
            }));
    }
    if (jsLoadFailFunc_) {
        imageComponent->SetLoadFailEventId(EventMarker([func = std::move(jsLoadFailFunc_)](const BaseEventInfo* info) {
            LOGD("HandleLoadImageFail");
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadImageFailEvent>(info);
            func->execute(*eventInfo);
        }));
    }
    if (boxComponent_) {
        auto backDecoration = boxComponent_->GetBackDecoration();
        if (backDecoration) {
            Border border = backDecoration->GetBorder();
            if (border.TopLeftRadius().IsValid() && border.TopRightRadius().IsValid() &&
                border.BottomLeftRadius().IsValid() && border.BottomRightRadius().IsValid()) {
                imageComponent->SetBorder(border);
            }
        }
    }
    return imageComponent;
}

std::vector<RefPtr<OHOS::Ace::SingleChild>> JSImage::CreateInteractableComponents()
{
    return JSInteractableView::CreateComponents();
}

void JSImage::SetAlt(std::string& value)
{
    alt_ = value;
}

void JSImage::SetObjectFit(int32_t value)
{
    objectFit_ = static_cast<ImageFit>(value);
}

void JSImage::SetMatchTextDirection(bool value)
{
    matchTextDirection_ = value;
}

void JSImage::SetFitOriginalSize(bool value)
{
    fitOriginalSize_ = value;
}

#ifdef USE_QUICKJS_ENGINE
JSValue JSImage::QjsOnComplete(JSContext* ctx, JSValueConst jsObject, int argc, JSValueConst* argv)
{
    if ((argc != 1) || !JS_IsFunction(ctx, argv[0])) {
        LOGE("OnComplete expects a function as parameter. Throwing exception.");
        return JS_EXCEPTION;
    }
    QJSContext::Scope scope(ctx);
    JSImage* jsImage = Unwrap<JSImage>(jsObject);

    if (jsImage == nullptr) {
        LOGE("OnComplete must be called on a JSImage. Throwing exception.");
        return JS_EXCEPTION;
    }
    auto loadSuccHandler =
        new QJSEventFunction<LoadImageSuccessEvent, 2>(ctx, JS_DupValue(ctx, argv[0]), LoadImageSuccEventToJSValue);
    jsLoadSuccFunc_ = loadSuccHandler;
    return JS_DupValue(ctx, jsObject); // for call chain
}

JSValue JSImage::QjsOnError(JSContext* ctx, JSValueConst jsObject, int argc, JSValueConst* argv)
{
    if ((argc != 1) || !JS_IsFunction(ctx, argv[0])) {
        LOGE("OnError expects a function as parameter. Throwing exception.");
        return JS_EXCEPTION;
    }
    QJSContext::Scope scope(ctx);
    JSImage* jsImage = Unwrap<JSImage>(jsObject);

    if (jsImage == nullptr) {
        LOGE("OnError must be called on a JSImage. Throwing exception.");
        return JS_EXCEPTION;
    }
    auto loadFailHandler =
        new QJSEventFunction<LoadImageFailEvent, 0>(ctx, JS_DupValue(ctx, argv[0]), LoadImageFailEventToJSValue);
    jsLoadFailFunc_ = loadFailHandler;
    return JS_DupValue(ctx, jsObject);
}

void JSImage::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSImage => MarkGC: Mark value for GC start");
    JSInteractableView::MarkGC(rt, markFunc);
    LOGD("JSImage => MarkGC: Mark value for GC end");
}

void JSImage::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSImage => release start");
    JSInteractableView::ReleaseRT(rt);
    LOGD("JSImage => release end");
}

void JSImage::QjsDestructor(JSRuntime* rt, JSImage* view)
{
    LOGD("JSImage(QjsDestructor) start");
    if (!view)
        return;

    view->ReleaseRT(rt);
    delete view;
    LOGD("JSImage(QjsDestructor) end");
}

void JSImage::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSImage(QjsGcMark) start");

    JSImage* view = Unwrap<JSImage>(val);
    if (!view)
        return;

    view->MarkGC(rt, markFunc);
    LOGD("JSImage(QjsGcMark) end");
}
#endif // USE_QUICKJS_ENGINE

#ifdef USE_V8_ENGINE
void JSImage::V8OnComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("JSImage V8OnComplete");
    auto isolate = args.GetIsolate();
    v8::HandleScope handleScope(isolate);
    if (args[0]->IsFunction()) {
        v8::Local<v8::Function> loadSuccFunction = v8::Local<v8::Function>::Cast(args[0]);
        jsLoadSuccFunc_ = AceType::MakeRefPtr<V8EventFunction<LoadImageSuccessEvent, 2>>(
            loadSuccFunction, LoadImageSuccEventToJSValue);
    } else {
        LOGE("args not function");
    }
    args.GetReturnValue().Set(args.This());
}

void JSImage::V8OnError(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("JSImage V8OnError");
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    if (args[0]->IsFunction()) {
        v8::Local<v8::Function> loadErrorFunction = v8::Local<v8::Function>::Cast(args[0]);
        jsLoadFailFunc_ =
            AceType::MakeRefPtr<V8EventFunction<LoadImageFailEvent, 0>>(loadErrorFunction, LoadImageFailEventToJSValue);
    } else {
        LOGE("args not function");
    }
    args.GetReturnValue().Set(args.This());
}

#endif // USE_V8_ENGINE

void JSImage::JSBind(BindingTarget globalObj)
{
    JSClass<JSImage>::Declare("Image");
    JSClass<JSImage>::Inherit<JSViewAbstract>();
    JSClass<JSImage>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSImage>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSImage>::Method("alt", &JSImage::SetAlt, opt);
    JSClass<JSImage>::Method("objectFit", &JSImage::SetObjectFit, opt);
    JSClass<JSImage>::Method("matchTextDirection", &JSImage::SetMatchTextDirection, opt);
    JSClass<JSImage>::Method("fitOriginalSize", &JSImage::SetFitOriginalSize, opt);
#ifdef USE_QUICKJS_ENGINE
    JSClass<JSImage>::CustomMethod("onComplete", &JSImage::QjsOnComplete);
    JSClass<JSImage>::CustomMethod("onError", &JSImage::QjsOnError);
#endif
#ifdef USE_V8_ENGINE
    JSClass<JSImage>::CustomMethod("onComplete", &JSImage::V8OnComplete);
    JSClass<JSImage>::CustomMethod("onError", &JSImage::V8OnError);
#endif
    JSClass<JSImage>::Bind<std::string>(globalObj);
}

} // namespace OHOS::Ace::Framework
