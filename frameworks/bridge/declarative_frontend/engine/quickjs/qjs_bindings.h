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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_BINDINGS
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_BINDINGS

#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "frameworks/bridge/common/utils/class_utils.h"
#include "frameworks/bridge/common/utils/function_traits.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings_implementation.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_value_conversions.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "third_party/quickjs/cutils.h"
#include "third_party/quickjs/quickjs-libc.h"

void* JS_GetOpaqueA(JSValueConst obj, JSClassID* classIds, size_t classIdLen);

JSValueConst JS_NewGlobalCConstructor(
    JSContext* ctx, const char* name, JSCFunction* func, int length, JSValueConst proto);

#ifdef __cplusplus
}
#endif

// FIXME(cvetan) Move to appropriate file and if possibly consolidate this with V8 conversions
namespace __detail__ {

template<typename T>
struct IsSignedInt {
    static constexpr bool value =
        std::is_integral<T>::value && std::is_signed<T>::value && !std::is_same<T, bool>::value;
};

template<typename T>
static constexpr bool is_signed_int_v = IsSignedInt<T>::value;

template<typename T>
T FromJSValue(JSValueConst val)
{
    static_assert(!std::is_const_v<T> && !std::is_reference_v<T>, //
        "Cannot convert values to reference or cv-qualified types!");

    JSContext* ctx = OHOS::Ace::Framework::QJSContext::current();
    if constexpr (is_signed_int_v<T>) {
        int64_t res;
        JS_ToInt64(ctx, &res, val);
        return res;
    } else if constexpr (std::is_unsigned_v<T>) {
        uint32_t res;
        JS_ToUint32(ctx, &res, val);
        return res;
    } else if constexpr (std::is_floating_point_v<T>) {
        double res;
        JS_ToFloat64(ctx, &res, val);
        return res;
    } else if constexpr (std::is_same_v<T, std::string>) {
        OHOS::Ace::Framework::ScopedString str(val);
        return str.str();
    }

    return T();
}

template<typename T>
JSValue ToJSValue(T val)
{
    JSContext* ctx = OHOS::Ace::Framework::QJSContext::current();
    if constexpr (is_signed_int_v<T>) {
        return JS_NewInt64(ctx, val);
    } else if constexpr (std::is_unsigned_v<T>) {
        return JS_NewInt64(ctx, val);
    } else if constexpr (std::is_floating_point_v<T>) {
        return JS_NewFloat64(ctx, val);
    } else if constexpr (std::is_same_v<T, std::string>) {
        return JS_NewStringLen(ctx, val.c_str(), val.size());
    } else if constexpr (std::is_same_v<T, const char*>) {
        return JS_NewStringLen(ctx, val, strlen(val));
    }

    return JS_ThrowInternalError(ctx, "Conversion failure...");
}

template<typename... Types>
struct TupleConverter {
    std::tuple<Types...> operator()(JSValueConst* argv)
    {
        int index = 0;
        return {
            __detail__::FromJSValue<Types>(argv[index++])...,
        };
    }
};

}; // namespace __detail__

namespace OHOS::Ace::Framework {

extern std::vector<JSClassID> g_classIds;

void* UnwrapAny(JSValueConst val);

template<typename T>
JSValue Wrap(JSValueConst newTarget, T* thisPtr);

template<typename T>
JSValue Wrap(T* thisPtr);

template<typename T>
T* Unwrap(JSValueConst val);

template<typename C>
class QJSKlass {
    using ThisJSClass = JSClassImpl<C, QJSKlass>;

public:
    QJSKlass() = delete;

    static void Declare(const char* name);

    template<typename R, typename... Args>
    static void Method(const char* name, R (C::*func)(Args...), int id);

    template<typename Base, typename R, typename... Args>
    static void Method(const char* name, R (Base::*func)(Args...), int id);

    static void CustomMethod(const char* name, FunctionCallback cb);

    template<typename T>
    static void CustomMethod(const char* name, MemberFunctionCallback<T> cb, int id);

    static void ExoticGetter(ExoticGetterCallback callback);
    static void ExoticSetter(ExoticSetterCallback callback);
    static void ExoticHasProperty(ExoticHasPropertyCallback callback);
    static void ExoticIsArray(ExoticIsArrayCallback callback);

    template<typename... Args>
    static void Bind(BindingTarget target);

    static void Bind(BindingTarget target, FunctionCallback ctor);

    template<typename Base>
    static void Inherit();

    static C* Unwrap(JSValueConst val);

    static JSValue NewObjectProtoClass(JSValue proto);

    static JSValue NewInstance();
    static JSValue GetProto();

    static int NumberOfInstances();

private:
    // TODO(cvetan) DEPRECATE
    DEFINE_HAS_METHOD(QjsDestructor)
    // TODO(cvetan) DEPRECATE
    DEFINE_HAS_METHOD(QjsGcMark)

    static void BindInternal(BindingTarget target, FunctionCallback ctor, size_t length);

    template<typename T>
    static JSValue InternalMemberFunctionCallback(
        JSContext* ctx, JSValueConst thisObj, int argc, JSValueConst* argv, int magic);

    template<typename Class, typename R, typename... Args>
    static JSValue MethodCallback(JSContext* ctx, JSValueConst thisObj, int argc, JSValueConst* argv, int magic);

    template<typename... Args>
    static JSValue InternalConstructor(JSContext* ctx, JSValueConst thisObj, int argc, JSValueConst* argv);

    static JSValue ConstructorInterceptor(JSContext* ctx, JSValueConst thisObj, int argc, JSValueConst* argv);

    static void Finalizer(JSRuntime* rt, JSValue val);
    static void GcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);

    static JSValue proto_;
    static std::unordered_map<std::string, JSCFunctionListEntry*> functions_;
    static JSClassID classId_;
    static JSClassExoticMethods exoticMethods_;
    static JSClassDef classDefinitions_;
    static FunctionCallback constructor_;

    template<typename U>
    friend class QJSKlass;
}; // namespace OHOS::Ace::Framework

template<typename T>
using JSClass = JSClassImpl<T, QJSKlass>;

} // namespace OHOS::Ace::Framework

#include "qjs_bindings.inl"

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_BINDINGS
