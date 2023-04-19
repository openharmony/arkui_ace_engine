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

enum class JavascriptEngine { NONE, ARK };

#ifdef USE_ARK_ENGINE

#include "ecmascript/napi/include/jsnapi.h"

using BindingTarget = panda::Local<panda::ObjectRef>;
using FunctionCallback = panda::Local<panda::JSValueRef>(*)(panda::JsiRuntimeCallInfo*);
using FunctionGetCallback = panda::Local<panda::JSValueRef>(*)(panda::JsiRuntimeCallInfo*);
using FunctionSetCallback = panda::Local<panda::JSValueRef>(*)(panda::JsiRuntimeCallInfo*);
template<typename T>
using MemberFunctionCallback = panda::Local<panda::JSValueRef>(T::*)(panda::JsiRuntimeCallInfo*);
template<typename T>
using MemberFunctionGetCallback = panda::Local<panda::JSValueRef>(T::*)(panda::JsiRuntimeCallInfo*);
template<typename T>
using MemberFunctionSetCallback = panda::Local<panda::JSValueRef>(T::*)(panda::JsiRuntimeCallInfo*);
using ExoticGetterCallback = int;
using ExoticSetterCallback = int;
using ExoticHasPropertyCallback = int;
using ExoticIsArrayCallback = int;

constexpr const JavascriptEngine cCurrentJSEngine = JavascriptEngine::ARK;

#else
#error "No engine selected"
#endif

using JSFunctionCallback = void (*)(const OHOS::Ace::Framework::JSCallbackInfo&);
template<typename T>
using JSMemberFunctionCallback = void (T::*)(const OHOS::Ace::Framework::JSCallbackInfo&);
template<typename T>
using JSDestructorCallback = void (*)(T* instance);
template<typename T>
using JSGCMarkCallback = void (*)(T* instance, const OHOS::Ace::Framework::JSGCMarkCallbackInfo&);

#endif
