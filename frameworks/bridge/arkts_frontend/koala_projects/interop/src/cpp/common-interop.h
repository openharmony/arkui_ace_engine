/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COMMON_INTEROP_BASE_H
#define COMMON_INTEROP_BASE_H

#include <vector>

#include "koala-types.h"

#define KOALA_INTEROP_PROFILER 0
#define KOALA_INTEROP_TRACER 0

#if KOALA_INTEROP_PROFILER
#include "profiler.h"
#define KOALA_INTEROP_LOGGER(name) InteropMethodCall logger(#name);
#endif

#if KOALA_INTEROP_TRACER
#include "tracer.h"
#define KOALA_INTEROP_LOGGER(name) InteropMethodCall logger(#name);
#endif


#ifdef KOALA_INTEROP_LOGGER
#define KOALA_MAYBE_LOG(name) KOALA_INTEROP_LOGGER(name);
#else
#define KOALA_MAYBE_LOG(name)
#endif

typedef void (*Callback_Caller_t)(KInt callbackKind, KSerializerBuffer argsData, KInt argsLength);
typedef void (*Callback_Caller_Sync_t)(KVMContext vmContext, KInt callbackKind, KSerializerBuffer argsData, KInt argsLength);
void setCallbackCaller(Callback_Caller_t caller);
void setCallbackCallerSync(Callback_Caller_Sync_t callerSync);

KVMDeferred* CreateDeferred(KVMContext context, KVMObjectHandle* promise);
const InteropAsyncWorker* GetAsyncWorker();

std::vector<KStringPtr> makeStringVector(KStringArray strArray);
std::vector<KStringPtr> makeStringVector(KNativePointerArray arr, KInt size);

#if KOALA_USE_NODE_VM || KOALA_USE_HZ_VM
#include "convertors-napi.h"
#elif KOALA_USE_JSC_VM
#include "convertors-jsc.h"
#elif KOALA_ETS_NAPI
#include "convertors-ets.h"
#elif KOALA_USE_JAVA_VM
#include "convertors-jni.h"
#elif KOALA_WASM
#include "convertors-wasm.h"
#elif KOALA_CJ
#include "convertors-cj.h"
#elif KOALA_ANI
#include "convertors-ani.h"
#else
#error "One of above branches must be taken"
#endif

#endif // COMMON_INTEROP_BASE_H
