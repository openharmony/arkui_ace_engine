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

#include "frameworks/bridge/declarative_frontend/jsview/js_navigator.h"

namespace OHOS::Ace::Framework {

#ifdef USE_QUICKJS_ENGINE
JSNavigator::JSNavigator(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren)
    : JSContainerBase(children, jsChildren)
#else
JSNavigator::JSNavigator(const std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren)
    : JSContainerBase(children, jsChildren)
#endif
{}

RefPtr<OHOS::Ace::Component> JSNavigator::CreateSpecializedComponent()
{
    LOGD("Create component: JSNavigator");
    auto child = children_.front();
    if (!child) {
        LOGE("JSNavigator children is null");
        return nullptr;
    }
    auto component = child->CreateComponent();
    auto navigatorComponent = AceType::MakeRefPtr<OHOS::Ace::NavigatorComponent>(component);

    navigatorComponent->SetUri(uri_);
    navigatorComponent->SetType(type_);
    navigatorComponent->SetActive(active_);

    return navigatorComponent;
}

void JSNavigator::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavigator>::Declare("Navigator");
    JSClass<JSNavigator>::Inherit<JSViewAbstract>();
    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSNavigator>::Method("target", &JSNavigator::SetUri, opt);
    JSClass<JSNavigator>::Method("type", &JSNavigator::SetType, opt);
    JSClass<JSNavigator>::Method("active", &JSNavigator::SetActive, opt);
    JSClass<JSNavigator>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSNavigator>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSNavigator>::Bind(globalObj, ConstructorCallback);
}

#ifdef USE_QUICKJS_ENGINE
void JSNavigator::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSNavigator => MarkGC: start");
    JSContainerBase::MarkGC(rt, markFunc);
    JSInteractableView::MarkGC(rt, markFunc);
    LOGD("JSNavigator => MarkGC: end");
}

void JSNavigator::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSNavigator => release children: start");
    JSContainerBase::ReleaseRT(rt);
    JSInteractableView::ReleaseRT(rt);
    LOGD("JSNavigator => release children: end");
}

void JSNavigator::QjsDestructor(JSRuntime* rt, JSNavigator* view)
{
    LOGD("JSNavigator(QjsDestructor) start");
    if (!view) {
        return;
    }

    view->ReleaseRT(rt);
    delete view;
    view = nullptr;
    LOGD("JSNavigator(QjsDestructor) end");
}

void JSNavigator::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSNavigator(QjsGcMark) start");
    JSNavigator* view = Unwrap<JSNavigator>(val);
    if (!view) {
        return;
    }

    view->MarkGC(rt, markFunc);
    LOGD("JSNavigator(QjsGcMark) end");
}

// STATIC qjs_class_bindings
JSValue JSNavigator::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSNavigator::ConstructorCallback");
    QJSContext::Scope scope(ctx);
    auto [children, jsChildren] = JsChildrenFromArgs(ctx, argc, argv);
    JSNavigator* navigator = new JSNavigator(children, jsChildren);
    return Wrap<JSNavigator>(new_target, navigator);
}
#endif

#ifdef USE_V8_ENGINE
void JSNavigator::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("ConstructorCallback");
    std::list<JSViewAbstract*> children;
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren;
    V8ChildrenFromArgs(args, children, jsChildren);
    auto instance = V8Object<JSNavigator>::New(args.This(), children, jsChildren);
    args.GetReturnValue().Set(instance->Get());
}
#endif

} // namespace OHOS::Ace::Framework
