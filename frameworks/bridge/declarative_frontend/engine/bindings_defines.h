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

#ifndef FOUNDATION_ACE_FRAMEWORKS_DECLARATIVE_FRONTEND_ENGINE_BINDINGS_DEFINES_H
#define FOUNDATION_ACE_FRAMEWORKS_DECLARATIVE_FRONTEND_ENGINE_BINDINGS_DEFINES_H

enum class JavascriptEngine { NONE, QUICKJS, V8 };

#ifdef USE_QUICKJS_ENGINE

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

using BindingTarget = JSValue;
using FunctionCallback = JSValue (*)(JSContext*, JSValueConst, int, JSValueConst*);
template<typename T>
using MemberFunctionCallback = JSValue (T::*)(JSContext*, JSValueConst, int, JSValueConst*);
using ExoticGetterCallback = JSValue (*)(JSContext* ctx, JSValueConst obj, JSAtom atom, JSValueConst receiver);
using ExoticSetterCallback = int (*)(
    JSContext* ctx, JSValueConst obj, JSAtom atom, JSValueConst value, JSValueConst receiver, int flags);
using ExoticHasPropertyCallback = int (*)(JSContext* ctx, JSValueConst obj, JSAtom atom);
using ExoticIsArrayCallback = int (*)(JSContext* ctx, JSValueConst obj);

/* return < 0 if exception or TRUE/FALSE */

constexpr const JavascriptEngine cCurrentJSEngine = JavascriptEngine::QUICKJS;

#elif USE_V8_ENGINE

#include "third_party/v8/include/v8.h"

using BindingTarget = v8::Local<v8::ObjectTemplate>;
using FunctionCallback = void (*)(const v8::FunctionCallbackInfo<v8::Value>&);
template<typename T>
using MemberFunctionCallback = void (T::*)(const v8::FunctionCallbackInfo<v8::Value>&);
using ExoticGetterCallback = int;
using ExoticSetterCallback = int;
using ExoticHasPropertyCallback = int;
using ExoticIsArrayCallback = int;

constexpr const JavascriptEngine cCurrentJSEngine = JavascriptEngine::V8;

#else
#error "No engine selected"
#endif

#endif
