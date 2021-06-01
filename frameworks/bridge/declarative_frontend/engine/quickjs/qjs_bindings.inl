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

#include "qjs_bindings.h"

#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_function_list_entries_container.h"

namespace OHOS::Ace::Framework {

template<typename T>
JSValue QJSKlass<T>::proto_ = JS_UNDEFINED;
template<typename T>
std::unordered_map<std::string, JSCFunctionListEntry*> QJSKlass<T>::functions_;
template<typename T>
JSClassDef QJSKlass<T>::classDefinitions_ = { nullptr, .finalizer = QJSKlass<T>::Finalizer,
    .gc_mark = QJSKlass<T>::GcMark, .exotic = nullptr, .call = nullptr };
template<typename T>
JSClassExoticMethods QJSKlass<T>::exoticMethods_;
template<typename T>
JSClassID QJSKlass<T>::classId_;
template<typename T>
FunctionCallback QJSKlass<T>::constructor_ = nullptr;

template<typename T>
JSValue Wrap(JSValueConst newTarget, T* thisPtr)
{
    JSContext* ctx = QJSContext::current();
    JSValue proto = JS_GetPropertyStr(ctx, newTarget, "prototype");
    JSValue thisJs = QJSKlass<T>::NewObjectProtoClass(proto);
    JS_FreeValue(ctx, proto);
    JS_SetOpaque(thisJs, thisPtr);
    LOGD("Wrap: Wrapping a raw pointer of %s around a new JSValue...", JSClass<T>::JSName());
    return thisJs;
}

template<typename T>
JSValue Wrap(T* thisPtr)
{
    JSValue thisJs = QJSKlass<T>::NewInstance();
    JS_SetOpaque(thisJs, thisPtr);
    LOGD("Wrap: Wrapping a raw pointer of %s around a new JSValue...", JSClass<T>::JSName());
    return thisJs;
}

template<typename T>
T* Unwrap(JSValueConst val)
{
    return QJSKlass<T>::Unwrap(val);
}

template<typename C>
void QJSKlass<C>::Declare(const char* name)
{
    classDefinitions_.class_name = name;
    JS_NewClassID(&classId_);
    g_classIds.push_back(classId_);

    JSContext* ctx = QJSContext::current();
    classDefinitions_.exotic = &exoticMethods_;
    JS_NewClass(JS_GetRuntime(ctx), classId_, &classDefinitions_);

    proto_ = JS_NewObject(ctx);
    JS_SetClassProto(ctx, classId_, proto_);
}

template<typename C>
template<typename R, typename... Args>
void QJSKlass<C>::Method(const char* name, R (C::*func)(Args...), int id)
{
    JSCFunctionListEntry* funcEntry = QJSFunctionListEntriesContainer::GetInstance().New(
        name, JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE, JS_DEF_CFUNC, id);
    funcEntry->u.func = { sizeof...(Args), JS_CFUNC_generic_magic };

    funcEntry->u.func.cfunc.generic_magic = MethodCallback<C, R, Args...>;
    functions_.insert_or_assign(name, funcEntry);
}

template<typename C>
template<typename Base, typename R, typename... Args>
void QJSKlass<C>::Method(const char* name, R (Base::*func)(Args...), int id)
{
    JSCFunctionListEntry* funcEntry = QJSFunctionListEntriesContainer::GetInstance().New(
        name, JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE, JS_DEF_CFUNC, id);
    funcEntry->u.func = { sizeof...(Args), JS_CFUNC_generic_magic };

    funcEntry->u.func.cfunc.generic_magic = MethodCallback<Base, R, Args...>;
    functions_.insert_or_assign(name, funcEntry);
}

template<typename C>
void QJSKlass<C>::CustomMethod(const char* name, FunctionCallback cb)
{
    JSCFunctionListEntry* funcEntry = QJSFunctionListEntriesContainer::GetInstance().New(
        name, JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE, JS_DEF_CFUNC, 0);
    funcEntry->u.func = { 1, JS_CFUNC_generic };

    funcEntry->u.func.cfunc.generic = cb;
    functions_.insert_or_assign(name, funcEntry);
}

template<typename C>
template<typename T>
void QJSKlass<C>::CustomMethod(const char* name, MemberFunctionCallback<T> cb, int id)
{
    JSCFunctionListEntry* funcEntry = QJSFunctionListEntriesContainer::GetInstance().New(
        name, JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE, JS_DEF_CFUNC, id);
    funcEntry->u.func = { 0, JS_CFUNC_generic_magic };

    funcEntry->u.func.cfunc.generic_magic = InternalMemberFunctionCallback<T>;
    functions_.insert_or_assign(name, funcEntry);
}

template<typename C>
void QJSKlass<C>::ExoticGetter(ExoticGetterCallback callback)
{
    exoticMethods_.get_property = callback;
}
template<typename C>
void QJSKlass<C>::ExoticSetter(ExoticSetterCallback callback)
{
    exoticMethods_.set_property = callback;
}
template<typename C>
void QJSKlass<C>::ExoticHasProperty(ExoticHasPropertyCallback callback)
{
    exoticMethods_.has_property = callback;
}
template<typename C>
void QJSKlass<C>::ExoticIsArray(ExoticIsArrayCallback callback)
{
    exoticMethods_.is_array = callback;
}

template<typename C>
template<typename... Args>
void QJSKlass<C>::Bind(BindingTarget target)
{
    BindInternal(target, QJSKlass<C>::InternalConstructor<Args...>, sizeof...(Args));
}

template<typename C>
void QJSKlass<C>::Bind(BindingTarget target, FunctionCallback ctor)
{
    constructor_ = ctor;
    BindInternal(target, ConstructorInterceptor, 0);
}

template<typename C>
template<typename Base>
void QJSKlass<C>::Inherit()
{
    static_assert(std::is_base_of_v<Base, C> && "Trying to inherit from unrelated class!");
    functions_.insert(QJSKlass<Base>::functions_.begin(), QJSKlass<Base>::functions_.end());
}

template<typename C>
C* QJSKlass<C>::Unwrap(JSValueConst val)
{
    return static_cast<C*>(JS_GetOpaque(val, classId_));
}

template<typename C>
JSValue QJSKlass<C>::NewObjectProtoClass(JSValue proto)
{
    return JS_NewObjectProtoClass(QJSContext::current(), proto, classId_);
}

template<typename C>
JSValue QJSKlass<C>::NewInstance()
{
    return JS_NewObjectClass(QJSContext::current(), classId_);
}

template<typename C>
JSValue QJSKlass<C>::GetProto()
{
    return proto_;
}

template<typename C>
int QJSKlass<C>::NumberOfInstances()
{
    return JS_CountClassInstances(JS_GetRuntime(QJSContext::current()), classId_);
}

template<typename C>
void QJSKlass<C>::BindInternal(BindingTarget target, FunctionCallback ctor, size_t length)
{
    JSContext* ctx = QJSContext::current();
    if (!ctx || !JS_GetRuntime(ctx))
        return;

    JSValue funcObj = JS_NewCFunction2(ctx, ctor, ThisJSClass::JSName(), length, JS_CFUNC_constructor_or_func, 0);

    if (!JS_IsUndefined(target)) {
        JS_DefinePropertyValueStr(ctx, target, ThisJSClass::JSName(), funcObj, JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE);
    }

    JSValue proto = JS_GetClassProto(ctx, classId_);
    for (const auto& [k, val] : functions_) {
        JS_SetPropertyFunctionList(ctx, proto, val, 1);
    }

    JS_AceSetConstructor(ctx, funcObj, proto);
}

template<typename C>
template<typename T>
JSValue QJSKlass<C>::InternalMemberFunctionCallback(
    JSContext* ctx, JSValueConst thisObj, int argc, JSValueConst* argv, int magic)
{
    C* ptr = static_cast<C*>(Unwrap(thisObj));
    T* instance = static_cast<T*>(ptr);
    auto binding = ThisJSClass::GetFunctionBinding(magic);
    LOGD("InternalmemberFunctionCallback: Calling %s::%s", ThisJSClass::JSName(), binding->Name());
    auto fnPtr =
        static_cast<FunctionBinding<T, JSValue, JSContext*, JSValueConst, int, JSValueConst*>*>(binding)->Get();
    return (instance->*fnPtr)(ctx, thisObj, argc, argv);
}

template<typename C>
template<typename Class, typename R, typename... Args>
JSValue QJSKlass<C>::MethodCallback(JSContext* ctx, JSValueConst thisObj, int argc, JSValueConst* argv, int magic)
{
    QJSContext::Scope scp(ctx);
    C* ptr = static_cast<C*>(UnwrapAny(thisObj));
    Class* instance = static_cast<Class*>(ptr);
    auto iBind = ThisJSClass::GetFunctionBinding(magic);
    FunctionBinding<Class, R, Args...>* binding = static_cast<FunctionBinding<Class, R, Args...>*>(iBind);

    LOGD("Calling method %s with %lu arguments", iBind->Name(), sizeof...(Args));
    auto fnPtr = binding->Get();
    auto tuple = __detail__::TupleConverter<std::decay_t<Args>...>()(argv);

    constexpr bool isVoid = std::is_void_v<R>;
    constexpr bool hasArguments = sizeof...(Args) != 0;
    bool returnSelf = binding->Options() & MethodOptions::RETURN_SELF;

    if constexpr (isVoid && hasArguments) {
        // void(Args...)
        FunctionUtils::CallMemberFunction(instance, fnPtr, tuple);
        return returnSelf ? JS_DupValue(ctx, thisObj) : JS_UNDEFINED;
    } else if constexpr (isVoid && !hasArguments) {
        // void()
        (instance->*fnPtr)();
        return returnSelf ? JS_DupValue(ctx, thisObj) : JS_UNDEFINED;
    } else if constexpr (!isVoid && hasArguments) {
        // T(Args...)
        auto result = FunctionUtils::CallMemberFunction(instance, fnPtr, tuple);
        return __detail__::ToJSValue<R>(result);
    } else if constexpr (!isVoid && !hasArguments) {
        // T()
        auto result = (instance->*fnPtr)();
        return __detail__::ToJSValue<R>(result);
    }
}

template<typename C>
template<typename... Args>
JSValue QJSKlass<C>::InternalConstructor(JSContext* ctx, JSValueConst thisObj, int argc, JSValueConst* argv)
{
    QJSContext::Scope scp(ctx);
    if (JS_IsUndefined(thisObj)) {
        return JS_ThrowSyntaxError(ctx, "Constructor of %s called without 'new'!", ThisJSClass::JSName());
    }

    if (argc != sizeof...(Args)) {
        return JS_ThrowSyntaxError(ctx, "Constructing %s requires %lu arguments, %d were provided",
            ThisJSClass::JSName(), static_cast<unsigned long>(sizeof...(Args)), argc);
    }

    JSValue newTargetProto = JS_GetPropertyStr(ctx, thisObj, "prototype");
    JSValue val = JS_NewObjectProtoClass(ctx, newTargetProto, classId_);
    auto tuple = __detail__::TupleConverter<std::decay_t<Args>...>()(argv);
    JS_SetOpaque(val, FunctionUtils::ConstructFromTuple<C>(tuple));
    return val;
}

template<typename C>
JSValue QJSKlass<C>::ConstructorInterceptor(JSContext* ctx, JSValueConst newTarget, int argc, JSValueConst* argv)
{
    if (JS_IsUndefined(newTarget)) {
        return JS_ThrowSyntaxError(ctx, "Constructor of %s called without 'new'!", ThisJSClass::JSName());
    }

    return constructor_(ctx, newTarget, argc, argv);
}

template<typename C>
void QJSKlass<C>::Finalizer(JSRuntime* rt, JSValue val)
{
    if constexpr (has_QjsDestructor<C>) {
        LOGD("Finalizer for %s", ThisJSClass::JSName());
        C* instance = Unwrap(val);
        C::QjsDestructor(rt, instance);
    } else {
        LOGD("No finalizer installed for %s", ThisJSClass::JSName());
    }
}

template<typename C>
void QJSKlass<C>::GcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("GC mark for %s", ThisJSClass::JSName());
    if constexpr (has_QjsGcMark<C>) {
        C::QjsGcMark(rt, val, markFunc);
    }
}

} // namespace OHOS::Ace::Framework
