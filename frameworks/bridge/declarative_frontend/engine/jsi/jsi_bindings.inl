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

#include <string>

#include "ecmascript/napi/include/jsnapi.h"

namespace OHOS::Ace::Framework {
template<typename C>
std::unordered_map<std::string, panda::Global<panda::FunctionRef>> JsiClass<C>::staticFunctions_;

template<typename C>
std::unordered_map<std::string, panda::Global<panda::FunctionRef>> JsiClass<C>::customFunctions_;

template<typename C>
FunctionCallback JsiClass<C>::constructor_ = nullptr;

template<typename C>
JSFunctionCallback JsiClass<C>::jsConstructor_ = nullptr;

template<typename C>
JSDestructorCallback<C> JsiClass<C>::jsDestructor_ = nullptr;

template<typename C>
JSGCMarkCallback<C> JsiClass<C>::jsGcMark_ = nullptr;

template<typename C>
std::string JsiClass<C>::className_;

template<typename C>
panda::Global<panda::FunctionRef> JsiClass<C>::classFunction_;

template<typename C>
void JsiClass<C>::Declare(const char* name)
{
    className_ = name;
    staticFunctions_.clear();
    customFunctions_.clear();
    classFunction_.Empty();
}

template<typename C>
template<typename Base, typename R, typename... Args>
void JsiClass<C>::Method(const char* name, R (Base::*func)(Args...), int id)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    auto funcId = std::make_shared<int32_t>(id);
    customFunctions_.emplace(name, panda::Global<panda::FunctionRef>(vm, panda::FunctionRef::New(vm,
        MethodCallback<Base, R, Args...>, funcId.get())));
}

template<typename C>
template<typename T>
void JsiClass<C>::CustomMethod(const char* name, MemberFunctionCallback<T> callback, int id)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    auto funcId = std::make_shared<int32_t>(id);
    customFunctions_.emplace(
        name, panda::Global<panda::FunctionRef>(vm, panda::FunctionRef::New(vm,
        InternalMemberFunctionCallback<T, panda::EcmaVM*, panda::Local<panda::JSValueRef>,
        const panda::Local<panda::JSValueRef>[], int32_t, void*>,
        funcId.get())));
}

template<typename C>
void JsiClass<C>::CustomMethod(const char* name, FunctionCallback callback)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    customFunctions_.emplace(
        name, panda::Global<panda::FunctionRef>(vm, panda::FunctionRef::New(vm, callback, nullptr)));
}

template<typename C>
template<typename T>
void JsiClass<C>::CustomMethod(const char* name, JSMemberFunctionCallback<T> callback, int id)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    auto funcId = std::make_shared<int32_t>(id);
    customFunctions_.emplace(name, panda::Global<panda::FunctionRef>(vm, panda::FunctionRef::New(vm,
        InternalJSMemberFunctionCallback<T>, funcId.get())));
}

template<typename C>
template<typename R, typename... Args>
void JsiClass<C>::StaticMethod(const char* name, R (*func)(Args...), int id)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    auto funcId = std::make_shared<int32_t>(id);
    staticFunctions_.emplace(name, panda::Global<panda::FunctionRef>(vm, panda::FunctionRef::New(vm,
        StaticMethodCallback<R, Args...>, funcId.get())));
}

template<typename C>
void JsiClass<C>::StaticMethod(const char* name, JSFunctionCallback func, int id)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    auto funcId = std::make_shared<int32_t>(id);
    staticFunctions_.emplace(name, panda::Global<panda::FunctionRef>(vm, panda::FunctionRef::New(vm,
        JSStaticMethodCallback, funcId.get())));
}

template<typename C>
void JsiClass<C>::CustomStaticMethod(const char* name, FunctionCallback callback)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    staticFunctions_.emplace(
        name, panda::Global<panda::FunctionRef>(vm, panda::FunctionRef::New(vm, callback, nullptr)));
}

template<typename C>
template<typename T>
void JsiClass<C>::StaticConstant(const char* name, T val)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    panda::Local<panda::JSValueRef> key = panda::StringRef::NewFromUtf8(vm, name);
    classFunction_->Set(vm, key, JsiValueConvertor::toJsiValue<std::string>(val));
}

template<typename C>
void JsiClass<C>::Bind(BindingTarget t, FunctionCallback ctor)
{
    constructor_ = ctor;
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    classFunction_ = panda::Global<panda::FunctionRef>(
        vm, panda::FunctionRef::NewClassFunction(vm, ConstructorInterceptor, nullptr, nullptr));
    classFunction_->SetName(vm, StringRef::NewFromUtf8(vm, className_.c_str()));
    auto prototype = Local<ObjectRef>(classFunction_->GetFunctionPrototype(vm));
    for (const auto& [name, val] : staticFunctions_) {
        classFunction_->Set(vm, panda::StringRef::NewFromUtf8(vm, name.c_str()), val.ToLocal(vm));
    }
    for (const auto& [name, val] : customFunctions_) {
        prototype->Set(vm, panda::StringRef::NewFromUtf8(vm, name.c_str()), val.ToLocal(vm));
    }
    t->Set(vm, panda::StringRef::NewFromUtf8(vm, ThisJSClass::JSName()), classFunction_);
}

template<typename C>
void JsiClass<C>::Bind(
    BindingTarget t, JSFunctionCallback ctor, JSDestructorCallback<C> dtor, JSGCMarkCallback<C> gcMark)
{
    jsConstructor_ = ctor;
    jsDestructor_ = dtor;
    jsGcMark_ = gcMark;
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    classFunction_ = panda::Global<panda::FunctionRef>(
        vm, panda::FunctionRef::NewClassFunction(vm, JSConstructorInterceptor, nullptr, nullptr));
    classFunction_->SetName(vm, StringRef::NewFromUtf8(vm, className_.c_str()));
    auto prototype = panda::Local<panda::ObjectRef>(classFunction_->GetFunctionPrototype(vm));
    for (const auto& [name, val] : staticFunctions_) {
        classFunction_->Set(vm, panda::StringRef::NewFromUtf8(vm, name.c_str()), val.ToLocal(vm));
    }
    for (const auto& [name, val] : customFunctions_) {
        prototype->Set(vm, panda::StringRef::NewFromUtf8(vm, name.c_str()), val.ToLocal(vm));
    }
    t->Set(vm, panda::Local<panda::JSValueRef>(panda::StringRef::NewFromUtf8(vm, ThisJSClass::JSName())),
        panda::Local<panda::JSValueRef>(classFunction_.ToLocal(vm)));
}

template<typename C>
template<typename... Args>
void JsiClass<C>::Bind(BindingTarget t, JSDestructorCallback<C> dtor, JSGCMarkCallback<C> gcMark)
{
    jsDestructor_ = dtor;
    jsGcMark_ = gcMark;
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    classFunction_ = panda::Global<panda::FunctionRef>(
        vm, panda::FunctionRef::NewClassFunction(vm, InternalConstructor<Args...>, nullptr, nullptr));
    classFunction_->SetName(vm, StringRef::NewFromUtf8(vm, className_.c_str()));
    auto prototype = panda::Local<panda::ObjectRef>(classFunction_->GetFunctionPrototype(vm));
    for (const auto& [name, val] : staticFunctions_) {
        classFunction_->Set(vm, panda::StringRef::NewFromUtf8(vm, name.c_str()), val.ToLocal(vm));
    }
    for (const auto& [name, val] : customFunctions_) {
        prototype->Set(vm, panda::StringRef::NewFromUtf8(vm, name.c_str()), val.ToLocal(vm));
    }
    t->Set(vm, panda::Local<panda::JSValueRef>(panda::StringRef::NewFromUtf8(vm, ThisJSClass::JSName())),
        panda::Local<panda::JSValueRef>(classFunction_.ToLocal(vm)));
}

template<typename C>
template<typename Base>
void JsiClass<C>::Inherit()
{
    auto& staticFunctions = GetStaticFunctions();
    for (auto& [name, function] : staticFunctions) {
        if (staticFunctions_.find(name) != staticFunctions_.end()) {
            continue;
        }
        staticFunctions_.emplace(name, function);
    }
    auto& customFunctions_ = GetCustomFunctions();
    for (auto& [name, function] : customFunctions_) {
        if (customFunctions_.find(name) != customFunctions_.end()) {
            continue;
        }
        customFunctions_.emplace(name, function);
    }
}

template<typename C>
std::unordered_map<std::string, panda::Global<panda::FunctionRef>>& JsiClass<C>::GetStaticFunctions()
{
    return staticFunctions_;
}

template<typename C>
std::unordered_map<std::string, panda::Global<panda::FunctionRef>>& JsiClass<C>::GetCustomFunctions()
{
    return customFunctions_;
}

template<typename C>
template<typename T, typename... Args>
panda::Local<panda::JSValueRef> JsiClass<C>::InternalMemberFunctionCallback(panda::EcmaVM* vm,
    panda::Local<panda::JSValueRef> thisObj, const panda::Local<panda::JSValueRef> argv[], int32_t argc, void* data)
{
    C* ptr = static_cast<C*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(0));
    T* instance = static_cast<T*>(ptr);
    int index = *(static_cast<int*>(data));
    auto binding = ThisJSClass::GetFunctionBinding(index);
    LOGD("InternalMemberFunctionCallback: Calling %{public}s::%{public}s", ThisJSClass::JSName(), binding->Name());
    auto fnPtr = static_cast<FunctionBinding<T, panda::Local<panda::JSValueRef>, Args...>*>(binding)->Get();
    (instance->*fnPtr)(vm, thisObj, argv, argc, data);
}

template<typename C>
template<typename T>
panda::Local<panda::JSValueRef> JsiClass<C>::InternalJSMemberFunctionCallback(panda::EcmaVM* vm,
    panda::Local<panda::JSValueRef> thisObj, const panda::Local<panda::JSValueRef> argv[], int32_t argc, void* data)
{
    C* ptr = static_cast<C*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(0));
    T* instance = static_cast<T*>(ptr);
    int index = *(static_cast<int*>(data));
    auto binding = ThisJSClass::GetFunctionBinding(index);
    LOGD("InternalmemberFunctionCallback: Calling %s::%s", ThisJSClass::JSName(), binding->Name());

    auto fnPtr = static_cast<FunctionBinding<T, void, const JSCallbackInfo&>*>(binding)->Get();
    JsiCallbackInfo info(vm, thisObj, argc, argv);
    (instance->*fnPtr)(info);

    std::variant<void*, panda::Global<panda::JSValueRef>> retVal = info.GetReturnValue();
    auto jsVal = std::get_if<panda::Global<panda::JSValueRef>>(&retVal);
    if (jsVal) {
        return jsVal->ToLocal(vm);
    }
    return panda::Local<panda::JSValueRef>(panda::JSValueRef::Undefined(vm));
}

template<typename C>
template<typename Class, typename R, typename... Args>
panda::Local<panda::JSValueRef> JsiClass<C>::MethodCallback(EcmaVM* vm, panda::Local<panda::JSValueRef> thisObj,
    const panda::Local<panda::JSValueRef> argv[], int32_t argc, void* data)
{
    C* ptr = static_cast<C*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(0));
    Class* instance = static_cast<Class*>(ptr);
    int index = *(static_cast<int*>(data));
    auto binding = ThisJSClass::GetFunctionBinding(index);
    LOGD("Calling %{public}s::%{public}s", ThisJSClass::JSName(), binding->Name());
    bool strictTypeCheck = binding->Options() & MethodOptions::STRICT_TYPE_CHECK;
    if (strictTypeCheck) {
    }
    auto fnPtr = static_cast<FunctionBinding<Class, R, Args...>*>(binding)->Get();
    auto tuple = __detail__::ToTuple<std::decay_t<Args>...>(argv);
    bool returnSelf = binding->Options() & MethodOptions::RETURN_SELF;
    constexpr bool isVoid = std::is_void_v<R>;
    constexpr bool hasArguments = sizeof...(Args) != 0;

    if constexpr (isVoid && hasArguments) {
        // C::MemberFunction(Args...)
        FunctionUtils::CallMemberFunction(instance, fnPtr, tuple);
        return returnSelf ? thisObj : panda::Local<panda::JSValueRef>(panda::JSValueRef::Undefined(vm));
    } else if constexpr (isVoid && !hasArguments) {
        // C::MemberFunction()
        (instance->*fnPtr)();
        return returnSelf ? thisObj : panda::Local<panda::JSValueRef>(panda::JSValueRef::Undefined(vm));
    } else if constexpr (!isVoid && hasArguments) {
        // R C::MemberFunction(Args...)
        auto result = FunctionUtils::CallMemberFunction(instance, fnPtr, tuple);
        return JsiValueConvertor::toJsiValue<R>(result);
    } else if constexpr (!isVoid && !hasArguments) {
        // R C::MemberFunction()
        auto res = (instance->*fnPtr)();
        return JsiValueConvertor::toJsiValue<R>(res);
    }
}

template<typename C>
template<typename Class, typename R, typename... Args>
panda::Local<panda::JSValueRef> JsiClass<C>::JSMethodCallback(panda::EcmaVM* vm,
    panda::Local<panda::JSValueRef> thisObj, const panda::Local<panda::JSValueRef> argv[], int32_t argc, void* data)
{
    C* ptr = static_cast<C*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(0));
    Class* instance = static_cast<Class*>(ptr);
    int index = *(static_cast<int*>(data));
    auto binding = ThisJSClass::GetFunctionBinding(index);
    LOGD("Calling %{public}s::%{public}s", ThisJSClass::JSName(), binding->Name());
    bool strictTypeCheck = binding->Options() & MethodOptions::STRICT_TYPE_CHECK;
    if (strictTypeCheck) {
    }
    JsiCallbackInfo info(vm, thisObj, argc, argv);
    auto fnPtr = static_cast<FunctionBinding<Class, R, Args...>*>(binding)->Get();
    (instance->*fnPtr)(info);
}

template<typename C>
template<typename R, typename... Args>
panda::Local<panda::JSValueRef> JsiClass<C>::StaticMethodCallback(panda::EcmaVM* vm,
    panda::Local<panda::JSValueRef> thisObj, const panda::Local<panda::JSValueRef> argv[], int32_t argc, void* data)
{
    int index = *(static_cast<int*>(data));
    auto binding = ThisJSClass::GetFunctionBinding(index);
    LOGD("Calling %{public}s::%{public}s", ThisJSClass::JSName(), binding->Name());
    bool strictTypeCheck = binding->Options() & MethodOptions::STRICT_TYPE_CHECK;
    if (strictTypeCheck) {
    }
    auto fnPtr = static_cast<StaticFunctionBinding<R, Args...>*>(binding)->Get();
    auto tuple = __detail__::ToTuple<std::decay_t<Args>...>(argv);
    bool returnSelf = binding->Options() & MethodOptions::RETURN_SELF;
    constexpr bool isVoid = std::is_void_v<R>;
    constexpr bool hasArguments = sizeof...(Args) != 0;

    if constexpr (isVoid && hasArguments) {
        // void C::MemberFunction(Args...)
        FunctionUtils::CallStaticMemberFunction(fnPtr, tuple);
        return returnSelf ? thisObj : panda::Local<panda::JSValueRef>(panda::JSValueRef::Undefined(vm));
    } else if constexpr (isVoid && !hasArguments) {
        // void C::MemberFunction()
        fnPtr();
        return panda::JSValueRef::Undefined(vm);
    } else if constexpr (!isVoid && hasArguments) {
        // R C::MemberFunction(Args...)
        auto result = FunctionUtils::CallStaticMemberFunction(fnPtr, tuple);
        return JsiValueConvertor::toJsiValue(result);
    } else if constexpr (!isVoid && !hasArguments) {
        // R C::MemberFunction()
        auto res = fnPtr();
        return JsiValueConvertor::toJsiValue(res);
    }
}

template<typename C>
panda::Local<panda::JSValueRef> JsiClass<C>::JSStaticMethodCallback(panda::EcmaVM* vm,
    panda::Local<panda::JSValueRef> thisObj, const panda::Local<panda::JSValueRef> argv[], int32_t argc, void* data)
{
    int index = *(static_cast<int*>(data));
    auto binding = ThisJSClass::GetFunctionBinding(index);
    LOGD("Calling %{public}s::%{public}s", ThisJSClass::JSName(), binding->Name());
    auto fnPtr = static_cast<StaticFunctionBinding<void, const JSCallbackInfo&>*>(binding)->Get();
    JsiCallbackInfo info(vm, thisObj, argc, argv);
    fnPtr(info);
    return panda::Local<panda::JSValueRef>(panda::JSValueRef::Undefined(vm));
}

template<typename C>
template<typename... Args>
panda::Local<panda::JSValueRef> JsiClass<C>::InternalConstructor(panda::EcmaVM* vm,
    panda::Local<panda::JSValueRef> thisObj, panda::Local<JSValueRef> newTarget,
    const panda::Local<panda::JSValueRef> argv[], int32_t argc, void* data)
{
    if (!newTarget->IsFunction()) {
        return panda::Local<panda::JSValueRef>(panda::JSValueRef::Undefined(vm));
    }

    JsiCallbackInfo info(vm, thisObj, argc, argv);
    auto tuple = __detail__::ToTuple<std::decay_t<Args>...>(argv);
    C* instance = FunctionUtils::ConstructFromTuple<C>(tuple);
    panda::Local<panda::ObjectRef>(thisObj)->SetNativePointerField(0, static_cast<void*>(instance));
    return panda::Local<panda::JSValueRef>(panda::JSValueRef::Undefined(vm));
}

template<typename C>
bool JsiClass<C>::CheckIfConstructCall(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> thisObj,
    panda::Local<panda::JSValueRef> newTarget, const panda::Local<panda::JSValueRef> argv[], int32_t argc, void* data)
{
    return true;
}

template<typename C>
panda::Local<panda::JSValueRef> JsiClass<C>::ConstructorInterceptor(panda::EcmaVM* vm,
    panda::Local<panda::JSValueRef> thisObj, panda::Local<panda::JSValueRef> newTarget,
    const panda::Local<panda::JSValueRef> argv[], int32_t argc, void* data)
{
    if (!newTarget->IsFunction()) {
        return panda::Local<panda::JSValueRef>(panda::JSValueRef::Undefined(vm));
    }

    return constructor_(vm, thisObj, argv, argc, data);
}

template<typename C>
panda::Local<panda::JSValueRef> JsiClass<C>::JSConstructorInterceptor(panda::EcmaVM* vm,
    panda::Local<panda::JSValueRef> thisObj, panda::Local<panda::JSValueRef> newTarget,
    const panda::Local<panda::JSValueRef> argv[], int32_t argc, void* data)
{
    if (newTarget->IsFunction()) {
        JsiCallbackInfo info(vm, thisObj, argc, argv);
        jsConstructor_(info);
        auto retVal = info.GetReturnValue();
        if (retVal.valueless_by_exception()) {
            LOGE("Constructor of %s must return a value!", ThisJSClass::JSName());
            return panda::Local<panda::JSValueRef>(panda::JSValueRef::Undefined(vm));
        }
        auto instance = std::get_if<void*>(&retVal);
        if (instance) {
            Local<ObjectRef>(thisObj)->SetNativePointerFieldCount(1);
            Local<ObjectRef>(thisObj)->SetNativePointerField(0, *instance);
            LOGD("Constructed %s", ThisJSClass::JSName());
            return thisObj;
        }
    }
    return panda::Local<panda::JSValueRef>(panda::JSValueRef::Undefined(vm));
}

template<typename C>
panda::Local<panda::JSValueRef> JsiClass<C>::NewInstance()
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetJsRuntime());
    auto vm = runtime->GetEcmaVm();
    return classFunction_->Constructor(vm, nullptr, 0);
}
} // namespace OHOS::Ace::Framework
