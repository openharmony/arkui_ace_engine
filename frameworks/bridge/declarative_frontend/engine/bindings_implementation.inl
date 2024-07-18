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

#include "bindings_implementation.h"

namespace OHOS::Ace::Framework {

template<typename T, template<typename> typename ImplDetail>
thread_local std::string JSClassImpl<T, ImplDetail>::jsName;

template<typename C, template<typename> typename ImplDetail>
void JSClassImpl<C, ImplDetail>::Declare(const char* name)
{
    jsName = name;
    ImplDetail<C>::Declare(name);
}

template<typename C, template<typename> typename ImplDetail>
template<typename Base, typename R, typename... Args>
void JSClassImpl<C, ImplDetail>::Method(const char* name, R (Base::*func)(Args...), MethodOptions options)
{
    static_assert(std::is_base_of_v<Base, C>, "Trying to bind an unrelated method!");
    ImplDetail<C>::Method(name, new FunctionBinding(name, options, func));
}

template<typename C, template<typename> typename ImplDetail>
template<typename R, typename... Args>
void JSClassImpl<C, ImplDetail>::StaticMethod(const char* name, R (*func)(Args...), MethodOptions options)
{
    ImplDetail<C>::StaticMethod(name, new StaticFunctionBinding(name, options, func));
}

template<typename C, template<typename> typename ImplDetail>
void JSClassImpl<C, ImplDetail>::StaticMethod(const char* name, JSFunctionCallback func)
{
    ImplDetail<C>::StaticMethod(name, new StaticFunctionBinding(name, MethodOptions::NONE, func));
}

template<typename C, template<typename> typename ImplDetail>
template<typename T>
void JSClassImpl<C, ImplDetail>::CustomMethod(const char* name, MemberFunctionCallback<T> callback)
{
    static_assert(std::is_base_of_v<T, C>, "Trying to bind an unrelated method!");
    ImplDetail<C>::CustomMethod(name, new FunctionBinding(name, MethodOptions::NONE, callback));
}

template<typename C, template<typename> typename ImplDetail>
void JSClassImpl<C, ImplDetail>::CustomMethod(const char* name, FunctionCallback callback)
{
    ImplDetail<C>::CustomMethod(name, callback);
}

template<typename C, template<typename> typename ImplDetail>
template<typename T>
void JSClassImpl<C, ImplDetail>::CustomMethod(const char* name, JSMemberFunctionCallback<T> callback)
{
    ImplDetail<C>::CustomMethod(name, new FunctionBinding(name, MethodOptions::NONE, callback));
}

template<typename C, template<typename> typename ImplDetail>
template<typename T>
void JSClassImpl<C, ImplDetail>::CustomProperty(
    const char* name, MemberFunctionGetCallback<T> getter, MemberFunctionSetCallback<T> setter)
{
    static_assert(std::is_base_of_v<T, C>, "Trying to bind an unrelated method!");
    ImplDetail<C>::CustomProperty(name, new FunctionBinding(name, MethodOptions::NONE, getter),
        new FunctionBinding(name, MethodOptions::NONE, setter));
}

template<typename C, template<typename> typename ImplDetail>
void JSClassImpl<C, ImplDetail>::CustomProperty(
    const char* name, FunctionGetCallback getter, FunctionSetCallback setter)
{
    ImplDetail<C>::CustomProperty(name, getter, setter);
}

template<typename C, template<typename> typename ImplDetail>
template<typename T>
void JSClassImpl<C, ImplDetail>::CustomProperty(
    const char* name, JSMemberFunctionCallback<T> getter, JSMemberFunctionCallback<T> setter)
{
    ImplDetail<C>::CustomProperty(name, new FunctionBinding(name, MethodOptions::NONE, getter),
        new FunctionBinding(name, MethodOptions::NONE, setter));
}

template<typename C, template<typename> typename ImplDetail>
void JSClassImpl<C, ImplDetail>::CustomStaticMethod(const char* name, FunctionCallback callback)
{
    ImplDetail<C>::CustomStaticMethod(name, callback);
}

template<typename C, template<typename> typename ImplDetail>
void JSClassImpl<C, ImplDetail>::ExoticGetter(ExoticGetterCallback callback)
{
    ImplDetail<C>::ExoticGetter(callback);
}

template<typename C, template<typename> typename ImplDetail>
void JSClassImpl<C, ImplDetail>::ExoticSetter(ExoticSetterCallback callback)
{
    ImplDetail<C>::ExoticSetter(callback);
}

template<typename C, template<typename> typename ImplDetail>
void JSClassImpl<C, ImplDetail>::ExoticHasProperty(ExoticHasPropertyCallback callback)
{
    ImplDetail<C>::ExoticHasProperty(callback);
}

template<typename C, template<typename> typename ImplDetail>
template<typename T>
void JSClassImpl<C, ImplDetail>::StaticConstant(const char* name, T value)
{
    ImplDetail<C>::StaticConstant(name, value);
}

template<typename C, template<typename> typename ImplDetail>
void JSClassImpl<C, ImplDetail>::Bind(BindingTarget bindTarget, FunctionCallback ctor)
{
    ImplDetail<C>::Bind(bindTarget, ctor);
}

template<typename C, template<typename> typename ImplDetail>
void JSClassImpl<C, ImplDetail>::Bind(
    BindingTarget bindTarget, JSFunctionCallback ctor, JSDestructorCallback<C> dtor, JSGCMarkCallback<C> gcMark)
{
    ImplDetail<C>::Bind(bindTarget, ctor, dtor, gcMark);
}

template<typename C, template<typename> typename ImplDetail>
template<typename... Args>
void JSClassImpl<C, ImplDetail>::Bind(
    BindingTarget bindTarget, JSDestructorCallback<C> dtor, JSGCMarkCallback<C> gcMark)
{
    ImplDetail<C>::template Bind<Args...>(bindTarget, dtor, gcMark);
}

template<typename C, template<typename> typename ImplDetail>
template<typename Base>
void JSClassImpl<C, ImplDetail>::Inherit()
{
    static_assert(std::is_base_of_v<Base, C>, "Calling Inherit() on unrelated classes!");
    ImplDetail<C>::template Inherit<Base>();
}

template<typename C, template<typename> typename ImplDetail>
template<typename Base>
void JSClassImpl<C, ImplDetail>::InheritAndBind(
    BindingTarget bindTarget, JSFunctionCallback ctor, JSDestructorCallback<C> dtor, JSGCMarkCallback<C> gcMark)
{
    static_assert(std::is_base_of_v<Base, C>, "Calling Inherit() on unrelated classes!");
    ImplDetail<C>::template InheritAndBind<Base>(bindTarget, ctor, dtor, gcMark);
}

template<typename C, template<typename> typename ImplDetail>
const char* JSClassImpl<C, ImplDetail>::JSName()
{
    return jsName.c_str();
}

template<typename C, template<typename> typename ImplDetail>
JSRef<JSObject> JSClassImpl<C, ImplDetail>::NewInstance()
{
    return JSRef<JSObject>::Make(ImplDetail<C>::NewInstance());
}

}; // namespace OHOS::Ace::Framework
