/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_MOCK_OHOS_MOCK_NAPI_NATIVE_ENGINE_NATIVE_VALUE_H
#define FOUNDATION_ACE_TEST_MOCK_OHOS_MOCK_NAPI_NATIVE_ENGINE_NATIVE_VALUE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>

#include "js_native_api.h"

// Forward declarations from napi subsystem
namespace panda {
class JsiRuntimeCallInfo;
}
namespace ecmascript {
struct JsFrameInfo;
}

namespace OHOS {

// Mock type declarations
class NativeEngine;
class NativeReference;

enum NativeValueType {
    NATIVE_UNDEFINED = 0,
    NATIVE_NULL = 1,
    NATIVE_BOOLEAN = 2,
    NATIVE_NUMBER = 3,
    NATIVE_STRING = 4,
    NATIVE_SYMBOL = 5,
    NATIVE_OBJECT = 6,
    NATIVE_FUNCTION = 7,
    NATIVE_EXTERNAL = 8,
    NATIVE_BIGINT = 9,
};

enum NativeThreadSafeFunctionCallMode {
    NATIVE_TSFUNC_NONBLOCKING = 0,
    NATIVE_TSFUNC_BLOCKING = 1,
};

enum NativeThreadSafeFunctionReleaseMode {
    NATIVE_TSFUNC_RELEASE = 0,
    NATIVE_TSFUNC_ABORT = 1,
};

// Forward declarations for native types
struct NativeObjectInfo {
    static NativeObjectInfo* CreateNewInstance();
    NativeEngine* engine;
    void* nativeObject;
    void (*callback)(void* data, void* hint);
    void* hint;
};

struct NapiFunctionInfo {
    static NapiFunctionInfo* CreateNewInstance();
    void* callback;
    void* data;
    bool isSendable;
    void* env;
};

#ifdef ENABLE_CONTAINER_SCOPE
int32_t scopeId = -1;
#endif

// Callback function types
typedef void (*NativeFinalize)(NativeEngine* engine, void* data, void* hint);
typedef void (*NativeAsyncExecuteCallback)(NativeEngine* engine, void* data);
typedef void (*NativeAsyncCompleteCallback)(NativeEngine* engine, int status, void* data);
typedef void (*DetachCallback)(NativeEngine* engine, void* value, void* hint);
typedef napi_value (*NativeCallback)(NativeEngine* env, void* value, void* hint);

using ErrorPos = std::pair<uint32_t, uint32_t>;
typedef void (*NativeThreadSafeFunctionCallJs)(NativeEngine* env, napi_value js_callback, void* context, void* data);

} // namespace OHOS

#endif // FOUNDATION_ACE_TEST_MOCK_OHOS_MOCK_NAPI_NATIVE_ENGINE_NATIVE_VALUE_H
