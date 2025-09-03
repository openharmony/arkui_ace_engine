/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include <cstdint>

#define KOALA_INTEROP_MODULE TestNativeModule
#include "common-interop.h"
#include "interop-logging.h"
#include "arkoala_api_generated.h"
#include "Serializers.h"

void CallVoid(KVMContext vmContext, KInt methodId, KInt length, void* args) {
#if KOALA_USE_NODE_VM || KOALA_USE_HZ_VM || KOALA_USE_PANDA_VM || KOALA_USE_JAVA_VM || KOALA_CJ
    KOALA_INTEROP_CALL_VOID(vmContext, methodId, length, args)
#else
#error vm not supported
#endif
}

KInt CallInt(KVMContext vmContext, KInt methodId, KInt length, void* args) {
#if KOALA_USE_NODE_VM || KOALA_USE_HZ_VM || KOALA_USE_PANDA_VM || KOALA_USE_JAVA_VM || KOALA_CJ
    KOALA_INTEROP_CALL_INT(vmContext, methodId, length, args)
#else
#error vm not supported
#endif
    // to silence false-positive check "non-void function does not return a value"
    // actual return happens inside macro
    return 0;
}

void CallVoidInts32(KVMContext vmContext, KInt methodId, KInt numArgs, KInt* args) {
#if KOALA_USE_NODE_VM || KOALA_USE_HZ_VM || KOALA_USE_PANDA_VM || KOALA_USE_JAVA_VM || KOALA_CJ
    KOALA_INTEROP_CALL_VOID_INTS32(vmContext, methodId, numArgs, args)
#else
#error vm not supported
#endif
}

KInt CallIntInts32(KVMContext vmContext, KInt methodId, KInt numArgs, KInt* args) {
#if KOALA_USE_NODE_VM || KOALA_USE_HZ_VM || KOALA_USE_PANDA_VM || KOALA_USE_JAVA_VM || KOALA_CJ
    KOALA_INTEROP_CALL_INT_INTS32(vmContext, methodId, numArgs, args)
#else
#error vm not supported
#endif
    // to silence false-positive check "non-void function does not return a value"
    // actual return happens inside macro
    return 0;
}

KInt impl_TestCallIntNoArgs(KVMContext vmContext, KInt methodId) {
    int32_t args[] = { 0 };
    return CallInt(
        vmContext,
        methodId,
        0,
        reinterpret_cast<void*>(args)
    );
}
KOALA_INTEROP_CTX_1(TestCallIntNoArgs, KInt, KInt)

KInt impl_TestCallIntIntArraySum(KVMContext vmContext, KInt methodId, int32_t* arr, KInt length) {
    return CallIntInts32(
        vmContext,
        methodId,
        length,
        reinterpret_cast<KInt*>(arr)
    );
}
KOALA_INTEROP_CTX_3(TestCallIntIntArraySum, KInt, KInt, int32_t*, KInt)

void impl_TestCallVoidIntArrayPrefixSum(KVMContext vmContext, KInt methodId, int32_t* arr, KInt length) {
    return CallVoidInts32(
        vmContext,
        methodId,
        length,
        reinterpret_cast<KInt*>(arr)
    );
}
KOALA_INTEROP_CTX_V3(TestCallVoidIntArrayPrefixSum, KInt, int32_t*, KInt)

KInt impl_TestCallIntRecursiveCallback(KVMContext vmContext, KInt methodId, KSerializerBuffer arr, KInt length) {
    reinterpret_cast<int32_t*>(arr)[0]++;
    if (reinterpret_cast<int32_t*>(arr)[0] + reinterpret_cast<int32_t*>(arr)[1] < reinterpret_cast<int32_t*>(arr)[2]) {
        return CallInt(
            vmContext,
            methodId,
            length,
            reinterpret_cast<void*>(arr)
        );
    }
    return 0;
}
KOALA_INTEROP_CTX_3(TestCallIntRecursiveCallback, KInt, KInt, KSerializerBuffer, KInt)

KInt impl_TestCallIntMemory(KVMContext vmContext, KInt methodId, KInt n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        void* arr = malloc(n);
        for (int j = 0; j < n; j++) {
            reinterpret_cast<uint8_t*>(arr)[j] = j & 255;
        }
        res += CallInt(vmContext, methodId, n, arr) & 255;
        free(arr);
    }
    return res;
}
KOALA_INTEROP_CTX_2(TestCallIntMemory, KInt, KInt, KInt)

void impl_TestWithBuffer(KInteropBuffer buffer) {
    std::string result;
    if (buffer.length == 256) {
        int8_t* view = (int8_t*)buffer.data;
        result = std::to_string(view[0]) + " " + std::to_string(view[100]);
    } else {
        result = "Incorrect length of buffer " + std::to_string(buffer.length);
    }
    GetDefaultLogger()->appendGroupedLog(1, result.c_str());
}
KOALA_INTEROP_V1(TestWithBuffer, KInteropBuffer)
