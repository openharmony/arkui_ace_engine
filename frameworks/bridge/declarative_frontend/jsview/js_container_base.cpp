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

#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"
#ifdef USE_V8_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/v8/v8_utils.h"
#endif

namespace OHOS::Ace::Framework {

#ifdef USE_V8_ENGINE
JSContainerBase::JSContainerBase(const std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren)
    : children_(children), jsChildren_(jsChildren) {};
#endif

#ifdef USE_QUICKJS_ENGINE
JSContainerBase::JSContainerBase(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren)
    : children_(children), jsChildren_(jsChildren) {};
#endif

void JSContainerBase::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("JSContainerBase::Destroy() start");

    auto startIter = children_.begin();
    auto endIter = children_.end();
    auto startJsIter = jsChildren_.begin();

    while (startIter != endIter) {
        if (!(*startIter)->IsCustomView()) {
            (*startIter)->Destroy(parentCustomView);
        }
#ifdef USE_V8_ENGINE
        (*startJsIter).Reset();
#elif USE_QUICKJS_ENGINE
        // Do nothing on the jsChildren here. That will be taken care of in releaseRT();
#endif
        ++startIter;
        ++startJsIter;
    }
    LOGD("JSContainerBase::Destroy() end");
}

#ifdef USE_QUICKJS_ENGINE

void JSContainerBase::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSContainerBase => MarkGC: start");
    if (!jsChildren_.empty()) {
        for (JSValue jsChild : jsChildren_) {
            JSViewAbstract* child = static_cast<JSViewAbstract*>(UnwrapAny(jsChild));
            if (!child->IsCustomView()) {
                JS_MarkValue(rt, jsChild, markFunc);
            }
        }
    }
    LOGD("JSContainerBase => MarkGC: end");
}

void JSContainerBase::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSContainerBase => release: start");
    if (!jsChildren_.empty()) {
        LOGD("JSContainerBase => release children: start");
        for (JSValue jsChild : jsChildren_) {
            JSViewAbstract* child = static_cast<JSViewAbstract*>(UnwrapAny(jsChild));
            if (!child->IsCustomView()) {
                JS_FreeValueRT(rt, jsChild);
            }
        }
        LOGD("JSContainerBase => release children: end");
    }
    LOGD("JSContainerBase => release: end");
}

std::pair<std::list<JSViewAbstract*>, std::list<JSValue>> JSContainerBase::JsChildrenFromArgs(
    JSContext* ctx, int argc, JSValueConst* argv)
{
    std::list<JSViewAbstract*> children;
    std::list<JSValue> jsChildren;

    for (int i = 0; i < argc; i++) {
        JsChildrenFromValue(ctx, argv[i], children, jsChildren);
    }

    return std::make_pair(std::move(children), std::move(jsChildren));
}

void JSContainerBase::JsChildrenFromValue(
    JSContext* ctx, JSValueConst value, std::list<JSViewAbstract*>& children, std::list<JSValue>& jsChildren)
{
    QJSContext::Scope scope(ctx);

    if (JS_IsFunction(ctx, value)) {
        LOGW("JsFlexConstructorInternal -> Function argument. Processing...");
        JsChildrenFromFunction(ctx, value, children, jsChildren);
    } else if (JS_IsArray(ctx, value)) {
        LOGW("JsFlexConstructorInternal -> Array argument. Processing...");
        JsChildrenFromArray(ctx, value, children, jsChildren);
    } else if (JS_IsObject(value)) {
        LOGW("JsFlexConstructorInternal -> Object argument. Processing...");
        JSValue duplicate = JS_DupValue(ctx, value);
        JsChildFromObject(ctx, duplicate, children, jsChildren);
    } else {
        LOGW("JsFlexConstructorInternal -> Unsupported child. Not an instance of View. Skipping.");
    }
}

void JSContainerBase::JsChildFromObject(
    JSContext* ctx, JSValueConst& argObj, std::list<JSViewAbstract*>& children, std::list<JSValue>& jsChildren)
{
    JSViewAbstract* child = static_cast<JSViewAbstract*>(UnwrapAny(argObj));
    // Might be an empty object or unsupported. Check if JSViewAbstract opaque is attached
    if (child) {
        LOGD("JsFlexChildFromObject -> Add child");
        children.emplace_back(child);
        jsChildren.emplace_back(argObj);
    } else {
        LOGW("JsFlexChildFromObject -> Unsupported child. Not an instance of View. Skipping.");
        JS_FreeValue(ctx, argObj);
    }
}

void JSContainerBase::JsChildrenFromArray(
    JSContext* ctx, JSValueConst& argArray, std::list<JSViewAbstract*>& children, std::list<JSValue>& jsChildren)
{
    int32_t length = QjsUtils::JsGetArrayLength(ctx, argArray);
    if (length < 0) {
        LOGE("JsFlexChildrenFromArray -> Error retrieving array\'s length.");
        return;
    }

    for (int i = 0; i < length; i++) {
        // JS_GetPropertyUint32 makes a copy of JSValue, but we cannot release it immediately because that would
        // destroy the view.
        JSValue element = JS_GetPropertyUint32(ctx, argArray, i);

        // Needs to be an object to potentially hold a view
        if (JS_IsFunction(ctx, element)) {
            JsChildrenFromFunction(ctx, element, children, jsChildren);
        } else if (JS_IsArray(ctx, element)) {
            // Nested array. Call self recursively
            JsChildrenFromArray(ctx, element, children, jsChildren);
        } else if (JS_IsObject(element)) {
            JsChildFromObject(ctx, element, children, jsChildren);
        } else {
            // Unsupported child. Release immediately
            LOGW("JsFlexChildrenFromArray -> Unsupported child. Not an instance of View. Skipping");
            JS_FreeValue(ctx, element);
        }
    }
}

void JSContainerBase::JsChildrenFromFunction(
    JSContext* ctx, JSValueConst& argObj, std::list<JSViewAbstract*>& children, std::list<JSValue>& jsChildren)
{
    JSValue result = JS_Call(ctx, argObj, JS_UNDEFINED, 0, NULL);

    if (JS_IsException(result)) {
        LOGE("JsFlexChildFromObject -> Error executing argument function");
        QjsUtils::JsStdDumpErrorAce(ctx);
        JS_FreeValue(ctx, result);
    } else if (JS_IsUndefined(result) || JS_IsNull(result)) {
        LOGW("JsFlexChildFromObject -> Function does not return a view, or a list of views. Skipping...");
        JS_FreeValue(ctx, result);
    } else if (JS_IsArray(ctx, result)) {
        LOGW("JsFlexChildFromObject -> Function result is array");
        JsChildrenFromArray(ctx, result, children, jsChildren);
    } else if (JS_IsObject(result)) {
        LOGW("JsFlexChildFromObject -> Function result is object");
        JsChildFromObject(ctx, result, children, jsChildren);
    }
}

#endif

#ifdef USE_V8_ENGINE

void JSContainerBase::V8ChildrenFromArgs(const v8::FunctionCallbackInfo<v8::Value>& args,
    std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>>& jsChildren)
{
    LOGD("V8ChildrenFromArgs");
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();
    if (context.IsEmpty()) {
        LOGE("context is empty!");
        return;
    }

    int argc = args.Length();
    // Process arguments
    for (int i = 0; i < argc; i++) {
        if (args[i]->IsFunction()) {
            v8::Local<v8::Object> v8Obj = args[i]->ToObject(context).ToLocalChecked();
            v8::Local<v8::Function> v8Func = v8::Local<v8::Function>::Cast(v8Obj);
            V8ChildrenFromFunction(context, args.This(), v8Func, children, jsChildren);
        } else if (args[i]->IsArray()) {
            v8::Local<v8::Object> v8Obj = args[i]->ToObject(context).ToLocalChecked();
            v8::Local<v8::Array> v8Array = v8::Local<v8::Array>::Cast(v8Obj);
            V8ChildrenFromArray(context, args.This(), v8Array, children, jsChildren);
        } else if (args[i]->IsObject()) {
            V8ChildrenFromObject(context, args[i], children, jsChildren);
        } else {
            LOGW("V8ChildrenFromArgs -> Unsupported child. Skipping.");
            continue;
        }
    }
}

void JSContainerBase::V8ChildrenFromObject(v8::Local<v8::Context> context, v8::Local<v8::Value> v8Val,
    std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>>& jsChildren)
{
    v8::Local<v8::Object> obj = v8Val->ToObject(context).ToLocalChecked();
    JSViewAbstract* value = static_cast<JSViewAbstract*>(obj->GetAlignedPointerFromInternalField(0));
    if (value) {
        children.emplace_back(value);
        jsChildren.emplace_back(
            v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>(v8::Isolate::GetCurrent(), obj));
    }
}

void JSContainerBase::V8ChildrenFromArray(v8::Local<v8::Context> context, v8::Local<v8::Value> argsObject,
    v8::Local<v8::Array> v8Array, std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>>& jsChildren)
{
    int length = v8Array->Length();
    for (int i = 0; i < length; i++) {
        v8::Local<v8::Value> v8Val = v8Array->Get(context, i).ToLocalChecked();
        if (v8Val->IsFunction()) {
            v8::Local<v8::Object> v8Obj = v8Val->ToObject(context).ToLocalChecked();
            v8::Local<v8::Function> v8Func = v8::Local<v8::Function>::Cast(v8Obj);
            V8ChildrenFromFunction(context, argsObject, v8Func, children, jsChildren);
        } else if (v8Val->IsArray()) {
            v8::Local<v8::Array> innerArray = v8::Local<v8::Array>::Cast(v8Val);
            V8ChildrenFromArray(context, argsObject, innerArray, children, jsChildren);
        } else if (v8Val->IsObject()) {
            V8ChildrenFromObject(context, v8Val, children, jsChildren);
        }
    }
}

void JSContainerBase::V8ChildrenFromFunction(v8::Local<v8::Context> context, v8::Local<v8::Value> argsObject,
    v8::Local<v8::Function> v8Func, std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>>& jsChildren)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);
    LOGD("V8 CALL: %s", V8Utils::ScopedString(v8Func).get());
    v8::TryCatch tryCatch(isolate);
    v8::Local<v8::Value> result;
    bool success = v8Func->Call(context, argsObject, 0, nullptr).ToLocal(&result);
    if (!success) {
        LOGE("V8ChildrenFromFunction V8 CALL fail!");
        V8Utils::JsStdDumpErrorAce(isolate, &tryCatch);
        return;
    }

    if (result->IsArray()) {
        v8::Local<v8::Object> v8Obj = result->ToObject(context).ToLocalChecked();
        v8::Local<v8::Array> v8Array = v8::Local<v8::Array>::Cast(v8Obj);
        V8ChildrenFromArray(context, argsObject, v8Array, children, jsChildren);
    } else if (result->IsObject()) {
        V8ChildrenFromObject(context, result, children, jsChildren);
    } else {
        LOGW("V8ChildrenFromFunction -> Unsupported child.");
    }
}

#endif

} // namespace OHOS::Ace::Framework
