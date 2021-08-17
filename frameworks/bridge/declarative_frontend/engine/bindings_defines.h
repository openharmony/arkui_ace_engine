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

#include "frameworks/bridge/declarative_frontend/engine/js_types.h"

enum class JavascriptEngine { NONE, QUICKJS };

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

using JSFunctionCallback = void (*)(const OHOS::Ace::Framework::JSCallbackInfo&);
template<typename T>
using JSMemberFunctionCallback = void (T::*)(const OHOS::Ace::Framework::JSCallbackInfo&);
template<typename T>
using JSDestructorCallback = void (*)(T* instance);
template<typename T>
using JSGCMarkCallback = void (*)(T* instance, const OHOS::Ace::Framework::JSGCMarkCallbackInfo&);

#endif
