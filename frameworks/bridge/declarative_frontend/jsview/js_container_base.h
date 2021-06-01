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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CONTAINER_BASE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CONTAINER_BASE_H

#include <list>

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"

#ifdef USE_QUICKJS_ENGINE
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"
#endif

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class JSContainerBase : public JSViewAbstract, public JSInteractableView {
    DECLARE_ACE_TYPE(JSContainerBase, JSViewAbstract);
protected:
#ifdef USE_V8_ENGINE
    JSContainerBase(const std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren);
#endif

#ifdef USE_QUICKJS_ENGINE
    JSContainerBase(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren);
#endif
    ~JSContainerBase() = default;
    virtual void Destroy(JSViewAbstract* parentCustomView) override;

protected:
#ifdef USE_QUICKJS_ENGINE
    void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    void ReleaseRT(JSRuntime* rt) override;
    static std::pair<std::list<JSViewAbstract*>, std::list<JSValue>> JsChildrenFromArgs(
        JSContext* ctx, int argc, JSValueConst* argv);
    static void JsChildrenFromValue(
        JSContext* ctx, JSValueConst value, std::list<JSViewAbstract*>& children, std::list<JSValue>& jsChildren);
    static void JsChildFromObject(
        JSContext* ctx, JSValueConst& argObj, std::list<JSViewAbstract*>& children, std::list<JSValue>& jsChildren);
    static void JsChildrenFromArray(
        JSContext* ctx, JSValueConst& argArray, std::list<JSViewAbstract*>& children, std::list<JSValue>& jsChildren);
    static void JsChildrenFromFunction(
        JSContext* ctx, JSValueConst& argObj, std::list<JSViewAbstract*>& children, std::list<JSValue>& jsChildren);
#endif

#ifdef USE_V8_ENGINE
    static void V8ChildrenFromArgs(const v8::FunctionCallbackInfo<v8::Value>& args,
        std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>>& jsChildren);
    static void V8ChildrenFromObject(v8::Local<v8::Context> context, v8::Local<v8::Value> v8Val,
        std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>>& jsChildren);
    static void V8ChildrenFromArray(v8::Local<v8::Context> context, v8::Local<v8::Value> argsObject,
        v8::Local<v8::Array> v8Array, std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>>& jsChildren);
    static void V8ChildrenFromFunction(v8::Local<v8::Context> context, v8::Local<v8::Value> argsObject,
        v8::Local<v8::Function> v8Func, std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>>& jsChildren);
#endif

protected:
    std::list<JSViewAbstract*> children_;
#ifdef USE_QUICKJS_ENGINE
    std::list<JSValue> jsChildren_;
#endif
#ifdef USE_V8_ENGINE
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren_;
#endif
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CONTAINER_BASE_H
