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

#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"

#include "base/log/ace_trace.h"
#include "core/pipeline/base/composed_element.h"

#ifdef USE_V8_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/v8/v8_utils.h"
#endif

namespace OHOS::Ace::Framework {

#ifdef USE_QUICKJS_ENGINE
JSView::JSView(JSContext* ctx, JSValue jsObject, JSValue jsRenderFunction)
{
    jsViewFunction_ = AceType::MakeRefPtr<QJSViewFunction>(ctx, jsObject, jsRenderFunction);
    LOGD("JSView constructor");
}
#endif
#ifdef USE_V8_ENGINE
JSView::JSView(v8::Local<v8::Object> jsObject, v8::Local<v8::Function> jsRenderFunction) : JSCustomViewBase()
{
    jsViewFunction_ = AceType::MakeRefPtr<V8ViewFunction>(jsObject, jsRenderFunction);
    LOGD("JSView constructor");
};
#endif

JSView::~JSView()
{
    jsViewFunction_.Reset();
    LOGD("DestroyJSView");
};

RefPtr<OHOS::Ace::Component> JSView::CreateSpecializedComponent()
{
    ACE_SCOPED_TRACE("JSView::CreateSpecializedComponent");
    LOGD("Create component: View  -> create composed component");
    // create component, return new something, need to set proper ID
    auto composedComponent =
        AceType::MakeRefPtr<ComposedComponent>(HasUniqueKey() ? GetUniqueKey() : std::string(""), "view");

    // add callback for element creation to component, and get pointer reference
    // to the element on creation. When state of this view changes, mark the
    // element to dirty.

    auto renderFunction = [&]() -> RefPtr<Component> { return internalRender(); };

    auto elementFunction = [&, renderFunction](OHOS::Ace::ComposedElement* element) {
        if (!element_) {
            jsViewFunction_->executeAppear();
        }
        element_ = element;
        // add render function callback to element. when the element rebuilds due
        // to state update it will call this callback to get the new child component.
        element_->SetRenderFunction(std::move(renderFunction));
    };

    composedComponent->SetElementFunction(std::move(elementFunction));

    if (IsStatic()) {
        LOGD("will mark composedComponent as static");
        composedComponent->SetStatic();
    }
    return composedComponent;
}

RefPtr<OHOS::Ace::Component> JSView::internalRender()
{
    LOGD("JSView: internalRender");
    needsUpdate_ = false;
    jsViewFunction_->executeAboutToRender();
    auto childView = jsViewFunction_->executeRender();

    if (childView) {
        auto component = childView->CreateComponent();
        jsViewFunction_->executeOnRenderDone();
        JSCustomViewBase::CleanUpAbandonedChild();
        jsViewFunction_->Destroy(this);
        LOGD("JSView: internalRender end");
        return component;
    }

    jsViewFunction_->executeOnRenderDone();
    return nullptr;
}

/**
 * marks the JSView's composed component as needing update / rerender
 */
void JSView::MarkNeedUpdate()
{
    ACE_DCHECK((getElement() != nullptr) && "JSView's ComposedElement must be created before requesting an update");
    ACE_SCOPED_TRACE("JSView::MarkNeedUpdate");
    LOGD("JSView View(%d) has just been marked to need update", getViewId());
    getElement()->MarkDirty();
    needsUpdate_ = true;
}

void JSView::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("JSView::Destroy start");
    JSCustomViewBase::Destroy(parentCustomView);
    jsViewFunction_->executeDisappear();
    jsViewFunction_.Reset();
    LOGD("JSView::Destroy end");
}

void JSView::JSBind(BindingTarget object)
{
    JSClass<JSView>::Declare("NativeView");
    JSClass<JSView>::Inherit<JSViewAbstract>();
    JSClass<JSView>::Bind(object, ConstructorCallback);
}

#ifdef USE_V8_ENGINE
void JSView::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    v8::Local<v8::Value> renderFunc =
        info.This()->Get(context, V8ValueConvertor::toV8Value<std::string>("render")).ToLocalChecked();

    if (!renderFunc->IsFunction()) {
        V8Utils ::ThrowException("View derived classes must provide render(){...} function");
        return;
    }

    int argc = info.Length();
    if (argc > 1 && (info[0]->IsNumber() || info[0]->IsString())) {
        V8Utils::ScopedString viewId(info[0]);
        if (!info[1]->IsUndefined() && info[1]->IsObject()) {
            v8::Local<v8::Object> parentObj = info[1]->ToObject(context).ToLocalChecked();
            JSView* parentView = static_cast<JSView*>(parentObj->GetAlignedPointerFromInternalField(0));
            auto shouldRecycle = parentView->FindChildById(viewId);
            if (shouldRecycle) {
                auto [view, jsView] = parentView->GetChildById(viewId);
                info.GetReturnValue().Set(jsView);
                if (!view->NeedsUpdate()) {
                    view->MarkStatic();
                }
            } else {
                auto instance =
                    V8Object<JSView>::New(info.This(), info.This(), v8::Local<v8::Function>::Cast(renderFunc));
                info.GetReturnValue().Set(instance->Get());

                JSViewAbstract* view =
                    static_cast<JSViewAbstract*>(instance->Get()->GetAlignedPointerFromInternalField(0));
                parentView->AddChildById(viewId, view, instance->Get());
            }
            return;
        }
        auto instance = V8Object<JSView>::New(info.This(), info.This(), v8::Local<v8::Function>::Cast(renderFunc));
        info.GetReturnValue().Set(instance->Get());
    } else {
        LOGE("JSView creation with invalid arguments.");
        V8Utils ::ThrowException("JSView creation with invalid arguments.");
    }
}
#endif // USE_V8_ENGINE

#ifdef USE_QUICKJS_ENGINE
void JSView::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSView => MarkGC: start");
    // this should always be true
    if (jsViewFunction_) {
        jsViewFunction_->MarkGC(rt, markFunc);
    }
    LOGD("JSView => MarkGC: end");
}

void JSView::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSView => release: start");
    // this should always be true
    if (jsViewFunction_) {
        jsViewFunction_->ReleaseRT(rt);
    }

    LOGD("JSView => release: end");
}

// STATIC qjs_class_binding
JSValue JSView::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSView::QjsConstructor");
    JSValue jsObject = JS_UNDEFINED;
    JSAtom renderProp = JS_NewAtom(ctx, "render");
    JSValue jsRenderFunction;
    JSView* view = nullptr;

    QJSContext::Scope scope(ctx);

    if (JS_IsUndefined(new_target)) {
        return JS_ThrowSyntaxError(ctx, "View called without 'new'!");
    }

    auto proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) {
        LOGE("Can not find prototype of JS View");
        JS_FreeValue(ctx, jsObject);
        JS_FreeAtom(ctx, renderProp);
        return proto;
    }

    if (argc > 1 && (JS_IsNumber(argv[0]) || JS_IsString(argv[0]))) {
        ScopedString viewId(argv[0]);

        JSView* parentView = nullptr;
        if (!JS_IsUndefined(argv[1]) && JS_IsObject(argv[1])) {
            parentView = static_cast<JSView*>(UnwrapAny(argv[1]));
        }

        if (parentView && parentView->FindChildById(viewId)) {
            auto [recycleView, jsView] = parentView->GetChildById(viewId);
            if (!recycleView->NeedsUpdate()) {
                recycleView->MarkStatic();
            }
            JS_FreeAtom(ctx, renderProp);
            JS_FreeValue(ctx, proto);
            return jsView;
        } else {
            // Merge properties defined in JS file with inherited properties - set as new prototype
            jsObject = QJSKlass<JSView>::NewObjectProtoClass(proto);

            LOGD("before JS_GetPropertyNoMagic");
            //  this does nto work because jsObject is exotic: JS_GetProperty(ctx, jsObject, renderProp);
            // JS_GetPropertyNoMagic is a new function we added to QuickJS.
            // It seves a very special purpose just for this one case here:
            // the JS render() function is part of the JS object prototype.
            // Since the object is a magic one a regular JS_GetProperty can not read
            // it (instead the request for the property is to ExoitcGet)
            // JS_GetPropertyNoMagic reads the function from the object's prototype
            // so that it store in JSRenderFunction.
            // use JS_GetPropertyNoMagic instead?;
            jsRenderFunction = JS_GetProperty(ctx, jsObject, renderProp);
            LOGD("after JS_GetPropertyNoMagic");

            if (!JS_IsFunction(ctx, jsRenderFunction)) {
                LOGE("View derived classes must provide render(){...} function");
                JS_FreeValue(ctx, jsObject);
                JS_FreeAtom(ctx, renderProp);
                return JS_ThrowSyntaxError(ctx, "View derived classes must provide render(){...} function");
            }
            view = new JSView(ctx, jsObject, jsRenderFunction);
            if (parentView) {
                parentView->AddChildById(viewId, view, jsObject);
            }
        }
    } else {
        JS_FreeValue(ctx, jsObject);
        JS_FreeAtom(ctx, renderProp);
        return JS_ThrowSyntaxError(ctx, "JSView 2 creation with invalid arguments.");
    }

    JS_FreeAtom(ctx, renderProp);
    JS_FreeValue(ctx, jsRenderFunction);
    JS_FreeValue(ctx, proto);

    JS_SetOpaque(jsObject, view);

    return jsObject;
}

void JSView::QjsDestructor(JSRuntime* rt, JSView* view)
{
    LOGD("JSView(QjsDestructor) start");
    if (!view)
        return;

    view->ReleaseRT(rt);
    delete view;
    LOGD("JSView(QjsDestructor) end");
}

void JSView::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSView(QjsGcMark) start");

    JSView* view = Unwrap<JSView>(val);
    if (!view) {
        LOGE("Failed to unwrap JSView!");
        return;
    }
    view->MarkGC(rt, markFunc);
    LOGD("JSView(QjsGcMark) end");
}
#endif

} // namespace OHOS::Ace::Framework
