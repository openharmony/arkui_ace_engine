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

#ifndef MOCK_OHOS_NAPI_ETSRUNTIME_ECMASCRIPT_NAPI_INCLUDE_JSNAPI_H
#define MOCK_OHOS_NAPI_ETSRUNTIME_ECMASCRIPT_NAPI_INCLUDE_JSNAPI_H

namespace panda {
class JSNApiHelper;
class EscapeLocalScope;
class PromiseRejectInfo;
template<typename T>
class CopyableGlobal;
template<typename T>
class Global;
class JSNApi;
template<typename T>
class Local;
class JSValueRef;
class PrimitiveRef;
class ArrayRef;
class BigIntRef;
class StringRef;
class ObjectRef;
class FunctionRef;
class NumberRef;
class BooleanRef;
class NativePointerRef;
class JsiRuntimeCallInfo;

namespace ecmascript {
class EcmaVM;
class JSTaggedValue;
class JSRuntimeOptions;
class JSThread;
struct EcmaRuntimeCallInfo;
} // namespace ecmascript
using WeakRefClearCallBack = void (*)(void*);

class ArrayBufferRef {
public:
    ArrayBufferRef();
};

template<typename T>
class CopyableGlobal {
public:
    inline CopyableGlobal() = default;
    ~CopyableGlobal() {}
};

} // namespace panda

#endif // MOCK_OHOS_NAPI_ETSRUNTIME_ECMASCRIPT_NAPI_INCLUDE_JSNAPI_H
